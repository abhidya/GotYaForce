// GOLD HERO family (ctor 0x8013c714) — ROM-faithful 1:1 port.
//
// Single borg: pl0802 (GOLD HERO, borgNumber 0x802). The decomp also branches on
// 0x803 (an un-named sibling morph form reached via the FUN_8013ecec / FUN_8013eba4
// morph pair); that branch is preserved inside the shared spawner but pl0802 is the
// only registered borg in scope.
//
// Source: research/decomp/ghidra-export/chunk_0036.c:3394-4988 + chunk_0037.c:1-430.
//   rootAction   = FUN_8013cb40 → PTR_FUN_8033993c[+0x580 actionIndex]
//   action 0     = variant-router → 3 phase tables indexed by +0x581 variantIndex
//                  @0x803399f8 (walker FUN_8013cc08), @0x80339a04 (FUN_8013cfd8),
//                  @0x80339a10 (FUN_8013d398). Each table is 8 phase slots.
//   action 1     = FUN_8013d7bc → PTR_FUN_80339a1c[+0x581] → 4 phase tables
//                  @0x80339a30 (FUN_8013d7f8), @0x80339a70 (FUN_8013e1d8),
//                  @0x80339a60 (FUN_8013dcec), @0x80339a80 (FUN_8013e578).
//   upperBody    = FUN_8013cb7c → halves +0x1900/+0x18da/+0x18e0 then
//                  PTR_FUN_803399e4[+0x581]. Not invoked during state-61 attack; wired
//                  for fidelity.
//
// ACTION 0 (dash/blast loop): variant-tuned beam/shot cycle. Variant 0 phases
//   cc50/cd30/ce30 — setup → active (contact→FUN_8013d600 spawn) → cooldown/exit.
//   Variant 1 (d014/d0bc/d190) swaps the stream group to 1 and gates on zz_006dee8_
//   aim. Variant 2 (d3e0/d4b4/d190) runs physics during the active phase.
//
// ACTION 1 (melee combo): 4 variant tables encoding ground/air/lunge/recover melee
//   chains. Variant 0 (d860/d940/d9e0/da94/db28) is the ground combo: setup → windup
//   → active → active2 → recover (with B-retap re-arm looping back).
//
// FUN_8013d600 (the GOLD HERO shot spawn): borg-switched ammo-gated single shot.
//   0x802 → zz_0082824_(0x2d); 0x803 → zz_00c3be0_(0x22). Each call decrements +0x6ef.
//
// Float constants read from boot.dol this session (sdata2 @0x8043a0f8..0x8043a148):
//   FLOAT_8043a0f8 = 0.0    zero scalar / threshold
//   FLOAT_8043a0fc = 1.0    FUN_80067310 gravity arg; air-return bit clear arg
//   FLOAT_8043a110 = -1.0   zz_004beb8_ stream rate
//   FLOAT_8043a114 = 0.95   blink + per-frame motion scale; velocity drag (action-1 ph2)
//   FLOAT_8043a118 = 3.0    afterimage distance threshold (zz_00b22f4_)
//   FLOAT_8043a11c = 20.0   windup/active +0x558 seed (the ubiquitous timer)
//   FLOAT_8043a120 = 30.0   action-1 +0x44 hSpeed seed
//   FLOAT_8043a124 = 150.0  action-1 ph1 +0x764 slow-damp threshold; range gate
//   FLOAT_8043a128 = 0.5    velocity drag (zz_006ed8c_ arg, slow-damp)
//   FLOAT_8043a12c = 60.0   action-1 variant-2 ph0 +0x558 seed (lunge windup)
//   FLOAT_8043a130 = 400.0  action-1 active range-check threshold (FUN_80066838)
//   FLOAT_8043a134 = 16.0   action-1 ph2 +0x558 re-seed (active2 timer)
//   FLOAT_8043a138 = 0.9    steerYaw decay (zz_006ed8c_ arg)
//   FLOAT_8043a13c = 0.99   velocity drag (action-1 ph0 residual)
//   FLOAT_8043a140 = 8.0    action-1 exit +0x694 state-timer seed base
//   FLOAT_8043a144 = 200.0  action-1 variant-1 ph1 +0x764 threshold
//   FLOAT_8043a148 = 0.1    action-1 variant-3 ph0 speed multiplier (FLOAT_8043a148)
//
// Exit helpers zz_006a474_ (romGroundIdleReturn), zz_006a5a4_ (romAirKnockoutReturn)
// are ported in shared-idle-return.ts; zz_006a668_ / zz_006a3d0_ are command-record
// re-dispatches modeled here as controlWord strips + cue dispatches.

import { createRomActor, type RomActor, type Vec3 } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { allocateWeapon, groundSnapRevert, stepTargetRoll, stepTargetYaw } from "../rom/helpers.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ============================================================================
// Borg identity.
// ============================================================================

const GOLD_HERO_BORG_NUMBERS: Record<string, number> = {
  pl0802: 0x802,
};

export type GoldHeroBorgId = keyof typeof GOLD_HERO_BORG_NUMBERS;

// ============================================================================
// Spawner addresses.
// ============================================================================

/** zz_0082824_ — record-table projectile spawn (GOLD HERO 0x802 shot, type 0x2d). */
export const GOLD_HERO_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ — per-borg effect spawn (sibling 0x803 morph shot, type 0x22). */
export const GOLD_HERO_EFFECT_SPAWNER = 0x800c3be0;
/** FUN_8013d600 — the GOLD HERO ammo-gated shot spawner (borg-switched leaf). */
export const GOLD_HERO_SPAWNER_FN = 0x8013d600;

// ============================================================================
// Config constants (DOL-read this session; see header).
// ============================================================================

