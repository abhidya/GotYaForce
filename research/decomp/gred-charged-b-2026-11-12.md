# RED and NEO charged B: bounded browser restoration

## Scope and baseline

This lane targets `pl0615` and `pl0629` only. G BLACK dispatches to the different
`80179d20` engine and is intentionally excluded. Before this change, real held-B
release selected exact command type3/subtype5, action3/variant0 (`80365e38`), but
`tryStartBAttack` was called only on a press edge. The actor stayed in action0 and
the generic charged-shot branch emitted two ordinary scaled projectiles instead
of the source charge handler and sustained beam.

This is a local implementation checkpoint, not a deployment or whole-game parity
claim. No original binary, model, sound or animation assets are added.

## Original evidence

Read-only original GG4E data and the existing decompilation establish:

- Family dispatcher `8018ed4c` chooses `8018ed80` for RED/NEO, which calls shared
  engine `80179814`. BLACK instead chooses `8018ee08` / `80179d20`.
- Configuration `80365854`: ground/air slots2/2, carry f32(.95), fire timer30,
  edge-extension budget30, setup `8018eda8`, release `8018edc4`.
- Setup sets lock yaw to heading, vertical velocity8 and gravity0. Release calls
  `800e19a8` with row15 and a pointer to actor6f7. This is not generic fireChild15.
- `8006a104` checks/debits resource cells for command types0/2, not type3. Neither
  the charge engine nor the beam allocator adds a debit. A charged release must
  not invent another ordinary-shot ammo consumption.
- Source code: `research/decomp/ghidra-export/chunk_0044.c` (179814 and phases),
  `chunk_0047.c` (family dispatch/release), `chunk_0024.c` (e19a8 emitter), and
  `chunk_0009.c` (6de44 input-edge count).

### Actor order

Phase0 seeds float560 and signed54e from config, selects slot, clears6f7, aims at
captured524, zeros motion/pose, calls setup, carries `(pos - own5e8) * .95`, probes
terrain and starts group4 slot2. The source5e8 is the actor's own saved position,
not the locked target position.

Phase1 ticks the stream, aims, decays/adds carry and probes. Positive P0 advances
phase, clears542, sets6f7=2 and invokes the release callback once.

Phase2 sets6f7=2 and extends timer by the popcount of fresh input edges5bc masked
`0x0f0f00`, bounded by the remaining signed54e budget. Holding a button is not a
fresh edge. It aims, carries, restores descriptor gravity on negative dash,
integrates primary physics and probes. If timer is already nonpositive, it ticks
and exits on negative P0. Otherwise it subtracts dt and ticks only while P0 is
nonnegative. A frozen negative-P0 interval is therefore intentional, not a stall.

Phase3 damps signed pitch by f32(.9), integrates and probes before ticking. A
nonzero probe plus negative P0 clears ownership, dispatches cue7, sets cooldown
8+dt, resets pitch and returns. Otherwise it ticks; a completed stream returns
to ground idle or airborne state according to the probe. No fallback hold timer
or unconditional phase2 stream advance is part of this source behavior.

### Authored animation clock

Main group4 slot2 issues opcode0a kind0/status14/255 and plays metadata4/1,
mode1, blend5. Kind0 registers no HIT: source4c6b4 requires signed kind>0;
only status14/255 is forwarded.
Original RED/NEO clips resolve to MOT4/1 and end25. At frame9, mode8 pauses for12;
frame11 executes op07 `[0,2,2]`; frame12 writes positive P0 and frame19 negative
P0. Animation end switches to metadata4/4, mode2, blend4 (MOT4/4, end25). Its end
switches to metadata0/14, mode1, blend20 (MOT0/24, end1), then waits elapsed20.
All three original AOBJ flags are zero in both RED/NEO archives.

### Sustained emitter

Row15 at `80317428` uses HIT27, joint1, local offset `(0,40,10)`, max scale1 and
an aim cone dot threshold `.9238790273666382`. Shared source growth takes15
updates and retirement uses divisor10. Pulse countdown starts0 and resets1 after
subtracting live owner dt. The emitter reads the referenced owner6f7 byte and
stops active emission when it becomes less than1. Death/form invalidation is a
separate retirement path. A generic fixed-life flying projectile does not match
these ownership semantics.

HIT27 maps record34 for both families: shape0, flags1, radius20, damage31
(HP1), refresh0. Source139a6c creates a pulse with live beam endpoint pointers;
139bbc registers its HIT and copies the start, 139c50 copies the live end on the
second pass, 139c78 disables HIT, and 139ca0 frees. Each pulse has an independent
identity across its two registered passes.

Original static joint1 was read in place from RED AFS1799 and NEO AFS1885. Both
have identity root rotation/scale/translation, identity joint1 rotation/scale,
and joint1 translation `(0,129.60008239746094,0)`. Including row15 offset gives
static local muzzle `(0,169.60008239746094,10)`. This is a bind-pose adapter, not
the original animated joint cache. No model data was copied.

Source5685c updates saved aim524 only for an eligible captured target. The aim
helpers retain the saved point when that target is lost; they must not adopt a
new selected opponent. Helper6e39c uses joint1 with signed AE3072*dt, clamped to
±0x4000. Host target visibility and begin-frame sampling remain adapter limits.

## Verification and fidelity limits

- `families/gred-charge-engine.selftest.ts`: 17 control-flow/numeric groups,
  including callback order, separate signed extension budget, fresh-edge mask,
  conditional interpreter calls, correct 8+dt landing and exit paths.
- `gredChargeStream.selftest.ts`: independent full interpreter-call traces at
  dt1 and dt.5; gates at calls15/28/29/36 and30/57/59/73 respectively; recoil
  calls42/85, recovery69/137, terminal90/178. These are interpreter calls, not
  whole-actor duration: phase2 can suppress calls intentionally.
- `gredChargeBattle.selftest.ts`: real held/released B for both actors, source
  action3 and authored-frame12 callback, no generic twin shots, no second ammo
  debit (including an emptied bank after charging), held/retapped input extension
  up to budget30, independent pulse passes and actual victim HP change, death
  tail, unbanked and BLACK/melee/X/Beam Gunner isolation.
- Renderer selfcheck: synthetic clips verify `charge_shot` exact MOT4/1,4/4 and
  0/24 playback for both families, source-held poses and transition resets. This
  checks mixer behavior without original assets, not screenshot equivalence.

Original source evidence does not by itself prove browser equivalence. Admission
still uses the host positive `chargeFrames` bank and its existing cooldown/input
thresholds; original charge accumulation and threshold parity are not claimed.
Normalized-stick quantization, captured-target visibility/begin-frame sampling,
static joint1 actor pitch anchor, yaw-only static bind-pose beam basis with cone
correction, instantaneous host capsule
geometry and generic beam art remain adapters. The actor part pitch is tracked
but does not drive an animated joint or muzzle transform. First-ever no-target entry uses a
forward point if there is no prior saved524; later entries retain a saved point.
The source status14/255 and equipment writes are tracked but their downstream
visual/status consumers are not newly implemented. Neutral dt1 is the live bridge
clock; dt.5 clock tests are not whole-engine variable-rate proof. A 300-update
host safety ceiling and existing 20-frame post-action cooldown are not original
charge timings. No original-console replay,
visual parity check or live deployment was performed for this local lane.

Final local `verify:contributor` passed after source review, including TypeScript,
renderer checks, ROM and full combat lifecycle suites, importer checks and the
production build (17.79 seconds). The existing large-bundle warning remains.
