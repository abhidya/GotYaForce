import {captureMissingLeaderIngress} from './battle-leader-ingress.selftest.js';
import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey,inner:boolean)=>void;
const next='pointer38: own data property required';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-association-scan-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(f:()=>unknown,part:string):string {let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
/** Explicit source-cell inputs on the same genuine six-actor graph. Only the
 * caller is activated at the third pass; this is not retail constructor or
 * six-active-actor predecessor hydration. */
export function createActorAssociationScanTestFixture(make:Make,targetRow=2) {
 const x=createActorThirdPassTestFixture(make,{field814:20}),caller=x.physicalActors[1]!,target=x.physicalActors[targetRow]!;
 for(const actor of x.physicalActors.slice(1))Object.assign(actor,{byte7d3:16,team:9});
 Object.assign(caller,{byte7d3:32,team:0,horizontalDistance75c:10});
 Object.assign(target,{byte7d3:target===caller?32:64,team:target===caller?0:1,byte58a:8});
 Reflect.set(x.physicalActors[3]!,'team',0);
 x.allocator.bindActor(x.physicalIdentities[targetRow]!,{byte83:0});x.physicalBindings[1]!.pointer508=target;
 const threshold=x.attributes.getActorBinding(x.physicalIdentities[1]!);
 return Object.assign(x,{caller,target,threshold,target83:x.allocator.getActorBinding(x.physicalIdentities[targetRow]!),candidate:x.physicalActors[3]!});
}
type Fixture=ReturnType<typeof createActorAssociationScanTestFixture>;
function retained(x:Fixture):void {
 equal(x.massHost.sourceArrowMass204,1200,'prior mass retained');equal(x.massPreparation.orderCount.count80436260,6,'prior ordering retained');
 equal(x.sourceActor.byte502,0,'genuine zero candidate result retained');equal(x.admissionState.pointer508,null,'primary null retained');
 for(const key of ['targetDistance758','horizontalDistance75c','targetDistance760','horizontalDistance764'])equal(Reflect.get(x.sourceActor,key),20000,'prior sentinel retained');
 for(const v of [x.vector,x.aim])for(const [i,key]of ['x','y','z'].entries())equal(Reflect.get(v,key),[0,0,20000][i],'prior direction retained');
}
function closed(x:Fixture):void {
 for(const a of x.physicalActors)check(hasIncompleteSourceActorDoubleLifecycle(a),'every retained actor closes');refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const f of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(f,'exclusively owned');
 refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function run(x:Fixture,expected=next,before:Visit=()=>{},after:Visit=()=>{}) {
 const leaderPrefix=captureMissingLeaderIngress(x);
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];
 let secondary=false,third=false,inner=false,physicalLoads=0,scheduler=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  leaderPrefix.observe(owner,key);
  if(owner===x.sourceActor&&key==='visibilityTarget')secondary=true;
  if(secondary&&owner===x.massPreparation&&key==='physicalBlock'){third=true;physicalLoads++;inner=physicalLoads>1;}
  if(third) {
   if(x.physicalActors.includes(owner)&&key==='active0')inner=false;
   if(owner===x.caller&&key==='active0')Reflect.set(owner,'active0',1);
   if(inner) {
    if(owner===x.target&&key==='byte58a')events.push('mask');
    const i=x.physicalActors.indexOf(owner);
    if(i>=0&&key==='team')events.push('team'+i);
    if(i>=0&&key==='byte7d3')events.push('flag'+i);
   }
   if(owner===x.groups&&/^\d+$/.test(String(key))||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))scheduler++;
   before(owner,key,inner);
  }
  const result=native(owner,key);if(third)after(owner,key,inner);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 if(expected===next)leaderPrefix.assert();
 check(secondary&&third,'genuine predecessors reached');equal(scheduler,0,'no scheduler access');retained(x);closed(x);
 return {events,message,physicalLoads};
}
const stores=(candidate=3,target=2)=>['flag1','flag1',`flag${candidate}`,`flag${candidate}`,`flag${target}`,`flag${target}`];
function branchTests(make:Make):void {
 for(const mask of [0,2,128,192]) {
  const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',mask);
  const r=run(x);equal(r.events.join(','),Array(5).fill('mask').join(','),'six positions, self skips before mask');equal(r.physicalLoads,2,'one fresh inner base');
  equal(Reflect.get(x.caller,'byte7d3'),32,'no-match caller unchanged');equal(Reflect.get(x.target,'byte7d3'),64,'no-match target unchanged');
 }
 for(const position of [0,3,4,5]) {
  const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',1<<position);Reflect.set(x.physicalActors[position]!,'team',0);
  const r=run(x);equal(r.events.join(','),[...Array(position+(position===0?1:0)).fill('mask'),`team${position}`,...stores(position)].join(','),'lazy first hit and separate flag pairs');
  equal(Reflect.get(x.caller,'byte7d3'),33,'caller bit0 set');equal(Reflect.get(x.physicalActors[position]!,'byte7d3'),position===0?1:17,'candidate bit0 set');equal(Reflect.get(x.target,'byte7d3'),66,'target bit1 set');
 }
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',24);Reflect.set(x.physicalActors[4]!,'team',0);const r=run(x);equal(r.events.join(','),['mask','mask','mask','team3',...stores()].join(','),'first match exits before later same-team candidate');equal(Reflect.get(x.physicalActors[4]!,'byte7d3'),16,'later candidate untouched');}
 for(const team of [128,255,2]) {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.caller,'team',team);Reflect.set(x.candidate,'team',team);run(x);equal(Reflect.get(x.candidate,'byte7d3'),17,'all signed raw teams supported');}
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.candidate,'team',255);const r=run(x);equal(r.events.join(','),['mask','mask','mask','team3','mask','mask'].join(','),'mismatched team continues through sixth position');}
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',0);let called=0;Object.defineProperty(x.candidate,'team',{get(){called++;throw Error('unreached team');},configurable:true});run(x);equal(called,0,'mask misses never invoke candidate team');}
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.candidate,'active0',0);run(x);equal(Reflect.get(x.candidate,'byte7d3'),17,'inactive matching candidate is not skipped');}
}
function captureTests(make:Make):void {
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',0);let masks=0;const r=run(x,next,undefined,(o,k,inner)=>{if(inner&&o===x.target&&k==='byte58a'&&++masks===1)Reflect.set(o,k,8);});equal(r.events.join(','),['mask','mask','mask','team3',...stores()].join(','),'mask reload sees change between candidates');}
 {const x=createActorAssociationScanTestFixture(make);let masks=0;const r=run(x,next,undefined,(o,k,inner)=>{if(inner&&o===x.target&&k==='byte58a'&&++masks===1)Reflect.set(o,k,0);});equal(r.events.join(','),Array(5).fill('mask').join(','),'initial mask is not cached for later positions');}
 {const x=createActorAssociationScanTestFixture(make);let masks=0;run(x,next,undefined,(o,k,inner)=>{if(inner&&o===x.target&&k==='byte58a'&&++masks===3)Reflect.set(o,k,0);});equal(Reflect.get(x.candidate,'byte7d3'),17,'captured mask still controls current candidate');}
 {const x=createActorAssociationScanTestFixture(make);run(x,next,undefined,(o,k)=>{if(o===x.threshold&&k==='field814')Reflect.set(x.caller,'team',9);});equal(Reflect.get(x.candidate,'byte7d3'),17,'candidate compares captured caller team');}
 {const x=createActorAssociationScanTestFixture(make);run(x,next,undefined,(o,k)=>{if(o===x.threshold&&k==='field814')Reflect.set(x.caller,'byte7d3',128);});equal(Reflect.get(x.caller,'byte7d3'),129,'association reloads caller flags after early bit test');}
 {const x=createActorAssociationScanTestFixture(make);let reads=0;run(x,next,undefined,(o,k,inner)=>{if(inner&&o===x.caller&&k==='byte7d3'&&++reads===1)Reflect.set(o,k,128);});equal(Reflect.get(x.caller,'byte7d3'),33,'store uses captured fresh flag load, not later scalar');}
 {const x=createActorAssociationScanTestFixture(make);run(x,next,(o,k,inner)=>{if(inner&&o===x.candidate&&k==='byte7d3')Reflect.set(o,k,64);if(inner&&o===x.target&&k==='byte7d3')Reflect.set(o,k,128);});equal(Reflect.get(x.candidate,'byte7d3'),65,'candidate fresh flags');equal(Reflect.get(x.target,'byte7d3'),130,'target fresh flags');}
 // Equal actual roles are legal. Earlier team loads remain captured while
 // subsequent fresh byte7d3 loads must see previous stores on the same owner.
 {const x=createActorAssociationScanTestFixture(make);Reflect.set(x.target,'byte58a',4);run(x,next,undefined,(o,k)=>{if(o===x.threshold&&k==='field814')Reflect.set(x.target,'team',0);});equal(Reflect.get(x.target,'byte7d3'),67,'candidate==target sees bit0 store before OR2');}
 {const x=createActorAssociationScanTestFixture(make,1);Reflect.set(x.candidate,'team',1);let teams=0;run(x,next,undefined,(o,k,inner)=>{if(!inner&&o===x.caller&&k==='team'&&++teams===1)Reflect.set(o,k,1);});equal(Reflect.get(x.caller,'byte7d3'),35,'caller==target sees first store before final OR2');equal(Reflect.get(x.candidate,'byte7d3'),17,'shared-target candidate also written');}
 {const x=createActorAssociationScanTestFixture(make);run(x,next,undefined,(o,k)=>{if(o===x.threshold&&k==='field814'){x.physicalBindings[1]!.pointer508={};x.target83.byte83=255;Reflect.set(x.caller,'active0',0);}});equal(Reflect.get(x.target,'byte7d3'),66,'captured target/83/active do not reload');}
}
function faultTests(make:Make):void {
 for(const value of [undefined,-1,256,1.5])for(const role of ['mask','team','caller','candidate','target']) {
  const x=createActorAssociationScanTestFixture(make),owner=role==='mask'||role==='target'?x.target:role==='team'||role==='candidate'?x.candidate:x.caller;
  const key=role==='mask'?'byte58a':role==='team'?'team':'byte7d3';
  run(x,key,undefined,(o,k)=>{if(o===x.threshold&&k==='field814')Reflect.set(owner,key,value);});
  if(role==='candidate'||role==='target')equal(Reflect.get(x.caller,'byte7d3'),33,'earlier caller store survives later bad byte');
  if(role==='target')equal(Reflect.get(x.candidate,'byte7d3'),17,'earlier candidate store survives bad target byte');
 }
 for(const role of ['caller','candidate','target']) {
  const x=createActorAssociationScanTestFixture(make),owner=role==='caller'?x.caller:role==='candidate'?x.candidate:x.target;
  Object.defineProperty(owner,'byte7d3',{writable:false});run(x,'non-writable association');
  equal(Reflect.get(x.caller,'byte7d3'),role==='caller'?32:33,'caller store partial order');equal(Reflect.get(x.candidate,'byte7d3'),role==='target'?17:16,'candidate store partial order');equal(Reflect.get(x.target,'byte7d3'),64,'target store not performed');
 }
 for(const role of ['caller','candidate','target'])for(const kind of ['delete','accessor','readonly']) {
  const x=createActorAssociationScanTestFixture(make),owner=role==='caller'?x.caller:role==='candidate'?x.candidate:x.target;let reads=0,getters=0;
  run(x,kind==='readonly'?'live non-writable':'live own data',undefined,(o,k,inner)=>{
   if(inner&&o===owner&&k==='byte7d3'&&++reads===2) {
    if(kind==='delete')Reflect.deleteProperty(owner,'byte7d3');
    else if(kind==='readonly')Object.defineProperty(owner,'byte7d3',{writable:false});
    else Object.defineProperty(owner,'byte7d3',{get(){getters++;return 255;},configurable:true});
   }
  });equal(getters,0,'late destination accessor never invoked');
  if(role!=='caller')equal(Reflect.get(x.caller,'byte7d3'),33,'prior caller write preserved after destination mutation');
  if(role==='target')equal(Reflect.get(x.candidate,'byte7d3'),17,'prior candidate write preserved after destination mutation');
 }
 for(const [role,key,alias]of [['target','byte58a','1418'],['target','byte58a','field58a'],['candidate','team','136'],['candidate','team','byte88'],['candidate','byte7d3','2003'],['target','byte7d3','field7d3']] as const) {
  const x=createActorAssociationScanTestFixture(make),owner=role==='target'?x.target:x.candidate;let hit=false;
  run(x,'competing',undefined,(o,k,inner)=>{if(inner&&o===owner&&k===key&&!hit){hit=true;Reflect.set(owner,alias,1);}});check(hit,'late alias injected');
 }
 for(const key of ['team','byte7d3']) {const x=createActorAssociationScanTestFixture(make);run(x,'incomplete',undefined,(o,k,inner)=>{if(inner&&o===x.candidate&&k===key)markIncompleteSourceActorDoubleLifecycle(x.candidate);});if(key==='byte7d3')equal(Reflect.get(x.caller,'byte7d3'),33,'caller store survives candidate closure');}
 {const x=createActorAssociationScanTestFixture(make);let hit=false;run(x,'reentry',(o,k,inner)=>{if(inner&&o===x.target&&k==='byte58a'&&!hit){hit=true;refuses(()=>x.frame.runFrame(),'same-runtime reentry');}});check(hit,'caught reentry reached');}
 {const x=createActorAssociationScanTestFixture(make);run(x,'physical base differs',undefined,(o,k)=>{if(o===x.threshold&&k==='field814')x.actorSlots[0]=x.physicalIdentities[3]!;});}
}
export function runActorAssociationScanSelfTests(make:Make):void {
 let count=0;const counted:Make=omit=>{count++;return make(omit);};branchTests(counted);captureTests(counted);faultTests(counted);
 console.log(`[actor-association-scan] PASS (${count} genuine shared-graph fixtures): fresh physical inner scan, lazy masks/teams, first-match sequential flags, captured values, role aliases and partial failure closure; still absent27764 row38 after the third RNG draw, no completed frame or browser claim`);
}