export const GH = {
  // Scalar / threshold floats.
  /** FLOAT_8043a0f8 = 0.0 — zero scalar / threshold. */
  ZERO: 0.0,
  /** FLOAT_8043a0fc = 1.0 — FUN_80067310 gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_8043a110 = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a114 = 0.95 — blink + per-frame motion scale; action-1 ph2 drag. */
  MOTION_SCALE: 0.95,
  /** FLOAT_8043a118 = 3.0 — afterimage distance threshold (zz_00b22f4_ gate). */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_8043a11c = 20.0 — ubiquitous +0x558 windup/active timer seed. */
  ACTIVE_TIMER: 20.0,
  /** FLOAT_8043a120 = 30.0 — action-1 +0x44 hSpeed seed. */
  HSPEED_SEED: 30.0,
  /** FLOAT_8043a124 = 150.0 — action-1 ph1 +0x764 slow-damp threshold. */
  SLOW_THRESHOLD: 150.0,
  /** FLOAT_8043a128 = 0.5 — velocity drag (slow-damp zz_006ed8c_ arg). */
  DRAG_HALF: 0.5,
  /** FLOAT_8043a12c = 60.0 — action-1 variant-2 ph0 +0x558 seed. */
  LUNGE_TIMER: 60.0,
  /** FLOAT_8043a130 = 400.0 — action-1 active range-check threshold. */
  RANGE_THRESHOLD: 400.0,
  /** FLOAT_8043a134 = 16.0 — action-1 ph2 +0x558 re-seed. */
  ACTIVE2_TIMER: 16.0,
  /** FLOAT_8043a138 = 0.9 — steerYaw / velocity decay (zz_006ed8c_ arg). */
  DECAY_0P9: 0.9,
  /** FLOAT_8043a13c = 0.99 — action-1 ph0 residual velocity drag. */
  DRAG_0P99: 0.99,
  /** FLOAT_8043a140 = 8.0 — action-1 exit +0x694 state-timer seed base. */
  EXIT_STATE_TIMER: 8.0,
  /** FLOAT_8043a144 = 200.0 — action-1 variant-1 ph1 +0x764 threshold. */
  VAR1_SLOW_THRESHOLD: 200.0,
  /** FLOAT_8043a148 = 0.1 — action-1 variant-3 ph0 speed multiplier. */
  VAR3_SPEED_MULT: 0.1,
  // Bit masks.
  /** +0x5e0 action-mode bits 0..1 stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 bit 0x40 — airborne / position-frozen. */
  AIRBORNE_BIT: 0x40,
  /** +0x5e0 bit 0x80 — air-mount (action-0 variant-2 ph0 clears this). */
  AIRMOUNT_BIT: 0x80,
  /** +0x5e0 bit 0x10 — close-input flag (action-0 variant-1 stream select). */
  CLOSE_INPUT_BIT: 0x10,
  /** +0x5e0 bit 0x20 — direction-input flag (action-0 variant-1 stream select). */
  DIR_INPUT_BIT: 0x20,
  /** +0x5b4 bit 0x200 — charge-hold status (action-0 ph2 ammo-gate). */
  CHARGE_BIT_5B4: 0x200,
  /** +0x5d4 bit 0x40 — B-repress edge (action-1 ph4 re-arm). */
  B_REPRESS_EDGE: 0x40,
  /** +0x5d8 bits 0xf0 — held-direction mask (action-0 ph2 release guard). */
  HELD_DIR_MASK: 0xf0,
  /** Stream groups. */
  ACTION0_STREAM_GROUP: 2,
  ACTION1_STREAM_GROUP: 3,
  /** Stream part mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** +0x6ea stream-slot cursor advance per armed phase (action 1). */
  SLOT_ADVANCE: 1,
  /** zz_006a3d0_ command-record cue id for the airborne re-route (action-0 ph2). */
  AIR_ROUT_CUE: 0x3,
  /** +0x1900 / +0x18da / +0x18e0 halver scale (upper-body virtual FUN_8013cb7c). */
  UB_YAW18E0_SCALE: 0.96,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ============================================================================

export interface GoldHeroScratch {
  /** +0x144 (s32): shared buff/charge counter (0x803 morph path decrements; 0x802 ammo
   *  gate checks >= 0). Surfaced on RomActor as childMask144 in some families; here we
   *  keep a dedicated slot for the GOLD HERO semantics. */
  ghChargeCounter144?: number;
  /** +0x558 mirrors handlerTimer when needed (kept on RomActor.handlerTimer). */
  /** +0x55c (f32): action-0 cooldown sub-timer. */
  ghCooldownTimer55c?: number;
  /** +0x560 (f32): action-0 windup/active sub-timer. */
  ghTimer560?: number;
  /** +0x6ea mirrors streamSlot (kept on RomActor.streamSlot for action 1). */
  /** +0x6ee (s8): action-0 stream-slot base. */
  ghStreamSlot6ee?: number;
  /** +0x6ef (s8): GOLD HERO shots remaining this cycle (FUN_8013d600 decrements). */
  ghShotsRemaining6ef?: number;
  /** +0x745 (s8): action-1 ph4 B-repress latch (set on edge, consumed on contact). */
  ghComboLatch745?: number;
  /** +0x764 (f32): action-1 slow-damp speed scalar (threshold FLOAT_8043a124/144). */
  ghSpeedScalar764?: number;
  /** +0x1d0c (s8): stream-authored bit (action-0 variant-2 ph0 stream-arm gate). */
  ghStreamArm1d0c?: number;
  /** +0x1d0d (s8): stream-authored byte (compared to 0x0d for stream-arm). */
  ghStreamArm1d0d?: number;
  /** +0x71c (s8): action-1 variant-1 ph1 steerYaw-decay gate. */
  ghSteerGate71c?: number;
  /** +0x1d9 (s8): hit-react byte (action-1 variant-1 active advance). */
  ghHitReact1d9?: number;
  /** +0x6f6 (s8): action-1 variant-3 ph0 latch. */
  ghLatch6f6?: number;
  /** +0x272 (u16): action-1 variant-3 ph0 bitmask OR 0x43. */
  ghBitmask272?: number;
  /** +0x3e9 (u8): slot index into DAT_80339964 / DAT_803399a4 timer tables. */
  ghSlot3e9?: number;
  /** +0x868/+0x874/+0x880 action-speed rows (first float each). */
  // (surfaced via actor.actionSpeedRows)
  /** +0x86c/+0x880 column-1 range rows (second float each). */
  ghRangeRow86c?: number;
  /** +0xcc lock pointer non-null test surface (also via helpers.lockTarget). */
  // (surfaced via helpers.lockTarget)
}

type GhActor = RomActor & GoldHeroScratch;

function scratchOf(actor: RomActor): GhActor {
  return actor as GhActor;
}

// ============================================================================
// LockTarget / range helpers (samurai pattern).
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

/** FUN_80066838(range, actor) — horizontal-distance range gate. Returns -1 no lock,
 *  1 when |Δ| ≤ range, 0 beyond. (samurai.rangeCheck precedent.) */
function rangeCheck(a: RomActor, range: number): number {
  if (!hasLock(a)) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

/** actor+0x868 row float ((prevActionIndex % 3) × 0xc + 0x868, column 0). */
function rangeRow868(a: GhActor): number {
  const idx = ((a.prevActionIndex ?? 0) % 3 + 3) % 3;
  return a.actionSpeedRows[idx] ?? GH.ACTIVE_TIMER;
}

/** actor+0x86c column-1 row float. */
function rangeRow86c(a: GhActor): number {
  return a.ghRangeRow86c ?? GH.ACTIVE_TIMER;
}

/** Airborne = +0x5e0 position-frozen bit set. */
function isAirborne(a: RomActor): boolean {
  return (a.controlWord & GH.AIRBORNE_BIT) !== 0;
}

/** zz_006ed8c_(scale, actor) — velocity drag on +0x44/+0x48. */
function applyDrag(a: RomActor, scale: number): void {
  a.hSpeed *= scale;
  a.yVel *= scale;
}

/** zz_00670dc_(actor, yaw) — physics-move projecting hSpeed via yaw (FUN_800676d8
 *  shape). Does NOT decay hSpeed/yVel (pure position projection + ground snap). */
function physicsMove(a: RomActor, yaw: number): void {
  integratePhysics(0, a, yaw);
}

/** dataPage(+0x4ac)+0x6c — gravityCoeff restore (descriptor.handlerData6c). */
function gravityRestore(a: RomActor): number {
  return a.descriptor?.handlerData6c ?? 1.0;
}

// ============================================================================
// zz_013d5a4_ (timer loader) — FUN_8013d5a4 @ chunk_0036.c:4228.
// Loads +0x560 = FLOAT_8043a11c (20.0), +0x558/+0x55c from DAT_80339964/803399a4
// tables indexed by +0x3e9 (slot). The slot tables are unsurfaced on the port side
// (TODO host — they're 4-byte float LUTs in the DOL data segment); the default
// fallback is FLOAT_8043a11c (20.0) which matches the corpus mode.
// ============================================================================
function loadGoldHeroTimers(a: GhActor): void {
  a.ghTimer560 = GH.ACTIVE_TIMER; // +0x560 = FLOAT_8043a11c
  // TODO(host): DAT_80339964[+0x3e9] → +0x558; DAT_803399a4[+0x3e9] → +0x55c.
  // Both are 4-byte float LUTs at the cited addresses; default to the mode value.
  a.handlerTimer = GH.ACTIVE_TIMER; // +0x558
  a.ghCooldownTimer55c = GH.ZERO; // +0x55c default
  if ((a.ghStreamSlot6ee ?? 0) !== 0) return;
  // +0x6ef = s_ddddddddddddddd_80339954[+0x3e9] — the per-slot shots-remaining byte.
  // TODO(host): unsurfaced LUT; default to 1 shot per cycle.
  if (a.ghShotsRemaining6ef === undefined) a.ghShotsRemaining6ef = 1;
}

// ============================================================================
// FUN_8013d600 (the GOLD HERO shot spawner) — chunk_0036.c:4247.
// Borg-switched ammo-gated single shot. Loads timers, optionally recomputes the
// aim yaw bookkeeping (zz_0046698_ + FUN_800452a0; TODO host — renderer matrix
// update), then on allocateWeapon(0,1,1) success fires:
//   0x803 → zz_00c3be0_(0x22)
//   0x802 → zz_0082824_(0x2d)
// Each successful shot decrements +0x6ef.
// ============================================================================
function goldHeroSpawn(a: GhActor, ctx: StreamContext): void {
  a.ghTimer560 = GH.ACTIVE_TIMER; // +0x560 = FLOAT_8043a11c
  // TODO(host): DAT_80339964/803399a4 timer-table reload (same as loadGoldHeroTimers).
  a.handlerTimer = GH.ACTIVE_TIMER;
  a.ghCooldownTimer55c = GH.ZERO;
  a.ghStreamSlot6ee = 1; // +0x6ee = 1
  if ((a.ghShotsRemaining6ef ?? 0) > 0) {
    // +0x1900 = 0; zz_0046698_(actor) — TODO(host): renderer aim/yaw refresh.
    // if (+0xcc != 0) { FUN_800452a0 × 2 → +0x1900; zz_0046dd4_(...) } — TODO host.
    if (allocateWeapon(a, ctx, 0, 1, true)) { // zz_006dbe0_(actor,0,1,1)
      if (a.borgNumber === 0x803) {
        ctx.onFamilyProjectile?.(a, GOLD_HERO_EFFECT_SPAWNER, 0x22); // zz_00c3be0_(0x22)
      } else if (a.borgNumber === 0x802) {
        ctx.onFamilyProjectile?.(a, GOLD_HERO_SHOT_HELPER, 0x2d); // zz_0082824_(0x2d)
      }
      a.ghShotsRemaining6ef = (a.ghShotsRemaining6ef ?? 0) - 1; // +0x6ef--
    }
  }
}

// ============================================================================
// zz_006a668_ (shot-channel clear + cue dispatch) — the action-0 variant-1 ph2
// denied-exit path. Clears +0x1d9c/+0x1db2/+0x1db3 + dispatches the current
// upper-body cue (+0x5e4) to full-body. Ported in cyber-machine.ts:618 faithfully;
// here we apply the same essential effects.
// ============================================================================
function dispatchShotClearAndCue(actor: RomActor): void {
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  // zz_006a668_(actor, 0x10) — dispatches the current upper-body cue to full body
  // and strips action bits. The 0x10 is the cue table column selector.
  dispatchFullBodyCue(actor, actor.ubCue);
  actor.controlWord = actor.controlWord & ~GH.ACTION_MODE_BITS;
}

// ============================================================================
// zz_006a3d0_ (command-record re-dispatch) — routes the actor to a different
// actionIndex/variantIndex. (cyber-machine / dragon precedent.) The full ROM
// helper rebuilds +0x5e4/+0x584/+0x580/+0x581 from the command table; here we
// model the essential effect: strip action bits + dispatch the cue.
// ============================================================================
function redispatchAction(actor: RomActor, _cmdByte: number, stateMode: number, variant: number): void {
  actor.controlWord = (actor.controlWord & ~GH.ACTION_MODE_BITS) | (stateMode & GH.ACTION_MODE_BITS);
  actor.variantIndex = variant;
  // The cue comes from the command record; we approximate by dispatching the current
  // attack cue (44) which all GOLD HERO action entries route through.
  dispatchFullBodyCue(actor, 44);
}

// ============================================================================
// FUN_8006cc90 host bridge — no stream banks extracted for GOLD HERO → no-op.
// ============================================================================
function tickGoldHeroStream(): number {
  return 0;
}

// ============================================================================
// Shared blink: motion = pos − targetCache5e8; motion ×= 0.95; pos += motion.
// ============================================================================
function applyBlink(a: RomActor): void {
  vecSubtract(a.pos, a.targetCache5e8, a.motion);
  vecScale(GH.MOTION_SCALE, a.motion, a.motion);
  vecAdd(a.pos, a.motion, a.pos);
}

// (motion-drift + steerYaw-decay helpers from other ports are inlined at their
// call sites here — GOLD HERO's exact coercion idioms differ per phase.)

// ============================================================================
// ACTION 0 — dash/blast loop. 3 variant tables (@0x803399f8 / @0x80339a04 /
// @0x80339a10), each 8 phase slots. The variant is selected by +0x581.
// ============================================================================

// ----------------------------------------------------------------------------
// Variant 0 — table @0x803399f8 (walker FUN_8013cc08 halves +0x1dfc).
//   ph0 FUN_8013cc50  setup — advance, startStream(g=2,slot=+0x6ee), aim, zero
//                       scalars, blink, ground snap, load timers, +0x80c = 0.
//   ph1 FUN_8013cd30  active — tick stream, aim, contact/threshold → spawn
//                       (FUN_8013d600), motion drift, ground snap, afterimage.
//   ph2 FUN_8013ce30  cooldown — drain +0x55c/+0x558, on contactP0<0 + charge bit
//                       ammo gate; OK + shots>0 → re-arm (startStream g=2 slot=1,
//                       +0x540--) OR re-route (airborne); denied/no shots → exit.
// ----------------------------------------------------------------------------

function action0Variant0Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  startStream(a, GH.STREAM_MASK, GH.ACTION0_STREAM_GROUP, a.ghStreamSlot6ee ?? 0, GH.STREAM_RATE);
  stepTargetYaw(a, 0xc1, 0, true); // zz_006d0dc_(0xc1) aim (preserve yaw on loss)
  a.controlWord = a.controlWord & ~(GH.CLOSE_INPUT_BIT | GH.DIR_INPUT_BIT | GH.AIRMOUNT_BIT); // +0x5e0 &= ~0xb0
  loadGoldHeroTimers(a); // zz_013d5a4_
  a.gravityCoeff = GH.ZERO; // +0x50 = FLOAT_8043a0f8
  a.yVel = GH.ZERO; // +0x48
  a.hDecel = GH.ZERO; // +0x4c
  a.hSpeed = GH.ZERO; // +0x44
  a.poseAccum80 = 0; // +0x80
  a.poseAccum7e = 0; // +0x7e
  a.poseAccum7c = 0; // +0x7c
  applyBlink(a); // gnt4_PSVECSubtract / Scale / Add
  groundSnapRevert(a); // zz_00679d0_
  a.accumulator80c = GH.ZERO; // +0x80c = FLOAT_8043a0f8
}

function action0Variant0Phase1(a: GhActor, ctx: StreamContext): void {
  // dt-zero on contact (chunk_0036.c:3915-3919): the ROM temporarily stores dt = 0
  // while ticking the stream so the wait-ops don't advance on a contact frame.
  const savedDt = a.dt;
  if (a.contactP0 !== 0) a.dt = GH.ZERO;
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  a.dt = savedDt;
  const aimConverged = stepTargetYaw(a, 0xc1, 0, true); // zz_006d0dc_(0xc1)
  const t560 = (a.ghTimer560 ?? 0) - a.dt;
  a.ghTimer560 = t560; // +0x560 -= dt
  if ((aimConverged || t560 <= GH.ZERO) && a.contactP0 !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    goldHeroSpawn(a, ctx); // FUN_8013d600
  }
  vecScale(GH.MOTION_SCALE, a.motion, a.motion); // motion ×= FLOAT_8043a114
  vecAdd(a.pos, a.motion, a.pos);
  groundSnapRevert(a); // zz_00679d0_
  if (Math.hypot(a.motion.x, a.motion.y, a.motion.z) > GH.AFTERIMAGE_THRESHOLD) {
    // zz_00b22f4_(actor) — afterimage step (host hook).
  }
}

function action0Variant0Phase2(a: GhActor, ctx: StreamContext): void {
  // Drain +0x55c OR tick the stream (chunk_0036.c:3949-3954).
  if ((a.ghCooldownTimer55c ?? 0) > GH.ZERO) {
    a.ghCooldownTimer55c = (a.ghCooldownTimer55c ?? 0) - a.dt;
  } else {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  // Drain +0x558 OR run the exit branch (chunk_0036.c:3955-3977).
  if (a.handlerTimer > GH.ZERO) {
    a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  } else {
    // Exit branch: contactP0<0 + charge bit → ammo gate.
    if (a.contactP0 < 0 && (a.statusWord5b4 & GH.CHARGE_BIT_5B4) !== 0) {
      const ammoOk = allocateWeapon(a, ctx, 0, 1, false); // zz_006dbe0_(0,1,0)
      if (!ammoOk) {
        action0GroundIdleExit(a);
        return;
      }
      if ((a.ghShotsRemaining6ef ?? 0) > 0 && (a.ghChargeCounter144 ?? 0) >= 0) {
        if (isAirborne(a)) {
          redispatchAction(a, 0, 3, 0); // zz_006a3d0_(0,3,0) — air re-route
          return;
        }
        // zz_006bf80_(actor) — visibility refresh (host hook, no-op here).
        a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- → back to ph1
        startStream(a, GH.STREAM_MASK, GH.ACTION0_STREAM_GROUP, 1, GH.STREAM_RATE);
        return;
      }
    } else {
      a.ghCooldownTimer55c = GH.ZERO; // +0x55c = 0
    }
  }
  // Tail: input-released guard (chunk_0036.c:3978-3989).
  if ((a.inputHeld5d8 & GH.HELD_DIR_MASK) === 0 && (a.inputEdge5d4 & 1) === 0 && a.wallContact === 0) {
    vecScale(GH.MOTION_SCALE, a.motion, a.motion);
    vecAdd(a.pos, a.motion, a.pos);
    groundSnapRevert(a);
    if (Math.hypot(a.motion.x, a.motion.y, a.motion.z) > GH.AFTERIMAGE_THRESHOLD) {
      // zz_00b22f4_(actor) — afterimage (host hook).
    }
    return;
  }
  action0GroundIdleExit(a);
}

/** LAB_8013cf60 exit tail: +0x73f=0; +0x5e0 &= ~3; zz_006a474_ ground idle return. */
function action0GroundIdleExit(a: GhActor): void {
  a.housekeeping73f = 0;
  a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
  romGroundIdleReturn(a); // zz_006a474_
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x80339a04 (walker FUN_8013cfd8, no scratch halver).
//   ph0 FUN_8013d014  setup — compute slot from +0x5e0 bits, startStream(g=2,
//                       slot), load timers.
//   ph1 FUN_8013d0bc  active — zz_006dee8_ aim, tick stream, contact/threshold →
//                       spawn (FUN_8013d600); aim invalid → re-route.
//   ph2 FUN_8013d190  cooldown — drain +0x55c/+0x558; on contactP0<0 + charge bit
//                       ammo gate; OK + shots>0 → borg-switched stream re-arm
//                       (variant by +0x5e0 bits); denied → zz_006a668_ exit.
// ----------------------------------------------------------------------------

function action0Variant1Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  // Slot select (chunk_0036.c:4018-4030): 4 default, 6 if airborne, 2 if close-input,
  // +0x1d10+8 if dir-input (capped to 0 when ubState==0xf).
  let slot = 4;
  if ((a.controlWord & GH.AIRMOUNT_BIT) !== 0) slot = 6;
  if ((a.controlWord & GH.CLOSE_INPUT_BIT) !== 0) slot = 2;
  if ((a.controlWord & GH.DIR_INPUT_BIT) !== 0) {
    slot = (((a.faceGate1d10 ?? 0) + 8) | 0);
    if (a.ubState === 0x0f) slot = 0;
  }
  startStream(a, 1, GH.ACTION0_STREAM_GROUP, slot + ((a.ghStreamSlot6ee ?? 0) | 0), GH.STREAM_RATE);
  loadGoldHeroTimers(a); // zz_013d5a4_
}

function action0Variant1Phase1(a: GhActor, ctx: StreamContext): void {
  const aim = stepTargetRoll(a, true); // zz_006dee8_(1)
  tickStream(a, 1, ctx); // zz_004cd24_(1)
  if (aim < 0) {
    // Target invalid → re-route (ground/air).
    redispatchAction(a, 0, isAirborne(a) ? 4 : 0, 2);
    return;
  }
  const t560 = (a.ghTimer560 ?? 0) - a.dt;
  a.ghTimer560 = t560; // +0x560 -= dt
  if (aim < 1 && t560 > GH.ZERO) return; // still converging + timer alive
  if (a.contactP0 !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    goldHeroSpawn(a, ctx); // FUN_8013d600
  }
}

function action0Variant1Phase2(a: GhActor, _ctx: StreamContext): void {
  // Drain +0x55c OR tick (chunk_0036.c:4087-4092).
  if ((a.ghCooldownTimer55c ?? 0) > GH.ZERO) {
    a.ghCooldownTimer55c = (a.ghCooldownTimer55c ?? 0) - a.dt;
  } else {
    tickStream(a, 1, _ctx);
  }
  // Drain +0x558 OR exit branch.
  if (a.handlerTimer > GH.ZERO) {
    a.handlerTimer = a.handlerTimer - a.dt;
    return;
  }
  // Exit branch: contactP0<0 + charge bit → ammo gate.
  if (!(a.contactP0 < 0 && (a.statusWord5b4 & GH.CHARGE_BIT_5B4) !== 0)) {
    a.ghCooldownTimer55c = GH.ZERO;
    return;
  }
  const ammoOk = allocateWeapon(a, _ctx, 0, 1, false); // zz_006dbe0_(0,1,0)
  if (!ammoOk) {
    action0ShotClearExit(a); // LAB_8013d364: zz_006a668_(0x10) exit
    return;
  }
  if (!((a.ghShotsRemaining6ef ?? 0) > 0 && (a.ghChargeCounter144 ?? 0) >= 0)) return;
  // zz_006bf80_(actor) — visibility refresh (no-op host).
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- → back to ph1
  const cw = a.controlWord;
  if ((cw & GH.AIRBORNE_BIT) !== 0 || a.fbCue === 4) {
    a.variantIndex = 3;
    const slot = (cw & GH.AIRMOUNT_BIT) !== 0 ? 7 : 5;
    startStream(a, 1, GH.ACTION0_STREAM_GROUP, slot, GH.STREAM_RATE);
    return;
  }
  if ((cw & GH.CLOSE_INPUT_BIT) !== 0) {
    a.variantIndex = 1;
    startStream(a, 1, GH.ACTION0_STREAM_GROUP, 3, GH.STREAM_RATE);
    return;
  }
  if ((cw & GH.DIR_INPUT_BIT) !== 0) {
    a.variantIndex = 2;
    const slot = (((a.faceGate1d10 ?? 0) + 9) | 0);
    startStream(a, 1, GH.ACTION0_STREAM_GROUP, a.ubState === 0x0f ? 1 : slot, GH.STREAM_RATE);
    return;
  }
  redispatchAction(a, 0, 0, 2); // zz_006a3d0_(0,0,2) ground idle re-route
}

/** LAB_8013d364 exit tail: zz_006a668_(0x10). */
function action0ShotClearExit(a: GhActor): void {
  a.housekeeping73f = 0;
  a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
  dispatchShotClearAndCue(a);
}

// ----------------------------------------------------------------------------
// Variant 2 — table @0x80339a10 (walker FUN_8013d398 halves +0x1dfc).
//   ph0 FUN_8013d3e0  setup — aim 0x81, clear air-mount bit, physics(1.0,lockYaw),
//                       ground clamp, startStream(1,g=2,+0x6ee+4), conditional
//                       startStream(2,0,0xd), load timers, +0x80c = 0.
//   ph1 FUN_8013d4b4  active — dt-zero on contact, tick stream, physics(1.0),
//                       ground clamp, aim 0x81, contact/threshold → spawn + exit
//                       (+0x5e0 &= ~2, zz_006a5a4_ air return).
//   ph2 FUN_8013d190  cooldown — shared with variant 1.
// ----------------------------------------------------------------------------

function action0Variant2Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  stepTargetYaw(a, 0x81, 0, true); // zz_006d0dc_(0x81)
  a.controlWord = a.controlWord & ~GH.AIRMOUNT_BIT; // +0x5e0 &= ~0x80
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  groundSnapRevert(a); // zz_00677b0_
  startStream(a, 1, GH.ACTION0_STREAM_GROUP, ((a.ghStreamSlot6ee ?? 0) + 4) | 0, GH.STREAM_RATE);
  if ((a.ghStreamArm1d0c ?? 0) !== 0 || (a.ghStreamArm1d0d ?? 0) !== 0x0d) {
    startStream(a, 2, 0, 0x0d, GH.STREAM_RATE); // zz_004beb8_(2,0,0xd)
  }
  loadGoldHeroTimers(a); // zz_013d5a4_
  a.accumulator80c = GH.ZERO; // +0x80c = FLOAT_8043a0f8
}

function action0Variant2Phase1(a: GhActor, ctx: StreamContext): void {
  const savedDt = a.dt;
  if (a.contactP0 !== 0) a.dt = GH.ZERO;
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  a.dt = savedDt;
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  groundSnapRevert(a); // zz_00677b0_
  const aimConverged = stepTargetYaw(a, 0x81, 0, true); // zz_006d0dc_(0x81)
  const t560 = (a.ghTimer560 ?? 0) - a.dt;
  a.ghTimer560 = t560; // +0x560 -= dt
  if ((aimConverged || t560 <= GH.ZERO) && a.contactP0 !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    goldHeroSpawn(a, ctx); // FUN_8013d600
    a.controlWord = a.controlWord & ~0x2; // +0x5e0 &= ~0x2
    romAirKnockoutReturn(a); // zz_006a5a4_
  }
  // zz_00b22f4_(actor) — afterimage (host hook).
}

// ============================================================================
// ACTION 1 — melee combo. 4 variant tables (@0x80339a30 / @0x80339a70 /
// @0x80339a60 / @0x80339a80), each 8 phase slots. Variant selected by +0x581.
// ============================================================================

// ----------------------------------------------------------------------------
// Variant 0 — table @0x80339a30 (walker FUN_8013d7f8 halves +0x18da/+0x18e0,
// clears +0xcc if +0x541).
//   ph0 FUN_8013d860  setup — +0x558=20.0, +0x745=0, +0x6ea=0, zero hSpeed/hDecel,
//                       range gate FUN_80066838(row868) → on fail +0x541=1 + +0xcc=0
//                       + +0x5ac=+0x72; aim 0xc0; +0x6ea++; startStream(0xf,3,slot).
//   ph1 FUN_8013d940  windup — tick stream (gated by +0x1b03), drain +0x558; on
//                       expiry/aim-converge → +0x540++, +0x558=20, +0x44=30, +0x4c=0,
//                       zz_00b2190_(0) afterimage arm.
//   ph2 FUN_8013d9e0  active — aim 0xc0, physics-move, tick stream, drain +0x558;
//                       on expiry/range-check → +0x540++, +0x6ea++, startStream.
//   ph3 FUN_8013da94  active2 — tick stream, aim, physics-move, drain; on
//                       expiry/range-check → +0x540++.
//   ph4 FUN_8013db28  recover — on B-repress edge latch +0x745=1; contactP0<0 +
//                       latch → +0x540++, +0x745=0, +0x558=20, +0x44=30, +0x4c=0,
//                       zz_00b2190_(0), +0x6ea++, startStream; else FUN_8013dc0c.
// ----------------------------------------------------------------------------

function action1Variant0Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = FLOAT_8043a11c (20.0)
  a.ghComboLatch745 = 0; // +0x745 = 0
  a.streamSlot = 0; // +0x6ea = 0
  a.hSpeed = GH.ZERO; // +0x44
  a.hDecel = GH.ZERO; // +0x4c
  // FUN_80066838(row868, actor) range gate.
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1; // +0x541 = 1
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null; // +0xcc = 0
    a.activeYaw = a.heading; // +0x5ac = +0x72
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  const slot = a.streamSlot ?? 0;
  a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
  startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
}

