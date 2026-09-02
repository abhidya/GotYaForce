#!/usr/bin/env python3
"""compare_transcript.py -- decide a `transcript_green` replay of a statically
recompiled function against a console capture.

Same verdict rules as research/decomp/oracle-harness/run-transcript.mjs: the
port must make the same calls, in the same order, to the same callees, with the
same argument values; a case that observes nothing is vacuous and is reported
rather than counted.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path


def val_eq(e, a):
    if isinstance(e, str):                    # i64, carried as a decimal string
        return str(e) == str(a)
    if isinstance(e, float) or isinstance(a, float):
        return float(e) == float(a)
    return int(e) == int(a)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--capture", required=True)
    ap.add_argument("--module", required=True)
    ap.add_argument("--node", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    lines = Path(a.capture).read_text().splitlines()
    header = json.loads(lines[0])
    cases = [json.loads(l) for l in lines[1:]
             if l.strip() and json.loads(l)["kind"] == "case"]

    r = subprocess.run([a.node, a.module], capture_output=True, text=True)
    if r.returncode != 0:
        raise SystemExit("module exited %d\n%s" % (r.returncode, r.stderr[-3000:]))
    got, cur = [], None
    for line in r.stdout.splitlines():
        line = line.strip()
        if not line.startswith("{"):
            continue
        e = json.loads(line)
        if e["k"] == "case":
            cur = {"n": e["n"], "calls": []}
        elif e["k"] == "case_end":
            got.append(cur); cur = None
        else:
            cur["calls"].append(e)

    divergence, matched_cases, matched_calls, vacuous = None, 0, 0, []
    for exp, act in zip(cases, got):
        if not exp["calls"] and exp.get("ret") is None:
            vacuous.append(exp["n"])
        if len(exp["calls"]) != len(act["calls"]):
            divergence = {"n": exp["n"], "kind": "call_count",
                          "report": "case %d: console made %d call(s), port made %d"
                                    % (exp["n"], len(exp["calls"]), len(act["calls"]))}
            break
        bad = False
        for i, (ec, ac) in enumerate(zip(exp["calls"], act["calls"])):
            if ec["callee"] != ac["callee"]:
                divergence = {"n": exp["n"], "i": i, "kind": "callee",
                              "report": "case %d call %d: console %s, port %s"
                                        % (exp["n"], i, ec["callee"], ac["callee"])}
                bad = True; break
            if len(ec["args"]) != len(ac["args"]):
                divergence = {"n": exp["n"], "i": i, "kind": "arity",
                              "report": "case %d call %d (%s): console %d arg(s), port %d"
                                        % (exp["n"], i, ec["callee"],
                                           len(ec["args"]), len(ac["args"]))}
                bad = True; break
            for j, (e, v) in enumerate(zip(ec["args"], ac["args"])):
                if not val_eq(e, v):
                    divergence = {"n": exp["n"], "i": i, "kind": "args",
                                  "report": "case %d call %d (%s) arg %d: console %r, "
                                            "port %r" % (exp["n"], i, ec["callee"],
                                                         j, e, v)}
                    bad = True; break
            if bad:
                break
            matched_calls += 1
        if bad:
            break
        matched_cases += 1

    if divergence is None and len(cases) != len(got):
        divergence = {"kind": "case_count",
                      "report": "console recorded %d case(s), port produced %d"
                                % (len(cases), len(got))}

    verdict = "pass" if divergence is None else "fail"
    res = {
        "result_schema": 1,
        "standard": "transcript_green",
        "standard_note": ("transcript_green is STRICTLY WEAKER than oracle_green: it "
                          "compares the observable call transcript and the return "
                          "value, not the function's memory write set."),
        "route": "static_recompilation",
        "route_note": (
            "The module under test was produced by research/tools/static-recomp/"
            "ppc_recomp.py from boot.dol: one C statement per PowerPC instruction "
            "word, emitted by table lookup. No decompiler output, no inferred "
            "signature, no hand-authored spec, no human review."),
        "fn": header["fn"]["export"],
        "gc_addr": header["fn"]["gc_addr"],
        "capture": {"file": a.capture, "cases": len(cases),
                    "counts": header["counts"]},
        "port_module": a.module,
        "cases_passed": matched_cases,
        "calls_matched": matched_calls,
        "vacuous_cases": vacuous,
        "divergence": divergence,
        "verdict": verdict,
        "does_not_verify": [
            "the function's memory WRITE SET -- this standard compares the callee "
            "boundary, not writes.",
            "out-of-unit callee behaviour: the callee is stubbed and its recorded "
            "memory delta is replayed, exactly as run-transcript.mjs does.",
            "any input outside the 24 recorded cases.",
        ],
    }
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(json.dumps(res, indent=2))
    print("verdict: %s   cases %d/%d   calls %d/%d"
          % (verdict, matched_cases, len(cases), matched_calls,
             header["counts"]["call"]))
    if divergence:
        print("divergence:", divergence["report"])
    return 0 if verdict == "pass" else 1


if __name__ == "__main__":
    sys.exit(main())
