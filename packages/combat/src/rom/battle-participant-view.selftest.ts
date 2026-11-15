import {createBattleLeaderSelectionTestFixture} from './battle-leader-selection.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {SourceBattleSystemGlobals,SourceBattleOuterGlobalFields} from './battle-global-layout.js';
import type {SourceActorPlayerSlotRecord} from './actor-slot-status.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const NORMAL='unknown/non-owned matrix-update actor',PAUSED='800294c8 reached mandatory80089554';
const pointers=['pointer14','pointer18','pointer1c','pointer20'] as const;
const metadata=['byte0c','byte0d','byte0e','byte0f'] as const;
const selectors=['byteC0','byteC1','byteC2','byteC3'] as const;
let fixtures=0;
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-participant-view-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
/** Explicit current synthetic cells on the same six-actor leader graph. No
 * replacement helper, callback, actor activation hook or source constructor. */
export function createBattleParticipantViewTestFixture(make:Make,paused=false,status6fc?:number) {
 fixtures++;const x=createBattleLeaderSelectionTestFixture(make,status6fc);
 // Explicit empty source lists for the first outer scheduler calls. The
 // genuinely spawned projectile stays in its allocator-owned group9.
 for(const group of [...Array.from({length:16},(_,i)=>32+i),57,58])x.groups[group]={head:null,tail:null};
 const system=x.systemGlobals as SourceBattleSystemGlobals,match=x.matchGlobals as typeof x.matchGlobals & SourceBattleOuterGlobalFields;
 Object.assign(system,{byte40:0,byte29:2,pointer14:null,pointer18:null,pointer1c:null,pointer20:null,
  byte0c:201,byte0d:202,byte0e:203,byte0f:204,controllerMask:63});
 Object.assign(match,{byteC0:0,byteC1:1,byteC2:2,byteC3:3,byte15db:63});
 for(let i=0;i<13;i++) {
  const row=x.slotRecords[i]??(x.slotRecords[i]={});Object.assign(row,{state18:i%3,byte10:40+i});
 }
 [0x800105ac,0x800105ac,0x80010570,0x80010578,0x80010580,0x80010588,0x80010590,0x80010598,0x800105a0,0x800105a8]
  .forEach((word,i)=>{x.dispatch3938[i]=word;});
 for(const a of x.actors)Object.assign(a,{byte43d:10,byte487:99});
 if(paused)match.byte66=1;
 return Object.assign(x,{system,match,paused});
}
type Fixture=ReturnType<typeof createBattleParticipantViewTestFixture>;
function closed(x:Fixture):void {
 check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'retained root actor closes');
 for(const a of x.actors)check(!isSourceActorDoubleFrameClaimed(a),'no actor-frame authority');
 refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const f of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(f,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
 refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
}
/** Descriptor observation changes only declared input records, never methods.
 * Actual source loads are distinguished from immutable diagnostic metadata. */