function action1Variant0Phase1(a: GhActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = 20.0
    a.hSpeed = GH.HSPEED_SEED; // +0x44 = FLOAT_8043a120 (30.0)
    a.hDecel = GH.ZERO; // +0x4c = 0
    // zz_00b2190_(actor, 0) — afterimage arm (host hook).
  }
}

function action1Variant0Phase2(a: GhActor, ctx: StreamContext): void {
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  physicsMove(a, a.lockYaw); // zz_00670dc_(lockYaw)
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || rangeCheck(a, GH.RANGE_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    const slot = a.streamSlot ?? 0;
    a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
    startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
  }
}

function action1Variant0Phase3(a: GhActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  physicsMove(a, a.lockYaw); // zz_00670dc_(lockYaw)
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || rangeCheck(a, GH.RANGE_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

function action1Variant0Phase4(a: GhActor, ctx: StreamContext): void {
  if ((a.inputEdge5d4 & GH.B_REPRESS_EDGE) !== 0) {
    a.ghComboLatch745 = 1; // +0x745 = 1
  }
  if (a.contactP0 < 0 && (a.ghComboLatch745 ?? 0) !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.ghComboLatch745 = 0; // +0x745 = 0
    a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = 20.0
    a.hSpeed = GH.HSPEED_SEED; // +0x44 = 30.0
    a.hDecel = GH.ZERO; // +0x4c = 0
    // zz_00b2190_(actor, 0) — afterimage arm (host hook).
    const slot = a.streamSlot ?? 0;
    a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
    startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
  } else {
    action1RecoverTail(a, ctx); // FUN_8013dc0c
  }
}

// ----------------------------------------------------------------------------
// FUN_8013dc0c (action-1 recover tail) — chunk_0036.c:4509. Tick stream, aim, dash-
// strength clear, slow-damp drag, physics-move, wall-contact → ground idle exit.
// ----------------------------------------------------------------------------

function action1RecoverTail(a: GhActor, ctx: StreamContext): void {
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  if ((a.faceGate1d10 ?? 0) !== 0) {
    stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  }
  if (a.dashStrength1d0f !== 0) {
    a.dashStrength1d0f = 0; // +0x1d0f = 0
    a.hSpeed = GH.HSPEED_SEED; // +0x44 = FLOAT_8043a120
    a.hDecel = GH.ZERO; // +0x4c = 0
  }
  if ((a.ghSpeedScalar764 ?? 0) < GH.SLOW_THRESHOLD) {
    applyDrag(a, GH.DRAG_HALF); // zz_006ed8c_(0.5)
  }
  if ((a.ghHitReact1d9 ?? 0) !== 0) {
    applyDrag(a, GH.DRAG_HALF); // zz_006ed8c_(0.5)
  }
  applyDrag(a, GH.MOTION_SCALE); // zz_006ed8c_(0.95)
  physicsMove(a, a.lockYaw); // zz_00670dc_(lockYaw)
  if (a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    romGroundIdleReturn(a); // zz_006a474_
  }
}

// ----------------------------------------------------------------------------
// Variant 2 — table @0x80339a60 (walker FUN_8013dcec clears +0xcc if +0x541).
//   ph0 FUN_8013dd3c  setup — +0x558=60.0 (FLOAT_8043a12c), +0x6ea=7, range gate
//                       FUN_800668cc(row86c), aim yaw+pitch, zero scalars, blink,
//                       ground clamp, +0x6ea++, startStream.
//   ph1 FUN_8013de88  windup — motion drift, ground clamp, tick stream, aim pitch,
//                       drain +0x558; on expiry/aim → +0x540++, +0x558=20, zz_0092dcc_.
//   ph2 FUN_8013df58  active — tick stream, aim yaw+pitch, hSpeed/yVel from
//                       steerYaw × 20, physics(1.0), ground clamp, drain; on
//                       expiry/range → +0x540++, +0x558=16 (FLOAT_8043a134).
//   ph3 FUN_8013e064  recover — dir-input brake, tick stream, steerYaw decay,
//                       drag, physics(1.0), ground clamp; contactP0<0 → cue 7 exit;
//                       wallContact → air-return + state-timer 8.
// ----------------------------------------------------------------------------

function action1Variant2Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  a.handlerTimer = GH.LUNGE_TIMER; // +0x558 = FLOAT_8043a12c (60.0)
  a.streamSlot = 7; // +0x6ea = 7
  // FUN_800668cc(row86c, actor) range gate.
  if (rangeCheck(a, rangeRow86c(a)) < 1) {
    a.fbPhaseSlots[1] = 1; // +0x541 = 1
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null; // +0xcc = 0
  }
  if (!hasLock(a)) {
    a.activeYaw = a.heading; // +0x5ac = +0x72
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  // zz_006e1d0_(0xc0, 1, 0x2000) — body pitch aim (host renderer hook; modeled as
  // the lock-yaw snapshot for the physics integrator).
  a.lockYaw = a.heading;
  a.gravityCoeff = GH.ZERO; // +0x50
  a.yVel = GH.ZERO; // +0x48
  a.hDecel = GH.ZERO; // +0x4c
  a.hSpeed = GH.ZERO; // +0x44
  a.poseAccum80 = 0;
  a.poseAccum7e = 0;
  a.poseAccum7c = 0;
  applyBlink(a); // gnt4_PSVECSubtract / Scale / Add
  groundSnapRevert(a); // zz_00677b0_
  const slot = a.streamSlot ?? 0;
  a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
  startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
}

function action1Variant2Phase1(a: GhActor, ctx: StreamContext): void {
  vecScale(GH.MOTION_SCALE, a.motion, a.motion); // motion ×= 0.95
  vecAdd(a.pos, a.motion, a.pos);
  groundSnapRevert(a); // zz_00677b0_
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  // zz_006e1d0_(0xc0,1,0x2000) — body pitch aim (renderer hook).
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = 20.0
    // zz_0092dcc_(actor, 0) — host renderer hook (afterimage trail arm).
  }
}

function action1Variant2Phase2(a: GhActor, ctx: StreamContext): void {
  if (a.contactP0 === 0 || a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  // zz_006e1d0_(0xc0,1,0x2000) — body pitch aim.
  // hSpeed = FLOAT_8043a11c × cos(steerYaw); yVel = -FLOAT_8043a11c × sin(steerYaw).
  // (chunk_0036.c:4651-4655; zz_0045238_/zz_0045204_ are cos/sin of BAM16.)
  const yawRad = (a.steerYaw / 0x10000) * Math.PI * 2;
  a.hSpeed = GH.ACTIVE_TIMER * Math.cos(yawRad); // +0x44 = 20 × cos(steerYaw)
  a.yVel = -GH.ACTIVE_TIMER * Math.sin(yawRad); // +0x48 = -20 × sin(steerYaw)
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  groundSnapRevert(a); // zz_00677b0_
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || rangeCheck(a, GH.RANGE_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.ACTIVE2_TIMER; // +0x558 = FLOAT_8043a134 (16.0)
    if (!hasLock(a)) {
      a.handlerTimer = GH.ZERO; // +0x558 = 0 (no target → skip active2)
    }
  }
}

function action1Variant2Phase3(a: GhActor, ctx: StreamContext): void {
  // Dir-input brake (chunk_0036.c:4687-4695): on (0x1d9 & 0x30) flip lockYaw 180°.
  if (((a.ghHitReact1d9 ?? 0) & 0x30) !== 0) {
    a.hSpeed = GH.ZERO;
    a.hDecel = GH.ZERO;
    a.yVel = GH.ACTIVE_TIMER; // +0x48 = 20.0
    a.gravityCoeff = GH.STREAM_RATE; // +0x50 = -1.0 (FLOAT_8043a110)
    a.lockYaw = (a.lockYaw - 0x8000) & 0xffff; // +0x5ae -= 0x8000
    a.fbPhaseSlots[2] = 1; // +0x542 = 1
  }
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  if ((a.ghSteerGate71c ?? 0) === 0 && (a.fbPhaseSlots[2] ?? 0) !== 0) {
    // steerYaw ×= 0.9 idiom (chunk_0036.c:4698-4702, FLOAT_8043a138).
    a.steerYaw = Math.trunc(a.steerYaw * GH.DECAY_0P9);
  }
  applyDrag(a, GH.DRAG_0P99); // zz_006ed8c_(0.99) — FLOAT_8043a13c
  a.gravityCoeff = gravityRestore(a); // +0x50 = dataPage(+0x4ac)+0x6c
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  const grounded = groundSnapRevert(a); // zz_00677b0_
  if (grounded && a.contactP0 < 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    dispatchUpperBodyCue(a, 7); // zz_006a750_(7)
    a.stateTimer = GH.EXIT_STATE_TIMER + a.dt; // +0x694 = 8.0 + dt
    return;
  }
  if (a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    romAirKnockoutReturn(a); // zz_006a5a4_
    a.stateTimer = GH.EXIT_STATE_TIMER + a.dt; // +0x694 = 8.0 + dt
  }
}

// ----------------------------------------------------------------------------
// Variant 1 — table @0x80339a70 (walker FUN_8013e1d8 halves +0x18da/+0x18e0,
// clears +0xcc if +0x541). Flight melee.
//   ph0 FUN_8013e240   setup — +0x6ea=5/6 (variant 2), range gate, aim, blink,
//                        ground clamp, +0x558=20, +0x6ea++, startStream.
//   ph1 FUN_8013e33c   windup — tick stream, drain +0x558; on expiry/aim → +0x540++,
//                        +0x558=30, +0x44=rangeRow/30, +0x4c=0, afterimage arm.
//   ph2 FUN_8013e43c   active — tick stream, aim, physics-move, drain; on
//                        expiry/range → +0x540++.
//   ph3 FUN_8013e4d8   recover — tick stream, drag, physics-move, contactP0<0 →
//                        ground idle exit; afterimage.
// ----------------------------------------------------------------------------

function action1Variant1Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  a.streamSlot = a.variantIndex === 2 ? 6 : 5; // +0x6ea = 5 (or 6 if variant 2)
  if (rangeCheck(a, rangeRow868(a)) < 1) {
    a.fbPhaseSlots[1] = 1; // +0x541 = 1
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null; // +0xcc = 0
    a.activeYaw = a.heading; // +0x5ac = +0x72
    if ((a.controlWord & GH.DIR_INPUT_BIT) !== 0) {
      a.activeYaw = a.lockYaw; // +0x5ac = +0x5ae
    }
  }
  a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = 20.0
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  const slot = a.streamSlot ?? 0;
  a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
  startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
  a.accumulator80c = GH.ZERO; // +0x80c = 0
}

function action1Variant1Phase1(a: GhActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.HSPEED_SEED; // +0x558 = 30.0 (FLOAT_8043a120)
    // +0x44 = (lock ? max(rangeRow, +0x764) : rangeRow) / 30.0; +0x4c = 0.
    const row = rangeRow868(a);
    const speedSrc = hasLock(a) && row < (a.ghSpeedScalar764 ?? 0) ? (a.ghSpeedScalar764 ?? 0) : row;
    a.hSpeed = speedSrc / GH.HSPEED_SEED; // +0x44
    a.hDecel = GH.ZERO; // +0x4c
    if (GH.VAR1_SLOW_THRESHOLD < (a.ghSpeedScalar764 ?? 0)) {
      // zz_00b2190_(actor, 0) — afterimage arm (host hook).
    }
  }
}

