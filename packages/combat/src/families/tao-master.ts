// TAO MASTER family (ctor 0x800a3b34) — ROM-faithful 1:1 port.
//
// Single borg: pl0801 (TAO MASTER, borgNumber 0x801). Currently UNREGISTERED in
// bridge.ts. Sibling shape to KUNG-FU MASTER (pl0800, ctor 0x80076784 — see
// kung-fu-master.ts); the action-0 shot volley and action-1 melee combo share their
// phase structure, differing only in spawn type (0x7d vs 0xc) and float base.
//
// Source: research/decomp/ghidra-export/chunk_0016.c:626-1987.
// The ctor wires root dispatcher FUN_800a3d10 which indexes
// PTR_FUN_802f7eb8[+0x580 actionIndex]. FUN_800a4570 (chunk_0016.c:887) is the
// action-1 variant dispatch (steerYaw halve + PTR_FUN_802f7ed0[+0x581]).
//
//   action 0 (shot volley): 4 variant tables @0x80433a38 / @0x80433a40 /
//                            @0x80433a48 / @0x80433a50. Chain of [setup, active] pairs
//                            cycling stream group 2 through slots 0/1/2/1
//                            (FUN_800a3f04/3f74/4138/41c8/422c/43dc/4444). Each active
//                            phase ammo-gates zz_006dbe0_(0,1,1) then spawns
//                            zz_0082824_(0x7d). Variants 1/2/3 tail into the action-2
//                            summon walker (FUN_800a5710/5b0c) — cross-action handoff.
//   action 1 (melee combo): 4 variant tables @0x802f7ee8 / @0x802f7efc / @0x802f7f0c /
//                            @0x802f7f1c. Long ground/air combo chain advancing the
//                            stream-slot cursor (+0x544) per hit; variant 3 tails
//                            into the action-2 summon (FUN_800a5760/5864/58c4/5ad8).
//   action 2 (fan summon):  2 variant tables @0x802f7f2c / @0x802f7f3c. Spawns a fan
//                            of child projectiles: contact op 0x04 arms a child slot
//                            (+0x146/+0x14a/+0x156/+0x158 arrays), the +0x5b4 input
//                            bits select the fan direction (0/1/2/3). The child-slot
//                            arrays aren't firstclass on RomActor — ported as scratch
//                            + TODO(host) for the renderer summon resolution.
//
// Float constants read from boot.dol this session (sdata2 @0x80438058..0x804380a8):
//   FLOAT_80438058 = 0.9    steerYaw decay (CONCAT44 double-coercion idiom)
//   DOUBLE_80438060 = (2^52 sentinel; GCC int->double magic, value 0)
//   FLOAT_80438068 = 0.0    zero scalar (velocity/pose resets, thresholds)
//   FLOAT_8043806c = -1.0   zz_004beb8_ stream rate
//   FLOAT_80438070 = 1.0    FUN_80067310 / zz_0067458_ gravity arg
//   FLOAT_80438074 = 7.9    action-0 v3 active hSpeed floor
//   FLOAT_80438078 = 30.0   action-1 v0 windup->active hSpeed seed
//   FLOAT_8043807c = 150.0  action-1 v1 ph1 velocity projection threshold
//   FLOAT_80438080 = 0.5    velocity drag
//   FLOAT_80438084 = 0.95   motion scale (action-2 ph0 velocity drag)
//   FLOAT_80438088 = 200.0  action-1 v1 ph1 slow-damp threshold
//   FLOAT_8043808c = 300.0  action-1 v2 ph1 +0x760 gate
//   FLOAT_80438090 = 3.0    action-1 v1 ph3 afterimage hSpeed threshold
//   FLOAT_80438094 = 60.0   action-1 v2/v3 ph0 +0x558 seed; action-2 exit +0x694 base
//   FLOAT_80438098 = 20.0   action-1 v2 ph1 +0x558 re-seed
//   FLOAT_8043809c = 0.125  action-1 v1 ph2 velocity projection scale
//   FLOAT_804380a0 = 0.03125 action-1 v1 ph2 hDecel scale
//   FLOAT_804380a4 = 40.0   action-1 v1 ph2 hSpeed clamp; action-2 ph0 +0x44 clamp
//   FLOAT_804380a8 = 10.0   action-1 v2 ph3 exit +0x694 seed
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

const TAO_MASTER_BORG_NUMBERS: Record<string, number> = {
  pl0801: 0x801,
};

export type TaoMasterBorgId = keyof typeof TAO_MASTER_BORG_NUMBERS;

// ============================================================================
// Spawner addresses (named const exports per the family-port contract).
// ============================================================================

/** zz_0082824_ @0x80082824 — record-table projectile spawn (TAO MASTER shot, type 0x7d). */
export const TAO_MASTER_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — per-borg effect spawn (reserved; TAO uses only zz_0082824_). */
export const TAO_MASTER_EFFECT_SPAWNER = 0x800c3be0;

// ============================================================================
// Config constants (DOL-read this session; see header for citations).
// ============================================================================

