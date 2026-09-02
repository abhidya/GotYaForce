#!/usr/bin/env python3
"""undecoded_probe.py -- explain the words capstone's PPC32 decoder rejects.

capstone knows generic PowerPC, NOT the GameCube's Gekko extensions.  Every
paired-single instruction therefore lands in the <undecoded> bucket, alongside
genuine data-in-text (jump tables, string literals, relocation stubs).  This
tool splits that bucket by PRIMARY OPCODE so the paired-single count -- the
single most load-bearing number in the static-recompilation go/no-go -- is
measured rather than assumed.

Gekko paired-single encodings (Broadway/Gekko user manual, and Dolphin's
Source/Core/Core/PowerPC/Interpreter/Interpreter_Paired.cpp):

    op 4   ps_* arithmetic + psq_lx/psq_stx family (extended opcode in bits)
    op 56  psq_l      op 57  psq_lu
    op 60  psq_st     op 61  psq_stu

Anything else in the bucket is reported by opcode so it can be inspected.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
from pathlib import Path

from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN

from dol_inventory import Dol

PS_PRIMARY = {4: "op4 (ps_* arith / psq_?x)", 56: "psq_l", 57: "psq_lu",
              60: "psq_st", 61: "psq_stu"}

# op-4 extended opcodes, from the Gekko manual.  Bits 26..30 for the
# load/store-indexed forms, bits 21..30 (XO) for the arithmetic forms.
OP4_XO5 = {
    0: None,          # falls through to the 10-bit table
    6: "psq_lx", 7: "psq_lux", 38: "psq_stx", 39: "psq_stux",
    10: "ps_sum0", 11: "ps_sum1", 12: "ps_muls0", 13: "ps_muls1",
    14: "ps_madds0", 15: "ps_madds1", 18: "ps_div", 20: "ps_sub",
    21: "ps_add", 23: "ps_sel", 24: "ps_res", 25: "ps_mul",
    26: "ps_rsqrte", 28: "ps_msub", 29: "ps_madd", 30: "ps_nmsub",
    31: "ps_nmadd",
}
OP4_XO10 = {
    0: "ps_cmpu0", 32: "ps_cmpo0", 40: "ps_neg", 64: "ps_cmpu1",
    72: "ps_mr", 96: "ps_cmpo1", 136: "ps_nabs", 264: "ps_abs",
    528: "ps_merge00", 560: "ps_merge01", 592: "ps_merge10",
    624: "ps_merge11", 1014: "dcbz_l",
}


def name_op4(w):
    xo5 = (w >> 1) & 0x1F
    if xo5 in OP4_XO5 and OP4_XO5[xo5]:
        return OP4_XO5[xo5]
    xo10 = (w >> 1) & 0x3FF
    return OP4_XO10.get(xo10, "op4.xo=%d" % xo10)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True

    by_primary = collections.Counter()
    ps_names = collections.Counter()
    other_examples = collections.defaultdict(list)
    zero_words = 0
    total_undec = 0

    for off, addr, size in dol.text:
        blob = dol.blob[off:off + size]
        for i in range(0, size - 3, 4):
            wb = blob[i:i + 4]
            got = list(md.disasm(wb, addr + i, count=1))
            if got and got[0].mnemonic not in (".byte", ".long", ""):
                continue
            total_undec += 1
            w = struct.unpack(">I", wb)[0]
            if w == 0:
                zero_words += 1
            op = w >> 26
            by_primary[op] += 1
            if op in PS_PRIMARY:
                ps_names[name_op4(w) if op == 4 else PS_PRIMARY[op]] += 1
            elif len(other_examples[op]) < 8:
                other_examples[op].append(
                    {"addr": "0x%08x" % (addr + i), "word": "0x%08x" % w})

    ps_total = sum(n for op, n in by_primary.items() if op in PS_PRIMARY)
    # dcbz_l is an op-4 Gekko cache op, not SIMD -- count it out of the SIMD tally
    dcbz_l = ps_names.get("dcbz_l", 0)

    out = {
        "schema": 1,
        "undecoded_words": total_undec,
        "all_zero_words": zero_words,
        "by_primary_opcode": {str(k): v for k, v in
                              sorted(by_primary.items(), key=lambda kv: -kv[1])},
        "paired_single_total": ps_total - dcbz_l,
        "gekko_op4_total_including_dcbz_l": ps_total,
        "dcbz_l": dcbz_l,
        "paired_single_by_mnemonic": dict(ps_names.most_common()),
        "non_gekko_undecoded": total_undec - ps_total,
        "non_gekko_examples": {str(k): v for k, v in other_examples.items()},
    }
    Path(a.out).write_text(json.dumps(out, indent=2))

    print("undecoded words: %d  (all-zero: %d)" % (total_undec, zero_words))
    print("")
    print("by primary opcode:")
    for op, n in sorted(by_primary.items(), key=lambda kv: -kv[1])[:20]:
        tag = PS_PRIMARY.get(op, "")
        print("  op %3d  %8d  %s" % (op, n, tag))
    print("")
    print("PAIRED SINGLE total (excl. dcbz_l): %d" % (ps_total - dcbz_l))
    print("dcbz_l: %d" % dcbz_l)
    for m, n in ps_names.most_common():
        print("    %-14s %7d" % (m, n))
    print("")
    print("non-Gekko undecoded (data-in-text / bad walk): %d"
          % (total_undec - ps_total))


if __name__ == "__main__":
    main()
