#!/usr/bin/env python3
"""datareloc.py -- make DATA relocations verifiable against the retail DOL.

THE GAP THIS CLOSES
-------------------
`objdiff.compare` masks every relocated operand on both sides and compares the
relocation's SYMBOL instead.  `match.py` could only resolve `R_PPC_REL24`
branch targets, because the link map
(`research/symbols/GG4E-CSM-20220412.map`) has a `.text section layout` block
and nothing else -- **the linked DOL carries no data symbol table.**  So a
candidate whose match rests on a *data* relocation
(`R_PPC_ADDR16_HA/LO/HI`, `R_PPC_ADDR32`, `R_PPC_EMB_SDA21`) had that operand
masked and never name-checked, and would have matched **any global in the
game**.  Measured, live, before this module existed: a hand-written candidate
for `zz_000a144_` naming `DAT_804360c8` / `DAT_804360c4` -- both off by four
from the globals the retail bytes actually touch -- reported `MATCH 100.00%`.

The retail bytes do carry the truth, and this module reads it.

  * `lwz rT, d(r13)` and friends encode `_SDA_BASE_ + d` exactly.
  * `lis rD, hi` + `addi/ori rD, rD, lo` (or a following `d(rD)` access)
    encode an absolute address exactly.

and the candidate side is resolvable too, because every global name this
corpus uses carries its own address (`DAT_80436498`, `FLOAT_80436a20`,
`PTR_DAT_8043393c`, `zz_02650c0_`), and `research/decomp/data/oracle-registry.json`
enumerates them.

THE RULE, as implemented
------------------------
For every data relocation the candidate object carries at offset `O`:

  1. `want` = the absolute GameCube address the RETAIL encoding at `O` names,
     derived from the retail bytes alone (SDA base + displacement, or the
     `lis`/`addi` pair, or the `ADDR32` word itself).
  2. `got`  = `resolve(relocation symbol) + addend`, resolved from the link
     map, the address encoded in the symbol name, or the oracle registry.
  3. `got == want`  -> the relocation is VERIFIED.
     `got != want`  -> MISMATCH.  Hard red.  This is the case the old oracle
                       accepted.
     either side unresolvable -> MATCH_UNVERIFIED, with the reason named.

Fail-closed everywhere: an unrecognised relocation type, a retail encoding
this module cannot reduce to an address, or a symbol it cannot resolve, all
downgrade the verdict.  Nothing here can turn a MISMATCH into a MATCH.

THE SDA BASES, and why they are not a guess
-------------------------------------------
Two independent derivations, cross-checked at load time; they must agree or
this module refuses to produce bases at all.

  a) The ROM's own boot code.  `__init_registers` ends with

         80003324  3c208044  lis  r1,  0x8044     ; stack
         80003328  6021d528  ori  r1,  r1, 0xd528
         8000332c  3c408043  lis  r2,  0x8043     ; _SDA2_BASE_
         80003330  6042ea20  ori  r2,  r2, 0xea20
         80003334  3da08043  lis  r13, 0x8043     ; _SDA_BASE_
         80003338  61adb5a0  ori  r13, r13, 0xb5a0
         8000333c  4e800020  blr

     -> r2 = 0x8043EA20, r13 = 0x8043B5A0.

  b) The DOL section table.  The Metrowerks EABI linker puts each small-data
     base 0x8000 past the start of its section, so a signed 16-bit
     displacement reaches the whole area:

         .sdata  @ 0x804335A0  ->  0x804335A0 + 0x8000 = 0x8043B5A0   (r13)
         .sdata2 @ 0x80436A20  ->  0x80436A20 + 0x8000 = 0x8043EA20   (r2)

A third, fully independent corroboration comes from Ghidra: `zz_0010b50_`
stores through `r13 - 0x54c4 / -0x54c6 / -0x54c8`, which under these bases are
0x804360DC / 0x804360DA / 0x804360D8 -- exactly the `DAT_804360dc`,
`DAT_804360da`, `DAT_804360d8` that `oracle-registry.json` records for that
function, derived by a different tool from a different pass.

FOR THE SEEDER LANE
-------------------
`loop.py`'s `leaf` seeder refuses r2/r13 access outright (`_base_fail`).  That
refusal was correct while data relocations were unverifiable; it no longer has
to be.  A seeder may lift it by calling

    datareloc.global_symbol(dol, smap, addr)   -> the C identifier a candidate
                                                  must use for the global at
                                                  `addr` (registry name if the
                                                  corpus has one, else
                                                  `DAT_%08x`)
    datareloc.global_decl(name, width, signed) -> the `extern` declaration
    datareloc.sda_bases(dol, smap)             -> {2: ..., 13: ...} + evidence
    datareloc.sda_target(word, bases)          -> the address a `d(r13)`-style
                                                  retail word names, or None

and nothing else changes: the candidate compiles to an `R_PPC_EMB_SDA21`
whose symbol this module now checks against the retail address.  A seeder that
guesses the wrong global no longer produces a match -- it produces a red.
"""
from __future__ import annotations

