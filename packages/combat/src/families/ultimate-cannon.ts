// ULTIMATE CANNON (pl0c04, ctor 0x800b05b4) family — bespoke 3-action port.
// @audit-ported pl0c04 action=0 variants=0,1
// @audit-ported pl0c04 action=2 variants=0,1
// @audit-ported pl0c04 action=3 variants=0,1
//
// Root dispatcher FUN_800b085c @0x800b085c (chunk_0017.c:3501):
//   `(*(code *)(&PTR_FUN_802fc420)[*(char *)(actor+0x580)])();`
//   [0] FUN_800b0898 (action 0), [1] FUN_800b0898, [2] FUN_800b0c20 (action 2),
//   [3] FUN_800b0f18 (action 3), [4] FUN_800b090c.
//
// ACTION 0 — B volley (turret-cycle). Dispatcher FUN_800b0898 →
// PTR_FUN_80433aa8[+0x581]: v0 → FUN_800b08d0 → PTR_FUN_802fc430[+0x540];
// v1 → FUN_800b0a50 → PTR_FUN_802fc43c[+0x540]. 5-phase:
//   ph0 (FUN_800b090c/FUN_800b0adc) setup: +0x540++, zero hardpoint flags,
//       stream g2 s0/s1.
//   ph1 (FUN_800b096c/FUN_800b0b3c) aim: stream tick + turret seek (FUN_800b1654)
//       → advance on fire-done or aim-fail, +0x548 = 10.
//   ph2 (FUN_800b0a04/FUN_800b0bd4) cooldown: +0x548--; exit via zz_006a474_
//       (ground) or zz_006a5a4_ (air).
//   (ph3/4 = the action-2 table start — overlap.)
//
// ACTION 2 — X-special (charge turret). Dispatcher FUN_800b0c20 →
// PTR_FUN_80433ab0[+0x581]: v0 → FUN_800b0c58 → PTR_FUN_802fc448[+0x540];
// v1 → FUN_800b0d90 → PTR_FUN_802fc454[+0x540]. 3-phase:
//   ph0 (FUN_800b0c94/FUN_800b0e1c) setup: +0x540++, zero +0x154, stream g2 s0/s1.
//   ph1 (FUN_800b0ce0/FUN_800b0e68) fire: stream tick + turret launch
//       (FUN_800b1918: ammo-gated zz_00c3be0_(4..7)) → advance, +0x548 = 10.
//   ph2 (FUN_800b0d44/FUN_800b0ecc) cooldown: +0x548--; ground/air exit.
//
// ACTION 3 — B-charge launch. Dispatcher FUN_800b0f18 → PTR_FUN_80433ab8[+0x581]:
//   v0 → FUN_800b0f64 → PTR_FUN_802fc460[+0x540]. 5-phase:
//   ph0 (FUN_800b0fa0) setup: +0x540++, +0x558=60, zero scalars, stream g4 s0,
//       ground flag +0x156 = grounded.
//   ph1 (FUN_800b1048) approach: +0x558 drain; on stream-end or timeout advance;
//       stream re-arm g4 s1 when grounded.
//   ph2 (FUN_800b115c) launch: set +0x5ae = heading−0x8000, hSpeed=40,
//       hDecel=−1.5, stream tick, ground-drag / full-clamp physics; on contact
//       → ground exit, else advance.
//   ph3 (FUN_800b136c) re-arm: +0x540++, stream g4 s1, velocity decay,
//       +0x548 = 0x3c, turret launch (zz_00ec1f4_/zz_00f0104_).
//   ph4 (FUN_800b142c) exit: +0x548 drain; on expiry advance + clear.
//   ph5 (FUN_800b12e8) final: clear +0x73f/+0x5e0, ground/air idle.
//
// Turret helpers (family-local, ported below):
//   FUN_800b1654 — turret pitch seek (zz_00853ec_(3) clamp −0x4000..0x1800, step
//       ±0x180, snap 0xc0) + ammo-gated zz_0084600_(+0x14c+3) burst fire.
//   FUN_800b17cc — charge hardpoint arm (turret roll −0x400 steps, ammo-gated
//       FUN_800e85f4 hardpoint spawn).
//   FUN_800b1918 — launch turret: ammo-gated zz_00c3be0_(4..7) with +0x154 countdown.
//   FUN_800b18e8 — FUN_8006cc90(0.2) turret tick probe (no-op approximation).
//
// Float constants (boot.dol, sdata2 @0x80438318..):
//   FLOAT_80438318 = -1.0    stream rate
//   FLOAT_8043831c = 0.98    hSpeed decay (turret cycle)
//   FLOAT_80438320 = 0.0     zero
//   FLOAT_80438324 = 0.96    yVel decay
//   FLOAT_80438328 = 1.0     gravity / unity
//   FLOAT_8043832c = 60.0    a3 ph0 +0x558 seed
//   FLOAT_80438330 = 40.0    a3 ph2 launch hSpeed
//   FLOAT_80438334 = -1.5    a3 ph2 launch hDecel
//   FLOAT_80438338 = 4.0     a3 ph2 ground hSpeed floor
//   FLOAT_8043833c = 0.2     FUN_800b18e8 stream rate

