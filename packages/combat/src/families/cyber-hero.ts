// CYBER HERO family (ctor 0x801d9314) — the bespoke hero-family port.
// Borg: pl0808 (CYBER HERO, borgNumber 0x808). Currently UNREGISTERED in bridge.ts.
//
// The ctor wires root dispatcher FUN_801d94a4 (chunk_0057.c:3044), which indexes
// PTR_FUN_8038f010[+0x580 actionIndex]. A sibling variant dispatcher FUN_801d94e0
// (:3055) indexes PTR_FUN_8038f024[+0x581 variantIndex] (with +0x18dc steerYaw >>= 1).
// The bespoke phase machines live across chunk_0055.c / chunk_0057.c:
//
//   action 1 blink-dash  table @0x8038f0b8 (3 phases, chunk_0057.c — SELF-CONTAINED):
//     ph0 FUN_801d970c (:3146) — blink reposition (×0.95), seed timer 60.0, zero the
//                                four velocity scalars + pose accum, aim yaw/pitch into
//                                +0x54e, arm stream group 3 at slot 0xc, advance +0x540.
//     ph1 FUN_801d9870 (:3199) — drift motion (×0.95), drain +0x558 by dt; advance when
//                                <= 0.0 OR yaw converges, projecting hSpeed/yVel from
//                                +0x54e at magnitude FLOAT_8043bf8c (40.0).
//     ph2 FUN_801d995c (:3232) — active dash: per-frame drag (×0.95, +×0.5 when in 150.0
//                                range), physics FUN_80067310(1.0, lockYaw); B-retap
//                                (contactP1<0 + input flags) re-blinks; wall/ground exit
//                                via zz_006a5a4_ / zz_006a750_(7) + +0x694 = 1.0+dt.
//
//   action 2/3 charge-flurry  table @0x8038a710 (4 phases, chunk_0055.c — config-driven):
//     dispatcher FUN_801ca34c (:4063) indexes the table by +0x540. Phases read a per-move
//     record (param_2) carrying the stream slot, timer seeds, motion scales, and the
//     contact/advance/flurry callbacks. ph0 FUN_801ca388 (:4074) arms group 4 + blink;
//     ph1 FUN_801ca4d4 (:4121) drifts + advances on contactP0>0; ph2 FUN_801ca5e0 (:4153)
//     is the charge-hold loop (drains +0x560, advances on contactP0<0); ph3 FUN_801ca790
//     (:4208) is the recover/exit (drag + air/land return).
//
//   action 4 recovery dash  table @0x8038a6fc (5 phases, chunk_0055.c — config-driven):
//     dispatcher zz_01c9c9c_ (:3826). ph0 FUN_801c9cec (:3840) arms group 3 + blink;
//     ph1 FUN_801c9e58 (:3890) drift; ph2 FUN_801c9f18 (:3918) wall-latch → velocity
//     projection; ph3 FUN_801ca01c (:3953) steer-dash loop with charge-drain; ph4
//     FUN_801ca280 (:4030) exit.
//
// Float constants (read from boot.dol this session via v2f; sdata2 @0x8043bdxx / bx):
//   FLOAT_8043bd18 = 60.0   main timer seed (action 2/3 + 4 setup)
//   FLOAT_8043bd1c = -1.0   zz_004beb8_ stream rate
//   FLOAT_8043bd20 = 0.0    threshold + pose-accum / +0x80c seed
//   FLOAT_8043bd30 = 0.5    slow-damp motion scale (+0x760 gate)
//   FLOAT_8043bd38 = 1.0    FUN_80067310 gravity arg
//   FLOAT_8043bd3c = 0.96   +0x18da steerYaw decay (FUN_801d9418)
//   FLOAT_8043bd40 = 8.0    exit +0x694 seed (action 2/3 + 4)
//   FLOAT_8043bd44 = 120.0  handlerTimer re-seed (action 4 ph3)
//   FLOAT_8043bd48 = 0.9    +0x18da steerYaw decay (action 2/3 ph3)
//   FLOAT_8043bd4c = 3.0    afterimage distance threshold (zz_01ca8c4_)
//   FLOAT_8043bf74 = 0.0    action-1 threshold / zero-scalar
//   FLOAT_8043bf70 = 0.5    action-1 in-range extra drag (FLOAT_8043bf90 = 150.0 gate)
//   FLOAT_8043bf80 = 60.0   action-1 main timer seed
//   FLOAT_8043bf84 = 0.95   action-1 blink + per-frame motion/drag scale
//   FLOAT_8043bf88 = -1.0   action-1 zz_004beb8_ stream rate
//   FLOAT_8043bf8c = 40.0   action-1 velocity-projection magnitude
//   FLOAT_8043bf90 = 150.0  action-1 in-range distance gate
//   FLOAT_8043bf94 = 1.0    action-1 FUN_80067310 gravity arg + exit +0x694 seed
//
// Unsaturated deps (honest approximations / TODO host):
//   * param_2 move records — the per-(action,variant) speeds/timers/callbacks live in
//     command-move data tables not extracted for pl0808. Module-level DEFAULT records
//     carry the structurally-read fields so the machines run end-to-end; a host that
//     resolves the real records overrides via ctx.onCyberHeroRecord.
//   * zz_00677b0_ (ground-collision probe returning int) — approximated by
//     groundSnapRevert's grounded flag (TODO host: exact collision semantics).
//   * zz_006ed8c_(scale) — velocity drag (hSpeed/yVel *= scale), ported inline.
//   * zz_006de44_ (B-charge drain query) — host hook onChargeDrain, default 0.
//   * zz_006d1a8_ / zz_006e39c_ (dual-axis aim into +0x524) — aim-only, no-op (TODO host).
//   * zz_0092dcc_ / zz_00670dc_ / zz_006eddc_ / zz_00b2190_ — no-op (TODO host).
//   * FUN_80066838 / FUN_800668cc (range gates) — host hook onRangeCheck, default false.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { groundSnapRevert, stepTargetPitch, stepTargetYaw } from "../rom/helpers.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ----------------------------------------------------------------------------
// Borg identity.
// ----------------------------------------------------------------------------
const CYBER_HERO_BORG_NUMBER = 0x808;

// ----------------------------------------------------------------------------
// Spawner addresses (named const exports per the family-port contract).
// ----------------------------------------------------------------------------
/** zz_0082824_ @0x80082824 — record-table projectile spawn. */
export const CYBER_HERO_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — per-borg effect spawn. */
export const CYBER_HERO_EFFECT_SPAWNER = 0x800c3be0;
/** zz_016cc24_ @0x8016cc24 — effect-child spawn. */
export const CYBER_HERO_EFFECT_CHILD_SPAWNER = 0x8016cc24;

