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

### Rung 2 probe (N=20) and what actually makes a window refuse

The ladder is stopped at rung 1 by the E1 budget, so rung 2 was run only as a
diagnostic probe -- it is deliberately NOT in the ledger. It refuses at
canonicalization, on a different symbol and through a different path:

    owner_variant_abi_incompatible: Clang rejected zz_007c800_
    owner/variant pair at auto-c0011-011/gnt4_shim.h

`0x8007c800` is another void ROM procedure (`chunk_0011.c:3407-3415`, registry
`return_type: void`, `returns_value: false`); `auto-c0011-011` consumes its
result.

Comparing the three runs pins down when a window refuses. There are two
independent paths, and a window has to clear both:

1. **Header vs header** -- two units in the window declare the same symbol
   incompatibly (rung 1: `auto-c0053-013` void vs `auto-c0025-002`
   `undefined8` on `zz_0089100_`). This is what the disagreement table above
   measures.
2. **Owner registry vs variant** -- a unit's declaration is incompatible with
   the registry owner AND that symbol's owner unit is itself in the window,
   so the owner loop canonicalizes it (rung 2: `zz_007c800_`, owner unit
   `auto-c0011-012`, which is in the last-20 window; the owner of
   `zz_0089100_`, `auto-c0013-000`, is not in any window here, which is why
   that symbol only ever surfaced through path 1).

That is why rung 1b links: dropping `auto-c0025-002` removes the window's
only header/header disagreement, and no owner unit for a divergent symbol is
present. `auto-c0053-003`/`-005` still carry a divergent `zz_006d144_`
declaration in that window and it costs nothing, because `zz_006d144_`'s
owner (`auto-c0009-007`) is absent.

Practical consequence: neither table alone predicts the gate. The
header-disagreement count is the lower bound and the owner-fork count (24
symbols across the full pool) is the upper bound. Both refusals observed so
far are in the owner-fork set, and both are the same residue defect.

### What it actually costs to climb (measured 2026-08-29)

Not every disagreement needs a corpus correction. Split each window's
disagreeing symbols by whether the owner-decl seed sync could simply
supersede the divergent declaration on the unit's next build:

- **rebuild-only** -- the unit's staged header predates the owner-decl
  injection pass (typically an unprototyped `int zz_004beb8_();` against a
  real owner prototype), and nothing in that unit consumes a result the
  owner declares void. A plain rebuild repairs it; no corpus change.
- **corpus fix** -- the owner is a `void` ROM procedure AND the unit's
  verbatim `.c` assigns its result. No header can reconcile that (the driver
  says so itself in `void_result_contradictions`), so the residue assignment
  has to come out of the chunk.

| N | disagreements | rebuild-only | corpus fix | corpus-fix symbols |
|---:|---:|---:|---:|---|
| 5 | 0 | 0 | 0 | -- |
| 10 | 1 | 0 | 1 | `zz_0089100_` (corrected on this branch) |
| 20 | 23 | 21 | 2 | + `zz_006d0dc_` |
| 40 | 44 | 38 | 6 | + `zz_0007030_` `zz_00456a0_` `zz_00679d0_` `zz_006d144_` |
| 80 | 59 | 47 | 12 | + `FUN_800669d0` `zz_0006fb4_` `zz_0007cac_` `zz_0048288_` `zz_0085e00_` `zz_008aff0_` |
| 83 | 63 | 51 | 12 | (same 12) |

All twelve are confirmed void in their own decompiled bodies (zero
return-with-value statements): `0x800669d0`, `0x80006fb4`, `0x80007030`,
`0x80007cac`, `0x800456a0`, `0x80048288`, `0x800679d0`, `0x8006d0dc`,
`0x8006d144`, `0x80085e00`, `0x80089100`, `0x8008aff0`.

So the whole 83-unit composed module is reachable from **12 corpus
corrections plus a rebuild sweep** -- two of the twelve (`zz_0089100_`,
`zz_0007030_`) are already corrected on this branch for `auto-c0025-002`.
Note that a symbol is only *cleared* once every unit that consumes it in the
window has been corrected and rebuilt, so the corrections are per call site,
not per symbol.

