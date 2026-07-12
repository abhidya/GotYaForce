// ALIEN WORM family (ctor 0x80118cb8) — bespoke Action 0 (ground dash) + Action 1
// (B melee) + Action 2 (X-special). Covers:
//   pl0501 ALIEN WORM  (0x501)
//   pl050b VENOM WORM  (0x50b)
//   pl050d CLAW WORM   (0x50d)
//   pl0517 POISON WORM (0x517)
// Source: research/decomp/ghidra-export/chunk_0032.c

import type { RomActor } from "../rom/actor.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const WORM_X = {
  COOLDOWN_GATE: 0.0,
  COOLDOWN: 4.0,
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  ACTION_MODE_BITS: 0x3,
  WORM_CHILD_SPAWNER_ADDR: 0x8011a108,
  CLOUD_SPAWNER_ADDR: 0x801d4d00,
  DASH_TIMER: 4.0,
  STREAM_RATE: 0.5,
  VEL_SCALE: 0.08,
  GRAVITY: 1.0,
  SPEED_DIV: 2.0,
  CONTACT_DIST_DEFAULT: 0.0,
  CONTACT_DIST_CLAW: 0.25,
  RELEASE_DIST: 0.0,
  MELEE_COOLDOWN: 3.0,
  STEER_VEL_SCALE: 0.04,
  PHASE3_TIMER: 6.0,
  STEER_CENTER: 2.0,
  IDLE_COOLDOWN: 1.0,
  CONTACT_CHILD_SPAWNER_ADDR: 0x8013a050,
} as const;

function spawnForBorg(borgNumber: number): { addr: number; type: number } {
  switch (borgNumber) {
    case 0x501: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 0 };
    case 0x50b: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 1 };
    case 0x50d: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 1 };
    case 0x517: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 3 };
    default: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 0 };
  }
}

function contactSpawnForBorg(borgNumber: number): { addr: number; type: number } {
  switch (borgNumber) {
    case 0x501: return { addr: WORM_X.CONTACT_CHILD_SPAWNER_ADDR, type: 0 };
    case 0x50b: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 0 };
    case 0x50d: return { addr: WORM_X.CONTACT_CHILD_SPAWNER_ADDR, type: 1 };
    case 0x517: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 2 };
    default: return { addr: WORM_X.CONTACT_CHILD_SPAWNER_ADDR, type: 0 };
  }
}

export interface WormFamilyCtx extends StreamContext {
  onFaceComplete?: (actor: RomActor, mask: number) => boolean;
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
}

interface WormScratch {
  moveTimer: number;
  animOffset2: number;
  animOffset1: number;
  animOffset0: number;
  streamCueCount: number;
  ubActive: number;
  comboStop: number;
  targetDist: number;
  perFrameField: number;
  partActive: Int8Array;
}

function scratchOf(actor: RomActor): RomActor & WormScratch {
  return actor as RomActor & WormScratch;
}

// ============================================================================
// FUN_80119848 — contact-prompted child spawn (zz_0119848_).
// ============================================================================
function wormContactSpawn(actor: RomActor, ctx: WormFamilyCtx): void {
  if (ctx.onAllocateResource?.(actor, 0, 1, 1) ?? true) {
    const { addr, type } = contactSpawnForBorg(actor.borgNumber);
    ctx.onFamilyProjectile?.(actor, addr, type);
  }
}

// ============================================================================
// Action 0 — Ground dash (FUN_80119250).
// PTR_FUN_8032b5e8[variantIndex]:
//   v0→PTR_FUN_8032b5fc[fbPhase]: ph0 arm, ph1 decay, ph2 contact+wall.
//   v1→PTR_FUN_8032b608[fbPhase]: ph0 arm+project, ph1 decay, ph2 contact+wall.
// ============================================================================

function wormAction0Wrapper(actor: RomActor, ctx: WormFamilyCtx): void {
  actor.steerYaw = actor.steerYaw >> 1;
  if (actor.variantIndex === 0) wormGroundPhaseDisp0(actor, ctx);
  else wormGroundPhaseDisp1(actor, ctx);
}

