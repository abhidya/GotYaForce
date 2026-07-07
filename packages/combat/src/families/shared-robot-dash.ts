import type { RomActor, Vec3 } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const ROBOT_DASH = {
  DASH_TIMER: 20.0,
  STREAM_RATE: -1.0,
  ZERO: 0.0,
  AIM_DECAY: 0.9,
  ACTION_MODE_BITS: 0x3,
} as const;

export interface RobotDashConfig {
  slotBase: number;
  rangeRow: number;
  ammoSlot: number;
  timerSeed: number;
  maskByte: number;
  onPhase3Hit?: (actor: RomActor) => void;
  onPhase3LockCheck?: (actor: RomActor) => boolean;
  onPhase3WallContact?: (actor: RomActor) => boolean;
}

interface RobotDashScratch {
  lockTarget?: Vec3 | null;
  grounded?: boolean;
  dashTargetInvalid?: boolean;
  dashContactFlag?: number;
  dashStreamMask?: number;
  dashTimer?: number;
  dashConfigByte?: number;
  dashHousekeep?: number;
  dashConfig?: RobotDashConfig;
  aimPitchP2a?: number;
  aimPitchP2b?: number;
}

function scratchOf(actor: RomActor): RomActor & RobotDashScratch {
  return actor as RomActor & RobotDashScratch;
}

function effLockTarget(actor: RomActor): Vec3 | null {
  const s = scratchOf(actor);
  if (s.dashTargetInvalid) return null;
  return s.lockTarget ?? null;
}

function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

function isStreamActive(actor: RomActor): boolean {
  return actor.parts.some(p => p.active !== 0);
}

function robotDashPhase0(actor: RomActor): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.dashTimer = ROBOT_DASH.DASH_TIMER;
  const cfg = s.dashConfig!;
  actor.handlerTimer = cfg.timerSeed;
  s.dashConfigByte = cfg.maskByte;
  actor.streamSlot = cfg.slotBase;
  const target = effLockTarget(actor);
  const rangeRows: number[] = [800.0, 1000.0, 1200.0, 1500.0];
  const range = rangeRows[cfg.rangeRow % rangeRows.length] ?? 800.0;
  if (target) {
    const dx = target.x - actor.pos.x;
    const dz = target.z - actor.pos.z;
    if (Math.hypot(dx, dz) > range) {
      s.dashTargetInvalid = true;
    }
  } else {
    s.dashTargetInvalid = true;
  }
  s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
  startStream(actor, s.dashStreamMask, 2, cfg.slotBase, ROBOT_DASH.STREAM_RATE);
}

function robotDashPhase1(actor: RomActor): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, {} as StreamContext);
  s.dashTimer = (s.dashTimer ?? ROBOT_DASH.DASH_TIMER) - actor.dt;
  if (s.dashTimer <= ROBOT_DASH.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 1) + 1;
  }
}

function robotDashPhase2(actor: RomActor): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, {} as StreamContext);
  if (actor.wallContact !== 0) {
    const cfg = s.dashConfig!;
    const ammoOk = true;
    if (ammoOk) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 2) + 2;
      s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
      startStream(actor, s.dashStreamMask, 2, cfg.slotBase + 2, ROBOT_DASH.STREAM_RATE);
    } else {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 2) + 1;
      startStream(actor, 1, 2, cfg.slotBase + 1, ROBOT_DASH.STREAM_RATE);
    }
  }
}

function robotDashPhase3(actor: RomActor): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, {} as StreamContext);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    s.dashContactFlag = 1;
    s.dashConfig!.onPhase3Hit?.(actor);
  }
  const lockValid = !s.dashTargetInvalid;
  if (lockValid && s.dashConfig!.onPhase3LockCheck?.(actor)) {
    s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
    startStream(actor, s.dashStreamMask, 2, s.dashConfig!.slotBase + 1, ROBOT_DASH.STREAM_RATE);
    return;
  }
  const streamActive = isStreamActive(actor);
  const contactOrWall = ((s.dashContactFlag ?? 0) > 0 && streamActive) || actor.wallContact !== 0;
  if (contactOrWall) {
    if (s.dashConfig!.onPhase3WallContact && !s.dashConfig!.onPhase3WallContact(actor)) return;
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 3) + 1;
    s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
    startStream(actor, s.dashStreamMask, 2, s.dashConfig!.slotBase + 2, ROBOT_DASH.STREAM_RATE);
  }
}

function robotDashPhase4(actor: RomActor): void {
  const s = scratchOf(actor);
  const a = toS16(s.aimPitchP2a ?? 0);
  const b = toS16(s.aimPitchP2b ?? 0);
  s.aimPitchP2a = toS16(a * ROBOT_DASH.AIM_DECAY);
  s.aimPitchP2b = toS16(b * ROBOT_DASH.AIM_DECAY);
  tickStream(actor, 1, {} as StreamContext);
  if (!isStreamActive(actor) || actor.wallContact !== 0) {
    s.dashHousekeep = 0;
    actor.controlWord &= ~ROBOT_DASH.ACTION_MODE_BITS;
    romGroundIdleReturn(actor);
  }
}

export function createRobotDashHandler(
  cfg: RobotDashConfig,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const s = scratchOf(actor);
    s.dashConfig = cfg;
    if (!actor.fbPhaseSlots[0]) {
      s.dashTargetInvalid = false;
      s.dashContactFlag = 0;
      s.dashStreamMask = 1;
      s.dashTimer = ROBOT_DASH.DASH_TIMER;
      s.dashConfigByte = cfg.maskByte;
      s.dashHousekeep = 0;
    }
    if (!effLockTarget(actor)) {
      s.dashTargetInvalid = true;
    }
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: robotDashPhase0(actor); break;
      case 1: robotDashPhase1(actor); break;
      case 2: robotDashPhase2(actor); break;
      case 3: robotDashPhase3(actor); break;
      case 4: robotDashPhase4(actor); break;
    }
  };
}
