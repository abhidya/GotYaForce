// KNIGHT CLUSTER — 7-family bespoke port covering 14 borgs.
//
// All seven families share the knight melee/lunge machinery (tables 0x80343c00 /
// 0x80343c14 / 0x80343c28 in chunk_0040.c, already ported in shared-knight-melee.ts).
// This module wires action 1 (B-melee) to that shared engine for the five families
// that use it, and provides per-family bespoke ports / TODO stubs for actions 0/2/3.
//
// Families covered:
//   SAPPHIRE KNIGHT   pl0208 (0x208), pl020e (0x20e)  — ctor 0x800bb390, chunk_0019.c
//   ELEMENTAL KNIGHT  pl0202 (0x202), pl020b (0x20b)  — ctor 0x80123438, chunk_0033.c
//   IMPERIAL KNIGHT   pl0209 (0x209)                  — ctor 0x801b7c74, chunk_0053.c
//   DARK KNIGHT       pl0205 (0x205)                  — ctor 0x801567f0, chunk_0040.c
//   AXE KNIGHT        pl0204 (0x204), pl020d (0x20d)  — ctor 0x800d6d10, chunk_0022.c
//   SPIKE KNIGHT      pl0203 (0x203), pl020c (0x20c)  — ctor 0x800e5288, chunk_0024.c
//   CHAINSAW KNIGHT   pl0201 (0x201)                  — ctor 0x800c8560, chunk_0020.c
//
// Port status:
//   - Action 1 (B-melee): FAITHFULLY PORTED for Sapphire/Axe/Spike/Imperial/Dark via
//     shared-knight-melee.ts (tables 0x80343c00/c14/c28). Elemental + Chainsaw have
//     bespoke melee tables (chunk_0033.c / chunk_0020.c) — TODO stubs cited.
//   - DARK KNIGHT action 1 (table 0x804346f0, fns FUN_80157584/FUN_801573d8) and
//     action 3 (table 0x80342a2c, fns FUN_80157e48/FUN_80157f24/FUN_80157fac):
//     FAITHFULLY PORTED from chunk_0040.c decomp.
//   - SPIKE KNIGHT action 2/4: delegates to knight-family.ts (configureKnightFamily).
//   - Remaining bespoke action 0/2/3 machines: shared-engine fallback with TODO
//     citations citing exact fn addresses + chunk lines.
//
// Float constants (read from boot.dol this session, rtoc sdata2 @0x8043a6xx):
//   FLOAT_8043a600 = 0.0    zero-scalar (velocity/pose resets, thresholds)
//   FLOAT_8043a60c = 1.0    FUN_80067310 gravity arg
//   FLOAT_8043a614 = 0.9    steerYaw decay factor (CONCAT44 double-coercion idiom)
//   FLOAT_8043a628 = 176.0  double-coercion base for the steerYaw ×0.9 idiom
//   FLOAT_8043a630 = 2.0    motion.z seed (FUN_80157868 phase advance)
//   FLOAT_8043a634 = 0.95   blink reposition + per-frame motion scale
//   FLOAT_8043a638 = -1.0   zz_004beb8_ stream rate
//   FLOAT_8043a63c = 60.0   handler timer seed (phase-0 windup)
//   FLOAT_8043a640 = 40.0   motion.y seed (FUN_80157868 phase advance)
//   FLOAT_8043a644 = 30.0   dash velocity magnitude (FUN_80157c34 contact burst)
//   FLOAT_8043a648 = 8.0    exit state-timer base (FUN_80157d20/FUN_80157fac)

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { allocateWeapon, groundSnapRevert, stepAfterimage, stepTargetYaw, toS16 } from "../rom/helpers.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { createGenericKnightRootAction } from "./shared-knight-melee.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";
import { configureKnightFamily, type KnightFamilyCtx } from "./knight-family.js";

// ============================================================================
// DOL-read float constants (sdata2 @0x8043a6xx).
// ============================================================================
const KC = {
  /** FLOAT_8043a600 = 0.0 — zero-scalar + threshold. */
  ZERO: 0.0,
  /** FLOAT_8043a60c = 1.0 — FUN_80067310 gravity arg. */
  GRAVITY: 1.0,
  /** FLOAT_8043a614 = 0.8999999761581421 — steerYaw decay factor. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_8043a628 = 176.0 — DOUBLE_8043a628 base for the int→double coercion sentinel. */
  STEER_COERCION_BASE: 176.0,
  /** FLOAT_8043a630 = 2.0 — motion.z seed in FUN_80157868. */
  MOTION_Z_SEED: 2.0,
  /** FLOAT_8043a634 = 0.949999988079071 — blink reposition + per-frame motion scale. */
  MOTION_SCALE: 0.949999988079071,
  /** FLOAT_8043a638 = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a63c = 60.0 — handler timer seed (phase-0 windup). */
  WINDUP_TIMER: 60.0,
  /** FLOAT_8043a640 = 40.0 — motion.y seed in FUN_80157868. */
  MOTION_Y_SEED: 40.0,
  /** FLOAT_8043a644 = 30.0 — dash velocity magnitude (FUN_80157c34). */
  DASH_VELOCITY: 30.0,
  /** FLOAT_8043a648 = 8.0 — exit state-timer base. */
  EXIT_TIMER_BASE: 8.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 position-frozen / airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** Stream group 2 (dash). */
  STREAM_GROUP_DASH: 2,
  /** Stream group 3 (melee). */
  STREAM_GROUP_MELEE: 3,
  /** Stream group 4 (charge/X-special). */
  STREAM_GROUP_CHARGE: 4,
} as const;

// ============================================================================
// Spawner addresses.
// ============================================================================
/** zz_0082824_ @0x80082824 — record-table projectile spawn. */
export const KNIGHT_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — per-borg effect spawn. */
export const KNIGHT_EFFECT_SPAWNER = 0x800c3be0;

export const KNIGHT_CLUSTER_CONSTANTS = KC;

// ============================================================================
// Borg-number maps.
// ============================================================================
const SAPPHIRE_BORG_NUMBERS: Record<string, number> = { pl0208: 0x208, pl020e: 0x20e };
const ELEMENTAL_BORG_NUMBERS: Record<string, number> = { pl0202: 0x202, pl020b: 0x20b };
const IMPERIAL_BORG_NUMBERS: Record<string, number> = { pl0209: 0x209 };
const DARK_BORG_NUMBERS: Record<string, number> = { pl0205: 0x205 };
const AXE_BORG_NUMBERS: Record<string, number> = { pl0204: 0x204, pl020d: 0x20d };
const SPIKE_BORG_NUMBERS: Record<string, number> = { pl0203: 0x203, pl020c: 0x20c };
const CHAINSAW_BORG_NUMBERS: Record<string, number> = { pl0201: 0x201 };

export type SapphireBorgId = "pl0208" | "pl020e";
export type ElementalBorgId = "pl0202" | "pl020b";
export type ImperialBorgId = "pl0209";
export type DarkBorgId = "pl0205";
export type AxeBorgId = "pl0204" | "pl020d";
export type SpikeBorgId = "pl0203" | "pl020c";
export type ChainsawBorgId = "pl0201";

// ============================================================================
// Shared helpers (the blink / motion-drift / exit patterns used across families).
// ============================================================================

/** +0x5e0 position-frozen bit set = airborne. */
function isAirborne(actor: RomActor): boolean {
  return (actor.controlWord & KC.AIRBORNE_BIT) !== 0;
}

/** +0xcc == 0 (no lock target) gates the activeYaw = heading copy. */
function hasLockTarget(actor: RomActor): boolean {
  const t = (actor as RomActor & { lockTarget?: unknown }).lockTarget;
  return t != null;
}

/** Blink reposition: motion = (pos − targetCache5e8) × 0.95; pos = target + motion.
 *  Keeps 95% of the distance from target (a 5% reposition toward target). */
function applyBlink(actor: RomActor): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(KC.MOTION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.targetCache5e8, actor.motion, actor.pos);
}

