// VICTORY KING cluster (ctor 0x8015a494) victory-king family — bespoke action-0 dash +
// action-3 B-charge port. 4 borgs share one root dispatcher:
//   pl0610 VICTORY KING   (0x610)
//   pl061e PROTO KING     (0x61e)
//   pl0621 VICTORY DUKE   (0x621)
//   pl0623 VICTORY BARON  (0x623)
//
// The ctor wires root dispatcher FUN_8015a848 (chunk_0040.c:3904), which indexes
// PTR_FUN_803447f4[+0x580 actionIndex]. Only action 0 (dash) and action 3 (B-charge)
// route to bespoke phase machines here; action 2 (X-special) routes through the shared
// engine zz_017a374_ (FUN_8015ad10 → zz_015ad5c_/zz_015ad84_/zz_015adac_), preserved
// via the shared-engine approximation so existing behavior does not regress. pl061e has
// no action-2 arm (FUN_8015ad10 falls through for 0x61e).
//
//   action 0 table @0x804346f8 = [FUN_8015a8f8(75i), FUN_8015aa24(133i)] — 2 phases.
//   action 3 table @0x803448b0 = [FUN_8015ae58(70i), FUN_8015af70(81i),
//                                  FUN_8015b0b4(142i), FUN_8015b2ec(77i)] — 4 phases.
//
// Source: research/decomp/ghidra-export/chunk_0040.c:3935-4054 (action 0),
//         :4179-4374 (action 3).
//
// ACTION 0 (dash):
//   ph0 setup  (FUN_8015a8f8) — advance +0x540; reset +0x541/+0x6ea (airborne → +0x6ea=1);
//     if no target (+0xcc==0) activeYaw=heading; aim yaw zz_006d144_(0xc1) (+ part pitch
//     zz_006e1ac_(0xc1,1) when airborne); zero the four velocity scalars + pose accum;
//     airborne overrides +0x48 (yVel) = 4.0; blink toward +0x5e8 (motion = pos−target,
//     ×0.95, pos += motion); zz_00679d0_ ground-snap; +0x6ea++; start stream group 2.
//   ph1 active (FUN_8015aa24) — tick stream; on contactP0<0 decay steerYaw ×0.9; on
//     contactP0>0 clear it + ammo gate zz_006dbe0_(0,1,1): denied → gravityCoeff =
//     descriptor.handlerData6c, +0x694 = 30.0+dt, goto exit; ok → borg-switched
//     zz_00c3be0_ spawn (0x610→0x35, 0x61e→0x55, 0x621→0x56, 0x623→0x57). faceGate aim;
//     dashStrength<0 → clear + gravityCoeff restore; motion ×0.95 + pos; physics
//     FUN_80067310(1.0, lockYaw); ground-snap; if no wallContact return; else exit
//     (+0x73f=0, +0x5e0&=~3, hSpeed/hDecel=0; air return zz_006a5a4_ if !grounded||airborne
//     else land return zz_006a474_).
//
// ACTION 3 (B-charge sword flurry):
//   ph0 setup  (FUN_8015ae58) — advance; activeYaw=heading if no target; +0x558=600.0,
//     +0x560=60.0, +0x6ea=0 (airborne→2); aim yaw 0xc0 + part pitch 0xc0; zero scalars +
//     pose; blink; ground-snap; +0x6ea++; start stream group 3.
//   ph1 windup (FUN_8015af70) — ground: steerYaw ×0.9; tick stream (only if +0x1b03);
//     slow-damp motion (×0.5 if +0x760<200); motion ×0.95 + pos; ground-snap; airborne
//     part-pitch aim; drain +0x560 by dt; advance when +0x560<=0 OR yaw converges; on
//     advance seed +0x6eb=4, +0x6ec=0, +0x54c=0, +0x54e=0x14.
//   ph2 flurry (FUN_8015b0b4) — zz_00f0104_(0x17,2) per-frame FX (TODO unsurfaced); while
//     +0x558>0 drain it + charge-hold bump (+0x5b4 & 0x200 [0x400 for 0x61e]) forces
//     +0x54c=2 (the release latch that sustains the flurry while B is held); ground steerYaw
//     decay; tick stream; faceGate aim; slow-damp + motion; ground-snap; on wallContact:
//     +0x6eb-- (wrap to 4 + toggle +0x6ec + borg-switched zz_0082824_ spawn: 0x610→0x36/0x37,
//     0x621→0x53/0x54, 0x623→0x55/0x56; 0x61e skips) AND +0x54c-- (advance to ph3 when <1,
//     re-arming stream group 3).
//   ph3 recover (FUN_8015b2ec) — tick stream; contactP0<0 steerYaw decay; dashStrength<0
//     gravityCoeff restore; physics(1.0, lockYaw); motion ×0.95 + pos; ground-snap; on
//     wallContact: +0x73f=0, +0x5e0&=~3; !grounded→zz_006a5a4_, grounded&&!airborne→
//     zz_006a474_, grounded&&airborne→zz_006a750_(7); +0x694 = 4.0+dt.
//
// Float constants (read from boot.dol this session via v2f, rtoc=0x8043ea20, sdata2
// @0x8043a7xx):
//   FLOAT_8043a720 = 0.0    zero-scalar (velocity/pose resets, thresholds)
//   FLOAT_8043a724 = 4.0    ph0 air-dash yVel seed; ph3 exit +0x694 seed base
//   FLOAT_8043a728 = 0.95   blink + per-frame motion scale
//   FLOAT_8043a72c = -1.0   zz_004beb8_ stream rate
//   FLOAT_8043a730 = 0.9    steerYaw decay factor (CONCAT44 double-coercion idiom)
//   FLOAT_8043a734 = 30.0   ph1 ammo-denied +0x694 seed
//   FLOAT_8043a738 = 1.0    FUN_80067310 gravity arg
//   FLOAT_8043a740 = double-coercion sentinel (2^52 high word 0x43300000; the steerYaw
//                    ×0.9 idiom — DOUBLE_8043a740 is the GCC int→double magic, value 0)
//   FLOAT_8043a748 = 600.0  action-3 ph0 +0x558 seed (flurry window)
//   FLOAT_8043a74c = 60.0   action-3 ph0 +0x560 seed (windup timer)
//   FLOAT_8043a750 = 200.0  +0x760 slow-damp threshold
//   FLOAT_8043a754 = 0.5    +0x760 slow-damp extra motion scale
//
// Exit helpers zz_006a474_ / zz_006a5a4_ / zz_006a750_ are ported in shared-idle-return.ts
// (romGroundIdleReturn / romAirKnockoutReturn) + dispatch.ts (dispatchUpperBodyCue).

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, groundSnapRevert, stepTargetYaw, stepPartTargetPitch } from "../rom/helpers.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";

