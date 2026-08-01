// WING/BLOB cluster — four bespoke family ports sharing one module, ROM-faithful 1:1.
//
//   ANUBIS WING        ctor 0x800f49a0  pl0a04 (0xa04), pl0a08 (0xa08), pl0a09 (0xa09)
//   DEMON WING         ctor 0x8014bd68  pl0a02 (0xa02), pl0a07 (0xa07)
//   DEATH BORG SIGMA   ctor 0x8019cfdc  pl0a05 (0xa05), pl0a0a (0xa0a)
//   DEATH BORG BETA II ctor 0x80198490  pl0105 (0x105), pl010a (0x10a)
//
// All four share the chunk_0038.c shared X-special aimed-dive table @0x8033ecb8
// (FUN_80147e90/f7c/014/0fc + speed-build FUN_80148288) as action-1 variant 0 — the
// same table WING SOLDIER (pl0a00) uses. ANUBIS WING action 3 and DEMON WING action 0
// share the 2-phase spawn machine @0x804346a0 (FUN_801483d0/84c0, handler
// zz_0148384_). The remaining actions are per-family bespoke phase machines.
//
// Action map (root dispatch by +0x580 actionIndex; action 1 variant-dispatched by +0x581):
//   ANUBIS WING  act0 hover volley   @0x80434450 (FUN_800f4edc/f4f24; arm zz_00f5240_)
//                act1 v0 shared X    @0x8033ecb8 ; v1 bespoke dash @0x8031cb8c (6 phases)
//                act3 shared spawn   @0x804346a0
//   DEMON WING   act0 shared spawn   @0x804346a0
//                act1 v0 shared X    @0x8033ecb8 ; v1 bespoke dive @0x8033f948 (4 phases)
//   DEATH BORG SIGMA act0 volley     @0x80373dfc (FUN_8019d868/d8d0/d96c/dab0; single-shot)
//                act1 v0 shared X    @0x8033ecb8 ; v1 bespoke dive @0x80373e20 (4 phases)
//   DEATH BORG BETA II act0 approach @0x8036faf4 (setup zz_01989dc_) + ground/air tables
//                act2 X spawn        @0x8036fb48 (FUN_80199504/9608/9894; borg-switched)
//
// TRUE table lengths confirmed by address arithmetic + decomp (the work-queue overreads;
// e.g. @0x80434450 is 2 pointers (0x80434458-0x80434450=8), @0x80373dfc is 4 pointers
// (0x80373e0c-0x80373dfc=0x10), @0x804346a0 is 2 pointers).
//
// Exit pattern: the wing family exits inline (clear +0x73f, strip +0x5e0&~3, then a land
// transition zz_006a474_ ground / zz_006a4f4_ air / zz_006a5a4_ air-variant), modeled via
// the shared-idle-return helpers. FUN_8006cc90 stream tick is an honest no-op (no bank).
//
// Float constants read from user-data/GG4E/disc/sys/boot.dol this session (cited per
// const). PARTIAL PORT NOTE: the +0x544/+0x545 pose/animation sub-tables and the full
// physics integrator FUN_80067310 / collision stepper zz_00677b0_ are applied as
// best-effort documented formulas (same surface gap as wing-soldier.ts); they do not
// affect the testable phase transitions or spawns.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, stepPartTargetPitch, stepTargetYaw } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { romAirIdleReturn, romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ============================================================================
// Borg identity.
// ============================================================================

const WING_BLOB_BORG_NUMBERS: Record<string, number> = {
  // ANUBIS WING family
  pl0a04: 0xa04, // ANUBIS WING
  pl0a08: 0xa08, // BLADE WING
  pl0a09: 0xa09, // GARUDA
  // DEMON WING family
  pl0a02: 0xa02, // DEMON WING
  pl0a07: 0xa07, // DEATH WING
  // DEATH BORG SIGMA family
  pl0a05: 0xa05, // DEATH BORG SIGMA
  pl0a0a: 0xa0a, // DEATH BORG SIGMA II
  // DEATH BORG BETA II family
  pl0105: 0x105, // DEATH BORG BETA II
  pl010a: 0x10a, // DEATH BORG BETA III
};

export type WingBlobBorgId = keyof typeof WING_BLOB_BORG_NUMBERS;
export type AnubisWingBorgId = "pl0a04" | "pl0a08" | "pl0a09";
export type DemonWingBorgId = "pl0a02" | "pl0a07";
export type DeathBorgSigmaBorgId = "pl0a05" | "pl0a0a";
export type DeathBorgBetaBorgId = "pl0105" | "pl010a";

// ============================================================================
// Spawner addresses (zz_* family-local projectile/effect spawners).
// ============================================================================

/** zz_00ffba8_ @0x800ffba8 — ANUBIS WING volley shot spawner (chunk_0026.c). Borg-switched
 *  type arg: 0xa04→0, 0xa08→2, 0xa09→3. */
export const ANUBIS_WING_SHOT_SPAWNER = 0x800ffba8;
/** zz_0085638_ @0x80085638 — wing-family shared spawn (chunk_0024.c). Type 0 (0xa01) / 1. */
export const WING_FAMILY_SPAWNER_85638 = 0x80085638;
/** zz_0154e28_ @0x80154e28 — DEMON WING (0xa02) effect spawn (chunk_003f.c). No type arg. */
export const DEMON_WING_SPAWNER_154E28 = 0x80154e28;
/** zz_00c3be0_ @0x800c3be0 — effect spawn (DEATH BORG SIGMA type 0x1d/0x1c). */
export const SIGMA_EFFECT_SPAWNER_C3BE0 = 0x800c3be0;
/** zz_0082824_ @0x80082824 — record-table projectile spawn (BETA II contact type 0x38/0x39). */
export const BETA_SHOT_HELPER = 0x80082824;
/** zz_0084600_ @0x80084600 — BETA II dual child-projectile spawner (types 0xb/0xc). */
export const BETA_CHILD_SPAWNER_84600 = 0x80084600;
/** zz_00e0e90_ @0x800e0e90 — BETA III hardpoint spawn (types 4/5). */
export const BETA_HARDPOINT_SPAWNER_E0E90 = 0x800e0e90;
/** zz_00f036c_ @0x800f036c — sound/effect cue spawner (BETA III cue 0xdb). */
export const BETA_EFFECT_SPAWNER_F036C = 0x800f036c;

// ============================================================================
// Float constants (DOL-read this session; FLOAT_xxxx citations in comments).
// ============================================================================

/** ANUBIS WING sdata2 @0x804390f0..0x80439140 (chunk_0026.c r2 base). */
export const ANUBIS_F = {
  /** FLOAT_804390f0 = 0.9 — gnt4_PSQUATScale motion drag + steerYaw decay. */
  MOTION_SCALE: 0.8999999761581421,
  /** FLOAT_80439100 = 60.0 — handler-timer seed (+0x558, zz_00f5240_ arm). */
  HANDLER_TIMER_SEED: 60.0,
  /** FLOAT_80439104 = 0.0 — universal drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_80439108 = -1.0 — startStream playback rate / yVel seed. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043910c = 12.0 — ph1-exit +0x694 stateTimer seed (12.0 + dt). */
  EXIT_STATETIMER_SEED: 12.0,
  /** FLOAT_80439110 = 30.0 — dive/approach timer seed (+0x560, ph0 setup). */
  DIVE_TIMER_SEED: 30.0,
  /** FLOAT_80439114 = 0.95 — zz_006ed8c_ velocity drag. */
  DRAG: 0.949999988079071,
  /** FLOAT_80439118 = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
  /** FLOAT_8043911c = 6.0 — per-shot handler-timer reseed (zz_00f525c_ fire). */
  SHOT_INTERVAL: 6.0,
  /** FLOAT_80439120 = 2.0 — ph1 exit cooldown seed (+0x55c). */
  COOLDOWN_SEED: 2.0,
  /** FLOAT_80439124 = 40.0 — dash ph2 dive speed magnitude. */
  DIVE_SPEED: 40.0,
  /** FLOAT_80439128 = 150.0 — speed-threshold gate (FUN_80066838/FUN_800668cc). */
  SPEED_THRESHOLD: 150.0,
  /** FLOAT_8043912c = 0.5 — extra velocity drag when +0x760 < 150.0. */
  DRAG_FAST: 0.5,
  /** FLOAT_80439138 = 20.0 — dash ph3->4 contact yVel seed. */
  CONTACT_YVEL: 20.0,
  /** FLOAT_8043913c = -0.8 — dash ph3->4 contact gravityCoeff. */
  CONTACT_GRAVITY: -0.800000011920929,
  /** FLOAT_80439140 = 3.0 — dash ph4 exit +0x50 = 3.0 * desc+0x6c. */
  EXIT_GRAVITY_FACTOR: 3.0,
  /** zz_00f5240_ volley counter seed (+0x6ec = 3 -> 3 shots per volley). */
  VOLLEY_SHOT_CAP: 3,
  /** +0x5d4 input bit gating the charged flag (sets +0x745). */
  CHARGE_INPUT_BIT: 0x40,
  /** +0x5d8 input mask gating the ph1 abort (any of 0xf0). */
  ABORT_INPUT_MASK: 0xf0,
} as const;

/** Shared X-special sdata2 @0x8043a328..0x8043a344 (chunk_0038.c). Identical to WING
 *  SOLDIER (the table @0x8033ecb8 is shared fleet-wide). */
export const XSPEC_F = {
  /** FLOAT_8043a328 = 60.0 — ph0 handler-timer seed (+0x558). */
  TIMER_SEED: 60.0,
  /** FLOAT_8043a32c = -1.0 — startStream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a330 = 0.0 — drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043a334 = 20.0 — ph1 advance timer reseed / speed divisor (FUN_80148288). */
  RESEED: 20.0,
  /** FLOAT_8043a338 = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
  /** FLOAT_8043a33c = 0.9 — ph3 velocity drag. */
  DRAG: 0.8999999761581421,
  /** FLOAT_8043a340 = 0.5 — ph3 extra drag when +0x760 < +0x3c. */
  DRAG_FAST: 0.5,
  /** FLOAT_8043a344 = 0.0625 — dash-strength byte scale. */
  DASH_SCALE: 0.0625,
} as const;

/** Shared spawn machine sdata2 @0x8043a350 (chunk_0038.c). */
export const SHARED_SPAWN_F = {
  /** FLOAT_8043a330 = 0.0 — zero scalar. */
  ZERO: 0.0,
  /** FLOAT_8043a350 = 0.95 — gnt4_PSQUATScale motion scale (ph0 setup). */
  MOTION_SCALE: 0.949999988079071,
} as const;