// ----------------------------------------------------------------------------
// Config constants (DOL-read this session; see header for citations).
// ----------------------------------------------------------------------------
export const CYBER_HERO = {
  /** FLOAT_8043bd18 = 60.0 — action 2/3 + 4 main timer seed. */
  MAIN_TIMER_SEED: 60.0,
  /** FLOAT_8043bd1c = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043bd20 = 0.0 — threshold + zero-scalar / +0x80c seed. */
  THRESHOLD: 0.0,
  /** FLOAT_8043bd30 = 0.5 — slow-damp motion scale (+0x760 < record gate). */
  SLOW_SCALE: 0.5,
  /** FLOAT_8043bd38 = 1.0 — FUN_80067310 gravity arg. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_8043bd40 = 8.0 — exit +0x694 seed (action 2/3 + 4). */
  EXIT_STATE_TIMER: 8.0,
  /** FLOAT_8043bd44 = 120.0 — action-4 ph3 handlerTimer re-seed. */
  FLURRY_WINDOW: 120.0,
  /** FLOAT_8043bd48 = 0.9 — action 2/3 ph3 steerYaw decay. */
  STEER_DECAY_23: 0.9,
  /** FLOAT_8043bd4c = 3.0 — afterimage distance threshold (zz_01ca8c4_). */
  AFTERIMAGE_DIST: 3.0,
  // action-1 dash (chunk_0057.c, sdata2 @0x8043bfxx).
  /** FLOAT_8043bf74 = 0.0 — action-1 threshold / zero-scalar. */
  A1_ZERO: 0.0,
  /** FLOAT_8043bf70 = 0.5 — action-1 in-range extra drag. */
  A1InRange_DRAG: 0.5,
  /** FLOAT_8043bf80 = 60.0 — action-1 main timer seed. */
  A1_MAIN_TIMER: 60.0,
  /** FLOAT_8043bf84 = 0.95 — action-1 blink + per-frame motion/drag scale. */
  A1_MOTION_SCALE: 0.95,
  /** FLOAT_8043bf88 = -1.0 — action-1 stream rate. */
  A1_STREAM_RATE: -1.0,
  /** FLOAT_8043bf8c = 40.0 — action-1 velocity-projection magnitude. */
  A1_SPEED: 40.0,
  /** FLOAT_8043bf90 = 150.0 — action-1 in-range distance gate. */
  A1InRange_GATE: 150.0,
  /** FLOAT_8043bf94 = 1.0 — action-1 physics gravity + exit +0x694 seed. */
  A1_PHYSICS_GRAVITY: 1.0,
  /** +0x5e0 action-mode bits stripped at every exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 position-frozen / airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** Stream mask (all 4 parts). */
  STREAM_MASK: 0xf,
  /** action-1 ph0 stream group (zz_004beb8_(…,0xf,3,…)). */
  A1_STREAM_GROUP: 3,
  /** action-1 ph0 stream slot seed (FUN_801d970c: +0x6ea = 0xc). */
  A1_SLOT_SEED: 0xc,
  /** action 2/3 + 4 stream group (zz_004beb8_(…,0xf,4/3,…)). */
  A23_STREAM_GROUP: 4,
  A4_STREAM_GROUP: 3,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface CyberHeroScratch {
  /** +0x54e: part-pitch/steer yaw used by the velocity projection (cos/sin). */
  chSeed54e?: number;
  /** +0x560: action 2/3 windup/charge timer (record seed; drained each frame). */
  chTimer560?: number;
  /** +0x55c: action 4 sub-timer (record seed). */
  chTimer55c?: number;
  /** +0x542: action 2/3 ph1 contact latch. */
  chFlag542?: number;
  /** +0x54c: action 4 ph2 hit latch / charge cursor. */
  chLatch54c?: number;
  /** +0x745: input/charge flag (set when +0x1d9 status byte != 0). */
  chFlag745?: number;
  /** +0x746: input-edge flag (set when +0x5d4 & 0x40). */
  chFlag746?: number;
  /** +0x6f7: air-dash / phase-mode byte (action 2/3: 0 setup, 2 active). */
  chAirMode6f7?: number;
  /** +0x760: movement speed scalar (slow-damp gate). */
  chSpeedScalar760?: number;
  /** +0x5bc: live status word (charge-hold bit host mirror). */
  statusWord5bc?: number;
}

type ChActor = RomActor & CyberHeroScratch;

function scratchOf(actor: RomActor): ChActor {
  return actor as ChActor;
}

function isAirborne(actor: RomActor): boolean {
  return (actor.controlWord & CYBER_HERO.AIRBORNE_BIT) !== 0;
}

// ----------------------------------------------------------------------------
// Host hooks (extend StreamContext). Defaults model "no target / no charge input"
// — the exact ROM behavior with no lock-on and no B-charge held.
// ----------------------------------------------------------------------------
export interface CyberHeroFamilyCtx extends StreamContext {
  /** FUN_80066838 / FUN_800668cc — target-in-range gate. Default false (no target). */
  onRangeCheck?: (actor: RomActor, distance: number) => boolean;
  /** zz_006de44_ — B-charge drain query; returns frames to consume. Default 0. */
  onChargeDrain?: (actor: RomActor) => number;
  /** Per-move record override (the command-move param_2). Default = DEFAULT records. */
  onCyberHeroRecord?: (actionIndex: number) => CyberHeroMoveRecord | undefined;
}

// ----------------------------------------------------------------------------
// zz_00677b0_ — ground-collision step probe returning int. Approximated by
// groundSnapRevert's grounded flag (TODO host: exact collision semantics).
// ----------------------------------------------------------------------------
function groundStepProbe(actor: RomActor): number {
  return groundSnapRevert(actor) ? 1 : 0;
}

/** zz_006ed8c_(scale, actor) — velocity drag: hSpeed/yVel *= scale. */
function applyVelocityDrag(actor: RomActor, scale: number): void {
  actor.hSpeed *= scale;
  actor.yVel *= scale;
}

/** Shared blink: motion = pos − targetCache; motion ×= scale; pos += motion. */
function applyBlink(actor: RomActor, scale: number): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Per-frame motion drift: motion ×= scale; pos += motion. */
function applyMotionDrift(actor: RomActor, scale: number): void {
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** +0xcc == 0 (no lock target) gates the activeYaw = heading copy. */
function hasLockTarget(actor: RomActor): boolean {
  const t = (actor as RomActor & { lockTarget?: unknown }).lockTarget;
  return t != null;
}

/** zz_006e514_(actor, 0xc0, &+0x54e) — pitch aim into +0x54e. Writes the result
 *  back into the chSeed54e scratch so the velocity projection reads it. */
function aimPitchInto54e(actor: ChActor): void {
  const current = actor.chSeed54e ?? 0;
  const r = stepTargetPitch(actor, 0xc0, current);
  actor.chSeed54e = r.value;
}

// ============================================================================
// ACTION 1 — blink-dash (table @0x8038f0b8). Self-contained (no param_2).
// FUN_801d970c / FUN_801d9870 / FUN_801d995c @ chunk_0057.c.
// ============================================================================

/** Phase 0 — FUN_801d970c @ chunk_0057.c:3146 (89 instrs). */
function action1Phase0(actor: ChActor, ctx: CyberHeroFamilyCtx): void {
  // +0xcc == 0 → +0x5ac = +0x72 (activeYaw = heading).
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading;
  // FUN_80066838(actionSpeedRow, actor) range gate; < 1 → no-target branch.
  const row = actor.actionSpeedRows[actor.prevActionIndex % 3] ?? 0;
  if (!ctx.onRangeCheck?.(actor, row)) {
    actor.fbPhaseSlots[1] = 1;          // +0x541 = 1
    (actor as RomActor & { lockTarget?: unknown }).lockTarget = null; // +0xcc = 0
    actor.lockYaw = actor.heading;      // +0x5ae = +0x72
    actor.activeYaw = actor.heading;    // +0x5ac = +0x72
  }
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.chFlag746 = 0;                  // +0x746 = 0
  actor.chFlag745 = 0;                  // +0x745 = 0
  actor.handlerTimer = CYBER_HERO.A1_MAIN_TIMER; // +0x558 = 60.0
  actor.chSeed54e = 0;                  // +0x54e = 0
  actor.streamSlot = CYBER_HERO.A1_SLOT_SEED;    // +0x6ea = 0xc
  // Zero the four velocity scalars (FLOAT_8043bf74 = 0.0) + pose accum.
  actor.gravityCoeff = CYBER_HERO.A1_ZERO;
  actor.yVel = CYBER_HERO.A1_ZERO;
  actor.hDecel = CYBER_HERO.A1_ZERO;
  actor.hSpeed = CYBER_HERO.A1_ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  stepTargetYaw(actor, 0xc0);           // zz_006d144_(0xc0)
  aimPitchInto54e(actor);               // zz_006e514_(0xc0, &+0x54e)
  // Blink toward +0x5e8 targetCache (×0.95 approach) + ground snap.
  applyBlink(actor, CYBER_HERO.A1_MOTION_SCALE);
  groundStepProbe(actor);               // zz_00677b0_
  // Arm stream group 3 at slot 0xc, then +0x6ea++.
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, CYBER_HERO.STREAM_MASK, CYBER_HERO.A1_STREAM_GROUP, slot, CYBER_HERO.A1_STREAM_RATE);
}

/** Phase 1 — FUN_801d9870 @ chunk_0057.c:3199 (59 instrs). */
function action1Phase1(actor: ChActor, ctx: CyberHeroFamilyCtx): void {
  void ctx;
  if (actor.streamHold1b03 !== 0) {
    tickStream(actor, CYBER_HERO.STREAM_MASK); // zz_004cd24_(0xf) (gated by +0x1b03)
  }
  // motion ×= 0.95; pos += motion; ground snap.
  applyMotionDrift(actor, CYBER_HERO.A1_MOTION_SCALE);
  groundStepProbe(actor);
  aimPitchInto54e(actor);               // zz_006e514_(0xc0, &+0x54e)
  // Drain +0x558 by dt.
  actor.handlerTimer -= actor.dt;
  // Advance when +0x558 <= 0.0 OR zz_006d144_(0xc0) returns nonzero (yaw converged).
  if (actor.handlerTimer <= CYBER_HERO.A1_ZERO || stepTargetYaw(actor, 0xc0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    // Velocity projection from +0x54e at magnitude 40.0.
    const yaw = actor.chSeed54e ?? 0;
    actor.hSpeed = CYBER_HERO.A1_SPEED * projectZ(yaw); // 40 × cos(yaw) (zz_0045238_)
    actor.yVel = CYBER_HERO.A1_SPEED * -projectX(yaw);  // 40 × -sin(yaw) (zz_0045204_)
    // zz_0092dcc_(actor, 0) — TODO(host): unported; no port-side effect.
  }
}

/** Phase 2 — FUN_801d995c @ chunk_0057.c:3232 (124 instrs). */
function action1Phase2(actor: ChActor, ctx: CyberHeroFamilyCtx): void {
  // Input-edge latches.
  if ((actor.inputEdge5d4 & 0x40) !== 0) actor.chFlag746 = 1; // +0x5d4 & 0x40 → +0x746
  if (actor.streamHold1b03 !== 0) actor.chFlag745 = 1;        // +0x1d9 != 0 → +0x745
  tickStream(actor, CYBER_HERO.STREAM_MASK);                  // zz_004cd24_(0xf)
  // B-retap re-blink: contactP1 < 0 AND (+0x746 & +0x745) != 0.
  if (actor.contactP1 < 0 && (((actor.chFlag746 ?? 0) & (actor.chFlag745 ?? 0)) !== 0)) {
    actor.chFlag746 = 0;
    actor.chFlag745 = 0;
    const yaw = actor.chSeed54e ?? 0;
    actor.hSpeed = CYBER_HERO.A1_SPEED * projectZ(yaw);
    actor.yVel = CYBER_HERO.A1_SPEED * -projectX(yaw);
    actor.hDecel = CYBER_HERO.A1_ZERO; // +0x4c = FLOAT_8043bf74
    actor.gravityCoeff = CYBER_HERO.A1_ZERO; // +0x50 = FLOAT_8043bf74
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, CYBER_HERO.STREAM_MASK, CYBER_HERO.A1_STREAM_GROUP, slot, CYBER_HERO.A1_STREAM_RATE);
    return;
  }
  // faceGate (+0x1d10) > 0 → re-aim.
  if (actor.faceGate1d10 > 0) {
    stepTargetYaw(actor, 0xc0);
    aimPitchInto54e(actor);
  }
  // dashStrength (+0x1d0f) < 0 → clear + restore gravityCoeff from descriptor.+0x6c.
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  }
  // Velocity drag ×0.95; extra ×0.5 when in 150.0 range.
  applyVelocityDrag(actor, CYBER_HERO.A1_MOTION_SCALE);
  if (ctx.onRangeCheck?.(actor, CYBER_HERO.A1InRange_GATE)) {
    applyVelocityDrag(actor, CYBER_HERO.A1InRange_DRAG);
  }
  // FUN_80067310(1.0, actor, lockYaw) — physics integration.
  integratePhysics(CYBER_HERO.A1_PHYSICS_GRAVITY, actor, actor.lockYaw);
  const grounded = groundStepProbe(actor); // zz_00677b0_
  // Grounded + contactP0 < 0 → air-style exit (cue 7, +0x694 = 1.0 + dt).
  if (grounded !== 0 && actor.contactP0 < 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = CYBER_HERO.A1_PHYSICS_GRAVITY + actor.dt; // +0x694 = 1.0 + dt
    return;
  }
  // wallContact (+0x1cee) → air knockout return.
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
    romAirKnockoutReturn(actor); // zz_006a5a4_
  }
}

