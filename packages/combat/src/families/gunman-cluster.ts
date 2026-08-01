// GUNMAN cluster — four bespoke GUNMAN/GUNNER-family ports sharing one module.
//
// Covers the four unregistered ctors that share the "ranged-burst X-special" archetype
// (a 3-4 phase aim→fire→recover shot deploy indexed by +0x540, group-4 stream arm,
// borg-switched projectile spawn):
//
//   REVOLVER GUNMAN  ctor 0x80072048  pl0100 (0x100) + pl0108 (0x108). BILLY alt.
//                   action-2 phase table @0x802d4374 (3 phases: zz_00736bc_ /
//                   FUN_800737d8 / FUN_80073a3c). Borg-switched dual-shot via
//                   zz_0084600_ (0x100→{0,1}; 0x108→{0xd,0xe}).
//   BEAM GUNNER      ctor 0x80102824  pl0104 (0x104). action-2 phase table @0x80321680
//                   (4 phases: FUN_80103714 / FUN_801037f8 / FUN_8010398c /
//                   FUN_80103aec). Charge-drain beam volley via zz_00e19a8_.
//   GATLING GUNNER   ctor 0x80134d68  pl0102 (0x102). action-2 phase table @0x80337fb8
//                   (3 phases: FUN_80135be8 / FUN_80135ce8 / FUN_80135de4). Single
//                   aimed round via zz_007db5c_(4).
//   POWERED GUNMAN   ctor 0x80165f64  pl0101 (0x101). action-2/3 phase table
//                   @0x8034e728 (3 phases: FUN_80166ea4 / FUN_80166fa8 / FUN_80167200).
//                   Action-2 spawns FUN_8016d584×4 (4-port); action-3 spawns
//                   zz_007db5c_({8,9,6,7}) + zz_00f036c_(6).
//
// Source (all read this session):
//   research/decomp/ghidra-export/chunk_0010.c:1086-1254  (REVOLVER action 2)
//   research/decomp/ghidra-export/chunk_0028.c:4533-4700  (BEAM action 2)
//   research/decomp/ghidra-export/chunk_0035.c:3418-3536  (GATLING action 2)
//   research/decomp/ghidra-export/chunk_0042.c:3729-3895  (POWERED action 2/3)
//
// Exit helpers zz_006a474_/zz_006a5a4_ are ported in shared-idle-return.ts; the local
// exitAction models zz_006a53c_ (housekeeping clear + action-mode strip + full-body cue
// 0x1b). FUN_8006cc90 stream tick is an honest no-op (no bank attached → +0x1d80 null).
//
// Float constants read from boot.dol this session (node readFloatBE via the v2f mapper):
//   REVOLVER sdata2 @0x80437780..0x804377c0
//   BEAM     sdata2 @0x804393a0..0x804393cc
//   GATLING  sdata2 @0x80439f68..0x80439f8c
//   POWERED  sdata2 @0x8043a9d8..0x8043aa08

import { createRomActor, type RomActor, type Vec3 } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import {
  allocateWeapon,
  groundSnapRevert,
  stepAfterimage,
  stepPartTargetPitch,
  stepTargetYaw,
} from "../rom/helpers.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ============================================================================
// Borg identity.
// ============================================================================

const GUNMAN_BORG_NUMBERS: Record<string, number> = {
  pl0100: 0x100, // REVOLVER GUNMAN
  pl0108: 0x108, // BILLY (revolver alt)
  pl0104: 0x104, // BEAM GUNNER
  pl0102: 0x102, // GATLING GUNNER
  pl0101: 0x101, // POWERED GUNMAN
};

export type RevolverBorgId = "pl0100" | "pl0108";

// ============================================================================
// Spawner addresses (zz_* family-local projectile/effect spawners).
// ============================================================================

/** zz_0084600_ @0x80084600 — REVOLVER child-projectile spawner (chunk_0012.c:3430).
 *  Allocates a projectile child via zz_0088aa0_ (weapon slot 3) and seeds its launch
 *  direction from the per-type DAT_802d9794 row. Borg-switched type arg:
 *  0x100 → {0,1}; 0x108 → {0xd,0xe}. */
export const REVOLVER_SHOT_SPAWNER = 0x80084600;
/** zz_007db5c_ @0x8007db5c — shared shuriken/round spawner (chunk_0011.c:4210). GATLING
 *  fires type 4; POWERED action-3 fires types {8,9,6,7}. */
export const GATLING_SHOT_SPAWNER = 0x8007db5c;
/** zz_00e19a8_ @0x800e19a8 — BEAM beam-fire spawner (chunk_0028.c). BEAM ph1 contact
 *  fires this with the +0x6f7 charge byte. */
export const BEAM_FIRE_SPAWNER = 0x800e19a8;
/** FUN_8016d584 @0x8016d584 — POWERED action-2 4-port aimed spawn (chunk_0042.c). Fired
 *  once per hardpoint (0..3) when the aim-roll converges. */
export const POWERED_PORT_SPAWNER = 0x8016d584;
/** zz_00f036c_ @0x800f036c — POWERED action-3 effect spawn (type 6). */
export const POWERED_EFFECT_SPAWNER = 0x800f036c;
/** zz_0082824_ @0x80082824 — SHOT_HELPER (record-table projectile spawn, shared). */
export const GUNMAN_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — effect spawner (shared). */
export const GUNMAN_EFFECT_SPAWNER = 0x800c3be0;

// ============================================================================
// Float constants (DOL-read this session; FLOAT_xxxx citations in comments).
// ============================================================================

