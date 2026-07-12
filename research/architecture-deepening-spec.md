# Spec: Architecture Deepening

## Objective

Implement every candidate in the 2026-07-12 architecture review without changing the browser recreation's observable behavior. The result must concentrate runtime invariants behind smaller interfaces, improve locality and leverage, and make those interfaces the primary test surfaces.

Acceptance criteria:

1. The ROM-family runtime owns its combat integration and floor behavior. No process-global floor implementation remains, the production battle module does not assemble a large callback object and then mutate runtime facts, and two battles can use distinct floor implementations without cross-talk.
2. Callers no longer need unrestricted mutable `BattleState` as Battle's effective interface. Presentation, camera, results, and Gotcha-Box settlement use deliberate Battle queries/snapshots; runtime state mutation remains inside the combat implementation.
3. Screen hosting owns menu-input subscription lifetime. Screen modules expose menu actions as behavior and do not individually subscribe/unsubscribe from the shared input bus. Lifecycle verification executes behavior rather than parsing source with regular expressions.
4. Challenge navigation and battle progression live in a game-session module. The shallow one-caller battle bootstrap is absorbed, transition rules are executable through the session interface, and `main.ts` primarily adapts session effects to rendering/audio/browser modules.
5. Gotcha-Box battle settlement is transactional. Begin, win, loss, and abandon ordering; kill filtering; drop rolls; collection updates; and persistence live behind one module interface with an in-memory adapter for tests and browser-storage adapter for production.
6. All pre-existing tracked and untracked worktree changes are preserved and included in the final commit.
7. The full repository verification passes, the final commit is on `main`, and `origin/main` contains it.

## Tech Stack

- TypeScript 5.6, Node.js 20+, pnpm 9 monorepo
- Vite browser application, Three.js renderer
- Existing framework-free selfchecks and TypeScript project references
- No new runtime or development dependencies

## Commands

- Install state: `rtk pnpm install --frozen-lockfile`
- Typecheck: `rtk pnpm typecheck`
- Build: `rtk pnpm build`
- Combat verification: `rtk pnpm selfcheck:rom` plus every `scripts/run-*-tests.mjs` runner
- Flow verification: `rtk pnpm selfcheck:1p`, `rtk pnpm selfcheck:challenge-stages`, `rtk pnpm selfcheck:menu-flow`, `rtk pnpm selfcheck:hud`
- Atlas verification: `rtk pnpm atlas:build`
- Worktree audit: `rtk git status --short`, `rtk git diff --check`

## Project Structure

- `packages/combat/src/` — Battle and ROM-family runtime implementations
- `packages/core/src/` — generic lifecycle hosting
- `packages/missions/src/` — Challenge and Gotcha-Box rules
- `apps/game/src/sim/` — browser adapters and game-session implementation
- `apps/game/src/ui/` — screens, menu input, and menu-screen hosting
- `scripts/` and colocated `*.selftest.ts` — executable verification
- `research/architecture-deepening-spec.md` — this living specification

## Code Style

Use explicit injected adapters and return facts through narrow interfaces:

```ts
export interface Store<T> {
  load(): T;
  save(value: T): void;
}

export function createModule(dependencies: Dependencies): Module {
  return { execute(input) { return run(input, dependencies); } };
}
```

Keep strict TypeScript settings, ESM `.js` import suffixes, existing formatting, descriptive domain names, and no speculative seams with only one adapter.

## Testing Strategy

- Add focused behavioral selfchecks for each new or deepened interface.
- Verify two independent ROM runtimes do not share floor behavior.
- Verify Battle queries return stable read-only facts and callers do not mutate runtime state.
- Verify host mount/replacement/clear dispatches input only to the current screen and releases resources exactly once.
- Verify every allowed session transition, battle startup failure recovery, win/loss completion, and Gotcha-Box win/revert transaction.
- Run the existing full typecheck, build, selfcheck, combat runner, and atlas build suite before committing.

## Boundaries

- Always: preserve current gameplay and research behavior; preserve all existing worktree changes; use deep-module vocabulary; keep adapters injectable; run verification before commit and push.
- Ask first: adding dependencies, deleting research evidence, changing generated asset formats, or force-pushing history. None are planned.
- Never: discard user changes, use destructive Git commands, commit secrets or disc assets, weaken tests to make a refactor pass, or leave `main` ahead of `origin/main` after completion.

## Success Criteria

- All seven acceptance criteria above have direct source and test evidence.
- `rtk git diff --check`, typecheck, build, every relevant selfcheck/test runner, and atlas build exit zero.
- One final commit contains the complete dirty worktree plus architecture changes.
- `git rev-parse main` equals `git rev-parse origin/main` after push.

## Open Questions

None. The user explicitly approved all review candidates, all existing worktree changes, direct work on `main`, and pushing to `origin/main`.

## Implementation Tasks

- [x] Task 1: Deepen the ROM-family runtime and remove process-global floor state.
  - Acceptance: Battle supplies one cohesive runtime dependency; family physics uses battle-local floor behavior; two runtime instances cannot overwrite one another; existing G RED work remains intact.
  - Verify: focused ROM selfcheck proves independent floor behavior, then `rtk pnpm selfcheck:rom`.
  - Files: `packages/combat/src/bridge.ts`, `packages/combat/src/battle.ts`, `packages/combat/src/rom/physics.ts`, relevant ROM selfcheck/types.
- [x] Task 2: Deepen Battle's interface and migrate state-reading callers.
  - Acceptance: deliberate read-only Battle queries/snapshots cover presentation, camera, results, and settlement facts; callers do not rely on unrestricted mutable state; `step` remains the mutation entry.
  - Verify: focused Battle selfcheck plus typecheck, 1P, HUD, and combat runners.
  - Files: `packages/combat/src/types.ts`, `packages/combat/src/battle.ts`, `apps/game/src/sim/presentation.ts`, `apps/game/src/main.ts`, focused tests.
- [x] Task 3: Make screen hosting own menu-input lifetime.
  - Acceptance: screen modules no longer subscribe/unsubscribe individually; host/router dispatches only to the current screen/overlay and releases it exactly once; flow verification is behavioral.
  - Verify: executable menu-host selfcheck and `rtk pnpm selfcheck:menu-flow`.
  - Files: `packages/core/src/index.ts`, `apps/game/src/ui/menuInput.ts`, screen modules, `apps/game/src/main.ts`, flow selfcheck.
- [x] Task 4: Deepen Challenge session/navigation and absorb battle bootstrap.
  - Acceptance: transition rules and battle preparation are executable through one game-session interface; one-caller `battleBootstrap.ts` is removed; `main.ts` adapts effects rather than owning transition validity.
  - Verify: session transition selfcheck, 1P selfcheck, challenge-stage selfcheck, typecheck.
  - Files: `apps/game/src/sim/gameSession.ts`, `apps/game/src/main.ts`, `apps/game/src/sim/battleBootstrap.ts`, focused tests.
- [x] Task 5: Make Gotcha-Box settlement transactional.
  - Acceptance: begin/win/loss/abandon transactions, defeat filtering, drops, collection, and persistence sit behind one interface with browser and memory adapters.
  - Verify: transaction selfcheck covers commit/revert/storage failure and the existing missions selfcheck.
  - Files: `packages/missions/src/getSystem.ts`, `apps/game/src/sim/getStorage.ts`, new settlement module, `apps/game/src/main.ts`, focused tests.
