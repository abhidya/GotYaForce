/** Bounded 8004d08c (chunk_0006.c:2156–2212), offline only.
 * Instruction/load/store order and constants are archived ProgramDB evidence
 * (research/tools/matching-decomp/read_archived_movement_followup_evidence.py),
 * not newly verified executable bytes or live FPSCR state. RN=00 / NI=0 and
 * finite exact-f32 operands are explicit host bounds. Fused subtraction is
 * negated AFTER rounding, and the tail multiplies .7f*movement BEFORE height.
 *
 * Existing RomActor fields, mapping descriptor4b0, stream marker71d and setup
 * movement6d8 remain live in their original records. Only missing 661/66c/670,
 * descriptor bytes receive storage. World Ys may be explicitly decoded copies
 * or read directly from a fixed actual full-matrix owner; the latter is never
 * copied into a second Y table and never recomputed by movement.
 * World Y[j] means actor+8f0+j*30, NOT local pose translation or partAimAnchors.
 * The nonnegative 128-entry host extent does not model negative RAM addressing.
 * Missing storage refuses when reached, with prior stores preserved.
 *
 * Direct RomActor binding is an explicit host identity association, not proof
 * of production hydration. Non-proxy own-data records and stable synchronous
 * actual getters are required. Methods/receivers and shared records are fixed
 * at binding; readonly inputs are allowed, destinations checked at each store.
 * Caught same-runtime mutation reentry poisons the enclosing operation.
 */
