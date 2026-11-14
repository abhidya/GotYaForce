import {beginDoubleCloneReactionFrame as begin, accumulateDoubleCloneReactionContact as add,
  finalizeDoubleCloneReactionFrame as finish, postDispatchDoubleCloneReaction as post,
  type DoubleCloneFrameContact, type DoubleCloneFrameTail} from './doubleCloneReactionFrame.js';
function assert(value:unknown,message:string):asserts value {
  if (!value) throw Error(`[doubleCloneReactionFrame] ${message}`);
}
function throws(fn:()=>unknown,message:string):void {
  let thrown = false; try { fn(); } catch { thrown = true; } assert(thrown,message);
}
const seed = {control5e0:0,flags1da:0,downGauge6c6:10,balance6c2:10,balanceBase6be:30};
const tail:DoubleCloneFrameTail = {borg3e8:3,descriptorClass591:0,pairedState4a0:0,
  alive:true,ordinaryCollisionTail:true,alreadyReacting:false,entry540:0,phase544:0,
  immediateDispatchPermitted:true,recoveryTerrain5ef08:false};
const contact = (eventId:string, patch:Partial<Extract<DoubleCloneFrameContact,{accepted:true}>> = {}):
  Extract<DoubleCloneFrameContact,{accepted:true}> => ({frameId:1,eventId,accepted:true,
  reactionFlags:1,flagsB:0,resolvedFlags1daOr:1,heavyEarlyReturn:false,
  gauges:{downSubtract:6,balanceDamage:6},...patch});
