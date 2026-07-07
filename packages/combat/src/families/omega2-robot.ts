import type { RomActor, Vec3 } from "../rom/actor.js";
import { integratePhysics } from "../rom/physics.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { vecScale, vecAdd, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** BAM→rad scale (2π/65536). */
const BAM_TO_RAD = (Math.PI * 2) / 65536;

/** ROM float constants for the OMEGA-II/III/IV X-special (chunk_0026.c:3235-3418). */
export const OMEGA2_X = {
  STREAM_RATE: -1.0,
  ZERO: 0.0,
  /** FLOAT_80439078 = 20.0 — launch/reposition speed K. */
  LAUNCH_SPEED: 20.0,
  /** FLOAT_80439088 = 0.0 — timer floor. */
  TIMER_FLOOR: 0.0,
  /** FLOAT_80439090 = 60.0 — phase-0 face budget AND phase-4 airborne timer. */
  SETUP_TIMER: 60.0,
  /** FLOAT_80439094 = 20.0 — phase-1→2 advance timer. */
  LAUNCH_TIMER: 20.0,
  /** FLOAT_8043909c ≈ 100.0 — phase-2 range check threshold. */
  RANGE_GATE: 100.0,
  /** FLOAT_804390ac = 250.0 — phase-1 FX distance gate. */
  FX_DIST_GATE: 250.0,
  /** FLOAT_804390b0 = 0.95 — reposition scale / decel factor. */
  REPOSITION_SCALE: 0.95,
  /** FLOAT_804390c4 = 250.0 — same as FX_DIST_GATE, phase-1 FX child distance gate. */
  FX_DIST_GATE2: 250.0,
  /** FLOAT_804390d4 = 1.0 — FUN_80067310 gravity param (phases 2/3/4). */
  GRAVITY_PARAM: 1.0,
  /** FLOAT_804390d8 = 300.0 — phase-3 hSpeed set on damage byte +0x1d9 & 0x30. */
  DAMAGE_HSPEED: 300.0,
  /** FLOAT_804390dc = 10.0 — phase-3 yVel set on damage byte. */
  DAMAGE_YVEL: 10.0,
} as const;

export interface Omega2XConfig {
  /** Stream slot base (r4 value the wrapper passes). */
  slotBase: number;
  /** Range gate threshold for phase 0 (from config block +0x86c). */
  rangeThreshold: number;
}

const DEFAULT_OMEGA2_CONFIG: Omega2XConfig = {
  slotBase: 0,
  rangeThreshold: 1000.0,
};

interface Omega2XScratch {
  lockTarget?: Vec3 | null;
  grounded?: boolean;
  /** +0x54e: aim pitch BAM angle stored by zz_006e514_. */
  omega2AimPitchBAM?: number;
  /** +0x541: target-invalid flag from phase-0 range gate. */
  omega2TargetInvalid?: boolean;
  /** +0x1d9: damage byte bitmask (bits 0x30 cancel phase-3 flight). */
  omega2DamageByte?: number;
}

function scratchOf(actor: RomActor): RomActor & Omega2XScratch {
  return actor as RomActor & Omega2XScratch;
}

function effLockTarget(actor: RomActor): Vec3 | null {
  const s = scratchOf(actor);
  if (s.omega2TargetInvalid) return null;
  return s.lockTarget ?? null;
}

function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

/** Compute aim pitch BAM from target position (simplified zz_006e514_). */
function computeAimPitch(actor: RomActor): number {
  const s = scratchOf(actor);
  const target = effLockTarget(actor);
  let pitch = s.omega2AimPitchBAM ?? 0;
  if (!target) {
    pitch = toS16(pitch * 0.9);
    s.omega2AimPitchBAM = pitch;
    return pitch;
  }
  const dx = target.x - actor.pos.x;
  const dz = target.z - actor.pos.z;
  const dy = target.y - actor.pos.y;
  const horizDist = Math.hypot(dx, dz);
  const atanBam = toS16(BAM_TO_RAD * 65536 / (Math.PI * 2) * Math.atan2(dy, horizDist));
  let desired = -atanBam;
  if (desired > 0x4000) desired = 0x4000;
  if (desired < -0x4000) desired = -0x4000;
  const step = 2560 * actor.dt;
  const delta = desired - pitch;
  if (Math.abs(delta) <= step) pitch = desired;
  else pitch += Math.sign(delta) * step;
  s.omega2AimPitchBAM = toS16(pitch);
  return pitch;
}

function faceLockTarget(actor: RomActor): boolean {
  const target = effLockTarget(actor);
  if (!target) return false;
  actor.heading = actor.lockYaw;
  actor.activeYaw = actor.lockYaw;
  return true;
}

