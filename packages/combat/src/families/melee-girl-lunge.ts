// Bespoke B-melee engine zz_010b7ac_ @0x8010b7ac — the LUNGE 4-phase melee machine
// shared by 12 "girl"/"death-borg-delta" borgs (variant 3 of action 1). Source:
//   research/decomp/ghidra-export/chunk_0030.c:1317 (dispatcher zz_010b7ac_)
//   chunk_0030.c:1331 (phase 0 setup FUN_8010b7fc)
//   chunk_0030.c:1378 (phase 1 pre-active FUN_8010b94c)
//   chunk_0030.c:1408 (phase 2 steer-dive FUN_8010ba14)
//   chunk_0030.c:1447 (phase 3 combo/recovery FUN_8010bb18)
//
// Distinct from the standing melee (zz_010c220_): phase 0 REPOSITIONS from the lock
// target (the PSVECSubtract/PSQUATScale/PSVECAdd "blink away" chain), phase 2 drives a
// steer-yaw sin/cos dive, and phase 3 carries the combo loop-back (+0x1cf0<0 &
// +0x746 → phase 3→2 with the next stream slot). References phase table
// PTR_FUN_80325a78.
//
// Borgs covered (action 1 variant 3): pl0300, pl0301, pl0302, pl0304, pl0305, pl0307,
// pl0308, pl0309, pl030a, pl030b, pl030c, pl030d.
//
// Float constants (FLOAT_804395xx bank, DOL-read):
//   FLOAT_8043956c = timer seed (phase 0 +0x558, phase 3 loop-back)
//   FLOAT_80439568 = active-window timer (phase 1 transition + phase 3 combo)
//   FLOAT_8043955c = reposition scale (phase 0/1) + recovery decel
//   FLOAT_80439554 = -1.0 stream rate
//   FLOAT_80439558 = 0.0 floor
//   FLOAT_8043957c = steer-yaw velocity magnitude
//   FLOAT_80439564 = physics gravity param (FUN_80067310)
//   FLOAT_80439580 = proximity range (FUN_800668cc gate)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  integratePhysics,
  vecSubtract,
  vecScale,
  vecAdd,
  projectX,
  projectZ,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const MELEE_GIRL_LUNGE = {
  TIMER_SEED: 60.0,      // FLOAT_8043956c
  ACTIVE_TIMER: 30.0,    // FLOAT_80439568
  STREAM_RATE: -1.0,     // FLOAT_80439554
  TIMER_FLOOR: 0.0,      // FLOAT_80439558
  REPOSITION_SCALE: 0.0, // FLOAT_8043955c (the motion ×= scale each active frame)
  STEER_MAGNITUDE: 1.0,  // FLOAT_8043957c
  GRAVITY: 1.0,          // FLOAT_80439564
  PROXIMITY: 100.0,      // FLOAT_80439580
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  STATE_FACE: 0xc0,
} as const;

export interface MeleeGirlLungeConfig {
  seedSlot?: number;
  activeTimer?: number;
  repositionScale?: number;
}

