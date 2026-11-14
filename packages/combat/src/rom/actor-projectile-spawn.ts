/** Bounded actual8007db5c, row1 only, over the real88aa0 allocation owner.
 * Both bodies and all selected row bytes are authenticated by the fixed
 * read_archived_projectile_spawn_evidence.py reader. Row1 is copied/frozen;
 * missing rows are not defaults. This is static-source offline execution, not
 * retail heap hydration, projectile flight, callback execution or playability.
 *
 * All reached source loads and stores retain instruction order. The newly
 * allocated byte record is the canonical allocation: exact8020b7a8 writes
 * position20 directly through the genuine matrix byte-store path, not a
 * temporary position copied after success. Existing actual/admission/gauge/setup owners
 * supply metadata without legacy bridge fields or source-owner snapshots.
 * Source90 alone gets a new explicit binding. Hooks7dcec/7e698 are numeric words
 * stored for a future lifecycle, never invoked here. Offset2c=0 genuinely skips
 *7b0. Finite binary32, stable synchronous own-data records and explicit pools
 * are host bounds; failed prefixes poison the shared actor and allocator.
 */
import type {RomActor} from './actor.js';
import {isSourceActorDoublePrehookRuntime, isSourceActorDoubleFrameAccess, requireSourceActorDoubleInvocation,
  requireCompleteSourceActorDoubleLifecycle, markIncompleteSourceActorDoubleLifecycle,
  type SourceActorDoublePrehookRuntime, type SourceActorDoubleFrameAccess} from './actor-double-prehook.js';
