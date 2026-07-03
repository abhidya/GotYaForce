# Notes: ATK-015 implementation

## Coordination note

Other agents may be concurrently editing `packages/combat/src/types.ts` and
`packages/combat/src/combat.ts` (ATK-004/009/010/011 and friends touch `BorgRuntime` and
`applyHit`). Per the ticket's own coordination instruction, this pass **does not touch either
file**. The ticket allows adding two display-only `lastDamageDealt`/`lastDamageTaken` fields
(updated in `applyHit`) — that part is **deferred**, not implemented, specifically to avoid
conflicting with concurrent edits to `types.ts`/`combat.ts`.

## What was added

- `apps/game/src/ui/hud/DebugOverlay.ts` — new. `createDebugOverlay(container)` returns a
  `DebugOverlayHandle` (`update(borg)`, `setVisible(v)`, `visible`, `destroy()`). Renders a
  single absolutely-positioned monospace `<pre>` overlay, hidden by default. Follows the
  existing `apps/game/src/ui/hud/BattleHud.ts` pattern (a `create*(container)` factory
  returning an `update`/`destroy` handle) but is intentionally much simpler — no SVG, no
  bitmap font, plain `textContent` — per the ticket's "no layout polish required" fallback.
- `apps/game/src/ui/index.ts` — barrel-exports `createDebugOverlay` / `DebugOverlayHandle`.
- `apps/game/src/main.ts` — mounts the overlay once at startup (`createDebugOverlay(ui)`),
  gates initial visibility on `?debugOverlay=1` (mirrors the existing `?debugBattle`/
  `?debugRender` URL-param convention just above it), toggles it with the backquote/backtick
  key (`Backquote`) in the existing `keydown` handler, and calls `debugOverlay.update(...)`
  from the render loop `tick()` — only while `flow.screen === "battle"`, reading the focused
  borg via the existing read-only `localFocusBorg()` accessor (same one `updateHud()` and
  `followCamera()` already use).

## Fields rendered

Per `BorgRuntime` fields that exist today: `state` + `stateTime`, `balanceGauge`/
`balanceGaugeMax`, `downGauge`/`downGaugeBase`, `comboAccum`/`comboRank` + `comboWindow`,
`invincTimer`, `ammo` + `cooldowns["reload"]` (the single-pool + reload cooldown model
`combat.ts` currently uses — confirmed no `weaponCells` field exists on `BorgRuntime` yet).

Fields other tickets will add (`weaponCells`, `burstArmFrames`, `burstActive`, `statusId`,
`statusTimer`, `movementContext`) are feature-detected with `in` checks against a loosely-typed
`FutureBorgFields` view, so the overlay compiles and simply omits a line for each field before
its ticket lands, and picks it up automatically once it does. Confirmed via grep that none of
these exist on `BorgRuntime`/`packages/combat/src/types.ts` as of this pass.

## Deferred (do not forget)

- `lastDamageDealt` / `lastDamageTaken` on `BorgRuntime`, updated in `applyHit`
  (`packages/combat/src/combat.ts`) — ticket explicitly allows this, but it's skipped here to
  avoid touching `types.ts`/`combat.ts` while other agents may be mid-edit on the same files.
  The overlay already has an `if ("lastDamageDealt" in b || "lastDamageTaken" in b)` block
  ready to light up the moment those two fields exist — no further overlay changes needed once
  a future pass adds them.

## How it's toggled

- URL: `?debugOverlay=1` (shows it from battle start).
- Keyboard: press the backquote/backtick key (`` ` ``) at any time to toggle.

## Determinism guardrail

`DebugOverlay.update()` only reads `BorgRuntime`/`cooldowns` fields and builds display strings;
it never assigns into `battle.state`, `BorgRuntime`, or any sim structure. `main.ts` wiring
calls it after `battleScene.update`/`followCamera`/`updateBattleDebugDataset` in the render
loop `tick()`, never from the fixed-step sim loop (`startFixedStepLoop`), so it cannot affect
sim stepping order or timing either.

## Verification performed

- Static: `pnpm typecheck` (`tsc -b tsconfig.json apps/game/tsconfig.json`) — passed, exit
  code 0, no errors.
- Read-through of `apps/game/src/sim/presentation.ts` (`battlePresentationState`/`focusBorg`)
  confirmed `localFocusBorg()` (used to feed the overlay) is itself read-only over
  `battle.state`.
- Did not run a live dev-server visual check in this pass (static verification + careful read
  only) — `pnpm --filter game dev` was not exercised.
