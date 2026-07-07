import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const KNIGHT_MELEE = {
  FACE_BUDGET: 60.0,
  ACTIVE_WINDOW: 20.0,
  ZERO: 0.0,
  PROXIMITY: 200.0,
  DRAG: 0.95,
  DT_MOD: 0.98,
  STREAM_RATE: -1.0,
  DASH_REFRESH_NUM: 2.5,
  DASH_REFRESH_DEN: 20.0,
  REPOSITION: 0.95,
  DIVE_MAGNITUDE: 30.0,
  GRAVITY: 1.0,
  DRIFT_THRESHOLD: 3.0,
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  MELEE_FX_ADDR: 0x800b2190,
  DIVE_FX_ADDR: 0x80092dcc,
  DEFAULT_RANGE_ROW: 1000.0,
} as const;

interface MeleeScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  rangeRow868?: number;
  rangeRow86c?: number;
  curTargetDist?: number;
  bRetapInput?: boolean;
  bRetap?: boolean;
  swingEvent?: number;
  dashStrength?: number;
  streamTickGate?: boolean;
  faceGate?: number;
  meleeAimPitch?: number;
  hitReact?: number;
  hitReact1dd?: number;
  inputHeld5d8?: number;
  inputEdge5d4?: number;
  wallContact?: number;
  activeYaw?: number;
  lockYaw?: number;
  steerYaw?: number;
  meter1900?: number;
  aimYawTrack?: number;
}

type MActor = RomActor & MeleeScratch;

function s16(v: number): number { return (v << 16) >> 16; }

function targetDistance(a: MActor): number {
  const t = a.lockTarget;
  if (t) { a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z); return a.curTargetDist; }
  return a.curTargetDist ?? 0;
}

function rangeCheck(a: MActor, range: number): number {
  if (!a.lockTarget) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

function rangeRow868(a: MActor): number { return a.rangeRow868 ?? KNIGHT_MELEE.DEFAULT_RANGE_ROW; }

function faceComplete(a: MActor): boolean { return a.lockTarget != null; }

function applyDrag(a: MActor, scale: number): void { a.hSpeed *= scale; a.yVel *= scale; }

function seekAimPitch(a: MActor): void {
  const t = a.lockTarget;
  if (!t) { a.meleeAimPitch = s16(Math.trunc((a.meleeAimPitch ?? 0) * 0.9)); return; }
  const hd = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
  a.meleeAimPitch = s16(Math.round((Math.atan2(-(t.y - a.pos.y), Math.max(hd, 1e-6)) / (Math.PI * 2)) * 0x10000));
}

function gravityRestore(a: MActor): number { return a.descriptor?.handlerData6c ?? 1.0; }

function setupLockGate(a: MActor, row: number, activeFrom: "heading" | "lockYaw"): void {
  if (rangeCheck(a, row) < 1) {
    a.fbPhaseSlots[1] = 1; a.lockTarget = null;
    a.activeYaw = activeFrom === "heading" ? a.heading : a.lockYaw;
  }
}

function blinkReposition(a: MActor, scale: number): void {
  if (a.lockTarget) { vecSubtract(a.pos, a.lockTarget, a.motion); vecScale(scale, a.motion, a.motion); vecAdd(a.pos, a.motion, a.pos); }
  else { a.motion.x = 0; a.motion.y = 0; a.motion.z = 0; }
}

function prelude(a: MActor): void {
  if ((a.fbPhaseSlots[0] ?? 0) === 0) (a as any)._80c = KNIGHT_MELEE.ZERO;
  vecSubtract(a.pos, a.lockTarget ?? a.pos, a.motion);
  if (Math.hypot(a.motion.x, a.motion.y, a.motion.z) > KNIGHT_MELEE.DRIFT_THRESHOLD) { }
}

function meleeExitWall(a: MActor): void {
  a.controlWord &= ~0x3;
  if ((a.controlWord & 0x40) === 0) romGroundIdleReturn(a);
  else romAirKnockoutReturn(a);
}

// 0x80343c00 / 0x80343c14 phase 0 — FUN_80158114 / FUN_80158700
function meleePhase0(a: MActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;
  setupLockGate(a, rangeRow868(a), "heading");
  a.bRetap = false;
  a.handlerTimer = KNIGHT_MELEE.FACE_BUDGET;
  a.streamSlot = seedSlot;
  const slot = a.streamSlot; a.streamSlot = slot + 1;
  startStream(a, KNIGHT_MELEE.PART_MASK, KNIGHT_MELEE.STREAM_GROUP, slot, KNIGHT_MELEE.STREAM_RATE);
}

// 0x80343c00 phase 1 — FUN_801581f4
function meleePhase1(a: MActor, ctx: StreamContext): void {
  if (a.streamTickGate) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;
    if (!a.lockTarget) a.fbPhaseSlots[0] += 2;
    a.handlerTimer = KNIGHT_MELEE.ACTIVE_WINDOW;
    let f = rangeRow868(a);
    if (a.lockTarget && f < targetDistance(a)) f = targetDistance(a);
    a.hSpeed = f / KNIGHT_MELEE.ACTIVE_WINDOW;
    a.hDecel = KNIGHT_MELEE.ZERO;
    integratePhysics(0, a, s16(a.lockYaw ?? 0));
    if (KNIGHT_MELEE.PROXIMITY < targetDistance(a)) ctx.onFamilyProjectile?.(a, KNIGHT_MELEE.MELEE_FX_ADDR, 0);
  }
}

