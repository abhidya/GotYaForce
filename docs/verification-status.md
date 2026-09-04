# Verification status — what is proven, what is not, and what cannot be

**Date: 2026-09-02.** This is the single page to read before repeating any number about
this project's port. It is deliberately not a design document and not a roadmap: it
records the *claim state* — which standards exist, what each one does and does not
establish, how much of the ROM can ever reach each one, and where each area actually
stands today.

Its companions, and the division of labour:

- [`docs/playable-port-design.md`](playable-port-design.md) — the normative design
  contract (v1 → v5, PASS verdict) for the wasm-unit pipeline. It says what SHOULD happen.
  This page says what HAS. **Superseded in part 2026-09-04** — see that document's own
  status note; the pipeline it designs is no longer the active port route (below, §5.5).
- [`docs/matching-decompilation-spike.md`](matching-decompilation-spike.md) and
  [`docs/matching-loop.md`](matching-loop.md) — the spike and the mechanical loop for the
  route that replaced it. §5.5 records the current standard and numbers.
- [`CONTRIBUTING.md`](../CONTRIBUTING.md) §"Evidence and promotion terms" — the binding
  vocabulary rules for anyone writing in this repo.
- [`docs/audits/`](audits/README.md) — dated findings about specific defects.
- [`research/decomp/data/verification-tier-survey.json`](../research/decomp/data/verification-tier-survey.json)
  — the machine-readable measurement this page's §2 quotes, with input digests.

> [!IMPORTANT]
> Nothing here is a projection. Every number is either read out of a committed artifact
> or re-derived by a script named beside it. Where a number is untracked or
> machine-local, it says so and is not treated as evidence.

---

## 1. The tier vocabulary

Five standards exist for wasm port units. They are **not a ladder of confidence in one
thing** — they verify different things, and the weaker ones can never be totalled with
the stronger one.

| Tier | What a result MEANS | What it does **NOT** claim |
| --- | --- | --- |
| `compile_only` | The unit's C compiled and linked to wasm. | **Anything at all about behaviour.** This is inventory. At least one `compile_only` unit is proven behaviourally wrong. |
| `oracle_green` | Every function's full captured corpus replays **byte-exact, per call**, including the **memory write set**, against console-derived evidence. | Any input outside the replayed corpus. Coverage is bounded by the capture, not by the function. |
| `boundary_green` | For a **nonterminating spine** function: over K captured iterations the port emits the identical **callee-boundary sequence** — same callees, same order, same arguments — and the identical spine-owned writes up to the cut. | It is **not** `oracle_green` and never upgrades into one. Nothing outside the declared owned regions is compared; the callees are stubs replaying captured values. |
| `transcript_green` | For an ordinary returning function: the port emits the identical **out-of-unit call transcript** (set, order, arguments) **and returns the identical value**, over N recorded cases; owned-region bytes are compared where the corpus declares them. | **No write-set comparison.** Reads are constrained only insofar as they change an argument or the return value. Callee behaviour is stubbed, not verified. |
| `dispatch_green` | For a function that **dispatches through a ROM function-pointer table**: over N recorded cases the port performs the identical indirect-dispatch stream — same sites, same order, interleaved correctly with its direct calls — and **each dispatch reaches the same GameCube address the console's `bctrl` jumped to**, with the same uniform-frame arguments. | **No write-set comparison.** The table's CONTENTS are seeded from the console (what is verified is *which entry the port selects*). A bridged dispatch's return is **supplied** by the harness. A dispatched callee's own behaviour is not verified. It requires a module built with the gate's indirect-call lowering. |

Four vocabulary traps, all of which have bitten:

1. **`oracle_divergent` is a flag, not a tier.** When a replay FAILs, by design it raises
   `oracle_divergent` and **changes no tier**. `auto-c0035-002` is byte-exact on 6,250 of
   20,000 cases and is *still recorded as a green `compile_only` unit*. Read the tier,
   never the colour, and never the word "green" on its own.
2. **`transcript_green` is a per-FUNCTION artifact.** It lives in its own filename
   namespace (`research/decomp/data/oracle-results/<unit>.<export>.transcript.json`), its
   verdict token shares no string with the other harnesses, and its `claim` block names
   `oracle_green` as the stronger standard in machine-readable form. Since 2026-09-02 it
   **is** also a unit tier the driver can record, but only through a rollup that requires
   **every export** of the unit to have a passing result bound by `wasm.sha256` to the
   staged bytes; a unit whose exports land on more than one standard is reported `mixed`
   and does not promote. Partial coverage reaches no tier. See §6 for the counters that
   had to be fixed first.
3. **`spine_green` does not exist.** The spine standard is `boundary_green`. The uppercase
   `BOUNDARY_GREEN` seen in commit subjects and console output is the verdict token for
   that same standard, not a fifth tier.
4. **`dispatch_green` is ORTHOGONAL, not the next rung.** It is not "transcript_green for
   indirect calls" and it is not weaker-than or stronger-than any of the three above; it
   observes a channel they cannot see and is blind to channels they check. Its artifact
   namespace (`*.dispatch.json`), its verdict token (`DISPATCH_GREEN`) and its `standard`
   field share no string with the others, and its `claim` block says so in
   machine-readable form (`orthogonal_to`, `not_a_ladder`). Never total it with any tier,
   and never describe a `dispatch_green` function as write-verified.

The GX host has a **separate, unrelated** vocabulary — `translated` / `latched` /
`declared-nop` / unimplemented (`GxImplTier` in
`packages/rom-runtime/src/gx/adapters.ts`). Those describe *implementation coverage of an
API surface*. They are not verification tiers and must never be summed with the ones
above. See §5.3.

The GX host also has its own two **verification** standards, added 2026-08-31 —
`gx_callstream_green` and `gx_framebuffer_equivalent`. They are console-derived, they carry
their own verdict tokens and their own artifact filename namespaces
(`*.gx-callstream.json`, `*.gx-framebuffer.json`), and they are **orthogonal to the five
tiers above rather than weaker or stronger than them**: they compare a function's GRAPHICS
SEAM EMISSION and one draw's PIXELS, neither of which a write set, a callee boundary or a
return value can see. Never total a GX result with a wasm-unit tier. See §5.3.