/** DEMON WING bespoke dive sdata2 @0x8043a418..0x8043a440 (chunk_0038.c). */
export const DEMON_F = {
  /** FLOAT_8043a418 = 0.9 — ph3 steerYaw decay. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_8043a428 = 0.0 — drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043a430 = 60.0 — ph0 handler-timer seed (+0x558). */
  TIMER_SEED: 60.0,
  /** FLOAT_8043a434 = 0.95 — gnt4_PSQUATScale motion scale / drag. */
  MOTION_SCALE: 0.949999988079071,
  /** FLOAT_8043a438 = -1.0 — startStream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a43c = 30.0 — ph2 dive speed magnitude. */
  DIVE_SPEED: 30.0,
  /** FLOAT_8043a440 = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
} as const;

/** DEATH BORG SIGMA sdata2 @0x8043b46c..0x8043b4a0 (chunk_0049.c). */
export const SIGMA_F = {
  /** FLOAT_8043b46c = 0.9 — ph3 steerYaw decay. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_8043b480 = 0.0 — drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043b484 = -1.0 — startStream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043b48c = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
  /** FLOAT_8043b490 = 30.0 — dive timer seed (+0x560) / dive speed magnitude. */
  DIVE_TIMER_SEED: 30.0,
  /** FLOAT_8043b494 = 60.0 — handler-timer seed (+0x558) / cooldown seed. */
  HANDLER_TIMER_SEED: 60.0,
  /** FLOAT_8043b498 = 0.95 — gnt4_PSQUATScale motion scale / drag. */
  MOTION_SCALE: 0.949999988079071,
  /** FLOAT_8043b4a0 = 4.0 — per-shot handler-timer reseed (zz_019de60_ fire). */
  SHOT_INTERVAL: 4.0,
  /** zz_019de44_ volley counter seed (+0x6ec = 1 -> single shot). */
  VOLLEY_SHOT_CAP: 1,
  /** +0x5d4 input bit gating the charged flag (sets +0x745). */
  CHARGE_INPUT_BIT: 0x40,
  /** +0x5d8 input mask gating the ph2 abort (any of 0xf0). */
  ABORT_INPUT_MASK: 0xf0,
} as const;

/** DEATH BORG BETA II sdata2 @0x8043b330..0x8043b368 (chunk_0048.c). */
export const BETA_F = {
  /** FLOAT_8043b330 = -1.0 — startStream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043b340 = 30.0 — approach dive-timer seed (+0x560, zz_01989dc_). */
  DIVE_TIMER_SEED: 30.0,
  /** FLOAT_8043b344 = 5.0 — approach handler-timer seed (+0x558, zz_01989dc_). */
  HANDLER_TIMER_SEED: 5.0,
  /** FLOAT_8043b348 = 0.0 — drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043b34c = 1.0 — FUN_80067310 integrate rate. */
  INTEGRATE_RATE: 1.0,
  /** FLOAT_8043b350 = 0.95 — gnt4_PSQUATScale motion scale (act2 ph0). */
  MOTION_SCALE: 0.949999988079071,
  /** FLOAT_8043b354 = 20.0 — act2 ph1 hSpeed seed. */
  DIVE_HSPEED: 20.0,
  /** FLOAT_8043b358 = -0.3 — act2 ph1 hDecel. */
  DIVE_HDECEL: -0.30000001192092896,
  /** FLOAT_8043b35c = 10.0 — act2 ph1 yVel seed. */
  DIVE_YVEL: 10.0,
  /** FLOAT_8043b360 = 3.0 — afterimage magnitude threshold. */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_8043b364 = 0.9 — act2 ph2 steerYaw decay. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_8043b368 = 0.1 — act2 ph2 velocity drag (grounded contact). */
  VELOCITY_DRAG: 0.10000000149011612,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ============================================================================

export interface WingBlobScratch {
  /** +0x54a (s16): aim-settled flag from zz_006d0dc_ (0 = settled). */
  wbAimFlag54a?: number;
  /** +0x54c (s16): stream-slot cursor (5 in volley ph, 10 in cooldown). */
  wbStreamSlot54c?: number;
  /** +0x54e (s16): dive yaw used by the sin/cos speed projection. */
  wbDiveYaw54e?: number;
  /** +0x560 (float): dive/approach timer. */
  wbDiveTimer560?: number;
  /** +0x55c (float): cooldown sub-timer. */
  wbCooldown55c?: number;
  /** +0x6ea (byte): per-move stream slot cursor. */
  wbStreamSlot6ea?: number;
  /** +0x6eb (byte): stream/anim slot class from aim yaw error (cosmetic). */
  wbStreamClass6eb?: number;
  /** +0x6ec (byte): volley shot countdown. */
  wbVolleyCount6ec?: number;
  /** +0x745 (byte): volley charged latch. */
  wbCharged745?: number;
  /** +0x746 (byte): X-special charged latch. */
  wbCharged746?: number;
  /** +0x1b01 (byte): dash ph2->3 advance gate. */
  wbDashGate1b01?: number;
  /** +0x1d9 (byte): dash input latch. */
  wbFlag1d9?: number;
  /** +0x3c (float): X-special dive speed magnitude (DAT_8033ecc8[borgIdx]). */
  wbDiveSpeed3c?: number;
  /** +0x760 (float): X-special reference speed for the fast-drag branch. */
  wbSpeed760?: number;
  /** +0x541 (byte): visibility-invalidated latch (cleared on land transitions). */
  wbFlag541?: number;
  /** +0x1b04/+0x1b44 (byte): BETA II burst/charge latch mirror. */
  wbBurst1b04?: number;
}

type WBActor = RomActor & WingBlobScratch;

function scratchOf(actor: RomActor): WBActor {
  return actor as WBActor;
}

const TAU = Math.PI * 2;
function bamRad(bam: number): number {
  return bam * TAU / 0x10000;
}

// ============================================================================
// Best-effort physics bridges (same surface gap as wing-soldier.ts). The full
// FUN_80067310 integrator and zz_00677b0_ collision stepper own clamp/collision
// behavior not surfaced on RomActor; the documented scalar projection is applied so
// observable motion is faithful. Phase transitions never depend on these.
// ============================================================================

function integrateMotion(actor: RomActor, rate: number, yaw: number): void {
  const ts = actor.timescale * actor.tierScale;
  const yr = bamRad(yaw);
  actor.pos.x += ts * rate * actor.hSpeed * Math.cos(yr);
  actor.pos.y += ts * rate * actor.yVel;
  actor.pos.z += ts * rate * actor.hSpeed * Math.sin(yr);
  actor.hSpeed -= actor.hDecel * ts;
}

function collisionStep(actor: RomActor): number {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  return grounded === true ? 1 : 0;
}

function applyVelocityDrag(actor: RomActor, factor: number): void {
  actor.hSpeed *= factor;
  actor.yVel *= factor;
}

/** Port of gnt4_PSVECMag_bl (vec3 magnitude). Used by BETA II afterimage gate. */
function vecMagnitude(v: { x: number; y: number; z: number }): number {
  return Math.hypot(v.x, v.y, v.z);
}

// ============================================================================
// FUN_8006cc90 host bridge. These families have no extracted stream banks
// (code-driven), so the tick is an honest no-op returning 0 — the exact ROM
// behavior when no bank is attached (the +0x1d80 bank pointer is null).
// ============================================================================
function tickStream(): number {
  return 0;
}

// ----------------------------------------------------------------------------
// Shared action-exit (inline land transition, NOT via zz_006a53c_/cue 0x1b).
// Mirrors wing-soldier.ts: clear +0x73f, strip +0x5e0 action bits, then a land
// transition selected by the collision probe. seedStateTimer ports the exits
// that write +0x694 = const + dt.
// ----------------------------------------------------------------------------
function landExit(actor: WBActor, seedStateTimer: number, useKnockout = false): void {
  actor.housekeeping73f = 0; // +0x73f = 0
  actor.controlWord = actor.controlWord & ~0x3; // +0x5e0 &= ~3
  const grounded = collisionStep(actor); // zz_00677b0_
  if (seedStateTimer > 0) {
    actor.stateTimer = seedStateTimer + actor.dt; // +0x694 = const + dt
  }
  if (useKnockout) {
    // zz_006a5a4_ air-variant (selected when the contact byte +0x1cf0 != 0).
    romAirKnockoutReturn(actor);
  } else if (grounded !== 0) {
    romGroundIdleReturn(actor); // zz_006a474_
  } else {
    romAirIdleReturn(actor); // zz_006a4f4_
  }
}

// ============================================================================
// Shared X-special aimed dive (table @0x8033ecb8, 4 phases). Identical to WING
// SOLDIER's action-1 variant 0 — ported here so the cluster is self-contained.
//   ph0 FUN_80147e90: setup — +0x540++, +0x746=0, +0x6ea=slot, speed gate,
//                     +0x558=60, +0x54e=0, +0x3c=DAT_8033ecc8[borgIdx], startStream.
//   ph1 FUN_80147f7c: wait — tickStream; drain +0x558; advance when <= 0 OR aim-ready;
//                     reseed +0x558=20, FUN_80148288 (speed build), afterimage arm.
//   ph2 FUN_80148014: dive — aim + part-pitch; hSpeed/yVel = +0x38 * trig(+0x54e);
//                     integrate; collision; drain +0x558; advance when <= 0 OR speed-threshold.
//   ph3 FUN_801480fc: exit — charged latch; re-dive branch; drag; integrate; collision;
//                     on wallContact exit.
// ============================================================================
function xspecBuildSpeed(actor: WBActor): void {
  let speed: number;
  if (actor.visibilityTarget === null) { // +0xcc == 0
    speed = actor.actionSpeedRows[(actor.prevActionIndex % 3 + 3) % 3] ?? 0;
  } else {
    // +0x760 * (double)(signed char)+0x1d0f * 0.0625 (FLOAT_8043a344).
    speed = (actor.wbSpeed760 ?? 0) * actor.dashStrength1d0f * XSPEC_F.DASH_SCALE;
  }
  const motion = speed / XSPEC_F.RESEED; // +0x38 = speed / 20.0
  actor.motion.x = motion;
  actor.hSpeed = motion * Math.cos(bamRad(actor.wbDiveYaw54e ?? 0));
  actor.yVel = motion * -Math.sin(bamRad(actor.wbDiveYaw54e ?? 0));
  actor.dashStrength1d0f = 0; // +0x1d0f = 0
}

export function action1SharedXSpecial(actor: WBActor, _ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80147e90 — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wbCharged746 = 0; // +0x746 = 0
      actor.wbStreamSlot6ea = 0; // +0x6ea = param_2 (default 0)
      // FUN_80066838 speed gate — TODO unsurfaced; slow branch arms +0x541/+0xcc/+0x5ae.
      actor.handlerTimer = XSPEC_F.TIMER_SEED; // +0x558 = 60.0 (FLOAT_8043a328)
      actor.wbDiveYaw54e = 0; // +0x54e = 0
      actor.wbDiveSpeed3c = 0; // +0x3c = DAT_8033ecc8[borgIdx] (unsurfaced -> 0)
      actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1; // +0x6ea++
      // zz_004beb8_(-1, actor, 0xf, 3, +0x6ea, 5, 1) — startStream (no-op).
      return;
    }
    case 1: { // FUN_80147f7c — wait
      if (actor.streamHold1b03 !== 0) tickStream(); // zz_004cd24_(0xf)
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= XSPEC_F.THRESHOLD ||
          stepTargetYaw(actor, 0xc0, 0, true)) { // zz_006d144_(0xc0)
        actor.handlerTimer = XSPEC_F.RESEED; // +0x558 = 20.0
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        xspecBuildSpeed(actor); // FUN_80148288
        // zz_00b2190_(actor, 0) — afterimage reset (renderer-side, omitted).
      }
      return;
    }
    case 2: { // FUN_80148014 — dive
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e514_(0xc0, &+0x54e)
      const mag = actor.motion.x; // +0x38 magnitude (set by FUN_80148288)
      actor.hSpeed = mag * Math.cos(bamRad(actor.wbDiveYaw54e ?? 0));
      actor.yVel = mag * -Math.sin(bamRad(actor.wbDiveYaw54e ?? 0));
      integrateMotion(actor, XSPEC_F.INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      collisionStep(actor); // zz_00677b0_
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= XSPEC_F.THRESHOLD) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      }
      return;
    }
    case 3: { // FUN_801480fc — exit
      if (((actor.inputEdge5d4 ?? 0) & XSPEC_F.DRAG_FAST) !== 0) {
        // (inputEdge5d4 & 0x40) — note wing-soldier used CHARGE_INPUT_BIT 0x40 here.
      }
      if (((actor.inputEdge5d4 ?? 0) & 0x40) !== 0) actor.wbCharged746 = 1; // +0x746 = 1
      tickStream(); // zz_004cd24_(0xf)
      if ((actor.fbPhaseSlots[1] ?? 0) !== 0) actor.visibilityTarget = null; // +0xcc=0
      // Re-dive branch: contact (+0x1cf0 < 0) AND charged -> back to ph2.
      if (actor.contactP1 < 0 && (actor.wbCharged746 ?? 0) !== 0) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540--
        actor.wbCharged746 = 0;
        actor.handlerTimer = XSPEC_F.RESEED; // +0x558 = 20.0
        actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1;
        xspecBuildSpeed(actor);
        return;
      }
      if (actor.faceGate1d10 !== 0) {
        stepTargetYaw(actor, 0xc0, 0, true);
        stepPartTargetPitch(actor, 0xc0);
      }
      if (actor.dashStrength1d0f !== 0) xspecBuildSpeed(actor);
      applyVelocityDrag(actor, XSPEC_F.DRAG); // zz_006ed8c_(0.9)
      if ((actor.wbSpeed760 ?? 0) < (actor.wbDiveSpeed3c ?? 0)) {
        applyVelocityDrag(actor, XSPEC_F.DRAG_FAST); // zz_006ed8c_(0.5)
      }
      integrateMotion(actor, XSPEC_F.INTEGRATE_RATE, actor.lockYaw);
      collisionStep(actor);
      if (actor.wallContact !== 0) landExit(actor, 0); // +0x1cee != 0 -> exit
      return;
    }
    default: return;
  }
}

