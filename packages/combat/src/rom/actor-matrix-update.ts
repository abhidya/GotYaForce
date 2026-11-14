/** Explicit bounded 800465fc normal matrix caller, never a tick hook.
 * Actual world stages execute 46754 once, then 46bd0(mode0), and optionally
 * 46e7c followed by 46bd0(mode1). 46e7c clears its actual scan counts and
 * admits 46ef4 damping (suppression or selector1), 47344 damping/addY, and
 * 47164 no-query exits, genuine query returns and explicit correction stores.
 * Other dispatch targets refuse after required argument reads. Without an
 * explicit query owner, 47164 refuses at a reached query. Correction storage
 * must be supplied explicitly; absent storage refuses before stackY/stores.
 * Primary/secondary entries share their exact owned rows with world traversal;
 * positive secondary matches can complete its bounded terrain orientation.
 * No descriptor bytes, terrain result or empty scan lists are fabricated.
 * Descriptor+22 is arithmetic-only for suppression/selector1/selector3, where
 * its base may be null or unbound; selector2 dereferences the actual binding.
 *
 * 47904 admits only its sequential flyer741, byte660 and metadata-high-nibble
 * early returns. Its active body refuses before lifecycle18 or joint12 stores.
 * The explicit shared global mask is retained by reference, never defaulted.
 * Mode1's final link invokes the actual 47a2c copy, not target recomputation.
 * Evidence: read_archived_normal_matrix_evidence.py and
 * research/decomp/normal-actor-matrix-evidence-2026-11-13.md and
 * research/decomp/terrain-matrix-handlers-evidence-2026-11-13.md and
 * research/decomp/terrain-query-evidence-2026-11-13.md.
 * The 16 indexed words are an audited address
 * window, not a proven dispatch-table allocation or permission to implement
 * other handlers. RN00/NI0, finite exact-f32 values, own-data non-proxy records,
 * stable actual owners and synchronous real effects are explicit host bounds.
 * No live FPSCR/GQR, RAM aliases, production hydration or replay parity claims.
 * Methods/receivers are captured; fields are consumed lazily and destinations
 * checked at each store. Caught reentry poisons the call. Prior work survives
 * refusal, including count clears, damping, matrix rebuilds and partial copies.
 */
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';
import type {SourceActorTerrainQueryRuntime} from './actor-terrain-query.js';
import type {SourceActorWorldMatrixRuntime, SourceActorCorrectedTraversalState,
  SourceActorPrimaryTerrainCorrection, SourceActorSecondaryTerrainCorrection} from './actor-world-matrix.js';
