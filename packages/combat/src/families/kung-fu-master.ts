// KUNG-FU MASTER family (ctor 0x80076784) — ROM-faithful 1:1 port.
//
// Single borg: pl0800 (KUNG-FU MASTER, borgNumber 0x800). Currently UNREGISTERED in
// bridge.ts. Sibling shape shared by TAO MASTER (0x801) — see tao-master.ts.
//
// Source: research/decomp/ghidra-export/chunk_0010.c:3179-3493 + chunk_0011.c:1-1389.
// The ctor wires root dispatcher FUN_800769f0 (chunk_0010.c:3259) which indexes
// PTR_FUN_802d5f18[+0x580 actionIndex]. FUN_80076a2c (chunk_0010.c:3270) is the
// action-1 variant dispatch (steerYaw halve + PTR_FUN_802d5f24[+0x581]).
//
//   action 0 (shot volley): 4 variant tables @0x804338a0 / @0x804338a8 /
//                            @0x804338b0 / @0x804338b8. Each is a chain of [setup,
//                            active] pairs cycling stream group 2 through slots
//                            0/1/2/1 (FUN_80076ad8/b48/d0c/d9c/e00/fb0/7018). Each
//                            active phase ammo-gates zz_006dbe0_(0,1,1) then spawns
//                            zz_0082824_(0xc). Variants 1/2/3 tail into the action-2
//                            dive walker (FUN_8007831c/b0c) — cross-action handoff.
//   action 1 (melee combo): 4 variant tables @0x802d5f50 / @0x802d5f64 / @0x802d5f74 /
//                            @0x802d5f84. Long ground/air combo chain advancing the
//                            stream-slot cursor (+0x544) per hit; variant 3 tails
//                            into the action-2 dive (FUN_8007836c/849c/798/b5c).
//   action 2 (dive lunge):  2 variant tables @0x802d5f94 / @0x802d5fa0. The dive arc
//                            uses a Hermite-style motion solver over +0x144/+0x14c/
//                            +0x150/+0x154/+0x158/+0x15c/+0x164 (coefficients
//                            FLOAT_804378bc/c0/c4/c8). The solver body is TODO(host);
//                            the phase transitions + setup seeds + exits are ported.
//
// Float constants read from boot.dol this session (sdata2 @0x80437838..0x804378e0):
//   FLOAT_80437838 = 0.9    steerYaw decay (CONCAT44 double-coercion idiom)
//   DOUBLE_80437840 = (2^52 sentinel; GCC int->double magic, value 0)
//   FLOAT_80437848 = 0.0    zero scalar (velocity/pose resets, thresholds)
//   FLOAT_8043784c = -1.0   zz_004beb8_ stream rate
//   FLOAT_80437850 = 1.0    FUN_80067310 / zz_0067458_ gravity arg
//   FLOAT_80437854 = 7.9    action-0 v3 active hSpeed floor
//   FLOAT_80437858 = 30.0   action-1 v0 windup->active hSpeed seed
//   FLOAT_8043785c = 100.0  action-1 v0 ph2 range-check threshold
//   FLOAT_80437860 = 0.5    velocity drag (slow-damp / hit-react)
//   FLOAT_80437864 = 0.95   motion scale (slow-damp false branch)
//   FLOAT_80437868 = 0.99   steerYaw decay (action-1 v1 drift)
//   FLOAT_80437870 = 300.0  action-1 v1 ph1 slow-damp threshold
//   FLOAT_80437874 = 60.0   action-1 v2/v3 ph0 +0x558 seed (lunge windup)
//   FLOAT_80437878 = 20.0   action-1 v1 ph1 +0x548 re-seed (active timer)
//   FLOAT_8043787c = 0.125  action-1 v1 ph2 velocity projection scale
//   FLOAT_80437880 = 0.03125 action-1 v1 ph2 hDecel scale
//   FLOAT_80437884 = 40.0   action-1 v1 ph2 no-target hSpeed; action-2 +0x558 seed
//   FLOAT_80437888 = 10.0   action-1 v2 ph3 exit +0x694 seed
//   FLOAT_8043788c = 8.0    action-2 ph0 +0x44 hSpeed seed
//   FLOAT_80437890 = -0.15  action-2 ph0 +0x50 gravityCoeff seed
//   FLOAT_80437894 = 7.0    action-2 ph1 active hSpeed seed
//   FLOAT_8043789c = -0.9   action-2 ph1 +0x4c motion drag
//   FLOAT_804378a0 = -0.7   action-2 ph1 +0x50 gravityCoeff (default exit branch)
//   FLOAT_804378a4 = 0.0054931640625 action-2 turn coefficient (BAM rad scaler)
//   DOUBLE_804378a8 = 360.0 (2pi wrap constant for the BAM yaw normalization)
//   FLOAT_804378b0 = 2160.0 action-2 +0x154 base (360x6)
//   FLOAT_804378bc = -12.0  action-2 motion solver coefficient (jerk term)
//   FLOAT_804378c0 = 6.0    action-2 motion solver coefficient
//   FLOAT_804378c4 = 4.0    action-2 motion solver coefficient
//   DOUBLE_804378d0 = 0.25  action-2 motion solver completion threshold
//   FLOAT_804378d8 = 200.0  action-2 v1 ph1 distance threshold (lock release)
//   FLOAT_804378dc = -40.0  action-2 v1 ph1 +0x48 yVel floor
//   FLOAT_804378e0 = 2.0    action-2 v1 ph1 hSpeed multiplier
//
// Exit helpers zz_006a474_ (romGroundIdleReturn), zz_006a5a4_ (romAirKnockoutReturn)
// are ported in shared-idle-return.ts.

import { createRomActor, type RomActor, type Vec3 } from "../rom/actor.js";
import { allocateWeapon, groundSnapRevert, stepTargetYaw } from "../rom/helpers.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ============================================================================
// Borg identity.
// ============================================================================

const KUNG_FU_MASTER_BORG_NUMBERS: Record<string, number> = {
  pl0800: 0x800,
};

export type KungFuMasterBorgId = keyof typeof KUNG_FU_MASTER_BORG_NUMBERS;

// ============================================================================
// Spawner addresses (named const exports per the family-port contract).
// ============================================================================

/** zz_0082824_ @0x80082824 — record-table projectile spawn (KUNG-FU MASTER shot, type 0xc). */
export const KUNG_FU_MASTER_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — per-borg effect spawn (reserved; KFM uses only zz_0082824_). */
export const KUNG_FU_MASTER_EFFECT_SPAWNER = 0x800c3be0;

// ============================================================================
// Config constants (DOL-read this session; see header for citations).
// ============================================================================

