# Revolver Gunman and Billy X: bounded source integration

## Status and scope

The audit began on main `31a2420` (Gatling PR 40). The implemented lane builds on
own-position-history prerequisite `9b56406`, which remains a separate change.
It is restricted to `pl0100`/`pl0108`, action 2, spawner 80084600 and rows
0/1 or 13/14. No original assets were uploaded and no retired driver was run.

Before this lane, the first actual Battle X attempt entered the family action
but emitted nothing: the authored part-0 auxiliary gate was not mirrored, source
ammo cell 2 had no alias, and airborne entry used the grounded cue/stream.
The dedicated source adapter now replaces generic shot fallback for this path.

The shared target correction is intentionally bounded to this action, Gatling X
and Powered normal X. Captured target identity remains fixed, while its position
is refreshed from a global pre-movement snapshot. Generic `aimOrigin518` keeps
its existing host meaning. Projectile tracking still reads current target roots
in the projectile pass; actor aim snapshots are not imposed on flight tracking.

## Source and original-byte provenance

- Action wrapper/setup/release/recovery: `docs-site/public/chunks/chunk_0010.c`,
  `zz_0073668_` 80073668, `zz_00736bc_` 800736bc, `FUN_800737d8`,
  `FUN_80073a3c`, lines 1072–1254.
- Projectile spawn/init/flight/cleanup/pitch: `chunk_0012.c:3430–3997`,
  80084600, 80084790, 80084cec, 800850f8, 80085134, 80085208, 800853ec.
- Original GG4E DOL, read in place from the owner's ISO: embedded base 0x1f700,
  length 3888928, SHA256
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
- Original `pl0100data.bin` and `pl0108data.bin`: 432 bytes each; ISO offsets
  0x47ee1800 and 0x47ee5800. Byte-identical SHA256
  `b77c86957e69d69912e4db3bcb735774b19fd56cf9df537dc59ea77982299943`.
  Identical actor descriptors do **not** imply identical ammo tables.
- Shot rows are also tracked in
  `packages/combat/src/data/shotVariantKinds.json`, table 0x802d9758, stride
  0x50. Fresh original reads confirmed rows 0=13 and 1=14 byte-for-byte.
- Current HIT and damage data are tracked in `attackHitTables.json` and
  `familyDamageRecords.json`. HIT kind 0 maps to record 15 for both borgs:
  shape 0, flags 1, damage record 1, active 0..-1, zero offset, extent [20,0,0].
  Family table 0x802d46e0 record 1 has HP 30, down/balance/combo 100,
  hitStrength 4, impact effect 1, reaction flags 2, severity 6, direction 2,
  yaw trim 0, pitch trim 24, rehit interval 0. Host sphere/sweep approximation
  must not be described as an exact reconstruction of source shape 0.

## Actual input, action gate, and ammo

### X is a press event

The common input routine `zz_00685c0_`, chunk0008:4670–4687, invokes
`zz_0068b8c_(actor, DAT_802d3910, actor+61c, 0x80)` for all actors. Fresh
original bytes at 802d3910 are `000100000000000104000000`, six BE u16 values
`[1,0,0,1,0x0400,0]`.

`FUN_80068c14` mode 1 routes to `zz_0068d04_`; flags bit 0 is clear, so that
tester reads the press-edge word +5bc, not held +5b4. The wrapper emits command
bit 0x80 for one frame; `zz_0069b98_` selects type 2. See chunk0008:4874–4970
and `pad-bit-binding-decode-2026-07-05.md` section 3. The family's +4f0 table
at 802d4590 is cue dispatch, not a separate pad descriptor.

The ground command is 802d4668 `[44,3,2,0]`; the airborne record is 802d46a8
`[45,3,2,4]`. The old bridge hardcoded cue 44 and did not establish the airborne control bit,
so nominal airborne input selected g4s0. The bounded bridge now uses cue45 for
variant4 and synchronizes bit0x40 at Revolver admission; g4s1 is observed in tests.

