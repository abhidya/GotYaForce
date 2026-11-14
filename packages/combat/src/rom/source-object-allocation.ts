/** Bounded source88aa0 allocation and88e50 release, not retail heap hydration.
 * Evidence: research/decomp/object-allocator-evidence-2026-11-14.md and
 * research/decomp/projectile-spawn-evidence-2026-11-14.md and
 * research/decomp/projectile-hit-evidence-2026-11-14.md and
 * research/decomp/projectile-cleanup-evidence-2026-11-14.md.
 * No original-runtime execution or oracle parity is claimed.
 * Object and descriptor records retain caller-supplied canonical BE byte storage.
 * Opaque symbols receive local u32 encodings solely to represent pointers in that
 * SAME storage. They are not emulated retail addresses. No RomActor/projectile
 * defaults, copied allocation record, model creation, or injected callback runs.
 * Synthetic offline fixtures must explicitly supply every reached byte/table cell.
 * The authenticated pool3 type3 size is0x2e4; group8..14 classifications are16.
 * Pool4 type4 size is0x1c0; group48..54 classifications are26. Its requested
 * descriptor count is zero; signed negative descriptor availability still fails.
 * Descriptor0 has actual nonnull initializer80006f60 (three zero word stores),
 * not an optional injected success function. Its source record stride is0x2c.
 * Release reaches actual nonnull06ed8; a nonzero descriptor+c remains an
 * explicit JObjUnref boundary. Cleanup preserves source stale fields and uses
 * the SAME pool/group/descriptor owners, with the root-owned draw list passed
 * only through the private active source3 join. No scheduler is invented.
 *
 * Scalar stores preflight one source-width destination before committing. Memset
 * zeroes the real supplied type-sized backing; byte-wise admission failure order
 * is a host bound, not a claim about the original memset implementation. Inputs
 * are synchronous, non-proxy own-data records, not SharedArrayBuffer storage.
 * The world adapter is an identity lookup; unrelated record mutation is outside
 * the admission contract. No constructor, arena offsets, or capacity is invented.
 * Read/store admission is lazy. Prior effects survive failure; allocation failure
 * after a store permanently closes the allocator. Caller capabilities separately
 * close actors whose subsequent spawn initialization was incomplete.
 */
