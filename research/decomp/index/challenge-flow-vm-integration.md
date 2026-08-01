# Challenge Flow VM — Integration Spec

How `apps/game/src/gameSession.ts` should drive the ROM-faithful Challenge state machine in
`apps/game/src/ui/intro/challengeFlowVm.ts` instead of the current HLE
`difficulty → players → load-box → select-force → briefing` path.

## TL;DR

`createChallengeFlowVm(sink)` is a 1:1 port of `dispatch_challenge_flow_state` @0x80195f2c
and its 8-entry mode table `PTR_FUN_8036f560`. It owns the Challenge state machine
(init → menu poll → box load → battle build → in-battle → clear/fail → exit). `gameSession.ts`
keeps its `screen`/`dispatch` reducer shape but, on the Challenge path, delegates per-frame
progress and the win/loss/advance decision to `vm.tick()` via a `ChallengeFlowEffectSink`
that bridges to `@gf/missions` (roster/cost data), the combat runtime (`Battle`), and the
renderer/audio. **gameSession is NOT edited by this port** — the changes below are the spec
for a follow-up wiring PR.

## ROM mode table (faithful, dumped from boot.dol)

| mode | ROM address    | handler                        | VM state after handler                       |
| ---- | -------------- | ------------------------------ | -------------------------------------------- |
| 0    | `0x80195fbc`   | `init_challenge_flow_state`    | clears work/save blocks → mode 1             |
| 1    | `0x80196030`   | `poll_challenge_menu_selection`| confirm → mode 3; cursor → mode 2; cancel → mode 7 |
| 2    | `0x80196188`   | box/force preview load         | on ready → mode 1                            |
| 3    | `0x801962c4`   | `build_challenge_battle_setup` | builds slot/team tables → mode 4 (sub 0)     |
| 4    | `0x8019688c`   | in-battle (sub-dispatch)       | sub 0 scene-wait → sub 1 run → sub 2 judge   |
| 5    | `0x80196a9c`   | clear/victory screen           | on dismiss → mode 7                          |
| 6    | `0x80196cec`   | fail/defeat screen             | on dismiss → mode 7                          |
| 7    | `0x80196d64`   | exit → physical menu           | one-shot teardown                            |

Mode 4 sub-table `PTR_FUN_8036f580`: sub 0 `0x801968cc` (scene-wait), sub 1 `0x80196948`
(battle run), sub 2 `0x801969a0` (post-battle gate). Post-battle advances only when
`(winMask & 1<<humanSide) && winMask <= 2`; otherwise → mode 6. Battle counter increments
on each win; `next < battleTotal` → rebuild (mode 3) for the next battle, else → mode 5.

`battleTotal` = `DAT_804356d0[difficulty]` = **5 / 10 / 15** (Normal / Tuff / Insane).
Start force energy `DAT_8036f554` = **1500 / 2000 / 2500**. Timer is frozen
(`work[0x48]=work[0x4c]=18000`, `work[0x50]=1`): Challenge battles cannot time out.

## Sink ↔ host bridges

Implement one `ChallengeFlowEffectSink` per active Challenge run. Each method cites the ROM
call it replaces and the existing host module that satisfies it:

| Sink method              | ROM call                        | Host bridge                                                                 |
| ------------------------ | ------------------------------- | --------------------------------------------------------------------------- |
| `onEnterChallenge`       | `zz_002a5f4_`                   | audio/scene stinger (renderer)                                              |
| `onChallengeWorkInit`    | `zz_0196f3c_` + `zz_0006b74_`   | seed `ChallengeRun` defaults                                                |
| `pollMenuResult`         | `zz_018f56c_`                   | input layer: cursor move (`0x8000\|idx`), confirm (`>0`), cancel (`<0`)     |
| `onMenuOpened`           | save-block cursor write         | no-op / cursor SFX                                                          |
| `buildBoxPreview`        | `PTR_DAT_80435a30` build        | `SelectForce`/`ForceBuilder` preview render                                 |
| `isBoxPreviewReady`      | `zz_01ba750_`                   | asset-load gate                                                             |
| `spawnBattleSetup`       | `zz_0029fd4_`/`zz_000685c_`/`zz_00064d4_` | build `MissionBattleConfig` from `ChallengeBattleSetup` + player force → `createBattle` |
| `isBattleSceneReady`     | `zz_000a3c4_`                   | stage asset-load gate (`loadStageAssets`)                                   |
| `stepBattleFrame`        | `zz_0028264_`                   | `Battle.step(...)` one fixed frame                                          |
| `isBattleEnded`          | `*PTR_DAT_80433930 == 1`        | `Battle` finished flag                                                      |
| `getWinnerMask`          | `PTR_DAT_80433934[0x1f]`        | `BattleResults.outcome` → bit0 side0 win / bit1 side1 win                   |
| `rerollStage`            | `zz_0196dac_`                   | `selectChallengeStage` (`@gf/missions/challenge-reference`) + 11-entry pool |
| `loadBattleScene`        | `zz_0042454_`/`zz_0042690_`/`zz_00437b0_` | `stageIdForBattleConfig` + `loadStageAssets`                      |
| `drawBorgFromPool`       | `zz_0196eb8_` (`PTR_DAT_80380804`) | `CHALLENGE_GROUP_ROSTERS` (`@gf/missions/challenge-reference`)           |
| `borgCost`               | `zz_0066168_`                   | `forceEnergy` (`@gf/combat/stats`)                                          |
| `showResultsScreen`      | `zz_01f5ae0_`                   | `Results` screen (mode = difficulty for clear, 3 for fail)                  |
| `isResultsDismissed`     | `zz_01f5b68_`                   | `Results` advance input                                                     |
| `exitToMenu`             | `0x80196d64`                    | `dispatch({type:"battle-abandoned"})`-equivalent → `menu` screen            |

