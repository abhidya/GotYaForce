# ATK-005: Melee-context profile mapping (schema + generator plumbing only)

**BLOCKED UNTIL (for real values)**: trace T2 delivers context → (command,subtype) →
(animation bank, hitbox remap slot) tuples, OR the +0x4ec action-table format is decoded
(open-questions Q3). Until then this ticket is schema/plumbing only.

## Purpose
Extend the action-profile shape so each borg can carry per-context melee entries once T2
provides them, without another schema migration later.

## Evidence
- Containers exist: group-1 attack banks (5-23 per borg, borg-animation-banks.md), 64
  frame-windowed attack hitbox records + remap B (hit-bin-format.md; zz_008ac80_ @0x8008ac80).
- No context axis exists in assets (findings mechanic D-K — CONFIRMED_ASSET negative), so
  entries default to null.

## Dependencies
ATK-001 (command types), ATK-004 (MovementContext).

## Files to edit
- `packages/combat/src/actionProfiles.ts` (optional `meleeByContext?: Partial<Record<MovementContext, MeleeActionDef>>` on `BorgActionProfile`, resolved to `null`s today)
- `scripts/gen-combat-action-profiles.mjs` (emit the empty field + provenance note)
- `packages/combat/src/data/actionProfiles.json` (regenerated)

## Required behavior
- Profiles gain the per-context slot; resolution falls back to the existing single `melee`
  def for every context (today's behavior, bit-for-bit).
- The generator comments/provenance say exactly what evidence will fill each slot (T2).

## Fallbacks allowed
- Everything falls back to the current single melee def — that IS the ticket.

## Tests to add
- Selfcheck: a profile with no context entries behaves identically to before (reuse ATK-002
  cases); a synthetic profile WITH a context entry is selected only when
  `movementContextOf(b)` matches.

## Do not change
- Damage records, hitbox radii, combo constants.

## Done when
Regenerated JSON is byte-stable except the new empty field; selfcheck green; synthetic
context-selection test passes.
