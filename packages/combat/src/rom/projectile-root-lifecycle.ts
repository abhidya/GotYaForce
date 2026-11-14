/** Bounded stored8007dcec callback and initial8007dd84 prefix, not a scheduler.
 * See projectile-callback/initialization-evidence-2026-11-14.md. Only source
 * state0 and row1 are authenticated. The actual8ac80 HIT registration remains
 * an explicit boundary after genuine89100(0,1), not an assumed empty asset.
 *
 * A separate explicit dispatch consumes a successfully spawned object's SAME
 * bytes. It never runs inline inside7db5c, invents an actor constructor, resumes
 * a failed frame, or claims source8997c/89898 snapshot/loop semantics. Frame-owned
 * actors remain unsupported until that actual later scheduler is implemented.
 * Draw head/tail and104/108 links are distinct from allocator group4/8 lists.
 * Synchronous non-proxy own-data records are the admitted host storage domain.
 * Prior writes remain on failure; the child, parent and allocator cannot replay.
 */
import {isSourceActorProjectileSpawnRuntime, markIncompleteSourceActorProjectileSpawn,
  type SourceActorProjectileSpawnRuntime} from './actor-projectile-spawn.js';
import {isSourceActorStageBoundsRuntime, type SourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import {isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {RomActor} from './actor.js';
import type {SourceAllocationBytes} from './source-object-allocation.js';

export interface SourceProjectileDrawList {head?: symbol | null; tail?: symbol | null}
export interface SourceProjectileRootSources {
  spawns: SourceActorProjectileSpawnRuntime;
  stage: SourceActorStageBoundsRuntime;
  /** Actual separate DAT_80436288[0]/80436290[0] records, not copied group lists. */
  drawList0: SourceProjectileDrawList;
  /** Explicit decoded802d6f98[0] and selected802d6da3, copied and validated. */
  initialState0: number;
  row1Hit03: number;
}
export interface SourceProjectileRootRuntime {
  bindProjectile(projectile: symbol): void;
  getObject(projectile: symbol): SourceAllocationBytes;
  getDrawList(): SourceProjectileDrawList;
  getSpawnRuntime(): SourceActorProjectileSpawnRuntime;
  getSourceOwners(projectile: symbol): readonly object[];
  dispatchStoredRoot(projectile: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedChildren = new WeakSet<object>(), claimedDrawLists = new WeakSet<object>();
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
  const draw = list as SourceProjectileDrawList;
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const call = <T>(run: () => T): T => {const value = run(); check(); return value;};
  const read = (owner: object, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const writeList = (key: 'head' | 'tail', value: symbol | null): void => {own(draw, key, true); check(); draw[key] = value; check();};
  const same = (value: unknown, expected: unknown, where: string): void => {check(); if (value !== expected) fail(`${where}: source owner changed or differs`);};
  interface Entry {id: symbol; origin: symbol; actual: RomActor; bytes: SourceAllocationBytes; stage: object; world: object; status: object; incomplete: boolean}
  const children = new Map<symbol, Entry>();
  const entry = (id: symbol): Entry => {const e = children.get(id); if (!e) fail('unknown/non-owned projectile'); return e;};
  const owners = (e: Entry): void => {
    if (e.incomplete) fail('known incomplete projectile root');
    call(() => spawns.assertActorComplete(e.origin));
    same(call(() => spawns.getSpawnOwnerIdentity(e.id)), e.origin, 'completed spawn');
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
    fail('8007de04 reached unsupported actual8008ac80 HIT registration(child,1); owner27c/3fc and type4 allocation are not hydrated');
  };
  const runtime: SourceProjectileRootRuntime = {
    bindProjectile(id) {guard(() => {
      if (typeof id !== 'symbol' || children.has(id)) fail('new projectile identity required');
      const origin = call(() => spawns.getSpawnOwnerIdentity(id)), actual = call(() => spawns.getActualActor(origin));
      const bytes = call(() => allocator.getObject(id));
      if (claimedChildren.has(bytes)) fail('child already claimed by source root');
      const e: Entry = {id, origin, actual, bytes, stage: call(() => stage.getActorBinding(origin)),
        world: call(() => stage.getWorldBinding(origin)), status: call(() => stage.getStatusBinding(origin)), incomplete: false};
      const owned = call(() => spawns.getSourceOwners(origin));
      if (owned.includes(draw) || draw === bytes || new Set([actual, bytes, e.stage, e.world, e.status, draw]).size !== 6)
        fail('draw list or projectile source owner alias');
      owners(e); children.set(id, e); claimedChildren.add(bytes);
    });},
    getObject(id) {return entry(id).bytes;}, getDrawList() {return draw;}, getSpawnRuntime() {return spawns;},
    getSourceOwners(id) {const e = entry(id); return Object.freeze([e.bytes, e.actual, e.stage, e.world, e.status, draw]);},
    dispatchStoredRoot(id) {guard(() => {
      const e = entry(id);
      if (isSourceActorDoubleFrameClaimed(e.actual)) fail('frame-owned actor requires its unimplemented later source object scheduler');
      try {
        owners(e);
        if (word(id, 0xc) !== 0x8007dcec) fail('unsupported stored projectile root callback');
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
        if (selected !== 0) fail(`8007dd64 reached unauthenticated projectile state${selected} dispatch cell`);
        if (state0 !== 0x8007dd84) fail('initial source dispatch target changed');
        initialize(e);
      } catch (error) {
        e.incomplete = true; markIncompleteSourceActorProjectileSpawn(spawns, e.origin); throw error;
      }
    });},
  };
  runtimes.add(runtime); claimedDrawLists.add(draw); return Object.freeze(runtime);
}
