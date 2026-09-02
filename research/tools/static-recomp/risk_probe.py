#!/usr/bin/env python3
"""risk_probe.py -- measure the four things that actually kill static
recompilers, on THIS ROM, rather than in general.

  1. INDIRECT CONTROL FLOW.  bctr/bctrl/blrl counts, and for each `bctr` the
     shape of the instructions that loaded CTR -- a compiler switch table
     (bounds check + lwzx from a constant table in .data) is a different problem
     from a genuine function pointer.  Both are handled by an entry-point jump
     table, but only if the targets are all real function entries, which is
     checkable: every switch-table word and every function-pointer word in the
     data sections either is an address in text or it is not.

  2. SELF-MODIFYING / DVD-OVERLAID CODE.  Instruction-cache invalidations
     (`icbi`) are the only way PowerPC code can legally be written at runtime.
     Their count and their call graph position says whether this game does it.

  3. PAIRED SINGLE concentration -- how many distinct functions a Gekko SIMD
     model unblocks, deduplicated over overlapping function extents.

  4. NON-ENTRY-POINT BRANCH TARGETS in the data sections: how many 32-bit words
     in .data point at an address inside .text, and how many of those are known
     function entries.  A recompiler's jump table must cover all of them.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from dol_inventory import Dol  # noqa: E402
import ppc_recomp as R  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--registry", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    dol = Dol.from_iso(Path(a.iso))
    text, data = dol.text, dol.data

    def tword(addr):
        for off, ad, sz in text:
            if ad <= addr < ad + sz:
                return struct.unpack(">I",
                                     dol.blob[off + (addr - ad):off + (addr - ad) + 4])[0]
        return None

    reg = json.loads(Path(a.registry).read_text())
    fns = reg["functions"]
    entries = set(int(f["address"], 16)
                  for f in (fns.values() if isinstance(fns, dict) else fns))
    for e in reg["excluded"]:
        if isinstance(e, dict) and e.get("address"):
            entries.add(int(e["address"], 16))

    # ---- 1. indirect control flow ---------------------------------------
    bctr, bctrl, blrl = [], [], []
    icbi, dcbst = [], []
    for off, ad, sz in text:
        blob = dol.blob[off:off + sz]
        for i in range(0, sz - 3, 4):
            w = struct.unpack(">I", blob[i:i + 4])[0]
            addr = ad + i
            if (w >> 26) == 19:
                xo, lk = R.XO10(w), R.LK(w)
                if xo == 528:
                    (bctrl if lk else bctr).append(addr)
                elif xo == 16 and lk:
                    blrl.append(addr)
            elif (w >> 26) == 31:
                if R.XO10(w) == 982:
                    icbi.append(addr)
                elif R.XO10(w) == 54:
                    dcbst.append(addr)

    # for each bctr, look back 12 instructions for the CTR source shape
    shapes = collections.Counter()
    for addr in bctr:
        shape = "unclassified"
        for k in range(1, 13):
            w = tword(addr - 4 * k)
            if w is None:
                break
            if (w >> 26) == 31 and R.XO10(w) == 467 and R.SPRN(w) == 9:   # mtctr
                # what fed the register mtctr read?
                src = R.RS(w)
                for j in range(k + 1, k + 8):
                    v = tword(addr - 4 * j)
                    if v is None:
                        break
                    if (v >> 26) == 31 and R.XO10(v) == 23 and R.RD(v) == src:
                        shape = "switch table (lwzx from an indexed table)"
                        break
                    if (v >> 26) == 32 and R.RD(v) == src:
                        shape = "loaded function pointer (lwz)"
                        break
                else:
                    shape = "mtctr from a computed register"
                break
        shapes[shape] += 1

    # ---- 4. code pointers in the data sections --------------------------
    text_lo = min(ad for _, ad, _ in text)
    text_hi = max(ad + sz for _, ad, sz in text)
    ptr_in_text = 0
    ptr_is_entry = 0
    ptr_not_entry = collections.Counter()
    for off, ad, sz in data:
        blob = dol.blob[off:off + sz]
        for i in range(0, sz - 3, 4):
            v = struct.unpack(">I", blob[i:i + 4])[0]
            if text_lo <= v < text_hi and (v & 3) == 0:
                ptr_in_text += 1
                if v in entries:
                    ptr_is_entry += 1
                else:
                    ptr_not_entry["0x%08x" % v] += 1

    # ---- 3. paired-single concentration, deduplicated --------------------
    ps_addrs = set()
    for off, ad, sz in text:
        blob = dol.blob[off:off + sz]
        for i in range(0, sz - 3, 4):
            w = struct.unpack(">I", blob[i:i + 4])[0]
            if (w >> 26) in (4, 56, 57, 60, 61):
                ps_addrs.add(ad + i)
    sorted_entries = sorted(entries)
    nxt = {sorted_entries[i]: sorted_entries[i + 1]
           for i in range(len(sorted_entries) - 1)}
    nxt[sorted_entries[-1]] = text_hi
    ps_fns = set()
    for e in sorted_entries:
        for x in ps_addrs:
            if e <= x < nxt[e]:
                ps_fns.add(e)
                break

    res = {
        "indirect_control_flow": {
            "bctr": len(bctr), "bctrl": len(bctrl), "blrl": len(blrl),
            "bctr_ctr_source_shapes": dict(shapes.most_common()),
        },
        "code_pointers_in_data_sections": {
            "words_pointing_into_text": ptr_in_text,
            "of_those_a_known_function_entry": ptr_is_entry,
            "of_those_NOT_a_known_entry": ptr_in_text - ptr_is_entry,
            "distinct_non_entry_targets": len(ptr_not_entry),
            "top_non_entry_targets": dict(ptr_not_entry.most_common(10)),
        },
        "self_modifying_code_signals": {
            "icbi_sites": ["0x%08x" % x for x in icbi],
            "dcbst_sites": ["0x%08x" % x for x in dcbst],
            "note": ("icbi is the only legal way to run code written at runtime "
                     "on PowerPC. A handful of sites inside the SDK's cache "
                     "library is the OS's own ICInvalidateRange, not an overlay "
                     "loader."),
        },
        "paired_single": {
            "instructions": len(ps_addrs),
            "functions_containing_at_least_one": len(ps_fns),
            "share_of_corpus_functions": round(len(ps_fns) / float(len(entries)), 4),
        },
    }
    Path(a.out).write_text(json.dumps(res, indent=2))
    print(json.dumps(res, indent=2)[:4000])


if __name__ == "__main__":
    main()
