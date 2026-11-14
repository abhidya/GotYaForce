/** Bounded actual800686f0, from authenticated800686f0..80068980 and
 * chunk_0008.c:4692. Explicit offline owners, not implicit retail hydration.
 * The global skip, three reset/release/warmup slots and ordinary return are
 * real source control flow. Absent optional genuine effects, mature held
 * charging retains its bank/654 writes then refuses80068838->800f0104 before
 * threshold reads, and ready transitions refuse800061cc. Genuine bounded
 * sound keepalive permits later threshold/clamp/655 work; real color-channel
 * initialization completes ready transitions. Cold sound starts/replacement
 * still refuse, and no callback pretends those effects ran.
 *
 * Existing world768/5e0/584/5b4/5d4, status6fc, mapping4b0/raw8c and attribute
 * 4ac/parameter owners remain live and unique. Only missing58e/63c..655 are
 * copied/sealed here. Global/data owners are explicit shared borrowed records. Reached constants
 * require authenticated10/+0/1/2 bits; selected table words remain live u32.
 * Stable synchronous non-proxy own-data records and finite exact binary32,
 * RN00/NI0 are admission bounds, not observed retail/FPSCR provenance.
 * Reads and destination checks follow the reached instruction prefix. Earlier
 * writes remain on refusal, and caught mutation reentry poisons the outer call.
 */
import type {BurstMeterState} from '../types.js';
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';
import {isSourceActorChargeEffectsRuntime, type SourceActorChargeEffectsRuntime} from './actor-charge-effects.js';

