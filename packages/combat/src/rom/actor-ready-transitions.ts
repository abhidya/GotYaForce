/** Bounded source8006a980/8006aab0, chunk_0009.c:999–1051 and fixed
 * archived read_archived_ready_lifecycle_evidence.py instruction evidence. The zero4a0 branch copies signed hp without
 * a clamp; nonzero4a0 stops at8006aa00->80066198 AFTER its prefix and signed
 * byte argument reloads. Nothing substitutes for that callee or its ratio math.
 *
 * Canonical stage.lifecycle18, world4a0/4a1/48a, status272, control490 and
 * borrowed Borg hp/maxHp/colorVariant remain live and exclusive. Only absent
 * offsets get explicit copied, sealed partial storage. hp is decoded signed16;
 * maxHp is existing rawu16 and is signextended by the source lha. Bytes remain
 * rawu8 until a source extsb. No defaults, hydration, callbacks or live tick.
 * Stable synchronous non-proxy own-data owners are admission bounds. Reached
 * failures retain prior stores and mark a host-only incomplete transition;
 * neither a retry nor changing a later gate can manufacture source success.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding, SourceActorStatusBorgOwner} from './actor-status-timers.js';
import {isSourceActorStageBoundsRuntime, type SourceActorStageBoundsRuntime, type SourceActorStageBoundsBinding} from './actor-stage-bounds.js';
import {isSourceActorControlLifecycleRuntime, type SourceActorControlLifecycleRuntime, type SourceActorControlLifecycleBinding} from './actor-control-lifecycle.js';

export interface SourceActorReadyTransitionsBinding {
  byte19: number; byte1a: number; byte1b: number; byte489: number;
  short48c: number; byte48e: number; byte48f: number;
  short494: number; short496: number; short49e: number; short3ea: number; byte3ef: number;
}
export interface SourceActorReadyTransitionsSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getWorldBinding' | 'getActualBorg'>;
  stageBounds: SourceActorStageBoundsRuntime;
  control: SourceActorControlLifecycleRuntime;
}
export interface SourceActorReadyTransitionsRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorReadyTransitionsBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getStageBinding(identity: symbol): Partial<SourceActorStageBoundsBinding>;
  getControlBinding(identity: symbol): Partial<SourceActorControlLifecycleBinding>;
  getActualBorg(identity: symbol): SourceActorStatusBorgOwner;
  getActorBinding(identity: symbol): Partial<SourceActorReadyTransitionsBinding>;
  getControlRuntime(): SourceActorControlLifecycleRuntime;
  getStageRuntime(): SourceActorStageBoundsRuntime;
  /** Host-only assertion: no source scalar reads, writes or recovery. */
  assertActorComplete(identity: symbol): void;
  transition490(identity: symbol): void;
  transition48a(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
const incompleteTransitions = new WeakSet<object>();
/** Shared host-only guard, including direct helpers not yet attached to control.
 * No source reads, mutation, recovery or publicly writable marker exists. */
export function hasIncompleteSourceActorReadyTransition(actual: object): boolean {
  return incompleteTransitions.has(actual);
}
export function isSourceActorReadyTransitionsRuntime(value: unknown): value is SourceActorReadyTransitionsRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-ready-transitions] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
const BYTES = ['byte19', 'byte1a', 'byte1b', 'byte489', 'byte48e', 'byte48f', 'byte3ef'] as const;
const SHORTS = ['short48c', 'short494', 'short496', 'short49e', 'short3ea'] as const;
export function createSourceActorReadyTransitionsRuntime(sources: SourceActorReadyTransitionsSources): SourceActorReadyTransitionsRuntime {
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
  const stageRuntime = read(sources, 'stageBounds'), controlRuntime = read(sources, 'control');
  if (!isSourceActorStageBoundsRuntime(stageRuntime)) fail('stageBounds requires genuine source runtime');
  if (!isSourceActorControlLifecycleRuntime(controlRuntime)) fail('control requires genuine source runtime');
  const capture = (name: keyof SourceActorReadyTransitionsSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusWorld = capture('status', 'getWorldBinding'), statusBorg = capture('status', 'getActualBorg');
  const stageActor = capture('stageBounds', 'getActualActor'), stageBinding = capture('stageBounds', 'getActorBinding');
  const stageWorld = capture('stageBounds', 'getWorldBinding'), stageStatus = capture('stageBounds', 'getStatusBinding');
  const controlActor = capture('control', 'getActualActor'), controlBinding = capture('control', 'getActorBinding');
  const controlWorld = capture('control', 'getWorldBinding'), controlStatus = capture('control', 'getStatusBinding');
  const byte = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const short = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const maxHp = (borg: unknown): number => integer(read(borg, 'maxHp'), 0, 65535, 'maxHp') << 16 >> 16;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; status: Partial<SourceActorStatusTimersBinding>;
    stage: Partial<SourceActorStageBoundsBinding>; control: Partial<SourceActorControlLifecycleBinding>;
    borg: SourceActorStatusBorgOwner; binding: Partial<SourceActorReadyTransitionsBinding>;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned ready-transition actor'); return value;
  };
  const owners = (e: Entry): object[] => [e.actual, e.world, e.status, e.stage, e.control, e.borg, e.binding];
  const noShadowOwners = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['lifecycle18', e.stage], ['mode4a0', e.world], ['mode4a1', e.world], ['flags48a', e.world],
      ['short272', e.status], ['byte490', e.control], ['hp', e.borg], ['maxHp', e.borg], ['colorVariant', e.borg],
      ...[...BYTES, ...SHORTS].map(key => [key, e.binding] as [string, object]),
    ]);
    // Alternate spelling cannot become a second scalar owner either.
    const aliases = ['byte18', 'byte4a0', 'byte4a1', 'byte48a', 'field272', 'short1c6', 'short1c4', 'byte3ed',
      'field48c', 'field494', 'field496', 'field49e', 'field3ea'];
    for (const owner of owners(e)) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing ready-transition storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing ready-transition alias`);
        check();
      }
    }
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(statusActor(id), e.actual, 'status actor');
    stable(stageActor(id), e.actual, 'stage actor'); stable(controlActor(id), e.actual, 'control actor');
    stable(worldBinding(id), e.world, 'world binding'); stable(statusBinding(id), e.status, 'status binding');
    stable(stageBinding(id), e.stage, 'stage binding'); stable(controlBinding(id), e.control, 'control binding');
    stable(statusWorld(id), e.world, 'status world binding'); stable(stageWorld(id), e.world, 'stage world binding');
    stable(controlWorld(id), e.world, 'control world binding'); stable(stageStatus(id), e.status, 'stage status binding');
    stable(controlStatus(id), e.status, 'control status binding'); stable(statusBorg(id), e.borg, 'status Borg');
    noShadowOwners(e);
  };
  const transition = (id: symbol, branch490: boolean): void => guard(() => {
    const e = entry(id);
    if (incompleteTransitions.has(e.actual)) fail('actual actor has a known incomplete ready transition; source continuation is unsupported');
    // Mark before owner admission so caught reentry cannot evade the guard.
    // This host marker is not an additional actor store or a source recovery path.
    incompleteTransitions.add(e.actual); admit(id, e);
    write(e.stage, 'lifecycle18', 2); write(e.binding, 'byte19', 2);
    write(e.binding, 'byte1a', 0); write(e.binding, 'byte1b', 0);
    write(e.status, 'short272', (short(e.status, 'short272') | 0x443) << 16 >> 16);
    if (!branch490) write(e.world, 'flags48a', 4);
    write(e.control, 'byte490', 4);
    write(e.binding, 'short48c', short(e.binding, branch490 ? 'short3ea' : 'short49e'));
    write(e.binding, 'byte48e', byte(e.borg, 'colorVariant'));
    if (branch490) {
      write(e.binding, 'byte48f', byte(e.binding, 'byte3ef'));
      if ((byte(e.world, 'mode4a0') << 24 >> 24) !== 0) {
        // lhz48c copies raw bits to the local halfword; lbz48e/lbz48f
        // and their extsb precede the call. No host table is consulted.
        const form = short(e.binding, 'short48c') & 65535;
        const color = byte(e.binding, 'byte48e') << 24 >> 24;
        const variant = byte(e.binding, 'byte48f') << 24 >> 24;
        fail(`8006aa00 reached unsupported source call 80066198(form=${form}, color=${color}, variant=${variant})`);
      }
    }
    write(e.binding, 'short494', short(e.borg, 'hp'));
    write(e.binding, 'short496', maxHp(e.borg));
    if (branch490) write(e.world, 'mode4a1', 0);
    check(); incompleteTransitions.delete(e.actual);
  });
  const runtime: SourceActorReadyTransitionsRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source ready-transition runtime');
      const e: Entry = {actual,
        world: record(worldBinding(id), 'world binding') as Entry['world'],
        status: record(statusBinding(id), 'status binding') as Entry['status'],
        stage: record(stageBinding(id), 'stage binding') as Entry['stage'],
        control: record(controlBinding(id), 'control binding') as Entry['control'],
        borg: record(statusBorg(id), 'status Borg') as Entry['borg'], binding: {}};
      const records = owners(e);
      if (new Set(records).size !== records.length || records.some(owner => assigned.has(owner))) fail('source owner alias: distinct actual/world/status/stage/control/Borg/ready required');
      admit(id, e); record(initial, 'initial ready binding');
      // Applying the same checks to the input rejects attempts to seed shadows.
      noShadowOwners({...e, binding: initial});
      for (const key of BYTES) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) e.binding[key] = byte(initial, key);
      for (const key of SHORTS) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) e.binding[key] = short(initial, key);
      Object.seal(e.binding); check(); actors.set(id, e);
      records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;},
    getStageBinding(id) {return entry(id).stage;},
    getControlBinding(id) {return entry(id).control;},
    getActualBorg(id) {return entry(id).borg;},
    getActorBinding(id) {return entry(id).binding;},
    getControlRuntime() {return controlRuntime;},
    getStageRuntime() {return stageRuntime;},
    assertActorComplete(id) {
      if (hasIncompleteSourceActorReadyTransition(entry(id).actual))
        fail('actual actor has a known incomplete ready transition; source continuation is unsupported');
    },
    transition490(id) {transition(id, true);},
    transition48a(id) {transition(id, false);},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