export const KFM = {
  /** FLOAT_80437838 = 0.9 — steerYaw decay factor. */
  STEER_DECAY: 0.9,
  /** FLOAT_80437848 = 0.0 — zero scalar + threshold. */
  ZERO: 0.0,
  /** FLOAT_8043784c = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80437850 = 1.0 — FUN_80067310 / zz_0067458_ gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_80437854 = 7.9 — action-0 v3 active hSpeed floor. */
  A0_V3_HSPEED_FLOOR: 7.9,
  /** FLOAT_80437858 = 30.0 — action-1 v0 windup->active hSpeed seed. */
  A1_V0_HSPEED: 30.0,
  /** FLOAT_8043785c = 100.0 — action-1 v0 ph2 range-check threshold. */
  A1_V0_RANGE: 100.0,
  /** FLOAT_80437860 = 0.5 — velocity drag (slow-damp / hit-react). */
  DRAG_HALF: 0.5,
  /** FLOAT_80437864 = 0.95 — motion scale (slow-damp false branch). */
  MOTION_SCALE: 0.95,
  /** FLOAT_80437868 = 0.99 — steerYaw decay (action-1 v1 drift). */
  DECAY_0P99: 0.99,
  /** FLOAT_80437870 = 300.0 — action-1 v1 ph1 slow-damp threshold. */
  A1_V1_SLOW_THRESHOLD: 300.0,
  /** FLOAT_80437874 = 60.0 — action-1 v2/v3 ph0 +0x558 seed. */
  A1_V2_WINDUP: 60.0,
  /** FLOAT_80437878 = 20.0 — action-1 v1 ph1 +0x548 re-seed. */
  A1_V1_ACTIVE_TIMER: 20.0,
  /** FLOAT_8043787c = 0.125 — action-1 v1 ph2 velocity projection scale. */
  A1_V1_PROJ_SCALE: 0.125,
  /** FLOAT_80437880 = 0.03125 — action-1 v1 ph2 hDecel scale. */
  A1_V1_HDECEL_SCALE: 0.03125,
  /** FLOAT_80437884 = 40.0 — action-1 v1 ph2 no-target hSpeed; action-2 +0x558 seed. */
  A1_V1_NO_TARGET_HSPEED: 40.0,
  A2_TIMER_SEED: 40.0,
  /** FLOAT_80437888 = 10.0 — action-1 v2 ph3 exit +0x694 seed. */
  A1_V2_EXIT_TIMER: 10.0,
  /** FLOAT_8043788c = 8.0 — action-2 ph0 +0x44 hSpeed seed. */
  A2_HSPEED_SEED: 8.0,
  /** FLOAT_80437890 = -0.15 — action-2 ph0 +0x50 gravityCoeff seed. */
  A2_GRAVITY: -0.15,
  /** FLOAT_80437894 = 7.0 — action-2 ph1 active hSpeed seed. */
  A2_ACTIVE_HSPEED: 7.0,
  /** FLOAT_8043789c = -0.9 — action-2 ph1 +0x4c motion drag. */
  A2_DRAG: -0.9,
  /** FLOAT_804378a0 = -0.7 — action-2 ph1 +0x50 gravityCoeff (default exit branch). */
  A2_GRAVITY_EXIT: -0.7,
  /** FLOAT_804378d8 = 200.0 — action-2 v1 ph1 distance threshold. */
  A2_V1_DIST_THRESHOLD: 200.0,
  /** FLOAT_804378dc = -40.0 — action-2 v1 ph1 +0x48 yVel floor. */
  A2_V1_YVEL_FLOOR: -40.0,
  /** FLOAT_804378e0 = 2.0 — action-2 v1 ph1 hSpeed multiplier. */
  A2_V1_HSPEED_MULT: 2.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5d4 bit 0x40 — B-repress edge (action-0/1 ph active latch). */
  B_REPRESS_EDGE: 0x40,
  /** +0x5d4 bit 0x80 — action-2 ph1 B-hold drain edge. */
  B_HOLD_EDGE: 0x80,
  /** action-0 stream group. */
  ACTION0_STREAM_GROUP: 2,
  /** action-1 stream group. */
  ACTION1_STREAM_GROUP: 3,
  /** action-2 stream group. */
  ACTION2_STREAM_GROUP: 4,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** action-1 v0 ph0 +0x548 seed (0x14 = 20 frames). */
  A1_V0_TIMER_SEED: 0x14,
  /** action-1 v1 ph0 +0x548 seed (0x3c = 60 frames). */
  A1_V1_TIMER_SEED: 0x3c,
  /** action-1 ph1->ph2 +0x548 re-seed (0x1e = 30 frames). */
  A1_V1_ACTIVE_RESEED: 0x1e,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not firstclass on RomActor.
// ============================================================================

export interface KungFuMasterScratch {
  /** +0x548 (s16): action-1 windup/active timer (drained each frame). */
  kfmTimer548?: number;
  /** +0x544 (s8): action-1 stream-slot / combo-step cursor (++ per advance). */
  kfmStep544?: number;
  /** +0x545 (s8): action-1 v0 ph4 latch (stream-arm gate). */
  kfmLatch545?: number;
  /** +0x745 (s8): B-repress latch (set on +0x5d4 & 0x40). */
  kfmComboLatch745?: number;
  /** +0x746 (s8): action-1 v0 combo hit count. */
  kfmHitCount746?: number;
  /** +0x764 (f32): action-1 slow-damp speed scalar. */
  kfmSpeedScalar764?: number;
  /** +0x760 (f32): action-1 v1 slow-damp speed scalar. */
  kfmSpeedScalar760?: number;
  /** +0x54a (s16): action-2 ph0 latch count (10). */
  kfmLatch54a?: number;
  /** +0x54e (s16): action-1 v1 part-pitch seed (lockYaw snapshot). */
  kfmSeed54e?: number;
  /** +0x71c (s8): action-1 v2/v3 ph3 steerYaw-decay gate. */
  kfmSteerGate71c?: number;
  /** +0x6f7 (s8): action-2 air-mode byte. */
  kfmAirMode6f7?: number;
  /** +0x1d9 (s8): hit-react byte (action-1 v1 active advance). */
  kfmHitReact1d9?: number;
  /** +0x174 (s8): action-2 ground-probe result latch. */
  kfmGround174?: number;
  /** +0x175 (s8): action-2 motion-solver completion latch. */
  kfmSolved175?: number;
  /** +0x15c/+0x164/+0x154 action-2 Hermite motion solver state.
   *  TODO(host): the solver integrates these each frame against FLOAT_804378bc/c0/c4. */
  kfmSolver?: {
    arc15c?: number; arcTime164?: number; curvature154?: number;
  };
}

type KfmActor = RomActor & KungFuMasterScratch;

function scratchOf(actor: RomActor): KfmActor {
  return actor as KfmActor;
}

// ============================================================================
// LockTarget / range helpers (samurai / gold-hero pattern).
// ============================================================================

function lockTarget(a: RomActor): Vec3 | null {
  return (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget ?? null;
}

function hasLock(a: RomActor): boolean {
  return lockTarget(a) != null;
}

function targetDistance(a: RomActor): number {
  const t = lockTarget(a);
  if (!t) return Infinity;
  return Math.hypot(t.x - a.pos.x, t.y - a.pos.y, t.z - a.pos.z);
}

/** FUN_80066838(range, actor) — horizontal-distance range gate. -1 no lock,
 *  1 when in range, 0 beyond. */
function rangeCheck(a: RomActor, range: number): number {
  if (!hasLock(a)) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

/** actor+0x868 row float ((prevActionIndex % 3) * 0xc + 0x868, column 0). */
function rangeRow868(a: KfmActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? KFM.A1_V0_HSPEED;
}

/** actor+0x86c column-1 row float. */
function rangeRow86c(a: KfmActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? KFM.A2_HSPEED_SEED;
}

/** actor+0x870 column-2 row float (action-1 v3 range gate). */
function rangeRow870(a: KfmActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? KFM.A2_HSPEED_SEED;
}

/** zz_00670dc_(actor, yaw) — physics-move projecting hSpeed via yaw (no gravity). */
function physicsMove(a: RomActor, yaw: number): void {
  integratePhysics(0, a, yaw);
}

/** dataPage(+0x4ac)+0x6c — gravityCoeff restore (descriptor.handlerData6c). */
function gravityRestore(a: RomActor): number {
  return a.descriptor?.handlerData6c ?? 0;
}

// ============================================================================
// zz_0076c80_ (action-0 setup tail) — FUN_80076c80 @ chunk_0010.c:3362.
// Advance +0x540, clear +0x541/+0x548/+0x745, aim. Shared by every action-0 setup.
// ============================================================================
function action0SetupTail(a: KfmActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  a.fbPhaseSlots[1] = 0;          // +0x541 = 0
  a.kfmTimer548 = 0;              // +0x548 = 0
  a.kfmComboLatch745 = 0;         // +0x745 = 0
  stepTargetYaw(a, 0x81, 0, true); // zz_006660c_ + zz_007933c_(0x81)
}

// ============================================================================
// ACTION 0 — shot volley. 4 variant tables, each a chain of [setup, active] pairs.
// ============================================================================

/** FUN_80076ad8 @ chunk_0010.c:3296 (28i) — v0 ph0: zero scalars, stream g=2 slot 0. */
function action0SetupSlot0(a: KfmActor): void {
  a.gravityCoeff = KFM.ZERO;
  a.yVel = KFM.ZERO;
  a.hDecel = KFM.ZERO;
  a.hSpeed = KFM.ZERO;
  a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION0_STREAM_GROUP, 0, KFM.STREAM_RATE);
  action0SetupTail(a);
}

/** FUN_80076d0c @ chunk_0010.c:3389 (22i) — stream g=2 slot 1. */
function action0SetupSlot1(a: KfmActor): void {
  a.gravityCoeff = KFM.ZERO;
  a.yVel = KFM.ZERO;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION0_STREAM_GROUP, 1, KFM.STREAM_RATE);
  action0SetupTail(a);
}

/** FUN_80076d9c @ chunk_0010.c:3419 (25i) — stream g=2 slot 2.
 *  variantIndex==2 -> restore gravityCoeff from descriptor.+0x6c. */
function action0SetupSlot2(a: KfmActor): void {
  startStream(a, KFM.STREAM_MASK, KFM.ACTION0_STREAM_GROUP, 2, KFM.STREAM_RATE);
  action0SetupTail(a);
  if (a.variantIndex === 2) {
    a.gravityCoeff = gravityRestore(a);
  }
}

/** FUN_80076fb0 @ chunk_0011.c:3 (26i) — stream g=2 slot 1; +0x4c=streamRate; +0x80c=0. */
function action0SetupSlot1B(a: KfmActor): void {
  a.gravityCoeff = KFM.ZERO;
  a.yVel = KFM.ZERO;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION0_STREAM_GROUP, 1, KFM.STREAM_RATE);
  action0SetupTail(a);
  a.hDecel = KFM.STREAM_RATE;    // +0x4c = FLOAT_8043784c (-1.0)
  a.accumulator80c = KFM.ZERO;   // +0x80c = FLOAT_80437848
}

