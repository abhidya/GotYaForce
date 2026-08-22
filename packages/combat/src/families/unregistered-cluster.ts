// Unregistered borg cluster — the last eight unregistered borgs, ROM-faithful 1:1 ports.
//
//   DEATH BORG ALPHA   pl0008 (0x008) ctor 0x8019e9a4 chunk_0049.c — hero dash/blast
//      (a0 @0x80376470/47c/488/494 four variants + a1 @0x803764cc/e4 two variants).
//      root zz_019edbc_ → PTR_zz_019edf8__8037643c[+0x580] → variant walkers.
//   DEATH BORG BETA    pl0109 (0x109) ctor 0x801d8730 chunk_0057.c+chunk_0055.c — hero
//      melee (a1 @0x8038e140/e150) + shared charge-flurry/recovery (@0x8038a6d8/e8).
//   DEATH BORG TAU     pl0807 (0x807) ctor 0x801a04f0 chunk_0049.c — hero melee
//      (a0 @0x80377880 ground + a1 @0x803778ac air).
//   METAL HERO         pl080a (0x80a) ctor 0x801bfe64 chunk_0054.c+chunk_0055.c — dash
//      (a0 @0x80435a54) + air dive (a2 @0x80383b60) + shared charge (a1).
//   POP HONEY          pl0904 (0x904) ctor 0x8012c498 chunk_0034.c — dash/blast
//      (a0 @0x803335f0) + melee (a1 @0x8033361c/634/648/658) + air (a2 @0x80333668/678).
//   JET HERO           pl0a01 (0xa01) ctor 0x80100ef4 chunk_0028.c+chunk_0038.c — flying
//      volley (a0 @0x80320528) + melee (a1 @0x8032054c/55c).
//   CARRIER HELICOPTER pl0d02 (0xd02) ctor 0x80135ee8 chunk_0035.c — vehicle volley
//      (a0 @0x80338c44) + dual spawn (a1 @0x80338c54) + deploy (a2 @0x80338c64).
//   FLYING SAUCER      pl0d03 (0xd03) ctor 0x80188ff4 chunk_0046.c — vehicle volley
//      (a0 @0x8036299c) + deploy (a2 @0x803629ac).
//
// Phase-table lengths confirmed by next-table − this-table address arithmetic
// (work-queue overreads). Phase transitions, spawns, ammo gates, exits faithful;
// renderer/physics clamps/aim solvers (gnt4_PSMTX*, zz_006e6c4_, zz_006ec1c_,
// zz_006eddc_, descriptor bone rows +0x8e0/8f0/900) marked TODO(host).
// Floats read from user-data/GG4E/disc/sys/boot.dol this session (cited per const).

import { createRomActor, type RomActor, type Vec3 } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  allocateWeapon,
  groundSnapRevert,
  stepPartTargetPitch,
  stepTargetPitch,
  stepTargetRoll,
  stepTargetYaw,
  toS16,
} from "../rom/helpers.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirIdleReturn, romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

const UNREG_BORG_NUMBERS: Record<string, number> = {
  pl0008: 0x008, pl0109: 0x109, pl0807: 0x807, pl080a: 0x80a,
  pl0904: 0x904, pl0a01: 0xa01, pl0d02: 0xd02, pl0d03: 0xd03,
};
export type UnregBorgId = keyof typeof UNREG_BORG_NUMBERS;

// ---- Shared spawner addresses (named const exports). ----
/** zz_0082824_ @0x80082824 — record-table projectile spawn. */
export const UNREG_SHOT_HELPER = 0x80082824;
/** zz_00c3be0_ @0x800c3be0 — per-borg effect spawn. */
export const UNREG_EFFECT_SPAWNER_C3BE0 = 0x800c3be0;
/** zz_016cc24_ @0x8016cc24 — effect-child spawn. */
export const UNREG_EFFECT_CHILD_SPAWNER = 0x8016cc24;
/** zz_0066530_ — family shot spawn (ALPHA/TAU melee hit). */
export const UNREG_MELEE_SHOT_SPAWNER = 0x80066530;
/** zz_01deb68_ @0x801deb68 — deploy arm (FLYING SAUCER). */
export const UNREG_DEPLOY_ARM = 0x801deb68;
/** zz_01043ac_ — CARRIER HELICOPTER dual-port spawn. */
export const UNREG_CARRIER_DUAL_SPAWNER = 0x801043ac;

// ---- Per-family float constants (DOL-read; cited per const). ----
export const DEATH_BORG_ALPHA = {
  STREAM_RATE: -1.0, // FLOAT_8043b4cc
  ZERO: 0.0, // FLOAT_8043b4d0
  PHYSICS_GRAVITY: 1.0, // FLOAT_8043b4d4
  MAIN_TIMER: 7.0, // FLOAT_8043b4d8 — zz_019f820_ +0x558 seed
  ACTIVE_TIMER: 30.0, // FLOAT_8043b4dc — windup/spawn re-seed
  A1_PH0_TIMER: 60.0, // FLOAT_8043b4e0 — a1 v0 ph0 +0x558
  A1_MOTION: 0.98, // FLOAT_8043b4e4
  A1_YVEL: 33.33333206176758, // FLOAT_8043b4ec
  A1_ACTIVE_THRESH: 2.0, // FLOAT_8043b4f8
  A1_SLOW_GATE: 200.0, // FLOAT_8043b4fc
  A1_ACTIVE_TIMER: 120.0, // FLOAT_8043b500
  A1_ACTIVE2_YVEL: -30.0, // FLOAT_8043b510
  A1_RANGE: 150.0, // FLOAT_8043b514 — FUN_80066838
  A1_DRAG: 0.949999988079071, // FLOAT_8043b518 — zz_006ed8c_
  A1_ACTIVE2_TIMER: 10.0, // FLOAT_8043b51c
  A1_V1_AIM_THRESH: -8192.0, // FLOAT_8043b520 — FUN_800667a0
  A1_V1_PH0_TIMER: 20.0, // FLOAT_8043b524
  A1_V1_RANGE: 250.0, // FLOAT_8043b530 — FUN_800668cc
  A1_V1_DIVISOR: 12.0, // FLOAT_8043b534
  EXIT_STATE_BASE: 1.0, // FLOAT_8043b4d4 — zz_006a750_(7) +0x694 base
  ACTION_MODE_BITS: 0x3,
} as const;

export const DEATH_BORG_BETA = {
  ZERO: 0.0, // FLOAT_8043bf38
  PH0_TIMER: 60.0, // FLOAT_8043bf3c
  MOTION: 0.949999988079071, // FLOAT_8043bf40
  STREAM_RATE: -1.0, // FLOAT_8043bf44
  WINDUP_TIMER: 20.0, // FLOAT_8043bf48
  SPEED: 30.0, // FLOAT_8043bf4c
  PHYSICS_GRAVITY: 1.0, // FLOAT_8043bf50
  RANGE: 150.0, // FLOAT_8043bf54 — FUN_800668cc
  V1_WINDUP_TIMER: 120.0, // FLOAT_8043bf58
  V1_DRAG: 0.8999999761581421, // FLOAT_8043bf5c
} as const;

export const DEATH_BORG_TAU = {
  PH0_TIMER: 60.0, // FLOAT_8043b540
  MOTION: 0.949999988079071, // FLOAT_8043b544
  STREAM_RATE: -1.0, // FLOAT_8043b548
  ZERO: 0.0, // FLOAT_8043b54c
  WINDUP_TIMER: 20.0, // FLOAT_8043b550
  ACTIVE_DAMP: 0.25, // FLOAT_8043b564
  ACTIVE2_YVEL: -3.0, // FLOAT_8043b568
  PHYSICS_GRAVITY: 1.0, // FLOAT_8043b56c
  RANGE: 400.0, // FLOAT_8043b570 — FUN_800668cc
  ACTIVE2_TIMER: 16.0, // FLOAT_8043b574
  RECOVER_DRAG: 0.5, // FLOAT_8043b578 — zz_006ed8c_
  RECOVER_TIMER: 10.0, // FLOAT_8043b57c
  RECOVER_YVEL: -0.30000001192092896, // FLOAT_8043b580
  RECOVER_DECAY: 0.9900000095367432, // FLOAT_8043b584
  ACTION_MODE_BITS: 0x3,
} as const;

export const METAL_HERO = {
  ZERO: 0.0, // FLOAT_8043bb38
  MOTION: 0.8999999761581421, // FLOAT_8043bb44
  A0_BLINK_GATE: 20.0, // FLOAT_8043bb48
  STREAM_RATE: -1.0, // FLOAT_8043bb4c
  EXIT_STATE_BASE: 16.0, // FLOAT_8043bb50 — +0x694 seed
  A0_AFTERIMAGE: 3.0, // FLOAT_8043bb54
  A2_PH0_TIMER: 10.0, // FLOAT_8043bb5c
  A2_MOTION: 0.949999988079071, // FLOAT_8043bb68
  A2_ACTIVE_TIMER: 120.0, // FLOAT_8043bb78
  ACTION_MODE_BITS: 0x3,
} as const;

export const POP_HONEY = {
  ZERO: 0.0, // FLOAT_80439da8
  P2_ACCEL_HI: 12.0, // FLOAT_80439dac
  P2_ACCEL_STEP: 15.0, // FLOAT_80439db0
  P2_ACCEL_LO: 8.0, // FLOAT_80439db4
  MAIN_TIMER: 60.0, // FLOAT_80439db8
  STREAM_RATE: -1.0, // FLOAT_80439dbc
  A0_STEER_DECAY: 0.800000011920929, // FLOAT_80439dc0
  A0_COOLDOWN_DRAG: 0.8999999761581421, // FLOAT_80439dd0
  A0_GROUND_SCALE: 0.9800000190734863, // FLOAT_80439dd4
  PHYSICS_GRAVITY: 1.0, // FLOAT_80439dd8
  A1_WINDUP_TIMER: 30.0, // FLOAT_80439ddc
  ACTION_MODE_BITS: 0x3,
} as const;

