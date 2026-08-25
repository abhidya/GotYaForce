# Playable-Port Design — making the pipeline converge on the 1:1 game

Status: DRAFT FOR OWNER REVIEW. The port is stopped (manual gate paused, GPU ceded to
omr-sweep) and may not run again until this design is reviewed and approved.

Date: 2026-08-25. Author: orchestrator session. Everything below is grounded in measured
session evidence, cited inline.

## 1. The problem with the port as it ran

The driver optimized for the wrong terminal state. Its loop was:

    decompiled C -> LLM header-fix -> compile -> N=5 assembly gate -> STAGING

88 units reached "green"; **85 of them are `compile_only`** — meaning "the C compiled",
not "it behaves like the ROM" — and **zero of the 88 flow anywhere the game can use
them**. The driver's own `_check_unverified_buildup` invariant fired 37+ times flagging
exactly this. Compiling was never the goal; it was mistaken for progress because it was
the only stage that was automated end-to-end.

A 1:1 playable port requires each unit to clear THREE stages, not one:

    COMPILED  ->  VERIFIED (byte-exact vs the real game)  ->  PLAYING (wired into the app)

Exactly one unit has cleared all three: `damage-core` — byte-exact over 26,232 replayed
cases, arena bound byte-for-byte to two independent console-RAM captures, running as the
game's live damage implementation, proven by landed hits in a production browser battle
(`ROM combat hit PROVEN: computeBaseDamage 256 -> 277`). That unit is the existence proof
for the whole design: every mechanism below is the generalization of how damage-core got
through.

## 2. Design principle

**A unit is DONE when it computes in the playing game, byte-identically to the console.
Nothing else counts.** The pipeline must be re-pointed so every stage serves that
definition, and its progress metric must be "units playing" (today: 1/1396), never
"units compiled" (today: 88).

## 3. The three stages, concretely

### Stage A — Compile (exists, keep, two amendments)

The current driver: LLM header-fix loop, import whitelist, N=5 assembly gate,
ABI canonicalization against the owner registry. It works — 36 units/day measured — and
its gates are sound (session evidence: every gate refusal investigated this session was
either correct or fail-safe).

Amendments (both bounded, both from measured failure classes):
1. **Per-unit SDK declarations at generation time.** The generator emits, per unit, only
   the `gnt4_*` declarations that unit's `unit.c` actually calls, from the
   corpus-validated canonical set (68 signatures, return types settled by uVar-capture
   evidence). This kills the implicit-declaration/`collision_stub` class WITHOUT the
   +1400-token prompt bloat that the bulk-seed attempt proved fatal (VRAM ceiling:
   16384-ctx 27B fills 94% of the 1080 Ti; units needing >16384 tokens get 409s).
   The reverted erosion guard stays out: seeds contain wrong `void` returns the model
   must be free to correct (auto-c0020-008 evidence).
2. **Terminal classification for over-budget units.** Units whose prompt exceeds the
   serving context are parked by the zero-delta mechanism already (verified: no unit
   context-red twice) — expose them in the summary as `awaiting_larger_context` so they
   read as a hardware queue, not failures.

### Stage B — Verify (build; this is the pivot)

The TS-differential route is exhausted — measured: only 2 of 133 eligible units have
every function port-grade, both already verified. The ~1,300 remaining units have no TS
reference, so the ONLY byte-exact oracle is the real game itself:

**Dolphin trace oracles.** Feasibility is proven on this rig this session:
- Bundled Dolphin 2606-97 boots the real GG4E disc deterministically
  (interpreter core, single thread; boot recipe documented in memory).
- **GDB stub confirmed LISTENING** (config key `[General] GDBPort` — found by reading
  the exe; the socket came up).
- Save states + 2x24MB MEM1 captures exist; the oracle arena was verified byte-identical
  against them, proving console memory converts into verification evidence.

Mechanism (generalizes the existing harness, which was deliberately left
trace-compatible via `reference_kind`):
1. RSP client (Python, no new tooling class — port stack is Python-only) sets
   breakpoints at a unit's function entries, plays a recorded battle (DTM replay for
   determinism), captures (args, referenced memory, return, memory writes) per call.
2. Captures serialize into the EXISTING corpus format; the EXISTING `run-unit.mjs`
   harness replays them against the unit's wasm. Byte-equal => `oracle_green`.
3. The driver's EXISTING sidecar overlay (`_effective_oracle`) and promotion path then
   promote verified units to `port-units/` with no driver redesign — that machinery is
   already written and reviewed.

GPU note: Dolphin capture must never contend with the LLM (session evidence: Dolphin
held D3D11 while the port ran). Under this design it cannot: capture runs only while
the port is paused, or capture-vs-compile alternates on the arbitration mechanism.

### Stage C — Play (generalize the proven seam)

damage-core established the integration pattern:
    unit.wasm + arena served from `apps/game/public/rom/` -> loader instantiates with
    JS shims at original GC addresses -> override seam in the TS module ->
    boot-time fidelity gate (wasm vs TS on the real input domain) -> live, with
    fallback to TS on any failure -> production smoke asserts the ROM path served play.

Generalization: one loader + one seam REGISTRY instead of a bespoke file per unit.
Each promoted (`oracle_green`) unit ships a small manifest (exports, scratch encoding,
shims needed — all already recorded by its spec) and the registry installs it behind
the matching TS module's seam. Adding a verified unit to the game becomes a manifest
entry, not hand-wiring. The fidelity-gate rule from the fractional-basePower bug is
LAW here: the gate must sample the input domain the game actually produces, not a
convenient one.

## 4. What "reaching the destination" means, measurably

The pipeline's summary line changes from green counts to a three-column ledger:

    compiled X / verified Y / playing Z   (of 1,396)

Convergence = Z growing. The driver loop becomes: compile the next unit; whenever a
trace corpus exists for a compiled unit, verify it; whenever a unit verifies, promote
and emit its play-manifest. All three run from the same queue discipline that exists
today.

## 5. Order of work (after review approval)

1. Stage-A amendment 1 (generator-side SDK declarations) — small, kills the top red class.
2. Stage-B pilot: trace-capture ONE already-compiled staged unit end-to-end to
   `oracle_green` via the existing promotion path. This is the single riskiest new
   mechanism; nothing else proceeds until it works.
3. Stage-C registry: generalize the damage-core loader; wire the pilot unit in;
   production smoke proves it plays.
4. Only then: run the three-stage loop continuously, under whatever GPU arbitration
   the rig lands.

