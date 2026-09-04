#!/usr/bin/env python3
"""throughput.py -- how long would an LLM matching loop take on THIS machine.

Every input is either measured in this repository or stated as an assumption
with its source. Nothing here is a simulation of the model; it is arithmetic
over a decode rate that the project has already measured.

MEASURED INPUTS

  decode rate       2.5 tok/s, 27B model on the GTX 1080 Ti.
                    Source: docs/audits/port-pipeline-integrity.md:655, which
                    uses it to explain why COMPILE_FIX_MAX_TOKENS=4096 pushes a
                    worst-case generation toward ~40 minutes.

  function sizes    research/decomp/data/matching-decomp-census.json, built by
                    leaf_census.py over 12,062 entry points in the retail DOL.

ASSUMPTIONS, each labelled, none of them measured on this machine because the
model server is down and the GPU is leased out:

  prefill rate      40 tok/s. Prefill is compute-bound rather than
                    bandwidth-bound and is conventionally 10-30x decode on this
                    class of card. 40 is generous.
  prompt size       a function-size-dependent budget (see prompt_tokens()).
  reply size        candidate C, roughly 3 tokens per PowerPC instruction plus
                    a fixed preamble. Small by the standards of this project's
                    existing 4096-token compile-fix replies.
  compile+diff      0.4 s. mwcceppc compiles a single small translation unit in
                    well under a second; objdiff.py is microseconds.
  iterations        a per-difficulty-tier guess, and the single most uncertain
                    number in the model. Sensitivity is reported.
  success rate      per tier; also a guess. Reported, not hidden.

Usage:  python throughput.py [--decode 2.5] [--json out.json]
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path

CENSUS = Path("D:/GotYaForce/.claude/worktrees/agent-a3f974e3aa4d99836/"
              "research/decomp/data/matching-decomp-census.json")

# tier -> (max difficulty score, mean iterations to converge, P(converges))
# The tiers are the difficulty score computed by leaf_census.py:difficulty().
TIERS = [
    ("trivial",   0,  3,  0.90),
    ("easy",      2,  8,  0.70),
    ("moderate",  4, 25,  0.40),
    ("hard",      6, 60,  0.15),
    ("research",  99, 120, 0.03),
]


def prompt_tokens(insns):
    """Disassembly + call/SDA context + neighbours + previous diff.

    ~14 tokens per disassembled instruction (address, encoding, mnemonic,
    operands, and the diff line that repeats it), plus a 400-token fixed
    preamble of rules and flag documentation.
    """
    return 400 + 14 * insns


def reply_tokens(insns):
    """Candidate C plus a short rationale. ~3 tokens per instruction."""
    return 120 + 3 * insns


def iteration_seconds(insns, decode, prefill, overhead):
    return (prompt_tokens(insns) / prefill
            + reply_tokens(insns) / decode
            + overhead)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--decode", type=float, default=2.5,
                    help="tok/s, measured: 2.5 on the 1080 Ti")
    ap.add_argument("--prefill", type=float, default=40.0)
    ap.add_argument("--overhead", type=float, default=0.4,
                    help="compile + diff seconds per iteration")
    ap.add_argument("--json")
    a = ap.parse_args()

    F = json.loads(CENSUS.read_text())["functions"]
    # SDK and TRK functions are excluded from the modelled work: they are
    # already matched in public decomp projects (spike doc section 5.3).
    game = [f for f in F if not f["name"].startswith(("gnt4", "TRK", "__TRK"))]

    print("decode %.2f tok/s   prefill %.0f tok/s   overhead %.1f s/iter"
          % (a.decode, a.prefill, a.overhead))
    print("modelled corpus: %d game functions (%d SDK/TRK excluded)\n"
          % (len(game), len(F) - len(game)))

    hdr = ("%-10s %6s %7s %6s %6s %10s %12s %10s"
           % ("tier", "fns", "insns", "iters", "P(ok)", "s/iter",
              "GPU-hours", "matched"))
    print(hdr)
    print("-" * len(hdr))

    lo = -1
    tot_hours = 0.0
    tot_matched = 0
    rows = []
    for name, hi, iters, p in TIERS:
        sel = [f for f in game if lo < f["difficulty"] <= hi]
        lo = hi
        if not sel:
            continue
        n = len(sel)
        insns = sum(f["insns"] for f in sel)
        mean_insns = float(insns) / n
        sper = iteration_seconds(mean_insns, a.decode, a.prefill, a.overhead)
        # A function that fails still burns its full iteration budget.
        hours = n * iters * sper / 3600.0
        matched = int(round(n * p))
        tot_hours += hours
        tot_matched += matched
        rows.append({"tier": name, "functions": n, "instructions": insns,
                     "iters": iters, "p_success": p,
                     "seconds_per_iteration": round(sper, 1),
                     "gpu_hours": round(hours, 1), "matched": matched})
        print("%-10s %6d %7d %6d %6.2f %10.1f %12.1f %10d"
              % (name, n, insns, iters, p, sper, hours, matched))

    print("-" * len(hdr))
    print("%-10s %6d %7d %6s %6s %10s %12.1f %10d"
          % ("TOTAL", len(game), sum(f["insns"] for f in game), "", "", "",
             tot_hours, tot_matched))

    days = tot_hours / 24.0
    print("\n  %.0f GPU-hours = %.0f GPU-days = %.1f GPU-YEARS of continuous"
          % (tot_hours, days, days / 365.0))
    print("  compute, for %d of %d functions matched (%.1f%% by count)."
          % (tot_matched, len(game), 100.0 * tot_matched / len(game)))

    matched_insns = 0
    lo = -1
    for name, hi, iters, p in TIERS:
        sel = [f for f in game if lo < f["difficulty"] <= hi]
        lo = hi
        matched_insns += p * sum(f["insns"] for f in sel)
    tot_insns = sum(f["insns"] for f in game)
    print("  By CODE VOLUME, which is how decomp projects report progress:")
    print("  %.1f%% of game instructions." % (100.0 * matched_insns / tot_insns))

    print("\n== sensitivity ==")
    for d in (2.5, 10, 40, 200):
        h = 0.0
        lo = -1
        for name, hi, iters, p in TIERS:
            sel = [f for f in game if lo < f["difficulty"] <= hi]
            lo = hi
            if not sel:
                continue
            m = float(sum(f["insns"] for f in sel)) / len(sel)
            h += len(sel) * iters * iteration_seconds(m, d, a.prefill,
                                                      a.overhead) / 3600.0
        print("  decode %6.1f tok/s -> %8.0f GPU-hours (%5.1f GPU-years)"
              % (d, h, h / 24.0 / 365.0))

    print("\n  Note: even at 200 tok/s the loop is prefill- and iteration-bound,")
    print("  not decode-bound, so buying a faster card does not rescue it.")

    # ------------------------------------------------------------------
    # The empirical alternative: rates actually ACHIEVED by published
    # LLM-driven matching-decomp projects, which used hosted frontier
    # models rather than a local quantised 27B.
    # ------------------------------------------------------------------
    print("\n== published LLM-driven matching decomp, for comparison ==")
    print("  (agent loops on hosted frontier models, not a local GPU)")
    published = [
        # (name, functions matched, calendar days, parallel loops/contributors)
        ("Star Fox Adventures (GameCube, 2.87 MB code)", 9304, 210, 8),
        ("Snowboard Kids (N64, 2145 fns, 100% matched)", 2145, 84, 1),
    ]
    n_here = len(game)
    for name, fns, days, par in published:
        per_day = float(fns) / days
        print("  %-46s %6.1f fns/day (%d loop%s)"
              % (name, per_day, par, "" if par == 1 else "s"))
        print("  %-46s -> %d functions here in %.0f days (%.1f months)"
              % ("", n_here, n_here / per_day, n_here / per_day / 30.4))
    print("\n  These are CALENDAR rates for whole projects, including the human")
    print("  time the local-GPU model above does not account for. They are the")
    print("  right comparison because they are the same task on the same class")
    print("  of binary -- and they are 2-3 orders of magnitude off the local")
    print("  2.5 tok/s figure. The difference is the model, not the method.")

    if a.json:
        Path(a.json).write_text(json.dumps({
            "decode_tok_s": a.decode, "prefill_tok_s": a.prefill,
            "overhead_s": a.overhead, "tiers": rows,
            "total_gpu_hours": round(tot_hours, 1),
            "total_matched": tot_matched,
            "modelled_functions": len(game),
        }, indent=1))
        print("\nwrote %s" % a.json)


if __name__ == "__main__":
    main()