export const JET_HERO = {
  ACTIVE_DRAG: 0.8999999761581421, // FLOAT_80439338 — zz_006eddc_
  ZERO: 0.0, // FLOAT_80439348
  STREAM_RATE: -1.0, // FLOAT_8043934c
  PHYSICS_GRAVITY: 1.0, // FLOAT_80439354
  MAIN_TIMER: 30.0, // FLOAT_80439358
  A1_PH0_TIMER: 60.0, // FLOAT_8043935c
  MOTION: 0.949999988079071, // FLOAT_80439360
  A1_GRAV_PROJ: 2.0, // FLOAT_80439364
  A1_SPEED: 40.0, // FLOAT_8043936c
  A1_RECOVER_DRAG: 0.9800000190734863, // FLOAT_80439370
  A1_BODY_SCALE: 1000.0, // FLOAT_80439374
  A1_YVEL: 33.33333206176758, // FLOAT_80439378
  A1_SLOW_GATE: 200.0, // FLOAT_80439388
  A1_RANGE: 50.0, // FLOAT_8043938c — FUN_80066838
  A1_EXIT_YVEL: -30.0, // FLOAT_80439390
  ACTION_MODE_BITS: 0x3,
} as const;

export const CARRIER = {
  AIM_MISS_SCALE: 0.8999999761581421, // FLOAT_80439f90
  PHYSICS_GRAVITY: 1.0, // FLOAT_80439f98 — zz_0067458_
  ZERO: 0.0, // FLOAT_80439fa8
  AIM_BLEND_A: 4.0, // FLOAT_80439fac
  AIM_BLEND_B: 0.6000000238418579, // FLOAT_80439fb0
  AIM_BLEND_DIV: 5.0, // FLOAT_80439fb4
  STREAM_RATE: 0.2, // FLOAT_80439fbc — FUN_8006cc90
  A1_PH0_TIMER: 20.0, // FLOAT_80439fc0
  SHOT_INTERVAL: 4, // +0x54a
  BURST_SHOT_CAP: 0x13, // +0x54c burst advance threshold
  BURST_BIT_5B4: 0x200, // +0x5b4 burst status bit
  COOLDOWN_COUNT: 0x1e, // +0x548 cooldown countdown seed
  DEPLOY_COUNT: 0xf, // +0x548 deploy countdown seed
  DEPLOY_CANCEL: 10, // zz_006a53c_(10) cancel param
} as const;

export const FLYING_SAUCER = {
  ZERO: 0.0, // FLOAT_8043afbc
  STREAM_RATE: 0.2, // FLOAT_8043afc4 — FUN_8006cc90
  SPAWN_EXIT_TIMER: 40.0, // FLOAT_8043afc8 — a0 spawn-exit +0x558
  DEPLOY_TIMER: 32.0, // FLOAT_8043afcc — a2 ph0 +0x558
  BURST_BIT_5BC: 0x200, // +0x5bc burst status bit
  SHOT_INTERVAL: 10, // +0x154
  BURST_SHOT_CAP: 4, // +0x156 burst advance threshold
  EXIT_CUE: 0x1b, // zz_006a53c_ full-body cue
  DEPLOY_PARAM: 0x1e, // zz_006a53c_(0x1e) deploy param
} as const;

// ---- Scratch mirrors for ROM offsets not first-class on RomActor. ----
export interface UnregScratch {
  unregCursor148?: number;
  unregLatch14a?: number;
  unregShotCd14c?: number;
  unregToggle14e?: number;
  unregToggle151?: number;
  unregBurst152?: number;
  unregShotCd154?: number;
  unregShotCount156?: number;
  unregFlag541?: number;
  unregFlag544?: number;
  unregFlag545?: number;
  unregCountdown548?: number;
  unregYaw54a?: number;
  unregCountdown54c?: number;
  unregSeed54e?: number;
  unregCooldown55c?: number;
  unregTimer560?: number;
  unregFlag6e9?: number;
  unregSlot6ea?: number;
  unregCounter6eb?: number;
  unregSlot6ee?: number;
  unregShots6ef?: number;
  unregFlag6f5?: number;
  unregMode6f7?: number;
  unregScalar760?: number;
  unregScalar764?: number;
  flag71c?: number;
  hit1d9?: number;
  statusWord5bc?: number;
  /** +0x5e8 lock target (aimed-shot machines). */
  lockTarget?: { x: number; y: number; z: number } | null;
}
type UA = RomActor & UnregScratch;

function scratchOf(actor: RomActor): UA {
  return actor as UA;
}

export interface UnregFamilyCtx extends StreamContext {
  /** FUN_80066838(range, actor) range gate. Default: no-target → -1. */
  onRangeCheck?: (actor: RomActor, range: number) => number;
  /** FUN_800668cc(range, actor) range gate (active variant). Default: -1. */
  onRangeCheckCc?: (actor: RomActor, range: number) => number;
}

// ---- Shared helpers (1:1 with ROM contracts). ----
/** zz_006a53c_(actor, param) — clear +0x73f, strip +0x5e0 action bits, dispatch
 *  full-body cue 0x1b, seed +0x694=param+dt when param>0. (chunk_0009.c:750) */
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) actor.stateTimer = param + actor.dt;
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, 0x1b);
}
/** zz_006a668_(actor, 0x10) — shot-channel clear + dispatch current upper cue. */
function shotClearAndCue(actor: RomActor): void {
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  dispatchFullBodyCue(actor, actor.ubCue);
  actor.controlWord = actor.controlWord & ~0x3;
}
/** zz_006a3d0_(actor, cmd, stateMode, variant) — command-record re-dispatch. */
function redispatchAction(actor: RomActor, stateMode: number, variant: number): void {
  actor.controlWord = (actor.controlWord & ~0x3) | (stateMode & 0x3);
  actor.variantIndex = variant;
  dispatchFullBodyCue(actor, 44);
}
function applyDrag(actor: RomActor, scale: number): void {
  actor.hSpeed *= scale;
  actor.yVel *= scale;
}
function physicsMove(actor: RomActor, yaw: number): void {
  integratePhysics(0, actor, yaw);
}
function groundStep(actor: RomActor): number {
  return groundSnapRevert(actor) ? 1 : 0;
}
function applyBlink(actor: RomActor, scale: number): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}
function applyMotionDrift(actor: RomActor, scale: number): void {
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}
function hasLock(actor: RomActor): boolean {
  return (actor as RomActor & { lockTarget?: Vec3 | null }).lockTarget != null;
}
function rangeCheck(actor: RomActor, range: number, ctx: UnregFamilyCtx, cc = false): number {
  const hook = cc ? ctx.onRangeCheckCc : ctx.onRangeCheck;
  if (hook) return hook(actor, range);
  return hasLock(actor) ? 0 : -1;
}
function speedRow(actor: RomActor): number {
  const idx = (((actor.prevActionIndex ?? 0) % 3) + 3) % 3;
  return actor.actionSpeedRows[idx] ?? 0;
}
/** FUN_8006cc90 host bridge — no stream banks → no-op returning 0. */
function tickUnregStream(): number {
  return 0;
}