function action1Variant1Phase2(a: GhActor, ctx: StreamContext): void {
  if (a.contactP0 === 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  physicsMove(a, a.lockYaw); // zz_00670dc_(lockYaw)
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || rangeCheck(a, GH.RANGE_THRESHOLD) !== 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
  // zz_00b22f4_(actor) — afterimage (host hook).
}

function action1Variant1Phase3(a: GhActor, ctx: StreamContext): void {
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  if ((a.faceGate1d10 ?? 0) !== 0) {
    stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  }
  applyDrag(a, GH.DECAY_0P9); // zz_006ed8c_(0.9) — FLOAT_8043a138
  physicsMove(a, a.lockYaw); // zz_00670dc_(lockYaw)
  if (a.contactP0 < 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    romGroundIdleReturn(a); // zz_006a474_
  }
  if (a.hSpeed > GH.AFTERIMAGE_THRESHOLD) {
    // zz_00b22f4_(actor) — afterimage (host hook).
  }
}

// ----------------------------------------------------------------------------
// Variant 3 — table @0x80339a80 (walker FUN_8013e578 clears +0xcc if +0x541).
//   ph0 FUN_8013e5c8  setup — +0x558=60.0, +0x6ea=8, range gate row86c, aim yaw+pitch,
//                      blink, ground clamp, +0x6ea++, startStream.
//   ph1..ph3 shared with variant 1 (FUN_8013e6e4/e7d8/e8d4).
//   ph4..ph7 = FUN_8013e9e0 (re-dispatch action-1 variant via +0x540).
// ----------------------------------------------------------------------------

function action1Variant3Phase0(a: GhActor): void {
  a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  a.handlerTimer = GH.LUNGE_TIMER; // +0x558 = 60.0 (FLOAT_8043a12c)
  a.streamSlot = 8; // +0x6ea = 8
  if (rangeCheck(a, rangeRow86c(a)) < 1) {
    a.fbPhaseSlots[1] = 1; // +0x541 = 1
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null; // +0xcc = 0
    a.activeYaw = a.lockYaw; // +0x5ac = +0x5ae
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  // zz_006e1d0_(0xc0,1,0x2000) — body pitch aim (renderer hook).
  applyBlink(a); // blink toward +0x5e8
  groundSnapRevert(a); // zz_00677b0_
  const slot = a.streamSlot ?? 0;
  a.streamSlot = slot + GH.SLOT_ADVANCE; // +0x6ea++
  startStream(a, GH.STREAM_MASK, GH.ACTION1_STREAM_GROUP, slot, GH.STREAM_RATE);
}

// FUN_8013e6e4 — variant 1 ph1 shape but zeroes all velocity scalars on advance.
function action1Variant3Phase1(a: GhActor, ctx: StreamContext): void {
  vecScale(GH.MOTION_SCALE, a.motion, a.motion); // motion ×= 0.95
  vecAdd(a.pos, a.motion, a.pos);
  groundSnapRevert(a); // zz_00677b0_
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  // zz_006e1d0_(0xc0,1,0x2000) — body pitch aim.
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || stepTargetYaw(a, 0xc0)) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.ACTIVE_TIMER; // +0x558 = 20.0
    a.gravityCoeff = GH.ZERO;
    a.yVel = GH.ZERO;
    a.hDecel = GH.ZERO;
    a.hSpeed = GH.ZERO;
    a.poseAccum80 = 0;
    a.poseAccum7e = 0;
    a.poseAccum7c = 0;
    // zz_0092dcc_(actor, 0) — afterimage trail arm (host hook).
  }
}

