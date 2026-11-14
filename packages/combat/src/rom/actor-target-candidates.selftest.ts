import {createSourceActorTargetDispatchRuntime,type SourceActorTargetDispatchSources} from './actor-target-dispatch.js';
import {createSourceActorSlotStatusRuntime,type SourceActorPlayerSlotRecord,type SourceActorSlotStatusSources} from './actor-slot-status.js';
import {createSourceObjectSchedulerRuntime,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit synthetic candidate words on the existing genuine world and allocator.
 * No scheduler/root/stage method or target-selector result is substituted. The
 * first surviving candidate still stops before the unsupported descriptor4b0. */
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[actor-target-candidates-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);return message;
}
function observe(run: ()=>void,before: (owner: object,key: PropertyKey)=>void,
  after?: (owner: object,key: PropertyKey)=>void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function setup(make: Make,half=1) {
  const x=make(),scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources);
  const slotRecords: Record<number,SourceActorPlayerSlotRecord>={0:{state18:0}};
  const dispatch3938: Record<number,number>={0:0x800105ac};
  const slotStatusSources: SourceActorSlotStatusSources={scheduler,slotRecords,dispatch3938};
  const slotStatus=createSourceActorSlotStatusRuntime(slotStatusSources);
  x.actionRequestSources.slotStatus=slotStatus;
  Object.assign(x.sourceActor,{byte43d:10,byte502:0,slot:0,housekeeping73f:0,inputEdge5d4:0});
  x.targetAction.byte7d2=0;x.targetAction.byte73c=0;x.header.mode4a1=0;
  const dispatch39a0: Record<number,number>={0:0x8006b850};
  const globals={half80436242:half,count804361a0:91};
  const list: Record<number,symbol|null>={0:null},scratch: Record<number,symbol|null>={0:null,1:x.actor,7:x.actor};
  const sources: SourceActorTargetDispatchSources={scheduler,dispatch39a0,candidateGlobals:globals,
    candidateList1d7c:list,scratchCandidates2208:scratch};
  const targetDispatch=createSourceActorTargetDispatchRuntime(sources);
  const targetPreparation=Object.assign(x.targetPreparation,{slotStatus,targetDispatch});
  return Object.assign(x,{scheduler,slotStatus,slotStatusSources,slotRecords,dispatch3938,dispatch39a0,
    sources,globals,list,scratch,targetDispatch,targetPreparation});
}
type Joined=ReturnType<typeof setup>;
function candidate(x: Joined,lifecycle: number|null=0) {
  const id=x.target,a=x.targetActor;
  x.dispatch.bindActor(id,{family1d88:null,shared1d8c:null,marker578:0,marker1db3:0});
  x.control.bindActor(id,{activeMask579:0,blockedMask1d9a:0,marker71d:0},Array.from({length:4},()=>
    ({current00:null,next04:null,wait14:0,finished1a:0,event1e:0,group18:0,action19:0,status1d:0,state1b:0,auxiliary1c:0})));
  x.control.bindStartActor(id,{familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:0});
  x.ready.bindActor(id,{familyBank1d78:null,sharedBank1d7c:null,movement6d8:0});
  x.movement.bindActor(id,a,{byte661:0,field66c:0,field670:0});x.attributes.bindActor(id,{});
  Reflect.deleteProperty(a,'invulnTimer');
  const slot=()=>({cell:{cur:0,max:0,refillType:0,refillParam:0,timer:0},mirror776:0});
  x.status.bindActor(id,{hp:1,hitDrainFrames:0,balanceGauge:0,balanceGaugeMax:0,balanceRefillDelay:0,
    downResetDelay:0,comboWindow:0,comboAccum:0,comboRank:0,invincTimer:0,sourceAmmoRefillPauseMask:0},
    {},[slot(),slot(),slot()]);
  for(const key of ['fbPhaseSlots','shotByte1db3','animState']) Reflect.deleteProperty(a,key);
  x.cues.bindActor(id,{});x.stageBounds.bindActor(id,lifecycle===null?{}:{lifecycle18:lifecycle});x.allocator.bindActor(id,{});
  Object.assign(a,{active0:1,team:1});
  x.allocator.writePointer(x.child,0x20,id);x.list[0]=x.child;
  equal(x.allocator.getPointerTarget(id),a,'candidate actual comes from genuine allocator pointer domain');
  equal(x.stageBounds.getActualActor(id),a,'candidate lifecycle belongs to same genuine stage actor');
  equal(x.root.getStageRuntime(),x.stageBounds,'root retains the actual stage owner');
  return x.stageBounds.getActorBinding(id);
}
function outer(x: Joined) {
  const sources: SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  return createSourceBattleOuterFrameRuntime(sources);
}
function closed(x: Joined): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes the actual caller');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
}
function noSchedulerWork(x: Joined,run: ()=>void): void {
  const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);let reads=0;
  observe(run,(owner,key)=>{
    if(owner===x.groups || (owner===x.matchGlobals && ['maskD1','maskD2'].includes(String(key)))) reads++;
  });
  equal(reads,0,'candidate helper never executes scheduler masks or group traversal');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'candidate helper creates no frame claim');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function boundary(x: Joined): void {
  const message=rejects(()=>x.targetDispatch.dispatchActor(x.actor),'8006b924');
  check(message.includes('candidate-positive'),'survivor stops at known candidate-positive boundary');
}

