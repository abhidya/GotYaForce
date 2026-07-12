// ARROW NINJA / SHIJIMA (pl0002/pl000b), constructor 0x800cfe9c.
// Action 1 variant routing at 0x8030de28:
//   v0 -> shared zz_00fed6c_ (config 0x8030de3c)
//   v1/v2 -> FUN_800d0d14, phase table 0x8030de54
//   v3/v4 -> FUN_800d117c, phase table 0x8030de64
// Source: research/decomp/ghidra-export/chunk_0022.c:315-634.

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn } from "./shared-idle-return.js";
import { createSharedMeleeLunge, type SharedLungeConfig } from "./shared-melee-lunge.js";
import {
  isStreamTickEnabled,
  stepTargetYaw,
  targetPitchBam,
} from "../rom/helpers.js";

export const ARROW_NINJA_ACTION1 = {
  GRAVITY: 1.0,          // FLOAT_804389f0
  ZERO: 0.0,             // FLOAT_804389f4
  LAUNCH_SPEED: 40.0,    // FLOAT_80438a10
  STREAM_RATE: -1.0,     // FLOAT_80438a20
  AIR_DIVE_SPEED: 30.0,  // FLOAT_80438a28
  AIM_TIMER: 60.0,       // FLOAT_80438a2c
  REPOSITION: 0.95,      // FLOAT_80438a30
  DASH_TIMER: 20.0,      // FLOAT_80438a34
  TRAIL_THRESHOLD: 3.0,  // FLOAT_80438a38
  RANGE: 150.0,          // FLOAT_80438a3c
  DECEL: 0.9,            // FLOAT_80438a40
  EXIT_COOLDOWN: 4.0,    // FLOAT_80438a44
  DIVE_RANGE: 250.0,     // FLOAT_80438a4c
  STREAM_GROUP: 3,
} as const;

/** Config @0x8030de3c: 0, 150.0, 20, 0.95, 0.95, 0.8. */
export const ARROW_NINJA_SHARED_LUNGE_CONFIG: SharedLungeConfig = {
  slotBase: 0,
  range: 150,
  dashFrames: 20,
  decelA: 0.95,
  decelB: 0.95,
  decelC: 0.8,
};

export interface ArrowNinjaScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  rangeRows868?: readonly [number, number, number];
  /** ROM +0x1d9 nonzero: phase-3 braking input. */
  arrowBrakeEvent?: boolean;
  /** ROM +0x71c: suppresses the ground-chain recovery body. */
  arrowRecoverySuppressed?: boolean;
  /** ROM +0x1d0f signed stream event. */
  arrowStreamEvent?: number;
  /** Host collision result corresponding to zz_00677b0_. */
  grounded?: boolean;
  housekeeping73f?: number;
  /** Optional exact homing pitch written to +0x54e by zz_006e6c4_. */
  divePitchBam?: number;
}

function targetDistance(actor: RomActor & ArrowNinjaScratch): number | null {
  const target = actor.lockTarget;
  if (!target) return null;
  return Math.hypot(target.x - actor.pos.x, target.y - actor.pos.y, target.z - actor.pos.z);
}

function rangeRow(actor: RomActor & ArrowNinjaScratch, offset = 0): number {
  return actor.rangeRows868?.[Math.abs(actor.prevActionIndex) % 3] ??
    (offset === 0 ? ARROW_NINJA_ACTION1.RANGE : ARROW_NINJA_ACTION1.DIVE_RANGE);
}

function groundChain(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & ArrowNinjaScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: { // FUN_800d0d64
        actor.fbPhaseSlots[0] = 1;
        actor.handlerTimer = ARROW_NINJA_ACTION1.AIM_TIMER;
        actor.streamSlot = 3;
        if (!actor.lockTarget || (targetDistance(actor) ?? Infinity) > rangeRow(actor)) {
          actor.activeYaw = actor.lockYaw;
        }
        stepTargetYaw(actor, 0xc0);
        if (actor.lockTarget) {
          vecSubtract(actor.pos, actor.lockTarget, actor.motion);
          vecScale(ARROW_NINJA_ACTION1.REPOSITION, actor.motion, actor.motion);
          vecAdd(actor.pos, actor.motion, actor.pos);
        }
        const slot = actor.streamSlot++;
        startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, slot,
          ARROW_NINJA_ACTION1.STREAM_RATE);
        return;
      }
      case 1: { // FUN_800d0e7c
        if (isStreamTickEnabled(actor)) tickStream(actor, 0xf, ctx);
        vecScale(ARROW_NINJA_ACTION1.REPOSITION, actor.motion, actor.motion);
        vecAdd(actor.pos, actor.motion, actor.pos);
        actor.handlerTimer -= actor.dt;
        const facingReady = stepTargetYaw(actor, 0xc0);
        if (actor.handlerTimer <= 0 || facingReady) {
          actor.fbPhaseSlots[0] = 2;
          actor.handlerTimer = ARROW_NINJA_ACTION1.DASH_TIMER;
          let distance = rangeRow(actor);
          const live = targetDistance(actor);
          if (live !== null && live < distance) distance = live;
          actor.hSpeed = distance / ARROW_NINJA_ACTION1.DASH_TIMER;
          actor.hDecel = 0;
          ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
        }
        return;
      }
      case 2: { // FUN_800d0fb0
        stepTargetYaw(actor, 0xc0);
        if (actor.contactP0 === 0 || isStreamTickEnabled(actor)) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        const distance = targetDistance(actor);
        if (actor.handlerTimer <= 0 || (distance !== null && distance <= ARROW_NINJA_ACTION1.RANGE)) {
          actor.fbPhaseSlots[0] = 3;
          actor.hSpeed = ARROW_NINJA_ACTION1.LAUNCH_SPEED;
          actor.hDecel = 0;
          actor.yVel = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED;
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
          const slot = actor.streamSlot++;
          startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, slot,
            ARROW_NINJA_ACTION1.STREAM_RATE);
        }
        return;
      }
      case 3: // FUN_800d10b4
        if (actor.arrowBrakeEvent) {
          actor.hSpeed *= ARROW_NINJA_ACTION1.DECEL;
          actor.yVel *= ARROW_NINJA_ACTION1.DECEL;
        }
        if (actor.arrowRecoverySuppressed) return;
        tickStream(actor, 0xf, ctx);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.wallContact !== 0) {
          actor.lockYaw = actor.activeYaw;
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          romAirKnockoutReturn(actor);
          actor.stateTimer = ARROW_NINJA_ACTION1.EXIT_COOLDOWN + actor.dt;
        }
        return;
      default: return;
    }
  };
}