/** Borg numbers for the VICTORY KING cluster. */
const VICTORY_KING_BORG_NUMBERS: Record<string, number> = {
  pl0610: 0x610,
  pl061e: 0x61e,
  pl0621: 0x621,
  pl0623: 0x623,
};

export type VictoryKingBorgId = "pl0610" | "pl061e" | "pl0621" | "pl0623";

// ----------------------------------------------------------------------------
// Spawner addresses.
// ----------------------------------------------------------------------------
/** zz_00c3be0_ — per-borg effect spawn (action-0 ph1 contact effect). */
const EFFECT_SPAWNER = 0x800c3be0;
/** zz_0082824_ — record-table projectile spawn (action-3 ph2 flurry shot). */
const SHOT_HELPER = 0x80082824;

// ----------------------------------------------------------------------------
// Config constants (DOL-read this session; sdata2 @0x8043a7xx).
// ----------------------------------------------------------------------------
const VK = {
  /** FLOAT_8043a720 = 0.0 — zero-scalar + threshold. */
  ZERO: 0.0,
  /** FLOAT_8043a724 = 4.0 — ph0 air-dash yVel seed; ph3 +0x694 seed base. */
  AIR_YVEL: 4.0,
  /** FLOAT_8043a728 = 0.95 — blink + per-frame motion scale. */
  MOTION_SCALE: 0.95,
  /** FLOAT_8043a72c = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a730 = 0.9 — steerYaw decay factor. */
  STEER_DECAY: 0.9,
  /** FLOAT_8043a734 = 30.0 — ph1 ammo-denied +0x694 seed. */
  DENIED_STATE_TIMER: 30.0,
  /** FLOAT_8043a738 = 1.0 — FUN_80067310 gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_8043a748 = 600.0 — action-3 ph0 +0x558 seed (flurry window). */
  FLURRY_WINDOW: 600.0,
  /** FLOAT_8043a74c = 60.0 — action-3 ph0 +0x560 seed (windup timer). */
  WINDUP_TIMER: 60.0,
  /** FLOAT_8043a750 = 200.0 — +0x760 slow-damp threshold. */
  SLOW_THRESHOLD: 200.0,
  /** FLOAT_8043a754 = 0.5 — +0x760 slow-damp extra motion scale. */
  SLOW_SCALE: 0.5,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 position-frozen / airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** action-3 ph2 stream-slot / flurry countdown seed. */
  FLURRY_SLOT_SEED: 4,
  /** action-3 ph1 +0x54e seed (0x14). Read by the stream tick; stored faithfully. */
  FLURRY_MAX_54E: 0x14,
  /** action-3 ph2 charge-hold release-latch floor (force +0x54c up to this while held). */
  FLURRY_LATCH_FLOOR: 2,
  /** action-3 ph1 charge status bit (non-0x61e). +0x5b4 & this. */
  CHARGE_BIT: 0x200,
  /** action-3 ph1 charge status bit (PROTO KING 0x61e only). */
  CHARGE_BIT_61E: 0x400,
  /** action-0 stream group. */
  ACTION0_STREAM_GROUP: 2,
  /** action-3 stream group. */
  ACTION3_STREAM_GROUP: 3,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface VictoryKingScratch {
  /** +0x560: action-3 windup/flurry sub-timer (ph0 seeds 60.0; ph1 drains). */
  vkTimer560?: number;
  /** +0x760: movement speed scalar; < 200 triggers the slow-damp motion scale. */
  vkSpeedScalar760?: number;
  /** +0x54c: action-3 ph2 flurry release latch (charge-hold bumps to 2). */
  vkHitCount54c?: number;
  /** +0x54e: action-3 ph1 seed (0x14); consumed by the stream tick. */
  vkFlurryMax54e?: number;
  /** +0x6ec: action-3 ph2 alternating flurry-shot toggle (XOR 1 each wrap). */
  vkFlurryToggle6ec?: number;
}

type VkActor = RomActor & VictoryKingScratch;

function scratchOf(actor: RomActor): VkActor {
  return actor as VkActor;
}

/** Airborne = +0x5e0 position-frozen bit set. */
function isAirborne(actor: RomActor): boolean {
  return (actor.controlWord & VK.AIRBORNE_BIT) !== 0;
}

/** +0xcc == 0 (no lock target) gates the activeYaw = heading copy. Modelled via the
 *  helpers' lockTarget scratch (null/undefined ⇒ no target). */
function hasLockTarget(actor: RomActor): boolean {
  const t = (actor as RomActor & { lockTarget?: unknown }).lockTarget;
  return t != null;
}

// ----------------------------------------------------------------------------
// Borg-switched spawn type selectors.
// ----------------------------------------------------------------------------

/** action-0 ph1 contact effect (zz_00c3be0_). Returns null for unknown borgs. */
function action0EffectType(borgNumber: number): number | null {
  switch (borgNumber) {
    case 0x610: return 0x35;
    case 0x61e: return 0x55;
    case 0x621: return 0x56;
    case 0x623: return 0x57;
    default: return null;
  }
}

/** action-3 ph2 flurry shot (zz_0082824_). PROTO KING (0x61e) has no flurry arm. */
function action3FlurryType(borgNumber: number, toggle: number): number | null {
  switch (borgNumber) {
    case 0x610: return toggle + 0x36; // 0x36 / 0x37
    case 0x621: return toggle + 0x53; // 0x53 / 0x54
    case 0x623: return toggle + 0x55; // 0x55 / 0x56
    default: return null; // 0x61e skips
  }
}

// ----------------------------------------------------------------------------
// Shared blink: motion = pos − targetCache; motion ×= 0.95; pos += motion.
// ----------------------------------------------------------------------------
function applyBlink(actor: RomActor): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(VK.MOTION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Per-frame motion continuation: motion ×= 0.95; pos += motion (no re-subtract). */
function applyMotionDrift(actor: RomActor): void {
  vecScale(VK.MOTION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** steerYaw ×= 0.9 (the GCC CONCAT44 double-coercion idiom; FLOAT_8043a730). */
function decaySteerYaw(actor: RomActor): void {
  const v = Math.trunc(actor.steerYaw * VK.STEER_DECAY);
  actor.steerYaw = (v & 0xffff) >= 0x8000 ? v - 0x10000 : v;
}

// ============================================================================
// ACTION 0 — dash (table @0x804346f8).
// ============================================================================

/** Phase 0 — setup. FUN_8015a8f8 @ chunk_0040.c:3935 (75 instrs). */
function action0Phase0Setup(actor: VkActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fbPhaseSlots[1] = 0;                                 // +0x541 = 0
  actor.streamSlot = 0;                                       // +0x6ea = 0
  if (isAirborne(actor)) actor.streamSlot = 1;                // +0x6ea = 1 (airborne)
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading; // +0xcc==0 → +0x5ac = +0x72
  // zz_006d144_(actor, 0xc1) — aim yaw.
  stepTargetYaw(actor, 0xc1);
  if (isAirborne(actor)) {
    // zz_006e1ac_(actor, 0xc1, 1) — part pitch aim.
    stepPartTargetPitch(actor, 0xc1);
  }
  // Zero the four velocity scalars + pose accum (FLOAT_8043a720 = 0.0).
  actor.gravityCoeff = VK.ZERO;
  actor.yVel = VK.ZERO;
  actor.hDecel = VK.ZERO;
  actor.hSpeed = VK.ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  if (isAirborne(actor)) {
    actor.yVel = VK.AIR_YVEL; // +0x48 = FLOAT_8043a724 (4.0)
  }
  // Blink toward +0x5e8 targetCache (95% approach) + ground snap.
  applyBlink(actor);
  groundSnapRevert(actor); // zz_00679d0_
  // Arm stream group 2 at the captured slot, then +0x6ea++.
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, VK.STREAM_MASK, VK.ACTION0_STREAM_GROUP, slot, VK.STREAM_RATE);
}

/** Phase 1 — active dash. FUN_8015aa24 @ chunk_0040.c:3982 (133 instrs). */
function action0Phase1Active(actor: VkActor, ctx: StreamContext): void {
  // zz_004cd24_(actor, 0xf) — tick all 4 parts' action stream.
  tickStream(actor, VK.STREAM_MASK, ctx);
  // contactP0 < 0 (blocked) → decay steerYaw.
  if (actor.contactP0 < 0) decaySteerYaw(actor);
  let exitNow = false;
  let grounded = false;
  if (actor.contactP0 > 0) {
    // Hit: clear contact, ammo-gate a borg-switched zz_00c3be0_ spawn.
    actor.contactP0 = 0;
    const ammoOk = allocateWeapon(actor, ctx, 0, 1, true); // zz_006dbe0_(actor,0,1,1)
    if (!ammoOk) {
      // Denied: restore gravityCoeff from descriptor.handlerData6c; +0x694 = 30.0+dt; exit.
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
      actor.stateTimer = VK.DENIED_STATE_TIMER + actor.dt;
      grounded = groundSnapRevert(actor); // the goto-LAB path; probe current support
      exitNow = true;
    } else {
      const type = action0EffectType(actor.borgNumber);
      if (type !== null) ctx.onFamilyProjectile?.(actor, EFFECT_SPAWNER, type);
    }
  }
  if (exitNow) {
    action0Exit(actor, grounded);
    return;
  }
  // faceGate (+0x1d10) != 0 → re-aim (yaw + airborne part pitch).
  if (actor.faceGate1d10 !== 0) {
    stepTargetYaw(actor, 0xc1);
    if (isAirborne(actor)) stepPartTargetPitch(actor, 0xc1);
  }
  // dashStrength (+0x1d0f) < 0 → clear + restore gravityCoeff.
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  }
  // motion ×= 0.95; pos += motion.
  applyMotionDrift(actor);
  // FUN_80067310(1.0, actor, lockYaw) — physics integration.
  integratePhysics(VK.PHYSICS_GRAVITY, actor, actor.lockYaw);
  grounded = groundSnapRevert(actor); // zz_00679d0_ → unaff_r30
  if (actor.wallContact === 0) return; // keep dashing
  // wallContact → exit (LAB_8015abd8).
  action0Exit(actor, grounded);
}

/** LAB_8015abd8 exit tail: +0x73f=0; +0x5e0&=~3; hSpeed/hDecel=0; air/land return. */
function action0Exit(actor: VkActor, grounded: boolean): void {
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~VK.ACTION_MODE_BITS;
  actor.hDecel = VK.ZERO; // +0x4c = FLOAT_8043a720
  actor.hSpeed = VK.ZERO; // +0x44 = FLOAT_8043a720
  if (!grounded || isAirborne(actor)) {
    romAirKnockoutReturn(actor); // zz_006a5a4_
  } else {
    romGroundIdleReturn(actor);  // zz_006a474_
  }
}

// ============================================================================
// ACTION 3 — B-charge sword flurry (table @0x803448b0).
// ============================================================================

/** Phase 0 — setup. FUN_8015ae58 @ chunk_0040.c:4179 (70 instrs). */
function action3Phase0Setup(actor: VkActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading;
  actor.handlerTimer = VK.FLURRY_WINDOW; // +0x558 = 600.0
  actor.vkTimer560 = VK.WINDUP_TIMER;    // +0x560 = 60.0
  actor.streamSlot = 0;                   // +0x6ea = 0
  if (isAirborne(actor)) actor.streamSlot = 2; // +0x6ea = 2 (airborne)
  stepTargetYaw(actor, 0xc0);             // zz_006d144_(0xc0)
  stepPartTargetPitch(actor, 0xc0);       // zz_006e1ac_(0xc0, 1)
  actor.gravityCoeff = VK.ZERO;
  actor.yVel = VK.ZERO;
  actor.hDecel = VK.ZERO;
  actor.hSpeed = VK.ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  applyBlink(actor);
  groundSnapRevert(actor);
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, VK.STREAM_MASK, VK.ACTION3_STREAM_GROUP, slot, VK.STREAM_RATE);
}

/** Phase 1 — windup. FUN_8015af70 @ chunk_0040.c:4223 (81 instrs). */
function action3Phase1Windup(actor: VkActor, ctx: StreamContext): void {
  if (!isAirborne(actor)) decaySteerYaw(actor);
  if (actor.streamHold1b03 !== 0) {
    tickStream(actor, VK.STREAM_MASK, ctx); // zz_004cd24_(0xf) (gated by +0x1b03)
  }
  if ((actor.vkSpeedScalar760 ?? 0) < VK.SLOW_THRESHOLD) {
    vecScale(VK.SLOW_SCALE, actor.motion, actor.motion); // motion ×= 0.5
  }
  applyMotionDrift(actor);
  groundSnapRevert(actor);
  if (isAirborne(actor)) stepPartTargetPitch(actor, 0xc0);
  // Drain +0x560 by dt.
  const t = (actor.vkTimer560 ?? 0) - actor.dt;
  actor.vkTimer560 = t;
  // Advance when +0x560 <= 0.0 OR zz_006d144_(0xc0) returns nonzero (yaw converged).
  if (t <= VK.ZERO) {
    action3AdvanceToFlurry(actor);
    return;
  }
  const converged = stepTargetYaw(actor, 0xc0);
  if (converged) action3AdvanceToFlurry(actor);
}

/** Seed the ph2 flurry cursors and advance +0x540 (chunk_0040.c:4254-4258). */
function action3AdvanceToFlurry(actor: VkActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.streamCounter6eb = VK.FLURRY_SLOT_SEED; // +0x6eb = 4
  actor.vkFlurryToggle6ec = 0;                   // +0x6ec = 0
  actor.vkHitCount54c = 0;                       // +0x54c = 0
  actor.vkFlurryMax54e = VK.FLURRY_MAX_54E;      // +0x54e = 0x14
}

/** Phase 2 — flurry. FUN_8015b0b4 @ chunk_0040.c:4265 (142 instrs). */
function action3Phase2Flurry(actor: VkActor, ctx: StreamContext): void {
  // zz_00f0104_(actor, 0x17, 2) — per-frame FX/sound (host hook).
  // TODO(rom): zz_00f0104_ unsurfaced; no port-side effect (cited @chunk_0040.c:4275).
  if (VK.ZERO < actor.handlerTimer) {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
    const chargeBit = actor.borgNumber === 0x61e ? VK.CHARGE_BIT_61E : VK.CHARGE_BIT;
    if (((actor.statusWord5b4 ?? 0) & chargeBit) !== 0 && (actor.vkHitCount54c ?? 0) < VK.FLURRY_LATCH_FLOOR) {
      actor.vkHitCount54c = VK.FLURRY_LATCH_FLOOR; // +0x54c = 2 (release latch while B held)
    }
  }
  if (!isAirborne(actor)) decaySteerYaw(actor);
  tickStream(actor, VK.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  if (actor.faceGate1d10 > 0) {
    stepTargetYaw(actor, 0xc0);
    if (isAirborne(actor)) stepPartTargetPitch(actor, 0xc0);
  }
  if ((actor.vkSpeedScalar760 ?? 0) < VK.SLOW_THRESHOLD) {
    vecScale(VK.SLOW_SCALE, actor.motion, actor.motion);
  }
  applyMotionDrift(actor);
  groundSnapRevert(actor);
  if (actor.wallContact === 0) return; // no active hit this frame
  // Flurry shot cadence: +0x6eb-- ; wrap to 4 + toggle +0x6ec + spawn.
  const slot = (actor.streamCounter6eb ?? 0) - 1;
  actor.streamCounter6eb = slot;
  if (slot < 1) {
    actor.streamCounter6eb = VK.FLURRY_SLOT_SEED; // +0x6eb = 4
    const toggle = (actor.vkFlurryToggle6ec ?? 0) ^ 1;
    actor.vkFlurryToggle6ec = toggle; // +0x6ec ^= 1
    const type = action3FlurryType(actor.borgNumber, toggle);
    if (type !== null) ctx.onFamilyProjectile?.(actor, SHOT_HELPER, type);
  }
  // Release latch: +0x54c-- ; advance to ph3 when < 1.
  const hits = (actor.vkHitCount54c ?? 0) - 1;
  actor.vkHitCount54c = hits;
  if (hits < 1) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // → ph3
    const s = actor.streamSlot;
    actor.streamSlot = s + 1;
    startStream(actor, VK.STREAM_MASK, VK.ACTION3_STREAM_GROUP, s, VK.STREAM_RATE);
  }
}

/** Phase 3 — recover. FUN_8015b2ec @ chunk_0040.c:4337 (77 instrs). */
function action3Phase3Recover(actor: VkActor, ctx: StreamContext): void {
  tickStream(actor, VK.STREAM_MASK, ctx);
  if (actor.contactP0 < 0) decaySteerYaw(actor);
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  }
  integratePhysics(VK.PHYSICS_GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, lockYaw)
  applyMotionDrift(actor);
  const grounded = groundSnapRevert(actor);
  if (actor.wallContact === 0) return;
  // Exit: +0x73f=0; +0x5e0&=~3; then a 3-way selector.
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~VK.ACTION_MODE_BITS;
  if (!grounded) {
    romAirKnockoutReturn(actor); // zz_006a5a4_
  } else if (!isAirborne(actor)) {
    romGroundIdleReturn(actor);  // zz_006a474_
  } else {
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(actor, 7)
  }
  actor.stateTimer = VK.AIR_YVEL + actor.dt; // +0x694 = 4.0 + dt
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_8015a848 indexes PTR_FUN_803447f4[+0x580]. action 0 and
// action 3 route to the bespoke phase machines; action 2 (X) routes through the shared
// engine (zz_017a374_ approximation, preserved); other actions fall through (no-op).
// ----------------------------------------------------------------------------
export function createVictoryKingRootAction(
  ctx: StreamContext,
  borgId: VictoryKingBorgId,
): (actor: RomActor) => void {
  // action 2 (X-special) — pl061e has no X arm; others keep the shared-engine rush.
  const xSeedSlot = borgId === "pl0610" ? 0
    : borgId === "pl061e" ? null
    : borgId === "pl0621" ? 0
    : 1; // pl0623
  const xHandler = xSeedSlot === null
    ? null
    : createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(xSeedSlot) });

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) action0Phase0Setup(actor);
        else action0Phase1Active(actor, ctx);
        return;
      }
      case 2:
        // FUN_8015ad10 → zz_017a374_ shared engine (preserved approximation).
        xHandler?.(base);
        return;
      case 3: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        switch (phase) {
          case 0: action3Phase0Setup(actor); return;
          case 1: action3Phase1Windup(actor, ctx); return;
          case 2: action3Phase2Flurry(actor, ctx); return;
          case 3: action3Phase3Recover(actor, ctx); return;
          default: return;
        }
      }
      default: return;
    }
  };
}