### Authored release

Both g4s0/g4s1 in bank 802bf040 set part 0 auxiliary +1cf0 to 1 at authored
frame 14 and reset at frame 56. Actual Battle instrumentation observed part0.c=1
at press-relative tick 16, but `contactP1` stayed 0 and phase 1 never advanced.
The old scheduler delivered the event 15 ticks after admission and invoked
the handler before that delivery. Mirroring the byte alone would therefore
still release two ticks late; use the source schedule and pre-handler ordering,
not a manually forced gate in a test.
The gate is source `signed char +1cf0 > 0`, not physical collision or part 1.
Source release advances to phase 2 **before** attempting ammo allocation.

`zz_006dbe0_(actor,2,1,1)` consumes a single source cell 2 charge. A successful
gate emits two children: row 0 and 1 for pl0100; row 13 and 14 for pl0108.
Failure emits neither and must not cause generic fallback or poison the
bridge's future-X effectiveness latch. Interrupted windup spends nothing.

Ammo is read from the separate family stat table, not `pl####data.bin`:
`FUN_800562b8`, chunk0007:60–100, selects
`PTR_DAT_802f2988[family] + (subIdx + variant*20 + levelOffset)*18`.
The first 8-byte segment initializes source cell 0, and the second initializes
source cell 2. Its four u16 fields mean initial current, maximum, refill type,
refill parameter. The existing browser/HUD weapon 1 should alias source cell 2,
with a single timer update and source pause bit 4.

Fresh original reads confirmed family01 pointer802f298c contains 802dfc98.
Default row offset 2 gives:

- pl0100 at 802dfcbc: `[150,20,20,0,120,1,1,0,180]`, hence X current/max 1,
  type 0, refill debt 180; raw `0096001400140000007800010001000000b4`.
- pl0108 at 802e07fc: `[200,20,20,0,60,1,1,0,120]`, hence X current/max 1,
  type 0, refill debt 120; raw `00c8001400140000003c0001000100000078`.

All twenty rows of both variants matched the tracked source-table export.
Normal Revolver's X debt is 180 throughout its 20 rows. Billy's is 120 at rows 0..2, then decreases by 2
per row through row 17 (90), remaining 90 at rows 18–19. The runtime's level
selection is an existing empirical `levelByte+2` rule, not a newly proven source
mapping. Do not claim all-tier exact parity from the level-0 check.

The original 360-byte row blocks start at 802dfc98 and 802e07d8; their SHA256
values are `8704a4970b8bd61713fe1e083bfc0b678c98bc08087e6d571b2b148720cf4d2c`
and `162f59c9e75bb957fdf8415665daed742321be85bd79861e3d8772ba25025b46`.

Source type 0 timer starts at zero when ammunition is nonempty, is seeded only
when consumption empties the cell, subtracts the cached source refill rate,
and restores maximum when debt reaches zero. Reuse the existing source timer
helper rather than fractional generic refill. See `zz_006dbe0_` and
`zz_006dcc0_`, chunk0009:2866–2973.

## Own movement and action recovery

### +5e8 is own position history, not target position

`zz_005685c_`, chunk0007:194–227, copies old +2c/+30/+34 into +5e8/+5ec/+5f0
before copying current +20/+24/+28 into +2c/+30/+34. Initial setup seeds all
three from the owner's own position (chunk0007:699–705). Consequently source
phase 0's `(pos - history5e8)*0.95` is inertial motion, not teleporting away
from the enemy. The pre-audit host instead writes the enemy into
`targetCache5e8`, causing false distance-scaled displacement. Fix this as the
separate shared history prerequisite; do not duplicate a Revolver-only hack.

### Recovery condition is inverted in the existing family

After physics, source calls direct floor probe `zz_00677b0_`, not the
`zz_00679d0_` no-surface revert wrapper used during windup.

- Grounded with +1cef >= 0: apply `zz_006ed8c_(0.1)` to **both** horizontal
  speed +44 and vertical speed +48, then wait unless +1cee is nonzero.
