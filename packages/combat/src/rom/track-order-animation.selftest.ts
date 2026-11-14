import {createSourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {AOBJ_NO_CALLBACK, AOBJ_REQUEST, AOBJ_STOPPED, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[track-order-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try {run();} catch (e) {diagnostic = String(e);}
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic || 'success'}`);
}
function fixture(receiver: 'observe' | 'joint' | 'silent') {
  const joints = createSourceJObjAnimationRuntime(), feedback = createSourceJointAnimationFeedbackRuntime(joints);
  const joint = joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -10, translation3c: -20, translation40: -30},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const fobjs = createSourceFObjScalarCallbackRuntime(joint), loader = createSourceFObjDescriptorRuntime(fobjs);
  const tracks = [5, 12, 6, 12, 7], bases = [10, 40, 20, 50, 30]; let descriptor: symbol | null = null;
  for (let i = tracks.length - 1; i >= 0; i--) {
    const data = fobjs.createData(Uint8Array.from([2, bases[i]!, 4, 2, bases[i]! + 8]));
    descriptor = loader.createDescriptor({next00: descriptor, length04: 5, start08: 0,
      track0c: tracks[i]!, format0d: 0x80, format0e: 0x80, data10: data});
  }
  const head = loader.loadDescriptors(descriptor), nodes: symbol[] = []; let current = head;
  while (current !== null) {nodes.push(current); current = fobjs.getNode(current).next00;}
  // Explicit attached factory state, not AObjAlloc, archive lookup or AddAnim.
  const aobjId = feedback.createAObj({flags: AOBJ_STOPPED | (receiver === 'silent' ? AOBJ_NO_CALLBACK : 0),
    frame: 99, rewind: 0, end: 3, rate: 2, fobjs: head});
  const aobj = feedback.getAObj(aobjId), callbacks: {owner: symbol | null; track: number; value: number}[] = [];
  joints.getBinding(joint).aobj7c = aobjId;
  joints.getBinding(joint).classUpdate50 = fobjs.createCallback((owner, track, value) => {
    callbacks.push({owner, track, value});
    // Observation is a real packed-interpreter callback test, NOT an installed
    // track12 JObj receiver. The joint case must retain its real refusal.
    if (receiver !== 'observe') joints.updateScalar(owner, track, value);
  });
  const ordering = createSourceJObjTrackOrderRuntime({joints, feedback,
    fobjs: {getFObj(id, nodeId) {if (id !== aobjId) throw Error('unbound FObj owner'); return fobjs.getNode(nodeId);}}});
  const requests = createSourceAnimationRequestRuntime({joints, dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()}, {
    requestAObj(id, frame) {
      if (id !== null && id !== aobjId) throw Error('unbound request AObj');
      requestSourceAObj(id === null ? null : aobj, frame, fobjs.effects);
    },
  });
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      if (id !== aobjId || owner !== joint) throw Error('unbound animation owner');
      interpretSourceAObj(aobj, callback, fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(id) {if (id !== null) throw Error('unsupported RObj');},
    animateDObjs(id) {if (id !== null) throw Error('unsupported DObj');},
  };
  const promote = () => ordering.promoteFirstTrack12(joint);
  const request = () => requests.requestJoint(joint, 2, 1);
  const run = () => joints.animateJoint(joint, effects);
  return {joints, joint, fobjs, aobj, nodes, callbacks, promote, request, run};
}
export function runTrackOrderAnimationSelfTest(): void {
  {
    const x = fixture('observe'); x.promote();
    check(x.aobj.fobjs === x.nodes[1] && x.fobjs.getNode(x.nodes[1]!).next00 === x.nodes[0] &&
      x.fobjs.getNode(x.nodes[0]!).next00 === x.nodes[2] && x.fobjs.getNode(x.nodes[2]!).next00 === x.nodes[3] &&
      x.callbacks.length === 0 && x.aobj.frame === 99 && x.nodes.every(id => x.fobjs.getNode(id).cursor04 === null),
    'promotion changes actual descriptor-loaded links only, first12 only; no request, callback or clock work');
    x.request(); x.run();
    check(x.callbacks.map(row => row.track).join() === '12,5,6,12,7' &&
      x.callbacks.map(row => row.value).join() === '44,14,24,54,34' && x.callbacks.every(row => row.owner === x.joint) &&
      x.aobj.frame === 2 && x.joints.endCallbacks.counts.running === 1 && x.joints.endCallbacks.counts.stopped === 0,
    'real requested packed streams emit first12 before translation and the later12, preserving actual values and ownership');
    x.promote(); x.run();
    check(x.callbacks.slice(5).map(row => row.track).join() === '12,5,6,12,7' &&
      x.callbacks.slice(5).map(row => row.value).join() === '48,18,28,58,38' && x.aobj.frame === 4 &&
      x.aobj.flags === AOBJ_STOPPED && x.joints.endCallbacks.counts.running === 1 && x.joints.endCallbacks.counts.stopped === 1,
    'repeat already-head promotion preserves real traversal, overshoot and stopped accounting');
    check(x.joints.getJoint(x.joint).translation38 === -10,
      'recording observer is not advertised as track12-capable joint receiver');
  }
  {
    const x = fixture('joint'); x.promote(); x.request(); rejects(x.run, 'unsupported scalar track');
    check(x.callbacks.length === 1 && x.callbacks[0]!.track === 12 && x.callbacks[0]!.value === 44 &&
      x.joints.getJoint(x.joint).translation38 === -10 && x.joints.getJoint(x.joint).translation3c === -20 &&
      x.joints.getJoint(x.joint).translation40 === -30 && (x.aobj.flags & AOBJ_REQUEST) === 0 &&
      x.aobj.frame === 2 && x.joints.endCallbacks.counts.running === 0 && x.joints.endCallbacks.counts.stopped === 0 &&
      x.fobjs.getNode(x.nodes[0]!).cursor04 === x.fobjs.getNode(x.nodes[0]!).base08 &&
      x.fobjs.getNode(x.nodes[0]!).byte12 === 0,
    'actual unsupported track12 receiver fails before later stream decode/translation and accounting; request prefix survives');
  }
  {
    const x = fixture('silent'); x.promote(); x.request(); x.run(); x.run();
    check(x.callbacks.length === 0 && x.aobj.frame === 4 && x.aobj.flags === (AOBJ_STOPPED | AOBJ_NO_CALLBACK) &&
      x.joints.endCallbacks.counts.running === 1 && x.joints.endCallbacks.counts.stopped === 1 &&
      x.nodes.every(id => x.fobjs.getNode(id).byte12 === 2) && x.joints.getJoint(x.joint).translation38 === -10,
    'actual source silent flag permits packed timing without inventing a track12 receiver or joint writes');
  }
  console.log('[track-order-animation] PASS: descriptor-owned first12 ordering through actual packed callbacks and silent timing, plus real JObj receiver refusal; no full attachment or track12 receiver');
}
