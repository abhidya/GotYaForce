// Public types for the deterministic battle API. Mirrors the contract in the task brief.
// Control scheme (CONFIRMED from the game's controls screen + lock-relative movement trace):
//   A=jump, B=attack(melee/contextual), X=special, R=switch lock-on target,
//   Z=ally lock-on (target selection only; ally charge/power-up behavior not decoded yet),
//   stick=move in the target-relative frame while locked. Pure left/right is a dodge step
//   (surfaced as `dash`); forward+left/right is circle-strafe.

import type { StageBounds, StageCollision, Vec3 } from "@gf/physics";
export {
  normalizeStageBounds,
  type RectStageBounds,
  type StageBounds,
  type StageCollision,
  type StageCollisionCell,
  type StageCollisionTriangle,
  type SymmetricStageBounds,
} from "@gf/physics";
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
  /** X — special attack. */
  special: boolean;
  /** Acquire / hold lock-on for non-player callers; human-controlled borgs auto-lock by default. */
  lockOn: boolean;
  /** R — cycle lock-on target. */
  switchLock: boolean;
  /** Z — ally lock-on request. Target selection is modeled; ally charge behavior is still unknown. */
  allyLock: boolean;
  /** Reserved/prototype; Challenge battle core ignores manual switching until original proof exists. */
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
    allyLock: false,
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
export interface ActorParamTier {
  /** `actor+0x74a`, reset by C `reset_actor_param_tier` to 0x10. */
  tier: number;
  /** `actor+0x74e`, signed byte accumulator touched by `apply_actor_param_tier_delta_63`. */
  deltaAccum: number;
  /** `actor+0x750`, set to 900 by `apply_actor_param_tier_delta_63` when accumulator is nonzero. */
  timerFrames: number;
}

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
  /** Balance gauge (struct+0x6c2, u16); a hit that depletes it forces a stagger
   *  (0x6fd |= 0xa6). Init = balanceGaugeMax from the borg's pl####data.bin u16[0]
   *  (chunk_0007.c:47-52); refills to max when balanceRefillDelay expires. */
  balanceGauge: number;
  /** Balance gauge max (struct+0x6be) — per-borg VERIFIED data (data/gaugeInit.json). */
  balanceGaugeMax: number;
  /** Down gauge (struct+0x6c6, u16); a hit that drops it below 1 staggers. Init/reset =
   *  downGaugeBase (pl####data.bin u16[1]); resets to base when downResetDelay expires
   *  (zz_003d3e8_, chunk_0004.c:6866-6876) and on stagger entry. */
  downGauge: number;
  /** Down gauge base (struct+0x6c4) — per-borg VERIFIED data (data/gaugeInit.json). */
  downGaugeBase: number;
  /** Post-hit window (struct+0x684, frames): balance refills to max on expiry. Set to 60 on
   *  every hit taken; frozen while in a hit reaction (see constants.ts STAGGER). */
  balanceRefillDelay: number;
  /** Post-hit window (struct+0x688, frames): down gauge resets to base on expiry. */
  downResetDelay: number;
  /** Post-hit combo window (struct+0x68c, frames): comboAccum/comboRank reset on expiry. */
  comboWindow: number;
  /** Combo accumulator (struct+0x6c8, clamped 0-99). */
  comboAccum: number;
  /** Combo rank byte (struct+0x6ca). Reset with comboAccum; rank derivation untraced. */
  comboRank: number;
  /** Proven actor param-tier state at `+0x74a/+0x74e/+0x750`; effect table mapping still unported. */
  paramTier: ActorParamTier;
  /** Current lock-on target uid, or null. */
  lockTarget: string | null;
  /** Current ally lock-on target uid, or null. Z control is asset-confirmed; downstream behavior is unknown. */
  allyLockTarget: string | null;
  /** Uids already struck by the CURRENT melee swing (enforces one hit per swing per target).
   *  Transient bookkeeping, reset on every swing start; optional so external constructors
   *  (tests/fakes) don't need to provide it. */
  meleeHitUids?: string[];
  alive: boolean;
}

/** A force = an ordered list of borgs a team/player deploys one at a time. */
export interface ForceConfig {
  team: number;
  ownerPlayer: string | null;
  borgIds: string[];
}

export interface SpawnPoint {
  pos: Vec3;
  /** Optional facing yaw in radians; omitted means face arena center. */
  rotY?: number;
}

export interface BattleConfig {
  stageId: string;
  forces: ForceConfig[];
  bounds?: StageBounds;
  collision?: StageCollision;
  /** Optional exact per-force spawn points from original stage/slot tables. */
  spawnPoints?: SpawnPoint[];
  /** Original battle timer in frames; omitted means no timer. */
  timeLimitFrames?: number;
  /**
   * DERIVED — model of the original timer-pause flag PTR_DAT_80433934[0x50].
   * The countdown (zz_0029b58_ @0x80029b58, chunk_0003.c:4631-4638) and BOTH
   * timeout branches of the battle-end judge (zz_00297c8_ @0x800297c8,
   * chunk_0003.c:4519-4529 and :4547-4553) run only while [0x50] == 0.
   * Challenge setup writes timeLimit=18000 AND [0x50]=1 (chunk_0048.c:390-392),
   * so original Challenge battles display a timer value but can never time out.
   * Versus with a selected limit writes seconds*60 and [0x50]=0 (chunk_0044.c:366-373).
   */
  timerFrozen?: boolean;
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
  /** Ballistic drop subtracted from vel.y each frame (bullet kinds only). Optional; 0/absent = none. */
  drop?: number;
  /** Damage-record index into gauges.ts DAMAGE_RECORDS for the gauge/stagger model
   *  (DERIVED mapping — see gauges.ts DAMAGE_RECORD_INDEX). Absent = normal shot (record 0). */
  damageRecordIndex?: number;
}

export interface BattleState {
  borgs: BorgRuntime[];
  projectiles: Projectile[];
  /** Remaining energy per team = sum of (alive + not-yet-deployed) borg energy. */
  energy: Record<number, number>;
  /** Whole borgs defeated per team, counted at the source death event before auto-deploy. */
  defeated: Record<number, number>;
  /** Energy/cost defeated per team, counted from each defeated borg's profile energy. */
  defeatedEnergy: Record<number, number>;
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
