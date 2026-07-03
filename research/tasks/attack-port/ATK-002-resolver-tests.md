# ATK-002: Contextual-resolver selection tests with synthetic profiles

## Purpose
Pin the CURRENT B/X selection behavior (primary-ordered melee/shot, charge hold/release,
combo chaining) in deterministic tests BEFORE the resolver is restructured (ATK-003), so
the restructure has a regression net.

## Evidence
- Current behavior to pin: `stepAttacks` order from `actionProfile.primary`
  (packages/combat/src/combat.ts:592-635); charge accumulate/release (:610-633);
  combo window/step (:598-609, :710-726); special AoE (:549-589).

## Dependencies
None (tests of existing code).

## Files to edit
- `packages/combat/src/selfcheck.ts` (follow its existing patterns) or a new
  `packages/combat/src/__tests__/` file if the repo grows a test runner — prefer selfcheck.

## Required behavior
Deterministic cases with synthetic `BorgProfile`s (see selfcheck.ts:891 area for the
synthetic-profile pattern):
1. primary=melee hybrid at any distance: B held → melee starts (state "attack", anim "melee").
2. primary=shot hybrid: B held → shot fires first (ammo decremented, projectile spawned).
3. melee-only (shot=null): B → melee; shot never attempted.
4. shot-only (melee=null): B → shot.
5. chargeable shooter: hold B N frames < tier1 → release fires tier 0; hold ≥ tier2 → tier 2
   (check projectile damage multiplier + damageRecordIndex 2).
6. X pressed → special AoE damages a borg in radius exactly once, sets cooldown.
Each case asserts projectile counts, ammo, cooldowns, state/anim strings.

## Fallbacks allowed
n/a.

## Tests to add
The cases above ARE the deliverable.

## Do not change
Any `src` behavior. If a test reveals a bug, file it in the ticket folder as a note; do not
fix inline.

## Done when
Selfcheck passes with the new cases; each case fails if `stepAttacks`' selection order is
perturbed (verify by temporarily flipping the order locally, then restoring).
