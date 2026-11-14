/** Explicit bounded 46698 caller plus ungated 46754, 46bd0 and 47a2c stages.
 * Mode0 traverses 4679c; mode1 performs bounded 46914 correction scans and
 * genuine bounded 47368 placement and 4784c terrain orientation through
 * explicitly bound real owners. General IK, ticks, JObj traversal and pose
 * setup remain outside this module. Callers choose every refresh point.
 * Evidence: research/decomp/jobj-world-matrix-integration-2026-11-13.md and
 * read_archived_actor_traversal_evidence.py. Additional stages follow
 * normal-actor-matrix-evidence-2026-11-13.md / read_archived_normal_matrix_evidence.py
 * and chunk_0005.c:2986–3310,3696–3716. Secondary4784c follows the
 * authenticated read_archived_terrain_orientation_evidence.py span. Its
 * orientation domain is the matrix owner's explicit flat-normal (2,1) subset,
 * with no idealized normalization shortcut. Primary47368 follows
 * primary-terrain-placement-evidence-2026-11-13.md and
 * primary-positive-bending-evidence-2026-11-13.md: retained pairs2/.5 or1/1,
 * target displacement (±0,1,±0), axes2/1 and signed bend1..3. This does not
 * promise endpoint contact. Ordinary matrix arithmetic retains
 * the exact identity-quaternion/zero-short domain, RN00/NI0, raw
 * floating GQR0 and signed-short, scale-zero GQR5 assumptions. None establish
 * live machine state, general trig, RAM aliases or original replay parity.
 *
 * Actual RomActor pos/bodyPitch/heading/steerYaw/stepHeight and bank-zero poses
 * remain live. Missing matrix fields are copied explicitly; corrected counts
 * retain the actual once-bound controller record, with no default state.
 * Joint1 correction X aliases actual steerYaw at+18da; no shadow X is retained.
 * Short binding fields are signed decoded values; existing BAM16 fields hold
 * unsigned bits and are sign-extended. Topology stores four raw bytes, but only
 * byte0/byte1 are consumed. A disabled joint still traverses both links.
 * The recursive byte1 branch receives the INCOMING parent; byte0 continuation
 * receives the current joint. Primary success additionally skips that byte0
 * node, visits its byte1 with the current joint as parent, then continues at
 * its byte0 using the skipped node as parent. Repeated nodes execute repeatedly,
 * subject to a host visit budget. No eager graph validation changes completed prefixes.
 *
 * Inputs/adapters must be non-proxy own-data records, stable, synchronous and
 * actual owners. Captured methods retain their receiver. Matrix storage must
 * be the same owner used by movement, with distinct slots/copies/scratch and no
 * cross-actor aliases. Per-access validation and caught-reentry poison are
 * host admission bounds. Failures preserve completed writes, never roll back.
 */
import type {RomActor} from './actor.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import type {SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import type {SourceActorTerrainQueryRuntime} from './actor-terrain-query.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointVector} from './joint-animation-feedback.js';
import {addSourceFloat32} from './source-float.js';

