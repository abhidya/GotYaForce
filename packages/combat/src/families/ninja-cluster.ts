// Ninja cluster — ROM-faithful 1:1 port of the THREE ninja families that share the
// chunk_0009.c / chunk_0025.c action-script region + the shuriken/kunai spawner tables:
//
//   NORMAL NINJA   pl0000/pl000a  ctor 0x8006f4f8  (chunk_0009.c) — action 0/1 ported
//                                                  here; action 2 (X) COMPOSED with the
//                                                  existing ninja.ts X-special callback.
//   DOUBLE NINJA   pl0003         ctor 0x8006f60c  (chunk_0009.c) — action 3 X-charge
//                                                  dash + action 4 big-shuriken toss.
//   SHURIKEN NINJA pl0001         ctor 0x800ea500  (chunk_0025.c) — action 0 ground
//                                                  combo + action 1 lunge + action 2 X.
//
// The three share the shuriken spawner zz_007db5c_ @0x8007db5c (table 0x802d6d68) and
// the kunai spawner zz_006ee14_ @0x8006ee14 (table 0x802d39b0); both surfaced through
// StreamContext.onFamilyProjectile. Float constants DOL-read this session (cited inline).
//
// Sources: research/decomp/ghidra-export/chunk_0009.c:5339-5593 + chunk_0010.c:1-47
//          (NORMAL/DOUBLE), chunk_0025.c:1953-3047 (SHURIKEN); decode doc
//          research/decomp/nn-family-decode-2026-07-06.md.
//
// NORMAL NINJA wiring decision: configureNormalNinjaFamily SUPERSEDES the existing
// configureNinjaFamily (ninja.ts) at the pl0000/pl000a registrations. It re-implements
// action 0/1 self-contained here and COMPOSES action 2 (X) by importing ninja.ts's
// ninjaXOnHit callback + NINJA_X config into the shared zz_00ff2bc_ machine — so the
// ninja.ts import STAYS (it is the source of the X-special callback), but its
// configureNinjaFamily is no longer the registration target. ninja.ts itself is
// unchanged (rom.selfcheck.ts still imports configureNinjaFamily/NINJA_X from it).

import { createRomActor, type RomActor } from "../rom/actor.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";
import { createSharedMeleeLunge, NINJA_LUNGE_CONFIG } from "./shared-melee-lunge.js";
import { ninjaXOnHit, NINJA_X } from "./ninja.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { allocateWeapon } from "../rom/helpers.js";
import { romGroundIdleReturn, romAirKnockoutReturn } from "./shared-idle-return.js";

// ============================================================================
// Spawner addresses (named const exports — the family-local projectile/effect
// spawners referenced by the three machines).
// ============================================================================
/** zz_006ee14_ @0x8006ee14 — kunai per-swing throw (table 0x802d39b0). */
export const KUNAI_SPAWNER_ADDR = 0x8006ee14;
/** zz_007db5c_ @0x8007db5c — shuriken record-table spawn (table 0x802d6d68). */
export const SHURIKEN_SPAWNER_ADDR = 0x8007db5c;
/** zz_0082824_ @0x80082824 — record-table projectile spawn (generic). */
export const NINJA_SHOT_HELPER = 0x80082824;

// ============================================================================
// Float constants — every value read from boot.dol this session (cited per use).
// ============================================================================
/** Normal/Double ninja floats (sdata2 @0x804376xx/0x804377xx). */
export const NINJA_FLOATS = {
  ZERO: 0.0,            // FLOAT_804376e4 — zero scalar / threshold
  NEG_ONE: -1.0,        // FLOAT_804376e0 — stream rate / gravity
  RANGE: 150.0,         // FLOAT_804376f8 — dash/charge range + speed base
  SWING_TIMER: 30.0,    // FLOAT_80437708 — B-combo swing timer / dash frames
  AIM_TIMER: 60.0,      // FLOAT_8043770c — face-target budget
  REPOS_98: 0.98,       // FLOAT_80437710 — shuriken-ninja reposition scale
  LEAP_GRAV_BASE: 2.0,  // FLOAT_80437728 — leap gravity term base (×−yVel/30)
  REPOS_95: 0.95,       // FLOAT_80437744 — motion decay / reposition scale
  BACKFLIP_HSPEED: 10.0,// FLOAT_80437748 — backflip hSpeed / contact timer
  SPIN_WINDOW: 20.0,    // FLOAT_8043774c — spin window / big-shuriken dash frames
  XCHARGE_EXIT_TIMER: 8.0, // FLOAT_80437764 — X-charge ph2 exit +0x694 seed
  BACKFLIP_YVEL: 15.0,  // FLOAT_80437768 — backflip yVel / X-charge +0x558 seed
  XCHARGE_7B0_SCALE: 0.92, // FLOAT_8043776c — X-charge ph1 +0x7b0 decay
  XCHARGE_BAM: 16384.0, // FLOAT_80437770 — quarter-turn BAM (cos charge ramp)
  RECOVER_DECAY: 0.97,  // FLOAT_80437774 — recovery motion decay
  TRAIL_GATE: 3.0,      // FLOAT_80437778 — afterimage distance gate
} as const;

/** Shuriken-ninja floats (sdata2 @0x80438fxx). */
export const SHURIKEN_FLOATS = {
  STEER_DECAY: 0.9,     // FLOAT_80438f68 — steerYaw decay (CONCAT44 idiom)
  STREAM_RATE: -1.0,    // FLOAT_80438f78 — stream playback rate
  ZERO: 0.0,            // FLOAT_80438f7c — zero scalar / threshold
  GRAVITY: 1.0,         // FLOAT_80438f80 — FUN_80067310 gravity param
  COMBO_TIMER: 30.0,    // FLOAT_80438f84 — combo swing timer / dash divisor
  ACTION1_TIMER: 60.0,  // FLOAT_80438f88 — action-1 ph0 / X ph0 +0x558 seed
  REPOS_98: 0.98,       // FLOAT_80438f8c — action-1 reposition scale
  RANGE_50: 50.0,       // FLOAT_80438f90 — action-1 range gate / X ph4 timer
  YVEL_MIN: -30.0,      // FLOAT_80438f94 — action-1 ph2 yVel clamp
  DASH_FRAMES_20: 20.0, // FLOAT_80438f98 — action-1 flying-lunge dash frames
  YVEL_DIV: 12.0,       // FLOAT_80438f9c — action-1 flying-lunge yVel divisor
  RANGE_150: 150.0,     // FLOAT_80438fa0 — action-1 flying-lunge range gate
  REPOS_95: 0.95,       // FLOAT_80438fa4 — X motion scale / flying recover decay
  X_PH2_TIMER: 45.0,    // FLOAT_80438fa8 — X ph2 +0x558 seed
  X_PH2_MY: 40.0,       // FLOAT_80438fac — X ph2 motion.y component
  X_PH2_MZ: 2.0,        // FLOAT_80438fb0 — X ph2 motion.z component
  X_PH2_760_GATE: 250.0,// FLOAT_80438fb4 — X ph2 +0x760 FX gate
  X_PH3_TIMER: 120.0,   // FLOAT_80438fb8 — X ph3 +0x558 seed
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not first-class on RomActor.
// (statusWord5b4 / inputEdge5d4 / inputHeld5d8 / contactP0 / wallContact etc. are
// already first-class on RomActor and read directly.)
// ============================================================================
export interface NinjaClusterScratch {
  /** Host-set lock target (mirrors +0xcc target pointer). */
  lockTarget?: { x: number; y: number; z: number } | null;
  /** Host-set grounded flag (mirrors +0x5e0 & 0x40 inverse / floor probe). */
  grounded?: boolean;
  /** +0x5b4 & 0x200 — B-held (burst/charge) latch. */
  bHeld?: boolean;
  /** +0x6ee/+0x6ef combo cursor + swings-left (zz_0070530_/zz_00eb228_). */
  comboStep?: number;
  swingsLeft?: number;
  /** +0x6ed combo max seed (shuriken ninja zz_00eb1f8_). */
  comboMax6ed?: number;
  /** +0x7c8 shuriken-arm flag (X-charge dash gates the type-2 shuriken spawn). */
  shurikenArm7c8?: number;
  /** +0x55c handler sub-timer (X-charge charge-speed ramp). */
  timer55c?: number;
  /** +0x560 swing sub-timer. */
  timer560?: number;
  /** +0x760 movement speed scalar (dash-speed floor / FX gate). */
  speedScalar760?: number;
  /** +0x764 dash-speed floor (action-1 lunge hSpeed min). */
  speedScalar764?: number;
}

type NcActor = RomActor & NinjaClusterScratch;

function scratchOf(actor: RomActor): NcActor {
  return actor as NcActor;
}

function targetDist(actor: RomActor): number | null {
  const t = (actor as NcActor).lockTarget;
  if (!t) return null;
  return Math.hypot(t.x - actor.pos.x, t.z - actor.pos.z);
}

// ----------------------------------------------------------------------------
// zz_006a53c_(actor, param) — chunk_0009.c:750. Common action-exit: clear
// housekeeping, strip the action-mode bits, dispatch full-body cue 0x1b, and
// (when param > 0) seed +0x694 = param + dt.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, 0x1b);
}

