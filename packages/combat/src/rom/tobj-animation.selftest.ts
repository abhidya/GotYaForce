import {createSourceTObjAnimationRuntime, type SourceTObjAnimationBinding,
  type SourceTObjAnimationEffects, type SourceTObjAnimationRuntime} from './tobj-animation.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[tobj-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const scalarHeader = () => ({flags4c: 0, rotation18: 0, rotation1c: 0, rotation20: 0, scale28: 1, scale2c: 1, translation34: 0, translation38: 0});
const empty: SourceTObjAnimationEffects = {interpretAObj() {}}; // Explicit test double.
function tobj(r: SourceTObjAnimationRuntime, patch: Partial<SourceTObjAnimationBinding> = {}) {
  const initial = {next08: null, aobj64: null, classUpdate48: null, ...patch};
  const id = r.createTexture(scalarHeader(), initial); return {id, n: r.getBinding(id), initial};
}
export function runTObjAnimationSelfTest(): void {
  for (const max of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER+1]) rejects(() => createSourceTObjAnimationRuntime(max), 'maxNodes');
  {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r);
    r.animateAll(null, undefined as unknown as SourceTObjAnimationEffects);
    check(Object.isFrozen(r) && Object.isSealed(a.n), 'method table frozen and bindings sealed');
    a.initial.next08 = Symbol('external edit'); check(a.n.next08 === null, 'initial input copied');
    rejects(() => r.getBinding(Symbol('foreign')), 'non-owned TObj');
    rejects(() => r.animateAll(a.id, undefined as unknown as SourceTObjAnimationEffects), 'effect data table');
    rejects(() => r.animateAll(a.id, Object.create(empty) as SourceTObjAnimationEffects), 'own data property');
    rejects(() => r.animateAll(a.id, {interpretAObj: null} as unknown as SourceTObjAnimationEffects), 'own data-function');
    let getter = false; const e = Object.defineProperty({}, 'interpretAObj', {get() {getter = true; return () => {};}});
    rejects(() => r.animateAll(a.id, e as SourceTObjAnimationEffects), 'own data property'); check(!getter, 'effect getter not called');
    for (const key of ['next08', 'aobj64', 'classUpdate48'] as const) {
      const initial = {...a.n}; Object.defineProperty(initial, key, {get() {getter = true; return null;}});
      rejects(() => r.createTexture(scalarHeader(), initial), 'own data property'); check(!getter, 'input getter not called');
      rejects(() => r.createTexture(scalarHeader(), {...a.n, [key]: 7}), 'opaque symbol');
    }
  }
  {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r), b = tobj(r), skipped = tobj(r);
    a.n.next08 = skipped.id; Object.freeze(skipped.n);
    const aa = Symbol('a AObj'), ca = Symbol('a callback'), ab = Symbol('b AObj'), cb = Symbol('b callback');
    a.n.aobj64 = aa; a.n.classUpdate48 = ca;
    const visits: symbol[] = []; let tail: symbol | null = null;
    const e: SourceTObjAnimationEffects = {interpretAObj(target, owner, callback) {
      check(this === e, 'original effect receiver retained'); visits.push(owner);
      if (owner === a.id) {
        check(target === aa && callback === ca, 'current owner and callback/AObj captured');
        a.n.aobj64 = 7 as unknown as symbol; Object.defineProperty(a.n, 'classUpdate48', {writable: false});
        a.n.next08 = b.id; b.n.aobj64 = ab; b.n.classUpdate48 = cb;
        e.interpretAObj = () => {check(false, 'replacement effect must not run');};
      } else if (owner === b.id) {
        check(target === ab && callback === cb, 'later binding changes are read when reached');
        tail = tobj(r).id; b.n.next08 = tail;
      } else check(owner === tail && target === null && callback === null, 'new tail and null targets dispatched');
    }};
    r.animateAll(a.id, e);
    check(visits.length === 3 && visits[0] === a.id && visits[1] === b.id && visits[2] === tail,
      'live next, effect-created tail, skipped frozen node and consumed-field non-revalidation');
  }
  for (const key of ['classUpdate48', 'aobj64', 'next08'] as const) {
    for (const defect of ['type', 'frozen']) {
      const r = createSourceTObjAnimationRuntime(), a = tobj(r); let called = 0;
      if (defect === 'type') a.n[key] = 7 as unknown as symbol; else Object.defineProperty(a.n, key, {writable: false});
      rejects(() => r.animateAll(a.id, {interpretAObj() {called++;}}), defect === 'type' ? 'opaque symbol' : 'non-writable');
      check(called === (key === 'next08' ? 1 : 0), 'field checks preserve exact completed call prefix');
    }
  }
  {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r); a.n.next08 = 7 as unknown as symbol;
    r.animateAll(a.id, {interpretAObj() {a.n.next08 = null;}});
    check(a.n.next08 === null, 'interpreter may repair next before its read');
  }
  {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r), b = tobj(r);
    r.getTexture(a.id).flags4c = NaN; Object.freeze(r.getTexture(a.id));
    let called = false; r.animateAll(a.id, {interpretAObj() {called = true;}});
    check(called, 'animation does not preflight a scalar header unused by its interpreter');
    r.animateAll(b.id, {interpretAObj(_a, owner) {r.updateScalar(owner, 2, 5);}});
    check(r.getTexture(b.id).translation34 === 5 && r.getTexture(b.id).flags4c === 0x80000000,
      'scalar receiver uses the same owner identity and is allowed during animation');
  }
  for (const defect of ['foreign', 'cycle', 'type']) {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r), b = tobj(r); a.n.next08 = b.id;
    b.n.next08 = defect === 'foreign' ? tobj(createSourceTObjAnimationRuntime()).id : defect === 'cycle' ? a.id : 7 as unknown as symbol;
    let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {count++; check(count <= 2, 'revisited texture interpreter called');}}),
      {foreign: 'non-owned TObj', cycle: 'cycle/revisited', type: 'opaque symbol'}[defect]!);
    check(count === 2, 'late traversal refusal preserves previous interpretations');
  }
  for (const result of [1, null, Promise.resolve()]) {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r), b = tobj(r); a.n.next08 = b.id; let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {count++; return result;}} as unknown as SourceTObjAnimationEffects), 'synchronously');
    check(count === 1, 'non-undefined return refuses after one call'); r.animateAll(a.id, empty);
  }
  for (const caught of [false, true]) {
    const r = createSourceTObjAnimationRuntime(), a = tobj(r), b = tobj(r); a.n.next08 = b.id; let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {
      count++; r.animateAll(null, undefined as unknown as SourceTObjAnimationEffects);
      if (caught) {try {r.animateAll(a.id, empty);} catch { /* outer call must fail too */ }}
      else r.animateAll(a.id, empty);
    }}), 'reentry');
    check(count === 1, 'reentry stops list even if caught'); r.animateAll(a.id, empty);
    rejects(() => r.animateAll(a.id, {interpretAObj() {throw Error('test effect failure');}}), 'test effect failure');
    r.animateAll(a.id, empty);
  }
  for (let budget = 1; budget <= 4; budget++) {
    const r = createSourceTObjAnimationRuntime(budget), nodes = Array.from({length: 4}, () => tobj(r));
    for (let i = 0; i < 3; i++) nodes[i]!.n.next08 = nodes[i+1]!.id;
    let count = 0; const run = () => r.animateAll(nodes[0]!.id, {interpretAObj() {count++;}});
    if (budget < 4) rejects(run, 'visit budget'); else run(); check(count === budget, 'visit budget retains completed prefix');
  }
  {
    const r = createSourceTObjAnimationRuntime(12001), first = tobj(r); let last = first;
    for (let i = 0; i < 12000; i++) {const next = tobj(r); last.n.next08 = next.id; last = next;}
    let count = 0, final: symbol | null = null;
    r.animateAll(first.id, {interpretAObj(_a, owner) {count++; final = owner;}});
    check(count === 12001 && final === last.id, 'deep list is iterative');
  }
  console.log('[tobj-animation] PASS: ordered mutable texture-list dispatch and bounded failure prefixes; synthetic, bounded scalar receiver separate from dispatch; no original replay');
}
