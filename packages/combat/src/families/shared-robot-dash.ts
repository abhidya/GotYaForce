import type { RomActor, Vec3 } from "../rom/actor.js";
import { allocateWeapon, partState, stepDualTargetAim, toS16 } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const ROBOT_DASH = {
  DASH_TIMER: 30.0, // FLOAT_80439078; actor+0x560 phase-1 window
  STREAM_RATE: -1.0,
  ZERO: 0.0,
  AIM_DECAY: 0.96, // FLOAT_8043908c
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
  /** actor+0x18e0/+0x18e2, the exact pair written by stepDualTargetAim. */
  aimPitch18e0?: number;
  aimYaw18e2?: number;
  /** actor+0x5d8 input/status bits; high nibble participates in phase-4 exit. */
  inputFlags5d8?: number;
  /** +0x5bc bit 0x200: held-action continuation status. */
  statusWord5bc?: number;
  /** Actor-local child ownership bytes +0x144 onward. Child death clears these. */
  robotSlotFlags?: number[];
  /** Independent rotating child indices at +0x146 and +0x148. */
  robotCursor146?: number;
  robotCursor148?: number;
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

function streamComplete(actor: RomActor): boolean {
  // FUN_800f2008/2118/22a8 gate directly on actor+0x1cee. The stream VM and
  // bridge lower/raise this modeled byte at real stream start/completion.
  return actor.wallContact !== 0;
}

function spawn(ctx: StreamContext, actor: RomActor, addr: number, ...types: number[]): void {
  for (const type of types) ctx.onFamilyProjectile?.(actor, addr, type);
}

function slotFlags(s: RobotDashScratch): number[] {
  return s.robotSlotFlags ??= [0, 0, 0, 0];
}

/** Decoded config+4 callbacks. Every callback performs its own consuming ammo check. */
function runContactCallback(actor: RomActor, ctx: StreamContext, cfg: RobotDashConfig): void {
  const s = scratchOf(actor);
  const addr = cfg.onContactAddr;
  if (!addr) return;
  // Timed/count callbacks mutate +0x558/+0x6ef before their consuming ammo call.
  const timed = addr === 0x800dabd8 || addr === 0x80113010 || addr === 0x801d49d8;
  if (timed) {
    actor.handlerTimer = 4;
    s.dashConfigByte = (s.dashConfigByte ?? 0) - 1;
  }
  if (!allocateWeapon(actor, ctx, cfg.ammoSlot, 1, true)) return;
  switch (addr) {
    case 0x80074d3c: {
      const cursor = s.robotCursor148 ?? 0;
      const type = actor.borgNumber === 0x40a ? cursor + 4 : cursor;
      spawn(ctx, actor, 0x8007f29c, type);
      slotFlags(s)[cursor] = 1;
      s.robotCursor148 = toS16(cursor + 1) & 0xff;
      break;
    }
    case 0x8009b7bc: {
      const cursor = s.robotCursor146 ?? 0;
      spawn(ctx, actor, 0x8009ad20, cursor);
      slotFlags(s)[cursor] = 1;
      s.robotCursor146 = toS16(cursor + 1) & 0xff;
      break;
    }
    case 0x80112f28: spawn(ctx, actor, 0x800c3be0, 0x0c, 0x0d); break;
    case 0x800d7fd8: spawn(ctx, actor, 0x800c3be0, 0x0a); break;
    case 0x800dabd8:
      spawn(ctx, actor, 0x80082824, 0x20, 0x21);
      break;
    case 0x80113010:
      if (actor.borgNumber === 0x408) spawn(ctx, actor, 0x80082824, 0x47, 0x48);
      else if (actor.borgNumber === 0x407) spawn(ctx, actor, 0x80082824, 0x78, 0x79);
      break;
    case 0x800dace8: spawn(ctx, actor, 0x800c3be0, 0x39, 0x3a); break;
    case 0x801d49d8:
      spawn(ctx, actor, 0x80082824, 0x73, 0x74);
      break;
    case 0x801d4ae8: spawn(ctx, actor, 0x800c3be0, 0x5f, 0x60); break;
    case 0x800dfeec:
    case 0x801d48cc: {
      const flags = slotFlags(s);
      let made = 0;
      const typeBase = addr === 0x801d48cc ? 2 : 0;
      for (let i = 0; i < 2; i++) {
        if (flags[i] !== 0) continue;
        flags[i] = 1;
        spawn(ctx, actor, 0x800e0e90, typeBase + i);
        made++;
      }
      if (made !== 0) ctx.onPlayCue?.(actor, 0xdb);
      break;
    }
  }
}

/** Decoded config+8 callbacks: signed part-1 state, ammo, input, or timed burst gate. */
function runContinueCallback(actor: RomActor, ctx: StreamContext, cfg: RobotDashConfig): boolean {
  const s = scratchOf(actor);
  if (!cfg.onContinueAddr) return false;
  if (cfg.onContinueAddr === 0x800dac44
      || cfg.onContinueAddr === 0x801130ac
      || cfg.onContinueAddr === 0x801d4a44) {
    if (actor.handlerTimer > 0) {
      actor.handlerTimer -= actor.dt;
      return false;
    }
    return allocateWeapon(actor, ctx, 0, 1, false) && (s.dashConfigByte ?? 0) > 0;
  }
  return partState(actor, 1) < 0
    && allocateWeapon(actor, ctx, 0, 1, false)
    && ((s.statusWord5bc ?? 0) & 0x200) !== 0;
}

function exitGateAllows(actor: RomActor, cfg: RobotDashConfig): boolean {
  if (!cfg.onExitGateAddr) return true;
  const flags = slotFlags(scratchOf(actor));
  return flags[0] === 0 && flags[1] === 0;
}

function robotDashPhase0(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.dashTimer = ROBOT_DASH.DASH_TIMER;
  const cfg = s.dashConfig!;
  actor.handlerTimer = cfg.timerSeed;
  s.dashConfigByte = cfg.maskByte;
  actor.streamSlot = cfg.slotBase;
  if (!allocateWeapon(actor, ctx, cfg.ammoSlot, 1, false)) s.dashTargetInvalid = true;
  if (!effLockTarget(actor)) s.dashTargetInvalid = true;
  stepDualTargetAim(actor);
  s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
  startStream(actor, s.dashStreamMask, 2, cfg.slotBase, ROBOT_DASH.STREAM_RATE);
}

function robotDashPhase1(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  s.dashTimer = (s.dashTimer ?? ROBOT_DASH.DASH_TIMER) - actor.dt;
  if (s.dashTimer <= ROBOT_DASH.ZERO || stepDualTargetAim(actor) !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 1) + 1;
  }
}

