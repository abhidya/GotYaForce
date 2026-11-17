import {classifyDoubleCloneReaction, type DoubleCloneReactionInput,
  type DoubleCloneReactionResult} from './doubleCloneReaction.js';

/** Inert, primary-actor collision-frame subset. No combat/Battle imports.
 * chunk_0003.c:5948/5954 clears6fd/599 before all passes;7633–7637 records
 * ordinary reaction flags;8011–8019 applies balance depletion once per frame.
 * Admission/immunity/status and down-damage scaling remain explicit source
 * boundaries. Never derive these inputs from host `hit`/`down` or audit pairs.
 */
export interface DoubleCloneFrameSeed {
  readonly control5e0:number;
  /** Already resolved source1da at frame opening; do not assume it is zero. */
  readonly flags1da:number;
  readonly downGauge6c6:number;
  readonly balance6c2:number;
  readonly balanceBase6be:number;
}
export interface DoubleCloneReactionFrame extends DoubleCloneFrameSeed {
  readonly frameId:number;
  readonly flags6fd:number;
  readonly heavy599:number;
  readonly eventIds:readonly string[];
  readonly complete:boolean;
  readonly reaction:DoubleCloneReactionResult | null;
}
export type DoubleCloneFrameContact = {
  readonly frameId:number;
  /** Caller replay identity, NOT a source object ID or victim UID. Scoped to frame. */
  readonly eventId:string;
  /** False means no supported source write occurred, not any late early-return.
   * Some source immunity returns follow the6fd OR and must remain accepted. */
  readonly accepted:false;
} | {
  readonly frameId:number;
  readonly eventId:string;
  readonly accepted:true;
  readonly reactionFlags:number;
  readonly flagsB:number;
  /** Only bits actually written after source immunity/status decisions. */
  readonly resolvedFlags1daOr:number;
  /** Nonimmune flagsA800 early return at7520: no balance/down writes. */
  readonly heavyEarlyReturn:boolean;
  /** Null when source8011 block is not reached (including lethal contacts).
   * downSubtract is already scaled and gated by7de/control01000000. */
  readonly gauges:null | {readonly downSubtract:number;readonly balanceDamage:number};
};
const integer = (value:number,min:number,max:number):boolean =>
  Number.isInteger(value) && value >= min && value <= max;
const short = (value:number):number => (value << 16) >> 16;
function requireValid(ok:boolean,message:string):void {
  if (!ok) throw new RangeError(`[doubleCloneReactionFrame] ${message}`);
}
function validId(frameId:number):boolean { return Number.isSafeInteger(frameId) && frameId >= 0; }

/** Retain the previous frame until opening its strictly newer successor.
 * Old event lists are discarded at this boundary, not accumulated indefinitely.
 * Callers must retain the returned state; immutable historical branches are not
 * a global replay ledger. One instance belongs to one owner lifecycle only. */
