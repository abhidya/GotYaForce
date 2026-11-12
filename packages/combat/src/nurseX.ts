/** Allied Nurse X, source8007bbe0/8007be08/8007c414/
 * 8007c4b8/8007c7a4, with the far 8007bf70..8007c350 continuation.
 * World bone anchors/collision remain the browser's documented root abstraction. */
import { steerNurseMotion, integrateNurseDrift } from './nurseMotion.js';
import bodyHeights from './data/actorBodyHeights.json' with { type: 'json' };
import type { BorgRuntime } from './types.js';
import { tierSizeScale } from './timescale.js';
import type { RomActor } from './rom/actor.js';
import type { StreamContext } from './rom/stream-vm.js';
import { stepTargetYaw } from './rom/helpers.js';
import { integratePhysicsPrimary } from './rom/physics.js';
import { romGroundIdleReturn, romAirKnockoutReturn } from './families/shared-idle-return.js';
import { createNurseFarStreamClock, recoverNurseFarStream, createNurseStreamClock, resumeNurseStream, recoverNurseStream, tickNurseStream, type NurseStreamClock } from './nurseStream.js';

export const NURSE_X = { closeDistance: 500, heightMargin: 93.69000244140625,
  faceTimer: 60, dashTimer: 30, dashSpeed: 15, resumeDistance: 200, missRecoveryTimer: 20 } as const;
export { isNurseX } from './nurseInput.js';
import { isNurseX } from './nurseInput.js';
/** Original branch tests, with explicit host root anchors replacing +8e0/+8f0.
 * No fallback body height is invented for unknown roster entries. */