Symbols that look contested but are NOT residue defects (their ROM bodies do
return values, so the consuming units are right and only the declaration
spelling diverges): `zz_0006f98_` `zz_004cd24_` `zz_0066ff0_` `zz_00677b0_`
`zz_006dbe0_` `zz_0088aa0_` (`void *`) `zz_01cce38_` `zz_0027adc_`
`FUN_800452a0` `FUN_80066838`. These belong to the rebuild-only bucket.

### Cost note

Canonicalization cost scales steeply with the number of distinct owner
symbols in the bundle: rung 0 (N=5) completes in ~3 minutes, rung 2 (N=20)
was still inside the owner corpus walk after 3 hours. Rungs 3-4 (N=40/80)
are not runnable in a single session as the runner stands; the static
disagreement measurement above is the practical instrument for planning
them.

## Correction to the "12 corpus fixes" estimate (measured 2026-08-29, second pass)

The estimate above counted a symbol as a residue defect on one test: its own
decompiled body is `void` with zero `return <expr>;` statements. That test is
necessary but NOT sufficient, and re-deriving it independently changed the
answer for **five of the twelve**.

### Why a `void` body can still deliver a value

PowerPC has no `void`. A function whose last action is a call leaves the
callee's `r3` untouched through its own epilogue, so it delivers that value to
its caller whether or not Ghidra prints a `return` for it. Ghidra's `void` at
the definition site is an inference about `r3` liveness at `blr`, and for a
tail-call wrapper that inference is simply wrong. The corpus shows the wrong
side directly: the ROM contains a real `cmpwi r3,0` after those calls, which is
why the decompiler emits `(iVarN = f(...), iVarN != 0)` -- a comparison Ghidra
never invents.

    void zz_006d144_(int param_1,uint param_2)      /* chunk_0009.c:2497 */
    { ... FUN_800669d0(param_1,param_2); return; }  /* -> FUN_80066a30    */

    undefined4 FUN_80066a30(int,uint,short)         /* chunk_0008.c:3390 */
    { ... return 0; ... return 1; }                 /* angle-clamp flag  */

`zz_006d144_` therefore returns `FUN_80066a30`'s 0/1 flag, and 156 of its 161
assigning call sites branch on it. The consuming units' `extern int` are RIGHT
and the registry owner prototype is wrong.

### The decisive test: what the corpus does with the result

Classifying every assignment site of every void-owner fork symbol inside the
83-unit pool's pinned blocks by how the assigned variable is consumed
(BRANCH / RETURN / STORE vs only reaching a dead first-parameter slot, or dead)
separates the two classes cleanly, with no symbol landing in both:

| class | symbols | pool units |
|---|---:|---:|
| residue -- result never branched on, stored or returned | 14 | 4 exclusively |
| value carrier -- result drives control flow or is returned | 10 | 28 |