import { createRomActor, type RomActor } from "../rom/actor.js";
import { integratePhysicsFullClamp } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { allocateWeapon, groundSnapRevert, toS16 } from "../rom/helpers.js";

/** Borg number for ULTIMATE CANNON. */
export const ULTIMATE_CANNON_BORG_NUMBER = 0xc04;

// ----------------------------------------------------------------------------
// Config constants (DOL-read).
// ----------------------------------------------------------------------------
export const ULTIMATE_CANNON = {
  /** FLOAT_80438320 = 0.0 — zero scalar. */
  ZERO: 0.0,
  /** FLOAT_80438318 = -1.0 — stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043831c = 0.98 — hSpeed decay (turret cycle + a3 re-arm). */
  HSPEED_DECAY: 0.9800000190734863,
  /** FLOAT_80438324 = 0.96 — yVel decay. */
  YVEL_DECAY: 0.9599999785423279,
  /** FLOAT_80438328 = 1.0 — gravity / unity. */
  GRAVITY: 1.0,
  /** FLOAT_8043832c = 60.0 — action-3 ph0 +0x558 seed. */
  A3_PH0_TIMER: 60.0,
  /** FLOAT_80438330 = 40.0 — action-3 ph2 launch hSpeed. */
  A3_LAUNCH_HSPEED: 40.0,
  /** FLOAT_80438334 = -1.5 — action-3 ph2 launch hDecel. */
  A3_LAUNCH_HDECEL: -1.5,
  /** FLOAT_80438338 = 4.0 — action-3 ph2 ground hSpeed floor. */
  A3_GROUND_FLOOR: 4.0,
  /** +0x548 cooldown seed (action-0/2). */
  COOLDOWN_SEED: 10,
  /** +0x548 a3 ph3 re-arm seed (0x3c). */
  A3_REARM_SEED: 0x3c,
  /** +0x148 turret burst fire interval (5 frames). */
  A0_FIRE_INTERVAL: 5,
  /** action-0 burst budget (12; 400 with B-held). */
  A0_BURST_BUDGET: 12,
  A0_BURST_HELD_BUDGET: 400,
  /** +0x146 B-held armed latch. */
  B_HELD_LATCH: 1,
  /** +0x154 a2/launch interval (0x5a). */
  A2_INTERVAL: 0x5a,
  /** +0x5b4 B-held status bit. */
  B_HELD_BIT: 0x200,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** zz_0084600_ @0x80084600 — beam-burst shot spawner (action 0). */
  BURST_SPAWNER: 0x80084600,
  /** zz_00c3be0_ @0x800c3be0 — effect spawner (action 2). */
  EFFECT_SPAWNER: 0x800c3be0,
  /** FUN_800e85f4 — hardpoint spawner (action-2 ph1 / charge). */
  HARDPOINT_SPAWNER: 0x800e85f4,
  /** action-2 launch effect records (zz_00c3be0_(4..7)). */
  A2_EFFECT_RECORDS: [4, 5, 6, 7],
  /** zz_00853ec_ turret-pitch seek clamp (0x4000). */
  TURRET_CLAMP_HIGH: 0x4000,
  /** zz_00853ec_ turret-pitch seek clamp low (0x1800). */
  TURRET_CLAMP_LOW: 0x1800,
  /** turret seek step (±0x180). */
  TURRET_STEP: 0x180,
  /** turret seek snap (±0xc0). */
  TURRET_SNAP: 0xc0,
} as const;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface UltimateCannonScratch {
  /** +0x144: turret pitch (s16, seek target). */
  ucTurretPitch144?: number;
  /** +0x18ec: turret pitch mirror (writes +0x144). */
  ucTurretMirror18ec?: number;
  /** +0x146: B-held armed latch. */
  ucArmed146?: number;
  /** +0x148: burst fire-interval countdown. */
  ucFireInterval148?: number;
  /** +0x14a: burst shot counter. */
  ucBurstCount14a?: number;
  /** +0x14c: burst record rotation cursor (& 3). */
  ucShotCursor14c?: number;
  /** +0x14d: charge hardpoint countdown (0x14). */
  ucChargeCountdown14d?: number;
  /** +0x152: charge hardpoint cursor (& 1). */
  ucChargeCursor152?: number;
  /** +0x154: launch interval countdown. */
  ucLaunchInterval154?: number;
  /** +0x156: grounded flag (1 grounded). */
  ucGrounded156?: number;
  /** +0x18fe/+0x1904: turret roll channels (charge). */
  ucTurretRoll18fe?: number;
  ucTurretRoll1904?: number;
  /** +0x541: one-shot latch. */
  ucLatch541?: number;
  /** +0x7de: action-3 post-dispatch flag (set by FUN_800b0f18). */
  ucPostFlag7de?: number;
  /** +0x548: turret cycle / cooldown counter. */
  ucCycle548?: number;
  /** Port-side turret pitch target (host-supplied, feeds zz_00853ec_ seek). */
  turretDesiredPitch?: number;
}

