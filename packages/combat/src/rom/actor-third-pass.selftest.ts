import {createRomActor} from './actor.js';
import {createActorSecondaryNullTestFixture} from './actor-secondary-null.selftest.js';
import {createSourceActorCommandAdmissionRuntime,type SourceActorCommandAdmissionBinding} from './actor-command-admission.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const next='80029460 reached mandatory80027764';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-third-pass-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}

/** Separate explicit host composition, not execution of retail constructors.
 * The existing sparse fixture stays unchanged. New physical identities come
 * from the real mapping registry and own distinct records in the SAME world,
 * status, attribute, charge, action, cue, dispatch and stream runtimes.
 * Only an explicitly supplied508 cell is copied into each genuine admission.
 * No inactive fallback, alternate pointer map or production owner is added.
 * The live mass table retains its documented repeated primary identity; this
 * fixture proves the distinct physical target pass, not six-actor mass setup.
 */
function fixture(make:Make,count=5,omittedRow=-1,firstInitial?:Readonly<Partial<SourceActorCommandAdmissionBinding>>) {
 const x=createActorSecondaryNullTestFixture(make);
 const ids=[...x.physicalIdentities],actuals:object[]=[...x.slotTargets];
 const bindings:(Partial<SourceActorCommandAdmissionBinding>|undefined)[]=[x.admissionState];
 for(let i=1;i<=count;i++) {
 const parts=Array.from({length:2},()=>Array.from({length:4},()=>x.mapping.createPart(
  {frame0c:0,duration24:0,segment2d:0,complete2e:0,mode2f:0,mirror30:0},
  {descriptor00:null,scaleIndex32:255,jointBank33:0,poseBuffer35:0})));
 const poses=Array.from({length:2},()=>Array.from({length:2},()=>x.feedback.createPose({translation:{x:0,y:0,z:0},quaternion:{x:0,y:0,z:0,w:1}})));
 const id=x.mapping.createActor({descriptor4b0:null,jointCount1d90:0,boundary1d91:0,boundary1d92:0,boundary1d93:0,jointBank1db4:null,jointBank1db8:null,timestep1dc8:0},{parts,poses});
 const actual=createRomActor(); actual.active0=0;
 const fresh=()=>x.matrices.createMatrix(Array(12).fill(0));
 x.world.bindActor(id,actual,{mode4a0:2,mode4a1:0,flags48a:0,mask1d70:0,roll74:0,yawOffset6b8:0,scale58:{x:1,y:1,z:1},offset1dbc:{x:0,y:0,z:0},adjusted1d54:{x:0,y:0,z:0},preRotation1d64:{x:0,y:0,z:0}},
 {matrices8d4:[fresh(),fresh()],copy114:fresh(),copy1aa4:fresh(),scratch:fresh(),topology1994:[[255,255,0,0],[255,255,0,0]],corrections18d4:[{x:0,y:0,z:0},{y:0,z:0}],scales15d4:[{x:1,y:1,z:1},{x:1,y:1,z:1}]});
 x.dispatch.bindActor(id,{family1d88:null,shared1d8c:null,marker578:0,marker1db3:0});
 x.control.bindActor(id,{activeMask579:0,blockedMask1d9a:0,marker71d:0},Array.from({length:4},()=>({current00:null,next04:null,wait14:0,finished1a:0,event1e:0,group18:0,action19:0,status1d:0,state1b:0,auxiliary1c:0})));
 x.control.bindStartActor(id,{familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:0});
 x.ready.bindActor(id,{familyBank1d78:null,sharedBank1d7c:null,movement6d8:0});
 x.movement.bindActor(id,actual,{byte661:0,field66c:0,field670:0});x.attributes.bindActor(id,{});
 Reflect.deleteProperty(actual,'invulnTimer');
 const slot=()=>({cell:{cur:0,max:0,refillType:0,refillParam:0,timer:0},mirror776:0});
 x.status.bindActor(id,{hp:1,hitDrainFrames:0,balanceGauge:0,balanceGaugeMax:0,balanceRefillDelay:0,downResetDelay:0,comboWindow:0,comboAccum:0,comboRank:0,invincTimer:0,sourceAmmoRefillPauseMask:0},{},[slot(),slot(),slot()]);
 for(const key of ['fbPhaseSlots','shotByte1db3','animState'])Reflect.deleteProperty(actual,key);
 x.cues.bindActor(id,{});
 const charge=x.commandAdmission.getChargeRuntime();charge.getEffects()?.bindActor(id,{});charge.bindActor(id,{});
 x.commandAdmission.getActionRuntime().bindActor(id,{});
 x.commandAdmission.bindActor(id, i===1&&firstInitial!==undefined?firstInitial:i===omittedRow?{}:{pointer508:null});
 x.allocator.registerExternal(id,actual);
 ids[i]=id;actuals[i]=actual;bindings[i]=x.commandAdmission.getActorBinding(id);

 }
 const physicalIdentities=Object.freeze(ids);
 x.massPreparation.physicalBlock=Object.freeze({base:x.actor,identities:physicalIdentities});
 return Object.assign(x,{physicalIdentities,physicalActors:actuals,physicalBindings:bindings,boundCount:count});
}
type Fixture=ReturnType<typeof fixture>;
/** Same genuine six-actor composition for later source continuation tests. */
export function createActorThirdPassTestFixture(make:Make) {return fixture(make);}