import json
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

REPO_DEFAULT = Path("D:/GotYaForce")

# ---------------------------------------------------------------------------
# relocation classification
# ---------------------------------------------------------------------------

# Relocation type numbers whose operand names a DATA address.  R_PPC_REL24 /
# REL14 are NOT here: those are branch targets and `match.py.expected_symbols`
# already name-checks them through the link map.
R_ADDR32, R_ADDR16, R_ADDR16_LO, R_ADDR16_HI, R_ADDR16_HA = 1, 2, 3, 4, 5
R_EMB_SDA21 = 109

DATA_RELOC_TYPES = {R_ADDR32, R_ADDR16, R_ADDR16_LO, R_ADDR16_HI,
                    R_ADDR16_HA, R_EMB_SDA21}

# Relocation types that carry no operand and need no address check.
R_EMB_MRKREF = 110
BENIGN_RELOC_TYPES = {R_EMB_MRKREF}


# ---------------------------------------------------------------------------
# the minimum PowerPC decoding this needs
# ---------------------------------------------------------------------------

# primary opcode -> (is_store, writes_rd)
DFORM_MEM = {
    32: (False, True),   34: (False, True),   40: (False, True),
    42: (False, True),   46: (False, True),   48: (False, False),
    50: (False, False),
    33: (False, True),   35: (False, True),   41: (False, True),
    43: (False, True),   49: (False, False),  51: (False, False),
    36: (True, False),   38: (True, False),   44: (True, False),
    47: (True, False),   52: (True, False),   54: (True, False),
    37: (True, False),   39: (True, False),   45: (True, False),
    53: (True, False),   55: (True, False),
}
OP_ADDI, OP_ADDIS, OP_ORI = 14, 15, 24


def _s16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def _fields(w):
    return (w >> 26), ((w >> 21) & 31), ((w >> 16) & 31), (w & 0xFFFF)


def sda_target(word, bases):
    """The absolute address a `d(r2)` / `d(r13)` retail encoding names.

    Also handles the r0 form the EABI linker emits when an `@sda21` symbol
    lives in neither small-data area (the displacement is then the whole
    address).  Returns None when the word is not a small-data reference.
    """
    op, _rd, ra, d = _fields(word)
    if op in DFORM_MEM or op == OP_ADDI:
        if ra in bases:
            return (bases[ra] + _s16(d)) & 0xFFFFFFFF
        if ra == 0:
            return _s16(d) & 0xFFFFFFFF
    return None


