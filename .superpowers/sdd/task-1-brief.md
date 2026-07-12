# Task 1: Deepen the ROM-family runtime

## Context

The combat package currently exposes a shallow `RomHostContext` seam with roughly twenty optional callbacks. `BattleImpl` is its only production adapter, constructs many callbacks in `deployNext`, and then mutates `hitResolver`, `groundClamp`, `bounds`, and `offMeshCheck`. `rom/physics.ts` also stores a process-global floor implementation overwritten during deployment. The dirty worktree already contains intentional G RED dash changes in `bridge.ts`, `families/gred.ts`, `families/gred-dash.ts`, and `rom.selfcheck.ts`; preserve them exactly while integrating this task.

## Requirements

1. Replace the callback-heavy production setup with one cohesive battle-owned runtime dependency/interface. Hide mutable runtime configuration behind construction/attachment rather than post-attach public mutation.
2. Remove the process-global ground-clamp registration from `rom/physics.ts`. Physics/family execution must use the floor behavior belonging to its own battle/runtime.
3. Prevent concrete `RomDriverBridge` implementation details from leaking through the public `BorgRuntime` shape where practical without breaking the family runtime.
4. Preserve all current combat behavior and every pre-existing dirty G RED change.
5. Add behavioral selfcheck coverage that creates two independent runtime instances with different floor behavior and proves there is no cross-talk.
6. Do not add dependencies or touch unrelated docs/app modules.

## Design constraints

- Prefer a small runtime dependency object representing battle-owned facts over a menu of optional callbacks.
- Internal family callbacks may remain internal implementation details; they must not be the production Battle seam.
- The interface is the test surface. Existing direct bridge selfchecks may remain for decoded family behavior, but new integration coverage must exercise the deepened construction seam.
- Keep strict TypeScript and ESM `.js` import suffixes.

## Verification

- Run the focused ROM selfcheck and `rtk pnpm selfcheck:rom`.
- Run `rtk proxy pnpm typecheck` if the filtered `rtk pnpm typecheck` reports its known false nonzero status while saying no errors.
- Record exact commands and results in the report.

## Git/report contract

- Work in `D:\GotYaForce` on the explicitly authorized `main` branch.
- Stage and commit only Task 1 files. Existing dirty hunks in overlapping Task 1 files are intentional and must be included; leave unrelated dirt untouched.
- Commit subject: `Deepen ROM family runtime`.
- Write the full report to `D:\GotYaForce\.superpowers\sdd\task-1-report.md`.
