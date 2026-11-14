/** Bounded actual800677b0: canonical7c9 skip and genuine3e0a8 no-contact return.
 * The distinct height-plus-normal query is never replaced with3d6e4, a host
 * floor callback, or a cached height. This slice performs no landing: contact
 * refuses before actual8020ba78 subtraction/normalization and slope handling.
 * Archived operands, not C evaluation order, fix hover668 before query and the
 * fresh positionY/step6d0/fadds after it. See research/decomp/ground-query-evidence-2026-11-14.md.
 * Finite exact binary32, RN00/NI0 and synchronous own-data records are host
 * bounds. No actor fields or query results are copied into parallel storage.
 */
import type {SourceJointVector} from './joint-animation-feedback.js';
import type {RomActor} from './actor.js';
import {addSourceFloat32} from './source-float.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorTerrainNormalOutput, isSourceActorTerrainQueryRuntime,
  type SourceActorTerrainQueryRuntime} from './actor-terrain-query.js';
import {requireCompleteSourceActorDoubleLifecycle, requireSourceActorDoubleInvocation} from './actor-double-prehook.js';

export interface SourceActorGroundProbeSources {
  gauges: SourceActorGaugeScaleRuntime;
  terrain: SourceActorTerrainQueryRuntime;
}
export interface SourceActorGroundProbeRuntime {
  bindActor(identity: symbol): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): object;
  getGaugeBinding(identity: symbol): object;
  getWorldBinding(identity: symbol): object;
  getStatusBinding(identity: symbol): object;
  getHistoryBinding(identity: symbol): object;
  getTerrainGlobals(): object;
  getSourceOwners(identity: symbol): readonly object[];
  /** A genuine zero is not a completed landing. Unsupported contact refuses. */
  runActor(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>();
export function isSourceActorGroundProbeRuntime(value: unknown): value is SourceActorGroundProbeRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-ground-probe] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorGroundProbeRuntime(sources: SourceActorGroundProbeSources): SourceActorGroundProbeRuntime {
  const gauges = own(sources, 'gauges'), terrain = own(sources, 'terrain');
  if (!isSourceActorGaugeScaleRuntime(gauges)) fail('genuine source gauge runtime required');
  if (!isSourceActorTerrainQueryRuntime(terrain)) fail('genuine source terrain-query runtime required');
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const value = run(); check(); return value;} finally {busy = false;}
  };
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const call = <T>(run: () => T): T => {const result = run(); check(); return result;};
  const same = (value: unknown, expected: object, where: string): void => {
    check(); if (value !== expected) fail(`${where}: canonical owner changed or differs`);
  };
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const byte = (value: unknown, key: string): number => {
    const n = read(value, key);
    if (typeof n !== 'number' || !Number.isInteger(n) || n < 0 || n > 255) fail(`${key}: source byte required`);
    return n === 0 ? 0 : n;
  };
  const globals = record(call(() => terrain.getTerrainGlobals()), 'terrain globals');
  interface Entry {actual: RomActor; borg: object; gauge: object; world: object; status: object; history: object; position: object}
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned ground actor'); return e;};
  const owners = (id: symbol, e: Entry): void => {
    requireCompleteSourceActorDoubleLifecycle(e.actual); check();
    same(call(() => gauges.getActualActor(id)), e.actual, 'gauge actual');
    same(call(() => terrain.getActualActor(id)), e.actual, 'terrain actual');
    same(call(() => gauges.getActualBorg(id)), e.borg, 'gauge Borg');
    same(call(() => gauges.getActorBinding(id)), e.gauge, 'gauge binding');
    same(call(() => gauges.getWorldBinding(id)), e.world, 'gauge world');
    same(call(() => gauges.getStatusBinding(id)), e.status, 'gauge status');
    same(call(() => terrain.getHistoryBinding(id)), e.history, 'terrain history');
    same(call(() => terrain.getTerrainGlobals()), globals, 'terrain globals');
    same(read(e.actual, 'pos'), e.position, 'actual position20');
    for (const value of [...Object.values(e), globals]) {
      for (const key of ['byte7c9', 'hoverOffset668', 'supportContact1db', 'stepHeight', 'pos', 'previousStepHeight6d4']) {
        const expected = key === 'byte7c9' ? e.gauge : key === 'previousStepHeight6d4' ? e.history : e.actual;
        if (value !== expected && Object.getOwnPropertyDescriptor(value, key) !== undefined)
          fail(`${key}: competing source storage owner`);
        check();
      }
      for (const key of ['collisionDisabled7c9', 'field7c9', 'groundHeight', 'groundNormal']) {
        if (Object.getOwnPropertyDescriptor(value, key) !== undefined) fail(`${key}: competing source storage alias`);
        check();
      }
    }
  };
  const runtime: SourceActorGroundProbeRuntime = {
    bindActor(id) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(call(() => gauges.getActualActor(id)), 'actual actor') as RomActor;
      const e: Entry = {actual, borg: record(call(() => gauges.getActualBorg(id)), 'actual Borg'),
        gauge: record(call(() => gauges.getActorBinding(id)), 'gauge'), world: record(call(() => gauges.getWorldBinding(id)), 'world'),
        status: record(call(() => gauges.getStatusBinding(id)), 'status'),
        history: record(call(() => terrain.getHistoryBinding(id)), 'history'), position: record(read(actual, 'pos'), 'position20')};
      const records = Object.values(e);
      if (new Set([...records, globals]).size !== records.length + 1 || records.some(value => assigned.has(value)))
        fail('source ground storage owner alias');
      owners(id, e); actors.set(id, e); records.forEach(value => assigned.add(value));
    });},
    getActualActor(id) {return entry(id).actual;}, getActualBorg(id) {return entry(id).borg;},
    getGaugeBinding(id) {return entry(id).gauge;}, getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;}, getHistoryBinding(id) {return entry(id).history;},
    getTerrainGlobals() {return globals;},
    getSourceOwners(id) {return Object.freeze([...Object.values(entry(id)), globals]);},
    runActor(id) {return guard(() => {
      const e = entry(id); requireSourceActorDoubleInvocation(e.actual, 'ground', runtime); owners(id, e);
      if (byte(e.gauge, 'byte7c9') !== 0) return 0;
      const clearance = f(e.actual, 'hoverOffset668');
      const normal = createSourceActorTerrainNormalOutput();
      const height = float(call(() => terrain.queryHeightNormal8003e0a8(id, e.position as SourceJointVector, clearance, normal)), '3e0a8 height');
      // Fresh source loads after3e0a8, not the query's captured position/step.
      const y = f(e.position, 'y'), step = f(e.actual, 'stepHeight');
      const top = addSourceFloat32(y, step);
      if (top > height) return 0;
      if (byte(e.actual, 'supportContact1db') === 0)
        fail('800677b0 reached unsupported actual8020ba78 contact displacement before normalization and slope handling');
      fail('800677b0 reached unsupported supporting-contact slope handling');
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