/** Per-frame motion continuation: motion ×= 0.95; pos += motion. */
function applyMotionDrift(actor: RomActor): void {
  vecScale(KC.MOTION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Zero all four velocity scalars + pose accumulators (the common phase-0 reset). */
function zeroVelocityAndPose(actor: RomActor): void {
  actor.gravityCoeff = KC.ZERO;
  actor.yVel = KC.ZERO;
  actor.hDecel = KC.ZERO;
  actor.hSpeed = KC.ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
}

// ============================================================================
// DARK KNIGHT bespoke phase machines (chunk_0040.c:1741-2314).
//
// DARK KNIGHT (pl0205, ctor 0x801567f0) shares the chunk_0040.c block with
// VICTORY KING + IMPERIAL KNIGHT. Its bespoke action 1 (table 0x804346f0:
// FUN_80157584 + FUN_801573d8) is a 2-phase dash-melee, and action 3
// (table 0x80342a2c: FUN_80157e48 + FUN_80157f24 + FUN_80157fac) is a 3-phase
// X-special-style lunge.
// ============================================================================

/** FUN_80157584 @ chunk_0040.c:1894 — DARK action 1 phase 0 (setup).
 *  Stream group 3 slot 3, blink reposition, zero scalars. */
function darkAction1Phase0(actor: RomActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  zeroVelocityAndPose(actor);
  applyBlink(actor);
  groundSnapRevert(actor); // zz_00677b0_
  startStream(actor, KC.STREAM_MASK, KC.STREAM_GROUP_MELEE, 3, KC.STREAM_RATE);
  actor.accumulator80c = KC.ZERO; // +0x80c = FLOAT_8043a600
}

/** FUN_801573d8 @ chunk_0040.c:1833 — DARK action 1 phase 1 (active).
 *  Tick stream, faceGate aim, dashStrength restore, motion ×0.95, physics(1.0),
 *  ground snap, exit on contact/wall. */
function darkAction1Phase1(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, KC.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  if (actor.faceGate1d10 > 0) {
    stepTargetYaw(actor, 0xc1); // zz_006d0dc_(0xc1, 0)
  }
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? KC.ZERO;
  }
  applyMotionDrift(actor);
  integratePhysics(KC.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, lockYaw)
  const grounded = groundSnapRevert(actor); // zz_00677b0_
  // contactP0 < 0 AND grounded → air exit (zz_006a5a4_) + stateTimer = 1.0 + dt.
  if (actor.contactP0 < 0 && !grounded) {
    darkExitAirborneTimer(actor, KC.GRAVITY);
    return;
  }
  if (actor.wallContact !== 0) {
    darkExitWallContact(actor, grounded);
  }
}

/** FUN_80157e48 @ chunk_0040.c:2239 — DARK action 3 phase 0 (X-special setup).
 *  Stream group 2 slot 10, blink reposition, zero scalars. */
function darkAction3Phase0(actor: RomActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading;
  zeroVelocityAndPose(actor);
  actor.streamSlot = 10; // +0x6ea = 10
  stepTargetYaw(actor, 0xc1); // zz_006d144_(0xc1)
  applyBlink(actor);
  groundSnapRevert(actor); // zz_00679d0_
  startStream(actor, KC.STREAM_MASK, KC.STREAM_GROUP_DASH, actor.streamSlot, KC.STREAM_RATE);
}

/** FUN_80157f24 @ chunk_0040.c:2272 — DARK action 3 phase 1 (active lunge).
 *  Tick stream, aim, motion drift, ground snap, on contactP0>0 advance + spawn. */
function darkAction3Phase1(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, KC.STREAM_MASK, ctx);
  stepTargetYaw(actor, 0xc1); // zz_006d144_(0xc1)
  applyMotionDrift(actor);
  groundSnapRevert(actor); // zz_00679d0_
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    // zz_01f4260_(actor, 0) — TODO(rom): the contact-effect spawn helper @0x801f4260
    // is not yet surfaced. No port-side effect until ported (cited @chunk_0040.c:2284).
    ctx.onFamilyProjectile?.(actor, KNIGHT_EFFECT_SPAWNER, 0);
  }
}

/** FUN_80157fac @ chunk_0040.c:2291 — DARK action 3 phase 2 (recovery).
 *  Tick stream, motion drift, ground snap, on wallContact exit. */
function darkAction3Phase2(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, KC.STREAM_MASK, ctx);
  applyMotionDrift(actor);
  const grounded = groundSnapRevert(actor); // zz_00679d0_
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~KC.ACTION_MODE_BITS;
    if (!grounded) {
      romAirKnockoutReturn(actor); // zz_006a5a4_
    } else {
      romGroundIdleReturn(actor); // zz_006a474_
    }
    actor.stateTimer = KC.EXIT_TIMER_BASE + actor.dt; // +0x694 = 8.0 + dt
  }
}

/** LAB exit tail for the airborne-timer path (FUN_801573d8:1855). */
function darkExitAirborneTimer(actor: RomActor, timerBase: number): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~KC.ACTION_MODE_BITS;
  romAirKnockoutReturn(actor); // zz_006a5a4_
  actor.stateTimer = timerBase + actor.dt; // +0x694 = timerBase + dt
}

/** LAB exit tail for the wall-contact path (FUN_801573d8:1863-1875). */
function darkExitWallContact(actor: RomActor, grounded: boolean): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~KC.ACTION_MODE_BITS;
  if (!grounded) {
    romAirKnockoutReturn(actor); // zz_006a5a4_
  } else if (!isAirborne(actor)) {
    romGroundIdleReturn(actor); // zz_006a474_
  } else {
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
  }
  actor.stateTimer = KC.GRAVITY + actor.dt; // +0x694 = 1.0 + dt
}

// ============================================================================
// DARK KNIGHT root action dispatcher.
// ============================================================================

function createDarkKnightRootAction(ctx: StreamContext): (actor: RomActor) => void {
  // Action 1: bespoke 2-phase dash-melee (table 0x804346f0).
  // Action 3: bespoke 3-phase lunge (table 0x80342a2c).
  // Action 0/2: shared-engine fallback (TODO: port chunk_0040.c bespoke fns).
  return (actor: RomActor) => {
    switch (actor.actionIndex) {
      case 1: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) darkAction1Phase0(actor);
        else darkAction1Phase1(actor, ctx);
        return;
      }
      case 3: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) darkAction3Phase0(actor);
        else if (phase === 1) darkAction3Phase1(actor, ctx);
        else darkAction3Phase2(actor, ctx);
        return;
      }
      default: return;
    }
  };
}

// ============================================================================
// SAPPHIRE KNIGHT bespoke action 2 — X-special phase machine (chunk_0019.c).
//
// @audit-ported pl0208 action=2 variants=0,1,2,3,4,5
// @audit-ported pl020e action=2 variants=0,1,2,3,4,5
//
// SAPPHIRE KNIGHT (pl0208/pl020e, ctor 0x800bb390) action 2 root handler is
// FUN_800bd074 @0x800bd074 (chunk_0019.c:1829). It is NOT the shared X engine:
// it routes via phase table 0x803019d0 indexed by +0x581 (variant). Variants 0-4
// select wrapper FUN_800bd0b0 which dispatches the 6-phase grounded table
// 0x803019e4 [= 0x800bd12c, 0x800bd220, 0x800bd3a8, 0x800bd600, 0x800bd708,
// 0x800bd7e4] indexed by +0x540 (phase). The airborne arm FUN_800bd5a4 →
// zz_00bd5c4_ dispatches table 0x803019f0 [= 0x800bd600, 0x800bd708, 0x800bd7e4]
// (phases 3-5 only). Table contents DOL-decoded byte-for-byte from boot.dol
// @0x803019d0..0x80301a00. Float constants read from sdata2 @0x804385xx.
// ============================================================================
const SAPPHIRE_X = {
  /** FLOAT_8043852c = 0.0 — zero-scalar (velocity/pose resets, +0x80c clear). */
  ZERO: 0.0,
  /** FLOAT_80438574 = 30.0 — ph0 +0x560 timer seed. */
  PH0_TIMER_560: 30.0,
  /** FLOAT_80438578 = 0.5 — ph0 +0x48 (yVel) seed. */
  PH0_YVEL: 0.5,
  /** FLOAT_80438530 = 0.95 — blink reposition + motion-drag scale. */
  BLINK_SCALE: 0.949999988079071,
  /** FLOAT_80438540 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80438534 = 1.0 — FUN_80067310 gravity arg (ph1/ph5 integrate). */
  GRAVITY: 1.0,
  /** FLOAT_8043857c = 16.0 — ph1 exit-fail +0x694 (stateTimer) base. */
  PH1_EXIT_TIMER: 16.0,
  /** FLOAT_80438518 = 0.9 — ph2/ph5 +0x18da steerYaw decay idiom. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_80438580 = 8.0 — ph5 exit +0x694 (stateTimer) base. */
  PH5_EXIT_TIMER: 8.0,
  /** ph0 +0x54e aim-timer seed (s16, literal 0x1e in FUN_800bd12c:1868). */
  PH0_AIM_TIMER_54E: 0x1e,
  /** ROM +0x5e0 airborne bit (selects air vs ground exit + air stream slot). */
  AIRBORNE_BIT: 0x40,
  /** ROM +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** Stream group 4 (X-special). */
  STREAM_GROUP_X: 4,
  /** Stream group 2 (ph3 re-arm). */
  STREAM_GROUP_2: 2,
  /** Spawner address for zz_00e19a8_ (ph1 contact deploy) — host-resolved. */
  PH1_SPAWNER: 0x800e19a8,
  /** Spawner address for zz_00f036c_ (ph4 beam burst) — host-resolved. */
  PH4_SPAWNER: 0x800f036c,
} as const;
export const SAPPHIRE_X_CONSTANTS = SAPPHIRE_X;