/** FUN_80076b48 @ chunk_0010.c:3320 (78i) — ground active. Tick stream, aim, ground
 *  snap, contact->ammo-gate->spawn zz_0082824_(0xc); exit branches on +0x541. */
function action0ActiveGround(a: KfmActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & KFM.B_REPRESS_EDGE) !== 0) a.kfmComboLatch745 = 1;
  tickStream(a, KFM.STREAM_MASK, ctx);
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw); // zz_0067458_(1.0, lockYaw)
  groundSnapRevert(a);
  const cVar = a.fbPhaseSlots[1] ?? 0;
  if (cVar === 1) {
    if (a.contactP0 === -1) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 1) {
    if (cVar === 0 && a.contactP0 === 3 && a.contactP1 === 1) {
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(a, KUNG_FU_MASTER_SHOT_HELPER, 0xc);
      }
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 3 && a.wallContact !== 0) {
    romGroundIdleReturn(a);
  }
}

/** FUN_80076e00 @ chunk_0010.c:3434 (94i) — physics/air active. FUN_80067310 +
 *  zz_00677b0_ ground probe; grounded -> air-return exit; else +0x541 branches. */
function action0ActiveAir(a: KfmActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & KFM.B_REPRESS_EDGE) !== 0) a.kfmComboLatch745 = 1;
  tickStream(a, KFM.STREAM_MASK, ctx);
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  if (grounded) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
    romAirKnockoutReturn(a);
    return;
  }
  const cVar = a.fbPhaseSlots[1] ?? 0;
  if (cVar === 1) {
    if (a.contactP0 === -1) {
      a.gravityCoeff = gravityRestore(a);
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 1) {
    if (cVar === 0 && a.contactP0 === 3 && a.contactP1 === 1) {
      a.gravityCoeff = gravityRestore(a);
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(a, KUNG_FU_MASTER_SHOT_HELPER, 0xc);
      }
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 3 && a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
    romAirKnockoutReturn(a);
  }
}

/** FUN_80077018 @ chunk_0011.c:25 (75i) — v3 active (+0x80c variant). hSpeed floor
 *  clamp (7.9), contact->spawn, exit on wallContact/contactP0<0. */
function action0ActiveV3(a: KfmActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  tickStream(a, KFM.STREAM_MASK, ctx);
  if (a.hSpeed < KFM.A0_V3_HSPEED_FLOOR) a.hSpeed = KFM.A0_V3_HSPEED_FLOOR;
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  if ((a.fbPhaseSlots[1] ?? 0) === 0 && a.contactP0 === 3 && a.contactP1 === 1) {
    if (allocateWeapon(a, ctx, 0, 1, true)) {
      ctx.onFamilyProjectile?.(a, KUNG_FU_MASTER_SHOT_HELPER, 0xc);
    }
    a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
  }
  if (a.wallContact !== 0 || a.contactP0 === -1) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
    if (a.ubCue === 0x2c) romGroundIdleReturn(a);
    else romAirKnockoutReturn(a);
  }
}

// ============================================================================
// ACTION 1 — melee combo. 4 variant tables @0x802d5f50 / @0x802d5f64 / @0x802d5f74 /
// @0x802d5f84. Each variant-table walker clears +0xcc if +0x541 set.
// ============================================================================

/** FUN_80077214 @ chunk_0011.c:97 (58i) — v0 ph0 setup. */
function action1V0Phase0(a: KfmActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.accumulator80c = KFM.ZERO;
  a.kfmTimer548 = KFM.A1_V0_TIMER_SEED;
  a.kfmComboLatch745 = 0;
  a.kfmHitCount746 = 0;
  a.kfmStep544 = 0;
  a.hSpeed = KFM.ZERO;
  a.hDecel = KFM.ZERO;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.activeYaw = a.heading;
  }
  stepTargetYaw(a, 0xc0);
  const step = a.kfmStep544 ?? 0;
  a.kfmStep544 = step + 1;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, step, KFM.STREAM_RATE);
}

