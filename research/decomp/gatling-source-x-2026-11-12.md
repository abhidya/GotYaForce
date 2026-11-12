# Gatling Gunner source X: bounded browser integration

## Scope and observed failure

`pl0102`, action2, `zz_007db5c_(owner,4)` now retains its source identity,
source special-ammo cell, ballistic row and impact child. It does not resolve
through the generic primary-shot kind/variant ladder. Powered normal and charged
paths retain their existing behavior; only the proven shared primary math is
parameterized for row4.

Before this change, actual Battle input after 100 idle frames released at frame 16,
but emitted HIT4/life15/speed30/gravity2/scale0.25 and left the four-round X magazine
unchanged. `useWeaponCell(2)` saw an unused zero-max cell as infinite. The family
also applied backward recoil even with source `+0x1d0f == 0`.

## Source provenance

Original GG4E DOL SHA256:
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
The static joint audit used `pl0102_mdl.arc`, AFS member 1339, ISO offset
0x492a6800, size 215947, SHA256
`5d8e9e4eb5d1f3f4e724c94fb873c7cfa5eb53a933436c92b1b82c95463e11f0`.
Original bytes were read in place; no disc or model files were uploaded.

- Family setup/release/recovery: `docs-site/public/chunks/chunk_0035.c:3418–3536`,
  `FUN_80135be8`, `FUN_80135ce8`, `FUN_80135de4`.
- Primary spawn/init/flight: `chunk_0011.c`, `zz_007db5c_`, `FUN_8007dd84`,
  `zz_007e200_`; row4, table802d6d68 stride0x38.
- Row bytes already checked into `packages/combat/src/data/shotVariantKinds.json`:
  `000a0b00428200000000000000000000422000000000000443fa00000000000040f000003e19999a3e99999a000d010240000000ff01ffff`.
- Explosion spawn/init/hold/tail: `chunk_0012.c`, `zz_0085e00_`, `FUN_80086084`,
  `FUN_80086350`, `FUN_8008643c`. First expansion phase is omitted from the C
  export; original PPC at800862b8 was decoded directly. Phase pointers802da554
  are800862b8/80086350/8008643c.
- Explosion13 table802da0b8, stride36, address802da28c, original DOL bytes:
  `0016006b000400003c23d70a3fa000003dcccccd411000003ca3d70a000000000000000c`.
- Original `comhit.bin`, ISO offset0x47f44800, AFS-relative0x0c1ac000,
  length0x5400, SHA256
  `e6a41d20e919e0fcf77898af7800f2beaffc459e2267bf4c227879d38a40c0a1`.
  HIT107 remap `93ffffff` selects record147, shape0/flags1/damage20,
  active0..-1, local offset0, extent[310,0,0].
- Global damage20 at802c4940 (DAT802c4760+20*24):
  `001400646464000000000002000401000020000000380000`.
  HP20/down100/balance100/combo100, curves0/0, hitStrength0, effect0,
  reaction2/severity4/direction1, flagsA0x20/flagsB0, yaw0/pitch56, rehit0.
  This is the global common damage table, not Gatling's family table.

## Implemented behavior

Primary row4 uses HIT0 (Gatling family damage1, extent20), speed40,
initial gravity0.3, correction period4, gravity clamp0..7.5/slew0.15,
life600 and visual scale2. No launch flash or proximity split. Constructor
performs its first flight update once. Saved aim is captured on command admission;
the admission-time target UID is retained even if the live lock changes. Windup
can invalidate that target but never acquires a replacement (`zz_006d144_` →
`zz_006660c_`, chunk0008:3160). Only a surviving saved target enables ballistic pitch.
No-target launches use owner heading and pitch0, without inventing an aim point.
Live target root is the existing bounded substitute for source center.

Joint11 static bind translation is
[67.59280443191528,136.1260986328125,-0.000013937185372014937], plus local[65,0,0].
Owner heading and captured owner base/tier scale transform that muzzle.
Recoil heading/speed10/yVel15/gravity-1 only apply when `dashStrength1d0f != 0`.
Source cell2 aliases the existing cell1 HUD magazine (4 rounds, refill type0,
300-frame debt). Admission checks; authored release consumes exactly once.
The source denial latch prevents fallback after failed allocation. As a bounded host admission correction, X edges are
sampled even while busy, so a rejected held press is not buffered until recovery.
This does not independently claim that Gatling uses Powered's input descriptor.

Registered target hit or terrain segment contact creates explosion13. Lifetime,
owner death and host out-of-bounds termination do not. Dedicated explosion
presentation suppresses only the generic terrain puff, preserving contact effects and the true despawn reason. Once created,
the explosion outlives owner death, matching its update wrapper.

