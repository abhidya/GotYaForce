// G RED family action 0 — exact dispatcher/table transcription of zz_018d288_.
//
// Root: 0x8018d288, variant table 0x8036559c:
//   v0 -> 0x8018d308 -> phases [0x8018d350, 0x8018d438, 0x8018d534]
//   v1/v2/v3 -> 0x8018d6f0 -> [0x8018d72c, 0x8018d7e4, 0x8018d8c0]
//   v4 -> 0x8018dab4 -> [0x8018dafc, 0x8018dbb4, 0x8018d8c0]
// Source: ghidra-export/chunk_0046.c:5069 through chunk_0047.c:228.

import type { RomActor, Vec3 } from "../rom/actor.js";
import {
  allocateWeapon,
  stepTargetRoll,
  stepTargetYaw,
  toS16,
} from "../rom/helpers.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

export const GRED_DASH = {
  ZERO: 0.0,                  // FLOAT_8043b110
  ROOT_ROLL_DECAY: 0.96,      // FLOAT_8043b118; +0x1900 every action tick
  AIM_TIMER: 30.0,            // FLOAT_8043b11c; actor+0x560
  REAIM_TIMER: 20.0,          // FLOAT_8043b12c; actor+0x560 after zz_018dcb0_
  REPEAT_G_RED: 12.0,         // FLOAT_8043b134; actor+0x558
  REPEAT_NEO_G_RED: 8.0,      // FLOAT_8043b138
  REPEAT_G_BLACK: 16.0,       // FLOAT_8043b13c
  MOTION_DECAY: 0.95,         // FLOAT_8043b124
  AFTERIMAGE_THRESHOLD: 3.0, // FLOAT_8043b128 (zz_00b22f4_, renderer-side)
  STREAM_RATE: -1.0,          // FLOAT_8043b120
  EXIT_COOLDOWN: 20.0,        // zz_006a668_(actor, 0x14)
  CONTROL_CLEAR_P0: 0xb0,
  ACTION_MODE_BITS: 0x3,
  PROJECTILE_SPAWNER: 0x800c3be0,
} as const;

interface GRedDashScratch {
  lockTarget?: Vec3 | null;
  grounded?: boolean;
  /** actor+0x560 — deliberately separate from RomActor.handlerTimer (+0x558). */
  dashAimTimer560?: number;
  /** actor+0x745 continuation latch. */
  dashLatch745?: boolean;
  /** actor+0x5d4 and +0x5d8 host input/status words. */
  inputFlags5d4?: number;
  inputFlags5d8?: number;
  /** actor+0x5e4 movement context and +0x1d10 stream-authored branch byte. */
  movementMode5e4?: number;
  streamBranch1d10?: number;
  /** Unsurfaced s16 aim accumulators decayed by the wrappers. */
  aimPitch18da?: number;
  aimPitch1900?: number;
  aimRoll1dfc?: number;
  /** Unsurfaced cleanup bytes retained so traces can compare them. */
  dashHousekeep6e8?: number;
  dashHousekeep73f?: number;
  /** +0x6ef child/projectile repeat count. */
  dashProjectilesRemaining?: number;
}

function scratch(actor: RomActor): RomActor & GRedDashScratch {
  return actor as RomActor & GRedDashScratch;
}

function streamSignalled(actor: RomActor): boolean {
  return actor.contactP0 !== 0 || actor.parts[0]!.streamPtr < 0;
}

function tickPreservingDtOnSignal(actor: RomActor, mask: number, ctx: StreamContext): void {
  const dt = actor.dt;
  if (actor.contactP0 !== 0) actor.dt = 0;
  tickStream(actor, mask, ctx);
  actor.dt = dt;
}

function decayMotionAndAdvance(actor: RomActor): void {
  actor.motion.x *= GRED_DASH.MOTION_DECAY;
  actor.motion.y *= GRED_DASH.MOTION_DECAY;
  actor.motion.z *= GRED_DASH.MOTION_DECAY;
  actor.pos.x += actor.motion.x;
  actor.pos.y += actor.motion.y;
  actor.pos.z += actor.motion.z;
  // zz_00679d0_ performs the host collision/ground snap. RomDriverBridge applies the
  // stage clamp after the handler; zz_00b22f4_ above magnitude 3 is afterimage FX only.
}

function repeatFrames(actor: RomActor): number {
  if (actor.borgNumber === 0x629) return GRED_DASH.REPEAT_NEO_G_RED;
  if (actor.borgNumber === 0x62a) return GRED_DASH.REPEAT_G_BLACK;
  return GRED_DASH.REPEAT_G_RED;
}

