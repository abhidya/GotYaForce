// NORMAL NINJA family (ctor 0x8006f4f8) — the second ROM-faithful family port.
// Covers pl0000 (NORMAL NINJA) and pl000a (SASUKE): the ctor gives both the SAME
// vtable/anim banks/tables and differs ONLY in the +0x4b0 descriptor (0x802d3dc8 vs
// 0x802d3ee0), so one family module covers both. Source:
// research/decomp/nn-family-decode-2026-07-06.md (adversarially verified, 14/16 claims
// dual-confirmed + 2 constant corrections applied here from the verify pass).
//
// Root dispatcher FUN_8006facc @0x8006facc:
//   `(*(code *)(&PTR_FUN_802d3b68)[*(char *)(actor+0x580)])();`
// Action table PTR_FUN_802d3b68 @0x802d3b68 (5 entries):
//   [0] 0x8006fb08  B-tap ground/dash/air sword-combo driver   — TODO port
//   [1] 0x80070604  contextual-B lunge driver (borg-switched)  — TODO port
//   [2] 0x80071598  X-special driver                           — PORTED here
//   [3] 0x800716d8  X-charge dash — DEAD for pl0000/pl000a (descriptor +0xb8 modes
//       `01 00 01 ff ff ff`: command types 3/4/5 disabled; live only for pl0003)
//   [4] 0x80071a84  B-charge shuriken toss — DEAD for pl0000/pl000a (same gate; its
//       zz_0071ac0_ machine is reachable for SASUKE via action-1 variants 1/2)
//
// The X-special (actionIndex 2) delegates ALL 5 variants to the SHARED engine machine
// zz_00ff2bc_ (families/shared-x-special.ts) with the family config block @0x80433868:
// {ground slot 0, air slot 1, on-hit callback zz_00715f8_}. The callback is the ninja
// signature move: on connect, BACKFLIP away and throw a shuriken.

import type { RomActor } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";
import { createSharedMeleeLunge, NINJA_LUNGE_CONFIG } from "./shared-melee-lunge.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

/** zz_00715f8_ @0x800715f8 constants — every value read from boot.dol. */
export const NINJA_X = {
  BACKFLIP_HSPEED: 10.0,  // FLOAT_80437748 → +0x44
  BACKFLIP_YVEL: 15.0,    // FLOAT_80437768 → +0x48 (vertical impulse)
  BACKFLIP_HDECEL: 0.0,   // FLOAT_804376e4 → +0x4c
  BACKFLIP_GRAVITY: -1.0, // FLOAT_804376e0 → +0x50 (gravity accel — NEGATIVE coefficient)
  /** Shuriken spawner zz_007db5c_ @0x8007db5c record-select by borgNumber (+0x3e8):
   *  borg 0x000 → type 0; borg 0x00a (SASUKE) → type 3. (DOUBLE NINJA borg 0x003 →
   *  types 1+2, not covered by this module's registration.) Table 0x802d6d68. */
  SHURIKEN_SPAWNER_ADDR: 0x8007db5c,
} as const;

/** Ground/air stream slots from the family X config block @0x80433868 (u16[0]/u16[1]). */
const NINJA_X_GROUND_SLOT = 0;
const NINJA_X_AIR_SLOT = 1;

function shurikenTypeFor(borgNumber: number): number {
  return borgNumber === 0x00a ? 3 : 0;
}

/**
 * The family on-hit callback zz_00715f8_ @0x800715f8 (cfg ptr[+4]), invoked by the
 * shared machine's phase-1 contact transition:
 *  (a) BACKFLIP — on the stream-event flag +0x1d0f: face away 180° (+0x5ae = +0x72 −
 *      0x8000) and set the launch scalars. Our decoded stream events don't surface
 *      +0x1d0f, so the backflip applies unconditionally on hit (the flag is armed by
 *      the same streams that arm the hit — labeled approximation).
 *  (b) SHURIKEN — ammo-gated (zz_006dbe0_ slot 2, cost 1; ammo is owned by BorgRuntime,
 *      surfaced through the host hook) spawn via zz_007db5c_(actor, typeByBorg).
 */
