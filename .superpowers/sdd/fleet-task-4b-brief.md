# Fleet Task 4B: Cyber Machine constructor cluster

## Scope

Complete the evidence-backed 1:1 state-machine port for constructor `0x800cc454` and all four members:

- `pl0602`
- `pl060a`
- `pl060c`
- `pl060e`

Audit every live action and variant exposed by the constructor, command tables, root dispatcher `FUN_800cc798`, and its subordinate phase tables. Do not assume the current `cyber-machine.ts` implementation is correct: it contains documented simplifications, inferred fields, and potentially incomplete dispatch.

## Authoritative evidence

- GG4E `boot.dol` and Ghidra decompilation/export under `research/decomp/` and `research/tools/OGhidra/analysis_sessions/`
- `packages/combat/src/data/commandMoveTables.json`
- `packages/combat/src/data/actionStreamTables.json`
- Generated fleet coverage artifacts

Wiki prose and behavioral resemblance are supporting context only. Reuse a shared helper only when address identity or the decompiled call graph proves the seam.

## Required work

1. Bank the exact root action table, live/disabled action slots, variant tables, phase tables, constants, and host calls with addresses.
2. Repair `packages/combat/src/families/cyber-machine.ts` so all proven live routes reproduce root dispatch, variant dispatch, phase transitions, actor mutations, stream behavior, resource/ammo behavior, and exit conditions.
3. Surface missing actor/context/host operations only when their semantics are proven. If an essential renderer/model-node or other host behavior cannot be mapped exactly, leave the affected slot `partial` and state the precise blocker.
4. Add exhaustive focused self-checks covering every member/action/variant route plus distinct phase transitions and constants.
5. Update fleet classifications and generated coverage. Promote only independently supportable complete slots; record exact evidence for disabled/delegated slots.
6. Write `.superpowers/sdd/fleet-task-4b-report.md` with changed files, evidence addresses, tests, remaining blockers, and before/after coverage counts.

## Acceptance

- No guessed constants, synthetic timers, placeholder target coordinates, or simplified phase machines are labeled ported.
- `pnpm --filter @gf/combat build`
- `pnpm --filter game typecheck` when bridge/host files change
- focused Cyber Machine self-checks
- `pnpm selfcheck:rom`
- `pnpm audit:family-state-machines`
- `git diff --check`

Do not commit or touch unrelated dirty files or Task 4A review-diff artifacts.
