# Fleet Task 2: Complete shared Robot-family machines

Finish, verify, and classify the shared Robot action-0 and action-1 engines already introduced from OGhidra evidence.

## Scope

- Shared action 0: `zz_00f1e30_` / `0x800f1e30`, phase table `0x8031b8a0`, configs in `shared-robot-dash.ts`.
- Shared action 1: `zz_00f2374_` / `FUN_800f2498`, implemented by `melee-robot.ts`.
- Action 0 live members: pl0400, pl0401, pl0402, pl0403, pl0404, pl0405, pl0407, pl0408, pl0409, pl040a, pl040b, pl040c, pl040d. pl0406 has no live action-0 leaf and must not be wrapped.
- Action 1 live members: pl0400 through pl040b except pl040c/pl040d; preserve the existing ROM-derived member set.
- Do not alter bespoke action-2 machines in this task.

## Requirements

- Verify exact constructor/root/action/config/phase addresses and constants against GG4E `boot.dol` and Ghidra exports before changing code.
- Audit all distinct action-0 config callbacks and every live member/variant, not only the sample pl0407/pl040b cases.
- Audit shared melee’s target/no-target speed source, timer, phase transitions, stream slots, deceleration clear, and far-distance helper behavior.
- Fix any discrepancy found. Do not rewrite correct behavior for style.
- Add focused selfchecks proving bridge routing and the distinct callback/config/transition families. Tests must exercise real handlers.
- Add reviewed manifest entries only for constructor/action slots whose every live member and variant meets all seven evidence dimensions. Use the fleet audit schema exactly.
- Regenerate coverage artifacts. Default audit must pass; strict should continue to fail only for the remaining fleet gaps.
- Run `pnpm --filter @gf/combat build`, focused tests, `pnpm selfcheck:rom`, and the default fleet audit.
- Preserve all concurrent architecture/deepening edits and unrelated docs changes. Touch only Robot family/bridge/selfcheck files when evidence requires it, the reviewed manifest/generated coverage, and Task 2 reporting artifacts.

## Global constraints

- ROM/decomp evidence is authoritative; no guessed constants or behavior.
- Ported requires root, variants/members, phases, constants, stream behavior, bridge, and focused tests.
- Preserve generic fallback for anything outside the proven live member set.

## Workspace/report

- Work in `D:/GotYaForce` on `codex/state-machine-fleet`.
- The tree is concurrently dirty. Do not stage or commit; controller will commit file-scoped changes.
- Prefix shell commands with `rtk`; use `apply_patch` for edits.
- Report to `D:/GotYaForce/.superpowers/sdd/fleet-task-2-report.md`.
