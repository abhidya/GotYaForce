// Public types for the deterministic battle API. Mirrors the contract in the task brief.
// Control scheme (CONFIRMED from the game's controls screen + lock-relative movement trace):
//   A=jump, B=attack(melee/contextual), Y=special, Z=switch lock-on target,
//   stick=move in the target-relative frame while locked. Pure left/right is a dodge step
//   (surfaced as `dash`); forward+left/right is circle-strafe.

import type { Vec3 } from "@gf/physics";
import type { BorgProfile } from "./stats.js";

/** One frame of intent for a single controlled borg (player OR resolved by AI). */
export interface PlayerInput {
  /** Stick X in [-1,1] (+X). */
  moveX: number;
  /** Stick Z in [-1,1] (+Z = forward, per RAM trace). */
  moveZ: number;
  /** A — jump / air-jump / hold for boost flight. */
  jump: boolean;
  /** B — melee / contextual attack. */
  attack: boolean;
  /** Y — special attack. */
  special: boolean;
  /** Acquire / hold lock-on for non-player callers; human-controlled borgs auto-lock by default. */
  lockOn: boolean;
  /** Z — cycle lock-on target. */
  switchLock: boolean;
  /** Switch to the next borg in the force (manual). */
  switchBorg: boolean;
  /** Step/dodge (stick-action). */
  dash: boolean;
}

export function emptyInput(): PlayerInput {
  return {
    moveX: 0,
    moveZ: 0,
    jump: false,
    attack: false,
    special: false,
    lockOn: false,
    switchLock: false,
    switchBorg: false,
    dash: false,
  };
}

/** Main borg state (maps to decomp struct+0x544 action enum: idle/move/attack/damage/down/death). */
export type BorgState =
  | "idle"
  | "move"
  | "jump"
  | "fly"
  | "attack"
  | "special"
  | "hit"
  | "down"
  | "death"
  | "spawn";

/** Live, per-frame runtime state of one borg instance. */
export interface BorgRuntime {
  uid: string;
  borgId: string;
  team: number;
  /** Owning player id, or null for CPU-controlled. */
  ownerPlayer: string | null;
  hp: number;
  maxHp: number;
  /** World position (struct+0x44 vec3, flat ground plane). */
  pos: Vec3;
  /** Facing yaw in radians (struct+0x72 heading; +Z forward). */
  rotY: number;
  /** Velocity (struct+0x58-ish vec3). */
  vel: Vec3;
  grounded: boolean;
  /** Remaining mid-air jumps. */
  airJumps: number;
  state: BorgState;
  /** Frames spent in the current state. */
  stateTime: number;
  /** Current animation label (cosmetic; render reads it). */
  anim: string;
  /** Ranged ammo remaining before reload. */
  ammo: number;
  /** Named cooldown timers (frames remaining). */
  cooldowns: Record<string, number>;
  /** Invincibility timer (struct+0x720, frames; counts down 1/frame). */
  invincTimer: number;
  /** Current lock-on target uid, or null. */
  lockTarget: string | null;
  alive: boolean;
}

/** A force = an ordered list of borgs a team/player deploys one at a time. */
export interface ForceConfig {
  team: number;
  ownerPlayer: string | null;
  borgIds: string[];
}

/** Legacy tuned half-extents from origin. Kept for existing callers/selfchecks. */
export interface SymmetricStageBounds {
  x: number;
  z: number;
}

/** Real stage-space X/Z rectangle decoded from STIH hit bins. */
export interface RectStageBounds {
  minX: number;
  maxX: number;
  minZ: number;
  maxZ: number;
}

export type StageBounds = SymmetricStageBounds | RectStageBounds;

export function normalizeStageBounds(bounds: StageBounds): RectStageBounds {
  if ("minX" in bounds) return bounds;
  return {
    minX: -bounds.x,
    maxX: bounds.x,
    minZ: -bounds.z,
    maxZ: bounds.z,
  };
}

export interface StageCollisionCell {
  index: number;
  triangleIndices: number[];
}

export interface StageCollisionTriangle {
  index: number;
  layerIndex: number | null;
  marker: number;
  vertices: [Vec3, Vec3, Vec3];
  normal: Vec3;
  planeD: number;
  bounds2d: RectStageBounds;
}

export interface StageCollision {
  triangles: StageCollisionTriangle[];
  grid?: {
    origin: { x: number; z: number };
    cellSize: { x: number; z: number };
    gridCells: { x: number; z: number; total: number };
    cells: StageCollisionCell[];
  };
}

export interface BattleConfig {
  stageId: string;
  forces: ForceConfig[];
  bounds?: StageBounds;
  collision?: StageCollision;
  /** Original battle timer in frames; omitted means no timer. */
  timeLimitFrames?: number;
}

export type BattleResult = "ongoing" | "win" | "lose" | "draw";

export type ProjectileVisualKind = "energy" | "flame" | "muzzle";

/** A homing/straight projectile in flight. */
export interface Projectile {
  uid: string;
  ownerUid: string;
  team: number;
  pos: Vec3;
  vel: Vec3;
  damage: number;
  hitstun: number;
  knockback: number;
  homingTurn: number;
  homingTarget: string | null;
  life: number;
  hitRadius: number;
  visualKind: ProjectileVisualKind;
}

export interface BattleState {
  borgs: BorgRuntime[];
  projectiles: Projectile[];
  /** Remaining energy per team = sum of (alive + not-yet-deployed) borg energy. */
  energy: Record<number, number>;
  /** The currently-active (controllable) borg uid per player id. */
  activeUidByPlayer: Record<string, string>;
  frame: number;
  /** Frames remaining on the battle timer, or null when untimed. */
  timeRemainingFrames: number | null;
  result: BattleResult;
}

/** The driver object returned by createBattle. */
export interface Battle {
  state: BattleState;
  /** Advance the sim by one fixed step. `dt` is accepted for API symmetry but the sim is
   *  fixed-step (SIM.DT); pass it through for documentation/compat. */
  step(dt: number, inputs: Record<string, PlayerInput>): void;
}

/** Internal: a deploy queue entry (a borg not yet on the field). */
export interface DeployEntry {
  borgId: string;
  profile: BorgProfile;
}
