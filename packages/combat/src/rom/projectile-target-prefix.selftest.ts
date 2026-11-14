import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import type {SourceProjectileFlightTestFixture} from './projectile-flight-prefix.selftest.js';

interface TargetStack {displacement: {x: number; y: number; z: number}}
/** The existing genuine completed-spawn/HIT graph, with separately supplied
 * source stack storage and the graph's SAME explicit GQR0 processor record.
 * Neither the factory nor this contract hydrates a retail target or heading.
 * Every nonnull pointer and altered arithmetic operand below is synthetic. */
export interface SourceProjectileTargetTestFixture extends SourceProjectileFlightTestFixture {
  targetStack: TargetStack;
  targetProcessor: {gqr0: number};
  rootSources: SourceProjectileFlightTestFixture['rootSources'] & {
    targetStack?: TargetStack;
    processor?: {gqr0: number};
  };
}
const POS = [0x20,0x24,0x28] as const, AIM = [0x144,0x148,0x14c] as const;
const DIRECTION = [0x38,0x3c,0x40] as const, AXES = ['x','y','z'] as const;
const POSITIVE = '8007dec0 reached actual frsqrte';
const ZERO = '8007df0c reached unauthenticated FLOAT_804379c0';
const NO_STACK = 'explicit target stack unavailable';
const PROFILE = 'explicit GQR0 float processor profile';
const NORMALIZE = 'actual8020bab8 Normalize';
const SENTINELS = [71,-23,59];
const MAX = (2-2**-23)*2**127;
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[projectile-target-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
function bits(value: number): number {
  const data=new DataView(new ArrayBuffer(4));data.setFloat32(0,value,false);return data.getUint32(0,false);
}
function words(x: SourceProjectileTargetTestFixture, offsets: readonly number[]): number[] {
  return offsets.map(offset=>x.allocator.readU32(x.child,offset));
}
function sameWords(x: SourceProjectileTargetTestFixture, offsets: readonly number[], expected: readonly number[], why: string): void {
  offsets.forEach((offset,i)=>equal(x.allocator.readU32(x.child,offset),expected[i],`${why} +${offset.toString(16)}`));
}
function stackBits(x: SourceProjectileTargetTestFixture, expected: readonly number[], why: string): void {
  AXES.forEach((axis,i)=>equal(bits(x.targetStack.displacement[axis]),expected[i],`${why} ${axis}`));
}
function retained(...records: object[]): () => void {
  const snapshots=records.map(record=>Object.getOwnPropertyDescriptors(record));
  return ()=>records.forEach((record,index)=>{
    const saved=snapshots[index]!,after=Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(after).length,Reflect.ownKeys(saved).length,'failed replay retains property count');
    for(const key of Object.keys(saved)) {
      const a=after[key],b=saved[key]!;
      check(a!==undefined && Object.is(a.value,b.value) && a.get===b.get && a.set===b.set &&
        a.writable===b.writable && a.configurable===b.configurable && a.enumerable===b.enumerable,
      `failed replay retains descriptor ${key}`);
    }
  });
}
/** Observe genuine descriptor loads and store preflights. No runtime callee is
 * replaced with a successful callback, and after sees the captured descriptor. */
