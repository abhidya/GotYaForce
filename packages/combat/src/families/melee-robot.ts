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
import { isStreamTickEnabled, stepTargetYaw } from "../rom/helpers.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const MELEE_ROBOT = {
  TIMER_SEED: 60.0,      // FLOAT_80439090
  ACTIVE_TIMER: 20.0,    // FLOAT_80439094
  STREAM_RATE: -1.0,     // FLOAT_8043907c
  TIMER_FLOOR: 0.0,      // FLOAT_80439088
  SPEED_COEFF: 2.0,      // FLOAT_80439098
  PROX_CONT_THOLD: 150.0,// FLOAT_8043909c
  RECOVERY_DECEL: 0.9,   // FLOAT_804390a0
  SPEED_THRESHOLD: 3.0,  // FLOAT_804390a4
  MELEE_FX_ADDR: 0x800b2190,
  DISTANCE_TRAIL_HELPER_ADDR: 0x800b22f4,
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  STATE_FACE: 0xc0,
} as const;

/** Per-member movement-page rows copied by the actor initializer:
 * page +0x134/+0x140/+0x14c -> actor +0x868/+0x874/+0x880
 * (chunk_0007.c:32-38). Values were read big-endian from the GG4E
 * pl0400data.bin..pl040bdata.bin pages. */
export const ROBOT_MELEE_RANGE_ROWS = {
  pl0400: [1000, 1000, 2500],
  pl0401: [1000, 1000, 2000],
  pl0402: [1000, 1000, 1000],
  pl0403: [1000, 1000, 1000],
  pl0404: [1000, 1000, 1000],
  pl0405: [1000, 1000, 1000],
  pl0406: [1000, 1000, 2500],
  pl0407: [1000, 1000, 2500],
  pl0408: [1000, 1000, 1000],
  pl0409: [1000, 1000, 1000],
  pl040a: [1000, 1000, 2500],
  pl040b: [1000, 1000, 1000],
} as const satisfies Record<string, readonly [number, number, number]>;

export interface MeleeRobotConfig {
  seedSlot?: number;
  activeTimer?: number;
  /** movement page +0x134/+0x140/+0x14c copied to actor +0x868/+0x874/+0x880. */
  rangeRows868: readonly [number, number, number];
}

interface MeleeScratch {
  bRetap?: boolean;
  bRetapInput?: boolean;
  swingReArm?: boolean;
  faceTarget?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  /** actor+0x868/+0x874/+0x880, selected by previous action index modulo three. */
  rangeRows868?: readonly [number, number, number];
  /** actor+0x760, maintained by the host target-distance update. */
  targetDistance760?: number;
  /** actor+0xb4 scale used by FUN_80066838's initial range test. */
  sizeScaleB4?: number;
  /** actor+0x1dd bit 0x80 makes FUN_80066838 accept the target unconditionally. */
  farDistanceBypass?: boolean;
  /** actor+0x1d9b, cleared once the target is within 150 units. */
  movementTrailFlag1d9b?: number;
}

function geometricTargetDistance(actor: RomActor & MeleeScratch): number | null {
  const target = actor.lockTarget;
  if (!target) return null;
  return Math.hypot(
    target.x - actor.pos.x,
    target.y - actor.pos.y,
    target.z - actor.pos.z,
  );
}

function horizontalTargetDistance(actor: RomActor & MeleeScratch): number {
  const target = actor.lockTarget;
  if (!target) return 0;
  return Math.hypot(target.x - actor.pos.x, target.z - actor.pos.z);
}

function targetDistance760(actor: RomActor & MeleeScratch): number {
  return actor.targetDistance760 ?? geometricTargetDistance(actor) ?? 0;
}

/** FUN_80066838(rangeRow, actor): no target/far target invalidates actor+0xcc. */
function targetWithinInitialRange(
  actor: RomActor & MeleeScratch,
  rangeRows868: readonly [number, number, number],
): boolean {
  if (!actor.lockTarget) return false;
  if (actor.farDistanceBypass) return true;
  const row = ((actor.prevActionIndex % 3) + 3) % 3;
  const range = rangeRows868[row]!;
  return horizontalTargetDistance(actor) <= range * (actor.sizeScaleB4 ?? 1);
}

/** FUN_800f2498 transition velocity. +0xcc==0 uses the selected +0x868 row;
 *  +0xcc!=0 uses FLOAT_80439098(2.0) * +0x760, both divided by +0x558(20). */