function diveVelocity(actor: RomActor & ArrowNinjaScratch): void {
  const pitch = actor.divePitchBam ?? targetPitchBam(actor) ?? 0;
  actor.divePitchBam = pitch;
  const angle = (pitch & 0xffff) * Math.PI * 2 / 0x10000;
  actor.hSpeed = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED * Math.cos(angle);
  actor.yVel = -ARROW_NINJA_ACTION1.AIR_DIVE_SPEED * Math.sin(angle);
}

function airDive(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as RomActor & ArrowNinjaScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: // FUN_800d11cc
        actor.fbPhaseSlots[0] = 1;
        actor.hSpeed = actor.yVel = actor.hDecel = actor.gravityCoeff = 0;
        actor.handlerTimer = ARROW_NINJA_ACTION1.AIR_DIVE_SPEED;
        actor.streamSlot = 3;
        ctx.onFamilyProjectile?.(actor, 0x80092dcc, 0);
        startStream(actor, 0xf, ARROW_NINJA_ACTION1.STREAM_GROUP, 2,
          ARROW_NINJA_ACTION1.STREAM_RATE);
        return;
      case 1: { // FUN_800d12b4
        diveVelocity(actor);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        const distance = targetDistance(actor);
        if (actor.handlerTimer <= 0 || (distance !== null && distance <= ARROW_NINJA_ACTION1.DIVE_RANGE)) {
          actor.fbPhaseSlots[0] += 2; // ROM intentionally skips phase 2.
        }
        return;
      }
      case 2: // FUN_800d1404 (reachable through external phase rewrites)
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
        actor.handlerTimer -= actor.dt;
        if (actor.handlerTimer <= 0) {
          actor.fbPhaseSlots[0] = 3;
          diveVelocity(actor);
        }
        return;
      case 3: // FUN_800d14bc
        tickStream(actor, 0xf, ctx);
        if ((actor.arrowStreamEvent ?? 0) < 0) {
          actor.arrowStreamEvent = 0;
          actor.yVel = Math.min(actor.yVel, 0);
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
        }
        actor.hSpeed *= Math.pow(ARROW_NINJA_ACTION1.REPOSITION, actor.dt);
        actor.yVel *= Math.pow(ARROW_NINJA_ACTION1.REPOSITION, actor.dt);
        integratePhysics(ARROW_NINJA_ACTION1.GRAVITY, actor, actor.activeYaw);
        if ((actor.grounded === true && actor.contactP0 < 0) || actor.wallContact !== 0) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          if (actor.grounded === true && actor.contactP0 < 0) dispatchUpperBodyCue(actor, 7);
          else romAirKnockoutReturn(actor);
          actor.stateTimer = ARROW_NINJA_ACTION1.GRAVITY + actor.dt;
        }
        return;
      default: return;
    }
  };
}

export type ArrowNinjaBorgId = "pl0002" | "pl000b";

export function configureArrowNinjaFamily(
  actor: RomActor,
  borgId: ArrowNinjaBorgId,
  ctx: StreamContext,
): void {
  const shared = createSharedMeleeLunge(ARROW_NINJA_SHARED_LUNGE_CONFIG, ctx);
  const ground = groundChain(ctx);
  const air = airDive(ctx);
  actor.borgNumber = borgId === "pl0002" ? 0x002 : 0x00b;
  actor.rootAction = (a: RomActor): void => {
    if (a.actionIndex !== 1) return;
    if (a.variantIndex === 0) shared(a);
    else if (a.variantIndex <= 2) ground(a);
    else air(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