/** zz_018dcb0_: re-arm the dash projectile/repeat window after a stream signal. */
function rearmDash(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  s.dashAimTimer560 = GRED_DASH.REAIM_TIMER;
  actor.streamSlot = 1;
  actor.handlerTimer = repeatFrames(actor);
  if (allocateWeapon(actor, ctx, 0, 1, true)) {
    const type = actor.borgNumber === 0x629 ? 0x65 : actor.borgNumber === 0x62a ? 0x66 : 0x2b;
    ctx.onFamilyProjectile?.(actor, GRED_DASH.PROJECTILE_SPAWNER, type);
    s.dashProjectilesRemaining = (s.dashProjectilesRemaining ?? 0) - 1;
  }
  // The ROM forces +0x6ef to zero when child-count +0x774 is empty. The host owns
  // child lifetime; a negative synthetic count is normalized to zero here.
  if ((s.dashProjectilesRemaining ?? 0) < 0) s.dashProjectilesRemaining = 0;
}

function finishDash(actor: RomActor): void {
  const s = scratch(actor);
  s.dashHousekeep6e8 = 0;
  s.dashHousekeep73f = 0;
  actor.controlWord &= ~GRED_DASH.ACTION_MODE_BITS;
  romGroundIdleReturn(actor); // zz_006a474_
  actor.stateTimer = Math.max(actor.stateTimer, GRED_DASH.EXIT_COOLDOWN); // zz_006a668_(..., 0x14)
}

function restartVariant(actor: RomActor, variant: number): void {
  actor.variantIndex = variant;
  actor.fbPhaseSlots[0] = 0;
}

// v0 machine -----------------------------------------------------------------

function dashV0Phase0(actor: RomActor): void {
  const s = scratch(actor);
  actor.fbPhaseSlots[0] = 1;
  s.dashLatch745 = false;
  s.dashAimTimer560 = GRED_DASH.AIM_TIMER;
  stepTargetYaw(actor, 0xc1);
  startStream(actor, 0xf, 2, actor.streamSlot, GRED_DASH.STREAM_RATE);
  actor.controlWord &= ~GRED_DASH.CONTROL_CLEAR_P0;
  actor.gravityCoeff = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  actor.hSpeed = 0;
  const target = s.lockTarget;
  if (target) {
    actor.motion.x = (actor.pos.x - target.x) * GRED_DASH.MOTION_DECAY;
    actor.motion.y = (actor.pos.y - target.y) * GRED_DASH.MOTION_DECAY;
    actor.motion.z = (actor.pos.z - target.z) * GRED_DASH.MOTION_DECAY;
    actor.pos.x += actor.motion.x;
    actor.pos.y += actor.motion.y;
    actor.pos.z += actor.motion.z;
  }
}

function dashV0Phase1(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  tickPreservingDtOnSignal(actor, 0xf, ctx);
  const ready = stepTargetYaw(actor, 0xc1);
  s.dashAimTimer560 = (s.dashAimTimer560 ?? GRED_DASH.AIM_TIMER) - actor.dt;
  if ((ready || s.dashAimTimer560 <= 0) && streamSignalled(actor)) {
    actor.fbPhaseSlots[0] = 2;
    rearmDash(actor, ctx);
  }
  decayMotionAndAdvance(actor);
}

function dashV0Phase2(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  if (((s.inputFlags5d4 ?? 0) & 0x20) !== 0) s.dashLatch745 = true;
  tickStream(actor, 0xf, ctx);
  if (actor.handlerTimer > 0) {
    actor.handlerTimer -= actor.dt;
  } else if (s.dashLatch745 && allocateWeapon(actor, ctx, 0, 1, false)) {
    s.dashLatch745 = false;
    actor.fbPhaseSlots[0] = 1;
    startStream(actor, 0xf, 2, 1, GRED_DASH.STREAM_RATE);
    return;
  }
  const exit = ((s.inputFlags5d8 ?? 0) & 0xf0) !== 0
    || ((s.inputFlags5d4 ?? 0) & 1) !== 0
    || actor.wallContact !== 0;
  if (exit) {
    finishDash(actor);
    return;
  }
  decayMotionAndAdvance(actor);
}

// v1/v2/v3 machine -----------------------------------------------------------

function variant123Slot(actor: RomActor): number {
  const s = scratch(actor);
  let slot = 4;
  if ((actor.controlWord & 0x80) !== 0) slot = 6;
  if ((actor.controlWord & 0x10) !== 0) slot = 2;
  if ((actor.controlWord & 0x20) !== 0) {
    slot = (s.streamBranch1d10 ?? 0) + 8;
    if (actor.ubState === 0x0f) slot = 0;
  }
  return slot + actor.streamSlot;
}

function dashV123Phase0(actor: RomActor): void {
  const s = scratch(actor);
  actor.fbPhaseSlots[0] = 1;
  s.dashLatch745 = false;
  s.dashAimTimer560 = GRED_DASH.AIM_TIMER;
  stepTargetRoll(actor, true);
  startStream(actor, 1, 2, variant123Slot(actor), GRED_DASH.STREAM_RATE);
}