function wormGroundPhaseDisp0(actor: RomActor, ctx: WormFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) wormGroundPh0(actor, ctx);
  else if (phase === 1) wormGroundPh1(actor, ctx);
  else wormGroundPh2(actor, ctx);
}

function wormGroundPh0(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.moveTimer = WORM_X.DASH_TIMER;
  actor.gravityCoeff = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  actor.hSpeed = 0;
  s.animOffset2 = 0; s.animOffset1 = 0; s.animOffset0 = 0;
  ctx.onFaceComplete?.(actor, 0xc1);
  startStream(actor, 0xf, 0, 1, WORM_X.STREAM_RATE);
}

function wormGroundPh1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0xc1) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 2, 0, WORM_X.STREAM_RATE);
  }
}

function wormGroundPh2(actor: RomActor, ctx: WormFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  ctx.onFaceComplete?.(actor, 0xc1);
  if (actor.contactP0 > 0) { actor.contactP0 = 0; wormContactSpawn(actor, ctx); }
  if (actor.wallContact !== 0) {
    scratchOf(actor).ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

function wormGroundPhaseDisp1(actor: RomActor, ctx: WormFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) wormGroundPh0v1(actor, ctx);
  else if (phase === 1) wormGroundPh1v1(actor, ctx);
  else wormGroundPh2v1(actor, ctx);
}

function wormGroundPh0v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.moveTimer = WORM_X.DASH_TIMER;
  actor.hSpeed = 0; actor.yVel = 0; actor.gravityCoeff = 0; actor.hDecel = 0;
  s.animOffset2 = 0; s.animOffset1 = 0; s.animOffset0 = 0;
  ctx.onFaceComplete?.(actor, 0xc1);
  // pos += (pos - target) * VEL_SCALE (velocity projection toward target)
  actor.pos.x += (actor.pos.x - 0) * WORM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * WORM_X.VEL_SCALE;
  startStream(actor, 0xf, 0, 0xf, WORM_X.STREAM_RATE);
}

function wormGroundPh1v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.pos.x += (actor.pos.x - 0) * WORM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * WORM_X.VEL_SCALE;
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0xc1) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 2, 1, WORM_X.STREAM_RATE);
  }
}

function wormGroundPh2v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.pos.x += (actor.pos.x - 0) * WORM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * WORM_X.VEL_SCALE;
  tickStream(actor, 0xf, ctx);
  ctx.onFaceComplete?.(actor, 0xc1);
  if (actor.contactP0 > 0) { actor.contactP0 = 0; wormContactSpawn(actor, ctx); }
  if (actor.wallContact !== 0) {
    s.ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

// ============================================================================
// Action 1 — B-melee (FUN_801198e8).
// PTR_FUN_8032b614[variantIndex]:
//   v0→PTR_FUN_8032b628[fbPhase]: 4 phases.
//   v1→PTR_FUN_8032b638[fbPhase]: 4 phases.
// ============================================================================

function wormBMeleeWrapper(actor: RomActor, ctx: WormFamilyCtx): void {
  if (actor.variantIndex === 0) wormMeleeDisp0(actor, ctx);
  else wormMeleeDisp1(actor, ctx);
}

function wormMeleeDisp0(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.fbPhaseSlots[1] !== 0) s.comboStop = 0;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) wormMeleePh0(actor, ctx);
  else if (phase === 1) wormMeleePh1(actor, ctx);
  else if (phase === 2) wormMeleePh2(actor, ctx);
  else wormMeleePh3(actor, ctx);
}

function wormMeleePh0(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  if (s.targetDist < 1) {
    actor.fbPhaseSlots[1] = 1;
    s.comboStop = 0;
    actor.activeYaw = actor.heading;
  }
  s.moveTimer = WORM_X.DASH_TIMER;
  ctx.onFaceComplete?.(actor, 0xc0);
  startStream(actor, 0xf, 3, 0, WORM_X.STREAM_RATE);
  s.perFrameField = 0;
}

function wormMeleePh1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0xc0) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    s.moveTimer = WORM_X.MELEE_COOLDOWN;
    actor.hSpeed = s.targetDist / WORM_X.SPEED_DIV;
    actor.yVel = 0;
  }
}

function wormMeleePh2(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
  ctx.onFaceComplete?.(actor, 0xc0);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) actor.fbPhaseSlots[0] = 3;
}

