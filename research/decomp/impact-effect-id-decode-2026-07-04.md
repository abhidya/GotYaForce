# Hit-impact effect selection decode — impactEffectId (damage record u8 +0x09)

**Date:** 2026-07-04
**Question:** where does the ROM consume the damage record's `impactEffectId` byte, what does it
index, and which visuals do the ids map to?
**Answer:** DECODED to the effect-definition table + per-variant handlers + keyframe tracks.
The only hop still unproven is texId → pixel cell (needs ptcl00.ptl/.ref parsing).

Record layout reminder (packages/combat/src/data/familyDamageRecords.json `_meta.recordLayout`,
gauges.ts `DamageRecord`): the byte is **u8 +0x09** of the 0x18-stride record (NOT +0x0e —
+0x0e is `knockbackDirMode`).

---

## 1. The consumption chain (all static, DERIVED)

### 1a. Gate + spawn call — resolve_hitbox_target_effects_and_damage @0x8002e2a8

`chunk_0003.c:8083-8188` (the tail of the hit-resolution function, after the damage/status
writers decoded in status-effects-decode-2026-07-04.md):

- `puVar17` = the attacker's hit record (`param_1+0x2c + hitboxIndex*0x18`); `iVar13` = the
  TARGET's own record (same formula on param_2).
- **Suppression gate** (`:8087-8088`):
  `if (((*(char *)(iVar13 + 9) != -1) || (target->type != 0x10)) && (*(char *)(puVar17 + 9) != -1))`
  → an attacker record with `impactEffectId == 0xff` spawns **no contact effect at all**; a
  projectile target whose own record says 0xff also suppresses.
- **Normal branch** (`:8090-8156`, no knockdown flags on either side): if none of the
  status-effect spawners fired first (`bVar2` — freeze `zz_010e158_`, stun `zz_013f300_`,
  grow/shrink/slow `zz_0176ec0_`, haste `zz_01dff24_`, drain `zz_01ec1bc_` each spawn their
  OWN effect and set `bVar2`, suppressing the generic impact spark) and the per-actor
  effect-throttle byte `+0x2af` is 0 (set to 4 on spawn — a re-spawn cooldown):
  `zz_0019550_(attackerRoot, &DAT_803b0720 /* contact point vec3 */, (uint)record[+0x09])` (`:8154`).
  Then `zz_002fc18_(attackerRoot, target, contactPoint, record[+0x0a])` (`:8156`) — the
  unknown0a byte feeds a SEPARATE per-hit call (camera shake / rumble / sfx candidate; not
  chased here).
- **Guard/projectile branch** (`:8163-8187`): when the hit is guarded (`+0x1da & 2`) or hits a
  projectile, `zz_00db250_(target, contactPoint, N)` spawns from a DIFFERENT table with
  HARDCODED ids N ∈ {0,1,3,5,6,7} keyed off the target actor's id (0x302 shield → 1, 0x603 → 3,
  0x60b → 5, 0x60d → 6, 0x60f → 7, else 0). That path ignores impactEffectId (table
  0x8031227c, 8-byte stride; entry word0 = alloc kind, word1 = def ptr — not decoded further).

### 1b. Effect-definition table — zz_0019550_ @0x80019550, table 0x802c7ed0

`chunk_0002.c:1501-1517`: `entry = 0x802c7ed0 + (id & 0xff) * 4`, bytes
`[b0 unused-here, b1 → effect+0x11, b2 → effect+0x12, b3 → effect+0x13 & alloc-kind arg]`,
passed to `zz_001959c_` which allocates the effect object (`zz_008893c_(2, 0x1f, 0, kind)`),
copies the contact point to +0x20..0x28, the attacker root to +0x8c, the attacker's
player/team byte +0x88, and installs update/draw dispatchers `FUN_800196d0`/`FUN_80019824`.

**Table dump (boot.dol .data, real entries are ids 0..8; bytes past id 8 are the ADJACENT
keyframe-track floats, i.e. table length = 9 — matching the census below):**

| id | b1 (variant) | b2 (subVariant) | b3 (kind = layer count/alloc) |
|---|---|---|---|
| 0 | 0 | 0 | 1 |
| 1 | 1 | 0 | 1 |
| 2 | 2 | 0 | 3 |
| 3 | 2 | 1 | 3 |
| 4 | 2 | 2 | 3 |
| 5 | 2 | 3 | 3 |
| 6 | 2 | 4 | 3 |
| 7 | 2 | 5 | 3 |
| 8 | 3 | 0 | 8 |

### 1c. Variant handlers — PTR_FUN_802c8174 (init) / 802c8184 (update) / 802c8194 (draw), defs PTR_DAT_802c8154