function branchTests(make: Make): void {
  {
    const x=setup(make,0);let calls=0;
    for(const key of ['candidateList1d7c','scratchCandidates2208']) Object.defineProperty(x.sources,key,{
      get() {calls++;throw Error('unreached list owner');},configurable:true});
    x.targetDispatch.dispatchActor(x.actor);equal(calls,0,'zero captured half never reads list or scratch owner');
    const owners=x.targetDispatch.getRetainedStorageOwners();
    check(!owners.includes(x.list)&&!owners.includes(x.scratch),'unreached candidate owners are not retained');
  }
  {
    const x=setup(make,4),events: string[]=[];
    candidate(x,2);x.list[0]=null;x.list[1]=x.nextChild;x.list[2]=x.child;x.list[3]=x.child;
    x.allocator.writePointer(x.nextChild,0x20,null);
    observe(()=>noSchedulerWork(x,()=>x.targetDispatch.dispatchActor(x.actor)),(owner,key)=>{
      if(owner===x.list && /^\d+$/.test(String(key))) events.push(`list${String(key)}`);
      if(owner===x.targetActor && ['active0','team'].includes(String(key))) events.push(`candidate.${String(key)}`);
      if(owner===x.sourceActor && key==='team') events.push('caller.team');
      if(owner===x.stageBounds.getActorBinding(x.target) && key==='lifecycle18') events.push('lifecycle');
    });
    equal(events.join(','),'list0,list1,list2,candidate.active0,caller.team,candidate.team,lifecycle,list3,candidate.active0,caller.team,candidate.team,lifecycle',
      'null list, null+20, active, caller team, candidate team and lifecycle filters follow source order');
    equal(x.globals.count804361a0,0,'positive input count with all rejected returns genuinely');
    equal(x.scratch[0],null,'rejected candidates never store scratch');equal(x.scratch[7],x.actor,'unused tail stays stale');
  }
  for(const kind of ['list-null','pointer-null','inactive','self','same-team','team-four'] as const) {
    const x=setup(make);let calls=0;
    if(kind!=='list-null') {
      x.list[0]=x.child;
      if(kind==='pointer-null') x.allocator.writePointer(x.child,0x20,null);
      else if(kind==='self') x.allocator.writePointer(x.child,0x20,x.actor);
      else {
        // Earlier filters need only the allocator's genuine pointer ownership,
        // not a fabricated stage binding. Any premature stage lookup must fail.
        x.allocator.bindActor(x.target,{});Object.assign(x.targetActor,{active0:kind==='inactive'?0:1,team:kind==='same-team'?0:4});
        x.allocator.writePointer(x.child,0x20,x.target);
      }
    }
    if(['list-null','pointer-null','inactive','self'].includes(kind))
      Object.defineProperty(x.sourceActor,'team',{get() {calls++;throw Error('unreached caller team');},configurable:true});
    Object.defineProperty(x.sources,'scratchCandidates2208',{get() {calls++;throw Error('unreached scratch');},configurable:true});
    x.targetDispatch.dispatchActor(x.actor);equal(calls,0,`${kind} skips downstream fields and scratch destination`);
    equal(x.globals.count804361a0,0,`${kind} preserves genuine zero scratch return`);
  }
  {
    const x=setup(make);x.allocator.bindActor(x.target,{});x.list[0]=x.child;x.allocator.writePointer(x.child,0x20,x.target);
    x.targetActor.team=x.sourceActor.team;
    for(let raw=1;raw<256;raw++) {
      x.targetActor.active0=raw;let teams=0;
      observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{if(owner===x.targetActor&&key==='team') teams++;});
      equal(teams,1,`nonzero signed active byte ${raw} remains active before equal-team skip`);
    }
    x.targetActor.active0=0;Object.defineProperty(x.targetActor,'team',{get() {throw Error('inactive team read');},configurable:true});
    x.targetDispatch.dispatchActor(x.actor);
  }
  {
    const x=setup(make);x.allocator.bindActor(x.target,{});x.list[0]=x.child;x.allocator.writePointer(x.child,0x20,x.target);x.targetActor.active0=1;
    for(let raw=0;raw<256;raw++) {x.sourceActor.team=raw;x.targetActor.team=raw;x.targetDispatch.dispatchActor(x.actor);}
    equal(x.globals.count804361a0,0,'all256 raw equal teams compare equally after signed conversion without stage access');
  }
  for(const raw of [0,1,2,127,128,129,254,255]) {
    const x=setup(make);candidate(x,raw);const admitted=(raw<<24>>24)<2;
    if(admitted) boundary(x);else x.targetDispatch.dispatchActor(x.actor);
    equal(x.globals.count804361a0,admitted?1:0,`signed lifecycle ${raw} controls append`);
    equal(x.scratch[0],admitted?x.child:null,`lifecycle ${raw} stores original OBJECT pointer, never actual-actor pointer`);
  }
  for(const teams of [[255,128],[128,255],[4,255],[255,4]] as const) {
    const x=setup(make);candidate(x);x.sourceActor.team=teams[0];x.targetActor.team=teams[1];
    if(teams[1]===4) x.targetDispatch.dispatchActor(x.actor);else boundary(x);
    equal(x.globals.count804361a0,teams[1]===4?0:1,'signed high teams remain unequal; only candidate team4 excludes');
  }
  {
    const x=setup(make,3);candidate(x);x.list[1]=x.child;x.list[2]=x.child;x.scratch[2]=null;
    const events: string[]=[];
    observe(()=>boundary(x),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0') events.push(`count${x.globals.count804361a0}`);
      if(owner===x.scratch&&/^\d+$/.test(String(key))) events.push(`scratch${String(key)}=${x.globals.count804361a0}`);
    });
    equal(x.globals.count804361a0,3,'duplicate candidates retained individually');
    for(let i=0;i<3;i++) equal(x.scratch[i],x.child,'duplicate append holds original candidate OBJECT identity');
    equal(events.join(','),'count91,count0,count0,scratch0=1,count1,count1,scratch1=2,count2,count2,scratch2=3,count3',
      'reset, fresh append count read, increment store, pointer destination and final reload are ordered');
    equal(x.scratch[7],x.actor,'append never clears unused stale tail');
    equal(x.sourceActor.byte502,0,'candidate scan never invents target-state outcome');
    equal(x.admissionState.pointer504,null,'candidate scan never chooses a target');closed(x);
  }
}

