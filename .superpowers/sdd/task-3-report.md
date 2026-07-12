# Task 3 report: Deepen screen hosting

## Status

Implemented. The app-owned `createMenuScreenHost` now composes generic core screen lifetime with one shared menu-input subscription, routes to the current screen/top overlay, preserves underlying HUD content for overlays, and guards all host-owned teardown paths for exact-once release.

All 11 screen handles expose `handleMenuInput(event)`. Screen modules no longer import, call, or clean up `subscribeMenuInput`; SelectForce retains `dir` metadata and TitleIntro retains its raw any-key listener while accepting host-routed gamepad input.

`main.ts` uses the deep host for standard screens, Results/Gets, and PauseMenu overlay lifetime. Direct Results/Gets/PauseMenu teardown coordination was removed.

## Files changed

- `apps/game/src/main.ts`
- `apps/game/src/ui/index.ts`
- `apps/game/src/ui/menuInput.ts`
- `apps/game/src/ui/menuScreenHost.ts` (new)
- `apps/game/src/ui/screens/BattleIntro.ts`
- `apps/game/src/ui/screens/ForceBuilder.ts`
- `apps/game/src/ui/screens/Gets.ts`
- `apps/game/src/ui/screens/LoadBoxData.ts`
- `apps/game/src/ui/screens/MainMenu.ts`
- `apps/game/src/ui/screens/PauseMenu.ts`
- `apps/game/src/ui/screens/Results.ts`
- `apps/game/src/ui/screens/SelectDifficulty.ts`
- `apps/game/src/ui/screens/SelectForce.ts`
- `apps/game/src/ui/screens/SelectPlayers.ts`
- `apps/game/src/ui/screens/TitleIntro.ts`
- `scripts/selfcheck-menu-flow.mjs`
- `.superpowers/sdd/task-3-report.md`

## Verification

- `rtk pnpm selfcheck:menu-flow` — PASS: 11 targets; delivery/current/top routing, replacement, clear, overlay fall-through, exact-once teardown.
- `rtk proxy pnpm typecheck` — PASS immediately after the Task 3 implementation (`tsc -b tsconfig.json apps/game/tsconfig.json`, exit 0). Final fresh rerun later failed only in concurrently edited unrelated Task 1/2 combat files: `packages/combat/src/families/melee-robot.ts:121,138` (`range` possibly undefined) and `packages/combat/src/rom/rom.selfcheck.ts:60` (unused `ROBOT_MELEE_RANGE_ROWS`).
- `rtk pnpm selfcheck:1p` — PASS: stage `st00`, triangles `1989`, first energy change frame `551`, result ongoing, final energy `{"0":1250,"1":1810}`.
- Coverage follow-up: `rtk pnpm selfcheck:menu-flow` — PASS after adding exact-once active-overlay release cases for standard replacement and `clear()`, plus Results/Gets `screenHost.set(handle)` wiring assertions.

## Concerns

- No browser E2E was run. The new selfcheck executes the real TypeScript host/core implementations in memory with an injected input source and fake DOM root; static checks remain only for screen wiring and TitleIntro's intentional raw-key listener.
- The shared checkout already contained unrelated Task 1/2 and other dirty changes, including overlapping `main.ts` edits; they were preserved and were not staged or committed.
- Concurrent unrelated combat edits made the final repository-wide typecheck non-green after an earlier clean Task 3 typecheck; those files were left untouched.
