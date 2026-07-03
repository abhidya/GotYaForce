# ATK-014: Friendly-fire regression tests

## Purpose
Friendly fire is already ROM-correct in the formula and reachable in the sim loops, but has
zero test coverage — a silent regression (e.g. someone "fixing" melee to skip teammates)
would be invisible. Pin it.

## Evidence
- ROM: same team && !(flagsA & 0x1000) → x0.25 (FLOAT_80437024); (flagsA & 0x1000) &&
  victim+0x59c & 0x1000 → /40; floor at 1 (zz_003cd5c_ step 18, behavior-notes (ah)/(o),
  chunk_0004.c:6811-6821).
- Port: damageFormula.ts:133-138; teammates hittable via canReceiveHit (combat.ts:118-120)
  in melee (:655) and special (:560) loops; projectiles hit any non-owner (:903).
- No ROM OHKO path exists (findings mechanic V — CHECKED_CLOSED); do not test for one.

## Dependencies
None.

## Files to edit
- `packages/combat/src/selfcheck.ts`

## Required behavior
Tests:
1. Formula-level: identical hit context, enemy vs teammate victim → teammate damage is
   exactly 0.25x (subject to the floor(1) and int truncation — compute expected through
   computeSourceDamage itself with team swapped).
2. Synthetic record with flagsA = 0x1000: teammate damage NOT reduced (exemption channel).
3. Sim-level: two same-team borgs, one melee swing connecting → teammate takes damage > 0
   (teammates are hittable) and less than the enemy-case damage.
4. Projectile same-team: teammate hit consumes the projectile and applies reduced damage.
5. blockDivisorActive + flagsA 0x1000 → damage divided by 40 (formula-level; no sim caller
   yet — assert the formula path works so future guard wiring has coverage).

## Fallbacks allowed
n/a.

## Do not change
- The 0.25/40 scalars, the team filters in lock-on (isEnemyAlive is CORRECT to exclude
  teammates from targeting — only hit resolution includes them).

## Done when
Five tests pass against current code; any failure is filed as a bug note, not patched
silently.