- Grounded with +1cef < 0: exit immediately.
- Not grounded: wait unless +1cee is nonzero.

Thus exit is `(grounded && contactP0 < 0) || wallContact != 0`, not >=0.
The existing port reverses the sign and applies drag on the wrong branch.
At unit dt drag is exactly multiplication by 0.1; otherwise the helper uses
`v *= 1 - (1-0.1)*dt`. Exit clears +1900/+1918, +73f, controlWord low two
bits, and +6e8; selects the air/ground/upper-body return; seeds +694 with
`1 + dt`. Remaining afterimage and pose decay should retain their source gates.

## Attack target identity versus its moving aim position

Command admission `zz_006a104_` calls `zz_006bda8_` (chunk0009:619,
1798–1858), copying active handles +504/+508 into attack handles +c8/+cc and
current flags +7d2 into +d0. This captures **identity**, not a new lock each tick.

Every global `zz_006ae60_` update refreshes +518/+51c/+520 from that captured
attack object's live center +64/+68/+6c (chunk0009:1365–1385). Its caller is
the main tick `zz_0029434_`, chunk0003:4315. Therefore position must not be
frozen at admission. `zz_006d0dc_` calls `zz_006660c_` unconditionally:
it validates existing attack handles and aims toward +518, or clears them if
invalid; it does not acquire a replacement. Optional airborne `zz_006e1ac_`
also reads +518 and part 1's matrix anchor. Children copy the surviving attack
handles at release. Their initial ballistic pitch reads the live center again.

Do not globally rewrite current `aimOrigin518`: despite its name, the host's
shared aim helpers presently treat it as the shooter's origin. Use a bounded
captured-target adapter/field in a follow-up, and then separate the source
target-center concept from the host shooter-origin concept deliberately.

Tracking eligibility also comes from admission. In `zz_006ae60_`, +758 is
3D root-to-active-target-center distance; +7d2 bit 4 is set when it is <= +814
for enemies or +818 for same-team actors (chunk0009:1303–1339).
`FUN_800562b8` loads +850/+854 from dynamic descriptor +80/+84, and
`zz_0055dcc_` copies them to +814/+818. Fresh original bytes in both actor
files are `45bb8000` = 6000 for each. These base values are not multiplied by
owner scale at those copies. Broader status-dependent range changes and source
target-shape centers need their own evidence and bounds.

## Projectile row contract

All four relevant rows share the following fields except left/right joint and
offset; rows 0/13 use joint 7 and x=-118, rows 1/14 joint 11 and x=118:

| Row offset | Meaning | Value |
|---|---|---|
| +00 s16 | Model identity | 0x400b |
| +02/+03 u8 | Attachment joint / HIT kind | 7 or 11 / 0 |
| +04 vec3 | Joint-local muzzle offset | (+/-118,6,23) |
| +10 f32 | Speed | 60 |
| +14 f32 | Initial gravity | 0.30000001192092896 |
| +18 u32 | Correction interval | 1 |
| +1c f32 | Horizontal turn cap, degrees/update | 1 |
| +20/+24 f32 | Desired gravity clamp | 0 / 7.5 |
| +28 f32 | Gravity change cap/update | 0.15000000596046448 |
| +2c f32 | Target-surface proximity detach threshold | 25 |
| +30 vec3 | Target offset in captured joint orientation | (0,20,0) |
| +3c vec3 | Child scale multipliers | (1,1,1) |
| +48..4f | Direction/invert/reference/invert/FX/unused/cue/unused | 5,0,2,0,5,0,6,0 |

**The value 25 is not a turn rate.** `FUN_80083874` compares target-center
distance minus the source target shape's radius/extent against 25, clearing
the child's +c8 when close. Target inactivity also clears it. This stops
homing, not the projectile. Actual horizontal angular correction is one
degree/update in `FUN_8006c498`.