import type {SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import type {SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';

export interface SourceActorMatrixUpdateBinding extends SourceActorCorrectedTraversalState {
  /** Raw bytes; the corrected traversal sign-extends them when reached. */
  count1d96: number;
  count1d97: number;
  field1d60: number;
  byte660: number;
  link4a4: symbol | null;
}
export type SourceActorMatrixUpdateInitial = Omit<SourceActorMatrixUpdateBinding, 'primary1a14' | 'secondary1a94'>;
export interface SourceActorMatrixUpdateStorage {
  readonly primary1a14?: readonly Readonly<SourceActorPrimaryTerrainCorrection>[];
  readonly secondary1a94?: readonly Readonly<SourceActorSecondaryTerrainCorrection>[];
}
export interface SourceActorMatrixUpdateGlobals {maskD2: number}
export interface SourceActorMatrixUpdateSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' |
    'getWorldMatrix' | 'bindCorrectedTraversalState' | 'prepareActor' | 'rebuildActor' | 'copyActorMatrices'>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActorBinding' | 'getDescriptorBinding'>;
  metadata: Pick<SourceAnimationSetupMetadataRuntime, 'getActorBinding'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor'>;
  /** Optional explicit source query owner. Unreached query paths do not need it. */
  terrain?: Pick<SourceActorTerrainQueryRuntime, 'query8003d6e4'>;
  /** The actual battle-global record, not a copied mask or a callback. */
  globals: SourceActorMatrixUpdateGlobals;
}
export interface SourceActorMatrixUpdateRuntime {
  bindActor(identity: symbol, initial: Readonly<SourceActorMatrixUpdateInitial>, storage?: SourceActorMatrixUpdateStorage): void;
  getActorBinding(identity: symbol): SourceActorMatrixUpdateBinding;
  updateActor(identity: symbol): void;
}
// Archived ProgramDB bytes at802d0d60, all16 entries reachable by selector&15.
const DISPATCH = Object.freeze([
  0x80046f08, 0x80046ef4, 0x80047164, 0x80047344,
  0x8004871c, 0x800487ec, 0x8004892c, 0x80048a6c,
  0x80048be0, 0x80049f10, 0x8004a00c, 0x8004a0e0,
  0x8004a1cc, 0x8004a2ec, 0x8004a41c, 0x8004a60c,
]);
function fail(reason: string): never {
  throw Error(`[actor-matrix-update] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned integer out of bounds`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite exact source float32 required`);
  return value;
}
function pointer(value: unknown, where: string): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: decoded symbol or null required`);
  return value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
  return value;
}
export function createSourceActorMatrixUpdateRuntime(sources: SourceActorMatrixUpdateSources): SourceActorMatrixUpdateRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const write = (value: unknown, key: string, next: number): void => {
    own(value, key, true); check(); (value as Record<string, unknown>)[key] = next; check();
  };
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const byte = (value: unknown, key: string): number => integer(read(value, key), 255, key);
  const capture = (name: keyof SourceActorMatrixUpdateSources, key: string) => {
    const receiver = own(sources, name), method = own(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  const query = Object.getOwnPropertyDescriptor(sources, 'terrain') === undefined ? null : capture('terrain', 'query8003d6e4');
  const getWorld = capture('world', 'getActorBinding'), getActual = capture('world', 'getActualActor');
  const getMatrix = capture('world', 'getWorldMatrix'), getDescriptor = capture('movement', 'getDescriptorBinding');
  const bindCorrected = capture('world', 'bindCorrectedTraversalState');
  const prepare = capture('world', 'prepareActor'), rebuild = capture('world', 'rebuildActor');
  const copy = capture('world', 'copyActorMatrices'), getMovement = capture('movement', 'getActorBinding');
  const getMetadata = capture('metadata', 'getActorBinding'), getMapping = capture('mapping', 'getActor');
  const globals = record(own(sources, 'globals'), 'actual battle globals');
  const effect = (fn: (...args: unknown[]) => unknown, ...args: unknown[]): void => {
    if (fn(...args) !== undefined) fail('effect must complete synchronously and return undefined');
  };
  interface Entry {
    actual: object; position: object; world: object; movement: object; metadata: object; mapping: object;
    binding: SourceActorMatrixUpdateBinding;
  }
  const actors = new Map<symbol, Entry>(), assignedActors = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const actor = actors.get(id); if (!actor) fail('unknown/non-owned matrix-update actor'); return actor;};
  const stable = (getter: (...args: unknown[]) => unknown, id: symbol, expected: object, name: string): object => {
    const actual = record(getter(id), name);
    if (actual !== expected) fail(`${name} owner changed its actual record`);
    return actual;
  };
  return Object.freeze({
    bindActor(id: symbol, initial: Readonly<SourceActorMatrixUpdateInitial>, storage?: SourceActorMatrixUpdateStorage): void {guard(() => {
      if (typeof id !== 'symbol') fail('actual actor symbol required');
      if (actors.has(id)) fail('matrix-update actor already bound');
      const actual = record(getActual(id), 'actual RomActor');
      const position = record(read(actual, 'pos'), 'actual position');
      if (assignedActors.has(actual)) fail('actual RomActor already bound to another identity');
      const world = record(getWorld(id), 'world'), movement = record(getMovement(id), 'movement');
      const metadata = record(getMetadata(id), 'metadata'), mapping = record(getMapping(id), 'mapping');
      const binding: SourceActorMatrixUpdateBinding = {
        count1d96: byte(initial, 'count1d96'), count1d97: byte(initial, 'count1d97'),
        field1d60: float(read(initial, 'field1d60'), 'field1d60'), byte660: byte(initial, 'byte660'),
        link4a4: pointer(read(initial, 'link4a4'), 'link4a4'),
      };
      if (storage !== undefined) {
        for (const key of ['primary1a14', 'secondary1a94'] as const) {
          if (Object.getOwnPropertyDescriptor(storage, key) === undefined) continue;
          const input = read(storage, key);
          if (!Array.isArray(input)) fail(`${key}: explicit correction array required`);
          const length = integer(read(input, 'length'), key === 'primary1a14' ? 8 : 4, `${key} length`);
          const rows: object[] = [];
          for (let i = 0; i < length; i++) {
            const row = record(read(input, String(i)), `${key} row`);
            rows.push(Object.seal(key === 'primary1a14' ? {
              x: float(read(row, 'x'), 'primary.x'), y: float(read(row, 'y'), 'primary.y'), z: float(read(row, 'z'), 'primary.z'),
              joint0c: byte(row, 'joint0c'), axis0d: byte(row, 'axis0d'), axis0e: byte(row, 'axis0e'), bend0f: byte(row, 'bend0f'),
            } : {joint00: byte(row, 'joint00'), axis01: byte(row, 'axis01'), axis02: byte(row, 'axis02'), padding03: byte(row, 'padding03')}));
          }
          Object.defineProperty(binding, key, {value: Object.freeze(rows), enumerable: true});
        }
      }
      Object.seal(binding);
      // Counts are the controller's real missing fields, shared with46914.
      effect(bindCorrected, id, binding);
      actors.set(id, {actual, position, world, movement, metadata, mapping, binding}); assignedActors.add(actual);
    });},
    getActorBinding(id: symbol): SourceActorMatrixUpdateBinding {return entry(id).binding;},
    updateActor(id: symbol): void {guard(() => {
      const actor = entry(id), state = actor.binding;
      if (byte(stable(getWorld, id, actor.world, 'world'), 'mode4a0') === 2) return;
      effect(prepare, id);
      effect(rebuild, id, 0);
      if (byte(stable(getMovement, id, actor.movement, 'movement'), 'byte661') === 0) {
        write(state, 'count1d96', 0); write(state, 'count1d97', 0);
        const actual = stable(getActual, id, actor.actual, 'actual RomActor');
        const suppressed = (integer(read(actual, 'controlWord'), 0xffffffff, 'controlWord') & 0x20000000) !== 0;
        // The actual unsuppressed argument-load order is metadata, descriptor,
        // table lookup, descriptor+22. Suppression still loads descriptor+22.
        const selector = suppressed ? null : byte(stable(getMetadata, id, actor.metadata, 'metadata'), 'byte1d98') & 15;
        const descriptorId = pointer(read(stable(getMapping, id, actor.mapping, 'mapping'), 'descriptor4b0'), 'descriptor4b0');
        // The computed +22 pointer is not dereferenced by46ef4. Do not demand
        // descriptor storage or fabricate its contents for arithmetic alone.
        const handler = selector === null ? 0x80046ef4 : DISPATCH[selector]!;
        if (handler !== 0x80046ef4 && handler !== 0x80047164 && handler !== 0x80047344) fail(`46e7c handler ${handler.toString(16)} is outside the bounded damping domain`);
        if (handler === 0x80047164) {
          const initialBits = byte(stable(getMetadata, id, actor.metadata, 'metadata'), 'byte1d99');
          const clearance = float(read(stable(getMovement, id, actor.movement, 'movement'), 'field670'), 'field670');
          const position = record(read(stable(getActual, id, actor.actual, 'actual RomActor'), 'pos'), 'actual position');
          if (position !== actor.position) fail('actual position record changed');
          const positionY = float(read(position, 'y'), 'position.y');
          const sum = float(addSourceFloat32(positionY, clearance), 'threshold sum');
          const threshold = float(fusedMultiplyAddSourceFloat32(2, initialBits & 15, sum), 'threshold');
          let descriptor: object | undefined;
          const descriptorRawByte = (key: string): number => {
            const current = record(getDescriptor(descriptorId), 'movement descriptor');
            if (descriptor !== undefined && descriptor !== current) fail('movement descriptor owner changed its actual record');
            descriptor = current;
            return byte(current, key);
          };
          const descriptorByte = (key: string): number => (descriptorRawByte(key) << 24) >> 24;
          const element = (index: number, offset: string): number => {
            const matrix = record(getMatrix(id, index), 'world matrix');
            if (!Array.isArray(matrix) || read(matrix, 'length') !== 12) fail('full matrix must retain 12 entries');
            return float(read(matrix, offset), `world matrix.${offset}`);
          };
          let primaryCursor = 0, secondaryCursor = 0;
          const row = (name: 'primary1a14' | 'secondary1a94', index: number): object => {
            const rows = read(state, name);
            if (!Array.isArray(rows) || index >= integer(read(rows, 'length'), name === 'primary1a14' ? 8 : 4, `${name} length`)) {
              fail(`${name}: correction store outside explicit owned slots`);
            }
            return record(read(rows, String(index)), `${name} row`);
          };
          for (let i = 0; i < 4; i++) {
            const key = ['joint22', 'joint2a', 'joint32', 'joint3a'][i]!;
            const firstIndex = descriptorByte(key);
            if (firstIndex === -1) break;
            const signedBits = (byte(stable(getMetadata, id, actor.metadata, 'metadata'), 'byte1d99') << 24) >> 24;
            if ((signedBits & (1 << (i + 6))) !== 0) continue;
            const x = element(firstIndex, '3');
            const nextIndex = descriptorByte(key);
            const y = element(nextIndex, '7');
            const reachesQuery = y <= threshold;
            const z = element(nextIndex, '11');
            if (reachesQuery) {
              if (query === null) fail('47164 terrain query 8003d6e4 is unsupported before tail damping and corrected pass');
              // Real caller-local XYZ, not a new actor or terrain-result owner.
              const point = {x, y, z};
              const height = float(query(id, point, clearance), 'terrain query result');
              const contactY = float(addSourceFloat32(clearance, height), 'terrain clearance sum');
              // 47244 reloads the stack Y after the call, not the matrix or a
              // cached pre-call Y. GT alone skips correction stores; equality
              // and lower results populate the explicit source entry owners.
              const afterQueryY = float(read(point, 'y'), 'query point.y');
              if (!(afterQueryY > contactY)) {
                // Missing explicit storage retains the previous admission boundary.
                if (Object.getOwnPropertyDescriptor(state, 'primary1a14') === undefined) {
                  fail('47164 correction entry path is unsupported before stackY and persistent correction stores');
                }
                write(point, 'y', contactY);
                const entryX = float(read(point, 'x'), 'query point.x'), entryY = float(read(point, 'y'), 'query point.y');
                const primary = row('primary1a14', primaryCursor);
                write(primary, 'x', entryX); write(primary, 'y', entryY);
                write(primary, 'z', float(read(point, 'z'), 'query point.z'));
                write(primary, 'joint0c', descriptorRawByte(key));
                const base = [0x22, 0x2a, 0x32, 0x3a][i]!;
                write(primary, 'axis0d', descriptorRawByte(`byte${(base + 1).toString(16)}`));
                write(primary, 'axis0e', descriptorRawByte(`byte${(base + 2).toString(16)}`));
                write(primary, 'bend0f', descriptorRawByte(`byte${(base + 3).toString(16)}`));
                primaryCursor++;
                write(state, 'count1d96', (byte(state, 'count1d96') + 1) & 255);
                const afterBits = (byte(stable(getMetadata, id, actor.metadata, 'metadata'), 'byte1d99') << 24) >> 24;
                if ((afterBits & (1 << (i + 4))) === 0) {
                  const secondaryJoint = descriptorRawByte(key);
                  const secondary = row('secondary1a94', secondaryCursor);
                  write(secondary, 'joint00', secondaryJoint);
                  write(secondary, 'axis01', descriptorRawByte(`byte${(base + 4).toString(16)}`));
                  write(secondary, 'axis02', descriptorRawByte(`byte${(base + 5).toString(16)}`));
                  secondaryCursor++;
                  write(state, 'count1d97', (byte(state, 'count1d97') + 1) & 255);
                }
              }
            }
          }
        }
        const old = float(read(state, 'field1d60'), 'field1d60');
        // A product of finite binary32 operands is exact in binary64 before
        // this one RN-even rounding, including signed zero and subnormals.
        const damped = float(Math.fround(old * 0.800000011920929), 'fmuls result');
        write(state, 'field1d60', damped);
        if (handler === 0x80047164 || handler === 0x80047344) {
          const adjusted = record(read(stable(getWorld, id, actor.world, 'world'), 'adjusted1d54'), 'adjusted1d54');
          const y = float(read(adjusted, 'y'), 'adjusted1d54.y');
          const velocity = float(read(state, 'field1d60'), 'field1d60');
          write(adjusted, 'y', float(addSourceFloat32(y, velocity), 'adjustedY sum'));
        }
        effect(rebuild, id, 1);
      }
      const actual = stable(getActual, id, actor.actual, 'actual RomActor');
      const visibility = byte(actual, 'visibilityBit'), mask = byte(globals, 'maskD2');
      if ((visibility & mask) === 0 && byte(actual, 'flyer741') === 0 && byte(state, 'byte660') === 0 &&
          (byte(stable(getMetadata, id, actor.metadata, 'metadata'), 'byte1d98') & 0xf0) !== 0x10) {
        fail('47904 active body is unsupported before lifecycle18 and joint12 correction stores');
      }
      if (byte(stable(getWorld, id, actor.world, 'world'), 'mode4a0') === 1) {
        // 47a2c resolves the target only if a signed source-count test reaches
        // an actual copy. No target mode/count/metadata or rebuild is needed.
        effect(copy, id, pointer(read(state, 'link4a4'), 'link4a4'));
      }
    });},
  });
}
