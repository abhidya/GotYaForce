import {createSourceDObjAnimationRuntime, type SourceDObjAnimationBinding,
  type SourceDObjAnimationEffects, type SourceDObjAnimationRuntime} from './dobj-animation.js';
import {createSourceJObjAnimationRuntime, type SourceJObjAnimationEffects} from './jobj-animation.js';
import {createSourceAObj, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[dobj-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const empty: SourceDObjAnimationEffects = {interpretAObj() {}, animatePObjs() {}, animateMObj() {}};
// These no-op effects are explicit orchestration test doubles, not implementations.
function dobj(r: SourceDObjAnimationRuntime, patch: Partial<SourceDObjAnimationBinding> = {}) {
  const initial = {next04: null, mobj08: null, pobj0c: null, aobj10: null, classUpdate44: null, ...patch};
  const id = r.createDObj(initial);
  return {id, n: r.getDObj(id), initial};
}
export function runDObjAnimationSelfTest(): void {
  for (const max of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => createSourceDObjAnimationRuntime(max), 'maxNodes');
  }
  {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r);
    r.animateAll(null, undefined as unknown as SourceDObjAnimationEffects);
    check(Object.isFrozen(r) && Object.isSealed(a.n), 'owned method table frozen, binding sealed');
    a.initial.next04 = Symbol('not copied later');
    check(a.n.next04 === null, 'initial records are copied rather than aliased');
    rejects(() => r.getDObj(Symbol('foreign')), 'non-owned DObj');
    rejects(() => r.animateAll(a.id, undefined as unknown as SourceDObjAnimationEffects), 'effect data table');
    for (const key of ['next04', 'mobj08', 'pobj0c', 'aobj10', 'classUpdate44'] as const) {
      let getter = false;
      const initial = {...a.n}; Object.defineProperty(initial, key, {get() {getter = true; return null;}});
      rejects(() => r.createDObj(initial), 'own data property'); check(!getter, `input ${key} getter never called`);
      rejects(() => r.createDObj({...a.n, [key]: 7}), 'opaque symbol');
    }
    for (const key of ['interpretAObj', 'animatePObjs', 'animateMObj'] as const) {
      let getter = false, entered = false;
      const effects = {...empty, interpretAObj() {entered = true;}};
      Object.defineProperty(effects, key, {get() {getter = true; return () => {};}});
      rejects(() => r.animateAll(a.id, effects), 'own data property');
      check(!getter && !entered, `effect ${key} preflight rejects getter without work`);
      rejects(() => r.animateAll(a.id, Object.create(empty) as SourceDObjAnimationEffects), 'own data property');
      rejects(() => r.animateAll(a.id, {...empty, [key]: null} as unknown as SourceDObjAnimationEffects), 'own data-function');
    }
  }
  {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r), b = dobj(r), skipped = dobj(r), tail = dobj(r);
    const ca = Symbol('callback a'), cb = Symbol('callback b'), aa = Symbol('AObj a'), ab = Symbol('AObj b');
    const p = Symbol('live PObj'), m = Symbol('live MObj');
    a.n.next04 = skipped.id; a.n.classUpdate44 = ca; a.n.aobj10 = aa;
    Object.freeze(skipped.n); // Unvisited records are not a whole-list preflight.
    b.n.classUpdate44 = Symbol('stale later callback'); b.n.aobj10 = Symbol('stale later AObj');
    const events: string[] = [];
    let owner: symbol;
    const effects: SourceDObjAnimationEffects = {
      interpretAObj(target, current, callback) {
        check(this === effects, 'AObj callee keeps original effect table this'); owner = current;
        events.push(current === a.id ? 'a0' : current === b.id ? 'a1' : 'a2');
        if (current === a.id) {
          check(target === aa && callback === ca, 'first AObj and resolved callback use same DObj owner');
          a.n.aobj10 = Symbol('consumed'); a.n.classUpdate44 = Symbol('consumed'); a.n.pobj0c = p;
          b.n.classUpdate44 = cb; b.n.aobj10 = ab;
          effects.animatePObjs = () => {check(false, 'replacement PObj callee');};
          effects.animateMObj = () => {check(false, 'replacement MObj callee');};
          effects.interpretAObj = () => {check(false, 'replacement AObj callee');};
        } else if (current === b.id) check(target === ab && callback === cb, 'later DObj reads its own callback and AObj');
        else check(current === tail.id && target === null && callback === null, 'null AObj/callback forwarded, tail visited');
      },
      animatePObjs(target) {
        check(this === effects, 'PObj callee this retained'); events.push(owner === a.id ? 'p0' : owner === b.id ? 'p1' : 'p2');
        if (owner === a.id) {check(target === p, 'PObj reloaded after AObj'); a.n.mobj08 = m;}
        else check(target === null, 'null PObj forwarded');
      },
      animateMObj(target) {
        check(this === effects, 'MObj callee this retained'); events.push(owner === a.id ? 'm0' : owner === b.id ? 'm1' : 'm2');
        if (owner === a.id) {check(target === m, 'MObj reloaded after PObj'); a.n.next04 = b.id;}
        else if (owner === b.id) {check(target === null, 'null MObj forwarded'); b.n.next04 = tail.id;}
      },
    };
    r.animateAll(a.id, effects);
    check(events.join() === 'a0,p0,m0,a1,p1,m1,a2,p2,m2', 'complete per-object order and live next after material effect');
  }
  {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r);
    a.n.pobj0c = 7 as unknown as symbol; a.n.mobj08 = 7 as unknown as symbol; a.n.next04 = 7 as unknown as symbol;
    let current: symbol, tail: symbol | null = null; const visits: symbol[] = [];
    r.animateAll(a.id, {
      interpretAObj(_target, owner) {current = owner; visits.push(owner); if (owner === a.id) a.n.pobj0c = null;},
      animatePObjs() {if (current === a.id) a.n.mobj08 = null;},
      animateMObj() {if (current === a.id) {tail = dobj(r).id; a.n.next04 = tail;}},
    });
    check(visits.length === 2 && visits[1] === tail, 'effects repair later fields before use and may allocate a newly followed tail');
  }
  for (const key of ['classUpdate44', 'aobj10', 'pobj0c', 'mobj08', 'next04'] as const) {
    for (const defect of ['type', 'frozen'] as const) {
      const r = createSourceDObjAnimationRuntime(), a = dobj(r); const events: string[] = [];
      if (defect === 'type') a.n[key] = 1 as unknown as symbol;
      else Object.defineProperty(a.n, key, {writable: false});
      rejects(() => r.animateAll(a.id, {
        interpretAObj() {events.push('a');}, animatePObjs() {events.push('p');}, animateMObj() {events.push('m');},
      }), defect === 'type' ? 'opaque symbol' : 'non-writable');
      check(events.join() === ({classUpdate44: '', aobj10: '', pobj0c: 'a', mobj08: 'a,p', next04: 'a,p,m'}[key]),
        `${key} ${defect} checked only at actual access, earlier effects retained`);
    }
  }
  {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r); const events: string[] = [];
    // Changes to consumed fields do not become a fictitious post-effect preflight.
    r.animateAll(a.id, {
      interpretAObj() {events.push('a'); Object.defineProperty(a.n, 'classUpdate44', {writable: false}); a.n.aobj10 = 7 as unknown as symbol;},
      animatePObjs() {events.push('p'); Object.defineProperty(a.n, 'pobj0c', {writable: false});},
      animateMObj() {events.push('m'); Object.defineProperty(a.n, 'mobj08', {writable: false});},
    });
    check(events.join() === 'a,p,m', 'already-consumed fields are not revalidated');
    rejects(() => r.animateAll(a.id, empty), 'non-writable');
  }
  for (const fault of ['a', 'p', 'm', 'async-a', 'async-p', 'async-m']) {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r), b = dobj(r); a.n.next04 = b.id;
    const events: string[] = [];
    const call = (where: string) => {events.push(where); if (fault === where) throw Error('test boundary failure');
      if (fault === 'async-'+where) return Promise.resolve();};
    rejects(() => r.animateAll(a.id, {
      interpretAObj: (() => call('a')) as SourceDObjAnimationEffects['interpretAObj'],
      animatePObjs: (() => call('p')) as SourceDObjAnimationEffects['animatePObjs'],
      animateMObj: (() => call('m')) as SourceDObjAnimationEffects['animateMObj'],
    }), fault.startsWith('async') ? 'synchronously' : 'test boundary failure');
    check(events.join() === ({a: 'a', p: 'a,p', m: 'a,p,m'}[fault.slice(-1)]), 'effect failure stops at its exact prefix');
    r.animateAll(a.id, empty); // Busy state is released after all failures.
  }
  for (const caught of [false, true]) {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r); let later = false;
    rejects(() => r.animateAll(a.id, {...empty, interpretAObj() {
      r.animateAll(null, undefined as unknown as SourceDObjAnimationEffects);
      if (caught) {try {r.animateAll(a.id, empty);} catch { /* outer execution still refuses */ }}
      else r.animateAll(a.id, empty);
    }, animatePObjs() {later = true;}}), 'reentry');
    check(!later, 'even a caught reentry aborts remaining effects'); r.animateAll(a.id, empty);
  }
  for (const defect of ['foreign', 'cycle', 'type']) {
    const r = createSourceDObjAnimationRuntime(), a = dobj(r), b = dobj(r); a.n.next04 = b.id;
    b.n.next04 = defect === 'foreign' ? dobj(createSourceDObjAnimationRuntime()).id : defect === 'cycle' ? a.id : 7 as unknown as symbol;
    let visits = 0;
    rejects(() => r.animateAll(a.id, {...empty, interpretAObj() {visits++;}}),
      {foreign: 'non-owned DObj', cycle: 'cycle/revisited', type: 'opaque symbol'}[defect]!);
    check(visits === 2, 'late link defect retains both visited nodes');
  }
  for (let budget = 1; budget <= 4; budget++) {
    const r = createSourceDObjAnimationRuntime(budget), nodes = Array.from({length: 4}, () => dobj(r));
    for (let i = 0; i < 3; i++) nodes[i]!.n.next04 = nodes[i+1]!.id;
    let visits = 0; const run = () => r.animateAll(nodes[0]!.id, {...empty, interpretAObj() {visits++;}});
    if (budget < 4) rejects(run, 'visit budget'); else run();
    check(visits === budget, 'visit budget preserves each completed node');
  }
  {
    const r = createSourceDObjAnimationRuntime(12001), first = dobj(r); let last = first;
    for (let i = 0; i < 12000; i++) {const next = dobj(r); last.n.next04 = next.id; last = next;}
    let count = 0, final: symbol | null = null;
    r.animateAll(first.id, {...empty, interpretAObj(_a, owner) {count++; final = owner;}});
    check(count === 12001 && final === last.id, 'long source list traversed iteratively');
  }
  {
    const j = createSourceJObjAnimationRuntime(), d = createSourceDObjAnimationRuntime();
    const root = j.createJoint({sibling08: null, child10: null, flags14: 0,
      rotation1c: 0, rotation20: 0, rotation24: 0, scale2c: 1, scale30: 1, scale34: 1,
      translation38: 0, translation3c: 0, translation40: 0},
    {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null});
    const first = dobj(d), second = dobj(d); first.n.next04 = second.id;
    j.getBinding(root).dobj18 = first.id;
    const rows = [root, first.id, second.id].map((owner, index) => {
      const f = createSourceFObjScalarCallbackRuntime(owner);
      // Real AObj/FObj empty-list behavior isolates dispatch/counting. No
      // unaudited DObj receiver or polygon/material behavior is substituted.
      const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: index+1, rate: 1, fobjs: null});
      const id = Symbol('AObj binding');
      if (index === 0) j.getBinding(owner).aobj7c = id; else d.getDObj(owner).aobj10 = id;
      requestSourceAObj(a, 0, f.effects); return {owner, id, a, f};
    });
    const events: string[] = [];
    j.endCallbacks.state.head28 = j.endCallbacks.createNode({next00: null,
      callback04: j.endCallbacks.createCallback(() => {events.push('end');})});
    const interpret = (id: symbol | null, owner: symbol, callback: symbol | null): void => {
      const row = rows.find(x => x.owner === owner && x.id === id);
      if (!row) throw Error('unbound owner/AObj');
      interpretSourceAObj(row.a, callback, row.f.effects, j.endCallbacks.counts);
      events.push(owner === root ? 'joint' : owner === first.id ? 'display1' : 'display2');
    };
    const de: SourceDObjAnimationEffects = {interpretAObj: interpret,
      animatePObjs(list) {if (list !== null) throw Error('unsupported PObj');},
      animateMObj(object) {if (object !== null) throw Error('unsupported MObj');}};
    const je: SourceJObjAnimationEffects = {interpretAObj: interpret,
      animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');}, animateDObjs(list) {d.animateAll(list, de);}};
    for (let pass = 0; pass < 5; pass++) {
      events.length = 0; j.animateTree(root, je);
      const expected = [[3, 0], [2, 1], [1, 1], [0, 1], [0, 0]][pass]!;
      check(j.endCallbacks.counts.running === expected[0] && j.endCallbacks.counts.stopped === expected[1],
        `JObj and both DObj AObjs share actual counters, pass ${pass}`);
      check(events.join() === (pass === 3 ? 'joint,display1,display2,end' : 'joint,display1,display2'),
        'tree completes only after final display AObj stops, never after merely visiting the joint');
    }
    check(rows.map(x => x.a.frame).join() === '1,2,3', 'each AObj retains its independent completion frame');
    // Required material refusal retains real prior AObj counting, with no end call.
    rows.forEach(row => requestSourceAObj(row.a, row.a.end, row.f.effects));
    events.length = 0; second.n.mobj08 = Symbol('unsupported material');
    rejects(() => j.animateTree(root, je), 'unsupported MObj');
    check(j.endCallbacks.counts.stopped === 3 && !events.includes('end'), 'DObj failure preserves counts and suppresses outer tree completion');
  }
  console.log('[dobj-animation] PASS: ordered mutable display-list dispatch, late host checks and actual shared AObj completion accounting; synthetic, no original replay or live integration');
}
