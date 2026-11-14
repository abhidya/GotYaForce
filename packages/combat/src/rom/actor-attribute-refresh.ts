/** Bounded actual 80055dcc, followed by the existing actual 8004d08c owner.
 * Source: chunk_0006.c:8091–8125; instruction order is authenticated by
 * read_archived_actor_attribute_evidence.py, not inferred from undefined4 C.
 * This is an explicit hydration/ordinary-lifecycle prefix, not a full spawn,
 * tick, production route, original replay or proof of retail input provenance.
 *
 * Mapping selects 4b0 once, modelScale is loaded once, five separate fmuls
 * products are stored in source order, 4ac is reloaded before each limit, then
 * fifteen lfs/stfs pairs run before the one movement call. That call consumes
 * retained world matrices: this runtime never refreshes matrices or clocks.
 * Finite exact-f32 operands/results, RN00/NI0 and non-proxy own-data records
 * are explicit host bounds, not a claim about arbitrary NaN payloads/FPSCR.
 *
 * Existing fields remain on actual RomActor/movement/mapping records. In
 * particular hoverOffset668 is required on the actual actor, and 868/874/880
 * remain the actual actionSpeedRows entries, never copied to a second table.
 * Only missing fields receive explicit new storage. Absent fields stay absent.
 * Owners and captured methods/receivers are fixed; scalars remain live. Reads
 * and writable destinations are checked only when reached. Refusal retains
 * completed stores/effects; caught mutation reentry poisons the outer call.
 */
import type {RomActor} from './actor.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';

export interface SourceActorAttributeRefreshBinding {
  byte87: number;
  field674: number;
  field770: number;
  /** Explicit source 4ac pointer, NOT legacy RomActor.descriptor (4b0). */
  parameter4ac: symbol | null;
  field850: number; field854: number; field858: number;
  field85c: number; field860: number; field864: number;
  field86c: number; field870: number; field878: number;
  field87c: number; field884: number; field888: number;
  field814: number; field818: number; field81c: number;
  field820: number; field824: number; field828: number;
  field82c: number; field830: number; field834: number;
  field838: number; field83c: number; field840: number;
  field844: number; field848: number; field84c: number;
}
/** Scalar extension of the SAME descriptor identity owned by joint mapping. */
export interface SourceActorAttributeDescriptorBinding {
  /** Raw signed-joint selector read at descriptor+10 by actual6bda8. */
  byte10: number;
  field44: number; field48: number; field4c: number; field50: number; field54: number;
}
export interface SourceActorAttributeParameterDescriptor {
  /** Signed-short extension of this SAME 4ac owner, consumed by 8005568c. */
  field04: number; field08: number;
  field74: number; field78: number; field7c: number;
  /** Unsigned table selector on this SAME 4ac owner, consumed by8006826c. */
  byteA3: number;
  /** Charge thresholds on this SAME 4ac owner, consumed by800686f0. */
  field184: number; field188: number; field18c: number;
}
export interface SourceActorAttributeRefreshSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getDescriptor'>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActualActor' | 'getActorBinding' | 'updateActor'>;
}
export interface SourceActorAttributeRefreshRuntime {
  getActualActor(identity: symbol): RomActor;
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorAttributeRefreshBinding>>): void;
  getActorBinding(identity: symbol): Partial<SourceActorAttributeRefreshBinding>;
  bindDescriptor(identity: symbol, initial: Readonly<Partial<SourceActorAttributeDescriptorBinding>>): void;
  getDescriptorBinding(identity: symbol): Partial<SourceActorAttributeDescriptorBinding>;
  createParameterDescriptor(initial: Readonly<Partial<SourceActorAttributeParameterDescriptor>>): symbol;
  getParameterDescriptor(identity: symbol): Partial<SourceActorAttributeParameterDescriptor>;
  refreshActor(identity: symbol): void;
}
const ROW_SOURCES = ['field850', 'field854', 'field858', 'field85c', 'field860', 'field864',
  0, 'field86c', 'field870', 1, 'field878', 'field87c', 2, 'field884', 'field888'] as const;
const ROW_DESTINATIONS = ['field814', 'field818', 'field81c', 'field820', 'field824', 'field828',
  'field82c', 'field830', 'field834', 'field838', 'field83c', 'field840', 'field844', 'field848', 'field84c'] as const;
const ACTOR_FLOATS = ['field674', 'field770', ...ROW_SOURCES.filter((key): key is Exclude<typeof key, number> => typeof key === 'string'),
  ...ROW_DESTINATIONS] as const;