/** REVOLVER GUNMAN sdata2 @0x80437780..0x804377c0. */
export const REVOLVER_F = {
  /** FLOAT_80437780 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80437798 = 0.0 — zero scalar (speeds/pose/accumulator80c). */
  ZERO: 0.0,
  /** FLOAT_8043779c = 1.0 — FUN_80067310 gravity arg (recover phase). */
  GRAVITY: 1.0,
  /** FLOAT_804377a0 = 0.95 — gnt4_PSQUATScale blink drag. */
  BLINK_DRAG: 0.95,
  /** FLOAT_804377a4 = 20.0 — air hSpeed seed (ph1 air branch). */
  AIR_HSPEED: 20.0,
  /** FLOAT_804377a8 = -0.3 — air hDecel. */
  AIR_HDECEL: -0.3,
  /** FLOAT_804377ac = 10.0 — yVel seed (air branch / ground when +0x1db==0). */
  YVEL_SEED: 10.0,
  /** FLOAT_804377b0 = 40.0 — ground hSpeed seed (ph1 ground branch). */
  GROUND_HSPEED: 40.0,
  /** FLOAT_804377b4 = -3.0 — ground hDecel. */
  GROUND_HDECEL: -3.0,
  /** FLOAT_804377b8 = 3.0 — afterimage magnitude threshold (motion & hSpeed). */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_804377bc = 0.9 — +0x18da steerYaw decay (ph2). */
  STEER_DECAY: 0.9,
  /** FLOAT_804377c0 = 0.1 — zz_006ed8c_ velocity drag (ph2 grounded contact). */
  VELOCITY_DRAG: 0.1,
} as const;

/** BEAM GUNNER sdata2 @0x804393a0..0x804393cc. */
export const BEAM_F = {
  /** FLOAT_804393a8 = 0.96 — +0x1900 yaw decay (ub wrapper FUN_80103b9c). */
  UB_YAW_DECAY: 0.96,
  /** FLOAT_804393ac = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_804393b0 = 0.0 — zero scalar (speeds / exit hSpeed,hDecel). */
  ZERO: 0.0,
  /** FLOAT_804393b4 = 0.95 — gnt4_PSQUATScale blink drag. */
  BLINK_DRAG: 0.95,
  /** FLOAT_804393bc = 1.0 — FUN_80067310 gravity arg. */
  GRAVITY: 1.0,
  /** FLOAT_804393c8 = 60.0 — +0x560 windup/charge timer seed (ph0). */
  CHARGE_TIMER_SEED: 60.0,
  /** FLOAT_804393cc = 0.5 — yVel seed (ph0). */
  YVEL_SEED: 0.5,
  /** +0x54e initial charge count (ph0 sets 0x3c = 60). */
  CHARGE_COUNT_INIT: 0x3c,
} as const;

/** GATLING GUNNER sdata2 @0x80439f68..0x80439f8c. */
export const GATLING_F = {
  /** FLOAT_80439f68 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80439f74 = 0.0 — zero scalar (speeds/pose/accumulator80c). */
  ZERO: 0.0,
  /** FLOAT_80439f78 = 1.0 — FUN_80067310 gravity arg (recover). */
  GRAVITY: 1.0,
  /** FLOAT_80439f7c = 0.95 — gnt4_PSQUATScale blink drag. */
  BLINK_DRAG: 0.95,
  /** FLOAT_80439f80 = 10.0 — hSpeed seed (ph1 contact). */
  HSPEED_SEED: 10.0,
  /** FLOAT_80439f84 = 15.0 — yVel seed (ph1 contact). */
  YVEL_SEED: 15.0,
  /** FLOAT_80439f88 = 3.0 — afterimage magnitude threshold. */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_80439f8c = 4.0 — exit +0x694 state-timer seed base. */
  EXIT_TIMER_SEED: 4.0,
} as const;

/** POWERED GUNMAN sdata2 @0x8043a9d8..0x8043aa08. */
export const POWERED_F = {
  /** FLOAT_8043a9e8 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a9ec = 0.0 — zero scalar (speeds/pose/accumulator80c). */
  ZERO: 0.0,
  /** FLOAT_8043a9f0 = 1.0 — FUN_80067310 gravity arg (recover). */
  GRAVITY: 1.0,
  /** FLOAT_8043a9f4 = 0.95 — gnt4_PSQUATScale blink drag. */
  BLINK_DRAG: 0.95,
  /** FLOAT_8043a9f8 = 20.0 — hSpeed seed (ph1 contact). */
  HSPEED_SEED: 20.0,
  /** FLOAT_8043a9fc = -0.3 — hDecel seed (ph1 contact). */
  HDECEL_SEED: -0.3,
  /** FLOAT_8043aa00 = 10.0 — yVel seed (ph1 contact). */
  YVEL_SEED: 10.0,
  /** FLOAT_8043aa04 = 3.0 — afterimage magnitude threshold. */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_8043aa08 = 0.9 — +0x18da steerYaw decay (ph2) & zz_006ed8c_ drag. */
  STEER_DECAY: 0.9,
} as const;

/** Shared bit masks (every gunman branch reads +0x5e0 the same way). */
const BITS = {
  /** +0x5e0 bit 0x40 — airborne / position-frozen (slot & branch select). */
  AIRBORNE: 0x40,
  /** +0x5e0 bits 0..1 — action-mode (stripped at exit). */
  ACTION_MODE: 0x3,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ============================================================================

export interface GunmanScratch {
  /** +0x541 (s8): beam-gun ph0/ph1 windup latch (ph1 sets 1 to fire zz_00107a0_). */
  gmBeamWindup541?: number;
  /** +0x54e (s16): beam-gun charge count (ph0 seeds 0x3c; ph2 drains via zz_006de44_). */
  gmBeamCharge54e?: number;
  /** +0x560 (f32): beam-gun windup/charge timer (ph0 seeds 60.0; ph1/ph2 drain). */
  gmBeamTimer560?: number;
  /** +0x6f7 (s8): beam-gun fire-state byte (0 idle, 2 active/charge). */
  gmBeamState6f7?: number;
  /** +0x6e8 (s8): housekeeping clear at exit (gunman recover). */
  gmHousekeeping6e8?: number;
  /** +0x18da (s16): steerYaw (recover-phase decay target). */
  gmSteerYaw18da?: number;
  /** +0x1900 / +0x1918 (s16): aim accumulators written by ph1 contact calc. */
  gmAimYaw1900?: number;
  gmAimYaw1918?: number;
  /** +0x524: beam-gun aim anchor vec3 consumed by zz_006d1a8_. */
  gmAimAnchor524?: Vec3;
}

type GunmanActor = RomActor & GunmanScratch;

function scratchOf(actor: RomActor): GunmanActor {
  return actor as GunmanActor;
}

export interface GunmanFamilyCtx extends StreamContext {}

// ============================================================================
// zz_006a53c_(actor, param) — chunk_0009.c:750. Common action-exit: clear
// housekeeping, strip the action-mode bits, dispatch full-body cue 0x1b, and
// (when param > 0) seed +0x694 = param + dt. (Mirrors fighter-craft.exitAction.)
// ============================================================================
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~BITS.ACTION_MODE;
  dispatchFullBodyCue(actor, 0x1b);
}
export const GUNMAN_EXIT_ACTION = exitAction;

