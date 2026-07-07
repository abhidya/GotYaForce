import type { RomActor, Vec3 } from "../rom/actor.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";

const BAM_TO_RAD = (Math.PI * 2) / 65536;

export const HAMMER_X = {
  STREAM_GROUP: 0xf,
  ZERO: 0.0,
  SETUP_TIMER: 60.0,
  REPOSITION_SCALE: 0.95,
  GRAVITY_PARAM: 1.0,
  MOTION_ACC_Y: 1.0,
  MOTION_ACC_Z: 0.0,
  HOVER_YVEL_FACTOR: 1.0,
  STATETIMER_SEED: 0.0,
  SOUND_CUE: 0xf,
} as const;

export interface HammerFamilyCtx {
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  onHammerProjectile?: (actor: RomActor, variant: number) => void;
  onSetupCollision?: (actor: RomActor, bodyType: number) => void;
  onFrameUpdate?: (actor: RomActor) => void;
  onCheckProjectile?: (actor: RomActor, mask: number) => boolean;
  onTickStream?: (actor: RomActor, group: number) => void;
  onExitRecovery?: (actor: RomActor) => void;
  onSpawnFX?: (actor: RomActor, fxType: number) => void;
}

export interface HammerXConfig {
  rangeThreshold: number;
}

const DEFAULT_HAMMER_CONFIG: HammerXConfig = {
  rangeThreshold: 1000.0,
};

interface HammerScratch {
  /** +0xcc: lock-on target position (synthetic, from BorgRuntime). */
  lockTarget?: Vec3 | null;
  /** +0x541: fail flag. */
  hammerFailFlag?: boolean;
  /** +0x6ea: hit counter (byte). */
  hammerHitCount?: number;
  /** +0x6f6: aim pitch BAM (short). */
  hammerAimPitchBAM?: number;
  /** +0x18dc: steer yaw animation (short). */
  hammerSteerYaw?: number;
  /** +0x73f: flag byte. */
  hammerFlag?: number;
  /** +0x1cf2: collision flag (byte). */
  hammerCollisionFlag?: number;
  /** +0x1d0f: contact flag (byte). */
  hammerContactFlag?: number;
  /** +0x1d9b: contact sub-byte. */
  hammerContactByte?: number;
  /** +0x548: hitbox offset X (short). */
  hitboxOffX?: number;
  /** +0x54a: hitbox offset Y (short). */
  hitboxOffY?: number;
  /** +0x54c: hitbox radius (short). */
  hitboxRadius?: number;
}

function scratchOf(actor: RomActor): RomActor & HammerScratch {
  return actor as RomActor & HammerScratch;
}

function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

function faceLockTarget(actor: RomActor): void {
  const s = scratchOf(actor);
  if (s.lockTarget) {
    actor.heading = actor.lockYaw;
    actor.activeYaw = actor.lockYaw;
  }
}

function computeAimPitch(actor: RomActor): number {
  const s = scratchOf(actor);
  const pitch = s.hammerAimPitchBAM ?? 0;
  const target = s.lockTarget;
  if (!target) {
    s.hammerAimPitchBAM = toS16(pitch * 0.9);
    return s.hammerAimPitchBAM ?? 0;
  }
  const dx = target.x - actor.pos.x;
  const dz = target.z - actor.pos.z;
  const dy = target.y - actor.pos.y;
  const horizDist = Math.hypot(dx, dz);
  let desired = -toS16(BAM_TO_RAD * 65536 / (Math.PI * 2) * Math.atan2(dy, horizDist));
  if (desired > 0x4000) desired = 0x4000;
  if (desired < -0x4000) desired = -0x4000;
  const step = 2560 * actor.dt;
  const delta = desired - pitch;
  const result = Math.abs(delta) <= step ? desired : pitch + Math.sign(delta) * step;
  s.hammerAimPitchBAM = toS16(result);
  return result;
}

