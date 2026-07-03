# ATK-006: Passive contact-damage scaffolding — DISABLED by default

## Purpose
Reserve the code path for stomp/contact damage (wiki mechanic L) behind a flag that stays
off, so a future trace can light it up without redesign — and so nobody implements it ad
hoc from the wiki.

## Evidence
- UPGRADED to observed-behavior (still no code evidence): speedrunners deliberately use
  contact hits — big borgs stepping on allies grants those allies hit-invincibility, i.e.
  contact damage is a real hit that triggers the i-frame machinery (behavior-notes (am),
  W10 in wiki-mechanics-queue.md). The scaffold still ships DISABLED; the upgrade means
  the T2 contact-script trace has a concrete scenario (a stepping-capable giant borg vs a
  stationary ally) and is now worth prioritizing.
- Original status: no ROM/asset proof found (findings mechanic L; state handlers were
  read in full in behavior-notes (u) with no movement damage side effects).
- Plausible carrier if real: persistent attack hitbox records (activeEnd = -1 in the attack
  region, hit-bin-format.md) + the rehit-interval mechanism (chunk_0013.c:1175-1182).

## Dependencies
None.

## Files to edit
- `packages/combat/src/constants.ts` (add `CONTACT_DAMAGE = { ENABLED: false } as const`,
  labeled WIKI_TAXONOMY_ONLY with a citation to the findings doc)
- `packages/combat/src/combat.ts` (a `stepContactDamage()` stub that returns immediately
  when disabled; called from battle.ts next to stepAttacks)

## Required behavior
- With the flag false (always, today): zero behavior change, zero per-frame cost beyond one
  boolean check.
- The stub's doc comment states the evidence gap and points at open-questions Q12 and the
  T2 contact-script extension.

## Fallbacks allowed
- The entire feature IS the fallback (disabled).

## Tests to add
- Selfcheck: two borgs overlapping for 120 frames take zero damage with the flag off.

## Do not change
- Do not implement any damage numbers, radii, or cooldowns — not even "reasonable" ones.

## Done when
Stub exists, flag off, overlap test passes, no other output changes.
