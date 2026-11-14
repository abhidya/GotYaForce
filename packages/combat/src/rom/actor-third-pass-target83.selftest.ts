import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Fixture=ReturnType<typeof createActorThirdPassTestFixture>;
type Visit=(owner:object,key:PropertyKey)=>void;
const next='80029460 reached mandatory80027764',zero='8006b380';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-third-pass-target83-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
function fixture(make:Make,value:number|null=1,targetRow=2,bind=true) {
 const x=createActorThirdPassTestFixture(make),targetId=x.physicalIdentities[targetRow]!,targetActor=x.physicalActors[targetRow]!;
 if(bind)x.allocator.bindActor(targetId,value===null?{}:{byte83:value});
 const binding=bind?x.allocator.getActorBinding(targetId):undefined;
 x.physicalBindings[1]!.pointer508=targetActor;
 return Object.assign(x,{targetId,targetActor,target83:binding});
}
type Bound=ReturnType<typeof fixture>;
function run(x:Bound,expected=next,before:Visit=()=>{},after?:Visit,activate=true) {
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];
 let secondary=false,third=false,reads=0,later=0,scheduler=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  if(owner===x.sourceActor&&key==='visibilityTarget')secondary=true;
  if(secondary&&owner===x.massPreparation&&key==='physicalBlock')third=true;
  if(third) {
   const actor=x.physicalActors.indexOf(owner),binding=x.physicalBindings.indexOf(owner);
   if(owner===x.physicalIdentities&&/^[0-5]$/.test(String(key)))events.push('row'+String(key));
   if(actor>=0&&key==='active0'){events.push('active'+actor);if(activate&&actor===1)Reflect.set(owner,'active0',1);}
   if(binding>=0&&key==='pointer508')events.push('508-'+binding);
   if(owner===x.target83&&key==='byte83'){reads++;events.push('target83');}
   if((owner===x.physicalActors[1]&&key==='byte7d3')||(owner===x.targetActor&&['team','byte58a'].includes(String(key))))later++;
   // Alias metadata checks on the group-table object are not group loads.
   if(owner===x.groups&&/^\d+$/.test(String(key))||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))scheduler++;
   before(owner,key);
  }
  const result=native(owner,key);if(third)after?.(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(secondary&&third,'actual secondary return and third pass reached');equal(later,0,'no actor7d3 or target association scalar read');equal(scheduler,0,'no scheduler execution reads');
 return {events,reads,message};
}
function retained(x:Fixture):void {
 equal(x.massHost.sourceArrowMass204,1200,'preceding mass write retained');equal(x.massPreparation.orderCount.count80436260,6,'preceding ordering retained');
 equal(x.sourceActor.byte502,0,'zero candidate source result retained');equal(x.admissionState.pointer508,null,'primary canonical508 null retained');
 for(const key of ['targetDistance758','horizontalDistance75c','targetDistance760','horizontalDistance764'])equal(Reflect.get(x.sourceActor,key),20000,'preceding distance sentinel retained');
 for(const vector of [x.vector,x.aim])for(const [i,key]of ['x','y','z'].entries())equal(Reflect.get(vector,key),[0,0,20000][i],'completed direction store retained');
}
function closed(x:Fixture):void {
 for(const actor of x.physicalActors)check(hasIncompleteSourceActorDoubleLifecycle(actor),'all retained physical actors close after refusal');
 refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const f of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(f,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
const events=(stop=false)=>['row0','active0','508-0','row1','active1','508-1','target83',...(stop?[]:[2,3,4,5].flatMap(i=>['row'+i,'active'+i,'508-'+i]))];
function branches(make:Make):void {
 for(const value of [0,1,2,127,128,254,255]) {
  const x=fixture(make,value);let getters=0;
  for(const key of ['team','byte58a','byte7d3'])Object.defineProperty(x.targetActor,key,{get(){getters++;throw Error('unreached target scalar');},configurable:true});
  const result=run(x,value===0?zero:next);
  equal(result.reads,1,'one canonical target83 byte read');equal(result.events.join(','),events(value===0).join(','),'source row/active/pointer/target83 order');equal(getters,0,'no later target getter');
  equal(x.allocator.getActualActor(x.targetId),x.targetActor,'allocator retains actual target');equal(x.world.getActualActor(x.targetId),x.targetActor,'world retains same target');
  equal(x.allocator.getActorBinding(x.targetId),x.target83,'canonical allocation83 owner retained');equal(x.target83!.byte83,value,'source byte is read-only');retained(x);closed(x);
 }
 {const x=fixture(make,255,1);run(x);retained(x);closed(x);}
 {const x=fixture(make,1);Object.defineProperty(x.target83!,'byte83',{writable:false});run(x);retained(x);closed(x);}
 {const x=fixture(make,1);let invoked=0;Object.defineProperty(x.targetActor,'eligibility83',{get(){invoked++;throw Error('unreached inactive target');}});equal(run(x,next,()=>{},undefined,false).reads,0,'inactive pointer never resolves target83');equal(invoked,0,'inactive target remains opaque');retained(x);closed(x);}
 {const x=fixture(make,1);x.physicalBindings[1]!.pointer508=null;equal(run(x).reads,0,'captured null skips target83');retained(x);closed(x);}
}
function captured(make:Make):void {
 for(const value of [0,1]) {
  const x=fixture(make,value);let hit=false;
  const r=run(x,value===0?zero:next,()=>{},(owner,key)=>{if(owner===x.target83&&key==='byte83'){hit=true;x.target83!.byte83=value===0?1:0;}});
  check(hit,'mutation after source83 descriptor capture');equal(r.reads,1,'no target83 reload');retained(x);closed(x);
 }
 {const x=fixture(make,1);let hit=false;run(x,next,(owner,key)=>{if(owner===x.target83&&key==='byte83'){hit=true;x.physicalBindings[1]!.pointer508={};Reflect.set(x.physicalActors[1]!,'active0',0);}});check(hit,'captured actor and pointer changed after branch/source load');retained(x);closed(x);}
 {
  const x=fixture(make,1);x.physicalBindings[3]!.pointer508=x.targetActor;let first=true;
  const r=run(x,zero,(owner,key)=>{if(owner===x.physicalActors[3]&&key==='active0'){Reflect.set(owner,'active0',1);x.target83!.byte83=0;}
   if(owner===x.target83&&key==='byte83'){if(first)first=false;}});
  equal(r.reads,2,'a later active actor reads the live same canonical target byte again');equal(r.events.at(-1),'target83','later zero byte stops before association');retained(x);closed(x);
 }
}
function failures(make:Make):void {
 for(const kind of ['unbound','missing','undefined','negative','fractional','too-large','nan'] as const) {
  const x=fixture(make,kind==='missing'?null:1,2,kind!=='unbound');
  const bad={undefined:undefined,negative:-1,fractional:0.5,'too-large':256,nan:NaN};
  if(kind in bad)Reflect.set(x.target83!,'byte83',bad[kind as keyof typeof bad]);
  run(x,'8006b374');retained(x);closed(x);
 }
 for(const key of ['byte83','eligibility83','groupEligibility83','field83','131'])for(const late of [false,true]) {
  const x=fixture(make,1);let hit=false,invoked=0;
  const add=()=>Object.defineProperty(x.targetActor,key,{get(){invoked++;throw Error('competing target getter');},configurable:true});if(!late)add();
  run(x,'competing',(owner,field)=>{if(late&&owner===x.target83&&field==='byte83'){hit=true;add();}});
  equal(invoked,0,'competing source alias getter never invoked');if(late)check(hit,'late alias added at actual source83 load');retained(x);closed(x);
 }
 {const x=fixture(make,1);let hit=false;run(x,'incomplete',(owner,key)=>{if(owner===x.physicalBindings[1]&&key==='pointer508'){hit=true;markIncompleteSourceActorDoubleLifecycle(x.targetActor);}});check(hit,'independent target closure injected before83 admission');retained(x);closed(x);}
 {const x=fixture(make,1);let hit=false;run(x,'incomplete',(owner,key)=>{if(owner===x.target83&&key==='byte83'){hit=true;markIncompleteSourceActorDoubleLifecycle(x.physicalActors[1]!);}});check(hit,'independent caller closure at source83 blocks later rows');retained(x);closed(x);}
 {const x=fixture(make,1);let hit=false;run(x,'competing',(owner,key)=>{if(owner===x.target83&&key==='byte83'){hit=true;Reflect.set(x.physicalActors[1]!,'field508',null);}});check(hit,'late caller508 alias at source83 blocks later rows');retained(x);closed(x);}
 {const x=fixture(make,1);let hit=false;run(x,'reentry',(owner,key)=>{if(owner===x.target83&&key==='byte83'){hit=true;refuses(()=>x.frame.runFrame(),'same-runtime reentry');}});check(hit,'caught outer reentry at source83');retained(x);closed(x);}
}
export function runActorThirdPassTarget83SelfTests(make:Make):void {
 let count=0;const counted:Make=omit=>{count++;return make(omit);};branches(counted);captured(counted);failures(counted);
 console.log(`[actor-third-pass-target83] PASS (${count} genuine shared-graph fixtures): allocation-owned target83, active/null gating, signed nonzero skips, captured pointer/byte order, lazy faults, aliases and permanent failure closure; stops before actor7d3 or mandatory27764, no complete association, outer frame, scheduler execution or browser claim`);
}
