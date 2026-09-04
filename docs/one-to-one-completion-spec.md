# One-to-one completion spec — from the measured state to a playable 1:1 build

**Date: 2026-09-01.** Status: **DRAFT FOR OWNER REVIEW.** This document proposes; it does
not record. Nothing in it has been implemented and nothing in it is a claim about the port.

> [!IMPORTANT]
> **Superseded in part, 2026-09-04 — the owner chose matching decompilation as the port
> route.** Read [`docs/static-recompilation-spike.md`](static-recompilation-spike.md) and
> [`docs/matching-decompilation-spike.md`](matching-decompilation-spike.md) first; the
> mechanical loop that route runs on is
> [`docs/matching-loop.md`](matching-loop.md). This document was written for, and
> everywhere below assumes, the wasm-unit pipeline that route retires. Read it accordingly:
>
> - **Superseded — do not act on these as written.** §4's critical path (P0–P7) and its
>   revisions in §6/§6a, all of which are steps *in the wasm-unit driver*; the composition
>   ladder as a route to a running game (§3.1, §3.8, gaps **C1/C2/C7/C9**); every gap and
>   option keyed to the driver's queue, the assembly gate, or per-unit specs (**E5**, **E6**,
>   **E11**'s framing as a port-pipeline defect rather than a decompiler-inference problem);
>   §9's owner-decision list insofar as it assumes the driver is what gets decided about.
>   The static-recompilation spike's §5.3 and the matching spike's §6.1 both enumerate, item
>   by item, what becomes obsolete — read those tables against this document's gap list
>   before reusing any of it.
> - **Still stands.** The HLE host material is route-independent and unaffected: §3.5 (H4,
>   audio has no mixer), §3.6 (H1/H2, the GX host cannot render a battle frame), §3.7 (H7/H5,
>   DVD and audio MMIO) — the static-recomp spike's §5.1 says this in as many words ("the
>   largest single body of work in the project... is untouched"). The claim-honesty
>   vocabulary and rules throughout (never total a weaker standard with a stronger one, a
>   ceiling is not a result, machine-local numbers are not repository evidence) apply
>   unchanged to whatever standard is in use, matching decomp's `MATCH` included — see
>   [`docs/verification-status.md`](verification-status.md) §5.5 and §6 rule 9. §9's
>   supplied-inputs list (a DTM, disc/save-state legality) and the general shape of "the
>   owner decides scope, an agent does not" also stand.
>
> Nothing below this note has been edited to reflect the route change; it is preserved as
> the record of the plan that was reviewed and superseded.

## How to read this, and what it is for

Three documents already exist and this one does not replace any of them:

- [`docs/playable-port-design.md`](playable-port-design.md) — the normative design contract
  (v1 → v5, PASS verdict). It says **what should happen**, mechanism by mechanism.
- [`docs/verification-status.md`](verification-status.md) — the claim state. It says **what
  has happened**, re-measured against the tree.
- [`CONTRIBUTING.md`](../CONTRIBUTING.md) §"Evidence and promotion terms" — the binding
  vocabulary.

This page answers a question none of them asks: **what is the ordered, gated sequence that
ends in a person playing this and it behaving like the GameCube game, and what is the
strongest true sentence we would be able to say about the result?** It is a spec, an options
analysis, and an adversarial review of itself.

It uses the review method [`docs/playable-port-design.md`](playable-port-design.md)
established and which produced four rounds of correction there: **state the plan, try to
prove it fails, list the fatal gaps, correct them, re-review, and record the residual risks
that survive.** §5 is that review turned on §2–§4 of this same document. A spec that passes
its own review on the first try has not been reviewed.

> [!IMPORTANT]
> Every number below is either read out of a committed artifact, computed from one by a
> command shown in §10, read out of a named source file at a cited line, or read out of a
> named commit message. Numbers that come from the driver's gitignored state
> (`research/decomp/generated/finish-game-port/`) are labelled **machine-local** and cannot
> be reproduced from a clone — claim-honesty rule 7,
> [`docs/verification-status.md:433`](verification-status.md). Anything that is a
> projection rather than a measurement is labelled **ESTIMATE** inline, with the
> measurement it was derived from.

---

## 1. The measured state, re-verified 2026-09-01

Every figure in this section was checked against this tree today. Where it disagrees with a
document, the disagreement is called out, because a stale number in a good document is the
most expensive kind.

### 1.1 The unit corpus

| | Count | Source |
| --- | ---: | --- |
| Units in the corpus | 1,396 | `research/decomp/data/verification-tier-survey.json` `totals.units` |
| Functions in the corpus | 10,954 | same, `totals.functions` |
| Never attempted | 1,133 | driver `progress/summary.json` `untouched` — **machine-local**, 2026-08-30T06:32Z |
| `red_retryable` | 147 | same, `retryable` |
| Settled `structural_ineligible` | 10 | same, `structural_ineligible` |
| Staged, tier `compile_only` | 103 (ledger) / **112 directories on disk** | same, `staged`; `research/decomp/port-units-staging/` |
| Promoted to `research/decomp/port-units/` | 3 | `collision-core`, `damage-core`, `knockback-core` |
| Recorded at state tier `oracle_green` | **1** (`collision-core`) | driver `wasm-units-state.json` — machine-local |
| In production (`apps/game/public/rom/`) | 1 unit + 1 composed rung-0 artifact | `damage-core.wasm`, `damage-core.threads.wasm`, `composed-rung0.threads.wasm` |

Two reconciliations the reader will otherwise trip on:

- **103 vs 112.** The driver ledger counts 103 staged `green/compile_only` records; the tree
  holds 112 staging directories. Nine of them have no `green/compile_only` state record —
  `auto-c0001-003/004/005/007/010/011/012/014` and `auto-c0025-002`, all `pending` after a
  `manual-revoke` or the `d5-migrate` pass. They are stale staging trees, not inventory.
  [`docs/verification-status.md:391`](verification-status.md) quotes 112; the driver quotes
  103; both are right about different things and neither is a count of ported code.
- **"106 green."** 3 promoted + 103 staged = 106, which is the number the driver's fail-open
  counters print. It is not a count of anything verified. See §2 gap **E6**.

### 1.2 What is actually verified — the whole list

This is not a summary. It is the complete inventory of behavioural evidence in the
repository, as of today.

| Standard | Result | Artifact |
| --- | --- | --- |
| `oracle_green`, reference **`ts_port`** | `damage-core` — 26,232 / 26,232, pass | `oracle-results/damage-core.json` |
| `oracle_green`, reference **`ts_port`**, threads relink | `damage-core.threads` — same verdict, byte-identical delta | `oracle-results/damage-core.threads.json` |
| unit replay, reference **`dolphin_trace`** | `auto-c0020-007` — **partial** (5/8 exports) | `oracle-results/auto-c0020-007.json:107` |
| unit replay, reference **`dolphin_trace`** | `auto-c0001-007` — **partial** | `oracle-results/auto-c0001-007.json:69` |
| unit replay, reference **`dolphin_trace`** | `auto-c0001-005` — **fail** | `oracle-results/auto-c0001-005.json:191` |
| unit replay, reference **`ts_port`** | `auto-c0034-018` — **partial** (1/6 exports) | `oracle-results/auto-c0034-018.json:53` |
| unit replay, reference **`ts_port`** | `auto-c0035-002` — **fail**, `oracle_divergent` | `oracle-results/auto-c0035-002.json:604` |
| `boundary_green` | `run_main_game_loop` — 274/274 calls, 16 iterations, pass | `oracle-results/spine-run-main-game-loop.boundary.json:40` |
| `transcript_green` | **16 functions pass, 3 fail**, across 8 units | 19 `*.transcript.json` artifacts |
| `gx_callstream_green` | `zz_0027c34_` — 4/4 invocations, 124/124 events | `oracle-results/gx-rom-unit.zz_0027c34_.gx-callstream.json:249` |
| `gx_framebuffer_equivalent` | `zz_0027c34_` — 286,720 pixels, 99.80 % within 4/255 | `oracle-results/gx-rom-unit.zz_0027c34_.gx-framebuffer.json:186` |

**The finding that changes how the rest of this document reads.** Grep the
`reference_kind` field across every unit-level artifact and it comes back:

    auto-c0034-018.json  ts_port      auto-c0001-007.json  dolphin_trace
    auto-c0035-002.json  ts_port      auto-c0001-005.json  dolphin_trace
    damage-core.json     ts_port      auto-c0020-007.json  dolphin_trace
    damage-core.threads.json  ts_port

Every unit-level **pass** in this repository is referenced against the TypeScript
recreation, not against the console. Every unit-level artifact referenced against the
**console** is a `fail` or a `partial`. `damage-core.json:20` records
`"reference_kind": "ts_port"` with references
`packages/combat/src/damage/sourceDamage.ts`, and one of its four functions
(`FUN_80031634`) is compared against a "spec-embedded jsRef (JS mirror of the verbatim C;
shares arena/input reads with the wasm)" — the artifact says so itself.

So: **zero units in this repository have reached a full-export-coverage byte-exact PASS
against console-derived evidence.** `damage-core` remains the project's one unambiguous
end-to-end success and it is a *differential against the recreation*, which is exactly the
route [`docs/playable-port-design.md:83-85`](playable-port-design.md) already declared
exhausted for the remaining ~1,300 units. The console-derived evidence that does exist is
16 `transcript_green` functions, one `boundary_green` spine, and two GX results — 19 wasm
functions and one draw, out of 10,954.

`collision-core` and `knockback-core`, both promoted, have **no committed result artifact
at all**; their provenance records a POC harness under
`research/decomp/poc/wasm-port-poc/` and `collision-core`'s own summary is
`"20000/20000, 28121/32153"` — the second measure is 87.5 %, not exact
(`research/decomp/port-units/collision-core/provenance.json`). `knockback-core`'s
provenance carries no `tier` and no `verified` field.

### 1.3 The ceilings

From [`research/decomp/data/verification-tier-survey.json`](../research/decomp/data/verification-tier-survey.json)
(generated 2026-08-30, input digests bound in the artifact). **This is eligibility, not
progress** — claim-honesty rule 6, [`docs/verification-status.md:429`](verification-status.md).

| | Functions | Share |
| --- | ---: | ---: |
| `oracle_green`-eligible (auto-derivable write-comparison spec) | 652 | 6.0 % |
| `transcript_green`-eligible | 8,197 | 74.8 % |
| **Verifiable by some tier** | **8,849** | **80.8 %** |
| Unverifiable — ROM function-pointer dispatch | 1,602 | 14.6 % |
| Unverifiable — empty transcript | 503 | 4.6 % |

Per unit, requiring full export coverage: **2** units all-`oracle_green`-eligible, 257
all-`transcript_green`-eligible, 119 mixed, **378 (27.1 %)** with full coverage at any
tier, **1,018 (72.9 %)** with at least one export no standard can reach.

The graphics ceiling is separate and permanent: **"framebuffer-equivalent, never
pixel-identical"** ([`docs/playable-port-design.md:412-414`](playable-port-design.md),
restated [`docs/verification-status.md:312`](verification-status.md)).

### 1.4 Composition and execution

- Ladder ceiling: **rung 1, N=10**, passed clean — `substitution: null`, `conflicts: []`,
  `new_contested / new_linked = 0 / 38`, 78 companion thunks, checked 2026-08-29
  ([`research/decomp/data/composition-ladder.json`](../research/decomp/data/composition-ladder.json);
  [`docs/composition-ladder.md:14-18`](composition-ladder.md)).
- Rung 2 is **not reached**. Its blocker is now rebuild scheduling, not ABI:
  "Rung 2 is now a rebuild-scheduling problem rather than an owner decision"
  ([`docs/composition-ladder.md:580`](composition-ladder.md)), waiting on rebuilds of
  `auto-c0011-012` then `auto-c0011-011` (`:527-530`, `:571-574`), with the doc warning the
  window "may well surface another placeholder of the `zz_007c844_` shape after that"
  (`:578-581`).
- The in-driver assembly gate ledger still reads `largest_n_passed: 5`, last updated
  **2026-08-21** (`research/decomp/data/assembly-gate.json`). The ladder runner is a
  separate scratch-only tool (`scripts/composition_ladder.py`) that never touches live
  driver state; the two ledgers are not synchronised and the ladder's is the current one.
- Contested symbols in the knowledge registry: **88** (machine-local; was 81 when
  [`docs/playable-port-design.md:356-357`](playable-port-design.md) measured it).
- Static ABI-disagreement instrument on the 82-unit pool: 0 at N=5, 0 at N=10, then **27 at
  N=20, 42 at N=40, 57 at N=80, 61 at N=82** ([`docs/composition-ladder.md:423-425`](composition-ladder.md)).
- The composed-module dispatch pilot **passed** and is served from
  `apps/game/public/rom/composed-rung0.threads.wasm`: 40-thunk dispatch table, 31 declared
  out-of-window imports all bound, 16/16 frames, 80 bridged crossings at exactly 5/frame, 0
  servicing errors, a reentrant invoke returning a value the ROM's own code computed
  (−42 from seeded floats) ([`docs/composed-pilot.md:148-151`](composed-pilot.md), `:100-107`).
- **Control inversion has never run.** "The pilot drives the *inverse* of control
  inversion and says so" ([`docs/composed-pilot.md:21`](composed-pilot.md)); the
  requirement table marks "Composed module drives the frames" **NOT met — the host drives**
  (`:36`). `run_main_game_loop` is not linked into any window.
- Shared memory is fixed at **2,155,479,040 bytes** (32,890 pages, initial == maximum,
  `ALLOW_MEMORY_GROWTH=0`) so the GC arena sits at original addresses; "This is not a
  tuning knob" ([`docs/composed-pilot.md:154-160`](composed-pilot.md)). It allocates in
  ~2 ms in headless Chrome (`:162-170`).
- Cross-origin isolation is built and gated: `apps/game/public/coi-serviceworker.js`,
  `scripts/smoke-coi-phase.mjs`, `apps/game/vite.config.ts`. V5 step 6 has landed.