export const TAO = {
  /** FLOAT_80438058 = 0.9 — steerYaw decay factor. */
  STEER_DECAY: 0.9,
  /** FLOAT_80438068 = 0.0 — zero scalar + threshold. */
  ZERO: 0.0,
  /** FLOAT_8043806c = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80438070 = 1.0 — FUN_80067310 / zz_0067458_ gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_80438074 = 7.9 — action-0 v3 active hSpeed floor. */
  A0_V3_HSPEED_FLOOR: 7.9,
  /** FLOAT_80438078 = 30.0 — action-1 v0 windup->active hSpeed seed. */
  A1_V0_HSPEED: 30.0,
  /** FLOAT_8043807c = 150.0 — action-1 v1 ph1 velocity projection threshold. */
  A1_V1_PROJ_THRESHOLD: 150.0,
  /** FLOAT_80438080 = 0.5 — velocity drag. */
  DRAG_HALF: 0.5,
  /** FLOAT_80438084 = 0.95 — motion scale (action-2 ph0 velocity drag). */
  MOTION_SCALE: 0.95,
  /** FLOAT_80438088 = 200.0 — action-1 v1 ph1 slow-damp threshold. */
  A1_V1_SLOW_THRESHOLD: 200.0,
  /** FLOAT_8043808c = 300.0 — action-1 v2 ph1 +0x760 gate. */
  A1_V2_SLOW_THRESHOLD: 300.0,
  /** FLOAT_80438090 = 3.0 — action-1 v1 ph3 afterimage hSpeed threshold. */
  A1_V1_AFTERIMAGE_HSPEED: 3.0,
  /** FLOAT_80438094 = 60.0 — action-1 v2/v3 ph0 +0x558 seed; action-2 exit +0x694 base. */
  A1_V2_WINDUP: 60.0,
  A2_EXIT_TIMER: 60.0,
  /** FLOAT_80438098 = 20.0 — action-1 v2 ph1 +0x558 re-seed. */
  A1_V2_ACTIVE_TIMER: 20.0,
  /** FLOAT_8043809c = 0.125 — action-1 v1 ph2 velocity projection scale. */
  A1_V1_PROJ_SCALE: 0.125,
  /** FLOAT_804380a0 = 0.03125 — action-1 v1 ph2 hDecel scale. */
  A1_V1_HDECEL_SCALE: 0.03125,
  /** FLOAT_804380a4 = 40.0 — action-1 v1 ph2 hSpeed clamp; action-2 ph0 +0x44 clamp. */
  A1_V1_HSPEED_CLAMP: 40.0,
  /** FLOAT_804380a8 = 10.0 — action-1 v2 ph3 exit +0x694 seed. */
  A1_V2_EXIT_TIMER: 10.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5d4 bit 0x40 — B-repress edge (action-0/1 ph active latch). */
  B_REPRESS_EDGE: 0x40,
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
  /** action-2 ph0 +0x548 seed (0x3c = 60 frames). */
  A2_TIMER_SEED: 0x3c,
  /** +0x5b4 fan-direction bit masks (action-2 ph0 reads these to set +0x144). */
  FAN_BIT_BACK: 0x10000,
  FAN_BIT_LEFT: 0x20000,
  FAN_BIT_FORWARD: 0x40000,
  FAN_BIT_RIGHT: 0x80000,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not firstclass on RomActor.
// ============================================================================

export interface TaoMasterScratch {
  /** +0x548 (s16): action-1 windup/active timer (drained each frame). */
  taoTimer548?: number;
  /** +0x544 (s8): action-1 stream-slot / combo-step cursor (++ per advance). */
  taoStep544?: number;
  /** +0x745 (s8): B-repress latch (set on +0x5d4 & 0x40). */
  taoComboLatch745?: number;
  /** +0x746 (s8): action-1 v0 combo hit count. */
  taoHitCount746?: number;
  /** +0x764 (f32): action-1 slow-damp speed scalar. */
  taoSpeedScalar764?: number;
  /** +0x760 (f32): action-1 v1 slow-damp speed scalar. */
  taoSpeedScalar760?: number;
  /** +0x54e (s16): action-1 v1 part-pitch seed (lockYaw snapshot). */
  taoSeed54e?: number;
  /** +0x54a (s16): action-2 ph0 lockYaw snapshot. */
  taoLatch54a?: number;
  /** +0x71c (s8): action-1 v2/v3 ph3 steerYaw-decay gate. */
  taoSteerGate71c?: number;
  /** +0x1d9 (s8): hit-react byte. */
  taoHitReact1d9?: number;
  /** +0x156 (s8): action-2 live child count (fan summon). */
  taoChildCount156?: number;
  /** +0x158 (s32): action-2 max child slots. */
  taoChildMax158?: number;
  /** +0x146[0..N] (s8 array): per-child flag slot (0=free, 1=armed, 2=aimed).
   *  TODO(host): the renderer summon system owns the real slots; surfaced as a
   *  sub-array so a host resolver can drive the fan spawn. */
  taoChildFlags146?: number[];
  /** +0x14a[0..N] (s16 array): per-child yaw (the fan direction). */
  taoChildYaws14a?: number[];
}

type TaoActor = RomActor & TaoMasterScratch;

function scratchOf(actor: RomActor): TaoActor {
  return actor as TaoActor;
}

// ============================================================================
// LockTarget / range helpers.
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

/** FUN_80066838(range, actor) — horizontal-distance range gate. */
function rangeCheck(a: RomActor, range: number): number {
  if (!hasLock(a)) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

function rangeRow868(a: TaoActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? TAO.A1_V0_HSPEED;
}

function rangeRow86c(a: TaoActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? TAO.A1_V2_WINDUP;
}

function rangeRow870(a: TaoActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? TAO.A1_V2_WINDUP;
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
// zz_00a40ac_ (action-0 setup tail) — FUN_800a40ac @ chunk_0016.c:692.
// Advance +0x540, clear +0x541/+0x548/+0x745, aim. Shared by every action-0 setup.
// ============================================================================
function action0SetupTail(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[1] = 0;
  a.taoTimer548 = 0;
  a.taoComboLatch745 = 0;
  stepTargetYaw(a, 0x81, 0, true); // zz_006660c_ + zz_00a6034_(0x81)
}

// ============================================================================
// ACTION 0 — shot volley. 4 variant tables, each a chain of [setup, active] pairs.
// ============================================================================

/** FUN_800a3f04 @ chunk_0016.c:626 (28i) — v0 ph0: zero scalars, stream g=2 slot 0. */
function action0SetupSlot0(a: TaoActor): void {
  a.gravityCoeff = TAO.ZERO;
  a.yVel = TAO.ZERO;
  a.hDecel = TAO.ZERO;
  a.hSpeed = TAO.ZERO;
  a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION0_STREAM_GROUP, 0, TAO.STREAM_RATE);
  action0SetupTail(a);
}

/** FUN_800a4138 @ chunk_0016.c:719 (22i) — stream g=2 slot 1. */
function action0SetupSlot1(a: TaoActor): void {
  a.gravityCoeff = TAO.ZERO;
  a.yVel = TAO.ZERO;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION0_STREAM_GROUP, 1, TAO.STREAM_RATE);
  action0SetupTail(a);
}

/** FUN_800a41c8 @ chunk_0016.c:749 (25i) — stream g=2 slot 2.
 *  variantIndex==2 -> restore gravityCoeff from descriptor.+0x6c. */
function action0SetupSlot2(a: TaoActor): void {
  startStream(a, TAO.STREAM_MASK, TAO.ACTION0_STREAM_GROUP, 2, TAO.STREAM_RATE);
  action0SetupTail(a);
  if (a.variantIndex === 2) {
    a.gravityCoeff = gravityRestore(a);
  }
}

/** FUN_800a43dc @ chunk_0016.c:826 (26i) — stream g=2 slot 1; +0x4c=streamRate; +0x80c=0. */
function action0SetupSlot1B(a: TaoActor): void {
  a.gravityCoeff = TAO.ZERO;
  a.yVel = TAO.ZERO;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION0_STREAM_GROUP, 1, TAO.STREAM_RATE);
  action0SetupTail(a);
  a.hDecel = TAO.STREAM_RATE;
  a.accumulator80c = TAO.ZERO;
}