Model flag semantics are spawner-specific: in `FUN_80084790`, bit 0x4000
selects the owner's weapon bank (`zz_0006f78_`) and strips that bit to model 11.
It does **not** mean global efct11. Do not reuse the different flag meaning
of the 8007db5c/Gatling spawner. No verified owner-local model11 browser export
was found; generic visible shell art remains an explicit placeholder.

Original static model0 joint chains for both archives have rotation zero,
scale one. World-bind translations (before owner scale/yaw) are:

- Aim joint 3: (0,124.89293384552002,0).
- Joint 7: (-67.59277391433716,136.1260347366333,-0.00000385384).
- Joint 11: (67.59280443191528,136.12609577178955,-0.0000139372).

These are static bind transforms, not animated muzzle transforms. Ground fire
also changes pose +1900/+1918 using 800853ec and the current joint X-axis pitch
before the children are scheduled; missing animated world matrices must remain
an explicit limitation.

The separate original model archives used for this comparison were
`pl0100_mdl.arc`, AFS index1327, ISO490b9000, length225767, SHA256
`0a5c6b0122e6ef2c4ff92c871b284a792adb05ffa365b853cc071c0e5277217d`, and
`pl0108_mdl.arc`, index1373, ISO496b6000, length226403, SHA256
`58a8faffcd88b78fc71630b363387511511dec0f6b8acd240dd1a196cdd1ce4d`.
Both have 12 model descriptors and 20 model0 joints. Model descriptor count
alone does not prove which original owner-local asset is bound at runtime.

## Exact init and flight order

### Init: 80084790

1. Set phase 1, matrix update 80048288, transform flags 0x10, direction mode 5,
   and life 600. Muzzle = current owner attachment matrix * local offset.
2. `zz_00853ec_` computes a low ballistic pitch toward live captured center:
   horizontal distance is floored at 0.0001; q = gravity*d*d/(2*speed*speed);
   discriminant is clamped to >=0; pitch = atan((d-sqrt(d*d-4*q*(q+dy)))/(2*q)),
   capped above at 0.8 rad. Return signed BAM16
   `-ownerPitch1d64 - trunc(10430.3779296875*pitch)`.
   With no target, pitch term is zero, leaving -ownerPitch1d64.
3. Direction mode 5 takes the Z column of owner joint0 basis * local X rotation
   by this angle. Reference mode 2 takes the attachment joint's Z column.
   Copy the attachment matrix to child+144 for later target-offset transforms.
4. Build the projectile matrix and emit launch effect 5 before HIT allocation
   and speed normalization. Allocate owner-local HIT kind 0. Failure enters
   cleanup; it must not fabricate a successful damaging shot.
5. Normalize direction and scale by 60; set interval 1 and gravity 0.3.
   If captured +d0 lacks bit 4, call 80085208 once for one gravity adjustment,
   then clear +c8. Otherwise retain target tracking.
6. Resolve owner-local model11 and emit sound cue6. **No first flight update is
   called by this constructor**, unlike the Powered/Gatling primary constructor.

### Flight: 80084cec

1. Read current matrix Y column as next reference, decrement life, and terminate
   on expiry, out-of-bounds, or registered hit flag +1d9. Advance draw roll by
   BAM 0x1400 per flight update.
2. 80083874 validates the captured target and applies surface-distance detach25.
3. Without target, advance X/Z directly by velocity.
4. With target, decrement interval. When due (every frame for these rows), form
   `goal = live target center + captured attachment rotation/scale * [0,20,0]`.
   `FUN_8006c498` temporarily removes vy, preserves horizontal speed (floored
   at 0.0001 using actor heading if needed), rotates horizontal direction toward
   goal by at most one degree, and **advances X/Z itself**, then restores vy.
   Compute remaining horizontal distance from the now-advanced position.
   With t = remainingHorizontal/horizontalSpeed, desiredGravity =
   `2*(t*vy - (goalY-posY))/(t*t)`, clamp 0..7.5, and slew by at most 0.15.
   A non-due interval advances X/Z directly.