// ============================================================================
// DEATH BORG ALPHA (pl0008) — hero dash/blast (a0, 4 variants) + melee (a1).
// ============================================================================
function alphaLoadTimers(a: UA): void {
  if ((a.unregSlot6ee ?? 0) === 0) a.unregShots6ef = 5;
  a.unregSlot6ee = 0;
  a.handlerTimer = DEATH_BORG_ALPHA.MAIN_TIMER;
  a.unregTimer560 = DEATH_BORG_ALPHA.ACTIVE_TIMER;
}
function alphaSpawnShot(a: UA, ctx: StreamContext): void {
  a.unregSlot6ee = 1;
  a.unregShots6ef = (a.unregShots6ef ?? 0) - 1;
  allocateWeapon(a, ctx, 0, 1, true); // zz_006dbe0_(0,1,1)
}
function alphaA0V0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    startStream(a, 1, 2, a.unregSlot6ee ?? 0, DEATH_BORG_ALPHA.STREAM_RATE);
    startStream(a, 2, 2, 9, DEATH_BORG_ALPHA.STREAM_RATE);
    a.controlWord = a.controlWord & 0xffffff4f;
    alphaLoadTimers(a);
    a.hDecel = DEATH_BORG_ALPHA.ZERO; a.hSpeed = DEATH_BORG_ALPHA.ZERO;
    return;
  }
  if (ph === 1) {
    if (a.contactP0 === 0) tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc1, 0, true);
    a.unregTimer560 = (a.unregTimer560 ?? 0) - a.dt;
    if (DEATH_BORG_ALPHA.ZERO < (a.unregTimer560 ?? 0)) return;
    if (a.contactP0 !== 0) { a.fbPhaseSlots[0] = ph + 1; alphaSpawnShot(a, ctx); }
    return;
  }
  if (ph === 2) {
    tickStream(a, 0xf, ctx);
    if ((a.statusWord5b4 & 0x200) === 0) {
      if ((a.inputHeld5d8 & 0xf0) === 0 && (a.inputEdge5d4 & 1) === 0 && a.wallContact === 0) return;
    } else if (allocateWeapon(a, ctx, 0, 1, false) && (a.unregShots6ef ?? 0) > 0) {
      if ((a.controlWord & 0x40) !== 0) { redispatchAction(a, 3, 0); return; }
      a.fbPhaseSlots[0] = ph - 1;
      startStream(a, 1, 2, 1, DEATH_BORG_ALPHA.STREAM_RATE);
      return;
    }
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
    romGroundIdleReturn(a);
  }
}
function alphaA0V1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    startStream(a, 1, 2, ((a.unregSlot6ee ?? 0) + 6) | 0, DEATH_BORG_ALPHA.STREAM_RATE);
    alphaLoadTimers(a);
    return;
  }
  if (ph === 1) {
    const aim = stepTargetRoll(a, true);
    tickStream(a, 1, ctx);
    a.unregTimer560 = (a.unregTimer560 ?? 0) - a.dt;
    if (aim < 0) { redispatchAction(a, 0, 2); return; }
    if (aim < 1 && DEATH_BORG_ALPHA.ZERO < (a.unregTimer560 ?? 0)) return;
    if (a.contactP0 !== 0) { a.fbPhaseSlots[0] = ph + 1; alphaSpawnShot(a, ctx); }
    return;
  }
  if (ph === 2) {
    tickStream(a, 1, ctx);
    if ((a.statusWord5b4 & 0x200) !== 0) {
      if (allocateWeapon(a, ctx, 0, 1, false) && (a.unregShots6ef ?? 0) > 0) {
        if ((a.controlWord & 0x40) === 0 && a.fbCue !== 4) {
          if ((a.controlWord & 0x10) !== 0) {
            a.fbPhaseSlots[0] = ph - 1;
            startStream(a, 1, 2, 7, DEATH_BORG_ALPHA.STREAM_RATE);
            return;
          }
          redispatchAction(a, 0, 2); return;
        }
        redispatchAction(a, 3, 2); return;
      }
    } else if ((a.inputHeld5d8 & 0xf0) !== 0 || a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
      shotClearAndCue(a);
    }
  }
}
function alphaA0V2(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    startStream(a, 1, 2, ((a.unregSlot6ee ?? 0) + 6) | 0, DEATH_BORG_ALPHA.STREAM_RATE);
    if ((a.controlWord & 0x80) !== 0) {
      romAirKnockoutReturn(a);
      startStream(a, 2, 0, 0xd, DEATH_BORG_ALPHA.STREAM_RATE);
    }
    alphaLoadTimers(a);
    return;
  }
  if (ph === 1) {
    stepTargetYaw(a, 0x81, 0, true);
    tickStream(a, 1, ctx);
    a.unregTimer560 = (a.unregTimer560 ?? 0) - a.dt;
    if (DEATH_BORG_ALPHA.ZERO < (a.unregTimer560 ?? 0)) return;
    if (a.contactP0 !== 0) { a.fbPhaseSlots[0] = ph + 1; alphaSpawnShot(a, ctx); }
    return;
  }
  if (ph === 2) {
    tickStream(a, 1, ctx);
    if ((a.statusWord5b4 & 0x200) !== 0) {
      if (allocateWeapon(a, ctx, 0, 1, false) && (a.unregShots6ef ?? 0) > 0) {
        if ((a.controlWord & 0x40) === 0) { redispatchAction(a, 0, 2); return; }
        a.fbPhaseSlots[0] = ph - 1;
        startStream(a, 1, 2, 7, DEATH_BORG_ALPHA.STREAM_RATE);
        return;
      }
    } else if ((a.inputHeld5d8 & 0xf0) === 0 && a.wallContact === 0) return;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
    shotClearAndCue(a);
  }
}
function alphaA0V3(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    stepTargetYaw(a, 0x81, 0, true);
    a.controlWord = a.controlWord & 0xffffff7f;
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    startStream(a, 1, 2, ((a.unregSlot6ee ?? 0) + 6) | 0, DEATH_BORG_ALPHA.STREAM_RATE);
    alphaLoadTimers(a);
    a.accumulator80c = DEATH_BORG_ALPHA.ZERO;
    return;
  }
  if (ph === 1) {
    stepTargetYaw(a, 0x81, 0, true);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    tickStream(a, 0xf, ctx);
    if (a.contactP0 !== 0) {
      a.fbPhaseSlots[0] = ph + 1;
      alphaSpawnShot(a, ctx);
      a.controlWord = a.controlWord & ~0x2;
      romAirKnockoutReturn(a);
    }
    return;
  }
  if (ph === 2) {
    tickStream(a, 1, ctx);
    if ((a.statusWord5b4 & 0x200) !== 0) {
      if (allocateWeapon(a, ctx, 0, 1, false) && (a.unregShots6ef ?? 0) > 0) {
        if ((a.controlWord & 0x40) === 0) { redispatchAction(a, 0, 2); return; }
        a.fbPhaseSlots[0] = ph - 1; a.variantIndex = 3;
        startStream(a, 1, 2, 7, DEATH_BORG_ALPHA.STREAM_RATE);
        return;
      }
    } else if ((a.inputHeld5d8 & 0xf0) === 0 && a.wallContact === 0) return;
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
    shotClearAndCue(a);
  }
}
function alphaA1V0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = DEATH_BORG_ALPHA.A1_PH0_TIMER;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.lockYaw = a.heading; a.activeYaw = a.heading;
    }
    a.gravityCoeff = DEATH_BORG_ALPHA.ZERO; a.yVel = DEATH_BORG_ALPHA.ZERO;
    a.hDecel = DEATH_BORG_ALPHA.ZERO; a.hSpeed = DEATH_BORG_ALPHA.ZERO;
    a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
    applyBlink(a, 1);
    return;
  }
  if (ph === 1) {
    applyMotionDrift(a, DEATH_BORG_ALPHA.A1_MOTION);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_ALPHA.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_ALPHA.ACTIVE_TIMER;
      a.yVel = DEATH_BORG_ALPHA.A1_YVEL; a.hDecel = DEATH_BORG_ALPHA.ZERO;
      startStream(a, 0xf, 3, 5, DEATH_BORG_ALPHA.STREAM_RATE);
    }
    return;
  }
  if (ph === 2) {
    tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    if (a.yVel < DEATH_BORG_ALPHA.A1_ACTIVE_THRESH) {
      a.fbPhaseSlots[0] = ph + 1;
      startStream(a, 0xf, 3, 6, DEATH_BORG_ALPHA.STREAM_RATE);
    }
    return;
  }
  if (ph === 3) {
    tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    if (a.contactP0 > 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_ALPHA.A1_ACTIVE_TIMER;
      a.hSpeed = 0; a.yVel = DEATH_BORG_ALPHA.A1_ACTIVE2_YVEL;
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
    }
    return;
  }
  if (ph === 4) {
    tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    if (rangeCheck(a, DEATH_BORG_ALPHA.A1_RANGE, ctx) > 0) {
      a.hDecel = DEATH_BORG_ALPHA.ZERO; a.hSpeed = DEATH_BORG_ALPHA.ZERO;
    }
    applyDrag(a, DEATH_BORG_ALPHA.A1_DRAG);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.lockYaw);
    if (DEATH_BORG_ALPHA.ZERO < a.handlerTimer) {
      a.handlerTimer -= a.dt;
      if (groundStep(a) !== 0) {
        a.fbPhaseSlots[0] = ph + 1;
        a.handlerTimer = DEATH_BORG_ALPHA.A1_ACTIVE2_TIMER;
        ctx.onFamilyProjectile?.(a, UNREG_MELEE_SHOT_SPAWNER, 0x2c); // zz_0066530_(0x2c)
        startStream(a, 0xf, 3, 7, DEATH_BORG_ALPHA.STREAM_RATE);
      }
    } else {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
    return;
  }
  if (ph === 5) {
    if (a.handlerTimer <= DEATH_BORG_ALPHA.ZERO) tickStream(a, 0xf, ctx);
    else a.handlerTimer -= a.dt;
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
      romGroundIdleReturn(a);
    }
  }
}
function alphaA1V1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.lockYaw = a.heading; a.activeYaw = a.heading;
    }
    a.fbPhaseSlots[0] = 1;
    a.gravityCoeff = DEATH_BORG_ALPHA.ZERO; a.yVel = DEATH_BORG_ALPHA.ZERO;
    a.hDecel = DEATH_BORG_ALPHA.ZERO; a.hSpeed = DEATH_BORG_ALPHA.ZERO;
    a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
    a.handlerTimer = DEATH_BORG_ALPHA.A1_V1_PH0_TIMER;
    a.unregSeed54e = 0;
    startStream(a, 0xf, 3, 8, DEATH_BORG_ALPHA.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    stepTargetYaw(a, 0xc0);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.activeYaw);
    groundStep(a);
    if (a.contactP0 === 0) tickStream(a, 0xf, ctx);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_ALPHA.ZERO || rangeCheck(a, DEATH_BORG_ALPHA.A1_V1_RANGE, ctx, true) > 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_ALPHA.A1_ACTIVE2_TIMER;
      a.hSpeed = (a.hSpeed ?? 0) / DEATH_BORG_ALPHA.A1_V1_DIVISOR;
      a.yVel = (a.yVel ?? 0) / DEATH_BORG_ALPHA.A1_V1_DIVISOR;
    }
    return;
  }
  if (ph === 2) {
    stepTargetYaw(a, 0xc0);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.activeYaw);
    groundStep(a);
    if (a.contactP0 === 0) tickStream(a, 0xf, ctx);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_ALPHA.ZERO) {
      a.fbPhaseSlots[0] = ph + 1;
      const yaw = a.unregSeed54e ?? 0;
      a.hSpeed = DEATH_BORG_ALPHA.ACTIVE_TIMER * projectZ(yaw);
      a.yVel = DEATH_BORG_ALPHA.ACTIVE_TIMER * -projectX(yaw);
    }
    return;
  }
  if (ph === 3) {
    tickStream(a, 0xf, ctx);
    if (a.faceGate1d10 !== 0) stepTargetYaw(a, 0xc0);
    if (a.dashStrength1d0f < 0) {
      a.dashStrength1d0f = 0;
      if (DEATH_BORG_ALPHA.ZERO < a.yVel) a.yVel = DEATH_BORG_ALPHA.ZERO;
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
    }
    applyDrag(a, DEATH_BORG_ALPHA.A1_DRAG);
    integratePhysics(DEATH_BORG_ALPHA.PHYSICS_GRAVITY, a, a.activeYaw);
    const grounded = groundStep(a);
    if (grounded !== 0 && a.contactP0 < 0) {
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
      dispatchUpperBodyCue(a, 7);
      a.stateTimer = DEATH_BORG_ALPHA.EXIT_STATE_BASE + a.dt;
      return;
    }
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_ALPHA.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
      a.stateTimer = DEATH_BORG_ALPHA.EXIT_STATE_BASE + a.dt;
    }
  }
}
function createAlphaRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.actionIndex === 0) {
      switch (a.variantIndex) {
        case 0: alphaA0V0(a, ctx); return;
        case 1: alphaA0V1(a, ctx); return;
        case 2: alphaA0V2(a, ctx); return;
        case 3: alphaA0V3(a, ctx); return;
        default: return;
      }
    } else if (a.actionIndex === 1) {
      if (a.variantIndex === 1) alphaA1V1(a, ctx); else alphaA1V0(a, ctx);
    }
  };
}
export function configureDeathBorgAlphaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0008 ?? 0x008;
  actor.rootAction = createAlphaRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEATH BORG TAU (pl0807) — hero melee (a0 ground @0x80377880, a1 air @0x803778ac).
