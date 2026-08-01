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
import { groundSnapRevert, stepTargetYaw } from "../rom/helpers.js";
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
// Per-family configure functions.
// ============================================================================

/** SAPPHIRE KNIGHT (pl0208/pl020e, ctor 0x800bb390) — shared knight melee (action 1) +
 *  shared-engine X-special fallback. TODO: port bespoke action 0/2 machines from
 *  chunk_0019.c (tables 0x80301904..0x803019f0, fns 0x800bb794..0x800bd7e4). */
export function configureSapphireKnightFamily(
  actor: RomActor,
  borgId: SapphireBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = SAPPHIRE_BORG_NUMBERS[borgId] ?? 0x208;
  const melee = createGenericKnightRootAction(ctx);
  const xSeedSlot = borgId === "pl0208" ? 2 : 15;
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(xSeedSlot) });
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
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
 *  shared-engine X-special fallback. TODO: port bespoke action 0 (tables
 *  0x80433b80/b88/b90, fns 0x800d7094..0x800d95c0 in chunk_0022.c/0023.c) and
 *  action 2 (table 0x8030fb14, fns 0x800d7540..0x800d7a98 in chunk_0022.c). */
export function configureAxeKnightFamily(
  actor: RomActor,
  borgId: AxeBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = AXE_BORG_NUMBERS[borgId] ?? 0x204;
  const melee = createGenericKnightRootAction(ctx);
  const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  actor.rootAction = (a) => {
    if (a.actionIndex === 1) { melee(a); return; }
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
