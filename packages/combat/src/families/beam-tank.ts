// BEAM TANK (pl0c02, ctor 0x80105144) family — bespoke 3-action port.
// @audit-ported pl0c02 action=0 variants=0,1
// @audit-ported pl0c02 action=1 variants=0
// @audit-ported pl0c02 action=2 variants=0,1
//
// Root dispatcher zz_01052c8_ @0x801052c8 (chunk_0029.c:678):
//   `(*(code *)(&PTR_zz_0105304__80321fa8)[*(char *)(actor+0x580)])();`
//   [0] zz_0105304_ (action 0), [1] zz_01055ec_ (action 1), [2] zz_0105f30_ (action 2).
//
// ACTION 0 — B volley. Dispatcher zz_0105304_ → PTR_FUN_804344a8[+0x581]:
//   v0 → zz_010533c_ → PTR_zz_0105378__80321fb4[+0x540]
//   v1 → zz_0105494_ → PTR_zz_01054d0__80321fc4[+0x540]
//   Both 4-phase machines are the same burst-volley shape:
//     ph0 (0x80105378/0x801054d0) setup: +0x540++, +0x548 = 10.
//     ph1 (0x80105390/0x801054e8) wait: +0x548--; zz_0106270_ (turret-aim probe);
//         on expiry zero the four hardpoint flags +0x144/+0x146/+0x148/+0x14a.
//     ph2 (0x801053f4/0x8010554c) fire: zz_0106270_; zz_0106398_ (ammo-gated
//         burst loop) → when it returns true advance +0x540, +0x548 = 0x1e.
//     ph3 (0x80105444/0x8010559c) cooldown: +0x548--; on expiry clear +0x73f,
//         strip +0x5e0, exit via zz_006a668_(kind 0x10).
//   zz_0106398_ (chunk_0029.c:1418): B-held (0x5b4&0x200 → +0x144=1) armed the burst
//   counter; per 5-frame cycle consume ammo slot 0 → spawn zz_0082824_(+0x14a + 0x15),
//   rotating +0x14a 0→3; returns 1 when 3 (or 5 with +0x144) shots have fired.
//
// ACTION 1 — B-charge. Dispatcher zz_01055ec_ → PTR_FUN_804344b0[+0x581]:
//   v0 → zz_0105624_ → PTR_zz_01056e4__80321fd4[+0x540] (5 phases).
//   Wrapper halves +0x1910 (turret roll channel) + clears +0xcc if +0x541.
//   ph0 (0x801056e4): +0x540++, +0x694 = 50+dt, range gate (+0x868 row, then
//       +0x770×0.5), zero scalars, +0x558 = 60, stream group 3 slot 0 (ground) /
//       1 (air), face 0xc0.
//   ph1 (0x80105818): stream tick; +0x558 -= +0x768; on expiry advance, re-seed
//       +0x558 (60 or 15 if +0x541), +0x709 = 4, arm the beam fire (hSpeed=40·cos/
//       sin(steerYaw) airborne or 40 ground, afterimage).
//   ph2 (0x801059e8): stream tick; +0x558 -= +0x768; in-range gate (500) or expiry
//       → advance, +0x558 = 30, +0x548 = DAT_804344bc (0), SFX 0xa7.
//   ph3 (0x80105b8c): stream tick; charge-drain (zz_006de44_(0xf0f00)) refunds
//       +0x558 while +0x548 > 0; on expiry advance, +0x542 = 1, +0x558 = 50,
//       +0x4c = -(+0x44/10) ground / 0 air + re-arm stream, +0x709 = 0.
//   ph4 (0x80105d5c): stream tick; hSpeed ×= (0.06·(1−dt) + 0.94) airborne;
//       +0x1910 turret-roll decay; +0x558 -= +0x768; on expiry zero turret
//       channels, +0x694 = dt, clear +0x73f/+0x5e0/+0x709, ground-idle or air-fall.
//
// ACTION 2 — X-special. Dispatcher zz_0105f30_ → PTR_FUN_804344c0[+0x581]:
//   v0 → zz_0105f68_ → PTR_zz_0105fa4__80321fe8[+0x540]
//   v1 → zz_01060ec_ → PTR_zz_0106128__80321ff8[+0x540]
//   Both 4-phase: ph0 +0x540++, +0x548=10; ph1 +0x548-- (or zz_01062cc_ turret
//   aim) → advance; ph2 zz_0106028_/zz_01061ac_ ammo gate slot 2 → spawn
//   zz_00c3be0_(8/9), +0x548 = 0x1e; ph3 cooldown exit via zz_006a668_(0x10).
//
// Exit helper zz_006a668_(kind 0x10) — see cyber-machine.ts cmXPhase1: reset the
// shot channels (+0x1d9c/+0x1db2/+0x1db3), arm the exact weapon-part animation
// (zz_0048d54_ kind 0x10), dispatch the current upper-body cue to full body.
//
// Float constants (boot.dol, sdata2 @0x80439418..):
//   FLOAT_80439418 = 0.1     wrapper channel blend t (0x80105624)
//   FLOAT_8043941c = -24576  wrapper turret-roll lerp slope
//   FLOAT_80439420 = 1.0     generic unity
//   FLOAT_80439428 = 176.0   s16→float magic
//   FLOAT_80439430 = 50.0    ph0 +0x694 seed; ph3 exit +0x558 re-seed
//   FLOAT_80439434 = 0.5     range-gate scale (+0x770 × 0.5); stream rates
//   FLOAT_80439438 = 0.0     zero
//   FLOAT_8043943c = 60.0    ph0/1 +0x558 seed
//   FLOAT_80439440 = -1.0    stream rate
//   FLOAT_80439444 = 15.0    ph1 +0x541 re-seed
//   FLOAT_80439448 = 40.0    ph1/2 beam speed coefficient
//   FLOAT_8043944c = -0.5    ph1/2 beam decel coefficient
//   FLOAT_80439450 = 0.3     airborne ph1/2 stream rate
//   FLOAT_80439454 = 0.8     steerYaw decay blend base
//   FLOAT_80439458 = 0.2     steerYaw decay blend slope
//   FLOAT_8043945c = 500.0   ph2 in-range gate
//   FLOAT_80439460 = 30.0    ph2 +0x558 re-seed
//   FLOAT_80439464 = 4.0     ph3 charge-drain refund step
//   FLOAT_80439468 = 10.0    ph3 ground +0x4c = -(+0x44/10)
//   FLOAT_8043946c = 0.94    ph4 airborne hSpeed decay base
//   FLOAT_80439470 = 0.06    ph4 airborne hSpeed decay slope

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysicsFullClamp, projectX, projectZ } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { allocateWeapon, groundSnapRevert, stepTargetYaw, toS16 } from "../rom/helpers.js";
import { armWeaponPartAnimation } from "./shared-aimed-shot-x.js";

