# ATK-001: Attack-command data schema (types only)

## Purpose
Give the port the ROM's command vocabulary (type/subtype) as TypeScript types so the
resolver (ATK-003), AI, and tests share one contract. Unlocks ATK-002/003/004 without
touching gameplay behavior.

## Evidence
- Command struct actor+0x4b0 (+0/+1 buttons, +4 command) → actor+0x660/+0x661/+0x591:
  chunk_0007.c:23 (`FUN_800562b8`), chunk_0009.c:978-980 (`zz_006a8c0_` @0x8006a8c0).
- Command types {1,2,3,5} set at actor+0x585 by testers under `FUN_800699d8` @0x800699d8
  (chunk_0009.c:220+); subtype 0-5 at +0x586 (chunk_0009.c:500-587).
- Dispatch families: +0x591 == 1/2 melee, 4/5/6 ranged (`FUN_8005d494`, chunk_0007.c:4750-4782).
- Full context: `research/decomp/attack-mechanics-findings.md` mechanic A;
  `research/decomp/data/attack-profile-port-schema.json#inputBindings`.

## Dependencies
None.

## Files to edit
- `packages/combat/src/types.ts` (add types; do NOT change PlayerInput semantics yet)
- new `packages/combat/src/command.ts` (types + constants only)

## Required behavior
- Add `AttackCommandType` (numeric enum mirroring ROM values 0-7; document 1/2 = melee
  family, 3 = unmapped, 4/5/6 = ranged family per dispatch, 7 = unmapped) and
  `AttackCommandSubtype` (0-5, meanings documented as UNMAPPED except 4 = air/elevated
  per chunk_0009.c:500-534 — cite, don't invent).
- Add `AttackCommand { type: AttackCommandType; subtype: AttackCommandSubtype }`.
- Every doc comment carries the evidence citation and a `BLOCKED:` note for unmapped values.
- No runtime code paths change. Export from `index.ts`.

## Fallbacks allowed
None needed — this is schema only.

## Tests to add
- Type-level/`selfcheck.ts` addition: constants exist, enum values match the ROM numbers
  (a table literal test, e.g. `COMMAND_FAMILY[1] === "melee"`, `COMMAND_FAMILY[5] === "ranged"`).

## Do not change
- `PlayerInput` fields, `stepAttacks` logic, `actionProfiles` — behavior is untouched.
- Do not assign button meanings to command values (that is ATK-003, blocked on trace T1).

## Done when
`pnpm typecheck` (or the scratch-tsc fallback in HANDOFF-PROMPT.md) passes; new types are
exported; no gameplay test output changes.