interface MeleeScratch {
  bRetap?: boolean;
  bRetapInput?: boolean;
  swingReArm?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function targetDistance(actor: RomActor & MeleeScratch): number | null {
  const t = actor.lockTarget;
  if (!t) return null;
  return Math.hypot(t.x - actor.pos.x, t.z - actor.pos.z);
}

// Phase 0 — FUN_8010b7fc @ chunk_0030.c:1331.
function phase0(actor: RomActor & MeleeScratch, cfg: Required<MeleeGirlLungeConfig>): void {
  actor.fbPhaseSlots[0] += 1;
  if (!actor.grounded) {
    actor.lockYaw = actor.heading;
    actor.activeYaw = actor.heading;
  }
  actor.handlerTimer = MELEE_GIRL_LUNGE.TIMER_SEED;
  actor.bRetap = false;
  actor.streamSlot = cfg.seedSlot;
  // Zero velocity scalars (+0x50/+0x48/+0x4c/+0x44 = FLOAT_80439558 = 0).
  actor.hSpeed = 0; actor.yVel = 0; actor.hDecel = 0; actor.gravityCoeff = 0;
  // Reposition: motion = (pos - lockTarget); motion *= scale; pos += motion.
  const target = actor.lockTarget;
  if (target && cfg.repositionScale !== 0) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(
    actor,
    MELEE_GIRL_LUNGE.PART_MASK,
    MELEE_GIRL_LUNGE.STREAM_GROUP,
    slot,
    MELEE_GIRL_LUNGE.STREAM_RATE,
  );
}

// Phase 1 — FUN_8010b94c @ chunk_0030.c:1378.
function phase1(actor: RomActor & MeleeScratch, cfg: Required<MeleeGirlLungeConfig>, ctx: StreamContext): void {
  tickStream(actor, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  if (cfg.repositionScale !== 0) {
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  actor.handlerTimer -= actor.dt;
  const facingComplete = actor.lockTarget != null;
  if (actor.handlerTimer <= MELEE_GIRL_LUNGE.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;
    actor.handlerTimer = cfg.activeTimer;
  }
}

// Phase 2 — FUN_8010ba14 @ chunk_0030.c:1408.
function phase2(actor: RomActor & MeleeScratch, ctx: StreamContext): void {
  tickStream(actor, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  // Steer-yaw dive: hSpeed = magnitude × cos(steerYaw); yVel = magnitude × -sin(steerYaw).
  // zz_0045238_(+0x54e) → cos (projectZ); zz_0045204_(+0x54e) → sin (projectX).
  actor.hSpeed = MELEE_GIRL_LUNGE.STEER_MAGNITUDE * projectZ(actor.steerYaw);
  actor.yVel = MELEE_GIRL_LUNGE.STEER_MAGNITUDE * -projectX(actor.steerYaw);
  integratePhysics(MELEE_GIRL_LUNGE.GRAVITY, actor, actor.activeYaw);
  actor.handlerTimer -= actor.dt;
  const dist = targetDistance(actor);
  const inProximity = dist !== null && dist <= MELEE_GIRL_LUNGE.PROXIMITY;
  if (actor.handlerTimer <= MELEE_GIRL_LUNGE.TIMER_FLOOR || inProximity) {
    actor.fbPhaseSlots[0] += 1;
  }
}

// Phase 3 — FUN_8010bb18 @ chunk_0030.c:1447.
function phase3(actor: RomActor & MeleeScratch, cfg: Required<MeleeGirlLungeConfig>, ctx: StreamContext): void {
  tickStream(actor, MELEE_GIRL_LUNGE.PART_MASK, ctx);
  if (actor.bRetapInput) actor.bRetap = true;
  // Combo-continue: +0x1cf0<0 (swingReArm) AND +0x746 (bRetap) → loop back to phase 2.
  if (actor.swingReArm && actor.bRetap) {
    actor.fbPhaseSlots[0] -= 1; // 3 → 2
    actor.bRetap = false;
    actor.handlerTimer = cfg.activeTimer;
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(
      actor,
      MELEE_GIRL_LUNGE.PART_MASK,
      MELEE_GIRL_LUNGE.STREAM_GROUP,
      slot,
      MELEE_GIRL_LUNGE.STREAM_RATE,
    );
    return;
  }
  // Recovery tail.
  const decel: number = MELEE_GIRL_LUNGE.REPOSITION_SCALE;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;
    actor.yVel *= decel;
  }
  integratePhysics(MELEE_GIRL_LUNGE.GRAVITY, actor, actor.activeYaw);
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 7);
  }
}

export function createMeleeGirlLunge(
  ctx: StreamContext,
  cfg: MeleeGirlLungeConfig = {},
): (actor: RomActor) => void {
  const resolved: Required<MeleeGirlLungeConfig> = {
    seedSlot: cfg.seedSlot ?? 0,
    activeTimer: cfg.activeTimer ?? MELEE_GIRL_LUNGE.ACTIVE_TIMER,
    repositionScale: cfg.repositionScale ?? MELEE_GIRL_LUNGE.REPOSITION_SCALE,
  };
  return (actor: RomActor) => {
    const a = actor as RomActor & MeleeScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: phase0(a, resolved); break;
      case 1: phase1(a, resolved, ctx); break;
      case 2: phase2(a, ctx); break;
      case 3: phase3(a, resolved, ctx); break;
      default: break;
    }
  };
}