/** FUN_8006cc90 stream tick — honest no-op (no bank attached; +0x1d80 null → returns 0). */
function tickGunmanStream(): number {
  return 0;
}
export const GUNMAN_TICK_STREAM = tickGunmanStream;

/** The shared blink reposition: motion = (pos − targetCache5e8) × drag; pos += motion.
 *  Port of the gnt4_PSVECSubtract / PSQUATScale / PSVECAdd triplet every gunman ph0/ph1
 *  runs (chunk_0010.c:1107-1110 etc.). */
function applyBlink(actor: RomActor, drag: number): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(drag, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Resolve the aim stream slot from the airborne bit. Port of the
 *  `+0x6ea = 0; if (+0x5e0 & 0x40) +0x6ea = 1;` idiom (REVOLVER/POWERED ph0). */
function slotFor(actor: RomActor): number {
  return (actor.controlWord & BITS.AIRBORNE) !== 0 ? 1 : 0;
}

// ============================================================================
// REVOLVER GUNMAN — action 2 phase table @0x802d4374 (3 phases).
//   ph0 zz_00736bc_ @chunk_0010.c:1086  — setup: zero speeds, blink, stream arm.
//   ph1 FUN_800737d8 @chunk_0010.c:1132 — active: aim, on +0x1cf0 contact → speeds +
//                                          borg-switched zz_0084600_ dual shot.
//   ph2 FUN_80073a3c @chunk_0010.c:1214 — recover: steer decay, physics, exit on contact.
// ============================================================================

function revolverPhase0(actor: GunmanActor, _ctx: GunmanFamilyCtx): void {
  // +0x540++ (zz_00736bc_:1095).
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  // Zero the speed scalars (FLOAT_80437798 = 0.0).
  actor.gravityCoeff = REVOLVER_F.ZERO;
  actor.yVel = REVOLVER_F.ZERO;
  actor.hDecel = REVOLVER_F.ZERO;
  actor.hSpeed = REVOLVER_F.ZERO;
  // Clear pose accumulators (+0x7c/+0x7e/+0x80).
  actor.poseAccum7c = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum80 = 0;
  // zz_006d0dc_(actor, 0xc1, 0) — yaw converge toward target.
  stepTargetYaw(actor, 0xc1, 0);
  if ((actor.controlWord & BITS.AIRBORNE) !== 0) {
    // zz_006e1ac_(actor, 0xc1, 1) — part-pitch converge.
    stepPartTargetPitch(actor, 0xc1);
  }
  // Blink toward cached target (×FLOAT_804377a0).
  applyBlink(actor, REVOLVER_F.BLINK_DRAG);
  groundSnapRevert(actor);
  // Air-with-ground-snap clears the airborne bit (zz_00736bc_:1112-1114).
  if ((actor.controlWord & 0x20) !== 0 && (actor as RomActor & { grounded?: boolean }).grounded === true) {
    actor.controlWord = actor.controlWord & ~BITS.AIRBORNE;
  }
  // Slot select + stream arm (group 4, slot, rate FLOAT_80437780).
  const slot = slotFor(actor);
  actor.streamSlot = slot;
  startStream(actor, 0xf, 4, slot, REVOLVER_F.STREAM_RATE);
  // +0x80c = 0.0.
  actor.accumulator80c = REVOLVER_F.ZERO;
}

function revolverPhase1(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  // zz_004cd24_(actor, 0xf) — tick the aim stream.
  tickStream(actor, 0xf, ctx);
  // zz_006d0dc_(actor, 0xc1, 0) — yaw converge.
  stepTargetYaw(actor, 0xc1, 0);
  if ((actor.controlWord & BITS.AIRBORNE) !== 0) {
    stepPartTargetPitch(actor, 0xc1);
  }
  // Blink drag + ground snap.
  vecScale(REVOLVER_F.BLINK_DRAG, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);

  // +0x1cf0 contact gate (part-1 contact > 0).
  if (actor.contactP1 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    // +0x5ae = +0x72 - 0x8000 (lockYaw = heading − 180°).
    actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
    const grounded = (actor.controlWord & BITS.AIRBORNE) === 0;
    if (grounded) {
      // Ground branch: hSpeed=40, hDecel=-3, yVel=10 (when +0x1db==0).
      actor.hSpeed = REVOLVER_F.GROUND_HSPEED;
      actor.hDecel = REVOLVER_F.GROUND_HDECEL;
      if (actor.ubState === 0) actor.yVel = REVOLVER_F.YVEL_SEED;
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
    } else {
      // Air branch: hSpeed=20, hDecel=-0.3, yVel=10.
      actor.hSpeed = REVOLVER_F.AIR_HSPEED;
      actor.hDecel = REVOLVER_F.AIR_HDECEL;
      actor.yVel = REVOLVER_F.YVEL_SEED;
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
    }
    // zz_006dbe0_(actor, 2, 1, 1) — the shared special-ammo gate (weapon index 2,
    // count 1, consume). Both shots fire together after this single gate succeeds.
    if (allocateWeapon(actor, ctx, 2, 1, true)) {
      // Borg-switched dual shot via zz_0084600_.
      if (actor.borgNumber === 0x100) {
        ctx.onFamilyProjectile?.(actor, REVOLVER_SHOT_SPAWNER, 0);
        ctx.onFamilyProjectile?.(actor, REVOLVER_SHOT_SPAWNER, 1);
      } else if (actor.borgNumber === 0x108) {
        ctx.onFamilyProjectile?.(actor, REVOLVER_SHOT_SPAWNER, 0xd);
        ctx.onFamilyProjectile?.(actor, REVOLVER_SHOT_SPAWNER, 0xe);
      }
    }
  }
  // Afterimage when |motion| > FLOAT_804377b8.
  if (Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z) > REVOLVER_F.AFTERIMAGE_THRESHOLD) {
    stepAfterimage(actor);
  }
}

