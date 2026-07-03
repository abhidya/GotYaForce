# ATK-019: Healing & lifesteal shells (REWRITTEN after behavior-notes (an) correction)

> **Correction notice (2026-07-03):** the first version of this ticket misread the
> chunk_0003.c:6318 HP-increment as Nurse healing. Guide-corpus decoding ((an) §2)
> proves the gated ids 0x702/0x70a are VAMPIRE KNIGHT (pl0702) and VLAD (pl070a) —
> that path is vampire LIFESTEAL. Nurse healing is a separate targeted X-attack.
> This ticket now ships two small shells.

## Purpose
Model the two ROM healing-adjacent mechanisms with honest confidence labels:
(A) vampire lifesteal + passive drain (corpus-evidenced increment, guide-evidenced
drain), (B) nurse targeted heal (guide-evidenced amounts, no code path found yet).

## Evidence
- (A) Lifesteal increment: chunk_0003.c:6318-6323 — ids 0x702/0x70a →
  `hp += (&DAT_803b0638)[slot*2]`, clamp to max (behavior-notes (al), corrected (an) §2).
  The accumulator's writers (what fills it — dealt melee damage per the guide) remain
  untraced. Passive drain ~2-3 HP/sec (guide-observed; drain loop unfound in corpus —
  OPEN, re-grep with the vampire path as anchor).
- (A2) Companion mechanic, NOT this ticket: :6237 ids 0x701/0x708 = Demon/Akuma
  Samurai sword growth — do not conflate.
- (B) Nurse heal: X attack dashes to target and heals a FIXED amount — Death Borg
  Theta 37 (0x906), Angel Nurse 50 (pl0900), Angel Rescue 100 (pl0908), Nao (pl090d,
  can heal ally or enemy; blocked while target's heal animation runs) — all
  OBSERVED_GUIDE ((an) §2, guide-anchors-movelist.json). No ROM code path isolated.

## Dependencies
None. Coordinate with ATK-010 (status shell) only to avoid combat.ts collisions.

## Files to edit
- `packages/combat/src/combat.ts` (`applyHeal(b, amount)` helper: clamp to maxHp,
  no-op on dead; a disabled `stepVampireDrain` stub)
- `packages/combat/src/constants.ts` (`HEAL = { NURSE_ENABLED: false,
  VAMPIRE_ENABLED: false }` with (an) citations; nurse amounts recorded as
  OBSERVED_GUIDE constants 37/50/100 — data, not active behavior)
- `packages/combat/src/stats.ts` or a small data map (vampire ids pl0702/pl070a;
  nurse ids pl0900/pl0908/pl090d/pl0d?? — Theta's roster id must be looked up by
  name, expect family 09 variant 06)

## Required behavior
- Both flags false: zero behavior change.
- `applyHeal` clamps, never revives, returns actual amount healed.
- No lifesteal rate, drain rate, or heal cooldowns invented — amounts present only as
  labeled OBSERVED_GUIDE constants awaiting trace T8/T10-style verification.

## Fallbacks allowed
- Disabled defaults are the ticket.

## Tests to add
- applyHeal clamp/no-revive/return value.
- Both-flags-off battle regression (identical outcomes).
- Roster check: the six ids above resolve in borgs.json with the expected names
  (log names; STOP and file a note on mismatch).

## Do not change
- applyHit/damageFormula (healing never flows through them); the :6237 sword-growth
  ids stay out of scope.

## Done when
Shells + tests green; NOTES-ATK-019.md records the roster name verification.
