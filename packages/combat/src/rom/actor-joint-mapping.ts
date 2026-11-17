/** Bounded actor joint mapping through the real existing-joint feedback runtime.
 * Source: 4a830/4aae0/4acdc/4b8f4, chunk_0006.c:387–611,1140–1157.
 * Stores part35, snapshots the signed range, then reloads descriptor/map/count/
 * joint bank per entry. The selected JObj is retained across advance and capture;
 * pose bank35 is read only after advancement. Repeated map entries repeat work.
 *
 * Part descriptor00 null latches completion before mirror/root/count checks.
 * Root-motion and mirrored mapping remain explicit refusals. Setup bit1 requires
 * a once-bound actual archive setup runtime.
 * Target1 translation scaling requires an explicitly bound actor+1dd4 float table.
 * This is not full actor mode execution, complete archive setup, source RAM ownership,
 * original replay or live wiring.
 *
 * Byte fields/entries contain raw unsigned byte bits; source signed-char reads
 * are sign-extended explicitly. Two banks/four inline parts and separate pose
 * and joint banks of at most 32 entries are host admission limits excluding RAM aliases.
 * Negative/out-of-layout addressing refuses only when reached. Bound records are
 * copied own-data non-proxy inputs; referenced symbolic tables remain live.
 * Adapters are fixed at construction, retain their this and must do real work or
 * refuse. No default quaternion converter or ignored required effect is installed.
 * Per-access ownership/type/writability and caught-reentry checks are host bounds.
 * Failures retain completed writes/effects. No deferred mutation is permitted.
 */