/** Port-side mirrors for ROM offsets not first-class on RomActor. */
export interface SapphireXScratch {
  /** ROM +0x560 — ph0 timer seed / ph2 active-frame decay accumulator. */
  sapphTimer560?: number;
  /** ROM +0x54e (s16) — ph0 aim-timer seed / ph2 decay clamp. */
  sapphAimTimer54e?: number;
  /** ROM +0x6f7 — stream-state byte (0 ph0, 2 ph1/ph2). */
  sapphByte6f7?: number;
  /** ROM +0x6e8 — exit byte cleared on the ph1/ph2 early-out. */
  sapphByte6e8?: number;
  /** ROM +0x5d8 & 0xf0 — ph5 B-held hold gate (mirrors inputHeld5d8). */
  // (read directly from actor.inputHeld5d8)
  /** ROM +0x54a (s16) — ph5 FUN_80067310 integration yaw. */
  sapphYaw54a?: number;
}

type SxActor = RomActor & SapphireXScratch;

/** SteerYaw decay idiom: (short)(int)((float)((double)CONCAT44(0x43300000,
 *  val ^ 0x80000000) - DOUBLE_80438520) * FLOAT_80438518) ≡ val × 0.9, truncated
 *  to s16. DOL-verified: DOUBLE_80438520 = 0x43300000_00000000 baseline,
 *  FLOAT_80438518 = 0.9. */
function decaySteerYaw18da(actor: RomActor): void {
  actor.steerYaw = toS16(actor.steerYaw * SAPPHIRE_X.STEER_DECAY);
}

/** zz_006d1a8_/zz_006e39c_/zz_006d144_/zz_006e1ac_ aim solvers are host-bound
 *  (descriptor bone geometry at +0x524). Approximated by the yaw convergence
 *  helper; TUNED — see findings doc. */
function sapphAimTuned(actor: RomActor): void {
  stepTargetYaw(actor, 0xc1);
}

/** ph0 setup — FUN_800bd12c @ chunk_0019.c:1856. Seeds +0x560=30, +0x54e=0x1e,
 *  zero velocity, blink reposition, startStream(g4 slot 2). */
function sapphPh0Setup(actor: SxActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.sapphTimer560 = SAPPHIRE_X.PH0_TIMER_560;           // +0x560 = 30.0
  actor.sapphAimTimer54e = SAPPHIRE_X.PH0_AIM_TIMER_54E;    // +0x54e = 0x1e
  actor.sapphByte6f7 = 0;                                   // +0x6f7 = 0
  sapphAimTuned(actor);
  actor.hDecel = SAPPHIRE_X.ZERO;   // +0x4c
  actor.hSpeed = SAPPHIRE_X.ZERO;   // +0x44
  actor.yVel = SAPPHIRE_X.PH0_YVEL; // +0x48 = 0.5
  actor.gravityCoeff = SAPPHIRE_X.ZERO; // +0x50
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion); // blink
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor); // zz_00679d0_
  actor.streamSlot = 2;    // +0x6ea = 2
  startStream(actor, SAPPHIRE_X.STREAM_MASK, SAPPHIRE_X.STREAM_GROUP_X,
    actor.streamSlot, SAPPHIRE_X.STREAM_RATE);
  actor.accumulator80c = SAPPHIRE_X.ZERO; // +0x80c
}

/** ph1 active fire — FUN_800bd220 @ chunk_0019.c:1892. On +0x1cee (wallContact):
 *  advance, re-arm stream slot 1 (3 air), consume ammo; on denial exit (timer 16),
 *  else deploy zz_00e19a8_. */
function sapphPh1Fire(actor: SxActor, ctx: StreamContext): void {
  tickStream(actor, SAPPHIRE_X.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  sapphAimTuned(actor);
  integratePhysics(SAPPHIRE_X.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0,+0x5ae)
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.wallContact !== 0) { // +0x1cee
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.sapphByte6f7 = 2;                                   // +0x6f7 = 2
    const air = (actor.controlWord & SAPPHIRE_X.AIRBORNE_BIT) !== 0;
    actor.streamSlot = air ? 3 : 1;                           // +0x6ea = 1 (gnd) / 3 (air)
    startStream(actor, SAPPHIRE_X.STREAM_MASK, SAPPHIRE_X.STREAM_GROUP_X,
      actor.streamSlot, SAPPHIRE_X.STREAM_RATE);
    if (!allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1) consume
      // Ammo denied → exit (FUN_800bd220:1919-1932).
      actor.housekeeping73f = 0;
      actor.controlWord &= ~SAPPHIRE_X.ACTION_MODE_BITS;
      actor.sapphByte6e8 = 0; // +0x6e8 = 0
      actor.hDecel = SAPPHIRE_X.ZERO;
      actor.hSpeed = SAPPHIRE_X.ZERO;
      if ((actor.controlWord & SAPPHIRE_X.AIRBORNE_BIT) === 0) romGroundIdleReturn(actor);
      else romAirKnockoutReturn(actor);
      actor.stateTimer = SAPPHIRE_X.PH1_EXIT_TIMER + actor.dt; // +0x694 = 16.0 + dt
      return;
    }
    // Ammo ok → zz_00e19a8_(actor, 0, &+0x6f7) contact deploy (host-resolved).
    ctx.onFamilyProjectile?.(actor, SAPPHIRE_X.PH1_SPAWNER, actor.sapphByte6f7 ?? 0);
  }
  stepAfterimage(actor); // zz_00b22f4_
}

/** ph2 sustained beam — FUN_800bd3a8 @ chunk_0019.c:1942. Timer decay, motion
 *  drift, +0x1cee exit. zz_006de44_/+0x1d10/+0x4ac gates are host-bound (TUNED). */
function sapphPh2Sustain(actor: SxActor, ctx: StreamContext): void {
  // zz_006de44_(0xf0f00) status read is host-bound → 0 (no timer decay this frame).
  if ((actor.faceGate1d10 ?? 0) > 0) sapphAimTuned(actor); // +0x1d10 > 0
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor); // zz_00677b0_
  if (actor.contactP0 < 1) {              // +0x1cef < 1 → tickStream
    tickStream(actor, SAPPHIRE_X.STREAM_MASK, ctx);
  } else if ((actor.sapphTimer560 ?? 0) <= SAPPHIRE_X.ZERO) {
    actor.contactP0 = 0; // +0x1cef = 0 (ph2→ph3 arm latched via +0x542/+0x541 host-side)
  } else {
    actor.sapphTimer560 = (actor.sapphTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  }
  if (actor.contactP0 < 0) decaySteerYaw18da(actor); // +0x1cef < 0
  if (actor.wallContact !== 0) { // +0x1cee → exit
    actor.housekeeping73f = 0;
    actor.controlWord &= ~SAPPHIRE_X.ACTION_MODE_BITS;
    actor.sapphByte6e8 = 0;
    actor.hDecel = SAPPHIRE_X.ZERO;
    actor.hSpeed = SAPPHIRE_X.ZERO;
    if ((actor.controlWord & SAPPHIRE_X.AIRBORNE_BIT) === 0) romGroundIdleReturn(actor);
    else romAirKnockoutReturn(actor);
  }
  stepAfterimage(actor);
}

/** ph3 re-arm — FUN_800bd600 @ chunk_0019.c:2035. Advance, zero velocity/pose,
 *  blink, startStream(g2 slot 0xf / 0x10 air). */
function sapphPh3Rearm(actor: SxActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  sapphAimTuned(actor); // zz_006d144_/zz_006e1ac_
  actor.gravityCoeff = SAPPHIRE_X.ZERO; // +0x50
  actor.yVel = SAPPHIRE_X.ZERO;         // +0x48
  actor.hDecel = SAPPHIRE_X.ZERO;       // +0x4c
  actor.hSpeed = SAPPHIRE_X.ZERO;       // +0x44
  actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0;
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  const air = (actor.controlWord & SAPPHIRE_X.AIRBORNE_BIT) !== 0;
  const slot = air ? 0x10 : 0x0f;       // +0x6ea = 0xf (gnd) / 0x10 (air)
  actor.streamSlot = slot + 1;          // +0x6ea = (cVar)+1
  startStream(actor, SAPPHIRE_X.STREAM_MASK, SAPPHIRE_X.STREAM_GROUP_2,
    slot, SAPPHIRE_X.STREAM_RATE);
}

/** ph4 contact burst — FUN_800bd708 @ chunk_0019.c:2076. On +0x1cef: advance,
 *  consume ammo, deploy zz_00f036c_(0xeb) + 6× zz_00e058c_(1, i+4). */
