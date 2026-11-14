import {createSourceActorSlotStatusRuntime, isSourceActorSlotStatusRuntime,
  type SourceActorPlayerSlotRecord, type SourceActorSlotStatusSources} from './actor-slot-status.js';
import {createSourceObjectSchedulerRuntime, requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {createSourceBattleOuterFrameRuntime, type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle, isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit synthetic current cells joined to the genuine action/admission,
 * spawn/allocator/root/scheduler graph. No callee, successful return, actor
 * binding or live pointer is replaced. Dispatch words are independent test
 * evidence; these are not source initializer defaults or retail hydration. */
type Fixture=ReturnType<typeof createBattleTargetPreparationTestFixture>;
type Make=()=>Fixture;
const DISPATCH: readonly number[]=[0x800105ac,0x800105ac,0x80010570,0x80010578,0x80010580,
  0x80010588,0x80010590,0x80010598,0x800105a0,0x800105a8];
const RESULTS: readonly number[]=[0,0,1,2,4,8,16,32,64,128];
function check(ok: boolean,why: string): void {if(!ok) throw Error(`[actor-slot-status-test] ${why}`);}
function equal(actual: unknown,expected: unknown,why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: ()=>unknown,fragment: string): string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);return message;
}
/** Descriptor observation/fault injection, never runtime method substitution. */
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
  const dispatch3938: Record<number,number>={};DISPATCH.forEach((value,index)=>{dispatch3938[index]=value;});
  const slotStatusSources: SourceActorSlotStatusSources={scheduler,slotRecords,dispatch3938};
  const slotStatus=createSourceActorSlotStatusRuntime(slotStatusSources);
  // The exact source passed at action construction is completed only AFTER
  // its real scheduler exists. The action runtime and its binding are retained.
  x.actionRequestSources.slotStatus=slotStatus;
  Object.assign(x.sourceActor,{byte43d:10,slot:0,housekeeping73f:0,inputEdge5d4:0});
  x.targetAction.byte7d2=0;x.targetAction.byte73c=0;x.header.mode4a1=0;
  const targetPreparation=Object.assign(x.targetPreparation,{slotStatus});
  return Object.assign(x,{scheduler,slotStatus,slotStatusSources,slotRecords,dispatch3938,targetPreparation});
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
  equal(reads,0,'helper/action/target never execute scheduler masks, groups or object snapshots');
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
}