// 0x80343c00 phase 2 — FUN_80158318
function meleePhase2(a: MActor, ctx: StreamContext): void {
  if (a.streamTickGate) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  integratePhysics(0, a, s16(a.lockYaw ?? 0));
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO || rangeCheck(a, KNIGHT_MELEE.PROXIMITY) > 0) {
    a.fbPhaseSlots[0] += 1;
    a.handlerTimer = KNIGHT_MELEE.ZERO;
  }
}

// 0x80343c00 phase 3 — FUN_801583b4
function meleePhase3(a: MActor, ctx: StreamContext): void {
  const savedDt = a.dt;
  (a as any).dt = a.dt * KNIGHT_MELEE.DT_MOD;
  tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  (a as any).dt = savedDt;
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO) { a.fbPhaseSlots[0] += 1; a.handlerTimer = KNIGHT_MELEE.ZERO; }
}

// 0x80343c00 phase 4 — FUN_80158444 (combo loop)
function meleePhase4(a: MActor, ctx: StreamContext): void {
  if (a.bRetapInput) a.bRetap = true;
  if ((a.swingEvent ?? 0) < 0 && a.bRetap) {
    a.bRetap = false;
    a.handlerTimer = KNIGHT_MELEE.ACTIVE_WINDOW;
    if (!a.lockTarget) a.hSpeed = rangeRow868(a) * 0.05;
    else a.hSpeed = KNIGHT_MELEE.DASH_REFRESH_NUM * targetDistance(a) * 0.05;
    if (KNIGHT_MELEE.PROXIMITY < targetDistance(a)) ctx.onFamilyProjectile?.(a, KNIGHT_MELEE.MELEE_FX_ADDR, 0);
    const slot = a.streamSlot; a.streamSlot = slot + 1;
    startStream(a, KNIGHT_MELEE.PART_MASK, KNIGHT_MELEE.STREAM_GROUP, slot, KNIGHT_MELEE.STREAM_RATE);
    return;
  }
  if ((a.faceGate ?? 0) > 0) { }
  if (a.dashStrength && a.dashStrength > 0) {
    a.dashStrength = 0;
    if (a.lockTarget) a.hSpeed = 0;
  }
  if ((a.handlerTimer <= KNIGHT_MELEE.ZERO || !a.lockTarget) && (a.borgNumber !== 0x205 && a.borgNumber !== 0x209)) {
    tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  } else {
    a.handlerTimer -= a.dt;
    applyDrag(a, KNIGHT_MELEE.DRAG);
    if (targetDistance(a) < KNIGHT_MELEE.PROXIMITY) applyDrag(a, KNIGHT_MELEE.DRAG);
    integratePhysics(0, a, s16(a.lockYaw ?? 0));
    const savedDt = a.dt;
    (a as any).dt = a.dt * KNIGHT_MELEE.DT_MOD;
    tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
    (a as any).dt = savedDt;
  }
  if ((a.contactP0 < 0 && ((a.inputHeld5d8 ?? 0) & 0xf0) !== 0) || a.wallContact !== 0) {
    a.controlWord &= ~0x3;
    romGroundIdleReturn(a);
  }
}