function updateSteerYaw(actor: RomActor, rate: number): void {
  const s = scratchOf(actor);
  s.hammerSteerYaw = toS16((s.hammerSteerYaw ?? 0) - Math.trunc(rate * actor.dt));
}

// Phase 0 — FUN_800e5a5c: Range check + aim + reposition + sound.
function hammerPhase0(actor: RomActor, cfg: HammerXConfig, ctx: HammerFamilyCtx): void {
  const s = scratchOf(actor);
  s.hammerAimPitchBAM = 0;
  s.hammerHitCount = 0;

  // Range check (FUN_80066838 from config block +0x868)
  if (cfg.rangeThreshold <= 0) {
    s.hammerFailFlag = true;
    actor.activeYaw = actor.heading;
  }

  actor.handlerTimer = HAMMER_X.SETUP_TIMER;
  faceLockTarget(actor);
  computeAimPitch(actor);

  // Reposition: motion = pos - target; motion *= 0.95; pos += motion
  const target = s.lockTarget;
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(HAMMER_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  ctx.onPlayCue?.(actor, HAMMER_X.SOUND_CUE);
  s.hammerHitCount = 1;

  actor.fbPhaseSlots[0] = 1;
}

// Phase 1 — FUN_800e5b80: Motion decay + aim + timer + advance.
function hammerPhase1(actor: RomActor, ctx: HammerFamilyCtx): void {
  vecScale(HAMMER_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  ctx.onTickStream?.(actor, HAMMER_X.STREAM_GROUP);
  computeAimPitch(actor);

  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= HAMMER_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
  }

  ctx.onFrameUpdate?.(actor);
}

// Phase 2 — FUN_800e5c40: Steer + motion + hitbox setup + child spawn → advance to 3.
function hammerPhase2(actor: RomActor, ctx: HammerFamilyCtx): void {
  const s = scratchOf(actor);
  updateSteerYaw(actor, 1.0);
  faceLockTarget(actor);
  computeAimPitch(actor);

  vecScale(HAMMER_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  ctx.onTickStream?.(actor, HAMMER_X.STREAM_GROUP);

  actor.fbPhaseSlots[0] = 3;

  // Hitbox offset varies by borg (pl0403 vs pl020c)
  s.hitboxOffX = actor.borgNumber === 0x20c ? 0x18 : 0x28;
  s.hitboxOffY = actor.borgNumber === 0x20c ? 0x28 : 0x38;
  s.hitboxRadius = 7;

  // Clear motion accumulator + set acceleration fields
  actor.motion.x = HAMMER_X.ZERO;
  actor.motion.y = HAMMER_X.MOTION_ACC_Y;
  actor.motion.z = HAMMER_X.MOTION_ACC_Z;
  actor.hDecel = HAMMER_X.ZERO;
  actor.gravityCoeff = HAMMER_X.ZERO;

  ctx.onSetupCollision?.(actor, 0x2d);
  ctx.onHammerProjectile?.(actor, 0);
}

// Phase 3 — FUN_800e5d64: Projectile management + velocity derivation + physics.
function hammerPhase3(actor: RomActor, ctx: HammerFamilyCtx): void {
  const s = scratchOf(actor);

  const projectileAlive = ctx.onCheckProjectile?.(actor, 0xf0f00) ?? false;
  if (projectileAlive) {
    const oldRadius = s.hitboxRadius ?? 7;
    s.hitboxRadius = Math.max(1, oldRadius - 1);
    const offY = s.hitboxOffY ?? 0x38;
    const consume = Math.min(oldRadius, offY);
    s.hitboxOffY = offY - consume;
    s.hitboxOffX = (s.hitboxOffX ?? 0x28) + consume;
  }

  updateSteerYaw(actor, 1.0);
  faceLockTarget(actor);
  computeAimPitch(actor);

  actor.motion.x = actor.motion.x + actor.motion.z * actor.dt;
  if (actor.motion.y < actor.motion.x) {
    actor.motion.x = actor.motion.y;
  }

  const pitchBAM = s.hammerAimPitchBAM ?? 0;
  const pitchRad = pitchBAM * BAM_TO_RAD;
  actor.hSpeed = actor.motion.x * Math.cos(pitchRad);
  actor.yVel = -actor.motion.x * Math.sin(pitchRad);

  integratePhysics(HAMMER_X.GRAVITY_PARAM, actor, actor.lockYaw);
  ctx.onTickStream?.(actor, HAMMER_X.STREAM_GROUP);

  if (s.hammerCollisionFlag && s.hammerCollisionFlag > 0) {
    s.hitboxOffX = (s.hitboxOffX ?? 0x28) - 8;
    if ((s.hitboxOffX ?? 0) < 0) {
      ctx.onPlayCue?.(actor, HAMMER_X.SOUND_CUE);
      actor.fbPhaseSlots[0] = 4;
      s.hammerSteerYaw = 0;
      s.hammerHitCount = (s.hammerHitCount ?? 0) + 1;
      actor.hSpeed = HAMMER_X.ZERO;
      actor.yVel = HAMMER_X.ZERO;
      actor.hDecel = HAMMER_X.ZERO;
      actor.gravityCoeff = HAMMER_X.ZERO;
    }
    ctx.onSpawnFX?.(actor, 10);
  }

  ctx.onFrameUpdate?.(actor);
}

// Phase 4 — FUN_800e5f54: Hover/descent + exit on hit.
function hammerPhase4(actor: RomActor, ctx: HammerFamilyCtx): void {
  const s = scratchOf(actor);

  ctx.onTickStream?.(actor, HAMMER_X.STREAM_GROUP);

  if (s.hammerContactFlag && s.hammerContactFlag > 0) {
    s.hammerContactFlag = 0;
    s.hammerContactByte = 0;
    actor.hDecel = HAMMER_X.ZERO;
    actor.hSpeed = HAMMER_X.ZERO;
    const descYVel = HAMMER_X.HOVER_YVEL_FACTOR * (actor.descriptor?.handlerData6c ?? 1);
    actor.yVel = descYVel;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 1;
  }

  integratePhysics(HAMMER_X.GRAVITY_PARAM, actor, actor.lockYaw);

  if (!actor.wallContact) {
    ctx.onFrameUpdate?.(actor);
  } else {
    s.hammerSteerYaw = 0;
    s.hammerFlag = 0;
    actor.controlWord &= ~0x3;
    ctx.onExitRecovery?.(actor);
    actor.stateTimer = HAMMER_X.STATETIMER_SEED + actor.dt;
  }
}

function createHammerXHandler(cfg: HammerXConfig, ctx: HammerFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    const s = scratchOf(actor);
    if (s.hammerFailFlag) {
      s.hammerFailFlag = false;
    }
    switch (actor.fbPhaseSlots[0]) {
      case 0: hammerPhase0(actor, cfg, ctx); break;
      case 1: hammerPhase1(actor, ctx); break;
      case 2: hammerPhase2(actor, ctx); break;
      case 3: hammerPhase3(actor, ctx); break;
      case 4: hammerPhase4(actor, ctx); break;
    }
  };
}

export function createHammerRootAction(
  ctx: HammerFamilyCtx,
  cfg?: Partial<HammerXConfig>,
): (actor: RomActor) => void {
  const config = { ...DEFAULT_HAMMER_CONFIG, ...cfg };
  const xHandler = createHammerXHandler(config, ctx);
  return (actor) => {
    if (actor.actionIndex === 2) {
      xHandler(actor);
    }
  };
}

export function configureHammerFamily(
  actor: RomActor,
  _borgId: "pl0403",
  ctx: HammerFamilyCtx,
  cfg?: Partial<HammerXConfig>,
): void {
  actor.borgNumber = 0x403;
  actor.rootAction = createHammerRootAction(ctx, cfg);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
