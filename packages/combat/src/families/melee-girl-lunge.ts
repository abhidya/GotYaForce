// Bespoke B-melee engine zz_010b7ac_ @0x8010b7ac — the M-2 LUNGE-DIVE 4-phase melee
// machine shared by the girl/delta cluster (action 1 variant 3; DEATH BORG DELTA also
// wires variant 4 here with seed 5). Phase table PTR_FUN_80325a78 @0x80325a78 —
// 4 entries, DOL-dump confirmed ([FUN_8010b7fc, FUN_8010b94c, FUN_8010ba14,
// FUN_8010bb18]; the next word 0x80325a88 is the M-3 table start = past end).
//
// Source (re-verified 2026-07-06 for the girl-cluster batch — this file REPLACES the
// wave-C transcription, which had the wrong float bank values and the old
// full-cue-0 + upper-7 exit convention):
//   research/decomp/ghidra-export/chunk_0030.c:1317 (dispatcher zz_010b7ac_)
//   chunk_0030.c:1331 (phase 0 setup FUN_8010b7fc)
//   chunk_0030.c:1378 (phase 1 pre-dive FUN_8010b94c)
//   chunk_0030.c:1408 (phase 2 pitch-dive FUN_8010ba14)
//   chunk_0030.c:1447 (phase 3 combo/recovery FUN_8010bb18)
//
// The seed slot is the leaf thunks' r4 immediate (raw-word verified: FUN_800c0914
// `addi r4,r0,4` → seed 4; DELTA's FUN_801d456c `addi r4,r0,5` → seed 5).
//
// Float constants (FLOAT_804395xx bank, ALL DOL-read this batch):
//   FLOAT_8043956c = 60.0  (phase-0 face budget +0x558)
//   FLOAT_80439568 = 20.0  (phase-2 dive window; phase-3 combo re-seed)
//   FLOAT_8043955c = 0.95  (blink-reposition scale + phase-3 recovery drag)
//   FLOAT_80439554 = -1.0  (stream rate)
//   FLOAT_80439558 = 0.0
//   FLOAT_8043957c = 30.0  (dive velocity magnitude)
//   FLOAT_80439564 = 1.0   (gravity param + landing cooldown seed)
//   FLOAT_80439580 = 150.0 (proximity range, FUN_800668cc gate)
//   DOUBLE_80439588 = 2.5 / DOUBLE_80439590 = 20.0 (phase-3 dash refresh:
//     +0x44 = (2.5 × +0x760) / 20 = dist × 0.125)

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { romAirKnockoutReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { resetPoseHousekeeping, stepTargetPitch, stepTargetYaw } from "../rom/helpers.js";

export const MELEE_GIRL_LUNGE = {
  FACE_BUDGET: 60.0,      // FLOAT_8043956c
  DIVE_WINDOW: 20.0,      // FLOAT_80439568
  REPOSITION: 0.95,       // FLOAT_8043955c (blink scale + recovery drag)
  STREAM_RATE: -1.0,      // FLOAT_80439554
  ZERO: 0.0,              // FLOAT_80439558
  DIVE_MAGNITUDE: 30.0,   // FLOAT_8043957c
  GRAVITY: 1.0,           // FLOAT_80439564 (also the landing +0x694 cooldown seed)
  PROXIMITY: 150.0,       // FLOAT_80439580 (FUN_800668cc gate)
  DASH_REFRESH_NUM: 2.5,  // DOUBLE_80439588
  DASH_REFRESH_DEN: 20.0, // DOUBLE_80439590
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  /** zz_0092dcc_ @0x80092dcc — dive FX child (samurai SAMURAI_SPAWNERS.DIVE_FX
   *  precedent; fired at the phase 1→2 dive start and on each phase-3 combo). */
  DIVE_FX_ADDR: 0x80092dcc,
} as const;

export interface MeleeGirlLungeConfig {
  /** +0x6ea g3 seed slot — the leaf thunk's r4 immediate (4 for every girl family;
   *  DEATH BORG DELTA v4 uses 5). */
  seedSlot?: number;
}

interface MeleeScratch {
  /** +0x5d4 & 0x40 — B button edge this frame (host-set). */
  bRetapInput?: boolean;
  /** +0x746 — B-retap latch. */
  bRetap?: boolean;
  /** (s8)+0x1cf0 — part-0 swing event byte (< 0 = combo re-arm). Plain read — it only
   *  gates the OPTIONAL combo loop, not phase progress. */
  swingEvent?: number;
  /** (s8)+0x1d0f — stream-authored dash-strength byte. */
  dashStrength?: number;
  /** +0x1b03 — stream-tick gate (anim hold byte). */
  streamTickGate?: boolean;
  /** +0x54e — dive aim pitch (BAM16; zz_006e514_ output — valkrie meleeAimPitch
   *  precedent, same offset). */
  meleeAimPitch?: number;
  /** actor+0x86c row (column 1) override — phase-0 air/range gate. */
  rangeRow86c?: number;
  /** actor+0x868 row (column 0) override — phase-3 no-lock dash refresh. */
  rangeRow868?: number;
  /** +0x760/+0x764 distance mirror (valkrie curTargetDist precedent). */
  curTargetDist?: number;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

type MActor = RomActor & MeleeScratch;

function s16(v: number): number {
  return (v << 16) >> 16;
}

/** +0x760/+0x764 mirror — refresh on locked reads, stale cache when unlocked. */
function targetDistance(a: MActor): number {
  const t = a.lockTarget;
  if (t) {
    a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    return a.curTargetDist;
  }
  return a.curTargetDist ?? 0;
}

/** FUN_80066838 / FUN_800668cc — range gate: −1 no lock, 1 in range, 0 beyond
 *  (samurai rangeCheck reading; both variants share the comparison contract). */
function rangeCheck(a: MActor, range: number): number {
  if (!a.lockTarget) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

/** zz_006d144_(actor, 0xc0) — face the lock target; nonzero = facing complete
 *  (bridge pre-aims lockYaw — shared-melee-gred precedent). */
function faceComplete(a: MActor): boolean {
  return stepTargetYaw(a, 0xc0);
}

/** zz_006e514_(actor, 0xc0, &+0x54e) — aim-pitch seek toward the lock target.
 *  PORT APPROXIMATION (valkrie.ts seekMeleeAimPitch precedent): snap to the target
 *  pitch; decay toward 0 without a target. +0x48 = mag × -sin(pitch) → pitch < 0
 *  aims UP. */
function seekAimPitch(a: MActor): void {
  a.meleeAimPitch = stepTargetPitch(a, 0xc0, a.meleeAimPitch ?? 0).value;
}

/** zz_006ed8c_(scale, actor) — velocity drag on +0x44/+0x48. */
function applyDrag(a: MActor, scale: number): void {
  a.hSpeed *= scale;
  a.yVel *= scale;
}

// Phase 0 — FUN_8010b7fc @ chunk_0030.c:1331. Blink-reposition setup.
function phase0(a: MActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                        // +0x540++
  // FUN_80066838(row86c — COLUMN 1) < 1 → invalidate: +0x541 = 1, +0xcc = 0,
  // +0x5ae = +0x72, +0x5ac = +0x72.
  if (rangeCheck(a, a.actionSpeedRows[1]) < 1) {
    a.fbPhaseSlots[1] = 1;
    a.lockTarget = null;
    a.lockYaw = a.heading;
    a.activeYaw = a.heading;
  }
  a.handlerTimer = MELEE_GIRL_LUNGE.FACE_BUDGET; // +0x558 = 60 (FLOAT_8043956c)
  a.meleeAimPitch = 0;                           // +0x54e = 0
  a.bRetap = false;                              // +0x746 = 0
  a.streamSlot = seedSlot;                       // +0x6ea = r4 seed
  a.gravityCoeff = MELEE_GIRL_LUNGE.ZERO;        // +0x50 = 0
  a.yVel = MELEE_GIRL_LUNGE.ZERO;                // +0x48 = 0
  a.hDecel = MELEE_GIRL_LUNGE.ZERO;              // +0x4c = 0
  a.hSpeed = MELEE_GIRL_LUNGE.ZERO;              // +0x44 = 0
  resetPoseHousekeeping(a);
  // zz_006d144_(0xc0) face + zz_006e514_(0xc0, &+0x54e) pitch seek.
  seekAimPitch(a);
  // Blink: motion = pos − target(+0x5e8); ×0.95 (FLOAT_8043955c); pos += motion.
  if (a.lockTarget) {
    vecSubtract(a.pos, a.lockTarget, a.motion);
    vecScale(MELEE_GIRL_LUNGE.REPOSITION, a.motion, a.motion);
    vecAdd(a.pos, a.motion, a.pos);
  } else {
    // The ROM reads the +0x5e8 target cache unconditionally; with no lock zero the
    // motion so phases 1-3 don't drift along a stale vector (blink rule, labeled).
    a.motion.x = 0; a.motion.y = 0; a.motion.z = 0;
  }
  // zz_00677b0_(actor) — ground collide (bridge owns the clamp).
  const slot = a.streamSlot;                     // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                       // +0x6ea++
  startStream(a, MELEE_GIRL_LUNGE.PART_MASK, MELEE_GIRL_LUNGE.STREAM_GROUP, slot, MELEE_GIRL_LUNGE.STREAM_RATE);
}

// Phase 1 — FUN_8010b94c @ chunk_0030.c:1378. Face budget → dive start.
function phase1(a: MActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {                 // +0x1b03 != 0
    tickStream(a, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  }
  vecScale(MELEE_GIRL_LUNGE.REPOSITION, a.motion, a.motion); // ×0.95
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — bridge clamp.
  seekAimPitch(a);                               // zz_006e514_(0xc0, &+0x54e)
  a.handlerTimer -= a.dt;                        // +0x558 -= dt
  if (a.handlerTimer <= MELEE_GIRL_LUNGE.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                      // +0x540++
    a.handlerTimer = MELEE_GIRL_LUNGE.DIVE_WINDOW; // +0x558 = 20 (FLOAT_80439568)
    // zz_0092dcc_(actor, 0) — dive FX child.
    ctx.onFamilyProjectile?.(a, MELEE_GIRL_LUNGE.DIVE_FX_ADDR, 0);
  }
}

// Phase 2 — FUN_8010ba14 @ chunk_0030.c:1408. Pitch-projected dive.
function phase2(a: MActor, ctx: StreamContext): void {
  if (a.streamHold1b03 !== 0) {                 // +0x1b03 != 0
    tickStream(a, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  }
  // zz_006d144_(0xc0) face + zz_006e514_ pitch seek.
  seekAimPitch(a);
  const pitch = a.meleeAimPitch ?? 0;
  a.hSpeed = MELEE_GIRL_LUNGE.DIVE_MAGNITUDE * projectZ(pitch);  // +0x44 = 30 × cos(+0x54e)
  a.yVel = MELEE_GIRL_LUNGE.DIVE_MAGNITUDE * -projectX(pitch);   // +0x48 = 30 × -sin(+0x54e)
  if (!a.lockTarget) {                           // +0xcc == 0 → abort the dive
    a.handlerTimer = MELEE_GIRL_LUNGE.ZERO;      // +0x558 = 0
    a.yVel = MELEE_GIRL_LUNGE.ZERO;              // +0x48 = 0
    a.hSpeed = MELEE_GIRL_LUNGE.ZERO;            // +0x44 = 0
    a.gravityCoeff = a.descriptor?.handlerData6c ?? 1.0; // +0x50 = dataPage(+0x4ac)+0x6c
  }
  integratePhysics(MELEE_GIRL_LUNGE.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5ac)
  // zz_00677b0_(actor) — bridge clamp.
  a.handlerTimer -= a.dt;                        // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_800668cc(150) > 0 (in range ONLY).
  if (a.handlerTimer <= MELEE_GIRL_LUNGE.ZERO || rangeCheck(a, MELEE_GIRL_LUNGE.PROXIMITY) > 0) {
    a.fbPhaseSlots[0] += 1;                      // +0x540++
  }
}

// Phase 3 — FUN_8010bb18 @ chunk_0030.c:1447. Combo loop-back / recovery.
function phase3(a: MActor, ctx: StreamContext): void {
  tickStream(a, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  if (a.bRetapInput) a.bRetap = true;            // +0x5d4 & 0x40 → +0x746 = 1
  // COMBO: (s8)+0x1cf0 < 0 (swing re-arm) AND +0x746 → 3 → 2 backward loop.
  if (a.contactP1 < 0 && a.bRetap) {
    a.fbPhaseSlots[0] -= 1;                      // +0x540 += -1
    a.bRetap = false;                            // +0x746 = 0
    a.handlerTimer = MELEE_GIRL_LUNGE.DIVE_WINDOW; // +0x558 = 20 (FLOAT_80439568)
    ctx.onFamilyProjectile?.(a, MELEE_GIRL_LUNGE.DIVE_FX_ADDR, 0); // zz_0092dcc_(a, 0)
    const slot = a.streamSlot;                   // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                     // +0x6ea++
    startStream(a, MELEE_GIRL_LUNGE.PART_MASK, MELEE_GIRL_LUNGE.STREAM_GROUP, slot, MELEE_GIRL_LUNGE.STREAM_RATE);
    return;
  }
  if (a.dashStrength1d0f > 0) {                  // (s8)+0x1d0f > 0 → dash refresh
    a.dashStrength1d0f = 0;                      // +0x1d0f = 0
    if (!a.lockTarget) {                         // +0xcc == 0
      a.hSpeed = a.actionSpeedRows[0]
        / MELEE_GIRL_LUNGE.DIVE_WINDOW;          // +0x44 = row868 / 20
    } else {
      // +0x44 = (2.5 × +0x760) / 20 (DOUBLE_80439588 / DOUBLE_80439590).
      a.hSpeed = (MELEE_GIRL_LUNGE.DASH_REFRESH_NUM * targetDistance(a))
        / MELEE_GIRL_LUNGE.DASH_REFRESH_DEN;
    }
  }
  if (a.dashStrength1d0f < 0) {                  // negative byte → altitude cap
    a.dashStrength1d0f = 0;                      // +0x1d0f = 0
    if (a.yVel > MELEE_GIRL_LUNGE.ZERO) a.yVel = MELEE_GIRL_LUNGE.ZERO; // +0x48 clamp ≤ 0
    a.gravityCoeff = a.descriptor?.handlerData6c ?? 1.0; // +0x50 = dataPage+0x6c
  }
  applyDrag(a, MELEE_GIRL_LUNGE.REPOSITION);     // zz_006ed8c_(0.95, FLOAT_8043955c)
  integratePhysics(MELEE_GIRL_LUNGE.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5ac)
  const grounded = a.grounded === true;          // iVar3 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {             // landed + (s8)+0x1cef < 0
    a.controlWord &= ~0x3;                       // +0x73f = 0; +0x5e0 &= 0xfffffffc
    dispatchUpperBodyCue(a, 7);                  // zz_006a750_(actor, 7)
    a.stateTimer = MELEE_GIRL_LUNGE.GRAVITY + a.dt; // +0x694 = 1.0 (FLOAT_80439564) + dt
    return;
  }
  if (a.wallContact !== 0) {                     // +0x1cee != 0
    a.controlWord &= ~0x3;                       // +0x73f = 0; +0x5e0 &= 0xfffffffc
    romAirKnockoutReturn(a);                     // zz_006a5a4_ @ chunk_0009.c:770
  }
}

/** Build the M-2 lunge-dive handler (dispatcher zz_010b7ac_ @0x8010b7ac). */
export function createMeleeGirlLunge(
  ctx: StreamContext,
  cfg: MeleeGirlLungeConfig = {},
): (actor: RomActor) => void {
  const seedSlot = cfg.seedSlot ?? 4; // fleet-wide r4 immediate (DELTA v4 passes 5)
  return (actor: RomActor) => {
    const a = actor as MActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {        // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {            // PTR_FUN_80325a78[+0x540]
      case 0: phase0(a, seedSlot); break;
      case 1: phase1(a, ctx); break;
      case 2: phase2(a, ctx); break;
      case 3: phase3(a, ctx); break;
      default: break;
    }
  };
}