/** Borg number for BEAM TANK. */
export const BEAM_TANK_BORG_NUMBER = 0xc02;

// ----------------------------------------------------------------------------
// Config constants (DOL-read).
// ----------------------------------------------------------------------------
export const BEAM_TANK = {
  /** FLOAT_80439438 = 0.0 — zero scalar. */
  ZERO: 0.0,
  /** FLOAT_8043943c = 60.0 — action-1 ph0/1 +0x558 seed. */
  A1_PH0_TIMER: 60.0,
  /** FLOAT_80439430 = 50.0 — action-1 ph0 +0x694 seed + ph3 exit +0x558 re-seed. */
  A1_PH0_STATE_TIMER: 50.0,
  /** FLOAT_80439444 = 15.0 — action-1 ph1 +0x541 re-seed. */
  A1_PH1_TARGETED_TIMER: 15.0,
  /** FLOAT_80439448 = 40.0 — action-1 ph1/2 beam speed coefficient. */
  A1_BEAM_SPEED: 40.0,
  /** FLOAT_8043944c = -0.5 — action-1 ph1/2 beam decel coefficient. */
  A1_BEAM_DECEL: -0.5,
  /** FLOAT_80439450 = 0.3 — action-1 airborne stream rate (ph1/2/3). */
  A1_AIR_STREAM_RATE: 0.3,
  /** FLOAT_8043945c = 500.0 — action-1 ph2 in-range gate. */
  A1_PH2_RANGE_GATE: 500.0,
  /** FLOAT_80439460 = 30.0 — action-1 ph2 +0x558 re-seed. */
  A1_PH2_TIMER: 30.0,
  /** FLOAT_80439464 = 4.0 — action-1 ph3 charge-drain refund step. */
  A1_PH3_REFUND: 4.0,
  /** FLOAT_80439468 = 10.0 — action-1 ph3 ground +0x4c = -(+0x44/10). */
  A1_PH3_DECEL_DIVISOR: 10.0,
  /** FLOAT_8043946c = 0.94 — action-1 ph4 airborne hSpeed decay base. */
  A1_PH4_DECAY_BASE: 0.94,
  /** FLOAT_80439470 = 0.06 — action-1 ph4 airborne hSpeed decay slope. */
  A1_PH4_DECAY_SLOPE: 0.06,
  /** FLOAT_80439440 = -1.0 — stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_80439434 = 0.5 — range-gate scale (+0x770 × 0.5). */
  RANGE_GATE_SCALE: 0.5,
  /** FLOAT_80439418 = 0.1 — action-1 wrapper turret-roll blend t. */
  WRAPPER_BLEND_T: 0.1,
  /** FLOAT_8043941c = -24576.0 — action-1 wrapper turret-roll lerp slope. */
  WRAPPER_ROLL_SLOPE: -24576.0,
  /** +0x548 turret-cycle seed (action-0/2 ph0). */
  CYCLE_SEED: 10,
  /** +0x548 cooldown seed (action-0 ph2 / action-2 ph2). */
  COOLDOWN_SEED: 0x1e,
  /** +0x6ef B-held burst gate (action-0 ph2). */
  BURST_GATE: 1,
  /** zz_006a668_ exit kind (0x10). */
  EXIT_KIND: 0x10,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 airborne/position-frozen bit. */
  AIRBORNE_BIT: 0x40,
  /** +0x5b4 B-held status bit (0x200). */
  B_HELD_BIT: 0x200,
  /** +0x1d9 & 0x10 — hit-react gate (action-1 ph0 0x144 seed). */
  HIT_REACT_MASK: 0x10,
  /** zz_0082824_ @0x80082824 — shot spawner (action 0). */
  SHOT_HELPER: 0x80082824,
  /** zz_00c3be0_ @0x800c3be0 — effect spawner (action 2). */
  EFFECT_SPAWNER: 0x800c3be0,
  /** action-0 shot record base (zz_0082824_(+0x14a + 0x15)). */
  A0_SHOT_BASE: 0x15,
  /** action-2 effect records (zz_00c3be0_(8) + (9)). */
  A2_EFFECT_RECORDS: [8, 9],
  /** action-0/2 shot-count wrap (3). */
  A0_SHOT_WRAP: 3,
  /** action-0 burst count (3; 5 when +0x144 armed). */
  A0_BURST_COUNT: 3,
  A0_BURST_LONG_COUNT: 5,
  /** action-0 ph2 hardpoint-interval countdown (5 frames). */
  A0_FIRE_INTERVAL: 5,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface BeamTankScratch {
  /** +0x548: turret cycle / cooldown counter (int, action-0/1/2). */
  btCycle548?: number;
  /** +0x144: B-held armed latch (action-0 burst extension). */
  btArmed144?: number;
  /** +0x146: hardpoint fire-interval countdown (5 → 0). */
  btFireInterval146?: number;
  /** +0x148: burst counter (shots fired this action). */
  btBurstCount148?: number;
  /** +0x14a: shot-record rotation cursor (& 3). */
  btShotCursor14a?: number;
  /** +0x543: ground/air stream flag (0 ground, 1 air). */
  btAir543?: number;
  /** +0x542: charge-committed flag (action-1 ph3). */
  btChargeCommitted542?: number;
  /** +0x541: one-shot target-invalid latch. */
  btInvalid541?: number;
  /** +0x709: contact-slow / landing flag (action-1). */
  btLanding709?: number;
  /** +0x1910: turret-roll channel (action-1 wrapper halves + decays). */
  btTurretRoll1910?: number;
  /** +0x190a: turret-roll mirror channel. */
  btTurretRoll190a?: number;
  /** +0x1dd: target-eligibility byte; bit 0x80 forces acceptance. */
  btEligibility1dd?: number;
  /** +0x1d9: part hit-react byte (action-1 ph0 0x144 seed). */
  btHitReact1d9?: number;
  /** +0x6ee: stream-slot base (action-1 ph0 stream slot). */
  btSlotBase6ee?: number;
}

type BtActor = RomActor & BeamTankScratch;

function scratchOf(actor: RomActor): BtActor {
  return actor as BtActor;
}

// ----------------------------------------------------------------------------
// Shared exit helper — zz_006a668_(kind 0x10). Mirrors cyber-machine cmXPhase1:
// reset the shot channels, arm the exact weapon-part animation (kind), dispatch
// the current upper-body cue to full body.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~BEAM_TANK.ACTION_MODE_BITS;
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  // zz_0048d54_(param_10 = 0x10) — arm the exact weapon-part animation.
  armWeaponPartAnimation(actor, BEAM_TANK.EXIT_KIND);
  dispatchFullBodyCue(actor, actor.ubCue);
}