/** FUN_800a3f74 @ chunk_0016.c:650 (78i) — ground active. Contact->ammo-gate->spawn
 *  zz_0082824_(0x7d); exit branches on +0x541. */
function action0ActiveGround(a: TaoActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & TAO.B_REPRESS_EDGE) !== 0) a.taoComboLatch745 = 1;
  tickStream(a, TAO.STREAM_MASK, ctx);
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  const cVar = a.fbPhaseSlots[1] ?? 0;
  if (cVar === 1) {
    if (a.contactP0 === -1) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 1) {
    if (cVar === 0 && a.contactP0 === 3 && a.contactP1 === 1) {
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(a, TAO_MASTER_SHOT_HELPER, 0x7d);
      }
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 3 && a.wallContact !== 0) {
    romGroundIdleReturn(a);
  }
}

/** FUN_800a422c @ chunk_0016.c:764 (94i) — physics/air active. */
function action0ActiveAir(a: TaoActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & TAO.B_REPRESS_EDGE) !== 0) a.taoComboLatch745 = 1;
  tickStream(a, TAO.STREAM_MASK, ctx);
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  if (grounded) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
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
        ctx.onFamilyProjectile?.(a, TAO_MASTER_SHOT_HELPER, 0x7d);
      }
      a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
    }
  } else if (cVar < 3 && a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
    romAirKnockoutReturn(a);
  }
}

/** FUN_800a4444 @ chunk_0016.c:848 (75i) — v3 active. hSpeed floor clamp (7.9),
 *  contact->spawn, exit on wallContact/contactP0<0. */
function action0ActiveV3(a: TaoActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  tickStream(a, TAO.STREAM_MASK, ctx);
  if (a.hSpeed < TAO.A0_V3_HSPEED_FLOOR) a.hSpeed = TAO.A0_V3_HSPEED_FLOOR;
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  if ((a.fbPhaseSlots[1] ?? 0) === 0 && a.contactP0 === 3 && a.contactP1 === 1) {
    if (allocateWeapon(a, ctx, 0, 1, true)) {
      ctx.onFamilyProjectile?.(a, TAO_MASTER_SHOT_HELPER, 0x7d);
    }
    a.fbPhaseSlots[1] = (a.fbPhaseSlots[1] ?? 0) + 1;
  }
  if (a.wallContact !== 0 || a.contactP0 === -1) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
    if (a.ubCue === 0x2c) romGroundIdleReturn(a);
    else romAirKnockoutReturn(a);
  }
}

// ============================================================================
// ACTION 1 — melee combo. 4 variant tables @0x802f7ee8 / @0x802f7efc / @0x802f7f0c /
// @0x802f7f1c. Each variant-table walker clears +0xcc if +0x541 set.
// ============================================================================

/** FUN_800a4640 @ chunk_0016.c:920 (58i) — v0 ph0 setup. */
function action1V0Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.accumulator80c = TAO.ZERO;
  a.taoTimer548 = TAO.A1_V0_TIMER_SEED;
  a.taoComboLatch745 = 0;
  a.taoHitCount746 = 0;
  a.taoStep544 = 0;
  a.hSpeed = TAO.ZERO;
  a.hDecel = TAO.ZERO;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.activeYaw = a.heading;
  }
  stepTargetYaw(a, 0xc0);
  const step = a.taoStep544 ?? 0;
  a.taoStep544 = step + 1;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, step, TAO.STREAM_RATE);
}

/** FUN_800a4728 @ chunk_0016.c:956 (37i) — v0 ph1 windup. */
function action1V0Phase1(a: TaoActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) tickStream(a, TAO.STREAM_MASK, ctx);
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 1 || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.taoTimer548 = TAO.A1_V0_TIMER_SEED;
    a.hSpeed = TAO.A1_V0_HSPEED;
    a.hDecel = TAO.ZERO;
  }
}

/** FUN_800a47bc @ chunk_0016.c:985 (51i) — v0 ph2 active. */
function action1V0Phase2(a: TaoActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0xc0);
  physicsMove(a, a.lockYaw);
  tickStream(a, TAO.STREAM_MASK, ctx);
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 1 || rangeCheck(a, TAO.A1_V1_PROJ_THRESHOLD) !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.fbPhaseSlots[2] = 0;
    const step = a.taoStep544 ?? 0;
    a.taoStep544 = step + 1;
    startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, step, TAO.STREAM_RATE);
    a.taoHitCount746 = (a.taoHitCount746 ?? 0) + 1;
  }
}

/** FUN_800a4888 @ chunk_0016.c:1016 (98i) — v0 ph3 recover/loop. zz_00a4ea0 tail. */
function action1V0Phase3(a: TaoActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & TAO.B_REPRESS_EDGE) !== 0) a.taoComboLatch745 = 1;
  const cVar = a.fbPhaseSlots[2] ?? 0;
  let uVar = 1;
  if (cVar === 1) { recoverTail(a, ctx, 1); return; }
  if (cVar < 1 && cVar === 0) {
    if (a.contactP0 === -1) {
      uVar = 3;
      if ((a.taoComboLatch745 ?? 0) < 1) {
        if (a.wallContact !== 0) {
          startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 7, TAO.STREAM_RATE);
        }
      } else {
        a.taoComboLatch745 = 0;
        if ((a.taoHitCount746 ?? 0) < 8) {
          if ((a.taoStep544 ?? 0) === 6) a.taoStep544 = 2;
        } else {
          a.fbPhaseSlots[2] = (a.fbPhaseSlots[2] ?? 0) + 1;
          a.taoStep544 = 6;
        }
        const step = a.taoStep544 ?? 0;
        a.taoStep544 = step + 1;
        startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, step, TAO.STREAM_RATE);
        a.taoHitCount746 = (a.taoHitCount746 ?? 0) + 1;
      }
    }
    recoverTail(a, ctx, uVar);
  }
}