/** FUN_800772fc @ chunk_0011.c:133 (37i) — v0 ph1 windup. */
function action1V0Phase1(a: KfmActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) tickStream(a, KFM.STREAM_MASK, ctx);
  const t = (a.kfmTimer548 ?? 0) - 1;
  a.kfmTimer548 = t;
  if (t < 1 || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.kfmTimer548 = KFM.A1_V0_TIMER_SEED;
    a.hSpeed = KFM.A1_V0_HSPEED;
    a.hDecel = KFM.ZERO;
  }
}

/** FUN_80077390 @ chunk_0011.c:162 (51i) — v0 ph2 active. */
function action1V0Phase2(a: KfmActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0xc0);
  physicsMove(a, a.lockYaw);
  tickStream(a, KFM.STREAM_MASK, ctx);
  const t = (a.kfmTimer548 ?? 0) - 1;
  a.kfmTimer548 = t;
  if (t < 1 || rangeCheck(a, KFM.A1_V0_RANGE) !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.fbPhaseSlots[2] = 0;
    const step = a.kfmStep544 ?? 0;
    a.kfmStep544 = step + 1;
    startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, step, KFM.STREAM_RATE);
    a.kfmHitCount746 = (a.kfmHitCount746 ?? 0) + 1;
    a.kfmLatch545 = 0;
  }
}

/** FUN_8007745c @ chunk_0011.c:193 (98i) — v0 ph3 recover/loop. */
function action1V0Phase3(a: KfmActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & KFM.B_REPRESS_EDGE) !== 0) a.kfmComboLatch745 = 1;
  const cVar = a.fbPhaseSlots[2] ?? 0;
  let uVar = 1;
  if (cVar === 1) { recoverTail(a, ctx, 1); return; }
  if (cVar < 1 && cVar === 0) {
    if (a.contactP0 === -1) {
      uVar = 3;
      if ((a.kfmComboLatch745 ?? 0) < 1) {
        if ((a.kfmLatch545 ?? 0) === 0) {
          if (a.wallContact !== 0) {
            startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 7, KFM.STREAM_RATE);
            a.kfmLatch545 = 1;
          }
        } else {
          uVar = 1;
        }
      } else {
        a.kfmComboLatch745 = 0;
        if ((a.kfmHitCount746 ?? 0) < 8) {
          if ((a.kfmStep544 ?? 0) === 6) a.kfmStep544 = 2;
        } else {
          a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
          a.fbPhaseSlots[3] = 0;
          a.kfmStep544 = 6;
        }
        a.kfmLatch545 = 0;
        const step = a.kfmStep544 ?? 0;
        a.kfmStep544 = step + 1;
        startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, step, KFM.STREAM_RATE);
        a.kfmHitCount746 = (a.kfmHitCount746 ?? 0) + 1;
      }
    }
    recoverTail(a, ctx, uVar);
  }
}

/** FUN_800775e4 @ chunk_0011.c:252 (9i) — v0 ph4. zz_0077608_(actor, 1). */
function action1V0Phase4(a: KfmActor, ctx: StreamContext): void {
  recoverTail(a, ctx, 1);
}

// zz_0077608_ (action-1 recover tail) — chunk_0011.c:263.
function recoverTail(a: KfmActor, ctx: StreamContext, param: number): void {
  if ((param & 1) !== 0) tickStream(a, KFM.STREAM_MASK, ctx);
  if (a.faceGate1d10 !== 0) stepTargetYaw(a, 0xc0);
  if (a.dashStrength1d0f !== 0) {
    a.dashStrength1d0f = 0;
    a.kfmTimer548 = KFM.A1_V0_TIMER_SEED;
    a.hSpeed = KFM.A1_V0_HSPEED;
    a.hDecel = KFM.ZERO;
  }
  if (KFM.A1_V1_SLOW_THRESHOLD <= (a.kfmSpeedScalar764 ?? 0)) {
    a.hSpeed *= KFM.MOTION_SCALE;
  } else {
    a.hSpeed *= KFM.DRAG_HALF;
  }
  if ((a.kfmHitReact1d9 ?? 0) !== 0) a.hSpeed *= KFM.DRAG_HALF;
  physicsMove(a, a.lockYaw);
  if ((param & 2) === 0 && a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
    romGroundIdleReturn(a);
  }
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x802d5f64 (walker FUN_80077720). Flight/dash melee.
// ----------------------------------------------------------------------------

function action1V1Phase0(a: KfmActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.accumulator80c = KFM.ZERO;
  a.kfmSeed54e = a.lockYaw;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.activeYaw = a.lockYaw;
  }
  a.kfmTimer548 = KFM.A1_V1_TIMER_SEED;
  stepTargetYaw(a, 0xc0);
  a.hSpeed *= KFM.DECAY_0P99;
  a.hDecel *= KFM.DECAY_0P99;
  physicsMove(a, a.kfmSeed54e ?? a.lockYaw);
  startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 0, KFM.STREAM_RATE);
}

function action1V1Phase1(a: KfmActor, _ctx: StreamContext): void {
  a.hSpeed *= KFM.DECAY_0P99;
  a.hDecel *= KFM.DECAY_0P99;
  physicsMove(a, a.kfmSeed54e ?? a.lockYaw);
  const t = (a.kfmTimer548 ?? 0) - 1;
  a.kfmTimer548 = t;
  if (t < 1 || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.kfmTimer548 = KFM.A1_V1_ACTIVE_RESEED;
    const row = rangeRow868(a);
    const src = hasLock(a) && row < (a.kfmSpeedScalar764 ?? 0) ? (a.kfmSpeedScalar764 ?? 0) : row;
    a.hSpeed = src / KFM.A1_V0_HSPEED;
    a.hDecel = KFM.ZERO;
  }
}

function action1V1Phase2(a: KfmActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0xc0);
  physicsMove(a, a.lockYaw);
  tickStream(a, KFM.STREAM_MASK, ctx);
  const t = (a.kfmTimer548 ?? 0) - 1;
  a.kfmTimer548 = t;
  if (t < 1 || rangeCheck(a, KFM.A1_V1_SLOW_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 10, KFM.STREAM_RATE);
  }
}

function action1V1Phase3(a: KfmActor, ctx: StreamContext): void {
  tickStream(a, KFM.STREAM_MASK, ctx);
  stepTargetYaw(a, 0xc0);
  a.hSpeed *= KFM.STEER_DECAY;
  physicsMove(a, a.lockYaw);
  if (a.wallContact !== 0) {
    a.streamCounter6eb = 0;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
    romGroundIdleReturn(a);
  }
}

// ----------------------------------------------------------------------------
// Variant 2 — table @0x802d5f74 (walker FUN_80077a9c). Lunge melee.
//   ph2 FUN_80077c2c velocity-projection reads part anchor +0x8e0/+0x8f0/+0x900;
//   TODO(host) for anchor resolution; structure + drain + advance ported faithful.
// ----------------------------------------------------------------------------