function revolverPhase2(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  // +0x18da steerYaw decay: val = (val - DOUBLE_base) × FLOAT_804377bc.
  s.gmSteerYaw18da = Math.trunc((s.gmSteerYaw18da ?? 0) * REVOLVER_F.STEER_DECAY);
  // tick stream + physics (gravity FLOAT_8043779c, yaw lockYaw).
  tickStream(actor, 0xf, ctx);
  integratePhysics(REVOLVER_F.GRAVITY, actor, actor.lockYaw);
  const grounded = groundSnapRevert(actor);
  // Grounded + contactP0 ≥ 0 → velocity drag (zz_006ed8c_ ×FLOAT_804377c0); else fallthrough.
  if (grounded && actor.contactP0 >= 0) {
    // fallthrough to contact check
  } else if (actor.contactP0 < 0) {
    // zz_006ed8c_((double)FLOAT_804377c0, actor) — velocity drag.
    actor.hSpeed *= REVOLVER_F.VELOCITY_DRAG;
  }
  // Exit on wallContact OR (grounded && contactP0 ≥ 0).
  if (actor.wallContact !== 0 || (grounded && actor.contactP0 >= 0)) {
    s.gmAimYaw1900 = 0;
    s.gmAimYaw1918 = 0;
    s.gmHousekeeping6e8 = 0;
    if (!grounded) {
      romAirKnockoutReturn(actor);
    } else if ((actor.controlWord & BITS.AIRBORNE) === 0) {
      romGroundIdleReturn(actor);
    } else {
      // zz_006a750_(actor, 7) — upper-body cue 7.
    }
    // +0x694 = FLOAT_8043779c + dt (state-timer seed).
    actor.stateTimer = REVOLVER_F.GRAVITY + actor.dt;
  }
  // Afterimage when hSpeed > FLOAT_804377b8.
  if (actor.hSpeed > REVOLVER_F.AFTERIMAGE_THRESHOLD) {
    stepAfterimage(actor);
  }
}

const REVOLVER_PHASE_TABLE = [revolverPhase0, revolverPhase1, revolverPhase2];

/** zz_0073668_ @chunk_0010.c:1072 — the X-special wrapper. Halves +0x18da when
 *  grounded, then dispatches PTR_zz_00736bc__802d4374[+0x540]. */
function revolverXHandler(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  if ((actor.controlWord & BITS.AIRBORNE) === 0) {
    s.gmSteerYaw18da = (s.gmSteerYaw18da ?? 0) >> 1;
  }
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = REVOLVER_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// GATLING GUNNER — action 2 phase table @0x80337fb8 (3 phases).
//   ph0 FUN_80135be8 @chunk_0035.c:3418 — setup.
//   ph1 FUN_80135ce8 @chunk_0035.c:3459 — active: on +0x1cef contact → speeds + shot.
//   ph2 FUN_80135de4 @chunk_0035.c:3503 — recover: physics, exit on contact.
// ============================================================================

function gatlingPhase0(actor: GunmanActor, _ctx: GunmanFamilyCtx): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  // if (+0xcc == 0) +0x5ac = +0x72 (lock active-yaw to heading when no target lock).
  if (actor.visibilityTarget === null) {
    actor.activeYaw = actor.heading;
  }
  // zz_006d144_(actor, 0xc1) — yaw converge (preserve-on-target-loss variant).
  stepTargetYaw(actor, 0xc1, 0);
  // Zero speeds (FLOAT_80439f74 = 0.0).
  actor.gravityCoeff = GATLING_F.ZERO;
  actor.yVel = GATLING_F.ZERO;
  actor.hDecel = GATLING_F.ZERO;
  actor.hSpeed = GATLING_F.ZERO;
  actor.poseAccum7c = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum80 = 0;
  // Blink + ground collision.
  applyBlink(actor, GATLING_F.BLINK_DRAG);
  groundSnapRevert(actor);
  // Slot select + stream arm (group 4, rate FLOAT_80439f68).
  const slot = slotFor(actor);
  const nextSlot = slot + 1;
  actor.streamSlot = nextSlot;
  startStream(actor, 0xf, 4, slot, GATLING_F.STREAM_RATE);
  actor.accumulator80c = GATLING_F.ZERO;
}

function gatlingPhase1(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc1, 0);
  vecScale(GATLING_F.BLINK_DRAG, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  // +0x1cef contact gate.
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
    actor.hSpeed = GATLING_F.HSPEED_SEED;
    actor.hDecel = GATLING_F.ZERO;
    actor.yVel = GATLING_F.YVEL_SEED;
    // +0x1d0f (dashStrength) != 0 → gravity = -1.0 (FLOAT_80439f68 repurposed as the
    // descriptor gravity slot read; the ROM reads *(desc+0x6c) here only in the
    // +0x1d0f branch via FLOAT_80439f68 = -1.0 as the gravity arg).
    if (actor.dashStrength1d0f !== 0) {
      actor.gravityCoeff = GATLING_F.STREAM_RATE; // -1.0
    }
    // zz_006dbe0_(actor, 2, 1, 1) — shared special-ammo gate; fire zz_007db5c_(4).
    if (allocateWeapon(actor, ctx, 2, 1, true)) {
      ctx.onFamilyProjectile?.(actor, GATLING_SHOT_SPAWNER, 4);
    }
  }
  if (Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z) > GATLING_F.AFTERIMAGE_THRESHOLD) {
    stepAfterimage(actor);
  }
}

function gatlingPhase2(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  integratePhysics(GATLING_F.GRAVITY, actor, actor.lockYaw);
  const grounded = groundSnapRevert(actor);
  // Air + grounded + contactP0 < 0 → air exit (cue 7, stateTimer = 4 + dt).
  if (grounded && (actor.controlWord & BITS.AIRBORNE) !== 0 && actor.contactP0 < 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~BITS.ACTION_MODE;
    // zz_006a750_(actor, 7).
    actor.stateTimer = GATLING_F.EXIT_TIMER_SEED + actor.dt;
    return;
  }
  // wallContact → exit (idle return, stateTimer = 4 + dt).
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~BITS.ACTION_MODE;
    if (!grounded) {
      romAirKnockoutReturn(actor);
    } else if ((actor.controlWord & BITS.AIRBORNE) === 0) {
      romGroundIdleReturn(actor);
    }
    actor.stateTimer = GATLING_F.EXIT_TIMER_SEED + actor.dt;
  }
}