/** Configure a freshly-spawned VICTORY KING cluster member. Stamps the per-borg number
 *  (so the borg-switched spawns select the correct record) and wires the bespoke
 *  action-0 dash + action-3 B-charge machines, preserving the action-2 X-special. */
export function configureVictoryKingFamily(
  actor: RomActor,
  borgId: VictoryKingBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = VICTORY_KING_BORG_NUMBERS[borgId] ?? 0x610;
  actor.rootAction = createVictoryKingRootAction(ctx, borgId);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const VICTORY_KING_CONSTANTS = VK;
export const VICTORY_KING_EFFECT_SPAWNER = EFFECT_SPAWNER;
export const VICTORY_KING_SHOT_HELPER = SHOT_HELPER;

// ============================================================================
// Self-tests. Mirror the rom.selfcheck.ts / death-borg-chi style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function makeCtx(opts: {
  onAllocateResource?: () => boolean;
  onFamilyProjectile?: (addr: number, type: number) => void;
} = {}): StreamContext {
  const ctx: StreamContext = {};
  if (opts.onAllocateResource) {
    ctx.onAllocateResource = () => opts.onAllocateResource!();
  }
  if (opts.onFamilyProjectile) {
    const sink = opts.onFamilyProjectile;
    ctx.onFamilyProjectile = (_a, addr, type) => sink(addr, type);
  }
  return ctx;
}