export interface SourceActorWorldMatrixBinding {
  mode4a0: number;
  mode4a1: number;
  flags48a: number;
  mask1d70: number;
  /** Decoded signed shorts, unlike RomActor's unsigned BAM16 bits. */
  roll74: number;
  yawOffset6b8: number;
  readonly scale58: SourceJointVector;
  readonly offset1dbc: SourceJointVector;
  readonly adjusted1d54: SourceJointVector;
  readonly preRotation1d64: SourceJointVector;
}
export interface SourceActorWorldMatrixCorrection {
  /** Required except for joint1, whose X is actual RomActor.steerYaw (+18da). */
  x?: number;
  y: number;
  z: number;
}
export interface SourceActorPrimaryTerrainCorrection extends SourceJointVector {
  joint0c: number;
  axis0d: number;
  axis0e: number;
  bend0f: number;
}
export interface SourceActorSecondaryTerrainCorrection {
  joint00: number;
  axis01: number;
  axis02: number;
  padding03: number;
}
export interface SourceActorCorrectedTraversalState {
  /** Raw bytes retained on the actual controller-owned record, not copied. */
  count1d96: number;
  count1d97: number;
  /** Explicit actual controller slots, never defaulted or copied here. Only
   * reached scan joints are read; other bytes/vectors remain lazy. */
  readonly primary1a14?: readonly SourceActorPrimaryTerrainCorrection[];
  readonly secondary1a94?: readonly SourceActorSecondaryTerrainCorrection[];
}
export interface SourceActorTerrainCorrectionSources {
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActorBinding'>;
  terrain: Pick<SourceActorTerrainQueryRuntime, 'queryNormal8003de80'>;
}
export interface SourceActorWorldMatrixStorage {
  readonly matrices8d4: readonly symbol[];
  readonly copy114: symbol;
  readonly copy1aa4: symbol;
  readonly scratch: symbol;
  readonly topology1994: readonly (readonly number[])[];
  readonly corrections18d4: readonly SourceActorWorldMatrixCorrection[];
  readonly scales15d4: readonly SourceJointVector[];
}
export interface SourceActorWorldMatrixSources {
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getLayout'>;
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getPose'>;
  matrices: SourceActorJointMatrixRuntime;
}
export interface SourceActorWorldMatrixRuntime {
  bindActor(identity: symbol, actual: RomActor, initial: Readonly<SourceActorWorldMatrixBinding>,
    storage: SourceActorWorldMatrixStorage): void;
  getActualActor(identity: symbol): RomActor;
  /** Retained source matrix runtime, not a replacement transform adapter. */
  getMatricesRuntime(): SourceActorJointMatrixRuntime;
  /** Same retained mapping header, for identity-preserving composition. */
  getMappingActor(identity: symbol): object;
  getActorBinding(identity: symbol): SourceActorWorldMatrixBinding;
  /** Live owned record, with lazy element reads left to the caller. */
  getWorldMatrix(identity: symbol, index: number): readonly number[];
  getStorage(identity: symbol): SourceActorWorldMatrixStorage;
  /** Once-only binding to the actual controller owner; no default scan state. */
  bindCorrectedTraversalState(identity: symbol, actualState: SourceActorCorrectedTraversalState): void;
  /** Once-only late binding, after real movement/terrain owners exist. */
  bindTerrainCorrectionSources(identity: symbol, sources: SourceActorTerrainCorrectionSources): void;
  /** Ungated 46754, separate from both rebuild passes. */
  prepareActor(identity: symbol): void;
  /** Ungated 46bd0; mode1 scans only reached explicitly owned slots. */
  rebuildActor(identity: symbol, mode: 0 | 1): void;
  /** 47a2c copies only world slots, with a fresh signed source count each test. */
  copyActorMatrices(sourceIdentity: symbol, targetIdentity: symbol | null): void;
  /** The explicit 46698 caller only; no per-frame deduplication or auto-refresh. */
  updateActor(identity: symbol): void;
}
const sourceWorldMatrixRuntimes = new WeakSet<object>();
export function isSourceActorWorldMatrixRuntime(value: unknown): value is SourceActorWorldMatrixRuntime {
  return value !== null && typeof value === 'object' && sourceWorldMatrixRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-world-matrix] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const descriptor = Object.getOwnPropertyDescriptor(record, key);
  if (!descriptor || !('value' in descriptor)) fail(`${key}: own data property required`);
  if (writable && !descriptor.writable) fail(`${key}: non-writable field is unsupported`);
  return descriptor.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite source float32 required`);
  return value;
}
function symbol(value: unknown, where: string): symbol {
  if (typeof value !== 'symbol') fail(`${where}: actual owned symbol required`); return value;
}
export function createSourceActorWorldMatrixRuntime(sources: SourceActorWorldMatrixSources,
  maxVisits = 4096): SourceActorWorldMatrixRuntime {
  if (!Number.isSafeInteger(maxVisits) || maxVisits < 1) fail('positive safe traversal budget required');
  const matricesRuntime = own(sources, 'matrices') as SourceActorJointMatrixRuntime;
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const byte = (record: unknown, key: string): number => integer(read(record, key), 0, 255, key);
  const signedByte = (record: unknown, key: string): number => (byte(record, key) << 24) >> 24;
  const short = (record: unknown, key: string): number => integer(read(record, key), -32768, 32767, key);
  const bam = (record: unknown, key: string): number => (integer(read(record, key), 0, 65535, key) << 16) >> 16;
  const f = (record: unknown, key: string): number => float(read(record, key), key);
  const capture = (name: keyof SourceActorWorldMatrixSources, key: string) => {
    const receiver = own(sources, name), method = own(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const mappingGet = capture('mapping', 'getActor'), layoutGet = capture('mapping', 'getLayout');
  const poseGet = capture('feedback', 'getPose'), matrixGet = capture('matrices', 'getMatrix');
  const identity = capture('matrices', 'identity'), translate = capture('matrices', 'translate');
  const correct = capture('matrices', 'correctShort'), scale = capture('matrices', 'scale');
  const copy = capture('matrices', 'copy'), rotate = capture('matrices', 'rotateShort'), compose = capture('matrices', 'composeJoint');
  const composePose = capture('matrices', 'composePose');
  const transformPoint = capture('matrices', 'transformPoint'), orientTerrain = capture('matrices', 'orientTerrainMatrix');
  const primaryPlacement = capture('matrices', 'primaryFoldedPlacement');
  const effect = (fn: (...args: unknown[]) => unknown, ...args: unknown[]): void => {
    if (fn(...args) !== undefined) fail('matrix effect must complete synchronously and return undefined');
  };
  const array = (value: unknown, max: number, where: string): readonly unknown[] => {
    if (!Array.isArray(value)) fail(`${where}: array data required`);
    integer(read(value, 'length'), 0, max, `${where} length`); return value;
  };
  const vector = (value: unknown, shorts: boolean): SourceJointVector => Object.seal({
    x: shorts ? short(value, 'x') : f(value, 'x'),
    y: shorts ? short(value, 'y') : f(value, 'y'),
    z: shorts ? short(value, 'z') : f(value, 'z'),
  });
  interface Entry {
    actual: RomActor; position: object; mapping: object; layout: object;
    poses: readonly symbol[]; poseRecords: readonly object[];
    binding: SourceActorWorldMatrixBinding; storage: SourceActorWorldMatrixStorage;
    matrices: ReadonlyMap<symbol, object>;
    corrected?: SourceActorCorrectedTraversalState;
    correctionArrays: Map<string, readonly unknown[]>;
    correctionRecords: Map<string, object>;
    terrainCorrection?: {movement: object; getMovement: (...args: unknown[]) => unknown;
      queryNormal: (...args: unknown[]) => unknown};
  }
  const actors = new Map<symbol, Entry>(), assignedActors = new WeakSet<object>();
  const assignedCorrectedStates = new WeakSet<object>(), assignedMovementStates = new WeakSet<object>();
  const assignedCorrectionStorage = new WeakMap<object, Entry>();
  const assignedMatrixIds = new Set<symbol>(), assignedMatrixRecords = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned world-matrix actor'); return value;};
  const slot = <T>(values: readonly T[], index: number, where: string): T => {
    if (!Number.isInteger(index) || index < 0 || index >= values.length) fail(`${where}: addressing outside explicitly owned storage`);
    return read(values, String(index)) as T;
  };
  const matrix = (actor: Entry, id: symbol): object => {
    const value = record(matrixGet(id), 'matrix owner');
    if (value !== actor.matrices.get(id)) fail('matrix owner changed its actual record');
    if (!Array.isArray(value) || read(value, 'length') !== 12) fail('full matrix must retain 12 entries');
    return value;
  };
  const matrixId = (actor: Entry, index: number): symbol => {
    const id = slot(actor.storage.matrices8d4, index, 'world matrix'); matrix(actor, id); return id;
  };
  const poseId = (actor: Entry, id: symbol, index: number): symbol => {
    // Layout identity is fixed. No inferred JObj hierarchy or bank substitution.
    if (mappingGet(id) !== actor.mapping || layoutGet(id) !== actor.layout) fail('mapping owner changed its actual record');
    const pose = slot(actor.poses, index, 'bank-zero pose');
    if (record(poseGet(pose), 'pose owner') !== actor.poseRecords[index]) fail('pose owner changed its actual record');
    return pose;
  };
  const topology = (actor: Entry, index: number): readonly number[] => slot(actor.storage.topology1994, index, 'topology');
  const correctionSlot = (actor: Entry, key: 'primary1a14' | 'secondary1a94', index: number): object => {
    const property = Object.getOwnPropertyDescriptor(actor.corrected!, key); check();
    if (!property || ('value' in property && property.value === undefined))
      fail(`positive ${key === 'primary1a14' ? 'count1d96' : 'count1d97'} IK scan is unsupported without explicitly owned ${key} slots`);
    const values = array(read(actor.corrected, key), key === 'primary1a14' ? 8 : 4, key);
    const previousArray = actor.correctionArrays.get(key), arrayOwner = assignedCorrectionStorage.get(values);
    if ((previousArray && previousArray !== values) || (arrayOwner && arrayOwner !== actor)) fail(`${key}: correction storage owner changed or aliases another actor`);
    // Arrays and records remain the controller's owners. No synthetic missing
    // entries, eager validation or copied count/slot state is introduced.
    for (const [other, otherValues] of actor.correctionArrays) if (other !== key && otherValues === values) fail(`${key}: aliased correction arrays unsupported`);
    actor.correctionArrays.set(key, values); assignedCorrectionStorage.set(values, actor);
    const value = record(slot(values, index, key), `${key} slot`), name = `${key}:${index}`;
    const previousRecord = actor.correctionRecords.get(name), recordOwner = assignedCorrectionStorage.get(value);
    if ((previousRecord && previousRecord !== value) || (recordOwner && recordOwner !== actor)) fail(`${key}: correction slot owner changed or aliases another actor`);
    for (const [other, otherValue] of actor.correctionRecords) if (other !== name && otherValue === value) fail(`${key}: aliased correction slots unsupported`);
    actor.correctionRecords.set(name, value); assignedCorrectionStorage.set(value, actor); return value;
  };
  function primaryCorrection(actor: Entry, id: symbol, current: number, parentIndex: number, index: number): void {
    const correction = correctionSlot(actor, 'primary1a14', index);
    poseId(actor, id, current);
    const translation = read(actor.poseRecords[current], 'translation');
    // 4739c loads current raw X, 473a0 reloads the matched record's joint,
    // then 473a8/473c4 load raw Y/Z. Preserve that scalar order. This local is
    // the source stack capture, never actor+1d54 or a quaternion composition.
    const x = f(translation, 'x'), base = signedByte(correction, 'joint0c') - 2;
    const local = {x, y: f(translation, 'y'), z: f(translation, 'z')};
    const destination = matrixId(actor, base), next = matrixId(actor, base + 1), end = matrixId(actor, base + 2);
    const parent = matrixId(actor, parentIndex);
    // Pointer+0xc selects the NEXT RAW POSE, independently of the record's
    // physical matrix base and independently of either topology byte.
    poseId(actor, id, current + 1);
    const nextTranslation = read(actor.poseRecords[current + 1], 'translation');
    effect(primaryPlacement, parent, destination, next, end, local, nextTranslation, correction);
  }
  function secondaryCorrection(actor: Entry, id: symbol, current: number, parentIndex: number, index: number): void {
    // 4784c reloads the selected record's joint, which addresses its target.
    // The input pointer still addresses the traversal joint's raw bank-zero
    // translation, even for joint1. No 1d54 or pre-rotation substitution occurs.
    const correction = correctionSlot(actor, 'secondary1a94', index);
    const destination = matrixId(actor, signedByte(correction, 'joint00'));
    const parent = matrixId(actor, parentIndex);
    poseId(actor, id, current);
    const translation = read(actor.poseRecords[current], 'translation');
    const local = {x: NaN, y: NaN, z: NaN}, normal = {x: NaN, y: NaN, z: NaN};
    effect(transformPoint, parent, translation, local);
    const target = matrix(actor, destination);
    write(target, '3', f(local, 'x')); write(target, '7', f(local, 'y')); write(target, '11', f(local, 'z'));
    // The real movement field is not touched until all three stores complete.
    const source = actor.terrainCorrection;
    if (!source) fail('actual terrain correction sources are not bound');
    const movement = record(source.getMovement(id), 'movement owner');
    if (movement !== source.movement) fail('movement owner changed its actual record');
    const clearance = f(movement, 'field670');
    integer(source.queryNormal(id, local, clearance, normal), 0, 1, 'normal query synchronous return');
    // The source ignores the 0/1 result. The real normal owner initializes its
    // local output even on the outside-bounds return. Axes reload afterward.
    const axisA = signedByte(correction, 'axis01'), axisB = signedByte(correction, 'axis02');
    effect(orientTerrain, destination, normal, axisA, axisB);
  }
  function prepare(actor: Entry, id: symbol): void {
    const state = actor.binding;
    // 46754's PSVECAdd loads both XY pairs before storing XY, and only then
    // loads Z. An invalid Z retains the completed XY pair, before root work.
    if ((byte(state, 'flags48a') & 6) === 0) {
      poseId(actor, id, 1);
      const translation = read(actor.poseRecords[1], 'translation');
      const x = f(translation, 'x'), y = f(translation, 'y');
      const ox = f(state.offset1dbc, 'x'), oy = f(state.offset1dbc, 'y');
      const rx = addSourceFloat32(x, ox), ry = addSourceFloat32(y, oy);
      write(state.adjusted1d54, 'x', rx); write(state.adjusted1d54, 'y', ry);
      const z = f(translation, 'z'), oz = f(state.offset1dbc, 'z');
      write(state.adjusted1d54, 'z', addSourceFloat32(z, oz));
    } else write(state.adjusted1d54, 'y', 20); // authenticated 80437098 = 41a00000
  }
  function rebuild(actor: Entry, id: symbol, mode: 0 | 1): void {
    const state = actor.binding, storage = actor.storage;

    const root = matrixId(actor, 0);
    effect(identity, root);
    const position = read(actor.actual, 'pos');
    if (position !== actor.position) fail('actual position record changed');
    effect(translate, root, position);
    let x: number, y: number, z: number;
    const offset = byte(state, 'mode4a1') === 0 ? short(state, 'yawOffset6b8') : 0;
    if (offset !== 0) {
      // Corrected branch loads heading before pitch, then roll, then extsh.
      const heading = bam(actor.actual, 'heading'); x = bam(actor.actual, 'bodyPitch');
      const combined = heading + offset * 0x400; z = short(state, 'roll74'); y = (combined << 16) >> 16;
    } else {x = bam(actor.actual, 'bodyPitch'); y = bam(actor.actual, 'heading'); z = short(state, 'roll74');}
    effect(correct, root, {x, y, z});
    effect(scale, root, state.scale58);
    matrix(actor, storage.copy114); effect(copy, root, storage.copy114);
    matrix(actor, storage.copy1aa4); effect(copy, root, storage.copy1aa4);
    const lifted = matrix(actor, storage.copy1aa4), oldY = f(lifted, '7'), height = f(actor.actual, 'stepHeight');
    write(lifted, '7', addSourceFloat32(oldY, height));

    interface Frame {current: number; parent: number; afterBranch: boolean; skipNext: boolean}
    const stack: Frame[] = [{current: signedByte(topology(actor, 0), '0'), parent: 0, afterBranch: false, skipNext: false}];
    let visits = 0;
    while (stack.length !== 0) {
      const frame = stack[stack.length - 1]!;
      if (frame.afterBranch) {
        if (frame.skipNext) {
          // Primary46914: AFTER current byte1 recursion, load current byte0
          // at469e4, then skipped byte1 at469f8 without a negative sentinel
          // test. A negative skipped index is outside explicit host storage,
          // not successful termination. No mask/count/ordinary work occurs.
          const previous = frame.current, skipped = signedByte(topology(actor, previous), '0');
          const branch = signedByte(topology(actor, skipped), '1');
          frame.current = skipped; frame.parent = previous; frame.skipNext = false;
          if (branch >= 0) stack.push({current: branch, parent: previous, afterBranch: false, skipNext: false});
          // Once that branch returns, the ordinary continuation below reads
          // skipped byte0 at46a14 and uses the skipped joint as its parent.
          continue;
        }
        const previous = frame.current;
        frame.current = signedByte(topology(actor, previous), '0');
        frame.parent = previous; frame.afterBranch = false; continue;
      }
      if (frame.current < 0) {stack.pop(); continue;}
      if (++visits > maxVisits) fail('traversal visit budget exceeded');
      if (frame.current >= 32) fail('joint index outside bounded 32-joint domain');
      const current = frame.current;
      if ((integer(read(state, 'mask1d70'), 0, 0xffffffff, 'mask1d70') & (1 << current)) !== 0) {
        let primary = -1, secondary = -1;
        if (mode === 1) {
          if (actor.corrected === undefined) fail('actual corrected traversal state is not bound');
          // Authenticated 46914 snapshots each signed count once per enabled
          // joint. It never reads either count for a disabled joint.
          const primaryCount = signedByte(actor.corrected, 'count1d96');
          for (let i = 0; i < primaryCount; i++) {
            if (signedByte(correctionSlot(actor, 'primary1a14', i), 'joint0c') - 2 === current) {primary = i; break;}
          }
          if (primary < 0) {
            const secondaryCount = signedByte(actor.corrected, 'count1d97');
            for (let i = 0; i < secondaryCount; i++) {
              if (signedByte(correctionSlot(actor, 'secondary1a94', i), 'joint00') === current) {secondary = i; break;}
            }
          }
        }
        if (primary >= 0) {
          primaryCorrection(actor, id, current, frame.parent, primary); frame.skipNext = true;
        } else if (secondary >= 0) secondaryCorrection(actor, id, current, frame.parent, secondary);
        else {
          let parent = matrixId(actor, frame.parent);
          if (current === 1) {
            matrix(actor, storage.scratch);
            effect(rotate, 'z', parent, storage.scratch, short(state.preRotation1d64, 'z'));
            effect(rotate, 'x', storage.scratch, storage.scratch, short(state.preRotation1d64, 'x'));
            effect(rotate, 'y', storage.scratch, storage.scratch, short(state.preRotation1d64, 'y'));
            parent = storage.scratch;
          }
          const destination = matrixId(actor, current), pose = poseId(actor, id, current);
          const correction = slot(storage.corrections18d4, current, 'joint correction');
          const scaling = slot(storage.scales15d4, current, 'joint scale');
          if (current === 1) {
            effect(composePose, parent, destination, pose, state.adjusted1d54);
            // 46dd4 loads its correction arguments after the first Concat.
            // +18da is actual steerYaw, not an independently owned X short.
            const x = bam(actor.actual, 'steerYaw'), y = short(correction, 'y'), z = short(correction, 'z');
            effect(correct, destination, {x, y, z});
            effect(scale, destination, scaling);
          } else effect(compose, parent, destination, pose, correction, scaling);
        }
      }
      const branch = signedByte(topology(actor, current), '1');
      frame.afterBranch = true;
      if (branch >= 0) stack.push({current: branch, parent: frame.parent, afterBranch: false, skipNext: false});
    }
  }
  const runtime: SourceActorWorldMatrixRuntime = Object.freeze({
    getMatricesRuntime() {return matricesRuntime;},
    bindActor(id: symbol, actual: RomActor, initial: Readonly<SourceActorWorldMatrixBinding>, storage: SourceActorWorldMatrixStorage): void {guard(() => {
      symbol(id, 'actor'); record(actual, 'actual RomActor');
      if (actors.has(id)) fail('world-matrix actor already bound');
      if (assignedActors.has(actual)) fail('actual RomActor already bound to another identity');
      const mapping = record(mappingGet(id), 'mapping actor'), layout = record(layoutGet(id), 'mapping layout');
      const banks = array(read(layout, 'poses'), 2, 'pose banks');
      if (banks.length !== 2) fail('two actual mapping pose banks required');
      const bank0 = array(read(banks, '0'), 32, 'bank-zero poses'), poses: symbol[] = [], poseRecords: object[] = [];
      for (let i = 0; i < bank0.length; i++) {
        const pose = symbol(read(bank0, String(i)), 'bank-zero pose');
        poses.push(pose); poseRecords.push(record(poseGet(pose), 'pose owner'));
      }
      const binding: SourceActorWorldMatrixBinding = {
        mode4a0: byte(initial, 'mode4a0'), mode4a1: byte(initial, 'mode4a1'), flags48a: byte(initial, 'flags48a'),
        mask1d70: integer(read(initial, 'mask1d70'), 0, 0xffffffff, 'mask1d70'),
        roll74: short(initial, 'roll74'), yawOffset6b8: short(initial, 'yawOffset6b8'),
        scale58: vector(read(initial, 'scale58'), false), offset1dbc: vector(read(initial, 'offset1dbc'), false),
        adjusted1d54: vector(read(initial, 'adjusted1d54'), false), preRotation1d64: vector(read(initial, 'preRotation1d64'), true),
      };
      // Owned vector identities cannot be replaced, but their scalar fields stay live.
      for (const key of ['scale58', 'offset1dbc', 'adjusted1d54', 'preRotation1d64']) Object.defineProperty(binding, key, {writable: false});
      Object.seal(binding);
      const matrices = new Map<symbol, object>(), records = new Set<object>();
      const claim = (value: unknown): symbol => {
        const id = symbol(value, 'matrix'), valueRecord = record(matrixGet(id), 'matrix owner');
        if (!Array.isArray(valueRecord) || read(valueRecord, 'length') !== 12) fail('full matrix must contain 12 entries');
        if (matrices.has(id) || assignedMatrixIds.has(id) || records.has(valueRecord) || assignedMatrixRecords.has(valueRecord)) fail('aliased matrix storage is unsupported');
        matrices.set(id, valueRecord); records.add(valueRecord); return id;
      };
      const inputMatrices = array(read(storage, 'matrices8d4'), 32, 'world matrices'), matrixIds: symbol[] = [];
      for (let i = 0; i < inputMatrices.length; i++) matrixIds.push(claim(read(inputMatrices, String(i))));
      const copy114 = claim(read(storage, 'copy114')), copy1aa4 = claim(read(storage, 'copy1aa4')), scratch = claim(read(storage, 'scratch'));
      const inputTopology = array(read(storage, 'topology1994'), 32, 'topology'), rows: number[][] = [];
      for (let i = 0; i < inputTopology.length; i++) {
        const row = array(read(inputTopology, String(i)), 4, 'topology row');
        if (row.length !== 4) fail('topology row requires four raw bytes');
        rows.push(Object.seal([byte(row, '0'), byte(row, '1'), byte(row, '2'), byte(row, '3')]));
      }
      const correctionInput = array(read(storage, 'corrections18d4'), 32, 'corrections18d4');
      const corrections: SourceActorWorldMatrixCorrection[] = [];
      for (let i = 0; i < correctionInput.length; i++) {
        const value = read(correctionInput, String(i));
        // +18da is already actual.steerYaw. Never read or retain caller X for
        // index1, even if supplied. Y/Z are the only missing correction fields.
        corrections.push(i === 1 ? Object.seal({y: short(value, 'y'), z: short(value, 'z')}) : vector(value, true));
      }
      const scaleInput = array(read(storage, 'scales15d4'), 32, 'scales15d4');
      const scales: SourceJointVector[] = [];
      for (let i = 0; i < scaleInput.length; i++) scales.push(vector(read(scaleInput, String(i)), false));
      const ownedStorage: SourceActorWorldMatrixStorage = Object.freeze({matrices8d4: Object.freeze(matrixIds), copy114, copy1aa4, scratch,
        topology1994: Object.freeze(rows), corrections18d4: Object.freeze(corrections), scales15d4: Object.freeze(scales)});
      const position = record(read(actual, 'pos'), 'actual position');
      actors.set(id, {actual, position, mapping, layout, binding, storage: ownedStorage, matrices,
        poses: Object.freeze(poses), poseRecords: Object.freeze(poseRecords),
        correctionArrays: new Map(), correctionRecords: new Map()});
      assignedActors.add(actual);
      for (const [matrixId, value] of matrices) {assignedMatrixIds.add(matrixId); assignedMatrixRecords.add(value);}
    });},
    getActorBinding(id: symbol): SourceActorWorldMatrixBinding {return entry(id).binding;},
    getWorldMatrix(id: symbol, index: number): readonly number[] {
      let result!: readonly number[];
      guard(() => {
        const actor = entry(id), slotId = slot(actor.storage.matrices8d4, index, 'world matrix');
        result = matrix(actor, slotId) as readonly number[];
      });
      return result;
    },
    getStorage(id: symbol): SourceActorWorldMatrixStorage {return entry(id).storage;},
    getActualActor(id: symbol): RomActor {return entry(id).actual;},
    getMappingActor(id: symbol): object {return entry(id).mapping;},
    bindCorrectedTraversalState(id: symbol, actualState: SourceActorCorrectedTraversalState): void {guard(() => {
      const actor = entry(id);
      if (actor.corrected !== undefined) fail('corrected traversal state already bound');
      record(actualState, 'actual corrected traversal state');
      if (assignedCorrectedStates.has(actualState)) fail('corrected traversal state already bound to another actor');
      byte(actualState, 'count1d96'); byte(actualState, 'count1d97');
      actor.corrected = actualState; assignedCorrectedStates.add(actualState);
    });},
    bindTerrainCorrectionSources(id: symbol, sources: SourceActorTerrainCorrectionSources): void {guard(() => {
      const actor = entry(id);
      if (actor.terrainCorrection !== undefined) fail('terrain correction sources already bound');
      const capture = (name: 'movement' | 'terrain', key: string) => {
        const receiver = read(sources, name), method = read(receiver, key);
        if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
        return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
      };
      const getMovement = capture('movement', 'getActorBinding'), queryNormal = capture('terrain', 'queryNormal8003de80');
      const movement = record(getMovement(id), 'movement owner');
      if (assignedMovementStates.has(movement)) fail('movement state already bound to another actor');
      actor.terrainCorrection = {movement, getMovement, queryNormal}; assignedMovementStates.add(movement);
    });},
    prepareActor(id: symbol): void {guard(() => prepare(entry(id), id));},
    rebuildActor(id: symbol, mode: 0 | 1): void {guard(() => {
      if (mode !== 0 && mode !== 1) fail('rebuild mode must be 0 or 1');
      rebuild(entry(id), id, mode);
    });},
    copyActorMatrices(sourceId: symbol, targetId: symbol | null): void {guard(() => {
      const source = entry(sourceId);
      for (let i = 0; ; i++) {
        if (mappingGet(sourceId) !== source.mapping) fail('mapping owner changed its actual record');
        if (i >= signedByte(source.mapping, 'jointCount1d90')) break;
        // Pointer arithmetic alone does not resolve target storage. In source,
        // no target fields or matrices are accessed unless a copy is reached.
        const from = matrixId(source, i);
        const target = entry(symbol(targetId, 'matrix-copy target'));
        const to = matrixId(target, i);
        effect(copy, from, to);
      }
    });},
    updateActor(id: symbol): void {guard(() => {
      const actor = entry(id);
      if (byte(actor.binding, 'mode4a0') === 2) return;
      prepare(actor, id); rebuild(actor, id, 0);
    });},
  });
  sourceWorldMatrixRuntimes.add(runtime); return runtime;
}
