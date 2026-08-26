# Composition ladder — rung procedure (design G3 as amended by E1)

The ladder grows the composed link beyond the N=5 gate window by doubling:
5 → 10 → 20 → 40 → … Each rung is one assembly-gate pass over the last N
gate-eligible units, run with owner-derived canonicalization AND the G2/H3
dispatch companion enabled. The normative budget is V4 E1:

    a rung passes iff its window LINKS, and
    new_contested_symbols / new_symbols_linked  ≤  the previous rung's ratio.

A rising rate is the hard stop: the ladder halts and ABI unification is
redesigned before any further scaling (G3 stop rule).

## Ledger

`research/decomp/data/composition-ladder.json` — one entry per rung:
`n`, `units`, `passed` (link AND budget), `conflicts` (symbol/class/units),
`new_contested_symbols`, `new_symbols_linked`, `ratio`, `companion`
(functions, table_size, arity export presence), `checked_at` (from the gate
result — the ledger carries no wall-clock of its own). Contested symbols
from refused attempts within a rung (e.g. a substitution after a refusal)
count toward that rung's conflict cost.

## Mechanics (scratch lane; never the live pipeline)

Runner: `scripts/composition_ladder.py` (Python-only, per the owner rule).
It imports the live OGhidra checkout read-only (`research/tools/OGhidra`)
and drives the SAME code path as the driver: `run_assembly_gate` with the
driver's `_canonicalization_request` (owner snapshot, pinned Clang,
`sdk_seed_path` = the live `gnt4_shim_seed.h`, read fresh) and
`dispatch_companion=True`, linking with the driver's own emcc link/smoke
runners. All writes land in a scratch directory.

    # 1. snapshot artifacts + canonical state into scratch (stable read)
    .venv/Scripts/python.exe scripts/composition_ladder.py init --scratch <dir>

    # 2. the gate's own eligibility/recency view of the snapshot
    #    (select_recent_green_units, tiers oracle_green + compile_only;
    #     digest-mismatch and pending units come back as exclusions)
    ... select --scratch <dir>

    # 3. one rung = the LAST n eligible units, oldest-first link order
    ... rung --scratch <dir> --tag rung0 --units <last-5 csv>
    ... rung --scratch <dir> --tag rung1 --units <last-10 csv>

    # 4. fold rung dumps into the tracked ledger (E1 ratios computed here)
    ... ledger --scratch <dir> --rungs "rung0;rung1" \
        --out research/decomp/data/composition-ladder.json

Notes:

- A snapshot taken under a running driver usually contains one `porting`
  record (the in-flight unit). `run_assembly_gate_now`'s interrupted-record
  guard exists to protect LIVE selection; against a frozen snapshot the
  equivalent is the eligibility rule itself — a `porting` unit is never
  green and never selected. The runner's explicit-units form reuses the
  same selection helper and records the in-flight unit in the `select`
  evidence.
- A rung refusal (canonicalize / link / companion) is a finding: capture
  the full refusal, then at most ONE mechanical remediation — drop the
  single conflicting unit, substitute the next eligible, re-run — and the
  substitution's conflicts are the rung's conflict cost in the ledger.
  Artifacts are never hand-edited.
- `new_symbols_linked` is measured as the growth of the dispatch-companion
  table (one thunk per defined function in the window), which is exactly
  the set of symbols the composed module links and can dispatch to.

## Current rung (2026-08-26, first execution)

Rung 0 (N=5) PASSED with the companion enabled — its first real-fleet
link: 40-thunk table, `__gf_dispatch` / `__gf_dispatch_arity_mismatches`
exported and `__gf_dispatch_miss` imported by the composed module. Rung 1
(N=10) LINKS after one substitution (auto-c0025-002 → auto-c0019-016; the
refusal was `canonical_header_ambiguous` on `zz_0089100_`, an
undefined8-vs-void caller-declaration fork), but that substitution costs
the rung its one contested symbol: ratio 1/38 against rung 0's 0/40. The
rate rose, so per the E1 budget the ladder is STOPPED at rung 1 pending
ABI unification (the known assembly-ABI seam work). See the ledger for
the full record.
