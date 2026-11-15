import {createSourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle,
  isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {SourceBattleOuterFrameTestFixture} from './battle-outer-frame.selftest.js';

type Make=()=>SourceBattleOuterFrameTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const normal='80029458 reached mandatory80053b30',paused='byte40: own data property required',
  zero='byteEB: own data property required';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-team-refresh-leaf-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {
  let message='';try{run();}catch(error){message=String(error);}
  check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;
}
function fixture(make:Make,value:unknown=1,burstRows:readonly number[]=[0]) {
  const x=make();Reflect.set(x.matchGlobals,'byteD9',value);
  x.matchGlobals.activeMask=15;x.matchGlobals.slotTeam=[0,1,2,3,0,0];
  for(const index of burstRows)x.teamRows103[index]!.byte10=128;
  const scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources),sources={scheduler,systemGlobals:x.systemGlobals};
  const outer=createSourceBattleOuterFrameRuntime(sources);
  return Object.assign(x,{scheduler,sources,outer});
}
type Fixture=ReturnType<typeof fixture>;
function observe(x:Fixture,expected:string,before:Visit=()=>{},after?:Visit) {
  const native=Object.getOwnPropertyDescriptor,events:string[]=[];let leafReads=0,schedulerReads=0;
  const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    const row=x.teamRows103.indexOf(owner as Fixture['teamRows103'][number]);
    if(owner===x.matchGlobals&&key==='byteD9'){events.push('leaf');leafReads++;}
    if(owner===x.matchGlobals&&key==='byte66')events.push('mode');
    if(row>=0&&['byte1','byte10','charged','meter','threshold30'].includes(String(key)))events.push(`r${row}.${String(key)}`);
    if(((owner===x.objectBytes||owner===x.nextObjectBytes||owner===x.actorSlots||owner===x.groups)&&/^\d+$/.test(String(key)))||
      owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
    before(owner,key);const result=native(owner,key);after?.(owner,key);return result;
  }) as typeof native;
  let message='';try{message=refuses(()=>x.outer.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
  equal(schedulerReads,0,'no scheduler traversal or snapshots');
  equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no actor frame claim');
  return {events,leafReads,message};
}
function refreshed(x:Fixture,index:number,charged:boolean):void {
  const row=x.teamRows103[index]!;
  equal(row.byte1,1,'one matching participant');equal(row.byte2,0,'no selected controllers');equal(row.byte3,1<<index,'row membership');
  equal(row.byte4,index,'ordered compact slot');for(let i=5;i<=9;i++)equal(Reflect.get(row,`byte${i}`),255,'remaining slots cleared');
  equal(row.charged,charged,'charged result');
}
function laterUntouched(x:Fixture,index:number):void {
  for(const row of x.teamRows103.slice(index+1)) {
    for(let i=1;i<=9;i++)equal(Reflect.get(row,`byte${i}`),90+i,'later row has no refresh stores');
    equal(row.charged,true,'later row charged untouched');
  }
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal closes retained actor');
  refuses(()=>x.outer.runFrame(),'permanently incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])
    refuses(run,'exclusively owned');
  refuses(()=>x.projectiles.assertActorComplete(x.actor),'incomplete');
  refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function branches(make:Make):void {
  for(const value of [1,2,127,128,254,255])for(const burstRow of [0,1,2,3]) {
    const x=fixture(make,value,[burstRow]),row=x.teamRows103[burstRow]!;let getters=0;
    for(const key of ['meter','threshold30','half18','half1a'])Object.defineProperty(row,key,{get(){getters++;throw Error('unreached suffix');},configurable:true});
    const result=observe(x,normal);equal(result.leafReads,1,'one reached unsigned leaf load');
    for(let i=0;i<4;i++)refreshed(x,i,false);
    equal(getters,0,'nonzero leaf skips all current-row charge/timer fields');closed(x);
  }
  for(const mode of [0,1,128,255]) {
    const x=fixture(make,255,[0,1,2,3]);x.matchGlobals.byte66=mode;
    const result=observe(x,mode===0?normal:paused);
    equal(result.leafReads,4,'each burst row gets a fresh leaf read');
    equal(result.events.filter(event=>event==='leaf'||event==='mode'||event.endsWith('.charged')).join(','),
      [0,1,2,3].flatMap(i=>[`r${i}.charged`,`r${i}.charged`,'leaf']).concat('mode').join(','),
      'clear/load/full-word branch each row, final mode only after every row');
    for(let i=0;i<4;i++)refreshed(x,i,false);closed(x);
  }
  for(const value of [0,-0])for(const row of [0,1,2,3]) {
    const x=fixture(make,value,[row]);const result=observe(x,zero);
    equal(result.leafReads,1,'zero still invokes exact unsigned leaf once');
    for(let i=0;i<=row;i++)refreshed(x,i,false);laterUntouched(x,row);
    equal(result.events.at(-1),'leaf','zero stops before timer, meter, later row or mode');closed(x);
  }
  {const x=fixture(make,1);Object.defineProperty(x.matchGlobals,'byteD9',{writable:false});observe(x,normal);closed(x);}
  for(const populated of [false,true]) {
    const x=fixture(make,undefined,populated?[]:[0,1,2,3]);if(!populated)x.matchGlobals.activeMask=0;
    let called=0;Object.defineProperty(x.matchGlobals,'byteD9',{get(){called++;throw Error('unreached leaf');},configurable:true});
    Reflect.set(x.matchGlobals,'fieldD9',1);
    equal(observe(x,normal).leafReads,0,'empty/nonburst rows do not demand leaf storage');equal(called,0,'unreached accessor stays lazy');closed(x);
  }
}
function captures(make:Make):void {
  {const x=fixture(make,1,[0,1,2,3]);let loads=0;
    const r=observe(x,zero,()=>{},(owner,key)=>{if(owner===x.matchGlobals&&key==='byteD9'&&++loads===2)Reflect.set(owner,key,0);});
    equal(r.leafReads,3,'second captured nonzero returns, third row reloads new zero');
    for(let i=0;i<3;i++)refreshed(x,i,false);laterUntouched(x,2);closed(x);}
  {const x=fixture(make,0,[0,1]);let hit=false;
    observe(x,zero,()=>{},(owner,key)=>{if(owner===x.matchGlobals&&key==='byteD9'){hit=true;Reflect.set(owner,key,255);}});
    check(hit,'zero value captured before mutation');refreshed(x,0,false);laterUntouched(x,0);closed(x);}
  {const x=fixture(make,1,[0,2]),row=x.teamRows103[1]!;row.meter=9;row.threshold30=9;
    observe(x,normal);refreshed(x,0,false);refreshed(x,1,true);refreshed(x,2,false);refreshed(x,3,false);closed(x);}
}
function faults(make:Make):void {
  for(const bad of [undefined,-1,256,1.5,NaN,Infinity,-Infinity,'1',null,1n]) {
    const x=fixture(make,bad);Reflect.set(x.matchGlobals,'byteD9',bad);equal(observe(x,'byteD9: raw unsigned').leafReads,1,'invalid reached leaf attempted once');
    refreshed(x,0,false);laterUntouched(x,0);closed(x);
  }
  for(const kind of ['missing','inherited','accessor']) {
    const x=fixture(make);let calls=0;Reflect.deleteProperty(x.matchGlobals,'byteD9');
    if(kind==='inherited')Object.setPrototypeOf(x.matchGlobals,{byteD9:1});
    if(kind==='accessor')Object.defineProperty(x.matchGlobals,'byteD9',{get(){calls++;return 1;},configurable:true});
    observe(x,'byteD9: own data');equal(calls,0,'leaf accessor is not invoked');refreshed(x,0,false);laterUntouched(x,0);closed(x);
  }
  for(const shadow of ['byted9','byte0d9','byte0D9','fieldD9','fieldd9','globalD9','globald9','217','byteD9']) {
    const x=fixture(make);let calls=0;
    Object.defineProperty(shadow==='byteD9'?x.sourceActor:x.matchGlobals,shadow,{get(){calls++;return 1;},configurable:true});
    observe(x,'competing source cell owner');equal(calls,0,'shadow accessors never invoked');refreshed(x,0,false);laterUntouched(x,0);closed(x);
  }
  for(const kind of ['delete','accessor','readonly','nonboolean']) {
    const x=fixture(make),row=x.teamRows103[0]!;let checks=0,calls=0;
    const r=observe(x,'charged: live',()=>{},(owner,key)=>{
      if(owner!==row||key!=='charged'||++checks!==2)return;
      if(kind==='delete')Reflect.deleteProperty(row,'charged');
      if(kind==='accessor')Object.defineProperty(row,'charged',{get(){calls++;return true;},set(){calls++;},configurable:true});
      if(kind==='readonly')Object.defineProperty(row,'charged',{writable:false});
      if(kind==='nonboolean')Reflect.set(row,'charged',1);
    });
    equal(checks,2,'mutation after final observable charged descriptor capture');equal(r.leafReads,0,'failed clear precedes leaf');
    equal(calls,0,'late charged getter/setter never invoked');equal(row.byte4,0,'prior roster survives failed clear');laterUntouched(x,0);closed(x);
  }
}
function terminalMetadata(make:Make):void {
  for(const kind of ['global-alias','actor-alias','nested-alias','scheduler','table','row','slots','system','delete','accessor','invalid','lifecycle','reentry']) {
    const x=fixture(make);let leaf=false,checks=0,hits=0,calls=0;
    const expected=kind.includes('alias')?'competing':kind==='lifecycle'?'incomplete':kind==='reentry'?'reentry':
      kind==='delete'||kind==='accessor'?'byteD9: terminal own data':kind==='invalid'?'byteD9: raw unsigned':'owner changed';
    const result=observe(x,expected,()=>{},(owner,key)=>{
      if(owner===x.matchGlobals&&key==='byteD9')leaf=true;
      // The second inventory's actorSlots descriptor follows the final public
      // alias walk. Mutate after its descriptor was captured: only the final
      // native metadata pass can catch it without another observable walk.
      if(!leaf||owner!==x.schedulerSources||key!=='actorSlots'||++checks!==2)return;
      hits++;
      if(kind==='global-alias')Reflect.set(x.matchGlobals,'217',1);
      if(kind==='actor-alias')Reflect.set(x.sourceActor,'byteD9',1);
      if(kind==='nested-alias')Reflect.set(x.schedulerSources,'lateOwner',{byteD9:1});
      if(kind==='scheduler')x.sources.scheduler={...x.scheduler};
      if(kind==='table')x.matchGlobals.teamRows103=[...x.teamRows103];
      if(kind==='row')x.teamRows103[0]={...x.teamRows103[0]!};
      if(kind==='slots')x.matchGlobals.slotTeam=[...x.matchGlobals.slotTeam];
      if(kind==='system')x.sources.systemGlobals={...x.systemGlobals};
      if(kind==='delete')Reflect.deleteProperty(x.matchGlobals,'byteD9');
      if(kind==='accessor')Object.defineProperty(x.matchGlobals,'byteD9',{get(){calls++;return 1;},configurable:true});
      if(kind==='invalid')Reflect.set(x.matchGlobals,'byteD9',256);
      if(kind==='lifecycle')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
      if(kind==='reentry')refuses(()=>x.outer.runFrame(),'same-runtime reentry');
    });
    equal(hits,1,'one fault at final observable metadata check');equal(checks,2,'no later observable inventory walk');
    equal(result.leafReads,1,'only one source leaf read');equal(calls,0,'terminal descriptor check never invokes getter');
    refreshed(x,0,false);laterUntouched(x,0);closed(x);
  }
  for(const kind of ['alias','lifecycle','reentry','delete','accessor']) {
    const x=fixture(make);let hits=0,calls=0;
    const expected=kind==='alias'?'competing':kind==='lifecycle'?'incomplete':kind==='reentry'?'reentry':'byteD9: terminal own data';
    observe(x,expected,()=>{},(owner,key)=>{
      if(owner!==x.matchGlobals||key!=='byteD9')return;hits++;
      if(kind==='alias')Reflect.set(owner,'fieldD9',1);
      if(kind==='lifecycle')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
      if(kind==='reentry')refuses(()=>x.outer.runFrame(),'same-runtime reentry');
      if(kind==='delete')Reflect.deleteProperty(owner,'byteD9');
      if(kind==='accessor')Object.defineProperty(owner,'byteD9',{get(){calls++;return 1;},configurable:true});
    });
    equal(hits,1,'fault after captured source descriptor');equal(calls,0,'getter not invoked');refreshed(x,0,false);laterUntouched(x,0);closed(x);
  }
}
export function runBattleTeamRefreshLeafSelfTests(make:Make):void {
  let count=0;const counted=()=>{count++;return make();};
  branches(counted);captures(counted);faults(counted);terminalMetadata(counted);
  console.log(`[battle-team-refresh-leaf] PASS (${count} genuine shared-graph fixtures): fresh canonical unsigned byteD9, ordered charged clears, nonzero later-row continuation and zero requires explicit8b480 byteEB, lazy/captured loads, final metadata mutations, alias/lifecycle/reentry closure; no supplied timer continuation, scheduler execution, complete frame, retail replay or browser claim`);
}