// ============================================================================
// Move-record config (param_2). The ROM phase functions read per-(action,variant)
// speeds/timers/callbacks from a record pointer. The command-move data tables for
// pl0808 are not extracted; these DEFAULT records carry the structurally-read
// fields (verified field-by-field against the decomp) so the machines run. A host
// that resolves the real records overrides via ctx.onCyberHeroRecord.
// ============================================================================

/** Callback shape for the param_2 code-pointer fields (family-local spawners). */
export type CyberHeroCallback = (actor: RomActor) => number | void;

export interface CyberHeroMoveRecord {
  /** *param_2 (int→char) → +0x6ea stream slot seed. */
  streamSlot: number;
  /** (float) param_2[1] / param_2+4 → blink motion scale. */
  motionScale: number;
  /** (short) param_2+1 / param_2+8 → +0x560 / +0x558 timer seed (frame count). */
  timerFrames: number;
  /** (short) param_2+6 / param_2+0xa → +0x54e / +0x54c seed. */
  seed54e?: number;
  seed54c?: number;
  /** (float) param_2+0xc / param_2+0x10 → speed magnitude / motion accel. */
  speed?: number;
  /** (short) param_2+0x14 → +0x558 re-seed (action 4 ph3). */
  flurryFrames?: number;
  /** (short) param_2+0x16 → +0x18dc steerYaw step (action 4 ph3). */
  steerStep?: number;
  /** param_2+0x0c / +0x10 / +0x14 / +0x18 / +0x1c code-ptr callbacks. */
  onContact?: CyberHeroCallback;
  onAdvance?: CyberHeroCallback;
  onFlurry?: CyberHeroCallback;
  onLoop?: CyberHeroCallback;
}

