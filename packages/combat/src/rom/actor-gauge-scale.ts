/** Actual 8003d3e8/8003d444 and bounded 8005bab8, offline only.
 * Evidence: read_archived_gauge_scale_evidence.py and source chunk_0004.c:
 * 6864–6892 / chunk_0007.c:3672–3713. No original execution is claimed.
 * Archived instruction/constant evidence, not C expression grouping, fixes
 * the three separately rounded reset operations: (B4-1), .5*delta, base*factor.
 * fctiwz is admitted only for representable signed32 results; extsh and sth
 * wrapping remain distinct. RN00/NI0 and finite exact binary32 are bounds.
 *
 * Actual Borg gauge fields are raw u16, while explicit missing7d6/7dc are
 * decoded signed shorts. Actual RomActor.modelScale/collisionScale, world
 * scale58, status7d8 and Borg.paramTier retain their existing owners. A missing
 * collisionScale is NOT replaced with modelScale. No clock or tier copy exists.
 * Optional genuine tier lifecycle supplies6817c at the reached750 expiry,
 * then the caller clears750/74e and continues its source scale interpolation.
 * Without that explicit binding the historical call-boundary refusal remains.
 * This neither implements full59068 nor activates any production/tick route.
 *
 * Non-proxy own-data records, stable synchronous owners, lazy reached reads
 * and destination checks are explicit host bounds. Refusals retain completed
 * effects; caught mutation reentry poisons the enclosing operation.
 */
import type {BorgRuntime} from '../types.js';
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {addSourceFloat32} from './source-float.js';
import {isSourceActorTierLifecycleRuntime, type SourceActorTierLifecycleRuntime} from './actor-tier-lifecycle.js';