function observe(run: () => void, before: (owner: object,key: PropertyKey) => void,
  after?: (owner: object,key: PropertyKey) => void): void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner: object,key: PropertyKey)=>{
    before(owner,key);const result=original(owner,key);after?.(owner,key);return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
function dispatch(x: SourceProjectileTargetTestFixture, boundary=POSITIVE): void {
  rejects(()=>x.root.dispatchStoredRoot(x.child),boundary);
}
function matrixRecords(x: SourceProjectileTargetTestFixture): number[][] {
  return [x.matrices.getMatrix(x.initializationStack.rotationX),x.matrices.getMatrix(x.initializationStack.rotationY)];
}
function closed(x: SourceProjectileTargetTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failure closes same actual Double owner');
  const keep=retained(x.objectBytes,x.nextObjectBytes,x.hitPool,x.descriptorPool,x.drawList,
    ...x.hitBytes,...matrixRecords(x),x.targetStack,x.targetStack.displacement);
  rejects(()=>x.root.dispatchStoredRoot(x.child),'incomplete');
  rejects(()=>x.hits.registerHit(x.child,1),'incomplete');
  rejects(()=>x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');keep();
}
function completedHit(x: SourceProjectileTargetTestFixture): void {
  const a=x.allocator,hit=x.hitIds[0]!;
  equal(x.hitPool.count,3,'one actual type4 allocation before target prefix');
  equal(x.groups[49]!.head,hit,'actual group49 insertion precedes target prefix');
  equal(a.readPointer(hit,0x20),x.child,'HIT keeps same child');
  equal(a.readU32(hit,0xc),0x8008a65c,'HIT future callback remains stored');
  equal(a.readU8(x.child,0x86),1,'completed HIT success flag');
  equal(a.readU8(x.child,0x18),1,'no invented initializer completion');
  equal(x.drawList.head,x.child,'earlier actual draw insertion remains');
}
function syntheticTarget(x: SourceProjectileTargetTestFixture): object {
  const target=Object.create(null) as object;
  x.projectiles.getAdmissionBinding(x.actor).pointerc8=target;
  // A deliberately stale child pointer cannot replace the saved owner's c8.
  x.allocator.writePointer(x.child,0xc8,null);
  return target;
}
function putVector(x: SourceProjectileTargetTestFixture, offsets: readonly number[], values: readonly number[]): void {
  offsets.forEach((offset,i)=>x.allocator.writeF32(x.child,offset,values[i]!));
}
/** Late explicit bytes isolate arithmetic without counterfeiting the genuine
 * post-HIT transform. That transform has already executed when stack is read. */
function arithmetic(x: SourceProjectileTargetTestFixture, aim: readonly number[], position: readonly number[], boundary=POSITIVE): void {
  let supplied=false;
  observe(()=>dispatch(x,boundary),(owner,key)=>{
    if(!supplied && owner===x.rootSources && key==='targetStack') {
      supplied=true;putVector(x,AIM,aim);putVector(x,POS,position);
    }
  });
  check(supplied,'synthetic byte operands supplied only at reached target branch');
}
function byteNames(prefix: string, base: number, width: number): string[] {
  return Array.from({length:width},(_,i)=>`${prefix}${(base+i).toString(16)}`);
}

export function runProjectileTargetPrefixSelfTests(make: () => SourceProjectileTargetTestFixture): void {
  {
    const x=make();
    equal(x.sourceActor.heading,0,'factory keeps inherited synthetic heading');
    equal(x.projectiles.getAdmissionBinding(x.actor).pointerc8,null,'factory never invents nonnull target');
    equal(x.rootSources.targetStack,x.targetStack,'actual explicit stack identity retained');
    equal(x.rootSources.processor,x.targetProcessor,'same actual graph processor is supplied');
    equal(x.targetProcessor.gqr0,0,'explicit existing GQR0 profile');
    stackBits(x,SENTINELS.map(bits),'explicit fresh stack sentinels');
    const aim=words(x,AIM),position=POS.map(offset=>x.allocator.readF32(x.child,offset));
    const capturedAim=AIM.map(offset=>x.allocator.readF32(x.child,offset));
    const keepMatrices=retained(...matrixRecords(x)),direction=words(x,DIRECTION),target=syntheticTarget(x);
    x.sourceActor.heading=0x8123; // Nonzero yaw is converted, never passed to null-path RotRad.
    Object.assign(x.sourceActor.aimOrigin518,{x:999,y:-888,z:777});
    Object.defineProperty(target,'pos',{get(){throw Error('opaque target must never be dereferenced');}});
    let opaqueReads=0,aimReads=0,initializationReads=0,helper=false;
    observe(()=>dispatch(x),(owner,key)=>{
      if(owner===x.rootSources && key==='targetStack') helper=true;
      if(owner===target) opaqueReads++;
      if(helper && owner===x.sourceActor.aimOrigin518) aimReads++;
      if(owner===x.rootSources && key==='initializationStack') initializationReads++;
    });
    equal(opaqueReads,0,'actual nonnull pointer is a branch test, not target position');
    equal(aimReads,0,'later actor aim is not substituted for child144 captured during actual spawn');
    equal(initializationReads,0,'nonnull target skips null-path rotation stack entirely');
    stackBits(x,capturedAim.map((v,i)=>bits(Math.fround(v-position[i]!))),'actual captured child aim minus refreshed child position');
    sameWords(x,AIM,aim,'source aim bytes remain unchanged');sameWords(x,DIRECTION,direction,'no later direction store');
    completedHit(x);keepMatrices();closed(x);
  }
  {
    const x=make(),target=syntheticTarget(x),matrix=x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[11]!);
    const aim=AIM.map(offset=>x.allocator.readF32(x.child,offset));
    const fresh=[1165,1890,3275],newMatrix=[3,-.5,2,1000,-2,4,.25,2000,5,2,-3,3000];
    const events:string[]=[];let afterHit=false,helper=false,mutated=false;
    observe(()=>dispatch(x),(owner,key)=>{
      if(!afterHit && owner===x.hitBinding.pointer3fc && key===String(0xa25)) {
        afterHit=true;newMatrix.forEach((v,i)=>{matrix[i]=v;});
        x.allocator.writePointer(x.child,0x90,null);x.allocator.writePointer(x.child,0x8c,null);
      }
      if(owner===x.rootSources && key==='targetStack') helper=true;
      if(!helper) return;
      if(owner===x.objectBytes) {
        const offset=Number(key);
        if(offset>=0x144 && offset<0x150) events.push(`a${offset.toString(16)}`);
        if(offset>=0x20 && offset<0x2c) events.push(`p${offset.toString(16)}`);
        if(offset>=0x90 && offset<0x94) throw Error('saved owner90 must not be reloaded');
      }
      if(owner===x.targetStack.displacement) events.push(`s${String(key)}`);
      if(owner===target) throw Error('nonnull target is opaque');
    },(owner,key)=>{
      // Actual c8 descriptor is captured before the later explicit host mutation.
      if(afterHit && !mutated && owner===x.projectiles.getAdmissionBinding(x.actor) && key==='pointerc8') {
        mutated=true;x.projectiles.getAdmissionBinding(x.actor).pointerc8=null;
      }
    });
    check(afterHit && mutated,'late matrix and captured c8 mutations both reached');
    sameWords(x,POS,fresh.map(bits),'fresh saved-owner joint11 transform after HIT');
    stackBits(x,aim.map((v,i)=>bits(Math.fround(v-fresh[i]!))),'subtraction consumes refreshed position');
    equal(events.join(','),[
      ...byteNames('a',0x144,8),...byteNames('p',0x20,8),'sx','sy',
      ...byteNames('a',0x14c,4),...byteNames('p',0x28,4),'sz','sx','sz',
    ].join(','),'genuine XY aim/position, paired XY preflight/store, Z aim/position/store, fresh scratch X/Z order');
    completedHit(x);closed(x);
  }

  // One source psq_st XY preflights BOTH ordinary host output fields. A fault
  // in either field retains both sentinels, not a half-committed source pair.
  for(const axis of ['x','y'] as const) {
    const x=make();syntheticTarget(x);let zReads=0;
    Object.defineProperty(x.targetStack.displacement,axis,{writable:false});
    observe(()=>dispatch(x,'non-writable'),(owner,key)=>{
      if(owner===x.objectBytes && Number(key)>=0x14c && Number(key)<0x150) zReads++;
    });
    stackBits(x,SENTINELS.map(bits),'failed XY pair preserves both lanes and Z');
    equal(zReads,0,'XY width fault precedes Z input loads');completedHit(x);closed(x);
  }
  for(const site of ['aim','position','store'] as const) {
    const x=make();syntheticTarget(x);const output=x.targetStack.displacement;let late=false;
    observe(()=>dispatch(x,site==='store'?'non-writable':'own data'),(owner,key)=>{
      if(!late && owner===x.rootSources && key==='targetStack') {
        late=true;putVector(x,AIM,[9,12,15]);putVector(x,POS,[1,2,3]);
        if(site==='store') Object.defineProperty(output,'z',{writable:false});
        else delete x.objectBytes[site==='aim'?0x14c:0x28];
      }
    });
    check(late,'Z fault introduced only after actual position refresh');
    stackBits(x,[8,10,59].map(bits),`${site} Z fault keeps the completed XY pair`);closed(x);
  }
  for(const [aim,position,expected,boundary,label] of [
    [[-0,0,-0],[0,-0,0],[0x80000000,0,0x80000000],ZERO,'signed zeros'],
    [[3,-7,0],[3,-7,0],[0,0,0],ZERO,'exact cancellation'],
    [[16777216,1,0],[-1,1,0],[0x4b800000,0,0],POSITIVE,'halfway rounds to even lower'],
    [[16777218,1,0],[-1,1,0],[0x4b800002,0,0],POSITIVE,'halfway rounds to even upper'],
    [[1+2**-23,1-2**-24,0],[1,1,0],[0x34000000,0xb3800000,0],POSITIVE,'adjacent f32 cancellation'],
    [[2**-149,8,0],[0,0,0],[1,0x41000000,0],ZERO,'minimum subnormal displacement'],
    [[2**-75,0,2**-75],[0,0,0],[0x1a000000,0,0x1a000000],ZERO,'both squares separately underflow'],
    [[2**-74,0,0],[0,0,0],[0x1a800000,0,0],POSITIVE,'positive subnormal square'],
  ] as const) {
    const x=make();syntheticTarget(x);const keep=retained(...matrixRecords(x)),direction=words(x,DIRECTION);
    arithmetic(x,aim,position,boundary);stackBits(x,expected,label);
    sameWords(x,DIRECTION,direction,`${label} stops before direction stores`);keep();closed(x);
  }
  // Independent branch witness: exact combined squares are one minsubnormal,
  // but each actual fmuls rounds its half-minsubnormal to +0 before fadds.
  equal(bits(Math.fround((2**-75)*(2**-75)+(2**-75)*(2**-75))),1,
    'a fused/late-rounded two-square expression would take the wrong positive branch');
  {
    const x=make();syntheticTarget(x);let reads=0,changed=false;
    observe(()=>arithmetic(x,[3,4,5],[0,0,0],ZERO),(owner,key)=>{
      if(owner===x.targetStack.displacement && key==='x' && ++reads===2) {
        // Both fresh loads are AFTER helper stores, not retained helper locals.
        x.targetStack.displacement.x=0;x.targetStack.displacement.z=0;
        x.targetStack.displacement.y=NaN;changed=true;
      }
    });
    check(changed,'fresh scratch X descriptor reached after full helper');
    equal(x.targetStack.displacement.x,0,'no replacement of scratchX at zero-constant boundary');
    equal(x.targetStack.displacement.z,0,'fresh scratchZ determines zero horizontal square');
    check(Number.isNaN(x.targetStack.displacement.y),'root never reads irrelevant scratchY');closed(x);
  }
  {
    const x=make();syntheticTarget(x);let xReads=0;
    observe(()=>arithmetic(x,[0,0,2],[0,0,0],ZERO),()=>{},(owner,key)=>{
      if(owner===x.targetStack.displacement && key==='x' && ++xReads===2) {
        x.targetStack.displacement.x=17;x.targetStack.displacement.z=0;
      }
    });
    equal(x.targetStack.displacement.x,17,'captured scratchX is not reloaded or replaced');
    equal(x.targetStack.displacement.z,0,'scratchZ is loaded after captured scratchX');closed(x);
  }
  for(const axis of ['x','z'] as const) {
    const x=make();syntheticTarget(x);let visits=0,changed=false;
    observe(()=>dispatch(x,'finite source float32'),(owner,key)=>{
      if(owner===x.targetStack.displacement && key===axis && ++visits===2) {
        x.targetStack.displacement[axis]=NaN;changed=true;
      }
    });
    check(changed,`fresh scratch ${axis} is individually validated`);closed(x);
  }
  for(const site of ['x','y','z'] as const) {
    const x=make();syntheticTarget(x);const aim=[8,10,12],position=[0,0,0],index=AXES.indexOf(site);
    aim[index]=MAX;position[index]=-MAX;
    arithmetic(x,aim,position,'overflow float32');
    stackBits(x,(site==='z'?[8,10,59]:SENTINELS).map(bits),`${site} subtraction overflow source prefix`);closed(x);
  }
  for(const [aim,boundary,label] of [
    [[MAX,7,1],'finite source float32','X square overflow'],
    [[1,7,MAX],'finite source float32','Z square overflow'],
    [[.75*2**64,7,.75*2**64],'overflow float32','sum of finite rounded squares overflows'],
  ] as const) {
    const x=make();syntheticTarget(x);const direction=words(x,DIRECTION),keep=retained(...matrixRecords(x));
    arithmetic(x,aim,[0,0,0],boundary);stackBits(x,aim.map(bits),`${label} retains all helper stores`);
    sameWords(x,DIRECTION,direction,`${label} prevents later operations`);keep();closed(x);
  }

  for(const kind of ['missing','accessor','undefined','invalid','field-accessor'] as const) {
    const x=make();syntheticTarget(x);let getterRan=false,stackReads=0,byteReads=0;
    if(kind==='missing') delete x.rootSources.processor;
    else if(kind==='accessor') Object.defineProperty(x.rootSources,'processor',{get(){getterRan=true;return x.targetProcessor;}});
    else if(kind==='undefined') Reflect.set(x.rootSources,'processor',undefined);
    else if(kind==='invalid') x.targetProcessor.gqr0=1;
    else Object.defineProperty(x.targetProcessor,'gqr0',{get(){getterRan=true;return 0;}});
    const keep=retained(x.targetStack.displacement);
    observe(()=>dispatch(x,kind==='invalid'?'GQR0 must explicitly select float':kind==='field-accessor'?'own data':PROFILE),(owner,key)=>{
      if(owner===x.targetStack.displacement) stackReads++;
      if(owner===x.objectBytes && Number(key)>=0x144 && Number(key)<0x150) byteReads++;
    });
    check(!getterRan && stackReads===0 && byteReads===0,'unavailable processor refuses before operand/output access without getters');
    completedHit(x);keep();closed(x);
  }
  for(const value of [undefined,-1,.5,NaN,Infinity,0x100000000]) {
    const x=make();syntheticTarget(x);const keep=retained(x.targetStack.displacement);let stackReads=0;
    Reflect.set(x.targetProcessor,'gqr0',value);
    observe(()=>dispatch(x,'unsigned source integer'),(owner,key)=>{
      if(owner===x.rootSources && key==='targetStack') stackReads++;
    });
    equal(stackReads,0,'invalid explicit GQR0 refuses before target stack admission');keep();closed(x);
  }
  {
    const x=make();syntheticTarget(x);let changed=false,targetReads=0;
    observe(()=>dispatch(x,'fresh heading72'),(owner,key)=>{
      if(!changed && owner===x.hitBinding.pointer3fc && key===String(0xa25)) {changed=true;x.sourceActor.heading=NaN;}
      if(owner===x.rootSources && (key==='processor'||key==='targetStack')) targetReads++;
    });
    check(changed && targetReads===0,'fresh source heading conversion gate precedes all target admission');closed(x);
  }
  for(const site of ['root','displacement'] as const) for(const kind of ['missing','accessor','inherited'] as const) {
    const x=make();syntheticTarget(x);let getterRan=false;const keep=retained(x.targetStack.displacement);
    const owner=site==='root'?x.rootSources:x.targetStack,key=site==='root'?'targetStack':'displacement';
    if(kind==='missing') Reflect.deleteProperty(owner,key);
    else if(kind==='accessor') Object.defineProperty(owner,key,{get(){getterRan=true;return site==='root'?x.targetStack:{x:1,y:2,z:3};}});
    else {
      const inherited=site==='root'?x.targetStack:{x:1,y:2,z:3};
      Reflect.deleteProperty(owner,key);Object.setPrototypeOf(owner,{[key]:inherited});
    }
    dispatch(x,site==='root'?NO_STACK:'own data');check(!getterRan,'stack accessor is rejected without invocation');keep();
    // The fixture's original stack may intentionally lack displacement here.
    if(site==='root') closed(x);
    else check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'malformed nested stack still closes actor');
  }
  for(const site of ['root','displacement'] as const) for(const value of [null,undefined,0,()=>0,[],new Float32Array(3),Promise.resolve(0)]) {
    const x=make();syntheticTarget(x);const keep=retained(x.targetStack.displacement);
    if(site==='root') Reflect.set(x.rootSources,'targetStack',value);
    else Reflect.set(x.targetStack,'displacement',value);
    dispatch(x,site==='root' && value===undefined?NO_STACK:'ordinary own-data record required');keep();
    check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'nonordinary stack refuses with shared closure');
  }
  for(const axis of AXES) {
    const x=make();syntheticTarget(x);let getterRan=false;
    Object.defineProperty(x.targetStack.displacement,axis,{get(){getterRan=true;return 0;}});
    dispatch(x,'own data');check(!getterRan,`${axis} output accessor is never invoked`);closed(x);
  }

  // Alias checks concern real graph ownership, never guessed pointer numbers.
  for(const owner of ['actor','child','nextChild','aim','position','draw','admission','world','stage','status'] as const) {
    const x=make();syntheticTarget(x);
    const source=owner==='actor'?x.sourceActor:owner==='child'?x.objectBytes:owner==='nextChild'?x.nextObjectBytes:
      owner==='aim'?x.sourceActor.aimOrigin518:owner==='position'?x.sourceActor.pos:owner==='draw'?x.drawList:
      owner==='admission'?x.projectiles.getAdmissionBinding(x.actor):owner==='world'?x.world.getActorBinding(x.actor):
      owner==='stage'?x.stageBounds.getActorBinding(x.actor):x.stageBounds.getStatusBinding(x.actor);
    const before=retained(source,x.targetStack.displacement);
    // Position is legitimately refreshed before stack admission, so snapshot
    // source owners only at the reached targetStack load, after those writes.
    let keep=before;
    observe(()=>{
      x.rootSources.targetStack={displacement:source as TargetStack['displacement']};dispatch(x,'target stack aliases source owner');
    },(record,key)=>{if(record===x.rootSources && key==='targetStack') keep=retained(source,x.targetStack.displacement);});
    keep();closed(x);
  }
  for(const current of [true,false]) for(const slot of ['joint','copy114','copy1aa4','scratch'] as const) {
    const x=make();syntheticTarget(x);const storage=x.world.getStorage(current?x.actor:x.target);
    const id=slot==='joint'?storage.matrices8d4[0]!:storage[slot],matrix=x.matrices.getMatrix(id),keep=retained(matrix);
    x.rootSources.targetStack={displacement:matrix as unknown as TargetStack['displacement']};
    dispatch(x,'ordinary own-data record required');keep();closed(x);
  }
  {
    const x=make();syntheticTarget(x);x.rootSources.targetStack=x.objectBytes as unknown as TargetStack;
    Object.defineProperty(x.objectBytes,'displacement',{value:x.targetStack.displacement,configurable:true});
    dispatch(x,'target stack aliases source owner');closed(x);
  }
  {
    const x=make(),target=x.targetStack.displacement,admission=x.projectiles.getAdmissionBinding(x.actor);
    admission.pointerc8=target;let freshHeading=false,captured=false,targetReads=0;
    const keep=retained(target);
    observe(()=>dispatch(x,'target stack aliases source owner'),(owner,key)=>{
      if(owner===x.sourceActor && key==='heading' && x.objectBytes[0x86]===1) freshHeading=true;
      if(owner===target) targetReads++;
    },(owner,key)=>{
      if(!captured && freshHeading && owner===admission && key==='pointerc8') {
        captured=true;admission.pointerc8=null;
      }
    });
    check(captured && targetReads===0,'captured opaque target cannot alias stack even after live c8 changes, without target property reads');
    keep();closed(x);
  }
  for(const reuse of ['wrapper','displacement'] as const) {
    const first=make();syntheticTarget(first);dispatch(first);
    const second=make();syntheticTarget(second);const keep=retained(first.targetStack,first.targetStack.displacement);
    second.rootSources.targetStack=reuse==='wrapper'?first.targetStack:{displacement:first.targetStack.displacement};
    dispatch(second,'target stack already claimed');keep();closed(first);closed(second);
  }
  {
    const x=make();syntheticTarget(x);
    const output=Object.assign(Object.create(null) as TargetStack['displacement'],{x:71,y:-23,z:59});
    const stack=Object.assign(Object.create(null) as TargetStack,{displacement:output});
    x.rootSources.targetStack=stack;dispatch(x);check(AXES.some(axis=>output[axis]!==x.targetStack.displacement[axis]),
      'explicit null-prototype own-data records are ordinary source stack storage');closed(x);
  }

  for(const mode of ['null','zeroHit'] as const) for(const kind of ['missing','accessor','malformed'] as const) {
    const x=make(),direction=words(x,DIRECTION),keep=retained(x.targetStack.displacement);let reads=0,getterRan=false;
    if(kind==='missing') {delete x.rootSources.targetStack;delete x.rootSources.processor;}
    else if(kind==='accessor') {
      Object.defineProperty(x.rootSources,'targetStack',{get(){getterRan=true;throw Error('unreached stack');}});
      Object.defineProperty(x.rootSources,'processor',{get(){getterRan=true;throw Error('unreached processor');}});
    } else {Reflect.set(x.rootSources,'targetStack',null);Reflect.set(x.rootSources,'processor',null);}
    if(mode==='zeroHit') {syntheticTarget(x);x.hitPool.head=null;}
    observe(()=>mode==='null'?dispatch(x,NORMALIZE):x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.rootSources && (key==='targetStack'||key==='processor')) reads++;
    });
    check(!getterRan && reads===0,`${mode} skips unavailable target stack and processor`);keep();
    if(mode==='null') {sameWords(x,DIRECTION,[0,0,0x3f800000],'old actual null-target flight behavior');closed(x);}
    else {
      equal(x.allocator.readU8(x.child,0x18),2,'actual zero HIT returns after state2 store');
      equal(x.hitPool.count,4,'exhaustion never pops a HIT');sameWords(x,DIRECTION,direction,'zero HIT skips later direction');
      check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'actual zero return does not poison actor');x.projectiles.assertActorComplete(x.actor);
    }
  }
  for(const site of ['aimXY','pairX','pairY','aimZ','storeZ','scratchX','scratchZ'] as const) {
    const x=make();syntheticTarget(x);let injected=false,xVisits=0,zVisits=0;
    observe(()=>dispatch(x,'reentry'),(owner,key)=>{
      if(owner===x.targetStack.displacement && key==='x') xVisits++;
      if(owner===x.targetStack.displacement && key==='z') zVisits++;
      const reached=site==='aimXY'?owner===x.objectBytes && key===String(0x144):
        site==='aimZ'?owner===x.objectBytes && key===String(0x14c):
        site==='pairX'?owner===x.targetStack.displacement && key==='x' && xVisits===1:
        site==='pairY'?owner===x.targetStack.displacement && key==='y':
        site==='storeZ'?owner===x.targetStack.displacement && key==='z' && zVisits===1:
        site==='scratchX'?owner===x.targetStack.displacement && key==='x' && xVisits===2:
        owner===x.targetStack.displacement && key==='z' && zVisits===2;
      if(!injected && reached) {injected=true;try{x.root.dispatchStoredRoot(x.child);}catch{/* Explicit caught host reentry. */}}
    });
    check(injected,`caught root reentry reached ${site}`);
    if(site==='aimXY'||site==='pairX'||site==='pairY') stackBits(x,SENTINELS.map(bits),'reentry before completed XY pair preserves both lanes');
    if(site==='aimZ'||site==='storeZ') equal(x.targetStack.displacement.z,59,'Z-stage reentry preserves old Z');
    closed(x);
  }
  console.log('[projectile-target-prefix] PASS: genuine HIT/refresh and captured child aim, opaque synthetic nonnull ownerc8, actual paired subtraction order and fault prefixes, signed-zero/f32 arithmetic, fresh scratch X/Z, separately rounded squares/underflow and overflow refusal, lazy explicit GQR0/stack, ownership/reentry closure and old null/zero-HIT behavior; no estimator, new constant, retail hydration, flight or original-execution claim');
}
