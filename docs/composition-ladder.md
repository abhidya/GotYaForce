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

## Re-execution (2026-08-29) and the `zz_0089100_` resolution

The eligible pool is unchanged since 2026-08-26 (83 units; newest
`generated_at` still `2026-08-26T07:30`), so the rung windows are the same.
Rung 0 reproduced exactly (pass, 40 thunks, 0 conflicts). Rung 1 now refuses
DECIDABLY -- the canonicalizer amendment landed as OGhidra `d0a0142` turns
the old undecidable `canonical_header_ambiguous` into:

    owner_variant_abi_incompatible: zz_0089100_ is declared
    void zz_0089100_(int, uint, int); in auto-c0053-013 but
    int zz_0089100_(int, uint, int); in auto-c0025-002;
    the two declarations cannot be unified

### Which side is wrong: the ROM says the registry is right

PPC has no `void`, so Ghidra's `void` is an inference and a caller-side
`uVarN = f(...)` is an inference about r3 liveness. Both are decidable from
the corpus, and every line of evidence points the same way:

1. **The owner's own body.** `0x80089100` (`chunk_0013.c:65`) decompiles as
   `void zz_0089100_(int, uint, int)` and every one of its exits is a bare
   `return;`. It computes no result: it is an intrusive doubly-linked-list
   bucket insert into the `DAT_80436268/70/78/80/88/90` and
   `DAT_803c6f3c/54` head/tail arrays, selected by the `0x40`/`0x20`/`0x10`
   bits of `param_2` and the head-vs-tail flag `param_3`.
2. **The corpus calls it both ways.** 197 call sites assign a "result", 172
   call it bare -- `chunk_0025.c` itself does both (`:467` bare, `:717`
   assigned). A genuine value-returning API is not used both ways.
3. **The artifact is systematic, not specific to this symbol.** The identical
   `uVarN = <void function>(...)` shape occurs on functions Ghidra itself
   declares `void` at their definition site, e.g. `zz_0007030_`
   (`chunk_0000.c:1548`). It is Ghidra threading the r3/r4 register pair
   across a call inside the `undefined8 param_1 + double param_2..param_8`
   HSD register model, not a return value.
4. **The value goes nowhere.** In `FUN_800e8dac` the "result" flows only into
   the first-parameter slots of `zz_0007030_` / `zz_0007c54_`, which never
   read `param_1`.

Verdict: the oracle registry is RIGHT, `auto-c0025-002` was consuming
register residue, and the fix belongs in the corpus.

### The fix, and why the fork existed at all

`auto-c0025-002`'s per-unit header seed already carried the correct
`extern void zz_0089100_(...)` owner prototype. The verbatim `.c` could
therefore not compile (`void value not ignored`), so the compile-fix model
was forced to redeclare the symbol as `undefined8` to make its own unit
build. The gate then correctly contested that redeclaration. **The corpus
defect is the root cause and the ABI fork is its symptom** -- which is why
re-syncing the seed alone could never have fixed it.

