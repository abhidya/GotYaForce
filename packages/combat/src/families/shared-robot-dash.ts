import type { RomActor, Vec3 } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const ROBOT_DASH = {
  DASH_TIMER: 30.0, // FLOAT_80439078; actor+0x560 phase-1 window
  STREAM_RATE: -1.0,
  ZERO: 0.0,
  AIM_DECAY: 0.9,
  ACTION_MODE_BITS: 0x3,
} as const;

export interface RobotDashConfig {
  slotBase: number;
  ammoSlot: number;
  timerSeed: number;
  maskByte: number;
  /** config+4/+8/+0x10 callback addresses (kept for host routing/provenance). */
  onContactAddr?: number;
  onContinueAddr?: number;
  onExitGateAddr?: number;
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
  /** actor+0x5d8 input/status bits; high nibble participates in phase-4 exit. */
  inputFlags5d8?: number;
}

/** DOL-read 0x14-byte config blocks passed to zz_00f1e30_. */
export const ROBOT_ACTION0_CONFIGS = {
  pl0400: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x80074d3c, onContinueAddr: 0x80074de0 },
  pl0401: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x8009b7bc, onContinueAddr: 0x8009b82c },
  pl0402: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x80112f28, onContinueAddr: 0x80112f80 },
  pl0403: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x800dfeec, onExitGateAddr: 0x800dff98 },
  pl0404: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x800d7fd8, onContinueAddr: 0x800d8024 },
  pl0405: { slotBase: 0, ammoSlot: 0, timerSeed: 4, maskByte: 5, onContactAddr: 0x800dabd8, onContinueAddr: 0x800dac44 },
  pl0407: { slotBase: 3, ammoSlot: 0, timerSeed: 4, maskByte: 5, onContactAddr: 0x80113010, onContinueAddr: 0x801130ac },
  pl0408: { slotBase: 3, ammoSlot: 0, timerSeed: 4, maskByte: 5, onContactAddr: 0x80113010, onContinueAddr: 0x801130ac },
  pl0409: { slotBase: 3, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x800dace8, onContinueAddr: 0x800dad40 },
  pl040a: { slotBase: 0, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x80074d3c, onContinueAddr: 0x80074de0 },
  pl040b: { slotBase: 0, ammoSlot: 2, timerSeed: -1, maskByte: -1, onContactAddr: 0x801d48cc, onExitGateAddr: 0x801d4978 },
  pl040c: { slotBase: 3, ammoSlot: 0, timerSeed: 4, maskByte: 5, onContactAddr: 0x801d49d8, onContinueAddr: 0x801d4a44 },
  pl040d: { slotBase: 6, ammoSlot: 0, timerSeed: -1, maskByte: -1, onContactAddr: 0x801d4ae8, onContinueAddr: 0x801d4b40 },
} as const satisfies Record<string, RobotDashConfig>;

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

function robotDashPhase0(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.dashTimer = ROBOT_DASH.DASH_TIMER;
  const cfg = s.dashConfig!;
  actor.handlerTimer = cfg.timerSeed;
  s.dashConfigByte = cfg.maskByte;
  actor.streamSlot = cfg.slotBase;
  if (!effLockTarget(actor)) s.dashTargetInvalid = true;
  s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
  startStream(actor, s.dashStreamMask, 2, cfg.slotBase, ROBOT_DASH.STREAM_RATE);
  void ctx;
}

function robotDashPhase1(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  s.dashTimer = (s.dashTimer ?? ROBOT_DASH.DASH_TIMER) - actor.dt;
  if (s.dashTimer <= ROBOT_DASH.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 1) + 1;
  }
}

function robotDashPhase2(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  if (actor.wallContact !== 0) {
    const cfg = s.dashConfig!;
    const resourceCtx = ctx as StreamContext & {
      onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
    };
    const ammoOk = resourceCtx.onAllocateResource?.(actor, cfg.ammoSlot, 1, 0) ?? true;
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

function robotDashPhase3(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    s.dashContactFlag = 1;
    s.dashConfig!.onPhase3Hit?.(actor);
    if (s.dashConfig!.onContactAddr) {
      ctx.onFamilyProjectile?.(actor, s.dashConfig!.onContactAddr, 0);
    }
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

function robotDashPhase4(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  const a = toS16(s.aimPitchP2a ?? 0);
  const b = toS16(s.aimPitchP2b ?? 0);
  s.aimPitchP2a = toS16(a * ROBOT_DASH.AIM_DECAY);
  s.aimPitchP2b = toS16(b * ROBOT_DASH.AIM_DECAY);
  tickStream(actor, 1, ctx);
  const exactExit = s.inputFlags5d8 === undefined ? false : (s.inputFlags5d8 & 0xf0) !== 0;
  const livenessExit = s.inputFlags5d8 === undefined && !isStreamActive(actor);
  if (exactExit || livenessExit || actor.wallContact !== 0) {
    s.dashHousekeep = 0;
    actor.controlWord &= ~ROBOT_DASH.ACTION_MODE_BITS;
    romGroundIdleReturn(actor);
  }
}

export function createRobotDashHandler(
  cfg: RobotDashConfig,
  ctx: StreamContext = {},
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
      case 0: robotDashPhase0(actor, ctx); break;
      case 1: robotDashPhase1(actor, ctx); break;
      case 2: robotDashPhase2(actor, ctx); break;
      case 3: robotDashPhase3(actor, ctx); break;
      case 4: robotDashPhase4(actor, ctx); break;
    }
  };
}
