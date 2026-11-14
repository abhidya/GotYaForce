import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceActorAnimationDispatchRuntime, type SourceActorAnimationSetupRequest} from './actor-animation-dispatch.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-setup-test] ${why}`);}
function rejects(run: () => unknown, fragment: string): void {let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);}
function fixture() {
  const unsupported = (): never => {throw Error('unexpected effect');};
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const effects = {interpretAObj: unsupported, animateRObjs: unsupported, animateDObjs: unsupported};
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, effects, {convertEulerToQuaternion: unsupported});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 7, duration24: 9, segment2d: 1, complete2e: 1, mode2f: 2, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 1})));
  const actor = mapping.createActor({descriptor4b0: mapping.createDescriptor([]), jointCount1d90: 0, boundary1d91: 0,
    boundary1d92: 0, boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1}, {parts, poses: [[], []]});
  const part = parts[0]![0]!, descriptors = createSourceAnimationDescriptorBankRuntime();
  // group1 displacement4, action0 displacement4, metadata starts at8.
  const bytes = new Uint8Array(48); bytes[3] = 4; bytes[5] = 4;
  const bank = descriptors.createBytes(bytes), dispatch = createSourceActorAnimationDispatchRuntime(mapping, feedback);
  dispatch.bindActor(actor, {family1d88: bank, shared1d8c: bank, marker578: 0, marker1db3: 0});
  for (const id of parts.flat()) dispatch.bindPart(id, {elapsed08: 3, previous10: 4, previous14: 5, linked36: 1});
  const targets = createSourceStreamWaitTargetRuntime(mapping, feedback, dispatch);
  const starts = createSourceStreamWaitRuntime({mapping, feedback, dispatch, targets});
  targets.bindActor(actor, Array.from({length: 4}, () => ({target08: 0, previous0c: 0, accumulator10: 0})));
  starts.bindActor(actor, {activeMask579: 0, blockedMask1d9a: 0, marker71d: 0}, Array.from({length: 4}, () => ({current00: null, wait14: 0, finished1a: 0, event1e: 0})));
  starts.bindStartActor(actor, {familyBank1d80: null, sharedBank1d84: null, defaultSelector582: 1, marker709: 0});
  const attached = createSourceAttachedJointSetupRuntime({joints, feedback, actors: mapping,
    requests: {requestJoint: unsupported}, fobjs: {getFObj: unsupported}}, effects);
  attached.bindPart(part, {rewind26: 0, loop2c: 0});
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors, actors: mapping, feedback, attached});
  metadata.bindActor(actor, {byte1d74: 0, byte1d75: 0, byte1d76: 0, byte1d77: 0, byte1d94: 0, byte1d95: 0, byte1d98: 0, byte1d99: 0, byte1d9b: 0});
  metadata.bindPart(part, {selector2a: 0, selector2b: 0, auxiliary37: 0});
  // Null archive bank returns -1 without reaching archive records; these explicit
  // refusals cannot manufacture a successful descriptor/setup effect.
  const archiveBanks = createSourceAnimationArchiveBankRuntime({mapping, metadata, archives: {getPartBinding: unsupported, getDescriptor: unsupported}});
  const hooks: {lookup?: () => void; metadata?: () => void} = {};
  const da = {resolveDescriptor(...args: Parameters<typeof descriptors.resolveDescriptor>) {
    check(this === da, 'captured descriptor receiver'); hooks.lookup?.(); return descriptors.resolveDescriptor(...args);
  }};
  const ma = {...metadata, applyMetadata(...args: Parameters<typeof metadata.applyMetadata>) {
    check(this === ma, 'captured metadata receiver'); metadata.applyMetadata(...args); hooks.metadata?.();
  }};
  const runtime = createSourceActorAnimationSetupRuntime({mapping, feedback, dispatch, descriptors: da, metadata: ma, archiveBanks, starts});
  runtime.bindActor(actor, {familyBank1d78: null, sharedBank1d7c: null, movement6d8: 4});
  runtime.bindPart(part, {group28: 3, action29: 4, bank31: 1, status38: 2, field18: 3, field1c: 4, field20: 5});
  const request = Object.defineProperties({group: 0, action: 0, frame: -0}, {
    mode: {get: unsupported}, transition: {get: unsupported},
  }) as SourceActorAnimationSetupRequest;
  const run = () => runtime.setupModeZero(actor, 0, request);
  return {runtime, actor, part, request, run, hooks, da, ma, starts, dispatch, mapping, feedback,
    side: runtime.getPartBinding(part), actual: feedback.getPart(part), clocks: dispatch.getPartBinding(part), mapped: mapping.getPartBinding(part)};
}
export function runActorAnimationSetupSelfTests(): void {
  {
    const x = fixture(); x.run();
    check(x.side.group28 === 0 && x.side.action29 === 0 && x.side.bank31 === 0 && x.side.status38 === 255, 'actual null-bank return stores low byte');
    check(x.actual.mode2f === 0 && x.actual.complete2e === 1 && Object.is(x.actual.frame0c, -0), 'shared feedback and signed zero');
    check(x.clocks.elapsed08 === 0 && x.clocks.previous10 === 0 && Object.is(x.clocks.previous14, -0) && x.clocks.linked36 === 0, 'shared dispatch stores');
    check(x.mapped.poseBuffer35 === 0 && x.mapped.descriptor00 === null && x.side.field18 === 0 && x.side.field1c === 0 && x.side.field20 === 0, 'setup stores, zero-joint actual mapping');
    rejects(() => x.runtime.finishPartOneSetup(x.actor), '4d08c');
    check(x.runtime.getActorBinding(x.actor).movement6d8 === 1, 'postamble store survives refusal');
  }
  {
    const x = fixture(), bank = Symbol('unowned decoded bank');
    x.runtime.getActorBinding(x.actor).familyBank1d78 = bank;
    rejects(x.run, 'unknown/non-owned table cursor');
    check(x.mapped.descriptor00 === bank && x.mapped.poseBuffer35 === 0 && x.actual.complete2e === 0 && x.side.status38 === 2,
      '4a754 stores selected bank and clears completion before archive refusal');
  }
  {
    const x = fixture(); Object.defineProperty(x.side, 'status38', {writable: false});
    rejects(x.run, 'non-writable');
    check(x.actual.complete2e === 0 && x.side.status38 === 2 && x.mapped.poseBuffer35 === 0,
      'archive return precedes status store and completion latch');
  }
  {
    const x = fixture(); x.dispatch.getActorBinding(x.actor).family1d88 = null;
    rejects(x.run, 'owned byte cursor');
    check(x.side.group28 === 3 && x.clocks.previous10 === 4, 'live actual descriptor gates are not copied');
  }
  for (const frame of [NaN, Infinity, 0.1]) {
    const x = fixture(); (x.request as {frame: number}).frame = frame;
    rejects(x.run, 'source float32');
    check(x.side.group28 === 0 && x.side.field20 === 0 && x.clocks.previous10 === 0 && x.clocks.previous14 === 5 && x.clocks.elapsed08 === 3 && x.actual.frame0c === 7 && x.mapped.poseBuffer35 === 1, 'bad frame refuses only at first reached frame store');
  }
  {
    const x = fixture(); x.starts.getStartActorBinding(x.actor).defaultSelector582 = 127;
    rejects(x.run, 'out of bounds'); check(x.side.group28 === 3 && x.side.field20 === 5, 'live actual selector and lookup precede part writes');
  }
  {
    const x = fixture(); x.hooks.lookup = () => {(x.request as {frame: number}).frame = 12;};
    x.da.resolveDescriptor = () => {throw Error('replacement');}; x.ma.applyMetadata = () => {throw Error('replacement');}; x.run();
    check(Object.is(x.actual.frame0c, -0) && Object.is(x.clocks.previous14, -0), 'ABI snapshot in both frame stores and captured functions');
  }
  {
    const x = fixture(); Object.defineProperty(x.clocks, 'previous14', {writable: false});
    rejects(x.run, 'non-writable'); check(x.clocks.previous10 === 0 && x.clocks.elapsed08 === 3 && x.side.field18 === 0, 'reached writable store preserves prefix');
  }
  {
    const x = fixture(); x.hooks.metadata = () => {try {x.run();} catch { /* poison must survive catch */ }};
    rejects(x.run, 'reentry'); check(x.side.group28 === 0 && x.side.field20 === 5, 'caught reentry stops before mode0 initialization');
  }
  {
    const x = fixture(); Object.freeze(x.dispatch.getActorBinding(x.actor)); Object.freeze(x.starts.getStartActorBinding(x.actor));
    x.run(); check(x.side.status38 === 255, 'readonly gate/default operands are legal');
  }
  {
    const x = fixture(); let calls = 0;
    const adapter = {updateActor(id: symbol) {
      check(this === adapter && id === x.actor && x.runtime.getActorBinding(id).movement6d8 === 1, 'postamble store before actual follow-up call'); calls++;
    }};
    x.runtime.bindMovementRuntime(adapter);
    adapter.updateActor = () => {throw Error('replacement must not execute');};
    x.runtime.finishPartOneSetup(x.actor); check(calls === 1, 'captured movement method');
    rejects(() => x.runtime.bindMovementRuntime(adapter), 'already bound');
  }
  for (const failure of ['async', 'reentry', 'readonly'] as const) {
    const x = fixture(); let calls = 0;
    const adapter = {updateActor() {
      calls++;
      if (failure === 'reentry') {try {x.runtime.finishPartOneSetup(x.actor);} catch { /* outer remains poisoned */ }}
      return failure === 'async' ? Promise.resolve() : undefined;
    }};
    x.runtime.bindMovementRuntime(adapter as unknown as Parameters<typeof x.runtime.bindMovementRuntime>[0]);
    if (failure === 'readonly') Object.defineProperty(x.runtime.getActorBinding(x.actor), 'movement6d8', {writable: false});
    rejects(() => x.runtime.finishPartOneSetup(x.actor), {async: 'synchronous undefined', reentry: 'reentry', readonly: 'non-writable'}[failure]);
    check(calls === (failure === 'readonly' ? 0 : 1) && x.runtime.getActorBinding(x.actor).movement6d8 === (failure === 'readonly' ? 4 : 1), 'failed follow-up preserves only reached effects');
  }

}