export function ninjaXOnHit(actor: RomActor, ctx: StreamContext): void {
  // (a) Backflip: +0x5ae = +0x72 − 0x8000 (face directly away), then the four scalars.
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = NINJA_X.BACKFLIP_HSPEED;
  actor.hDecel = NINJA_X.BACKFLIP_HDECEL;
  actor.yVel = NINJA_X.BACKFLIP_YVEL;
  actor.gravityCoeff = NINJA_X.BACKFLIP_GRAVITY;
  // (b) Shuriken. The host resolves the family table (0x802d6d68) + ammo gate; when the
  // hook is unwired this is an honest no-op (the melee contact is the ported payload).
  ctx.onFamilyProjectile?.(actor, NINJA_X.SHURIKEN_SPAWNER_ADDR, shurikenTypeFor(actor.borgNumber));
}

export interface NinjaFamilyCtx extends StreamContext {}

/** Kunai spawner zz_006ee14_ @0x8006ee14 (table 0x802d39b0) — per-swing throw in the
 *  B-combo. Variant by borgNumber: SASUKE → 4 (speed 85), else 0 (speed 60). */
const KUNAI_SPAWNER_ADDR = 0x8006ee14;
function kunaiVariantFor(borgNumber: number): number {
  return borgNumber === 0x00a ? 4 : 0;
}

/** Host-set per-frame input scratch (the bridge mirrors the virtual-pad reads the ROM
 *  machines poll: +0x5b4 & 0x200 B-held, +0x5d4 & 0x40 B-retap edge). */
interface NinjaScratch {
  bHeld?: boolean;
  bRetapInput?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  /** +0x6ee/+0x6ef combo cursor + swings-left (zz_0070530_/zz_0070558_). */
  comboStep?: number;
  swingsLeft?: number;
}

function targetDist(actor: RomActor): number | null {
  const t = (actor as RomActor & NinjaScratch).lockTarget;
  if (!t) return null;
  return Math.hypot(t.x - actor.pos.x, t.z - actor.pos.z);
}

// ============================================================================
// Action 0 — B-tap ground combo, machine A (FUN_8006fb44, variants 0/5).
// Phases @0x802d3ba4 = [0x8006fb8c, 0x8006fc24, 0x8006fcb8].
// Constants: swing timer 30.0 (FLOAT_80437708), 5 swings (+0x6ef seed), overlay
// stream part-2 g2 slot 9, combo-loop restart slot 1. nn-family-decode §A7 (verify-
// corrected: P1 faces with mask 0xC1, not 0x81).
// ============================================================================
const NINJA_BCOMBO = {
  SWING_TIMER: 30.0, // FLOAT_80437708
  SWINGS: 5,         // zz_0070530_: +0x6ef = 5 when +0x6ee == 0
  OVERLAY_SLOT: 9,   // P0 second stream: part mask 2, group 2, slot 9
  LOOP_SLOT: 1,      // P2 B-held ground restart: group 2 slot 1
} as const;

function ninjaBComboPhase0(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & NinjaScratch;
  actor.fbPhaseSlots[0] = 1;
  // zz_0070530_ combo seed: fresh chain → 5 swings, cursor 0; swing timer 30.
  if (!s.comboStep) {
    s.comboStep = 0;
    s.swingsLeft = NINJA_BCOMBO.SWINGS;
  }
  actor.handlerTimer = NINJA_BCOMBO.SWING_TIMER; // +0x560 = 30.0
  actor.hSpeed = 0; // zero +0x44/+0x4c
  actor.hDecel = 0;
  actor.controlWord &= ~0xb0; // P0 clears +0x5e0 bits 0xb0
  // Dual stream: part 1 = g2 slot (+0x6ee combo step), part 2 = g2 slot 9 overlay.
  startStream(actor, 0x1, 2, s.comboStep ?? 0);
  startStream(actor, 0x2, 2, NINJA_BCOMBO.OVERLAY_SLOT);
  void ctx;
}

function ninjaBComboPhase1(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & NinjaScratch;
  // ROM: tick stream only while +0x1cef == 0; face zz_006d0dc_(0xc1,0); timer counts
  // down only while facing incomplete (bridge pre-aims → counts on no-target only).
  if (actor.contactP0 === 0) tickStream(actor, 0x1, ctx);
  if (!s.lockTarget) actor.handlerTimer -= actor.dt;
  if (actor.contactP0 > 0 || actor.handlerTimer <= -NINJA_BCOMBO.SWING_TIMER) {
    // zz_0070558_ swing bookkeeping: cursor → 1, swings--, ammo(slot 0, cost 1),
    // kunai throw (zz_006ee14_ variant by borg).
    actor.fbPhaseSlots[0] = 2;
    s.comboStep = (s.comboStep ?? 0) + 1;
    s.swingsLeft = (s.swingsLeft ?? NINJA_BCOMBO.SWINGS) - 1;
    ctx.onFamilyProjectile?.(actor, KUNAI_SPAWNER_ADDR, kunaiVariantFor(actor.borgNumber));
  }
}