// ============================================================================
function tauGround(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.activeYaw = a.lockYaw;
    }
    a.handlerTimer = DEATH_BORG_TAU.PH0_TIMER;
    a.unregSlot6ea = 2;
    stepTargetYaw(a, 0xc0);
    applyBlink(a, DEATH_BORG_TAU.MOTION);
    groundStep(a);
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 3, slot, DEATH_BORG_TAU.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    if (a.contactP0 === 0 || a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    applyMotionDrift(a, DEATH_BORG_TAU.MOTION);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_TAU.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_TAU.WINDUP_TIMER;
      a.hDecel = DEATH_BORG_TAU.ZERO;
      a.accumulator80c = DEATH_BORG_TAU.ZERO;
      a.hSpeed = speedRow(a) / DEATH_BORG_TAU.WINDUP_TIMER;
    }
    return;
  }
  if (ph === 2) {
    if (a.contactP0 === 0 || a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    applyDrag(a, DEATH_BORG_TAU.MOTION);
    physicsMove(a, a.lockYaw);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_TAU.ZERO || rangeCheck(a, DEATH_BORG_TAU.RANGE, ctx, true) !== 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.hSpeed *= DEATH_BORG_TAU.ACTIVE_DAMP;
    }
    return;
  }
  if (ph === 3) {
    if ((a.flag71c ?? 0) === 0) {
      tickStream(a, 0xf, ctx);
      applyDrag(a, DEATH_BORG_TAU.MOTION);
      physicsMove(a, a.lockYaw);
      if (a.contactP1 !== 0) {
        a.fbPhaseSlots[0] = ph + 1;
        a.hSpeed = DEATH_BORG_TAU.ZERO; a.hDecel = DEATH_BORG_TAU.ZERO;
        a.yVel = DEATH_BORG_TAU.PH0_TIMER;
        a.gravityCoeff = DEATH_BORG_TAU.ACTIVE2_YVEL;
        ctx.onFamilyProjectile?.(a, UNREG_MELEE_SHOT_SPAWNER, 0x2d); // zz_0066530_(0x2d)
      }
    }
    return;
  }
  if (ph === 4) {
    tickStream(a, 0xf, ctx);
    integratePhysics(DEATH_BORG_TAU.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_TAU.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
  }
}
function tauAir(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = DEATH_BORG_TAU.PH0_TIMER;
    a.unregSlot6ea = 4;
    if (rangeCheck(a, speedRow(a), ctx, true) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.activeYaw = a.heading;
    }
    stepTargetYaw(a, 0xc0);
    stepPartTargetPitch(a, 0xc0);
    applyBlink(a, DEATH_BORG_TAU.MOTION);
    groundStep(a);
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 3, slot, DEATH_BORG_TAU.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    applyMotionDrift(a, DEATH_BORG_TAU.MOTION);
    groundStep(a);
    if (a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    stepPartTargetPitch(a, 0xc0);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_TAU.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_TAU.WINDUP_TIMER;
    }
    return;
  }
  if (ph === 2) {
    tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    stepPartTargetPitch(a, 0xc0);
    a.hSpeed = DEATH_BORG_TAU.PH0_TIMER * projectZ(a.steerYaw);
    a.yVel = DEATH_BORG_TAU.PH0_TIMER * -projectX(a.steerYaw);
    integratePhysics(DEATH_BORG_TAU.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_TAU.ZERO || rangeCheck(a, DEATH_BORG_TAU.RANGE, ctx, true) > 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_TAU.ACTIVE2_TIMER;
      const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
      startStream(a, 0xf, 3, slot, DEATH_BORG_TAU.STREAM_RATE);
    }
    return;
  }
  if (ph === 3) {
    if (a.contactP0 === 0) tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    stepPartTargetPitch(a, 0xc0);
    applyDrag(a, DEATH_BORG_TAU.RECOVER_DRAG);
    integratePhysics(DEATH_BORG_TAU.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_TAU.ZERO) {
      a.fbPhaseSlots[0] = ph + 1;
      a.hSpeed = DEATH_BORG_TAU.PH0_TIMER * projectZ(a.steerYaw);
      a.yVel = DEATH_BORG_TAU.PH0_TIMER * -projectX(a.steerYaw);
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
    }
    return;
  }
  if (ph === 4) {
    tickStream(a, 0xf, ctx);
    if (((a.hit1d9 ?? 0) & 0x30) !== 0) {
      a.hSpeed = DEATH_BORG_TAU.ZERO; a.hDecel = DEATH_BORG_TAU.ZERO;
      a.yVel = DEATH_BORG_TAU.RECOVER_TIMER;
      a.gravityCoeff = DEATH_BORG_TAU.RECOVER_YVEL;
      a.lockYaw = toS16(a.lockYaw - 0x8000);
    }
    applyDrag(a, DEATH_BORG_TAU.RECOVER_DECAY);
    integratePhysics(DEATH_BORG_TAU.PHYSICS_GRAVITY, a, a.lockYaw);
    const grounded = groundStep(a);
    if (grounded !== 0 && a.contactP0 < 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_TAU.ACTION_MODE_BITS;
      dispatchUpperBodyCue(a, 7);
      a.stateTimer = DEATH_BORG_TAU.PHYSICS_GRAVITY + a.dt;
      return;
    }
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~DEATH_BORG_TAU.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
  }
}
function createTauRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.variantIndex === 1) {
      if (a.actionIndex === 1) tauAir(a, ctx); else tauGround(a, ctx);
    }
  };
}
export function configureDeathBorgTauFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0807 ?? 0x807;
  actor.rootAction = createTauRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DEATH BORG BETA (pl0109) — hero melee (a1 v0 @0x8038e140, v1 @0x8038e150).
// ============================================================================
function betaV0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    if (!hasLock(a)) a.activeYaw = a.heading;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.lockYaw = a.heading; a.activeYaw = a.heading;
    }
    a.handlerTimer = DEATH_BORG_BETA.PH0_TIMER;
    a.unregSeed54e = 0; a.unregSlot6ea = 7; a.unregCounter6eb = 0;
    a.gravityCoeff = DEATH_BORG_BETA.ZERO; a.yVel = DEATH_BORG_BETA.ZERO;
    a.hDecel = DEATH_BORG_BETA.ZERO; a.hSpeed = DEATH_BORG_BETA.ZERO;
    a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
    stepTargetYaw(a, 0xc0);
    stepTargetPitch(a, 0xc0, a.unregSeed54e ?? 0);
    applyBlink(a, DEATH_BORG_BETA.MOTION);
    groundStep(a);
    startStream(a, 0xf, 3, a.unregSlot6ea ?? 0, DEATH_BORG_BETA.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    if (a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    applyMotionDrift(a, DEATH_BORG_BETA.MOTION);
    groundStep(a);
    stepTargetPitch(a, 0xc0, a.unregSeed54e ?? 0);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_BETA.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_BETA.WINDUP_TIMER;
    }
    return;
  }
  if (ph === 2) {
    if (a.contactP0 === 0) tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    stepTargetPitch(a, 0xc0, a.unregSeed54e ?? 0);
    a.hSpeed = DEATH_BORG_BETA.SPEED * projectZ(a.unregSeed54e ?? 0);
    a.yVel = DEATH_BORG_BETA.SPEED * -projectX(a.unregSeed54e ?? 0);
    integratePhysics(DEATH_BORG_BETA.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_BETA.ZERO || rangeCheck(a, DEATH_BORG_BETA.RANGE, ctx, true) > 0) {
      a.fbPhaseSlots[0] = ph + 1;
    }
    return;
  }
  if (ph === 3) {
    if ((a.inputEdge5d4 & 0x40) !== 0) a.unregLatch14a = 1;
    if (a.faceGate1d10 !== 0) {
      stepTargetYaw(a, 0xc0);
      stepTargetPitch(a, 0xc0, a.unregSeed54e ?? 0);
    }
    if (a.contactP1 < 0 && ((a.unregLatch14a ?? 0) & (a.unregFlag541 ?? 0)) !== 0) {
      a.unregLatch14a = 0; a.unregFlag541 = 0;
      a.unregCounter6eb = ((a.unregCounter6eb ?? 0) + 1) & 1;
      startStream(a, 0xf, 3, ((a.unregSlot6ea ?? 0) + (a.unregCounter6eb ?? 0)) | 0, DEATH_BORG_BETA.STREAM_RATE);
      return;
    }
    if (a.dashStrength1d0f < 0) {
      a.dashStrength1d0f = 0;
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
    }
    applyDrag(a, DEATH_BORG_BETA.MOTION);
    integratePhysics(DEATH_BORG_BETA.PHYSICS_GRAVITY, a, a.lockYaw);
    const grounded = groundStep(a);
    if (grounded !== 0 && a.contactP0 < 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~0x3;
      dispatchUpperBodyCue(a, 7);
      a.stateTimer = DEATH_BORG_BETA.PHYSICS_GRAVITY + a.dt;
      return;
    }
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~0x3;
      romAirKnockoutReturn(a);
    }
  }
}
function betaV1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = DEATH_BORG_BETA.PH0_TIMER;
    a.unregSlot6ea = 0xb;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.activeYaw = a.heading;
    }
    stepTargetYaw(a, 0xc0);
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 3, slot, DEATH_BORG_BETA.STREAM_RATE);
    a.accumulator80c = DEATH_BORG_BETA.ZERO;
    return;
  }
  if (ph === 1) {
    if (a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_BETA.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = DEATH_BORG_BETA.V1_WINDUP_TIMER;
      a.hSpeed = DEATH_BORG_BETA.SPEED; a.hDecel = DEATH_BORG_BETA.ZERO;
    }
    return;
  }
  if (ph === 2) {
    stepTargetYaw(a, 0xc0);
    if (a.dashStrength1d0f !== 0) {
      a.dashStrength1d0f = 0;
      a.hSpeed = DEATH_BORG_BETA.SPEED; a.hDecel = DEATH_BORG_BETA.ZERO;
    }
    applyDrag(a, DEATH_BORG_BETA.MOTION);
    physicsMove(a, a.lockYaw);
    tickStream(a, 0xf, ctx);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= DEATH_BORG_BETA.ZERO) {
      a.handlerTimer = DEATH_BORG_BETA.ZERO;
      if (a.contactP0 !== 0) {
        a.fbPhaseSlots[0] = ph + 1;
        const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
        startStream(a, 0xf, 3, slot, DEATH_BORG_BETA.STREAM_RATE);
      }
    }
    return;
  }
  if (ph === 3) {
    applyDrag(a, DEATH_BORG_BETA.V1_DRAG);
    physicsMove(a, a.lockYaw);
    if (a.hSpeed < DEATH_BORG_BETA.PHYSICS_GRAVITY && a.wallContact !== 0) {
      tickStream(a, 0xf, ctx);
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~0x3;
      romGroundIdleReturn(a);
    }
  }
}
function createBetaRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.actionIndex === 1) {
      if (a.variantIndex === 1) betaV1(a, ctx); else betaV0(a, ctx);
    }
  };
}
export function configureDeathBorgBetaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0109 ?? 0x109;
  actor.rootAction = createBetaRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// METAL HERO (pl080a) — dash (a0 @0x80435a54) + air dive (a2 @0x80383b60).