function freshnessTests(make: Make): void {
  for(const phase of ['before','after'] as const) {
    const x=setup(make);candidate(x,2);let changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(!changed&&owner===x.list&&key==='0') {changed=true;x.list[0]=null;}
    };
    let actives=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(phase==='before') change(owner,key);if(owner===x.targetActor&&key==='active0') actives++;
    },phase==='after'?change:undefined);
    equal(actives,phase==='before'?0:1,'list branch uses value captured by its own current descriptor');
  }
  {
    const x=setup(make,2);candidate(x,2);x.list[1]=x.child;
    const word=x.allocator.readU32(x.child,0x20);let first=true,activeReads=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(owner===x.targetActor&&key==='active0') {
        activeReads++;if(first) {first=false;for(let offset=0x20;offset<0x24;offset++) x.objectBytes[offset]=0;}
      }
    });
    check(word!==0,'registered pointer is encoded by nonzero big-endian allocator bytes');
    equal(activeReads,1,'later duplicate reloads current BE+20 bytes, not a cached decoded pointer');
    equal(x.globals.count804361a0,0,'fresh null+20 skips later candidate');
  }
  {
    const x=setup(make,2);candidate(x,2);x.list[1]=null;let changed=false,actives=0;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{if(owner===x.targetActor&&key==='active0') actives++;},(owner,key)=>{
      if(!changed&&owner===x.list&&key==='0') {changed=true;x.list[1]=x.child;x.globals.half80436242=0;}
    });
    equal(x.globals.count804361a0,0,'captured input half still visits remaining live list word');
    check(changed,'half mutation happened after entry count capture');
    equal(actives,2,'captured half continues through newly supplied second live list word');
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make);candidate(x);let changed=false;
    const change=(owner: object,key: PropertyKey): void=>{
      if(!changed&&owner===x.targetActor&&key==='active0') {changed=true;x.targetActor.active0=0;}
    };
    observe(()=>{if(phase==='before') x.targetDispatch.dispatchActor(x.actor);else boundary(x);},
      phase==='before'?change:()=>{},phase==='after'?change:undefined);
    equal(x.globals.count804361a0,phase==='before'?0:1,'candidate active test uses captured byte, not later mutation');
  }
  {
    const x=setup(make,2);candidate(x);x.list[1]=x.child;x.scratch[3]=null;let appended=false;
    observe(()=>boundary(x),()=>{},(owner,key)=>{
      if(!appended&&owner===x.scratch&&key==='0') {appended=true;x.globals.count804361a0=3;}
    });
    equal(x.scratch[0],x.child,'first append remains despite later count mutation');
    equal(x.scratch[3],x.child,'next candidate reloads count rather than private append cursor');
    equal(x.globals.count804361a0,4,'second increment uses newly read scratch count');
    equal(x.scratch[1],x.actor,'skipped scratch slot is not normalized');
  }

  for(const point of ['caller-team','candidate-team','lifecycle'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make),stage=candidate(x,point==='lifecycle'?2:0);let changed=false;
    const owner=point==='caller-team'?x.sourceActor:point==='candidate-team'?x.targetActor:stage;
    const key=point==='lifecycle'?'lifecycle18':'team';
    const change=(observed: object,property: PropertyKey): void=>{
      if(!changed&&observed===owner&&property===key) {changed=true;Reflect.set(owner,key,point==='candidate-team'?4:1);}
    };
    const admitted=point==='lifecycle'?phase==='before':phase==='after';
    observe(()=>{if(admitted) boundary(x);else x.targetDispatch.dispatchActor(x.actor);},phase==='before'?change:()=>{},phase==='after'?change:undefined);
    check(changed,'filter fault injection observes reached own data cell');
    equal(x.globals.count804361a0,admitted?1:0,`${phase} ${point} mutation respects captured source load`);
  }
  for(const value of [0,7]) {
    const x=setup(make);candidate(x);let accesses=0;
    observe(()=>{if(value===0) x.targetDispatch.dispatchActor(x.actor);else boundary(x);},(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++accesses===4) x.globals.count804361a0=value;
    });
    equal(x.globals.count804361a0,value,'final return decision reloads current scratch count');
    equal(x.scratch[0],x.child,'final count zero does not roll back completed append');
  }
}

