# Task 2 report: Deepen the Battle interface

## Status

Implemented. `Battle.state` is no longer public; `BattleImpl` owns private mutable state.
Callers now consume a deep-readonly `BattleObservation`, `activeActor`/`actor` identity
queries, and the observation returned by each fixed step. Live actor/projectile objects retain
identity, including projectile despawn metadata after removal. Exact mutation arrangements use
`battleStateForSelfcheck`, defined only in `battle.ts` and not re-exported by `@gf/combat`.

## Source and test changes

- Added `DeepReadonly`, `BattleActorObservation`, `BattleProjectileObservation`, and
  `BattleObservation`; changed `Battle.step` to return the post-step observation.
- Migrated game presentation, camera, scene, HUD debug overlay, combat selfchecks, and all
  challenge scripts away from `battle.state`.
- Extended `battleJudge.selftest.ts` with active/uid lookup, pre/post energy-result-defeat,
  compile-time readonly, fixed-step return, and projectile identity/despawn checks.
- Preserved Task 1's battle-owned `RomBattleRuntime` work and unrelated checkout changes.

## Verification (exact commands/results)

- `rtk proxy pnpm typecheck` — PASS (exit 0).
- `rtk test node scripts/run-judge-tests.mjs` — PASS, 23/23 checks.
- `rtk test node scripts/run-burst-tests.mjs` — PASS, 70/70 checks.
- `rtk pnpm selfcheck:1p` — PASS; stage `st00`, first energy change frame 551, result ongoing at smoke limit.
- `rtk pnpm selfcheck:challenge-stages` — PASS; 11 base stages and `st2c`/`st4c` family variants.
- `rtk pnpm selfcheck:hud` — PASS, static/parse-level HUD checks.
- `rtk git diff --check` — PASS (no output).

## Minor review cleanup

Corrected the public type documentation: actors are structured per-boundary snapshots whose
identity is stable only within the cached observation, while projectile elements alone retain
live simulation identity across boundaries.

- `rtk pnpm selfcheck:challenge-stages` — PASS; 11 base stages, `st2c`/`st4c` family variants,
  and 18-name arena coverage.
- `rtk test node packages/combat/dist/selfcheck.js` — FAIL in an unrelated existing Task 1
  expectation: `assertGRedChargeStreamUnresolvedKeepsFallback` expects the G RED B-charge leaf
  to be unresolved, but the current shared checkout resolves it to group 4/slot 1. The failure
  occurs before Battle-interface-specific full-suite coverage and was not changed because it is
  outside Task 2.

## Concerns

The full legacy combat selfcheck has the Task 1 G RED expectation mismatch above. All focused
Battle/judge/burst checks and every verification command required by the Task 2 brief pass.

## Review follow-up: fixed-step snapshot consistency

`BattleImpl.observe()` now caches a stable observation per fixed-step boundary. Actor facts and
all aggregate containers/records are cloned; projectile arrays are copied while projectile
elements deliberately retain sim identity. `activeActor` and `actor` query that same cached
actor snapshot. The judge coverage now captures a pre-step observation and verifies its energy,
energy maximum, defeats/counts, and actor HP/alive facts remain unchanged after a lethal step;
the existing projectile removal/despawn identity assertion remains green.

Follow-up verification (exact commands/results):

- `rtk proxy pnpm typecheck` — PASS (exit 0).
- `rtk test node scripts/run-judge-tests.mjs` — PASS, 31/31 checks.
- `rtk test node scripts/run-burst-tests.mjs` — PASS, 70/70 checks.
- `rtk pnpm selfcheck:1p` — PASS; stage `st00`, first energy change frame 551, result ongoing at smoke limit.
- `rtk pnpm selfcheck:hud` — PASS, static/parse-level HUD checks.
- `rtk git diff --check` — PASS (no output).