// ============================================================================
function metalA0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.unregSlot6ea = (a.controlWord & 0x40) !== 0 ? 1 : 0;
    a.gravityCoeff = METAL_HERO.ZERO; a.yVel = METAL_HERO.ZERO;
    a.hDecel = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
    a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
    if (!hasLock(a)) a.activeYaw = a.heading;
    stepTargetYaw(a, 0xc1, 0, true);
    applyBlink(a, METAL_HERO.MOTION);
    groundSnapRevert(a);
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 2, slot, METAL_HERO.STREAM_RATE);
    a.accumulator80c = METAL_HERO.ZERO;
    return;
  }
  if (ph === 1) {
    if (((a.statusWord5bc ?? 0) & 0x200) !== 0 && (a.unregFlag541 ?? 0) !== 0) {
      if ((a.controlWord & 0x40) !== 0) { redispatchAction(a, 2, 0); return; }
      redispatchAction(a, 0, 0); return;
    }
    stepTargetYaw(a, 0xc1, 0, true);
    tickStream(a, 0xf, ctx);
    applyMotionDrift(a, METAL_HERO.MOTION);
    const grounded = groundSnapRevert(a);
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~METAL_HERO.ACTION_MODE_BITS;
      a.hDecel = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
      if (!grounded) romAirKnockoutReturn(a); else romGroundIdleReturn(a);
      a.stateTimer = METAL_HERO.EXIT_STATE_BASE + a.dt;
    }
  }
}
function metalA2(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.unregFlag541 = 0; a.unregFlag545 = 0;
    a.handlerTimer = METAL_HERO.A2_PH0_TIMER;
    a.unregSlot6ea = 2;
    if (!hasLock(a)) a.activeYaw = a.heading;
    stepTargetYaw(a, 0xc0);
    a.gravityCoeff = METAL_HERO.ZERO; a.yVel = METAL_HERO.ZERO;
    a.hDecel = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
    a.poseAccum80 = 0; a.poseAccum7e = 0; a.poseAccum7c = 0;
    applyBlink(a, METAL_HERO.A2_MOTION);
    groundSnapRevert(a);
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 4, slot, METAL_HERO.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    if (a.contactP1 < 1) tickStream(a, 0xf, ctx);
    else {
      tickStream(a, 0xf, ctx);
      a.handlerTimer -= a.dt;
      if (a.handlerTimer < METAL_HERO.ZERO) a.contactP1 = 0;
    }
    stepTargetYaw(a, 0xc0);
    applyMotionDrift(a, METAL_HERO.A2_MOTION);
    const grounded = groundSnapRevert(a);
    if (a.contactP0 > 0) {
      a.contactP0 = 0;
      if (allocateWeapon(a, ctx, 2, 1, true)) { a.unregFlag541 = 1; a.unregFlag545 = 1; }
      else { a.unregFlag541 = -1; a.unregFlag6e9 = 0; }
    }
    if (a.contactP1 < 0 && (a.unregFlag541 ?? 0) < 0) {
      a.fbPhaseSlots[0] = ph + 2; a.unregFlag6e9 = 0;
      if (grounded) a.controlWord = a.controlWord & 0xffffffbf;
      const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
      startStream(a, 0xf, 4, slot, METAL_HERO.STREAM_RATE);
    } else if (a.contactP0 < 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = METAL_HERO.A2_ACTIVE_TIMER;
      a.motion.x = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
    }
    return;
  }
  if (ph === 2) {
    integratePhysics(METAL_HERO.ZERO, a, a.lockYaw);
    const grounded = groundSnapRevert(a);
    if (!grounded) {
      a.handlerTimer -= a.dt;
      if (a.handlerTimer < METAL_HERO.ZERO) {
        a.unregFlag541 = -1; a.unregFlag6e9 = 0;
        a.housekeeping73f = 0;
        a.controlWord = a.controlWord & ~METAL_HERO.ACTION_MODE_BITS;
        a.hDecel = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
        romAirKnockoutReturn(a);
        a.stateTimer = METAL_HERO.EXIT_STATE_BASE + a.dt;
      }
    } else {
      a.fbPhaseSlots[0] = ph + 1; a.unregFlag541 = -1;
    }
    return;
  }
  if (ph === 3) {
    tickStream(a, 0xf, ctx);
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~METAL_HERO.ACTION_MODE_BITS;
      a.hDecel = METAL_HERO.ZERO; a.hSpeed = METAL_HERO.ZERO;
      const grounded = groundStep(a);
      if (!grounded) romAirKnockoutReturn(a); else romGroundIdleReturn(a);
      a.stateTimer = METAL_HERO.EXIT_STATE_BASE + a.dt;
    }
  }
}
function createMetalRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.actionIndex === 0) metalA0(a, ctx);
    else if (a.actionIndex === 2) metalA2(a, ctx);
  };
}
export function configureMetalHeroFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl080a ?? 0x80a;
  actor.rootAction = createMetalRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// POP HONEY (pl0904) — dash/blast (a0) + melee (a1). Shot spawn zz_0082824_(0x22).
// ============================================================================
function popA0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  const airVar = a.variantIndex === 2 || a.variantIndex === 4;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.unregFlag544 = 0; a.unregFlag545 = 0;
    if (a.variantIndex === 0) { a.hDecel = POP_HONEY.ZERO; a.hSpeed = POP_HONEY.ZERO; }
    else if (a.variantIndex === 3) { a.yVel = POP_HONEY.ZERO; a.gravityCoeff = POP_HONEY.ZERO; }
    else if (a.variantIndex === 2) {
      if (POP_HONEY.ZERO <= a.yVel) {
        a.yVel = a.yVel + (POP_HONEY.P2_ACCEL_HI < a.yVel ? POP_HONEY.P2_ACCEL_STEP : POP_HONEY.P2_ACCEL_LO);
      }
    } else if (a.variantIndex === 4 && 0 < (a.unregScalar764 ?? 0)) {
      a.yVel = a.yVel + POP_HONEY.P2_ACCEL_STEP;
    }
    a.unregYaw54a = a.lockYaw;
    if (!hasLock(a)) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.activeYaw = a.heading;
    }
    a.handlerTimer = POP_HONEY.MAIN_TIMER;
    stepTargetYaw(a, 0xc1);
    stepPartTargetPitch(a, 0xc1);
    startStream(a, 0xf, 2, airVar ? 3 : 0, POP_HONEY.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    tickStream(a, 0xf, ctx);
    const aim = stepTargetYaw(a, 0xc1);
    stepPartTargetPitch(a, 0xc1);
    a.handlerTimer -= a.dt;
    if ((a.wallContact === 0 || !aim) && POP_HONEY.ZERO < a.handlerTimer) return;
    a.fbPhaseSlots[0] = ph + 1;
    startStream(a, 0xf, 2, airVar ? 4 : 1, POP_HONEY.STREAM_RATE);
    return;
  }
  if (ph === 2) {
    tickStream(a, 0xf, ctx);
    if (a.wallContact !== 0) {
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(a, UNREG_SHOT_HELPER, 0x22); // zz_0082824_(0x22)
      }
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = POP_HONEY.MAIN_TIMER;
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
      startStream(a, 0xf, 2, airVar ? 5 : 2, POP_HONEY.STREAM_RATE);
    }
    return;
  }
  if (ph === 3) {
    a.steerYaw = Math.trunc((a.steerYaw ?? 0) * POP_HONEY.A0_STEER_DECAY);
    const done = tickStream(a, 0xf, ctx);
    if (done && airVar) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~POP_HONEY.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
      a.lockYaw = a.unregYaw54a ?? a.lockYaw;
      return;
    }
    a.handlerTimer -= a.dt;
    if (POP_HONEY.ZERO < a.handlerTimer) {
      if ((a.unregFlag545 ?? 0) !== 0) {
        if (airVar) {
          a.housekeeping73f = 0;
          a.controlWord = a.controlWord & ~POP_HONEY.ACTION_MODE_BITS;
          romAirKnockoutReturn(a);
          a.lockYaw = a.unregYaw54a ?? a.lockYaw;
        } else { a.fbPhaseSlots[0] = ph + 1; }
      }
    } else {
      a.hDecel = POP_HONEY.ZERO; a.hSpeed = POP_HONEY.ZERO;
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~POP_HONEY.ACTION_MODE_BITS;
      romAirKnockoutReturn(a);
    }
  }
}
function popA1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = POP_HONEY.MAIN_TIMER;
    a.unregLatch14a = 0;
    a.hSpeed = POP_HONEY.ZERO; a.hDecel = POP_HONEY.ZERO;
    a.unregFlag541 = 0;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.activeYaw = a.heading;
    }
    stepTargetYaw(a, 0xc0);
    a.accumulator80c = POP_HONEY.ZERO;
    return;
  }
  if (ph === 1) {
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= POP_HONEY.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = POP_HONEY.A1_WINDUP_TIMER;
    }
    return;
  }
  // active/recover follow the gold-hero a1 shape (chunk_0034.c:2837-3014);
  // TODO(host): descriptor aim matrix for exact velocity projection.
}
function createPopRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.actionIndex === 0) popA0(a, ctx);
    else if (a.actionIndex === 1) popA1(a, ctx);
  };
}
export function configurePopHoneyFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0904 ?? 0x904;
  actor.rootAction = createPopRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// JET HERO (pl0a01) — flying volley (a0) + melee (a1).
