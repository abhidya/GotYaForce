import {createSourceActorAnimationTransitionRuntime, divideSourceAnimationFloat32,
  hasIncompleteSourceActorAnimationTransition} from './actor-animation-transition.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceActorAnimationDispatchRuntime, isSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
function check(value: boolean, message: string): void {if (!value) throw Error(`[animation-transition-test] ${message}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(expected), `expected ${expected}, got ${error || 'success'}`);
}
function fixture(count = 1) {
  const unsupported = (): never => {throw Error('unreached actual dependency');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const effects = {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported};
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, effects, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, (_, bank) => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: bank ? 50 : 4, duration24: bank ? -100 : 9, segment2d: bank ? 0 : 2, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: bank, poseBuffer35: bank})));
  const poses = Array.from({length: 2}, (_, bank) => Array.from({length: 2}, () => feedback.createPose(
    {translation: {x: bank ? 30 : 10, y: bank ? 40 : 20, z: bank ? 50 : -0}, quaternion: {x: 0, y: 0, z: 0, w: 1}})));
  const descriptor = mapping.createDescriptor(count === 0 ? [] : Array.from({length: count}, () => 1));
  const actor = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 2, boundary1d91: count,
    boundary1d92: count, boundary1d93: count, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses});
  const descriptors = createSourceAnimationDescriptorBankRuntime(), bytes = new Uint8Array(48); bytes[3] = 4; bytes[5] = 4;
  const descriptorBank = descriptors.createBytes(bytes), dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(actor, {family1d88: descriptorBank, shared1d8c: descriptorBank, marker578: 0, marker1db3: 0});
  const attached = createSourceAttachedJointSetupRuntime({joints, feedback, actors: mapping,
    requests: {requestJoint: unsupported}, fobjs: {getFObj: unsupported}}, effects);
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  const starts = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  targets.bindActor(actor, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  starts.bindActor(actor, {activeMask579: 15, blockedMask1d9a: 0, marker71d: 0}, Array.from({length: 4}, () =>
    ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  starts.bindStartActor(actor, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 1, marker709: 0});
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors, actors: mapping, feedback, attached});
  metadata.bindActor(actor, {byte1d74: 11, byte1d75: 12, byte1d76: 21, byte1d77: 22,
    byte1d94: 31, byte1d95: 32, byte1d98: 0, byte1d99: 0, byte1d9b: 0});
  const archives = createSourceArchiveJointSetupRuntime({actors: mapping,
    archives: {getArchive: unsupported, getPublicName: unsupported, getPublicAddress: unsupported, cursorOffset: unsupported},
    attachment: {getDescriptor: unsupported, addAnimation: unsupported}, tail: attached});
  mapping.bindSetupRuntime(archives);
  const archiveBanks = createSourceAnimationArchiveBankRuntime({mapping, metadata, archives});
  const inputs = {mapping, feedback, dispatch, descriptors, metadata, archiveBanks, starts};
  const setup = createSourceActorAnimationSetupRuntime(inputs);
  setup.bindActor(actor, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 3});
  for (const [bank, row] of parts.entries()) for (const id of row) {
    dispatch.bindPart(id, {elapsed08: bank ? 50 : 2, previous10: bank ? 51 : 3, previous14: bank ? 52 : -0, linked36: bank ? 8 : 9});
    attached.bindPart(id, {rewind26: bank ? -11 : -12, loop2c: bank ? 3 : 4});
    metadata.bindPart(id, {selector2a: bank ? 22 : 23, selector2b: bank ? 24 : 25, auxiliary37: bank ? 26 : 27});
    archives.bindPart(id, {descriptor04: null});
    setup.bindPart(id, {group28: bank ? 32 : 33, action29: bank ? 34 : 35, bank31: bank, status38: bank ? 36 : 37,
      field18: bank ? 40 : 41, field1c: bank ? 42 : 43, field20: bank ? 44 : 45});
  }
  const transition = createSourceActorAnimationTransitionRuntime({mapping, feedback, dispatch, setup, attached, metadata, archives});
  for (const [bank, row] of parts.entries()) for (const id of row) transition.bindPartRaw(id,
    {byte34: 80 + bank, byte39: 81 + bank, byte3a: 82 + bank, byte3b: 83 + bank, byte3c: 84 + bank,
      byte3d: 85 + bank, byte3e: 86 + bank, byte3f: 87 + bank});
  transition.bindDescriptor(descriptor, {byte42: 1, byte43: 1});
  setup.bindTransitionRuntime(transition); dispatch.bindTransitionRuntime(transition); dispatch.bindSetupRuntime(setup);
  const id = parts[0]![0]!, backup = parts[1]![0]!;
  return {mapping, feedback, dispatch, setup, transition, attached, metadata, archives, archiveBanks, starts, inputs,
    actor, descriptor, parts, poses, id, backup, header: mapping.getActor(actor),
    current: feedback.getPose(poses[0]![1]!), previous: feedback.getPose(poses[1]![1]!),
    state: setup.getPartBinding(id), actual: feedback.getPart(id), clocks: dispatch.getPartBinding(id),
    visibility: metadata.getActorBinding(actor), request: {frame: 0, group: 0, action: 0, transition: 6, mode: 1},
    begin: () => dispatch.setupPart(actor, 0, {blockedMask1d9a: 0}, {frame: 0, group: 0, action: 0, transition: 6, mode: 1})};
}
export function runActorAnimationTransitionSelfTests(): void {
  {
    const x = fixture(); check(isSourceActorAnimationDispatchRuntime(x.dispatch) && !isSourceActorAnimationDispatchRuntime({...x.dispatch}), 'dispatch brand cannot be copied');
    x.transition.copyPart(x.actor, 0, 0, 0);
    for (const runtime of [x.setup, x.dispatch, x.attached, x.metadata, x.archives] as const) {
      const a = runtime.getPartBinding(x.id), b = runtime.getPartBinding(x.backup);
      for (const key of Object.keys(a)) check(Object.is((a as unknown as Record<string, unknown>)[key], (b as unknown as Record<string, unknown>)[key]), `canonical copy ${key}`);
    }
    for (const key of Object.keys(x.actual)) check(Object.is((x.actual as unknown as Record<string, unknown>)[key],
      (x.feedback.getPart(x.backup) as unknown as Record<string, unknown>)[key]), `feedback copy ${key}`);
    check(x.mapping.getPartBinding(x.backup).jointBank33 === 1, 'post-copy bank overwrite');
    for (const key of ['descriptor00', 'scaleIndex32', 'poseBuffer35'] as const)
      check(Object.is(x.mapping.getPartBinding(x.id)[key], x.mapping.getPartBinding(x.backup)[key]), `mapping copy ${key}`);
    check(x.transition.getPartRaw(x.backup).byte34 === 80 && x.transition.getPartRaw(x.backup).byte3f === 87, 'all absent padding copied');
    check(x.visibility.byte1d76 === 11 && x.visibility.byte1d77 === 12 && x.visibility.byte1d94 === 31, 'channel0 bank history only');
    check(x.previous.translation.x === 10 && Object.is(x.previous.translation.z, -0), 'pose translation signed-zero copy');
    x.transition.copyPart(x.actor, 1, 0, 1);
    check(x.mapping.getPartBinding(x.id).jointBank33 === 0, 'reverse bank copy xor1');
  }
  {
    const x = fixture(), source = {mapping: x.mapping, feedback: x.feedback, dispatch: x.dispatch, setup: x.setup,
      attached: x.attached, metadata: x.metadata, archives: x.archives};
    rejects(() => createSourceActorAnimationTransitionRuntime({...source, mapping: {...x.mapping}}), 'matched genuine setup');
    rejects(() => createSourceActorAnimationTransitionRuntime({...source, metadata: {...x.metadata}}), 'matched genuine metadata');
    rejects(() => createSourceActorAnimationTransitionRuntime({...source, archives: {...x.archives}}), 'matched genuine metadata');
    rejects(() => createSourceActorAnimationTransitionRuntime({...source, attached: {...x.attached}}), 'matched genuine metadata');
    const original = x.inputs.mapping; x.inputs.mapping = {...x.mapping}; x.inputs.metadata = {...x.metadata};
    check(x.setup.getActualMapping() === original && x.setup.getActualMetadata() === x.metadata, 'source container mutation cannot redirect captured provenance');
    x.begin(); check(x.actual.mode2f === 1, 'captured original sources execute after container replacement');
  }
  {
    const x = fixture(); const dest = x.setup.getPartBinding(x.backup);
    Object.defineProperty(x.metadata.getPartBinding(x.backup), 'selector2b', {writable: false});
    rejects(() => x.transition.copyPart(x.actor, 0, 0, 0), 'non-writable');
    check(dest.field20 === 45 && dest.group28 === 32 && dest.action29 === 34 && x.metadata.getPartBinding(x.backup).selector2a === 22,
      'preceding words retained, packed word atomically refuses');
    check(hasIncompleteSourceActorAnimationTransition(x.header), 'copy failure consumes actor');
    x.dispatch.getActorBinding(x.actor).family1d88 = null; x.actual.mode2f = 0;
    rejects(() => x.dispatch.updatePart(x.actor, 0), 'incomplete mode1');
    rejects(() => x.setup.setupModeZero(x.actor, 0, x.request), 'incomplete mode1');
  }
  {
    const x = fixture(); Object.defineProperty(x.actual, 'frame0c', {value: NaN});
    rejects(() => x.transition.copyPart(x.actor, 0, 0, 1), 'finite exact');
    check(x.dispatch.getPartBinding(x.backup).elapsed08 === 50, 'second paired load failure precedes either destination store');
  }
  {
    const x = fixture(); x.mapping.getPartBinding(x.id).scaleIndex32 = 12; x.transition.getPartRaw(x.id).byte34 = NaN;
    rejects(() => x.transition.copyPart(x.actor, 0, 0, 1), 'integer out of bounds');
    check(x.mapping.getPartBinding(x.backup).scaleIndex32 === 255 && x.setup.getPartBinding(x.backup).group28 === 33,
      'second packed word load preserves preceding pairs but neither word of failed pair');
  }
  {
    const x = fixture(); x.header.descriptor4b0 = null;
    x.transition.copyPart(x.actor, 0, 0, 1);
    check(x.previous.translation.x === 30 && x.visibility.byte1d76 === 11, 'copyMode1 skips range/descriptor/pose after part and visibility');
  }
  {
    const x = fixture(); Object.defineProperty(x.previous.quaternion, 'y', {writable: false});
    x.current.quaternion.x = 0.25;
    rejects(() => x.transition.copyPart(x.actor, 0, 0, 0), 'non-writable');
    check(x.previous.quaternion.x === 0.25 && x.previous.translation.x === 30, 'each quaternion word store retains prefix');
  }
  for (const [weight, expected, visibility] of [[0, 10, 11], [0.5, 20, 11], [1, 30, 21], [-1, -10, 11], [2, 50, 21]]) {
    const x = fixture(); x.transition.blendPart(x.actor, 0, weight!);
    check(x.current.translation.x === expected && x.current.quaternion.w === 1, 'real linear pose blend without clamp');
    check(x.visibility.byte1d94 === visibility && x.visibility.byte1d95 === 32, 'threshold equality and first matching descriptor');
  }
  {
    const x = fixture(); x.previous.quaternion.w = -1; x.transition.blendPart(x.actor, 0, 0.75);
    check(x.current.quaternion.w === 1 && x.previous.quaternion.w === -1, 'hemisphere flips local copy only');
  }
  {
    const x = fixture(); Object.defineProperty(x.current.translation, 'y', {writable: false});
    rejects(() => x.transition.blendPart(x.actor, 0, 0.5), 'non-writable');
    check(x.current.translation.x === 10 && Object.is(x.current.translation.z, -0), 'paired xy store refuses atomically');
  }
  {
    const x = fixture(); Object.defineProperty(x.current.translation, 'z', {writable: false});
    rejects(() => x.transition.blendPart(x.actor, 0, 0.5), 'non-writable');
    check(x.current.translation.x === 20 && x.current.translation.y === 30, 'z store failure retains completed paired xy store');
  }
  {
    const x = fixture(); Object.defineProperty(x.current.quaternion, 'x', {writable: false});
    rejects(() => x.transition.blendPart(x.actor, 0, 0), 'non-writable');
    check(x.visibility.byte1d94 === 31, 'mandatory equal quaternion store is not elided');
  }
  for (const value of [0.9999899864196777, 0.9999900460243225]) {
    const x = fixture(); x.previous.quaternion.w = value;
    if (value === 0.9999899864196777) rejects(() => x.transition.blendPart(x.actor, 0, 0.5), 'callee8023cc8c');
    else {x.transition.blendPart(x.actor, 0, 0.5); check(x.current.quaternion.w === Math.fround(0.5 + Math.fround(0.5 * value)), 'strict above-threshold real linear quaternion');}
  }
  {
    const x = fixture(); x.previous.quaternion.w = 0; x.previous.quaternion.x = 1;
    rejects(() => x.transition.blendPart(x.actor, 0, 0.5), 'callee8023cc8c');
    check(x.current.translation.x === 20 && x.current.quaternion.w === 1 && x.visibility.byte1d94 === 31,
      'nonlinear refuses after translation before quaternion/visibility');
    rejects(() => x.transition.blendPart(x.actor, 0, 0), 'incomplete mode1');
  }
  {
    const x = fixture(2); x.transition.blendPart(x.actor, 0, 0.5);
    check(x.current.translation.x === 25, 'duplicate mapped joints repeat actual blend');
  }
  {
    const x = fixture(0); x.header.descriptor4b0 = null; x.transition.blendPart(x.actor, 0, 0.5);
    check(x.current.translation.x === 10, 'empty range does not read descriptor or poses');
  }
  {
    const x = fixture(); x.begin();
    check(x.actual.mode2f === 1 && x.state.field18 === 7 && x.state.field1c === 1 && x.clocks.elapsed08 === 0 && x.actual.frame0c === 0,
      'genuine mode1 setup writes canonical clocks');
    x.clocks.linked36 = 99;
    for (let i = 0; i < 6; i++) x.dispatch.updatePart(x.actor, 0);
    check(x.actual.mode2f === 0 && x.state.field1c === 7 && x.actual.frame0c === 0 && x.clocks.elapsed08 === 6,
      'mode1 six real updates complete blend, linked36 is unused');
    x.clocks.linked36 = 0; x.dispatch.updatePart(x.actor, 0);
    check(x.actual.frame0c === 1 && x.clocks.previous14 === 0 && x.clocks.previous10 === 6, 'following update is real mode0');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = 2.5; x.begin(); x.dispatch.updatePart(x.actor, 0); x.dispatch.updatePart(x.actor, 0);
    check(x.actual.frame0c === 0.5 && x.state.field1c === 7.5 && x.actual.mode2f === 0, 'mode1 preserves overshoot');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = 0; x.begin(); x.dispatch.updatePart(x.actor, 0);
    check(x.state.field1c === 0 && x.actual.mode2f === 1 && x.state.field20 === 1, 'zero timestep mandatory blend writes without clock progress');
  }
  {
    const x = fixture(); x.setup.setupModeOne(x.actor, 0, {...x.request, transition: 0});
    check(x.actual.mode2f === 0 && x.state.field18 === 0 && x.transition.getPartRaw(x.backup).byte34 === 81, 'transition zero exact mode0 without backup');
  }
  {
    const x = fixture(); x.setup.getActorBinding(x.actor).familyBank1d78 = Symbol('unowned');
    rejects(x.begin, 'unknown/non-owned');
    check(x.transition.getPartRaw(x.backup).byte34 === 80 && hasIncompleteSourceActorAnimationTransition(x.header), 'failure after successful backup consumes containing setup');
    rejects(() => x.dispatch.updatePart(x.actor, 0), 'incomplete mode1');
  }
  {
    const x = fixture(0); let calls = 0;
    x.setup.bindMovementRuntime({updateActor() {calls++;}});
    rejects(() => x.dispatch.setupPart(x.actor, 1, {blockedMask1d9a: 0}, x.request), 'genuine matched 4d08c');
    check(x.setup.getActorBinding(x.actor).movement6d8 === 1 && calls === 0 &&
      x.feedback.getPart(x.parts[0]![1]!).mode2f === 1 && hasIncompleteSourceActorAnimationTransition(x.header),
      'real setup precedes mandatory6d8 then fake movement refusal consumes whole setup');
    x.setup.getActorBinding(x.actor).movement6d8 = 9;
    rejects(() => x.setup.finishPartOneSetup(x.actor), 'incomplete mode1');
    check(x.setup.getActorBinding(x.actor).movement6d8 === 9 && calls === 0, 'direct legacy post cannot bypass poisoned containingmode1');
  }
  {
    const x = fixture(); x.begin(); Object.defineProperty(x.state, 'field1c', {writable: false});
    rejects(() => x.dispatch.updatePart(x.actor, 0), 'non-writable');
    check(x.clocks.elapsed08 === 1 && x.clocks.previous10 === 0, 'playback failure preserves snapshots and elapsed store');
    x.actual.mode2f = 0; x.dispatch.getActorBinding(x.actor).family1d88 = null;
    rejects(() => x.dispatch.updatePart(x.actor, 0), 'incomplete mode1');
    check(x.clocks.previous10 === 0, 'no repeated snapshot after failure');
  }
  check(Object.is(divideSourceAnimationFloat32(-0, 3), -0) && divideSourceAnimationFloat32(1, 7) === Math.fround(1 / 7), 'exact division zero and ordinary ratio');
  rejects(() => divideSourceAnimationFloat32(1, 0), 'zero divisor');
  console.log('[animation-transition] PASS: complete canonical part/pose copy, real linear pose blending, mode1 setup/playback and retained consumed failure prefixes; nonlinear/retail hydration remain unsupported');
}
