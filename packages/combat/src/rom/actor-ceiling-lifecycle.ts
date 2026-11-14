/** Explicit bounded80068030 ceiling tail and its genuine three-instruction
 * leaf8008b290, not physicsExtras.floorSnap8030 or a general actor frame.
 * Evidence: actor-ceiling-lifecycle-evidence-2026-11-14.md and
 * read_archived_actor_ceiling_evidence.py. The authenticated41+3 instructions
 * use match-global80433934+d9, signed
 * actual1db, actual24/668/48/30 and shared stage8043625c+34. Every scalar
 * remains on its existing owner; no empty helper binding or default exists.
 * The genuine normal-matrix runtime supplies the match-global owner, and the
 * genuine stage-bounds runtime supplies the SAME terrain-global owner.
 *
 * Source order matters: stage pointer before fadds, upper34 after fadds;
 * successful gates store +0 to48 BEFORE reloading stage/668/34/30. Saved30
 * is loaded BEFORE fsubs. Ordered GT alone selects saved30; equality selects
 * the computed difference, preserving its signed zero. A completed call
 * returns literal0 or1. Earlier stores survive later refusal, without rollback.
 *
 * Finite exact-f32, RN00/NI0, non-proxy own-data records and stable synchronous
 * borrowed owners are explicit host bounds, not live FPSCR/RAM or replay proof.
 * Captured methods preserve receivers; retained vectors, permanent actor
 * claims, alias checks and caught-reentry poison protect source ownership.
 * Nothing hydrates inputs, executes the host floor contract or activates ticks.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import {isSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateRuntime,
  type SourceActorMatrixUpdateBinding, type SourceActorMatrixUpdateGlobals} from './actor-matrix-update.js';
import {isSourceActorStageBoundsRuntime, type SourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import type {SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {addSourceFloat32} from './source-float.js';

export interface SourceActorCeilingLifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  matrix: SourceActorMatrixUpdateRuntime;
  stageBounds: SourceActorStageBoundsRuntime;
}
export interface SourceActorCeilingLifecycleRuntime {
  bindActor(identity: symbol): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): object;
  getMatrixBinding(identity: symbol): SourceActorMatrixUpdateBinding;
  getTerrainGlobals(): SourceActorTerrainGlobals;
  getMatchGlobals(): SourceActorMatrixUpdateGlobals;
  updateActor(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorCeilingLifecycleRuntime(value: unknown): value is SourceActorCeilingLifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-ceiling-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(value, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorCeilingLifecycleRuntime(sources: SourceActorCeilingLifecycleSources): SourceActorCeilingLifecycleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const write = (value: unknown, key: string, next: number): void => {
    own(value, key, true); check(); (value as Record<string, unknown>)[key] = next; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorCeilingLifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  if (!isSourceActorMatrixUpdateRuntime(read(sources, 'matrix')))
    fail('matrix requires genuine source runtime, not a match-global callback');
  if (!isSourceActorStageBoundsRuntime(read(sources, 'stageBounds')))
    fail('stage bounds requires genuine source runtime, not a floor callback');
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const matrixActor = capture('matrix', 'getActualActor'), matrixWorld = capture('matrix', 'getWorldBinding');
  const matrixMapping = capture('matrix', 'getMappingActor'), matrixBinding = capture('matrix', 'getActorBinding');
  const matchGlobals = capture('matrix', 'getGlobals');
  const stageActor = capture('stageBounds', 'getActualActor'), stageWorld = capture('stageBounds', 'getWorldBinding');
  const terrainGlobals = capture('stageBounds', 'getTerrainGlobals');
  const match = record(matchGlobals(), 'match globals80433934') as SourceActorMatrixUpdateGlobals;
  const terrain = record(terrainGlobals(), 'terrain globals8043625c') as SourceActorTerrainGlobals;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const byte = (value: unknown, key: string): number => {
    const result = read(value, key);
    if (typeof result !== 'number' || !Number.isInteger(result) || result < 0 || result > 255)
      fail(`${key}: raw byte out of bounds`);
    return result === 0 ? 0 : result;
  };
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  interface Entry {
    actual: RomActor; position: object; savedPosition: object; world: SourceActorWorldMatrixBinding;
    mapping: object; matrix: SourceActorMatrixUpdateBinding;
  }
  const actorOwners = (e: Entry): object[] => [e.actual, e.position, e.savedPosition, e.world, e.mapping, e.matrix];
  const noShadowOwners = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['pos', e.actual], ['savedGroundPos', e.actual], ['supportContact1db', e.actual],
      ['hoverOffset668', e.actual], ['yVel', e.actual], ['byteD9', match], ['upper34', terrain],
    ]);
    const aliases = ['airborneNoFloor1db', 'byte1db', 'field1db', 'field24', 'positionY24',
      'field668', 'hover668', 'field48', 'yVel48', 'field30', 'savedY30', 'globalD9', 'fieldD9'];
    for (const owner of [...actorOwners(e), match, terrain]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing ceiling-lifecycle storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing ceiling-lifecycle storage alias`);
        check();
      }
    }
  };
  const checkOwners = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(matrixActor(id), e.actual, 'matrix actor'); stable(matrixWorld(id), e.world, 'matrix world');
    stable(matrixMapping(id), e.mapping, 'matrix mapping'); stable(matrixBinding(id), e.matrix, 'matrix binding');
    stable(stageActor(id), e.actual, 'stage actor'); stable(stageWorld(id), e.world, 'stage world');
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned ceiling-lifecycle actor'); return value;
  };
  const runtime: SourceActorCeilingLifecycleRuntime = {
    bindActor(id) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source ceiling-lifecycle runtime');
      const e: Entry = {actual, position: record(read(actual, 'pos'), 'actual position'),
        savedPosition: record(read(actual, 'savedGroundPos'), 'actual saved position'),
        world: record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding,
        mapping: record(worldMapping(id), 'mapping actor'),
        matrix: record(matrixBinding(id), 'matrix binding') as SourceActorMatrixUpdateBinding};
      checkOwners(id, e);
      const records = actorOwners(e);
      if (new Set([...records, match, terrain]).size !== records.length + 2 || records.some(value => assigned.has(value)))
        fail('source owner alias: distinct actual/position/saved/world/mapping/matrix/match/terrain required');
      noShadowOwners(e); check(); actors.set(id, e);
      records.forEach(value => assigned.add(value)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getMatrixBinding(id) {return entry(id).matrix;},
    getTerrainGlobals() {return terrain;},
    getMatchGlobals() {return match;},
    updateActor(id) {return guard(() => {
      const e = entry(id), {actual} = e;
      // These borrowed-owner checks are host admission, not source scalar reads.
      checkOwners(id, e); noShadowOwners(e);
      // Genuine8008b290: lwz shared match pointer, lbz d9, return raw unsigned byte.
      stable(matchGlobals(), match, 'match globals80433934');
      if (byte(match, 'byteD9') !== 0) return 0;
      if ((byte(actual, 'supportContact1db') << 24 >> 24) !== 0) return 0;
      stable(read(actual, 'pos'), e.position, 'actual position');
      const y = f(e.position, 'y'), hover = f(actual, 'hoverOffset668');
      // 68064 pointer load precedes68068 fadds;6806c upper load follows it.
      stable(terrainGlobals(), terrain, 'terrain globals8043625c');
      const raised = addSourceFloat32(y, hover);
      if (!(raised > f(terrain, 'upper34'))) return 0;
      if (!(f(actual, 'yVel') > 0)) return 0;
      write(actual, 'yVel', 0); // Authenticated804375d0 bits00000000.
      stable(terrainGlobals(), terrain, 'terrain globals8043625c'); // 6808c reload.
      const freshHover = f(actual, 'hoverOffset668'), upper = f(terrain, 'upper34');
      stable(read(actual, 'savedGroundPos'), e.savedPosition, 'actual saved position');
      const saved = f(e.savedPosition, 'y'); // 68098 BEFORE6809c subtraction.
      const difference = addSourceFloat32(upper, -freshHover);
      stable(read(actual, 'pos'), e.position, 'actual position');
      write(e.position, 'y', saved > difference ? saved : difference);
      return 1;
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
