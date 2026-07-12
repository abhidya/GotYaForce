# OGhidra first-pass findings applied to the 1:1 port (2026-07-12)

Source session: `research/tools/OGhidra/analysis_sessions/session_1783829686_785a372e/session.json`.
All numeric constants below were checked against `user-data/GG4E/disc/sys/boot.dol` and the
referenced Ghidra-exported function bodies before being applied. This is the first implementation
pass: the phase routing and surfaced state are ROM-derived, while the remaining host-bound gates
are listed explicitly at the end.

## Newly confirmed behavior

### Shared Robot action 0 (`zz_00f1e30_`, 0x800f1e30)

- The handler is a five-phase shared engine using table `0x8031b8a0`; it is not one uniform
  hard-coded Robot dash.
- The dash window is **30.0 frames** (`FLOAT_80439078`), correcting the earlier 20-frame port.
- Its 20-byte per-Borg config is `{s16 slotBase, s16 ammoSlot, callback@+4,
  callback@+8, s16 timerSeed, s16 count/mask, callback@+16}`.
- The configs differ materially: pl0405/pl0407/pl0408/pl040c use timer/count `4/5`; pl0407/0408
  start at stream slot 3; pl040b consumes ammo slot 2; pl040d starts at slot 6.
- pl0406 has no action-0 command leaf and must not receive the shared wrapper.
- Phase 4's exit is gated by `actor+0x5d8 & 0xf0`, not by the analysis session's inferred
  "Gotcha meter decay" description of `0x800f22a8`.

### Shared Robot melee (`FUN_800f2498`)

- Lunge speed is not always `50 / timer`. With a target it is `target distance (+0x760) / 30`;
  without one it is the selected `+0x868[previousAction % 3] / 30` row.
- Horizontal deceleration is explicitly cleared at the transition.
- Distances above the ROM threshold trigger `zz_00b2190_(actor, 0)`.

### EAGLE JET action 1 (`FUN_8012b458`)

- This is a single code-driven handler, not a stream phase table.
- It holds for **45.0 frames**, writes effect mode `0x83`, retires hit kind `0x7f`, prepares part
  slots 4 and 5, and plays cue `0x20`.
- Expiry runs the `zz_006a53c_(actor, 0x10)` cleanup: cooldown `16 + dt`, clear action bits, and
  dispatch full-body cue `0x1b`.

### NORMAL TANK / LEOPARD action 0 and action 2 (constructor 0x8007ca5c)

- Action 0's two variant tables are byte-equivalent five-phase machines: **15-frame windup,
  10-frame windup, barrel-ready wait, burst, 30-frame recovery**.
- The burst fires every **5 frames**. Normal completion is three shots; `+0x5b4 & 0x200` extends
  it to five. The nearer of the two vectors at `+0xa30/+0xa90` selects projectile record 3 or 2.
- Action 2 is **not** the shared X-special. Variant 0 uses the eight-entry table `0x802d6aac`;
  variant 1 enters the four-entry airborne subtable `0x802d6abc` directly.
- Exact action-2 constants are aim timer 30.0, stream rate -1.0, airborne horizontal seed 10.0,
  horizontal deceleration -0.3, pitch clamp `[-0x3800, 0x1800]`, turn step `0x180`, snap `0xc0`.

### ARROW NINJA / SHIJIMA action 1 (constructor 0x800cfe9c)

- Variant table `0x8030de28` routes v0 to shared lunge `zz_00fed6c_`, v1/v2 to phase table
  `0x8030de54`, and v3/v4 to phase table `0x8030de64`.
- The v0 config at `0x8030de3c` is `{slot 0, range 150, timer 20, decay .95/.95/.8}`.
- v1/v2 are a rising ground chain: 60-frame aim, 0.95 reposition tail, 20-frame approach,
  range 150, then horizontal/vertical launch seeds 40/30 and a 0.9 recovery brake.
- v3/v4 are a homing air dive: group-3 slot 2, 30-frame/30-speed seed, range cutoff 250, and
  a deliberate phase increment by two that normally skips table entry 2.

### EAGLE ROBOT / PROTO EAGLE action 0 (constructor 0x80129608)

- Variant table `0x80331948` routes v0 to `0x8033195c`, v1-v3 to `0x80331968`, and v4 to
  airborne table `0x80331974`.
- Shared constants are aim 30, upper aim 20, stream rate -1, reposition 0.95, gravity 1.
- The fire helper seeds `+0x6ee=1`, decrements ammo count, and uses different repeat timing:
  EAGLE ROBOT **16 frames**, PROTO EAGLE **2 frames**.
- EAGLE ROBOT fires child records `0x1e/0x1f` through `zz_00c3be0_`; PROTO EAGLE fires
  projectile records `0x6e/0x6f` through `zz_0082824_`.
- pl0606 now composes this action 0 with its already-ported shared morph action 2; pl061a is
  registered for action 0 without falsely routing its bespoke action 2 through the morph engine.

## Port locations and verification

- `packages/combat/src/families/shared-robot-dash.ts`
- `packages/combat/src/families/melee-robot.ts`
- `packages/combat/src/families/eagle-jet.ts`
- `packages/combat/src/families/tank-borg.ts`
- `packages/combat/src/families/arrow-ninja.ts`
- `packages/combat/src/families/eagle-robot.ts`
- Registration and focused assertions: `packages/combat/src/bridge.ts` and
  `packages/combat/src/rom/rom.selfcheck.ts`.

Verification at capture time: combat TypeScript build passes and `pnpm selfcheck:rom` passes.

## Remaining fidelity gates (do not treat as unknown mechanics)

The ROM behavior above is known, but several inputs still cross the `BorgRuntime`/`RomActor`
boundary and need live host wiring for frame-perfect behavior: ammo-allocation return values;
aim-complete and barrel-ready helper results; the exact signed stream events at `+0x1cef/+0x1d0f`;
collision/landing helper returns; descriptor bone-derived homing pitch; and Robot config callbacks
whose addresses are known but whose host effects are only routed today. The first-pass handlers
surface these as named scratch fields/callbacks and use conservative liveness fallbacks when the
host has not supplied them. Future vectorized passes should focus on those helper semantics rather
than rediscovering the phase tables or constants above.