function ninjaBComboPhase2(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & NinjaScratch;
  tickStream(actor, 0x1, ctx);
  const swingsLeft = s.swingsLeft ?? 0;
  if (s.bHeld && swingsLeft > 0) {
    // Ground: loop — restart part-1 stream at g2 slot 1, back to phase 1.
    // (Airborne re-dispatches via zz_006a3d0_(0,3,0) — command re-issue; the bridge's
    // command layer owns that path, so the port loops in place for both.)
    actor.fbPhaseSlots[0] = 1;
    startStream(actor, 0x1, 2, NINJA_BCOMBO.LOOP_SLOT);
    actor.handlerTimer = NINJA_BCOMBO.SWING_TIMER;
    actor.contactP0 = 0;
    return;
  }
  // Stream end / no follow-up → ground idle reset (zz_006a474_).
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= 0) {
    s.comboStep = 0;
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor); // zz_006a474_ (decomp-verified, shared-idle-return.ts)
  }
}

function ninjaBCombo(actor: RomActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: ninjaBComboPhase0(actor, ctx); break;
    case 1: ninjaBComboPhase1(actor, ctx); break;
    case 2: ninjaBComboPhase2(actor, ctx); break;
    default: break;
  }
}

// ============================================================================
// Action 1 v2 — pl0000 SPIN SLASH (zz_0070c7c_, phases @0x802d3c2c).
// Constants (§A8): aim 60.0 (FLOAT_8043770c), reposition ×0.98 (FLOAT_80437710),
// dash 30f (FLOAT_80437708), spin window 20.0 (FLOAT_8043774c), spin rate 1638.4
// BAM/frame, decay 0.9, in-range 150.0 (FLOAT_804376f8); streams g3 s3 (dash-in),
// g3 s4 (the spin).
// ============================================================================
const NINJA_SPIN = {
  AIM: 60.0, REPOS: 0.98, DASH_FRAMES: 30.0, SPIN_WINDOW: 20.0,
  SPIN_RATE_BAM: 1638.4, DECAY: 0.9, RANGE: 150.0,
  DASH_SLOT: 3, SPIN_SLOT: 4,
} as const;

function ninjaSpinSlash(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & NinjaScratch;
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = NINJA_SPIN.AIM;
      actor.hSpeed = 0; actor.hDecel = 0;
      // Reposition ×0.98 pull (same motion-accumulator shape as shared-X's 0.95).
      const t = s.lockTarget;
      if (t) {
        actor.motion.x = (actor.pos.x - t.x) * NINJA_SPIN.REPOS - (actor.pos.x - t.x);
        actor.motion.z = (actor.pos.z - t.z) * NINJA_SPIN.REPOS - (actor.pos.z - t.z);
      }
      startStream(actor, 0xf, 3, NINJA_SPIN.DASH_SLOT);
      break;
    }
    case 1: {
      tickStream(actor, 0xf, ctx);
      actor.pos.x += actor.motion.x;
      actor.pos.z += actor.motion.z;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0 || s.lockTarget) {
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = NINJA_SPIN.DASH_FRAMES;
        const d = targetDist(actor);
        actor.hSpeed = Math.max(NINJA_SPIN.RANGE, d ?? NINJA_SPIN.RANGE) / NINJA_SPIN.DASH_FRAMES;
      }
      break;
    }
    case 2: {
      tickStream(actor, 0xf, ctx);
      actor.handlerTimer -= actor.dt;
      const d = targetDist(actor);
      if (actor.handlerTimer <= 0 || (d !== null && d <= NINJA_SPIN.RANGE)) {
        actor.fbPhaseSlots[0] = 3;
        actor.handlerTimer = NINJA_SPIN.SPIN_WINDOW;
        startStream(actor, 0xf, 3, NINJA_SPIN.SPIN_SLOT);
      }
      break;
    }
    case 3: {
      tickStream(actor, 0xf, ctx);
      if (actor.handlerTimer > 0) {
        actor.handlerTimer -= actor.dt;
        // The spin: heading += 1638.4 BAM per frame while the spin window runs.
        actor.heading = (actor.heading + Math.round(NINJA_SPIN.SPIN_RATE_BAM * actor.dt)) & 0xffff;
        actor.hSpeed *= NINJA_SPIN.DECAY;
      } else {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 0);
        dispatchFullBodyCue(actor, 0);
      }
      break;
    }
    default: break;
  }
}