// ----------------------------------------------------------------------------
// zz_0106270_ @ chunk_0029.c:1371 — turret-aim probe. FUN_8006cc90(0.5, actor, 2,
// 1, {0x7fff,0x8000,0xffff,0}) — a part-2 stream/animation tick. The ROM returns
// 1 when the tick produced a nonzero event. PORT APPROXIMATION: without resident
// banks the tick is a no-op, so this returns 1 only when a host event is set
// (mirror of the vehicle-family's no-op tick). Action-0 ph1/2 and action-2 ph1
// gate the phase advance on it.
// ----------------------------------------------------------------------------
function turretAimProbe(actor: RomActor, ctx: StreamContext): number {
  // FUN_8006cc90(0.5, actor, 2, 1, tbl) — host presentation hook. The port models
  // the "event fired" result as tickStream's return (false without banks → 0).
  const fired = tickStream(actor, 2, ctx);
  return fired ? 1 : 0;
}

// ----------------------------------------------------------------------------
// zz_01062cc_ @ chunk_0029.c:1389 — turret-aligned probe (action-2 ph1 / action-1
// charge). Runs zz_0106270_ then two more FUN_8006cc90 ticks (parts 9/10). Returns
// true only when all three report an event — the turret is fully aligned.
// PORT APPROXIMATION: same no-op tick semantics (returns false without banks).
// ----------------------------------------------------------------------------
function turretAligned(actor: RomActor, ctx: StreamContext): boolean {
  turretAimProbe(actor, ctx);
  tickStream(actor, 9, ctx);
  tickStream(actor, 10, ctx);
  return false;
}