function faultTests(make: Make): void {
  for(const location of ['list','scratch'] as const) for(const fault of ['missing','getter','promise','typed-array','null','primitive'] as const) {
    const x=setup(make);if(location==='scratch') candidate(x);let calls=0;
    const key=location==='list'?'candidateList1d7c':'scratchCandidates2208';
    if(fault==='missing') Reflect.deleteProperty(x.sources,key);
    if(fault==='getter') Object.defineProperty(x.sources,key,{get() {calls++;throw Error('source getter invoked');},configurable:true});
    if(fault==='promise') Reflect.set(x.sources,key,Promise.resolve({0:null}));
    if(fault==='typed-array') Reflect.set(x.sources,key,new Uint32Array(1));
    if(fault==='null') Reflect.set(x.sources,key,null);
    if(fault==='primitive') Reflect.set(x.sources,key,7);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='missing'&&location==='list'?'8006b898':
      fault==='getter'||fault==='missing'?'own data':'record');
    equal(calls,0,'source getter never runs');
    equal(x.globals.count804361a0,location==='scratch'?1:0,'source-owner fault preserves only source-ordered completed count stores');
    equal(x.scratch[0],null,'invalid source owner cannot receive pending pointer append');closed(x);
  }
  for(const fault of ['missing','getter','number','object','promise','undefined'] as const) {
    const x=setup(make);let calls=0;
    if(fault==='missing') delete x.list[0];
    if(fault==='getter') Object.defineProperty(x.list,'0',{get() {calls++;throw Error('list getter invoked');},configurable:true});
    if(fault==='number') Reflect.set(x.list,'0',0);
    if(fault==='object') Reflect.set(x.list,'0',{});
    if(fault==='promise') Reflect.set(x.list,'0',Promise.resolve(null));
    if(fault==='undefined') Reflect.set(x.list,'0',undefined);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='missing'||fault==='getter'?'own data':'pointer identity');
    equal(calls,0,'list-word getter never invoked');equal(x.globals.count804361a0,0,'bad list retains reset');
  }
  for(const kind of ['unknown','foreign','descriptor','external','object-interior'] as const) {
    const x=setup(make);let id: symbol;
    if(kind==='unknown') id=Symbol('unknown object');
    else if(kind==='foreign') {const y=setup(make);id=y.child;}
    else if(kind==='descriptor') id=x.descriptor;
    else if(kind==='external') {id=Symbol('external object');x.allocator.registerExternal(id,{active0:0});}
    else id=x.allocator.getInteriorPointer(x.child,4);
    x.list[0]=id;rejects(()=>x.targetDispatch.dispatchActor(x.actor),'object');
    equal(x.globals.count804361a0,0,'non-OBJECT candidate word refuses after reset');
  }
  for(const kind of ['pointer-interior','external-inactive','external-unbound','actor-no-stage'] as const) {
    const x=setup(make);x.list[0]=x.child;let id: symbol;
    if(kind==='pointer-interior') id=x.allocator.getInteriorPointer(x.actor,4);
    else if(kind==='actor-no-stage') {x.allocator.bindActor(x.target,{});Object.assign(x.targetActor,{active0:1,team:1});id=x.target;}
    else {id=Symbol(kind);x.allocator.registerExternal(id,{active0:kind==='external-inactive'?0:1,team:1});}
    x.allocator.writePointer(x.child,0x20,id);
    if(kind==='external-inactive') x.targetDispatch.dispatchActor(x.actor);
    else rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='pointer-interior'?'base identity':'actor');
    equal(x.globals.count804361a0,0,'unqualified actual never appends before its reached stage proof');
  }
  for(const fault of ['missing','getter','invalid-byte','unregistered-word'] as const) {
    const x=setup(make);candidate(x);let calls=0;
    if(fault==='missing') delete x.objectBytes[0x21];
    if(fault==='getter') Object.defineProperty(x.objectBytes,'33',{get() {calls++;throw Error('BE byte getter invoked');},configurable:true});
    if(fault==='invalid-byte') x.objectBytes[0x21]=256;
    if(fault==='unregistered-word') for(let offset=0x20;offset<0x24;offset++) x.objectBytes[offset]=255;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='unregistered-word'?'pointer':fault==='invalid-byte'?'integer':'own data');
    equal(calls,0,'BE bytes admit own data only');equal(x.globals.count804361a0,0,'pointer read fault precedes count increment');
  }
  for(const location of ['active','caller-team','candidate-team','lifecycle'] as const)
    for(const fault of ['missing','getter','negative','overflow','fraction','nan'] as const) {
      const x=setup(make),stage=candidate(x);let calls=0;
      const owner=location==='active'||location==='candidate-team'?x.targetActor:location==='caller-team'?x.sourceActor:stage;
      const key=location==='active'?'active0':location==='lifecycle'?'lifecycle18':'team';
      // Stage bindings are sealed. An explicitly absent lifecycle must use a
      // genuinely omitted bind cell; it cannot be deleted after binding.
      if(location==='lifecycle'&&(fault==='missing'||fault==='getter')) continue;
      if(fault==='missing') Reflect.deleteProperty(owner,key);
      if(fault==='getter') Object.defineProperty(owner,key,{get() {calls++;throw Error('scalar getter invoked');},configurable:true});
      if(fault==='negative') Reflect.set(owner,key,-1);
      if(fault==='overflow') Reflect.set(owner,key,256);
      if(fault==='fraction') Reflect.set(owner,key,0.5);
      if(fault==='nan') Reflect.set(owner,key,NaN);
      rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='missing'||fault==='getter'?'own data':'raw unsigned');
      equal(calls,0,'candidate scalar getters never invoked');equal(x.globals.count804361a0,0,'scalar fault precedes increment');
    }

  {
    const x=setup(make),stage=candidate(x,null);
    check(!Object.hasOwn(stage,'lifecycle18'),'genuine stage binding omits missing lifecycle rather than fabricating it');
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'lifecycle18: own data');
    equal(x.globals.count804361a0,0,'missing sealed lifecycle stops before append');
  }
  {
    const x=setup(make),stage=candidate(x,2);
    for(const [owner,key] of [[x.sourceActor,'team'],[x.targetActor,'active0'],[x.targetActor,'team'],[stage,'lifecycle18']] as const)
      Object.defineProperty(owner,key,{writable:false});
    x.targetDispatch.dispatchActor(x.actor);
    equal(x.globals.count804361a0,0,'readonly filter inputs remain valid because source only reads them');
  }
  for(const fault of ['missing','getter','readonly'] as const) {
    const x=setup(make);candidate(x);let calls=0;
    if(fault==='missing') delete x.scratch[0];
    if(fault==='getter') Object.defineProperty(x.scratch,'0',{get() {calls++;throw Error('scratch getter invoked');},configurable:true});
    if(fault==='readonly') Object.defineProperty(x.scratch,'0',{writable:false});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='readonly'?'non-writable':'own data');
    equal(x.globals.count804361a0,1,'increment commits before failed scratch pointer destination');
    equal(calls,0,'scratch getter is never invoked');equal(x.scratch[1],x.actor,'fault leaves unused tail untouched');closed(x);
  }
  {
    const x=setup(make);candidate(x);Reflect.set(x.scratch,'0',NaN);let descriptors=0;
    observe(()=>boundary(x),(owner,key)=>{if(owner===x.mapping.getActor(x.actor)&&key==='descriptor4b0') descriptors++;});
    equal(descriptors,0,'positive scan boundary precedes descriptor4b0 read');equal(x.scratch[0],x.child,'append ignores malformed previous destination value');
  }
  for(const value of [-1,0.5,NaN,Infinity,0x100000000]) {
    const x=setup(make);candidate(x);let accesses=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'raw unsigned'),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++accesses===2) x.globals.count804361a0=value;
    });
    equal(x.globals.count804361a0,value,'invalid fresh scratch count is not normalized');equal(x.scratch[0],null,'invalid count stops before pointer store');
  }
  for(const fault of ['missing','getter','readonly'] as const) {
    const x=setup(make);candidate(x);let accesses=0,calls=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='readonly'?'non-writable':'own data'),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++accesses===(fault==='readonly'?3:2)) {
        if(fault==='missing') Reflect.deleteProperty(x.globals,key);
        if(fault==='getter') Object.defineProperty(x.globals,key,{get() {calls++;throw Error('count getter');},configurable:true});
        if(fault==='readonly') Object.defineProperty(x.globals,key,{writable:false});
      }
    });
    equal(x.scratch[0],null,'count read or increment preflight fault precedes scratch pointer destination');
    equal(calls,0,'fresh count getter not invoked');
  }
}

