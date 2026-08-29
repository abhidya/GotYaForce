---
title: Runtime Traces
---

# Runtime traces

Dolphin GDB stub traces used to validate mechanics claims.

**Sources:**
- `research/traces/GG4E/dolphin-gdb-trace-results.md`
- `research/traces/GG4E/asset-runtime-capture-sop.md`
- `research/traces/GG4E/mechanics-runtime-trace-plan.md`
- `research/traces/GG4E/golden-trace-runbook.md`

## SOP

Asset runtime capture has a documented SOP. See
`research/traces/GG4E/asset-runtime-capture-sop.md` for breakpoints,
watchpoints, and golden-fit recipe.

## What traces prove

Many Dolphin traces prove PAD normalization but not B/X/Z action semantics.
Treat action claims from PAD-only traces as `invalid` unless backed by
additional watchpoints. See [Trace validity ledger](./traces-ledger).

## Per-call oracle capture (`dolphin-trace`)

A second, newer trace surface exists for the wasm-unit port: `research/tools/dolphin-trace/`
breaks on a ported function's entry in the live game and records, per call, the arguments,
referenced memory, return value, and memory writes. The output is a JSONL fixture that
`research/decomp/oracle-harness/run-unit.mjs` replays against the compiled wasm unit, which is
how a unit earns `oracle_green`. Capture plans live in `plans/`, reusable play scenarios in
`scenarios/`.

Two limits are worth stating plainly:

- **These are samples, not replayable traces.** No DTM movie exists; every capture rides a
  savestate plus synthesized input, so a capture cannot be reproduced bit-for-bit later.
- **Most functions never fire.** A 90-second scout over 201 callee-free staged functions
  during a live 2v2 fight hit exactly two of them. Coverage, not tooling, is the bottleneck.

See the [verified ports guide](../contributing/porting) for how a capture becomes a verdict.
