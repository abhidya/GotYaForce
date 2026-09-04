<div align="center">
  <img src="docs-site/public/favicon.svg" width="88" height="88" alt="GotYaForce logo">

  <h1>GotYaForce</h1>

  <p>
    An evidence-first browser recreation of <strong>Gotcha Force</strong>,
    built from the GameCube original one system at a time.
  </p>

  <p>
    <a href="https://abhidya.github.io/GotYaForce/game/">Play in browser</a>
    ·
    <a href="https://abhidya.github.io/GotYaForce/">Research Atlas</a>
    ·
    <a href="docs/matching-decompilation-spike.md">Port route: matching decompilation</a>
    ·
    <a href="docs/verification-status.md">Verification status</a>
    ·
    <a href="research/decomp/PORT-1TO1-STATUS.md">Subsystem tracker</a>
  </p>

  <p>
    <img src="https://img.shields.io/badge/status-work_in_progress-f59e0b" alt="Status: work in progress">
    <img src="https://img.shields.io/badge/TypeScript-5.6-3178c6?logo=typescript&logoColor=white" alt="TypeScript 5.6">
    <img src="https://img.shields.io/badge/three.js-r169-black?logo=threedotjs" alt="three.js r169">
    <img src="https://img.shields.io/badge/target-GG4E_%2F_NTSC--U-ff6fb1" alt="Target: GG4E / NTSC-U">
  </p>
</div>

> [!IMPORTANT]
> GotYaForce is a playable research port, not a finished replacement for the original game.
> Challenge mode runs from menus through results. Some Borg actions still use partial
> behavior while their ROM state machines are transcribed, and the automated
> recompile-the-ROM pipeline described below is **research-stage**: almost everything it has
> produced is unverified.

---

## Two tracks, and why the distinction matters

The repository runs two efforts at once. Conflating them is the single easiest way to
misread this project's status.