function boundTests(make: Make): void {
  {
    const x=setup(make,4096);for(let i=0;i<4096;i++) x.list[i]=null;
    x.targetDispatch.dispatchActor(x.actor);equal(x.globals.count804361a0,0,'exact4096 null visits are admitted');
  }
  {
    const x=setup(make,4097);for(let i=0;i<4096;i++) x.list[i]=null;let calls=0;
    Object.defineProperty(x.list,'4096',{get() {calls++;throw Error('unreached host-bound word');},configurable:true});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'4096');equal(calls,0,'visit host bound refuses before the next list word');
    equal(x.globals.count804361a0,0,'visit bound retains prior source reset');
  }
  {
    const x=setup(make,65535);delete x.list[0];
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'own data');
    equal(x.globals.count804361a0,0,'huge captured half does not eagerly preflight later visit bound');
  }
  for(const count of [4095,4096,0xffffffff]) {
    const x=setup(make);candidate(x);x.scratch[4095]=null;let accesses=0,scratchReads=0;
    observe(()=>{if(count===4095) boundary(x);else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'4096');},(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++accesses===2) x.globals.count804361a0=count;
      if(owner===x.sources&&key==='scratchCandidates2208') scratchReads++;
    });
    equal(x.globals.count804361a0,(count+1)>>>0,'source count+1 store precedes reached scratch-index host bound, including wrap');
    equal(scratchReads,count===4095?1:0,'unadmitted scratch index never reads scratch owner');
    equal(x.scratch[4095],count===4095?x.child:null,'last in-bound scratch destination is admitted');
  }
}