/** Default action 2/3 charge-flurry record (FUN_801ca388 param_2 layout). */
const DEFAULT_A23_RECORD: CyberHeroMoveRecord = {
  streamSlot: 0,
  motionScale: CYBER_HERO.A1_MOTION_SCALE,
  timerFrames: Math.round(CYBER_HERO.MAIN_TIMER_SEED),
  seed54e: 0,
  speed: CYBER_HERO.A1_SPEED,
};

/** Default action 4 recovery record (FUN_801c9cec param_2 layout). */
const DEFAULT_A4_RECORD: CyberHeroMoveRecord = {
  streamSlot: 0,
  motionScale: CYBER_HERO.A1_MOTION_SCALE,
  timerFrames: Math.round(CYBER_HERO.MAIN_TIMER_SEED),
  seed54c: 0,
  speed: CYBER_HERO.A1_SPEED,
  flurryFrames: Math.round(CYBER_HERO.FLURRY_WINDOW),
  steerStep: 0,
};

// ============================================================================
// ACTION 2/3 — charge-flurry (table @0x8038a710). FUN_801ca34c dispatcher indexes
// [FUN_801ca388, FUN_801ca4d4, FUN_801ca5e0, FUN_801ca790] by +0x540.
// ============================================================================

/** Phase 0 — FUN_801ca388 @ chunk_0055.c:4074 (83 instrs). */
function action23Phase0Setup(actor: ChActor, rec: CyberHeroMoveRecord): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fbPhaseSlots[1] = 0;             // +0x541 = 0
  actor.chTimer560 = rec.timerFrames;    // +0x560 = record timer
  actor.chSeed54e = rec.seed54e ?? 0;    // +0x54e = record seed
  actor.chFlag746 = 0;                   // +0x746 = 0
  actor.chFlag745 = 0;                   // +0x745 = 0
  actor.streamSlot = rec.streamSlot;     // +0x6ea = record slot
  actor.chAirMode6f7 = 0;                // +0x6f7 = 0
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading; // +0xcc==0 → +0x5ac=+0x72
  // zz_006d1a8_ / zz_006e39c_ — dual-axis aim into +0x524 (TODO host: aim-only, no-op).
  actor.gravityCoeff = CYBER_HERO.THRESHOLD;
  actor.yVel = CYBER_HERO.THRESHOLD;
  actor.hDecel = CYBER_HERO.THRESHOLD;
  actor.hSpeed = CYBER_HERO.THRESHOLD;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  applyBlink(actor, rec.motionScale);    // blink ×= record motion scale
  groundSnapRevert(actor);               // zz_00679d0_
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;           // +0x6ea++
  startStream(actor, CYBER_HERO.STREAM_MASK, CYBER_HERO.A23_STREAM_GROUP, slot, CYBER_HERO.STREAM_RATE);
}

/** Phase 1 — FUN_801ca4d4 @ chunk_0055.c:4121 (67 instrs). */
function action23Phase1Drift(actor: ChActor, rec: CyberHeroMoveRecord): void {
  if ((actor.inputEdge5d4 & 0x80) !== 0) actor.chFlag746 = 1; // +0x5d4 & 0x80 → +0x746
  tickStream(actor, CYBER_HERO.STREAM_MASK);
  // zz_006d1a8_ / zz_006e39c_ — dual-axis aim (TODO host: no-op).
  rec.onContact?.(actor);                // param_2+0xc callback
  integratePhysics(CYBER_HERO.PHYSICS_GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, lockYaw)
  applyMotionDrift(actor, rec.motionScale);
  groundSnapRevert(actor);               // zz_00679d0_
  // contactP0 > 0 → advance to ph2 (the charge loop).
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.chFlag542 = 0;                 // +0x542 = 0
    actor.chAirMode6f7 = 2;              // +0x6f7 = 2
    rec.onAdvance?.(actor);              // param_2+0x10 callback
  }
}

