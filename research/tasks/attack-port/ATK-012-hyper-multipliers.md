# ATK-012: Hyper/Power Burst effects (multipliers, meter, duration)

**BLOCKED UNTIL**: trace T3 delivers (a) the meter field + fill rule, (b) burst duration /
what clears +0x6fc, and (c) the speed channel (open-questions Q4/Q5). The damage and reload
effects below are already DERIVED and may be wired as soon as a duration source exists.

## Purpose
Make Power Burst real: meter, activation gate, duration, and the three proven effects.

## Evidence
- Damage: +0x6fc → outgoing x2.0 / incoming x0.5 (zz_003cd5c_ steps 3/10, behavior-notes
  (ah), chunk_0004.c:6705-6707/6761-6763). The port's computeSourceDamage ALREADY has
  `attackerPairAttack`/`defenderPairAttack` params implementing exactly these scalars
  (damageFormula.ts:97,114) — wire, do not duplicate.
- Reload: refill rate x FLOAT_804376c8 under +0x6fc (zz_006dcc0_, chunk_0009.c:2923-2927);
  dump the float via dol.py before wiring.
- Activation chain + pair sync: ATK-011 evidence; paired path zz_005b678_ (species table
  0x802d352c) and heading sync chunk_0007.c:3192-3198.
- Meter/duration/speed: UNKNOWN (corpus negatives; findings mechanic S).

## Dependencies
ATK-011 (shell), ATK-009 (refill model, for the reload boost), T3 trace.

## Files to edit
- `packages/combat/src/combat.ts` / `burst.ts` (meter fill from damage events per T3;
  duration countdown; clear)
- `packages/combat/src/battle.ts` (pass burst flags into damage context:
  `attackerPairAttack: attacker.burstActive`, `defenderPairAttack: victim.burstActive`)
- `packages/combat/src/constants.ts` (BURST block: DERIVED multipliers cited; T3-derived
  meter/duration constants cited)

## Required behavior
- Damage: exclusively via the existing pairAttack params. NEVER add a second x2/x0.5.
- Reload: multiply ATK-009's refill rate by the dumped FLOAT_804376c8 while burstActive.
- Meter/duration: exactly the T3-derived rule, cited to the new behavior-notes section.
- Speed: only if T3/Q5 finds the channel; otherwise leave a labeled BLOCKED note — do not
  approximate "massive speed" from the wiki.

## Fallbacks allowed
- None for numbers. If T3 yields duration but not meter, ship duration with a debug-only
  "meter always full" flag labeled BLOCKED, default off.

## Tests to add
- HIT-TIME evaluation (guide-observed, behavior-notes (am)/W13): a projectile FIRED before
  burst activation whose hit lands DURING burst gets the 2x bonus — i.e. the multiplier
  reads the attacker's burstActive at applyHit time, not at spawn time. (The current
  damage-context wiring already behaves this way if you pass the live attacker reference;
  the test pins it.)
- Burst attacker vs normal: damage exactly 2x the non-burst baseline (formula-level test).
- Burst defender: incoming exactly 0.5x.
- Both: 1x net (2 * 0.5) — matches formula composition.
- Refill: gradual borg refills FLOAT_804376c8-times faster under burst.
- Duration: burst clears after the T3-derived frame count.

## Do not change
- comboRankScale, same-team scalar, type matrix (they compose in the formula already).

## Done when
T3 section exists in behavior-notes; all tests pass; tuned-burndown gains no new TUNED
markers (everything cited).
