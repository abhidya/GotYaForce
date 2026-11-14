import {createActorTargetCandidatesTestFixture} from './actor-target-candidates.selftest.js';
import {createSourceBattleOuterFrameRuntime,type SourceBattleOuterFrameSources} from './battle-outer-frame.js';
import {hasIncompleteSourceActorDoubleLifecycle,isSourceActorDoubleFrameClaimed,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

/** Explicit offline operands on the real allocator/HIT/dispatch graph. The
 * primary helper is never replaced: only finite live coordinates can make its
 * genuine squared result zero. Every witness still refuses inside6ae60. */
type Make=typeof createBattleTargetPreparationTestFixture;
type Bytes=Partial<Record<number,number>>;
type Vector={x:number;y:number;z:number};
type Visit=(owner:object,key:PropertyKey)=>void;
const axes=['x','y','z'] as const;
const distance='targetDistance758',horizontal='horizontalDistance75c',zero='float80437658',sentinel='float80437678';
function check(ok:boolean,why:string):void {if(!ok) throw Error(`[actor-primary-stores-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run:()=>unknown,fragment:string):string {
  let message='';try {run();} catch(error) {message=String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message||'success'}`);return message;
}
function float(bytes:Bytes,offset:number,value:number):void {
  const view=new DataView(new ArrayBuffer(4));view.setFloat32(0,value,false);
  for(let i=0;i<4;i++) bytes[offset+i]=view.getUint8(i);
}
function position(bytes:Bytes,x:number,y=0,z=0):void {float(bytes,0x64,x);float(bytes,0x68,y);float(bytes,0x6c,z);}
function setup(make:Make) {
  const x=createActorTargetCandidatesTestFixture(make),stack:Vector={x:91,y:92,z:93},vector:Vector={x:71,y:72,z:73};
  x.sources.projectionStack=stack;Reflect.set(x.rootSources,'processor',x.actionSources.processor);x.scalarDescriptor.byte10=1;
  const processor=x.actionSources.processor,pos=x.sourceActor.pos,data=x.commandAdmission.getData();
  const matrix=x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[1]!);
  matrix[3]=0;matrix[7]=0;matrix[11]=0;
  equal(x.hits.registerHit(x.child,1),1,'genuine HIT registration completes');
  const id=x.hitIds[0]!,bytes=x.hitBytes[0]!,descriptor=x.allocator.readPointer(id,0x28)!;
  const address=x.allocator.getInteriorAddress(descriptor)!;
  equal(address.base,x.hitTableIdentity,'real HIT descriptor owns the selected OBJECT');
  const table=x.hitBinding.pointer3fc;table[address.byteOffset+2]=2;table[address.byteOffset+3]=0;
  x.allocator.writePointer(id,0x20,x.target);position(bytes,5,6,7);
  x.list[0]=id;x.scratch[0]=null;Reflect.set(x.sourceActor,'lockTarget',vector);
  Object.assign(pos,{x:1,y:2,z:3});
  // These fields and constants are explicit witness hydration, never defaults.
  equal(Object.getOwnPropertyDescriptor(x.sourceActor,distance),undefined,'actual758 has no constructor default');
  equal(Object.getOwnPropertyDescriptor(x.sourceActor,horizontal),undefined,'actual75c has no constructor default');
  equal(Object.getOwnPropertyDescriptor(data,zero),undefined,'shared+0 has no fixture/constructor default');
  Object.assign(x.sourceActor,{targetDistance758:91,horizontalDistance75c:93});
  Reflect.set(data,zero,0);Reflect.set(data,sentinel,20000);
  const outerSources:SourceBattleOuterFrameSources={scheduler:x.scheduler,systemGlobals:x.systemGlobals,
    massPreparation:x.massPreparation,targetPreparation:x.targetPreparation};
  const frame=createSourceBattleOuterFrameRuntime(outerSources);
  return Object.assign(x,{stack,vector,processor,pos,data,matrix,id,bytes,frame,outerSources});
}
type Fixture=ReturnType<typeof setup>;
/** First canonical508 starts the primary window. Changing A here leaves the
 * genuine completed selector/vector stores intact. Null witnesses change the
 * actual OBJECT+20 before6b850's final actor-pointer reload, not a fake return. */