Explosion initializes scale0.01*captured owner scale, velocity0.1*owner scale,
then adds velocity each update until clamped at1.25*owner scale (13 updates).
Velocity clamp is0.02..9*owner scale, acceleration0. Three hold updates remain
collidable; the fourth disables collision and starts tail. Collision uses a
separate global hit identity, so each victim may be hit once; multiple victims
may connect in one frame. The old generic persistent-projectile interval0 rule
is NOT reused. Source evidence: victim attack-ID ring at chunk0003:7627,
identity rejection at8445+, positive-interval ID regeneration at chunk0013:1173+.
The primary and explosion are distinct attacks and can both hit a victim.

Main effect model22 starts material frame0, sound12 once. The tracked
`apps/game/public/audio/se/manifest.json` includes `se_00c` at
`audio/se/se_00c.ogg`; cue availability is confirmed, not audibly validated. Ring model18 uses
10-frame keys: scale(0:1,1,1;1:2,1,2;10:2.5,1,2.5), alpha(0:1;1:1;10:0),
scaled by captured owner scale. Tail model23 lasts through frame30, keys
scale(0:1,1,1;30:1.25,1.25,1.25), alpha(0:1;30:0), scaled by terminal
explosion scale1.25*owner. Thus tail grows from1.25 to1.5625 times owner scale.
Keys linearly interpolate via `zz_0018fd8_`/`zz_0019370_` (chunk0002).
Source yaw update writes+72 but explosion draw reads+70; no invented visual spin
or randomized gameplay RNG consumption is added. Numeric presentation is
simulation-owned and snapshots are detached.

## Explicit limits

- Primary model10 is an **owner-local** pl0102 ARC submodel, not global efct10.
  Source `0006f78` selects the player weapon bank; row flags000a do not select
  global DAT803bb374. Original model10 is a distinct one-joint/two-DOBJ model
  (root25c08, DOBJ25b78→25bf8). Existing browser export includes only main model0.
  The existing generic visible primary fallback remains, explicitly not original
  grenade art. No original assets were uploaded or substituted with global model10.
- Animated joint11 matrices are unavailable in simulation; static bind is used.
- Source shape0 is not claimed to be an exact sphere. Primary uses existing host
  swept geometry; explosion uses max extent310*scale plus host target-body radius
  as a spherical proximity approximation. Source actor/target center is root.
- Source object scheduler subframe allocation/init ordering is not proven here.
  The host creates the initialized explosion at impact, first collision is on the
  following simulation update after growth. It does not claim exact source
  collision-scheduler parity. Hit disable precedes collision on the fourth hold
  update. Tail never damages.
- Source attraction sinks, complete projectile-vs-projectile shape masks,
  target inactivity+656 and global RNG scheduling are outside this lane.
- Shared flight uses JS trig/numeric safeguards rather than bit-identical PPC/libm.

## Verification

Pure `gatlingProjectile.selftest.ts` covers row4/no-target/interval4/no-split,
static bind scaling, explosion identity and complete expansion/hold/tail timing.
`gatlingBattle.selftest.ts` exercises real Battle input/admission/release/ammo and
collision lifecycle; renderer tests separately check source effect lifecycle.
Final local validation:

- `pnpm typecheck`: passed after the target-snapshot correction.
- `pnpm --filter @gf/combat test:lifecycle`: passed, including actual Battle
  lock switches, target death/replacement, ammo and explosion damage, and existing
  Powered normal/charged regressions.
- `pnpm selfcheck:gatling-projectiles`: passed, including phase replacement,
  shared geometry ownership, repeated sync, missing assets and terrain-only FX
  suppression. Powered flash, renderer morph/lifetime and disposal checks passed.
- `pnpm selfcheck:rom`, repository policy, browser gate, menu, Force Builder,
  game session, pause, input focus, title, camera, Challenge and OGhidra port
  guard checks: passed.
- `pnpm --filter game build`: passed after the target-snapshot correction.
- `pnpm verify:contributor`: stopped at the existing sparse-checkout HUD asset
  gap after repository policy, typecheck and browser gate passed. Missing files:
  `ui/tpl/ascii/image_00_IA4.png`, `ui/hsd/fmg00_mdl/texture_001_CI8.png`, and
  `ui/tpl/bn0000/image_00_CI4.png`. All remaining stages were run separately.
- `pnpm verify:docs`: blocked by absent
  `research/asset-inventory/borg-assets.json`; downstream atlas build did not run.
- Independent review found and reproduced the admission-target snapshot bug;
  it was corrected and covered by actual Battle R-switch, target death and
  replacement-deployment regressions before publication.

Browser GPU/visual and audible play-testing remain outstanding. No source-byte
matching or complete 1:1 gameplay parity claim is implied.
