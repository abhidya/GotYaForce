# Notes: ATK-001 / ATK-004 implementation

## Coordination note

Another agent was concurrently editing `packages/combat/src/selfcheck.ts` while this work
was done. To avoid any conflict, this work does **not** touch `selfcheck.ts` at all — it adds
a separate self-test entry point and its own runner script instead of appending to the
existing one. `packages/combat/src/selfcheck.ts` was not read-modified, only referenced for
style conventions (via a Read, not an Edit).

## What was added

- `packages/combat/src/command.ts` — ATK-001. `AttackCommandType` / `AttackCommandSubtype`
  enums, `COMMAND_FAMILY` lookup table, `AttackCommand` interface. Types/constants only, zero
  runtime behavior change.
- `packages/combat/src/movement.ts` — ATK-004. Added `MovementContext` type and the pure
  `movementContextOf(b): MovementContext` helper (no new mutable state beyond a single
  `cooldowns["landedFrames"]` entry, which follows the exact same pattern as the pre-existing
  `dashActive`/`dash` cooldowns and ticks down via the existing generic `stepCooldowns` loop in
  combat.ts — nothing new was added to `stepCooldowns`). `onLand` now also arms
  `cooldowns["landedFrames"] = MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES`.
- `packages/combat/src/constants.ts` — added `MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES = 6`,
  labeled TUNED per the file's header convention (a port-side capture constant with no ROM
  source — the movement-context enum itself is WIKI_TAXONOMY_ONLY per
  `attack-mechanics-findings.md` mechanics D-K).
- `packages/combat/src/index.ts` — exports for all of the above
  (`AttackCommandType`, `AttackCommandSubtype`, `COMMAND_FAMILY`, `AttackCommand`,
  `movementContextOf`, `MovementContext`, `MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES`).
- `packages/combat/src/commandSchema.selftest.ts` — new, standalone self-test covering both
  tickets' "Tests to add" sections: the `COMMAND_FAMILY[1] === "melee"` /
  `COMMAND_FAMILY[5] === "ranged"` table literal tests, enum-value-matches-ROM-number checks,
  and the frame-scripted movement-context sequences (jump: standing -> jump_rise ->
  neutral_air -> landing -> standing; ground dash -> ground_dash; air dash -> air_dash; flyer
  boosting -> flying). Exports `runSelfTest(): number` (0 = pass), matching the style of the
  existing `selfcheck.ts`/`missions/src/selfcheck.ts` self-tests but as a fully separate file.
- `scripts/run-attack-schema-tests.mjs` — new runner, mirrors the existing
  `scripts/selfcheck-challenge-stages.mjs` convention (imports from the built `dist/` output
  after `tsc -b`, calls the exported self-test function, exits with its return code).

## How to run

```
pnpm --filter @gf/combat build   # or: (cd packages/combat && npx tsc -b)
node scripts/run-attack-schema-tests.mjs
```

## Guardrails respected

- No edits to `packages/combat/src/selfcheck.ts`.
- No edits to `PlayerInput`, `stepAttacks`, `actionProfiles` data.
- `BorgRuntime` was only ADDED to conceptually (a new `cooldowns["landedFrames"]` key inside
  the existing `Record<string, number>` cooldowns bag) — no existing `BorgRuntime` field was
  changed, renamed, or removed.
- Every `AttackCommandType`/`AttackCommandSubtype` enum value's doc comment carries either a
  DERIVED_ROM citation or an explicit `BLOCKED:` note per ATK-001's requirement.
