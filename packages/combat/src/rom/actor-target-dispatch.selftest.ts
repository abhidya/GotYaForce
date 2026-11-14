import {createSourceActorTargetDispatchRuntime,isSourceActorTargetDispatchRuntime,
  type SourceActorTargetDispatchSources} from './actor-target-dispatch.js';
import {createSourceActorSlotStatusRuntime,type SourceActorPlayerSlotRecord,type SourceActorSlotStatusSources} from './actor-slot-status.js';
import {createSourceObjectSchedulerRuntime,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit synthetic current cells on the genuine scheduler/spawn/admission
 * graph. Neither source constructors nor ordinary fixtures hydrate502 or the
 * dispatch word. Calls and return values remain the real bounded runtimes.
 * Descriptor observation injects faults; it never replaces a source callee. */
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[actor-target-dispatch-test] ${why}`);}
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
function setup(make: Make) {
  const x=make(),scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources);
  const slotRecords: Record<number,SourceActorPlayerSlotRecord>={0:{state18:0}};
  const dispatch3938: Record<number,number>={0:0x800105ac};
  const slotStatusSources: SourceActorSlotStatusSources={scheduler,slotRecords,dispatch3938};
  const slotStatus=createSourceActorSlotStatusRuntime(slotStatusSources);
  x.actionRequestSources.slotStatus=slotStatus;
  Object.assign(x.sourceActor,{byte43d:10,byte502:0,slot:0,housekeeping73f:1,inputEdge5d4:0});
  x.targetAction.byte7d2=0;x.targetAction.byte73c=0;x.header.mode4a1=0;
  const dispatch39a0: Record<number,number>={0:0x8006b850};
  const targetDispatchSources: SourceActorTargetDispatchSources={scheduler,dispatch39a0};
  const targetDispatch=createSourceActorTargetDispatchRuntime(targetDispatchSources);
  const targetPreparation=Object.assign(x.targetPreparation,{slotStatus,targetDispatch});
  return Object.assign(x,{scheduler,slotStatus,slotStatusSources,slotRecords,dispatch3938,dispatch39a0,
    targetDispatchSources,targetDispatch,targetPreparation});
}
type Joined=ReturnType<typeof setup>;
function outer(x: Joined) {
  const sources: SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  return {sources,frame:createSourceBattleOuterFrameRuntime(sources)};
}
function noSchedulerWork(x: Joined,run: ()=>void): void {
  const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);let reads=0;
  observe(run,(owner,key)=>{
    if(owner===x.groups || owner===x.objectBytes || owner===x.nextObjectBytes ||
      (owner===x.matchGlobals && ['maskD1','maskD2'].includes(String(key)))) reads++;
  });
  equal(reads,0,'target dispatch never executes scheduler masks, groups or object snapshots');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'helper creates no actor-frame epoch or claim');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function closed(x: Joined,frame: ReturnType<typeof outer>['frame']): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'outer refusal permanently closes genuine actor');
  rejects(()=>frame.runFrame(),'permanently incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)])
    rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
}
function inactive(x: Joined): void {
  x.sourceActor.active0=0;x.sourceActor.byte502=211;
  x.admissionState.pointer508=x.visibility[0]!;x.admissionState.pointer504=x.visibility[1]!;
}
function clearPlan(x: Joined): {owner: object;key: string;initial: unknown}[] {
  return [{owner:x.sourceActor,key:'byte502',initial:211},
    {owner:x.admissionState,key:'pointer508',initial:x.visibility[0]!},
    {owner:x.admissionState,key:'pointer504',initial:x.visibility[1]!}];
}
function prefix(x: Joined,count: number,why: string): void {
  clearPlan(x).forEach(({owner,key,initial},index)=>
    equal(Reflect.get(owner,key),index<count?(index===0?0:null):initial,`${why}: ${key}`));
}

function helperTests(make: Make): void {
  {
    const old=make(),scheduler=createSourceObjectSchedulerRuntime(old.schedulerSources);
    check(!Object.hasOwn(old.sourceActor,'byte502'),'ordinary fixture has no invented502');
    check(!Object.hasOwn(old.targetPreparation,'targetDispatch'),'ordinary target ingress stays absent');
    const helper=createSourceActorTargetDispatchRuntime({scheduler});old.sourceActor.active0=0;
    check(!Object.hasOwn(old.sourceActor,'byte502'),'helper construction never creates502');
    rejects(()=>helper.dispatchActor(old.actor),'byte502: own data');
    check(!Object.hasOwn(old.sourceActor,'byte502'),'missing reached destination is not synthesized');
  }
  {
    const x=setup(make);
    equal(x.targetDispatch.getSchedulerRuntime(),x.scheduler,'exact scheduler owner');
    equal(x.scheduler.getRootRuntime().getSpawnRuntime().getAdmissionRuntime(),x.commandAdmission,'same spawn-retained admission');
    equal(x.commandAdmission.getActorBinding(x.actor),x.admissionState,'same canonical504/508 owner');
    equal(x.commandAdmission.getActualActor(x.actor),x.sourceActor,'same actual502 owner');
    check(Object.isFrozen(x.targetDispatch) && isSourceActorTargetDispatchRuntime(x.targetDispatch),'genuine frozen dispatch helper');
    for(const fake of [{...x.targetDispatch},Object.create(x.targetDispatch),{},null,undefined])
      check(!isSourceActorTargetDispatchRuntime(fake),'brand cannot be copied or inherited');
    rejects(()=>createSourceActorTargetDispatchRuntime({scheduler:x.scheduler}),'already');
    rejects(()=>createSourceActorTargetDispatchRuntime({scheduler:{...x.scheduler}}),'genuine scheduler');
    const initial=x.targetDispatch.getRetainedStorageOwners();
    check(Object.isFrozen(initial) && initial.includes(x.targetDispatchSources) && !initial.includes(x.dispatch39a0),
      'construction retains direct sources but never eagerly reads the table');
    noSchedulerWork(x,()=>equal(x.targetDispatch.dispatchActor(x.actor),undefined,'genuine active nonzero73f return'));
    const owners=x.targetDispatch.getRetainedStorageOwners();
    check(Object.isFrozen(owners) && owners.includes(x.targetDispatchSources) && owners.includes(x.dispatch39a0),
      'reached table retained by exact identity');
    check(!owners.includes(x.scheduler) && !owners.includes(x.sourceActor) && !owners.includes(x.admissionState),
      'direct inventory never recursively absorbs scheduler, actor or admission owners');
  }
  {
    const x=setup(make);
    for(let raw=0;raw<256;raw++) {
      x.sourceActor.active0=raw;x.sourceActor.byte502=0;
      x.admissionState.pointer504=x.visibility[1]!;x.admissionState.pointer508=x.visibility[0]!;
      x.targetDispatch.dispatchActor(x.actor);
      equal(x.sourceActor.byte502,0,`raw active${raw} retains or clears0`);
      equal(x.admissionState.pointer508,raw===0?null:x.visibility[0],`all256 active bytes508 ${raw}`);
      equal(x.admissionState.pointer504,raw===0?null:x.visibility[1],`all256 active bytes504 ${raw}`);
    }
  }
  for(let raw=0;raw<256;raw++) {
    const x=setup(make);x.sourceActor.byte502=raw;let tableReads=0,housekeepingReads=0;
    observe(()=>{
      if(raw===0) x.targetDispatch.dispatchActor(x.actor);
      else rejects(()=>x.targetDispatch.dispatchActor(x.actor),`signed target index ${raw<128?raw:raw-256}`);
    },(owner,key)=>{
      if(owner===x.targetDispatchSources && key==='dispatch39a0') tableReads++;
      if(owner===x.sourceActor && key==='housekeeping73f') housekeepingReads++;
    });
    equal(tableReads,raw===0?1:0,`signed502 host bound precedes table read for raw${raw}`);
    equal(housekeepingReads,raw===0?1:0,`unadmitted signed502 never enters6b850 for raw${raw}`);
    equal(x.sourceActor.byte502,raw,'active dispatch never normalizes or rewrites raw502');
  }
  {
    const x=setup(make);
    for(let raw=1;raw<256;raw++) {
      x.sourceActor.housekeeping73f=raw;x.targetDispatch.dispatchActor(x.actor);
      equal(x.sourceActor.housekeeping73f,raw,`all nonzero signed/raw73f values return ${raw}`);
    }
    x.sourceActor.housekeeping73f=0;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'candidateGlobals: own data');
  }
  for(const active of [0,1,128,255]) {
    const x=setup(make),events: string[]=[];x.sourceActor.active0=active;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),(owner,key)=>{
      if(owner===x.sourceActor && ['active0','byte502','housekeeping73f'].includes(String(key))) events.push(String(key));
      if(owner===x.admissionState && ['pointer508','pointer504'].includes(String(key))) events.push(String(key));
      if(owner===x.dispatch39a0 && key==='0') events.push('dispatch0');
    });
    equal(events.join(','),active===0?'active0,byte502,pointer508,pointer504':'active0,byte502,dispatch0,housekeeping73f',
      'scalar and destination order exactly follows the selected source branch');
  }
  {
    const x=setup(make);inactive(x);
    Reflect.set(x.sourceActor,'byte502',NaN);Reflect.set(x.admissionState,'pointer508',17);Reflect.set(x.admissionState,'pointer504',Promise.resolve(1));
    Object.defineProperty(x.sourceActor,'housekeeping73f',{get() {throw Error('unreached73f');},configurable:true});
    Object.defineProperty(x.targetDispatchSources,'dispatch39a0',{get() {throw Error('unreached dispatch');},configurable:true});
    noSchedulerWork(x,()=>x.targetDispatch.dispatchActor(x.actor));prefix(x,3,'inactive stores ignore old destination values');
    check(!x.targetDispatch.getRetainedStorageOwners().includes(x.dispatch39a0),'inactive branch never retains dispatch table');
  }
  for(const initial of [0,1]) {
    const x=setup(make);inactive(x);x.sourceActor.active0=initial;x.sourceActor.byte502=0;let changed=false;
    observe(()=>x.targetDispatch.dispatchActor(x.actor),()=>{},(owner,key)=>{
      if(!changed && owner===x.sourceActor && key==='active0') {changed=true;x.sourceActor.active0=initial===0?1:0;}
    });
    check(changed,'active mutation occurs after raw-byte load');
    equal(x.admissionState.pointer508,initial===0?null:x.visibility[0],'branch uses captured active byte, not a later reload');
    equal(x.admissionState.pointer504,initial===0?null:x.visibility[1],'captured inactive byte keeps both ordered pointer clears');
  }
  {
    const x=setup(make);x.targetDispatch.dispatchActor(x.actor);x.dispatch39a0[0]=0x8006b854;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'authenticated');
  }
  for(const key of ['pointer508','pointer504'] as const) {
    const x=setup(make);Object.defineProperty(x.admissionState,key,{writable:false});
    x.targetDispatch.dispatchActor(x.actor);
    equal(x.admissionState[key],null,'active return never preflights inactive-only readonly destination');
  }
  for(const key of ['active0','byte502','housekeeping73f'] as const) for(const value of [-1,256,0.5,NaN,Infinity]) {
    const x=setup(make);Reflect.set(x.sourceActor,key,value);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),`${key}: raw unsigned`);
  }
  for(const key of ['active0','byte502','housekeeping73f'] as const) for(const kind of ['missing','getter'] as const) {
    const x=setup(make);let calls=0;
    if(kind==='missing') Reflect.deleteProperty(x.sourceActor,key);
    else Object.defineProperty(x.sourceActor,key,{get() {calls++;throw Error('scalar getter invoked');},configurable:true});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),`${key}: own data`);equal(calls,0,'reached getters are refused without invocation');
  }
  for(const fault of ['missing-source','getter-source','missing-cell','getter-cell','wrong-word','fraction','negative','overflow','typed-array','promise'] as const) {
    const x=setup(make);let calls=0,housekeepingReads=0;
    if(fault==='missing-source') delete x.targetDispatchSources.dispatch39a0;
    if(fault==='getter-source') Object.defineProperty(x.targetDispatchSources,'dispatch39a0',{get() {calls++;throw Error('table getter');}});
    if(fault==='missing-cell') delete x.dispatch39a0[0];
    if(fault==='getter-cell') Object.defineProperty(x.dispatch39a0,'0',{get() {calls++;throw Error('cell getter');}});
    if(fault==='wrong-word') x.dispatch39a0[0]=0x8006b854;
    if(fault==='fraction') x.dispatch39a0[0]=0.5;
    if(fault==='negative') x.dispatch39a0[0]=-1;
    if(fault==='overflow') x.dispatch39a0[0]=0x100000000;
    if(fault==='typed-array') Reflect.set(x.targetDispatchSources,'dispatch39a0',new Uint32Array([0x8006b850]));
    if(fault==='promise') Reflect.set(x.targetDispatchSources,'dispatch39a0',Promise.resolve(x.dispatch39a0));
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),fault==='wrong-word'?'authenticated':
      ['fraction','negative','overflow'].includes(fault)?'raw unsigned':fault==='typed-array'||fault==='promise'?'own-data record':'own data'),
      (owner,key)=>{if(owner===x.sourceActor && key==='housekeeping73f') housekeepingReads++;});
    equal(calls,0,'invalid dispatch evidence never calls getters');equal(housekeepingReads,0,'callee guard follows valid dispatch evidence');
  }
  {
    const x=setup(make);x.targetDispatch.dispatchActor(x.actor);
    x.targetDispatchSources.dispatch39a0={...x.dispatch39a0};
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'canonical owner changed');
  }
  {
    const x=setup(make),y=setup(make);x.targetDispatch.dispatchActor(x.actor);
    y.targetDispatchSources.dispatch39a0=x.dispatch39a0;
    rejects(()=>y.targetDispatch.dispatchActor(y.actor),'already claimed');
  }
  for(const alias of ['sources','actor','action','admission','world','actor-slots','root-source','slot-row','slot-records','slot-dispatch'] as const) {
    const x=setup(make);
    if(alias.startsWith('slot-')) {x.sourceActor.byte43d=0;x.slotStatus.readSlot(0);}
    const owner=alias==='sources'?x.targetDispatchSources:alias==='actor'?x.sourceActor:alias==='action'?x.targetAction:
      alias==='admission'?x.admissionState:alias==='world'?x.header:alias==='actor-slots'?x.actorSlots:
        alias==='root-source'?x.rootSources:alias==='slot-row'?x.slotRecords[0]:alias==='slot-records'?x.slotRecords:x.dispatch3938;
    Reflect.set(x.targetDispatchSources,'dispatch39a0',owner);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias');
  }
  for(const [location,key] of [['actor','state502'],['actor','field502'],['actor','1282'],['actor','byte508'],
    ['actor','pointer508'],['dispatch','byte502'],['dispatch','pointer504'],['actor','field504'],['actor','byte50A']] as const) {
    const x=setup(make),owner=location==='actor'?x.sourceActor:x.dispatch39a0;let calls=0;
    Object.defineProperty(owner,key,{get() {calls++;throw Error('shadow getter invoked');},configurable:true});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'competing');equal(calls,0,'shadow aliases refused by descriptor presence');
  }
  {
    const x=setup(make),y=setup(make);x.targetDispatchSources.scheduler=y.scheduler;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'canonical scheduler');
  }
  for(const kind of ['foreign','external','interior'] as const) {
    const x=setup(make),id=kind==='interior'?x.allocator.getInteriorPointer(x.actor,4):Symbol(kind);
    if(kind==='external') x.allocator.registerExternal(id,{active0:1,byte502:0,housekeeping73f:1});
    rejects(()=>x.targetDispatch.dispatchActor(id),'unknown');
  }
}

function candidates(x: Joined,half=0) {
  const globals={half80436242:half,count804361a0:91};
  x.sourceActor.housekeeping73f=0;x.targetDispatchSources.candidateGlobals=globals;return globals;
}
function candidateTests(make: Make): void {
  {
    const x=setup(make),globals=candidates(x),events: string[]=[];
    Reflect.set(globals,'count804361a0',NaN);
    observe(()=>noSchedulerWork(x,()=>x.targetDispatch.dispatchActor(x.actor)),(owner,key)=>{
      if(owner===x.sourceActor && key==='housekeeping73f') events.push('73f');
      if(owner===globals && ['half80436242','count804361a0'].includes(String(key))) events.push(String(key));
    });
    equal(events.join(','),'73f,half80436242,count804361a0,count804361a0',
      'zero73f loads half before scratch destination then freshly reloads scratch count');
    equal(globals.count804361a0,0,'scratch reset does not validate its old word');
    check(x.targetDispatch.getRetainedStorageOwners().includes(globals),'reached candidate globals retained by identity');
    equal(x.sourceActor.byte502,0,'zero-candidate return never changes state');
    equal(x.admissionState.pointer508,null,'zero-candidate return never invents a target');
  }
  for(const half of [1,2,255,256,32767,32768,65535]) {
    const x=setup(make),globals=candidates(x,half);let countAccesses=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'candidate list803c1d7c load'),(owner,key)=>{
      if(owner===globals && key==='count804361a0') countAccesses++;
    });
    equal(globals.count804361a0,0,`unsigned candidate half${half} retains scratch reset before refusal`);
    equal(countAccesses,1,'nonzero original half refuses before final scratch reload');
    equal(globals.half80436242,half,'candidate count input is never rewritten');
  }
  for(const value of [-1,65536,0.5,NaN,Infinity]) {
    const x=setup(make),globals=candidates(x);globals.half80436242=value;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'half80436242: raw unsigned');
    equal(globals.count804361a0,91,'invalid half refuses before scratch store');
  }
  for(const key of ['half80436242','count804361a0'] as const) for(const fault of ['missing','getter','readonly'] as const) {
    const x=setup(make),globals=candidates(x);let calls=0;
    if(fault==='missing') Reflect.deleteProperty(globals,key);
    if(fault==='getter') Object.defineProperty(globals,key,{get() {calls++;throw Error('candidate getter');},configurable:true});
    if(fault==='readonly') Object.defineProperty(globals,key,{writable:false});
    if(key==='half80436242' && fault==='readonly') x.targetDispatch.dispatchActor(x.actor);
    else rejects(()=>x.targetDispatch.dispatchActor(x.actor),`${key}: ${fault==='readonly'?'non-writable':'own data'}`);
    equal(calls,0,'candidate getters never invoked');
    if(key==='half80436242' && fault!=='readonly') equal(globals.count804361a0,91,'half read fault preserves scratch');
  }
  for(const initial of [0,1]) {
    const x=setup(make),globals=candidates(x,initial);let changed=false;
    observe(()=>{
      if(initial===0) x.targetDispatch.dispatchActor(x.actor);
      else rejects(()=>x.targetDispatch.dispatchActor(x.actor),'candidate list803c1d7c load');
    },()=>{},(owner,key)=>{
      if(!changed && owner===globals && key==='half80436242') {changed=true;globals.half80436242=initial===0?1:0;}
    });
    check(changed,'half mutation injected after source descriptor capture');
    equal(globals.count804361a0,0,'branch uses originally loaded half despite later live mutation');
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make),globals=candidates(x);let countAccesses=0;
    const change=(owner: object,key: PropertyKey): void=>{
      if(owner===globals && key==='count804361a0' && ++countAccesses===2) globals.count804361a0=7;
    };
    observe(()=>{
      if(phase==='before') rejects(()=>x.targetDispatch.dispatchActor(x.actor),'candidate-positive source path');
      else x.targetDispatch.dispatchActor(x.actor);
    },phase==='before'?change:()=>{},phase==='after'?change:undefined);
    equal(countAccesses,2,'source reloads scratch exactly once after reset');
    equal(globals.count804361a0,7,'fresh scratch read never manufactures another reset');
  }
  {
    const x=setup(make);let calls=0;
    Object.defineProperty(x.targetDispatchSources,'candidateGlobals',{get() {calls++;throw Error('unreached globals');}});
    x.targetDispatch.dispatchActor(x.actor);equal(calls,0,'nonzero73f never loads candidate globals');
  }
  for(const kind of ['missing','getter','promise','typed-array'] as const) {
    const x=setup(make);x.sourceActor.housekeeping73f=0;let calls=0;
    if(kind==='getter') Object.defineProperty(x.targetDispatchSources,'candidateGlobals',{get() {calls++;throw Error('globals getter');}});
    if(kind==='promise') Reflect.set(x.targetDispatchSources,'candidateGlobals',Promise.resolve({}));
    if(kind==='typed-array') Reflect.set(x.targetDispatchSources,'candidateGlobals',new Uint16Array(2));
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),kind==='promise'||kind==='typed-array'?'own-data record':'own data');
    equal(calls,0,'candidate owner getters never invoked');
  }
  {
    const x=setup(make),globals=candidates(x);x.targetDispatch.dispatchActor(x.actor);
    x.targetDispatchSources.candidateGlobals={...globals};
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'canonical owner changed');
  }
  {
    const x=setup(make),y=setup(make),globals=candidates(x);candidates(y);x.targetDispatch.dispatchActor(x.actor);
    y.targetDispatchSources.candidateGlobals=globals;
    rejects(()=>y.targetDispatch.dispatchActor(y.actor),'already claimed');
  }
  for(const ownerName of ['sources','dispatch','actor','binding','world','slot-records'] as const) {
    const x=setup(make);candidates(x);x.slotStatus.readSlot(0);
    const owner=ownerName==='sources'?x.targetDispatchSources:ownerName==='dispatch'?x.dispatch39a0:
      ownerName==='actor'?x.sourceActor:ownerName==='binding'?x.admissionState:ownerName==='world'?x.header:x.slotRecords;
    Reflect.set(x.targetDispatchSources,'candidateGlobals',owner);
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'alias');
  }
  for(const key of ['byte80436242','word80436242'] as const) {
    const x=setup(make),globals=candidates(x);let calls=0;
    Object.defineProperty(globals,key,{get() {calls++;throw Error('shadow candidate getter');}});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'competing');equal(calls,0,'candidate half aliases reject by presence');
  }
  for(const point of ['half','store','reload'] as const) {
    const x=setup(make),globals=candidates(x);let countAccesses=0,entered=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'caught same-runtime reentry'),(owner,key)=>{
      if(owner===globals && key==='count804361a0') countAccesses++;
      const hit=owner===globals && (point==='half'?key==='half80436242':key==='count804361a0'&&countAccesses===(point==='store'?1:2));
      if(hit&&!entered) {entered=true;rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');}
    });
    check(entered,`candidate ${point} reentry reached`);
    equal(globals.count804361a0,point==='reload'?0:91,'caught candidate reentry preserves completed scratch reset only');
  }
  for(const point of ['half','store','reload'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make),globals=candidates(x);Reflect.deleteProperty(x.targetPreparation,'slotStatus');
    const {frame}=outer(x);let countAccesses=0,injected=false;
    const inject=(owner: object,key: PropertyKey): void=>{
      if(owner===globals && key==='count804361a0') countAccesses++;
      const hit=owner===globals && (point==='half'?key==='half80436242':key==='count804361a0'&&countAccesses===(point==='store'?1:2));
      if(hit&&!injected) {injected=true;rejects(()=>frame.runFrame(),'mandatory8006b450');}
    };
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(injected,`${phase} candidate ${point} closure reached`);
    equal(globals.count804361a0,point==='reload'?0:91,'late closure prevents later scratch write');closed(x,frame);
  }
}

/** Optional helper sources can be declared before their first reached call.
 * Their records must remain distinct both now and after later source changes. */
function lateOwnerTests(make: Make): void {
  {
    const x=setup(make),globals=candidates(x);x.slotRecords[0]=Object.assign(globals,{state18:0});
    check(!x.slotStatus.getRetainedStorageOwners().includes(globals),'candidate alias is a declared but unreached slot row');
    let states=0,halves=0,scratch=0;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'candidateGlobals: source storage alias'),(owner,key)=>{
      if(owner===globals && key==='state18') states++;
      if(owner===globals && key==='half80436242') halves++;
      if(owner===globals && key==='count804361a0') scratch++;
    });
    equal(states,0,'declared reference admission never reads slot-state scalar');
    equal(halves,0,'unreached slot-row alias refuses before candidate half read');
    equal(scratch,0,'unreached slot-row alias refuses before scratch destination preflight');
    equal(globals.count804361a0,91,'declared slot-row alias cannot receive candidate scratch reset');
  }
  for(const claimed of ['dispatch','globals'] as const) for(const late of ['records','row','dispatch'] as const) {
    const x=setup(make),owner=claimed==='globals'?candidates(x):x.dispatch39a0;
    x.targetDispatch.dispatchActor(x.actor);
    check(x.targetDispatch.getRetainedStorageOwners().includes(owner),'target successfully claims data before future slot-source mutation');
    check(!x.slotStatus.getRetainedStorageOwners().includes(x.slotRecords),'slot records remain unreached before future alias');
    if(late==='records') Reflect.set(x.slotStatusSources,'slotRecords',owner);
    if(late==='row') Reflect.set(x.slotRecords,'0',owner);
    if(late==='dispatch') {x.sourceActor.byte43d=0;Reflect.set(x.slotStatusSources,'dispatch3938',owner);}
    rejects(()=>x.slotStatus.readSlot(0),`${late==='records'?'slotRecords':late==='row'?'slotRecord0':'dispatch3938'}: storage already claimed`);
    if(claimed==='globals') equal(Reflect.get(owner,'count804361a0'),0,'future slot alias leaves previously reset candidate scratch unchanged');
  }
  for(const claimed of ['dispatch','globals'] as const) {
    const x=setup(make),owner=claimed==='globals'?candidates(x):x.dispatch39a0;
    x.targetDispatch.dispatchActor(x.actor);
    Reflect.set(x.schedulerSources,'actorSlots',owner);
    rejects(()=>x.scheduler.getActorSlotTable(),'actor slots source storage already claimed');
  }
}

function faultTests(make: Make): void {
  for(let fault=0;fault<3;fault++) {
    const x=setup(make);inactive(x);const store=clearPlan(x)[fault]!;
    Object.defineProperty(store.owner,store.key,{writable:false});
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),`${store.key}: non-writable`);prefix(x,fault,'readonly failure preserves exact clear prefix');
    check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failed direct clear permanently closes actual actor');
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
    rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
  }
  {
    const x=setup(make);inactive(x);delete x.sourceActor.byte502;
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'byte502: own data');
    equal(x.admissionState.pointer508,x.visibility[0],'missing502 blocks later508 store');
    equal(x.admissionState.pointer504,x.visibility[1],'missing502 blocks later504 store');
  }
  {
    const x=setup(()=>make('pointer508'));x.sourceActor.active0=0;x.sourceActor.byte502=211;
    x.admissionState.pointer504=x.visibility[1]!;
    check(!Object.hasOwn(x.admissionState,'pointer508'),'missing508 fixture uses truly absent sealed canonical cell');
    rejects(()=>x.targetDispatch.dispatchActor(x.actor),'pointer508: own data');
    equal(x.sourceActor.byte502,0,'missing508 retains earlier502 clear');
    equal(x.admissionState.pointer504,x.visibility[1],'missing508 stops before504');
    check(!Object.hasOwn(x.admissionState,'pointer508'),'missing pointer destination is never manufactured');
  }
  for(const location of ['active','state','dispatch','housekeeping','store502','store508','store504'] as const) {
    const x=setup(make);if(location.startsWith('store')) inactive(x);let entered=false;
    observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'caught same-runtime reentry'),(owner,key)=>{
      const reached=location==='active'?owner===x.sourceActor&&key==='active0':
        location==='state'||location==='store502'?owner===x.sourceActor&&key==='byte502':
          location==='dispatch'?owner===x.dispatch39a0&&key==='0':
            location==='housekeeping'?owner===x.sourceActor&&key==='housekeeping73f':
              owner===x.admissionState&&key===(location==='store508'?'pointer508':'pointer504');
      if(reached&&!entered) {entered=true;rejects(()=>x.targetDispatch.dispatchActor(x.actor),'same-runtime reentry');}
    });
    check(entered,`caught helper reentry reaches ${location}`);
    if(location.startsWith('store')) prefix(x,location==='store502'?0:location==='store508'?1:2,'caught reentry retains only completed stores');
  }
}

/** The850 helper may return, but the mandatory same-actor af8c source
 * continuation is still unavailable. No later pass may absorb that return. */
function continuationProbe(x: Joined) {
  let selected=false,pointer508=0,physicalReloads=0,nextIdentity=0,nextActive=0;
  return {
    visit(owner: object,key: PropertyKey): void {
      if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
      if(!selected) return;
      if(owner===x.admissionState&&key==='pointer508') pointer508++;
      if(owner===x.massPreparation&&key==='physicalBlock') physicalReloads++;
      if(owner===x.physicalIdentities&&key==='1') nextIdentity++;
      if(owner===x.slotTargets[1]&&key==='active0') nextActive++;
    },
    assert(helper508Stores: number): void {
      check(selected,'outer reached the genuine target dispatcher');
      equal(pointer508,helper508Stores,'only helper508 stores occur, never the unsupported af8c or later pointer reload');
      equal(physicalReloads,0,'returned helper never reaches the third-pass physical-block reload');
      equal(nextIdentity,0,'returned helper never advances to the next second-pass physical identity');
      equal(nextActive,0,'returned helper never reads the next second-pass actor active byte');
    },
  };
}

function outerTests(make: Make): void {
  {
    const x=setup(make),{frame}=outer(x),probe=continuationProbe(x);let target=false,actionHousekeeping=0,dispatchHousekeeping=0;
    noSchedulerWork(x,()=>observe(()=>rejects(()=>frame.runFrame(),'8006af8c'),(owner,key)=>{
      probe.visit(owner,key);
      if(owner===x.targetPreparation && key==='targetDispatch') target=true;
      if(owner===x.sourceActor && key==='housekeeping73f') {if(target) dispatchHousekeeping++;else actionHousekeeping++;}
    }));
    equal(actionHousekeeping,1,'outer first executes real prepareTarget73f return');
    equal(dispatchHousekeeping,1,'outer then executes genuine6b85073f return');probe.assert(0);
    equal(x.sourceActor.byte502,0,'active dispatcher does not mutate502');
    equal(x.massPreparation.orderCount.count80436260,6,'new dispatcher follows whole mass ordering');
    equal(x.massHost.sourceArrowMass204,1200,'new dispatcher retains mass update');
    for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const)
      equal(x.sourceActor[key],0,'new dispatcher retains earlier genuine target clear');
    closed(x,frame);
  }
  {
    const x=setup(make),{frame}=outer(x),probe=continuationProbe(x);let selected=false,tableReads=0;
    x.sourceActor.byte502=211;x.admissionState.pointer508=x.visibility[0]!;x.admissionState.pointer504=x.visibility[1]!;
    observe(()=>rejects(()=>frame.runFrame(),'8006af8c'),(owner,key)=>{
      probe.visit(owner,key);
      if(!selected && owner===x.targetPreparation && key==='targetDispatch') {selected=true;x.sourceActor.active0=0;}
      if(owner===x.targetDispatchSources && key==='dispatch39a0') tableReads++;
    });
    check(selected,'live active change occurs after real action target return');prefix(x,3,'outer selects live inactive dispatcher');
    equal(tableReads,0,'outer inactive dispatcher never loads table evidence');probe.assert(1);closed(x,frame);
  }
  {
    const x=setup(make);x.sourceActor.housekeeping73f=0;const {frame}=outer(x);
    rejects(()=>frame.runFrame(),'candidateGlobals: own data');closed(x,frame);
  }
  for(const half of [0,1,65535]) {
    const x=setup(make),globals=candidates(x,half),{frame}=outer(x),probe=continuationProbe(x);
    observe(()=>rejects(()=>frame.runFrame(),half===0?'8006af8c':'candidate list803c1d7c load'),probe.visit);
    probe.assert(0);
    equal(globals.count804361a0,0,'outer preserves genuine candidate scratch reset before later refusal');closed(x,frame);
  }
  for(const fault of ['missing','copied','foreign'] as const) {
    const x=setup(make),other=fault==='foreign'?setup(make):undefined;
    if(fault==='missing') Reflect.deleteProperty(x.targetPreparation,'targetDispatch');
    if(fault==='copied') x.targetPreparation.targetDispatch={...x.targetDispatch};
    if(other) x.targetPreparation.targetDispatch=other.targetDispatch;
    const {frame}=outer(x);
    rejects(()=>frame.runFrame(),fault==='missing'?'8006b7f4':'target-dispatch');closed(x,frame);
  }
  for(const location of ['active','state','dispatch','housekeeping'] as const) {
    const x=setup(make),{frame}=outer(x);let selected=false,entered=false;
    observe(()=>rejects(()=>frame.runFrame(),'known incomplete source Double lifecycle'),(owner,key)=>{
      if(owner===x.targetPreparation && key==='targetDispatch') selected=true;
      const reached=location==='active'?owner===x.sourceActor&&key==='active0':
        location==='state'?owner===x.sourceActor&&key==='byte502':location==='dispatch'?owner===x.dispatch39a0&&key==='0':
          owner===x.sourceActor&&key==='housekeeping73f';
      if(selected && reached && !entered) {entered=true;rejects(()=>frame.runFrame(),'same-runtime reentry');}
    });
    check(entered,`outer reentry reached dispatch ${location}`);closed(x,frame);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make),globals=candidates(x),{frame}=outer(x);let injected=false,accesses=0;
    const inject=(owner: object,key: PropertyKey): void=>{
      if(owner!==globals || key!=='count804361a0') return;
      accesses++;
      if(!injected) {injected=true;rejects(()=>frame.runFrame(),'same-runtime reentry unsupported');}
    };
    observe(()=>rejects(()=>frame.runFrame(),'incomplete'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(injected,`${phase} scratch preflight reaches caught reentry on the SAME active outer frame`);
    equal(accesses,1,'same-frame reentry prevents both pending scratch store and later reload');
    equal(globals.count804361a0,91,'immediate shared-graph closure blocks the pending scratch store');
    closed(x,frame);
  }
  for(const location of ['active','state','dispatch','housekeeping','store502','store508','store504'] as const)
    for(const phase of ['before','after'] as const) {
      const x=setup(make);if(location.startsWith('store')) inactive(x);
      Reflect.deleteProperty(x.targetPreparation,'slotStatus');const {frame}=outer(x);let injected=false;
      const inject=(owner: object,key: PropertyKey): void=>{
        const reached=location==='active'?owner===x.sourceActor&&key==='active0':
          location==='state'||location==='store502'?owner===x.sourceActor&&key==='byte502':
            location==='dispatch'?owner===x.dispatch39a0&&key==='0':location==='housekeeping'?owner===x.sourceActor&&key==='housekeeping73f':
              owner===x.admissionState&&key===(location==='store508'?'pointer508':'pointer504');
        if(reached&&!injected) {injected=true;rejects(()=>frame.runFrame(),location.startsWith('store')?'unknown':'mandatory8006b450');}
      };
      observe(()=>rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete'),phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
      check(injected,`${phase} ${location} injects real outer closure during direct helper`);
      if(location.startsWith('store')) prefix(x,location==='store502'?0:location==='store508'?1:2,'late closure preserves only prior stores');
      closed(x,frame);
    }
}

export function runActorTargetDispatchSelfTests(make: Make): void {
  helperTests(make);candidateTests(make);lateOwnerTests(make);faultTests(make);outerTests(make);
  console.log('[actor-target-dispatch] PASS: all256 active/state/housekeeping bytes, ordered canonical502/508/504 clears, authenticated signed-index0 dispatch, genuine73f and zero-candidate returns, ordered scratch reset/reload, lazy owner/scalar faults, data aliases and caught reentry, real outer exact6af8c return boundary before further pointer/actor/pass reads and permanent closure; bounded offline synthetic composition only, no source hydration, candidate-list load, scheduler execution or full-frame claim');
}