function run(x:Fixture,fragment:string,before:Visit=()=>{},after?:Visit,nullable=false):string {
  const original=Object.getOwnPropertyDescriptor;
  let helper=false,primary=false,selected=false,changed=false,message='',later=0;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
    if(owner===x.targetPreparation&&key==='targetDispatch') selected=true;
    if(nullable&&selected&&!changed&&owner===x.admissionState&&key==='pointer504') {
      changed=true;x.allocator.writePointer(x.id,0x20,null);
    }
    if(!helper) {if(owner===x.vector&&key==='z') helper=true;}
    else if(!primary&&owner===x.admissionState&&key==='pointer508') {
      primary=true;if(!nullable) Object.assign(x.pos,{x:5,y:6,z:7});
    }
    if(primary) {
      if(owner===x.physicalIdentities&&key==='1'||owner===x.slotTargets[1]&&key==='active0'||
        owner===x.sourceActor&&key==='active0'||owner===x.massPreparation&&key==='physicalBlock'||
        owner===x.groups||owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) later++;
      before(owner,key);
    }
    const result=original(owner,key);
    if(primary) after?.(owner,key);
    return result;
  }) as typeof original;
  try {message=rejects(()=>x.frame.runFrame(),fragment);} finally {Object.getOwnPropertyDescriptor=original;}
  check(primary,'genuine post-helper primary branch reached');equal(later,0,'no boundary reaches another actor, pass or scheduler operation');
  if(nullable) {check(changed,'actual OBJECT+20 changed before helper final508 store');equal(x.admissionState.pointer508,null,'helper genuinely stores null508');}
  return message;
}
function retained(x:Fixture):void {
  equal(x.sourceActor.byte502,1,'completed helper502 store survives');
  axes.forEach((axis,i)=>equal(x.vector[axis],[5,6,7][i],`completed helper ${axis} store survives`));
  axes.forEach(axis=>equal(x.stack[axis],0,`projection ${axis} store survives`));
  equal(x.globals.count804361a0,1,'candidate count survives');equal(x.scratch[0],x.id,'selected original OBJECT survives');
  equal(x.massPreparation.orderCount.count80436260,6,'mass ordering survives');equal(x.massHost.sourceArrowMass204,1200,'mass update survives');
}
function closed(x:Fixture):void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'primary refusal closes actual caller permanently');
  rejects(()=>x.frame.runFrame(),'permanently incomplete');rejects(()=>x.targetDispatch.dispatchActor(x.actor),'incomplete');
  rejects(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
  for(const next of [()=>x.scheduler.runGroup(9),()=>x.scheduler.runSlots(8),()=>x.scheduler.runWrapper(8)]) rejects(next,'exclusively owned');
  rejects(()=>x.root.dispatchStoredRoot(x.child),'exclusively owned');
  rejects(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
}
function distances(x:Fixture,a:unknown,b:unknown):void {
  equal(Reflect.get(x.sourceActor,distance),a,'actual758 value');equal(Reflect.get(x.sourceActor,horizontal),b,'actual75c value');
}
function rawKey(key:PropertyKey):boolean {return /^\d+$/.test(String(key))&&Number(key)>=0x64&&Number(key)<0x70;}

function branchOrderTests(make:Make):void {
  {
    const x=setup(make),events:string[]=[],claimed=isSourceActorDoubleFrameClaimed(x.sourceActor);let threshold=false,forbidden=0,profile=0;
    run(x,'8006b098',(owner,key)=>{
      if(owner===x.data&&key===zero) threshold=true;
      if(!threshold) return;
      if(owner===x.data&&(key===zero||key===sentinel)) events.push(String(key));
      if(owner===x.sourceActor&&(key===distance||key===horizontal)) events.push(String(key));
      if(owner===x.pos&&axes.includes(key as typeof axes[number])) events.push(`a.${String(key)}`);
      if(owner===x.bytes&&rawKey(key)) events.push(`b.${Number(key).toString(16)}`);
      if(owner===x.admissionState&&key==='pointer508') events.push('508');
      if(owner===x.processor&&key==='gqr0') profile++;
      if(owner===x.physicalIdentities&&key==='1'||owner===x.slotTargets[1]&&key==='active0'||
        owner===x.massPreparation&&key==='physicalBlock'||owner===x.groups||
        owner===x.matchGlobals&&['maskD1','maskD2'].includes(String(key))) forbidden++;
    });
    equal(events.join(','),`${zero},${distance},${zero},a.x,b.64,b.65,b.66,b.67,a.z,b.6c,b.6d,b.6e,b.6f,${horizontal},508`,
      'afB0, b008, b00c, b010/b014/b018/b01c, b088 and fresh b094 run in scalar source order');
    equal(profile,0,'horizontal scalar path loads no GQR0');equal(forbidden,0,'no later actor, pass or scheduler operation');
    equal(isSourceActorDoubleFrameClaimed(x.sourceActor),claimed,'primary stores never grant frame authority');
    distances(x,0,0);retained(x);closed(x);
  }
  for(const values of [[-0,0,-0],[Math.fround(1e-40),Math.fround(-1e-40),Math.fround(1e-40)],[2**-75,0,2**-75],[1.25,-2.5,3.75]]) {
    const x=setup(make);let changed=false;
    run(x,'8006b098',(owner,key)=>{
      if(!changed&&owner===x.admissionState&&key==='pointer508') {
        changed=true;axes.forEach((axis,i)=>x.pos[axis]=values[i]!);
        if(Math.abs(values[0]!)<1e-20) position(x.bytes,0,0,0);else position(x.bytes,...values as [number,number,number]);
      }
    });
    distances(x,0,0);retained(x);closed(x);
  }
  {
    const x=setup(make);let dest=0,zeroLoads=0;
    run(x,'8006afbc',(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer508') Object.assign(x.pos,{x:-5,y:-6,z:-7});
      if(owner===x.sourceActor&&(key===distance||key===horizontal)) dest++;
      if(owner===x.data&&key===zero) zeroLoads++;
    });
    distances(x,91,93);equal(dest,0,'positive genuine squared distance refuses before either destination admission');
    equal(zeroLoads,1,'positive squared branch loads the exact threshold first');retained(x);closed(x);
  }
  for(const axis of ['x','z'] as const) {
    const x=setup(make);let changed=false,stored=false,reads=0;
    run(x,'8006b03c',(owner,key)=>{
      if(owner===x.sourceActor&&key===distance) {changed=true;stored=true;}
      if(stored&&owner===x.pos&&key===axis) {x.pos[axis]=-x.pos[axis];reads++;}
      if(owner===x.sourceActor&&key===horizontal) throw Error('positive horizontal must stop before75c');
    });
    check(changed,'first distance store reached');equal(reads,1,`fresh horizontal ${axis} sees the live change`);
    distances(x,0,93);retained(x);closed(x);
  }
  {
    const x=setup(make),events:string[]=[],forbiddenNames:string[]=[];let forbidden=0;
    run(x,'8006b190',(owner,key)=>{
      if(owner===x.data&&(key===zero||key===sentinel)) events.push(String(key));
      if(owner===x.sourceActor&&[distance,horizontal,'heading'].includes(String(key))) events.push(String(key));
      if(owner===x.admissionState&&key==='pointer504'||owner===x.sourceActor&&key==='pos'||
        owner===x.pos&&axes.includes(key as typeof axes[number])||owner===x.bytes&&rawKey(key)||
        owner===x.rootSources&&key==='processor'||owner===x.processor&&key==='gqr0'||
        owner===x.vector&&axes.includes(key as typeof axes[number])) {forbidden++;forbiddenNames.push(String(key));}
    },undefined,true);
    equal(events.join(','),`${sentinel},${horizontal},${distance},heading`,'null path loads20000 once, stores75c then758, then loads heading');
    equal(forbidden,0,`null path never reads504, position, profile or target vector [${forbiddenNames.join(',')}]`);distances(x,20000,20000);retained(x);closed(x);
  }
}

function captureAndFreshTests(make:Make):void {
  {
    const x=setup(make),replacement:Bytes={};for(let i=0;i<0x70;i++) replacement[i]=0;
    x.allocator.registerObject(Symbol('alternate original OBJECT'),replacement);position(replacement,NaN,NaN,NaN);
    let threshold=false,otherReads=0,p504=0,p508=0;
    const opaque={};Object.defineProperty(opaque,'pos',{get(){throw Error('fresh508 must remain opaque');}});
    run(x,'8006b098',(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer504') p504++;
      if(owner===x.admissionState&&key==='pointer508') p508++;
      if(!threshold&&owner===x.data&&key===zero) {
        threshold=true;x.admissionState.pointer504=replacement;Reflect.set(x.admissionState,'pointer508',opaque);
      }
      if(owner===replacement&&rawKey(key)) otherReads++;
    });
    equal(p504,1,'captured504 is never reloaded for horizontal');equal(p508,2,'mandatory6d228 operand reloads canonical508');
    equal(otherReads,0,'horizontal keeps original OBJECT bytes despite504 mutation');distances(x,0,0);retained(x);closed(x);
  }
  for(const fresh of [null,{},17]) {
    const x=setup(make);let stores=0,p508=0;
    run(x,typeof fresh==='number'?'pointer':'8006b098',(owner,key)=>{
      if(owner===x.sourceActor&&key===horizontal) {stores++;Reflect.set(x.admissionState,'pointer508',fresh);}
      if(owner===x.admissionState&&key==='pointer508') p508++;
    });
    equal(stores,1,'75c reached before fresh508');equal(p508,2,'fresh508 is actually loaded');distances(x,0,0);retained(x);closed(x);
  }
  for(const phase of ['before','after'] as const) {
    const x=setup(make);let n=0;
    const mutation:Visit=(owner,key)=>{if(owner===x.sourceActor&&key===horizontal&&++n===1) Reflect.set(x.data,sentinel,123);};
    run(x,'8006b190',phase==='before'?mutation:()=>{},phase==='after'?mutation:undefined,true);
    equal(n,1,'first null store admission reached');distances(x,20000,20000);retained(x);closed(x);
  }
  {
    const x=setup(make);let n=0;
    run(x,zero,(owner,key)=>{if(owner===x.data&&key===zero&&++n===2) Reflect.set(x.data,zero,-0);});
    equal(n,2,'horizontal threshold reloads after758 rather than reusing earlier+0');distances(x,0,93);retained(x);closed(x);
  }
  {
    const x=setup(make);let threshold=false;
    run(x,'8006b098',(owner,key)=>{
      if(owner===x.data&&key===zero&&!threshold) {
        threshold=true;Object.freeze(x.pos);Object.freeze(x.bytes);Object.defineProperty(x.processor,'gqr0',{writable:false});
        Object.defineProperty(x.data,zero,{writable:false});
      }
    });
    distances(x,0,0);retained(x);closed(x);
  }
}

function constantFaultTests(make:Make):void {
  for(const branch of ['primary','horizontal','null'] as const) for(const kind of ['missing','inherited','accessor','negative-zero','wrong','neighbor','nan','infinite','inexact','string','null','undefined','object','boolean'] as const) {
    const x=setup(make);let n=0,hit=false,invoked=0;
    const key=branch==='null'?sentinel:zero,at=branch==='horizontal'?2:1;
    run(x,key,(owner,field)=>{
      if(owner===x.data&&field===key&&++n===at) {
        hit=true;
        if(kind==='accessor') Object.defineProperty(x.data,key,{get(){invoked++;return 0;},configurable:true});
        else if(kind==='missing'||kind==='inherited') {Reflect.deleteProperty(x.data,key);if(kind==='inherited') Object.setPrototypeOf(x.data,{[key]:branch==='null'?20000:0});}
        else Reflect.set(x.data,key,kind==='negative-zero'?-0:kind==='wrong'?1:kind==='neighbor'?(branch==='null'?20000+2**-9:2**-149):kind==='nan'?NaN:kind==='infinite'?Infinity:kind==='inexact'?1+2**-30:kind==='null'?null:kind==='undefined'?undefined:kind==='object'?{}:kind==='boolean'?false:'0');
      }
    },undefined,branch==='null');
    check(hit,`${branch} ${kind} constant fault reached`);equal(invoked,0,'constant accessor never invoked');
    distances(x,branch==='horizontal'?0:91,93);retained(x);closed(x);
  }
}

function destinationFaultTests(make:Make):void {
  for(const nullable of [false,true]) for(const field of [distance,horizontal]) for(const kind of ['missing','inherited','accessor','readonly'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    const mutation:Visit=(owner,key)=>{
      if(!hit&&owner===x.sourceActor&&key===field) {
        hit=true;
        if(kind==='readonly') Object.defineProperty(owner,key,{writable:false});
        else if(kind==='accessor') Object.defineProperty(owner,key,{get(){invoked++;return 0;},set(){invoked++;},configurable:true});
        else {Reflect.deleteProperty(owner,key);if(kind==='inherited') Object.setPrototypeOf(owner,{[key]:0});}
      }
    };
    run(x,field,phase==='before'?mutation:()=>{},phase==='after'?mutation:undefined,nullable);
    check(hit,`${nullable?'null':'nonnull'} ${kind} ${phase} destination ${field} reached`);equal(invoked,0,'store never invokes old-value accessor/setter');
    const other=field===distance?horizontal:distance;
    equal(Reflect.get(x.sourceActor,other),nullable?(field===distance?20000:91):(field===horizontal?0:93),'failed store retains precisely the earlier stores');
    retained(x);closed(x);
  }
  for(const nullable of [false,true]) {
    const x=setup(make);Object.assign(x.sourceActor,{targetDistance758:NaN,horizontalDistance75c:Symbol('unread prior distance')});
    run(x,nullable?'8006b190':'8006b098',()=>{},undefined,nullable);
    distances(x,nullable?20000:0,nullable?20000:0);retained(x);closed(x);
  }
  for(const kind of ['missing','accessor','readonly'] as const) {
    const x=setup(make);let reached=false,invoked=0;
    run(x,'8006afbc',(owner,key)=>{
      if(owner===x.admissionState&&key==='pointer508'&&!reached) {
        reached=true;Object.assign(x.pos,{x:-5,y:-6,z:-7});
        for(const field of [distance,horizontal]) {
          if(kind==='missing') Reflect.deleteProperty(x.sourceActor,field);
          else if(kind==='readonly') Object.defineProperty(x.sourceActor,field,{writable:false});
          else Object.defineProperty(x.sourceActor,field,{get(){invoked++;throw Error('unreached destination');},configurable:true});
        }
      }
    });
    equal(invoked,0,'positive squared refusal never admits unreached distance destinations');retained(x);closed(x);
  }
}

function horizontalFaultTests(make:Make):void {
  {
    const x=setup(make),native=Math.fround,arithmetic:number[]=[];let thresholds=0,tracing=false;
    // Observe the original arithmetic without substituting any helper return.
    // The f32 validators expose the operands of the two real subtracts and sum;
    // the two rounded multiply sites are separately visible between them.
    Math.fround=(value:number):number=>{if(tracing) arithmetic.push(value);return native(value);};
    try {
      run(x,'8006b03c',(owner,key)=>{
        if(owner===x.data&&key===zero&&++thresholds===2) Object.assign(x.pos,{x:8,z:13});
      },(owner,key)=>{if(thresholds===2&&owner===x.bytes&&key==='111') tracing=true;});
    } finally {Math.fround=native;}
    equal(arithmetic.join(','),'8,-5,13,-7,9,9,36,36,9,36',
      'all four lfs finish before X subtraction, Z subtraction, separate X/Z f32 squares, then separate f32 sum');
    distances(x,0,93);retained(x);closed(x);
  }
  {
    const x=setup(make);let loads=0,invoked=0;
    run(x,'8006b098',(owner,key)=>{
      if(owner===x.data&&key===zero&&++loads===2) {
        Object.defineProperty(x.pos,'y',{get(){invoked++;throw Error('horizontal A.y is unreached');},configurable:true});
        for(let offset=0x68;offset<0x6c;offset++) Object.defineProperty(x.bytes,String(offset),{
          get(){invoked++;throw Error('horizontal B.y is unreached');},configurable:true});
        Object.defineProperty(x.processor,'gqr0',{get(){invoked++;throw Error('horizontal GQR0 is unreached');},configurable:true});
      }
    });
    equal(invoked,0,'horizontal scalar path neither admits Y nor invokes a processor profile');distances(x,0,0);retained(x);closed(x);
  }
  const sites=['a-x','b-100','b-101','b-102','b-103','a-z','b-108','b-109','b-110','b-111'];
  for(const site of sites) for(const kind of ['missing','inherited','accessor','invalid','inexact'] as const) {
    const x=setup(make);let horizontalWindow=false,hit=false,invoked=0,zeroLoads=0;const reads:string[]=[];
    const owner=site.startsWith('a')?x.pos:x.bytes,key=site.slice(2);
    run(x,kind==='invalid'||kind==='inexact'?(site.startsWith('a')?'float32':'byte'):'own data',(at,field)=>{
      if(at===x.data&&field===zero&&++zeroLoads===2) horizontalWindow=true;
      if(!horizontalWindow) return;
      if(at===x.pos&&['x','z'].includes(String(field))) reads.push(`a-${String(field)}`);
      if(at===x.bytes&&rawKey(field)) reads.push(`b-${String(field)}`);
      if(!hit&&at===owner&&field===key) {
        hit=true;
        if(kind==='accessor') Object.defineProperty(owner,key,{get(){invoked++;return 0;},configurable:true});
        else if(kind==='missing'||kind==='inherited') {const previous=Reflect.get(owner,key);Reflect.deleteProperty(owner,key);if(kind==='inherited') Object.setPrototypeOf(owner,{[key]:previous});}
        else Reflect.set(owner,key,site.startsWith('a')?(kind==='invalid'?NaN:1+2**-30):(kind==='invalid'?256:0.5));
      }
    });
    check(hit,`${kind} horizontal ${site} fault reached`);equal(invoked,0,'horizontal source accessor is not invoked');
    equal(reads.join(','),sites.slice(0,sites.indexOf(site)+1).join(','),'horizontal failure stops at exact source scalar/byte');
    distances(x,0,93);retained(x);closed(x);
  }
  for(const site of ['subtract-x','subtract-z','square-x','square-z','sum'] as const) {
    const x=setup(make),max=Math.fround(3.4e38),large=Math.fround(2e19),sum=Math.fround(1.4e19);let n=0;const reads:string[]=[];
    run(x,'float32',(owner,key)=>{
      if(owner===x.data&&key===zero&&++n===2) {
        Object.assign(x.pos,{x:0,y:0,z:0});position(x.bytes,0,0,0);
        if(site==='subtract-x') {x.pos.x=max;position(x.bytes,-max);}
        if(site==='subtract-z') {x.pos.z=max;position(x.bytes,0,0,-max);}
        if(site==='square-x') x.pos.x=large;
        if(site==='square-z') x.pos.z=large;
        if(site==='sum') {x.pos.x=sum;x.pos.z=sum;}
      }
      if(n===2&&owner===x.pos&&axes.includes(key as typeof axes[number])) reads.push(`a.${String(key)}`);
      if(n===2&&owner===x.bytes&&rawKey(key)) reads.push(`b.${String(key)}`);
    });
    equal(reads.join(','),'a.x,b.100,b.101,b.102,b.103,a.z,b.108,b.109,b.110,b.111',`${site}: all four lfs precede horizontal arithmetic`);
    distances(x,0,93);retained(x);closed(x);
  }
}

function headingTests(make:Make):void {
  for(const value of [0,1,32767,32768,65535]) {
    const x=setup(make);let reads=0;
    run(x,'8006b190',(owner,key)=>{if(owner===x.sourceActor&&key==='heading') {reads++;x.sourceActor.heading=value;}},undefined,true);
    equal(reads,1,'heading loaded once at b18c');distances(x,20000,20000);retained(x);closed(x);
  }
  for(const kind of ['missing','inherited','accessor','nan','fraction','signed-negative','too-negative','too-positive'] as const) {
    const x=setup(make);let hit=false,invoked=0;
    run(x,'heading',(owner,key)=>{
      if(owner===x.sourceActor&&key==='heading'&&!hit) {
        hit=true;
        if(kind==='accessor') Object.defineProperty(owner,key,{get(){invoked++;return 0;},configurable:true});
        else if(kind==='missing'||kind==='inherited') {Reflect.deleteProperty(owner,key);if(kind==='inherited') Object.setPrototypeOf(owner,{heading:0});}
        else Reflect.set(owner,key,kind==='nan'?NaN:kind==='fraction'?1.5:kind==='signed-negative'?-1:kind==='too-negative'?-32769:65536);
      }
    },undefined,true);
    check(hit,`${kind} signed heading fault reached`);equal(invoked,0,'heading accessor never invoked');distances(x,20000,20000);retained(x);closed(x);
  }
}

function aliasAndOwnershipTests(make:Make):void {
  const raw=['field758','field75c','field75C','float758','float75c','float75C',
    ...Array.from({length:8},(_,i)=>0x758+i).flatMap(offset=>[String(offset),'byte'+offset.toString(16),'byte'+offset.toString(16).toUpperCase()])];
  for(const key of [...new Set(raw)]) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{
      if(!hit&&owner===x.sourceActor&&field===distance) {hit=true;Reflect.set(x.sourceActor,key,17);}
    });
    check(hit,`late raw primary shadow ${key} reached at758 admission`);distances(x,91,93);retained(x);closed(x);
  }
  for(const target of ['data','position','projection','actual-target'] as const) for(const key of [distance,horizontal,zero,sentinel]) {
    const x=setup(make);let hit=false;
    const owner=target==='data'?x.data:target==='position'?x.pos:target==='projection'?x.stack:x.targetActor;
    // A different real world-bound actor may own its own canonical distances.
    if(target==='actual-target'&&(key===distance||key===horizontal)) continue;
    // Both constants already belong to this exact shared-data record.
    if(target==='data'&&(key===zero||key===sentinel)) continue;
    run(x,'competing',(at,field)=>{
      if(!hit&&at===x.sourceActor&&field===distance) {hit=true;Reflect.set(owner,key,17);}
    });
    check(hit,`late duplicate ${target}.${key} reached`);distances(x,91,93);retained(x);closed(x);
  }
  {
    const x=setup(make);let hit=false;
    run(x,'8006b098',(owner,key)=>{
      if(!hit&&owner===x.data&&key===zero) {
        hit=true;Object.assign(x.targetActor,{targetDistance758:123,horizontalDistance75c:456});
      }
    });
    distances(x,0,0);equal(Reflect.get(x.targetActor,distance),123,'different genuine actual actor owns its own758');
    equal(Reflect.get(x.targetActor,horizontal),456,'different genuine actual actor owns its own75c');retained(x);closed(x);
  }
  for(const key of ['field72','short72','yaw72','114','115','byte72','byte73']) {
    const x=setup(make);let hit=false;
    run(x,'competing',(owner,field)=>{
      if(!hit&&owner===x.sourceActor&&field===distance) {hit=true;Reflect.set(x.sourceActor,key,17);}
    },undefined,true);
    check(hit,`late heading shadow ${key} reached before b18c`);distances(x,20000,20000);retained(x);closed(x);
  }
  for(const target of ['admission','position','motion','projection'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,zeroLoads=0;
    const mutate:Visit=(owner,key)=>{
      if(owner===x.data&&key===zero) zeroLoads++;
      if(!hit&&zeroLoads===2&&owner===x.pos&&key==='x') {
        hit=true;
        if(target==='admission') Reflect.set(x.targetPreparation,'admission',{});
        if(target==='position') x.sourceActor.pos={x:5,y:6,z:7};
        if(target==='motion') Reflect.set(x.sourceActor,'motion',x.pos);
        if(target==='projection') Reflect.set(x.sources,'projectionStack',x.pos);
      }
    };
    run(x,target==='admission'?'retained command':target==='position'?'position':'alias',phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined);
    check(hit,`${phase} horizontal ${target} ownership replacement reached`);distances(x,0,93);retained(x);closed(x);
  }
}

function interruptionTests(make:Make):void {
  const sites=['constant1','store758','constant2','a-x','b-x','a-z','b-z','store75c','fresh508','null-constant','null75c','null758','heading'];
  for(const site of sites) for(const kind of ['reentry','caller'] as const) for(const phase of ['before','after'] as const) {
    const x=setup(make);let hit=false,zeros=0,pointers=0;
    const nullable=site.startsWith('null')||site==='heading';
    const mutate:Visit=(owner,key)=>{
      if(owner===x.data&&key===zero) zeros++;
      if(owner===x.admissionState&&key==='pointer508') pointers++;
      const at=site==='constant1'?owner===x.data&&key===zero&&zeros===1:
        site==='constant2'?owner===x.data&&key===zero&&zeros===2:
        site==='store758'||site==='null758'?owner===x.sourceActor&&key===distance:
        site==='store75c'||site==='null75c'?owner===x.sourceActor&&key===horizontal:
        site==='fresh508'?owner===x.admissionState&&key==='pointer508'&&pointers===2:
        site==='null-constant'?owner===x.data&&key===sentinel:
        site==='heading'?owner===x.sourceActor&&key==='heading':
        zeros===2&&(site.startsWith('a')?owner===x.pos&&key===site.slice(2):owner===x.bytes&&key===(site==='b-x'?'100':'108'));
      if(!hit&&at) {
        hit=true;
        if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
        else {x.control.getActorBinding(x.actor).activeMask579=256;rejects(()=>x.control.update(x.actor,1),'activeMask579');}
      }
    };
    run(x,kind==='reentry'?'reentry':'incomplete',phase==='before'?mutate:()=>{},phase==='after'?mutate:undefined,nullable);
    check(hit,`${kind} ${phase} at ${site} reached`);
    const a=site==='fresh508'||site==='heading'?nullable?20000:0:
      nullable?91:['constant1','store758'].includes(site)?91:0;
    const b=nullable?['null758','heading'].includes(site)?20000:93:site==='fresh508'?0:93;
    distances(x,a,b);retained(x);closed(x);
  }
}

function finalSnapshotInterruptionTests(make:Make):void {
  for(const nullable of [false,true]) for(const field of [distance,horizontal])
    for(const kind of ['incomplete','caller','reentry','alias','removed','inherited','accessor','readonly'] as const) {
    const x=setup(make),native=Object.getOwnPropertyDescriptors,originalValue=Reflect.get(x.sourceActor,field);
    let admitted=false,hit=false,invoked=0;
    const shape=['removed','inherited','accessor','readonly'].includes(kind);
    // Only the direct final-store snapshot[key] lookup triggers this witness.
    // Metadata Object.values/entries enumeration forwards the native snapshot
    // unchanged and is explicitly excluded. No actual source object is proxied.
    Object.getOwnPropertyDescriptors=((owner:object)=>{
      const fields=native(owner);if(owner!==x.sourceActor) return fields;
      let enumerated=false;
      return new Proxy(fields,{
        ownKeys(target) {enumerated=true;return Reflect.ownKeys(target);},
        get(target,key,receiver) {
          if(admitted&&!enumerated&&!hit&&key===field) {
            hit=true;
            if(kind==='incomplete') markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
            else if(kind==='caller') {
              x.control.getActorBinding(x.actor).activeMask579=256;
              rejects(()=>x.control.update(x.actor,1),'activeMask579');
            } else if(kind==='reentry') rejects(()=>x.frame.runFrame(),'same-runtime reentry');
            else if(kind==='alias') Reflect.set(x.sourceActor,'field758',17);
            else if(kind==='removed'||kind==='inherited') {
              Reflect.deleteProperty(x.sourceActor,field);
              if(kind==='inherited') Object.setPrototypeOf(x.sourceActor,{[field]:originalValue});
            } else if(kind==='accessor') Object.defineProperty(x.sourceActor,field,{
              get(){invoked++;return originalValue;},set(){invoked++;},configurable:true});
            else Object.defineProperty(x.sourceActor,field,{writable:false});
          }
          return Reflect.get(target,key,receiver);
        },
      });
    }) as typeof native;
    try {
      run(x,shape?field:kind==='alias'?'competing':kind==='reentry'?'reentry':'incomplete',
        (owner,key)=>{if(owner===x.sourceActor&&key===field) admitted=true;},undefined,nullable);
    } finally {Object.getOwnPropertyDescriptors=native;}
    check(hit,`${nullable?'null':'nonnull'} ${kind} at exact final ${field} snapshot reached`);
    if(shape) {
      equal(invoked,0,'final snapshot shape change never invokes an accessor or setter');
      const current=Object.getOwnPropertyDescriptor(x.sourceActor,field);
      if(kind==='removed'||kind==='inherited') equal(current,undefined,'final snapshot removal never recreates an own field');
      if(kind==='accessor') check(current!==undefined&&!('value' in current),'final snapshot accessor is not overwritten');
      if(kind==='readonly') {
        equal(current?.writable,false,'final readonly destination stays readonly');
        equal(current?.value,originalValue,'final readonly destination is not written');
      }
      const other=field===distance?horizontal:distance;
      equal(Reflect.get(x.sourceActor,other),nullable?(field===distance?20000:91):(field===horizontal?0:93),
        'final snapshot shape failure preserves exactly earlier stores');
    } else distances(x,nullable?91:field===distance?91:0,nullable?field===horizontal?93:20000:93);
    retained(x);closed(x);
  }
}

export function runActorPrimaryStoresSelfTests(make:Make):void {
  let fixtures=0;const counted:Make=omit=>{fixtures++;return make(omit);};
  branchOrderTests(counted);captureAndFreshTests(counted);constantFaultTests(counted);destinationFaultTests(counted);
  horizontalFaultTests(counted);headingTests(counted);aliasAndOwnershipTests(counted);interruptionTests(counted);finalSnapshotInterruptionTests(counted);
  console.log(`[actor-primary-stores] PASS (${fixtures} genuine graph fixtures): genuine post6b850 primary+0 gates, explicit actual758/75c partial stores, captured OBJECT horizontal scalar/byte/arithmetic order, fresh canonical508 and null20000/heading order, lazy source/destination faults and permanent outer closure; stops at afbc/b03c/b098/b190, no estimator, later actor/pass/scheduler, completed-frame or console claim`);
}
