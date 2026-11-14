/** Bounded stored8007dcec callback and initial8007dd84 prefix, not a scheduler.
 * See projectile-callback/initialization-evidence-2026-11-14.md. Only source
 * states0/2/3 and row1 are authenticated. Explicit state2 data admits its real
 * retirement handler; explicit state3 data admits canonical cleanup (see
 * projectile-cleanup-integration-2026-11-14.md). A genuine8ac80 continuation
 * preserves actual zero return or refreshes the same child position, then
 * refuses at the reached flight helper. Missing HIT remains an explicit bound.
 *
 * A separate explicit dispatch consumes a successfully spawned object's SAME
 * bytes. It never runs inline inside7db5c, invents an actor constructor, resumes
 * a failed frame. The separate genuine object scheduler can own this root and
 * enter its private selected-callback body without duplicating the0c load.
 * Frame-owned actors still require the unimplemented outer-frame scheduler join.
 * Draw head/tail and104/108 links are distinct from allocator group4/8 lists.
 * Synchronous non-proxy own-data records are the admitted host storage domain.
 * Prior writes remain on failure; the child, parent and allocator cannot replay.
 */
import {requireSourceObjectSchedulerInvocation, requireStandaloneSourceProjectileRoot,
  type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {isSourceActorProjectileSpawnRuntime, markIncompleteSourceActorProjectileSpawn,
  type SourceActorProjectileSpawnRuntime} from './actor-projectile-spawn.js';
import {isSourceActorStageBoundsRuntime, type SourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import {isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {RomActor} from './actor.js';
import type {SourceAllocationBytes} from './source-object-allocation.js';
import {isSourceProjectileHitRuntime, type SourceProjectileHitRuntime} from './projectile-hit-registration.js';
import {sourceProjectileHeadingRadians, sourceProjectileInitialPitch} from './projectile-heading.js';
import {addSourceFloat32} from './source-float.js';
import type {SourceJointVector} from './joint-animation-feedback.js';

export interface SourceProjectileDrawList {head?: symbol | null; tail?: symbol | null}
export interface SourceProjectileInitializationStack {rotationX: symbol; rotationY: symbol}
export interface SourceProjectileTargetStack {displacement: SourceJointVector}
export interface SourceProjectileRootSources {
  spawns: SourceActorProjectileSpawnRuntime;
  stage: SourceActorStageBoundsRuntime;
  /** Actual separate DAT_80436288[0]/80436290[0] records, not copied group lists. */
  drawList0: SourceProjectileDrawList;
  /** Explicit decoded802d6f98[0] and selected802d6da3, copied and validated. */
  initialState0: number;
  row1Hit03: number;
  /** Optional decoded802d6fa0, admitted only at actual signed state2 dispatch. */
  retirementState2?: number;
  /** Optional decoded802d6fa4, admitted only at actual signed state3 dispatch. */
  cleanupState3?: number;
  /** Optional genuine continuation, never a caller-supplied success callback. */
  hits?: SourceProjectileHitRuntime;
  /** Explicit source temporary matrix storage, distinct from all actor matrices. */
  initializationStack?: SourceProjectileInitializationStack;
  /** Explicit retained source stack28/2c/30, not a target/actor vector alias. */
  targetStack?: SourceProjectileTargetStack;
  /** Explicit host profile for the reached paired-vector helper, never defaulted. */
  processor?: {gqr0: number};
}
export interface SourceProjectileRootRuntime {
  bindProjectile(projectile: symbol): void;
  getObject(projectile: symbol): SourceAllocationBytes;
  getDrawList(): SourceProjectileDrawList;
  getSpawnRuntime(): SourceActorProjectileSpawnRuntime;
  getSourceOwners(projectile: symbol): readonly object[];
  dispatchStoredRoot(projectile: symbol): void;
}
interface SchedulerJoin {prepare(scheduler: SourceObjectSchedulerRuntime, child: symbol): symbol;
  invoke(scheduler: SourceObjectSchedulerRuntime, child: symbol): void; close(scheduler: SourceObjectSchedulerRuntime): void}
const schedulerJoins = new WeakMap<object, SchedulerJoin>();
function schedulerJoin(root: SourceProjectileRootRuntime): SchedulerJoin {
  const join=schedulerJoins.get(root);if(!join || !isSourceProjectileRootRuntime(root)) fail('genuine scheduled projectile root required');return join;
}
export function prepareSourceProjectileScheduledRoot(root: SourceProjectileRootRuntime,scheduler: SourceObjectSchedulerRuntime,child: symbol): symbol {
  return schedulerJoin(root).prepare(scheduler,child);
}
export function invokeSourceProjectileScheduledRoot(root: SourceProjectileRootRuntime,scheduler: SourceObjectSchedulerRuntime,child: symbol): void {
  schedulerJoin(root).invoke(scheduler,child);
}
export function markIncompleteSourceProjectileScheduledRoot(root: SourceProjectileRootRuntime,scheduler: SourceObjectSchedulerRuntime): void {
  schedulerJoin(root).close(scheduler);
}
const runtimes = new WeakSet<object>(), claimedChildren = new WeakSet<object>(), claimedDrawLists = new WeakSet<object>(),
  claimedStackMatrices = new WeakSet<object>(), claimedTargetStacks = new WeakSet<object>();
const cleanupScopes = new WeakMap<object, (spawns: SourceActorProjectileSpawnRuntime, child: symbol) =>
  {drawList: SourceProjectileDrawList; lifetime: symbol}>();
/** Internal genuine join: a branded idle root never authorizes cleanup. */
export function requireSourceProjectileCleanupInvocation(root: SourceProjectileRootRuntime,
  spawns: SourceActorProjectileSpawnRuntime, child: symbol): {drawList: SourceProjectileDrawList; lifetime: symbol} {
  const scope = cleanupScopes.get(root);
  if (!isSourceProjectileRootRuntime(root) || !scope) fail('private active state3 cleanup invocation required');
  return scope(spawns,child);
}
export function isSourceProjectileRootRuntime(value: unknown): value is SourceProjectileRootRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[projectile-root-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field`);
  return p.value;
}
function unsigned(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned source integer required`);
  return value === 0 ? 0 : value;
}
export function createSourceProjectileRootRuntime(sources: SourceProjectileRootSources): SourceProjectileRootRuntime {
  const spawns = own(sources, 'spawns'), stage = own(sources, 'stage'), list = own(sources, 'drawList0');
  if (!isSourceActorProjectileSpawnRuntime(spawns) || !isSourceActorStageBoundsRuntime(stage)) fail('genuine spawn and stage runtimes required');
  if (list === null || typeof list !== 'object' || Array.isArray(list) || ArrayBuffer.isView(list) || list instanceof Promise)
    fail('separate synchronous draw list record required');
  if (claimedDrawLists.has(list)) fail('draw list already claimed');
  const state0 = unsigned(own(sources, 'initialState0'), 0xffffffff, 'state0'), hit = unsigned(own(sources, 'row1Hit03'), 255, 'row1Hit03');
  if (state0 !== 0x8007dd84 || hit !== 1) fail('initial-state or row1 HIT cell differs from authenticated evidence');
  const allocator = spawns.getAllocatorRuntime(), prehook = spawns.getPrehookRuntime();
  const hitProperty = Object.getOwnPropertyDescriptor(sources,'hits');
  if (hitProperty && !('value' in hitProperty)) fail('hits: own data runtime required');
  const hits = hitProperty?.value as unknown;
  if (hits !== undefined && (!isSourceProjectileHitRuntime(hits) || hits.getSpawnRuntime() !== spawns))
    fail('genuine HIT runtime with same completed-spawn owner required');
  const draw = list as SourceProjectileDrawList;
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const call = <T>(run: () => T): T => {const value = run(); check(); return value;};
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const writeList = (key: 'head' | 'tail', value: symbol | null): void => {own(draw, key, true); check(); draw[key] = value; check();};
  const same = (value: unknown, expected: unknown, where: string): void => {check(); if (value !== expected) fail(`${where}: source owner changed or differs`);};
  interface Entry {id: symbol; origin: symbol; actual: RomActor; bytes: SourceAllocationBytes; stage: object; world: object; status: object; incomplete: boolean; released: boolean; lifetime: symbol}
  const children = new Map<symbol, Entry>();
  let cleanupEntry: Entry | undefined;
  const entry = (id: symbol): Entry => {const e = children.get(id); if (!e) fail('unknown/non-owned projectile'); return e;};
  const owners = (e: Entry): void => {
    if (e.incomplete) fail('known incomplete projectile root');
    call(() => spawns.assertActorComplete(e.origin));
    same(call(() => spawns.getSpawnOwnerIdentity(e.id)), e.origin, 'completed spawn');
    same(call(() => spawns.getSpawnLifetime(e.id)), e.lifetime, 'completed spawn lifetime');
    same(call(() => spawns.getActualActor(e.origin)), e.actual, 'spawn actor');
    same(call(() => stage.getActualActor(e.origin)), e.actual, 'stage actor');
    same(call(() => allocator.getObject(e.id)), e.bytes, 'same child bytes');
    same(call(() => stage.getActorBinding(e.origin)), e.stage, 'stage18');
    same(call(() => stage.getWorldBinding(e.origin)), e.world, 'stage world');
    same(call(() => stage.getStatusBinding(e.origin)), e.status, 'stage status');
    same(call(() => prehook.getWorldBinding(e.origin)), e.world, 'spawn world');
    same(call(() => prehook.getStatusBinding(e.origin)), e.status, 'spawn status');
    for (const key of ['lifecycle18', 'byte18', 'state18']) {
      if (Object.getOwnPropertyDescriptor(e.actual, key) !== undefined) fail(`${key}: competing actual actor storage`); check();
    }
  };
  const owner90 = (e: Entry, pointer: symbol | null): RomActor => {
    // This bounded graph represents the existing genuine main-actor owner only.
    // Null/other registered pointers are never replaced by8c or self defaults.
    if (pointer === null) fail('actual pointer90 is null at reached owner dereference');
    if (pointer !== e.origin) fail('pointer90 owner is outside the bound genuine main-actor domain');
    same(call(() => allocator.getPointerTarget(pointer)), e.actual, 'pointer90 actual'); return e.actual;
  };
  const u8 = (id: symbol, offset: number): number => call(() => allocator.readU8(id, offset));
  const s8 = (id: symbol, offset: number): number => call(() => allocator.readS8(id, offset));
  const word = (id: symbol, offset: number): number => call(() => allocator.readU32(id, offset));
  const ptr = (id: symbol, offset: number): symbol | null => call(() => allocator.readPointer(id, offset));
  const put8 = (id: symbol, offset: number, value: number): void => {call(() => allocator.writeU8(id, offset, value));};
  const put16 = (id: symbol, offset: number, value: number): void => {call(() => allocator.writeU16(id, offset, value));};
  const put32 = (id: symbol, offset: number, value: number): void => {call(() => allocator.writeU32(id, offset, value));};
  const putPtr = (id: symbol, offset: number, value: symbol | null): void => {call(() => allocator.writePointer(id, offset, value));};
  const invalidation = (id: symbol): void => {
    //8aff0 compares raw type3 before sign-extending the same loaded byte.
    const type = u8(id, 2);
    if (type === 3 || (type << 24 >> 24) === 0) put8(id, 0x1d8, 1);
    // r3 retains id. The caller ignores that genuine returned pointer.
  };
  const registerDraw = (id: symbol): void => {
    if (word(id, 0x100) === 0) return;
    put8(id, 0x85, 0);
    const old = read(draw, 'head');
    if (old !== null && typeof old !== 'symbol') fail('draw head: source pointer required');
    writeList('head', id); putPtr(id, 0x108, null);
    if (old === null) {writeList('tail', id); putPtr(id, 0x104, null);}
    else {putPtr(id, 0x104, old); call(() => allocator.getObject(old)); putPtr(old, 0x108, id);}
  };
  const targetPrefix = (e: Entry, capturedTarget: object): never => {
    const processorProperty=Object.getOwnPropertyDescriptor(sources,'processor');check();
    if(!processorProperty || !('value' in processorProperty) || processorProperty.value===undefined)
      fail('actual8020ba78 target displacement requires explicit GQR0 float processor profile');
    const processor=processorProperty.value as unknown;
    if(unsigned(read(processor,'gqr0'),0xffffffff,'gqr0')!==0)
      fail('GQR0 must explicitly select float load/store type0 scale0');
    const supplied=Object.getOwnPropertyDescriptor(sources,'targetStack');check();
    if(!supplied || !('value' in supplied) || supplied.value===undefined)
      fail('8007de9c reached actual8020ba78 target displacement; explicit target stack unavailable');
    const record=(value:unknown,where:string):object=>{
      if(value===null || typeof value!=='object' || Array.isArray(value) || ArrayBuffer.isView(value) || value instanceof Promise)
        fail(`${where}: ordinary own-data record required`);
      return value;
    };
    const stack=record(supplied.value,'target stack'), destination=record(read(stack,'displacement'),'target displacement');
    // Host ownership admission only: inspect descriptors, never invoke accessors
    // or dereference the target pointer. Existing actor vectors, HIT bindings,
    // registered child/descriptor bytes and their immediate owners cannot stand
    // in for the source stack. Matrix arrays are rejected by record admission.
    const sourceOwners=[...call(()=>spawns.getSourceOwners(e.origin)),e.bytes,e.stage,e.world,e.status,draw,sources,processor,capturedTarget];
    if(hits!==undefined) sourceOwners.push(call(()=>hits.getActorBinding(e.origin)));
    const nested:object[]=[];
    for(const owner of sourceOwners) {
      if(owner===sources || owner===capturedTarget || owner===null || typeof owner!=='object') continue;
      const descriptors=Object.getOwnPropertyDescriptors(owner);check();
      for(const descriptor of Object.values(descriptors))
        if('value' in descriptor && descriptor.value!==null && typeof descriptor.value==='object') nested.push(descriptor.value);
    }
    if(stack===destination || [...sourceOwners,...nested].includes(stack) || [...sourceOwners,...nested].includes(destination))
      fail('target stack aliases source owner');
    if(claimedTargetStacks.has(stack)||claimedTargetStacks.has(destination)) fail('target stack already claimed');
    claimedTargetStacks.add(stack);claimedTargetStacks.add(destination);
    const value=(number:unknown,where:string):number=>{
      if(typeof number!=='number'||!Number.isFinite(number)||!Object.is(number,Math.fround(number))) fail(`${where}: finite source float32 required`);
      return number;
    };
    const load=(offset:number):number=>call(()=>allocator.readF32(e.id,offset));
    // Actual8020ba78: paired XY loads/subtract/store, THEN Z loads/subtract.
    const ax=load(0x144),ay=load(0x148),bx=load(0x20),by=load(0x24);
    const x=addSourceFloat32(ax,-bx),y=addSourceFloat32(ay,-by);
    own(destination,'x',true);check();own(destination,'y',true);check();
    (destination as SourceJointVector).x=x;check();(destination as SourceJointVector).y=y;check();
    const az=load(0x14c),bz=load(0x28),z=addSourceFloat32(az,-bz);
    // W1's second lanes are both +1 and execute the unused +0 subtraction.
    addSourceFloat32(1,-1);
    own(destination,'z',true);check();(destination as SourceJointVector).z=z;check();
    //7dea0/7dea4 both loads precede either square. Never reload stackY here.
    const dx=value(read(destination,'x'),'stack28'),dz=value(read(destination,'z'),'stack30');
    const xx=value(Math.fround(dx*dx),'8007dea8 squareX');
    const zz=value(Math.fround(dz*dz),'8007deb0 squareZ');
    const squared=addSourceFloat32(xx,zz); //7deb4, not a fused/unrounded norm.
    if(squared>0) fail('8007dec0 reached actual frsqrte after target horizontal-square prefix; estimator remains unsupported');
    // Even nonzero displacement can round both squares to zero. Source next
    // loads379c0 before7df10 replaces stack28; neither is invented here.
    fail('8007df0c reached unauthenticated FLOAT_804379c0 after zero horizontal-square prefix');
  };
  const initialize = (e: Entry): void => {
    const variant = u8(e.id, 0x11), pointer = ptr(e.id, 0x90);
    put8(e.id, 0x18, 1);
    put32(e.id, 0x100, 0x80047aa4);
    registerDraw(e.id);
    put8(e.id, 0x84, 0x14);
    const actual = owner90(e, pointer), heading = unsigned(read(actual, 'heading'), 0xffff, 'heading');
    put16(e.id, 0x72, heading);
    if (variant !== 1) fail(`8007ddfc reached unauthenticated row${variant} HIT byte`);
    if ((hit << 24 >> 24) !== 1) fail('authenticated signed row1 HIT byte changed');
    if (hits === undefined)
      fail('8007de04 reached unsupported actual8008ac80 HIT registration(child,1); owner27c/3fc and type4 allocation are not hydrated');
    same(call(() => hits.getActualActor(e.origin)),e.actual,'HIT actual');
    const result = call(() => hits.registerHit(e.id,1));
    if (result === 0) {put8(e.id,0x18,2);return;} //7de10/14 then actual epilogue
    // Saved initializer90, NOT a fresh child90/8c read after HIT registration.
    const world = call(() => spawns.getWorldRuntime()), matrices = call(() => world.getMatricesRuntime());
    same(call(() => world.getActualActor(e.origin)),actual,'saved initializer world owner');
    same(call(() => world.getActorBinding(e.origin)),e.world,'same initializer world binding');
    const row = call(() => spawns.getSpawnRow1());
    const joint = unsigned(read(row,'joint02'),255,'row1 joint02') << 24 >> 24;
    const matrix = call(() => world.getWorldMatrix(e.origin,joint));
    const storage = call(() => world.getStorage(e.origin)), matrixId = read(read(storage,'matrices8d4'),String(joint));
    if (typeof matrixId !== 'symbol') fail('saved owner joint11 source matrix identity required');
    same(call(() => matrices.getMatrix(matrixId)),matrix,'same actual saved-owner matrix');
    call(() => matrices.transformPointBytes(matrixId,row.local04,e.bytes,0x20));
    if ((unsigned(read(row,'offset2c'),255,'row1 offset2c') << 24 >> 24) !== 0)
      fail('8007de54 reached unsupported actual8020ba54 nonzero row1 offset');
    // Fresh owner72 and canonical ownerc8 are both read before literal loads.
    const freshHeading = unsigned(read(actual,'heading'),65535,'fresh heading72');
    const admission = call(() => spawns.getAdmissionBinding(e.origin)), target = read(admission,'pointerc8');
    if (target !== null && typeof target !== 'object') fail('ownerc8: explicit source pointer owner required');
    const yaw = sourceProjectileHeadingRadians(freshHeading);
    if (target !== null) targetPrefix(e,target);
    const pitch = sourceProjectileInitialPitch();
    if (!Number.isFinite(yaw) || !Object.is(pitch,-0)) fail('source flight scalar invariant differs');
    const suppliedStack = Object.getOwnPropertyDescriptor(sources,'initializationStack');check();
    if (!suppliedStack || !('value' in suppliedStack))
      fail('8007e030 reached positive HIT continuation at actual8020b238 RotRad(X,-0); explicit initialization stack unavailable');
    const stack = suppliedStack.value as unknown;
    if ([e.actual,e.bytes,e.stage,e.world,e.status,draw].includes(stack as object)) fail('initialization stack aliases source owner');
    const xId=read(stack as object,'rotationX'), yId=read(stack as object,'rotationY');
    if (typeof xId!=='symbol' || typeof yId!=='symbol' || xId===yId) fail('distinct owned initialization stack matrices required');
    // Host ownership admission, not emulated matrix-data loads. No source actor
    // slot can be overwritten to stand in for the two source stack matrices.
    if(call(()=>world.ownsActorMatrix(xId))||call(()=>world.ownsActorMatrix(yId))) fail('initialization stack aliases actor matrix storage');
    const xMatrix=call(()=>matrices.getMatrix(xId)),yMatrix=call(()=>matrices.getMatrix(yId));
    if(claimedStackMatrices.has(xMatrix)||claimedStackMatrices.has(yMatrix)) fail('initialization stack already claimed');
    claimedStackMatrices.add(xMatrix);claimedStackMatrices.add(yMatrix);
    call(()=>matrices.rotateRadiansZero('x',xId,pitch));
    call(()=>matrices.rotateRadiansZero('y',yId,yaw));
    call(()=>matrices.concat(yId,xId,xId));
    for(const [lane,offset] of [[2,0x38],[6,0x3c],[10,0x40]] as const) {
      const value=read(xMatrix,String(lane));
      if(typeof value!=='number'||!Number.isFinite(value)||!Object.is(value,Math.fround(value))) fail('source direction lane requires finite float32');
      call(()=>allocator.writeF32(e.id,offset,value));
    }
    fail('8007e074 reached actual8020bab8 Normalize after source flight-direction stores; reciprocal-square-root estimate remains unsupported');
  };
  const dispatch = (id: symbol,scheduler?: SourceObjectSchedulerRuntime): void => {guard(() => {
      if(scheduler===undefined) requireStandaloneSourceProjectileRoot(runtime);
      const e = entry(id);
      if(scheduler!==undefined) requireSourceObjectSchedulerInvocation(scheduler,runtime,id,'callback',e.lifetime);
      if (e.released) fail('released projectile requires a new completed spawn and explicit rebind');
      if (isSourceActorDoubleFrameClaimed(e.actual)) fail('frame-owned actor requires its unimplemented later source object scheduler');
      try {
        owners(e);
        if (scheduler===undefined && word(id, 0xc) !== 0x8007dcec) fail('unsupported stored projectile root callback');
        //7dd00 captures18,7dd04 loads90, then the SAVED byte is signed/tested.
        const rawState = u8(id, 0x18), pointer = ptr(id, 0x90), state = rawState << 24 >> 24;
        if (state < 2) {
          const actual = owner90(e, pointer), life = unsigned(read(e.stage, 'lifecycle18'), 255, 'lifecycle18') << 24 >> 24;
          let retire = life >= 2;
          if (!retire) {
            const family = unsigned(read(actual, 'borgNumber'), 65535, 'borgNumber') << 16 >> 16;
            retire = family !== call(() => allocator.readS16(id, 0x94));
          }
          if (retire) {put8(id, 0x18, 2); invalidation(id); put8(id, 0x82, 0);}
        }
        const selected = s8(id, 0x18);
        if (selected === 2) {
          // Cell802d6fa0 is a distinct explicit source input. Do not inspect it
          // while another state is selected or default a missing cell to code.
          const supplied = Object.getOwnPropertyDescriptor(sources,'retirementState2');check();
          if (!supplied || ('value' in supplied && supplied.value === undefined))
            fail('8007dd64 reached unauthenticated projectile state2 dispatch cell');
          if (!('value' in supplied)) fail('retirementState2: own data dispatch cell required');
          const target = unsigned(supplied.value,0xffffffff,'retirementState2');
          if (target !== 0x8007e63c) fail('retirementState2: authenticated dispatch target differs');
          // Actual7e654 stores3 before7e658 calls8aff0. The saved child then
          // receives82=0 at7e660 only after that helper returns. This is one
          // complete invocation, not an inline state3/free-list continuation.
          put8(id,0x18,3); invalidation(id); put8(id,0x82,0); return;
        }
        if (selected === 3) {
          const supplied = Object.getOwnPropertyDescriptor(sources,'cleanupState3');check();
          if (!supplied || ('value' in supplied && supplied.value === undefined))
            fail('8007dd64 reached unauthenticated projectile state3 dispatch cell');
          if (!('value' in supplied)) fail('cleanupState3: own data dispatch cell required');
          if (unsigned(supplied.value,0xffffffff,'cleanupState3') !== 0x8007e678)
            fail('cleanupState3: authenticated dispatch target differs');
          cleanupEntry=e;
          try {call(() => spawns.cleanupProjectile(id,runtime));} finally {cleanupEntry=undefined;}
          // A NEW bind after a NEW completed spawn constructs another Entry.
          // The old Entry stays released even if these exact bytes are reused.
          e.released=true;claimedChildren.delete(e.bytes);return;
        }
        if (selected !== 0) fail(`8007dd64 reached unauthenticated projectile state${selected} dispatch cell`);
        if (state0 !== 0x8007dd84) fail('initial source dispatch target changed');
        initialize(e);
      } catch (error) {
        e.incomplete = true; markIncompleteSourceActorProjectileSpawn(spawns, e.origin); throw error;
      }

    });};
  const runtime: SourceProjectileRootRuntime = {
    bindProjectile(id) {guard(() => {
      if (typeof id !== 'symbol' || (children.has(id) && !children.get(id)!.released)) fail('new projectile identity required');
      const origin = call(() => spawns.getSpawnOwnerIdentity(id)), actual = call(() => spawns.getActualActor(origin));
      const bytes = call(() => allocator.getObject(id));
      if (claimedChildren.has(bytes)) fail('child already claimed by source root');
      const e: Entry = {id, origin, actual, bytes, stage: call(() => stage.getActorBinding(origin)),
        world: call(() => stage.getWorldBinding(origin)), status: call(() => stage.getStatusBinding(origin)), incomplete: false,
        released:false,lifetime:call(() => spawns.getSpawnLifetime(id))};
      const owned = call(() => spawns.getSourceOwners(origin));
      if (owned.includes(draw) || draw === bytes || new Set([actual, bytes, e.stage, e.world, e.status, draw]).size !== 6)
        fail('draw list or projectile source owner alias');
      owners(e); children.set(id, e); claimedChildren.add(bytes);
    });},
    getObject(id) {return entry(id).bytes;}, getDrawList() {return draw;}, getSpawnRuntime() {return spawns;},
    getSourceOwners(id) {const e = entry(id); return Object.freeze([e.bytes, e.actual, e.stage, e.world, e.status, draw]);},
    dispatchStoredRoot(id) {dispatch(id);},
  };
  schedulerJoins.set(runtime,{
    prepare(scheduler,id) {
      requireSourceObjectSchedulerInvocation(scheduler,runtime,id,'prepare');
      let lifetime: symbol | undefined;
      guard(()=>{const e=entry(id);
        if(e.released) fail('released projectile requires a new completed spawn and explicit rebind');
        if(isSourceActorDoubleFrameClaimed(e.actual)) fail('frame-owned actor requires its unimplemented later source object scheduler');
        owners(e);lifetime=e.lifetime;
      });
      return lifetime!;
    },
    invoke(scheduler,id) {dispatch(id,scheduler);},
    close(scheduler) {
      requireSourceObjectSchedulerInvocation(scheduler,runtime,undefined,'closure');
      for(const e of children.values()) {e.incomplete=true;markIncompleteSourceActorProjectileSpawn(spawns,e.origin);}
    },
  });
  cleanupScopes.set(runtime,(producer,child) => {
    const e=cleanupEntry;
    if (!busy || poisoned || !e || e.id!==child || e.released || e.incomplete || producer!==spawns)
      fail('private active state3 cleanup invocation required');
    return {drawList:draw,lifetime:e.lifetime};
  });
  runtimes.add(runtime); claimedDrawLists.add(draw); return Object.freeze(runtime);
}