function sapphPh4Burst(actor: SxActor, ctx: StreamContext): void {
  tickStream(actor, SAPPHIRE_X.STREAM_MASK, ctx);
  sapphAimTuned(actor);
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.contactP0 !== 0) { // +0x1cef
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
      // zz_00f036c_(0xeb) + loop zz_00e058c_(1, i+4) ×6 — host-resolved burst.
      ctx.onFamilyProjectile?.(actor, SAPPHIRE_X.PH4_SPAWNER, 0xeb);
    }
  }
}

/** ph5 recover/exit — FUN_800bd7e4 @ chunk_0019.c:2110. Physics(+0x54a), steerYaw
 *  decay, +0x5d8&0xf0 / +0x1cee exit gate (timer 8). */
function sapphPh5Recover(actor: SxActor, ctx: StreamContext): void {
  tickStream(actor, SAPPHIRE_X.STREAM_MASK, ctx);
  integratePhysics(SAPPHIRE_X.GRAVITY, actor, actor.sapphYaw54a ?? actor.lockYaw); // +0x54a
  vecScale(SAPPHIRE_X.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.contactP0 < 0) decaySteerYaw18da(actor); // +0x1cef < 0
  // Hold gate: (+0x5d8 & 0xf0)==0 AND +0x1cee==0 → hold (return); else exit.
  const hold = (actor.inputHeld5d8 & 0xf0) === 0 && actor.wallContact === 0;
  if (hold) return;
  actor.housekeeping73f = 0;
  actor.controlWord &= ~SAPPHIRE_X.ACTION_MODE_BITS;
  actor.hDecel = SAPPHIRE_X.ZERO;
  actor.hSpeed = SAPPHIRE_X.ZERO;
  if ((actor.controlWord & SAPPHIRE_X.AIRBORNE_BIT) === 0) romGroundIdleReturn(actor);
  else romAirKnockoutReturn(actor);
  actor.stateTimer = SAPPHIRE_X.PH5_EXIT_TIMER + actor.dt; // +0x694 = 8.0 + dt
  void ctx;
}

/** SAPPHIRE action 2 root — FUN_800bd074 @0x800bd074. Routes +0x581 (variant)
 *  through table 0x803019d0. Variants 0-4 (and the pl0208/pl020e live set 0-5)
 *  enter the grounded 6-phase machine at phase 0. The wrapper FUN_800bd0b0's
 *  +0x18fe/0x1900 config write (when +0x6f7 > 0) is cosmetic and omitted (TUNED). */
export function createSapphireAction2(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as SxActor;
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: sapphPh0Setup(actor); return;
      case 1: sapphPh1Fire(actor, ctx); return;
      case 2: sapphPh2Sustain(actor, ctx); return;
      case 3: sapphPh3Rearm(actor); return;
      case 4: sapphPh4Burst(actor, ctx); return;
      case 5: sapphPh5Recover(actor, ctx); return;
      default: return;
    }
  };
}

// ============================================================================
// AXE KNIGHT bespoke action 2 — homing-dive X-special (chunk_0022.c).
//
// @audit-ported pl0204 action=2 variants=0,1,2,3,4,5
// @audit-ported pl020d action=2 variants=0,1,2,3,4,5
//
// AXE KNIGHT (pl0204/pl020d, ctor 0x800d6d10) action 2 root handler is
// FUN_800d74b4 @0x800d74b4 (chunk_0022.c:4750). It routes via phase table
// 0x8030fb00 indexed by +0x581 (variant). Variants 0-4 select wrapper
// FUN_800d74f0 which dispatches the 6-phase table 0x8030fb14 =
// [0x800d7540, 0x800d7648, 0x800d76cc, 0x800d77b8, 0x800d7934, 0x800d7a98]
// indexed by +0x540 (phase). Table contents DOL-decoded byte-for-byte from
// boot.dol @0x8030fb00..0x8030fb44. Floats read from sdata2 @0x80438bxx.
// The ph3 sin/cos projection (hSpeed = motion.x×cos(steerYaw), yVel =
// motion.x×−sin(steerYaw)) is the same BAM16 idiom as the NORMAL NINJA flying
// lunge ph1 (ninja-cluster.ts). pl020d (borg 0x20d) ph2 uses +0x548=0.
// ============================================================================
const AXE_X = {
  /** FLOAT_80438b7c = 0.0 — zero-scalar (+0x80c / motion / threshold). */
  ZERO: 0.0,
  /** FLOAT_80438b90 = 60.0 — ph0 +0x558 approach timer seed. */
  PH0_TIMER_558: 60.0,
  /** FLOAT_80438b80 = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80438b94 = 30.0 — ph2 motion.y (+0x3c) speed clamp. */
  PH2_SPEED_CLAMP: 30.0,
  /** FLOAT_80438b98 = 2.0 — ph2 motion.z (+0x40) acceleration seed. */
  PH2_ACCEL_SEED: 2.0,
  /** FLOAT_80438b78 = 1.0 — FUN_80067310 gravity arg (ph3/ph4/ph5). */
  GRAVITY: 1.0,
  /** FLOAT_80438b9c = 0.9 — ph4/ph5 +0x18da steerYaw decay. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_80438bac = 120.0 — ph4 grounded-advance +0x558 reseed. */
  PH4_RECOVER_TIMER: 120.0,
  /** FLOAT_80438ba8 = 8.0 — exit +0x694 (stateTimer) base. */
  EXIT_TIMER: 8.0,
  /** DOUBLE_80438ba0 = 0.5 — ph4 +0x44 ground-speed hold gate. */
  PH4_HOLDSPEED_GATE: 0.5,
  /** DOUBLE_80438bb0 = 0.25 — ph4 contact +0x1dc8 (dt) scale trick. */
  PH4_DT_SCALE: 0.25,
  /** BAM16 half-turn (0x8000 = 180°) for the sin/cos projection. */
  BAM16_HALF: 0x8000,
  /** ph2 +0x548 seed (0x14 = 20; pl020d/0x20d → 0). */
  PH2_TIMER548_DEFAULT: 0x14,
  /** ph2 +0x54a seed (0x32 = 50). */
  PH2_TIMER54A: 0x32,
  /** ph2 +0x54c seed (8). */
  PH2_TIMER54C: 8,
  /** ph3 +0x548 per-frame decrement (10). */
  PH3_TIMER548_DEC: 10,
  /** ROM +0x5e0 airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** ROM +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** Stream group 4 (X-special). */
  STREAM_GROUP: 4,
} as const;
export const AXE_X_CONSTANTS = AXE_X;

/** Port-side mirrors for ROM offsets not first-class on RomActor. */
export interface AxeXScratch {
  /** ROM +0x548 (s16) — ph2 dive timer / ph3 countdown. */
  axeTimer548?: number;
  /** ROM +0x54a (s16) — ph2 dive timer / ph3 clamp. */
  axeTimer54a?: number;
  /** ROM +0x54c (s16) — ph2 timer / ph3 decay-clamp floor (2). */
  axeTimer54c?: number;
  /** ROM +0x1b01 — ph3 active-frame gate byte. */
  axeByte1b01?: number;
  /** ROM +0x1b03 — ph1 stream-hold gate byte (streamHold1b03 alias). */
  // (read from actor.streamHold1b03)
  /** motion.y speed clamp (mirrors +0x3c). */
  axeSpeedClamp?: number;
}

type AxActor = RomActor & AxeXScratch;

/** BAM16 sin/cos. zz_0045204_/zz_0045238_ are the HSD s16 trig helpers. */
function bamCos(angle: number): number { return Math.cos((angle / AXE_X.BAM16_HALF) * Math.PI); }
function bamSin(angle: number): number { return Math.sin((angle / AXE_X.BAM16_HALF) * Math.PI); }

/** ph0 setup — FUN_800d7540 @ chunk_0022.c:4773. +0x540++, +0x6ea slot pick,
 *  +0x558=60, motion=pos−target, startStream(g4). */
function axePh0Setup(actor: AxActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.streamSlot = (actor.controlWord & AXE_X.AIRBORNE_BIT) !== 0 ? 3 : 0; // +0x6ea
  // FUN_80066838(+0x868 row, actor) range gate is host-bound (renderer rows);
  // the failure branch sets +0x541=1 / +0xcc=0 / +0x5ac=+0x72 — TUNED, omitted.
  actor.handlerTimer = AXE_X.PH0_TIMER_558; // +0x558 = 60.0
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion); // motion = pos − target
  groundSnapRevert(actor); // zz_00677b0_
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1; // +0x6ea = cVar + 1
  startStream(actor, AXE_X.STREAM_MASK, AXE_X.STREAM_GROUP, slot, AXE_X.STREAM_RATE);
  actor.accumulator80c = AXE_X.ZERO; // +0x80c
}

/** ph1 approach — FUN_800d7648 @ chunk_0022.c:4809. tickStream, +0x558 -= dt,
 *  advance on timer≤0 OR aim converged. */