function run(x:Fixture,expected=x.paused?PAUSED:NORMAL,before:Visit=()=>{},after:Visit=()=>{}) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];let started=false,finished=false,schedulerReads=0,prefixReached=false,prefixModes=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.system&&key==='byte40')started=true;
  if(started&&!finished) {
   if(owner===x.system&&['byte40','controllerMask','byte29',...pointers,...metadata].includes(String(key)))events.push('P.'+String(key));
   if(owner===x.match&&[...selectors,'byte15db','byte66'].includes(String(key)))events.push('M.'+String(key));
   if(owner===x.actorSlots&&/^[0-9]+$/.test(String(key)))events.push('slot'+String(key));
   const index=x.actors.indexOf(owner as typeof x.actors[number]);
   if(index>=0&&['active0','byte43d','byte487'].includes(String(key)))events.push(`a${index}.${String(key)}`);
   for(let i=0;i<13;i++)if(owner===x.slotRecords[i]&&['state18','byte10'].includes(String(key)))events.push(`r${i}.${String(key)}`);
   if(owner===x.dispatch3938&&/^\d+$/.test(String(key)))events.push('dispatch'+String(key));
   if(owner===x.outerSources&&key==='systemGlobals')events.push('reloadP');
   if(owner===x.groups||owner===x.objectBytes||owner===x.nextObjectBytes||owner===x.match&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
   before(owner,key);
   if(owner===x.match&&key==='byte66')finished=true;
  }
  if(finished&&owner===x.groups[39]&&key==='head')prefixReached=true;
  if(prefixReached&&key==='mode4a0')prefixModes++;
  const result=native(owner,key);if(started)after(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 if(expected===NORMAL)check(prefixReached&&prefixModes>0,'completed wrappers reach real5ace8 matrix prerequisite');
 check(started,'actual bef4 entry reached');equal(schedulerReads,0,'no scheduler masks/groups/snapshots before fresh mode load');closed(x);return{events,message};
}
function viewIndex(x:Fixture,index:number):number {
 const value=Reflect.get(x.system,pointers[index]!);
 if(typeof value!=='symbol')throw Error('[battle-participant-view-test] published opaque view identity required');
 const address=x.allocator.getInteriorAddress(value);
 if(address===null)throw Error('[battle-participant-view-test] view is an actual interior identity');
 equal(x.allocator.getPointerTarget(address.base),x.slotRecords,'same canonical player table address base');
 return (address.byteOffset-0x394)/0x3e4;
}
function published(x:Fixture,records:readonly number[],bytes?:readonly number[]):void {
 for(let i=0;i<4;i++){equal(viewIndex(x,i),records[i],'selected logical row+394');equal(Reflect.get(x.system,metadata[i]!),bytes?.[i]??40+records[i]!,'fresh metadata byte');}
}
function inputLaziness(make:Make):void {
 const x=createBattleParticipantViewTestFixture(make,true);delete x.outerSources.massPreparation;delete x.outerSources.targetPreparation;
 Object.defineProperty(x.outerSources,'participantViews',{get(){throw Error('ordinary path read special global ingress');}});
 x.system.byte29=255;for(let i=1;i<4;i++)Reflect.deleteProperty(x.match,selectors[i]!);
 Reflect.deleteProperty(x.match,'byte15db');x.match.byteC0=255;
 const before=[x.massPreparation.rngState.byte804360c6,x.massPreparation.rngState.byte804360c7];
 run(x);published(x,[0,0,0,0]);equal(x.actors[0]!.byte487,0,'single selected actor gets index0');
 equal(x.massPreparation.rngState.byte804360c6,before[0],'paused low RNG remains');equal(x.massPreparation.rngState.byte804360c7,before[1],'paused high RNG remains');
 for(const a of x.actors)equal(a.byte335,77,'paused path never executes leader writes');
}
function baseline(make:Make):void {
 const x=createBattleParticipantViewTestFixture(make),r=run(x);published(x,[0,1,2,3]);
 check(!Object.hasOwn(x.outerSources,'participantViews'),'ordinary source needs no special ingress');
 equal(x.massPreparation.orderCount.count80436260,6,'genuine mass ordering completes');
 for(let i=0;i<6;i++) {
  equal(x.actors[i]!.mass208,0,'real lifecycle-zero mass');equal(x.actors[i]!.field664,1,'real ordering reset');
  equal(x.actors[i]!.pointer330,x.physicalIdentities[4+(i&1)],'real27764 leader publication');
  equal(x.actors[i]!.byte487,i<4?i:99,'only selected original slots are marked');
  check(hasIncompleteSourceActorDoubleLifecycle(x.actors[i]!),'all six genuinely retained actors close');
 }
 const scalar=r.events.filter(e=>!e.startsWith('reloadP')&&!/^P\.(pointer|byte0)/.test(e)&&!e.endsWith('.byte487'));
 const expected=['P.byte40','P.controllerMask','slot0','a0.active0','P.byte29'];
 for(let i=0;i<4;i++)expected.push('M.'+selectors[i],'M.byte15db',`r${i}.state18`,`slot${i}`,`a${i}.byte43d`,`r${i}.byte10`,`slot${i}`);
 expected.push('M.byte66');equal(scalar.join(','),expected.join(','),'complete ordered source scalar loads');
}
function modes(make:Make):void {
 for(const mode of [0,1,2,3,127,128,254,255]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=mode;const r=run(x);
  published(x,mode===2?[0,1,2,3]:mode===1?[0,1,0,1]:[0,0,0,0]);
  const reads=r.events.filter(e=>/^r\d+\.byte10$/.test(e));
  equal(reads.join(','),(mode===2?[0,1,2,3]:mode===1?[0,0,1,1]:[0,0,0,0]).map(i=>`r${i}.byte10`).join(','),'duplicate metadata load order');
  equal(r.events.filter(e=>e.endsWith('.state18')).length,mode===2?4:mode===1?2:1,'genuine10514 count');
  const order=mode===2?[[0],[1],[2],[3]]:mode===1?[[0,2],[1,3]]:[[0,1,2,3]];
  const stores=order.flatMap((views,i)=>[...views.flatMap(v=>['P.'+pointers[v],'P.'+metadata[v]]),`a${i}.byte487`]);
  equal(r.events.filter(e=>/^P\.(pointer|byte0)/.test(e)||e.endsWith('.byte487')).join(','),stores.join(','),'source-ordered pointer/metadata/actor stores');
  equal(r.events.filter(e=>e==='reloadP').length,8,'ordinary paths reload P before every one of eight view stores');
  if(mode!==2){equal(x.system.pointer14,x.system.pointer1c,'duplicate logical views preserve pointer identity');if(mode!==1)equal(x.system.pointer14,x.system.pointer18,'all four copies share one identity');}
 }
 for(const mode of [0,1,2]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=mode;for(const key of selectors)Reflect.set(x.match,key,0);
  run(x);published(x,[0,0,0,0]);equal(x.actors[0]!.byte487,mode===2?3:mode===1?1:0,'repeated original selected slot is last-store-wins');
 }
}
function shifts(make:Make):void {
 for(const raw of [0,1,5,6,7,8,31,32,63,64,65,96,127,128,192,224,254,255])for(const mask of [0,1,2,63,255]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.system.controllerMask=4;x.match.byteC0=raw;x.match.byte15db=mask;
  const signed=raw<128?raw:raw-256,shift=signed&63,bit=shift>=32?0:2**shift,
   selected=signed===-1||(mask&bit)===0?2:signed;
  const r=run(x,selected<0||selected>=13?'slot':selected>=6?'six-word':PAUSED);
  equal(r.events.filter(e=>e==='M.byte15db').length,raw===255?0:1,'only signed-1 skips selection mask');
  if(selected>=0&&selected<6){published(x,[selected,selected,selected,selected]);equal(x.actors[selected]!.byte487,0,'fresh original slot selected');}
  else {check(pointers.every(key=>Reflect.get(x.system,key)===null),'invalid selected slot has no caller writes');
   if(selected===6||selected===7)equal(r.events.filter(e=>e===`r${selected}.state18`).length,1,'bounded player read precedes six-word refusal');}
 }
}
function fallback(make:Make):void {
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.system.controllerMask=0;x.match.byteC0=255;
  const r=run(x);published(x,[0,0,0,0]);equal(r.events.filter(e=>e==='P.controllerMask').length,6,'all six disabled masks read live');
  equal(r.events.filter(e=>e.endsWith('.active0')).length,0,'disabled slots never dereferenced');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.system.controllerMask=63;x.match.byteC0=255;
  x.actors[0]!.active0=0;x.actors[1]!.active0=255;
  const r=run(x);published(x,[1,1,1,1]);equal(r.events.filter(e=>e.endsWith('.active0')).join(','),'a0.active0,a1.active0','first signed nonzero active stops scan');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.system.controllerMask=0;x.match.byteC0=255;let n=0;
  run(x,PAUSED,(o,k)=>{if(o===x.system&&k==='controllerMask'&&++n===3)x.system.controllerMask=4;});
  published(x,[2,2,2,2]);equal(n,3,'captured P mask reloaded per reached candidate');
 }
}
function helpers(make:Make):void {
 for(const high of [0,2])for(const low of [0,2,10,130]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.slotRecords[0]!.state18=high;x.actors[0]!.byte43d=low;
  delete x.slotRecords[6]!.state18;
  const alternate=(low&127)===2;run(x);published(x,Array(4).fill(alternate?6:0));
  equal(x.actors[0]!.byte487,0,'final actor is original slot even for alternate row');equal(x.actors[1]!.byte487,99,'unselected actor unchanged');
 }
}
function special(make:Make):void {
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte40=1;
  run(x,'participantViews');check(pointers.every(k=>Reflect.get(x.system,k)===null),'missing explicit special global precedes all view writes');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte40=1;x.outerSources.participantViews={};
  run(x,'byte804360dc');check(pointers.every(k=>Reflect.get(x.system,k)===null),'special global byte is never defaulted');
 }
 for(const raw of [1,128,255]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte40=raw;
  x.outerSources.participantViews={byte804360dc:4};delete x.slotRecords[12]!.state18;
  Reflect.deleteProperty(x.system,'controllerMask');Reflect.deleteProperty(x.system,'byte29');
  for(const key of [...selectors,'byte15db'])Reflect.deleteProperty(x.match,key);
  for(const a of x.actors){delete a.byte43d;delete a.active0;}
  const r=run(x);published(x,[12,12,12,12]);equal(x.actors[4]!.byte487,0,'special final slot4');
  equal(r.events.filter(e=>e==='r12.byte10').length,4,'special metadata reread four times');
  equal(r.events.filter(e=>e==='reloadP').length,7,'special first store uses captured P, followed by seven reloads');
  const stores=pointers.flatMap((key,i)=>['P.'+key,'r12.byte10','reloadP','P.'+metadata[i],...(i===3?[]:['reloadP'])]);
  equal(r.events.filter(e=>/^P\.(pointer|byte0)/.test(e)||e==='r12.byte10'||e==='reloadP').join(','),stores.join(','),'special source-exact interleaving and capture');
  check(!r.events.some(e=>e.includes('state18')||e.includes('43d')||e.includes('controllerMask')||e.includes('byte29')||e.includes('dispatch')),'special skips ordinary-only inputs');
 }
 for(const raw of [6,127,128,255]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte40=1;x.outerSources.participantViews={byte804360dc:raw};
  run(x,'slot');published(x,[12,12,12,12]);for(const a of x.actors)equal(a.byte487,99,'out-of-domain special slot refuses after all views');
 }
}
function liveReads(make:Make):void {
 for(const special of [false,true]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.system.byte40=special?1:0;
  if(special)x.outerSources.participantViews={byte804360dc:0};const row=x.slotRecords[special?12:0]!;let reads=0;
  run(x,PAUSED,(o,k)=>{if(o===row&&k==='byte10'){Reflect.set(row,'byte10',70+reads);reads++;}});
  published(x,Array(4).fill(special?12:0),[70,71,72,73]);equal(reads,4,'metadata never cached');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;x.actors[0]!.byte43d=2;let changed=false;
  run(x,PAUSED,(o,k)=>{if(o===x.slotRecords[6]&&k==='byte10'&&!changed){changed=true;x.actorSlots[0]=x.physicalIdentities[5]!;}});
  published(x,[6,6,6,6]);equal(x.actors[0]!.byte487,99,'helper-observed actor is not reused');equal(x.actors[5]!.byte487,0,'fresh original slot pointer gets final487');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=2;let changed=false;
  run(x,NORMAL,(o,k)=>{if(o===x.actors[3]&&k==='byte487'&&!changed){changed=true;x.match.byte66=0;}});
  check(changed,'post-bef4 fresh match-mode control reached');
 }
}
function partial(make:Make):void {
 for(const field of [...pointers,...metadata,'byte487'] as const)for(const kind of ['missing','readonly','accessor'] as const) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;
  const owner=field==='byte487'?x.actors[0]!:x.system;let calls=0;
  if(kind==='missing')Reflect.deleteProperty(owner,field);
  else Object.defineProperty(owner,field,kind==='readonly'?{writable:false}:{get(){calls++;throw Error('invoked destination');},configurable:true});
  run(x,field);equal(calls,0,'invalid destination getter never runs');
  const faultIndex=field==='byte487'?8:pointers.includes(field as typeof pointers[number])?2*pointers.indexOf(field as typeof pointers[number]):2*metadata.indexOf(field as typeof metadata[number])+1;
  for(let i=0;i<4;i++) {
   if(2*i<faultIndex)equal(viewIndex(x,i),0,'prior pointer write retained');
   else if(pointers[i]!==field)equal(Reflect.get(x.system,pointers[i]!),null,'later pointer untouched');
   if(2*i+1<faultIndex)equal(Reflect.get(x.system,metadata[i]!),40,'prior metadata retained');
   else if(metadata[i]!==field)equal(Reflect.get(x.system,metadata[i]!),201+i,'later metadata untouched');
  }
  if(field!=='byte487')equal(x.actors[0]!.byte487,99,'no final actor write before four views');
 }
 for(const readIndex of [1,2,3,4]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;let reads=0;
  run(x,'byte10',(o,k)=>{if(o===x.slotRecords[0]&&k==='byte10'&&++reads===readIndex)Reflect.deleteProperty(o,'byte10');});
  for(let i=0;i<4;i++){if(i<readIndex)equal(viewIndex(x,i),0,'pointer before missing metadata survives');else equal(Reflect.get(x.system,pointers[i]!),null,'later pointer absent');
   equal(Reflect.get(x.system,metadata[i]!),i<readIndex-1?40:201+i,'metadata exact prefix');}
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);Reflect.deleteProperty(x.slotRecords[2]!,'byte10');run(x,'byte10');
  equal(x.actors[0]!.byte487,0,'first iteration survives');equal(x.actors[1]!.byte487,1,'second iteration survives');equal(x.actors[2]!.byte487,99,'failed iteration final store absent');
  equal(viewIndex(x,2),2,'third pointer survives');equal(x.system.pointer20,null,'fourth iteration never entered');
 }
}
function refusalGuards(make:Make):void {
 {
  const x=createBattleParticipantViewTestFixture(make,true);delete x.outerSources.systemGlobals;
  refuses(()=>x.frame.runFrame(),'systemGlobals');closed(x);check(pointers.every(k=>Reflect.get(x.system,k)===null),'missing actual P owner does not fabricate views');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);delete x.system.byte40;run(x,'byte40');
  check(pointers.every(k=>Reflect.get(x.system,k)===null),'missing actual40 is the real entry boundary');
 }
 for(const field of ['byte40','byte29','controllerMask'] as const)for(const bad of [-1,256,0.5,NaN,Infinity,'0']) {
  const x=createBattleParticipantViewTestFixture(make,true);Reflect.set(x.system,field,bad);run(x,field);
  check(pointers.every(k=>Reflect.get(x.system,k)===null),'bad reached scalar leaves view destinations');
 }
 for(const where of ['byte40','state18','byte10','pointer14','byte487']) {
  const x=createBattleParticipantViewTestFixture(make,true);let entered=false;
  run(x,'reentry',(o,k)=>{if(!entered&&k===where&&(o===x.system||o===x.slotRecords[0]||o===x.actors[0])){entered=true;refuses(()=>x.frame.runFrame(),'reentry');}});
  check(entered,'reentry source point reached');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;let changed=false;
  run(x,'changed',(o,k)=>{if(o===x.slotRecords[0]&&k==='byte10'&&!changed){changed=true;x.slotStatusSources.slotRecords={...x.slotRecords};}});
  check(changed,'stale table mutation reached');
 }
 {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;let reads=0;
  run(x,'changed',(o,k)=>{if(o===x.slotRecords[0]&&k==='byte10'&&++reads===1)x.slotRecords[0]={state18:0,byte10:17} as SourceActorPlayerSlotRecord;});
  equal(viewIndex(x,0),0,'first pointer retained after stale row refusal');
 }
 for(const alias of ['system','actor','other-row'] as const) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;
  x.slotRecords[0]=(alias==='system'?x.system:alias==='actor'?x.actors[0]:x.slotRecords[1]) as SourceActorPlayerSlotRecord;
  run(x,'alias');
 }
}
/** Uppercase spellings are the same raw bytes, including aliases added after
 * the destination's observable descriptor was read. No shadow may reach a store. */
