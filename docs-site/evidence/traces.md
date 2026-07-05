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