/** FUN_800a4a10 @ chunk_0016.c:1075 (9i) — v0 ph4. */
function action1V0Phase4(a: TaoActor, ctx: StreamContext): void {
  recoverTail(a, ctx, 1);
}

// zz_00a4ea0-style recover tail (chunk_0016.c — the action-1 recover shared body).
// Modeled on the KFM zz_0077608_ shape: tick stream, faceGate aim, dashStrength clear,
// slow-damp drag, physics-move, wall-contact exit.
function recoverTail(a: TaoActor, ctx: StreamContext, param: number): void {
  if ((param & 1) !== 0) tickStream(a, TAO.STREAM_MASK, ctx);
  if (a.faceGate1d10 !== 0) stepTargetYaw(a, 0xc0);
  if (a.dashStrength1d0f !== 0) {
    a.dashStrength1d0f = 0;
    a.taoTimer548 = TAO.A1_V0_TIMER_SEED;
    a.hSpeed = TAO.A1_V0_HSPEED;
    a.hDecel = TAO.ZERO;
  }
  if (TAO.A1_V1_SLOW_THRESHOLD <= (a.taoSpeedScalar764 ?? 0)) {
    a.hSpeed *= TAO.MOTION_SCALE;
  } else {
    a.hSpeed *= TAO.DRAG_HALF;
  }
  if ((a.taoHitReact1d9 ?? 0) !== 0) a.hSpeed *= TAO.DRAG_HALF;
  physicsMove(a, a.lockYaw);
  if ((param & 2) === 0 && a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
    romGroundIdleReturn(a);
  }
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x802f7efc (walker FUN_800a4b9c-phases). Flight/dash melee.
//   ph2 FUN_800a5058 velocity-projection reads part anchor +0x8e0/+0x8f0/+0x900;
//   TODO(host) for anchor resolution; structure + drain + advance ported faithful.
// ----------------------------------------------------------------------------

function action1V1Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.taoSeed54e = a.lockYaw;
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
    a.activeYaw = a.lockYaw;
    if ((a.controlWord & 0x20) !== 0) a.activeYaw = a.lockYaw;
  }
  a.taoTimer548 = TAO.A1_V1_TIMER_SEED;
  stepTargetYaw(a, 0xc0);
  startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 10, TAO.STREAM_RATE);
  a.accumulator80c = TAO.ZERO;
}

function action1V1Phase1(a: TaoActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) tickStream(a, TAO.STREAM_MASK, ctx);
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 1 || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.taoTimer548 = TAO.A1_V1_ACTIVE_RESEED;
    const row = rangeRow868(a);
    const src = hasLock(a) && row < (a.taoSpeedScalar764 ?? 0) ? (a.taoSpeedScalar764 ?? 0) : row;
    a.hSpeed = src / TAO.A1_V0_HSPEED;
    a.hDecel = TAO.ZERO;
  }
}

function action1V1Phase2(a: TaoActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0xc0);
  physicsMove(a, a.lockYaw);
  tickStream(a, TAO.STREAM_MASK, ctx);
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 1 || rangeCheck(a, TAO.A1_V1_SLOW_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 10, TAO.STREAM_RATE);
  }
}

function action1V1Phase3(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  stepTargetYaw(a, 0xc0);
  a.hSpeed *= TAO.STEER_DECAY;
  physicsMove(a, a.lockYaw);
  if (a.wallContact !== 0) {
    a.streamCounter6eb = 0;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
    romGroundIdleReturn(a);
  }
  if (a.hSpeed > TAO.A1_V1_AFTERIMAGE_HSPEED) {
    // zz_00b22f4_(actor) — afterimage (host hook).
  }
}

// ----------------------------------------------------------------------------
// Variant 2 — table @0x802f7f0c (walker FUN_800a4f18-phases). Lunge melee.
// ----------------------------------------------------------------------------

function action1V2Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  if (rangeCheck(a, rangeRow86c(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
  }
  a.handlerTimer = TAO.A1_V2_WINDUP;
  a.streamSlot = 3;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 8, TAO.STREAM_RATE);
}

function action1V2Phase1(a: TaoActor, _ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  const t = a.handlerTimer - TAO.PHYSICS_GRAVITY;
  a.handlerTimer = t;
  if (t <= TAO.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.handlerTimer = TAO.A1_V2_SLOW_THRESHOLD; // FLOAT_8043808c = 300.0 (re-seed)
    if (TAO.A1_V2_SLOW_THRESHOLD < (a.taoSpeedScalar760 ?? 0)) {
      // zz_0092dcc_(actor, 0) — host hook.
    }
  }
}

/** FUN_800a5058 — velocity-projection active. Target anchor read TODO(host). */
function action1V2Phase2(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  if (!hasLock(a)) {
    a.hSpeed = TAO.A1_V1_HSPEED_CLAMP;
    a.hDecel = TAO.ZERO; a.yVel = TAO.ZERO;
    a.gravityCoeff = gravityRestore(a);
  } else {
    // TODO(host): +0x8e0/+0x8f0/+0x900 part-anchor projection (chunk_0016.c:1349-1365).
    const t = lockTarget(a)!;
    const mag = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    a.hSpeed = mag * TAO.A1_V1_PROJ_SCALE;
    a.hDecel = -a.hSpeed * TAO.A1_V1_HDECEL_SCALE;
    a.yVel = (t.y - a.pos.y) * TAO.A1_V1_PROJ_SCALE;
    a.gravityCoeff = TAO.ZERO;
  }
  stepTargetYaw(a, 0x81, 0, true);
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  groundSnapRevert(a);
  if ((a.taoHitReact1d9 ?? 0) === 0) {
    a.handlerTimer = a.handlerTimer - a.dt;
  }
  if (a.handlerTimer <= TAO.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 9, TAO.STREAM_RATE);
  }
}

