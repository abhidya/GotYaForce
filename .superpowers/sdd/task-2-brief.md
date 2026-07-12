# Task 2: Deepen the Battle interface

## Context

Task 1 introduced a narrow `RomFamilyDriver` and battle-owned `RomBattleRuntime`. The public `Battle` interface still exposes mutable `BattleState` plus `step`; app presentation, camera, results, settlement, scripts, and combat selfchecks navigate or mutate that state directly. The goal is to make Battle's deliberate read interface the caller/test surface while keeping simulation mutation inside `BattleImpl`.

## Requirements

1. Remove mutable `state: BattleState` from the public `Battle` interface. `BattleImpl` may keep private/internal mutable state.
2. Add a small deliberate read interface that supplies the facts callers actually need: fixed-step result, active actor lookup, actor/projectile observations, per-team energy/maxima, timer/winner facts, telemetry/results facts, and recorded defeats. Returned structures must be typed read-only; preserve live projectile identity because the renderer reads despawn metadata after removal.
3. Migrate every non-implementation caller away from `battle.state`, including `apps/game/src/main.ts`, `apps/game/src/sim/presentation.ts`, relevant scripts, and combat selfchecks. Do not leave a public `debugState`, `unsafeState`, or equivalent escape hatch.
4. Tests that need to arrange internal state must use behavior through the Battle interface where feasible. If exact judge setup requires a test seam, keep it package-internal in `battle.ts`, do not re-export it from `@gf/combat`, name it explicitly for selfchecks, and minimize its use.
5. Preserve all current runtime behavior, the Task 1 ROM runtime work, and the renderer's projectile-identity contract.
6. Add behavioral verification for the new read interface: active lookup, energy/result/defeat facts before and after stepping, read-only observation behavior, and current projectile identity behavior.
7. No new dependencies and no unrelated architecture work.

## Design constraints

- Prefer cohesive observation/query concepts over one getter per raw field.
- Read-only TypeScript interfaces must not expose concrete mutable `BattleState` or `BorgRuntime` types as mutable values.
- The interface is the test surface; internal mutable state is implementation.
- Keep strict TypeScript, ESM `.js` suffixes, and existing fixed-step semantics.

## Verification

- Focused Battle/judge/selfcheck runners covering changed tests.
- `rtk proxy pnpm typecheck`.
- `rtk pnpm selfcheck:1p`, `rtk pnpm selfcheck:challenge-stages`, and `rtk pnpm selfcheck:hud`.
- Record exact commands/results in `D:\GotYaForce\.superpowers\sdd\task-2-report.md`.

## Git/report contract

- The shared checkout may still be on an externally controlled branch. Do not switch branches, stage, or commit.
- Modify only Task 2 source/tests and preserve all unrelated dirt.
- Write the full report to `D:\GotYaForce\.superpowers\sdd\task-2-report.md` and return status/test summary/concerns.
