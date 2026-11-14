import {createSourceActorMatrixUpdateRuntime} from './actor-matrix-update.js';
import {hasIncompleteSourceActorDoubleLifecycle, isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {createSourceBattleOuterFrameRuntime, type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime, requireSourceObjectSchedulerSnapshot,
  type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import type {createBattleMassOrderingTestFixture} from './attached-setup-animation.selftest.js';

/** Independently ordered assertions from80053d60..8005406c and800055fc.
 * Explicit bounded synthetic inputs, one genuine active actor repeated in six
 * live slots. No source callee is substituted, no six-actor retail hydration,
 * successful outer frame, scheduler execution or gameplay fidelity is claimed.
 * No-contact local counters are zero; strict passenger-count sorting remains
 * unreachable here. Role1 exercises real backward insertion separately. */
type Fixture=ReturnType<typeof createBattleMassOrderingTestFixture>;
const NEXT='8006ae60', COUNT='count80436260', LOW='byte804360c6', HIGH='byte804360c7';
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[battle-mass-ordering-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): void {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
/** Observation/mutation of reached descriptors, never a callee replacement. */
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
  const sources={scheduler,systemGlobals:x.systemGlobals,massPreparation:x.massPreparation};
  return {scheduler,sources,outer:createSourceBattleOuterFrameRuntime(sources)};
}
function closed(x: Fixture,scheduler: SourceObjectSchedulerRuntime,outer: SourceBattleOuterFrameRuntime): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal closes actual actor');
  rejects(()=>outer.runFrame(),'permanently incomplete');
  for(const run of [()=>scheduler.runGroup(9),()=>scheduler.runSlots(8),()=>scheduler.runWrapper(8)])
    rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  rejects(()=>requireSourceObjectSchedulerSnapshot(scheduler,x.allocator,x.child),'private active');
}
/** Independent integer quotient/remainder form, not the runtime bit operations. */
function nextSeed(low: number,high: number): [number,number] {
  const nextHigh=Math.floor((768*high+3*low)/256)%256;
  return [(low+nextHigh)%256,nextHigh];
}
function twoSeeds(low: number,high: number) {
  const first=nextSeed(low,high),second=nextSeed(...first);
  return {first,second,start:Math.floor(first[0]/4)%6,direction:Math.floor(second[0]/8)%2===1?1:-1};
}
function role1(x: Fixture): void {x.header.mode4a0=1;}
function atConstant(x: Fixture,action: ()=>void): (owner: object,key: PropertyKey)=>void {
  let done=false;return (owner,key)=>{if(!done && owner===x.massPreparation.data && key==='float80437258') {done=true;action();}};
}

export function runBattleMassOrderingSelfTests(make: ()=>Fixture): void {
  {
    const x=make(),{scheduler,outer}=setup(x),events: string[]=[],indices: number[]=[];
    let suffix=false,objectReads=0;
    const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
    equal(x.world.getCorrectedTraversalState(x.actor),x.normalState,'genuine world retains the same corrected4a4 binding');
    observe(()=>rejects(()=>outer.runFrame(),NEXT),(owner,key)=>{
      if(owner===x.massPreparation.rngState && (key===LOW || key===HIGH)) {suffix=true;events.push(String(key));}
      if(suffix && owner===x.actorSlots) indices.push(Number(key));
      if(suffix && owner===x.massPreparation.orderCount && key===COUNT) events.push(`count:${x.massPreparation.orderCount[COUNT]}`);
      if(suffix && owner===x.sourceActor && key==='field664') events.push('664');
      if(owner===x.objectBytes || owner===x.nextObjectBytes || owner===x.groups ||
        (owner===x.matchGlobals && ['maskD1','maskD2'].includes(String(key)))) objectReads++;
    });
    equal(events.slice(0,9).join(','),[HIGH,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW,'count:77'].join(','),
      'two RNG calls load high/low then store high/low before count clear');
    equal(indices.join(','),'2,3,4,5,0,1,0','two independent source draws choose start2/+1, then fresh final base load');
    equal(x.massPreparation.rngState[LOW],217,'two source draws retain final low');
    equal(x.massPreparation.rngState[HIGH],17,'two source draws retain final high');
    equal(x.massPreparation.orderCount[COUNT],6,'six stable equal-count appends');
    for(let i=0;i<6;i++) equal(x.massPreparation.orderPointers[i],x.actor,'stable ties keep repeated actual pointer');
    equal(x.sourceActor.field664,1,'reached source664 store');
    equal(x.massHost.sourceArrowMass204,1200,'old mass prefix survives');
    equal(objectReads,0,'no scheduler groups/masks/object callbacks');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no actor frame epoch claimed');
    closed(x,scheduler,outer);
  }
  // Every start and both directions are witnessed through actual table reads.
  const rotations=new Map<string,[number,number]>();
  for(let high=0;high<256;high++) for(let low=0;low<256;low++) {
    const expected=twoSeeds(low,high),key=`${expected.start}/${expected.direction}`;
    if(!rotations.has(key)) rotations.set(key,[low,high]);
  }
  equal(rotations.size,12,'independent arithmetic spans all start/direction combinations');
  for(const [low,high] of rotations.values()) {
    const x=make(),expected=twoSeeds(low,high);x.massPreparation.rngState[LOW]=low;x.massPreparation.rngState[HIGH]=high;
    const {outer}=setup(x),indices: number[]=[];let suffix=false;
    observe(()=>rejects(()=>outer.runFrame(),NEXT),(owner,key)=>{
      if(owner===x.massPreparation.data && key==='float80437258') suffix=true;
      if(suffix && owner===x.actorSlots) indices.push(Number(key));
    });
    equal(indices.join(','),[...Array.from({length:6},(_,i)=>(expected.start+i*expected.direction+30)%6),0].join(','),
      'live cyclic table order includes both wrap directions');
    equal(x.massPreparation.rngState[LOW],expected.second[0],'independent two-call low result');
    equal(x.massPreparation.rngState[HIGH],expected.second[1],'independent two-call high result');
  }
  // Selected low/high carry and sign boundaries exercise genuine mutations.
  // The all-state loop above is coverage selection, not an
  // all-state claim against the runtime.
  for(const high of [0,1,85,127,128,170,255]) for(const low of [0,1,2,3,63,64,85,86,127,128,169,170,171,195,254,255]) {
    const x=make(),expected=twoSeeds(low,high);x.massPreparation.rngState[LOW]=low;x.massPreparation.rngState[HIGH]=high;
    // Stop at the first operation after both draws to isolate byte arithmetic.
    Reflect.deleteProperty(x.massPreparation,'orderCount');
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'orderCount: own data');
    equal(x.massPreparation.rngState[LOW],expected.second[0],`RNG low ${low}/${high}`);
    equal(x.massPreparation.rngState[HIGH],expected.second[1],`RNG high ${low}/${high}`);
  }
  for(const [key,nth,low,high] of [[HIGH,2,195,1],[LOW,2,195,5],[HIGH,4,200,5],[LOW,4,200,17]] as const) {
    const x=make(),{scheduler,outer}=setup(x);let visits=0;
    observe(()=>rejects(()=>outer.runFrame(),'non-writable'),(owner,field)=>{
      if(owner===x.massPreparation.rngState && field===key && ++visits===nth)
        Object.defineProperty(owner,key,{writable:false});
    });
    equal(x.massPreparation.rngState[LOW],low,'failed RNG store keeps exact low prefix');
    equal(x.massPreparation.rngState[HIGH],high,'failed RNG store keeps exact high prefix');
    equal(x.massPreparation.orderCount[COUNT],77,'RNG failure precedes count clear');
    equal(x.sourceActor.field664,77,'RNG failure precedes664');closed(x,scheduler,outer);
  }
  for(const key of [HIGH,LOW] as const) for(const value of [-1,256,1.5,NaN,Infinity]) {
    const x=make();x.massPreparation.rngState[key]=value;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'raw unsigned source integer');
    equal(x.massPreparation.orderCount[COUNT],77,'bad raw RNG byte refuses before count reset');
  }
  for(const fault of ['rng','count','constant','664','pointers','pointer0'] as const) {
    const x=make();let expected='own data';
    if(fault==='rng') {Reflect.deleteProperty(x.massPreparation,'rngState');expected='800055fc';}
    if(fault==='count') Reflect.deleteProperty(x.massPreparation,'orderCount');
    if(fault==='constant') Reflect.deleteProperty(x.massPreparation.data,'float80437258');
    if(fault==='664') Reflect.deleteProperty(x.sourceActor,'field664');
    if(fault==='pointers') Reflect.deleteProperty(x.massPreparation,'orderPointers');
    if(fault==='pointer0') Reflect.deleteProperty(x.massPreparation.orderPointers,'0');
    const {outer}=setup(x);rejects(()=>outer.runFrame(),expected);
    if(fault!=='count') equal(x.massPreparation.orderCount[COUNT],fault==='rng'?77:
      fault==='pointers'||fault==='pointer0'?1:0,'missing lazy owner preserves exact preceding count store');
    if(fault!=='664') equal(x.sourceActor.field664,['rng','count','constant'].includes(fault)?77:1,'missing owner preserves664 prefix');
    equal(x.massHost.sourceArrowMass204,1200,'ordering admission happens after complete mass prefix');
  }
  for(const value of [0,-0,2,NaN,1.1]) {
    const x=make();x.massPreparation.data.float80437258=value;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),Number.isFinite(value)&&Math.fround(value)===value?'authenticated source bits':'finite exact source float32');
    equal(x.massPreparation.orderCount[COUNT],0,'count clears before invalid1.0');equal(x.sourceActor.field664,77,'invalid1.0 precedes664');
  }
  for(const active of [0,1,127,128,255]) {
    const x=make(),{outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),NEXT),atConstant(x,()=>{x.sourceActor.active0=active;}));
    equal(x.sourceActor.field664,1,'664 writes even on inactive actor');
    equal(x.massPreparation.orderCount[COUNT],active===0?0:6,'signed nonzero active admits negative bytes');
  }
  for(const mode of [0,1,2,127,128,255]) {
    const x=make();x.header.mode4a0=mode;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),NEXT);
    equal(x.massPreparation.orderCount[COUNT],mode===1?0:6,'only unsigned4a0 value1 skips randomized insertion');
  }
  for(const slot of [1,5,6,127,128,255]) {
    const x=make();x.sourceActor.slot=slot;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'local passenger count');
    equal(x.massPreparation.orderCount[COUNT],1,'first append does not read slot or uninitialized local byte');
    equal(x.massPreparation.orderPointers[0],x.actor,'first pointer append precedes second comparison refusal');
    equal(x.massPreparation.orderPointers[1],null,'no guessed zero counter admits second pointer');
  }
  {
    const x=make();x.sourceActor.active0=0;const {outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),'local passenger count'),atConstant(x,()=>{x.sourceActor.active0=1;}));
    equal(x.massPreparation.orderCount[COUNT],1,'inactive physical row did not initialize slot0 counter');
  }
  for(const count of [128,255]) {
    const x=make(),{outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),NEXT),atConstant(x,()=>{x.massPreparation.orderCount[COUNT]=count;}));
    equal(x.massPreparation.orderCount[COUNT],count,'negative captured count skips insertion without clamping');
    check(Object.values(x.massPreparation.orderPointers).every(p=>p===null),'negative count leaves stale array alone');
  }
  for(const count of [6,127]) {
    const x=make();for(let i=0;i<6;i++) x.massPreparation.orderPointers[i]=x.actor;
    const {outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),'explicit6-word'),atConstant(x,()=>{x.massPreparation.orderCount[COUNT]=count;}));
    equal(x.massPreparation.orderCount[COUNT],count===6?7:127,'append increments before out-of-domain pointer; scan refuses before append');
  }
  {
    const x=make(),{outer}=setup(x);let countReads=0;
    observe(()=>rejects(()=>outer.runFrame(),'explicit6-word'),(owner,key)=>{
      if(owner===x.massPreparation.orderCount && key===COUNT && ++countReads===3) x.massPreparation.orderCount[COUNT]=255;
    });
    equal(x.massPreparation.orderCount[COUNT],0,'fresh append raw255 wraps before signed-1 pointer refusal');
    equal(x.massPreparation.orderPointers[0],null,'negative append index is not clamped');
  }
  for(const link of ['stale','null','miss'] as const) {
    const x=make();role1(x);
    x.normalState.link4a4=link==='null'?null:x.target;
    x.massPreparation.orderPointers[0]=link==='stale'?x.target:null;
    const {outer}=setup(x),events: string[]=[];let suffix=false;
    observe(()=>rejects(()=>outer.runFrame(),NEXT),(owner,key)=>{
      if(owner===x.massPreparation.data && key==='float80437258') suffix=true;
      if(!suffix) return;
      if(owner===x.massPreparation.orderPointers) events.push(`list${String(key)}`);
      if(owner===x.normalState && key==='link4a4') events.push('parent');
    });
    equal(events.slice(0,2).join(','),'list0,parent','role1 loads stale list word before fresh parent pointer');
    equal(x.massPreparation.orderCount[COUNT],link==='miss'?0:1,'count+1 scan includes stale logical tail even for empty list');
    equal(x.massPreparation.orderPointers[0],link==='miss'?null:x.actor,'null equality is source pointer comparison, not a guessed default');
  }
  {
    const x=make();role1(x);Reflect.deleteProperty(x.massPreparation.orderPointers,'0');
    Reflect.deleteProperty(x.normalState,'link4a4');
    const {outer}=setup(x);let links=0;
    observe(()=>rejects(()=>outer.runFrame(),'0: own data'),(owner,key)=>{if(owner===x.normalState && key==='link4a4') links++;});
    equal(links,0,'missing stale tail word refuses before missing4a4 owner');
  }
  for(const position of [0,1,3,4]) {
    const x=make();role1(x);
    const markers=Array.from({length:6},(_,i)=>Symbol(`unresolved stale pointer${i}`));
    markers[position]=x.target;for(let i=0;i<6;i++) x.massPreparation.orderPointers[i]=markers[i]!;
    const {outer}=setup(x),indices: number[]=[];let phase=false;
    const count4=atConstant(x,()=>{x.massPreparation.orderCount[COUNT]=4;phase=true;});
    observe(()=>rejects(()=>outer.runFrame(),NEXT),(owner,key)=>{
      count4(owner,key);if(phase && owner===x.massPreparation.orderPointers) indices.push(Number(key));
    });
    equal(indices.join(','),[...Array.from({length:position+1},(_,i)=>i),
      ...Array.from({length:4-position},(_,i)=>[3-i,4-i]).flat(),position].join(','),
      'role1 scans count+1 then shifts each load/store from high to low before insertion');
    const expected=[...markers.slice(0,position),x.actor,...markers.slice(position,4),markers[5]];
    for(let i=0;i<6;i++) equal(x.massPreparation.orderPointers[i],expected[i],'source stable backward insertion and untouched tail');
    equal(x.massPreparation.orderCount[COUNT],5,'role1 pointer insertion increments count');
  }
  for(const fault of ['shift4','insert0','count'] as const) {
    const x=make();role1(x);x.massPreparation.orderPointers[0]=x.target;
    const markers=Array.from({length:5},(_,i)=>Symbol(`shift marker${i}`));
    for(let i=1;i<6;i++) x.massPreparation.orderPointers[i]=markers[i-1]!;
    const {outer}=setup(x);let final=false;
    const count4=atConstant(x,()=>{x.massPreparation.orderCount[COUNT]=4;});
    observe(()=>rejects(()=>outer.runFrame(),'non-writable'),(owner,key)=>{
      count4(owner,key);
      if(owner===x.normalState && key==='link4a4') {
        final=true;
        if(fault==='shift4') Object.defineProperty(x.massPreparation.orderPointers,'4',{writable:false});
        if(fault==='insert0') Object.defineProperty(x.massPreparation.orderPointers,'0',{writable:false});
        if(fault==='count') Object.defineProperty(x.massPreparation.orderCount,COUNT,{writable:false});
      }
    });
    check(final,'role1 reaches genuine link4a4');equal(x.massPreparation.orderCount[COUNT],4,'failed insertion/count preserves count4');
    equal(x.massPreparation.orderPointers[0],fault==='count'?x.actor:x.target,'insertion pointer store precedes count store');
    equal(x.massPreparation.orderPointers[4],fault==='shift4'?markers[3]:markers[2],'earlier backward shift survives later failure');
    equal(x.massPreparation.orderPointers[1],fault==='shift4'?markers[0]:x.target,'first failed high shift prevents all lower shifts');
  }
  {
    const x=make();role1(x);x.massPreparation.orderPointers[0]=x.target;
    const {outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),NEXT),()=>{},(owner,key)=>{
      if(owner===x.normalState && key==='link4a4') x.massPreparation.orderCount[COUNT]=255;
    });
    equal(x.massPreparation.orderPointers[0],x.actor,'role1 uses captured position despite changed fresh count');
    equal(x.massPreparation.orderCount[COUNT],0,'fresh insertion raw255 wraps only after pointer store');
  }
  {
    const x=make();role1(x);x.massPreparation.orderPointers[0]=Symbol('nonmatching stale pointer');
    x.massPreparation.orderPointers[1]=x.target;
    const {outer}=setup(x);let links=0;
    const count1=atConstant(x,()=>{x.massPreparation.orderCount[COUNT]=1;});
    observe(()=>rejects(()=>outer.runFrame(),NEXT),(owner,key)=>{
      count1(owner,key);if(owner===x.normalState && key==='link4a4') links++;
    });
    equal(links,2,'parent reloads at every comparison including stale logical tail1');
    equal(x.massPreparation.orderPointers[1],x.actor,'logical tail match inserts at count');
    equal(x.massPreparation.orderCount[COUNT],2,'stale tail match increments count');
  }
  for(const which of ['null-next','missing664','final-base'] as const) {
    const x=make(),{outer}=setup(x);let suffix=false,visits=0;
    observe(()=>rejects(()=>outer.runFrame(),which==='null-next'?'null actor':which==='missing664'?'field664':'final physical base'),
      (owner,key)=>{
        if(owner===x.massPreparation.data && key==='float80437258') suffix=true;
        if(suffix && owner===x.actorSlots && ++visits===2) {
          if(which==='null-next') x.actorSlots[3]=null;
          if(which==='missing664') x.actorSlots[3]=x.physicalIdentities[5]!;
        }
        if(suffix && owner===x.actorSlots && which==='final-base' && visits===7) x.actorSlots[0]=x.physicalIdentities[5]!;
      });
    equal(x.massPreparation.orderCount[COUNT],which==='final-base'?6:1,'fresh table loads preserve earlier ordered writes');
    equal(x.massPreparation.orderPointers[0],x.actor,'first real append retained after later pointer mutation');
  }
  {
    const x=make();role1(x);Reflect.deleteProperty(x.massPreparation,'matrices');
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'matrices: own data');
    equal(x.sourceActor.field664,1,'missing optional4a4 runtime is lazy until role1 final scan');
  }
  {
    const x=make();Reflect.deleteProperty(x.massPreparation,'matrices');
    const {outer}=setup(x);rejects(()=>outer.runFrame(),NEXT);
    equal(x.massPreparation.orderCount[COUNT],6,'ordinary no-role1 path never demands optional matrices');
  }
  {
    const x=make();role1(x);
    // Negative admission fixture only: this second branded runtime deliberately
    // fails to register its binding with the actual world. The adapter is never
    // used to claim a successful source call, matrix update, or outer frame.
    const counterfeit=createSourceActorMatrixUpdateRuntime({
      world:{...x.world,bindCorrectedTraversalState() {}},movement:x.movement,
      metadata:x.metadata,mapping:x.mapping,globals:x.matchGlobals,
    });
    counterfeit.bindActor(x.actor,{count1d96:0,count1d97:0,field1d60:0,byte660:0,link4a4:null});
    const counterfeitBinding=counterfeit.getActorBinding(x.actor);
    equal(counterfeit.getActualActor(x.actor),x.sourceActor,'negative runtime retains same actual actor');
    equal(counterfeit.getWorldBinding(x.actor),x.header,'negative runtime retains same world binding');
    equal(counterfeit.getMappingActor(x.actor),x.mapping.getActor(x.actor),'negative runtime retains same mapping actor');
    equal(counterfeit.getGlobals(),x.matchGlobals,'negative runtime retains same battle globals');
    equal(x.world.getCorrectedTraversalState(x.actor),x.normalState,'counterfeit binding did not replace canonical corrected state');
    check(counterfeitBinding!==x.normalState,'negative runtime has a distinct branded4a4 binding');
    x.massPreparation.matrices=counterfeit;
    const {scheduler,outer}=setup(x);let linkReads=0,listReads=0;
    observe(()=>rejects(()=>outer.runFrame(),'canonical corrected4a4 owner differs'),(owner,key)=>{
      if(owner===counterfeitBinding && key==='link4a4') linkReads++;
      if(owner===x.massPreparation.orderPointers) listReads++;
    });
    equal(linkReads,0,'canonical corrected owner refusal precedes counterfeit4a4 pointer load');
    equal(listReads,1,'source stale list load still precedes canonical4a4 admission');
    equal(x.massPreparation.orderCount[COUNT],0,'counterfeit null parent cannot authorize insertion');
    equal(x.massPreparation.orderPointers[0],null,'refused counterfeit preserves stale null tail');
    equal(x.sourceActor.field664,1,'completed RNG/randomized664 prefix remains visible');
    closed(x,scheduler,outer);
  }
  for(const alias of ['rng-count','rng-data','pointers-slots','pointers-team','count-actor'] as const) {
    const x=make();
    if(alias==='rng-count') Reflect.set(x.massPreparation,'orderCount',x.massPreparation.rngState);
    if(alias==='rng-data') Reflect.set(x.massPreparation,'rngState',x.massPreparation.data);
    if(alias==='pointers-slots') Reflect.set(x.massPreparation,'orderPointers',x.actorSlots);
    if(alias==='pointers-team') Reflect.set(x.massPreparation,'orderPointers',x.massPreparation.teamPointers);
    if(alias==='count-actor') Reflect.set(x.massPreparation,'orderCount',x.sourceActor);
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'alias');
  }
  for(const rival of ['float664','mass664','1636','byte664','byte665','byte666','byte667','slot3e4','byte3e4']) {
    const x=make();Reflect.set(x.sourceActor,rival,17);
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'competing source cell');
  }
  for(const replaced of ['rngState','orderPointers','orderCount','massPreparation'] as const) {
    const x=make(),{outer,sources}=setup(x);let done=false;
    observe(()=>rejects(()=>outer.runFrame(),'canonical owner changed'),(owner,key)=>{
      const gate=replaced==='rngState'?owner===x.massPreparation.rngState&&key===LOW:
        owner===x.massPreparation.orderPointers&&key==='0';
      if(!done && gate) {
        done=true;
        if(replaced==='massPreparation') sources.massPreparation={...x.massPreparation};
        else Reflect.set(x.massPreparation,replaced,{...x.massPreparation[replaced]});
      }
    });
    check(done,'canonical owner replacement observed at a reached source operation');
  }
  for(const location of ['rng','664','append','parent'] as const) {
    const x=make();if(location==='parent') {role1(x);x.normalState.link4a4=null;}
    const {scheduler,outer}=setup(x);let reentered=false;
    observe(()=>rejects(()=>outer.runFrame(),'caught same-runtime reentry'),(owner,key)=>{
      const match=location==='rng'?owner===x.massPreparation.rngState&&key===HIGH:
        location==='664'?owner===x.sourceActor&&key==='field664':
        location==='append'?owner===x.massPreparation.orderPointers&&key==='0':owner===x.normalState&&key==='link4a4';
      if(!reentered && match) {reentered=true;rejects(()=>outer.runFrame(),'same-runtime reentry');}
    });
    check(reentered,'reentry reaches requested ordering operation');closed(x,scheduler,outer);
  }
  console.log('[battle-mass-ordering] PASS: genuine two-call byte RNG, 112 independent boundary seeds and all12 cyclic traversals, source664/active/mode order, initialized physical counters and signed slots/counts, stable repeated-pointer ties, stale-tail/null-parent role1 matching, backward load/store pairs, append versus insertion failure prefixes, live table/final base reloads, lazy identity/alias/reentry closure; synthetic no-contact subset only, no retail six-actor hydration, passenger sorting, scheduler or full frame claim');
}