Value carriers (registry `void` is wrong; the fix is an owner-prototype
correction, NOT a corpus edit): `zz_006d144_` `zz_006d0dc_` `zz_007c800_`
`FUN_800669d0` `zz_00679d0_` `zz_008ae10_` `zz_01b1fb8_` `zz_01f1280_`
`zz_0085e00_` `zz_008aff0_`. Every one is either a terminal tail call into a
value-returning callee (`FUN_80066a30`, `zz_008ae60_`, `zz_01b1014_`, an
indirect `PTR_FUN_803a17..` dispatch) or leaves a live computed register at
`blr` (`zz_00679d0_` carries `zz_00677b0_`'s `undefined4`). `zz_0085e00_` and
`zz_008aff0_` are genuine no-result procedures, but the only pool call sites
are `uVar6 = f(...); return uVar6;` inside `uint FUN_800bee1c`
(`chunk_0019.c:3068`), which returns the residue -- correcting those two sites
means deciding what `FUN_800bee1c` returns, which the corpus cannot settle.

Residue symbols (safe, same class as the merged `chunk_0025.c` correction):
`zz_0089100_` `zz_0007030_` `zz_0007cac_` `zz_0006fb4_` `zz_00456a0_`
`zz_0048288_` `zz_0018270_` `zz_00086b8_` `zz_0005984_` `zz_00088a4_`
`zz_0008970_` `zz_0040b94_` `zz_0040d64_` `zz_0197ad8_`.

### What a corpus sweep can actually reach

A unit only stops forking once EVERY void-owner assignment in its pinned blocks
is gone. Of the 32 pool units carrying such assignments, only 4 have no value
carrier among them and are therefore corpus-correctable end to end:
`auto-c0002-001` `auto-c0028-018` `auto-c0029-001` `auto-c0034-018` (12 sites,
corrected in the commit that carries this section). The other 28 are blocked on
a value carrier and cannot be unforked by any corpus edit --
`zz_006d144_` alone blocks 11 of them and `zz_006d0dc_` another 9.

So the honest ceiling is NOT "12 corpus corrections plus a rebuild sweep":

| step | reachable |
|---|---|
| corrections merged + `auto-c0025-002` revoked and rebuilt | rung 1, N=10 |
| + the 4 units above revoked and rebuilt | still rung 1 |
| rung 2 (N=20) and beyond | blocked on the owner-prototype decision |

Rung 2's observed refusal is `zz_007c800_` -- a value carrier. Climbing past
rung 1 needs the oracle registry to record the tail-call return types for the
ten value-carrier symbols (an owner decision: it changes the canonical ABI for
symbols the whole fleet declares), after which those 28 units are
rebuild-only. No amount of corpus correction substitutes for it.

### Rung state after the `auto-c0025-002` revocation (2026-08-29)

`auto-c0025-002`'s corpus fix landed on `main` as `747bc061`, so the ordering
rule in `research/decomp/corpus-correction-loop.md` step 3 was satisfied and its
compile-only verdict was revoked inside a manual-gate pause window
(`verdict-revoke-bb414324c7e6…`, registry 167 -> 168, gate restored). The unit
is `pending` and rebuilds from the corrected chunk on the driver's normal
rotation.

The eligible pool is therefore 82, and the rung-1 window is the old rung-1b set
(`auto-c0019-016` in place of `auto-c0025-002`). Both rungs were re-run in
scratch against that pool, with owner-derived canonicalization and the dispatch
companion enabled:

| rung | N | result | conflicts | companion | new_contested/new_linked |
|---:|---:|---|---:|---:|---|
| 0 | 5 | PASS | 0 | 40 thunks | 0/40 = 0.0 |
| 1 | 10 | **PASS** | 0 | 78 thunks | 0/38 = 0.0 |

Rung 1 links with no substitution and no contested symbol, so the E1 budget is
met (0.0 <= rung 0's 0.0) and **the ladder ceiling moves from rung 0 to rung
1**. The static declaration-disagreement measurement over this pool reproduces
the gate exactly: 0 at N=5, 0 at N=10, then 27 at N=20, 42 at N=40, 57 at N=80,
61 at N=82.

Rung 2 (N=20) was NOT re-run: its refusal is already characterised
(`owner_variant_abi_incompatible` on `zz_007c800_`, owner unit `auto-c0011-012`
in the window), `zz_007c800_` is a value carrier per the section above, and the
run costs hours. Projected ceiling stands at rung 1 until the owner-prototype
decision lands.

## The owner-prototype decision, taken (2026-08-29)

The ten value carriers named above are no longer a pending owner decision. Each
was re-verified against the DOL text section itself -- `boot.dol` disassembled
with capstone PPC32-BE against `research/symbols/GG4E-CSM-20220412.map` -- not
from the decompiled C, and all ten are now recorded non-void in
`research/decomp/data/oracle-registry.json`.

The rule the disassembly settles: **an epilogue never writes r3.** Every
`lwz r0,N(r1) / lwz r31,... / mtlr r0 / addi r1,r1,N / blr` sequence restores
lr, the saved GPRs and the stack pointer and leaves r3 exactly as the last call
left it. So a function whose last action is `bl` delivers its callee's result,
and a function that calls something and then never writes r3 again delivers
that result too. "void body with no `return <expr>;`" is necessary but not
sufficient for a no-result procedure.

| symbol | ROM evidence | terminal | recorded |
|---|---|---|---|
| `zz_006d144_` | `bl 800669d0` @`8006d18c`, epilogue clean | `FUN_80066a30` `li r3,0`/`li r3,1` | `undefined4` |
| `zz_006d0dc_` | `bl 800669d0` @`8006d124`, epilogue clean | same | `undefined4` |
| `FUN_800669d0` | `bl 80066a30` @`80066a1c`, epilogue clean | `FUN_80066a30` | `undefined4` |
| `zz_007c800_` | `bl 800669d0` @`8007c828`, epilogue clean | same | `undefined4` |
| `zz_00679d0_` | `bl zz_00677b0_` @`800679e4`, r3 never rewritten on any path | `zz_00677b0_` | `undefined4` |
| `zz_008ae10_` | `bl zz_008ae60_` @`8008ae28`, epilogue clean | `mr r3,r28; blr` | `undefined4` |
| `zz_01b1fb8_` | `bl zz_01b1014_` @`801b1fc4`, epilogue clean | `mr r3,r31; blr` | `int` |
| `zz_01f1280_` | `bctrl` @`801f12b4`, epilogue clean | all 4 table handlers `undefined4`, shared tail `li r3,1` @`801f16ac` | `undefined4` |
| `zz_0085e00_` | `bl zz_0088aa0_` @`80085e38`; NULL test branches to the epilogue, r3 never rewritten | `zz_0088aa0_` `void *` | `void *` |
| `zz_008aff0_` | leaf; NO instruction in `8008aff0`-`8008b00c` writes r3 | -- returns param_1 | `int` |

Two of these had been provisionally filed as genuine no-result procedures. The
disassembly says otherwise for both, and that settles their consumer
`uint FUN_800bee1c` without any reasoning about *its* callers: on the
`zz_0085e00_` path it forwards the allocation result, on the `zz_008aff0_` path
it forwards a live object pointer (never zero), and its other exits are
`return 0;` and `return (uint)bVar7;`. FUN_800bee1c is a predicate and stays
`uint`, unchanged.

### Why this is the wall, and exactly where it stood

`plan_canonicalization` supersedes an unprototyped placeholder declaration
(`extern int f();` -- 201 of 239 owner-symbol variants have that shape) with the
owner prototype and never probes it. There is one carve-out:

```python
if supersede and owner.projection.abi_tuple.return_type == "void" and not result_unused:
    substitute = None if owner_defined_here else _import_safe_prototype(owner)
```

A **void** owner whose result some unit **consumes**, when the owner's own unit
is **in the window**, cannot be superseded -- substitution is refused and the
pair goes to the Clang probe, where `int f()` against `void f(int,uint)` is
incompatible. That is the whole of rung 2's refusal, and it is a return-type
fact, which is why no corpus correction could reach it: the registry's canonical
ABI had to change.

With the owner return type no longer `void`, the carve-out does not fire and the
placeholder is superseded silently. Verified symbol by symbol against the real
`ClangDeclaratorParser` and the real helpers, over the N=20 window:

- **before** (main registry): `zz_007c800_` @ `auto-c0011-011`,
  `extern int zz_007c800_();` vs `void zz_007c800_(int, uint);` -> probed ->
  **incompatible**. This reproduces the recorded rung-2 refusal exactly.
- **after** (corrected registry): that same site is `SUPERSEDED`, and so is
  every other placeholder/spelling-only variant of the ten in the window.

### The header-disagreement table is not the unlock, and never was

The tuple-equality table over unit headers barely moves, because it measures
header-vs-header divergence and the registry change does not rewrite any staged
header:

| N | baseline | after the 2 required rebuilds | at full convergence |
|---:|---:|---:|---:|
| 10 | 0 | 0 | 0 |
| 20 | 27 | 28 | 23 |
| 40 | 42 | 43 | 38 |
| 80 | 57 | 57 | 51 |
| 82 | 61 | 61 | 55 |

It even ticks *up* at N=20/40 after a partial rebuild, because a rebuilt unit's
synced declaration diverges from its unrebuilt neighbours'. Six symbols leave
the disagreeing set at N=82 (`FUN_800669d0`, `zz_00679d0_`, `zz_006d0dc_`,
`zz_006d144_`, `zz_0085e00_`, `zz_008aff0_`); the residue is a different
population of symbols entirely. Treat that table as the lower bound it always
was and read the owner/variant path instead.

### What still has to happen

Of the ten units whose queue-pinned blocks changed sha, **eight are still
`pending`** and will pick up the corrected corpus on their first build with no
intervention. Only two are green and need the corpus-correction loop's
revoke-and-rebuild:

- `auto-c0011-012` -- owner of `zz_007c800_`; its staged `unit.c` still carries
  the pre-correction `void zz_007c800_(int,uint)` definition, which now
  contradicts the corrected owner. **This is what rung 2 waits on.**
- `auto-c0019-013` -- carries the `(uint)` cast line; its build is unaffected
  either way (`-Wno-int-conversion` is set in both the per-unit and the assembly
  compile), so this one is provenance hygiene, not a blocker.
