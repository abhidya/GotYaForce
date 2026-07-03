# ATK-008: Projectile consumption refactor (persist + rehit interval)

**BLOCKED UNTIL (for per-move values)**: T6 trace or the Q10 flag sweep identifies which
moves persist. The MECHANISM below is ROM-evidenced and may be built now with today's
consume-on-first-hit as the universal default.

## Purpose
Restructure `stepProjectiles` so consumption is a per-projectile policy instead of a
hard-coded `break`, matching the ROM's structure (persistence is the default; despawn is
type-gated; re-hits are interval-paced).

## Evidence
- Rehit: damage record s8+0x16 reloads per-OBJECT counter object+0x4e; interval 0 =
  unlimited rehit (chunk_0013.c:1175-1182) (corpus read, audit).
- Despawn: object+0x10=2 is actor-gated, not collision-coded (chunk_0013.c:1188).
- Collision gate flagsB 0x4000/0x2000 (chunk_0003.c:7080) — semantics unsettled; do not
  wire these bits yet.
- DamageRecord already carries `rehitIntervalFrames` in the port (gauges.ts:53-55, unused).

## Dependencies
ATK-002 (regression net). Independent of ATK-007.

## Files to edit
- `packages/combat/src/types.ts` (`Projectile.consumeOnHit?: boolean` default true;
  `Projectile.rehitCounter?: number`)
- `packages/combat/src/combat.ts` (`stepProjectiles`)

## Required behavior
- Default path unchanged: `consumeOnHit !== false` → first valid hit consumes (today's
  behavior, bit-for-bit; ATK-002 cases must stay green).
- When `consumeOnHit === false`: projectile persists; each victim can be re-hit only when
  the rehit counter (reloaded from `record.rehitIntervalFrames`) expires — mirror the ROM's
  single per-object counter, NOT a per-target map (chunk_0013.c evidence above).
- No caller sets `consumeOnHit: false` yet — that flip is T6's outcome.

## Fallbacks allowed
- Universal consume-on-first-hit default (labeled FALLBACK_RECOMMENDED).

## Tests to add
- Default projectile: consumed on first hit (existing behavior).
- Synthetic persist projectile with interval 0: hits 2 lined-up borgs in one flight,
  each once per frame contact.
- Synthetic persist projectile with interval 10: same target re-hit exactly every 10 frames
  while overlapping.

## Do not change
- Damage formula, knockback, homing, projectileInPlayArea.

## Done when
All three vector tests pass; ATK-002 regression green; no gameplay caller flips the flag.
