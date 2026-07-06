// Bespoke B-melee engine zz_0149178_ @0x80149178 — the 4-phase LUNGE melee machine
// shared by 12 "samurai"/"death-borg-zeta" borgs (variants 3/4 of action 1). Source:
//   research/decomp/ghidra-export/chunk_0038.c:2158 (dispatcher zz_0149178_)
//   chunk_0038.c:2172 (phase 0 setup FUN_801491c8)
//   chunk_0038.c:2219 (phase 1 pre-active FUN_80149318)
//   chunk_0038.c:2264 (phase 2 steer-dive FUN_80149484)
//   chunk_0038.c:2309 (phase 3 recovery FUN_801495bc)
//
// CONFIG-STRUCT-DRIVEN (like the shared engine zz_0177dd8_): each phase handler takes a
// second param `param_2` = the config struct pointer, reading per-variant fields
// (reposition scale, timer, proximity, velocity scale, decel). References phase table
// PTR_FUN_8033ed2c. Distinct from the shared melee in that phase 0 repositions from
// target (the "blink away" chain) and phase 2 drives a steer-yaw sin/cos dive; no
// combo loop-back (phase 3 is straight recovery).
//
// Borgs covered (action 1 variants 3/4): pl0700, pl0701, pl0702, pl0703, pl0705,
// pl0706, pl0708, pl0709, pl070a, pl070b, pl070c, pl070d.
//
// Config struct layout (the ROM's param_2, read at the offsets cited inline):
//   +0x00 s32 seedSlot          ((char)*param_2 → +0x6ea)
//   +0x04 u32 timerFrames       (CONCAT44/DOUBLE u32→f32 coerce at phase 1 transition)
//   +0x08 f32 proximityRange    (FUN_800668cc gate, phase 2 advance)
//   +0x0c f32 velocityScale     (phase 2 transition multiplier on +0x44/+0x48/+0x4c/+0x50)
//   +0x10 f32 decel             (phase 3 zz_006ed8c_ scale)
//   +0x14 f32 repositionScale   (phase 0 + phase 1 PSQUATScale factor)
//
// Float constants (FLOAT_8043a3xx bank, DOL-read):
//   FLOAT_8043a384 = timer seed (phase 0 +0x558)
//   FLOAT_8043a374 = 0.0 floor / zero scalar
//   FLOAT_8043a37c = -1.0 stream rate
//   FLOAT_8043a378 = physics gravity param (FUN_80067310)
//   DOUBLE_8043a368 = u32→f64 coercion sentinel (the timerFrames cast at phase 1)

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
import { computeLungeSpeed } from "./shared-engine.js";

export const MELEE_SAMURAI = {
  TIMER_SEED: 60.0,      // FLOAT_8043a384
  STREAM_RATE: -1.0,     // FLOAT_8043a37c
  TIMER_FLOOR: 0.0,      // FLOAT_8043a374
  GRAVITY: 1.0,          // FLOAT_8043a378
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  STATE_FACE: 0xc0,
} as const;

export interface MeleeSamuraiConfig {
  /** +0x00: seed slot byte. */
  seedSlot: number;
  /** +0x04: u32 timer frames (the active-window length). */
  timerFrames: number;
  /** +0x08: float proximity range (phase 2 advance gate). */
  proximityRange: number;
  /** +0x0c: float velocity scale applied on the phase 2→3 transition. */
  velocityScale?: number;
  /** +0x10: float decel (phase 3 zz_006ed8c_ scale). Default 1.0. */
  decel?: number;
  /** +0x14: float reposition scale (phase 0 + phase 1 "blink from target"). */
  repositionScale?: number;
}