// ============================================================================
// Action 1 v4 — LEAP DIVE-SLAM (6 phases @0x802d3c14). Compact port of the §A8
// transcription with the verify-pass corrections: jump 33.333 u/f (or dy/30 + Y-aim
// 1000×scale), apex gate yVel < 2.0 → slot 6, dive −30.0 u/f, gravity term
// +0x50 = 2.0 × (−yVel/30) [FLOAT_80437728/FLOAT_80437708 — NOT 200.0], landing
// 150-gate + 0.95 decay + slot 7.
// ============================================================================
const NINJA_LEAP = {
  AIM: 60.0, JUMP: 33.333, APEX_YVEL: 2.0, DIVE: -30.0, RANGE: 150.0, DECAY: 0.95,
  RISE_SLOT: 5, APEX_SLOT: 6, LAND_SLOT: 7,
} as const;

function ninjaLeap(actor: RomActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = NINJA_LEAP.AIM;
      actor.yVel = NINJA_LEAP.JUMP;
      // Gravity: +0x50 = 2.0 × (−yVel/30) — the corrected §A8 term.
      actor.gravityCoeff = 2.0 * (-actor.yVel / 30.0);
      startStream(actor, 0xf, 3, NINJA_LEAP.RISE_SLOT);
      break;
    }
    case 1: {
      tickStream(actor, 0xf, ctx);
      integratePhysics(1.0, actor, actor.activeYaw);
      if (actor.yVel < NINJA_LEAP.APEX_YVEL) {
        actor.fbPhaseSlots[0] = 2;
        startStream(actor, 0xf, 3, NINJA_LEAP.APEX_SLOT);
        actor.yVel = NINJA_LEAP.DIVE; // the dive
        actor.gravityCoeff = 0;
        // Dive XZ: 0.5 × dist / 30 toward the target.
        const d = targetDist(actor);
        actor.hSpeed = d !== null ? (0.5 * d) / 30.0 : 0;
      }
      break;
    }
    case 2: {
      tickStream(actor, 0xf, ctx);
      integratePhysics(1.0, actor, actor.activeYaw);
      const grounded = (actor as RomActor & NinjaScratch).grounded === true;
      if (grounded) {
        actor.fbPhaseSlots[0] = 3;
        actor.yVel = 0;
        startStream(actor, 0xf, 3, NINJA_LEAP.LAND_SLOT);
        actor.handlerTimer = 30;
      }
      break;
    }
    case 3: {
      tickStream(actor, 0xf, ctx);
      actor.hSpeed *= NINJA_LEAP.DECAY;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0) {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 0);
        dispatchFullBodyCue(actor, 0);
      }
      break;
    }
    default: break;
  }
}

// ============================================================================
// Action 4 machine A — BIG-SHURIKEN TOSS (zz_0071ac0_, phases @0x802d3c90).
// Command-disabled for pl0000/pl000a as action 4, but SASUKE reaches it through
// action-1 variants 1/2 (the borg-switched table @0x802d3be8). Constants (§A10):
// aim 60→dash 20f (FLOAT_8043774c), reposition ×0.95 (FLOAT_80437744), stream g4 s4,
// recovery decay ×0.97 (FLOAT_80437774), trail gate 3.0.
// ============================================================================
const NINJA_TOSS = {
  REPOS: 0.95, DASH_FRAMES: 20.0, DECAY: 0.97, STREAM_GROUP: 4, STREAM_SLOT: 4,
} as const;