function helperTests(make: Make): void {
  {
    const old=make();
    check(!Object.hasOwn(old.sourceActor,'byte43d'),'old target fixture has no invented43d byte');
    check(!Object.hasOwn(old.actionRequestSources,'slotStatus') && !Object.hasOwn(old.targetPreparation,'slotStatus'),
      'old target/action fixture retains absent helper ingress');
  }
  {
    const x=setup(make);
    equal(x.slotStatus.getSchedulerRuntime(),x.scheduler,'exact scheduler owner');
    equal(x.scheduler.getAllocatorRuntime(),x.allocator,'same allocator target domain');
    equal(x.scheduler.getRootRuntime().getSpawnRuntime().getAdmissionRuntime(),x.commandAdmission,'same retained admission');
    equal(x.commandAdmission.getActionRuntime(),x.actionRequest,'same retained action runtime');
    equal(x.actionRequest!.getSlotStatusRuntime(),x.slotStatus,'post-construction explicit helper joins same action source');
    equal(x.commandAdmission.getActionBinding(x.actor),x.targetAction,'same sealed7d2/73c owner');
    check(Object.isFrozen(x.slotStatus) && isSourceActorSlotStatusRuntime(x.slotStatus),'frozen genuine helper');
    for(const fake of [{...x.slotStatus},Object.create(x.slotStatus),{},null,undefined])
      check(!isSourceActorSlotStatusRuntime(fake),'helper brand cannot be copied/inherited');
    rejects(()=>createSourceActorSlotStatusRuntime({scheduler:x.scheduler}),'already');
    rejects(()=>createSourceActorSlotStatusRuntime({scheduler:{...x.scheduler}}),'genuine scheduler');
    noSchedulerWork(x,()=>equal(x.slotStatus.readSlot(0),0,'status index10 returns unsigned zero'));
    const owners=x.slotStatus.getRetainedStorageOwners();
    check(Object.isFrozen(owners) && owners.includes(x.slotStatusSources) && owners.includes(x.slotRecords) &&
      owners.includes(x.slotRecords[0]!) && !owners.includes(x.dispatch3938),'direct owners retain reached records only');
    check(!owners.includes(x.scheduler) && !owners.includes(x.sourceActor),'direct inventory never recursively absorbs scheduler or actor');
  }
  {
    const x=setup(make);
    for(let status=0;status<256;status++) for(const state of [0,2,255]) {
      x.sourceActor.byte43d=status;x.slotRecords[0]!.state18=state;
      const index=status%128,low=index<10?RESULTS[index]!:0;
      equal(x.slotStatus.readSlot(0),low+(state===2?0x80000000:0),`all raw43d bytes ${status}, state18 ${state}`);
    }
    for(let state=0;state<256;state++) {
      x.slotRecords[0]!.state18=state;x.sourceActor.byte43d=0;
      equal(x.slotStatus.readSlot(0),RESULTS[0]!+(state===2?0x80000000:0),`all raw per-slot states ${state}`);
    }
  }
  {
    const x=setup(make),events: string[]=[];
    x.slotRecords[0]!.state18=2;x.sourceActor.byte43d=0;
    observe(()=>equal(x.slotStatus.readSlot(0),0x80000000+RESULTS[0]!,'highbit and local OR remain unsigned'),(owner,key)=>{
      if(owner===x.slotRecords[0] && key==='state18') events.push('state18');
      if(owner===x.actorSlots && key==='0') events.push('pointer0');
      if(owner===x.sourceActor && key==='byte43d') events.push('43d');
      if(owner===x.dispatch3938 && key==='0') events.push('dispatch0');
    });
    equal(events.join(','),'state18,pointer0,43d,dispatch0','source scalar order: player state, fresh table pointer, selected actual43d, dispatch');
  }
  {
    const x=setup(make),other={byte43d:2},id=Symbol('explicit non-caller slot target');
    x.allocator.registerExternal(id,other);x.sourceActor.byte43d=255;
    equal(x.slotStatus.readSlot(0),0,'initial live table selects caller');
    x.actorSlots[0]=id;equal(x.slotStatus.readSlot(0),RESULTS[2],'fresh pointer selects allocator actual target, never caller');
    other.byte43d=131;equal(x.slotStatus.readSlot(0),RESULTS[3],'selected actor byte remains live and masked');
    x.actorSlots[0]=x.actor;equal(x.slotStatus.readSlot(0),0,'retargeting back uses live table, not cached actual');
    x.actorSlots[0]=id;
    observe(()=>equal(x.slotStatus.readSlot(0),0,'pointer is loaded after state18 mutation'),(owner,key)=>{
      if(owner===x.slotRecords[0] && key==='state18') x.actorSlots[0]=x.actor;
    });
  }
  // The high bit is accumulated, never an early return that hides bad43d,
  // missing pointers or an unauthenticated in-range switch table entry.
  for(const state of [0,2]) for(const fault of ['pointer','byte43d','dispatch'] as const) {
    const x=setup(make);x.slotRecords[0]!.state18=state;x.sourceActor.byte43d=0;
    if(fault==='pointer') x.actorSlots[0]=null;
    else if(fault==='byte43d') delete x.sourceActor.byte43d;
    else delete x.dispatch3938[0];
    rejects(()=>x.slotStatus.readSlot(0),fault==='pointer'?'nonnull':fault==='byte43d'?'byte43d: own data':'0: own data');
  }
  for(const status of [10,11,127,138,255]) {
    const x=setup(make);x.sourceActor.byte43d=status;x.slotRecords[0]!.state18=2;
    Object.defineProperty(x.slotStatusSources,'dispatch3938',{get() {throw Error('unreached table getter');},configurable:true});
    equal(x.slotStatus.readSlot(0),0x80000000,'out-of-range masked status skips dispatch owner entirely');
  }
  for(let index=0;index<10;index++) {
    const x=setup(make);x.sourceActor.byte43d=index;
    x.dispatch3938[index]=(DISPATCH[index]!+4)>>>0;
    rejects(()=>x.slotStatus.readSlot(0),'authenticated target');
    x.dispatch3938[index]=DISPATCH[index]!;
    equal(x.slotStatus.readSlot(0),RESULTS[index],'recoverable direct helper source fault does not fabricate closure');
    Object.defineProperty(x.dispatch3938,String(index),{get() {throw Error('dispatch getter invoked');},configurable:true});
    rejects(()=>x.slotStatus.readSlot(0),`${index}: own data`);
  }
  for(const slot of [-128,-1,13,127,128,255,0.5,NaN,Infinity]) {
    const x=setup(make);let scalarReads=0;
    observe(()=>rejects(()=>x.slotStatus.readSlot(slot),'slot'),(owner,key)=>{
      if(owner===x.slotRecords || owner===x.slotRecords[0] || owner===x.actorSlots ||
        (owner===x.sourceActor && key==='byte43d')) scalarReads++;
    });
    equal(scalarReads,0,'invalid signed/domain slot refuses before any indexed scalar');
  }
  for(const slot of [6,12]) {
    const x=setup(make);x.slotRecords[slot]={state18:2};let stateReads=0,pointers=0;
    observe(()=>rejects(()=>x.slotStatus.readSlot(slot),'six-word'),(owner,key)=>{
      if(owner===x.slotRecords[slot] && key==='state18') stateReads++;
      if(owner===x.actorSlots && key===String(slot)) pointers++;
    });
    equal(stateReads,1,'valid player record is read before bounded actor-table refusal');
    equal(pointers,0,'out-of-domain actor slot never invents a pointer');
  }
  for(const key of ['state18','byte43d'] as const) for(const value of [-1,256,0.5,NaN,Infinity]) {
    const x=setup(make);Reflect.set(key==='state18'?x.slotRecords[0]!:x.sourceActor,key,value);
    rejects(()=>x.slotStatus.readSlot(0),`${key}: raw unsigned`);
  }
  for(const fault of ['missing-row','missing-state','getter-state','getter-actor','interior','foreign','pointer-type'] as const) {
    const x=setup(make);
    if(fault==='missing-row') delete x.slotRecords[0];
    if(fault==='missing-state') delete x.slotRecords[0]!.state18;
    if(fault==='getter-state') Object.defineProperty(x.slotRecords[0],'state18',{get() {throw Error('state getter invoked');}});
    if(fault==='getter-actor') Object.defineProperty(x.sourceActor,'byte43d',{get() {throw Error('actor getter invoked');},configurable:true});
    if(fault==='interior') x.actorSlots[0]=x.allocator.getInteriorPointer(x.actor,4);
    if(fault==='foreign') x.actorSlots[0]=Symbol('unregistered actor');
    if(fault==='pointer-type') Reflect.set(x.actorSlots,'0',{});
    rejects(()=>x.slotStatus.readSlot(0),fault==='missing-row'?'0: own data':fault.includes('state')?'state18: own data':
      fault==='getter-actor'?'byte43d: own data':fault==='interior'?'base identity':fault==='foreign'?'unknown':'nonnull');
  }
  for(const location of ['records','row','dispatch'] as const) {
    const x=setup(make);x.sourceActor.byte43d=0;x.slotStatus.readSlot(0);
    if(location==='records') x.slotStatusSources.slotRecords={...x.slotRecords};
    if(location==='row') x.slotRecords[0]={...x.slotRecords[0]};
    if(location==='dispatch') x.slotStatusSources.dispatch3938={...x.dispatch3938};
    rejects(()=>x.slotStatus.readSlot(0),'canonical owner changed');
  }
  for(const alias of ['actual','action','world','slots','root-source'] as const) {
    const x=setup(make),owner=alias==='actual'?x.sourceActor:alias==='action'?x.targetAction:
      alias==='world'?x.header:alias==='slots'?x.actorSlots:x.rootSources;
    Reflect.set(x.slotStatusSources,'slotRecords',owner);
    rejects(()=>x.slotStatus.readSlot(0),'alias');
  }
  for(const alias of ['sources','row-is-records','dispatch-is-row','dispatch-is-records'] as const) {
    const x=setup(make);x.sourceActor.byte43d=0;
    if(alias==='sources') Reflect.set(x.slotStatusSources,'slotRecords',x.slotStatusSources);
    if(alias==='row-is-records') Reflect.set(x.slotRecords,'0',x.slotRecords);
    if(alias==='dispatch-is-row') Reflect.set(x.slotStatusSources,'dispatch3938',x.slotRecords[0]);
    if(alias==='dispatch-is-records') Reflect.set(x.slotStatusSources,'dispatch3938',x.slotRecords);
    rejects(()=>x.slotStatus.readSlot(0),'alias');
  }
  {
    const first=setup(make),second=setup(make);first.slotStatus.readSlot(0);
    second.slotStatusSources.slotRecords=first.slotRecords;
    rejects(()=>second.slotStatus.readSlot(0),'already claimed');
  }
  for(const [location,key] of [['row','status18'],['row','24'],['actor','status43d'],['actor','byte43D'],['actor','1085']] as const) {
    const x=setup(make);let getterCalls=0;
    Object.defineProperty(location==='row'?x.slotRecords[0]!:x.sourceActor,key,{get() {getterCalls++;throw Error('alias getter invoked');}});
    rejects(()=>x.slotStatus.readSlot(0),'competing');equal(getterCalls,0,'shadow aliases rejected by descriptor presence');
  }
  for(const location of ['state','pointer','actor','dispatch'] as const) {
    const x=setup(make);x.sourceActor.byte43d=0;let entered=false;
    observe(()=>rejects(()=>x.slotStatus.readSlot(0),'caught same-runtime reentry'),(owner,key)=>{
      const reached=location==='state'?owner===x.slotRecords[0]&&key==='state18':
        location==='pointer'?owner===x.actorSlots&&key==='0':location==='actor'?owner===x.sourceActor&&key==='byte43d':
          owner===x.dispatch3938&&key==='0';
      if(reached && !entered) {entered=true;rejects(()=>x.slotStatus.readSlot(0),'same-runtime reentry');}
    });
    check(entered,`same-helper caught reentry at ${location} poisons enclosing read`);
  }
}