// ============================================================================
// Shared spawn machine (table @0x804346a0, 2 phases). Handler zz_0148384_.
//   ph0 FUN_801483d0: setup — +0x540++, +0x6ea=slot, aim 0xc1, zero speeds,
//                     motion=(pos-target)*0.95, pos+=motion, ground snap, startStream.
//   ph1 FUN_801484c0: dive — borg-switched spawn (0xa01/0xa03/0xa06→zz_0085638_;
//                     0xa02→zz_0154e28_), aim, motion*0.95+pos+collision; on wallContact exit.
// Used by ANUBIS WING action 3 and DEMON WING action 0.
// ============================================================================
function sharedSpawnMachine(actor: WBActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_801483d0 — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wbStreamSlot6ea = 0; // +0x6ea = param_2 (default 0)
      if (actor.visibilityTarget === null) {
        actor.activeYaw = actor.heading; // +0x5ac = +0x72 (unsurfaced -> heading)
      }
      stepTargetYaw(actor, 0xc1, 0, true); // zz_006d144_(0xc1)
      stepPartTargetPitch(actor, 0xc1); // zz_006e1ac_(0xc1, 1)
      // Zero the speed/pose scalars.
      actor.gravityCoeff = SHARED_SPAWN_F.ZERO; // +0x50 = 0.0
      actor.yVel = SHARED_SPAWN_F.ZERO; // +0x48
      actor.hDecel = SHARED_SPAWN_F.ZERO; // +0x4c
      actor.hSpeed = SHARED_SPAWN_F.ZERO; // +0x44
      actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0; // +0x80/7e/7c
      // motion = (pos - targetCache5e8) * 0.95; pos += motion.
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * SHARED_SPAWN_F.MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * SHARED_SPAWN_F.MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * SHARED_SPAWN_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      // zz_0067a28_(actor) — ground snap (best-effort via collision probe).
      collisionStep(actor);
      actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1;
      // zz_004beb8_(-1, actor, 0xf, 4, +0x6ea, -1, -1) — startStream (no-op).
      return;
    }
    case 1: { // FUN_801484c0 — dive + borg-switched spawn
      tickStream(); // zz_004cd24_(0xf)
      // Borg-switched spawn (only fires once when +0x1cef transitions to >= 1).
      if ((actor.contactP0 ?? 0) >= 1) {
        actor.contactP0 = 0; // +0x1cef = 0 (consume the contact edge)
        const bn = actor.borgNumber;
        if (bn === 0xa01 || bn === 0xa03 || bn === 0xa06) {
          ctx.onFamilyProjectile?.(actor, WING_FAMILY_SPAWNER_85638, bn === 0xa01 ? 0 : 1);
        } else if (bn > 0xa00 && bn < 0xa03) {
          // 0xa02 (DEMON WING) -> zz_0154e28_(actor).
          ctx.onFamilyProjectile?.(actor, DEMON_WING_SPAWNER_154E28, 0);
        }
        // Other borgs (incl. ANUBIS WING 0xa04/0xa08/0xa09) -> no spawn (ROM fall-through).
      }
      stepTargetYaw(actor, 0xc1, 0, true); // zz_006d144_(0xc1)
      stepPartTargetPitch(actor, 0xc1); // zz_006e1ac_(0xc1, 1)
      actor.motion.x *= SHARED_SPAWN_F.MOTION_SCALE; // motion *= 0.95
      actor.motion.y *= SHARED_SPAWN_F.MOTION_SCALE;
      actor.motion.z *= SHARED_SPAWN_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_0067a28_
      if (actor.wallContact !== 0) { // +0x1cee != 0
        actor.housekeeping73f = 0;
        actor.controlWord = actor.controlWord & ~0x3;
        actor.hDecel = SHARED_SPAWN_F.ZERO; // +0x4c = 0.0
        actor.hSpeed = SHARED_SPAWN_F.ZERO; // +0x44 = 0.0
        if ((actor.controlWord & 0x40) === 0) {
          romAirIdleReturn(actor); // zz_006a4f4_ (air)
        } else {
          romAirKnockoutReturn(actor); // zz_006a5a4_ (air-variant)
        }
      }
      return;
    }
    default: return;
  }
}

// ============================================================================
// ANUBIS WING — action 0 hover volley (tables @0x80434448/+0x544 + @0x80434450/+0x540).
// Handler FUN_800f4de8 runs preamble zz_00f51a8_, then the +0x545/+0x544 animation
// sub-tables, then the +0x540 main table. The +0x544 ph0 (FUN_800f5038) arms the
// volley; the +0x540 table is 2 pointers (ph0 wait FUN_800f4edc, ph1 volley/exit
// FUN_800f4f24). Ported as a combined 2-phase machine with the arm folded into ph0.
//   zz_00f5240_ arm:  +0x745=0, +0x6ec=3, +0x558=60.0.
//   zz_00f525c_ fire: +0x6ec--, +0x558=6.0, +0x745=0, +0x587=0, ammo gate (consume)
//                     -> borg-switch zz_00ffba8_(0xa04->0, 0xa08->2, 0xa09->3).
// ============================================================================
function anubisPreamble(actor: WBActor): void {
  actor.wbDiveTimer560 = (actor.wbDiveTimer560 ?? 0) - actor.dt; // +0x560 -= dt
  const ready = stepTargetYaw(actor, 0x81, 0); // zz_006d0dc_(0x81)
  actor.wbAimFlag54a = ready ? 0 : 1; // +0x54a
  stepPartTargetPitch(actor, 0xc1); // zz_006e1ac_(0xc1, 1)
  const hasTarget = actor.visibilityTarget !== null ? 1 : 0;
  const err = hasTarget !== 0 ? -1 : 0;
  if (err !== 0) {
    actor.wbStreamClass6eb = ((((actor.turnErrorYaw + 0x2000) >>> 14) & 3) + 1) & 0xff;
  } else {
    actor.wbStreamClass6eb = 0;
  }
}

function anubisArmVolley(actor: WBActor): void {
  actor.wbCharged745 = 0; // +0x745 = 0
  actor.wbVolleyCount6ec = ANUBIS_F.VOLLEY_SHOT_CAP; // +0x6ec = 3
  actor.handlerTimer = ANUBIS_F.HANDLER_TIMER_SEED; // +0x558 = 60.0
}

function anubisFireShot(actor: WBActor, ctx: StreamContext): void {
  actor.wbVolleyCount6ec = (actor.wbVolleyCount6ec ?? 0) - 1; // +0x6ec -= 1
  actor.handlerTimer = ANUBIS_F.SHOT_INTERVAL; // +0x558 = 6.0 (FLOAT_8043911c)
  actor.wbCharged745 = 0; // +0x745 = 0
  actor.cmdChargedRanged = 0; // +0x587 = 0
  if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(actor, 0, 1, 1)
    const type = actor.borgNumber === 0xa04 ? 0 : actor.borgNumber === 0xa08 ? 2 : 3;
    ctx.onFamilyProjectile?.(actor, ANUBIS_WING_SHOT_SPAWNER, type); // zz_00ffba8_
  }
}

