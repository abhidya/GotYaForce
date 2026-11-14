/** Bounded actual8006f7c0 selected by an explicit decoded4bc pointer.
 * Source chunk_0009.c:4091-4117; the function ends at8006f88c, where
 * the separate omitted72-byte posthook begins. This is not that posthook.
 * Authenticated instruction order and constructor pointer:
 * research/decomp/double-action-envelope-evidence-2026-11-14.md.
 * Existing actual3e8/5e0/aimRoll1dfc, stream582, status272, charge58e and
 * persistent ninjaX7c8/7b0 owners stay live. Only missing6ee/family pointer
 * cells are copied/sealed, with no defaults. Source short272 is retained in
 * its existing signed16 representation; lha/sth preserve its raw bit pattern.
 * Non-Double or unarmed Double returns genuinely when this function is
 * explicitly selected (not proof of other families' constructor pointers).
 * Armed Double retains its
 * earlier writes, then refuses before actual4538c normalization. No vector,
 * float constant, scale or posthook is guessed. Stable synchronous non-proxy
 * own-data records are host admission bounds, not retail hydration/provenance.
 * Refusals after source effects permanently poison this actor's Double
 * lifecycle, including action dispatch. No production routing is added.
 */
import type {RomActor} from './actor.js';
import {getDoubleNinjaOwnerState, type DoubleNinjaOwnerState} from '../ninjaX.js';
import {isSourceActorStatusTimersRuntime, type SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime} from './actor-input-charge.js';
import {isSourceStreamWaitRuntime, type SourceStreamWaitRuntime} from './stream-wait.js';

