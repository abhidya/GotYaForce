import {hasIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {sourceProjectileHeadingRadians, sourceProjectileInitialPitch} from './projectile-heading.js';
import type {SourceProjectileHitTestFixture} from './projectile-hit-registration.selftest.js';
import type {SourceProjectileInitializationStack} from './projectile-root-lifecycle.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorJointMatrixRuntime} from './actor-joint-matrix.js';

/** The genuine attached graph supplies completed spawn/HIT owners and explicit
 * sentinel stack matrices. Its inherited synthetic heading/target are observed,
 * not overwritten by this factory contract or claimed as retail hydration.
 * Mutations below deliberately isolate source branches and host failure order.
 * No original execution, general trigonometry, normalization or flight is proved. */
export interface SourceProjectileFlightTestFixture extends SourceProjectileHitTestFixture {
  world: SourceActorWorldMatrixRuntime;
  matrices: SourceActorJointMatrixRuntime;
  initializationStack: SourceProjectileInitializationStack;
  /** Existing second genuine world actor, with separately owned matrix slots. */
  target: symbol;
}
const NORMALIZE = 'actual8020bab8 Normalize';
const TARGET = 'actual8020ba78 target displacement';
const ZERO = 0, ONE = 0x3f800000, NEGATIVE_ZERO = 0x80000000;
// Independent IEEE expectations for RotTrig(X,-0), RotTrig(Y,+0), then Y*X.
const X_BITS = [ONE,ZERO,ZERO,ZERO,ZERO,ONE,ZERO,ZERO,ZERO,NEGATIVE_ZERO,ONE,ZERO];
const Y_BITS = [ONE,ZERO,ZERO,ZERO,ZERO,ONE,ZERO,ZERO,NEGATIVE_ZERO,ZERO,ONE,ZERO];
const PRODUCT_BITS = [ONE,ZERO,ZERO,ZERO,ZERO,ONE,ZERO,ZERO,ZERO,ZERO,ONE,ZERO];
const POSITION = [0x20,0x24,0x28] as const, DIRECTION = [0x38,0x3c,0x40] as const;
const REFRESH_MATRIX = [3,-.5,2,1000,-2,4,.25,2000,5,2,-3,3000];
const REFRESH_POSITION = [1165,1890,3275]; // Exact integer arithmetic: each row consumes (55,0,0,1).
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[projectile-flight-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  if (!Object.is(actual,expected)) throw Error(`[projectile-flight-test] ${why}: values differ`);
}
function rejects(run: () => unknown, fragment: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(fragment),`expected ${fragment}, got ${message || 'success'}`);
}
function bits(value: number): number {
  const data = new DataView(new ArrayBuffer(4)); data.setFloat32(0,value,false); return data.getUint32(0,false);
}
function matrixBits(matrix: readonly number[], expected: readonly number[], why: string): void {
  equal(matrix.length,expected.length,`${why} extent`);
  expected.forEach((value,index) => equal(bits(matrix[index]!),value,`${why} lane${index}`));
}
/** Descriptor interception observes genuine own-data accesses, never replaces a
 * runtime callee with a successful callback. after sees the captured descriptor. */
