import {createRomActor} from './actor.js';
import {createSourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {createBattleMassPreparationTestFixture} from './attached-setup-animation.selftest.js';

type Make=typeof createBattleMassPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const RNG='800055fc',ZERO0='80053cc8',ZERO1='80053d24';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-passenger-early-stop-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}

/** Existing genuine target already belongs to the SAME world/mapping graph.
 * The explicit allocation binding owns83; the actual object owns1e4. No source
 * constructor, callback substitution, target mass hydration or copied byte83. */
export function createBattlePassengerEarlyStopFixture(make:Make,value:number|null=1,bind=true) {
 const x=make();
 if(bind)x.allocator.bindActor(x.target,value===null?{}:{byte83:value});
 x.sourceActor.supportContact1db=1;x.sourceActor.linkedOwner1e4=x.targetActor;
 const passenger83=bind?x.allocator.getActorBinding(x.target):undefined;
 const scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources);
 const sources={scheduler,systemGlobals:x.systemGlobals,massPreparation:x.massPreparation};
 const outer=createSourceBattleOuterFrameRuntime(sources);
 return Object.assign(x,{passenger83,scheduler,sources,outer});
}
type Fixture=ReturnType<typeof createBattlePassengerEarlyStopFixture>;
function trace(x:Fixture,expected=RNG,before:Visit=()=>{},after?:Visit) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];
 let live=false,slots=0,linkReads=0,byteReads=0,schedulerReads=0;
 const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.actorSlots&&key==='0'&&++slots===2)live=true;
  if(live){
   if(owner===x.actorSlots&&/^[0-5]$/.test(String(key)))events.push('slot'+String(key));
   if(owner===x.massHost&&key==='sourceArrowMass204')events.push('204');
   if(owner===x.sourceActor&&key==='mass208')events.push('208');
   if(owner===x.sourceActor&&key==='supportContact1db')events.push('contact');
   if(owner===x.sourceActor&&key==='linkedOwner1e4'){events.push('1e4');linkReads++;}
   if(owner===x.passenger83&&key==='byte83'){events.push('83');byteReads++;}
  }
  if((owner===x.objectBytes||owner===x.nextObjectBytes||owner===x.groups)&&/^\d+$/.test(String(key))||
   owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
  before(owner,key);const result=native(owner,key);after?.(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.outer.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 equal(schedulerReads,0,'no scheduler groups, object bytes or masks');
 equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no actor epoch manufactured');
 return {events,linkReads,byteReads,message};
}
function prefix(x:Fixture,total=1200):void {
 equal(x.massHost.sourceArrowMass204,total,'self-mass writes survive bounded refusal');
 equal(x.sourceActor.mass208,200,'physical scaled208 retained');equal(x.massPreparation.teamCounts[0],1,'physical team append retained');
 equal(x.massPreparation.teamPointers[0],x.actor,'same physical actor append');
}
function closed(x:Fixture,target=true):void {
 check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'caller permanently closes');
 if(target)check(hasIncompleteSourceActorDoubleLifecycle(x.targetActor),'resolved passenger permanently closes');
 refuses(()=>x.outer.runFrame(),'permanently incomplete');
 for(const call of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(call,'exclusively owned');
 refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
 refuses(()=>x.projectiles.spawn(x.actor,1),'incomplete');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function branches(make:Make):void {
 check(!Object.hasOwn(createRomActor(),'linkedOwner1e4'),'new pointer has no constructor default');
 for(const value of [0,1,2,127,128,254,255])for(const contact of [1,128,255]) {
  const x=createBattlePassengerEarlyStopFixture(make,value);x.sourceActor.supportContact1db=contact;
  let getters=0;
  for(const key of ['slot','mass208','supportContact1db','linkedOwner1e4'])Object.defineProperty(x.targetActor,key,{get(){getters++;throw Error('unreached passenger continuation');},configurable:true});
  const result=trace(x,value===0?ZERO0:RNG);
  equal(result.events.join(','),Array.from({length:value===0?1:6},(_,i)=>['slot'+i,'204','208','204','contact','1e4','83']).flat().join(','),'source pointer-table/self-mass/contact/1e4/83 order');
  equal(result.linkReads,value===0?1:6,'one actual pointer load per reached traversal');equal(result.byteReads,result.linkReads,'one canonical83 load per captured passenger');
  equal(getters,0,'passenger3e4/mass/contact/next-link are never consumed');equal(x.passenger83!.byte83,value,'borrowed byte is read-only');
  equal(x.allocator.getActualActor(x.target),x.world.getActualActor(x.target),'same actual allocator/world actor');check(Object.isSealed(x.passenger83),'same sealed binding');
  prefix(x,value===0?200:1200);closed(x);
 }
 for(let stop=0;stop<6;stop++) {
  const x=createBattlePassengerEarlyStopFixture(make,0);let contacts=0;
  trace(x,stop%2===0?ZERO0:ZERO1,(owner,key)=>{if(owner===x.sourceActor&&key==='supportContact1db')x.sourceActor.supportContact1db=contacts++===stop?1:0;});
  equal(contacts,stop+1,'zero83 stops at exact reached half');prefix(x,200*(stop+1));closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);x.sourceActor.supportContact1db=0;let getters=0;
  Object.defineProperty(x.sourceActor,'linkedOwner1e4',{get(){getters++;throw Error('unreached pointer');}});
  const result=trace(x);equal(result.linkReads,0,'zero contact never inspects pointer');equal(result.byteReads,0,'zero contact never reads passenger');equal(getters,0,'missing/poisoned pointer remains lazy');prefix(x);closed(x,false);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);x.sourceActor.linkedOwner1e4=x.sourceActor;x.allocator.getActorBinding(x.actor).byte83=255;
  trace(x);prefix(x);closed(x,false);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);Object.defineProperty(x.passenger83!,'byte83',{writable:false});trace(x);prefix(x);closed(x);
 }
}
function capture(make:Make):void {
 for(const old of [0,1]) {
  const x=createBattlePassengerEarlyStopFixture(make,old);let once=false;
  const result=trace(x,old===0?ZERO0:RNG,()=>{},(owner,key)=>{
   if(owner===x.passenger83&&key==='byte83'&&!once){once=true;x.passenger83!.byte83=old===0?1:0;x.sourceActor.supportContact1db=0;}
  });
  check(once,'captured byte interruption reached');equal(result.byteReads,1,'captured byte not reread');prefix(x,old===0?200:1200);closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);let once=false;
  const result=trace(x,RNG,()=>{},(owner,key)=>{if(owner===x.sourceActor&&key==='linkedOwner1e4'&&!once){once=true;x.sourceActor.linkedOwner1e4=x.sourceActor;x.sourceActor.supportContact1db=0;}});
  equal(result.byteReads,1,'captured pointer survives live1e4 change');prefix(x);closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);let reads=0;
  trace(x,ZERO1,(owner,key)=>{if(owner===x.passenger83&&key==='byte83'&&++reads===2)x.passenger83!.byte83=0;});
  equal(reads,2,'next actual table half freshly reloads same byte');prefix(x,400);closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);let once=false;
  trace(x,ZERO1,()=>{},(owner,key)=>{if(owner===x.passenger83&&key==='byte83'&&!once){once=true;x.sourceActor.linkedOwner1e4=x.sourceActor;}});
  check(once,'first passenger byte captured before pointer retarget');prefix(x,400);closed(x);
 }
 for(const replacement of ['null','inactive'] as const) {
  const x=createBattlePassengerEarlyStopFixture(make);let once=false;
  trace(x,replacement==='null'?'null actor':'unknown',(owner,key)=>{if(owner===x.passenger83&&key==='byte83'&&!once){once=true;x.actorSlots[1]=replacement==='null'?null:x.physicalIdentities[5]!;}});
  check(once,'passenger predicate reached');prefix(x,200);closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);let once=false;
  trace(x,'non-writable',(owner,key)=>{if(owner===x.passenger83&&key==='byte83'&&!once){once=true;Object.defineProperty(x.massHost,'sourceArrowMass204',{writable:false});}});
  prefix(x,200);closed(x);
 }
}
function failures(make:Make):void {
 for(const kind of ['missing','undefined','null','number','symbol','plain','foreign','interior','external','unbound','missing83','negative','fractional','too-large','nan','infinity'] as const) {
  const x=createBattlePassengerEarlyStopFixture(make,kind==='missing83'?null:1,kind!=='unbound');let expected='';
  if(kind==='missing'){delete x.sourceActor.linkedOwner1e4;expected='unsupported actual pointer1e4';}
  if(['undefined','null','number','symbol','plain'].includes(kind)){
   Reflect.set(x.sourceActor,'linkedOwner1e4',({undefined:undefined,null:null,number:1,symbol:x.target,plain:{}} as Record<string,unknown>)[kind]);expected=kind==='plain'?'not been registered':'record required';
  }
  if(kind==='foreign'){x.sourceActor.linkedOwner1e4=make().targetActor;expected='not been registered';}
  if(kind==='interior'){Reflect.set(x.sourceActor,'linkedOwner1e4',x.allocator.getPointerTarget(x.allocator.getInteriorPointer(x.actor,4)));expected='base identity';}
  if(kind==='external'){const external={};x.allocator.registerExternal(Symbol('not an actor'),external);Reflect.set(x.sourceActor,'linkedOwner1e4',external);expected='unknown/non-owned';}
  if(kind==='unbound') {x.allocator.registerExternal(x.target,x.targetActor);expected='unknown/non-owned';}
  if(kind==='missing83')expected='byte83: terminal own data';
  const bad={negative:-1,fractional:.5,'too-large':256,nan:NaN,infinity:Infinity};
  if(kind in bad){Reflect.set(x.passenger83!,'byte83',bad[kind as keyof typeof bad]);expected='raw unsigned';}
  trace(x,expected);prefix(x,200);closed(x,!['missing','undefined','null','number','symbol','plain','foreign','interior','external'].includes(kind));
 }
 for(const key of ['pointer1e4','pointer1E4','field1e4','byte1e4','byte1e5','byte1E6','byte1e7','484','485','486','487'])for(const late of [false,true]) {
  const x=createBattlePassengerEarlyStopFixture(make);let hit=false,getters=0;
  const add=()=>Object.defineProperty(x.sourceActor,key,{get(){getters++;throw Error('alias accessor');},configurable:true});if(!late)add();
  trace(x,'competing',(owner,field)=>{if(late&&owner===x.passenger83&&field==='byte83'){hit=true;add();}});
  if(late)check(hit,'late pointer alias reached');equal(getters,0,'alias accessor not invoked');prefix(x,200);closed(x,late);
 }
 for(const key of ['byte83','eligibility83','groupEligibility83','field83','131'])for(const late of [false,true]) {
  const x=createBattlePassengerEarlyStopFixture(make);let hit=false,getters=0;
  const add=()=>Object.defineProperty(x.targetActor,key,{get(){getters++;throw Error('alias accessor');},configurable:true});if(!late)add();
  trace(x,'competing',(owner,field)=>{if(late&&owner===x.passenger83&&field==='byte83'){hit=true;add();}});
  if(late)check(hit,'late byte alias reached');equal(getters,0,'alias accessor not invoked');prefix(x,200);closed(x);
 }
 for(const field of ['linkedOwner1e4','pointer1e4','field1e4','byte1e4'])for(const role of ['sources','globals','mass','borg'] as const) {
  const x=createBattlePassengerEarlyStopFixture(make);
  const owner={sources:x.sources,globals:x.matchGlobals,mass:x.massPreparation,borg:x.massHost}[role];
  Reflect.set(owner,field,x.targetActor);trace(x,'competing');prefix(x,200);closed(x,false);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);let getters=0;
  Object.defineProperty(x.sourceActor,'linkedOwner1e4',{get(){getters++;throw Error('pointer accessor');}});
  trace(x,'own data');equal(getters,0,'reached pointer accessor refused without invocation');prefix(x,200);closed(x,false);
 }
 for(const fault of ['accessor','deleted','readonly'] as const) {
  const x=createBattlePassengerEarlyStopFixture(make);let visits=0,hit=false,setters=0;
  trace(x,fault==='readonly'?'non-writable':'own data',()=>{},(owner,key)=>{
   if(owner!==x.massHost||key!=='sourceArrowMass204'||++visits!==5)return;
   hit=true;
   if(fault==='accessor')Object.defineProperty(owner,key,{get(){return 200;},set(){setters++;},configurable:true});
   if(fault==='deleted')Reflect.deleteProperty(owner,key);
   if(fault==='readonly')Object.defineProperty(owner,key,{writable:false});
  });
  check(hit,'second self-mass final preflight reached');equal(setters,0,'late accessor setter never invoked');
  if(fault==='deleted')check(!Object.hasOwn(x.massHost,'sourceArrowMass204'),'deleted destination not recreated');
  else equal(x.massHost.sourceArrowMass204,200,'first self mass write survives later destination refusal');
  equal(x.sourceActor.mass208,200,'earlier physical mass store survives');closed(x);
 }
 for(const fault of ['caller-closed','target-closed','pointer-delete','pointer-accessor','mass-owner','scheduler-owner','last-hook-shadow','reentry'] as const) {
  const x=createBattlePassengerEarlyStopFixture(make);let hit=false,getters=0;
  trace(x,fault.includes('closed')?'incomplete':fault==='reentry'?'reentry':fault==='last-hook-shadow'?'competing':fault.includes('owner')?'owner changed':'own data',(owner,key)=>{
   const trigger=fault==='last-hook-shadow'?owner===x.targetActor&&key==='131':owner===x.passenger83&&key==='byte83';
   if(!trigger||hit)return;hit=true;
   if(fault==='caller-closed')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
   if(fault==='target-closed')markIncompleteSourceActorDoubleLifecycle(x.targetActor);
   if(fault==='pointer-delete')delete x.sourceActor.linkedOwner1e4;
   if(fault==='pointer-accessor')Object.defineProperty(x.sourceActor,'linkedOwner1e4',{get(){getters++;throw Error('late pointer getter');}});
   if(fault==='mass-owner')x.sources.massPreparation={...x.massPreparation};
   if(fault==='scheduler-owner')Reflect.set(x.sources,'scheduler',{});
   if(fault==='last-hook-shadow')Reflect.set(x.sourceActor,'field1e4',null);
   if(fault==='reentry')refuses(()=>x.outer.runFrame(),'same-runtime reentry');
  });
  check(hit,'late failure injection reached');equal(getters,0,'late pointer getter not invoked');prefix(x,200);closed(x);
 }
 {
  const x=createBattlePassengerEarlyStopFixture(make);delete x.sourceActor.linkedOwner1e4;Reflect.set(x.sourceActor,'linkedOwner',x.targetActor);
  trace(x,'unsupported actual pointer1e4');prefix(x,200);closed(x,false);
 }
}
export function runBattlePassengerEarlyStopSelfTests(make:Make):void {
 let count=0;const counted:Make=()=>{count++;return make();};branches(counted);capture(counted);failures(counted);
 console.log(`[battle-passenger-early-stop] PASS (${count} genuine shared-graph fixtures): actual1e4 capture, allocation-owned signed83, both half exits, six live table reloads, lazy continuation, alias/lifecycle/late-descriptor refusal and permanent closure; zero83 stops before slot/mass/count, no passenger propagation or complete frame`);
}