State machine: `FUN_8001970c` (state 0) dispatches init by `effect+0x11` (the variant byte);
per-variant def structs at `PTR_DAT_802c8154[variant]`, 0xc-stride rows
`{s16 texId, s16 lifeFrames, u32 scaleTrackPtr, u32 alphaTrackPtr}`.

Track formats (evaluators `zz_0018f88_`/`zz_0018fd8_` and `zz_0019338_`/`zz_0019370_`):
scale = `{s32 frame, f32 x, f32 y, f32 z}` × N, alpha = `{s32 frame, f32 a}` × N, both
terminated by frame == -1, linear interpolation between keys.

| variant | init/update | structure (dumped from boot.dol) |
|---|---|---|
| 0 (id 0) | FUN_80019860 / FUN_80019950 | ONE billboard, texId **21**, life **20f**; scale keys 1@f0 → 2@f4 → 3@f20; alpha 1@f0 → 1@f10 → 0@f20. A big slow swelling flash. |
| 1 (id 1) | FUN_80019a14 / FUN_80019c3c | PARTICLE BURST: count = (rand&3+8) + (rand>>4&3+8) = **16..22** (clamped by a global 512-particle budget at PTR_DAT_80433934+0x1e6), life **10f**, particle texId selected by the **attacker's player index** (`+0x88`): row 0 texId **2**, row 1 texId **3** (chunk_0002.c:1750-1758; forced to row 0 in mode PTR_DAT_80433934[0x51]==3). Each particle gets random velocity seeds (+0x70/+0x72). HSD JObj-based (gnt4_HSD_JObjSetFlagsAll per particle). |
| 2 (ids 2..7) | FUN_8001a288 / FUN_8001a3c4 | THREE layered quads oriented by the attacker→contact direction (PSVECSubtract + zz_0045ef4_ basis build): layer0 texId **144** life **7f** scale 1→0.25@f6→0@f7; layer1 texId **145** life **10f** scale 1→0; layer2 texId **146** life **13f** scale 0 until f2 → 1@f3 → 1.5@f13, alpha 0/0@f2/1@f3/1@f8/0@f13 (a delayed expanding ring). |
| 3 (id 8) | FUN_8001a71c / FUN_8001a7b0 | TWO layers: layer0 texId **53** life **10f** scale 0.5@f0 → 1@f2 → 0@f10; layer1 texId **54** life **6f** ANISOTROPIC scale (x,y,z) (0, 1.5, 1.5)@f0 → (1,1,1)@f2 → (1.5, 0, 0)@f6 — a collapsing/expanding cross, reads as a slash flash. |

### 1d. Honest unknowns