function action1V2Phase0(a: KfmActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  if (rangeCheck(a, rangeRow86c(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
  }
  a.handlerTimer = KFM.A1_V2_WINDUP;
  a.streamSlot = 3;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 8, KFM.STREAM_RATE);
}

function action1V2Phase1(a: KfmActor, _ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  const t = a.handlerTimer - KFM.PHYSICS_GRAVITY;
  a.handlerTimer = t;
  if (t <= KFM.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.handlerTimer = KFM.A1_V1_ACTIVE_TIMER;
  }
}

function action1V2Phase2(a: KfmActor, ctx: StreamContext): void {
  tickStream(a, KFM.STREAM_MASK, ctx);
  if (!hasLock(a)) {
    a.hSpeed = KFM.A1_V1_NO_TARGET_HSPEED;
    a.hDecel = KFM.ZERO; a.yVel = KFM.ZERO;
    a.gravityCoeff = gravityRestore(a);
  } else {
    // TODO(host): +0x8e0/+0x8f0/+0x900 part-anchor projection (chunk_0011.c:520-536).
    const t = lockTarget(a)!;
    const mag = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    a.hSpeed = mag * KFM.A1_V1_PROJ_SCALE;
    a.hDecel = -a.hSpeed * KFM.A1_V1_HDECEL_SCALE;
    a.yVel = (t.y - a.pos.y) * KFM.A1_V1_PROJ_SCALE;
    a.gravityCoeff = KFM.ZERO;
  }
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  if ((a.kfmHitReact1d9 ?? 0) === 0) {
    a.handlerTimer = a.handlerTimer - a.dt;
  }
  if (a.handlerTimer <= KFM.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 9, KFM.STREAM_RATE);
  }
}

function action1V2Phase3(a: KfmActor, ctx: StreamContext): void {
  tickStream(a, KFM.STREAM_MASK, ctx);
  if ((a.kfmSteerGate71c ?? 0) === 0) {
    integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
    if (a.hSpeed < KFM.ZERO) { a.hSpeed = KFM.ZERO; a.hDecel = KFM.ZERO; }
    groundSnapRevert(a);
    if (a.wallContact !== 0) {
      a.stateTimer = KFM.A1_V2_EXIT_TIMER + a.dt;
      romAirKnockoutReturn(a);
    }
  }
}

// ----------------------------------------------------------------------------
// Variant 3 — table @0x802d5f84 (walker FUN_80077e68). Extended lunge -> dive handoff.
//   ph2 FUN_80078020 uses FUN_800452a0 steerYaw clamp (aim solver) — TODO(host).
// ----------------------------------------------------------------------------

function action1V3Phase0(a: KfmActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[1] = 0;
  a.fbPhaseSlots[2] = 0;
  if (rangeCheck(a, rangeRow870(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
  }
  a.handlerTimer = KFM.A1_V2_WINDUP;
  a.streamSlot = 3;
  startStream(a, KFM.STREAM_MASK, KFM.ACTION1_STREAM_GROUP, 0xb, KFM.STREAM_RATE);
}

function action1V3Phase1(a: KfmActor, _ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  const t = a.handlerTimer - KFM.PHYSICS_GRAVITY;
  a.handlerTimer = t;
  if (t <= KFM.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.handlerTimer = KFM.A1_V1_ACTIVE_TIMER;
    if (a.hSpeed < KFM.A1_V0_HSPEED) a.hSpeed = KFM.A1_V1_ACTIVE_TIMER;
    a.hDecel = KFM.STEER_DECAY;
  }
}

function action1V3Phase2(a: KfmActor, ctx: StreamContext): void {
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar === 1) {
    integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  } else if (cVar < 1 && cVar === 0) {
    if ((a.fbPhaseSlots[1] ?? 0) === 0) {
      stepTargetYaw(a, 0x81, 0, true);
      a.lockYaw = a.activeYaw;
      if (hasLock(a)) {
        // TODO(host): +0x8e0/+0x8f0/+0x900 anchor projection into +0x48.
        a.yVel = (lockTarget(a)!.y - a.pos.y) * KFM.A1_V1_PROJ_SCALE;
        a.gravityCoeff = KFM.ZERO;
      }
      if (rangeCheck(a, KFM.A1_V2_WINDUP) !== 0) a.fbPhaseSlots[1] = 1;
    }
    // TODO(host): FUN_800452a0(yVel, hSpeed) -> steerYaw clamp +/-0x38e (aim solver).
  }
  tickStream(a, KFM.STREAM_MASK, ctx);
  if (KFM.A1_V1_NO_TARGET_HSPEED < a.hSpeed) {
    a.hSpeed = KFM.A1_V1_NO_TARGET_HSPEED;
    a.hDecel = KFM.ZERO;
  }
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  if (grounded && (a.fbPhaseSlots[2] ?? 0) === 0) {
    a.steerYaw = 0; a.yVel = KFM.ZERO; a.gravityCoeff = KFM.ZERO;
    a.fbPhaseSlots[1] = 1;
  }
  a.handlerTimer = a.handlerTimer - a.dt;
  if (a.handlerTimer <= KFM.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  }
}

function action1V3Phase3(a: KfmActor, ctx: StreamContext): void {
  tickStream(a, KFM.STREAM_MASK, ctx);
  if ((a.kfmSteerGate71c ?? 0) === 0) {
    integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
    groundSnapRevert(a);
    if (a.wallContact !== 0) {
      a.steerYaw = 0;
      a.stateTimer = KFM.A1_V2_EXIT_TIMER + a.dt;
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
  }
}

// ============================================================================
// ACTION 2 — dive lunge. 2 variant tables @0x802d5f94 / @0x802d5fa0. The dive arc
// uses a Hermite-style motion solver (coefficients FLOAT_804378bc/c0/c4). Solver body
// is TODO(host); phase transitions + setup seeds + exits are ported faithful.
// ============================================================================

/** FUN_8007836c @ chunk_0011.c:792 (76i) — v0 ph0 setup. */
function action2V0Phase0(a: KfmActor): void {
  a.accumulator80c = KFM.ZERO;
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[1] = 0; a.fbPhaseSlots[2] = 0; a.fbPhaseSlots[3] = 0;
  a.kfmHitCount746 = 0;
  a.handlerTimer = KFM.A2_TIMER_SEED;
  a.kfmLatch54a = 10;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.lockYaw = a.heading;
  } else {
    stepTargetYaw(a, 0x81, 0, true);
    a.lockYaw = a.activeYaw;
    a.heading = a.lockYaw;
  }
  a.hSpeed = KFM.A2_HSPEED_SEED;
  a.hDecel = KFM.STEER_DECAY;
  a.yVel = KFM.ZERO;
  a.gravityCoeff = KFM.A2_GRAVITY;
  groundSnapRevert(a);
  a.kfmStep544 = 0;
  startStream(a, 0x3, KFM.ACTION2_STREAM_GROUP, 0, KFM.STREAM_RATE);
}

/** FUN_8007849c @ chunk_0011.c:843 (191i) — v0 ph1 active. Motion-solver + B-hold
 *  drain + contact branches. Solver body TODO(host); transitions ported. */
function action2V0Phase1(a: KfmActor, ctx: StreamContext): void {
  a.handlerTimer = a.handlerTimer - a.dt;
  tickStream(a, KFM.STREAM_MASK, ctx);
  if ((a.fbPhaseSlots[3] ?? 0) === 0 && (a.kfmHitReact1d9 ?? 0) !== 0) {
    if ((a.fbPhaseSlots[2] ?? 0) < 2) a.kfmAirMode6f7 = 0x38;
    a.hSpeed = KFM.A2_ACTIVE_HSPEED;
    a.hDecel = KFM.ZERO;
    a.fbPhaseSlots[1] = 1;
    a.fbPhaseSlots[2] = 3;
    a.fbPhaseSlots[3] = 1;
  }
  if ((a.kfmStep544 ?? 0) === 1) {
    if ((a.fbPhaseSlots[1] ?? 0) === 0) {
      stepTargetYaw(a, 0x81, 0, true);
      a.lockYaw = a.activeYaw;
      if (rangeCheck(a, KFM.A1_V2_WINDUP) !== 0) a.fbPhaseSlots[1] = 1;
    }
    integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  }
  groundSnapRevert(a);
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar === 0) {
    if (a.contactP0 === 4 && a.contactP1 === 1) {
      a.fbPhaseSlots[2] = 1;
      a.kfmStep544 = 1;
    } else if (a.wallContact !== 0) {
      a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
      a.kfmAirMode6f7 = 0x38;
    }
  }
  if (cVar > 2 && cVar !== 4) {
    a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
    a.yVel = KFM.A2_ACTIVE_HSPEED;
    a.gravityCoeff = KFM.ZERO; a.hDecel = KFM.ZERO;
  }
  if (cVar > 2 && cVar !== 4 && ((a.inputEdge5d4 & KFM.B_HOLD_EDGE) !== 0) && (a.kfmLatch54a ?? 0) > 0) {
    a.handlerTimer += KFM.PHYSICS_GRAVITY;
    a.kfmLatch54a = (a.kfmLatch54a ?? 0) - 1;
  }
  if (a.handlerTimer <= KFM.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.fbPhaseSlots[2] = 0;
    a.hDecel = KFM.A2_DRAG;
    a.gravityCoeff = KFM.A2_GRAVITY_EXIT;
    // TODO(host): Hermite motion-solver seed (FLOAT_804378a4 = 0.005493...; DOUBLE_804378a8).
    if (!a.kfmSolver) a.kfmSolver = {};
    a.kfmSolver.curvature154 = 2160.0;
    a.kfmSolved175 = 0;
  }
}

