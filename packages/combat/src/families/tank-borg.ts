// Tank Borg family (pl0c00-pl0c06).
//
// NORMAL TANK / LEOPARD (pl0c00/pl0c06) use the bespoke constructor at
// 0x8007ca5c. Their action machines are ported from chunk_0011.c:
//   action 0: FUN_8007cd24 / FUN_8007d070, tables 0x802d6a84/0x802d6a98
//   action 2 v0: FUN_8007d3f4, table 0x802d6aac (8 phases)
//   action 2 v1: FUN_8007d6c4, table 0x802d6abc (4 phases + flight wrapper)
// The other tank constructors remain code-driven/unported and deliberately no-op.

import type { RomActor, Vec3 } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

export const NORMAL_TANK = {
  WINDUP_A: 15,
  WINDUP_B: 10,
  BURST_INTERVAL: 5,
  SHORT_BURST: 3,
  LONG_BURST: 5,
  RECOVERY: 30,
  ACTION0_EXIT_CUE: 0x10,
  ACTION2_AIM_TIMER: 30.0,       // FLOAT_80437988
  STREAM_RATE: -1.0,             // FLOAT_8043798c
  ZERO: 0.0,                     // FLOAT_80437990
  FLIGHT_GRAVITY: 1.0,           // FLOAT_80437994
  AIR_HORIZONTAL_SPEED: 10.0,    // FLOAT_80437998
  AIR_HORIZONTAL_DECEL: -0.3,    // FLOAT_8043799c
  AIM_MIN: -0x3800,
  AIM_MAX: 0x1800,
  AIM_STEP: 0x180,
  AIM_SNAP: 0xc0,
  STREAM_GROUP: 4,
  STREAM_SLOT: 0,
  STREAM_MASK: 3,
  SHOT_HELPER: 0x80082824,
} as const;

/** Port-side mirrors for fields/collision queries not yet first-class on RomActor. */
export interface NormalTankScratch {
  /** Two target vectors at ROM +0xa30/+0xa90; the nearer selects barrel side. */
  tankTargetVectors?: readonly [Vec3, Vec3];
  /** Result of zz_007da18_'s two-barrel readiness test. */
  tankBarrelsReady?: boolean;
  /** ROM +0x5b4 bit 0x200: extends a burst from three shots to five. */
  tankLongBurst?: boolean;
  /** ROM +0x144 turret pitch and zz_00853ec_(actor,2) target pitch. */
  tankTurretPitch?: number;
  tankDesiredPitch?: number;
  /** FUN_800669d0(actor,0xc1) completion bit. */
  tankYawReady?: boolean;
  /** ROM +0x541 one-shot latch. */
  tankEntryLatch?: number;
  /** ROM +0x73f housekeeping byte. */
  housekeeping73f?: number;
  /** ROM +0x146 aiming enable byte. */
  tankAimEnabled?: number;
  /** ROM +0x709 landing/collision flag. */
  tankLandedFlag?: number;
}

interface TankConfig {
  bespokeNormalTank: boolean;
}

const TANK_CONFIGS = {
  pl0c00: { bespokeNormalTank: true },
  pl0c01: { bespokeNormalTank: false },
  pl0c02: { bespokeNormalTank: false },
  pl0c04: { bespokeNormalTank: false },
  pl0c05: { bespokeNormalTank: false },
  pl0c06: { bespokeNormalTank: true },
} as const satisfies Record<string, TankConfig>;

const TANK_BORG_NUMBERS: Record<string, number> = {
  pl0c00: 0xc00, pl0c01: 0xc01, pl0c02: 0xc02,
  pl0c04: 0xc04, pl0c05: 0xc05, pl0c06: 0xc06,
};

export type TankBorgId = keyof typeof TANK_CONFIGS;

