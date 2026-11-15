import {createSourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
import {createSourceObjectSchedulerRuntime,requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle,
  isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {SourceBattleOuterFrameTestFixture} from './battle-outer-frame.selftest.js';

type Make=()=>SourceBattleOuterFrameTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const normal='80029458 reached mandatory80053b30',paused='80029464 reached mandatory8000bef4',
  positive='80029de0 reached unsupported positive burst timer floating suffix';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[battle-burst-expiry-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):string {
  let message='';try{run();}catch(error){message=String(error);}
  check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;
}
function fixture(make:Make,mask:unknown=0,timer:unknown=1,rows:readonly number[]=[0]) {
  const x=make();Object.assign(x.matchGlobals,{byteD9:0,byteEB:mask,activeMask:15,slotTeam:[0,1,2,3,0,0]});
  for(const index of rows)Object.assign(x.teamRows103[index]!,{byte10:128,half18:timer,meter:777});
  const scheduler=createSourceObjectSchedulerRuntime(x.schedulerSources),sources={scheduler,systemGlobals:x.systemGlobals};
  const outer=createSourceBattleOuterFrameRuntime(sources);
  return Object.assign(x,{scheduler,sources,outer});
}
type Fixture=ReturnType<typeof fixture>;
function observe(x:Fixture,expected:string,before:Visit=()=>{},after?:Visit) {
  const native=Object.getOwnPropertyDescriptor,events:string[]=[];let d9=0,eb=0,schedulerReads=0;
  const claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    const index=x.teamRows103.indexOf(owner as Fixture['teamRows103'][number]);
    if(owner===x.matchGlobals&&key==='byteD9'){events.push('D9');d9++;}
    if(owner===x.matchGlobals&&key==='byteEB'){events.push('EB');eb++;}
    if(owner===x.matchGlobals&&key==='byte66')events.push('mode');
    if(index>=0&&['half18','meter','byte10','threshold30','charged','byte3'].includes(String(key)))events.push(`r${index}.${String(key)}`);
    if(((owner===x.objectBytes||owner===x.nextObjectBytes||owner===x.actorSlots||owner===x.groups)&&/^\d+$/.test(String(key)))||
      owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key)))schedulerReads++;
    before(owner,key);const result=native(owner,key);after?.(owner,key);return result;
  }) as typeof native;
  let message='';try{message=refuses(()=>x.outer.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
  equal(schedulerReads,0,'no scheduler traversal/snapshots');equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no actor frame claim');
  return {events,d9,eb,message};
}
function laterUntouched(x:Fixture,index:number):void {
  for(const row of x.teamRows103.slice(index+1)) {
    for(let i=1;i<=9;i++)equal(Reflect.get(row,`byte${i}`),90+i,'later roster untouched');
    equal(row.charged,true,'later charged untouched');
  }
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes retained actor');
  refuses(()=>x.outer.runFrame(),'permanently incomplete');
  for(const run of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8),()=>x.root.dispatchStoredRoot(x.child)])
    refuses(run,'exclusively owned');
  refuses(()=>x.projectiles.assertActorComplete(x.actor),'incomplete');
  refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function branches(make:Make):void {
  for(const timer of [0,1,2,0x7ffe,0x7fff,0x8000,0x8001,0xfffe,0xffff])for(const index of [0,1,2,3]) {
    const x=fixture(make,0,timer,[index]),row=x.teamRows103[index]!,next=((timer-1)<<16)>>16;
    let getters=0;for(const key of ['half1a','threshold30','float80436f08','float80436f00'])
      Object.defineProperty(row,key,{get(){getters++;throw Error('unreached floating/charge suffix');},configurable:true});
    const r=observe(x,next>0?positive:normal);
    equal(Reflect.get(row,'half18'),next&65535,'signed decrement with low16 store');equal(row.charged,false,'ordered charged clear');
    equal(row.meter,next>0?777:0,'expiry first/last meter stores');equal(row.byte10,next>0?128:0,'expiry burst clear');
    equal(r.d9,1,'one D9 leaf');equal(r.eb,1,'one EB leaf');equal(getters,0,'unsupported suffix never read');
    const tail=r.events.slice(r.events.indexOf('EB')+1).filter(e=>e.startsWith(`r${index}.`));
    equal(tail.join(','),[`r${index}.half18`,`r${index}.half18`,...(next>0?[]:[`r${index}.meter`,`r${index}.byte10`,`r${index}.meter`])].join(','),
      'EB0 skips row3; exact timer load/store and two distinct meter stores');
    if(next>0)laterUntouched(x,index);else for(const item of x.teamRows103)equal(item.byte1,1,'later rows refresh');closed(x);
  }
  for(const mask of [1,2,4,8,32,64,128,255])for(const rowMask of [0,1,2,0x80,0xff]) {
    const overlap=(mask&(rowMask<<24>>24))!==0,x=fixture(make,mask),row=x.teamRows103[0]!;let getters=0;
    if(!overlap)for(const key of ['half18','meter','threshold30'])Object.defineProperty(row,key,{get(){getters++;throw Error('skipped timer');},configurable:true});
    const r=observe(x,normal,()=>{},(owner,key)=>{if(owner===x.matchGlobals&&key==='byteEB')row.byte3=rowMask;});
    equal(row.byte10,overlap?0:128,'source lbz return AND signed row mask');equal(r.eb,1,'one captured EB');
    equal(r.events.slice(r.events.indexOf('EB')+1).filter(e=>e==='r0.byte3').length,1,'nonzero EB reads row3 once');
    equal(getters,0,'nonoverlap timer remains lazy');closed(x);
  }
  for(const mode of [0,1,128,255]) {
    const x=fixture(make,0,1,[0,1,2,3]);x.matchGlobals.byte66=mode;
    const r=observe(x,mode?paused:normal);equal(r.d9,4,'fresh D9 every burst');equal(r.eb,4,'fresh EB every zero D9');
    equal(r.events.at(-1),'mode','mode read only after all rows');for(const row of x.teamRows103){equal(row.byte10,0,'all expire');equal(row.meter,0,'all cleared');}closed(x);
  }
  for(const skip of ['empty','nonburst','D9','mask']) {
    const x=fixture(make,2),row=x.teamRows103[0]!;let calls=0;
    if(skip==='empty')x.matchGlobals.activeMask=0;
    if(skip==='nonburst')row.byte10=0;
    if(skip==='D9')Reflect.set(x.matchGlobals,'byteD9',255);
    if(skip!=='mask')Object.defineProperty(x.matchGlobals,'byteEB',{get(){calls++;throw Error('unreached EB');},configurable:true});
    Object.defineProperty(row,'half18',{get(){calls++;throw Error('unreached timer');},configurable:true});
    Reflect.set(row,'short18',3);Reflect.set(x.matchGlobals,'half10c',3);
    observe(x,normal);equal(calls,0,'skipped fields and timer aliases stay lazy');closed(x);
  }
}
function captured(make:Make):void {
  {const x=fixture(make,0,1,[0,1,2,3]);let eb=0;
    const r=observe(x,normal,()=>{},(owner,key)=>{if(owner===x.matchGlobals&&key==='byteEB'&&++eb===1)Reflect.set(owner,key,1);});
    equal(r.eb,4,'fresh EB each later row');equal(x.teamRows103[0]!.byte10,0,'captured zero expires despite new mask');
    for(const row of x.teamRows103.slice(1))equal(row.byte10,128,'fresh nonoverlap mask skips later timers');closed(x);}
  {const x=fixture(make,0,1,[0,1,2,3]);let d9=0;
    const r=observe(x,normal,()=>{},(owner,key)=>{if(owner===x.matchGlobals&&key==='byteD9'&&++d9===1)Reflect.set(owner,key,255);});
    equal(r.d9,4,'D9 reloaded later');equal(r.eb,1,'captured zero reaches EB, later nonzero skips EB');closed(x);}
  {const x=fixture(make,1),row=x.teamRows103[0]!;let reads=0;
    observe(x,normal,()=>{},(owner,key)=>{if(owner===row&&key==='byte3'&&++reads===4)row.byte3=0;});
    // Refresh writes byte3 twice and reads it once; the fourth observation is the mask load.
    equal(reads,4,'one reached mask source read after roster');equal(row.byte10,0,'captured nonzero overlap survives valid mutation');closed(x);}
  for(const timer of [1,2,0x8000]) {
    const x=fixture(make,0,timer),row=x.teamRows103[0]!;let hits=0;
    observe(x,timer===1?normal:positive,()=>{},(owner,key)=>{if(owner===row&&key==='half18'&&++hits===1)Reflect.set(row,'half18',77);});
    equal(Reflect.get(row,'half18'),(timer-1)&65535,'captured lha value determines store and branch');closed(x);
  }
}
function faults(make:Make):void {
  for(const key of ['byteEB','half18'])for(const bad of [undefined,-1,65536,1.5,NaN,Infinity,-Infinity,'1',null,1n,...(key==='byteEB'?[256]:[])]) {
    const x=fixture(make),row=x.teamRows103[0]!,owner=key==='byteEB'?x.matchGlobals:row;Reflect.set(owner,key,bad);
    observe(x,`${key}: raw unsigned`);equal(row.charged,false,'charged clear precedes scalar refusal');equal(row.meter,777,'no expired meter write');laterUntouched(x,0);closed(x);
  }
  for(const key of ['byteEB','half18'])for(const kind of ['missing','inherited','accessor']) {
    const x=fixture(make),owner=key==='byteEB'?x.matchGlobals:x.teamRows103[0]!;let getters=0;Reflect.deleteProperty(owner,key);
    if(kind==='inherited')Object.setPrototypeOf(owner,{[key]:1});
    if(kind==='accessor')Object.defineProperty(owner,key,{get(){getters++;return 1;},configurable:true});
    observe(x,`${key}: own data`);equal(getters,0,'accessors never called');laterUntouched(x,0);closed(x);
  }
  for(const key of ['half18','meter','byte10'])for(const occurrence of key==='meter'?[1,2]:[key==='byte10'?2:2]) {
    const x=fixture(make),row=x.teamRows103[0]!;let hits=0;
    observe(x,`${key}: non-writable`,(owner,field)=>{if(owner===row&&field===key&&++hits===occurrence)Object.defineProperty(row,key,{writable:false});});
    equal(Reflect.get(row,'half18'),key==='half18'?1:0,'completed timer store survives');
    equal(row.meter,key==='byte10'||key==='meter'&&occurrence===2?0:777,'earlier meter stores survive');
    equal(row.byte10,key==='meter'&&occurrence===2?0:128,'earlier burst clear survives');laterUntouched(x,0);closed(x);
  }
  for(const key of ['half18','meter','byte10'])for(const kind of ['delete','accessor','readonly']) {
    const x=fixture(make),row=x.teamRows103[0]!;let hits=0,calls=0;const occurrence=key==='meter'?1:2;
    observe(x,`${key}: live`,()=>{},(owner,field)=>{
      if(owner!==row||field!==key||++hits!==occurrence)return;
      if(kind==='delete')Reflect.deleteProperty(row,key);
      if(kind==='accessor')Object.defineProperty(row,key,{get(){calls++;return 1;},set(){calls++;},configurable:true});
      if(kind==='readonly')Object.defineProperty(row,key,{writable:false});
    });
    equal(calls,0,'late destination getter/setter never called');if(kind==='delete')check(!Object.hasOwn(row,key),'no missing destination recreation');
    laterUntouched(x,0);closed(x);
  }
  for(const alias of ['byteeb','byte0eb','byte0EB','fieldEB','fieldeb','globalEB','globaleb','235','byteEB',
    'short18','field18','byte18','byte19','24','25','half018','half10c','half10C','268','269','byte10c','byte10d']) {
    const x=fixture(make),row=x.teamRows103[0]!;let calls=0;
    const owner=alias==='byteEB'?x.sourceActor:['short18','field18','byte18','byte19','24','25','half018'].includes(alias)?row:x.matchGlobals;
    Object.defineProperty(owner,alias,{get(){calls++;return 1;},configurable:true});observe(x,'competing source cell owner');
    equal(calls,0,'alias getter never called');equal(row.meter,777,'alias precedes expiry writes');laterUntouched(x,0);closed(x);
  }
}
function terminal(make:Make):void {
  for(const stage of ['EB','half18','first-meter','byte10','last-meter'])for(const kind of
    ['global-alias','nested-alias','row-alias','timer-alias','scheduler','table','row','slots','system','lifecycle','reentry']) {
    const x=fixture(make),row=x.teamRows103[0]!;let armed=false,checks=0,hits=0,half=0,meter=0,burst=0;
    const expected=kind.includes('alias')?'competing':kind==='lifecycle'?'incomplete':kind==='reentry'?'reentry':'owner changed';
    observe(x,expected,()=>{},(owner,key)=>{
      if(owner===x.matchGlobals&&key==='byteEB'&&stage==='EB')armed=true;
      if(owner===row&&key==='half18'&&++half===2&&stage==='half18')armed=true;
      if(owner===row&&key==='meter'&&++meter===(stage==='last-meter'?2:1)&&stage.includes('meter'))armed=true;
      if(owner===row&&key==='byte10'&&++burst===2&&stage==='byte10')armed=true;
      if(!armed||owner!==x.schedulerSources||key!=='actorSlots'||++checks!==2)return;hits++;
      if(kind==='global-alias')Reflect.set(x.matchGlobals,'235',1);
      if(kind==='nested-alias')Reflect.set(x.schedulerSources,'lateOwner',{byteEB:1});
      if(kind==='row-alias')Reflect.set(row,'half32',1);
      if(kind==='timer-alias')Reflect.set(x.matchGlobals,stage==='EB'?'byteEB':'half10c',1);
      if(kind==='timer-alias'&&stage==='EB')Reflect.set(x.sourceActor,'byteEB',1);
      if(kind==='scheduler')x.sources.scheduler={...x.scheduler};
      if(kind==='table')x.matchGlobals.teamRows103=[...x.teamRows103];
      if(kind==='row')x.teamRows103[0]={...row};
      if(kind==='slots')x.matchGlobals.slotTeam=[...x.matchGlobals.slotTeam];
      if(kind==='system')x.sources.systemGlobals={...x.systemGlobals};
      if(kind==='lifecycle')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
      if(kind==='reentry')refuses(()=>x.outer.runFrame(),'same-runtime reentry');
    });
    equal(hits,1,'mutation after final observable inventory');equal(checks,2,'no subsequent observable inventory');
    equal(Reflect.get(row,'half18'),['EB','half18'].includes(stage)?1:0,'completed timer store retained');
    equal(row.meter,['byte10','last-meter'].includes(stage)?0:777,'completed meter writes retained');
    equal(row.byte10,stage==='last-meter'?0:128,'completed burst clear retained');laterUntouched(x,0);closed(x);
  }
  for(const stage of ['EB','half18','first-meter','byte10','last-meter'])for(const kind of ['delete','accessor','readonly','invalid']) {
    if(stage==='EB'&&kind==='readonly' || !['EB','half18'].includes(stage)&&kind==='invalid')continue;
    const x=fixture(make),row=x.teamRows103[0]!,key=stage==='EB'?'byteEB':stage==='half18'?'half18':stage==='byte10'?'byte10':'meter';
    const owner=stage==='EB'?x.matchGlobals:row;let armed=false,seen=0,checks=0,hits=0,calls=0;
    const occurrence=stage==='half18'||stage==='byte10'||stage==='last-meter'?2:1;
    const expected=kind==='invalid'?`${key}: raw unsigned`:`${key}: ${stage==='EB'?'terminal own data':'live'}`;
    observe(x,expected,()=>{},(record,field)=>{
      if(record===owner&&field===key&&++seen===occurrence)armed=true;
      if(!armed||record!==x.schedulerSources||field!=='actorSlots'||++checks!==2)return;hits++;
      if(kind==='delete')Reflect.deleteProperty(owner,key);
      if(kind==='accessor')Object.defineProperty(owner,key,{get(){calls++;return 1;},set(){calls++;},configurable:true});
      if(kind==='readonly')Object.defineProperty(owner,key,{writable:false});
      if(kind==='invalid')Reflect.set(owner,key,stage==='EB'?256:65536);
    });
    equal(hits,1,'destination/source changed at last observable inventory');equal(checks,2,'native validation has no observer callbacks');
    equal(calls,0,'final getter/setter never called');if(kind==='delete')check(!Object.hasOwn(owner,key),'final deletion not recreated');
    laterUntouched(x,0);closed(x);
  }
  {const x=fixture(make,1),row=x.teamRows103[0]!;let reads=0;
    observe(x,'byte3: raw unsigned',()=>{},(owner,key)=>{if(owner===row&&key==='byte3'&&++reads===4)row.byte3=256;});
    equal(row.meter,777,'late invalid signed mask stops before timer');closed(x);}
  {const x=fixture(make);Object.defineProperty(x.matchGlobals,'byteEB',{writable:false});observe(x,normal);closed(x);}
  for(const key of ['byteEB','half18'])for(const kind of ['delete','accessor','invalid']) {
    const x=fixture(make),owner=key==='byteEB'?x.matchGlobals:x.teamRows103[0]!;let hits=0,calls=0;
    observe(x,`${key}: ${kind==='invalid'?'raw unsigned':'terminal own data'}`,()=>{},(record,field)=>{
      if(record!==owner||field!==key||++hits!==1)return;
      if(kind==='delete')Reflect.deleteProperty(owner,key);
      if(kind==='accessor')Object.defineProperty(owner,key,{get(){calls++;return 1;},configurable:true});
      if(kind==='invalid')Reflect.set(owner,key,key==='byteEB'?256:65536);
    });equal(calls,0,'late source getter never called');laterUntouched(x,0);closed(x);
  }
}
export function runBattleBurstExpirySelfTests(make:Make):void {
  let count=0;const counted=()=>{count++;return make();};branches(counted);captured(counted);faults(counted);terminal(counted);
  console.log(`[battle-burst-expiry] PASS (${count} genuine shared-graph fixtures): fresh D9/EB, captured unsigned mask/signed row and wrapped half18 decrement, exact repeated expiry stores, positive29de0 refusal, lazy suffix, partial writes and terminal owner/alias/descriptor/lifecycle/reentry closure; no floating suffix, scheduler execution, complete frame, retail replay or browser claim`);
}
