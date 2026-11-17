import {resolveDoubleCloneOrdinaryContact as resolve, type DoubleCloneOrdinaryContactInput}
  from './doubleCloneContact.js';
import {beginDoubleCloneReactionFrame as begin, accumulateDoubleCloneReactionContact as add}
  from './doubleCloneReactionFrame.js';
function assert(value:unknown,message:string):asserts value {
  if (!value) throw Error(`[doubleCloneContact] ${message}`);
}
const ordinary:DoubleCloneOrdinaryContactInput = Object.freeze({frameId:1,eventId:'first',
  acceptedPrimaryContact:true,attackerUnpaired:true,victimUnpaired:true,ordinaryStateVerified:true,
  attackerOwnerClass83:0,attackerOwner6fc:0,victimClass83:0,victim6fc:0,
  victimControl5e0:0,victimFlags1da:0,victim7de:0,attackingObjectPowerC4:1,
  targetDescriptorFlags:0,flagsA:1,flagsB:0,reactionFlags:1,downGaugeDamage:6,
  balanceGaugeDamage:6,postHp1c6:100,lethal:false});
function contact(patch:Partial<DoubleCloneOrdinaryContactInput> = {}) {
  const result = resolve({...ordinary,...patch});
  assert(result.type === 'verified',`expected verified: ${JSON.stringify(result)}`);
  return result.contact;
}
function unsupported(patch:Partial<DoubleCloneOrdinaryContactInput>,reason:string):void {
  const result = resolve({...ordinary,...patch});
  assert(result.type === 'unsupported' && result.reason === reason,
    `expected ${reason}: ${JSON.stringify(result)}`);
}
export function runDoubleCloneContactSelfTest():void {
  assert(contact().gauges?.downSubtract === 6,'neutral object power');
  assert(contact({attackingObjectPowerC4:2}).gauges?.downSubtract === 9,'nonneutral OBJECT power');
  assert(contact({downGaugeDamage:7,attackingObjectPowerC4:.5}).gauges?.downSubtract === 6,
    'negative intermediate truncates toward zero');
  assert(contact({downGaugeDamage:100,attackingObjectPowerC4:Math.fround(.1)}).gauges?.downSubtract === 55,
    'float32 steps yield -45 rather than double precision -44');
  assert(contact({downGaugeDamage:1023,attackingObjectPowerC4:Math.fround(3.2913)}).gauges?.downSubtract === 2195,
    'positive float32 product rounds before truncation');
  // Instruction-order oracle: subtraction, factor multiply, base multiply,
  // truncation and integer addition. Half-scaling is exact in this admitted
  // u16-base/finite-f32 domain, so moving the half to base does not provide a
  // distinct representable regression; retain the actual PPC order anyway.
  for (const base of [0,1,3,100,255,1023,32767,65535]) {
    for (const scale of [-3,-.1,0,.1,.5,1,1.0000001192092896,2,3.2913,100]) {
      const delta = Math.fround(Math.fround(scale) - 1);
      const factor = Math.fround(.5 * delta);
      const product = Math.fround(base * factor);
      const expected = ((base + Math.trunc(product)) << 16) >> 16;
      assert(contact({downGaugeDamage:base,attackingObjectPowerC4:scale}).gauges?.downSubtract === expected,
        `PPC numeric order base=${base} power=${scale}`);
    }
  }
  assert(contact({downGaugeDamage:65535}).gauges?.downSubtract === -1,'source signed-short65535');
  const gated = contact({victim7de:255});
  assert(gated.gauges?.downSubtract === 0 && gated.gauges.balanceDamage === 6,'7de gates only down');
  const lethal = contact({postHp1c6:0,lethal:true,reactionFlags:0x80});
  assert(lethal.gauges === null && lethal.reactionFlags === 0x80 && lethal.resolvedFlags1daOr === 1,
    'lethal contact retains prior source OR writes, with no ordinary gauges');
  for (const flagsA of [0,1,0x20,0x21]) assert(contact({flagsA}).flagsB === 0,'ordinary flagsA subset');
  for (let bit=1;bit<=0x8000;bit*=2) {
    if ((bit & 0x21) === 0) unsupported({flagsA:bit},'unsupported-flagsA');
    unsupported({flagsB:bit},'unsupported-flagsB');
  }
  unsupported({targetDescriptorFlags:0x40},'target-descriptor40');
  unsupported({targetDescriptorFlags:0x41},'target-descriptor40');
  unsupported({attackerOwnerClass83:0x10},'nonordinary-attacker-owner');
  unsupported({attackerOwner6fc:1},'nonordinary-attacker-owner');
  unsupported({victimClass83:0x10},'nonordinary-victim');
  unsupported({victim6fc:1},'nonordinary-victim');
  unsupported({victimControl5e0:0x01000000},'reacting-or-special-victim-control');
  unsupported({victimControl5e0:0x10000000},'reacting-or-special-victim-control');
  unsupported({victimFlags1da:2},'nonordinary-victim-flags1da');
  unsupported({postHp1c6:0,lethal:false},'inconsistent-lethal-postHp1c6');
  unsupported({postHp1c6:1,lethal:true},'inconsistent-lethal-postHp1c6');
  for (const field of ['acceptedPrimaryContact','attackerUnpaired','victimUnpaired','ordinaryStateVerified'] as const) {
    unsupported({[field]:false},`unproved-${field}`);
  }
  // Runtime callers can omit/mis-type source fields despite the TS contract.
  for (const field of Object.keys(ordinary) as (keyof DoubleCloneOrdinaryContactInput)[]) {
    if (field === 'frameId' || field === 'eventId') continue;
    unsupported({[field]:null},`unknown-${field}`);
    unsupported({[field]:undefined},`unknown-${field}`);
  }
  for (const power of [NaN,Infinity,-Infinity,Number.MAX_VALUE,'1',true]) {
    unsupported({attackingObjectPowerC4:power as number},'invalid-attackingObjectPowerC4');
  }
  unsupported({attackingObjectPowerC4:1e30},'unrepresentable-scaled-down-damage');
  unsupported({downGaugeDamage:-1},'invalid-downGaugeDamage');
  unsupported({balanceGaugeDamage:256},'invalid-balanceGaugeDamage');
  unsupported({frameId:-1},'invalid-frameId');
  unsupported({eventId:''},'invalid-eventId');

  const seed = {control5e0:0,flags1da:0,downGauge6c6:10,balance6c2:10,balanceBase6be:30};
  const original = Object.freeze(begin(null,1,seed));
  const first = add(original,contact());
  assert(first.downGauge6c6 === 4 && first.balance6c2 === 4 && first.flags6fd === 1,'first frame writes');
  assert(add(first,contact()) === first,'frame owns replay prevention');
  const second = add(first,contact({eventId:'second',reactionFlags:2}));
  const third = add(second,contact({eventId:'third'}));
  assert(second.flags6fd === 0xa7 && second.balance6c2 === 30 && second.downGauge6c6 === -2,
    'combined ordinary contacts cause one source balance break');
  assert(third.balance6c2 === 30 && third.downGauge6c6 === -8,'later contacts still write down, not balance');
  const raw80 = add(original,contact({reactionFlags:0x80}));
  assert(raw80.balance6c2 === 10 && raw80.downGauge6c6 === 4 && raw80.flags6fd === 0x80,
    'record OR precedes reducer balance guard');
  const dead = add(original,lethal);
  assert(dead.balance6c2 === 10 && dead.downGauge6c6 === 10 && dead.flags6fd === 0x80 && dead.flags1da === 1,
    'lethal frame integration preserves gauges');
  const blockedDown = add(original,gated);
  assert(blockedDown.downGauge6c6 === 10 && blockedDown.balance6c2 === 4,'7de integration preserves balance write');
  assert(original.downGauge6c6 === 10 && ordinary.attackingObjectPowerC4 === 1,'pure inputs unchanged');
}