### Roster generation reconciliation

`build_challenge_battle_setup` rolls CPU rosters itself (count cap from
`CHALLENGE_ALLY_COUNT_BY_BATTLE`/`ENEMY_COUNT_BY_BATTLE`, budget cap with
`floor(cost*2/3)`). The existing `@gf/missions` `ChallengeRun` ALSO generates rosters from
`challenge-reference.ts`. On integration, **the VM's `ChallengeBattleSetup.slots` is
authoritative**: `spawnBattleSetup` consumes it directly and must NOT re-roll. The
`@gf/missions` roster/cost helpers are reused only through `drawBorgFromPool`/`borgCost` so
the VM's budget gating stays source-owned. `ChallengeRun`'s `next()/getCurrentBattle()`
flow is superseded by the VM's battle counter + post-battle gate.

## gameSession wiring (follow-up PR — no edits in this port)

1. **Enter Challenge from the physical menu** (`menu-select { mode: "challenge" }`):
   construct `vm = createChallengeFlowVm(sink, { controllerMask, menu: { difficulty } })`.
   `controllerMask` = `0x01` for 1P, `0x03` for 2P (slot bits). Drive the difficulty/box
   selection UI into `vm.state.menu.difficulty` / `.boxIndex`. Then `screen = "difficulty"`
   is replaced by a single Challenge screen that calls `vm.tick()` each fixed frame.

2. **Per frame on the Challenge screen**: `vm.tick()`. Map `vm.state.mode` to effects:
   - `MENU_POLL` / `BOX_LOAD` → render the menu/force UI from `vm.state.menu`.
   - `BATTLE_BUILD` → on the `spawnBattleSetup` sink callback, build the `Battle` and flip
     to the battle screen (replaces `briefing` + `prepareBattle`).
   - `IN_BATTLE` → `stepBattleFrame` drives the existing battle loop; `getWinnerMask` +
     the post-battle sub replaces `battle-resolved` + `advance`.
   - `CLEAR` / `FAIL` → `Results` screen (`showResultsScreen` mode distinguishes them).
   - `EXIT` → `exitToMenu` returns to `"menu"` (replaces the HLE `back`/`battle-abandoned`).

3. **Drop the HLE intermediate screens** (`players`, `load-box`) on the Challenge path:
   the ROM has no equivalent — `controllerMask` and the box index come straight from the
   menu/force UI. Versus/mission modes are unaffected.

4. **Battle count / progression**: `vm.state.battleTotal` (5/10/15) and `vm.state.battleIndex`
   replace `ChallengeRun.current/total`. A full clear (mode 5) is the win; mode 6 is the loss.

## Boundaries / honest gaps

- **`0x80196d64` (mode 7) is not emitted by Ghidra** as a standalone fn; confirmed only as
  the exit handler (behavior-notes.md ae). Ported as the `exitToMenu` boundary — no invented
  teardown logic.
- **Roster borg-id draw** delegates to `drawBorgFromPool` because `PTR_DAT_80380804` (the
  per-group borg-id lists consumed by `zz_0196eb8_`) is a deep combat-runtime table not yet
  dumped; `@gf/missions` `CHALLENGE_GROUP_ROSTERS` is the verified equivalent.
- **RNG** (`zz_00055fc_`) for the pool-index low bits uses `Math.random`; the budget/count
  gating around it is ported verbatim. Swap for the seeded PRNG when the combat runtime
  exposes one.
- **`Math.floor(cost*2/3)`** is the reduced form of Ghidra's sign-adjusted decomposition of
  `zz_0066168_` cost charging (chunk_0048.c:351).
