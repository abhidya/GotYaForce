import {createBattleParticipantViewTestFixture} from './battle-participant-view.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Fixture=ReturnType<typeof createBattleParticipantViewTestFixture>;
type Visit=(owner:object,key:PropertyKey)=>void;
const HISTORY='80053a58 reached mandatory80054070',NEXT='8002948c reached mandatory80087cf0';
let fixtures=0;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-ordered-actor-prefix-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);}
/** Explicit entry inputs on six genuinely retained owners. Zero count is the
 * result of the real mass pass on inactive actors, never a replacement list. */
function fixture(make:Make,inactive=false):Fixture{
 fixtures++;const x=createBattleParticipantViewTestFixture(make,false,0);
 for(const [i,id]of x.physicalIdentities.entries()){
  x.world.getActorBinding(id).mode4a0=0;
  x.status.getActualBorg(id).burstArmFrames=[0,1,128,255,4,7][i]!;
  if(inactive)x.actors[i]!.active0=0;
 }
 return x;
}
function run(x:Fixture,expected:string,visit:Visit=()=>{}):void{
 const native=Object.getOwnPropertyDescriptor;let started=false;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.groups[39]&&key==='head')started=true;
  if(started)visit(owner,key);
  return native(owner,key);
 }) as typeof native;
 try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(started,'real scheduler39 returned before direct53a2c');
 refuses(()=>x.frame.runFrame(),'incomplete');
 refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
}
export function runBattleOrderedActorPrefixSelfTests(make:Make):void{
 fixtures=0;
 {
  const x=fixture(make),events:string[]=[];
  run(x,HISTORY,(o,k)=>{
   if(o===x.massPreparation.orderCount&&k==='count80436260')events.push('count');
   if(o===x.massPreparation.orderPointers&&k==='0')events.push('pointer');
   if(k==='byte6fc'||k==='burstArmFrames')throw Error('later helper read before54070');
  });
  check(events.join(',')==='count,pointer','live count before first current table pointer');
  check(x.massPreparation.orderCount.count80436260===6,'six genuinely admitted actors');
 }
 {
  const x=fixture(make,true);run(x,NEXT);
  check(x.massPreparation.orderCount.count80436260===0,'real inactive mass result');
  check(x.physicalIdentities.map(id=>x.status.getActualBorg(id).burstArmFrames).join(',')==='0,0,127,254,3,6','signed6fb wraps on every physical inactive actor');
 }
 {
  const x=fixture(make,true);x.statusState.byte6fc=128;
  run(x,'after6fc clear');check(x.statusState.byte6fc===0,'clear survives mandatory8c4 refusal');
  check(x.status.getActualBorg(x.physicalIdentities[1]!).burstArmFrames===1,'later countdown not reached');
 }
 {
  const x=fixture(make,true);x.statusState.byte6fc=1;Object.defineProperty(x.statusState,'byte6fc',{writable:false});
  run(x,'writable');check(x.statusState.byte6fc===1,'readonly clear never changes owner');
 }
 for(const kind of ['missing','readonly','shadow']as const){
  const x=fixture(make,true),later=x.status.getActualBorg(x.physicalIdentities[3]!);
  if(kind==='missing')Reflect.deleteProperty(later,'burstArmFrames');
  if(kind==='readonly')Object.defineProperty(later,'burstArmFrames',{writable:false});
  if(kind==='shadow')Object.assign(x.actors[3]!,{byte6fb:255});
  run(x,kind==='readonly'?'writable':kind==='missing'?'burstArmFrames':'competing source cell');
  check(x.status.getActualBorg(x.physicalIdentities[2]!).burstArmFrames===127,'earlier decrement survives later refusal');
  check(x.status.getActualBorg(x.physicalIdentities[4]!).burstArmFrames===4,'later actor remains untouched');
 }
 {
  const x=fixture(make,true);for(const row of x.teamRows103)row.byte10=1;
  run(x,NEXT,(_o,k)=>{if(k==='byte6fc'||k==='byte7de'||k==='field8c4')throw Error('guarded helper load');});
 }
 {
  fixtures++;const x=createBattleParticipantViewTestFixture(make);
  for(const id of x.physicalIdentities){x.world.getActorBinding(id).mode4a0=0;x.status.getActualBorg(id).burstArmFrames=7;}
  for(const actor of x.actors)actor.active0=0;
  run(x,'byte6fc: own data property');
  check(x.status.getActualBorg(x.actor).burstArmFrames===7,'missing reached second status cell precedes all countdown stores');
 }
 {
  const x=fixture(make,true);let removed=false;
  run(x,NEXT,(o,k)=>{if(!removed&&o===x.groups[39]&&k==='head'){
   removed=true;Reflect.deleteProperty(x.massPreparation,'orderPointers');
  }});check(removed,'unused ordered table can be absent after genuine zero-count preparation');
 }
 {
  const x=fixture(make);let changed=false;
  run(x,'owner changed',(o,k)=>{if(!changed&&o===x.massPreparation.orderCount&&k==='count80436260'){
   changed=true;x.massPreparation.orderPointers={...x.massPreparation.orderPointers};
  }});check(changed,'captured canonical ordered-table owner cannot be replaced');
 }
 for(const key of ['byte6fc','byte6fb']as const){
  const x=fixture(make,true);
  if(key==='byte6fc')Object.assign(x.actors[0]!,{byte6fc:0});
  else Object.assign(x.status.getActualBorg(x.actor),{byte6fb:0});
  run(x,'competing source cell');
  check(x.status.getActualBorg(x.physicalIdentities[1]!).burstArmFrames===1,'competing canonical owner refuses before later countdown');
 }
 for(const mode of ['null','foreign']as const){
  const x=fixture(make);let changed=false;
  run(x,mode==='null'?'actor':'unknown/non-owned pointer identity',(o,k)=>{if(!changed&&o===x.massPreparation.orderCount&&k==='count80436260'){
   changed=true;x.massPreparation.orderPointers[0]=mode==='null'?null:Symbol('unowned current pointer');
  }});check(changed,'current ordered pointer mutation is observed');
 }
 {
  const x=fixture(make);let changed=false;
  // An explicit live-input mutation test, not the zero-count baseline above.
  run(x,NEXT,(o,k)=>{if(!changed&&o===x.massPreparation.orderCount&&k==='count80436260'){
   changed=true;x.massPreparation.orderCount.count80436260=255;
  }});check(changed,'negative signed count bypasses54070 but not mandatory helpers');
 }
 for(const cross of [false,true]){
  const x=fixture(make);let attempted=false;
  run(x,'caught same-runtime reentry',(o,k)=>{if(!attempted&&o===x.massPreparation.orderCount&&k==='count80436260'){
   attempted=true;try{if(cross)x.scheduler.runWrapper(40);else x.frame.runFrame();}catch{}
  }});check(attempted,'caught nested execution still permanently closes frame');
 }
 console.log(`[battle-ordered-actor-prefix] PASS: ${fixtures} genuine compositions; direct53a2c ordering, signed count, partial6fc clear, canonical6fb wrapping and fail-closed unsupported boundaries; no complete-frame claim`);
}