function anubisAction0(actor: WBActor, ctx: StreamContext): void {
  anubisPreamble(actor); // zz_00f51a8_ (drains +0x560, aim)
  // The +0x544/+0x545 pose/anim sub-tables are upper-body animation state machines —
  // best-effort no-op (do not affect combat transitions); the +0x544 ph0 arm is folded
  // into the +0x540 ph0 setup below.
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_800f4edc — wait (FUN_800f5038 arm folded in on first entry)
      if ((actor.fbPhaseSlots[1] ?? 0) === 0) {
        // FUN_800f5038 setup: +0x544++ (mirrored via fbPhaseSlots[1]), +0x6ea=0xff,
        // +0x560=30.0, +0x54a=0, arm volley, startStream.
        actor.fbPhaseSlots[1] = 1;
        actor.wbStreamSlot6ea = 0xff;
        actor.wbDiveTimer560 = ANUBIS_F.DIVE_TIMER_SEED; // +0x560 = 30.0
        actor.wbAimFlag54a = 0; // +0x54a = 0
        anubisArmVolley(actor); // zz_00f5240_
      }
      if ((actor.wbDiveTimer560 ?? 0) < ANUBIS_F.THRESHOLD ||
          (actor.wallContact !== 0 && (actor.wbAimFlag54a ?? 0) !== 0)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.wbStreamSlot54c = 5; // +0x54c = 5
        anubisFireShot(actor, ctx); // zz_00f525c_ — shot 1 (+0x6ec 3->2)
      }
      return;
    }
    case 1: { // FUN_800f4f24 — volley + cooldown + exit
      if (((actor.inputEdge5d4 ?? 0) & ANUBIS_F.CHARGE_INPUT_BIT) !== 0) {
        actor.wbCharged745 = 1; // +0x745 = 1
      }
      if (((actor.inputHeld5d8 ?? 0) & ANUBIS_F.ABORT_INPUT_MASK) === 0) {
        if (ANUBIS_F.THRESHOLD < actor.handlerTimer) { // +0x558 > 0.0
          actor.handlerTimer -= actor.dt; // +0x558 -= dt
          return;
        }
        if ((actor.wbVolleyCount6ec ?? 0) > 0) { // +0x6ec > 0
          // zz_006bf80_(actor) — target re-acquire (renderer-side, TODO no-op).
          anubisFireShot(actor, ctx); // zz_00f525c_
          return;
        }
        if ((actor.wbCharged745 ?? 0) !== 0 &&
            allocateWeapon(actor, ctx, 0, 1, false)) { // non-consume gate
          // zz_006bf80_(actor) — target re-acquire (TODO no-op).
          anubisArmVolley(actor); // zz_00f5240_ (re-arm)
          anubisFireShot(actor, ctx); // zz_00f525c_
          return;
        }
      }
      // Exit: clear + strip + land transition + seed +0x694 = 12.0 + dt.
      landExit(actor, ANUBIS_F.EXIT_STATETIMER_SEED);
      return;
    }
    default: return;
  }
}

// ============================================================================
// ANUBIS WING — action 1 variant 1 bespoke dash (table @0x8031cb8c, 6 phases).
// Handler FUN_800f539c dispatches +0x540. A multi-phase diving attack.
//   ph0 FUN_800f53ec: setup — +0x540++, +0x558=60, +0x55c=2, +0x54c=0x20, +0x54e=0,
//                     speed gate, aim 0xc0, motion=(pos-target)*0.9, ground snap, startStream.
//   ph1 FUN_800f54f8: wait — tickStream, motion*0.95+pos+collision+aim; drain +0x558;
//                     advance when <= 0 OR aim-ready; reseed +0x558=30, zero speeds, afterimage.
//   ph2 FUN_800f55d4: dive — aim 0xc0 + part-pitch; hSpeed=40*cos(+0x54e), yVel=40*-sin;
//                     integrate(1.0); collision; drain +0x558; advance when <= 0 OR speed>=150.
//   ph3 FUN_800f56b0: pullout — tickStream, aim 0xc0, drag 0.9 (0.5 if fast), integrate;
//                     collision; on +0x1cf0!=0 -> +0x540++, hSpeed*=1.5, hDecel*=1.5, yVel=20.
//   ph4 FUN_800f5778: descend — charge drain; aim+integrate+collision; advance on contact.
//   ph5 FUN_800f58f0: exit — tickStream, integrate, collision; on wallContact exit.
// ============================================================================
function anubisAction1Dash(actor: WBActor, ctx: StreamContext): void {
  if ((actor.fbPhaseSlots[1] ?? 0) !== 0) actor.visibilityTarget = null; // +0xcc=0 when +0x541
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_800f53ec — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.handlerTimer = ANUBIS_F.HANDLER_TIMER_SEED; // +0x558 = 60.0
      actor.wbCooldown55c = ANUBIS_F.COOLDOWN_SEED; // +0x55c = 2.0
      actor.wbStreamSlot54c = 0x20; // +0x54c = 0x20
      actor.wbDiveYaw54e = 0; // +0x54e = 0
      // FUN_80066838 speed gate (TODO unsurfaced) -> slow branch arms +0x541/+0xcc/+0x5ac.
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * ANUBIS_F.MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * ANUBIS_F.MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * ANUBIS_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_00677b0_
      // zz_004beb8_(-1, actor, 0xf, 3, 4, 8, 1) — startStream (no-op).
      void ctx;
      return;
    }
    case 1: { // FUN_800f54f8 — wait
      if (actor.streamHold1b03 !== 0) tickStream();
      actor.motion.x *= ANUBIS_F.MOTION_SCALE; actor.motion.y *= ANUBIS_F.MOTION_SCALE;
      actor.motion.z *= ANUBIS_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor);
      stepPartTargetPitch(actor, 0xc0);
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= ANUBIS_F.THRESHOLD ||
          stepTargetYaw(actor, 0xc0, 0, true)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.handlerTimer = ANUBIS_F.DIVE_TIMER_SEED; // +0x558 = 30.0
        actor.gravityCoeff = ANUBIS_F.THRESHOLD; // +0x50 = 0.0
        actor.yVel = ANUBIS_F.THRESHOLD; // +0x48 = 0.0
        actor.hDecel = ANUBIS_F.THRESHOLD; // +0x4c = 0.0
        actor.hSpeed = ANUBIS_F.THRESHOLD; // +0x44 = 0.0
        actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0;
        // zz_00b2190_(actor, 0) — afterimage reset (omitted).
      }
      return;
    }
    case 2: { // FUN_800f55d4 — dive
      if ((actor.contactP0 ?? 0) === 0) tickStream(); // +0x1cef == 0
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e514_(0xc0, &+0x54e)
      actor.hSpeed = ANUBIS_F.DIVE_SPEED * Math.cos(bamRad(actor.wbDiveYaw54e ?? 0));
      actor.yVel = ANUBIS_F.DIVE_SPEED * -Math.sin(bamRad(actor.wbDiveYaw54e ?? 0));
      integrateMotion(actor, ANUBIS_F.INTEGRATE_RATE, actor.lockYaw);
      collisionStep(actor);
      actor.handlerTimer -= actor.dt;
      // FUN_80066838(150, actor) speed-threshold (TODO unsurfaced -> 0, timer gates).
      if (actor.handlerTimer <= ANUBIS_F.THRESHOLD) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      }
      return;
    }
    case 3: { // FUN_800f56b0 — pullout
      tickStream();
      stepTargetYaw(actor, 0xc0, 0, true);
      applyVelocityDrag(actor, ANUBIS_F.MOTION_SCALE); // zz_006ed8c_(0.9)
      if ((actor.wbSpeed760 ?? 0) < ANUBIS_F.SPEED_THRESHOLD) {
        applyVelocityDrag(actor, ANUBIS_F.DRAG_FAST); // zz_006ed8c_(0.5)
      }
      integrateMotion(actor, ANUBIS_F.INTEGRATE_RATE, actor.activeYaw); // +0x5ac
      collisionStep(actor);
      if (actor.contactP1 !== 0) { // +0x1cf0 != 0
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.hSpeed *= 1.5; // FLOAT_80439130 DOUBLE factor
        actor.hDecel *= 1.5;
        actor.yVel = ANUBIS_F.CONTACT_YVEL; // +0x48 = 20.0
        actor.gravityCoeff = ANUBIS_F.CONTACT_GRAVITY; // +0x50 = -0.8
      }
      return;
    }
    case 4: { // FUN_800f5778 — descend (best-effort: charge drain + aim + advance gate)
      // zz_006de44_(actor, 0xf0f00) charge-drain -> +0x54c countdown (cosmetic).
      if ((actor.wbStreamSlot54c ?? 0) > 0) {
        actor.wbStreamSlot54c = (actor.wbStreamSlot54c ?? 0) - 1;
      }
      stepTargetYaw(actor, 0xc0, 0, true);
      integrateMotion(actor, ANUBIS_F.INTEGRATE_RATE, actor.lockYaw);
      collisionStep(actor);
      // Advance on contact (+0x1cef < 0) OR yVel < 0.
      if (actor.contactP0 < 0 || actor.yVel < ANUBIS_F.THRESHOLD) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.gravityCoeff = ANUBIS_F.EXIT_GRAVITY_FACTOR *
          (actor.descriptor?.handlerData6c ?? 0); // +0x50 = 3.0 * desc+0x6c
      }
      return;
    }
    case 5: { // FUN_800f58f0 — exit
      tickStream();
      integrateMotion(actor, ANUBIS_F.INTEGRATE_RATE, actor.lockYaw);
      const grounded = collisionStep(actor);
      if (grounded !== 0 || actor.wallContact !== 0) {
        // Exit: clear + strip + zz_006a750_(7) (upper cue 7) + seed +0x694 = 1.0 + dt.
        actor.housekeeping73f = 0;
        actor.controlWord = actor.controlWord & ~0x3;
        // zz_006a750_(actor, 7) — upper-body cue 7 (renderer-side; modeled via stateTimer).
        actor.stateTimer = ANUBIS_F.INTEGRATE_RATE + actor.dt; // +0x694 = 1.0 + dt
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// ANUBIS WING root dispatcher (FUN_800f4d70 indexes PTR_FUN_8031cb54[+0x580]).
// ----------------------------------------------------------------------------
export function createAnubisWingRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: anubisAction0(actor, ctx); return;
      case 1:
        if (actor.variantIndex === 0) action1SharedXSpecial(actor, ctx); // @0x8033ecb8
        else anubisAction1Dash(actor, ctx); // @0x8031cb8c
        return;
      case 3: sharedSpawnMachine(actor, ctx); return; // @0x804346a0
      default: return;
    }
  };
}