function observe(run: () => void, before: (owner: object,key: PropertyKey) => void,
  after?: (owner: object,key: PropertyKey) => void): void {
  const original = Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor = ((owner: object,key: PropertyKey) => {
    before(owner,key); const result = original(owner,key); after?.(owner,key); return result;
  }) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor = original;}
}
function retained(...records: object[]): () => void {
  const snapshots = records.map(record => Object.getOwnPropertyDescriptors(record));
  return () => records.forEach((record,index) => {
    const saved = snapshots[index]!, after = Object.getOwnPropertyDescriptors(record);
    equal(Reflect.ownKeys(after).length,Reflect.ownKeys(saved).length,'failed replay keeps property count');
    for (const key of Object.keys(saved)) {
      const a = after[key], b = saved[key]!;
      check(a !== undefined && Object.is(a.value,b.value) && a.get === b.get && a.set === b.set &&
        a.writable === b.writable && a.configurable === b.configurable && a.enumerable === b.enumerable,
      `failed replay retains descriptor ${key}`);
    }
  });
}
function matrices(x: SourceProjectileFlightTestFixture): [number[],number[]] {
  return [x.matrices.getMatrix(x.initializationStack.rotationX),x.matrices.getMatrix(x.initializationStack.rotationY)];
}
function joint(x: SourceProjectileFlightTestFixture): number[] {
  return x.matrices.getMatrix(x.world.getStorage(x.actor).matrices8d4[11]!);
}
function words(x: SourceProjectileFlightTestFixture, offsets: readonly number[]): number[] {
  return offsets.map(offset => x.allocator.readU32(x.child,offset));
}
function sameWords(x: SourceProjectileFlightTestFixture, offsets: readonly number[], expected: readonly number[], why: string): void {
  offsets.forEach((offset,i) => equal(x.allocator.readU32(x.child,offset),expected[i],`${why} +${offset.toString(16)}`));
}
function closed(x: SourceProjectileFlightTestFixture): void {
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'failed flight prefix closes shared actual actor');
  const keep = retained(x.objectBytes,x.nextObjectBytes,x.hitPool,x.descriptorPool,x.drawList,...x.hitBytes,...matrices(x));
  rejects(() => x.root.dispatchStoredRoot(x.child),'incomplete');
  rejects(() => x.hits.registerHit(x.child,1),'incomplete');
  rejects(() => x.projectiles.spawn(x.actor,1),'incomplete');
  rejects(() => x.allocator.writeU8(x.nextChild,0,1),'incomplete');
  keep();
}
function dispatch(x: SourceProjectileFlightTestFixture, boundary = NORMALIZE): void {
  rejects(() => x.root.dispatchStoredRoot(x.child),boundary);
}
function completedHit(x: SourceProjectileFlightTestFixture): void {
  const a = x.allocator, hit = x.hitIds[0]!;
  equal(x.hitPool.count,3,'one genuine type4 allocation precedes the flight prefix');
  equal(x.groups[49]!.head,hit,'HIT occupies real group49');
  equal(a.readPointer(hit,0x20),x.child,'HIT retains same child identity');
  equal(a.readU32(hit,0xc),0x8008a65c,'HIT stores actual future callback');
  equal(a.readU8(x.child,0x86),1,'completed HIT success flag');
  equal(a.readU8(x.child,0x1d8),0,'completed HIT clears invalidation');
  equal(a.readU8(x.child,0x18),1,'no invented completion beyond the direction prefix');
}
function syntheticNullHeading(x: SourceProjectileFlightTestFixture, heading: number): void {
  // Explicit synthetic branch operands, never a change to the factory defaults.
  x.sourceActor.heading = heading; x.projectiles.getAdmissionBinding(x.actor).pointerc8 = null;
}

/** Integer-only independently rounded rational n*13176795/2^37. No floating
 * multiplication, fround, source conversion helper or DataView float decode is
 * used to construct the expected binary32 result. */
function referenceHeadingBits(raw: number): number {
  const signed = raw < 32768 ? raw : raw-65536;
  if (signed === 0) return 0;
  const negative = signed < 0, numerator = BigInt(negative ? -signed : signed)*13176795n;
  const width = numerator.toString(2).length;
  let exponent = width-1-37, significand: bigint;
  if (width <= 24) significand = numerator << BigInt(24-width);
  else {
    const shift = BigInt(width-24), remainder = numerator & ((1n << shift)-1n), halfway = 1n << (shift-1n);
    significand = numerator >> shift;
    if (remainder > halfway || (remainder === halfway && (significand & 1n) !== 0n)) significand++;
    if (significand === 1n << 24n) {significand >>= 1n; exponent++;}
  }
  return ((negative ? NEGATIVE_ZERO : 0) | ((exponent+127)<<23) | Number(significand-(1n<<23n))) >>> 0;
}