// ----------------------------------------------------------------------------
// zz_0106398_ @ chunk_0029.c:1418 — action-0 burst fire. Returns 1 (done) when the
// shot budget is exhausted or ammo is denied; else consumes ammo slot 0, spawns
// zz_0082824_(+0x14a + 0x15), rotates +0x14a, returns 0.
// ----------------------------------------------------------------------------
function burstFire(actor: BtActor, ctx: StreamContext): number {
  if ((actor.statusWord5b4 & BEAM_TANK.B_HELD_BIT) !== 0) actor.btArmed144 = 1;
  if ((actor.btFireInterval146 ?? 0) === 0) {
    actor.btFireInterval146 = BEAM_TANK.A0_FIRE_INTERVAL;
    actor.btBurstCount148 = (actor.btBurstCount148 ?? 0) + 1;
    if (!allocateWeapon(actor, ctx, 0, 1, true)) return 1; // ammo denied → done
    ctx.onFamilyProjectile?.(actor, BEAM_TANK.SHOT_HELPER, (actor.btShotCursor14a ?? 0) + BEAM_TANK.A0_SHOT_BASE);
    actor.btShotCursor14a = ((actor.btShotCursor14a ?? 0) + 1) % BEAM_TANK.A0_SHOT_WRAP;
    const budget = (actor.btArmed144 ?? 0) === 0 ? BEAM_TANK.A0_BURST_COUNT : BEAM_TANK.A0_BURST_LONG_COUNT;
    // ROM: `if (+0x144 == 0) { if (2 < +0x148) return 1 } else { +0x144=0; if (4 < +0x148) return 1 }`
    // — the done edge fires on the shot that reaches budget (count >= budget).
    if (budget <= (actor.btBurstCount148 ?? 0)) return 1;
    actor.btArmed144 = 0;
  } else {
    actor.btFireInterval146 = (actor.btFireInterval146 ?? 0) - 1;
  }
  return 0;
}

// ============================================================================
// ACTION 0 — B volley.
// ============================================================================

function a0Phase0Setup(actor: BtActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.btCycle548 = BEAM_TANK.CYCLE_SEED;                   // +0x548 = 10
}

function a0Phase1Wait(actor: BtActor, ctx: StreamContext): void {
  actor.btCycle548 = (actor.btCycle548 ?? 0) - 1;
  turretAimProbe(actor, ctx);
  if ((actor.btCycle548 ?? 0) < 1) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.btArmed144 = 0;
    actor.btFireInterval146 = 0;
    actor.btBurstCount148 = 0;
    actor.btShotCursor14a = 0;
  }
}

function a0Phase2Fire(actor: BtActor, ctx: StreamContext): void {
  turretAimProbe(actor, ctx);
  if (burstFire(actor, ctx) !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.btCycle548 = BEAM_TANK.COOLDOWN_SEED;               // +0x548 = 0x1e
  }
}

function a0Phase3Cooldown(actor: BtActor): void {
  actor.btCycle548 = (actor.btCycle548 ?? 0) - 1;
  if ((actor.btCycle548 ?? 0) < 1) exitAction(actor);
}