export function configureAnubisWingFamily(
  actor: RomActor,
  borgId: AnubisWingBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = WING_BLOB_BORG_NUMBERS[borgId] ?? 0xa04;
  actor.rootAction = createAnubisWingRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEMON WING — action 1 variant 1 bespoke dive (table @0x8033f948, 4 phases).
//   ph0 FUN_8014c394: setup — +0x540++, +0x558=60, +0x54a=0x14, +0x6ea=5, speed gate,
//                     aim 0xc0, motion=(pos-target)*0.95, collision, startStream, +0x80c=0.
//   ph1 FUN_8014c4c8: wait — motion*0.95+pos+collision+aim; drain +0x558; advance when
//                     <= 0 OR aim-ready; reseed +0x558=60, zero speeds, afterimage.
//   ph2 FUN_8014c5b8: dive — if +0x1d9: +0x54a--; aim 0xc0 + part-pitch; hSpeed=30*cos,
//                     yVel=30*-sin; integrate(1.0); collision; drain +0x558; advance when
//                     <= 0 OR +0x54a < 1; afterimage.
//   ph3 FUN_8014c6b0: exit — steerYaw*=0.9; tickStream; if +0x544==0 && +0x1b01: +0x544=1;
//                     else drag 0.95; integrate; collision; on wallContact exit.
// ============================================================================
function demonAction1Dive(actor: WBActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_8014c394 — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.handlerTimer = DEMON_F.TIMER_SEED; // +0x558 = 60.0
      actor.wbAimFlag54a = 0x14; // +0x54a = 0x14
      actor.wbStreamSlot6ea = 5; // +0x6ea = 5
      // FUN_80066838 speed gate (TODO unsurfaced).
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * DEMON_F.MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * DEMON_F.MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * DEMON_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_00677b0_
      actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1;
      actor.accumulator80c = DEMON_F.THRESHOLD; // +0x80c = 0.0
      void ctx;
      return;
    }
    case 1: { // FUN_8014c4c8 — wait
      actor.motion.x *= DEMON_F.MOTION_SCALE; actor.motion.y *= DEMON_F.MOTION_SCALE;
      actor.motion.z *= DEMON_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor);
      if (actor.streamHold1b03 !== 0) tickStream();
      stepPartTargetPitch(actor, 0xc0);
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= DEMON_F.THRESHOLD ||
          stepTargetYaw(actor, 0xc0, 0, true)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.handlerTimer = DEMON_F.TIMER_SEED; // +0x558 = 60.0
        actor.gravityCoeff = DEMON_F.THRESHOLD; // +0x50 = 0.0
        actor.yVel = DEMON_F.THRESHOLD; actor.hDecel = DEMON_F.THRESHOLD; actor.hSpeed = DEMON_F.THRESHOLD;
        actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0;
        // zz_0092dcc_(actor, 0) — unknown VFX (TODO, not ported).
      }
      return;
    }
    case 2: { // FUN_8014c5b8 — dive
      if ((actor.wbFlag1d9 ?? 0) !== 0) {
        actor.wbAimFlag54a = (actor.wbAimFlag54a ?? 0) - 1; // +0x54a -= 1
      }
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
      actor.hSpeed = DEMON_F.DIVE_SPEED * Math.cos(bamRad(actor.steerYaw)); // +0x18da
      actor.yVel = DEMON_F.DIVE_SPEED * -Math.sin(bamRad(actor.steerYaw));
      integrateMotion(actor, DEMON_F.INTEGRATE_RATE, actor.lockYaw);
      collisionStep(actor);
      tickStream();
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= DEMON_F.THRESHOLD || (actor.wbAimFlag54a ?? 0) < 1) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      }
      return;
    }
    case 3: { // FUN_8014c6b0 — exit
      actor.steerYaw = Math.trunc(actor.steerYaw * DEMON_F.STEER_DECAY); // +0x18da *= 0.9
      tickStream();
      if ((actor.fbPhaseSlots[1] ?? 0) === 0) {
        if ((actor.wbDashGate1b01 ?? 0) !== 0) {
          actor.fbPhaseSlots[1] = 1; // +0x544 = 1
          // zz_004beb8_ startStream (no-op).
        }
      } else {
        applyVelocityDrag(actor, DEMON_F.MOTION_SCALE); // zz_006ed8c_(0.95)
      }
      integrateMotion(actor, DEMON_F.INTEGRATE_RATE, actor.lockYaw);
      if ((actor.hSpeed ?? 0) < DEMON_F.THRESHOLD) {
        actor.hSpeed = DEMON_F.THRESHOLD;
        actor.hDecel = DEMON_F.THRESHOLD;
      }
      const grounded = collisionStep(actor);
      if (actor.wallContact !== 0) {
        landExit(actor, 0, true); // zz_006a5a4_ / zz_006a474_
        void grounded;
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// DEMON WING root dispatcher (action 0 = shared spawn @0x804346a0, action 1 variant).
// ----------------------------------------------------------------------------
export function createDemonWingRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: sharedSpawnMachine(actor, ctx); return; // @0x804346a0
      case 1:
        if (actor.variantIndex === 0) action1SharedXSpecial(actor, ctx); // @0x8033ecb8
        else demonAction1Dive(actor, ctx); // @0x8033f948
        return;
      default: return;
    }
  };
}

export function configureDemonWingFamily(
  actor: RomActor,
  borgId: DemonWingBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = WING_BLOB_BORG_NUMBERS[borgId] ?? 0xa02;
  actor.rootAction = createDemonWingRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEATH BORG SIGMA — action 0 single-shot volley (table @0x80373dfc, 4 phases).
// Handler zz_019d770_ runs preamble zz_019ddbc_ (same shape as wing), then the
// +0x545/+0x544 animation sub-tables, then the +0x540 main table. SINGLE-SHOT
// (+0x6ec seed = 1), borg-switched effect spawn (0xa05->zz_00c3be0_(0x1d),
// 0xa0a->zz_00c3be0_(0x1c)).
//   ph0 FUN_8019d868: setup — +0x540=1, +0x560=30, +0x54c=0, arm (zz_019de44_),
//                     startStream.
//   ph1 FUN_8019d8d0: wait — +0x54c=0; advance when +0x560<0 OR (contact && aim unsettled);
//                     on advance fire (zz_019de60_), +0x54c=5, startStream.
//   ph2 FUN_8019d96c: volley — charged latch; +0x54c=5; if +0x558<=0: if +0x6ec<1 advance
//                     (+0x55c=60,+0x54c=10) else fire+loop; else drain. Abort on +0x5d8&0xf0.
//   ph3 FUN_8019dab0: cooldown — charged latch; +0x54c=10; charged+ammo(non-consume) ->
//                     +0x540-- (re-arm+fire); else drain +0x55c; exit when <= 0 OR contact.
// ============================================================================
function sigmaPreamble(actor: WBActor): void {
  const ready = stepTargetYaw(actor, 0x81, 0); // zz_006d0dc_(0x81)
  actor.wbAimFlag54a = ready ? 0 : 1; // +0x54a
  stepPartTargetPitch(actor, 0xc1); // zz_006e1ac_(0xc1, 1)
  const hasTarget = actor.visibilityTarget !== null ? 1 : 0;
  const err = hasTarget !== 0 ? -1 : 0;
  actor.wbStreamClass6eb = err !== 0
    ? ((((actor.turnErrorYaw + 0x2000) >>> 14) & 3) + 1) & 0xff : 0;
}

function sigmaArmVolley(actor: WBActor): void {
  actor.wbCharged745 = 0; // +0x745 = 0
  actor.wbVolleyCount6ec = SIGMA_F.VOLLEY_SHOT_CAP; // +0x6ec = 1 (single shot)
  actor.handlerTimer = SIGMA_F.HANDLER_TIMER_SEED; // +0x558 = 60.0
}

function sigmaFireShot(actor: WBActor, ctx: StreamContext): void {
  actor.wbVolleyCount6ec = (actor.wbVolleyCount6ec ?? 0) - 1; // +0x6ec -= 1
  actor.handlerTimer = SIGMA_F.SHOT_INTERVAL; // +0x558 = 4.0 (FLOAT_8043b4a0)
  actor.wbCharged745 = 0; // +0x745 = 0
  actor.cmdChargedRanged = 0; // +0x587 = 0
  if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(actor, 0, 1, 1)
    const type = actor.borgNumber === 0xa05 ? 0x1d : 0x1c; // 0xa05->0x1d, 0xa0a->0x1c
    ctx.onFamilyProjectile?.(actor, SIGMA_EFFECT_SPAWNER_C3BE0, type); // zz_00c3be0_
  }
}

function sigmaAction0(actor: WBActor, ctx: StreamContext): void {
  sigmaPreamble(actor); // zz_019ddbc_
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_8019d868 — setup
      actor.fbPhaseSlots[0] = 1; // +0x540 = 1
      actor.wbDiveTimer560 = SIGMA_F.DIVE_TIMER_SEED; // +0x560 = 30.0
      actor.wbStreamSlot54c = 0; // +0x54c = 0
      sigmaArmVolley(actor); // zz_019de44_
      // zz_004beb8_ startStream (no-op).
      return;
    }
    case 1: { // FUN_8019d8d0 — wait
      actor.wbStreamSlot54c = 0; // +0x54c = 0
      if ((actor.wbDiveTimer560 ?? 0) < SIGMA_F.THRESHOLD ||
          (actor.wallContact !== 0 && (actor.wbAimFlag54a ?? 0) !== 0)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        sigmaFireShot(actor, ctx); // zz_019de60_ — shot 1 (+0x6ec 1->0)
        actor.wbStreamSlot54c = 5; // +0x54c = 5
      }
      return;
    }
    case 2: { // FUN_8019d96c — volley
      if (((actor.inputEdge5d4 ?? 0) & SIGMA_F.CHARGE_INPUT_BIT) !== 0) {
        actor.wbCharged745 = 1; // +0x745 = 1
      }
      actor.wbStreamSlot54c = 5; // +0x54c = 5
      if (actor.handlerTimer <= SIGMA_F.THRESHOLD) { // +0x558 <= 0.0
        if ((actor.wbVolleyCount6ec ?? 0) < 1) {
          actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
          actor.wbCooldown55c = SIGMA_F.HANDLER_TIMER_SEED; // +0x55c = 60.0
          actor.wbStreamSlot54c = 10; // +0x54c = 10
        } else {
          // zz_006bf80_(actor) — target re-acquire (TODO no-op).
          sigmaFireShot(actor, ctx); // zz_019de60_
        }
      } else {
        actor.handlerTimer -= actor.dt; // +0x558 -= dt
      }
      if (((actor.inputHeld5d8 ?? 0) & SIGMA_F.ABORT_INPUT_MASK) !== 0) {
        landExit(actor, (actor.handlerTimer ?? 0) + actor.dt); // +0x694 = +0x558 + dt
      }
      return;
    }
    case 3: { // FUN_8019dab0 — cooldown
      if (((actor.inputEdge5d4 ?? 0) & SIGMA_F.CHARGE_INPUT_BIT) !== 0) {
        actor.wbCharged745 = 1;
      }
      actor.wbStreamSlot54c = 10; // +0x54c = 10
      if ((actor.wbCharged745 ?? 0) !== 0 &&
          allocateWeapon(actor, ctx, 0, 1, false)) { // non-consume gate
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- (back to ph2)
        sigmaArmVolley(actor); // zz_019de44_ (re-arm)
        // zz_006bf80_(actor) — target re-acquire (TODO no-op).
        sigmaFireShot(actor, ctx); // zz_019de60_
        return;
      }
      if (((actor.inputHeld5d8 ?? 0) & SIGMA_F.ABORT_INPUT_MASK) === 0 &&
          (actor.wbCooldown55c = (actor.wbCooldown55c ?? 0) - actor.dt,
            (actor.wbCooldown55c ?? 0) > SIGMA_F.THRESHOLD) &&
          actor.wallContact === 0) {
        return;
      }
      landExit(actor, 0); // clear + strip + land transition
      return;
    }
    default: return;
  }
}

