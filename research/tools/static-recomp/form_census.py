#!/usr/bin/env python3
"""form_census.py -- how big does the translation table actually have to be?

The mnemonic histogram over-counts, because a disassembler prints `li`, `mr`,
`slwi`, `clrlwi`, `nop` and `rotlwi` as separate mnemonics for what are three
ENCODING FORMS (addi, or, rlwinm).  A recompiler's table is keyed on the
encoding, not the printed name, so the encoding-form census is the honest answer
to "how many instructions must a full recompiler cover".

It also reports where the hard classes LIVE: an instruction that only appears
inside the OS boot path is not on a high-level-hosted port's critical path.
"""
from __future__ import annotations

import argparse
import collections
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from dol_inventory import Dol, gekko_override, gekko_fallback, classify  # noqa: E402

from capstone import Cs, CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN  # noqa: E402


def form_key(w):
    op = w >> 26
    if op in (4, 56, 57, 60, 61):
        return "gekko/%s" % (gekko_fallback(w) or "op%d" % op)
    if op in (19, 31):
        return "%d/%d" % (op, (w >> 1) & 0x3FF)
    if op in (59, 63):
        x5 = (w >> 1) & 0x1F
        if x5 in (18, 20, 21, 22, 23, 24, 25, 26, 28, 29, 30, 31):
            return "%d/A%d" % (op, x5)
        return "%d/%d" % (op, (w >> 1) & 0x3FF)
    return str(op)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    dol = Dol.from_iso(Path(a.iso))
    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
    md.skipdata = True

    forms = collections.Counter()
    form_name = {}
    # .init is text section 0; a high-level-hosted port never runs the OS boot
    init_lo, init_hi = dol.text[0][1], dol.text[0][1] + dol.text[0][2]
    hard_where = collections.Counter()
    total = 0
    for off, ad, sz in dol.text:
        blob = dol.blob[off:off + sz]
        for i in range(0, sz - 3, 4):
            w = struct.unpack(">I", blob[i:i + 4])[0]
            if w == 0:
                continue
            total += 1
            k = form_key(w)
            forms[k] += 1
            if k not in form_name:
                ovr = gekko_override(w)
                if ovr:
                    form_name[k] = ovr
                else:
                    g = list(md.disasm(blob[i:i + 4], ad + i, count=1))
                    form_name[k] = (g[0].mnemonic if g and g[0].mnemonic
                                    not in (".byte", ".long", "")
                                    else (gekko_fallback(w) or "?"))
            cls = classify(form_name[k])
            if cls in ("PAIRED_SINGLE", "FP_NONIEEE", "SUPERVISOR", "SYSCALL"):
                where = "init/OS boot" if init_lo <= ad + i < init_hi else "main text"
                hard_where["%s @ %s" % (cls, where)] += 1

    run, marks, mi = 0, [0.90, 0.99, 0.999, 0.9999, 1.0], 0
    curve = {}
    for i, (k, n) in enumerate(forms.most_common(), 1):
        run += n
        while mi < len(marks) and run / float(total) >= marks[mi]:
            curve["%.4g%%" % (marks[mi] * 100)] = i
            mi += 1

    res = {
        "instructions": total,
        "distinct_encoding_forms": len(forms),
        "forms_needed_for_coverage": curve,
        "hard_class_location": dict(hard_where.most_common()),
        "form_histogram": [{"form": k, "name": form_name[k], "count": n,
                            "class": classify(form_name[k])}
                           for k, n in forms.most_common()],
    }
    Path(a.out).write_text(json.dumps(res, indent=2))
    print("instructions (excl. zero padding): %d" % total)
    print("DISTINCT ENCODING FORMS: %d" % len(forms))
    print("forms needed for coverage:", curve)
    print("hard classes by location:")
    for k, v in hard_where.most_common():
        print("   %-32s %6d" % (k, v))


if __name__ == "__main__":
    main()