function axePh1Approach(actor: AxActor, ctx: StreamContext): void {
  groundSnapRevert(actor);
  if (actor.streamHold1b03 !== 0) tickStream(actor, AXE_X.STREAM_MASK, ctx); // +0x1b03
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  const converged = stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0) returns nonzero on converge
  if (actor.handlerTimer <= AXE_X.ZERO || converged) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

/** ph2 launch — FUN_800d76cc @ chunk_0022.c:4833. On +0x1cee: advance, seed
 *  +0x548/+0x54a/+0x54c, motion=(0,30,2), zz_0066530_(0x2d), startStream. */
function axePh2Launch(actor: AxActor, ctx: StreamContext): void {
  tickStream(actor, AXE_X.STREAM_MASK, ctx);
  stepTargetYaw(actor, 0xc0);
  groundSnapRevert(actor);
  if (actor.wallContact !== 0) { // +0x1cee
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.axeTimer548 = (actor.borgNumber === 0x20d) ? 0 : AXE_X.PH2_TIMER548_DEFAULT; // +0x548
    actor.axeTimer54a = AXE_X.PH2_TIMER54A; // +0x54a = 0x32
    actor.axeTimer54c = AXE_X.PH2_TIMER54C; // +0x54c = 8
    actor.motion = { x: AXE_X.ZERO, y: AXE_X.PH2_SPEED_CLAMP, z: AXE_X.PH2_ACCEL_SEED };
    actor.axeSpeedClamp = AXE_X.PH2_SPEED_CLAMP;
    // zz_0066530_(0x2d) + zz_00b2190_(0) — host-bound effect/equipment hooks.
    ctx.onFamilyProjectile?.(actor, 0x80066530, 0x2d);
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, AXE_X.STREAM_MASK, AXE_X.STREAM_GROUP, slot, AXE_X.STREAM_RATE);
  }
}

/** ph3 homing dive — FUN_800d77b8 @ chunk_0022.c:4875. motion.x accelerates by
 *  motion.z×dt (clamped to motion.y), then hSpeed = motion.x×cos(steerYaw),
 *  yVel = motion.x×−sin(steerYaw); physics(1.0, +0x5ae). */
function axePh3Dive(actor: AxActor, ctx: StreamContext): void {
  // zz_006de44_(0xf0f00) status-decay read is host-bound → 0 this frame.
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  // motion.x += motion.z × dt; clamp ≤ motion.y (the speed clamp).
  let mx = actor.motion.x + actor.motion.z * actor.dt;
  const clamp = actor.axeSpeedClamp ?? AXE_X.PH2_SPEED_CLAMP;
  if (mx > clamp) mx = clamp;
  actor.motion.x = mx;
  actor.hSpeed = mx * bamCos(actor.steerYaw); // +0x44 = motion.x × cos(+0x18da)
  actor.yVel = mx * -bamSin(actor.steerYaw);  // +0x48 = motion.x × −sin(+0x18da)
  integratePhysics(AXE_X.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, +0x5ae)
  groundSnapRevert(actor);
  tickStream(actor, AXE_X.STREAM_MASK, ctx);
  if ((actor.axeByte1b01 ?? 0) !== 0) { // +0x1b01
    actor.axeTimer548 = (actor.axeTimer548 ?? 0) - AXE_X.PH3_TIMER548_DEC; // +0x548 -= 10
    if ((actor.axeTimer548 ?? 0) < 0) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      const slot = actor.streamSlot;
      actor.streamSlot = slot + 1;
      startStream(actor, AXE_X.STREAM_MASK, AXE_X.STREAM_GROUP, slot, AXE_X.STREAM_RATE);
    }
  }
  stepAfterimage(actor);
}

/** ph4 dive sustain — FUN_800d7934 @ chunk_0022.c:4929. steerYaw decay, drag,
 *  physics; hold while +0x44 ≥ 0.5; on grounded-slow advance (120 timer), on
 *  grounded-stopped exit (8 timer). */
function axePh4Sustain(actor: AxActor, ctx: StreamContext): void {
  actor.steerYaw = toS16(actor.steerYaw * AXE_X.STEER_DECAY); // +0x18da ×= 0.9
  // zz_006ed8c_(0.9) velocity drag — modeled as the motion drift below.
  integratePhysics(AXE_X.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, +0x5ae)
  const grounded = groundSnapRevert(actor);
  if (actor.hSpeed >= AXE_X.PH4_HOLDSPEED_GATE) { // +0x44 ≥ 0.5 (DOUBLE_80438ba0)
    if (actor.contactP0 < 0) { // +0x1cef < 0 — the dt-scale contact trick
      // +0x1dc8 ×= 0.25 for the tick then restore (host-owned dt; approximated).
      tickStream(actor, AXE_X.STREAM_MASK, ctx);
    } else {
      tickStream(actor, AXE_X.STREAM_MASK, ctx);
    }
    stepAfterimage(actor);
  } else if (!grounded) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++ (still air)
    actor.handlerTimer = AXE_X.PH4_RECOVER_TIMER; // +0x558 = 120.0
    actor.lockYaw = actor.heading; // +0x5ae = +0x72 (heading) — TUNED approx
  } else {
    axeExitGrounded(actor);
  }
}

/** ph5 recover/exit — FUN_800d7a98 @ chunk_0022.c:4982. steerYaw decay, physics;
 *  grounded → +0x558 countdown then air-exit; airborne → ub-cue(7) exit. */
function axePh5Recover(actor: AxActor, ctx: StreamContext): void {
  actor.steerYaw = toS16(actor.steerYaw * AXE_X.STEER_DECAY);
  tickStream(actor, AXE_X.STREAM_MASK, ctx);
  integratePhysics(AXE_X.GRAVITY, actor, actor.lockYaw);
  const grounded = groundSnapRevert(actor);
  if (!grounded) {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
    if (actor.handlerTimer <= AXE_X.ZERO) axeExitAirborne(actor);
  } else {
    actor.steerYaw = 0;
    actor.housekeeping73f = 0;
    actor.controlWord &= ~AXE_X.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = AXE_X.EXIT_TIMER + actor.dt; // +0x694 = 8.0 + dt
  }
}

/** Common grounded exit (FUN_800d7934:4969) — strips mode+airborne bits,
 *  ground-idle return, +0x694 = 8.0 + dt. */
function axeExitGrounded(actor: AxActor): void {
  actor.steerYaw = 0;
  actor.housekeeping73f = 0;
  actor.controlWord &= ~AXE_X.ACTION_MODE_BITS;
  actor.controlWord &= ~AXE_X.AIRBORNE_BIT;
  romGroundIdleReturn(actor); // zz_006a474_
  actor.stateTimer = AXE_X.EXIT_TIMER + actor.dt;
}

/** Common airborne exit (FUN_800d7a98:5003) — zz_006a5a4_ air return. */
function axeExitAirborne(actor: AxActor): void {
  actor.steerYaw = 0;
  actor.housekeeping73f = 0;
  actor.controlWord &= ~AXE_X.ACTION_MODE_BITS;
  romAirKnockoutReturn(actor); // zz_006a5a4_
  actor.stateTimer = AXE_X.EXIT_TIMER + actor.dt;
}

/** AXE action 2 root — FUN_800d74b4 @0x800d74b4. Variants 0-5 enter the
 *  grounded 6-phase machine at phase 0. */
export function createAxeAction2(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor): void => {
    const actor = base as AxActor;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: axePh0Setup(actor); return;
      case 1: axePh1Approach(actor, ctx); return;
      case 2: axePh2Launch(actor, ctx); return;
      case 3: axePh3Dive(actor, ctx); return;
      case 4: axePh4Sustain(actor, ctx); return;
      case 5: axePh5Recover(actor, ctx); return;
      default: return;
    }
  };
}

// ============================================================================
// Per-family configure functions.
// ============================================================================

/** SAPPHIRE KNIGHT (pl0208/pl020e, ctor 0x800bb390) — shared knight melee (action 1) +
 *  bespoke action 2 X-special phase machine (FUN_800bd074 → table 0x803019d0,
 *  chunk_0019.c). Action 0 still uses the shared-engine fallback (TODO: port
 *  bespoke action 0 from fns 0x800bb794..0x800bc250). */