// ============================================================================
function jetA0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.unregTimer560 = JET_HERO.MAIN_TIMER;
    a.unregCountdown54c = 0;
    startStream(a, 1, 2, a.unregSlot6ea ?? 0, JET_HERO.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    a.unregCountdown54c = 0;
    if ((a.unregTimer560 ?? 0) < JET_HERO.ZERO || (a.wallContact !== 0 && (a.unregYaw54a ?? 0) !== 0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.unregCountdown54c = 5;
      startStream(a, 1, 2, ((a.unregSlot6ea ?? 0) + 5) | 0, JET_HERO.STREAM_RATE);
    }
    return;
  }
  if (ph === 2) {
    if ((a.inputEdge5d4 & 0x40) !== 0) a.unregLatch14a = 1;
    a.unregCountdown54c = 5;
    if (a.handlerTimer <= JET_HERO.ZERO) {
      if ((a.unregCounter6eb ?? 0) < 1) {
        a.fbPhaseSlots[0] = ph + 1;
        a.unregCooldown55c = JET_HERO.A1_PH0_TIMER;
        a.unregCountdown54c = 10;
        startStream(a, 7, 2, ((a.unregSlot6ea ?? 0) + 10) | 0, JET_HERO.STREAM_RATE);
      } else {
        startStream(a, 1, 2, ((a.unregSlot6ea ?? 0) + 5) | 0, JET_HERO.STREAM_RATE);
      }
    } else { a.handlerTimer -= a.dt; }
    if ((a.inputHeld5d8 & 0xf0) !== 0) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~JET_HERO.ACTION_MODE_BITS;
      const grounded = groundStep(a);
      if (!grounded) romAirIdleReturn(a); else romGroundIdleReturn(a);
      a.stateTimer = a.handlerTimer + a.dt;
    }
    return;
  }
  if (ph === 3) {
    if ((a.inputEdge5d4 & 0x40) !== 0) a.unregLatch14a = 1;
    a.unregCountdown54c = 10;
    if ((a.unregLatch14a ?? 0) !== 0 && allocateWeapon(a, ctx, 0, 1, false)) {
      a.fbPhaseSlots[0] = ph - 1;
      startStream(a, 1, 2, ((a.unregSlot6ea ?? 0) + 5) | 0, JET_HERO.STREAM_RATE);
      return;
    }
    if ((a.inputHeld5d8 & 0xf0) === 0) {
      a.unregCooldown55c = (a.unregCooldown55c ?? 0) - a.dt;
      if (JET_HERO.ZERO < (a.unregCooldown55c ?? 0) && a.wallContact === 0) return;
    }
    a.housekeeping73f = 0;
    a.controlWord = a.controlWord & ~JET_HERO.ACTION_MODE_BITS;
    const grounded = groundStep(a);
    if (!grounded) romAirIdleReturn(a); else romGroundIdleReturn(a);
  }
}
function jetA1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = JET_HERO.A1_PH0_TIMER;
    a.unregSlot6ea = 4;
    if (rangeCheck(a, speedRow(a), ctx) < 1) {
      a.unregFlag541 = 1;
      (a as RomActor & { lockTarget?: Vec3 | null }).lockTarget = null;
      a.lockYaw = a.heading; a.activeYaw = a.heading;
    }
    a.unregSeed54e = a.lockYaw;
    const slot = a.unregSlot6ea ?? 0; a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 3, slot, JET_HERO.STREAM_RATE);
    return;
  }
  if (ph === 1) {
    if (a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    applyDrag(a, JET_HERO.MOTION);
    integratePhysics(JET_HERO.PHYSICS_GRAVITY, a, a.unregSeed54e ?? a.lockYaw);
    groundStep(a);
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= JET_HERO.ZERO || stepTargetYaw(a, 0xc0)) {
      a.fbPhaseSlots[0] = ph + 1;
      a.handlerTimer = JET_HERO.MAIN_TIMER;
      a.hSpeed = JET_HERO.A1_SPEED * projectZ(a.unregSeed54e ?? 0);
      a.yVel = JET_HERO.A1_SPEED * -projectX(a.unregSeed54e ?? 0);
    }
    return;
  }
  if (ph === 2) {
    if (a.streamHold1b03 !== 0) tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    if (rangeCheck(a, JET_HERO.A1_RANGE, ctx) > 0) applyDrag(a, JET_HERO.ACTIVE_DRAG);
    integratePhysics(JET_HERO.PHYSICS_GRAVITY, a, a.lockYaw);
    groundStep(a);
    if (a.yVel < JET_HERO.ZERO) {
      a.fbPhaseSlots[0] = ph + 1;
      a.gravityCoeff = JET_HERO.ZERO; a.yVel = JET_HERO.ZERO;
    }
    return;
  }
  if (ph === 3) {
    tickStream(a, 0xf, ctx);
    stepTargetYaw(a, 0xc0);
    if (rangeCheck(a, JET_HERO.A1_RANGE, ctx) === 0) physicsMove(a, a.lockYaw);
    if (a.wallContact !== 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.hSpeed = JET_HERO.ZERO; a.yVel = JET_HERO.A1_EXIT_YVEL;
      a.gravityCoeff = a.descriptor?.handlerData6c ?? 0;
      groundStep(a);
    }
  }
}
function createJetRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    if (a.actionIndex === 0) jetA0(a, ctx);
    else if (a.actionIndex === 1) jetA1(a, ctx);
    else if (a.actionIndex === 2) jetA2(a, ctx);
  };
}

/** zz_0085638_ @0x80085638 — JET-family shot spawner. Kind-3 child (+0x10 = 3,
 *  +0x11 = subIdx). ACTION-2's ph1 borg switch spawns subIdx 0 for 0xa01 (pl0a01). */
export const JET_SHOT_SPAWNER = 0x80085638;

/** JET HERO action-2 (X-special) — FUN_80102800 → zz_0148384_ (chunk_0038.c:1629),
 *  2-phase table @0x804346a0 = [0x801483d0, 0x801484c0]:
 *    ph0 (0x801483d0) setup: +0x540++, face 0xc1, zero scalars/turn-rates,
 *        reposition ×0.95 + ground snap, group-4 stream (slot from +0x6ea,
 *        pre-increment — the wrapper's param2 slot).
 *    ph1 (0x801484c0) contact+exit: on +0x1cef contact clear + borg-switched
 *        spawn (0xa01 → zz_0085638_(0); 0xa03/0xa06 → zz_0085638_(1); 0xa02 →
 *        zz_0154e28_), then face + reposition; on +0x1cee wall contact exit
 *        (zero speeds, air idle zz_006a4f4_ / air fall zz_006a5a4_).
 */
function jetA2(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1; // +0x540++
    a.unregSlot6ea = 0;    // wrapper param2 slot (0 for the action-2 binding)
    if (!a.lockTarget) a.activeYaw = a.heading; // +0xcc == 0 → +0x5ac = +0x72
    stepTargetYaw(a, 0xc1); // zz_006d144_(actor, 0xc1)
    a.gravityCoeff = JET_HERO.ZERO;
    a.yVel = JET_HERO.ZERO;
    a.hDecel = JET_HERO.ZERO;
    a.hSpeed = JET_HERO.ZERO;
    a.poseAccum7c = 0;
    a.poseAccum7e = 0;
    a.poseAccum80 = 0;
    if (a.lockTarget) {
      vecSubtract(a.pos, a.lockTarget, a.motion);
      vecScale(0.949999988079071, a.motion, a.motion); // FLOAT_8043a350
      vecAdd(a.pos, a.motion, a.pos);
    }
    groundSnapRevert(a); // zz_0067a28_
    const slot = a.unregSlot6ea ?? 0;
    a.unregSlot6ea = slot + 1;
    startStream(a, 0xf, 4, slot, JET_HERO.STREAM_RATE); // zz_004beb8_(-1, mask 0xf, group 4)
    return;
  }
  if (ph === 1) {
    tickStream(a, 0xf, ctx);
    if (a.contactP0 !== undefined && a.contactP0 >= 1) {
      a.contactP0 = 0;
      if (a.borgNumber === 0xa01) {
        ctx.onFamilyProjectile?.(a, JET_SHOT_SPAWNER, 0);
      } else if (a.borgNumber === 0xa03 || a.borgNumber === 0xa06) {
        ctx.onFamilyProjectile?.(a, JET_SHOT_SPAWNER, 1);
      }
      // 0xa02 arm: zz_0154e28_ (bespoke — not reached by this binding; kept for
      // the borg switch's fidelity).
    }
    stepTargetYaw(a, 0xc1); // zz_006d144_(actor, 0xc1)
    if (a.lockTarget) {
      vecScale(0.949999988079071, a.motion, a.motion);
      vecAdd(a.pos, a.motion, a.pos);
    }
    groundSnapRevert(a); // zz_0067a28_
    if (a.wallContact !== 0) {
      a.housekeeping73f = 0;
      a.controlWord &= ~JET_HERO.ACTION_MODE_BITS;
      a.hDecel = JET_HERO.ZERO;
      a.hSpeed = JET_HERO.ZERO;
      if ((a.controlWord & 0x40) === 0) {
        romAirIdleReturn(a); // zz_006a4f4_
      } else {
        romAirKnockoutReturn(a); // zz_006a5a4_
      }
    }
    return;
  }
}
export function configureJetHeroFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0a01 ?? 0xa01;
  actor.rootAction = createJetRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// CARRIER HELICOPTER (pl0d02) — vehicle volley (a0) + dual spawn (a1) + deploy (a2).
