# ATK-013: Resistance/falloff — pin-down tests + "do not implement" guard

## Purpose
The audit's highest-risk finding is a NON-task: the wiki's hidden per-target damage
resistance IS the already-ported combo-rank falloff (`comboRankScale_802c7ca0`). This
ticket adds tests that pin the existing behavior and a code comment that stops future
agents from adding a duplicate layer. NO new mechanic.

## Evidence
- ROM: `dmg *= DAT_802c7ca0[victim+0x6ca]` = [1.0, 0.8, 0.5, 0.25, 0.1, 0.05, 0.02, ...]
  unless record flagsB & 0x4000 (zz_003cd5c_ step 16, behavior-notes (ah),
  chunk_0004.c:6804-6806); accumulator/rank chunk_0003.c:8021-8030; 60-frame window reset
  chunk_0006.c:8009-8010.
- Port: damageFormula.ts:130-132 (falloff), combat.ts:306-311 (accum/rank),
  combat.ts:371-378 (window reset).
- Verdict + risk: findings mechanic U; ledger `resistance_falloff`.

## Dependencies
None.

## Files to edit
- `packages/combat/src/damageFormula.ts` (comment block above the falloff line naming the
  wiki mechanic and forbidding a second layer, citing the findings doc)
- `packages/combat/src/selfcheck.ts` (tests)

## Required behavior
Tests only:
1. Same victim hit repeatedly fast enough to roll the accumulator: damage sequence follows
   the extracted table ratios exactly (compare computeSourceDamage outputs at comboRank
   0,1,2,3).
2. flagsB & 0x4000 record: falloff skipped (damage independent of comboRank).
3. 60 frames without a hit (stepGaugeWindows) → comboAccum/comboRank reset → damage back
   to full.

## Fallbacks allowed
n/a.

## Do not change
- ANY damage numbers or the falloff table. If a test fails, the port has a real bug —
  report it in the ticket folder, do not "fix" the table.

## Done when
Three tests pass against current code; the guard comment is in place.