/** Airborne = +0x5e0 position-frozen bit set (bridge mirrors grounded inverse). */
function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as NcActor).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

// ============================================================================
// NORMAL NINJA (pl0000/pl000a) — action 0 B-tap sword combo + action 1
// contextual-B. Action 2 (X) is COMPOSED via ninja.ts's ninjaXOnHit + the shared
// zz_00ff2bc_ machine (config @0x80433868).
// ============================================================================

/** zz_0070530_-shaped combo seed (NORMAL NINJA B-combo): 5 swings, cursor 0. */
function normalComboSeed(actor: NcActor): void {
  if (!actor.comboStep) {
    actor.comboStep = 0;
    actor.swingsLeft = 5;
  }
  actor.timer560 = NINJA_FLOATS.SWING_TIMER; // +0x560 = 30.0 (FLOAT_80437708)
}

/** zz_0070558_-shaped per-swing bookkeeping + kunai throw (borg-switched variant). */
function normalSwingSpawn(actor: NcActor, ctx: StreamContext): void {
  actor.comboStep = (actor.comboStep ?? 0) + 1;
  actor.swingsLeft = (actor.swingsLeft ?? 5) - 1;
  // Kunai zz_006ee14_: SASUKE (0x00a) → variant 4 (speed 85); else variant 0.
  const variant = actor.borgNumber === 0x00a ? 4 : 0;
  ctx.onFamilyProjectile?.(actor, KUNAI_SPAWNER_ADDR, variant);
}

/** Action 0 — B-tap ground combo, table @0x802d3ba4 (3 phases). */
function normalBCombo(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      normalComboSeed(actor);
      actor.handlerTimer = NINJA_FLOATS.SWING_TIMER;
      actor.hSpeed = 0;
      actor.hDecel = 0;
      actor.controlWord &= ~0xb0; // P0 clears +0x5e0 bits 0xb0
      startStream(actor, 0x1, 2, actor.comboStep ?? 0); // part 1: g2 slot (combo step)
      startStream(actor, 0x2, 2, 9);                    // part 2: g2 slot 9 overlay
      return;
    }
    case 1: {
      if (actor.contactP0 === 0) tickStream(actor, 0x1, ctx);
      if (actor.lockTarget == null) {
        actor.handlerTimer -= actor.dt;
      }
      if (actor.contactP0 > 0 || actor.handlerTimer <= -NINJA_FLOATS.SWING_TIMER) {
        actor.fbPhaseSlots[0] = 2;
        normalSwingSpawn(actor, ctx);
      }
      return;
    }
    case 2: {
      tickStream(actor, 0x1, ctx);
      const swingsLeft = actor.swingsLeft ?? 0;
      if (actor.bHeld && swingsLeft > 0) {
        // Ground loop — restart part-1 at g2 slot 1, back to phase 1.
        actor.fbPhaseSlots[0] = 1;
        startStream(actor, 0x1, 2, 1);
        actor.handlerTimer = NINJA_FLOATS.SWING_TIMER;
        actor.contactP0 = 0;
        return;
      }
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0) {
        actor.comboStep = 0;
        actor.controlWord &= ~0x3;
        romGroundIdleReturn(actor); // zz_006a474_
      }
      return;
    }
    default:
      return;
  }
}

// ----------------------------------------------------------------------------
// NORMAL NINJA action 1 — contextual-B (borg-switched). pl0000 v2 = spin slash,
// v4 = leap dive-slam; SASUKE v1/v2 = big-shuriken toss; v0/v1 (+ v3 approx) =
// the shared melee lunge zz_00fed6c_ (config @0x802d3bfc).
// ----------------------------------------------------------------------------

/** Action 1 v2 — SPIN SLASH (zz_0070c7c_, phases @0x802d3c2c). pl0000 only. */
function normalSpinSlash(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = NINJA_FLOATS.AIM_TIMER; // 60.0
      actor.hSpeed = 0; actor.hDecel = 0;
      const t = actor.lockTarget;
      if (t) {
        // Reposition ×0.98 pull (FLOAT_80437710).
        actor.motion.x = (actor.pos.x - t.x) * NINJA_FLOATS.REPOS_98 - (actor.pos.x - t.x);
        actor.motion.z = (actor.pos.z - t.z) * NINJA_FLOATS.REPOS_98 - (actor.pos.z - t.z);
      }
      startStream(actor, 0xf, 3, 3); // g3 slot 3 (dash-in)
      return;
    }
    case 1: {
      tickStream(actor, 0xf, ctx);
      actor.pos.x += actor.motion.x;
      actor.pos.z += actor.motion.z;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0 || actor.lockTarget != null) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = NINJA_FLOATS.SWING_TIMER; // 30f dash
        const d = targetDist(actor);
        actor.hSpeed = Math.max(NINJA_FLOATS.RANGE, d ?? NINJA_FLOATS.RANGE) / NINJA_FLOATS.SWING_TIMER;
      }
      return;
    }
    case 2: {
      tickStream(actor, 0xf, ctx);
      actor.handlerTimer -= actor.dt;
      const d = targetDist(actor);
      if (actor.handlerTimer <= 0 || (d !== null && d <= NINJA_FLOATS.RANGE)) {
        actor.fbPhaseSlots[0] = 3;
        actor.handlerTimer = NINJA_FLOATS.SPIN_WINDOW; // 20.0
        startStream(actor, 0xf, 3, 4); // g3 slot 4 (the spin)
      }
      return;
    }
    case 3: {
      tickStream(actor, 0xf, ctx);
      if (actor.handlerTimer > 0) {
        actor.handlerTimer -= actor.dt;
        // Spin: heading += 1638.4 BAM/frame while the spin window runs.
        actor.heading = (actor.heading + Math.round(1638.4 * actor.dt)) & 0xffff;
        actor.hSpeed *= 0.9;
      } else {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 0);
        dispatchFullBodyCue(actor, 0);
      }
      return;
    }
    default:
      return;
  }
}