function decayVelocity(k: number, actor: RomActor): void {
  if (actor.dt === 1) {
    actor.hSpeed *= k;
    actor.yVel *= k;
  } else {
    actor.hSpeed -= actor.hSpeed * (1 - k) * actor.dt;
    actor.yVel -= actor.yVel * (1 - k) * actor.dt;
  }
}

/** Range check — port of FUN_80066838(range, actor): returns true when target in range. */
function targetInRange(actor: RomActor, range: number): boolean {
  const s = scratchOf(actor);
  if (s.omega2TargetInvalid) return false;
  const target = effLockTarget(actor);
  if (!target) return false;
  const dx = target.x - actor.pos.x;
  const dz = target.z - actor.pos.z;
  const dist = Math.hypot(dx, dz);
  return dist <= range;
}

export interface Omega2FamilyCtx extends StreamContext {}

// Phase 0 — FUN_800f3d04 @ chunk_0026.c:3237. Setup + range gate + blink + stream.
function omega2Phase0(actor: RomActor, cfg: Omega2XConfig, ctx: Omega2FamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = OMEGA2_X.SETUP_TIMER;
  s.omega2AimPitchBAM = 0;
  s.omega2TargetInvalid = false;
  actor.streamSlot = cfg.slotBase;

  // +0xcc == 0 path → lock yaw = heading
  actor.activeYaw = actor.lockYaw;

  // Range check via FUN_80066838
  if (!targetInRange(actor, cfg.rangeThreshold)) {
    s.omega2TargetInvalid = true;
    actor.lockYaw = actor.heading;
    actor.activeYaw = actor.heading;
  }

  // zz_006d144_(actor, 0xc0) — face target + voice
  ctx.onPlayCue?.(actor, 0xc0);
  faceLockTarget(actor);

  // zz_006e514_(actor, 0xc0, &pitch) — compute aim pitch
  computeAimPitch(actor);

  // Blink reposition: motion = pos - target; motion *= 0.95; pos += motion
  const target = effLockTarget(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(OMEGA2_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 3, slot, OMEGA2_X.STREAM_RATE);
}

// Phase 1 — FUN_800f3e3c @ chunk_0026.c:3279. Reposition + timer/face + advance.
function omega2Phase1(actor: RomActor, _cfg: Omega2XConfig, ctx: Omega2FamilyCtx): void {
  vecScale(OMEGA2_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // Conditional stream tick (gated on +0x1b03 != 0)
  tickStream(actor, 0xf, ctx);

  // zz_006e514_ — recompute aim pitch
  computeAimPitch(actor);

  // Timer countdown + face alignment check (zz_006d144_ return).
  // Advance on EITHER timer expiry OR face-aligned target in range.
  actor.handlerTimer -= actor.dt;
  const aligned = faceLockTarget(actor);

  if (actor.handlerTimer <= OMEGA2_X.TIMER_FLOOR || aligned) {
    actor.fbPhaseSlots[0] = 2;
    actor.handlerTimer = OMEGA2_X.LAUNCH_TIMER;
    const pitchBAM = scratchOf(actor).omega2AimPitchBAM ?? 0;
    const pitchRad = pitchBAM * BAM_TO_RAD;
    actor.hSpeed = OMEGA2_X.LAUNCH_SPEED * Math.cos(pitchRad);
    actor.yVel = -OMEGA2_X.LAUNCH_SPEED * Math.sin(pitchRad);
    actor.hDecel = OMEGA2_X.TIMER_FLOOR;
    actor.gravityCoeff = OMEGA2_X.TIMER_FLOOR;
    const target = effLockTarget(actor);
    if (target) {
      const dx = target.x - actor.pos.x;
      const dz = target.z - actor.pos.z;
      if (Math.hypot(dx, dz) > OMEGA2_X.FX_DIST_GATE) {
        ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
      }
    }
  }
}

// Phase 2 — FUN_800f3f50 @ chunk_0026.c:3320. Powered flight + timer/range → advance.
function omega2Phase2(actor: RomActor, _cfg: Omega2XConfig, ctx: Omega2FamilyCtx): void {
  // Re-derive velocity from aim pitch each frame (powered flight)
  computeAimPitch(actor);
  const pitchRad = (scratchOf(actor).omega2AimPitchBAM ?? 0) * BAM_TO_RAD;
  actor.hSpeed = OMEGA2_X.LAUNCH_SPEED * Math.cos(pitchRad);
  actor.yVel = -OMEGA2_X.LAUNCH_SPEED * Math.sin(pitchRad);

  integratePhysics(OMEGA2_X.GRAVITY_PARAM, actor, actor.lockYaw);
  tickStream(actor, 0xf, ctx);

  // Timer countdown + range gate
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= OMEGA2_X.TIMER_FLOOR || targetInRange(actor, OMEGA2_X.RANGE_GATE)) {
    actor.fbPhaseSlots[0] = 3;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 3, slot, OMEGA2_X.STREAM_RATE);
  }
}

