/** Explicit 8005685c transform-history snapshot, never a tick or mode hook.
 * The actual world owner supplies RomActor and its current signed-short fields.
 * Only the missing history fields are initialized here. Existing position,
 * saved position, older position and aim records remain live actual owners.
 * +cc is the current RomActor.visibilityTarget, not the normal controller's
 * +4a4 matrix-copy link. The entire transform prefix precedes its visibility
 * gate; target+83 nonzero skips both mask reads. No target controlWord is read.
 *
 * Evidence: chunk_0007.c:196–223 and the authenticated 164-byte 8005685c span
 * in read_archived_transform_history_evidence.py. Position/aim XY words
 * are both loaded before their separate stores; Z is loaded afterward. The
 * two short XY pairs each use one word load/store, followed by a halfword Z.
 * History shorts are signed decoded values; actual BAM16 inputs retain their
 * bits through sign extension. Signed-short numeric -0 normalizes to +0
 * because its source integer bits have no distinct negative zero.
 * +6d0/+6d4 uses lfs/stfs, not an integer copy.
 *
 * Finite exact-f32 values (including signed zero/subnormals), raw byte/BAM16
 * inputs, signed shorts, stable synchronous actual owners and own-data
 * non-proxy records are explicit host bounds, not raw RAM/NaN-payload or live
 * FPSCR parity. Current values are read only when reached. Each destination
 * store validates writability; the two halves of one word validate together.
 * Captured methods preserve receivers; caught reentry poisons the call.
 * Failures preserve completed writes. No animation, matrix refresh, default
 * history, frame deduplication, timer, controller gate or rollback is added.
 */
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceJointVector} from './joint-animation-feedback.js';