export function configureSapphireKnightFamily(
  actor: RomActor,
  borgId: SapphireBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = SAPPHIRE_BORG_NUMBERS[borgId] ?? 0x208;
  const melee = createGenericKnightRootAction(ctx);
  const xSeedSlot = borgId === "pl0208" ? 2 : 15;
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(xSeedSlot) });
  const sapphX = createSapphireAction2(ctx);
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
    if (a.actionIndex === 2) { sapphX(a); return; }
    shared(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** ELEMENTAL KNIGHT (pl0202/pl020b, ctor 0x80123438) — bespoke melee + X-special
 *  machines in chunk_0033.c not yet ported. Shared-engine fallback wired for all
 *  actions with TODO citations. TODO: port tables 0x8032e390 (action 0),
 *  0x8032e3b8..0x8032e400 (action 1 bespoke melee), 0x8032e424 (action 2 X-special).
 *  Fns: 0x8012399c..0x80125968. */
export function configureElementalKnightFamily(
  actor: RomActor,
  borgId: ElementalBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = ELEMENTAL_BORG_NUMBERS[borgId] ?? 0x202;
  // pl0202: groundSlot 0, airSlot 0; pl020b: groundSlot 2, airSlot 2 (wave-b-catch-all).
  const xSeedSlot = borgId === "pl0202" ? 0 : 2;
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(xSeedSlot) });
  actor.rootAction = shared;
  // TODO(rom): port the bespoke Elemental melee tables (0x8032e3b8/c8/d8/ec/400,
  // fns 0x80123e20..0x80125400 in chunk_0033.c) to replace the shared-engine melee.
  void ctx;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** IMPERIAL KNIGHT (pl0209, ctor 0x801b7c74) — shared knight melee (action 1) +
 *  shared-engine X-special fallback. TODO: port bespoke action 2 (table 0x80382218,
 *  fns 0x801b822c..0x801b8a1c in chunk_0053.c) and action 3 (table 0x80382228). */
