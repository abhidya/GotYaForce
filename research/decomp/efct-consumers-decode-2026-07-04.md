# efct00 bank consumers decode — the OTHER zz_0006fb4_ callers + matAnim color tracks

**Date:** 2026-07-04
**Question:** the ptl-format notes' documented next steps — (a) which game events the other
~230 `zz_0006fb4_ @80006fb4` call sites serve (projectile visuals, muzzle flashes, status
FX) and which texIds they use; (b) what the archive's matAnim (HSD material animation)
banks encode and who consumes them.
**Answer:** the bank-argument (param 9) partitions the call sites cleanly; the three
gameplay-relevant DAT_803bb374 consumers are DECODED (launch/muzzle FX family, projectile
flight visuals, slow/haste status FX) with their texId tables dumped from boot.dol, and the
matAnim color tracks are extracted into efctBankMeshes.json. Honest unknowns in §6.

---

## 1. Call-site census — the bank argument partitions the space

`zz_0006fb4_(f1..f8, bank, slotPtr, texId, ...)` resolves
`jobjDescArray = (*(bank+0x10))->word0; JObjLoadJoint(jobjDescArray[texId])`. ~230 call
sites in the corpus; what `bank` is decides which archive texId indexes:

| bank arg | identity | sites (approx) | decoded? |
|---|---|---|---|
| `DAT_803bb374` | **efct00_mdl.arc** (efct.pzz m1) — the 157-entry bank already parsed to efctBankMeshes.json | ~28 | the 3 gameplay consumers below; rest enumerated §5 |
| `DAT_803bb384` | second battle-FX bank, loaded next to 374 by the same init family — **presumed efct01_mdl.arc** (efct.pzz m2, same archive shape); consumer cluster chunk_0032 | ~15 | NOT decoded (no impact on current port visuals) |
| `DAT_803bb470` | third bank of that block (chunk_0012 5459/5534/5714/5768 cluster) | ~5 | NOT decoded |
| `DAT_804361fc` | a menu/system-scene bank pointer (bss; set by a different loader) | ~120 | NOT decoded — menu/UI scenes, out of battle scope |
| `zz_0006f78_(obj)` = `DAT_803bbac0 + player*0xc30` | **per-player weapon-FX bank** (each player slot's own parsed archive) | ~6 | format known, per-borg contents NOT decoded |
| `*(actor+0x600)` | per-actor model bank (borg's own archive) | ~25 | borg-specific effects, NOT decoded |
| misc locals (`iVar\d+`) | one of the above via a local | ~30 | per-site |

Everything below is about `DAT_803bb374` = the bank the port renders.

## 2. Launch/muzzle FX family — zz_00aedc0_ @0x800aedc0 (chunk_0017.c:2380) — DECODED

Generic "oriented layered flash" spawner: `zz_00aedc0_(actor, basisMtx3x4, id, teamByte)`
allocates effect type 9 with `layerCount = fence[id+1]-fence[id]` layers.

- **Fence table** s16[10] @ **0x802fafd0**: `0,0,1,2,4,6,8,10,13,16,18` → ids 0..8.
  (dumped from boot.dol; 0x802fafd0..0x802fafe4 sits exactly before the state dispatch
  table PTR_FUN_802fafe4 = {800af054 init, 800af2d0 update, 800af3a8, 800af3bc}.)
- **Layer def table** @ **0x802faef8**, 0xc stride — SAME row format as the impact
  variants: `{s16 texId, s16 lifeFrames, u32 scaleTrackPtr, u32 alphaTrackPtr}`, tracks in
  the boot.dol `{s32 frame, f32 x,y,z}` / `{s32 frame, f32 a}` −1-terminated format
  (evaluators zz_0018f88_/zz_0019338_ — identical to the impact chain).
- Init `FUN_800af054`: extracts the basis columns' magnitudes as the node scale,
  normalizes, gives each layer a random z-spin phase (except def row 7), loads the bank
  mesh and **attaches the entry's matAnim at frame = teamByte** (id==2 layers via
  zz_0006fb4_+zz_00086b8_, all others via zz_000726c_; mode `PTR_DAT_80433934[0x51]==3`
  forces frame 0 — the same mode-3 quirk as the impact id-1 burst).

Full id → layer dump (boot.dol; frames @60fps; scale keys {f,x,y,z}, alpha {f,a}):

| id | rows | layers (texId, life, scale keys, alpha keys) |
|---|---|---|
| 0 | 0 | **35**, 4f, (0:1,1,1)(1:.25,.25,.25)(4:0,0,.25), a(0:1)(1:1)(4:0) — **the gun muzzle flash** |
| 1 | 1 | 55, 3f, (0:.5)(3:1), no alpha track |
| 2 | 2-3 | 10, 2f, (0:1)(1:.25)(2:0) + 11, 10f, (0:1)(10:1.5), a(0:1)(10:0) |
| 3 | 4-5 | 92, 2f + 93, 10f (same key shapes as id 2) |
| 4 | 6-7 | 92, 2f + 99, 15f, (0:1)(1:1.5)(15:2), a(0:1)(15:0) |
| 5 | 8-9 | 92, 2f + 35, 7f, (0:0)(1:1)(4:1.5)(7:0,0,4) |
| 6 | 10-12 | 74, 4f + 75, 10f + 76, 13f (delayed ring: a(0:0)(2:0)(3:1)(8:1)(13:0)) |
| 7 | 13-15 | 1, 3f + 20, 11f, (1:.7,.7,3)(10:0,0,6) + 76, 26f |
| 8 | 16-17 | 92, 2f + 93, 10f (0.8-scaled variants) |

Callers → game events:

- **FUN_80072218 @0x80072218** (chunk_0010.c:174): basis from the gun joint matrix block
  actor+0xa24 (forward negated: FLOAT_80437780 = −1.0, unit scale), spawns **id 0** and
  plays SFX 6 → **the generic shot muzzle flash** (texId 35 = a z-elongated flash cone;
  z = shot axis). Twin copy FUN_80135ce8-adjacent @chunk_0035.c:2868; two more id-0 sites
  in chunk_0030.c:3817 / chunk_0048.c:1897+1910 (other fire paths).
- **FUN_8007dd84 @0x8007dd84** (projectile spawn, §3): row byte +0x34 ≥ 0 → spawn that id
  oriented along the launch direction (most rows carry −1 = none).
- **zz_00aeef8_ @0x800aeef8**: id 7 at the HAND joint (joint 6, or 10 when param 0;
  hand basis scaled by FLOAT_804382c8 = −1.0) — a melee hand flash (caller chunk_0025.c:1969).
- Static ids 1 (chunk_0061/0062 ×3), 3 (chunk_0045.c:5492), 4 (chunk_0040.c:3895) and
  per-table bytes (DAT_802d7b42, DAT_802d97a4, DAT_802da563, DAT_8030313b, DAT_8031ef87,
  DAT_8033d256, DAT_80340f06, DAT_8035068d, DAT_803507f4, DAT_8038e07e ×s16) from
  borg-specific shot tables — not resolved per-borg here.

## 3. Projectile flight visuals — FUN_8007dd84 @0x8007dd84 (chunk_0011.c:4282) — DECODED (format)

The shot init keyed by variant byte +0x11 into the 0x38-stride row table **0x802d6d68**
(10 rows; the same table shotVariantKinds.json already dumps as `rawBytes` — kindOffset 3).
Visual-relevant row fields (offsets within the 56-byte row):

| off | field |
|---|---|
| +0x00 | s16 `texId \| flags`: **0x4000** set → efct00 bank + matAnim attached at frame **1.0 (team 0) / 3.0 (team 1)** (FLOAT_804379d0/d4); **0x8000** (alone) → efct00 bank, no matAnim; **neither** → texId indexes the PER-PLAYER weapon bank `zz_0006f78_` (DAT_803bbac0+player*0xc30) |
| +0x02 | u8 attach joint index (actor mtx array +0x8d4, 0x30 stride) |
| +0x03 | u8 hit kind (already in shotVariantKinds.json) |
| +0x04 | f32[3] muzzle offset vector (joint space) |
| +0x10 | f32 speed |
| +0x34 | s8 launch-FX id → zz_00aedc0_ (−1 = none) |

Examples: rows 0-3 (NORMAL NINJA family guns) = texId **14** from the per-player weapon
bank, launch FX −1; rows 6/7 (G RED/BLACK 0x615-family shots) = `0xc07d` → efct00 texId
**125** team-tinted (extracted tracks: frame 1 ≈ BLUE, frame 3 ≈ RED — matching the 1.0/3.0
team frames), launch FX id 0. The other ~80 spawner tables (one per fire function, listed in
shotVariantKinds.json `tables`) carry the same row format; decoding THEIR texIds per borg is
mechanical but not done here (§6).

## 4. Slow/haste status FX — zz_013f300_ @0x8013f300 (chunk_0037.c:421) — DECODED

`zz_013f300_(target, 0 slow | 1 haste)` (spawned by the on-hit status writers,
status-effects-decode-2026-07-04.md) builds a 4-part aura:

- **texIds**: s16 table @ **0x80434670** = `[0x30, 0x31, 0x32]` = **48, 49, 50**, indexed
  by clamped part slot `[0,0,1,2]` → parts = 48, 48, 49, 50 (FUN_8013f84c).
  Bank geometry: 48 = flat 113-radius star ring (672 tris), 49 = 108-long clock hand,
  50 = 75-long short hand → an animated CLOCK with orbiting sparkles.
- **Motion** (FUN_8013f84c seed, zz_013fa70_ advance, s16 angle units/frame):
  slot-0 parts tumble in world space (random z/x phases `rand<<8`; speeds x=±1024·t,
  z=±1024·(1−t), t=(rand&0x3f)/63, random signs); slots 1/2 are **camera-facing billboards**
  (draw path FUN_8013f790, basis zz_00484e8_ + up DAT_802b0cb4) spinning in the view plane
  at **−2184** (slot 1, ~12°/f) and **−182** (slot 2, ~1°/f). **Slow halves all speeds.**
- **Color pulse**: every tick the entry matAnim is re-attached at frame
  `s = clamp(sin(phase)·0.5+0.5, 0, 1)` (+0x1e phase += **0x222**/f slow, **0x444**/f haste;
  floats 0.5/1.0/0.0 @0x8043a150/54/58) **+2 when slow** (the countLeadingZeros(+0x11)
  expression) → haste samples track frames 0..1, slow samples 2..3.
  The extracted tracks CONFIRM the split: 48/49/50 all carry r/g/b keys
  f0=(1,1,1) f1=(1,0.2,0) [white↔ORANGE = haste] f2=(1,1,1) f3=(0,0.3,1) [white↔BLUE = slow].
- **Anchor/scale**: at the target's matrix translation (+0x910/920/930), scale = actor
  scale +0xb4 × per-borg float +0x7fc (NOT decoded). Lifetime: while the 900f status timer
  (+0x710/+0x712) runs; a tick SFX (zz_00f036c_ id 0x19) plays every 24f.

## 5. Remaining DAT_803bb374 sites (enumerated, NOT decoded)

chunk_0002.c:1661/2313/3358/3403 (the impact handlers, already decoded — NO matAnim attach);
chunk_0006.c:2531; chunk_0011.c:4424-4434 (=FUN_8007dd84 §3); chunk_0012.c:4138/4216/4467/
4528/4653/4814 (effect-object family around the 0x114-matrix pattern — launch-FX-like,
per-table ids); chunk_0014.c:2950; chunk_0017.c:2572/4582/4884/5019 (incl. FUN_800af054 §2);
chunk_0018.c:2324; chunk_0019.c:2469/2643; chunk_0020.c:4565; chunk_0027.c:670;
chunk_0033.c:324; chunk_0036.c:32/3532; chunk_0037.c:739 (=zz_013f300_ §4).

## 6. matAnim color tracks — extracted (scripts/gen-ptl-cell-map.mjs)

- Chain: `JOBJDesc+8` → NULL-terminated **MatAnimJoint\* array** (the ROM attach
  `zz_00086b8_ @800086b8` / `zz_000726c_ @8000726c` only uses element [0], via
  `HSD_JObjAddAnimAll(jobj, 0, matAnimJoint, 0)` + ReqAnimAll at the caller's frame) →
  MatAnimJoint tree (child/next/matAnim, parallel to the JOBJ tree) → MatAnim list
  (parallel to the DOBJ list) → AOBJ `{flags, endFrame, FObjDesc}` → FObj packed keyframes
  (HSD varint opcodes; values LITTLE-endian; structures verified against tools/HSDLib).
- Extracted per dobj into efctBankMeshes.json `anim: { end, r/g/b/a: [[frame, value,
  interpCode], ...] }` — MatTrackType DIFFUSE_R/G/B (4/5/6) + ALPHA (10); the HSD alpha
  track stores TRANSPARENCY, converted to OPACITY at generation. Coverage: **89 dobjs**
  across the 75 hasMatAnim entries; every AOBJ in the bank also carries AMBIENT_R/G/B +
  SPECULAR_R/G/B tracks (types 1/2/3/7/8/9, 89 each) — skipped: the bank draws unlit
  (no lighting flags), so only diffuse/alpha are consumed; counts recorded in `_meta`.
- Generator self-asserts (fails loudly): texIds 35/48/49/50 must have color tracks and
  48/49/50 must span frame ≥ 3 (the slow pulse window).

## 7. Port wiring (2026-07-04)

- **scripts/gen-ptl-cell-map.mjs**: matAnim decode (§6) → efctBankMeshes.json (+14 KB).
- **apps/game/src/sim/battleScene.ts**:
  - `spawnBankFx` new opts: exact ROM `scaleKeys`/`alphaKeys` (piecewise-linear, replaces
    the start/end lerp) and static `matAnimFrame` color sample (`sampleBankAnim`).
  - **Muzzle flash** = DERIVED: bank texId 35 with the id-0 tracks (§2), matAnim frame =
    attacker team (0 blue / 1 red-pink). TUNED: spawn position (shared MUZZLE_OFFSET stands
    in for the gun joint matrix), yaw-only orientation, the per-slot trigger heuristic
    (the ROM triggers per fire function; most projectile rows carry launch-FX −1), sprite
    fallback.
  - **Slow/haste auras** = DERIVED: per-actor persistent 4-part aura (texIds 48/48/49/50),
    ROM spins/billboarding/pulse rates, pulse-sampled matAnim colors (+2 slow window),
    lifetime = the sim's 900f timers (new BattleActorView slowHitTimer/hasteHitTimer from
    the existing BorgRuntime fields). TUNED: overall scale 1.0 (+0x7fc undecoded), anchor
    at borg position, no 24f tick SFX, Math.random() in place of the ROM RNG stream.
  - `setCamera` (main.ts) gives the clock-hand billboards their camera basis.
- NOT wired (documented only): per-variant projectile flight texIds (§3 — needs the
  per-borg fire-table join; port keeps its TUNED visualKind sprites), the melee hand flash
  id 7, launch-FX ids on shot tables, DAT_803bb384/470 and menu banks.

**Validation:** `pnpm typecheck` ✓, `packages/combat/dist/selfcheck.js` ✓,
`scripts/selfcheck-1p-challenge.mjs` ✓, `scripts/selfcheck-challenge-stages.mjs` ✓,
generator self-asserts (§6) ✓.

**Honest unknowns:** per-borg projectile texId resolution (mechanical via
shotVariantKinds.json rawBytes +0x00/+0x34, not done); the +0x7fc aura scale float; whether
matAnim ADVANCES over a muzzle layer's life after the initial team-frame attach (AObj rate
not traced — the port samples statically; entry 35's tracks are step-keyed at integer
frames, so any drift within 4f is ≤1 key); DAT_803bb384/DAT_803bb470/DAT_804361fc bank
identities; the ambient/specular tracks' effect (unlit bank — presumed dead data).