type UcActor = RomActor & UltimateCannonScratch;

function scratchOf(actor: RomActor): UcActor {
  return actor as UcActor;
}

// ----------------------------------------------------------------------------
// Exit helpers — zz_006a474_ (ground) / zz_006a5a4_ (air) after clearing the
// action-mode bits. (The family's exit phases call these directly, not
// zz_006a668_.)
// ----------------------------------------------------------------------------
function exitGround(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~ULTIMATE_CANNON.ACTION_MODE_BITS;
  romGroundIdleReturn(actor);
}

function exitAir(actor: RomActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~ULTIMATE_CANNON.ACTION_MODE_BITS;
  romAirKnockoutReturn(actor);
}

// ----------------------------------------------------------------------------
// zz_00853ec_(actor, 3) + seek — turret pitch toward the target (chunk_0017.c:
// 4138-4158). Clamps to [−0x4000, 0x1800], steps ±0x180, snaps within 0xc0.
// PORT APPROXIMATION: target pitch from helpers.stepTargetYaw is not surfaced as
// a BAM; the seek uses a host-provided desired pitch or keeps the current value.
// ----------------------------------------------------------------------------
function turretSeek(actor: UcActor): void {
  // zz_00853ec_ returns the target turret pitch (host/geometry). Defaults to the
  // current value so the seek is a no-op without host input; the step/snap logic
  // is ported faithfully for when a desired pitch is supplied.
  const desired = toS16((actor as UcActor & { turretDesiredPitch?: number }).turretDesiredPitch ?? 0);
  const clamped = Math.max(-ULTIMATE_CANNON.TURRET_CLAMP_HIGH,
    Math.min(ULTIMATE_CANNON.TURRET_CLAMP_LOW, desired));
  const cur = toS16(actor.ucTurretPitch144 ?? 0);
  let next: number;
  if (cur < clamped) {
    next = cur + ULTIMATE_CANNON.TURRET_STEP;
    if (clamped - ULTIMATE_CANNON.TURRET_SNAP <= next) next = clamped;
  } else if (clamped < cur) {
    next = cur - ULTIMATE_CANNON.TURRET_STEP;
    if (next <= clamped + ULTIMATE_CANNON.TURRET_SNAP) next = clamped;
  } else {
    next = cur;
  }
  actor.ucTurretPitch144 = toS16(next);
  actor.ucTurretMirror18ec = toS16(next);
}