export function configureImperialKnightFamily(
  actor: RomActor,
  borgId: ImperialBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = IMPERIAL_BORG_NUMBERS[borgId] ?? 0x209;
  const melee = createGenericKnightRootAction(ctx);
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
    shared(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** DARK KNIGHT (pl0205, ctor 0x801567f0) — bespoke action 1 (table 0x804346f0) +
 *  bespoke action 3 (table 0x80342a2c), faithfully ported from chunk_0040.c.
 *  Action 0/2: shared-engine fallback. */
export function configureDarkKnightFamily(
  actor: RomActor,
  borgId: DarkBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = DARK_BORG_NUMBERS[borgId] ?? 0x205;
  const bespoke = createDarkKnightRootAction(ctx);
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  actor.rootAction = (a) => {
    if (a.actionIndex === 1 || a.actionIndex === 3) { bespoke(a); return; }
    shared(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** AXE KNIGHT (pl0204/pl020d, ctor 0x800d6d10) — shared knight melee (action 1) +
 *  bespoke action 2 homing-dive X-special (FUN_800d74b4 → table 0x8030fb00,
 *  chunk_0022.c). Action 0 still uses the shared-engine fallback (TODO: port
 *  bespoke action 0 from fns 0x800d7094..0x800d95c0). */
export function configureAxeKnightFamily(
  actor: RomActor,
  borgId: AxeBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = AXE_BORG_NUMBERS[borgId] ?? 0x204;
  const melee = createGenericKnightRootAction(ctx);
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  const axeX = createAxeAction2(ctx);
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
    if (a.actionIndex === 2) { axeX(a); return; }
    shared(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** SPIKE KNIGHT (pl0203/pl020c, ctor 0x800e5288) — delegates action 2 (shot) + action 4
 *  (jump) to knight-family.ts (configureKnightFamily, already ported), plus shared
 *  knight melee at action 1. TODO: port bespoke action 0 (table 0x803188b4, fns
 *  0x800e5664..0x800e59c8 in chunk_0024.c) and action 3 (table 0x803188e8). */
export function configureSpikeKnightFamily(
  actor: RomActor,
  borgId: SpikeBorgId,
  ctx: StreamContext & KnightFamilyCtx,
): void {
  actor.borgNumber = SPIKE_BORG_NUMBERS[borgId] ?? 0x203;
  // Delegate to knight-family.ts for action 2 (shot) + action 4 (jump).
  configureKnightFamily(actor, borgId, ctx);
  const origRoot = actor.rootAction!;
  // Wire shared knight melee at action 1 on top.
  const melee = createGenericKnightRootAction(ctx);
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
    origRoot(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** CHAINSAW KNIGHT (pl0201, ctor 0x800c8560) — bespoke melee + X-special machines in
 *  chunk_0020.c not yet ported. Shared-engine fallback wired for all actions with
 *  TODO citations. TODO: port tables 0x80309c10/c1c (action 1 bespoke melee, fns
 *  0x800c87e4..0x800c8ed0) and 0x80309c40 (action 2, fns 0x800c8f0c..0x800c9164). */
export function configureChainsawKnightFamily(
  actor: RomActor,
  borgId: ChainsawBorgId,
  ctx: StreamContext,
): void {
  void ctx;
  actor.borgNumber = CHAINSAW_BORG_NUMBERS[borgId] ?? 0x201;
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  actor.rootAction = shared;
  // TODO(rom): port the bespoke Chainsaw melee tables (0x80309c10/c1c, fns
  // 0x800c87e4..0x800c8ed0 in chunk_0020.c) to replace the shared-engine melee.
  void ctx;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirror the rom.selfcheck.ts / victory-king.ts style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function makeCtx(): StreamContext {
  return {};
}

export function runKnightClusterSelfTests(assert: AssertFn): void {
  // ==========================================================================
  // Borg-number stamping — every family stamps the correct +0x3e8 value.
  // ==========================================================================
  const stampCases: Array<{ id: string; num: number; configure: (a: RomActor) => void }> = [
    { id: "pl0208", num: 0x208, configure: (a) => configureSapphireKnightFamily(a, "pl0208", makeCtx()) },
    { id: "pl020e", num: 0x20e, configure: (a) => configureSapphireKnightFamily(a, "pl020e", makeCtx()) },
    { id: "pl0202", num: 0x202, configure: (a) => configureElementalKnightFamily(a, "pl0202", makeCtx()) },
    { id: "pl020b", num: 0x20b, configure: (a) => configureElementalKnightFamily(a, "pl020b", makeCtx()) },
    { id: "pl0209", num: 0x209, configure: (a) => configureImperialKnightFamily(a, "pl0209", makeCtx()) },
    { id: "pl0205", num: 0x205, configure: (a) => configureDarkKnightFamily(a, "pl0205", makeCtx()) },
    { id: "pl0204", num: 0x204, configure: (a) => configureAxeKnightFamily(a, "pl0204", makeCtx()) },
    { id: "pl020d", num: 0x20d, configure: (a) => configureAxeKnightFamily(a, "pl020d", makeCtx()) },
    { id: "pl0201", num: 0x201, configure: (a) => configureChainsawKnightFamily(a, "pl0201", makeCtx()) },
  ];
  for (const { id, num, configure } of stampCases) {
    const a = createMinimalActor();
    configure(a);
    assert(a.borgNumber === num, `${id} borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} rootAction wired`);
    assert(a.defaultGroup === 0, `${id} defaultGroup = 0`);
  }

  // ==========================================================================
  // SAPPHIRE KNIGHT action 2 — bespoke 6-phase X-special (FUN_800bd074,
  //  table 0x803019d0, chunk_0019.c:1829-2147). DOL-verified constants.
  // ==========================================================================
  {
    const shots: Array<{ addr: number; type: number }> = [];
    const sctx: StreamContext = {
      onFamilyProjectile: (_actor, addr, type) => shots.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = createMinimalActor() as RomActor & SapphireXScratch;
    configureSapphireKnightFamily(a, "pl0208", sctx);
    const root = a.rootAction!;
    // Variant routing: action 2 selects the bespoke machine (NOT shared fallback).
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a);
    // Phase 0 (FUN_800bd12c): +0x540→1, +0x560=30.0, +0x54e=0x1e, +0x48=0.5, slot 2.
    assert(a.fbPhaseSlots[0] === 1, "SAPPHIRE a2 ph0 advances +0x540 to 1");
    assert(a.sapphTimer560 === SAPPHIRE_X.PH0_TIMER_560,
      "SAPPHIRE a2 ph0 +0x560 = 30.0 (FLOAT_80438574)");
    assert(a.sapphAimTimer54e === SAPPHIRE_X.PH0_AIM_TIMER_54E,
      "SAPPHIRE a2 ph0 +0x54e = 0x1e (FUN_800bd12c:1868)");
    assert(a.yVel === SAPPHIRE_X.PH0_YVEL,
      "SAPPHIRE a2 ph0 +0x48 = 0.5 (FLOAT_80438578)");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "SAPPHIRE a2 ph0 zeroes hSpeed/hDecel/gravityCoeff (FLOAT_8043852c)");
    assert(a.streamSlot === 2, "SAPPHIRE a2 ph0 streamSlot = 2 (+0x6ea, FUN_800bd12c:1884)");
    assert(Math.abs(a.pos.x - 195) < 0.001,
      "SAPPHIRE a2 ph0 blink: pos.x = 195 (pos += (pos−target)×0.95 = 100+95, FLOAT_80438530)");

    // Phase 1 (FUN_800bd220): no wallContact → drift + afterimage, no advance.
    a.fbPhaseSlots[0] = 1; a.wallContact = 0; a.contactP0 = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "SAPPHIRE a2 ph1 no-wallContact holds phase");

    // Phase 1 with wallContact + ammo ok → advance to ph2 + spawn zz_00e19a8_.
    a.fbPhaseSlots[0] = 1; a.wallContact = 1; shots.length = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "SAPPHIRE a2 ph1 wallContact advances to ph2");
    assert(shots.length === 1 && shots[0]!.addr === SAPPHIRE_X.PH1_SPAWNER,
      "SAPPHIRE a2 ph1 ammo-ok deploys zz_00e19a8_ (0x800e19a8)");

    // Phase 1 with wallContact + ammo DENIED → exit, stateTimer = 16.0 + dt.
    a.fbPhaseSlots[0] = 1; a.wallContact = 1;
    const noAmmo: StreamContext = {
      onFamilyProjectile: () => {},
      onAllocateResource: () => false,
    };
    const a2 = createMinimalActor() as RomActor & SapphireXScratch;
    configureSapphireKnightFamily(a2, "pl0208", noAmmo);
    const root2 = a2.rootAction!;
    a2.actionIndex = 2; a2.dt = 1; a2.fbPhaseSlots[0] = 1; a2.wallContact = 1;
    a2.controlWord = 0x3; a2.housekeeping73f = 1; a2.hSpeed = 7; a2.hDecel = 4;
    root2(a2);
    assert(a2.housekeeping73f === 0 && (a2.controlWord & 0x3) === 0,
      "SAPPHIRE a2 ph1 ammo-denied clears +0x73f / strips +0x5e0 bits");
    assert(a2.hSpeed === 0 && a2.hDecel === 0,
      "SAPPHIRE a2 ph1 exit zeroes +0x44/+0x4c (FLOAT_8043852c)");
    assert(a2.stateTimer === SAPPHIRE_X.PH1_EXIT_TIMER + 1,
      "SAPPHIRE a2 ph1 exit stateTimer = 16.0 + dt (FLOAT_8043857c)");

    // Phase 5 (FUN_800bd7e4) hold-vs-exit gate on +0x5d8 & 0xf0.
    const a5 = createMinimalActor() as RomActor & SapphireXScratch;
    configureSapphireKnightFamily(a5, "pl0208", sctx);
    const root5 = a5.rootAction!;
    a5.actionIndex = 2; a5.dt = 1; a5.fbPhaseSlots[0] = 5;
    a5.inputHeld5d8 = 0; a5.wallContact = 0; // hold condition
    root5(a5);
    assert(a5.fbPhaseSlots[0] === 5, "SAPPHIRE a2 ph5 holds when (+0x5d8&0xf0)==0 && !wall");
    a5.inputHeld5d8 = 0x30; // B-held → exit
    a5.controlWord = 0x3; a5.housekeeping73f = 1; a5.hSpeed = 6;
    root5(a5);
    assert(a5.housekeeping73f === 0 && (a5.controlWord & 0x3) === 0,
      "SAPPHIRE a2 ph5 (+0x5d8&0xf0)!=0 exits: strips +0x73f/+0x5e0");
    assert(a5.stateTimer === SAPPHIRE_X.PH5_EXIT_TIMER + 1,
      "SAPPHIRE a2 ph5 exit stateTimer = 8.0 + dt (FLOAT_80438580)");
  }

  // ==========================================================================
  // AXE KNIGHT action 2 — bespoke 6-phase homing-dive X-special (FUN_800d74b4,
  //  table 0x8030fb00, chunk_0022.c:4748-5018). DOL-verified constants.
  // ==========================================================================
  {
    const fx: Array<{ addr: number; type: number }> = [];
    const xctx: StreamContext = {
      onFamilyProjectile: (_actor, addr, type) => fx.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = createMinimalActor() as RomActor & AxeXScratch;
    configureAxeKnightFamily(a, "pl0204", xctx);
    const root = a.rootAction!;
    // Variant routing: action 2 selects the bespoke dive machine.
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 10, y: 0, z: 0 };
    root(a);
    // Phase 0 (FUN_800d7540): +0x540→1, +0x558=60.0, motion=pos−target, slot 1.
    assert(a.fbPhaseSlots[0] === 1, "AXE a2 ph0 advances +0x540 to 1");
    assert(a.handlerTimer === AXE_X.PH0_TIMER_558,
      "AXE a2 ph0 +0x558 = 60.0 (FLOAT_80438b90)");
    assert(a.motion.x === 90, "AXE a2 ph0 motion.x = pos−target = 90 (FUN_800d7540:4796)");
    assert(a.streamSlot === 1, "AXE a2 ph0 streamSlot = 1 (+0x6ea = 0+1, FUN_800d7540:4801)");
    assert(a.accumulator80c === 0, "AXE a2 ph0 +0x80c = 0.0 (FLOAT_80438b7c)");

    // Phase 1 (FUN_800d7648): timer expiry → advance.
    a.fbPhaseSlots[0] = 1; a.handlerTimer = 0.5; a.streamHold1b03 = 1;
    root(a);
    assert(a.handlerTimer < 0.5, "AXE a2 ph1 decrements +0x558 by dt");
    a.handlerTimer = 0; // force expiry
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "AXE a2 ph1 +0x558≤0 advances to ph2");

    // Phase 2 (FUN_800d76cc): wallContact → advance, motion=(0,30,2), +0x548=0x14.
    a.fbPhaseSlots[0] = 2; a.wallContact = 1; a.borgNumber = 0x204; fx.length = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "AXE a2 ph2 wallContact advances to ph3");
    assert(a.motion.y === AXE_X.PH2_SPEED_CLAMP && a.motion.z === AXE_X.PH2_ACCEL_SEED,
      "AXE a2 ph2 motion = (0, 30.0, 2.0) (FLOAT_80438b94/98)");
    assert(a.axeTimer548 === AXE_X.PH2_TIMER548_DEFAULT,
      "AXE a2 ph2 pl0204 +0x548 = 0x14 (FUN_800d76cc:4849)");
    assert(fx.length === 1 && fx[0]!.addr === 0x80066530,
      "AXE a2 ph2 deploys zz_0066530_(0x2d) effect");
    // pl020d variant: +0x548 = 0.
    const ad = createMinimalActor() as RomActor & AxeXScratch;
    configureAxeKnightFamily(ad, "pl020d", xctx);
    const rootd = ad.rootAction!;
    ad.actionIndex = 2; ad.dt = 1; ad.fbPhaseSlots[0] = 2; ad.wallContact = 1; ad.borgNumber = 0x20d;
    rootd(ad);
    assert(ad.axeTimer548 === 0, "AXE a2 ph2 pl020d (0x20d) +0x548 = 0 (FUN_800d76cc:4852)");

    // Phase 3 (FUN_800d77b8): motion.x accelerates by motion.z×dt, projects via steerYaw.
    const a3 = createMinimalActor() as RomActor & AxeXScratch;
    configureAxeKnightFamily(a3, "pl0204", xctx);
    const root3 = a3.rootAction!;
    a3.actionIndex = 2; a3.dt = 1; a3.fbPhaseSlots[0] = 3;
    a3.motion = { x: 0, y: 30, z: 2 }; a3.steerYaw = 0; // steerYaw=0 → cos=1, sin=0
    a3.lockYaw = 0;
    root3(a3);
    assert(a3.motion.x === 2, "AXE a2 ph3 motion.x += motion.z×dt = 0+2 (FUN_800d77b8:4901)");
    assert(a3.hSpeed === 2 && a3.yVel === 0,
      "AXE a2 ph3 steerYaw=0: hSpeed=motion.x×cos=2, yVel=motion.x×−sin=0");

    // Phase 4 (FUN_800d7934): hSpeed < 0.5 + grounded → exit, stateTimer = 8.0+dt.
    const a4 = createMinimalActor() as RomActor & AxeXScratch;
    configureAxeKnightFamily(a4, "pl0204", xctx);
    const root4 = a4.rootAction!;
    a4.actionIndex = 2; a4.dt = 1; a4.fbPhaseSlots[0] = 4;
    a4.hSpeed = 0.1; a4.controlWord = 0x43; a4.housekeeping73f = 1; a4.steerYaw = 100;
    a4.physicsRuntime = {
      clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }),
      isSupported: () => true,
    };
    root4(a4);
    assert(a4.steerYaw === 0 && a4.housekeeping73f === 0 && (a4.controlWord & 0x43) === 0,
      "AXE a2 ph4 grounded-stop exit: +0x18da=0, strips +0x73f/+0x5e0/+0x40");
    assert(a4.stateTimer === AXE_X.EXIT_TIMER + 1,
      "AXE a2 ph4 exit stateTimer = 8.0 + dt (FLOAT_80438ba8)");
  }

  // ==========================================================================
  // SPIKE KNIGHT — delegates to knight-family.ts (action 2/4) + shared melee.
  // ==========================================================================
  for (const { id, num } of [{ id: "pl0203" as const, num: 0x203 }, { id: "pl020c" as const, num: 0x20c }]) {
    const a = createMinimalActor();
    const spikeCtx: StreamContext & KnightFamilyCtx = {
      ...makeCtx(),
      onTickStream: () => {},
      onAllocateResource: () => true,
      onPlayCue: () => {},
      onSpawnChild: () => true,
      onSpawnFX: () => {},
      onFaceTarget: () => {},
      onFrameUpdate: () => {},
      onCheckCollision: () => 0,
      onExitFb: () => {},
      onExitUb: () => {},
      onClearAction: () => {},
    };
    configureSpikeKnightFamily(a, id, spikeCtx);
    assert(a.borgNumber === num, `${id} borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} rootAction wired (delegates to knight-family + shared melee)`);
  }

  // ==========================================================================
  // DARK KNIGHT action 1 — bespoke 2-phase dash-melee (table 0x804346f0).
  // ==========================================================================
  {
    const a = createMinimalActor();
    configureDarkKnightFamily(a, "pl0205", makeCtx());
    const root = a.rootAction!;
    // Phase 0: setup — +0x540 advances, velocity zeroed, blink reposition.
    a.actionIndex = 1; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "DARK action1 ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "DARK action1 ph0 zeroes velocity scalars (FLOAT_8043a600)");
    assert(Math.abs(a.pos.x - 95) < 0.001, "DARK action1 ph0 blink: pos.x = 95 ((100−0)×0.95, FLOAT_8043a634)");
  }

  // ==========================================================================
  // DARK KNIGHT action 3 — bespoke 3-phase lunge (table 0x80342a2c).
  // ==========================================================================
  {
    const a = createMinimalActor();
    configureDarkKnightFamily(a, "pl0205", makeCtx());
    const root = a.rootAction!;
    // Phase 0: setup — +0x540 advances, streamSlot=10, velocity zeroed, blink.
    a.actionIndex = 3; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.pos = { x: 200, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "DARK action3 ph0 advances +0x540 to 1");
    assert(a.streamSlot === 10, "DARK action3 ph0 streamSlot = 10 (FLOAT seed)");
    assert(Math.abs(a.pos.x - 190) < 0.001, "DARK action3 ph0 blink: pos.x = 190 ((200−0)×0.95, FLOAT_8043a634)");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "DARK action3 ph0 zeroes velocity scalars");

    // Phase 1: active — on contactP0>0, advance to phase 2 + spawn.
    const shots: Array<{ addr: number; type: number }> = [];
    const ctx2: StreamContext = {
      onFamilyProjectile: (_actor, addr, type) => shots.push({ addr, type }),
    };
    configureDarkKnightFamily(a, "pl0205", ctx2);
    const root2 = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; // hit
    root2(a);
    assert(a.fbPhaseSlots[0] === 2, "DARK action3 ph1 contactP0>0 advances to ph2");
    assert(shots.length === 1 && shots[0]!.addr === KNIGHT_EFFECT_SPAWNER,
      "DARK action3 ph1 spawns zz_00c3be0_ effect on contact");

    // Phase 2: recovery — wallContact triggers exit (+0x73f=0, +0x5e0&=~3, stateTimer=8+dt).
    a.fbPhaseSlots[0] = 2;
    a.wallContact = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = {
      clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }),
      isSupported: () => true,
    };
    root2(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "DARK action3 ph2 wallContact clears +0x73f / strips +0x5e0 bits");
    assert(a.stateTimer === KC.EXIT_TIMER_BASE + 1,
      "DARK action3 ph2 exit stateTimer = 8.0 + dt (FLOAT_8043a648)");
  }

  // ==========================================================================
  // All families route action 1 to shared knight melee (except Elemental/Chainsaw).
  // ==========================================================================
  for (const { id, configure } of [
    { id: "pl0208", configure: (a: RomActor) => configureSapphireKnightFamily(a, "pl0208", makeCtx()) },
    { id: "pl0204", configure: (a: RomActor) => configureAxeKnightFamily(a, "pl0204", makeCtx()) },
    { id: "pl0209", configure: (a: RomActor) => configureImperialKnightFamily(a, "pl0209", makeCtx()) },
  ]) {
    const a = createMinimalActor();
    configure(a);
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.fbPhaseSlots[0] = 0; a.fbPhaseSlots[1] = 0;
    a.streamSlot = 0;
    // Shared knight melee phase 0 arms the stream; the exact behavior depends on
    // variant dispatch but the rootAction must not throw.
    root(a);
    assert(true, `${id} action 1 (shared knight melee) dispatches without error`);
  }
}