1. **texId → pixel cell.** ~~unproven~~ **RESOLVED (later on 2026-07-04) — and the guess
   here was WRONG**: texId does NOT index ptcl00.ptl. `zz_0006fb4_` resolves texId as an
   index into the scene_data **JOBJDesc array of efct00_mdl.arc** (157 entries; bank buffer
   = efct.pzz member 1), and the entries are **untextured vertex-colored GX meshes** — there
   is no pixel cell at all. Full chain, entry format, per-texId validation (21, 2/3,
   144/145/146, 53/54) and port wiring: research/decomp/ptl-format-notes-2026-07-04.md.
   (The texId 2/3 ↔ txg cell #2 numbering similarity was indeed a coincidence.)
2. **subVariant byte (b2, ids 2..7).** Stored at effect+0x12 (`zz_001959c_`,
   chunk_0002.c:1534) but no reader of that field was located in the effect family's
   init/update/draw handlers — plausibly consumed inside the shared draw path for
   color/hue selection (6 palette variants of the same 3-layer impact), or genuinely unused.
   Ids 2–7 are treated as one visual class in the port until located.
3. **The variant-0/1 def rows' b0 byte** (entry+0x0) is not read by zz_0019550_; unknown role.
4. **Status-FX precedence**: the ROM suppresses the generic impact spark when a
   freeze/stun/slow/haste/drain effect spawned for the same connection (bVar2 chain,
   chunk_0003.c:8091-8151). The port does NOT model this suppression (its status FX are
   HUD-side, not world-side) — noted as a fidelity gap, not wired.
5. **Effect throttle +0x2af** (set to 4 on spawn, spawn skipped while nonzero) — a per-victim
   re-spawn cooldown of ~4 frames. Not ported (the port's hit-slot edge trigger has a similar
   practical effect).

---

## 2. Census — impactEffectId across familyDamageRecords.json

1530 records / 124 distinct tables / 208 borgs (scratch script over the JSON; same numbers
reproducible from `_meta`).

| id | records | share | reading |
|---|---|---|---|
| 1 | 1021 | 66.7% | the default hit burst (variant 1) — bulk of melee AND shot records |
| 0 | 93 | 6.1% | big swelling flash (variant 0) — heavy/finisher-ish rows (avg hitStrength 9.2) |
| 2 | 65 | 4.2% | 3-layer directional impact, subVariant 0 |
| 3 | 55 | 3.6% | 3-layer, subVariant 1 |
| 8 | 53 | 3.5% | 2-layer slash/cross flash (variant 3) |
| 4 | 37 | 2.4% | 3-layer, subVariant 2 |
| 0xff | 26 | 1.7% | explicitly NO contact effect |
| 5 | 21 | 1.4% | 3-layer, subVariant 3 |
| 6, 7 | 1 + 4 | 0.3% | 3-layer, subVariants 4/5 |
| others (9..246) | 154 | 10.1% | **table-extent overshoot rows**, not design data |

**Ids 0–8 + 0xff cover 89.9% of rows and ~100% of the rows that are actually reachable**: the
out-of-range ids sit on the same corrupt high-index rows already flagged by combat.ts's
`isSaneStatusRecord` filter (grow+shrink both set, hpDamage ≈ 32768+, hitStrength 128,
`reactionAnimVariant == impactEffectId` — i.e. adjacent non-record memory). Per-id field
profile confirms it: id ≤ 8 rows have sane avgHp (28–1059) while the out-of-range ids average
3.5k–57k "hp". The canonical 9-record archetype table (damageRecords.json, DAT_802d46e0) is
impactEffectId = 1 on ALL nine records.

Archetype split (sane ids only): melee-flavored rows (forced-stagger reactionFlags, higher
hitStrength) and shot rows BOTH sit overwhelmingly on id 1; id 0 skews to high-hitStrength
rows; ids 2–7 and 8 appear on specific families' hit rows (per-family flavor, e.g. sword
families' records carrying id 8) — no clean melee/shot partition exists, it is per-hitbox
authoring.

---

## 3. Port wiring (2026-07-04)

**Sim (packages/combat):**
- `gauges.ts DamageRecord` — added the missing `impactEffectId` (u8 +0x09) field (the JSON
  extractions already carried it; the interface didn't).
- `combat.ts applyHit` — writes `victim.lastHitImpactEffectId = record.impactEffectId` and
  `victim.lastHitAttackerTeam` on every connection (renderer-facing, no sim reads).
- `combat.ts stepProjectiles` — writes `pr.lastImpactEffectId = record.impactEffectId`
  alongside `hitConfirmedThisFrame`.
- `types.ts` — the three fields above, documented with the chain.

**Renderer (apps/game):**
- `battleView.ts` — threads both borg fields into `BattleActorView`.
- `battleScene.ts spawnHitFx(position, impactEffectId, attackerTeam)` replaces the generic
  `spawnHitSpark`, and projectile borg-hits (hitConfirmedThisFrame + hit-target despawn) now
  route through it too (hit-terrain keeps the generic efct00 puff — different ROM path).
  Styles per id class: 0 = swelling flash (20f, ×3 growth); 1/fallback = 16–22-particle
  scatter burst (10f, attacker-team tint); 2–7 = flash+core+delayed-ring 3-layer (7/10/13f,
  ring delayed to f3); 8 = star core + anisotropic collapsing cross (10f/6f); 0xff = nothing.

**Label ledger:** DERIVED = the id byte, the gate/suppression (0xff), the spawn chain, layer
counts, lifetimes, keyframe endpoints, the burst count range, and the attacker-team texture
split of id 1. TUNED = which ptcl00/efct00 cell stands in for each texId, tint colors, world
footprint scale, linear approximation of multi-key curves, and burst scatter offsets (the ROM
uses random per-particle velocities).

**Validation:** `pnpm typecheck` ✓, `packages/combat/dist/selfcheck.js` ✓ (new focused assert:
hit connections carry `record.impactEffectId` verbatim incl. the 0xff sentinel + attacker
team), `scripts/run-projectile-tests.mjs` 36/36 ✓ (new assert: projectile hit carries the
record's id), `scripts/selfcheck-1p-challenge.mjs` ✓, `scripts/selfcheck-challenge-stages.mjs` ✓.

**Next steps (if ever needed):** parse ptcl00.ptl/.ref to resolve texId → txg cell + blend
mode (kills the last TUNED hop and would also unlock projectile/trail visuals); locate the
subVariant (+0x12) reader; model the status-FX suppression + the +0x2af throttle.