/** FUN_80078798 @ chunk_0011.c:959 (221i) — v0 ph2 motion-solver + exit. Solver body
 *  TODO(host); exit transitions ported faithful. */
function action2V0Phase2(a: KfmActor, ctx: StreamContext): void {
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar !== 2) {
    if (cVar > 1) {
      if (cVar !== 4) {
        if (cVar <= 3 && tickStream(a, KFM.STREAM_MASK, ctx)) {
          a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
        }
      }
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
      if ((a.kfmLatch545 ?? 0) === 0) { romAirKnockoutReturn(a); return; }
      romGroundIdleReturn(a);
      return;
    }
    if (cVar === 0) {
      a.kfmSolver = a.kfmSolver ?? {};
      a.kfmSolver.arc15c = KFM.A1_V2_WINDUP;
      a.hDecel = -(a.hSpeed / KFM.A1_V2_WINDUP);
      // TODO(host): Hermite seed of +0x144/+0x14c/+0x150/+0x158/+0x164.
      a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
    }
    // TODO(host): Hermite integration step (chunk_0011.c:1014-1052) once +0x154 surfaced.
  }
  if (a.kfmGround174 === 1) {
    a.kfmLatch545 = 1;
    startStream(a, KFM.STREAM_MASK, KFM.ACTION2_STREAM_GROUP, 2, KFM.STREAM_RATE);
  } else {
    a.kfmLatch545 = 0;
  }
  a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  a.kfmGround174 = grounded ? 1 : 0;
  if (grounded) {
    if ((a.fbPhaseSlots[2] ?? 0) < 2 || (a.kfmLatch545 ?? 0) === 1) {
      // zz_00b22f4_(actor) — afterimage.
    } else if ((a.kfmLatch545 ?? 0) === 0 && (a.fbPhaseSlots[2] ?? 0) > 2) {
      a.fbPhaseSlots[2] = 4;
    }
  }
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x802d5fa0 (walker FUN_80078b0c). Shared shape with v0 tail.
// ----------------------------------------------------------------------------

function action2V1Phase0(a: KfmActor): void {
  a.accumulator80c = KFM.ZERO;
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[1] = 0; a.fbPhaseSlots[2] = 0;
  a.kfmHitCount746 = 0;
  a.handlerTimer = KFM.A2_TIMER_SEED;
  a.kfmLatch54a = 10;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.lockYaw = a.heading;
  } else {
    stepTargetYaw(a, 0x81, 0, true);
    a.lockYaw = a.activeYaw;
  }
  a.hSpeed = KFM.A2_HSPEED_SEED;
  a.hDecel = KFM.STEER_DECAY;
  physicsMove(a, a.lockYaw);
  a.yVel = KFM.ZERO; a.gravityCoeff = KFM.ZERO;
  startStream(a, 0x3, KFM.ACTION2_STREAM_GROUP, 3, KFM.STREAM_RATE);
}

/** FUN_80078c68 — velocity-projection active. Target anchor read TODO(host). */
function action2V1Phase1(a: KfmActor, ctx: StreamContext): void {
  tickStream(a, KFM.STREAM_MASK, ctx);
  a.handlerTimer = a.handlerTimer - a.dt;
  if ((a.fbPhaseSlots[1] ?? 0) === 0) {
    if ((a.kfmHitReact1d9 ?? 0) === 0) {
      if (!hasLock(a)) {
        a.hSpeed = KFM.A2_V1_HSPEED_MULT * rangeRow86c(a) / KFM.A1_V1_ACTIVE_TIMER;
        a.hDecel = KFM.ZERO; a.yVel = KFM.ZERO;
        a.gravityCoeff = gravityRestore(a);
      } else {
        // TODO(host): +0x8e0/+0x8f0/+0x900 anchor projection (chunk_0011.c:1173-1207).
        const t = lockTarget(a)!;
        const mag = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
        let yv = (t.y - a.pos.y) * KFM.A1_V1_PROJ_SCALE;
        if (yv <= 0) {
          if (yv < KFM.A2_V1_YVEL_FLOOR) yv = KFM.A2_V1_YVEL_FLOOR;
          a.gravityCoeff = KFM.ZERO;
        } else {
          if (yv > KFM.A1_V1_NO_TARGET_HSPEED) yv = KFM.A1_V1_NO_TARGET_HSPEED;
          a.gravityCoeff = KFM.A2_GRAVITY_EXIT;
        }
        a.yVel = yv;
        a.hSpeed = mag * KFM.A1_V1_PROJ_SCALE;
        a.hDecel = -a.hSpeed * KFM.A1_V1_HDECEL_SCALE;
        if (mag < KFM.A2_V1_DIST_THRESHOLD) a.fbPhaseSlots[1] = 1;
      }
      stepTargetYaw(a, 0x81, 0, true);
      a.lockYaw = a.activeYaw;
    } else {
      a.fbPhaseSlots[1] = 1;
    }
  }
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar === 0 && a.wallContact !== 0) {
    a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
    a.kfmAirMode6f7 = 0x38;
  }
  if (a.handlerTimer <= KFM.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.fbPhaseSlots[2] = 0;
    a.hDecel = KFM.A2_DRAG;
    a.gravityCoeff = gravityRestore(a);
    if (!a.kfmSolver) a.kfmSolver = {};
    a.kfmSolver.curvature154 = 2160.0;
    a.kfmSolved175 = 0;
  }
}