Corrected in `chunk_0025.c` per the manual-corpus-correction convention
(same-line replacement, inline provenance comment, line count unchanged;
of the 150 queue-pinned extraction blocks in that chunk only
`auto-c0025-002`'s 696-749 block changes sha). Two symbols, same class:
`zz_0089100_` at `:717` and `zz_0007030_` at `:734` / `:740`, with `uVar6`
initialised to a deterministic `0` at `:712` in place of undefined register
content.

**Preflight (corpus-correction-loop step 2):** with only the corrected chunk
and the UNMODIFIED owner prototypes, `auto-c0025-002` rebuilds through the
production `emcc_build_unit` invocation and compiles first try -- no model
call, no header edit. Projected onto the rung-1 window its declaration goes
`undefined8 zz_0089100_(int,uint,int);` -> `void zz_0089100_(int,uint,int);`
and the window drops from 1 declaration disagreement to **0**.

The correction is committed on branch `corpus/zz-0089100-residue` (not
pushed, not merged). It is inert until it is on the checkout the driver
reads AND `auto-c0025-002`'s compile-only verdict is revoked so the unit
rebuilds -- the ordering rule in `research/decomp/corpus-correction-loop.md`
step 3. Until then the staged artifact still carries the fork, so the rung
ledger below records the un-corrected reality.

## Ceiling and the ranked blockers (measured 2026-08-29)

A window refuses when two units in it declare the same `zz_*`/`FUN_*` symbol
incompatibly. That is measurable statically from the staged `gnt4_shim.h`
files, and the measurement reproduces the gate exactly at N=5 (0
disagreements, rung 0 passes) and N=10 (exactly 1 -- `zz_0089100_`, which is
exactly what rung 1 refuses on):

| N | declaration disagreements | void/value forks |
|---:|---:|---:|
| 5 | 0 | 0 |
| 10 | 1 | 1 |
| 20 | 23 | 1 |
| 40 | 44 | 4 |
| 80 | 59 | 11 |
| 83 (all eligible) | 63 | 11 |

Ceiling today, on live state: **rung 0, N=5.** With the correction merged and
`auto-c0025-002` rebuilt: **rung 1, N=10** (0 disagreements -> 0 contested ->
ratio 0.0, which meets rung 0's 0.0 budget). Rung 2 (N=20) is blocked by 23
disagreeing symbols and is the next real wall.

Across the whole eligible pool the dominant class is one defect repeated:
the corpus assigns the r3 residue of a void ROM procedure, so every
consuming unit is forced to redeclare that procedure as value-returning.
Every void/value fork symbol in the pool is a genuine void ROM procedure
with zero return-with-value statements in its own decompiled body:

| symbol | address | enters window at N | units carrying the value fork |
|---|---|---:|---:|
| `zz_006d144_` | `0x8006d144` | 8 | 11 |
| `zz_0089100_` | `0x80089100` | 10 | 4 |
| `zz_0007030_` | `0x80007030` | 10 | 5 |
| `zz_006d0dc_` | `0x8006d0dc` | 13 | 9 |
| `zz_00679d0_` | `0x800679d0` | 21 | 3 |
| `zz_0088aa0_` | `0x80088aa0` | 21 | 7 |
| `zz_00456a0_` | `0x800456a0` | 24 | 1 |
| `zz_0006fb4_` | `0x80006fb4` | 49 | 1 |
| `zz_0048288_` | `0x80048288` | 49 | 1 |
| `zz_0085e00_` | `0x80085e00` | 49 | 1 |
| `zz_008aff0_` | `0x8008aff0` | 49 | 1 |
| `zz_0007cac_` | `0x80007cac` | 54 | 1 |
| `FUN_800669d0` | `0x800669d0` | 72 | 1 |

(`zz_004beb8_` at `0x8004beb8` is the same void-procedure class and the
largest by unit count -- 30 of the 83 eligible units carry a declaration
that diverges from its `void` owner prototype -- but the divergences in the
N<=83 windows are arity/unprototyped rather than void-vs-value, so it is
listed here as a sweep target rather than a window fork.)

`auto-c0053-003`'s own header records the mechanism in the model's words:

    /* Disagreement with the advisory registry: zz_006d144_ is assigned to an
     * int in this unit's call site (`iVar4 = zz_006d144_(param_1,0xc0)`), so
     * it MUST return ... */
    extern undefined4 zz_006d144_(int param_1,uint param_2);
    /* extern void zz_006d144_(int param_1, int param_2);  -- rejected: this
     * unit assigns its result; must return undefined4. */

A second, larger class shows up from N=20 on: unprototyped declarations
(`int zz_004beb8_();`) against a real owner prototype. `_parameters_are_abi_
equivalent` refuses unknown spellings, so those are contests too, and they
account for most of the 23 disagreements at N=20.

Scaling the ladder is therefore not a canonicalizer problem: it is a corpus
sweep. Each fork symbol needs the same treatment `zz_0089100_` just received
(prove the ROM body computes no result, drop the residue assignment at every
pinned call site, revoke and rebuild the affected units). That sweep is an
owner decision, not a unilateral one -- correcting all 197 `zz_0089100_`
assignment sites alone would invalidate pinned blocks across dozens of
chunks and require a revocation per affected green unit.

### Cost note

Canonicalization cost scales steeply with the number of distinct owner
symbols in the bundle: rung 0 (N=5) completes in ~3 minutes, rung 2 (N=20)
was still inside the owner corpus walk after 3 hours. Rungs 3-4 (N=40/80)
are not runnable in a single session as the runner stands; the static
disagreement measurement above is the practical instrument for planning
them.
