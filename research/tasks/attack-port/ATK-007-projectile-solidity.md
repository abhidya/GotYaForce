# ATK-007: Projectile solidity / projectile-vs-projectile interaction

**BLOCKED UNTIL**: trace T5 or the PTR_FUN_802da740 per-type dispatch read (open-questions
Q6) produces a real solidity signal. Wiki behavior must NOT be coded as final from
taxonomy alone.

## Purpose
Implement solid/nonsolid projectile interaction (wiki mechanic M/N) once — and only once —
a ROM/trace source for per-projectile solidity exists.

## Evidence
- Wiki (taxonomy): solids (missiles/drills) destructible by melee/solids/nonsolids;
  nonsolids pass through nonsolids.
- Corpus negative: no proj-vs-proj logic in the generic collision passes
  (collision_hit_pair_pass_* @0x8002da88/0x8002db58, chunk_0003.c:7031-7223); per-type
  dispatch (PTR_FUN_802da740, chunk_0013.c:1172) unread.
- Do NOT use projectileVisualFamilies.json as a solidity source (visual-only, behavior-notes (t)).

## Dependencies
T5 / Q6 evidence; ATK-008 (consumption refactor) strongly recommended first.

## Files to edit
- `packages/combat/src/types.ts` (`Projectile.solidity?: "solid" | "nonsolid"`)
- `packages/combat/src/combat.ts` (`stepProjectiles` pairwise pass)
- `packages/combat/src/actionProfiles.ts`/generator (per-move solidity once sourced)

## Required behavior
(write only after evidence) Interaction matrix from the evidence, with the decision table
recorded in the ticket PR and behavior-notes.

## Fallbacks allowed
- Until evidence: nothing ships. If a debug toggle is wanted for experimentation, it must
  default off and be labeled WIKI_TAXONOMY_ONLY.

## Tests to add
- Test vectors (pre-written, will be enabled with the feature):
  - nonsolid A vs nonsolid B head-on → both survive, cross paths.
  - solid vs nonsolid head-on → solid destroyed (and/or nonsolid consumed, per evidence).
  - solid vs solid → both destroyed.
  - melee swing overlapping a solid projectile → projectile destroyed, swing continues.

## Do not change
- Borg hit resolution, damage records, homing.

## Done when
Evidence exists AND the matrix tests pass against it; behavior-notes gains the citation.
