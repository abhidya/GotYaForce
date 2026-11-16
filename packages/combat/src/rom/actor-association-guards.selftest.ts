import {captureMissingLeaderIngress} from './battle-leader-ingress.selftest.js';
import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const next='pointer38: own data property required',scan='byte58a: own data property required';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-association-guards-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(f:()=>unknown,part:string):string {let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
function fixture(make:Make,flags=0,callerTeam=0,targetTeam=1,distance=10,limit=20) {
 const x=createActorThirdPassTestFixture(make,{field814:limit}),caller=x.physicalActors[1]!,target=x.physicalActors[2]!;
 Object.assign(caller,{byte7d3:flags,team:callerTeam,horizontalDistance75c:distance});Reflect.set(target,'team',targetTeam);
 x.allocator.bindActor(x.physicalIdentities[2]!,{byte83:0});x.physicalBindings[1]!.pointer508=target;
 const threshold=x.attributes.getActorBinding(x.physicalIdentities[1]!);
 return Object.assign(x,{caller,target,threshold,target83:x.allocator.getActorBinding(x.physicalIdentities[2]!)});
}
type Fixture=ReturnType<typeof fixture>;
function run(x:Fixture,expected=scan,before:Visit=()=>{},after?:Visit) {
 const leaderPrefix=captureMissingLeaderIngress(x);
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];let secondary=false,third=false,physicalLoads=0,inner=0,scheduler=0;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  leaderPrefix.observe(owner,key);
  if(owner===x.sourceActor&&key==='visibilityTarget')secondary=true;
  if(secondary&&owner===x.massPreparation&&key==='physicalBlock'){third=true;physicalLoads++;}
  if(third) {
   if(owner===x.physicalIdentities&&/^[0-5]$/.test(String(key)))events.push('row'+String(key));
   if(owner===x.caller&&key==='active0')Reflect.set(owner,'active0',1);
   if(owner===x.target83&&key==='byte83')events.push('83');
   if(owner===x.caller&&key==='byte7d3')events.push('flags');
   if(owner===x.target&&key==='team')events.push('target-team');
   if(owner===x.caller&&key==='team')events.push('caller-team');
   if(owner===x.caller&&key==='horizontalDistance75c')events.push('distance');
   if(owner===x.threshold&&key==='field814')events.push('threshold');
   if(owner===x.target&&key==='byte58a')inner++;
   if(owner===x.groups&&/^\d+$/.test(String(key))||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))scheduler++;
   before(owner,key);
  }
  const result=native(owner,key);if(third)after?.(owner,key);return result;
 }) as typeof native;
 let message='';try{message=refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 if(expected===next)leaderPrefix.assert();
 check(secondary&&third,'real predecessor source paths reached');equal(physicalLoads,expected===scan?2:1,'fresh inner physical reload only after admitted guards');equal(inner,expected===scan?1:0,'unhydrated target58a stops at its reached load');equal(scheduler,0,'no scheduler field read');
 return {events,message};
}
const prefix=['row0','row1','83'];
const skipped=['row2','row3','row4','row5'];
function expect(x:Fixture,expected:string,fields:string[],skip:boolean,before?:Visit,after?:Visit):void {
 const r=run(x,expected,before,after);equal(r.events.join(','),[...prefix,...fields,...(skip?skipped:[])].join(','),'exact lazy source prefix');retained(x);closed(x);
}
function retained(x:Fixture):void {
 equal(x.massHost.sourceArrowMass204,1200,'prior mass retained');equal(x.massPreparation.orderCount.count80436260,6,'prior ordering retained');equal(x.sourceActor.byte502,0,'genuine zero candidate result retained');equal(x.admissionState.pointer508,null,'primary source null retained');
 for(const key of ['targetDistance758','horizontalDistance75c','targetDistance760','horizontalDistance764'])equal(Reflect.get(x.sourceActor,key),20000,'prior sentinel retained');
 for(const v of [x.vector,x.aim])for(const [i,key]of ['x','y','z'].entries())equal(Reflect.get(v,key),[0,0,20000][i],'prior direction retained');
}
function closed(x:Fixture):void {
 for(const a of x.physicalActors)check(hasIncompleteSourceActorDoubleLifecycle(a),'every retained actor closes');refuses(()=>x.frame.runFrame(),'permanently incomplete');
 for(const f of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])refuses(f,'exclusively owned');refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