5. Advance Y by `vy - gravity/2`, then subtract gravity from vy.
   800833a4 only sends the source target warning bookkeeping; it does not acquire
   a replacement target. Apply source size/speed status helpers (833ec/83610).
6. Normalize the full velocity and multiply by the current speed, **then restore
   the separately updated vy**. Refresh scale, handle attraction sinks (83714),
   and terrain segment contact (84170). No explosion/split child is spawned.

80085208 uses the same gravity calculation but without horizontal turning or
advancement. A dedicated Revolver state is safer than reusing Powered's different
flight order, no-lateral-steering behavior, initialization update, and split logic.
Numerical safeguards against zero flight time may be sensible host behavior, but
must be labeled rather than claimed as source branches.

Owner invalidation/reuse is checked by 80084000 before phase dispatch. Cleanup
800850f8 disables hit state through 8008aff0 and hides rendering; 80085134 frees
the object. Keep owner death, target loss, expiry, hit, terrain and bounds reasons
distinct; target loss alone is not projectile death.

### Fresh helper constants

- 80437658 = 0; 80437670 = 1; 80437688 = -1;
  8043768c = 0.01745329238474369 (degrees to radians);
  80437690 = 0.00009999999747378752.
- 80437b40 = 0.0000958738019107841 (BAM to radians);
  80437b44 = -1; double80437b48 = 0; double80437b50 = 0.5;
  double80437b58 = 3; f32 80437b60 = 2; 80437b64 = 0.5;
  80437b68 = 10; 80437b6c = 0.00009999999747378752;
  80437b70 = 4; 80437b74 = 0.800000011920929;
  80437b78 = 10430.3779296875.

## Launch effect 5 is not Powered's effect 0

`zz_0048288_` constructs the scaled mode-5 basis from flight direction/reference
and launch position, then `zz_00aedc0_` captures that matrix. Its init extracts
column magnitudes, normalizes basis columns, and uses max(X,Y) magnitude as base
scale. With these row multipliers, that is captured owner scale.

Fresh original definitions at 802faf58/802faf64:

The effect5 fence pair at 802fafda/802fafdc is raw `0008000a` = [8,10].
This confirms definition rows8/9 and corrects the extra leading zero in the
historical fence-table literal in `efct-consumers-decode-2026-07-04.md`.

- Row8 raw `005c0002802fac0000000000`: global model92, life2, scale track802fac00,
  no alpha track. Scale keys f0=(1,1,1), f1=(0.5,0.5,0.5), f2=(0,0,0).
- Row9 raw `00230007802fac4000000000`: global model35, life7, scale track802fac40,
  no alpha track. Scale keys f0=(0,0,0), f1=(1,1,1), f4=(1.5,1.5,1.5),
  f7=(0,0,4).

Each layer gets its own initial RNG byte <<8 Z phase (only definition row7 is
exempt). Team material animation is sampled separately from geometric scale.
Two successful source children therefore request two effect instances, four
layer-phase random bytes total, and cue6 once per initialized child.
There is no authored alpha fade for either layer. Update disables each layer
when its own age reaches its lifetime (800af2d0); draw uses the captured basis
and independent layer phase/scale (800af488). It does not follow the shell.

Existing `PoweredLaunchFlashObservation` is restricted to effect0/life4 and one
model35 layer with different keys. Do not send effect5 through it unchanged.
Use a dedicated observation or a reviewed generalization carrying effect ID,
captured position/basis/scale, per-layer phase, age and lifetime. Simulation owns
aging and captured data; repeated renderer sync/pause must not advance it.
Missing committed meshes must not fabricate unrelated art or sound.

## Implementation and acceptance checks

- `sourceAttackTarget.ts` samples all actor roots before movement, then refreshes
  each captured attack target by UID. A dead/missing target clears permanently.
  Bridge windup helpers consume that captured position rather than the live UI
  lock. Recovery retains its source backward recoil bearing.
