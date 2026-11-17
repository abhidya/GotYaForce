import {createSourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import {AOBJ_STOPPED, AOBJ_REQUEST, createSourceAObj, requestSourceAObj, interpretSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[requested-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let message = ''; try {run();} catch (e) {message = String(e);}
  check(message.includes(expected), `expected ${expected}, got ${message || 'success'}`);
}
function fixture() {
  const joints = createSourceJObjAnimationRuntime(), dobjs = createSourceDObjAnimationRuntime();
  const pobjs = createSourcePObjAnimationRuntime(), mobjs = createSourceMObjAnimationRuntime(), tobjs = createSourceTObjAnimationRuntime();
  const makeJoint = (flags14 = 0) => joints.createJoint({sibling08: null, child10: null, flags14,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: -1, translation3c: -2, translation40: -3},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  const root = makeJoint(), child = makeJoint(), sibling = makeJoint(), parent = makeJoint(0x40);
  joints.getJoint(root).child10 = child; joints.getJoint(root).sibling08 = sibling; joints.getBinding(root).parent0c = parent;
  const texture = () => tobjs.createTexture({flags4c: 0x1234567, rotation18: 0, rotation1c: 0, rotation20: 0,
    scale28: 1, scale2c: 1, translation34: -5, translation38: -6}, {next08: null, aobj64: null, classUpdate48: null});
  const texture1 = texture(), texture2 = texture(); tobjs.getBinding(texture1).next08 = texture2;
  const polygon2 = pobjs.createPObj({next04: null, aobj18: null, classUpdate48: null});
  const polygon1 = pobjs.createPObj({next04: polygon2, aobj18: null, classUpdate48: null});
  const material = mobjs.createMObj({tobj08: texture1, aobj14: null, classUpdate4c: null});
  const display = dobjs.createDObj({next04: null, mobj08: material, pobj0c: polygon1, aobj10: null, classUpdate44: null});
  joints.getBinding(root).dobj18 = display;
  const requestEvents: {name: string; frame: number}[] = [], receiverEvents: string[] = [];
  const targets = [root, display, polygon1, polygon2, material, texture1, texture2, Symbol('RObj owner'), child, sibling];
  const names = ['joint', 'display', 'polygon1', 'polygon2', 'material', 'texture1', 'texture2', 'relation', 'child', 'sibling'];
  const rows = targets.map((owner, index) => {
    const fobjs = createSourceFObjScalarCallbackRuntime(owner), loader = createSourceFObjDescriptorRuntime(fobjs);
    const data = fobjs.createData(Uint8Array.from([2, 10 + index, 4, 2, 18 + index]));
    const descriptor = loader.createDescriptor({next00: null, length04: 5, start08: index % 2,
      track0c: owner === root ? 5 : owner === texture1 ? 2 : owner === texture2 ? 8 : 0,
      format0d: 0x80, format0e: 0x80, data10: data});
    const node = loader.loadDescriptors(descriptor)!, header = fobjs.getNode(node);
    // Explicit previously-used interpreter state. Actual request must reset it.
    Object.assign(header, {cursor04: fobjs.cursorAt(data, 2), flags10: 0x66, byte11: 5, byte12: 6,
      half16: 7, half1a: 8, frame1c: 9, value20: 10, value24: 11, value28: 12, value2c: 13});
    const aobj = createSourceAObj({flags: AOBJ_STOPPED, frame: 99, rewind: 0, end: 10, rate: 2, fobjs: node});
    const id = Symbol(names[index]), name = names[index]!;
    let callback: symbol | null = null;
    if (owner === root || owner === texture1 || owner === texture2) callback = fobjs.createCallback((target, track, value) => {
      receiverEvents.push(name); if (target === root) joints.updateScalar(target, track, value); else tobjs.updateScalar(target, track, value);
    });
    if (owner === root || owner === child || owner === sibling) {
      joints.getBinding(owner).aobj7c = id; joints.getBinding(owner).classUpdate50 = callback;
    } else if (owner === display) dobjs.getDObj(owner).aobj10 = id;
    else if (owner === material) mobjs.getMObj(owner).aobj14 = id;
    else if (owner === texture1 || owner === texture2) {
      tobjs.getBinding(owner).aobj64 = id; tobjs.getBinding(owner).classUpdate48 = callback;
    } else if (owner === polygon1 || owner === polygon2) pobjs.getPObj(owner).aobj18 = id;
    return {owner, name, fobjs, loader, data, node, header, aobj, id, callback};
  });
  const requests = createSourceAnimationRequestRuntime({joints, dobjs, pobjs, mobjs, tobjs}, {
    requestAObj(id, frame) {
      if (id === null) {requestSourceAObj(null, frame, rows[0]!.fobjs.effects); return;}
      const row = rows.find(row => row.id === id); if (!row) throw Error('unbound actual AObj request');
      requestSourceAObj(row.aobj, frame, row.fobjs.effects); requestEvents.push({name: row.name, frame});
    },
  });
  const relation = requests.createRObj({next00: null, aobj18: rows[7]!.id});
  // Only request fields are modeled for RObj. No RObj interpreter/receiver is invented.
  joints.getBinding(root).robj80 = relation;
  let endCalls = 0;
  joints.endCallbacks.counts.running = 13; joints.endCallbacks.counts.stopped = 17;
  joints.endCallbacks.state.head28 = joints.endCallbacks.createNode({next00: null,
    callback04: joints.endCallbacks.createCallback(() => {endCalls++;})});
  const unchanged = (index: number) => {
    const row = rows[index]!;
    check(row.aobj.flags === AOBJ_STOPPED && row.aobj.frame === 99 && row.header.flags10 === 0x66 &&
      row.header.frame1c === 9 && row.fobjs.cursorOffset(row.data, row.header.cursor04!) === 2 && row.header.value20 === 10,
    `excluded ${row.name} AObj/FObj remains unchanged`);
  };
  const requested = (index: number, frame: number, headerFlags = 0x21) => {
    const row = rows[index]!;
    check(row.aobj.flags === AOBJ_REQUEST && row.aobj.frame === frame && row.header.cursor04 === row.data &&
      row.header.flags10 === headerFlags && row.header.frame1c === frame + index % 2 && row.header.byte11 === 0 && row.header.byte12 === 0 &&
      row.header.half16 === 0 && row.header.half1a === 0 && row.header.value20 === 0 && row.header.value24 === 0 &&
      row.header.value28 === 0 && row.header.value2c === 0, `real ${row.name} request stores and FObj reset at frame ${frame}: AObj ${row.aobj.flags}/${row.aobj.frame}, FObj ${row.header.flags10}/${row.header.frame1c}`);
  };
  return {joints, dobjs, pobjs, mobjs, tobjs, requests, root, display, polygon1, polygon2, material, texture1, texture2,
    relation, rows, requestEvents, receiverEvents, unchanged, requested, get endCalls() {return endCalls;}};
}
export function runRequestedAnimationSelfTest(): void {
  for (const [mask, indices] of [[0, []], [1, [0]], [4, [4]], [8, [2, 3]], [0x10, [5, 6]],
    [0x80, [7]], [0x9d, [0, 2, 3, 4, 5, 6, 7]]] as const) {
    const x = fixture(); x.requests.requestJoint(x.root, 2, mask);
    check(x.requestEvents.map(e => e.name).join() === indices.map(i => x.rows[i]!.name).join(), 'source mask and nested actual request order');
    for (let i = 0; i < x.rows.length; i++) {
      if ((indices as readonly number[]).includes(i)) x.requested(i, 2); else x.unchanged(i);
    }
    check(x.receiverEvents.length === 0 && x.joints.getJoint(x.root).translation38 === -1 &&
      x.joints.getJoint(x.root).flags14 === 0 && x.tobjs.getTexture(x.texture1).flags4c === 0x1234567 &&
      x.joints.endCallbacks.counts.running === 13 && x.joints.endCallbacks.counts.stopped === 17 && x.endCalls === 0,
    'request never interprets, checks dirty parent, walks JObj descendants, counts or invokes completion');
  }
  {
    const x = fixture(); x.requests.requestJoint(x.root, 2, 0x9d);
    for (const index of [0, 5, 6]) {
      const row = x.rows[index]!; interpretSourceAObj(row.aobj, row.callback, row.fobjs.effects, x.joints.endCallbacks.counts);
    }
    check(x.joints.getJoint(x.root).translation38 === 14 && x.tobjs.getTexture(x.texture1).translation34 === 21 &&
      x.tobjs.getTexture(x.texture2).rotation20 === 20 && x.receiverEvents.join() === 'joint,texture1,texture2',
    'requested real packed streams drive implemented joint and texture receivers only on later interpretation');
    check(x.joints.endCallbacks.counts.running === 16 && x.joints.endCallbacks.counts.stopped === 17 && x.endCalls === 0,
      'later interpretation, not request, performs actual shared accounting');
    x.requests.requestJoint(x.root, 0, 0x9d);
    for (const index of [0, 2, 3, 4, 5, 6, 7]) x.requested(index, 0, [0, 5, 6].includes(index) ? 1 : 0x21);
    check(x.joints.getJoint(x.root).translation38 === 14 && x.receiverEvents.length === 3 &&
      x.joints.endCallbacks.counts.running === 16, 'repeat request resets streams without updating receivers or resetting counts');
  }
  for (const gate of [0x20, 0x4000]) {
    const x = fixture(); x.joints.getJoint(x.root).flags14 = gate; x.requests.requestJoint(x.root, 2, 0x9d);
    check(x.requestEvents.map(e => e.name).join() === 'joint,relation', 'DObj gate leaves current JObj and RObj requests active');
    for (let i = 0; i < x.rows.length; i++) if (i === 0 || i === 7) x.requested(i, 2); else x.unchanged(i);
  }
  {
    const x = fixture(), bad = x.rows[6]!;
    Object.defineProperty(bad.header, 'value24', {writable: false});
    rejects(() => x.requests.requestJoint(x.root, 2, 0x9d), 'value24: non-writable');
    check(x.requestEvents.map(e => e.name).join() === 'joint,polygon1,polygon2,material,texture1',
      'late actual FObj refusal preserves exact earlier request order and stops before RObj');
    for (const index of [0, 2, 3, 4, 5]) x.requested(index, 2);
    check(bad.aobj.frame === 2 && bad.aobj.flags === AOBJ_REQUEST && bad.header.flags10 === 0x66 &&
      bad.header.frame1c === 9 && bad.fobjs.cursorOffset(bad.data, bad.header.cursor04!) === 2,
    'failing real FObj preflight retains its already-written AObj frame/flags, but no FObj request stores');
    x.unchanged(1); x.unchanged(7);
    check(x.receiverEvents.length === 0 && x.joints.endCallbacks.counts.running === 13 && x.endCalls === 0,
      'failure does not fabricate receiver effects or counts');
  }
  {
    const x = fixture(), wide = 1 + 2 ** -25;
    rejects(() => x.requests.requestJoint(x.root, wide, 0x9d), 'float32 request operand');
    check(x.rows[0]!.aobj.frame === 1 && x.rows[0]!.aobj.flags === AOBJ_REQUEST && x.rows[0]!.header.frame1c === 9 &&
      x.requestEvents.length === 0, 'dispatcher forwards original wider double: real AObj stores f32 then real FObj refuses');
    x.unchanged(2); x.unchanged(7);
  }
  {
    const x = fixture(), wide = 1 + 2 ** -25;
    x.rows[0]!.aobj.fobjs = null; x.joints.getBinding(x.root).dobj18 = null; x.joints.getBinding(x.root).robj80 = null;
    x.requests.requestJoint(x.root, wide, 1);
    check(x.rows[0]!.aobj.frame === 1 && x.requestEvents.length === 1 && x.requestEvents[0]!.frame === wide,
      'real empty FObj chain accepts wider finite request and receives original double unchanged');
  }
  {
    const x = fixture(); x.requests.requestJoint(x.root, NaN, 0);
    check(x.requestEvents.length === 0, 'mask-zero traversal does not consume invalid frame');
    for (let i = 0; i < x.rows.length; i++) x.unchanged(i);
  }
  console.log('[requested-animation] PASS: real descriptor/AObj/FObj requests across owned dispatch tables, receiver continuation and failure prefixes; no complete actor setup, RObj receiver or original replay');
}
