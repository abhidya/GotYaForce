/** Bounded ground-close Nurse X, source8007bbe0/8007be08/8007c414/
 * 8007c4b8/8007c7a4. Far and airborne branches are deliberately not admitted.
 * World bone anchors/collision remain the browser's documented root abstraction. */
import bodyHeights from './data/actorBodyHeights.json' with { type: 'json' };
import type { BorgRuntime } from './types.js';
import { tierSizeScale } from './timescale.js';
import type { RomActor } from './rom/actor.js';
import type { StreamContext } from './rom/stream-vm.js';
import { stepTargetYaw } from './rom/helpers.js';
import { integratePhysicsPrimary } from './rom/physics.js';
import { romGroundIdleReturn, romAirKnockoutReturn } from './families/shared-idle-return.js';
import { createNurseStreamClock, resumeNurseStream, recoverNurseStream, tickNurseStream, type NurseStreamClock } from './nurseStream.js';

export const NURSE_X = { closeDistance: 500, heightMargin: 93.69000244140625,
  faceTimer: 60, dashTimer: 30, dashSpeed: 15, resumeDistance: 200, airRecoveryTimer: 20 } as const;
export { isNurseX } from './nurseInput.js';
import { isNurseX } from './nurseInput.js';
/** Original branch tests, with explicit host root anchors replacing +8e0/+8f0.
 * No fallback body height is invented for unknown roster entries. */
export function canStartNurseX(owner: BorgRuntime, target: BorgRuntime | undefined | null): boolean {
  if (!isNurseX(owner.borgId) || !owner.grounded || !owner.command?.exact ||
      owner.command.type !== 2 || owner.command.actionIndex !== 2 || owner.command.variantIndex !== 0 ||
      !target || target.uid === owner.uid || target.team !== owner.team ||
      !target.alive || target.hp <= 0 || target.state === 'death' ||
      (target.targetEligibility83 ?? 0) !== 0) return false;
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
  stream: NurseStreamClock;
  paid: boolean;
  timer: number;
  subphase: number;
  airborneExit: boolean;
}
const states = new WeakMap<RomActor, NurseXState>();
export function getNurseXState(actor: RomActor): NurseXState | undefined { return states.get(actor); }
export function prepareNurseX(actor: RomActor, targetUid: string): void {
  states.set(actor, { targetUid, stream: createNurseStreamClock(16), paid: false,
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
  const state = states.get(actor);
  if (!state) return;
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0:
      actor.fbPhaseSlots[0] = 1;
      actor.contactP0 = 0; actor.contactP1 = 0;
      actor.motion.x = actor.motion.y = actor.motion.z = 0;
      ctx.onArmHit?.(actor, 0, 0, 255);
      ctx.onPlayAnim?.(actor, 4, 2, false);
      stepTargetYaw(actor, 0xc0);
      state.paid = ctx.onAllocateResource?.(actor, 2, 1, 1) === true;
      break;
    case 1:
      // Source phase1 does NOT tick the stream while it settles facing.
      state.timer -= actor.dt;
      if (state.timer <= 0 || stepTargetYaw(actor, 0xc0)) {
        if (!state.paid) { exit(actor, false); break; }
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
          state.subphase = grounded(actor) ? 1 : 2;
          state.timer = NURSE_X.airRecoveryTimer;
        }
      } else if ((state.subphase === 1 && actor.contactP0 === 3 && actor.contactP1 === 8) ||
          (state.subphase === 2 && (state.timer -= actor.dt) <= 0)) {
        state.subphase = 99;
        recoverNurseStream(state.stream);
        actor.contactP0 = actor.contactP1 = 0;
        ctx.onArmHit?.(actor, 0, 0, 255);
        ctx.onPlayAnim?.(actor, 4, 3, false);
      }
      state.airborneExit = !grounded(actor);
      if (state.stream.stage === 'done') actor.fbPhaseSlots[0] = 8;
      break;
    case 8: exit(actor, state.airborneExit); break;
  }
}
