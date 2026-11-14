import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {claimSourceHelperStorage,reserveSourcePointerStorage} from './source-storage-claims.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit synthetic inputs on the genuine allocator/HIT/selector graph.
 * Actual OBJECT+20 is nulled before the selector's final508 store. The caller
 * then executes genuine primary and secondary null direction stores. Five
 * inactive physical rows lack admission owners, so the natural next boundary
 * is third-pass row1, not fabricated27764 success or scheduler authority. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Vector={x:number;y:number;z:number};
type Visit=(owner:object,key:PropertyKey)=>void;
const axes=['x','y','z'] as const;
const distance='targetDistance760',horizontal='horizontalDistance764',factor='float80437078';
const configured=Symbol('retain configured profile'),missingProfile=Symbol('missing captured profile');
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[actor-secondary-null-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run:()=>unknown,fragment:string):string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message||'success'}`);return message;
}
function fromBits(bits:number):number {const v=new DataView(new ArrayBuffer(4));v.setUint32(0,bits,false);return v.getFloat32(0,false);}
function float(bytes:Bytes,offset:number,value:number):void {
  const v=new DataView(new ArrayBuffer(4));v.setFloat32(0,value,false);
  for(let i=0;i<4;i++) bytes[offset+i]=v.getUint8(i);
}
function setup(make:Make,profile:unknown=configured,hasSelection=true) {
  // Capture the actual configuration object while the canonical admission
  // constructor reads it. Mutate its data property BEFORE capture, never a
  // getter return or a runtime method. The profile remains construction-owned.
  const native=Object.getOwnPropertyDescriptor;let profileSource:object|undefined,captures=0;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    if(key==='gqr5'&&native(owner,'actionRequest')&&native(owner,'charge')&&native(owner,'cues')&&native(owner,'streams')) {
      profileSource=owner;captures++;
      if(profile!==configured) {
        if(profile===missingProfile) Reflect.deleteProperty(owner,'gqr5');else Reflect.set(owner,'gqr5',profile);
      }
    }
    return native(owner,key);
  }) as typeof native;
  let x:ReturnType<typeof createActorTargetCandidatesTestFixture>;
  try {x=createActorTargetCandidatesTestFixture(make,hasSelection?1:0);} finally {Object.getOwnPropertyDescriptor=native;}
  equal(captures,1,'one actual admission configuration captures GQR5');check(profileSource!==undefined,'actual admission sources captured');
  const stack:Vector={x:91,y:92,z:93},vector:Vector={x:71,y:72,z:73};
  x.sources.projectionStack=stack;Reflect.set(x.rootSources,'processor',x.actionSources.processor);x.scalarDescriptor.byte10=1;
  const processor=x.actionSources.processor,pos=x.sourceActor.pos,data=x.commandAdmission.getData(),mappingActor=x.mapping.getActor(x.actor);
  const matrixIds=x.world.getStorage(x.actor).matrices8d4,matrix=x.matrices.getMatrix(matrixIds[1]!);
  matrix[3]=0;matrix[7]=0;matrix[11]=0;
  equal(x.hits.registerHit(x.child,1),1,'genuine HIT registration completes');
  const id=x.hitIds[0]!,bytes=x.hitBytes[0]!,descriptor=x.allocator.readPointer(id,0x28)!;
  const address=x.allocator.getInteriorAddress(descriptor)!;
  equal(address.base,x.hitTableIdentity,'real HIT descriptor owns selected OBJECT bytes');
  const table=x.hitBinding.pointer3fc;table[address.byteOffset+2]=2;table[address.byteOffset+3]=0;
  x.allocator.writePointer(id,0x20,x.target);float(bytes,0x64,5);float(bytes,0x68,6);float(bytes,0x6c,7);
  x.list[0]=id;x.scratch[0]=null;Reflect.set(x.sourceActor,'lockTarget',vector);
  const aim=x.sourceActor.aimOrigin518;Object.assign(aim,{x:-51,y:-52,z:-53});
  Object.assign(x.sourceActor,{visibilityTarget:null,targetDistance760:61,horizontalDistance764:63});
  Object.assign(pos,{x:1,y:2,z:3});Object.assign(x.sourceActor,{heading:0,targetDistance758:91,horizontalDistance75c:93});
  Reflect.set(data,'float80437658',0);Reflect.set(data,'float80437678',20000);
  equal(Reflect.get(data,factor),fromBits(0x38c90fdb),'existing canonical factor has authenticated f32 bits38c90fdb');
  const outerSources:SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  const frame=createSourceBattleOuterFrameRuntime(outerSources);
  return Object.assign(x,{stack,vector,aim,processor,pos,data,mappingActor,matrix,matrixIds,id,bytes,frame,outerSources,profileSource:profileSource!,hasSelection});
}
type Fixture=ReturnType<typeof setup>;
const tail='unknown/non-owned admission actor';
let injectedAdmissionDepth=0;
function failAdmission(x:Fixture):void {
  // Execute a real, separate admission call to poison its lifecycle, but do
  // not mislabel that injected call's own508 load as outer third-pass progress.
  injectedAdmissionDepth++;
  try {rejects(()=>x.commandAdmission.dispatchSubtypeDirection(x.actor),'signed585 pointer slot');}
  finally {injectedAdmissionDepth--;}
}
function run(x:Fixture,fragment=tail,before:Visit=()=>{},after?:Visit):string {
  const native=Object.getOwnPropertyDescriptor;
  let dispatch=false,changed=false,helper=false,primary=false,secondary=false,storedNull=false,late=0,scheduler=0,third508=0;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    if(injectedAdmissionDepth>0) return native(owner,key);
    if(owner===x.targetPreparation&&key==='targetDispatch') dispatch=true;
    if(x.hasSelection&&dispatch&&!changed&&owner===x.admissionState&&key==='pointer504') {
      changed=true;x.allocator.writePointer(x.id,0x20,null);
    }
    if(!helper&&owner===x.vector&&key==='z') helper=true;
    else if(!primary&&(helper||!x.hasSelection&&dispatch)&&owner===x.admissionState&&key==='pointer508') primary=true;
    if(primary&&!secondary&&owner===x.sourceActor&&key==='visibilityTarget') {secondary=true;storedNull=native(x.admissionState,'pointer508')?.value===null;}
    if(secondary) {
      if(owner===x.physicalIdentities&&key==='1'||owner===x.slotTargets[1]&&key==='active0'||
        owner===x.sourceActor&&key==='active0'||owner===x.massPreparation&&key==='physicalBlock') late++;
      if(owner===x.groups||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) scheduler++;
      if(owner===x.admissionState&&key==='pointer508') third508++;
      before(owner,key);
    }
    const result=native(owner,key);if(secondary) after?.(owner,key);return result;
  }) as typeof native;
  let message='';try {message=rejects(()=>x.frame.runFrame(),fragment);} finally {Object.getOwnPropertyDescriptor=native;}
  check(primary,'genuine primary null branch reached');check(secondary,'genuine secondary cc load reached');
  if(x.hasSelection) check(changed,'actual OBJECT+20 changed before selector final508');
  check(storedNull,'selector genuinely stored null508 before secondary');
  equal(scheduler,0,'no scheduler mask/group authority');
  if(fragment===tail||fragment==='8006b374') {check(late>0,'completed secondary resumes existing physical passes');equal(third508,1,'third pass reloads canonical row0 null508 exactly once');}
  else {equal(late,0,'secondary refusal prevents remaining actors and third pass');equal(third508,0,'no premature third-pass508');}
  return message;
}
function primaryRetained(x:Fixture):void {
  equal(x.sourceActor.byte502,x.hasSelection?1:0,'selector502 retained');
  equal(x.sourceActor.targetDistance758,20000,'primary758 retained');equal(x.sourceActor.horizontalDistance75c,20000,'primary75c retained');
  axes.forEach((axis,i)=>equal(x.vector[axis],[0,0,20000][i],`primary ${axis} unchanged by secondary`));
  if(x.hasSelection) {
    equal(x.admissionState.pointer504,x.bytes,'original selected OBJECT504 retained');
    equal(x.globals.count804361a0,1,'candidate count retained');equal(x.scratch[0],x.id,'original OBJECT selection retained');
    axes.forEach(axis=>equal(x.stack[axis],0,'projection prefix retained'));
  }
  equal(x.massPreparation.orderCount.count80436260,6,'mass ordering retained');equal(x.massHost.sourceArrowMass204,1200,'mass prefix retained');
}
function retained(x:Fixture,values:readonly unknown[]=[0,0,20000],sentinels=true):void {
  primaryRetained(x);axes.forEach((axis,i)=>equal(x.aim[axis],values[i],`secondary partial ${axis}`));
  if(sentinels) {equal(x.sourceActor.targetDistance760,20000,'secondary760 retained');equal(x.sourceActor.horizontalDistance764,20000,'secondary764 retained');}
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal permanently closes actual caller');
  rejects(()=>x.frame.runFrame(),'permanently incomplete');rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
  for(const next of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(next,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function prefix(axis:'x'|'y'|'z'):number[] {return axis==='x'?[-51,-52,-53]:axis==='y'?[0,-52,-53]:[0,0,-53];}
function corrupt(owner:object,key:string,kind:string,invoked:()=>void):void {
  if(kind==='missing'||kind==='inherited') {
    const old=Object.getOwnPropertyDescriptors(owner)[key]?.value;equal(Reflect.deleteProperty(owner,key),true,'actual property removed');
    if(kind==='inherited') Object.setPrototypeOf(owner,{[key]:old});
  } else if(kind==='accessor') Object.defineProperty(owner,key,{get(){invoked();return 0;},set(){invoked();},configurable:true});
  else if(kind==='readonly') Object.defineProperty(owner,key,{writable:false});
  else equal(Reflect.set(owner,key,kind==='nan'?NaN:kind==='infinite'?Infinity:kind==='negative-infinite'?-Infinity:
    kind==='inexact'?1+2**-30:kind==='string'?'0':kind==='null'?null:kind==='undefined'?undefined:
    kind==='object'?{}:kind==='boolean'?false:kind==='negative-zero'?-0:kind==='neighbor'?fromBits(0x38c90fdc):1),true,'actual source operand changed');
}

function orderAndBoundaryTests(make:Make):void {
  {
    const x=setup(make),events:string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);let forbidden=0,headings=0;
    run(x,tail,(owner,key)=>{
      if(owner===x.sourceActor&&['visibilityTarget','heading',distance,horizontal,'active0'].includes(String(key))) {events.push(String(key));if(key==='heading') headings++;}
      if(owner===x.data&&[factor,'float80437678'].includes(String(key))) events.push(String(key));
      if(owner===x.mappingActor&&key==='descriptor4b0') events.push('descriptor4b0');
      if(owner===x.scalarDescriptor&&key==='byte10') events.push('byte10');
      if(owner===x.matrixIds&&key==='1') events.push('matrix[1]');
      if(owner===x.matrix&&key==='7') events.push('matrix.7');
      if(owner===x.aim&&axes.includes(key as typeof axes[number])) events.push(`aim.${String(key)}`);
      if(owner===x.slotTargets[1]&&key==='active0') events.push('row1.active0');
      if(owner===x.admissionState&&key==='pointer508') events.push('third508');
      if(owner===x.admissionState&&key==='pointerc8'||owner===x.pos&&axes.includes(key as typeof axes[number])||
        owner===x.processor&&['gqr0','gqr5'].includes(String(key))||owner===x.rootSources&&key==='processor') forbidden++;
    });
    equal(events.join(','),`visibilityTarget,float80437678,${horizontal},${distance},heading,${factor},${horizontal},aim.x,descriptor4b0,byte10,matrix[1],matrix.7,aim.y,heading,${factor},${horizontal},aim.z,row1.active0,active0,third508,row1.active0`,
      'cc then b2ec764/760, signed sine/X, descriptor row7/Y, fresh cosine/Z, second-pass skip and third-pass active-before508');
    equal(headings,2,'secondary sine and cosine freshly load heading');equal(forbidden,0,'nullcc never loads c8/position/live processor');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no fabricated frame claim');
    equal(claimSourceHelperStorage(x.vector,x.targetDispatch),true,'primary retains selector claim');
    check(x.commandAdmission.getKnownStorageEntries().some(e=>e.owner===x.aim&&e.kind==='aim'),'secondary borrows admission-owned aim storage');
    retained(x);closed(x);
  }
  for(const readonly of [false,true]) {
    const x=setup(make);let invoked=0;
    const opaque={};for(const key of ['eligibility83','pos','x','y','z','active0','target']) Object.defineProperty(opaque,key,{get(){invoked++;throw Error('opaque target dereference');}});
    Reflect.set(x.sourceActor,'visibilityTarget',opaque);
    if(readonly) Object.defineProperty(x.sourceActor,'visibilityTarget',{writable:false});
    Object.defineProperty(x.admissionState,'pointerc8',{writable:false,value:17});
    run(x,'8006b1dc');equal(invoked,0,'nonnullcc stays opaque before c8 dereference');retained(x,[-51,-52,-53],false);
    equal(x.sourceActor.targetDistance760,61,'nonnullcc leaves760 unchanged');equal(x.sourceActor.horizontalDistance764,63,'nonnullcc leaves764 unchanged');closed(x);
  }
  for(const kind of ['missing','inherited','accessor','undefined','nan','inexact','string','boolean'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    run(x,'visibilityTarget',(owner,key)=>{if(!hit&&owner===x.sourceActor&&key==='visibilityTarget') {hit=true;corrupt(owner,'visibilityTarget',kind,()=>invoked++);}});
    check(hit,'malformedcc reached actual source load');equal(invoked,0,'cc getter never invoked');retained(x,[-51,-52,-53],false);closed(x);
  }
  {
    const x=setup(make);Object.defineProperty(x.sourceActor,'visibilityTarget',{writable:false});
    Object.defineProperty(x.admissionState,'pointerc8',{value:17,writable:false});
    run(x);retained(x);equal(x.admissionState.pointerc8,17,'nullcc never validates unreachable c8');closed(x);
  }
  {
    const x=setup(make);let hit=false,invoked=0;
    run(x,tail,(owner,key)=>{if(!hit&&owner===x.sourceActor&&key==='visibilityTarget') {
      hit=true;
      for(const record of [x.pos,x.bytes,x.processor]) for(const field of record===x.pos?axes:record===x.bytes?Array.from({length:12},(_,i)=>String(0x64+i)):['gqr0','gqr5'])
        Object.defineProperty(record,field,{get(){invoked++;throw Error('unreached secondary source');},configurable:true});
      for(const lane of [0,1,2,3,4,5,6,8,9,10,11]) x.matrix[lane]=NaN;
    }});
    equal(invoked,0,'nullcc keeps source position/OBJECT/live processor and unused matrix lanes lazy');retained(x);closed(x);
  }
}

function capturedOperandTests(make:Make):void {
  for(const initiallyNull of [false,true]) {
    const x=setup(make),opaque={};let changed=false;
    Reflect.set(x.sourceActor,'visibilityTarget',initiallyNull?null:opaque);
    run(x,initiallyNull?tail:'8006b1dc',()=>{},(owner,key)=>{if(!changed&&owner===x.sourceActor&&key==='visibilityTarget') {
      changed=true;Reflect.set(x.sourceActor,'visibilityTarget',initiallyNull?opaque:null);
    }});
    check(changed,'cc source mutated after actual descriptor capture');
    retained(x,initiallyNull?[0,0,20000]:[-51,-52,-53],initiallyNull);closed(x);
  }
  {
    const x=setup(make);let changed=false,reads=0;
    run(x,tail,(owner,key)=>{
      if(owner===x.data&&key==='float80437678') reads++;
      if(!changed&&owner===x.sourceActor&&key===horizontal) {changed=true;Reflect.set(x.data,'float80437678',NaN);}
    });
    equal(reads,1,'secondary sentinel is captured once before both destination stores');
    retained(x);closed(x);
  }
}

function aimOwnershipTests(make:Make):void {
  for(const kind of ['unclaimed','same-claim','other-claim','pointer-reserved'] as const) {
    const x=setup(make);
    if(kind==='same-claim') equal(claimSourceHelperStorage(x.aim,x.commandAdmission),true,'existing exact admission claim installed');
    if(kind==='other-claim') equal(claimSourceHelperStorage(x.aim,{}),true,'competing helper claim installed');
    if(kind==='pointer-reserved') equal(reserveSourcePointerStorage(x.aim),true,'pointer storage reservation installed');
    run(x,kind==='other-claim'||kind==='pointer-reserved'?'claimed':tail);
    retained(x,kind==='other-claim'||kind==='pointer-reserved'?[-51,-52,-53]:[0,0,20000]);
    if(kind==='unclaimed'||kind==='same-claim') {
      equal(claimSourceHelperStorage(x.aim,x.commandAdmission),true,'secondary retains exact admission helper claim');
      equal(claimSourceHelperStorage(x.aim,{}),false,'secondary cannot transfer existing helper claim');
    }
    closed(x);
  }
  {
    const x=setup(make);let invoked=0;
    for(const axis of axes) Object.defineProperty(x.aim,axis,{get(){invoked++;throw Error('metadata read XYZ');},configurable:true});
    equal(x.commandAdmission.getAimPositionOwner(x.actor),x.aim,'metadata-only API borrows actual aim owner');
    equal(invoked,0,'metadata-only borrowing never loads XYZ');
    axes.forEach((axis,i)=>Object.defineProperty(x.aim,axis,{value:-51-i,writable:true,configurable:true,enumerable:true}));
    run(x);retained(x);closed(x);
  }
  for(const mode of ['reuse','replacement','alias'] as const) {
    const x=setup(make);
    Object.assign(x.sourceActor,{cmdButton:2,cmdSubtype:0});
    equal(x.commandAdmission.dispatchSubtypeDirection(x.actor),1,'genuine existing command execution captures null target and aim');
    check(x.commandAdmission.getKnownStorageEntries().some(e=>e.owner===x.aim&&e.kind==='aim'),'actual command capture retained aim owner');
    equal(claimSourceHelperStorage(x.aim,x.commandAdmission),true,'command and outer borrow use same storage claim');
    Object.assign(x.aim,{x:-51,y:-52,z:-53});Object.assign(x.sourceActor,{targetDistance760:61,horizontalDistance764:63});
    let changed=false;
    run(x,mode==='reuse'?tail:mode==='replacement'?'aimOrigin518':'alias',(owner,key)=>{
      if(!changed&&owner===x.sourceActor&&key==='visibilityTarget') {
        changed=true;
        if(mode==='replacement') Reflect.set(x.sourceActor,'aimOrigin518',{x:41,y:42,z:43});
        if(mode==='alias') Reflect.set(x.sourceActor,'motion',x.aim);
      }
    });
    retained(x,mode==='reuse'?[0,0,20000]:[-51,-52,-53]);closed(x);
  }
}

function sentinelTests(make:Make):void {
  for(const key of [horizontal,distance]) for(const kind of ['missing','inherited','accessor','readonly'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    const mutate:Visit=(owner,field)=>{if(!hit&&owner===x.sourceActor&&field===key) {hit=true;corrupt(owner,key,kind,()=>invoked++);}};
    run(x,key,phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);check(hit,`${phase} ${key} destination reached`);
    equal(invoked,0,'sentinel getter/setter never invoked');retained(x,[-51,-52,-53],false);
    const fields=Object.getOwnPropertyDescriptors(x.sourceActor);
    equal(fields[key===distance?horizontal:distance]?.value,key===distance?20000:61,'sentinel prior prefix is exact');
    if(kind==='readonly') equal(fields[key]?.value,key===distance?61:63,'readonly scalar not overwritten');
    if(kind==='missing'||kind==='inherited') equal(fields[key],undefined,'missing scalar not recreated');closed(x);
  }
  for(const kind of ['missing','inherited','accessor','nan','inexact','negative-zero','neighbor'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    run(x,'float80437678',(owner,key)=>{if(!hit&&owner===x.data&&key==='float80437678') {hit=true;corrupt(owner,String(key),kind,()=>invoked++);}});
    equal(invoked,0,'secondary sentinel getter never invoked');retained(x,[-51,-52,-53],false);closed(x);
  }
  {
    const x=setup(make);let hit=false;
    run(x,tail,(owner,key)=>{if(!hit&&owner===x.sourceActor&&key==='visibilityTarget') {hit=true;Reflect.set(x.sourceActor,horizontal,NaN);Reflect.set(x.sourceActor,distance,Symbol('old scalar'));}});
    retained(x);closed(x);
  }
}

function arithmeticAndSourceTests(make:Make):void {
  for(const at of [1,2]) for(const value of [1,32767,32768,65535]) {
    const x=setup(make),native=Math.fround,products:number[]=[];let headings=0,factors=0,tracing=false;
    Math.fround=(value:number):number=>{if(tracing) products.push(value);return native(value);};
    try {run(x,at===1?'80045204':'80045238',(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading'&&++headings===at) x.sourceActor.heading=value;
      if(owner===x.data&&key===factor&&++factors===at) tracing=true;
    });} finally {Math.fround=native;}
    equal(headings,at,'secondary fails at exact unsupported trig');equal(factors,at,'factor loaded before nonzero trig boundary');
    check(products.some(v=>Object.is(v,fromBits(0x38c90fdb)*(value<<16>>16))),'secondary fmuls uses sign-extended raw BAM16');
    retained(x,at===1?[-51,-52,-53]:[0,0,-53]);closed(x);
  }
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','nan','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let headings=0,invoked=0;
    run(x,'heading',(owner,key)=>{if(owner===x.sourceActor&&key==='heading'&&++headings===at) corrupt(owner,'heading',kind,()=>invoked++);});
    equal(headings,at,'secondary heading fault is lazy');equal(invoked,0,'heading getter not invoked');retained(x,at===1?[-51,-52,-53]:[0,0,-53]);closed(x);
  }
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','negative-zero','neighbor','nan','infinite','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let seen=0,invoked=0;
    run(x,factor,(owner,key)=>{if(owner===x.data&&key===factor&&++seen===at) corrupt(owner,factor,kind,()=>invoked++);});
    equal(seen,at,'secondary factor freshly reloaded');equal(invoked,0,'factor getter never invoked');retained(x,at===1?[-51,-52,-53]:[0,0,-53]);closed(x);
  }
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','nan','infinite','negative-infinite','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let heading=false,seen=0,invoked=0;
    run(x,horizontal,(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') heading=true;
      if(heading&&owner===x.sourceActor&&key===horizontal&&++seen===at) corrupt(owner,horizontal,kind,()=>invoked++);
    });
    equal(seen,at,'secondary764 operand fault at exact fresh sine/cosine load');equal(invoked,0,'764 getter not invoked');
    retained(x,at===1?[-51,-52,-53]:[0,0,-53],false);equal(x.sourceActor.targetDistance760,20000,'760 sentinel retained with invalid764');closed(x);
  }
  for(const pair of [[-0,-0],[-7,-9],[fromBits(1),fromBits(2)],[fromBits(0x7f7fffff),fromBits(0xff7fffff)]]) {
    const x=setup(make);let heading=false,reads=0;
    run(x,tail,(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') heading=true;
      if(heading&&owner===x.sourceActor&&key===horizontal) Reflect.set(owner,horizontal,pair[reads++]!);
    });
    equal(reads,2,'secondary764 read freshly once per component');
    retained(x,[Math.fround(pair[0]!*0),0,Math.fround(pair[1]!*1)],false);equal(x.sourceActor.targetDistance760,20000,'760 not reread as764');closed(x);
  }
  for(const site of ['descriptor','byte','matrix'] as const) for(const kind of ['nan','inexact','null','undefined','object','string']) {
    const x=setup(make),owner=site==='descriptor'?x.mappingActor:site==='byte'?x.scalarDescriptor:x.matrix,key=site==='descriptor'?'descriptor4b0':site==='byte'?'byte10':'7';
    let hit=false,invoked=0;
    run(x,site==='descriptor'?'descriptor':site==='byte'?'byte10':kind==='nan'||kind==='inexact'?'float32':'7',(at,field)=>{
      if(!hit&&at===owner&&field===key) {hit=true;corrupt(owner,key,kind,()=>invoked++);}
    });
    check(hit,'secondary matrix source reached after X');equal(invoked,0,'descriptor/matrix accessor never invoked');retained(x,[0,-52,-53]);closed(x);
  }
  for(const raw of [0,1,2,11,127,128,255]) {
    const x=setup(make);let hit=false,lane=0;
    const valid=raw<x.matrixIds.length&&raw<128,chosen=valid?x.matrices.getMatrix(x.matrixIds[raw]!):undefined;
    run(x,valid?tail:'world matrix',(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') {hit=true;x.scalarDescriptor.byte10=raw;if(chosen) chosen[7]=17+raw;}
      if(owner===chosen&&key==='7') lane++;
    });
    check(hit,'descriptor signed byte fresh after primary Y');equal(lane,valid?1:0,'only reached signed matrix row7 read');
    retained(x,valid?[0,17+raw,20000]:[0,-52,-53]);closed(x);
  }
  {
    const x=setup(make);let heading=false;
    run(x,tail,(owner,key)=>{if(!heading&&owner===x.sourceActor&&key==='heading') {
      heading=true;for(const [record,field] of [[x.profileSource,'gqr5'],[x.processor,'gqr5'],[x.processor,'gqr0']] as const) Reflect.set(record,field,0);
      for(const [record,field] of [[x.sourceActor,'heading'],[x.sourceActor,horizontal],[x.scalarDescriptor,'byte10'],[x.matrix,'7'],[x.sourceActor,'aimOrigin518'],[x.data,factor]] as const)
        Object.defineProperty(record,field,{writable:false});
    }});
    retained(x);closed(x);
  }
  for(const site of ['descriptor','byte','matrix'] as const) {
    const x=setup(make),owner=site==='descriptor'?x.mappingActor:site==='byte'?x.scalarDescriptor:x.matrix,key=site==='descriptor'?'descriptor4b0':site==='byte'?'byte10':'7';let hit=false;
    run(x,tail,(at,field)=>{if(!hit&&at===owner&&field===key) {
      hit=true;check(Object.isSealed(owner),'canonical scalar source sealed');equal(Reflect.deleteProperty(owner,key),false,'sealed source cannot lose own field');
      equal(Reflect.setPrototypeOf(owner,{[key]:0}),false,'sealed source cannot substitute inherited field');
      equal(Reflect.defineProperty(owner,key,{get(){throw Error('uninstalled getter');}}),false,'sealed source cannot substitute accessor');
    }});
    check(hit,'actual source metadata checked lazily');retained(x);closed(x);
  }
}

function destinationTests(make:Make):void {
  for(const axis of axes) for(const kind of ['missing','inherited','accessor','readonly'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    const mutate:Visit=(owner,key)=>{if(!hit&&owner===x.aim&&key===axis) {hit=true;corrupt(owner,axis,kind,()=>invoked++);}};
    run(x,axis,phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,`${phase} ${axis} ${kind} aim destination reached`);equal(invoked,0,'aim getter/setter not invoked');primaryRetained(x);
    const fields=Object.getOwnPropertyDescriptors(x.aim),expected=prefix(axis);
    axes.forEach((other,i)=>{if(other!==axis) equal(fields[other]?.value,expected[i],'earlier aim stores retained precisely');});
    if(kind==='missing'||kind==='inherited') equal(fields[axis],undefined,'missing aim coordinate never recreated');
    if(kind==='accessor') check(fields[axis]!==undefined&&!('value'in fields[axis]!), 'aim accessor not overwritten');
    if(kind==='readonly') equal(fields[axis]?.value,expected[axes.indexOf(axis)],'readonly aim coordinate not written');
    equal(x.sourceActor.targetDistance760,20000,'prior760 retained');equal(x.sourceActor.horizontalDistance764,20000,'prior764 retained');closed(x);
  }
  for(const axis of axes) for(const kind of ['missing','inherited','accessor','replaced','position','projection','matrix','primary','other-actor'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    run(x,kind==='other-actor'?'alias':'aimOrigin518',(owner,key)=>{if(!hit&&owner===x.aim&&key===axis) {
      hit=true;
      if(kind==='missing'||kind==='inherited'||kind==='accessor') corrupt(x.sourceActor,'aimOrigin518',kind,()=>invoked++);
      else if(kind==='other-actor') Reflect.set(x.targetActor,'aimOrigin518',x.aim);
      else if(kind==='replaced') Reflect.set(x.sourceActor,'aimOrigin518',{x:21,y:22,z:23});
      else Reflect.set(x.sourceActor,'aimOrigin518',kind==='position'?x.pos:kind==='projection'?x.stack:kind==='matrix'?x.matrix:x.vector);
    }});
    check(hit,'actual aim owner replacement fault reached');equal(invoked,0,'aim owner getter never invoked');retained(x,prefix(axis));closed(x);
  }
  {
    const x=setup(make);let hit=false;
    run(x,tail,(owner,key)=>{if(!hit&&owner===x.sourceActor&&key==='heading') {hit=true;Object.assign(x.aim,{x:NaN,y:Symbol('old Y'),z:undefined});}});
    retained(x);closed(x);
  }
}

function competingSourceTests(make:Make):void {
  for(const at of [1,2]) for(const site of ['factor','heading'] as const) {
    const x=setup(make);let seen=0,hit=false;
    run(x,'competing',(owner,key)=>{if(owner===x.data&&key===factor&&++seen===at) {
      hit=true;Reflect.set(site==='factor'?x.sourceActor:x.data,site==='factor'?factor:'heading',site==='factor'?fromBits(0x38c90fdb):0);
    }});
    check(hit,'secondary competing canonical source inserted');retained(x,at===1?[-51,-52,-53]:[0,0,-53]);closed(x);
  }
  for(const axis of axes) for(const key of ['field518','field51c','field51C','field520','position518','targetPosition518','1304','byte518']) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{if(!hit&&owner===x.aim&&field===axis) {hit=true;Reflect.set(x.sourceActor,key,0);}});
    check(hit,'secondary aim shadow introduced at destination');retained(x,prefix(axis));closed(x);
  }
  for(const site of ['outer','globals','data','binding','target-preparation','matrix','aim'] as const) for(const axis of axes) {
    const x=setup(make);let hit=false;
    const competing=site==='outer'?x.outerSources:site==='globals'?x.systemGlobals:site==='data'?x.data:
      site==='binding'?x.admissionState:site==='target-preparation'?x.targetPreparation:site==='matrix'?x.matrix:x.aim;
    const extensible=Object.isExtensible(competing);
    run(x,extensible?'competing':tail,(owner,key)=>{if(!hit&&owner===x.aim&&key===axis) {
      hit=true;equal(Reflect.set(competing,'field518',0),extensible,'alias injection respects sealed canonical storage');
    }});
    check(hit,`${site} aim alias attempted at ${axis} destination`);
    if(!extensible) equal(Object.getOwnPropertyDescriptor(competing,'field518'),undefined,'sealed owner cannot acquire alias');
    retained(x,extensible?prefix(axis):[0,0,20000]);closed(x);
  }
  for(const key of ['field518','field51c','field51C','field520','position518','targetPosition518','1304','byte518']) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{if(!hit&&owner===x.data&&field===factor) {
      hit=true;Reflect.set(x.outerSources,key,0);
    }});
    check(hit,'outer aim alias introduced at first secondary factor read');retained(x,[-51,-52,-53]);closed(x);
  }
  for(const key of ['field760','field764','byte760','byte764','1888','1892','pointercc','fieldcc','bytecc','204','205','206','207']) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{if(!hit&&owner===x.sourceActor&&field==='visibilityTarget') {hit=true;Reflect.set(x.sourceActor,key,0);}});
    check(hit,`secondary distance/cc shadow ${key} introduced at reached load`);retained(x,[-51,-52,-53],false);closed(x);
  }
}

function interruptionTests(make:Make):void {
  const sites=['cc','sentinel','store764','store760','heading1','factor1','distance1','x','descriptor','byte','matrix','y','heading2','factor2','distance2','z'];
  for(const site of sites) for(const kind of ['reentry','caller','admission'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,headings=0,factors=0,distances=0;
    const mutate:Visit=(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') headings++;
      if(owner===x.data&&key===factor) factors++;
      if(headings>0&&owner===x.sourceActor&&key===horizontal) distances++;
      const at=site==='cc'?owner===x.sourceActor&&key==='visibilityTarget':
        site==='sentinel'?owner===x.data&&key==='float80437678':
        site==='store764'?owner===x.sourceActor&&key===horizontal&&headings===0:
        site==='store760'?owner===x.sourceActor&&key===distance:
        site.startsWith('heading')?owner===x.sourceActor&&key==='heading'&&headings===Number(site.slice(-1)):
        site.startsWith('factor')?owner===x.data&&key===factor&&factors===Number(site.slice(-1)):
        site.startsWith('distance')?owner===x.sourceActor&&key===horizontal&&headings>0&&distances===Number(site.slice(-1)):
        site==='descriptor'?owner===x.mappingActor&&key==='descriptor4b0':site==='byte'?owner===x.scalarDescriptor&&key==='byte10':
        site==='matrix'?owner===x.matrix&&key==='7':owner===x.aim&&key===site;
      if(!hit&&at) {
        hit=true;
        if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
        else if(kind==='caller') {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
        else failAdmission(x);
      }
    };
    run(x,kind==='reentry'?'reentry':'incomplete',phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,`${kind} ${phase} exact secondary ${site} interrupted`);
    const index=sites.indexOf(site);retained(x,index<=7?[-51,-52,-53]:index<=11?[0,-52,-53]:[0,0,-53],false);
    equal(x.sourceActor.horizontalDistance764,index>2?20000:63,'interruption preserves exact764 prefix');
    equal(x.sourceActor.targetDistance760,index>3?20000:61,'interruption preserves exact760 prefix');closed(x);
  }
}

function finalSnapshotTests(make:Make):void {
  for(const key of [horizontal,distance,...axes]) for(const kind of ['incomplete','caller','admission','reentry','alias','missing','inherited','accessor','readonly','replaced'] as const) {
    const x=setup(make),axis=axes.includes(key as typeof axes[number]),owner=axis?x.aim:x.sourceActor,native=Object.getOwnPropertyDescriptors;
    let admitted=false,hit=false,invoked=0;
    Object.getOwnPropertyDescriptors=((at:object)=>{
      const fields=native(at);if(at!==owner) return fields;let enumerated=false;
      return new Proxy(fields,{
        ownKeys(target) {enumerated=true;return Reflect.ownKeys(target);},
        get(target,field,receiver) {
          if(admitted&&!enumerated&&!hit&&field===key) {
            hit=true;
            if(kind==='incomplete') markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
            else if(kind==='caller') {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
            else if(kind==='admission') failAdmission(x);
            else if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
            else if(kind==='alias') Reflect.set(x.sourceActor,axis?'motion':'field760',axis?x.aim:0);
            else if(kind==='replaced') {
              if(axis) Reflect.set(x.sourceActor,'aimOrigin518',{x:31,y:32,z:33});
              else Reflect.set(x.targetPreparation,'admission',{});
            } else corrupt(owner,key,kind,()=>invoked++);
          }
          return Reflect.get(target,field,receiver);
        },
      });
    }) as typeof native;
    try {run(x,kind==='reentry'?'reentry':kind==='alias'?axis?'alias':'competing':kind==='replaced'?axis?'aimOrigin518':'admission':
      ['incomplete','caller','admission'].includes(kind)?'incomplete':key,(at,field)=>{if(at===owner&&field===key) admitted=true;});
    } finally {Object.getOwnPropertyDescriptors=native;}
    check(hit,`${key} ${kind} final snapshot mutation reached`);equal(invoked,0,'final snapshot never calls getter/setter');primaryRetained(x);
    const fields=native(owner),expected=axis?prefix(key as typeof axes[number]):[-51,-52,-53];
    for(const [i,field] of axes.entries()) if(!axis||field!==key||!['missing','inherited','accessor'].includes(kind))
      equal(native(x.aim)[field]?.value,expected[i],'final snapshot blocks pending aim store and preserves prior stores');
    if(kind==='missing'||kind==='inherited') equal(fields[key],undefined,'final property removal not recreated');
    if(kind==='accessor') check(fields[key]!==undefined&&!('value'in fields[key]!), 'final accessor remains untouched');
    if(kind==='readonly') equal(fields[key]?.writable,false,'final readonly remains untouched');
    for(const scalar of [horizontal,distance]) if(axis||scalar!==key||!['missing','inherited','accessor'].includes(kind))
      equal(native(x.sourceActor)[scalar]?.value,axis||key===distance&&scalar===horizontal?20000:scalar===distance?61:63,'final scalar snapshot preserves exact sentinel prefix');
    closed(x);
  }
}

function laterBoundaryTests(make:Make):void {
  {
    const x=setup(make);let third=false,reads=0;
    const opaque={};Object.defineProperty(opaque,'eligibility83',{get(){reads++;throw Error('unreached target83');}});
    run(x,'8006b374',(owner,key)=>{if(owner===x.admissionState&&key==='pointer508') {third=true;x.admissionState.pointer508=opaque;}});
    check(third,'post-secondary third pass reached');equal(reads,0,'nonnull third-pass target stays opaque at unsupported83');retained(x);closed(x);
  }
  for(const zero of [false,true]) {
    const x=setup(make);if(zero) Object.assign(x.pos,{x:5,y:6,z:7});
    const native=Object.getOwnPropertyDescriptor;let secondary=0;
    Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{if(owner===x.sourceActor&&key==='visibilityTarget') secondary++;return native(owner,key);}) as typeof native;
    try {rejects(()=>x.frame.runFrame(),zero?'8006d228':'frsqrte');} finally {Object.getOwnPropertyDescriptor=native;}
    equal(secondary,0,'nonnull primary/estimator cannot advance to secondary');equal(x.aim.x,-51,'nonnull primary retains secondaryX');
    equal(x.sourceActor.targetDistance760,61,'nonnull primary retains secondary760');closed(x);
  }
}

export function runActorSecondaryNullSelfTests(make:Make):void {
  let fixtures=0;const counted:Make=omit=>{fixtures++;return make(omit);};
  orderAndBoundaryTests(counted);capturedOperandTests(counted);aimOwnershipTests(counted);sentinelTests(counted);arithmeticAndSourceTests(counted);destinationTests(counted);
  competingSourceTests(counted);interruptionTests(counted);finalSnapshotTests(counted);laterBoundaryTests(counted);
  console.log(`[actor-secondary-null] PASS (${fixtures} genuine graph fixtures): actual nullcc, opaque nonnullcc boundary, retained764/760 sentinels, fresh signed trig/764 and descriptor row7, canonical admission aim ownership, exact partial stores and final snapshot closure; genuine remaining second pass and third-pass dependency boundary, no estimator, scheduler authority or completed outer frame`);
}