export interface SourceActorGaugeScaleBinding {
  short7d6: number; short7dc: number;
  targetScaleB8: number; byte7c9: number; fieldC4: number;
}
export type SourceActorGaugeBorgOwner = Pick<BorgRuntime, 'downGaugeBase' | 'downGauge' | 'paramTier'>;
export interface SourceActorGaugeScaleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActualBorg' | 'getActorBinding'>;
}
export interface SourceActorGaugeScaleRuntime {
  bindActor(identity: symbol, actualBorg: SourceActorGaugeBorgOwner,
    initial: Readonly<Partial<SourceActorGaugeScaleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorGaugeBorgOwner;
  getStatusBinding(identity: symbol): object;
  getWorldBinding(identity: symbol): object;
  getTierOwner(identity: symbol): object;
  getActorBinding(identity: symbol): Partial<SourceActorGaugeScaleBinding>;
  /** One-time late binding breaks the real gauge/tier owner construction cycle. */
  bindTierLifecycleSources(identity: symbol, tiers: SourceActorTierLifecycleRuntime): void;
  getTierLifecycleRuntime(identity: symbol): SourceActorTierLifecycleRuntime | undefined;
  resetDownGauge(identity: symbol): void;
  resetSecondaryGauge(identity: symbol): void;
  updateActor(identity: symbol): void;
}
// A status callee must be this implementation, not an arbitrary successful
// callback with matching method names. It still verifies all owner identities.
const genuineRuntimes = new WeakSet<object>();
export function isSourceActorGaugeScaleRuntime(value: unknown): value is SourceActorGaugeScaleRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-gauge-scale] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
const s16 = (value: number): number => value << 16 >> 16;
const STEP = 0.05000000074505806; // Archived80437420, bits3d4ccccd.
export function createSourceActorGaugeScaleRuntime(sources: SourceActorGaugeScaleSources): SourceActorGaugeScaleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (r: unknown, key: string): unknown => {const value = own(r, key); check(); return value;};
  const write = (r: unknown, key: string, value: number): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
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
  const capture = (name: keyof SourceActorGaugeScaleSources, key: string) => {
    const receiver = own(sources, name), method = own(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const result = Reflect.apply(method, receiver, [id]); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBorg = capture('status', 'getActualBorg');
  const statusBinding = capture('status', 'getActorBinding');
  const f = (r: unknown, key: string): number => float(read(r, key), key);
  const h = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const b = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const multiply = (a: number, b: number): number => float(Math.fround(a * b), 'fmuls result');
  interface Entry {
    actual: RomActor; borg: SourceActorGaugeBorgOwner; tier: object;
    world: object; scale: object; status: object; binding: Partial<SourceActorGaugeScaleBinding>;
  }
  interface TierSources {
    runtime: SourceActorTierLifecycleRuntime;
    actor: () => unknown; borg: () => unknown; status: () => unknown;
    world: () => unknown; gauge: () => unknown; tier: () => unknown;
    apply: (delta: number) => unknown;
  }
  const tierSources = new Map<symbol, TierSources>();
  const checkTierSources = (bound: TierSources, actor: Entry): void => {
    if (bound.actor() !== actor.actual || bound.borg() !== actor.borg || bound.status() !== actor.status ||
        bound.world() !== actor.world || bound.gauge() !== actor.binding || bound.tier() !== actor.tier)
      fail('tier lifecycle actual actor/Borg/status/world/gauge/tier owners differ');
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const actor = actors.get(id); if (!actor) fail('unknown/non-owned gauge actor'); return actor;};
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): void => {
    if (get(id) !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const actorOwners = (id: symbol, actor: Entry): void => {
    stable(worldActor, id, actor.actual, 'world actor'); stable(statusActor, id, actor.actual, 'status actor');
    stable(statusBorg, id, actor.borg, 'status Borg'); stable(statusBinding, id, actor.status, 'status binding');
  };
  const reset = (id: symbol, actor: Entry, secondary: boolean): void => {
    actorOwners(id, actor);
    // lha precedes lfs; the original base is retained through correction/add.
    const base = secondary ? h(actor.binding, 'short7d6') :
      s16(integer(read(actor.borg, 'downGaugeBase'), 0, 65535, 'downGaugeBase'));
    const scale = f(actor.actual, 'modelScale');
    const delta = addSourceFloat32(scale, -1), factor = multiply(0.5, delta);
    // The signed-short->double subtraction->f32 conversion is exact here.
    const correction = multiply(base, factor), converted = Math.trunc(correction);
    integer(converted, -2147483648, 2147483647, 'fctiwz signed32 result');
    const result = s16(base + s16(converted));
    if (secondary) write(actor.binding, 'short7dc', result);
    else write(actor.borg, 'downGauge', result & 65535);
  };
  const runtime: SourceActorGaugeScaleRuntime = Object.freeze({
    bindActor(id: symbol, actualBorg: SourceActorGaugeBorgOwner,
      initial: Readonly<Partial<SourceActorGaugeScaleBinding>>): void {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      const borg = record(actualBorg, 'actual BorgRuntime') as SourceActorGaugeBorgOwner;
      stable(statusActor, id, actual, 'status actor'); stable(statusBorg, id, borg, 'status Borg');
      const status = record(statusBinding(id), 'status binding'), world = record(worldBinding(id), 'world binding');
      const scale = record(read(world, 'scale58'), 'world scale58'), tier = record(read(borg, 'paramTier'), 'actual Borg.paramTier');
      const records = [actual, borg, status, world, scale, tier];
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value)))
        fail('source owner alias: distinct actual actor/Borg/status/world/scale/tier required');
      record(initial, 'initial gauge binding');
      const binding: Partial<SourceActorGaugeScaleBinding> = {};
      for (const key of ['short7d6', 'short7dc'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = h(initial, key);
      for (const key of ['targetScaleB8', 'fieldC4'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = f(initial, key);
      if (Object.getOwnPropertyDescriptor(initial, 'byte7c9') !== undefined) binding.byte7c9 = b(initial, 'byte7c9');
      check(); actors.set(id, {actual, borg, status, world, scale, tier, binding: Object.seal(binding)});
      records.forEach(value => assigned.add(value)); assigned.add(binding);
    });},
    getActualActor(id: symbol) {return entry(id).actual;},
    getActualBorg(id: symbol) {return entry(id).borg;},
    getStatusBinding(id: symbol) {return entry(id).status;},
    getWorldBinding(id: symbol) {return entry(id).world;},
    getTierOwner(id: symbol) {return entry(id).tier;},
    getActorBinding(id: symbol) {return entry(id).binding;},
    getTierLifecycleRuntime(id: symbol) {entry(id); return tierSources.get(id)?.runtime;},
    bindTierLifecycleSources(id: symbol, tiers: SourceActorTierLifecycleRuntime): void {guard(() => {
      const actor = entry(id);
      if (tierSources.has(id)) fail('tier lifecycle sources already bound');
      if (!isSourceActorTierLifecycleRuntime(tiers)) fail('tier lifecycle requires the genuine source runtime, not callback effects');
      const method = (key: keyof SourceActorTierLifecycleRuntime) => {
        const fn = read(tiers, key);
        if (typeof fn !== 'function') fail(`${key}: own data-function required`);
        return (...args: unknown[]): unknown => {const result = Reflect.apply(fn, tiers, [id, ...args]); check(); return result;};
      };
      const bound: TierSources = {runtime: tiers, actor: method('getActualActor'), borg: method('getActualBorg'),
        status: method('getStatusBinding'), world: method('getWorldBinding'), gauge: method('getGaugeBinding'),
        tier: method('getTierOwner'), apply: method('applyDelta127')};
      checkTierSources(bound, actor); check(); tierSources.set(id, bound);
    });},
    resetDownGauge(id: symbol): void {guard(() => reset(id, entry(id), false));},
    resetSecondaryGauge(id: symbol): void {guard(() => reset(id, entry(id), true));},
    updateActor(id: symbol): void {guard(() => {
      const actor = entry(id), actual = actor.actual, binding = actor.binding;
      actorOwners(id, actor);
      if (read(actor.borg, 'paramTier') !== actor.tier) fail('actual Borg.paramTier owner changed');
      const timer = h(actor.tier, 'timerFrames');
      if (timer > 0) {
        const remaining = s16(timer - 1);
        write(actor.tier, 'timerFrames', remaining);
        if (remaining <= 0) {
          // lbz/extsb/neg precede the actual call, even when6817c's global
          // gate later returns. Its genuine return precedes BOTH caller clears.
          const delta = -integer(read(actor.tier, 'deltaAccum'), -128, 127, 'deltaAccum');
          const tiers = tierSources.get(id);
          if (!tiers) fail('8005baf4 reached unsupported source call 8006817c (global gate and parameter table owner required)');
          checkTierSources(tiers, actor);
          if (tiers.apply(delta) !== undefined) fail('genuine tier lifecycle returned asynchronously or unexpectedly');
          write(actor.tier, 'timerFrames', 0); //5bafc, after genuine return.
          write(actor.tier, 'deltaAccum', 0); //5bb00, not before6817c.
        }
      }
      // Archived loads are B8 then B4, unlike the decompiler's printed order.
      const target = f(binding, 'targetScaleB8'), before = f(actual, 'modelScale');
      if (target === before) return;
      if (b(binding, 'byte7c9') !== 0) return;
      const up = target > before;
      write(actual, 'modelScale', addSourceFloat32(before, up ? STEP : -STEP));
      const reachedTarget = f(binding, 'targetScaleB8'), after = f(actual, 'modelScale');
      if (up ? reachedTarget <= after : reachedTarget >= after) {
        write(actual, 'modelScale', reachedTarget);
        reset(id, actor, false);
      }
      // Five independent source loads and stores. Later destination failure
      // preserves modelScale, any reset and the completed scale-copy prefix.
      for (const key of ['x', 'y', 'z'] as const) {
        const value = f(actual, 'modelScale');
        stable(worldBinding, id, actor.world, 'world binding');
        if (read(actor.world, 'scale58') !== actor.scale) fail('world scale58 owner changed');
        write(actor.scale, key, value);
      }
      write(actual, 'collisionScale', f(actual, 'modelScale'));
      write(binding, 'fieldC4', f(actual, 'modelScale'));
    });},
  });
  genuineRuntimes.add(runtime); return runtime;
}
