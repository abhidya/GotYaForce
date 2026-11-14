import {hasIncompleteSourceActorDoubleLifecycle, isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import {createSourceBattleOuterFrameRuntime, type SourceBattleOuterFrameRuntime,
  type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime, requireSourceObjectSchedulerSnapshot,
  type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import type {createBattleMassPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** These assertions were ordered independently from authenticated db.3.gbf
 * derived instructions80053b5c–80053d60. They test the genuine bounded runtime,
 * not an original-console oracle, ordinary actor hydration, successful RNG,
 * passenger propagation, scheduler execution, or a successful outer frame.
 * The explicit fixture has one genuinely bound actor repeated in the pointer
 * table and five distinct inactive physical rows without status/4ac owners.
 */
type Fixture=ReturnType<typeof createBattleMassPreparationTestFixture>;
const RNG='800055fc', PASSENGER='unsupported actual pointer1e4';
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[battle-mass-preparation-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): void {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
/** Descriptor observation only, never a successful source callee substitute.
 * Mutations are explicitly synthetic interruptions at reached source loads. */
function observe(run: ()=>void,before: (owner: object,key: PropertyKey)=>void,
  after?: (owner: object,key: PropertyKey)=>void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function omitMassParameter(x: Fixture): void {
  const replacement={...x.massParameter};delete replacement.field98;
  const binding=x.attributes.getActorBinding(x.actor);
  binding.parameter4ac=x.attributes.createParameterDescriptor(replacement);
  x.massParameter=x.attributes.getParameterDescriptor(binding.parameter4ac);
}
function setup(x: Fixture,supply=true) {
  const scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources);
  const sources: SourceBattleOuterFrameSources={scheduler,systemGlobals:x.systemGlobals};
  if(supply) sources.massPreparation=x.massPreparation;
  return {scheduler,sources,outer:createSourceBattleOuterFrameRuntime(sources)};
}
function closed(x: Fixture,scheduler: SourceObjectSchedulerRuntime,outer: SourceBattleOuterFrameRuntime): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal closes retained actual Double owner');
  rejects(()=>outer.runFrame(),'permanently incomplete');
  for(const run of [()=>scheduler.runGroup(9),()=>scheduler.runSlots(8),()=>scheduler.runWrapper(8)])
    rejects(run,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  rejects(()=>requireSourceObjectSchedulerSnapshot(scheduler,x.allocator,x.child),'private active');
}
interface Store {owner: object;key: string;value: number|symbol|null;nth: number}
/** Source clear order from53b5c,53b64–53bcc, not grouped by destination type. */
function clears(x: Fixture): Store[] {
  const p=x.massPreparation.teamPointers,c=x.massPreparation.teamCounts;
  const pointer=(i: number): Store=>({owner:p,key:String(i),value:null,nth:1});
  const count=(i: number): Store=>({owner:c,key:String(i),value:0,nth:1});
  return [...Array.from({length:20},(_,i)=>pointer(i)),count(0),pointer(20),count(1),pointer(21),
    count(2),pointer(22),pointer(23),count(3)];
}
function stores(x: Fixture): Store[] {
  return [...clears(x),{owner:x.massHost,key:'sourceArrowMass204',value:0,nth:1},
    {owner:x.sourceActor,key:'mass208',value:200,nth:1},
    {owner:x.massPreparation.teamCounts,key:'0',value:1,nth:3},
    {owner:x.massPreparation.teamPointers,key:'0',value:x.actor,nth:2},
    ...Array.from({length:6},(_,i)=>({owner:x.massHost,key:'sourceArrowMass204',value:200*(i+1),nth:3+i*2}))];
}
function untouchedObjects(x: Fixture,run: ()=>void): void {
  let objectReads=0;const before=isSourceActorDoubleFrameClaimed(x.sourceActor);
  observe(run,(owner,key)=>{
    if(owner===x.objectBytes || owner===x.nextObjectBytes || owner===x.groups ||
      (owner===x.matchGlobals && ['maskD1','maskD2'].includes(String(key)))) objectReads++;
  });
  equal(objectReads,0,'no scheduler masks/groups, object snapshots or callbacks');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor),before,'no manufactured actor-frame epoch/claim');
}

export function runBattleMassPreparationSelfTests(make: ()=>Fixture): void {
  {
    const x=make(),{scheduler,outer}=setup(x),events: string[]=[];
    equal(scheduler.getActorSlotTable(),x.actorSlots,'same original live pointer table');
    equal(x.root.getStageRuntime(),x.stageBounds,'same stage owner');
    equal(x.status.getActualBorg(x.actor),x.massHost,'actual204 borrows existing Borg cell');
    equal(x.status.getAttributeBinding(x.actor),x.attributes.getActorBinding(x.actor),'same4ac binding');
    equal(new Set(x.physicalIdentities).size,6,'fixture keeps six distinct physical identities');
    const expected=stores(x);const visits=new Map<Store,number>();
    untouchedObjects(x,()=>observe(()=>rejects(()=>outer.runFrame(),RNG),(owner,key)=>{
      if(owner===x.actorSlots) events.push(`slot${String(key)}`);
      for(let i=0;i<expected.length;i++) {const store=expected[i]!;
        if(store.owner!==owner || store.key!==key) continue;
        const n=(visits.get(store)??0)+1;visits.set(store,n);
        if(n===store.nth) events.push(`write${i}`);
      }
      for(let i=0;i<6;i++) if(owner===x.slotTargets[i] && key==='active0') events.push(`physical${i}`);
    }));
    equal(events.slice(0,30).join(','),['write0','slot0',...Array.from({length:27},(_,i)=>`write${i+1}`),'physical0'].join(','),
      'first pointer clear precedes captured table0, then all mixed-order clears before physical traversal');
    equal(events.filter(e=>e.startsWith('physical')).join(','),'physical0,physical1,physical2,physical3,physical4,physical5',
      'physical stride walks original distinct block, not repeated live table');
    equal(events.filter(e=>e.startsWith('slot')).join(','),'slot0,slot0,slot1,slot2,slot3,slot4,slot5',
      'capture followed by six fresh live loads');
    equal(events.filter(e=>e.startsWith('write')).join(','),expected.map((_,i)=>`write${i}`).join(','),'all source stores ordered');
    equal(x.sourceActor.mass208,200,'scaled descriptor98 stored on actual208');
    equal(x.massHost.sourceArrowMass204,1200,'six repeated pointers perform six float additions');
    equal(x.massPreparation.teamCounts[0],1,'state1 physical actor appended only once');
    equal(x.massPreparation.teamPointers[0],x.actor,'compact team0 first pointer');
    check(x.slotTargets.slice(1).every(a=>hasIncompleteSourceActorDoubleLifecycle(a)),'all newly reached inactive physical actors close');
    closed(x,scheduler,outer);
  }
  {
    const x=make(),{outer}=setup(x),events: string[]=[];
    const binding=x.attributes.getActorBinding(x.actor);let started=false;
    observe(()=>rejects(()=>outer.runFrame(),RNG),(owner,key)=>{
      if(owner===x.sourceActor && key==='active0') {started=true;events.push('active0');}
      if(!started) return;
      for(const [record,field,label] of [
        [x.massPreparation.data,'float80437250','zero'],[x.massPreparation.data,'float80437254','threshold'],
        [x.massHost,'sourceArrowMass204','204'],[x.stageState,'lifecycle18','18'],[binding,'parameter4ac','4ac'],
        [x.massParameter,'field98','98'],[x.sourceActor,'modelScale','scale'],[x.sourceActor,'mass208','208'],
        [x.sourceActor,'team','team'],[x.massPreparation.teamCounts,'0','count'],
        [x.sourceActor,'supportContact1db','1db'],
      ] as const) if(owner===record && key===field) events.push(label);
    });
    equal(events.join(','),['active0','zero','204','18','4ac','threshold','98','scale','208','18','team','count','count',
      ...Array.from({length:6},()=>['204','208','204','1db']).flat()].join(','),
    'actual scalar load/store preflight order follows53be0–53d50 without eager parameter/scale/support reads');
  }
  {
    const x=make(),{outer}=setup(x);let captures=0;
    observe(()=>rejects(()=>outer.runFrame(),'unknown'),()=>{},(owner,key)=>{
      if(owner===x.actorSlots && key==='0' && ++captures===1) x.actorSlots[0]=x.physicalIdentities[5]!;
    });
    equal(x.sourceActor.mass208,200,'captured table0 base continues original physical block after live table permutation');
    equal(x.massHost.sourceArrowMass204,0,'second traversal reloads changed table0 before any addition');
    equal(x.massPreparation.teamCounts[0],1,'genuine physical append survives different first live pointer');
  }
  for(const active of [0,127,128,255]) {
    const x=make();x.sourceActor.active0=active;
    if(active===0) {
      omitMassParameter(x);Reflect.deleteProperty(x.massPreparation,'data');
      Reflect.deleteProperty(x.massPreparation,'attributes');
    }
    for(const row of x.slotTargets.slice(1)) for(const key of ['modelScale','mass208','supportContact1db'])
      Object.defineProperty(row,key,{get() {throw Error('inactive physical scalar getter reached');},configurable:true});
    const {outer}=setup(x);rejects(()=>outer.runFrame(),RNG);
    equal(x.sourceActor.mass208,active===0 ? 79 : 200,'signed nonzero active byte versus lazy inactive physical scalars');
    equal(x.massHost.sourceArrowMass204,active===0 ? 547 : 1200,'inactive first row keeps204/208 but all live entries add');
  }
  {
    const x=make();x.sourceActor.team=1;const {outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),RNG),(owner,key)=>{
      if(owner===x.sourceActor && key==='team') x.massPreparation.teamCounts[1]=255;
    });
    equal(x.massPreparation.teamCounts[1],0,'raw255 count increments and wraps to0');
    equal(x.massPreparation.teamPointers[5],x.actor,'signed count-1 addresses prior explicit team cell, not clamped to row');
  }
  for(const [accumulator,mass,expected] of [[2**24,1,2**24],[-0,-0,-0],[1,-1,-5]] as const) {
    const x=make(),{outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),RNG),(owner,key)=>{
      if(owner===x.slotTargets[5] && key==='active0') {
        x.massHost.sourceArrowMass204=accumulator;x.sourceActor.mass208=mass;
      }
    });
    equal(x.massHost.sourceArrowMass204,expected,'six nearest-even additions use live204/208 including cancellation/signed zero');
  }
  {
    const x=make(),{outer}=setup(x);Reflect.set(x.slotTargets[3]!,'sourceArrowMass204',9);
    rejects(()=>outer.runFrame(),'competing source cell owner');
    check(hasIncompleteSourceActorDoubleLifecycle(x.slotTargets[3]!), 'new actual closes even when its own alias admission fails');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.slotTargets[4]!), 'unreached following actual remains unclaimed');
  }
  // Each real store destination is made non-writable only at its actual
  // preflight. Every earlier store persists, every later store stays untouched.
  for(let fault=0;fault<38;fault++) {
    const x=make(),plan=stores(x),target=plan[fault]!,{scheduler,outer}=setup(x);
    equal(plan.length,38,'enumerated complete bounded-prefix store list');
    const expected=new Map<object,Map<string,unknown>>();
    for(const store of plan) {
      let cells=expected.get(store.owner);if(!cells) {cells=new Map();expected.set(store.owner,cells);}
      if(!cells.has(store.key)) cells.set(store.key,Reflect.get(store.owner,store.key));
    }
    for(const store of plan.slice(0,fault)) expected.get(store.owner)!.set(store.key,store.value);
    let n=0,hit=false;
    observe(()=>rejects(()=>outer.runFrame(),'non-writable'),(owner,key)=>{
      if(owner===target.owner && key===target.key && ++n===target.nth) {
        hit=true;Object.defineProperty(owner,key,{writable:false});
      }
    });
    check(hit,`store fault${fault} reached`);
    for(const [owner,cells] of expected) for(const [key,value] of cells) equal(Reflect.get(owner,key),value,`store fault${fault} retains exact prefix ${key}`);
    closed(x,scheduler,outer);
  }
  for(const lifecycle of [0,1,2,3,127,128,255]) {
    const x=make();x.stageState.lifecycle18=lifecycle;
    if(lifecycle!==1 && lifecycle!==2) {
      omitMassParameter(x);Reflect.deleteProperty(x.sourceActor,'modelScale');
      Reflect.deleteProperty(x.massPreparation,'attributes');
    }
    const {outer}=setup(x);rejects(()=>outer.runFrame(),RNG);
    equal(x.sourceActor.mass208,lifecycle===1 || lifecycle===2 ? 200 : 0,'signed lifecycle1/2 selects mass only');
    equal(x.massPreparation.teamCounts[0],lifecycle===1 ? 1 : 0,'only unsigned lifecycle1 appends');
  }
  for(const [first,second] of [[1,2],[2,1],[255,1],[1,255]] as const) {
    const x=make();x.stageState.lifecycle18=first;let reads=0;
    const {outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),RNG),()=>{},(owner,key)=>{
      if(owner===x.stageState && key==='lifecycle18' && ++reads===1) x.stageState.lifecycle18=second;
    });
    equal(reads,2,'lifecycle is loaded twice, never cached');
    equal(x.massPreparation.teamCounts[0],second===1 ? 1 : 0,'fresh unsigned second lifecycle load decides append');
    equal(x.sourceActor.mass208,first===1 || first===2 ? 200 : 0,'first signed lifecycle load still decides mass');
  }
  for(const [mass,scale,result] of [
    [100,2,200],[49999,3,149997],[50000,NaN,50000],[50001,NaN,50001],
    [-3,2,-6],[-0,2,-0],[0,-2,-0],[2**-149,.5,0],[-(2**-149),.5,-0],
    [Math.fround(1.0000001192092896),Math.fround(1.0000001192092896),Math.fround(1.0000002384185933)],
  ]) {
    const x=make();x.massParameter.field98=mass!;x.sourceActor.modelScale=scale!;
    if(Number.isNaN(scale)) Reflect.deleteProperty(x.sourceActor,'modelScale');
    const {outer}=setup(x);rejects(()=>outer.runFrame(),RNG);
    equal(x.sourceActor.mass208,result,'threshold/scaled finite float32 including signed zero and underflow');
    if(Object.is(result,-0)) equal(x.massHost.sourceArrowMass204,0,'+0 plus -0 is +0 under nearest-even');
  }
  for(const [mass,scale] of [[-3.4028234663852886e38,2],[49999,3.4028234663852886e38]]) {
    const x=make();x.massParameter.field98=mass!;x.sourceActor.modelScale=scale!;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'overflows finite float32');
    equal(x.massHost.sourceArrowMass204,0,'overflow keeps preceding204 clear');
    equal(x.sourceActor.mass208,79,'overflow refuses before208 store');
  }
  {
    const x=make();x.massParameter.field98=3.4028234663852886e38;
    const {scheduler,outer}=setup(x);rejects(()=>outer.runFrame(),'overflow float32');
    equal(x.massHost.sourceArrowMass204,3.4028234663852886e38,'first addition survives second overflowing addition');
    closed(x,scheduler,outer);
  }
  for(const value of [NaN,Infinity,-Infinity,1.1]) {
    const x=make();x.massParameter.field98=value;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'finite exact source float32');
    equal(x.massHost.sourceArrowMass204,0,'invalid98 refuses after preceding204 clear');
  }
  for(const [key,value] of [['float80437250',-0],['float80437254',49999]] as const) {
    const x=make();x.massPreparation.data[key]=value;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'differs from authenticated source bits');
    equal(x.massHost.sourceArrowMass204,key==='float80437250' ? 73 : 0,'authenticated constant fault preserves exact prefix');
  }
  for(const team of [0,1,2,3,4,127,128,255]) {
    const x=make();x.sourceActor.team=team;
    const {outer}=setup(x);rejects(()=>outer.runFrame(),team<4 ? RNG : 'team outside');
    for(let i=0;i<4;i++) equal(x.massPreparation.teamCounts[i],team===i ? 1 : 0,'signed team bounded without clamp');
    equal(x.sourceActor.mass208,200,'team refusal follows mass store');
  }
  for(const count of [6,23,24,127,128,255]) {
    const x=make(),{outer}=setup(x);let reached=false;
    observe(()=>rejects(()=>outer.runFrame(),count<24 ? RNG : 'pointer index outside'),(owner,key)=>{
      if(owner===x.sourceActor && key==='team' && !reached) {reached=true;x.massPreparation.teamCounts[0]=count;}
    });
    equal(x.massPreparation.teamCounts[0],(count+1)&255,'raw count increment wraps before signed pointer index fault');
    if(count<24) equal(x.massPreparation.teamPointers[count],x.actor,'positive count addresses explicit whole24-word owner');
  }
  for(const flag of [1,128,255]) {
    const x=make();x.sourceActor.supportContact1db=flag;
    const {scheduler,outer}=setup(x);let pointerReads=0;
    observe(()=>rejects(()=>outer.runFrame(),PASSENGER),(owner)=>{if(owner===x.actorSlots) pointerReads++;});
    equal(x.massHost.sourceArrowMass204,200,'nonzero signed support refuses only after own addition');
    equal(pointerReads,2,'passenger boundary stops before second pointer load');
    closed(x,scheduler,outer);
  }
  {
    const x=make(),{outer}=setup(x);let phase=false;
    observe(()=>rejects(()=>outer.runFrame(),RNG),(owner,key)=>{
      if(owner===x.slotTargets[5] && key==='active0') {phase=true;x.sourceActor.active0=0;}
    });
    check(phase,'all physical rows reached');equal(x.massHost.sourceArrowMass204,1200,'second pointer traversal ignores newly inactive0');
  }
  {
    const x=make(),{outer}=setup(x);
    observe(()=>rejects(()=>outer.runFrame(),'mass208: own data'),(owner,key)=>{
      if(owner===x.slotTargets[5] && key==='active0') {x.sourceActor.active0=0;delete x.sourceActor.mass208;}
    });
    equal(x.massHost.sourceArrowMass204,0,'inactive live pointer still requires208 before own store');
  }
  for(const next of [null,'inactive'] as const) {
    const x=make(),{outer}=setup(x);let captures=0;
    observe(()=>rejects(()=>outer.runFrame(),next===null ? 'null actor' : 'unknown'),()=>{},(owner,key)=>{
      if(owner===x.actorSlots && key==='0' && ++captures===2) x.actorSlots[1]=next===null ? null : x.physicalIdentities[5]!;
    });
    equal(x.massHost.sourceArrowMass204,200,'fresh slot1 replacement observed after first addition');
    equal(x.massPreparation.teamCounts[0],1,'physical traversal independent of replacement live pointer order');
  }
  {
    const x=make(),{outer}=setup(x);x.slotTargets[3]!.active0=1;
    rejects(()=>outer.runFrame(),'unknown');
    equal(x.sourceActor.mass208,200,'earlier genuine actor writes survive newly active missing status owner');
    check(hasIncompleteSourceActorDoubleLifecycle(x.slotTargets[3]!), 'new actual lacking genuine status is also closed');
    check(!hasIncompleteSourceActorDoubleLifecycle(x.slotTargets[4]!), 'unreached physical actor is not eagerly closed');
  }
  for(const fault of ['missing-block','unfrozen-block','unfrozen-ids','duplicate','base','interior'] as const) {
    const x=make();let expected='frozen';
    if(fault==='missing-block') {Reflect.deleteProperty(x.massPreparation,'physicalBlock');expected='own data';}
    if(fault==='unfrozen-block') x.massPreparation.physicalBlock={...x.massPreparation.physicalBlock};
    if(fault==='unfrozen-ids') x.massPreparation.physicalBlock=Object.freeze({base:x.actor,identities:[...x.physicalIdentities]});
    if(fault==='duplicate') {const ids=[...x.physicalIdentities];ids[2]=ids[1]!;
      x.massPreparation.physicalBlock=Object.freeze({base:x.actor,identities:Object.freeze(ids)});expected='distinct physical';}
    if(fault==='base') {x.massPreparation.physicalBlock=Object.freeze({...x.massPreparation.physicalBlock,base:Symbol('other')});expected='base differs';}
    if(fault==='interior') {const ids=[...x.physicalIdentities];ids[2]=x.allocator.getInteriorPointer(x.actor,0x1e00);
      x.massPreparation.physicalBlock=Object.freeze({base:x.actor,identities:Object.freeze(ids)});expected='base identity';}
    const {outer}=setup(x);rejects(()=>outer.runFrame(),expected);
    for(let i=0;i<4;i++) equal(x.massPreparation.teamCounts[i],i===0 && (fault==='duplicate' || fault==='interior') ? 1 : 0,
      'metadata admission follows clears; later bad physical row preserves earlier genuine append');
  }
  for(const key of ['byte208','byte209','byte20a','byte20b','byte20A','byte20B','521','522','523']) {
    const x=make();Reflect.set(x.massHost,key,7);
    const {scheduler,outer}=setup(x);rejects(()=>outer.runFrame(),'competing source cell');
    equal(x.massHost.sourceArrowMass204,73,'Borg raw208 alias refuses before first204 reset');
    equal(x.sourceActor.mass208,79,'actual208 is not overwritten when another owner claims its bytes');
    for(let i=0;i<4;i++) equal(x.massPreparation.teamCounts[i],0,'completed list/count clears remain');
    closed(x,scheduler,outer);
  }
  for(const fault of ['attributes-missing','attributes-copy','null4ac','missing98','actual204','actual18','borg208-shadow'] as const) {
    const x=make();let expected='';
    if(fault==='attributes-missing') {Reflect.deleteProperty(x.massPreparation,'attributes');expected='own data';}
    if(fault==='attributes-copy') {x.massPreparation.attributes={...x.attributes};expected='same genuine4ac';}
    if(fault==='null4ac') {x.attributes.getActorBinding(x.actor).parameter4ac=null;expected='null4ac';}
    if(fault==='missing98') {omitMassParameter(x);expected='field98: own data';}
    if(fault==='actual204') {Reflect.set(x.sourceActor,'sourceArrowMass204',10);expected='competing source cell';}
    if(fault==='actual18') {Reflect.set(x.sourceActor,'lifecycle18',1);expected='competing source cell';}
    if(fault==='borg208-shadow') {Reflect.set(x.massHost,'mass208',100);expected='competing source cell';}
    const {scheduler,outer}=setup(x);rejects(()=>outer.runFrame(),expected);closed(x,scheduler,outer);
  }
  for(const fault of ['counts-pointers','pointers-slots','data-counts','physical-pointers'] as const) {
    const x=make();
    if(fault==='counts-pointers') Reflect.set(x.massPreparation,'teamCounts',x.massPreparation.teamPointers);
    if(fault==='pointers-slots') Reflect.set(x.massPreparation,'teamPointers',x.actorSlots);
    if(fault==='data-counts') Reflect.set(x.massPreparation,'data',x.massPreparation.teamCounts);
    if(fault==='physical-pointers') Reflect.set(x.massPreparation,'physicalBlock',x.massPreparation.teamPointers);
    const {outer}=setup(x);rejects(()=>outer.runFrame(),'source storage alias');
  }
  {
    const x=make(),{scheduler,outer}=setup(x);let reentered=false;
    observe(()=>rejects(()=>outer.runFrame(),'caught same-runtime reentry'),(owner,key)=>{
      if(owner===x.massHost && key==='sourceArrowMass204' && !reentered) {
        reentered=true;rejects(()=>outer.runFrame(),'same-runtime reentry');
      }
    });
    check(reentered,'caught reentry reached first204 store preflight');
    equal(x.massHost.sourceArrowMass204,73,'poisoned reentry prevents interrupted store');
    closed(x,scheduler,outer);
  }
  {
    const x=make(),{outer}=setup(x,false);rejects(()=>outer.runFrame(),'mandatory80053b30');
    equal(x.massHost.sourceArrowMass204,73,'ordinary missing mass ingress retains old boundary');
    equal(x.massPreparation.teamCounts[0],91,'old route does not clear explicit unused mass ingress');
  }
  console.log('[battle-mass-preparation] PASS: authenticated clear/source-store order, all38 store-fault prefixes, genuine borrowed204/4ac/stage owners, signed byte branches and fresh unsigned18, finite float32/threshold/signed-zero/overflow, distinct physical rows and six live repeated-pointer additions, exact1e4/55fc bounds and permanent graph closure; bounded synthetic inputs only, no retail hydration, scheduler, passenger/RNG success, or successful frame claim');
}
