// EAGLE ROBOT / PROTO EAGLE (pl0606/pl061a), constructor 0x80129608.
// Bespoke action-0 variant table 0x80331948 and phase tables:
//   v0   -> 0x8033195c (full-body three-phase burst)
//   v1-3 -> 0x80331968 (directional upper-body three-phase burst)
//   v4   -> 0x80331974 (airborne two-phase lead-in + shared recovery)
// Source: research/decomp/ghidra-export/chunk_0034.c:798-1192.

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { configureEagleFamily } from "./shared-morph-x.js";

export const EAGLE_ROBOT_ACTION0 = {
  AIM_TIMER: 30.0,          // FLOAT_80439d08
  STREAM_RATE: -1.0,        // FLOAT_80439d0c
  ZERO: 0.0,                // FLOAT_80439d10
  REPOSITION: 0.95,         // FLOAT_80439d14
  TRAIL_THRESHOLD: 3.0,     // FLOAT_80439d18
  UPPER_AIM_TIMER: 20.0,    // FLOAT_80439d1c
  GRAVITY: 1.0,             // FLOAT_80439d20
  EAGLE_REPEAT_TIMER: 16.0, // FLOAT_80439d24
  PROTO_REPEAT_TIMER: 2.0,  // FLOAT_80439d28
  EXIT_CUE: 0x10,
  STREAM_GROUP: 2,
} as const;

export interface EagleRobotScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  /** ROM +0x560, separate from +0x558 handlerTimer. */
  eagleAimTimer?: number;
  /** ROM +0x6ee/+0x6ef. */
  eagleStreamSeed?: number;
  eagleAmmoCount?: number;
  /** Host surface for zz_006d0dc_/zz_006dee8_ aim completion. */
  eagleAimReady?: boolean;
  /** ROM +0x5b4 bit 0x200 plus negative +0x1cef repeat event. */
  eagleRepeatRequested?: boolean;
  /** Directional stream selector corresponding to +0x1d10. */
  eagleDirectionIndex?: number;
  streamTickGate?: boolean;
  housekeeping73f?: number;
}

export type EagleRobotBorgId = "pl0606" | "pl061a";

function repeatTimer(actor: RomActor): number {
  return actor.borgNumber === 0x61a
    ? EAGLE_ROBOT_ACTION0.PROTO_REPEAT_TIMER
    : EAGLE_ROBOT_ACTION0.EAGLE_REPEAT_TIMER;
}

function firePair(actor: RomActor & EagleRobotScratch, ctx: StreamContext): void {
  actor.eagleStreamSeed = 1;
  actor.eagleAimTimer = EAGLE_ROBOT_ACTION0.UPPER_AIM_TIMER;
  actor.handlerTimer = repeatTimer(actor);
  actor.eagleAmmoCount = Math.max(0, (actor.eagleAmmoCount ?? 1) - 1);
  if (actor.borgNumber === 0x606) {
    ctx.onFamilyProjectile?.(actor, 0x800c3be0, 0x1e);
    ctx.onFamilyProjectile?.(actor, 0x800c3be0, 0x1f);
  } else {
    ctx.onFamilyProjectile?.(actor, 0x80082824, 0x6e);
    ctx.onFamilyProjectile?.(actor, 0x80082824, 0x6f);
  }
}

function canRepeat(actor: RomActor & EagleRobotScratch): boolean {
  return actor.eagleRepeatRequested === true && (actor.eagleAmmoCount ?? 0) > 0;
}

function finishGround(actor: RomActor & EagleRobotScratch): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;
  romGroundIdleReturn(actor);
}

function fullBodyBurst(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & EagleRobotScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: { // FUN_801299e4
        actor.fbPhaseSlots[0] = 1;
        actor.eagleAimTimer = EAGLE_ROBOT_ACTION0.AIM_TIMER;
        startStream(actor, 0xf, EAGLE_ROBOT_ACTION0.STREAM_GROUP,
          actor.eagleStreamSeed ?? 0, EAGLE_ROBOT_ACTION0.STREAM_RATE);
        actor.controlWord &= ~0xb0;
        actor.hSpeed = actor.yVel = actor.hDecel = actor.gravityCoeff = 0;
        if (actor.lockTarget) {
          vecSubtract(actor.pos, actor.lockTarget, actor.motion);
          vecScale(EAGLE_ROBOT_ACTION0.REPOSITION, actor.motion, actor.motion);
          vecAdd(actor.pos, actor.motion, actor.pos);
        }
        return;
      }
      case 1: // FUN_80129ac4
        tickStream(actor, 0xf, ctx);
        actor.eagleAimTimer = (actor.eagleAimTimer ?? 0) - actor.dt;
        if (actor.contactP0 !== 0 && (actor.eagleAimReady === true || (actor.eagleAimTimer ?? 0) <= 0)) {
          actor.fbPhaseSlots[0] = 2;
          firePair(actor, ctx);
        }
        vecScale(EAGLE_ROBOT_ACTION0.REPOSITION, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
        return;
      case 2: // FUN_80129bc8
        tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        if (actor.handlerTimer > 0) return;
        if (canRepeat(actor)) {
          actor.eagleRepeatRequested = false;
          actor.fbPhaseSlots[0] = 1;
          startStream(actor, 0xf, EAGLE_ROBOT_ACTION0.STREAM_GROUP, 1,
            EAGLE_ROBOT_ACTION0.STREAM_RATE);
          return;
        }
        finishGround(actor);
        return;
      default: return;
    }
  };
}

