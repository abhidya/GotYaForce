// Browser adapter for local controls and exported-stage availability.

import type { CombatStageCatalog } from "@gf/missions";
import type { PlayerInput } from "@gf/combat";
import {
  DEFAULT_ARENA_STAGE,
  EXPORTED_STAGE_CATALOG,
  EXPORTED_STAGE_IDS,
  isExportedStageId,
  stageCatalogEntry,
} from "../stages/catalog.generated.js";

export { DEFAULT_ARENA_STAGE, EXPORTED_STAGE_CATALOG, EXPORTED_STAGE_IDS, isExportedStageId };

export const EXPORTED_STAGE_CATALOG_ADAPTER: CombatStageCatalog = {
  defaultStageId: DEFAULT_ARENA_STAGE,
  hasStageCollision(stageId: string): boolean {
    const entry = stageCatalogEntry(stageId);
    return !!entry && entry.collisionCount > 0;
  },
};

/** Local input snapshot accumulated from the keyboard/gamepad each frame. */
export interface LocalControls {
  moveX: number;
  moveZ: number;
  jump: boolean;
  attack: boolean;
  special: boolean;
  lockOn: boolean;
  switchLock: boolean;
  allyLock: boolean;
  switchBorg: boolean;
  dash: boolean;
}

/**
 * Build a combat PlayerInput from the live key set (KeyboardEvent.code values)
 * plus an optional gamepad. Key mapping (per the brief):
 *   WASD / arrows         = move
 *   Space / J             = jump (A)
 *   K / B                 = attack (B)
 *   L / X                 = special (X)
 *   Shift                 = dash (keyboard affordance; stick-snap dodge is handled by movement)
 *   U                     = explicit lockOn request (players auto-lock in combat core)
 *   R / Tab               = switchLock (GC R "lock-on switch": cycle enemy targets; edge-triggered in battle core)
 *   Z                     = allyLock (GC Z "ally lock-on"; target selection only until charge behavior is decoded)
 * Manual borg switching is deliberately unbound: the extracted control texture does not
 * show it, and current C evidence only proves death/auto-deploy swap flow.
 */
export function inputFromKeys(keys: ReadonlySet<string>, pad?: Gamepad | null): PlayerInput {
  let moveX = 0;
  let moveZ = 0;
  if (keys.has("KeyA") || keys.has("ArrowLeft")) moveX -= 1;
  if (keys.has("KeyD") || keys.has("ArrowRight")) moveX += 1;
  // +Z is forward in the sim (per RAM trace). W / Up = forward.
  if (keys.has("KeyW") || keys.has("ArrowUp")) moveZ += 1;
  if (keys.has("KeyS") || keys.has("ArrowDown")) moveZ -= 1;

  let jump = keys.has("Space") || keys.has("KeyJ");
  let attack = keys.has("KeyK") || keys.has("KeyB");
  let special = keys.has("KeyL") || keys.has("KeyX");
  let dash = keys.has("ShiftLeft") || keys.has("ShiftRight");
  let lockOn = keys.has("KeyU");
  let switchLock = keys.has("KeyR") || keys.has("Tab");
  let allyLock = keys.has("KeyZ");
  const switchBorg = false;

  if (pad) {
    const ax = pad.axes[0] ?? 0;
    const ay = pad.axes[1] ?? 0;
    if (Math.abs(ax) > 0.2) moveX = ax;
    if (Math.abs(ay) > 0.2) moveZ = -ay; // stick up = forward
    const b = (i: number) => pad.buttons[i]?.pressed ?? false;
    jump = jump || b(0); // A
    attack = attack || b(1); // B
    special = special || b(2); // X
    // Explicit lock is mostly diagnostic because player borgs auto-lock by default.
    lockOn = lockOn || b(6);
    switchLock = switchLock || b(5) || b(7);
    // XInput has no exact GC Z; use the left shoulder as the least-conflicting ally-lock stand-in.
    allyLock = allyLock || b(4);
  }

  return {
    moveX: clamp(moveX, -1, 1),
    moveZ: clamp(moveZ, -1, 1),
    jump,
    attack,
    special,
    lockOn,
    switchLock,
    allyLock,
    switchBorg,
    dash,
  };
}

function clamp(v: number, lo: number, hi: number): number {
  return v < lo ? lo : v > hi ? hi : v;
}

