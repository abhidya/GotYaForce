#!/usr/bin/env python3
"""selftest.py -- prove the matching harness works, without the compiler.

`mwcceppc.exe` is not on this machine, so the decisive test of the spike -- write
C, compile it, get the retail bytes -- cannot be run.  What CAN be proven is
everything on either side of the compiler: that the retail bytes are extracted
correctly, that a candidate object is decoded correctly, that relocations are
handled the way a real freshly-compiled object needs, that a MATCH is reported
when and only when the program is the same, and that a MISMATCH names the exact
instruction that differs.

Six checks, each with an expected verdict stated up front.  Any deviation is a
harness bug and this script exits non-zero.

    T1  identity                retail vs retail                -> MATCH
    T2  stand-in backend        assembled candidate             -> MATCH
    T3  single-word mutation    negative control                -> MISMATCH @ known offset
    T4  semantic equivalent     different encoding, same effect -> MISMATCH
    T5  wrong length            truncated candidate             -> MISMATCH
    T6  relocated object        synthetic ELF32-BE .o w/ REL24  -> MATCH (reloc masked)
        T6b same, wrong symbol                                  -> MISMATCH (symbol check)

T2 is NOT evidence that the function is matchable from C.  It writes the same
instructions twice.  Its claim is only that the encode->compare path works.
"""
from __future__ import annotations

import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from dolsym import load, function_bytes  # noqa: E402
from objdiff import compare, render_diff  # noqa: E402
from ppcasm import assemble  # noqa: E402

REPO = HERE.parents[2]

FAILURES = []


def check(name, cond, detail=""):
    status = "ok  " if cond else "FAIL"
    print("  [%s] %s %s" % (status, name, detail))
    if not cond:
        FAILURES.append(name)


# --------------------------------------------------------------------------
# a minimal ELF32 big-endian relocatable-object WRITER, for T6 only.
# This stands in for the object file mwcceppc would emit.
# --------------------------------------------------------------------------