export function runVictoryKingSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // ==========================================================================
  // ACTION 0 — dash.
  // ==========================================================================

  // --- ph0 setup: each borg stamps its borgNumber + advances + zeroes scalars. ---
  for (const { id, num } of [
    { id: "pl0610" as const, num: 0x610 },
    { id: "pl061e" as const, num: 0x61e },
    { id: "pl0621" as const, num: 0x621 },
    { id: "pl0623" as const, num: 0x623 },
  ]) {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, id, makeCtx());
    assert(a.borgNumber === num, `${id} borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} bespoke rootAction wired`);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, `${id} action0 ph0 advances to ph1`);
    assert(
      a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      `${id} action0 ph0 zeroes hSpeed/hDecel/gravityCoeff (FLOAT_8043a720)`,
    );
    assert(a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      `${id} action0 ph0 clears pose accumulators`);
  }

  // --- ph0 airborne: yVel overridden to 4.0 (FLOAT_8043a724); stream slot starts 1. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.controlWord = VK.AIRBORNE_BIT; // airborne
    root(a); // ph0
    assert(a.yVel === VK.AIR_YVEL, "action0 ph0 airborne yVel = 4.0 (FLOAT_8043a724)");
    assert(a.streamSlot === 2, "action0 ph0 airborne streamSlot = 2 (seed 1 + advance)");
  }

  // --- ph0 ground blink: motion = (pos−target)×0.95 added to pos. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.pos.x === 195, "action0 ph0 blink: pos.x = 195 ((100−0)×0.95 added)");
    assert(a.motion.x === 95, "action0 ph0 motion.x = 95 (×FLOAT_8043a728)");
  }

  // --- ph1 contact > 0 + ammo ok: borg-switched zz_00c3be0_ spawn per borg. ---
  {
    const cases: Array<{ id: VictoryKingBorgId; num: number; type: number }> = [
      { id: "pl0610", num: 0x610, type: 0x35 },
      { id: "pl061e", num: 0x61e, type: 0x55 },
      { id: "pl0621", num: 0x621, type: 0x56 },
      { id: "pl0623", num: 0x623, type: 0x57 },
    ];
    for (const { id, num, type } of cases) {
      const shots: Shot[] = [];
      const a = createRomActor() as VkActor;
      configureVictoryKingFamily(a, id, makeCtx({
        onAllocateResource: () => true,
        onFamilyProjectile: (addr, t) => shots.push({ addr, type: t }),
      }));
      const root = a.rootAction!;
      a.actionIndex = 0; a.dt = 1;
      a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
      a.fbPhaseSlots[0] = 1; // jump to ph1
      a.contactP0 = 1;       // hit
      root(a);
      assert(
        shots.length === 1 && shots[0]!.addr === EFFECT_SPAWNER && shots[0]!.type === type,
        `${id} action0 ph1 contact spawns zz_00c3be0_(${type}) (got ${JSON.stringify(shots)})`,
      );
      assert(a.contactP0 === 0, `${id} action0 ph1 clears contactP0 after spawn`);
      void num;
    }
  }

  // --- ph1 contact > 0 + ammo DENIED: gravityCoeff restore + exit (+0x694=30+dt). ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx({ onAllocateResource: () => false }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.descriptor = {
      header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(0),
      handlerData6c: 1.5, subtypePartCommand: new Int8Array(0),
      buttonLiveFlag: new Int8Array(0), defaultHand0: 0, defaultHand1: 0,
    };
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a); // ph1 denied → exit
    assert(a.gravityCoeff === 1.5, "action0 ph1 denied restores gravityCoeff from descriptor.handlerData6c");
    assert(a.stateTimer === VK.DENIED_STATE_TIMER + 1, "action0 ph1 denied +0x694 = 30.0 + dt (FLOAT_8043a734)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph1 denied clears +0x73f and strips +0x5e0 action bits");
    assert(a.hSpeed === 0 && a.hDecel === 0, "action0 ph1 exit zeroes hSpeed/hDecel");
  }

  // --- ph1 dash physics: integratePhysics projects hSpeed via lockYaw. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.hSpeed = 10; a.hDecel = 0; a.gravityCoeff = 0;
    a.fbPhaseSlots[0] = 1; // ph1
    a.wallContact = 0;     // keep dashing (no exit)
    root(a);
    assert(a.pos.z === 10, "action0 ph1 dash: pos.z += hSpeed×cos(0) = 10 (lockYaw 0 faces +Z)");
    assert(a.fbPhaseSlots[0] === 1, "action0 ph1 stays in ph1 while no wallContact");
  }

  // --- ph1 wallContact exit (grounded, not airborne): land return zeroes yVel. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.hSpeed = 10; a.hDecel = 0; a.gravityCoeff = 0; a.yVel = 7;
    a.fbPhaseSlots[0] = 1;
    a.wallContact = 1; // exit trigger
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a); // ph1 → exit (grounded land return)
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph1 wallContact exit clears +0x73f / strips +0x5e0 bits");
    assert(a.yVel === 0 && a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action0 ph1 land return (zz_006a474_) zeroes all velocity scalars");
  }

  // --- ph1 wallContact exit (airborne): air return keeps selector mask (cue 6). ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[6 * 2 + 1] = 24;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.hSpeed = 10; a.hDecel = 0; a.gravityCoeff = 0;
    a.fbPhaseSlots[0] = 1;
    a.wallContact = 1;
    a.controlWord = 0x40 | 0x3; a.housekeeping73f = 1; // airborne + action bits
    root(a); // ph1 → air return (zz_006a5a4_)
    assert(a.ubState === 24, "action0 ph1 air return dispatches upper cue 6 (→ state 24)");
    assert((a.controlWord & 0x3) === 0, "action0 ph1 air return stripped action bits");
  }

  // --- rootAction no-ops for unsupported actionIndex. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; // no bespoke handler
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action1 falls through (no bespoke handler)");
  }

  // ==========================================================================
  // ACTION 3 — B-charge sword flurry.
  // ==========================================================================

  // --- ph0 setup: handlerTimer=600, timer560=60, streamSlot, zero scalars. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action3 ph0 advances to ph1");
    assert(a.handlerTimer === VK.FLURRY_WINDOW, "action3 ph0 +0x558 = 600.0 (FLOAT_8043a748)");
    assert(a.vkTimer560 === VK.WINDUP_TIMER, "action3 ph0 +0x560 = 60.0 (FLOAT_8043a74c)");
    assert(a.streamSlot === 1, "action3 ph0 streamSlot = 1 (seed 0 + advance)");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action3 ph0 zeroes all velocity scalars");
  }

  // --- ph0 airborne: streamSlot starts at 2 (group-3 air slot). ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0623", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.controlWord = VK.AIRBORNE_BIT;
    root(a);
    assert(a.streamSlot === 3, "action3 ph0 airborne streamSlot = 3 (seed 2 + advance)");
  }

  // --- ph1 windup: advance on +0x560 expiry → ph2 seeds flurry cursors. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.vkTimer560 = 1.0; // one frame from expiry
    root(a); // 1.0 − 1 = 0 ≤ 0 → advance
    assert(a.fbPhaseSlots[0] === 2, "action3 ph1 advances to ph2 when +0x560 <= 0.0");
    assert(a.streamCounter6eb === VK.FLURRY_SLOT_SEED, "action3 ph1→ph2 seeds +0x6eb = 4");
    assert(a.vkFlurryToggle6ec === 0, "action3 ph1→ph2 seeds +0x6ec = 0");
    assert(a.vkHitCount54c === 0, "action3 ph1→ph2 seeds +0x54c = 0");
    assert(a.vkFlurryMax54e === VK.FLURRY_MAX_54E, "action3 ph1→ph2 seeds +0x54e = 0x14");
  }

  // --- ph2 flurry: charge-hold bumps +0x54c to 2; wallContact spawns alternating shots. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, t) => shots.push({ addr, type: t }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = VK.FLURRY_WINDOW;
    a.statusWord5b4 = VK.CHARGE_BIT; // B held → charge latch active
    a.streamCounter6eb = VK.FLURRY_SLOT_SEED;
    a.vkHitCount54c = 0;
    a.vkFlurryToggle6ec = 0;
    // Frame 1: charge bumps +0x54c=2; wallContact → +0x6eb 4→3 (no wrap), +0x54c 2→1.
    a.wallContact = 1;
    root(a);
    assert(a.vkHitCount54c === 1, "action3 ph2 frame1: charge-bump +0x54c=2 then wallContact → 1");
    assert(a.streamCounter6eb === 3, "action3 ph2 frame1: +0x6eb 4→3 (no wrap, no shot)");
    assert(shots.length === 0, "action3 ph2 frame1: no flurry shot yet (+0x6eb not wrapped)");
    assert(a.fbPhaseSlots[0] === 2, "action3 ph2 frame1: stays in ph2 (latch sustained)");

    // Frame 2: charge re-bumps +0x54c=2 (1<2); wallContact → +0x6eb 3→2, +0x54c 2→1.
    root(a);
    assert(a.vkHitCount54c === 1, "action3 ph2 frame2: charge re-bump keeps +0x54c at 1 (2 then −1)");
    assert(a.streamCounter6eb === 2, "action3 ph2 frame2: +0x6eb 3→2");

    // Release B: clear charge bit. Frame 3: no bump; +0x6eb 2→1, +0x54c 1→0 → advance ph3.
    a.statusWord5b4 = 0;
    root(a);
    assert(a.streamCounter6eb === 1, "action3 ph2 frame3 (released): +0x6eb 2→1");
    assert(a.vkHitCount54c === 0 && a.fbPhaseSlots[0] === 3,
      "action3 ph2 frame3 (released): +0x54c 1→0 <1 advances to ph3");
  }

  // --- ph2 flurry shot cadence: 4 wallContacts wrap +0x6eb → spawn + toggle. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx({
      onFamilyProjectile: (addr, t) => shots.push({ addr, type: t }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0;          // skip the charge-bump branch
    a.wallContact = 1;
    a.streamCounter6eb = VK.FLURRY_SLOT_SEED;
    a.vkHitCount54c = 100;       // large latch → never advance during the cadence test
    a.vkFlurryToggle6ec = 0;
    // 4 frames wrap +0x6eb 4→3→2→1→0 (0<1 → toggle 0→1, spawn type 0x37, reseed 4).
    // ROM toggles +0x6ec BEFORE reading it (chunk_0040.c:4310-4313): first wrap = 0x37.
    for (let i = 0; i < 4; i += 1) root(a);
    assert(shots.length === 1 && shots[0]!.addr === SHOT_HELPER && shots[0]!.type === 0x37,
      `action3 ph2 first wrap spawns zz_0082824_(0x37) (toggle pre-read: 0^1=1) (got ${JSON.stringify(shots)})`);
    assert(a.vkFlurryToggle6ec === 1, "action3 ph2 wrap toggles +0x6ec to 1");
    // Next 4 frames wrap again → toggle 1→0 → spawn type 0x36.
    for (let i = 0; i < 4; i += 1) root(a);
    assert(shots.length === 2 && shots[1]!.type === 0x36,
      `action3 ph2 second wrap spawns zz_0082824_(0x36) (toggle 1^1=0) (got ${JSON.stringify(shots)})`);
  }

  // --- ph2 PROTO KING (0x61e): no flurry shot arm + 0x400 charge bit. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl061e", makeCtx({
      onFamilyProjectile: (addr, t) => shots.push({ addr, type: t }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0;
    a.wallContact = 1;
    a.streamCounter6eb = 1; // next wallContact wraps (1→0)
    a.vkHitCount54c = 100;
    a.vkFlurryToggle6ec = 0;
    root(a);
    assert(shots.length === 0, "action3 ph2 PROTO KING (0x61e) skips the flurry shot spawn");
  }

  // --- ph2 pl0621/pl0623 flurry record types (first wrap = base+1, toggle pre-read). ---
  {
    for (const { id, firstType } of [{ id: "pl0621" as const, firstType: 0x54 }, { id: "pl0623" as const, firstType: 0x56 }]) {
      const shots: Shot[] = [];
      const a = createRomActor() as VkActor;
      configureVictoryKingFamily(a, id, makeCtx({
        onFamilyProjectile: (addr, t) => shots.push({ addr, type: t }),
      }));
      const root = a.rootAction!;
      a.actionIndex = 3; a.dt = 1;
      a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
      a.fbPhaseSlots[0] = 2; a.handlerTimer = 0; a.wallContact = 1;
      a.streamCounter6eb = 1; a.vkHitCount54c = 100; a.vkFlurryToggle6ec = 0;
      root(a); // wrap → toggle 0→1 → spawn base+1
      assert(shots.length === 1 && shots[0]!.type === firstType,
        `action3 ph2 ${id} first wrap spawns zz_0082824_(0x${firstType.toString(16)})`);
    }
  }

  // --- ph3 recover: wallContact exit (grounded) → land return + +0x694 = 4+dt. ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 3;
    a.wallContact = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.hSpeed = 8; a.yVel = 4; a.hDecel = 2; a.gravityCoeff = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a); // ph3 → grounded land return
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action3 ph3 exit clears +0x73f / strips +0x5e0 bits");
    assert(a.stateTimer === VK.AIR_YVEL + 1, "action3 ph3 exit +0x694 = 4.0 + dt (FLOAT_8043a724)");
    assert(a.yVel === 0 && a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action3 ph3 land return (zz_006a474_) zeroes all velocity scalars");
  }

  // --- ph3 recover airborne: dispatches upper cue 7 (zz_006a750_(7)). ---
  {
    const a = createRomActor() as VkActor;
    configureVictoryKingFamily(a, "pl0610", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[7 * 2 + 1] = 30;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 3;
    a.wallContact = 1;
    a.controlWord = VK.AIRBORNE_BIT | 0x3; a.housekeeping73f = 1; // grounded && airborne
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.ubState === 30, "action3 ph3 airborne exit dispatches upper cue 7 (→ state 30)");
    assert(a.stateTimer === VK.AIR_YVEL + 1, "action3 ph3 airborne exit still seeds +0x694 = 4.0 + dt");
  }
}