/** Action 1 v4 — LEAP DIVE-SLAM (6 phases @0x802d3c14). */
function normalLeap(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = NINJA_FLOATS.AIM_TIMER;
      actor.yVel = 33.333; // leap jump impulse (FLOAT dump, §A8)
      // Gravity term +0x50 = 2.0 × (−yVel/30) — FLOAT_80437728/FLOAT_80437708.
      actor.gravityCoeff = NINJA_FLOATS.LEAP_GRAV_BASE * (-actor.yVel / 30.0);
      startStream(actor, 0xf, 3, 5); // g3 slot 5 (rise)
      return;
    }
    case 1: {
      tickStream(actor, 0xf, ctx);
      integratePhysics(1.0, actor, actor.activeYaw);
      if (actor.yVel < 2.0) {
        actor.fbPhaseSlots[0] = 2;
        startStream(actor, 0xf, 3, 6); // g3 slot 6 (apex)
        actor.yVel = -30.0; // the dive
        actor.gravityCoeff = 0;
        const d = targetDist(actor);
        actor.hSpeed = d !== null ? (0.5 * d) / 30.0 : 0;
      }
      return;
    }
    case 2: {
      tickStream(actor, 0xf, ctx);
      integratePhysics(1.0, actor, actor.activeYaw);
      if (actor.grounded === true) {
        actor.fbPhaseSlots[0] = 3;
        actor.yVel = 0;
        startStream(actor, 0xf, 3, 7); // g3 slot 7 (land)
        actor.handlerTimer = 30;
      }
      return;
    }
    case 3: {
      tickStream(actor, 0xf, ctx);
      actor.hSpeed *= 0.95;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0) {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 0);
        dispatchFullBodyCue(actor, 0);
      }
      return;
    }
    default:
      return;
  }
}

/** Action 1 v1/v2 (SASUKE) — BIG-SHURIKEN TOSS (zz_0071b10_/c50_/d78, table
 *  @0x802d3c90). Ported 1:1 from chunk_0009.c:5516 + chunk_0010.c:1. */
function normalBigShurikenToss(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // zz_0071b10_: advance; range gate FUN_80066838(+0x868 row) — labeled gate on
      // lock-target presence (the +0x868 rows are runtime-populated, writer unlocated).
      actor.fbPhaseSlots[0] = 1;
      if (actor.lockTarget == null) {
        actor.activeYaw = actor.heading;
        actor.lockYaw = actor.heading;
      }
      actor.hSpeed = 0; actor.yVel = 0; actor.hDecel = 0; actor.gravityCoeff = 0;
      // Reposition ×0.95 (motion accumulator, FLOAT_80437744).
      vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
      vecScale(NINJA_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      startStream(actor, 0xf, 4, 4); // g4 slot 4
      actor.handlerTimer = NINJA_FLOATS.SPIN_WINDOW; // 20.0 (FLOAT_8043774c)
      return;
    }
    case 1: {
      // zz_0071c50_: motion ×0.95; tick (gated by +0x1b03); advance on timer/yaw.
      vecScale(NINJA_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= NINJA_FLOATS.ZERO) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = NINJA_FLOATS.SPIN_WINDOW; // 20.0
        const d = targetDist(actor);
        actor.hSpeed = Math.max(NINJA_FLOATS.RANGE, d ?? NINJA_FLOATS.RANGE) / NINJA_FLOATS.SPIN_WINDOW;
        actor.hDecel = 0;
      }
      return;
    }
    case 2: {
      // zz_0071d78_: tick; faceGate; dashStrength<0 clear; decay 0.97 (FLOAT_80437774);
      // physics; exit on contact<0 → ground return; trail gate |pos−target|>3.0.
      tickStream(actor, 0xf, ctx);
      // (faceGate +0x1d10 → zz_006d144_(0xc0): bridge pre-aims lockYaw.)
      if (actor.dashStrength1d0f < 0) {
        actor.dashStrength1d0f = 0;
        actor.hDecel = NINJA_FLOATS.ZERO;
        actor.hSpeed = NINJA_FLOATS.ZERO;
      }
      actor.hSpeed *= NINJA_FLOATS.RECOVER_DECAY; // zz_006ed8c_(0.97)
      actor.yVel *= NINJA_FLOATS.RECOVER_DECAY;
      integratePhysics(1.0, actor, actor.lockYaw); // zz_00670dc_(lockYaw)
      if (actor.contactP0 < 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romGroundIdleReturn(actor); // zz_006a474_
      }
      return;
    }
    default:
      return;
  }
}

/** Build the NORMAL NINJA root action (action 0/1 bespoke + action 2 X composed). */
function createNormalNinjaRootAction(ctx: StreamContext): (actor: RomActor) => void {
  // Action 2 (X) — COMPOSE with ninja.ts's X-special callback via the shared
  // zz_00ff2bc_ machine. Config @0x80433868: u16 groundSlot=0, airSlot=1.
  const xConfig: SharedXConfig = {
    groundSlot: 0,
    airSlot: 1,
    onHit: ninjaXOnHit,
  };
  const xSpecial = createSharedXSpecial(xConfig, ctx);
  const lunge = createSharedMeleeLunge(NINJA_LUNGE_CONFIG, ctx);

  // Action 1 borg-switched variant table (FUN_80070604):
  //   pl0000 @0x802d3bd4: [lunge, lunge, spinSlash, flyingLunge*, leap]
  //   SASUKE @0x802d3be8: [lunge, bigShuriken, bigShuriken, flyingLunge*, leap]
  const contextualB = (actor: NcActor): void => {
    const v = actor.variantIndex;
    const isSasuke = actor.borgNumber === 0x00a;
    if (v === 2) {
      if (isSasuke) normalBigShurikenToss(actor, ctx);
      else normalSpinSlash(actor, ctx);
    } else if (v === 1 && isSasuke) {
      normalBigShurikenToss(actor, ctx);
    } else if (v === 4) {
      normalLeap(actor, ctx);
    } else {
      lunge(actor); // v0/v1 (+ v3 flying-lunge approximation, zz_00710d8_ unported)
    }
  };

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: normalBCombo(actor, ctx); return;
      case 1: contextualB(actor); return;
      case 2: xSpecial(base); return;
      // actions 3/4 are command-disabled for pl0000/pl000a (descriptor +0xb8 = 0xff).
      default: return;
    }
  };
}

