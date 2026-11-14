import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime, type SourceJointPoseEffects} from './joint-animation-feedback.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {AOBJ_STOPPED, requestSourceAObj, interpretSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[descriptor-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
// This analytic zero-Euler fixture is explicit and rejects all other rotations.
// It is not an installed/default source quaternion backend or a replay oracle.
const zeroEuler: SourceJointPoseEffects = {convertEulerToQuaternion(rotation, output) {
  if (![rotation.x, rotation.y, rotation.z].every(v => Object.is(v, 0))) throw Error('fixture supports positive zero Euler only');
  output.w = 1; output.x = 0; output.y = 0; output.z = 0;
}};
function fixture(options: {badTrack?: boolean; foreignData?: boolean; truncatedData?: boolean} = {}) {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const targets = [0, 1].map(() => joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 7, rotation20: 8, rotation24: 9, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -100, translation3c: -200, translation40: -300},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null}));
  const callbacks: {owner: symbol | null; track: number; value: number}[] = [];
  let firstData: symbol | null = null;
  const rows = targets.map((joint, index) => {
    const fobjs = createSourceFObjScalarCallbackRuntime(joint), loader = createSourceFObjDescriptorRuntime(fobjs);
    const tracks = [1, 2, 3, 5, 6, 7], base = 10 + index * 40;
    const streams = tracks.map((track, trackIndex) => {
      const value = track <= 3 ? 0 : base + (track - 5) * 10;
      const bytes = Uint8Array.from(track <= 3 ? [1, 0, 4, 1, 0] : [2, value, 4, 2, value + 8]);
      const data = fobjs.createData(index === 1 && trackIndex === 5 && options.truncatedData ? bytes.slice(0, 2) : bytes);
      if (index === 0 && trackIndex === 5) firstData = data;
      return {data, bytes};
    });
    const descriptors: symbol[] = []; let next: symbol | null = null;
    for (let i = tracks.length - 1; i >= 0; i--) {
      const badLast = index === 1 && i === 5;
      const id = loader.createDescriptor({next00: next, length04: streams[i]!.bytes.length,
        start08: index === 0 && i === 3 ? 2 : 0,
        track0c: badLast && options.badTrack ? 99 : tracks[i]!, format0d: 0x80, format0e: 0x80,
        data10: badLast && options.foreignData ? firstData : streams[i]!.data});
      descriptors.unshift(id); next = id;
    }
    const head = loader.loadDescriptors(next), nodes: symbol[] = []; let cursor = head;
    while (cursor !== null) {
      nodes.push(cursor); const n = fobjs.getNode(cursor);
      check(n.cursor04 === null && n.flags10 === 0 && n.frame1c === 0 && n.value20 === 0 && n.value24 === 0,
        'descriptor load leaves actual allocation-zero cursor/interpreter state until request');
      cursor = n.next00;
    }
    check(nodes.length === 6 && nodes.map(id => fobjs.getNode(id).track13).join() ===
      (index === 1 && options.badTrack ? '1,2,3,5,6,99' : '1,2,3,5,6,7'), 'six descriptors produce the actual ordered FObj list');
    // AObj state is explicitly seeded. This is not AObjAlloc/AObjLoadDesc and
    // does not assume an unverified allocator rate constant or archive ownership.
    const aobjId = feedback.createAObj({flags: AOBJ_STOPPED, frame: 0, rewind: 0, end: index === 0 ? 3 : 5, rate: 7, fobjs: head});
    const aobj = feedback.getAObj(aobjId), binding = joints.getBinding(joint); binding.aobj7c = aobjId;
    // Exercise actual post-attachment flag helpers on the shared joint, without
    // claiming the missing archive, removal or RObj attachment steps ran.
    if (index === 0) joints.setFlags(joint, 8); else joints.clearFlags(joint, 8);
    binding.classUpdate50 = fobjs.createCallback((owner, track, value) => {
      callbacks.push({owner, track, value}); joints.updateScalar(owner, track, value);
    });
    return {joint, fobjs, loader, descriptors, streams, nodes, head, aobjId, aobj, base};
  });
  const byOwner = new Map(rows.map(row => [row.joint, row]));
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      const row = byOwner.get(owner); check(row !== undefined && row.aobjId === id, 'mapped call keeps real owner/AObj association');
      interpretSourceAObj(row!.aobj, callback, row!.fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');},
    animateDObjs(list) {if (list !== null) throw Error('unsupported DObj');},
  };
  const mapping = createSourceActorJointMappingRuntime(joints, feedback, effects, zeroEuler);
  const parts = Array.from({length: 2}, () => Array.from({length: 4}, () => mapping.createPart(
    {frame0c: 123, duration24: 5, segment2d: 9, complete2e: 0, mode2f: 0, mirror30: 0},
    {descriptor00: Symbol('explicit part descriptor presence'), scaleIndex32: 255, jointBank33: 0, poseBuffer35: 0})));
  const poses = Array.from({length: 2}, () => Array.from({length: 3}, () => feedback.createPose(
    {translation: {x: -1, y: -2, z: -3}, quaternion: {x: 4, y: 5, z: 6, w: 7}})));
  const bank = mapping.createJointBank([null, ...targets]), descriptor = mapping.createDescriptor([1, 2]);
  const actor = mapping.createActor({descriptor4b0: descriptor, jointCount1d90: 3,
    boundary1d91: 2, boundary1d92: 2, boundary1d93: 2, jointBank1db4: bank, jointBank1db8: null, timestep1dc8: 2}, {parts, poses});
  const part = feedback.getPart(parts[0]![0]!), pose = (index: number) => feedback.getPose(poses[0]![index]!);
  const requests = createSourceAnimationRequestRuntime({joints,
    dobjs: createSourceDObjAnimationRuntime(), pobjs: createSourcePObjAnimationRuntime(),
    mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()}, {
    requestAObj(id, frame) {
      if (id === null) {requestSourceAObj(null, frame, rows[0]!.fobjs.effects); return;}
      const row = rows.find(row => row.aobjId === id);
      if (!row) throw Error('unbound descriptor fixture AObj');
      requestSourceAObj(row.aobj, frame, row.fobjs.effects);
    },
  });
  const ordering = createSourceJObjTrackOrderRuntime({joints, feedback,
    fobjs: {getFObj(aobjId, nodeId) {
      const row = rows.find(row => row.aobjId === aobjId);
      if (!row) throw Error('unbound descriptor fixture FObj owner');
      return row.fobjs.getNode(nodeId);
    }},
  });
  const request = () => rows.forEach(row => {
    ordering.promoteFirstTrack12(row.joint);
    check(row.aobj.fobjs === row.head && row.nodes.every((id, index) =>
      row.fobjs.getNode(id).next00 === (row.nodes[index + 1] ?? null)),
    'absent-track12 promotion preserves actual supported descriptor lists before mapped playback');
    requests.requestJoint(row.joint, 0, 1);
  });
  const run = () => mapping.animatePart(actor, 0, 0, 0, 2);
  return {joints, feedback, mapping, rows, actor, part, pose, request, run, callbacks};
}
export function runDescriptorAnimationSelfTest(): void {
  {
    const x = fixture(); let completionCalls = 0;
    x.joints.endCallbacks.counts.running = 9; x.joints.endCallbacks.counts.stopped = 7;
    x.joints.endCallbacks.state.head28 = x.joints.endCallbacks.createNode({next00: null,
      callback04: x.joints.endCallbacks.createCallback(() => {completionCalls++;})});
    x.request();
    for (const row of x.rows) for (const [i, id] of row.nodes.entries()) {
      const node = row.fobjs.getNode(id);
      check(node.cursor04 === row.streams[i]!.data && node.flags10 === 1 && node.frame1c === node.offset18,
        'actual AObj request initializes the descriptor-loaded cursor/state and signed start offset');
    }
    check(x.callbacks.length === 0 && x.joints.getJoint(x.rows[0]!.joint).rotation1c === 7 &&
      x.joints.endCallbacks.counts.running === 9 && x.joints.endCallbacks.counts.stopped === 7,
    'loading/requesting does not fake receiver calls or global accounting');
    const expected = [[0, 0, 14, 50, 11, 7, 0], [2, 2, 18, 54, 13, 7, 0],
      [4, 4, 22, 58, 14, 8, 0], [4, 6, 22, 62, 14, 9, 1], [4, 6, 22, 62, 14, 9, 1]];
    for (const [firstFrame, secondFrame, firstX, secondX, running, stopped, complete] of expected) {
      x.run();
      check(x.rows[0]!.aobj.frame === firstFrame && x.rows[1]!.aobj.frame === secondFrame &&
        x.pose(1).translation.x === firstX && x.pose(2).translation.x === secondX && x.part.frame0c === secondFrame &&
        x.part.complete2e === complete && x.joints.endCallbacks.counts.running === running &&
        x.joints.endCallbacks.counts.stopped === stopped && completionCalls === 0,
      'descriptor-loaded real streams advance mapped pose/frame/latch and preserve single-joint shared accounting');
    }
    check(x.pose(1).translation.y === 28 && x.pose(1).translation.z === 38 &&
      x.pose(2).translation.y === 72 && x.pose(2).translation.z === 82 && x.pose(1).quaternion.w === 1 && x.pose(2).quaternion.w === 1,
    'all six descriptor tracks drive rotation and translation before actual analytic fixture pose output');
    check(x.rows.every(row => x.joints.getJoint(row.joint).rotation1c === 0 && x.joints.getJoint(row.joint).rotation20 === 0 &&
      x.joints.getJoint(row.joint).rotation24 === 0 && (x.joints.getJoint(row.joint).flags14 & 0x40) !== 0),
    'real loaded rotation streams replace nonzero initial Euler values and mark transforms dirty');
  }
  {
    const x = fixture();
    for (const row of x.rows) for (const id of row.descriptors) Object.assign(row.loader.getDescriptor(id),
      {next00: null, start08: 0.1, track0c: 99, data10: Symbol('changed unused descriptor data'), length04: 0});
    x.request(); x.run();
    check(x.pose(1).translation.x === 14 && x.pose(2).translation.x === 50 && x.part.frame0c === 0,
      'loaded fields and list links are copied rather than read live from descriptors during playback');
  }
  for (const kind of ['badTrack', 'foreignData', 'truncatedData'] as const) {
    const x = fixture({[kind]: true}); x.request();
    const message = kind === 'badTrack' ? 'unsupported' : kind === 'foreignData' ? 'non-owned stream' : 'truncated wait';
    rejects(x.run, message);
    const second = x.joints.getJoint(x.rows[1]!.joint);
    check(x.pose(1).translation.x === 14 && x.pose(1).quaternion.w === 1 && x.part.frame0c === 0 &&
      second.translation38 === 50 && second.translation3c === 60 && second.translation40 === -300 &&
      x.pose(2).translation.x === -1 && x.pose(2).quaternion.w === 7 &&
      x.joints.endCallbacks.counts.running === 1 && x.joints.endCallbacks.counts.stopped === 0,
    'late actual receiver/data refusal retains earlier owner feedback and current scalar prefix, but no current pose/count');
    if (kind === 'truncatedData') {
      const last = x.rows[1]!.fobjs.getNode(x.rows[1]!.nodes[5]!);
      check(last.length0c === 5 && x.rows[1]!.fobjs.cursorOffset(last.base08!, last.cursor04!) === 2,
        'descriptor loader copies declared length without reading bytes; real decoder preserves two consumed bytes at truncation');
    }
  }
  console.log('[descriptor-animation] PASS: owned descriptors through real request-by-flags, packed streams and actor mapped pose/frame feedback; explicit zero-Euler fixture, no AObj allocator/archive or original replay');
}