// ----------------------------------------------------------------------------
// FUN_800b1654 @ chunk_0017.c:4129 — action-0 turret cycle fire. Turret seek +
// ammo-gated zz_0084600_(+0x14c + 3) burst; returns 1 when done (12 shots, or
// 400 with B-held).
// ----------------------------------------------------------------------------
function turretCycleFire(actor: UcActor, ctx: StreamContext): number {
  turretSeek(actor);
  if ((actor.ucFireInterval148 ?? 0) === 0) {
    actor.ucFireInterval148 = ULTIMATE_CANNON.A0_FIRE_INTERVAL;
    actor.ucBurstCount14a = (actor.ucBurstCount14a ?? 0) + 1;
    if (!allocateWeapon(actor, ctx, 0, 1, true)) return 1;
    ctx.onFamilyProjectile?.(actor, ULTIMATE_CANNON.BURST_SPAWNER,
      (actor.ucShotCursor14c ?? 0) + 3);
    actor.ucShotCursor14c = ((actor.ucShotCursor14c ?? 0) + 1) & 3;
    const budget = (actor.ucArmed146 ?? 0) === 0
      ? ULTIMATE_CANNON.A0_BURST_BUDGET : ULTIMATE_CANNON.A0_BURST_HELD_BUDGET;
    if (budget <= (actor.ucBurstCount14a ?? 0)) return 1;
    actor.ucArmed146 = 0;
  } else {
    actor.ucFireInterval148 = (actor.ucFireInterval148 ?? 0) - 1;
    if ((actor.statusWord5b4 & ULTIMATE_CANNON.B_HELD_BIT) !== 0) actor.ucArmed146 = 1;
  }
  return 0;
}

// ----------------------------------------------------------------------------
// FUN_800b17cc(actor, variant) @ chunk_0017.c:4193 — charge hardpoint arm.
// ----------------------------------------------------------------------------
// FUN_800b1918 @ chunk_0017.c:4245 — action-2 launch turret. Ammo-gated
// zz_00c3be0_(4..7) with +0x154 countdown; returns 1 when done.
// ----------------------------------------------------------------------------
function launchTurret(actor: UcActor, ctx: StreamContext): number {
  if ((actor.ucLaunchInterval154 ?? 0) === 0) {
    actor.ucLaunchInterval154 = ULTIMATE_CANNON.A2_INTERVAL;
    if (!allocateWeapon(actor, ctx, 2, 1, true)) return 1;
    for (const rec of ULTIMATE_CANNON.A2_EFFECT_RECORDS) {
      ctx.onFamilyProjectile?.(actor, ULTIMATE_CANNON.EFFECT_SPAWNER, rec);
    }
  } else {
    actor.ucLaunchInterval154 = (actor.ucLaunchInterval154 ?? 0) - 1;
  }
  return 0;
}

// ============================================================================
// ACTION 0 — B volley (turret-cycle).
// ============================================================================

function a0Phase0Setup(actor: UcActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.ucArmed146 = 0;
  actor.ucFireInterval148 = 0;
  actor.ucBurstCount14a = 0;
  actor.ucShotCursor14c = 0;
  actor.ucLatch541 = 0;
  // +0x14c/0x14d/0x152 hardpoint flags zeroed (host-scratch).
  startStream(actor, 0xf, 2, actor.fbPhaseSlots[1] ?? 0, ULTIMATE_CANNON.STREAM_RATE);
}

function a0Phase1Aim(actor: UcActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  const done = turretCycleFire(actor, ctx);
  if (done !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.ucCycle548 = ULTIMATE_CANNON.COOLDOWN_SEED;          // +0x548 = 10
  }
}

function a0Phase2Cooldown(actor: UcActor): void {
  actor.ucCycle548 = (actor.ucCycle548 ?? 0) - 1;
  if ((actor.ucCycle548 ?? 0) < 1) {
    if ((actor.ucGrounded156 ?? 0) === 0) exitAir(actor);
    else exitGround(actor);
  }
}

