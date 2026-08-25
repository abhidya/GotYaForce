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