| | **Track 1 — TypeScript recreation** | **Track 2 — port route (matching decompilation)** |
| --- | --- | --- |
| What it is | Hand-written TS/three.js game, each system transcribed from ROM evidence | Compile candidate C with a PowerPC compiler and diff against retail bytes until byte-identical, driven by a local model. Route chosen 2026-09-04, superseding the wasm-unit pipeline below |
| Status | **Playable.** This is what ships to GitHub Pages | **Research-stage.** 405 functions byte-identical (0.2528 % of the game's instructions); the older wasm-unit pipeline's verified tiers (below) are historical, not the active route |
| Governing doc | [`research/decomp/PORT-1TO1-STATUS.md`](research/decomp/PORT-1TO1-STATUS.md) | [`docs/matching-decompilation-spike.md`](docs/matching-decompilation-spike.md), [`docs/matching-loop.md`](docs/matching-loop.md); [`docs/playable-port-design.md`](docs/playable-port-design.md) is the superseded-in-part predecessor |
| In production today | The whole game | One wasm unit (the ROM damage core, still live — see below) |

Track 2's long-term goal is to replace Track 1 subsystem by subsystem with byte-exact
recompiled ROM code. It has done that exactly once so far.

> [!IMPORTANT]
> **Route decision, 2026-09-04: Track 2's port route is now matching decompilation, not
> the wasm-unit pipeline described below.** The owner chose this after two feasibility
> spikes —
> [`docs/static-recompilation-spike.md`](docs/static-recompilation-spike.md) and
> [`docs/matching-decompilation-spike.md`](docs/matching-decompilation-spike.md). Read
> "Track 2 — matching decompilation" below for what that is, what it retires, and the
> current numbers. **The Ghidra + compile-fix wasm-unit driver
> (`finish-port --drive`) is obsolete on this route and must not be relaunched** — the
> verified-tier record further down this file (`damage-core`, `boundary_green`,
> `dispatch_green`, and so on) is kept as history, not as the active pipeline.

Known defects and open findings for both tracks live in
[`docs/audits/`](docs/audits/README.md) — a defect ledger for the game app, the port
pipeline's integrity findings, data-provenance gaps, and what still blocks a public
release. Machine-side operational knowledge is in [`docs/ops/`](docs/ops/).

---

## Track 1 — what is working

- Start-to-finish 1-player Challenge flow: force building, battles, results, Gotcha Box drops
- Browser model exports for **209 of the 219 Borg IDs on disc**; **185** have animation
  mappings; 208 have full metadata records
- Visual geometry and collision for **all 40 exported stage variants**
- ROM-derived damage, ammo, knockback, targeting, scoring, drop, and action-stream systems
- Real UI, music, voice, combat-audio, lighting, and effect assets where attribution is verified
- The **ROM wasm damage core is live in production** — the game's damage numbers come from
  recompiled ROM code, not from the TS reimplementation (see Track 2 below)
- Cross-origin isolation in dev and production, so shared-memory wasm builds can run
- A searchable research atlas over functions, data tables, Borgs, stages, mechanics, evidence

### Coverage snapshot

Regenerate every number here with the command in its row — none of them are hand-maintained.

| Area | Current state | Regenerate with |
| --- | --- | --- |
| Family action state machines | 232 ported, 93 partial, 0 missing across 325 slots | `pnpm audit:family-state-machines` |
| Family coverage audit | 119 constructor families, 208 roster entries, 0 structural errors | `pnpm audit:family-state-machines` |
| TUNED constant debt | 257 awaiting evidence, 238 DERIVED, across 38 files | `node scripts/report-tuned-constants.mjs` |
| Borg model/animation coverage | 209 static exports, 185 animated, of 219 disc IDs | `node scripts/inventory-borg-assets.mjs` † |
| Stages | 40 / 40 visual and collision exports | `pnpm manifest:stages` † |
| Challenge mode | Playable end to end | `pnpm selfcheck:1p`, `pnpm smoke:browser` |

† These read a user-supplied disc dump under `user-data/`, which is gitignored and absent
from a clean clone. Their committed outputs cannot be refreshed without one.

These describe evidence coverage, not one overall completion percentage. A `TUNED` marker is
a value still waiting on ROM or trace evidence; `DERIVED` means the evidence is cited.

### Recently fixed (2026-08)

- **Animation freeze** — finished one-shot clips accumulated in the mixer blend and stalled
  actors mid-battle. The smoke run now asserts battle actors are actually playing clips.
- **Open-window hit sentinel** — a sentinel comparison discarded live hit windows;
  **2,190 hit records restored**.
- **Cross-origin isolation** — COOP/COEP in dev and preview via Vite headers, in production
  via the vendored `coi-serviceworker.js`, with a smoke phase asserting
  `crossOriginIsolated === true` in both serving modes.

---

## Track 2 — matching decompilation (the port route)

**What it is.** Write C, compile it with a PowerPC compiler, diff the object code against
the retail GameCube image until it is byte-identical. A matched function is not *argued*
to be the same program; within the limits recorded below, it **is** the same program — and
because the artifact is ordinary C, it compiles for any target afterward, wasm included.

**Why this route, not the wasm-unit pipeline described further down.** Two feasibility
spikes ran on 2026-09-02/03: [`docs/static-recompilation-spike.md`](docs/static-recompilation-spike.md)
(mechanical PowerPC→C translation — technically strong, but a transliteration, which the
owner's brief explicitly excludes) and
[`docs/matching-decompilation-spike.md`](docs/matching-decompilation-spike.md) (matching
decompilation — the only route that produces what was asked for: real, compilable,
byte-exact source). The owner chose matching decompilation. What it retires: the Ghidra +
compile-fix wasm-unit driver (`finish-port --drive` in the OGhidra checkout) is **obsolete
on this route and must not be relaunched** — its 1,396-unit queue, the compile-fix LLM
loop, per-unit specs, the composition ladder, and the assembly gate all become obsolete
machinery under matching decomp (see the spike's §5.3 for the full list of what
disappears and why). The verification-tier work recorded further down this section
(`damage-core`, `boundary_green`, `dispatch_green`, and the rest) stays true as history
and `damage-core` stays live in production; nothing about it is retracted, but it is no
longer where new port work happens.

**Current numbers, with their honesty caveats.** The matched corpus:
[`src-match/`](src-match/README.md), registry `src-match/matched.json`.

| | |
| --- | ---: |
| Matched functions | **405** |
| Matched instructions | **1,773** |
| Share of `.init` + `.text` (701,464 instructions) | **0.2528 %** |
| Share of the 5,897 link-map `.text` functions | 6.87 % |
| Produced with zero model calls (mechanical seeders) | 392 of 405 |

Two honest discounts, stated in the registry's own README and repeated here because they
are easy to lose: **118 of the 405 (29 % of the functions, 6.7 % of the instructions) are
a single `blr`**, matched by `void f(void) {}` — true about the bytes, thin about the
program. And **no global accessor is in this corpus** — a candidate resting on a data
relocation (`r13`/`r2`-relative access) has that relocation's *symbol* masked and never
checked by the oracle, so it would match any global in the game; such verdicts are
recorded `MATCH_UNVERIFIED` and are never written to `src-match/` (104 functions refused
on this ground alone). Also: every match here is `mwcc-rs`-exact, not genuine-MWCC-exact
(`mwcceppc.exe` was never obtained; see
[`research/tools/matching-decomp/TOOLCHAIN.md`](research/tools/matching-decomp/TOOLCHAIN.md)).

**What bounds the route today is the compiler, not the model or the C.**
[`docs/matching-compiler-census.md`](docs/matching-compiler-census.md) compiled every one
of the 12,062 entry points' verbatim Ghidra C against `mwcc-rs`: only **10.07 % of the
game's instructions compile**; **87.2 % is compiler-blocked** (63.6 % the code generator
refusing to lower something it parsed, 23.6 % a front-end parse/typecheck refusal), behind
four diagnostics that together hold 63.7 % of the code. That is the binding constraint —
not GPU throughput, not model quality.

**Commands:**

```bash
# Re-verify the whole matched corpus + negative controls (408 ok, 0 failed)
python src-match/verify.py --control

# Which compiler build/flags each matched function discriminates
python src-match/verify.py --sweep

# Regenerate the compiler-capability census; --check re-derives and diffs, writes nothing
MWCC_RS=<path>/target/release/mwcc.exe python research/tools/matching-decomp/census.py
python research/tools/matching-decomp/census.py --check

# The mechanical seeder + permuter loop (no model calls; see docs/matching-loop.md)
python research/tools/matching-decomp/loop.py selftest
python research/tools/matching-decomp/loop.py run --class shape-shared --no-llm
python research/tools/matching-decomp/loop.py run --all-compilable --max-insns 9999 --no-llm
```

Full detail, including why the local 27B model on the project's GPU cannot drive the LLM
step at any usable rate (2.6 GPU-years for 25 % of the code, versus published frontier-model
loops reaching 88.78 % of a same-sized GameCube title in ~7 months) is in the spike's §4 and
§6.2, and the mechanical-loop results (392 free matches, the permuter's measured
zero-contribution finding) are in [`docs/matching-loop.md`](docs/matching-loop.md).

---

## Track 2, historical — the wasm-unit port pipeline

> [!NOTE]
> **Superseded as the port route by matching decompilation, 2026-09-04** (see above). This
> section is kept because the verified results below are real and `damage-core` is still
> live in the shipped game — not because the pipeline they came from is still how new port
> work happens. Do not relaunch `finish-port --drive`.

The pipeline takes decompiled PowerPC-derived C out of the Ghidra corpus, slices it into
compilable units, drives a local LLM to make each unit compile against a shim seed, links it
to WebAssembly with emscripten, and then tries to prove the result behaves like the real
console. The design contract — reviewed adversarially through four FAIL rounds to a **v5
PASS verdict** — is [`docs/playable-port-design.md`](docs/playable-port-design.md).

### Verification tiers — read these literally

| Tier | What was proven | What was **not** proven |
| --- | --- | --- |
| `compile_only` | The unit compiles and links to wasm | **Nothing about behavior.** This is inventory, not progress |
| `oracle_green` | Its full corpus replays byte-exact against an independent oracle, per call | Coverage beyond the replayed corpus |
| `boundary_green` | For a nonterminating spine function, every captured callee boundary and spine-owned write is byte-exact up to the cut | The same as `oracle_green` — it never upgrades into one. Nothing outside the declared owned regions; the callees are stubs replaying captured values |
| `transcript_green` | For an ordinary returning function, the port emits the identical out-of-unit call transcript (set, order, arguments) and returns the identical value over N recorded cases | **No write-set comparison at all.** Strictly weaker than `oracle_green` and never upgrades into one. A per-**function** artifact, deliberately not a unit tier in the driver's ledger |

`boundary_green` was **first reached on 2026-08-30** by `run_main_game_loop` — 274/274
calls, `research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json`. What
that verdict is and is not worth (the ROM passes it no arguments, and its one owned region
never varied) is written out in
[`docs/verification-status.md`](docs/verification-status.md) §5.1. The driver still has no
code path to record either weaker tier in unit state; both are per-artifact standards today.

> **How much of the ROM can ever be verified.** Measured, not projected: **652 of 10,954
> functions (6.0 %)** can carry an auto-derived `oracle_green` write-comparison spec at all,
> **8,197 (74.8 %)** are reachable by `transcript_green`, **8,849 (80.8 %)** by some tier,
> and **2,105 (19.2 %)** by none. Units with full export coverage: **378 of 1,396 (27.1 %)**.
> These are *eligibility* ceilings, not results. Artifact:
> [`research/decomp/data/verification-tier-survey.json`](research/decomp/data/verification-tier-survey.json);
> the full picture with the caveats is
> [`docs/verification-status.md`](docs/verification-status.md).

### Current state (2026-08-30)

Repository-verifiable, from committed artifacts:

| | Count | Where |
| --- | --- | --- |
| Staged unit artifacts, **all tier `compile_only` (UNVERIFIED)** | **112** | `research/decomp/port-units-staging/*/provenance.json` |
| Promoted units | **3** — `damage-core`, `collision-core`, `knockback-core` | `research/decomp/port-units/` |
| Units in production | **1** — `damage-core` (+ its threads relink) | `apps/game/public/rom/` |
| Unit-level oracle verdicts on record | 2 `pass`, 3 `partial`, 2 `fail` | `research/decomp/data/oracle-results/*.json` |
| `transcript_green` results | 3 — 2 `pass`, 1 `fail` | `research/decomp/data/oracle-results/*.transcript.json` |
| `boundary_green` results | 1 `pass` — `run_main_game_loop`, 274/274 calls | `research/decomp/data/oracle-results/spine-run-main-game-loop.boundary.json` |
| Dolphin-captured corpora | **18** (+1 TS-differential POC), covering 5 units and the spine | `research/decomp/oracle-harness/corpora/` |

Queue-level, from the driver's own state file — **machine-local and untracked**, so these
numbers are not reproducible from a clone (`research/decomp/generated/finish-game-port/`
is gitignored except for the knowledge registry):

| | Count |
| --- | --- |
| Units in the queue | **1,396** |
| `pending` | 1,131 |
| `red_retryable` | 147 |
| `green` | 107 — of which 104 `compile_only`, 1 `oracle_green`, 2 untiered legacy |
| `structural_ineligible` (settled, permanent) | 10 |
| Driver's own **verified fraction** | **0.93 %** |

Two units replayed **behaviorally divergent** against a reference:

- **`auto-c0035-002`** — `FAIL`, **6,250 / 20,000 cases byte-exact**, 2 of 8 exports covered.
  It compiles, it links, and it passed an N=5 assembly gate. Its behavior is wrong. By
  design a FAIL flags `oracle_divergent` and changes no tier, so it is *still recorded as a
  green `compile_only` unit* — which is precisely why `compile_only` must never be read as
  progress.
- **`auto-c0001-005`** — `FAIL`, 0 / 200. The more useful one: root-causing it proved
  *Ghidra* was wrong, not the port. See the correction loop below.

And one that passed everything it was asked and still is not verified:

- **`auto-c0001-007`** — 120 / 120 captured cases byte-exact, verdict **`partial`**, because
  the spec covers 1 of its 8 exports. Full-coverage or it does not count.

`damage-core` is the one end-to-end success: 4 functions, **26,232 / 26,232 replayed cases
byte-exact**, relinked for shared memory and re-verified with a byte-identical verdict, and
serving the live game.

### The workflow, with real commands

The driver lives in **OGhidra**, an external tool checkout at `research/tools/OGhidra` that
is **not vendored into this repository** (`tools/` and friends are gitignored; you clone it
separately). All driver verbs run from inside that checkout:

```powershell
cd research/tools/OGhidra

# The port run itself. Requires OGHIDRA_PORT_MODE=wasm_units in the env or .env;
# this is the argv the rig supervisor launches.
.venv\Scripts\python.exe main.py finish-port --drive --until-blocked

# Trace-verify one staged compile-only unit against the real game:
# refresh capture plans, capture per-export cases in a headless Null-backend
# Dolphin, replay through run-unit.mjs, record the verdict in canonical state.
.venv\Scripts\python.exe -m src.port_wasm_units verify-unit --unit <name> --cases 120

# Budgeted batch of the same, product-priority first. Operator-run, not
# supervisor-rotated. Refuses to start while a driver is alive.
.venv\Scripts\python.exe -m src.port_wasm_units verify-sweep --max-units 3 --max-seconds 3600

# Promote a staged green by re-running its recorded oracle sidecar.
.venv\Scripts\python.exe -m src.port_wasm_units reverify-unit --unit <name>

# Composability check over the last N green/staged units (--all sweeps everything).
.venv\Scripts\python.exe -m src.port_wasm_units assembly-gate --n 5

# Settle a provable contradiction PERMANENTLY, through the journal.
# --status takes only `green` or `structural_ineligible`.
# Hand-editing wasm-units-state.json is forbidden — see AGENTS.md.
.venv\Scripts\python.exe -m src.port_wasm_units settle-unit --unit <name> \
    --status structural_ineligible --reason "<file:line of the contradiction>"
```

Other verbs: `revoke-unit`, `invalidate-diagnosis`, `backfill-artifact-digest`,
`d5-migrate`, `f4-recheck`. Every one of them takes the driver lock and emits a journal
event; none of them edit artifacts by hand.

Repository-side tooling. `research/tools/dolphin-trace/` **is** tracked here (the rest of
`research/tools/` is gitignored); none of these have npm wrappers:

```bash
# Capture per-call oracle fixtures from the real game in Dolphin (GDB-RSP stub).
python research/tools/dolphin-trace/capture_oracle.py --help   # launch|stop|probe|scout|capture

# Replay a unit's corpus (oracle_green standard).
node research/decomp/oracle-harness/run-unit.mjs --unit <name>

# Replay a nonterminating spine at its callee boundary (boundary_green standard).
node research/decomp/oracle-harness/run-spine.mjs --capture <capture.jsonl> [--wasm <path>]

# Composition ladder rungs (scratch lane; never the live pipeline).
python scripts/composition_ladder.py init   --scratch <dir>
python scripts/composition_ladder.py select --scratch <dir>
python scripts/composition_ladder.py rung   --scratch <dir> --tag rung0 --units <csv>
python scripts/composition_ladder.py ledger --scratch <dir> --rungs "rung0;rung1" \
    --out research/decomp/data/composition-ladder.json
```

### Where the pipeline is blocked

- **The composition ladder is stopped at rung 1.**
  ([`docs/composition-ladder.md`](docs/composition-ladder.md),
  [`research/decomp/data/composition-ladder.json`](research/decomp/data/composition-ladder.json))
  Rung 0 (N=5) linked clean — 40-thunk dispatch table, zero contested symbols. Rung 1 (N=10)
  now also passes clean after the registry correction of 2026-08-29: `substitution: null`,
  `conflicts: []`, ratio **0/38** against rung 0's 0/40, 78 companion thunks. Rung 2 has not
  been attempted successfully: it needs two rebuilds behind it (`auto-c0011-012`, then
  `auto-c0011-011`), so **rung 2 is now a rebuild-scheduling problem, not an ABI or owner
  decision** — a real change in kind, but the ceiling is still N=10. Rung 1 of a
  5 → 10 → 20 → 40 → … → 1,396 sequence is very early, and the whole run happened in a
  scratch lane, never the live pipeline.
- **Verification does not scale yet.** 1,396 units queued, 3 `oracle_green`. Of the 10,954
  functions, **80.8 % are eligible** for some verification standard and 19.2 % are eligible
  for none ([`docs/verification-status.md`](docs/verification-status.md)) — eligibility, not
  results; the gap between the two is three orders of magnitude. Trace capture needs
  the real game running in Dolphin with a user-supplied disc, which is the throughput
  ceiling. A 90-second scout across 201 callee-free staged functions in a live 2v2 fight
  found exactly **two** that fire at all.
- **No DTM movie exists.** The design's coverage prerequisite (G4/I3) is **unmet**: every
  capture so far rides a savestate plus synthesized input, so they are fresh samples, not
  replayable traces.
- **`@gf/rom-runtime` is a scaffold.** The composed-module execution runtime — worker,
  Atomics bridge, reentrant dispatch, adapters, ledger — exists and self-tests, but
  **nothing in `apps/game` imports it yet**. It is not on the production path.
- **The G2/H3 dispatch companion is opt-in**, behind
  `OGHIDRA_PORT_DISPATCH_COMPANION=1` (OGhidra `src/port_dispatch_companion.py`).

### The corpus-correction loop

When a unit is proven divergent, the fault may be in the *decompilation*, not the port.
[`research/decomp/corpus-correction-loop.md`](research/decomp/corpus-correction-loop.md)
is the sanctioned path, first executed 2026-08-26 on `auto-c0001-005` / `FUN_8000fc2c`:
Ghidra had mis-lifted the ROM's Y-zeroing store as a dead local (stack aliasing), so the
camera-distance solver used a 3D distance where the ROM uses a horizontal one.

It works because **`unit.c` is regenerated output and the chunk is the source of truth** —
fix `research/decomp/ghidra-export/chunk_NNNN.c`, revoke the verdict, and the driver's normal
loop rebuilds the unit from corrected source. No driver changes, no hand-edited artifacts,
no hand-edited state.

### Threads relink

A verified unit relinked for shared memory has **different bytes than what was verified**, so
[`docs/threads-relink-reverify.md`](docs/threads-relink-reverify.md) suspends its
`oracle_green` / `boundary_green` status until the full corpus replays byte-equal against the
relinked module. `damage-core` passed this on 2026-08-26 (26,232/26,232, verdict-delta none).
A compile-only threads build is inventory, not progress.

---

## Quick start

### Requirements

- Node.js 20 or newer
- pnpm 9
- A modern browser with WebGL support

```bash
git clone https://github.com/abhidya/GotYaForce.git
cd GotYaForce
corepack enable
pnpm install --frozen-lockfile
pnpm dev
```

Open the local URL printed by Vite, normally `http://localhost:5173`. No disc image is
needed for the normal development loop.

### Controls

| Action | Keyboard | Standard gamepad |
| --- | --- | --- |
| Move | `WASD` or arrow keys | Left stick |
| Jump / A | `Space` or `J` | A |
| Attack / B | `K` or `B` | B |
| Special / X | `L` or `X` | X |
| Hyper / Y | `Y` or `H` | Y |
| Dash | `Shift` | Stick-snap movement |
| Next / previous target | `R` or `Tab` / `Q` | Right / left trigger |
| Ally lock | `Z` | Left shoulder |

### Useful query parameters

| Parameter | Effect |
| --- | --- |
| `?romwasm=threads` | Load the shared-memory relink of the ROM damage core instead of the default exported-memory build |
| `?romwasm=0` | Force the TypeScript damage port and skip the ROM core entirely (debugging) |
| `?composed=<n>` | Boot the composed-module **dispatch pilot** for n frames. Synthetic adapters, unverified units, no behavioural claim — the page says so on screen while it runs |
| `?debugOverlay=1` | Show the sim-state overlay (also toggled with `` ` ``). Its first line names which damage core is producing the numbers |

Which damage core is live is always observable, never silent: `<html data-gf-rom-damage>` is
`rom-live`, `ts-port-forced` or `ts-port-degraded`, `window.__romDamageStatus` carries the
reason, `window.__romDamage` exists only while the ROM core is installed, and anything other
than `rom-live` raises an on-screen banner (a genuine failure also logs `console.error`,
which fails the production smoke).

---

## How the port is built

GotYaForce is not a clean-room reinterpretation of a wiki description. Mechanics are promoted
to ROM-derived only when they can be tied back to decompiled PowerPC code, DOL bytes, decoded
tables, extracted assets, or controlled Dolphin traces.

```text
boot.dol + disc assets + Dolphin traces
              │
              ├──────────────────────────────┐
              ▼                              ▼
   decompilation and evidence maps    wasm-unit pipeline (Track 2)
              │                              │
              ▼                              ▼
  deterministic extract/convert       compile → link → trace-verify
              │                              │
              ▼                              ▼
 TypeScript runtime + self-checks  ←── oracle_green units replace TS seams
              │
              ▼
        browser recreation
```

The actor runtime mirrors the original cue dispatch, action tables, phase handlers, stream
VM, and physics integration. Families land independently; Borgs without a completed family
port continue through the generic combat path instead of being falsely labeled exact. See the
[`ROM porting guide`](packages/combat/src/rom/PORTING.md) for the implementation model.

---

## Repository map

| Path | Purpose |
| --- | --- |
| [`apps/game`](apps/game) | Vite + TypeScript + three.js browser game (the deployed app) |
| [`packages/combat`](packages/combat) | Battle simulation, ROM-faithful actor runtime, wasm damage-core loader |
| [`packages/missions`](packages/missions) | Challenge flow, scoring, stages, Gotcha Box logic |
| [`packages/assets`](packages/assets) | Borg and stage catalogs, generated asset metadata |
| [`packages/render`](packages/render) | three.js loading and rendering helpers |
| [`packages/physics`](packages/physics) | ROM-derived movement integration and collision |
| [`packages/formats`](packages/formats) | Disc/archive format parsers (AFS, PZZ, TPL, HSD anim, hit bins) |
| [`packages/rom-runtime`](packages/rom-runtime) | Composed-module execution runtime. Wired into the app behind `?composed=` only, as a **dispatch pilot with synthetic adapters and no behavioural claim** (`docs/composed-pilot.md`); it does not serve gameplay |
| [`packages/audio`](packages/audio) · [`packages/ai`](packages/ai) · [`packages/core`](packages/core) | Supporting runtime libraries |
| [`packages/save`](packages/save) | **Empty on purpose** — no save layer exists here. Persistence lives in `apps/game/src/sim/getStorage.ts` and `SelectForce.ts`; see the package's own header and `docs/audits/game-app-defect-ledger.md` §3.6 |
| [`packages/test-fixtures`](packages/test-fixtures) | Shared synthetic fixtures for tests |
| [`docs`](docs) | Port design contract, composition ladder, threads relink runbook |
| [`docs-site`](docs-site) | VitePress research atlas (deployed to Pages root) |
| [`scripts`](scripts) | Extraction, conversion, generation, audit, self-check, and smoke tools |
| [`research/decomp`](research/decomp) | Ghidra corpus, evidence indexes, oracle harness, port units |
| [`research/tools/dolphin-trace`](research/tools/dolphin-trace) | Per-call oracle capture from the real game |
| [`research/format-specs`](research/format-specs) | File-format specifications and provenance |
| `research/tools/OGhidra` | **External checkout, not vendored** — the port driver lives here |

---

## Useful commands

```bash
# Game
pnpm dev                     # dev server (COOP/COEP headers included)
pnpm build                   # build all workspace packages
pnpm --filter game build     # production build with the /GotYaForce/game/ base
pnpm typecheck

# Shared gate (what CI runs)
pnpm verify:contributor      # repo policy + typecheck + browser gate + combat lifecycle
                             # + importer test + production game build
pnpm test:oracle             # deterministic oracle-harness evidence
pnpm verify:docs             # atlas build; VitePress fails on broken internal links

# Regression self-checks
pnpm selfcheck:game-session
pnpm selfcheck:1p
pnpm selfcheck:challenge-stages
pnpm selfcheck:rom
pnpm selfcheck:hud
pnpm audit:family-state-machines

# Headless browser smoke gates
pnpm smoke:browser                                              # playable route, animation liveness, COI
GF_SMOKE_ROM_HIT=1 pnpm smoke:browser                           # + assert the ROM wasm damage core is live
GF_SMOKE_ROMWASM=threads GF_SMOKE_ROM_HIT=1 pnpm smoke:browser  # + the shared-memory relink under COI
pnpm smoke:rom-runtime                                          # @gf/rom-runtime self-test phase

# Research atlas
pnpm atlas:dev
pnpm atlas:build
GF_ATLAS_SKIP_MODELS=1 pnpm atlas:build   # text/data only, skips the heavy model copy

# Regenerate derived reports
node scripts/report-tuned-constants.mjs   # research/tuned-burndown.md
node scripts/reorg-decomp.mjs             # research/decomp/organized/ (gitignored)
node scripts/build-decomp-evidence-index.mjs
```

The family audit defaults to structural validation. It is expected to report partial slots
until the port is complete; strict completeness is a finish-line gate.

---

## Disc data and generated assets

The repository targets the US release (`GG4E`, NTSC-U). A disc image is never required for
the normal browser-development loop and **must not be committed**. Extraction and
regeneration workflows expect a legally obtained, user-supplied dump under `user-data/`,
which is gitignored — as are `research/decomp/organized/`, all `dist/` output, savestates,
and local model transcripts.

The HSD asset pipeline runs offline:

```text
GameCube archives → HSDRaw / HSDRawViewer → Collada or GLB + PNG textures → browser assets
```

The `_mdl.arc` model container is **HSD DAT** (HAL Sysdolphin) — solved 2026-06-30, spec and
validation evidence in
[`research/format-specs/arc-hsd-format.md`](research/format-specs/arc-hsd-format.md). There is
intentionally **no runtime TypeScript parser** for it: conversion happens at build time, and
[`packages/formats/src/mdl-arc.ts`](packages/formats/src/mdl-arc.ts) is a documented stub
explaining why. (Older research notes, including
[`research/PHASE0_RESEARCH.md`](research/PHASE0_RESEARCH.md), still describe the model format
as the project's unsolved blocker; that snapshot predates the solution and carries a
correction banner.)

---

## Deployment

One GitHub Pages site, built by
[`.github/workflows/deploy-pages.yml`](.github/workflows/deploy-pages.yml) on every push to
`main`:

- `https://abhidya.github.io/GotYaForce/` — the research atlas
- `https://abhidya.github.io/GotYaForce/game/` — the playable game

`apps/game/vite.config.ts` sets the `/GotYaForce/game/` base for production builds, so
runtime URLs must go through the app's `publicUrl` helper rather than absolute `/…` paths.
Cross-origin isolation comes from Vite response headers in dev/preview and from the vendored
`coi-serviceworker.js` in production. Full detail in [`DEPLOY-PLAN.md`](DEPLOY-PLAN.md).

`apps/game/server.mjs` is a standalone WebSocket room-server prototype. Nothing in the client
connects to it; treat online multiplayer as unimplemented.

---

## Contributing

Start with [`CONTRIBUTING.md`](CONTRIBUTING.md) and the
[atlas contributor guide](docs-site/contributing/). Agents operating the unattended port rig
must read [`AGENTS.md`](AGENTS.md) first — it documents the one correct way to stop the
pipeline and the failure modes of every shortcut.

The highest-value contributions are small and evidence-backed:

1. Pick one family and one action index from the
   [coverage audit](research/decomp/family-state-machine-coverage.md).
2. Trace its constructor, dispatcher, variant table, phase functions, helpers, and constants.
3. Preserve unresolved host behavior as an explicit blocker.
4. Add boundary assertions for every transition.
5. Run the ROM self-check and family audit before opening a pull request.

Please do not replace unknown behavior with plausible constants and call it 1:1. In this
project, an honest `TUNED`, `PARTIAL`, `BLOCKED`, or `compile_only` label is better than an
unsupported exactness claim.

---

## Legal

Gotcha Force, its characters, names, and original assets are property of their respective
rightsholders. This is an unofficial preservation and reverse-engineering project and is not
affiliated with or endorsed by Capcom or Nintendo. No disc image, encryption keys, or
proprietary SDK is distributed by this project.
