# Powered Gunman charged-X source lane

Scope: pl0101 exact type 5 / action 3, record 0x8034ead0 [44, 3, 3, 0], spawner
0x8007db5c rows **8, 9, 6, 7**. Normal B, short-X compatibility and other families
retain their existing routes. No raw assets were copied/uploaded or replaced.

## Source evidence

Original boot.dol SHA-256:
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
Original pl0101data.bin +0x18c = float 180 (0x43340000). X weapon row
[1, 1, 0, 120] is ammo/reload data, not charge timing.

- zz_00686f0_, chunk_0008:4691–4785: ten held warmup frames, then charge 180.
  Neutral dt = 1 reaches ready on held frame 190. Paired active burst maps to source
  +0x6fc tenfold accumulation, reaching frame 28; warmup/decay are unchanged.
  Release tests ready before subtracting 2. Residual survives subthreshold release;
  rehold warms up again. Active command 5 and successful commit clear counters.
  Other active actions do not stop charge bookkeeping.
- zz_0069c50_ → zz_0069dd0_ → zz_0069fe0_ → zz_006a104_ (chunk_0009) type 5 has no ammo consumption.
  FUN_80166fa8, chunk_0042:3825–3840, gates action 2 only with
  zz_006dbe0_(2, 1, 1). Action 3 emits rows 8, 9, 6, 7 and effect 6 at 0x800f036c
  unconditionally. Effect 6 creates no damaging fifth projectile.
- Bank 0x8034ebe0 g4s0/s1 sets part 0 aux 1 at authored frame 16. DOL opcode 02
  writes this signed byte to +0x1cf0 (not part 1.state). The narrow bridge maps
  that byte and dispatches the stream before the same-frame handler gate.
  Frame 0 clears it on repeat. See action-vm-and-gcrash-decode-2026-07-05.md.
- Primary table 0x802d6d68 stride 56, init/update 0x8007df18/0x8007e18c:
  HIT 15, speed 60, life 600 with immediate init update; ballistic initial pitch,
  fixed horizontal heading; gravity interval 1, clamp 0..7.5, slew 0.15;
  half-step vertical displacement; normalize full velocity then restore vy.
  Invalid targets are permanently dropped. Distance <300 × target scale replaces
  the primary before movement/collision with secondary ports 6, 7, 4, 5 respectively.
- Secondary 0x8016d584, table 0x80350660 rows 4..7 and speed array 0x80350640:
  four children per primary, five byte-RNG draws, source cone basis,
  randomized speed/deceleration, no constructor flight tick; life 40 then
  scale × 0.8 until <0.001. Terrain/hit termination enters shrink.
- Primary bank 125/team tint, scale 0.4, +0x1800 BAM yaw spin. Secondary bank 26,
  source basis plus local-Z +0x1400 spin, scale inherited from owner. Alpha 1
  overrides generic fade; secondary disappearance is scale shrink.
- HIT 15 and HIT 0 independently resolve to family damage record 1. Their raw
  radius is 0 and half extent is [20, 0, 0]; the existing browser max-extent
  collision stand-in therefore uses radius 20, not an authored source sphere.
  Collision flags 5 vs 1 are retained metadata; existing geometry does not
  interpret them. No generic B-kind precedence or findVariantByKind(15) fallback.

## Honest implementation boundaries

Short-X remains release-based compatibility, not source press-while-charging.
The source charged route uses no tuned 45/90 tier or damage multiplier. There is
no X-charge HUD/ready indicator in the current game; none is added. Presentation
of the non-damaging 0x800f036c effect 6 and source charge glow remain unimplemented.

Only neutral one-frame timestep is supported. Full source status time scaling,
global input disable, disabled-command masks and every command admission gate
are not claimed. Host paired active burst is the bounded +0x6fc mapping. Existing
browser action recovery/cooldown and terrain/hit behavior remain in use.

Muzzles are explicitly **static-bind approximations**, not animated firing poses.
Source joints map identity to DFS slots; bone 7 origin is
(-67.59277391433716, 136.12603759765625, -0.000003853841917589307), bone 11
(67.59280443191528, 136.1260986328125, -0.000013937185372014937).
Ancestors have zero rotation/unit scale. Row offsets ± 118, y 36/-22, z 30 are added
before owner yaw/scale. Neutral lower muzzles stay above ground. Renderer matrices
never feed simulation. Original model SHA-256:
`eb9e768cfc2dc7f02f91c1e76ffe84d8927f030c33f022fc20bc0f89ba6cebaa`.

Source saved launch aim +0x518 and live target center +0x64 both use target root in
the host adapter; independent animated transforms are absent. Pure math exposes
launchAim separately. JS floating-point/trig and explicit finite degenerate
trajectory/basis safeguards are not source FPU bit equivalence. Source RNG byte
routine is reused, but global RNG scheduling is not claimed equivalent.

Collision retains the browser swept body/terrain stand-ins, not original animated
hitbox geometry. The existing generic special body adapter in the source audit
pass does not sync HP/reactions into gameplay; live damage uses projectiles.

## Verification

Pure tests cover ballistic/half-step math, fixed heading, gravity clamps/slew,
target invalidation, lifetime, strict scaled proximity, immediate init update,
seeded four-child cones/speeds, secondary no-init-tick, shrink/deceleration,
owner scale and static muzzle coordinates.

Lifecycle integration tests exercise actual Battle hold/release at ammo 0/1,
frame 190 admission, exact record/action, four row identities, no fifth damaging
effect, no allocation, source visuals/HIT flags, above-ground attachments,
constructor life 599 then 598, proximity replacement, secondary life 40 then 39,
expiry shrink, repeat frame 16 reset/no held autofire, old 90-frame negative,
residual decay, paired 28 threshold, active-command reset, prefire hit interruption,
close-target no pre-spawn damage, and unrelated-borg isolation.

Primary source invalidation is null target, inactive target byte 0, or the
conjunction target +0x83 == 0 and target +0x656 != 0 (zz_007e200_). The host
currently approximates the inactive byte using alive/HP/death state. It does not
expose +0x656; targetEligibility83 alone must not invalidate. Visibility +0x5e6
is not read by this source path.

The primary constructor retains its muzzle position for the first host terrain/body
sweep (source zz_0084170_ compares current +0x20 against previous +0x2c). Tests
include a wall between muzzle and first endpoint. Primary owner death removes the
child before a possible split. Secondary owner death transitions flight to shrink
(0x8016d95c → 0x80084000); already-shrinking children continue. These paths have
explicit regression tests. Owner identity reuse and every source owner-state byte
are not represented by the host's stable UID/alive model.