export function canStartNurseX(owner: BorgRuntime, target: BorgRuntime | undefined | null): boolean {
  if (!isNurseX(owner.borgId) || !owner.command?.exact ||
      owner.command.type !== 2 || owner.command.actionIndex !== 2 || owner.command.variantIndex !== (owner.grounded ? 0 : 1) ||
      !target || target.uid === owner.uid || target.team !== owner.team ||
      !target.alive || target.hp <= 0 || target.state === 'death' ||
      (target.targetEligibility83 ?? 0) !== 0) return false;
  const heights: Readonly<Record<string, number>> = bodyHeights.borgs;
  return heights[target.combatFormId ?? target.borgId] !== undefined;
}
/** Source close/far branch, separate from valid-allied action admission. */
export function isCloseNurseX(owner: BorgRuntime, target: BorgRuntime): boolean {
  const heights: Readonly<Record<string, number>> = bodyHeights.borgs;
  const baseHeight = heights[target.combatFormId ?? target.borgId];
  if (baseHeight === undefined) return false;
  const targetPos = target.sourceFramePose?.pos ?? target.pos;
  const sourceY = owner.pos.y + NURSE_X.heightMargin;
  const height = Math.fround(baseHeight * tierSizeScale(target));
  return Math.hypot(targetPos.x - owner.pos.x, targetPos.y - owner.pos.y, targetPos.z - owner.pos.z) < NURSE_X.closeDistance &&
    sourceY >= targetPos.y - NURSE_X.heightMargin && sourceY <= targetPos.y + height;
}
export interface NurseXState {
  targetUid: string | null;
  close: boolean;
  pendingContact: number;
  recoil: { x: number; y: number; z: number } | null;
  stream: NurseStreamClock;
  paid: boolean;
  timer: number;
  subphase: number;
  airborneExit: boolean;
}
const states = new WeakMap<RomActor, NurseXState>();
export function getNurseXState(actor: RomActor): NurseXState | undefined { return states.get(actor); }
export function prepareNurseX(actor: RomActor, targetUid: string, close = true): void {
  states.set(actor, { targetUid, close, pendingContact: 0, recoil: null, stream: close ? createNurseStreamClock(16) : createNurseFarStreamClock(), paid: false,
    timer: NURSE_X.faceTimer, subphase: 0, airborneExit: false });
}
export function clearNurseX(actor: RomActor): void { states.delete(actor); }
function grounded(actor: RomActor): boolean { return (actor as RomActor & { grounded?: boolean }).grounded === true; }
function tick(actor: RomActor): void {
  const state = states.get(actor)!;
  const event = tickNurseStream(state.stream, actor.dt);
  if (event.aux !== undefined) { actor.contactP0 = 3; actor.contactP1 = event.aux; }
}
function exit(actor: RomActor, air: boolean): void {
  actor.controlWord &= ~3;
  if (air) romAirKnockoutReturn(actor); else romGroundIdleReturn(actor);
}
export function stepNurseX(actor: RomActor, ctx: StreamContext): void {
  stepNurseXPhases(actor, ctx);
  // 8007bb6c clamps after every phase, including its early-return paths.
  if (actor.hSpeed > 30) actor.hSpeed = 30;
}
function stepNurseXPhases(actor: RomActor, ctx: StreamContext): void {
  const state = states.get(actor);
  if (!state) return;
  const contact = state.pendingContact; state.pendingContact = 0;
  if (!state.close && (actor.fbPhaseSlots[0] ?? 0) >= 2) { stepNurseFar(actor, ctx, state, contact); return; }
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0:
      actor.fbPhaseSlots[0] = 1;
      actor.contactP0 = 0; actor.contactP1 = 0;
      actor.motion.x = actor.motion.y = actor.motion.z = 0;
      ctx.onArmHit?.(actor, state.close ? 0 : 3, 0, 255);
      ctx.onPlayAnim?.(actor, 4, state.close ? 2 : 0, false);
      // Original opcode03 (PPC8004c488) replaces only bits4..11. The
      // ground s2 descriptor writes0; airborne s5 writes40. Both play g4s2.
      actor.controlWord = (actor.controlWord & ~0xff0) | (state.close && actor.variantIndex === 0 ? 0 : 0x40);
      stepTargetYaw(actor, 0xc0);
      state.paid = ctx.onAllocateResource?.(actor, 2, 1, 1) === true;
      break;
    case 1:
      // Source phase1 does NOT tick the stream while it settles facing.
      state.timer -= actor.dt;
      if (state.timer <= 0 || stepTargetYaw(actor, 0xc0)) {
        if (!state.close) {
          actor.fbPhaseSlots[0] = 2;
          actor.hSpeed = actor.hDecel = 1;
          // +8dc/+8ec/+8fc: actor matrix forward column, not a root-motion delta.
          const yaw = actor.heading * Math.PI * 2 / 65536;
          const pitch = actor.bodyPitch * Math.PI * 2 / 65536;
          Object.assign(actor.motion, { x: Math.sin(yaw) * Math.cos(pitch),
            y: -Math.sin(pitch), z: Math.cos(yaw) * Math.cos(pitch) });
          break;
        }
        if (!state.paid) { exit(actor, actor.variantIndex !== 0); break; }
        actor.fbPhaseSlots[0] = 5;
        state.timer = NURSE_X.dashTimer;
        actor.hSpeed = NURSE_X.dashSpeed;
        actor.hDecel = actor.yVel = actor.gravityCoeff = 0;
      }
      break;
    case 5: {
      tick(actor);
      stepTargetYaw(actor, 0xc0);
      integratePhysicsPrimary(1, actor, actor.lockYaw);
      state.timer -= actor.dt;
      const target = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
      if (state.timer <= 0 || (target && Math.hypot(target.x - actor.pos.x, target.z - actor.pos.z) <= NURSE_X.resumeDistance * actor.modelScale)) {
        actor.fbPhaseSlots[0] = 6; state.subphase = 0;
        resumeNurseStream(state.stream, actor.dt);
        ctx.onArmHit?.(actor, 4, 127, 255);
      }
      break;
    }
    case 6:
      tick(actor);
      if (state.subphase === 0) {
        stepTargetYaw(actor, 0xc0);
        integratePhysicsPrimary(1, actor, actor.lockYaw);
        if (actor.contactP0 === 3 && actor.contactP1 === 6) {
          actor.hSpeed = actor.hDecel = 0;
          state.subphase = contact > 0 && contact < 128 ? 1 : 2;
          state.timer = NURSE_X.missRecoveryTimer;
        }
      } else if ((state.subphase === 1 && actor.contactP0 === 3 && actor.contactP1 === 8) ||
          (state.subphase === 2 && (state.timer -= actor.dt) <= 0)) {
        state.subphase = 99;
        recoverNurseStream(state.stream);
        actor.contactP0 = actor.contactP1 = 0;
        ctx.onArmHit?.(actor, 0, 0, 255);
        ctx.onPlayAnim?.(actor, 4, 3, false);
        // Both variants explicitly select stream s4, whose opcode03 clears40.
        // Do not substitute the unused s7 airborne recovery descriptor.
        actor.controlWord &= ~0xff0;
      }
      state.airborneExit = !grounded(actor);
      if (state.stream.stage === 'done') actor.fbPhaseSlots[0] = 8;
      break;
    case 8: exit(actor, state.airborneExit); break;
  }
}