/** Configure NORMAL NINJA (pl0000) / SASUKE (pl000a). SUPPLANTS configureNinjaFamily. */
export function configureNormalNinjaFamily(
  actor: RomActor,
  borgId: "pl0000" | "pl000a",
  ctx: StreamContext,
): void {
  actor.borgNumber = borgId === "pl000a" ? 0x00a : 0x000;
  actor.rootAction = createNormalNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// DOUBLE NINJA (pl0003, ctor 0x8006f60c) — shares the NORMAL NINJA action 0/1
// machines (same chunk_0009.c tables 0x802d3ba4…) PLUS action 3 (X-charge dash,
// table @0x802d3c70 = [zz_0071750_, zz_0071858_, zz_0071938_]) and action 4
// (big-shuriken toss). Borg 0x003 → shuriken types 1 (+2 when +0x7c8 armed).
// ============================================================================

/** DOUBLE NINJA X-special on-hit: backflip (same scalars) + borg-0x003 shuriken.
 *  borg 0x003 → type 1, plus type 2 when the X-charge armed +0x7c8 (decode §2). */
function doubleNinjaXOnHit(actor: RomActor, ctx: StreamContext): void {
  // Backflip — identical scalars to ninja.ts ninjaXOnHit (the shared X config).
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = NINJA_X.BACKFLIP_HSPEED;
  actor.hDecel = NINJA_X.BACKFLIP_HDECEL;
  actor.yVel = NINJA_X.BACKFLIP_YVEL;
  actor.gravityCoeff = NINJA_X.BACKFLIP_GRAVITY;
  // Shuriken zz_007db5c_: borg 0x003 → type 1; +type 2 when +0x7c8 armed.
  const a = actor as NcActor;
  ctx.onFamilyProjectile?.(actor, SHURIKEN_SPAWNER_ADDR, 1);
  if ((a.shurikenArm7c8 ?? 0) !== 0) {
    ctx.onFamilyProjectile?.(actor, SHURIKEN_SPAWNER_ADDR, 2);
  }
}

/** Phase 1 — zz_0071858_: motion decay + tick + contact advance. Factored because
 *  ph0 falls through into it (the ROM calls zz_0071858_ at end of zz_0071750_). */
function doubleXChargePh1(actor: NcActor, ctx: StreamContext): void {
  // +0x7b0 ×= 0.92 (FLOAT_8043776c) — +0x7b0 is a renderer aim anchor (unported);
  // motion ×= 0.95; pos += motion; ground snap.
  vecScale(NINJA_FLOATS.REPOS_95, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    if ((actor.timer560 ?? 0) === 0) {
      actor.timer560 = NINJA_FLOATS.BACKFLIP_HSPEED; // 10.0 (FLOAT_80437748)
      // FUN_800061a8(param_1, 5) — feedback identity; TODO unsurfaced (chunk_0009.c).
    }
    actor.timer560 = (actor.timer560 ?? 0) - actor.dt;
    if ((actor.timer560 ?? 0) <= NINJA_FLOATS.ZERO) {
      actor.fbPhaseSlots[0] = 2; // → ph2
      actor.shurikenArm7c8 = 0;
    }
  }
}

/** DOUBLE NINJA action 3 — X-CHARGE DASH (table @0x802d3c70, 3 phases).
 *  Source: chunk_0009.c:5361-5487 (zz_0071750_/858/938). */
function doubleXChargeDash(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // zz_0071750_: setup + blink + stream, then fall through to ph1.
      actor.fbPhaseSlots[0] = 1;
      actor.timer560 = NINJA_FLOATS.ZERO;   // +0x560 = 0.0
      actor.handlerTimer = NINJA_FLOATS.BACKFLIP_YVEL; // +0x558 = 15.0 (FLOAT_80437768)
      actor.timer55c = NINJA_FLOATS.ZERO;   // +0x55c = 0.0
      if ((actor.shurikenArm7c8 ?? 0) === 1) actor.shurikenArm7c8 = 2;
      else {
        actor.shurikenArm7c8 = 0;
      }
      actor.gravityCoeff = NINJA_FLOATS.ZERO;
      actor.yVel = NINJA_FLOATS.ZERO;
      actor.hDecel = NINJA_FLOATS.ZERO;
      actor.hSpeed = NINJA_FLOATS.ZERO;
      actor.poseAccum80 = 0; actor.poseAccum7e = 0; actor.poseAccum7c = 0;
      // Blink: motion = (pos − targetCache5e8) ×0.95; pos += motion; ground snap.
      vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
      vecScale(NINJA_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      // Stream: slot = airborne ? 3 : 2; group 4.
      const slot = isAirborne(actor) ? 3 : 2;
      startStream(actor, 0xf, 4, slot, NINJA_FLOATS.NEG_ONE);
      doubleXChargePh1(actor, ctx);
      return;
    }
    case 1: {
      doubleXChargePh1(actor, ctx);
      return;
    }
    case 2: {
      // zz_0071938_: the charge dash (cos-ramp speed) + exit.
      vecScale(NINJA_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      if (actor.handlerTimer <= NINJA_FLOATS.ZERO) {
        actor.shurikenArm7c8 = 1;
        actor.timer55c = NINJA_FLOATS.RANGE; // 150.0
        tickStream(actor, 0xf, ctx);
        if (actor.wallContact !== 0) {
          actor.housekeeping73f = 0;
          actor.controlWord &= ~0x3;
          if (isAirborne(actor)) romAirKnockoutReturn(actor);
          else romGroundIdleReturn(actor);
        }
      } else {
        actor.handlerTimer -= actor.dt;
        if (actor.handlerTimer <= NINJA_FLOATS.ZERO) {
          actor.handlerTimer = NINJA_FLOATS.ZERO;
          // zz_004cff4_(0xf) — stream hold reset; no-op without byte-loaded banks.
        }
        actor.shurikenArm7c8 = 2;
        // +0x55c = 150.0 × cos(16384 BAM × (+0x558 / 15.0)) — the charge-speed ramp.
        const bam = Math.round(NINJA_FLOATS.XCHARGE_BAM * (actor.handlerTimer / NINJA_FLOATS.BACKFLIP_YVEL));
        actor.timer55c = NINJA_FLOATS.RANGE * Math.cos((bam & 0xffff) / 0x10000 * Math.PI * 2);
      }
      return;
    }
    default:
      return;
  }
}

/** Build the DOUBLE NINJA root action. */
function createDoubleNinjaRootAction(ctx: StreamContext): (actor: RomActor) => void {
  // Action 2 (X) — shared zz_00ff2bc_ with the DOUBLE NINJA on-hit (borg 0x003 types).
  const xConfig: SharedXConfig = {
    groundSlot: 0,
    airSlot: 1,
    onHit: doubleNinjaXOnHit,
  };
  const xSpecial = createSharedXSpecial(xConfig, ctx);
  const lunge = createSharedMeleeLunge(NINJA_LUNGE_CONFIG, ctx);

  // Action 1 — same shape as NORMAL NINJA; DOUBLE NINJA is a single borg so
  // v2 → spin slash, v4 → leap, else lunge.
  const contextualB = (actor: NcActor): void => {
    const v = actor.variantIndex;
    if (v === 2) normalSpinSlash(actor, ctx);
    else if (v === 4) normalLeap(actor, ctx);
    else lunge(actor);
  };

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: normalBCombo(actor, ctx); return;
      case 1: contextualB(actor); return;
      case 2: xSpecial(base); return;
      case 3: doubleXChargeDash(actor, ctx); return; // X-charge dash (live for pl0003)
      case 4: normalBigShurikenToss(actor, ctx); return; // B-charge big-shuriken toss
      default: return;
    }
  };
}