function fail(reason: string): never {
  throw Error(`[actor-attribute-refresh] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
function integer(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned integer out of bounds`);
  return value;
}
function pointer(value: unknown, where: string): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: decoded symbol or null required`);
  return value;
}
export function createSourceActorAttributeRefreshRuntime(sources: SourceActorAttributeRefreshSources): SourceActorAttributeRefreshRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const capture = (name: keyof SourceActorAttributeRefreshSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(fn, receiver, [id]); check(); return value;};
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const worldActor = capture('world', 'getActualActor'), mappingActor = capture('mapping', 'getActor');
  const mappingDescriptor = capture('mapping', 'getDescriptor'), movementActor = capture('movement', 'getActualActor');
  const movementBinding = capture('movement', 'getActorBinding'), updateMovement = capture('movement', 'updateActor');
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const copy = <T extends object>(initial: Readonly<Partial<T>>, fields: readonly (keyof T & string)[]): Partial<T> => {
    record(initial, 'initial binding'); const binding: Record<string, unknown> = {};
    for (const key of fields) {
      const p = Object.getOwnPropertyDescriptor(initial, key); check();
      if (p !== undefined) binding[key] = f(initial, key);
    }
    return binding as Partial<T>;
  };
  interface ActorEntry {
    actual: RomActor; mapping: object; movement: object; rows: readonly number[];
    binding: Partial<SourceActorAttributeRefreshBinding>;
  }
  const actors = new Map<symbol, ActorEntry>();
  // Reject cross-actor aliases even though the individual scalar owners differ.
  const assigned = new WeakSet<object>(), descriptorRecords = new WeakSet<object>();
  const descriptors = new Map<symbol, {actual: object; binding: Partial<SourceActorAttributeDescriptorBinding>}>();
  const parameters = new Map<symbol, Partial<SourceActorAttributeParameterDescriptor>>();
  const actorEntry = (id: symbol): ActorEntry => {const value = actors.get(id); if (!value) fail('unknown/non-owned attribute actor'); return value;};
  const descriptorEntry = (id: symbol | null) => {
    const value = id === null ? undefined : descriptors.get(id);
    if (!value) fail('descriptor scalars require an owned bound mapping descriptor'); return value;
  };
  const parameterEntry = (id: symbol | null) => {
    const value = id === null ? undefined : parameters.get(id);
    if (!value) fail('parameter4ac requires an explicitly owned parameter descriptor'); return value;
  };
  const movement = (id: symbol, actor: ActorEntry): object => {
    if (movementActor(id) !== actor.actual || movementBinding(id) !== actor.movement) fail('movement owner changed its actual record');
    return actor.movement;
  };
  return Object.freeze({
    bindActor(id: symbol, initial: Readonly<Partial<SourceActorAttributeRefreshBinding>>): void {guard(() => {
      if (typeof id !== 'symbol') fail('actor identity must be a symbol');
      if (actors.has(id)) fail('actor already bound');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (movementActor(id) !== actual) fail('world/movement actual RomActor owners differ');
      const mapping = record(mappingActor(id), 'mapping actor'), state = record(movementBinding(id), 'movement binding');
      const rows = read(actual, 'actionSpeedRows');
      if (!Array.isArray(rows) || read(rows, 'length') !== 3) fail('actual actionSpeedRows must retain three owned entries');
      const records = [actual, mapping, state, rows];
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value) || descriptorRecords.has(value)))
        fail('actor storage aliases another actual owner');
      const binding = copy<SourceActorAttributeRefreshBinding>(initial, ACTOR_FLOATS);
      if (Object.getOwnPropertyDescriptor(initial, 'byte87') !== undefined) binding.byte87 = integer(read(initial, 'byte87'), 255, 'byte87');
      if (Object.getOwnPropertyDescriptor(initial, 'parameter4ac') !== undefined) binding.parameter4ac = pointer(read(initial, 'parameter4ac'), 'parameter4ac');
      check(); actors.set(id, {actual, mapping, movement: state, rows, binding: Object.seal(binding)});
      for (const value of records) assigned.add(value);
    });},
    getActualActor(id: symbol) {return actorEntry(id).actual;},
    getActorBinding(id: symbol) {return actorEntry(id).binding;},
    bindDescriptor(id: symbol, initial: Readonly<Partial<SourceActorAttributeDescriptorBinding>>): void {guard(() => {
      if (typeof id !== 'symbol') fail('descriptor identity must be a symbol');
      if (descriptors.has(id)) fail('descriptor already bound');
      const actual = record(mappingDescriptor(id), 'mapping descriptor');
      if (descriptorRecords.has(actual) || assigned.has(actual)) fail('mapping descriptor aliases another actual owner');
      const binding = copy<SourceActorAttributeDescriptorBinding>(initial, ['field44', 'field48', 'field4c', 'field50', 'field54']);
      const joint = Object.getOwnPropertyDescriptor(initial, 'byte10'); check();
      if (joint !== undefined)
        binding.byte10 = integer(read(initial, 'byte10'), 255, 'byte10');
      Object.seal(binding);
      descriptors.set(id, {actual, binding}); descriptorRecords.add(actual);
    });},
    getDescriptorBinding(id: symbol) {return descriptorEntry(id).binding;},
    createParameterDescriptor(initial: Readonly<Partial<SourceActorAttributeParameterDescriptor>>): symbol {return guard(() => {
      const binding = copy<SourceActorAttributeParameterDescriptor>(initial, ['field74', 'field78', 'field7c', 'field184', 'field188', 'field18c']);
      for (const key of ['field04', 'field08'] as const) {
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) {
          const value = read(initial, key);
          if (typeof value !== 'number' || !Number.isInteger(value) || value < -32768 || value > 32767)
            fail(`${key}: signed-short integer required`);
          binding[key] = value === 0 ? 0 : value;
        }
      }
      if (Object.getOwnPropertyDescriptor(initial, 'byteA3') !== undefined)
        binding.byteA3 = integer(read(initial, 'byteA3'), 255, 'byteA3');
      Object.seal(binding);
      const id = Symbol('owned actor parameter4ac'); parameters.set(id, binding); return id;
    });},
    getParameterDescriptor(id: symbol) {return parameterEntry(id);},
    refreshActor(id: symbol): void {guard(() => {
      const actor = actorEntry(id), actual = actor.actual, binding = actor.binding;
      if (worldActor(id) !== actual) fail('world owner changed its actual record');
      // 55de0–55de8: control bit6 always precedes every later source read.
      write(binding, 'byte87', (integer(read(actual, 'controlWord'), 0xffffffff, 'controlWord') >>> 6) & 1);
      if (mappingActor(id) !== actor.mapping) fail('mapping owner changed its actual record');
      const selected = pointer(read(actor.mapping, 'descriptor4b0'), 'descriptor4b0');
      const scale = f(actual, 'modelScale'); // Retained even if later stores fail.
      const descriptor = descriptorEntry(selected);
      if (mappingDescriptor(selected!) !== descriptor.actual) fail('mapping descriptor owner changed its actual record');
      const product = (key: keyof SourceActorAttributeDescriptorBinding): number => float(Math.fround(f(descriptor.binding, key) * scale), 'fmuls result');
      write(actual, 'hoverOffset668', product('field4c'));
      // Resolve/validate existing movement storage only at its first store.
      const height = product('field44'); write(movement(id, actor), 'field66c', height);
      write(actor.movement, 'field670', product('field48'));
      write(binding, 'field674', product('field54'));
      write(binding, 'field770', product('field50'));
      // Three distinct lwz 4ac operations, no retained pointer across copies.
      write(actual, 'maxHSpeed', f(parameterEntry(pointer(read(binding, 'parameter4ac'), 'parameter4ac')), 'field74'));
      write(actual, 'maxRise', f(parameterEntry(pointer(read(binding, 'parameter4ac'), 'parameter4ac')), 'field78'));
      write(actual, 'maxFall', f(parameterEntry(pointer(read(binding, 'parameter4ac'), 'parameter4ac')), 'field7c'));
      for (let index = 0; index < ROW_SOURCES.length; index++) {
        const source = ROW_SOURCES[index]!;
        let value: number;
        if (typeof source === 'number') {
          if (read(actual, 'actionSpeedRows') !== actor.rows || read(actor.rows, 'length') !== 3)
            fail('actual actionSpeedRows owner changed');
          value = f(actor.rows, String(source));
        } else value = f(binding, source);
        write(binding, ROW_DESTINATIONS[index]!, value);
      }
      // 55ed0: one real movement call, no matrix/animation/history refresh.
      movement(id, actor);
      if (updateMovement(id) !== undefined) fail('movement effect must complete synchronously and return undefined');
    });},
  });
}
