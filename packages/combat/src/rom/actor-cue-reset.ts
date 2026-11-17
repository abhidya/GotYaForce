/** Source8006a750/8006a6fc over explicitly exclusive offline owners.
 * Actual table/cues/states and fbPhase540 stay live. Legacy fbPhaseSlots
 * conflates540..543 despite its old544 annotation and must be absent, as must
 * legacy shotByte1db3 and animState. Source dispatch marker1db3 is the sole
 * byte owner. Actual onLand754 is the sole callback pointer; stw0 becomes null,
 * never a timer or callback invocation. Only missing bytes get binding cells.
 * Binding never deletes or migrates legacy fields. This is not live dispatch.
 *
 * Cue input is unsigned32 register bits. slwi1 wraps before indexing, then stb
 * writes low8 bits. Only addressed elements in an explicit non-shared Int8Array
 * are admitted. No missing-table/entry false success,48-entry clamp or early
 * byte truncation. Sentinelff returns0 without stores; success returns1 after
 * source-ordered descending phase clears. Reached failures retain all prior
 * effects. Non-proxy own records and stable synchronous exclusive owners are
 * bounds; explicit table bytes do not establish retail table hydration.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorAnimationDispatchRuntime, SourceActorAnimationDispatchBinding} from './actor-animation-dispatch.js';
export interface SourceActorCueResetBinding {
  byte541: number; byte542: number; byte543: number;
  byte544: number; byte545: number; byte546: number; byte547: number;
  byte588: number; byte7ce: number; byte7cf: number;
}
export interface SourceActorCueResetSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getMappingActor'>;
  dispatch: Pick<SourceActorAnimationDispatchRuntime, 'getSourceActor' | 'getActorBinding'>;
}
export interface SourceActorCueResetRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorCueResetBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getMappingActor(identity: symbol): object;
  getDispatchBinding(identity: symbol): SourceActorAnimationDispatchBinding;
  getActorBinding(identity: symbol): Partial<SourceActorCueResetBinding>;
  dispatchUpperBodyCue(identity: symbol, cue: number): 0 | 1;
  dispatchFullBodyCue(identity: symbol, cue: number): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
export function isSourceActorCueResetRuntime(value: unknown): value is SourceActorCueResetRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-cue-reset] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
const typed = Object.getPrototypeOf(Int8Array.prototype) as object;
const arrayLength = Object.getOwnPropertyDescriptor(typed, 'length')!.get!;
const arrayBuffer = Object.getOwnPropertyDescriptor(typed, 'buffer')!.get!;
export function createSourceActorCueResetRuntime(sources: SourceActorCueResetSources): SourceActorCueResetRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (r: unknown, key: string): unknown => {const result = own(r, key); check(); return result;};
  const write = (r: unknown, key: string, value: number | null): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const capture = (name: keyof SourceActorCueResetSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(fn, receiver, [id]); check(); return value;};
  };
  const worldActual = capture('world', 'getActualActor'), worldMapping = capture('world', 'getMappingActor');
  const dispatchMapping = capture('dispatch', 'getSourceActor'), dispatchBinding = capture('dispatch', 'getActorBinding');
  const b = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const s = (r: unknown, key: string): number => integer(read(r, key), -128, 127, key);
  const exclusive = (actual: object): void => {
    for (const key of ['fbPhaseSlots', 'shotByte1db3', 'animState']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing legacy source owner present`);
      check();
    }
  };
  interface Entry {actual: RomActor; mapping: object; dispatch: SourceActorAnimationDispatchBinding; binding: Partial<SourceActorCueResetBinding>}
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned cue actor'); return value;};
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const dispatchCue = (id: symbol, cue: number, upper: boolean): 0 | 1 => guard(() => {
    const actor = entry(id), actual = actor.actual, binding = actor.binding;
    stable(worldActual(id), actual, 'world actor'); stable(worldMapping(id), actor.mapping, 'world mapping');
    stable(dispatchMapping(id), actor.mapping, 'dispatch mapping'); stable(dispatchBinding(id), actor.dispatch, 'dispatch binding');
    exclusive(actual);
    const indexBits = integer(cue, 0, 0xffffffff, 'cue register bits');
    const table = read(actual, 'cueTable');
    if (!ArrayBuffer.isView(table) || !(table instanceof Int8Array) || !(Reflect.apply(arrayBuffer, table, []) instanceof ArrayBuffer))
      fail('cueTable: actual non-shared Int8Array required');
    const length = Reflect.apply(arrayLength, table, []) as number;
    const offset = (((indexBits << 1) >>> 0) + (upper ? 1 : 0)) >>> 0;
    if (offset >= length) fail('cueTable: indexed byte outside explicitly owned storage');
    const selected = s(table, String(offset));
    if (selected === -1) return 0;
    if (upper) {
      write(binding, 'byte7ce', b(actual, 'ubCue'));
      write(actual, 'ubCue', indexBits & 255);
      write(actual, 'prevUbState', s(actual, 'ubState'));
      write(actual, 'ubState', selected);
      for (const key of ['byte547', 'byte546', 'byte545', 'byte544', 'byte588']) write(binding, key, 0);
      write(actual, 'onLand754', null);
      write(actor.dispatch, 'marker1db3', 0);
    } else {
      write(binding, 'byte7cf', b(actual, 'fbCue'));
      write(actual, 'fbCue', indexBits & 255);
      write(actual, 'prevFbState', s(actual, 'fbState'));
      write(actual, 'fbState', selected);
      for (const key of ['byte543', 'byte542', 'byte541']) write(binding, key, 0);
      write(actual, 'fbPhase', 0);
    }
    return 1;
  });
  const runtime: SourceActorCueResetRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActual(id), 'actual actor') as RomActor; exclusive(actual);
      if (claimed.has(actual)) fail('actual actor already claimed by a source cue runtime');
      const mapping = record(worldMapping(id), 'world mapping'); stable(dispatchMapping(id), mapping, 'dispatch mapping');
      const dispatch = record(dispatchBinding(id), 'dispatch binding') as SourceActorAnimationDispatchBinding;
      const records = [actual, mapping, dispatch];
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value))) fail('source owner alias');
      record(initial, 'initial cue binding');
      const binding: Partial<SourceActorCueResetBinding> = {};
      for (const key of ['byte541','byte542','byte543','byte544','byte545','byte546','byte547','byte588','byte7ce','byte7cf'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = b(initial, key);
      check(); actors.set(id, {actual, mapping, dispatch, binding: Object.seal(binding)});
      records.forEach(value => assigned.add(value)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getMappingActor(id) {return entry(id).mapping;},
    getDispatchBinding(id) {return entry(id).dispatch;},
    getActorBinding(id) {return entry(id).binding;},
    dispatchUpperBodyCue(id, cue) {return dispatchCue(id, cue, true);},
    dispatchFullBodyCue(id, cue) {return dispatchCue(id, cue, false);},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