function actionTests(make: Make): void {
  {
    const x=setup(make),id=Symbol('non-caller action status target'),actual={byte43d:2};
    x.allocator.registerExternal(id,actual);x.actorSlots[0]=id;x.sourceActor.byte43d=NaN;x.sourceActor.inputEdge5d4=4;
    x.actionRequest!.updateActor(x.actor);equal(x.targetAction.byte73c,0,'action helper reads selected allocator target, not caller43d');
    actual.byte43d=10;x.actionRequest!.updateActor(x.actor);
    equal(x.targetAction.byte73c,2,'same live retargeted actor can unblock action input on next call');
  }
  {
    const x=setup(make),action=x.actionRequest!;
    // Exhaustive low-byte combinations independently select source priority.
    for(const edges of [...Array.from({length:256},(_,i)=>i),...Array.from({length:32},(_,i)=>2**i),
      0xffffffff,0xffffffe3,0x80000000,0x8000001c]) {
      x.targetAction.byte73c=0;x.sourceActor.inputEdge5d4=edges;
      const expected=Math.floor(edges/4)%2===1?2:Math.floor(edges/8)%2===1?3:Math.floor(edges/16)%2===1?5:0;
      let reads=0;
      observe(()=>equal(action.updateActor(x.actor),undefined,'genuine zero4a1 action return'),(owner,key)=>{
        if(owner===x.sourceActor && key==='inputEdge5d4') reads++;
      });
      equal(reads,1,'zero helper result loads inputEdge5d4 exactly once');
      equal(x.targetAction.byte73c,expected,`request priority4→2,8→3,10→5 for ${edges}`);
      equal(x.sourceActor.inputEdge5d4,edges,'action consumer never rewrites canonical input edges');
    }
    noSchedulerWork(x,()=>{x.targetAction.byte73c=0;action.updateActor(x.actor);});
  }
  for(const status of [2,3,4,5,6,7,8,9,130,137]) {
    const x=setup(make);x.sourceActor.byte43d=status;x.sourceActor.inputEdge5d4=NaN;
    let reads=0;
    observe(()=>x.actionRequest!.updateActor(x.actor),(owner,key)=>{if(owner===x.sourceActor && key==='inputEdge5d4') reads++;});
    equal(reads,0,'nonzero helper mask returns before inputEdge5d4');
    equal(x.targetAction.byte73c,0,'nonzero helper mask preserves request');
  }
  {
    const x=setup(make);x.slotRecords[0]!.state18=2;x.sourceActor.inputEdge5d4=NaN;
    x.actionRequest!.updateActor(x.actor);equal(x.targetAction.byte73c,0,'unsigned highbit helper result inhibits action input');
  }
  for(const status of [0,1,10,127,128,129,255]) {
    const x=setup(make);x.sourceActor.byte43d=status;x.sourceActor.inputEdge5d4=0x1c;
    x.actionRequest!.updateActor(x.actor);equal(x.targetAction.byte73c,2,'all helper-zero dispatch/default branches reach priority4');
  }
  {
    const x=setup(make),events: string[]=[];x.sourceActor.byte43d=0;x.sourceActor.inputEdge5d4=0x1c;
    observe(()=>x.actionRequest!.updateActor(x.actor),(owner,key)=>{
      if(owner===x.sourceActor && ['slot','byte43d','inputEdge5d4'].includes(String(key))) events.push(String(key));
      if(owner===x.targetAction && key==='byte73c') events.push('73c');
      if(owner===x.slotRecords[0] && key==='state18') events.push('state18');
      if(owner===x.actorSlots && key==='0') events.push('pointer0');
      if(owner===x.dispatch3938 && key==='0') events.push('dispatch0');
    });
    equal(events.join(','),'73c,slot,state18,pointer0,byte43d,dispatch0,inputEdge5d4,73c',
      'one source edge word is loaded only after whole shared helper and before request store');
  }
  for(const edges of [0,1,2,0x20,4,8,16,28]) {
    const x=setup(make);x.sourceActor.inputEdge5d4=edges;
    Object.defineProperty(x.targetAction,'byte73c',{writable:false});
    if((edges&0x1c)!==0) rejects(()=>x.actionRequest!.updateActor(x.actor),'byte73c: non-writable');
    else x.actionRequest!.updateActor(x.actor);
    equal(x.targetAction.byte73c,0,'unselected readonly request is lazy, selected store refuses without mutation');
  }
  for(const value of [-1,0x100000000,0.5,NaN,Infinity]) {
    const x=setup(make);x.sourceActor.inputEdge5d4=value;
    rejects(()=>x.actionRequest!.updateActor(x.actor),'inputEdge5d4: unsigned integer');
    equal(x.targetAction.byte73c,0,'bad input edge has no request store');
  }
  for(const mode of [1,127,128,255]) {
    const x=setup(make);x.header.mode4a1=mode;x.sourceActor.slot=NaN;x.sourceActor.inputEdge5d4=NaN;
    let reads=0;
    observe(()=>rejects(()=>x.actionRequest!.updateActor(x.actor),'8005a34c'),(owner,key)=>{
      if((owner===x.sourceActor && ['slot','inputEdge5d4'].includes(String(key))) ||
        (owner===x.admissionState && key==='pointer508') || owner===x.slotRecords) reads++;
    });
    equal(reads,0,'nonzero4a1 preserves pointer508 boundary before slot/helper/input');
  }
  {
    const x=setup(make);
    for(let i=1;i<13;i++) x.slotRecords[i]={state18:0};
    for(let raw=0;raw<256;raw++) {
      x.sourceActor.slot=raw;x.targetAction.byte73c=0;
      if(raw<6) x.actionRequest!.updateActor(x.actor);
      else rejects(()=>x.actionRequest!.updateActor(x.actor),raw<13?'six-word':'bounded13-record');
      equal(x.targetAction.byte73c,0,'all raw slot bytes preserve source sign-extension/domain boundary');
    }
  }
  for(const fault of ['missing','copied','foreign','changed','removed'] as const) {
    const x=setup(make),other=fault==='foreign'||fault==='changed'?setup(make):undefined;
    if(fault==='changed'||fault==='removed') x.actionRequest!.getSlotStatusRuntime();
    if(fault==='missing'||fault==='removed') delete x.actionRequestSources.slotStatus;
    if(fault==='copied') x.actionRequestSources.slotStatus={...x.slotStatus};
    if(other) x.actionRequestSources.slotStatus=other.slotStatus;
    rejects(()=>x.actionRequest!.updateActor(x.actor),fault==='missing'?'80010514':fault==='copied'?'genuine':
      fault==='foreign'?'exact scheduler/action':fault==='changed'?'canonical owner changed':'canonical owner removed');
  }
  for(const location of ['state','edge','store'] as const) for(const method of ['updateActor','prepareTarget'] as const) {
    const x=setup(make);x.sourceActor.inputEdge5d4=4;let entered=false,requestReads=0;
    observe(()=>rejects(()=>x.actionRequest!.updateActor(x.actor),'caught same-runtime reentry'),(owner,key)=>{
      if(owner===x.targetAction && key==='byte73c') requestReads++;
      const reached=location==='state'?owner===x.slotRecords[0]&&key==='state18':
        location==='edge'?owner===x.sourceActor&&key==='inputEdge5d4':owner===x.targetAction&&key==='byte73c'&&requestReads===2;
      if(reached && !entered) {entered=true;rejects(()=>x.actionRequest![method](x.actor),'same-runtime reentry');}
    });
    check(entered,`action ${method} reentry reached ${location}`);
    equal(x.targetAction.byte73c,0,'caught action reentry prevents later destination store');
  }
}

