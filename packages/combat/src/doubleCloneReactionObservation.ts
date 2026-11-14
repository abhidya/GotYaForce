import type {BorgRuntime} from './types.js';
import type {DamageRecord} from './gauges.js';

/** Transport evidence only. This is NOT a source reaction frame and never calls
 * the classifier or owner post-dispatch hook. Source actor updates/post-hook run
 * before collision tail, so this frame's contacts cannot authorize that hook.
 * Weak object identity, not uid, scopes observations to one deployment/Battle. */
export const DOUBLE_CLONE_OBSERVATION_CONTACT_LIMIT = 64;
export interface DoubleCloneHostSnapshot {
  readonly hp:number;
  readonly state:BorgRuntime['state'];
  readonly downGauge:number;
  readonly balanceGauge:number;
}
export interface DoubleCloneAcceptedContactObservation {
  /** Monotonic accepted applyHit call ordinal within this owner/frame. */
  readonly ordinal:number;
  readonly eventId:string;
  readonly attackerUid:string|null;
  readonly hostBefore:DoubleCloneHostSnapshot;
  readonly record:Readonly<Pick<DamageRecord,'index'|'flagsA'|'flagsB'|'reactionFlags'|
    'downGaugeDamage'|'balanceGaugeDamage'>>;
}
export interface DoubleCloneReactionObservation {
  readonly frameId:number;
  readonly ownerUid:string;
  readonly complete:boolean;
  readonly hostAtOpen:DoubleCloneHostSnapshot;
  readonly hostAtClose:DoubleCloneHostSnapshot|null;
  readonly acceptedContactCount:number;
  readonly droppedContactCount:number;
  readonly contacts:readonly DoubleCloneAcceptedContactObservation[];
  readonly sourceObservation:'unknown';
  readonly unknownReasons:readonly string[];
}
const observations = new WeakMap<BorgRuntime,DoubleCloneReactionObservation>();
const missingSourceFields = Object.freeze([
  'source-1da-and-immunity-resolved-contact-writes-unavailable',
  'source-gauge-scaling-and-7de-control-gates-unavailable',
  'source-control-entry-phase-and-dispatch-state-not-authoritative',
  'source-collision-tail-and-recovery-terrain-unavailable',
]);
function snapshot(owner:BorgRuntime):DoubleCloneHostSnapshot {
  return Object.freeze({hp:owner.hp,state:owner.state,downGauge:owner.downGauge,
    balanceGauge:owner.balanceGauge});
}
/** Only Battle's real simulation boundary opens a frame. No implicit frame is
 * created by direct helper hits, rejected contacts, or audit collision pairs. */
export function beginDoubleCloneReactionObservation(owner:BorgRuntime,frameId:number):void {
  if(owner.borgId!=='pl0003'||!owner.alive)return;
  const previous=observations.get(owner);
  if(!Number.isSafeInteger(frameId)||frameId<0||(previous&&frameId<=previous.frameId))return;
  observations.set(owner,Object.freeze({frameId,ownerUid:owner.uid,complete:false,
    hostAtOpen:snapshot(owner),hostAtClose:null,acceptedContactCount:0,droppedContactCount:0,
    contacts:Object.freeze([]),sourceObservation:'unknown',unknownReasons:missingSourceFields}));
}
/** Sole caller: accepted applyHit, after all admission gates, before any host
 * mutation. Raw record flags are not resolved source flags1da/6fd. Host gauge
 * snapshots must never seed the source reducer, particularly after stagger reset
 * or a preceding same-frame contact. No victim-uid deduplication occurs here. */
export function observeDoubleCloneAcceptedContact(owner:BorgRuntime,record:DamageRecord,
  attackerUid:string|null):void {
  const frame=observations.get(owner);
  if(!frame||frame.complete)return;
  if(owner.borgId!=='pl0003'){
    if(!frame.unknownReasons.includes('owner-form-changed'))observations.set(owner,Object.freeze({
      ...frame,unknownReasons:Object.freeze([...frame.unknownReasons,'owner-form-changed'])}));
    return;
  }
  const ordinal=frame.acceptedContactCount+1;
  const overflow=frame.contacts.length>=DOUBLE_CLONE_OBSERVATION_CONTACT_LIMIT;
  const contact:DoubleCloneAcceptedContactObservation|null=overflow?null:Object.freeze({
    ordinal,eventId:`${frame.frameId}:${ordinal}`,attackerUid,hostBefore:snapshot(owner),
    record:Object.freeze({index:record.index,flagsA:record.flagsA,flagsB:record.flagsB,
      reactionFlags:record.reactionFlags,downGaugeDamage:record.downGaugeDamage,
      balanceGaugeDamage:record.balanceGaugeDamage})});
  observations.set(owner,Object.freeze({...frame,acceptedContactCount:ordinal,
    droppedContactCount:frame.droppedContactCount+(overflow?1:0),
    contacts:contact?Object.freeze([...frame.contacts,contact]):frame.contacts,
    unknownReasons:overflow&&frame.droppedContactCount===0?
      Object.freeze([...missingSourceFields,'contact-observation-overflow']):frame.unknownReasons}));
}
/** Close after melee AND projectile passes, before owner replacement. Final host
 * gauges are diagnostic only; they already include host stagger resets. */
export function finalizeDoubleCloneReactionObservation(owner:BorgRuntime,frameId:number):void {
  const frame=observations.get(owner);
  if(!frame||frame.complete||frame.frameId!==frameId)return;
  observations.set(owner,Object.freeze({...frame,complete:true,hostAtClose:snapshot(owner),
    unknownReasons:owner.borgId!=='pl0003'&&!frame.unknownReasons.includes('owner-form-changed')?
      Object.freeze([...frame.unknownReasons,'owner-form-changed']):frame.unknownReasons}));
}
export function readDoubleCloneReactionObservation(owner:BorgRuntime):DoubleCloneReactionObservation|null {
  return observations.get(owner)??null;
}
