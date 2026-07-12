# Task 5: Deepen Challenge session/navigation

## Context

`main.ts` still owns a mutable `flow` object plus `showTitleIntro`, `showMenu`, `showDifficulty`, `showPlayers`, `showLoadBoxData`, `showSelectForce`, `showForceBuilder`, `startRun`, `showBattleIntro`, `showResults`, `showGets`, and `advanceRun`. Transition rules live in screen callbacks. `apps/game/src/sim/battleBootstrap.ts` is a shallow one-caller module whose option/result interfaces are nearly as complex as its implementation. Tasks 1-4 provide deep Battle, menu-screen host, and Gotcha-Box interfaces for the new session module to consume.

## Requirements

1. Add an app-owned `gameSession.ts` deep module that owns all Challenge flow state: current screen, difficulty budget, player count, selected force slot/slots, force-editor return target, Challenge run/progression, pending battle config, and post-battle drops/results routing.
2. Expose one event-dispatch interface plus a read-only session snapshot and async battle preparation through the same module. Transition validity, back paths, run creation/advance/complete/loss, and results→Gets routing are implementation details. Invalid events for the current screen must reject clearly or produce an explicit no-op—never silently corrupt state.
3. Return a small set of declarative effects/facts for `main.ts` to adapt (render screen, prepare/start battle, recover from preparation failure). Do not move DOM, Three.js, audio playback, fixed-step simulation, or browser globals into the session module.
4. Replace the `showX` callback chain and global `flow` object in `main.ts` with one session event adapter/render switch. Screen callbacks may play their immediate SFX, then dispatch an event; they must not encode the next valid screen themselves.
5. Absorb stage selection, asset loading, default bounds, mission→combat translation, Battle creation, and local-player-id calculation from `battleBootstrap.ts` into the game-session implementation. Delete `battleBootstrap.ts`; no shallow replacement module with the same interface.
6. Battle preparation failures must leave the session in/recover it to Select Force and remain retryable. Integration with Task 4's guarded Gotcha-Box initialization must preserve begin-after-bootstrap and revert-on-post-begin-error.
7. Keep battle runtime state (`BattleSession`, HUD, camera, scene, fixed-step loop) in `main.ts`; the Challenge session owns navigation/progression, not simulation implementation.
8. Preserve all existing observable menu/back/edit/run/results/Gets behavior, Tasks 1-4, and unrelated dirt. No dependencies.

## Interface depth target

- Prefer `dispatch(event) -> effects`, `snapshot()`, and `prepareBattle()` over many `showX` methods.
- Inject the few facts that truly vary: force catalog operations, Challenge-run creation, stage catalog/assets, borg stats. Production and focused fake adapters justify those seams.
- `main.ts` should have one rendering/effect interpreter rather than a transition function per screen.

## Verification

- Add an executable Node selfcheck that transpiles/executes the real session module with fakes as needed.
- Cover every forward/back transition, menu force-edit return, force slot selection/update, run creation, briefing back/confirm, preparation success/default bounds/failure retry, win with/without drops, loss, run completion, Results→Gets→next battle, and invalid-event handling.
- Add a simple static guard that `main.ts` no longer defines the global `flow` object or `showX` transition cluster and no longer imports `battleBootstrap`; verify the file is deleted.
- Run focused session check, menu-flow, 1P, challenge-stages, HUD, settlement, `rtk proxy pnpm typecheck`, and scoped diff-check.
- Record exact results in `.superpowers/sdd/task-5-report.md`.

## Git/report contract

- Do not switch branch, stage, or commit while the external checkout controller is active.
- Use apply_patch; prefix commands with rtk; preserve all unrelated dirt.
- Write `.superpowers/sdd/task-5-report.md`; return concise status/files/tests/concerns.
