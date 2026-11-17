import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime, type SourceJointPoseEffects} from './joint-animation-feedback.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-joint-scaling-test] ${why}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
function fixture(map: readonly number[] = [1]) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const joint = joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 2, translation3c: 3, translation40: 4},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const hooks: {afterCapture?: () => void; getPose?: () => void} = {};
  let captures = 0, advances = 0;
  const effects: SourceJObjAnimationEffects = {
    interpretAObj() {throw Error('no-AObj fixture refuses interpretation');},
    animateRObjs() {throw Error('no-AObj fixture refuses RObj animation');},
    animateDObjs() {throw Error('no-AObj fixture refuses DObj animation');},
  };
  const poseEffects: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
    check(this === poseEffects, 'fixed converter receiver');
    check(Object.isFrozen(rotation), 'immutable Euler snapshot');
    if (![rotation.x, rotation.y, rotation.z].every(v => Object.is(v, 0))) throw Error('positive zero Euler only');
    output.x = 0; output.y = 0; output.z = 0; output.w = 1;
  }};
  // Forward to real owned records and real no-AObj advance/capture. Hooks are
  // explicitly out-of-contract fault injection, never supported source effects.
  const adapter = {...feedback,
    getPose(id: symbol) {check(this === adapter, 'fixed getPose receiver'); hooks.getPose?.(); return feedback.getPose(id);},
    advanceExistingJoint(...args: Parameters<typeof feedback.advanceExistingJoint>) {
      check(this === adapter, 'fixed advance receiver'); advances++; feedback.advanceExistingJoint(...args);
    },
    capturePoseAndFrame(...args: Parameters<typeof feedback.capturePoseAndFrame>) {
      check(this === adapter, 'fixed capture receiver'); feedback.capturePoseAndFrame(...args); captures++; hooks.afterCapture?.();
    },
  };
  const runtime = createSourceActorJointMappingRuntime(joints, adapter, effects, poseEffects);
  const descriptor = runtime.createDescriptor(map), bank = runtime.createJointBank([null, joint, joint]);
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => runtime.createPart(
    {frame0c: 17, duration24: 3, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: descriptor, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const poses = Array.from({length: 2}, () => Array.from({length: 3}, () => feedback.createPose(
    {translation: {x: 11, y: 13, z: 17}, quaternion: {x: 19, y: 23, z: 29, w: 31}})));
  const actor = runtime.createActor({descriptor4b0: descriptor, jointCount1d90: 3,
    boundary1d91: map.length, boundary1d92: map.length, boundary1d93: map.length,
    jointBank1db4: bank, jointBank1db8: bank, timestep1dc8: 1}, {parts, poses});
  const binding = runtime.getPartBinding(parts[0]![0]!);
  const pose = (b = 0, i = 1) => feedback.getPose(poses[b]![i]!);
  const animate = (b = 0) => runtime.animatePart(actor, 0, b, 0, 2);
  const bind = (values: readonly number[]) => runtime.bindScaleTable(actor, values);
  return {runtime, actor, binding, bind, animate, pose, hooks, adapter, poseEffects, joints,
    source: joints.getJoint(joint), header: runtime.getActor(actor), part: feedback.getPart(parts[0]![0]!),
    counts: () => ({captures, advances})};
}
const xyz = ['x', 'y', 'z'] as const;
export function runActorJointScalingSelfTest(): void {
  for (const factor of [0, -0, -2, 0.5, Math.fround(1 / 3), 2 ** 120, 2 ** -149]) {
    const t = fixture(); t.bind([factor]); t.animate();
    for (const [i, key] of xyz.entries()) check(Object.is(t.pose().translation[key], Math.fround((i + 2) * factor)), `${factor} ${key} exact f32 product`);
    check(t.pose().quaternion.w === 1 && t.pose().quaternion.x === 0 && t.part.frame0c === 17,
      'three-float scale leaves actual converted quaternion and no-AObj frame intact');
  }
  {
    const t = fixture(); t.source.translation38 = -0; t.source.translation3c = 2 ** -149; t.source.translation40 = -(2 ** -149);
    t.bind([0.5]); t.animate();
    check(Object.is(t.pose().translation.x, -0) && Object.is(t.pose().translation.y, 0) && Object.is(t.pose().translation.z, -0),
      'negative zero and subnormal tie-to-even underflow are retained');
  }
  for (const axis of xyz) {
    const t = fixture(); t.source.translation38 = 2; t.source.translation3c = 3; t.source.translation40 = 4;
    t.source[axis === 'x' ? 'translation38' : axis === 'y' ? 'translation3c' : 'translation40'] = Math.fround(3.4028234663852886e38);
    t.bind([2]); rejects(t.animate, `translation scaling ${axis} result`);
    for (const [i, key] of xyz.entries()) {
      const original = key === axis ? Math.fround(3.4028234663852886e38) : i + 2;
      check(Object.is(t.pose().translation[key], i < xyz.indexOf(axis) ? original * 2 : original), `overflow ${axis} retains ${key} prefix`);
    }
    check(t.counts().captures === 1 && t.pose().quaternion.w === 1, 'overflow retains real capture');
  }
  for (const axis of xyz) {
    const t = fixture(); t.bind([2]);
    t.hooks.afterCapture = () => {Object.defineProperty(t.pose().translation, axis, {writable: false});};
    rejects(t.animate, `${axis}: non-writable`);
    for (const [i, key] of xyz.entries()) check(t.pose().translation[key] === (i + 2) * (i < xyz.indexOf(axis) ? 2 : 1),
      `read-only ${axis} fails at its store, retains ${key} prefix`);
  }
  // Y and Z must both be read/validated before any X write, in that order.
  for (const axis of ['y', 'z'] as const) {
    const t = fixture(); t.bind([2]);
    t.hooks.afterCapture = () => {t.pose().translation[axis] = NaN; Object.defineProperty(t.pose().translation, 'x', {writable: false});};
    rejects(t.animate, `translation scaling ${axis}`);
    check(t.pose().translation.x === 2, `${axis} snapshot failure precedes X destination access`);
  }
  {
    const t = fixture(); t.bind([2]); t.hooks.afterCapture = () => {t.pose().translation.y = NaN; t.pose().translation.z = NaN;};
    rejects(t.animate, 'translation scaling y');
  }
  for (const axis of ['y', 'z'] as const) {
    const t = fixture(); t.bind([2]);
    t.hooks.afterCapture = () => {t.pose().translation.x = NaN; t.pose().translation[axis] = NaN;};
    rejects(t.animate, `translation scaling ${axis}`);
  }
  {
    const t = fixture(); t.bind([2]);
    Object.defineProperty(t.runtime.getScaleTable(t.actor), '0', {writable: false});
    t.animate(); check(t.pose().translation.x === 4, 'read-only factor is consumed without demanding a write');
  }
  {
    const t = fixture(); t.bind([2]);
    t.hooks.afterCapture = () => {t.pose().translation.x = NaN;};
    rejects(t.animate, 'translation scaling x: expected');
    check(t.pose().translation.y === 3 && t.pose().translation.z === 4, 'invalid X snapshot precedes every scaling store');
  }
  for (const b of [0, 1]) {
    const t = fixture(); t.bind([3]); t.animate(b);
    check(t.pose(b).translation.x === 6 && t.pose(1 - b).translation.x === 11, 'both pose banks and unselected preservation');
  }
  {
    const t = fixture(); t.bind([2, 3]);
    t.hooks.afterCapture = () => {t.binding.poseBuffer35 = 1; t.binding.scaleIndex32 = 1;};
    t.animate(); check(t.pose().translation.x === 2 && t.pose(1).translation.x === 33 && t.pose(1).translation.z === 51,
      'out-of-contract postcapture bank/index mutation reselects live slot1, not captured pose');
    check(t.pose(1).quaternion.w === 31, 'scaling touches no quaternion, even in recaptured bank');
  }
  {
    const t = fixture(); t.bind([2]); t.hooks.afterCapture = () => {t.binding.scaleIndex32 = 255;};
    t.animate(); check(t.pose().translation.x === 2, 'postcapture negative scale byte skips table');
  }
  {
    const t = fixture(); t.bind([2, 3]);
    // An intentionally impure forwarding getter is outside the supported
    // adapter contract; this only probes the explicit second scale32 read.
    t.hooks.getPose = () => {t.binding.scaleIndex32 = 1;};
    t.animate(); check(t.pose().translation.x === 6, 'address selection re-reads scale index after branch check');
  }
  for (const raw of [2, 128, 255]) {
    const t = fixture(); t.bind([2]); t.hooks.afterCapture = () => {t.binding.poseBuffer35 = raw;};
    rejects(t.animate, 'scaling pose bank: addressing');
    check(t.pose().translation.x === 2, 'postcapture invalid signed bank refuses without scaling');
  }
  {
    const t = fixture([1, 1]); t.bind([2]);
    t.hooks.afterCapture = () => {t.source.translation38 += 1;};
    t.animate(); check(t.counts().advances === 2 && t.counts().captures === 2 && t.pose().translation.x === 6,
      'repeated entries repeat actual advancement, capture and scaling, not cumulative stale pose multiplication');
  }
  {
    const t = fixture(); t.bind([2]); t.animate(); t.runtime.getScaleTable(t.actor)[0] = -3; t.animate();
    check(t.pose().translation.x === -6, 'live factor changed on subsequent call');
  }
  for (const raw of [0, 127, 128, 255]) {
    const t = fixture(); t.binding.scaleIndex32 = raw;
    if (raw < 128) {const table = Array<number>(128).fill(2); table[raw] = 3; t.bind(table);}
    t.animate(); check(t.pose().translation.x === (raw < 128 ? 6 : 2), `signed index ${raw}`);
  }
  {
    const t = fixture(); rejects(t.animate, 'translation scaling');
    check(t.pose().translation.x === 2 && t.pose().quaternion.w === 1, 'unbound refusal follows capture');
    t.bind([]); rejects(t.animate, 'translation scaling table: addressing');
  }
  {
    const t = fixture(); t.bind([2]); t.binding.scaleIndex32 = 127; rejects(t.animate, 'translation scaling table: addressing');
  }
  for (const gate of ['negative', 'target', 'null-part', 'count'] as const) {
    const t = fixture(gate === 'target' ? [2] : [1]);
    if (gate === 'negative') t.binding.scaleIndex32 = 255;
    if (gate === 'null-part') {t.binding.descriptor00 = null; t.part.mirror30 = 1;}
    if (gate === 'count') t.header.jointCount1d90 = 1;
    t.animate();
    check(t.counts().captures === (gate === 'negative' || gate === 'target' ? 1 : 0), `${gate} gates unbound table`);
    if (gate === 'null-part') check(t.part.complete2e === 1, 'null part latches completion before scale and mirror');
  }
  for (const raw of [128, 255]) {
    const t = fixture(); t.bind([2]); t.runtime.getScaleTable(t.actor)[0] = NaN; t.binding.scaleIndex32 = raw;
    t.animate(); check(t.pose().translation.x === 2, 'signed negative scale index skips malformed bound table');
  }
  {
    const t = fixture([2]); t.bind([2]); t.runtime.getScaleTable(t.actor)[0] = NaN;
    t.animate(); check(t.pose(0, 2).translation.x === 2, 'non-target1 destination skips malformed bound table');
  }
  {
    const t = fixture(); t.bind([2, 3]); t.runtime.getScaleTable(t.actor)[1] = NaN;
    t.pose(1).translation.y = NaN; t.animate(); check(t.pose().translation.x === 4, 'unconsumed table and pose fields ignored');
    t.binding.scaleIndex32 = 1; rejects(t.animate, 'translation scaling factor');
    check(t.pose().translation.x === 2, 'invalid reached factor refuses before scaling stores');
  }
  {
    const t = fixture(), input = [2]; t.bind(input); input[0] = 9;
    check(t.runtime.getScaleTable(t.actor) !== input && Object.isSealed(t.runtime.getScaleTable(t.actor)), 'copied sealed owned scale table');
    t.animate(); check(t.pose().translation.x === 4, 'caller input mutation cannot alias table');
    rejects(() => t.bind([3]), 'already bound');
    rejects(() => t.runtime.bindScaleTable(Symbol('foreign actor'), [2]), 'unknown/non-owned actor');
    rejects(() => t.runtime.getScaleTable(Symbol('foreign actor')), 'unknown/non-owned actor');
    const other = fixture(); other.bind(t.runtime.getScaleTable(t.actor)); other.runtime.getScaleTable(other.actor)[0] = 7;
    check(t.runtime.getScaleTable(t.actor)[0] === 2, 'second actor cannot alias first table');
  }
  for (const input of [[NaN], [Infinity], [1 / 3], Array<number>(129).fill(1), Array<number>(1)]) {
    const t = fixture(); rejects(() => t.bind(input), input.length === 129 ? 'length' : input[0] === undefined ? 'own data' : 'finite source float32');
    t.bind([2]); t.animate(); check(t.pose().translation.x === 4, 'failed binding does not consume once-only slot');
  }
  {
    const t = fixture(), input = [2]; let reads = 0;
    Object.defineProperty(input, '0', {get() {reads++; return 2;}});
    rejects(() => t.bind(input), 'own data property'); check(reads === 0, 'binding rejects getters without invoking');
  }
  {
    const t = fixture(); t.bind([2]);
    t.adapter.getPose = () => {throw Error('replacement getter must not run');};
    t.poseEffects.convertEulerToQuaternion = () => {throw Error('replacement converter must not run');};
    t.animate(); check(t.pose().translation.x === 4, 'construction snapshots getter and converter function with original receiver');
  }
  for (const rotation of [-0, 1]) {
    const t = fixture(); t.bind([2]); t.source.rotation1c = rotation;
    rejects(t.animate, 'positive zero Euler only'); check(t.pose().translation.x === 2, 'nonfixture rotation refuses before scale');
  }
  for (const at of ['capture', 'getter', 'binding'] as const) {
    const t = fixture(); if (at !== 'binding') t.bind([2]);
    const reenter = () => {rejects(at === 'binding' ? () => t.bind([2]) : t.animate, 'same-runtime reentry');};
    if (at === 'getter') t.hooks.getPose = reenter; else t.hooks.afterCapture = reenter;
    rejects(t.animate, 'same-runtime reentry was caught');
    check(t.pose().translation.x === 2, 'caught reentry poisons caller before scaling writes');
    delete t.hooks.getPose; delete t.hooks.afterCapture;
    if (at === 'binding') t.bind([2]); t.animate();
    check(t.pose().translation.x === 4, 'busy guard clears after refusal and binding was not mutated');
  }
}
