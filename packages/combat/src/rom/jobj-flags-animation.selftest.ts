import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {AOBJ_REQUEST, AOBJ_STOPPED, createSourceAObj, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[jobj-flags-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try {run();} catch (e) {diagnostic = String(e);}
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic || 'success'}`);
}
function fixture(maxFlagNodes?: number) {
  const joints = createSourceJObjAnimationRuntime(4096, 4096, 4096, maxFlagNodes);
  const ids = Array.from({length: 5}, () => joints.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -1, translation3c: -2, translation40: -3},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null}));
  const [root, child, leaf, sibling, excluded] = ids as [symbol, symbol, symbol, symbol, symbol];
  const headers = ids.map(id => joints.getJoint(id));
  headers[0]!.child10 = child; headers[0]!.sibling08 = excluded;
  headers[1]!.child10 = leaf; headers[1]!.sibling08 = sibling;
  joints.getBinding(child).parent0c = root; joints.getBinding(leaf).parent0c = child;
  joints.getBinding(sibling).parent0c = root;
  const callbacks: number[] = [], hook: {duringRoot?: () => void} = {};
  const rows = ids.map((owner, index) => {
    const fobjs = createSourceFObjScalarCallbackRuntime(owner), loader = createSourceFObjDescriptorRuntime(fobjs);
    const base = 10 * (index + 1), data = fobjs.createData(Uint8Array.from([2, base, 4, 2, base + 8]));
    const descriptor = loader.createDescriptor({next00: null, length04: 5, start08: 0, track0c: 5,
      format0d: 0x80, format0e: 0x80, data10: data});
    const node = loader.loadDescriptors(descriptor)!;
    const aobj = createSourceAObj({flags: AOBJ_STOPPED, frame: 99, rewind: 0, end: 20, rate: 2, fobjs: node});
    const id = Symbol('explicit owned AObj binding'); joints.getBinding(owner).aobj7c = id;
    joints.getBinding(owner).classUpdate50 = fobjs.createCallback((joint, track, value) => {
      callbacks.push(index); joints.updateScalar(joint, track, value); if (owner === root) hook.duringRoot?.();
    });
    return {id, owner, aobj, fobjs, node};
  });
  let endCalls = 0;
  joints.endCallbacks.state.head28 = joints.endCallbacks.createNode({next00: null,
    callback04: joints.endCallbacks.createCallback(() => {endCalls++;})});
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(id, owner, callback) {
      const row = rows.find(row => row.id === id && row.owner === owner);
      if (!row) throw Error('unbound actual AObj');
      interpretSourceAObj(row.aobj, callback, row.fobjs.effects, joints.endCallbacks.counts);
    },
    animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');},
    animateDObjs(list) {if (list !== null) throw Error('unsupported DObj');},
  };
  const requests = createSourceAnimationRequestRuntime({joints, dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()}, {
    requestAObj(id, frame) {
      if (id === null) {requestSourceAObj(null, frame, rows[0]!.fobjs.effects); return;}
      const row = rows.find(row => row.id === id); if (!row) throw Error('unbound actual request');
      requestSourceAObj(row.aobj, frame, row.fobjs.effects);
    },
  });
  const request = () => {
    // Independently prepare the excluded-root-sibling sentinel. The real tree
    // request below must not visit it; its pending request also survives playback.
    const sentinel = rows[4]!; requestSourceAObj(sentinel.aobj, 0, sentinel.fobjs.effects);
    requests.requestJointTree(root, 0, 1);
  };
  const run = () => joints.animateTree(root, effects);
  return {joints, root, child, leaf, sibling, excluded, headers, rows, callbacks, hook, request, run, get endCalls() {return endCalls;}};
}
export function runJObjFlagsAnimationSelfTest(): void {
  {
    const x = fixture(); x.joints.setFlags(x.root, 8);
    check(x.headers.map(h => h.flags14).join() === '72,64,64,64,0' && x.callbacks.length === 0 &&
      x.rows.every(row => row.aobj.frame === 99 && row.fobjs.getNode(row.node).cursor04 === null) && x.endCalls === 0,
    'single flag8 helper actually dirties descendants on shared headers without clocks, stream requests or callbacks');
    x.request(); x.run();
    check(x.callbacks.join() === '0,1,2,3' && x.headers.map(h => h.translation38).join() === '10,20,30,40,-1' &&
      x.joints.endCallbacks.counts.running === 4 && x.rows[4]!.aobj.flags === AOBJ_REQUEST,
    'actual packed tree playback uses shared dirty flags, excludes root sibling and leaves its request pending');
    x.joints.setFlagsAll(x.root, 0x1000);
    check(x.headers.map(h => h.flags14).join() === '4168,64,64,64,0', 'new root prune stops the same flag traversal');
    x.callbacks.length = 0; x.run();
    check(x.callbacks.join() === '0' && x.rows.map(row => row.aobj.frame).join() === '2,0,0,0,0' &&
      x.headers[0]!.translation38 === 14 && x.joints.endCallbacks.counts.running === 1,
    'actual animation subsequently honors flag-created pruning and preserves child clocks');
    x.joints.clearFlagsAll(x.root, 0x1000); x.joints.setFlagsAll(x.root, 0x10);
    check(x.headers.map(h => h.flags14).join() === '88,80,80,80,0', 'clearing prune opens descendants for actual flag stores');
    x.callbacks.length = 0; x.run();
    check(x.callbacks.join() === '0,1,2,3' && x.rows.map(row => row.aobj.frame).join() === '4,2,2,2,0' &&
      x.headers.map(h => h.translation38).join() === '18,24,34,44,-1' && x.joints.endCallbacks.counts.running === 4 && x.endCalls === 0,
    'visibility flag alone does not suppress source animation; no renderer or track12 threshold is inferred');
    x.joints.clearFlagsAll(x.root, 0x18);
    check(x.headers.map(h => h.flags14).join() === '64,64,64,64,0', 'clear helpers preserve source dirty writes and unrelated root sibling');
  }
  {
    const x = fixture(); x.request(); x.hook.duringRoot = () => x.joints.setFlags(x.root, 0x1000); x.run();
    check(x.callbacks.join() === '0' && x.rows[1]!.aobj.flags === AOBJ_REQUEST &&
      x.rows[1]!.fobjs.getNode(x.rows[1]!.node).byte12 === 0 && x.joints.endCallbacks.counts.running === 1,
    'synchronous real scalar callback can set prune before current animation traversal reads child gate');
    delete x.hook.duringRoot; x.joints.clearFlagsAll(x.root, 0x1000); x.callbacks.length = 0; x.run();
    check(x.callbacks.join() === '0,1,2,3' && x.rows.map(row => row.aobj.frame).join() === '2,0,0,0,0',
      'cleared flag opens pending child requests without advancing their clocks prematurely');
  }
  {
    const x = fixture(); Object.defineProperty(x.headers[2]!, 'flags14', {writable: false});
    rejects(() => x.joints.setFlags(x.root, 8), 'non-writable');
    check(x.headers.map(h => h.flags14).join() === '64,64,0,0,0' && x.callbacks.length === 0 &&
      x.rows.every(row => row.aobj.frame === 99) && x.endCalls === 0,
    'actual dirty propagation failure preserves its prefix and prevents pending flag8 store or animation work');
  }
  {
    const x = fixture(1); rejects(() => x.joints.setFlagsAll(x.root, 1), 'flag inspected-node budget');
    check(x.headers.map(h => h.flags14).join() === '1,0,0,0,0',
      'animation factory forwards fourth flag budget without changing existing dirty/animation/end bounds');
  }
  console.log('[jobj-flags-animation] PASS: real dirty flags and source prune transitions control actual descriptor-packed tree playback; no attachment, track11/12 receiver or render activation');
}
