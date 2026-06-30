// Adapter layer between the three finished systems:
//   @gf/missions (createChallengeRun -> missions BattleConfig)  ->
//   @gf/combat   (createBattle -> deterministic Battle)         ->
//   three.js scene (BorgRuntime[] -> rendered models).
//
// This file owns the SHAPE MISMATCH fix: missions' BattleConfig uses
//   { arena, forces:[{ team:"player"|"enemy", ownerPlayer:number|null, borgIds, cpuAlly? }] }
// while combat's createBattle wants
//   { stageId, forces:[{ team:number, ownerPlayer:string|null, borgIds }] }.
// See convertBattleConfig() below. Human player 0 -> playerId "p0".

import type {
  BattleConfig as MissionBattleConfig,
} from "@gf/missions";
import type {
  BattleConfig as CombatBattleConfig,
  PlayerInput,
  StageBounds,
  StageCollision,
} from "@gf/combat";

/** Default renderable Challenge arena until trace data proves the original arena rotation. */
export const DEFAULT_ARENA_STAGE = "st00";

/**
 * Map a mission arena id to a browser-exported stage id.
 *
 * The extractor exports real disc stages as `st##`. Adventure arena names like
 * "Little Hill" are not yet verified against those ids, so they deliberately
 * fall back instead of guessing. When a traced table exists, add it here.
 */
export function stageIdForArena(arena: string | undefined): string {
  const normalized = arena?.trim().toLowerCase() ?? "";
  if (/^st\d{2}$/.test(normalized)) return normalized;
  if (normalized === "challenge") return DEFAULT_ARENA_STAGE;
  return DEFAULT_ARENA_STAGE;
}

/** Stable playerId for a 0-based human player index, matching the brief: 0 -> "p0". */
export function playerIdFor(playerIndex: number): string {
  return `p${playerIndex}`;
}

/**
 * Convert a missions BattleConfig into the combat-core BattleConfig.
 *  - stageId   = arena (mapped to a renderable stage)
 *  - team      = force.team === "player" ? 0 : 1
 *  - ownerPlayer = null for CPU, "p"+index for humans
 */
export function convertBattleConfig(
  cfg: MissionBattleConfig,
  stageId: string = stageIdForArena(cfg.arena),
  bounds?: StageBounds,
  collision?: StageCollision,
): CombatBattleConfig {
  return {
    stageId,
    ...(bounds ? { bounds } : {}),
    ...(collision ? { collision } : {}),
    forces: cfg.forces.map((force) => ({
      team: force.team === "player" ? 0 : 1,
      ownerPlayer: force.ownerPlayer == null ? null : playerIdFor(force.ownerPlayer),
      borgIds: [...force.borgIds],
    })),
  };
}

/** Local input snapshot accumulated from the keyboard/gamepad each frame. */
export interface LocalControls {
  moveX: number;
  moveZ: number;
  jump: boolean;
  attack: boolean;
  special: boolean;
  lockOn: boolean;
  switchLock: boolean;
  switchBorg: boolean;
  dash: boolean;
}

/**
 * Build a combat PlayerInput from the live key set (KeyboardEvent.code values)
 * plus an optional gamepad. Key mapping (per the brief):
 *   WASD / arrows         = move
 *   Space / J             = jump (A)
 *   K / X                 = attack (B)
 *   L / Y                 = special (Y)
 *   Shift                 = dash
 *   U                     = lockOn (R)
 *   Tab                   = switchLock (Z)
 *   E                     = switchBorg
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
  let attack = keys.has("KeyK") || keys.has("KeyX");
  let special = keys.has("KeyL") || keys.has("KeyY");
  let dash = keys.has("ShiftLeft") || keys.has("ShiftRight");
  let lockOn = keys.has("KeyU");
  let switchLock = keys.has("Tab");
  const switchBorg = keys.has("KeyE");

  if (pad) {
    const ax = pad.axes[0] ?? 0;
    const ay = pad.axes[1] ?? 0;
    if (Math.abs(ax) > 0.2) moveX = ax;
    if (Math.abs(ay) > 0.2) moveZ = -ay; // stick up = forward
    const b = (i: number) => pad.buttons[i]?.pressed ?? false;
    jump = jump || b(0); // A
    attack = attack || b(1) || b(2); // B / X
    special = special || b(3); // Y
    dash = dash || b(5) || b(7); // shoulder/trigger
    lockOn = lockOn || b(4) || b(6);
    switchLock = switchLock || b(9);
  }

  return {
    moveX: clamp(moveX, -1, 1),
    moveZ: clamp(moveZ, -1, 1),
    jump,
    attack,
    special,
    lockOn,
    switchLock,
    switchBorg,
    dash,
  };
}

function clamp(v: number, lo: number, hi: number): number {
  return v < lo ? lo : v > hi ? hi : v;
}
