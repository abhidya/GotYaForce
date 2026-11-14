/** Bounded control-zero continuation of actual80059068. Evidence:
 * actor-normal-lifecycle-evidence-2026-11-14.md and its fixed archived reader.
 * Fixed authenticated
 * cue cells802d3300/802d3324 resolve to8005913c/80059138. Cue9 is an independent
 * return-only body. Optional genuine cue0 continues movement3's two real cue
 * resets or the ordered terrain helper, retaining the next699d8 refusal.
 * Cue0 and normal share status attributes, cue records and mapping identity.
 * Its additional history/position owners are retained, with no copied state.
 * Actual4c8 is separate explicit source
 * storage: independently authenticated8006f950 and8018cfe4 return. The source
 * constructors prove distinct Double Ninja/G RED pointer producers, not live
 * hydration. No target is inferred from a host family name or rootAction.
 * No generic callback, family handler or source-call omission is admitted.
 *
 * Genuine59f5c supports its control mask/57a merge, real6a6fc cue synchronization
 * and move661==10 return. Optional genuine rotation damping continues the
 * active correction body on the same mapping clock, descriptor registry and
 * world rows. Without it,80059fac remains the historical refusal, including
 * a sentinel list. Partial damping stores permanently block later bypasses.
 * Genuine5a144 decrements signed6bc before reaching nonnull4dc's unsupported
 * indirect call. Source reads and destination checks are lazy and ordered;
 * failures retain all prior effects. This is not a full frame or hydration.
 *
 * Existing actual controlWord/cues/stateFlagA/stateFlagB and movement.byte661
 * remain sole owners. Only absent4c8/4dc/6bc/1d9 get explicit partial storage.
 * Stable synchronous non-proxy own-data owners are host admission bounds.
 * Methods and receivers are captured, brands immutable, claims permanent,
 * and caught mutation reentry poisons the containing operation. A reached
 * cue0 call, cue reset or countdown expiry must finish before this actual actor can
 * continue; host-only incomplete markers cannot be cleared by editing cues
 * or counters. They are admission bounds, not additional source stores.
 */
import type {RomActor} from './actor.js';
import {isSourceActorCue0LifecycleRuntime, hasIncompleteSourceActorCue0Lifecycle,
  type SourceActorCue0LifecycleRuntime} from './actor-cue0-lifecycle.js';
import {isSourceActorRotationDampingRuntime, hasIncompleteSourceActorRotationDamping,
  type SourceActorRotationDampingRuntime} from './actor-rotation-damping.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorMovementFollowupRuntime, SourceActorMovementFollowupBinding} from './actor-movement-followup.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding} from './actor-status-timers.js';
import type {SourceActorAnimationDispatchBinding} from './actor-animation-dispatch.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime,
  type SourceActorCueResetBinding} from './actor-cue-reset.js';