export interface SourceActorDoublePrehookBinding {
  pointer4b4: number; pointer4bc: number; pointer4c0: number;
  byte6ee: number;
}
export interface SourceActorDoublePrehookSources {
  status: SourceActorStatusTimersRuntime;
  charge: SourceActorInputChargeRuntime;
  streams: SourceStreamWaitRuntime;
}
export interface SourceActorDoublePrehookRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorDoublePrehookBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceActorDoublePrehookBinding>;
  getMappingActor(identity: symbol): object;
  getWorldBinding(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getStartBinding(identity: symbol): object;
  /** Same genuine runtime used by source action stream starts. */
  getStreamsRuntime(): SourceStreamWaitRuntime;
  getChargeBinding(identity: symbol): object;
  getStatusBinding(identity: symbol): object;
  getCloneOwner(identity: symbol): DoubleNinjaOwnerState | undefined;
  getSourceOwners(identity: symbol): readonly object[];
  assertActorComplete(identity: symbol): void;
  runActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>(), incomplete = new WeakSet<object>();
export function isSourceActorDoublePrehookRuntime(value: unknown): value is SourceActorDoublePrehookRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
/** A permanent failure latch. No public clear or fallback operation exists. */
export function markIncompleteSourceActorDoubleLifecycle(actual: object): void {incomplete.add(actual);}
export function hasIncompleteSourceActorDoubleLifecycle(actual: object): boolean {return incomplete.has(actual);}
export function requireCompleteSourceActorDoubleLifecycle(actual: object): void {
  if (incomplete.has(actual)) fail('known incomplete source Double lifecycle');
}
function fail(reason: string): never {
  throw Error(`[actor-double-prehook] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string, writable = false): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(owner, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
export function createSourceActorDoublePrehookRuntime(sources: SourceActorDoublePrehookSources): SourceActorDoublePrehookRuntime {
  const status = own(sources, 'status'), charge = own(sources, 'charge'), streams = own(sources, 'streams');
  if (!isSourceActorStatusTimersRuntime(status)) fail('status requires genuine source runtime');
  if (!isSourceActorInputChargeRuntime(charge)) fail('charge requires genuine source runtime');
  if (!isSourceStreamWaitRuntime(streams)) fail('streams requires genuine source runtime');
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const value = run(); check(); return value;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const invoke = <T>(run: () => T): T => {const value = run(); check(); return value;};
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const byte = (owner: object, key: string): number => integer(read(owner, key), 0, 255, key);
  const word = (owner: object, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const half = (owner: object, key: string): number => integer(read(owner, key), -32768, 32767, key);
  interface Entry {
    actual: RomActor; mapping: object; world: object; attribute: object; start: object; charge: object; status: object;
    binding: Partial<SourceActorDoublePrehookBinding>; clone?: DoubleNinjaOwnerState;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned Double actor'); return e;};
  const owners = (e: Entry): object[] => [e.actual, e.mapping, e.world, e.attribute, e.start, e.charge, e.status, e.binding,
    ...(e.clone === undefined ? [] : [e.clone])];
  const same = (value: unknown, expected: object, where: string): void => {
    check(); if (value !== expected) fail(`${where}: canonical owner changed or differs`);
  };
  const noShadows = (e: Entry): void => {
    const canonical = new Map<string, object | undefined>([['borgNumber', e.actual], ['controlWord', e.actual], ['aimRoll1dfc', e.actual],
      ['defaultSelector582', e.start], ['short272', e.status], ['byte58e', e.charge], ['byte6ee', e.binding],
      ['pointer4b4', e.binding], ['pointer4bc', e.binding], ['pointer4c0', e.binding],
      ['arm7c8', e.clone], ['offset7b0', e.clone]]);
    for (const owner of owners(e)) {
      for (const [key, expected] of canonical) if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
        fail(`${key}: competing Double storage owner`);
      for (const key of ['byte3e8', 'short3e8', 'flags5e0', 'field1dfc', 'short1dfc', 'byte582', 'byte272',
        'field272', 'field58e', 'field6ee', 'byte7c8', 'clone7c8', 'field7b0', 'field4b4', 'field4bc', 'field4c0'])
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing Double storage alias`);
    }
    check();
  };
  const reconcile = (id: symbol, e: Entry): void => {
    same(invoke(() => status.getActualActor(id)), e.actual, 'status actual');
    same(invoke(() => charge.getActualActor(id)), e.actual, 'charge actual');
    same(invoke(() => status.getActorBinding(id)), e.status, 'status binding');
    same(invoke(() => charge.getStatusBinding(id)), e.status, 'charge status');
    same(invoke(() => status.getMappingActor(id)), e.mapping, 'status mapping');
    same(invoke(() => charge.getMappingActor(id)), e.mapping, 'charge mapping');
    same(invoke(() => status.getWorldBinding(id)), e.world, 'world binding');
    same(invoke(() => status.getAttributeBinding(id)), e.attribute, 'status attribute');
    same(invoke(() => charge.getAttributeBinding(id)), e.attribute, 'charge attribute');
    same(invoke(() => status.getStartBinding(id)), e.start, 'status stream start');
    same(invoke(() => streams.getStartActorBinding(id)), e.start, 'stream start');
    same(invoke(() => charge.getActorBinding(id)), e.charge, 'charge binding');
    const clone = getDoubleNinjaOwnerState(e.actual); check();
    if (e.clone !== undefined && clone !== e.clone) fail('persistent clone owner changed');
    if (e.clone === undefined && clone !== undefined) {
      record(clone, 'persistent clone owner');
      if (assigned.has(clone)) fail('persistent clone owner aliases another source owner');
      e.clone = clone;
      if (actors.has(id)) assigned.add(clone);
    }
    for (const key of ['rootAction', 'preState', 'postState'])
      if (read(e.actual, key) !== null) fail(`legacy callable ${key} conflicts with source Double ownership`);
    noShadows(e);
  };
  const runtime: SourceActorDoublePrehookRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(invoke(() => status.getActualActor(id)), 'actual actor') as RomActor;
      requireCompleteSourceActorDoubleLifecycle(actual);
      if (claimed.has(actual)) fail('actual actor already claimed by source Double runtime');
      record(initial, 'initial binding');
      const binding: Partial<SourceActorDoublePrehookBinding> = {};
      for (const key of ['pointer4b4', 'pointer4bc', 'pointer4c0'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = word(initial, key);
      if (Object.getOwnPropertyDescriptor(initial, 'byte6ee') !== undefined) binding.byte6ee = byte(initial, 'byte6ee');
      const e: Entry = {actual, binding: Object.seal(binding),
        mapping: record(invoke(() => status.getMappingActor(id)), 'mapping'), world: record(invoke(() => status.getWorldBinding(id)), 'world'),
        attribute: record(invoke(() => status.getAttributeBinding(id)), 'attribute'), start: record(invoke(() => status.getStartBinding(id)), 'stream start'),
        status: record(invoke(() => status.getActorBinding(id)), 'status'), charge: record(invoke(() => charge.getActorBinding(id)), 'charge')};
      reconcile(id, e);
      const records = owners(e);
      if (new Set(records).size !== records.length || records.some(owner => assigned.has(owner)))
        fail('source Double storage owner alias');
      check(); actors.set(id, e); records.forEach(owner => assigned.add(owner)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getActorBinding(id) {return entry(id).binding;},
    getMappingActor(id) {return entry(id).mapping;}, getWorldBinding(id) {return entry(id).world;},
    getAttributeBinding(id) {return entry(id).attribute;}, getStartBinding(id) {return entry(id).start;},
    getStreamsRuntime() {return streams;},
    getChargeBinding(id) {return entry(id).charge;}, getStatusBinding(id) {return entry(id).status;},
    getCloneOwner(id) {return getDoubleNinjaOwnerState(entry(id).actual);},
    getSourceOwners(id) {
      const e = entry(id), result: object[] = [e.binding, e.charge];
      const clone = getDoubleNinjaOwnerState(e.actual);
      if (clone !== undefined) {
        result.push(clone);
        // Metadata-only alias exclusion, not a source vector load. No numeric
        // component is inspected before the unsupported4538c call.
        const offset = Object.getOwnPropertyDescriptor(clone, 'offset7b0');
        if (offset && 'value' in offset && offset.value !== null && typeof offset.value === 'object') result.push(offset.value);
      }
      return Object.freeze(result);
    },
    assertActorComplete(id) {guard(() => {const e = entry(id); requireCompleteSourceActorDoubleLifecycle(e.actual); reconcile(id, e);});},
    runActor(id) {guard(() => {
      const e = entry(id); requireCompleteSourceActorDoubleLifecycle(e.actual); reconcile(id, e);
      let effect = false;
      const write = (owner: object, key: string, value: number): void => {
        own(owner, key, true); check(); effect = true; (owner as Record<string, unknown>)[key] = value; check();
      };
      try {
        const target = word(e.binding, 'pointer4bc');
        if (target !== 0x8006f7c0) fail(`unsupported actual4bc target0x${target.toString(16)}`);
        const borg = integer(read(e.actual, 'borgNumber'), 0, 65535, 'borgNumber');
        write(e.start, 'defaultSelector582', borg === 3 ? 1 : 0);
        if ((word(e.actual, 'controlWord') & 1) === 0) {
          write(e.actual, 'aimRoll1dfc', 0); write(e.binding, 'byte6ee', 0);
        }
        if ((word(e.actual, 'controlWord') & 0x1000) === 0) {
          const bits = half(e.status, 'short272') & 0xfffb;
          write(e.status, 'short272', bits << 16 >> 16);
        }
        write(e.charge, 'byte58e', byte(e.charge, 'byte58e') & 0xdf);
        if (integer(read(e.actual, 'borgNumber'), 0, 65535, 'borgNumber') === 3) {
          if (e.clone === undefined) fail('actual7c8 requires existing explicit persistent clone owner');
          if (byte(e.clone, 'arm7c8') !== 0) {
            write(e.charge, 'byte58e', byte(e.charge, 'byte58e') | 0x20);
            fail('8006f7c0 reached unsupported actual8004538c normalization of persistent7b0');
          }
        }
        check();
      } catch (error) {
        if (effect) markIncompleteSourceActorDoubleLifecycle(e.actual);
        throw error;
      }
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