function dashV123Phase1(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  const aim = stepTargetRoll(actor, true);
  if (actor.contactP0 === 0) tickStream(actor, 1, ctx);
  if (aim < 0) {
    restartVariant(actor, (actor.controlWord & 0x40) === 0 ? 0 : 4);
    return;
  }
  if (aim === 0) {
    s.dashAimTimer560 = (s.dashAimTimer560 ?? GRED_DASH.AIM_TIMER) - actor.dt;
    if (s.dashAimTimer560 > 0) return;
  }
  if (streamSignalled(actor)) {
    actor.fbPhaseSlots[0] = 2;
    rearmDash(actor, ctx);
  }
}

/** Shared phase 2 used by variants 1-4 (FUN_8018d8c0). */
function dashSharedPhase2(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  if (((s.inputFlags5d4 ?? 0) & 0x20) !== 0) s.dashLatch745 = true;
  tickStream(actor, 1, ctx);
  if (actor.handlerTimer > 0) {
    actor.handlerTimer -= actor.dt;
    stepTargetRoll(actor, true);
  } else if (s.dashLatch745 && allocateWeapon(actor, ctx, 0, 1, false)) {
    s.dashLatch745 = false;
    actor.fbPhaseSlots[0] = 1;
    let slot: number;
    if ((actor.controlWord & 0x40) === 0 && (s.movementMode5e4 ?? 0) !== 4) {
      if ((actor.controlWord & 0x10) !== 0) {
        actor.variantIndex = 1;
        slot = 3;
      } else if ((actor.controlWord & 0x20) !== 0) {
        actor.variantIndex = 2;
        slot = actor.ubState === 0x0f ? 1 : (s.streamBranch1d10 ?? 0) + 9;
      } else {
        restartVariant(actor, 0);
        return;
      }
    } else {
      actor.variantIndex = 3;
      slot = (actor.controlWord & 0x80) !== 0 ? 7 : 5;
    }
    startStream(actor, 1, 2, slot, GRED_DASH.STREAM_RATE);
    return;
  }
  if (((s.inputFlags5d8 ?? 0) & 0xf0) !== 0 || actor.wallContact !== 0) finishDash(actor);
}

// v4 machine -----------------------------------------------------------------

function dashV4Phase0(actor: RomActor): void {
  const s = scratch(actor);
  actor.fbPhaseSlots[0] = 1;
  s.dashLatch745 = false;
  s.dashAimTimer560 = GRED_DASH.AIM_TIMER;
  stepTargetYaw(actor, 0x81);
  integratePhysics(1.0, actor, actor.lockYaw);
  startStream(actor, 1, 2, actor.streamSlot + 6, GRED_DASH.STREAM_RATE);
  startStream(actor, 2, 0, 0x0d, GRED_DASH.STREAM_RATE);
}

function dashV4Phase1(actor: RomActor, ctx: StreamContext): void {
  const s = scratch(actor);
  tickPreservingDtOnSignal(actor, 0xf, ctx);
  integratePhysics(1.0, actor, actor.lockYaw);
  const ready = stepTargetYaw(actor, 0x81);
  s.dashAimTimer560 = (s.dashAimTimer560 ?? GRED_DASH.AIM_TIMER) - actor.dt;
  if ((s.dashAimTimer560 <= 0 || ready) && streamSignalled(actor)) {
    actor.fbPhaseSlots[0] = 2;
    rearmDash(actor, ctx);
    actor.controlWord &= ~0x2;
    romAirKnockoutReturn(actor); // zz_006a5a4_
  }
}

function dispatchVariant(actor: RomActor, ctx: StreamContext): void {
  const variant = actor.variantIndex;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (variant === 0) {
    if (phase === 0) dashV0Phase0(actor);
    else if (phase === 1) dashV0Phase1(actor, ctx);
    else if (phase === 2) dashV0Phase2(actor, ctx);
    return;
  }
  if (variant >= 1 && variant <= 3) {
    if (phase === 0) dashV123Phase0(actor);
    else if (phase === 1) dashV123Phase1(actor, ctx);
    else if (phase === 2) dashSharedPhase2(actor, ctx);
    return;
  }
  if (variant === 4) {
    if (phase === 0) dashV4Phase0(actor);
    else if (phase === 1) dashV4Phase1(actor, ctx);
    else if (phase === 2) dashSharedPhase2(actor, ctx);
  }
}

export function createGRedDash(ctx: StreamContext = {}): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const s = scratch(actor);
    s.aimPitch1900 = toS16((s.aimPitch1900 ?? 0) * GRED_DASH.ROOT_ROLL_DECAY);
    s.aimPitch18da = toS16(s.aimPitch18da ?? 0) >> 1;
    if (actor.variantIndex === 0 || actor.variantIndex === 4) {
      s.aimRoll1dfc = toS16(s.aimRoll1dfc ?? 0) >> 1;
    }
    dispatchVariant(actor, ctx);
  };
}