export function runProjectileFlightPrefixSelfTests(make: () => SourceProjectileFlightTestFixture): void {
  for (let heading = 0; heading < 65536; heading++)
    equal(bits(sourceProjectileHeadingRadians(heading)),referenceHeadingBits(heading),`all signed16 yaw bits ${heading}`);
  equal(bits(sourceProjectileHeadingRadians(1)),0x38c90fdb,'named804379ac literal is selected exactly');
  equal(bits(sourceProjectileHeadingRadians(0x8000)),0xc0490fdb,'signed negative half-turn, not unsigned yaw');
  equal(bits(sourceProjectileHeadingRadians(0xffff)),0xb8c90fdb,'signed negative one');
  equal(bits(sourceProjectileInitialPitch()),NEGATIVE_ZERO,'actual fneg of named positive-zero pitch');
  for (const value of [-1,65536,.5,NaN,Infinity,-Infinity])
    rejects(() => sourceProjectileHeadingRadians(value),'unsigned source heading');

  {
    const x = make(), [rotationX,rotationY] = matrices(x), matrix = joint(x);
    // Observed state of this inherited synthetic graph. No default mutation.
    equal(x.sourceActor.heading,0,'unmodified graph currently supplies heading0');
    equal(x.projectiles.getAdmissionBinding(x.actor).pointerc8,null,'unmodified graph currently supplies actual null target');
    check(rotationX.every(value => value === 37) && rotationY.every(value => value === -19),'explicit fresh stack sentinels');
    equal(x.root.getObject(x.child),x.objectBytes,'root retains same actual child byte owner');
    equal(x.world.getActualActor(x.actor),x.sourceActor,'same actual saved world owner');
    equal(x.world.getMatricesRuntime(),x.matrices,'same actual matrix runtime');
    equal(x.world.getWorldMatrix(x.actor,11),matrix,'same actual joint11 record');
    const keepJoint = retained(matrix), position = words(x,POSITION), events: string[] = [];
    let rotationsChecked = false;
    observe(() => dispatch(x),(owner,key) => {
      if (owner === rotationY && key === 'length') {
        matrixBits(rotationX,X_BITS,'real X negative-zero rotation before concat');
        matrixBits(rotationY,Y_BITS,'real Y positive-zero rotation before concat'); rotationsChecked = true;
      }
      if (owner === rotationX || owner === rotationY) events.push(`${owner === rotationX ? 'x' : 'y'}${String(key)}`);
    });
    check(rotationsChecked,'real concat snapshots its two actual rotation inputs');
    const xStores = [0,1,2,3,4,7,8,11,9,10,5,6], yStores = [6,7,0,1,10,11,4,5,2,3,8,9];
    // Independent source RotTrig store schedules followed by Concat's two
    // snapshots, paired store schedule, then interleaved direction lane reads.
    equal(events.join(','),[
      ...xStores.map(i=>`x${i}`),...yStores.map(i=>`y${i}`),'ylength',
      ...Array.from({length:12},(_,i)=>`y${i}`),'xlength',...Array.from({length:12},(_,i)=>`x${i}`),
      ...[0,1,4,5,2,3,6,7,8,9,10,11].map(i=>`x${i}`),'x2','x6','x10',
    ].join(','),'source X then Y then Concat(Y,X,X) then source lane order');
    matrixBits(rotationX,PRODUCT_BITS,'actual in-place Y*X product'); matrixBits(rotationY,Y_BITS,'right operation preserves Y input');
    sameWords(x,DIRECTION,[ZERO,ZERO,ONE],'unnormalized source direction bits');
    sameWords(x,POSITION,position,'same live joint gives same refreshed child position');
    equal(x.allocator.readU32(x.child,0x100),0x80047aa4,'earlier genuine draw callback retained');
    equal(x.drawList.head,x.child,'earlier genuine draw insertion retained');
    completedHit(x); keepJoint(); closed(x);
  }
  {
    const x = make(), matrix = joint(x), row = x.projectiles.getSpawnRow1(), events: string[] = [];
    REFRESH_MATRIX.forEach((value,i) => {matrix[i] = value;});
    let afterHit = false;
    observe(() => dispatch(x),(owner,key) => {
      if (owner === x.hitBinding.pointer3fc && key === String(0xa25)) afterHit = true;
      if (!afterHit) return;
      if (owner === row && (key === 'joint02' || key === 'offset2c')) events.push(String(key));
      if (owner === matrix && key !== 'length') events.push(`m${String(key)}`);
      if (owner === row.local04) events.push(`v${String(key)}`);
      if (owner === x.objectBytes && Number(key)>=0x20 && Number(key)<0x2c) events.push(`c${Number(key).toString(16)}`);
      if (owner === x.sourceActor && key === 'heading') events.push('fresh72');
      if (owner === x.projectiles.getAdmissionBinding(x.actor) && key === 'pointerc8') events.push('livec8');
    });
    sameWords(x,POSITION,REFRESH_POSITION.map(bits),'fresh source joint11 after actual spawn');
    equal(events.join(','),[
      'joint02','vx','vy','m0','m1','vz','m2','m3','m4','m5','m6','m7','c20','c21','c22','c23',
      'm8','m9','m10','m11','c24','c25','c26','c27','c28','c29','c2a','c2b','offset2c','fresh72','livec8',
    ].join(','),'source row/joint/MultVec byte-store/fresh-heading/live-target order');
    completedHit(x); closed(x);
  }
  {
    const x = make(), matrix = joint(x), initialHeading = 0x8123;
    syntheticNullHeading(x,initialHeading); let changed = false, later90 = false, later8c = false;
    observe(() => dispatch(x),(owner,key) => {
      if (!changed && owner === x.hitBinding.pointer3fc && key === String(0xa25)) {
        x.allocator.writePointer(x.child,0x90,null); x.allocator.writePointer(x.child,0x8c,null);
        x.sourceActor.heading = 0; REFRESH_MATRIX.forEach((value,i) => {matrix[i] = value;}); changed = true;
      } else if (changed && owner === x.objectBytes) {
        if (Number(key)>=0x90 && Number(key)<0x94) later90 = true;
        if (Number(key)>=0x8c && Number(key)<0x90) later8c = true;
      }
    });
    check(changed && !later90 && !later8c,'initializer retains its saved owner across real HIT, without child90/8c reload');
    equal(x.allocator.readU16(x.child,0x72),initialHeading,'child72 retains earlier copy, not fresh owner heading');
    equal(x.allocator.readPointer(x.hitIds[0]!,0x24),x.actor,'HIT itself used the prior genuine parent90');
    sameWords(x,POSITION,REFRESH_POSITION.map(bits),'post-HIT live joint mutation belongs to the saved actual owner');
    sameWords(x,DIRECTION,[ZERO,ZERO,ONE],'fresh owner heading0, not previously stored child72'); closed(x);
  }
  for (const heading of [1,0x7fff,0x8000,0xffff]) {
    const x = make(), [rotationX,rotationY] = matrices(x), oldDirection = words(x,DIRECTION);
    syntheticNullHeading(x,0); let changed = false;
    observe(() => dispatch(x,'nonzero radians'),(owner,key) => {
      if (!changed && owner === x.hitBinding.pointer3fc && key === String(0xa25)) {x.sourceActor.heading=heading;changed=true;}
    });
    check(changed,'synthetic fresh nonzero heading supplied only after prior child72 copy');
    equal(x.allocator.readU16(x.child,0x72),0,'earlier child72 cannot replace fresh owner heading');
    matrixBits(rotationX,X_BITS,'X negative-zero rotation survives nonzero Y refusal');
    check(rotationY.every(value => value === -19),'nonzero Y refuses before destination writes');
    sameWords(x,DIRECTION,oldDirection,'unsupported yaw never invents child direction'); completedHit(x); closed(x);
  }
  {
    const x = make(), target = Object.create(null) as object, [rotationX,rotationY] = matrices(x);
    syntheticNullHeading(x,1); x.projectiles.getAdmissionBinding(x.actor).pointerc8 = target;
    x.allocator.writePointer(x.child,0xc8,null); let targetReads = 0, stackReads = 0;
    Object.defineProperty(target,'pos',{get() {throw Error('target must remain opaque at ba78');}});
    const before = words(x,DIRECTION);
    observe(() => dispatch(x,TARGET),(owner,key) => {
      if (owner === target) targetReads++;
      if (owner === x.rootSources && key === 'initializationStack') stackReads++;
    });
    check(targetReads===0 && stackReads===0,'nonnull canonical parentc8 stops before target dereference and stack access');
    check(rotationX.every(v=>v===37) && rotationY.every(v=>v===-19),'target path never substitutes null-path rotations');
    sameWords(x,DIRECTION,before,'nonnull target leaves child direction unchanged'); closed(x);
  }
  for (const capturedNull of [true,false]) {
    const x = make(), admission = x.projectiles.getAdmissionBinding(x.actor), target = Object.create(null) as object;
    syntheticNullHeading(x,0); admission.pointerc8 = capturedNull ? null : target;
    // Opposite stale childc8, and an after-read mutation of canonical parentc8.
    x.allocator.writePointer(x.child,0xc8,capturedNull ? x.actor : null);
    let reachedFreshHeading = false, captured = false;
    observe(() => dispatch(x,capturedNull ? NORMALIZE : TARGET),(owner,key) => {
      if (owner===x.sourceActor && key==='heading' && x.objectBytes[0x86]===1) reachedFreshHeading=true;
    },(owner,key) => {
      if (!captured && reachedFreshHeading && owner===admission && key==='pointerc8') {
        captured=true; admission.pointerc8=capturedNull ? target : null;
      }
    });
    check(captured,'fresh canonical ownerc8 read captured before branch');
    equal(admission.pointerc8,capturedNull ? target : null,'explicit later host mutation remains visible');
    if(capturedNull) sameWords(x,DIRECTION,[ZERO,ZERO,ONE],'captured nullness governs even after canonical pointer changes');
    else check(matrices(x)[0].every(v=>v===37),'captured nonnull target is never reloaded as null');
    closed(x);
  }
  for (const value of [undefined,0,Symbol('not an actual pointer owner')]) {
    const x = make(), admission = x.projectiles.getAdmissionBinding(x.actor), keep = retained(...matrices(x));
    syntheticNullHeading(x,0); Reflect.set(admission,'pointerc8',value);
    dispatch(x,'ownerc8: explicit source pointer owner'); keep(); closed(x);
  }
  for (const value of [undefined,NaN,-1,65536,.5]) {
    const x = make(), keep = retained(...matrices(x)); let changed = false;
    observe(() => dispatch(x,'fresh heading72'),(owner,key) => {
      if (!changed && owner===x.hitBinding.pointer3fc && key===String(0xa25)) {Reflect.set(x.sourceActor,'heading',value); changed=true;}
    });
    check(changed,'fresh invalid heading reaches only the later source load'); keep(); completedHit(x); closed(x);
  }

  // Each source stfs is full-width atomic under the explicit own-data host
  // admission policy. Earlier source axes stay committed; later axes stay old.
  for (const axis of [0,1,2]) for (let byte = 0; byte < 4; byte++) {
    const x=make(), matrix=joint(x), before=words(x,POSITION), direction=words(x,DIRECTION), keep=retained(...matrices(x));
    REFRESH_MATRIX.forEach((value,i)=>{matrix[i]=value;});
    Object.defineProperty(x.objectBytes,String(POSITION[axis]!+byte),{writable:false});
    dispatch(x,'non-writable');
    sameWords(x,POSITION,before.map((old,i)=>i<axis ? bits(REFRESH_POSITION[i]!) : old),'position stfs full-width fault prefix');
    sameWords(x,DIRECTION,direction,'position fault precedes all direction writes');
    completedHit(x); keep(); closed(x);
  }
  for (const lane of [0,6,7,8,10,11]) {
    const x=make(), matrix=joint(x), before=words(x,POSITION), keep=retained(...matrices(x));
    REFRESH_MATRIX.forEach((value,i)=>{matrix[i]=value;}); matrix[lane]=NaN;
    dispatch(x,'finite source float32');
    sameWords(x,POSITION,before.map((old,i)=>lane>=8 && i===0 ? bits(REFRESH_POSITION[0]!) : old),
      'source load fault preserves X only if reached before later row loads');
    keep(); closed(x);
  }
  for (const axis of [0,1,2]) for (let byte=0;byte<4;byte++) {
    const x=make(), before=words(x,DIRECTION), expected=[ZERO,ZERO,ONE];
    Object.defineProperty(x.objectBytes,String(DIRECTION[axis]!+byte),{writable:false});
    dispatch(x,'non-writable');
    sameWords(x,DIRECTION,before.map((old,i)=>i<axis ? expected[i]! : old),'direction stfs full-width fault prefix');
    matrixBits(matrices(x)[0],PRODUCT_BITS,'both rotations and concat precede direction width fault'); closed(x);
  }
  {
    const x=make(), [rotationX]=matrices(x), before=words(x,DIRECTION), events:string[]=[]; let direction=false, visits=0;
    observe(()=>dispatch(x,'finite float32'),(owner,key)=>{
      if(owner===rotationX && key==='2' && ++visits===4) direction=true;
      if(!direction) return;
      if(owner===rotationX && ['2','6','10'].includes(String(key))) events.push(`m${String(key)}`);
      if(owner===x.objectBytes && Number(key)>=0x38 && Number(key)<=0x43) {
        events.push(`c${Number(key).toString(16)}`);
        if(key===String(0x3b)) rotationX[6]=NaN;
      }
    });
    equal(events.join(','),'m2,c38,c39,c3a,c3b,m6','lane2 load/store precedes fresh lane6 load, not eager direction snapshot');
    sameWords(x,DIRECTION,[ZERO,before[1]!,before[2]!],'lane6 fault retains completed X direction only'); closed(x);
  }
  {
    const x=make(), [rotationX]=matrices(x), before=words(x,DIRECTION); let direction=false, visits=0;
    observe(()=>dispatch(x,'finite float32'),(owner,key)=>{
      if(owner===rotationX && key==='2' && ++visits===4) direction=true;
      if(direction && owner===x.objectBytes && key===String(0x3f)) rotationX[10]=NaN;
    });
    sameWords(x,DIRECTION,[ZERO,ZERO,before[2]!],'fresh lane10 fault preserves completed X/Y directions'); closed(x);
  }

  {
    const x=make(), matrix=joint(x), before=words(x,POSITION), direction=words(x,DIRECTION), keep=retained(...matrices(x));
    x.hitPool.head=null; matrix[0]=NaN; delete x.rootSources.initializationStack;
    let reachedAllocation=false, laterHeading=0, laterTarget=0, laterJoint=0, laterStack=0;
    observe(()=>x.root.dispatchStoredRoot(x.child),(owner,key)=>{
      if(owner===x.hitPool && key==='head') {reachedAllocation=true;x.sourceActor.heading=NaN;}
      if(!reachedAllocation) return;
      if(owner===x.sourceActor && key==='heading') laterHeading++;
      if(owner===x.projectiles.getAdmissionBinding(x.actor) && key==='pointerc8') laterTarget++;
      if(owner===matrix) laterJoint++;
      if(owner===x.rootSources && key==='initializationStack') laterStack++;
    });
    check(reachedAllocation && laterHeading===0 && laterTarget===0 && laterJoint===0 && laterStack===0,
      'real zero HIT return skips position refresh, fresh heading/target and unavailable stack');
    equal(x.allocator.readU8(x.child,0x18),2,'actual zero HIT result writes state2 and returns');
    equal(x.hitPool.count,4,'exhaustion without pop preserves explicit count');
    sameWords(x,POSITION,before,'zero HIT leaves earlier spawn position'); sameWords(x,DIRECTION,direction,'zero HIT leaves direction'); keep();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'genuine zero HIT return does not poison the actor');
    x.projectiles.assertActorComplete(x.actor);
  }
  for(const owner of ['current','second'] as const) for(const slot of ['joint','copy114','copy1aa4','scratch'] as const) {
    const x=make(), storage=x.world.getStorage(owner==='current' ? x.actor : x.target);
    const alias=slot==='joint' ? storage.matrices8d4[0]! : storage[slot];
    const prior=retained(x.matrices.getMatrix(alias),...matrices(x)), before=words(x,DIRECTION);
    x.rootSources.initializationStack={rotationX:alias,rotationY:x.initializationStack.rotationY};
    dispatch(x,'initialization stack aliases actor matrix storage'); prior();
    sameWords(x,DIRECTION,before,`${owner} actor ${slot} never substitutes source stack`); closed(x);
  }
  for(const kind of ['same','unknown','child'] as const) {
    const x=make(), keep=retained(...matrices(x));
    x.rootSources.initializationStack=kind==='child' ? x.objectBytes as unknown as SourceProjectileInitializationStack :
      {rotationX:x.initializationStack.rotationX,rotationY:kind==='same' ? x.initializationStack.rotationX : Symbol('unowned temporary')};
    dispatch(x,kind==='same' ? 'distinct owned initialization stack' : kind==='child' ? 'aliases source owner' : 'unknown/non-owned matrix');
    keep(); closed(x);
  }
  {
    const x=make(), keep=retained(...matrices(x)); let getterRan=false;
    Object.defineProperty(x.rootSources,'initializationStack',{get(){getterRan=true;return x.initializationStack;}});
    dispatch(x,'explicit initialization stack unavailable'); check(!getterRan,'stack getter is rejected without invocation'); keep(); closed(x);
  }
  for(const site of ['position','rotation','concat','direction'] as const) {
    const x=make(), [rotationX,rotationY]=matrices(x); let injected=false, visits=0;
    observe(()=>dispatch(x,'reentry'),(owner,key)=>{
      const direction=owner===rotationX && key==='2' && ++visits===4;
      const reached=site==='position' ? owner===x.objectBytes && key===String(0x20) && x.objectBytes[0x86]===1 :
        site==='rotation' ? owner===rotationX && key==='0' : site==='concat' ? owner===rotationY && key==='length' : direction;
      if(!injected && reached) {
        injected=true; try{x.root.dispatchStoredRoot(x.child);}catch{/* Deliberately caught invalid host reentry. */}
      }
    });
    check(injected,`caught same-root reentry injected at ${site}`); closed(x);
  }
  console.log('[projectile-flight-prefix] PASS: genuine HIT and saved-owner joint11 refresh, exhaustive signed16 yaw bits, actual -0 X/+0 Y/Concat direction, source-order and full-width faults, target/nonzero boundaries, zero HIT skip, actor-matrix alias refusal and permanent failure closure; explicit synthetic operands, mandatory Normalize refusal, no flight/original/estimator claim');
}