/** Action-0 root — dispatcher zz_0105304_ → PTR_FUN_804344a8[+0x581] (v0/v1 same shape). */
function beamTankAction0(actor: BtActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a0Phase0Setup(actor); break;
    case 1: a0Phase1Wait(actor, ctx); break;
    case 2: a0Phase2Fire(actor, ctx); break;
    case 3: a0Phase3Cooldown(actor); break;
    default: break;
  }
}

// ============================================================================
// ACTION 1 — B-charge.
// ============================================================================

/** Wrapper zz_0105624_ @ chunk_0029.c:871: halve +0x1910, clear +0xcc if +0x541,
 *  then phase table; also lerps +0x1910/+0x190a toward FLOAT_8043941c (as a
 *  rotation-velocity falloff) while +0x542 == 0. */
function a1Wrapper(actor: BtActor): void {
  actor.btTurretRoll1910 = toS16(actor.btTurretRoll1910 ?? 0) >> 1;
  actor.btTurretRoll190a = toS16(actor.btTurretRoll190a ?? 0) >> 1;
  if (actor.btInvalid541 !== 0) actor.visibilityTarget = null;
  if ((actor.btChargeCommitted542 ?? 0) === 0) {
    // +0x1910 = lerp(current, FLOAT_8043941c, FLOAT_80439418 × dt); mirror to +0x190a.
    const cur = toS16(actor.btTurretRoll1910 ?? 0);
    const t = BEAM_TANK.WRAPPER_BLEND_T * actor.dt;
    const next = Math.trunc(cur + (BEAM_TANK.WRAPPER_ROLL_SLOPE - cur) * t);
    actor.btTurretRoll1910 = toS16(next);
    actor.btTurretRoll190a = toS16(next);
  }
}

function a1Phase0Setup(actor: BtActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.stateTimer = BEAM_TANK.A1_PH0_STATE_TIMER + actor.dt; // +0x694 = 50 + dt
  actor.btInvalid541 = 0;
  actor.btLanding709 = 0;
  actor.btChargeCommitted542 = 0;
  // Range gate: row(+0x868) then +0x770 × 0.5. Fail → +0x541 = 1, +0xcc = 0.
  const row = actor.actionSpeedRows[(actor.cmdButton ?? 0) % 3] ?? BEAM_TANK.A1_PH0_TIMER;
  const inRange = tnRangeGate(actor, row, BEAM_TANK.RANGE_GATE_SCALE);
  if (!inRange) {
    actor.btInvalid541 = 1;
    actor.visibilityTarget = null;
    actor.activeYaw = actor.heading;
  }
  actor.gravityCoeff = BEAM_TANK.ZERO;
  actor.yVel = BEAM_TANK.ZERO;
  actor.hSpeed = BEAM_TANK.ZERO;
  actor.handlerTimer = BEAM_TANK.A1_PH0_TIMER; // +0x558 = 60
  const airborne = (actor.controlWord & BEAM_TANK.AIRBORNE_BIT) !== 0;
  actor.btAir543 = airborne ? 1 : 0;
  const slot = (actor.btSlotBase6ee ?? 0) + (airborne ? 1 : 0);
  startStream(actor, 0xf, 3, slot, BEAM_TANK.STREAM_RATE);
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  actor.accumulator80c = BEAM_TANK.ZERO;
}

function a1Phase1Beam(actor: BtActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.aimRateScale; // +0x558 -= +0x768
  if (actor.handlerTimer > BEAM_TANK.ZERO) return;
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = actor.btInvalid541 !== 0 ? BEAM_TANK.A1_PH1_TARGETED_TIMER : BEAM_TANK.A1_PH0_TIMER;
  actor.btLanding709 = 4; // +0x709 = 4
  const yaw = actor.steerYaw; // +0x18da
  if ((actor.btAir543 ?? 0) === 0) {
    actor.hSpeed = BEAM_TANK.A1_BEAM_SPEED;      // +0x44 = 40
    actor.hDecel = BEAM_TANK.A1_BEAM_DECEL;      // +0x4c = -0.5
    groundDrag(actor, ctx);
    ctx.onFamilyProjectile?.(actor, 0x800b2190, 0); // zz_00b2190_(0) afterimage
  } else {
    // Airborne beam: 40·cos/sin(steerYaw), decel -0.5·cos/sin, full-clamp physics.
    actor.hSpeed = BEAM_TANK.A1_BEAM_SPEED * projectZ(yaw);
    actor.yVel = BEAM_TANK.A1_BEAM_SPEED * -projectX(yaw);
    actor.hDecel = BEAM_TANK.A1_BEAM_DECEL * projectZ(yaw);
    actor.gravityCoeff = BEAM_TANK.A1_BEAM_DECEL * -projectX(yaw);
    integratePhysicsFullClamp(1.0, actor, actor.lockYaw); // zz_0067458_(1.0)
    const grounded = groundSnapRevert(actor);
    if (grounded) {
      actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * BEAM_TANK.A1_PH4_DECAY_BASE);
      ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
    }
  }
  actor.accumulator80c = BEAM_TANK.ZERO;
}