const GATLING_PHASE_TABLE = [gatlingPhase0, gatlingPhase1, gatlingPhase2];

function gatlingXHandler(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = GATLING_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// BEAM GUNNER — action 2 phase table @0x80321680 (4 phases).
//   ph0 FUN_80103714 @chunk_0028.c:4533 — setup: charge timer, stream arm.
//   ph1 FUN_801037f8 @chunk_0028.c:4573 — active: aim, on contact → beam fire / exit.
//   ph2 FUN_8010398c @chunk_0028.c:4625 — charge drain, physics, re-arm.
//   ph3 FUN_80103aec @chunk_0028.c:4674 — recover: physics, exit on contact.
// True table length = 4 (work-queue overreads 4 trailing FUN_80103c10 stubs belonging
// to the adjacent action-3 table @0x803216a4; confirmed by decomp dispatch + address
// arithmetic).
// ============================================================================

function beamPhase0(actor: GunmanActor, _ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.gmBeamWindup541 = 0;
  s.gmBeamTimer560 = BEAM_F.CHARGE_TIMER_SEED; // +0x560 = FLOAT_804393c8.
  s.gmBeamCharge54e = BEAM_F.CHARGE_COUNT_INIT; // +0x54e = 0x3c.
  actor.streamSlot = 0;
  s.gmBeamState6f7 = 0;
  actor.lockYaw = actor.heading; // +0x5ae = +0x72.
  // Speeds: 4c=0, 44=0, 48=0.5, 50=0.
  actor.hDecel = BEAM_F.ZERO;
  actor.hSpeed = BEAM_F.ZERO;
  actor.yVel = BEAM_F.YVEL_SEED;
  actor.gravityCoeff = BEAM_F.ZERO;
  // zz_006d1a8_(actor, 0xc1, +0x524) — yaw converge toward the +0x524 anchor.
  stepTargetYaw(actor, 0xc1, 0);
  applyBlink(actor, BEAM_F.BLINK_DRAG);
  groundSnapRevert(actor);
  // Slot++ + stream arm (group 4, rate FLOAT_804393ac).
  const slot = (actor.streamSlot ?? 0) + 1;
  actor.streamSlot = slot;
  startStream(actor, 0xf, 4, (actor.streamSlot ?? 1) - 1, BEAM_F.STREAM_RATE);
}

function beamPhase1(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc1, 0);
  // +0x784 < 1 → +0x50 = *(desc+0x6c); else if +0x541==0 → +0x541=1, zz_00107a0_(10).
  if ((actor as RomActor & { gmStatus784?: number }).gmStatus784 === undefined || (actor as RomActor & { gmStatus784?: number }).gmStatus784! < 1) {
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  } else if ((s.gmBeamWindup541 ?? 0) === 0) {
    s.gmBeamWindup541 = 1;
    // zz_00107a0_(actor, 10) — TODO(host): status/sound hook @0x800107a0 (unsurfaced).
  }
  // Physics (gravity FLOAT_804393bc, yaw lockYaw) + blink + collision.
  integratePhysics(BEAM_F.GRAVITY, actor, actor.lockYaw);
  vecScale(BEAM_F.BLINK_DRAG, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  // Contact gate: +0x1cef < 1 OR ammo-peek (zz_006dbe0_(2,1,0) = allocateWeapon consume=false).
  if (actor.contactP0 < 1 || allocateWeapon(actor, ctx, 2, 1, false)) {
    if (actor.wallContact === 0) {
      return; // no wall contact → stay.
    }
    // zz_00f036c_(actor, 0xc3) — TODO(host): effect hook @0x800f036c (unsurfaced).
    // zz_006dbe0_(actor, 2, 1, 1) — consume gate; fire zz_00e19a8_(1, +0x6f7).
    if (allocateWeapon(actor, ctx, 2, 1, true)) {
      ctx.onFamilyProjectile?.(actor, BEAM_FIRE_SPAWNER, s.gmBeamState6f7 ?? 0);
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      s.gmBeamState6f7 = 2;
      const slot = (actor.streamSlot ?? 0) + 1;
      actor.streamSlot = slot;
      startStream(actor, 0xf, 4, slot - 1, BEAM_F.STREAM_RATE);
      return;
    }
  }
  // Else: exit (73f=0, 5e0&=~3, 4c=0, 44=0, zz_006a5a4_).
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~BITS.ACTION_MODE;
  actor.hDecel = BEAM_F.ZERO;
  actor.hSpeed = BEAM_F.ZERO;
  romAirKnockoutReturn(actor);
}

function beamPhase2(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  s.gmBeamState6f7 = 2;
  // zz_006de44_(actor, 0xf0f00) — charge drain; clamps uVar3 to +0x54e and subtracts.
  // TODO(host): zz_006de44_ @0x8006de44 (the held-button charge meter) is unsurfaced;
  // modeled as a 1-unit drain per tick (the no-input default).
  const drain = 1;
  const charge = s.gmBeamCharge54e ?? 0;
  const drained = Math.max(0, charge - drain);
  s.gmBeamCharge54e = drained;
  s.gmBeamTimer560 = (s.gmBeamTimer560 ?? 0) + (charge - drained);
  // Physics (gravity FLOAT_804393bc, yaw lockYaw - 0x8000).
  integratePhysics(BEAM_F.GRAVITY, actor, (actor.lockYaw - 0x8000) & 0xffff);
  groundSnapRevert(actor);
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    stepTargetYaw(actor, 0xc1, 0);
    // zz_006e39c_(actor, 0xc1, 1, 0x4000, +0x524) — TODO(host): dual-axis aim pitch
    // converge @0x8006e39c (unsurfaced); stepPartTargetPitch is the nearest port.
    stepPartTargetPitch(actor, 0xc1);
  }
  // Timer exhausted → advance + re-arm.
  if ((s.gmBeamTimer560 ?? 0) <= BEAM_F.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.hDecel = BEAM_F.ZERO;
    actor.hSpeed = BEAM_F.ZERO;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
    s.gmBeamState6f7 = 0;
    const slot = (actor.streamSlot ?? 0) + 1;
    actor.streamSlot = slot;
    startStream(actor, 0xf, 4, slot - 1, BEAM_F.STREAM_RATE);
  } else {
    s.gmBeamTimer560 = (s.gmBeamTimer560 ?? 0) - actor.dt;
  }
}

