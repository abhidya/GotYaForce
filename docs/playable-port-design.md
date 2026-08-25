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