def absolute_refs(retail, base_addr=0):
    """{offset: absolute address} for every `lis`-built reference in a function.

    A forward symbolic scan carrying, per register, the high half a `lis` put
    there.  The address is only complete once the low half arrives, so BOTH the
    `lis` offset and the offset that supplies the low half are recorded -- which
    is exactly the pair of offsets a compiler puts `R_PPC_ADDR16_HA` and
    `R_PPC_ADDR16_LO` on.

    Any instruction this scan does not model CLEARS the whole pending-high map.
    That is deliberate: a stale high half would produce a WRONG retail address,
    and a wrong address in this table could let a bad candidate through.  A
    dropped one only costs a MATCH_UNVERIFIED.
    """
    out = {}
    pend = {}                      # reg -> (offset of the lis, high half)
    n = len(retail) // 4
    for i in range(n):
        off = i * 4
        w = struct.unpack_from(">I", retail, off)[0]
        op, rd, ra, d = _fields(w)
        if op == OP_ADDIS and ra == 0:
            pend[rd] = (off, d)
            continue
        if op == OP_ADDI:
            if ra in pend:
                ho, hi = pend[ra]
                addr = ((hi << 16) + _s16(d)) & 0xFFFFFFFF
                out[ho] = addr
                out[off] = addr
            pend.pop(rd, None)
            continue
        if op == OP_ORI:
            # ori rA, rS, UIMM -- destination is rA, source is rS (bits 21-25)
            if rd in pend:
                ho, hi = pend[rd]
                addr = ((hi << 16) | d) & 0xFFFFFFFF
                out[ho] = addr
                out[off] = addr
            pend.pop(ra, None)
            continue
        if op in DFORM_MEM:
            if ra in pend:
                ho, hi = pend[ra]
                addr = ((hi << 16) + _s16(d)) & 0xFFFFFFFF
                out[ho] = addr
                out[off] = addr
            if DFORM_MEM[op][1]:
                pend.pop(rd, None)
            continue
        if op == 18:               # b / bl -- no GPR written
            continue
        pend.clear()
    return out


def retail_data_addresses(retail, base_addr, bases):
    """{offset: (address, how)} for every data reference the retail encodes.

    `how` is one of 'sda' (small-data base + displacement), 'abs-lis' (a
    `lis`/low-half pair) or 'abs-r0' (a bare absolute displacement).
    """
    out = {}
    for off, addr in absolute_refs(retail, base_addr).items():
        out[off] = (addr, "abs-lis")
    n = len(retail) // 4
    for i in range(n):
        off = i * 4
        if off in out:
            continue
        w = struct.unpack_from(">I", retail, off)[0]
        op, _rd, ra, _d = _fields(w)
        t = sda_target(w, bases)
        if t is not None:
            out[off] = (t, "sda" if ra in bases else "abs-r0")
    return out


# ---------------------------------------------------------------------------
# the SDA bases
# ---------------------------------------------------------------------------

class SdaBaseError(RuntimeError):
    pass


