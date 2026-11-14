import {createSourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import {hasIncompleteSourceActorDoubleLifecycle, isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {createSourceBattleOuterFrameRuntime, type SourceBattleOuterFrameRuntime,
  type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime, requireSourceObjectSchedulerSnapshot,
  type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import type {createBattleMassOrderingTestFixture, createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Bounded composition assertions ordered from authenticated8006ae60.
 * The third loop's assembly loads active0 at6b35c, then508 at6b360, BEFORE
 * testing active0. The decompiler's expression order is not the load order.
 * One genuine actor and five distinct inactive physical rows are explicit
 * synthetic ingress. No six-active hydration, source callee substitute,
 * scheduler execution, successful outer frame or retail fidelity is claimed. */
type Fixture=ReturnType<typeof createBattleTargetPreparationTestFixture>;
type OldFixture=ReturnType<typeof createBattleMassOrderingTestFixture>;
type Make=(omit?: 'byte7d2'|'pointer508')=>Fixture;
const CALLEE='8006b450', OLD='8006ae60';
const ACTUAL_KEYS=['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const;
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[battle-target-preparation-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);return message;
}
/** Reached-descriptor observation and fault injection only. This does not
 * replace any genuine runtime method, binding, source callee or return. */
function observe(run: ()=>void,before: (owner: object,key: PropertyKey)=>void,
  after?: (owner: object,key: PropertyKey)=>void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function setup(x: Fixture) {
  const scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources);
  const sources: SourceBattleOuterFrameSources={scheduler,systemGlobals:x.systemGlobals,massPreparation:x.massPreparation,
    targetPreparation:x.targetPreparation};
  return {scheduler,sources,outer:createSourceBattleOuterFrameRuntime(sources)};
}
function atTarget(sources: SourceBattleOuterFrameSources,action: ()=>void): (owner: object,key: PropertyKey)=>void {
  let done=false;return (owner,key)=>{
    if(!done && owner===sources && key==='targetPreparation') {done=true;action();}
  };
}
function closed(x: Fixture,scheduler: SourceObjectSchedulerRuntime,outer: SourceBattleOuterFrameRuntime): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal closes retained actual actor');
  rejects(()=>outer.runFrame(),'permanently incomplete');
  for(const run of [()=>scheduler.runGroup(9),()=>scheduler.runSlots(8),()=>scheduler.runWrapper(8)])
    rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  rejects(()=>requireSourceObjectSchedulerSnapshot(scheduler,x.allocator,x.child),'private active');
}
function clearPlan(x: Fixture): {owner: object;key: string;initial: number}[] {
  return [
    ...ACTUAL_KEYS.slice(0,4).map((key,index)=>({owner:x.sourceActor,key,initial:91+index})),
    {owner:x.targetAction,key:'byte7d2',initial:95},
    {owner:x.sourceActor,key:'byte7d3',initial:96},
  ];
}
function checkPrefix(x: Fixture,completed: number,why: string): void {
  clearPlan(x).forEach((store,index)=>equal(Reflect.get(store.owner,store.key),index<completed?0:store.initial,`${why} ${store.key}`));
}
function untouchedScheduler(x: Fixture,run: ()=>void): void {
  let reads=0;const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
  observe(run,(owner,key)=>{
    if(owner===x.objectBytes || owner===x.nextObjectBytes || owner===x.groups ||
      (owner===x.matchGlobals && ['maskD1','maskD2'].includes(String(key)))) reads++;
  });
  equal(reads,0,'target prefix never reads scheduler masks/groups/object snapshots');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no actor-frame epoch/claim is manufactured');
}

export function runBattleTargetPreparationSelfTests(make: Make,oldMake: ()=>OldFixture): void {
  {
    const old=oldMake(),scheduler=createSourceObjectSchedulerRuntime(old.schedulerSources);
    const outer=createSourceBattleOuterFrameRuntime({scheduler,systemGlobals:old.systemGlobals,massPreparation:old.massPreparation});
    check(ACTUAL_KEYS.every(key=>!Object.hasOwn(old.sourceActor,key)),'ordinary old fixture has no new target bytes');
    rejects(()=>outer.runFrame(),OLD);
    equal(old.massPreparation.orderCount.count80436260,6,'old fixture still completes genuine53b30 before unchanged6ae60 boundary');
  }
  {
    const x=make(),{scheduler,sources,outer}=setup(x),events: string[]=[];
    equal(x.projectiles.getAdmissionRuntime(),x.commandAdmission,'target uses SAME spawn-retained command-admission runtime');
    equal(x.targetAction,x.actionRequest!.getActorBinding(x.actor),'7d2 lives on SAME genuine action binding');
    equal(x.admissionState,x.commandAdmission.getActorBinding(x.actor),'508 lives on SAME genuine admission binding');
    equal(new Set(x.physicalIdentities).size,6,'six physical identities remain distinct');
    let target=false;
    untouchedScheduler(x,()=>observe(()=>rejects(()=>outer.runFrame(),CALLEE),(owner,key)=>{
      if(owner===sources && key==='targetPreparation') target=true;
      if(!target) return;
      if(owner===x.actorSlots) events.push(`slot${String(key)}`);
      x.slotTargets.forEach((row,index)=>{if(owner===row && key==='active0') events.push(`active${index}`);});
      for(const store of clearPlan(x)) if(owner===store.owner && key===store.key) events.push(store.key);
      if(owner===x.stageState && key==='lifecycle18') events.push('life');
      if(owner===x.admissionState && key==='pointer508') events.push('508');
    }));
    equal(events.join(','),['slot0','active0','byte58a','byte58b','byte58c','byte58d','byte7d2','byte7d3',
      'active1','active2','active3','active4','active5','slot0','active0','life'].join(','),
      'all first-pass physical clears precede fresh second base and first positive-lifecycle6b450 boundary');
    checkPrefix(x,6,'complete genuine first actor clear');
    equal(x.massPreparation.orderCount.count80436260,6,'all randomized mass-ordering writes precede target');
    equal(x.massHost.sourceArrowMass204,1200,'completed mass prefix is retained');
    check(x.slotTargets.every(hasIncompleteSourceActorDoubleLifecycle),'all reached physical actors permanently close');
    closed(x,scheduler,outer);
  }
  // Each genuine first-actor destination is independently made read-only at
  // its source store. No rollback and no bulk six-store preflight is allowed.
  for(let fault=0;fault<6;fault++) {
    const x=make(),{scheduler,sources,outer}=setup(x),store=clearPlan(x)[fault]!;
    let target=false,hit=false;
    observe(()=>rejects(()=>outer.runFrame(),'non-writable'),(owner,key)=>{
      if(owner===sources && key==='targetPreparation') target=true;
      if(target && owner===store.owner && key===store.key) {hit=true;Object.defineProperty(owner,key,{writable:false});}
    });
    check(hit,`reached clear store${fault}`);checkPrefix(x,fault,`fault${fault} retains ordered prefix`);
    equal(x.massPreparation.orderCount.count80436260,6,'clear fault is after whole mass ordering');
    closed(x,scheduler,outer);
  }
  for(const key of ACTUAL_KEYS) {
    const x=make(),index=clearPlan(x).findIndex(store=>store.key===key),{sources,outer}=setup(x);
    const inject=atTarget(sources,()=>{Reflect.deleteProperty(x.sourceActor,key);});
    observe(()=>rejects(()=>outer.runFrame(),`${key}: own data`),inject);
    clearPlan(x).forEach((store,i)=>{if(i!==index) equal(Reflect.get(store.owner,store.key),i<index?0:store.initial,'missing actual byte keeps exact clear prefix');});
    check(!Object.hasOwn(x.sourceActor,key),'missing store destination is not synthesized');
  }
  {
    const x=make('byte7d2'),{scheduler,outer}=setup(x);
    check(!Object.hasOwn(x.targetAction,'byte7d2'),'genuine sealed action owner truly omits7d2');
    rejects(()=>outer.runFrame(),'byte7d2: own data');
    for(const key of ACTUAL_KEYS.slice(0,4)) equal(Reflect.get(x.sourceActor,key),0,'missing7d2 follows first four actual stores');
    equal(x.sourceActor.byte7d3,96,'missing7d2 precedes final actual clear');closed(x,scheduler,outer);
    const ordinary=oldMake();check(Object.hasOwn(ordinary.actionRequest!.getActorBinding(ordinary.actor),'byte7d2'),'negative construction scope restores ordinary action input');
  }
  for(const active of [0,1,127,128,255]) {
    const x=make(),{sources,outer}=setup(x);let lifeReads=0,target=false;
    const inject=atTarget(sources,()=>{target=true;x.sourceActor.active0=active;});
    observe(()=>rejects(()=>outer.runFrame(),active===0?'unknown':CALLEE),(owner,key)=>{
      inject(owner,key);if(target && owner===x.stageState && key==='lifecycle18') lifeReads++;
    });
    checkPrefix(x,active===0?0:6,'raw signed-nonzero active gate');
    equal(lifeReads,active===0?0:1,'inactive second pass never loads lifecycle');
  }
  {
    const x=make(),{sources,outer}=setup(x);let unusedReads=0,target=false;
    for(const row of x.slotTargets.slice(1)) for(const key of [...ACTUAL_KEYS,'byte7d2','pointer508'])
      Object.defineProperty(row,key,{get() {throw Error('inactive field getter reached');},configurable:true});
    observe(()=>rejects(()=>outer.runFrame(),CALLEE),(owner,key)=>{
      if(owner===sources && key==='targetPreparation') target=true;
      if(target && x.slotTargets.slice(1).includes(owner) && [...ACTUAL_KEYS,'byte7d2','pointer508'].includes(String(key))) unusedReads++;
    });
    equal(unusedReads,0,'inactive first-pass rows read no target, action or lifecycle fields');
  }
  // There are36 potential source stores, but only the first physical row has
  // genuine7d2. Activate one later row AFTER mass preparation: its four actual
  // clears survive the missing canonical action owner; never invent a binding.
  for(let index=1;index<6;index++) {
    const x=make(),row=x.slotTargets[index]!,{sources,outer}=setup(x);
    const inject=atTarget(sources,()=>{Object.assign(row,{active0:1,byte58a:11,byte58b:12,byte58c:13,byte58d:14,byte7d3:16});});
    observe(()=>rejects(()=>outer.runFrame(),'unknown'),inject);
    checkPrefix(x,6,'first actor completes before later unbound row');
    for(const key of ACTUAL_KEYS.slice(0,4)) equal(Reflect.get(row,key),0,'later physical row retains four actual clears');
    equal(Reflect.get(row,'byte7d3'),16,'later unbound7d2 prevents its sixth clear');
    check(!Object.hasOwn(row,'byte7d2'),'no physical-row7d2 shadow is invented');
  }
  for(const lifecycle of [0,1,2,127,128,255]) {
    const x=make(),{sources,outer}=setup(x);let target=false,reads=0;
    const inject=atTarget(sources,()=>{target=true;x.stageState.lifecycle18=lifecycle;});
    observe(()=>rejects(()=>outer.runFrame(),lifecycle>0&&lifecycle<128?CALLEE:'unknown'),(owner,key)=>{
      inject(owner,key);if(target && owner===x.admissionState && key==='pointer508') reads++;
    });
    equal(reads,lifecycle>0&&lifecycle<128?0:1,'only SIGNED lifecycle>0 reaches6b450 before third pass');
    checkPrefix(x,6,'signed lifecycle always follows complete clears');
  }
  for(const active of [0,1,128,255]) for(const nonnull of [false,true]) {
    const x=make(),{sources,outer}=setup(x),events: string[]=[];let pass=0,target=false;
    const inject=atTarget(sources,()=>{target=true;x.stageState.lifecycle18=0;x.sourceActor.active0=active;});
    x.admissionState.pointer508=nonnull?x.visibility[0]!:null;
    observe(()=>rejects(()=>outer.runFrame(),nonnull&&active!==0?'83':'unknown'),(owner,key)=>{
      inject(owner,key);
      if(target && owner===x.actorSlots && key==='0') pass++;
      if(pass!==3) return;
      if(owner===x.sourceActor && key==='active0') events.push('active0');
      if(owner===x.admissionState && key==='pointer508') events.push('508');
      if(owner===x.slotTargets[1] && key==='active0') events.push('active1');
      if(owner===x.visibility[0]) events.push(`target:${String(key)}`);
    });
    equal(events.join(','),nonnull&&active!==0?'active0,508':'active0,508,active1',
      'third assembly load order precedes branch: active0 then508; no target83 read or guessed inactive508');
  }
  for(const active of [0,1]) {
    const x=make('pointer508'),{sources,outer}=setup(x);let third=0,target=false,pass=0;
    check(!Object.hasOwn(x.admissionState,'pointer508'),'genuine sealed admission truly omits508');
    const inject=atTarget(sources,()=>{target=true;x.sourceActor.active0=active;x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),'pointer508: own data'),(owner,key)=>{
      inject(owner,key);if(target && owner===x.actorSlots && key==='0') pass++;
      if(pass===3 && owner===x.sourceActor && key==='active0') third++;
    });
    equal(third,1,'inactive third-pass active load cannot bypass missing canonical508');
  }
  for(const [active,next] of [[0,1],[1,0],[128,0]] as const) {
    const x=make(),{sources,outer}=setup(x);let changed=false;
    x.admissionState.pointer508=x.visibility[0]!;
    const inject=atTarget(sources,()=>{x.sourceActor.active0=active;x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),active===0?'unknown':'83'),(owner,key)=>{
      inject(owner,key);
      if(owner===x.admissionState && key==='pointer508') {changed=true;x.sourceActor.active0=next;}
    });
    check(changed,'mutation reaches third-pass508 load');equal(x.sourceActor.active0,next,'mutation is retained');
  }
  for(const active of [0,1]) {
    const x=make(),{sources,outer}=setup(x);
    Reflect.set(x.admissionState,'pointer508',undefined);
    const inject=atTarget(sources,()=>{x.sourceActor.active0=active;x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),'pointer508: synchronous own-data'),inject);
  }
  // Each pass independently reloads live table[0], but the immutable physical
  // map is still the original block. A new base is refused, not reinterpreted.
  for(const which of [1,2,3]) {
    const x=make(),{sources,outer}=setup(x);let target=false,loads=0,changed=false;
    const inject=atTarget(sources,()=>{target=true;x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),'base'),(owner,key)=>{
      inject(owner,key);
      if(target && owner===x.actorSlots && key==='0' && ++loads===which) {x.actorSlots[0]=x.physicalIdentities[5]!;changed=true;}
    });
    check(changed,`fresh base pass${which} is reached`);equal(loads,which,'stops at first changed pass base');
    checkPrefix(x,which===1?0:6,'fresh base fault preserves only earlier source clears');
  }
  for(const key of ['active0','lifecycle18'] as const) for(const value of [-1,256,1.5,NaN]) {
    const x=make(),{sources,outer}=setup(x);
    const inject=atTarget(sources,()=>{if(key==='active0') x.sourceActor.active0=value;else x.stageState.lifecycle18=value;});
    observe(()=>rejects(()=>outer.runFrame(),'raw unsigned source integer'),inject);
    checkPrefix(x,key==='active0'?0:6,'invalid raw gate has exact source prefix');
  }
  for(const key of ['byte7d2','pointer508','lifecycle18','byte58A','1418','flags7d3']) {
    const x=make(),{sources,outer}=setup(x);
    const inject=atTarget(sources,()=>{Reflect.set(x.sourceActor,key,17);if(key==='pointer508') x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),'competing'),inject);
    equal(x.massPreparation.orderCount.count80436260,6,'target shadow admission is lazy after mass ordering');
  }
  for(const fault of ['missing','copied','second-brand'] as const) {
    const x=make(),{sources,outer}=setup(x);
    if(fault==='missing') Reflect.deleteProperty(x.targetPreparation,'admission');
    if(fault==='copied') Reflect.set(x.targetPreparation,'admission',{...x.commandAdmission});
    if(fault==='second-brand') sources.targetPreparation={admission:createSourceActorCommandAdmissionRuntime({
      world:x.world,status:x.status,attributes:x.attributes,charge:x.charge,actionRequest:x.actionRequest!,cues:x.cues,streams:x.control,gqr5:0x00070007,
    })};
    rejects(()=>outer.runFrame(),fault==='missing'?'admission: own data':'exact retained command admission');
    equal(x.massPreparation.orderCount.count80436260,6,'bad admission is not an eager pre-mass requirement');
    checkPrefix(x,4,'admission refusal retains exactly four preceding actual stores');
  }
  for(const alias of ['mass','actual','slots'] as const) {
    const x=make(),{sources,outer}=setup(x);
    Reflect.set(sources,'targetPreparation',alias==='mass'?x.massPreparation:alias==='actual'?x.sourceActor:x.actorSlots);
    rejects(()=>outer.runFrame(),'alias');checkPrefix(x,0,'target source alias refuses before target stores');
    equal(x.massPreparation.orderCount.count80436260,6,'target alias admission follows complete mass ordering');
  }
  for(const replace of ['targetPreparation','admission','physicalBlock'] as const) {
    const x=make(),{sources,outer}=setup(x);let changed=false;
    observe(()=>rejects(()=>outer.runFrame(),replace==='admission'?'exact retained command admission':'changed'),(owner,key)=>{
      if(!changed && owner===x.sourceActor && key==='byte58b') {
        changed=true;
        if(replace==='targetPreparation') sources.targetPreparation={...x.targetPreparation};
        else if(replace==='admission') Reflect.set(x.targetPreparation,'admission',{...x.commandAdmission});
        else x.massPreparation.physicalBlock=Object.freeze({...x.massPreparation.physicalBlock});
      }
    });
    check(changed,`canonical ${replace} replacement is observed after target begins`);
  }
  for(const location of ['clear','action','lifecycle','508'] as const) {
    const x=make(),{scheduler,sources,outer}=setup(x);let reentered=false,target=false;
    const inject=atTarget(sources,()=>{target=true;if(location==='508') x.stageState.lifecycle18=0;});
    observe(()=>rejects(()=>outer.runFrame(),'caught same-runtime reentry'),(owner,key)=>{
      inject(owner,key);
      const match=location==='clear'?owner===x.sourceActor&&key==='byte58c':
        location==='action'?owner===x.targetAction&&key==='byte7d2':
        location==='lifecycle'?owner===x.stageState&&key==='lifecycle18':owner===x.admissionState&&key==='pointer508';
      if(target && !reentered && match) {reentered=true;rejects(()=>outer.runFrame(),'same-runtime reentry');}
    });
    check(reentered,`caught reentry reaches ${location}`);closed(x,scheduler,outer);
  }
  console.log('[battle-target-preparation] PASS: authenticated ordered first-pass clears on same genuine7d2 owner, each six-store failure prefix and missing sealed cells, six physical rows with lazy inactive fields, signed lifecycle first6b450 boundary, assembly active0/508 load order and unbound inactive refusal, fresh pass bases, canonical admission/alias/reentry closure; bounded synthetic composition only, no six-active hydration, target helpers, scheduler or full-frame claim');
}