- `revolverProjectileRuntime.ts` captures target identity/range at admission,
  enqueues the two rows at the authored gate and initializes them in the object
  pass after actor updates. Initialization keeps life600 and does not advance.
  This is a bounded host scheduling choice, not complete original scheduler parity.
- `revolverProjectile.ts` owns source pitch, one-degree horizontal turning,
  adaptive gravity, proximity detach and 600-update lifetime. No Powered flight
  reuse, split child or explosion was introduced. Source HIT0/damage1 reaches the
  existing damage path and collision sweep.
- Source cell2 aliases the HUD cell1 magazine; the existing verified tier rows
  supply the distinct baseline 180/120 refill periods. Input edges are sampled
  while busy, so held or rejected presses do not queue an attack after recovery.
- The bridge mirrors signed part0 aux and dispatches the stream before the family
  handler with source frame numbering. Actual input releases at authored14.
  The family recovery uses direct floor probing and the corrected negative-contact
  exit condition; grounded nonnegative contact drags both speed components.
- Effect5 has a dedicated detached simulation observation. Each child captures a
  unit basis and owner scale, two independently phased layers (92/2f and35/7f),
  and cue6. Simulation advances their ages; renderer sync does not. Visual RNG is
  an independent deterministic stream, not claimed to match global source RNG.
- Owner-local shell11 intentionally remains generic visible shell art. The
  renderer explicitly rejects any accidental global11 bank visual for this lane.

Pure tests assert no constructor movement/life loss; left/right rows and
scale; target/no-target pitch; admission range inside/outside/exactly6000;
target motion and lateral one-degree turn; gravity solve after horizontal step;
detach25; target death without replacement; 600-update expiry; cleanup and no
explosion. Test zero horizontal speed/zero flight time as documented safeguards.

Actual Battle tests drive first-use and repeated X for both borgs, ground
and air. Assert exactly two source children, one ammo decrement at authored gate,
correct HIT0/damage1, full reload boundaries180/120 at baseline, no short-release
duplicate, no held repeat, no queued press through busy action, empty admission,
late depletion, interruption, lock switch, moving captured target, target death,
owner death, terrain and victim hit. Verify all observations are detached.
Dedicated renderer tests cover two distinct layer lifetimes, owner scale, independent
rotation, no alpha fade, repeated sync/pause, missing assets and disposal.

## Explicit remaining boundaries

Animated joint transforms, actor/target collision-shape centers and radii, source
attraction sinks, all projectile-vs-projectile masks, inactive-target +656,
status-dependent range/size/speed changes, exact global scheduler allocation
ordering and global RNG scheduling are not proven by this bounded lane.
The target adapter should document root/body-radius substitutions clearly.
JS trig and finite safeguards are not bit-identical PPC/libm execution.
Original visible shell art is not exported. This audit does not constitute GPU
browser or audible play-testing, and does not claim complete game parity.

## Validation record

- `pnpm typecheck`: passed after runtime integration.
- `pnpm selfcheck:rom`: passed, including existing family helper tests.
- `pnpm --filter @gf/combat test:lifecycle`: passed, including the new actual
  Battle suite and prior source X lanes.
- `pnpm selfcheck:revolver-launch-flashes`, `selfcheck:powered-launch-flashes`
  and `selfcheck:gatling-projectiles`: passed.
- `pnpm --filter game build`: passed with existing missing-reference-image and
  large-bundle warnings. `git diff --check`: passed.
- Actual Battle tests cover both ground/air inputs, exact authored gate14, two
  children/one allocation, baseline refill180/120, held/release/busy/empty/late
  denial, interruption, captured target motion/R-switch/loss, range6000 boundary,
  actor-order-invariant pre-movement aiming, source lifetime and cleanup.
- Natural victim contact is tested at range 1500. At range 800 the static wide
  muzzles and source 1-degree cap miss the centered host body; tests do not alter
  flight math to force a close-range hit.
- GPU browser and audible play-testing are separate validation; these unit and
  renderer checks do not claim either.
