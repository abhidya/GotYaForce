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
  switchLockPrev: boolean;
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
 *   R / Tab               = switchLock (GC R "lock-on switch": source request 2 / next target)
 *   Q                     = switchLockPrev (GC L "lock-on switch": source request 3 / previous target)
 *   Z                     = allyLock (GC Z "ally lock-on"; target selection only until charge behavior is decoded)
 * Manual borg switching is deliberately unbound: the extracted control texture does not
 * show it, and current C evidence only proves death/auto-deploy swap flow.
 *
 * HORIZONTAL AXIS SIGN: +Z is forward (RAM trace) and yawFromXZ(x, z) = atan2(x, z)
 * yields rotY that increases toward +X. The chase cam (camera.ts) trails the borg along
 * -forward, so with up=+Y a borg facing +Z has world +X on the player's LEFT (Three.js
 * camera-local +X = world -X). Feeding +X straight into yawFromXZ therefore turns the
 * borg toward the player's LEFT when they press RIGHT. To make "press right = turn
 * right" we feed the NEGATED stick X into the sim (and likewise for lock-frame strafing
 * in movement.ts resolveHorizontalIntent, which consumes the same axis). The sim/AI
 * keep their internal "+X is world-right" convention untouched; only the human-input
 * adapter flips.
 */
export function inputFromKeys(keys: ReadonlySet<string>, pad?: Gamepad | null): PlayerInput {
  let moveX = 0;
  let moveZ = 0;
  if (keys.has("KeyA") || keys.has("ArrowLeft")) moveX += 1;
  if (keys.has("KeyD") || keys.has("ArrowRight")) moveX -= 1;
  // +Z is forward in the sim (per RAM trace). W / Up = forward.
  if (keys.has("KeyW") || keys.has("ArrowUp")) moveZ += 1;
  if (keys.has("KeyS") || keys.has("ArrowDown")) moveZ -= 1;

  let jump = keys.has("Space") || keys.has("KeyJ");
  let attack = keys.has("KeyK") || keys.has("KeyB");
  let special = keys.has("KeyL") || keys.has("KeyX");
  let dash = keys.has("ShiftLeft") || keys.has("ShiftRight");
  let lockOn = keys.has("KeyU");
  let switchLock = keys.has("KeyR") || keys.has("Tab");
  let switchLockPrev = keys.has("KeyQ");
  let allyLock = keys.has("KeyZ");
  const switchBorg = false;
  let hyper = keys.has("KeyY") || keys.has("KeyH");

  if (pad) {
    const ax = pad.axes[0] ?? 0;
    const ay = pad.axes[1] ?? 0;
    if (Math.abs(ax) > 0.2) moveX = -ax; // see HORIZONTAL AXIS SIGN note above
    if (Math.abs(ay) > 0.2) moveZ = -ay; // stick up = forward
    const b = (i: number) => pad.buttons[i]?.pressed ?? false;
    jump = jump || b(0); // A
    attack = attack || b(1); // B
    special = special || b(2); // X
    // Explicit lock is mostly diagnostic because player borgs auto-lock by default.
    // No exact browser mapping for the GameCube shoulder cluster; use right shoulder/trigger
    // for source request 2 and left trigger for request 3. LB remains the Z stand-in below.
    switchLock = switchLock || b(5) || b(7);
    switchLockPrev = switchLockPrev || b(6);
    // XInput has no exact GC Z; use the left shoulder as the least-conflicting ally-lock stand-in.
    allyLock = allyLock || b(4);
    // XInput button 3 (Y on the standard mapping) is otherwise unused here — natural stand-in
    // for GC Y (shell input only, ATK-011; no gameplay effect).
    hyper = hyper || b(3);
  }

  return {
    moveX: clamp(moveX, -1, 1),
    moveZ: clamp(moveZ, -1, 1),
    jump,
    attack,
    special,
    lockOn,
    switchLock,
    switchLockPrev,
    allyLock,
    switchBorg,
    dash,
    hyper,
  };
}

function clamp(v: number, lo: number, hi: number): number {
  return v < lo ? lo : v > hi ? hi : v;
}