// ============================================================================
// DEATH BORG SIGMA — action 1 variant 1 bespoke dive (table @0x80373e20, 4 phases).
// Handler zz_019dfbc_ dispatches +0x540.
//   ph0 zz_019e00c_: setup — +0x540++, +0x6ea=3, speed gate, +0x558=60, aim 0xc0,
//                    motion=(pos-target)*0.95, collision, startStream, +0x80c=0.
//   ph1 zz_019e138_: wait — tickStream, motion*0.95+pos+collision+aim; drain +0x558;
//                    advance when <= 0 OR aim-ready; reseed +0x558=60.
//   ph2 zz_019e1f4_: dive — if +0x1d9: +0x541=0xff; aim 0xc0 + part-pitch;
//                    hSpeed=30*cos(steerYaw), yVel=30*-sin; integrate(1.0); collision;
//                    drain +0x558; advance when <= 0 AND +0x1b01; reseed +0x50=desc+0x6c.
//   ph3 zz_019e310_: exit — steerYaw*=0.9; tickStream; drag 0.9; integrate; collision;
//                    on wallContact exit.
// ============================================================================
function sigmaAction1Dive(actor: WBActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // zz_019e00c_ — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wbStreamSlot6ea = 3; // +0x6ea = 3
      // FUN_80066838 speed gate (TODO unsurfaced).
      actor.handlerTimer = SIGMA_F.HANDLER_TIMER_SEED; // +0x558 = 60.0
      stepTargetYaw(actor, 0xc0, 0, true); // zz_006d144_(0xc0)
      stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * SIGMA_F.MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * SIGMA_F.MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * SIGMA_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor);
      actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1;
      actor.accumulator80c = SIGMA_F.THRESHOLD; // +0x80c = 0.0
      void ctx;
      return;
    }
    case 1: { // zz_019e138_ — wait
      if (actor.streamHold1b03 !== 0) tickStream();
      actor.motion.x *= SIGMA_F.MOTION_SCALE; actor.motion.y *= SIGMA_F.MOTION_SCALE;
      actor.motion.z *= SIGMA_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor);
      stepPartTargetPitch(actor, 0xc0);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SIGMA_F.THRESHOLD ||
          stepTargetYaw(actor, 0xc0, 0, true)) {
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.handlerTimer = SIGMA_F.HANDLER_TIMER_SEED; // +0x558 = 60.0
      }
      return;
    }
    case 2: { // zz_019e1f4_ — dive
      if ((actor.wbFlag1d9 ?? 0) !== 0) actor.fbPhaseSlots[1] = 0xff; // +0x541 = 0xff
      stepTargetYaw(actor, 0xc0, 0, true);
      stepPartTargetPitch(actor, 0xc0);
      actor.hSpeed = SIGMA_F.DIVE_TIMER_SEED * Math.cos(bamRad(actor.steerYaw));
      actor.yVel = SIGMA_F.DIVE_TIMER_SEED * -Math.sin(bamRad(actor.steerYaw));
      integrateMotion(actor, SIGMA_F.INTEGRATE_RATE, actor.lockYaw);
      collisionStep(actor);
      tickStream();
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SIGMA_F.THRESHOLD) {
        actor.handlerTimer = SIGMA_F.THRESHOLD; // +0x558 = 0.0
        if ((actor.wbDashGate1b01 ?? 0) !== 0) {
          actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
          actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = desc+0x6c
          actor.wbStreamSlot6ea = (actor.wbStreamSlot6ea ?? 0) + 1;
        }
      }
      return;
    }
    case 3: { // zz_019e310_ — exit
      actor.steerYaw = Math.trunc(actor.steerYaw * SIGMA_F.STEER_DECAY); // *= 0.9
      tickStream();
      applyVelocityDrag(actor, SIGMA_F.STEER_DECAY); // zz_006ed8c_(0.9)
      integrateMotion(actor, SIGMA_F.INTEGRATE_RATE, actor.lockYaw);
      const grounded = collisionStep(actor);
      if (actor.wallContact !== 0) {
        landExit(actor, 0, grounded === 0); // zz_006a5a4_ air / zz_006a474_ ground
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// DEATH BORG SIGMA root dispatcher.
// ----------------------------------------------------------------------------
export function createDeathBorgSigmaRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: sigmaAction0(actor, ctx); return;
      case 1:
        if (actor.variantIndex === 0) action1SharedXSpecial(actor, ctx); // @0x8033ecb8
        else sigmaAction1Dive(actor, ctx); // @0x80373e20
        return;
      default: return;
    }
  };
}

export function configureDeathBorgSigmaFamily(
  actor: RomActor,
  borgId: DeathBorgSigmaBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = WING_BLOB_BORG_NUMBERS[borgId] ?? 0xa05;
  actor.rootAction = createDeathBorgSigmaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEATH BORG BETA II — action 2 X-special spawn (table @0x8036fb48, 3 phases).
// Handler zz_01994b0_ dispatches +0x540.
//   ph0 FUN_80199504: setup — +0x540++, +0x6ea=0 (1 if +0x5e0&0x40), zero speeds, aim
//                     0xc1, motion=(pos-target)*0.95, ground snap, startStream, +0x80c=0.
//   ph1 FUN_80199608: dive — when +0x1cf0>0: +0x540++, set speeds, borg-switched spawn:
//                     0x105 (BETA II): ammo gate (widx 2, consume) -> zz_0084600_(0xb)+
//                       zz_0084600_(0xc) [dual child spawn];
//                     0x10a (BETA III): ammo gate (widx 0, consume) -> loop 2 hardpoints:
//                       +0x144[i]=1, zz_00e0e90_(i+4, 2); zz_00f036c_(0xdb) if any.
//                     afterimage if motion magnitude > 3.0.
//   ph2 FUN_80199894: exit — steerYaw*=0.9; tickStream; integrate(1.0); collision;
//                     on wallContact exit (clear + strip + land transition + seed +0x694).
// ============================================================================
function betaAction2(actor: WBActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: { // FUN_80199504 — setup
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.wbStreamSlot6ea = 0; // +0x6ea = 0
      if ((actor.controlWord & 0x40) !== 0) actor.wbStreamSlot6ea = 1; // +0x6ea = 1
      actor.gravityCoeff = BETA_F.THRESHOLD; // +0x50 = 0.0
      actor.yVel = BETA_F.THRESHOLD; actor.hDecel = BETA_F.THRESHOLD; actor.hSpeed = BETA_F.THRESHOLD;
      actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0;
      stepTargetYaw(actor, 0xc1, 0); // zz_006d0dc_(0xc1, 0)
      if ((actor.controlWord & 0x40) !== 0) stepPartTargetPitch(actor, 0xc1); // 0xc1, 1
      actor.motion.x = (actor.pos.x - actor.targetCache5e8.x) * BETA_F.MOTION_SCALE;
      actor.motion.y = (actor.pos.y - actor.targetCache5e8.y) * BETA_F.MOTION_SCALE;
      actor.motion.z = (actor.pos.z - actor.targetCache5e8.z) * BETA_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      // zz_00679d0_(actor) — ground-snap revert (best-effort via collision probe).
      collisionStep(actor);
      // zz_004beb8_(-1, actor, 0xf, 4, +0x6ea, -1, -1) — startStream (no-op).
      actor.accumulator80c = BETA_F.THRESHOLD; // +0x80c = 0.0
      return;
    }
    case 1: { // FUN_80199608 — dive + borg-switched spawn
      tickStream();
      stepTargetYaw(actor, 0xc1, 0);
      if ((actor.controlWord & 0x40) !== 0) stepPartTargetPitch(actor, 0xc1);
      actor.motion.x *= BETA_F.MOTION_SCALE; actor.motion.y *= BETA_F.MOTION_SCALE;
      actor.motion.z *= BETA_F.MOTION_SCALE;
      actor.pos.x += actor.motion.x; actor.pos.y += actor.motion.y; actor.pos.z += actor.motion.z;
      collisionStep(actor); // zz_00679d0_
      if (actor.contactP1 > 0) { // +0x1cf0 > 0
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
        actor.lockYaw = (actor.heading - 0x8000) & 0xffff; // +0x5ae = +0x72 - 0x8000
        actor.hSpeed = BETA_F.DIVE_HSPEED; // +0x44 = 20.0
        actor.hDecel = BETA_F.DIVE_HDECEL; // +0x4c = -0.3
        actor.yVel = BETA_F.DIVE_YVEL; // +0x48 = 10.0
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = desc+0x6c
        if (actor.borgNumber === 0x105) {
          // BETA II: dual child spawn (weapon slot 2, consume).
          if (allocateWeapon(actor, ctx, 2, 1, true)) {
            ctx.onFamilyProjectile?.(actor, BETA_CHILD_SPAWNER_84600, 0xb); // zz_0084600_(0xb)
            ctx.onFamilyProjectile?.(actor, BETA_CHILD_SPAWNER_84600, 0xc); // zz_0084600_(0xc)
          }
        } else if (actor.borgNumber === 0x10a) {
          // BETA III: hardpoint spawn (weapon slot 0, consume).
          if (allocateWeapon(actor, ctx, 0, 1, true)) {
            let fired = 0;
            for (let i = 0; i < 2; i += 1) {
              if (actor.attachmentFlags14c[i] === 0) {
                actor.attachmentFlags14c[i] = 1; // +0x144[i] = 1
                ctx.onFamilyProjectile?.(actor, BETA_HARDPOINT_SPAWNER_E0E90, i + 4);
                fired += 1;
              }
            }
            if (fired !== 0) ctx.onPlayCue?.(actor, 0xdb); // zz_00f036c_(0xdb)
          }
        }
      }
      if (vecMagnitude(actor.motion) > BETA_F.AFTERIMAGE_THRESHOLD) {
        // zz_00b22f4_(actor) — afterimage step (renderer-side, omitted).
      }
      return;
    }
    case 2: { // FUN_80199894 — exit
      actor.steerYaw = Math.trunc(actor.steerYaw * BETA_F.STEER_DECAY); // +0x18da *= 0.9
      tickStream();
      integrateMotion(actor, BETA_F.INTEGRATE_RATE, actor.lockYaw); // FUN_80067310(1.0)
      const grounded = collisionStep(actor);
      if (grounded !== 0 && (actor.contactP0 ?? 0) >= 0) {
        applyVelocityDrag(actor, BETA_F.VELOCITY_DRAG); // zz_006ed8c_(0.1)
      }
      if (grounded === 0 || (actor.contactP0 ?? 0) < 0 || actor.wallContact !== 0) {
        // Exit: clear + strip + land transition + seed +0x694 = 1.0 + dt.
        actor.housekeeping73f = 0;
        actor.controlWord = actor.controlWord & ~0x3;
        if (grounded === 0) romAirKnockoutReturn(actor); // zz_006a5a4_
        else if ((actor.controlWord & 0x40) === 0) romGroundIdleReturn(actor); // zz_006a474_
        else { /* zz_006a750_(actor, 7) — upper cue 7 (renderer-side). */ }
        actor.stateTimer = BETA_F.INTEGRATE_RATE + actor.dt; // +0x694 = 1.0 + dt
      }
      if ((actor.hSpeed ?? 0) > BETA_F.AFTERIMAGE_THRESHOLD) {
        // zz_00b22f4_(actor) — afterimage (omitted).
      }
      return;
    }
    default: return;
  }
}

