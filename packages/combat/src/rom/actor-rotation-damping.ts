/** Bounded rotation body80059fac..8005a110 of actual80059f5c, offline only.
 * Evidence: read_archived_actor_rotation_evidence.py authenticates the source
 * instructions and constants in both archived snapshots. The caller's mode,
 * flags and special branches are NOT implemented here. No production wiring,
 * family descriptor provenance or original-execution parity is claimed.
 *
 * The coefficient is source fsubs(1, mapping1dc8), then fused fmadds using
 * archived3dccccd0 (NOT usual .1f) and3f666666. Each signed-short conversion
 * through4330000080000000 is exact; fmuls rounds before signed32 fctiwz and
 * the low16 store. RN00/NI0, finite exact f32 and signed32 conversion range are
 * admission bounds, not emulation of invalid-conversion saturation/FPSCR.
 *
 * Each of at most eight iterations reloads canonical mapping.descriptor4b0
 * and the registered raw8c descriptor. Source+b0 is raw8c[0x24+i]. Signed -1
 * ends only the list; trailing joint1 X/Y/Z always run, even after list joint1.
 * Joint1 X is the actual unsigned BAM16 steerYaw; other corrections remain
 * signed values on the SAME world corrections18d4 rows. There is no copied
 * list, clock, correction table, family default, or second joint1 X owner.
 *
 * Non-proxy own-data owners must be stable and synchronous. Host identity
 * checks inspect metadata, not eagerly loaded source scalar values. Reached
 * reads/stores stay ordered and lazy; refusals retain earlier effects. Fixed
 * methods retain receivers, caught reentry poisons the enclosing operation,
 * and genuine-runtime brands and actual-actor claims are permanent.
 */
import type {RomActor} from './actor.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding,
  SourceActorWorldMatrixStorage} from './actor-world-matrix.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';

