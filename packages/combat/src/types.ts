// Public types for the deterministic battle API. Mirrors the contract in the task brief.
// Control scheme (CONFIRMED from the game's controls screen):
//   A=jump, B=attack(melee/contextual), Y=special, R=lock-on, Z=switch lock-on target,
//   stick=move, step/dodge=stick-action (we surface it as `dash`).

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
  /** R — acquire / hold lock-on. */
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

export interface BattleConfig {
  stageId: string;
  forces: ForceConfig[];
  bounds?: { x: number; z: number };
}

export type BattleResult = "ongoing" | "win" | "lose" | "draw";

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
  homingTarget: string | null;
  life: number;
  hitRadius: number;
}

export interface BattleState {
  borgs: BorgRuntime[];
  projectiles: Projectile[];
  /** Remaining energy per team = sum of (alive + not-yet-deployed) borg energy. */
  energy: Record<number, number>;
  /** The currently-active (controllable) borg uid per player id. */
  activeUidByPlayer: Record<string, string>;
  frame: number;
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