function trace(x:Fixture,expected=next,before:Visit=()=>{},after?:Visit) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];
 let secondary=false,third=false,schedulerReads=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.sourceActor&&key==='visibilityTarget')secondary=true;
  if(secondary&&owner===x.massPreparation&&key==='physicalBlock')third=true;
  if(secondary&&(owner===x.groups||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))))schedulerReads++;
  if(third) {
   if(owner===x.physicalIdentities&&/^[0-5]$/.test(String(key)))events.push('row'+String(key));
   const actual=x.physicalActors.indexOf(owner),binding=x.physicalBindings.indexOf(owner);
   if(actual>=0&&key==='active0')events.push('active'+actual);
   if(binding>=0&&key==='pointer508')events.push('508-'+binding);
   before(owner,key);
  }
  const result=native(owner,key);if(third)after?.(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(secondary&&third,'real secondary return and fresh third-pass physical base reached');
 equal(schedulerReads,0,'no scheduler masks or group authority after target preparation');
 return {events,message};
}
const fullEvents=(rows:number)=>Array.from({length:rows},(_,i)=>[`row${i}`,`active${i}`,`508-${i}`]).flat();
function retained(x:Fixture):void {
 equal(x.sourceActor.byte502,0,'genuine empty selector result retained');
 equal(x.admissionState.pointer508,null,'genuine empty selector null pointer retained');
 equal(x.globals.count804361a0,0,'selector scratch count retained');
 for(const key of ['targetDistance758','horizontalDistance75c','targetDistance760','horizontalDistance764'])
  equal(Reflect.get(x.sourceActor,key),20000,`${key} sentinel retained`);
 for(const vector of [x.vector,x.aim])for(const [i,key]of ['x','y','z'].entries())equal(Reflect.get(vector,key),[0,0,20000][i],`completed ${key} retained`);
 equal(x.massPreparation.orderCount.count80436260,6,'preceding genuine mass order retained');
 equal(x.massHost.sourceArrowMass204,1200,'preceding mass write retained');
}
function closed(x:Fixture):void {
 for(const actor of x.physicalActors)check(hasIncompleteSourceActorDoubleLifecycle(actor),'outer refusal closes every retained physical actor');
 refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const call of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(call,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function assertOwners(x:Fixture):void {
 const ids=x.physicalIdentities.slice(0,x.boundCount+1);
 for(const getter of [x.commandAdmission.getActualActor,x.commandAdmission.getActorBinding,x.commandAdmission.getWorldBinding,
  x.commandAdmission.getStatusBinding,x.commandAdmission.getMappingActor,x.commandAdmission.getAttributeBinding,
  x.commandAdmission.getChargeBinding,x.commandAdmission.getActionBinding,x.commandAdmission.getCueBinding,
  x.commandAdmission.getDispatchBinding,x.commandAdmission.getStartBinding,x.commandAdmission.getStreamBinding])
  equal(new Set(ids.map(id=>getter(id))).size,ids.length,'every actor has a distinct canonical owner for each source role');
 for(const [i,id]of ids.entries()) {
  equal(x.world.getActualActor(id),x.physicalActors[i],'world retains exact physical actor');
  equal(x.status.getActualActor(id),x.physicalActors[i],'status retains exact physical actor');
  equal(x.allocator.getPointerTarget(id),x.physicalActors[i],'allocator pointer reaches the same physical record');
  equal(x.commandAdmission.getActorBinding(id),x.physicalBindings[i],'third-pass binding is the genuine admission owner');
  check(Object.isSealed(x.physicalBindings[i]),'canonical pointer binding is sealed');
 }
}
function compositionTests(make:Make):void {
 for(const count of [0,1,2,3,4,5]) {
  const x=fixture(make,count);assertOwners(x);
  const claimed=x.physicalActors.map(isSourceActorDoubleFrameClaimed);
  const result=trace(x,count===5?next:'unknown/non-owned admission actor');
  const expected=count===5?fullEvents(6):[...fullEvents(count+1),`row${count+1}`,`active${count+1}`];
  equal(result.events.join(','),expected.join(','),'each additional genuine owner advances exactly one physical row');
  x.physicalActors.forEach((actor,i)=>equal(isSourceActorDoubleFrameClaimed(actor),claimed[i],'no actor frame authority manufactured'));
  retained(x);closed(x);
 }
 const x=fixture(make);let getters=0;
 for(let i=1;i<6;i++)for(const key of ['heading','team','byte7d3','horizontalDistance75c','field814'])
  Object.defineProperty(x.physicalActors[i],key,{get(){getters++;throw Error('unreached inactive scalar');},configurable:true});
 trace(x);equal(getters,0,'inactive rows do not hydrate or read unrelated source fields');retained(x);closed(x);
}
function pointerTests(make:Make):void {
 for(const row of [1,3,5]) {
  const x=fixture(make,5,row),result=trace(x,'pointer508');
  equal(result.events.join(','),[...fullEvents(row),`row${row}`,`active${row}`,`508-${row}`].join(','),'missing inactive508 refuses at its own source load');retained(x);closed(x);
 }
 for(const row of [1,3,5]) {
  const x=fixture(make),binding=x.physicalBindings[row]!;Reflect.set(binding,'pointer508',undefined);
  const result=trace(x,'pointer508');
  equal(result.events.join(','),[...fullEvents(row),`row${row}`,`active${row}`,`508-${row}`].join(','),'undefined inactive508 does not become null');retained(x);closed(x);
 }
 for(const kind of ['opaque','other-actor','readonly'] as const) {
  const x=fixture(make);let getters=0;
  const opaque={};for(const key of ['eligibility83','team','byte58a','byte7d3'])Object.defineProperty(opaque,key,{get(){getters++;throw Error('inactive pointer dereference');}});
  x.physicalBindings[1]!.pointer508=kind==='other-actor'?x.physicalActors[2]!:opaque;
  if(kind==='readonly')Object.defineProperty(x.physicalBindings[1]!,'pointer508',{writable:false});
  equal(trace(x).events.join(','),fullEvents(6).join(','),'inactive nonnull pointer remains opaque after its mandatory load');
  equal(getters,0,'no target scalar is dereferenced for inactive row');retained(x);closed(x);
 }
 // Exercise first binding of a genuinely new identity, not the duplicate-ID
 // guard. Inherited cells stay absent, while accessor/undefined cells fail.
 {
  const initial=Object.create({pointer508:null});
  const x=fixture(make,5,-1,initial);
  check(!Object.hasOwn(x.physicalBindings[1]!,'pointer508'),'inherited input never becomes canonical own storage');
  equal(trace(x,'pointer508').events.join(','),[...fullEvents(1),'row1','active1','508-1'].join(','),'inherited input refuses at actual third-pass load');retained(x);closed(x);
 }
 for(const kind of ['accessor','undefined'] as const) {
  let reads=0;const initial:Partial<SourceActorCommandAdmissionBinding>={};
  if(kind==='accessor')Object.defineProperty(initial,'pointer508',{get(){reads++;return null;}});
  else Reflect.set(initial,'pointer508',undefined);
  refuses(()=>fixture(make,1,-1,initial),'pointer508');
  equal(reads,0,'new admission never invokes malformed source accessor');
 }
 {
  const initial:Partial<SourceActorCommandAdmissionBinding>={pointer508:null};
  const x=fixture(make,5,-1,initial);initial.pointer508={};
  equal(x.physicalBindings[1]!.pointer508,null,'admission copies explicit data into distinct canonical binding');
  trace(x);retained(x);closed(x);
 }
}
function capturedOrderTests(make:Make):void {
 for(const active of [false,true]) {
  const x=fixture(make),actor=x.physicalActors[1]!,binding=x.physicalBindings[1]!;let activeRead=false,pointerRead=false,targetReads=0;
  const opaque={};Object.defineProperty(opaque,'eligibility83',{get(){targetReads++;throw Error('target83 read');}});binding.pointer508=opaque;
  const result=trace(x,active?'8006b374':next,(owner,key)=>{
   if(owner===actor&&key==='active0'){activeRead=true;Reflect.set(actor,'active0',active?1:0);}
   if(owner===binding&&key==='pointer508'){pointerRead=true;Reflect.set(actor,'active0',active?0:1);}
  });
  check(activeRead&&pointerRead,'active load precedes pointer load on real third pass');
  equal(targetReads,0,'active nonnull pointer stops before unsupported target83; inactive pointer remains opaque');
  equal(result.events.join(','),(active?[...fullEvents(1),'row1','active1','508-1']:fullEvents(6)).join(','),'captured active byte controls branch despite later source mutation');retained(x);closed(x);
 }
 for(const initiallyNull of [true,false]) {
  const x=fixture(make),actor=x.physicalActors[1]!,binding=x.physicalBindings[1]!;let hit=false;
  const opaque={};binding.pointer508=initiallyNull?null:opaque;
  trace(x,initiallyNull?next:'8006b374',(owner,key)=>{if(owner===actor&&key==='active0')Reflect.set(actor,'active0',1);},
   (owner,key)=>{if(!hit&&owner===binding&&key==='pointer508'){hit=true;binding.pointer508=initiallyNull?opaque:null;}});
  check(hit,'pointer changed after actual source descriptor capture');retained(x);closed(x);
 }
}
function ownerFailureTests(make:Make):void {
 for(const key of ['pointer508','field508','byte508','1288']) {
  const x=fixture(make);let hit=false;
  const result=trace(x,'competing',(owner,field)=>{if(owner===x.physicalActors[2]&&field==='active0'){hit=true;Reflect.set(owner,key,null);}});
  check(hit,'late actual-actor pointer shadow introduced');equal(result.events.join(','),[...fullEvents(2),'row2','active2'].join(','),'shadow refuses before canonical pointer or later actors');retained(x);closed(x);
 }
 {
  const x=fixture(make),other=createSourceActorCommandAdmissionRuntime({world:x.world,status:x.status,attributes:x.attributes,
   charge:x.commandAdmission.getChargeRuntime(),actionRequest:x.commandAdmission.getActionRuntime(),cues:x.cues,streams:x.control,gqr5:0x00070007});
  for(const id of x.physicalIdentities)refuses(()=>other.bindActor(id,{pointer508:null}),'already claimed');
  assertOwners(x);trace(x);retained(x);closed(x);
 }
 for(const at of ['active','pointer'] as const) {
  const x=fixture(make);let hit=false;
  const result=trace(x,'reentry',(owner,key)=>{if(!hit&&(at==='active'?owner===x.physicalActors[3]&&key==='active0':owner===x.physicalBindings[3]&&key==='pointer508')) {
   hit=true;refuses(()=>x.frame.runFrame(),'same-runtime reentry');
  }});
  check(hit,'caught outer reentry at exact third-pass source load');
  equal(result.events.join(','),[...fullEvents(3),'row3','active3',...(at==='pointer'?['508-3']:[])].join(','),'caught reentry prevents later row reads');retained(x);closed(x);
 }
}
export function runActorThirdPassSelfTests(make:Make):void {
 let fixtures=0;const counted:Make=omit=>{fixtures++;return make(omit);};
 compositionTests(counted);pointerTests(counted);capturedOrderTests(counted);ownerFailureTests(counted);
 console.log(`[actor-third-pass] PASS (${fixtures} genuine shared-graph fixtures): six distinct canonical admission owners, unconditional inactive508 reads, captured active/pointer order, opaque pointers, missing-owner and partial failure closure; target preparation reaches mandatory27764 only, no retail constructor, completed frame, scheduler execution or browser claim`);
}