import type {SourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import type {SourceJObjAnimationRuntime, SourceJObjAnimationEffects} from './jobj-animation.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointAnimationPart, SourceJointPoseEffects} from './joint-animation-feedback.js';

export interface SourceActorJointMappingHeader {
  descriptor4b0: symbol | null;
  jointCount1d90: number;
  boundary1d91: number;
  boundary1d92: number;
  boundary1d93: number;
  jointBank1db4: symbol | null;
  jointBank1db8: symbol | null;
  timestep1dc8: number;
}
export interface SourceActorJointPartBinding {
  descriptor00: symbol | null;
  scaleIndex32: number;
  jointBank33: number;
  poseBuffer35: number;
}
export interface SourceActorJointLayout {
  readonly parts: readonly (readonly symbol[])[];
  readonly poses: readonly (readonly symbol[])[];
}
export interface SourceActorJointMappingRuntime {
  getActualFeedback(): SourceJointAnimationFeedbackRuntime;
  getActualSetup(): Pick<SourceArchiveJointSetupRuntime, 'setupActorJoint'> | undefined;
  createDescriptor(jointMap8c: readonly number[]): symbol;
  getDescriptor(identity: symbol): number[];
  createJointBank(joints: readonly (symbol | null)[]): symbol;
  getJointBank(identity: symbol): (symbol | null)[];
  createPart(initial: SourceJointAnimationPart, binding: SourceActorJointPartBinding): symbol;
  getPartBinding(identity: symbol): SourceActorJointPartBinding;
  createActor(initial: SourceActorJointMappingHeader, layout: SourceActorJointLayout): symbol;
  getActor(identity: symbol): SourceActorJointMappingHeader;
  getLayout(identity: symbol): SourceActorJointLayout;
  /** Copied inline actor+1dd4 storage, bound once; 128 entries is host policy, not a proven source extent. */
  bindScaleTable(actor: symbol, values: readonly number[]): void;
  getScaleTable(actor: symbol): number[];
  bindSetupRuntime(setup: Pick<SourceArchiveJointSetupRuntime, 'setupActorJoint'>): void;
  /** 4a754 continuation: caller has already stored poseBuffer35. */
  mapPreparedPart(actor: symbol, partBank: number, partNumber: number, operationFlags: number): void;
  animatePart(actor: symbol, partBank: number, poseBuffer: number, partNumber: number, operationFlags: number): void;
}
const genuineRuntimes = new WeakSet<object>();
export function isSourceActorJointMappingRuntime(value: unknown): value is SourceActorJointMappingRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-joint-mapping] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: object, key: string, writable = true): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, max: number, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) fail(`${where}: unsigned integer out of range`);
}
function link(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function float(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) fail(`${where}: expected finite source float32`);
}
function byte(record: object, key: string): number {const value = own(record, key); integer(value, 255, key); return value;}
function signed(record: object, key: string): number {return (byte(record, key) << 24) >> 24;}
function write(record: object, key: string, value: number): void {own(record, key); (record as Record<string, unknown>)[key] = value;}
function method(table: object, key: string): (...args: never[]) => unknown {
  const fn = own(table, key, false); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
function arrayCopy<T>(initial: readonly T[], max: number, validate: (value: unknown, key: string) => void): T[] {
  if (!Array.isArray(initial)) fail('array data required');
  const length = own(initial, 'length', false); integer(length, max, 'length');
  const output: T[] = [];
  for (let i = 0; i < length; i++) {const key = String(i), value = own(initial, key, false); validate(value, key); output.push(value as T);}
  return Object.seal(output);
}
export function createSourceActorJointMappingRuntime(joints: SourceJObjAnimationRuntime,
  feedback: SourceJointAnimationFeedbackRuntime, animationEffects: SourceJObjAnimationEffects,
  poseEffects: SourceJointPoseEffects): SourceActorJointMappingRuntime {
  const bindingGet = method(joints, 'getBinding');
  const partCreate = method(feedback, 'createPart'), partGet = method(feedback, 'getPart'), poseGet = method(feedback, 'getPose');
  const aobjGet = method(feedback, 'getAObj'), advance = method(feedback, 'advanceExistingJoint'), capture = method(feedback, 'capturePoseAndFrame');
  const interpret = method(animationEffects, 'interpretAObj'), robj = method(animationEffects, 'animateRObjs'), dobj = method(animationEffects, 'animateDObjs');
  const converter = method(poseEffects, 'convertEulerToQuaternion');
  // Wrapper calls preserve each original table receiver while fixing its function.
  const fixedAnimation = Object.freeze<SourceJObjAnimationEffects>({
    interpretAObj(aobj, owner, callback) {call('interpret AObj', () => Reflect.apply(interpret, animationEffects, [aobj, owner, callback]));},
    animateRObjs(list) {call('animate RObjs', () => Reflect.apply(robj, animationEffects, [list]));},
    animateDObjs(list) {call('animate DObjs', () => Reflect.apply(dobj, animationEffects, [list]));},
  });
  const fixedPose = Object.freeze<SourceJointPoseEffects>({
    convertEulerToQuaternion(rotation, output) {call('convert Euler', () => Reflect.apply(converter, poseEffects, [rotation, output]));},
  });
  const descriptors = new Map<symbol, number[]>(), banks = new Map<symbol, (symbol | null)[]>();
  const partBindings = new Map<symbol, SourceActorJointPartBinding>();
  const actors = new Map<symbol, SourceActorJointMappingHeader>(), layouts = new Map<symbol, SourceActorJointLayout>();
  const assignedParts = new Set<symbol>(), assignedPoses = new Set<symbol>();
  const scaleTables = new Map<symbol, number[]>();
  const getDescriptor = (id: symbol): number[] => {const value = descriptors.get(id); if (!value) fail('unknown/non-owned descriptor'); return value;};
  const getJointBank = (id: symbol): (symbol | null)[] => {const value = banks.get(id); if (!value) fail('unknown/non-owned joint bank'); return value;};
  const getPartBinding = (id: symbol): SourceActorJointPartBinding => {const value = partBindings.get(id); if (!value) fail('unknown/non-owned part binding'); return value;};
  const getActor = (id: symbol): SourceActorJointMappingHeader => {const value = actors.get(id); if (!value) fail('unknown/non-owned actor'); return value;};
  const getLayout = (id: symbol): SourceActorJointLayout => {const value = layouts.get(id); if (!value) fail('unknown/non-owned actor layout'); return value;};
  const getScaleTable = (id: symbol): number[] => {
    getActor(id); const table = scaleTables.get(id);
    if (!table) fail('translation scaling requires an explicitly bound actor+1dd4 table');
    return table;
  };
  const getPart = (id: symbol) => Reflect.apply(partGet, feedback, [id]) as SourceJointAnimationPart;
  let busy = false, reentered = false;
  const call = (name: string, fn: () => unknown): void => {
    let result: unknown; try {result = fn();} catch (e) {fail(`${name}: effect threw (${String(e)})`);}
    if (result !== undefined) fail(`${name}: effect must complete synchronously and return undefined`);
    if (reentered) fail('same-runtime reentry was caught inside an effect');
  };
  const readLink = (record: object, key: string): symbol | null => {const value = own(record, key); link(value, key); return value;};
  const index = (value: number, length: number, where: string): number => {
    if (value < 0 || value >= length) fail(`${where}: addressing outside owned layout is unsupported`);
    return value;
  };
  let setupBinding: Readonly<{receiver: Pick<SourceArchiveJointSetupRuntime, 'setupActorJoint'>; method: (...args: never[]) => unknown}> | undefined;
  const mapPart = (actorId: symbol, partBank: number, partNumber: number, operationFlags: number, poseBuffer?: number): void => {
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      integer(partBank, 1, 'partBank'); if (poseBuffer !== undefined) integer(poseBuffer, 255, 'poseBuffer'); integer(partNumber, 3, 'partNumber');
      integer(operationFlags, 0xffffffff, 'operationFlags');
      busy = true; reentered = false;
      try {
        const actor = getActor(actorId), layout = getLayout(actorId), partId = layout.parts[partBank]![partNumber]!;
        const binding = getPartBinding(partId), part = getPart(partId);
        if (poseBuffer !== undefined) write(binding, 'poseBuffer35', poseBuffer);
        const boundaries = ['jointCount1d90', 'boundary1d91', 'boundary1d92', 'boundary1d93'] as const;
        const start = partNumber === 0 ? 0 : signed(actor, boundaries[partNumber]!);
        const end = signed(actor, partNumber === 3 ? 'jointCount1d90' : boundaries[partNumber + 1]!);
        for (let ordinal = start; ordinal < end; ordinal++) {
          const descriptorId = readLink(actor, 'descriptor4b0'); if (descriptorId === null) fail('null actor descriptor is unsupported');
          const map = getDescriptor(descriptorId);
          const sourceIndex = signed(map, String(index(ordinal, map.length, 'joint map')));
          const descriptor = readLink(binding, 'descriptor00');
          if (descriptor === null) {write(part, 'complete2e', 1); continue;}
          if (byte(part, 'mirror30') !== 0) fail('mirrored joint mapping is unsupported');
          if (sourceIndex === 0) fail('root-motion joint mapping is unsupported');
          if (sourceIndex >= signed(actor, 'jointCount1d90')) continue;
          if (sourceIndex < 0) fail('negative joint addressing is unsupported');
          const jointBank = signed(binding, 'jointBank33'); index(jointBank, 2, 'joint bank');
          const bankId = readLink(actor, jointBank === 0 ? 'jointBank1db4' : 'jointBank1db8');
          if (bankId === null) fail('null joint bank is unsupported');
          const bank = getJointBank(bankId), joint = readLink(bank, String(index(sourceIndex, bank.length, 'joint table')));
          if (joint === null) fail('null mapped JObj is unsupported');
          if ((operationFlags & 1) !== 0) {
            if (!setupBinding) fail('setup branch requires a bound archive setup runtime');
            call('setup actor joint', () => Reflect.apply(setupBinding!.method, setupBinding!.receiver, [actorId, partId, joint, sourceIndex]));
          } else {
            // These duplicate binding/ownership inspections have no intervening
            // effect and no getters. They preserve the helper's lazy timestep load.
            let timestep = NaN;
            if ((operationFlags & 3) === 2) {
              const selected = Reflect.apply(bindingGet, joints, [joint]) as object;
              const aobj = readLink(selected, 'aobj7c');
              if (aobj !== null) {
                Reflect.apply(aobjGet, feedback, [aobj]);
                const value = own(actor, 'timestep1dc8'); float(value, 'timestep1dc8'); timestep = value;
              }
            }
            call('advance existing joint', () => Reflect.apply(advance, feedback, [partId, joint, timestep, operationFlags, fixedAnimation]));
          }
          const outputBank = signed(binding, 'poseBuffer35'); index(outputBank, 2, 'pose bank');
          const poses = layout.poses[outputBank]!, pose = poses[index(sourceIndex, poses.length, 'pose table')]!;
          call('capture pose and frame', () => Reflect.apply(capture, feedback, [partId, joint, pose, fixedPose]));
          const scaleIndex = signed(binding, 'scaleIndex32');
          if (scaleIndex >= 0 && sourceIndex === 1) {
            // 4acdc re-reads bank35 and scale32 after capture. Address-expression
            // operand order is not instruction-audited: adapters must be stable
            // actual getters, not additional source effects or memory aliases.
            const scaleBank = signed(binding, 'poseBuffer35'); index(scaleBank, 2, 'scaling pose bank');
            const scalePoses = layout.poses[scaleBank]!;
            const scalePose = Reflect.apply(poseGet, feedback,
              [scalePoses[index(1, scalePoses.length, 'scaling pose table')]!]) as object;
            if (reentered) fail('same-runtime reentry was caught inside an adapter');
            const table = getScaleTable(actorId), liveIndex = signed(binding, 'scaleIndex32');
            const factor = own(table, String(index(liveIndex, table.length, 'translation scaling table')), false);
            float(factor, 'translation scaling factor');
            const translation = own(scalePose, 'translation', false) as object;
            // 8020ba9c (chunk_0064.c:1299–1317) scales THREE floats,
            // despite its PSQUAT name. Snapshot Y then Z before the X store.
            const y = own(translation, 'y', false); float(y, 'translation scaling y');
            const z = own(translation, 'z', false); float(z, 'translation scaling z');
            const x = own(translation, 'x', false); float(x, 'translation scaling x');
            const store = (key: string, component: number): void => {
              // Finite exact-f32 products fit f64 precision and range. Round
              // once to f32, RN00/NI0 only; no instruction/ABI/paired-quantization
              // or NI1 parity claim. Preserve signed zero/subnormals. Overflow
              // refuses before this store, retaining earlier completed stores.
              const value = Math.fround(component * factor);
              float(value, `translation scaling ${key} result`);
              write(translation, key, value);
            };
            store('x', x); store('y', y); store('z', z);
          }
        }
      } finally {busy = false;}
  };
  const runtime: SourceActorJointMappingRuntime = Object.freeze({
    getActualFeedback() {return feedback;},
    getActualSetup() {return setupBinding?.receiver;},
    createDescriptor(initial: readonly number[]): symbol {
      const value = arrayCopy(initial, 128, (v, key) => integer(v, 255, key)), id = Symbol('owned actor descriptor');
      descriptors.set(id, value); return id;
    },
    getDescriptor,
    createJointBank(initial: readonly (symbol | null)[]): symbol {
      const value = arrayCopy(initial, 32, link), id = Symbol('owned actor joint bank'); banks.set(id, value); return id;
    },
    getJointBank,
    createPart(initial: SourceJointAnimationPart, binding: SourceActorJointPartBinding): symbol {
      const copied = {} as SourceActorJointPartBinding;
      for (const key of ['descriptor00', 'scaleIndex32', 'jointBank33', 'poseBuffer35'] as const) {
        const value = own(binding, key, false);
        if (key === 'descriptor00') {link(value, key); copied[key] = value;}
        else {integer(value, 255, key); copied[key] = value;}
      }
      const id = Reflect.apply(partCreate, feedback, [initial]) as symbol;
      partBindings.set(id, Object.seal(copied)); return id;
    },
    getPartBinding,
    createActor(initial: SourceActorJointMappingHeader, layout: SourceActorJointLayout): symbol {
      const copied = {} as SourceActorJointMappingHeader;
      for (const key of ['descriptor4b0', 'jointCount1d90', 'boundary1d91', 'boundary1d92', 'boundary1d93',
        'jointBank1db4', 'jointBank1db8', 'timestep1dc8'] as const) {
        const value = own(initial, key, false);
        if (key === 'descriptor4b0' || key === 'jointBank1db4' || key === 'jointBank1db8') {link(value, key); copied[key] = value;}
        else if (key === 'timestep1dc8') {float(value, key); copied[key] = value;}
        else {integer(value, 255, key); copied[key] = value;}
      }
      const newParts = new Set<symbol>(), newPoses = new Set<symbol>();
      const rows = (name: 'parts' | 'poses'): readonly (readonly symbol[])[] => {
        const rows = own(layout, name, false) as readonly (readonly symbol[])[];
        const copiedRows = arrayCopy(rows, 2, (row, key) => {
          if (!Array.isArray(row)) fail(`${name}[${key}]: array data required`);
        });
        if (copiedRows.length !== 2) fail(`${name}: exactly two owned banks required`);
        return Object.freeze(copiedRows.map(row => {
          const ids = arrayCopy(row, name === 'parts' ? 4 : 32, (id, key) => {
            if (typeof id !== 'symbol') fail(`${name}[${key}]: owned identity required`);
            const pending = name === 'parts' ? newParts : newPoses, assigned = name === 'parts' ? assignedParts : assignedPoses;
            if (pending.has(id) || assigned.has(id)) fail(`${name}: aliased inline storage is unsupported`);
            if (name === 'parts') {getPartBinding(id); getPart(id);} else Reflect.apply(poseGet, feedback, [id]);
            pending.add(id);
          });
          if (name === 'parts' && ids.length !== 4) fail('parts: exactly four inline parts per bank required');
          return Object.freeze(ids);
        }));
      };
      const ownedLayout = Object.freeze({parts: rows('parts'), poses: rows('poses')});
      const id = Symbol('owned mapped actor'); actors.set(id, Object.seal(copied)); layouts.set(id, ownedLayout);
      for (const part of newParts) assignedParts.add(part); for (const pose of newPoses) assignedPoses.add(pose);
      return id;
    },
    getActor, getLayout, getScaleTable,
    bindScaleTable(actor: symbol, values: readonly number[]): void {
      if (busy) {reentered = true; fail('same-runtime reentry during translation scaling table binding is unsupported');}
      getActor(actor);
      if (scaleTables.has(actor)) fail('translation scaling table is already bound');
      scaleTables.set(actor, arrayCopy(values, 128, float));
    },
    bindSetupRuntime(setup: Pick<SourceArchiveJointSetupRuntime, 'setupActorJoint'>): void {
      if (busy) {reentered = true; fail('same-runtime reentry during setup binding is unsupported');}
      if (setupBinding) fail('setup runtime is already bound');
      setupBinding = Object.freeze({receiver: setup, method: method(setup, 'setupActorJoint')});
    },
    mapPreparedPart(actor: symbol, partBank: number, partNumber: number, operationFlags: number): void {
      mapPart(actor, partBank, partNumber, operationFlags);
    },
    animatePart(actor: symbol, partBank: number, poseBuffer: number, partNumber: number, operationFlags: number): void {
      if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
      integer(poseBuffer, 255, 'poseBuffer');
      mapPart(actor, partBank, partNumber, operationFlags, poseBuffer);
    },
  });
  genuineRuntimes.add(runtime); return runtime;
}
