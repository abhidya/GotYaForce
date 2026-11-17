import {createSourcePObjAnimationRuntime, type SourcePObjAnimationBinding,
  type SourcePObjAnimationEffects, type SourcePObjAnimationRuntime} from './pobj-animation.js';
function check(ok: boolean, message: string): void {if (!ok) throw Error(`[pobj-animation-test] ${message}`);}
function rejects(run: () => void, expected: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(expected), `expected ${expected}, got ${error}`);
}
const empty: SourcePObjAnimationEffects = {interpretAObj() {}}; // Explicit test double.
function pobj(r: SourcePObjAnimationRuntime, patch: Partial<SourcePObjAnimationBinding> = {}) {
  const initial = {next04: null, aobj18: null, classUpdate48: null, ...patch};
  const id = r.createPObj(initial); return {id, n: r.getPObj(id), initial};
}
export function runPObjAnimationSelfTest(): void {
  for (const max of [0, -1, 1.5, NaN, Infinity, Number.MAX_SAFE_INTEGER+1]) rejects(() => createSourcePObjAnimationRuntime(max), 'maxNodes');
  {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r);
    r.animateAll(null, undefined as unknown as SourcePObjAnimationEffects);
    check(Object.isFrozen(r) && Object.isSealed(a.n), 'method table frozen and bindings sealed');
    a.initial.next04 = Symbol('external edit'); check(a.n.next04 === null, 'initial input copied');
    rejects(() => r.getPObj(Symbol('foreign')), 'non-owned PObj');
    rejects(() => r.animateAll(a.id, undefined as unknown as SourcePObjAnimationEffects), 'effect data table');
    rejects(() => r.animateAll(a.id, Object.create(empty) as SourcePObjAnimationEffects), 'own data property');
    rejects(() => r.animateAll(a.id, {interpretAObj: null} as unknown as SourcePObjAnimationEffects), 'own data-function');
    let getter = false; const e = Object.defineProperty({}, 'interpretAObj', {get() {getter = true; return () => {};}});
    rejects(() => r.animateAll(a.id, e as SourcePObjAnimationEffects), 'own data property'); check(!getter, 'effect getter not called');
    for (const key of ['next04', 'aobj18', 'classUpdate48'] as const) {
      const initial = {...a.n}; Object.defineProperty(initial, key, {get() {getter = true; return null;}});
      rejects(() => r.createPObj(initial), 'own data property'); check(!getter, 'input getter not called');
      rejects(() => r.createPObj({...a.n, [key]: 7}), 'opaque symbol');
    }
  }
  {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r), b = pobj(r), skipped = pobj(r);
    a.n.next04 = skipped.id; Object.freeze(skipped.n);
    const aa = Symbol('a AObj'), ca = Symbol('a callback'), ab = Symbol('b AObj'), cb = Symbol('b callback');
    a.n.aobj18 = aa; a.n.classUpdate48 = ca;
    const visits: symbol[] = []; let tail: symbol | null = null;
    const e: SourcePObjAnimationEffects = {interpretAObj(target, owner, callback) {
      check(this === e, 'original effect receiver retained'); visits.push(owner);
      if (owner === a.id) {
        check(target === aa && callback === ca, 'current owner and callback/AObj captured');
        a.n.aobj18 = 7 as unknown as symbol; Object.defineProperty(a.n, 'classUpdate48', {writable: false});
        a.n.next04 = b.id; b.n.aobj18 = ab; b.n.classUpdate48 = cb;
        e.interpretAObj = () => {check(false, 'replacement effect must not run');};
      } else if (owner === b.id) {
        check(target === ab && callback === cb, 'later binding changes are read when reached');
        tail = pobj(r).id; b.n.next04 = tail;
      } else check(owner === tail && target === null && callback === null, 'new tail and null targets dispatched');
    }};
    r.animateAll(a.id, e);
    check(visits.length === 3 && visits[0] === a.id && visits[1] === b.id && visits[2] === tail,
      'live next, effect-created tail, skipped frozen node and consumed-field non-revalidation');
  }
  for (const key of ['classUpdate48', 'aobj18', 'next04'] as const) {
    for (const defect of ['type', 'frozen']) {
      const r = createSourcePObjAnimationRuntime(), a = pobj(r); let called = 0;
      if (defect === 'type') a.n[key] = 7 as unknown as symbol; else Object.defineProperty(a.n, key, {writable: false});
      rejects(() => r.animateAll(a.id, {interpretAObj() {called++;}}), defect === 'type' ? 'opaque symbol' : 'non-writable');
      check(called === (key === 'next04' ? 1 : 0), 'field checks preserve exact completed call prefix');
    }
  }
  {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r); a.n.next04 = 7 as unknown as symbol;
    r.animateAll(a.id, {interpretAObj() {a.n.next04 = null;}});
    check(a.n.next04 === null, 'interpreter may repair next before its read');
  }
  for (const defect of ['foreign', 'cycle', 'type']) {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r), b = pobj(r); a.n.next04 = b.id;
    b.n.next04 = defect === 'foreign' ? pobj(createSourcePObjAnimationRuntime()).id : defect === 'cycle' ? a.id : 7 as unknown as symbol;
    let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {count++; check(count <= 2, 'revisited polygon interpreter called');}}),
      {foreign: 'non-owned PObj', cycle: 'cycle/revisited', type: 'opaque symbol'}[defect]!);
    check(count === 2, 'late traversal refusal preserves previous interpretations');
  }
  for (const result of [1, null, Promise.resolve()]) {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r), b = pobj(r); a.n.next04 = b.id; let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {count++; return result;}} as unknown as SourcePObjAnimationEffects), 'synchronously');
    check(count === 1, 'non-undefined return refuses after one call'); r.animateAll(a.id, empty);
  }
  for (const caught of [false, true]) {
    const r = createSourcePObjAnimationRuntime(), a = pobj(r), b = pobj(r); a.n.next04 = b.id; let count = 0;
    rejects(() => r.animateAll(a.id, {interpretAObj() {
      count++; r.animateAll(null, undefined as unknown as SourcePObjAnimationEffects);
      if (caught) {try {r.animateAll(a.id, empty);} catch { /* outer call must fail too */ }}
      else r.animateAll(a.id, empty);
    }}), 'reentry');
    check(count === 1, 'reentry stops list even if caught'); r.animateAll(a.id, empty);
    rejects(() => r.animateAll(a.id, {interpretAObj() {throw Error('test effect failure');}}), 'test effect failure');
    r.animateAll(a.id, empty);
  }
  for (let budget = 1; budget <= 4; budget++) {
    const r = createSourcePObjAnimationRuntime(budget), nodes = Array.from({length: 4}, () => pobj(r));
    for (let i = 0; i < 3; i++) nodes[i]!.n.next04 = nodes[i+1]!.id;
    let count = 0; const run = () => r.animateAll(nodes[0]!.id, {interpretAObj() {count++;}});
    if (budget < 4) rejects(run, 'visit budget'); else run(); check(count === budget, 'visit budget retains completed prefix');
  }
  {
    const r = createSourcePObjAnimationRuntime(12001), first = pobj(r); let last = first;
    for (let i = 0; i < 12000; i++) {const next = pobj(r); last.n.next04 = next.id; last = next;}
    let count = 0, final: symbol | null = null;
    r.animateAll(first.id, {interpretAObj(_a, owner) {count++; final = owner;}});
    check(count === 12001 && final === last.id, 'deep list is iterative');
  }
  console.log('[pobj-animation] PASS: ordered mutable polygon-list dispatch and bounded failure prefixes; synthetic, no geometry receiver or original replay');
}
