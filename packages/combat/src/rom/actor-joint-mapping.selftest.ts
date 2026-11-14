import {createSourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
import {createSourceArchivePublicRuntime} from './archive-public.js';
import {createSourceActorJointMappingRuntime, type SourceActorJointMappingHeader,
  type SourceActorJointPartBinding} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime, type SourceJointAnimationPart,
  type SourceJointPoseEffects} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {AOBJ_LOOP, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';

function check(ok: boolean, message: string): void {if (!ok) throw Error(`[actor-joint-mapping-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const partInitial = (patch: Partial<SourceJointAnimationPart> = {}): SourceJointAnimationPart =>
  ({frame0c: 123, duration24: 3, segment2d: 9, complete2e: 0, mode2f: 0, mirror30: 0, ...patch});
const bindingInitial = (patch: Partial<SourceActorJointPartBinding> = {}): SourceActorJointPartBinding =>
  ({descriptor00: Symbol('non-null part descriptor'), scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0, ...patch});
const poseInitial = () => ({translation: {x: -1, y: -2, z: -3}, quaternion: {x: 4, y: 5, z: 6, w: 7}});
// Explicit analytic fixture backend, never a default/general quaternion converter.
// Only positive-zero Euler inputs are admitted; every other rotation refuses.
const zeroEuler: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
  check(Object.isFrozen(rotation), 'converter receives an immutable Euler snapshot');
  if (![rotation.x, rotation.y, rotation.z].every(v => Object.is(v, 0))) throw Error('fixture supports positive zero Euler only');
  output.x = 0; output.y = 0; output.z = 0; output.w = 1;
}};
function fixture(options: {map?: readonly number[]; count?: number; boundaries?: readonly number[]; poseCount?: number} = {}) {
  const j = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(j);
  const tracks = Array.from({length: 2}, (_, bank) => Array.from({length: 8}, (_, index) => {
    const base = 10 + bank * 80 + index * 10;
    const joint = j.createJoint({sibling08: null, child10: null, flags14: 0, rotation1c: 0, rotation20: 0, rotation24: 0,
      scale2c: 1, scale30: 1, scale34: 1, translation38: base - 5, translation3c: bank + 2, translation40: index + 3},
    {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
    const f = createSourceFObjScalarCallbackRuntime(joint), data = f.createData(Uint8Array.from([2, base, 4, 2, base + 8]));
    const node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5, flags10: 1,
      byte11: 0, byte12: 0, track13: 5, format14: 0x80, format15: 0x80,
      half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
    const aobj = feedback.createAObj({flags: 0, frame: 0, rewind: 0, end: 3, rate: 1, fobjs: node});
    const a = feedback.getAObj(aobj), binding = j.getBinding(joint);
    binding.aobj7c = aobj; binding.classUpdate50 = f.createCallback(j.updateScalar);
    requestSourceAObj(a, 0, f.effects);
    return {bank, index, base, joint, f, aobj, a, binding};
  }));
  type Track = (typeof tracks)[number][number];
  const byJoint = new Map(tracks.flat().map(t => [t.joint, t]));
  const events: string[] = [], visits: string[] = [];
  // afterPose mutations, reentry and non-void returns below deliberately inject
  // out-of-contract faults to inspect refusal boundaries, never admitted source
  // conversion behavior. The real converter only writes its supplied quaternion.
  const hooks: {afterInterpret?: (track: Track) => void; afterR?: () => void; afterD?: () => void; afterPose?: () => void} = {};
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      check(this === effects, 'interpreter retains original effect-table this');
      const track = byJoint.get(owner); check(track !== undefined, 'real interpreter receives an owned joint');
      check(id === track!.aobj, 'real interpreter receives the selected joint AObj');
      interpretSourceAObj(feedback.getAObj(id!), callback, track!.f.effects, j.endCallbacks.counts);
      visits.push(`${track!.bank}:${track!.index}`); events.push('a'); return hooks.afterInterpret?.(track!);
    },
    animateRObjs(list) {check(this === effects, 'RObj effect retains this'); check(list === null, 'fixture refuses nonnull RObj');
      events.push('r'); return hooks.afterR?.();},
    animateDObjs(list) {check(this === effects, 'DObj effect retains this'); check(list === null, 'fixture refuses nonnull DObj');
      events.push('d'); return hooks.afterD?.();},
  };
  const poseEffects: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
    check(this === poseEffects, 'pose converter retains original effect-table this');
    zeroEuler.convertEulerToQuaternion(rotation, output); events.push('q'); return hooks.afterPose?.();
  }};
  // Mutable own-data forwarding tables test snapshot and receiver behavior while
  // delegating every operation to the real JObj/feedback implementation.
  const jointAdapter = {...j, getBinding(id: symbol) {
    check(this === jointAdapter, 'getBinding retains runtime-table this'); return j.getBinding(id);
  }};
  const feedbackAdapter = {...feedback,
    createPart(initial: SourceJointAnimationPart) {
      check(this === feedbackAdapter, 'createPart retains runtime-table this'); return feedback.createPart(initial);
    },
    getPart(id: symbol) {check(this === feedbackAdapter, 'getPart retains runtime-table this'); return feedback.getPart(id);},
    getPose(id: symbol) {check(this === feedbackAdapter, 'getPose retains runtime-table this'); return feedback.getPose(id);},
    getAObj(id: symbol) {check(this === feedbackAdapter, 'getAObj retains runtime-table this'); return feedback.getAObj(id);},
    advanceExistingJoint(...args: Parameters<typeof feedback.advanceExistingJoint>) {
      check(this === feedbackAdapter, 'advance retains runtime-table this'); feedback.advanceExistingJoint(...args);
    },
    capturePoseAndFrame(...args: Parameters<typeof feedback.capturePoseAndFrame>) {
      check(this === feedbackAdapter, 'capture retains runtime-table this'); feedback.capturePoseAndFrame(...args);
    },
  };
  const runtime = createSourceActorJointMappingRuntime(jointAdapter, feedbackAdapter, effects, poseEffects);
  const mapInput = [...(options.map ?? [1, 2, 3, 2])], descriptor = runtime.createDescriptor(mapInput);
  const jointInputs = tracks.map(row => row.map(t => t.joint)), banks = jointInputs.map(row => runtime.createJointBank(row));
  const partInputs = Array.from({length: 2}, () => Array.from({length: 4}, () => partInitial()));
  const bindingInputs = partInputs.map(row => row.map(() => bindingInitial()));
  const parts = partInputs.map((row, bank) => row.map((initial, index) => runtime.createPart(initial, bindingInputs[bank]![index]!)));
  const poses = Array.from({length: 2}, () => Array.from({length: options.poseCount ?? 8}, () => feedback.createPose(poseInitial())));
  const bounds = options.boundaries ?? [1, 2, 3];
  const actorInput: SourceActorJointMappingHeader = {descriptor4b0: descriptor, jointCount1d90: options.count ?? 4,
    boundary1d91: bounds[0]!, boundary1d92: bounds[1]!, boundary1d93: bounds[2]!,
    jointBank1db4: banks[0]!, jointBank1db8: banks[1]!, timestep1dc8: 1};
  const actor = runtime.createActor(actorInput, {parts, poses}), header = runtime.getActor(actor);
  const part = (bank = 0, number = 0) => feedback.getPart(parts[bank]![number]!);
  const binding = (bank = 0, number = 0) => runtime.getPartBinding(parts[bank]![number]!);
  const pose = (bank: number, index: number) => feedback.getPose(poses[bank]![index]!);
  const track = (bank: number, index: number) => tracks[bank]![index]!;
  const animate = (partBank = 0, poseBank = 0, number = 0, flags = 2) => runtime.animatePart(actor, partBank, poseBank, number, flags);
  return {j, feedback, runtime, jointAdapter, feedbackAdapter, effects, poseEffects, tracks, track, hooks, events, visits,
    descriptor, mapInput, jointInputs, banks, partInputs, bindingInputs, parts, poses, actorInput, actor, header, part, binding, pose, animate};
}
export function runActorJointMappingSelfTest(): void {
  // Prepared mapping is the 4a754 continuation: it never repeats the selector
  // store. A read-only selector is admissible on an empty range (no later read).
  {
    const x = fixture({boundaries: [0, 0, 0]});
    Object.defineProperty(x.binding(), 'poseBuffer35', {value: 1, writable: false});
    x.runtime.mapPreparedPart(x.actor, 0, 0, 3);
    rejects(() => x.animate(0, 1, 0, 3), 'poseBuffer35: non-writable');
  }
  {
    const x = fixture(); x.binding().poseBuffer35 = 1;
    x.runtime.mapPreparedPart(x.actor, 0, 0, 2);
    check(x.visits.join() === '0:1' && x.pose(1, 1).translation.x === 20 && x.pose(0, 1).translation.x === -1,
      'prepared mapping consumes existing selector and keeps actual playback/capture');
  }
  {
    const x = fixture(), archives = createSourceArchivePublicRuntime();
    const unreachable = (): never => {throw Error('unreached attachment/tail');};
    const setup = createSourceArchiveJointSetupRuntime({actors: x.runtime, archives,
      attachment: {getDescriptor: unreachable, addAnimation: unreachable}, tail: {continueAttachedSetupTail: unreachable}});
    const archive = archives.createArchive({publicCount0c: 0, data20: null, publicTable28: null, stringTable30: null});
    const descriptor = setup.createDescriptor({archive0c: archive});
    setup.bindPart(x.parts[0]![0]!, {descriptor04: descriptor});
    setup.bindActorPoseIndex(x.actor, 0);
    const poses = setup.createPoseTable(Array.from({length: 65}, () => ({translation0c: 1, translation1c: 2, translation2c: 3})));
    setup.bindPosePool([poses]);
    x.runtime.bindSetupRuntime(setup);
    rejects(() => x.animate(0, 1, 0, 3), 'out-of-count');
    check(x.events.length === 0 && x.pose(1, 1).translation.x === -1,
      'actual archive runtime performs owned actor/pool/pose/count prefix and refuses before capture');
  }
  // Deliberately rejecting setup adapters exercise dispatch/configuration only.
  // Successful archive attachment and subsequent capture/scaling are exercised
  // by the packed actor integration, never a fabricated successful setup effect.
  for (const flags of [1, 3, 0xffffffff]) {
    const x = fixture(); x.header.timestep1dc8 = NaN;
    const setup = {setupActorJoint(actor: symbol, part: symbol, joint: symbol | null, index: number): never {
      check(this === setup, 'setup original receiver is retained');
      check(actor === x.actor && part === x.parts[0]![0] && joint === x.track(0, 1).joint && index === 1,
        'setup receives actual actor, selected part, retained joint and source index');
      throw Error('explicit rejecting setup fixture');
    }};
    x.runtime.bindSetupRuntime(setup);
    setup.setupActorJoint = () => {throw Error('replaced method must not run');};
    rejects(() => x.runtime.bindSetupRuntime(setup), 'already bound');
    rejects(() => x.animate(0, 1, 0, flags), 'explicit rejecting setup fixture');
    check(x.events.length === 0 && x.pose(1, 1).translation.x === -1 && x.track(0, 1).a.rate === 1,
      'setup wins over playback without timestep load, advance or capture after refusal');
  }
  for (const action of ['bind', 'prepared', 'animate'] as const) {
    const x = fixture();
    const setup = {setupActorJoint() {
      rejects(() => {
        if (action === 'bind') x.runtime.bindSetupRuntime(setup);
        else if (action === 'prepared') x.runtime.mapPreparedPart(x.actor, 0, 0, 1);
        else x.animate();
      }, 'same-runtime reentry');
    }};
    x.runtime.bindSetupRuntime(setup);
    rejects(() => x.animate(0, 1, 0, 1), 'reentry was caught');
    check(x.events.length === 0 && x.pose(1, 1).translation.x === -1, 'caught setup reentry poisons outer call before capture');
  }
  {
    const x = fixture();
    x.runtime.bindSetupRuntime({setupActorJoint: (() => Promise.resolve()) as unknown as () => void});
    rejects(() => x.animate(0, 1, 0, 1), 'synchronously and return undefined');
    check(x.events.length === 0, 'async setup return refuses before capture');
  }
  {
    const x = fixture();
    rejects(() => x.runtime.bindSetupRuntime(Object.create({setupActorJoint() {throw Error('inherited');}})), 'own data');
    x.runtime.bindSetupRuntime({setupActorJoint() {throw Error('unused setup must not run');}});
    x.animate();
    check(x.visits.join() === '0:1' && x.pose(0, 1).translation.x === 20, 'binding setup leaves existing playback unchanged');
  }
  // All four signed range formulas, including a distinct end=count range.
  for (const [number, expected] of [[0, '0:3,0:1'], [1, '0:2'], [2, '0:3,0:1'], [3, '0:2,0:3']] as const) {
    const x = fixture({map: [3, 1, 2, 3, 1, 2, 3], count: 7, boundaries: [2, 3, 5]});
    x.animate(0, 1, number);
    check(x.visits.join() === expected && x.binding(0, number).poseBuffer35 === 1 && x.part(0, number).frame0c === 0,
      `part${number} uses its source range and stores pose selector`);
    for (const index of expected.split(',').map(s => Number(s.split(':')[1]))) {
      check(x.pose(1, index).translation.x === x.track(0, index).base && x.pose(1, index).quaternion.w === 1,
        'range executes packed FObj scalar callbacks and actual pose conversion');
      check(x.pose(0, index).translation.x === -1, 'unselected pose bank is untouched');
    }
  }
  {
    const x = fixture(); x.binding(1, 2).jointBank33 = 1; x.animate(1, 0, 2);
    check(x.visits.join() === '1:3' && x.pose(0, 3).translation.x === 120 && x.pose(0, 3).translation.y === 3 &&
      x.pose(0, 3).translation.z === 6 && x.part(1, 2).frame0c === 0 && x.part(0, 2).frame0c === 123 &&
      x.part(1, 0).frame0c === 123 && x.pose(1, 3).translation.x === -1,
    'part bank, joint bank and pose bank are three independent selections');
  }
  for (const [number, count, bounds] of [[0, 4, [0, 2, 3]], [1, 4, [2, 2, 3]], [2, 4, [1, 3, 2]],
    [3, 2, [1, 2, 3]], [0, 4, [255, 2, 3]], [1, 4, [255, 254, 3]], [3, 255, [1, 2, 0]]] as const) {
    const x = fixture({count, boundaries: bounds}); x.header.descriptor4b0 = null;
    x.animate(0, 255, number, 1);
    check(x.binding(0, number).poseBuffer35 === 255 && x.events.length === 0 && x.part(0, number).complete2e === 0,
      'empty/reversed/signed range stores selector without descriptor/setup/pose access');
  }
  {
    const x = fixture({boundaries: [255, 0, 0]});
    rejects(() => x.animate(0, 1, 1), 'joint map: addressing');
    check(x.binding(0, 1).poseBuffer35 === 1 && x.events.length === 0, 'negative signed start refuses only at reached map access');
  }
  {
    const x = fixture({map: [1, 1, 2], count: 3, boundaries: [3, 3, 3]}); x.header.timestep1dc8 = 2; x.part().duration24 = 1;
    let endCalls = 0; x.j.endCallbacks.counts.running = 5; x.j.endCallbacks.counts.stopped = 6;
    x.j.endCallbacks.state.head28 = x.j.endCallbacks.createNode({next00: null,
      callback04: x.j.endCallbacks.createCallback(() => {endCalls++;})});
    x.animate();
    check(x.visits.join() === '0:1,0:1,0:2' && x.track(0, 1).a.frame === 2 && x.pose(0, 1).translation.x === 24 &&
      x.pose(0, 2).translation.x === 30 && x.part().frame0c === 0 && x.part().complete2e === 1,
    'duplicate map repeats real advancement; completion does not stop later pose/frame overwrites');
    check(x.j.endCallbacks.counts.running === 8 && x.j.endCallbacks.counts.stopped === 6 && endCalls === 0 &&
      x.events.join() === 'a,r,d,q,a,r,d,q,a,r,d,q', 'single-joint mapping never resets counters or invokes global end callbacks');
  }
  {
    const x = fixture({map: [1], count: 2}); const t = x.track(0, 1);
    x.part().duration24 = 39; t.a.end = 39; x.header.timestep1dc8 = 2; requestSourceAObj(t.a, 38, t.f.effects);
    x.animate(); check(x.part().frame0c === 38 && x.part().complete2e === 0, 'requested frame38 suppresses first advancement');
    x.animate(); check(x.part().frame0c === 40 && x.part().complete2e === 1 && x.pose(0, 1).translation.x === 100,
      'actual end39/frame38/rate2 overshoot stays unclamped and captures actual packed-stream linear extrapolation');
    check(x.j.endCallbacks.counts.running === 1 && x.j.endCallbacks.counts.stopped === 1, 'actual AObj state drives completion counts');
  }
  {
    const x = fixture({map: [1], count: 2}), t = x.track(0, 1);
    x.part().duration24 = 30; t.a.end = 30; t.a.flags |= AOBJ_LOOP; x.header.timestep1dc8 = 1.5;
    requestSourceAObj(t.a, 28.5, t.f.effects); x.animate(); x.animate();
    check(x.part().frame0c === 0 && x.part().segment2d === 1 && x.part().complete2e === 0 && x.pose(0, 1).translation.x === 20,
      'real wrap re-requests scalar stream and copies segment/frame without completing');
  }
  {
    const x = fixture({map: [1, 1, 1, 7], count: 3, boundaries: [0, 0, 0]});
    const replacement = x.runtime.createDescriptor([0, 2, 3, 7]);
    const replacementBank = x.runtime.createJointBank(x.tracks[0]!.map(t => t.joint));
    x.runtime.getJointBank(replacementBank)[1] = x.track(0, 3).joint;
    x.hooks.afterInterpret = t => {
      if (t.joint === x.track(0, 1).joint) {
        x.header.descriptor4b0 = replacement; x.header.jointCount1d90 = 4; x.header.boundary1d93 = 7;
        x.binding(0, 3).jointBank33 = 1; x.header.timestep1dc8 = 2; x.binding(0, 3).poseBuffer35 = 1;
        x.runtime.getJointBank(x.banks[0]!)[1] = x.track(1, 7).joint;
        x.runtime.getJointBank(x.banks[1]!)[2] = x.track(1, 4).joint;
      } else if (t.joint === x.track(1, 4).joint) {
        x.runtime.getDescriptor(replacement)[2] = 1; x.header.jointCount1d90 = 2; x.header.boundary1d93 = 0;
        x.binding(0, 3).jointBank33 = 0; x.header.jointBank1db4 = replacementBank;
        x.header.timestep1dc8 = 3; x.binding(0, 3).poseBuffer35 = 0;
        x.runtime.getJointBank(x.banks[1]!)[2] = x.track(1, 7).joint;
      }
    };
    x.animate(0, 0, 3);
    check(x.visits.join() === '0:1,1:4,0:3' && x.track(0, 1).a.rate === 1 && x.track(1, 4).a.rate === 2 && x.track(0, 3).a.rate === 3,
      'future iterations reload descriptor/map/count/joint bank/table/timestep while original range stays snapshotted');
    check(x.pose(1, 1).translation.x === 20 && x.pose(0, 2).translation.x === 130 && x.pose(0, 1).translation.x === 40 &&
      x.pose(0, 3).translation.x === -1 && x.track(1, 7).a.rate === 1,
    'current JObj stays cached; post-advance pose selector and mapped index select destination, not actual joint identity');
  }
  {
    const x = fixture({map: [1, 2, 1], count: 4, boundaries: [3, 3, 3]});
    x.hooks.afterInterpret = () => {x.header.jointCount1d90 = 2;}; x.animate();
    check(x.visits.join() === '0:1,0:1' && x.pose(0, 2).translation.x === -1 && x.track(0, 1).a.frame === 1,
      'each mapped index compares with current count; ordinal2 is processed even when current count is2');
  }
  {
    const x = fixture({map: [1, 0, 255], count: 3, boundaries: [3, 3, 3]});
    x.hooks.afterInterpret = () => {x.binding().descriptor00 = null;}; x.animate();
    check(x.visits.join() === '0:1' && x.part().complete2e === 1 && x.part().frame0c === 0 && x.pose(0, 1).translation.x === 20,
      'future ordinals reload changed part descriptor and null-complete root/negative entries');
  }
  for (const mapped of [0, 255]) {
    const x = fixture({map: [mapped], count: 2}); x.binding().descriptor00 = null;
    x.part().mirror30 = NaN; x.binding().jointBank33 = NaN; x.binding().scaleIndex32 = NaN;
    x.header.jointCount1d90 = NaN; x.header.timestep1dc8 = NaN;
    x.animate(0, 255, 0, 1);
    check(x.part().complete2e === 1 && x.part().frame0c === 123 && x.events.length === 0 && x.binding().poseBuffer35 === 255,
      'null part descriptor latches before root/negative/count/bank/pose/scaling/setup and ignores invalid unused fields');
  }
  {
    const x = fixture({map: [0, 1], count: 2, boundaries: [2, 2, 2]}); x.binding().descriptor00 = null;
    Object.defineProperty(x.runtime.getDescriptor(x.descriptor), '1', {writable: false});
    rejects(() => x.animate(), '1: non-writable');
    check(x.part().complete2e === 1 && x.events.length === 0, 'null completion does not end loop; next map read still happens');
  }
  {
    const x = fixture(); x.binding().descriptor00 = null; x.header.descriptor4b0 = null;
    rejects(() => x.animate(0, 1), 'null actor descriptor');
    check(x.part().complete2e === 0 && x.binding().poseBuffer35 === 1, 'actor descriptor/map access precedes null-part completion');
  }
  for (const [mapped, mirror, count, expected] of [[0, 0, 0, 'root-motion'], [0, 1, 0, 'mirrored joint'],
    [7, 1, 0, 'mirrored joint'], [254, 0, 255, 'negative joint']] as const) {
    const x = fixture({map: [mapped], count}); x.part().mirror30 = mirror;
    rejects(() => x.animate(), expected);
    check(x.events.length === 0 && x.part().frame0c === 123, 'mirror/root gates precede count and reached negative addressing precedes effects');
  }
  for (const [mapped, count] of [[2, 2], [7, 2], [255, 255]] as const) {
    const x = fixture({map: [mapped], count}); x.binding().jointBank33 = NaN; x.binding().scaleIndex32 = NaN;
    x.header.jointBank1db4 = Symbol('foreign unused'); x.header.timestep1dc8 = NaN;
    x.animate(0, 255, 0, 1);
    check(x.events.length === 0 && x.part().complete2e === 0, 'count skip leaves invalid downstream and setup fields unused, including negative>=negative');
  }
  for (const flags of [0, 4, 0xfffffffc]) {
    const x = fixture(); x.header.timestep1dc8 = NaN; Object.defineProperty(x.header, 'timestep1dc8', {writable: false});
    x.animate(0, 0, 0, flags);
    check(x.visits.length === 0 && x.pose(0, 1).translation.x === 15 && x.pose(0, 1).quaternion.w === 1 &&
      x.part().frame0c === 0 && x.part().segment2d === 9 && x.track(0, 1).a.rate === 1,
    'bit2-clear still captures actual pose/frame without reading invalid timestep or advancing');
  }
  {
    const x = fixture(); x.track(0, 1).binding.aobj7c = null; x.header.timestep1dc8 = NaN;
    Object.defineProperty(x.header, 'timestep1dc8', {writable: false}); x.animate();
    check(x.visits.length === 0 && x.pose(0, 1).translation.x === 15 && x.pose(0, 1).quaternion.w === 1 &&
      x.part().frame0c === 123 && x.part().segment2d === 9, 'null AObj skips timestep/advance but still performs real pose capture');
  }
  for (const flags of [1, 3, 0xffffffff]) {
    const x = fixture(); x.header.timestep1dc8 = NaN;
    rejects(() => x.animate(0, 1, 0, flags), 'setup branch');
    check(x.binding().poseBuffer35 === 1 && x.pose(1, 1).translation.x === -1 && x.events.length === 0,
      'reached setup refusal happens before timestep or pose capture');
  }
  {
    const x = fixture(); x.header.timestep1dc8 = NaN;
    rejects(() => x.animate(), 'timestep1dc8'); check(x.track(0, 1).a.rate === 1 && x.events.length === 0, 'reached timestep rejects before advancement');
  }
  for (const scale of [0, 127]) {
    const x = fixture(); x.binding().scaleIndex32 = scale;
    rejects(() => x.animate(), 'translation scaling');
    check(x.part().frame0c === 0 && x.part().segment2d === 0 && x.pose(0, 1).translation.x === 20 &&
      x.pose(0, 1).quaternion.w === 1 && x.events.join() === 'a,r,d,q', 'target1 scaling refuses only after complete capture');
  }
  for (const scale of [128, 255]) {
    const x = fixture(); x.binding().scaleIndex32 = scale; x.animate();
    check(x.pose(0, 1).translation.x === 20, 'signed-negative scale byte does not enter target1 scaling');
  }
  {
    const x = fixture({map: [2]}); x.binding().scaleIndex32 = 0; x.animate();
    check(x.pose(0, 2).translation.x === 30, 'nonnegative scale index is admitted for target2');
    Object.defineProperty(x.binding(), 'scaleIndex32', {writable: false});
    rejects(() => x.animate(), 'scaleIndex32: non-writable');
    check(x.pose(0, 2).translation.x === 32 && x.part().frame0c === 1, 'target2 still reads scale index after capture');
  }
  {
    // Deliberate out-of-contract converter fault injection, not source behavior.
    const x = fixture({map: [2]}); x.hooks.afterPose = () => {x.binding().scaleIndex32 = NaN;};
    rejects(() => x.animate(), 'scaleIndex32');
    check(x.part().frame0c === 0 && x.pose(0, 2).quaternion.w === 1, 'fault-injected scale index mutation is observed after capture/frame feedback');
  }
  {
    // Deliberate out-of-contract converter fault injection tests late reload.
    const x = fixture(); x.hooks.afterPose = () => {x.binding().scaleIndex32 = 0;};
    rejects(() => x.animate(), 'translation scaling');
    check(x.part().frame0c === 0, 'fault-injected scaling gate observes post-capture value rather than entry snapshot');
  }
  for (const readonly of [false, true]) {
    const x = fixture({map: [1, 2], boundaries: [2, 2, 2]});
    x.hooks.afterInterpret = () => {
      if (readonly) Object.defineProperty(x.runtime.getDescriptor(x.descriptor), '1', {writable: false});
      else x.runtime.getDescriptor(x.descriptor)[1] = NaN;
    };
    rejects(() => x.animate(), readonly ? '1: non-writable' : '1: unsigned');
    check(x.visits.join() === '0:1' && x.pose(0, 1).translation.x === 20 && x.part().frame0c === 0 && x.pose(0, 2).translation.x === -1,
      'late map failure retains completed first-entry advancement/pose/frame only');
  }
  {
    const x = fixture({map: [1, 2], boundaries: [2, 2, 2]});
    Object.defineProperty(x.runtime.getJointBank(x.banks[0]!), '2', {writable: false});
    rejects(() => x.animate(), '2: non-writable');
    check(x.visits.join() === '0:1' && x.pose(0, 1).translation.x === 20, 'late readonly joint table retains preceding work');
  }
  {
    const x = fixture({map: [1, 2], boundaries: [2, 2, 2]});
    Object.defineProperty(x.pose(0, 2).translation, 'y', {writable: false});
    rejects(() => x.animate(), 'y: non-writable');
    check(x.visits.join() === '0:1,0:2' && x.pose(0, 1).quaternion.w === 1 && x.pose(0, 2).translation.x === 30 &&
      x.pose(0, 2).translation.y === -2 && x.pose(0, 2).translation.z === -3 && x.pose(0, 2).quaternion.w === 7,
    'late pose failure preserves earlier joint and current translation store prefix');
  }
  for (const poseBank of [2, 128, 255]) {
    const x = fixture(); x.hooks.afterInterpret = () => {x.binding().poseBuffer35 = poseBank;};
    rejects(() => x.animate(), 'pose bank: addressing');
    check(x.visits.join() === '0:1' && x.part().segment2d === 0 && x.part().frame0c === 123 && x.pose(0, 1).translation.x === -1,
      'invalid signed pose selector refuses after actual advancement but before capture');
  }
  {
    const x = fixture({map: [2], poseCount: 2});
    rejects(() => x.animate(), 'pose table: addressing');
    check(x.visits.join() === '0:2' && x.part().segment2d === 0 && x.part().frame0c === 123, 'bounded pose table failure follows advancement');
  }
  {
    const x = fixture(); x.binding().poseBuffer35 = NaN; x.header.boundary1d91 = NaN;
    rejects(() => x.animate(0, 1), 'boundary1d91');
    check(x.binding().poseBuffer35 === 1, 'selector store overwrites invalid old value before range validation');
  }
  {
    const x = fixture(); Object.defineProperty(x.binding(), 'poseBuffer35', {writable: false}); x.header.boundary1d91 = NaN;
    rejects(() => x.animate(0, 1), 'poseBuffer35: non-writable');
    check(x.events.length === 0 && x.binding().poseBuffer35 === 0, 'readonly selector refuses before range reads');
  }
  {
    const x = fixture(); Object.defineProperty(x.part(), 'frame0c', {writable: false});
    rejects(() => x.animate(), 'frame0c: non-writable');
    check(x.pose(0, 1).translation.x === 20 && x.pose(0, 1).quaternion.w === 1 && x.part().frame0c === 123,
      'readonly feedback frame retains real completed pose and advancement');
  }
  {
    const x = fixture(); x.j.getJoint(x.track(0, 1).joint).rotation20 = 1;
    rejects(() => x.animate(), 'fixture supports positive zero Euler');
    check(x.pose(0, 1).translation.x === 20 && x.pose(0, 1).quaternion.w === 7 && x.part().frame0c === 123,
      'nonzero Euler refuses explicitly after scalar/translation work, not fake identity success');
  }
  {
    const x = fixture(); const replaced = () => {throw Error('replaced adapter should not run');};
    x.effects.interpretAObj = replaced; x.effects.animateRObjs = replaced; x.effects.animateDObjs = replaced;
    x.poseEffects.convertEulerToQuaternion = replaced; x.jointAdapter.getBinding = replaced;
    x.feedbackAdapter.getPart = replaced; x.feedbackAdapter.getPose = replaced; x.feedbackAdapter.getAObj = replaced;
    x.feedbackAdapter.advanceExistingJoint = replaced; x.feedbackAdapter.capturePoseAndFrame = replaced;
    x.feedbackAdapter.createPart = replaced;
    const extra = x.runtime.createPart(partInitial(), bindingInitial());
    check(x.feedback.getPart(extra).frame0c === 123, 'part factory function was snapshotted');
    x.animate(); check(x.pose(0, 1).translation.x === 20 && x.events.join() === 'a,r,d,q',
      'all fixed adapters keep construction-time functions and original receivers');
  }
  for (const stage of ['afterInterpret', 'afterR', 'afterD', 'afterPose'] as const) {
    for (const result of [1, Promise.resolve()]) {
      const x = fixture(); x.hooks[stage] = () => result;
      rejects(() => x.animate(), 'synchronously');
      check(x.part().frame0c === 123 && x.pose(0, 1).translation.x === (stage === 'afterPose' ? 20 : -1),
        'non-undefined/thenable effect result refuses before later mapping steps while retaining reached work');
      delete x.hooks[stage]; x.animate(); check(x.part().frame0c === 1, 'effect return refusal permits clean later call');
    }
  }
  for (const stage of ['afterR', 'afterD', 'afterPose'] as const) {
    const x = fixture(); x.hooks[stage] = () => {throw Error(`required ${stage} refusal`);};
    rejects(() => x.animate(), `required ${stage} refusal`);
    check(x.j.getJoint(x.track(0, 1).joint).translation38 === 20 && x.part().frame0c === 123 &&
      x.pose(0, 1).translation.x === (stage === 'afterPose' ? 20 : -1), 'effect failure retains exactly reached real work');
    delete x.hooks[stage]; x.animate(); check(x.part().frame0c === 1, 'failed effect releases runtime for later successful call');
  }
  for (const stage of ['afterInterpret', 'afterR', 'afterPose'] as const) {
    for (const caught of [false, true]) {
      const x = fixture(); x.part().duration24 = 0; x.hooks[stage] = () => {
        if (caught) {try {x.animate(1, 1, 0);} catch { /* caught reentry must still poison the outer mapper */ }}
        else x.animate(1, 1, 0);
      };
      rejects(() => x.animate(), 'reentry');
      check(x.part(1).frame0c === 123 && x.binding(1).poseBuffer35 === 0 && x.j.getJoint(x.track(0, 1).joint).translation38 === 20,
        'caught and uncaught reentry cannot execute nested selector writes and preserve earlier real scalar work');
      check(x.events.join() === (stage === 'afterInterpret' ? 'a' : stage === 'afterR' ? 'a,r' : 'a,r,d,q') &&
        x.part().segment2d === (stage === 'afterPose' ? 0 : 9) && x.part().frame0c === 123 && x.part().complete2e === 0 &&
        x.pose(0, 1).quaternion.w === (stage === 'afterPose' ? 1 : 7) && x.j.endCallbacks.counts.running === 1,
      'reentry poison refuses at the immediate adapter boundary before later effects, segment, frame or completion');
      delete x.hooks[stage]; x.animate(); check(x.part().frame0c === 1 && x.pose(0, 1).translation.x === 22,
        'outer refusal clears busy/poison for independent subsequent call');
    }
  }
  {
    const x = fixture(); const layout = x.runtime.getLayout(x.actor);
    x.mapInput[0] = 0; x.jointInputs[0]![1] = x.track(1, 7).joint; x.actorInput.descriptor4b0 = null;
    x.bindingInputs[0]![0]!.descriptor00 = null; x.partInputs[0]![0]!.mirror30 = 1;
    x.parts[0]![0] = Symbol('changed original layout'); x.poses[0]![1] = Symbol('changed original pose layout');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.header) && Object.isSealed(x.runtime.getDescriptor(x.descriptor)) &&
      Object.isSealed(x.runtime.getJointBank(x.banks[0]!)) && Object.isFrozen(layout) && Object.isFrozen(layout.parts) &&
      Object.isFrozen(layout.parts[0]) && Object.isFrozen(layout.poses[0]), 'runtime owns sealed records and immutable layout containers');
    x.runtime.animatePart(x.actor, 0, 0, 0, 2);
    const storedPart = layout.parts[0]![0]!, storedPose = layout.poses[0]![1]!;
    check(x.feedback.getPart(storedPart).frame0c === 0 && x.feedback.getPose(storedPose).translation.x === 20,
      'factories copy maps, banks, records and layout arrays rather than retaining caller aliases');
  }
  {
    const x = fixture(); const foreign = fixture();
    rejects(() => x.runtime.getDescriptor(foreign.descriptor), 'non-owned descriptor');
    rejects(() => x.runtime.getJointBank(foreign.banks[0]!), 'non-owned joint bank');
    rejects(() => x.runtime.getPartBinding(foreign.parts[0]![0]!), 'non-owned part');
    rejects(() => x.runtime.getActor(foreign.actor), 'non-owned actor');
    rejects(() => x.runtime.getLayout(foreign.actor), 'non-owned actor');
    x.header.descriptor4b0 = foreign.descriptor; rejects(() => x.animate(), 'non-owned descriptor');
    x.header.descriptor4b0 = x.descriptor; x.header.jointBank1db4 = foreign.banks[0]!;
    rejects(() => x.animate(), 'non-owned joint bank'); x.header.jointBank1db4 = x.banks[0]!;
    x.runtime.getJointBank(x.banks[0]!)[1] = foreign.track(0, 1).joint;
    rejects(() => x.animate(), 'non-owned animation binding');
  }
  for (const invalid of [null, Symbol('foreign mapped JObj')]) {
    const x = fixture(); x.runtime.getJointBank(x.banks[0]!)[1] = invalid;
    rejects(() => x.animate(), invalid === null ? 'null mapped JObj' : 'non-owned animation binding');
    check(x.events.length === 0 && x.pose(0, 1).translation.x === -1, 'invalid reached joint identity refuses before effects');
  }
  for (const bank of [2, 128, 255]) {
    const x = fixture(); x.binding().jointBank33 = bank;
    rejects(() => x.animate(), 'joint bank: addressing'); check(x.events.length === 0, 'signed joint bank must address owned banks');
  }
  {
    const x = fixture(); x.header.jointBank1db4 = null;
    rejects(() => x.animate(), 'null joint bank');
    x.header.jointBank1db4 = x.runtime.createJointBank([null]); rejects(() => x.animate(), 'joint table: addressing');
  }
  {
    const x = fixture({map: [31], count: 32, poseCount: 32});
    const bank = x.runtime.createJointBank(Array(32).fill(null) as null[]);
    x.runtime.getJointBank(bank)[31] = x.track(0, 1).joint; x.header.jointBank1db4 = bank; x.animate();
    check(x.pose(0, 31).translation.x === 20 && x.part().frame0c === 0,
      'last admitted joint-bank and pose-bank slot31 works with mapped index rather than joint identity');
    x.runtime.getDescriptor(x.descriptor)[0] = 32; x.header.jointCount1d90 = 33;
    rejects(() => x.animate(), 'joint table: addressing');
    check(x.visits.length === 1, 'selected joint index32 refuses at bank boundary before a second advance');
    rejects(() => fixture({poseCount: 33}), 'length');
  }
  {
    const x = fixture(); const freshParts = () => Array.from({length: 2}, () => Array.from({length: 4}, () =>
      x.runtime.createPart(partInitial(), bindingInitial())));
    const freshPoses = () => Array.from({length: 2}, () => [x.feedback.createPose(poseInitial()), x.feedback.createPose(poseInitial())]);
    rejects(() => x.runtime.createActor(x.actorInput, {parts: x.parts, poses: freshPoses()}), 'aliased inline');
    rejects(() => x.runtime.createActor(x.actorInput, {parts: freshParts(), poses: x.poses}), 'aliased inline');
    const parts = freshParts(), poses = freshPoses(); const saved = parts[1]![0]!; parts[1]![0] = parts[0]![0]!;
    rejects(() => x.runtime.createActor(x.actorInput, {parts, poses}), 'aliased inline'); parts[1]![0] = saved;
    const savedPose = poses[1]![0]!; poses[1]![0] = poses[0]![0]!;
    rejects(() => x.runtime.createActor(x.actorInput, {parts, poses}), 'aliased inline'); poses[1]![0] = savedPose;
    const actor = x.runtime.createActor(x.actorInput, {parts, poses});
    check(x.runtime.getLayout(actor).parts[1]![0] === saved, 'failed admission does not reserve previously inspected parts or poses');
    const foreign = fixture();
    rejects(() => x.runtime.createActor(x.actorInput, {parts: foreign.parts, poses: freshPoses()}), 'non-owned part');
    rejects(() => x.runtime.createActor(x.actorInput, {parts: freshParts(), poses: foreign.poses}), 'non-owned pose');
  }
  {
    const x = fixture(); let getterRan = false;
    const accessor = <T extends object>(value: T, key: string): T => Object.defineProperty(value, key,
      {get() {getterRan = true; throw Error('getter must not run');}});
    rejects(() => x.runtime.createDescriptor(accessor([1], '0')), 'own data property');
    rejects(() => x.runtime.createJointBank(accessor([x.track(0, 1).joint], '0')), 'own data property');
    rejects(() => x.runtime.createPart(partInitial(), accessor(bindingInitial(), 'descriptor00')), 'own data property');
    rejects(() => x.runtime.createPart(partInitial(), Object.create(bindingInitial()) as SourceActorJointPartBinding), 'own data property');
    rejects(() => x.runtime.createActor(accessor({...x.actorInput}, 'boundary1d91'), {parts: x.parts, poses: x.poses}), 'own data property');
    rejects(() => x.runtime.createActor(Object.create(x.actorInput) as SourceActorJointMappingHeader, {parts: x.parts, poses: x.poses}), 'own data property');
    rejects(() => x.runtime.createActor(x.actorInput, accessor({parts: x.parts, poses: x.poses}, 'parts')), 'own data property');
    for (const key of ['interpretAObj', 'animateRObjs', 'animateDObjs'] as const) {
      rejects(() => createSourceActorJointMappingRuntime(x.j, x.feedback, accessor({...x.effects}, key), x.poseEffects), 'own data property');
    }
    rejects(() => createSourceActorJointMappingRuntime(x.j, x.feedback, Object.create(x.effects) as SourceJObjAnimationEffects, x.poseEffects), 'own data property');
    rejects(() => createSourceActorJointMappingRuntime(x.j, x.feedback, x.effects, accessor({...x.poseEffects}, 'convertEulerToQuaternion')), 'own data property');
    rejects(() => createSourceActorJointMappingRuntime(accessor({...x.j}, 'getBinding'), x.feedback, x.effects, x.poseEffects), 'own data property');
    rejects(() => createSourceActorJointMappingRuntime(x.j, accessor({...x.feedback}, 'capturePoseAndFrame'), x.effects, x.poseEffects), 'own data property');
    check(!getterRan, 'factories and fixed adapters refuse inherited/accessor inputs without invoking getters');
  }
  {
    const x = fixture();
    for (const value of [-1, 256, 1.5, NaN]) rejects(() => x.runtime.createDescriptor([value]), 'unsigned integer');
    rejects(() => x.runtime.createDescriptor(Array(129).fill(1) as number[]), 'length');
    rejects(() => x.runtime.createJointBank(Array(33).fill(null) as null[]), 'length');
    check(x.runtime.getDescriptor(x.runtime.createDescriptor(Array(128).fill(255) as number[])).length === 128,
      'descriptor permits128 raw-byte entries without imposing signed read bounds at construction');
    rejects(() => x.runtime.createDescriptor(new Array<number>(1)), 'own data property');
    rejects(() => x.runtime.createJointBank([1 as unknown as symbol]), 'opaque symbol');
    rejects(() => x.runtime.createPart(partInitial(), bindingInitial({jointBank33: -1})), 'jointBank33');
    rejects(() => x.runtime.createActor({...x.actorInput, timestep1dc8: 0.1}, {parts: x.parts, poses: x.poses}), 'float32');
    rejects(() => x.runtime.createActor({...x.actorInput, jointCount1d90: -1}, {parts: x.parts, poses: x.poses}), 'jointCount1d90');
    for (const args of [[-1, 0, 0, 2], [2, 0, 0, 2], [0, -1, 0, 2], [0, 256, 0, 2], [0, 0, 4, 2], [0, 0, 0, -1],
      [0, 0, 0, 0x100000000], [0, 0, 0, NaN]] as const) rejects(() => x.runtime.animatePart(x.actor, args[0], args[1], args[2], args[3]), 'unsigned integer');
    check(x.events.length === 0 && x.binding().poseBuffer35 === 0, 'entry argument admission precedes all stores/effects');
  }
  console.log('[actor-joint-mapping] PASS: bounded owned actor ranges, live mapping and actual joint feedback; explicit zero-Euler fixture, not full modes or original replay');
}
