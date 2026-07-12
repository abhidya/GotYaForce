// Bespoke B-melee engine zz_010c220_ @0x8010c220 — the M-4 STANDING 4-phase melee
// machine shared by the girl/delta cluster (action 1 variant 1; DEATH BORG DELTA
// wires variants 1 AND 2 here with seed 6). Phase table PTR_FUN_80325a98 @0x80325a98
// — 4 entries, DOL-dump confirmed ([FUN_8010c270, FUN_8010c354, FUN_8010c43c,
// FUN_8010c508]; the next word 0x80325aa8 is the M-5 table start = past end).
//
// Source (re-verified 2026-07-06 for the girl-cluster batch — this file REPLACES the
// wave-C transcription: wrong float values [active window is 20, not 30; proximity is
// 150, not 100], a phantom +0x6ea increment in phase 0, the missing melee-FX child,
// the missing phase-2 hit-react advance and +0x541=0xff re-arm, and the old
// full-cue-0 exit convention):
//   research/decomp/ghidra-export/chunk_0030.c:1695 (dispatcher zz_010c220_)
//   chunk_0030.c:1709 (phase 0 setup FUN_8010c270)
//   chunk_0030.c:1740 (phase 1 pre-active FUN_8010c354)
//   chunk_0030.c:1774 (phase 2 active FUN_8010c43c)
//   chunk_0030.c:1807 (phase 3 recovery FUN_8010c508)
//
// The seed slot is the leaf thunks' r4 immediate (girl families 8, KILLER GIRL 9,
// DEATH BORG DELTA 6 — actionStreamTables.json emulated evidence + raw-word check
// of FUN_801d4548 `addi r4,r0,6`).
//
// Float constants (FLOAT_804395xx bank, ALL DOL-read this batch):
//   FLOAT_8043956c = 60.0  (phase-0 face budget)
//   FLOAT_80439568 = 20.0  (phase-2 active window + dash divisor)
//   FLOAT_8043955c = 0.95  (phase-2 drag)
//   FLOAT_80439540 = 0.9   (phase-3 recovery drag)
//   FLOAT_80439554 = -1.0  (stream rate)
//   FLOAT_80439558 = 0.0
//   FLOAT_80439560 = 3.0   (afterimage |vel| gate — renderer no-op)
//   FLOAT_80439580 = 150.0 (proximity range, FUN_80066838 gate + FX gate)

import type { RomActor } from "../rom/actor.js";
import { integratePhysics } from "../rom/physics.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { stepAfterimage, stepTargetYaw } from "../rom/helpers.js";

export const MELEE_GIRL_STANDING = {
  FACE_BUDGET: 60.0,    // FLOAT_8043956c
  ACTIVE_WINDOW: 20.0,  // FLOAT_80439568
  DRAG: 0.95,           // FLOAT_8043955c
  RECOVERY_DRAG: 0.9,   // FLOAT_80439540
  STREAM_RATE: -1.0,    // FLOAT_80439554
  ZERO: 0.0,            // FLOAT_80439558
  PROXIMITY: 150.0,     // FLOAT_80439580
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  /** zz_00b2190_ @0x800b2190 — melee trail FX child (samurai MELEE_FX precedent). */
  MELEE_FX_ADDR: 0x800b2190,
} as const;

export interface MeleeGirlStandingConfig {
  /** +0x6ea g3 seed slot — the leaf thunk's r4 immediate (8 girls / 9 killer / 6 delta). */
  seedSlot?: number;
}

