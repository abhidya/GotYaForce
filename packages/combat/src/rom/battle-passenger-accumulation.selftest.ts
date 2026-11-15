import {createRomActor} from './actor.js';
import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const RNG='800055fc';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-passenger-accumulation-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}

/** Reuse the genuine multi-actor status/world/allocator composition. The
 * second physical row is inactive by default, but its passenger slot is0:
 * only the active ORIGINAL physical row0 initializes that local stack byte.
 * The explicit204 belongs to its already bound Borg, never to the RomActor.
 * This is synthetic ingress, not retail constructors or source hydration. */
export function createBattlePassengerAccumulationFixture(make:Make) {
 const x=createActorThirdPassTestFixture(make),passengerId=x.physicalIdentities[1]!,passenger=x.physicalActors[1]!;
 const passengerMass=x.status.getActualBorg(passengerId);
 passengerMass.sourceArrowMass204=10;
 Object.assign(passenger,{slot:0,mass208:999,supportContact1db:0});
 x.allocator.bindActor(passengerId,{byte83:0});
 const passenger83=x.allocator.getActorBinding(passengerId);
 x.sourceActor.supportContact1db=1;Reflect.set(x.sourceActor,'linkedOwner1e4',passenger);
 Reflect.deleteProperty(x.massPreparation,'rngState');Reflect.deleteProperty(x.outerSources,'targetPreparation');
 return Object.assign(x,{passengerId,passenger,passengerMass,passenger83,outer:x.frame});
}
type Fixture=ReturnType<typeof createBattlePassengerAccumulationFixture>;
function trace(x:Fixture,expected=RNG,before:Visit=()=>{},after?:Visit) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];
 let live=false,slots=0,schedulerReads=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.actorSlots&&key==='0'&&++slots===2)live=true;
  if(live) {
   if(owner===x.actorSlots&&/^[0-5]$/.test(String(key)))events.push('table'+String(key));
   if(owner===x.massHost&&key==='sourceArrowMass204')events.push('self204');
   if(owner===x.sourceActor&&key==='mass208')events.push('original208');
   if(owner===x.sourceActor&&key==='supportContact1db')events.push('selfContact');
   if(owner===x.sourceActor&&key==='linkedOwner1e4')events.push('link');
   if(owner===x.passenger83&&key==='byte83')events.push('83');
   if(owner===x.passenger&&key==='slot')events.push('slot');
   if(owner===x.passengerMass&&key==='sourceArrowMass204')events.push('passenger204');
   if(owner===x.passenger&&key==='supportContact1db')events.push('passengerContact');
   if(owner===x.passenger&&key==='linkedOwner1e4')events.push('nextLink');
   before(owner,key);
  }
  if((owner===x.groups||owner===x.objectBytes||owner===x.nextObjectBytes)&&/^\d+$/.test(String(key))||
   owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
  const result=native(owner,key);if(live)after?.(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.outer.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 equal(schedulerReads,0,'no scheduler authority consumed');return {events,message};
}
function closed(x:Fixture,all=true):void {
 for(const actor of all?x.physicalActors:[x.sourceActor,x.passenger])check(hasIncompleteSourceActorDoubleLifecycle(actor),'all retained physical actors close');
 refuses(()=>x.outer.runFrame(),'permanently incomplete');
 for(const call of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(call,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
 refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');refuses(()=>x.projectiles.spawn(x.actor,1),'incomplete');
}
function basic(make:Make):void {
 for(const contact of [0,1,127,128,255])for(let position=0;position<6;position++) {
  const x=createBattlePassengerAccumulationFixture(make);let visits=0,getters=0;
  Reflect.set(x.passenger,'supportContact1db',contact);
  for(const key of ['mass208','linkedOwner1e4'])Object.defineProperty(x.passenger,key,{get(){getters++;throw Error('unreached passenger field');},configurable:true});
  const result=trace(x,contact===0?RNG:'linkedOwner1e4: own data',(owner,key)=>{
   if(owner===x.sourceActor&&key==='supportContact1db')x.sourceActor.supportContact1db=visits++===position?1:0;
  });
  const count=contact===0?6:position+1;
  const expected=Array.from({length:count},(_,i)=>[`table${i}`,'self204','original208','self204','selfContact',
   ...(i===position?['link','83','slot','passenger204','original208','passenger204','passengerContact',...(contact===0?[]:['nextLink'])]:[])]).flat();
  equal(result.events.join(','),expected.join(','),'both unrolled halves preserve complete source load/store order');
  equal(x.massHost.sourceArrowMass204,count*200,'self store prefix retained');equal(x.passengerMass.sourceArrowMass204,210,'one passenger add retained');
  equal(getters,0,'passenger208 and next pointer getter never invoked');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);trace(x);
  equal(x.passengerMass.sourceArrowMass204,1210,'six repeated/shared passenger updates reload live204');equal(x.massHost.sourceArrowMass204,1200,'all six originals finish');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);x.sourceActor.linkedOwner1e4=x.sourceActor;
  x.allocator.getActorBinding(x.actor).byte83=0;
  trace(x,'repeated zero83 passenger');equal(x.massHost.sourceArrowMass204,400,'self alias adds original208 after completed self store');equal(x.passengerMass.sourceArrowMass204,10,'unselected passenger untouched');closed(x);
 }
}
function selfAliasZero(make:Make):void {
 const x=createBattlePassengerAccumulationFixture(make);x.sourceActor.linkedOwner1e4=x.sourceActor;
 const binding=x.allocator.getActorBinding(x.actor);binding.byte83=0;let hit=false;
 trace(x,RNG,(owner,key)=>{if(!hit&&owner===binding&&key==='byte83'){hit=true;x.sourceActor.supportContact1db=0;}});
 check(hit,'self passenger83 captured before contact changes');equal(x.massHost.sourceArrowMass204,1400,'self-alias contact zero resumes all six live halves');closed(x);
}
function captures(make:Make):void {
 for(const field of ['83','pointer','slot','204','208','contact'] as const) {
  const x=createBattlePassengerAccumulationFixture(make);let hit=false,read208=0;
  const result=trace(x,RNG,()=>{},(owner,key)=>{
   if(owner===x.sourceActor&&key==='mass208')read208++;
   const trigger=field==='83'?owner===x.passenger83&&key==='byte83':field==='pointer'?owner===x.sourceActor&&key==='linkedOwner1e4':
    field==='slot'?owner===x.passenger&&key==='slot':field==='204'?owner===x.passengerMass&&key==='sourceArrowMass204':
    field==='208'?owner===x.sourceActor&&key==='mass208'&&read208===2:owner===x.passenger&&key==='supportContact1db';
   if(hit||!trigger)return;hit=true;x.sourceActor.supportContact1db=0;
   if(field==='83')x.passenger83.byte83=1;
   if(field==='pointer')x.sourceActor.linkedOwner1e4=x.sourceActor;
   if(field==='slot')Reflect.set(x.passenger,'slot',255);
   if(field==='204')x.passengerMass.sourceArrowMass204=999;
   if(field==='208')x.sourceActor.mass208=3;
   if(field==='contact')Reflect.set(x.passenger,'supportContact1db',1);
  });
  check(hit,'captured source scalar interruption reached');equal(result.events.filter(e=>e==='83').length,1,'no byte83 reread');
  equal(x.passengerMass.sourceArrowMass204,210,'captured load used despite later cell mutation');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);let hit=false;
  trace(x,RNG,(owner,key)=>{if(!hit&&owner===x.passengerMass&&key==='sourceArrowMass204'){hit=true;x.sourceActor.mass208=7;x.sourceActor.supportContact1db=0;}});
  equal(x.passengerMass.sourceArrowMass204,17,'fresh ORIGINAL208 loaded after passenger204, never cached self or passenger208');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);let hit=false;
  trace(x,'null actor',(owner,key)=>{if(!hit&&owner===x.passenger&&key==='supportContact1db'){hit=true;x.actorSlots[1]=null;}});
  equal(x.passengerMass.sourceArrowMass204,210,'completed passenger stores survive fresh next table load');equal(x.massHost.sourceArrowMass204,200,'later table half not prefetched');closed(x);
 }
}
function counters(make:Make):void {
 for(const slot of [1,5,6,127,128,255]) {
  const x=createBattlePassengerAccumulationFixture(make);Reflect.set(x.passenger,'slot',slot);
  const result=trace(x,'local passenger count');
  equal(result.events.slice(-3).join(','),'slot,passenger204,original208','range/uninitialized refusal occurs after BOTH masses');
  equal(x.passengerMass.sourceArrowMass204,10,'counter admission fails before mass store');equal(x.massHost.sourceArrowMass204,200,'self prefix retained');closed(x);
 }
 for(const physical of [1,2,3,4,5]) {
  const x=createBattlePassengerAccumulationFixture(make),id=x.physicalIdentities[physical]!,actor=x.physicalActors[physical]!;
  Object.assign(actor,{active0:1,mass208:77});x.stageBounds.bindActor(id,{lifecycle18:0});
  const host=x.status.getActualBorg(id);host.sourceArrowMass204=77;
  // Passenger identity/team do not choose the local byte. Its slot selects
  // the independently initialized ACTIVE PHYSICAL row, with no parameter4ac.
  Reflect.set(x.passenger,'slot',physical);Reflect.set(x.passenger,'team',255);
  trace(x);equal(x.passengerMass.sourceArrowMass204,physical===1?1200:1210,'active physical row initializes selected counter');closed(x);
 }
 for(const bad of [-1,.5,256,NaN,Infinity,undefined]) {
  const x=createBattlePassengerAccumulationFixture(make);Reflect.set(x.passenger,'slot',bad);
  const result=trace(x,'raw unsigned');check(!result.events.includes('passenger204'),'malformed raw slot refuses before mass load');closed(x);
 }
}
function arithmetic(make:Make):void {
 const maximum=(2-2**-23)*2**127;
 for(const [a,b,expected] of [[2**24,1,2**24],[2**24+2,1,2**24+4],[-0,-0,-0],
  [2**-149,2**-149,2**-148],[1,-1,0],[maximum,maximum,undefined]] as const) {
  const x=createBattlePassengerAccumulationFixture(make);x.passengerMass.sourceArrowMass204=a;
  Reflect.set(x.passenger,'supportContact1db',1);let hit=false;
  const result=trace(x,expected===undefined?'overflow float32':'explicit linkedOwner1e4 required',(owner,key)=>{
   if(!hit&&owner===x.passenger83&&key==='byte83'){hit=true;x.sourceActor.mass208=b;}
  });
  check(hit,'original208 mutation after self store reached');
  equal(x.passengerMass.sourceArrowMass204,expected===undefined?a:expected,'one exact finite nearest-even f32 sum');
  equal(result.events.filter(e=>e==='passenger204').length,expected===undefined?1:2,'overflow precedes passenger destination store');
  equal(x.massHost.sourceArrowMass204,200,'earlier self store remains');closed(x);
 }
 for(const field of ['sourceArrowMass204','mass208','supportContact1db'] as const)for(const bad of [-1.5,256,NaN,Infinity,undefined]) {
  if(field!=='supportContact1db'&&(bad===-1.5||bad===256))continue;
  const x=createBattlePassengerAccumulationFixture(make);let hit=false;
  trace(x,field==='supportContact1db'?'raw unsigned':'float32',(owner,key)=>{
   if(hit||owner!==x.passenger83||key!=='byte83')return;hit=true;
   Reflect.set(field==='sourceArrowMass204'?x.passengerMass:field==='mass208'?x.sourceActor:x.passenger,field,bad);
  });
  check(hit,'malformed field reached');
  if(field==='supportContact1db')equal(x.passengerMass.sourceArrowMass204,210,'malformed contact follows both stores');
  else if(field==='mass208')equal(x.passengerMass.sourceArrowMass204,10,'bad original208 precedes passenger store');
  closed(x);
 }
}
function failures(make:Make):void {
 for(const field of ['slot','sourceArrowMass204','supportContact1db'] as const)for(const fault of ['missing','accessor','inherited'] as const) {
  const x=createBattlePassengerAccumulationFixture(make),owner=field==='sourceArrowMass204'?x.passengerMass:x.passenger;let getters=0;
  Reflect.deleteProperty(owner,field);
  if(fault==='accessor')Object.defineProperty(owner,field,{get(){getters++;throw Error('forbidden getter');},configurable:true});
  if(fault==='inherited')Object.setPrototypeOf(owner,{[field]:0});
  trace(x,'own data');equal(getters,0,'missing/inherited/accessor source never synthesized or invoked');
  if(field==='supportContact1db')equal(x.passengerMass.sourceArrowMass204,210,'mass store retained before missing contact');closed(x);
 }
 for(const field of ['slot3e4','byte3E4','996','sourceArrowMass204','float204','byte206','mass208','field208','byte20B','supportContact1db','byte1DB','475'])
  for(const late of [false,true]) {
   const x=createBattlePassengerAccumulationFixture(make);let hit=false,getters=0;
   const owner=['mass208','supportContact1db'].includes(field)?x.passengerMass:x.passenger;
   const add=()=>Object.defineProperty(owner,field,{get(){getters++;throw Error('competing alias getter');},configurable:true});
   if(!late)add();
   trace(x,'competing',(record,key)=>{if(late&&!hit&&record===x.passenger83&&key==='byte83'){hit=true;add();}});
   if(late)check(hit,'late alias insertion reached');equal(getters,0,'alias getter not invoked');closed(x,late);
  }
 for(const role of ['source','global','mass','status','mapping','attribute','world'] as const) {
  const x=createBattlePassengerAccumulationFixture(make);
  const owner={source:x.outerSources,global:x.matchGlobals,mass:x.massPreparation,status:x.status.getActorBinding(x.passengerId),
   mapping:x.status.getMappingActor(x.passengerId),attribute:x.attributes.getActorBinding(x.passengerId),world:x.world.getActorBinding(x.passengerId)}[role];
  // Sealed genuine bindings refuse an added cell themselves. A wrong owner
  // is never used as the passenger Borg merely because it advertises204.
  if(Object.isExtensible(owner)) {
   Reflect.set(owner,'sourceArrowMass204',901);trace(x,'competing');equal(x.passengerMass.sourceArrowMass204,10,'wrong Borg-like owner is not consumed');closed(x);
  } else check(!Reflect.set(owner,'sourceArrowMass204',901),'sealed canonical role cannot acquire counterfeit204');
 }
 for(const fault of ['deleted','accessor','readonly','late-shadow','closed-borg','closed-actor','reentry','mass-owner','count-owner'] as const) {
  const x=createBattlePassengerAccumulationFixture(make);let visits=0,hit=false,setters=0;
  trace(x,fault==='readonly'?'non-writable':fault==='late-shadow'?'competing':fault.startsWith('closed')?'incomplete':
   fault==='reentry'?'reentry':fault.endsWith('owner')?'owner changed':'own data',()=>{},(owner,key)=>{
    if(owner!==x.passengerMass||key!=='sourceArrowMass204'||++visits!==2)return;
    hit=true;
    if(fault==='deleted')Reflect.deleteProperty(owner,key);
    if(fault==='accessor')Object.defineProperty(owner,key,{get(){return 10;},set(){setters++;},configurable:true});
    if(fault==='readonly')Object.defineProperty(owner,key,{writable:false});
    if(fault==='late-shadow')Reflect.set(x.passenger,'float204',901);
    if(fault==='closed-borg')markIncompleteSourceActorDoubleLifecycle(x.passengerMass);
    if(fault==='closed-actor')markIncompleteSourceActorDoubleLifecycle(x.passenger);
    if(fault==='reentry')refuses(()=>x.outer.runFrame(),'same-runtime reentry');
    if(fault==='mass-owner')x.outerSources.massPreparation={...x.massPreparation};
    if(fault==='count-owner')x.massPreparation.teamCounts={...x.massPreparation.teamCounts};
   });
  check(hit,'final passenger destination preflight interruption reached');equal(setters,0,'late destination never calls setter');
  if(fault==='deleted')check(!Object.hasOwn(x.passengerMass,'sourceArrowMass204'),'deleted mass not recreated');
  else equal(x.passengerMass.sourceArrowMass204,10,'source mass store did not execute after destination refusal');
  equal(x.massHost.sourceArrowMass204,200,'all earlier self effects retained');closed(x);
 }
 // Final observable alias descriptor can mutate a previously inspected owner.
 for(const trigger of ['slot3e4','byte206','byte20B','byte1DB']) {
  const x=createBattlePassengerAccumulationFixture(make);let hit=false;
  trace(x,'competing',()=>{},(owner,key)=>{if(!hit&&owner===x.passenger&&key===trigger){hit=true;Reflect.set(x.outerSources,'sourceArrowMass204',901);}});
  check(hit,'late observable metadata interruption reached');closed(x);
 }
}
function ordering(make:Make):void {
 const x=createBattlePassengerAccumulationFixture(make);let suffix=false;
 Object.assign(x.passenger,{active0:1,mass208:77,slot:1,field664:77});
 x.stageBounds.bindActor(x.passengerId,{lifecycle18:0});
 x.massPreparation.rngState={byte804360c6:0xc3,byte804360c7:1};
 trace(x,'8006ae60',(owner,key)=>{
  if(!suffix&&owner===x.massPreparation.rngState&&key==='byte804360c7') {
   suffix=true;x.actorSlots[1]=x.passengerId;
  }
 });
 check(suffix,'both real RNG calls and existing ordering reached');
 equal(x.passengerMass.sourceArrowMass204,1200,'six source contributions accumulated after active row clear');
 equal(x.massPreparation.orderCount.count80436260,6,'six entries in genuine suffix');
 equal(x.massPreparation.orderPointers[0],x.passengerId,'counter6 inserts ahead of earlier counter0 actors');
 for(let i=1;i<6;i++)equal(x.massPreparation.orderPointers[i],x.actor,'stable existing entries shifted by actual suffix');
 equal(x.massPreparation.rngState.byte804360c6,217,'real RNG prefix retained');closed(x);
}
export function runBattlePassengerAccumulationSelfTests(make:Make):void {
 let count=0;const counted:Make=(...args)=>{count++;return make(...args);};
 basic(counted);selfAliasZero(counted);captures(counted);counters(counted);arithmetic(counted);failures(counted);ordering(counted);
 console.log(`[battle-passenger-accumulation] PASS (${count} genuine shared-graph fixtures): captured zero83 first passenger mass/count/contact-zero propagation, both halves and six live originals, initialized physical counters and lazy next-link admission; no complete frame claim`);
}