- **One document is stale and should be corrected.** The repository root
  [`README.md`](../README.md) says of `@gf/rom-runtime`: "**nothing in `apps/game` imports
  it yet**. It is not on the production path." It is:
  `apps/game/src/main.ts:20` imports `bootComposedModule` and `onGameFrame` from
  `./rom/composedBoot`, which imports `@gf/rom-runtime`, and
  `apps/game/src/rom/composedWorker.ts:14` imports `installRomRuntimeWorker`. The composed
  runtime **is** on the production path as of the composed pilot. This is drift, not a
  disagreement about substance, and it is exactly the class of error §1 exists to catch.

### 1.5 The host at the SDK seam

| Surface | Coverage | Verification |
| --- | --- | --- |
| GX | 49/76 entry points `translated`, **437/502 static call sites = 87.1 %** ([`docs/gx-hle-host.md:227`](gx-hle-host.md)) | **0 / 56 adapters** at `evidenceClass: "verified"` ([`docs/gx-hle-host.md:740`](gx-hle-host.md)); 16/76 entry points seam-compared; 1 draw rasterization-compared |
| DVD | 9/15 entry points, **33/41 static call sites = 80.5 %** ([`docs/audio-dvd-hle-host.md:246`](audio-dvd-hle-host.md)) | **0** — "There is no DVD trace, no audio capture, no reference" (`:602`) |
| Audio, bridged seam | 5/5 entry points, 6/6 call sites (`:305`) | 0 |
| Audio, in-window MMIO | **34 of 40 call sites do not cross the seam** (`:265`) | 0 |

Three facts from those documents that no coverage percentage expresses:

1. **The GX host throws on a real battle frame.** Over 32.2 s of a live 2v2 the ROM made
   **507 calls to entry points the host does not implement**, each of which its
   loud-unimplemented adapter throws on; `GXSetFog` alone is 220 of them while ranking 45th
   by static call sites ([`docs/gx-hle-host.md:870-883`](gx-hle-host.md)). "A host that
   throws on `GXSetFog` cannot render one frame of a battle" (`:953`).
2. **The audio mixer does not exist and cannot be ported.** Gotcha Force mixes in MusyX
   microcode on the GameCube DSP; that microcode "is not PowerPC code, is not in the DOL's
   text", is uploaded over a mailbox as a blob, and "There is nothing here to translate"
   ([`docs/audio-dvd-hle-host.md:42-46`](audio-dvd-hle-host.md)). "This host can carry a PCM
   buffer to the speakers; it cannot fill one" (`:46`). A composed module running today
   DMAs silence.
3. **The assembly gate does not lower AI/DSP MMIO.** `port_wgpipe_lowering.py` covers the
   `0xCC008000` write-gather-pipe window and only that window; the audio ROM-unit fixture
   applies the equivalent rewrite by hand, disclosed as `AI_MMIO_NOT_GATE_LOWERED`
   ([`docs/audio-dvd-hle-host.md:130-135`](audio-dvd-hle-host.md), `:540-542`). Every
   in-window audio access to `0xCC0050xx` / `0xCC006Cxx` in a real gate-built module is
   out of bounds of the 0x807A0000-byte memory and traps (`:123-125`).

### 1.6 Capture coverage and the evidence machinery

- Capture plans exist for **all 810 exports of the 103 staged units** (commit `5f016850`;
  847 files in `research/tools/dolphin-trace/plans/`). Of those 810:
  **598 capturable, 168 refused for ROM function-pointer dispatch, 43 for an empty
  transcript, 1 for an unnamed SDK site**
  ([`research/decomp/data/transcript-work-queue.json`](../research/decomp/data/transcript-work-queue.json)).
- **Only 10 of the 103 staged units have every export capturable.** 44 units scouted; 34
  exports measured firing; 25 both capturable and firing (same artifact, `totals`).
- **Zero of the 103 staged units have every export both capturable and measured firing.**
  Computed from the same artifact (§10). No staged unit can reach full-coverage
  `transcript_green` from what has been scouted.
- Coverage authorship is no longer purely an owner input. `research/tools/dolphin-trace/force_navigator.py`
  generates scenarios autonomously: **42 scenario files exist and every one records
  `"dtm": null`**, driven instead by a savestate plus synthesized pad input plus, for the
  battle-roster family, writing a chosen borg into the game's own slot table and rewinding
  the battle phase machine (`research/tools/dolphin-trace/scenarios/battle-roster-0x801a10e8.json`).
  This materially changes design gap G4 ([`docs/playable-port-design.md:387-406`](playable-port-design.md)),
  which recorded DTM authorship as a standing human dependency. **There are no `.dtm` files
  anywhere in the tree.**
- The scenario set is 39 `battle-roster-*`, 2 `battle-2v2-*` and 1 `title-attract`. The
  work queue references 33 distinct scenarios and **every one of them is a battle**.
  Menus, shop, save, the Challenge flow and the non-battle half of the game have no
  scenario that any queued export uses.
- **Captures are not replayable.** `research/tools/dolphin-trace/README.md:76-79`:
  captures ride savestate plus synthesized input and are "**non-deterministic across
  runs** (each capture is a fresh sample, not a replayable trace)". The repository root
  [`README.md:265-267`](../README.md) states the same: "**No DTM movie exists.** The
  design's coverage prerequisite (G4/I3) is **unmet**". This is load-bearing for §5 **X2**.
- The rig **cannot write a savestate**: `--save_state` is load-only, `keybd_event` /
  `SendInput` produce no key state, `GetForegroundWindow()` returns 0 — "there is no
  interactive input desktop to inject into"
  (`research/tools/dolphin-trace/README.md:81-93`). New savestates are an owner input.

### 1.6a Measured capture cost — the unit of work is one emulator boot

Every number here is from `research/tools/dolphin-trace/README.md` unless noted.

| Quantity | Measured | Cite |
| --- | --- | --- |
| Frame rate under a breakpoint loop | one frame per 0.2–0.3 s wall, "roughly **15x slower than real time**" | `:56`, `:110` |
| Stub session lifetime | "**about 40 s** … or a few hundred breakpoint stops, whichever comes first" | `:103-107` |
| Stub connections per boot | **one** — "The stub never re-listens after its single client disconnects" | `:57-60` |
| Dolphin relaunch with a savestate | ~15 s | `:60` |
| Roster-reload scenario setup | ~45 s per launch | `research/tools/dolphin-trace/transcript_sweep.py:9-11` |
| `oracle_green` capture | ~25 s for 120 cases | `:137` |
| `boundary_green` spine capture | ~21 s for K=16 (274 calls) | `:382`, `:425` |
| Offline plan derivation (`sites`) | model-free, ~0.5 s per export | `:556` |
| Scout yield | 90 s over 201 callee-free staged functions → **2 fire** | `:116-120` |
| Scout yield, roster scenarios | 5 of 33, 10 of 64, 18 of 62 | `:625-627` |

So the unit of capture work is **one export per emulator boot**: ~15 s relaunch + up to
~45 s scenario setup + a ≤40 s usable stub window, yielding ~24 cases. Sweeping the 598
capturable staged exports at one boot each is therefore on the order of **17 Dolphin-hours**
of pure capture — **ESTIMATE**, derived by multiplying 598 × ~100 s — before any scouting,
any re-capture, and any of the failure modes in §2.4.

The README's own conclusion about where the cost really is:
"growing capture coverage is a **game-state authoring problem** … not a tooling problem"
(`:116-120`).

### 1.7 The promotion pipeline is currently a no-op

This was measured against the driver checkout (`D:\GotYaForce\research\tools\OGhidra`,
unvendored) and it is the single most consequential structural fact in this document.

The only code path that flips a unit's tier is `_reverify_unit_inner`
(`src/port_wasm_units.py:5779`). Its chain of preconditions:

1. `_verification_candidates` returns `[]` immediately if the oracle sidecar is empty
   (`src/port_wasm_units.py:5714-5716`), and skips any unit with no sidecar entry (`:5721-5723`).
2. A sidecar entry is required and validated (`:5796-5801`), and its `exports_sha256` must
   match the staged artifact's provenance export set (`:5802-5809`).
3. A sidecar entry can only be built by `build_sidecar_entry` (`src/port_trace_verify.py:391`)
   from a full-coverage PASS under `eligible_for_oracle_green` (`src/port_trace_verify.py:337-388`)
   — fail-closed on verdict, export coverage, per-function verdict, `unexplained == 0`, and
   a coverage audit.
4. That PASS can only come from `run-unit.mjs`, which **requires a hand-authored spec
   module**: `research/decomp/oracle-harness/run-unit.mjs:98-100` fails with
   `no spec module at …` if `specs/<unit>.spec.mjs` is absent.

Measured today:

- **6 spec modules exist** (`research/decomp/oracle-harness/specs/`): `auto-c0001-005`,
  `auto-c0001-007`, `auto-c0020-007`, `auto-c0034-018`, `auto-c0035-002`, `damage-core`.
- **3 of the 103 staged compile-only greens have one** — `auto-c0020-007` (PARTIAL, 5/8
  exports), `auto-c0034-018` (PARTIAL, 1/6), `auto-c0035-002` (FAIL, `oracle_divergent`).
  None can promote. The other two spec'd units are `pending`, not staged.
- **The sidecar `research/decomp/data/oracle-commands.json` contains exactly one unit** —
  `damage-core`, which is not a staged compile-only green.

Therefore `_verification_candidates` returns `[]` on every driver pass. **The driver's
verification lane has never had a candidate and cannot acquire one without a hand-authored
spec.** Spec emission is only partly automatable: `src/port_spec_emit.py` classifies an
export `human` if the plan is unvalidated, or it makes an indirect call, or it calls any
external ROM `zz_*` callee, or it calls a `gnt4_*` helper with no vetted shim, or its
declared write set is empty, or a declared write has no pre-state in the read set
(`:147-190`) — and `port_spec_emit.py` is **not imported by the driver at all**; it is an
operator-run offline tool.

And the weaker standard that covers the majority does not exist in the driver:
`transcript_green` appears **12 times in the whole OGhidra checkout, all of them inside
`tools/survey_plan_tiers.py`**; `boundary_green` appears nowhere. `src/port_trace_verify.py:73`
hardcodes `HARNESS_ENTRY = "run-unit.mjs"`, and `validate_oracle_entry`
(`src/port_wasm_units.py:1208`) requires the sidecar's first pattern to be the `ORACLE TOTAL`
line. **A transcript result cannot convert a unit in the ledger today**, which is why the
16 passing `transcript_green` functions moved the ledger by zero.

### 1.8 Throughput

Machine-local, computed from `research/decomp/generated/finish-game-port/events.jsonl`
(§10 shows the command):

- 457 `wasm_unit_started`, 272 `wasm_unit_red`, **138 `wasm_unit_green`** between
  2026-08-10 and 2026-08-26. Green rate ≈ **30 %** of starts.
- Per-day greens: 2, 1, 6, 7, **37**, 2, **27**, **36**, 10, 10. Peak 37/day; mean over the
  ten days with any green ≈ 13.8/day.
- **Last green: 2026-08-26T07:34Z.** The driver has produced nothing since. Current state:
  `driver_status: "stopped"`, `workflow_state: "leased-out"`, detail "GPU leased to
  omr-sweep (priority 1)".
- `verified_fraction_mark` in live driver state: `{verified: 1, staged: 106, fraction: 0.0093}`.

### 1.9 What is playable today

The browser build is a real vertical slice, not a mock-up: a live Chromium run went
**Title → Challenge → Normal → 1P → Load Box → Select Force → Battle Intro → rendered
battle HUD** with no console errors, and a production bundle builds and serves under
`/GotYaForce/game/`; the audit's conclusion was "to repair and gate it, not replace it"
([`docs/audits/game-app-defect-ledger.md:24-27`](audits/game-app-defect-ledger.md)). Exactly
one ROM-derived unit participates: `damage-core`, behind the seam described in
[`docs/playable-port-design.md:112-124`](playable-port-design.md).

Its regression net has a hole worth stating here because §4 depends on that net: roughly
120 assertions in `packages/combat/src/selfcheck.ts` have no runner, and **18
`scripts/run-*.mjs` runners are absent from every `package.json` script**
([`docs/audits/game-app-defect-ledger.md`](audits/game-app-defect-ledger.md) §3.1).

---

## 2. The gap inventory

Every gap between today and "a person plays this and it behaves as the GameCube game".
Grouped by kind, each with its measurement, its evidence, and whether it blocks the
critical path.

Three of these classes are **not** gaps in the ordinary sense — they are ceilings. They are
marked ∞ and they do not close; §8 is where they are converted into claim language instead.

### 2.1 Class E — Evidence

