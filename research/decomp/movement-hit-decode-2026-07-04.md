# Movement speed chain + HIT kind pipeline + damage-table bindings (2026-07-04 decode)

Three corpus digs, all DERIVED with quoted evidence (condensed from the session's agent
reports). These retire the port's biggest remaining TUNED movement debt and fully map the
attack-HIT selection pipeline.

## 1. Ground-speed chain — FULLY DERIVED (retires the 22.0 anchor)

Actor fields: scalar h-speed `+0x44`, h-accel `+0x4c`, v-speed `+0x48`, gravity `+0x50`,
status timescale `+0x5f4`, tier velocity scale `+0x5f8`. Integrator family FUN_80067310 /
zz_0067458_ / FUN_80067524 (chunk_0008.c:3780-3906):

    worldDelta/frame = speed(+0x44) × timescale(+0x5f4) × velScale(+0x5f8)
    speed += accel(+0x4c) × timescale

- **Run start SNAPS speed to page+0x2c** (`zz_005f578_` chunk_0007.c:5973:
  `+0x44 = page[+0x2c]; +0x4c = 0;` — also chunk_0008.c:170/1339/2199). page+0x2c IS the
  run speed; there is NO lerp to it. Over-speed is braked back to page+0x2c by the
  0.90/0.10 blend (FUN_800633c8 chunk_0008.c:1148-1163).
- **page+0x50 ("speed stat") is a MINIMUM**: launch floor (`FUN_80061f50` chunk_0008.c:324-328
  `if (+0x44 < page[+0x50]) +0x44 = page[+0x50]`, then `+0x48 = page[+0x48]` jump impulse)
  and landing seed ×0.5 (chunk_0007.c:5201/6537, FLOAT_80437460 = 0.5). It is NOT run speed.
- **Both multipliers are ×1.0 at baseline** (FLOAT_804373c8 = 1.0; tier 16 row = 1.0) —
  so ROM world units are 1:1 with the port's stage geometry, and G RED's ground run speed
  is **12.0 u/f raw**. The old 22.0 backward-walk trace anchor could NOT be reconciled with
  any code path (no ×1.833 exists) — honest conclusion: the trace sample was not plain walk
  or was mis-sampled; re-trace watching +0x44/+0x5f4/+0x5f8/+0x74a directly if re-anchoring.
- Idle decay ×0.98/frame (chunk_0008.c:383-385); per-frame accel `+0x4c = page[+0x44] ×
  cos(page[+0x42])` (chunk_0008.c:376-381); "accel==0 → snap" is emergent, not a branch.
- Per-page velocity clamp triplet `+0x74/+0x78/+0x7c` → actor+0x678 (zz_0055dcc_
  chunk_0006.c:8105), clamps +0x44 only while +0x4c > 0: G RED = 8/18/-30; most borgs
  100/100/-35 (inert).
- **Stat rows do NOT feed movement** (honest negative): PTR_DAT_802f2988 rows only feed
  ammo/weapon fields (chunk_0007.c:60-71) and HP (chunk_0006.c:8181-8184).

**Status/tier multipliers (the Acceleration-Ninja mechanism):**
- +0x5f4 rebuilt per frame by FUN_8005a378 (chunk_0007.c:2817-2898): base 1.0; burst/fusion
  flag +0x6fc → ×1.5 (FLOAT_804373d8); haste table DAT_802dd58c = {0.1, 1.25, 1.5, 1.75}
  (idx +0x70d/+0x70f); slow table DAT_802dd57c = {0, 0.7, 0.4, 0.2} (idx +0x70c/+0x70e,
  hit-inflicted chunk_0003.c:7673/8105/8143); freeze ×0.03 (FLOAT_804373dc) while +0x71c>0.
- +0x5f8 from the param-tier system: refresh_actor_param_tier_table @0x8006826c reads
  PTR_DAT_804339e0[page[0xa3]] + tier×0xc (tables at 0x802dd5a0/0x802dd720, 33 rows × 3
  floats: [sizeScale, animRate?, velScale]). Tier byte +0x74a defaults 16 = (1,1,1);
  17=×1.40, 18=×1.746, 19=×2.068, 20=×2.366, 21=×2.64 … 31=×4.56; <16 shrinks to ×0.06.
  Size target +0xb8 lerps into +0xb4 at ±0.05/frame (zz_005bab8_ chunk_0007.c:3689-3708).
- A self-buff special applies **+4 tiers for 1200 frames** (zz_011230c_ chunk_0031.c:590,
  reverted by FUN_8010f790 chunk_0030.c:4018) = velocity ×2.366 + size ×2.6 — the
  "acceleration" archetype. Family attribution to pl0004 NOT established in corpus (the
  dispatch link is unread); hit-applied tier deltas also exist (chunk_0003.c:6248, delta
  table BSS, auto-revert after +0x750 = 900f).

**Port consequence (landed 2026-07-04):** the port's velocities migrate to RAW ROM scale —
ground speed = page+0x2c via movementData.ts, jump = page+0x48 raw, fall gravity =
|page+0x6c| raw, MAX_FALL = 35.0 (FLOAT_804375f0), knockback PORT_SCALE = 1.0. The old
22.0-anchored constants were internally inconsistent with the 1:1 stage geometry.