export interface SourceActorRotationDampingSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor' | 'getStorage'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getDescriptor'>;
}
export interface SourceActorRotationDampingRuntime {
  bindActor(identity: symbol): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): object;
  getWorldStorage(identity: symbol): SourceActorWorldMatrixStorage;
  /** Retained storage/array/rows only, never actual/world/mapping or scalar reads. */
  getStorageOwners(identity: symbol): readonly object[];
  /** Already reached descriptors only; does not load descriptor4b0. */
  getKnownDescriptorRecords(): readonly object[];
  /** Rotation body only: the caller supplies actual80059f5c's admission gates. */
  assertActorComplete(identity: symbol): void;
  updateActor(identity: symbol): void;
}
const genuineRuntimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
const incompleteActors = new WeakSet<object>();
/** A successful store followed by refusal cannot be bypassed by later caller gates. */
export function hasIncompleteSourceActorRotationDamping(actual: object): boolean {
  return incompleteActors.has(actual);
}
export function isSourceActorRotationDampingRuntime(value: unknown): value is SourceActorRotationDampingRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-rotation-damping] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(value, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
const s16 = (value: number): number => value << 16 >> 16;
// Authenticated804373c8/c4/c0, immutable module constants, no new data owner.
const ONE = 1; //3f800000
const WEIGHT = 0.10000002384185791; //3dccccd0
const BASE = 0.8999999761581421; //3f666666

export function createSourceActorRotationDampingRuntime(sources: SourceActorRotationDampingSources): SourceActorRotationDampingRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorRotationDampingSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const result = Reflect.apply(method, receiver, [id]); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor'), worldStorage = capture('world', 'getStorage');
  const mappingActor = capture('mapping', 'getActor'), mappingDescriptor = capture('mapping', 'getDescriptor');
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const property = (value: object, key: string): PropertyDescriptor | undefined => {
    const found = Object.getOwnPropertyDescriptor(value, key); check(); return found;
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; mapping: object; storage: SourceActorWorldMatrixStorage;
    corrections: object | undefined; rows: ReadonlyMap<string, object>; storageOwners: readonly object[];
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const descriptors = new Map<symbol, object>(), descriptorIdentities = new WeakMap<object, symbol>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned rotation actor'); return value;
  };
  const roots = (e: Entry): object[] => [e.actual, e.world, e.mapping];
  const noShadows = (e: Entry, extra?: object): void => {
    const canonical = new Map<string, object>([
      ['timestep1dc8', e.mapping], ['descriptor4b0', e.mapping],
      ['corrections18d4', e.storage], ['steerYaw', e.actual],
    ]);
    const aliases = ['field1dc8', 'pointer4b0', 'field4b0', 'rotationListB0', 'rotations18d4',
      'short18da', 'field18da', 'steerYaw18da'];
    for (const owner of [...roots(e), ...e.storageOwners, ...(extra === undefined ? [] : [extra])]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && property(owner, key) !== undefined)
          fail(`${key}: competing rotation storage on another owner`);
      }
      for (const key of aliases) if (property(owner, key) !== undefined) fail(`${key}: competing rotation storage alias`);
    }
  };
  const checkRoots = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping'); stable(mappingActor(id), e.mapping, 'mapping actor');
    stable(worldStorage(id), e.storage, 'world storage'); noShadows(e);
  };
  const correction = (id: symbol, e: Entry, index: number): object => {
    // Called only when an actual row load is reached, never for joint1 X.
    integer(index, 0, 31, 'joint correction index');
    stable(worldStorage(id), e.storage, 'world storage');
    const values = read(e.storage, 'corrections18d4');
    if (!Array.isArray(values)) fail('corrections18d4: explicit array storage required');
    if (e.corrections !== values) fail('corrections18d4 owner changed');
    const length = integer(read(values, 'length'), 0, 32, 'corrections18d4 length');
    if (index >= length) fail('joint correction: addressing outside explicitly owned storage');
    const key = String(index), row = record(read(values, key), `joint${index} correction`);
    if (e.rows.get(key) !== row) fail(`joint${index} correction owner changed`);
    // +18da is already owned by steerYaw. Even an unread second X is forbidden,
    // but this row-shape check waits for the first reached row1 access (Y).
    if (index === 1 && property(row, 'x') !== undefined) fail('joint1 X aliases actual steerYaw');
    return row;
  };
  const descriptor = (e: Entry): object => {
    const selected = read(e.mapping, 'descriptor4b0');
    if (selected !== null && typeof selected !== 'symbol') fail('descriptor4b0: decoded symbol or null required');
    if (selected === null) fail('descriptor4b0: null descriptor at reached rotation-list load');
    const value = record(mappingDescriptor(selected), 'descriptor4b0 raw8c');
    if (!Array.isArray(value) || !Object.isSealed(value)) fail('descriptor4b0: sealed raw8c byte array required');
    const previous = descriptors.get(selected);
    if (previous !== undefined) stable(value, previous, 'descriptor4b0 raw8c');
    else {
      if (assigned.has(value) || descriptorIdentities.has(value)) fail('descriptor4b0 aliases another source owner or descriptor identity');
      descriptors.set(selected, value); descriptorIdentities.set(value, selected);
    }
    noShadows(e, value); return value;
  };
  const scaleAxis = (id: symbol, e: Entry, index: number, axis: 'x' | 'y' | 'z', coefficient: number): void => {
    const actualX = index === 1 && axis === 'x';
    const owner = actualX ? e.actual : correction(id, e, index), key = actualX ? 'steerYaw' : axis;
    const source = actualX ? s16(integer(read(owner, key), 0, 65535, key)) : integer(read(owner, key), -32768, 32767, key);
    // lha/xoris/lfd/fsubs with bias4330000080000000 is exactly this signed16
    // integer. It must NOT go through a helper requiring f32 bias operands.
    // f32*f32 fits exactly in binary64 before this one f32 rounding. Using
    // FMA(...,+0) instead would incorrectly change negative-zero products.
    const product = float(Math.fround(source * coefficient), 'fmuls result');
    const converted = integer(Math.trunc(product), -2147483648, 2147483647, 'fctiwz signed32 result');
    // Mark immediately after the successful store, before any caught-reentry
    // check. Once a later failure escapes, no retry can apply damping twice.
    own(owner, key, true); check();
    (owner as unknown as Record<string, unknown>)[key] = actualX ? converted & 65535 : s16(converted);
    incompleteActors.add(e.actual); check();
  };
  const runtime: SourceActorRotationDampingRuntime = {
    bindActor(id) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'actual actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source rotation runtime');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const mapping = record(mappingActor(id), 'mapping actor'); stable(worldMapping(id), mapping, 'world mapping');
      const storage = record(worldStorage(id), 'world storage') as SourceActorWorldMatrixStorage;
      // Identity-only host admission. Missing/invalid source storage and row
      // scalars remain lazy; a sentinel still reaches joint1 X without row1.
      const candidate = property(storage, 'corrections18d4');
      const corrections = candidate && 'value' in candidate && candidate.value !== null && typeof candidate.value === 'object'
        ? candidate.value as object : undefined;
      const rows = new Map<string, object>(), storageOwners = [storage as object];
      if (corrections !== undefined) {
        storageOwners.push(corrections);
        if (Array.isArray(corrections)) for (const key of Object.getOwnPropertyNames(corrections)) {
          if (!/^(0|[1-9][0-9]*)$/.test(key)) continue;
          const p = property(corrections, key);
          if (p && 'value' in p && p.value !== null && typeof p.value === 'object') {
            rows.set(key, p.value as object); storageOwners.push(p.value as object);
          }
        }
      }
      const e: Entry = {actual, world, mapping, storage, corrections, rows, storageOwners: Object.freeze(storageOwners)};
      const records = [...roots(e), ...storageOwners];
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value) || descriptorIdentities.has(value)))
        fail('source owner alias: distinct actual/world/mapping/storage/correction owners required');
      noShadows(e); check(); actors.set(id, e); records.forEach(value => assigned.add(value)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getWorldStorage(id) {return entry(id).storage;},
    getStorageOwners(id) {return entry(id).storageOwners;},
    getKnownDescriptorRecords() {return Object.freeze([...descriptors.values()]);},
    assertActorComplete(id) {
      if (incompleteActors.has(entry(id).actual)) fail('actual actor has known incomplete rotation damping');
    },
    updateActor(id) {guard(() => {
      const e = entry(id);
      if (incompleteActors.has(e.actual)) fail('actual actor has known incomplete rotation damping');
      checkRoots(id, e);
      //59fac c8;59fb4 mapping1dc8;59fbc c4;59fc4 fsubs;59fc8 c0;
      //59fcc conversion bias;59fd0 fused fmadds. No coefficient clamp.
      const one = ONE, timestep = float(read(e.mapping, 'timestep1dc8'), 'timestep1dc8'), weight = WEIGHT;
      const difference = addSourceFloat32(one, -timestep), base = BASE;
      const coefficient = fusedMultiplyAddSourceFloat32(weight, difference, base);
      for (let ordinal = 0; ordinal < 8; ordinal++) {
        stable(mappingActor(id), e.mapping, 'mapping actor');
        const bytes = descriptor(e), at = 0x24 + ordinal;
        const length = integer(read(bytes, 'length'), 0, 0xffffffff, 'raw8c length');
        if (at >= length) fail('descriptor+b0: addressing outside explicitly owned raw8c storage');
        const index = integer(read(bytes, String(at)), 0, 255, 'descriptor+b0 raw byte') << 24 >> 24;
        if (index === -1) break;
        integer(index, 0, 31, 'joint correction index');
        for (const axis of ['x', 'y', 'z'] as const) scaleAxis(id, e, index, axis, coefficient);
      }
      for (const axis of ['x', 'y', 'z'] as const) scaleAxis(id, e, 1, axis, coefficient);
      check(); incompleteActors.delete(e.actual);
    });},
  };
  genuineRuntimes.add(runtime); return Object.freeze(runtime);
}