function a1Phase2Charge(actor: BtActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.aimRateScale; // +0x558 -= +0x768
  const inRange = tnRangeGate(actor, BEAM_TANK.A1_PH2_RANGE_GATE, 1);
  if (actor.handlerTimer > BEAM_TANK.ZERO && !inRange) {
    beamDrift(actor, ctx);
    return;
  }
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = BEAM_TANK.A1_PH2_TIMER;               // +0x558 = 30
  actor.btCycle548 = 0;                                      // DAT_804344bc = 0
  ctx.onPlayCue?.(actor, 0xa7); // zz_00f036c_(0xa7)
  beamDrift(actor, ctx);
}

function a1Phase3Drain(actor: BtActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // zz_006de44_(0xf0f00) — charge-drain query; while +0x548 > 0 refund +0x558 by 4.
  const drain = actor.btCycle548 ?? 0;
  if (drain > 0) {
    actor.handlerTimer += BEAM_TANK.A1_PH3_REFUND; // +0x558 += 4
    actor.btCycle548 = drain - 1;
  }
  beamDrift(actor, ctx);
  actor.handlerTimer -= actor.aimRateScale; // +0x558 -= +0x768
  if (actor.handlerTimer > BEAM_TANK.ZERO) return;
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.btChargeCommitted542 = 1;
  actor.handlerTimer = BEAM_TANK.A1_PH0_STATE_TIMER;         // +0x558 = 50
  if ((actor.btAir543 ?? 0) === 0) {
    actor.hDecel = -(actor.hSpeed / BEAM_TANK.A1_PH3_DECEL_DIVISOR);
    startStream(actor, 0xf, 0, 0, BEAM_TANK.STREAM_RATE); // zz_004beb8_(g0 s0, 10, 1)
  } else {
    actor.hDecel = BEAM_TANK.ZERO;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
    startStream(actor, 0xf, 0, 0, BEAM_TANK.STREAM_RATE);
    actor.controlWord |= BEAM_TANK.AIRBORNE_BIT; // +0x5e0 |= 0x40
  }
  actor.btLanding709 = 0;
}

function a1Phase4Exit(actor: BtActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if ((actor.btAir543 ?? 0) === 0) {
    groundDrag(actor, ctx);
    ctx.onFamilyProjectile?.(actor, 0x800b2190, 0); // zz_00b22f4_ afterimage
  } else {
    // hSpeed ×= (0.06·(1−dt) + 0.94); full-clamp physics.
    actor.hSpeed *= (BEAM_TANK.A1_PH4_DECAY_SLOPE * (1 - actor.dt) + BEAM_TANK.A1_PH4_DECAY_BASE);
    integratePhysicsFullClamp(1.0, actor, actor.lockYaw);
    const grounded = groundSnapRevert(actor);
    if (grounded) {
      actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * BEAM_TANK.A1_PH4_DECAY_BASE);
      ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
      actor.btLanding709 = 1;
    }
  }
  // +0x1910 roll decay toward 0.
  if ((actor.btChargeCommitted542 ?? 0) !== 0 && (actor.btTurretRoll1910 ?? 0) !== 0) {
    const cur = toS16(actor.btTurretRoll1910 ?? 0);
    const next = Math.trunc(cur - cur / Math.max(actor.handlerTimer, 1));
    actor.btTurretRoll1910 = toS16(next);
    actor.btTurretRoll190a = toS16(next);
  }
  actor.handlerTimer -= actor.aimRateScale; // +0x558 -= +0x768
  if (actor.handlerTimer > BEAM_TANK.ZERO) return;
  actor.btTurretRoll1910 = 0;
  actor.btTurretRoll190a = 0;
  actor.stateTimer = actor.dt; // +0x694 = dt
  actor.housekeeping73f = 0;
  actor.controlWord &= ~BEAM_TANK.ACTION_MODE_BITS;
  actor.btLanding709 = 0;
  if ((actor.btAir543 ?? 0) === 0) {
    actor.gravityCoeff = BEAM_TANK.ZERO;
    actor.yVel = BEAM_TANK.ZERO;
    actor.hDecel = BEAM_TANK.ZERO;
    actor.hSpeed = BEAM_TANK.ZERO;
    romGroundIdleReturn(actor); // zz_006a474_
  } else {
    romAirKnockoutReturn(actor); // zz_006a5a4_
  }
}