export function beginDoubleCloneReactionFrame(previous:DoubleCloneReactionFrame | null,
  frameId:number,seed:DoubleCloneFrameSeed):DoubleCloneReactionFrame {
  requireValid(validId(frameId) && (!previous || (previous.complete && frameId > previous.frameId)),
    'frame must advance after finalization');
  requireValid(integer(seed.control5e0,0,0xffffffff) && integer(seed.flags1da,0,255) &&
    integer(seed.downGauge6c6,-32768,32767) && integer(seed.balance6c2,-32768,32767) &&
    integer(seed.balanceBase6be,-32768,32767),'invalid source seed');
  return {...seed,frameId,flags6fd:0,heavy599:0,eventIds:[],complete:false,reaction:null};
}
export function accumulateDoubleCloneReactionContact(frame:DoubleCloneReactionFrame,
  contact:DoubleCloneFrameContact):DoubleCloneReactionFrame {
  requireValid(!frame.complete && contact.frameId === frame.frameId,'closed or mismatched frame');
  requireValid(typeof contact.eventId === 'string' && contact.eventId.length > 0,'missing event ID');
  if (!contact.accepted || frame.eventIds.includes(contact.eventId)) return frame;
  requireValid(integer(contact.reactionFlags,0,255) && integer(contact.flagsB,0,65535) &&
    integer(contact.resolvedFlags1daOr,0,255),'invalid source contact flags');
  if (contact.gauges) requireValid(integer(contact.gauges.downSubtract,-32768,32767) &&
    integer(contact.gauges.balanceDamage,0,255),'invalid resolved gauge write');
  requireValid((!contact.heavyEarlyReturn && (contact.flagsB & 0xc00) === 0) || contact.gauges === null,
    'heavy or flagsB400/800 path returns before gauges');
  let flags6fd = frame.flags6fd;
  let downGauge6c6 = frame.downGauge6c6;
  let balance6c2 = frame.balance6c2;
  if (contact.heavyEarlyReturn || (contact.flagsB & 0xfc0) === 0) flags6fd |= contact.reactionFlags;
  if (contact.gauges) {
    downGauge6c6 = short(downGauge6c6 - contact.gauges.downSubtract);
    // The record OR happens BEFORE this guard, including a record-supplied80.
    if ((flags6fd & 0x80) === 0) {
      balance6c2 = short(balance6c2 - contact.gauges.balanceDamage);
      if (balance6c2 < 1) {
        balance6c2 = frame.balanceBase6be;
        flags6fd |= 0xa6;
      }
    }
  }
  return {...frame,flags6fd,downGauge6c6,balance6c2,
    heavy599:frame.heavy599 | (contact.heavyEarlyReturn ? 1 : 0),
    flags1da:frame.flags1da | contact.resolvedFlags1daOr | (contact.heavyEarlyReturn ? 1 : 0),
    eventIds:[...frame.eventIds,contact.eventId]};
}
export type DoubleCloneFrameTail = Omit<DoubleCloneReactionInput,
  'control5e0'|'flags6fd'|'flags1da'|'heavy599'|'downGauge6c6'|'frameAggregationComplete'>;
/** Call only after ALL contact passes. The frozen-in-time gauge must precede
 * source3d3e8 and host stagger resets. Unsupported stays unsupported. */
export function finalizeDoubleCloneReactionFrame(frame:DoubleCloneReactionFrame,
  frameId:number,tail:DoubleCloneFrameTail):DoubleCloneReactionFrame {
  requireValid(!frame.complete && frameId === frame.frameId,'closed or mismatched frame');
  const reaction = classifyDoubleCloneReaction({...tail,control5e0:frame.control5e0,
    flags6fd:frame.flags6fd,flags1da:frame.flags1da,heavy599:frame.heavy599,
    downGauge6c6:frame.downGauge6c6,frameAggregationComplete:true});
  return {...frame,complete:true,reaction};
}
export interface DoubleClonePostDispatchOwner {
  readonly arm7c8:number;
  readonly offset7b0:readonly [number,number,number];
  readonly lastPostDispatchId:number | null;
}
export interface DoubleClonePostDispatchInput {
  /** Caller transport sequence for actual owner dispatches, NOT collision frames.
   * Strictly increases within this owner lifecycle, including no-bit dispatches. */
  readonly dispatchId:number;
  /** Actual source control word sampled AFTER this actor's action dispatch,
   * immediately at its6f88c hook. Never substitute a collision classifier bit. */
  readonly liveControl5e0:number;
}
/** Source6f88c, independently checked from original instructions (omitted C).
 * The actor scheduler runs +4bc -> action -> +4c0 BEFORE collision processing.
 * Collision5c290/5c694 does not invoke +4c0. The next real post-hook therefore
 * reads live control after the intervening action handler, which can change the
 * collision-classified bit. This hook is deliberately independent of frames.
 * Clears arm iff live02000000; does not change control or normalize offset.
 * Caller must retain returned bookkeeping; this is not a global replay ledger. */
export function postDispatchDoubleCloneReaction(owner:DoubleClonePostDispatchOwner,
  dispatch:DoubleClonePostDispatchInput):DoubleClonePostDispatchOwner {
  requireValid(validId(dispatch.dispatchId) && integer(dispatch.liveControl5e0,0,0xffffffff),
    'invalid dispatch identity or live control word');
  requireValid(integer(owner.arm7c8,0,255) && (owner.lastPostDispatchId === null ||
    (validId(owner.lastPostDispatchId) && dispatch.dispatchId > owner.lastPostDispatchId)),
    'invalid owner or replayed post-dispatch identity');
  return {...owner,arm7c8:(dispatch.liveControl5e0 & 0x02000000) !== 0 ? 0 : owner.arm7c8,
    lastPostDispatchId:dispatch.dispatchId};
}
