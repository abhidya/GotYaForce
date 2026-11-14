/** Bounded actual8005a190, authenticated8005a190..8005a298 and
 * chunk_0007.c:2730–2768, with genuine leaves8006ab9c/8006abb8 from
 * chunk_0009.c:1089–1111. Gated/countdown calls return the source's literal0.
 * Without an explicit genuine ready runtime, transitions retain their historical
 * refusals BEFORE transition effects. With one,8006a980 may complete and the
 * caller writes489=4,19=3 then returns1.8006aab0 executes its leaf, then reads
 * signed actual team before refusing80176ec0. No callback manufactures success.
 * A reached transition marks the actual actor as incomplete until the WHOLE
 * supported caller path completes. Later calls refuse before source reads, even if its gates or
 * counters change. This host admission guard is NOT an original source write
 * or a recovery mechanism; it prevents a partial call from becoming success.
 *
 * The same actual controlWord, world4a1/4a0/48a and status6fc owners remain
 * live. Only absent490/49a/49c get explicit copied, sealed partial storage.
 * Raw bytes and decoded signed16 shorts are explicit admission bounds.
 * Captured methods retain receivers; stable synchronous non-proxy own-data
 * owners are required. Reads and writable-destination checks follow reached
 * instructions, and caught mutation reentry poisons the outer call. Earlier
 * stores survive refusal. No defaults, hydration, rollback or tick activation.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding} from './actor-status-timers.js';
import {hasIncompleteSourceActorReadyTransition, isSourceActorReadyTransitionsRuntime, type SourceActorReadyTransitionsRuntime, type SourceActorReadyTransitionsBinding} from './actor-ready-transitions.js';

export interface SourceActorControlLifecycleBinding {byte490: number; short49a: number; short49c: number}
export interface SourceActorControlLifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getWorldBinding'>;
}
export interface SourceActorControlLifecycleRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorControlLifecycleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getActorBinding(identity: symbol): Partial<SourceActorControlLifecycleBinding>;
  /** Once-only genuine ready helper; does not activate a source tick. */
  bindReadyRuntime(ready: SourceActorReadyTransitionsRuntime): void;
  getReadyRuntime(): SourceActorReadyTransitionsRuntime | undefined;
  /** 1 only after the complete admitted8006a980 branch and caller stores. */
  updateActor(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
const incompleteTransitions = new WeakSet<object>();
export function isSourceActorControlLifecycleRuntime(value: unknown): value is SourceActorControlLifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-control-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
export function createSourceActorControlLifecycleRuntime(sources: SourceActorControlLifecycleSources): SourceActorControlLifecycleRuntime {
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
  const capture = (name: keyof SourceActorControlLifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusWorld = capture('status', 'getWorldBinding');
  const byte = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const short = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const word = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const noShadowOwners = (actual: object): void => {
    for (const key of ['byte490', 'short49a', 'field49a', 'short49c', 'field49c',
      'mode4a1', 'byte4a1', 'mode4a0', 'byte4a0', 'flags48a', 'byte48a', 'byte6fc', 'flags5e0', 'word5e0']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined)
        fail(`${key}: competing control-lifecycle storage on actual actor`);
      check();
    }
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; status: Partial<SourceActorStatusTimersBinding>;
    binding: Partial<SourceActorControlLifecycleBinding>;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned control-lifecycle actor'); return value;
  };
  interface Ready {runtime: SourceActorReadyTransitionsRuntime;
    complete: SourceActorReadyTransitionsRuntime['assertActorComplete'];
    actor: SourceActorReadyTransitionsRuntime['getActualActor'];
    world: SourceActorReadyTransitionsRuntime['getWorldBinding'];
    status: SourceActorReadyTransitionsRuntime['getStatusBinding'];
    control: SourceActorReadyTransitionsRuntime['getControlBinding'];
    binding: SourceActorReadyTransitionsRuntime['getActorBinding'];
    transition490: SourceActorReadyTransitionsRuntime['transition490'];
    transition48a: SourceActorReadyTransitionsRuntime['transition48a']}
  let ready: Ready | undefined;
  const readyBinding = (id: symbol, actor: Entry): Partial<SourceActorReadyTransitionsBinding> => {
    const source = ready!;
    const invoke = (method: Function): unknown => {const result = Reflect.apply(method, source.runtime, [id]); check(); return result;};
    stable(invoke(source.actor), actor.actual, 'ready actor');
    stable(invoke(source.world), actor.world, 'ready world binding');
    stable(invoke(source.status), actor.status, 'ready status binding');
    stable(invoke(source.control), actor.binding, 'ready control binding');
    return record(invoke(source.binding), 'ready binding') as Partial<SourceActorReadyTransitionsBinding>;
  };
  const invokeReady = (id: symbol, actor: Entry, branch490: boolean): Partial<SourceActorReadyTransitionsBinding> => {
    const source = ready!, binding = readyBinding(id, actor);
    const result = Reflect.apply(branch490 ? source.transition490 : source.transition48a, source.runtime, [id]); check();
    if (result !== undefined) fail('genuine ready helper returned asynchronously or unexpectedly');
    stable(readyBinding(id, actor), binding, 'ready binding');
    return binding;
  };
  // Both seven-instruction leaves return1 iff the masked actual5e0 word is0.
  // In particular bits0/1 block6ab9c but do NOT block6abb8.
  const ready8006ab9c = (actual: RomActor): boolean => (word(actual, 'controlWord') & 0x91001003) === 0;
  const ready8006abb8 = (actual: RomActor): boolean => (word(actual, 'controlWord') & 0x91001000) === 0;
  const runtime: SourceActorControlLifecycleRuntime = {
    bindReadyRuntime(value) {guard(() => {
      if (ready !== undefined) fail('ready runtime already bound');
      if (!isSourceActorReadyTransitionsRuntime(value)) fail('ready transitions require genuine source runtime, not callback effects');
      const owner = read(value, 'getControlRuntime');
      if (typeof owner !== 'function') fail('ready control runtime method required');
      const control = Reflect.apply(owner, value, []); check(); stable(control, runtime, 'ready control runtime');
      const method = (key: keyof SourceActorReadyTransitionsRuntime): Function => {
        const fn = read(value, key); if (typeof fn !== 'function') fail(`${key}: ready source method required`); return fn;
      };
      const candidate: Ready = {runtime: value,
        complete: method('assertActorComplete') as SourceActorReadyTransitionsRuntime['assertActorComplete'],
        actor: method('getActualActor') as SourceActorReadyTransitionsRuntime['getActualActor'],
        world: method('getWorldBinding') as SourceActorReadyTransitionsRuntime['getWorldBinding'],
        status: method('getStatusBinding') as SourceActorReadyTransitionsRuntime['getStatusBinding'],
        control: method('getControlBinding') as SourceActorReadyTransitionsRuntime['getControlBinding'],
        binding: method('getActorBinding') as SourceActorReadyTransitionsRuntime['getActorBinding'],
        transition490: method('transition490') as SourceActorReadyTransitionsRuntime['transition490'],
        transition48a: method('transition48a') as SourceActorReadyTransitionsRuntime['transition48a']};
      // Publish only after every already-bound actor agrees. Failed binding can retry.
      for (const [id, actor] of actors) {
        for (const [fn, expected, where] of [[candidate.actor, actor.actual, 'ready actor'],
          [candidate.world, actor.world, 'ready world binding'], [candidate.status, actor.status, 'ready status binding'],
          [candidate.control, actor.binding, 'ready control binding']] as const) {
          const result = Reflect.apply(fn, value, [id]); check(); stable(result, expected, where);
        }
        const binding = Reflect.apply(candidate.binding, value, [id]); check(); record(binding, 'ready binding');
      }
      check(); ready = candidate;
    });},
    getReadyRuntime() {return ready?.runtime;},
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source control-lifecycle runtime');
      noShadowOwners(actual); stable(statusActor(id), actual, 'status actor');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const status = record(statusBinding(id), 'status binding') as Partial<SourceActorStatusTimersBinding>;
      stable(statusWorld(id), world, 'status world binding');
      const owners = [actual, world, status];
      if (new Set(owners).size !== owners.length || owners.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual actor/world/status required');
      record(initial, 'initial control-lifecycle binding');
      const binding: Partial<SourceActorControlLifecycleBinding> = {};
      if (Object.getOwnPropertyDescriptor(initial, 'byte490') !== undefined) binding.byte490 = byte(initial, 'byte490');
      for (const key of ['short49a', 'short49c'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = short(initial, key);
      check(); actors.set(id, {actual, world, status, binding: Object.seal(binding)});
      [...owners, binding].forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;},
    getActorBinding(id) {return entry(id).binding;},
    updateActor(id) {return guard(() => {
      const {actual, world, status, binding} = entry(id);
      if (incompleteTransitions.has(actual)) fail('actual actor has a known incomplete control transition; source continuation is unsupported');
      if (hasIncompleteSourceActorReadyTransition(actual))
        fail('actual actor has a known incomplete ready transition; source continuation is unsupported');
      // A standalone helper failure must not turn into a gated returned0 here,
      // including when this genuine ready runtime was attached after that failure.
      if (ready !== undefined) {
        const result = Reflect.apply(ready.complete, ready.runtime, [id]); check();
        if (result !== undefined) fail('genuine ready completeness assertion returned unexpectedly');
      }
      // Owner admission does not load or validate any source scalar early.
      stable(worldActor(id), actual, 'world actor'); stable(statusActor(id), actual, 'status actor');
      stable(worldBinding(id), world, 'world binding'); stable(statusBinding(id), status, 'status binding');
      stable(statusWorld(id), world, 'status world binding'); noShadowOwners(actual);
      // Signed-byte zero comparisons equal raw-byte zero comparisons.
      if (byte(world, 'mode4a1') !== 0) return 0;
      if (byte(world, 'mode4a0') !== 0) return 0;
      if (byte(status, 'byte6fc') !== 0) return 0;
      if (byte(world, 'flags48a') === 2) {
        const count = short(binding, 'short49c');
        if (count > 0) {write(binding, 'short49c', count - 1); return 0;}
        if (!ready8006ab9c(actual)) return 0;
        incompleteTransitions.add(actual);
        if (ready === undefined) fail('8005a204 reached unsupported source call 8006aab0(actor); later80176ec0 and returned1 have not executed');
        invokeReady(id, entry(id), false);
        const team = byte(actual, 'team') << 24 >> 24; // lbz@8005a208, extsb@8005a214.
        fail(`8005a218 reached unsupported source call 80176ec0(actor, team=${team}, 0); returned1 has not executed`);
      }
      if (byte(binding, 'byte490') !== 2) return 0;
      const count = short(binding, 'short49a');
      if (count <= 0) return 0;
      const next = (count - 1) << 16 >> 16; // extsh.@8005a240 precedes sth@8005a244.
      write(binding, 'short49a', next);
      if (next > 0) return 0;
      if (ready8006abb8(actual)) {
        incompleteTransitions.add(actual);
        if (ready === undefined) fail('8005a25c reached unsupported source call 8006a980(actor); later byte489=4/byte19=3 and returned1 have not executed');
        const destination = invokeReady(id, entry(id), true);
        write(destination, 'byte489', 4); // stb@8005a268.
        write(destination, 'byte19', 3); // stb@8005a270, after li returnr3=1.
        check(); incompleteTransitions.delete(actual);
        return 1;
      }
      write(binding, 'short49a', 1); // Only the blocked leaf result reaches8005a27c.
      return 0;
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