/** Configure DOUBLE NINJA (pl0003). UNREGISTERED → new registration. */
export function configureDoubleNinjaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = 0x003;
  actor.rootAction = createDoubleNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// SHURIKEN NINJA (pl0001, ctor 0x800ea500, chunk_0025.c) — action 0 ground combo
// (table @0x8031b0ec), action 1 lunge (ground @0x8031b178 / flying @0x8031b188),
// action 2 X barrage-dive (table @0x8031b1a8, 6 phases).
// ============================================================================

/** zz_00eb1f8_-shaped combo seed (shuriken ninja): +0x6ef=5, +0x6ed=7, +0x560=30. */
function shurikenComboSeed(actor: NcActor): void {
  if ((actor.comboStep ?? 0) === 0) actor.swingsLeft = 5;
  actor.comboStep = 0;
  actor.comboMax6ed = 7;
  actor.timer560 = SHURIKEN_FLOATS.COMBO_TIMER; // 30.0 (FLOAT_80438f84)
}

/** zz_00eb228_-shaped per-swing: +0x6ee=1, +0x6ef--, ammo gate, kunai zz_006ee14_(0). */
function shurikenSwingSpawn(actor: NcActor, ctx: StreamContext): void {
  actor.comboStep = 1;
  actor.swingsLeft = (actor.swingsLeft ?? 5) - 1;
  if (allocateWeapon(actor, ctx, 0, 1, true)) {
    ctx.onFamilyProjectile?.(actor, KUNAI_SPAWNER_ADDR, 0);
  }
}

/** Action 0 — B-tap ground combo (table @0x8031b0ec = [FUN_800ea860/8f8/98c]). */
function shurikenBCombo(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // FUN_800ea860: dual stream (part1 g2 slot +0x6ee, part2 g2 slot 9) + seed.
      actor.fbPhaseSlots[0] = 1;
      startStream(actor, 0x1, 2, actor.comboStep ?? 0, SHURIKEN_FLOATS.STREAM_RATE);
      startStream(actor, 0x2, 2, 9, SHURIKEN_FLOATS.STREAM_RATE);
      actor.controlWord &= ~0xb0; // +0x5e0 &= ~0xb0 (0xffffff4f)
      shurikenComboSeed(actor);
      actor.hDecel = SHURIKEN_FLOATS.ZERO; // +0x4c = 0.0
      actor.hSpeed = SHURIKEN_FLOATS.ZERO; // +0x44 = 0.0
      return;
    }
    case 1: {
      // FUN_800ea8f8: tick (gated by +0x1cef==0); face zz_006d0dc_(0xc1,0); advance
      // on contact; timer counts down only while facing incomplete (no target).
      if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
      if (actor.lockTarget == null) {
        actor.timer560 = (actor.timer560 ?? 0) - actor.dt;
        if (SHURIKEN_FLOATS.ZERO < (actor.timer560 ?? 0)) return;
      }
      if (actor.contactP0 !== 0) {
        actor.fbPhaseSlots[0] = 2;
        shurikenSwingSpawn(actor, ctx);
      }
      return;
    }
    case 2: {
      // FUN_800ea98c: B-held loop / air re-dispatch / exit.
      tickStream(actor, 0xf, ctx);
      if (((actor.statusWord5b4) & 0x200) !== 0) {
        // Burst/B-held: ammo check (no consume) + swings left → loop.
        if (allocateWeapon(actor, ctx, 0, 1, false) && (actor.swingsLeft ?? 0) > 0) {
          if (isAirborne(actor)) {
            // zz_006a3d0_(0,3,0) — command re-issue; bridge owns that path. Labeled
            // approximation: exit to idle (the bridge re-arms on next command).
            exitAction(actor, 0);
            return;
          }
          // zz_006bf80_(actor) — target refresh; host-owned, no-op here.
          actor.fbPhaseSlots[0] = 1; // +0x540-- (loop to ph1)
          startStream(actor, 0x1, 2, 1, SHURIKEN_FLOATS.STREAM_RATE);
          return;
        }
      } else if (
        ((actor.inputHeld5d8) & 0xf0) === 0 &&
        ((actor.inputEdge5d4) & 1) === 0 &&
        actor.wallContact === 0
      ) {
        return; // no input, no contact → stay in ph2
      }
      // Exit: ground idle return.
      actor.housekeeping73f = 0;
      actor.controlWord &= ~0x3;
      romGroundIdleReturn(actor); // zz_006a474_
      return;
    }
    default:
      return;
  }
}

// ----------------------------------------------------------------------------
// SHURIKEN NINJA action 1 — ground lunge (table @0x8031b178) + flying lunge
// (table @0x8031b188). Selected by airborne state (the bridge mirrors grounded).
// ----------------------------------------------------------------------------

/** Action 1 ground lunge — zz_00eb3f0_/500/630/738 (table @0x8031b178, 4 phases). */
function shurikenGroundLunge(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // zz_00eb3f0_: setup + blink + stream g3 slot 4.
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = SHURIKEN_FLOATS.ACTION1_TIMER; // 60.0
      if (actor.lockTarget == null) {
        actor.activeYaw = actor.heading;
        actor.lockYaw = actor.heading;
      }
      // Blink ×0.98 (FLOAT_80438f8c).
      vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
      vecScale(SHURIKEN_FLOATS.REPOS_98, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      startStream(actor, 0xf, 3, 4, SHURIKEN_FLOATS.STREAM_RATE);
      return;
    }
    case 1: {
      // zz_00eb500_: tick (gated +0x1b03); motion ×0.98; advance on timer.
      if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx);
      vecScale(SHURIKEN_FLOATS.REPOS_98, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = SHURIKEN_FLOATS.COMBO_TIMER; // 30.0 (dash frames)
        // hSpeed = max(rangeRow86c, +0x764) / 30.0.
        const floor = actor.speedScalar764 ?? 0;
        actor.hSpeed = Math.max(NINJA_FLOATS.RANGE, floor) / SHURIKEN_FLOATS.COMBO_TIMER;
        actor.yVel = 0; actor.hDecel = 0; actor.gravityCoeff = 0;
      }
      return;
    }
    case 2: {
      // zz_00eb630_: physics + advance on timer.
      if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx);
      integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.activeYaw);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO) {
        actor.fbPhaseSlots[0] = 3;
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
      }
      return;
    }
    case 3: {
      // zz_00eb738_: recover/exit. dashStrength<0 clear; decay 0.98; physics; exit.
      tickStream(actor, 0xf, ctx);
      if (actor.dashStrength1d0f < 0) {
        actor.dashStrength1d0f = 0;
        if (SHURIKEN_FLOATS.ZERO < actor.yVel) actor.yVel = SHURIKEN_FLOATS.ZERO;
      }
      actor.hSpeed *= SHURIKEN_FLOATS.REPOS_98; // zz_006ed8c_(0.98)
      actor.yVel *= SHURIKEN_FLOATS.REPOS_98;
      integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.activeYaw);
      if (actor.contactP0 < 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
        actor.stateTimer = SHURIKEN_FLOATS.GRAVITY + actor.dt; // 1.0 + dt
      } else if (actor.wallContact !== 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor); // zz_006a5a4_
      }
      return;
    }
    default:
      return;
  }
}

