// Exact constructor routing and evidence-backed live leaves for the Machine Red
// (0x800c91bc) and Machine Blue (0x800ce730) clusters. These constructors share
// visual themes, not action tables: never alias either root to DEFAULT_CONFIGS.

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { groundClamp, integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { stepPartTargetPitch, stepTargetYaw, toS16 } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import {
  createSharedAimedShotX,
  machineBlueXOnSteer,
  MACHINE_BLUE_X_CONFIG,
} from "./shared-aimed-shot-x.js";

export type MachineRedBorgId = "pl0600" | "pl0608" | "pl0616" | "pl061c";
export type MachineBlueBorgId = "pl0601" | "pl0609" | "pl0617" | "pl061d";

export interface MachineFamilyCtx extends StreamContext {
  onMachineRoute?: (actor: RomActor, leafAddress: number) => void;
  /** Exact zz_013212c_ third-argument identity: actor byte record +0x14c+index.
   * The host still lacks the callee's mutation contract, so the byte itself remains
   * bridge-owned and the affected actions stay partial. */
  onMachineHardpointDeploy?: (actor: RomActor, spawnerAddress: number, type: number, hardpointIndex: number) => void;
}

/** boot.dol pointer tables, retained as executable documentation and test seams. */
export const MACHINE_RED_ROUTES = {
  root: 0x800c94d4,
  actionTable: 0x8030a558,
  actions: [0x800c9510, 0x800ca034, 0x800cb9d4],
  variants: [
    [0x800c9590, 0x800c997c, 0x800c997c, 0x800c997c, 0x800c9d44, 0x800c95d8],
    [0x800ca5dc, 0x800cb3c8, 0x800cb394, 0x800caddc, 0x800cb424, 0x800ca070],
    [0x800cba10, 0x800cba10, 0x800cba10, 0x800cba10, 0x800cba10],
  ],
} as const;

export const MACHINE_BLUE_ROUTES = {
  root: 0x800cea5c,
  actionTable: 0x8030ce34,
  actions: [0x800cea98, 0x800cf884, 0x800cf990, 0x800cfb94, 0x800cfc38],
  variants: [
    [0x800ceae0, 0x800cef38, 0x800cef38, 0x800cef38, 0x800cf300],
    [0x800cf8c0, 0x800cf8f4, 0x800cf928, 0x800cf968, 0x800cf968],
    [0x800cf9cc, 0x800cf9cc, 0x800cf9cc, 0x800cf9cc, 0x800cf9cc],
    [0x800cfb94, 0x800cfb94, 0x800cfb94, 0x800cfb94, 0x800cfb94],
    [0x800cfc74, 0x800cfc74, 0x800cfc74, 0x800cfdf0, 0x800cfdf0],
  ],
} as const;

export const MACHINE_RED_X = {
  ENGINE: 0x80179d20,
  PHASE_TABLE: 0x804347a8,
  PHASES: [0x80179d58, 0x80179e60],
  CONFIG: 0x8030a66c,
  SLOT: 0,
  REPOSITION_SCALE: 0.949999988079071,
  STREAM_RATE: -1,
  RISE_YVEL: 4,
  PROJECTILE_SPAWNER: 0x8016cc24,
  COOLDOWN: 30,
} as const;

export const MACHINE_BLUE_DEPLOY = {
  SPAWNER: 0x8013212c,
  BLUE_BASE: 2,
  ATLAS_BASE: 10,
  STREAM_SLOT: 2,
  REPOSITION_SCALE: 0.949999988079071,
  STREAM_RATE: -1,
  STATEFUL_COOLDOWN: 4,
  IMMEDIATE_COOLDOWN: 1,
} as const;

type MachineActor = RomActor & {
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
};

function machineRedProjectileType(actor: RomActor): number | null {
  switch (actor.borgNumber) {
    case 0x600: return 0;
    case 0x608: return 0x0c;
    case 0x616: return 0x0d;
    case 0x61c: return 0x0e;
    default: return null;
  }
}

/** FUN_800cba38: ammo-gated projectile deployment followed by the exact rise seed. */
function machineRedXSetupCallback(actor: MachineActor, ctx: MachineFamilyCtx): void {
  const allowed = ctx.onAllocateResource?.(actor, 2, 1, 1) ?? false;
  if (!allowed) actor.fbPhaseSlots[1] = ((actor.fbPhaseSlots[1] ?? 0) + 1) & 0xff;
  else {
    const type = machineRedProjectileType(actor);
    if (type !== null) ctx.onFamilyProjectile?.(actor, MACHINE_RED_X.PROJECTILE_SPAWNER, type);
  }
  actor.hDecel = 0;
  actor.hSpeed = 0;
  actor.yVel = MACHINE_RED_X.RISE_YVEL;
  actor.gravityCoeff = 0;
}

function machineRedX(actor: MachineActor, ctx: MachineFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) {
    actor.fbPhaseSlots[0] = 1;
    actor.fbPhaseSlots[1] = 0;
    actor.streamSlot = MACHINE_RED_X.SLOT;
    stepTargetYaw(actor, 0xc1, 0, true);
    stepPartTargetPitch(actor, 0xc1);
    actor.hSpeed = actor.yVel = actor.hDecel = actor.gravityCoeff = 0;
    machineRedXSetupCallback(actor, ctx);
    const target = actor.lockTarget;
    if (target) {
      vecSubtract(actor.pos, target, actor.motion);
      vecScale(MACHINE_RED_X.REPOSITION_SCALE, actor.motion, actor.motion);
      vecAdd(actor.pos, actor.motion, actor.pos);
    }
    groundClamp(actor);
    startStream(actor, 0xf, 4, actor.streamSlot, MACHINE_RED_X.STREAM_RATE);
    actor.streamSlot++;
    return;
  }
  if (phase !== 1) return;
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 < 0) actor.steerYaw = toS16(actor.steerYaw) >> 1;
  if (actor.contactP0 < 1 || (actor.fbPhaseSlots[1] ?? 0) < 1) {
    if (actor.faceGate1d10 !== 0) {
      stepTargetYaw(actor, 0xc1, 0, true);
      stepPartTargetPitch(actor, 0xc1);
    }
    if (actor.dashStrength1d0f < 0) {
      actor.dashStrength1d0f = 0;
      if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
    }
    vecScale(MACHINE_RED_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
    integratePhysics(1, actor, actor.lockYaw);
    groundClamp(actor);
    if (actor.wallContact === 0) return;
  } else {
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
    actor.stateTimer = MACHINE_RED_X.COOLDOWN + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;
  actor.hSpeed = 0;
  actor.hDecel = 0;
  romAirKnockoutReturn(actor);
}

function blueBase(actor: RomActor): number {
  return actor.borgNumber === 0x61d ? MACHINE_BLUE_DEPLOY.ATLAS_BASE : MACHINE_BLUE_DEPLOY.BLUE_BASE;
}

function deployAttached(actor: RomActor, ctx: MachineFamilyCtx, firstOnly: boolean): number[] {
  const fired: number[] = [];
  for (let i = 0; i < 4; i++) {
    if ((actor.attachmentFlags14c[i]! & 1) === 0) continue;
    const type = blueBase(actor) + i;
    ctx.onMachineHardpointDeploy?.(actor, MACHINE_BLUE_DEPLOY.SPAWNER, type, i);
    ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_DEPLOY.SPAWNER, type);
    fired.push(type);
    if (firstOnly) break;
  }
  return fired;
}