/** zz_00670dc_(actor, +0x5ae) — ground-drag physics (approximation). */
function groundDrag(actor: RomActor, ctx: StreamContext): void {
  void ctx;
  integratePhysicsFullClamp(1.0, actor, actor.lockYaw); // zz_0067458_(1.0)
  groundSnapRevert(actor);                              // zz_00677b0_
}

/** Shared action-1 drift tail (used by ph1/2/3): ground drag + afterimage, or the
 *  airborne beam-drift projection + full-clamp physics. */
function beamDrift(actor: BtActor, ctx: StreamContext): void {
  if ((actor.btAir543 ?? 0) === 0) {
    groundDrag(actor, ctx);
    ctx.onFamilyProjectile?.(actor, 0x800b2190, 0); // zz_00b22f4_ afterimage
  } else {
    tickStream(actor, 0xf, ctx); // FUN_8006cc90(0.3, actor, 1, 0, &DAT_804344b4)
    const yaw = actor.steerYaw;
    actor.hSpeed = BEAM_TANK.A1_BEAM_SPEED * projectZ(yaw);
    actor.yVel = BEAM_TANK.A1_BEAM_SPEED * -projectX(yaw);
    actor.hDecel = BEAM_TANK.A1_BEAM_DECEL * projectZ(yaw);
    actor.gravityCoeff = BEAM_TANK.A1_BEAM_DECEL * -projectX(yaw);
    integratePhysicsFullClamp(1.0, actor, actor.lockYaw);
    const grounded = groundSnapRevert(actor);
    if (grounded) {
      actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * BEAM_TANK.A1_PH4_DECAY_BASE);
      ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
    }
  }
}

/** FUN_80066838(range, actor) — target-in-range gate (host hook). Default true. */
function tnRangeGate(actor: RomActor, range: number, scale: number): boolean {
  void range; void scale;
  // The +0x770 distance mirror + eligibility byte are host-supplied; the port
  // treats an active visibility target as in-range (cyber-hero convention).
  return actor.visibilityTarget !== null;
}

/** Action-1 root — dispatcher zz_01055ec_ → PTR_FUN_804344b0[+0x581] (v0 only). */
function beamTankAction1(actor: BtActor, ctx: StreamContext): void {
  actor.btAir543 = (actor.controlWord & BEAM_TANK.AIRBORNE_BIT) !== 0 ? 1 : 0;
  a1Wrapper(actor);
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a1Phase0Setup(actor); break;
    case 1: a1Phase1Beam(actor, ctx); break;
    case 2: a1Phase2Charge(actor, ctx); break;
    case 3: a1Phase3Drain(actor, ctx); break;
    case 4: a1Phase4Exit(actor, ctx); break;
    default: break;
  }
}

// ============================================================================
// ACTION 2 — X-special.
// ============================================================================

/** Action-2 root — dispatcher zz_0105f30_ → PTR_FUN_804344c0[+0x581] (v0/v1 same shape). */
function beamTankAction2(actor: BtActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0:
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.btCycle548 = BEAM_TANK.CYCLE_SEED;                  // +0x548 = 10
      break;
    case 1:
      actor.btCycle548 = (actor.btCycle548 ?? 0) - 1;
      if ((actor.btCycle548 ?? 0) < 1 || turretAligned(actor, ctx)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.btArmed144 = 0;
        actor.btFireInterval146 = 0;
        actor.btBurstCount148 = 0;
        actor.btShotCursor14a = 0;
      }
      break;
    case 2:
      turretAligned(actor, ctx);
      if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
        for (const rec of BEAM_TANK.A2_EFFECT_RECORDS) {
          ctx.onFamilyProjectile?.(actor, BEAM_TANK.EFFECT_SPAWNER, rec); // zz_00c3be0_(8/9)
        }
      }
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.btCycle548 = BEAM_TANK.COOLDOWN_SEED;               // +0x548 = 0x1e
      break;
    case 3:
      actor.btCycle548 = (actor.btCycle548 ?? 0) - 1;
      if ((actor.btCycle548 ?? 0) < 1) exitAction(actor);
      break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — zz_01052c8_ indexes PTR_zz_0105304__80321fa8[+0x580].