function robotDashPhase2(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  stepDualTargetAim(actor);
  if (streamComplete(actor)) {
    const cfg = s.dashConfig!;
    const ammoOk = allocateWeapon(actor, ctx, cfg.ammoSlot, 1, false);
    if (ammoOk) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 2) + 1;
      s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
      startStream(actor, s.dashStreamMask, 2, cfg.slotBase + 1, ROBOT_DASH.STREAM_RATE);
    } else {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 2) + 2;
      s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
      startStream(actor, s.dashStreamMask, 2, cfg.slotBase + 2, ROBOT_DASH.STREAM_RATE);
    }
  }
}

function robotDashPhase3(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx);
  stepDualTargetAim(actor);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    s.dashContactFlag = 1;
    s.dashConfig!.onPhase3Hit?.(actor);
    runContactCallback(actor, ctx, s.dashConfig!);
  }
  const lockValid = !s.dashTargetInvalid;
  const continueRequested = s.dashConfig!.onPhase3LockCheck?.(actor)
    ?? runContinueCallback(actor, ctx, s.dashConfig!);
  if (lockValid && continueRequested) {
    s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
    startStream(actor, s.dashStreamMask, 2, s.dashConfig!.slotBase + 1, ROBOT_DASH.STREAM_RATE);
    return;
  }
  const inputExit = (s.inputFlags5d8 ?? 0) & 0xf0;
  const shouldExit = ((s.dashContactFlag ?? 0) > 0 && inputExit !== 0) || streamComplete(actor);
  if (shouldExit && exitGateAllows(actor, s.dashConfig!)) {
    if (s.dashConfig!.onPhase3WallContact && !s.dashConfig!.onPhase3WallContact(actor)) return;
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 3) + 1;
    s.dashStreamMask = actor.ubState === 1 ? 0xf : 1;
    startStream(actor, s.dashStreamMask, 2, s.dashConfig!.slotBase + 2, ROBOT_DASH.STREAM_RATE);
  }
}

function robotDashPhase4(actor: RomActor, ctx: StreamContext): void {
  const s = scratchOf(actor);
  const pitch = toS16(s.aimPitch18e0 ?? 0);
  const yaw = toS16(s.aimYaw18e2 ?? 0);
  s.aimPitch18e0 = toS16(pitch * ROBOT_DASH.AIM_DECAY);
  s.aimYaw18e2 = toS16(yaw * ROBOT_DASH.AIM_DECAY);
  tickStream(actor, 1, ctx);
  const exactExit = ((s.inputFlags5d8 ?? 0) & 0xf0) !== 0;
  if (exactExit || streamComplete(actor)) {
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
