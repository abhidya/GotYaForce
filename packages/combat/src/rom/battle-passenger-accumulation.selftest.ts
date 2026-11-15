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
  const result=trace(x,contact===0?RNG:position%2===0?'80053cb8':'80053d14',(owner,key)=>{
   if(owner===x.sourceActor&&key==='supportContact1db')x.sourceActor.supportContact1db=visits++===position?1:0;
  });
  const count=contact===0?6:position+1;
  const expected=Array.from({length:count},(_,i)=>[`table${i}`,'self204','original208','self204','selfContact',
   ...(i===position?['link','83','slot','passenger204','original208','passenger204','passengerContact']:[])]).flat();
  equal(result.events.join(','),expected.join(','),'both unrolled halves preserve complete source load/store order');
  equal(x.massHost.sourceArrowMass204,count*200,'self store prefix retained');equal(x.passengerMass.sourceArrowMass204,210,'one passenger add retained');
  equal(getters,0,'passenger208 and second link remain unread');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);trace(x);
  equal(x.passengerMass.sourceArrowMass204,1210,'six repeated/shared passenger updates reload live204');equal(x.massHost.sourceArrowMass204,1200,'all six originals finish');closed(x);
 }
 {
  const x=createBattlePassengerAccumulationFixture(make);x.sourceActor.linkedOwner1e4=x.sourceActor;
  x.allocator.getActorBinding(x.actor).byte83=0;
  trace(x,'80053cb8');equal(x.massHost.sourceArrowMass204,400,'self alias adds original208 after completed self store');equal(x.passengerMass.sourceArrowMass204,10,'unselected passenger untouched');closed(x);
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
  const result=trace(x,expected===undefined?'overflow float32':'80053cb8',(owner,key)=>{
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
 // This lane can execute at most six increments. Byte wrapping is expressed
 // in production, but no injected stack owner or unreachable255→0 witness.
}
export function runBattlePassengerAccumulationSelfTests(make:Make):void {
 let count=0;const counted:Make=(...args)=>{count++;return make(...args);};
 basic(counted);selfAliasZero(counted);captures(counted);counters(counted);arithmetic(counted);failures(counted);ordering(counted);
 console.log(`[battle-passenger-accumulation] PASS (${count} genuine shared-graph fixtures): captured zero83 first passenger mass/count/contact-zero propagation, both halves and six live originals, initialized physical counters and explicit unsupported second-link continuation; no arbitrary chain or complete frame claim`);
}
