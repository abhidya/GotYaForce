# Task 4 report: transactional Gotcha-Box settlement

## Status

Implemented and verified.

The `@gf/missions` settlement module now owns loaded pool/collection state, begin/win/revert
ordering, defeat filtering, accrual, drop rolling, stable collection timestamps, and whole-state
commits. Invalid ordering throws defined errors. Win commits pool progress even without a drop;
loss/abandon restore the exact begin snapshot.

Browser persistence now uses one versioned `gf-gotcha-box-v1` value containing pool and
collection. It validates current data, migrates valid legacy pool/collection keys only when the
new key is absent, and keeps an in-memory session when storage is absent or throws.

Production `main.ts` owns one settlement instance and only calls `begin`, `win`, and `revert`.

## Files

- `packages/missions/src/gotchaBoxSettlement.ts` — deep settlement module, state/persistence
  seam, and isolated in-memory adapter.
- `packages/missions/src/gotchaBoxSettlement.selfcheck.ts` — behavioral transaction selfcheck.
- `packages/missions/src/index.ts` — settlement interface exports.
- `apps/game/src/sim/getStorage.ts` — versioned atomic browser adapter and legacy migration.
- `apps/game/src/main.ts` — begin/win/revert-only production wiring.
- `scripts/selfcheck-get-storage.mjs` — browser-free fake-Storage validation/migration checks.
- `package.json` — focused `selfcheck:get-settlement` command.

## Verification

- `rtk pnpm selfcheck:get-settlement` — PASS (exit 0). Missions build passed; settlement
  lifecycle/filtering/commit/revert/timestamp/isolation checks passed; browser
  validation/migration/fallback/atomic-write checks passed.
- `rtk proxy pnpm typecheck` — PASS (exit 0).
- `rtk pnpm selfcheck:1p` — PASS (exit 0): stage `st00`, first energy change frame 551,
  final energy `{0:1250,1:1810}`.
- Scoped `rtk git diff --check -- ...` including the initialization helper and every Task 4
  implementation/selfcheck/report file — PASS (exit 0, no output).
- Scoped `rtk git diff --check -- ...` over all Task 4 implementation, selfcheck, command and
  report files — PASS (exit 0, no output).
- `rtk proxy node packages/missions/dist/selfcheck.js` — PASS (exit 0): Challenge reference
  audit and seeded GET-system end-to-end audit passed; 59/70 Adventure stages resolve all
  enemies with only `Random` unresolved.

## Concerns / coordination

- No known functional gaps or added dependencies.
- The shared checkout's external controller created commits `8bcbc94e` (module/storage/index)
  and `ce20f299` (`main.ts` wiring) during implementation. I did not switch branches, stage, or
  commit. The remaining task-specific test/validator changes are visible in the working tree.

## Review follow-up

All Task 4 review findings were addressed:

- `gotchaBox.begin()` now runs only after `createBattleBootstrap` resolves and before `session`
  makes the battle active. The focused selfcheck asserts this ordering, so a rejected bootstrap
  cannot strand an active settlement transaction.
- Browser collection validation now accepts only canonical unit records (`partIndex === 0`, no
  `partsCount`) or consistent parts records (`partsCount` integer > 1 and `partIndex` integer in
  `1..partsCount`). Malformed current and legacy unit/parts cases degrade to fresh state, and
  malformed legacy values are not migrated.
- Domain behavior now covers injected nondefault player/victim team facts.
- Browser migration now covers both pool-only and collection-only legacy state.

Fresh post-review verification:

- `rtk pnpm selfcheck:get-settlement` — PASS (exit 0). Missions build passed; settlement output
  reports lifecycle, default/injected-team filtering, commits/reverts, timestamp and adapter
  isolation; browser output reports bootstrap ordering, strict validation, migration, fallback
  and atomic write.
- `rtk proxy pnpm typecheck` — PASS (exit 0).
- `rtk pnpm selfcheck:1p` — PASS (exit 0): stage `st00`, first energy change frame 551,
  final energy `{0:1250,1:1810}`.

## Final review follow-up

- Added `initializeGotchaBoxBattle`, an executable lifecycle helper used by `enterBattle`.
  Bootstrap runs before settlement begins. After a successful begin, the complete remaining
  initialization callback (including async work) is guarded; any failure reverts once and then
  rethrows the original error to the existing caller recovery path.
- Focused executable checks prove bootstrap rejection does not begin/revert and an asynchronous
  post-begin initialization rejection performs exactly one begin and one revert while preserving
  the original rejection.
- Browser collection validation now constrains `partsCount` to the real 2–5 range. Impossible
  values 6 and 999 are checked as malformed in both current and legacy state and degrade fresh.

Fresh final verification:

- `rtk pnpm selfcheck:get-settlement` — PASS (exit 0). Missions build passed; domain settlement
  checks passed; browser output reports initialization cleanup, strict validation, migration,
  fallback, and atomic write.
- `rtk proxy pnpm typecheck` — PASS (exit 0).
- `rtk pnpm selfcheck:1p` — PASS (exit 0): stage `st00`, first energy change frame 551,
  final energy `{0:1250,1:1810}`.