def _bases_from_boot(dol, smap):
    """r2 / r13 as the ROM's own `__init_registers` sets them."""
    rec = smap.by_name.get("__init_registers")
    if rec is None:
        raise SdaBaseError("__init_registers is not in the link map")
    # The map understates this function's extent; read forward to its `blr`.
    blob = dol.read(rec["addr"], 0x100)
    if blob is None:
        raise SdaBaseError("__init_registers is not inside a DOL section")
    found, ev = {}, []
    pend = {}
    for i in range(len(blob) // 4):
        w = struct.unpack_from(">I", blob, i * 4)[0]
        a = rec["addr"] + i * 4
        op, rd, ra, d = _fields(w)
        if op == OP_ADDIS and ra == 0:
            pend[rd] = (a, w, d)
        elif op == OP_ORI and rd in pend:
            ha, hw, hi = pend.pop(rd)
            if rd in (2, 13):
                found[rd] = ((hi << 16) | d) & 0xFFFFFFFF
                ev.append("0x%08x %08x lis r%d, 0x%04x / 0x%08x %08x "
                          "ori r%d, r%d, 0x%04x -> 0x%08x"
                          % (ha, hw, rd, hi, a, w, rd, rd, d, found[rd]))
        elif op == OP_ADDI and ra in pend and ra == rd:
            ha, hw, hi = pend.pop(rd)
            if rd in (2, 13):
                found[rd] = ((hi << 16) + _s16(d)) & 0xFFFFFFFF
                ev.append("0x%08x %08x lis r%d, 0x%04x / 0x%08x %08x "
                          "addi r%d, r%d, 0x%04x -> 0x%08x"
                          % (ha, hw, rd, hi, a, w, rd, rd, d, found[rd]))
        if w == 0x4E800020:        # blr -- end of __init_registers
            break
    if 2 not in found or 13 not in found:
        raise SdaBaseError("__init_registers does not set both r2 and r13 "
                           "(found %s)" % sorted(found))
    return found, ev


def _bases_from_sections(dol):
    """r2 / r13 from the DOL section table: small-data base = start + 0x8000.

    The two highest-addressed DOL data sections are `.sdata` and `.sdata2`;
    the Metrowerks EABI linker centres each base 0x8000 into its section so a
    signed 16-bit displacement covers it.
    """
    if len(dol.data) < 2:
        raise SdaBaseError("DOL has fewer than two data sections")
    ds = sorted(dol.data, key=lambda t: t[1])
    sdata, sdata2 = ds[-2], ds[-1]
    ev = [".sdata  @ 0x%08x size 0x%x -> r13 = 0x%08x"
          % (sdata[1], sdata[2], sdata[1] + 0x8000),
          ".sdata2 @ 0x%08x size 0x%x -> r2  = 0x%08x"
          % (sdata2[1], sdata2[2], sdata2[1] + 0x8000)]
    return {13: sdata[1] + 0x8000, 2: sdata2[1] + 0x8000}, ev


_BASES_CACHE = {}


def sda_bases(dol, smap):
    """{2: _SDA2_BASE_, 13: _SDA_BASE_} plus the evidence for each.

    Both derivations must agree.  If they do not, this raises rather than
    picking one -- a wrong base silently mis-addresses every global.
    """
    key = id(dol)
    if key in _BASES_CACHE:
        return _BASES_CACHE[key]
    boot, boot_ev = _bases_from_boot(dol, smap)
    sect, sect_ev = _bases_from_sections(dol)
    if boot != sect:
        raise SdaBaseError(
            "the two SDA base derivations disagree: boot code says %s, the "
            "DOL section table says %s"
            % ({k: "0x%08x" % v for k, v in boot.items()},
               {k: "0x%08x" % v for k, v in sect.items()}))
    out = dict(boot)
    out["evidence"] = {"__init_registers": boot_ev, "dol_sections": sect_ev}
    _BASES_CACHE[key] = out
    return out


def bases_only(dol, smap):
    b = sda_bases(dol, smap)
    return {k: v for k, v in b.items() if isinstance(k, int)}


# ---------------------------------------------------------------------------
# candidate-side symbol resolution
# ---------------------------------------------------------------------------

# `DAT_80436498`, `FLOAT_80436a20`, `PTR_DAT_8043393c`, `DOUBLE_80436a28`,
# `PTR_FUN_802c3818`, `s_Some_string_802b1234` -- every naming convention this
# corpus uses ends in the symbol's own address.
_TRAILING_ADDR = re.compile(r"_([0-9a-fA-F]{8})$")
# `zz_02650c0_` -- the link map's own style for an unnamed function: the
# leading 0x8 is implicit.
_ZZ_NAME = re.compile(r"^zz_([0-9a-fA-F]{7})_$")

REGISTRY_DEFAULT = ("research", "decomp", "data", "oracle-registry.json")


class SymbolResolver(object):
    """Candidate symbol name -> absolute GameCube address, or None.

    Sources, in order of authority:
      1. the link map -- the project's authoritative symbol table
         (`.text` only, which is all a linked DOL can offer);
      2. the address encoded in the name, accepted ONLY when it lands inside a
         DOL section or the DOL's bss range -- so an arbitrary identifier that
         happens to end in eight hex digits cannot resolve to nonsense;
      3. `research/decomp/data/oracle-registry.json`, which enumerates every
         global the Ghidra corpus references.  It carries no address of its
         own -- the names are address-encoded -- so it is used to CORROBORATE
         a name-derived address and to name an address, never to invent one.

    Anything else returns None, which the oracle turns into
    MATCH_UNVERIFIED rather than MATCH.
    """

    def __init__(self, dol, smap, repo=None, registry=None, load_registry=True):
        self.dol = dol
        self.smap = smap
        self.repo = Path(repo) if repo else REPO_DEFAULT
        self._reg_path = Path(registry) if registry else \
            self.repo.joinpath(*REGISTRY_DEFAULT)
        self._reg_names = None if load_registry else set()
        self._reg_by_addr = None if load_registry else {}
        self._cache = {}

    # -- registry ---------------------------------------------------------
    def _load_registry(self):
        if self._reg_names is not None:
            return
        names, by_addr = set(), {}
        try:
            d = json.loads(self._reg_path.read_text(encoding="utf-8-sig"))
        except Exception:
            self._reg_names, self._reg_by_addr = set(), {}
            return
        for f in d.get("functions", []):
            for g in f.get("global_refs") or []:
                s = g.get("symbol")
                if not s:
                    continue
                names.add(s)
                m = _TRAILING_ADDR.search(s)
                if m:
                    by_addr.setdefault(int(m.group(1), 16), s)
        self._reg_names, self._reg_by_addr = names, by_addr

    def registry_names(self):
        self._load_registry()
        return self._reg_names

    def name_for_address(self, addr):
        """The corpus's own name for a global, or a synthesised `DAT_` name."""
        self._load_registry()
        return self._reg_by_addr.get(addr, "DAT_%08x" % addr)

    # -- address plausibility ---------------------------------------------
    def in_image(self, addr):
        if self.dol.read(addr, 1) is not None:
            return True
        return self.dol.bss_addr <= addr < self.dol.bss_addr + self.dol.bss_size

    # -- resolution -------------------------------------------------------
    def resolve(self, name):
        """(address|None, source, note)."""
        if name in self._cache:
            return self._cache[name]
        out = self._resolve(name)
        self._cache[name] = out
        return out

    def _resolve(self, name):
        rec = self.smap.by_name.get(name)
        if rec is not None:
            return rec["addr"], "link-map", "%s section" % rec["section"]
        m = _ZZ_NAME.match(name)
        if m:
            a = 0x80000000 | int(m.group(1), 16)
            if self.in_image(a):
                return a, "name-encoded", "zz_ link-map style name"
        m = _TRAILING_ADDR.search(name)
        if m:
            a = int(m.group(1), 16)
            if self.in_image(a):
                self._load_registry()
                src = "registry+name" if name in self._reg_names \
                    else "name-encoded"
                return a, src, "address encoded in the symbol name"
            return None, None, ("'%s' encodes 0x%08x, which is in no DOL "
                                "section and not in bss" % (name, a))
        self._load_registry()
        if name in self._reg_names:
            return None, None, ("'%s' is a known corpus global but its name "
                                "encodes no address" % name)
        return None, None, ("'%s' resolves to no address: not in the link "
                            "map, no address encoded in the name" % name)

    def __call__(self, name):
        return self.resolve(name)


# ---------------------------------------------------------------------------
# the check
# ---------------------------------------------------------------------------

def _rel_name(rtype):
    from objdiff import PPC_RELOC
    return PPC_RELOC.get(rtype, ("R_PPC_%d" % rtype, 0xFFFFFFFF))[0]


def check_data_relocs(retail, base_addr, cand_relocs, retail_addrs,
                      resolver, skip_offsets=()):
    """Verify every DATA relocation the candidate carries.

    retail_addrs   {offset: (address, how)} from `retail_data_addresses`
    resolver       callable name -> (addr|None, source, note)
    skip_offsets   offsets already name-checked elsewhere (the REL24 set)

    Returns {"verified": [...], "errors": [...], "unverified": [...]}.
    `errors` is a hard MISMATCH; `unverified` downgrades MATCH to
    MATCH_UNVERIFIED.  Neither can ever upgrade a verdict.
    """
    verified, errors, unverified = [], [], []
    skip = set(skip_offsets)
    for off, rtype, name, addend in cand_relocs:
        if off in skip:
            continue
        if rtype in BENIGN_RELOC_TYPES:
            continue
        rn = _rel_name(rtype)
        if rtype not in DATA_RELOC_TYPES:
            unverified.append({
                "offset": off, "type": rn, "symbol": name,
                "reason": "relocation type %s is neither a branch this "
                          "harness resolves nor a data reference it models"
                          % rn})
            continue
        if rtype == R_ADDR32:
            want = struct.unpack_from(">I", retail, off)[0] \
                if off + 4 <= len(retail) else None
            how = "addr32-word"
        else:
            hit = retail_addrs.get(off)
            want, how = (hit if hit else (None, None))
        if want is None:
            unverified.append({
                "offset": off, "type": rn, "symbol": name,
                "reason": "the retail encoding at +0x%03x is not a data "
                          "reference this harness can reduce to an address"
                          % off})
            continue
        got, source, note = resolver(name)
        if got is None:
            unverified.append({
                "offset": off, "type": rn, "symbol": name,
                "retail_addr": "0x%08x" % want, "retail_how": how,
                "reason": note})
            continue
        got = (got + addend) & 0xFFFFFFFF
        row = {"offset": off, "type": rn, "symbol": name, "addend": addend,
               "retail_addr": "0x%08x" % want, "cand_addr": "0x%08x" % got,
               "retail_how": how, "symbol_source": source}
        if got != want:
            errors.append(dict(row, reason=(
                "the retail bytes reference 0x%08x; '%s'%s is 0x%08x"
                % (want, name, ("%+d" % addend) if addend else "", got))))
        else:
            verified.append(row)
    return {"verified": verified, "errors": errors, "unverified": unverified}


# ---------------------------------------------------------------------------
# helpers the seeder lane calls
# ---------------------------------------------------------------------------

CTYPE_FOR = {(1, True): "signed char", (1, False): "unsigned char",
             (2, True): "short", (2, False): "unsigned short",
             (4, True): "int", (4, False): "unsigned int"}


def global_symbol(dol, smap, addr, resolver=None):
    """The C identifier a candidate must use for the global at `addr`.

    Uses the corpus's own name when `oracle-registry.json` has one, so a
    matched source reads the same way the rest of the project does, and falls
    back to Ghidra's own convention otherwise.  Either way the name encodes
    the address, so `SymbolResolver` can check it.
    """
    r = resolver or SymbolResolver(dol, smap)
    return r.name_for_address(addr)


def global_decl(name, width=4, signed=True, pointer=False):
    """The `extern` declaration for a global of the given shape."""
    ty = "void *" if pointer else (CTYPE_FOR.get((width, signed), "int") + " ")
    return "extern %s%s;" % (ty, name)


# ---------------------------------------------------------------------------

def _main(argv):
    import argparse
    ap = argparse.ArgumentParser(
        description="report the SDA bases and every data reference in a "
                    "retail function")
    ap.add_argument("--repo", default=str(REPO_DEFAULT))
    ap.add_argument("--bases", action="store_true")
    ap.add_argument("function", nargs="*")
    a = ap.parse_args(argv)
    from dolsym import load, function_bytes
    dol, smap = load(repo=a.repo)
    b = sda_bases(dol, smap)
    if a.bases or not a.function:
        print("SDA BASES")
        print("  r2  (_SDA2_BASE_) = 0x%08x" % b[2])
        print("  r13 (_SDA_BASE_)  = 0x%08x" % b[13])
        for src, lines in b["evidence"].items():
            print("  evidence -- %s" % src)
            for ln in lines:
                print("    " + ln)
        if not a.function:
            return 0
    res = SymbolResolver(dol, smap, repo=a.repo)
    bo = bases_only(dol, smap)
    for fn in a.function:
        rec, retail = function_bytes(dol, smap, fn)
        if rec is None:
            print("%s: not in the link map" % fn)
            continue
        print("\n== %s @ 0x%08x" % (rec["name"], rec["addr"]))
        refs = retail_data_addresses(retail, rec["addr"], bo)
        if not refs:
            print("   no data references")
        for off in sorted(refs):
            addr, how = refs[off]
            print("   +0x%03x  %-8s -> 0x%08x  %s"
                  % (off, how, addr, res.name_for_address(addr)))
    return 0


if __name__ == "__main__":
    sys.exit(_main(sys.argv[1:]))
