/** Bounded source 4b94c part/pose copy, 4a8cc blending and 4a00c mode1.
 * All existing fields are borrowed from their canonical owners. Only the eight
 * absent bytes of the 0x40 part and descriptor42/43 have explicit sidecars.
 * No zero defaults, synthetic clock, copied source record or skipped callee.
 *
 * research/decomp/actor-mode1-envelope-evidence-2026-11-14.md authenticates
 * every selected instruction and
 * constants. 8020bf08 admits ONLY its finite linear branch, strictly above
 * 3f7fff58; the nonlinear branch refuses at real 8023cc8c. Quaternion weights
 * are not clamped/normalized, and arithmetic is not fused. Paired vector scale
 * requires GQR0 float/scale0, RN00/NI0; these are host preconditions, not live
 * register observations. Two part/pose banks, four channels, finite f32 and
 * no RAM aliases/proxies/deferred effects are additional host bounds.
 *
 * Source word loads/stores remain paired. Packed-word destination fields are
 * checked together before its single logical store. Completed word/pose stores
 * survive failure. A failed mode1 containing operation consumes the canonical
 * mapping actor, preventing replay through changed mode or readiness gates.
 */
import {addSourceFloat32} from './source-float.js';
import {isSourceActorAnimationDispatchRuntime, type SourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {isSourceActorAnimationSetupRuntime, type SourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {isSourceActorJointMappingRuntime, type SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {isSourceJointAnimationFeedbackRuntime, type SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {isSourceAttachedJointSetupRuntime, type SourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {isSourceAnimationSetupMetadataRuntime, type SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {isSourceArchiveJointSetupRuntime, type SourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {isSourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';

export interface SourceActorAnimationTransitionRawPart {
  byte34: number; byte39: number; byte3a: number; byte3b: number;
  byte3c: number; byte3d: number; byte3e: number; byte3f: number;
}
export interface SourceActorAnimationTransitionDescriptor {byte42: number; byte43: number}
export interface SourceActorAnimationTransitionSources {
  mapping: SourceActorJointMappingRuntime;
  feedback: SourceJointAnimationFeedbackRuntime;
  dispatch: SourceActorAnimationDispatchRuntime;
  setup: SourceActorAnimationSetupRuntime;
  attached: Pick<SourceAttachedJointSetupRuntime, 'getPartBinding'>;
  metadata: Pick<SourceAnimationSetupMetadataRuntime, 'getPartBinding' | 'getActorBinding'>;
  archives: Pick<SourceArchiveJointSetupRuntime, 'getPartBinding'>;
}
export interface SourceActorAnimationTransitionRuntime {
  getActualMapping(): SourceActorJointMappingRuntime;
  getActualFeedback(): SourceJointAnimationFeedbackRuntime;
  getActualDispatch(): SourceActorAnimationDispatchRuntime;
  getActualSetup(): SourceActorAnimationSetupRuntime;
  bindPartRaw(part: symbol, initial: SourceActorAnimationTransitionRawPart): void;
  getPartRaw(part: symbol): SourceActorAnimationTransitionRawPart;
  bindDescriptor(descriptor: symbol, initial: SourceActorAnimationTransitionDescriptor): void;
  getDescriptorBinding(descriptor: symbol): SourceActorAnimationTransitionDescriptor;
  copyPart(actor: symbol, sourceBank: number, channel: number, copyMode: number): void;
  blendPart(actor: symbol, channel: number, weight: number): void;
  updateModeOne(actor: symbol, channel: number): void;
}
const runtimes = new WeakSet<object>(), incompleteActors = new WeakSet<object>();
export function isSourceActorAnimationTransitionRuntime(value: unknown): value is SourceActorAnimationTransitionRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function hasIncompleteSourceActorAnimationTransition(actor: object): boolean {return incompleteActors.has(actor);}
/** Internal shared failure latch. Identity is the canonical mapping header. */
export function markIncompleteSourceActorAnimationTransition(actor: object): void {incompleteActors.add(actor);}
export function requireCompleteSourceActorAnimationTransition(actor: object): void {
  if (incompleteActors.has(actor)) fail('incomplete mode1 operation: actor replay is unsupported');
}
function fail(reason: string): never {throw Error(`[actor-animation-transition] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, low: number, high: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < low || value > high) fail(`${where}: integer out of bounds`);
  return value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite exact source float32 required`);
  return value;
}
const mul = (a: number, b: number): number => float(Math.fround(a * b), 'fmuls result');
const sub = (a: number, b: number): number => addSourceFloat32(a, -b);
const bits = new DataView(new ArrayBuffer(4));
function dyadic(value: number): {mantissa: bigint; exponent: number; negative: boolean} {
  float(value, 'fdivs operand'); bits.setFloat32(0, value, false);
  const raw = bits.getUint32(0, false), e = (raw >>> 23) & 255;
  return {mantissa: BigInt((raw & 0x7fffff) | (e === 0 ? 0 : 0x800000)),
    exponent: e === 0 ? -149 : e - 150, negative: (raw >>> 31) !== 0};
}
/** Internal exact rational RN00/NI0 fdivs shared with mode1 setup. */
export function divideSourceAnimationFloat32(a: number, b: number): number {
  const x = dyadic(a), y = dyadic(b), negative = x.negative !== y.negative;
  if (y.mantissa === 0n) fail('fdivs zero divisor outside finite domain');
  if (x.mantissa === 0n) return negative ? -0 : 0;
  let power = x.mantissa.toString(2).length - y.mantissa.toString(2).length;
  if (power >= 0 ? x.mantissa < (y.mantissa << BigInt(power)) : (x.mantissa << BigInt(-power)) < y.mantissa) power--;
  const exponent = x.exponent - y.exponent, quantum = Math.max(-149, power + exponent - 23), shift = exponent - quantum;
  const numerator = shift >= 0 ? x.mantissa << BigInt(shift) : x.mantissa;
  const denominator = shift < 0 ? y.mantissa << BigInt(-shift) : y.mantissa;
  let rounded = numerator / denominator;
  const twice = (numerator % denominator) * 2n;
  if (twice > denominator || (twice === denominator && (rounded & 1n) !== 0n)) rounded++;
  return float((negative ? -1 : 1) * Number(rounded) * 2 ** quantum, 'fdivs result');
}
type Owner = 'mapping' | 'feedback' | 'dispatch' | 'setup' | 'attached' | 'metadata' | 'archives' | 'raw';
type Field = readonly [Owner, string, 'byte' | 'short' | 'float' | 'link'];
// Each row is one source BE word. No word or padding byte is omitted.
const WORDS: readonly (readonly Field[])[] = [
  [['mapping', 'descriptor00', 'link']], [['archives', 'descriptor04', 'link']],
  [['dispatch', 'elapsed08', 'float']], [['feedback', 'frame0c', 'float']],
  [['dispatch', 'previous10', 'float']], [['dispatch', 'previous14', 'float']],
  [['setup', 'field18', 'float']], [['setup', 'field1c', 'float']], [['setup', 'field20', 'float']],
  [['feedback', 'duration24', 'short'], ['attached', 'rewind26', 'short']],
  [['setup', 'group28', 'byte'], ['setup', 'action29', 'byte'], ['metadata', 'selector2a', 'byte'], ['metadata', 'selector2b', 'byte']],
  [['attached', 'loop2c', 'byte'], ['feedback', 'segment2d', 'byte'], ['feedback', 'complete2e', 'byte'], ['feedback', 'mode2f', 'byte']],
  [['feedback', 'mirror30', 'byte'], ['setup', 'bank31', 'byte'], ['mapping', 'scaleIndex32', 'byte'], ['mapping', 'jointBank33', 'byte']],
  [['raw', 'byte34', 'byte'], ['mapping', 'poseBuffer35', 'byte'], ['dispatch', 'linked36', 'byte'], ['metadata', 'auxiliary37', 'byte']],
  [['setup', 'status38', 'byte'], ['raw', 'byte39', 'byte'], ['raw', 'byte3a', 'byte'], ['raw', 'byte3b', 'byte']],
  [['raw', 'byte3c', 'byte'], ['raw', 'byte3d', 'byte'], ['raw', 'byte3e', 'byte'], ['raw', 'byte3f', 'byte']],
];
const RAW = ['byte34', 'byte39', 'byte3a', 'byte3b', 'byte3c', 'byte3d', 'byte3e', 'byte3f'] as const;
export function createSourceActorAnimationTransitionRuntime(sources: SourceActorAnimationTransitionSources): SourceActorAnimationTransitionRuntime {
  const mapping = own(sources, 'mapping') as SourceActorJointMappingRuntime;
  const feedback = own(sources, 'feedback') as SourceJointAnimationFeedbackRuntime;
  const dispatch = own(sources, 'dispatch'), setup = own(sources, 'setup');
  if (!isSourceActorJointMappingRuntime(mapping) || !isSourceJointAnimationFeedbackRuntime(feedback) ||
    !isSourceActorAnimationDispatchRuntime(dispatch) || !isSourceActorAnimationSetupRuntime(setup) ||
    dispatch.getActualMapping() !== mapping || dispatch.getActualFeedback() !== feedback ||
    setup.getActualMapping() !== mapping || setup.getActualFeedback() !== feedback || setup.getActualDispatch() !== dispatch) {
    fail('matched genuine setup/dispatch/mapping/feedback owners required');
  }
  const metadata = own(sources, 'metadata'), archives = own(sources, 'archives'), attached = own(sources, 'attached');
  const archiveBanks = setup.getActualArchiveBanks();
  if (!isSourceAnimationSetupMetadataRuntime(metadata) || !isSourceArchiveJointSetupRuntime(archives) ||
    !isSourceAttachedJointSetupRuntime(attached) || !isSourceAnimationArchiveBankRuntime(archiveBanks) ||
    setup.getActualMetadata() !== metadata || metadata.getActualMapping() !== mapping || metadata.getActualFeedback() !== feedback ||
    metadata.getActualAttached() !== attached || attached.getActualMapping() !== mapping || attached.getActualFeedback() !== feedback ||
    archives.getActualMapping() !== mapping || archives.getActualTail() !== attached ||
    archiveBanks.getActualMapping() !== mapping || archiveBanks.getActualMetadata() !== metadata || archiveBanks.getActualArchives() !== archives ||
    mapping.getActualFeedback() !== feedback || mapping.getActualSetup() !== archives) {
    fail('matched genuine metadata/attached/archive owners required');
  }
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const capture = (receiver: unknown, key: string) => {
    const fn = own(receiver, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(fn, receiver, args); check();
      if (result instanceof Promise) fail('adapter must complete synchronously'); return result;};
  };
  const getActor = capture(mapping, 'getActor'), getLayout = capture(mapping, 'getLayout'), getDescriptor = capture(mapping, 'getDescriptor');
  const getPose = capture(feedback, 'getPose'), animate = capture(mapping, 'animatePart');
  const getVisibility = capture(own(sources, 'metadata'), 'getActorBinding');
  const getters: Record<Exclude<Owner, 'raw'>, (...args: unknown[]) => unknown> = {
    mapping: capture(mapping, 'getPartBinding'), feedback: capture(feedback, 'getPart'),
    dispatch: capture(dispatch, 'getPartBinding'), setup: capture(setup, 'getPartBinding'),
    attached: capture(own(sources, 'attached'), 'getPartBinding'), metadata: capture(own(sources, 'metadata'), 'getPartBinding'),
    archives: capture(own(sources, 'archives'), 'getPartBinding'),
  };
  const raw = new Map<symbol, SourceActorAnimationTransitionRawPart>(), descriptors = new Map<symbol, SourceActorAnimationTransitionDescriptor>();
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: unknown): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const f = (record: unknown, key: string) => float(read(record, key), key);
  const byte = (record: unknown, key: string) => integer(read(record, key), 0, 255, key);
  const signed = (record: unknown, key: string) => byte(record, key) << 24 >> 24;
  const identity = (value: unknown, where: string): symbol => {if (typeof value !== 'symbol') fail(`${where}: owned symbol required`); return value;};
  const getRaw = (id: symbol): SourceActorAnimationTransitionRawPart => {const value = raw.get(id); if (!value) fail('missing explicit raw part34/39..3f'); return value;};
  const descriptorBinding = (id: symbol): SourceActorAnimationTransitionDescriptor => {
    const value = descriptors.get(id); if (!value) fail('missing explicit descriptor42/43'); return value;
  };
  const record = (part: symbol, owner: Owner): unknown => owner === 'raw' ? getRaw(part) : getters[owner](part);
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false; try {run(); check();} finally {busy = false;}
  };
  const actorGuard = (id: symbol, run: () => void): void => guard(() => {
    const actor = getActor(id) as object; requireCompleteSourceActorAnimationTransition(actor);
    try {run(); check();} catch (error) {markIncompleteSourceActorAnimationTransition(actor); throw error;}
  });
  const partAt = (id: symbol, bank: number, channel: number): symbol => {
    integer(bank, 0, 1, 'two-bank host bound'); integer(channel, 0, 3, 'four-channel host bound');
    return identity(read(read(read(getLayout(id), 'parts'), String(bank)), String(channel)), 'part');
  };
  const range = (id: symbol, channel: number): [number, number] => {
    integer(channel, 0, 3, 'four-channel host bound'); const actor = getActor(id);
    const keys = ['jointCount1d90', 'boundary1d91', 'boundary1d92', 'boundary1d93'] as const;
    return [channel === 0 ? 0 : signed(actor, keys[channel]!), signed(actor, channel === 3 ? keys[0] : keys[channel + 1]!)];
  };
  const mappedJoint = (id: symbol, ordinal: number): number => {
    const descriptor = identity(read(getActor(id), 'descriptor4b0'), 'descriptor4b0');
    const map = getDescriptor(descriptor), index = signed(map, String(ordinal));
    if (index < 0) fail('negative mapped pose addressing is unsupported'); return index;
  };
  const pose = (id: symbol, bank: number, joint: number): unknown => {
    const row = read(read(getLayout(id), 'poses'), String(bank));
    return getPose(identity(read(row, String(joint)), 'pose'));
  };
  const readWord = (part: symbol, index: number): unknown[] => WORDS[index]!.map(([owner, key, type]) => {
    const value = read(record(part, owner), key);
    if (type === 'float') float(value, key);
    else if (type === 'byte') integer(value, 0, 255, key);
    else if (type === 'short') integer(value, -32768, 32767, key);
    else if (value !== null && typeof value !== 'symbol') fail(`${key}: raw symbolic pointer required`);
    return value;
  });
  const storeWord = (part: symbol, index: number, values: unknown[]): void => {
    // One source stw cannot leave only some bytes of a packed word changed.
    const targets = WORDS[index]!.map(([owner, key]) => ({record: record(part, owner), key}));
    for (const target of targets) {own(target.record, target.key, true); check();}
    targets.forEach((target, i) => {(target.record as Record<string, unknown>)[target.key] = values[i];}); check();
  };
  const copyPair = (from: unknown, to: unknown, a: string, b: string): void => {
    const first = f(from, a), second = f(from, b); write(to, a, first); write(to, b, second);
  };
  const copy = (id: symbol, bank: number, channel: number, copyMode: number): void => {
    const source = partAt(id, bank, channel), destination = partAt(id, bank ^ 1, channel);
    for (let word = 0; word < 16; word += 2) {
      const first = readWord(source, word), second = readWord(source, word + 1);
      storeWord(destination, word, first); storeWord(destination, word + 1, second);
    }
    write(getters.mapping(destination), 'jointBank33', bank ^ 1);
    if (channel === 0) {
      const visibility = getVisibility(id), from = bank === 0 ? ['byte1d74', 'byte1d75'] : ['byte1d76', 'byte1d77'];
      const to = bank === 0 ? ['byte1d76', 'byte1d77'] : ['byte1d74', 'byte1d75'];
      for (let i = 0; i < 2; i++) write(visibility, to[i]!, byte(visibility, from[i]!));
    }
    integer(copyMode, -0x80000000, 0xffffffff, 'copyMode');
    if (copyMode !== 0) return;
    const [start, end] = range(id, channel);
    for (let ordinal = start; ordinal < end; ordinal++) {
      const joint = mappedJoint(id, ordinal), from = pose(id, bank, joint), to = pose(id, bank ^ 1, joint);
      const a = read(from, 'quaternion'), b = read(to, 'quaternion');
      copyPair(a, b, 'x', 'y'); copyPair(a, b, 'z', 'w');
      const at = read(from, 'translation'), bt = read(to, 'translation');
      copyPair(at, bt, 'x', 'y'); write(bt, 'z', f(at, 'z'));
    }
  };
  const blend = (id: symbol, channel: number, weight: number): void => {
    float(weight, 'blend weight'); const other = sub(1, weight), [start, end] = range(id, channel);
    for (let ordinal = start; ordinal < end; ordinal++) {
      const joint = mappedJoint(id, ordinal), current = pose(id, 0, joint), previous = pose(id, 1, joint);
      const currentT = read(current, 'translation'), previousT = read(previous, 'translation');
      // Real paired scale reads xyz, then computes/stores xy followed by z.
      const scaled = (value: unknown, scale: number): number[] => {
        const x = f(value, 'x'), y = f(value, 'y'), z = f(value, 'z'); return [mul(x, scale), mul(y, scale), mul(z, scale)];
      };
      const aT = scaled(currentT, other), bT = scaled(previousT, weight);
      const x = addSourceFloat32(aT[0]!, bT[0]!), y = addSourceFloat32(aT[1]!, bT[1]!);
      own(currentT, 'x', true); own(currentT, 'y', true); check();
      (currentT as {x: number; y: number}).x = x; (currentT as {x: number; y: number}).y = y; check();
      write(currentT, 'z', addSourceFloat32(aT[2]!, bT[2]!));
      const currentQ = read(current, 'quaternion'), previousQ = read(previous, 'quaternion');
      const a = ['x', 'y', 'z', 'w'].map(key => f(currentQ, key));
      const b = ['x', 'y', 'z', 'w'].map(key => f(previousQ, key));
      // Exact source arithmetic order from the authenticated4a8cc instructions.
      const dx = sub(a[0]!, b[0]!), dy = sub(a[1]!, b[1]!), sx = addSourceFloat32(a[0]!, b[0]!), sy = addSourceFloat32(a[1]!, b[1]!);
      const dx2 = mul(dx, dx), dy2 = mul(dy, dy), dz = sub(a[2]!, b[2]!), sz = addSourceFloat32(a[2]!, b[2]!);
      const sx2 = mul(sx, sx), sy2 = mul(sy, sy), dw = sub(a[3]!, b[3]!), sw = addSourceFloat32(a[3]!, b[3]!), dz2 = mul(dz, dz);
      const diffXY = addSourceFloat32(dx2, dy2), sz2 = mul(sz, sz), sumXY = addSourceFloat32(sx2, sy2), dw2 = mul(dw, dw);
      const diffXYZ = addSourceFloat32(dz2, diffXY), sw2 = mul(sw, sw), sumXYZ = addSourceFloat32(sz2, sumXY);
      if (addSourceFloat32(dw2, diffXYZ) > addSourceFloat32(sw2, sumXYZ)) for (let i = 0; i < 4; i++) b[i] = -b[i]!;
      // Actual8020bf08 linear branch. No normalization or identity shortcut.
      const px = mul(a[0]!, b[0]!), py = mul(a[1]!, b[1]!), pz = mul(a[2]!, b[2]!);
      const xy = addSourceFloat32(px, py), pw = mul(a[3]!, b[3]!), xyz = addSourceFloat32(pz, xy);
      let dot = addSourceFloat32(pw, xyz), sign = 1;
      if (dot < 0) {dot = -dot; sign = -1;}
      if (!(dot > 0.9999899864196777)) fail('8020bf08 nonlinear branch requires unsupported callee8023cc8c');
      const signedWeight = mul(sign, weight), remaining = sub(1, weight);
      for (let i = 0; i < 4; i++) write(currentQ, ['x', 'y', 'z', 'w'][i]!, addSourceFloat32(mul(remaining, a[i]!), mul(signedWeight, b[i]!)));
      for (let i = 0; i < 2; i++) {
        const descriptor = identity(read(getActor(id), 'descriptor4b0'), 'descriptor4b0'); getDescriptor(descriptor);
        const binding = descriptorBinding(descriptor);
        if (signed(binding, i === 0 ? 'byte42' : 'byte43') !== joint) continue;
        const visibility = getVisibility(id), selected = weight > 0.5 ? ['byte1d76', 'byte1d77'] : ['byte1d74', 'byte1d75'];
        write(visibility, i === 0 ? 'byte1d94' : 'byte1d95', byte(visibility, selected[i]!)); break;
      }
    }
  };
  const runtime: SourceActorAnimationTransitionRuntime = Object.freeze({
    getActualMapping() {return mapping;}, getActualFeedback() {return feedback;},
    getActualDispatch() {return dispatch;}, getActualSetup() {return setup;},
    bindPartRaw(id: symbol, initial: SourceActorAnimationTransitionRawPart): void {guard(() => {
      if (raw.has(id)) fail('raw part already bound'); getters.mapping(id);
      const record = {} as SourceActorAnimationTransitionRawPart;
      for (const key of RAW) record[key] = byte(initial, key); raw.set(id, Object.seal(record));
    });},
    getPartRaw: getRaw,
    bindDescriptor(id: symbol, initial: SourceActorAnimationTransitionDescriptor): void {guard(() => {
      if (descriptors.has(id)) fail('transition descriptor already bound'); getDescriptor(id);
      descriptors.set(id, Object.seal({byte42: byte(initial, 'byte42'), byte43: byte(initial, 'byte43')}));
    });},
    getDescriptorBinding: descriptorBinding,
    copyPart(id: symbol, bank: number, channel: number, mode: number): void {actorGuard(id, () => copy(id, bank, channel, mode));},
    blendPart(id: symbol, channel: number, weight: number): void {actorGuard(id, () => blend(id, channel, weight));},
    updateModeOne(id: symbol, channel: number): void {actorGuard(id, () => {
      const part = partAt(id, 0, channel), clock = getters.dispatch(part);
      write(clock, 'elapsed08', addSourceFloat32(f(clock, 'elapsed08'), f(getActor(id), 'timestep1dc8')));
      const state = getters.setup(part);
      write(state, 'field1c', addSourceFloat32(f(state, 'field1c'), f(getActor(id), 'timestep1dc8')));
      const elapsed = f(state, 'field1c'), duration = f(state, 'field18');
      if (elapsed < duration) {
        write(state, 'field20', sub(1, divideSourceAnimationFloat32(elapsed, duration)));
        if (animate(id, 0, 0, channel, 0) !== undefined) fail('animatePart must synchronously return undefined');
        blend(id, channel, f(state, 'field20'));
      } else {
        const overflow = sub(elapsed, duration), actual = getters.feedback(part), previous = f(actual, 'frame0c');
        write(actual, 'frame0c', addSourceFloat32(previous, overflow));
        if (animate(id, 0, 0, channel, 1) !== undefined) fail('animatePart must synchronously return undefined');
        write(actual, 'mode2f', 0);
      }
    });},
  });
  runtimes.add(runtime); return runtime;
}