/** FUN_80078fc8 — v1 ph2 motion-solver + exit (shared shape with v0 ph2). */
function action2V1Phase2(a: KfmActor, ctx: StreamContext): void {
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar !== 2) {
    if (cVar > 1) {
      if (cVar !== 4) {
        if (cVar <= 3 && tickStream(a, KFM.STREAM_MASK, ctx)) {
          a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
        }
      }
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~KFM.ACTION_MODE_BITS;
      if ((a.kfmLatch545 ?? 0) === 0) { romAirKnockoutReturn(a); return; }
      romGroundIdleReturn(a);
      return;
    }
    if (cVar === 0) {
      a.kfmSolver = a.kfmSolver ?? {};
      a.kfmSolver.arc15c = KFM.A1_V2_WINDUP;
      a.hDecel = -(a.hSpeed / KFM.A1_V2_WINDUP);
      a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
    }
  }
  if (a.kfmGround174 === 1) {
    a.kfmLatch545 = 1;
    startStream(a, KFM.STREAM_MASK, KFM.ACTION2_STREAM_GROUP, 4, KFM.STREAM_RATE);
  } else {
    a.kfmLatch545 = 0;
  }
  a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
  integratePhysics(KFM.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  a.kfmGround174 = grounded ? 1 : 0;
  if (grounded) {
    if ((a.fbPhaseSlots[2] ?? 0) < 2 || (a.kfmLatch545 ?? 0) === 1) {
      // afterimage.
    } else if ((a.kfmLatch545 ?? 0) === 0 && (a.fbPhaseSlots[2] ?? 0) > 2) {
      a.fbPhaseSlots[2] = 4;
    }
  }
}

// ============================================================================
// Phase tables. Each variant-table walker clears +0xcc if +0x541 set (action 1) then
// dispatches its table by +0x540.
// ============================================================================

type PhaseFn = (a: KfmActor, ctx: StreamContext) => void;

// Action 0 variant 0 — table @0x804338a0 (walker FUN_80076aa0).
const ACTION0_VARIANT0_TABLE: PhaseFn[] = [
  action0SetupSlot0, action0ActiveGround, action0SetupSlot1, action0ActiveGround,
  action0SetupSlot2, action0ActiveAir, action0SetupSlot1B, action0ActiveV3,
];
// Action 0 variant 1 — table @0x804338a8 (walker FUN_80076cd4).
const ACTION0_VARIANT1_TABLE: PhaseFn[] = [
  action0SetupSlot1, action0ActiveGround, action0SetupSlot2, action0ActiveAir,
  action0SetupSlot1B, action0ActiveV3, action2V0Dispatch, action2V1Dispatch,
];
// Action 0 variant 2 — table @0x804338b0 (walker FUN_80076d64).
const ACTION0_VARIANT2_TABLE: PhaseFn[] = [
  action0SetupSlot2, action0ActiveAir, action0SetupSlot1B, action0ActiveV3,
  action2V0Dispatch, action2V1Dispatch,
];
// Action 0 variant 3 — table @0x804338b8 (walker FUN_80076f78).
const ACTION0_VARIANT3_TABLE: PhaseFn[] = [
  action0SetupSlot1B, action0ActiveV3, action2V0Dispatch, action2V1Dispatch,
];

// Action 1 variant 0 — table @0x802d5f50 (walker FUN_800771c4).
const ACTION1_VARIANT0_TABLE: PhaseFn[] = [
  action1V0Phase0, action1V0Phase1, action1V0Phase2, action1V0Phase3,
  action1V0Phase4, action1V1Phase0, action1V1Phase1, action1V1Phase2,
];
// Action 1 variant 1 — table @0x802d5f64 (walker FUN_80077720).
const ACTION1_VARIANT1_TABLE: PhaseFn[] = [
  action1V1Phase0, action1V1Phase1, action1V1Phase2, action1V1Phase3,
  action1V2Phase0, action1V2Phase1, action1V2Phase2, action1V2Phase3,
];
// Action 1 variant 2 — table @0x802d5f74 (walker FUN_80077a9c).
const ACTION1_VARIANT2_TABLE: PhaseFn[] = [
  action1V2Phase0, action1V2Phase1, action1V2Phase2, action1V2Phase3,
  action1V3Phase0, action1V3Phase1, action1V3Phase2, action1V3Phase3,
];
// Action 1 variant 3 — table @0x802d5f84 (walker FUN_80077e68).
const ACTION1_VARIANT3_TABLE: PhaseFn[] = [
  action1V3Phase0, action1V3Phase1, action1V3Phase2, action1V3Phase3,
  action2V0Phase0, action2V0Phase1, action2V0Phase2, action2V1Phase0,
];

// Action 2 variant 0 — table @0x802d5f94 (walker FUN_8007831c).
const ACTION2_VARIANT0_TABLE: PhaseFn[] = [
  action2V0Phase0, action2V0Phase1, action2V0Phase2, action2V1Phase0,
  action2V1Phase1, action2V1Phase2,
];
// Action 2 variant 1 — table @0x802d5fa0 (walker FUN_80078b0c).
const ACTION2_VARIANT1_TABLE: PhaseFn[] = [
  action2V1Phase0, action2V1Phase1, action2V1Phase2,
];

const ACTION0_TABLES: PhaseFn[][] = [
  ACTION0_VARIANT0_TABLE, ACTION0_VARIANT1_TABLE, ACTION0_VARIANT2_TABLE, ACTION0_VARIANT3_TABLE,
];
const ACTION1_TABLES: PhaseFn[][] = [
  ACTION1_VARIANT0_TABLE, ACTION1_VARIANT1_TABLE, ACTION1_VARIANT2_TABLE, ACTION1_VARIANT3_TABLE,
];
const ACTION2_TABLES: PhaseFn[][] = [
  ACTION2_VARIANT0_TABLE, ACTION2_VARIANT1_TABLE,
];

// Cross-action handoffs: action-0 variant-table tails call the action-2 walkers
// (FUN_8007831c -> PTR_FUN_802d5f94, FUN_80078b0c -> PTR_FUN_802d5fa0).
function action2V0Dispatch(a: KfmActor, ctx: StreamContext): void {
  const phase = a.fbPhaseSlots[0] ?? 0;
  const fn = ACTION2_VARIANT0_TABLE[Math.min(phase, ACTION2_VARIANT0_TABLE.length - 1)];
  if (fn) fn(a, ctx);
}
function action2V1Dispatch(a: KfmActor, ctx: StreamContext): void {
  const phase = a.fbPhaseSlots[0] ?? 0;
  const fn = ACTION2_VARIANT1_TABLE[Math.min(phase, ACTION2_VARIANT1_TABLE.length - 1)];
  if (fn) fn(a, ctx);
}

// ============================================================================
// Root action dispatcher — FUN_800769f0 indexes PTR_FUN_802d5f18[+0x580]. Variant-table
// walker prologues preserved (clear +0xcc if +0x541 set for actions 1/2).
// ============================================================================

