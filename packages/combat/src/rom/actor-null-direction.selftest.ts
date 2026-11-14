import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import {claimSourceHelperStorage,reserveSourcePointerStorage} from './source-storage-claims.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Synthetic, explicitly supplied operands on the genuine allocator/HIT/6b850
 * graph. No source callee, trig result, descriptor runtime or matrix runtime is
 * replaced. A null OBJECT+20 makes the real selector store null508; its three
 * completed lockTarget stores are then borrowed by the real caller. Every
 * witness stops inside6ae60, before the secondary/+cc load at8006b1d0. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Vector={x:number;y:number;z:number};
type Visit=(owner:object,key:PropertyKey)=>void;
const axes=['x','y','z'] as const;
const distance='targetDistance758',horizontal='horizontalDistance75c',factor='float80437078';
const configured=Symbol('retain configured profile'),missingProfile=Symbol('missing captured profile');
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[actor-null-direction-test] ${why}`);}
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
  Object.assign(pos,{x:1,y:2,z:3});Object.assign(x.sourceActor,{heading:0,targetDistance758:91,horizontalDistance75c:93});
  Reflect.set(data,'float80437658',0);Reflect.set(data,'float80437678',20000);
  equal(Reflect.get(data,factor),fromBits(0x38c90fdb),'existing canonical factor has authenticated f32 bits38c90fdb');
  const outerSources:SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  const frame=createSourceBattleOuterFrameRuntime(outerSources);
  return Object.assign(x,{stack,vector,processor,pos,data,mappingActor,matrix,matrixIds,id,bytes,frame,outerSources,profileSource:profileSource!,hasSelection});
}
type Fixture=ReturnType<typeof setup>;
function rawKey(key:PropertyKey):boolean {return /^\d+$/.test(String(key))&&Number(key)>=0x64&&Number(key)<0x70;}
function run(x:Fixture,fragment:string,before:Visit=()=>{},after?:Visit):string {
  const native=Object.getOwnPropertyDescriptor;let helper=false,primary=false,dispatch=false,changed=false,later=0,message='';
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    if(owner===x.targetPreparation&&key==='targetDispatch') dispatch=true;
    if(x.hasSelection&&dispatch&&!changed&&owner===x.admissionState&&key==='pointer504') {
      changed=true;x.allocator.writePointer(x.id,0x20,null);
    }
    if(!helper&&owner===x.vector&&key==='z') helper=true;
    else if(!primary&&(helper||!x.hasSelection&&dispatch)&&owner===x.admissionState&&key==='pointer508') {
      primary=true;
      // Keep this older primary-only suite bounded at the first missing cc
      // source cell. The separate secondary suite hydrates that continuation.
      equal(Reflect.deleteProperty(x.sourceActor,'visibilityTarget'),true,'remove unreached secondary source cell');
    }
    if(primary) {
      if(owner===x.physicalIdentities&&key==='1'||owner===x.slotTargets[1]&&key==='active0'||
        owner===x.sourceActor&&key==='active0'||owner===x.massPreparation&&key==='physicalBlock'||owner===x.groups||
        owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) later++;
      before(owner,key);
    }
    const result=native(owner,key);if(primary) after?.(owner,key);return result;
  }) as typeof native;
  try {message=rejects(()=>x.frame.runFrame(),fragment);} finally {Object.getOwnPropertyDescriptor=native;}
  check(primary,'genuine post-selector primary null branch reached');equal(later,0,'no later actor/pass/scheduler operation');
  if(x.hasSelection) check(changed,'actual OBJECT+20 changes before real final508 store');
  equal(x.admissionState.pointer508,null,'canonical selector stores genuine null508');return message;
}
function retained(x:Fixture,values:readonly unknown[]=[0,0,20000]):void {
  equal(x.sourceActor.byte502,x.hasSelection?1:0,'earlier selector502 retained');
  if(x.hasSelection) {
    equal(x.admissionState.pointer504,x.bytes,'original OBJECT504 retained');
    axes.forEach(axis=>equal(x.stack[axis],0,`earlier projection ${axis} retained`));
    equal(x.globals.count804361a0,1,'candidate count retained');equal(x.scratch[0],x.id,'selected original OBJECT retained');
  }
  equal(x.sourceActor.targetDistance758,20000,'ordered prior758 retained');equal(x.sourceActor.horizontalDistance75c,20000,'ordered prior75c retained');
  axes.forEach((axis,i)=>equal(x.vector[axis],values[i],`exact partial target ${axis}`));
  equal(x.massPreparation.orderCount.count80436260,6,'mass ordering retained');equal(x.massHost.sourceArrowMass204,1200,'mass update retained');
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'null-direction refusal permanently closes actual caller');
  rejects(()=>x.frame.runFrame(),'permanently incomplete');rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
  for(const next of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(next,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function prefix(axis:'x'|'y'|'z'):number[] {return axis==='x'?[5,6,7]:axis==='y'?[0,6,7]:[0,0,7];}
function corrupt(owner:object,key:string,kind:string,invoked:()=>void):void {
  if(kind==='missing'||kind==='inherited') {
    const old=Object.getOwnPropertyDescriptors(owner)[key]?.value;equal(Reflect.deleteProperty(owner,key),true,'fault removes actual own source/destination property');
    if(kind==='inherited') Object.setPrototypeOf(owner,{[key]:old});
  } else if(kind==='accessor') Object.defineProperty(owner,key,{get(){invoked();return 0;},set(){invoked();},configurable:true});
  else if(kind==='readonly') Object.defineProperty(owner,key,{writable:false});
  else equal(Reflect.set(owner,key,kind==='nan'?NaN:kind==='infinite'?Infinity:kind==='negative-infinite'?-Infinity:
    kind==='inexact'?1+2**-30:kind==='string'?'0':kind==='null'?null:kind==='undefined'?undefined:
    kind==='object'?{}:kind==='boolean'?false:kind==='negative-zero'?-0:kind==='neighbor'?fromBits(0x38c90fdc):1),true,'fault replaces actual source data value');
}

function orderAndOwnershipTests(make:Make):void {
  for(const secondary of [null,{},17]) {
    const x=setup(make),events:string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);let forbidden=0,headings=0;
    Reflect.set(x.sourceActor,'visibilityTarget',secondary);
    run(x,'8006b1d0',(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') {headings++;events.push('heading');}
      if(owner===x.data&&[factor,'float80437678'].includes(String(key))) events.push(String(key));
      if(owner===x.sourceActor&&[distance,horizontal].includes(String(key))) events.push(String(key));
      if(owner===x.mappingActor&&key==='descriptor4b0') events.push('descriptor4b0');
      if(owner===x.scalarDescriptor&&key==='byte10') events.push('byte10');
      if(owner===x.matrixIds&&key==='1') events.push('matrix[1]');
      if(owner===x.matrix&&key==='7') events.push('matrix.7');
      if(owner===x.vector&&axes.includes(key as typeof axes[number])) events.push(`target.${String(key)}`);
      if(owner===x.admissionState&&key==='pointer504'||
        owner===x.pos&&axes.includes(key as typeof axes[number])||owner===x.bytes&&rawKey(key)||
        owner===x.processor&&['gqr0','gqr5'].includes(String(key))||owner===x.rootSources&&key==='processor') forbidden++;
    });
    equal(events.join(','),`float80437678,${horizontal},${distance},heading,${factor},${horizontal},target.x,descriptor4b0,byte10,matrix[1],matrix.7,target.y,heading,${factor},${horizontal},target.z`,
      'b180 ordered stores, b18c/b190/b194/b19c, descriptor/matrix/Y, fresh b1bc/b1c0/b1c4/b1cc source order');
    equal(headings,2,'heading is freshly loaded for cosine');equal(forbidden,0,'no504, actual position, GQR0 or live processor loads before missing secondary source cell');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'no new frame authority');
    equal(claimSourceHelperStorage(x.vector,x.targetDispatch),true,'borrow keeps real selector storage claim');
    equal(claimSourceHelperStorage(x.vector,{}),false,'null direction cannot transfer selector claim to another owner');
    retained(x);closed(x);
  }
  for(const mode of ['unclaimed','same-claim','other-claim','pointer-reserved'] as const) {
    const x=setup(make,configured,false);
    if(mode==='same-claim') equal(claimSourceHelperStorage(x.vector,x.targetDispatch),true,'explicit same-domain claim admitted');
    if(mode==='other-claim') equal(claimSourceHelperStorage(x.vector,{}),true,'explicit conflict claim installed');
    if(mode==='pointer-reserved') equal(reserveSourcePointerStorage(x.vector),true,'explicit pointer-domain conflict installed');
    run(x,mode==='other-claim'||mode==='pointer-reserved'?'claimed':'8006b1d0');
    retained(x,mode==='other-claim'||mode==='pointer-reserved'?[71,72,73]:[0,0,20000]);closed(x);
  }
}

function profileTests(make:Make):void {
  for(const value of [missingProfile,null,0,7,0x00070000,0x01070007,0x00060006,-1,0x100000000,0.5,NaN,Infinity,'458759',{}]) {
    const x=setup(make,value);let factors=0;
    run(x,'GQR5',(owner,key)=>{if(owner===x.data&&key===factor) factors++;});
    equal(factors,0,'malformed captured GQR5 refuses before factor');retained(x,[5,6,7]);closed(x);
  }
  for(const mode of ['changed','missing','accessor','readonly'] as const) {
    const x=setup(make);let invoked=0;
    if(mode==='changed') Reflect.set(x.profileSource,'gqr5',0);
    else corrupt(x.profileSource,'gqr5',mode,()=>invoked++);
    run(x,'8006b1d0');equal(invoked,0,'retained profile never rereads configuration/getter');retained(x);closed(x);
  }
  const x=setup(make,null);Reflect.set(x.profileSource,'gqr5',0x00070007);
  run(x,'GQR5');retained(x,[5,6,7]);closed(x);
}

function headingAndArithmeticTests(make:Make):void {
  for(const at of [1,2]) for(const value of [1,32767,32768,65535]) {
    const x=setup(make),native=Math.fround,products:number[]=[];let headings=0,factors=0,tracing=false;
    Math.fround=(value:number):number=>{if(tracing) products.push(value);return native(value);};
    try {
      run(x,at===1?'80045204':'80045238',(owner,key)=>{
        if(owner===x.sourceActor&&key==='heading'&&++headings===at) x.sourceActor.heading=value;
        if(owner===x.data&&key===factor&&++factors===at) tracing=true;
      });
    } finally {Math.fround=native;}
    equal(headings,at,'nonzero fails at reached first/second helper');equal(factors,at,'factor precedes nonzero trig boundary');
    check(products.some(v=>Object.is(v,fromBits(0x38c90fdb)*(value<<16>>16))),'real fmuls receives sign-extended raw BAM16, no early heading shortcut');
    retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','nan','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let headings=0,invoked=0;
    run(x,'heading',(owner,key)=>{if(owner===x.sourceActor&&key==='heading'&&++headings===at) corrupt(owner,'heading',kind,()=>invoked++);});
    equal(headings,at,'bad heading fails lazily at selected load');equal(invoked,0,'heading getter never invoked');
    retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  for(const at of [1,2]) for(const value of [-1,-32768,65536,0.5]) {
    const x=setup(make);let headings=0;
    run(x,'heading',(owner,key)=>{if(owner===x.sourceActor&&key==='heading'&&++headings===at) x.sourceActor.heading=value;});
    retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  for(const pair of [[-0,-0],[-7,-9],[fromBits(1),fromBits(2)],[fromBits(0x7f7fffff),fromBits(0xff7fffff)]]) {
    const x=setup(make);let reads=0,heading=false;
    run(x,'8006b1d0',(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') heading=true;
      if(heading&&owner===x.sourceActor&&key===horizontal) Reflect.set(owner,horizontal,pair[reads++]!);
    });
    equal(reads,2,'distance is freshly loaded once per sine/cosine multiply');
    equal(x.vector.x,Math.fround(pair[0]!*0),'single f32 sine multiplication preserves negative zero');
    equal(x.vector.y,0,'canonical matrix Y unchanged');equal(x.vector.z,Math.fround(pair[1]!*1),'single f32 cosine multiplication preserves fresh operand');
    // With zero sine/unit cosine, every finite f32 (including FLT_MAX) has a
    // finite product. No invented trig result is used to manufacture overflow.
    check(Number.isFinite(x.vector.x)&&Number.isFinite(x.vector.z),'finite extremal products do not spuriously overflow');
    equal(x.sourceActor.targetDistance758,20000,'758 survives fresh75c operands');closed(x);
  }
}

function sourceFaultTests(make:Make):void {
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','negative-zero','neighbor','nan','infinite','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let seen=0,invoked=0;
    run(x,factor,(owner,key)=>{if(owner===x.data&&key===factor&&++seen===at) corrupt(owner,factor,kind,()=>invoked++);});
    equal(seen,at,'factor reload remains lazy');equal(invoked,0,'factor accessor never invoked');retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  {
    const x=setup(make);Object.defineProperty(x.data,factor,{writable:false});
    run(x,'8006b1d0');retained(x);closed(x);
  }
  {
    const x=setup(make);let heading=false;
    run(x,'8006b1d0',(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading'&&!heading) {
        heading=true;Object.defineProperty(x.sourceActor,'heading',{writable:false});
        Object.defineProperty(x.sourceActor,horizontal,{writable:false});
        Object.defineProperty(x.scalarDescriptor,'byte10',{writable:false});Object.defineProperty(x.matrix,'7',{writable:false});
        Object.defineProperty(x.sourceActor,'lockTarget',{writable:false});
      }
    });
    retained(x);closed(x);
  }
  for(const at of [1,2]) for(const kind of ['missing','inherited','accessor','nan','infinite','negative-infinite','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let heading=false,seen=0,invoked=0;
    run(x,horizontal,(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') heading=true;
      if(heading&&owner===x.sourceActor&&key===horizontal&&++seen===at) corrupt(owner,horizontal,kind,()=>invoked++);
    });
    equal(seen,at,'distance reload fault reaches exact sine/cosine operand');equal(invoked,0,'distance getter never invoked');
    axes.forEach((axis,i)=>equal(x.vector[axis],(at===1?[5,6,7]:[0,0,7])[i],'bad distance preserves earlier stores'));
    equal(x.sourceActor.targetDistance758,20000,'758 retained despite malformed fresh75c');closed(x);
  }
  for(const site of ['descriptor','byte','matrix'] as const) for(const kind of ['nan','inexact','null','undefined','object','string']) {
    const x=setup(make),owner=site==='descriptor'?x.mappingActor:site==='byte'?x.scalarDescriptor:x.matrix,key=site==='descriptor'?'descriptor4b0':site==='byte'?'byte10':'7';
    let hit=false,invoked=0;
    run(x,site==='descriptor'?'descriptor':site==='byte'?'byte10':kind==='nan'||kind==='inexact'?'float32':'7',(at,field)=>{
      if(!hit&&at===owner&&field===key) {hit=true;corrupt(owner,key,kind,()=>invoked++);}
    });
    check(hit,`${site} ${kind} exact source reached`);equal(invoked,0,'descriptor/matrix source getter never invoked');retained(x,[0,6,7]);closed(x);
  }
  for(const site of ['descriptor','byte','matrix'] as const) {
    const x=setup(make),owner=site==='descriptor'?x.mappingActor:site==='byte'?x.scalarDescriptor:x.matrix,key=site==='descriptor'?'descriptor4b0':site==='byte'?'byte10':'7';
    let hit=false,invoked=0;
    run(x,'8006b1d0',(at,field)=>{
      if(!hit&&at===owner&&field===key) {
        hit=true;check(Object.isSealed(owner),'genuine canonical descriptor record is sealed');
        equal(Reflect.deleteProperty(owner,key),false,'source own property cannot be removed');
        equal(Reflect.setPrototypeOf(owner,{[key]:0}),false,'source record cannot become inherited replacement');
        equal(Reflect.defineProperty(owner,key,{get(){invoked++;return 0;}}),false,'sealed source refuses accessor replacement');
      }
    });
    check(hit,'sealed source shape checked only when reached');equal(invoked,0,'source getter never installed/invoked');retained(x);closed(x);
  }
  for(const raw of [0,1,2,127,128,255]) {
    const x=setup(make);let hit=false,lane=0;
    const valid=raw<x.matrixIds.length&&raw<128,chosen=valid?x.matrices.getMatrix(x.matrixIds[raw]!):undefined;
    run(x,valid?'8006b1d0':'world matrix',(owner,key)=>{
      if(owner===x.scalarDescriptor&&key==='byte10') {hit=true;x.scalarDescriptor.byte10=raw;if(chosen) chosen[7]=17+raw;}
      if(owner===chosen&&key==='7') lane++;
    });
    check(hit,'canonical scalar descriptor signed index read');equal(lane,valid?1:0,'only reached signed canonical world row loads lane7');
    retained(x,valid?[0,17+raw,20000]:[0,6,7]);closed(x);
  }
  {
    const x=setup(make);let invoked=0,started=false;
    run(x,'8006b1d0',(owner,key)=>{
      if(!started&&owner===x.sourceActor&&key==='heading') {
        started=true;
        for(const [record,keys] of [[x.pos,axes],[x.bytes,Array.from({length:12},(_,i)=>String(0x64+i))],
          [x.processor,['gqr0','gqr5']],[x.sourceActor,['visibilityTarget']]] as const)
          for(const field of keys) Object.defineProperty(record,field,{get(){invoked++;throw Error('unreached source scalar');},configurable:true});
        for(const lane of [0,1,2,3,4,5,6,8,9,10,11]) x.matrix[lane]=NaN;
      }
    });
    equal(invoked,0,'no source preloads: position, OBJECT bytes, processor, other matrix lanes and secondary stay lazy');retained(x);closed(x);
  }
}

function competingSourceTests(make:Make):void {
  for(const at of [1,2]) for(const site of ['factor','heading'] as const) {
    const x=setup(make);let seen=0,hit=false;
    run(x,'competing',(owner,key)=>{
      if(owner===x.data&&key===factor&&++seen===at) {
        hit=true;equal(Reflect.set(site==='factor'?x.sourceActor:x.data,site==='factor'?factor:'heading',site==='factor'?fromBits(0x38c90fdb):0),true,'competing source insertion succeeds');
      }
    });
    check(hit,'competing canonical factor/heading introduced at reached source load');retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  for(const at of [1,2]) for(const key of ['field72','short72','yaw72','byte72','byte73']) {
    const x=setup(make);let seen=0;
    run(x,'competing',(owner,field)=>{if(owner===x.data&&field===factor&&++seen===at) equal(Reflect.set(x.data,key,0),true,'raw heading shadow insertion succeeds');});
    equal(seen,at,'raw heading shadow refused at first/second factor');retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
  for(const axis of axes) for(const key of ['field50c','field50C','field510','field514','position50c','targetPosition50c','1292','byte50c']) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{if(!hit&&owner===x.vector&&field===axis) {hit=true;equal(Reflect.set(x.sourceActor,key,0),true,'raw selected-vector shadow insertion succeeds');}});
    check(hit,'raw selected-position shadow introduced at reached destination');retained(x,prefix(axis));closed(x);
  }
}

function destinationTests(make:Make):void {
  for(const axis of axes) for(const kind of ['missing','inherited','accessor','readonly'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    const mutate:Visit=(owner,key)=>{if(!hit&&owner===x.vector&&key===axis) {hit=true;corrupt(owner,axis,kind,()=>invoked++);}};
    run(x,axis,phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,`${phase} ${axis} ${kind} destination reached`);equal(invoked,0,'destination accessor/setter never invoked');
    const fields=Object.getOwnPropertyDescriptors(x.vector),expected=prefix(axis);
    axes.forEach((other,i)=>{if(other!==axis) equal(fields[other]?.value,expected[i],'precisely earlier target stores retained');});
    if(kind==='missing'||kind==='inherited') equal(fields[axis],undefined,'missing destination never recreated');
    if(kind==='accessor') check(fields[axis]!==undefined&&!('value'in fields[axis]!), 'accessor never overwritten');
    if(kind==='readonly') equal(fields[axis]?.value,expected[axes.indexOf(axis)],'readonly destination never written');
    equal(x.sourceActor.targetDistance758,20000,'prior758 retained');equal(x.sourceActor.horizontalDistance75c,20000,'prior75c retained');closed(x);
  }
  for(const axis of axes) for(const kind of ['missing','inherited','accessor','replaced','position','projection','matrix','aim','other-actor'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    run(x,kind==='other-actor'?'alias':'lockTarget',(owner,key)=>{
      if(!hit&&owner===x.vector&&key===axis) {
        hit=true;
        if(kind==='missing'||kind==='inherited'||kind==='accessor') corrupt(x.sourceActor,'lockTarget',kind,()=>invoked++);
        else if(kind==='other-actor') Reflect.set(x.targetActor,'lockTarget',x.vector);
        else if(kind==='replaced') Reflect.set(x.sourceActor,'lockTarget',{x:21,y:22,z:23});
        else Reflect.set(x.sourceActor,'lockTarget',kind==='position'?x.pos:kind==='projection'?x.stack:kind==='matrix'?x.matrix:x.sourceActor.aimOrigin518);
      }
    });
    check(hit,`${axis} ${kind} owner fault reached`);equal(invoked,0,'owner getter never invoked');retained(x,prefix(axis));closed(x);
  }
  {
    const x=setup(make);let begun=false;
    run(x,'8006b1d0',(owner,key)=>{
      if(!begun&&owner===x.sourceActor&&key==='heading') {begun=true;Object.assign(x.vector,{x:NaN,y:Symbol('unread Y'),z:undefined});}
    });
    retained(x);closed(x);
  }
}

function interruptionTests(make:Make):void {
  const sites=['heading1','factor1','distance1','x','descriptor','byte','matrix','y','heading2','factor2','distance2','z'];
  for(const site of sites) for(const kind of ['reentry','caller'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,headings=0,factors=0,distances=0;
    const mutate:Visit=(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading') headings++;
      if(owner===x.data&&key===factor) factors++;
      if(headings>0&&owner===x.sourceActor&&key===horizontal) distances++;
      const at=site.startsWith('heading')?owner===x.sourceActor&&key==='heading'&&headings===Number(site.slice(-1)):
        site.startsWith('factor')?owner===x.data&&key===factor&&factors===Number(site.slice(-1)):
        site.startsWith('distance')?owner===x.sourceActor&&key===horizontal&&headings>0&&distances===Number(site.slice(-1)):
        site==='descriptor'?owner===x.mappingActor&&key==='descriptor4b0':site==='byte'?owner===x.scalarDescriptor&&key==='byte10':
        site==='matrix'?owner===x.matrix&&key==='7':owner===x.vector&&key===site;
      if(!hit&&at) {
        hit=true;
        if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
        else {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
      }
    };
    run(x,kind==='reentry'?'reentry':'incomplete',phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,`${kind} ${phase} interruption reaches ${site}`);
    retained(x,sites.indexOf(site)<=3?[5,6,7]:sites.indexOf(site)<=7?[0,6,7]:[0,0,7]);closed(x);
  }
}

function admissionClosureTests(make:Make):void {
  for(const at of [1,2]) for(const phase of ['before','after'] as const) {
    const x=setup(make);let factors=0,fired=false,laterScalars=0;
    const mutate:Visit=(owner,key)=>{
      if(fired&&owner===x.sourceActor&&key===horizontal) laterScalars++;
      if(!fired&&owner===x.data&&key===factor&&++factors===at) {
        fired=true;
        // Genuine admission writes587 then refuses its actual out-of-range
        // command pointer slot. No runtime method or completion getter is replaced.
        rejects(()=>x.commandAdmission.dispatchSubtypeDirection(x.actor),'signed585 pointer slot');
      }
    };
    run(x,'incomplete',phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(fired,'genuine independent admission failure reached at factor');equal(laterScalars,0,'admission-only closure blocks the next75c scalar read');
    retained(x,at===1?[5,6,7]:[0,0,7]);closed(x);
  }
}

function finalSnapshotTests(make:Make):void {
  for(const axis of axes) for(const kind of ['incomplete','caller','admission','reentry','alias','missing','inherited','accessor','readonly','replaced'] as const) {
    const x=setup(make),native=Object.getOwnPropertyDescriptors;let admitted=false,hit=false,invoked=0;
    Object.getOwnPropertyDescriptors=((owner:object)=>{
      const fields=native(owner);if(owner!==x.vector) return fields;
      let enumerated=false;
      // Observe direct final-store snapshot[axis], not Object.values/entries
      // metadata enumeration. Source owners remain ordinary, unproxied records.
      return new Proxy(fields,{
        ownKeys(target) {enumerated=true;return Reflect.ownKeys(target);},
        get(target,key,receiver) {
          if(admitted&&!enumerated&&!hit&&key===axis) {
            hit=true;
            if(kind==='incomplete') markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
            else if(kind==='caller') {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
            else if(kind==='admission') rejects(()=>x.commandAdmission.dispatchSubtypeDirection(x.actor),'signed585 pointer slot');
            else if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
            else if(kind==='alias') Reflect.set(x.sourceActor,'motion',x.vector);
            else if(kind==='replaced') Reflect.set(x.sourceActor,'lockTarget',{x:31,y:32,z:33});
            else corrupt(x.vector,axis,kind,()=>invoked++);
          }
          return Reflect.get(target,key,receiver);
        },
      });
    }) as typeof native;
    try {
      run(x,kind==='reentry'?'reentry':kind==='alias'?'alias':kind==='replaced'?'lockTarget':
        ['incomplete','caller','admission'].includes(kind)?'incomplete':axis,(owner,key)=>{if(owner===x.vector&&key===axis) admitted=true;});
    } finally {Object.getOwnPropertyDescriptors=native;}
    check(hit,`${axis} ${kind} exact final snapshot interruption reached`);equal(invoked,0,'final snapshot never invokes getter/setter');
    const fields=Object.getOwnPropertyDescriptors(x.vector),expected=prefix(axis);
    for(const [i,key] of axes.entries()) if(key!==axis||!['missing','inherited','accessor'].includes(kind)) equal(fields[key]?.value,expected[i],'final snapshot prevents pending store and keeps prior stores');
    if(kind==='missing'||kind==='inherited') equal(fields[axis],undefined,'final removal never recreates destination');
    if(kind==='accessor') check(fields[axis]!==undefined&&!('value'in fields[axis]!), 'final accessor stays an accessor');
    if(kind==='readonly') equal(fields[axis]?.writable,false,'final readonly flag preserved');
    equal(x.sourceActor.targetDistance758,20000,'final snapshot retains prior758');equal(x.sourceActor.horizontalDistance75c,20000,'final snapshot retains prior75c');closed(x);
  }
}

export function runActorNullDirectionSelfTests(make:Make):void {
  let fixtures=0;const counted:Make=omit=>{fixtures++;return make(omit);};
  orderAndOwnershipTests(counted);profileTests(counted);headingAndArithmeticTests(counted);sourceFaultTests(counted);
  competingSourceTests(counted);destinationTests(counted);interruptionTests(counted);admissionClosureTests(counted);finalSnapshotTests(counted);
  console.log(`[actor-null-direction] PASS (${fixtures} genuine graph fixtures): shared captured GQR5 and exact factor, signed fresh headings/distances, source scalar/matrix order, borrowed canonical target storage, lazy faults and final snapshot closure; stops before8006b1d0 secondary load, no estimator, later actor/pass/scheduler or completed-frame claim`);
}