def make_elf32be_obj(text, relocs, symnames):
    """relocs: [(offset, r_type, symbol_index)]; symnames: ['', 'fn', 'callee']"""
    shstr = b"\x00.text\x00.rela.text\x00.symtab\x00.strtab\x00.shstrtab\x00"

    def shoff(nm):
        return shstr.index(nm.encode() + b"\x00")

    strtab = b"\x00" + b"".join(n.encode() + b"\x00" for n in symnames[1:])

    def stroff(n):
        return strtab.index(n.encode() + b"\x00")

    sym = b"\x00" * 16  # STN_UNDEF
    # index 1: the function itself, defined in .text (shndx 1)
    sym += struct.pack(">IIIBBH", stroff(symnames[1]), 0, len(text),
                       (1 << 4) | 2, 0, 1)
    # index 2..: undefined callees
    for n in symnames[2:]:
        sym += struct.pack(">IIIBBH", stroff(n), 0, 0, (1 << 4) | 2, 0, 0)

    rela = b"".join(struct.pack(">IIi", off, (si << 8) | rt, 0)
                    for off, rt, si in relocs)

    secs = [
        ("", 0, b"", 0, 0, 0),
        (".text", 1, text, 6, 0, 0),
        (".rela.text", 4, rela, 0, 3, 1),
        (".symtab", 2, sym, 0, 4, 1),
        (".strtab", 3, strtab, 0, 0, 0),
        (".shstrtab", 3, shstr, 0, 0, 0),
    ]
    ehsize, shentsize = 52, 40
    off = ehsize
    body = b""
    hdrs = []
    for nm, typ, data, flags, link, info in secs:
        if typ == 0:
            hdrs.append((0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
            continue
        pad = (-off) % 4
        body += b"\x00" * pad
        off += pad
        entsize = {2: 16, 4: 12}.get(typ, 0)
        hdrs.append((shoff(nm), typ, flags, 0, off, len(data), link, info,
                     4, entsize))
        body += data
        off += len(data)
    pad = (-off) % 4
    body += b"\x00" * pad
    off += pad
    shoff_final = off
    eh = b"\x7fELF" + bytes([1, 2, 1, 0]) + b"\x00" * 8
    eh += struct.pack(">HHIIIIIHHHHHH", 1, 20, 1, 0, 0, shoff_final, 0,
                      ehsize, 0, 0, shentsize, len(secs), 5)
    sh = b"".join(struct.pack(">10I", *h) for h in hdrs)
    return eh + body + sh


def main():
    dol, smap = load(repo=str(REPO.parents[2]) if False else "D:/GotYaForce")

    print("== T1  identity: retail vs retail ==")
    rec, retail = function_bytes(dol, smap, "zz_00660b8_")
    v = compare(retail, retail, [], rec["addr"])
    check("T1 verdict MATCH", v["verdict"] == "MATCH", v["verdict"])
    check("T1 exact bytes", v["exact_bytes"] is True)
    check("T1 100%", v["match_pct"] == 100.0)

    print("\n== T2  stand-in backend: assemble a candidate, compare ==")
    src = """
        lbz  r0, 0x57b(r3)
        or   r0, r0, r4
        stb  r0, 0x57b(r3)
        blr
    """
    cand, _ = assemble(src, rec["addr"])
    v = compare(retail, cand, [], rec["addr"])
    check("T2 verdict MATCH", v["verdict"] == "MATCH", v["verdict"])
    check("T2 bytes equal retail", cand == retail,
          "%s vs %s" % (cand.hex(), retail.hex()))
    print("       (this writes the same instructions twice; it proves the "
          "encoder and\n        comparator agree, NOT that the function is "
          "matchable from C)")

    print("\n== T3  negative control: one word changed ==")
    bad = bytearray(cand)
    struct.pack_into(">I", bad, 4, 0x7C002378 ^ 0x00010000)  # or r0,r0,r4 -> r5
    v = compare(retail, bytes(bad), [], rec["addr"])
    check("T3 verdict MISMATCH", v["verdict"] == "MISMATCH", v["verdict"])
    check("T3 names instruction 1", v["first_diff"]
          and v["first_diff"]["index"] == 1,
          str(v["first_diff"] and v["first_diff"]["addr"]))
    check("T3 3 of 4 still match", v["matched_insns"] == 3,
          "%d" % v["matched_insns"])
    print("       first_diff: retail %s / candidate %s"
          % (v["first_diff"]["retail"], v["first_diff"]["cand"]))

    print("\n== T4  semantically equivalent, differently encoded ==")
    # Same observable effect (set bits of r4 into byte [r3+0x57b]) written the
    # way a different compiler / different C would emit it.  A behavioural
    # oracle would PASS this.  A matching oracle must REJECT it -- that
    # rejection is the entire value of the route, and its entire cost.
    alt = """
        addi r5, r3, 0x57b
        lbz  r0, 0(r5)
        or   r0, r4, r0
        stb  r0, 0(r5)
        blr
    """
    cand4, _ = assemble(alt, rec["addr"])
    v = compare(retail, cand4, [], rec["addr"])
    check("T4 verdict MISMATCH", v["verdict"] == "MISMATCH", v["verdict"])
    check("T4 length differs", v["size_match"] is False,
          "retail %d vs cand %d" % (v["retail_insns"], v["cand_insns"]))

    print("\n== T5  truncated candidate ==")
    v = compare(retail, cand[:8], [], rec["addr"])
    check("T5 verdict MISMATCH", v["verdict"] == "MISMATCH", v["verdict"])
    check("T5 size flagged", v["size_match"] is False)

    print("\n== T6  relocated object: the shape mwcceppc actually emits ==")
    rec2, retail2 = function_bytes(dol, smap, "zz_00122c8_")
    print("       target %s @ 0x%08x, %d insns, calls 0x80012308"
          % (rec2["name"], rec2["addr"], rec2["size"] // 4))
    # A fresh .o has bl target = 0 and an R_PPC_REL24 relocation naming the callee.
    fresh = bytearray(retail2)
    struct.pack_into(">I", fresh, 12, 0x48000001)  # bl 0 (+lk), unlinked
    obj = make_elf32be_obj(bytes(fresh),
                           [(12, 10, 2)],           # offset 12, R_PPC_REL24, sym 2
                           ["", "zz_00122c8_", "zz_0012308_"])
    from objdiff import Elf32BE
    e = Elf32BE(obj)
    sec = e.section(".text")
    cand6 = e.data(sec)
    rel6 = e.relocs_for(".text")
    check("T6 elf parses", len(cand6) == len(retail2), "%d B" % len(cand6))
    check("T6 one relocation", len(rel6) == 1, str(rel6))
    check("T6 reloc is REL24 @ +0x00c",
          rel6 and rel6[0][0] == 12 and rel6[0][1] == 10)
    check("T6 reloc names callee", rel6 and rel6[0][2] == "zz_0012308_",
          rel6[0][2] if rel6 else "-")
    v = compare(retail2, cand6, rel6, rec2["addr"],
                expected_syms={12: "zz_0012308_"})
    check("T6 verdict MATCH (bl masked by reloc)", v["verdict"] == "MATCH",
          v["verdict"])
    check("T6 not exact bytes", v["exact_bytes"] is False,
          "the bl word genuinely differs; the relocation is why that is ok")

    v = compare(retail2, cand6, rel6, rec2["addr"],
                expected_syms={12: "some_other_function"})
    check("T6b wrong callee symbol -> MISMATCH", v["verdict"] == "MISMATCH",
          v["verdict"])
    check("T6b symbol error reported", len(v["reloc_symbol_errors"]) == 1,
          str(v["reloc_symbol_errors"]))

    print("\n== T7  unmasked bl would be a false mismatch (why T6 matters) ==")
    v = compare(retail2, cand6, [], rec2["addr"])
    check("T7 without relocs -> MISMATCH at the bl",
          v["verdict"] == "MISMATCH" and v["first_diff"]["offset"] == 12,
          str(v["first_diff"] and v["first_diff"]["addr"]))

    print("\n" + "=" * 66)
    if FAILURES:
        print("HARNESS SELFTEST FAILED: %d check(s): %s"
              % (len(FAILURES), ", ".join(FAILURES)))
        return 1
    print("HARNESS SELFTEST PASSED -- all checks, including both negative")
    print("controls and the relocation-symbol control.")
    print("This exercises the extractor, encoder and comparator only -- NO")
    print("compiler is invoked.  For the compiler stage, run:")
    print("    python src-match/verify.py --control")
    print("which drives mwcc-rs over the matched corpus (see TOOLCHAIN.md).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
