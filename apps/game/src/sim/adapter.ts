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
import {
  DEFAULT_ARENA_STAGE,
  EXPORTED_STAGE_CATALOG,
  EXPORTED_STAGE_IDS,
  isExportedStageId,
  stageCatalogEntry,
} from "../stages/catalog.generated.js";

export { DEFAULT_ARENA_STAGE, EXPORTED_STAGE_CATALOG, EXPORTED_STAGE_IDS, isExportedStageId };

/**
 * Map a mission arena id to a browser-exported stage id.
 *
 * The extractor exports real disc stages as `st##` ids in the generated catalog.
 * Adventure arena names like "Little Hill" are not yet verified against those ids,
 * so they deliberately fall back instead of guessing. When a traced table exists,
 * add it here.
 */
export function stageIdForArena(arena: string | undefined): string {
  const normalized = arena?.trim().toLowerCase() ?? "";
  if (isExportedStageId(normalized)) return normalized;
  if (normalized === "challenge") return DEFAULT_ARENA_STAGE;
  return DEFAULT_ARENA_STAGE;
}

/**
 * Resolve the actual renderable stage for a mission battle.
 *
 * Challenge mode writes three raw selector bytes in the DOL-backed setup:
 *   PTR_DAT_80433934[0x1c] = stage byte
 *   PTR_DAT_80433934[0x1d] = subtable 0..2
 *   PTR_DAT_80433934[0x1e] = variant within that subtable
 *
 * The stage asset loader indexes `PTR_DAT_802d07a0[stageByte * 3 + subtable]` and then
 * the variant pointer inside that table. Browser exports currently expose the three visual
 * subtable families as `st00`/`st20`/`st40` where those archives exist, but not every
 * stage byte has every family exported. Use the subtable family when present, otherwise
 * fall back to the base `st##` stage instead of fabricating a missing archive.
 */
export function stageIdForBattleConfig(cfg: MissionBattleConfig): string {
  const meta = cfg.meta;
  const stageByte = meta?.stageByte;
  const stageSubtable = meta?.stageSubtable;
  if (Number.isInteger(stageByte) && Number.isInteger(stageSubtable)) {
    const familyByte = (stageSubtable as number) * 0x20 + (stageByte as number);
    const familyId = stageIdFromByte(familyByte);
    if (stageHasCollision(familyId)) return familyId;

    const baseId = stageIdFromByte(stageByte as number);
    if (stageHasCollision(baseId)) return baseId;
  }

  return stageIdForArena(cfg.arena);
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
  stageId: string = stageIdForBattleConfig(cfg),
  bounds?: StageBounds,
  collision?: StageCollision,
): CombatBattleConfig {
  return {
    stageId,
    ...(bounds ? { bounds } : {}),
    ...(collision ? { collision } : {}),
    ...(cfg.timeLimitFrames !== undefined ? { timeLimitFrames: cfg.timeLimitFrames } : {}),
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
  allyLock: boolean;
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
 *   Shift                 = dash (keyboard affordance; stick-snap dodge is handled by movement)
 *   U                     = explicit lockOn request (players auto-lock in combat core)
 *   Tab                   = switchLock (GC R stand-in)
 *   Z                     = allyLock (GC Z stand-in; target selection only until charge behavior is decoded)
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
  let attack = keys.has("KeyK") || keys.has("KeyX");
  let special = keys.has("KeyL") || keys.has("KeyY");
  let dash = keys.has("ShiftLeft") || keys.has("ShiftRight");
  let lockOn = keys.has("KeyU");
  let switchLock = keys.has("Tab");
  let allyLock = keys.has("KeyZ");
  const switchBorg = false;

  if (pad) {
    const ax = pad.axes[0] ?? 0;
    const ay = pad.axes[1] ?? 0;
    if (Math.abs(ax) > 0.2) moveX = ax;
    if (Math.abs(ay) > 0.2) moveZ = -ay; // stick up = forward
    const b = (i: number) => pad.buttons[i]?.pressed ?? false;
    jump = jump || b(0); // A
    attack = attack || b(1) || b(2); // B / X
    special = special || b(3); // Y
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

function stageIdFromByte(byte: number): string {
  return `st${Math.max(0, byte).toString(16).padStart(2, "0")}`;
}

function stageHasCollision(stageId: string): boolean {
  const entry = stageCatalogEntry(stageId);
  return !!entry && entry.collisionCount > 0;
}