function ownerTests(make: Make): void {
  for(const ownerKey of ['candidateList1d7c','scratchCandidates2208'] as const) {
    const x=setup(make);candidate(x,ownerKey==='candidateList1d7c'?2:0);
    if(ownerKey==='candidateList1d7c') x.targetDispatch.dispatchActor(x.actor);
    else {
      let accesses=0;observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
        if(owner===x.globals&&key==='count804361a0'&&++accesses===4) x.globals.count804361a0=0;
      });
    }
    const owner=ownerKey==='candidateList1d7c'?x.list:x.scratch;
    check(x.targetDispatch.getRetainedStorageOwners().includes(owner),'reached candidate owner retained by exact identity');
    Reflect.set(x.sources,ownerKey,{...owner});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'canonical owner changed');
  }
  for(const location of ['list','scratch'] as const) for(const alias of ['sources','dispatch','globals','other-list','actor','candidate','stage','world','slot-row','slot-records'] as const) {
    const x=setup(make);const stage=candidate(x);
    const owner=alias==='sources'?x.sources:alias==='dispatch'?x.dispatch39a0:alias==='globals'?x.globals:
      alias==='other-list'?(location==='list'?x.scratch:x.list):alias==='actor'?x.sourceActor:
        alias==='candidate'?x.targetActor:alias==='stage'?stage:alias==='world'?x.header:alias==='slot-row'?x.slotRecords[0]!:x.slotRecords;
    Reflect.set(x.sources,location==='list'?'candidateList1d7c':'scratchCandidates2208',owner);
    // The declared scratch source is lazy: candidate-list admission need not
    // inspect an unreached scratch record merely to forbid possible aliases.
    if(location==='list'&&alias==='other-list') {x.scratch[0]=null;x.targetDispatch.dispatchActor(x.actor);continue;}
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),location==='list'&&alias==='stage'?'competing':'alias');
    equal(x.globals.count804361a0,location==='list'?0:1,'owner alias preserves only earlier source count writes');
  }
  for(const location of ['list','scratch'] as const) {
    const x=setup(make),y=setup(make);candidate(x,location==='list'?2:0);candidate(y,location==='list'?2:0);
    if(location==='list') x.targetDispatch.dispatchActor(x.actor);
    else {let reads=0;observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++reads===4) x.globals.count804361a0=0;
    });}
    Reflect.set(y.sources,location==='list'?'candidateList1d7c':'scratchCandidates2208',location==='list'?x.list:x.scratch);
    rejects(()=>y.targetDispatch.dispatchActor(y.actor),'already claimed');
  }
  for(const location of ['list','scratch'] as const) for(const late of ['slot-records','slot-row','slot-dispatch','scheduler-slots'] as const) {
    const x=setup(make);candidate(x,location==='list'?2:0);
    if(location==='list') x.targetDispatch.dispatchActor(x.actor);
    else {let reads=0;observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++reads===4) x.globals.count804361a0=0;
    });}
    const owner=location==='list'?x.list:x.scratch;
    if(late==='scheduler-slots') {
      Reflect.set(x.schedulerSources,'actorSlots',owner);rejects(()=>x.scheduler.getActorSlotTable(),'already claimed');
    } else {
      if(late==='slot-records') Reflect.set(x.slotStatusSources,'slotRecords',owner);
      if(late==='slot-row') Reflect.set(x.slotRecords,'0',owner);
      if(late==='slot-dispatch') {x.sourceActor.byte43d=0;Reflect.set(x.slotStatusSources,'dispatch3938',owner);}
      rejects(()=>x.slotStatus.readSlot(0),'already claimed');
    }
  }
  for(const location of ['globals','list','scratch'] as const) for(const method of ['external','object','descriptor'] as const) {
    const x=setup(make);candidate(x,location==='scratch'?0:2);
    if(location==='scratch') {let reads=0;observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(owner===x.globals&&key==='count804361a0'&&++reads===4) x.globals.count804361a0=0;
    });} else x.targetDispatch.dispatchActor(x.actor);
    const owner=location==='globals'?x.globals:location==='list'?x.list:x.scratch,id=Symbol('late candidate storage alias');
    rejects(()=>{
      if(method==='external') x.allocator.registerExternal(id,owner);
      else if(method==='object') x.allocator.registerObject(id,owner as Record<number,number>);
      else x.allocator.registerDescriptor(id,owner as Record<number,number>);
    },'already claimed');
    rejects(()=>x.allocator.getPointerTarget(id),'unknown');
  }

}

