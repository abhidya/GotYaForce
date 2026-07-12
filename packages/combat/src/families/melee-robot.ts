// Bespoke B-melee engine zz_00f2374_ @0x800f2374 — the 3-phase melee machine shared by
// 12 "robot"/"death-borg-omega" borgs (variant 0 of action 1). Source:
//   research/decomp/ghidra-export/chunk_0026.c:2263 (dispatcher zz_00f2374_)
//   chunk_0026.c:2277 (phase 0 setup FUN_800f23c4)
//   chunk_0026.c:2309 (phase 1 pre-active FUN_800f2498)
//   chunk_0026.c:2346 (phase 2 active/combo/recovery FUN_800f259c)
//
// 3-phase (NOT 4): phase 2 fuses the active frames, the combo-continue check, and the
// recovery tail into one handler (the +0x1cf0/+0x746 combo gate branches inline).
// References phase table PTR_FUN_8031b8b4.
//
// Borgs covered (action 1 variant 0): pl0400, pl0401, pl0402, pl0403, pl0404, pl0405,
// pl0406, pl0407, pl0408, pl0409, pl040a, pl040b.
//
// Float constants (FLOAT_804390xx bank, DOL-read):
//   FLOAT_80439090 = timer seed (phase 0 +0x558)
//   FLOAT_80439094 = active-window timer (phase 1 transition + phase 2 combo)
//   FLOAT_80439088 = 0.0 floor / +0x4c zero
//   FLOAT_8043907c = -1.0 stream rate
//   FLOAT_80439098 = speed scalar multiplier (the +0x760 current-speed coefficient)
//   FLOAT_8043909c = proximity-continue threshold
//   FLOAT_804390a0 = recovery decel
//   FLOAT_804390a4 = speed threshold (zz_00b22f4_ gate)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const MELEE_ROBOT = {
  TIMER_SEED: 60.0,      // FLOAT_80439090
  ACTIVE_TIMER: 30.0,    // FLOAT_80439094
  STREAM_RATE: -1.0,     // FLOAT_8043907c
  TIMER_FLOOR: 0.0,      // FLOAT_80439088
  SPEED_COEFF: 1.0,      // FLOAT_80439098
  PROX_CONT_THOLD: 0.0,  // FLOAT_8043909c
  RECOVERY_DECEL: 1.0,   // FLOAT_804390a0
  SPEED_THRESHOLD: 0.0,  // FLOAT_804390a4
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  STATE_FACE: 0xc0,
} as const;

export interface MeleeRobotConfig {
  seedSlot?: number;
  activeTimer?: number;
}

interface MeleeScratch {
  bRetap?: boolean;
  bRetapInput?: boolean;
  swingReArm?: boolean;
  faceTarget?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  /** +0x1b03 part-animation hold byte; undefined keeps the host liveness fallback. */
  streamTickGate?: boolean;
  /** actor+0x868/+0x874/+0x880, selected by previous action index modulo three. */
  rangeRows868?: readonly [number, number, number];
}

function targetDistance(actor: RomActor & MeleeScratch): number | null {
  const target = actor.lockTarget;
  if (!target) return null;
  return Math.hypot(target.x - actor.pos.x, target.z - actor.pos.z);
}

/** FUN_800f2498 transition velocity. +0xcc==0 uses the selected +0x868 row;
 *  +0xcc!=0 uses FLOAT_80439098(1.0) * +0x760, both divided by +0x558(30). */
function setTransitionSpeed(actor: RomActor & MeleeScratch, timer: number): number {
  if (timer <= 0) return 0;
  const dist = targetDistance(actor);
  if (dist !== null) {
    actor.hSpeed = dist / timer;
    return dist;
  }
  const row = ((actor.prevActionIndex % 3) + 3) % 3;
  const range = actor.rangeRows868?.[row] ?? 50.0;
  actor.hSpeed = range / timer;
  return range;
}

// Phase 0 — FUN_800f23c4 @ chunk_0026.c:2277.
function phase0(actor: RomActor & MeleeScratch, cfg: Required<MeleeRobotConfig>): void {
  actor.fbPhaseSlots[0] += 1;
  actor.handlerTimer = MELEE_ROBOT.TIMER_SEED;
  actor.streamSlot = cfg.seedSlot;
  actor.bRetap = false;
  if (!actor.grounded) {
    actor.activeYaw = actor.heading;
    actor.lockYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(
    actor,
    MELEE_ROBOT.PART_MASK,
    MELEE_ROBOT.STREAM_GROUP,
    slot,
    MELEE_ROBOT.STREAM_RATE,
  );
}

// Phase 1 — FUN_800f2498 @ chunk_0026.c:2309.
function phase1(actor: RomActor & MeleeScratch, cfg: Required<MeleeRobotConfig>, ctx: StreamContext): void {
  // ROM gate is +0x1b03 != 0. The bridge does not stamp it for every family yet;
  // undefined retains the old liveness behavior, while an explicit false is exact.
  if (actor.streamTickGate ?? true) tickStream(actor, MELEE_ROBOT.PART_MASK, ctx);
  actor.handlerTimer -= actor.dt;
  const facingComplete = actor.lockTarget != null;
  if (actor.handlerTimer <= MELEE_ROBOT.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;
    actor.handlerTimer = cfg.activeTimer;
    const speedSource = setTransitionSpeed(actor, cfg.activeTimer);
    actor.hDecel = MELEE_ROBOT.TIMER_FLOOR;
    if (speedSource > MELEE_ROBOT.SPEED_THRESHOLD) {
      ctx.onFamilyProjectile?.(actor, 0x800b2190, 0);
    }
  }
}

// Phase 2 — FUN_800f259c @ chunk_0026.c:2346 (active + combo + recovery fused).
function phase2(actor: RomActor & MeleeScratch, cfg: Required<MeleeRobotConfig>, ctx: StreamContext): void {
  if (actor.bRetapInput) actor.bRetap = true;
  // Combo-continue: +0x1cf0<0 (swingReArm) AND +0x746 (bRetap) → replay next slot.
  if (actor.swingReArm && actor.bRetap) {
    actor.bRetap = false;
    actor.handlerTimer = cfg.activeTimer;
    setTransitionSpeed(actor, cfg.activeTimer);
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(
      actor,
      MELEE_ROBOT.PART_MASK,
      MELEE_ROBOT.STREAM_GROUP,
      slot,
      MELEE_ROBOT.STREAM_RATE,
    );
    return;
  }
  // Active/recovery frames.
  tickStream(actor, MELEE_ROBOT.PART_MASK, ctx);
  const decel = MELEE_ROBOT.RECOVERY_DECEL;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;
    actor.yVel *= decel;
  }
  integratePhysics(0, actor, actor.activeYaw);
  if (actor.faceTarget) {
    // zz_006d144_(actor, 0xc0) — face target (bridge pre-aims lockYaw).
  }
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 0);
  }
}

export function createMeleeRobot(
  ctx: StreamContext,
  cfg: MeleeRobotConfig = {},
): (actor: RomActor) => void {
  const resolved: Required<MeleeRobotConfig> = {
    seedSlot: cfg.seedSlot ?? 0,
    activeTimer: cfg.activeTimer ?? MELEE_ROBOT.ACTIVE_TIMER,
  };
  return (actor: RomActor) => {
    const a = actor as RomActor & MeleeScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: phase0(a, resolved); break;
      case 1: phase1(a, resolved, ctx); break;
      case 2: phase2(a, resolved, ctx); break;
      default: break;
    }
  };
}