export function createKungFuMasterRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    const actionIndex = a.actionIndex;
    const variantIndex = a.variantIndex;
    let table: PhaseFn[] | null = null;
    if (actionIndex === 0) {
      table = ACTION0_TABLES[variantIndex] ?? ACTION0_VARIANT0_TABLE;
    } else if (actionIndex === 1) {
      if ((a.fbPhaseSlots[1] ?? 0) !== 0) {
        (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      }
      table = ACTION1_TABLES[variantIndex] ?? ACTION1_VARIANT0_TABLE;
    } else if (actionIndex === 2) {
      if ((a.fbPhaseSlots[1] ?? 0) === 1) {
        (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      }
      table = ACTION2_TABLES[variantIndex] ?? ACTION2_VARIANT0_TABLE;
    }
    if (!table) return;
    const phase = a.fbPhaseSlots[0] ?? 0;
    const fn = table[phase];
    if (fn) fn(a, ctx);
  };
}

/** Configure a freshly-spawned KUNG-FU MASTER (pl0800). Stamps borgNumber 0x800 and
 *  wires the bespoke action-0 shot-volley + action-1 melee-combo + action-2 dive. */
export function configureKungFuMasterFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = 0x800; // KUNG_FU_MASTER_BORG_NUMBERS.pl0800
  actor.rootAction = createKungFuMasterRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  // TODO(host): FUN_80076880 ctor setup — zz_00765a8_ allocates the KFM satellite
  // objects. The wingman system isn't surfaced on RomActor; bridge wires at spawn.
}

export const KUNG_FU_MASTER_CONSTANTS = KFM;

// ============================================================================
// Self-tests. Mirror rom.selfcheck.ts / gold-hero.ts style.
// ============================================================================

export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

function makeCtx(opts: {
  onAllocateResource?: (slot: number, count: number, mode: number) => boolean;
  onFamilyProjectile?: (addr: number, type: number) => void;
} = {}): StreamContext {
  const ctx: StreamContext = {};
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

export function runKungFuMasterSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // configure: stamps borgNumber 0x800 + wires rootAction.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    assert(a.borgNumber === 0x800, "configure stamps borgNumber 0x800 (KUNG-FU MASTER)");
    assert(a.rootAction !== null, "configure wires rootAction (FUN_800769f0)");
  }

  // ACTION 0 v0 ph0 setup (FUN_80076ad8): zero scalars, advance, +0x548=0.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action0 v0 ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action0 v0 ph0 zeroes velocity scalars (FLOAT_80437848)");
    assert((a.kfmTimer548 ?? 0) === 0, "action0 v0 ph0 +0x548 = 0 (zz_0076c80_)");
    assert((a.kfmComboLatch745 ?? 0) === 0, "action0 v0 ph0 +0x745 = 0");
  }

  // ACTION 0 v0 ph1 (FUN_80076b48): contact op 3 + sub 1 + ammo ok -> spawn 0xc.
  {
    const shots: Shot[] = [];
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 3; a.contactP1 = 1;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === KUNG_FU_MASTER_SHOT_HELPER && shots[0]!.type === 0xc,
      `action0 v0 ph1 contact spawns zz_0082824_(0xc) (got ${JSON.stringify(shots)})`);
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action0 v0 ph1 advances +0x541 to 1 after spawn");
  }

  // ACTION 0 v0 ph1: ammo DENIED -> no spawn; +0x541 still advances.
  {
    const shots: Shot[] = [];
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 3; a.contactP1 = 1;
    root(a);
    assert(shots.length === 0, "action0 v0 ph1 ammo denied suppresses zz_0082824_(0xc)");
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action0 v0 ph1 still advances +0x541 on denied ammo");
  }

  // ACTION 0 v0 ph5 (FUN_80076e00): grounded -> air-return exit.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1);
    a.fbPhaseSlots[0] = 5;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 v0 ph5 grounded -> air-return exit clears +0x73f + strips bits");
  }

  // ACTION 1 v0 ph0 setup (FUN_80077214): +0x548=0x14, +0x544=0->1, range gate.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.hDecel = 3;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.actionSpeedRows = [200, 200, 200];
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action1 v0 ph0 advances +0x540 to 1");
    assert((a.kfmTimer548 ?? 0) === KFM.A1_V0_TIMER_SEED, "action1 v0 ph0 +0x548 = 0x14");
    assert((a.kfmStep544 ?? 0) === 1, "action1 v0 ph0 +0x544 = 0 -> 1");
    assert(a.hSpeed === 0 && a.hDecel === 0, "action1 v0 ph0 zeroes hSpeed/hDecel");
  }

  // ACTION 1 v0 ph0 range-gate fail -> +0x541=1, +0xcc=0.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 9999 };
    a.actionSpeedRows = [200, 200, 200];
    a.heading = 0x1234;
    root(a);
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action1 v0 ph0 range-gate fail -> +0x541 = 1");
    assert((a as RomActor & { lockTarget?: Vec3 | null }).lockTarget === null,
      "action1 v0 ph0 range-gate fail clears +0xcc");
    assert(a.activeYaw === 0x1234, "action1 v0 ph0 range-gate fail +0x5ac = heading");
  }

  // ACTION 1 v0 ph1 windup (FUN_800772fc): timer expiry -> ph2, +0x44=30.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.kfmTimer548 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 v0 ph1 timer expiry -> ph2");
    assert(approxEq(a.hSpeed, KFM.A1_V0_HSPEED), "action1 v0 ph1->ph2 +0x44 = 30.0 (FLOAT_80437858)");
  }

  // ACTION 1 v2 ph0 setup (FUN_80077aec): +0x558=60, +0x6ea=3.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.actionSpeedRows = [200, 200, 200];
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action1 v2 ph0 advances +0x540 to 1");
    assert(approxEq(a.handlerTimer, KFM.A1_V2_WINDUP), "action1 v2 ph0 +0x558 = 60.0 (FLOAT_80437874)");
    assert(a.streamSlot === 3, "action1 v2 ph0 +0x6ea = 3");
  }

  // ACTION 2 v0 ph0 setup (FUN_8007836c): +0x558=40, +0x54a=10, +0x44=8, +0x50=-0.15.
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.variantIndex = 0; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.actionSpeedRows = [200, 200, 200];
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: false }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action2 v0 ph0 advances +0x540 to 1");
    assert(approxEq(a.handlerTimer, KFM.A2_TIMER_SEED), "action2 v0 ph0 +0x558 = 40.0 (FLOAT_80437884)");
    assert((a.kfmLatch54a ?? 0) === 10, "action2 v0 ph0 +0x54a = 10");
    assert(approxEq(a.hSpeed, KFM.A2_HSPEED_SEED), "action2 v0 ph0 +0x44 = 8.0 (FLOAT_8043788c)");
    assert(approxEq(a.gravityCoeff, KFM.A2_GRAVITY), "action2 v0 ph0 +0x50 = -0.15 (FLOAT_80437890)");
  }

  // Root dispatcher: unsupported actionIndex falls through (no-op).
  {
    const a = createRomActor() as KfmActor;
    configureKungFuMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 5;
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action5 falls through (no bespoke handler)");
  }
}