/** Phase 1 — zz_00eb9b8_: yVel aim + physics + advance on timer/range gate. */
function shurikenFlyingLungePh1(actor: NcActor, ctx: StreamContext): void {
  // yVel = (part aim anchor 8f0 − aimOrigin.z) / 12.0 — renderer anchors; the
  // bridge surfaces target Y via lockTarget. Approximation: target Y delta / 12.
  const t = actor.lockTarget;
  if (t) {
    const dy = t.y - actor.pos.y;
    actor.yVel = Math.max(SHURIKEN_FLOATS.YVEL_MIN, Math.min(SHURIKEN_FLOATS.COMBO_TIMER, dy)) / SHURIKEN_FLOATS.YVEL_DIV;
  }
  integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.activeYaw);
  if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.dt;
  const d = targetDist(actor);
  if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO || (d !== null && d <= SHURIKEN_FLOATS.RANGE_150)) {
    actor.fbPhaseSlots[0] = 2;
  }
}

/** Action 1 flying lunge — zz_00eb88c_/9b8/ab4 (table @0x8031b188, 3 phases). */
function shurikenFlyingLunge(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // zz_00eb88c_: dash setup + stream g3 slot 5, then fall through to ph1.
      actor.fbPhaseSlots[0] = 1;
      if (actor.lockTarget == null) {
        actor.lockYaw = actor.heading;
        actor.activeYaw = actor.heading;
      }
      const floor = actor.speedScalar764 ?? 0;
      actor.hSpeed = Math.max(NINJA_FLOATS.RANGE, floor) / SHURIKEN_FLOATS.DASH_FRAMES_20; // /20
      actor.hDecel = 0; actor.yVel = 0; actor.gravityCoeff = 0;
      actor.handlerTimer = SHURIKEN_FLOATS.DASH_FRAMES_20; // 20.0
      startStream(actor, 0xf, 3, 5, SHURIKEN_FLOATS.STREAM_RATE);
      shurikenFlyingLungePh1(actor, ctx);
      return;
    }
    case 1: {
      shurikenFlyingLungePh1(actor, ctx);
      return;
    }
    case 2: {
      // zz_00ebab4_: recover/exit. decay 0.95 (FLOAT_80438fa4); physics; exit.
      tickStream(actor, 0xf, ctx);
      if (actor.dashStrength1d0f < 0) {
        actor.dashStrength1d0f = 0;
        if (SHURIKEN_FLOATS.ZERO < actor.yVel) actor.yVel = SHURIKEN_FLOATS.ZERO;
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
      }
      actor.hSpeed *= SHURIKEN_FLOATS.REPOS_95; // zz_006ed8c_(0.95)
      actor.yVel *= SHURIKEN_FLOATS.REPOS_95;
      integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.activeYaw);
      if (actor.contactP0 < 0) {
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 7);
        actor.stateTimer = SHURIKEN_FLOATS.GRAVITY + actor.dt;
      } else if (actor.wallContact !== 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor);
      }
      return;
    }
    default:
      return;
  }
}

// ----------------------------------------------------------------------------
// SHURIKEN NINJA action 2 — X-SPECIAL barrage dive (table @0x8031b1a8 =
// [zz_00ebc5c_, zz_00ebd74_, zz_00ebe18_, zz_00ebee0_, zz_00ec02c_, zz_00ec160_],
// 6 phases). Driver zz_00ebbd0_ → zz_00ebc0c_ → PTR_zz_00ebc5c__8031b1a8[+0x540].
// ----------------------------------------------------------------------------

function shurikenXBarrage(actor: NcActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      // zz_00ebc5c_: setup + blink ×0.95 + stream g4 slot (+0x6ea++).
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = SHURIKEN_FLOATS.ACTION1_TIMER; // 60.0 (FLOAT_80438f88)
      actor.streamSlot = 0;
      if (actor.lockTarget == null) {
        actor.activeYaw = actor.heading;
      }
      vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
      vecScale(SHURIKEN_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      const slot = actor.streamSlot;
      actor.streamSlot = slot + 1;
      startStream(actor, 0xf, 4, slot, SHURIKEN_FLOATS.STREAM_RATE);
      actor.accumulator80c = 0;
      return;
    }
    case 1: {
      // zz_00ebd74_: tick (gated +0x1b03); motion ×0.95; advance on timer.
      if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx);
      vecScale(SHURIKEN_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO) {
        actor.fbPhaseSlots[0] = 2;
      }
      return;
    }
    case 2: {
      // zz_00ebe18_: on contact (+0x1cef) seed the dive: +0x558=45, motion=(0,40,2).
      vecScale(SHURIKEN_FLOATS.REPOS_95, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
      tickStream(actor, 0xf, ctx);
      if (actor.contactP0 !== 0) {
        actor.fbPhaseSlots[0] = 3;
        actor.handlerTimer = SHURIKEN_FLOATS.X_PH2_TIMER; // 45.0
        actor.motion.x = SHURIKEN_FLOATS.ZERO;
        actor.motion.y = SHURIKEN_FLOATS.X_PH2_MY; // 40.0
        actor.motion.z = SHURIKEN_FLOATS.X_PH2_MZ; // 2.0
        actor.hDecel = SHURIKEN_FLOATS.ZERO;
        actor.gravityCoeff = SHURIKEN_FLOATS.ZERO;
        // zz_00b2190_(0) afterimage when +0x760 > 250.0 — FX helper, host-side.
      }
      return;
    }
    case 3: {
      // zz_00ebee0_: steer-dive integration. motion.x += motion.z×dt (capped at
      // motion.y); hSpeed = motion.x × cos(steerYaw); yVel = −motion.x × sin(steerYaw).
      actor.motion.x = actor.motion.x + actor.motion.z * actor.dt;
      if (actor.motion.y < actor.motion.x) actor.motion.x = actor.motion.y;
      actor.hSpeed = actor.motion.x * Math.cos((actor.steerYaw & 0xffff) / 0x10000 * Math.PI * 2);
      actor.yVel = -actor.motion.x * Math.sin((actor.steerYaw & 0xffff) / 0x10000 * Math.PI * 2);
      integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.lockYaw);
      tickStream(actor, 0xf, ctx);
      // zz_00f0104_(3,2) — per-frame FX/sound; TODO unsurfaced (chunk_0025.c:2957).
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO) {
        actor.fbPhaseSlots[0] = 4;
        actor.handlerTimer = SHURIKEN_FLOATS.X_PH3_TIMER; // 120.0
        if (SHURIKEN_FLOATS.ZERO < actor.yVel) actor.yVel = SHURIKEN_FLOATS.ZERO;
        actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
        const slot = actor.streamSlot;
        actor.streamSlot = slot + 1;
        startStream(actor, 0xf, 4, slot, SHURIKEN_FLOATS.STREAM_RATE);
      }
      return;
    }
    case 4: {
      // zz_00ec02c_: ground approach + grounded contact → ph5; timer-out → air exit.
      tickStream(actor, 0xf, ctx);
      integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.lockYaw);
      actor.handlerTimer -= actor.dt;
      if (SHURIKEN_FLOATS.ZERO < actor.handlerTimer) {
        if (actor.grounded === true || actor.wallContact !== 0) {
          actor.fbPhaseSlots[0] = 5;
          actor.handlerTimer = SHURIKEN_FLOATS.RANGE_50; // 50.0 (FLOAT_80438f90)
          actor.steerYaw = 0;
          // g4 slot 4 re-arm (group 0x82 = shared-bank group 2); zz_0066530_(0x2c)
          // + zz_00b2190_(2) — TODO unsurfaced FX/cue (chunk_0025.c:3008-3010).
          startStream(actor, 0xf, 0x82, 4, SHURIKEN_FLOATS.STREAM_RATE);
        }
      } else {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romAirKnockoutReturn(actor); // zz_006a5a4_
      }
      return;
    }
    case 5: {
      // zz_00ec160_: recover. decay 0.95; physics; exit on contact → ground return.
      if (actor.handlerTimer <= SHURIKEN_FLOATS.ZERO) {
        tickStream(actor, 0xf, ctx);
      } else {
        actor.handlerTimer -= actor.dt;
        actor.hSpeed *= SHURIKEN_FLOATS.REPOS_95; // zz_006ed8c_(0.95)
        actor.yVel *= SHURIKEN_FLOATS.REPOS_95;
        integratePhysics(SHURIKEN_FLOATS.GRAVITY, actor, actor.lockYaw);
      }
      if (actor.wallContact !== 0) {
        actor.housekeeping73f = 0;
        actor.controlWord &= ~0x3;
        romGroundIdleReturn(actor); // zz_006a474_
      }
      return;
    }
    default:
      return;
  }
}