function nearestBarrel(actor: RomActor & NormalTankScratch): number {
  const vectors = actor.tankTargetVectors;
  if (!vectors) return 0;
  const distance2 = (v: Vec3): number => {
    const x = actor.pos.x - v.x;
    const y = actor.pos.y - v.y;
    const z = actor.pos.z - v.z;
    return x * x + y * y + z * z;
  };
  return distance2(vectors[1]) < distance2(vectors[0]) ? 1 : 0;
}

function fireTurretShot(actor: RomActor, side: number, ctx: StreamContext): void {
  // zz_006dbe0_(actor,0,1,1) is the ammo gate. Resource ownership remains in the
  // host; the family callback is the exact zz_0082824_(actor, side ? 2 : 3) call.
  ctx.onFamilyProjectile?.(actor, NORMAL_TANK.SHOT_HELPER, side === 0 ? 3 : 2);
}

/** Action 0, shared by both variant tables (the tables contain byte-identical phases). */
export function createNormalTankAction0(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & NormalTankScratch;
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: // 0x8007cd60 / 0x8007d0ac
        actor.fbPhaseSlots[0] = 1;
        actor.stateTimer = NORMAL_TANK.WINDUP_A;
        return;
      case 1: // 0x8007cd78 / 0x8007d0c4
        actor.fbPhaseSlots[0] = 2;
        actor.stateTimer = NORMAL_TANK.WINDUP_B;
        return;
      case 2: { // FUN_8007cd90 / FUN_8007d0dc
        actor.stateTimer -= actor.dt;
        if (actor.stateTimer < 1 || actor.tankBarrelsReady === true) {
          actor.fbPhaseSlots[0] = 3;
          actor.stateTimer = 0;
          actor.handlerTimer = 0; // ROM +0x54a
          actor.motion.x = 0;     // port mirror for ROM +0x54c burst count
        }
        return;
      }
      case 3: { // FUN_8007ce84 / FUN_8007d1d0
        const side = nearestBarrel(actor);
        if (actor.tankLongBurst === true) actor.stateTimer = 1;
        if (actor.handlerTimer > 0) {
          actor.handlerTimer -= actor.dt;
          return;
        }
        actor.handlerTimer = NORMAL_TANK.BURST_INTERVAL;
        actor.motion.x += 1;
        fireTurretShot(actor, side, ctx);
        const limit = actor.stateTimer === 0 ? NORMAL_TANK.SHORT_BURST : NORMAL_TANK.LONG_BURST;
        if (actor.motion.x >= limit) {
          actor.fbPhaseSlots[0] = 4;
          actor.stateTimer = NORMAL_TANK.RECOVERY;
        }
        return;
      }
      case 4: // FUN_8007d020 / FUN_8007d36c
        actor.stateTimer -= actor.dt;
        if (actor.stateTimer < 1) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          dispatchFullBodyCue(actor, NORMAL_TANK.ACTION0_EXIT_CUE);
        }
        return;
      default:
        return;
    }
  };
}

function streamEnded(actor: RomActor, mask: number): boolean {
  for (let i = 0; i < actor.parts.length; i++) {
    if ((mask & (1 << i)) !== 0 && actor.parts[i]!.streamPtr >= 0) return false;
  }
  return true;
}

function beginTankX(actor: RomActor, airborne: boolean): void {
  actor.fbPhaseSlots[0] += 1;
  actor.handlerTimer = NORMAL_TANK.ACTION2_AIM_TIMER;
  startStream(actor, NORMAL_TANK.STREAM_MASK, NORMAL_TANK.STREAM_GROUP,
    NORMAL_TANK.STREAM_SLOT, NORMAL_TANK.STREAM_RATE);
  if (airborne) actor.controlWord |= 0x40;
  actor.gravityCoeff = NORMAL_TANK.ZERO;
}

