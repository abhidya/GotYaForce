import {createSourceJObjAnimationRuntime, type SourceJObjAnimationRuntime,
  type SourceJObjAnimationEffects} from './jobj-animation.js';
import type {SourceJObjScalarHeader} from './jobj-update.js';
import {createSourceAObj, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[jobj-tree] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
function joint(r: SourceJObjAnimationRuntime, patch: Partial<SourceJObjScalarHeader> = {}) {
  const id = r.createJoint({sibling08: null, child10: null, flags14: 0,
    rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
    translation38: 0, translation3c: 0, translation40: 0, ...patch},
  {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
  return {id, n: r.getJoint(id), b: r.getBinding(id)};
}
const empty: SourceJObjAnimationEffects = {
  interpretAObj() {}, animateRObjs() {}, animateDObjs() {},
}; // Explicit traversal test doubles, never production animation implementations.
export function runJObjTreeSelfTest(): void {
  for (const max of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => createSourceJObjAnimationRuntime(10, max), 'maxAnimationNodes');
  }
  {
    const r = createSourceJObjAnimationRuntime(); r.endCallbacks.counts.running = 11; r.endCallbacks.counts.stopped = 12;
    r.endCallbacks.state.head28 = Symbol('unused');
    r.animateTree(null, undefined as unknown as SourceJObjAnimationEffects);
    check(r.endCallbacks.counts.running === 11 && r.endCallbacks.counts.stopped === 12 && r.endCallbacks.state.head28 !== null,
      'null root ignores all effects and global counter/list state');
    rejects(() => r.animateTree(Symbol('foreign'), empty), 'non-owned joint identity');
    check(r.endCallbacks.counts.running === 0 && r.endCallbacks.counts.stopped === 0,
      'non-null root resolution follows source counter reset');
    const o = joint(r); r.endCallbacks.counts.stopped = 13;
    let getter = false; const bad = {...empty};
    Object.defineProperty(bad, 'interpretAObj', {get() {getter = true; return () => {};}});
    rejects(() => r.animateTree(o.id, bad), 'own data-function');
    check(!getter && r.endCallbacks.counts.stopped === 13, 'host effect-table preflight precedes source init and never calls getters');
  }
  {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), a = joint(r), leaf = joint(r), b = joint(r), excluded = joint(r);
    root.n.child10 = a.id; a.n.child10 = leaf.id; a.n.sibling08 = b.id; root.n.sibling08 = excluded.id;
    const names = new Map([[root.id, 'root'], [a.id, 'a'], [leaf.id, 'leaf'], [b.id, 'b'], [excluded.id, 'excluded']]);
    const events: string[] = []; let current = '';
    const callback = r.endCallbacks.createCallback(() => {events.push('end');});
    r.endCallbacks.state.head28 = r.endCallbacks.createNode({next00: null, callback04: callback});
    r.endCallbacks.counts.running = 14; r.endCallbacks.counts.stopped = 15;
    const effects: SourceJObjAnimationEffects = {
      interpretAObj(_target, owner) {
        current = names.get(owner)!; events.push(`a:${current}`);
        if (owner === root.id) check(r.endCallbacks.counts.running === 0 && r.endCallbacks.counts.stopped === 0, 'counters init before first owner');
        r.endCallbacks.counts.stopped++;
        // Source callees are static throughout this tree, despite effect-table edits.
        effects.animateRObjs = () => {throw Error('replacement should not run');};
      },
      animateRObjs() {events.push(`r:${current}`);},
      animateDObjs() {events.push(`d:${current}`);},
    };
    r.animateTree(root.id, effects);
    check(events.join() === 'a:root,r:root,d:root,a:a,r:a,d:a,a:leaf,r:leaf,d:leaf,a:b,r:b,d:b,end',
      'preorder complete per-joint calls, no root sibling, end only after entire tree');
    check(r.endCallbacks.counts.stopped === 4 && r.endCallbacks.counts.running === 0,
      'one reset for tree, not once per joint');
  }
  for (const flags of [0x40, 0x1000000, 0x2000000, 0x20, 0x4000, 0x4020, 0x800040]) {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), child = joint(r, {flags14: flags}), leaf = joint(r);
    root.n.child10 = child.id; child.n.child10 = leaf.id;
    const visited: symbol[] = [];
    r.animateTree(root.id, {...empty, interpretAObj(_a, owner) {visited.push(owner);}});
    check(visited.length === 3 && visited[2] === leaf.id, `flag${flags} does not suppress joint animation or descendants`);
  }
  for (const changedBy of ['a', 'r', 'd']) {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), child = joint(r);
    root.n.child10 = child.id; root.n.sibling08 = 7 as unknown as symbol;
    const visited: symbol[] = [];
    const e: SourceJObjAnimationEffects = {
      interpretAObj(_a, owner) {visited.push(owner); if (changedBy === 'a') root.n.flags14 |= 0x1000;},
      animateRObjs() {if (changedBy === 'r') root.n.flags14 |= 0x1000;},
      animateDObjs() {if (changedBy === 'd') root.n.flags14 |= 0x1000;},
    };
    r.animateTree(root.id, e); check(visited.length === 1, `post-${changedBy} flag1000 gates children after full own animation`);
    root.n.child10 = 7 as unknown as symbol; r.animateTree(root.id, empty);
    root.n.child10 = child.id; visited.length = 0;
    r.animateTree(root.id, {...empty, interpretAObj(_a, owner) {visited.push(owner); root.n.flags14 &= ~0x1000;}});
    check(visited.length === 2, 'effects clearing initial prune allow children this pass');
  }
  {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), a = joint(r), leaf = joint(r);
    const old = joint(r), next = joint(r), tail = joint(r), ignored = joint(r);
    root.n.child10 = ignored.id; a.n.child10 = leaf.id; a.n.sibling08 = old.id;
    const visited: symbol[] = [];
    r.animateTree(root.id, {...empty, interpretAObj(_a, owner) {
      visited.push(owner);
      if (owner === root.id) root.n.child10 = a.id;
      if (owner === leaf.id) {
        a.n.sibling08 = next.id; root.n.child10 = ignored.id; root.n.flags14 |= 0x1000;
      }
      if (owner === next.id) next.n.sibling08 = tail.id;
    }});
    check(visited.length === 5 && visited.every((id, i) => id === [root.id, a.id, leaf.id, next.id, tail.id][i]),
      'child read after own effects, sibling read after subtree, entered parent prune/child not rechecked');
  }
  for (let budget = 1; budget <= 5; budget++) {
    const r = createSourceJObjAnimationRuntime(1, budget), nodes = Array.from({length: 5}, () => joint(r));
    nodes[0]!.n.child10 = nodes[1]!.id; nodes[1]!.n.child10 = nodes[2]!.id;
    nodes[1]!.n.sibling08 = nodes[3]!.id; nodes[3]!.n.sibling08 = nodes[4]!.id;
    let ended = false; const visited: symbol[] = [];
    r.endCallbacks.state.head28 = r.endCallbacks.createNode({next00: null,
      callback04: r.endCallbacks.createCallback(() => {ended = true;})});
    const run = () => r.animateTree(nodes[0]!.id, {...empty, interpretAObj(_a, owner) {
      visited.push(owner); r.endCallbacks.counts.stopped++;
    }});
    if (budget < 5) rejects(run, 'animation-node budget'); else run();
    check(visited.length === budget && visited.every((id, i) => id === nodes[i]!.id) &&
      r.endCallbacks.counts.stopped === budget && ended === (budget === 5), 'each budget cut preserves preorder prefix without end callbacks');
  }
  for (const fault of ['cycle', 'shared', 'foreign', 'invalid', 'frozen', 'effect']) {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), child = joint(r), leaf = joint(r);
    root.n.child10 = child.id; child.n.child10 = leaf.id;
    const visited: symbol[] = []; let ended = false;
    r.endCallbacks.state.head28 = r.endCallbacks.createNode({next00: null,
      callback04: r.endCallbacks.createCallback(() => {ended = true;})});
    if (fault === 'cycle') child.n.sibling08 = root.id;
    if (fault === 'shared') child.n.sibling08 = leaf.id;
    if (fault === 'foreign') child.n.sibling08 = joint(createSourceJObjAnimationRuntime()).id;
    if (fault === 'invalid') child.n.sibling08 = 7 as unknown as symbol;
    if (fault === 'frozen') Object.freeze(leaf.n);
    rejects(() => r.animateTree(root.id, {...empty, interpretAObj(_a, owner) {
      visited.push(owner); r.endCallbacks.counts.stopped++;
      if (fault === 'effect' && owner === child.id) throw Error('fixture effect failure');
    }}), {cycle: 'cycle/revisited', shared: 'cycle/revisited', foreign: 'non-owned joint', invalid: 'opaque symbol',
      frozen: 'non-writable', effect: 'fixture effect failure'}[fault]!);
    const count = fault === 'frozen' || fault === 'effect' ? 2 : 3;
    check(visited.length === count && r.endCallbacks.counts.stopped === count && !ended,
      `tree ${fault} retains visited/effect prefix and suppresses final end invocation`);
    // The busy guard is released even after traversal failure.
    root.n.flags14 |= 0x1000; r.endCallbacks.state.head28 = null; r.animateTree(root.id, empty);
  }
  {
    const r = createSourceJObjAnimationRuntime(), root = joint(r);
    rejects(() => r.animateTree(root.id, {...empty, interpretAObj() {r.animateJoint(root.id, empty);}}), 'reentry');
    r.endCallbacks.state.head28 = r.endCallbacks.createNode({next00: null,
      callback04: r.endCallbacks.createCallback(() => {r.animateTree(root.id, empty);})});
    rejects(() => r.animateTree(root.id, {...empty, interpretAObj() {r.endCallbacks.counts.stopped++;}}), 'reentry');
    r.endCallbacks.state.head28 = null; r.animateTree(root.id, empty);
    check(r.endCallbacks.counts.stopped === 0, 'guards release after end callback failure');
  }
  {
    const r = createSourceJObjAnimationRuntime(1, 12001), root = joint(r); let last = root;
    for (let i = 0; i < 12000; i++) {const next = joint(r); last.n.child10 = next.id; last = next;}
    let count = 0, end: symbol | null = null;
    r.animateTree(root.id, {...empty, interpretAObj(_a, owner) {count++; end = owner;}});
    check(count === 12001 && end === last.id, 'iterative traversal has no source-inline-depth or JS stack cap');
  }
  {
    const r = createSourceJObjAnimationRuntime(), root = joint(r), child = joint(r);
    root.n.child10 = child.id; child.b.parent0c = root.id;
    const animations = [root, child].map((j, index) => {
      const f = createSourceFObjScalarCallbackRuntime(j.id), data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
      const node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5, flags10: 1,
        byte11: 0, byte12: 0, track13: index === 0 ? 5 : 7, format14: 0x80, format15: 0x80,
        half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
      const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: index === 0 ? 3 : 5, rate: 2, fobjs: node});
      j.b.aobj7c = Symbol('owned AObj'); j.b.classUpdate50 = f.createCallback(r.updateScalar);
      requestSourceAObj(a, 0, f.effects); return {j, f, a};
    });
    const events: string[] = [];
    r.endCallbacks.state.head28 = r.endCallbacks.createNode({next00: null,
      callback04: r.endCallbacks.createCallback(() => {events.push('end');})});
    const effects: SourceJObjAnimationEffects = {
      interpretAObj(id, owner, cb) {
        const row = animations.find(x => x.j.id === owner && x.j.b.aobj7c === id);
        if (!row) throw Error('unbound AObj/owner');
        interpretSourceAObj(row.a, cb, row.f.effects, r.endCallbacks.counts);
        events.push(owner === root.id ? 'root' : 'child');
      },
      animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');},
      animateDObjs(list) {if (list !== null) throw Error('unsupported DObj');},
    };
    const expected = [[2, 0], [2, 0], [1, 1], [0, 1], [0, 0]];
    for (let pass = 0; pass < 5; pass++) {
      events.length = 0; r.animateTree(root.id, effects);
      check(r.endCallbacks.counts.running === expected[pass]![0] && r.endCallbacks.counts.stopped === expected[pass]![1],
        `real AObj accounting pass${pass}: stopped-on-entry never counts as newly completed`);
      check(events.join() === (pass === 3 ? 'root,child,end' : 'root,child'), 'end callback only on last observed completion, after entire tree');
    }
    check(root.n.translation38 === 18 && child.n.translation40 === 22 && animations[0]!.a.frame === 4 && animations[1]!.a.frame === 6,
      'independent FObj clocks preserve linear extrapolation 10 + 2*6 = 22 and AObj overshoot rather than clamping');
  }
  console.log('[jobj-tree] PASS: ordered mutable JObj tree, source AObj accounting/end callback wrapper, partial failures and bounded real composition; synthetic, no original replay or live integration');
}
