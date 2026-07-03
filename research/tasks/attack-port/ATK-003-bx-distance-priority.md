# ATK-003: B/X distance-priority resolver implementation

**BLOCKED UNTIL**: trace T1 (attack-mechanics-trace-plan.md) delivers the
(button, movement state, distance) → command table AND `FLOAT_8043762c` is dumped via
`research/decomp/dol.py`. Do not start this ticket before those values exist in
behavior-notes.md as a new lettered section.

## Purpose
Replace the static `actionProfile.primary` ordering with the ROM's contextual B/X command
resolution — the biggest player-feel item in the audit.

## Evidence
- Decision pipeline: `FUN_800699d8` @0x800699d8 + testers (chunk_0009.c:220-587);
  ranged-needs-target gate (:412); distance gates FLOAT_8043762c vs +0x694/+0x6a4
  (:497-498, 555-556); execution table +0x4ec (`zz_006a104_` :603-662).
- CONFIRMED_MANUAL (behavior-notes (ao)): the far=fire / close=melee rule is official,
  and the target cursor flips yellow->red at melee range ("battle mode") — the
  threshold is HUD-observable, so T1 calibrates FLOAT_8043762c against the cursor flip.
- CONFIRMED_MANUAL controls the resolver must eventually cover: L AND R both switch
  targets; Z is HOLD-to-lock-partner (not press-cycle); A-while-launched = air
  recovery jump (W14, separate ticket); stick double-tap = evade dash (W15).
- Findings mechanic A/B; ledger `contextual_attack_resolution`.

## Dependencies
ATK-001 (types), ATK-002 (regression net), T1 trace results.

## Files to edit
- new `packages/combat/src/commandResolver.ts`
- `packages/combat/src/combat.ts` (`stepAttacks` consumes a resolved command)
- `packages/combat/src/battle.ts` (pass movement context / target distance)

## Required behavior
- Pure function `resolveAttackCommand(input, borgState, targetInfo): AttackCommand | null`
  implementing the T1-derived table exactly; every branch cites the trace/notebook line.
- Per-borg X overloading (guide-observed, behavior-notes (am)/W12): on flyer borgs X is a
  dive/flight control, not a special attack — the resolver must support a per-borg X
  binding, and T1 must include a flyer X-press script line before this branch is written.
  Also note the observed mid-air X dual-shot variant (air-context ranged, subtype-4
  adjacent) as a T1/T2 capture target.
- `stepAttacks` maps command families to melee/shot/special exactly as today's actions
  (no new attack kinds in this ticket).
- AI callers go through the same resolver (single vocabulary).

## Fallbacks allowed
- Where T1 leaves a cell unmapped, fall back to the CURRENT primary-ordered behavior and
  label the branch `FALLBACK_RECOMMENDED` with a comment. No invented thresholds.

## Tests to add
- Table-driven: each T1-derived (button, context, distance) row → expected command.
- ATK-002's regression cases updated only where the trace PROVES the old behavior wrong
  (note each flip in the test comment with the trace citation).

## Do not change
- Damage formula, gauges, projectile code.
- `actionProfiles.json` data.

## Done when
Resolver passes the table tests; selfcheck green; behavior-notes.md gained the T1 section
this ticket cites.