// ============================================================================
function carrierA0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) { a.fbPhaseSlots[0] = 1; return; }
  if (ph === 1) {
    a.handlerTimer -= a.dt;
    if (tickUnregStream() !== 0 || a.handlerTimer < CARRIER.ZERO) {
      a.fbPhaseSlots[0] = ph + 1;
      a.unregCountdown548 = 0; a.unregShotCd14c = 0; a.unregCountdown54c = 0;
    }
    return;
  }
  if (ph === 2) {
    if ((a.statusWord5b4 & CARRIER.BURST_BIT_5B4) !== 0) a.unregCountdown548 = 1;
    if ((a.unregShotCd14c ?? 0) === 0) {
      a.unregShotCd14c = CARRIER.SHOT_INTERVAL;
      a.unregCountdown54c = (a.unregCountdown54c ?? 0) + 1;
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        const toggle = (a.unregCursor148 ?? 0) & 1;
        ctx.onFamilyProjectile?.(a, UNREG_SHOT_HELPER, toggle === 0 ? 0x12 : 0x13);
        a.unregCursor148 = toggle ^ 1;
      }
      if ((a.unregCountdown548 ?? 0) === 0) {
        if (1 < (a.unregCountdown54c ?? 0)) {
          a.fbPhaseSlots[0] = ph + 1; a.unregCountdown548 = CARRIER.COOLDOWN_COUNT;
        }
      } else {
        a.unregCountdown548 = 0;
        if (CARRIER.BURST_SHOT_CAP < (a.unregCountdown54c ?? 0)) {
          a.fbPhaseSlots[0] = ph + 1; a.unregCountdown548 = CARRIER.COOLDOWN_COUNT;
        }
      }
    } else { a.unregShotCd14c = (a.unregShotCd14c ?? 0) - 1; }
    return;
  }
  if (ph === 3) {
    a.unregCountdown548 = (a.unregCountdown548 ?? 0) - 1;
    if ((a.unregCountdown548 ?? 0) < 1) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~0x3;
      romAirKnockoutReturn(a);
    }
  }
}
function carrierA1(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = CARRIER.A1_PH0_TIMER;
    a.unregCountdown548 = 0; a.unregShotCd14c = 0; a.unregCountdown54c = 0;
    a.gravityCoeff = CARRIER.ZERO; a.hDecel = CARRIER.ZERO;
    return;
  }
  if (ph === 1) {
    a.handlerTimer -= a.dt;
    const aim = stepTargetYaw(a, 0x81, 0, true); // FUN_800669d0(0x81)
    if (aim || a.handlerTimer <= CARRIER.ZERO) {
      a.fbPhaseSlots[0] = ph + 1; a.handlerTimer = CARRIER.ZERO;
    }
    return;
  }
  if (ph === 2) {
    if ((a.unregShotCd14c ?? 0) === 0) {
      a.unregShotCd14c = CARRIER.SHOT_INTERVAL;
      a.unregCountdown54c = (a.unregCountdown54c ?? 0) + 1;
      if (allocateWeapon(a, ctx, 2, 1, true)) {
        a.unregCursor148 = 1;
        ctx.onFamilyProjectile?.(a, UNREG_CARRIER_DUAL_SPAWNER, 0); // zz_01043ac_(0)
        a.unregToggle14e = 1;
        ctx.onFamilyProjectile?.(a, UNREG_CARRIER_DUAL_SPAWNER, 1); // zz_01043ac_(1)
      }
      if ((a.unregCountdown548 ?? 0) === 0) {
        a.fbPhaseSlots[0] = ph + 1; a.unregCountdown548 = CARRIER.COOLDOWN_COUNT;
      } else {
        a.unregCountdown548 = 0;
        if (CARRIER.BURST_SHOT_CAP < (a.unregCountdown54c ?? 0)) {
          a.fbPhaseSlots[0] = ph + 1; a.unregCountdown548 = CARRIER.COOLDOWN_COUNT;
        }
      }
    } else { a.unregShotCd14c = (a.unregShotCd14c ?? 0) - 1; }
    return;
  }
  if (ph === 3) {
    a.unregCountdown548 = (a.unregCountdown548 ?? 0) - 1;
    if ((a.unregCountdown548 ?? 0) < 1) {
      a.housekeeping73f = 0;
      a.controlWord = a.controlWord & ~0x3;
      romAirKnockoutReturn(a);
    }
  }
}
function carrierA2(a: UA, _ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) { a.fbPhaseSlots[0] = 1; return; }
  if (ph === 1) {
    if ((a.unregLatch14a ?? 0) === 0) {
      a.fbPhaseSlots[0] = ph + 1;
      a.unregCountdown548 = CARRIER.DEPLOY_COUNT;
      a.unregLatch14a = 1;
    } else { exitAction(a, CARRIER.DEPLOY_CANCEL); }
    return;
  }
  if (ph === 2) {
    a.unregCountdown548 = (a.unregCountdown548 ?? 0) - 1;
    if ((a.unregCountdown548 ?? 0) < 1) exitAction(a, 0);
  }
}
function createCarrierRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    switch (a.actionIndex) {
      case 0: carrierA0(a, ctx); return;
      case 1: carrierA1(a, ctx); return;
      case 2: carrierA2(a, ctx); return;
      default: return;
    }
  };
}
export function configureCarrierHelicopterFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0d02 ?? 0xd02;
  actor.rootAction = createCarrierRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// FLYING SAUCER (pl0d03) — vehicle volley (a0) + deploy (a2).
