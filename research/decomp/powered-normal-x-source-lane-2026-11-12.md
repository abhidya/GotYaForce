# Powered Gunman normal-X source lane

Scope: pl0101 normal type 2/action 2, four `FUN_8016d584` port calls, **sixteen
children** total. Charged action 3 keeps its existing four primary/split route.
No asset files were copied, uploaded, or replaced.

## Evidence and live integration

- `pad-bit-binding-decode-2026-07-05.md` section 3: X descriptor `0x802d3910`
  has mode 1, flags 0, edge/polled seeds 0/1 and button mask 0x0400. Original
  `FUN_80068c14` -> `zz_0068d04_` tests the rising-edge word +0x5bc, not raw
  held +0x5b4; `zz_0068b8c_` emits transformed bit 0x80 for one frame.
  `zz_0069b98_` selects type 2. Held X separately feeds `zz_00686f0_` slot 2
  charge. Action 2 does not reset charge; active command 5 and committed charge do.
- Actual `Battle.step` records both edges before ROM action ownership can skip
  `stepAttacks`. No held repeat, no short-release duplicate, no delayed press
  queued through a busy action. Existing command priority is retained. Admission
  requires decoded type 2/action 2, ground record `0x8034ea20` [44,3,2,0].
  Empty admission does not fall back to a generic attack.
- `FUN_80166fa8`, chunk_0042:3766–3846, gates the action on positive signed
  +0x1cf0, consumes source weapon 2 once with `zz_006dbe0_(2,1,1)`, and calls
  ports 0,1,2,3 with saved +0x518. Authored g4s0/s1 part 0 aux is dispatched
  before the handler on frame 16; frame 0 clears the gate on repetition.
  Interruption before that gate spends nothing. Late depletion produces no
  payload and does not poison the bridge's future-X fallback latch.
- Browser/HUD weapon 1 aliases source cell 2, as in the already decoded
  `FUN_800562b8` second-stat-segment binding. pl0101's [1,1,0,120] X row uses
  integer source timer debt, source-slot pause bit 4, and shared source refill
  rate handling. Aliased cells are ticked once. The charging threshold remains
  180 plus ten warmup frames; ammo/reload 120 is not charge time.

## Projectile table and physics

Original boot.dol SHA256:
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
Original table `0x80350660`, stride 48, rows 0..3 was reread from the user disc.
Each row: model 26, HIT/pool 0, speed 40, acceleration −1, scale [1,1,1], life 40,
roll divisor 16, count 4, axis 2 (local Z), inversion 0, effect 0, sound 6.
Pitch units are 2,1,4,4 respectively, multiplied by PI/16.

Joints are 7,11,7,11. Local offsets are (−118,16,30), (118,16,30),
(−118,−22,30), (118,−22,30). Upper normal offset 16 must not be confused
with charged-primary offset 36. Each port consumes one RNG nibble for roll,
then four source-byte speed factors `((byte & 7) + 9) / 16`. Four evenly spaced
cone directions share the source basis. Normal and charged-split children
reuse the same constructor/flight/shrink math, not duplicated tuned physics.

`FUN_8016d584` -> `FUN_8016d95c` -> `FUN_8016d9ac`/`FUN_8016db34`/
`FUN_8016dcc0` (chunk_0043:4633–4980) provides the lifecycle: no constructor
flight step; first subsequent step life 39, source speed/deceleration and
local-Z spin 0x1400, then scale×0.8 on expiry/termination until below 0.001.
HIT 0 resolves family damage record 1, collision flag 1. As in charged children,
the browser uses max-extent radius 20 and bank 26/team tint, alpha 1.

## Saved aim and honest boundaries

`zz_006a104_` calls `zz_006bda8_` at admission, which snapshots target center
into +0x518. The host snapshots the selected target root and does not chase a
moving target during windup. Static muzzle and reference transforms are
computed at the fire gate, separately from this saved aim.

Without a target, source X/Z are **absolute world coordinates**
`20000*sin(yaw), 20000*cos(yaw)`, without adding actor position.
`FLOAT_80437678` was verified as 20000. Descriptor byte+0x10 is 3:
constructor instructions 80166000/8016602c/80166038 bind actor+0x4b0 to
0x8034e830, and original byte 0x8034e840 is 3. Source Y is joint 3's world
matrix translation. The static-bind host approximation is
actorY + ownerScale×124.89293384552002. Joint 3 and ancestors have zero
rotation/unit scale. Model SHA256:
`eb9e768cfc2dc7f02f91c1e76ffe84d8927f030c33f022fc20bc0f89ba6cebaa`.

This is not full animated-pose or FPU equivalence. Target center is a host
root; muzzles/reference axis and no-target joint 3 use static binds plus owner
yaw/scale, not animated joint matrices. Source cone degenerate-vector
safeguards remain explicitly finite host behavior. Global RNG scheduling,
full command admission/cancel masks and status timestep parity are not
claimed. Existing host action recovery and terrain/body swept collision
stand-ins remain. Port effect 0 and sound 6 presentation are not implemented
here; no fake damaging effect is added. Scope is normal X on this one borg;
other families and charged action 3 retain their existing behavior.

## Verification

Pure tests cover all four normal port cones, seeded twenty-draw volley, static
muzzle coordinates under owner yaw/scale, HIT identity and shared lifecycle.
Actual Battle tests cover press admission, authored frame 16, full/empty/late
ammo denial, interruption, repeated presses, held/no-release duplication,
charge accumulation through action 2 and subsequent charged release, integer
120-frame refill and source pause mask, paired cached refill rates, target
movement during windup, and off-origin/scaled no-target aim. Independent
probes also cover a fresh press during ROM ownership remaining discarded after
recovery/refill, successful firing after a late resource denial, and strict
owner/action scope. Complete combat lifecycle and TypeScript checks pass.

Contributor aggregate stops at the existing sparse-checkout HUD asset gap:
ASCII font, face roundel and borg banner image are absent. Policy, typecheck
and browser gate pass before that stop. Every remaining contributor stage was
run separately and passed: menu, force builder, game session, battle pause/input,
title, camera, challenge flow, render disposal, ROM checks, OGhidra import,
and production game build. Docs verification cannot reach atlas/link checking
because `research/asset-inventory/borg-assets.json` is absent. No missing assets
were manufactured. Browser visual playthrough was not performed by this lane.