## 6. Review checklist for the owner

- [ ] Is "done = playing byte-identically" the right terminal definition?
- [ ] Stage B: accept Dolphin-GDB capture as the verification oracle?
- [ ] Stage C: accept the seam-registry generalization of damage-core's pattern?
- [ ] Pilot-first ordering (one unit end-to-end before any scale)?
- [ ] Resume the port only after items 1-4 are approved?

## 7. Session evidence index

- damage-core end-to-end: commits `b61440f3`, `cd547226`, `ef050286` (fractional fix)
- TS-route exhaustion, VRAM ceiling, seed classes, erosion-guard revert, Dolphin
  feasibility: memory files `oracle-differential-route-exhausted`,
  `large-unit-context-vram-ceiling`, `sdk-shim-seed-gap`,
  `phase-a-dolphin-feasibility`, `canonical-header-ambiguous-append`
- Port stopped + GPU ceded: `D:/rig/state/manual-gate.json` (by: oghidra-port)


---

# ADVERSARIAL REVIEW (2026-08-25) — v1 FAILS the requirement; v2 corrections below

Reviewed against the actual requirement: **a fully 1:1 port of the game, playable.**
Four material failures found in v1. Each is stated with evidence, then the correction.

## F1 — v1's terminal state is not the ported game; it is the TS game with grafts

The seam-registry (v1 Stage C) substitutes individual ROM functions behind seams in the
EXISTING TypeScript engine. Its asymptote is "a TS recreation whose leaf computations are
ROM-computed" — the frame loop, scheduling, call graph, and composition remain the
recreation, forever. That is not a 1:1 port of the game; it is a TS game with an
increasing number of verified islands.

**Correction (v2 terminal architecture):** the destination is the ASSEMBLED module — the
N-unit composed wasm the assembly gate already builds and links (shared linear memory,
original GameCube addresses) — grown until it contains the ROM's call graph including its
own main loop, with the browser app reduced to a HOST: rendering, audio, input, and DVD
backends behind the SDK seam. The end-state is boot.dol's code executing in one wasm
module with a high-level host — and the TS engine is SCAFFOLDING that shrinks as the
composed module grows. The seam-registry survives only as the transitional mechanism that
lets verified pieces play (and be regression-tested in play) before the composed module
can stand alone.

## F2 — v1 ignores the SDK layer entirely: 996 functions with 6 verified shims

Measured: **996 functions are excluded as `sdk_prefix`** ("never ported by design"), the
corpus references at least 68 distinct `gnt4_*` entry points, and exactly **~6 shims
exist and are oracle-validated** (damage/knockback/collision specs). A "fully 1:1 playable"
game calls the SDK constantly — matrix/quaternion math, GX graphics, OS, DVD, audio. v1
contains no plan for the other ~62 referenced shims, no verification story for any shim,
and no accounting for the long tail of the 996.

**Correction (v2 Stage D — SDK seam):** every SDK function the composed module imports
gets a host implementation with the SAME verification bar as ported units: trace-captured
input/output pairs from the real game, replayed against the shim. Math/OS shims are small
and verifiable this way; GX/audio/DVD are the HLE host boundary (F1) and are verified at
the observable-behavior level (framebuffer/audio-buffer/file-read equivalence), stated
honestly as such. The shim ledger (implemented/verified per symbol) joins the convergence
metric.

## F3 — per-unit wasm instances cannot compose a game: shared state diverges

The proven integration pattern instantiates EACH unit with a PRIVATE memory and arena
copy (wasmDamageCore.ts). Two units sharing mutable ROM state (HP mirrors, bss arrays,
struct pools) in separate instances read/write DIFFERENT copies — state diverges the
moment two wired units touch the same address. v1 Stage C scales this pattern; it cannot
produce a coherent game beyond a few disjoint islands.