// 0x80343c14 / 0x80343c28 phase — FUN_801587cc (face budget variant)
function meleePhase1b(a: MActor, ctx: StreamContext): void {
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;
    a.handlerTimer = KNIGHT_MELEE.ACTIVE_WINDOW;
    let d = rangeRow868(a);
    if (a.lockTarget && d < targetDistance(a)) d = targetDistance(a);
    a.hSpeed = (KNIGHT_MELEE.DASH_REFRESH_NUM * d) / KNIGHT_MELEE.DASH_REFRESH_DEN;
    a.hDecel = KNIGHT_MELEE.ZERO;
    integratePhysics(0, a, s16(a.lockYaw ?? 0));
    ctx.onFamilyProjectile?.(a, KNIGHT_MELEE.MELEE_FX_ADDR, 0);
  }
}

// 0x80343c14/28 phase — FUN_801588bc (active dash variant)
function meleePhase2b(a: MActor, ctx: StreamContext): void {
  integratePhysics(0, a, s16(a.lockYaw ?? 0));
  if (a.contactP0 === 0) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO || rangeCheck(a, KNIGHT_MELEE.PROXIMITY) > 0) {
    a.fbPhaseSlots[0] += 1;
    a.handlerTimer = KNIGHT_MELEE.ZERO;
  }
}

// 0x80343c14 phase 3 — FUN_80158958 (recovery tick)
function meleePhase3b(a: MActor, ctx: StreamContext): void {
  if (a.contactP0 === 0) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  else {
    const savedDt = a.dt;
    (a as any).dt = a.dt * KNIGHT_MELEE.DT_MOD;
    tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
    (a as any).dt = savedDt;
  }
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO) a.fbPhaseSlots[0] += 1;
}

// 0x80343c14 phase 4 — FUN_80158a00 (wall exit)
function meleePhase4b(a: MActor, ctx: StreamContext): void {
  tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  if ((a.faceGate ?? 0) > 0) { }
  if ((a.dashStrength ?? 0) > 0) { applyDrag(a, KNIGHT_MELEE.DRAG); integratePhysics(0, a, s16(a.lockYaw ?? 0)); }
  if (a.wallContact !== 0) meleeExitWall(a);
}

// 0x80343c14 phase 5 / 0x80343c28 phase 0 — FUN_80158ae4 (pitch dive setup)
function divePhase0(a: MActor, seedSlot: number): void {
  setupLockGate(a, rangeRow868(a), "lockYaw");
  const p208_20e = a.borgNumber === 0x208 || a.borgNumber === 0x20e;
  if (!p208_20e && a.lockTarget) {
    const d = Math.hypot(a.lockTarget.x - a.pos.x, a.lockTarget.z - a.pos.z);
    if (d < 200) { a.variantIndex = 5; return; }
  }
  a.fbPhaseSlots[0] += 1;
  a.bRetap = false;
  a.handlerTimer = KNIGHT_MELEE.FACE_BUDGET;
  a.meleeAimPitch = 0;
  a.streamSlot = seedSlot;
  a.gravityCoeff = KNIGHT_MELEE.ZERO;
  a.yVel = KNIGHT_MELEE.ZERO;
  a.hDecel = KNIGHT_MELEE.ZERO;
  a.hSpeed = KNIGHT_MELEE.ZERO;
  seekAimPitch(a as any);
  blinkReposition(a as any, KNIGHT_MELEE.REPOSITION);
  const slot = a.streamSlot; a.streamSlot = slot + 1;
  startStream(a, KNIGHT_MELEE.PART_MASK, KNIGHT_MELEE.STREAM_GROUP, slot, KNIGHT_MELEE.STREAM_RATE);
}

// 0x80343c28 phase 1 — FUN_80158d38 (pitch dive active)
function divePhase1(a: MActor, ctx: StreamContext): void {
  if (a.contactP0 === 0) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  seekAimPitch(a as any);
  const pitch = a.meleeAimPitch ?? 0;
  a.hSpeed = KNIGHT_MELEE.DIVE_MAGNITUDE * projectZ(pitch);
  a.yVel = KNIGHT_MELEE.DIVE_MAGNITUDE * -projectX(pitch);
  integratePhysics(KNIGHT_MELEE.GRAVITY, a, s16(a.lockYaw ?? 0));
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO || rangeCheck(a, KNIGHT_MELEE.PROXIMITY) > 0) {
    a.fbPhaseSlots[0] += 1;
    a.handlerTimer = KNIGHT_MELEE.ACTIVE_WINDOW;
    a.hSpeed *= KNIGHT_MELEE.DT_MOD;
    a.hDecel *= KNIGHT_MELEE.DT_MOD;
    a.yVel *= KNIGHT_MELEE.DT_MOD;
    a.gravityCoeff *= KNIGHT_MELEE.DT_MOD;
  }
}