import type {RomActor} from './actor.js';
import type {SourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceStreamWaitRuntime} from './stream-wait.js';
import type {SourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';

export interface SourceActorMovementFollowupBinding {byte661: number; field66c: number; field670: number}
/** Raw unsigned byte bits. Joint indices sign-extend at their source reads;
 * optional correction bytes retain exact bits and are demanded only when used. */
export interface SourceActorMovementDescriptorBinding {
  joint0f: number; joint22: number; joint2a: number; joint32: number; joint3a: number;
  byte23?: number; byte24?: number; byte25?: number; byte26?: number; byte27?: number;
  byte2b?: number; byte2c?: number; byte2d?: number; byte2e?: number; byte2f?: number;
  byte33?: number; byte34?: number; byte35?: number; byte36?: number; byte37?: number;
  byte3b?: number; byte3c?: number; byte3d?: number; byte3e?: number; byte3f?: number;
}
const TERRAIN_DESCRIPTOR_BYTES = [
  'byte23', 'byte24', 'byte25', 'byte26', 'byte27',
  'byte2b', 'byte2c', 'byte2d', 'byte2e', 'byte2f',
  'byte33', 'byte34', 'byte35', 'byte36', 'byte37',
  'byte3b', 'byte3c', 'byte3d', 'byte3e', 'byte3f',
] as const;
export interface SourceActorMovementFollowupSources {
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getDescriptor'>;
  waits: Pick<SourceStreamWaitRuntime, 'getActorBinding'>;
  setup: Pick<SourceActorAnimationSetupRuntime, 'getActorBinding'>;
  matrixOwner?: Pick<SourceActorJointMatrixRuntime, 'getMatrix'>;
}
export interface SourceActorMovementFollowupRuntime {
  bindActor(identity: symbol, actor: RomActor, initial: Readonly<SourceActorMovementFollowupBinding>): void;
  /** Actual bound owner, never a copy; supports composition identity checks. */
  getActualActor(identity: symbol): RomActor;
  /** Retained source records for exact setup/postamble composition, never copies. */
  getMappingActor(identity: symbol): object;
  getSetupBinding(identity: symbol): object;
  getWaitBinding(identity: symbol): object;
  getActorBinding(identity: symbol): SourceActorMovementFollowupBinding;
  bindDescriptor(identity: symbol, initial: Readonly<SourceActorMovementDescriptorBinding>): void;
  getDescriptorBinding(identity: symbol): SourceActorMovementDescriptorBinding;
  /** Copied decoded world-matrix storage, once bound. No default matrices. */
  bindWorldMatrixY(identity: symbol, values: readonly number[]): void;
  getWorldMatrixY(identity: symbol): number[];
  /** Alternative binding to actual full matrices. Reads element7 lazily without
   * copying Ys or recomputing matrices. Cannot coexist with decoded Y storage. */
  bindWorldMatrices(identity: symbol, matrices: readonly symbol[]): void;
  updateActor(identity: symbol): void;
}
const genuineRuntimes = new WeakSet<object>();
export function isSourceActorMovementFollowupRuntime(value: unknown): value is SourceActorMovementFollowupRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {throw Error(`[actor-movement-followup] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, max: number, key: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${key}: unsigned integer out of bounds`);
  return value;
}
function float(value: unknown, key: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${key}: finite exact source float32 required`);
  return value;
}
function pointer(value: unknown): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail('descriptor4b0: decoded symbol or null required');
  return value;
}
function product(a: number, b: number): number {
  // A finite binary32 product fits exactly in binary64 before this single
  // rounding. No intermediate underflow occurs in binary64 for f32 operands.
  return float(Math.fround(a * b), 'fmuls result');
}
export function createSourceActorMovementFollowupRuntime(sources: SourceActorMovementFollowupSources): SourceActorMovementFollowupRuntime {
  let busy = false, poisoned = false;
  const read = (record: unknown, key: string): unknown => {
    const value = own(record, key); if (poisoned) fail('caught same-runtime reentry'); return value;
  };
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); if (poisoned) fail('caught same-runtime reentry');
    (record as Record<string, unknown>)[key] = value;
    if (poisoned) fail('caught same-runtime reentry');
  };
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); if (poisoned) fail('caught same-runtime reentry');} finally {busy = false;}
  };
  const capture = (name: keyof SourceActorMovementFollowupSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {
      const result = Reflect.apply(fn, receiver, [id]);
      if (poisoned) fail('caught same-runtime reentry');
      if (result instanceof Promise) fail('adapter must complete synchronously');
      if (result === null || typeof result !== 'object') fail('adapter must return an actual owned record');
      return result;
    };
  };
  const getMapping = capture('mapping', 'getActor'), getDescriptor = capture('mapping', 'getDescriptor');
  const getWait = capture('waits', 'getActorBinding'), getSetup = capture('setup', 'getActorBinding');
  const getMatrix = Object.getOwnPropertyDescriptor(sources, 'matrixOwner') === undefined ? null : capture('matrixOwner', 'getMatrix');
  const actors = new Map<symbol, {actual: RomActor; mapping: unknown; wait: unknown; setup: unknown; binding: SourceActorMovementFollowupBinding}>();
  const assignedActors = new WeakSet<object>();
  const descriptors = new Map<symbol, SourceActorMovementDescriptorBinding>(), matrices = new Map<symbol, number[]>();
  const matrixPools = new Map<symbol, {ids: readonly symbol[]; records: readonly unknown[]}>();
  const actorEntry = (id: symbol) => {const entry = actors.get(id); if (!entry) fail('unknown/non-owned movement actor'); return entry;};
  const descriptorEntry = (id: symbol | null) => {
    const entry = id === null ? undefined : descriptors.get(id);
    if (!entry) fail('descriptor byte requires an owned bound mapping descriptor'); return entry;
  };
  const matrixEntry = (id: symbol) => {actorEntry(id); const entry = matrices.get(id); if (!entry) fail('world-matrix Y storage must be explicitly bound'); return entry;};
  const byte = (record: unknown, key: string) => integer(read(record, key), 255, key);
  const signed = (record: unknown, key: string) => (byte(record, key) << 24) >> 24;
  const f = (record: unknown, key: string) => float(read(record, key), key);
  const worldY = (id: symbol, index: number): number => {
    if (index < 0) fail('negative world-matrix addressing is unsupported');
    const pool = matrixPools.get(id);
    if (pool) {
      if (index >= pool.ids.length) fail('world-matrix addressing outside explicitly owned storage');
      const record = getMatrix!(pool.ids[index]!);
      if (record !== pool.records[index]) fail('matrix owner changed its actual record');
      if (read(record, 'length') !== 12) fail('full world matrix must retain 12 elements');
      return f(record, '7');
    }
    const table = matrixEntry(id), length = integer(read(table, 'length'), 128, 'world-matrix length');
    if (index >= length) fail('world-matrix addressing outside explicitly owned storage');
    return f(table, String(index));
  };
  const runtime: SourceActorMovementFollowupRuntime = {
    bindActor(id: symbol, actual: RomActor, initial: Readonly<SourceActorMovementFollowupBinding>): void {guard(() => {
      if (actors.has(id)) fail('actor already bound');
      if (actual === null || typeof actual !== 'object') fail('actual RomActor data record required');
      if (assignedActors.has(actual)) fail('actual RomActor already assigned to a source identity');
      const mapping = getMapping(id), wait = getWait(id), setup = getSetup(id);
      const byte661 = byte(initial, 'byte661'), field66c = f(initial, 'field66c'), field670 = f(initial, 'field670');
      actors.set(id, {actual, mapping, wait, setup, binding: Object.seal({byte661, field66c, field670})});
      assignedActors.add(actual);
    });},
    getActualActor(id: symbol) {return actorEntry(id).actual;},
    getMappingActor(id: symbol) {return actorEntry(id).mapping as object;},
    getSetupBinding(id: symbol) {return actorEntry(id).setup as object;},
    getWaitBinding(id: symbol) {return actorEntry(id).wait as object;},
    getActorBinding(id: symbol) {return actorEntry(id).binding;},
    bindDescriptor(id: symbol, initial: Readonly<SourceActorMovementDescriptorBinding>): void {guard(() => {
      if (descriptors.has(id)) fail('descriptor already bound');
      getDescriptor(id); // Identity belongs to the actual mapping descriptor owner.
      const binding = {} as SourceActorMovementDescriptorBinding;
      for (const key of ['joint0f', 'joint22', 'joint2a', 'joint32', 'joint3a'] as const) binding[key] = byte(initial, key);
      for (const key of TERRAIN_DESCRIPTOR_BYTES) {
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = byte(initial, key);
      }
      descriptors.set(id, Object.seal(binding));
    });},
    getDescriptorBinding(id: symbol) {return descriptorEntry(id);},
    bindWorldMatrixY(id: symbol, values: readonly number[]): void {guard(() => {
      actorEntry(id); if (matrices.has(id) || matrixPools.has(id)) fail('world-matrix Y storage already bound');
      if (!Array.isArray(values)) fail('world-matrix Y array required');
      const length = integer(read(values, 'length'), 128, 'world-matrix length'), copied: number[] = [];
      for (let i = 0; i < length; i++) copied.push(f(values, String(i)));
      matrices.set(id, Object.seal(copied));
    });},
    getWorldMatrixY: matrixEntry,
    bindWorldMatrices(id: symbol, values: readonly symbol[]): void {guard(() => {
      actorEntry(id); if (matrices.has(id) || matrixPools.has(id)) fail('world-matrix storage already bound');
      if (!getMatrix) fail('actual matrix owner must be supplied');
      if (!Array.isArray(values)) fail('matrix identity array required');
      const length = integer(read(values, 'length'), 128, 'world-matrix length');
      const ids: symbol[] = [], records: unknown[] = [];
      for (let i = 0; i < length; i++) {
        const matrix = read(values, String(i));
        if (typeof matrix !== 'symbol') fail('actual matrix symbol required');
        const record = getMatrix(matrix);
        if (read(record, 'length') !== 12) fail('full world matrix must retain 12 elements');
        ids.push(matrix); records.push(record);
      }
      matrixPools.set(id, {ids: Object.freeze(ids), records: Object.freeze(records)});
    });},
    updateActor(id: symbol): void {guard(() => {
      const actor = actorEntry(id), actual = actor.actual;
      // lbz +3e8 is the HIGH byte of the existing big-endian borgNumber u16.
      if ((integer(read(actual, 'borgNumber'), 0xffff, 'borgNumber') >>> 8) === 5 ||
          byte(actor.binding, 'byte661') !== 0 ||
          (integer(read(actual, 'controlWord'), 0xffffffff, 'controlWord') & 0x40) === 0) {
        write(actual, 'stepHeight', 0); return;
      }
      const marker = signed(actor.wait, 'marker71d');
      if (marker !== 0) {
        // The signed-byte-minus-one conversion is exact; scale is loaded before
        // the two source-rounded products. No normal-path fields are consumed.
        const scale = f(actual, 'modelScale');
        write(actual, 'stepHeight', product(product(5, marker - 1), scale)); return;
      }
      // Retain the first descriptor+22 list separately from the later +f load.
      const list = pointer(read(actor.mapping, 'descriptor4b0'));
      const clearance = f(actor.binding, 'field670');
      const initialY = worldY(id, 1);
      write(actual, 'stepHeight', initialY);
      const halfHeight = f(actor.binding, 'field66c'), previous = f(actual, 'stepHeight');
      write(actual, 'stepHeight', -fusedMultiplyAddSourceFloat32(halfHeight, 0.5, -previous));
      const root = pointer(read(actor.mapping, 'descriptor4b0'));
      const position = f(read(actual, 'pos'), 'y');
      const rootIndex = signed(descriptorEntry(root), 'joint0f');
      const beforeRoot = f(actual, 'stepHeight');
      const rootY = worldY(id, rootIndex);
      const rootHeight = fusedMultiplyAddSourceFloat32(addSourceFloat32(rootY, -position), 0.5, position);
      if (rootHeight < beforeRoot) write(actual, 'stepHeight', rootHeight);
      for (const key of ['joint22', 'joint2a', 'joint32', 'joint3a'] as const) {
        const index = signed(descriptorEntry(list), key);
        if (index === -1) break;
        const beforeJoint = f(actual, 'stepHeight');
        const jointY = worldY(id, index), height = addSourceFloat32(jointY, -clearance);
        if (height < beforeJoint) write(actual, 'stepHeight', height);
      }
      const beforeRelative = f(actual, 'stepHeight'), currentPosition = f(read(actual, 'pos'), 'y');
      write(actual, 'stepHeight', addSourceFloat32(beforeRelative, -currentPosition));
      const movement = f(actor.setup, 'movement6d8'), relative = f(actual, 'stepHeight');
      write(actual, 'stepHeight', product(relative, product(0.699999988079071, movement)));
      if (f(actual, 'stepHeight') < 0) write(actual, 'stepHeight', 0);
    });},
  };
  genuineRuntimes.add(runtime);
  return Object.freeze(runtime);
}