function setTransitionSpeed(
  actor: RomActor & MeleeScratch,
  timer: number,
  rangeRows868: readonly [number, number, number],
): void {
  if (timer <= 0) return;
  if (actor.lockTarget) {
    actor.hSpeed = (MELEE_ROBOT.SPEED_COEFF * targetDistance760(actor)) / timer;
    return;
  }
  const row = ((actor.prevActionIndex % 3) + 3) % 3;
  const range = rangeRows868[row]!;
  actor.hSpeed = range / timer;
}

function spawnLaunchFxIfFar(actor: RomActor & MeleeScratch, ctx: StreamContext): void {
  if (targetDistance760(actor) > MELEE_ROBOT.PROX_CONT_THOLD) {
    ctx.onFamilyProjectile?.(actor, MELEE_ROBOT.MELEE_FX_ADDR, 0);
  }
}

// Phase 0 — FUN_800f23c4 @ chunk_0026.c:2277.
function phase0(actor: RomActor & MeleeScratch, cfg: Required<MeleeRobotConfig>): void {
  actor.fbPhaseSlots[0] += 1;
  actor.handlerTimer = MELEE_ROBOT.TIMER_SEED;
  actor.streamSlot = cfg.seedSlot;
  actor.bRetap = false;
  if (!targetWithinInitialRange(actor, cfg.rangeRows868)) {
    actor.lockTarget = null;
  }
  stepTargetYaw(actor, MELEE_ROBOT.STATE_FACE);
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
  if (isStreamTickEnabled(actor)) tickStream(actor, MELEE_ROBOT.PART_MASK, ctx);
  actor.handlerTimer -= actor.dt;
  const facingComplete = stepTargetYaw(actor, MELEE_ROBOT.STATE_FACE);
  if (actor.handlerTimer <= MELEE_ROBOT.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;
    actor.handlerTimer = cfg.activeTimer;
    setTransitionSpeed(actor, cfg.activeTimer, cfg.rangeRows868);
    actor.hDecel = MELEE_ROBOT.TIMER_FLOOR;
    spawnLaunchFxIfFar(actor, ctx);
  }
}

// Phase 2 — FUN_800f259c @ chunk_0026.c:2346 (active + combo + recovery fused).
function phase2(actor: RomActor & MeleeScratch, cfg: Required<MeleeRobotConfig>, ctx: StreamContext): void {
  if (actor.bRetapInput) actor.bRetap = true;
  // Combo-continue: +0x1cf0<0 (swingReArm) AND +0x746 (bRetap) → replay next slot.
  if (actor.swingReArm && actor.bRetap) {
    actor.bRetap = false;
    actor.handlerTimer = cfg.activeTimer;
    setTransitionSpeed(actor, cfg.activeTimer, cfg.rangeRows868);
    actor.hDecel = MELEE_ROBOT.TIMER_FLOOR;
    spawnLaunchFxIfFar(actor, ctx);
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
  if (actor.handlerTimer > MELEE_ROBOT.TIMER_FLOOR) {
    actor.handlerTimer -= actor.dt;
    if (targetDistance760(actor) <= MELEE_ROBOT.PROX_CONT_THOLD) {
      actor.movementTrailFlag1d9b = 0;
    } else {
      actor.hSpeed *= MELEE_ROBOT.RECOVERY_DECEL;
      actor.yVel *= MELEE_ROBOT.RECOVERY_DECEL;
      integratePhysics(0, actor, actor.activeYaw);
    }
  }
  if (actor.faceTarget) {
    stepTargetYaw(actor, MELEE_ROBOT.STATE_FACE);
  }
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
  if (actor.hSpeed > MELEE_ROBOT.SPEED_THRESHOLD) {
    ctx.onFamilyProjectile?.(actor, MELEE_ROBOT.DISTANCE_TRAIL_HELPER_ADDR, 0);
  }
}

export function createMeleeRobot(
  ctx: StreamContext,
  cfg: MeleeRobotConfig,
): (actor: RomActor) => void {
  const resolved = {
    seedSlot: cfg.seedSlot ?? 0,
    activeTimer: cfg.activeTimer ?? MELEE_ROBOT.ACTIVE_TIMER,
    rangeRows868: cfg.rangeRows868,
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