export interface SourceActorInputChargeBinding {
  byte58e: number;
  field63c: number; field640: number; field644: number;
  field648: number; field64c: number; field650: number;
  byte654: number; byte655: number;
}
export interface SourceActorInputChargeGlobal {
  byte1829?: number;
  /** Same80433934 owner; reached voice gate, not a default audio policy. */
  byte45?: number;
  /** Same matrix-global owner; explicit source team rows, never a copied flag. */
  teamRows103?: readonly Pick<BurstMeterState, 'charged'>[];
}
export interface SourceActorInputChargeData {
  float80437628?: number; float8043762c?: number;
  float80437630?: number; float80437634?: number;
  /** Explicit authenticated command-capture/trig constants on this data owner. */
  float80437678?: number; float80437078?: number;
  flags3994?: readonly number[];
  /** Explicit decoded big-endian u32 arrays at802d3970/397c. */
  held3970?: readonly number[]; release397c?: readonly number[];
}
export interface SourceActorInputChargeSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getMappingActor'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor' | 'getAttributeBinding'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getDescriptor'>;
  attributes: Pick<SourceActorAttributeRefreshRuntime, 'getActualActor' | 'getActorBinding' | 'getParameterDescriptor'>;
  global: SourceActorInputChargeGlobal;
  data: SourceActorInputChargeData;
  /** Optional genuine bounded color initializer/sound keepalive, never callbacks. */
  effects?: SourceActorChargeEffectsRuntime;
}
export interface SourceActorInputChargeRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorInputChargeBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceActorInputChargeBinding>;
  getStatusBinding(identity: symbol): object;
  getMappingActor(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  /** Reached descriptor load through this SAME retained mapping registry. */
  getMappingDescriptor(identity: symbol): number[];
  /** Already reached raw8c owners only; never loads an actor pointer. */
  getKnownDescriptorRecords(): readonly object[];
  getGlobal(): SourceActorInputChargeGlobal;
  getData(): SourceActorInputChargeData;
  getEffects(): SourceActorChargeEffectsRuntime | undefined;
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
export function isSourceActorInputChargeRuntime(value: unknown): value is SourceActorInputChargeRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
const FLOATS = ['field63c', 'field640', 'field644', 'field648', 'field64c', 'field650'] as const;
const BYTES = ['byte58e', 'byte654', 'byte655'] as const;
const WARMUPS = ['field63c', 'field640', 'field644'] as const;
const BANKS = ['field648', 'field64c', 'field650'] as const;
const THRESHOLDS = ['field184', 'field188', 'field18c'] as const;
function fail(reason: string): never {
  throw Error(`[actor-input-charge] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
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
export function createSourceActorInputChargeRuntime(sources: SourceActorInputChargeSources): SourceActorInputChargeRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (r: unknown, key: string): unknown => {const value = own(r, key); check(); return value;};
  const write = (r: unknown, key: string, value: number): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: 'world' | 'status' | 'mapping' | 'attributes' | 'effects', key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol, ...args: unknown[]): unknown => {const value = Reflect.apply(method, receiver, [id, ...args]); check(); return value;};
  };
  const worldActor = capture('world', 'getActualActor'), statusActor = capture('status', 'getActualActor');
  const worldMapping = capture('world', 'getMappingActor'), attributeActor = capture('attributes', 'getActualActor');
  const statusMapping = capture('status', 'getMappingActor'), statusAttribute = capture('status', 'getAttributeBinding');
  const statusBinding = capture('status', 'getActorBinding'), mappingActor = capture('mapping', 'getActor');
  const mappingDescriptor = capture('mapping', 'getDescriptor'), attributeBinding = capture('attributes', 'getActorBinding');
  const parameterDescriptor = capture('attributes', 'getParameterDescriptor');
  const global = record(read(sources, 'global'), 'source global') as SourceActorInputChargeGlobal;
  const data = record(read(sources, 'data'), 'source constants/tables') as SourceActorInputChargeData;
  const effectsProperty = Object.getOwnPropertyDescriptor(sources, 'effects');
  if (effectsProperty !== undefined && !isSourceActorChargeEffectsRuntime(read(sources, 'effects')))
    fail('effects require the genuine source runtime, not callbacks');
  const effects = effectsProperty === undefined ? undefined : read(sources, 'effects') as SourceActorChargeEffectsRuntime;
  const effectActual = !effects ? undefined : capture('effects', 'getActualActor');
  const effectBinding = !effects ? undefined : capture('effects', 'getActorBinding');
  const keepSound = !effects ? undefined : capture('effects', 'keepChargeSound');
  const initializeColor = !effects ? undefined : capture('effects', 'initializeReadyColor');
  const effectData = effects?.getData(), effectSound = effects?.getSound();
  const optionalTable = (key: 'held3970' | 'release397c'): object | undefined => {
    const property = Object.getOwnPropertyDescriptor(data, key); check();
    if (property === undefined) return undefined;
    const value = read(data, key);
    if (!Array.isArray(value)) fail(`${key}: explicit own-data array required`);
    return value;
  };
  const heldTable = optionalTable('held3970'), releaseTable = optionalTable('release397c');
  const shared = [global, data, heldTable, releaseTable, effectData, effectSound].filter((value): value is object => value !== undefined);
  if (new Set(shared).size !== shared.length) fail('global/data/table owner alias');
  // Inspect only own object references, never selected scalar fields. A sound
  // row is shared across actors, but cannot be another input/storage owner.
  const effectStorageOwners = (): object[] => {
    const nested: object[] = [];
    for (const key of ['records3ae8', 'scripts']) {
      const p = effectSound && Object.getOwnPropertyDescriptor(effectSound, key); check();
      const map = p && 'value' in p ? p.value : undefined;
      if (map === null || typeof map !== 'object') continue;
      nested.push(map);
      for (const descriptor of Object.values(Object.getOwnPropertyDescriptors(map))) {
        if ('value' in descriptor && descriptor.value !== null && typeof descriptor.value === 'object') nested.push(descriptor.value);
      }
      check();
    }
    return nested;
  };
  const checkEffectStorage = (actorOwners: object[]): void => {
    const nested = effectStorageOwners();
    const owners = [...shared, ...actorOwners, ...nested];
    if (new Set(owners).size !== owners.length) fail('charge/effect storage owner alias');
    if (nested.some(owner => descriptorIdentities.has(owner) || parameterIdentities.has(owner)))
      fail('effect storage aliases an observed source descriptor/parameter owner');
  };
  const b = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const u = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const f = (r: unknown, key: string): number => float(read(r, key), key);
  const constant = (key: 'float80437628' | 'float8043762c' | 'float80437630' | 'float80437634', expected: number): number => {
    const value = f(data, key);
    if (!Object.is(value, expected)) fail(`${key}: authenticated source constant bits required`);
    return value;
  };
  const pointer = (value: unknown, where: string): symbol => {
    if (typeof value !== 'symbol') fail(`${where}: explicitly owned non-null decoded symbol required`);
    return value;
  };
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): object => {
    if (get(id) !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
    return expected;
  };
  const exclusive = (actual: object): void => {
    for (const key of [...FLOATS, ...BYTES, 'byte6fc', 'flags5e0', 'inputFlags5d4', 'sourceAmmoRefillRate']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing source owner present`);
      check();
    }
  };
  interface Entry {actual: RomActor; status: object; mapping: object; attribute: object; effect?: object; binding: Partial<SourceActorInputChargeBinding>}
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const descriptors = new Map<symbol, object>(), parameters = new Map<symbol, object>();
  const descriptorIdentities = new WeakMap<object, symbol>(), parameterIdentities = new WeakMap<object, symbol>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned charge actor'); return value;};
  const independent = (owners: object[]): void => {
    if (new Set(owners).size !== owners.length || owners.some(value => shared.includes(value) || assigned.has(value) ||
      descriptorIdentities.has(value) || parameterIdentities.has(value))) fail('source charge owner alias');
  };
  const sourceDescriptor = (id: symbol, actor: Entry): object => {
    stable(mappingActor, id, actor.mapping, 'mapping actor');
    const selected = pointer(read(actor.mapping, 'descriptor4b0'), 'descriptor4b0');
    const actual = record(mappingDescriptor(selected), 'mapping descriptor raw8c');
    if (!Array.isArray(actual)) fail('mapping descriptor raw8c: explicit own-data byte array required');
    if (descriptors.has(selected) && descriptors.get(selected) !== actual) fail('descriptor4b0 owner changed its actual record');
    const other = descriptorIdentities.get(actual);
    if (assigned.has(actual) || shared.includes(actual) || effectStorageOwners().includes(actual) || parameterIdentities.has(actual) || (other !== undefined && other !== selected))
      fail('descriptor4b0 aliases another source owner or descriptor identity');
    descriptors.set(selected, actual); descriptorIdentities.set(actual, selected); return actual;
  };
  const sourceParameter = (id: symbol, actor: Entry): object => {
    stable(attributeBinding, id, actor.attribute, 'attribute binding');
    const selected = pointer(read(actor.attribute, 'parameter4ac'), 'parameter4ac');
    const actual = record(parameterDescriptor(selected), 'parameter4ac');
    if (parameters.has(selected) && parameters.get(selected) !== actual) fail('parameter4ac owner changed its actual record');
    const other = parameterIdentities.get(actual);
    if (assigned.has(actual) || shared.includes(actual) || effectStorageOwners().includes(actual) || descriptorIdentities.has(actual) || (other !== undefined && other !== selected))
      fail('parameter4ac aliases another source owner or parameter identity');
    parameters.set(selected, actual); parameterIdentities.set(actual, selected); return actual;
  };
  const tableWord = (key: 'held3970' | 'release397c', table: object | undefined, slot: number): number => {
    if (read(data, key) !== table || table === undefined) fail(`${key}: retained table owner changed or missing`);
    if (read(table, 'length') !== 3) fail(`${key}: explicit three-entry table required`);
    return u(table, String(slot));
  };
  const runtime: SourceActorInputChargeRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor; exclusive(actual);
      stable(statusActor, id, actual, 'status actor'); stable(attributeActor, id, actual, 'attribute actor');
      const status = record(statusBinding(id), 'status binding'), mapping = record(mappingActor(id), 'mapping actor');
      const attribute = record(attributeBinding(id), 'attribute binding');
      stable(worldMapping, id, mapping, 'world mapping actor');
      stable(statusMapping, id, mapping, 'status mapping actor'); stable(statusAttribute, id, attribute, 'status attribute binding');
      let effect: object | undefined;
      if (effectActual) {
        stable(effectActual, id, actual, 'effect actor');
        effect = record(effectBinding!(id), 'effect binding');
      }
      const records = [actual, status, mapping, attribute, ...(effect ? [effect] : [])];
      independent(records);
      if (claimed.has(actual)) fail('actual actor already claimed by source charge runtime');
      record(initial, 'initial charge binding');
      const binding: Partial<SourceActorInputChargeBinding> = {};
      for (const key of FLOATS) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = f(initial, key);
      for (const key of BYTES) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = b(initial, key);
      checkEffectStorage([...records, binding]);
      check(); actors.set(id, {actual, status, mapping, attribute, ...(effect ? {effect} : {}), binding: Object.seal(binding)});
      for (const owner of [...records, binding]) assigned.add(owner);
      claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActorBinding(id) {return entry(id).binding;},
    getStatusBinding(id) {return entry(id).status;},
    getMappingActor(id) {return entry(id).mapping;},
    getAttributeBinding(id) {return entry(id).attribute;},
    getMappingDescriptor(id) {return guard(() => sourceDescriptor(id, entry(id)) as number[]);},
    getKnownDescriptorRecords() {return Object.freeze([...descriptors.values()]);},
    getGlobal() {return global;},
    getData() {return data;},
    getEffects() {return effects;},
    updateActor(id) {guard(() => {
      const actor = entry(id), {actual, binding} = actor;
      if (read(sources, 'global') !== global) fail('global owner changed its actual record');
      if (read(sources, 'data') !== data) fail('data owner changed its actual record');
      stable(worldActor, id, actual, 'world actor'); stable(statusActor, id, actual, 'status actor');
      stable(attributeActor, id, actual, 'attribute actor'); stable(worldMapping, id, actor.mapping, 'world mapping actor');
      stable(statusMapping, id, actor.mapping, 'status mapping actor'); stable(statusAttribute, id, actor.attribute, 'status attribute binding'); exclusive(actual);
      if (effectActual) {
        stable(effectActual, id, actual, 'effect actor');
        stable(effectBinding!, id, actor.effect!, 'effect binding');
      }
      checkEffectStorage([actual, actor.status, actor.mapping, actor.attribute, binding, ...(actor.effect ? [actor.effect] : [])]);
      // 68710 global skip reaches no charge scalars or stores.
      if (b(global, 'byte1829') !== 0) return;
      stable(statusBinding, id, actor.status, 'status binding');
      const burst = b(actor.status, 'byte6fc'); // 6871c BEFORE the768 load.
      let rate = f(actual, 'aimRateScale');
      if (burst !== 0) rate = float(Math.fround(rate * constant('float80437628', 10)), 'fmuls rate result');
      const oldReady = b(binding, 'byte655'); write(binding, 'byte655', 0);
      for (let slot = 0; slot < 3; slot++) {
        const descriptor = sourceDescriptor(id, actor);
        if ((b(descriptor, String(0x2f + slot)) << 24 >> 24) === -1) continue;
        const bit = 1 << slot, warmupKey = WARMUPS[slot]!, bankKey = BANKS[slot]!;
        const reset = (): void => {
          const zero = constant('float8043762c', 0);
          write(binding, warmupKey, zero); write(binding, bankKey, zero);
          write(binding, 'byte654', b(binding, 'byte654') & ~bit);
        };
        // Matching584 reset bypasses58e entirely.
        if ((u(actual, 'controlWord') & 3) !== 0 && (b(actual, 'prevActionIndex') << 24 >> 24) === slot + 3) {reset(); continue;}
        if ((b(binding, 'byte58e') & (1 << (slot + 3))) !== 0) {reset(); continue;}
        const held = u(actual, 'statusWord5b4');
        if ((held & tableWord('held3970', heldTable, slot)) === 0) {
          const parameter = sourceParameter(id, actor); // Pointer precedes bank then threshold loads.
          const bank = f(binding, bankKey), threshold = f(parameter, THRESHOLDS[slot]!);
          if (bank >= threshold) {
            const edge = u(actual, 'inputEdge5d4'), mask = tableWord('release397c', releaseTable, slot);
            write(actual, 'inputEdge5d4', (edge | mask) >>> 0);
          }
          const zero = constant('float8043762c', 0), two = constant('float80437634', 2);
          write(binding, warmupKey, zero);
          const freshRate = f(actual, 'aimRateScale'), freshBank = f(binding, bankKey);
          // fnmsubs is NEGATION AFTER the single rounded exact(a*b-c),
          // not fma(-a,b,c). This distinction preserves exact-zero sign.
          write(binding, bankKey, -fusedMultiplyAddSourceFloat32(two, freshRate, -freshBank));
          write(binding, 'byte654', b(binding, 'byte654') & ~bit);
          if (f(binding, bankKey) <= zero) write(binding, bankKey, zero);
        } else {
          const warmup = f(binding, warmupKey), limit = constant('float80437628', 10);
          if (warmup >= limit) {
            write(binding, bankKey, addSourceFloat32(f(binding, bankKey), rate));
            write(binding, 'byte654', b(binding, 'byte654') | bit);
            if (!keepSound) fail('80068838 reached unsupported source call 800f0104 (actor,1,4) before parameter4ac/threshold reads');
            if (keepSound(id) !== undefined) fail('genuine charge sound helper returned asynchronously or unexpectedly');
            // The actual callee returned: reload4ac, then bank, then threshold.
            const parameter = sourceParameter(id, actor);
            const bank = f(binding, bankKey), threshold = f(parameter, THRESHOLDS[slot]!);
            if (bank >= threshold) {
              write(binding, bankKey, threshold);
              write(binding, 'byte655', b(binding, 'byte655') | bit);
            }
            continue;
          }
          write(binding, warmupKey, addSourceFloat32(warmup, constant('float80437630', 1)));
          const after = f(binding, warmupKey);
          if (after > limit) {
            const excess = addSourceFloat32(after, -limit); // fsubs BEFORE bank load.
            write(binding, bankKey, addSourceFloat32(f(binding, bankKey), excess));
            write(binding, warmupKey, limit);
          }
        }
      }
      const ready = b(binding, 'byte655');
      if (oldReady === 0 && ready !== 0) {
        if (!initializeColor) fail('80068944 reached unsupported source call 800061cc (actor,0x13)');
        if (initializeColor(id, 0x13) !== undefined) fail('genuine ready color helper returned asynchronously or unexpectedly');
      }
      if (oldReady !== 0 && ready === 0) {
        if (!initializeColor) fail('80068960 reached unsupported source call 800061cc (actor,0x14)');
        if (initializeColor(id, 0x14) !== undefined) fail('genuine ready color helper returned asynchronously or unexpectedly');
      }
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