// Phase 3 — FUN_800f404c @ chunk_0026.c:3357. Decel + contact gate → advance.
function omega2Phase3(actor: RomActor, _cfg: Omega2XConfig, ctx: Omega2FamilyCtx): void {
  // zz_006ed8c_(0.95, actor) — exponential decel
  decayVelocity(OMEGA2_X.REPOSITION_SCALE, actor);

  integratePhysics(OMEGA2_X.GRAVITY_PARAM, actor, actor.lockYaw);
  tickStream(actor, 0xf, ctx);

  const s = scratchOf(actor);
  const damageByte = s.omega2DamageByte ?? 0;

  if ((damageByte & 0x30) !== 0) {
    // Damage byte 0x30 set → launch toward opposite direction
    actor.hSpeed = OMEGA2_X.DAMAGE_HSPEED;
    actor.hDecel = OMEGA2_X.TIMER_FLOOR;
    actor.yVel = OMEGA2_X.DAMAGE_YVEL;
    actor.lockYaw = toS16(actor.lockYaw - 0x8000);
  } else if (actor.contactP0 >= 0) {
    // +0x1cef >= 0 → stream contact byte says keep waiting
    return;
  }

  // Advance to phase 4
  actor.fbPhaseSlots[0] = 4;
  actor.handlerTimer = OMEGA2_X.SETUP_TIMER;
  if (actor.descriptor) {
    actor.gravityCoeff = actor.descriptor.handlerData6c;
  }
}

// Phase 4 — FUN_800f4104 @ chunk_0026.c:3391. Landing detection → exit.
function omega2Phase4(actor: RomActor, _cfg: Omega2XConfig, ctx: Omega2FamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  integratePhysics(OMEGA2_X.GRAVITY_PARAM, actor, actor.lockYaw);

  const grounded = scratchOf(actor).grounded === true;

  if (grounded) {
    // Landed → landing recovery zz_006a750_(actor, 7) + cooldown seed
    scratchOf(actor).omega2AimPitchBAM = 0;
    actor.controlWord &= ~0x3;
    // zz_006a750_(actor, 7) — landing recovery upper cue
    ctx.onPlayCue?.(actor, 0x2c);
    actor.stateTimer = OMEGA2_X.GRAVITY_PARAM + actor.dt;
    // The ground idle return completes the exit
    romGroundIdleReturn(actor);
  } else {
    // Airborne: wait for timer expiry → air knockout
    actor.handlerTimer -= actor.dt;
    if (actor.handlerTimer <= OMEGA2_X.TIMER_FLOOR) {
      scratchOf(actor).omega2AimPitchBAM = 0;
      actor.controlWord &= ~0x3;
      romAirKnockoutReturn(actor);
    }
  }
}

// ============================================================================
// Dispatcher — zz_00f3cb4_ @chunk_0026.c:3223
// ============================================================================
function createOmega2XHandler(ctx: Omega2FamilyCtx, cfg: Omega2XConfig): (actor: RomActor) => void {
  return (actor) => {
    const s = scratchOf(actor);
    // Prologue: if +0x541 set → drop lock pointer
    if (s.omega2TargetInvalid) {
      s.omega2TargetInvalid = false;
    }
    switch (actor.fbPhaseSlots[0]) {
      case 0: omega2Phase0(actor, cfg, ctx); break;
      case 1: omega2Phase1(actor, cfg, ctx); break;
      case 2: omega2Phase2(actor, cfg, ctx); break;
      case 3: omega2Phase3(actor, cfg, ctx); break;
      case 4: omega2Phase4(actor, cfg, ctx); break;
    }
  };
}

export function createOmega2RootAction(ctx: Omega2FamilyCtx, cfg?: Partial<Omega2XConfig>): (actor: RomActor) => void {
  const config = { ...DEFAULT_OMEGA2_CONFIG, ...cfg };
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                           // 0: dash attack — TODO
    null,                           // 1: B-tap melee — TODO
    createOmega2XHandler(ctx, config), // 2: X-special
    null,                           // 3: B charge — TODO
    null,                           // 4: — TODO
  ];
  return (actor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

export function configureOmega2Family(
  actor: RomActor,
  borgId: "pl040b" | "pl040c" | "pl040d",
  ctx: Omega2FamilyCtx,
  cfg?: Partial<Omega2XConfig>,
): void {
  actor.borgNumber =
    borgId === "pl040b" ? 0x40b :
    borgId === "pl040c" ? 0x40c : 0x40d;
  actor.rootAction = createOmega2RootAction(ctx, cfg);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