/** Far allied continuation, 8007bf70 / 8007c19c / 8007c350 / 8007c6b0. */
function stepNurseFar(actor: RomActor, ctx: StreamContext, state: NurseXState, contact: number): void {
  const phase = actor.fbPhaseSlots[0];
  const hit = contact > 0 && contact < 128;
  const target = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  const seek = (lower: boolean): void => {
    stepTargetYaw(actor, 0xc0);
    if (target && state.targetUid) {
      steerNurseMotion(actor, { ...target, y: target.y - (lower ? NURSE_X.heightMargin : 0) });
      const distance = (actor as RomActor & { targetDistance760?: number }).targetDistance760 ?? 0;
      actor.hDecel = distance >= 300 ? 1 : -4;
    }
    integrateNurseDrift(actor);
    if (actor.hDecel < 0 && actor.hSpeed < 15) actor.hSpeed = 15;
  };
  const recover = (recoil: boolean): void => {
    actor.fbPhaseSlots[0] = 4;
    if (recoil) {
      const m = actor.motion, n = Math.hypot(m.x, m.z);
      const v = { x: n > 0 ? -m.x / n : 0, y: 0.699999988079071, z: n > 0 ? -m.z / n : 0 };
      const len = Math.hypot(v.x, v.y, v.z);
      state.recoil = { x: v.x / len, y: v.y / len, z: v.z / len };
      Object.assign(m, { x: 0, y: 1, z: 0 }); actor.hSpeed = 8; actor.hDecel = 0;
      actor.stateTimer = 80 + actor.dt;
    } else actor.hDecel = -0.10000000149011612;
    recoverNurseFarStream(state.stream);
    actor.contactP0 = actor.contactP1 = 0;
    ctx.onArmHit?.(actor, 0, 0, 255);
    ctx.onPlayAnim?.(actor, 4, 1, false);
    actor.controlWord = (actor.controlWord & ~0xff0) | 0x40;
  };
  if (phase === 2) {
    tick(actor);
    if (hit) { recover(true); return; }
    if (!state.paid) {
      if (actor.contactP0 === 3 && actor.contactP1 === 9) {
        actor.stateTimer = 30 + actor.dt; exit(actor, true);
      }
      return;
    }
    seek(false);
    if (actor.contactP0 === 3 && actor.contactP1 === 10) actor.contactP0 = actor.contactP1 = 0;
    else if (actor.contactP0 === 3 && actor.contactP1 === 1) {
      actor.fbPhaseSlots[0] = 3; state.timer = 30;
      actor.contactP0 = actor.contactP1 = 0;
    }
  } else if (phase === 3) {
    // No stream tick here: source holds the HIT pose while homing continues.
    seek(true);
    state.timer -= actor.dt;
    if (hit || state.timer <= 0) recover(hit);
  } else if (phase === 4) {
    tick(actor); integrateNurseDrift(actor);
    if (state.recoil) {
      actor.motion.x += state.recoil.x; actor.motion.y += state.recoil.y; actor.motion.z += state.recoil.z;
    }
    if (state.stream.stage === 'done') actor.fbPhaseSlots[0] = 7;
  } else if (phase === 7) {
    integrateNurseDrift(actor);
    actor.yVel = actor.motion.y;
    actor.activeYaw = actor.lockYaw = Math.round(Math.atan2(actor.motion.x, actor.motion.z) * 65536 / (2 * Math.PI)) & 0xffff;
    exit(actor, true);
  }
}