## 2. HIT kind pipeline — zz_008ac80_ fully read (chunk_0013.c:1351-1413)

`zz_008ac80_(actor, kind)`: copies owner's damage-table ptr (+0x27c), reads owner hit.bin
remap `bin+0xa20 + kind*4` (≤4 entries, 0xff terminates), spawns a hit object per entry:
record ptr = `bin+0xaa0 + entry*0x50`; hitbox+0x11 = record u16+0x04 (damage index);
+0x48/+0x4a = record +0x06/+0x08 frame window; bone matrix from record byte+0x01
(|0x80 → root). Per-frame handler FUN_8008a65c (chunk_0013.c:1125-1249):
- Borg-attached: window compared against the ANIMATION frame float `actor+0x1cdc`;
  hitbox auto-despawns when the anim-ID snapshot (+0x4c = group<<12|slot) changes.
- Projectile-attached (+0x83 != 0): +0x48/+0x4a are per-tick countdowns.
- On contact: damage record = `hitbox+0x2c table + hitbox[0x11]*0x18`; rec+0x16 = re-hit
  interval; shape byte dispatches PTR_FUN_802da740/802da758[shape].
Base/body hitboxes come from the sibling zz_008ab30_ (bin+0x20 records, spawned once at
borg init chunk_0007.c:945); shared global table via zz_008ae60_ (rebinds DAT_802c4760).

**Where kinds come from:**
- **Melee/B-close: per-ANIMATION event stream** — motion opcode interpreter zz_004c050_
  (chunk_0006.c:1523) walks per-anim byte-code; handler FUN_8004c6b4 (chunk_0006.c:1727-1747)
  reads a 4-byte event record and calls `zz_008ac80_(actor, event[1])`, storing it at
  +0x744. So melee kinds live IN the mot data per swing — extract the event tracks to map
  swing→kind (no universal melee kind exists in code).
- **Shots/specials: per-weapon-family DOL variant tables** — command record bytes
  (+0x580/+0x581 = actionIndex/variantIndex) drive family modules
  (PTR_FUN_802d3b68/802d3b7c dispatch, chunk_0009.c:4210+); fire fns spawn a child with
  variant byte +0x11 (zz_006ee14_ chunk_0009.c:3789; zz_0099e70_ chunk_0015.c:1398); the
  child's init reads kind from a static table, e.g. `DAT_802d39b3[variant*0x34]`
  (chunk_0009.c:3895/3908) or DAT_802d0ff0 stride 0x24 kind at +3 (chunk_0006.c:2915-2976);
  ~40 sibling sites — static, extractable.
- **Literal kind sites (11)**: generic shot-child inits use kind 0 (FUN_80099bb4
  chunk_0015.c:1263, FUN_800a2850 :7432, FUN_800c1750 chunk_0020.c:608); borg-specific:
  pl0d06/pl0d07 kind 0 (chunk_0052.c:427/432), pl0809 kind 1 (chunk_0040.c:1162);
  sub-weapons kind 5 (chunk_0032.c:1525), 8 (chunk_0021.c:1867), 9 (chunk_0062.c:1545),
  0xc (chunk_0058.c:5767), 0x18 (chunk_0061.c:948); one runtime-global kind
  (DAT_802f6ef0, chunk_0015.c:6752).

## 3. Per-family damage-record tables — bindings solved (112 tables)

- Binding: family ctor stores the table at actor+0x27c right after its +0x4ec command-table
  write (G RED zz_018ccfc_ chunk_0046.c:4812 → DAT_80365ec0). Children inherit the owner's
  ptr (chunk_0013.c:1368). Consumer indexes `*(+0x2c) + u8 index * 0x18` with NO bounds
  check (chunk_0003.c:7514/8421/8618) → zz_003cd5c_ reads the 0x18 record.
- DAT_802d46e0 (the extracted 9-record damageRecords.json) is ONLY family 0x01's table —
  every family has its own (G RED family = 36 records at DAT_80365ec0, the largest;
  common ceiling 24; global max hit.bin damage index = 35, fits).
- **scripts/scan-damage-table-bindings.mjs** (this session) scans boot.dol for
  `stw rN, 0x27c(r3)` across all 119 ctors from commandMoveTables.json → 112 distinct
  tables, all sized ≥ maxIdx+1. 8 ctors bind per-variant tables behind actor+0x3e8 id
  compares (0x80073b70, 0x80108954, 0x80118cb8 ×4, 0x801223c0, 0x80142674, 0x8015613c,
  0x801ba020, 0x801e78c0) — emulate the compare like gen-command-move-tables.mjs does.
  scripts/scan-damage-table-extents.mjs dumps records (validated byte-for-byte vs
  damageRecords.json for DAT_802d46e0).
- **Follow-up extractor recipe**: clone gen-command-move-tables.mjs's ctor scan, capture
  +0x27c stores, per-borg record count = max hit.bin damageRecordIndex + 1, emit
  packages/combat/src/data/familyDamageRecords.json → per-hit record selection
  (attackHitTables.json record.damageRecordIndex → family table) replaces the 3-archetype
  DAMAGE_RECORD_INDEX mapping.