/** Genuine additional world/status/allocator actors, outside the physical six.
 * These bindings are synthetic source ingress, never a substituted runtime. */
function extraPassenger(x:Fixture,slotIndex=0) {
 const parts=Array.from({length:2},()=>Array.from({length:4},()=>x.mapping.createPart(
  {frame0c:0,duration24:0,segment2d:0,complete2e:0,mode2f:0,mirror30:0},
  {descriptor00:null,scaleIndex32:255,jointBank33:0,poseBuffer35:0})));
 const poses=Array.from({length:2},()=>Array.from({length:2},()=>x.feedback.createPose({translation:{x:0,y:0,z:0},quaternion:{x:0,y:0,z:0,w:1}})));
 const id=x.mapping.createActor({descriptor4b0:null,jointCount1d90:0,boundary1d91:0,boundary1d92:0,boundary1d93:0,jointBank1db4:null,jointBank1db8:null,timestep1dc8:0},{parts,poses});
 const actor=createRomActor();actor.active0=0;
 const fresh=()=>x.matrices.createMatrix(Array(12).fill(0));
 x.world.bindActor(id,actor,{mode4a0:2,mode4a1:0,flags48a:0,mask1d70:0,roll74:0,yawOffset6b8:0,scale58:{x:1,y:1,z:1},offset1dbc:{x:0,y:0,z:0},adjusted1d54:{x:0,y:0,z:0},preRotation1d64:{x:0,y:0,z:0}},
 {matrices8d4:[fresh(),fresh()],copy114:fresh(),copy1aa4:fresh(),scratch:fresh(),topology1994:[[255,255,0,0],[255,255,0,0]],corrections18d4:[{x:0,y:0,z:0},{y:0,z:0}],scales15d4:[{x:1,y:1,z:1},{x:1,y:1,z:1}]});
 x.dispatch.bindActor(id,{family1d88:null,shared1d8c:null,marker578:0,marker1db3:0});
 x.control.bindActor(id,{activeMask579:0,blockedMask1d9a:0,marker71d:0},Array.from({length:4},()=>({current00:null,next04:null,wait14:0,finished1a:0,event1e:0,group18:0,action19:0,status1d:0,state1b:0,auxiliary1c:0})));
 x.control.bindStartActor(id,{familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:0});
 x.ready.bindActor(id,{familyBank1d78:null,sharedBank1d7c:null,movement6d8:0});
 x.movement.bindActor(id,actor,{byte661:0,field66c:0,field670:0});x.attributes.bindActor(id,{});
 Reflect.deleteProperty(actor,'invulnTimer');
 const ammo=()=>({cell:{cur:0,max:0,refillType:0,refillParam:0,timer:0},mirror776:0});
 x.status.bindActor(id,{hp:1,hitDrainFrames:0,balanceGauge:0,balanceGaugeMax:0,balanceRefillDelay:0,downResetDelay:0,comboWindow:0,comboAccum:0,comboRank:0,invincTimer:0,sourceAmmoRefillPauseMask:0},{},[ammo(),ammo(),ammo()]);
 for(const key of ['fbPhaseSlots','shotByte1db3','animState'])Reflect.deleteProperty(actor,key);
 x.allocator.registerExternal(id,actor);x.allocator.bindActor(id,{byte83:0});
 Object.assign(actor,{slot:slotIndex,mass208:999,supportContact1db:0});
 const borg=x.status.getActualBorg(id);borg.sourceArrowMass204=10;
 return {id,actor,borg,allocation:x.allocator.getActorBinding(id)};
}
type Passenger=ReturnType<typeof extraPassenger>;
function chain(x:Fixture,length:number,slotIndex=0):Passenger[] {
 const nodes=Array.from({length},()=>extraPassenger(x,slotIndex));
 for(let i=0;i<nodes.length-1;i++)Object.assign(nodes[i]!.actor,{supportContact1db:1,linkedOwner1e4:nodes[i+1]!.actor});
 x.sourceActor.linkedOwner1e4=nodes[0]!.actor;return nodes;
}
function reachedClosed(nodes:readonly Passenger[]):void {
 for(const node of nodes)check(hasIncompleteSourceActorDoubleLifecycle(node.actor),'each genuinely reached external actor closes');
}
function finiteChains(make:Make):void {
 for(let position=0;position<6;position++) {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,5);let originals=0,getters=0;
  const events:string[]=[];
  for(const n of nodes)Object.defineProperty(n.actor,'mass208',{get(){getters++;throw Error('passenger is not contribution original');},configurable:true});
  Object.defineProperty(nodes[4]!.actor,'linkedOwner1e4',{get(){getters++;throw Error('past contact zero');},configurable:true});
  trace(x,RNG,(owner,key)=>{
   if(owner===x.sourceActor&&key==='supportContact1db')x.sourceActor.supportContact1db=originals++===position?1:0;
   if(owner===x.sourceActor&&key==='mass208')events.push('original208');
   for(const [i,n]of nodes.entries()) {
    if(owner===n.actor&&key==='slot')events.push(`${i}:slot`);
    if(owner===n.borg&&key==='sourceArrowMass204')events.push(`${i}:204`);
    if(owner===n.actor&&key==='supportContact1db')events.push(`${i}:contact`);
    if(owner===n.actor&&key==='linkedOwner1e4')events.push(`${i}:link`);
    if(owner===n.allocation&&key==='byte83')events.push(`${i}:83`);
   }
  });
  const expected=Array(position+1).fill('original208').concat(nodes.flatMap((_,i)=>[
   `${i}:83`,`${i}:slot`,`${i}:204`,'original208',`${i}:204`,`${i}:contact`,...(i===4?[]:[`${i}:link`])]),Array(5-position).fill('original208')).flat();
  equal(events.join(','),expected.join(','),'every hop and both halves preserve source load/store order');
  for(const n of nodes)equal(n.borg.sourceArrowMass204,210,'one selected original reaches all five passengers');
  equal(getters,0,'unreached contribution and terminal pointer accessors remain lazy');reachedClosed(nodes);closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,9);
  trace(x);for(const n of nodes)equal(n.borg.sourceArrowMass204,1210,'long shared suffix accumulated again for each repeated live original');
  reachedClosed(nodes);closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,3);let hit=0;
  trace(x,RNG,(owner,key)=>{
   for(const [i,n]of nodes.entries())if(owner===n.borg&&key==='sourceArrowMass204'&&hit===i){x.sourceActor.mass208=i+3;x.sourceActor.supportContact1db=0;hit++;}
  });
  equal(hit,3,'every reached passenger load can change original208 before its fresh load');
  nodes.forEach((n,i)=>equal(n.borg.sourceArrowMass204,13+i,'each hop loads fixed ORIGINAL208 afresh'));reachedClosed(nodes);closed(x);
 }
 for(const tail of ['self','two','lasso'] as const) {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,tail==='self'?1:tail==='two'?2:4);
  const repeat=tail==='lasso'?1:0,last=nodes[nodes.length-1]!;
  Object.assign(last.actor,{supportContact1db:1,linkedOwner1e4:nodes[repeat]!.actor});
  let repeatedSlots=0;
  trace(x,'repeated zero83 passenger',(owner,key)=>{if(owner===nodes[repeat]!.actor&&key==='slot')repeatedSlots++;});
  equal(repeatedSlots,1,'repeat refusal precedes repeated slot/mass/count reads');
  for(const n of nodes)equal(n.borg.sourceArrowMass204,210,'cycle retains exactly its completed finite prefix');reachedClosed(nodes);closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,2);let changed=false;
  Object.assign(nodes[1]!.actor,{supportContact1db:1,linkedOwner1e4:nodes[0]!.actor});
  trace(x,RNG,(owner,key)=>{if(!changed&&owner===nodes[1]!.actor&&key==='supportContact1db') {
   changed=true;nodes[0]!.allocation.byte83=128;x.sourceActor.supportContact1db=0;
  }});
  check(changed,'repeated target83 changes before its next fresh capture');
  for(const n of nodes)equal(n.borg.sourceArrowMass204,210,'repeated nonzero83 exits before repeat admission');reachedClosed(nodes);closed(x);
 }
}
function laterCapturesAndOriginalGuards(make:Make):void {
 {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,3);
  x.actorSlots[1]=x.passengerId;
  Object.assign(x.passenger,{mass208:7,supportContact1db:1,linkedOwner1e4:nodes[1]!.actor});
  trace(x);
  equal(nodes[0]!.borg.sourceArrowMass204,1010,'five repeated A originals reach first node');
  for(const n of nodes.slice(1))equal(n.borg.sourceArrowMass204,1017,'distinct original B contributes its own208 to shared suffix');
  equal(x.passengerMass.sourceArrowMass204,17,'inactive physical B preserves explicit208 for its own self store');reachedClosed(nodes);closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,3);let hit=false;
  trace(x,RNG,()=>{},(owner,key)=>{
   if(!hit&&owner===nodes[1]!.allocation&&key==='byte83') {
    hit=true;nodes[1]!.allocation.byte83=255;x.sourceActor.supportContact1db=0;
   }
  });
  check(hit,'advanced zero83 capture interrupted');
  for(const n of nodes)equal(n.borg.sourceArrowMass204,210,'captured advanced zero83 remains authoritative after live83 changes');reachedClosed(nodes);closed(x);
 }
 for(const point of ['link','83'] as const)for(const role of ['actor','borg'] as const) {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,2);let hit=false;
  nodes[1]!.allocation.byte83=1;
  trace(x,'incomplete',()=>{},(owner,key)=>{
   if(!hit&&(point==='link'?owner===nodes[0]!.actor&&key==='linkedOwner1e4':owner===nodes[1]!.allocation&&key==='byte83')) {
    hit=true;markIncompleteSourceActorDoubleLifecycle(role==='actor'?x.sourceActor:x.massHost);
   }
  });
  check(hit,'fixed original lifecycle is interrupted during advanced lazy exit');
  equal(nodes[0]!.borg.sourceArrowMass204,210,'first completed store remains after lazy-exit original guard');
  equal(nodes[1]!.borg.sourceArrowMass204,10,'nonzero83 target mass stays unread and untouched');reachedClosed(nodes.slice(0,1));closed(x);
 }
}
function registryBoundary(make:Make):void {
 for(const kind of ['zero','nonzero','unrelated'] as const) {
  const x=createBattlePassengerAccumulationFixture(make);let added:Passenger|undefined,hit=false,reads=0;
  trace(x,kind==='zero'?'outside captured registry':RNG,(owner,key)=>{
   if(!hit&&owner===x.sourceActor&&key==='linkedOwner1e4') {
    hit=true;added=extraPassenger(x);x.sourceActor.supportContact1db=0;
    if(kind!=='unrelated')x.sourceActor.linkedOwner1e4=added.actor;
    if(kind==='nonzero')added.allocation.byte83=255;
    for(const field of ['slot','mass208','supportContact1db','linkedOwner1e4'])Object.defineProperty(added.actor,field,{get(){reads++;throw Error('outside domain scalar');},configurable:true});
    Object.defineProperty(added.borg,'sourceArrowMass204',{get(){reads++;throw Error('outside domain Borg');},configurable:true});
   }
  });
  check(hit&&added!==undefined,'late genuine registry addition occurs after snapshot');equal(reads,0,'late zero/nonzero target has no slot or mass or contact reads');
  if(kind!=='unrelated')reachedClosed([added!]);
  equal(x.passengerMass.sourceArrowMass204,kind==='unrelated'?210:10,'unrelated addition does not eagerly refuse existing passenger');closed(x);
 }
}
function advancedGuards(make:Make):void {
 for(const fault of ['original-actor','original-borg','original-alias','mass-owner','counter-owner','target-readonly','target-alias'] as const) {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,3);let hit=false;
  trace(x,fault.startsWith('original-')&&fault!=='original-alias'?'incomplete':fault.endsWith('alias')?'competing':fault.endsWith('owner')?'owner changed':'non-writable',(owner,key)=>{
   if(hit||owner!==nodes[1]!.actor||key!=='slot')return;hit=true;
   if(fault==='original-actor')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
   if(fault==='original-borg')markIncompleteSourceActorDoubleLifecycle(x.massHost);
   if(fault==='original-alias')Reflect.set(x.sourceActor,'field208',99);
   if(fault==='mass-owner')x.outerSources.massPreparation={...x.massPreparation};
   if(fault==='counter-owner')x.massPreparation.teamCounts={...x.massPreparation.teamCounts};
   if(fault==='target-readonly')Object.defineProperty(nodes[1]!.borg,'sourceArrowMass204',{writable:false});
   if(fault==='target-alias')Reflect.set(nodes[1]!.actor,'float204',99);
  });
  check(hit,'fault is injected after current actor advanced away from original');
  equal(nodes[0]!.borg.sourceArrowMass204,210,'completed prior hop survives guard refusal');
  equal(nodes[1]!.borg.sourceArrowMass204,10,'failing hop destination is untouched');
  equal(nodes[2]!.borg.sourceArrowMass204,10,'future chain is not prevalidated');
  reachedClosed(nodes.slice(0,2));closed(x);
 }
}
function realCounterWrap(make:Make):void {
 for(const [length,suffix,total]of [[43,40,255],[43,41,256],[43,42,257],[43,43,258],[21,22,127],[21,23,128]] as const) {
  const x=createBattlePassengerAccumulationFixture(make),nodes=chain(x,Math.max(length,suffix),1);
  // Both originals share a suffix, but A need not start at the first node.
  x.sourceActor.linkedOwner1e4=nodes[nodes.length-length]!.actor;
  Object.assign(x.passenger,{active0:1,mass208:77,slot:1,field664:77,supportContact1db:1,linkedOwner1e4:nodes[nodes.length-suffix]!.actor});
  x.stageBounds.bindActor(x.passengerId,{lifecycle18:0});
  x.actorSlots[1]=x.passengerId;
  x.massPreparation.rngState={byte804360c6:0xc3,byte804360c7:1};
  trace(x,'8006ae60');
  equal(x.massPreparation.orderCount.count80436260,6,'genuine ordering consumes all six original visits');
  const signed=(total&255)<<24>>24,bIndex=signed>0?0:5;
  equal(x.massPreparation.orderPointers[bIndex],x.passengerId,`real count ${total} wraps to ${total&255} and compares signed ${signed}`);
  for(let i=0;i<6;i++)if(i!==bIndex)equal(x.massPreparation.orderPointers[i],x.actor,'signed count insertion preserves stable remaining originals');
  equal(x.massHost.sourceArrowMass204,1000,'five A originals contribute normally');
  equal(nodes[nodes.length-1]!.borg.sourceArrowMass204,1010,'B contributes zero but still increments every suffix counter');
  reachedClosed(nodes);closed(x);
 }
}
export function runBattlePassengerFiniteTraversalSelfTests(make:Make):void {
 let count=0;const counted:Make=(...args)=>{count++;return make(...args);};
 finiteChains(counted);laterCapturesAndOriginalGuards(counted);registryBoundary(counted);advancedGuards(counted);realCounterWrap(counted);
 console.log(`[battle-passenger-finite-traversal] PASS (${count} genuine shared-graph fixtures): finite external chains, six live originals and shared suffixes, fresh original208, source-ordered lazy exits, cycle/registry host bounds, advanced original guards, genuine wrapping counters and signed stable ordering; no complete frame or retail hydration claim`);
}
