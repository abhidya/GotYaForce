#!/usr/bin/env python3
"""batch_recomp.py -- run the spike translator over EVERY function in the
corpus and report exactly what it can and cannot translate.

This is the honest-cost measurement.  The go/no-go instruction histogram says
what is IN the DOL; this says what the translator, as written, would emit today
and what would stop it, function by function, reason by reason.

It does not compile anything.  It translates in memory and counts.

Function boundaries come from the project's own registry
(research/decomp/data/oracle-registry.json, 10,954 functions) plus the 1,018
excluded entries, capped at the next entry point so a tail branch cannot run the
walk into the following function.
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
    secs = dol.text

    def word(addr):
        for off, ad, sz in secs:
            if ad <= addr < ad + sz:
                return struct.unpack(">I",
                                     dol.blob[off + (addr - ad):off + (addr - ad) + 4])[0]
        return None

    reg = json.loads(Path(a.registry).read_text())
    addrs = set()
    fns = reg["functions"]
    for f in (fns.values() if isinstance(fns, dict) else fns):
        addrs.add(int(f["address"], 16))
    for e in reg["excluded"]:
        if isinstance(e, dict) and e.get("address"):
            addrs.add(int(e["address"], 16))
    entries = sorted(addrs)
    nxt = {entries[i]: entries[i + 1] for i in range(len(entries) - 1)}
    text_end = max(ad + sz for _, ad, sz in secs)
    nxt[entries[-1]] = text_end

    ok = 0
    failed = collections.Counter()
    fail_examples = collections.defaultdict(list)
    forms_used = collections.Counter()
    ok_instructions = 0
    failed_instructions = 0
    failed_fns = []
    unmapped = 0

    for e in entries:
        limit = min(nxt[e] - e, 0x8000)
        if word(e) is None:
            unmapped += 1
            continue
        try:
            lo, hi = R.function_extent(word, e, limit=limit)
        except Exception as ex:
            failed["extent: %s" % str(ex).split("--")[-1].strip()] += 1
            continue
        n = (hi - lo) // 4
        bad = None
        counted = collections.Counter()
        for addr in range(lo, hi, 4):
            w = word(addr)
            if w is None:
                bad = "walk left mapped ROM"
                break
            try:
                R.translate(addr, w, lo, hi)
                counted[form_key(w)] += 1
            except R.Unsupported as ex:
                bad = ex.why
                break
            except Exception as ex:                     # generator bug, not ROM
                bad = "generator error: %s" % ex
                break
        if bad is None:
            ok += 1
            ok_instructions += n
            forms_used.update(counted)
        else:
            key = normalise(bad)
            failed[key] += 1
            failed_instructions += n
            failed_fns.append("0x%08x" % e)
            if len(fail_examples[key]) < 6:
                fail_examples[key].append("0x%08x" % e)

    total = len(entries) - unmapped
    res = {
        "schema": 1,
        "entry_points": len(entries),
        "entry_points_in_text": total,
        "entry_points_outside_text": unmapped,
        "translated_whole": ok,
        "translated_whole_share": round(ok / float(total), 4),
        "translated_instructions": ok_instructions,
        "blocked_functions": sum(failed.values()),
        "blocked_instructions_in_those_functions": failed_instructions,
        "blocking_reasons": dict(failed.most_common()),
        "blocking_examples": {k: v for k, v in fail_examples.items()},
        "encoding_forms_emitted": len(forms_used),
        "encoding_form_histogram": dict(forms_used.most_common()),
    }
    Path(a.out).write_text(json.dumps(res, indent=2))
    print("entry points: %d (in text: %d)" % (len(entries), total))
    print("translated whole, no human input: %d (%.1f%%), %d instructions"
          % (ok, 100.0 * ok / total, ok_instructions))
    print("blocked: %d functions" % sum(failed.values()))
    print("")
    print("blocking reasons:")
    for k, v in failed.most_common(25):
        print("  %6d  %s   e.g. %s" % (v, k, ", ".join(fail_examples[k][:3])))
    print("")
    print("distinct ENCODING FORMS the translator emitted: %d" % len(forms_used))


def form_key(w):
    op = R.OP(w)
    if op == 31:
        return "31/%d" % R.XO10(w)
    if op == 19:
        return "19/%d" % R.XO10(w)
    if op in (59, 63):
        x5 = R.XO5(w)
        if x5 in R.A_FORM:
            return "%d/A%d" % (op, x5)
        return "%d/%d" % (op, R.XO10(w))
    return str(op)


def normalise(why):
    for tok in ("XO=", "SPR ", "primary opcode ", "op "):
        if tok in why:
            return why
    return why


if __name__ == "__main__":
    main()