| ID | Gap | Measurement | Evidence | Blocks critical path? |
| --- | --- | --- | --- | --- |
| **E1** | No unit has a console-derived full-coverage byte-exact PASS. Every unit-level pass is `ts_port`-referenced; every console-referenced unit artifact is fail or partial. | 3 `ts_port` passes, 3 `dolphin_trace` results (1 fail, 2 partial) | §1.2; `reference_kind` grep | No — blocks the **claim**, not play |
| **E2** ∞ | 19.2 % of functions have no route to any standard: 1,602 dispatch through a ROM function-pointer table, 503 have an empty transcript. | 2,105 / 10,954 | `verification-tier-survey.json`; [`verification-status.md:132-141`](verification-status.md) | No — ceiling |
| **E3** | The staged corpus cannot convert. Zero of 103 staged units have every export both capturable and measured firing; only 10 have every export capturable at all. | 598/810 capturable; 10 units full-plan; 0 units full-and-firing | `transcript-work-queue.json` | No — blocks the claim |
| **E4** | The stack-local-pointer argument class reds captures that are otherwise correct: the console passes its frame address, the port passes its wasm linear-stack address, and arguments compare by value. | **56 of the 598 capturable staged exports, across 39 units** | commit `612a1934` message; `oracle-results/auto-c0020-007.zz_00c44a8_.transcript.json` divergence | No — blocks the claim |
| **E5** | Promotion requires a hand-authored per-unit spec. 6 exist; 3 belong to staged units; all 3 record PARTIAL or FAIL. The sidecar holds 1 unit. The driver's verification lane returns `[]` every pass. | 6 specs / 1,396 units | §1.7, with driver `file:line` | **Yes** for the claim track; no for play |
| **E6** | The driver has no `transcript_green` or `boundary_green` tier, so 16 passing console-derived function results converted nothing. Two counters are additionally **fail-open on tier** and would silently inflate `queue.green`, the README table and the rig contract probe the moment a new tier is recorded. | `transcript_green` appears 12× in OGhidra, all in `tools/`; `boundary_green` 0× | §1.7; `src/port_contract.py:125`, `src/port_progress.py:209`; [`verification-status.md:440-470`](verification-status.md) | **Yes** for the claim track |
| **E7** | Proven corpus corrections cannot land. `auto-c0020-007/FUN_800c4468` replays **24/24 cases, 48/48 calls green** from corrected source in `research/decomp/transcript-preflight/`, and the staged artifact still reds "because the driver is paused and cannot rebuild it". | 1 proven fix stalled | commit `612a1934` message; `research/decomp/transcript-preflight/auto-c0020-007-FUN_800c4468/` | **Yes** — a stalled correction loop stops both tracks |
| **E8** | Coverage authorship covers one third of the game. All 33 referenced scenarios are `battle-roster-*` / `battle-2v2-*`. No scenario reaches menus, shop, save, attract, the Challenge flow, or the 200+ borgs outside the scouted families. | 44 scenario files, 0 non-battle | `research/tools/dolphin-trace/scenarios/` | **Yes** for the claim track |
| **E9** | The `oracle_green` standard is *empty*, not hard, for 40.7 % of functions — 4,455 store nothing a capture could compare, and a spec over them passes vacuously. This already happened in the wild (15/15 on `"reads": [], "writes": []`). | 4,455 / 10,954 | [`verification-status.md:120-122`](verification-status.md), §4 | No — a design fact the plan must respect |
| **E10** | **Captures are not replayable and no DTM exists**, so the design's own frame-boundary state-evidence gate (V5 I1, step 9) — "the shared arena matches a Dolphin trace of the same DTM at each frame boundary" — has no input that could satisfy it. | 0 DTM files | `research/tools/dolphin-trace/README.md:72-80`; [`playable-port-design.md:745-751`](playable-port-design.md) | **Yes** — it makes the design's strongest gate unpassable as written |
| **E11** | The decompiled corpus carries a systematic mis-lift at scale: Ghidra's varargs-assert prefix (`undefined8` + seven invented `double`s) is on **1,514 of 10,954 registry functions**, 809 of them with 16 parameters, **48 of those inside 23 of the 103 staged units**. The same class is uncorrected on `start` `@0x80003154` and "will matter at whole-program link". | 1,514 / 10,954 | commit `6499c285` subject; `research/tools/dolphin-trace/README.md:521-529` | **Yes** — for both tracks |

### 2.2 Class C — Composition and execution

| ID | Gap | Measurement | Evidence | Blocks critical path? |
| --- | --- | --- | --- | --- |
| **C1** | The composition ladder is at N=10 of 1,396 and its next rung is blocked on two artifact rebuilds that require the driver to run. | rung 1, ratio 0/38 | `composition-ladder.json`; [`composition-ladder.md:576-581`](composition-ladder.md) | **Yes** |
| **C2** | **The ladder selects by recency, not by call graph.** A rung is "the LAST n eligible units, oldest-first link order". Doubling a recency window will never link `run_main_game_loop` or its spine, and the spine is the prerequisite for control inversion. | selection rule | [`composition-ladder.md:49-51`](composition-ladder.md); H2 gate (a), [`playable-port-design.md:552-555`](playable-port-design.md) | **Yes — this is the deepest structural gap on the playability track** |
| **C3** | Control inversion has never run. The host calls the composed module once per rendered frame; the module does not drive. | pilot requirement table: 5 rows NOT met | [`composed-pilot.md:24-37`](composed-pilot.md) | **Yes** |
| **C4** | The spine's `boundary_green` is thin. With the ABI corrected there are **zero argument slots to compare**, and the single owned region (`0x80436190`, 4 bytes) held `00000000` at all 274 boundaries — the entire verdict rests on one call sequence. | 274/274 calls, 0 args, 1 invariant region | [`verification-status.md:196-203`](verification-status.md) | No — but it caps what H2 gate (a) is worth |
| **C5** | The composed pilot's adapters are synthetic. No DTM capture exists for `zz_0085e00_`, `zz_008aff0_`, `zz_006de10_`; two are hand stubs and the third runs `TraceDeltaAdapter` against a synthetic fixture, which "proves nothing about what the ROM writes". The frame check is against a declared expectation: "It catches a broken bridge; it cannot catch a wrong port." | 3 adapters, 0 trace-derived | [`composed-pilot.md:210-249`](composed-pilot.md) | **Yes** for the I1 state-evidence gate |
| **C6** | Every unit entering the composed lane has its verification **suspended** by the threads relink and needs a per-unit base-proof → relink → full-corpus replay → artifact pass. Only `damage-core` has passed one. | 1 of 1,396 | [`threads-relink-reverify.md:4-9`](threads-relink-reverify.md), `:123-129` | Deferred — see §5 **X7** |
| **C7** | Shared memory is a fixed 2,155,479,040-byte committed allocation with growth disabled, proven only in headless Chrome on the rig. No measurement exists on any other browser, on a low-RAM machine, or on mobile. | 32,890 pages, initial == maximum | [`composed-pilot.md:154-170`](composed-pilot.md) | **Yes** for shipping |
| **C8** | H3's uniform dispatch ABI converts signature traps into **silent mis-marshalling**, against a registry carrying 88 contested symbols. PPC register-residue reads are a known unreproducible class. | 88 contested (machine-local) | [`playable-port-design.md:877-884`](playable-port-design.md) | Risk, not a blocker |
| **C9** | Static ABI disagreement rises steeply past the current rung: 0 at N=10, then 27 at N=20, 42 at N=40, 57 at N=80, 61 at N=82 on the 82-unit pool. The ladder's E1 budget is a *rate* rule and the rate is about to move. | 27 → 61 | [`composition-ladder.md:423-425`](composition-ladder.md) | **Yes** |

### 2.3 Class H — The host at the SDK seam