/** Build the SHURIKEN NINJA root action. */
function createShurikenNinjaRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: shurikenBCombo(actor, ctx); return;
      case 1:
        // Ground lunge when grounded, flying lunge when airborne (situation switch).
        if (isAirborne(actor)) shurikenFlyingLunge(actor, ctx);
        else shurikenGroundLunge(actor, ctx);
        return;
      case 2: shurikenXBarrage(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure SHURIKEN NINJA (pl0001). UNREGISTERED → new registration. */
export function configureShurikenNinjaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = 0x001;
  actor.rootAction = createShurikenNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests. Mirror the rom.selfcheck.ts / victory-king.ts style.
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
    ctx.onFamilyProjectile = (_actor, addr, type) => sink(addr, type);
  }
  return ctx;
}

export function runNinjaClusterSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // ==========================================================================
  // NORMAL NINJA — action 0 B-combo + action 1 + X compose.
  // ==========================================================================

  // --- action 0 ph0: stamps borgNumber, seeds 5 swings, zeroes scalars. ---
  for (const { id, num } of [
    { id: "pl0000" as const, num: 0x000 },
    { id: "pl000a" as const, num: 0x00a },
  ]) {
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, id, makeCtx());
    assert(a.borgNumber === num, `NORMAL ${id} borgNumber stamped 0x${num.toString(16)}`);
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, `NORMAL ${id} action0 ph0 → ph1`);
    assert(a.swingsLeft === 5, `NORMAL ${id} action0 seeds 5 swings (zz_0070530_)`);
    assert(a.hSpeed === 0 && a.hDecel === 0, `NORMAL ${id} action0 ph0 zeroes hSpeed/hDecel`);
  }

  // --- action 0 ph1 contact → ph2 kunai spawn (borg-switched variant). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, "pl0000", makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP0 = 1;
    root(a); // ph1 contact → ph2
    assert(a.fbPhaseSlots[0] === 2, "NORMAL action0 ph1 contact → ph2");
    assert(
      shots.length === 1 && shots[0]!.addr === KUNAI_SPAWNER_ADDR && shots[0]!.type === 0,
      `NORMAL pl0000 kunai variant 0 (got ${JSON.stringify(shots)})`,
    );
  }
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, "pl000a", makeCtx({
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP0 = 1;
    root(a);
    assert(
      shots.length === 1 && shots[0]!.type === 4,
      "NORMAL SASUKE kunai variant 4 (speed 85)",
    );
  }

  // --- action 0 ph2 B-held loop → back to ph1; release → exit. ---
  {
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, "pl0000", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 2; a.bHeld = true; a.swingsLeft = 3;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "NORMAL action0 ph2 B-held → loop to ph1 (slot-1 restart)");
    // Release B → drain timer → exit.
    a.bHeld = false; a.fbPhaseSlots[0] = 2; a.handlerTimer = 0.5;
    root(a); root(a);
    assert((a.controlWord & 0x3) === 0, "NORMAL action0 ph2 release → exit (ground idle return)");
  }

  // --- action 1 v0 → shared lunge ph0 (streamSlot = slotBase+1). ---
  {
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, "pl0000", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "NORMAL action1 v0 → shared lunge ph0 (aim)");
    assert(a.streamSlot === NINJA_LUNGE_CONFIG.slotBase + 1, "NORMAL action1 lunge stream cursor = slotBase+1");
  }

  // --- action 2 X compose: phase-0 blink + on-contact backflip (SASUKE shuriken 3). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureNormalNinjaFamily(a, "pl000a", makeCtx({
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    // The shared zz_00ff2bc_ machine blinks against lockTarget (the host lock ptr),
    // not targetCache5e8 — set it so the reposition runs.
    a.lockTarget = { x: 0, y: 0, z: 0 };
    root(a); // X ph0
    assert(a.fbPhaseSlots[0] === 1, "NORMAL action2 X ph0 → ph1 (composed shared machine)");
    assert(a.pos.x === 195, "NORMAL X ph0 blink: pos.x = 195 ((100−0)×0.95)");
    // ph1 contact → on-hit backflip + shuriken type 3.
    a.contactP0 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "NORMAL X ph1 contact → ph2");
    assert(a.hSpeed === NINJA_X.BACKFLIP_HSPEED && a.yVel === NINJA_X.BACKFLIP_YVEL,
      "NORMAL X on-hit backflip scalars (ninjaXOnHit composed)");
    assert(
      shots.length === 1 && shots[0]!.addr === SHURIKEN_SPAWNER_ADDR && shots[0]!.type === 3,
      `NORMAL SASUKE X on-hit shuriken type 3 (got ${JSON.stringify(shots)})`,
    );
  }

  // ==========================================================================
  // DOUBLE NINJA — action 3 X-charge dash + X on-hit shuriken types 1/+2.
  // ==========================================================================

  // --- action 3 ph0 setup: blink + stream group 4 slot 2 (ground). ---
  {
    const a = createRomActor() as NcActor;
    configureDoubleNinjaFamily(a, makeCtx());
    assert(a.borgNumber === 0x003, "DOUBLE pl0003 borgNumber stamped 0x003");
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0 (falls through to ph1 — ROM zz_0071750_ calls zz_0071858_ at end)
    assert(a.handlerTimer === NINJA_FLOATS.BACKFLIP_YVEL, "DOUBLE action3 ph0 +0x558 = 15.0 (FLOAT_80437768)");
    // ph0 blink (pos += (pos−target)×0.95 → 195) THEN ph1 drift (motion ×= 0.95; pos
    // += motion → ~285.25) both run this frame (the ROM fall-through). Assert the
    // combined result to confirm the blink seeded motion and ph1 continued it.
    assert(a.pos.x > 285 && a.pos.x < 286, `DOUBLE action3 ph0 blink+ph1 drift: pos.x ≈ 285 (got ${a.pos.x})`);
    assert(a.hSpeed === 0 && a.gravityCoeff === 0, "DOUBLE action3 ph0 zeroes scalars (FLOAT_804376e4)");
  }

  // --- action 3 ph1 contact → ph2 (timer560 counts down then advances). ---
  {
    const a = createRomActor() as NcActor;
    configureDoubleNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1; a.fbPhaseSlots[0] = 1; a.wallContact = 1;
    a.timer560 = 0; // contact with timer560==0 → seed 10.0
    root(a);
    // ROM seeds 10.0 AND decrements by dt in the SAME frame (zz_0071858_:5422-5427).
    assert(
      a.timer560 === NINJA_FLOATS.BACKFLIP_HSPEED - a.dt,
      `DOUBLE action3 ph1 contact seeds +0x560 = 10.0 then −dt (got ${a.timer560})`,
    );
    // Drain timer560 → advance to ph2. Single frame: timer560 0.5 → −0.5 ≤ 0 → ph2,
    // and ph1 sets +0x7c8 = 0 on the advance (assert before the next ph2 frame
    // overwrites +0x7c8 with 2).
    a.timer560 = 0.5;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "DOUBLE action3 ph1 timer560 ≤ 0 → ph2");
    assert((a.shurikenArm7c8 ?? 0) === 0, "DOUBLE action3 ph1→ph2 clears +0x7c8");
  }

  // --- action 2 X on-hit (DOUBLE): shuriken type 1, +type 2 when +0x7c8 armed. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureDoubleNinjaFamily(a, makeCtx({
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); a.contactP0 = 1; root(a); // ph0 → ph1 contact → on-hit
    assert(
      shots.length === 1 && shots[0]!.addr === SHURIKEN_SPAWNER_ADDR && shots[0]!.type === 1,
      `DOUBLE X on-hit shuriken type 1 (got ${JSON.stringify(shots)})`,
    );
    // With +0x7c8 armed → +type 2.
    shots.length = 0;
    const b = createRomActor() as NcActor;
    configureDoubleNinjaFamily(b, makeCtx({
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const rb = b.rootAction!;
    b.actionIndex = 2; b.dt = 1; b.shurikenArm7c8 = 2;
    b.pos = { x: 100, y: 0, z: 0 }; b.targetCache5e8 = { x: 0, y: 0, z: 0 };
    rb(b); b.contactP0 = 1; rb(b);
    assert(
      shots.length === 2 && shots.some((s) => s.type === 1) && shots.some((s) => s.type === 2),
      `DOUBLE X on-hit +0x7c8 armed → types 1+2 (got ${JSON.stringify(shots)})`,
    );
  }

  // --- action 4 big-shuriken toss ph0 → ph1 (timer seed). ---
  {
    const a = createRomActor() as NcActor;
    configureDoubleNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 4; a.dt = 1;
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "DOUBLE action4 big-shuriken ph0 → ph1");
    assert(a.handlerTimer === NINJA_FLOATS.SPIN_WINDOW, "DOUBLE action4 ph0 +0x558 = 20.0 (FLOAT_8043774c)");
  }

  // ==========================================================================
  // SHURIKEN NINJA — action 0 combo + action 2 X barrage.
  // ==========================================================================

  // --- action 0 ph0: dual stream + combo seed (5 swings, +0x6ed=7, +0x560=30). ---
  {
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx());
    assert(a.borgNumber === 0x001, "SHURIKEN pl0001 borgNumber stamped 0x001");
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "SHURIKEN action0 ph0 → ph1");
    assert(a.swingsLeft === 5, "SHURIKEN action0 seeds 5 swings (zz_00eb1f8_)");
    assert(a.comboMax6ed === 7, "SHURIKEN action0 +0x6ed = 7 (zz_00eb1f8_)");
    assert(a.timer560 === SHURIKEN_FLOATS.COMBO_TIMER, "SHURIKEN action0 +0x560 = 30.0 (FLOAT_80438f84)");
  }

  // --- action 0 ph1 contact → ph2 kunai spawn (ammo-gate). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP0 = 1;
    root(a); // ph1 contact → ph2 + swing spawn
    assert(a.fbPhaseSlots[0] === 2, "SHURIKEN action0 ph1 contact → ph2");
    assert(
      shots.length === 1 && shots[0]!.addr === KUNAI_SPAWNER_ADDR && shots[0]!.type === 0,
      `SHURIKEN action0 kunai zz_006ee14_(0) on ammo-ok (got ${JSON.stringify(shots)})`,
    );
    assert(a.swingsLeft === 4, "SHURIKEN action0 swings decremented");
  }

  // --- action 0 ph1 contact DENIED (ammo gate fails) → no kunai. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 1; a.contactP0 = 1;
    root(a);
    assert(shots.length === 0, "SHURIKEN action0 ammo-denied → no kunai spawn (zz_006dbe0_ gate)");
  }

  // --- action 0 ph2 B-held loop → ph1 (slot-1 restart); swings gate. ---
  {
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1; a.fbPhaseSlots[0] = 2;
    a.statusWord5b4 = 0x200; a.swingsLeft = 3; // B-held burst + swings left
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "SHURIKEN action0 ph2 B-held + swings → loop to ph1 (slot-1 restart)");
  }

  // --- action 2 X ph0 → ph1 → ph2 contact advance. ---
  {
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "SHURIKEN action2 X ph0 → ph1");
    assert(a.handlerTimer === SHURIKEN_FLOATS.ACTION1_TIMER, "SHURIKEN X ph0 +0x558 = 60.0 (FLOAT_80438f88)");
    assert(a.pos.x === 195, "SHURIKEN X ph0 blink: pos.x = 195 ((100−0)×0.95, FLOAT_80438fa4)");
    // ph1 timer-out → ph2.
    a.handlerTimer = 0; a.streamHold1b03 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "SHURIKEN X ph1 timer ≤ 0 → ph2");
    // ph2 contact → ph3 dive seed.
    a.contactP0 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "SHURIKEN X ph2 contact → ph3 (dive seed)");
    assert(a.handlerTimer === SHURIKEN_FLOATS.X_PH2_TIMER, "SHURIKEN X ph2 +0x558 = 45.0 (FLOAT_80438fa8)");
    assert(a.motion.y === SHURIKEN_FLOATS.X_PH2_MY && a.motion.z === SHURIKEN_FLOATS.X_PH2_MZ,
      "SHURIKEN X ph2 dive motion = (0, 40, 2) (FLOAT_80438fac/fb0)");
  }

  // --- rootAction no-ops for unsupported actionIndex. ---
  {
    const a = createRomActor() as NcActor;
    configureShurikenNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 9; a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "SHURIKEN unsupported actionIndex falls through (no-op)");
  }
}