**Matching decompilation has its own standard, added 2026-09-04, and it is not a sixth
rung of the ladder above — it is a different kind of test entirely.** `MATCH` means the
candidate C, compiled with the project's PowerPC compiler, is **byte-identical** to the
retail object after masking relocated operand fields (and checking the relocation's
*symbol* against what the link map says the retail branch resolves to). There is no
capture, no console, no run-time behaviour involved at all — it is a static compile-and-diff
against the shipped binary. Verdict token `MATCH` (or `MATCH_UNVERIFIED` — see below);
artifact `src-match/matched.json`; the standard's own writeup is
[`docs/matching-loop.md`](matching-loop.md) and the reproduction commands are
[`src-match/README.md`](../src-match/README.md). **It must never be summed with
`compile_only`, `oracle_green`, `boundary_green`, `transcript_green`, `dispatch_green`, or
either GX standard** — none of those observe compiled bytes against the retail image, and
this standard observes nothing else. Its honest unit is **both** a function count and an
instruction share, for the same reason `transcript_green`'s ceiling and the GX coverage
numbers are — a matched-function percentage alone hides how much of the game it actually
covers (§5.5).

`MATCH_UNVERIFIED` is a **held-not-counted** result, not a weaker pass. A candidate whose
match rests on a **data** relocation (`R_PPC_ADDR16_HA/LO`, `R_PPC_EMB_SDA21`) has that
operand masked exactly like a branch relocation, but the oracle has no data symbol table to
check the masked value's *symbol* against — so such a candidate would report MATCH against
**any** global in the game. Rather than accept that, the loop downgrades the verdict to
`MATCH_UNVERIFIED` and never records it in `src-match/`. It does not count toward the 405
matched functions below, and no future page may promote it into the corpus without first
closing the underlying hole (a data-relocation symbol check `match.py` does not yet have).

### Non-vacuity is enforced, not assumed

A weaker standard is only worth having if it cannot pass on nothing. For
`transcript_green`: zero cases cannot pass, a corpus below `--min-cases` cannot pass, and
a case with no calls, no return value and no owned expectation fails the run outright —
and `capture_transcript.py` refuses that shape before the emulator is even started. This
guard exists because the vacuity it prevents **already happened** under the older
standard; see §4.

---

## 2. The measured ceiling — how much of the ROM is verifiable at all

