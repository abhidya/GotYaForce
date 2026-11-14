import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceAObj, requestSourceAObj, interpretSourceAObj, AOBJ_REQUEST, AOBJ_STOPPED} from './aobj-clock.js';
function check(ok: boolean, why: string): void {if (!ok) throw Error(`[request-tree-playback-test] ${why}`);}
function rejects(fn: () => unknown, expected: string): void {
  let error = ''; try {fn();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error || 'success'}`);
}
function fixture(treeLimit = 4096) {
  const joints = createSourceJObjAnimationRuntime();
  const owners = Array.from({length: 5}, () => joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -1, translation3c: -2, translation40: -3},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null}));
  const [root, child, leaf, sibling, excluded] = owners as [symbol, symbol, symbol, symbol, symbol];
  joints.getJoint(root).child10 = child; joints.getJoint(root).sibling08 = excluded;
  joints.getJoint(child).child10 = leaf; joints.getJoint(child).sibling08 = sibling;
  joints.getBinding(child).parent0c = root; joints.getBinding(leaf).parent0c = child;
  joints.getBinding(sibling).parent0c = root;
  const callbackOrder: number[] = [], requestOrder: number[] = [];
  const rows = owners.map((owner, index) => {
    const fobjs = createSourceFObjScalarCallbackRuntime(owner), loader = createSourceFObjDescriptorRuntime(fobjs);
    const base = (index + 1) * 10, bytes = Uint8Array.from([2, base, 4, 2, base + 8]);
    const data = fobjs.createData(bytes);
    const descriptor = loader.createDescriptor({next00: null, length04: bytes.length, start08: 0,
      track0c: 5, format0d: 0x80, format0e: 0x80, data10: data});
    const node = loader.loadDescriptors(descriptor)!;
    const aobj = createSourceAObj({flags: AOBJ_STOPPED, frame: 99, rewind: 0, end: 20, rate: 2, fobjs: node});
    const identity = Symbol('explicit AObj binding'); joints.getBinding(owner).aobj7c = identity;
    joints.getBinding(owner).classUpdate50 = fobjs.createCallback((target, track, value) => {
      callbackOrder.push(index); joints.updateScalar(target, track, value);
    });
    return {owner, identity, aobj, fobjs, data, node};
  });
  const requests = createSourceAnimationRequestRuntime({joints, dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()}, {
    requestAObj(id, frame) {
      if (id === null) {requestSourceAObj(null, frame, rows[0]!.fobjs.effects); return;}
      const index = rows.findIndex(row => row.identity === id); if (index < 0) throw Error('unbound AObj request');
      const row = rows[index]!; requestOrder.push(index); requestSourceAObj(row.aobj, frame, row.fobjs.effects);
    },
  }, 4096, treeLimit);
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      const row = rows.find(row => row.identity === id && row.owner === owner);
      if (!row) throw Error('unbound actual interpreter');
      interpretSourceAObj(row.aobj, callback, row.fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(id) {if (id !== null) throw Error('unsupported RObj animation');},
    animateDObjs(id) {if (id !== null) throw Error('unsupported DObj animation');},
  };
  let endCalls = 0;
  joints.endCallbacks.counts.running = 7; joints.endCallbacks.counts.stopped = 8;
  joints.endCallbacks.state.head28 = joints.endCallbacks.createNode({next00: null,
    callback04: joints.endCallbacks.createCallback(() => {endCalls++;})});
  const request = (frame: number, flags = 1) => requests.requestJointTree(root, frame, flags);
  const animate = () => joints.animateTree(root, effects);
  return {joints, requests, root, child, leaf, sibling, excluded, rows, callbackOrder, requestOrder, request, animate,
    get endCalls() {return endCalls;}};
}
export function runAnimationRequestTreePlaybackSelfTest(): void {
  {
    const t = fixture(); t.request(2);
    check(t.requestOrder.join() === '0,1,2,3' && t.callbackOrder.length === 0 && t.endCalls === 0 &&
      t.joints.endCallbacks.counts.running === 7 && t.joints.endCallbacks.counts.stopped === 8,
      'tree request performs actual AObj/FObj resets in preorder without interpretation or completion work');
    for (const row of t.rows.slice(0, 4)) {
      const node = row.fobjs.getNode(row.node);
      check(row.aobj.flags === AOBJ_REQUEST && row.aobj.frame === 2 && node.frame1c === 2 &&
        node.cursor04 === row.data && node.byte12 === 0 && node.flags10 === 1 &&
        t.joints.getJoint(row.owner).translation38 === -1, 'actual request resets packed decoder but does not write pose');
    }
    check(t.rows[4]!.aobj.flags === AOBJ_STOPPED && t.rows[4]!.aobj.frame === 99 &&
      t.rows[4]!.fobjs.getNode(t.rows[4]!.node).cursor04 === null, 'root sibling never requested');
    t.animate();
    check(t.callbackOrder.join() === '0,1,2,3' && t.rows.map(row => t.joints.getJoint(row.owner).translation38).join() === '14,24,34,44,-1' &&
      t.joints.endCallbacks.counts.running === 4 && t.joints.endCallbacks.counts.stopped === 0 && t.endCalls === 0,
      'actual tree playback consumes requested packed states through source JObj scalar receivers');
    t.requestOrder.length = 0; t.callbackOrder.length = 0; t.request(1); t.animate();
    check(t.requestOrder.join() === '0,1,2,3' && t.callbackOrder.join() === '0,1,2,3' &&
      t.rows.map(row => t.joints.getJoint(row.owner).translation38).join() === '12,22,32,42,-1',
      'repeat whole-tree request rewinds actual decoded lists, not a cached or interpolated pose');
  }
  {
    const t = fixture(); t.joints.setFlags(t.child, 0x1000); t.request(2);
    check(t.requestOrder.join() === '0,1,3' && t.rows[2]!.aobj.frame === 99 && t.rows[2]!.aobj.flags === AOBJ_STOPPED,
      'source request prune skips only child descendants, not child siblings');
    t.animate();
    check(t.callbackOrder.join() === '0,1,3' && t.joints.getJoint(t.leaf).translation38 === -1, 'matching tree prune controls actual later playback');
    t.joints.clearFlags(t.child, 0x1000); t.requestOrder.length = 0; t.callbackOrder.length = 0;
    t.request(1); t.animate();
    check(t.requestOrder.join() === '0,1,2,3' && t.callbackOrder.join() === '0,1,2,3' && t.joints.getJoint(t.leaf).translation38 === 32,
      'reopened subtree receives its own actual stream request before playback');
  }
  {
    const t = fixture(); t.request(NaN, 0);
    check(t.requestOrder.length === 0 && t.rows.every(row => row.aobj.frame === 99), 'mask zero traverses without numeric admission or AObj resets');
    t.joints.getJoint(t.child).child10 = Symbol('foreign reached child');
    rejects(() => t.request(NaN, 0), 'non-owned');
  }
  {
    const t = fixture(); t.rows[2]!.fobjs.getNode(t.rows[2]!.node).offset18 = 0.5;
    rejects(() => t.request(2), 'offset18');
    check(t.requestOrder.join() === '0,1,2' && t.rows[0]!.aobj.flags === AOBJ_REQUEST &&
      t.rows[1]!.fobjs.getNode(t.rows[1]!.node).frame1c === 2 && t.rows[2]!.aobj.flags === AOBJ_REQUEST &&
      t.rows[2]!.aobj.frame === 2 && t.rows[2]!.fobjs.getNode(t.rows[2]!.node).cursor04 === null &&
      t.rows[3]!.aobj.frame === 99 && t.callbackOrder.length === 0,
      'late actual decoder reset refusal retains earlier tree requests and current AObj prefix, not later sibling');
  }
  {
    const t = fixture(2); rejects(() => t.request(2), 'budget');
    check(t.requestOrder.join() === '0,1' && t.rows[2]!.aobj.frame === 99 && t.rows[3]!.aobj.frame === 99,
      'tree budget stops before next actual request and preserves completed root/child resets');
  }
  {
    const t = fixture(); rejects(() => t.request(0.1), 'float32 request operand');
    check(t.requestOrder.join() === '0' && t.rows[0]!.aobj.frame === Math.fround(0.1) &&
      t.rows[0]!.fobjs.getNode(t.rows[0]!.node).cursor04 === null && t.rows[1]!.aobj.frame === 99,
      'tree forwards original double to actual AObj/FObj boundary without coercing it');
  }
}