**Correction:** all wired units share **one** WebAssembly.Memory (the composed module's),
one arena, original addresses — which is exactly what the assembly gate already produces
per window. Stage C v2 wires the COMPOSED module once and routes seams into its exports;
individual-instance wiring is only permissible for provably-disjoint state (damage-core
qualifies; it was checked — most units will not).

## F4 — trace verification is bounded by play coverage, and v1 has no coverage plan

Trace oracles prove equivalence ON OBSERVED CASES. "Record a battle" exercises a sliver
of 10,954 functions: menus, 200+ borgs, every stage, every mode, attract, shop, save —
most code runs only under inputs no single battle produces. v1 has no plan for reaching
the code, so "verified" would silently mean "verified on whatever we happened to play."

**Correction:** a coverage LEDGER drives capture: per function, hit-count from traces
(the GDB stub counts breakpoint hits cheaply). Capture sessions are authored per
subsystem as DTM replays (deterministic, re-runnable), and the convergence metric gains a
fourth column: functions EXERCISED. Uncalled code is reported as unverified-unreachable,
never bundled into a byte-exact claim. The claim discipline: "byte-exact on N recorded
cases across M call sites", per unit, in the result artifact — the damage-core standard
applied honestly at scale.

## Residual risks v2 states plainly (no design can remove them)

- ~9+ units exceed the serving-context/VRAM ceiling on current hardware; they queue
  behind a model/hardware change, tracked, not hidden.
- 2 SDK signatures remain unsettled pending a real reference.
- Anti-piracy/timing-sensitive code may resist HLE hosting; discovered empirically.

## Revised order of work (supersedes v1 §5)

1. Stage-A amendment (generator-side SDK declarations) — unchanged.
2. **Trace pilot** — unchanged gate: one staged unit to `oracle_green` end-to-end.
3. **Composed-module pilot (new, from F3):** wire one ASSEMBLED N-unit module (shared
   memory) into the app behind seams; prove two units sharing state stay coherent in play.
4. Coverage ledger + first authored DTM capture set (from F4).
5. SDK shim ledger + verification harness for math/OS shims (from F2).
6. Only then scale the loop; convergence metric becomes:
   `compiled / exercised / verified / playing-composed of 1,396 (+ shim ledger)`.

v1's checklist is withdrawn. The review question for the owner is single:
**approve the v2 terminal architecture (composed module + HLE host, TS as shrinking
scaffold) and the 6-step order above.**


---

# V3 AMENDMENTS (2026-08-25) — closing the composed-module execution gaps

A second adversarial review of v2 returned FAIL with four gaps, all in the space
BETWEEN "the composed module links" and "the composed module runs the game" — v2's F1
declared the composed-module terminal architecture but left its execution mechanics,
dispatch mechanics, scaling mechanics, and input authorship unstated. Each gap below is
stated with evidence, the mechanism that closes it, and the gate that proves it closed.
Where a citation reads `file:line`, the line was read and verified for this amendment.

## G1 — Control inversion: the composed module has no execution model

**The gap.** v2 F1 ends with "boot.dol's code executing in one wasm module with a
high-level host" and says nothing about HOW that code runs. A GameCube main loop is
built on blocking host waits — `VIWaitForRetrace`, `GXDrawDone`, `OSThread`
suspend/resume — and vanilla WebAssembly cannot suspend mid-stack: a faithfully
translated `run_main_game_loop` (start-code-flow.md's spine; every per-frame entry in
its flow table routes through it, e.g. research/decomp/index/start-code-flow.md:90-92)
would spin forever inside one `requestAnimationFrame` callback and freeze the tab.
Without an execution model, F1's terminal architecture is a linker artifact, not a
running game.

**The mechanism.**
- The composed module runs in a **dedicated Web Worker**, sharing its
  `WebAssembly.Memory` with the main thread.
- Blocking SDK waits are emulated with **SharedArrayBuffer + Atomics.wait** in the
  worker: the shim for `VIWaitForRetrace`/`GXDrawDone` genuinely blocks the worker
  thread until the host (main thread) signals, which is exactly the semantics the ROM
  expects and is legal off the main thread.
- Rendering goes through **OffscreenCanvas** so the worker-side GX shim can submit
  frames without bouncing every draw through postMessage.
- **Asyncify is EXCLUDED.** It rewrites the module's code to make it suspendable,
  which breaks the pipeline's core claim that the verified bytes are the shipped
  bytes. **JSPI** (stack switching) is noted as a future alternative once it is
  broadly shipped — it suspends without rewriting — but the design does not depend
  on it.
- **OSThreads require an inventory, not an assumption.** The ROM's actual thread
  population must be measured from traces (the Stage-B GDB stub can log
  `OSCreateThread` calls like any other breakpoint). Deliverable: a per-thread ledger
  (creation site, entry point, what it blocks on) with a per-thread HLE strategy —
  the default being cooperative scheduling in the worker, yielding only at blocking
  SDK calls, which matches GameCube OSThreads' non-preemptive-in-practice usage.
  Any thread that defeats this (e.g. relies on preemption) is flagged for owner
  review, not silently approximated.

**The gate.** A new pipeline step (order-of-work item 6): the composed module DRIVES
N consecutive frames of play — its own loop calling out through the SDK seam — with
the TS engine fully passive. Until that gate passes, every "composed module" claim is
a linking claim, and the doc must say so.

## G2 — Function-pointer dispatch: GC code addresses stored in data have no wasm target

**The gap.** The ROM is dispatch-table-driven, and the pipeline has no story for it.
Evidence, all verified in this tree:
- research/decomp/index/start-code-flow.md:105 names it outright: "Function-pointer
  dispatch tables are a known gap; Challenge flow uses dispatch arrays such as
  `PTR_FUN_*` and will need table decoding." (The same file's "Indirect Dispatch
  Sites" table, lines 94-100, lists only 3 statically-resolved sites.)
- Per-borg constructor tables: `PTR_PTR_802d3224` (family byte = borg-id high byte,
  variant = low byte), research/decomp/behavior-notes.md:2884.
- Menu-mode table `PTR_FUN_802da780` (11 reviewed entries), dispatched as
  `(*(code *)(&PTR_FUN_802da780)[menu_mode])()` —
  research/decomp/index/title-main-menu-flow.md:20,26 and ghidra-export/chunk_0013.c:2625.
- Hitbox shape-kind evaluator table `PTR_FUN_802da740` (12 handlers),
  research/decomp/behavior-notes.md:2345.
- Per-actor state dispatch `(*(code*)(&PTR_FUN_802d3570)[*(char*)(actor+0x540)])(actor)`,
  research/decomp/behavior-notes.md:2633 (35-entry table, behavior-notes.md:1111).
- `mtctr`/`bctrl` indirect calls appear throughout the export.

Every stored function pointer is a GameCube 0x80xxxxxx CODE address sitting in the
shared linear memory. In a composed wasm module those bytes point at nothing: wasm
functions are not addressable memory. The moment the composed module executes a real
dispatch site, it loads a GC address and has no way to call it.

**The mechanism.** The assembly gate (which already links N units at original GC
addresses) additionally emits an **address-keyed function table**: every linked
function is registered in a `WebAssembly.Table` at an index derived from its GC
address (direct map or a dense side-table keyed by address). Indirect call sites in
the generated C are lowered to `call_indirect` through that table, grouped into
**signature classes** (wasm `call_indirect` is signature-checked, so the gate must
bucket the observed dispatch signatures — the same signature evidence the corpus
already records). Function pointers stored in data then work UNMODIFIED: the ROM
writes a GC address into a struct, the lowered call site reads it back and
`call_indirect`s through the table. No pointer rewriting in data, so byte-exactness
of memory state is preserved.

**The gate.** The composed-module pilot (order-of-work item 4) must include at least
one unit that calls through a REAL ROM dispatch table (any of the tables cited above)
via the address-keyed function table — not a direct-call-only window. A pilot of
straight-line callers proves nothing about the mechanism the ROM actually uses.

## G3 — Composition scaling has no gate between N=5 and N=1,396

**The gap.** Measured state, verified in this tree:
- `largest_n_passed` is **5** (research/decomp/data/assembly-gate.json:4).
- The knowledge registry carries **81 contested symbols** (`"contested": true` count
  in research/decomp/generated/finish-game-port/knowledge-registry.json) at only ~88
  units integrated.
- A recent run failed canonicalize outright: `canonicalization_refused` on
  `FUN_800c6178`, detail `owner_variant_abi_incompatible: Clang rejected FUN_800c6178
  owner/variant pair at auto-c0020-009/gnt4_shim.h` (live driver state in
  assembly-gate.json, lines 1677-1707 of the working copy at review time; the same
  failure class appears throughout knowledge-registry.json, e.g. lines 3125, 6030).

Contested declarations at N=5 windows already include `undefined8` forks, `CONCAT44`
macro divergence, and dozens of `collision_stub` prototype conflicts
(assembly-gate.json `conflicts` map, this tree). v2 step 6 says "only then scale the
loop" — growing 5 → 1,396 requires cross-window ABI unification, and NOTHING in v2
gates that growth. Scaling an ungated composition is how 88 compile-only greens
happened at Stage A; v2 was set to repeat the mistake at Stage C.

**The mechanism.** An explicit **N-doubling composition ladder**: 5 → 10 → 20 → 40 →
80 → … Each rung is a gate run with a **per-rung conflict budget** (new contested
symbols introduced by that rung). The stop rule is rate-based: if the contested-symbol
rate RISES rung-over-rung — conflicts per newly-added unit growing as N grows — the
ladder **STOPS**, and ABI unification is redesigned (canonical typedef/macro set,
registry-enforced single declarations) before any further scaling. A rising rate means
divergence is systemic and every doubling makes the eventual unification strictly more
expensive; a falling rate means canonicalization is winning and the ladder may
continue. This is an explicit step in the order of work, not an assumption folded
inside the word "scale".

**The gate.** Each rung passes only when its window links AND its new-conflict count
is within budget. The ladder's current rung joins the convergence ledger next to the
three-column metric.

## G4 — Coverage authorship: DTM captures are a human input the doc never named

**The gap.** v2 F4 introduced the coverage ledger and said capture sessions "are
authored per subsystem as DTM replays" — passive voice hiding a standing human
dependency. Someone has to PLAY the game into every subsystem: 200+ borgs, every
stage, shop, save, attract. No autonomous component of this pipeline produces those
inputs today.

**The correction (honesty, not mechanism).** The DTM capture library is an
**OWNER-SUPPLIED external input**, and the doc says so plainly:
- It is tracked as a first-class DEPENDENCY in the convergence ledger — a
  capture-coverage column whose growth is owner work, not pipeline work. When
  verification stalls, the ledger shows whether the pipeline is blocked on itself or
  waiting on captures.
- All autonomy claims in this document are scoped to everything DOWNSTREAM of
  captures: breakpoint capture, corpus building, replay verification, promotion,
  integration.
- An input-script generator (synthesizing controller inputs to reach code, guided by
  the coverage ledger) is noted as POSSIBLE future tooling. It is not designed here
  and nothing in the order of work assumes it exists.

## Non-fatal review notes, recorded for honesty

1. **WebGL rasterization ceiling.** The GX host backend renders through WebGL/WebGPU,
   not a cycle-accurate Flipper. Claims discipline for the graphics boundary (v2
   Stage D already set the observable-behavior bar): the standard is
   **"framebuffer-equivalent, never pixel-identical"** — and no document claim may
   quietly upgrade it.
2. **Mid-game MEM1 snapshot boot is scaffolding.** Booting the composed module from a
   captured MEM1 snapshot (the 2x24MB captures, v1 Stage B) skips the ROM's own init
   path. It is legitimate for pilots and must be RETIRED on the same schedule as the
   TS engine: the end state boots from reset through the ROM's real initialization.
3. **Serving-context raise (16384 → 60000).** The larger context shrinks the
   `awaiting_larger_context` queue (v1 Stage A amendment 2) — more over-budget units
   become compilable. It changes no architectural conclusion in this document; it
   moves units between queues.

## Revised order of work (supersedes v2's 6-step list)

1. Stage-A amendment (generator-side SDK declarations) — unchanged from v1/v2.
2. Trace pilot — unchanged gate: one staged unit to `oracle_green` end-to-end via
   Dolphin-GDB capture and the existing promotion path.
3. Assembly-gate dispatch lowering (G2): emit the address-keyed function table and
   lower indirect call sites to `call_indirect` with signature classes. Lands before
   the composed-module pilot so the pilot can gate on it.
4. Composed-module pilot (v2 F3 + G2 gate): wire one assembled N-unit module (shared
   memory, original addresses) into the app behind seams; prove two units sharing
   state stay coherent in play; the window MUST include at least one unit calling
   through a real ROM dispatch table via the address-keyed table.
5. OSThread and blocking-call inventory (G1 prerequisite): trace-measure the threads
   the ROM actually creates and the blocking SDK calls on its hot loop; write the
   per-thread HLE strategy ledger; owner reviews any thread that defeats cooperative
   scheduling.
6. Control-inversion pilot (G1): composed module in a dedicated Web Worker (shared
   `WebAssembly.Memory`, SharedArrayBuffer + Atomics.wait for blocking shims,
   OffscreenCanvas rendering; Asyncify excluded, JSPI future-noted). Gate: the
   composed module DRIVES N frames of play with the TS engine passive.
7. Coverage ledger + first DTM capture set (v2 F4, amended by G4): captures are
   owner-supplied; the ledger tracks capture coverage as an explicit external
   dependency.
8. SDK shim ledger + verification harness for math/OS shims (v2 F2) — GX/audio/DVD
   held to framebuffer/audio/file-read equivalence, stated as such.
9. Composition ladder (G3): N-doubling 5 → 10 → 20 → 40 → …, per-rung conflict
   budget, hard stop and ABI-unification redesign if the contested-symbol rate rises
   rung-over-rung.
10. Continuous loop at scale. Convergence metric:
    `compiled / exercised / verified / playing-composed of 1,396`
    (+ shim ledger, + capture-coverage dependency, + current ladder rung).

The review question for the owner is unchanged in kind, updated in content:
**approve the v3 execution model (Worker + Atomics control inversion, address-keyed
indirect dispatch, gated composition ladder, owner-supplied capture dependency) and
the 10-step order above.**


---

# V4 AMENDMENTS (2026-08-25) — deployment isolation, out-of-window boundary, dispatch ABI

A third adversarial review of v3 returned FAIL: three fatal gaps and two
enforceability notes. All three fatals sit in the space v3 opened — the Worker +
Atomics execution model and the address-keyed dispatch table — where v3 named the
mechanism but left a load-bearing precondition, boundary, or failure mode unstated.
Each is given below as gap, mechanism, and gate. The two enforceability notes are
folded in as NORMATIVE rules, not commentary. Where a citation reads `file:line`,
the line was read and verified for this amendment.

## H1 — Cross-origin isolation is an unstated precondition of the entire execution model

**The gap.** Everything in G1 rests on shared `WebAssembly.Memory`,
`SharedArrayBuffer`, and `Atomics.wait` — and browsers gate all three behind
`crossOriginIsolated === true`, which requires the server to send COOP/COEP response
headers (`Cross-Origin-Opener-Policy: same-origin`,
`Cross-Origin-Embedder-Policy: require-corp`). Production is GitHub Pages
(apps/game/vite.config.ts:5-7 — production base is the Pages subpath
`/GotYaForce/game/`), and GitHub Pages cannot set response headers. Nothing in
`apps/game` sets or references them: a search for
COOP/COEP/`crossOriginIsolated`/`SharedArrayBuffer` across `apps/game` matches no
source file (verified this session; the only hits are byte coincidences inside two
texture PNGs). As written, v3's control-inversion pilot would pass on a
suitably-configured dev machine and the shipped game would throw on
`new SharedArrayBuffer` — the execution model silently did not apply to production.

**The mechanism.** Cross-origin isolation becomes an explicit PRECONDITION of the
control-inversion step, with a serving plan for both environments:
- **Dev:** the Vite dev server sends COOP/COEP via `server.headers` in
  apps/game/vite.config.ts.
- **Production (GitHub Pages):** a coi-serviceworker-style shim — a service worker
  that intercepts and re-serves every response with the isolation headers added —
  installed at first load, after which the page reloads once into an isolated
  context. This is a known, widely-used pattern for header-less static hosts.
- **Fallback:** if the service-worker shim proves unreliable (first-load reload
  loops, SW update races), the fallback is a host change to any static host that
  can set response headers. The subpath base is already config-driven
  (vite.config.ts:7), so a host change is a config change, not a code change.

**Threads relink invalidates Stage-B verification — a required re-verification
pass, not a footnote.** Building the composed module against a shared, imported
memory (the threads/atomics target) changes the emitted module bytes relative to
what Stage B verified. The same "the verified bytes are the shipped bytes"
principle that excluded Asyncify (G1) applies with full force here: after the
threads-enabled relink, EVERY previously-verified unit's `oracle_green` status is
SUSPENDED until its corpus is replayed against the relinked artifact and comes back
byte-equal. This re-verification pass is a scheduled step in the order of work
(step 8 below), and no composed-module claim may cite pre-relink verification.

**The gate.** The smoke script asserts `window.crossOriginIsolated === true` in
BOTH dev and production before any shared-memory work counts as done. A
control-inversion pilot that passed only where headers happen to be set has not
passed.

## H2 — The out-of-window call boundary is undefined, making the control-inversion gate unpassable or vacuous

**The gap.** The G1 gate reads "the composed module DRIVES N frames of play with
the TS engine fully passive." The largest window ever linked is N=5 of 1,396
(research/decomp/data/assembly-gate.json:4, `largest_n_passed: 5`), and
`run_main_game_loop` (`0x800527d8`, research/decomp/index/start-code-flow.md:87)
fans out into essentially the entire per-frame call graph — the flow table routes
every per-frame entry through it. v3 never says what a linked function's call to an
UNLINKED callee binds to. With no answer, the gate is unpassable (the module traps
at the first out-of-window call) or vacuous (out-of-window calls silently no-op and
"drives N frames" means nothing). Either way, "TS engine fully passive" is
undefined while the TS scaffold still implements most of the game.

**The mechanism: a generated HOST BRIDGE.** Every out-of-window callee becomes a
declared wasm import, bound to a bridge that performs a synchronous Atomics-based
RPC from the worker to the main-thread TS scaffold:
1. The worker-side bridge stub writes the callee's GC address and marshalled
   arguments into a fixed ring buffer in shared memory, then `Atomics.wait`s.
2. The main thread services the call — dispatching into the TS scaffold's
   implementation of that function — writes the result into the ring buffer, and
   `Atomics.notify`s.
3. The worker resumes with the result, exactly as if the callee had been linked.

A **per-frame bridged-call ledger** records every symbol that crosses the boundary
(symbol, GC address, call count). This redefines the terms of G1 precisely:
- The TS scaffold remains the implementation of not-yet-ported functions WITHOUT
  being in control.
- **Passivity is redefined as: "TS executes only when called through the bridge."**
  Control inversion is real — the composed module owns the loop; TS is a set of
  callees.
- The ledger is the shrink metric F1 promised: as the composition ladder grows,
  symbols move from bridged to linked and the per-frame bridged-call count falls.

**The gates.**
- (a) **Prerequisite:** `run_main_game_loop` itself reaches `oracle_green` and is
  linked INTO the composed window before the control-inversion step runs. A
  composed module driven by anything other than the ROM's own loop has not
  inverted control.
- (b) The control-inversion gate is restated: **the composed module drives N frames
  with every out-of-window call routed through the declared bridge, with the
  bridged-call count reported per frame and monotonically shrinking as the ladder
  grows.** Frames driven with any undeclared or unrouted out-of-window call do not
  count.

## H3 — Dispatch ABI: signature mismatch must be RESOLVED, not merely checked

**The gap.** G2's signature classes make `call_indirect` signature-CHECKED — and
wasm's answer to a failed check is a TRAP. PPC indirect calls are
signature-agnostic: the caller jumps through `ctr` with whatever is in the argument
registers, and the ROM exploits that freely. The menu table dispatches with zero
arguments (`(*(code *)(&PTR_FUN_802da780)[menu_mode])();`,
research/decomp/ghidra-export/chunk_0013.c:2625) while the actor table passes the
actor pointer (research/decomp/behavior-notes.md:2633) — and callee-signature
divergence is endemic in the gate's own data: 81 contested symbols, `undefined8`
forks, `collision_stub` prototype conflicts (G3's evidence). Under G2 as written,
the first dispatch whose caller-side class disagrees with the callee's true
signature traps the module. Signature classes turn UB into a crash; they do not
make dispatch work.

**The mechanism: a UNIFORM DISPATCH ABI.** The assembly gate emits, for every
address-keyed table:
- **Adapter thunks as table entries.** Every entry in the `WebAssembly.Table` is a
  generated thunk with ONE canonical signature — e.g. `(i32 argptr) -> i32`, with
  arguments marshalled through a fixed frame in shared memory. Each thunk is
  generated AT LINK TIME from the callee's true signature: it unmarshals the frame
  into the callee's real parameters, calls the callee directly, and marshals the
  return back.
- **Caller-site lowering to the uniform signature.** Indirect call sites lower to:
  write arguments into the fixed frame, `call_indirect` with the canonical
  signature. Cross-class calls (zero-arg menu dispatch, one-arg actor dispatch,
  anything the ROM does) CANNOT trap on signature — every table entry has the same
  wasm type; fidelity to the callee lives in the thunk.
- **Table misses are defined behavior.** A stored function pointer whose target is
  not yet linked hits a **miss-handler import**: it logs the GC address to the
  bridged-call ledger and routes the call to the host bridge (H2's mechanism) —
  the TS scaffold services it like any out-of-window call. A miss is a bridge
  call, never a trap and never undefined behavior. This also closes the loop with
  H2: the dispatch table and the bridge share one ledger and one boundary
  semantics.

**The gate.** The dispatch pilot (order-of-work step 3/4) must include, in
addition to G2's real-ROM-table requirement:
- one **deliberately cross-class dispatch** (e.g. a zero-arg-style call into a
  callee with parameters), passing with correct results, and
- one **table-miss case** (a stored pointer to a not-yet-linked function),
  serviced through the miss handler with a correct result and a ledger entry.
Both must pass with correct results AND correct ledger entries. A pilot of
same-class, all-linked dispatches proves nothing about the two failure modes the
ROM will actually produce.

## Enforceability amendments (normative)

**E1 — The composition ladder's conflict budget gets a formula (amends G3).** "A
per-rung conflict budget" is unenforceable without a number. The budget is:

    a rung passes if  (new contested symbols introduced at that rung)
                    / (new symbols linked at that rung)
                    ≤ the same ratio at the previous rung.

That is, the contested-symbol RATE must be non-increasing rung-over-rung — the
quantitative form of G3's stop rule. The ratio is recorded per rung in the ledger.
The formula is PROVISIONAL and revisable with evidence, but any revision must be
written into this document with the measurements that justified it; the ladder
never runs against an unstated budget.

**E2 — Canvas ownership during the hybrid period (amends G1's OffscreenCanvas
plan).** `transferControlToOffscreen()` permanently detaches a canvas from
main-thread rendering — so the existing three.js renderer (scaffold) and the
worker-side GX shim CANNOT share one canvas, and no hand-off scheme can un-transfer
it. The stated mechanism for the hybrid period is a **dual-canvas compositor**: the
scaffold's three.js canvas below, the worker's OffscreenCanvas layered above,
opacity-switched per scene ownership (whichever side owns the current scene's
rendering is visible; the other is transparent and idle). The dual-canvas period
ends when the GX path owns rendering outright, on the same retirement schedule as
the TS scaffold itself.

## Revised order of work (supersedes v3's 10-step list)

1. Stage-A amendment (generator-side SDK declarations) — unchanged from v1/v2/v3.
2. Trace pilot — unchanged gate: one staged unit to `oracle_green` end-to-end via
   Dolphin-GDB capture and the existing promotion path.
3. Assembly-gate dispatch lowering (G2 as amended by H3): emit the address-keyed
   table as UNIFORM-ABI adapter thunks (one canonical signature, link-time
   generation from true callee signatures), lower indirect call sites to the
   canonical signature, and emit the miss-handler import routing to the host
   bridge. Lands before the composed-module pilot so the pilot can gate on it.
4. Composed-module pilot (v2 F3 + G2 + H3 gates): wire one assembled N-unit module
   (shared memory, original addresses) into the app behind seams; prove two units
   sharing state stay coherent in play. The window MUST exercise: at least one
   real ROM dispatch table, one deliberately cross-class dispatch, and one
   table-miss case — all with correct results and ledger entries.
5. OSThread and blocking-call inventory (G1 prerequisite) — unchanged: per-thread
   ledger and HLE strategy; owner reviews any thread that defeats cooperative
   scheduling.
6. Cross-origin isolation serving plan (H1): Vite `server.headers` for dev; the
   coi-serviceworker shim for GitHub Pages; host-change fallback documented. Gate:
   the smoke script asserts `window.crossOriginIsolated === true` in both dev and
   production. PRECONDITION for steps 7-9; no shared-memory work counts as done
   without it.
7. Host bridge (H2): generate the out-of-window import set and the Atomics RPC
   bridge with its per-frame bridged-call ledger. Prerequisite folded in:
   `run_main_game_loop` reaches `oracle_green` and is linked into the composed
   window.
8. Stage-B re-verification pass (H1): after the threads-enabled relink (shared
   imported memory), replay every verified unit's corpus against the relinked
   artifact; all `oracle_green` statuses are suspended until re-green. No
   composed-module claim may cite pre-relink verification.
9. Control-inversion pilot (G1 as amended by H2 + E2): composed module in a
   dedicated Web Worker — shared `WebAssembly.Memory`, SharedArrayBuffer +
   Atomics.wait blocking shims, dual-canvas compositor for the hybrid rendering
   period; Asyncify excluded, JSPI future-noted. Gate: the composed module drives
   N frames with every out-of-window call routed through the declared bridge,
   bridged-call count reported per frame and monotonically shrinking as the
   ladder grows.
10. Coverage ledger + first DTM capture set (v2 F4, amended by G4): captures are
    owner-supplied; the ledger tracks capture coverage as an explicit external
    dependency.
11. SDK shim ledger + verification harness for math/OS shims (v2 F2) —
    GX/audio/DVD held to framebuffer/audio/file-read equivalence, stated as such.
12. Composition ladder (G3 as amended by E1): N-doubling 5 → 10 → 20 → 40 → …,
    rung passes only if its window links AND its new-contested/new-linked ratio is
    ≤ the previous rung's ratio (recorded per rung); hard stop and
    ABI-unification redesign if the rate rises.
13. Continuous loop at scale. Convergence metric:
    `compiled / exercised / verified / playing-composed of 1,396`
    (+ shim ledger, + capture-coverage dependency, + current ladder rung,
    + per-frame bridged-call count, + isolation status in the smoke report).

The review question for the owner, updated in content:
**approve the v4 deployment and boundary model (COOP/COEP isolation plan with
production shim and re-verification after the threads relink, host-bridge
out-of-window boundary with ledger-defined passivity, uniform dispatch ABI with
defined table misses, formulaic ladder budget, dual-canvas hybrid rendering) and
the 13-step order above.**


---

# V5 AMENDMENTS (2026-08-25) — bridged-callee contract, reentrant bridge, spine verification

A fourth adversarial review of v4 returned FAIL: three fatal gaps and three
non-fatal notes. All three fatals sit inside the mechanisms v4 itself introduced —
the host bridge (H2) and its prerequisite chain — where v4 named the RPC transport
but left the callee's semantic contract, the bridge's reentrancy behavior, and the
verification standard for nonterminating functions unstated. Each is given below as
gap, mechanism, and gate. The three notes are folded in as NORMATIVE one-liners.
Where a citation reads `file:line`, the line was read and verified for this
amendment.

## I1 — Bridged-callee contract: routing a call is not servicing it

**The gap.** H2's bridge assumed the TS scaffold can service a bridged call "as if
the callee had been linked." That is false twice over:

- (a) **No per-symbol callees exist.** The scaffold is a HOLISTIC recreation, not a
  function-for-function one: `apps/game/src/sim/battleScene.ts` is a scene-driven
  monolith (one `BattleScene` class, apps/game/src/sim/battleScene.ts:607, ~98KB of
  scene logic). There is no TS function corresponding to an arbitrary GC symbol,
  and nothing in the scaffold takes GC-pointer arguments read out of the shared
  arena.
- (b) **"As if linked" is a MEMORY claim, not a return-value claim.** A linked
  callee performs byte-level writes into the shared GC RAM image — struct fields,
  pools, globals at original addresses — that downstream LINKED code then reads.
  TS object-state cannot emit those writes: a bridged call serviced by scaffold
  logic would return a plausible value while leaving the arena stale, and every
  linked function reading that state afterward would consume garbage. The
  routing-only gate (H2 gate (b), "every out-of-window call routed through the
  declared bridge") would PASS while the game state silently diverged.

**The mechanism: a BRIDGED-CALLEE CLASS.** Out-of-window symbols are serviced by
**per-symbol host adapters**, each owning the full memory contract:

- An adapter **reads its arguments from GC memory** (dereferencing GC-pointer args
  in the shared arena) and **writes its results AND side-effects back to GC memory
  at the original addresses** — the same observable behavior a linked callee would
  have.
- Adapters are written **ONLY for symbols the bridged-call ledger proves are
  actually hit** — demand-driven from measured frames, never thousands up-front.
  The ledger (H2) is the adapter work-queue.
- Each adapter is **derived from the same Dolphin trace evidence as ports**: the
  callee's per-call memory-write set is captured at its Stage-B breakpoints, and
  the adapter must REPRODUCE that write set. An adapter without trace evidence for
  its symbol is not a valid adapter.
- The TS scaffold MAY back an adapter's logic (compute with scaffold code where it
  matches), but **the adapter owns marshalling** — state moves into and out of GC
  memory at the adapter boundary, never implicitly through TS object state.

**The gate.** The control-inversion gate (H2 gate (b)) gains **STATE EVIDENCE**:
at each frame boundary, the shared arena is compared against a Dolphin trace of
the SAME DTM replay at the same frame boundary. A frame passes only if the arena
matches the trace **modulo a declared exclusion list** (e.g. uninitialized
scratch regions), with every exclusion justified in the ledger. Routing counts
alone no longer pass a frame; a frame whose arena diverges outside the exclusion
list fails, regardless of how faithfully calls were routed.

## I2 — Bridge reentrancy: a bridged callee that calls back into the module deadlocks it

**The gap.** A bridged TS/host callee whose implementation reaches a ported
function's seam (the Stage-C pattern — scaffold code calling into verified wasm)
targets the worker's instance — but the worker's thread is PARKED in
`Atomics.wait` inside that very call chain (H2 step 1). The main thread would be
waiting on the worker's export while the worker waits on the main thread's
result: deadlock, by construction, the first time a bridged callee touches a
ported seam. Separately, scaffold paths are ASYNC (loaders, promise chains) while
the H2 RPC contract is synchronous — an async servicing path would leave the
worker parked forever with no error.

**The mechanism: worker-side REENTRANT DISPATCH LOOP (normative).** The bridge
adopts the Emscripten-proxying-style discipline:

- The parked worker-side bridge stub distinguishes two wake kinds in the ring
  buffer: **"result"** (the bridged call completed) and **"invoke linked
  export"** (the main-thread servicer needs a linked function run).
- On an invoke-request wake, the worker **calls the requested export on its own
  stack**, writes the result back into the ring buffer, notifies, and
  **re-waits** for its original result. The main-thread servicer never calls
  worker exports directly; it enqueues invoke requests to the parked worker.
- Nesting (a re-entered export that itself bridges out) is allowed to a **stated
  maximum depth**; exceeding it is a **declared servicing error** recorded in the
  ledger, never a silent hang.
- **Bridged callees MUST be synchronous.** Any async path reached during
  servicing (an await, a pending promise, a lazy load) is a declared servicing
  error surfaced in the ledger — the frame fails loudly. Adapters requiring async
  resources must acquire them ahead of servicing (preload), never during it.

**The gate.** The bridge pilot (order-of-work step 7) includes at least **one
reentrant case** — a bridged call whose adapter invokes a linked export via the
dispatch loop — passing with correct results and correct ledger entries. A
bridge pilot of leaf-only adapters has not exercised the deadlock it exists to
prevent.

## I3 — Spine verification: `oracle_green` is unreachable for nonterminating functions

**The gap.** H2 gate (a) requires `run_main_game_loop` to reach `oracle_green`
before the control-inversion step. But `run_main_game_loop` (`0x800527d8`,
named at research/decomp/index/start-code-flow.md:33; decompiled body at
research/decomp/ghidra-export/chunk_0006.c:5790-5833) is `do { ... } while( true )`
(chunk_0006.c:5808 and :5832) — it NEVER RETURNS, and its loop body is almost
entirely out-of-unit calls. Stage B's per-call replay standard — capture
(args, referenced memory, return, memory writes), replay, byte-compare — cannot
even terminate on it: there is no return to compare and the harness would spin.
The v4 step-7 prerequisite permanently blocks its own step. The same applies to
any spine/dispatcher function whose body is a nonterminating loop over callees.

**The mechanism: a distinct verification standard, `boundary_green`.**

- **Capture:** from Dolphin, record K loop iterations' **callee-boundary
  sequence** — for each call the spine makes: callee GC address, arguments, and
  memory deltas attributable to the interval.
- **Replay:** the harness stubs every callee with its captured boundary behavior
  (returning the recorded results, applying the recorded memory deltas),
  **terminates after K iterations** via an iteration-counting stub, and asserts
  the wasm emits the **identical call sequence and writes** — same callees, same
  order, same arguments, same spine-owned memory writes.
- `boundary_green` — NOT `oracle_green` — is the verification prerequisite for
  nonterminating/spine functions. The two standards are recorded distinctly in
  the ledger; a `boundary_green` unit never silently upgrades to an
  `oracle_green` claim.

**The ordering defect, fixed.** v4 placed the first owner-supplied DTM at step 10
while steps 2, 7, and 9 all consume trace captures — every trace-dependent step
sat upstream of its own input. Corrected: **at least one owner-supplied DTM is a
prerequisite of the FIRST trace-dependent step (step 2, the trace pilot)**, and
the full capture library remains the step-10 deliverable.

**The gate.** `run_main_game_loop` reaches `boundary_green` over K owner-approved
iterations before the control-inversion step runs; the K, the callee-boundary
corpus, and the stub exclusions are recorded in its result artifact.

## Non-fatal review notes (normative)

1. **H3's uniform ABI trades traps for potential silent mis-marshalling.** With
   every table entry sharing one canonical signature, a wrong "true signature"
   (81 contested symbols in the registry) no longer traps at `call_indirect` —
   it mis-marshals silently; the design states this trade explicitly and relies
   on the trace/oracle discipline (Stage B replay + I1 state evidence) to catch
   the divergence. PPC **register-residue reads** — a callee consuming argument
   registers the call site never set — are a known unreproducible class, flagged
   to the ledger when detected, never silently papered over.
2. **The smoke harness must tolerate the coi-serviceworker first-load reload**
   (install, then one reload into the isolated context — H1's production
   mechanism), or the production `crossOriginIsolated` assertion will flake on
   every first visit.
3. **Step-8 re-verification requires harness work that does not exist yet:** the
   Node harness instantiates units with only an `env` shim import and reads the
   module's own EXPORTED memory (research/decomp/oracle-harness/lib/wasm.mjs:27-33,
   used by research/decomp/oracle-harness/run-unit.mjs); threads-target wasm
   instead IMPORTS a shared `WebAssembly.Memory`, which Node supports but the
   harness does not implement. Extending the harness to instantiate
   threads-target wasm with imported shared memory is an explicit step-8 subtask.

## Revised order of work (supersedes v4's 13-step list)

1. Stage-A amendment (generator-side SDK declarations) — unchanged from v1-v4.
2. Trace pilot — unchanged gate (one staged unit to `oracle_green` end-to-end via
   Dolphin-GDB capture and the existing promotion path), amended prerequisite
   (I3): **at least one owner-supplied DTM exists before this step runs** — the
   first trace-dependent step carries the DTM dependency, not step 10.
3. Assembly-gate dispatch lowering (G2 as amended by H3): uniform-ABI adapter
   thunks, canonical-signature call-site lowering, miss-handler import routing to
   the host bridge. Lands before the composed-module pilot.
4. Composed-module pilot (v2 F3 + G2 + H3 gates): one assembled N-unit module
   (shared memory, original addresses) wired behind seams; two units sharing
   state stay coherent in play; window exercises a real ROM dispatch table, one
   cross-class dispatch, and one table-miss case — correct results and ledger
   entries for all three.
5. OSThread and blocking-call inventory (G1 prerequisite) — unchanged: per-thread
   ledger and HLE strategy; owner reviews any thread that defeats cooperative
   scheduling.
6. Cross-origin isolation serving plan (H1, amended by note 2): Vite
   `server.headers` for dev; coi-serviceworker shim for GitHub Pages with the
   smoke harness tolerating the first-load reload; host-change fallback
   documented. Gate: `window.crossOriginIsolated === true` asserted in both dev
   and production. Precondition for steps 7-9.
7. Host bridge (H2 as amended by I1 + I2 + I3): generate the out-of-window
   import set, the Atomics RPC transport, the per-frame bridged-call ledger, and
   the **bridged-callee adapter class** (per-symbol, demand-driven from the
   ledger, trace-derived write sets, adapter-owned marshalling into/out of GC
   memory); the worker-side **reentrant dispatch loop** is normative (stated
   nesting depth, synchronous-only servicing, declared servicing errors).
   Prerequisite: `run_main_game_loop` reaches **`boundary_green`** (I3) and is
   linked into the composed window. Gate additionally includes I2's reentrant
   pilot case.
8. Stage-B re-verification pass (H1, amended by note 3): after the
   threads-enabled relink, replay every verified unit's corpus against the
   relinked artifact; all `oracle_green`/`boundary_green` statuses suspended
   until re-green. **Explicit subtask: extend run-unit.mjs (via lib/wasm.mjs) to
   instantiate threads-target wasm with an imported shared memory.**
9. Control-inversion pilot (G1 as amended by H2 + E2 + I1): composed module in a
   dedicated Web Worker — shared `WebAssembly.Memory`, SharedArrayBuffer +
   Atomics.wait blocking shims, dual-canvas compositor; Asyncify excluded, JSPI
   future-noted. Gate: the composed module drives N frames with every
   out-of-window call routed through the declared bridge AND **frame-boundary
   state evidence** — the shared arena matches a Dolphin trace of the same DTM
   at each frame boundary, modulo the declared, ledger-justified exclusion list.
   Bridged-call count reported per frame and monotonically shrinking as the
   ladder grows.
10. Coverage ledger + full DTM capture library (v2 F4, amended by G4 and I3):
    captures are owner-supplied; the ledger tracks capture coverage as an
    explicit external dependency; the FIRST DTM moved to step 2, the library
    grows here.
11. SDK shim ledger + verification harness for math/OS shims (v2 F2) —
    GX/audio/DVD held to framebuffer/audio/file-read equivalence, stated as
    such.
12. Composition ladder (G3 as amended by E1): N-doubling 5 → 10 → 20 → 40 → …,
    rung passes only if its window links AND its new-contested/new-linked ratio
    is ≤ the previous rung's ratio (recorded per rung); hard stop and
    ABI-unification redesign if the rate rises.
13. Continuous loop at scale. Convergence metric:
    `compiled / exercised / verified / playing-composed of 1,396`
    (+ shim ledger, + capture-coverage dependency, + current ladder rung,
    + per-frame bridged-call count, + adapter ledger with per-symbol trace
    evidence, + frame-boundary state-evidence status, + isolation status in the
    smoke report).

The review question for the owner, updated in content:
**approve the v5 boundary semantics (bridged-callee adapters with trace-derived
memory contracts and frame-boundary state evidence, worker-side reentrant
dispatch loop with synchronous-only servicing, `boundary_green` as the
verification standard for nonterminating spine functions, DTM dependency moved
to the first trace-dependent step) and the 13-step order above.**