/** Phase 2 — FUN_801ca5e0 @ chunk_0055.c:4153 (108 instrs). Charge-hold loop. */
function action23Phase2Charge(actor: ChActor, rec: CyberHeroMoveRecord, ctx: CyberHeroFamilyCtx): void {
  if ((actor.inputEdge5d4 & 0x80) !== 0) actor.chFlag746 = 1; // +0x746
  actor.chAirMode6f7 = 2;                // +0x6f7 = 2
  // zz_006de44_(actor, 0xf0f00) — B-charge drain (host hook). Drains +0x54e / +0x560.
  const drain = ctx.onChargeDrain?.(actor) ?? 0;
  if (drain !== 0) {
    let cap = actor.chSeed54e ?? 0;
    if (cap < drain) cap = drain;
    actor.chSeed54e = (actor.chSeed54e ?? 0) - cap;
    actor.chTimer560 = (actor.chTimer560 ?? 0) + cap;
  }
  // zz_006d1a8_ / zz_006e39c_ — dual-axis aim (TODO host: no-op).
  applyMotionDrift(actor, rec.motionScale);
  // dashStrength (+0x1d0f) < 0 → clear + restore gravityCoeff.
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
  }
  integratePhysics(CYBER_HERO.PHYSICS_GRAVITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
  if ((actor.chTimer560 ?? 0) <= CYBER_HERO.THRESHOLD) {
    tickStream(actor, CYBER_HERO.STREAM_MASK);
    // contactP1 < 0 + flurry callback → hold the loop.
    if (actor.contactP1 < 0 && rec.onFlurry && rec.onFlurry(actor) !== 0) {
      return;
    }
    // contactP0 < 0 → advance to ph3 (recover).
    if (actor.contactP0 < 0) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.chAirMode6f7 = 0;            // +0x6f7 = 0
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = descriptor.+0x6c
    }
  } else {
    actor.chTimer560 = (actor.chTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  }
}

/** Phase 3 — FUN_801ca790 @ chunk_0055.c:4208 (recover/exit). */
function action23Phase3Recover(actor: ChActor, ctx: CyberHeroFamilyCtx): void {
  void ctx;
  // +0x18da *= 0.9 (FLOAT_8043bd48 — CONCAT44 int→double coercion idiom).
  actor.steerYaw = Math.trunc((actor.steerYaw ?? 0) * CYBER_HERO.STEER_DECAY_23);
  integratePhysics(CYBER_HERO.PHYSICS_GRAVITY, actor, actor.lockYaw);
  const grounded = groundStepProbe(actor); // zz_00677b0_
  // Grounded + airborne bit + contactP0 < 0 → air exit (cue 7, +0x694 = 8.0 + dt).
  if (grounded !== 0 && isAirborne(actor) && actor.contactP0 < 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = CYBER_HERO.EXIT_STATE_TIMER + actor.dt; // +0x694 = 8.0 + dt
    return;
  }
  tickStream(actor, CYBER_HERO.STREAM_MASK);
  if (actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
    actor.hDecel = CYBER_HERO.THRESHOLD; // +0x4c = FLOAT_8043bd20
    actor.hSpeed = CYBER_HERO.THRESHOLD; // +0x44 = FLOAT_8043bd20
    if (grounded === 0) {
      romAirKnockoutReturn(actor); // zz_006a5a4_
    } else {
      romGroundIdleReturn(actor);  // zz_006a474_
    }
    actor.stateTimer = CYBER_HERO.EXIT_STATE_TIMER + actor.dt; // +0x694 = 8.0 + dt
  }
}

// ============================================================================
// ACTION 4 — recovery dash (table @0x8038a6fc). zz_01c9c9c_ dispatcher indexes
// [FUN_801c9cec, FUN_801c9e58, FUN_801c9f18, FUN_801ca01c, FUN_801ca280] by +0x540.
// ============================================================================

/** Phase 0 — FUN_801c9cec @ chunk_0055.c:3840 (91 instrs). */
function action4Phase0Setup(actor: ChActor, rec: CyberHeroMoveRecord, ctx: CyberHeroFamilyCtx): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  if (!hasLockTarget(actor)) actor.activeYaw = actor.heading; // +0xcc==0 → +0x5ac=+0x72
  // FUN_80066838 range gate (no-target branch when the host gate fails).
  const row = actor.actionSpeedRows[actor.prevActionIndex % 3] ?? 0;
  if (!ctx.onRangeCheck?.(actor, row)) {
    actor.fbPhaseSlots[1] = 1;            // +0x541 = 1
    (actor as RomActor & { lockTarget?: unknown }).lockTarget = null;
    actor.activeYaw = actor.heading;      // +0x5ac = +0x72
  }
  actor.handlerTimer = CYBER_HERO.MAIN_TIMER_SEED; // +0x558 = 60.0
  actor.chSeed54e = 0;                    // +0x54e = 0
  actor.streamSlot = rec.streamSlot;      // +0x6ea = record slot
  actor.gravityCoeff = CYBER_HERO.THRESHOLD;
  actor.yVel = CYBER_HERO.THRESHOLD;
  actor.hDecel = CYBER_HERO.THRESHOLD;
  actor.hSpeed = CYBER_HERO.THRESHOLD;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  stepTargetYaw(actor, 0xc0);             // zz_006d144_(0xc0)
  aimPitchInto54e(actor);                 // zz_006e514_(0xc0, &+0x54e)
  applyBlink(actor, rec.motionScale);     // blink ×= record motion scale
  groundSnapRevert(actor);                // zz_00677b0_
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;            // +0x6ea++
  startStream(actor, CYBER_HERO.STREAM_MASK, CYBER_HERO.A4_STREAM_GROUP, slot, CYBER_HERO.STREAM_RATE);
  actor.accumulator80c = CYBER_HERO.THRESHOLD; // +0x80c = FLOAT_8043bd20
}