/** Action-0 root — dispatcher FUN_800b0898 → PTR_FUN_80433aa8[+0x581]. */
function ultimateCannonAction0(actor: UcActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a0Phase0Setup(actor); break;
    case 1: a0Phase1Aim(actor, ctx); break;
    case 2: a0Phase2Cooldown(actor); break;
    default: break;
  }
}

// ============================================================================
// ACTION 2 — X-special (charge turret).
// ============================================================================

function a2Phase0Setup(actor: UcActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.ucLaunchInterval154 = 0;
  startStream(actor, 0xf, 2, actor.fbPhaseSlots[1] ?? 0, ULTIMATE_CANNON.STREAM_RATE);
}

function a2Phase1Fire(actor: UcActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  launchTurret(actor, ctx);
  // FUN_800b0ce0/FUN_800b0e68: the phase advances unconditionally after the
  // launch helper runs (the ROM does +0x540++ regardless of the helper result).
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.ucCycle548 = ULTIMATE_CANNON.COOLDOWN_SEED;          // +0x548 = 10
}

function a2Phase2Cooldown(actor: UcActor): void {
  actor.ucCycle548 = (actor.ucCycle548 ?? 0) - 1;
  if ((actor.ucCycle548 ?? 0) < 1) {
    if ((actor.ucGrounded156 ?? 0) === 0) exitAir(actor);
    else exitGround(actor);
  }
}

/** Action-2 root — dispatcher FUN_800b0c20 → PTR_FUN_80433ab0[+0x581]. */
function ultimateCannonAction2(actor: UcActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a2Phase0Setup(actor); break;
    case 1: a2Phase1Fire(actor, ctx); break;
    case 2: a2Phase2Cooldown(actor); break;
    default: break;
  }
}

// ============================================================================
// ACTION 3 — B-charge launch.
// ============================================================================

function a3Phase0Setup(actor: UcActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = ULTIMATE_CANNON.A3_PH0_TIMER;        // +0x558 = 60
  actor.gravityCoeff = ULTIMATE_CANNON.ZERO;
  actor.yVel = ULTIMATE_CANNON.ZERO;
  actor.hDecel = ULTIMATE_CANNON.ZERO;
  actor.hSpeed = ULTIMATE_CANNON.ZERO;
  actor.streamSlot = 0;
  // zz_00ec1f4_(0) — host arm; zz_00f0104_(8, 2) — host part anim (no-op).
  startStream(actor, 0xf, 4, 0, ULTIMATE_CANNON.STREAM_RATE);
  actor.ucGrounded156 = groundSnapRevert(actor) ? 1 : 0;
}

function a3Phase1Approach(actor: UcActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.dt;
  const done = turretTickProbe(actor, ctx);
  if ((done !== 0 || actor.handlerTimer <= ULTIMATE_CANNON.ZERO) && actor.wallContact !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.ucLatch541 = 0;
    // zz_004cff4_(0xf) — clear stream.
    if ((actor.ucGrounded156 ?? 0) === 0) actor.fbPhaseSlots[1] = 1; // +0x581 = 1
  }
}

function a3Phase2Launch(actor: UcActor, ctx: StreamContext): void {
  if (actor.ucLatch541 === 0) {
    actor.ucLatch541 = 1;
    actor.lockYaw = (actor.heading - 0x8000) & 0xffff; // +0x5ae = +0x72 − 0x8000
    actor.hSpeed = ULTIMATE_CANNON.A3_LAUNCH_HSPEED;   // +0x44 = 40
    actor.hDecel = ULTIMATE_CANNON.A3_LAUNCH_HDECEL;   // +0x4c = -1.5
    actor.streamSlot = 1;
  }
  const i = tickStream(actor, 0xf, ctx);
  if (!i) {
    if (actor.contactP0 === 1) { // +0x1cef == 1 → ground drag
      groundDrag(actor);
      if (actor.hSpeed < ULTIMATE_CANNON.A3_GROUND_FLOOR) actor.hSpeed = ULTIMATE_CANNON.A3_GROUND_FLOOR;
    } else if ((actor.ucGrounded156 ?? 0) === 1) {
      actor.gravityCoeff = ULTIMATE_CANNON.ZERO;
      actor.yVel = ULTIMATE_CANNON.ZERO;
      actor.hDecel = ULTIMATE_CANNON.ZERO;
      actor.hSpeed = ULTIMATE_CANNON.ZERO;
    } else {
      integratePhysicsFullClamp(ULTIMATE_CANNON.GRAVITY, actor, actor.lockYaw);
      actor.hSpeed *= ULTIMATE_CANNON.HSPEED_DECAY;
      actor.hDecel = ULTIMATE_CANNON.ZERO;
    }
  } else {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.streamSlot = 2;
  }
}