export interface SourceActorNormalLifecycleBinding {
  /** Explicit decoded source addresses, not host functions. Null is address0. */
  callback4c8: number | null;
  callback4dc: number | null;
  short6bc: number;
  byte1d9: number;
}
export interface SourceActorNormalLifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'> &
    Partial<Pick<SourceActorWorldMatrixRuntime, 'getStorage'>>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getWorldBinding' |
    'getMappingActor' | 'getMovementBinding'> & Partial<Pick<SourceActorStatusTimersRuntime, 'getAttributeBinding'>>;
  /** Missing leaves6a6fc unsupported only when a signed cue mismatch reaches it. */
  cues?: SourceActorCueResetRuntime;
  /** Genuine rotation body, absent retains the historical59fac refusal. */
  rotation?: SourceActorRotationDampingRuntime;
  /** Genuine cue0 body and its ordered terrain call; absent retains target refusal. */
  cue0?: SourceActorCue0LifecycleRuntime;
}
export interface SourceActorNormalLifecycleRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorNormalLifecycleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): object;
  getMovementBinding(identity: symbol): SourceActorMovementFollowupBinding;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getActorBinding(identity: symbol): Partial<SourceActorNormalLifecycleBinding>;
  getCueRuntime(): SourceActorCueResetRuntime | undefined;
  getRotationRuntime(): SourceActorRotationDampingRuntime | undefined;
  getCue0Runtime(): SourceActorCue0LifecycleRuntime | undefined;
  getCueBinding(identity: symbol): Partial<SourceActorCueResetBinding> | undefined;
  getDispatchBinding(identity: symbol): SourceActorAnimationDispatchBinding | undefined;
  /** Host-only incomplete-call assertion; performs no source scalar reads. */
  assertActorComplete(identity: symbol): void;
  /** Direct bounded leaf/helper calls, not substitutes for the complete sequence. */
  dispatchCue(identity: symbol): void;
  updateCueState(identity: symbol): void;
  updateCountdown(identity: symbol): void;
  /** Executes cue dispatch, actual4c8 dispatch,59f5c,5a144, in source order. */
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
const incompleteCountdowns = new WeakSet<object>(), incompleteCueSyncs = new WeakSet<object>();
export function hasIncompleteSourceActorNormalCountdown(actual: object): boolean {
  return incompleteCountdowns.has(actual);
}
export function hasIncompleteSourceActorNormalCueSync(actual: object): boolean {
  return incompleteCueSyncs.has(actual);
}
export function isSourceActorNormalLifecycleRuntime(value: unknown): value is SourceActorNormalLifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function isSourceActorNormalLifecycleClaimedActor(value: unknown): boolean {
  return value !== null && typeof value === 'object' && claimedActors.has(value);
}
/** Separately authenticated one-instruction leaves. Neither examines its actor. */
export function sourceActorNormalReturn80059138(_actual: unknown): void {}
export function sourceActorNormalReturn8006f950(_actual: unknown): void {}
export function sourceActorNormalReturn8018cfe4(_actual: unknown): void {}
function fail(reason: string): never {
  throw Error(`[actor-normal-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, key: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${key}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
export function createSourceActorNormalLifecycleRuntime(sources: SourceActorNormalLifecycleSources): SourceActorNormalLifecycleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const write = (owner: unknown, key: string, next: number): void => {
    own(owner, key, true); check(); (owner as Record<string, unknown>)[key] = next; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorNormalLifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const movementActor = capture('movement', 'getActualActor'), movementBinding = capture('movement', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusWorld = capture('status', 'getWorldBinding'), statusMapping = capture('status', 'getMappingActor');
  const statusMovement = capture('status', 'getMovementBinding');
  const cueRuntime = Object.getOwnPropertyDescriptor(sources, 'cues') === undefined ? undefined : read(sources, 'cues');
  if (cueRuntime !== undefined && !isSourceActorCueResetRuntime(cueRuntime)) fail('cues requires genuine source runtime');
  const cueActor = cueRuntime === undefined ? undefined : capture('cues', 'getActualActor');
  const cueMapping = cueRuntime === undefined ? undefined : capture('cues', 'getMappingActor');
  const cueBinding = cueRuntime === undefined ? undefined : capture('cues', 'getActorBinding');
  const cueDispatch = cueRuntime === undefined ? undefined : capture('cues', 'getDispatchBinding');
  const fullCue = cueRuntime === undefined ? undefined : capture('cues', 'dispatchFullBodyCue');
  const rotationOption = Object.getOwnPropertyDescriptor(sources, 'rotation');
  const rotation = rotationOption === undefined ? undefined : read(sources, 'rotation');
  if (rotationOption !== undefined && !isSourceActorRotationDampingRuntime(rotation))
    fail('rotation requires genuine source runtime');
  const rotationActor = rotation === undefined ? undefined : capture('rotation', 'getActualActor');
  const rotationWorld = rotation === undefined ? undefined : capture('rotation', 'getWorldBinding');
  const rotationMapping = rotation === undefined ? undefined : capture('rotation', 'getMappingActor');
  const rotationStorage = rotation === undefined ? undefined : capture('rotation', 'getWorldStorage');
  const worldStorage = rotation === undefined ? undefined : capture('world', 'getStorage');
  const rotationOwners = rotation === undefined ? undefined : capture('rotation', 'getStorageOwners');
  const rotationDescriptors = rotation === undefined ? undefined : capture('rotation', 'getKnownDescriptorRecords');
  const dampRotation = rotation === undefined ? undefined : capture('rotation', 'updateActor');
  const cue0Option = Object.getOwnPropertyDescriptor(sources, 'cue0');
  const cue0 = cue0Option === undefined ? undefined : read(sources, 'cue0');
  if (cue0Option !== undefined && !isSourceActorCue0LifecycleRuntime(cue0))
    fail('cue0 requires genuine source runtime');
  const cue0Actor = cue0 === undefined ? undefined : capture('cue0', 'getActualActor');
  const cue0World = cue0 === undefined ? undefined : capture('cue0', 'getWorldBinding');
  const cue0Mapping = cue0 === undefined ? undefined : capture('cue0', 'getMappingActor');
  const cue0Movement = cue0 === undefined ? undefined : capture('cue0', 'getMovementBinding');
  const cue0Attribute = cue0 === undefined ? undefined : capture('cue0', 'getAttributeBinding');
  const statusAttribute = cue0 === undefined ? undefined : capture('status', 'getAttributeBinding');
  const cue0Cues = cue0 === undefined ? undefined : capture('cue0', 'getCueRuntime');
  const cue0CueBinding = cue0 === undefined ? undefined : capture('cue0', 'getCueBinding');
  const cue0Dispatch = cue0 === undefined ? undefined : capture('cue0', 'getDispatchBinding');
  const cue0Owners = cue0 === undefined ? undefined : capture('cue0', 'getSourceOwners');
  const cue0Terrain = cue0 === undefined ? undefined : capture('cue0', 'getTerrainGlobals');
  const dispatchCue0 = cue0 === undefined ? undefined : capture('cue0', 'dispatchCue0');
  const ownerList = (value: unknown, where: string): object[] => {
    if (!Array.isArray(value)) fail(`${where}: actual owner array required`);
    return value.map(owner => record(owner, where));
  };
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 0, 255, key);
  const signedByte = (owner: unknown, key: string): number => byte(owner, key) << 24 >> 24;
  const short = (owner: unknown, key: string): number => integer(read(owner, key), -32768, 32767, key);
  const address = (owner: unknown, key: string): number | null => {
    const value = read(owner, key);
    return value === null ? null : integer(value, 0, 0xffffffff, key);
  };
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; mapping: object;
    movement: SourceActorMovementFollowupBinding;
    status: Partial<SourceActorStatusTimersBinding>;
    cue: Partial<SourceActorCueResetBinding> | undefined;
    dispatch: SourceActorAnimationDispatchBinding | undefined;
    binding: Partial<SourceActorNormalLifecycleBinding>;
    rotationStorage?: object; rotationOwners?: readonly object[];
    cue0Owners?: readonly object[]; cue0Terrain?: object; cue0Attribute?: object;
  }
  const owners = (e: Entry): object[] => [e.actual, e.world, e.mapping, e.movement, e.status, e.binding,
    ...(e.cue === undefined ? [] : [e.cue]), ...(e.dispatch === undefined ? [] : [e.dispatch]), ...(e.rotationOwners ?? []), ...(e.cue0Owners ?? [])];
  const noShadows = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['controlWord', e.actual], ['ubCue', e.actual], ['fbCue', e.actual],
      ['stateFlagA', e.actual], ['stateFlagB', e.actual], ['byte661', e.movement],
      ['callback4c8', e.binding], ['callback4dc', e.binding], ['short6bc', e.binding], ['byte1d9', e.binding],
    ]);
    const aliases = ['byte5e4', 'byte5e5', 'word5e0', 'flags5e0', 'field5e0', 'field4c8', 'pointer4c8',
      'field4dc', 'pointer4dc', 'field6bc', 'timer6bc', 'countdown6bc', 'metadata1d9', 'flags1d9',
      'field1d9', 'hitReact', 'flyingBounce1d9', 'aerialXDamaged',
      'flags57a', 'flags57b', 'byte57a', 'byte57b', 'field57a', 'field57b', 'field661', 'move661'];
    for (const owner of owners(e)) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing normal-lifecycle storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing normal-lifecycle storage alias`);
        check();
      }
    }
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(movementActor(id), e.actual, 'movement actor'); stable(movementBinding(id), e.movement, 'movement binding');
    stable(statusActor(id), e.actual, 'status actor'); stable(statusBinding(id), e.status, 'status binding');
    stable(statusWorld(id), e.world, 'status world'); stable(statusMapping(id), e.mapping, 'status mapping');
    stable(statusMovement(id), e.movement, 'status movement');
    if (cueActor) {
      stable(cueActor(id), e.actual, 'cue actor'); stable(cueMapping!(id), e.mapping, 'cue mapping');
      stable(cueBinding!(id), e.cue!, 'cue binding'); stable(cueDispatch!(id), e.dispatch!, 'cue dispatch');
    }
    if (rotationActor) {
      stable(rotationActor(id), e.actual, 'rotation actor');
      stable(rotationWorld!(id), e.world, 'rotation world');
      stable(rotationMapping!(id), e.mapping, 'rotation mapping');
      stable(rotationStorage!(id), e.rotationStorage!, 'rotation storage');
      stable(worldStorage!(id), e.rotationStorage!, 'rotation/world storage');
      const current = ownerList(rotationOwners!(id), 'rotation storage owners');
      if (current.length !== e.rotationOwners!.length || current.some((owner, i) => owner !== e.rotationOwners![i]))
        fail('rotation source storage owners changed');
      const known = ownerList(rotationDescriptors!(), 'known rotation descriptors');
      if (known.some(owner => owners(e).includes(owner))) fail('rotation descriptor aliases a normal source owner');
    }
    if (cue0Actor) {
      stable(cue0Actor(id), e.actual, 'cue0 actor'); stable(cue0World!(id), e.world, 'cue0 world');
      stable(cue0Mapping!(id), e.mapping, 'cue0 mapping'); stable(cue0Movement!(id), e.movement, 'cue0 movement');
      stable(cue0Attribute!(id), e.cue0Attribute!, 'cue0 attribute');
      stable(statusAttribute!(id), e.cue0Attribute!, 'cue0/status attribute');
      if (cue0Cues!() !== cueRuntime || cue0CueBinding!(id) !== e.cue || cue0Dispatch!(id) !== e.dispatch)
        fail('cue0/normal must share the same genuine cue runtime and records');
      stable(cue0Terrain!(), e.cue0Terrain!, 'cue0 terrain');
      const current = ownerList(cue0Owners!(id), 'cue0 source owners');
      if (current.length !== e.cue0Owners!.length || current.some((owner, i) => owner !== e.cue0Owners![i]))
        fail('cue0 source owners changed');
      if (owners(e).includes(e.cue0Terrain!)) fail('cue0 terrain aliases an actor source owner');
    }
    noShadows(e);
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const e = actors.get(id); if (!e) fail('unknown/non-owned normal-lifecycle actor'); return e;
  };
  const assertComplete = (actual: object): void => {
    if (hasIncompleteSourceActorCue0Lifecycle(actual))
      fail('actual actor has a known incomplete cue0 lifecycle; source continuation is unsupported');
    if (hasIncompleteSourceActorRotationDamping(actual))
      fail('actual actor has a known incomplete rotation damping; source continuation is unsupported');
    if (incompleteCueSyncs.has(actual))
      fail('actual actor has a known incomplete cue synchronization; source continuation is unsupported');
    if (incompleteCountdowns.has(actual))
      fail('actual actor has a known incomplete6bc expiry; source continuation is unsupported');
  };
  const dispatch = (id: symbol, e: Entry): void => {
    if (hasIncompleteSourceActorCue0Lifecycle(e.actual))
      fail('actual actor has a known incomplete cue0 lifecycle; source continuation is unsupported');
    const cue = signedByte(e.actual, 'ubCue');
    const cell = (0x802d3300 + (cue << 2)) >>> 0;
    if (cue === 9) {sourceActorNormalReturn80059138(e.actual); return;}
    if (cue === 0) {
      if (!dispatchCue0)
        fail('800590e8 reached unsupported actual cue target8005913c from authenticated table802d3300 entry802d3300');
      assertComplete(e.actual);
      if (dispatchCue0(id) !== undefined) fail('genuine cue0 returned asynchronously or unexpectedly');
      return;
    }
    fail(`800590e0 reached unsupported source table802d3300 entry ${cell.toString(16)} before indirect call800590e8`);
  };
  const callback = (e: Entry): void => {
    const target = address(e.binding, 'callback4c8');
    if (target === 0x8006f950) {sourceActorNormalReturn8006f950(e.actual); return;}
    if (target === 0x8018cfe4) {sourceActorNormalReturn8018cfe4(e.actual); return;}
    fail(`800590f8 reached unsupported actual4c8 target ${target === null || target === 0 ? 'null' : target.toString(16)} after load800590ec`);
  };
  const cueState = (id: symbol, e: Entry): void => {
    const control = integer(read(e.actual, 'controlWord'), 0, 0xffffffff, 'controlWord');
    if ((control & 0x81000003) !== 0) {
      if ((byte(e.binding, 'byte1d9') & 0xf0) !== 0) {
        const before = byte(e.actual, 'stateFlagA'), flags = byte(e.actual, 'stateFlagB');
        write(e.actual, 'stateFlagA', before | flags);
      }
      return;
    }
    const upper = signedByte(e.actual, 'ubCue'), full = signedByte(e.actual, 'fbCue');
    if (upper !== full) {
      if (!fullCue) fail('80059f9c reached unsupported source call8006a6fc');
      // The real callee stores fbCue before its later state/phase clears. If
      // it throws, a retry must not bypass those stores because the cues now
      // compare equal. Only a verified native return completes this call.
      incompleteCueSyncs.add(e.actual);
      const result = fullCue(id, upper >>> 0);
      if (result !== 0 && result !== 1) fail('genuine full-body cue returned asynchronously or unexpectedly');
      incompleteCueSyncs.delete(e.actual);
      // Source ignores the real callee result, including its sentinel0 return.
    }
    if (signedByte(e.movement, 'byte661') === 10) return;
    if (!dampRotation) fail('80059fac reached unsupported rotation damping before first source constant load');
    if (dampRotation(id) !== undefined) fail('genuine rotation damping returned asynchronously or unexpectedly');
  };
  const countdown = (e: Entry): void => {
    assertComplete(e.actual);
    const before = short(e.binding, 'short6bc');
    if (before <= 0) return;
    const remaining = before - 1;
    write(e.binding, 'short6bc', remaining);
    if (remaining > 0) return;
    // Host-only poison prevents a retained1->0 store from manufacturing a
    // later nonpositive success after missing, invalid or unimplemented4dc.
    incompleteCountdowns.add(e.actual);
    const target = address(e.binding, 'callback4dc');
    if (target === null || target === 0) {incompleteCountdowns.delete(e.actual); return;}
    fail(`8005a17c reached unsupported actual4dc target ${target.toString(16)} after6bc decrement`);
  };
  const runtime: SourceActorNormalLifecycleRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'actual actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source normal-lifecycle runtime');
      const e: Entry = {actual,
        world: record(worldBinding(id), 'world binding') as Entry['world'],
        mapping: record(worldMapping(id), 'world mapping'),
        movement: record(movementBinding(id), 'movement binding') as Entry['movement'],
        status: record(statusBinding(id), 'status binding') as Entry['status'],
        cue: cueBinding === undefined ? undefined : record(cueBinding(id), 'cue binding') as Entry['cue'],
        dispatch: cueDispatch === undefined ? undefined : record(cueDispatch(id), 'cue dispatch') as Entry['dispatch'], binding: {}};
      if (rotationStorage) {
        e.rotationStorage = record(rotationStorage(id), 'rotation storage');
        e.rotationOwners = ownerList(rotationOwners!(id), 'rotation storage owners');
      }
      if (cue0Owners) {
        e.cue0Owners = ownerList(cue0Owners(id), 'cue0 source owners');
        e.cue0Terrain = record(cue0Terrain!(), 'cue0 terrain');
        e.cue0Attribute = record(cue0Attribute!(id), 'cue0 attribute');
      }
      admit(id, e); const records = owners(e);
      if (new Set(records).size !== records.length || records.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual/world/mapping/movement/status/normal/cue/dispatch required');
      record(initial, 'initial normal binding'); noShadows({...e, binding: initial});
      for (const key of ['callback4c8', 'callback4dc'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) e.binding[key] = address(initial, key);
      if (Object.getOwnPropertyDescriptor(initial, 'short6bc') !== undefined) e.binding.short6bc = short(initial, 'short6bc');
      if (Object.getOwnPropertyDescriptor(initial, 'byte1d9') !== undefined) e.binding.byte1d9 = byte(initial, 'byte1d9');
      Object.seal(e.binding); check(); actors.set(id, e);
      records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getMovementBinding(id) {return entry(id).movement;},
    getStatusBinding(id) {return entry(id).status;},
    getActorBinding(id) {return entry(id).binding;},
    getCueRuntime() {return cueRuntime as SourceActorCueResetRuntime | undefined;},
    getRotationRuntime() {return rotation as SourceActorRotationDampingRuntime | undefined;},
    getCue0Runtime() {return cue0 as SourceActorCue0LifecycleRuntime | undefined;},
    getCueBinding(id) {return entry(id).cue;},
    getDispatchBinding(id) {return entry(id).dispatch;},
    assertActorComplete(id) {assertComplete(entry(id).actual);},
    dispatchCue(id) {guard(() => {
      const e = entry(id);
      if (hasIncompleteSourceActorCue0Lifecycle(e.actual))
        fail('actual actor has a known incomplete cue0 lifecycle; source continuation is unsupported');
      admit(id, e); dispatch(id, e);
    });},
    updateCueState(id) {guard(() => {const e = entry(id); assertComplete(e.actual); admit(id, e); cueState(id, e);});},
    updateCountdown(id) {guard(() => {const e = entry(id); assertComplete(e.actual); admit(id, e); countdown(e);});},
    updateActor(id) {guard(() => {
      const e = entry(id);
      assertComplete(e.actual);
      admit(id, e);
      dispatch(id, e); callback(e); cueState(id, e); countdown(e);
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