interface MeleeScratch {
  /** +0x1d9 — hit-react/impact status byte (phase-2 advance OR; samurai hitReact). */
  hitReact?: number;
  /** actor+0x868 row (column 0) override. */
  rangeRow868?: number;
  /** +0x764 distance mirror. */
  curTargetDist?: number;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

type MActor = RomActor & MeleeScratch;

function s16(v: number): number {
  return (v << 16) >> 16;
}

function targetDistance(a: MActor): number {
  const t = a.lockTarget;
  if (t) {
    a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    return a.curTargetDist;
  }
  return a.curTargetDist ?? 0;
}

/** FUN_80066838(range, actor) — −1 no lock, 1 in range, 0 beyond. */
function rangeCheck(a: MActor, range: number): number {
  if (!a.lockTarget) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

function faceComplete(a: MActor): boolean {
  return stepTargetYaw(a, 0xc0);
}

/** zz_006ed8c_(scale, actor). */
function applyDrag(a: MActor, scale: number): void {
  a.hSpeed *= scale;
  a.yVel *= scale;
}

// Phase 0 — FUN_8010c270 @ chunk_0030.c:1709.
function phase0(a: MActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                        // +0x540++
  a.streamSlot = seedSlot;                       // +0x6ea = r4 seed
  // FUN_80066838(row868) < 1 → invalidate; the +0x5ac source forks on +0x5e0 & 0x20.
  if (rangeCheck(a, a.actionSpeedRows[0]) < 1) {
    a.fbPhaseSlots[1] = 1;                       // +0x541 = 1
    a.lockTarget = null;                         // +0xcc = 0
    if ((a.controlWord & 0x20) === 0) {
      a.activeYaw = a.heading;                   // +0x5ac = +0x72
    } else {
      a.activeYaw = a.lockYaw;                   // +0x5ac = +0x5ae
    }
  }
  a.handlerTimer = MELEE_GIRL_STANDING.FACE_BUDGET; // +0x558 = 60 (FLOAT_8043956c)
  faceComplete(a);                               // zz_006d144_(actor, 0xc0)
  // zz_004beb8_(-1.0, actor, 0xf, 3, (s8)+0x6ea) — NO +0x6ea increment in M-4.
  startStream(a, MELEE_GIRL_STANDING.PART_MASK, MELEE_GIRL_STANDING.STREAM_GROUP,
    a.streamSlot, MELEE_GIRL_STANDING.STREAM_RATE);
  a.accumulator80c = 0;
}

// Phase 1 — FUN_8010c354 @ chunk_0030.c:1740. Face budget → swing arm.
function phase1(a: MActor, ctx: StreamContext): void {
  a.handlerTimer -= a.dt;                        // +0x558 -= dt
  if (a.handlerTimer <= MELEE_GIRL_STANDING.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                      // +0x540++
    a.handlerTimer = MELEE_GIRL_STANDING.ACTIVE_WINDOW; // +0x558 = 20 (FLOAT_80439568)
    let f = a.actionSpeedRows[0];                 // actor+0x868 descriptor row
    if (a.lockTarget && f < targetDistance(a)) { // +0xcc != 0 && row < +0x764
      f = targetDistance(a);
    }
    a.hSpeed = f / MELEE_GIRL_STANDING.ACTIVE_WINDOW; // +0x44 = f / 20
    a.hDecel = MELEE_GIRL_STANDING.ZERO;         // +0x4c = 0
    if (MELEE_GIRL_STANDING.PROXIMITY < targetDistance(a)) { // 150 < +0x764
      ctx.onFamilyProjectile?.(a, MELEE_GIRL_STANDING.MELEE_FX_ADDR, 0); // zz_00b2190_(a, 0)
    }
  }
}

// Phase 2 — FUN_8010c43c @ chunk_0030.c:1774. Active dash-in.
function phase2(a: MActor, ctx: StreamContext): void {
  faceComplete(a);                               // zz_006d144_(actor, 0xc0)
  applyDrag(a, MELEE_GIRL_STANDING.DRAG);        // zz_006ed8c_(0.95, FLOAT_8043955c)
  integratePhysics(0, a, s16(a.lockYaw));        // zz_00670dc_(actor, +0x5ae) — yaw-only
  if (a.contactP0 >= 0) {                        // -1 < (s8)+0x1cef → tick
    tickStream(a, MELEE_GIRL_STANDING.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                        // +0x558 -= dt
  // Advance when: timer ≤ 0 OR FUN_80066838(150) ≥ 1 OR hit-react byte +0x1d9 != 0.
  if (a.handlerTimer > MELEE_GIRL_STANDING.ZERO
    && rangeCheck(a, MELEE_GIRL_STANDING.PROXIMITY) < 1
    && (a.hitReact ?? 0) === 0) {
    if (a.hSpeed > 3) stepAfterimage(a);
    return;                                      // LAB_8010c4dc
  }
  a.fbPhaseSlots[0] += 1;                        // +0x540++
  a.fbPhaseSlots[1] = 0xff;                      // +0x541 = 0xff (lock-clear re-arm)
  if (a.hSpeed > 3) stepAfterimage(a);
}

// Phase 3 — FUN_8010c508 @ chunk_0030.c:1807. Recovery.
function phase3(a: MActor, ctx: StreamContext): void {
  tickStream(a, MELEE_GIRL_STANDING.PART_MASK, ctx);
  applyDrag(a, MELEE_GIRL_STANDING.RECOVERY_DRAG); // zz_006ed8c_(0.9, FLOAT_80439540)
  integratePhysics(0, a, s16(a.lockYaw));        // zz_00670dc_(actor, +0x5ae)
  if (a.wallContact !== 0) {                     // +0x1cee != 0
    a.controlWord &= ~0x3;                       // +0x73f = 0; +0x5e0 &= 0xfffffffc
    romGroundIdleReturn(a);                      // zz_006a474_ @ chunk_0009.c:708
  }
  if (a.hSpeed > 3) stepAfterimage(a);
}

/** Build the M-4 standing-melee handler (dispatcher zz_010c220_ @0x8010c220). */
export function createMeleeGirlStanding(
  ctx: StreamContext,
  cfg: MeleeGirlStandingConfig = {},
): (actor: RomActor) => void {
  const seedSlot = cfg.seedSlot ?? 8; // girl-family r4 immediate (killer 9, delta 6)
  return (actor: RomActor) => {
    const a = actor as MActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {        // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {            // PTR_FUN_80325a98[+0x540]
      case 0: phase0(a, seedSlot); break;
      case 1: phase1(a, ctx); break;
      case 2: phase2(a, ctx); break;
      case 3: phase3(a, ctx); break;
      default: break;
    }
  };
}
