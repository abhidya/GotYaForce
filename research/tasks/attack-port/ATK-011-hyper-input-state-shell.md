# ATK-011: Hyper/Power Burst input + state shell

## Purpose
Add the Y input and the burst state fields (arm window, active flag) with the ROM's
activation SHAPE, without any gameplay effects (those are ATK-012, blocked on trace T3).

## Evidence
- Arm gate: `FUN_80069814` chunk_0009.c:104-115 — Y-family bit in transformed word +0x5d4
  sets +0x6fb = 6 (6-frame arm window) (corpus read, audit).
- Consume: `zz_005b2b8_` @0x8005b2b8 chunk_0007.c:3354-3494 — +0x6fb non-zero + active borg
  → +0x6fc = 1, +0x6fa = 1; per-frame +0x6fb decrement (:3473-3490).
- Findings mechanic S; schema `attack-profile-port-schema.json#hyperModifiers`.

## Dependencies
None (ATK-012 depends on this).

## Files to edit
- `packages/combat/src/types.ts` (`PlayerInput.hyper: boolean`; BorgRuntime:
  `burstArmFrames: number`, `burstActive: boolean`, `burstPaired: boolean`)
- `packages/combat/src/battle.ts` (plumb input; edge-latch like switchLockHeld)
- `packages/combat/src/combat.ts` or new `burst.ts` (`stepBurst`: arm window set to 6 on
  press edge, decrement per frame, activate when armed — mirroring the two-stage ROM shape)

## Required behavior
- Y press edge → `burstArmFrames = 6` (DERIVED value, cite chunk_0009.c:113).
- While `burstArmFrames > 0` and borg active → `burstActive = true` (activation
  precondition beyond "armed" is UNKNOWN — no meter exists yet; gate activation behind a
  new `BURST.ENABLED = false` constant so the shell is inert in real battles until ATK-012).
- `burstActive` has ZERO effects in this ticket.
- `emptyInput()` gains `hyper: false`; all existing input constructors updated.

## Fallbacks allowed
- `BURST.ENABLED = false` default (labeled BLOCKED-until-T3).

## Tests to add
- Press edge arms exactly 6 frames; window decrements; re-press re-arms.
- With ENABLED=true (test-only), activation sets burstActive.
- With ENABLED=false, full battle produces identical results to before (regression).

## Do not change
- damageFormula (ATK-012 wires it), ammo refill, movement.

## Done when
Shell tests pass; default battles byte-identical; PlayerInput change compiles across
apps/game + packages.