function releaseShotState(actor: RomActor, cooldown: number): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  dispatchFullBodyCue(actor, actor.ubCue);
  actor.stateTimer = cooldown + actor.dt;
}

/** FUN_800cfb94: deploy the first attached hardpoint then enter shot state. */
function machineBlueAction3(actor: RomActor, ctx: MachineFamilyCtx): void {
  deployAttached(actor, ctx, true);
  releaseShotState(actor, MACHINE_BLUE_DEPLOY.IMMEDIATE_COOLDOWN);
}

/** FUN_800cfc74 (variants 0..2) and FUN_800cfdf0 (variants 3..4). */
function machineBlueAction4(actor: MachineActor, ctx: MachineFamilyCtx): void {
  if (actor.variantIndex >= 3) {
    deployAttached(actor, ctx, false);
    releaseShotState(actor, MACHINE_BLUE_DEPLOY.IMMEDIATE_COOLDOWN);
    return;
  }
  if ((actor.fbPhaseSlots[0] ?? 0) === 0) {
    actor.fbPhaseSlots[0] = 1;
    if (!actor.lockTarget) actor.activeYaw = actor.heading;
    machineBlueXOnSteer(actor);
    const target = actor.lockTarget;
    if (target) vecSubtract(actor.pos, target, actor.motion);
    actor.streamSlot = MACHINE_BLUE_DEPLOY.STREAM_SLOT;
    startStream(actor, 0xf, 4, actor.streamSlot, MACHINE_BLUE_DEPLOY.STREAM_RATE);
    actor.accumulator80c = 0;
  }
  tickStream(actor, 0xf, ctx);
  vecScale(MACHINE_BLUE_DEPLOY.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundClamp(actor);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    deployAttached(actor, ctx, false);
  }
  if (actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
    actor.stateTimer = MACHINE_BLUE_DEPLOY.STATEFUL_COOLDOWN + actor.dt;
  }
}

function routeLeaf(routes: readonly (readonly number[])[], actor: RomActor): number | null {
  return routes[actor.actionIndex]?.[actor.variantIndex] ?? null;
}

export function configureMachineRedFamily(actor: RomActor, borgId: MachineRedBorgId, ctx: MachineFamilyCtx): void {
  actor.borgNumber = Number.parseInt(borgId.slice(2), 16);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  actor.rootAction = (a) => {
    const leaf = routeLeaf(MACHINE_RED_ROUTES.variants, a);
    if (leaf === null) return;
    ctx.onMachineRoute?.(a, leaf);
    if (a.actionIndex === 2) machineRedX(a as MachineActor, ctx);
  };
}

export function configureMachineBlueFamily(actor: RomActor, borgId: MachineBlueBorgId, ctx: MachineFamilyCtx): void {
  actor.borgNumber = Number.parseInt(borgId.slice(2), 16);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const aimedX = createSharedAimedShotX(MACHINE_BLUE_X_CONFIG, ctx);
  actor.rootAction = (a) => {
    if ((a.actionIndex === 3 || a.actionIndex === 4) && borgId !== "pl0609" && borgId !== "pl061d") return;
    const leaf = routeLeaf(MACHINE_BLUE_ROUTES.variants, a);
    if (leaf === null) return;
    ctx.onMachineRoute?.(a, leaf);
    if (a.actionIndex === 2) aimedX(a);
    else if (a.actionIndex === 3) machineBlueAction3(a, ctx);
    else if (a.actionIndex === 4) machineBlueAction4(a as MachineActor, ctx);
  };
}