/** Phase 1 — FUN_801c9e58 @ chunk_0055.c:3890 (48 instrs). */
function action4Phase1Drift(actor: ChActor, rec: CyberHeroMoveRecord): void {
  if (actor.streamHold1b03 !== 0) tickStream(actor, CYBER_HERO.STREAM_MASK);
  applyMotionDrift(actor, rec.motionScale);
  groundStepProbe(actor);                 // zz_00677b0_
  aimPitchInto54e(actor);                 // zz_006e514_(0xc0, &+0x54e)
  actor.handlerTimer -= actor.dt;         // +0x558 -= dt
  if (actor.handlerTimer <= CYBER_HERO.THRESHOLD || stepTargetYaw(actor, 0xc0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

/** Phase 2 — FUN_801c9f18 @ chunk_0055.c:3918 (65 instrs). Wall-latch + velocity. */
function action4Phase2Latch(actor: ChActor, rec: CyberHeroMoveRecord): void {
  tickStream(actor, CYBER_HERO.STREAM_MASK);
  stepTargetYaw(actor, 0xc0);             // zz_006d144_(0xc0)
  aimPitchInto54e(actor);                 // zz_006e514_(0xc0, &+0x54e)
  applyMotionDrift(actor, rec.motionScale);
  groundStepProbe(actor);                 // zz_00677b0_
  // wallContact (+0x1cee) → advance to ph3 + velocity projection.
  if (actor.wallContact !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = rec.timerFrames; // +0x558 = record timer
    actor.chLatch54c = rec.seed54c ?? 0;  // +0x54c = record seed
    actor.chTimer55c = CYBER_HERO.THRESHOLD; // +0x55c = 0.0
    actor.motion.x = CYBER_HERO.THRESHOLD;   // +0x38 = 0.0
    actor.hSpeed = rec.speed ?? CYBER_HERO.A1_SPEED; // +0x40 = record speed magnitude
    const yaw = actor.chSeed54e ?? 0;
    actor.hSpeed = (rec.speed ?? CYBER_HERO.A1_SPEED) * projectZ(yaw); // 40 × cos
    actor.yVel = (rec.speed ?? CYBER_HERO.A1_SPEED) * -projectX(yaw);  // 40 × -sin
  }
}

/** Phase 3 — FUN_801ca01c @ chunk_0055.c:3953 (153 instrs). Steer-dash loop. */
function action4Phase3Steer(actor: ChActor, rec: CyberHeroMoveRecord, ctx: CyberHeroFamilyCtx): void {
  // zz_006de44_(actor, 0xf0f00) — B-charge drain (host hook). Drains +0x54c / +0x558.
  const drain = ctx.onChargeDrain?.(actor) ?? 0;
  if (drain !== 0) {
    let cap = actor.chLatch54c ?? 0;
    if (cap < drain) cap = drain;
    actor.chLatch54c = (actor.chLatch54c ?? 0) - cap;
    actor.handlerTimer = (actor.handlerTimer ?? 0) + cap;
  }
  // +0x55c sub-timer drain; re-seed from record.flurryFrames + cue 9 on expiry.
  actor.chTimer55c = (actor.chTimer55c ?? 0) - actor.dt;
  if ((actor.chTimer55c ?? 0) <= CYBER_HERO.THRESHOLD) {
    actor.chTimer55c = rec.flurryFrames ?? CYBER_HERO.FLURRY_WINDOW;
    ctx.onPlayCue?.(actor, 9);            // zz_00f036c_(actor, 9)
  }
  // +0x18dc += record.steerStep × dt (the steer-dash integration).
  actor.steerYaw = Math.trunc(((actor.steerYaw ?? 0) + (rec.steerStep ?? 0) * actor.dt));
  tickStream(actor, CYBER_HERO.STREAM_MASK);
  stepTargetYaw(actor, 0xc0);             // zz_006d144_(0xc0)
  aimPitchInto54e(actor);                 // zz_006e514_(0xc0, &+0x54e)
  // motion accel: +0x38 += record.speed × dt (clamped to +0x40).
  const mag = rec.speed ?? CYBER_HERO.A1_SPEED;
  actor.motion.x = Math.min(actor.hSpeed, actor.motion.x + mag * actor.dt);
  const yaw = actor.chSeed54e ?? 0;
  actor.hSpeed = (rec.speed ?? CYBER_HERO.A1_SPEED) * projectZ(yaw);
  actor.yVel = (rec.speed ?? CYBER_HERO.A1_SPEED) * -projectX(yaw);
  // slow-damp when +0x760 < record gate.
  if ((actor.chSpeedScalar760 ?? 0) < rec.motionScale) {
    actor.motion.x *= CYBER_HERO.SLOW_SCALE;
  }
  integratePhysics(CYBER_HERO.PHYSICS_GRAVITY, actor, actor.lockYaw);
  groundStepProbe(actor);                 // zz_00677b0_
  actor.handlerTimer -= actor.dt;         // +0x558 -= dt
  if (actor.handlerTimer <= CYBER_HERO.THRESHOLD) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = CYBER_HERO.FLURRY_WINDOW; // +0x558 = 120.0 (FLOAT_8043bd44)
    rec.onLoop?.(actor);                  // param_2+0x18 callback
    actor.steerYaw = 0;                   // +0x18dc = 0
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;          // +0x6ea++
    startStream(actor, CYBER_HERO.STREAM_MASK, CYBER_HERO.A4_STREAM_GROUP, slot, CYBER_HERO.STREAM_RATE);
  }
  // zz_00b22f4_(actor) — afterimage step (host-side hostic; no port-side effect).
}

/** Phase 4 — FUN_801ca280 @ chunk_0055.c:4030 (51 instrs). Exit. */
function action4Phase4Exit(actor: ChActor): void {
  tickStream(actor, CYBER_HERO.STREAM_MASK);
  integratePhysics(CYBER_HERO.PHYSICS_GRAVITY, actor, actor.lockYaw);
  const grounded = groundStepProbe(actor); // zz_00677b0_
  if (grounded !== 0 && actor.wallContact !== 0) {
    actor.housekeeping73f = 0;
    actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = CYBER_HERO.EXIT_STATE_TIMER + actor.dt; // +0x694 = 8.0 + dt
  } else if (actor.wallContact === 0) {
    actor.handlerTimer -= actor.dt;       // +0x558 -= dt
    if (actor.handlerTimer <= CYBER_HERO.THRESHOLD) {
      actor.housekeeping73f = 0;
      actor.controlWord = actor.controlWord & ~CYBER_HERO.ACTION_MODE_BITS;
      romAirKnockoutReturn(actor); // zz_006a5a4_
    }
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_801d94a4 indexes PTR_FUN_8038f010[+0x580].
// ----------------------------------------------------------------------------
export function createCyberHeroRootAction(
  ctx: CyberHeroFamilyCtx,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 1: {
        // Action 1 blink-dash (table @0x8038f0b8).
        const phase = actor.fbPhaseSlots[0] ?? 0;
        switch (phase) {
          case 0: action1Phase0(actor, ctx); return;
          case 1: action1Phase1(actor, ctx); return;
          case 2: action1Phase2(actor, ctx); return;
          default: return;
        }
      }
      case 2:
      case 3: {
        // Action 2/3 charge-flurry (table @0x8038a710).
        const rec = ctx.onCyberHeroRecord?.(actor.actionIndex) ?? DEFAULT_A23_RECORD;
        const phase = actor.fbPhaseSlots[0] ?? 0;
        switch (phase) {
          case 0: action23Phase0Setup(actor, rec); return;
          case 1: action23Phase1Drift(actor, rec); return;
          case 2: action23Phase2Charge(actor, rec, ctx); return;
          case 3: action23Phase3Recover(actor, ctx); return;
          default: return;
        }
      }
      case 4: {
        // Action 4 recovery dash (table @0x8038a6fc).
        const rec = ctx.onCyberHeroRecord?.(4) ?? DEFAULT_A4_RECORD;
        const phase = actor.fbPhaseSlots[0] ?? 0;
        switch (phase) {
          case 0: action4Phase0Setup(actor, rec, ctx); return;
          case 1: action4Phase1Drift(actor, rec); return;
          case 2: action4Phase2Latch(actor, rec); return;
          case 3: action4Phase3Steer(actor, rec, ctx); return;
          case 4: action4Phase4Exit(actor); return;
          default: return;
        }
      }
      default:
        return; // action 0 (generic dash) and unmapped actions fall through.
    }
  };
}

/** Configure a freshly-spawned CYBER HERO (pl0808). Stamps the borg number and
 *  wires the bespoke action-1 blink-dash + action-2/3 charge-flurry + action-4
 *  recovery-dash machines. */
export function configureCyberHeroFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = CYBER_HERO_BORG_NUMBER;
  actor.rootAction = createCyberHeroRootAction(ctx as CyberHeroFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ----------------------------------------------------------------------------
// cos/sin of a BAM16 yaw — local mirrors of physics.projectZ / projectX so the
// velocity-projection reads exactly match the ROM's zz_0045238_ / zz_0045204_.
// ----------------------------------------------------------------------------
function projectZ(bam: number): number {
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return Math.cos((s / 0x10000) * Math.PI * 2);
}
function projectX(bam: number): number {
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return Math.sin((s / 0x10000) * Math.PI * 2);
}

// ============================================================================
// Self-tests. Mirror the rom.selfcheck.ts / victory-king style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

function makeCtx(opts: {
  onRangeCheck?: (d: number) => boolean;
  onChargeDrain?: () => number;
  onFamilyProjectile?: (addr: number, type: number) => void;
  onAllocateResource?: () => boolean;
  record?: CyberHeroMoveRecord;
} = {}): CyberHeroFamilyCtx {
  const ctx: CyberHeroFamilyCtx = {};
  if (opts.onRangeCheck) ctx.onRangeCheck = (_a, d) => opts.onRangeCheck!(d);
  if (opts.onChargeDrain) ctx.onChargeDrain = () => opts.onChargeDrain!();
  if (opts.onFamilyProjectile) {
    const sink = opts.onFamilyProjectile;
    ctx.onFamilyProjectile = (_a, addr, type) => sink(addr, type);
  }
  if (opts.onAllocateResource) ctx.onAllocateResource = () => opts.onAllocateResource!();
  if (opts.record) ctx.onCyberHeroRecord = () => opts.record;
  return ctx;
}

export function runCyberHeroSelfTests(assert: AssertFn): void {
  // ==========================================================================
  // ACTION 1 — blink-dash (table @0x8038f0b8).
  // ==========================================================================
  console.log("[cyber-hero] action 1 blink-dash (FUN_801d970c/9870/995c):");

  // --- ph0 setup: blink, timer=60, streamSlot=13, velocity scalars zeroed. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    assert(a.borgNumber === CYBER_HERO_BORG_NUMBER, "borgNumber stamped 0x808 (CYBER HERO)");
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0x1000;
    a.pos = { x: 100, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action1 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, CYBER_HERO.A1_MAIN_TIMER), "+0x558 = 60.0 (FLOAT_8043bf80)");
    assert(a.streamSlot === CYBER_HERO.A1_SLOT_SEED + 1, "+0x6ea = 0xc + advance = 13");
    assert(a.chSeed54e === 0, "+0x54e seeded 0");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action1 ph0 zeroes the four velocity scalars (FLOAT_8043bf74)");
    assert(a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      "action1 ph0 clears pose accumulators");
    // blink: motion = (pos−target)×0.95 added → x = 100 + 95 = 195.
    assert(approxEq(a.pos.x, 195.0), "action1 ph0 blink: pos.x = 195 (×FLOAT_8043bf84=0.95)");
    assert(approxEq(a.motion.x, 95.0), "action1 ph0 motion.x = 95");
    assert(a.lockYaw === a.heading, "action1 ph0 no-target: +0x5ae = +0x72 (lockYaw = heading)");
  }

  // --- ph1: motion drift + timer drain → advance + velocity projection. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.motion.x = 95.0;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; // one frame from expiry
    a.chSeed54e = 0;      // yaw 0 → cos=1, sin=0
    root(a); // 1.0 − 1 = 0 ≤ 0 → advance
    assert(a.fbPhaseSlots[0] === 2, "action1 ph1 advances to ph2 when +0x558 <= 0.0");
    assert(approxEq(a.motion.x, 95.0 * CYBER_HERO.A1_MOTION_SCALE),
      "action1 ph1 motion *= FLOAT_8043bf84 (0.95)");
    // Velocity projection: hSpeed = 40×cos(0) = 40; yVel = 40×-sin(0) = 0.
    assert(approxEq(a.hSpeed, CYBER_HERO.A1_SPEED), "action1 ph1 hSpeed = 40×cos(0) = 40 (FLOAT_8043bf8c)");
    assert(approxEq(a.yVel, 0.0), "action1 ph1 yVel = 40×-sin(0) = 0");
  }

  // --- ph1 yaw-converged advance branch (zz_006d144_ returns nonzero). ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0; a.lockYaw = 0;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 50.0; // not expired
    a.chSeed54e = 0;
    // stepTargetYaw converges immediately when heading already equals desired (0).
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 ph1 advances when zz_006d144_(0xc0) converges");
  }

  // --- ph2: velocity drag + physics + wall exit (air knockout return). ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[6 * 2 + 1] = 24;
    a.fbPhaseSlots[0] = 2;
    a.hSpeed = 40; a.yVel = 0; a.hDecel = 0; a.gravityCoeff = 0;
    a.chSeed54e = 0;
    a.wallContact = 1; // exit trigger
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: false }), isSupported: () => true };
    root(a);
    assert(approxEq(a.hSpeed, 40 * CYBER_HERO.A1_MOTION_SCALE), "action1 ph2 drag: hSpeed *= 0.95");
    assert(a.ubState === 24, "action1 ph2 wall exit: air return dispatches upper cue 6 (→ state 24)");
    assert((a.controlWord & 0x3) === 0, "action1 ph2 exit strips +0x5e0 action bits");
  }

  // --- ph2 grounded + contactP0<0: cue 7 air-style exit, +0x694 = 1.0+dt. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[7 * 2 + 1] = 30;
    a.fbPhaseSlots[0] = 2;
    a.hSpeed = 40; a.yVel = 0; a.hDecel = 0; a.gravityCoeff = 0;
    a.chSeed54e = 0;
    a.contactP0 = -1; // grounded + contactP0<0 → air-style exit
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.ubState === 30, "action1 ph2 grounded+contact<0: dispatches upper cue 7 (→ state 30)");
    assert(approxEq(a.stateTimer, CYBER_HERO.A1_PHYSICS_GRAVITY + 1), "+0x694 = 1.0 + dt (FLOAT_8043bf94)");
  }

  // --- ph2 in-range extra drag (FUN_800668cc(150.0) true → ×0.5 more). ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx({ onRangeCheck: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.hSpeed = 40; a.yVel = 10; a.hDecel = 0; a.gravityCoeff = 0;
    a.chSeed54e = 0;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: false }), isSupported: () => true };
    root(a);
    // 40 × 0.95 (drag) × 0.5 (in-range) = 19.
    assert(approxEq(a.hSpeed, 40 * CYBER_HERO.A1_MOTION_SCALE * CYBER_HERO.A1InRange_DRAG),
      "action1 ph2 in-range extra drag ×0.5 (FLOAT_8043bf70, gate FLOAT_8043bf90=150.0)");
  }

  // ==========================================================================
  // ACTION 2/3 — charge-flurry (table @0x8038a710).
  // ==========================================================================
  console.log("[cyber-hero] action 2/3 charge-flurry (FUN_801ca388/ca4d4/ca5e0/ca790):");

  // --- ph0 setup: timer560, blink, group-4 stream arm. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0x2000;
    a.pos = { x: 50, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2/3 ph0 advances to ph1");
    assert(a.fbPhaseSlots[1] === 0, "action2/3 ph0 seeds +0x541 = 0");
    assert(a.chAirMode6f7 === 0, "action2/3 ph0 +0x6f7 = 0");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action2/3 ph0 zeroes the four velocity scalars");
    assert(approxEq(a.pos.x, 50 + 50 * CYBER_HERO.A1_MOTION_SCALE),
      "action2/3 ph0 blink ×= record motion scale (0.95)");
    assert(a.streamSlot === DEFAULT_A23_RECORD.streamSlot + 1, "action2/3 ph0 streamSlot = record + advance");
  }

  // --- ph1: contactP0>0 → advance to ph2 (+0x6f7=2). ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; // hit → advance
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action2/3 ph1 contactP0>0 advances to ph2");
    assert(a.chAirMode6f7 === 2, "action2/3 ph1→ph2 sets +0x6f7 = 2");
    assert(a.chFlag542 === 0, "action2/3 ph1→ph2 clears +0x542");
  }

  // --- ph2: timer drain; advance to ph3 on contactP0<0. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.chTimer560 = 0.0; // already expired → advance-check branch runs
    a.contactP0 = -1;   // advance trigger
    a.descriptor = { header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(0),
      handlerData6c: 1.25, subtypePartCommand: new Int8Array(0), buttonLiveFlag: new Int8Array(0),
      defaultHand0: 0, defaultHand1: 0 };
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "action2/3 ph2 advances to ph3 when contactP0<0");
    assert(a.chAirMode6f7 === 0, "action2/3 ph2→ph3 sets +0x6f7 = 0");
    assert(approxEq(a.gravityCoeff, 1.25), "action2/3 ph2 restores gravityCoeff from descriptor.+0x6c");
  }

  // --- ph2 timer not expired: drains +0x560 by dt, stays in ph2. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 2;
    a.chTimer560 = 30.0; // well above threshold
    a.contactP0 = 0;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action2/3 ph2 stays when +0x560 > 0.0");
    assert(approxEq(a.chTimer560, 29.0), "action2/3 ph2 drains +0x560 by dt");
  }

  // --- ph3 recover: wall exit zeroes hSpeed/hDecel + land return. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[0] = 0;
    a.fbPhaseSlots[0] = 3;
    a.hSpeed = 30; a.yVel = 4; a.hDecel = 2; a.gravityCoeff = 1;
    a.wallContact = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert((a.controlWord & 0x3) === 0, "action2/3 ph3 exit strips +0x5e0 action bits");
    assert(a.hSpeed === 0 && a.hDecel === 0, "action2/3 ph3 exit zeroes hSpeed/hDecel (FLOAT_8043bd20)");
    assert(approxEq(a.stateTimer, CYBER_HERO.EXIT_STATE_TIMER + 1), "+0x694 = 8.0 + dt (FLOAT_8043bd40)");
  }

  // ==========================================================================
  // ACTION 4 — recovery dash (table @0x8038a6fc).
  // ==========================================================================
  console.log("[cyber-hero] action 4 recovery dash (FUN_801c9cec/9e58/9f18/ca01c/ca280):");

  // --- ph0 setup: timer=60, blink, group-3 stream, scalars zeroed. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.heading = 0x800;
    a.pos = { x: 20, y: 0, z: 0 };
    a.hSpeed = 7; a.yVel = 3; a.hDecel = 1; a.gravityCoeff = 4;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action4 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, CYBER_HERO.MAIN_TIMER_SEED), "+0x558 = 60.0 (FLOAT_8043bd18)");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action4 ph0 zeroes the four velocity scalars");
    assert(approxEq(a.pos.x, 20 + 20 * CYBER_HERO.A1_MOTION_SCALE), "action4 ph0 blink ×= 0.95");
  }

  // --- ph1: timer drain → advance on expiry. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.heading = 0; a.lockYaw = 0;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; // one frame from expiry
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action4 ph1 advances to ph2 when +0x558 <= 0.0");
  }

  // --- ph2: wall latch → advance + velocity projection. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.wallContact = 1;
    a.chSeed54e = 0; // cos=1, sin=0
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "action4 ph2 wall latch advances to ph3");
    assert(approxEq(a.hSpeed, CYBER_HERO.A1_SPEED), "action4 ph2 hSpeed = 40×cos(0) = 40 (record speed)");
    assert(approxEq(a.yVel, 0.0), "action4 ph2 yVel = 40×-sin(0) = 0");
  }

  // --- ph3: +0x558 drain → advance to ph4 + re-seed 120.0. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.fbPhaseSlots[0] = 3;
    a.handlerTimer = 1.0; // one frame from re-seed
    a.chSeed54e = 0;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.fbPhaseSlots[0] === 4, "action4 ph3 advances to ph4 when +0x558 <= 0.0");
    assert(approxEq(a.handlerTimer, CYBER_HERO.FLURRY_WINDOW), "+0x558 re-seeded to 120.0 (FLOAT_8043bd44)");
  }

  // --- ph4: wallContact exit (cue 7) when grounded. ---
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[7 * 2 + 1] = 12;
    a.fbPhaseSlots[0] = 4;
    a.handlerTimer = 50.0; // not expired → wallContact path
    a.wallContact = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.physicsRuntime = { clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: true }), isSupported: () => true };
    root(a);
    assert(a.ubState === 12, "action4 ph4 wall exit dispatches upper cue 7 (→ state 12)");
    assert((a.controlWord & 0x3) === 0, "action4 ph4 exit strips +0x5e0 action bits");
    assert(approxEq(a.stateTimer, CYBER_HERO.EXIT_STATE_TIMER + 1), "+0x694 = 8.0 + dt (FLOAT_8043bd40)");
  }

  // ==========================================================================
  // Root dispatch + fallthrough.
  // ==========================================================================
  console.log("[cyber-hero] root dispatcher (FUN_801d94a4 → PTR_FUN_8038f010):");
  {
    const a = createRomActor() as ChActor;
    configureCyberHeroFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; // generic dash — no bespoke handler
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action0 falls through (no bespoke handler)");
    a.actionIndex = 5; // unmapped
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "unmapped actionIndex falls through");
  }
}