function interruptionTests(make: Make): void {
  for(const point of ['list','pointer-byte','active','caller-team','candidate-team','lifecycle','count-read','count-store','scratch','final-count'] as const)
    for(const phase of ['before','after'] as const) {
      const x=setup(make),stage=candidate(x);let counts=0,entered=false;
      const inject=(owner: object,key: PropertyKey): void=>{
        if(owner===x.globals&&key==='count804361a0') counts++;
        const hit=point==='list'?owner===x.list&&key==='0':point==='pointer-byte'?owner===x.objectBytes&&key==='33':
          point==='active'?owner===x.targetActor&&key==='active0':point==='caller-team'?owner===x.sourceActor&&key==='team':
            point==='candidate-team'?owner===x.targetActor&&key==='team':point==='lifecycle'?owner===stage&&key==='lifecycle18':
              point==='scratch'?owner===x.scratch&&key==='0':owner===x.globals&&key==='count804361a0'&&counts===(point==='count-read'?2:point==='count-store'?3:4);
        if(hit&&!entered) {entered=true;rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');}
      };
      observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'caught same-runtime reentry'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
      check(entered,`${phase} reentry reaches ${point}`);
      equal(x.globals.count804361a0,point==='scratch'||point==='final-count'?1:0,'caught reentry preserves only fully completed scratch count stores');
      equal(x.scratch[0],point==='final-count'?x.child:null,'caught reentry stops pending pointer write');closed(x);
    }
  for(const point of ['list','pointer-byte','active','lifecycle','count-store','scratch','final-count'] as const)
    for(const phase of ['before','after'] as const) {
      const x=setup(make),stage=candidate(x);Reflect.deleteProperty(x.targetPreparation,'slotStatus');const frame=outer(x);
      let counts=0,entered=false;
      const inject=(owner: object,key: PropertyKey): void=>{
        if(owner===x.globals&&key==='count804361a0') counts++;
        const hit=point==='list'?owner===x.list&&key==='0':point==='pointer-byte'?owner===x.objectBytes&&key==='33':
          point==='active'?owner===x.targetActor&&key==='active0':point==='lifecycle'?owner===stage&&key==='lifecycle18':
            point==='scratch'?owner===x.scratch&&key==='0':owner===x.globals&&key==='count804361a0'&&counts===(point==='count-store'?3:4);
        if(hit&&!entered) {entered=true;rejects(()=>frame.runFrame(),point==='pointer-byte'?'same-runtime reentry':'mandatory8006b450');}
      };
      observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),point==='pointer-byte'?'caught same-runtime reentry':'incomplete'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
      check(entered,`${phase} outer failure reaches ${point}`);
      equal(x.globals.count804361a0,point==='scratch'||point==='final-count'?1:0,'outer closure retains completed increment only');
      equal(x.scratch[0],point==='final-count'?x.child:null,'outer closure blocks pending pointer store');
      closed(x);rejects(()=>frame.runFrame(),'permanently incomplete');
    }
}


/** Close the genuine second actor through a failed actual stream operation.
 * This is not a manufactured lifecycle flag or a dispatcher reentry: the
 * independently bound candidate stream catches its own source-byte failure. */