// 0x80343c28 phase 2 — FUN_80158e60 (pitch dive recovery)
function divePhase2(a: MActor, ctx: StreamContext): void {
  if (a.contactP0 === 0) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  else {
    const savedDt = a.dt;
    (a as any).dt = a.dt * KNIGHT_MELEE.DT_MOD;
    tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
    (a as any).dt = savedDt;
  }
  integratePhysics(KNIGHT_MELEE.GRAVITY, a, s16(a.lockYaw ?? 0));
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO) {
    a.fbPhaseSlots[0] += 1;
    a.hSpeed *= KNIGHT_MELEE.DASH_REFRESH_NUM;
    a.hDecel *= KNIGHT_MELEE.DASH_REFRESH_NUM;
    a.yVel *= KNIGHT_MELEE.DASH_REFRESH_NUM;
    a.gravityCoeff *= KNIGHT_MELEE.DASH_REFRESH_NUM;
  }
}

// 0x80343c28 phase 3 — FUN_80158f58 (combo loop / land)
function divePhase3(a: MActor, ctx: StreamContext): void {
  if (a.bRetapInput) a.bRetap = true;
  tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  if ((a.swingEvent ?? 0) < 0 && a.bRetap) {
    a.bRetap = false;
    seekAimPitch(a as any);
    const pitch = a.meleeAimPitch ?? 0;
    a.hSpeed = KNIGHT_MELEE.DIVE_MAGNITUDE * projectZ(pitch);
    a.yVel = KNIGHT_MELEE.DIVE_MAGNITUDE * -projectX(pitch);
    const slot = a.streamSlot; a.streamSlot = slot + 1;
    startStream(a, KNIGHT_MELEE.PART_MASK, KNIGHT_MELEE.STREAM_GROUP, slot, KNIGHT_MELEE.STREAM_RATE);
    return;
  }
  if ((a.dashStrength ?? 0) < 0) {
    a.dashStrength = 0;
    if (a.yVel > KNIGHT_MELEE.ZERO) a.yVel = KNIGHT_MELEE.ZERO;
    a.gravityCoeff = gravityRestore(a);
  }
  applyDrag(a, KNIGHT_MELEE.REPOSITION);
  integratePhysics(KNIGHT_MELEE.GRAVITY, a, s16(a.lockYaw ?? 0));
  const grounded = a.grounded === true;
  if (grounded && a.contactP0 < 0) {
    a.controlWord &= ~0x3;
    dispatchUpperBodyCue(a, 7);
    a.stateTimer = KNIGHT_MELEE.GRAVITY + a.dt;
    return;
  }
  if (a.wallContact !== 0) meleeExitWall(a);
}

/** zz_0159100_ — shared melee setup: clear gravity override if phase 0, drift-correct if
 *  target distance exceeds PROXIMITY. */
function sharedMeleeSetup(a: MActor): void {
  if ((a.fbPhaseSlots[0] ?? 0) === 0) (a as any)._80c = KNIGHT_MELEE.ZERO;
  const t = a.lockTarget;
  if (t) {
    const dx = t.x - a.pos.x;
    const dy = t.y - a.pos.y;
    const dz = t.z - a.pos.z;
    if (Math.hypot(dx, dy, dz) > KNIGHT_MELEE.PROXIMITY) {
      // zz_00b22f4_ — drift correction (approximated by repositioning toward target)
      vecSubtract(a.pos, t, a.motion);
      vecScale(KNIGHT_MELEE.DT_MOD, a.motion, a.motion);
      vecAdd(a.pos, a.motion, a.pos);
    }
  }
}

/** zz_015809c_ — entry point for knight melee table 0x80343c00. Clears +0xcc if +0x541
 *  is set (first-entry flag), runs shared setup, then dispatches phase via table00. */
export function knightMeleeEntry00(actor: RomActor, table: (a: RomActor) => void): void {
  const a = actor as MActor;
  if ((a as any)._541) (a as any)._cc = 0;
  sharedMeleeSetup(a);
  table(actor);
}