function targetTests(make: Make): void {
  {
    const x=setup(make),id=Symbol('non-caller target-preparation status target'),actual={byte43d:2};
    x.allocator.registerExternal(id,actual);x.actorSlots[0]=id;x.sourceActor.byte43d=NaN;
    x.sourceActor.housekeeping73f=NaN;x.targetAction.byte73c=NaN;
    x.actionRequest!.prepareTarget(x.actor);
    equal(x.targetAction.byte73c,NaN,'target helper uses live allocator target and returns before caller request');
  }
  {
    const x=setup(make),action=x.actionRequest!;
    x.targetAction.byte7d2=NaN;x.header.mode4a1=NaN;x.sourceActor.inputEdge5d4=NaN;
    for(let raw=0;raw<256;raw++) {
      x.targetAction.byte73c=raw;
      if(raw<=1 || raw>=128) equal(action.prepareTarget(x.actor),undefined,'signed73c<=1 genuine target early return');
      else rejects(()=>action.prepareTarget(x.actor),raw===4?'6b4f4':raw===5?'6b4c0':'6b544');
      equal(x.targetAction.byte73c,raw,'target prefix never rewrites request');
    }
    noSchedulerWork(x,()=>{x.targetAction.byte73c=255;action.prepareTarget(x.actor);});
  }
  for(const kind of ['mask','high','housekeeping'] as const) {
    const x=setup(make);x.targetAction.byte73c=NaN;x.sourceActor.housekeeping73f=kind==='housekeeping'?128:NaN;
    if(kind==='mask') x.sourceActor.byte43d=2;
    if(kind==='high') x.slotRecords[0]!.state18=2;
    let requests=0,housekeeping=0;
    observe(()=>x.actionRequest!.prepareTarget(x.actor),(owner,key)=>{
      if(owner===x.targetAction && key==='byte73c') requests++;
      if(owner===x.sourceActor && key==='housekeeping73f') housekeeping++;
    });
    equal(requests,0,'earlier helper/housekeeping target return never reads73c');
    equal(housekeeping,kind==='housekeeping'?1:0,'target helper return precedes housekeeping scalar');
  }
  {
    const x=setup(make),events: string[]=[];
    observe(()=>x.actionRequest!.prepareTarget(x.actor),(owner,key)=>{
      if(owner===x.sourceActor && ['slot','byte43d','housekeeping73f','inputEdge5d4'].includes(String(key))) events.push(String(key));
      if(owner===x.slotRecords[0] && key==='state18') events.push('state18');
      if(owner===x.actorSlots && key==='0') events.push('pointer0');
      if(owner===x.targetAction && ['byte73c','byte7d2'].includes(String(key))) events.push(String(key));
    });
    equal(events.join(','),'slot,state18,pointer0,byte43d,housekeeping73f,byte73c',
      'target prefix uses helper, housekeeping, signed request; no7d2 or input-edge read');
  }
  for(const request of [2,3,4,5,6,127]) {
    const x=setup(make);x.targetAction.byte73c=request;let reads=0;
    for(const key of ['pointer6e0','byte73d']) Object.defineProperty(x.sourceActor,key,{get() {throw Error('unsupported target getter');},configurable:true});
    observe(()=>rejects(()=>x.actionRequest!.prepareTarget(x.actor),request===4?'pointer6e0':request===5?'pointer508':request<4?'byte73d':'saved-register'),(owner,key)=>{
      if((owner===x.sourceActor && ['pointer6e0','byte73d','inputEdge5d4'].includes(String(key))) ||
        (owner===x.admissionState && key==='pointer508')) reads++;
    });
    equal(reads,0,'active target request refuses before its first branch-specific unsupported scalar');
  }
  for(const kind of ['helper-mask','helper-high','housekeeping','request0','request1','request128','request255'] as const) {
    const x=setup(make);const {frame}=outer(x);
    if(kind==='helper-mask') x.sourceActor.byte43d=2;
    if(kind==='helper-high') x.slotRecords[0]!.state18=2;
    if(kind==='housekeeping') x.sourceActor.housekeeping73f=255;
    if(kind==='request1') x.targetAction.byte73c=1;
    if(kind==='request128') x.targetAction.byte73c=128;
    if(kind==='request255') x.targetAction.byte73c=255;
    noSchedulerWork(x,()=>rejects(()=>frame.runFrame(),'8006b7f4'));
    for(const key of ['byte58a','byte58b','byte58c','byte58d','byte7d3'] as const)
      equal(x.sourceActor[key],0,'new target helper retains earlier ordered target clears');
    equal(x.targetAction.byte7d2,0,'new target helper retains same genuine7d2 clear');
    equal(x.massPreparation.orderCount.count80436260,6,'new helper follows whole mass ordering');
    equal(x.massHost.sourceArrowMass204,1200,'new helper retains earlier mass update');
    closed(x,frame);
  }
  for(const request of [2,3,4,5,6,127]) {
    const x=setup(make);x.targetAction.byte73c=request;const {frame}=outer(x);
    rejects(()=>frame.runFrame(),request===4?'6b4f4':request===5?'6b4c0':'6b544');closed(x,frame);
  }
  {
    const x=setup(make),id=Symbol('late live external helper target'),actual={byte43d:2};
    x.allocator.registerExternal(id,actual);const {frame}=outer(x);let retargeted=false;
    x.sourceActor.byte43d=NaN;
    observe(()=>rejects(()=>frame.runFrame(),'8006b7f4'),(owner,key)=>{
      if(owner===x.slotRecords[0] && key==='state18') {retargeted=true;x.actorSlots[0]=id;}
    });
    check(retargeted,'outer reaches real helper after physical traversal and mass work');
    equal(x.actorSlots[0],id,'helper uses live pointer changed after physical second-pass base was captured');
    closed(x,frame);
  }
  for(const fault of ['no-target-helper','no-action-helper','copied-helper','foreign-helper'] as const) {
    const x=setup(make),other=fault==='foreign-helper'?setup(make):undefined;
    if(fault==='no-target-helper') Reflect.deleteProperty(x.targetPreparation,'slotStatus');
    if(fault==='no-action-helper') delete x.actionRequestSources.slotStatus;
    if(fault==='copied-helper') x.targetPreparation.slotStatus={...x.slotStatus};
    if(other) x.targetPreparation.slotStatus=other.slotStatus;
    const {frame}=outer(x);
    rejects(()=>frame.runFrame(),fault==='no-target-helper'?'mandatory8006b450':'exact shared');closed(x,frame);
  }
  {
    const x=setup(make),{frame}=outer(x);rejects(()=>frame.runFrame(),'8006b7f4');
    x.sourceActor.inputEdge5d4=4;let edges=0;
    observe(()=>{
      rejects(()=>x.actionRequest!.updateActor(x.actor),'incomplete');
      rejects(()=>x.actionRequest!.prepareTarget(x.actor),'incomplete');
    },(owner,key)=>{if(owner===x.sourceActor && key==='inputEdge5d4') edges++;});
    equal(edges,0,'permanently closed allocator prevents newly supported action input continuation');
    equal(x.targetAction.byte73c,0,'preclosed action cannot write request2');
    // A read-only helper is not scheduler execution; closure must be checked
    // by the genuine action graph rather than an invented helper capability.
    equal(x.slotStatus.readSlot(0),0,'direct readonly slot helper acquires no frame authority');
    closed(x,frame);
  }
  {
    const x=setup(make);x.sourceActor.inputEdge5d4=4;
    Reflect.deleteProperty(x.targetPreparation,'slotStatus');const {frame}=outer(x);
    let injected=false,edges=0;
    observe(()=>rejects(()=>x.actionRequest!.updateActor(x.actor),'incomplete'),(owner,key)=>{
      if(owner===x.sourceActor && key==='inputEdge5d4') edges++;
      if(!injected && owner===x.slotRecords[0] && key==='state18') {
        injected=true;
        // The genuine outer closes while the helper is reading. Its missing
        // optional target ingress refuses before any reentrant action method.
        rejects(()=>frame.runFrame(),'mandatory8006b450');
      }
    });
    check(injected,'closure was injected during real helper state18 read');
    equal(edges,0,'post-helper same-allocator completion guard prevents input consumption');
    equal(x.targetAction.byte73c,0,'close-during-helper cannot write request2');
    closed(x,frame);
  }
  for(const location of ['edge','destination'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);x.sourceActor.inputEdge5d4=4;
    Reflect.deleteProperty(x.targetPreparation,'slotStatus');const {frame}=outer(x);
    let injected=false,edges=0,requests=0;
    const inject=(owner: object,key: PropertyKey): void=>{
      if(owner===x.sourceActor && key==='inputEdge5d4') edges++;
      if(owner===x.targetAction && key==='byte73c') requests++;
      const reached=location==='edge'?owner===x.sourceActor&&key==='inputEdge5d4':
        owner===x.targetAction&&key==='byte73c'&&requests===2;
      if(!injected && reached) {
        injected=true;
        // No mocked completion or direct incomplete flag: the real outer
        // retains its mass/clear prefix and permanently closes the graph.
        rejects(()=>frame.runFrame(),'mandatory8006b450');
      }
    };
    observe(()=>rejects(()=>x.actionRequest!.updateActor(x.actor),'incomplete'),
      phase==='before'?inject:()=>{},phase==='after'?inject:undefined);
    check(injected,`${phase} ${location} descriptor reaches the late closure window`);
    equal(edges,1,'late closure occurs after the shared helper and at the sole source edge load');
    equal(requests,location==='edge'?1:2,'edge closure stops before destination preflight; destination closure reaches it once');
    equal(x.targetAction.byte73c,0,`${phase} ${location} closure cannot leak the reached request2 store`);
    equal(x.massPreparation.orderCount.count80436260,6,'nested outer mass prefix is retained without rollback');
    closed(x,frame);
  }
  for(const location of ['state','actor','housekeeping','request'] as const) {
    const x=setup(make),{frame}=outer(x);let entered=false,target=false;
    observe(()=>rejects(()=>frame.runFrame(),'caught same-runtime reentry'),(owner,key)=>{
      if(owner===x.slotRecords[0] && key==='state18') target=true;
      const reached=location==='state'?owner===x.slotRecords[0]&&key==='state18':
        location==='actor'?owner===x.sourceActor&&key==='byte43d':
          location==='housekeeping'?owner===x.sourceActor&&key==='housekeeping73f':owner===x.targetAction&&key==='byte73c';
      if(target && reached && !entered) {entered=true;rejects(()=>frame.runFrame(),'same-runtime reentry');}
    });
    check(entered,`outer caught reentry is reached in shared target ${location}`);closed(x,frame);
  }
}

export function runActorSlotStatusSelfTests(make: Make): void {
  helperTests(make);
  actionTests(make);targetTests(make);
  console.log('[actor-slot-status] PASS: all25643d/state bytes and authentic dispatch words, fresh allocator targets and ordered lazy reads, exact shared action/scheduler graph, zero4a1 one-word input priorities and signed6b450 early returns, readonly/alias/reentry failures and permanent outer6b7f4 closure; bounded offline synthetic composition only, no source hydration, active target selection, scheduler run or full-frame claim');
}
