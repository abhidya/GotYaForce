#!/usr/bin/env python3
"""op63_probe.py -- break the op-63 residue out of the undecoded bucket.

Primary opcode 63 is the double-precision floating-point extended-opcode space.
capstone's PPC32 decoder rejects some of it; this tool reports the extended
opcode (XO, bits 21..30) distribution so each rejected form can be named against
the PowerPC 750CL / Gekko manual rather than guessed at.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
from pathlib import Path

from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN

from dol_inventory import Dol

# XO (bits 21..30) for primary opcode 63, PowerPC 750CL.
XO63 = {
    0: "fcmpu", 12: "frsp", 14: "fctiw", 15: "fctiwz", 32: "fcmpo",
    38: "mtfsb1", 40: "fneg", 64: "mcrfs", 70: "mtfsb0", 72: "fmr",
    134: "mtfsfi", 136: "fnabs", 264: "fabs", 583: "mffs", 711: "mtfsf",
    # A-form (XO in bits 26..30) handled separately
}
XO63_A = {
    18: "fdiv", 20: "fsub", 21: "fadd", 22: "fsqrt", 23: "fsel",
    25: "fmul", 26: "frsqrte", 28: "fmsub", 29: "fmadd", 30: "fnmsub",
    31: "fnmadd",
}


def name63(w):
    xo5 = (w >> 1) & 0x1F
    if xo5 in XO63_A:
        return XO63_A[xo5]
    xo10 = (w >> 1) & 0x3FF
    return XO63.get(xo10, "op63.xo=%d" % xo10)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True

    names = collections.Counter()
    op0 = collections.Counter()
    for off, addr, size in dol.text:
        blob = dol.blob[off:off + size]
        for i in range(0, size - 3, 4):
            wb = blob[i:i + 4]
            got = list(md.disasm(wb, addr + i, count=1))
            if got and got[0].mnemonic not in (".byte", ".long", ""):
                continue
            w = struct.unpack(">I", wb)[0]
            if w >> 26 == 63:
                names[name63(w)] += 1
            elif w >> 26 == 0:
                op0["0x%08x" % w] += 1

    out = {"op63_undecoded_by_form": dict(names.most_common()),
           "op0_undecoded_words": dict(op0.most_common(12))}
    Path(a.out).write_text(json.dumps(out, indent=2))
    print("op-63 words capstone rejected, named by XO:")
    for m, n in names.most_common():
        print("  %-16s %7d" % (m, n))
    print("")
    print("op-0 words (padding / data-in-text):")
    for m, n in op0.most_common(10):
        print("  %-12s %7d" % (m, n))


if __name__ == "__main__":
    main()
