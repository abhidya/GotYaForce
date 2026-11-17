import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
import {createSourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import {createSourceAttachedJointSetupRuntime} from './attached-joint-setup.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import {createSourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[archive-setup-test] ${why}`);}
function rejects(run: () => unknown, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error || 'success'}`);
}
/** Deliberately real attachment + real missing-track tail refusal. Complete
 * six-track packed execution belongs to the integration fixture, not a fake
 * successful tail here. Unreachable effects explicitly refuse. */
function fixture() {
  const archives = createSourceArchivePublicRuntime(), bytes = new Uint8Array(80), view = new DataView(bytes.buffer);
  view.setUint32(0, 16); view.setUint32(4, 0); view.setUint32(8, 32); view.setUint32(12, 2);
  bytes.set([97, 0, 97, 0, 98, 0], 64);
  const base = archives.createBytes(bytes), stringTable30 = archives.cursorAt(base, 64);
  const archive = archives.createArchive({publicCount0c: 2, data20: base, publicTable28: base, stringTable30});
  const j = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(j);
  const joint = j.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const part = feedback.createPart({frame0c: 0, duration24: -1, segment2d: 9, complete2e: 0, mode2f: 0, mirror30: 0});
  const fobjs = createSourceFObjRuntime(() => {throw Error('unexpected interpreter');});
  const loader = createSourceFObjDescriptorRuntime(fobjs);
  const aDescs = createSourceAllocatedAObjDescriptorRuntime({feedback, fobjs: loader, removal: fobjs});
  const life = createSourceAObjLifecycleRuntime({feedback, fobjs, descriptors: aDescs});
  const order = createSourceJObjTrackOrderRuntime({joints: j, feedback, fobjs: {getFObj(_owner, node) {return fobjs.getNode(node);}}});
  const attachment = createSourceJObjAddAnimationRuntime({joints: j, lifecycle: life, order});
  const aDesc = aDescs.createDescriptor({flags00: 0, end04: 8, fobj08: null, joint0c: null});
  const anim = attachment.createDescriptor({aobj08: aDesc, robj0c: null, flags10: 1});
  const otherAnim = attachment.createDescriptor({aobj08: null, robj0c: null, flags10: 0});
  const unreachable = (): never => {throw Error('unsupported test effect reached');};
  const tail = createSourceAttachedJointSetupRuntime({joints: j, feedback, actors: {getActor: unreachable},
    requests: {requestJoint: unreachable}, fobjs: {getFObj(_owner, node) {return fobjs.getNode(node);}}},
  {interpretAObj: unreachable, animateRObjs: unreachable, animateDObjs: unreachable});
  tail.bindPart(part, {rewind26: 0, loop2c: 0});
  const events: string[] = [];
  const hooks: {name?: () => void; address?: () => void; add?: () => unknown; tail?: () => unknown; archive?: () => void} = {};
  const archiveAdapter = {
    getArchive(key: symbol) {check(this === archiveAdapter, 'archive original receiver'); events.push('archive'); hooks.archive?.(); return archives.getArchive(key);},
    getPublicName(key: symbol, index: number) {check(this === archiveAdapter, 'name original receiver'); events.push('name'); const result = archives.getPublicName(key, index); hooks.name?.(); return result;},
    getPublicAddress(key: symbol, name: symbol | null) {check(this === archiveAdapter, 'address original receiver'); events.push('address'); const result = archives.getPublicAddress(key, name); hooks.address?.(); return result;},
    cursorOffset: archives.cursorOffset,
  };
  const attachmentAdapter = {
    getDescriptor: attachment.getDescriptor,
    addAnimation(target: symbol | null, desc: symbol | null) {check(this === attachmentAdapter, 'attachment original receiver'); events.push(desc === null ? 'add-null' : 'add'); attachment.addAnimation(target, desc); return hooks.add?.() as void;},
  };
  const tailAdapter = {continueAttachedSetupTail(actor: symbol, p: symbol, target: symbol | null) {
    check(this === tailAdapter, 'tail original receiver'); events.push('tail'); tail.continueAttachedSetupTail(actor, p, target); return hooks.tail?.() as void;
  }};
  const actors = createSourceActorJointMappingRuntime(j, feedback,
    {interpretAObj: unreachable, animateRObjs: unreachable, animateDObjs: unreachable},
    {convertEulerToQuaternion: unreachable});
  const actor = actors.createActor({descriptor4b0: null, jointCount1d90: 0, boundary1d91: 0, boundary1d92: 0,
    boundary1d93: 0, jointBank1db4: null, jointBank1db8: null, timestep1dc8: 1},
  {parts: Array.from({length: 2}, () => Array.from({length: 4}, () => actors.createPart(
    {frame0c: 0, duration24: -1, segment2d: 0, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: null, scaleIndex32: 0, jointBank33: 0, poseBuffer35: 0}))), poses: [[], []]});
  const actorHooks: {get?: () => void} = {};
  const actorAdapter = {getActor(key: symbol) {
    check(this === actorAdapter, 'actor original receiver'); actorHooks.get?.(); return actors.getActor(key);
  }};
  const runtime = createSourceArchiveJointSetupRuntime({archives: archiveAdapter, attachment: attachmentAdapter, tail: tailAdapter, actors: actorAdapter});
  const input = {archive0c: archive}, descriptor = runtime.createDescriptor(input), bindingInput = {descriptor04: descriptor};
  runtime.bindPart(part, bindingInput);
  const poseInput = [{translation0c: 10, translation1c: 20, translation2c: 30}, {translation0c: 11, translation1c: 21, translation2c: 31}];
  const poses = runtime.createPoseTable(poseInput), pose = runtime.getPoseTable(poses);
  runtime.bindAddress(base, archives.cursorAt(base, 16), anim);
  runtime.bindAddress(base, archives.cursorAt(base, 32), otherAnim);
  events.length = 0;
  const run = (index = 0) => runtime.continueResolvedArchiveSetup(actor, part, joint, index, poses);
  return {archives, base, archive, j, feedback, joint, part, fobjs, aDescs, aDesc, attachment, anim, otherAnim,
    runtime, actor, actors, actorAdapter, actorHooks, descriptor, poses, pose, input, bindingInput, poseInput, events, hooks, archiveAdapter, attachmentAdapter, run};
}
export function runArchiveJointSetupSelfTest(): void {
  {const x = fixture(); const p = Symbol('null descriptor part'); x.runtime.bindPart(p, {descriptor04: null});
    rejects(() => x.runtime.continueResolvedArchiveSetup(x.actor, p, null, 0, x.poses), 'descriptor04: owned symbol');
    check(x.events.length === 0, 'null descriptor binding refuses only when dereferenced');}
  const block = () => Array.from({length: 65}, () => ({translation0c: 1, translation1c: 2, translation2c: 3}));
  {const x = fixture(); const first = x.runtime.createPoseTable(block()), second = x.runtime.createPoseTable(block());
    const tables = [first, second]; x.runtime.bindPosePool(tables); tables[0] = Symbol('ignored copied pool input');
    x.runtime.bindActorPoseIndex(x.actor, 0);
    check(Object.isSealed(x.runtime.getActorPoseBinding(x.actor)), 'owned sealed live actor byte');
    x.runtime.getPoseTable(first)[0xc] = NaN;
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'pose+0c');
    x.runtime.getActorPoseBinding(x.actor).poseIndex97 = 1;
    x.actorAdapter.getActor = () => {throw Error('replacement must not run');};
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'missing track fallback');
    check(x.j.getBinding(x.joint).aobj7c !== null, 'live actor byte selects real second slot and real attachment survives tail refusal');
    rejects(() => x.runtime.bindPosePool([second]), 'already bound');
    rejects(() => x.runtime.bindActorPoseIndex(x.actor, 1), 'already bound');
    x.runtime.getActorPoseBinding(x.actor).poseIndex97 = 255;
    rejects(() => x.runtime.setupActorJoint(x.actor, Symbol('unreached'), null, 0), '803ba890');
    x.runtime.getActorPoseBinding(x.actor).poseIndex97 = 2;
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'unowned pose pool region');
    x.runtime.getActorPoseBinding(x.actor).poseIndex97 = 0;
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 64), 'out-of-count');
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 65), 'crosses owned pool slot');
    x.runtime.getActorPoseBinding(x.actor).poseIndex97 = 256;
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'byte required');
  }
  {const x = fixture(); rejects(() => x.runtime.bindPosePool([x.poses]), 'complete 65-matrix');
    rejects(() => x.runtime.bindPosePool(new Array(129)), 'signed positive slots');
    rejects(() => x.runtime.bindPosePool([Symbol('foreign')]), 'unknown/non-owned pose table');
    rejects(() => x.runtime.bindActorPoseIndex(Symbol('foreign'), 0), 'unknown');
    x.runtime.bindActorPoseIndex(x.actor, 0);
    rejects(() => x.runtime.setupActorJoint(x.actor, Symbol('unreached'), null, 0), 'unowned pose pool region');
    x.runtime.bindPosePool([x.runtime.createPoseTable(block())]);
    x.actorHooks.get = () => {rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'reentry');};
    rejects(() => x.runtime.setupActorJoint(x.actor, x.part, x.joint, 0), 'reentry caught');
    check(x.events.length === 0, 'prefix reentry refuses before archive effects');
  }
  {const x = fixture(); x.archives.getArchive(x.archive).publicCount0c = NaN; x.pose[0xc] = NaN;
    rejects(x.run, 'publicCount0c'); check(x.events.join() === 'archive', 'invalid count precedes invalid pose');}
  {const x = fixture(); const empty = x.archives.createArchive({publicCount0c: 0, data20: null, publicTable28: null, stringTable30: null});
    x.hooks.archive = () => {x.runtime.getDescriptor(x.descriptor).archive0c = empty;};
    rejects(x.run, 'non-null attached AObj');
    check(x.events.join() === 'archive,name,address,add-null,tail', 'name uses saved first archive, address reloads changed descriptor');}

  {const x = fixture(); x.input.archive0c = Symbol('ignored'); x.bindingInput.descriptor04 = Symbol('ignored'); x.poseInput[0]!.translation0c = NaN;
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.runtime.getDescriptor(x.descriptor)) && Object.isSealed(x.pose), 'copied sealed ownership');
    rejects(() => x.run(1), 'missing track fallback'); const loaded = x.j.getBinding(x.joint).aobj7c!;
    check(x.feedback.getAObj(loaded).end === 8 && x.j.getJoint(x.joint).flags14 === 0x48, 'duplicate name selects actual first descriptor, actual allocation/flags survive tail refusal');
    check(x.events.join() === 'archive,name,address,add,tail', 'ordered real lookup then attachment then tail');
    rejects(() => x.run(), 'missing track fallback'); rejects(() => x.feedback.getAObj(loaded), 'unknown');
    check(x.j.getBinding(x.joint).aobj7c !== loaded, 'actual replacement removes old AObj');
  }
  for (const byte of [0xc, 0x1c, 0x2c]) {
    const x = fixture(); x.archives.getArchive(x.archive).publicCount0c = 0; x.pose[byte] = NaN;
    rejects(x.run, `pose+${byte.toString(16).padStart(2, '0')}`); check(x.events.join() === 'archive', 'count snapshot precedes all translation loads and branch');
  }
  {const x = fixture(); x.archives.getArchive(x.archive).publicCount0c = 0;
    rejects(x.run, 'out-of-count'); check(x.events.join() === 'archive' && x.j.getBinding(x.joint).aobj7c === null, 'unsupported reset refuses before lookup/attachment');}
  {const x = fixture(); rejects(() => x.run(0x10000000), 'out-of-count');
    check(x.events.join() === 'archive', 'PPC multiplication wraps to actual owned pose before unsigned count guard');
    rejects(() => x.runtime.createPoseTable(new Array(349526)), 'host budget');}
  {const x = fixture(); x.archives.getArchive(x.archive).publicCount0c = 0xffffffff;
    rejects(() => x.run(0x80000000), 'owned byte cursor');
    check(x.events.join() === 'archive,name,address', 'wrapped high-bit index reaches signed-name null and real nonempty address comparison refusal');}
  {const x = fixture(); rejects(() => x.run(2), '108: own data'); check(x.events.join() === 'archive', 'count snapshot precedes missing pose read and out-of-count branch');}
  {const x = fixture(); for (const key of Object.keys(x.pose)) Object.defineProperty(x.pose, key, {writable: false});
    Object.defineProperty(x.runtime.getPartBinding(x.part), 'descriptor04', {writable: false});
    Object.defineProperty(x.runtime.getDescriptor(x.descriptor), 'archive0c', {writable: false});
    Object.defineProperty(x.archives.getArchive(x.archive), 'publicCount0c', {writable: false});
    rejects(x.run, 'missing track fallback'); check(x.j.getBinding(x.joint).aobj7c !== null, 'read-only consumed operands accepted');}
  {const x = fixture(); const other = x.archives.createArchive({publicCount0c: 0, data20: null, publicTable28: null, stringTable30: null});
    x.hooks.name = () => {x.runtime.getDescriptor(x.descriptor).archive0c = other;};
    rejects(x.run, 'non-null attached AObj'); check(x.events.join() === 'archive,name,address,add-null,tail', 'repeated descriptor/archive load changes real lookup and null forwards');}
  {const x = fixture(); rejects(x.run, 'missing track fallback'); const old = x.j.getBinding(x.joint).aobj7c;
    const other = x.archives.createArchive({publicCount0c: 0, data20: null, publicTable28: null, stringTable30: null});
    x.hooks.name = () => {x.runtime.getDescriptor(x.descriptor).archive0c = other;};
    rejects(x.run, 'missing track fallback'); check(x.j.getBinding(x.joint).aobj7c === old, 'null address preserves old nonnull AObj and reaches real tail scan');}
  {const x = fixture(); rejects(x.run, 'missing track fallback'); const old = x.j.getBinding(x.joint).aobj7c!;
    x.attachment.getDescriptor(x.anim).aobj08 = null;
    rejects(x.run, 'non-null attached AObj'); rejects(() => x.feedback.getAObj(old), 'unknown');
    check(x.j.getBinding(x.joint).aobj7c === null, 'nonnull empty AnimJoint removes old graph before missing-AObj tail refusal');}
  {const x = fixture(); x.hooks.name = () => {x.runtime.getPartBinding(x.part).descriptor04 = Symbol('bad second descriptor');};
    rejects(x.run, 'unknown/non-owned setup descriptor'); check(x.events.join() === 'archive,name', 'part+4 is also loaded again');}
  {const x = fixture(); x.hooks.name = () => {x.archives.getArchive(x.archive).data20 = x.archives.cursorAt(x.base, 1);};
    rejects(x.run, 'lacks explicit'); check(x.j.getBinding(x.joint).aobj7c === null, 'unbound actual address never substitutes index descriptor');}
  {const x = fixture(); rejects(() => x.runtime.bindAddress(x.base, x.archives.cursorAt(x.base, 16), x.anim), 'already bound');
    rejects(() => x.runtime.bindAddress(x.base, Symbol('foreign'), x.anim), 'owned byte cursor');
    rejects(() => x.runtime.bindAddress(x.base, x.archives.cursorAt(x.base, 48), Symbol('foreign')), 'unknown/non-owned');
    x.runtime.bindAddress(x.base, x.archives.cursorAt(x.base, 48), x.anim);
    rejects(() => x.runtime.bindPart(x.part, {descriptor04: x.descriptor}), 'already bound');}
  {const x = fixture(); x.hooks.name = () => {rejects(x.run, 'reentry');};
    rejects(x.run, 'reentry caught'); check(x.events.join() === 'archive,name', 'caught nested execution poisons outer run');}
  {const x = fixture(); x.hooks.add = () => Promise.resolve(); rejects(x.run, 'synchronously return void');
    check(x.j.getBinding(x.joint).aobj7c !== null && !x.events.includes('tail'), 'nonvoid result refuses after preserving real attachment');}
  {const x = fixture(); x.archiveAdapter.getPublicName = () => {throw Error('replacement must not run');};
    x.attachmentAdapter.addAnimation = () => {throw Error('replacement must not run');};
    rejects(x.run, 'missing track fallback'); check(x.events.includes('add'), 'captured methods survive host replacement');}
  {const x = fixture(); x.aDescs.getDescriptor(x.aDesc).joint0c = Symbol('unresolved joint descriptor');
    rejects(x.run, 'joint'); check(!x.events.includes('tail'), 'real loader refusal does not advance to tail');}
}