function action1V2Phase3(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  if ((a.taoSteerGate71c ?? 0) === 0) {
    integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
    if (a.hSpeed < TAO.ZERO) { a.hSpeed = TAO.ZERO; a.hDecel = TAO.ZERO; }
    groundSnapRevert(a);
    if (a.wallContact !== 0) {
      a.stateTimer = TAO.A1_V2_EXIT_TIMER + a.dt;
      romAirKnockoutReturn(a);
    }
  }
}

// ----------------------------------------------------------------------------
// Variant 3 — table @0x802f7f1c (walker FUN_800a52e4-phases). Extended lunge.
//   ph2 FUN_800a544c uses FUN_800452a0 steerYaw clamp (aim solver) — TODO(host).
// ----------------------------------------------------------------------------

function action1V3Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[1] = 0;
  a.fbPhaseSlots[2] = 0;
  if (rangeCheck(a, rangeRow870(a)) < 1) {
    a.fbPhaseSlots[1] = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
  }
  a.handlerTimer = TAO.A1_V2_WINDUP;
  a.streamSlot = 3;
  startStream(a, TAO.STREAM_MASK, TAO.ACTION1_STREAM_GROUP, 0xb, TAO.STREAM_RATE);
}

function action1V3Phase1(a: TaoActor, _ctx: StreamContext): void {
  stepTargetYaw(a, 0x81, 0, true);
  const t = a.handlerTimer - TAO.PHYSICS_GRAVITY;
  a.handlerTimer = t;
  if (t <= TAO.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.handlerTimer = TAO.A1_V2_ACTIVE_TIMER;
    if (a.hSpeed < TAO.A1_V0_HSPEED) a.hSpeed = TAO.A1_V2_WINDUP;
    a.hDecel = TAO.STEER_DECAY;
  }
}

function action1V3Phase2(a: TaoActor, ctx: StreamContext): void {
  const cVar = a.fbPhaseSlots[2] ?? 0;
  if (cVar === 1) {
    integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  } else if (cVar < 1 && cVar === 0) {
    if ((a.fbPhaseSlots[1] ?? 0) === 0) {
      stepTargetYaw(a, 0x81, 0, true);
      a.lockYaw = a.activeYaw;
      if (hasLock(a)) {
        // TODO(host): +0x8e0/+0x8f0/+0x900 anchor projection into +0x48.
        a.yVel = (lockTarget(a)!.y - a.pos.y) * TAO.A1_V1_PROJ_SCALE;
        a.gravityCoeff = TAO.ZERO;
      }
      if (rangeCheck(a, TAO.A1_V2_WINDUP) !== 0) a.fbPhaseSlots[1] = 1;
    }
    // TODO(host): FUN_800452a0(yVel, hSpeed) -> steerYaw clamp +/-0x38e (aim solver).
  }
  tickStream(a, TAO.STREAM_MASK, ctx);
  if (TAO.A1_V1_HSPEED_CLAMP < a.hSpeed) {
    a.hSpeed = TAO.A1_V1_HSPEED_CLAMP;
    a.hDecel = TAO.ZERO;
  }
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
  const grounded = groundSnapRevert(a);
  if (grounded && (a.fbPhaseSlots[2] ?? 0) === 0) {
    a.steerYaw = 0; a.yVel = TAO.ZERO; a.gravityCoeff = TAO.ZERO;
    a.fbPhaseSlots[1] = 1;
  }
  a.handlerTimer = a.handlerTimer - a.dt;
  if (a.handlerTimer <= TAO.ZERO) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  }
}

function action1V3Phase3(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  if ((a.taoSteerGate71c ?? 0) === 0) {
    integratePhysics(TAO.PHYSICS_GRAVITY, a, a.lockYaw);
    groundSnapRevert(a);
    if (a.wallContact !== 0) {
      a.steerYaw = 0;
      a.stateTimer = TAO.A1_V2_EXIT_TIMER + a.dt;
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
  }
}

// ============================================================================
// ACTION 2 — fan summon. 2 variant tables @0x802f7f2c / @0x802f7f3c. Spawns a fan of
// child projectiles: contact op 0x04 arms a child slot (+0x146/+0x14a/+0x156/+0x158
// arrays), the +0x5b4 input bits select the fan direction (0=back,1=left,2=right,3=fwd).
// The child-slot arrays aren't firstclass on RomActor — ported as scratch + TODO(host).
// ============================================================================

/** FUN_800a5760 @ chunk_0016.c:1617 (65i) — v0 ph0 setup. +0x548=0x3c, range gate,
 *  +0x544 fan-direction select from +0x5b4 bits, stream arm slot 0. */
function action2V0Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.taoTimer548 = TAO.A2_TIMER_SEED;
  a.hSpeed = TAO.ZERO;
  a.hDecel = TAO.ZERO;
  if (!hasLock(a)) {
    a.taoStep544 = 1;             // +0x544 = 1 (no-target flag)
    a.activeYaw = a.heading;      // +0x5ac = +0x72
  } else {
    a.taoStep544 = 0;             // +0x544 = 0
  }
  stepTargetYaw(a, 0xc0);
  startStream(a, TAO.STREAM_MASK, TAO.ACTION2_STREAM_GROUP, 0, TAO.STREAM_RATE);
  // Fan-direction selector from +0x5b4 input bits (chunk_0016.c:1637-1659).
  if ((a.taoChildCount156 ?? 0) > 0) {
    const bits = a.statusWord5b4 ?? 0;
    let dir = 3;
    if ((bits & TAO.FAN_BIT_BACK) !== 0) dir = 1;
    else if ((bits & TAO.FAN_BIT_LEFT) !== 0) dir = 2;
    else if ((bits & TAO.FAN_BIT_FORWARD) !== 0) dir = 3;
    else if ((bits & TAO.FAN_BIT_RIGHT) !== 0) dir = 0;
    a.childMask144 = dir; // +0x144 = fan direction
  }
}

/** FUN_800a5864 @ chunk_0016.c:1668 (24i) — v0 ph1 windup. Drain +0x548; on
 *  expiry/aim -> advance. */