import {isSourceActorDoubleActionRuntime, type SourceActorDoubleActionRuntime} from './actor-double-action.js';
import {isSourceActorWorldMatrixRuntime, type SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {isSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {isSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {isSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {isSourceActorAnimationSetupRuntime, type SourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {isSourceActorCommandAdmissionRuntime, type SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {isSourceObjectAllocationRuntime, type SourceObjectAllocationRuntime} from './source-object-allocation.js';
import type {SourceJointVector} from './joint-animation-feedback.js';

export interface SourceActorProjectileSpawnRow {
  family2e: number; joint02: number; local04: Readonly<SourceJointVector>; offset2c: number;
}
export interface SourceActorProjectileSpawnBinding {pointer90: object | null}
export interface SourceActorProjectileSpawnSources {
  prehook: SourceActorDoublePrehookRuntime;
  world: SourceActorWorldMatrixRuntime;
  admission: SourceActorCommandAdmissionRuntime;
  gauges: SourceActorGaugeScaleRuntime;
  setup: SourceActorAnimationSetupRuntime;
  allocator: SourceObjectAllocationRuntime;
  /** Explicit decoded row802d6da0, validated against the fixed static evidence. */
  row1: Readonly<SourceActorProjectileSpawnRow>;
}
export interface SourceActorProjectileSpawnRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorProjectileSpawnBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceActorProjectileSpawnBinding>;
  getPrehookRuntime(): SourceActorDoublePrehookRuntime;
  getCueRuntime(): ReturnType<SourceActorCommandAdmissionRuntime['getCueRuntime']>;
  getAllocatorRuntime(): SourceObjectAllocationRuntime;
  getSourceOwners(identity: symbol): readonly object[];
  assertActorComplete(identity: symbol): void;
  /** Identity registered only after every source spawn store completes. */
  getSpawnOwnerIdentity(projectile: symbol): symbol;
  /** Actual88aa0(owner,4,48,0,0) for a completed child's reached8ac80 call. */
  allocateProjectileHit(projectile: symbol): symbol | null;
  /** Host return exposes allocation identity for inspection; source returns void. */
  spawn(identity: symbol, variant: number): symbol | null;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
const frameBinders = new WeakMap<object, (id: symbol, access: SourceActorDoubleFrameAccess) => void>();
const incompleters = new WeakMap<object, (id: symbol) => void>();
/** Internal monotone failure propagation. This never supplies execution authority. */
export function markIncompleteSourceActorProjectileSpawn(runtime: SourceActorProjectileSpawnRuntime, id: symbol): void {
  const mark = incompleters.get(runtime); if (!mark) fail('genuine projectile runtime required for failure propagation'); mark(id);
}
export function isSourceActorProjectileSpawnRuntime(value: unknown): value is SourceActorProjectileSpawnRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
/** Authenticated internal action join. Never exposes the private frame token. */
export function bindSourceActorProjectileSpawnFrame(action: SourceActorDoubleActionRuntime,
  runtime: SourceActorProjectileSpawnRuntime, id: symbol, access: SourceActorDoubleFrameAccess): void {
  if (!isSourceActorDoubleActionRuntime(action) || !isSourceActorProjectileSpawnRuntime(runtime) ||
      action.getProjectileRuntime() !== runtime || action.getActualActor(id) !== runtime.getActualActor(id) ||
      action.getPrehookRuntime() !== runtime.getPrehookRuntime() ||
      !isSourceActorDoubleFrameAccess(access, runtime.getActualActor(id)))
    fail('projectile frame join requires private genuine action binding');
  const bind = frameBinders.get(runtime); if (!bind) fail('genuine projectile frame binder missing'); bind(id, access);
}
function fail(reason: string): never {
  throw Error(`[actor-projectile-spawn] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorProjectileSpawnRuntime(sources: SourceActorProjectileSpawnSources): SourceActorProjectileSpawnRuntime {
  const prehook = own(sources, 'prehook'), world = own(sources, 'world'), admission = own(sources, 'admission'),
    gauges = own(sources, 'gauges'), setup = own(sources, 'setup'), allocator = own(sources, 'allocator');
  if (!isSourceActorDoublePrehookRuntime(prehook) || !isSourceActorWorldMatrixRuntime(world) ||
      !isSourceActorCommandAdmissionRuntime(admission) || !isSourceActorGaugeScaleRuntime(gauges) ||
      !isSourceActorAnimationSetupRuntime(setup) || !isSourceObjectAllocationRuntime(allocator))
    fail('genuine prehook/world/admission/gauge/setup/allocation runtimes required');
  const matrices = world.getMatricesRuntime(), mapping = setup.getActualMapping(), dispatch = setup.getActualDispatch();
  if (!isSourceActorJointMatrixRuntime(matrices) || !isSourceActorJointMappingRuntime(mapping) ||
      !isSourceActorAnimationDispatchRuntime(dispatch)) fail('genuine shared matrix/mapping/dispatch runtimes required');
  const streams = prehook.getStreamsRuntime(), cues = admission.getCueRuntime();
  if (setup.getActualStarts() !== streams || streams.getDispatchRuntime() !== dispatch || dispatch.getSetupRuntime() !== setup ||
      dispatch.getActualMapping() !== mapping) fail('setup/stream/dispatch runtime graph differs');
  const initialRow = own(sources, 'row1'), initialLocal = own(initialRow, 'local04');
  const row: Readonly<SourceActorProjectileSpawnRow> = Object.freeze({
    family2e: integer(own(initialRow, 'family2e'), -32768, 32767, 'row1.family2e'),
    joint02: integer(own(initialRow, 'joint02'), 0, 255, 'row1.joint02'),
    local04: Object.freeze({x: float(own(initialLocal, 'x'), 'row1.x'), y: float(own(initialLocal, 'y'), 'row1.y'), z: float(own(initialLocal, 'z'), 'row1.z')}),
    offset2c: integer(own(initialRow, 'offset2c'), 0, 255, 'row1.offset2c'),
  });
  if (row.family2e !== 3 || row.joint02 !== 11 || !Object.is(row.local04.x, 55) ||
      !Object.is(row.local04.y, 0) || !Object.is(row.local04.z, 0) || row.offset2c !== 0)
    fail('row1 disagrees with authenticated802d6da0 cells');
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const call = <T>(run: () => T): T => {const result = run(); check(); return result;};
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous own record required`);
    return value;
  };
  const byte = (value: unknown, key: string): number => integer(read(value, key), 0, 255, key);
  const half = (value: unknown, key: string): number => integer(read(value, key), 0, 65535, key);
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const pointer = (value: unknown, key: string): object | null => {const p = read(value, key); return p === null ? null : record(p, key);};
  const stable = (value: unknown, expected: unknown, where: string): void => {check(); if (value !== expected) fail(`${where}: canonical owner changed or differs`);};
  interface Entry {actual: RomActor; mapping: object; world: object; status: object; admission: object; gauge: object;
    setupPart0: object; setupActor: object; aim: object; binding: Partial<SourceActorProjectileSpawnBinding>; caller: symbol}
  const actors = new Map<symbol, Entry>(), frameAccesses = new Map<symbol, SourceActorDoubleFrameAccess>();
  const completedSpawns = new Map<symbol, symbol>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned projectile actor'); return e;};
  const partZero = (id: symbol): object => {
    const layout = call(() => mapping.getLayout(id)), parts = read(layout, 'parts'), bank = read(parts, '0'), part = read(bank, '0');
    if (typeof part !== 'symbol') fail('setup bank0 part0 identity required');
    return call(() => setup.getPartBinding(part));
  };
  const ownRecords = (e: Entry): object[] => [e.actual,e.mapping,e.world,e.status,e.admission,e.gauge,e.setupPart0,e.setupActor,e.aim,e.binding];
  const noShadows = (id: symbol, e: Entry): void => {
    const canonical = new Map<string, object>([
      ...['slot','borgNumber','borgMirror94','carriedSlot96','carriedVariant97','team','visibilityTarget','modelScale','collisionScale','aimOrigin518'].map(k => [k,e.actual] as [string,object]),
      ['byte83',call(() => allocator.getActorBinding(id))],
      ['pointer90', e.binding], ['pointerc8',e.admission], ['byteD0',e.admission],
      ['targetScaleB8',e.gauge], ['fieldC4',e.gauge], ['group28',e.setupPart0], ['action29',e.setupPart0],
    ]);
    const records = [...ownRecords(e), ...call(() => prehook.getSourceOwners(id)), ...call(() => allocator.getSourceOwners(id))];
    for (const r of records) {
      for (const [key, expected] of canonical) {
        if (r !== expected && Object.getOwnPropertyDescriptor(r,key) !== undefined) fail(`${key}: competing source storage owner`);
        check();
      }
      for (const key of ['eligibility83','groupEligibility83','slot3e4','byte3e4','field90','owner90','pointer94','byte94','byte96','byte97','byte88','floatB4','fieldB4','fieldB8','floatC0','fieldC0','pointerCC','pointerC8','byte1afc','byte1afd']) {
        if (Object.getOwnPropertyDescriptor(r,key) !== undefined) fail(`${key}: competing source storage alias`); check();
      }
    }
  };
  const owners = (id: symbol, e: Entry): void => {
    requireCompleteSourceActorDoubleLifecycle(e.actual);
    call(() => allocator.assertActorComplete(id));
    stable(call(() => prehook.getActualActor(id)),e.actual,'prehook actual');
    stable(call(() => world.getActualActor(id)),e.actual,'world actual');
    stable(call(() => admission.getActualActor(id)),e.actual,'admission actual');
    stable(call(() => gauges.getActualActor(id)),e.actual,'gauge actual');
    stable(call(() => allocator.getActualActor(id)),e.actual,'allocator actual');
    stable(call(() => world.getActorBinding(id)),e.world,'world binding');
    stable(call(() => prehook.getWorldBinding(id)),e.world,'prehook world');
    stable(call(() => admission.getWorldBinding(id)),e.world,'admission world');
    stable(call(() => gauges.getWorldBinding(id)),e.world,'gauge world');
    stable(call(() => world.getMappingActor(id)),e.mapping,'world mapping');
    stable(call(() => mapping.getActor(id)),e.mapping,'setup mapping');
    stable(call(() => admission.getMappingActor(id)),e.mapping,'admission mapping');
    stable(call(() => prehook.getMappingActor(id)),e.mapping,'prehook mapping');
    stable(call(() => prehook.getStatusBinding(id)),e.status,'prehook status');
    stable(call(() => admission.getStatusBinding(id)),e.status,'admission status');
    stable(call(() => gauges.getStatusBinding(id)),e.status,'gauge status');
    stable(call(() => admission.getActorBinding(id)),e.admission,'admission binding');
    stable(call(() => gauges.getActorBinding(id)),e.gauge,'gauge binding');
    stable(call(() => setup.getActorBinding(id)),e.setupActor,'setup actor');
    stable(partZero(id),e.setupPart0,'setup part0');
    stable(read(e.actual,'aimOrigin518'),e.aim,'actual aim518');
    stable(call(() => world.getMatricesRuntime()),matrices,'world matrix runtime');
    stable(call(() => admission.getCueRuntime()),cues,'admission cues');
    stable(call(() => cues.getMappingActor(id)),e.mapping,'cue mapping');
    stable(call(() => cues.getDispatchBinding(id)),call(() => dispatch.getActorBinding(id)),'cue dispatch');
    noShadows(id,e);
  };
  const runtime: SourceActorProjectileSpawnRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = call(() => prehook.getActualActor(id));
      if (claimed.has(actual)) fail('actual already claimed by projectile spawn runtime');
      const binding: Partial<SourceActorProjectileSpawnBinding> = {};
      record(initial,'initial binding');
      for (const key of Reflect.ownKeys(initial)) {
        if (key !== 'pointer90') fail(`${String(key)}: not missing source90 storage`); check();
      }
      if (Object.getOwnPropertyDescriptor(initial,'pointer90') !== undefined) binding.pointer90 = pointer(initial,'pointer90');
      const e: Entry = {actual, mapping:call(() => prehook.getMappingActor(id)),world:call(() => prehook.getWorldBinding(id)),
        status:call(() => prehook.getStatusBinding(id)),admission:call(() => admission.getActorBinding(id)),gauge:call(() => gauges.getActorBinding(id)),
        setupPart0:partZero(id),setupActor:call(() => setup.getActorBinding(id)),aim:record(read(actual,'aimOrigin518'),'aim518'),
        binding:Object.seal(binding),caller:Symbol('private projectile allocation caller')};
      if (new Set(ownRecords(e)).size !== ownRecords(e).length) fail('projectile source owner alias');
      owners(id,e); call(() => allocator.claimActor(id,e.caller)); actors.set(id,e); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getActorBinding(id) {return entry(id).binding;},
    getPrehookRuntime() {return prehook;}, getCueRuntime() {return cues;}, getAllocatorRuntime() {return allocator;},
    getSourceOwners(id) {return Object.freeze([...new Set([...ownRecords(entry(id)),row,row.local04,...allocator.getSourceOwners(id)])]);},
    assertActorComplete(id) {const e = entry(id); requireCompleteSourceActorDoubleLifecycle(e.actual); allocator.assertActorComplete(id);},
    getSpawnOwnerIdentity(projectile) {
      const id = completedSpawns.get(projectile);
      if (id === undefined) fail('projectile has no completed genuine spawn');
      return id;
    },
    allocateProjectileHit(projectile) {return guard(() => {
      const id = completedSpawns.get(projectile);
      if (id === undefined) fail('HIT allocation requires completed genuine spawn');
      const e = entry(id);
      try {owners(id,e); return call(() => allocator.allocateProjectileHit(id,e.caller));}
      catch (error) {
        markIncompleteSourceActorDoubleLifecycle(e.actual);
        allocator.markActorIncomplete(id,e.caller); throw error;
      }
    });},
    spawn(id, variant) {return guard(() => {
      const e = entry(id); requireSourceActorDoubleInvocation(e.actual,'projectile',runtime);
      try {
        owners(id,e);
        const selected = integer(variant,0,0xffffffff,'variant register') & 255;
        const family = half(e.actual,'borgNumber') << 16 >> 16; //db90 before selected row family
        if (selected !== 1) fail(`8007db5c row${selected} is not authenticated`);
        if (family !== row.family2e) return null; // source return, no allocation
        const access = frameAccesses.get(id), allocate = () => allocator.allocateProjectile(id,e.caller);
        const child = call(() => access === undefined ? allocate() : access.invoke('allocation',allocator,allocate));
        if (child === null) return null;
        const u8 = (offset: number, value: number): void => {call(() => allocator.writeU8(child,offset,value));};
        const u16 = (offset: number, value: number): void => {call(() => allocator.writeU16(child,offset,value));};
        const u32 = (offset: number, value: number): void => {call(() => allocator.writeU32(child,offset,value));};
        const sf = (offset: number, value: number): void => {call(() => allocator.writeF32(child,offset,value));};
        const ptr = (offset: number, value: object | null): void => {
          const target = value === null ? null : call(() => allocator.getPointerIdentity(value));
          call(() => allocator.writePointer(child,offset,target));
        };
        u8(0,1); u8(0x10,15); u8(0x11,variant & 255);
        u32(0x0c,0x8007dcec); u32(0x10c,0x8007e698);
        call(() => allocator.writePointer(child,0x8c,id));
        ptr(0x90,pointer(e.binding,'pointer90'));
        u16(0x94,half(e.actual,'borgMirror94'));
        u8(0x96,byte(e.actual,'carriedSlot96')); u8(0x97,byte(e.actual,'carriedVariant97')); u8(0x88,byte(e.actual,'team'));
        ptr(0xc8,pointer(e.admission,'pointerc8')); ptr(0xcc,pointer(e.actual,'visibilityTarget'));
        sf(0xb8,f(e.gauge,'targetScaleB8')); sf(0xb4,f(e.actual,'modelScale'));
        sf(0x58,f(e.actual,'modelScale')); sf(0x5c,f(e.actual,'modelScale')); sf(0x60,f(e.actual,'modelScale'));
        sf(0xc0,f(e.actual,'collisionScale')); sf(0xc4,f(e.gauge,'fieldC4')); u8(0xd0,byte(e.admission,'byteD0'));
        const joint = row.joint02 << 24 >> 24;
        const matrix = call(() => world.getWorldMatrix(id,joint));
        const storage = call(() => world.getStorage(id)), matrixId = read(read(storage,'matrices8d4'),String(joint));
        if (typeof matrixId !== 'symbol') fail('joint11 source matrix identity required');
        stable(call(() => matrices.getMatrix(matrixId)),matrix,'same actual joint11 matrix');
        const childBytes = call(() => allocator.getObject(child));
        if (ownRecords(e).includes(childBytes)) fail('allocated child aliases source storage');
        call(() => matrices.transformPointBytes(matrixId,row.local04,childBytes,0x20));
        if ((row.offset2c << 24 >> 24) !== 0) fail('row1 offset flag disagrees with authenticated zero');
        //dca4/a8 load two words BEFORE either destination store, then Z.
        const aimX = f(e.aim,'x'), aimY = f(e.aim,'y');
        sf(0x144,aimX); sf(0x148,aimY); sf(0x14c,f(e.aim,'z'));
        u8(0x150,byte(e.setupPart0,'group28')); u8(0x151,byte(e.setupPart0,'action29'));
        completedSpawns.set(child, id);
        return child;
      } catch (error) {
        markIncompleteSourceActorDoubleLifecycle(e.actual);
        // Both owners remain closed even when source metadata fails after88aa0.
        allocator.markActorIncomplete(id,e.caller); throw error;
      }
    });},
  };
  runtimes.add(runtime);
  incompleters.set(runtime,id => {const e = entry(id); markIncompleteSourceActorDoubleLifecycle(e.actual); allocator.markActorIncomplete(id,e.caller);});
  frameBinders.set(runtime,(id,access) => {entry(id); if (frameAccesses.has(id)) fail('projectile already frame bound'); frameAccesses.set(id,access);});
  return Object.freeze(runtime);
}
