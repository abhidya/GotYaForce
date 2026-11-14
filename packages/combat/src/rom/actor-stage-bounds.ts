/** Explicit bounded80059e58 stage-boundary lifecycle, not an ordinary tick.
 * Uses the SAME actual actor, world.mode4a1, status.short272 and shared
 * DAT_8043625c terrain owner. Stage+38/3c/40/44 are not terrain-grid extents.
 * Only absent18/6cc get explicit storage here; actual noClamp6cb remains the
 * existing physics-extras owner. Nothing is defaulted or hydrated from host
 * death/fusion state. A successful return proves only this bounded helper.
 *
 * Archived65-instruction span: signed4a1, unsigned18, signed6cb gates; ordered
 * inclusive X/Z bounds; signed16 increment/reload; >=30 or02000000 transition;
 * clear6cc, set6cb, optionally OR43 into272, then6a750(actor,9),6a6fc(actor,9).
 * Optional genuine source cue reset pair may be bound explicitly. Without it,
 * reaching6a750 retains the historical refusal. No approximate callback can
 * manufacture success; with it, both calls execute even if upper returns0.
 * Finite exact-f32 comparisons, non-proxy own-data records and synchronous
 * stable owners are explicit bounds, not live FPSCR/RAM or retail-input proof.
 * No rollback, automatic cadence, movement, pose, history or live activation.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding} from './actor-status-timers.js';
import type {SourceActorTerrainQueryRuntime, SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime} from './actor-cue-reset.js';

export interface SourceActorStageBoundsBinding {lifecycle18: number; short6cc: number}
export interface SourceActorStageBoundsSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding'>;
  terrain: Pick<SourceActorTerrainQueryRuntime, 'getTerrainGlobals'>;
}
export interface SourceActorStageBoundsRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorStageBoundsBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getActorBinding(identity: symbol): Partial<SourceActorStageBoundsBinding>;
  getTerrainGlobals(): SourceActorTerrainGlobals;
  /** Once-only genuine helper binding. Does not activate a source tick. */
  bindCueRuntime(cues: SourceActorCueResetRuntime): void;
  getCueRuntime(): SourceActorCueResetRuntime | undefined;
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorStageBoundsRuntime(value: unknown): value is SourceActorStageBoundsRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-stage-bounds] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
export function createSourceActorStageBoundsRuntime(sources: SourceActorStageBoundsSources): SourceActorStageBoundsRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorStageBoundsSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(fn, receiver, args); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const terrainGlobals = capture('terrain', 'getTerrainGlobals');
  const terrain = record(terrainGlobals(), 'shared DAT_8043625c terrain') as SourceActorTerrainGlobals;
  const byte = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const short = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const word = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const f = (r: unknown, key: string): number => float(read(r, key), key);
  const noShadowOwners = (actual: object): void => {
    for (const key of ['lifecycle18', 'short6cc', 'field6cc']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined)
        fail(`${key}: competing stage-boundary storage on actual actor`);
      check();
    }
  };
  interface Entry {
    actual: RomActor; position: object; world: SourceActorWorldMatrixBinding;
    status: Partial<SourceActorStatusTimersBinding>; binding: Partial<SourceActorStageBoundsBinding>;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned stage-boundary actor'); return value;};
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  let cues: {runtime: SourceActorCueResetRuntime; actor: (id: symbol) => RomActor;
    upper: (id: symbol, cue: number) => 0 | 1; full: (id: symbol, cue: number) => 0 | 1} | undefined;
  const invokeCue = (id: symbol, actor: Entry, upper: boolean): void => {
    const owner = cues!;
    const actual = Reflect.apply(owner.actor, owner.runtime, [id]); check();
    stable(actual, actor.actual, 'cue actor');
    const result = Reflect.apply(upper ? owner.upper : owner.full, owner.runtime, [id, 9]); check();
    if (result !== 0 && result !== 1) fail('genuine cue helper returned asynchronously or unexpectedly');
  };
  const runtime: SourceActorStageBoundsRuntime = {
    getCueRuntime() {return cues?.runtime;},
    bindCueRuntime(value) {guard(() => {
      if (cues !== undefined) fail('cue runtime already bound');
      if (!isSourceActorCueResetRuntime(value)) fail('cue reset requires genuine source runtime, not callback effects');
      const actor = read(value, 'getActualActor'), upper = read(value, 'dispatchUpperBodyCue'), full = read(value, 'dispatchFullBodyCue');
      if (typeof actor !== 'function' || typeof upper !== 'function' || typeof full !== 'function') fail('cue source methods required');
      for (const [id, bound] of actors) {
        const actual = Reflect.apply(actor, value, [id]); check(); stable(actual, bound.actual, 'cue actor');
      }
      cues = {runtime: value, actor: actor as SourceActorCueResetRuntime['getActualActor'],
        upper: upper as SourceActorCueResetRuntime['dispatchUpperBodyCue'], full: full as SourceActorCueResetRuntime['dispatchFullBodyCue']};
    });},
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source stage-boundary runtime');
      if (cues !== undefined) {
        const cueActual = Reflect.apply(cues.actor, cues.runtime, [id]); check(); stable(cueActual, actual, 'cue actor');
      }
      noShadowOwners(actual);
      stable(statusActor(id), actual, 'status actor');
      const position = record(read(actual, 'pos'), 'actual position');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const status = record(statusBinding(id), 'status binding') as Partial<SourceActorStatusTimersBinding>;
      const records = [actual, position, world, status];
      if (new Set([...records, terrain]).size !== records.length + 1 || records.some(value => assigned.has(value)))
        fail('source owner alias: distinct actual actor/position/world/status/terrain required');
      record(initial, 'initial stage-boundary binding');
      const binding: Partial<SourceActorStageBoundsBinding> = {};
      if (Object.getOwnPropertyDescriptor(initial, 'lifecycle18') !== undefined) binding.lifecycle18 = byte(initial, 'lifecycle18');
      if (Object.getOwnPropertyDescriptor(initial, 'short6cc') !== undefined) binding.short6cc = short(initial, 'short6cc');
      check(); actors.set(id, {actual, position, world, status, binding: Object.seal(binding)});
      records.forEach(value => assigned.add(value)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;},
    getActorBinding(id) {return entry(id).binding;},
    getTerrainGlobals() {return terrain;},
    updateActor(id) {guard(() => {
      const actor = entry(id);
      // Owner checks are host admission, not extra source field accesses.
      stable(worldActor(id), actor.actual, 'world actor'); stable(statusActor(id), actor.actual, 'status actor');
      stable(worldBinding(id), actor.world, 'world binding'); stable(statusBinding(id), actor.status, 'status binding');
      noShadowOwners(actor.actual);
      if ((byte(actor.world, 'mode4a1') << 24 >> 24) !== 0) return;
      if (byte(actor.binding, 'lifecycle18') !== 1) return;
      if ((byte(actor.actual, 'noClamp6cb') << 24 >> 24) !== 0) return;
      stable(terrainGlobals(), terrain, 'shared DAT_8043625c terrain');
      stable(read(actor.actual, 'pos'), actor.position, 'actual position');
      const x = f(actor.position, 'x');
      // The first x is retained for both X comparisons. z loads only after
      // BOTH X comparisons pass, then is retained for both Z comparisons.
      let outside = x < f(terrain, 'minX3c');
      if (!outside) outside = x > f(terrain, 'maxX38');
      if (!outside) {
        const z = f(actor.position, 'z');
        outside = z < f(terrain, 'minZ44');
        if (!outside) outside = z > f(terrain, 'maxZ40');
      }
      if (!outside) {write(actor.binding, 'short6cc', 0); return;}
      write(actor.binding, 'short6cc', (short(actor.binding, 'short6cc') + 1) << 16 >> 16);
      if (short(actor.binding, 'short6cc') < 30 && (word(actor.actual, 'controlWord') & 0x02000000) === 0) return;
      write(actor.binding, 'short6cc', 0);
      if ((word(actor.actual, 'controlWord') & 0x05000000) === 0) write(actor.actual, 'noClamp6cb', 1);
      else {
        write(actor.actual, 'noClamp6cb', 2);
        write(actor.status, 'short272', (short(actor.status, 'short272') | 0x43) << 16 >> 16);
      }
      if (cues === undefined) fail('80059f2c reached unsupported source call 8006a750(actor,9); later8006a6fc has not executed');
      invokeCue(id, actor, true);
      invokeCue(id, actor, false);
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
