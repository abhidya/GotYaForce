# ATK-015: Debug overlay fields for attack-mechanics verification

## Purpose
Expose the audit's runtime fields in the game's debug overlay so trace sessions (T1-T10)
and future tickets can eyeball sim state against Dolphin side-by-side.

## Evidence
- Fields chosen = the trace plan's log list (attack-mechanics-trace-plan.md): state, gauges,
  combo, invincibility, ammo cells, burst, status, movement context.

## Dependencies
Fields that don't exist yet degrade gracefully: show them only if present (works before or
after ATK-004/009/010/011 land).

## Files to edit
- `apps/game/src/ui/` debug overlay component (locate the existing debug/HUD readout used
  by battleScene; follow its pattern)
- `apps/game/src/sim/battleScene.ts` only if a plumbing hook is missing

## Required behavior
Per selected borg, render: state + stateTime, balanceGauge/max, downGauge/base,
comboAccum/comboRank + comboWindow, invincTimer, ammo (weapon cells if present, else the
single pool + reload cooldown), burstArmFrames/burstActive (if present), statusId/timer
(if present), movementContext (if present), last damage dealt/taken (add two small
`lastDamageDealt/Taken` fields updated in applyHit — display-only).

## Fallbacks allowed
- Missing fields hidden; no layout polish required.

## Tests to add
- None (display-only), but the overlay must not affect sim determinism — verify a selfcheck
  battle hash is unchanged with the overlay on.

## Do not change
- Any packages/combat sim logic except the two display-only lastDamage fields.

## Done when
Overlay shows the fields live in a versus battle; sim output unchanged.