// FUN_8013e7d8 — variant 1 ph2 shape with steerYaw projection.
function action1Variant3Phase2(a: GhActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {
    tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  stepTargetYaw(a, 0xc0); // zz_006d144_(0xc0)
  // zz_006e1d0_(0xc0,1,0x2000) — body pitch aim.
  const yawRad = (a.steerYaw / 0x10000) * Math.PI * 2;
  a.hSpeed = GH.ACTIVE_TIMER * Math.cos(yawRad); // +0x44 = 20 × cos(steerYaw)
  a.yVel = -GH.ACTIVE_TIMER * Math.sin(yawRad); // +0x48 = -20 × sin(steerYaw)
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  groundSnapRevert(a); // zz_00677b0_
  a.handlerTimer = a.handlerTimer - a.dt; // +0x558 -= dt
  if (a.handlerTimer <= GH.ZERO || rangeCheck(a, GH.RANGE_THRESHOLD) > 0) {
    a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    a.handlerTimer = GH.ACTIVE2_TIMER; // +0x558 = 16.0 (FLOAT_8043a134)
    if (!hasLock(a)) {
      a.handlerTimer = GH.ZERO; // +0x558 = 0 (no target → skip)
    }
  }
}

// FUN_8013e8d4 — variant 1 ph3 recover (chunk_0037.c:3). Drag, physics, contact exit.
function action1Variant3Phase3(a: GhActor, ctx: StreamContext): void {
  tickStream(a, GH.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  applyDrag(a, GH.DRAG_0P99); // zz_006ed8c_(0.99) — FLOAT_8043a13c
  a.gravityCoeff = gravityRestore(a); // +0x50 = dataPage(+0x4ac)+0x6c
  integratePhysics(GH.PHYSICS_GRAVITY, a, a.lockYaw); // FUN_80067310(1.0, lockYaw)
  const grounded = groundSnapRevert(a); // zz_00677b0_
  if (grounded && a.contactP0 < 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    dispatchUpperBodyCue(a, 7); // zz_006a750_(7)
    a.stateTimer = GH.EXIT_STATE_TIMER + a.dt; // +0x694 = 8.0 + dt
    return;
  }
  if (a.wallContact !== 0) {
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~GH.ACTION_MODE_BITS;
    romAirKnockoutReturn(a); // zz_006a5a4_
  }
}

// ============================================================================
// Phase-table walkers. Each variant-table walker (FUN_8013cc08 / FUN_8013cfd8 / ...)
// halves a scratch field then dispatches its 8-entry table by +0x540. The cross-
// action routers (FUN_8013d7f8 / FUN_8013e1d8 / FUN_8013dcec / FUN_8013e578) are
// themselves the action-1 variant-table walkers.
// ============================================================================

type PhaseFn = (a: GhActor, ctx: StreamContext) => void;

// Action 0 variant 0 — table @0x803399f8 (walker FUN_8013cc08 halves +0x1dfc).
const ACTION0_VARIANT0_TABLE: PhaseFn[] = [
  action0Variant0Phase0, action0Variant0Phase1, action0Variant0Phase2,
  action0Variant1Phase0, action0Variant1Phase1, action0Variant1Phase2,
  action0Variant2Phase0, action0Variant2Phase1,
];

// Action 0 variant 1 — table @0x80339a04 (walker FUN_8013cfd8).
const ACTION0_VARIANT1_TABLE: PhaseFn[] = [
  action0Variant1Phase0, action0Variant1Phase1, action0Variant1Phase2,
  action0Variant2Phase0, action0Variant2Phase1, action0Variant1Phase2,
  action1Variant0Phase0, action1Variant1Phase0,
];

// Action 0 variant 2 — table @0x80339a10 (walker FUN_8013d398 halves +0x1dfc).
const ACTION0_VARIANT2_TABLE: PhaseFn[] = [
  action0Variant2Phase0, action0Variant2Phase1, action0Variant1Phase2,
  action1Variant0Phase0, action1Variant1Phase0, action1Variant1Phase0,
  action1Variant2Phase0, action1Variant3Phase0,
];

// Action 1 variant 0 — table @0x80339a30 (walker FUN_8013d7f8 halves +0x18da/+0x18e0).
const ACTION1_VARIANT0_TABLE: PhaseFn[] = [
  action1Variant0Phase0, action1Variant0Phase1, action1Variant0Phase2,
  action1Variant0Phase3, action1Variant0Phase4, action1Variant0Phase3,
  action1Variant0Phase4, action1Variant0Phase4,
];

// Action 1 variant 1 — table @0x80339a70 (walker FUN_8013e1d8 halves +0x18da/+0x18e0).
const ACTION1_VARIANT1_TABLE: PhaseFn[] = [
  action1Variant1Phase0, action1Variant1Phase1, action1Variant1Phase2,
  action1Variant1Phase3, action1Variant3Phase0, action1Variant3Phase1,
  action1Variant3Phase2, action1Variant3Phase3,
];

// Action 1 variant 2 — table @0x80339a60 (walker FUN_8013dcec).
const ACTION1_VARIANT2_TABLE: PhaseFn[] = [
  action1Variant2Phase0, action1Variant2Phase1, action1Variant2Phase2,
  action1Variant2Phase3, action1Variant1Phase0, action1Variant1Phase1,
  action1Variant1Phase2, action1Variant1Phase3,
];

// Action 1 variant 3 — table @0x80339a80 (walker FUN_8013e578).
const ACTION1_VARIANT3_TABLE: PhaseFn[] = [
  action1Variant3Phase0, action1Variant3Phase1, action1Variant3Phase2,
  action1Variant3Phase3, action1RecoverTail, action1RecoverTail,
  action1RecoverTail, action1RecoverTail,
];

const ACTION0_TABLES: PhaseFn[][] = [
  ACTION0_VARIANT0_TABLE, ACTION0_VARIANT1_TABLE, ACTION0_VARIANT2_TABLE,
];

const ACTION1_TABLES: PhaseFn[][] = [
  ACTION1_VARIANT0_TABLE, ACTION1_VARIANT1_TABLE, ACTION1_VARIANT2_TABLE, ACTION1_VARIANT3_TABLE,
];

// ============================================================================
// Root action dispatcher — FUN_8013cb40 @ chunk_0036.c:3828. Dispatches the
// actionIndex → variant-router → phase-table. Each variant-table walker halves
// a scratch field (modeling the ROM's per-walker prologue) then dispatches the
// selected phase table by +0x540.
// ============================================================================

export function createGoldHeroRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    const actionIndex = a.actionIndex;
    const variantIndex = a.variantIndex;
    let table: PhaseFn[] | null = null;
    if (actionIndex === 0) {
      // Variant-table walkers: FUN_8013cc08 / FUN_8013cfd8 / FUN_8013d398.
      // The variant-0/2 walkers halve +0x1dfc (stepTargetRoll accumulator in
      // helpers); variant-1 walker has no prologue.
      if (variantIndex === 0 || variantIndex === 2) {
        // +0x1dfc /= 2 (chunk_0036.c:3861, 4158).
        const scratch = a as RomActor & { aimRoll1dfc?: number };
        scratch.aimRoll1dfc = Math.trunc((scratch.aimRoll1dfc ?? 0) / 2);
      }
      table = ACTION0_TABLES[variantIndex] ?? ACTION0_VARIANT0_TABLE;
    } else if (actionIndex === 1) {
      // Variant-table walkers: FUN_8013d7f8 / FUN_8013e1d8 / FUN_8013dcec / FUN_8013e578.
      // Variants 0/1 halve +0x18da/+0x18e0 (chunk_0036.c:4327-4328, 4731-4732);
      // variants 2/3 clear +0xcc if +0x541 (chunk_0036.c:4549-4551, 4866-4868).
      if (variantIndex === 0 || variantIndex === 1) {
        a.steerYaw = Math.trunc(a.steerYaw / 2); // +0x18da /= 2
        const scratch = a as RomActor & { aimPitch18e0?: number };
        scratch.aimPitch18e0 = Math.trunc((scratch.aimPitch18e0 ?? 0) / 2); // +0x18e0 /= 2
      } else {
        if ((a.fbPhaseSlots[1] ?? 0) !== 0) {
          (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null; // +0xcc = 0
        }
      }
      table = ACTION1_TABLES[variantIndex] ?? ACTION1_VARIANT0_TABLE;
    }
    if (!table) return;
    const phase = a.fbPhaseSlots[0] ?? 0;
    const fn = table[phase];
    if (fn) fn(a, ctx);
    void tickGoldHeroStream; // FUN_8006cc90 host bridge (no-op, referenced for fidelity)
  };
}

// ============================================================================
// Upper-body virtual — FUN_8013cb7c @ chunk_0036.c:3841. Halves +0x1900 (×0.96)
// and +0x18da/+0x18e0 (÷2), then dispatches PTR_FUN_803399e4[+0x581]. Not invoked
// during state-61 attack but wired for fidelity.
// ============================================================================

export function createGoldHeroUpperBody(): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = base as RomActor & { aimYaw18e2?: number; aimPitch18e0?: number };
    a.aimYaw18e2 = Math.trunc((a.aimYaw18e2 ?? 0) * GH.UB_YAW18E0_SCALE); // +0x1900 ×= 0.96
    base.steerYaw = Math.trunc(base.steerYaw / 2); // +0x18da /= 2
    a.aimPitch18e0 = Math.trunc((a.aimPitch18e0 ?? 0) / 2); // +0x18e0 /= 2
    // PTR_FUN_803399e4[+0x581] — upper-body variant dispatch (host renderer hook).
  };
}