function candidateFailure(x: Joined): ()=>void {
  x.control.bindActualActor(x.target,x.movement);
  equal(x.control.getActualActor(x.target),x.targetActor,'failed stream owns the same genuine candidate actor');
  return ()=>{
    x.control.getActorBinding(x.target).activeMask579=256;
    rejects(()=>x.control.update(x.target,1),'activeMask579');
    check(hasIncompleteSourceActorDoubleLifecycle(x.targetActor),'actual candidate stream failure permanently closes candidate');
  };
}
function candidateClosureTests(make: Make): void {
  for(const filter of ['accepted','inactive','same-team','team-four','lifecycle'] as const) {
    const x=setup(make);candidate(x,filter==='lifecycle'?2:0);const failCandidate=candidateFailure(x);
    if(filter==='inactive') x.targetActor.active0=0;
    if(filter==='same-team') x.targetActor.team=x.sourceActor.team;
    if(filter==='team-four') x.targetActor.team=4;
    failCandidate();check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'candidate failure alone leaves caller complete');
    let activeReads=0,teamReads=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete'),(owner,key)=>{
      if(owner===x.targetActor&&key==='active0') activeReads++;
      if(owner===x.targetActor&&key==='team') teamReads++;
    });
    equal(activeReads,0,`previously failed ${filter} candidate refuses before its active byte`);
    equal(teamReads,0,'closed candidate never reaches team filter');
    equal(x.globals.count804361a0,0,'closed candidate retains completed reset without increment');
    equal(x.scratch[0],null,'closed candidate never appends');closed(x);
  }
  for(const point of ['active','caller-team','candidate-team','lifecycle','count-read','count-store','scratch','final-count'] as const)
    for(const phase of ['before','after'] as const) {
      const x=setup(make),stage=candidate(x),failCandidate=candidateFailure(x);let counts=0,entered=false;
      const inject=(owner: object,key: PropertyKey): void=>{
        if(owner===x.globals&&key==='count804361a0') counts++;
        const hit=point==='active'?owner===x.targetActor&&key==='active0':
          point==='caller-team'?owner===x.sourceActor&&key==='team':point==='candidate-team'?owner===x.targetActor&&key==='team':
            point==='lifecycle'?owner===stage&&key==='lifecycle18':point==='scratch'?owner===x.scratch&&key==='0':
              owner===x.globals&&key==='count804361a0'&&counts===(point==='count-read'?2:point==='count-store'?3:4);
        if(hit&&!entered) {entered=true;failCandidate();}
      };
      observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
      check(entered,`${phase} candidate failure reaches ${point}`);
      equal(x.globals.count804361a0,point==='scratch'||point==='final-count'?1:0,
        'candidate closure retains only already completed count stores');
      equal(x.scratch[0],point==='final-count'?x.child:null,'candidate closure blocks a pending pointer append');
      equal(x.scratch[7],x.actor,'candidate closure leaves unused scratch tail unchanged');closed(x);
    }
  for(const phase of ['before','after'] as const) {
    const x=setup(make,2);candidate(x,2);x.list[1]=null;const failCandidate=candidateFailure(x);let entered=false;
    const inject=(owner: object,key: PropertyKey): void=>{
      if(!entered&&owner===x.list&&key==='1') {entered=true;failCandidate();}
    };
    observe(()=>x.targetDispatch.dispatchActor(x.actor),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(entered,`${phase} next iteration observes candidate closure`);
    equal(x.globals.count804361a0,0,'later null iteration genuinely returns after previous candidate closure');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'previous candidate guard is cleared before next list iteration');
  }
  {
    const x=setup(make);candidate(x,2);const failCandidate=candidateFailure(x);
    x.targetDispatch.dispatchActor(x.actor);failCandidate();x.sourceActor.housekeeping73f=1;
    x.targetDispatch.dispatchActor(x.actor);
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'candidate guard is cleared after a successful helper return');
  }
}

function outerTests(make: Make): void {
  for(const accepted of [false,true]) {
    const x=setup(make),stage=candidate(x,accepted?0:2),frame=outer(x);let selected=false,lifecycle=0,descriptor=0;
    observe(()=>rejects(()=>frame.runFrame(),accepted?'8006b924':'unknown'),(owner,key)=>{
      if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
      if(selected&&owner===stage&&key==='lifecycle18') lifecycle++;
      if(selected&&owner===x.mapping.getActor(x.actor)&&key==='descriptor4b0') descriptor++;
    });
    equal(lifecycle,1,'real outer target dispatcher reaches candidate lifecycle exactly once');
    equal(descriptor,0,'surviving scan stops before caller descriptor4b0');
    equal(x.globals.count804361a0,accepted?1:0,'outer retains candidate count outcome');
    equal(x.scratch[0],accepted?x.child:null,'outer retains only source candidate pointer append');
    equal(x.massPreparation.orderCount.count80436260,6,'candidate scan follows actual complete mass ordering');
    equal(x.massHost.sourceArrowMass204,1200,'candidate scan preserves genuine mass update');
    for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const)
      equal(x.sourceActor[key],0,'candidate scan follows genuine target-preparation clears');
    closed(x);rejects(()=>frame.runFrame(),'permanently incomplete');
    for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(run,'exclusively owned');
    rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
    rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  }
}

export function runActorTargetCandidatesSelfTests(make: Make): void {
  branchTests(make);freshnessTests(make);faultTests(make);boundTests(make);ownerTests(make);interruptionTests(make);candidateClosureTests(make);outerTests(make);
  console.log('[actor-target-candidates] PASS: genuine same-world candidate scan, all255 nonzero active bytes, signed team/lifecycle filters, live BE+20 pointers and duplicate retention, ordered count-before-pointer stores and stale tails, lazy faults and host bounds, owner/alias/reentry and independently failed candidate closure, actual outer rejected-candidate return and exact6b924 stop; explicit synthetic inputs only, no target selection, descriptor continuation or full-frame claim');
}

/** Genuine reusable candidate graph for later source continuation tests. */
export function createActorTargetCandidatesTestFixture(make: Make,half=1,lifecycle=0) {
  const x=setup(make,half);candidate(x,lifecycle);return x;
}
