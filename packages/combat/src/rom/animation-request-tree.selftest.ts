import {createSourceAnimationRequestRuntime, type SourceAnimationRequestRuntime} from './animation-request.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourcePObjAnimationRuntime} from './pobj-animation.js';
import {createSourceMObjAnimationRuntime} from './mobj-animation.js';
import {createSourceTObjAnimationRuntime} from './tobj-animation.js';

function check(ok: boolean, message: string): void {if (!ok) throw Error(`[animation-request-tree-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
// Actual source-owned JObj records; synthetic request/getter adapters below
// exercise host traversal/fault order. They are NOT source user callbacks.
function fixture(maxNodes = 4096, maxTreeNodes?: number) {
  const joints = createSourceJObjAnimationRuntime();
  const s = {joints: {...joints}, dobjs: createSourceDObjAnimationRuntime(),
    pobjs: createSourcePObjAnimationRuntime(), mobjs: createSourceMObjAnimationRuntime(), tobjs: createSourceTObjAnimationRuntime()};
  const events: symbol[] = [], frames: number[] = [], reads: string[] = [];
  let hook: (id: symbol | null) => void = () => {};
  let getterHook: (kind: string, id: symbol) => void = () => {};
  s.joints.getJoint = function(id) {
    check(this === s.joints, 'captured getJoint this'); reads.push('joint'); getterHook('joint', id); return joints.getJoint(id);
  };
  s.joints.getBinding = function(id) {
    check(this === s.joints, 'captured getBinding this'); reads.push('binding'); getterHook('binding', id); return joints.getBinding(id);
  };
  const effects = {requestAObj(id: symbol | null, frame: number) {
    check(this === effects, 'captured effect this'); if (id !== null) events.push(id); frames.push(frame); hook(id);
  }};
  const r = createSourceAnimationRequestRuntime(s, effects, maxNodes, maxTreeNodes);
  const make = () => {
    const a = Symbol('synthetic request target');
    const j = joints.createJoint({sibling08: null, child10: null, flags14: 0,
      rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
      translation38: 0, translation3c: 0, translation40: 0},
    {parent0c: null, aobj7c: a, robj80: null, dobj18: null, classUpdate50: null});
    return {j, a, h: joints.getJoint(j), b: joints.getBinding(j)};
  };
  return {s, joints, r, effects, events, frames, reads, make,
    hook(fn: typeof hook) {hook = fn;}, getterHook(fn: typeof getterHook) {getterHook = fn;}};
}
export function runAnimationRequestTreeSelfTest(): void {
  for (const limit of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => fixture(4096, limit), 'maxTreeNodes');
  }
  {
    const x = fixture(), root = x.make(), a = x.make(), b = x.make(), c = x.make(), d = x.make();
    root.h.child10 = a.j; a.h.child10 = b.j; b.h.sibling08 = c.j; a.h.sibling08 = d.j;
    root.h.sibling08 = Symbol('excluded foreign root sibling');
    Object.defineProperty(root.h, 'sibling08', {writable: false});
    const frame = 1 + 2 ** -30;
    x.joints.endCallbacks.counts.running = 17; x.joints.endCallbacks.counts.stopped = 19;
    let ended = false;
    x.joints.endCallbacks.state.head28 = x.joints.endCallbacks.createNode({next00: null,
      callback04: x.joints.endCallbacks.createCallback(() => {ended = true;})});
    x.r.requestJointTree(root.j, frame, 1);
    check(x.events.length === 5 && x.events.every((id, i) => id === [root.a, a.a, b.a, c.a, d.a][i]), 'distinct identity preorder');
    check(x.frames.every(f => f === frame && f !== Math.fround(frame)), 'original double');
    check(!ended && x.joints.endCallbacks.counts.running === 17 && x.joints.endCallbacks.counts.stopped === 19,
      'requests never initialize counters or invoke end callbacks');
  }
  for (const before of [0, 0x1000]) {
    const x = fixture(), root = x.make(), a = x.make(), b = x.make();
    root.h.child10 = a.j; a.h.child10 = b.j; a.h.flags14 = before;
    x.hook(id => {if (id === a.a) a.h.flags14 = before === 0 ? 0x1000 : 0;});
    x.r.requestJointTree(root.j, 0, 1);
    check(x.events.length === (before === 0 ? 2 : 3), 'live prune opens/closes after request');
  }
  {
    const x = fixture(), root = x.make(), a = x.make(), b = x.make(), c = x.make();
    root.h.child10 = Symbol('replaced child'); a.h.child10 = b.j; a.h.sibling08 = Symbol('replaced sibling');
    x.hook(id => {if (id === root.a) root.h.child10 = a.j; if (id === b.a) a.h.sibling08 = c.j;});
    x.r.requestJointTree(root.j, -0, 1);
    check(x.events.length === 4 && x.events[3] === c.a && x.frames.every(f => Object.is(f, -0)), 'live links after nested work');
  }
  for (const bits of [0x20, 0x4000, 0x4020, 0x40, 0x00800000, 0x01000000, 0x00600000, 0x100, 0]) {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j; root.h.flags14 = bits;
    const pA = Symbol('PObj'), rA = Symbol('RObj');
    const p = x.s.pobjs.createPObj({next04: null, aobj18: pA, classUpdate48: null});
    root.b.dobj18 = x.s.dobjs.createDObj({next04: null, pobj0c: p, mobj08: null, aobj10: null, classUpdate44: null});
    root.b.robj80 = x.r.createRObj({next00: null, aobj18: rA});
    x.r.requestJointTree(root.j, 0, 0x89);
    check(x.events.includes(a.a) && x.events.includes(rA) && x.events.includes(pA) === ((bits & 0x4020) === 0),
      'display gate only skips DObjs; independent/dirty flags do not suppress request or descent');
  }
  {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    for (const n of [root, a]) {
      n.b.aobj7c = 7 as unknown as symbol; Object.defineProperty(n.b, 'aobj7c', {writable: false});
      n.h.translation38 = NaN; Object.defineProperty(n.h, 'translation38', {writable: false});
    }
    a.h.flags14 = 0x1000; a.h.child10 = 7 as unknown as symbol;
    Object.defineProperty(a.h, 'child10', {writable: false});
    x.r.requestJointTree(root.j, NaN, 0);
    check(x.events.length === 0 && x.reads.filter(v => v === 'joint').length === 4, 'mask0 traverses without unused AObj/scalar/frame/child admission');
  }
  for (const mask of [0, 1, 4, 8, 0x10, 0x80, 0x9d, 0xffffffff]) {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    const expected: symbol[] = [];
    for (const n of [root, a]) {
      const pa = Symbol('p'), ma = Symbol('m'), ta = Symbol('t'), ra = Symbol('r');
      const p = x.s.pobjs.createPObj({next04: null, aobj18: pa, classUpdate48: null});
      const t = x.s.tobjs.createTexture({flags4c: 0, rotation18: 0, rotation1c: 0, rotation20: 0,
        scale28: 1, scale2c: 1, translation34: 0, translation38: 0}, {next08: null, aobj64: ta, classUpdate48: null});
      const m = x.s.mobjs.createMObj({tobj08: t, aobj14: ma, classUpdate4c: null});
      n.b.dobj18 = x.s.dobjs.createDObj({next04: null, pobj0c: p, mobj08: m, aobj10: Symbol('unused DObj'), classUpdate44: null});
      n.b.robj80 = x.r.createRObj({next00: null, aobj18: ra});
      for (const [bit, target] of [[1, n.a], [8, pa], [4, ma], [0x10, ta], [0x80, ra]] as const) {
        if ((mask & bit) !== 0) expected.push(target);
      }
    }
    x.r.requestJointTree(root.j, 1 + 2 ** -30, mask);
    check(x.events.length === expected.length && x.events.every((id, i) => id === expected[i]), 'unchanged mask reaches every node and owner');
  }
  {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    const ra = Symbol('late RObj prune'); root.b.robj80 = x.r.createRObj({next00: null, aobj18: ra});
    x.hook(id => {if (id === ra) root.h.flags14 = 0x1000;});
    x.r.requestJointTree(root.j, 0, 0x81);
    check(x.events.length === 2 && x.events[1] === ra, 'prune reload follows RObj, not only JObj AObj');
  }
  for (const key of ['child10', 'sibling08'] as const) for (const fault of ['foreign', 'invalid', 'readonly'] as const) {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    if (fault === 'foreign') a.h[key] = Symbol('foreign');
    else if (fault === 'invalid') a.h[key] = 7 as unknown as symbol;
    else Object.defineProperty(a.h, key, {writable: false});
    rejects(() => x.r.requestJointTree(root.j, 0, 1), fault === 'foreign' ? 'non-owned' : fault === 'invalid' ? 'opaque symbol' : 'non-writable');
    check(x.events.length === 2 && x.events[1] === a.a, 'late tree field fault preserves completed requests');
  }
  for (const cycle of ['self', 'ancestor', 'dag']) {
    const x = fixture(), root = x.make(), a = x.make(), b = x.make(); root.h.child10 = a.j;
    if (cycle === 'self') a.h.sibling08 = a.j;
    else if (cycle === 'ancestor') a.h.child10 = root.j;
    else {a.h.child10 = b.j; a.h.sibling08 = b.j;}
    rejects(() => x.r.requestJointTree(root.j, 0, 1), 'cycle/revisited');
    check(new Set(x.events).size === x.events.length && x.events.length === (cycle === 'dag' ? 3 : 2), 'no duplicate request');
  }
  {
    const x = fixture(1, 3), root = x.make(), a = x.make(), b = x.make(); root.h.child10 = a.j; a.h.child10 = b.j;
    const ro = x.r.createRObj({next00: null, aobj18: Symbol('shared RObj')});
    for (const n of [root, a, b]) n.b.robj80 = ro;
    x.r.requestJointTree(root.j, 0, 0x81);
    check(x.events.length === 6, 'separate list budget per invocation, independent tree budget');
    x.r.getRObj(ro).next00 = x.r.createRObj({next00: null, aobj18: Symbol('late RObj')}); x.events.length = 0;
    rejects(() => x.r.requestJointTree(root.j, 0, 0x81), 'RObj visit budget');
    check(x.events.length === 2, 'list exhaustion remains independent');
  }
  for (const [size, limit, expected] of [[4097, 4096, 4096], [12001, 12001, 12001]] as const) {
    const x = limit === 4096 ? fixture() : fixture(1, limit), root = x.make(); let tail = root;
    for (let i = 1; i < size; i++) {const next = x.make(); tail.h.child10 = next.j; tail = next;}
    if (size > limit) rejects(() => x.r.requestJointTree(root.j, 0, 1), 'tree visit budget');
    else x.r.requestJointTree(root.j, 0, 1);
    check(x.events.length === expected, 'default tree bound or explicit deep iterative traversal');
  }
  {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    x.s.joints.getJoint = () => {throw Error('replaced getJoint');};
    x.s.joints.getBinding = () => {throw Error('replaced getBinding');};
    x.effects.requestAObj = () => {throw Error('replaced effect');};
    x.r.requestJointTree(root.j, 0, 1); check(x.events.length === 2, 'factory-captured methods fixed for tree');
  }
  for (const method of ['requestJointTree', 'requestJoint', 'requestRObjs', 'requestDObjs', 'requestPObjs', 'requestMObj', 'requestTObjs'] as const) {
    const x = fixture(), root = x.make(), a = x.make(); root.h.child10 = a.j;
    x.hook(() => {
      x.r[method](null, NaN, NaN);
      try {x.r[method](root.j, 0, 0);} catch { /* poison must survive catch */ }
    });
    rejects(() => x.r.requestJointTree(root.j, 0, 1), 'reentry was caught');
    check(x.reads.length === 1 && x.events.length === 1, 'effect reentry stops before flags/child/sibling lookup');
    x.hook(() => {}); x.events.length = 0; x.r.requestJointTree(root.j, 0, 1);
    check(x.events.length === 2, 'recovery after poisoned pass');
  }
  for (const kind of ['joint', 'binding']) {
    const x = fixture(), root = x.make();
    x.getterHook(k => {if (k === kind) {try {x.r.requestJointTree(root.j, 0, 0);} catch { /* caught */ }}});
    rejects(() => x.r.requestJointTree(root.j, 0, 1), 'reentry was caught');
    check(x.events.length === (kind === 'binding' ? 0 : 1), 'getter poison preserves prefix and prevents returned record consumption');
  }
  {
    const x = fixture(), root = x.make(), child = x.make(); root.h.child10 = child.j;
    let jointReads = 0;
    x.getterHook(kind => {
      if (kind === 'joint' && ++jointReads === 2) {
        try {x.r.requestJointTree(root.j, 0, 1);} catch { /* post-request lookup poison survives */ }
      }
    });
    rejects(() => x.r.requestJointTree(root.j, 0, 1), 'reentry was caught');
    check(jointReads === 2 && x.events.length === 1 && x.events[0] === root.a,
      'post-request tree gate lookup reentry prevents child request');
    x.getterHook(() => {}); x.events.length = 0; x.r.requestJointTree(root.j, 0, 1);
    check(x.events.length === 2, 'post-request lookup poison recovers on a new pass');
  }
  {
    const x = fixture(); x.r.requestJointTree(null, NaN, NaN);
    rejects(() => x.r.requestJointTree(Symbol('foreign'), 0, 1), 'non-owned');
    for (const flags of [-1, NaN, Infinity, 0.1, 0x100000000]) rejects(() => x.r.requestJointTree(Symbol(), 0, flags), 'uint32');
    check(x.reads.length === 1 && x.events.length === 0, 'null and invalid flags bypass getters');
    // Existing public non-tree entry also shares the tree's poison guard.
    const root = x.make(); const r: SourceAnimationRequestRuntime = x.r;
    x.hook(() => {try {r.requestJointTree(root.j, 0, 1);} catch { /* caught */ }});
    rejects(() => r.requestJoint(root.j, 0, 1), 'reentry was caught');
  }
}