function action2V0Phase1(a: TaoActor, _ctx: StreamContext): void {
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 1 || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.fbPhaseSlots[1] = 0; // +0x541 = 0
  }
}

/** FUN_800a58c4 @ chunk_0016.c:1687 (133i) — v0 ph2 active. Contact op 0x04 arms a
 *  child slot; op sub 0x03 spawns (ammo-gate zz_006dbe0_(2,1,1)); sub 0x02 aims the
 *  fan yaw per +0x144. Child-slot arrays ported as scratch; renderer summon TODO(host). */
function action2V0Phase2(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  const op = a.contactP0;
  const sub = a.contactP1;
  if (op === 4 && sub === 3) {
    a.contactP0 = 0; a.contactP1 = 0;
    // Arm a free child slot: ammo-gate weapon cell 2.
    if ((a.taoChildCount156 ?? 0) > 0 && allocateWeapon(a, ctx, 2, 1, true)) {
      const flags = a.taoChildFlags146 ?? [];
      const max = a.taoChildMax158 ?? 0;
      for (let i = 0; i < max && i < flags.length; i++) {
        if (flags[i] === 0) { flags[i] = 1; a.taoChildCount156 = (a.taoChildCount156 ?? 0) - 1; break; }
      }
      a.taoChildFlags146 = flags;
    }
  } else if (op === 4 && sub === 2) {
    a.contactP0 = 0; a.contactP1 = 0;
    // Aim a child slot: set its fan yaw from +0x144 direction.
    const flags = a.taoChildFlags146 ?? [];
    const yaws = a.taoChildYaws14a ?? [];
    const max = a.taoChildMax158 ?? 0;
    let aimed = false;
    for (let i = 0; i < max && i < flags.length; i++) {
      if (flags[i] === 1) {
        flags[i] = 2;
        const dir = a.childMask144 ?? 0;
        if (dir === 0) yaws[i] = (a.heading - 0x8000) & 0xffff;       // back
        else if (dir === 1) yaws[i] = (a.heading - 0x4000) & 0xffff;  // left
        else if (dir === 2) yaws[i] = (a.heading + 0x4000) & 0xffff;  // right
        else yaws[i] = a.heading;                                      // forward
        aimed = true;
        // TODO(host): spawn the fan child via ctx.onFamilyProjectile once the
        // renderer summon system resolves the child slot -> projectile mapping.
        break;
      }
    }
    a.taoChildFlags146 = flags;
    a.taoChildYaws14a = yaws;
    if (!aimed) {
      // zz_004cff4_(actor, 0xf) x2 — stream clear (host hook).
    }
  } else if (op === -1) {
    a.contactP0 = 0;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
  }
  if (a.wallContact === 1) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  }
}

/** FUN_800a5ad8 @ chunk_0016.c:1757 (13i) — v0 ph3 exit. Ground idle return. */
function action2V0Phase3(a: TaoActor): void {
  a.housekeeping73f = 0;
  a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
  romGroundIdleReturn(a);
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x802f7f3c (walker FUN_800a5b0c). Shared summon shape with v0.
// ----------------------------------------------------------------------------

/** FUN_800a5b5c @ chunk_0016.c:1784 (83i) — v1 ph0 setup. +0x548=0x3c, +0x54a=lockYaw,
 *  velocity drag x0.95, physics, stream arm slot 1, fan-direction select. */
function action2V1Phase0(a: TaoActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  a.fbPhaseSlots[2] = 0;
  a.taoTimer548 = TAO.A2_TIMER_SEED;
  a.taoLatch54a = a.lockYaw;
  if (!hasLock(a)) {
    a.fbPhaseSlots[1] = 1;
    a.activeYaw = a.heading;
  } else {
    a.fbPhaseSlots[1] = 0;
  }
  stepTargetYaw(a, 0xc1);
  a.hSpeed *= TAO.MOTION_SCALE;
  a.hDecel *= TAO.MOTION_SCALE;
  a.yVel *= TAO.MOTION_SCALE;
  a.gravityCoeff = TAO.ZERO;
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.taoLatch54a ?? a.lockYaw);
  groundSnapRevert(a);
  startStream(a, TAO.STREAM_MASK, TAO.ACTION2_STREAM_GROUP, 1, TAO.STREAM_RATE);
  if ((a.taoChildCount156 ?? 0) > 0) {
    const bits = a.statusWord5b4 ?? 0;
    let dir = 3;
    if ((bits & TAO.FAN_BIT_BACK) !== 0) dir = 1;
    else if ((bits & TAO.FAN_BIT_LEFT) !== 0) dir = 2;
    else if ((bits & TAO.FAN_BIT_FORWARD) !== 0) dir = 3;
    else if ((bits & TAO.FAN_BIT_RIGHT) !== 0) dir = 0;
    a.childMask144 = dir;
  }
}

/** FUN_800a5ca8 @ chunk_0016.c:1845 (38i) — v1 ph1 windup. Drag x0.9, physics, drain
 *  +0x548; on expiry/aim -> advance. */
function action2V1Phase1(a: TaoActor, _ctx: StreamContext): void {
  a.hSpeed *= TAO.STEER_DECAY;
  a.hDecel *= TAO.STEER_DECAY;
  a.yVel *= TAO.STEER_DECAY;
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.taoLatch54a ?? a.lockYaw);
  groundSnapRevert(a);
  const t = (a.taoTimer548 ?? 0) - 1;
  a.taoTimer548 = t;
  if (t < 0 || stepTargetYaw(a, 0xc1)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  }
}

/** FUN_800a5d40 @ chunk_0016.c:1872 (169i) — v1 ph2 active. Same contact-op fan-arm
 *  shape as v0 ph2 (chunk_0016.c:1885-1947); +0x542 contact-arm + steerYaw decay +
 *  exit on wallContact -> air-return +0x694 = 60+dt. */
