import type {DoubleCloneFrameContact} from './doubleCloneReactionFrame.js';

/** An inert source subset, not a host applyHit adapter. Callers must prove each
 * certificate from the actual admitted primary contact. A Double borg ID or an
 * audit overlap alone proves none of these conditions. null means unknown.
 * chunk_0003.c:7541–7549,7633–7637,7795–7814,7991–8019. */
export interface DoubleCloneOrdinaryContactInput {
  readonly frameId:number;
  readonly eventId:string;
  readonly acceptedPrimaryContact:boolean|null;
  readonly attackerUnpaired:boolean|null;
  readonly victimUnpaired:boolean|null;
  /** No other source status, immunity, reflection or special-contact branch. */
  readonly ordinaryStateVerified:boolean|null;
  readonly attackerOwnerClass83:number|null;
  /** Attacker OWNER6fc changes the7546 down-damage multiplier. */
  readonly attackerOwner6fc:number|null;
  readonly victimClass83:number|null;
  readonly victim6fc:number|null;
  readonly victimControl5e0:number|null;
  readonly victimFlags1da:number|null;
  readonly victim7de:number|null;
  /** Actual param_1+20 OBJECT+c4 at contact, NOT its owner's current power.
   * A launched shot can retain different power from its owner. No default1. */
  readonly attackingObjectPowerC4:number|null;
  readonly targetDescriptorFlags:number|null;
  readonly flagsA:number|null;
  readonly flagsB:number|null;
  readonly reactionFlags:number|null;
  readonly downGaugeDamage:number|null;
  readonly balanceGaugeDamage:number|null;
  /** Source post-damage HP1c6 and damage routine lethal outcome, not host HP. */
  readonly postHp1c6:number|null;
  readonly lethal:boolean|null;
}
export type DoubleCloneOrdinaryContactResult = {
  readonly type:'verified';
  readonly contact:Extract<DoubleCloneFrameContact,{accepted:true}>;
} | {readonly type:'unsupported';readonly reason:string};
const unsupported = (reason:string):DoubleCloneOrdinaryContactResult => ({type:'unsupported',reason});
const integer = (value:unknown,min:number,max:number):value is number =>
  typeof value === 'number' && Number.isInteger(value) && value >= min && value <= max;

/** Resolves only the writes consumed by the frame reducer. Does not apply HP,
 * gauge subtraction/reset, admission, status, actor dispatch or clone changes.
 * Target descriptor40 must be read and ruled out for this particular contact,
 * even if the original Double body table is independently known to lack it. */
export function resolveDoubleCloneOrdinaryContact(input:DoubleCloneOrdinaryContactInput):
  DoubleCloneOrdinaryContactResult {
  if (!integer(input.frameId,0,Number.MAX_SAFE_INTEGER)) return unsupported('invalid-frameId');
  if (typeof input.eventId !== 'string' || input.eventId.length === 0) return unsupported('invalid-eventId');
  for (const field of ['acceptedPrimaryContact','attackerUnpaired','victimUnpaired',
    'ordinaryStateVerified','lethal'] as const) {
    if (typeof input[field] !== 'boolean') return unsupported(`unknown-${field}`);
    if (field !== 'lethal' && !input[field]) return unsupported(`unproved-${field}`);
  }
  for (const field of ['attackerOwnerClass83','attackerOwner6fc','victimClass83','victim6fc',
    'victimFlags1da','victim7de','reactionFlags','balanceGaugeDamage'] as const) {
    if (input[field] == null) return unsupported(`unknown-${field}`);
    if (!integer(input[field],0,255)) return unsupported(`invalid-${field}`);
  }
  for (const field of ['targetDescriptorFlags','flagsA','flagsB','downGaugeDamage'] as const) {
    if (input[field] == null) return unsupported(`unknown-${field}`);
    if (!integer(input[field],0,65535)) return unsupported(`invalid-${field}`);
  }
  if (input.victimControl5e0 == null) return unsupported('unknown-victimControl5e0');
  if (!integer(input.victimControl5e0,0,0xffffffff)) return unsupported('invalid-victimControl5e0');
  if (input.postHp1c6 == null) return unsupported('unknown-postHp1c6');
  if (!integer(input.postHp1c6,0,32767)) return unsupported('invalid-postHp1c6');
  if (input.attackingObjectPowerC4 == null) return unsupported('unknown-attackingObjectPowerC4');
  if (typeof input.attackingObjectPowerC4 !== 'number' || !Number.isFinite(input.attackingObjectPowerC4))
    return unsupported('invalid-attackingObjectPowerC4');
  const power = Math.fround(input.attackingObjectPowerC4);
  if (!Number.isFinite(power)) return unsupported('invalid-attackingObjectPowerC4');
  if (input.attackerOwnerClass83 !== 0 || input.attackerOwner6fc !== 0)
    return unsupported('nonordinary-attacker-owner');
  if (input.victimClass83 !== 0 || input.victim6fc !== 0)
    return unsupported('nonordinary-victim');
  if ((input.victimControl5e0 & 0x11000000) !== 0)
    return unsupported('reacting-or-special-victim-control');
  if ((input.victimFlags1da! & ~1) !== 0) return unsupported('nonordinary-victim-flags1da');
  if ((input.targetDescriptorFlags! & 0x40) !== 0) return unsupported('target-descriptor40');
  if ((input.flagsA! & ~0x21) !== 0) return unsupported('unsupported-flagsA');
  if (input.flagsB !== 0) return unsupported('unsupported-flagsB');
  if (input.lethal !== (input.postHp1c6 === 0)) return unsupported('inconsistent-lethal-postHp1c6');
  // Original PPC8002e3c4–8002e40c: fsubs(power,1), fmuls(.5,delta),
  // fmuls(base,factor), fctiwz, then integer base addition. Constants at
  //80436f78=1 and80436f7c=.5. Reject out-of-range conversion rather than infer
  // an implementation-specific integer-indefinite result.
  const base = input.downGaugeDamage!;
  const factor = Math.fround(.5 * Math.fround(power - 1));
  const scaled = Math.fround(base * factor);
  const delta = Math.trunc(scaled);
  const damage = base + delta;
  if (!integer(delta,-0x80000000,0x7fffffff) || !integer(damage,-0x80000000,0x7fffffff))
    return unsupported('unrepresentable-scaled-down-damage');
  return {type:'verified',contact:{frameId:input.frameId,eventId:input.eventId,accepted:true,
    reactionFlags:input.reactionFlags!,flagsB:0,resolvedFlags1daOr:1,heavyEarlyReturn:false,
    gauges:input.lethal ? null : {downSubtract:input.victim7de === 0 ? (damage << 16) >> 16 : 0,
      balanceDamage:input.balanceGaugeDamage!}}};
}
