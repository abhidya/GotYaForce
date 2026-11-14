import {hitBin, sourceTerrainGrid} from '@gf/formats';
import type {BorgRuntime, WeaponCell} from '../types.js';
import {NeoGredMeleeState} from '../neoGredMelee.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorTickPrefixRuntime, isSourceActorTickPrefixClaimedActor} from './actor-tick-prefix.js';
import {createSourceActorStatusTimersRuntime, type SourceActorStatusAmmoSlot} from './actor-status-timers.js';
import {createSourceActorTerrainQueryRuntime, type SourceActorTerrainQueryRuntime, type SourceActorTerrainGlobals} from './actor-terrain-query.js';
import {createSourceActorTransformHistoryRuntime, type SourceActorTransformHistoryRuntime} from './actor-transform-history.js';
import {createSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateStorage} from './actor-matrix-update.js';
import {createSourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {createSourceActorJointMatrixRuntime} from './actor-joint-matrix.js';
import {createSourceJObjModelHydrationRuntime} from './jobj-model-hydration.js';
import {createSourceDisplayAnimationAttachmentRuntime} from './display-animation-attachment.js';
import {createSourceAnimationArchiveHydrationRuntime} from './animation-archive-hydration.js';
import {createSourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import {createSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshBinding} from './actor-attribute-refresh.js';
import {createSourceActorAnimationSetupRuntime} from './actor-animation-setup.js';
import {createSourceAnimationArchiveBankRuntime} from './animation-archive-bank.js';
import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
import {createSourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime, type SourceJointPoseEffects} from './joint-animation-feedback.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createRomActor} from './actor.js';
import {updateReactionStream} from './stream-vm.js';
import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {AOBJ_LOOP, AOBJ_REQUEST, AOBJ_STOPPED, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[attached-setup-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try {run();} catch (e) {diagnostic = String(e);}
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic || 'success'}`);
}
const zeroEuler: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
  if (![rotation.x, rotation.y, rotation.z].every(v => Object.is(v, 0))) throw Error('fixture supports positive zero Euler only');
  output.x = 0; output.y = 0; output.z = 0; output.w = 1;
}};
function fixture(partNumber: 0 | 1 = 0, ownedAttachment = false, archiveSetup = false, modelDat?: Uint8Array, poseCapacity = 2) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const modelHydration = createSourceJObjModelHydrationRuntime(joints);
  const model = modelDat === undefined ? null : modelHydration.hydrateModelArchive(modelDat, 0);
  // Explicit actor joint-bank mapping to descriptor data+40, not traversal order.
  const joint = model ? model.joints.find(row => row.dataOffset === 0x40)!.joint : joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 7, rotation20: 8, rotation24: 9, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -10, translation3c: -20, translation40: -30},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const fobjs = createSourceFObjScalarCallbackRuntime(joint), loader = createSourceFObjDescriptorRuntime(fobjs);
  const tracks = [1, 2, 3, 5, 6, 7], data: symbol[] = []; let descriptor: symbol | null = null;
  for (let i = tracks.length - 1; i >= 0; i--) {
    const track = tracks[i]!, base = track <= 3 ? 0 : 10 * (track - 4);
    data[i] = fobjs.createData(Uint8Array.from(track <= 3 ? [1, 0, 4, 1, 0] : [2, base, 4, 2, base + 8]));
    descriptor = loader.createDescriptor({next00: descriptor, length04: 5, start08: 0, track0c: track,
      format0d: 0x80, format0e: 0x80, data10: data[i]!});
  }
  const receiverTracks: number[] = [];
  const aobjLoader = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs: loader, removal: fobjs});
  const aobjDescriptor = aobjLoader.createDescriptor({flags00: AOBJ_LOOP, end04: 3, fobj08: descriptor, joint0c: null});
  const lifecycle = createSourceAObjLifecycleRuntime({feedback, fobjs, descriptors: aobjLoader});
  const order = createSourceJObjTrackOrderRuntime({joints, feedback, fobjs: {
    getFObj(id, nodeId) {feedback.getAObj(id); return fobjs.getNode(nodeId);},
  }});
  const dobjs = createSourceDObjAnimationRuntime(), pobjs = createSourcePObjAnimationRuntime();
  const mobjs = createSourceMObjAnimationRuntime(), tobjs = createSourceTObjAnimationRuntime();
  const displayAttachment = createSourceDisplayAnimationAttachmentRuntime(dobjs);
  const displayRows = new Map<symbol, {owner: symbol; fobjs: ReturnType<typeof createSourceFObjScalarCallbackRuntime>}>();
  const displayVisits: symbol[] = [];
  const attachment = createSourceJObjAddAnimationRuntime({joints, lifecycle, order, displayAttachment});
  const animDescriptor = attachment.createDescriptor({aobj08: aobjDescriptor, robj0c: null, flags10: 1});
  let aobjId!: symbol;
  if (ownedAttachment && !archiveSetup) {
    // Real source-owned allocation, descriptor loading and JObj attachment.
    // Archive name/public-address lookup and actor setup inputs are still supplied.
    attachment.addAnimation(joint, animDescriptor);
    const attached = joints.getBinding(joint).aobj7c;
    if (attached === null) throw Error('source attachment unexpectedly returned null');
    aobjId = attached;
    const allocated = feedback.getAObj(aobjId);
    check(allocated.flags === (AOBJ_STOPPED | AOBJ_LOOP) && Object.is(allocated.frame, 0) &&
      Object.is(allocated.rewind, 0) && allocated.end === 3 && allocated.rate === 1 && allocated.joint18 === null &&
      (joints.getJoint(joint).flags14 & 8) !== 0,
    'source allocation initializes the actual clock before descriptor load and JObj flag attachment');
  } else if (!ownedAttachment) {
    // Retain the older explicit post-allocation fixture as independent coverage.
    aobjId = feedback.createAObj({flags: AOBJ_STOPPED, frame: 99, rewind: 5, end: 99, rate: 7, fobjs: null});
    const supplied = feedback.getAObj(aobjId);
    check(aobjLoader.continueAllocatedLoad(aobjId, aobjDescriptor) === aobjId &&
      supplied.flags === (AOBJ_STOPPED | AOBJ_LOOP) && Object.is(supplied.rewind, 0) && supplied.end === 3 &&
      supplied.frame === 99 && supplied.rate === 7, 'actual post-allocation descriptor stores retain supplied frame/rate and AObj identity');
    joints.getBinding(joint).aobj7c = aobjId;
  }
  let aobj!: ReturnType<typeof feedback.getAObj>;
  if (!archiveSetup) aobj = feedback.getAObj(aobjId);
  joints.getBinding(joint).classUpdate50 = fobjs.createCallback((owner, track, value) => {
    receiverTracks.push(track); joints.updateScalar(owner, track, value);
  });
  const interpretDisplay = (id: symbol | null, owner: symbol, callback: symbol | null): void => {
    displayVisits.push(owner);
    if (id === null) {interpretSourceAObj(null, callback, fobjs.effects, joints.endCallbacks.counts); return;}
    const row = displayRows.get(id);
    if (!row || row.owner !== owner) throw Error('unbound display interpreter');
    interpretSourceAObj(feedback.getAObj(id), callback, row.fobjs.effects, joints.endCallbacks.counts);
  };
  const animationEffects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      if (id === null) {interpretSourceAObj(null, callback, fobjs.effects, joints.endCallbacks.counts); return;}
      if ((!ownedAttachment && id !== aobjId) || owner !== joint) throw Error('unbound setup fixture animation');
      interpretSourceAObj(ownedAttachment ? feedback.getAObj(id) : aobj, callback, fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(id) {if (id !== null) throw Error('unsupported RObj animation');},
    animateDObjs(id) {dobjs.animateAll(id, {interpretAObj: interpretDisplay,
      animatePObjs(list) {pobjs.animateAll(list, {interpretAObj: interpretDisplay});},
      animateMObj(object) {mobjs.animate(object, {interpretAObj: interpretDisplay,
        animateTObjs(list) {tobjs.animateAll(list, {interpretAObj: interpretDisplay});},
      });},
    });},
  };
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, animationEffects, zeroEuler);
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 2, duration24: 99, segment2d: 9, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: Symbol('explicit part descriptor presence'), scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const poses = Array.from({length: 2}, () => Array.from({length: poseCapacity}, () => feedback.createPose(
    {translation: {x: -1, y: -2, z: -3}, quaternion: {x: 4, y: 5, z: 6, w: 7}})));
  const bank = mapping.createJointBank([null, joint]), map = mapping.createDescriptor([1]);
  const actor = mapping.createActor({descriptor4b0: map, jointCount1d90: 2, boundary1d91: partNumber === 0 ? 1 : 0,
    boundary1d92: 1, boundary1d93: 1, jointBank1db4: bank, jointBank1db8: null, timestep1dc8: 2}, {parts, poses});
  let requestCalls = 0, endCalls = 0;
  const requests = createSourceAnimationRequestRuntime({joints, dobjs, pobjs, mobjs, tobjs}, {
    requestAObj(id, frame) {
      if (!ownedAttachment && id !== null && id !== aobjId) throw Error('unbound setup fixture request');
      const display = id === null ? undefined : displayRows.get(id);
      requestSourceAObj(id === null ? null : display || ownedAttachment ? feedback.getAObj(id) : aobj,
        frame, display?.fobjs.effects ?? fobjs.effects); requestCalls++;
    },
  });
  const setup = createSourceAttachedJointSetupRuntime({joints, feedback, actors: mapping, requests,
    fobjs: {getFObj(id, nodeId) {if (!ownedAttachment && id !== aobjId) throw Error('wrong attached FObj owner'); feedback.getAObj(id); return fobjs.getNode(nodeId);}}}, animationEffects);
  const partId = parts[0]![partNumber]!, part = feedback.getPart(partId), pose = feedback.getPose(poses[0]![1]!);
  setup.bindPart(partId, {rewind26: -7, loop2c: 0});
  joints.endCallbacks.counts.running = 3; joints.endCallbacks.counts.stopped = 4;
  joints.endCallbacks.state.head28 = joints.endCallbacks.createNode({next00: null,
    callback04: joints.endCallbacks.createCallback(() => {endCalls++;})});
  const archives = createSourceArchivePublicRuntime();
  const archiveFront = createSourceArchiveJointSetupRuntime({archives, attachment, tail: setup, actors: mapping});
  // Explicit synthetic decoded object identities. Actual lookup still reads the
  // copied BE32 public table and compares NUL-terminated bytes from index zero.
  // Entry 1 shares entry 0's name but deliberately points to an empty animation.
  const archiveBytes = new Uint8Array(96), archiveView = new DataView(archiveBytes.buffer);
  archiveView.setUint32(8, 0); archiveView.setUint32(12, 0);
  archiveView.setUint32(16, 4); archiveView.setUint32(20, 0);
  archiveBytes.set([0x61, 0x6e, 0x69, 0x6d, 0], 32);
  const archiveBase = archives.createBytes(archiveBytes);
  const archive = archives.createArchive({publicCount0c: 2, data20: archives.cursorAt(archiveBase, 64),
    publicTable28: archives.cursorAt(archiveBase, 8), stringTable30: archives.cursorAt(archiveBase, 32)});
  const wrapper = archiveFront.createDescriptor({archive0c: archive});
  archiveFront.bindPart(partId, {descriptor04: wrapper});
  archiveFront.bindAddress(archiveBase, archives.cursorAt(archiveBase, 64), animDescriptor);
  const emptyAnimation = attachment.createDescriptor({aobj08: null, robj0c: null, flags10: 0});
  archiveFront.bindAddress(archiveBase, archives.cursorAt(archiveBase, 68), emptyAnimation);
  const poseTable = archiveFront.createPoseTable([
    {translation0c: -10, translation1c: -20, translation2c: -30},
    {translation0c: -100, translation1c: -200, translation2c: -300},
  ]);
  const runArchive = () => archiveFront.continueResolvedArchiveSetup(actor, partId, joint, 1, poseTable);
  if (archiveSetup) {
    check(ownedAttachment && joints.getBinding(joint).aobj7c === null,
      'archive setup starts without caller allocation or direct attachment store');
    runArchive();
    aobjId = joints.getBinding(joint).aobj7c!;
    aobj = feedback.getAObj(aobjId);
  }
  const nodes: symbol[] = []; let node = aobj.fobjs;
  while (node !== null) {nodes.push(node); node = fobjs.getNode(node).next00;}
  const run = archiveSetup ? runArchive : () => setup.continueAttachedSetupTail(actor, partId, joint);
  return {model, modelHydration, joints, feedback, mapping, setup, fobjs, actor, joint, aobj, aobjId, part, partId, pose, nodes,
    receiverTracks, run, requests, animationEffects, dobjs, pobjs, mobjs, tobjs, displayAttachment, displayRows, displayVisits, archives, archiveFront, archive, wrapper, archiveBase, poseTable, emptyAnimation, aobjLoader, aobjDescriptor, loader, descriptor, data, lifecycle, attachment, animDescriptor, get requestCalls() {return requestCalls;}, get endCalls() {return endCalls;}};
}
function dispatchFixture(partNumber: 0 | 1 = 0, ownedAttachment = false, archiveSetup = false, modelDat?: Uint8Array, poseCapacity = 2) {
  const x = fixture(partNumber, ownedAttachment, archiveSetup, modelDat, poseCapacity), dispatch = createSourceActorAnimationDispatchRuntime(x.mapping, x.feedback);
  // Presence-only source gates, not fabricated descriptor contents. Real
  // playback still comes from the explicitly attached owned fixture above.
  dispatch.bindActor(x.actor, {family1d88: Symbol('family descriptor presence'),
    shared1d8c: Symbol('shared descriptor presence'), marker578: 0, marker1db3: 0});
  dispatch.bindPart(x.partId, {elapsed08: 7, previous10: -1, previous14: -2, linked36: 0});
  return Object.assign(x, {dispatch, clocks: dispatch.getPartBinding(x.partId)});
}
function waitFixture(accumulator = 0, ownedAttachment = false, archiveSetup = false) {
  const x = dispatchFixture(1, ownedAttachment, archiveSetup), wait = createSourceStreamWaitTargetRuntime(x.mapping, x.feedback, x.dispatch);
  wait.bindActor(x.actor, Array.from({length: 4}, (_, i) =>
    ({target08: 77 + i, previous0c: -3, accumulator10: i === 1 ? accumulator : 100})));
  return Object.assign(x, {wait, stream: wait.getStreamPart(x.actor, 1)});
}
function controlFixture(flags01: number, wait14: number, gqr5 = 0x00070007) {
  const x = waitFixture(2), control = createSourceStreamWaitRuntime({mapping: x.mapping, feedback: x.feedback,
    dispatch: x.dispatch, targets: x.wait, gqr5});
  // Explicit startup-derived host numeric profile, not a live register capture.
  // Explicit owned current-record fields, not hydration of legacy frameClock,
  // streamPtr or an unimplemented command parser. Part0 remains non-null even
  // though only part1 is selected, matching the source's global null check.
  const command = control.createCommand({flags01});
  control.bindActor(x.actor, {activeMask579: 2, blockedMask1d9a: 0}, Array.from({length: 4}, () =>
    ({current00: command, wait14, finished1a: 0, event1e: 7})));
  return Object.assign(x, {control, command, waitControl: control.getPartBinding(x.actor, 1)});
}
/** Explicit byte-backed opcode0 fixture. Archive/bootstrap inputs remain supplied,
 * but wait values, flags and next-record identities come from actual copied bytes. */
function parsedControlFixture(bytes: Uint8Array, ownedAttachment = false, archiveSetup = false) {
  const x = waitFixture(2, ownedAttachment, archiveSetup), control = createSourceStreamWaitRuntime({mapping: x.mapping, feedback: x.feedback,
    dispatch: x.dispatch, targets: x.wait, gqr5: 0x00070007});
  const base = control.createStream(bytes);
  // Nonselected part0 retains a real byte cursor for 4cd24's global null check.
  // Only part1 has an attached animation and receives the parser/update calls.
  control.bindActor(x.actor, {activeMask579: 2, blockedMask1d9a: 0}, Array.from({length: 4}, () =>
    ({current00: base, next04: null, wait14: 99, finished1a: 1, event1e: 7})));
  return Object.assign(x, {control, base, waitControl: control.getPartBinding(x.actor, 1)});
}
/** Actual two-level signed-relative bank selection over supplied copied fixture bytes.
 * The descriptor/JObj attachment is still explicit, not a fabricated allocator. */
function startedControlFixture(commands: Uint8Array, ownedAttachment = false, archiveSetup = false) {
  const bytes = new Uint8Array(40 + commands.length);
  const view = new DataView(bytes.buffer);
  view.setInt16(12, 16); // family cursor8 + group2*2 -> group cursor24
  view.setInt16(26, 16); // group cursor24 + action1*2 -> command cursor40
  bytes.set(commands, 40);
  const x = parsedControlFixture(bytes, ownedAttachment, archiveSetup);
  x.control.bindStartActor(x.actor, {familyBank1d80: x.control.cursorAt(x.base, 8),
    sharedBank1d84: null, defaultSelector582: 2, marker709: 9});
  x.waitControl.group18 = 97; x.waitControl.action19 = 98; x.waitControl.status1d = 99;
  return Object.assign(x, {start: x.control.getStartActorBinding(x.actor),
    begin: (group = 0) => x.control.startStream(x.actor, 0x82, group, 1)});
}
/** Descriptor and metadata prerequisites are invoked explicitly, not disguised as
 * a completed 4871c/48648 ready setup. Their outputs are the actual records later
 * consumed by archive attachment, playback and scaling. */
function metadataControlFixture(scaleIndex = 255, flags = 1) {
  const x = startedControlFixture(Uint8Array.from([0, 1, 0, 0]), true, true);
  const descriptors = createSourceAnimationDescriptorBankRuntime();
  const bytes = new Uint8Array(128), view = new DataView(bytes.buffer);
  view.setInt16(12, 16); // actual family cursor8, default group2 -> group cursor24
  view.setInt16(26, 24); // action1 -> descriptor cursor48
  view.setInt16(14, 24); // changed default group3 -> group cursor32
  view.setInt16(34, 48); // action1 -> alternate descriptor cursor80
  for (const at of [48, 80]) {
    bytes[at] = at === 48 ? scaleIndex : 255;
    bytes[at + 12] = 0x81; bytes[at + 13] = 2; bytes[at + 14] = flags;
    bytes[at + 15] = 7; bytes[at + 16] = 5;
    bytes[at + 17] = 6; bytes[at + 18] = 7; bytes[at + 19] = 8;
  }
  const base = descriptors.createBytes(bytes), gates = x.dispatch.getActorBinding(x.actor);
  gates.family1d88 = descriptors.cursorAt(base, 8);
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors, actors: x.mapping,
    feedback: x.feedback, attached: x.setup});
  metadata.bindActor(x.actor, {byte1d74: 1, byte1d75: 2, byte1d76: 3, byte1d77: 4,
    byte1d94: 5, byte1d95: 6, byte1d98: 7, byte1d99: 8, byte1d9b: 9});
  metadata.bindPart(x.partId, {selector2a: 0, selector2b: 0, auxiliary37: 0});
  const apply = () => {
    const cursor = descriptors.resolveDescriptor(gates, x.start, 0, 1);
    metadata.applyMetadata(x.actor, x.partId, 1, cursor);
    return cursor;
  };
  return Object.assign(x, {descriptors, descriptorBase: base, metadata, apply});
}
/** Fully composed bounded mode0: owned descriptor banks, metadata, archive slots,
 * actor pose pool, actual replacement attachment, capture and stream controls.
 * Inputs remain explicit decoded synthetic data; no production bridge is enabled. */
function readyControlFixture(partNumber: 0 | 1 = 0, modelDat?: Uint8Array, poseCapacity = 2) {
  const x = dispatchFixture(partNumber, true, true, modelDat, poseCapacity), mask = 1 << partNumber;
  const initialAObj = x.joints.getBinding(x.joint).aobj7c;
  x.attachment.addAnimation(x.joint, x.emptyAnimation);
  check(x.joints.getBinding(x.joint).aobj7c === null, 'ready fixture starts with genuinely removed animation');
  const poses = x.archiveFront.createPoseTable(Array.from({length: 65}, (_, i) =>
    ({translation0c: i, translation1c: i + 1, translation2c: i + 2})));
  x.archiveFront.bindPosePool([poses]); x.archiveFront.bindActorPoseIndex(x.actor, 0);
  x.mapping.bindSetupRuntime(x.archiveFront);
  const targets = createSourceStreamWaitTargetRuntime(x.mapping, x.feedback, x.dispatch);
  targets.bindActor(x.actor, Array.from({length: 4}, () => ({target08: 77, previous0c: -3, accumulator10: 2})));
  const control = createSourceStreamWaitRuntime({mapping: x.mapping, feedback: x.feedback, dispatch: x.dispatch, targets, gqr5: 0x00070007});
  const commandBytes = new Uint8Array(56), commandView = new DataView(commandBytes.buffer);
  commandView.setInt16(12, 16); commandView.setInt16(26, 16);
  commandBytes.set([1, 0, 1, 0, 0, 0, 0, 2, 0, 8, 0, 2, 0, 1, 0, 0], 40);
  const commands = control.createStream(commandBytes);
  control.bindActor(x.actor, {activeMask579: mask, blockedMask1d9a: 0, marker71d: 9}, Array.from({length: 4}, () =>
    ({current00: commands, next04: null, wait14: 99, finished1a: 1, event1e: 7})));
  control.bindStartActor(x.actor, {familyBank1d80: control.cursorAt(commands, 8), sharedBank1d84: null, defaultSelector582: 2, marker709: 9});
  const descriptors = createSourceAnimationDescriptorBankRuntime(), bytes = new Uint8Array(96), view = new DataView(bytes.buffer);
  view.setInt16(12, 16); view.setInt16(26, 24);
  bytes[48] = 255;
  for (const at of [4, 12, 20, 28]) {bytes[48 + at] = 1; bytes[48 + at + 1] = 0; bytes[48 + at + 2] = 1;}
  bytes[57] = 10; bytes[58] = 11;
  const base = descriptors.createBytes(bytes), gates = x.dispatch.getActorBinding(x.actor);
  gates.family1d88 = descriptors.cursorAt(base, 8); gates.shared1d8c = descriptors.cursorAt(base, 8);
  const metadata = createSourceAnimationSetupMetadataRuntime({descriptors, actors: x.mapping, feedback: x.feedback, attached: x.setup});
  metadata.bindActor(x.actor, {byte1d74: 1, byte1d75: 2, byte1d76: 3, byte1d77: 4,
    byte1d94: 5, byte1d95: 6, byte1d98: 7, byte1d99: 8, byte1d9b: 9});
  metadata.bindPart(x.partId, {selector2a: 0, selector2b: 0, auxiliary37: 0});
  const archiveBanks = createSourceAnimationArchiveBankRuntime({mapping: x.mapping, metadata, archives: x.archiveFront});
  const absentArchive = x.archives.createArchive({...x.archives.getArchive(x.archive), publicCount0c: 0});
  const fallbackWrapper = x.archiveFront.createDescriptor({archive0c: absentArchive});
  const fallback = archiveBanks.createPointerTable([fallbackWrapper]), selected = archiveBanks.createPointerTable([x.wrapper]);
  const bank = archiveBanks.createPointerTable([fallback, selected]);
  const ready = createSourceActorAnimationSetupRuntime({mapping: x.mapping, feedback: x.feedback, dispatch: x.dispatch,
    descriptors, metadata, archiveBanks, starts: control});
  ready.bindActor(x.actor, {familyBank1d78: bank, sharedBank1d7c: null, movement6d8: -7});
  ready.bindPart(x.partId, {group28: 77, action29: 78, bank31: 1, status38: 9, field18: 10, field1c: 11, field20: 12});
  const readyHooks: {afterMode?: () => unknown} = {};
  const readyAdapter = {
    setupModeZero(...args: Parameters<typeof ready.setupModeZero>) {
      check(this === readyAdapter, 'ready dispatch retains actual adapter receiver');
      ready.setupModeZero(...args); return readyHooks.afterMode?.();
    },
    finishPartOneSetup(actor: symbol) {check(this === readyAdapter, 'part1 adapter receiver'); ready.finishPartOneSetup(actor);},
  };
  x.dispatch.bindSetupRuntime(readyAdapter);
  return Object.assign(x, {control, targets, metadata, archiveBanks, ready, readyAdapter, readyHooks, commands, bank, selected, fallbackWrapper,
    initialAObj, mask, stream: targets.getStreamPart(x.actor, partNumber), waitControl: control.getPartBinding(x.actor, partNumber),
    begin: () => control.startStream(x.actor, mask, 0, 1)});
}
/** Part1 completes through real 4d08c on shared RomActor state. World matrices
 * remain separate explicitly decoded inputs, never local-pose approximations. */
function movementControlFixture(modelDat?: Uint8Array, poseCapacity = 2) {
  const x = readyControlFixture(1, modelDat, poseCapacity), sourceActor = createRomActor();
  sourceActor.borgNumber = 0x0300; sourceActor.stepHeight = 99; sourceActor.modelScale = 2;
  sourceActor.pos.y = 2; sourceActor.yVel = 7; sourceActor.parts[1].frameClock = 123;
  const matrices = createSourceActorJointMatrixRuntime(x.feedback);
  const movement = createSourceActorMovementFollowupRuntime({mapping: x.mapping, waits: x.control, setup: x.ready, matrixOwner: matrices});
  movement.bindActor(x.actor, sourceActor, {byte661: 0, field66c: 4, field670: 1});
  x.ready.bindMovementRuntime(movement);
  return Object.assign(x, {matrices, movement, sourceActor});
}
/** Independent hand-authored bare HSD DAT: two public names alias one leaf
 * AnimJoint at data offset zero, six FObj records and unchanged packed bytes. */
function hydrationDatFixture() {
  const dataSize = 0xf0, relocations = [8, 0x28];
  for (let i = 0; i < 6; i++) {if (i < 5) relocations.push(0x30 + i * 0x14); relocations.push(0x40 + i * 0x14);}
  const relocationAt = 0x20 + dataSize, publicAt = relocationAt + relocations.length * 4, stringsAt = publicAt + 16;
  const bytes = new Uint8Array(stringsAt + 14), view = new DataView(bytes.buffer);
  view.setUint32(0, bytes.length); view.setUint32(4, dataSize); view.setUint32(8, relocations.length); view.setUint32(12, 2);
  const data = 0x20; view.setUint32(data + 8, 0x20); view.setUint32(data + 0x10, 1);
  view.setUint32(data + 0x20, AOBJ_LOOP); view.setFloat32(data + 0x24, 3); view.setUint32(data + 0x28, 0x30);
  const tracks = [1, 2, 3, 5, 6, 7];
  for (let i = 0; i < tracks.length; i++) {
    const at = data + 0x30 + i * 0x14, stream = 0xc0 + i * 8, track = tracks[i]!;
    if (i < tracks.length - 1) view.setUint32(at, 0x30 + (i + 1) * 0x14);
    view.setUint32(at + 4, 5); view.setFloat32(at + 8, 0); bytes[at + 12] = track;
    bytes[at + 13] = 0x80; bytes[at + 14] = 0x80; view.setUint32(at + 16, stream);
    const base = 1 + 10 * (track - 4);
    bytes.set(track <= 3 ? [1, 0, 4, 1, 0] : [2, base, 4, 2, base + 12], data + stream);
  }
  relocations.forEach((offset, i) => view.setUint32(relocationAt + i * 4, offset));
  view.setUint32(publicAt, 0); view.setUint32(publicAt + 4, 0);
  view.setUint32(publicAt + 8, 0); view.setUint32(publicAt + 12, 7);
  bytes.set([106, 111, 105, 110, 116, 48, 0, 106, 111, 105, 110, 116, 49, 0], stringsAt);
  return bytes;
}
function hydratedControlFixture(dat = hydrationDatFixture(), modelDat?: Uint8Array, poseCapacity = 2) {
  const x = movementControlFixture(modelDat, poseCapacity);
  const hydration = createSourceAnimationArchiveHydrationRuntime({archives: x.archives, fobjData: x.fobjs,
    fobjs: x.loader, aobjs: x.aobjLoader, joints: x.attachment, setup: x.archiveFront});
  const imported = hydration.hydrateAnimationArchive(dat, [0, 1]);
  x.archiveBanks.getPointerTable(x.selected)[0] = imported.setupDescriptor;
  return Object.assign(x, {dat, hydration, imported});
}
/** Bare model DAT, authored independently from the importer. A selected root
 * at80 has children00/40, first child has childc0. Root.next points to100,
 * whose unsupported bytes prove the source single-root load never visits it. */
function modelDatFixture() {
  const dataSize = 0x140, slots = [8, 12, 0x88, 0x8c];
  const relocAt = 0x20 + dataSize, publicAt = relocAt + slots.length * 4, stringsAt = publicAt + 8;
  const bytes = new Uint8Array(stringsAt + 6), view = new DataView(bytes.buffer);
  view.setUint32(0, bytes.length); view.setUint32(4, dataSize); view.setUint32(8, slots.length); view.setUint32(12, 1);
  const flags = [0x100000, 0x80000, 0, 0x40000];
  for (let index = 0; index < 4; index++) {
    const at = 0x20 + index * 0x40; view.setUint32(at + 4, flags[index]!);
    [7, 8, 9, 1, 1, 1, -10 - index, -20 - index, -30 - index].forEach((v, i) => view.setFloat32(at + 0x14 + i * 4, v));
  }
  view.setUint32(0x20 + 8, 0xc0); view.setUint32(0x20 + 12, 0x40);
  view.setUint32(0x20 + 0x88, 0); view.setUint32(0x20 + 0x8c, 0x100);
  view.setUint32(0x20 + 0x100, 0xffffffff); // Ignored unsupported sibling descriptor.
  slots.forEach((slot, i) => view.setUint32(relocAt + i * 4, slot));
  view.setUint32(publicAt, 0x80); bytes.set([109, 111, 100, 101, 108, 0], stringsAt);
  return bytes;
}
function modelHydratedControlFixture(modelDat = modelDatFixture(), animationDat = hydrationDatFixture(), poseCapacity = 2) {
  const x = hydratedControlFixture(animationDat, modelDat, poseCapacity);
  if (!x.model) throw Error('model fixture requires actual imported owners');
  return Object.assign(x, {modelDat, importedModel: x.model});
}
/** Explicit 46dd4 helper boundary: supplied resolved parent and actual bank0
 * captured pose. This is not the special joint1 caller, which also pre-rotates
 * its parent and substitutes +1d54 translation. No hierarchy/clock is invented. */
function matrixHydratedControlFixture() {
  const x = modelHydratedControlFixture(); x.begin(); // First actual bank0 capture; movement gate remains off.
  const poseId = x.mapping.getLayout(x.actor).poses[0]![1]!;
  const parent = x.matrices.createMatrix([2, 0, 0, 100, 0, 3, 0, 200, 0, 0, 4, 300]);
  const destination = x.matrices.createMatrix([9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9]);
  const correction = {x: 0, y: 0, z: 0}, scale = {x: 1, y: 2, z: 1};
  const rebuild = () => x.matrices.composeJoint(parent, destination, poseId, correction, scale);
  rebuild();
  x.movement.bindWorldMatrices(x.actor, [parent, destination]);
  x.movement.bindDescriptor(x.mapping.getActor(x.actor).descriptor4b0!,
    {joint0f: 1, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255});
  x.sourceActor.controlWord = 0x40;
  return Object.assign(x, {parent, destination, poseId, correction, scale, rebuild, matrix: x.matrices.getMatrix(destination)});
}
/** Actual first-pass 46698 caller with explicit actor topology and storage.
 * The imported JObj tree is deliberately different; it cannot select this graph.
 * Source setup still consumes retained matrices, never an automatic refresh. */
function worldMatrixHydratedControlFixture(correctionDescriptor = false, primaryChain = false) {
  const capacity = primaryChain ? 4 : 2;
  const x = modelHydratedControlFixture(modelDatFixture(), hydrationDatFixture(), capacity); x.begin();
  x.sourceActor.pos.x = 100; x.sourceActor.pos.y = 2; x.sourceActor.pos.z = 300;
  x.sourceActor.stepHeight = 9;
  const fresh = () => x.matrices.createMatrix(Array(12).fill(77));
  const matrices8d4 = Array.from({length: capacity}, fresh), copy114 = fresh(), copy1aa4 = fresh(), scratch = fresh();
  const world = createSourceActorWorldMatrixRuntime({mapping: x.mapping, feedback: x.feedback, matrices: x.matrices});
  world.bindActor(x.actor, x.sourceActor, {
    mode4a0: 0, mode4a1: 0, flags48a: 0, mask1d70: 2, roll74: 0, yawOffset6b8: 0,
    scale58: {x: 2, y: 3, z: 4}, offset1dbc: {x: 3, y: 4, z: 5},
    adjusted1d54: {x: -1, y: -2, z: -3}, preRotation1d64: {x: 0, y: 0, z: 0},
  }, {matrices8d4, copy114, copy1aa4, scratch, topology1994: primaryChain ? [[1, 255, 255, 0], [2, 255, 0, 1], [3, 255, 0, 2], [255, 255, 0, 3]] : [[1, 255, 255, 0], [255, 255, 0, 1]],
    corrections18d4: Array.from({length: capacity}, () => ({x: 0, y: 0, z: 0})),
    scales15d4: Array.from({length: capacity}, (_, i) => ({x: 1, y: !primaryChain && i === 1 ? 2 : 1, z: 1}))});
  const header = world.getActorBinding(x.actor), worldStorage = world.getStorage(x.actor);
  const rebuild = () => world.updateActor(x.actor); rebuild();
  x.movement.bindWorldMatrices(x.actor, matrices8d4);
  x.movement.bindDescriptor(x.mapping.getActor(x.actor).descriptor4b0!,
    {joint0f: 1, joint22: 255, joint2a: 255, joint32: 255, joint3a: 255,
      ...(correctionDescriptor ? {byte23: 2, byte24: 1, byte25: 3, byte26: 2, byte27: 1,
        byte2b: 4, byte2c: 5, byte2d: 6, byte2e: 2, byte2f: 1} : {})});
  x.sourceActor.controlWord = 0x40;
  return Object.assign(x, {world, header, worldStorage, rebuild, rootMatrix: x.matrices.getMatrix(matrices8d4[0]!),
    worldMatrix: x.matrices.getMatrix(matrices8d4[1]!), copiedRoot: x.matrices.getMatrix(copy114), liftedRoot: x.matrices.getMatrix(copy1aa4)});
}
/** Explicit normal465fc caller over the same DAT/animation/pose/movement owners.
 * The linked actor has genuine separate world storage but no normal controller,
 * metadata or movement binding. 47a2c copies matrices, not actor state. */
function normalMatrixHydratedControlFixture(terrainFactory?: (owner: ReturnType<typeof worldMatrixHydratedControlFixture>) => SourceActorTerrainQueryRuntime,
  correctionStorage?: SourceActorMatrixUpdateStorage, primaryChain = false) {
  const x = worldMatrixHydratedControlFixture(correctionStorage !== undefined, primaryChain);
  const capacity = primaryChain ? 4 : 2;
  const sourceActor = Object.assign(x.sourceActor, {flyer741: 0});
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => x.mapping.createPart(
    {frame0c: 0, duration24: 0, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const poses = Array.from({length: 2}, () => Array.from({length: capacity}, () => x.feedback.createPose(
    {translation: {x: -101, y: -102, z: -103}, quaternion: {x: 0, y: 0, z: 0, w: 1}})));
  // Target joint count and modes do not control the source-driven copy loop.
  const target = x.mapping.createActor({descriptor4b0: null, jointCount1d90: 0, boundary1d91: 0,
    boundary1d92: 0, boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 0}, {parts, poses});
  const targetActor = createRomActor(); targetActor.pos.y = -99; targetActor.stepHeight = -88;
  const fresh = () => x.matrices.createMatrix(Array(12).fill(-77));
  const matrices8d4 = Array.from({length: capacity}, fresh), copy114 = fresh(), copy1aa4 = fresh(), scratch = fresh();
  x.world.bindActor(target, targetActor, {
    mode4a0: 2, mode4a1: 0, flags48a: 0, mask1d70: 0, roll74: 0, yawOffset6b8: 0,
    scale58: {x: 1, y: 1, z: 1}, offset1dbc: {x: 0, y: 0, z: 0},
    adjusted1d54: {x: -5, y: -6, z: -7}, preRotation1d64: {x: 0, y: 0, z: 0},
  }, {matrices8d4, copy114, copy1aa4, scratch, topology1994: Array.from({length: capacity}, () => [255, 255, 0, 0]),
    corrections18d4: primaryChain ? Array.from({length: capacity}, () => ({x: 0, y: 0, z: 0})) : [{x: 0, y: 0, z: 0}, {y: 0, z: 0}],
    scales15d4: Array.from({length: capacity}, () => ({x: 1, y: 1, z: 1}))});
  const globals = {maskD2: 0};
  const normal = createSourceActorMatrixUpdateRuntime({world: x.world, movement: x.movement,
    metadata: x.metadata, mapping: x.mapping, globals, ...(terrainFactory === undefined ? {} : {terrain: terrainFactory(x)})});
  normal.bindActor(x.actor, {count1d96: 8, count1d97: 9, field1d60: 10, byte660: 0, link4a4: target}, correctionStorage);
  x.header.mode4a0 = 1;
  // Authentic table index1 selects damping; high nibble1 returns in47904.
  x.metadata.getActorBinding(x.actor).byte1d98 = 0x11;
  return Object.assign(x, {sourceActor, normal, globals, normalState: normal.getActorBinding(x.actor),
    target, targetActor, targetPose: x.feedback.getPose(poses[0]![1]!), targetHeader: x.world.getActorBinding(target),
    targetMatrices: matrices8d4.map(id => x.matrices.getMatrix(id)),
    targetCopies: [copy114, copy1aa4, scratch].map(id => x.matrices.getMatrix(id)),
    updateNormal: () => normal.updateActor(x.actor)});
}
/** Explicit 5685c boundary over the same actual source actor/world records.
 * Only the four previously absent history records are introduced. */
function historyHydratedControlFixture() {
  const x = normalMatrixHydratedControlFixture();
  Object.assign(x.sourceActor.savedGroundPos, {x: 10, y: 20, z: 30});
  Object.assign(x.sourceActor.targetCache5e8, {x: -1, y: -2, z: -3});
  Object.assign(x.sourceActor.aimOrigin518, {x: 501, y: 502, z: 503});
  const history = createSourceActorTransformHistoryRuntime({world: x.world});
  history.bindActor(x.actor, {
    rotation76: {x: 111, y: 222, z: 333}, preRotation1d6a: {x: 444, y: 555, z: 666},
    previousStepHeight6d4: -99, aimOrigin524: {x: -11, y: -12, z: -13},
  });
  return Object.assign(x, {history, historyState: history.getActorBinding(x.actor), snapshot: () => history.snapshotActor(x.actor)});
}
// Explicit independently enumerated source/destination addresses. In particular,
// 868/874/880 are the existing actual RomActor actionSpeedRows, not new sidecars.
const attributeRowSources = ['field850', 'field854', 'field858', 'field85c', 'field860', 'field864',
  0, 'field86c', 'field870', 1, 'field878', 'field87c', 2, 'field884', 'field888'] as const;
const attributeRowDestinations = ['field814', 'field818', 'field81c', 'field820', 'field824', 'field828',
  'field82c', 'field830', 'field834', 'field838', 'field83c', 'field840', 'field844', 'field848', 'field84c'] as const;
/** The real DAT/setup/world/history/movement composition, with only the missing
 * 55dcc inputs supplied explicitly. This does not hydrate a production actor. */
function attributeHydratedControlFixture(parameterShorts?: {field04: number; field08: number}) {
  const x = historyHydratedControlFixture();
  const sourceActor = Object.assign(x.sourceActor, {hoverOffset668: -668});
  sourceActor.maxHSpeed = -678; sourceActor.maxRise = -679; sourceActor.maxFall = -680;
  const descriptorIdentity = x.mapping.getActor(x.actor).descriptor4b0!;
  // A transparent observation adapter counts actual callee invocations, never
  // substitutes a successful result or owns copies of movement/actor records.
  let movementCalls = 0;
  const movementObserver = {
    getActualActor(id: symbol) {check(this === movementObserver, 'attribute actual-actor receiver'); return x.movement.getActualActor(id);},
    getActorBinding(id: symbol) {check(this === movementObserver, 'attribute movement-binding receiver'); return x.movement.getActorBinding(id);},
    updateActor(id: symbol) {
      check(this === movementObserver, 'attribute actual movement-call receiver');
      movementCalls++; x.movement.updateActor(id);
    },
  };
  const attributes = createSourceActorAttributeRefreshRuntime({world: x.world, mapping: x.mapping, movement: movementObserver});
  attributes.bindDescriptor(descriptorIdentity, {field44: 2, field48: 0.5, field4c: 3, field50: 5, field54: 4});
  const parameter4ac = attributes.createParameterDescriptor({field74: 11, field78: 12, field7c: 13, ...parameterShorts});
  const initial: Partial<SourceActorAttributeRefreshBinding> = {byte87: 9, field674: -674, field770: -770, parameter4ac};
  const expectedRows = Array.from({length: 15}, (_, i) => 101 + i);
  attributeRowSources.forEach((key, i) => {
    if (typeof key === 'number') sourceActor.actionSpeedRows[key] = expectedRows[i]!;
    else initial[key] = expectedRows[i]!;
    initial[attributeRowDestinations[i]!] = -1000 - i;
  });
  attributes.bindActor(x.actor, initial);
  return Object.assign(x, {sourceActor, attributes, descriptorIdentity, expectedRows,
    attributeState: attributes.getActorBinding(x.actor),
    scalarDescriptor: attributes.getDescriptorBinding(descriptorIdentity),
    parameter: attributes.getParameterDescriptor(parameter4ac),
    movementState: x.movement.getActorBinding(x.actor),
    movementDescriptor: x.movement.getDescriptorBinding(descriptorIdentity),
    movementCallCount: () => movementCalls, refreshAttributes: () => attributes.refreshActor(x.actor)});
}
type AttributeFixture = ReturnType<typeof attributeHydratedControlFixture>;
/** Snapshot actual records, including identity-valued fields and signed zeros.
 * Attribute refresh may only change its own outputs and actual stepHeight. */
function retainAttributeUnrelatedOwners(x: AttributeFixture): () => void {
  const aobj = x.joints.getBinding(x.joint).aobj7c!;
  const records: object[] = [x.header, x.header.scale58, x.header.offset1dbc, x.header.adjusted1d54,
    x.header.preRotation1d64, x.normalState, x.historyState, x.historyState.rotation76,
    x.historyState.preRotation1d6a, x.historyState.aimOrigin524, x.sourceActor.pos,
    x.sourceActor.savedGroundPos, x.sourceActor.targetCache5e8, x.sourceActor.aimOrigin518,
    x.sourceActor.actionSpeedRows, ...x.sourceActor.parts, x.targetActor, x.targetHeader,
    x.targetPose, x.targetPose.translation, x.targetPose.quaternion,
    x.clocks, x.part, x.stream, x.waitControl, x.control.getActorBinding(x.actor),
    x.ready.getActorBinding(x.actor), x.mapping.getActor(x.actor),
    x.joints.getBinding(x.joint), x.joints.getJoint(x.joint), x.feedback.getAObj(aobj),
    ...x.worldStorage.matrices8d4.map(id => x.matrices.getMatrix(id)),
    ...[x.worldStorage.copy114, x.worldStorage.copy1aa4, x.worldStorage.scratch].map(id => x.matrices.getMatrix(id)),
    ...x.targetMatrices, ...x.targetCopies];
  for (const bank of x.mapping.getLayout(x.actor).poses) for (const id of bank) {
    const pose = x.feedback.getPose(id); records.push(pose, pose.translation, pose.quaternion);
  }
  let node = x.feedback.getAObj(aobj).fobjs;
  while (node !== null) {const record = x.fobjs.getNode(node); records.push(record); node = record.next00;}
  const saved = records.map(record => ({record, keys: Reflect.ownKeys(record),
    values: Reflect.ownKeys(record).map(key => Reflect.get(record, key))}));
  const yVel = x.sourceActor.yVel, requests = x.requestCalls, ends = x.endCalls, callbacks = x.receiverTracks.length;
  return () => {
    check(saved.every(({record, keys, values}) => Reflect.ownKeys(record).length === keys.length &&
      keys.every((key, i) => Object.is(Reflect.get(record, key), values[i]))) &&
      x.sourceActor.yVel === yVel && x.requestCalls === requests && x.endCalls === ends && x.receiverTracks.length === callbacks,
      '55dcc retains actual matrices, linked owner, history, pose, AObj/FObj, wait and host clocks without hidden refresh');
  };
}
function checkAttributeStores(x: AttributeFixture, expectedProducts: readonly number[], message: string): void {
  const products = [x.sourceActor.hoverOffset668, x.movementState.field66c, x.movementState.field670,
    x.attributeState.field674, x.attributeState.field770];
  check(products.every((value, i) => Object.is(value, expectedProducts[i])) &&
    x.attributeState.byte87 === ((x.sourceActor.controlWord >>> 6) & 1) &&
    x.sourceActor.maxHSpeed === 11 && x.sourceActor.maxRise === 12 && x.sourceActor.maxFall === 13 &&
    attributeRowDestinations.every((key, i) => Object.is(x.attributeState[key], x.expectedRows[i])), message);
}
function runAttributeHydratedControlTests(): void {
  {
    const x = attributeHydratedControlFixture(); x.snapshot();
    check(x.world.getActualActor(x.actor) === x.sourceActor && x.movement.getActualActor(x.actor) === x.sourceActor,
      'attribute composition shares one actual RomActor across world and movement');
    let retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [6, 4, 1, 8, 10], 'all five descriptor products, three limits and fifteen copies reach actual owners');
    check(x.movementCallCount() === 1 && x.sourceActor.stepHeight === Math.fround(46.5 * Math.fround(0.7)),
      'attribute tail invokes actual4d08c exactly once on retained worldY95');

    x.sourceActor.modelScale = 3; x.scalarDescriptor.field44 = 32;
    retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [9, 96, 1.5, 12, 15], 'live model scale and descriptor recompute the same movement fields');
    check(x.sourceActor.stepHeight === Math.fround(45 * Math.fround(0.7)) && x.movementCallCount() === 2,
      'actual4d08c consumes refreshed half-height96 instead of fixture constant4');
    x.scalarDescriptor.field48 = 20; x.movementDescriptor.joint22 = 1;
    retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [9, 96, 60, 12, 15], 'refreshed clearance remains the actual movement owner');
    const lowHeight = Math.fround(33 * Math.fround(0.7));
    check(x.sourceActor.stepHeight === lowHeight && x.movementCallCount() === 3,
      'actual descriptor joint list consumes refreshed clearance60');

    const oldAObj = x.joints.getBinding(x.joint).aobj7c; x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix[7] === 95 && x.movementCallCount() === 3 &&
      x.historyState.previousStepHeight6d4 === 9, 'genuine wait advances pose only, not attributes, matrices or history');
    x.scalarDescriptor.field4c = 7; x.sourceActor.actionSpeedRows[0] = 206; x.expectedRows[6] = 206;
    x.sourceActor.actionSpeedRows[1] = 209; x.expectedRows[9] = 209;
    x.sourceActor.actionSpeedRows[2] = 212; x.expectedRows[12] = 212;
    retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [21, 96, 60, 12, 15], 'all three live existing actionSpeedRows remain the row source owners');
    check(x.sourceActor.stepHeight === lowHeight && x.movementCallCount() === 4,
      'explicit attributes after genuine wait still consume retained world output, not changed local pose');
    x.begin();
    check(x.joints.getBinding(x.joint).aobj7c !== oldAObj && x.pose.translation.y === 27 &&
      x.sourceActor.stepHeight === lowHeight && x.worldMatrix[7] === 95 && x.movementCallCount() === 4 &&
      x.historyState.previousStepHeight6d4 === 9, 'genuine replacement setup executes its own movement without inventing an attribute call');
    x.control.update(x.actor, 2); x.sourceActor.pos.y = 6; x.metadata.getActorBinding(x.actor).byte1d98 = 0x11;
    x.updateNormal();
    check(x.worldMatrix[7] === 117 && x.targetMatrices[1]![7] === 117 && x.movementCallCount() === 4 &&
      x.historyState.previousStepHeight6d4 === 9, 'only the explicit normal465fc call refreshes retained matrices and linked receiver');
    retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    check(x.sourceActor.stepHeight === Math.fround(51 * Math.fround(0.7)) && x.movementCallCount() === 5,
      'next explicit attribute call consumes newly retained worldY117 through real movement');
    x.snapshot();
    check(x.historyState.previousStepHeight6d4 === x.sourceActor.stepHeight && x.sourceActor.savedGroundPos.y === 6 &&
      x.worldMatrix[7] === 117, 'only an explicit next history call snapshots refreshed movement output');
  }
  {
    const x = attributeHydratedControlFixture(), alternative = x.mapping.createDescriptor([1]);
    x.attributes.bindDescriptor(alternative, {field44: 5, field48: 2, field4c: 7, field50: 11, field54: 9});
    x.movement.bindDescriptor(alternative, {joint0f: 1, joint22: 0, joint2a: 255, joint32: 255, joint3a: 255});
    x.mapping.getActor(x.actor).descriptor4b0 = alternative;
    const retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [14, 10, 4, 18, 22], 'live selected4b0 identity selects all actual descriptor scalars');
    check(x.sourceActor.stepHeight === 0 && x.movementCallCount() === 1,
      'the same selected descriptor supplies actual movement bytes, including changed joint0 worldY2');
  }
  for (const gate of ['family', 'byte661', 'control', 'marker-positive', 'marker-negative', 'normal'] as const) {
    const x = attributeHydratedControlFixture();
    if (gate === 'family') x.sourceActor.borgNumber = 0x0501;
    if (gate === 'byte661') x.movementState.byte661 = 7;
    if (gate === 'control') x.sourceActor.controlWord = 0x80;
    if (gate === 'marker-positive') x.control.getActorBinding(x.actor).marker71d = 2;
    if (gate === 'marker-negative') x.control.getActorBinding(x.actor).marker71d = 255;
    if (gate !== 'normal') {x.sourceActor.pos.y = NaN; x.worldMatrix[7] = NaN; x.movementDescriptor.joint0f = NaN;}
    const retained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); retained();
    checkAttributeStores(x, [6, 4, 1, 8, 10], `all55dcc stores precede actual movement gate ${gate}`);
    const expected = gate === 'normal' ? Math.fround(46.5 * Math.fround(0.7)) :
      gate === 'marker-positive' ? 10 : gate === 'marker-negative' ? -20 : 0;
    check(x.sourceActor.stepHeight === expected && x.movementCallCount() === 1,
      `actual movement gate ${gate} observes its own source bounds and skips unread invalid matrix inputs`);
  }
  for (let failed = 0; failed < 5; failed++) for (const fault of ['source', 'destination'] as const) {
    const x = attributeHydratedControlFixture(); x.movementState.field66c = -66; x.movementState.field670 = -67;
    const sources = ['field4c', 'field44', 'field48', 'field54', 'field50'] as const;
    const destinations: readonly [object, string][] = [[x.sourceActor, 'hoverOffset668'], [x.movementState, 'field66c'],
      [x.movementState, 'field670'], [x.attributeState, 'field674'], [x.attributeState, 'field770']];
    const before = [-668, -66, -67, -674, -770], after = [6, 4, 1, 8, 10];
    if (fault === 'source') x.scalarDescriptor[sources[failed]!] = NaN;
    else Object.defineProperty(destinations[failed]![0], destinations[failed]![1], {writable: false});
    const retained = retainAttributeUnrelatedOwners(x);
    rejects(x.refreshAttributes, fault === 'source' ? 'finite exact' : 'non-writable'); retained();
    check(x.attributeState.byte87 === 1 && destinations.every(([record, key], i) => Reflect.get(record, key) === (i < failed ? after[i] : before[i])) &&
      x.sourceActor.maxHSpeed === -678 && x.sourceActor.maxRise === -679 && x.sourceActor.maxFall === -680 &&
      attributeRowDestinations.every((key, i) => x.attributeState[key] === -1000 - i) &&
      x.sourceActor.stepHeight === 9 && x.movementCallCount() === 0,
      `product${failed} ${fault} refusal retains byte87 and ordered actual destination prefix before limits, rows or callee`);
  }
  for (let failed = 0; failed < 15; failed++) for (const fault of ['source', 'destination'] as const) {
    const x = attributeHydratedControlFixture(), source = attributeRowSources[failed]!, destination = attributeRowDestinations[failed]!;
    if (fault === 'source') {
      if (typeof source === 'number') x.sourceActor.actionSpeedRows[source] = NaN;
      else x.attributeState[source] = NaN;
    } else Object.defineProperty(x.attributeState, destination, {writable: false});
    const retained = retainAttributeUnrelatedOwners(x);
    rejects(x.refreshAttributes, fault === 'source' ? 'finite exact' : 'non-writable'); retained();
    check(attributeRowDestinations.every((key, i) => x.attributeState[key] === (i < failed ? x.expectedRows[i] : -1000 - i)) &&
      x.sourceActor.hoverOffset668 === 6 && x.movementState.field66c === 4 && x.movementState.field670 === 1 &&
      x.attributeState.byte87 === 1 && x.attributeState.field674 === 8 && x.attributeState.field770 === 10 &&
      x.sourceActor.maxHSpeed === 11 && x.sourceActor.maxRise === 12 && x.sourceActor.maxFall === 13 &&
      x.sourceActor.stepHeight === 9 && x.movementCallCount() === 0,
      `row${failed} ${fault} refusal retains every earlier sequential copy, complete scalar prefix and no callee`);
  }
  {
    const x = attributeHydratedControlFixture(); x.parameter.field7c = NaN;
    const retained = retainAttributeUnrelatedOwners(x); rejects(x.refreshAttributes, 'finite exact'); retained();
    check(x.sourceActor.hoverOffset668 === 6 && x.movementState.field66c === 4 && x.movementState.field670 === 1 &&
      x.attributeState.field674 === 8 && x.attributeState.field770 === 10 && x.sourceActor.maxHSpeed === 11 &&
      x.sourceActor.maxRise === 12 && x.sourceActor.maxFall === -680 &&
      attributeRowDestinations.every((key, i) => x.attributeState[key] === -1000 - i) && x.movementCallCount() === 0,
      'late actual4ac limit refusal retains products and earlier limits before any row or movement effect');
  }
  for (const fault of ['root-index', 'movement-factor', 'height-destination'] as const) {
    const x = attributeHydratedControlFixture();
    if (fault === 'root-index') x.movementDescriptor.joint0f = 254;
    if (fault === 'movement-factor') x.ready.getActorBinding(x.actor).movement6d8 = NaN;
    if (fault === 'height-destination') Object.defineProperty(x.sourceActor, 'stepHeight', {writable: false});
    const retained = retainAttributeUnrelatedOwners(x);
    rejects(x.refreshAttributes, fault === 'root-index' ? 'negative world-matrix' : fault === 'movement-factor' ? 'finite exact' : 'non-writable');
    retained(); checkAttributeStores(x, [6, 4, 1, 8, 10], `actual4d08c ${fault} refusal retains every55dcc store`);
    check(x.movementCallCount() === 1 && x.sourceActor.stepHeight === (fault === 'root-index' ? 93 : fault === 'movement-factor' ? 46.5 : 9),
      `actual4d08c ${fault} refusal also retains its own completed height prefix`);
  }
  console.log('[actor-attribute-composition] PASS: five55dcc products, three limits and fifteen sequential row copies on actual DAT/setup/world/movement owners; live scale/descriptor/actionSpeedRows, real4d08c gates and failure prefixes, genuine wait/replacement and explicit normal/history cadence; explicit synthetic inputs only, no production activation or full lifecycle claim');
}
/** Explicit 55dcc -> 5568c prefix on the existing source graph. The borrowed
 * host-field record and three distinct WeaponCells are supplied synthetic
 * owners, not copied status snapshots or a claim of production Borg hydration. */
function statusHydratedControlFixture() {
  const x = attributeHydratedControlFixture({field04: 20, field08: 4});
  const sourceActor = Object.assign(x.sourceActor, {slopeMode698: 0.5});
  sourceActor.stateTimer = 1.5; sourceActor.housekeeping73f = 7; sourceActor.aimRateScale = 0.5;
  sourceActor.dt = 13; sourceActor.contactFlags = 0x3f; sourceActor.fbState = 1;
  x.header.yawOffset6b8 = 2;
  const sourceClock = x.mapping.getActor(x.actor), start = x.control.getStartActorBinding(x.actor);
  check(sourceClock.timestep1dc8 === 2 && start.marker709 === 0, 'real source start supplies its cleared marker and existing timestep');
  start.marker709 = 0x15;
  const cells: [WeaponCell, WeaponCell, WeaponCell] = [
    {cur: 1, max: 5, refillType: 0, refillParam: 11, timer: 0.25},
    {cur: 2, max: 7, refillType: 0, refillParam: 13, timer: 0.5},
    {cur: 3, max: 9, refillType: 0, refillParam: 17, timer: 1},
  ];
  const host: Pick<BorgRuntime, 'hp' | 'hitDrainFrames' | 'balanceGauge' | 'balanceGaugeMax' | 'downGauge' |
    'downGaugeBase' | 'balanceRefillDelay' | 'downResetDelay' | 'comboWindow' | 'comboAccum' | 'comboRank' |
    'invincTimer' | 'sourceAmmoRefillPauseMask' | 'sourceAmmoRefillRate' | 'weaponCells' | 'ammo' | 'statusTimer'> = {
    hp: 87, hitDrainFrames: 0, balanceGauge: 3, balanceGaugeMax: 40, downGauge: 7, downGaugeBase: 10,
    balanceRefillDelay: 0.25, downResetDelay: 5, comboWindow: 0.5, comboAccum: 9, comboRank: 3,
    invincTimer: 0.25, sourceAmmoRefillPauseMask: 0, sourceAmmoRefillRate: 99,
    // Browser X/HUD indexing is deliberately distinct: its entries1/2 alias
    // source cell2, while source cell1 remains separately supplied and owned.
    weaponCells: [cells[0], cells[2], cells[2]], ammo: 81, statusTimer: 71,
  };
  const ammoSlots: readonly [SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot] =
    [{cell: cells[0], mirror776: 11}, {cell: cells[1], mirror776: 12}, {cell: cells[2], mirror776: 13}];
  const statusSources = {world: x.world, mapping: x.mapping, movement: x.movement, attributes: x.attributes, streams: x.control};
  const status = createSourceActorStatusTimersRuntime(statusSources);
  const missing = {
    field690: 0.25, field69c: 2, field6a0: -2, field6a4: 1,
    byte6fc: 0, byte7de: 2, byte71c: 0, byte656: 2, byte593: 3, byte594: 4, byte596: 5,
    byte707: 0x3f, byte708: 0x3f, bytea8: 3, bytea9: 4, byteaa: 5, byteab: 6, byteac: 7, bytead: 8,
    short736: 4, short738: -9, short73a: 0, byte747: 7, short272: 9,
    field1dcc: 0.5, field7d8: 4, field8c8: 1, byte7d4: 1,
    childPointers440: Array<null>(8).fill(null),
    byte6fd: 1, byte702: 2, short282: 3, short284: 4, short6b6: 5,
  };
  status.bindActor(x.actor, host, missing, ammoSlots);
  return Object.assign(x, {sourceActor, sourceClock, start, host, cells, ammoSlots, status, statusSources, missing,
    statusState: status.getActorBinding(x.actor), updateStatus: () => status.updateActor(x.actor),
    refreshStatusPrefix: () => {x.refreshAttributes(); status.updateActor(x.actor);}});
}
function runStatusHydratedControlTests(): void {
  {
    const x = statusHydratedControlFixture(); x.snapshot(); x.refreshStatusPrefix();
    checkAttributeStores(x, [6, 4, 1, 8, 10], 'real55dcc completes before the actual bounded5568c call');
    check(x.movementCallCount() === 1 && x.sourceActor.stepHeight === Math.fround(46.5 * Math.fround(0.7)) &&
      x.world.getActualActor(x.actor) === x.sourceActor && x.movement.getActualActor(x.actor) === x.sourceActor,
      'status shares the actual actor after real attribute movement on retained worldY95');
    check(x.sourceActor.stateTimer === 0 && x.sourceActor.housekeeping73f === 0 && x.sourceActor.dt === 13 &&
      x.sourceClock.timestep1dc8 === 2 && x.sourceActor.controlWord === 0x40 && x.sourceActor.slopeMode698 === 0 &&
      x.statusState.field690 === 0 && x.statusState.field69c === 1.5 && x.statusState.field6a0 === -2 && x.statusState.field6a4 === 0.5,
      'actual694 uses mapping timestep2, five source timers use actual768, and negative timer remains unchanged');
    check(x.header.yawOffset6b8 === 1 && x.statusState.byte7de === 1 && x.statusState.byte656 === 1 &&
      x.statusState.byte593 === 2 && x.statusState.byte594 === 3 && x.statusState.byte596 === 4,
      'status decrements actual world6b8 and independent source byte counters');
    check([x.statusState.bytea8, x.statusState.bytea9, x.statusState.byteaa, x.statusState.byteab,
      x.statusState.byteac, x.statusState.bytead].join(',') === '1,3,1,5,1,7' &&
      x.start.marker709 === 0x15 && x.sourceActor.contactFlags === 0x3f,
      'six counters read true stream marker709 rather than the deliberately different legacy contactFlags');
    check(x.host.balanceRefillDelay === 0 && x.host.balanceGauge === 40 && x.host.downResetDelay === 4.5 &&
      x.host.downGauge === 7 && x.host.comboWindow === 0 && x.host.comboAccum === 0 && x.host.comboRank === 0 &&
      x.host.invincTimer === 0 && x.statusState.short272 === 0 && x.statusState.field7d8 === 3.5 &&
      x.host.hp === 87 && x.host.hitDrainFrames === 0 && x.statusState.field8c8 === 1.5,
      'actual borrowed host gauge/combo/invulnerability owners receive ordered source effects with genuine skipped callees');
    check(x.cells.map(cell => cell.cur).join(',') === '5,7,3' && x.cells.map(cell => cell.timer).join(',') === '0,0,0.5' &&
      x.ammoSlots.map(slot => slot.mirror776).join(',') === '5,7,13' && x.host.weaponCells![0] === x.cells[0] &&
      x.host.weaponCells![1] === x.cells[2] && x.host.weaponCells![2] === x.cells[2] &&
      x.host.sourceAmmoRefillRate === 99 && x.host.ammo === 81 && x.host.statusTimer === 71,
      'real6dcc0 visits three distinct source cells once; HUD aliases and legacy cached rate/duration are not source owners');
    check(x.statusState.short736 === 20 && x.statusState.short738 === 20 && x.statusState.byte747 === 0 &&
      x.attributes.getParameterDescriptor(x.attributeState.parameter4ac!) === x.parameter &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77 && x.pose.translation.y === 27 &&
      x.historyState.previousStepHeight6d4 === 9,
      'same actual4ac cap completes the tail without hidden matrix, linked-copy, pose or history work');

    const oldAObj = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.start.marker709 === 0 && x.joints.getBinding(x.joint).aobj7c !== oldAObj &&
      x.sourceActor.contactFlags === 0x3f && x.statusState.field8c8 === 1.5 && x.cells[2].timer === 0.5 &&
      x.movementCallCount() === 1 && x.worldMatrix[7] === 95 && x.historyState.previousStepHeight6d4 === 9,
      'genuine stream replacement clears the borrowed709 owner and invokes only its own actual movement');
    x.sourceActor.stateTimer = 3; x.sourceClock.timestep1dc8 = 0.25; x.updateStatus();
    check(x.sourceActor.stateTimer === 2.75 && x.header.yawOffset6b8 === 0 &&
      [x.statusState.bytea8, x.statusState.bytea9, x.statusState.byteaa, x.statusState.byteab,
        x.statusState.byteac, x.statusState.bytead].join(',') === '0,2,0,4,0,6' &&
      x.cells[2].cur === 9 && x.ammoSlots[2].mirror776 === 9 && x.cells[2].timer === 0 &&
      x.host.downResetDelay === 4 && x.statusState.field8c8 === 2 && x.movementCallCount() === 1,
      'next real status call observes live mappingdt and actual start reset, clears world yaw, and completes source cell2 once');
    x.sourceClock.timestep1dc8 = 2; x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77 &&
      x.statusState.field8c8 === 2 && x.sourceActor.stateTimer === 2.75 && x.movementCallCount() === 1,
      'real wait advances source pose without inventing another status, attribute or matrix call');
    x.sourceActor.pos.y = 6; x.metadata.getActorBinding(x.actor).byte1d98 = 0x11; x.updateNormal();
    check(x.worldMatrix[7] === 117 && x.targetMatrices[1]![7] === 117 && x.statusState.field8c8 === 2 &&
      x.historyState.previousStepHeight6d4 === 9 && x.movementCallCount() === 1,
      'only the later explicit465fc refresh consumes new pose/position and copies actual linked matrices');
    x.refreshAttributes();
    check(x.sourceActor.stepHeight === Math.fround(55.5 * Math.fround(0.7)) && x.movementCallCount() === 2 &&
      x.statusState.field8c8 === 2 && x.sourceActor.stateTimer === 2.75,
      'later real55dcc movement consumes worldY117 without implicitly ticking status');
    x.snapshot();
    check(x.historyState.previousStepHeight6d4 === x.sourceActor.stepHeight && x.sourceActor.savedGroundPos.y === 6,
      'only explicit history advances the previous-height owner after status and later matrix cadence');
  }
  for (const special of [false, true]) {
    const x = statusHydratedControlFixture(); x.sourceActor.controlWord = 0; x.statusState.byte7d4 = 0;
    x.refreshAttributes(); if (special) x.movementState.byte661 = 2;
    const replacement = x.attributes.createParameterDescriptor({field04: 12, field08: 7, field74: 11, field78: 12, field7c: 13});
    x.attributeState.parameter4ac = replacement; x.statusState.short736 = 10; x.updateStatus();
    check(x.statusState.short736 === 12 && x.statusState.byte747 === (special ? 7 : 0) && x.attributeState.byte87 === 0,
      `source ${special ? 'special661' : 'ordinary87'} regeneration reloads same4ac identity with signed cap and branch-specific747 store`);
    x.statusState.short736 = 32767; x.updateStatus();
    check(x.statusState.short736 === -32762, 'actual4ac increment stores low16 before signed cap comparison');
  }
  for (const call of ['f0104', '3d3e8', '3d444'] as const) {
    const x = statusHydratedControlFixture();
    if (call === 'f0104') {x.statusState.byte707 = 0; x.start.marker709 = 1;}
    else if (call === '3d3e8') x.host.downResetDelay = 0.25;
    else {x.host.downResetDelay = 0; x.statusState.field7d8 = 0.25;}
    rejects(x.refreshStatusPrefix, call);
    checkAttributeStores(x, [6, 4, 1, 8, 10], `unsupported${call} retains all prior actual55dcc effects`);
    check(x.sourceActor.stateTimer === 0 && x.sourceActor.housekeeping73f === 0 && x.header.yawOffset6b8 === 1 &&
      x.statusState.bytea8 === 1 && x.statusState.bytea9 === 3 && x.movementCallCount() === 1 &&
      x.sourceActor.stepHeight === Math.fround(46.5 * Math.fround(0.7)) && x.worldMatrix[7] === 95,
      `reached${call} refusal preserves early timers, world short, stream counters and real movement prefix`);
    check(x.host.balanceGauge === (call === 'f0104' ? 3 : 40) &&
      x.host.balanceRefillDelay === (call === 'f0104' ? 0.25 : 0) &&
      x.host.downResetDelay === (call === 'f0104' ? 5 : 0) &&
      x.statusState.field7d8 === (call === '3d444' ? 0 : 4) &&
      x.host.comboWindow === 0.5 && x.host.comboAccum === 9 && x.host.invincTimer === 0.25 &&
      x.cells.map(cell => cell.cur).join(',') === '1,2,3' && x.statusState.field8c8 === 1,
      `unsupported${call} stops at its exact call boundary, retaining reached expiry stores and leaving the later suffix untouched`);
  }
  {
    const x = statusHydratedControlFixture(); x.refreshAttributes(); x.attributeState.parameter4ac = null;
    rejects(x.updateStatus, '4ac');
    check(x.cells.map(cell => cell.cur).join(',') === '5,7,3' && x.ammoSlots.map(slot => slot.mirror776).join(',') === '5,7,13' &&
      x.cells[2].timer === 0.5 && x.host.balanceGauge === 40 && x.host.invincTimer === 0 &&
      x.statusState.short738 === -9 && x.statusState.short736 === 4 && x.statusState.byte747 === 7 &&
      x.statusState.field8c8 === 1 && x.movementCallCount() === 1,
      'late missing actual4ac retains real ammo/gauge/attribute/movement writes before any tail cap or accumulator store');
  }
  {
    const x = statusHydratedControlFixture(); Object.defineProperty(x.ammoSlots[1], 'mirror776', {writable: false});
    rejects(x.refreshStatusPrefix, 'non-writable');
    check(x.cells[0].cur === 5 && x.ammoSlots[0].mirror776 === 5 && x.cells[0].timer === 0 &&
      x.cells[1].cur === 7 && x.ammoSlots[1].mirror776 === 12 && x.cells[1].timer === 0 &&
      x.cells[2].cur === 3 && x.cells[2].timer === 1 && x.ammoSlots[2].mirror776 === 13 &&
      x.host.balanceGauge === 40 && x.statusState.short738 === -9 && x.statusState.field8c8 === 1,
      'readonly second ammo mirror retains slot0, slot1 debt/current and prior gauge stores but does not visit slot2 or tail');
  }
  {
    const x = statusHydratedControlFixture(), rejected = createSourceActorStatusTimersRuntime(x.statusSources);
    rejects(() => rejected.bindActor(x.actor, x.host, x.missing, [x.ammoSlots[0], x.ammoSlots[2],
      {cell: x.host.weaponCells![1]!, mirror776: 12}]), 'distinct');
    check(x.sourceActor.stateTimer === 1.5 && x.header.yawOffset6b8 === 2 && x.host.balanceGauge === 3 &&
      x.cells.map(cell => cell.timer).join(',') === '0.25,0.5,1' && x.movementCallCount() === 0,
      'binding rejects aliased browser X cells as independent source slots before any source effect');
  }
  {
    const x = statusHydratedControlFixture(); x.sourceActor.controlWord = 0x02000040; x.sourceActor.lockYaw = 0xf000;
    Object.defineProperty(x.statusState, 'short6b6', {writable: false});
    rejects(x.refreshStatusPrefix, '5c290');
    check(x.statusState.byte6fd === 0x26 && x.statusState.byte702 === 8 && x.statusState.short282 === -10240 &&
      x.statusState.short284 === 0x1000 && x.statusState.short6b6 === 5 &&
      x.cells.map(cell => cell.cur).join(',') === '5,7,3' && x.ammoSlots.map(slot => slot.mirror776).join(',') === '5,7,13' &&
      x.host.balanceGauge === 40 && x.host.invincTimer === 0 && x.statusState.short736 === 4 &&
      x.statusState.short738 === -9 && x.statusState.byte747 === 7 && x.statusState.field8c8 === 1 &&
      x.movementCallCount() === 1 && x.worldMatrix[7] === 95,
      'actual reaction call refuses after ammo and ordered reaction bytes/shorts, before restoration or final accumulator');
  }
  {
    const x = statusHydratedControlFixture(), legacy = Object.assign(x.sourceActor, {invulnTimer: 91});
    const rejected = createSourceActorStatusTimersRuntime(x.statusSources);
    rejects(() => rejected.bindActor(x.actor, x.host, x.missing, x.ammoSlots), 'source720 owner conflict');
    check(x.host.invincTimer === 0.25 && legacy.invulnTimer === 91 && x.host.balanceGauge === 3 &&
      x.sourceActor.stateTimer === 1.5 && x.cells[0].timer === 0.25,
      'binding refuses the pre-existing legacy720 rival instead of silently borrowing or creating another timer');
    rejects(x.refreshStatusPrefix, 'source720 owner conflict');
    check(x.sourceActor.stateTimer === 0 && x.host.balanceGauge === 40 && x.host.comboAccum === 0 &&
      x.host.invincTimer === 0.25 && legacy.invulnTimer === 91 && x.statusState.short272 === 9 &&
      x.cells[0].timer === 0.25 && x.statusState.field8c8 === 1 && x.movementCallCount() === 1,
      'a later legacy720 conflict retains completed source effects but refuses before either invulnerability owner is mutated');
  }
  console.log('[actor-status-composition] PASS: actual55dcc then bounded5568c/6dcc0 over shared actor/world/parameter/stream-clock owners, borrowed host gauges/invulnerability and three distinct source ammo cells with mirrors; active effects, genuine source-start reset, later wait/movement/matrix/history cadence and reached refusal prefixes; synthetic inputs only, no59068/full tick/spawn or production activation');
}
/** Extend the established synthetic DAT/setup/world/attribute/status graph.
 * The same borrowed host owns its paramTier; only absent gauge/scale fields are
 * added. Historical unbound-reset fixtures above deliberately remain unchanged. */
function gaugeScaleHydratedControlFixture() {
  const x = statusHydratedControlFixture();
  const host = Object.assign(x.host, {paramTier: {tier: 16, deltaAccum: 5, timerFrames: 8}});
  x.sourceActor.collisionScale = -19;
  const gauges = createSourceActorGaugeScaleRuntime({world: x.world, status: x.status});
  gauges.bindActor(x.actor, host, {short7d6: -40, short7dc: -7,
    targetScaleB8: 2.0625, byte7c9: 0, fieldC4: -23});
  x.status.bindGaugeResetSources(x.actor, gauges);
  return Object.assign(x, {host, gauges, gaugeState: gauges.getActorBinding(x.actor),
    tier: host.paramTier, scaleVector: x.header.scale58, updateScale: () => gauges.updateActor(x.actor)});
}
type GaugeScaleFixture = ReturnType<typeof gaugeScaleHydratedControlFixture>;
/** Observe all other existing owners around only5bab8. In particular neither
 * matrices, animation, attributes, status nor history is an implicit suffix. */
function retainGaugeScaleUnrelatedOwners(x: GaugeScaleFixture): () => void {
  const aobj = x.joints.getBinding(x.joint).aobj7c!;
  const rows: {record: object; omitted?: readonly string[]}[] = [
    {record: x.sourceActor, omitted: ['modelScale', 'collisionScale']},
    {record: x.host, omitted: ['downGauge']}, {record: x.tier, omitted: ['timerFrames']},
    {record: x.gaugeState, omitted: ['fieldC4']},
    ...[x.header, x.header.offset1dbc, x.header.adjusted1d54, x.header.preRotation1d64,
      x.normalState, x.historyState, x.historyState.rotation76, x.historyState.preRotation1d6a,
      x.historyState.aimOrigin524, x.sourceActor.pos, x.sourceActor.savedGroundPos,
      x.sourceActor.targetCache5e8, x.sourceActor.aimOrigin518, x.sourceActor.actionSpeedRows,
      ...x.sourceActor.parts, x.targetActor, x.targetHeader, x.targetHeader.scale58,
      x.targetPose, x.targetPose.translation, x.targetPose.quaternion, x.clocks, x.part,
      x.stream, x.waitControl, x.control.getActorBinding(x.actor), x.start, x.statusState,
      ...x.cells, ...x.ammoSlots, x.attributeState, x.parameter, x.scalarDescriptor,
      x.movementState, x.ready.getActorBinding(x.actor), x.sourceClock,
      x.joints.getBinding(x.joint), x.joints.getJoint(x.joint), x.feedback.getAObj(aobj),
      ...x.worldStorage.matrices8d4.map(id => x.matrices.getMatrix(id)),
      ...[x.worldStorage.copy114, x.worldStorage.copy1aa4, x.worldStorage.scratch].map(id => x.matrices.getMatrix(id)),
      ...x.targetMatrices, ...x.targetCopies].map(record => ({record})),
  ];
  for (const bank of x.mapping.getLayout(x.actor).poses) for (const id of bank) {
    const pose = x.feedback.getPose(id); rows.push(...[pose, pose.translation, pose.quaternion].map(record => ({record})));
  }
  let node = x.feedback.getAObj(aobj).fobjs;
  while (node !== null) {const record = x.fobjs.getNode(node); rows.push({record}); node = record.next00;}
  const saved = rows.map(({record, omitted = []}) => ({record, ownKeys: Reflect.ownKeys(record),
    keys: Reflect.ownKeys(record).filter(key => typeof key !== 'string' || !omitted.includes(key))}))
    .map(row => ({...row, values: row.keys.map(key => Reflect.get(row.record, key))}));
  const requests = x.requestCalls, ends = x.endCalls, callbacks = x.receiverTracks.length, movements = x.movementCallCount();
  return () => check(saved.every(({record, ownKeys, keys, values}) => Reflect.ownKeys(record).length === ownKeys.length &&
    keys.every((key, i) => Object.is(Reflect.get(record, key), values[i]))) &&
    x.requestCalls === requests && x.endCalls === ends && x.receiverTracks.length === callbacks && x.movementCallCount() === movements,
    '5bab8 retains all unrelated actual actor/status/attribute/animation/linked-matrix/history owners without a hidden caller');
}
function checkScaleStores(x: GaugeScaleFixture, scale: number, message: string): void {
  check(x.world.getActorBinding(x.actor).scale58 === x.scaleVector &&
    [x.sourceActor.modelScale, x.scaleVector.x, x.scaleVector.y, x.scaleVector.z,
      x.sourceActor.collisionScale, x.gaugeState.fieldC4].every(value => Object.is(value, scale)), message);
}
function runGaugeScaleHydratedControlTests(): void {
  {
    const x = gaugeScaleHydratedControlFixture(); x.host.downGaugeBase = 32;
    x.host.downResetDelay = 0.25; x.statusState.field7d8 = 0.25; x.snapshot();
    check(x.gauges.getActualActor(x.actor) === x.sourceActor && x.status.getActualActor(x.actor) === x.sourceActor &&
      x.gauges.getActualBorg(x.actor) === x.host && x.status.getActualBorg(x.actor) === x.host &&
      x.gauges.getStatusBinding(x.actor) === x.statusState && x.host.paramTier === x.tier,
      'gauge/scale binds the SAME actual actor, status, borrowed Borg and ActorParamTier identities');
    x.refreshStatusPrefix();
    checkAttributeStores(x, [6, 4, 1, 8, 10], 'actual55dcc stores precede both active source reset calls');
    check(x.host.downResetDelay === 0 && x.host.downGauge === 48 && x.statusState.field7d8 === 0 &&
      x.gaugeState.short7dc === -60 && x.host.comboWindow === 0 && x.host.invincTimer === 0 &&
      x.cells.map(cell => cell.cur).join(',') === '5,7,3' && x.statusState.field8c8 === 1.5 &&
      x.tier.timerFrames === 8 && x.sourceActor.modelScale === 2 && x.sourceActor.collisionScale === -19,
      'reached688 and7d8 expiry invoke real3d3e8/3d444, then continue genuine status/ammo suffix without implicitly calling5bab8');

    let retained = retainGaugeScaleUnrelatedOwners(x); x.updateScale(); retained();
    checkScaleStores(x, 2.049999952316284, 'nontrivial upward fadds writes actualB4, world58/5c/60, collisionC0 and missingC4');
    check(x.host.paramTier === x.tier && x.tier.timerFrames === 7 && x.tier.tier === 16 && x.tier.deltaAccum === 5 &&
      x.host.downGauge === 48 && x.gaugeState.short7dc === -60,
      'actual signed750 decrements in place; an intermediate scale does not invent a gauge-reset call');
    x.host.downGauge = 99;
    retained = retainGaugeScaleUnrelatedOwners(x); x.updateScale(); retained();
    checkScaleStores(x, 2.0625, 'overshoot clamps actualB4 to liveB8 before all five real scale copies');
    check(x.host.downGauge === 49 && x.gaugeState.short7dc === -60 && x.tier.timerFrames === 6 &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77 && x.pose.translation.y === 27 &&
      x.historyState.previousStepHeight6d4 === 9,
      'completion runs only real3d3e8 against newB4; matrices, secondary gauge, pose and history remain retained');

    // A deliberately larger live descriptor makes the scaled half-height the
    // winning real4d08c bound instead of its separate root-height clamp.
    x.scalarDescriptor.field44 = 64;
    let attributesRetained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); attributesRetained();
    checkAttributeStores(x, [6.1875, 132, 1.03125, 8.25, 10.3125], 'later actual55dcc observes changed modelScale through all five real products');
    check(x.sourceActor.stepHeight === Math.fround(27 * Math.fround(0.7)) && x.movementCallCount() === 2 &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77 && x.tier.timerFrames === 6,
      'later genuine4d08c consumes refreshed132 half-height on retained worldY95 without an extra scale or matrix call');
    x.updateStatus();
    check(x.header.yawOffset6b8 === 0 && x.statusState.field8c8 === 2 && x.tier.timerFrames === 6 &&
      x.host.downGauge === 49 && x.gaugeState.short7dc === -60 && x.worldMatrix[7] === 95,
      'an explicit second real status call clears its actual yaw countdown before the admitted zero-short world refresh');
    x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix[7] === 95 && x.tier.timerFrames === 6 &&
      x.statusState.field8c8 === 2 && x.movementCallCount() === 2,
      'real wait advances pose only; the scale helper is not an ordinary tick or a hidden wait suffix');
    x.sourceActor.pos.y = 6; x.updateNormal();
    check(x.rootMatrix[0] === 2.0625 && x.rootMatrix[5] === 2.0625 && x.rootMatrix[10] === 2.0625 &&
      x.worldMatrix[3] === 153.625 && x.worldMatrix[7] === 82.3125 && x.worldMatrix[11] === 399 &&
      x.worldMatrix[0] === 2.0625 && x.worldMatrix[5] === 4.125 && x.worldMatrix[10] === 2.0625 &&
      x.targetMatrices[1]!.every((value, i) => Object.is(value, x.worldMatrix[i])) &&
      x.targetActor.modelScale === 1 && x.targetHeader.scale58.x === 1 && x.tier.timerFrames === 6 &&
      x.historyState.previousStepHeight6d4 === 9 && x.statusState.field8c8 === 2,
      'only explicit465fc consumes actual world.scale58, refreshes matrices and copies linked matrices without copying linked actor scale or ticking status');
    attributesRetained = retainAttributeUnrelatedOwners(x); x.refreshAttributes(); attributesRetained();
    check(x.sourceActor.stepHeight === 7.21875 && x.movementCallCount() === 3 && x.tier.timerFrames === 6,
      'later actual55dcc/4d08c observes newly retained scaled worldY82.3125 and the same132 dimension');
    const oldAObj = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.joints.getBinding(x.joint).aobj7c !== oldAObj && x.pose.translation.y === 27 &&
      x.sourceActor.stepHeight === 7.21875 && x.worldMatrix[7] === 82.3125 && x.movementCallCount() === 3 &&
      x.tier.timerFrames === 6 && x.historyState.previousStepHeight6d4 === 9,
      'genuine replacement setup consumes retained scaled matrices and movement fields without repeating55dcc/5bab8');
    x.snapshot();
    check(x.historyState.previousStepHeight6d4 === 7.21875 && x.sourceActor.savedGroundPos.y === 6 &&
      x.worldMatrix[7] === 82.3125 && x.host.paramTier === x.tier,
      'only explicit history advances the actual previous-height owner after the scaled source composition');
  }
  {
    const x = gaugeScaleHydratedControlFixture(); x.host.downGaugeBase = 32; x.gaugeState.targetScaleB8 = 1.9375;
    let retained = retainGaugeScaleUnrelatedOwners(x); x.updateScale(); retained();
    checkScaleStores(x, 1.9500000476837158, 'downward interpolation executes the actual fsubs step');
    check(x.host.downGauge === 7 && x.tier.timerFrames === 7, 'intermediate downward scale retains the actual gauge');
    retained = retainGaugeScaleUnrelatedOwners(x); x.updateScale(); retained();
    checkScaleStores(x, 1.9375, 'downward completion clamps then copies into every actual scale destination');
    check(x.host.downGauge === 47 && x.gaugeState.short7dc === -7 && x.tier.timerFrames === 6,
      'downward completion resets actual downGauge with truncation, without resetting secondary7dc');
  }
  for (const gate of ['equal', 'byte7c9'] as const) {
    const x = gaugeScaleHydratedControlFixture();
    if (gate === 'equal') x.gaugeState.targetScaleB8 = 2;
    else x.gaugeState.byte7c9 = 1;
    const retained = retainGaugeScaleUnrelatedOwners(x); x.updateScale(); retained();
    check(x.tier.timerFrames === 7 && x.sourceActor.modelScale === 2 && x.scaleVector.x === 2 &&
      x.scaleVector.y === 3 && x.scaleVector.z === 4 && x.sourceActor.collisionScale === -19 &&
      x.gaugeState.fieldC4 === -23 && x.host.downGauge === 7,
      `actual ${gate} gate retains all scale destinations while the real earlier750 decrement still executes`);
  }
  {
    const x = gaugeScaleHydratedControlFixture(); x.tier.timerFrames = 1;
    const retained = retainGaugeScaleUnrelatedOwners(x); rejects(x.updateScale, '6817c'); retained();
    check(x.host.paramTier === x.tier && x.tier.timerFrames === 0 && x.tier.deltaAccum === 5 && x.tier.tier === 16 &&
      x.sourceActor.modelScale === 2 && x.scaleVector.x === 2 && x.scaleVector.y === 3 &&
      x.scaleVector.z === 4 && x.sourceActor.collisionScale === -19 && x.gaugeState.fieldC4 === -23 && x.host.downGauge === 7,
      'reached actual750 expiry retains decrement but refuses unresolved6817c global/table behavior before tier/delta clears or any scale step');
  }
  {
    const x = gaugeScaleHydratedControlFixture(); x.host.downGaugeBase = 32;
    x.host.downResetDelay = 0.25; x.statusState.field7d8 = 0.25; x.gaugeState.short7d6 = NaN;
    rejects(x.refreshStatusPrefix, 'short7d6');
    checkAttributeStores(x, [6, 4, 1, 8, 10], 'late actual secondary-reset refusal preserves every earlier55dcc store');
    check(x.host.downResetDelay === 0 && x.host.downGauge === 48 && x.statusState.field7d8 === 0 &&
      x.gaugeState.short7dc === -7 && x.host.comboWindow === 0.5 && x.host.invincTimer === 0.25 &&
      x.cells.map(cell => cell.cur).join(',') === '1,2,3' && x.statusState.field8c8 === 1 &&
      x.worldMatrix[7] === 95 && x.movementCallCount() === 1,
      'bound actual3d444 unsupported input preserves earlier real3d3e8 and both expiry stores while refusing the later status suffix');
  }
  for (const fault of ['world-y', 'collision', 'fieldC4'] as const) {
    const x = gaugeScaleHydratedControlFixture(); x.host.downGaugeBase = 32; x.gaugeState.targetScaleB8 = 2.03125;
    if (fault === 'world-y') Object.defineProperty(x.scaleVector, 'y', {writable: false});
    else if (fault === 'collision') delete x.sourceActor.collisionScale;
    else Object.defineProperty(x.gaugeState, 'fieldC4', {writable: false});
    const retained = retainGaugeScaleUnrelatedOwners(x); rejects(x.updateScale, fault === 'collision' ? 'collisionScale' : 'non-writable'); retained();
    check(x.tier.timerFrames === 7 && x.sourceActor.modelScale === 2.03125 && x.host.downGauge === 48 &&
      x.scaleVector.x === 2.03125 && x.scaleVector.y === (fault === 'world-y' ? 3 : 2.03125) &&
      x.scaleVector.z === (fault === 'world-y' ? 4 : 2.03125) &&
      x.sourceActor.collisionScale === (fault === 'collision' ? undefined : fault === 'fieldC4' ? 2.03125 : -19) &&
      x.gaugeState.fieldC4 === -23 && x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77,
      `${fault} refusal retains completed timer/interpolation/reset and each ordered actual scale store, without host collision fallback or implicit matrix work`);
  }
  console.log('[actor-gauge-scale-composition] PASS: actual688/7d8 reset callees and bounded5bab8 on the same DAT/setup/world/status/Borg/paramTier owners; both interpolation directions, completion reset, five actual scale copies, real later55dcc/movement and explicit matrix/linked/history cadence; missing6817c table/global and reached write failures preserve prefixes; synthetic inputs only, no59068/full tick/spawn or production activation');
}
/** Independent tiny unrelocated STIH source bytes. Source cell pointers and
 * record base are +8 relative; tolerant host cell interpretation is not used. */
function sourceTerrainDatFixture(floor: boolean, height = 0) {
  const recordOffset = 0x50, bytes = new Uint8Array(recordOffset + (floor ? 0x38 : 0));
  const view = new DataView(bytes.buffer);
  view.setUint32(0, 0x53544948); view.setUint32(4, bytes.length);
  view.setUint32(8, 500); view.setUint32(12, 500); view.setInt32(16, 2); view.setInt32(20, 2);
  view.setInt32(24, 0); view.setInt32(28, 0); view.setInt32(32, 0x20); view.setInt32(36, recordOffset - 8);
  let at = 0x38;
  for (let cell = 0; cell < 4; cell++) {
    view.setInt32(0x28 + cell * 4, at - 8);
    if (floor && cell === 0) {view.setInt32(at, 0); at += 4;}
    view.setInt32(at, -1); at += 4;
  }
  if (floor) {
    view.setUint32(recordOffset, 0xfedcba98); // Source query does not filter marker.
    const values = [0, height, 0, 0, height, 1000, 1000, height, 0, 0, 1, 0, 123];
    values.forEach((value, index) => view.setFloat32(recordOffset + 4 + index * 4, value));
  }
  return {bytes, grid: hitBin.parseStageHitGrid(bytes)};
}
function terrainHydratedControlFixture(floorHeight = 0, corrections = false, primaryChain = false) {
  const floor = sourceTerrainDatFixture(true, floorHeight), ceiling24 = sourceTerrainDatFixture(false), ceiling20 = sourceTerrainDatFixture(false);
  const terrain: SourceActorTerrainGlobals = {
    floor1c: sourceTerrainGrid.createSourceTerrainGrid(floor.bytes, floor.grid, 0x1c),
    ceiling24: sourceTerrainGrid.createSourceTerrainGrid(ceiling24.bytes, ceiling24.grid, 0x24),
    ceiling20: sourceTerrainGrid.createSourceTerrainGrid(ceiling20.bytes, ceiling20.grid, 0x20),
    upper34: 1000, lower68: -1000,
  };
  let history!: SourceActorTransformHistoryRuntime, query!: SourceActorTerrainQueryRuntime;
  const queryCalls: {point: Readonly<{x: number; y: number; z: number}>; clearance: number; height: number}[] = [];
  const queryHooks: {after?: (point: Readonly<{x: number; y: number; z: number}>, height: number) => void} = {};
  const normalCalls: {point: {x: number; y: number; z: number}; normal: {x: number; y: number; z: number}; result: 0 | 1; clearance: number}[] = [];
  const correctionStorage: SourceActorMatrixUpdateStorage | undefined = corrections ? {
    primary1a14: Array.from({length: 4}, () => ({x: -101, y: -102, z: -103, joint0c: 201, axis0d: 202, axis0e: 203, bend0f: 204})),
    secondary1a94: Array.from({length: 4}, () => ({joint00: 211, axis01: 212, axis02: 213, padding03: 214})),
  } : undefined;
  const x = normalMatrixHydratedControlFixture(owner => {
    history = createSourceActorTransformHistoryRuntime({world: owner.world});
    history.bindActor(owner.actor, {rotation76: {x: 0, y: 0, z: 0}, preRotation1d6a: {x: 0, y: 0, z: 0},
      previousStepHeight6d4: -99, aimOrigin524: {x: -1, y: -2, z: -3}});
    query = createSourceActorTerrainQueryRuntime({world: owner.world, history, terrain}); query.bindActor(owner.actor);
    return Object.freeze({bindActor: query.bindActor, queryNormal8003de80: query.queryNormal8003de80,
      query8003d6e4(id: symbol, point: Readonly<{x: number; y: number; z: number}>, clearance: number) {
        const height = query.query8003d6e4(id, point, clearance);
        queryCalls.push({point, clearance, height}); queryHooks.after?.(point, height); return height;
      },
    });
  }, correctionStorage, primaryChain);
  if (corrections) x.world.bindTerrainCorrectionSources(x.actor, {movement: x.movement, terrain: {
    queryNormal8003de80(id, point, clearance, normal) {
      const result = query.queryNormal8003de80(id, point, clearance, normal);
      normalCalls.push({point: {...point}, normal: {...normal}, result, clearance}); return result;
    },
  }});
  x.sourceActor.pos.y = 20; x.sourceActor.stepHeight = 9;
  x.header.scale58.y = 1; x.header.offset1dbc.y = -37;
  x.metadata.getActorBinding(x.actor).byte1d98 = 0x12; x.metadata.getActorBinding(x.actor).byte1d99 = 0;
  x.movement.getActorBinding(x.actor).field670 = 2;
  const descriptor = x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);
  descriptor.joint22 = 1; descriptor.joint2a = 255;
  history.snapshotActor(x.actor);
  return Object.assign(x, {terrain, floor, ceiling24, ceiling20, history, historyState: history.getActorBinding(x.actor),
    query, queryCalls, queryHooks, normalCalls, correctionInput: correctionStorage, descriptor, snapshot: () => history.snapshotActor(x.actor)});
}
/** A source-reachable minimum-reach primary chain. The first pass uses joint1's
 * adjusted translation8, while47368 later transforms its raw pose10. Real floor
 *10 plus clearance1 therefore creates target11 from queried distal10.5, yet the
 * primary vector is exactly+Y1. Metadata0x15 reaches the query and genuinely
 * suppresses secondary storage. This is not a claimed retail model fixture. */
function primaryTerrainHydratedControlFixture(bend = 3, floorHeight = 10) {
  const x = terrainHydratedControlFixture(floorHeight, true, true);
  Object.assign(x.sourceActor.pos, {x: 100, y: 0, z: 100}); x.sourceActor.stepHeight = 0;
  Object.assign(x.header.scale58, {x: 1, y: 1, z: 1});
  Object.assign(x.header.offset1dbc, {x: 0, y: -2, z: 0}); x.header.mask1d70 = 14;
  x.mapping.getActor(x.actor).jointCount1d90 = 4;
  const rawPoses = x.mapping.getLayout(x.actor).poses[0]!.map(id => x.feedback.getPose(id));
  for (let i = 0; i < rawPoses.length; i++) {
    Object.assign(rawPoses[i]!.translation, {x: 0, y: [0, 10, 2, 0.5][i]!, z: 0});
    Object.assign(rawPoses[i]!.quaternion, {x: 0, y: 0, z: 0, w: 1});
  }
  x.movement.getActorBinding(x.actor).field670 = 1;
  x.metadata.getActorBinding(x.actor).byte1d99 = 0x15;
  x.normalState.field1d60 = 0;
  Object.assign(x.descriptor, {joint22: 3, joint2a: 255, byte23: 2, byte24: 1, byte25: bend});
  x.snapshot();
  return Object.assign(x, {rawPoses,
    chainMatrices: x.worldStorage.matrices8d4.map(id => x.matrices.getMatrix(id))});
}
/** Equal unit bones make the same genuine floor query reach positive sine
 * refinement. First-pass positions are8/9/10; raw primary origin10 and floor10
 * plus clearance1 still produce the supported target displacement+Y1. */
function positivePrimaryTerrainHydratedControlFixture(bend = 3) {
  const x = primaryTerrainHydratedControlFixture(bend);
  x.rawPoses[2]!.translation.y = 1;
  x.rawPoses[3]!.translation.y = 1;
  x.snapshot();
  return x;
}
/** The existing source setup owns the same display graph used by request and
 * playback. PObj/MObj/DObj AObjs are preexisting stopped clocks; the first
 * material also has a real active packed texture stream and scalar receiver. */
function displayHydratedControlFixture() {
  const x = hydratedControlFixture();
  const texture = x.tobjs.createTexture({flags4c: 0, rotation18: 0, rotation1c: 0, rotation20: 0,
    scale28: 1, scale2c: 1, translation34: -1, translation38: -2},
  {next08: null, aobj64: null, classUpdate48: null});
  const p1 = x.pobjs.createPObj({next04: null, aobj18: null, classUpdate48: null});
  const p2 = x.pobjs.createPObj({next04: null, aobj18: null, classUpdate48: null});
  const m1 = x.mobjs.createMObj({tobj08: texture, aobj14: null, classUpdate4c: null});
  const m2 = x.mobjs.createMObj({tobj08: null, aobj14: null, classUpdate4c: null});
  const d2 = x.dobjs.createDObj({next04: null, mobj08: m2, pobj0c: p2, aobj10: null, classUpdate44: null});
  const d1 = x.dobjs.createDObj({next04: d2, mobj08: m1, pobj0c: p1, aobj10: null, classUpdate44: null});
  const owners = [d1, p1, m1, texture, d2, p2, m2];
  const oldAObjs = owners.map((owner, index) => {
    const fobjs = createSourceFObjScalarCallbackRuntime(owner);
    const id = x.feedback.createAObj({flags: AOBJ_STOPPED, frame: 10 + index, rewind: 0, end: 40, rate: 1, fobjs: null});
    x.displayRows.set(id, {owner, fobjs}); return id;
  });
  x.dobjs.getDObj(d1).aobj10 = oldAObjs[0]!; x.pobjs.getPObj(p1).aobj18 = oldAObjs[1]!;
  x.mobjs.getMObj(m1).aobj14 = oldAObjs[2]!; x.tobjs.getBinding(texture).aobj64 = oldAObjs[3]!;
  x.dobjs.getDObj(d2).aobj10 = oldAObjs[4]!; x.pobjs.getPObj(p2).aobj18 = oldAObjs[5]!;
  x.mobjs.getMObj(m2).aobj14 = oldAObjs[6]!;
  const textureAObj = x.feedback.getAObj(oldAObjs[3]!), textureFObjs = x.displayRows.get(oldAObjs[3]!)!.fobjs;
  const textureData = textureFObjs.createData(Uint8Array.from([2, 10, 4, 2, 18]));
  const textureLoader = createSourceFObjDescriptorRuntime(textureFObjs);
  const textureDescriptor = textureLoader.createDescriptor({next00: null, length04: 5, start08: 0,
    track0c: 2, format0d: 0x80, format0e: 0x80, data10: textureData});
  const textureNode = textureLoader.loadDescriptors(textureDescriptor)!; textureAObj.fobjs = textureNode;
  x.tobjs.getBinding(texture).classUpdate48 = textureFObjs.createCallback((owner, track, value) => x.tobjs.updateScalar(owner, track, value));
  requestSourceAObj(textureAObj, 1, textureFObjs.effects);
  x.joints.getBinding(x.joint).dobj18 = d1;
  const displayBindings = () => [x.dobjs.getDObj(d1).aobj10, x.pobjs.getPObj(p1).aobj18,
    x.mobjs.getMObj(m1).aobj14, x.tobjs.getBinding(texture).aobj64, x.dobjs.getDObj(d2).aobj10,
    x.pobjs.getPObj(p2).aobj18, x.mobjs.getMObj(m2).aobj14];
  return Object.assign(x, {d1, d2, p1, p2, m1, m2, texture, owners, oldAObjs, displayBindings,
    textureAObj, textureFObjs, textureNode});
}
export function runAttachedSetupAnimationSelfTest(): void {
  for (const bend of [1, 2, 3, 255, 254, 253]) {
    const x = positivePrimaryTerrainHydratedControlFixture(bend); x.updateNormal();
    const first = x.chainMatrices.map(matrix => matrix.slice()), endpoint = x.chainMatrices[3]!;
    check(endpoint[3] === 100 && endpoint[7] === (bend === 2 || bend === 254 ? 12 : 11) && endpoint[11] === 100,
      'genuine nonzero bending retains axis-specific source geometry, not an unconditional target snap');
    check(x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, x.targetMatrices[i]![j]))),
      'positive-sine current, adjacent and traversed distal matrices reach the linked clone');
    x.updateNormal();
    check(x.queryCalls.length === 2 && x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 &&
      x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, first[i]![j]))),
      'repeated positive-sine refresh remeasures the first pass rather than bending already-bent output');
  }
  {
    const x = positivePrimaryTerrainHydratedControlFixture();
    const reached: {x: number; y: number; z: number; height: number}[] = [];
    x.queryHooks.after = (point, height) => {reached.push({...point, height});};
    x.updateNormal();
    check(reached.length === 1 && reached[0]!.x === 100 && reached[0]!.y === 10 && reached[0]!.z === 100 && reached[0]!.height === 10,
      'unit-bone first pass supplies the real distal query point10, not the earlier folded point10.5');
    check(x.normalState.primary1a14![0]!.y === 11 && x.chainMatrices[1]![7] === 10 &&
      x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 && x.normalCalls.length === 0,
      'actual floor and clearance create unit primary displacement and suppress only the secondary entry');
    // Independent source-operation expectations, including the unequal rounded
    // off-diagonal entries after the second Concat. No runtime helper derives these.
    const expected = [
      [0x3efffffd, 0x3f5db3d5, 0, 0x42c80000, 0xbf5db3d5, 0x3efffffd, 0, 0x41200000, 0, 0, 0x3f7ffffe, 0x42c80000],
      [0x3efffffc, 0xbf5db3d5, 0, 0x42c9bb68, 0x3f5db3d6, 0x3efffffd, 0, 0x41280000, 0, 0, 0x3f7ffffe, 0x42c80000],
      [0x3efffffc, 0xbf5db3d5, 0, 0x42c80000, 0x3f5db3d6, 0x3efffffd, 0, 0x41300000, 0, 0, 0x3f7ffffe, 0x42c80000],
    ];
    const view = new DataView(new ArrayBuffer(4));
    check(expected.every((row, i) => row.every((bits, j) => {
      view.setFloat32(0, x.chainMatrices[i + 1]![j]!); return view.getUint32(0) === bits;
    })), 'positive primary source arithmetic reaches all36 expected base, middle and special-traversal distal words');
    const retained = x.chainMatrices.map(matrix => matrix.slice());
    x.control.update(x.actor, 2); x.begin();
    check(x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, retained[i]![j]))) && reached.length === 1,
      'actual wait and replacement setup retain bent matrices with no hidden refresh');
    check(x.sourceActor.stepHeight === 3.5, 'actual replacement movement consumes retained positive-bend baseY10');
  }
  {
    const x = positivePrimaryTerrainHydratedControlFixture(); x.descriptor.byte25 = 0;
    rejects(x.updateNormal, 'primary bend axis');
    check(x.chainMatrices[1]![0] === 1 - 2 ** -23 && x.chainMatrices[1]![7] === 10 &&
      x.chainMatrices[2]![7] === 9 && x.chainMatrices[3]![7] === 10 && x.targetMatrices[1]![7] === -77,
      'positive-sine invalid late bend preserves completed orientation but no final rotations, special continuation or clone copy');
  }
  {
    const x = positivePrimaryTerrainHydratedControlFixture(); x.rawPoses[3]!.translation.y = 0.5; x.snapshot();
    rejects(x.updateNormal, 'retained bone length');
    check(x.normalState.count1d96 === 1 && x.chainMatrices[1]![7] === 8 && x.chainMatrices[2]![7] === 9 &&
      x.chainMatrices[3]![7] === 9.5 && x.targetMatrices[1]![7] === -77,
      'unproved mixed unit/half-unit pair retains first pass and genuine query without inventing primary placement');
  }
  for (const bend of [1, 2, 3, 255, 254, 253]) {
    const x = primaryTerrainHydratedControlFixture(bend); x.updateNormal();
    const first = x.chainMatrices.map(matrix => matrix.slice());
    check(x.chainMatrices[3]![7] === (bend === 2 || bend === 254 ? 12.5 : 11.5),
      'source signed bend lookup selects actual X/Y/Z matrices without claiming every axis attains the target');
    x.updateNormal();
    check(x.queryCalls.length === 2 && x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 &&
      x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, first[i]![j]))),
      'repeated real primary refresh recreates entries and first-pass lengths without accumulating normalization error');
  }
  {
    const x = primaryTerrainHydratedControlFixture(); x.descriptor.byte25 = 0;
    rejects(x.updateNormal, 'primary bend axis');
    const q2 = 1 - 2 ** -23;
    check(x.normalState.count1d96 === 1 && x.chainMatrices[1]![7] === 10 && x.chainMatrices[1]![0] === q2 &&
      x.chainMatrices[2]![7] === 10 && x.chainMatrices[3]![7] === 10.5 && x.targetMatrices[1]![7] === -77,
      'late invalid bend retains reached primary translation and orientation but not either final Concat or linked copy');
  }
  {
    const x = primaryTerrainHydratedControlFixture(3, 11);
    rejects(x.updateNormal, 'only flat');
    check(x.normalState.primary1a14![0]!.y === 12 && x.chainMatrices[1]![7] === 10 && x.chainMatrices[1]![0] === 1 &&
      x.chainMatrices[2]![7] === 10 && x.targetMatrices[1]![7] === -77,
      'genuine changed floor target outside unit-displacement domain refuses after raw primary translation, with old basis and no clone copy');
  }
  {
    const x = primaryTerrainHydratedControlFixture();
    const reached: {x: number; y: number; z: number; height: number}[] = [];
    x.queryHooks.after = (point, height) => {reached.push({...point, height});};
    x.updateNormal();
    check(reached.length === 1 && reached[0]!.x === 100 && reached[0]!.y === 10.5 && reached[0]!.z === 100 && reached[0]!.height === 10,
      'real primary caller queries first-pass distal10.5 and returns actual floor10');
    const primary = x.normalState.primary1a14![0]!;
    check(primary.x === 100 && primary.y === 11 && primary.z === 100 && primary.joint0c === 3 &&
      primary.axis0d === 2 && primary.axis0e === 1 && primary.bend0f === 3,
      'real47164 stores reached target11 and original primary descriptor bytes');
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 && x.normalCalls.length === 0,
      'source0x15 metadata admits query and suppresses only the secondary record');
    const q2 = 1 - 2 ** -23, base = x.chainMatrices[1]!, middle = x.chainMatrices[2]!, end = x.chainMatrices[3]!;
    check(base[7] === 10 && base[0] === q2 && base[5] === q2 && base[10] === q2,
      'primary transforms raw pose10 instead of adjusted8 and executes actual rounded orientation');
    check(middle[7] === 12 && middle[0] === -q2 && middle[5] === -q2 && middle[10] === q2,
      'primary second Concat places and folds actual adjacent matrix with captured raw translation2');
    check(end[7] === 11.5 && end[0] === -q2 && end[5] === -q2 && end[10] === q2,
      'special traversal skips overwritten joint2 and rebuilds distal joint3 from its folded parent, not the unreachable target11');
    check(x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, x.targetMatrices[i]![j]))),
      'all actual primary-chain matrices reach the linked clone without a second owner');
    const retained = x.chainMatrices.map(matrix => matrix.slice());
    x.control.update(x.actor, 2); x.begin();
    check(x.chainMatrices.every((matrix, i) => matrix.every((value, j) => Object.is(value, retained[i]![j]))) && reached.length === 1,
      'real wait and replacement setup retain the primary matrices without hidden queries or refresh');
    check(x.sourceActor.stepHeight === 3.5, 'actual replacement movement consumes retained primary baseY10');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.queryHooks.after = () => {x.descriptor.joint22 = 255;};
    x.updateNormal();
    check(x.normalState.primary1a14![0]!.joint0c === 255 && x.normalState.secondary1a94![0]!.joint00 === 255 &&
      x.normalState.count1d96 === 1 && x.normalState.count1d97 === 1 && x.normalCalls.length === 0 && x.worldMatrix[7] === 18,
      'descriptor joint bytes reload and store raw255 bits; only later scans sign-extend them and take genuine unmatched traversal');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.queryHooks.after = () => {x.metadata.getActorBinding(x.actor).byte1d99 = 0x10;};
    x.updateNormal();
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 &&
      x.normalState.secondary1a94![0]!.joint00 === 211 && x.normalCalls.length === 0 && x.worldMatrix[7] === 18,
      'secondary mask reloads metadata after primary entry/count rather than using initial threshold bits');
  }
  {
    const x = terrainHydratedControlFixture(8, true); x.descriptor.joint2a = 1; x.descriptor.joint32 = 255;
    x.updateNormal();
    check(x.normalState.count1d96 === 2 && x.normalState.count1d97 === 2 &&
      x.normalState.secondary1a94![0]!.joint00 === 1 && x.normalState.secondary1a94![1]!.joint00 === 1 &&
      x.normalState.secondary1a94![2]!.joint00 === 211 && x.normalCalls.length === 1 && x.worldMatrix[7] === 47,
      'two real secondary stores advance their own cursor while corrected traversal still uses its first matching entry');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.descriptor.joint2a = 1; x.descriptor.joint32 = 255;
    x.metadata.getActorBinding(x.actor).byte1d99 = 0x10;
    x.updateNormal();
    check(x.queryCalls.length === 2 && x.normalState.count1d96 === 2 && x.normalState.count1d97 === 1 &&
      x.normalState.primary1a14![0]!.axis0d === 2 && x.normalState.primary1a14![1]!.axis0d === 4 &&
      x.normalState.primary1a14![1]!.axis0e === 5 && x.normalState.primary1a14![1]!.bend0f === 6 &&
      x.normalState.secondary1a94![0]!.axis01 === 2 && x.normalState.secondary1a94![1]!.joint00 === 211 &&
      x.normalCalls.length === 1 && x.targetMatrices[1]![7] === 47,
      'primary/secondary source cursors advance independently across two genuine contacts and per-iteration secondary mask bits');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.queryHooks.after = () => {x.normalState.count1d96 = 255; x.normalState.count1d97 = 255;};
    x.updateNormal();
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 &&
      x.normalState.primary1a14![0]!.joint0c === 1 && x.normalState.secondary1a94![0]!.joint00 === 1 &&
      x.normalCalls.length === 0 && x.worldMatrix[7] === 18,
      'source counters reload after completed entry stores and increment as bytes independently of local entry cursors');
  }
  for (const floorHeight of [8, 12]) {
    const x = terrainHydratedControlFixture(floorHeight, true);
    const primary = x.normalState.primary1a14![0]!, secondary = x.normalState.secondary1a94![0]!;
    Object.assign(x.correctionInput!.primary1a14![0]!, {x: 999});
    Object.assign(x.correctionInput!.secondary1a94![0]!, {padding03: 0});
    check(primary.x === -101 && secondary.padding03 === 214 && Object.isFrozen(x.normalState.primary1a14) &&
      Object.isFrozen(x.normalState.secondary1a94) && Object.getOwnPropertyDescriptor(x.normalState, 'primary1a14')!.writable === false,
      'actual correction slot owners copy explicit initial fields, retain stable row/array identity and do not borrow mutable initialization');
    x.updateNormal();
    const q2 = Math.fround(1 - 2 ** -23);
    const expected = [2 * q2, 0, 0, 134, 0, 2 * q2, 0, 47, 0, 0, 4 * q2, 448];
    check(x.queryCalls.length === 1 && x.queryCalls[0]!.height === floorHeight &&
      x.queryCalls[0]!.point.y === floorHeight + 2 && primary.x === 140 && primary.y === floorHeight + 2 && primary.z === 468 &&
      primary.joint0c === 1 && primary.axis0d === 2 && primary.axis0e === 1 && primary.bend0f === 3,
      'genuine equal/lower terrain result updates caller stackY and actual XYZ/descriptor primary entry in source order');
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 1 && secondary.joint00 === 1 &&
      secondary.axis01 === 2 && secondary.axis02 === 1 && secondary.padding03 === 214 &&
      x.normalState.primary1a14![1]!.x === -101 && x.normalState.secondary1a94![1]!.joint00 === 211,
      'source cursors/counts create both entries without touching secondary padding or later slots');
    check(x.normalCalls.length === 1 && x.normalCalls[0]!.point.x === 134 && x.normalCalls[0]!.point.y === 47 &&
      x.normalCalls[0]!.point.z === 448 && x.normalCalls[0]!.normal.y === 1 && x.normalCalls[0]!.clearance === 2 &&
      x.worldMatrix.every((v, i) => Object.is(v, expected[i])) && x.targetMatrices[1]!.every((v, i) => Object.is(v, expected[i])),
      'actual positive-list match executes raw-pose transform, real normal query, source estimate/refinement and restored scale before linked copy');
    check(x.normalState.field1d60 === 8 && x.header.adjusted1d54.y === -2 && x.worldMatrix[7] !== primary.y,
      'secondary correction aligns normal with raw pose, not primary height or the ordinary joint1 adjusted translation');
    const retained = [...x.worldMatrix]; x.control.update(x.actor, 2);
    check(x.worldMatrix.every((v, i) => Object.is(v, retained[i])) && x.normalCalls.length === 1,
      'actual source wait retains the correction output without another query/matrix pass');
    x.begin();
    check(x.sourceActor.stepHeight === Math.fround(13.5 * Math.fround(0.7)) && x.historyState.previousStepHeight6d4 === 9 &&
      x.worldMatrix.every((v, i) => Object.is(v, retained[i])) && x.targetMatrices[1]![7] === 47,
      'real replacement setup/movement consumes retained correction matrix without recomputing it or rewriting prior height');
    x.snapshot(); check(x.historyState.previousStepHeight6d4 === x.sourceActor.stepHeight,
      'next explicit lifecycle history captures the real correction-driven movement output');
  }
  {
    const x = terrainHydratedControlFixture(8, true); x.updateNormal();
    const first = [...x.worldMatrix]; x.updateNormal();
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 1 && x.normalCalls.length === 2 &&
      x.normalState.field1d60 === Math.fround(8 * Math.fround(0.8)) && x.worldMatrix.every((v, i) => Object.is(v, first[i])),
      'each explicit source refresh clears/reuses entry cursors and rebuilds before normalization, without accumulating estimate error or deduplicating calls');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.metadata.getActorBinding(x.actor).byte1d99 = 0x10; x.updateNormal();
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 && x.normalCalls.length === 0 &&
      x.worldMatrix[7] === 18 && x.normalState.secondary1a94![0]!.joint00 === 211,
      'source secondary mask skips only its stores/count; positive primary miss then uses genuine ordinary traversal');
  }
  {
    const x = terrainHydratedControlFixture(8, true), row = x.normalState.primary1a14![0]!;
    Object.defineProperty(row, 'axis0e', {writable: false}); rejects(x.updateNormal, 'non-writable field');
    check(row.x === 140 && row.y === 10 && row.z === 468 && row.joint0c === 1 && row.axis0d === 2 &&
      row.axis0e === 203 && row.bend0f === 204 && x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 &&
      x.normalState.field1d60 === 10 && x.worldMatrix[7] === 10 && x.targetMatrices[1]![7] === -77,
      'late primary byte-store refusal retains XYZ and earlier bytes, not cursor/count, damping or second pass/copy');
  }
  {
    const x = terrainHydratedControlFixture(8, true), row = x.normalState.secondary1a94![0]!;
    Object.defineProperty(row, 'axis02', {writable: false}); rejects(x.updateNormal, 'non-writable field');
    check(x.normalState.count1d96 === 1 && x.normalState.count1d97 === 0 && row.joint00 === 1 && row.axis01 === 2 &&
      row.axis02 === 213 && row.padding03 === 214 && x.normalState.field1d60 === 10 && x.normalCalls.length === 0,
      'late secondary byte-store refusal preserves completed primary/count and earlier secondary bytes without count increment or tail');
  }
  {
    const x = terrainHydratedControlFixture(8, true);
    x.queryHooks.after = () => {
      x.descriptor.byte23 = 255; x.descriptor.byte24 = 254; x.descriptor.byte25 = 253;
      x.movement.getActorBinding(x.actor).field670 = 5;
    };
    x.updateNormal();
    check(x.normalState.primary1a14![0]!.axis0d === 255 && x.normalState.primary1a14![0]!.axis0e === 254 &&
      x.normalState.primary1a14![0]!.bend0f === 253 && x.normalState.primary1a14![0]!.y === 10 &&
      x.normalCalls[0]!.clearance === 5 && x.worldMatrix[7] === 47,
      'descriptor bytes reload after genuine height query, caller uses saved clearance, and secondary normal call freshly reads movement clearance');
  }
  {
    const x = terrainHydratedControlFixture(8, true); x.queryHooks.after = () => {x.descriptor.joint22 = 3;};
    rejects(x.updateNormal, 'world matrix: addressing outside explicitly owned storage');
    check(x.normalState.primary1a14![0]!.joint0c === 3 && x.normalState.secondary1a94![0]!.joint00 === 3 &&
      x.normalState.count1d96 === 1 && x.normalState.count1d97 === 1 && x.normalState.field1d60 === 8 &&
      x.worldMatrix[7] === 10 && x.normalCalls.length === 0 && x.targetMatrices[1]![7] === -77,
      'fresh joint byte reaches primary but missing adjacent matrix owners refuse before placement, without secondary fallthrough or copying partial results');
  }
  {
    const x = terrainHydratedControlFixture(8, true); x.descriptor.byte26 = 3;
    rejects(x.updateNormal, 'positive terrain axes (2,1)');
    check(x.worldMatrix[3] === 134 && x.worldMatrix[7] === 47 && x.worldMatrix[11] === 448 &&
      x.worldMatrix[0] === 2 && x.worldMatrix[5] === 2 && x.normalCalls.length === 1 && x.targetMatrices[1]![7] === -77,
      'unsupported orientation axis preserves genuine translated matrix and normal-query prefix without fabricating orientation or linked copy');
  }
  {
    const x = terrainHydratedControlFixture(8, true); x.pose.translation.x = 4000; x.header.offset1dbc.x = -3950;
    x.updateNormal();
    check(x.queryCalls[0]!.point.x === 200 && x.normalCalls[0]!.point.x === 8100 && x.normalCalls[0]!.result === 0 &&
      x.normalCalls[0]!.normal.y === 1 && x.worldMatrix[3] === 8100 && x.targetMatrices[1]![3] === 8100,
      'real outside-bounds normal query writes its default and returns0;4784c ignores the status and completes authentic orientation/copy');
  }
  {
    const x = terrainHydratedControlFixture(); x.updateNormal();
    check(x.queryCalls.length === 1 && x.queryCalls[0]!.clearance === 2 && x.queryCalls[0]!.height === 0 &&
      x.queryCalls[0]!.point.x === 140 && x.queryCalls[0]!.point.y === 10 && x.queryCalls[0]!.point.z === 468,
      'actual selector2 reaches source query over strict STIH layers and real triangle vertices, without a marker filter or floor callback');
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 && x.normalState.field1d60 === 8 &&
      x.header.adjusted1d54.y === -2 && x.worldMatrix[7] === 18 && x.targetMatrices[1]![7] === 18 &&
      x.historyState.previousStepHeight6d4 === 9 && x.sourceActor.savedGroundPos.y === 20,
      'genuine no-correction terrain result completes damping, corrected matrix traversal and linked copy while retaining lifecycle history');
    const retained = [...x.worldMatrix], target = [...x.targetMatrices[1]!]; x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix.every((v, i) => Object.is(v, retained[i])) &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, target[i])) && x.queryCalls.length === 1,
      'source wait preserves terrain-refreshed matrices and does not add another query tick');
    x.begin();
    check(x.pose.translation.y === 27 && x.sourceActor.stepHeight === 0 && x.historyState.previousStepHeight6d4 === 9 &&
      x.worldMatrix[7] === 18 && x.targetMatrices[1]![7] === 18,
      'real replacement setup consumes retained terrain-adjusted world matrix and clamps current height without rewriting history');
    x.snapshot();
    check(x.historyState.previousStepHeight6d4 === 0 && x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'explicit next lifecycle snapshot captures actual movement output without a host clock or second matrix update');
  }
  {
    const x = terrainHydratedControlFixture();
    x.sourceActor.savedGroundPos.y = 40;
    x.updateNormal();
    check(x.queryCalls[0]!.clearance === 2 && x.queryCalls[0]!.height === 0 && x.queryCalls[0]!.point.y === 10 &&
      x.historyState.previousStepHeight6d4 === 9 && x.normalState.field1d60 === 8 && x.worldMatrix[7] === 18,
      'positive previous-top displacement adjusts only query-local clearance: caller keeps 2 rather than 22 and completes strict-GT continuation');
  }
  {
    const x = terrainHydratedControlFixture(8), retained = [...x.targetMatrices[1]!];
    rejects(x.updateNormal, 'correction entry path');
    check(x.queryCalls[0]!.height === 8 && x.queryCalls[0]!.point.y === 10 && x.worldMatrix[7] === 10 &&
      x.normalState.field1d60 === 10 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'genuine nonzero height 8 plus caller clearance 2 reaches equality and refuses before correction stores');
  }
  {
    const x = terrainHydratedControlFixture(2 ** -24); x.updateNormal();
    check(x.queryCalls[0]!.height === 2 ** -24 && x.normalState.field1d60 === 8 && x.worldMatrix[7] === 18,
      'caller separately rounds original clearance plus real nonzero terrain height before strict-GT continuation');
  }
  for (const y of [2, 1]) {
    const x = terrainHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    x.header.offset1dbc.y = y - 47;
    rejects(x.updateNormal, 'correction entry path');
    check(x.queryCalls.length === 1 && x.queryCalls[0]!.height === 0 && x.queryCalls[0]!.point.y === y &&
      x.worldMatrix[7] === y && x.normalState.field1d60 === 10 && x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 &&
      x.header.adjusted1d54.y === y - 20 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'equal/lower jointY reaches genuine query then refuses before stackY or persistent correction entries, retaining first pass and clear counts');
  }
  {
    const x = terrainHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    const nonempty = sourceTerrainDatFixture(true, 50);
    const layer = sourceTerrainGrid.createSourceTerrainGrid(nonempty.bytes, nonempty.grid, 0x24);
    Object.defineProperty(x.terrain, 'ceiling24', {value: layer});
    nonempty.grid.triangles[0]!.normal.y = NaN; // Unread body must not preempt refusal.
    rejects(x.updateNormal, 'nonempty ceiling');
    check(x.queryCalls.length === 0 && x.worldMatrix[7] === 10 && x.normalState.field1d60 === 10 &&
      x.normalState.count1d96 === 0 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'reached nonempty source ceiling refuses before triangle-body reads, preserving the caller first pass without a fake empty result');
  }
  {
    const x = terrainHydratedControlFixture();
    x.queryHooks.after = point => {Object.assign(point, {y: 2});};
    rejects(x.updateNormal, 'correction entry path');
    check(x.queryCalls[0]!.point.y === 2 && x.worldMatrix[7] === 10 && x.normalState.field1d60 === 10,
      'caller reloads local pointY after the actual query adapter rather than reusing the pre-call matrix value');
  }
  {
    const x = terrainHydratedControlFixture();
    x.queryHooks.after = () => {x.movement.getActorBinding(x.actor).field670 = 999;};
    x.updateNormal();
    check(x.queryCalls[0]!.clearance === 2 && x.normalState.field1d60 === 8 && x.worldMatrix[7] === 18,
      'caller post-query sum uses its source-saved clearance even if the shared current field changes');
  }

  {
    const x = historyHydratedControlFixture(), oldPose = {...x.pose.translation};
    const initialWorld = [...x.worldMatrix], initialTarget = [...x.targetMatrices[1]!];
    const oldAObj = x.joints.getBinding(x.joint).aobj7c;
    x.snapshot();
    check(x.sourceActor.targetCache5e8.x === 10 && x.sourceActor.targetCache5e8.y === 20 && x.sourceActor.targetCache5e8.z === 30 &&
      x.sourceActor.savedGroundPos.x === 100 && x.sourceActor.savedGroundPos.y === 2 && x.sourceActor.savedGroundPos.z === 300 &&
      x.historyState.previousStepHeight6d4 === 9 && x.historyState.aimOrigin524.y === -12,
      'actual source history shifts existing old/current actor positions and height, while null visibility target retains aim history');
    check(x.worldMatrix.every((v, i) => Object.is(v, initialWorld[i])) && x.targetMatrices[1]!.every((v, i) => Object.is(v, initialTarget[i])) &&
      x.pose.translation.y === oldPose.y && x.normalState.field1d60 === 10 && x.joints.getBinding(x.joint).aobj7c === oldAObj &&
      x.sourceActor.parts[1].frameClock === 123,
      'explicit snapshot does not tick animation, damping, matrices, linked receiver, attachment or host clock');
    Object.assign(x.sourceActor.pos, {x: 104, y: 6, z: 308});
    x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.sourceActor.savedGroundPos.y === 2 && x.historyState.previousStepHeight6d4 === 9 &&
      x.worldMatrix.every((v, i) => Object.is(v, initialWorld[i])),
      'real source wait changes pose while frame history and retained matrix output remain unchanged');
    x.begin();
    const nextHeight = Math.fround(44.5 * Math.fround(0.7));
    check(x.pose.translation.y === 27 && x.sourceActor.stepHeight === nextHeight && x.historyState.previousStepHeight6d4 === 9 &&
      x.sourceActor.savedGroundPos.y === 2 && x.joints.getBinding(x.joint).aobj7c !== oldAObj,
      'actual replacement setup movement changes current height from retained worldY95 without refreshing previous-height ownership');
    // Setup loaded its own metadata; select this explicit admitted synthetic
    // normal-handler input before the separate matrix call.
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x11;
    x.updateNormal();
    check(x.worldMatrix[7] === 99 && x.targetMatrices[1]![7] === 99 && x.historyState.previousStepHeight6d4 === 9,
      'real normal matrix refresh reads current position and setup height without implicitly advancing history');
    x.snapshot();
    check(x.sourceActor.targetCache5e8.x === 100 && x.sourceActor.targetCache5e8.y === 2 && x.sourceActor.targetCache5e8.z === 300 &&
      x.sourceActor.savedGroundPos.x === 104 && x.sourceActor.savedGroundPos.y === 6 && x.sourceActor.savedGroundPos.z === 308 &&
      x.historyState.previousStepHeight6d4 === nextHeight && x.worldMatrix[7] === 99 && x.targetMatrices[1]![7] === 99 &&
      x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'next explicit snapshot captures real movement output and current source position without a second matrix or gameplay clock');
  }
  {
    const x = historyHydratedControlFixture(); x.header.mode4a0 = 2;
    x.sourceActor.bodyPitch = 0xffff; x.sourceActor.heading = 0x8000; x.header.roll74 = -32768;
    Object.assign(x.header.preRotation1d64, {x: -1, y: 32767, z: -32768});
    x.sourceActor.visibilityTarget = {eligibility83: 1, visibilityMask5e6: NaN, controlWord: NaN};
    x.sourceActor.visibilityBit = NaN; x.globals.maskD2 = NaN;
    x.snapshot();
    check(x.historyState.rotation76.x === -1 && x.historyState.rotation76.y === -32768 && x.historyState.rotation76.z === -32768 &&
      x.historyState.preRotation1d6a.x === -1 && x.historyState.preRotation1d6a.y === 32767 && x.historyState.preRotation1d6a.z === -32768 &&
      x.historyState.aimOrigin524.x === 501 && x.historyState.aimOrigin524.y === 502 && x.historyState.aimOrigin524.z === 503,
      'snapshot observes actual actor BAM bits and world short owners without a matrix-mode gate; target83 skips unrelated masks/control word');
    check(x.targetActor.pos.y === -99 && x.targetPose.translation.y === -102 && x.targetMatrices[1]![7] === -77 &&
      x.normalState.link4a4 === x.target,
      'source visibility association is distinct from linked matrix receiver; history never snapshots or ticks that receiver');
    x.sourceActor.visibilityTarget = null; x.sourceActor.aimOrigin518.y = NaN;
    x.snapshot(); check(x.historyState.aimOrigin524.y === 502, 'changed null visibility association skips unread aim values and retains history');
  }
  {
    const x = historyHydratedControlFixture();
    x.sourceActor.visibilityTarget = {eligibility83: 0, visibilityMask5e6: 4, controlWord: NaN};
    x.sourceActor.visibilityBit = 2; x.snapshot();
    check(x.historyState.aimOrigin524.y === -12, 'nonintersecting actual target mask preserves prior aim origin');
    x.sourceActor.visibilityBit = 4; x.snapshot();
    check(x.historyState.aimOrigin524.y === 502, 'intersecting actual visibility mask copies source aim origin');
    Object.assign(x.sourceActor.pos, {x: 7, y: 8, z: 9}); x.sourceActor.stepHeight = 11;
    Object.defineProperty(x.historyState.aimOrigin524, 'y', {writable: false});
    x.sourceActor.aimOrigin518.x = 601; x.sourceActor.aimOrigin518.y = 602;
    rejects(x.snapshot, 'non-writable');
    check(x.sourceActor.savedGroundPos.x === 7 && x.sourceActor.savedGroundPos.y === 8 && x.sourceActor.savedGroundPos.z === 9 &&
      x.historyState.previousStepHeight6d4 === 11 && x.historyState.aimOrigin524.x === 601 && x.historyState.aimOrigin524.y === 502 &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77,
      'late aim Y store refusal preserves completed history and first aim word without any fabricated rollback or matrix refresh');
  }

  {
    const x = normalMatrixHydratedControlFixture();
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x13;
    x.metadata.getActorBinding(x.actor).byte1d99 = NaN;
    x.movement.getActorBinding(x.actor).field670 = NaN;
    x.mapping.getActor(x.actor).descriptor4b0 = null;
    x.updateNormal();
    check(x.normalState.field1d60 === 8 && x.header.adjusted1d54.y === 39 &&
      x.worldMatrix[3] === 140 && x.worldMatrix[7] === 119 && x.worldMatrix[11] === 468 &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, x.worldMatrix[i])) &&
      x.pose.translation.y === 27 && x.rootMatrix[7] === 2 && x.liftedRoot[7] === 11,
      'real selector3 adds damped correction to actual adjustedY before corrected traversal and linked copy, without reading unused terrain inputs');
  }
  {
    const x = normalMatrixHydratedControlFixture();
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x12;
    x.metadata.getActorBinding(x.actor).byte1d99 = 0;
    const descriptor = x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);
    descriptor.joint22 = 1; descriptor.joint2a = 255;
    x.updateNormal();
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 && x.normalState.field1d60 === 8 &&
      x.header.adjusted1d54.y === 39 && x.worldMatrix[7] === 119 && x.targetMatrices[1]![7] === 119,
      'real handler2 reads first-pass world joint above threshold, then sentinel, before damping and actual corrected matrix/receiver update');
    const retained = [...x.worldMatrix], target = [...x.targetMatrices[1]!];
    x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix.every((v, i) => Object.is(v, retained[i])) &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, target[i])) && x.header.adjusted1d54.y === 39,
      'packed wait retains terrain-adjusted matrix output and does not repeat damping');
    const old = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.pose.translation.y === 27 && x.worldMatrix[7] === 119 && x.targetMatrices[1]![7] === 119 &&
      x.sourceActor.stepHeight === Math.fround(58.5 * Math.fround(0.7)) && x.joints.getBinding(x.joint).aobj7c !== old &&
      x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'replacement setup consumes retained corrected worldY through actual movement owner without touching linked pose or clock');
  }
  {
    const x = normalMatrixHydratedControlFixture();
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x12;
    x.metadata.getActorBinding(x.actor).byte1d99 = 0xc0;
    const descriptor = x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);
    descriptor.joint22 = 254; descriptor.joint2a = 254; descriptor.joint32 = 254; descriptor.joint3a = 254;
    x.updateNormal();
    check(x.worldMatrix[7] === 119 && x.targetMatrices[1]![7] === 119 && x.normalState.field1d60 === 8,
      'signed metadata mask skips all four real descriptor entries, including bits8/9, without treating negative2 as a sentinel or reading invalid matrix indices');
  }
  {
    const x = normalMatrixHydratedControlFixture();
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x12;
    x.metadata.getActorBinding(x.actor).byte1d99 = 0;
    const descriptor = x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);
    descriptor.joint22 = 255; descriptor.joint2a = NaN; descriptor.joint32 = NaN; descriptor.joint3a = NaN;
    x.updateNormal();
    check(x.worldMatrix[7] === 119 && x.normalState.field1d60 === 8,
      'actual first-entry minus1 sentinel skips unused later descriptor bytes and still performs handler2 tail');
  }
  {
    const x = normalMatrixHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x12;
    x.metadata.getActorBinding(x.actor).byte1d99 = 0;
    const descriptor = x.movement.getDescriptorBinding(x.mapping.getActor(x.actor).descriptor4b0!);
    descriptor.joint22 = 1; descriptor.joint2a = 0;
    rejects(x.updateNormal, '3d6e4');
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 && x.normalState.field1d60 === 10 &&
      x.header.adjusted1d54.y === 31 && x.rootMatrix[7] === 2 && x.worldMatrix[7] === 95 &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'reached terrain query refuses after first-pass matrices and cleared counts, before invented height, damping, adjustedY, corrected pass or linked copy');
  }

  {
    const x = normalMatrixHydratedControlFixture(); x.updateNormal();
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 && x.normalState.field1d60 === 8 &&
      x.header.adjusted1d54.x === 20 && x.header.adjusted1d54.y === 31 && x.header.adjusted1d54.z === 42 &&
      x.worldMatrix[3] === 140 && x.worldMatrix[7] === 95 && x.worldMatrix[11] === 468,
      'normal source caller clears shared correction counts, damps actual field, and rebuilds supported corrected pass without adding damping to translation');
    check(x.targetMatrices[0]!.every((v, i) => Object.is(v, x.rootMatrix[i])) &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, x.worldMatrix[i])) &&
      x.targetCopies.every(matrix => matrix.every(v => v === -77)) &&
      x.targetActor.pos.y === -99 && x.targetActor.stepHeight === -88 && x.targetPose.translation.y === -102 &&
      x.targetHeader.adjusted1d54.y === -6 && x.mapping.getActor(x.target).jointCount1d90 === 0,
      'real source-count copy reaches separate linked actor slots despite target mode2 and count0, without copying pose, positions, root copies or scratch');
    const retained = [...x.worldMatrix], targetRetained = [...x.targetMatrices[1]!];
    x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix.every((v, i) => Object.is(v, retained[i])) &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, targetRetained[i])) && x.normalState.field1d60 === 8,
      'packed wait does not silently refresh either actor matrix or advance normal damping');
    const priorHeight = x.sourceActor.stepHeight; x.updateNormal();
    check(x.normalState.field1d60 === Math.fround(8 * Math.fround(0.8)) &&
      x.worldMatrix[3] === 152 && x.worldMatrix[7] === 113 && x.worldMatrix[11] === 492 &&
      x.targetMatrices[1]!.every((v, i) => Object.is(v, x.worldMatrix[i])) && x.liftedRoot[7] === Math.fround(2 + priorHeight),
      'next explicit normal call captures new bank-zero pose and copies completed corrected output to actual linked actor');
    const previous = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.pose.translation.y === 27 && x.worldMatrix[7] === 113 && x.targetMatrices[1]![7] === 113 &&
      x.sourceActor.stepHeight === Math.fround(55.5 * Math.fround(0.7)) && x.joints.getBinding(x.joint).aobj7c !== previous &&
      x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'real replacement setup consumes retained normal matrix through the shared movement owner without a second clock or linked-actor movement');
  }
  {
    const x = normalMatrixHydratedControlFixture();
    x.movement.getActorBinding(x.actor).byte661 = 1; x.normalState.count1d96 = 5; x.normalState.count1d97 = 6;
    x.normalState.field1d60 = NaN; x.sourceActor.flyer741 = NaN; x.normalState.byte660 = NaN;
    x.metadata.getActorBinding(x.actor).byte1d98 = NaN; x.globals.maskD2 = x.sourceActor.visibilityBit;
    x.sourceActor.pos.y = 12; x.updateNormal();
    check(x.rootMatrix[7] === 12 && x.worldMatrix[7] === 105 && x.targetMatrices[1]![7] === 105 &&
      x.normalState.count1d96 === 5 && x.normalState.count1d97 === 6 && Number.isNaN(x.normalState.field1d60),
      'shared movement byte skips damping and corrected scan while current visibility mask skips unused postprocess operands');
  }
  {
    const x = normalMatrixHydratedControlFixture();
    x.sourceActor.controlWord |= 0x20000000; x.metadata.getActorBinding(x.actor).byte1d98 = NaN;
    x.sourceActor.flyer741 = 1; x.mapping.getActor(x.actor).descriptor4b0 = null;
    x.updateNormal();
    check(x.normalState.field1d60 === 8 && x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 &&
      x.targetMatrices[1]![7] === 95,
      'suppressed terrain route reads descriptor identity but no metadata or descriptor byte, then genuine flyer guard permits linked copy');
  }
  {
    const x = normalMatrixHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    x.metadata.getActorBinding(x.actor).byte1d98 = 0x10; x.sourceActor.pos.y = 12;
    rejects(x.updateNormal, '46e7c');
    check(x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 && x.normalState.field1d60 === 10 &&
      x.rootMatrix[7] === 12 && x.worldMatrix[7] === 105 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'unsupported selected terrain handler refuses after completed first pass and zero stores, before invented damping, corrected output or linked copy');
  }
  {
    const x = normalMatrixHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    x.metadata.getActorBinding(x.actor).byte1d98 = 1; x.sourceActor.pos.y = 12;
    rejects(x.updateNormal, '47904');
    check(x.normalState.field1d60 === 8 && x.normalState.count1d96 === 0 && x.normalState.count1d97 === 0 &&
      x.rootMatrix[7] === 12 && x.worldMatrix[7] === 105 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'active unsupported postprocess retains real damping and both passes but refuses before any linked copy or fabricated IK output');
  }
  {
    const x = normalMatrixHydratedControlFixture(), retained = [...x.targetMatrices[1]!];
    x.sourceActor.steerYaw = 1; x.sourceActor.pos.y = 12;
    rejects(x.updateNormal, 'short');
    check(x.worldStorage.corrections18d4[1]!.x === undefined && x.worldMatrix[7] === 105 && x.worldMatrix[5] === 3 &&
      x.rootMatrix[7] === 12 && x.normalState.count1d96 === 8 && x.normalState.count1d97 === 9 &&
      x.normalState.field1d60 === 10 && x.targetMatrices[1]!.every((v, i) => Object.is(v, retained[i])),
      'actual steering field is joint1 X correction, read after first pose Concat; failure retains that matrix before correction, scale or terrain');
  }
  {
    const x = normalMatrixHydratedControlFixture(), root = [...x.rootMatrix], target = [...x.targetMatrices[1]!];
    x.header.mode4a0 = 2; x.sourceActor.pos.y = NaN; x.normalState.field1d60 = NaN;
    x.sourceActor.flyer741 = NaN; x.globals.maskD2 = NaN; x.movement.getActorBinding(x.actor).byte661 = NaN;
    x.updateNormal();
    check(x.rootMatrix.every((v, i) => Object.is(v, root[i])) && x.targetMatrices[1]!.every((v, i) => Object.is(v, target[i])) &&
      x.normalState.count1d96 === 8 && x.normalState.count1d97 === 9,
      'normal initial mode2 gate avoids all unused transforms, movement, postprocess globals and link effects');
  }

  {
    const x = worldMatrixHydratedControlFixture();
    check(x.pose.translation.x === 17 && x.pose.translation.y === 27 && x.pose.translation.z === 37 &&
      x.header.adjusted1d54.x === 20 && x.header.adjusted1d54.y === 31 && x.header.adjusted1d54.z === 42 &&
      x.worldMatrix[3] === 140 && x.worldMatrix[7] === 95 && x.worldMatrix[11] === 468 &&
      x.worldMatrix[0] === 2 && x.worldMatrix[5] === 6 && x.worldMatrix[10] === 4,
      'actual first-pass root and special joint1 wrappers consume captured pose plus separate offset without mutating pose');
    check(x.rootMatrix[7] === 2 && x.copiedRoot[7] === 2 && x.liftedRoot[7] === 11 &&
      x.copiedRoot.every((value, i) => Object.is(value, x.rootMatrix[i])),
      'source root copies share root values, with prior movement height added only to second copy');
    const retained = [...x.worldMatrix]; x.control.update(x.actor, 2);
    check(x.pose.translation.y === 33 && x.worldMatrix.every((value, i) => Object.is(value, retained[i])),
      'packed wait changes pose but leaves actual source traversal matrices retained');
    const previous = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.pose.translation.y === 27 && x.worldMatrix[7] === 95 &&
      x.sourceActor.stepHeight === Math.fround(46.5 * Math.fround(0.7)) && x.liftedRoot[7] === 11 &&
      x.joints.getBinding(x.joint).aobj7c !== previous,
      'replacement setup consumes source-produced retained world matrix without rebuilding root copies');
    x.control.update(x.actor, 2); const priorHeight = x.sourceActor.stepHeight; x.rebuild();
    check(x.pose.translation.y === 33 && x.header.adjusted1d54.y === 37 &&
      x.worldMatrix[3] === 152 && x.worldMatrix[7] === 113 && x.worldMatrix[11] === 492 &&
      x.liftedRoot[7] === Math.fround(2 + priorHeight),
      'later explicit caller refresh reads current pose and last actual movement height');
    x.begin(); check(x.worldMatrix[7] === 113 && x.pose.translation.y === 27 &&
      x.sourceActor.stepHeight === Math.fround(55.5 * Math.fround(0.7)),
      'next setup uses newly retained source traversal output, not its freshly captured local pose');
    x.header.flags48a = 2; x.header.offset1dbc.x = 1000; x.header.offset1dbc.z = 2000;
    x.rebuild(); check(x.header.adjusted1d54.x === 26 && x.header.adjusted1d54.y === 20 &&
      x.header.adjusted1d54.z === 48 && x.worldMatrix[3] === 152 && x.worldMatrix[7] === 62 && x.worldMatrix[11] === 492,
      'alternate flags write only authenticated special Y20 and preserve prior XZ despite current pose/offset changes');
    x.mapping.getLayout(x.actor).poses[1]!.forEach(id => {x.feedback.getPose(id).translation.y = -500;});
    x.header.flags48a = 0; x.header.offset1dbc.x = 3; x.header.offset1dbc.z = 5; x.rebuild();
    check(x.worldMatrix[7] === 95 && x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'bank-zero capture remains authoritative and explicit caller never advances host physics or legacy clocks');
  }
  {
    const x = worldMatrixHydratedControlFixture(), retained = [...x.worldMatrix];
    x.header.mask1d70 = 0; x.sourceActor.pos.y = 10; x.rebuild();
    check(x.rootMatrix[7] === 10 && x.worldMatrix.every((value, i) => Object.is(value, retained[i])),
      'inactive joint retains full matrix while root generation still executes');
    x.header.mode4a0 = 2; x.sourceActor.pos.y = NaN; x.header.offset1dbc.x = NaN;
    const savedRoot = [...x.rootMatrix]; x.rebuild();
    check(x.rootMatrix.every((value, i) => Object.is(value, savedRoot[i])),
      'disabled first-pass caller skips source transforms and invalid unused inputs');
  }
  {
    const x = worldMatrixHydratedControlFixture(), retained = [...x.worldMatrix];
    x.header.preRotation1d64.x = 1; x.sourceActor.pos.y = 10;
    rejects(x.rebuild, 'short');
    check(x.rootMatrix[7] === 10 && x.copiedRoot[7] === 10 && x.liftedRoot[7] === 19 &&
      x.worldMatrix.every((value, i) => Object.is(value, retained[i])),
      'unsupported special wrapper preserves completed root and copies without claiming a successful traversal');
  }
  {
    const x = matrixHydratedControlFixture();
    check(x.matrix[0] === 2 && x.matrix[5] === 6 && x.matrix[10] === 4 &&
      x.matrix[3] === 134 && x.matrix[7] === 281 && x.matrix[11] === 448,
      'explicit source matrix helper composes actual captured DAT pose with resolved parent and separate source scale');
    const retained = [...x.matrix];
    check(x.control.update(x.actor, 2) === 0 && x.pose.translation.y === 33 && x.matrix.every((value, i) => Object.is(value, retained[i])),
      'packed wait changes live bank0 pose without secretly rebuilding existing matrix pool');
    x.begin();
    check(x.pose.translation.y === 27 && x.matrix[7] === 281 &&
      x.sourceActor.stepHeight === Math.fround(139.5 * Math.fround(0.7)),
      'next setup captures new pose but movement reads retained generated world Y, not local translation or a recomputed value');
    x.control.update(x.actor, 2); x.rebuild();
    check(x.pose.translation.y === 33 && x.matrix[3] === 146 && x.matrix[7] === 299 && x.matrix[11] === 472,
      'later explicit matrix phase uses current actual pose through the same owner');
    const previous = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.pose.translation.y === 27 && x.matrix[7] === 299 &&
      x.sourceActor.stepHeight === Math.fround(148.5 * Math.fround(0.7)) &&
      x.joints.getBinding(x.joint).aobj7c !== previous && x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'replacement setup consumes newly retained shared matrix without double clock or host movement');
    x.mapping.getLayout(x.actor).poses[1]!.forEach(id => {if (id !== null) x.feedback.getPose(id).translation.y = -500;});
    x.rebuild(); check(x.matrix[7] === 281, 'explicit source bank0 pose remains authoritative despite bank1 changes');
    x.correction.x = 1;
    rejects(x.rebuild, 'correction');
    check(x.matrix[5] === 3 && x.matrix[7] === 281,
      'unsupported correction retains actual parent-pose concat before scale, without fabricated success');
  }
  {
    const x = modelHydratedControlFixture(), root = x.importedModel.root;
    const byOffset = (offset: number) => x.importedModel.joints.find(row => row.dataOffset === offset)!.joint;
    const firstChild = byOffset(0), grandchild = byOffset(0xc0);
    check(root === byOffset(0x80) && x.joint === byOffset(0x40) && x.importedModel.joints.length === 4 &&
      x.joints.getJoint(root).child10 === firstChild && x.joints.getJoint(firstChild).sibling08 === x.joint &&
      x.joints.getJoint(firstChild).child10 === grandchild && x.joints.getJoint(root).sibling08 === null &&
      x.joints.getBinding(firstChild).parent0c === root && x.joints.getBinding(x.joint).parent0c === root &&
      x.joints.getBinding(grandchild).parent0c === firstChild && x.joints.getJoint(root).flags14 === 0x70000040,
      'model DAT establishes actual parent/child/sibling identities and descendant flags, never follows selected root sibling');
    const untouched = [root, firstChild, grandchild].map(id => ({id, snapshot: {...x.joints.getJoint(id)}}));
    const oldRoot = root; x.modelDat.fill(0); x.dat.fill(0); x.begin();
    const first = x.joints.getBinding(x.joint).aobj7c;
    check(first !== null && x.feedback.getAObj(first!).frame === 2 && x.pose.translation.x === 17 &&
      x.pose.translation.y === 27 && x.pose.translation.z === 37 && x.sourceActor.stepHeight === 0 &&
      x.joints.getJoint(x.joint).translation38 === 17 && x.importedModel.root === oldRoot,
      'two independently hydrated DAT inputs feed actual opcode01, replacement, packed playback and mapped pose on explicit selected joint');
    for (const row of untouched) check(Object.entries(row.snapshot).every(([key, value]) =>
      Object.is(x.joints.getJoint(row.id)[key as keyof typeof row.snapshot], value)) && x.joints.getBinding(row.id).aobj7c === null,
      'single-JObj source setup never animates or attaches the model root, other sibling or grandchild');
    check(x.control.update(x.actor, 2) === 0 && x.feedback.getAObj(first!).frame === 4 && x.pose.translation.x === 23 &&
      x.control.update(x.actor, 2) === 1 && x.feedback.getAObj(first!).frame === 4,
      'source wait advances imported model joint exactly once and terminal stop does not add another clock');
    x.begin(); const second = x.joints.getBinding(x.joint).aobj7c;
    check(second !== null && second !== first && x.feedback.getAObj(second).frame === 2 && x.pose.translation.x === 17 &&
      x.joints.getBinding(x.joint).parent0c === oldRoot && x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
      'repeat command replaces only the real imported joint animation, retaining model ownership and host clock boundaries');
    rejects(() => x.feedback.getAObj(first!), 'unknown/non-owned AObj');
    const invalid = modelDatFixture(); new DataView(invalid.buffer).setUint32(0x20 + 0x84, 0x1000);
    rejects(() => x.modelHydration.hydrateModelArchive(invalid, 0), 'instance');
    check(x.joints.getBinding(x.joint).aobj7c === second && x.pose.translation.x === 17,
      'rejected model preflight does not disturb live setup ownership or pose');
    const another = x.modelHydration.hydrateModelArchive(modelDatFixture(), 0);
    check(another.root !== oldRoot && another.joints.every(row => !x.importedModel.joints.some(old => old.joint === row.joint)) &&
      x.joints.getBinding(x.joint).aobj7c === second && x.joints.getJoint(another.root).flags14 === 0x70000040,
      'valid model reimport has fresh joint identities and does not rebind an existing actor bank');
    for (const row of another.joints) x.joints.getJoint(row.joint).flags14 &= ~0x40;
    x.joints.updateScalar(another.root, 5, 123);
    check(another.joints.every(row => (x.joints.getJoint(row.joint).flags14 & 0x40) !== 0),
      'imported hierarchy is consumed by the actual dirty-subtree owner, not just metadata');
  }
  {
    const x = displayHydratedControlFixture();
    x.attachment.addAnimation(x.joint, null);
    check(x.joints.getBinding(x.joint).aobj7c === null && x.displayVisits.length === 0 &&
      x.displayBindings().every((id, i) => id === x.oldAObjs[i]) && x.textureAObj.frame === 1 && x.textureAObj.flags === AOBJ_REQUEST,
      'null AnimJoint traverses display attachment without changing preexisting animations or playing them');
    x.dat.fill(0); x.begin(); const first = x.joints.getBinding(x.joint).aobj7c;
    check(first !== null && x.feedback.getAObj(first).frame === 2 && x.pose.translation.x === 17 &&
      x.displayBindings().every((id, i) => id === x.oldAObjs[i]) && x.textureAObj.fobjs === x.textureNode &&
      x.textureAObj.frame === 1 && x.tobjs.getTexture(x.texture).translation34 === 12 &&
      x.displayVisits.every((owner, i) => owner === x.owners[i]) && x.displayVisits.length === 7 && x.requestCalls === 2,
      'DAT ready setup replaces joint only, preserves real display lifetimes and plays existing texture stream through same owned graph');
    for (const i of [0, 1, 2, 4, 5, 6]) check(x.feedback.getAObj(x.oldAObjs[i]!).frame === 10 + i &&
      x.feedback.getAObj(x.oldAObjs[i]!).flags === AOBJ_STOPPED, 'joint-only request preserves stopped display clocks');
    x.displayVisits.length = 0;
    check(x.control.update(x.actor, 2) === 0 && x.textureAObj.frame === 2 &&
      x.tobjs.getTexture(x.texture).translation34 === 14 && x.displayVisits.length === 7,
      'source wait advances joint and retained texture once, not a second display clock');
    check(x.control.update(x.actor, 2) === 1 && x.textureAObj.frame === 2 && x.displayVisits.length === 7,
      'source terminal stop does not run display animation again');
    x.displayVisits.length = 0; x.begin();
    check(x.joints.getBinding(x.joint).aobj7c !== first && x.displayBindings().every((id, i) => id === x.oldAObjs[i]) &&
      x.textureAObj.fobjs === x.textureNode && x.textureAObj.frame === 3 && x.tobjs.getTexture(x.texture).translation34 === 16 &&
      x.displayVisits.length === 7 && x.requestCalls === 3 && x.sourceActor.parts[1].frameClock === 123 && x.sourceActor.yVel === 7,
      'repeat setup replaces joint while preexisting packed texture advances instead of being reset or removed');
    rejects(() => x.feedback.getAObj(first!), 'unknown/non-owned AObj');
  }
  {
    const x = displayHydratedControlFixture(); x.begin();
    const old = x.joints.getBinding(x.joint).aobj7c; x.displayVisits.length = 0;
    x.dobjs.getDObj(x.d2).next04 = Symbol('unowned late DObj');
    rejects(() => x.begin(), 'unknown/non-owned DObj');
    const current = x.joints.getBinding(x.joint).aobj7c;
    check(current !== null && current !== old && x.feedback.getAObj(current).frame === 0 &&
      (x.feedback.getAObj(current).flags & AOBJ_STOPPED) !== 0 && x.requestCalls === 2 && x.displayVisits.length === 0 &&
      x.displayBindings().every((id, i) => id === x.oldAObjs[i]) && x.textureAObj.frame === 1,
      'late display attachment failure retains completed joint replacement, no request/playback or display rollback');
    rejects(() => x.feedback.getAObj(old!), 'unknown/non-owned AObj');
  }
  for (const bit of [0x20, 0x4000]) {
    const x = displayHydratedControlFixture(); x.joints.getJoint(x.joint).flags14 |= bit;
    x.joints.getBinding(x.joint).dobj18 = Symbol('unvisited display list'); x.begin();
    check(x.pose.translation.x === 17 && x.displayVisits.length === 0 && x.textureAObj.frame === 1 && x.requestCalls === 2,
      'actual final JObj display flag skips attachment, request and playback without inspecting list');
  }
  {
    const x = displayHydratedControlFixture(); x.begin(); const requests = x.requestCalls;
    x.requests.requestJoint(x.joint, 2, 0x1c);
    check(x.requestCalls === requests + 5 && x.feedback.getAObj(x.oldAObjs[0]!).frame === 10 &&
      x.feedback.getAObj(x.oldAObjs[4]!).frame === 14 &&
      [1, 2, 3, 5, 6].every(i => x.feedback.getAObj(x.oldAObjs[i]!).frame === 2 &&
        x.feedback.getAObj(x.oldAObjs[i]!).flags === AOBJ_REQUEST),
      'later actual material/shape/texture request resolves same preserved owner bindings and never requests DObj own AObj');
    x.displayVisits.length = 0; x.joints.animateJoint(x.joint, x.animationEffects);
    check(x.displayVisits.length === 7 && x.textureAObj.frame === 2 && x.tobjs.getTexture(x.texture).translation34 === 14,
      'actual nested display playback consumes retained texture decoder request without a copied display graph');
  }

  {
    const x = hydratedControlFixture(); x.begin(); const first = x.joints.getBinding(x.joint).aobj7c;
    const invalid = hydrationDatFixture(); new DataView(invalid.buffer).setUint32(0, invalid.length - 1);
    rejects(() => x.hydration.hydrateAnimationArchive(invalid, [0, 1]), 'file size');
    check(x.joints.getBinding(x.joint).aobj7c === first && x.pose.translation.x === 17 && x.requestCalls === 2,
      'bad DAT preflight cannot replace or advance the live graph');
    const nextBytes = hydrationDatFixture(); nextBytes[0x20 + 0xd8 + 1] = 41; nextBytes[0x20 + 0xd8 + 4] = 53;
    const next = x.hydration.hydrateAnimationArchive(nextBytes, [0, 1]);
    check(next.byteBase !== x.imported.byteBase && next.roots[0]!.descriptor !== x.imported.roots[0]!.descriptor &&
      x.joints.getBinding(x.joint).aobj7c === first && x.requestCalls === 2,
      'fresh DAT owns distinct archive/descriptor identities and cannot mutate the existing attached graph');
    x.archiveBanks.getPointerTable(x.selected)[0] = next.setupDescriptor; x.begin();
    const replacement = x.joints.getBinding(x.joint).aobj7c;
    check(replacement !== null && replacement !== first && x.pose.translation.x === 47 && x.pose.translation.y === 27 &&
      x.feedback.getAObj(replacement).frame === 2 && x.requestCalls === 3,
      'actual command replaces the live graph only after selecting the newly hydrated archive');
    rejects(() => x.feedback.getAObj(first!), 'unknown/non-owned AObj');
  }

  {
    const x = hydratedControlFixture(), first = x.imported.roots[0]!, second = x.imported.roots[1]!;
    check(first.dataOffset === 0 && second.dataOffset === 0 && first.descriptor === second.descriptor && first.address === second.address &&
      x.joints.getBinding(x.joint).aobj7c === null && x.requestCalls === 1 && x.clocks.elapsed08 === 7,
      'DAT hydration preserves public aliases and offset-zero roots without running setup or animation');
    x.dat.fill(0); x.begin(); const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 2 && x.feedback.getAObj(id).end === 3 &&
      x.pose.translation.x === 17 && x.pose.translation.y === 27 && x.pose.translation.z === 37 &&
      x.archiveFront.getPartBinding(x.partId).descriptor04 === x.imported.setupDescriptor &&
      x.ready.getPartBinding(x.partId).status38 === 0 && x.sourceActor.stepHeight === 0 &&
      x.waitControl.status1d === 1 && x.control.getActorBinding(x.actor).marker71d === 0 && x.requestCalls === 2,
      'actual ready part1 reads hydrated archive/FObj descriptors and copied packed bytes, not earlier handwritten graph');
    check(x.control.update(x.actor, 2) === 0 && id !== null && x.feedback.getAObj(id).frame === 4 &&
      x.clocks.elapsed08 === 2 && x.pose.translation.x === 23 && x.pose.translation.y === 33 && x.pose.translation.z === 43,
      'hydrated graph advances exactly once through source wait');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 2, 'hydrated terminal stop does not double advance');
    x.begin(); const replacement = x.joints.getBinding(x.joint).aobj7c;
    check(replacement !== null && replacement !== id && x.feedback.getAObj(replacement).frame === 2 &&
      x.pose.translation.x === 17 && x.requestCalls === 3 && x.sourceActor.parts[1].frameClock === 123 && x.sourceActor.yVel === 7,
      'repeat command replaces from the same hydrated descriptors without second owner/host clock');
    rejects(() => x.feedback.getAObj(id!), 'unknown/non-owned AObj');
  }

  {
    const x = movementControlFixture(); x.begin();
    const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 2 && x.pose.translation.x === 14 &&
      x.ready.getActorBinding(x.actor).movement6d8 === 1 && Object.is(x.sourceActor.stepHeight, 0) &&
      x.control.getActorBinding(x.actor).marker71d === 0 && x.waitControl.status1d === 1 &&
      x.waitControl.current00 === x.control.cursorAt(x.commands, 48) && x.stream.target08 === 2 &&
      x.clocks.elapsed08 === 0 && x.requestCalls === 2,
    'actual part1 ready setup completes early-zero movement then caller status/target/marker/terminal stores');
    check(x.control.update(x.actor, 2) === 0 && id !== null && x.feedback.getAObj(id).frame === 4 &&
      x.clocks.elapsed08 === 2 && x.sourceActor.yVel === 7 && x.sourceActor.parts[1].frameClock === 123,
    'part1 advances the real graph once without starting host physics or synthetic VM clock');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 2, 'part1 terminal stop does not double advance');
    x.sourceActor.stepHeight = 88; x.begin();
    const next = x.joints.getBinding(x.joint).aobj7c;
    check(next !== null && next !== id && x.feedback.getAObj(next).frame === 2 &&
      x.sourceActor.stepHeight === 0 && x.requestCalls === 3, 'part1 repeat replaces graph and recomputes shared step height');
    rejects(() => x.feedback.getAObj(id!), 'unknown/non-owned AObj');
  }
  {
    const x = movementControlFixture(); x.sourceActor.controlWord = 0x40; x.begin();
    check(x.sourceActor.stepHeight === 80 && x.control.getActorBinding(x.actor).marker71d === 0 &&
      x.waitControl.status1d === 1 && x.stream.target08 === 2,
    'movement uses live signed marker before opcode01 clears it, and actual model scale');
  }
  {
    const x = movementControlFixture(); x.sourceActor.controlWord = 0x40;
    x.control.getActorBinding(x.actor).marker71d = 0;
    const descriptor = x.mapping.getActor(x.actor).descriptor4b0;
    if (descriptor === null) throw Error('missing actual movement fixture descriptor');
    x.movement.bindDescriptor(descriptor, {joint0f: 0, joint22: 2, joint2a: 255, joint32: 0, joint3a: 0});
    x.movement.bindWorldMatrixY(x.actor, [20, 12, 7]); x.begin();
    check(x.sourceActor.stepHeight === Math.fround(2.8) && x.waitControl.status1d === 1 &&
      x.pose.translation.y === 24 && x.control.getActorBinding(x.actor).marker71d === 0,
    'part1 normal world-matrix clamp uses separate actual decoded matrices, not captured local pose');
    x.sourceActor.pos.y = 3; x.begin();
    check(x.sourceActor.stepHeight === Math.fround(3 * Math.fround(0.7)) && x.requestCalls === 3,
      'repeated part1 setup rereads actual position and world matrices');
  }
  {
    const x = movementControlFixture(); Object.defineProperty(x.sourceActor, 'stepHeight', {writable: false});
    rejects(x.begin, 'non-writable');
    const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 2 && x.sourceActor.stepHeight === 99 &&
      x.ready.getActorBinding(x.actor).movement6d8 === 1 && x.waitControl.status1d === 0 &&
      x.waitControl.current00 === null && x.control.getActorBinding(x.actor).marker71d === 9,
    'movement failure retains real setup and 6d8 store, but not caller continuation');
  }

  {
    const x = readyControlFixture(); Object.defineProperty(x.ready.getPartBinding(x.partId), 'status38', {writable: false});
    rejects(x.begin, 'non-writable');
    check(x.archiveFront.getPartBinding(x.partId).descriptor04 === x.wrapper && x.part.complete2e === 0 &&
      x.joints.getBinding(x.joint).aobj7c === null && x.requestCalls === 1 && x.waitControl.status1d === 0,
      'status38 store occurs after real archive selection but before any mapped attachment/capture');
  }
  {
    const x = readyControlFixture();
    const command = x.control.createStream(Uint8Array.from([1, 0, 1, 0, 0, 0, 255, 255, 0, 1, 0, 0]));
    x.control.parseWaitRecord(x.actor, x.mask, command);
    const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 4 && x.part.frame0c === 4 &&
      x.pose.translation.x === 18 && x.part.complete2e === 1 && x.stream.target08 === 6 &&
      x.clocks.elapsed08 === 0 && x.requestCalls === 2,
      'negative command frame resolves from actual prior frame plus timestep before real ready setup');
  }
  {
    const x = readyControlFixture();
    x.readyAdapter.setupModeZero = () => {throw Error('replaced setup method must not run');};
    x.begin(); check(x.pose.translation.x === 14, 'ready dispatcher captures original setup method and receiver');
    rejects(() => x.dispatch.bindSetupRuntime(x.ready), 'already bound');
    const id = x.joints.getBinding(x.joint).aobj7c;
    rejects(() => x.dispatch.setupPart(x.actor, 0, x.control.getActorBinding(x.actor),
      {frame: 2, group: 0, action: 1, transition: 0, mode: 2}), 'unsupported setup mode');
    check(x.joints.getBinding(x.joint).aobj7c === id && x.requestCalls === 2,
      'unsupported mode does not accidentally enter mode0');
  }
  for (const kind of ['async', 'reentry'] as const) {
    const x = readyControlFixture();
    x.readyHooks.afterMode = () => {
      if (kind === 'async') return Promise.resolve();
      rejects(() => x.dispatch.setupPart(x.actor, 0, x.control.getActorBinding(x.actor),
        {frame: 2, group: 0, action: 1, transition: 0, mode: 0}), 'reentry');
      return undefined;
    };
    rejects(x.begin, kind === 'async' ? 'synchronously return undefined' : 'reentry was caught');
    const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 2 && x.pose.translation.x === 14 &&
      x.waitControl.status1d === 0 && x.waitControl.current00 === null && x.requestCalls === 2,
    'ready dispatch adapter refusal preserves completed real setup but not caller continuation');
  }
  {
    const x = readyControlFixture();
    x.mapping.getActor(x.actor).descriptor4b0 = x.mapping.createDescriptor([1, 1]);
    x.mapping.getActor(x.actor).boundary1d91 = 2;
    x.begin();
    const id = x.joints.getBinding(x.joint).aobj7c;
    check(id !== null && x.feedback.getAObj(id).frame === 2 && x.requestCalls === 3 && x.pose.translation.x === 14,
      'repeated source map entries repeat actual replacement setup and capture, without caching or extra ticks');
  }
  {
    const x = readyControlFixture(); x.begin();
    const attached = x.joints.getBinding(x.joint).aobj7c;
    if (attached === null) throw Error('[attached-setup-animation-test] ready setup did not attach animation');
    check(attached !== null && attached !== x.initialAObj && x.feedback.getAObj(attached).frame === 2 &&
      x.part.frame0c === 2 && x.part.duration24 === 3 && x.part.complete2e === 0 &&
      x.pose.translation.x === 14 && x.pose.translation.y === 24 && x.pose.translation.z === 34 &&
      x.clocks.elapsed08 === 0 && x.clocks.previous10 === 0 && x.clocks.previous14 === 2 &&
      x.ready.getPartBinding(x.partId).status38 === 0 && x.ready.getPartBinding(x.partId).bank31 === 0 &&
      x.archiveFront.getPartBinding(x.partId).descriptor04 === x.wrapper && x.stream.target08 === 2 &&
      x.waitControl.status1d === 1 && x.waitControl.current00 === x.control.cursorAt(x.commands, 48) &&
      x.requestCalls === 2,
    'ready mode0 opcode01 performs actual non-null archive selection, allocation, attachment, capture and control stores without extra fallback');
    check(x.control.update(x.actor, x.mask) === 0 && x.feedback.getAObj(attached).frame === 4 &&
      x.clocks.elapsed08 === 2 && x.pose.translation.x === 18 && x.stream.target08 === 4,
    'ready graph resumes exactly once on subsequent source wait progression');
    check(x.control.update(x.actor, x.mask) === 1 && x.clocks.elapsed08 === 2,
      'ready graph final stop does not advance twice');
    x.begin(); const replacement = x.joints.getBinding(x.joint).aobj7c;
    check(replacement !== null && replacement !== attached && x.feedback.getAObj(replacement).frame === 2 &&
      x.clocks.elapsed08 === 0 && x.pose.translation.x === 14 && x.requestCalls === 3,
    'repeated ready command releases and replaces the actual graph, resetting shared state');
    rejects(() => x.feedback.getAObj(attached), 'unknown/non-owned AObj');
  }
  {
    const x = readyControlFixture(1);
    rejects(x.begin, '4d08c');
    const attached = x.joints.getBinding(x.joint).aobj7c;
    check(attached !== null && x.feedback.getAObj(attached).frame === 2 && x.pose.translation.x === 14 &&
      x.ready.getActorBinding(x.actor).movement6d8 === 1 && x.clocks.elapsed08 === 0 &&
      x.waitControl.status1d === 0 && x.waitControl.current00 === null &&
      x.control.getActorBinding(x.actor).marker71d === 9 && x.requestCalls === 2,
    'part1 unsupported movement postamble preserves real completed setup and 6d8 store but not caller continuation');
  }
  {
    const x = readyControlFixture(); x.archiveBanks.getPointerTable(x.selected)[0] = null;
    rejects(x.begin, 'out-of-count');
    check(x.archiveFront.getPartBinding(x.partId).descriptor04 === x.fallbackWrapper &&
      x.ready.getPartBinding(x.partId).status38 === 1 && x.part.complete2e === 1 &&
      x.joints.getBinding(x.joint).aobj7c === null && x.waitControl.status1d === 0,
    'real missing archive slot follows actual fallback before later unsupported setup, retaining source prefix');
  }
  {
    const x = metadataControlFixture(0);
    x.mapping.bindScaleTable(x.actor, [2]);
    x.part.mirror30 = 1; x.setup.getPartBinding(x.partId).loop2c = 1;
    const callbacks = x.receiverTracks.length;
    check(x.apply() === x.descriptors.cursorAt(x.descriptorBase, 48) &&
      x.part.mirror30 === 0 && x.mapping.getPartBinding(x.partId).scaleIndex32 === 0 &&
      x.setup.getPartBinding(x.partId).loop2c === 0 && x.setup.getPartBinding(x.partId).rewind26 === 7 &&
      x.metadata.getPartBinding(x.partId).selector2a === 0x81 &&
      x.metadata.getPartBinding(x.partId).selector2b === 2 &&
      x.metadata.getPartBinding(x.partId).auxiliary37 === 5 &&
      x.metadata.getActorBinding(x.actor).byte1d98 === 6 &&
      x.metadata.getActorBinding(x.actor).byte1d99 === 7 &&
      x.metadata.getActorBinding(x.actor).byte1d9b === 8 &&
      x.aobj.frame === 2 && x.clocks.elapsed08 === 7 && x.requestCalls === 1 && x.receiverTracks.length === callbacks,
    'real descriptor-bank selection writes shared metadata without advancing or faking ready setup');
    const old = x.joints.getBinding(x.joint).aobj7c;
    x.run();
    const attached = x.joints.getBinding(x.joint).aobj7c;
    check(attached !== null && attached !== old && x.requestCalls === 2 && x.part.segment2d === 0,
      'metadata clears the actual loop field consumed by real replacement attachment and setup tail');
    x.begin();
    check(x.feedback.getAObj(attached!).frame === 4 && x.pose.translation.x === 36 &&
      x.pose.translation.y === 56 && x.pose.translation.z === 76 && x.clocks.elapsed08 === 9,
    'metadata scaling and mirror writes reach actual playback on the replacement graph');
    x.start.defaultSelector582 = 3;
    check(x.apply() === x.descriptors.cursorAt(x.descriptorBase, 80) &&
      x.mapping.getPartBinding(x.partId).scaleIndex32 === 255,
    'descriptor selection reads the actual changed stream-start default, not a parallel owner');
  }
  {
    const x = metadataControlFixture(255, 5); x.apply();
    const old = x.joints.getBinding(x.joint).aobj7c;
    rejects(() => x.run(), 'rewind');
    const attached = x.joints.getBinding(x.joint).aobj7c;
    check(attached !== null && attached !== old &&
      (x.feedback.getAObj(attached).flags & AOBJ_LOOP) !== 0 &&
      x.setup.getPartBinding(x.partId).loop2c === 1 && x.requestCalls === 1,
    'metadata loop bit reaches real unsupported rewind branch after owned replacement, not fake success');
  }
  {
    const x = startedControlFixture(Uint8Array.from([1, 0x82, 0x17, 2, 4, 0, 255, 255, 0, 8, 0, 2, 0, 1, 0, 0]), true, true);
    const gates = x.dispatch.getActorBinding(x.actor);
    gates.marker578 = 1; gates.marker1db3 = 1;
    x.control.getActorBinding(x.actor).marker71d = 9;
    const callbacks = x.receiverTracks.length;
    x.begin();
    check(x.waitControl.current00 === x.control.cursorAt(x.base, 48) && x.waitControl.status1d === 1 &&
      x.stream.target08 === 2 && x.stream.accumulator10 === 0 && x.waitControl.wait14 === 2 &&
      x.control.getActorBinding(x.actor).marker71d === 0 && x.aobj.frame === 2 && x.clocks.elapsed08 === 7 &&
      x.requestCalls === 1 && x.receiverTracks.length === callbacks && x.pose.translation.x === -1,
    'actual marker-gated opcode01 completes source control stores without fake setup, playback or terminal fallback');
    gates.marker578 = 0;
    check(x.control.update(x.actor, 2) === 0 && x.aobj.frame === 4 && x.clocks.elapsed08 === 9 &&
      x.pose.translation.x === 18 && x.stream.target08 === 4 && x.waitControl.status1d === 1 &&
      x.waitControl.current00 === x.control.cursorAt(x.base, 52),
    'next parse without opcode01 restores actual fallback playback on the same archive-owned graph');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 9,
      'new terminal wait completes without another animation tick');
  }
  {
    const x = startedControlFixture(Uint8Array.from([1, 0, 0, 0, 0, 0, 0, 3, 0x10, 0, 1, 20, 0, 1, 0, 0]), true, true);
    x.dispatch.getActorBinding(x.actor).family1d88 = null;
    x.begin();
    check(x.stream.accumulator10 === 20 && x.stream.target08 === 2 && x.aobj.frame === 2 &&
      x.clocks.elapsed08 === 7 && x.waitControl.current00 === x.control.cursorAt(x.base, 52),
    'completed opcode01 suppresses terminal fallback even after a later actual accumulator command');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0]), true); x.run();
    const gates = x.dispatch.getActorBinding(x.actor); gates.marker578 = 1; gates.marker1db3 = 1;
    x.control.getActorBinding(x.actor).marker71d = 9;
    rejects(() => x.control.parseWaitRecord(x.actor, 6, x.base), 'unsupported setup table/4871c');
    const other = x.control.getPartBinding(x.actor, 2), otherTarget = x.wait.getStreamPart(x.actor, 2);
    check(x.waitControl.status1d === 1 && x.stream.previous0c === 78 && x.stream.target08 === 4 &&
      other.status1d === 0 && otherTarget.previous0c === 79 && otherTarget.target08 === 79 &&
      x.control.getActorBinding(x.actor).marker71d === 9 && x.waitControl.current00 === x.base &&
      x.aobj.frame === 2 && x.clocks.elapsed08 === 7 && x.requestCalls === 1,
    'earlier gated part stores survive later ready-setup refusal, without later marker/terminal or animation effects');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0]), true); x.run();
    x.dispatch.getActorBinding(x.actor).shared1d8c = null;
    x.control.getActorBinding(x.actor).marker71d = 9;
    rejects(() => x.control.parseWaitRecord(x.actor, 2, x.base), '8043712c');
    check(x.waitControl.status1d === 1 && x.stream.previous0c === 78 && x.stream.target08 === 4 &&
      x.control.getActorBinding(x.actor).marker71d === 0 && x.waitControl.current00 === x.base &&
      x.waitControl.finished1a === 1 && x.aobj.frame === 2 && x.clocks.elapsed08 === 7,
    'unsupported opcode01 speed branch retains all gated part and marker effects but no terminal install or playback');
  }
  {
    const x = fixture(1, true);
    const front = createSourceArchiveJointSetupRuntime({archives: x.archives, attachment: x.attachment,
      tail: {continueAttachedSetupTail(actor, part, joint) {
        x.setup.continueAttachedSetupTail(actor, part, joint);
        return Promise.resolve() as unknown as void;
      }}});
    front.bindPart(x.partId, {descriptor04: front.createDescriptor({archive0c: x.archive})});
    front.bindAddress(x.archiveBase, x.archives.cursorAt(x.archiveBase, 64), x.animDescriptor);
    const poses = front.createPoseTable([{translation0c: 0, translation1c: 0, translation2c: 0}]);
    rejects(() => front.continueResolvedArchiveSetup(x.actor, x.partId, x.joint, 0, poses), 'synchronously return void');
    const current = x.joints.getBinding(x.joint).aobj7c!;
    check(current !== x.aobjId && x.feedback.getAObj(current).frame === 2 &&
      x.feedback.getAObj(current).rate === 2 && x.requestCalls === 1 && x.part.segment2d === 0,
    'invalid tail return keeps completed real archive replacement, request, rate and segment stores');
    rejects(() => {x.feedback.getAObj(x.aobjId);}, 'unknown/non-owned AObj');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 8, 0, 2, 0x10, 0, 1, 20, 0, 1, 0, 0]), true, true);
    check(x.aobj.frame === 2 && x.aobj.rate === 2 && x.part.duration24 === 3 && x.nodes.length === 6 &&
      x.requestCalls === 1 && x.part.segment2d === 0,
    'archive index 1 resolves duplicate name to first address, allocates actual tracks and executes real setup tail');
    x.begin();
    check(x.aobj.frame === 4 && x.pose.translation.x === 18 && x.clocks.elapsed08 === 9 && x.stream.target08 === 4,
      'archive-selected actual animation reaches packed playback and pose capture');
    check(x.control.update(x.actor, 2) === 0 && x.stream.accumulator10 === 20 && x.stream.target08 === 24 &&
      x.control.update(x.actor, 2) === 1, 'archive-selected graph participates in actual command and wait progression');
    const oldId = x.aobjId;
    x.part.frame0c = 2; x.run();
    const replacementId = x.joints.getBinding(x.joint).aobj7c!;
    const replacement = x.feedback.getAObj(replacementId);
    check(replacementId !== oldId && replacement.frame === 2 && replacement.rate === 2 && x.requestCalls === 2,
      'repeated archive setup replaces the actual graph and completes request/rate setup');
    rejects(() => {x.feedback.getAObj(oldId);}, 'unknown/non-owned AObj');
    for (const id of x.nodes) rejects(() => {x.fobjs.getNode(id);}, 'unknown/non-owned node');
    x.begin();
    check(replacement.frame === 4 && x.pose.translation.x === 18 && x.clocks.elapsed08 === 13,
      'replacement archive graph becomes current playback owner rather than a captured first clock');
    x.setup.getPartBinding(x.partId).loop2c = 1;
    rejects(x.run, 'unverified DOUBLE_804370f8');
    const failedId = x.joints.getBinding(x.joint).aobj7c!;
    check(failedId !== replacementId && x.feedback.getAObj(failedId).frame === 0 &&
      (x.feedback.getAObj(failedId).flags & AOBJ_LOOP) !== 0 && x.requestCalls === 2,
    'unsupported tail retains archive-selected replacement and source loop flag before refusal');
    rejects(() => {x.feedback.getAObj(replacementId);}, 'unknown/non-owned AObj');
  }

  {
    const x = startedControlFixture(Uint8Array.from([0, 8, 0, 2, 0x10, 0, 1, 20, 0, 1, 0, 0]), true);
    check(x.aobj.frame === 0 && x.aobj.rate === 1 && x.joints.getBinding(x.joint).aobj7c === x.aobjId && x.nodes.length === 6,
      'genuine first attachment needs no caller-created AObj or manual binding assignment');
    x.run(); x.begin();
    check(x.aobj.frame === 4 && x.clocks.elapsed08 === 9 && x.pose.translation.x === 18 &&
      x.stream.target08 === 4 && x.waitControl.current00 === x.control.cursorAt(x.base, 40),
    'allocated and attached actual descriptor tracks feed setup, bank start, animation and pose capture');
    check(x.control.update(x.actor, 2) === 0 && x.stream.accumulator10 === 20 && x.stream.target08 === 24 &&
      x.control.update(x.actor, 2) === 1, 'genuine attachment continues through command and terminal wait lifecycle');
    const old = x.aobj, oldId = x.aobjId;
    x.attachment.addAnimation(x.joint, x.animDescriptor);
    rejects(() => {x.feedback.getAObj(oldId);}, 'unknown/non-owned AObj');
    rejects(() => requestSourceAObj(old, 0, x.fobjs.effects), 'factory-created');
    for (const node of x.nodes) rejects(() => {x.fobjs.getNode(node);}, 'unknown/non-owned node');
    const replacementId = x.joints.getBinding(x.joint).aobj7c!;
    const replacement = x.feedback.getAObj(replacementId);
    check(replacementId !== oldId && replacement.frame === 0 && replacement.rate === 1 && replacement.fobjs !== null && old.fobjs === null,
      'real replacement releases old tracks and clock identity before attaching independently initialized animation');
    x.part.frame0c = 2; x.run(); x.begin();
    check(replacement.frame === 4 && replacement.rate === 2 && x.pose.translation.x === 18 &&
      x.clocks.elapsed08 === 13 && x.stream.target08 === 4, 'replacement is the live playback owner, not a stale first-allocation capture');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 1, 0, 0]), true);
    x.run(); x.begin();
    const empty = x.attachment.createDescriptor({aobj08: null, robj0c: null, flags10: 0});
    x.attachment.addAnimation(x.joint, empty);
    check(x.joints.getBinding(x.joint).aobj7c === null && (x.joints.getJoint(x.joint).flags14 & 8) === 0 && x.aobj.fobjs === null,
      'null AObj descriptor removes the actual prior animation and stores null before source flags');
    rejects(() => {x.feedback.getAObj(x.aobjId);}, 'unknown/non-owned AObj');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0x10, 255, 1, 7, 0, 1, 0, 0])); x.run(); x.begin();
    check(x.start.marker709 === 0 && x.waitControl.group18 === 2 && x.waitControl.action19 === 1 &&
      x.waitControl.status1d === 0 && x.waitControl.event1e === 0 && x.waitControl.finished1a === 0 &&
      x.waitControl.current00 === x.control.cursorAt(x.base, 44) && x.waitControl.next04 === x.control.cursorAt(x.base, 48) &&
      x.stream.previous0c === 0 && x.stream.accumulator10 === 7 && x.stream.target08 === 11 &&
      x.aobj.frame === 4 && x.clocks.elapsed08 === 9 && x.pose.translation.x === 18,
    'bank start resolves actual relative tables, stamps/resets shared state, and executes command plus packed fallback');
    check(x.wait.getStreamPart(x.actor, 0).target08 === 77 && x.control.getPartBinding(x.actor, 0).event1e === 7 &&
      x.control.getPartBinding(x.actor, 0).current00 === x.base, 'bank start leaves nonselected actual state untouched');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 9, 'started terminal stop waits for the next actor update');
    x.begin(2);
    check(x.waitControl.finished1a === 0 && x.stream.previous0c === 0 && x.stream.accumulator10 === 7 &&
      x.stream.target08 === 11 && x.clocks.elapsed08 === 11 && x.aobj.frame === 4,
    'restarting resets stream targets and control completion without duplicating or resetting the actual animation clock');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 8, 0, 2, 0x10, 0, 1, 20, 0, 1, 0, 0])); x.run(); x.begin();
    check(x.stream.accumulator10 === 0 && x.stream.target08 === 4 && x.waitControl.wait14 === 2,
      'start reset clears stale accumulator before the first real fallback');
    check(x.control.update(x.actor, 2) === 0 && x.stream.accumulator10 === 20 && x.stream.target08 === 24 &&
      x.clocks.elapsed08 === 11 && x.waitControl.current00 === x.control.cursorAt(x.base, 48) && x.waitControl.finished1a === 0,
    'started countdown continues through actual byte commands and shared target playback');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 11, 'started stream completes without a second same-tick evaluation');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 1, 0, 0])); x.run();
    x.start.sharedBank1d84 = x.start.familyBank1d80; x.start.familyBank1d80 = Symbol('unused foreign family');
    x.begin(0x82);
    check(x.waitControl.group18 === 0x82 && x.waitControl.action19 === 1 && x.stream.target08 === 4 &&
      x.clocks.elapsed08 === 9 && x.aobj.frame === 4, 'shared bank selection masks the lookup but retains original selector stamp');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 1, 0, 0])); x.run();
    x.start.familyBank1d80 = null; x.start.defaultSelector582 = NaN; x.begin();
    for (let i = 0; i < 4; i++) {
      const control = x.control.getPartBinding(x.actor, i), target = x.wait.getStreamPart(x.actor, i);
      check(control.current00 === null && control.next04 === null && control.wait14 === 0 && control.finished1a === 1 &&
        control.event1e === 0 && control.status1d === 0 && target.previous0c === 0 && target.target08 === 0 && target.accumulator10 === 0,
      'missing bank resets and finishes all four source controls, ignoring selection and unused default');
    }
    check(x.waitControl.group18 === 97 && x.waitControl.action19 === 98 && x.start.marker709 === 0 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2 && x.pose.translation.x === -1,
    'null bank neither stamps selectors nor advances actual animation');
  }
  {
    const x = startedControlFixture(Uint8Array.from([1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0])); x.run();
    rejects(x.begin, 'unsupported setup table/4871c');
    check(x.start.marker709 === 0 && x.waitControl.group18 === 2 && x.waitControl.action19 === 1 &&
      x.waitControl.current00 === null && x.waitControl.next04 === null && x.waitControl.wait14 === 0 &&
      x.waitControl.finished1a === 0 && x.waitControl.event1e === 0 && x.stream.target08 === 0 &&
      x.stream.accumulator10 === 0 && x.clocks.elapsed08 === 7 && x.aobj.frame === 2,
    'unsupported real setup opcode retains resolved source start/reset effects without a fake setup or animation tick');
  }
  {
    const x = startedControlFixture(Uint8Array.from([0, 1, 0, 0])); x.run();
    x.start.familyBank1d80 = x.control.cursorAt(x.base, 100);
    rejects(x.begin, 'out of bounds');
    check(x.start.marker709 === 0 && x.waitControl.group18 === 97 && x.waitControl.action19 === 98 &&
      x.waitControl.current00 === x.base && x.waitControl.wait14 === 99 && x.stream.target08 === 78 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2, 'bank lookup fault clears reached marker but precedes stamps, resets and playback');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0x10, 255, 1, 7, 0, 1, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.stream.accumulator10 === 7 && x.stream.previous0c === 78 && x.stream.target08 === 11 &&
      x.aobj.frame === 4 && x.clocks.elapsed08 === 9 && x.pose.translation.x === 18 &&
      x.waitControl.current00 === x.control.cursorAt(x.base, 4) && x.waitControl.next04 === x.control.cursorAt(x.base, 8),
    'opcode10 mode1 writes the actual shared accumulator before packed fallback produces frame4 plus7');
    check(x.control.update(x.actor, 2) === 1 && x.stream.target08 === 11 && x.clocks.elapsed08 === 9,
      'terminal wait flags come from the reached record, not ignored command byte1');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0x10, 99, 2, 2, 0x10, 88, 2, 3, 0x10, 77, 1, 9, 0, 1, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.part.mirror30 === 0 && x.stream.accumulator10 === 9 && x.stream.target08 === 13 &&
      x.clocks.elapsed08 === 9 && x.aobj.frame === 4 && x.pose.translation.x === 18 &&
      x.waitControl.current00 === x.control.cursorAt(x.base, 12) && x.waitControl.next04 === x.control.cursorAt(x.base, 16),
    'set then XOR shared mirror and accumulator commands all execute before one actual fallback and terminal install');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0x10, 0, 2, 1, 0x10, 0, 1, 5, 0, 1, 0, 0])); x.run();
    x.part.mirror30 = 255;
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.part.mirror30 === 0 && x.stream.accumulator10 === 5 && x.stream.target08 === 9 && x.aobj.frame === 4,
      'mode2 clear overwrites the real mirror byte before real mapping reads it');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0x10, 0, 2, 2, 0, 1, 0, 0])); x.run();
    rejects(() => x.control.parseWaitRecord(x.actor, 2, x.base), 'mirrored joint mapping');
    check(x.part.mirror30 === 1 && x.stream.previous0c === 78 && x.stream.target08 === 78 &&
      x.clocks.elapsed08 === 9 && x.part.frame0c === 4 && x.aobj.frame === 2 &&
      x.waitControl.current00 === x.base && x.waitControl.next04 === null && x.waitControl.wait14 === 99,
    'set-mirror command is retained while actual unsupported mirrored mapping refuses before decoder, target and wait installation');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0, 8, 0, 2, 0x10, 0, 1, 20, 0, 1, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.control.update(x.actor, 2) === 0 && x.stream.accumulator10 === 20 && x.stream.previous0c === 6 &&
      x.stream.target08 === 24 && x.clocks.elapsed08 === 11 && x.aobj.frame === 4 &&
      x.waitControl.current00 === x.control.cursorAt(x.base, 8) && x.waitControl.finished1a === 0,
    'met non-stop countdown executes a real nonzero command chain before the next wait and target');
    check(x.control.update(x.actor, 2) === 1 && x.stream.target08 === 24 && x.clocks.elapsed08 === 11,
      'command chain does not re-evaluate the new terminal wait in the same tick');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0x10, 0, 1, 7])); x.run();
    rejects(() => x.control.parseWaitRecord(x.actor, 2, x.base), 'out of bounds');
    check(x.stream.accumulator10 === 7 && x.stream.previous0c === -3 && x.stream.target08 === 78 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2 && x.waitControl.next04 === null && x.waitControl.wait14 === 99,
    'missing terminal opcode retains a completed command effect but performs no animation fallback or control install');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0, 8, 0, 4, 0, 1, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.waitControl.current00 === x.base && x.control.cursorOffset(x.base, x.waitControl.next04!) === 4 &&
      x.waitControl.wait14 === 4 && x.waitControl.finished1a === 0 && x.waitControl.event1e === 7 &&
      x.clocks.elapsed08 === 9 && x.aobj.frame === 4 && x.stream.target08 === 6 && x.pose.translation.x === 18,
    'byte-backed parser first runs actual packed animation then installs the signed wait without clearing event');
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.wait14 === 2 && x.waitControl.event1e === 0 &&
      x.clocks.elapsed08 === 9 && x.stream.target08 === 6,
    'parsed countdown waits without animation before reaching its real next cursor');
    check(x.control.update(x.actor, 2) === 0 && x.control.cursorOffset(x.base, x.waitControl.current00!) === 4 &&
      x.control.cursorOffset(x.base, x.waitControl.next04!) === 8 && x.waitControl.wait14 === 0 &&
      x.waitControl.finished1a === 0 && x.clocks.elapsed08 === 11 && x.stream.previous0c === 6 && x.stream.target08 === 6,
    'met non-stop countdown parses exactly one next record, including real fallback, without immediately finishing it');
    const callbacks = x.receiverTracks.length;
    check(x.control.update(x.actor, 2) === 1 && x.waitControl.finished1a === 1 && x.clocks.elapsed08 === 11 &&
      x.receiverTracks.length === callbacks && x.waitControl.next04 === x.control.cursorAt(x.base, 8),
    'final stop at buffer end needs no readable next opcode and completes without replay');
    check(x.control.getPartBinding(x.actor, 0).wait14 === 99 && x.control.getPartBinding(x.actor, 0).event1e === 7 &&
      x.wait.getStreamPart(x.actor, 0).target08 === 77, 'byte-record continuation leaves other parts untouched');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0, 0, 0, 10, 0, 1, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.current00 === x.base && x.clocks.elapsed08 === 11,
      'parsed ordinary wait uses live elapsed9 and performs actual unmet continuation');
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.current00 === x.control.cursorAt(x.base, 4) &&
      x.clocks.elapsed08 === 13 && x.waitControl.finished1a === 0 && x.stream.target08 === 6,
    'ordinary threshold next observes elapsed11 and parses one record through shared actual target runtime');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 13,
      'new stop wait is evaluated only by the following actor update');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0, 1, 255, 255])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    check(x.waitControl.wait14 === -1 && x.part.complete2e === 1 && x.control.update(x.actor, 2) === 1 &&
      x.clocks.elapsed08 === 9 && x.pose.translation.x === 18,
    'signed BE16 wait -1 consumes actual packed completion rather than an authored float or synthetic clock');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0])); x.run();
    rejects(() => x.control.parseWaitRecord(x.actor, 2, x.base), 'out of bounds');
    check(x.waitControl.current00 === x.base && x.waitControl.next04 === x.control.cursorAt(x.base, 4) &&
      x.waitControl.wait14 === 99 && x.waitControl.finished1a === 1 && x.waitControl.event1e === 7 &&
      x.clocks.elapsed08 === 9 && x.aobj.frame === 4 && x.stream.target08 === 6 && x.pose.translation.x === 18,
    'truncated wait preserves actual playback and current/next stores, with later control fields unchanged');
  }
  {
    const x = parsedControlFixture(Uint8Array.from([0, 8, 0, 2, 2, 0, 0, 0])); x.run();
    x.control.parseWaitRecord(x.actor, 2, x.base);
    rejects(() => x.control.update(x.actor, 2), 'unsupported zz_004c050_ opcode');
    check(x.waitControl.current00 === x.base && x.waitControl.wait14 === 0 && x.waitControl.finished1a === 0 &&
      x.waitControl.event1e === 0 && x.clocks.elapsed08 === 9 && x.stream.target08 === 6,
    'reached nonzero opcode refuses before another fallback but keeps preceding countdown/event writes');
  }
  for (const [flags, threshold] of [[3, 3], [3, -0.5], [5, 100]]) {
    const x = controlFixture(flags!, threshold!); x.run();
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.finished1a === 0 &&
      x.clocks.elapsed08 === 9 && x.part.frame0c === 4 && x.aobj.frame === 4 &&
      x.stream.target08 === 6 && x.pose.translation.x === 18 && x.waitControl.wait14 === threshold,
    'relative and percentage waits use actual pre-step frame2/duration3, then drive packed playback and target production');
    const callbacks = x.receiverTracks.length;
    check(x.control.update(x.actor, 2) === 1 && x.waitControl.finished1a === 1 &&
      x.clocks.elapsed08 === 9 && x.aobj.frame === 4 && x.stream.target08 === 6 &&
      x.receiverTracks.length === callbacks && x.waitControl.wait14 === threshold,
    'next relative/percentage predicate finishes from actual frame4 without replay or changing authored wait');
  }
  {
    const x = controlFixture(3, -1); x.run();
    check(x.control.update(x.actor, 2) === 1 && x.waitControl.wait14 === -1 && x.waitControl.finished1a === 1 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2 && x.stream.target08 === 78,
    'negative relative wait derives threshold duration3 minus1 and finishes at actual frame2 without playback');
  }
  {
    const x = controlFixture(4, 50); x.run();
    rejects(() => x.control.update(x.actor, 2), '4c050');
    check(x.waitControl.event1e === 0 && x.waitControl.finished1a === 0 && x.waitControl.wait14 === 50 &&
      x.aobj.frame === 2 && x.clocks.elapsed08 === 7 && x.stream.target08 === 78,
    'met percentage non-stop wait preserves source state at the unimplemented command boundary');
  }
  {
    const x = controlFixture(5, 100, 0); x.run();
    rejects(() => x.control.update(x.actor, 2), 'GQR5:');
    check(x.waitControl.event1e === 0 && x.waitControl.finished1a === 0 && x.clocks.elapsed08 === 7 &&
      x.aobj.frame === 2 && x.stream.target08 === 78,
    'unsupported selected numeric profile refuses before actual animation or target effects');
  }
  {
    const x = controlFixture(1, 8); x.run();
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.event1e === 0 && x.waitControl.finished1a === 0 &&
      x.stream.previous0c === 78 && x.stream.target08 === 6 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 4 && x.part.complete2e === 1 && x.pose.translation.x === 18,
    'source actor wait uses pre-dispatch elapsed7, then actual packed playback produces elapsed9/frame4/target6');
    const callbacks = x.receiverTracks.length;
    check(x.control.update(x.actor, 2) === 1 && x.waitControl.finished1a === 1 &&
      x.stream.previous0c === 78 && x.stream.target08 === 6 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 4 && x.receiverTracks.length === callbacks,
    'next source wait observes elapsed9 above threshold8 and finishes without another animation step, despite frame4 below threshold');
    check(x.control.update(x.actor, 2) === 1 && x.clocks.elapsed08 === 9 && x.aobj.frame === 4 &&
      x.receiverTracks.length === callbacks, 'already-finished non-linked part remains finished without replay');
  }
  {
    const x = controlFixture(1, -1); x.run(); x.aobj.flags |= AOBJ_LOOP; x.part.duration24 = 3;
    check(x.control.update(x.actor, 2) === 0 && x.part.complete2e === 0 && x.part.segment2d === 1 &&
      x.stream.accumulator10 === 5 && x.stream.target08 === 6 && x.aobj.frame === 1 && x.pose.translation.x === 12,
    'negative stop wait initially unmet then actual wrapped playback updates shared segment and accumulated target');
    const callbacks = x.receiverTracks.length;
    check(x.control.update(x.actor, 2) === 1 && x.waitControl.finished1a === 1 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 1 && x.stream.accumulator10 === 5 && x.receiverTracks.length === callbacks,
    'next negative stop wait sees positive actual segment and finishes without a second wrap');
  }
  {
    const x = controlFixture(15, 3.5); x.run();
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.wait14 === 1.5 && x.clocks.elapsed08 === 7 &&
      x.aobj.frame === 2 && x.stream.target08 === 78 && x.stream.previous0c === -3,
    'fractional countdown takes priority over unsupported predicate bits and skips actual animation/target updates');
    check(x.control.update(x.actor, 2) === 1 && Object.is(x.waitControl.wait14, 0) && x.waitControl.finished1a === 1 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2 && x.stream.target08 === 78,
    'countdown clamps negative result to positive zero and finishes stop wait without playback');
  }
  {
    const x = controlFixture(8, 1); x.run();
    rejects(() => x.control.update(x.actor, 2), '4c050');
    check(x.waitControl.event1e === 0 && Object.is(x.waitControl.wait14, 0) && x.waitControl.finished1a === 0 &&
      x.clocks.elapsed08 === 7 && x.aobj.frame === 2 && x.stream.target08 === 78,
    'met non-stop countdown preserves subtraction/clamp and event clear at the explicit command execution boundary');
  }
  {
    const x = controlFixture(0, -1); x.run();
    check(x.control.update(x.actor, 2) === 0 && x.part.complete2e === 1 && x.stream.target08 === 6,
      'negative non-stop wait runs actual playback while source completion is not yet positive');
    rejects(() => x.control.update(x.actor, 2), '4c050');
    check(x.waitControl.finished1a === 0 && x.clocks.elapsed08 === 9 && x.aobj.frame === 4 &&
      x.stream.target08 === 6 && x.stream.previous0c === 78,
    'next positive completion reaches command boundary without fabricating a finished flag or replay');
  }
  {
    const x = controlFixture(2, 8); x.run();
    x.control.getActorBinding(x.actor).blockedMask1d9a = 2; x.waitControl.wait14 = NaN; x.waitControl.finished1a = 1;
    check(x.control.update(x.actor, 2) === 0 && x.waitControl.event1e === 0 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 4 && x.part.complete2e === 1 && x.pose.translation.x === 18 &&
      x.stream.target08 === 78 && x.stream.previous0c === -3,
    'source blocked route precedes finished/predicate branches and performs only actual animation, not target continuation');
  }
  for (const accumulator of [0, 2]) {
    const x = waitFixture(accumulator); x.run(); x.part.frame0c = 100;
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 78 && x.stream.target08 === accumulator + 4 && x.stream.accumulator10 === accumulator &&
      x.part.frame0c === 4 && x.aobj.frame === 4 && x.part.complete2e === 1 && x.pose.translation.x === 18 &&
      x.wait.getStreamPart(x.actor, 0).target08 === 77 && x.wait.getStreamPart(x.actor, 0).previous0c === -3,
    'part1 source target1cfc comes from actual packed playback plus accumulator, after old target snapshot, ignoring dispatcher completion');
    // Explicit comparison bridge only: the legacy consumer still calls its
    // existing tick/start interpreter. This does not wire source ownership or
    // claim faithful legacy wait predicates. Its inactive bank has no commands.
    const legacy = createRomActor();
    Object.assign(legacy.parts[1]!, {group: 0x81, slot: 0, prevTarget: x.stream.target08, frameClock: 10000});
    check(updateReactionStream(legacy, 0x81, 0) === (accumulator === 0 ? 'continued' : 'restarted'),
      'explicit bridge proves newly produced source1cfc crosses verified reaction threshold5 independently of synthetic frameClock');
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === accumulator + 4 && x.stream.target08 === accumulator + 4 &&
      x.clocks.elapsed08 === 11 && x.part.frame0c === 4,
    'continued entered branch captures stopped frame and retains accumulator rather than accumulating provisional frame');
  }
  for (const duration of [0, 3, -3]) {
    const x = waitFixture(2); x.run(); x.aobj.flags |= AOBJ_LOOP; x.part.duration24 = duration;
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 78 && x.stream.target08 === 3 + duration && x.stream.accumulator10 === 2 + duration &&
      x.aobj.frame === 1 && x.part.frame0c === 1 && x.part.segment2d === 1 && x.part.complete2e === (duration <= 1 ? 1 : 0) &&
      x.pose.translation.x === 12 && x.clocks.elapsed08 === 9,
    'actual wrapped playback adds signed duration once, then uses captured frame for source target regardless of completion');
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 3 + duration && x.stream.target08 === 2 + 2 * duration &&
      x.stream.accumulator10 === 2 + 2 * duration && x.aobj.frame === 0 && x.part.segment2d === 1 &&
      x.pose.translation.x === 10 && x.clocks.elapsed08 === 11,
    'a second real wrap accumulates another duration after stop/request/replay');
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 2 + 2 * duration && x.stream.target08 === 4 + 2 * duration &&
      x.stream.accumulator10 === 2 + 2 * duration && x.aobj.frame === 2 && x.part.segment2d === 0 &&
      x.pose.translation.x === 14 && x.clocks.elapsed08 === 13,
    'the next non-wrapping playback retains accumulated duration and uses the newly captured frame');
  }
  {
    const x = waitFixture(2); x.run(); x.aobj.flags |= AOBJ_LOOP; x.part.duration24 = 3;
    x.mapping.getActor(x.actor).timestep1dc8 = 8;
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 78 && x.stream.accumulator10 === 5 && x.stream.target08 === 6 &&
      x.aobj.frame === 1 && x.part.segment2d === 1 && x.clocks.elapsed08 === 15 && x.pose.translation.x === 12,
    'one live wrapped flag adds one duration even when actual AObj step crosses several loop lengths');
  }
  for (const field of ['accumulator10', 'target08'] as const) {
    const x = waitFixture(2); x.run(); x.aobj.flags |= AOBJ_LOOP; x.part.duration24 = 3;
    Object.defineProperty(x.stream, field, {writable: false});
    rejects(() => x.wait.continueUnmetNonCountdownWait(x.actor, 1), `${field}: non-writable`);
    check(x.stream.previous0c === 78 && x.stream.target08 === 78 &&
      x.stream.accumulator10 === (field === 'accumulator10' ? 2 : 5) && x.aobj.frame === 1 &&
      x.part.frame0c === 1 && x.part.segment2d === 1 && x.pose.translation.x === 12 && x.clocks.elapsed08 === 9,
    'real wrapped replay survives later store refusal, retaining the accumulator only if its store succeeded');
  }
  for (const gate of ['readiness', 'freeze'] as const) {
    const x = waitFixture(2); x.run(); x.part.duration24 = NaN;
    const gates = x.dispatch.getActorBinding(x.actor);
    if (gate === 'readiness') gates.family1d88 = null;
    else {gates.marker578 = 1; gates.marker1db3 = 1;}
    x.wait.continueUnmetNonCountdownWait(x.actor, 1);
    check(x.stream.previous0c === 78 && x.stream.target08 === 4 && x.clocks.elapsed08 === 7 && x.part.frame0c === 2 &&
      x.aobj.frame === 2 && x.part.complete2e === 0 && x.pose.translation.x === -1,
    'readiness/freeze dispatcher return does not gate source target addition or consume unused duration on zero segment');
  }
  {
    const x = waitFixture(); x.run(); Object.defineProperty(x.stream, 'target08', {writable: false});
    rejects(() => x.wait.continueUnmetNonCountdownWait(x.actor, 1), 'target08');
    check(x.stream.previous0c === 78 && x.stream.target08 === 78 && x.aobj.frame === 4 &&
      x.part.frame0c === 4 && x.part.complete2e === 1 && x.pose.translation.x === 18,
    'readonly target refuses only at final store after old-target copy and real playback');
  }
  {
    const x = waitFixture(); x.run(); x.fobjs.getNode(x.nodes[3]!).track13 = 11;
    rejects(() => x.wait.continueUnmetNonCountdownWait(x.actor, 1), 'unsupported scalar track');
    check(x.stream.previous0c === 78 && x.stream.target08 === 78 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 4 && x.part.complete2e === 0 && x.pose.translation.x === -1,
    'actual receiver failure retains old-target snapshot and dispatch prefix, never synthesizing source target');
  }
  {
    const x = dispatchFixture(); x.run(); x.part.frame0c = 100;
    check(x.dispatch.updatePart(x.actor, 0) === 1 && x.clocks.previous10 === 7 && x.clocks.previous14 === 100 &&
      x.clocks.elapsed08 === 9 && x.part.frame0c === 4 && x.aobj.frame === 4 && x.part.complete2e === 1 &&
      x.pose.translation.x === 18 && x.pose.translation.y === 28 && x.pose.translation.z === 38 &&
      x.joints.endCallbacks.counts.stopped === 5,
    'mode0 dispatch snapshots entry clocks, then actual packed playback replaces provisional frame102 with real AObj frame4/completion');
    const callbacks = x.receiverTracks.length; x.pose.translation.x = -77;
    check(x.dispatch.updatePart(x.actor, 0) === 1 && x.clocks.elapsed08 === 11 && x.clocks.previous10 === 9 &&
      x.clocks.previous14 === 4 && x.part.frame0c === 4 && x.aobj.frame === 4 && x.pose.translation.x === 18 &&
      x.receiverTracks.length === callbacks && x.joints.endCallbacks.counts.stopped === 5,
    'completed mode0 still advances elapsed and captures actual stopped pose without advancing decoder or using provisional frame6');
  }
  {
    const x = dispatchFixture(); x.run(); x.aobj.flags |= AOBJ_LOOP; x.part.frame0c = 100;
    // Explicit finite fixture rewind/end were installed by the real descriptor
    // continuation. This does not exercise the unsupported signed rewind setup.
    check(x.dispatch.updatePart(x.actor, 0) === 0 && x.aobj.frame === 1 && x.part.frame0c === 1 &&
      x.part.segment2d === 1 && x.part.complete2e === 0 && x.clocks.previous14 === 100 && x.clocks.elapsed08 === 9 &&
      x.pose.translation.x === 12 && x.pose.translation.y === 22 && x.pose.translation.z === 32,
    'mode0 dispatch consumes actual FObj stop/request/rewind playback and WRAPPED feedback, not an increment-only clock');
    check(x.dispatch.updatePart(x.actor, 0) === 0 && x.aobj.frame === 0 && x.part.frame0c === 0 &&
      x.part.segment2d === 1 && x.pose.translation.x === 10 && x.clocks.previous14 === 1 && x.clocks.elapsed08 === 11,
    'repeated real rollover produces captured frame0 while independent elapsed continues');
  }
  {
    const x = dispatchFixture(); x.run(); x.joints.getBinding(x.joint).aobj7c = null;
    x.part.frame0c = 100; x.part.complete2e = 255;
    check(x.dispatch.updatePart(x.actor, 0) === -1 && x.part.frame0c === 102 && x.clocks.elapsed08 === 9 &&
      x.aobj.frame === 2 && x.pose.translation.x === 14 && x.part.segment2d === 0,
    'null actual AObj leaves provisional mode0 frame, captures existing geometry and returns signed live completion');
  }
  {
    const x = dispatchFixture(); x.run(); x.mapping.getPartBinding(x.partId).descriptor00 = null;
    check(x.dispatch.updatePart(x.actor, 0) === 1 && x.part.frame0c === 4 && x.aobj.frame === 2 &&
      x.part.complete2e === 1 && x.pose.translation.x === -1 && x.clocks.elapsed08 === 9,
    'actual null-part-descriptor path latches completion without decoder or pose work');
  }
  {
    const x = dispatchFixture(); x.run();
    x.fobjs.getNode(x.nodes[3]!).track13 = 11;
    rejects(() => x.dispatch.updatePart(x.actor, 0), 'unsupported scalar track');
    check(x.clocks.previous10 === 7 && x.clocks.previous14 === 2 && x.clocks.elapsed08 === 9 &&
      x.part.frame0c === 4 && x.aobj.frame === 4 && x.part.complete2e === 0 && x.pose.translation.x === -1,
    'late real receiver failure preserves dispatcher clocks and actual AObj advance, never synthesizing successful feedback');
  }
  {
    const x = fixture(); Object.defineProperty(x.setup.getPartBinding(x.partId), 'rewind26', {writable: false});
    x.run();
    const joint = x.joints.getJoint(x.joint);
    check(x.aobj.flags === 0 && x.aobj.frame === 2 && x.aobj.rewind === 0 && x.aobj.rate === 2 &&
      x.part.duration24 === 3 && x.part.frame0c === 2 && x.part.segment2d === 0 && x.part.complete2e === 0,
    'real non-loop tail clears LOOP, keeps rewind, writes duration, requests frame, installs actor rate and clears segment');
    check(x.receiverTracks.join() === '1,2,3,5,6,7' && joint.rotation1c === 0 && joint.rotation20 === 0 &&
      joint.rotation24 === 0 && joint.translation38 === 14 && joint.translation3c === 24 && joint.translation40 === 34,
    'actual attached descriptor streams execute once after request, replacing rotations and translation');
    check(x.requestCalls === 1 && x.joints.endCallbacks.counts.running === 4 &&
      x.joints.endCallbacks.counts.stopped === 4 && x.endCalls === 0 && x.pose.translation.x === -1 && x.pose.quaternion.w === 7,
    'setup tail performs single-joint interpretation but no pose capture or global completion work');
    x.mapping.animatePart(x.actor, 0, 0, 0, 2);
    check(x.aobj.frame === 4 && (x.aobj.flags & AOBJ_STOPPED) !== 0 && x.pose.translation.x === 18 &&
      x.pose.translation.y === 28 && x.pose.translation.z === 38 && x.pose.quaternion.w === 1 && x.part.frame0c === 4 &&
      x.part.complete2e === 1 && x.joints.endCallbacks.counts.running === 4 && x.joints.endCallbacks.counts.stopped === 5 && x.endCalls === 0,
    'existing actual actor continuation consumes setup duration/rate and produces mapped pose/frame/completion');
  }
  {
    const x = fixture(); x.setup.getPartBinding(x.partId).loop2c = 1; x.aobj.flags = AOBJ_STOPPED;
    rejects(x.run, '804370f8');
    check(x.aobj.flags === (AOBJ_STOPPED | AOBJ_LOOP) && x.aobj.rewind === 0 && x.aobj.frame === 99 &&
      x.part.duration24 === 99 && x.part.segment2d === 9 && x.requestCalls === 0 && x.receiverTracks.length === 0 &&
      x.fobjs.getNode(x.nodes[0]!).cursor04 === null,
    'unverified loop conversion preserves source LOOP prefix but never invents rewind/request/playback');
  }
  {
    const x = fixture(); x.fobjs.getNode(x.nodes[5]!).track13 = 8;
    rejects(x.run, 'missing');
    check(x.aobj.flags === (AOBJ_STOPPED | AOBJ_LOOP) && x.part.duration24 === 99 && x.receiverTracks.length === 0,
      'missing required translation track refuses before fallback or setup effects');
  }
  {
    const x = fixture(); Object.defineProperty(x.part, 'segment2d', {writable: false});
    rejects(x.run, 'segment2d');
    check(x.aobj.frame === 2 && x.aobj.flags === 0 && x.part.duration24 === 3 && x.part.segment2d === 9 &&
      x.joints.getJoint(x.joint).translation38 === 14 && x.joints.endCallbacks.counts.running === 4 && x.receiverTracks.length === 6,
    'late segment-store refusal retains actual requests, scalar playback and accounting');
  }
  {
    const x = fixture(); x.fobjs.getNode(x.nodes[5]!).length0c = 1;
    rejects(x.run, 'truncated stream');
    check(x.part.duration24 === 3 && x.part.segment2d === 9 && x.aobj.frame === 2 && x.aobj.rate === 2 &&
      (x.aobj.flags & AOBJ_REQUEST) === 0 && x.joints.getJoint(x.joint).translation38 === 14 &&
      x.joints.getJoint(x.joint).translation3c === 24 && x.joints.getJoint(x.joint).translation40 === -30 &&
      x.joints.endCallbacks.counts.running === 3 && x.endCalls === 0,
    'late actual decoder refusal retains setup and earlier receivers, but no current AObj count or final segment store');
  }
  {
    const x = fixture(); x.run();
    const oldHeaders = x.nodes.map(id => x.fobjs.getNode(id));
    // Replace the real played list using the same descriptor-backed streams.
    // This tests release and fresh decoder state without inventing asset ownership.
    check(x.aobjLoader.continueAllocatedLoad(x.aobjId, x.aobjDescriptor) === x.aobjId, 'replace on the same actual clock');
    for (let i = 0; i < x.nodes.length; i++) {
      rejects(() => x.fobjs.getNode(x.nodes[i]!), 'unknown/non-owned node identity');
      rejects(() => x.fobjs.validateNode(oldHeaders[i]!), 'non-owned header');
    }
    const fresh: symbol[] = []; let current = x.aobj.fobjs;
    while (current !== null) {fresh.push(current); current = x.fobjs.getNode(current).next00;}
    check(fresh.length === 6 && fresh.every(id => !x.nodes.includes(id)) &&
      fresh.every(id => x.fobjs.getNode(id).cursor04 === null), 'replacement owns fresh unrequested nodes');
    x.receiverTracks.length = 0;
    x.part.frame0c = 1; x.run();
    check(x.receiverTracks.join() === '1,2,3,5,6,7' && x.aobj.frame === 1 &&
      x.joints.getJoint(x.joint).translation38 === 12 && x.joints.getJoint(x.joint).translation3c === 22 &&
      x.joints.getJoint(x.joint).translation40 === 32, 'replacement reuses retained packed streams through real setup playback');
    x.mapping.animatePart(x.actor, 0, 0, 0, 2);
    check(x.aobj.frame === 3 && x.pose.translation.x === 16 && x.pose.translation.y === 26 &&
      x.pose.translation.z === 36 && x.part.complete2e === 1 && x.part.duration24 === 3,
      'replacement clock feeds mapped pose and completion');
  }
  for (const [poseBank, scale] of [[0, 0.5], [1, -2]] as const) {
    const x = fixture();
    x.mapping.bindScaleTable(x.actor, [scale, 3]);
    x.mapping.getPartBinding(x.partId).scaleIndex32 = 0;
    x.run(); // Real descriptor-backed setup/request before mapped capture/scaling.
    x.mapping.animatePart(x.actor, 0, poseBank, 0, 2);
    const output = x.feedback.getPose(x.mapping.getLayout(x.actor).poses[poseBank]![1]!);
    const other = x.feedback.getPose(x.mapping.getLayout(x.actor).poses[poseBank === 0 ? 1 : 0]![1]!);
    check(output.translation.x === 18 * scale && output.translation.y === 28 * scale &&
      output.translation.z === 38 * scale && output.quaternion.w === 1 && other.translation.x === -1,
      'actual descriptor-loaded playback scales only selected captured translation bank');
    check(x.joints.getJoint(x.joint).translation38 === 18 && x.joints.getJoint(x.joint).translation3c === 28 &&
      x.joints.getJoint(x.joint).translation40 === 38 && x.aobj.frame === 4 && x.part.frame0c === 4 &&
      x.part.complete2e === 1 && x.part.duration24 === 3,
      'translation scaling preserves source joint, actual clock and completion feedback');
    x.mapping.getScaleTable(x.actor)[0] = 2;
    x.part.frame0c = 0; x.run();
    x.mapping.animatePart(x.actor, 0, poseBank, 0, 2);
    check(output.translation.x === 28 && output.translation.y === 48 && output.translation.z === 68 &&
      x.aobj.frame === 2 && x.part.frame0c === 2 && x.part.complete2e === 1,
      'subsequent request/playback reads changed actual scale table without double-scaling prior pose');
  }
  runAttributeHydratedControlTests();
  runStatusHydratedControlTests();
  runGaugeScaleHydratedControlTests();
  runTickPrefixHydratedControlTests();
  console.log('[attached-setup-animation] PASS: owned allocation/removal and single-JObj replacement, post-allocation descriptors, explicit non-loop setup, actual playback/feedback, wrapped targets and actor-level source waits; byte-backed waits, opcode10 accumulator/mirror commands and source bank start/reset; actual archive name/address selection with explicit decoded inputs, shared descriptor-bank metadata and bounded non-null ready mode0 opcode01 setup with actual pose-pool lookup and mapping capture, real part1 movement follow-up, bounded original-byte DAT hydration and null-descriptor display attachment preserving actual shared display playback owners; bounded DAT joint transform topology consumed by actual setup and dirty propagation; explicit source matrix helper, bounded first-pass traversal and normal damping/corrected traversal, selector3 adjusted-Y correction and selector2 no-query descriptor scans with actual linked-actor matrix copying and retained shared-matrix movement consumption and explicit source transform-history snapshots around real wait/setup/movement/matrix calls; genuine bounded source terrain grid/triangle queries, explicit correction entries, real positive-list normal alignment, bounded folded and positive-sine primary two-bone placement with special topology and retained linked-matrix consumers; unsupported tagged source archive parsing, setup rewind conversion, other command handlers, production ownership, general quaternion backend and original replay');
}

/** Actual59068 prefix on the SAME supplied DAT/setup/status/gauge owner graph.
 * The distinct3D/XZ raw values are explicit decoded pre59068 inputs, not a
 * source sqrt implementation, capture, target lookup or production scheduler. */
function tickPrefixHydratedControlFixture(withByte598 = true) {
  const x = gaugeScaleHydratedControlFixture();
  const sourceActor = Object.assign(x.sourceActor, {targetDistance760: -760, horizontalDistance764: -764});
  sourceActor.controlWord = 0x100040; sourceActor.supportContact1db = 0;
  const prefix = createSourceActorTickPrefixRuntime({world: x.world, gauges: x.gauges});
  prefix.bindActor(x.actor, x.host, withByte598 ? {byte598: 7} : {});
  return Object.assign(x, {sourceActor, prefix, prefixState: prefix.getActorBinding(x.actor),
    runRawPrefix: (epoch: number, targetDistance760: number, horizontalDistance764: number) =>
      prefix.ingestRawDistancesAndRun(x.actor, epoch, {boundary: 'externally-decoded-pre59068-raw',
        targetDistance760, horizontalDistance764})});
}
type TickPrefixFixture = ReturnType<typeof tickPrefixHydratedControlFixture>;
/** Only the reached distance/scale/tier/control stores may change here. The
 * real graph's other records, identities and explicit-call cadence stay put. */
function retainTickPrefixUnrelatedOwners(x: TickPrefixFixture): () => void {
  const aobj = x.joints.getBinding(x.joint).aobj7c!;
  const rows: {record: object; omitted?: readonly string[]}[] = [
    {record: x.sourceActor, omitted: ['targetDistance760', 'horizontalDistance764', 'modelScale', 'collisionScale', 'controlWord']},
    {record: x.host, omitted: ['downGauge']}, {record: x.tier, omitted: ['timerFrames']},
    {record: x.gaugeState, omitted: ['fieldC4']}, {record: x.prefixState, omitted: ['byte598']},
    {record: x.scaleVector, omitted: ['x', 'y', 'z']},
    ...[x.header, x.header.offset1dbc, x.header.adjusted1d54, x.header.preRotation1d64,
      x.normalState, x.historyState, x.historyState.rotation76, x.historyState.preRotation1d6a,
      x.historyState.aimOrigin524, x.sourceActor.pos, x.sourceActor.savedGroundPos,
      x.sourceActor.targetCache5e8, x.sourceActor.aimOrigin518, x.sourceActor.actionSpeedRows,
      ...x.sourceActor.parts, x.targetActor, x.targetHeader, x.targetHeader.scale58,
      x.targetPose, x.targetPose.translation, x.targetPose.quaternion, x.clocks, x.part,
      x.stream, x.waitControl, x.control.getActorBinding(x.actor), x.start, x.statusState,
      ...x.cells, ...x.ammoSlots, x.attributeState, x.parameter, x.scalarDescriptor,
      x.movementState, x.ready.getActorBinding(x.actor), x.sourceClock,
      x.joints.getBinding(x.joint), x.joints.getJoint(x.joint), x.feedback.getAObj(aobj),
      ...x.worldStorage.matrices8d4.map(id => x.matrices.getMatrix(id)),
      ...[x.worldStorage.copy114, x.worldStorage.copy1aa4, x.worldStorage.scratch].map(id => x.matrices.getMatrix(id)),
      ...x.targetMatrices, ...x.targetCopies].map(record => ({record})),
  ];
  for (const bank of x.mapping.getLayout(x.actor).poses) for (const id of bank) {
    const pose = x.feedback.getPose(id); rows.push(...[pose, pose.translation, pose.quaternion].map(record => ({record})));
  }
  let node = x.feedback.getAObj(aobj).fobjs;
  while (node !== null) {const record = x.fobjs.getNode(node); rows.push({record}); node = record.next00;}
  const saved = rows.map(({record, omitted = []}) => ({record, ownKeys: Reflect.ownKeys(record),
    keys: Reflect.ownKeys(record).filter(key => typeof key !== 'string' || !omitted.includes(key))}))
    .map(row => ({...row, values: row.keys.map(key => Reflect.get(row.record, key))}));
  const requests = x.requestCalls, ends = x.endCalls, callbacks = x.receiverTracks.length, movements = x.movementCallCount();
  return () => check(saved.every(({record, ownKeys, keys, values}) => Reflect.ownKeys(record).length === ownKeys.length &&
    keys.every((key, i) => Object.is(Reflect.get(record, key), values[i]))) &&
    x.requestCalls === requests && x.endCalls === ends && x.receiverTracks.length === callbacks && x.movementCallCount() === movements,
    'bounded59068 retains unrelated DAT/setup/status/attribute/animation/world/linked/history owners and explicit-call cadence');
}
function runTickPrefixHydratedControlTests(): void {
  {
    const x = tickPrefixHydratedControlFixture(); x.host.downGaugeBase = 32;
    const distanceConsumer = new NeoGredMeleeState(x.sourceActor, null);
    check(distanceConsumer.actor === x.sourceActor && distanceConsumer.targetDistance760 === -760 &&
      !Object.prototype.hasOwnProperty.call(distanceConsumer, 'targetDistance760'),
      'existing Neo accessor borrows canonical760 without copying it or dispatching any family action');
    x.host.downResetDelay = 0.25; x.statusState.field7d8 = 0.25; x.snapshot(); x.refreshStatusPrefix();
    // The prior real status call retains the two distinct raw input slots.
    checkAttributeStores(x, [6, 4, 1, 8, 10], 'actual55dcc/status finish before explicit raw59068 ingress');
    check(x.prefix.getActualActor(x.actor) === x.sourceActor && x.prefix.getActualBorg(x.actor) === x.host &&
      x.gauges.getActualActor(x.actor) === x.sourceActor && x.gauges.getActualBorg(x.actor) === x.host &&
      x.world.getActualActor(x.actor) === x.sourceActor && x.status.getActualActor(x.actor) === x.sourceActor &&
      x.host.paramTier === x.tier && isSourceActorTickPrefixClaimedActor(x.sourceActor) &&
      x.sourceActor.targetDistance760 === -760 && x.sourceActor.horizontalDistance764 === -764 &&
      x.host.downGauge === 48 && x.gaugeState.short7dc === -60 && x.tier.timerFrames === 8,
      '59068 claims the same actual actor/Borg/paramTier graph without copying fields or hiding earlier reset calls');
    let retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(40, 64, 20), '59e58'); retained();
    checkScaleStores(x, 2.049999952316284, 'real5bab8 runs after both actual59068 distance divisions');
    check(x.sourceActor.targetDistance760 === 32 && distanceConsumer.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 &&
      x.sourceActor.controlWord === 0x40 && x.prefixState.byte598 === 0 && x.sourceActor.supportContact1db === 0 &&
      x.tier.timerFrames === 7 && x.host.downGauge === 48 && x.gaugeState.short7dc === -60 &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77 && x.pose.translation.y === 27 &&
      x.historyState.previousStepHeight6d4 === 9,
      'distinct3D64/XZ20 divide by oldB4=2 before scale changes; actual67a70 clears control then598 and genuinely returns on zero1db before unsupported59e58');
    retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(40, 640, 200), 'epoch'); retained();
    check(x.sourceActor.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 &&
      x.sourceActor.modelScale === 2.049999952316284 && x.tier.timerFrames === 7 &&
      x.sourceActor.controlWord === 0x40 && x.prefixState.byte598 === 0 && x.host.downGauge === 48,
      'same consumed epoch cannot ingest replacement raw values, divide again, tick750 or repeat scale/contact effects after59e58 refusal');

    // A later explicit source call boundary supplies fresh raw distances. The
    // epoch is a consumed attempt token, not a whole-frame normalized-state flag.
    x.host.downGauge = 99; x.sourceActor.controlWord = 0x100040; x.prefixState.byte598 = 9;
    const before = x.sourceActor.modelScale;
    retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(41, 66, 22), '59e58'); retained();
    checkScaleStores(x, 2.0625, 'next actual5bab8 clamps toB8 and copies all five scale destinations');
    check(x.sourceActor.targetDistance760 === Math.fround(66 / before) &&
      distanceConsumer.targetDistance760 === x.sourceActor.targetDistance760 &&
      x.sourceActor.horizontalDistance764 === Math.fround(22 / before) &&
      x.sourceActor.targetDistance760 !== Math.fround(66 / 2.0625) &&
      x.sourceActor.horizontalDistance764 !== Math.fround(22 / 2.0625) &&
      x.tier.timerFrames === 6 && x.host.downGauge === 49 && x.gaugeState.short7dc === -60 &&
      x.sourceActor.controlWord === 0x40 && x.prefixState.byte598 === 0,
      'fresh raw ingress overwrites both prior normalized slots; both divisions precede real completion/reset49 and actual67a70 clears');
    const distances = [x.sourceActor.targetDistance760, x.sourceActor.horizontalDistance764];
    x.scalarDescriptor.field44 = 64; x.refreshAttributes();
    checkAttributeStores(x, [6.1875, 132, 1.03125, 8.25, 10.3125], 'later explicit55dcc consumes the prefix actual model scale');
    check(x.sourceActor.stepHeight === Math.fround(27 * Math.fround(0.7)) && x.movementCallCount() === 2 &&
      x.worldMatrix[7] === 95 && x.tier.timerFrames === 6,
      'later real4d08c consumes refreshed half-height132 on retained worldY95 without ticking59068');
    x.updateStatus(); x.control.update(x.actor, 2);
    check(x.header.yawOffset6b8 === 0 && x.statusState.field8c8 === 2 && x.pose.translation.y === 33 &&
      x.worldMatrix[7] === 95 && x.tier.timerFrames === 6 && x.movementCallCount() === 2,
      'separate actual status clears yaw and actual wait advances pose; neither is an implicit59068 suffix');
    x.sourceActor.pos.y = 6; x.updateNormal();
    check(x.rootMatrix[0] === 2.0625 && x.rootMatrix[5] === 2.0625 && x.rootMatrix[10] === 2.0625 &&
      x.worldMatrix[3] === 153.625 && x.worldMatrix[7] === 82.3125 && x.worldMatrix[11] === 399 &&
      x.targetMatrices[1]!.every((value, i) => Object.is(value, x.worldMatrix[i])) &&
      x.targetActor.modelScale === 1 && x.targetHeader.scale58.x === 1 && x.historyState.previousStepHeight6d4 === 9,
      'only explicit465fc consumes retained scale vector and copies actual linked matrices, without copying linked model scale or history');
    x.refreshAttributes();
    check(x.sourceActor.stepHeight === 7.21875 && x.movementCallCount() === 3 && x.tier.timerFrames === 6,
      'later real55dcc/4d08c consumes newly retained worldY82.3125 after the bounded prefix');
    const oldAObj = x.joints.getBinding(x.joint).aobj7c; x.begin();
    check(x.joints.getBinding(x.joint).aobj7c !== oldAObj && x.pose.translation.y === 27 &&
      x.sourceActor.stepHeight === 7.21875 && x.worldMatrix[7] === 82.3125 && x.movementCallCount() === 3 &&
      x.tier.timerFrames === 6 && x.historyState.previousStepHeight6d4 === 9,
      'genuine replacement setup consumes retained prefix/matrix output without replaying distance/scale work');
    x.snapshot();
    check(x.historyState.previousStepHeight6d4 === 7.21875 && x.sourceActor.savedGroundPos.y === 6 &&
      x.sourceActor.targetDistance760 === distances[0] && x.sourceActor.horizontalDistance764 === distances[1] &&
      x.tier.timerFrames === 6 && x.prefixState.byte598 === 0,
      'explicit history alone advances previous height while later real consumers retain both canonical distance cells');
  }
  {
    const x = tickPrefixHydratedControlFixture(); x.tier.timerFrames = 1;
    let retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(3, 64, 20), '6817c'); retained();
    check(x.sourceActor.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 &&
      x.tier.timerFrames === 0 && x.tier.tier === 16 && x.tier.deltaAccum === 5 &&
      x.sourceActor.modelScale === 2 && x.scaleVector.x === 2 && x.scaleVector.y === 3 && x.scaleVector.z === 4 &&
      x.sourceActor.collisionScale === -19 && x.gaugeState.fieldC4 === -23 && x.host.downGauge === 7 &&
      x.sourceActor.controlWord === 0x100040 && x.prefixState.byte598 === 7,
      'reached real6817c refusal preserves both normalized distance stores and750 decrement, but no scale or67a70 suffix');
    retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(3, 128, 40), 'epoch'); retained();
    check(x.sourceActor.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 &&
      x.tier.timerFrames === 0 && x.sourceActor.modelScale === 2 && x.sourceActor.controlWord === 0x100040 && x.prefixState.byte598 === 7,
      'partial failure consumes epoch before first store; duplicate cannot replace distances or rerun real5bab8');
  }
  {
    const x = tickPrefixHydratedControlFixture(); x.host.downGaugeBase = 32; x.gaugeState.targetScaleB8 = 2.03125;
    delete x.sourceActor.collisionScale;
    const retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(1, 64, 20), 'collisionScale'); retained();
    check(x.sourceActor.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 &&
      x.tier.timerFrames === 7 && x.sourceActor.modelScale === 2.03125 && x.host.downGauge === 48 &&
      [x.scaleVector.x, x.scaleVector.y, x.scaleVector.z].every(value => value === 2.03125) &&
      x.sourceActor.collisionScale === undefined && x.gaugeState.fieldC4 === -23 &&
      x.sourceActor.controlWord === 0x100040 && x.prefixState.byte598 === 7,
      'late real5bab8 missingC0 refusal retains distance/timer/scale/reset/world-copy prefix without host fallback or67a70');
  }
  for (const fault of ['control', 'byte598', 'missing598', 'contact1db'] as const) {
    const x = tickPrefixHydratedControlFixture(fault !== 'missing598');
    if (fault === 'control') Object.defineProperty(x.sourceActor, 'controlWord', {writable: false});
    else if (fault === 'byte598') Object.defineProperty(x.prefixState, 'byte598', {writable: false});
    else if (fault === 'contact1db') x.sourceActor.supportContact1db = 1;
    const retained = retainTickPrefixUnrelatedOwners(x);
    rejects(() => x.runRawPrefix(2, 64, 20), fault === 'contact1db' ? '1e4' : fault === 'missing598' ? 'byte598' : 'non-writable'); retained();
    checkScaleStores(x, 2.049999952316284, `${fault} refuses only after real distance/tier/scale effects`);
    check(x.sourceActor.targetDistance760 === 32 && x.sourceActor.horizontalDistance764 === 10 && x.tier.timerFrames === 7 &&
      x.sourceActor.controlWord === (fault === 'control' ? 0x100040 : 0x40) &&
      x.prefixState.byte598 === (fault === 'missing598' ? undefined : fault === 'contact1db' ? 0 : 7) &&
      x.sourceActor.supportContact1db === (fault === 'contact1db' ? 1 : 0) &&
      x.worldMatrix[7] === 95 && x.targetMatrices[1]![7] === -77,
      `${fault} retains exact67a70 store order; real nonzero supporting contact refuses missing1e4 owner rather than borrowing the separate collision adapter`);
  }
  console.log('[actor-tick-prefix-composition] PASS: explicit decoded3D760/XZ764 ingress and bounded real59068 prefix on the SAME DAT/setup/status/gauge/world/Borg owners; both divisions before real5bab8, actual750/scale/reset/copies, real67a70 control/598 clears and zero1db return, strict consumed epochs and retained6817c/C0/67a70 failure prefixes; explicit later55dcc/4d08c/wait/matrix/linked/history consumers; always refuses remaining59e58 or earlier unsupported effect, no full tick/raw producer/spawn/production activation');
}