export interface SourceActorTransformHistoryBinding {
  /** Decoded signed shorts at +76/+78/+7a, preserving current BAM16 bits. */
  readonly rotation76: SourceJointVector;
  /** Decoded signed shorts at +1d6a/+1d6c/+1d6e. */
  readonly preRotation1d6a: SourceJointVector;
  previousStepHeight6d4: number;
  readonly aimOrigin524: SourceJointVector;
}
export interface SourceActorTransformHistorySources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
}
export interface SourceActorTransformHistoryRuntime {
  bindActor(identity: symbol, initial: Readonly<SourceActorTransformHistoryBinding>): void;
  getActorBinding(identity: symbol): SourceActorTransformHistoryBinding;
  /** Explicit ungated 8005685c, independent of normal/mode1 matrix updates. */
  snapshotActor(identity: symbol): void;
}
function fail(reason: string): never {
  throw Error(`[actor-transform-history] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
  return value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorTransformHistoryRuntime(sources: SourceActorTransformHistorySources): SourceActorTransformHistoryRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const writable = (value: unknown, key: string): void => {own(value, key, true); check();};
  const store = (value: object, key: string, next: number): void => {
    (value as Record<string, unknown>)[key] = next; check();
  };
  const write = (value: object, key: string, next: number): void => {writable(value, key); store(value, key, next);};
  const writeShortPair = (value: object, x: number, y: number): void => {
    // One source stw: refusal at either host half must precede both writes.
    writable(value, 'x'); writable(value, 'y'); store(value, 'x', x); store(value, 'y', y);
  };
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const byte = (value: unknown, key: string): number => integer(read(value, key), 0, 255, key);
  const short = (value: unknown, key: string): number => integer(read(value, key), -32768, 32767, key) | 0;
  const bam = (value: unknown, key: string): number => (integer(read(value, key), 0, 65535, key) << 16) >> 16;
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const receiver = own(sources, 'world');
  const capture = (key: string) => {
    const method = own(receiver, key);
    if (typeof method !== 'function') fail(`world.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const getActual = capture('getActualActor'), getWorld = capture('getActorBinding');
  const vector = (value: unknown, shorts: boolean): SourceJointVector => Object.seal({
    x: shorts ? short(value, 'x') : f(value, 'x'),
    y: shorts ? short(value, 'y') : f(value, 'y'),
    z: shorts ? short(value, 'z') : f(value, 'z'),
  });
  type ActualVector = 'pos' | 'savedGroundPos' | 'targetCache5e8' | 'aimOrigin518';
  interface Entry {
    actual: object; world: object; vectors: Readonly<Record<ActualVector, object>>;
    preRotation: object; binding: SourceActorTransformHistoryBinding;
  }
  const actors = new Map<symbol, Entry>(), assignedRecords = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const actor = actors.get(id); if (!actor) fail('unknown/non-owned transform-history actor'); return actor;};
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): object => {
    const value = record(get(id), where);
    if (value !== expected) fail(`${where} owner changed its actual record`);
    return value;
  };
  const actualVector = (actor: Entry, id: symbol, key: ActualVector): object => {
    const value = record(read(stable(getActual, id, actor.actual, 'actual RomActor'), key), key);
    if (value !== actor.vectors[key]) fail(`${key} owner changed its actual record`);
    return value;
  };
  const preRotation = (actor: Entry, id: symbol): object => {
    const value = record(read(stable(getWorld, id, actor.world, 'world'), 'preRotation1d64'), 'preRotation1d64');
    if (value !== actor.preRotation) fail('preRotation1d64 owner changed its actual record');
    return value;
  };
  const copyVector = (from: () => object, to: () => object): void => {
    const source = from(), x = f(source, 'x'), y = f(source, 'y');
    write(to(), 'x', x); write(to(), 'y', y);
    const z = f(from(), 'z'); write(to(), 'z', z);
  };
  return Object.freeze({
    bindActor(id: symbol, initial: Readonly<SourceActorTransformHistoryBinding>): void {guard(() => {
      if (typeof id !== 'symbol') fail('actual actor symbol required');
      if (actors.has(id)) fail('transform-history actor already bound');
      const actual = record(getActual(id), 'actual RomActor'), world = record(getWorld(id), 'world');
      const vectors = Object.freeze({pos: record(read(actual, 'pos'), 'pos'),
        savedGroundPos: record(read(actual, 'savedGroundPos'), 'savedGroundPos'),
        targetCache5e8: record(read(actual, 'targetCache5e8'), 'targetCache5e8'),
        aimOrigin518: record(read(actual, 'aimOrigin518'), 'aimOrigin518')});
      const pre = record(read(world, 'preRotation1d64'), 'preRotation1d64');
      const records = [actual, world, ...Object.values(vectors), pre], seen = new Set<object>();
      for (const value of records) {
        if (seen.has(value) || assignedRecords.has(value)) fail('aliased transform owner is unsupported');
        seen.add(value);
      }
      const binding: SourceActorTransformHistoryBinding = {
        rotation76: vector(read(initial, 'rotation76'), true),
        preRotation1d6a: vector(read(initial, 'preRotation1d6a'), true),
        previousStepHeight6d4: f(initial, 'previousStepHeight6d4'),
        aimOrigin524: vector(read(initial, 'aimOrigin524'), false),
      };
      // Only scalar stores are supported; destinations retain their owner.
      for (const key of ['rotation76', 'preRotation1d6a', 'aimOrigin524']) Object.defineProperty(binding, key, {writable: false});
      Object.seal(binding);
      actors.set(id, {actual, world, vectors, preRotation: pre, binding});
      for (const value of [...records, binding, binding.rotation76, binding.preRotation1d6a, binding.aimOrigin524]) assignedRecords.add(value);
    });},
    getActorBinding(id: symbol): SourceActorTransformHistoryBinding {return entry(id).binding;},
    snapshotActor(id: symbol): void {guard(() => {
      const actor = entry(id), state = actor.binding;
      copyVector(() => actualVector(actor, id, 'savedGroundPos'), () => actualVector(actor, id, 'targetCache5e8'));
      copyVector(() => actualVector(actor, id, 'pos'), () => actualVector(actor, id, 'savedGroundPos'));
      const actual = stable(getActual, id, actor.actual, 'actual RomActor');
      const pitch = bam(actual, 'bodyPitch'), heading = bam(actual, 'heading');
      writeShortPair(state.rotation76, pitch, heading);
      write(state.rotation76, 'z', short(stable(getWorld, id, actor.world, 'world'), 'roll74'));
      const pre = preRotation(actor, id), x = short(pre, 'x'), y = short(pre, 'y');
      writeShortPair(state.preRotation1d6a, x, y);
      write(state.preRotation1d6a, 'z', short(preRotation(actor, id), 'z'));
      write(state, 'previousStepHeight6d4', f(stable(getActual, id, actor.actual, 'actual RomActor'), 'stepHeight'));
      const target = read(stable(getActual, id, actor.actual, 'actual RomActor'), 'visibilityTarget');
      if (target === null) return;
      record(target, 'actual visibility target');
      if (byte(target, 'eligibility83') === 0) {
        const mask = byte(target, 'visibilityMask5e6');
        const visibility = byte(stable(getActual, id, actor.actual, 'actual RomActor'), 'visibilityBit');
        if ((mask & visibility) === 0) return;
      }
      copyVector(() => actualVector(actor, id, 'aimOrigin518'), () => state.aimOrigin524);
    });},
  });
}
