/** Bounded actual8005a298, chunk_0007.c:2772–2811 and authenticated
 * archived8005a298..8005a378 instructions (read_archived_ready_lifecycle_evidence.py).
 * Only the source early returns
 * and special-request byte73c=4 store are implemented. The zero4a1 path
 * loads actual raw slot3e4, sign-extends it, then refuses the source10514
 * call before inputEdge5d4. Nonzero4a1 refuses BEFORE loading pointer508:
 * Borg.targetLockState.activeTargetUid and matrix link4a4 do not yet share
 * an authenticated pointer identity domain. No comparison is fabricated.
 *
 * Actual statusWord5b4/housekeeping73f/slot/inputEdge5d4 and world.mode4a1
 * retain their canonical owners. Only absent7d2/73c have explicit copied
 * sealed partial cells. Wrong-owner cells and aliases are rejected by
 * descriptor presence at admission and calls, without reading their values.
 * No defaults, predicate callback, shadow pointers or tick activation.
 * Stable synchronous non-proxy own-data owners, raw bytes and unsigned32
 * words are admission bounds. Source scalar reads and writable checks are
 * reached lazily. Methods retain captured receivers; caught mutation reentry
 * poisons the enclosing call. Prior writes are never rolled back.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';

export interface SourceActorActionRequestBinding {byte7d2: number; byte73c: number}
export interface SourceActorActionRequestSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
}
export interface SourceActorActionRequestRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorActionRequestBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getActorBinding(identity: symbol): Partial<SourceActorActionRequestBinding>;
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorActionRequestRuntime(value: unknown): value is SourceActorActionRequestRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-action-request] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max)
    fail(`${where}: unsigned integer out of bounds`);
  return value === 0 ? 0 : value;
}
export function createSourceActorActionRequestRuntime(sources: SourceActorActionRequestSources): SourceActorActionRequestRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
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
  const receiver = read(sources, 'world');
  const capture = (key: string) => {
    const method = read(receiver, key);
    if (typeof method !== 'function') fail(`world.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const worldActor = capture('getActualActor'), worldBinding = capture('getActorBinding');
  const byte = (r: unknown, key: string): number => integer(read(r, key), 255, key);
  const word = (r: unknown, key: string): number => integer(read(r, key), 0xffffffff, key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {actual: RomActor; world: SourceActorWorldMatrixBinding; binding: Partial<SourceActorActionRequestBinding>}
  const noShadowOwners = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['statusWord5b4', e.actual], ['housekeeping73f', e.actual], ['slot', e.actual], ['inputEdge5d4', e.actual],
      ['mode4a1', e.world], ['byte7d2', e.binding], ['byte73c', e.binding],
    ]);
    const aliases = ['flags7d2', 'actionRequest73c', 'byte73f', 'word5b4', 'flags5b4',
      'word5d4', 'byte3e4', 'slot3e4', 'byte4a1'];
    for (const owner of [e.actual, e.world, e.binding]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing action-request storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing action-request storage alias`);
        check();
      }
    }
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned action-request actor'); return value;
  };
  const runtime: SourceActorActionRequestRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source action-request runtime');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const owners = [actual, world];
      if (new Set(owners).size !== owners.length || owners.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual actor/world required');
      record(initial, 'initial action-request binding');
      const binding: Partial<SourceActorActionRequestBinding> = {};
      const e: Entry = {actual, world, binding};
      noShadowOwners(e);
      // The copied input can seed only the absent cells, never a shadow of
      // a retained canonical owner or an alternative spelling of that cell.
      noShadowOwners({...e, binding: initial});
      for (const key of ['byte7d2', 'byte73c'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = byte(initial, key);
      Object.seal(binding); check(); actors.set(id, e);
      [...owners, binding].forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getActorBinding(id) {return entry(id).binding;},
    updateActor(id) {guard(() => {
      const e = entry(id), {actual, world, binding} = e;
      stable(worldActor(id), actual, 'world actor'); noShadowOwners(e);
      if ((byte(binding, 'byte7d2') & 3) === 1) {
        if ((word(actual, 'statusWord5b4') & 0x10) === 0) write(binding, 'byte73c', 4);
        return;
      }
      // lbz/extsb zero comparisons are equivalent over admitted raw bytes.
      if (byte(actual, 'housekeeping73f') !== 0) return;
      if (byte(binding, 'byte73c') !== 0) return;
      stable(worldBinding(id), world, 'world binding');
      if (byte(world, 'mode4a1') === 0) {
        const slot = byte(actual, 'slot') << 24 >> 24;
        fail(`8005a300 reached unsupported source call 80010514(slot=${slot}); inputEdge5d4 and later action stores have not executed`);
      }
      fail('8005a34c reached unsupported source pointer508 load; actual target508 and link4a4 identities are unreconciled, later4a4 load/comparison/store have not executed');
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