function wormMeleePh3(actor: RomActor, ctx: WormFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) ctx.onFaceComplete?.(actor, 0xc0);
  if (actor.wallContact !== 0) {
    const s = scratchOf(actor);
    s.ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

function wormMeleeDisp1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.fbPhaseSlots[1] !== 0) s.comboStop = 0;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) wormMeleePh0v1(actor, ctx);
  else if (phase === 1) wormMeleePh1v1(actor, ctx);
  else if (phase === 2) wormMeleePh2v1(actor, ctx);
  else wormMeleePh3v1(actor, ctx);
}

function wormMeleePh0v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.streamCueCount = 1;
  if (s.targetDist < 1) {
    actor.fbPhaseSlots[1] = 1;
    s.comboStop = 0;
    actor.activeYaw = actor.heading;
  }
  s.moveTimer = WORM_X.DASH_TIMER;
  ctx.onFaceComplete?.(actor, 0xc0);
  actor.pos.x += (actor.pos.x - 0) * WORM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * WORM_X.VEL_SCALE;
  const slot = s.streamCueCount;
  s.streamCueCount = slot + 1;
  startStream(actor, 0xf, 3, slot, WORM_X.STREAM_RATE);
  s.perFrameField = 0;
}

function wormMeleePh1v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  if (s.partActive?.[3] !== 0) tickStream(actor, 0xf, ctx);
  actor.pos.x += (actor.pos.x - 0) * WORM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * WORM_X.VEL_SCALE;
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0xc0) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    s.moveTimer = WORM_X.PHASE3_TIMER;
  }
}

function wormMeleePh2v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onFaceComplete?.(actor, 0xc0);
  actor.hSpeed = WORM_X.STEER_VEL_SCALE;
  actor.yVel = -WORM_X.STEER_VEL_SCALE;
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) {
    s.moveTimer = 0;
    if (s.partActive?.[1] !== 0) {
      actor.fbPhaseSlots[0] = 3;
      s.moveTimer = WORM_X.PHASE3_TIMER;
      const slot = s.streamCueCount;
      s.streamCueCount = slot + 1;
      startStream(actor, 0xf, 3, slot, WORM_X.STREAM_RATE);
    }
  }
}

function wormMeleePh3v1(actor: RomActor, ctx: WormFamilyCtx): void {
  const s = scratchOf(actor);
  actor.steerYaw = (actor.steerYaw * WORM_X.STEER_CENTER) & 0xffff;
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer > 0) return;
  actor.hSpeed = 0; actor.yVel = 0;
  s.ubActive = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  romGroundIdleReturn(actor);
}

// ============================================================================
// Action 2 — X-special (FUN_80118efc borg-switched spawn).
// 2-phase: spawn child, clean up.
// ============================================================================

function wormXPhase0(actor: RomActor, ctx: WormFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  const { addr, type } = spawnForBorg(actor.borgNumber);
  ctx.onFamilyProjectile?.(actor, addr, type);
  actor.stateTimer = WORM_X.COOLDOWN + actor.dt;
}

function wormXPhase1(actor: RomActor, _ctx: WormFamilyCtx): void {
  actor.controlWord = actor.controlWord & ~WORM_X.ACTION_MODE_BITS;
}

function wormXHandler(actor: RomActor, ctx: WormFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) wormXPhase0(actor, ctx);
  else wormXPhase1(actor, ctx);
}

// ============================================================================
// Root action dispatcher — FUN_80119214 (PTR_FUN_8032b5dc[actionIndex]).
// ============================================================================

export function createWormRootAction(ctx: WormFamilyCtx): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    (a) => wormAction0Wrapper(a, ctx),
    (a) => wormBMeleeWrapper(a, ctx),
    (a) => wormXHandler(a, ctx),
    null, // 3: B charge
    null, // 4:
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

export function configureWormFamily(
  actor: RomActor,
  borgId: "pl0501" | "pl050b" | "pl050d" | "pl0517",
  ctx: WormFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0501" ? 0x501 :
    borgId === "pl050b" ? 0x50b :
    borgId === "pl050d" ? 0x50d : 0x517;
  actor.rootAction = createWormRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