Source of record:
[`research/decomp/data/verification-tier-survey.json`](../research/decomp/data/verification-tier-survey.json),
generated by [`research/decomp/data/build_tier_survey.py`](../research/decomp/data/build_tier_survey.py)
from `research/tools/OGhidra/tools/survey_plan_tiers.py`. The artifact binds the sha256 of
the oracle registry, the decompiled-C chunk corpus, and all five classification-logic
files (the indirect-call lowering is one of them, because `dispatch_green` eligibility IS
its parser's verdict), so the numbers are diffable and re-derivable rather than quoted from a terminal.

**This is a ceiling, not progress.** The survey is static and model-free: it asks, of each
function's decompiled C, *could a spec of this standard be built for it at all* — never
*has one been built* or *did it pass*. A function counted below has **not been verified**;
it has been found **eligible**. Verified units are counted in §5, from committed artifacts.

Over **10,954 functions in 1,396 units**:

| Strongest standard reachable | Functions | Share |
| --- | ---: | ---: |
| `oracle_green` (auto-derivable write-comparison spec) | **652** | **6.0 %** |
| `transcript_green` (call sequence + arguments + return value + owned regions) | **8,197** | **74.8 %** |
| `dispatch_green` (indirect-dispatch stream + resolved GameCube targets) | **1,534** | **14.0 %** |
| **Verifiable by some tier** | **10,383** | **94.8 %** |
| Unverifiable by any existing standard | **571** | **5.2 %** |

> **What changed on 2026-09-02, and what did not.** Before `dispatch_green` existed the
> two rows above it summed to 8,849 (80.8 %) and 2,105 functions (19.2 %) had no route to
> any claim. **1,534 of those 2,105 now have one.** Read that as *eligibility*: **not one
> more function has been verified by this change**. What was actually added is four
> console-derived results over four functions (§5.1a) against a ceiling that grew by
> 1,534 — so the gap between reachable and reached got *wider*, not narrower. The third
> standard is worth having because the class it reaches was not "hard", it was
> **unreachable by construction** — and the reason was a lowering choice, not a property
> of the ROM (§3).

Per unit, requiring **full export coverage** (a unit promotion demands every export;
a unit whose exports land on a mix of standards is reported mixed, never rounded up):

| Per-unit state | Units | Share |
| --- | ---: | ---: |
| All exports `oracle_green`-eligible | 2 | 0.1 % |
| All exports `transcript_green`-eligible | 257 | 18.4 % |
| All exports covered, **mixed tiers** | 840 | 60.2 % |
| **Full export coverage (any tier)** | **1,099** | **78.7 %** |
| Has at least one unverifiable export | 297 | 21.3 % |

For scale: before `transcript_green` existed, units with full export coverage numbered
**2**. The second standard moved that to **378**, and the third moved it to **1,099**. It
did not make 1,097 units verified — it made them *reachable*. Note also where the growth
went: almost all of it is the **mixed-tier** row (119 → 840), so most of those units now
depend on *two or three different standards at once* to be covered at all, and a claim
about such a unit has to be quoted per export, never as one word.

### The number that motivated the second standard

Under the write-comparison ceiling alone, **4,455 functions (40.7 %) store nothing a
capture could compare.** For those the byte-exact standard is not hard, it is **empty**: a
spec over them passes vacuously. That is not a hypothetical — see §4.

---

## 3. What is unverifiable, and why

### 3.1 The 1,602 that used to be — the ROM function-pointer dispatch class

Until 2026-09-02 this page said of these functions: the C is `(*(code *)...)()`; emcc
lowers that `bctrl` to a `call_indirect` on the **module's own table**; no import shim can
observe it, so the captured transcript would have a hole exactly where the interesting
behaviour is — and `capture_transcript.py` refuses the shape rather than producing a
transcript that silently omits the dispatch.

Every sentence of that is still true, and the conclusion drawn from it was still wrong.
**The table a composed module dispatches on is not emcc's — it is generated by the
assembly gate.** The design's uniform dispatch ABI (V4 H3) already emitted an
address-keyed table of adapter thunks, `__gf_dispatch`, and the declared
`__gf_dispatch_miss` host import. A thunk is a function the gate wrote, and a function the
gate wrote can be watched. The dispatch that hides from an import shim does not hide from
a thunk the gate generated.

What was missing was the **outbound half**. The companion made it possible to call *into*
a ROM function by address; nothing rewrote the ROM's own indirect call sites to go *out*
through it, so in a gate-built module those `bctrl`s were still `call_indirect` on emcc's
table — invisible, and pointed at a GameCube address that is not a wasm table index.
`research/tools/OGhidra/src/port_indirect_lowering.py` is that rewrite, and the
companion's opt-in trace mode brackets each dispatch with two declared imports.

Measured against the corpus, of the 1,602:

| | Functions | |
| --- | ---: | --- |
| every indirect call site lowerable ⇒ `dispatch_green`-eligible | **1,534** | 95.8 % of the class |
| refused: the call's **result is used** | **68** | 4.2 % |

The 68 are refused deliberately and the refusal is the honest one: the uniform frame's
`i32` result is only a **view** of the return slot (for an `i64` return it is not even the
PPC `r3` image, and the frame header says so), and an indirect call site has no callee
prototype from which to derive the true return class. Lowering those would narrow a return
silently, which is exactly the "signature traps become silent mis-marshalling" risk the
design records as C8. They stay unverifiable rather than becoming quietly wrong.

**The ceiling above is the lowering's PARSER. The compiler was measured separately.**
All **112** staged units were run through the lowering: 90 contain a lowerable indirect
call site, 22 contain none, and **0 were refused**. All 90 were then rebuilt end to end —
lowering, companion, `emcc` with flags byte-identical to the production per-unit build —
and **90 of 90 compiled and linked**, 173 lowered call sites in total, every one of the 90
modules importing `__gf_dispatch_enter` / `__gf_dispatch_exit` and exporting
`__gf_dispatch_at`. That is a compile-and-observability rate, not a verification rate: what
it establishes is that the rewrite survives the toolchain at corpus scale, which is the one
thing a static survey cannot say.

**Site binding is exact for almost all of it.** Of the 1,534, **1,484 (96.7 %)** have
exactly one indirect call site, so their capture binds the ROM's `bctrl` to the port's
lowered site unambiguously. The other 50 have 2–12 sites and fall back to naming the
enclosing *function* rather than the site, because Ghidra's structured C need not order
sites the way the machine code does — the plan records which binding it used and the
result artifact carries it.

Two limits on how far the 1,534 can be read:

- **It requires the lowering.** A standalone unit built the ordinary way is still
  unobservable. `run-dispatch.mjs` refuses such a module by name rather than passing on
  it, and there is a test that pins that refusal.
- **It is not fully static.** The capture plan additionally audits the ROM's own `bctrl`
  count against the lowered C's site count, per function in the closure — a disagreement
  means the decompiled C does not describe that function's dispatch, and the plan refuses
  rather than binding sites by position. That audit needs the DOL, so a function counted
  eligible above can still be refused at plan time.

### 3.2 The 503 that remain — empty transcript

No out-of-unit call, no return value, and no indirect dispatch either. There is genuinely
nothing observable at any boundary to compare. These are not "hard"; under every standard
that exists they are unobservable, and a spec over them would be the vacuity in §4 by
construction. With the 68 above, **571 functions (5.2 %) have no route to a claim.**

The class is still **standard-relative, not permanent** — a fourth standard that compared
internal state directly would move it. No such standard is designed.

---

## 4. The defect `transcript_green` caught on its first outing

`auto-c0020-007.FUN_800c4448` — a function Ghidra typed with 9 parameters, seven of them
invented `double`s, plus one real pointer. Its `oracle_green` corpus
(`research/decomp/oracle-harness/corpora/auto-c0020-007.FUN_800c4448.dolphin-trace.jsonl`)
holds **15 cases, and all 15 record `"reads": [], "writes": []`.** The unit result
`auto-c0020-007.json` records it as 15/15 passing, with the note that it "stores nothing,
so it has no write set to compare."

**A 15/15 pass on nothing.** That is the vacuity the ceiling number in §2 predicts, caught
in the wild. Its `transcript_green` run
(`research/decomp/data/oracle-results/auto-c0020-007.FUN_800c4448.transcript.json`) is a
real `pass` — 12 cases, 12 calls matched, `claim.established: true` — and it is the first
non-vacuous statement anyone has been able to make about that function.

Its neighbour `FUN_800c4468` is the harsher lesson and is frequently confused with it. That
is the function Ghidra gave **16 parameters** (seven invented `double`s, then eight
integer slots); its corpus has **200 cases, none vacuous**, and it passed 200/200 under the
old standard. Its `transcript_green` run **FAILS**: `cases_passed: 0`, `calls_matched: 0`,
`claim.established: false`, diverging at case 0 argument 0, with the artifact recording
that "NO owned-region bytes were reached: the corpus declares 3 watch region(s) but the run
stopped before any case completed."

Two functions, two different failures of the old standard: one passed on nothing, one
passed on a corpus that the stronger boundary check rejects outright. Neither was visible
before.

---

## 5. Where each area actually stands

### 5.1 The spine — first `boundary_green`

**Reached.** `run_main_game_loop` (`0x800527d8`, export `zz_00527d8_`) is the first and
only `boundary_green` result:

- Artifact: `research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json` —
  `standard: "boundary_green"`, **274 / 274 calls matched**, 16 iterations, terminator
  `call_cap`, `divergence: null`, `verdict: "pass"`.
- Corpus: `research/decomp/oracle-harness/corpora/spine-run-main-game-loop.boundary.jsonl`
  (274 call records, 15 back-edges retired). Harness:
  `research/decomp/oracle-harness/run-spine.mjs`.
- It required correcting **Ghidra's invented 16-parameter signature to `void(void)`**,
  proven from DOL disassembly; the correction landed in
  `research/decomp/ghidra-export/chunk_0006.c` (lines 5790-5833) via the sanctioned
  [corpus-correction loop](../research/decomp/corpus-correction-loop.md). Narrative and the
  disassembly proof: `research/tools/dolphin-trace/README.md`.

**What it is worth, stated plainly.** With the ABI corrected there are **zero argument
slots to compare** — the ROM passes none — and the single owned region (`0x80436190`,
4 bytes) held `00000000` at all 274 boundaries and at the cut: the owned-write channel was
exercised but never varied. The entire verdict rests on the **274/274 exact call
sequence**. A negative control (swapping two adjacent callees) does correctly report FAIL,
so the check is not degenerate — but it is one call sequence, not a behavioural proof of
the spine.

**Windows gotcha before anyone re-runs it:** the recorded corpus sha256 is the **LF**
digest. A CRLF checkout will compute a different hash for the same file. That is a checkout
artifact, not tampering.

### 5.1a The dispatch class — first `dispatch_green` results

**Reached, 2026-09-02.** Four functions across two units, all against the live console
(bundled Dolphin, Null video, CPU only), all `verdict: "pass"`:

| unit / export | cases | events | dispatches | distinct targets reached | arg slots compared |
| --- | ---: | ---: | ---: | ---: | ---: |
| `auto-c0011-005` / `FUN_80079a40` | 24/24 | 24/24 | 24 | 1 | 0 |
| `auto-c0011-005` / `FUN_80079ab8` | 40/40 | 80/80 | 40 | **4** | 0 |
| `auto-c0050-003` / `zz_01a31d8_` | 40/40 | 40/40 | 40 | **4** | **40** |
| `auto-c0050-003` / `zz_01a31a0_` | 40/40 | 40/40 | 40 | 1 | 0 |

Artifacts: `research/decomp/data/oracle-results/<unit>.<export>.dispatch.json`. Corpora:
`research/decomp/oracle-harness/corpora/<unit>.<export>.dispatch.jsonl`. Modules:
`research/decomp/port-units-dispatch/<unit>/`, rebuilt from the staged unit by
`research/tools/OGhidra/tools/build_dispatch_unit.py` with byte-identical emcc flags to
the production per-unit build.

**Read the columns, not the verdict.** `FUN_80079ab8` is the one that carries the claim:
its 40 cases dispatch to **four different** GameCube addresses, so the port is discriminating
between table entries rather than always producing the same answer; and each of its cases
also makes a direct out-of-unit call, so the *interleaving* of the two channels is checked.
`FUN_80079a40` and `zz_01a31a0_` reached one target each — over those corpora the state
byte never varied, so what they establish is much weaker and the artifact's
`resolved_targets` says so. `zz_01a31d8_` is the only one that compared any argument.

Three further honest limits, all recorded in each artifact rather than only here:

- **`FUN_80079a40` and `zz_01a31a0_` would be VACUOUS under `transcript_green`** — no
  out-of-unit call, no return value. Their entire observable behaviour *is* the dispatch.
  That is the case the standard exists for, and it is also why a single-target corpus over
  one of them is a thin result.
- **Bridged vs in-table matters.** A dispatch whose target is outside the module's own
  table is serviced by the harness from the console's `r3`, so its return is an *input*;
  only an in-table resolution has its return compared. `auto-c0011-005/FUN_80079ab8`
  reaches one in-table target (`0x80079b08`) and three bridged ones.
- **The memory half of all four results establishes nothing, and they say so.**
  Watch-window bytes are counted three ways on purpose: bytes the harness *replayed*
  into the arena, bytes it *compared* at return, and — the only one that means
  anything — bytes the case actually **moved** away from what was seeded. All four
  artifacts report `owned_bytes_moved: 0`. For `auto-c0050-003` the whole window was
  replayed (`owned_bytes_checked: 0`); for `auto-c0011-005` 29,652 and 49,876 bytes
  *were* compared and every one of them came back byte-identical to the seed, so the
  comparison read back its own input. The `claim.verifies` line for those two says
  **"NOTHING about memory"** in those words rather than quoting the byte count. What
  these four results establish is the dispatch stream, and only that.

**Negative controls.** `research/decomp/oracle-harness/tests/dispatch-harness.test.mjs`
(20 tests, run by `pnpm test:oracle`) drives the harness against mutants of the committed
console captures: a wrong dispatch target, a *plausible* wrong target (another address the
same corpus really dispatches to), a wrong argument register, wrong bytes across an
in-table dispatch, a wrong declared return shape, a swapped dispatch/call order, a missing
event, **a dispatch-table entry the DOL-derived registry contradicts**, and **a
resolution-class disagreement** — plus the guards: an empty capture cannot pass, a case
that observed no dispatch cannot pass, drifting header counts cannot pass, a capture with
no end record cannot pass, and a module built *without* the lowering is refused rather
than passed. One test is the inverse and exists to pin a limit: mutating a **bridged**
return does **not** red, because that value is the harness's own input.

One control mutates the **port** rather than the capture, and it is the one that answers
the standing objection that a thunk-level transcript observes the gate's own lowering
and could therefore agree with itself.
`research/decomp/oracle-harness/tests/fixtures/dispatch-wrong-index/` is `auto-c0011-005`
rebuilt from a `unit.c` in which `FUN_80079ab8` reads its vtable index from
`param_1 + 0x541` instead of `+ 0x540` — **one character**. The lowering, the companion,
the emitted table and the emcc flags are identical, the table audit still passes, and
the module is entirely self-consistent, so nothing inside it can notice. Replayed
against the committed console capture it fails at case 1: *"the console's bctrl at
0x80079ae8 jumped to 0x80079ba8 (FUN_80079ba8), the port dispatched to 0x80079b08"*.
That module is committed with a warning header and must never be promoted, loaded or
counted.

**What closes the wrong-thunk blindness.** A transcript taken at a thunk is self-consistent
with a *wrong* address-to-thunk mapping, so three checks are grounded outside the
companion and every artifact records all three under `claim.wrong_thunk_defence`:
(1) the **console's resolved target**, read out of CTR (or LR for `blrl`) at a breakpoint
on the branch *before* it executes; (2) a **table audit** — every emitted table entry must
agree with `oracle-registry.json`, which is derived from the DOL rather than from the
window's sources, and a contradiction fails the run before any replay; (3) a
**resolution-class check** — the module's in-table/bridged answer must match what the
audited table actually contains. All four results record `table_audit.status: "pass"` with
8/8 entries cross-checked.

### 5.2 The composition ladder — ceiling is rung 1

`research/decomp/data/composition-ladder.json` holds exactly two rungs: rung 0 (N=5,
passed, 0 conflicts, 40 companion thunks) and rung 1 (**N=10**, passed, 0 conflicts,
`new_contested / new_linked = 0 / 38`, 78 companion thunks), checked 2026-08-29.

**Rung 2 has not been reached.** Per [`docs/composition-ladder.md`](composition-ladder.md),
the value-carrier wall that blocked it is removed and that was genuinely the wall — but
rung 2 needs two rebuilds behind it (`auto-c0011-012`, then `auto-c0011-011`), and the
window may surface another placeholder of the same shape after that. **Rung 2 is now a
rebuild-scheduling problem rather than an ABI/owner decision**, which is a real change in
kind, not a change in the ceiling. The ceiling is still N=10.

### 5.3 The GX HLE host — 87.1 % translated; one seam and one draw verified, 0 adapters verified

From [`docs/gx-hle-host.md`](gx-hle-host.md), recomputable from
`research/decomp/data/gx-call-inventory.json` against
`packages/rom-runtime/src/gx/adapters.ts`:

| | Entry points | ROM call sites | Share of 502 |
| --- | ---: | ---: | ---: |
| `translated` | 49 / 76 | 437 | **87.1 %** |
| + `latched` | 50 | 438 | 87.3 % |
| + `declared-nop` | 56 | 468 | 93.2 % |
| unimplemented | 20 | 34 | 6.8 % |

**Coverage is still not verification, and the two must still be quoted together.** What
changed on 2026-08-31 is that the verification column is no longer the single number 0.
It is four numbers, and collapsing them into one percentage would be exactly the error
this page exists to prevent:

| what is compared against the console | before 2026-08-31 | now |
| --- | ---: | ---: |
| GX adapters at `evidenceClass: "verified"` | 0 / 56 | **0 / 56** |
| entry points whose SEAM EMISSION is console-compared | 0 / 76 | **16 / 76 (21.1 %)** |
| ROM draw functions whose RASTERIZED RESULT is console-compared | 0 | **1 of the 1 that is ported** |
| console pixels compared against a host prediction | 0 | **286,720** |

The first row is the one to quote when asked whether the GX host is verified. It has not
moved, and the smoke phase still **fails** if any adapter claims `"verified"`. An adapter
earns that class when *its own* behaviour is checked; neither standard below does that for
any individual entry point.

Two GX standards now exist, both console-derived, both with their own filename namespace
and their own verdict token, and **neither is a wasm-unit tier**:

| Standard | Verdict token | Artifact | What a pass MEANS | What it does **NOT** claim |
| --- | --- | --- | --- | --- |
| `gx_callstream_green` | `GX_CALLSTREAM_GREEN` | `oracle-results/<name>.<fn>.gx-callstream.json` | The gate-lowered wasm build of one ROM draw function emits the **identical SDK-seam stream** to the console — same GX calls in the same order with the same arguments, and the same write-gather-pipe writes at the same widths with the same values. | **Any pixel.** No framebuffer is read. Also not the MEANING of any argument: a 7 is compared as the number 7. |
| `gx_framebuffer_equivalent` | `GX_FRAMEBUFFER_EQUIVALENT` | `oracle-results/<name>.<fn>.gx-framebuffer.json` | The difference between two real console frames that differ only in whether one ROM draw ran is **framebuffer-equivalent** to what the host predicts from its own decoded geometry, decoded vertex colour and blend-enum reading, within a **declared** 4/255 per 8-bit RGB channel. | The rest of the frame (controlled for by the differential, not reproduced). The WebGL backend — no GL context is created. Any textured, TEV-programmed, lit or depth-interacting draw. |

Measured results, both on `zz_0027c34_` (`0x80027c34`), 2026-08-31:

- **call stream** — 4/4 invocations, 124/124 events (76 GX/SDK calls, 48 pipe writes,
  128 pipe bytes), no divergence. The console's own vertex bytes additionally decoded
  through the host's FIFO with 0 dropped and 0 pending.
- **framebuffer** — host-predicted touched region `x [0,640) y [0,448)` matched the
  console's changed region exactly, **0** pixels changed outside it; per-channel |Δ| mean
  0.78, p50 1, p95 2, p99 3, max 7 over 860,160 channel samples; 99.80 % within 4/255.

That second measurement **settles an `[SDK]` item**: `GXSetBlendMode`'s factor numbering,
labelled "[SDK] — NOT settled from the corpus" in `gx/enums.ts`, is discriminated
decisively by the console — reading factor 5 as `SRCALPHA` rather than `INVSRCALPHA` would
have scaled the frame by 7/255 instead of 248/255. It does not settle the hardware's exact
rounding divisor, and the doc says so.

**The ceiling is unchanged**: "framebuffer-equivalent, never pixel-identical"
(`playable-port-design.md` V3 non-fatal note 1). Nothing in these results may be quoted as
bit-exactness, and a p99 of 3/255 over one alpha-blended untextured quad says nothing about
a textured one.

**Non-vacuity is enforced, not assumed**, as for `transcript_green`:
`research/decomp/oracle-harness/tests/gx-callstream-harness.test.mjs` (16 tests, run by
`pnpm test:oracle`) drives both harnesses against mutants of the committed console
captures — wrong argument, wrong pipe value, wrong pipe width, wrong call order, an extra
event, a stack pointer replaced by a static address, a wrong blend-factor reading, a wrong
decoded quad extent — and against the guards: a capture whose guard never opened cannot
pass, an empty capture cannot pass, header counts that drift cannot pass, two identical
console frames cannot pass, and frames from different frame indices are refused outright.

**What the oracle found wrong.** The runtime call-frequency ranking that
`docs/gx-hle-host.md` §2 said "does not exist" now does
(`research/decomp/data/gx-surface/`), and it **inverts the static ranking**: over 32.2 s of
a live 2v2 battle the ROM made **507 calls to entry points the host does not implement**,
each of which its loud-unimplemented adapter would throw on. `GXSetFog` alone accounts for
220 of them while ranking 45th by static call sites. The EFB copy path
(`GXCopyTex`/`GXSetTexCopySrc`/`Dst`/`GXSetCopyFilter`) is confirmed live rather than
hypothetical. Separately, 20 of 21 observed `GXSetTexCoordGen2` calls name a
post-transform matrix the host does not apply, and 5 of 21 ask for a normalized source it
does not apply either — both previously listed as reported approximations, now measured as
the normal case. Full detail and the corrected work order in `docs/gx-hle-host.md` §6.4
and §7.

Write-gather-pipe lowering is real and is exercised on the ROM's own draw function
`zz_0027c34_` — the browser leg drives the **assembly gate's own output**
(`packages/rom-runtime/test/fixtures/gx-rom-unit/`), not a hand-written fixture, and the
call-stream oracle now compares that same unit against the console. Two caveats the doc
itself carries: the lowering is **opt-in and off by default**
(`OGHIDRA_PORT_WGPIPE_LOWERING=1`), and the browser run evidence still lands in untracked
`.tmp/gx-host-smoke/evidence/`, so the smoke phase's recorded counts remain a doc
transcription. The two console standards above are the opposite: their captures and their
result artifacts are committed, so their numbers are re-derivable rather than transcribed.

Ceiling note, permanent: the standard for this boundary is **"framebuffer-equivalent, never
pixel-identical"** (design V3 non-fatal note 1). WebGL rasterization cannot match Flipper —
EFB copy semantics, fixed-point rasterization, the 24-bit depth comparison, texture filter
kernels, and the TEV's signed 10-bit per-stage rounding all differ. Translating more of the
pipeline moves this path closer to that ceiling; it does not raise it. No document, log
line, or test name may quietly upgrade it.

### 5.3a The DVD HLE host — 80.5 % translated, 0 % verified

From [`docs/audio-dvd-hle-host.md`](audio-dvd-hle-host.md), recomputable from
`research/decomp/data/dvd-call-inventory.json` against
`packages/rom-runtime/src/dvd/adapters.ts`:

| | Entry points | ROM call sites | Share of 41 |
| --- | ---: | ---: | ---: |
| `translated` | 9 / 15 | 33 | **80.5 %** |
| + `latched` | 10 | 34 | 82.9 % |
| + `declared-nop` | 13 | 39 | 95.1 % |
| unimplemented | 2 | 2 | 4.9 % |

**Verification is exactly 0 %.** No DVD trace exists and no read has been compared against
a real drive. Two further caveats belong next to that number, and neither is a coverage
question: **this repository contains no disc bytes** (`research/disc/` holds one
`.gitkeep`), so the default disc is one the host builds in memory; and the **timing model
is knowingly wrong** — reads complete inside their adapter call, so the ROM's
`DVDGetCommandBlockStatus` spin loops exit on their first iteration where real hardware
would take milliseconds. The host reports that as
`DVD_READS_COMPLETE_SYNCHRONOUSLY` on every report.

### 5.3b The audio HLE host — the mixer is ABSENT, and no coverage number says so

From [`docs/audio-dvd-hle-host.md`](audio-dvd-hle-host.md) §3, recomputable from
`research/decomp/data/audio-call-inventory.json`. Audio has **two seams** and reporting one
number over both would be a claim rather than a measurement:

| surface | implemented | total | ROM call sites |
| --- | ---: | ---: | ---: |
| **bridged** entry points (adapters can cover these) | 5 / 5 | 5 | 6 / 6 |
| **in-window** entry points (adapters cannot) | — | 15 | 34 |
| **MMIO registers** acted on / stored only / measured | 9 | 9 | 18 |

**The dominant fact is not on that table.** Gotcha Force mixes audio in MusyX microcode
executing on the GameCube DSP. That microcode is not PowerPC code, is not in the DOL, and
is uploaded over a mailbox as a binary blob — there is nothing for any porting pipeline to
translate. This host carries a PCM buffer to the speakers and models the AI/DSP registers
the ROM's own code drives; **it cannot fill that buffer**, so a composed module running
today DMAs silence. The host reports `dspMicrocodeAbsent: true` on every report and the
smoke phase fails if it ever stops.

Second-order gaps, all reported as named diagnostics rather than left to be discovered:
ARAM DMA is stored and not performed (`ARAM_DMA_NOT_MODELLED`; those are the busiest audio
registers in the corpus at 247 reads / 251 writes), and the **assembly gate does not lower
AI/DSP MMIO at all** (`AI_MMIO_NOT_GATE_LOWERED`) — the ROM-unit fixture applies that
rewrite by hand, unlike the GX fixture whose lowering is genuine gate output.

One thing on this path IS checked against something other than itself: the new TypeScript
DSP-ADPCM decoder is compared sample-for-sample against `decode_dsp_adpcm` in
`scripts/export-combat-se.py`, the Python implementation that produced the combat-SE OGGs
the game ships. That is an independent second implementation, not console capture.

### 5.4 Capture coverage — the real bottleneck

Verification is bounded by what has actually been captured off the console, and that
inventory is small:

| | Count | Where |
| --- | ---: | --- |
| Dolphin-captured corpus files | 18 (+1 TS-differential POC, `damage-core-poc.jsonl`) | `research/decomp/oracle-harness/corpora/` |
| — distinct units they cover | 5 (`auto-c0001-005`, `-007`, `auto-c0020-007`, `auto-c0035-000`, `auto-c0050-000`) plus the spine | |
| Committed result artifacts | 33 | `research/decomp/data/oracle-results/` |
| — unit-level (`run-unit.mjs`) verdicts | 7: 2 `pass`, 3 `partial`, 2 `fail` | `<unit>.json` |
| — `transcript_green` | 19: 16 `pass`, 3 `fail` | `*.transcript.json` |
| — `dispatch_green` | 4: 4 `pass` | `*.dispatch.json` |
| — `boundary_green` | 1: `pass` | `spine-run-main-game-loop.boundary.json` |
| — `gx_callstream_green` | 1: `pass` | `*.gx-callstream.json` |
| — `gx_framebuffer_equivalent` | 1: `pass` | `*.gx-framebuffer.json` |
| GX console captures | 3 (1 call stream + 2 console frames) | `research/decomp/oracle-harness/corpora/gx-rom-unit.*` |
| GX runtime surface samples | 2 (one game state) | `research/decomp/data/gx-surface/` |
| Promoted units | 3 — `damage-core`, `collision-core`, `knockback-core` | `research/decomp/port-units/` |
| Units in production | 1 — `damage-core` (+ its threads relink) | `apps/game/public/rom/` |
| Staged units, **all `compile_only` (UNVERIFIED)** | 112 | `research/decomp/port-units-staging/*/provenance.json` |

Three of those 18 Dolphin corpora record **zero cases** (`FUN_800c4308`, `FUN_800c4838`,
`zz_00c4704_`): the capture ran and the function was never reached. They are inventory, not
evidence, and the harnesses refuse them rather than passing on nothing.

Against a corpus of **1,396 units / 10,954 functions**, and against an *eligibility*
ceiling of 10,383 functions. The gap between "could be verified" (§2) and "has been
verified" (this table) is the honest shape of the project: three orders of magnitude — and
2026-09-02 **widened** it, because raising a ceiling by 1,534 functions while adding four
results moves the ratio the wrong way. That is the correct thing to notice about it.

The one unambiguous end-to-end success remains `damage-core`: 4 functions, **26,232 /
26,232 replayed cases byte-exact**, relinked for shared memory and re-verified with a
byte-identical verdict, serving the live game.

### 5.5 Matching decompilation — a different standard, its own corpus

**This is not part of the ladder in §1–§5.4 and none of its counts belong in those
totals.** It is a static compile-and-diff against the retail image, produced by
[`research/tools/matching-decomp/loop.py`](../research/tools/matching-decomp/loop.py) and
recorded in [`src-match/matched.json`](../src-match/matched.json), re-provable at any time
with `python src-match/verify.py --control`.

| | Count | Share |
| --- | ---: | ---: |
| Matched functions (`MATCH`) | **405** | 6.87 % of the 5,897 link-map `.text` functions |
| Matched instructions | **1,773** | **0.2528 %** of `.init` + `.text` (701,464 instructions) |
| Produced with zero model calls | 392 / 405 | — |
| Held as `MATCH_UNVERIFIED` (data relocation, symbol unchecked) | not counted above | — |

**Report this by instructions, not by function count** — the same rule §5.2 states for the
`transcript_green` ceiling applies here with more force, because this corpus is the extreme
case of it: its mean matched function is 4.4 instructions against a corpus mean of 58.2.
Two honesty discounts apply directly to the 405/1,773 above, both recorded in
[`src-match/README.md`](../src-match/README.md):

- **118 of the 405 (29 % of the functions, 6.7 % of the instructions) are a single `blr`**,
  matched by `void f(void) {}`. True about the bytes; thin about the program.
- **No global accessor is in this corpus.** 104 candidates that would otherwise be among
  the easiest shapes in the binary (`lwz r3, d(r13); blr`) were refused rather than
  recorded `MATCH`, because the oracle cannot check a data relocation's symbol — see the
  `MATCH_UNVERIFIED` definition in §1.

A separate measurement — [`docs/matching-compiler-census.md`](matching-compiler-census.md)
— compiled every one of the 12,062 entry points' verbatim (uncorrected) Ghidra C against
the same compiler, to find the ceiling this route is actually working against: **10.07 %
of the game's instructions compile at all**; **87.2 % is blocked by the compiler itself**
(63.6 % code-generator refusals, 23.6 % front-end parse/typecheck refusals), concentrated
behind four diagnostics. A compile is not a match — 10.07 % compiles, 0.61 % of that
matches on the first try with no iteration at all (the census's own §3) — but it is the
number that says the binding constraint here is compiler capability, not model throughput
or GPU time.

Every match in this corpus is `mwcc-rs`-exact, not genuine-Metrowerks-exact: `mwcceppc.exe`
was never obtained, and there is currently no way on this machine to check where `mwcc-rs`
might diverge from it. See
[`research/tools/matching-decomp/TOOLCHAIN.md`](../research/tools/matching-decomp/TOOLCHAIN.md).

---

## 6. Standing claim-honesty rules

These are not style preferences. Each one exists because it was violated and the violation
cost time.

1. **`compile_only` is UNVERIFIED inventory, never progress.** Never describe a
   `compile_only` unit as ported, done, working, or finished. A staged-unit count is a
   queue depth, not an achievement.
2. **A FAIL changes no tier.** A unit can be simultaneously "green" in the driver's status
   field and *proven behaviourally wrong*. Report the tier and the verdict, never the
   status word alone.
3. **Weaker standards are never totalled with `oracle_green`.** `boundary_green` and
   `transcript_green` are callee-boundary claims. Never count a `transcript_green` function
   toward write-verified coverage, and never report either as `oracle_green`.
3a. **`dispatch_green` is orthogonal, and a dispatch result is not a memory result.** It
   verifies which GameCube address the port dispatched to, with which frame arguments, in
   which order. It compares no write set; the dispatch table's contents are handed to the
   port; a bridged callee's return is handed to the port. Never total it with any tier,
   and never let "1,534 functions are now verifiable" be written as "1,534 functions are
   now verified" — rule 6 applies to it with particular force, because this is the largest
   single ceiling movement the project has ever recorded.
4. **GX coverage is not verification.** "87.1 % of call sites translated" and "0 of 56
   adapters verified" are both true and must be printed together. Since 2026-08-31 the GX
   verification figure is no longer a single number (§5.3) — quote the four rows, never a
   blended percentage, and never let "one draw compared against the console" become "the
   renderer is verified". The same rule applies to any future percentage of an API surface.
5. **"Framebuffer-equivalent, never pixel-identical."** The graphics boundary has a ceiling
   below byte-exactness and always will. Do not let a passing render test be written up as
   a pixel match.
6. **A ceiling is not a result.** The §2 numbers describe eligibility. Writing "80.8 % of
   the ROM is verifiable" is correct; writing "80.8 % verified" is a fabrication of three
   orders of magnitude.
7. **Machine-local numbers are not repository evidence.** The driver's queue state lives in
   gitignored `research/decomp/generated/finish-game-port/`. Numbers from it cannot be
   reproduced from a clone and must be labelled machine-local wherever they are quoted.
8. **Relinking invalidates a verdict.** A verified unit relinked for shared memory has
   different bytes than what was verified; it does not carry its `oracle_green` /
   `boundary_green` status across until the full corpus replays byte-equal against the new
   binary. See [`docs/threads-relink-reverify.md`](threads-relink-reverify.md).
9. **Matching-decomp `MATCH` counts are never summed with any trace-based tier, and never
   with each other across the `MATCH` / `MATCH_UNVERIFIED` distinction.** A compile-and-diff
   against retail bytes and a console capture verify different things — one is proof the
   compiled object equals the shipped one, the other is proof the port behaves like a
   running console. Report matching-decomp progress by instructions (§5.5), never folded
   into the wasm-unit ceiling in §2, and never with `MATCH_UNVERIFIED` results included in
   the matched count.

### Fixed 2026-09-02: two driver counters were fail-OPEN on tier

The defect, in the unvendored OGhidra checkout, as it stood on 2026-08-30:

- `src/port_contract.py:125` —
  `counts["staged" if (record or {}).get("tier") == "compile_only" else "green"] += 1`
- `src/port_progress.py:209` — `if record.get("tier") == "compile_only": … else: counts["green"] += 1`

Both tested **"is `compile_only`"** and routed *everything else* — including `None`, a
typo, or a future `transcript_green` — into `green`. The predicate was "not `compile_only`",
not "is `oracle_green`".

**It was live, not latent, and the earlier text on this page was wrong about that.** The
driver ledger carries **two `status: green` records with no `tier` field at all** —
`damage-core` and `knockback-core` (machine-local, `wasm-units-state.json`, re-measured
2026-09-02) — and both counters were already reporting them as verified. Measured on the
live ledger: the old predicate gave **green = 3**, while `run-state.json`'s
`units_verified` (the correct positive test) gave **1**. Two files published by the same
run disagreed, and the looser number is the one in the README banner. The remaining
exposure was real too: the first commit teaching the driver a new tier would additionally
have inflated `progress/current.json` (`queue.green`), `progress/summary.json`, the
generated README table, the health state (`remaining = total − green − staged`), progress-
branch commit subjects, and the contract probe's `counts` that the rig supervisor reads.

**The fix, as made** (OGhidra branch `driver-tier-vocabulary`):

- `src/port_tiers.py` is the single tier vocabulary. `VERIFIED_TIERS =
  {transcript_green, boundary_green, oracle_green}` and `WRITE_VERIFIED_TIERS =
  {oracle_green}` are explicit allowlists; `classify_tier` answers
  `verified` / `staged` / **`unknown`**, and every predicate is a positive membership test.
- Both counters, plus `run-state.json`'s `units_verified` / `units_staged` and the
  unverified-inventory invariant, now use that one predicate. A green record whose tier the
  driver cannot classify lands in a new `unknown_tier` bucket — never in `green`, and never
  quietly in `staged` either. It is published in `summary.json`, `current.json` and the
  README line, and it is deliberately **not** subtracted from health's `remaining`, so an
  unclassifiable record keeps a run from reporting COMPLETE.
- `units_verified` is accompanied by `units_verified_by_tier` and `units_write_verified`,
  so rule 3 (never total the weaker standards with `oracle_green`) is expressible in the
  machine output rather than only in prose.
- Regression tests assert that `None`, `"oracle-green"`, `"ORACLE_GREEN"`, `"spine_green"`,
  `"mixed"` and an arbitrary future tier all classify as `unknown` and none of them lands
  in `green`, in both files and in the run-state writer.

**Under the corrected counters the live ledger reads: green (verified) = 1, staged = 103,
unknown_tier = 2** — where it previously read green = 3, staged = 103.

---

## 7. Reproducing the numbers on this page

```bash
# §2 — the ceiling. Requires the OGhidra checkout (not vendored; clone separately).
python research/decomp/data/build_tier_survey.py
python research/decomp/data/build_tier_survey.py --check   # drift check, writes nothing

# §5.1 — replay the spine capture (no emulator needed)
node research/decomp/oracle-harness/run-spine.mjs \
  --capture research/decomp/oracle-harness/corpora/spine-run-main-game-loop.boundary.jsonl

# §5.4 — replay a unit corpus, and a transcript corpus
node research/decomp/oracle-harness/run-unit.mjs --unit damage-core
node research/decomp/oracle-harness/run-transcript.mjs   # see its --help for corpus args

# §5.1a — replay a dispatch capture (no emulator needed; the lowered modules are committed)
node research/decomp/oracle-harness/run-dispatch.mjs \
  --capture research/decomp/oracle-harness/corpora/auto-c0011-005.FUN_80079ab8.dispatch.jsonl

# the negative controls for it (19 tests), plus every other harness's
pnpm test:oracle
```

Rebuilding a dispatch-lowered module, and capturing a new one off the console (requires the
OGhidra checkout, the emsdk, and — for the capture — the disc and a savestate):

```bash
python research/tools/OGhidra/tools/build_dispatch_unit.py \
  --repo-root D:/GotYaForce --unit auto-c0011-005 \
  --out research/decomp/port-units-dispatch/auto-c0011-005

python research/tools/dolphin-trace/capture_transcript.py dispatch-sites \
  --unit auto-c0011-005 --fn FUN_80079ab8 \
  --wasm research/decomp/port-units-dispatch/auto-c0011-005/unit.wasm \
  --sites-manifest research/decomp/port-units-dispatch/auto-c0011-005/gf_indirect_sites.json \
  --out research/tools/dolphin-trace/plans/auto-c0011-005.FUN_80079ab8.dispatch.json

python research/tools/dolphin-trace/capture_oracle.py launch \
  --scenario battle-roster-0x80079410 --wait 150
python research/tools/dolphin-trace/capture_transcript.py dispatch-capture \
  --plan research/tools/dolphin-trace/plans/auto-c0011-005.FUN_80079ab8.dispatch.json \
  --n 40 --scenario battle-roster-0x80079410 \
  --wasm-rel ../../port-units-dispatch/auto-c0011-005/unit.wasm \
  --arena-rel ../arena-trace-empty.json \
  --out research/decomp/oracle-harness/corpora/auto-c0011-005.FUN_80079ab8.dispatch.jsonl
python research/tools/dolphin-trace/capture_oracle.py stop
```

`--check` re-derives the survey and diffs it against the committed artifact, ignoring only
the timestamp and the tool commit. A non-zero exit means the tree no longer produces the
numbers above and this page is stale.

---

## Provenance

Written 2026-08-30; §1, §2, §3, §5.1a, §5.4 and §6 re-measured and rewritten 2026-09-02
when `dispatch_green` was added. The 2026-09-02 pass changed the ceiling and added four
results; it changed nothing about any previously recorded result, and the four numbers in
§5.3's GX table are unmoved. Every figure was measured against the tree on its stated date,
not carried forward from an earlier document. Where a claim in an existing document disagreed with the
measurement, the measurement won and the other document was corrected — the corrections are
listed in the commit that introduced this page.
