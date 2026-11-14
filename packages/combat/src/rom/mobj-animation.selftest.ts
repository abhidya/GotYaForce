import {createSourceMObjAnimationRuntime, type SourceMObjAnimationBinding,
  type SourceMObjAnimationEffects, type SourceMObjAnimationRuntime} from './mobj-animation.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[mobj-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
// These no-op effects are explicit orchestration test doubles, not implementations.
const empty: SourceMObjAnimationEffects = {interpretAObj() {}, animateTObjs() {}};
function mobj(r: SourceMObjAnimationRuntime, patch: Partial<SourceMObjAnimationBinding> = {}) {
  const initial = {tobj08: null, aobj14: null, classUpdate4c: null, ...patch};
  const id = r.createMObj(initial);
  return {id, n: r.getMObj(id), initial};
}
export function runMObjAnimationSelfTest(): void {
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r);
    r.animate(null, undefined as unknown as SourceMObjAnimationEffects);
    let getter = false;
    const invalid = {get interpretAObj() {getter = true; throw Error('must not read');}};
    r.animate(null, invalid as unknown as SourceMObjAnimationEffects);
    check(!getter, 'null material bypasses effect-table validation');
    check(Object.isFrozen(r) && Object.isSealed(a.n), 'owned method table frozen, binding sealed');
    check(r.getMObj(a.id) === a.n, 'getMObj retains owned binding identity');
    for (const key of ['tobj08', 'aobj14', 'classUpdate4c'] as const) {
      a.initial[key] = Symbol('not copied later');
      check(a.n[key] === null, `input ${key} is copied rather than aliased`);
      let accessed = false;
      const initial = {...a.n}; Object.defineProperty(initial, key, {get() {accessed = true; return null;}});
      rejects(() => r.createMObj(initial), `${key}: own data property`);
      check(!accessed, `input ${key} getter never called`);
      const inherited = Object.create({[key]: null}) as SourceMObjAnimationBinding;
      for (const other of ['tobj08', 'aobj14', 'classUpdate4c'] as const) {
        if (other !== key) inherited[other] = null;
      }
      rejects(() => r.createMObj(inherited), `${key}: own data property`);
      rejects(() => r.createMObj({...a.n, [key]: 7}), `${key}: expected opaque symbol`);
    }
    for (const initial of [null, undefined, 7, () => {}]) {
      rejects(() => r.createMObj(initial as unknown as SourceMObjAnimationBinding), 'initial binding data record');
    }
    const frozenInput = Object.freeze({...a.n}), copied = r.getMObj(r.createMObj(frozenInput));
    copied.tobj08 = Symbol('owned writable copy');
    check(frozenInput.tobj08 === null, 'factory accepts frozen own-data input but owns a writable copy');
    rejects(() => r.getMObj(Symbol('foreign')), 'non-owned MObj');
    for (const target of [Symbol('unowned'), mobj(createSourceMObjAnimationRuntime()).id, 7]) {
      let effects = 0;
      rejects(() => r.animate(target as symbol, {interpretAObj() {effects++;}, animateTObjs() {effects++;}}),
        typeof target === 'symbol' ? 'non-owned MObj' : 'opaque symbol');
      check(effects === 0, 'invalid material refused before effects');
      r.animate(a.id, empty);
    }
    for (const table of [null, undefined, 7, () => {}]) {
      rejects(() => r.animate(a.id, table as unknown as SourceMObjAnimationEffects), 'effect data table');
    }
    for (const key of ['interpretAObj', 'animateTObjs'] as const) {
      let accessed = false, entered = false;
      const effects = {...empty, interpretAObj() {entered = true;}};
      Object.defineProperty(effects, key, {get() {accessed = true; return () => {};}});
      rejects(() => r.animate(a.id, effects), `${key}: own data property`);
      check(!accessed && !entered, `effect ${key} preflight rejects getter without work`);
      const inherited = Object.create(empty) as SourceMObjAnimationEffects;
      if (key === 'interpretAObj') inherited.animateTObjs = empty.animateTObjs;
      else inherited.interpretAObj = empty.interpretAObj;
      rejects(() => r.animate(a.id, inherited), `${key}: own data property`);
      rejects(() => r.animate(a.id, {...empty, [key]: null} as unknown as SourceMObjAnimationEffects),
        `${key}: own data-function`);
      r.animate(a.id, empty); // Failed method snapshots never latch the guard.
    }
    r.animate(a.id, Object.freeze({...empty}));
  }
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r), b = mobj(r);
    const aa = Symbol('AObj a'), ab = Symbol('AObj b'), ca = Symbol('callback a'), cb = Symbol('callback b');
    const stale = Symbol('stale TObj'), live = Symbol('live TObj');
    a.n.aobj14 = aa; a.n.classUpdate4c = ca; a.n.tobj08 = stale;
    b.n.aobj14 = ab; b.n.classUpdate4c = cb;
    const events: string[] = [];
    const effects: SourceMObjAnimationEffects = {
      interpretAObj(target, owner, callback) {
        check(this === effects, 'AObj callee keeps original effect-table this'); events.push('a');
        check(target === aa && owner === a.id && callback === ca, 'AObj and resolved callback pair with current MObj');
        a.n.aobj14 = ab; a.n.classUpdate4c = cb; a.n.tobj08 = live;
        effects.interpretAObj = () => {events.push('replacement-a');};
        effects.animateTObjs = () => {events.push('replacement-t');};
      },
      animateTObjs(target) {
        check(this === effects, 'TObj callee keeps original effect-table this'); events.push('t');
        check(target === live, 'TObj list is reloaded after AObj effect');
      },
    };
    r.animate(a.id, effects);
    check(events.join() === 'a,t', 'original snapped methods execute once in source order');
    r.animate(a.id, effects);
    check(events.join() === 'a,t,replacement-a,replacement-t', 'next invocation snapshots current effect methods');
    r.animate(b.id, {interpretAObj(target, owner, callback) {
      check(target === ab && owner === b.id && callback === cb, 'another invocation uses its own material owner');
    }, animateTObjs(target) {check(target === null, 'null TObj list forwarded');}});
    const n = mobj(r); let nullCalls = 0;
    r.animate(n.id, {interpretAObj(target, owner, callback) {
      check(target === null && owner === n.id && callback === null, 'null AObj and callback forwarded'); nullCalls++;
    }, animateTObjs(target) {check(target === null, 'null TObj still dispatched'); nullCalls++;}});
    check(nullCalls === 2, 'non-null material invokes both effects despite null targets');
  }
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r); let texture = false;
    const effects: SourceMObjAnimationEffects = {interpretAObj() {
      Object.defineProperty(effects, 'animateTObjs', {get() {throw Error('late getter must not run');}});
    }, animateTObjs() {texture = true;}};
    r.animate(a.id, effects);
    check(texture, 'effect table is not reread after AObj mutation');
  }
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r); let texture = false;
    a.n.tobj08 = 7 as unknown as symbol;
    r.animate(a.id, {interpretAObj() {a.n.tobj08 = null;}, animateTObjs(target) {
      check(target === null, 'repaired TObj target used'); texture = true;
    }});
    check(texture, 'AObj effect may repair a later field before its source access');
  }
  for (const key of ['classUpdate4c', 'aobj14', 'tobj08'] as const) {
    for (const defect of ['type', 'frozen'] as const) {
      const r = createSourceMObjAnimationRuntime(), a = mobj(r); const events: string[] = [];
      if (defect === 'type') a.n[key] = 1 as unknown as symbol;
      else Object.defineProperty(a.n, key, {writable: false});
      rejects(() => r.animate(a.id, {interpretAObj() {events.push('a');}, animateTObjs() {events.push('t');}}),
        `${key}: ${defect === 'type' ? 'expected opaque symbol' : 'non-writable'}`);
      check(events.join() === (key === 'tobj08' ? 'a' : ''),
        `${key} ${defect} checked only at actual access, earlier effects retained`);
      r.animate(mobj(r).id, empty); // Even unrecoverable frozen bindings release the runtime guard.
    }
  }
  for (const defect of ['type', 'frozen'] as const) {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r); let texture = false;
    rejects(() => r.animate(a.id, {interpretAObj() {
      if (defect === 'type') a.n.tobj08 = 7 as unknown as symbol;
      else Object.defineProperty(a.n, 'tobj08', {writable: false});
    }, animateTObjs() {texture = true;}}), defect === 'type' ? 'opaque symbol' : 'non-writable');
    check(!texture, 'new late-field defects are caught after completed AObj effect');
  }
  for (const key of ['classUpdate4c', 'aobj14', 'tobj08'] as const) {
    for (const defect of ['type', 'frozen'] as const) {
      const r = createSourceMObjAnimationRuntime(), a = mobj(r); const events: string[] = [];
      const consume = () => {
        if (defect === 'type') a.n[key] = 7 as unknown as symbol;
        else Object.defineProperty(a.n, key, {writable: false});
      };
      r.animate(a.id, {interpretAObj() {events.push('a'); if (key !== 'tobj08') consume();},
        animateTObjs() {events.push('t'); if (key === 'tobj08') consume();}});
      check(events.join() === 'a,t', `consumed ${key} ${defect} is not revalidated`);
      rejects(() => r.animate(a.id, empty), defect === 'type' ? 'opaque symbol' : 'non-writable');
    }
  }
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r);
    a.n.classUpdate4c = 7 as unknown as symbol;
    Object.defineProperty(a.n, 'aobj14', {writable: false});
    rejects(() => r.animate(a.id, empty), 'classUpdate4c: expected opaque symbol');
    a.n.classUpdate4c = null;
    rejects(() => r.animate(a.id, empty), 'aobj14: non-writable');
  }
  for (const boundary of ['a', 't']) {
    for (const result of ['throw', 'promise', 'null', 'number', 'object', 'function'] as const) {
      const r = createSourceMObjAnimationRuntime(), a = mobj(r); const events: string[] = [];
      let thenRead = false;
      const returned = {get then() {thenRead = true; return () => {};}};
      const call = (where: string): unknown => {
        events.push(where);
        if (where !== boundary) return;
        switch (result) {
          case 'throw': throw Error('test boundary failure');
          case 'promise': return Promise.resolve();
          case 'null': return null;
          case 'number': return 0;
          case 'object': return returned;
          case 'function': return () => {};
        }
      };
      rejects(() => r.animate(a.id, {
        interpretAObj: (() => call('a')) as SourceMObjAnimationEffects['interpretAObj'],
        animateTObjs: (() => call('t')) as SourceMObjAnimationEffects['animateTObjs'],
      }), result === 'throw' ? 'test boundary failure' : 'synchronously');
      check(events.join() === (boundary === 'a' ? 'a' : 'a,t'), 'effect failure stops at its exact prefix');
      check(!thenRead, 'non-undefined effect result is refused without probing then');
      r.animate(a.id, empty);
    }
  }
  for (const boundary of ['a', 't']) {
    for (const caught of [false, true]) {
      const r = createSourceMObjAnimationRuntime(), a = mobj(r), b = mobj(r); const events: string[] = [];
      const call = (where: string): void => {
        events.push(where);
        r.animate(null, undefined as unknown as SourceMObjAnimationEffects);
        if (where !== boundary) return;
        if (caught) {try {r.animate(b.id, empty);} catch { /* outer invocation still refuses */ }}
        else r.animate(a.id, empty);
      };
      rejects(() => r.animate(a.id, {interpretAObj() {call('a');}, animateTObjs() {call('t');}}), 'reentry');
      check(events.join() === (boundary === 'a' ? 'a' : 'a,t'), 'caught and uncaught reentry stop at exact prefix');
      r.animate(a.id, empty);
    }
  }
  {
    const r = createSourceMObjAnimationRuntime(), a = mobj(r), other = createSourceMObjAnimationRuntime();
    const b = mobj(other); let calls = 0;
    r.animate(a.id, {interpretAObj() {
      r.animate(null, undefined as unknown as SourceMObjAnimationEffects);
      other.animate(b.id, {interpretAObj() {calls++;}, animateTObjs() {calls++;}});
    }, animateTObjs() {calls++;}});
    check(calls === 3, 'null same-runtime call and non-null distinct-runtime dispatch remain supported');
  }
  console.log('[mobj-animation] PASS: owner-paired material AObj dispatch, live texture-list reload and late host checks; synthetic, no original replay or live integration');
}