function aimTankX(actor: RomActor & NormalTankScratch, ctx: StreamContext): void {
  actor.tankAimEnabled = 1;
  let desired = actor.tankDesiredPitch ?? 0;
  desired = Math.max(NORMAL_TANK.AIM_MIN, Math.min(NORMAL_TANK.AIM_MAX, desired));
  let pitch = actor.tankTurretPitch ?? 0;
  if (pitch < desired) pitch = Math.min(desired, pitch + NORMAL_TANK.AIM_STEP);
  else if (pitch > desired) pitch = Math.max(desired, pitch - NORMAL_TANK.AIM_STEP);
  if (Math.abs(pitch - desired) <= NORMAL_TANK.AIM_SNAP) pitch = desired;
  actor.tankTurretPitch = pitch;
  actor.handlerTimer -= actor.dt;
  if ((actor.tankYawReady === true && pitch === desired) || actor.handlerTimer <= 0) {
    actor.fbPhaseSlots[0] += 1;
    actor.tankEntryLatch = 0;
  }
  tickStream(actor, 0xf, ctx); // ROM ticks mask 0xf while aiming.
}

function fireTankX(actor: RomActor & NormalTankScratch, airborne: boolean, ctx: StreamContext): void {
  if (actor.tankEntryLatch !== 1) {
    actor.tankEntryLatch = 1;
    if (airborne) {
      actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
      actor.hSpeed = NORMAL_TANK.AIR_HORIZONTAL_SPEED;
      actor.hDecel = NORMAL_TANK.AIR_HORIZONTAL_DECEL;
      actor.yVel = NORMAL_TANK.AIR_HORIZONTAL_SPEED;
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? NORMAL_TANK.ZERO;
    }
    ctx.onFamilyProjectile?.(actor, 0x80084600, 2);
    actor.tankAimEnabled = 0;
  }
  if (!airborne && actor.contactP0 === 1) {
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
    actor.contactP0 = 0;
  }
  tickStream(actor, NORMAL_TANK.STREAM_MASK, ctx);
  if (streamEnded(actor, NORMAL_TANK.STREAM_MASK)) actor.fbPhaseSlots[0] += 1;
}

/** Action 2 v0: grounded four-phase attack followed by its airborne four-phase arm. */
export function createNormalTankAction2Variant0(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & NormalTankScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: beginTankX(actor, false); return;
      case 1: aimTankX(actor, ctx); return;
      case 2: fireTankX(actor, false, ctx); return;
      case 3:
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romGroundIdleReturn(actor);
        return;
      case 4: beginTankX(actor, true); return;
      case 5: aimTankX(actor, ctx); return;
      case 6: fireTankX(actor, true, ctx); return;
      case 7:
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor);
        return;
      default: return;
    }
  };
}

/** Action 2 v1: the ROM enters directly at the airborne four-phase subtable. */
export function createNormalTankAction2Variant1(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & NormalTankScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: beginTankX(actor, true); break;
      case 1: aimTankX(actor, ctx); break;
      case 2: fireTankX(actor, true, ctx); break;
      case 3:
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor);
        break;
      default: break;
    }
    integratePhysics(NORMAL_TANK.FLIGHT_GRAVITY, actor, actor.lockYaw);
    if ((actor as NormalTankScratch).tankLandedFlag === 1) {
      (actor as NormalTankScratch).tankLandedFlag = 0;
      if ((actor as NormalTankScratch).tankEntryLatch !== 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor);
      }
    }
  };
}

export function createTankRootAction(borgId: TankBorgId, ctx: StreamContext): (actor: RomActor) => void {
  if (!TANK_CONFIGS[borgId].bespokeNormalTank) return () => {};
  const action0 = createNormalTankAction0(ctx);
  const action2v0 = createNormalTankAction2Variant0(ctx);
  const action2v1 = createNormalTankAction2Variant1(ctx);
  return (actor: RomActor): void => {
    if (actor.actionIndex === 0) action0(actor);
    else if (actor.actionIndex === 2) (actor.variantIndex === 0 ? action2v0 : action2v1)(actor);
  };
}

export function configureTankFamily(actor: RomActor, borgId: TankBorgId, ctx: StreamContext): void {
  actor.borgNumber = TANK_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createTankRootAction(borgId, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
