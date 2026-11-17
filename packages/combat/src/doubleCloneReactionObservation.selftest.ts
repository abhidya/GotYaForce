import {beginDoubleCloneReactionObservation as begin,observeDoubleCloneAcceptedContact as accept,
  finalizeDoubleCloneReactionObservation as finish,readDoubleCloneReactionObservation as read,
  DOUBLE_CLONE_OBSERVATION_CONTACT_LIMIT as limit} from './doubleCloneReactionObservation.js';
import {damageRecordByIndex} from './gauges.js';
import type {BorgRuntime} from './types.js';
function check(ok:unknown,message:string):asserts ok {
  if(!ok)throw Error(`[doubleCloneReactionObservation] ${message}`);
}
const owner=()=>({uid:'same-uid',borgId:'pl0003',alive:true,hp:100,state:'idle',
  downGauge:100,balanceGauge:200} as BorgRuntime);
export function runDoubleCloneReactionObservationSelfTest():void {
  const b=owner(),record={...damageRecordByIndex(0)};
  accept(b,record,null);check(read(b)===null,'no helper-created frame');
  begin(b,1);const opened=read(b)!;
  accept(b,record,'first');b.downGauge=40;accept(b,record,'second');
  const two=read(b)!;
  check(two.acceptedContactCount===2&&two.contacts[0]!.ordinal===1&&two.contacts[1]!.ordinal===2,
    'same victim retains distinct accepted-call ordinal');
  check(two.contacts[0]!.hostBefore.downGauge===100&&two.contacts[1]!.hostBefore.downGauge===40,
    'host snapshots remain diagnostic contact-time values');
  record.reactionFlags=255;
  check(two.contacts[0]!.record.reactionFlags!==255&&opened.contacts.length===0,
    'copied records and historical immutable observations');
  for(let i=2;i<limit+4;i++)accept(b,record,null);
  const capped=read(b)!;
  check(capped.contacts.length===limit&&capped.acceptedContactCount===limit+4&&
    capped.droppedContactCount===4&&capped.unknownReasons.includes('contact-observation-overflow'),
    'bounded overflow remains explicit unknown');
  finish(b,2);check(!read(b)!.complete,'mismatched close ignored');
  finish(b,1);const closed=read(b)!;
  accept(b,record,null);finish(b,1);begin(b,1);
  check(read(b)===closed&&closed.complete&&closed.sourceObservation==='unknown',
    'late events, repeat close and same-frame begin cannot change closed evidence');
  begin(b,2);check(read(b)!.contacts.length===0&&read(b)!.acceptedContactCount===0,
    'new frame discards old bounded ledger');
  const replacement=owner();check(read(replacement)===null,'same uid replacement is isolated');
  begin(replacement,2);accept(replacement,record,null);
  check(read(b)!.acceptedContactCount===0,'distinct owners and Battles do not share frames');
  b.borgId='pl0000';accept(b,record,null);finish(b,2);
  check(read(b)!.acceptedContactCount===0&&read(b)!.unknownReasons.includes('owner-form-changed'),
    'same object changing form cannot ingest another borg contact');
  const dead=owner();dead.alive=false;begin(dead,1);check(read(dead)===null,'dead owners do not open');
  const other=owner();other.borgId='pl0000';begin(other,1);check(read(other)===null,'only Double Ninja observed');
  check(Object.isFrozen(closed)&&Object.isFrozen(closed.contacts)&&Object.isFrozen(closed.contacts[0])&&
    Object.isFrozen(closed.contacts[0]!.record)&&Object.isFrozen(closed.contacts[0]!.hostBefore),
    'read-only observations cannot mutate combat or collector state');
}
