# Acceleration Ninja action-2 dash motion

This bounded browser-game change restores scalar displacement during Acceleration
Ninja (`pl0004`) action 2. It does not establish complete Ninja or original-game parity.

## Observable change

The family already set its dash speed to three times the descriptor maximum, but
left its physics calls as comments. During subsequent ROM-owned frames the battle
skips generic movement, so that speed did not move the actor. Entry and ongoing
action-2 frames now integrate position; recovery integrates after its stream-authored
speed reset. No other family or shared legacy integrator behavior changes.

## Source evidence and scope

- `research/decomp/ghidra-export/chunk_0042.c:730-844`: action-2 setup seeds speed
  and invokes its first approach frame inline. The approach handler ticks the stream,
  copies heading to lock yaw, assigns dash speed, integrates, then probes the ground.
- `chunk_0042.c:847-889`: recovery ticks the stream, handles positive dash strength
  by clearing horizontal speed/deceleration, then integrates.
- `research/decomp/ghidra-export/chunk_0008.c:3787-3828`: `FUN_80067310` orders
  position integration, floor snap, horizontal decay/floor, gravity, and lower-only
  vertical clamp. Upper horizontal/vertical limits belong to `zz_0067458_` instead.
- `packages/combat/src/bridge.ts`: X entry invokes phase 0, then `tick` advances
  the retained phase and `syncOut` publishes position. `battle.ts` skips generic
  movement on owned frames. Its entry frame still performs generic movement before
  attack dispatch; original entry timing remains unverified.

`integratePhysicsPrimary` composes the existing shared arithmetic with the lower-only
clamp. Ground snapping still uses the existing host abstraction. Original trig-table
and floating-point equivalence, aiming, collision probes, exit redirects, and Ninja
actions 0/3 remain partial. This change does not invent ground-probe results or
promote family audit classifications.

## Repeatable validation

Run `node scripts/run-rom-tests.mjs` and `pnpm exec tsc -b packages/combat`.

The focused regressions cover:
- exactly one entry, ongoing, and recovery displacement at yaw 0 and quarter-turn;
- stream speed reset before recovery displacement;
- ground callback timing before decay/gravity;
- populated upper limits not capping the primary helper, with lower floors retained;
- actual bridge X entry and an owned ongoing frame publishing position changes.

Removing only the two action-2 integrator calls makes the motion regression tests
fail, including both bridge displacement assertions. The close-distance transition
fixture now follows the moving actor so it still tests the intended distance gate.

State-table, G RED bridge, and Ninja bridge checks run inside `runSelfTest`, after
its failure-counter reset and before its return-code check. A bridge-only negative
control (one intentionally false displacement assertion, with family code unchanged)
produces exactly one failure and exit code 1. Restoring it returns the suite to exit 0.

## Browser check (not yet performed)

Select Acceleration Ninja and trigger the action-2 X dash on a flat, open stage.
Verify it visibly travels through subsequent frames instead of staying stationary,
then check recovery and stage-edge behavior. Record any targeting, collision, or
exit mismatch separately: these remain known partial areas, not verified parity.
