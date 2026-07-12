# Task 3: Deepen screen hosting

## Context

`packages/core/src/index.ts` owns screen mount/destroy/root lifetime, but all 11 screen modules independently call `subscribeMenuInput` and unsubscribe during `destroy`. `scripts/selfcheck-menu-flow.mjs` only regex-parses source and explicitly does not execute delivery or lifecycle behavior. Standard screens use `screenHost`; PauseMenu is an overlay mounted directly during battle. Task 3 must make one host/router own input lifetime for both standard screens and overlays.

## Requirements

1. Screen modules must expose menu-action behavior on their returned handles and must not import/call `subscribeMenuInput` or own unsubscribe cleanup. Preserve each screen's current action semantics, including SelectForce direction metadata and TitleIntro's legitimate raw any-key listener.
2. Add one deep menu-screen host module that composes DOM screen lifetime with the shared menu-input bus. It must subscribe once, route actions only to the current top handle, own standard screen replacement/clear, and support a PauseMenu-style overlay without deleting the underlying HUD/root content.
3. Host cleanup must be idempotent. Replacement, clear, overlay close, and host destroy must release each handle exactly once. With no active target, input must be ignored or fall through safely.
4. Update `main.ts` to use the deep host for standard screens, Results/Gets handles, and PauseMenu overlay. `main.ts` must not manually coordinate input subscription lifetime.
5. Replace the source-regex menu-flow check with executable behavioral verification of bus delivery, current/top routing, replacement, clear, overlay priority/fall-through, and exact-once teardown. Static checks may remain only for the TitleIntro raw-listener exception or simple wiring not executable in Node.
6. Keep core generic: `packages/core` must not import app menu-input types. The app-owned menu-screen host is the seam between generic screen lifetime and the menu bus.
7. Preserve existing UI behavior, Task 1/2 work, and all unrelated dirt. No dependencies.

## Suggested shape (not mandatory if a deeper equivalent is found)

- A shared `MenuInputTarget` handle interface with `handleMenuInput(event): void`.
- An app-owned `createMenuScreenHost(root, inputBus)` that composes `createScreenHost`, maintains an overlay stack, and owns its single bus subscription.
- Dependency injection for the input subscription/dispatch source so Node selfchecks can execute without browser globals.

## Verification

- New executable menu-screen host selfcheck exercises all lifecycle cases above.
- `rtk pnpm selfcheck:menu-flow` must execute behavior and pass.
- `rtk proxy pnpm typecheck` and `rtk pnpm selfcheck:1p`.
- Record exact results in `.superpowers/sdd/task-3-report.md`.

## Git/report contract

- Do not switch branches, stage, or commit while shared checkout ownership is external.
- Use apply_patch; prefix all shell commands with rtk.
- Write `.superpowers/sdd/task-3-report.md` and return status/changed files/tests/concerns.