function beamPhase3(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  integratePhysics(BEAM_F.GRAVITY, actor, actor.lockYaw);
  const grounded = groundSnapRevert(actor);
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~BITS.ACTION_MODE;
    actor.hDecel = BEAM_F.ZERO;
    actor.hSpeed = BEAM_F.ZERO;
    if (!grounded) {
      romAirKnockoutReturn(actor);
    } else {
      // zz_006a750_(actor, 7) + stateTimer = FLOAT_804393bc + dt.
      actor.stateTimer = BEAM_F.GRAVITY + actor.dt;
    }
  }
}

const BEAM_PHASE_TABLE = [beamPhase0, beamPhase1, beamPhase2, beamPhase3];

function beamXHandler(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = BEAM_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// POWERED GUNMAN — action 2/3 phase table @0x8034e728 (3 phases).
//   ph0 FUN_80166ea4 @chunk_0042.c:3729 — setup.
//   ph1 FUN_80166fa8 @chunk_0042.c:3766 — active: on +0x1cf0 contact → speeds +
//     action-switched spawn (action 2 → FUN_8016d584×4; action 3 → zz_007db5c_×4).
//   ph2 FUN_80167200 @chunk_0042.c:3850 — recover: steer decay, physics, exit.
// ============================================================================

function poweredPhase0(actor: GunmanActor, _ctx: GunmanFamilyCtx): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  // Slot select (0 ground / 1 air).
  actor.streamSlot = slotFor(actor);
  // Zero speeds (FLOAT_8043a9ec = 0.0).
  actor.gravityCoeff = POWERED_F.ZERO;
  actor.yVel = POWERED_F.ZERO;
  actor.hDecel = POWERED_F.ZERO;
  actor.hSpeed = POWERED_F.ZERO;
  actor.poseAccum7c = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum80 = 0;
  stepTargetYaw(actor, 0xc1, 0);
  if ((actor.controlWord & BITS.AIRBORNE) !== 0) {
    stepPartTargetPitch(actor, 0xc1);
  }
  applyBlink(actor, POWERED_F.BLINK_DRAG);
  groundSnapRevert(actor);
  // Stream arm (group 4, slot, rate FLOAT_8043a9e8).
  startStream(actor, 0xf, 4, actor.streamSlot ?? 0, POWERED_F.STREAM_RATE);
  actor.accumulator80c = POWERED_F.ZERO;
}

function poweredPhase1(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc1, 0);
  if ((actor.controlWord & BITS.AIRBORNE) !== 0) {
    stepPartTargetPitch(actor, 0xc1);
  }
  vecScale(POWERED_F.BLINK_DRAG, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  // +0x1cf0 contact gate.
  if (actor.contactP1 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
    // Speeds: hSpeed=20, hDecel=-0.3, yVel=10, gravity=desc.6c.
    actor.hSpeed = POWERED_F.HSPEED_SEED;
    actor.hDecel = POWERED_F.HDECEL_SEED;
    actor.yVel = POWERED_F.YVEL_SEED;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
    // Ground aim calc writes +0x1900/+0x1918 (unsurfaced anchors 0xa24/0xae4).
    // zz_0046698_(actor) — TODO(host): aim update @0x80046698 (unsurfaced).
    if (actor.actionIndex === 2) {
      // Action 2: zz_006dbe0_(2,1,1) gate → FUN_8016d584×4 (4-port aimed spawn).
      if (allocateWeapon(actor, ctx, 2, 1, true)) {
        for (let port = 0; port < 4; port++) {
          ctx.onFamilyProjectile?.(actor, POWERED_PORT_SPAWNER, port);
        }
      }
    } else {
      // Action 3: zz_007db5c_({8,9,6,7}) + zz_00f036c_(6). Single ammo gate covers the volley.
      if (allocateWeapon(actor, ctx, 2, 1, true)) {
        for (const type of [8, 9, 6, 7]) {
          ctx.onFamilyProjectile?.(actor, GATLING_SHOT_SPAWNER, type);
        }
        // zz_00f036c_(actor, 6) — effect spawn.
        ctx.onFamilyProjectile?.(actor, POWERED_EFFECT_SPAWNER, 6);
      }
    }
  }
  if (Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z) > POWERED_F.AFTERIMAGE_THRESHOLD) {
    stepAfterimage(actor);
  }
}

function poweredPhase2(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const s = scratchOf(actor);
  // +0x18da steerYaw decay (×FLOAT_8043aa08).
  s.gmSteerYaw18da = Math.trunc((s.gmSteerYaw18da ?? 0) * POWERED_F.STEER_DECAY);
  tickStream(actor, 0xf, ctx);
  integratePhysics(POWERED_F.GRAVITY, actor, actor.lockYaw);
  const grounded = groundSnapRevert(actor);
  if (grounded && actor.contactP0 >= 0) {
    // fallthrough to contact check
  } else if (actor.contactP0 < 0) {
    // zz_006ed8c_((double)FLOAT_8043aa08, actor) — velocity drag.
    actor.hSpeed *= POWERED_F.STEER_DECAY;
  }
  if (actor.wallContact !== 0 || (grounded && actor.contactP0 >= 0)) {
    s.gmAimYaw1900 = 0;
    s.gmAimYaw1918 = 0;
    s.gmHousekeeping6e8 = 0;
    if (!grounded) {
      romAirKnockoutReturn(actor);
    } else if ((actor.controlWord & BITS.AIRBORNE) === 0) {
      romGroundIdleReturn(actor);
    }
    actor.stateTimer = POWERED_F.GRAVITY + actor.dt;
  }
  if (actor.hSpeed > POWERED_F.AFTERIMAGE_THRESHOLD) {
    stepAfterimage(actor);
  }
}