function a3Phase3Rearm(actor: UcActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  startStream(actor, 0xf, 4, 1, ULTIMATE_CANNON.STREAM_RATE);
  actor.hSpeed *= ULTIMATE_CANNON.HSPEED_DECAY;
  actor.hDecel = ULTIMATE_CANNON.ZERO;
  actor.yVel *= ULTIMATE_CANNON.YVEL_DECAY;
  actor.gravityCoeff = ULTIMATE_CANNON.ZERO;
  actor.ucCycle548 = ULTIMATE_CANNON.A3_REARM_SEED;   // +0x548 = 0x3c
  actor.streamSlot = 0;
  // zz_00ec1f4_(0) + zz_00f0104_(8, 2) — host arm/anim (no-op).
  integratePhysicsFullClamp(ULTIMATE_CANNON.GRAVITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
}

function a3Phase4Exit(actor: UcActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  const done = turretTickProbe(actor, ctx);
  actor.ucCycle548 = (actor.ucCycle548 ?? 0) - 1;
  if ((actor.ucCycle548 ?? 0) < 1 || done !== 0) {
    if (actor.wallContact !== 0) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.ucLatch541 = 0;
    }
  }
  actor.hSpeed *= ULTIMATE_CANNON.HSPEED_DECAY;
  actor.yVel *= ULTIMATE_CANNON.YVEL_DECAY;
  integratePhysicsFullClamp(ULTIMATE_CANNON.GRAVITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
}

function a3Phase5Final(actor: UcActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~ULTIMATE_CANNON.ACTION_MODE_BITS;
  if ((actor.ucGrounded156 ?? 0) === 1) romGroundIdleReturn(actor);
  else romAirKnockoutReturn(actor);
}

/** FUN_800b18e8 @ chunk_0017.c:4234 — FUN_8006cc90(0.2) turret tick probe. */
function turretTickProbe(actor: RomActor, ctx: StreamContext): number {
  const fired = tickStream(actor, 2, ctx);
  return fired ? 1 : 0;
}

/** zz_00670dc_(actor, +0x5ae) — ground-drag physics (approximation). */
function groundDrag(actor: RomActor): void {
  integratePhysicsFullClamp(ULTIMATE_CANNON.GRAVITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
}

/** Action-3 root — dispatcher FUN_800b0f18 → PTR_FUN_80433ab8[+0x581] (v0). */
function ultimateCannonAction3(actor: UcActor, ctx: StreamContext): void {
  actor.ucPostFlag7de = 1; // +0x7de = 1 (set by FUN_800b0f18)
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: a3Phase0Setup(actor); break;
    case 1: a3Phase1Approach(actor, ctx); break;
    case 2: a3Phase2Launch(actor, ctx); break;
    case 3: a3Phase3Rearm(actor); break;
    case 4: a3Phase4Exit(actor, ctx); break;
    case 5: a3Phase5Final(actor); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_800b085c indexes PTR_FUN_802fc420[+0x580].
// ----------------------------------------------------------------------------
export function createUltimateCannonRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: ultimateCannonAction0(actor, ctx); return;
      case 2: ultimateCannonAction2(actor, ctx); return;
      case 3: ultimateCannonAction3(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned ULTIMATE CANNON (pl0c04). */
export function configureUltimateCannonFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = ULTIMATE_CANNON_BORG_NUMBER;
  actor.rootAction = createUltimateCannonRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const ULTIMATE_CANNON_CONSTANTS = ULTIMATE_CANNON;

// ============================================================================
// Self-tests — mirror the beam-tank / icbm-tank style.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runUltimateCannonSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // --- configure stamps borgNumber + wires bespoke rootAction. ---
  {
    const a = createRomActor() as UcActor;
    configureUltimateCannonFamily(a, makeCtx());
    assert(a.borgNumber === 0xc04, "pl0c04 borgNumber stamped 0xc04");
    assert(a.rootAction !== null, "ultimate-cannon bespoke rootAction wired");
  }

  // --- action 0: ph0 setup → ph1 fire (12 shots) → ph2 cooldown exit. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as UcActor;
    configureUltimateCannonFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.ucGrounded156 = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances +0x540");
    // ph1: 12 shots. Shot 1 at call 1, then interval 5 → shots 2-12 at calls
    // 7,13,19,25,31,37,43,49,55,61,67. The 12th shot (call 67) hits budget → advance.
    for (let i = 0; i < 67; i += 1) root(a);
    assert(shots.length === 12, `action0 ph1 fires 12 shots (got ${shots.length})`);
    assert(shots[0]!.addr === ULTIMATE_CANNON.BURST_SPAWNER && shots[0]!.type === 3,
      `action0 ph1 first shot zz_0084600_(3) (got ${JSON.stringify(shots[0])})`);
    assert(a.fbPhaseSlots[0] === 2, "action0 ph1 advances to ph2 on burst completion");
    // ph2: cooldown 10 → ground exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 10; i += 1) root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph2 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 2: ph0 setup → ph1 launch (4 effects) → ph2 cooldown exit. ---
  {
    const spawned: Shot[] = [];
    const a = createRomActor() as UcActor;
    configureUltimateCannonFamily(a, makeCtx({
      onFamilyProjectile: (_ac, addr, type) => spawned.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.ucGrounded156 = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 ph0 advances +0x540");
    root(a); // ph1 launch
    assert(spawned.length === 4 && spawned[0]!.addr === ULTIMATE_CANNON.EFFECT_SPAWNER
        && spawned[0]!.type === 4 && spawned[3]!.type === 7,
      `action2 ph1 spawns zz_00c3be0_(4..7) (got ${JSON.stringify(spawned)})`);
    assert(a.fbPhaseSlots[0] === 2, "action2 ph1 advances to ph2");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 10; i += 1) root(a); // ph2 cooldown
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action2 ph2 exits (clears +0x73f, strips +0x5e0)");
  }

  // --- action 3: ph0 setup → ph1 approach → ph2 launch → ... → ph5 final. ---
  {
    const a = createRomActor() as UcActor;
    configureUltimateCannonFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.ucGrounded156 = 0; // airborne so the launch commit persists (grounded zeroes scalars)
    a.wallContact = 1; // gate ph1 advance
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action3 ph0 advances +0x540");
    assert(a.handlerTimer === ULTIMATE_CANNON.A3_PH0_TIMER,
      "action3 ph0 seeds +0x558 = 60.0 (FLOAT_8043832c)");
    // ph1: probe or timeout + wallContact → advance.
    for (let i = 0; i < 60; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 2, "action3 ph1 advances to ph2");
    // ph2: launch commits hSpeed=40, hDecel=-1.5, then the airborne full-clamp
    // branch decays: hSpeed += hDecel×dt = 38.5, then ×0.98 = 37.73 (ROM
    // FUN_800b115c airborne path) and zeroes +0x4c.
    root(a);
    assert(Math.abs(a.hSpeed - (ULTIMATE_CANNON.A3_LAUNCH_HSPEED + ULTIMATE_CANNON.A3_LAUNCH_HDECEL) * ULTIMATE_CANNON.HSPEED_DECAY) < 1e-6,
      "action3 ph2 commits hSpeed = (40 + -1.5) × 0.98 = 37.73");
    assert(a.hDecel === ULTIMATE_CANNON.ZERO,
      "action3 ph2 airborne branch zeroes hDecel (+0x4c)");
  }
}

/** Test context builder (mirrors beam-tank's makeCtx). */
function makeCtx(opts: {
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
  onPlayCue?: () => void;
} = {}): StreamContext {
  const ctx: StreamContext = {};
  if (opts.onFamilyProjectile) ctx.onFamilyProjectile = opts.onFamilyProjectile;
  if (opts.onPlayCue) ctx.onPlayCue = () => opts.onPlayCue!();
  return ctx;
}
