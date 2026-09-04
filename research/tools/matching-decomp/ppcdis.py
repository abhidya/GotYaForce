#!/usr/bin/env python3
"""ppcdis.py -- PowerPC / Gekko disassembly for the matching harness.

capstone 5.0.1 in CS_MODE_32|CS_MODE_BIG_ENDIAN is WRONG about this CPU in two
documented ways (see docs/static-recompilation-spike.md §1.2):

  * primary opcodes 4 / 56 / 57 / 60 / 61 are AltiVec/VSX on a 64-bit POWER core
    but are the Gekko PAIRED-SINGLE unit -- capstone renders psq_st as `xxsel`;
  * `fcmpo` (primary 63, XO 32) is rejected outright.

For a matching harness the byte comparison is authoritative and the mnemonic is
only for the human and the LLM to read, but a disassembly that LIES about the
instruction is worse than none -- it would put `xxsel` into an LLM prompt.  So
capstone is used as a renderer and every Gekko-affected primary opcode is
overridden here.

Nothing in this module decides a match.
"""
from __future__ import annotations

import struct

try:
    import capstone
    _CS = capstone.Cs(capstone.CS_ARCH_PPC,
                      capstone.CS_MODE_32 | capstone.CS_MODE_BIG_ENDIAN)
    _CS.detail = False
except Exception:  # pragma: no cover
    _CS = None

GEKKO_PRIMARY = (4, 56, 57, 60, 61)

# Gekko paired-single: primary opcode -> mnemonic (D-form) or XO table.
PS_DFORM = {56: "psq_l", 57: "psq_lu", 60: "psq_st", 61: "psq_stu"}

PS_XO5 = {  # primary 4, bits 26..30 (A-form)
    10: "ps_sum0", 11: "ps_sum1", 12: "ps_muls0", 13: "ps_muls1",
    14: "ps_madds0", 15: "ps_madds1", 18: "ps_div", 20: "ps_sub",
    21: "ps_add", 23: "ps_sel", 24: "ps_res", 25: "ps_mul",
    26: "ps_rsqrte", 28: "ps_msub", 29: "ps_madd", 30: "ps_nmsub",
    31: "ps_nmadd",
}
PS_XO10 = {  # primary 4, bits 21..30 (X-form)
    40: "ps_neg", 72: "ps_mr", 136: "ps_nabs", 264: "ps_abs",
    0: "ps_cmpu0", 32: "ps_cmpo0", 64: "ps_cmpu1", 96: "ps_cmpo1",
    528: "ps_merge00", 560: "ps_merge01", 592: "ps_merge10", 624: "ps_merge11",
    1014: "dcbz_l",
    6: "psq_lx", 7: "psq_lux", 38: "psq_stx", 39: "psq_stux",
}

FLOAT63_XO10 = {32: "fcmpo", 0: "fcmpu"}


def _gekko(word, addr):
    op = word >> 26
    if op in PS_DFORM:
        rd = (word >> 21) & 31
        ra = (word >> 16) & 31
        i = (word >> 12) & 7
        w = (word >> 15) & 1
        d = word & 0xFFF
        if d & 0x800:
            d -= 0x1000
        return "%s f%d, %d(r%d), %d, %d" % (PS_DFORM[op], rd, d, ra, w, i)
    if op == 4:
        xo10 = (word >> 1) & 0x3FF
        if xo10 in PS_XO10:
            return "%s f%d, f%d, f%d" % (PS_XO10[xo10], (word >> 21) & 31,
                                         (word >> 16) & 31, (word >> 11) & 31)
        xo5 = (word >> 1) & 0x1F
        if xo5 in PS_XO5:
            return "%s f%d, f%d, f%d, f%d" % (
                PS_XO5[xo5], (word >> 21) & 31, (word >> 16) & 31,
                (word >> 6) & 31, (word >> 11) & 31)
        return ".4byte 0x%08x /* gekko primary 4, xo %d */" % (word, xo10)
    return None


def disasm_word(word, addr):
    op = word >> 26
    if op in GEKKO_PRIMARY:
        s = _gekko(word, addr)
        if s:
            return s
    if op == 63:
        xo10 = (word >> 1) & 0x3FF
        if xo10 in FLOAT63_XO10:
            return "%s cr%d, f%d, f%d" % (FLOAT63_XO10[xo10], (word >> 23) & 7,
                                          (word >> 16) & 31, (word >> 11) & 31)
    if word == 0x60000000:
        return "nop"
    if _CS is not None:
        b = struct.pack(">I", word)
        for ins in _CS.disasm(b, addr):
            m = ins.mnemonic
            o = ins.op_str
            return (m + " " + o).strip()
    return ".4byte 0x%08x" % word


def disasm(blob, addr):
    """[(addr, word, text)] for a big-endian PPC byte blob."""
    out = []
    n = len(blob) // 4
    for i, w in enumerate(struct.unpack(">%dI" % n, blob[:n * 4])):
        out.append((addr + i * 4, w, disasm_word(w, addr + i * 4)))
    return out


def render(blob, addr, prefix=""):
    return "\n".join("%s%08x  %08x  %s" % (prefix, a, w, t)
                     for a, w, t in disasm(blob, addr))


if __name__ == "__main__":
    import sys
    from pathlib import Path
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from dolsym import load, function_bytes
    d, s = load()
    for name in sys.argv[1:]:
        rec, b = function_bytes(d, s, name)
        if rec is None:
            print("%s: not in map" % name)
            continue
        print("== %s @ 0x%08x  %d B ==" % (rec["name"], rec["addr"], rec["size"]))
        print(render(b, rec["addr"]))
        print()