const all=['flags','target-team','caller-team','distance','threshold'];
function branchTests(make:Make):void {
 for(const value of [0,1,2,3,127,128,254,255]) {
  const x=fixture(make,value);expect(x,value&1?next:scan,value&1?['flags']:all,!!(value&1));equal(Reflect.get(x.caller,'byte7d3'),value,'flags unchanged');
 }
 for(const [a,b]of [[0,0],[1,1],[128,128],[255,255],[0,255],[128,127],[255,0],[2,3]]) {
  const x=fixture(make,0,a,b);expect(x,a===b?next:scan,a===b?all.slice(0,3):all,a===b);
 }
 for(const [distance,limit]of [[10,20],[20,20],[21,20],[-2,-1],[-1,-2],[0,0],[-0,0],[0,-0],[-0,-0],[2**-149,0],[0,2**-149],[-(2**-149),0],[(2-2**-23)*2**127,(2-2**-23)*2**127]] as const) {
  const x=fixture(make,0,0,1,distance,limit);expect(x,distance>limit?next:scan,all,distance>limit);
  equal(Reflect.get(x.caller,'horizontalDistance75c'),distance,'captured source distance unchanged including signzero');equal(x.threshold.field814,limit,'canonical threshold unchanged');
 }
 {const x=fixture(make,1);let hits=0;Object.defineProperty(x.target,'team',{get(){hits++;throw Error('unreached team');}});expect(x,next,['flags'],true);equal(hits,0,'odd flags skip team getter');}
 {const x=fixture(make,0,128,128);let hits=0;Object.defineProperty(x.caller,'horizontalDistance75c',{get(){hits++;throw Error('unreached distance');}});expect(x,next,all.slice(0,3),true);equal(hits,0,'equal teams skip distance getter');}
 {const x=fixture(make);for(const [owner,key]of [[x.caller,'byte7d3'],[x.caller,'team'],[x.target,'team'],[x.caller,'horizontalDistance75c'],[x.threshold,'field814']] as const)Object.defineProperty(owner,key,{writable:false});expect(x,scan,all,false);}
}
function captureTests(make:Make):void {
 for(const value of [0,1]) {const x=fixture(make,value);expect(x,value?next:scan,value?['flags']:all,!!value,undefined,(owner,key)=>{if(owner===x.caller&&key==='byte7d3')Reflect.set(x.caller,key,value?0:1);});}
 {const x=fixture(make,0,0,0);expect(x,next,all.slice(0,3),true,(owner,key)=>{if(owner===x.caller&&key==='team')Reflect.set(x.target,'team',255);});}
 {const x=fixture(make,0,0,1);expect(x,scan,all,false,undefined,(owner,key)=>{if(owner===x.caller&&key==='team')Reflect.set(x.caller,'team',1);});}
 for(const gt of [false,true]) {
  const x=fixture(make,0,0,1,gt?30:10,20);expect(x,gt?next:scan,all,gt,(owner,key)=>{if(owner===x.threshold&&key==='field814')Reflect.set(x.caller,'horizontalDistance75c',gt?0:100);},(owner,key)=>{if(owner===x.threshold&&key==='field814')x.threshold.field814=gt?100:0;});
 }
 {const x=fixture(make);expect(x,scan,all,false,(owner,key)=>{if(owner===x.caller&&key==='byte7d3'){x.physicalBindings[1]!.pointer508={};Reflect.set(x.caller,'active0',0);x.target83.byte83=255;}});}
}
function faultTests(make:Make):void {
 for(const stage of ['flags','target-team','caller-team','distance','threshold']) {
  const n=all.indexOf(stage),key=stage==='flags'?'byte7d3':stage==='distance'?'horizontalDistance75c':stage==='threshold'?'field814':'team';
  for(const kind of ['undefined','accessor'] as const) {
   if(kind==='accessor'&&stage==='threshold')continue; // sealed canonical cell cannot be redefined.
   const x=fixture(make),owner=stage==='target-team'?x.target:stage==='threshold'?x.threshold:x.caller;let invoked=0;
   if(kind==='undefined')Reflect.set(owner,key,undefined);else Object.defineProperty(owner,key,{get(){invoked++;throw Error('source getter');},configurable:true});
   expect(x,key,all.slice(0,n+1),false);equal(invoked,0,'source accessor never invoked');
  }
 }
 for(const key of ['horizontalDistance75c','field814'])for(const bad of [NaN,Infinity,-Infinity,0.1]) {
  const x=fixture(make);Reflect.set(key==='field814'?x.threshold:x.caller,key,bad);expect(x,'finite exact source float32',all.slice(0,key==='field814'?5:4),false);
 }
 for(const [field,alias]of [['byte7d3','field7d3'],['team','byte88'],['horizontalDistance75c','field75c'],['field814','field814']] as const) {
  const x=fixture(make),owner=field==='field814'?x.threshold:field==='team'?x.target:x.caller;let hit=false;
  const n=field==='byte7d3'?0:field==='team'?1:field==='horizontalDistance75c'?3:4;
  expect(x,'competing',all.slice(0,n+1),false,(value,key)=>{if(value===owner&&key===field){hit=true;Reflect.set(field==='team'?x.target:x.caller,alias,1);}});check(hit,'late source alias injected');
 }
 for(const at of ['byte7d3','team','horizontalDistance75c','field814'])for(const who of ['caller','target']) {
  const x=fixture(make),owner=at==='field814'?x.threshold:at==='team'?x.target:x.caller;let hit=false;
  const n=at==='byte7d3'?0:at==='team'?1:at==='horizontalDistance75c'?3:4;
  expect(x,'incomplete',all.slice(0,n+1),false,(value,key)=>{if(value===owner&&key===at){hit=true;markIncompleteSourceActorDoubleLifecycle(who==='caller'?x.caller:x.target);}});check(hit,'late independent closure injected');
 }
 {const x=fixture(make);let hit=false;expect(x,'reentry',all,false,(owner,key)=>{if(owner===x.threshold&&key==='field814'){hit=true;refuses(()=>x.frame.runFrame(),'same-runtime reentry');}});check(hit,'caught reentry before comparison');}
 {const x=fixture(make);let hit=false;expect(x,'canonical814',all,false,(owner,key)=>{if(owner===x.threshold&&key==='field814'){hit=true;Reflect.set(x.massPreparation,'attributes',{});}});check(hit,'late attribute runtime replacement rejected');}
}
function terminalMetadataTests(make:Make):void {
 for(const kind of ['target','caller','attributes','flags','team','distance','threshold','target83','caller508','numeric-flags','numeric-team','numeric-distance','numeric-threshold']) {
  const x=fixture(make);let reached=false,checks=0,hits=0;
  const expected=kind==='target'||kind==='caller'?'incomplete':kind==='attributes'?'canonical814':'competing';
  expect(x,expected,all,false,undefined,(owner,key)=>{
   if(owner===x.threshold&&key==='field814')reached=true;
   if(reached&&owner===x.target83&&key==='131'&&++checks===2) {
    hits++;
    if(kind==='target'||kind==='caller')markIncompleteSourceActorDoubleLifecycle(kind==='target'?x.target:x.caller);
    else if(kind==='attributes')Reflect.set(x.massPreparation,'attributes',{});
    else {
     const alias:Record<string,string>={flags:'field7d3',team:'byte88',distance:'field75c',threshold:'field814',target83:'eligibility83',caller508:'field508','numeric-flags':'2003','numeric-team':'136','numeric-distance':'1884','numeric-threshold':'2068'};
     Reflect.set(kind==='team'||kind==='target83'||kind==='numeric-team'?x.target:x.caller,alias[kind]!,1);
    }
   }
  });
  equal(hits,1,'fault injected once at final observable metadata check');equal(checks,2,'terminal native checks do not repeat observable descriptor walk');
 }
}
export function runActorAssociationGuardsSelfTests(make:Make):void {
 let count=0;const counted:Make=omit=>{count++;return make(omit);};branchTests(counted);captureTests(counted);faultTests(counted);terminalMetadataTests(counted);
 console.log(`[actor-association-guards] PASS (${count} genuine shared-graph fixtures): caller7d3 bit0, ordered signed teams, canonical75c/attribute814 finite GT-only gate, captured loads, lazy faults and permanent closure; stops at missing target58a or absent27764 row38 after the third RNG draw, no unordered/FPSCR execution, association writes, completed outer frame or browser claim`);
}