interface MeleeScratch {
  velRefresh?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function targetDistance(actor: RomActor & MeleeScratch): number | null {
  const t = actor.lockTarget;
  if (!t) return null;
  return Math.hypot(t.x - actor.pos.x, t.z - actor.pos.z);
}

// Phase 0 — FUN_801491c8 @ chunk_0038.c:2172.
function phase0(actor: RomActor & MeleeScratch, cfg: MeleeSamuraiConfig): void {
  actor.fbPhaseSlots[0] += 1;
  if (!actor.grounded) {
    actor.lockYaw = actor.heading;
    actor.activeYaw = actor.heading;
  }
  actor.handlerTimer = MELEE_SAMURAI.TIMER_SEED;
  actor.steerYaw = 0;
  actor.streamSlot = cfg.seedSlot;
  // Zero velocity scalars (+0x50/+0x48/+0x4c/+0x44 = FLOAT_8043a374 = 0).
  actor.hSpeed = 0; actor.yVel = 0; actor.hDecel = 0; actor.gravityCoeff = 0;
  // Reposition: motion = (pos - lockTarget); motion *= scale; pos += motion.
  const target = actor.lockTarget;
  const scale = cfg.repositionScale ?? 0;
  if (target && scale !== 0) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(scale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(
    actor,
    MELEE_SAMURAI.PART_MASK,
    MELEE_SAMURAI.STREAM_GROUP,
    slot,
    MELEE_SAMURAI.STREAM_RATE,
  );
}

// Phase 1 — FUN_80149318 @ chunk_0038.c:2219.
function phase1(actor: RomActor & MeleeScratch, cfg: MeleeSamuraiConfig, ctx: StreamContext): void {
  tickStream(actor, MELEE_SAMURAI.PART_MASK, ctx);
  const scale = cfg.repositionScale ?? 0;
  if (scale !== 0) {
    vecScale(scale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  actor.handlerTimer -= actor.dt;
  const facingComplete = actor.lockTarget != null;
  if (actor.handlerTimer <= MELEE_SAMURAI.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;
    actor.handlerTimer = cfg.timerFrames;
    computeLungeSpeed(actor, cfg.timerFrames);
  }
}

// Phase 2 — FUN_80149484 @ chunk_0038.c:2264.
function phase2(actor: RomActor & MeleeScratch, cfg: MeleeSamuraiConfig, ctx: StreamContext): void {
  if (actor.contactP0 === 0) {
    tickStream(actor, MELEE_SAMURAI.PART_MASK, ctx);
  }
  // Steer-yaw dive: hSpeed = motion.mag × cos(steerYaw); yVel = motion.mag × -sin(steerYaw).
  const mag = actor.motion.x; // +0x38 magnitude (the ROM reads *(float*)(+0x38))
  actor.hSpeed = mag * projectZ(actor.steerYaw);
  actor.yVel = mag * -projectX(actor.steerYaw);
  integratePhysics(MELEE_SAMURAI.GRAVITY, actor, actor.activeYaw);
  actor.handlerTimer -= actor.dt;
  const dist = targetDistance(actor);
  const inProximity = dist !== null && dist <= cfg.proximityRange;
  if (actor.handlerTimer <= MELEE_SAMURAI.TIMER_FLOOR || inProximity) {
    actor.fbPhaseSlots[0] += 1;
    const vs = cfg.velocityScale ?? 1.0;
    if (vs !== 1.0) {
      actor.hSpeed *= vs;
      actor.hDecel *= vs;
      actor.yVel *= vs;
      actor.gravityCoeff *= vs;
    }
  }
}

// Phase 3 — FUN_801495bc @ chunk_0038.c:2309.
function phase3(actor: RomActor & MeleeScratch, cfg: MeleeSamuraiConfig, ctx: StreamContext): void {
  tickStream(actor, MELEE_SAMURAI.PART_MASK, ctx);
  if (actor.velRefresh) {
    // velRefresh (+0x1d0f>0): recompute steer-yaw projection from the +0x38 magnitude.
    const mag = actor.motion.x;
    actor.hSpeed = mag * projectZ(actor.steerYaw);
    actor.yVel = mag * -projectX(actor.steerYaw);
  }
  const decel = cfg.decel ?? 1.0;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;
    actor.yVel *= decel;
  }
  integratePhysics(MELEE_SAMURAI.GRAVITY, actor, actor.activeYaw);
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 7);
  }
}

export function createMeleeSamurai(
  ctx: StreamContext,
  cfg: MeleeSamuraiConfig,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as RomActor & MeleeScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: phase0(a, cfg); break;
      case 1: phase1(a, cfg, ctx); break;
      case 2: phase2(a, cfg, ctx); break;
      case 3: phase3(a, cfg, ctx); break;
      default: break;
    }
  };
}

/** Default config matching the ROM power-on state (documented defaults from
 *  shared-engine.ts DEFAULT_CONFIGS.groundMelee until the per-family dig completes). */
export const SAMURAI_MELEE_DEFAULT_CONFIG: MeleeSamuraiConfig = {
  seedSlot: 0,
  timerFrames: 30,
  proximityRange: 100,
};
