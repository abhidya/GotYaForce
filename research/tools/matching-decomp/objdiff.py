#!/usr/bin/env python3
"""objdiff.py -- the ORACLE of a matching decompilation.

Given the retail bytes of a function and the object code a candidate C source
compiled to, decide -- exactly, mechanically, in milliseconds, with no
hand-authored spec and no console capture -- whether they are the same program.

This is a re-implementation of the comparison rule that `objdiff`
(github.com/encounter/objdiff) applies, in the ~200 lines this project needs,
so the loop has no external dependency:

  1. A freshly compiled object file's branch and address operands are ZERO,
     because the linker has not run.  Every such field carries a relocation.
     Comparing raw bytes there would report a difference that is not one.
     So each relocated operand field is masked on BOTH sides, and the
     relocation's SYMBOL is compared instead.
  2. Everything not covered by a relocation must be byte-identical.  There is
     no tolerance, no similarity threshold, no "close enough".

Two verdicts are produced and they are not the same claim:

    exact        every byte identical, relocations included.  Only meaningful
                 when comparing retail against retail, or against an already
                 linked image.
    MATCH        every byte identical after relocation masking, AND every
                 relocation names the symbol the retail call/reference goes to.
                 This is what a decomp project means by "matched".

Anything else is a MISMATCH, and the report names the first differing
instruction, which is what feeds back into the next LLM iteration.

Candidate input may be:
    * an ELF32 big-endian relocatable object (what mwcceppc emits), via --obj
    * a raw big-endian blob, via --bin
    * assembly, assembled by ppcasm.py, via --asm

Exit code 0 == MATCH, 1 == MISMATCH, 2 == harness error.  Machine-readable
verdict on stdout with --json.
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ppcdis import disasm_word  # noqa: E402


# --------------------------------------------------------------------------
# ELF32 big-endian reader -- enough for a mwcceppc .o
# --------------------------------------------------------------------------

SHT_RELA, SHT_REL, SHT_SYMTAB = 4, 9, 2

# PowerPC EABI relocation types and the operand field each one patches.
# (name, mask of the bits the relocation OWNS in the 32-bit instruction word)
PPC_RELOC = {
    1:  ("R_PPC_ADDR32", 0xFFFFFFFF),
    3:  ("R_PPC_ADDR16_LO", 0x0000FFFF),
    4:  ("R_PPC_ADDR16_HI", 0x0000FFFF),
    5:  ("R_PPC_ADDR16_HA", 0x0000FFFF),
    6:  ("R_PPC_ADDR14", 0x0000FFFC),
    10: ("R_PPC_REL24", 0x03FFFFFC),
    11: ("R_PPC_REL14", 0x0000FFFC),
    26: ("R_PPC_REL32", 0xFFFFFFFF),
    109: ("R_PPC_EMB_SDA21", 0x001FFFFF),
    110: ("R_PPC_EMB_MRKREF", 0x00000000),
}


class Elf32BE(object):
    def __init__(self, blob):
        self.b = blob
        if blob[:4] != b"\x7fELF":
            raise ValueError("not an ELF file")
        if blob[4] != 1 or blob[5] != 2:
            raise ValueError("not ELF32 big-endian (got class=%d data=%d)"
                             % (blob[4], blob[5]))
        (self.e_type, self.e_machine) = struct.unpack_from(">HH", blob, 16)
        (self.e_shoff,) = struct.unpack_from(">I", blob, 32)
        (self.e_shentsize, self.e_shnum, self.e_shstrndx) = \
            struct.unpack_from(">HHH", blob, 46)
        self.sh = []
        for i in range(self.e_shnum):
            o = self.e_shoff + i * self.e_shentsize
            f = struct.unpack_from(">10I", blob, o)
            self.sh.append({"name_off": f[0], "type": f[1], "flags": f[2],
                            "addr": f[3], "offset": f[4], "size": f[5],
                            "link": f[6], "info": f[7], "align": f[8],
                            "entsize": f[9]})
        strtab = self.sh[self.e_shstrndx]
        self.shstr = blob[strtab["offset"]:strtab["offset"] + strtab["size"]]
        for s in self.sh:
            s["name"] = self._str(self.shstr, s["name_off"])

    @staticmethod
    def _str(tab, off):
        e = tab.find(b"\x00", off)
        return tab[off:e if e >= 0 else len(tab)].decode("latin1")

    def section(self, name):
        for s in self.sh:
            if s["name"] == name:
                return s
        return None

    def data(self, s):
        return self.b[s["offset"]:s["offset"] + s["size"]]

    def symbols(self):
        st = None
        for s in self.sh:
            if s["type"] == SHT_SYMTAB:
                st = s
                break
        if st is None:
            return []
        strs = self.data(self.sh[st["link"]])
        out = []
        n = st["size"] // 16
        for i in range(n):
            o = st["offset"] + i * 16
            nm, val, sz, info, other, shndx = struct.unpack_from(">IIIBBH", self.b, o)
            out.append({"name": self._str(strs, nm), "value": val,
                        "size": sz, "shndx": shndx})
        return out

    def relocs_for(self, secname):
        """[(offset, type, symbol_name, addend)] targeting secname."""
        syms = self.symbols()
        out = []
        for s in self.sh:
            if s["type"] not in (SHT_REL, SHT_RELA):
                continue
            if s["name"] not in (".rela" + secname, ".rel" + secname):
                continue
            rela = s["type"] == SHT_RELA
            step = 12 if rela else 8
            d = self.data(s)
            for i in range(0, len(d) - step + 1, step):
                if rela:
                    off, info, add = struct.unpack_from(">IIi", d, i)
                else:
                    off, info = struct.unpack_from(">II", d, i)
                    add = 0
                rtype = info & 0xFF
                sidx = info >> 8
                nm = syms[sidx]["name"] if sidx < len(syms) else "?"
                out.append((off, rtype, nm, add))
        return out


# --------------------------------------------------------------------------
# comparison
# --------------------------------------------------------------------------

def words(blob):
    n = len(blob) // 4
    return list(struct.unpack(">%dI" % n, blob[:n * 4]))


def compare(retail, cand, cand_relocs=None, base_addr=0,
            retail_relocs=None, expected_syms=None):
    """The oracle.  Returns a verdict dict.

    retail        bytes from the DOL
    cand          bytes of the candidate's .text
    cand_relocs   [(offset, type, sym, addend)] from the candidate object
    expected_syms {offset: symbol_name} the retail call/ref at that offset
                  should resolve to; if given, relocation SYMBOLS are checked.
    """
    cand_relocs = cand_relocs or []
    rmap = {}
    for off, rtype, nm, add in cand_relocs:
        name, mask = PPC_RELOC.get(rtype, ("R_PPC_%d" % rtype, 0xFFFFFFFF))
        rmap.setdefault(off & ~3, []).append((off, name, mask, nm, add))

    rw, cw = words(retail), words(cand)
    n = min(len(rw), len(cw))
    diffs = []
    same = 0
    exact = (retail == cand)
    reloc_notes = []

    for i in range(n):
        off = i * 4
        a, b = rw[i], cw[i]
        mask = 0
        rl = rmap.get(off, [])
        for _o, rname, rmask, rsym, radd in rl:
            mask |= rmask
            reloc_notes.append({"offset": off, "type": rname,
                                "symbol": rsym, "addend": radd})
        if (a & ~mask) == (b & ~mask):
            same += 1
        else:
            diffs.append({
                "index": i, "offset": off, "addr": "0x%08x" % (base_addr + off),
                "retail_word": "0x%08x" % a, "cand_word": "0x%08x" % b,
                "retail": disasm_word(a, base_addr + off),
                "cand": disasm_word(b, base_addr + off),
                "reloc_mask": "0x%08x" % mask,
            })

    size_ok = len(rw) == len(cw)
    verdict = "MATCH" if (size_ok and not diffs) else "MISMATCH"

    # symbol check on relocations
    sym_errors = []
    if expected_syms:
        for off, rtype, nm, add in cand_relocs:
            want = expected_syms.get(off)
            if want is not None and want != nm:
                sym_errors.append({"offset": off, "expected": want, "got": nm})
        if sym_errors:
            verdict = "MISMATCH"

    return {
        "verdict": verdict,
        "exact_bytes": exact,
        "retail_insns": len(rw),
        "cand_insns": len(cw),
        "size_match": size_ok,
        "matched_insns": same,
        "match_pct": round(100.0 * same / max(len(rw), len(cw), 1), 2),
        "first_diff": diffs[0] if diffs else None,
        "diffs": diffs,
        "relocations": reloc_notes,
        "reloc_symbol_errors": sym_errors,
    }


def render_diff(v, retail, cand, base_addr):
    """Side-by-side text -- this is what goes back into the LLM prompt."""
    rw, cw = words(retail), words(cand)
    bad = set(d["index"] for d in v["diffs"])
    lines = []
    n = max(len(rw), len(cw))
    for i in range(n):
        a = rw[i] if i < len(rw) else None
        b = cw[i] if i < len(cw) else None
        addr = base_addr + i * 4
        ls = "%08x  %-34s" % (addr, disasm_word(a, addr)) if a is not None \
            else " " * 44
        rs = "%-34s" % (disasm_word(b, addr) if b is not None else "")
        mark = "  " if (i not in bad and a is not None and b is not None) else "<<"
        lines.append("%s |%s %s" % (ls, mark, rs))
    return "\n".join(lines)


# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--function", required=True,
                    help="name or 0xADDR of the retail function")
    ap.add_argument("--repo", default="D:/GotYaForce")
    ap.add_argument("--obj", help="candidate ELF32-BE relocatable object")
    ap.add_argument("--obj-section", default=".text")
    ap.add_argument("--obj-symbol", help="symbol inside --obj to compare (default: whole section)")
    ap.add_argument("--bin", dest="binf", help="candidate raw big-endian blob")
    ap.add_argument("--asm", help="candidate assembly, assembled by ppcasm.py")
    ap.add_argument("--mutate", help="i:0xWORD -- perturb the candidate (negative control)")
    ap.add_argument("--json")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()

    from dolsym import load, function_bytes
    dol, smap = load(repo=a.repo)
    rec, retail = function_bytes(dol, smap, a.function)
    if rec is None:
        # allow raw address+size
        print("error: %s not found in the link map" % a.function, file=sys.stderr)
        return 2
    base = rec["addr"]

    cand_relocs = []
    if a.obj:
        e = Elf32BE(Path(a.obj).read_bytes())
        s = e.section(a.obj_section)
        if s is None:
            print("error: %s has no section %s" % (a.obj, a.obj_section),
                  file=sys.stderr)
            return 2
        cand = e.data(s)
        cand_relocs = e.relocs_for(a.obj_section)
        if a.obj_symbol:
            for sy in e.symbols():
                if sy["name"] == a.obj_symbol and sy["size"]:
                    cand = cand[sy["value"]:sy["value"] + sy["size"]]
                    cand_relocs = [(o - sy["value"], t, n, ad)
                                   for o, t, n, ad in cand_relocs
                                   if sy["value"] <= o < sy["value"] + sy["size"]]
                    break
    elif a.binf:
        cand = Path(a.binf).read_bytes()
    elif a.asm:
        from ppcasm import assemble_file
        cand, _ = assemble_file(a.asm, base)
    else:
        cand = retail  # identity check

    if a.mutate:
        i_s, w_s = a.mutate.split(":")
        i = int(i_s)
        w = int(w_s, 16)
        b = bytearray(cand)
        struct.pack_into(">I", b, i * 4, w)
        cand = bytes(b)

    v = compare(retail, cand, cand_relocs, base)
    v["function"] = rec["name"]
    v["address"] = "0x%08x" % base
    v["retail_size"] = rec["size"]

    if not a.quiet:
        print("== %s @ 0x%08x (%d B) ==" % (rec["name"], base, rec["size"]))
        print("%-44s | %s" % ("RETAIL", "CANDIDATE"))
        print(render_diff(v, retail, cand, base))
        print()
        for r in v["relocations"]:
            print("  reloc +0x%03x %-20s -> %s%+d" % (
                r["offset"], r["type"], r["symbol"], r["addend"]))
        print("\nVERDICT %s   %d/%d instructions   %.2f%%   exact_bytes=%s"
              % (v["verdict"], v["matched_insns"], max(v["retail_insns"],
                 v["cand_insns"]), v["match_pct"], v["exact_bytes"]))
        if v["first_diff"]:
            d = v["first_diff"]
            print("first difference at %s: retail %s (%s) vs candidate %s (%s)"
                  % (d["addr"], d["retail_word"], d["retail"],
                     d["cand_word"], d["cand"]))

    if a.json:
        Path(a.json).write_text(json.dumps(v, indent=1))
        if not a.quiet:
            print("wrote %s" % a.json)

    return 0 if v["verdict"] == "MATCH" else 1


if __name__ == "__main__":
    sys.exit(main())
