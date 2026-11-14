import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceActorMovementFollowupRuntime, type SourceActorMovementFollowupBinding, type SourceActorMovementDescriptorBinding} from './actor-movement-followup.js';
import {createRomActor} from './actor.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-movement-test] ${why}`);}
function equal(actual: number, expected: number, why: string): void {check(Object.is(actual, expected), `${why}: got ${actual}, expected ${expected}`);}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function fixture(deferBind = false, fullMatrices = false) {
  const unsupported = (): never => {throw Error('unexpected unrelated effect');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const mapping = createSourceActorJointMappingRuntime(joints, feedback,
    {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported}, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0})));
  const descriptor = mapping.createDescriptor([]);
  const actor = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 0, boundary1d91: 0,
    boundary1d92: 0, boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(actor, {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  targets.bindActor(actor, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  const waits = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  waits.bindActor(actor, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0},
    Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  waits.bindStartActor(actor, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 0, marker709: 0});
  // These untouched setup dependencies explicitly refuse, rather than provide
  // fake successful metadata/archive effects. Setup owns the actual 6d8 record.
  const setup = createSourceActorAnimationSetupRuntime({mapping, feedback, dispatch,
    descriptors: createSourceAnimationDescriptorBankRuntime(), starts: waits,
    metadata: {getPartBinding: unsupported, applyMetadata: unsupported}, archiveBanks: {resolveArchive: unsupported}});
  setup.bindActor(actor, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 1});
  const actual = createRomActor(); actual.controlWord = 0x40; actual.stepHeight = 91;
  const initial: SourceActorMovementFollowupBinding = {byte661: 0, field66c: 0, field670: 0};
  const hooks: {mapping?: () => void; wait?: () => void; setup?: () => void; matrix?: () => void} = {};
  const mappingAdapter = {
    getActor(id: symbol) {check(this === mappingAdapter, 'mapping original receiver'); hooks.mapping?.(); return mapping.getActor(id);},
    getDescriptor(id: symbol) {check(this === mappingAdapter, 'descriptor original receiver'); return mapping.getDescriptor(id);},
  };
  const waitAdapter = {getActorBinding(id: symbol) {check(this === waitAdapter, 'wait original receiver'); hooks.wait?.(); return waits.getActorBinding(id);}};
  const setupAdapter = {getActorBinding(id: symbol) {check(this === setupAdapter, 'setup original receiver'); hooks.setup?.(); return setup.getActorBinding(id);}};
  const matrixOwner = createSourceActorJointMatrixRuntime(feedback), matrixReads: symbol[] = [];
  const matrixAdapter = {getMatrix(id: symbol) {
    check(this === matrixAdapter, 'matrix original receiver'); matrixReads.push(id); hooks.matrix?.(); return matrixOwner.getMatrix(id);
  }};
  const runtime = createSourceActorMovementFollowupRuntime({mapping: mappingAdapter, waits: waitAdapter, setup: setupAdapter,
    ...(fullMatrices ? {matrixOwner: matrixAdapter} : {})});
  const bind = () => runtime.bindActor(actor, actual, initial);
  if (!deferBind) bind();
  const bindNormal = (values: readonly number[] = [20, 20], bytes: SourceActorMovementDescriptorBinding =
    {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255}) => {
    runtime.bindDescriptor(descriptor, bytes); runtime.bindWorldMatrixY(actor, values);
  };
  return {matrixOwner, matrixAdapter, matrixReads, runtime, actual, actor, descriptor, mapping, waits, setup, initial, bind, bindNormal,
    mappingAdapter, waitAdapter, setupAdapter, hooks, run: () => runtime.updateActor(actor)};
}
export function runActorMovementFollowupSelfTests(): void {
  {
    const x = fixture();
    const input: SourceActorMovementDescriptorBinding = {joint0f: 255, joint22: 1, joint2a: 2, joint32: 3, joint3a: 4,
      byte23: 255, byte24: 254, byte25: 253, byte26: 2, byte27: 1, byte2b: 251, byte2c: 250, byte2d: 249,
      byte2e: 248, byte2f: 247, byte33: 246, byte34: 245, byte35: 244, byte36: 243, byte37: 242,
      byte3b: 241, byte3c: 240, byte3d: 239, byte3e: 238, byte3f: 237};
    x.runtime.bindDescriptor(x.descriptor, input);
    const owned = x.runtime.getDescriptorBinding(x.descriptor);
    check(Object.keys(input).every(key => (owned as unknown as Record<string, number>)[key] === (input as unknown as Record<string, number>)[key]),
      'all explicit correction descriptor bytes retain exact unsigned bits on the existing descriptor owner');
    input.byte23 = 0; input.joint22 = 0;
    check(owned.byte23 === 255 && owned.joint22 === 1 && Object.isSealed(owned),
      'descriptor storage is owned rather than borrowed, with no duplicate correction joint identity');
    owned.byte23 = 7; check(x.runtime.getDescriptorBinding(x.descriptor).byte23 === 7, 'correction descriptor bytes remain live owned fields');
  }
  {
    const x = fixture(); x.runtime.bindDescriptor(x.descriptor, {joint0f: 255, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
    check(!Object.hasOwn(x.runtime.getDescriptorBinding(x.descriptor), 'byte23'), 'absent correction descriptor bytes are not zero-filled');
  }
  for (const bad of [256, -1, 0.5, NaN]) {
    const x = fixture(); rejects(() => x.runtime.bindDescriptor(x.descriptor,
      {joint0f: 255, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255, byte3f: bad}), 'unsigned integer');
  }
  {
    const x = fixture(false, true), make = (y: number) => x.matrixOwner.createMatrix([1, 0, 0, 300, 0, 1, 0, y, 0, 0, 1, 500]);
    const root = make(20), body = make(40), slots = [root, body];
    x.runtime.bindDescriptor(x.descriptor, {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
    x.runtime.bindWorldMatrices(x.actor, slots); slots[0] = Symbol('external replacement');
    x.matrixReads.length = 0; x.matrixAdapter.getMatrix = () => {throw Error('replacement matrix getter');};
    x.run(); equal(x.actual.stepHeight, 7, 'full-matrix Y loads use index7 on original captured owner');
    check(x.matrixReads.length === 2 && x.matrixReads[0] === body && x.matrixReads[1] === root,
      'reached source order reads existing joint1 then root, without a recompute or table copy');
    x.matrixOwner.getMatrix(root)[7] = 60; x.run(); equal(x.actual.stepHeight, 21, 'live full-matrix writes feed later movement');
    x.actual.controlWord = 0; x.matrixOwner.getMatrix(body)[7] = NaN; x.matrixReads.length = 0;
    x.run(); equal(x.actual.stepHeight, 0, 'early movement gate skips invalid existing matrix');
    check(x.matrixReads.length === 0, 'early gate never resolves matrix owner');
    x.actual.controlWord = 0x40; x.actual.stepHeight = 91;
    rejects(x.run, 'float32'); equal(x.actual.stepHeight, 91, 'initial generated matrix failure precedes first movement store');
    rejects(() => x.runtime.bindWorldMatrixY(x.actor, [1, 2]), 'already bound');
    rejects(() => x.runtime.bindWorldMatrices(x.actor, slots), 'already bound');
    rejects(() => x.runtime.getWorldMatrixY(x.actor), 'explicitly bound');
  }
  {
    const x = fixture(false, true), make = () => x.matrixOwner.createMatrix([1, 0, 0, 0, 0, 1, 0, 20, 0, 0, 1, 0]);
    const a = make(), b = make();
    x.runtime.bindDescriptor(x.descriptor, {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
    x.runtime.bindWorldMatrices(x.actor, [a, b]); x.matrixReads.length = 0;
    x.hooks.matrix = () => {try {x.run();} catch { /* caught reentry must poison enclosing load */ }};
    rejects(x.run, 'reentry'); equal(x.actual.stepHeight, 91, 'matrix adapter reentry poisons before initial store');
    delete x.hooks.matrix;
    Object.freeze(x.matrixOwner.getMatrix(a)); Object.freeze(x.matrixOwner.getMatrix(b));
    x.run(); equal(x.actual.stepHeight, 7, 'readonly actual matrices remain valid movement inputs');
  }
  {
    const x = fixture(); rejects(() => x.runtime.bindWorldMatrices(x.actor, []), 'matrix owner');
    const y = fixture(false, true); y.bindNormal(); rejects(() => y.runtime.bindWorldMatrices(y.actor, []), 'already bound');
    const z = fixture(false, true); rejects(() => z.runtime.bindWorldMatrices(z.actor, [Symbol('foreign')]), 'unknown/non-owned');
    rejects(() => z.runtime.bindWorldMatrices(z.actor, [null as unknown as symbol]), 'symbol');
  }
  {
    const x = fixture(); x.actual.borgNumber = 0x05ff; x.actual.controlWord = NaN;
    x.runtime.getActorBinding(x.actor).byte661 = NaN; x.waits.getActorBinding(x.actor).marker71d = NaN;
    x.actual.stepHeight = NaN; x.run(); equal(x.actual.stepHeight, 0, 'high borg byte short circuits every other operand and overwrites stale NaN');
  }
  {
    const x = fixture(); x.actual.borgNumber = 5; x.waits.getActorBinding(x.actor).marker71d = 2;
    x.actual.modelScale = 2; x.run(); equal(x.actual.stepHeight, 10, 'low borg byte 5 does not select early zero');
  }
  for (const gate of ['byte661', 'controlWord'] as const) {
    const x = fixture(); x.waits.getActorBinding(x.actor).marker71d = NaN; x.actual.modelScale = NaN;
    if (gate === 'byte661') {x.runtime.getActorBinding(x.actor).byte661 = 255; x.actual.controlWord = NaN;}
    else x.actual.controlWord = 0x80;
    x.run(); equal(x.actual.stepHeight, 0, `${gate} short circuit skips marker and scale`);
  }
  for (const marker of [1, 2, 127, 128, 255]) {
    const x = fixture(); x.waits.getActorBinding(x.actor).marker71d = marker; x.actual.modelScale = 2;
    x.runtime.getActorBinding(x.actor).field66c = NaN; x.runtime.getActorBinding(x.actor).field670 = NaN;
    x.mapping.getActor(x.actor).descriptor4b0 = null; x.actual.pos.y = NaN;
    x.setup.getActorBinding(x.actor).movement6d8 = NaN;
    x.run(); equal(x.actual.stepHeight, (((marker << 24) >> 24) - 1) * 10, `signed marker ${marker} has no general-path loads/clamp`);
  }
  {
    const x = fixture(); x.waits.getActorBinding(x.actor).marker71d = 1; x.actual.modelScale = -1;
    x.run(); equal(x.actual.stepHeight, -0, 'marker zero times negative scale preserves -0');
  }
  {
    const x = fixture(); x.waits.getActorBinding(x.actor).marker71d = 2; x.actual.modelScale = 0.1;
    rejects(x.run, 'float32'); equal(x.actual.stepHeight, 91, 'marker scale refusal before only store');
  }
  {
    const x = fixture(); x.waits.getActorBinding(x.actor).marker71d = 127; x.actual.modelScale = Math.fround(3e38);
    rejects(x.run, 'fmuls'); equal(x.actual.stepHeight, 91, 'marker overflow before only store');
  }
  {
    const x = fixture(); x.bindNormal([50, 40, 30, 20, 10], {joint0f: 0, joint22: 2, joint2a: 3, joint32: 4, joint3a: 255});
    x.actual.pos.y = 4; x.actual.modelScale = NaN;
    x.runtime.getActorBinding(x.actor).field66c = 8; x.runtime.getActorBinding(x.actor).field670 = 3;
    x.setup.getActorBinding(x.actor).movement6d8 = 2; x.run();
    equal(x.actual.stepHeight, Math.fround(3 * Math.fround(Math.fround(0.7) * 2)), 'normal minimum, live setup scale and no modelScale load');
  }
  {
    const x = fixture(); x.bindNormal([0, 0]); x.run();
    equal(x.actual.stepHeight, -0, 'fnmsubs negates after fused rounding; final comparison preserves -0');
  }
  {
    const x = fixture(), tiny = 2 ** -149; x.bindNormal([4 * tiny, 10 * tiny]);
    x.actual.pos.y = tiny; x.setup.getActorBinding(x.actor).movement6d8 = 2; x.run();
    equal(x.actual.stepHeight, tiny, 'root fmadds uses one rounding, including gradual underflow');
  }
  {
    const x = fixture(), height = 0.42916440963745117; x.bindNormal([10, height]);
    x.setup.getActorBinding(x.actor).movement6d8 = 0.1778261512517929; x.run();
    equal(x.actual.stepHeight, 0.05342165753245354, 'tail computes .7f times movement before height times product');
    check(x.actual.stepHeight !== 0.05342165380716324, 'wrong left-associated tail is distinguishable');
  }
  {
    const x = fixture(); x.bindNormal([2, 2]); x.actual.pos.y = 10; x.run(); equal(x.actual.stepHeight, 0, 'negative final result clamps to positive zero');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.setup.getActorBinding(x.actor).movement6d8 = -1;
    x.run(); equal(x.actual.stepHeight, 0, 'negative movement is consumed, then final clamp runs');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.waits.getActorBinding(x.actor).marker71d = 2;
    x.run(); equal(x.actual.stepHeight, 5, 'live shared marker update, not copied at bind');
    x.waits.getActorBinding(x.actor).marker71d = 0; x.setup.getActorBinding(x.actor).movement6d8 = 2;
    x.run(); equal(x.actual.stepHeight, 14, 'live shared setup movement, not copied at bind');
  }
  {
    const x = fixture(); x.runtime.getActorBinding(x.actor).field670 = NaN;
    rejects(x.run, 'field670'); equal(x.actual.stepHeight, 91, 'entry670 load precedes absent initial matrix');
  }
  {
    const x = fixture(); rejects(x.run, 'explicitly bound'); equal(x.actual.stepHeight, 91, 'absent world matrix cannot use actor aim anchors');
    x.runtime.bindWorldMatrixY(x.actor, [20]); rejects(x.run, 'outside explicitly owned'); equal(x.actual.stepHeight, 91, '+920 requires joint-one Y storage');
  }
  {
    const x = fixture(); x.runtime.bindWorldMatrixY(x.actor, [20, 20]); x.runtime.getActorBinding(x.actor).field66c = NaN;
    rejects(x.run, 'field66c'); equal(x.actual.stepHeight, 20, '+920 copy precedes field66c refusal');
  }
  {
    const x = fixture(); x.runtime.bindWorldMatrixY(x.actor, [20, 20]); x.runtime.getActorBinding(x.actor).field66c = 8;
    rejects(x.run, 'descriptor byte'); equal(x.actual.stepHeight, 16, 'descriptor metadata is needed only after fnmsubs store');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.mapping.getActor(x.actor).descriptor4b0 = null;
    x.runtime.getActorBinding(x.actor).field66c = 8;
    rejects(x.run, 'descriptor byte'); equal(x.actual.stepHeight, 16, 'null symbolic descriptor retained until reached byte load');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.runtime.getDescriptorBinding(x.descriptor).joint0f = 255;
    rejects(x.run, 'negative world-matrix'); equal(x.actual.stepHeight, 20, 'root -1 is not the loop sentinel');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); const d = x.runtime.getDescriptorBinding(x.descriptor);
    d.joint22 = 254; rejects(x.run, 'negative world-matrix'); equal(x.actual.stepHeight, 10, 'negative loop address refuses after root minimum store');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); const d = x.runtime.getDescriptorBinding(x.descriptor);
    d.joint22 = 255; d.joint2a = NaN; d.joint32 = NaN; d.joint3a = NaN;
    x.run(); equal(x.actual.stepHeight, 7, 'signed -1 sentinel skips all later list bytes');
  }
  {
    const x = fixture(); x.bindNormal([20, 20, 3], {joint0f: 0, joint22: 2, joint2a: 2, joint32: 2, joint3a: 2});
    x.run(); equal(x.actual.stepHeight, Math.fround(3 * Math.fround(0.7)), 'four non-sentinel slots finish without reading a fifth');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.actual.pos.y = 2; x.setup.getActorBinding(x.actor).movement6d8 = NaN;
    rejects(x.run, 'movement6d8'); equal(x.actual.stepHeight, 9, 'relative-height store survives late movement admission failure');
  }
  {
    const x = fixture(); x.bindNormal([Math.fround(3e38), Math.fround(3e38)]);
    x.setup.getActorBinding(x.actor).movement6d8 = Math.fround(3e38);
    rejects(x.run, 'fmuls'); equal(x.actual.stepHeight, Math.fround(1.5e38), 'late product overflow preserves already stored relative height');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]); x.runtime.getActorBinding(x.actor).field66c = NaN;
    Object.defineProperty(x.actual, 'stepHeight', {writable: false});
    rejects(x.run, 'non-writable'); equal(x.actual.stepHeight, 91, 'first destination admission precedes later input reads');
  }
  {
    const x = fixture(); x.bindNormal([20, 20]);
    for (const key of ['borgNumber', 'controlWord', 'modelScale', 'pos'] as const) Object.defineProperty(x.actual, key, {writable: false});
    Object.freeze(x.actual.pos); Object.freeze(x.runtime.getActorBinding(x.actor));
    Object.freeze(x.mapping.getActor(x.actor)); Object.freeze(x.waits.getActorBinding(x.actor));
    Object.freeze(x.setup.getActorBinding(x.actor)); Object.freeze(x.runtime.getDescriptorBinding(x.descriptor)); Object.freeze(x.runtime.getWorldMatrixY(x.actor));
    x.run(); equal(x.actual.stepHeight, 7, 'readonly source operands accepted, only destination must be writable');
  }
  {
    const x = fixture(true); Object.freeze(x.initial);
    x.mappingAdapter.getActor = () => {throw Error('replacement getter');};
    x.mappingAdapter.getDescriptor = () => {throw Error('replacement descriptor getter');};
    x.waitAdapter.getActorBinding = () => {throw Error('replacement wait getter');};
    x.setupAdapter.getActorBinding = () => {throw Error('replacement setup getter');};
    x.bind(); x.bindNormal(Object.freeze([20, 20]), Object.freeze({joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255}));
    x.run(); equal(x.actual.stepHeight, 7, 'captured methods and original receivers, readonly bind inputs');
  }
  {
    const x = fixture(true); x.hooks.mapping = () => {try {x.bind();} catch { /* caught inner refusal must poison outer bind */ }};
    rejects(x.bind, 'reentry'); rejects(x.run, 'unknown/non-owned');
    delete x.hooks.mapping; x.bind(); x.actual.controlWord = 0; x.run(); equal(x.actual.stepHeight, 0, 'new outer operation recovers after poisoned binding');
  }
  {
    const x = fixture(); rejects(x.bind, 'already bound');
    rejects(() => x.runtime.bindActor(Symbol('different source'), x.actual, x.initial), 'already assigned');
    rejects(() => x.runtime.bindDescriptor(Symbol('foreign descriptor'), {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255}), 'unknown/non-owned');
    rejects(() => x.runtime.updateActor(Symbol('foreign actor')), 'unknown/non-owned');
    x.bindNormal(); rejects(() => x.runtime.bindWorldMatrixY(x.actor, []), 'already bound');
    rejects(() => x.runtime.bindDescriptor(x.descriptor, {joint0f: 0, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255}), 'already bound');
  }
  {
    const x = fixture(); let calls = 0;
    Object.defineProperty(x.actual, 'borgNumber', {get() {calls++; return 0;}});
    rejects(x.run, 'own data property'); check(calls === 0, 'source accessor rejected without invoking it');
  }
  {
    const x = fixture(); const values = [20, 20]; x.bindNormal(values); values[0] = -500;
    x.initial.byte661 = 1; x.run();
    equal(x.actual.stepHeight, 7, 'external initial arrays and records are not retained as mutable storage');
    x.runtime.getWorldMatrixY(x.actor)[0] = 40; x.run();
    equal(x.actual.stepHeight, 14, 'new sidecars/matrix copied at bind, owned exposed matrix remains live');
  }
}