function action2V1Phase2(a: TaoActor, ctx: StreamContext): void {
  tickStream(a, TAO.STREAM_MASK, ctx);
  const op = a.contactP0;
  const sub = a.contactP1;
  if (op === 4 && sub === 3) {
    a.contactP0 = 0; a.contactP1 = 0;
    if ((a.taoChildCount156 ?? 0) > 0 && allocateWeapon(a, ctx, 2, 1, true)) {
      const flags = a.taoChildFlags146 ?? [];
      const max = a.taoChildMax158 ?? 0;
      for (let i = 0; i < max && i < flags.length; i++) {
        if (flags[i] === 0) { flags[i] = 1; a.taoChildCount156 = (a.taoChildCount156 ?? 0) - 1; break; }
      }
      a.taoChildFlags146 = flags;
    }
  } else if (op === 4 && sub === 2) {
    a.contactP0 = 0; a.contactP1 = 0;
    const flags = a.taoChildFlags146 ?? [];
    const yaws = a.taoChildYaws14a ?? [];
    const max = a.taoChildMax158 ?? 0;
    let aimed = false;
    for (let i = 0; i < max && i < flags.length; i++) {
      if (flags[i] === 1) {
        flags[i] = 2;
        const dir = a.childMask144 ?? 0;
        if (dir === 0) yaws[i] = (a.heading - 0x8000) & 0xffff;
        else if (dir === 1) yaws[i] = (a.heading - 0x4000) & 0xffff;
        else if (dir === 2) yaws[i] = (a.heading + 0x4000) & 0xffff;
        else yaws[i] = a.heading;
        aimed = true;
        break;
      }
    }
    a.taoChildFlags146 = flags;
    a.taoChildYaws14a = yaws;
    if (!aimed) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
      a.hDecel = TAO.ZERO; a.hSpeed = TAO.ZERO;
      a.steerYaw = 0;
      romAirKnockoutReturn(a);
      a.stateTimer = TAO.A2_EXIT_TIMER + a.dt;
      return;
    }
  } else if (op === -1) {
    a.contactP0 = 0;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~TAO.ACTION_MODE_BITS;
  }
  stepTargetYaw(a, 0xc1);
  if ((a.fbPhaseSlots[2] ?? 0) === 1) {
    // zz_006e1ac_(actor, 0xc1, 1) — part pitch aim (host renderer hook).
  }
  a.hSpeed *= TAO.STEER_DECAY;
  a.hDecel *= TAO.STEER_DECAY;
  a.yVel *= TAO.STEER_DECAY;
  integratePhysics(TAO.PHYSICS_GRAVITY, a, a.taoLatch54a ?? a.lockYaw);
  groundSnapRevert(a);
  if (a.wallContact !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
    a.gravityCoeff = gravityRestore(a);
  }
}

/** FUN_800a5fe4 @ chunk_0016.c:1975 (20i) — v1 ph3 exit. Air return +0x694 = 60+dt. */
function action2V1Phase3(a: TaoActor): void {
  a.hDecel = TAO.ZERO;
  a.hSpeed = TAO.ZERO;
  a.steerYaw = 0;
  romAirKnockoutReturn(a);
  a.stateTimer = TAO.A2_EXIT_TIMER + a.dt;
}

// ============================================================================
// Phase tables.
// ============================================================================

type PhaseFn = (a: TaoActor, ctx: StreamContext) => void;

// Action 0 variant 0 — table @0x80433a38 (walker FUN_800a3ea8).
const ACTION0_VARIANT0_TABLE: PhaseFn[] = [
  action0SetupSlot0, action0ActiveGround, action0SetupSlot1, action0ActiveGround,
  action0SetupSlot2, action0ActiveAir, action0SetupSlot1B, action0ActiveV3,
];
// Action 0 variant 1 — table @0x80433a40 (walker FUN_800a4100).
const ACTION0_VARIANT1_TABLE: PhaseFn[] = [
  action0SetupSlot1, action0ActiveGround, action0SetupSlot2, action0ActiveAir,
  action0SetupSlot1B, action0ActiveV3, action2V0Dispatch, action2V1Dispatch,
];
// Action 0 variant 2 — table @0x80433a48 (walker FUN_800a4190).
const ACTION0_VARIANT2_TABLE: PhaseFn[] = [
  action0SetupSlot2, action0ActiveAir, action0SetupSlot1B, action0ActiveV3,
  action2V0Dispatch, action2V1Dispatch,
];
// Action 0 variant 3 — table @0x80433a50 (walker FUN_800a43a4).
const ACTION0_VARIANT3_TABLE: PhaseFn[] = [
  action0SetupSlot1B, action0ActiveV3, action2V0Dispatch, action2V1Dispatch,
];

// Action 1 variant 0 — table @0x802f7ee8 (walker FUN_800a45f0).
const ACTION1_VARIANT0_TABLE: PhaseFn[] = [
  action1V0Phase0, action1V0Phase1, action1V0Phase2, action1V0Phase3,
  action1V0Phase4, action1V1Phase0, action1V1Phase1, action1V1Phase2,
];
// Action 1 variant 1 — table @0x802f7efc (walker FUN_800a4ec8).
const ACTION1_VARIANT1_TABLE: PhaseFn[] = [
  action1V1Phase0, action1V1Phase1, action1V1Phase2, action1V1Phase3,
  action1V2Phase0, action1V2Phase1, action1V2Phase2, action1V2Phase3,
];
// Action 1 variant 2 — table @0x802f7f0c (walker FUN_800a5294).
const ACTION1_VARIANT2_TABLE: PhaseFn[] = [
  action1V2Phase0, action1V2Phase1, action1V2Phase2, action1V2Phase3,
  action1V3Phase0, action1V3Phase1, action1V3Phase2, action1V3Phase3,
];
// Action 1 variant 3 — table @0x802f7f1c (walker FUN_800a52e4-walker).
const ACTION1_VARIANT3_TABLE: PhaseFn[] = [
  action1V3Phase0, action1V3Phase1, action1V3Phase2, action1V3Phase3,
  action2V0Phase0, action2V0Phase1, action2V0Phase2, action2V0Phase3,
];