function uppercaseAliases(make:Make):void {
 const cases:[string,typeof pointers[number]|typeof metadata[number]][]=[
  ['byte1A','pointer18'],['byte1B','pointer18'],
  ['byte1C','pointer1c'],['byte1D','pointer1c'],['byte1E','pointer1c'],['byte1F','pointer1c'],
  ['byte0C','byte0c'],['byte0D','byte0d'],['byte0E','byte0e'],['byte0F','byte0f']];
 for(const [alias,field]of cases)for(const late of [false,true]) {
  const x=createBattleParticipantViewTestFixture(make,true);x.system.byte29=0;let injected=false;
  if(!late)Reflect.set(x.system,alias,99);
  run(x,'competing',()=>{},(owner,key)=>{
   if(late&&!injected&&owner===x.system&&key===field){injected=true;Reflect.set(x.system,alias,99);}
  });
  if(late)check(injected,'late uppercase alias reached the destination observation');
  const pointerIndex=pointers.indexOf(field as typeof pointers[number]),byteIndex=metadata.indexOf(field as typeof metadata[number]);
  equal(Reflect.get(x.system,field),pointerIndex>=0?null:201+byteIndex,`${alias} blocks its pending destination`);
  equal(x.actors[0]!.byte487,99,'uppercase alias failure cannot reach final actor marker');
 }
}
export function runBattleParticipantViewSelfTest(make:Make):void {
 baseline(make);inputLaziness(make);modes(make);shifts(make);fallback(make);helpers(make);special(make);liveReads(make);partial(make);refusalGuards(make);uppercaseAliases(make);
 console.log(`[battle-participant-view] PASS (${fixtures} genuine graph fixtures): complete bounded bef4, live source order, signed/PPC slot selection, same player-table interiors, interleaved metadata, fresh original actor487, partial writes and closure; explicit first scheduler lists return to the next mandatory boundary, no full frame/epoch/browser claim`);
}