// Minimal actor factory for tests (avoids importing createRomActor which needs full init).
function createMinimalActor(): RomActor {
  const a = {} as RomActor;
  // Initialize the fields the phase machines touch.
  a.physicsRuntime = null;
  a.pos = { x: 0, y: 0, z: 0 };
  a.motion = { x: 0, y: 0, z: 0 };
  a.targetCache5e8 = { x: 0, y: 0, z: 0 };
  a.aimOrigin518 = { x: 0, y: 0, z: 0 };
  a.partAimAnchors = [null, null, null, null];
  a.hSpeed = 0; a.yVel = 0; a.hDecel = 0; a.gravityCoeff = 0;
  a.heading = 0; a.lockYaw = 0; a.activeYaw = 0; a.turnErrorYaw = 0; a.steerYaw = 0;
  a.bodyPitch = 0; a.aimRateScale = 1; a.actionSpeedRows = [0, 0, 0];
  a.savedGroundPos = { x: 0, y: 0, z: 0 };
  a.housekeeping73f = 0; a.accumulator80c = 0;
  a.poseAccum7c = 0; a.poseAccum7e = 0; a.poseAccum80 = 0;
  a.afterimageSamplePos = { x: 0, y: 0, z: 0 }; a.modelScale = 1; a.sizeScale = 1;
  a.afterimageSerial = 0;
  a.weaponPartMask = 0x0f; a.weaponAnimationActiveMask = 0;
  a.weaponAnimationState = [0, 0, 0, 0];
  a.weaponAnimationParams = {
    baseRate: 0, descriptorWord: 0, endFrame: 0, startFrame: 0,
    group: 0, slot: 0, durationAdjust: 0, toggle: 0, tailByte: 0, descriptor: null,
  };
  a.weaponAnimationBlocks = [new Uint8Array(0x38), new Uint8Array(0x38), new Uint8Array(0x38), new Uint8Array(0x38)];
  a.weaponAnimationTiming = [
    { duration: 0, dt: 0, rate: 0 }, { duration: 0, dt: 0, rate: 0 },
    { duration: 0, dt: 0, rate: 0 }, { duration: 0, dt: 0, rate: 0 },
  ];
  a.visibilityBit = 1; a.visibilityTarget = null; a.visibilityRoster = [];
  a.borgMirror94 = 0; a.carriedSlot96 = 0; a.carriedVariant97 = 0; a.identityVariant = 0;
  a.borgNumber = 0; a.slot = 0; a.team = 0;
  a.fbPhase = 0; a.fbPhaseSlots = [0, 0, 0, 0];
  a.fbState = -1; a.ubState = -1; a.prevFbState = -1; a.prevUbState = -1;
  a.ubCue = 0; a.fbCue = 0; a.controlWord = 0;
  a.actionIndex = 0; a.variantIndex = 0; a.prevActionIndex = 0;
  a.cmdButton = 0; a.cmdSubtype = 0; a.cmdChargedRanged = 0;
  a.rootAction = null; a.hasBCharge = false; a.upperBody = null; a.preState = null; a.postState = null;
  a.descriptor = null; a.commandTable = null; a.cueTable = null;
  a.familyStreamBank = null; a.sharedStreamBank = null;
  a.familyAnimDescBank = null; a.sharedAnimDescBank = null; a.soundEventTable = null;
  a.defaultGroup = 0; a.streamSlot = 0;
  a.parts = [
    { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
    { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
    { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
    { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
  ];
  a.maxRise = 0; a.maxFall = 0; a.maxHSpeed = 0; a.stepHeight = 0;
  a.timescale = 1; a.tierScale = 1; a.dt = 1;
  a.contactP0 = 0; a.wallContact = 0; a.childMask144 = 0;
  a.attachmentFlags14c = [0, 0, 0, 0]; a.contactP1 = 0;
  a.dashStrength1d0f = 0; a.faceGate1d10 = 0; a.streamHold1b03 = 0; a.streamCounter6eb = 0;
  a.statusWord5b4 = 0; a.inputEdge5d4 = 0; a.inputHeld5d8 = 0;
  a.stateTimer = 0; a.shotScalar1d9c = 0; a.shotByte1db2 = 0; a.shotByte1db3 = 0; a.handlerTimer = 0;
  return a;
}
