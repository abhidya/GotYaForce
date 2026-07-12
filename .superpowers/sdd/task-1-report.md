# Task 1 report: Deepen the ROM-family runtime

## Status

**DONE_WITH_CONCERNS** — implementation and verification are complete; Git staging and commit are intentionally deferred because another task changed the shared worktree branch.

Implemented the battle-owned ROM-family runtime seam. `BattleImpl` now constructs one `RomBattleRuntime` containing floor, resource, projectile, and hit-resolution behavior and attaches drivers through that cohesive dependency. `deployNext` no longer assembles a callback menu or mutates bridge configuration after attachment.

ROM physics now reads floor behavior from the individual `RomActor`'s attached physics runtime. The process-global clamp and registration function were removed, so drivers belonging to separate battles cannot overwrite each other's floor behavior.

`BorgRuntime.romDriver` now exposes the narrow `RomFamilyDriver` interface rather than the concrete `RomDriverBridge` class. Existing direct bridge selfchecks remain available for decoded family behavior.

## Files changed

- `packages/combat/src/battle.ts` — owns and supplies one cohesive runtime dependency.
- `packages/combat/src/bridge.ts` — adds the production construction seam and hides runtime configuration.
- `packages/combat/src/rom/actor.ts` — carries battle-local physics behavior per actor.
- `packages/combat/src/rom/physics.ts` — removes process-global floor state.
- `packages/combat/src/types.ts` — narrows the public ROM driver shape.
- `packages/combat/src/rom/rom.selfcheck.ts` — proves two attached runtimes retain distinct floors without cross-talk.
- `packages/combat/src/families/shared-aerial-dive-x.ts` — updates the stale global-registration comment.
- Pre-existing G RED work in `bridge.ts`, `families/gred.ts`, `families/gred-dash.ts`, and `rom.selfcheck.ts` was preserved.

## Verification

- `rtk pnpm typecheck` — reported the known filtered false nonzero status while saying `TypeScript: No errors found`.
- `rtk proxy pnpm typecheck` — exited 0.
- `rtk pnpm --filter @gf/combat build` — exited 0.
- `rtk node scripts/run-rom-tests.mjs` — exited 0; the focused ROM selfcheck included three independent-floor assertions and ended `ALL PASS`.
- `rtk pnpm selfcheck:rom` — exited 0 and ended `ALL PASS`.
- `rtk git diff --check` — exited 0.

## Concerns

- At the commit gate the shared worktree branch had been changed concurrently from the authorized `main` branch to `codex/state-machine-fleet`. No branch switch or commit was attempted while that conflict remained; commit status is reported separately after coordination.
- Unrelated dirty docs, research, and `rom/PORTING.md` changes were left untouched.