// Action 2 variant 0 — table @0x802f7f2c (walker FUN_800a5710).
const ACTION2_VARIANT0_TABLE: PhaseFn[] = [
  action2V0Phase0, action2V0Phase1, action2V0Phase2, action2V0Phase3,
  action2V1Phase0, action2V1Phase1, action2V1Phase2, action2V1Phase3,
];
// Action 2 variant 1 — table @0x802f7f3c (walker FUN_800a5b0c).
const ACTION2_VARIANT1_TABLE: PhaseFn[] = [
  action2V1Phase0, action2V1Phase1, action2V1Phase2, action2V1Phase3,
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
// (FUN_800a5710 -> PTR_FUN_802f7f2c, FUN_800a5b0c -> PTR_FUN_802f7f3c).
function action2V0Dispatch(a: TaoActor, ctx: StreamContext): void {
  const phase = a.fbPhaseSlots[0] ?? 0;
  const fn = ACTION2_VARIANT0_TABLE[Math.min(phase, ACTION2_VARIANT0_TABLE.length - 1)];
  if (fn) fn(a, ctx);
}
function action2V1Dispatch(a: TaoActor, ctx: StreamContext): void {
  const phase = a.fbPhaseSlots[0] ?? 0;
  const fn = ACTION2_VARIANT1_TABLE[Math.min(phase, ACTION2_VARIANT1_TABLE.length - 1)];
  if (fn) fn(a, ctx);
}

// ============================================================================
// Root action dispatcher — FUN_800a3d10 indexes PTR_FUN_802f7eb8[+0x580]. Variant-table
// walker prologues preserved (clear +0xcc if +0x541 set for actions 1/2).
// ============================================================================

export function createTaoMasterRootAction(
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

/** Configure a freshly-spawned TAO MASTER (pl0801). Stamps borgNumber 0x801 and wires
 *  the bespoke action-0 shot-volley + action-1 melee-combo + action-2 fan-summon. */
export function configureTaoMasterFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = 0x801; // TAO_MASTER_BORG_NUMBERS.pl0801
  actor.rootAction = createTaoMasterRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  // TODO(host): FUN_800a3c00 ctor setup — satellite/summon object allocation. The
  // summon system isn't surfaced on RomActor; bridge wires at spawn.
}

export const TAO_MASTER_CONSTANTS = TAO;

// ============================================================================
// Self-tests. Mirror rom.selfcheck.ts / kung-fu-master.ts style.
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

export function runTaoMasterSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // configure: stamps borgNumber 0x801 + wires rootAction.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    assert(a.borgNumber === 0x801, "configure stamps borgNumber 0x801 (TAO MASTER)");
    assert(a.rootAction !== null, "configure wires rootAction (FUN_800a3d10)");
  }

  // ACTION 0 v0 ph0 setup (FUN_800a3f04): zero scalars, advance, +0x548=0.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action0 v0 ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action0 v0 ph0 zeroes velocity scalars (FLOAT_80438068)");
    assert((a.taoTimer548 ?? 0) === 0, "action0 v0 ph0 +0x548 = 0 (zz_00a40ac_)");
  }

  // ACTION 0 v0 ph1 (FUN_800a3f74): contact op 3 + sub 1 + ammo ok -> spawn 0x7d.
  {
    const shots: Shot[] = [];
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 3; a.contactP1 = 1;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === TAO_MASTER_SHOT_HELPER && shots[0]!.type === 0x7d,
      `action0 v0 ph1 contact spawns zz_0082824_(0x7d) (got ${JSON.stringify(shots)})`);
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action0 v0 ph1 advances +0x541 to 1 after spawn");
  }

  // ACTION 0 v0 ph1: ammo DENIED -> no spawn; +0x541 still advances.
  {
    const shots: Shot[] = [];
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 3; a.contactP1 = 1;
    root(a);
    assert(shots.length === 0, "action0 v0 ph1 ammo denied suppresses zz_0082824_(0x7d)");
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action0 v0 ph1 still advances +0x541 on denied ammo");
  }

  // ACTION 0 v0 ph5 (FUN_800a422c): grounded -> air-return exit.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
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

  // ACTION 1 v0 ph0 setup (FUN_800a4640): +0x548=0x14, +0x544=0->1, range gate.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.hDecel = 3;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.actionSpeedRows = [200, 200, 200];
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action1 v0 ph0 advances +0x540 to 1");
    assert((a.taoTimer548 ?? 0) === TAO.A1_V0_TIMER_SEED, "action1 v0 ph0 +0x548 = 0x14");
    assert((a.taoStep544 ?? 0) === 1, "action1 v0 ph0 +0x544 = 0 -> 1");
    assert(a.hSpeed === 0 && a.hDecel === 0, "action1 v0 ph0 zeroes hSpeed/hDecel");
  }

  // ACTION 1 v0 ph0 range-gate fail -> +0x541=1, +0xcc=0.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
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

  // ACTION 1 v0 ph1 windup (FUN_800a4728): timer expiry -> ph2, +0x44=30.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.taoTimer548 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 v0 ph1 timer expiry -> ph2");
    assert(approxEq(a.hSpeed, TAO.A1_V0_HSPEED), "action1 v0 ph1->ph2 +0x44 = 30.0 (FLOAT_80438078)");
  }

  // ACTION 1 v2 ph0 setup (FUN_800a4f18): +0x558=60, +0x6ea=3.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.actionSpeedRows = [200, 200, 200];
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action1 v2 ph0 advances +0x540 to 1");
    assert(approxEq(a.handlerTimer, TAO.A1_V2_WINDUP), "action1 v2 ph0 +0x558 = 60.0 (FLOAT_80438094)");
    assert(a.streamSlot === 3, "action1 v2 ph0 +0x6ea = 3");
  }

  // ACTION 2 v0 ph0 setup (FUN_800a5760): +0x548=0x3c, fan-direction select from bits.
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.variantIndex = 0; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 };
    a.taoChildCount156 = 2;
    a.statusWord5b4 = TAO.FAN_BIT_RIGHT; // dir 0 (back)
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action2 v0 ph0 advances +0x540 to 1");
    assert((a.taoTimer548 ?? 0) === TAO.A2_TIMER_SEED, "action2 v0 ph0 +0x548 = 0x3c");
    assert(a.childMask144 === 0, "action2 v0 ph0 +0x144 = 0 (FAN_BIT_RIGHT -> back dir)");
  }

  // Root dispatcher: unsupported actionIndex falls through (no-op).
  {
    const a = createRomActor() as TaoActor;
    configureTaoMasterFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 5;
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action5 falls through (no bespoke handler)");
  }
}