/** zz_0158688_ — entry point for knight melee table 0x80343c14. Same pattern but dispatches
 *  via table14. */
export function knightMeleeEntry14(actor: RomActor, table: (a: RomActor) => void): void {
  const a = actor as MActor;
  if ((a as any)._541) (a as any)._cc = 0;
  sharedMeleeSetup(a);
  table(actor);
}

/** zz_0158a94_ — entry point for knight melee table 0x80343c28 (pitch dive). Does NOT call
 *  sharedMeleeSetup — dispatches directly into the dive table. */
export function knightMeleeEntry28(actor: RomActor, table: (a: RomActor) => void): void {
  const a = actor as MActor;
  if ((a as any)._541) (a as any)._cc = 0;
  table(actor);
}

export function createKnightMeleeTable00(ctx: StreamContext, seedSlot = 0): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as MActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    prelude(a);
    switch (a.fbPhaseSlots[0] ?? 0) {
      case 0: meleePhase0(a, seedSlot); break;
      case 1: meleePhase1(a, ctx); break;
      case 2: meleePhase2(a, ctx); break;
      case 3: meleePhase3(a, ctx); break;
      case 4: meleePhase4(a, ctx); break;
      default: break;
    }
  };
}

export function createKnightMeleeTable14(ctx: StreamContext, seedSlot = 0): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as MActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    prelude(a);
    switch (a.fbPhaseSlots[0] ?? 0) {
      case 0: meleePhase0(a, seedSlot); break;
      case 1: meleePhase1b(a, ctx); break;
      case 2: meleePhase2b(a, ctx); break;
      case 3: meleePhase3b(a, ctx); break;
      case 4: meleePhase4b(a, ctx); break;
      default: break;
    }
  };
}

function divePhaseRecovery(a: MActor, ctx: StreamContext): void {
  if (a.contactP0 === 0) tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
  else {
    const savedDt = a.dt;
    (a as any).dt = a.dt * KNIGHT_MELEE.DT_MOD;
    tickStream(a, KNIGHT_MELEE.PART_MASK, ctx);
    (a as any).dt = savedDt;
  }
  integratePhysics(KNIGHT_MELEE.GRAVITY, a, s16(a.lockYaw ?? 0));
  a.handlerTimer -= a.dt;
  if (a.handlerTimer <= KNIGHT_MELEE.ZERO) {
    a.fbPhaseSlots[0] += 1;
    a.hSpeed *= KNIGHT_MELEE.DASH_REFRESH_DEN;
    a.hDecel *= KNIGHT_MELEE.DASH_REFRESH_DEN;
    a.yVel *= KNIGHT_MELEE.DASH_REFRESH_DEN;
    a.gravityCoeff *= KNIGHT_MELEE.DASH_REFRESH_DEN;
  }
}

/** Generic knight-family root action wiring shared melee to action 1. Action 0 (dash),
 *  action 2 (X-special), and 3/4 fall through to the combat layer. Pre-creates all 4
 *  variant tables once. */
export function createGenericKnightRootAction(ctx: StreamContext): (actor: RomActor) => void {
  const meleeTables = [
    createKnightMeleeTable00(ctx, 0),
    createKnightMeleeTable14(ctx, 3),
    createKnightMeleeTable14(ctx, 4),
    createKnightMeleeTable28(ctx),
  ];
  return (actor: RomActor) => {
    if (actor.actionIndex === 1) {
      const a = actor as MActor;
      a.steerYaw = (a.steerYaw as any) >> 1;
      (a as any).steerYaw2 = ((a as any).steerYaw2 ?? 0) >> 1;
      const variant = ((a as any)._581 as number) ?? 0;
      const table: ((a: RomActor) => void) | undefined = meleeTables[variant];
      if (!table) return;
      if (variant < 3) knightMeleeEntry14(actor, table);
      else knightMeleeEntry28(actor, table);
    }
  };
}

export function createKnightMeleeTable28(ctx: StreamContext, seedSlot = 0): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as MActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {
      case 0: divePhase0(a, seedSlot); break;
      case 1: divePhase1(a, ctx); break;
      case 2: divePhase2(a, ctx); break;
      case 3: divePhaseRecovery(a, ctx); break;
      case 4: divePhase3(a, ctx); break;
      default: break;
    }
  };
}