// ============================================================================
// DEATH BORG BETA II — action 0 approach machine (tables @0x8036faf4 setup +
// @0x8036fb18/@0x8036fb24 ground/air). PARTIAL PORT: the full movement machine
// involves zz_006a3d0_ command-record dispatch (transitions to other actions) and
// per-variant aim/approach state tables not surfaced as clean phase transitions.
// The testable, spawn-producing path is ported: zz_01989dc_ setup + the contact-fire
// zz_019932c_ (zz_0082824_(0x38/0x39) when +0x1cef > 0). The movement/aim integration
// is a best-effort documented pass.
//   zz_01989dc_ setup: +0x540=1, +0x542=0, +0x560=30, +0x558=5, burst latch.
//   zz_019932c_ fire:  on contact (+0x1cef > 0): +0x1900=0; ammo gate (widx 0, consume)
//                      -> zz_0082824_(0x38 or 0x39 if +0x1b04).
// ============================================================================
function betaAction0(actor: WBActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) {
    // zz_01989dc_ — setup (runs once on entry).
    actor.fbPhaseSlots[0] = 1; // +0x540 = 1
    actor.fbPhaseSlots[2] = 0; // +0x542 = 0
    actor.wbDiveTimer560 = BETA_F.DIVE_TIMER_SEED; // +0x560 = 30.0
    actor.handlerTimer = BETA_F.HANDLER_TIMER_SEED; // +0x558 = 5.0
    // +0x1b04 = +0x1b44 burst mirror (unsurfaced -> 0).
    return;
  }
  // Approach/aim pass: drain +0x558; on contact (+0x1cef > 0) fire zz_019932c_.
  stepTargetYaw(actor, 0xc1, 0); // zz_006d0dc_ aim (best-effort).
  if ((actor.contactP0 ?? 0) > 0) {
    // zz_019932c_ — contact fire.
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    if (allocateWeapon(actor, ctx, 0, 1, true)) { // zz_006dbe0_(actor, 0, 1, 1)
      const type = (actor.wbBurst1b04 ?? 0) !== 0 ? 0x39 : 0x38;
      ctx.onFamilyProjectile?.(actor, BETA_SHOT_HELPER, type); // zz_0082824_
    }
  } else if (actor.handlerTimer > BETA_F.THRESHOLD) {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
  }
}

// ----------------------------------------------------------------------------
// DEATH BORG BETA II root dispatcher.
// ----------------------------------------------------------------------------
export function createDeathBorgBetaRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) { // +0x580
      case 0: betaAction0(actor, ctx); return;
      case 2: betaAction2(actor, ctx); return; // @0x8036fb48
      default: return;
    }
  };
}