const POWERED_PHASE_TABLE = [poweredPhase0, poweredPhase1, poweredPhase2];

function poweredXHandler(actor: GunmanActor, ctx: GunmanFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = POWERED_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action routers — index PTR_FUN_[actionIndex]; action 2 (X-special) ported here,
// other rows wire in as their handlers port. Null entries fall through to the generic
// @gf/combat layer (mirrors fighter-craft / wire-gunner convention).
// ============================================================================

function createRevolverRootAction(
  ctx: GunmanFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null, // 0: dash attack (FUN_800729f8/zz_00728f0 etc.) — TODO port
    null, // 1: B melee (chunk_0042.c shared 0x8034c6a8 range) — TODO port
    (actor) => revolverXHandler(scratchOf(actor), ctx), // 2: X-special (dual-shot deploy)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

function createGatlingRootAction(
  ctx: GunmanFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null, // 0: dash attack (FUN_8013550c etc.) — TODO port
    null, // 1: B melee (shared chunk_0042 range) — TODO port
    (actor) => gatlingXHandler(scratchOf(actor), ctx), // 2: X-special (single round)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

function createBeamRootAction(
  ctx: GunmanFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null, // 0: dash attack (FUN_80102af8 etc.) — TODO port
    null, // 1: B melee (shared chunk_0042 range) — TODO port
    (actor) => beamXHandler(scratchOf(actor), ctx), // 2: X-special (beam volley)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

function createPoweredRootAction(
  ctx: GunmanFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null, // 0: dash attack (FUN_801666e0 etc.) — TODO port
    null, // 1: B melee (shared chunk_0042 range) — TODO port
    (actor) => poweredXHandler(scratchOf(actor), ctx), // 2: X-special (4-port spawn)
    (actor) => poweredXHandler(scratchOf(actor), ctx), // 3: X-special alt (shuriken volley)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

// ============================================================================
// configure* — stamps the borg-number switch + wires the root action.
// ============================================================================

/** Configure a freshly-spawned REVOLVER GUNMAN-family actor (pl0100/pl0108). */
export function configureRevolverGunmanFamily(
  actor: RomActor,
  borgId: RevolverBorgId,
  ctx: GunmanFamilyCtx,
): void {
  actor.borgNumber = GUNMAN_BORG_NUMBERS[borgId] ?? 0x100;
  actor.rootAction = createRevolverRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a freshly-spawned BEAM GUNNER actor (pl0104). */
export function configureBeamGunnerFamily(actor: RomActor, ctx: GunmanFamilyCtx): void {
  actor.borgNumber = 0x104;
  actor.rootAction = createBeamRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a freshly-spawned GATLING GUNNER actor (pl0102). */
export function configureGatlingGunnerFamily(actor: RomActor, ctx: GunmanFamilyCtx): void {
  actor.borgNumber = 0x102;
  actor.rootAction = createGatlingRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a freshly-spawned POWERED GUNMAN actor (pl0101). */
export function configurePoweredGunmanFamily(actor: RomActor, ctx: GunmanFamilyCtx): void {
  actor.borgNumber = 0x101;
  actor.rootAction = createPoweredRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests. Mirror gold-hero / rom.selfcheck style.
// ============================================================================

export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

interface ShotEvent { addr: number; type: number; }

function makeCtx(opts: {
  onAllocateResource?: (slot: number, count: number, mode: number) => boolean;
  onFamilyProjectile?: (addr: number, type: number) => void;
} = {}): GunmanFamilyCtx {
  const ctx: GunmanFamilyCtx = {};
  if (opts.onAllocateResource) {
    const sink = opts.onAllocateResource;
    ctx.onAllocateResource = (_a, slot, count, mode) => sink(slot, count, mode ?? 0);
  }
  if (opts.onFamilyProjectile) {
    const sink = opts.onFamilyProjectile;
    ctx.onFamilyProjectile = (_a, addr, type) => sink(addr, type);
  }
  return ctx;
}

export function runGunmanClusterSelfTests(assert: AssertFn): void {
  // ==========================================================================
  // REVOLVER GUNMAN
  // ==========================================================================

  // --- configure: stamps borgNumber + wires rootAction. ---
  {
    const a = createRomActorScratch();
    configureRevolverGunmanFamily(a, "pl0100", makeCtx());
    assert(a.borgNumber === 0x100, "revolver configure stamps borgNumber 0x100 (pl0100)");
    assert(a.rootAction !== null, "revolver configure wires rootAction");

    const b = createRomActorScratch();
    configureRevolverGunmanFamily(b, "pl0108", makeCtx());
    assert(b.borgNumber === 0x108, "revolver configure stamps borgNumber 0x108 (pl0108)");
  }

  // --- action 2 ph0: advance +0x540, zero speeds, blink, stream arm. ---
  {
    const a = createRomActorScratch();
    configureRevolverGunmanFamily(a, "pl0100", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.accumulator80c = 42;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "revolver ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "revolver ph0 zeroes hSpeed/hDecel/gravityCoeff (FLOAT_80437798)");
    assert(a.accumulator80c === 0, "revolver ph0 +0x80c = 0 (FLOAT_80437798)");
    assert(approxEq(a.pos.x, 195), "revolver ph0 blink pos.x = 195 ((100−0)×0.95 added)");
  }

  // --- action 2 ph1: contact → borg-switched dual shot (0x100 → {0,1}). ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureRevolverGunmanFamily(a, "pl0100", makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // ph1
    a.contactP1 = 1; // +0x1cf0 > 0 (contact)
    a.ubState = 0;
    a.heading = 0x1000;
    root(a);
    assert(shots.length === 2 && shots[0]!.addr === REVOLVER_SHOT_SPAWNER && shots[0]!.type === 0 && shots[1]!.type === 1,
      `revolver ph1 0x100 contact spawns zz_0084600_({0,1}) (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2, "revolver ph1 contact → +0x540++ (advance to ph2)");
    assert(a.lockYaw === ((0x1000 - 0x8000) & 0xffff), "revolver ph1 sets lockYaw = heading − 0x8000");
  }

  // --- action 2 ph1: 0x108 borg-switch → {0xd,0xe}. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureRevolverGunmanFamily(a, "pl0108", makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP1 = 1; a.ubState = 0; a.heading = 0;
    root(a);
    assert(shots.length === 2 && shots[0]!.type === 0xd && shots[1]!.type === 0xe,
      `revolver ph1 0x108 contact spawns zz_0084600_({0xd,0xe}) (got ${JSON.stringify(shots)})`);
  }

  // --- action 2 ph1: ammo-gate denies shots when allocateWeapon returns false. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureRevolverGunmanFamily(a, "pl0100", makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1; a.contactP1 = 1; a.ubState = 0; a.heading = 0;
    root(a);
    assert(shots.length === 0, "revolver ph1 ammo-gate denies shots when allocateWeapon=false");
    assert(a.fbPhaseSlots[0] === 2, "revolver ph1 still advances to ph2 when ammo denied");
  }

  // ==========================================================================
  // GATLING GUNNER
  // ==========================================================================

  // --- configure + ph0 setup. ---
  {
    const a = createRomActorScratch();
    configureGatlingGunnerFamily(a, makeCtx());
    assert(a.borgNumber === 0x102, "gatling configure stamps borgNumber 0x102");
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.pos = { x: 50, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "gatling ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "gatling ph0 zeroes speeds (FLOAT_80439f74)");
  }

  // --- ph1 contact → zz_007db5c_(4) single round. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureGatlingGunnerFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; // +0x1cef > 0
    a.heading = 0;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === GATLING_SHOT_SPAWNER && shots[0]!.type === 4,
      `gatling ph1 contact spawns zz_007db5c_(4) (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2, "gatling ph1 contact → advance to ph2");
    assert(a.hSpeed === GATLING_F.HSPEED_SEED && a.yVel === GATLING_F.YVEL_SEED,
      "gatling ph1 seeds hSpeed=10/yVel=15 (FLOAT_80439f80/84)");
  }

  // --- ph1 ammo-gate denies. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureGatlingGunnerFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP0 = 1; a.heading = 0;
    root(a);
    assert(shots.length === 0, "gatling ph1 ammo-gate denies when allocateWeapon=false");
  }

  // ==========================================================================
  // BEAM GUNNER
  // ==========================================================================

  // --- configure + ph0 setup. ---
  {
    const a = createRomActorScratch();
    configureBeamGunnerFamily(a, makeCtx());
    assert(a.borgNumber === 0x104, "beam configure stamps borgNumber 0x104");
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 0, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "beam ph0 advances +0x540 to 1");
    assert(approxEq(a.gmBeamTimer560 ?? 0, 60), "beam ph0 +0x560 = 60.0 (FLOAT_804393c8)");
    assert((a.gmBeamCharge54e ?? 0) === 0x3c, "beam ph0 +0x54e = 0x3c (charge count)");
    assert(approxEq(a.yVel, 0.5), "beam ph0 yVel = 0.5 (FLOAT_804393cc)");
  }

  // --- ph1 contact → beam fire via zz_00e19a8_. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configureBeamGunnerFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // ph1
    a.contactP0 = 0; // < 1 → enters the contact gate
    a.wallContact = 1; // wall contact present
    a.gmBeamState6f7 = 0;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === BEAM_FIRE_SPAWNER,
      `beam ph1 contact fires zz_00e19a8_ (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2, "beam ph1 contact → advance to ph2");
  }

  // ==========================================================================
  // POWERED GUNMAN
  // ==========================================================================

  // --- configure + ph0 setup. ---
  {
    const a = createRomActorScratch();
    configurePoweredGunmanFamily(a, makeCtx());
    assert(a.borgNumber === 0x101, "powered configure stamps borgNumber 0x101");
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.pos = { x: 0, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "powered ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "powered ph0 zeroes speeds (FLOAT_8043a9ec)");
  }

  // --- action 2 ph1 contact → FUN_8016d584×4 (4-port spawn). ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configurePoweredGunmanFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP1 = 1; // +0x1cf0 > 0
    a.heading = 0;
    root(a);
    const ports = shots.filter((s) => s.addr === POWERED_PORT_SPAWNER);
    assert(ports.length === 4, `powered action-2 ph1 spawns FUN_8016d584×4 (got ${ports.length})`);
    assert(a.fbPhaseSlots[0] === 2, "powered ph1 contact → advance to ph2");
  }

  // --- action 3 ph1 contact → zz_007db5c_({8,9,6,7}) + effect. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configurePoweredGunmanFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 1; a.contactP1 = 1; a.heading = 0;
    root(a);
    const volleys = shots.filter((s) => s.addr === GATLING_SHOT_SPAWNER).map((s) => s.type).sort();
    const fx = shots.filter((s) => s.addr === POWERED_EFFECT_SPAWNER);
    assert(JSON.stringify(volleys) === JSON.stringify([6, 7, 8, 9]),
      `powered action-3 ph1 spawns zz_007db5c_({8,9,6,7}) (got ${JSON.stringify(volleys)})`);
    assert(fx.length === 1 && fx[0]!.type === 6, "powered action-3 ph1 spawns zz_00f036c_(6) effect");
  }

  // --- ph1 ammo-gate denies. ---
  {
    const shots: ShotEvent[] = [];
    const a = createRomActorScratch();
    configurePoweredGunmanFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP1 = 1; a.heading = 0;
    root(a);
    assert(shots.length === 0, "powered ph1 ammo-gate denies when allocateWeapon=false");
  }
}

/** Create a RomActor with the gunman scratch fields pre-zeroed (test helper). */
function createRomActorScratch(): GunmanActor {
  const a = createRomActor() as GunmanActor;
  a.gmBeamWindup541 = 0;
  a.gmBeamCharge54e = 0;
  a.gmBeamTimer560 = 0;
  a.gmBeamState6f7 = 0;
  a.gmHousekeeping6e8 = 0;
  a.gmSteerYaw18da = 0;
  a.gmAimYaw1900 = 0;
  a.gmAimYaw1918 = 0;
  a.gmAimAnchor524 = { x: 0, y: 0, z: 0 };
  return a;
}