export function runDoubleCloneReactionFrameSelfTest():void {
  const original = Object.freeze(begin(null,1,seed));
  assert(add(original,{frameId:1,eventId:'rejected',accepted:false}) === original,'rejected contact is inert');
  const one = add(original,contact('first'));
  assert(one.downGauge6c6 === 4 && one.balance6c2 === 4 && one.flags6fd === 1,'first writes');
  assert(original.downGauge6c6 === 10 && original.eventIds.length === 0,'pure input preservation');
  assert(add(one,contact('first')) === one,'same accepted contact is not replayed');
  const two = add(one,contact('second',{reactionFlags:2}));
  assert(two.downGauge6c6 === -2 && two.balance6c2 === 30 && two.flags6fd === 0xa7,'combined frame OR and break');
  const three = add(two,contact('third'));
  assert(three.balance6c2 === 30 && three.downGauge6c6 === -8,'balance once, down each contact');
  const done = finish(three,1,tail);
  assert(done.downGauge6c6 === -8 && done.reaction?.type === 'reset','final gauge retained before resets');
  throws(()=>add(done,contact('late')),'late contact rejected');
  throws(()=>finish(done,1,tail),'duplicate finalization rejected');
  throws(()=>begin(one,2,seed),'cannot drop unfinished frame');
  throws(()=>begin(done,1,seed),'old frame cannot reopen');
  throws(()=>add(original,contact('wrong',{frameId:2})),'wrong frame rejected');
  const next = begin(done,2,{...seed,flags1da:0x10});
  assert(next.flags6fd === 0 && next.heavy599 === 0 && next.eventIds.length === 0 && next.flags1da === 0x10,
    'next-frame reset is limited to known source fields');
  assert(add(next,contact('first',{frameId:2})).eventIds.length === 1,'event identity is frame-scoped');

  // Every special flagsB bit suppresses only the ordinary record OR, not a
  // fabricated immunity decision or a separately resolved gauge write.
  for (let flagsB=0;flagsB<=0xffff;flagsB++) {
    const result = add(original,contact('mask',{flagsB,reactionFlags:0x22,gauges:null}));
    assert(result.flags6fd === ((flagsB & 0xfc0) === 0 ? 0x22 : 0),`flagsB=${flagsB}`);
  }
  const specialBreak = add(original,contact('special',{flagsB:0x40,reactionFlags:0x40,
    gauges:{downSubtract:0,balanceDamage:10}}));
  assert(specialBreak.flags6fd === 0xa6,'resolved break is independent of suppressed ordinary OR');
  const raw80 = add(original,contact('raw80',{reactionFlags:0x80}));
  assert(raw80.balance6c2 === 10 && raw80.downGauge6c6 === 4,'raw record80 suppresses balance decrement');
  const heavy = add(original,contact('heavy',{heavyEarlyReturn:true,flagsB:0xfc0,gauges:null,
    resolvedFlags1daOr:0,reactionFlags:2}));
  assert(heavy.flags6fd === 2 && heavy.flags1da === 1 && heavy.heavy599 === 1 && heavy.downGauge6c6 === 10,
    'nonimmune heavy early return precedes ordinary flagsB gate');
  assert(finish(heavy,1,tail).reaction?.type === 'unsupported','heavy remains outside classifier scope');
  const status = add(original,contact('status',{resolvedFlags1daOr:0x11}));
  assert(finish(status,1,tail).reaction?.type === 'unsupported','resolved status is never ordinary hit');
  const wrapped = add(begin(null,1,{...seed,downGauge6c6:-32768}),contact('wrap',{
    gauges:{downSubtract:1,balanceDamage:0}}));
  assert(wrapped.downGauge6c6 === 32767,'source signed-short wrap');
  const balanceWrap = add(begin(null,1,{...seed,balance6c2:-32768}),contact('balance-wrap',{
    gauges:{downSubtract:0,balanceDamage:1}}));
  assert(balanceWrap.balance6c2 === 32767 && balanceWrap.flags6fd === 1,'balance wrap does not falsely break');
  const positive = finish(add(original,contact('partial',{reactionFlags:2})),1,tail);
  assert(positive.reaction?.type === 'preserve' && !positive.reaction.enteredReaction,
    'single partial hit does not invent host forced stagger');
  const zero = finish(add(original,contact('zero',{reactionFlags:1,
    gauges:{downSubtract:10,balanceDamage:0}})),1,tail);
  assert(zero.reaction?.type === 'preserve' && zero.reaction.enteredReaction,'zero gauge enters1to4');

  const offset = Object.freeze([3,4,5] as const);
  const owner = Object.freeze({arm7c8:1,offset7b0:offset,lastPostDispatchId:null});
  const dispatch = Object.freeze({dispatchId:100,liveControl5e0:0x02000000});
  const cleared = post(owner,dispatch);
  assert(cleared.arm7c8 === 0 && cleared.offset7b0 === offset && owner.arm7c8 === 1,'posthook only clears arm');
  assert(dispatch.liveControl5e0 === 0x02000000,'posthook does not clear control bit');
  // A collision reset prediction can be invalidated by the next action handler.
  assert(done.reaction?.type === 'reset' &&
    post(owner,{dispatchId:100,liveControl5e0:0}).arm7c8 === 1,
    'stale collision reset cannot override a cleared live bit');
  assert(positive.reaction?.type === 'preserve' &&
    post(owner,dispatch).arm7c8 === 0,
    'intervening action can set the live bit after a preserve prediction');
  const unsupported = finish(one,1,{...tail,immediateDispatchPermitted:false,alive:false});
  assert(unsupported.reaction?.type === 'unsupported' && post(owner,dispatch).arm7c8 === 0,
    'a proved actual hook reads live control independently of an unsupported classifier');
  for (const liveControl5e0 of [0,1,0x40,0x01000000,0x80000000,0xfdffffff]) {
    const kept = post(owner,{dispatchId:100,liveControl5e0});
    assert(kept.arm7c8 === 1 && kept.offset7b0 === offset && kept.lastPostDispatchId === 100,
      'unrelated control bits preserve arm and consume dispatch identity');
    throws(()=>post(kept,{dispatchId:100,liveControl5e0:0x02000000}),
      'no-bit dispatch cannot replay with changed input');
  }
  for (const liveControl5e0 of [0x02000000,0x02000040,0xffffffff]) {
    assert(post(owner,{dispatchId:100,liveControl5e0}).arm7c8 === 0,'live reset bit clears arm');
  }
  assert(post(cleared,{dispatchId:101,liveControl5e0:0}).arm7c8 === 0,'next dispatch does not rearm');
  throws(()=>post(cleared,dispatch),'same dispatch cannot replay');
  throws(()=>post(cleared,{dispatchId:99,liveControl5e0:0}),'old dispatch cannot replay');
  throws(()=>post(owner,{dispatchId:NaN,liveControl5e0:0}),'invalid dispatch ID');
  for (const liveControl5e0 of [-1,0x100000000,NaN,0.5]) {
    throws(()=>post(owner,{dispatchId:100,liveControl5e0}),'invalid live source control');
  }
  throws(()=>add(original,contact('bad',{heavyEarlyReturn:true})),'heavy cannot also write gauges');
  throws(()=>add(original,contact('early',{flagsB:0x400})),'special early return cannot write gauges');
  throws(()=>begin(null,NaN,seed),'invalid frame ID');
  throws(()=>begin(null,0,{...seed,flags1da:256}),'invalid source byte');
}
