import {createSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshBinding,
  type SourceActorAttributeDescriptorBinding} from './actor-attribute-refresh.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createRomActor} from './actor.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-attribute-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
const sourceOffsets = [0x850, 0x854, 0x858, 0x85c, 0x860, 0x864, 0x868, 0x86c, 0x870, 0x874, 0x878, 0x87c, 0x880, 0x884, 0x888];
const target = (index: number) => `field${(0x814 + 4 * index).toString(16)}`;
const table = (record: object) => record as Record<string, unknown>;
function fixture(defer = false) {
  const unsupported = (): never => {throw Error('unexpected unrelated effect');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const descriptor = mapping.createDescriptor([]);
  const id = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(id, {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  targets.bindActor(id, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  const waits = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  waits.bindActor(id, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  waits.bindStartActor(id, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 0});
  const setup = createSourceActorAnimationSetupRuntime({mapping, feedback, dispatch,
    descriptors: createSourceAnimationDescriptorBankRuntime(), starts: waits,
    metadata: {getPartBinding: unsupported, applyMetadata: unsupported}, archiveBanks: {resolveArchive: unsupported}});
  setup.bindActor(id, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const actual = Object.assign(createRomActor(), {hoverOffset668: -99});
  actual.controlWord = 0x40; actual.modelScale = 2; actual.stepHeight = 91;
  actual.maxHSpeed = -90; actual.maxRise = -91; actual.maxFall = -92;
  actual.actionSpeedRows = [107, 110, 113];
  const matrices = createSourceActorJointMatrixRuntime(feedback);
  const make = (y: number) => matrices.createMatrix([1, 0, 0, 17, 0, 1, 0, y, 0, 0, 1, 19]);
  const root = make(100), body = make(20);
  const world = createSourceActorWorldMatrixRuntime({mapping, feedback, matrices});
  world.bindActor(id, actual, {mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 0,
    scale58: {x: 1, y: 1, z: 1}, offset1dbc: {x: 0, y: 0, z: 0}, adjusted1d54: {x: 0, y: 0, z: 0},
    preRotation1d64: {x: 0, y: 0, z: 0}}, {matrices8d4: [root, body], copy114: make(7), copy1aa4: make(8), scratch: make(9),
    topology1994: [], corrections18d4: [], scales15d4: []});
  const movement = createSourceActorMovementFollowupRuntime({mapping, waits, setup, matrixOwner: matrices});
  movement.bindActor(id, actual, {byte661: 0, field66c: -66, field670: -67});
  movement.bindDescriptor(descriptor, {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
  movement.bindWorldMatrices(id, [root, body]);
  const hooks: {world?: () => unknown; mapping?: () => unknown; descriptor?: () => unknown;
    movementActor?: () => unknown; movementBinding?: () => unknown; effect?: () => unknown} = {};
  let movementCalls = 0;
  const worldAdapter = {getActualActor(actor: symbol) {
    check(this === worldAdapter, 'captured world receiver'); return (hooks.world ? hooks.world() : world.getActualActor(actor)) as typeof actual;
  }};
  const mappingAdapter = {
    getActor(actor: symbol) {check(this === mappingAdapter, 'captured mapping receiver');
      return (hooks.mapping ? hooks.mapping() : mapping.getActor(actor)) as ReturnType<typeof mapping.getActor>;},
    getDescriptor(desc: symbol) {check(this === mappingAdapter, 'captured descriptor receiver');
      return (hooks.descriptor ? hooks.descriptor() : mapping.getDescriptor(desc)) as number[];},
  };
  const movementAdapter = {
    getActualActor(actor: symbol) {check(this === movementAdapter, 'captured movement actor receiver');
      return (hooks.movementActor ? hooks.movementActor() : movement.getActualActor(actor)) as typeof actual;},
    getActorBinding(actor: symbol) {check(this === movementAdapter, 'captured movement binding receiver');
      return (hooks.movementBinding ? hooks.movementBinding() : movement.getActorBinding(actor)) as ReturnType<typeof movement.getActorBinding>;},
    updateActor(actor: symbol): void {check(this === movementAdapter, 'captured movement effect receiver');
      movementCalls++; movement.updateActor(actor); return hooks.effect?.() as void;},
  };
  const runtime = createSourceActorAttributeRefreshRuntime({world: worldAdapter, mapping: mappingAdapter, movement: movementAdapter});
  const parameter = runtime.createParameterDescriptor({field74: 7, field78: 8, field7c: 9});
  const initial: Partial<SourceActorAttributeRefreshBinding> = {byte87: 9, field674: -74, field770: -70, parameter4ac: parameter};
  for (let i = 0; i < sourceOffsets.length; i++) {
    if (![6, 9, 12].includes(i)) table(initial)[`field${sourceOffsets[i]!.toString(16)}`] = 101 + i;
    table(initial)[target(i)] = -100 - i;
  }
  const descriptorInitial: Partial<SourceActorAttributeDescriptorBinding> = {field4c: 3, field44: 2, field48: 0.5, field54: 4, field50: 5};
  const bind = () => runtime.bindActor(id, initial);
  const bindDescriptor = () => runtime.bindDescriptor(descriptor, descriptorInitial);
  if (!defer) {bind(); bindDescriptor();}
  return {id, descriptor, parameter, actual, mapping, waits, setup, matrices, root, body, world, movement,
    runtime, initial, descriptorInitial, bind, bindDescriptor, hooks, worldAdapter, mappingAdapter, movementAdapter,
    calls: () => movementCalls, run: () => runtime.refreshActor(id)};
}
function copied(x: ReturnType<typeof fixture>, count = 15): void {
  const state = x.runtime.getActorBinding(x.id);
  for (let i = 0; i < 15; i++) equal(table(state)[target(i)], i < count ? 101 + i : -100 - i, `row ${i} prefix length ${count}`);
}
function products(x: ReturnType<typeof fixture>, count = 5): void {
  const state = x.runtime.getActorBinding(x.id), movement = x.movement.getActorBinding(x.id);
  const values = [x.actual.hoverOffset668, movement.field66c, movement.field670, state.field674, state.field770];
  const expected = [6, 4, 1, 8, 10], old = [-99, -66, -67, -74, -70];
  for (let i = 0; i < 5; i++) equal(values[i], i < count ? expected[i] : old[i], `product ${i} prefix length ${count}`);
}
/** Independent exact dyadic multiplication and RNE packing. No runtime float
 * helper, host float multiplication, or Math.fround is used by this oracle. */
function referenceProduct(a: number, b: number): number {
  const view = new DataView(new ArrayBuffer(4));
  const bits = (value: number): number => {view.setFloat32(0, value, false); return view.getUint32(0, false);};
  const aa = bits(a), bb = bits(b), sign = (aa ^ bb) >>> 31;
  const decode = (word: number): [bigint, number] => {
    const e = (word >>> 23) & 255, m = word & 0x7fffff;
    return [BigInt(e === 0 ? m : m + 0x800000), e === 0 ? -149 : e - 150];
  };
  const [am, ae] = decode(aa), [bm, be] = decode(bb), n = am * bm, exp = ae + be;
  if (n === 0n) return sign ? -0 : 0;
  const top = n.toString(2).length - 1 + exp;
  let unit = Math.max(top - 23, -149);
  const round = (shift: number): bigint => {
    if (shift <= 0) return n << BigInt(-shift);
    const d = 1n << BigInt(shift), q = n / d, r = n % d;
    return q + (2n * r > d || (2n * r === d && (q & 1n) === 1n) ? 1n : 0n);
  };
  let mantissa = round(unit - exp);
  if (mantissa >= 0x1000000n) {mantissa >>= 1n; unit++;}
  let word: number;
  if (unit > 104) word = 0x7f800000;
  else if (mantissa < 0x800000n) word = Number(mantissa);
  else word = ((unit + 150) << 23) + Number(mantissa - 0x800000n);
  view.setUint32(0, ((sign << 31) | word) >>> 0, false); return view.getFloat32(0, false);
}
export function runActorAttributeRefreshSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getDescriptorBinding(x.descriptor).byte10, undefined, 'historical descriptors do not gain a joint10 default');
    for (let raw = 0; raw < 256; raw++) {
      const descriptor = x.mapping.createDescriptor([]), initial = {byte10: raw};
      x.runtime.bindDescriptor(descriptor, initial); initial.byte10 = 255 - raw;
      const binding = x.runtime.getDescriptorBinding(descriptor);
      equal(binding.byte10, raw, 'explicit raw joint10 is copied on the existing descriptor identity');
      check(Object.isSealed(binding), 'joint selector descriptor extension stays sealed');
    }
    for (const value of [-1, 256, 0.5, NaN, Infinity]) {
      const descriptor = x.mapping.createDescriptor([]);
      rejects(() => x.runtime.bindDescriptor(descriptor, {byte10: value}), 'unsigned integer');
      x.runtime.bindDescriptor(descriptor, {byte10: 0});
    }
    const descriptor = x.mapping.createDescriptor([]); let reads = 0;
    const initial = Object.defineProperty({}, 'byte10', {get() {reads++; return 0;}});
    rejects(() => x.runtime.bindDescriptor(descriptor, initial), 'own data property');
    equal(reads, 0, 'joint10 accessor is never invoked');
    x.runtime.bindDescriptor(descriptor, {byte10: 127});
  }
  {
    const x = fixture();
    check(!Object.hasOwn(x.runtime.getParameterDescriptor(x.parameter), 'byteA3'), 'no default tier selector');
    check(!Object.hasOwn(x.runtime.getParameterDescriptor(x.parameter), 'fieldAe'), 'no default yaw rate');
    const known = x.runtime.getKnownParameterDescriptors();
    check(Object.isFrozen(known) && known.includes(x.runtime.getParameterDescriptor(x.parameter)), 'known parameter metadata retains actual sealed owner');
    const originalPointer = x.runtime.getActorBinding(x.id).parameter4ac;
    x.runtime.getActorBinding(x.id).parameter4ac = Symbol('unreached foreign pointer');
    equal(x.runtime.getKnownParameterDescriptors()[0], known[0], 'known metadata never dereferences actor4ac');
    x.runtime.getActorBinding(x.id).parameter4ac = originalPointer!;
    for (const value of [-32768, -1, 0, 1, 32767]) {
      const initial = {fieldAe: value}, id = x.runtime.createParameterDescriptor(initial);
      const descriptor = x.runtime.getParameterDescriptor(id);
      equal(descriptor.fieldAe, value, 'same4ac registry retains signed+ae');
      initial.fieldAe = 99; equal(descriptor.fieldAe, value, 'yaw rate copied once');
      equal(Object.keys(descriptor).join(','), 'fieldAe', 'yaw rate invents no other fields');
      check(Object.isSealed(descriptor), 'yaw-rate descriptor sealed');
    }
    for (const value of [-32769, 32768, 0.5, NaN, Infinity])
      rejects(() => x.runtime.createParameterDescriptor({fieldAe: value}), 'fieldAe: signed-short');
    let rateAccessor = false;
    rejects(() => x.runtime.createParameterDescriptor({get fieldAe() {rateAccessor = true; return 0;}}), 'fieldAe: own data');
    check(!rateAccessor, 'yaw rate accessor never invoked');
    for (const selector of [0, 1, 127, 128, 255]) {
      const initial = {byteA3: selector}, id = x.runtime.createParameterDescriptor(initial);
      const descriptor = x.runtime.getParameterDescriptor(id);
      equal(descriptor.byteA3, selector, 'same4ac registry retains unsigned+a3');
      initial.byteA3 = 42; equal(descriptor.byteA3, selector, 'initial selector copied once');
      check(Object.isSealed(descriptor), 'parameter descriptor remains sealed');
      equal(Object.keys(descriptor).join(','), 'byteA3', 'selector extension invents no constructor limits or floats');
      descriptor.byteA3 = 3; equal(x.runtime.getParameterDescriptor(id).byteA3, 3, 'selector stays live on same registry owner');
    }
    for (const selector of [-1, 256, 1.5, NaN, Infinity])
      rejects(() => x.runtime.createParameterDescriptor({byteA3: selector}), 'byteA3: unsigned integer');
    let invoked = false;
    rejects(() => x.runtime.createParameterDescriptor({get byteA3() {invoked = true; return 0;}}), 'byteA3: own data');
    check(!invoked, 'selector admission does not invoke accessor');
  }
  {
    const x = fixture(), rows = x.actual.actionSpeedRows, before = [...x.world.getWorldMatrix(x.id, 1)]; x.run();
    products(x); copied(x); equal(x.actual.maxHSpeed, 7, 'explicit parameter74'); equal(x.actual.maxRise, 8, 'explicit parameter78');
    equal(x.actual.maxFall, 9, 'explicit parameter7c'); equal(x.runtime.getActorBinding(x.id).byte87, 1, 'bit6 copied');
    equal(x.actual.stepHeight, Math.fround(18 * Math.fround(0.7)), 'real movement consumes refreshed field66c');
    equal(x.calls(), 1, 'one actual movement call'); check(rows === x.actual.actionSpeedRows, 'existing row owner retained');
    check(before.every((v, i) => Object.is(v, x.world.getWorldMatrix(x.id, 1)[i])), 'retained full matrix unchanged');
    x.actual.modelScale = 4; x.runtime.getDescriptorBinding(x.descriptor).field44 = 3;
    x.actual.actionSpeedRows[1] = -17; x.runtime.getParameterDescriptor(x.parameter).field78 = 18; x.run();
    equal(x.movement.getActorBinding(x.id).field66c, 12, 'live scale and descriptor');
    equal(x.actual.stepHeight, Math.fround(14 * Math.fround(0.7)), 'later call uses retained matrix and new height');
    equal(x.runtime.getActorBinding(x.id).field838, -17, 'actual row change is not stale copied source');
    equal(x.actual.maxRise, 18, 'live parameter'); equal(x.calls(), 2, 'one movement call each refresh');
  }
  for (const control of [0, 1, 0x3f, 0x40, 0x41, 0x80, 0xc0, 0x80000040, 0xffffffff]) {
    const x = fixture(); x.actual.controlWord = control; x.run(); products(x); copied(x);
    equal(x.runtime.getActorBinding(x.id).byte87, (control & 64) ? 1 : 0, `bit6 ${control}`);
  }
  for (const gate of ['family', 'byte661', 'control', 'marker'] as const) {
    const x = fixture();
    if (gate === 'family') x.actual.borgNumber = 0x0500;
    if (gate === 'byte661') x.movement.getActorBinding(x.id).byte661 = 1;
    if (gate === 'control') x.actual.controlWord = 0;
    if (gate === 'marker') x.waits.getActorBinding(x.id).marker71d = 255;
    x.matrices.getMatrix(x.body)[7] = NaN; x.run(); products(x); copied(x);
    equal(x.actual.stepHeight, gate === 'marker' ? -20 : 0, `${gate} only gates final real movement`);
    equal(x.calls(), 1, `${gate} still calls movement`);
  }
  {
    const x = fixture(), next = x.mapping.createDescriptor([]);
    x.runtime.bindDescriptor(next, {field4c: 11, field44: 12, field48: 13, field54: 14, field50: 15});
    x.movement.bindDescriptor(next, {joint0f: 1, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
    x.mapping.getActor(x.id).descriptor4b0 = next; x.run();
    equal(x.actual.hoverOffset668, 22, 'live selected mapping descriptor'); equal(x.movement.getActorBinding(x.id).field66c, 24, 'same selected dimension descriptor');
    equal(x.actual.stepHeight, Math.fround(8 * Math.fround(0.7)), 'movement uses mapping selection too');
  }
  for (const change of ['scale', 'descriptor', 'both'] as const) {
    const x = fixture(), next = x.mapping.createDescriptor([]);
    x.runtime.bindDescriptor(next, {field4c: 51, field44: 52, field48: 53, field54: 54, field50: 55});
    x.movement.bindDescriptor(next, {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
    x.actual.borgNumber = 0x0500; // Real movement gate avoids unrelated later loads.
    let changed = false;
    // A genuine captured owner-method boundary after the first two products,
    // not a scalar getter, Proxy, replacement record or fake movement effect.
    x.hooks.movementActor = () => {
      if (!changed) {
        changed = true;
        if (change !== 'descriptor') x.actual.modelScale = 8;
        if (change !== 'scale') x.mapping.getActor(x.id).descriptor4b0 = next;
      }
      return x.movement.getActualActor(x.id);
    };
    x.run(); products(x); copied(x); equal(x.calls(), 1, `${change} retained inputs precede one real movement call`);
    check(changed, 'retention witness crossed the actual movement getter');
    x.run();
    const state = x.runtime.getActorBinding(x.id), movement = x.movement.getActorBinding(x.id);
    const values = [x.actual.hoverOffset668, movement.field66c, movement.field670, state.field674, state.field770];
    const expected = change === 'scale' ? [24, 16, 4, 32, 40] : change === 'descriptor' ? [102, 104, 106, 108, 110] : [408, 416, 424, 432, 440];
    for (let i = 0; i < values.length; i++) equal(values[i], expected[i], `${change} becomes live only on the next refresh`);
    equal(x.calls(), 2, `${change} second refresh still calls real movement once`);
  }
  for (let index = 0; index < 5; index++) {
    const x = fixture(), keys = ['field4c', 'field44', 'field48', 'field54', 'field50'];
    table(x.runtime.getDescriptorBinding(x.descriptor))[keys[index]!] = NaN;
    rejects(x.run, 'float32'); products(x, index); copied(x, 0); equal(x.calls(), 0, 'bad product skips callee');
    equal(x.runtime.getActorBinding(x.id).byte87, 1, 'byte87 survives bad product'); equal(x.actual.maxHSpeed, -90, 'limits not reached');
  }
  for (const where of ['hoverOffset668', 'field66c', 'field670', 'field674', 'field770']) {
    const x = fixture(), index = ['hoverOffset668', 'field66c', 'field670', 'field674', 'field770'].indexOf(where);
    const owner = index === 0 ? x.actual : index < 3 ? x.movement.getActorBinding(x.id) : x.runtime.getActorBinding(x.id);
    Object.defineProperty(owner, where, {writable: false}); rejects(x.run, where); products(x, index); copied(x, 0);
  }
  for (let index = 0; index < 3; index++) {
    const x = fixture(), source = ['field74', 'field78', 'field7c'], destination = ['maxHSpeed', 'maxRise', 'maxFall'];
    table(x.runtime.getParameterDescriptor(x.parameter))[source[index]!] = NaN; rejects(x.run, source[index]!); products(x); copied(x, 0);
    for (let i = 0; i < 3; i++) equal(table(x.actual)[destination[i]!], i < index ? 7 + i : -90 - i, 'limit source prefix');
    const y = fixture(); Object.defineProperty(y.actual, destination[index]!, {writable: false}); rejects(y.run, destination[index]!); products(y); copied(y, 0);
    for (let i = 0; i < 3; i++) equal(table(y.actual)[destination[i]!], i < index ? 7 + i : -90 - i, 'limit store prefix');
  }
  for (let index = 0; index < 15; index++) {
    const x = fixture();
    if ([6, 9, 12].includes(index)) x.actual.actionSpeedRows[(index - 6) / 3] = NaN;
    else table(x.runtime.getActorBinding(x.id))[`field${sourceOffsets[index]!.toString(16)}`] = NaN;
    rejects(x.run, 'float32'); products(x); copied(x, index); equal(x.calls(), 0, 'late row source skips callee');
    equal(x.actual.maxFall, 9, 'all limits survive row refusal');
    const y = fixture(); Object.defineProperty(y.runtime.getActorBinding(y.id), target(index), {writable: false});
    rejects(y.run, target(index)); products(y); copied(y, index); equal(y.calls(), 0, 'late row store skips callee');
  }
  for (const absent of ['parameter4ac', 'field850', 'field888', 'field84c'] as const) {
    const x = fixture(true); delete x.initial[absent]; x.bind(); x.bindDescriptor(); rejects(x.run, absent); products(x);
    check(!Object.hasOwn(x.runtime.getActorBinding(x.id), absent), 'missing storage not defaulted');
    if (absent === 'field888' || absent === 'field84c') {
      for (let i = 0; i < 14; i++) equal(table(x.runtime.getActorBinding(x.id))[target(i)], 101 + i, 'missing final field preserves fourteen pairs');
    }
  }
  {
    const x = fixture(), absent = x.runtime.createParameterDescriptor({field74: 31});
    x.runtime.getActorBinding(x.id).parameter4ac = absent; rejects(x.run, 'field78');
    equal(x.actual.maxHSpeed, 31, 'missing parameter field preserves first limit'); equal(x.actual.maxRise, -91, 'missing second limit not defaulted');
    x.runtime.getActorBinding(x.id).parameter4ac = null; rejects(x.run, 'parameter4ac');
  }
  {
    const x = fixture(); x.mapping.getActor(x.id).descriptor4b0 = null; x.actual.modelScale = NaN;
    rejects(x.run, 'modelScale'); equal(x.runtime.getActorBinding(x.id).byte87, 1, 'scale read is after byte, before first descriptor scalar');
    x.actual.modelScale = 2; rejects(x.run, 'descriptor scalars');
  }
  {
    const x = fixture(); x.actual.actionSpeedRows = [7, 8, 9]; rejects(x.run, 'actionSpeedRows owner changed'); products(x); copied(x, 6);
  }
  {
    const x = fixture(); x.matrices.getMatrix(x.root)[7] = NaN; rejects(x.run, 'float32'); products(x); copied(x);
    equal(x.actual.stepHeight, 18, 'real callee preserves initial Y and half-height stores'); equal(x.calls(), 1, 'callee refusal still one invocation');
  }
  const tiny = 2 ** -149, max = 3.4028234663852886e38;
  // These are lfs/stfs transfers, not raw undefined4 copies. Every destination
  // independently witnesses the admitted finite-f32 bit-sign/value domain.
  for (const value of [0, -0, tiny, -tiny, -13.5, max, -max]) {
    const x = fixture(), state = x.runtime.getActorBinding(x.id);
    x.actual.controlWord = 0; // The real callee gate still follows all copies.
    const parameter = x.runtime.getParameterDescriptor(x.parameter);
    parameter.field74 = value; parameter.field78 = value; parameter.field7c = value;
    for (let i = 0; i < 15; i++) {
      if ([6, 9, 12].includes(i)) x.actual.actionSpeedRows[(i - 6) / 3] = value;
      else table(state)[`field${sourceOffsets[i]!.toString(16)}`] = value;
    }
    x.run();
    for (const actual of [x.actual.maxHSpeed, x.actual.maxRise, x.actual.maxFall]) equal(actual, value, 'lfs/stfs limit preserves finite value/sign');
    for (let i = 0; i < 15; i++) equal(table(state)[target(i)], value, `lfs/stfs row ${i} preserves finite value/sign`);
    equal(x.calls(), 1, 'finite copy domain still invokes actual movement once');
  }
  const cases: [number, number][] = [[0, -1], [-0, -1], [-0, 1], [tiny, 0.5], [3 * tiny, 0.5], [tiny, 1.5],
    [1.0000001192092896, 1.0000001192092896], [0.3333333432674408, 0.10000000149011612], [max, 1],
    [max, 0.5], [max, 2], [-max, 2], [1.1754943508222875e-38, 0.5], [2 ** -126, 0.9999999403953552]];
  for (const [scale, scalar] of cases) {
    const x = fixture(), expected = referenceProduct(scale, scalar); x.actual.modelScale = scale; x.actual.borgNumber = 0x500;
    const descriptor = x.runtime.getDescriptorBinding(x.descriptor);
    for (const key of ['field4c', 'field44', 'field48', 'field54', 'field50']) table(descriptor)[key] = scalar;
    if (!Number.isFinite(expected)) {rejects(x.run, 'fmuls'); equal(x.actual.hoverOffset668, -99, 'overflow refuses at first product effect');}
    else {x.run();
      for (const value of [x.actual.hoverOffset668, x.movement.getActorBinding(x.id).field66c, x.movement.getActorBinding(x.id).field670,
        x.runtime.getActorBinding(x.id).field674, x.runtime.getActorBinding(x.id).field770]) equal(value, expected, 'independent exact dyadic product');
    }
  }
  for (const invalid of [NaN, Infinity, -Infinity, 0.1]) {
    const x = fixture(); x.actual.modelScale = invalid; rejects(x.run, 'modelScale'); products(x, 0);
  }
  {
    const x = fixture(true); Object.freeze(x.initial); Object.freeze(x.descriptorInitial);
    x.worldAdapter.getActualActor = () => {throw Error('replacement world method');};
    x.mappingAdapter.getActor = () => {throw Error('replacement mapping method');};
    x.mappingAdapter.getDescriptor = () => {throw Error('replacement descriptor method');};
    x.movementAdapter.getActorBinding = () => {throw Error('replacement movement binding method');};
    x.movementAdapter.getActualActor = () => {throw Error('replacement actual method');};
    x.movementAdapter.updateActor = () => {throw Error('replacement effect');};
    x.bind(); x.bindDescriptor(); x.run(); products(x); copied(x); equal(x.calls(), 1, 'captured methods retain all receivers');
  }
  for (const owner of ['world', 'mapping', 'descriptor', 'movementActor', 'movementBinding'] as const) {
    const x = fixture(); x.hooks[owner] = () => ({}); rejects(x.run, 'owner changed');
    equal(x.runtime.getActorBinding(x.id).byte87, owner === 'world' ? 9 : 1, 'owner validation preserves reached byte prefix');
    products(x, owner === 'movementActor' || owner === 'movementBinding' ? 1 : 0);
  }
  for (const owner of ['world', 'mapping', 'movementActor', 'movementBinding'] as const) {
    const x = fixture(true); x.hooks[owner] = () => Promise.resolve({}); rejects(x.bind, owner === 'movementActor' ? 'owners differ' : 'synchronous');
    rejects(x.run, 'unknown/non-owned');
  }
  for (const effect of [() => 3, () => Promise.resolve()]) {
    const x = fixture(); x.hooks.effect = effect; rejects(x.run, 'effect must complete synchronously'); copied(x); products(x); equal(x.calls(), 1, 'bad effect return follows actual movement');
  }
  for (const owner of ['world', 'mapping', 'descriptor', 'movementBinding', 'effect'] as const) {
    const x = fixture(); x.hooks[owner] = () => {
      try {x.run();} catch { /* caught inner error must poison enclosing operation */ }
      if (owner === 'world') return x.actual;
      if (owner === 'mapping') return x.mapping.getActor(x.id);
      if (owner === 'descriptor') return x.mapping.getDescriptor(x.descriptor);
      if (owner === 'movementBinding') return x.movement.getActorBinding(x.id);
      return undefined;
    };
    rejects(x.run, 'reentry');
    if (owner === 'effect') {products(x); copied(x); equal(x.calls(), 1, 'reentry after real movement preserves completed prefix');}
    delete x.hooks[owner]; x.run(); equal(x.calls(), owner === 'effect' ? 2 : 1, 'later independent operation recovers');
  }
  {
    const x = fixture(true); x.hooks.world = () => {try {x.bind();} catch { /* poison bind */ } return x.actual;};
    rejects(x.bind, 'reentry'); rejects(x.run, 'unknown/non-owned'); delete x.hooks.world; x.bind(); x.bindDescriptor(); x.run();
  }
  {
    const x = fixture(); rejects(x.bind, 'already bound'); rejects(x.bindDescriptor, 'already bound');
    rejects(() => x.runtime.refreshActor(Symbol('foreign')), 'unknown/non-owned');
    x.hooks.world = () => x.actual; x.hooks.movementActor = () => x.actual;
    x.hooks.mapping = () => x.mapping.getActor(x.id); x.hooks.movementBinding = () => x.movement.getActorBinding(x.id);
    rejects(() => x.runtime.bindActor(Symbol('alias'), x.initial), 'aliases');
    rejects(() => x.runtime.bindDescriptor(Symbol('foreign'), x.descriptorInitial), 'unknown/non-owned');
    x.hooks.descriptor = () => x.mapping.getDescriptor(x.descriptor);
    rejects(() => x.runtime.bindDescriptor(Symbol('alias'), x.descriptorInitial), 'aliases');
  }
  {
    const x = fixture(); let accesses = 0;
    Object.defineProperty(x.actual, 'hoverOffset668', {get() {accesses++; return 1;}});
    rejects(x.run, 'own data property'); equal(accesses, 0, 'destination accessor not invoked');
    const y = fixture(); Object.defineProperty(y.actual, 'modelScale', {get() {accesses++; return 2;}});
    rejects(y.run, 'own data property'); equal(accesses, 0, 'source accessor not invoked');
    const z = fixture(); delete (z.actual as Partial<typeof z.actual>).hoverOffset668;
    Object.setPrototypeOf(z.actual, {hoverOffset668: 7}); rejects(z.run, 'own data property');
  }
  {
    const x = fixture(); Object.freeze(x.runtime.getDescriptorBinding(x.descriptor)); Object.freeze(x.runtime.getParameterDescriptor(x.parameter));
    Object.freeze(x.actual.actionSpeedRows); Object.freeze(x.mapping.getActor(x.id));
    Object.defineProperty(x.actual, 'controlWord', {writable: false}); Object.defineProperty(x.actual, 'modelScale', {writable: false});
    x.actual.hoverOffset668 = NaN; x.actual.maxHSpeed = NaN; x.run(); products(x); copied(x);
    equal(x.actual.maxHSpeed, 7, 'readonly sources accepted and stale destination NaN overwritten');
  }
  {
    const x = fixture(true); x.initial.field888 = 0.1; rejects(x.bind, 'float32');
    x.initial.field888 = 115; x.initial.parameter4ac = 1 as unknown as symbol; rejects(x.bind, 'symbol');
    x.initial.parameter4ac = x.parameter; x.initial.byte87 = 256; rejects(x.bind, 'unsigned integer');
    x.initial.byte87 = 9; x.bind(); x.descriptorInitial.field4c = 0.1; rejects(x.bindDescriptor, 'float32');
    rejects(() => x.runtime.createParameterDescriptor({field74: 0.1}), 'float32');
  }
}