| ID | Gap | Measurement | Evidence | Blocks critical path? |
| --- | --- | --- | --- | --- |
| **H1** | GX throws on a real battle frame: 507 calls in 32.2 s to unimplemented entry points, fog first at 220. | 507 / 32.2 s | [`gx-hle-host.md:870-883`](gx-hle-host.md) | **Yes** |
| **H2** | Whole missing GX mechanisms: no EFB model or `GXCopyTex` (confirmed live), no per-vertex position matrices so "Nothing about character geometry can be right until this exists", no post-transform texture matrices though **20 of 21** observed `GXSetTexCoordGen2` calls name one, no fog, no mipmaps, no scissor, no indirect texturing, no batching. | 8 named mechanisms | [`gx-hle-host.md:700-725`](gx-hle-host.md), `:897-899`, `:982-987` | **Yes** |
| **H3** ∞ | The graphics boundary's ceiling is framebuffer-equivalent, never pixel-identical. EFB copy semantics, fixed-point rasterization, 24-bit depth compare, texture filter kernels and TEV signed-10-bit rounding all differ from Flipper. Translating more of the pipeline moves toward the ceiling; it does not raise it. | permanent | [`verification-status.md:312-317`](verification-status.md) | No — ceiling |
| **H4** ∞ | **Audio has no mixer.** The MusyX microcode is not PowerPC, is not in the DOL, and arrives as a mailbox blob. A composed module DMAs silence. Nothing in the porting pipeline can address this, by construction. | whole subsystem | [`audio-dvd-hle-host.md:42-51`](audio-dvd-hle-host.md), `:154-155`, `:592` | **Yes** — and only an owner scope decision closes it |
| **H5** | The assembly gate does not lower AI/DSP MMIO. 34 of 40 audio call sites are in-window MMIO to `0xCC0050xx`/`0xCC006Cxx`, which are out of bounds of the module's memory and trap. The audio fixture hand-applies the rewrite. | 34/40 sites, 18 registers, 403 reads / 342 writes | [`audio-dvd-hle-host.md:122-135`](audio-dvd-hle-host.md) | **Yes** |
| **H6** | ARAM DMA is stored and not performed — the busiest audio registers in the corpus at 247 reads / 251 writes — and the AI DMA interrupt is queued, not timed: "Nothing paces it at 5 ms." | 3 registers, 498 accesses | [`audio-dvd-hle-host.md:341-346`](audio-dvd-hle-host.md), `:596` | Follows H4 |
| **H7** | DVD: 0 % verified, no disc bytes in the repository (`research/disc/` holds one `.gitkeep`), the timing model is knowingly wrong (reads complete inside the adapter call so the ROM's spin loops exit on iteration 1), and 2 entry points are unimplemented — one of which the ROM's **boot path branches on**. | 0 % / 2 EPs | [`verification-status.md:319-339`](verification-status.md); [`audio-dvd-hle-host.md:579-584`](audio-dvd-hle-host.md) | **Yes** |
| **H8** | There is no SDK shim ledger. 996 `gnt4_*` functions are excluded by design, the corpus references at least 68 entry points, the seed declares 6, staged units declare 17, and 6 conflict — including a real f64/i64 split on `gnt4_PSMTXConcat_bl`. | 6 seeded / 17 declared / 6 conflicting | [`playable-port-design.md:191-198`](playable-port-design.md); [`audits/port-pipeline-integrity.md:632-651`](audits/port-pipeline-integrity.md) | **Yes** |
| **H9** | Every GX `[SDK]` enum that has not been settled by the console is still a guess, and the concentration of risk is named: "Every observed texture is `CMPR`", whose texel bit layout "carries essentially all of the risk". | 20/20 observed textures | [`gx-hle-host.md:904-907`](gx-hle-host.md) | Risk |

### 2.4 Class P — Pipeline and hardware

| ID | Gap | Measurement | Evidence | Blocks critical path? |
| --- | --- | --- | --- | --- |
| **P1** | 1,133 units have never been attempted, and the driver is stopped with the GPU leased away. Last green 2026-08-26. | 1,133 untouched | driver `summary.json` (machine-local) | **Yes** |
| **P2** | Compile throughput is 30 % of starts (138 green / 457 started) with a peak of 37/day. | measured over 17 days | `events.jsonl` (machine-local) | Rate, not blocker |
| **P3** | Capture and compile contend for one GPU. Dolphin held D3D11 while the port ran; a paused supervisor actively unloads any model you load. | rig policy | [`playable-port-design.md:106-108`](playable-port-design.md); [`AGENTS.md`](../AGENTS.md) | **Yes** — scheduling constraint |
| **P4** | Dolphin stub sessions are short: reset after ~40 s or a few hundred breakpoint stops; the GDB stub refuses the hardware window (`m cc00201c,4` → `E00`); the video backend string must be exactly `Software Renderer` or both XFBs read back all zero. | measured | [`gx-hle-host.md:922-940`](gx-hle-host.md) | **Yes** — caps capture design |
| **P5** | Known driver defects §7.1–7.10 of the integrity audit were recorded 2026-08-21…23 and **none was re-verified on 2026-08-29**. They include "'Verbatim / byte-faithful C' is false at both boundaries", a regex import scanner, and queue eligibility that ignores runtime-semantic dependencies. | 10 findings, unverified | [`audits/port-pipeline-integrity.md:452-456`](audits/port-pipeline-integrity.md) | Risk |
| **P6** | Three capture-machinery defects that manufacture **false negatives**: `capture_oracle.py stop` does not reap orphan Dolphins, and "a run that overlapped them recorded several zero-case corpora that looked like 'the function never fired'"; a `verify-unit` with capture rewrites per-export fixtures **without re-merging**, so a spec can replay a stale corpus; and `--wasm-rel`/`--arena-rel` still default to the literal placeholder `UNIT`, so a corpus written without them dies at replay with ENOENT. | 3 defects, all open | `research/tools/dolphin-trace/README.md:619-627`, `:260-270`, `:575-579` | **Yes** — a false negative is worse than no result |

### 2.5 Class S — Product and scaffold

| ID | Gap | Measurement | Evidence | Blocks critical path? |
| --- | --- | --- | --- | --- |
| **S1** | The shrink metric the design promised — bridged calls per frame falling as the ladder grows — has never fallen, because nothing has been linked into the loop. It stands at exactly 5/frame in the only measurement. | 5/frame, 16 frames | [`composed-pilot.md:98`](composed-pilot.md), `:148-151` | **Yes** — it is the convergence signal |
| **S2** | The regression net protecting the scaffold while it shrinks is partly dark: ~120 assertions with no runner and 18 `run-*.mjs` runners wired into no `package.json` script. | 18 runners | [`audits/game-app-defect-ledger.md`](audits/game-app-defect-ledger.md) §3.1 | **Yes** — you cannot safely shrink what you cannot regression-test |
| **S3** | A `compile_only` unit can be behaviourally wrong and still read green. `auto-c0035-002` is byte-exact on 6,250 of 20,000 cases and is *still recorded as a green `compile_only` unit*; `auto-c0001-005` was proven wrong by the console. | 2 proven-wrong units of 5 examined | [`verification-status.md:41-44`](verification-status.md); [`corpus-correction-loop.md`](../research/decomp/corpus-correction-loop.md) | **Yes** — this is what §4's liveness gate exists for |

### 2.6 Ranking

**Blocks a playable ROM-driven build** (in dependency order): E7/P1/P3 → E11 → C2 →
C1/C9 → H5 → H1/H2 → C3 → C7 → H7 → H4 (scope decision) → S1/S2.

**Blocks the 1:1 claim but not play**: E1, E3, E4, E5, E6, E8, E10, C4, C5, H8, H9, P6.

**Does not close** (∞): E2, H3, and H4 in any form a porting pipeline can reach.

The two lists barely intersect. That is the central observation of this document and §3
and §4 are built on it:

> **Verification is not on the critical path to playability. It is the critical path to the
> CLAIM.** The assembly gate accepts `compile_only` units — `ELIGIBLE_CANONICAL_TIERS =
> frozenset({"compile_only", "oracle_green"})`, `src/port_assembly_gate.py:1025` — so the
> composed module can grow, link, and run on inventory that carries no behavioural claim at
> all. The V5 order of work interleaves the two tracks and gates several playability steps
> on verification milestones (step 7's prerequisite is a `boundary_green` spine; step 4's
> composed pilot sits ahead of the ladder at step 12). Running them as one serial chain
> means the playability track inherits the evidence track's asymptote, and §1.7 shows that
> asymptote is currently a **no-op**.

This does not license shipping unverified code as a port. §5 **X8** is where that tension
is attacked, and §8 is where it is resolved in claim language.

---

## 3. Options

For each gap that materially moves the outcome: at least two candidate solutions, honest
pros and cons, a cost in the units this project measures, what each would **prove** versus
merely **produce**, and a recommendation.

Cost units, with their measured anchors:

- **agent-session** — one orchestrated session. No repository measurement exists for
  session throughput; every session figure below is an **ESTIMATE** and is marked.
- **Dolphin-hour** — emulator capture wall clock. Anchor: one export per boot at ~100 s
  (§1.6a). Mutually exclusive with GPU-hours (P3).
- **GPU-hour** — local LLM serving. Anchor: 138 greens / 457 starts over 17 days; peak
  37/day; mean 13.8/day across days with any green (§1.8).
- **corpus correction** — one sanctioned chunk edit + revoke + natural rebuild
  ([`corpus-correction-loop.md`](../research/decomp/corpus-correction-loop.md)). Anchor:
  3 landed to date, one of which is still stalled (E7).
- **hand-authored artifact** — a spec, an adapter, a scenario, a shim. Anchor: 6 specs,
  3 pilot adapters, 42 scenarios, 6 seeded shims.

### 3.1 C2 — the composition ladder cannot converge on a runnable module

**The gap.** A rung is "the LAST n eligible units, oldest-first link order"
([`composition-ladder.md:49-51`](composition-ladder.md)). Doubling a recency window
produces a bigger arbitrary bag of units. It will never contain `run_main_game_loop`
(`0x800527d8`), which H2 gate (a) makes a hard prerequisite of control inversion: "A
composed module driven by anything other than the ROM's own loop has not inverted control"
([`playable-port-design.md:552-555`](playable-port-design.md)).

**Option A — keep recency, grow to N=1,396.** Let the ladder run to completion; the spine
arrives when everything arrives.

- *Pros:* zero new mechanism; the E1 budget rule already governs it; the existing runner
  works unchanged.
- *Cons:* the static disagreement instrument says the window breaks long before then —
  27 conflicts at N=20, 42 at N=40, 57 at N=80, 61 at N=82 on the 82-unit pool
  ([`composition-ladder.md:423-425`](composition-ladder.md)) — and the pool is 82 of 1,396.
  It also requires all 1,133 untouched units to compile first.
- *Cost:* ~82 driver-days of GPU at the 13.8/day mean for the untouched units alone
  (**ESTIMATE** from §1.8), plus an unbounded ABI-unification programme.
- *Proves:* nothing until the very end. *Produces:* a monotonically growing conflict count.

**Option B — re-point the ladder at the boot-to-battle call graph (recommended).** Replace
`select_recent_green_units` with a **spine-rooted frontier**: start from
`run_main_game_loop` and take the units containing its direct callees, then their callees,
breadth-first. Growth is measured not by N but by **bridged calls per frame** — the metric
H2 already defined and S1 says has never moved.

- *Pros:* it is the only selection rule whose limit is a running game. It converts the
  ladder's success metric into the design's own shrink metric. It makes the units the
  driver should compile next *derivable* rather than arbitrary, which also re-points
  `unit-priority.json`. The host bridge (H2) already makes a partial window runnable, so
  the frontier does not have to be closed to be useful.
- *Cons:* the frontier is not small — the flow table routes every per-frame entry through
  the spine ([`playable-port-design.md:274-277`](playable-port-design.md)) — so the first
  frontier ring may itself exceed any N the gate has linked. It also breaks the E1 budget's
  comparability, because a spine-rooted rung and a recency rung are not the same
  population; the budget formula has to be restated per-frontier-ring and the restatement
  written into the design doc, per E1's own revision rule
  ([`playable-port-design.md:611-621`](playable-port-design.md)).
- *Cost:* 1 agent-session to derive the frontier from `oracle-registry.json` +
  `start-code-flow.md` and emit a `spine-frontier.json` ranking; 1–2 agent-sessions to
  re-point the ladder runner and `unit-priority.json` generator (**ESTIMATE**). No new GPU
  or Dolphin cost.
- *Proves:* that the composed module is on a path to running the game.
  *Produces:* a work queue whose exhaustion is the terminal state.

**Option C — skip the ladder; link the spine window directly.** Build one hand-chosen
window: the spine plus its 17 loop-body callees
([`playable-port-design.md:980-983`](playable-port-design.md)), bridging everything else.

- *Pros:* fastest route to a control-inversion attempt; the smallest window that can
  possibly satisfy H2 gate (a).
- *Cons:* it skips the ABI-unification signal the ladder exists to produce, which is the
  mistake G3 was written to prevent ([`playable-port-design.md:352-370`](playable-port-design.md)).
  Several of those callees are almost certainly not compiled, and the units containing them
  are not known to be gate-eligible.
- *Proves:* control inversion is or is not achievable at all. *Produces:* one window.

**Recommendation: B, with C as its first ring.** Re-point the selection rule, and make the
spine-plus-loop-body window the *first* frontier ring so that Option C's fast answer is
obtained inside the mechanism rather than beside it. Record the restated budget formula in
`playable-port-design.md` before the first spine-rooted rung runs.

### 3.2 E5 + E6 — the promotion machinery is a no-op

**The gap.** §1.7. The verification lane returns `[]` every pass; promotion needs a
hand-authored spec; 6 exist; the driver has no tier in which to record the one standard
that covers the majority.

**Option A — author specs.** Write `specs/<unit>.spec.mjs` by hand for staged units.

- *Pros:* it is the existing, reviewed, fail-closed path; a pass through it is the
  strongest claim this project has (`oracle_green`, full export coverage).
- *Cons:* `port_spec_emit.py:147-190` classifies an export `human` if the plan is
  unvalidated, or it calls **any** external ROM `zz_*` callee, or any unshimmed `gnt4_*`
  helper, or its declared write set is empty. Per the survey that is most of the corpus:
  652 functions (6.0 %) are auto-derivable and **2 units** have every export so. The
  remaining specs are per-unit human reasoning that "a template cannot do" (`:163-167`).
  And the ceiling is brutal: even perfect spec authoring caps at 2 units at
  `all_exports_oracle_green`.
- *Cost:* the three staged units that already have specs record PARTIAL/PARTIAL/FAIL, so
  the marginal spec buys a partial. **ESTIMATE**: ≥1 agent-session per unit for HUMAN-tier
  exports; 1,396 units ⇒ not a plan.
- *Proves:* byte-exact write-set equality. *Produces:* partials.

**Option B — teach the driver `transcript_green` and `boundary_green` (recommended).**
Add the tiers to the state schema, generalise `HARNESS_ENTRY`
(`src/port_trace_verify.py:73` hardcodes `run-unit.mjs`) and the sidecar's
`ORACLE TOTAL` pattern requirement (`src/port_wasm_units.py:1208`), and add a unit-level
rollup that requires full export coverage and never rounds a mixed unit up — the rule
`tools/survey_plan_tiers.py:230-241` already implements offline.

- *Pros:* `run-transcript.mjs` is **spec-free** — it drives from the corpus alone — so this
  converts the standard that already produced 16 console-derived passes into ledger
  movement without any hand authoring. It is the only option that scales.
- *Cons:* it is strictly weaker, and the project's rules forbid totalling it with
  `oracle_green` ([`verification-status.md:418-420`](verification-status.md)). It must ship
  **behind** the fail-open counter fix, because the first commit that teaches the driver a
  new tier silently inflates `queue.green`, the README table, the health `remaining`, and
  the rig contract probe ([`verification-status.md:458-466`](verification-status.md)).
  And the ceiling is measured and low: only 10 of 103 staged units can ever reach full
  transcript coverage, and **zero** currently have every export firing (E3).
- *Cost:* 2–3 agent-sessions in the OGhidra checkout (**ESTIMATE**), plus the counter fix.
- *Proves:* that console-derived evidence can move the project's own progress metric.
  *Produces:* on the current corpus, at most ~10 unit conversions.

**Option C — stop promoting units and record evidence per function.** Abandon the unit as
the promotion granule. Publish a per-function evidence map; the composed module links
whatever compiles; the claim is made over functions, not units.

- *Pros:* it matches the shape of the evidence that actually exists — every console-derived
  result in this repo is per-function (16 transcript, 1 boundary, 2 GX). It removes the
  full-export-coverage requirement that turns three passing functions in `auto-c0020-007`
  into a PARTIAL unit. It is the only option under which the 8,197 `transcript_green`-
  eligible functions can be counted at all.
- *Cons:* it breaks the promotion path into `port-units/`, which is what production loads.
  It also removes a real safety property: a unit promoted with one unverified export can
  ship a wrong export, which is exactly why full coverage was demanded.
- *Cost:* 2 agent-sessions to define the per-function ledger and its rollup;
  the production loader keeps loading whole modules regardless (**ESTIMATE**).
- *Proves:* nothing new. *Produces:* an honest denominator.

**Recommendation: B then C.** B first because it is a strict prerequisite (the driver
cannot record what it has no tier for), C second because the unit granule is the reason
16 passing functions read as zero progress. Neither may ship before the fail-open counters
are inverted to positive predicates against an explicit verified-tier set — that ordering
is not negotiable and is stated as gate P1.3 in §4.

### 3.3 E3 + E8 — coverage authorship is the real bottleneck

**The gap.** 0 of 103 staged units have every export both capturable and firing. All queued
scenarios are battles. The README's own verdict: coverage growth "is a **game-state
authoring problem** … not a tooling problem" (`:116-120`).

**Option A — more `force_navigator cover` scenarios in the same family.** Keep generating
`battle-roster-*` scenarios for unscouted borg families.

- *Pros:* fully autonomous today; the mechanism is proven (39 such scenarios exist, and the
  roster-reload basis is *measured*, not assumed —
  `scenarios/battle-roster-0x801a10e8.json` `live_families_basis`).
- *Cons:* it can only ever reach battle code. 59 of 103 staged units are unscouted, but the
  fraction of the ROM that is battle code bounds this permanently.
- *Cost:* ~45 s setup + 180 s scout per boot ⇒ **ESTIMATE** ~2–3 Dolphin-hours to scout the
  59 remaining staged units.
- *Proves:* nothing. *Produces:* capture opportunities.

**Option B — extend `force_navigator` to non-battle states (recommended alongside A).** The
navigator already writes into the game's own state and rewinds its own phase machine. The
same technique applied to the menu-mode table (`PTR_FUN_802da780`, 11 reviewed entries,
[`playable-port-design.md:321-324`](playable-port-design.md)) and the Challenge flow would
reach the half of the game no scenario covers.

- *Pros:* it is the only route to menu/shop/save/Challenge coverage that does not need a
  human at a controller. Anchors already exist in the corpus.
- *Cons:* **the validity question is real and unanswered**. Poking a menu mode into a
  dispatch variable produces a state the ROM may never reach by play; the arguments a
  function sees there may be off-manifold, and a transcript captured from an unreachable
  state verifies the port against a case the game never generates. The battle-roster
  scenarios already carry this risk and mitigate it by *measuring* that the family
  constructor fires and the battle reports live gameplay — the same mitigation must be
  designed per state class, not assumed.
- *Cost:* 2–3 agent-sessions plus ~3–5 Dolphin-hours to establish and measure the first
  non-battle state class (**ESTIMATE**).
- *Proves:* reachability of a game state. *Produces:* scenarios.

**Option C — owner-recorded DTMs.** The design's original G4 answer.

- *Pros:* a DTM is **replayable and deterministic**, which nothing else in the pipeline is
  (E10). It is the only input that can satisfy the I1 frame-boundary state-evidence gate.
  It also samples the input manifold the game actually produces, which is exactly what
  Option B cannot guarantee.
- *Cons:* it is owner wall-clock, it does not scale to 200+ borgs and every stage, and the
  rig cannot even record one today without an interactive input desktop
  (`README.md:81-93`).
- *Cost:* owner hours, unmeasured. One DTM per subsystem.
- *Proves:* determinism, which unlocks a whole class of gates. *Produces:* replayable
  coverage.

**Recommendation: A and B for breadth, C for depth, and C is not optional.** A and B grow
the number of functions that can be sampled; only C makes a capture *replayable*, and
without at least one replayable recording the design's step-9 gate has no input (E10). The
minimum ask is **one DTM through the boot → title → battle → results path** — not a
library.

### 3.4 E4 — the stack-local-pointer class

**The gap.** 56 of the 598 capturable staged exports, across 39 units, pass a stack-local
address to an out-of-unit callee; the console passes its frame address, the port passes its
wasm linear-stack address, and `run-transcript.mjs` compares arguments by value. These can
never match. Recorded only in the commit message of `612a1934` — not in the README, not in
`docs/`, and not in the harness's `does_not_verify` list.

**Option A — declare the exclusion.** Add the class to `run-transcript.mjs`'s
`does_not_verify` and stop counting those exports.

- *Pros:* one line of honesty; ships today. *Cons:* it weakens the standard further and
  gives up on 9.4 % of the capturable surface.
- *Cost:* < 1 agent-session. *Proves:* nothing. *Produces:* accurate claim text.

**Option B — port the fix that already exists (recommended).** `capture_gx.py:43-55`
already solves exactly this: a stack-relative argument is recorded as
`{"k":"sp","off":<arg − r1 at the call>}` and compared **structurally** — the aliasing
pattern and pairwise offsets must match, and a stack-relative argument may never equal a
non-stack one, enforced at `run-gx-callstream.mjs:245`. Port that encoding into
`capture_transcript.py` and `run-transcript.mjs`, and seed the bytes behind the pointer.

- *Pros:* the design and the negative control both exist and are tested; it recovers 56
  exports across 39 units; it is a real check ("the port passes the same buffer to the same
  calls"), and `capture_gx.py` already states in its own docstring that it is weaker than
  value equality, so the honesty text is written.
- *Cons:* it is a second, weaker comparison inside an already-weak standard, and the result
  artifact must say so per-argument or the weakening becomes invisible.
- *Cost:* 1–2 agent-sessions; re-capture of the 56 exports ⇒ **ESTIMATE** ~1.6
  Dolphin-hours.
- *Proves:* buffer-identity across the seam. *Produces:* 56 re-runnable exports.

**Recommendation: B, with A landed first as an interim.** Do A in the same commit that
writes the class into `docs/verification-status.md`, because a defect class documented only
in git history is one `git gc` away from being rediscovered.

### 3.5 H4 — audio has no mixer

This is the gap where the uncomfortable options are the real ones, so all four are stated.
The corpus evidence:
`zz_0217dd8_` writes command word `0xBABE0180` to the DSP mailbox and spins; `0xBABE` is
MusyX's mailbox magic; the AI ring is at `0x803DB100` with `0x280`-byte transfers at 32 kHz
= a 5 ms MusyX frame ([`audio-dvd-hle-host.md:143-151`](audio-dvd-hle-host.md)).

**Option A — leave it absent and silent.** Status quo. `dspMicrocodeAbsent: true` on every
report; the smoke phase fails if it stops.

- *Pros:* honest, zero cost, already enforced. *Cons:* a composed-module build is a silent
  game, which most readers will not accept as playable.
- *Cost:* 0. *Proves:* nothing. *Produces:* silence, correctly labelled.

**Option B — intercept above MusyX with the already-ported cue system (recommended).** The
ROM's sound dispatcher `zz_00efb3c_` (`0x800EFB3C`) splits `bank = id >> 7`,
`sample = id & 0x7f`, and `packages/audio`'s `resolveCue` "already ports that arithmetic and
is self-tested" ([`audio-dvd-hle-host.md:645-648`](audio-dvd-hle-host.md)). Bridge the
dispatcher to the recreation's OGG cue path.

- *Pros:* the game makes the right sound at the right moment using assets extracted from
  the owner's own disc; it is buildable now; it reuses a tested component. The seam is a
  ROM function, so it is *declarable* in the bridged-call ledger like any other adapter.
- *Cons:* it is emphatically **not a port of the audio path**, and the doc says so: "it
  produces sound, it does not translate the ROM's audio path, and the coverage tables here
  must never be allowed to absorb it" (`:650-651`). It also does nothing for BGM streaming,
  for `AISetStreamPlayState`/`DVDLowAudioStream` (entirely unmodelled, `:597`), or for the
  in-window MMIO code that will still execute and still write arena state (see §5 **X4**).
- *Cost:* 2–3 agent-sessions (**ESTIMATE**); no Dolphin or GPU cost.
- *Proves:* nothing about the ROM's audio. *Produces:* audio.

**Option C — write a MusyX-shaped software mixer.** Reimplement the mixer's behaviour in
TypeScript from the ARAM sample pool and the command stream.

- *Pros:* it would fill the PCM buffer from game-driven state, so the AI DMA path becomes
  real rather than a transport proof. *Cons:* it is a reimplementation of undocumented
  microcode with **no oracle** — there is no DSP capture, and the design's own next-step
  list puts "capture one second of AI DMA buffer contents (it will be silence, which is the
  point)" as a thing "none of these has ever been done"
  ([`audio-dvd-hle-host.md:607-616`](audio-dvd-hle-host.md)). It also requires ARAM DMA
  modelling first (`:652-654`), which is 3 registers and 498 corpus accesses.
- *Cost:* 5+ agent-sessions and an unbounded tuning tail; ARAM modelling first
  (**ESTIMATE**).
- *Proves:* nothing without a console audio capture. *Produces:* plausible sound.

**Option D — emulate the GameCube DSP.** Run the uploaded microcode blob in a DSP
interpreter.

- *Pros:* it is the **only** option that could ever be sample-accurate, because it runs the
  actual mixer. *Cons:* it is emulation, not porting — it moves the project's terminal
  architecture from "the ROM's code in one wasm module with a high-level host" to "a
  partial GameCube emulator", which contradicts
  [`playable-port-design.md:184-189`](playable-port-design.md). It requires the microcode
  blob, which lives on the disc and is not in the repository. It requires ARAM to be real.
  And a DSP interpreter running at 5 ms cadence inside the worker competes with the frame
  loop for the same thread.
- *Cost:* very large; unmeasured. *Proves:* sample equivalence, in principle.
  *Produces:* a second emulator.

**Recommendation: B, with A's honesty machinery kept intact and D explicitly declined.**
Bridge the cue dispatcher so the game has sound; keep `dspMicrocodeAbsent: true` and the
smoke assertion so no report can quietly claim the audio path is ported; and **scope audio
out of the 1:1 claim in writing** (§8). Option D is the only route to a true 1:1 audio
claim and it is out of scope for this project's stated architecture — say that once, in the
design doc, rather than leaving it as an open item that periodically re-litigates itself.

### 3.6 H1 + H2 — the GX host cannot render a battle frame

**The gap.** 507 calls in 32.2 s to entry points that throw; and whole missing mechanisms —
EFB copy (confirmed live), skinning ("Nothing about character geometry can be right until
this exists"), post-transform texture matrices (20 of 21 observed texgen calls name one).

**Option A — implement in static-call-site order.** The historical approach that took the
host from 49.2 % to 87.1 %.

- *Pros:* it is how the existing coverage was built. *Cons:* the runtime capture
  **inverted** that ranking: "Static call-site share is not a usable proxy for what a frame
  needs" ([`gx-hle-host.md:886-887`](gx-hle-host.md)); `GXSetFog` is 220 live calls and
  ranks 45th statically.
- *Cost:* unbounded. *Proves:* nothing. *Produces:* coverage percentage.

**Option B — implement in measured runtime-frequency order (recommended).** Work the §7
order the GX doc already derived from the live capture: fog → EFB/`GXCopyTex` →
post-transform texmtx + normalized texgen → skinning → a second, harder oracle draw →
scissor/line/point/boot plumbing → batching + OffscreenCanvas.

- *Pros:* it is the only ordering with measured justification, and the console evidence for
  the first two items is *already captured* — fog type 2 with a colour pointer, type 0 to
  disable, `GXSetFogRangeAdj` enable always 0; `GXSetTexCopySrc/Dst` and `GXCopyTex`
  parameters recorded, "which is most of the specification"
  ([`gx-hle-host.md:956-972`](gx-hle-host.md)).
- *Cons:* the ranking comes from **one game state** — a live 2v2 battle — and the doc says
  it "should be re-measured across several before it is treated as the ranking" (`:914-916`,
  `:1019-1024`). Menus may need a different set entirely.
- *Cost:* **ESTIMATE** 1–2 agent-sessions per mechanism, 6–8 mechanisms; plus ~1
  Dolphin-hour to widen the surface capture to a second and third game state first.
- *Proves:* that a frame does not throw. *Produces:* a renderable battle.

**Option C — a second console oracle draw before any more implementation.** The verified
draw is "the smallest and simplest one: an untextured, unlit, single-stage, alpha-blended
quad" (`:991-992`); a textured, multi-stage draw "is what would put the TEV shader
generator and the texture decoder in front of the console for the first time; today neither
has ever been compared against anything" (`:995-997`).

- *Pros:* it attacks the largest concentration of unproven code with one measurement, and
  the CMPR texel layout "carries essentially all of the risk" (`:906`). *Cons:* it produces
  no new rendering capability; and the technique generalises only to draws switchable by
  staging one word of ROM state (`:999-1000`).
- *Cost:* ~2 Dolphin-hours plus 1 agent-session (**ESTIMATE**).
- *Proves:* the TEV generator and the texture decoder, for the first time.
  *Produces:* one artifact.

**Recommendation: B, with C inserted immediately after post-transform texmtx lands.** Do
the runtime-frequency work, but do not let the host reach "renders a battle" without a
second, textured oracle draw — otherwise the largest untested subsystem in the host
(texture decode + TEV) reaches production having been compared against nothing.

### 3.7 H7 + H5 — DVD and the audio MMIO window

**H5 (gate does not lower AI/DSP MMIO)** has no real alternative: the audio doc's own §8
item 1 is "the top item because nothing else in the audio half can reach a real composed
module without it" ([`audio-dvd-hle-host.md:622-624`](audio-dvd-hle-host.md)), and the
concrete specification is written there — generalise `port_wgpipe_lowering.py` from the
single `0xCC008000` window to an address-window table, add the AI and DSP windows, emit
`__gf_mmio_load_u16/u32` and `__gf_mmio_store_u16/u32`, and delete `gf_hw_mmio.h` and the
`AI_MMIO_NOT_GATE_LOWERED` diagnostic. Cost: 1–2 agent-sessions (**ESTIMATE**). Do it.
Without it, any real gate-built module containing audio code traps on an out-of-bounds
access (`:123-125`).

**H7 (DVD)** splits:

**Option A — keep the `SyntheticDisc`.** The host builds a disc in memory.

- *Pros:* works in a clean checkout with no proprietary bytes; the FST parser is real and
  `[CORPUS]`-derived. *Cons:* the game reads content that is not the game's content; the
  force navigator's `zz_0041288_ → zz_00410bc_` borg-archive streaming cannot run
  (`:637-638`).
- *Cost:* 0.

**Option B — a real disc behind a provider interface (recommended).** Missing pieces are
named: a host-side index loader, a byte source (HTTP range reader or an extracted
directory), "and a decision about whether the browser is allowed to hold 1.4 GB"
(`:632-637`).

- *Pros:* it is the only way ROM asset paths execute for real. *Cons:* it is owner-supplied
  data — the repository contains no disc bytes and must not — so the shipped build needs a
  legal story for how a user supplies their own disc.
- *Cost:* 2 agent-sessions plus an owner decision on hosting (**ESTIMATE**).

The DVD **timing model** is a separate matter and both docs concede it is "knowingly wrong
and cannot be fixed by accuracy work alone" (`:65-66`): reads complete inside their adapter
call, so `DVDGetCommandBlockStatus` spin loops exit on iteration 1. Under control inversion
the worker can genuinely block, so a *deferred* completion becomes expressible for the
first time — this should be revisited at that step, not before.

### 3.8 C7 — the 2.155 GB shared memory

**Option A — accept it and gate the device.** Publish a minimum-spec check and refuse
gracefully.

- *Pros:* no architectural change; "This is not a tuning knob"
  ([`composed-pilot.md:154-160`](composed-pilot.md)) because the arena must sit at original
  addresses. *Cons:* the game becomes desktop-only, likely Chromium-only, and the smoke has
  only ever proved it in headless Chrome on the rig. Firefox and Safari have different
  `SharedArrayBuffer` and wasm-memory ceilings and none has been measured.
- *Cost:* < 1 agent-session for the gate; ~1 agent-session to measure three browsers.

**Option B — wasm64 / a sparse arena.** Reduce the committed allocation.

- *Pros:* would restore low-RAM and mobile. *Cons:* the whole point of the fixed layout is
  that GC pointers in data are valid linear-memory addresses unmodified, which is what
  makes H3's "no pointer rewriting in data" byte-exactness property hold
  ([`playable-port-design.md:343-345`](playable-port-design.md)). Any sparse scheme
  reintroduces address translation and forfeits that. Memory64 is not uniformly available.
- *Cost:* large; and it invalidates the existing gate output.

**Recommendation: A.** Measure three browsers, publish the minimum spec, and record
desktop-only as a **product** limitation in the claim text. Do not trade the address
identity property for reach; it is load-bearing for the entire byte-exactness argument.

### 3.9 E2 — the 19.2 % with no route to a claim

1,602 functions dispatch through a ROM function-pointer table and 503 have an empty
transcript. [`verification-status.md:143-145`](verification-status.md) is explicit that both
classes are "standard-relative, not permanent" and that no third standard is designed.

**Option A — accept the floor.** State 19.2 % as permanently unclaimable and move on.

- *Pros:* honest and free. *Cons:* it caps the strongest possible claim at 80.8 % of
  functions *eligible*, which — given the actual conversion rate — is not the binding
  constraint anyway.

**Option B — design a third standard: in-module table instrumentation (recommended for
the 1,602).** The 1,602 are unobservable specifically because emcc lowers `bctrl` to a
`call_indirect` on the module's own table, which no import shim can see. But the composed
module's dispatch table is **generated by the assembly gate** (G2/H3 adapter thunks,
`__gf_dispatch`, `__gf_dispatch_miss`). A thunk is a generated function: it can record
`(caller, target GC address, arguments)` into a ledger. The dispatch that hides from an
import shim does not hide from a thunk the gate wrote.

- *Pros:* the mechanism already exists and is already in the shipped rung-0 artifact
  (40-thunk table, `frame_abi_version: 1`). It converts the single largest unverifiable
  class into a transcript-comparable one. It costs no new emulator capability — the console
  side is already captured the same way.
- *Cons:* it only works **inside the composed module**, not for a standalone unit replay,
  so it is a standard that only exists after C2/C1 have produced a real window. It also
  measures the gate's own lowering, so a bug in the thunk generator is invisible to it —
  the negative-control discipline that `gx-callstream-harness.test.mjs` uses (16 mutants)
  would have to be replicated.
- *Cost:* 2–3 agent-sessions after the ladder produces a spine-rooted window (**ESTIMATE**).
- *Proves:* the dispatch behaviour the ROM actually runs on.
  *Produces:* a route to a claim for 1,602 functions.

**Option C — nothing for the 503.** No out-of-unit call, no return value, nothing at the
import boundary. A fourth standard comparing internal state directly would be an entirely
different machine.

**Recommendation: A for the 503, B for the 1,602, scheduled after the composed window
exists.** Note that B is a *later* item than it looks, because it depends on C2.

### 3.10 S2 — the regression net under a shrinking scaffold

**Option A — wire the 18 orphaned runners.** They exist; they are absent from
`package.json`.

- *Pros:* cheap, and the ledger's own conclusion is that "This is the finding that lets the
  others survive. Finding #4 below shipped precisely because its test was orphaned"
  ([`audits/game-app-defect-ledger.md`](audits/game-app-defect-ledger.md) §3.1).
- *Cons:* some will fail on wiring, which is work, not a reason not to.
- *Cost:* 1–2 agent-sessions (**ESTIMATE**).

**Option B — a golden-frame differential against the current build.** Snapshot the
scaffold's behaviour before each seam replacement and diff.

- *Pros:* catches regressions the unit tests do not describe. *Cons:* it pins the
  *recreation's* behaviour as the reference, which is precisely the circularity
  `damage-core`'s `ts_port` reference already suffers from (§1.2); a seam replacement that
  is *more* correct than the scaffold would read as a regression.

**Recommendation: A, and explicitly not B.** Wire the runners. Do not build a differential
whose reference is the recreation — this project has already learned that lesson once, and
E1 is what it cost.

---

## 4. The critical path (first statement)

Eight phases. Each states its entry condition, its work, and an **exit gate** written so
that it can be checked mechanically. A phase is not done because its work is done; it is
done when its gate passes.

This is the *first statement* of the path. §5 attacks it, §6 replaces it. Do not implement
from this section.

### P0 — Restart the pipeline

**Entry.** Driver `stopped` since 2026-08-26; GPU leased to `omr-sweep`; one proven corpus
correction stalled (E7); three capture defects manufacturing false negatives (P6).

**Work.**
- **P0.1** Owner decision on GPU allocation (§9). Capture and compile are mutually
  exclusive on this rig.
- **P0.2** Land the outstanding corpus corrections through the sanctioned loop
  ([`corpus-correction-loop.md`](../research/decomp/corpus-correction-loop.md)):
  `FUN_800c4468` (chunks already corrected by `534bd22f`; the revocation and natural
  rebuild are outstanding).
- **P0.3** Invert the two fail-open counters (`src/port_contract.py:125`,
  `src/port_progress.py:209`) to positive tests against an explicit verified-tier set, plus
  a test that an unknown tier string does not land in `green`.
- **P0.4** Fix the three false-negative capture defects: orphan Dolphin reaping in
  `capture_oracle.py stop`, corpus re-merge after a capture, and the `UNIT` placeholder
  defaults on `--wasm-rel` / `--arena-rel`.

**Exit gate G0.** A driver run completes a unit; at least one revocation has rebuilt and
re-landed; a test proves an unknown tier string routes to neither `green` nor `staged`;
`capture_oracle.py stop` reaps an orphan in a test.

### P1 — Make the evidence that already exists countable

**Entry.** G0. **Declared ceiling, stated before the work starts so it is not mistaken for
a scaling fix: at most ~10 unit conversions are reachable** (E3 — 10 of 103 staged units
have every export capturable, and zero have every export firing).

**Work.**
- **P1.1** Add `transcript_green` and `boundary_green` to the driver state schema;
  generalise `HARNESS_ENTRY` (`src/port_trace_verify.py:73`) and the sidecar's
  `ORACLE TOTAL` pattern requirement (`src/port_wasm_units.py:1208`); add a unit rollup that
  requires full export coverage and never rounds a mixed unit up.
- **P1.2** Declare the stack-local exclusion in `run-transcript.mjs`'s `does_not_verify`
  and write the class into `docs/verification-status.md`.
- **P1.3** Port `capture_gx.py`'s `{"k":"sp","off":…}` structural comparison into
  `capture_transcript.py` and `run-transcript.mjs`.

**Exit gate G1.** (a) A unit whose every export is `transcript_green` is recorded at a
`transcript_green` unit tier **and `queue.green` does not move**; (b) the unknown-tier test
from P0.3 still passes; (c) at least one of the 56 stack-local exports replays green under
the structural comparison; (d) the class is documented in `docs/`.

### P2 — Repair the corpus substrate

**Entry.** G0.

**Work.**
- **P2.1** Survey the Ghidra varargs-assert prefix class across all 1,514 affected registry
  functions; the blast radius inside staging is already measured at 48 functions in 23 of
  the 103 staged units.
- **P2.2** Correct `start` `@0x80003154`, same class, flagged as "it will matter at
  whole-program link".
- **P2.3** Re-extract every pinned range and confirm only the intended digests change — the
  293-range / 2-digest procedure is already proven.

**Exit gate G2.** Every staged unit whose source carries the prefix has been revoked and
rebuilt or carries a recorded reason why not; `start` compiles with the corrected
signature; the re-extraction check is clean.

### P3 — Spine-rooted composition

**Entry.** G0, G2.

**Work.**
- **P3.1** Emit `spine-frontier.json`: the call graph rooted at `run_main_game_loop`
  (`0x800527d8`), ranked by frontier ring.
- **P3.2** Re-point the ladder's selection rule and `unit-priority.json` at the frontier.
- **P3.3** Restate the E1 conflict budget for frontier rings **in
  `playable-port-design.md`, with the measurements that justify it**, before the first
  spine-rooted rung runs — E1's own revision rule.
- **P3.4** Run frontier ring 0: the spine plus its 17 loop-body callees.
- **P3.5** Compile whatever ring 0 needs that is untouched.

**Exit gate G3.** A composed module links containing `run_main_game_loop` and its loop
body; the rung's `new_contested / new_linked` ratio is recorded; every out-of-window import
is bound (rung 0's "all 31 bound" property preserved); and the per-frame bridged-call count
is recorded as the **baseline** for the S1 shrink metric.

### P4 — A frame that does not throw

**Entry.** G3.

**Work.**
- **P4.1** Widen the GX runtime surface capture to at least three game states.
- **P4.2** GX in measured runtime order: fog → EFB / `GXCopyTex` → post-transform texture
  matrices and normalized texgen → per-vertex position matrices (skinning).
- **P4.3** A second, **textured** console oracle draw.
- **P4.4** Teach the assembly gate the AI and DSP MMIO windows (H5).
- **P4.5** Bridge the ROM sound dispatcher to the recreation's cue path (§3.5 B), keeping
  `dspMicrocodeAbsent: true` and its smoke assertion.
- **P4.6** DVD provider decision and the two unimplemented entry points.

**Exit gate G4.** The composed module executes one full frame of the boot path with **zero**
loud-unimplemented throws, zero `AI_MMIO_NOT_GATE_LOWERED` diagnostics, and an empty
unimplemented-hit ledger; the second oracle draw passes `gx_framebuffer_equivalent` within
its declared tolerance.

### P5 — Control inversion

**Entry.** G3, G4, and the cross-origin isolation gate (already landed).

**Work.**
- **P5.1** Trace-derived adapters for the demand set the bridged-call ledger names (I1).
- **P5.2** Extend the proven worker-side reentrant dispatch loop to the frontier window's
  import set.
- **P5.3** A per-frame watchdog at worker park points.
- **P5.4** Threads relink and re-verify for every unit in the window that has evidence.

**Exit gate G5, two tiers, both reported.**
- **(a) Liveness.** The composed module drives N ≥ 600 consecutive frames with the TS
  engine passive, every out-of-window call routed through the declared bridge, zero
  servicing errors, zero watchdog trips, per-frame bridged-call count reported.
- **(b) Fidelity.** At each declared frame boundary the shared arena matches a Dolphin
  trace of the same DTM replay, modulo a declared, ledger-justified exclusion list.

A build that has passed only (a) may never be described as verified.

### P6 — Evidence against the running module

**Entry.** G5(a).

**Work.**
- **P6.1** Thunk-level dispatch transcripts (§3.9 B) — the route to a claim for the 1,602.
- **P6.2** Divergence bisection: first diverging frame → first diverging call → owning unit
  → the sanctioned corpus-correction loop.
- **P6.3** Coverage authorship targeted by what actually executes rather than by the staged
  queue.

**Exit gate G6.** One divergence found by comparison is traced to a unit and closed through
`revoke-unit` and rebuild, end to end, with the artifact chain recorded.

### P7 — Ship

**Entry.** G4, G5(a), and the S2 regression net wired.

**Work.** Device gate and published minimum spec; the per-function evidence map shipped
with the build; the claim text of §8 on the page.

**Exit gate G7.** The production smoke asserts `crossOriginIsolated`, drives the composed
module for N frames on the deployed build, and the published page states the evidence tiers
of the functions that executed.

---

## 5. Adversarial review of §3 and §4 — VERDICT: FAIL

Reviewed against the requirement: **a person plays this and it behaves as the GameCube
game, and the sentences we say about it are true.** Eight material failures. Each is stated
with its evidence, then corrected in §6. Where a citation reads `file:line`, the line was
read for this review.

### X1 — G3's frontier ring 0 is not a well-defined set of units, and may not be linkable

§3.1 Option B and P3.4 assume "the units containing the spine's direct callees" is a small,
gate-eligible set. Three pieces of measured evidence say otherwise:

1. **The unit partition cuts across the spine's call graph.** The queue's real unit for the
   spine, `auto-c0006-013`, "cannot serve as the `boundary_green` target" *because it
   bundles one of the spine's own loop callees*
   (`research/tools/dolphin-trace/README.md:531-544`) — which is why the existing
   `boundary_green` result was produced against a separate preflight build in
   `research/decomp/spine-boundary/`, not a queue unit. So "take the units containing ring
   0" does not yield a ring; it yields units that already contain parts of ring 1.
2. **The largest window ever linked is N=10 with 78 companion thunks**
   (`composition-ladder.json` rung 1). Ring 0's unit closure size has never been computed,
   and the loop body is 17 calls
   ([`playable-port-design.md:980-983`](playable-port-design.md)) whose owning units are
   unknown.
3. **The spine fans out into essentially the entire per-frame call graph**
   ([`playable-port-design.md:521-524`](playable-port-design.md)), so a breadth-first
   frontier reaches N = the whole ROM within two or three rings.

As written, P3 is a phase whose first action might be unbounded, and the gate G3 would
simply never be reached. **This is fatal to the recommended option.**

### X2 — G5(b) and P6 have no input, and would not fit down the wire even if they did

Two independent measurements kill the fidelity gate as written.

1. **There is no DTM and captures are not replayable.**
   `research/tools/dolphin-trace/README.md:76-79`: captures ride savestate plus synthesized
   input and are "non-deterministic across runs (each capture is a fresh sample, not a
   replayable trace)". The repository root [`README.md:265-267`](../README.md) states the
   coverage prerequisite is **unmet**. The rig cannot record a DTM: `--save_state` is
   load-only and
   there is "no interactive input desktop to inject into" (`:81-93`). So G5(b) — "the same
   DTM replay" — has no input, and neither does P6.2's bisection signal, which I made
   depend on it.
2. **A per-frame arena comparison is not physically available.** "A full MEM1 diff is
   24 MB per boundary over a GDB-RSP socket; nothing like that runs at frame rate"
   (`research/tools/dolphin-trace/capture_transcript.py:62-66`), and the stub dies after
   "about 40 s … or a few hundred breakpoint stops"
   (`research/tools/dolphin-trace/README.md:103-107`) at "roughly 15x slower than real
   time" (`:110`). G5(b) as written asks for something the transport cannot carry.

The design document has the same defect — V5 I1's gate is "the shared arena is compared
against a Dolphin trace of the SAME DTM replay … at each frame boundary"
([`playable-port-design.md:745-751`](playable-port-design.md)) — so this review finds it in
both documents. **Fatal.**

### X3 — P3 and P4 drive a window of unverified units and have no defence against a hang

The plan's central move is that the composed module can grow on `compile_only` inventory.
The measured counter-evidence is direct:

- `auto-c0035-002` is byte-exact on 6,250 of 20,000 cases and is *still recorded as a green
  `compile_only` unit* ([`verification-status.md:41-44`](verification-status.md)).
- `auto-c0001-005` was proven behaviourally wrong against the console and required the
  corpus-correction loop.
- Two of the five units ever compared against anything were wrong.

A wrong unit inside a driven frame loop does not necessarily trap. It can spin. A wasm
function spinning inside a worker cannot be interrupted by the host, and the design
explicitly excluded Asyncify ([`playable-port-design.md:292-296`](playable-port-design.md)),
so there is no suspension mechanism. **P5.3's watchdog is scheduled two phases after the
first driven window and is described in one line. That is not a plan; it is a hope.**
Fatal.

### X4 — "Scope audio out" is a mechanism decision, not only a claim decision

§3.5 recommends bridging the cue dispatcher and scoping audio out of the 1:1 claim. But the
ROM's in-window audio code **still executes and still writes the shared arena**: 34 of 40
audio call sites are in-window, touching 18 registers across 403 static reads and 342 static
writes ([`audio-dvd-hle-host.md:265`](audio-dvd-hle-host.md), `:267`), and the ARAM DMA trio
alone is 247 reads / 251 writes (`:341-346`). Under a null DSP that code produces different
arena state than the console's real DSP does. Two consequences the spec did not state:

- Every one of those bytes is a failure under any arena comparison, so the exclusion list
  G5(b) waves at is not a footnote — it is a derived, reviewed artifact that does not exist.
- Worse, the timing differs too: "Nothing paces it at 5 ms" (`:596`), so the ROM's audio
  code advances at a different rate than the console's and its *control flow* diverges, not
  only its data. An exclusion list over addresses does not cover a divergence in how many
  times a loop ran.

An unguarded exclusion list silently swallows gameplay divergence. **Fatal to the fidelity
gate.**

### X5 — The evidence plan is a 10/1,396 plan, and the spec knows it and proceeds anyway

§3.2 recommends teaching the driver `transcript_green`, and P1 states the ceiling honestly:
~10 unit conversions. Then §4 proceeds as if the evidence track were addressed. It is not.
Against 1,396 units and 10,954 functions, P1 is plumbing, and the spec presents plumbing in
the position where a throughput plan belongs. The two mechanisms that could actually move
the denominator — thunk-level dispatch transcripts for the 1,602 (§3.9 B) and coverage
targeted by execution (§3.3) — are both parked at P6, behind G5(a), behind three phases.
**The plan's own ordering starves its only scaling mechanism.** Fatal to the claim track.

### X6 — C6 was marked "deferred" without an argument

The gap table marks the threads-relink re-verification obligation "deferred". The rule is
unconditional: "every `oracle_green` / `boundary_green` status is SUSPENDED until the unit's
full corpus replays byte-equal against the relinked artifact"
([`threads-relink-reverify.md:4-9`](threads-relink-reverify.md)), and "each verified unit
needs its OWN pass" (`:123-129`). Deferring a normative rule because it is inconvenient is
the failure mode this project's documents exist to prevent. Fatal as written, though the
correction is not what it looks like — see §6.

### X7 — The phase ordering assumes parallelism the rig does not have

P2 and P3.5 need the driver, which needs the GPU. P4.1, P4.3 and P6 need Dolphin. The
design records that "Dolphin capture must never contend with the LLM"
([`playable-port-design.md:106-108`](playable-port-design.md)), and
[`AGENTS.md`](../AGENTS.md) records that a paused supervisor *actively unloads any model you
load*. So the phases as ordered cannot run as written, and §4 never says so. A critical path
that cannot be scheduled on the machine it runs on is not a critical path. Fatal.

### X8 — The spec's central move manufactures exactly the overclaim the project forbids

§2.6 decouples playability from verification, and §4 acts on it: a composed module built of
`compile_only` units, driving frames, shipped. Claim-honesty rule 1 exists precisely to stop
that artifact being described as progress: "**`compile_only` is UNVERIFIED inventory, never
progress.** Never describe a `compile_only` unit as ported, done, working, or finished"
([`verification-status.md:412-414`](verification-status.md)). The spec provides no
vocabulary for what such a build *is*, which means the first person to demo it will reach
for the words the project has banned. **Fatal to the project's culture, which is its most
valuable asset.**

---

## 6. Corrections, and the revised critical path

Each fatal gap above, closed.

### Correcting X1 — ring 0 is the spine unit alone; everything else is bridged

The frontier does not need to be closed to be useful, because the host bridge already makes
a partial window runnable: every out-of-window callee becomes a declared import serviced
through the Atomics RPC bridge ([`playable-port-design.md:531-539`](playable-port-design.md)),
and a table miss is a bridge call, never a trap
([`playable-port-design.md:592-596`](playable-port-design.md)).

So **ring 0 is the unit that contains `run_main_game_loop`, and nothing else.** All 17 loop
callees are bridged. This satisfies H2 gate (a) — the module is driven by the ROM's own
loop — on the smallest possible window, and it starts the S1 shrink metric at its maximum
rather than requiring it to be small.

Two consequences that must be recorded:

- The spine's unit `auto-c0006-013` bundles one of its own loop callees
  (`README.md:531-544`), so ring 0 is N=1 but not a clean spine-only module. Either the
  preflight build in `research/decomp/spine-boundary/` becomes the ring-0 artifact — with
  the provenance cost that it is not a queue unit — or `auto-c0006-013` is accepted whole
  and the bundled callee is linked rather than bridged. **This is a decision, and it is
  recorded as one** (§9, owner item 5), because the first option forfeits the
  regenerate-from-the-queue property the corpus-correction loop depends on.
- The frontier ranking still has a job: it becomes the **compile priority order** for the
  driver (`unit-priority.json`), so that the 1,133 untouched units are attempted in the
  order that shrinks the bridged-call count fastest. That is a queue re-ranking, not a
  linking constraint, and it has no size problem.

`spine-frontier.json` therefore ships as a *ranking*, and the ladder grows by **bridged
calls per frame falling**, not by N doubling. The E1 ratio budget still applies per rung
and its restatement (P3.3) is now simply "a rung is a frontier prefix", which is
comparable rung-to-rung because the prefix is nested.

### Correcting X2 — sparse boundaries, a required owner DTM, and a ledger-based interim signal

Three changes.

1. **G5(b) becomes sparse, not per-frame.** The comparison is against **full MEM1 snapshots
   at a small number of declared boundaries** — the mechanism v1 Stage B already proved
   converts, where "the oracle arena was verified byte-identical" against 2 × 24 MB console
   captures ([`playable-port-design.md:90-93`](playable-port-design.md)). Snapshots are
   taken outside the frame loop, so neither the 24 MB transport cost nor the ~40 s stub
   window binds. The number of boundaries is declared in the result artifact, as `K` is for
   `boundary_green`.
2. **One owner DTM becomes a hard prerequisite of G5(b), and G5(b) alone.** Everything up
   to and including G5(a) proceeds without it. This is the correct placement of the
   dependency: V5 I3 moved the DTM to the first trace-dependent step
   ([`playable-port-design.md:817-821`](playable-port-design.md)); the measurement since
   then (E10) shows the *first* trace-dependent step never needed it — non-deterministic
   sampling is sufficient for `transcript_green` — and the step that genuinely cannot
   proceed without it is the arena comparison. The dependency moves to where it bites.
3. **The interim divergence signal is the ledger, not the arena.** Without a DTM, P6.2
   bisects on the **bridged-call and dispatch ledger**: the sequence of out-of-window calls
   the composed module makes in a frame, compared against a transcript captured for the
   same function from the console. That is the `transcript_green` comparison applied to a
   running module instead of a replayed one, it needs no determinism beyond a single
   capture, and the harness for it already exists.

### Correcting X3 — the watchdog moves to P3 and is a build variant, not a code change

Promote the watchdog ahead of the first driven window, and resolve the byte-exactness
conflict it creates explicitly:

- The gate's dispatch thunks gain an **optional** back-edge budget decrement that calls a
  `__gf_watchdog_tick` import. It is emitted only under a `--watchdog` build flag.
- The **watchdog build is a debugging artifact and is never the verified artifact.** The
  shipped and verified module is the non-watchdog build. This preserves "the verified bytes
  are the shipped bytes", which is the principle that excluded Asyncify
  ([`playable-port-design.md:292-296`](playable-port-design.md)), while giving the driven
  window a way to fail loudly instead of hanging a tab.
- Any window larger than the last one that passed G5(a) must first pass its liveness run
  **under the watchdog build**. A hang under the watchdog names the spinning function; a
  hang without it names nothing.

Additionally, G3 gains a precondition that costs nothing and would have caught
`auto-c0035-002`: **any unit in the window that has a committed `fail` or `oracle_divergent`
artifact is excluded from the window** until its correction has landed.

### Correcting X4 — the audio arena footprint is a derived, guarded artifact

Add to P4, before P4.5:

- **P4.4a — derive the audio arena footprint.** From the corpus, enumerate the addresses
  the in-window audio code writes (the MusyX bookkeeping, the ARAM mirrors, the AI register
  shadows, the `0x803DB100` ring). Emit it as a reviewed artifact, not a gate parameter.
- **The exclusion is guarded.** Any read of an excluded region *by a function outside the
  audio set* is a **declared failure**, not a pass. Without the guard the exclusion list
  can absorb a gameplay divergence and the gate passes on nothing — which is exactly the
  vacuity `transcript_green` was built to prevent
  ([`verification-status.md:69-76`](verification-status.md)).
- **Control-flow divergence is acknowledged, not excluded.** Because "Nothing paces it at
  5 ms" ([`audio-dvd-hle-host.md:596`](audio-dvd-hle-host.md)), the ROM's audio code will
  execute a different number of iterations than the console's. An address exclusion cannot
  cover that. So the DMA pacing item — currently §8 item 6 of the audio doc, "a design
  decision, not a patch" (`:655-659`) — is **promoted onto the critical path** as a
  prerequisite of G5(b), and if it is not solved, G5(b)'s scope is reduced in writing to
  frames on which the audio path is quiescent.

### Correcting X5 — the scaling mechanism moves ahead of control inversion

**P6.1 does not depend on G5(a).** Thunk-level dispatch transcripts need a linked window
with a dispatch table — G3 — and nothing else. The composed rung-0 artifact already carries
a 40-thunk table with `frame_abi_version: 1`. Move it.

The revised path therefore splits the evidence track into:

- **P1 (plumbing, ~10 units)** — labelled as plumbing in the phase title so nobody reads it
  as throughput.
- **P3b (scaling)** — thunk-level dispatch transcripts, run against the ring-0 window,
  targeting the 1,602 functions that are otherwise unclaimable. This is the only mechanism
  in the whole plan whose denominator is in the thousands.
- **P6.3 (targeting)** — coverage authored against what executes.

### Correcting X6 — relink re-verification is an artifact property, not a phase

The inversion the gap table missed: **only a unit that has evidence can have that evidence
suspended, and today exactly one unit does.** The relink rule is not a scaling blocker now;
it becomes one precisely when P1 and P3b succeed. The correction is therefore not to
schedule a phase but to change an artifact schema:

- Every result artifact records **which binary it was produced against** — standalone
  export-memory unit, or composed-lane imported-shared-memory module.
- A claim may only be made about the composed module from artifacts of the second kind.
- The base-proof → relink → replay → `.threads.json` pass
  ([`threads-relink-reverify.md:31-98`](threads-relink-reverify.md)) becomes a scripted
  step in the promotion path rather than a hand-run procedure, so the obligation scales
  with the evidence rather than being deferred.

### Correcting X7 — an explicit alternation schedule, owned by the owner

The phases are re-labelled by the resource they consume, and the plan states that they
alternate rather than run in parallel:

| Resource | Phases |
| --- | --- |
| **GPU (LLM serving slot)** | P0.2, P2, P3.5 |
| **Dolphin (exclusive with GPU)** | P1.3 re-capture, P3b, P4.1, P4.3, P6 |
| **Neither** | P0.3, P0.4, P1.1, P1.2, P3.1–P3.4, P4.2, P4.4, P4.5, P5, P7 |

The third row is the majority of the work and can proceed regardless. The first two rows
alternate on the manual gate, per [`AGENTS.md`](../AGENTS.md), and the alternation cadence
is an **owner decision** (§9, owner item 1) because it is a resource allocation, not an
engineering choice.

### Correcting X8 — a new metric and a new claim-honesty rule

Introduce **ROM-executed functions per frame**: the count of distinct functions that
executed from ROM-derived code in the composed module during a recorded run, reported
**always** with its evidence breakdown and never as a single number:

    ROM-executed this run: 412 functions
      oracle_green      3
      transcript_green  16
      boundary_green    1
      compile_only    392   (UNVERIFIED)

And add to [`docs/verification-status.md`](verification-status.md) §6 a ninth standing rule:

> **9. Execution is not verification.** A function that executed from ROM-derived code in
> the composed module has been *run*, not *checked*. "ROM-executed" and "verified" are
> different counts over the same population and must never be printed as one number, and a
> build that drives frames is not a ported game — it is a running module whose functions
> carry the tiers they carry.

This is the vocabulary the plan was missing. Without it the plan is a machine for producing
the overclaim; with it, the decoupling in §2.6 is safe.

### The revised critical path

| Phase | Resource | Exit gate |
| --- | --- | --- |
| **P0 Restart** | GPU + none | G0: a unit completes; a revocation rebuilds; the unknown-tier test passes; orphan reaping tested |
| **P1 Evidence plumbing** (~10 units, labelled) | none + Dolphin | G1: a full-transcript unit records a `transcript_green` tier and `queue.green` does not move; one stack-local export replays green; the class is in `docs/` |
| **P2 Corpus substrate** | GPU | G2: prefix-class units revoked and rebuilt or reasoned; `start` corrected; re-extraction clean |
| **P3 Ring-0 composition** | none + GPU | G3: a module links containing `run_main_game_loop`; all imports bound; **no unit with a `fail`/`oracle_divergent` artifact in the window**; bridged-call baseline recorded |
| **P3b Dispatch transcripts** (the scaling mechanism) | Dolphin | G3b: a function of the 1,602 class carries a thunk-level transcript result, with a mutant negative-control suite in the style of `gx-callstream-harness.test.mjs` |
| **P4 Non-throwing frame** | none + Dolphin | G4: one boot-path frame with zero unimplemented throws, zero `AI_MMIO_NOT_GATE_LOWERED`, an empty unimplemented-hit ledger, a second textured oracle draw passing, **and the audio arena footprint artifact reviewed** |
| **P5 Control inversion** | none | G5(a): ≥600 driven frames, TS passive, all calls routed, zero servicing errors, zero watchdog trips — **run under the watchdog build first**. G5(b): sparse MEM1 boundary comparison against an owner DTM, guarded exclusion list |
| **P6 Divergence loop** | Dolphin | G6: one ledger-detected divergence traced to a unit and closed through revoke + rebuild |
| **P7 Ship** | none | G7: production smoke asserts isolation, drives N frames, publishes the ROM-executed count **with** its evidence breakdown |

Ordering constraints that are not implied by the table: P3 requires G2; P3b requires G3;
P5 requires G3 and G4; G5(b) requires an owner DTM and the audio pacing decision; P7
requires G4 and G5(a) and the S2 net.

---

## 6a. Second review round — the corrections themselves

The corrections in §6 were reviewed against the same requirement. Three further defects,
all inside mechanisms §6 itself introduced. None is fatal to the plan; each changes a gate.

### Y1 — Ring 0 bridges ~17 callees for which no valid adapter can exist yet

§6's correction of X1 makes ring 0 the spine alone and bridges everything. But V5 I1 is
explicit that routing a call is not servicing it: a bridged callee must read its arguments
from GC memory and write its results **and side effects** back to GC memory at the original
addresses, and "An adapter without trace evidence for its symbol is not a valid adapter"
([`playable-port-design.md:727-740`](playable-port-design.md)). The composed pilot's three
adapters are synthetic and the doc says they "prove nothing about what the ROM writes"
([`composed-pilot.md:210-249`](composed-pilot.md)). And the V5 verdict's escape hatch —
trace-delta adapters that "mechanically apply recorded per-call memory deltas under DTM
lockstep" ([`playable-port-design.md:977-980`](playable-port-design.md)) — needs the DTM
again.

**Correction.** G5(a) is restated as, and only as, a **routing and liveness** gate that
produces no behavioural claim — which is exactly how the composed pilot already labels
itself, down to `<html data-gf-composed-pilot="synthetic-no-behavioural-claim">` and an
on-screen banner. Adapter authoring is demand-driven from the bridged-call ledger at a
stated per-symbol capture cost of ~100 s of Dolphin time (§1.6a). The frames driven before
adapters have real write sets are **behaviourally meaningless and must be labelled so in
the DOM and in the smoke report**, using the pilot's existing machinery.

### Y2 — P3b measures the gate's own lowering and is blind to a wrong thunk

Thunk-level dispatch transcripts (§3.9 B, phase P3b) observe `call_indirect` through a
table the assembly gate generated. If the thunk generator mis-marshals — which H3's uniform
ABI makes possible *silently*, against 88 contested symbols
([`playable-port-design.md:877-881`](playable-port-design.md)) — the transcript records the
wrong call faithfully. This is the same circularity the write-gather-pipe lowering had
until the console compared it.

**Correction.** G3b requires two things, not one: the mutant negative-control suite in the
style of `research/decomp/oracle-harness/tests/gx-callstream-harness.test.mjs` (16 tests,
run by `pnpm test:oracle`), **and** at least one thunk-level transcript cross-checked
against a console capture of the same dispatch site. That second half is a capture-side
change: `capture_transcript.py` currently **refuses** the indirect-dispatch shape rather
than capturing it (`:51-60`), so P3b costs a capture-tool change as well as a replay-tool
one. §3.9's cost estimate of 2–3 agent-sessions is revised to **4–5** (**ESTIMATE**).

### Y3 — G4 is much weaker than it reads

"One full frame of the boot path with zero loud-unimplemented throws" can pass while a
battle frame still throws. The measured 507 unimplemented calls in 32.2 s came from a live
2v2 battle, and `GXSetFog` — 220 of them — is a battle call
([`gx-hle-host.md:870-883`](gx-hle-host.md)). A boot-path frame exercises a different
surface entirely.

**Correction.** G4 is stated **per game state** and must be satisfied for **each** of the
≥3 states captured at P4.1, one of which must be the live 2v2 battle that produced the
surface measurement. The unimplemented-hit ledger must be empty for every one of them.

---

## 7. Residual risks that survive the corrections

No plan removes these. They are stated so no future document has to rediscover them.

- **R1 — 503 functions have no route to any claim, permanently-as-designed.** No
  out-of-unit call and no return value; nothing at the import boundary to compare
  ([`verification-status.md:138-141`](verification-status.md)). The 1,602 get a route only
  *inside* the composed module (P3b), never as standalone units.
- **R2 — The graphics boundary's ceiling is below byte-exactness and always will be.**
  "Framebuffer-equivalent, never pixel-identical"
  ([`verification-status.md:312-317`](verification-status.md)).
- **R3 — Audio has no portable route to 1:1.** The mixer is microcode that is not in the
  DOL. The only mechanism that could be sample-accurate is DSP emulation, which is a
  different project (§3.5 D).
- **R4 — The decompiled corpus is the substrate and its defect rate is unmeasured.** What
  is measured: 1,514 of 10,954 registry functions carry the varargs-assert prefix; two of
  the five units ever compared against a reference were proven mis-lifted; three corpus
  corrections have landed in total. **ESTIMATE**, from that base rate: corpus correction is
  a multi-hundred-item programme, and every correction costs a full port cycle
  ([`corpus-correction-loop.md`](../research/decomp/corpus-correction-loop.md)).
- **R5 — One GPU.** Capture and compile alternate; there is no configuration in which both
  tracks run at once.
- **R6 — H3's uniform dispatch ABI trades traps for silent mis-marshalling**, against 88
  contested symbols, and PPC register-residue reads remain "a known unreproducible class"
  ([`playable-port-design.md:877-884`](playable-port-design.md)). The spine's own first
  capture failed on exactly this — 783 of 920 argument slots diverged
  (`research/tools/dolphin-trace/README.md:418-455`).
- **R7 — The shipped build is desktop-class only.** A committed 2,155,479,040-byte shared
  allocation, proven in one browser on one machine.
- **R8 — Without an owner DTM there is no whole-frame fidelity claim at all**, only
  liveness plus a per-function evidence map. This is the single highest-leverage owner
  input in the entire plan.
- **R9 — Ten driver defects (§7.1–7.10 of the integrity audit) have not been re-verified
  since 2026-08-23** and live in an unvendored checkout, including "'Verbatim /
  byte-faithful C' is false at both boundaries"
  ([`audits/port-pipeline-integrity.md:452-456`](audits/port-pipeline-integrity.md)).
- **R10 — `collision-core` and `knockback-core` are promoted with no committed result
  artifact**, and `collision-core`'s own recorded summary is 28,121/32,153 on its second
  measure. Two of the three units in `research/decomp/port-units/` do not meet the standard
  the directory implies. This should be resolved before any count of "promoted units" is
  published again.

---

## 8. The honest verdict

### 8.1 Is a full byte-exact 1:1 port of all 1,396 units reachable by this pipeline?

**No.** Five independent measurements each close the door on their own; together they close
it without ambiguity.

1. **2,105 of 10,954 functions (19.2 %) have no route to any existing standard** — 1,602
   dispatch through a ROM function-pointer table, 503 have an empty transcript
   (`verification-tier-survey.json`). §3.9's proposal opens a route for the 1,602 *inside
   the composed module*; it opens none for the 503, and none for any of them as standalone
   units.
2. **Byte-exact means `oracle_green`, and `oracle_green` is auto-derivable for 6.0 % of
   functions and for 2 units out of 1,396.** Everything else needs a hand-authored spec.
   Six exist. Even at one spec per unit per session this is not a plan, and the survey's own
   per-unit rollup caps `all_exports_oracle_green` at **2**.
3. **The `oracle_green` standard is empty for 40.7 % of functions** — 4,455 store nothing a
   capture could compare, and a spec over them passes vacuously. That already happened:
   15/15 on `"reads": [], "writes": []`
   ([`verification-status.md:149-162`](verification-status.md)). A "byte-exact port" whose
   byte-exactness is vacuous over two fifths of the code is not byte-exact.
4. **The graphics boundary has a ceiling below byte-exactness and always will.** WebGL
   cannot match Flipper; the standard is framebuffer-equivalent, and translating more of
   the pipeline moves toward that ceiling without raising it.
5. **The audio mixer is not in the DOL.** MusyX microcode is not PowerPC, is not
   translatable, and the host "cannot fill" the PCM buffer. No amount of porting reaches it.

And one measurement about where the project actually stands, which matters more than any
ceiling: **zero units in this repository have a console-derived full-coverage byte-exact
PASS.** Every unit-level pass is referenced against the TypeScript recreation; every
console-referenced unit artifact is a fail or a partial (§1.2).

### 8.2 What IS reachable, stated as a definition

> ### ROM-driven, evidence-tiered 1:1-playable
>
> Gotcha Force runs in a browser with **the game's own compiled code** — the decompiled
> ROM recompiled and linked as a single WebAssembly module at original GameCube addresses,
> in a shared linear memory, **driving its own main loop**. Graphics, input, file I/O, OS
> services and audio transport are provided by a high-level host at the SDK seam. Every
> call that leaves the module is declared in a ledger and serviced by a named adapter.
> Every function that executes carries a published evidence tier, and the build reports how
> many of the functions it executed are `oracle_green`, `transcript_green`,
> `boundary_green`, and `compile_only` (unverified).

That definition is reachable because every clause in it is a mechanism that exists or has a
gate in §6: the composed module links (rung 1), the bridge routes and reenters (the composed
pilot), isolation works (the COI phase), the loop has a standard (`boundary_green`), and the
tiers have harnesses. What it does **not** claim is the part measurement forbids.

### 8.3 The exact claim language

Sentences that would be **true** of the build defined in §8.2, and may be published:

- "The game's own ROM-derived code drives the frame loop; the TypeScript engine executes
  only when called through the declared bridge."
- "During the recorded session, N distinct functions executed from ROM-derived code. Of
  those, *a* are `oracle_green`, *b* are `transcript_green`, *c* are `boundary_green`, and
  *d* are `compile_only` — unverified."
- "Rendering is framebuffer-equivalent to the console within a declared per-channel
  tolerance **on the draws that have been compared**; N draws have been compared."
- "The composed module's arena matched a console snapshot at K declared frame boundaries,
  modulo the exclusion list published beside the result."
- "Audio is produced by the recreation's cue path. The ROM's mixer is DSP microcode that is
  not present in the executable, and no part of the audio signal path is ported."

Sentences that would be **false**, and stay banned regardless of how good the build gets:

- "A byte-exact port." "A 1:1 port." "Pixel-perfect." "Fully verified."
- Any percentage derived from the §1.3 ceiling presented as achieved coverage — claim-honesty
  rule 6, and the error it names is three orders of magnitude.
- Any single blended number for GX verification — rule 4.
- Any total that sums `transcript_green` or `boundary_green` with `oracle_green` — rule 3.
- "N units ported", where N counts `compile_only` inventory — rule 1.
- **New, and the one this spec introduces the risk of:** "N functions ported", where N
  counts functions that *executed*. Execution is not verification — §6's new rule 9.

The honest short form, if one is needed:

> **A browser build in which the GameCube game's own code runs, with its evidence stated
> function by function.**

Not "a 1:1 port". The qualifier is not modesty; it is the difference between a true
sentence and a false one, and this project's entire method is built on knowing which is
which.

---

## 9. What the owner must decide or supply

Separated from what the pipeline can do on its own. Everything not listed here is
downstream of these and is pipeline work.

### 9.1 Decisions

1. **GPU allocation and the alternation cadence.** Capture and compile are mutually
   exclusive on this rig and §6's revised path alternates between them. How the slot is
   shared — and whether `omr-sweep` keeps priority 1 — is a resource decision only the
   owner can make. **Blocks:** P0.2, P2, P3.5, P3b, P4.1, P4.3, P6. This is the single
   scheduling input on which every phase depends.
2. **Audio scope.** Accept §3.5 option B — bridge the ROM's cue dispatcher to the
   recreation's OGG path, keep `dspMicrocodeAbsent: true`, and **scope audio out of the 1:1
   claim in writing**? Or fund option C (a MusyX-shaped mixer with no oracle) or D (DSP
   emulation, a different project)? **Blocks:** P4.5, and the claim text in §8.3.
3. **At least one recorded DTM.** The highest-leverage single input in the plan (R8).
   Without it there is no whole-frame fidelity claim at all — only liveness and a
   per-function evidence map. The minimum ask is **one recording through boot → title →
   battle → results**, not a library. Note the rig cannot record one today: `--save_state`
   is load-only and there is no interactive input desktop
   (`research/tools/dolphin-trace/README.md:81-93`), so this needs a machine or a method the
   owner supplies. **Blocks:** G5(b), and the trace-delta adapter route.
4. **Disc bytes and their legal story.** The repository contains none and must not. A real
   disc behind the provider interface is the only way ROM asset paths execute for real, and
   it needs a decision about how a user supplies their own copy and whether the browser is
   allowed to hold 1.4 GB ([`audio-dvd-hle-host.md:632-637`](audio-dvd-hle-host.md)).
   **Blocks:** P4.6 and every asset-streaming code path.
5. **The ring-0 artifact.** `auto-c0006-013` bundles one of the spine's own loop callees,
   so ring 0 is either that whole unit (accepting the bundled callee as linked) or the
   preflight build in `research/decomp/spine-boundary/` (forfeiting the
   regenerate-from-the-queue property the corpus-correction loop depends on). **Blocks:**
   P3.4.
6. **Device scope.** Accept desktop-class only, with a published minimum spec, as the price
   of the 2.155 GB address-identity layout? **Blocks:** P7.
7. **Whether to publish a build that has passed G5(a) but not G5(b).** A module that drives
   frames with no behavioural claim is a legitimate milestone and a serious overclaim risk.
   §6's rule 9 and Y1's labelling machinery make it publishable safely; whether to publish
   it at all is a judgement call. **Blocks:** P7.
8. **Whether `collision-core` and `knockback-core` stay in `research/decomp/port-units/`**
   given R10 — no committed result artifact, and one recorded at 28,121/32,153.

### 9.2 Supplied inputs

- The retail GG4E disc / ISO. Already the throughput ceiling for everything the trace tools
  do; `sites` decodes `boot.dol` out of it.
- New savestates, if a non-battle state class needs one the navigator cannot construct —
  the rig cannot write savestates.
- The DTM of decision 3.

### 9.3 What the pipeline does autonomously

Everything downstream of those: scenario generation via `force_navigator cover` (42
scenarios already, all `dtm: null`), plan derivation (`sites`, 810 plans, ~0.5 s each),
scouting, capture, replay, corpus correction through the sanctioned revoke-and-rebuild
loop, compilation, the assembly gate and its dispatch companion, the ladder, the host
adapters, and every gate in §6 that is not marked as blocked above.

---

## 10. Reproducing every number on this page

```bash
# The doc build this page must not break
pnpm verify:docs

# §1.3 — the ceiling (needs the OGhidra checkout; not vendored)
python research/decomp/data/build_tier_survey.py --check

# §1.2 — the complete evidence inventory, and the reference_kind finding
ls research/decomp/data/oracle-results/
grep -o '"reference_kind": "[a-z_]*"' research/decomp/data/oracle-results/*.json
grep -o '"verdict": "[a-z_]*"'        research/decomp/data/oracle-results/*.transcript.json

# §1.6 — the capture-plan ceiling, the refusal split, and the "zero units ready" finding
python - <<'PY'
import json, collections
d = json.load(open('research/decomp/data/transcript-work-queue.json'))
print(d['totals'])
c = collections.Counter(r['refusal'] or 'CAPTURABLE' for u in d['units'] for r in u['rows'])
print(dict(c))
print('units full_coverage      :', sum(1 for u in d['units'] if u['full_coverage']))
print('units full AND all firing:', sum(1 for u in d['units']
      if u['full_coverage'] and u.get('observed_firing', 0) == u['exports']))
print('distinct scenarios       :', len({u['scenario'] for u in d['units']}))
PY

# §1.4 — the ladder ceiling
cat research/decomp/data/composition-ladder.json

# §1.2 — replay the spine capture (no emulator needed)
node research/decomp/oracle-harness/run-spine.mjs \
  --capture research/decomp/oracle-harness/corpora/spine-run-main-game-loop.boundary.jsonl

# §2 E4 — the stack-local class, which lives only in git history
git log -1 --format=%b 612a1934

# §1.8 — throughput. MACHINE-LOCAL: gitignored, not reproducible from a clone.
python - <<'PY'
import json, collections
ev = []
for line in open('research/decomp/generated/finish-game-port/events.jsonl',
                 encoding='utf-8', errors='replace'):
    line = line.strip()
    if line:
        try: ev.append(json.loads(line))
        except Exception: pass
g = [e for e in ev if e['kind'] == 'wasm_unit_green']
print('started', sum(1 for e in ev if e['kind'] == 'wasm_unit_started'),
      'red',     sum(1 for e in ev if e['kind'] == 'wasm_unit_red'),
      'green',   len(g))
print(sorted(collections.Counter(e['timestamp'][:10] for e in g).items()))
PY
```

Where a number came from a source file rather than an artifact, the `file:line` is inline in
the text. Where it came from the driver's gitignored state, it is labelled machine-local at
the point of use.

---

## Provenance

Written 2026-09-01 in an isolated worktree, from a re-measurement of the tree on that date.
Where a figure in an existing document disagreed with the measurement, the disagreement is
named in §1 rather than silently resolved. No number here was carried forward from an
earlier document without being re-checked.

Nothing in this document has been implemented. It proposes a path and reviews it; the
normative contract remains [`docs/playable-port-design.md`](playable-port-design.md) until
an owner review moves it.