// ============================================================================
// configureGoldHeroFamily — wires the rootAction + upper-body virtual, stamps the
// borg-number switch (0x802), and zeroes the stream cursors. The ctor-side
// helper-allocation (FUN_8013c844 → zz_013c50c_ wingman setup) is a TODO(host):
// the satellite object system isn't surfaced on the port side.
// ============================================================================

export function configureGoldHeroFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = 0x802; // GOLD_HERO_BORG_NUMBERS.pl0802
  actor.rootAction = createGoldHeroRootAction(ctx);
  actor.upperBody = createGoldHeroUpperBody();
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  // TODO(host): FUN_8013c844 ctor setup — zz_013c50c_(actor) allocates the wingman
  // beam objects for borg 0x802 (2 helper slots at +0x708 stride 0x80). The satellite
  // system isn't surfaced on RomActor; bridge wires this at spawn time.
}

// ============================================================================
// Self-tests. Mirror rom.selfcheck.ts / victory-king.ts style.
// ============================================================================

export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

function makeCtx(opts: {
  onAllocateResource?: (slot: number, count: number, mode: number) => boolean;
  onFamilyProjectile?: (addr: number, type: number) => void;
  onParamTierDelta?: (delta: number) => void;
  onPlayCue?: (cueId: number) => void;
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
  if (opts.onParamTierDelta) {
    const sink = opts.onParamTierDelta;
    ctx.onParamTierDelta = (_a, delta) => sink(delta);
  }
  if (opts.onPlayCue) {
    const sink = opts.onPlayCue;
    ctx.onPlayCue = (_a, cueId) => sink(cueId);
  }
  return ctx;
}

export function runGoldHeroSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // ==========================================================================
  // configure: stamps borgNumber 0x802 + wires rootAction.
  // ==========================================================================
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    assert(a.borgNumber === 0x802, "configure stamps borgNumber 0x802 (GOLD HERO)");
    assert(a.rootAction !== null, "configure wires rootAction (FUN_8013cb40)");
    assert(a.upperBody !== null, "configure wires upperBody (FUN_8013cb7c)");
  }

  // ==========================================================================
  // ACTION 0 — variant 0 (table @0x803399f8).
  // ==========================================================================

  // --- ph0 setup: advance +0x540, zero scalars, blink, +0x80c=0, pose accum. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.accumulator80c = 42;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 v0 ph0 advances +0x540 to 1");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action0 v0 ph0 zeroes hSpeed/hDecel/gravityCoeff (FLOAT_8043a0f8)");
    assert(a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      "action0 v0 ph0 clears pose accumulators");
    assert(a.accumulator80c === 0, "action0 v0 ph0 +0x80c = 0 (FLOAT_8043a0f8)");
    // blink: motion = (pos − target) × 0.95 = (95,0,0); pos += motion → x = 195.
    assert(approxEq(a.pos.x, 195), "action0 v0 ph0 blink pos.x = 195 ((100−0)×0.95 added)");
    assert(approxEq(a.motion.x, 95), "action0 v0 ph0 motion.x = 95 (×FLOAT_8043a114)");
  }

  // --- ph0 controlWord strip: bits 0x10/0x20/0x80 cleared. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.controlWord = 0xb0; // bits 4/5/7
    root(a); // ph0
    assert((a.controlWord & 0xb0) === 0, "action0 v0 ph0 strips +0x5e0 bits 0x10/0x20/0x80");
  }

  // --- ph1 contact + ammo ok → borg-switched zz_0082824_(0x2d) spawn. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // ph1
    a.ghTimer560 = 1; // force the threshold branch (1 − 1 = 0 ≤ 0)
    a.ghShotsRemaining6ef = 1;
    a.contactP0 = 1; // +0x1cef set (shot fired this frame)
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === GOLD_HERO_SHOT_HELPER && shots[0]!.type === 0x2d,
      `action0 v0 ph1 contact spawns zz_0082824_(0x2d) (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 2, "action0 v0 ph1 contact → +0x540++ (advance to ph2)");
    assert((a.ghShotsRemaining6ef ?? 0) === 0, "action0 v0 ph1 spawn decrements +0x6ef");
  }

  // --- ph1 borgNumber 0x803 morph path → zz_00c3be0_(0x22). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.borgNumber = 0x803; // sibling morph form
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.ghTimer560 = 1;
    a.ghShotsRemaining6ef = 1;
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === GOLD_HERO_EFFECT_SPAWNER && shots[0]!.type === 0x22,
      "action0 v0 ph1 borg 0x803 spawns zz_00c3be0_(0x22)");
  }

  // --- ph1 ammo DENIED → no spawn (FUN_8013d600 gate). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.ghTimer560 = 1;
    a.ghShotsRemaining6ef = 1;
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 0, "action0 v0 ph1 ammo denied suppresses zz_0082824_ spawn");
    assert((a.ghShotsRemaining6ef ?? 0) === 1, "action0 v0 ph1 ammo denied does NOT decrement +0x6ef");
    assert(a.fbPhaseSlots[0] === 2, "action0 v0 ph1 still advances to ph2 on denied ammo");
  }

  // --- ph2 cooldown: +0x558 drains; ground-idle exit when input released. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1);
    a.fbPhaseSlots[0] = 2; // ph2
    a.handlerTimer = 0; // skip the +0x558 drain (already ≤ 0)
    a.contactP0 = 0; // no charge-bit gate
    a.inputEdge5d4 = 0; a.inputHeld5d8 = 0; a.wallContact = 1; // release guard fails → exit
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.hSpeed = 8; a.yVel = 4; a.hDecel = 2; a.gravityCoeff = 1;
    root(a); // ph2 → ground idle exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 v0 ph2 exit clears +0x73f + strips +0x5e0 bits");
    assert(a.yVel === 0 && a.hSpeed === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action0 v0 ph2 ground idle return (zz_006a474_) zeroes velocity scalars");
  }

  // --- ph2 re-arm: contactP0<0 + charge bit + ammo ok → +0x540-- (back to ph1). ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0;
    a.contactP0 = -1; // < 0 → charge-bit branch
    a.statusWord5b4 = GH.CHARGE_BIT_5B4; // charge held
    a.ghShotsRemaining6ef = 1;
    a.ghChargeCounter144 = 0; // >= 0
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action0 v0 ph2 re-arm decrements +0x540 (back to ph1)");
  }

  // ==========================================================================
  // ACTION 0 — variant 1 (table @0x80339a04). Stream-slot select from +0x5e0 bits.
  // ==========================================================================

  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 1; a.dt = 1;
    a.controlWord = 0; // default slot 4
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 v1 ph0 advances +0x540 to 1");
    assert(a.handlerTimer === GH.ACTIVE_TIMER, "action0 v1 ph0 +0x558 = 20.0 (timer loader default)");
  }

  // ==========================================================================
  // ACTION 0 — variant 2 (table @0x80339a10). Physics-integrated active phase.
  // ==========================================================================

  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 2; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.accumulator80c = 42;
    a.controlWord = GH.AIRMOUNT_BIT; // bit 0x80 set → ph0 clears it
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 v2 ph0 advances +0x540 to 1");
    assert((a.controlWord & GH.AIRMOUNT_BIT) === 0, "action0 v2 ph0 clears +0x5e0 bit 0x80");
    assert(a.accumulator80c === 0, "action0 v2 ph0 +0x80c = 0");
  }

  // ==========================================================================
  // ACTION 1 — variant 0 (table @0x80339a30, ground combo).
  // ==========================================================================

  // --- ph0 setup: +0x558=20, +0x745=0, +0x6ea=0→1, hSpeed/hDecel=0, stream slot. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.hDecel = 3;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 100 }; // in range
    a.actionSpeedRows = [200, 200, 200];
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action1 v0 ph0 advances +0x540 to 1");
    assert(a.handlerTimer === GH.ACTIVE_TIMER, "action1 v0 ph0 +0x558 = 20.0 (FLOAT_8043a11c)");
    assert(a.ghComboLatch745 === 0, "action1 v0 ph0 +0x745 = 0");
    assert(a.streamSlot === 1, "action1 v0 ph0 +0x6ea = 0 → 1 (slot pre-read + advance)");
    assert(a.hSpeed === 0 && a.hDecel === 0, "action1 v0 ph0 zeroes hSpeed/hDecel");
  }

  // --- ph0 range-gate fail → +0x541=1, +0xcc=0, +0x5ac=+0x72. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 9999 }; // out of range
    a.actionSpeedRows = [200, 200, 200];
    a.heading = 0x1234;
    root(a); // ph0
    assert((a.fbPhaseSlots[1] ?? 0) === 1, "action1 v0 ph0 range-gate fail → +0x541 = 1");
    assert((a as RomActor & { lockTarget?: Vec3 | null }).lockTarget === null,
      "action1 v0 ph0 range-gate fail clears +0xcc (lockTarget)");
    assert(a.activeYaw === 0x1234, "action1 v0 ph0 range-gate fail +0x5ac = +0x72 (heading)");
  }

  // --- ph1 timer expiry → ph2: +0x558=20, +0x44=30, +0x4c=0. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // ph1
    a.handlerTimer = 1; // one frame from expiry (1 − 1 = 0 ≤ 0)
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 v0 ph1 timer expiry → ph2");
    assert(a.handlerTimer === GH.ACTIVE_TIMER, "action1 v0 ph1→ph2 +0x558 = 20.0 (FLOAT_8043a11c)");
    assert(a.hSpeed === GH.HSPEED_SEED, "action1 v0 ph1→ph2 +0x44 = 30.0 (FLOAT_8043a120)");
    assert(a.hDecel === 0, "action1 v0 ph1→ph2 +0x4c = 0");
  }

  // --- ph2 active: range-check advances to ph3. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2; // ph2
    a.handlerTimer = 0; // force range-check branch
    (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x: 0, y: 0, z: 50 }; // in range (< 400)
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "action1 v0 ph2 range-check → ph3");
    assert(a.streamSlot === 1, "action1 v0 ph2 advance +0x6ea++ (stream cursor)");
  }

  // --- ph4 recover: B-repress edge + contact → re-arm to next combo hit. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 4; // ph4
    a.inputEdge5d4 = GH.B_REPRESS_EDGE; // B re-press
    a.contactP0 = -1; // swing connected (< 0)
    a.streamSlot = 2;
    root(a);
    assert(a.fbPhaseSlots[0] === 5, "action1 v0 ph4 B-retap+contact → +0x540++ (combo re-arm)");
    assert(a.handlerTimer === GH.ACTIVE_TIMER, "action1 v0 ph4 re-arm +0x558 = 20.0");
    assert(a.hSpeed === GH.HSPEED_SEED, "action1 v0 ph4 re-arm +0x44 = 30.0");
    assert(a.ghComboLatch745 === 0, "action1 v0 ph4 re-arm clears +0x745 latch");
    assert(a.streamSlot === 3, "action1 v0 ph4 re-arm advances +0x6ea");
  }

  // --- ph4 no retap: falls through to recover tail; wallContact → ground idle. ---
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 4;
    a.inputEdge5d4 = 0; // no retap
    a.contactP0 = 0;
    a.wallContact = 1; // FUN_8013dc0c exit trigger
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.hSpeed = 8; a.yVel = 4; a.hDecel = 2; a.gravityCoeff = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    root(a); // ph4 → recover tail → ground idle exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action1 v0 ph4 recover wallContact exit clears +0x73f + strips bits");
  }

  // ==========================================================================
  // Root dispatcher: unsupported actionIndex falls through (no-op).
  // ==========================================================================
  {
    const a = createRomActor() as GhActor;
    configureGoldHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; // no table
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action4 falls through (no bespoke handler)");
  }
}

export const GOLD_HERO_CONSTANTS = GH;