export function configureDeathBorgBetaFamily(
  actor: RomActor,
  borgId: DeathBorgBetaBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = WING_BLOB_BORG_NUMBERS[borgId] ?? 0x105;
  actor.rootAction = createDeathBorgBetaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirrors rom.selfcheck.ts style. Covers:
//   - ANUBIS WING action 0: 3-shot volley, ammo-gate, charged re-volley, exit.
//   - ANUBIS WING action 1 bespoke dash: ph0 setup + timer transitions.
//   - Shared X-special (via ANUBIS action 1 v0): ph0 setup + ph1 advance.
//   - Shared spawn machine (via DEMON action 0 / ANUBIS action 3): ph0 setup.
//   - DEMON WING action 1 bespoke dive: ph0 setup + ph1 advance.
//   - DEATH BORG SIGMA action 0: single-shot volley + charged re-volley.
//   - DEATH BORG SIGMA action 1 bespoke dive: ph0 setup + ph1 advance.
//   - DEATH BORG BETA II action 2: ph0 setup + ph1 borg-switched spawn (0x105/0x10a).
//   - DEATH BORG BETA II action 0: contact-fire zz_0082824_.
// ============================================================================
export function runWingBlobClusterSelfTests(assert: (cond: boolean, msg: string) => void): void {
  type Shot = { addr: number; type: number };

  // --- ANUBIS WING action 0: 2-phase hover volley, 3 shots, then exit. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureAnubisWingFamily(a, "pl0a04", sctx);
    assert(a.borgNumber === 0xa04, "ANUBIS WING pl0a04 borgNumber stamped 0xa04");
    assert(a.rootAction !== null, "ANUBIS WING bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;

    // ph0 setup + wait: arm volley (+0x6ec=3, +0x558=60), then drive +0x560 negative.
    root(a);
    const s = a as RomActor & WingBlobScratch;
    assert(s.wbVolleyCount6ec === ANUBIS_F.VOLLEY_SHOT_CAP, "ANUBIS ph0 arms volley +0x6ec = 3");
    assert(s.wbDiveTimer560 === ANUBIS_F.DIVE_TIMER_SEED, "ANUBIS ph0 seeds +0x560 = 30.0");
    assert(a.handlerTimer === ANUBIS_F.HANDLER_TIMER_SEED, "ANUBIS ph0 seeds +0x558 = 60.0");
    s.wbDiveTimer560 = -1;
    root(a); // advance to ph1, fire shot 1
    assert(a.fbPhaseSlots[0] === 1, "ANUBIS ph0 advances 0 -> 1 when +0x560 < 0.0");
    assert(s.wbVolleyCount6ec === 2, "ANUBIS ph0 fired shot 1 (+0x6ec 3 -> 2)");
    assert(shots.length === 1 && shots[0]!.addr === ANUBIS_WING_SHOT_SPAWNER && shots[0]!.type === 0,
      `ANUBIS ph0 spawns zz_00ffba8_(0) for pl0a04 (got ${JSON.stringify(shots)})`);

    // ph1 volley: drain +0x558 to fire remaining 2 shots, then exit.
    for (let i = 0; i < 20 && a.fbPhaseSlots[0] === 1; i += 1) {
      a.handlerTimer = 0; // force the <= 0.0 fire branch
      root(a);
    }
    assert(shots.length === 3, `ANUBIS volley fired 3 shots total (got ${shots.length})`);
    assert(shots.every((sp) => sp.addr === ANUBIS_WING_SHOT_SPAWNER && sp.type === 0),
      "all ANUBIS volley shots route zz_00ffba8_(0) for pl0a04");
  }

  // --- ANUBIS WING action 0 ammo-gate failure: spawn suppressed, counter still drains. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureAnubisWingFamily(a, "pl0a08", sctx);
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    (a as RomActor & WingBlobScratch).wbDiveTimer560 = -1;
    a.rootAction!(a); // ph0 -> ph1 (fire, ammo denied)
    assert(a.fbPhaseSlots[0] === 1, "ANUBIS ammo-fail still advances ph0 -> ph1");
    assert(shots.length === 0, "ANUBIS ammo-fail suppresses the volley spawn");
    assert((a as RomActor & WingBlobScratch).wbVolleyCount6ec === 2,
      "ANUBIS ammo-fail still decrements volley +0x6ec (3 -> 2)");
  }

  // --- ANUBIS WING action 0 charged re-volley loop. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: (_a, _s, _c, mode) => mode === 0 ? true : true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureAnubisWingFamily(a, "pl0a09", sctx);
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // start in ph1
    a.inputEdge5d4 = ANUBIS_F.CHARGE_INPUT_BIT; // +0x5d4 & 0x40 -> +0x745 = 1
    const s = a as RomActor & WingBlobScratch;
    s.wbVolleyCount6ec = 0; // volley exhausted
    a.handlerTimer = 0; // force the <= 0.0 branch
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "ANUBIS charged + ammo -> re-volley loops (stays ph1)");
    assert(s.wbVolleyCount6ec === ANUBIS_F.VOLLEY_SHOT_CAP - 1,
      "ANUBIS re-volley re-arms +0x6ec = 3 then fires shot 1 (-> 2)");
    assert(shots.length === 1, "ANUBIS re-volley fires shot 1 (zz_00ffba8_(3) for pl0a09)");
    assert(shots[0]!.type === 3, "ANUBIS re-volley type 3 for pl0a09");
  }

  // --- ANUBIS WING action 1 bespoke dash (variant 1): ph0 setup + ph1 timer advance. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureAnubisWingFamily(a, "pl0a04", sctx);
    a.actionIndex = 1; a.variantIndex = 1; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "ANUBIS dash ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === ANUBIS_F.HANDLER_TIMER_SEED, "ANUBIS dash ph0 seeds +0x558 = 60.0");
    const s = a as RomActor & WingBlobScratch;
    assert(s.wbCooldown55c === ANUBIS_F.COOLDOWN_SEED, "ANUBIS dash ph0 seeds +0x55c = 2.0");
    // ph1 wait: drain +0x558 to <= 0 to advance.
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "ANUBIS dash ph1 advances 1 -> 2 when +0x558 <= 0.0");
  }

  // --- Shared X-special (ANUBIS action 1 variant 0): ph0 setup + ph1 advance. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureAnubisWingFamily(a, "pl0a04", sctx);
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "X-special ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === XSPEC_F.TIMER_SEED, "X-special ph0 seeds +0x558 = 60.0");
    const s = a as RomActor & WingBlobScratch;
    assert(s.wbCharged746 === 0, "X-special ph0 clears +0x746");
    a.handlerTimer = 0;
    a.rootAction!(a); // ph1 advance
    assert(a.fbPhaseSlots[0] === 2, "X-special ph1 advances 1 -> 2 when +0x558 <= 0.0");
    assert(a.handlerTimer === XSPEC_F.RESEED, "X-special ph1 reseeds +0x558 = 20.0");
  }

  // --- Shared spawn machine (DEMON WING action 0): ph0 setup. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureDemonWingFamily(a, "pl0a02", sctx);
    assert(a.borgNumber === 0xa02, "DEMON WING pl0a02 borgNumber stamped 0xa02");
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "shared-spawn ph0 advances +0x540 0 -> 1");
    assert(a.hSpeed === 0.0, "shared-spawn ph0 zeroes +0x44");
  }

  // --- Shared spawn machine (DEMON WING 0xa02) contact spawn: zz_0154e28_. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureDemonWingFamily(a, "pl0a02", sctx);
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1; // ph1
    a.contactP0 = 1; // +0x1cef >= 1 (contact edge)
    a.rootAction!(a);
    assert(shots.length === 1 && shots[0]!.addr === DEMON_WING_SPAWNER_154E28,
      `DEMON 0xa02 contact -> zz_0154e28_ (got ${JSON.stringify(shots)})`);
    assert(a.contactP0 === 0, "shared-spawn ph1 consumes the contact edge (+0x1cef -> 0)");
  }

  // --- DEMON WING action 1 bespoke dive (variant 1): ph0 setup + ph1 advance. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureDemonWingFamily(a, "pl0a02", sctx);
    a.actionIndex = 1; a.variantIndex = 1; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "DEMON dive ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === DEMON_F.TIMER_SEED, "DEMON dive ph0 seeds +0x558 = 60.0");
    const s = a as RomActor & WingBlobScratch;
    assert(s.wbAimFlag54a === 0x14, "DEMON dive ph0 seeds +0x54a = 0x14");
    a.handlerTimer = 0;
    a.rootAction!(a); // ph1 advance
    assert(a.fbPhaseSlots[0] === 2, "DEMON dive ph1 advances 1 -> 2 when +0x558 <= 0.0");
  }

  // --- DEATH BORG SIGMA action 0: single-shot volley + charged re-volley. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureDeathBorgSigmaFamily(a, "pl0a05", sctx);
    assert(a.borgNumber === 0xa05, "SIGMA pl0a05 borgNumber stamped 0xa05");
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0 setup (FUN_8019d868 sets +0x540 = 1)
    const s = a as RomActor & WingBlobScratch;
    assert(a.fbPhaseSlots[0] === 1, "SIGMA ph0 setup sets +0x540 = 1");
    assert(s.wbVolleyCount6ec === SIGMA_F.VOLLEY_SHOT_CAP, "SIGMA ph0 arms volley +0x6ec = 1");
    assert(s.wbDiveTimer560 === SIGMA_F.DIVE_TIMER_SEED, "SIGMA ph0 seeds +0x560 = 30.0");
    s.wbDiveTimer560 = -1;
    a.rootAction!(a); // ph1 wait -> advance + fire shot 1
    assert(a.fbPhaseSlots[0] === 2, "SIGMA ph1 wait advances +0x540 1 -> 2 when +0x560 < 0.0");
    assert(s.wbVolleyCount6ec === 0, "SIGMA fired shot 1 (+0x6ec 1 -> 0)");
    assert(shots.length === 1 && shots[0]!.addr === SIGMA_EFFECT_SPAWNER_C3BE0 && shots[0]!.type === 0x1d,
      `SIGMA 0xa05 spawns zz_00c3be0_(0x1d) (got ${JSON.stringify(shots)})`);
    // ph2 volley: +0x558 drained, volley exhausted -> advance to cooldown (+0x540 2->3).
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3, "SIGMA ph2 volley advances +0x540 2 -> 3 when exhausted");
    assert((s.wbCooldown55c ?? 0) === SIGMA_F.HANDLER_TIMER_SEED, "SIGMA ph2->3 seeds +0x55c = 60.0");
    // ph3 charged re-volley: charged + non-consuming ammo -> +0x540-- back to ph2 (3->2).
    a.inputEdge5d4 = SIGMA_F.CHARGE_INPUT_BIT;
    s.wbVolleyCount6ec = 0;
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "SIGMA charged + ammo -> ph3 loops +0x540 3 -> 2");
    assert(s.wbVolleyCount6ec === 0, "SIGMA re-volley re-arms +0x6ec = 1 then fires (-> 0)");
    assert(shots.length === 2, "SIGMA re-volley fires a second zz_00c3be0_(0x1d)");
  }

  // --- DEATH BORG SIGMA 0xa0a spawns type 0x1c. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureDeathBorgSigmaFamily(a, "pl0a0a", sctx);
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0
    (a as RomActor & WingBlobScratch).wbDiveTimer560 = -1;
    a.rootAction!(a); // ph1 fire
    assert(shots.length === 1 && shots[0]!.type === 0x1c,
      `SIGMA 0xa0a spawns zz_00c3be0_(0x1c) (got ${JSON.stringify(shots)})`);
  }

  // --- DEATH BORG SIGMA action 1 bespoke dive: ph0 setup + ph1 advance. ---
  {
    const a = scratchOf(createRomActor());
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    configureDeathBorgSigmaFamily(a, "pl0a05", sctx);
    a.actionIndex = 1; a.variantIndex = 1; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "SIGMA dive ph0 advances +0x540 0 -> 1");
    assert(a.handlerTimer === SIGMA_F.HANDLER_TIMER_SEED, "SIGMA dive ph0 seeds +0x558 = 60.0");
    a.handlerTimer = 0;
    a.rootAction!(a); // ph1 advance
    assert(a.fbPhaseSlots[0] === 2, "SIGMA dive ph1 advances 1 -> 2 when +0x558 <= 0.0");
  }

  // --- DEATH BORG BETA II action 2 (0x105): ph0 setup + ph1 dual child spawn. ---
  {
    const shots: Shot[] = [];
    const cues: number[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onPlayCue: (_a, cue) => cues.push(cue),
    };
    const a = scratchOf(createRomActor());
    configureDeathBorgBetaFamily(a, "pl0105", sctx);
    assert(a.borgNumber === 0x105, "BETA II pl0105 borgNumber stamped 0x105");
    a.actionIndex = 2; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "BETA act2 ph0 advances +0x540 0 -> 1");
    assert(a.hSpeed === 0.0, "BETA act2 ph0 zeroes +0x44");
    // ph1 dive: contact (+0x1cf0 > 0) -> dual child spawn (0xb, 0xc).
    a.contactP1 = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "BETA act2 ph1 advances 1 -> 2 on +0x1cf0 > 0");
    assert(shots.length === 2, `BETA 0x105 dual child spawn (got ${shots.length} shots)`);
    assert(shots[0]!.addr === BETA_CHILD_SPAWNER_84600 && shots[0]!.type === 0xb,
      "BETA 0x105 child spawn 0 -> zz_0084600_(0xb)");
    assert(shots[1]!.addr === BETA_CHILD_SPAWNER_84600 && shots[1]!.type === 0xc,
      "BETA 0x105 child spawn 1 -> zz_0084600_(0xc)");
  }

  // --- DEATH BORG BETA III (0x10a) action 2: hardpoint spawn + cue 0xdb. ---
  {
    const shots: Shot[] = [];
    const cues: number[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onPlayCue: (_a, cue) => cues.push(cue),
    };
    const a = scratchOf(createRomActor());
    configureDeathBorgBetaFamily(a, "pl010a", sctx);
    assert(a.borgNumber === 0x10a, "BETA III pl010a borgNumber stamped 0x10a");
    a.actionIndex = 2; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    a.contactP1 = 1;
    a.rootAction!(a); // ph1 dive -> hardpoint spawn
    assert(shots.length === 2, `BETA III 0x10a spawns 2 hardpoints (got ${shots.length})`);
    assert(shots.every((sp) => sp.addr === BETA_HARDPOINT_SPAWNER_E0E90),
      "BETA III hardpoints route zz_00e0e90_");
    assert(shots[0]!.type === 4 && shots[1]!.type === 5, "BETA III hardpoint types 4, 5");
    assert(cues.length === 1 && cues[0] === 0xdb, "BETA III plays cue 0xdb (zz_00f036c_)");
    // Re-fire should be suppressed (attachment flags already set).
    shots.length = 0; cues.length = 0;
    a.fbPhaseSlots[0] = 1; // back to ph1
    a.contactP1 = 1;
    a.rootAction!(a);
    assert(shots.length === 0, "BETA III suppresses re-spawn (attachment flags set)");
  }

  // --- DEATH BORG BETA II action 0: contact-fire zz_0082824_(0x38). ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActor());
    configureDeathBorgBetaFamily(a, "pl0105", sctx);
    a.actionIndex = 0; a.dt = 1;
    a.rootAction!(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "BETA act0 setup +0x540 = 1");
    a.contactP0 = 1; // +0x1cef > 0
    a.rootAction!(a); // contact fire
    assert(shots.length === 1 && shots[0]!.addr === BETA_SHOT_HELPER && shots[0]!.type === 0x38,
      `BETA act0 contact -> zz_0082824_(0x38) (got ${JSON.stringify(shots)})`);
  }
}

// ----------------------------------------------------------------------------
// Named const exports for spawner addresses + floats (audit surface).
// ----------------------------------------------------------------------------
export const WING_BLOB_CONSTANTS = {
  ANUBIS_F, XSPEC_F, SHARED_SPAWN_F, DEMON_F, SIGMA_F, BETA_F,
} as const;
