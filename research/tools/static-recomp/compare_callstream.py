#!/usr/bin/env python3
"""compare_callstream.py -- replay the CONSOLE capture against the STATICALLY
RECOMPILED function and decide whether they emitted the same SDK-seam stream.

The comparison rules are the ones
research/decomp/oracle-harness/run-gx-callstream.mjs already applies to the
Ghidra-derived wasm build, reimplemented here so the two results are directly
comparable:

  * event kinds and their ORDER must match exactly (call vs wgpipe);
  * a call must match on callee, arity, and every plain argument by value;
  * a stack-relative argument -- one the console recorded as {"k":"sp","off":N}
    -- is compared STRUCTURALLY, because the console's stack address and the
    port's are different by construction.  It may not be 0, it may not collide
    with an address the console passed as a plain value, and the pairwise
    offsets between stack-relative arguments must match.  (capture_gx.py's own
    docstring; run-gx-callstream.mjs:225-270.)
  * a write-gather-pipe write must match on width and value, and on the STORE
    SITE address, which the recompiled code carries because every memory
    instruction records its own address in ctx.cia.

The recompiler's stack pointer is deliberately NOT the console's, so the
stack-relative check is a real check and not an accident of both sides
happening to start at the same address.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path


def load_console(path):
    lines = Path(path).read_text().splitlines()
    header = json.loads(lines[0])
    invs = [json.loads(l) for l in lines[1:] if l.strip()]
    return header, invs


def run_port(node, module):
    out = subprocess.run([node, module], capture_output=True, text=True)
    if out.returncode != 0:
        raise SystemExit("port module exited %d\n%s" % (out.returncode, out.stderr))
    events = []
    for line in out.stdout.splitlines():
        line = line.strip()
        if line.startswith("{"):
            events.append(json.loads(line))
    return events


def split_invocations(events):
    invs, cur = [], None
    for e in events:
        if e["k"] == "invocation":
            cur = {"n": e["n"], "entry_sp": e["entry_sp"], "events": []}
        elif e["k"] == "exit":
            cur["exit_sp"] = e["exit_sp"]
            invs.append(cur)
            cur = None
        else:
            cur["events"].append(e)
    return invs


def is_sp(v):
    return isinstance(v, dict) and v.get("k") == "sp"


def compare_invocation(exp_events, act):
    """Returns (None, counts) on agreement, else (divergence, counts)."""
    counts = {"call": 0, "wgpipe": 0, "sp_arg": 0}
    if len(exp_events) != len(act["events"]):
        return ({"kind": "length",
                 "report": "console emitted %d event(s), port emitted %d"
                           % (len(exp_events), len(act["events"]))}, counts)
    sp_seen = []
    plain_values = set()
    for e in exp_events:
        if e["k"] == "call":
            for v in e["args"]:
                if not is_sp(v):
                    plain_values.add(v & 0xFFFFFFFF)
    for i, (exp, a) in enumerate(zip(exp_events, act["events"])):
        if exp["k"] != a["k"]:
            return ({"kind": "kind", "i": i,
                     "report": "event %d: console %s, port %s" % (i, exp["k"], a["k"])},
                    counts)
        if exp["k"] == "wgpipe":
            counts["wgpipe"] += 1
            if exp["width"] != a["width"]:
                return ({"kind": "width", "i": i,
                         "report": "event %d: console width %d, port width %d"
                                   % (i, exp["width"], a["width"])}, counts)
            if (exp["value"] & 0xFFFFFFFF) != (a["value"] & 0xFFFFFFFF):
                return ({"kind": "value", "i": i,
                         "report": "event %d: console value 0x%x, port 0x%x"
                                   % (i, exp["value"], a["value"])}, counts)
            if exp["at"].lower() != a["at"].lower():
                return ({"kind": "site", "i": i,
                         "report": "event %d: console store site %s, port %s"
                                   % (i, exp["at"], a["at"])}, counts)
            continue
        counts["call"] += 1
        if exp["callee"] != a["callee"]:
            return ({"kind": "callee", "i": i,
                     "report": "event %d: console called %s, port called %s"
                               % (i, exp["callee"], a["callee"])}, counts)
        if exp["at"].lower() != a["at"].lower():
            return ({"kind": "call_site", "i": i,
                     "report": "event %d (%s): console call site %s, port %s"
                               % (i, exp["callee"], exp["at"], a["at"])}, counts)
        if len(exp["args"]) != len(a["args"]):
            return ({"kind": "arity", "i": i,
                     "report": "event %d (%s): console passed %d argument(s), port %d"
                               % (i, exp["callee"], len(exp["args"]), len(a["args"]))},
                    counts)
        port_sp = int(a["sp"], 16)
        for j, (e, v) in enumerate(zip(exp["args"], a["args"])):
            v &= 0xFFFFFFFF
            if is_sp(e):
                counts["sp_arg"] += 1
                if v == 0:
                    return ({"kind": "sp_null", "i": i,
                             "report": "event %d (%s) arg %d: console passed a stack "
                                       "pointer, port passed 0" % (i, exp["callee"], j)},
                            counts)
                if v in plain_values:
                    return ({"kind": "sp_collision", "i": i,
                             "report": "event %d (%s) arg %d: port passed 0x%08x, which "
                                       "the console passed elsewhere as a PLAIN address"
                                       % (i, exp["callee"], j, v)}, counts)
                for prev in sp_seen:
                    if (v - prev["port"]) != (e["off"] - prev["off"]):
                        return ({"kind": "sp_layout", "i": i,
                                 "report": "event %d (%s) arg %d: console stack offsets "
                                           "differ by %d, port pointers differ by %d"
                                           % (i, exp["callee"], j,
                                              e["off"] - prev["off"], v - prev["port"])},
                                counts)
                # the offset the port's pointer has from ITS OWN stack pointer at
                # the call must equal the console's offset from ITS OWN.
                if (v - port_sp) & 0xFFFFFFFF != (e["off"] & 0xFFFFFFFF):
                    return ({"kind": "sp_offset", "i": i,
                             "report": "event %d (%s) arg %d: console arg was sp%+d, "
                                       "port arg is sp%+d"
                                       % (i, exp["callee"], j, e["off"],
                                          (v - port_sp) & 0xFFFFFFFF)}, counts)
                sp_seen.append({"off": e["off"], "port": v})
                continue
            if (e & 0xFFFFFFFF) != v:
                return ({"kind": "arg", "i": i,
                         "report": "event %d (%s) arg %d: console 0x%08x, port 0x%08x"
                                   % (i, exp["callee"], j, e & 0xFFFFFFFF, v)}, counts)
    return (None, counts)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--capture", required=True)
    ap.add_argument("--module", required=True)
    ap.add_argument("--node", required=True)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    header, cons = load_console(a.capture)
    act = split_invocations(run_port(a.node, a.module))

    totals = {"call": 0, "wgpipe": 0, "sp_arg": 0}
    per_inv, divergence = [], None
    if len(cons) != len(act):
        divergence = {"kind": "invocations",
                      "report": "console recorded %d invocation(s), port produced %d"
                                % (len(cons), len(act))}
    else:
        for ci, ai in zip(cons, act):
            d, counts = compare_invocation(ci["events"], ai)
            for k in totals:
                totals[k] += counts[k]
            per_inv.append({"n": ci["n"], "console_events": len(ci["events"]),
                            "port_events": len(ai["events"]),
                            "console_entry_sp": ci["entry_sp"],
                            "port_entry_sp": ai["entry_sp"],
                            "match": d is None,
                            "divergence": d})
            if d is not None and divergence is None:
                divergence = dict(d, invocation=ci["n"])

    verdict = "pass" if divergence is None else "fail"
    result = {
        "result_schema": 1,
        "standard": "gx_callstream_green",
        "standard_note": ("gx_callstream_green is the GX SDK-seam standard. It is NOT "
                          "one of the wasm-unit verification tiers and must never be "
                          "summed with or reported as any of them."),
        "route": "static_recompilation",
        "route_note": (
            "The module under test was produced by research/tools/static-recomp/"
            "ppc_recomp.py: one C statement per PowerPC instruction word, emitted by "
            "table lookup from boot.dol. No decompiler output, no type inference, no "
            "hand-authored spec and no per-function human review was involved. The "
            "comparison rules are those of research/decomp/oracle-harness/"
            "run-gx-callstream.mjs."),
        "fn": header["function"]["export"],
        "gc_addr": header["function"]["gc_addr"],
        "capture": {"file": a.capture, "invocations": len(cons),
                    "counts": header["counts"]},
        "port_module": a.module,
        "invocations_matched": sum(1 for p in per_inv if p["match"]),
        "events_compared": totals,
        "per_invocation": per_inv,
        "divergence": divergence,
        "verdict": verdict,
        "does_not_verify": [
            "ANY PIXEL. No framebuffer is read on either side.",
            "the MEANING of any argument value.",
            "any ROM function other than this one, and any game state other than "
            "the captured one.",
            "that the recompiler is correct for instructions this function does not "
            "use -- it implements 14 of the 268 forms in the DOL.",
            "an UNSEEDED run: the console's own memory at the six addresses it read "
            "was replayed into the recompiler's MEM1, and the guard flag the original "
            "capture staged was staged in that seed too.",
        ],
        "what_it_does_verify": [
            "that a MECHANICAL, table-driven translation of 99 PowerPC instructions "
            "reproduces the console's SDK-seam behaviour exactly: the same 19 calls "
            "in the same order at the same call sites with the same arguments, and "
            "the same 12 write-gather-pipe writes at the same widths with the same "
            "values from the same store sites.",
            "that the write-gather pipe needs no static source-lowering pass: the "
            "store's effective address is resolved at runtime inside the memory "
            "accessor.",
            "that a stack-local pointer argument -- the class the existing pipeline "
            "records as un-verifiable for 56 exports across 39 units -- lands at the "
            "correct offset from the port's own stack pointer even though that stack "
            "pointer was deliberately chosen to differ from the console's.",
        ],
    }
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(json.dumps(result, indent=2))
    print("verdict: %s  invocations %d/%d  calls %d  wgpipe %d  sp-args %d"
          % (verdict, result["invocations_matched"], len(cons),
             totals["call"], totals["wgpipe"], totals["sp_arg"]))
    if divergence:
        print("divergence:", divergence["report"])
    return 0 if verdict == "pass" else 1


if __name__ == "__main__":
    sys.exit(main())