// ============================================================================
function saucerA0(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) { a.fbPhaseSlots[0] = 1; return; }
  if (ph === 1) {
    if ((a.statusWord5bc ?? 0) & FLYING_SAUCER.BURST_BIT_5BC) a.unregBurst152 = 1;
    a.handlerTimer -= a.dt;
    if (tickUnregStream() !== 0 || a.handlerTimer < FLYING_SAUCER.ZERO) {
      a.fbPhaseSlots[0] = ph + 1;
    }
    return;
  }
  if (ph === 2) {
    if ((a.statusWord5bc ?? 0) & FLYING_SAUCER.BURST_BIT_5BC) a.unregBurst152 = 1;
    if ((a.unregShotCd154 ?? 0) === 0) {
      a.unregShotCd154 = FLYING_SAUCER.SHOT_INTERVAL;
      a.unregShotCount156 = (a.unregShotCount156 ?? 0) + 1;
      if (allocateWeapon(a, ctx, 0, 1, true)) {
        ctx.onFamilyProjectile?.(a, UNREG_EFFECT_SPAWNER_C3BE0, 0x36); // zz_00c3be0_(0x36)
        ctx.onFamilyProjectile?.(a, UNREG_EFFECT_SPAWNER_C3BE0, 0x37); // zz_00c3be0_(0x37)
        a.unregToggle151 = ((a.unregToggle151 ?? 0) + 1) & 1;
      }
      if ((a.unregBurst152 ?? 0) === 0) {
        if (0 < (a.unregShotCount156 ?? 0)) {
          a.fbPhaseSlots[0] = ph + 1; a.handlerTimer = FLYING_SAUCER.SPAWN_EXIT_TIMER;
        }
      } else {
        a.unregBurst152 = 0;
        if (FLYING_SAUCER.BURST_SHOT_CAP < (a.unregShotCount156 ?? 0)) {
          a.fbPhaseSlots[0] = ph + 1; a.handlerTimer = FLYING_SAUCER.SPAWN_EXIT_TIMER;
        }
      }
    } else { a.unregShotCd154 = (a.unregShotCd154 ?? 0) - 1; }
    return;
  }
  if (ph === 3) {
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= FLYING_SAUCER.ZERO) exitAction(a, 0);
  }
}
function saucerDeploySolve(a: UA): void {
  a.unregMode6f7 = 2;
  // zz_0189704_(actor,+0x144) — gnt4_PSMTXMultVec on renderer-owned part-anchor
  // +0x934 (TODO(host): exact matrix solve deferred to host bridge).
  if ((a.unregCountdown54c ?? 0) < 1) {
    a.unregCountdown548 = toS16(Math.trunc((a.unregYaw54a ?? 0) * a.dt + (a.unregCountdown548 ?? 0)));
    a.handlerTimer -= a.dt;
    if (a.handlerTimer <= FLYING_SAUCER.ZERO) a.fbPhaseSlots[0] = (a.fbPhaseSlots[0] ?? 0) + 1;
  } else { a.unregCountdown54c = (a.unregCountdown54c ?? 0) - 1; }
}
function saucerA2(a: UA, ctx: UnregFamilyCtx): void {
  const ph = a.fbPhaseSlots[0] ?? 0;
  if (ph === 0) {
    a.fbPhaseSlots[0] = 1;
    a.unregCountdown548 = 0x4000;
    a.unregYaw54a = toS16(0xfde0);
    a.unregCountdown54c = 0x14;
    a.handlerTimer = FLYING_SAUCER.DEPLOY_TIMER;
    if (!allocateWeapon(a, ctx, 2, 1, true)) { exitAction(a, FLYING_SAUCER.DEPLOY_PARAM); return; }
    ctx.onFamilyProjectile?.(a, UNREG_DEPLOY_ARM, 8); // zz_01deb68_(actor,8,...)
    saucerDeploySolve(a); // ROM calls zz_01895e8_ inline at end of ph0
    return;
  }
  if (ph === 1) { saucerDeploySolve(a); return; }
  if (ph === 2) {
    a.unregCountdown548 = (a.unregCountdown548 ?? 0) - 1;
    if ((a.unregCountdown548 ?? 0) < 1) exitAction(a, FLYING_SAUCER.DEPLOY_PARAM);
  }
}
function createSaucerRootAction(ctx: UnregFamilyCtx): (actor: RomActor) => void {
  return (base: RomActor) => {
    const a = scratchOf(base);
    switch (a.actionIndex) {
      case 0: saucerA0(a, ctx); return;
      case 2: saucerA2(a, ctx); return;
      default: return;
    }
  };
}
export function configureFlyingSaucerFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS.pl0d03 ?? 0xd03;
  actor.rootAction = createSaucerRootAction(ctx as UnregFamilyCtx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Generic configure (tableless fallback). Stamps borg number; generic layer owns logic. */
export function configureUnregisteredFamily(actor: RomActor, borgId: UnregBorgId, _ctx: StreamContext): void {
  actor.borgNumber = UNREG_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = null;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirror rom.selfcheck.ts / vehicle-borg.ts style. Covers phase
// transitions, ammo gates, spawns, and exits for the vehicle + spawn-machine
// families (the cleanest end-to-end machines).
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

type Shot = { addr: number; type: number };

function shotCtx(onAlloc: boolean, sink: Shot[]): StreamContext {
  return {
    onAllocateResource: () => onAlloc,
    onFamilyProjectile: (_a, addr, type) => sink.push({ addr, type }),
  };
}

export function runUnregisteredClusterSelfTests(assert: AssertFn): void {
  // ========================================================================
  console.log("[unregistered-cluster] FLYING SAUCER (pl0d03) — action 0 volley:");
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(true, shots);
    const a = createRomActor() as UA;
    configureFlyingSaucerFamily(a, sctx);
    assert(a.borgNumber === 0xd03, "pl0d03 borgNumber stamped 0xd03");
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0 advance
    assert(a.fbPhaseSlots[0] === 1, "saucer a0 ph0 advances to ph1");
    a.handlerTimer = -1;
    root(a); // ph1 advance (threshold < 0)
    assert(a.fbPhaseSlots[0] === 2, "saucer a0 ph1 advances to ph2 when +0x558 < 0.0");
    root(a); // ph2 spawn (shotCd 0 → fire)
    assert(shots.length === 2 && shots[0]!.addr === UNREG_EFFECT_SPAWNER_C3BE0,
      `saucer a0 ph2 spawns zz_00c3be0_(0x36)+0x37 (got ${JSON.stringify(shots)})`);
    assert(a.fbPhaseSlots[0] === 3 && a.handlerTimer === FLYING_SAUCER.SPAWN_EXIT_TIMER,
      "saucer a0 ph2 single-shot advances to ph3 + +0x558=40 (FLOAT_8043afc8)");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 40; i++) root(a);
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "saucer a0 ph3 exits via zz_006a53c_(0) when +0x558 <= 0.0");
  }

  // --- FLYING SAUCER action 0 ammo denial suppresses spawn. ---
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(false, shots);
    const a = createRomActor() as UA;
    configureFlyingSaucerFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); a.handlerTimer = -1; root(a); root(a);
    assert(shots.length === 0, "saucer a0 ammo denial suppresses spawn");
  }

  // --- FLYING SAUCER action 2 deploy: ammo OK → arm + countdown exit. ---
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(true, shots);
    const a = createRomActor() as UA;
    configureFlyingSaucerFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    root(a); // ph0 arm + inline solve
    assert(shots.length === 1 && shots[0]!.addr === UNREG_DEPLOY_ARM && shots[0]!.type === 8,
      `saucer a2 ph0 spawns zz_01deb68_(8) (got ${JSON.stringify(shots)})`);
    assert(a.unregCountdown54c === 0x14 - 1, "saucer a2 ph0 inline solve decrements +0x54c");
    for (let i = 0; i < 18; i++) root(a); // +0x54c → 1
    root(a); // +0x54c → 0 (else branch)
    root(a); // first drain-frame: accumulate +0x548 + drain +0x558
    assert(a.unregCountdown548 === toS16(0x4000 + 0xfde0 * 1),
      "saucer a2 solve accumulates +0x548 one frame (CONCAT44 idiom)");
    for (let i = 0; i < 31; i++) root(a);
    root(a); // +0x558 → <= 0 → advance to ph2
    assert(a.fbPhaseSlots[0] === 2, "saucer a2 ph1 advances to ph2 when +0x558 <= 0.0");
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.unregCountdown548 = 1;
    root(a); // ph2 exit
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "saucer a2 ph2 exits via zz_006a53c_(0x1e) when +0x548 < 1");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] CARRIER HELICOPTER (pl0d02) — action 0 volley:");
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(true, shots);
    const a = createRomActor() as UA;
    configureCarrierHelicopterFamily(a, sctx);
    assert(a.borgNumber === 0xd02, "pl0d02 borgNumber stamped 0xd02");
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); root(a); // ph0 + ph1
    assert(a.fbPhaseSlots[0] === 2, "carrier a0 ph1 advances to ph2");
    root(a); // ph2 spawn (first shot, count=1, no advance — interval 4)
    assert(shots.length === 1 && shots[0]!.addr === UNREG_SHOT_HELPER && shots[0]!.type === 0x12,
      `carrier a0 ph2 fires zz_0082824_(0x12) first shot (got ${JSON.stringify(shots)})`);
    assert(a.unregCursor148 === 1, "carrier a0 ph2 toggles +0x148 0→1");
    // Non-burst advances after the 2nd shot (+0x54c > 1): 4 cooldown ticks + fire.
    root(a); root(a); root(a); root(a); // +0x54a: 3→2→1→0
    root(a); // +0x54a == 0 → fire 2nd shot, count=2, advance
    assert(shots.length === 2 && a.fbPhaseSlots[0] === 3,
      "carrier a0 ph2 non-burst advances to ph3 after 2nd shot (+0x54c > 1)");
  }

  // --- CARRIER action 1 dual spawn (ammo-gated zz_01043ac_ ×2). ---
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(true, shots);
    const a = createRomActor() as UA;
    configureCarrierHelicopterFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    root(a); root(a); root(a); // ph0 + ph1 + ph2
    assert(shots.length === 2 && shots[0]!.addr === UNREG_CARRIER_DUAL_SPAWNER,
      `carrier a1 ph2 spawns zz_01043ac_(0)+(1) (got ${JSON.stringify(shots)})`);
  }

  // --- CARRIER action 2 deploy cancel on re-enter (zz_006a53c_(10)). ---
  {
    const sctx = shotCtx(true, []);
    const a = createRomActor() as UA;
    configureCarrierHelicopterFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    root(a); root(a); // ph0 + ph1 (arm)
    assert(a.unregCountdown548 === CARRIER.DEPLOY_COUNT && a.unregLatch14a === 1,
      "carrier a2 ph1 first enter arms deploy (+0x548=0xf, +0x14a=1)");
    a.fbPhaseSlots[0] = 1;
    root(a); // re-enter ph1 → cancel
    assert(approxEq(a.stateTimer, CARRIER.DEPLOY_CANCEL + 1),
      "carrier a2 ph1 re-enter cancels via zz_006a53c_(10) → +0x694 = 10+dt");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] DEATH BORG TAU (pl0807) — ground melee setup:");
  {
    const a = createRomActor() as UA;
    configureDeathBorgTauFamily(a, shotCtx(true, []));
    assert(a.borgNumber === 0x807, "pl0807 borgNumber stamped 0x807");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 1; a.dt = 1;
    a.heading = 0x100;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "tau ground ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, DEATH_BORG_TAU.PH0_TIMER), "+0x558 = 60 (FLOAT_8043b540)");
    assert(a.unregSlot6ea === 3, "tau ph0 streamSlot advances 2→3");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] DEATH BORG ALPHA (pl0008) — a0 v0 setup + windup:");
  {
    const a = createRomActor() as UA;
    configureDeathBorgAlphaFamily(a, shotCtx(true, []));
    assert(a.borgNumber === 0x008, "pl0008 borgNumber stamped 0x008");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "alpha a0v0 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, DEATH_BORG_ALPHA.MAIN_TIMER), "+0x558 = 7 (FLOAT_8043b4d8)");
    assert(a.unregShots6ef === 5, "alpha ph0 seeds +0x6ef = 5 shots remaining");
    // windup drains +0x560 (30) → after 30 ticks advance on contact.
    a.contactP0 = 1;
    for (let i = 0; i < 30; i++) root(a);
    assert(a.fbPhaseSlots[0] === 2, "alpha a0v0 ph1 advances to ph2 on contact after +0x560 drain");
    assert(a.unregShots6ef === 4, "alpha ph1 spawn decrements +0x6ef 5→4");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] METAL HERO (pl080a) — a0 dash setup:");
  {
    const a = createRomActor() as UA;
    configureMetalHeroFamily(a, shotCtx(true, []));
    assert(a.borgNumber === 0x80a, "pl080a borgNumber stamped 0x80a");
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.pos = { x: 20, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "metal a0 ph0 advances to ph1");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "metal a0 ph0 zeroes velocity scalars (FLOAT_8043bb38)");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] POP HONEY (pl0904) — a0 blast spawn:");
  {
    const shots: Shot[] = [];
    const sctx = shotCtx(true, shots);
    const a = createRomActor() as UA;
    configurePopHoneyFamily(a, sctx);
    assert(a.borgNumber === 0x904, "pl0904 borgNumber stamped 0x904");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "pop a0 ph0 advances to ph1");
    a.handlerTimer = -1; root(a); // ph1 → ph2
    assert(a.fbPhaseSlots[0] === 2, "pop a0 ph1 advances to ph2 on timer expiry");
    a.wallContact = 1; root(a); // ph2 spawn
    assert(shots.length === 1 && shots[0]!.addr === UNREG_SHOT_HELPER && shots[0]!.type === 0x22,
      `pop a0 ph2 spawns zz_0082824_(0x22) on contact (got ${JSON.stringify(shots)})`);
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] JET HERO (pl0a01) — a1 melee windup:");
  {
    const a = createRomActor() as UA;
    configureJetHeroFamily(a, shotCtx(true, []));
    assert(a.borgNumber === 0xa01, "pl0a01 borgNumber stamped 0xa01");
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "jet a1 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, JET_HERO.A1_PH0_TIMER), "+0x558 = 60 (FLOAT_8043935c)");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] JET HERO (pl0a01) — a2 X-special (FUN_80102800):");
  {
    const shots: Array<{ addr: number; type: number }> = [];
    const a = createRomActor() as UA;
    configureJetHeroFamily(a, shotCtx(true, shots));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.controlWord = 0x3;
    a.pos = { x: 0, y: 0, z: 0 };
    a.lockTarget = { x: 0, y: 0, z: 100 };
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "jet a2 ph0 advances to ph1");
    assert(a.unregSlot6ea === 1, "jet a2 ph0 seeds +0x6ea = 0 then pre-increments to 1");
    // ph1: contact → borg-switched spawn (0xa01 → subIdx 0).
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === JET_SHOT_SPAWNER && shots[0]!.type === 0,
      "jet a2 contact spawns zz_0085638_ subIdx 0 for 0xa01");
    // ph1 wall-contact exit: air idle (controlWord airborne bit 0x40 == 0).
    a.wallContact = 1;
    a.contactP0 = 0;
    root(a);
    assert((a.controlWord & JET_HERO.ACTION_MODE_BITS) === 0,
      "jet a2 wall exit strips action-mode bits");
  }

  // ========================================================================
  console.log("\n[unregistered-cluster] DEATH BORG BETA (pl0109) — a1 v0 setup:");
  {
    const a = createRomActor() as UA;
    configureDeathBorgBetaFamily(a, shotCtx(true, []));
    assert(a.borgNumber === 0x109, "pl0109 borgNumber stamped 0x109");
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1, "beta a1v0 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, DEATH_BORG_BETA.PH0_TIMER), "+0x558 = 60 (FLOAT_8043bf3c)");
  }
}