function directionalSlot(actor: RomActor & EagleRobotScratch): number {
  let slot = 4;
  if ((actor.controlWord & 0x80) !== 0) slot = 6;
  if ((actor.controlWord & 0x10) !== 0) slot = 2;
  if ((actor.controlWord & 0x20) !== 0) slot = (actor.eagleDirectionIndex ?? 0) + 8;
  return slot + (actor.eagleStreamSeed ?? 0);
}

function upperBodyBurst(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & EagleRobotScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: // FUN_80129da8
        actor.fbPhaseSlots[0] = 1;
        actor.eagleAimTimer = EAGLE_ROBOT_ACTION0.UPPER_AIM_TIMER;
        startStream(actor, 1, EAGLE_ROBOT_ACTION0.STREAM_GROUP, directionalSlot(actor),
          EAGLE_ROBOT_ACTION0.STREAM_RATE);
        return;
      case 1: // FUN_80129e58
        if (actor.contactP0 === 0 || actor.streamTickGate !== false) tickStream(actor, 1, ctx);
        actor.eagleAimTimer = (actor.eagleAimTimer ?? 0) - actor.dt;
        if (actor.contactP0 !== 0 && (actor.eagleAimReady === true || (actor.eagleAimTimer ?? 0) <= 0)) {
          actor.fbPhaseSlots[0] = 2;
          firePair(actor, ctx);
        }
        return;
      case 2: // FUN_80129f40
        tickStream(actor, 1, ctx);
        actor.handlerTimer -= actor.dt;
        if (actor.handlerTimer > 0) return;
        if (canRepeat(actor)) {
          actor.eagleRepeatRequested = false;
          actor.fbPhaseSlots[0] = 1;
          startStream(actor, 1, EAGLE_ROBOT_ACTION0.STREAM_GROUP, directionalSlot(actor),
            EAGLE_ROBOT_ACTION0.STREAM_RATE);
          return;
        }
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        dispatchFullBodyCue(actor, EAGLE_ROBOT_ACTION0.EXIT_CUE);
        return;
      default: return;
    }
  };
}

function airborneBurst(ctx: StreamContext, recovery: (actor: RomActor) => void): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & EagleRobotScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: // FUN_8012a170
        actor.fbPhaseSlots[0] = 1;
        actor.eagleAimTimer = EAGLE_ROBOT_ACTION0.AIM_TIMER;
        integratePhysics(EAGLE_ROBOT_ACTION0.GRAVITY, actor, actor.lockYaw);
        startStream(actor, 1, EAGLE_ROBOT_ACTION0.STREAM_GROUP,
          (actor.eagleStreamSeed ?? 0) + 6, EAGLE_ROBOT_ACTION0.STREAM_RATE);
        startStream(actor, 2, 0, 0xd, EAGLE_ROBOT_ACTION0.STREAM_RATE);
        return;
      case 1: // FUN_8012a220
        if (actor.contactP0 === 0 || actor.streamTickGate !== false) tickStream(actor, 0xf, ctx);
        integratePhysics(EAGLE_ROBOT_ACTION0.GRAVITY, actor, actor.lockYaw);
        actor.eagleAimTimer = (actor.eagleAimTimer ?? 0) - actor.dt;
        if (actor.contactP0 !== 0 && (actor.eagleAimReady === true || (actor.eagleAimTimer ?? 0) <= 0)) {
          actor.fbPhaseSlots[0] = 2;
          firePair(actor, ctx);
          actor.controlWord &= ~0x2;
          romAirKnockoutReturn(actor);
        }
        return;
      case 2:
        recovery(actor);
        return;
      default: return;
    }
  };
}

export function createEagleRobotAction0(ctx: StreamContext): (actor: RomActor) => void {
  const full = fullBodyBurst(ctx);
  const upper = upperBodyBurst(ctx);
  const air = airborneBurst(ctx, upper);
  return (actor: RomActor): void => {
    if (actor.variantIndex === 0) full(actor);
    else if (actor.variantIndex < 4) upper(actor);
    else air(actor);
  };
}

export function configureEagleRobotFamily(
  actor: RomActor,
  borgId: EagleRobotBorgId,
  ctx: StreamContext,
): void {
  let morphAction: ((actor: RomActor) => void) | null = null;
  if (borgId === "pl0606") {
    configureEagleFamily(actor, "pl0606", ctx);
    morphAction = actor.rootAction;
  }
  actor.borgNumber = borgId === "pl0606" ? 0x606 : 0x61a;
  const action0 = createEagleRobotAction0(ctx);
  actor.rootAction = (a: RomActor): void => {
    if (a.actionIndex === 0) action0(a);
    else morphAction?.(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