// ----------------------------------------------------------------------------
export function createBeamTankRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: beamTankAction0(actor, ctx); return;
      case 1: beamTankAction1(actor, ctx); return;
      case 2: beamTankAction2(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned BEAM TANK (pl0c02). */
export function configureBeamTankFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = BEAM_TANK_BORG_NUMBER;
  actor.rootAction = createBeamTankRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const BEAM_TANK_CONSTANTS = BEAM_TANK;

// ============================================================================
// Self-tests — mirror the teleport-ninja / panther-vehicle style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runBeamTankSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // --- configure stamps borgNumber + wires bespoke rootAction. ---
  {
    const a = createRomActor() as BtActor;
    configureBeamTankFamily(a, makeCtx());
    assert(a.borgNumber === 0xc02, "pl0c02 borgNumber stamped 0xc02");
    assert(a.rootAction !== null, "beam-tank bespoke rootAction wired");
  }

  // --- action 0: ph0 setup (+0x540++, +0x548=10), ph1 wait, ph2 fire, ph3 exit. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as BtActor;
    configureBeamTankFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.aimRateScale = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances +0x540");
    assert(a.btCycle548 === BEAM_TANK.CYCLE_SEED, "action0 ph0 seeds +0x548 = 10");
    // ph1: wait 10 cycles → advance.
    for (let i = 0; i < 10; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 2, "action0 ph1 advances to ph2 after 10 frames");
    // ph2: 3 shots. Fire cadence: interval +0x146 starts 0 → shot 1 (call 1), then
    // 5 decrements → shot 2 (call 7), 5 more → shot 3 (call 13) which also returns
    // done (budget 3) → advance to ph3 on the same call.
    for (let i = 0; i < 13; i += 1) root(a);
    assert(shots.length === 3, `action0 ph2 fires 3 shots (got ${shots.length})`);
    assert(shots[0]!.addr === BEAM_TANK.SHOT_HELPER && shots[0]!.type === 0x15
        && shots[1]!.type === 0x16 && shots[2]!.type === 0x17,
      `action0 ph2 shots zz_0082824_(0x15,0x16,0x17) (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 3, "action0 ph2 advances to ph3 on burst completion");
    assert(a.btCycle548 === BEAM_TANK.COOLDOWN_SEED, "action0 ph2 seeds +0x548 = 0x1e");
    // ph3: cooldown 30 → exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 30; i += 1) root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph3 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 2: ph0 setup, ph1 wait, ph2 spawn effects, ph3 exit. ---
  {
    const spawned: Shot[] = [];
    const a = createRomActor() as BtActor;
    configureBeamTankFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => spawned.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 ph0 advances +0x540");
    for (let i = 0; i < 10; i += 1) root(a); // ph1 wait
    assert(a.fbPhaseSlots[0] === 2, "action2 ph1 advances to ph2");
    root(a); // ph2 fire
    assert(spawned.length === 2 && spawned[0]!.addr === BEAM_TANK.EFFECT_SPAWNER
        && spawned[0]!.type === 8 && spawned[1]!.type === 9,
      `action2 ph2 spawns zz_00c3be0_(8,9) (got ${JSON.stringify(spawned)})`);
    assert(a.fbPhaseSlots[0] === 3, "action2 ph2 advances to ph3");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 30; i += 1) root(a); // ph3 cooldown
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action2 ph3 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 1: ph0 setup → ph1 beam → ph2 charge → ph3 drain → ph4 exit. ---
  {
    const a = createRomActor() as BtActor;
    configureBeamTankFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1; a.aimRateScale = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action1 ph0 advances +0x540");
    assert(a.handlerTimer === BEAM_TANK.A1_PH0_TIMER, "action1 ph0 seeds +0x558 = 60.0");
    // ph1: drain 60 → advance to ph2.
    for (let i = 0; i < 60; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 ph1 advances to ph2 when +0x558 <= 0");
    // ph2: drain 30 → advance to ph3.
    for (let i = 0; i < 30; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 3, "action1 ph2 advances to ph3 when +0x558 <= 0");
    // ph3: drain 50 → advance to ph4.
    for (let i = 0; i < 50; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 4, "action1 ph3 advances to ph4 when +0x558 <= 0");
    // ph4: drain 50 → exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 50; i += 1) root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action1 ph4 exits (clears +0x73f, strips +0x5e0)");
  }
}

/** Test context builder (mirrors teleport-ninja's makeCtx). */
function makeCtx(opts: {
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
  onPlayCue?: () => void;
} = {}): StreamContext {
  const ctx: StreamContext = {};
  if (opts.onFamilyProjectile) ctx.onFamilyProjectile = opts.onFamilyProjectile;
  if (opts.onPlayCue) ctx.onPlayCue = () => opts.onPlayCue!();
  return ctx;
}