import {requireSourceObjectSchedulerSnapshot, type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {requireCompleteSourceActorDoubleLifecycle, requireSourceActorDoubleInvocation} from './actor-double-prehook.js';

export type SourceAllocationBytes = Partial<Record<number, number>>;
export interface SourceObjectPool {head?: symbol | null; tail?: symbol | null; count?: number}
export interface SourceObjectGroup {head?: symbol | null; tail?: symbol | null}
export interface SourceDescriptorPool {
  freeHead?: symbol | null; activeHead?: symbol | null;
  /** Raw source halfword;197bec sign-extends only when reached. */
  count?: number;
  /** Explicit source code-pointer bits, not a host success callback. */
  initCallback14?: number;
  /** Explicit descriptor0 release cell8036f65c, reached only by197ad8. */
  releaseCallback18?: number;
}
export interface SourceObjectAllocationActorBinding {byte83: number}
/** Symbolic address only: this neither dereferences nor copies source bytes. */
export interface SourceObjectInteriorAddress {readonly base: symbol; readonly byteOffset: number}
/** Frozen alias metadata retains the original target, not a replacement record. */
export interface SourceObjectInteriorTarget {readonly base: object; readonly byteOffset: number}
export interface SourceObjectAllocationSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'>;
  objectPools: Readonly<Record<number, SourceObjectPool>>;
  descriptorPools: Readonly<Record<number, SourceDescriptorPool>>;
  groups: Readonly<Record<number, SourceObjectGroup>>;
  /** Signed type index -> source u16 byte size, DAT_802da660. */
  typeSizes: Readonly<Record<number, number>>;
  /** Effective signed group index -> source raw byte, DAT_802da700. */
  groupEligibility: Readonly<Record<number, number>>;
}
export interface SourceObjectAllocationRuntime {
  registerObject(identity: symbol, bytes: SourceAllocationBytes): void;
  registerDescriptor(identity: symbol, bytes: SourceAllocationBytes): void;
  registerExternal(identity: symbol, actual: object): void;
  bindActor(identity: symbol, initial: Readonly<Partial<SourceObjectAllocationActorBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceObjectAllocationActorBinding>;
  getSourceOwners(identity: symbol): readonly object[];
  assertActorComplete(identity: symbol): void;
  claimActor(identity: symbol, caller: symbol): void;
  allocateProjectile(identity: symbol, caller: symbol): symbol | null;
  allocateProjectileHit(identity: symbol, caller: symbol): symbol | null;
  /** Actual88e50 helper chain, only through the spawn owner private capability. */
  releaseProjectile(identity: symbol, caller: symbol, projectile: symbol, drawList0: SourceObjectGroup): void;
  markActorIncomplete(identity: symbol, caller: symbol): void;
  /** Actual retained DAT_803c706c group record; no copied list or head. */
  getGroup(index: number): SourceObjectGroup;
  /** Host identity-only admission inventory, never a copied source list. */
  getRetainedStorageOwners(): readonly object[];
  /** Narrow actual scheduler stw+76, never a general unaligned scalar API. */
  writeSchedulerRotation76(identity: symbol, value: number, scheduler: SourceObjectSchedulerRuntime): void;
  getObject(identity: symbol): SourceAllocationBytes;
  getDescriptor(identity: symbol): SourceAllocationBytes;
  getPointerTarget(identity: symbol): object;
  getPointerIdentity(actual: object): symbol;
  /** Intern an owned base+offset alias. Scalar access still requires actual memory. */
  getInteriorPointer(base: symbol, byteOffset: number): symbol;
  /** Null for an owned base identity; unknown/foreign identities are rejected. */
  getInteriorAddress(pointer: symbol): Readonly<SourceObjectInteriorAddress> | null;
  readU8(identity: symbol, offset: number): number;
  readS8(identity: symbol, offset: number): number;
  readU16(identity: symbol, offset: number): number;
  readS16(identity: symbol, offset: number): number;
  readU32(identity: symbol, offset: number): number;
  readF32(identity: symbol, offset: number): number;
  readPointer(identity: symbol, offset: number): symbol | null;
  writeU8(identity: symbol, offset: number, value: number): void;
  writeU16(identity: symbol, offset: number, value: number): void;
  writeU32(identity: symbol, offset: number, value: number): void;
  writeF32(identity: symbol, offset: number, value: number): void;
  writePointer(identity: symbol, offset: number, value: symbol | null): void;
}
const schedulerIncomplete = new WeakSet<object>();
/** Permanent failure closure only; grants no execution authority. */
export function markIncompleteSourceObjectAllocation(runtime: SourceObjectAllocationRuntime): void {
  if (!isSourceObjectAllocationRuntime(runtime)) fail('genuine allocator required');
  schedulerIncomplete.add(runtime);
}
const runtimes = new WeakSet<object>(), claimedStorage = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceObjectAllocationRuntime(value: unknown): value is SourceObjectAllocationRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[source-object-allocation] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max)
    fail(`${where}: unsigned integer out of bounds`);
  return value === 0 ? 0 : value;
}
function link(value: unknown, where: string): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
  return value;
}
export function createSourceObjectAllocationRuntime(sources: SourceObjectAllocationSources): SourceObjectAllocationRuntime {
  let busy = false, poisoned = false, incomplete = false, allocating = false, dirty = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T, mutation = false): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    if (mutation && (incomplete || schedulerIncomplete.has(runtime))) fail('permanently incomplete allocation owner');
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;}
    catch (error) {if (allocating && dirty) incomplete = true; throw error;}
    finally {busy = false; allocating = false;}
  };
  const read = (r: unknown, key: string): unknown => {const v = own(r, key); check(); return v;};
  const write = (r: unknown, key: string, v: unknown): void => {
    own(r, key, true); check();
    if (allocating) dirty = true;
    (r as Record<string, unknown>)[key] = v; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise || ArrayBuffer.isView(value))
      fail(`${where}: synchronous non-shared own-data record required`);
    check(); return value;
  };
  const owners = new Map<string, object>(), roles = new WeakMap<object, string>();
  const retain = (value: unknown, role: string, exclusive = true): object => {
    const actual = record(value, role), previous = owners.get(role), other = roles.get(actual);
    if (previous !== undefined && previous !== actual) fail(`${role}: owner changed its actual record`);
    if (other !== undefined && other !== role) fail(`${role}: owner aliases ${other}`);
    if (previous === undefined && exclusive && claimedStorage.has(actual)) fail(`${role}: already claimed allocation storage`);
    owners.set(role, actual); roles.set(actual, role);
    if (exclusive) claimedStorage.add(actual);
    return actual;
  };
  const world = retain(read(sources, 'world'), 'world', false), method = read(world, 'getActualActor');
  if (typeof method !== 'function') fail('world.getActualActor: own data-function required');
  const actualActor = (id: symbol): RomActor => {
    if (read(sources, 'world') !== world) fail('world owner changed');
    const value = Reflect.apply(method, world, [id]); check(); return record(value, 'actual actor') as RomActor;
  };
  const table = (name: 'objectPools' | 'descriptorPools' | 'groups' | 'typeSizes' | 'groupEligibility'): object =>
    retain(read(sources, name), name);
  const pool = (name: 'objectPools' | 'descriptorPools' | 'groups', index: number): object =>
    retain(read(table(name), String(index)), `${name}[${index}]`);
  type Memory = {kind: 'object' | 'descriptor'; bytes: SourceAllocationBytes};
  const memories = new Map<symbol, Memory>(), targets = new Map<symbol, object>(), targetIds = new WeakMap<object, symbol>();
  const interiorIds = new Map<symbol, Map<number, symbol>>(), interiorAddresses = new Map<symbol, Readonly<SourceObjectInteriorAddress>>();
  const handles = new Map<symbol, number>(), identities = new Map<number, symbol>();
  let nextHandle = 1;
  const identify = (id: symbol, target: object): void => {
    if (typeof id !== 'symbol') fail('symbol identity required');
    const prior = targets.get(id), priorId = targetIds.get(target);
    if (prior !== undefined && prior !== target) fail('pointer identity changed its actual owner');
    if (priorId !== undefined && priorId !== id) fail('actual pointer owner already has a different identity');
    if (prior === undefined) {
      if (nextHandle > 0xffffffff) fail('opaque pointer handle capacity exhausted');
      targets.set(id, target); targetIds.set(target, id); handles.set(id, nextHandle); identities.set(nextHandle++, id);
    }
  };
  const target = (id: symbol): object => {
    const value = targets.get(id); if (value === undefined) fail('unknown/non-owned pointer identity'); return value;
  };
  const interiorPointer = (base: symbol, byteOffset: number): symbol => {
    target(base); integer(byteOffset, 0xffff, 'interior byte offset');
    if (byteOffset === 0) return base;
    const prior = interiorAddresses.get(base);
    if (prior !== undefined) {base = prior.base; byteOffset += prior.byteOffset;}
    integer(byteOffset, 0xffff, 'interior byte offset');
    const original = target(base), byOffset = interiorIds.get(base) ?? new Map<number, symbol>();
    const existing = byOffset.get(byteOffset); if (existing !== undefined) return existing;
    const id = Symbol('source interior pointer');
    const view: Readonly<SourceObjectInteriorTarget> = Object.freeze({base: original, byteOffset});
    identify(id, view);
    interiorAddresses.set(id, Object.freeze({base, byteOffset}));
    byOffset.set(byteOffset, id); interiorIds.set(base, byOffset); return id;
  };
  const registerMemory = (id: symbol, initial: SourceAllocationBytes, kind: Memory['kind']): void => {
    if (typeof id !== 'symbol' || targets.has(id)) fail('new symbol memory identity required');
    const bytes = retain(initial, `${kind} bytes ${nextHandle}`) as SourceAllocationBytes;
    identify(id, bytes); memories.set(id, {kind, bytes});
  };
  const memory = (id: symbol, kind?: Memory['kind']): SourceAllocationBytes => {
    const value = memories.get(id);
    if (!value || (kind !== undefined && value.kind !== kind)) fail(`unknown/non-owned ${kind ?? 'memory'} identity`);
    return value.bytes;
  };
  const address = (offset: number, width: number, schedulerWord76 = false): void => {
    integer(offset, 0xffff, 'byte offset');
    if (offset + width > 0x10000) fail('byte range exceeds bounded source record');
    if (width > 1 && offset % width !== 0 && !(schedulerWord76 && offset === 0x76 && width === 4)) fail('unaligned source scalar outside admitted domain');
  };
  const load = (id: symbol, offset: number, width: number): number => {
    address(offset, width); const bytes = memory(id); let value = 0;
    for (let i = 0; i < width; i++) value = value * 256 + integer(read(bytes, String(offset + i)), 255, `byte${(offset + i).toString(16)}`);
    return value;
  };
  const store = (id: symbol, offset: number, width: number, value: number, schedulerWord76 = false): void => {
    address(offset, width, schedulerWord76); integer(value, 2 ** (width * 8) - 1, 'source scalar store');
    const bytes = memory(id);
    // One PPC scalar store is indivisible in this admitted synchronous model.
    for (let i = 0; i < width; i++) {own(bytes, String(offset + i), true); check();}
    if (allocating) dirty = true;
    for (let i = 0; i < width; i++) bytes[offset + i] = Math.floor(value / 2 ** (8 * (width - 1 - i))) % 256;
    check();
  };
  const pointer = (id: symbol, offset: number): symbol | null => {
    const encoded = load(id, offset, 4); if (encoded === 0) return null;
    const result = identities.get(encoded); if (result === undefined) fail('source pointer has no owned opaque identity'); return result;
  };
  const putPointer = (id: symbol, offset: number, value: symbol | null): void => {
    link(value, 'pointer store');
    const encoded = value === null ? 0 : handles.get(value);
    if (encoded === undefined) fail('pointer store has no owned opaque identity');
    store(id, offset, 4, encoded);
  };
  const raw = (r: unknown, key: string, max: number): number => integer(read(r, key), max, key);
  const pointerField = (r: unknown, key: string): symbol | null => link(read(r, key), key);
  interface Actor {actual: RomActor; binding: Partial<SourceObjectAllocationActorBinding>; caller?: symbol; incomplete: boolean}
  const actors = new Map<symbol, Actor>();
  const actor = (id: symbol): Actor => {const a = actors.get(id); if (!a) fail('unknown/non-owned actor identity'); return a;};
  const noShadow = (actual: RomActor): void => {
    for (const key of ['byte83', 'eligibility83', 'groupEligibility83', 'slot3e4', 'byte3e4']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing source actor storage`); check();
    }
  };
  const authorize = (id: symbol, caller: symbol): Actor => {
    const a = actor(id);
    if (typeof caller !== 'symbol' || a.caller !== caller) fail('exclusive actor caller capability required');
    if (a.incomplete) fail('permanently incomplete projectile actor');
    return a;
  };
  const countDescriptor = (p: object): number => raw(p, 'count', 0xffff) << 16 >> 16;
  const allocateDescriptor = (): symbol | null => {
    const p = pool('descriptorPools', 0), count = countDescriptor(p);
    if (count <= 0) return null;
    write(p, 'count', (count - 1) & 0xffff);
    const id = pointerField(p, 'freeHead');
    if (id === null) fail('descriptor free head null at source dereference');
    memory(id, 'descriptor');
    write(p, 'freeHead', pointer(id, 0));
    putPointer(id, 0, null);
    store(id, 9, 1, 1); store(id, 10, 1, 0);
    const previous = pointerField(p, 'activeHead');
    putPointer(id, 4, previous);
    if (previous !== null) {
      //197a80 reloads the active head after the new node+4 store.
      const reloaded = pointerField(p, 'activeHead');
      if (reloaded === null) fail('descriptor active head null at source dereference');
      memory(reloaded, 'descriptor'); putPointer(reloaded, 0, id);
    }
    write(p, 'activeHead', id);
    const callback = raw(p, 'initCallback14', 0xffffffff);
    if (callback !== 0x80006f60) fail(`descriptor row0 initializer ${callback.toString(16)} is outside authenticated80006f60 metadata`);
    // Actual nonnull06f60 callback, not a host success stub: all three
    // source word stores execute before its zero return skips197ad8.
    store(id, 0x20, 4, 0); store(id, 0x24, 4, 0); store(id, 0x28, 4, 0);
    //06d4c retains the actual returned descriptor and clears +0xc.
    store(id, 0x0c, 4, 0); return id;
  };
  const popObject = (poolIndex: 3 | 4): symbol | null => {
    const p = pool('objectPools', poolIndex), id = pointerField(p, 'head');
    if (id === null) return null;
    write(p, 'count', (raw(p, 'count', 0xffff) - 1) & 0xffff);
    memory(id, 'object');
    const next = pointer(id, 4); write(p, 'head', next);
    if (next === null) write(p, 'tail', null);
    const type = load(id, 2, 1), signedType = type << 24 >> 24;
    const size = raw(table('typeSizes'), String(signedType), 0xffff);
    const expectedSize = poolIndex === 3 ? 0x2e4 : 0x1c0;
    if (signedType !== poolIndex || size !== expectedSize)
      fail(`only authenticated object pool${poolIndex} type${poolIndex} size0x${expectedSize.toString(16)} is bounded`);
    // Real canonical bytes, not a replacement record or selective field reset.
    for (let offset = 0; offset < size; offset++) store(id, offset, 1, 0);
    store(id, 2, 1, type); store(id, 3, 1, poolIndex); return id;
  };
  const allocate = (id: symbol, caller: symbol, poolIndex: 3 | 4): symbol | null => {
    const a = authorize(id, caller);
    requireSourceActorDoubleInvocation(a.actual, 'allocation', runtime);
    if (actualActor(id) !== a.actual) fail('world actor owner changed its actual record'); noShadow(a.actual);
    allocating = true; dirty = false;
    const requestedDescriptors = poolIndex === 3 ? 1 : 0, requestedGroup = poolIndex === 3 ? 8 : 48;
    if (countDescriptor(pool('descriptorPools', 0)) < requestedDescriptors) return null;
    const allocated = popObject(poolIndex); if (allocated === null) return null;
    store(allocated, 1, 1, requestedGroup); store(allocated, 0x85, 1, 255);
    let group = requestedGroup;
    if (raw(a.binding, 'byte83', 255) === 0) group += (raw(a.actual, 'slot', 255) << 24 >> 24) + 1;
    store(allocated, 1, 1, group & 255);
    const eligibility = raw(table('groupEligibility'), String(group), 255), expectedEligibility = poolIndex === 3 ? 16 : 26;
    if (group < requestedGroup || group > requestedGroup + 6 || eligibility !== expectedEligibility)
      fail(`only authenticated group${requestedGroup}..${requestedGroup + 6} classification${expectedEligibility} is bounded`);
    store(allocated, 0x83, 1, eligibility);
    const g = pool('groups', group), previous = pointerField(g, 'head');
    write(g, 'head', allocated); putPointer(allocated, 4, null);
    if (previous === null) {write(g, 'tail', allocated); putPointer(allocated, 8, null);}
    else {putPointer(allocated, 8, previous); memory(previous, 'object'); putPointer(previous, 4, allocated);}
    if ((load(allocated, 2, 1) << 24 >> 24) !== 4) {
      for (let index = 0; index < 8; index++)
        putPointer(allocated, 0xe0 + index * 4, index < requestedDescriptors ? allocateDescriptor() : null);
      store(allocated, 0x99, 1, requestedDescriptors);
    }
    return allocated;
  };
  const release = (id: symbol, caller: symbol, child: symbol, draw: SourceObjectGroup): void => {
    const a = authorize(id,caller);
    requireSourceActorDoubleInvocation(a.actual,'allocation',runtime);
    if (actualActor(id) !== a.actual) fail('world actor owner changed its actual record'); noShadow(a.actual);
    memory(child,'object');
    if ([...owners.values(),a.actual,a.binding].includes(draw)) fail('cleanup draw list aliases allocation owner');
    record(draw,'actual cleanup draw list');
    allocating = true; dirty = false;
    const signed = (object: symbol, offset: number): number => load(object,offset,1) << 24 >> 24;
    const unlinkDraw = (): void => {
      const group = signed(child,0x85); //89444/48: -1 is a genuine immediate return.
      if (group === -1) return;
      const previous = pointer(child,0x104), next = pointer(child,0x108);
      if (group !== 0) fail('actual89444 reached unsupported draw-list family or group');
      // Actual group0 has tail at r4, head at r5; it is NOT allocator group order.
      if (previous === null && next === null) {write(draw,'tail',null);write(draw,'head',null);}
      else if (previous === null) {write(draw,'tail',next);putPointer(next!,0x104,null);}
      else if (next === null) {write(draw,'head',previous);putPointer(previous,0x108,null);}
      else {putPointer(previous,0x108,next);putPointer(next,0x104,previous);}
      store(child,0x100,4,0);store(child,0x85,1,255);
    };
    const releaseDescriptor = (descriptor: symbol): void => {
      memory(descriptor,'descriptor');
      // Actual06d80 never clears a null+c. Nonnull requires real JObjUnref.
      if (pointer(descriptor,0x0c) !== null) fail('actual80006da0 reached unsupported8024fd74 JObjUnref');
      const type = signed(descriptor,8);
      if (type !== 0) fail(`actual197b10 reached unauthenticated descriptor row${type} release callback`);
      const p = pool('descriptorPools',type), callback = raw(p,'releaseCallback18',0xffffffff);
      if (callback !== 0x80006ed8) fail('descriptor0 release callback differs from authenticated80006ed8');
      // Actual nonnull06ed8 callback reloads+c even after06d80 saw null.
      if (pointer(descriptor,0x0c) !== null) fail('actual80006ef8 reached unsupported8024fd74 JObjUnref');
      //06ed8 returns0.197ad8 ignores that value and reloads both active links.
      const previous = pointer(descriptor,0), next = pointer(descriptor,4);
      if (previous === null) write(p,'activeHead',next); else putPointer(previous,4,next);
      if (next !== null) putPointer(next,0,previous);
      const free = pointerField(p,'freeHead');
      putPointer(descriptor,0,free);write(p,'freeHead',descriptor);store(descriptor,9,1,0);
      //197bec and197bd8 each resolve the actual shared table; signed load then
      // low16 store preserves wrap. The captured row index is not reread from8.
      const count = countDescriptor(pool('descriptorPools',type));
      write(pool('descriptorPools',type),'count',(count+1)&0xffff);
    };
    const group = signed(child,1);
    if (group !== -1) {
      const previous = pointer(child,4), next = pointer(child,8);
      if (previous === null && next === null) {
        write(pool('groups',group),'head',null);
        write(pool('groups',signed(child,1)),'tail',null); //88eb0 fresh index
      } else if (previous === null) {
        write(pool('groups',group),'head',next);putPointer(next!,4,null);
      } else if (next === null) {
        write(pool('groups',group),'tail',previous);putPointer(previous,8,null);
      } else {putPointer(previous,8,next);putPointer(next,4,previous);}
      if (load(child,2,1) !== 4) {
        unlinkDraw();
        for (let index=0;index<signed(child,0x99);index++) {
          const descriptor = pointer(child,0xe0+index*4);
          if (descriptor !== null) releaseDescriptor(descriptor);
        }
      }
    }
    // Actual89814 uses tail/head/count globals separately and reloads byte3.
    const firstPool = pool('objectPools',signed(child,3)), tail = pointerField(firstPool,'tail');
    if (tail === null) {
      write(firstPool,'tail',child);write(pool('objectPools',signed(child,3)),'head',child);
    } else {
      putPointer(tail,4,child);write(pool('objectPools',signed(child,3)),'tail',child);
    }
    const countPool = pool('objectPools',signed(child,3)), count = raw(countPool,'count',0xffff);
    write(countPool,'count',(count+1)&0xffff);store(child,0,1,0);putPointer(child,4,null);
  };
  const floatBits = new DataView(new ArrayBuffer(4));
  const runtime: SourceObjectAllocationRuntime = {
    registerObject(id, bytes) {guard(() => registerMemory(id, bytes, 'object'), true);},
    registerDescriptor(id, bytes) {guard(() => registerMemory(id, bytes, 'descriptor'), true);},
    registerExternal(id, actual) {guard(() => {record(actual, 'external pointer owner'); identify(id, actual);}, true);},
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new actor symbol identity required');
      const actual = actualActor(id); noShadow(actual);
      if (memories.has(id) || roles.has(actual)) fail('actual actor aliases allocation storage');
      if (claimedActors.has(actual)) fail('actual actor already claimed by allocation runtime');
      const binding: Partial<SourceObjectAllocationActorBinding> = {};
      record(initial, 'initial actor binding');
      if (initial === actual || roles.has(initial)) fail('initial actor binding aliases source owner');
      for (const key of ['slot', 'slot3e4', 'byte3e4', 'eligibility83', 'groupEligibility83']) {
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) fail(`${key}: competing source actor storage`); check();
      }
      const supplied83 = Object.getOwnPropertyDescriptor(initial, 'byte83'); check();
      if (supplied83 !== undefined) binding.byte83 = raw(initial, 'byte83', 255);
      identify(id, actual); actors.set(id, {actual, binding: Object.seal(binding), incomplete: false}); claimedActors.add(actual);
    }, true);},
    getActualActor(id) {return actor(id).actual;},
    getActorBinding(id) {return actor(id).binding;},
    getSourceOwners(id) {const a = actor(id); return [a.actual, a.binding, ...owners.values()];},
    assertActorComplete(id) {
      const a = actor(id); requireCompleteSourceActorDoubleLifecycle(a.actual);
      if (incomplete || schedulerIncomplete.has(runtime) || a.incomplete) fail('permanently incomplete allocation owner');
    },
    claimActor(id, caller) {guard(() => {
      const a = actor(id); if (typeof caller !== 'symbol' || a.caller !== undefined) fail('actor caller already claimed or not a symbol');
      a.caller = caller;
    }, true);},
    markActorIncomplete(id, caller) {guard(() => {
      const a = actor(id);
      if (typeof caller !== 'symbol' || a.caller !== caller) fail('exclusive actor caller capability required');
      a.incomplete = true; incomplete = true;
    });},
    allocateProjectile(id, caller) {return guard(() => allocate(id, caller, 3), true);},
    allocateProjectileHit(id, caller) {return guard(() => allocate(id, caller, 4), true);},
    releaseProjectile(id, caller, child, draw) {guard(() => release(id,caller,child,draw),true);},
    getRetainedStorageOwners() {return Object.freeze([...new Set([...owners.values(),...targets.values()])]);},
    getGroup(index) {return guard(() => {integer(index,0x3fffffff,'effective group index');return pool('groups',index) as SourceObjectGroup;});},
    writeSchedulerRotation76(id,value,scheduler) {
      requireSourceObjectSchedulerSnapshot(scheduler,runtime,id);
      guard(() => store(id,0x76,4,value,true),true);
    },
    getObject(id) {return memory(id, 'object');},
    getDescriptor(id) {return memory(id, 'descriptor');},
    getPointerTarget(id) {return target(id);},
    getPointerIdentity(actual) {const id = targetIds.get(actual); if (id === undefined) fail('actual pointer owner has not been registered'); return id;},
    getInteriorPointer(base, byteOffset) {return guard(() => interiorPointer(base, byteOffset), true);},
    getInteriorAddress(id) {return guard(() => {target(id); return interiorAddresses.get(id) ?? null;});},
    readU8(id, offset) {return guard(() => load(id, offset, 1));},
    readS8(id, offset) {return guard(() => load(id, offset, 1) << 24 >> 24);},
    readU16(id, offset) {return guard(() => load(id, offset, 2));},
    readS16(id, offset) {return guard(() => load(id, offset, 2) << 16 >> 16);},
    readU32(id, offset) {return guard(() => load(id, offset, 4));},
    readF32(id, offset) {return guard(() => {
      floatBits.setUint32(0, load(id, offset, 4), false); const value = floatBits.getFloat32(0, false);
      if (!Number.isFinite(value)) fail('finite exact source float32 required'); return value;
    });},
    readPointer(id, offset) {return guard(() => pointer(id, offset));},
    writeU8(id, offset, value) {guard(() => store(id, offset, 1, value), true);},
    writeU16(id, offset, value) {guard(() => store(id, offset, 2, value), true);},
    writeU32(id, offset, value) {guard(() => store(id, offset, 4, value), true);},
    writeF32(id, offset, value) {guard(() => {
      if (!Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail('finite exact source float32 required');
      floatBits.setFloat32(0, value, false); store(id, offset, 4, floatBits.getUint32(0, false));
    }, true);},
    writePointer(id, offset, value) {guard(() => putPointer(id, offset, value), true);},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
