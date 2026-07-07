import type { RomActor } from "../rom/actor.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { vecScale, vecAdd, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** ROM float constants for the magnet robot X-special (chunk_0023.c:1758-1832). */
export const MAGNET_ROBOT_X = {
  REPOSITION_SCALE: 0.95,
  STREAM_RATE: -1.0,
  ZERO: 0.0,
  CHILD_SPAWNER_ADDR: 0x800dd47c,
} as const;

function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

export interface MagnetRobotFamilyCtx extends StreamContext {}

// Phase 0 — FUN_800dafb4 @ chunk_0023.c:1746. Setup + reposition + stream start.
// Selects stream slot 0 (ground) or 2 (air), faces target, blinks away.
function magnetXPhase0(actor: RomActor, ctx: MagnetRobotFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;

  const slot = (actor.controlWord & 0x40) !== 0 ? 2 : 0;
  actor.streamSlot = slot;

  // zz_006d144_(actor, 0xc1) — face target + voice cue
  actor.activeYaw = actor.lockYaw;
  ctx.onPlayCue?.(actor, 0xc1);

  // Blink-reposition: motion = pos − target; motion ×= 0.95; pos += motion
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(MAGNET_ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, MAGNET_ROBOT_X.STREAM_RATE);
}

// Phase 1 — FUN_800db074 @ chunk_0023.c:1774. Fly + contact deploy + wall transition.
// Tick stream while motion decays; on part-0 contact (+) → borg-switched child deploy;
// on wall contact (+) → advance to phase 2 with decel stream slot.
function magnetXPhase1(actor: RomActor, ctx: MagnetRobotFamilyCtx): void {
  // zz_006d144_(actor, 0xc1) — face target + voice cue
  actor.activeYaw = actor.lockYaw;
  ctx.onPlayCue?.(actor, 0xc1);

  tickStream(actor, 0xf, ctx);

  // Decaying motion (phase 0's blink continues to decay each frame)
  vecScale(MAGNET_ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // CONTACT: part-0 contact byte → deploy magnet child (chunk_0023.c:1787-1797)
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    const addr = MAGNET_ROBOT_X.CHILD_SPAWNER_ADDR;
    const type = actor.borgNumber === 0x409 ? 1 : 0;
    ctx.onFamilyProjectile?.(actor, addr, type);
  }

  // WALL CONTACT: advance to phase 2, start decel stream (chunk_0023.c:1799-1808)
  if (actor.wallContact !== 0) {
    actor.fbPhaseSlots[0] = 2;
    const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
    const slot = grounded ? 1 : 3;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, MAGNET_ROBOT_X.STREAM_RATE);
  }
}

// Phase 2 — FUN_800db1a0 @ chunk_0023.c:1817. Recovery → wall-contact exit.
// Tick stream until wall contact; on contact → clear action bits, zero speed, exit.
function magnetXPhase2(actor: RomActor, ctx: MagnetRobotFamilyCtx): void {
  tickStream(actor, 0xf, ctx);

  vecScale(MAGNET_ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  if (actor.wallContact !== 0) {
    (actor as RomActor & { wallImpactFlag?: number }).wallImpactFlag = 0;
    actor.controlWord &= ~0x3;
    actor.hDecel = MAGNET_ROBOT_X.ZERO;
    actor.hSpeed = MAGNET_ROBOT_X.ZERO;
    if (actor.descriptor) {
      actor.gravityCoeff = actor.descriptor.handlerData6c;
    }
    if ((actor.controlWord & 0x40) === 0) {
      romGroundIdleReturn(actor);
    } else {
      romAirKnockoutReturn(actor);
    }
  }
}

/** Create the magnet robot X-special dispatcher (table 0x80311ca4). */
function createMagnetRobotXHandler(ctx: MagnetRobotFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    switch (actor.fbPhaseSlots[0]) {
      case 0: magnetXPhase0(actor, ctx); break;
      case 1: magnetXPhase1(actor, ctx); break;
      case 2: magnetXPhase2(actor, ctx); break;
    }
  };
}

export function createMagnetRobotRootAction(ctx: MagnetRobotFamilyCtx): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                               // 0: dash attack — injected by withRobotDash in bridge.ts
    null,                               // 1: B-tap melee — TODO port
    createMagnetRobotXHandler(ctx),      // 2: X-special magnet-suck-in deploy
    null,                               // 3: B charge — TODO port
    null,                               // 4: — TODO port
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

export function configureMagnetRobotFamily(
  actor: RomActor,
  borgId: "pl0405" | "pl0409",
  ctx: MagnetRobotFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl0405" ? 0x405 : 0x409;
  actor.rootAction = createMagnetRobotRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