function ninjaBigShurikenToss(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & NinjaScratch;
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: {
      actor.fbPhaseSlots[0] = 1;
      actor.hSpeed = 0; actor.hDecel = 0;
      const t = s.lockTarget;
      if (!t) { actor.activeYaw = actor.heading; actor.lockYaw = actor.heading; }
      // Reposition ×0.95 (motion accumulator, same shape as shared-X phase 0).
      if (t) {
        actor.motion.x = (actor.pos.x - t.x) * NINJA_TOSS.REPOS;
        actor.motion.z = (actor.pos.z - t.z) * NINJA_TOSS.REPOS;
        actor.pos.x += actor.motion.x;
        actor.pos.z += actor.motion.z;
      }
      startStream(actor, 0xf, NINJA_TOSS.STREAM_GROUP, NINJA_TOSS.STREAM_SLOT);
      actor.handlerTimer = NINJA_TOSS.DASH_FRAMES;
      break;
    }
    case 1: {
      tickStream(actor, 0xf, ctx);
      actor.motion.x *= NINJA_TOSS.REPOS;
      actor.motion.z *= NINJA_TOSS.REPOS;
      actor.pos.x += actor.motion.x;
      actor.pos.z += actor.motion.z;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0) {
        actor.fbPhaseSlots[0] = 2;
        const d = targetDist(actor);
        actor.hSpeed = Math.max(150.0, d ?? 150.0) / NINJA_TOSS.DASH_FRAMES;
        actor.handlerTimer = 30;
      }
      break;
    }
    case 2: {
      tickStream(actor, 0xf, ctx);
      actor.hSpeed *= NINJA_TOSS.DECAY;
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer <= 0 || actor.contactP0 < 0) {
        actor.controlWord &= ~0x3;
        dispatchUpperBodyCue(actor, 0);
        dispatchFullBodyCue(actor, 0);
      }
      break;
    }
    default: break;
  }
}

export function createNinjaRootAction(ctx: NinjaFamilyCtx): (actor: RomActor) => void {
  const xConfig: SharedXConfig = {
    groundSlot: NINJA_X_GROUND_SLOT,
    airSlot: NINJA_X_AIR_SLOT,
    onHit: ninjaXOnHit,
  };
  const xSpecial = createSharedXSpecial(xConfig, ctx);
  const lunge = createSharedMeleeLunge(NINJA_LUNGE_CONFIG, ctx);

  // Action 1 — contextual B: BORG-SWITCHED variant tables (FUN_80070604):
  //   pl0000 @0x802d3bd4: [lunge, lunge, spinSlash, flyingLunge*, leap]
  //   SASUKE @0x802d3be8: [lunge, bigShuriken, bigShuriken, flyingLunge*, leap]
  // (*flying lunge v3 (zz_00710d8_) is NOT ported this pass — its bone-matrix steering
  // + SASUKE bounce needs the +0x86c row semantics; falls through to the shared lunge
  // as the closest ported motion, labeled approximation.)
  const contextualB = (actor: RomActor): void => {
    const v = actor.variantIndex;
    const isSasuke = actor.borgNumber === 0x00a;
    if (v === 2) {
      if (isSasuke) ninjaBigShurikenToss(actor, ctx);
      else ninjaSpinSlash(actor, ctx);
    } else if (v === 1 && isSasuke) {
      ninjaBigShurikenToss(actor, ctx);
    } else if (v === 4) {
      ninjaLeap(actor, ctx);
    } else {
      lunge(actor); // v0/v1 (and the v3 approximation)
    }
  };

  // PTR_FUN_802d3b68 — action 0 (B-tap combo) + 1 (contextual B) + 2 (X) ported;
  // 3/4 are command-disabled for this family's two borgs (descriptor +0xb8 = 0xff).
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    (actor) => ninjaBCombo(actor, ctx), // 0: B-tap sword combo (FUN_8006fb08 machine A)
    contextualB,                        // 1: contextual-B (FUN_80070604, borg-switched)
    xSpecial,                           // 2: X-special (shared zz_00ff2bc_, cfg 0x80433868)
    null,                               // 3: X-charge dash — command-disabled
    null,                               // 4: B-charge toss — command-disabled (SASUKE
                                        //    reaches its machine via action-1 v1/v2 above)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned ninja-family actor (pl0000/pl000a). */
export function configureNinjaFamily(
  actor: RomActor,
  borgId: "pl0000" | "pl000a",
  ctx: NinjaFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl000a" ? 0x00a : 0x000;
  actor.rootAction = createNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
