# Task 4: Make Gotcha-Box settlement transactional

## Context

Gotcha-Box rules live as individual functions in `packages/missions/src/getSystem.ts`; browser persistence is four independent functions in `apps/game/src/sim/getStorage.ts`; `main.ts` owns mutable pool/collection/snapshot facts and must remember begin/win/loss/abandon ordering across seven calls. Battle now exposes coherent `BattleObservation.defeats`. This task must put the whole battle transaction behind one module interface and provide real memory/browser storage adapters.

## Requirements

1. Add a deep settlement module in `@gf/missions` that owns loaded pool/collection state and the complete battle transaction: begin snapshot, win filtering/accrual/drop roll/collection update/commit, loss revert, and abandon revert.
2. The module must reject or safely define invalid ordering (double begin, settle without begin, repeat settle) rather than relying on caller discipline. A win keeps pool progress even if no drop rolls; loss/abandon restore the exact pre-battle pool.
3. Move collected-drop record/timestamp semantics into the domain module. Inject RNG and clock. A single settlement uses one timestamp for its drops.
4. Define a small persistence adapter seam that loads/saves the whole Gotcha-Box state. Provide an in-memory adapter in missions for behavioral tests and a browser localStorage adapter in `getStorage.ts`.
5. Browser persistence must save pool+collection as one versioned state value so the transaction cannot commit only half. Migrate valid legacy `gf-get-pool-v1` / `gf-get-collection-v1` data when no new value exists. Invalid/unavailable storage degrades to a fresh/in-memory session without throwing, matching current behavior.
6. Defeat filtering currently means victim team 1 and killer team 0. Keep that as explicit injected/default team facts in the settlement module, not a hidden `main.ts` loop. Ignore same-team, unattributed, and player-victim defeats.
7. Update `main.ts` to own one settlement module instance and call only begin/win/revert-level behavior. Remove manual pool, collection, snapshot, register/roll/record/save ordering.
8. Export only the deep module/types needed by callers; low-level GET rule functions may remain for research/selfchecks, but production `main.ts` must not compose them.
9. Preserve all behavior and Tasks 1-3; no dependencies or unrelated changes.

## Verification

- Behavioral settlement selfcheck with memory adapter covers: begin+win with qualifying/nonqualifying defeats, no-drop win persistence, loss restore, abandon restore, double begin, settle without begin, repeated settle, stable timestamp, and adapter round-trip isolation.
- Browser adapter validation/migration is covered with an injected Storage-like fake; do not require real `window` in Node.
- Add/use a focused root command if needed, then run it, `rtk proxy pnpm typecheck`, `rtk pnpm selfcheck:1p`, and relevant missions selfcheck.
- Record exact results in `.superpowers/sdd/task-4-report.md`.

## Git/report contract

- Do not switch branch, stage, or commit while shared checkout is externally controlled.
- Use apply_patch; prefix shell with rtk; preserve all unrelated dirt.
- Write `.superpowers/sdd/task-4-report.md` and return status/files/tests/concerns.
