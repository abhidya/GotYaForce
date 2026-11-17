import {createSourceJObjAnimationRuntime, type SourceJObjAnimationBinding,
  type SourceJObjAnimationEffects, type SourceJObjAnimationRuntime} from './jobj-animation.js';
import type {SourceJObjScalarHeader} from './jobj-update.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import {createSourceAObj, createSourceAObjCounters, interpretSourceAObj,
  requestSourceAObj, AOBJ_REQUEST, AOBJ_STOPPED} from './aobj-clock.js';

function check(ok: boolean, message: string): void { if (!ok) throw Error(`[jobj-animation] ${message}`); }
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try {run();} catch (error) {diagnostic = String(error);}
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic}`);
}
function fields(patch: Partial<SourceJObjScalarHeader> = {}): SourceJObjScalarHeader {
  return {sibling08: null, child10: null, flags14: 0, rotation1c: -0, rotation20: 2, rotation24: 3,
    scale2c: 4, scale30: 5, scale34: 6, translation38: 7, translation3c: 8, translation40: 9, ...patch};
}
function binding(patch: Partial<SourceJObjAnimationBinding> = {}): SourceJObjAnimationBinding {
  return {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null, ...patch};
}
function joint(r: SourceJObjAnimationRuntime, scalar: Partial<SourceJObjScalarHeader> = {},
  animation: Partial<SourceJObjAnimationBinding> = {}) {
  const id = r.createJoint(fields(scalar), binding(animation));
  return {id, n: r.getJoint(id), b: r.getBinding(id)};
}
function same(actual: object, expected: object, message: string): void {
  check(Object.keys(expected).every(key => Object.is((actual as Record<string, unknown>)[key],
    (expected as Record<string, unknown>)[key])), message);
}
function recording() {
  const events: Array<{name: string; target: symbol | null; owner?: symbol; callback?: symbol | null}> = [];
  // Explicit orchestration test doubles, not RObj/DObj implementations.
  const effects: SourceJObjAnimationEffects = {
    interpretAObj(target, owner, callback) {events.push({name: 'a', target, owner, callback});},
    animateRObjs(target) {events.push({name: 'r', target});},
    animateDObjs(target) {events.push({name: 'd', target});},
  };
  return {events, effects};
}
export function runJObjAnimationSelfTest(): void {
  // Exhaust all relevant owner bits, including bits which must NOT suppress
  // dependency writes, against raw-vs-logical parent dirty states and RObj lists.
  const bits = [0x40, 0x800000, 0x1000000, 0x200000, 0x400000, 0x1000, 0x2000000, 0x80000000];
  for (let mask = 0; mask < 256; mask++) {
    const flags = bits.reduce((v, bit, index) => (v | ((mask & (1 << index)) ? bit : 0)) >>> 0, 0);
    for (const pFlags of [null, 0, 0x40, 0x800000, 0x800040, 0x1000040]) {
      for (const hasRObj of [false, true]) {
        const r = createSourceJObjAnimationRuntime(), p = joint(r, {flags14: pFlags ?? 0});
        const child = joint(r), owner = joint(r, {flags14: flags, child10: child.id},
          {parent0c: pFlags === null ? null : p.id, robj80: hasRObj ? Symbol('RObj') : null});
        const before = {...owner.n}, beforeParent = {...p.n}, beforeBinding = {...owner.b};
        let dirty = (flags & 0x800000) === 0 && (flags & 0x40) !== 0;
        if (!dirty) {
          dirty = (flags & 0x800000) === 0
            ? (pFlags !== null && (pFlags & 0x40) !== 0) || (flags & 0x600000) !== 0 || hasRObj
            : (flags & 0x1000000) === 0 && pFlags !== null && (pFlags & 0x800000) === 0 && (pFlags & 0x40) !== 0;
        }
        r.checkDepend(owner.id);
        same(owner.n, {...before, flags14: dirty ? (flags | 0x40) >>> 0 : flags}, `dependency mask${mask} parent${pFlags} robj${hasRObj}`);
        same(p.n, beforeParent, 'dependency reads but never changes parent');
        same(owner.b, beforeBinding, 'dependency never changes bindings');
        check(child.n.flags14 === 0, 'dependency never dirties a child subtree');
      }
    }
  }
  {
    const r = createSourceJObjAnimationRuntime();
    r.checkDepend(null); r.animateJoint(null, undefined as unknown as SourceJObjAnimationEffects);
    for (const flags of [0x40, 0x1800000, 0x1800040]) {
      const o = joint(r, {flags14: flags});
      o.b.parent0c = 7 as unknown as symbol; o.b.robj80 = 9 as unknown as symbol;
      r.checkDepend(o.id); check(o.n.flags14 === flags, 'source-short-circuited links are not validated');
    }
    const o = joint(r, {flags14: 0x200000}, {parent0c: Symbol('foreign')});
    rejects(() => r.checkDepend(o.id), 'non-owned joint identity');
    check(o.n.flags14 === 0x200000, 'parent is resolved before sufficient mode bits');
    o.b.parent0c = null; o.b.robj80 = 9 as unknown as symbol;
    r.checkDepend(o.id); check(o.n.flags14 === 0x200040, 'mode bits short-circuit malformed RObj during dependency only');
    const self = joint(r); self.b.parent0c = self.id; r.checkDepend(self.id);
    check(self.n.flags14 === 0, 'parent self-reference is a single lookup, not recursive traversal');
  }
  for (const flags of [0, 0x20, 0x4000, 0x4020, 0x1000, 0x1000000, 0x2000000, 0x80000000]) {
    const r = createSourceJObjAnimationRuntime(), o = joint(r, {flags14: flags}), f = recording();
    r.animateJoint(o.id, f.effects);
    check(f.events.map(e => e.name).join() === ((flags & 0x4020) ? 'a,r' : 'a,r,d'), 'only 4020 gates DObj; all other source calls still run');
    check(f.events.every(e => e.target === null) && f.events[0]!.owner === o.id && f.events[0]!.callback === null,
      'null targets forwarded and owner/callback passed explicitly');
  }
  {
    const r = createSourceJObjAnimationRuntime(), a = Symbol('a'), cb = Symbol('callback');
    const r1 = Symbol('r1'), r2 = Symbol('r2'), d1 = Symbol('d1'), d2 = Symbol('d2');
    const o = joint(r, {flags14: 0x200000}, {aobj7c: a, classUpdate50: cb, robj80: r1, dobj18: d1});
    const events: string[] = [];
    r.animateJoint(o.id, {
      interpretAObj(target, owner, callback) {
        check(o.n.flags14 === 0x200040 && target === a && owner === o.id && callback === cb, 'dependency precedes exact AObj dispatch');
        events.push('a'); o.b.robj80 = r2; o.b.classUpdate50 = Symbol('future callback');
        o.n.flags14 = 0x200020; // Clear dirty but retain dependency mode: no second dependency check.
      },
      animateRObjs(target) {
        check(target === r2 && o.n.flags14 === 0x200020, 'RObj reload after AObj without rechecking dependency');
        events.push('r'); o.n.flags14 &= ~0x20; o.b.dobj18 = d2;
      },
      animateDObjs(target) {check(target === d2 && o.n.flags14 === 0x200000, 'DObj pointer and flags reload after RObj'); events.push('d');},
    });
    check(events.join() === 'a,r,d', 'mutable dispatch order');
  }
  {
    const r = createSourceJObjAnimationRuntime(), o = joint(r), events: string[] = [];
    o.b.robj80 = 12 as unknown as symbol; o.n.flags14 = 0x40; // Dependency does not inspect it.
    r.animateJoint(o.id, {
      interpretAObj() {events.push('a'); o.b.robj80 = null;},
      animateRObjs() {events.push('r'); o.n.flags14 |= 0x4000; o.b.dobj18 = 12 as unknown as symbol;},
      animateDObjs() {throw Error('gated DObj effect should not run');},
    });
    check(events.join() === 'a,r', 'AObj may fix a later RObj argument and RObj may gate unread invalid DObj');
    o.n.flags14 = 0; o.b.parent0c = Symbol('foreign');
    rejects(() => r.animateJoint(o.id, recording().effects), 'non-owned joint identity');
    check(o.n.flags14 === 0, 'dependency refuses unresolved parent before any effect');
  }
  {
    const r = createSourceJObjAnimationRuntime(), input = binding(), o = r.createJoint(fields(), input);
    input.parent0c = Symbol('other'); check(r.getBinding(o).parent0c === null, 'binding copied rather than retained');
    check(Object.isSealed(r.getBinding(o)) && !Object.isFrozen(r.getBinding(o)), 'binding sealed mutable data');
    rejects(() => r.getBinding(Symbol('foreign')), 'non-owned animation binding');
    const foreign = joint(createSourceJObjAnimationRuntime());
    rejects(() => r.animateJoint(foreign.id, recording().effects), 'non-owned joint identity');
    rejects(() => r.createJoint(fields(), null as unknown as SourceJObjAnimationBinding), 'data record');
    let read = false; const access = binding();
    Object.defineProperty(access, 'aobj7c', {get() {read = true; return null;}});
    rejects(() => r.createJoint(fields(), access), 'own data property'); check(!read, 'binding accessor not invoked');
    rejects(() => r.createJoint(fields(), Object.create(binding()) as SourceJObjAnimationBinding), 'own data property');
    for (const key of Object.keys(binding()) as (keyof SourceJObjAnimationBinding)[]) {
      rejects(() => r.createJoint(fields(), binding({[key]: 7} as unknown as SourceJObjAnimationBinding)), 'opaque symbol');
      const x = joint(r, {flags14: 0x200000}); Object.defineProperty(x.b, key, {writable: false});
      rejects(() => r.animateJoint(x.id, recording().effects), `${key}: non-writable`);
      check(x.n.flags14 === 0x200000, 'immutable binding refused before dependency write');
    }
    const broken = joint(r, {flags14: 0x200000});
    rejects(() => r.animateJoint(broken.id, {interpretAObj() {}} as unknown as SourceJObjAnimationEffects), 'all three');
    check(broken.n.flags14 === 0x200000, 'effect-set preflight refuses before dependency write');
  }
  for (const key of ['classUpdate50', 'aobj7c', 'robj80', 'dobj18'] as const) {
    const r = createSourceJObjAnimationRuntime(), o = joint(r, {flags14: 0x200000}), f = recording();
    o.b[key] = 7 as unknown as symbol;
    rejects(() => r.animateJoint(o.id, f.effects), `${key}: expected opaque`);
    check(o.n.flags14 === 0x200040 && f.events.map(e => e.name).join() ===
      ({classUpdate50: '', aobj7c: '', robj80: 'a', dobj18: 'a,r'}[key]),
    `invalid ${key} refuses only when read, retaining exact dependency/effect prefix`);
  }
  for (const key of ['interpretAObj', 'animateRObjs', 'animateDObjs'] as const) {
    const r = createSourceJObjAnimationRuntime(), o = joint(r, {flags14: 0x200000}), f = recording();
    const before = {...o.n}, selector = Symbol('original callback'); o.b.classUpdate50 = selector;
    let getterRead = false;
    Object.defineProperty(f.effects, key, {get() {
      getterRead = true; o.b.classUpdate50 = Symbol('changed callback');
      r.checkDepend(o.id); return () => {};
    }});
    rejects(() => r.animateJoint(o.id, f.effects), 'own data-function');
    check(!getterRead && !f.events.length && o.b.classUpdate50 === selector,
      `accessor effect ${key} rejected without getter mutation/reentry`);
    same(o.n, before, 'accessor effect rejection precedes dependency write');
  }
  {
    const r = createSourceJObjAnimationRuntime(), o = joint(r), f = recording();
    rejects(() => r.animateJoint(o.id, Object.create(f.effects) as SourceJObjAnimationEffects), 'own data-function');
    const e: SourceJObjAnimationEffects = {...f.effects, interpretAObj(target, owner, cb) {
      check(this === e, 'data effects keep their original table as receiver');
      f.effects.interpretAObj(target, owner, cb);
      e.animateRObjs = () => {throw Error('effect methods must not be reread');};
      e.animateDObjs = () => {throw Error('effect methods must not be reread');};
    }};
    r.animateJoint(o.id, e);
    check(f.events.map(event => event.name).join() === 'a,r,d', 'static callee effect methods are copied once before dispatch');
  }
  {
    const r = createSourceJObjAnimationRuntime(), o = joint(r), f = recording();
    r.animateJoint(o.id, {...f.effects, interpretAObj(target, owner, cb) {
      f.effects.interpretAObj(target, owner, cb);
      o.b.aobj7c = 7 as unknown as symbol; o.b.classUpdate50 = 8 as unknown as symbol;
      o.b.parent0c = 9 as unknown as symbol;
    }});
    check(f.events.map(e => e.name).join() === 'a,r,d', 'already consumed bindings are not reread after AObj effect');
    o.b.parent0c = null;
    rejects(() => r.animateJoint(o.id, recording().effects), 'classUpdate50: expected opaque');
  }
  for (const where of ['a', 'r', 'd']) {
    for (const how of ['throw', 'return', 'reenter', 'freeze', 'nan']) {
      const r = createSourceJObjAnimationRuntime(), o = joint(r, {flags14: 0x200000}), calls: string[] = [];
      function effect(name: string): void {
        calls.push(name); o.n.translation38++;
        if (name !== where) return;
        if (how === 'throw') throw Error('deliberate effect failure');
        if (how === 'return') return 1 as unknown as void;
        if (how === 'reenter') r.checkDepend(o.id);
        if (how === 'freeze') Object.defineProperty(o.b, 'parent0c', {writable: false});
        if (how === 'nan') o.n.translation40 = NaN;
      }
      rejects(() => r.animateJoint(o.id, {interpretAObj() {return effect('a');}, animateRObjs() {return effect('r');}, animateDObjs() {return effect('d');}}),
        {throw: 'deliberate effect failure', return: 'return undefined', reenter: 'reentry', freeze: 'non-writable', nan: 'finite source float32'}[how]!);
      const count = ['a', 'r', 'd'].indexOf(where) + 1;
      check(calls.join() === ['a', 'r', 'd'].slice(0, count).join() && o.n.flags14 === 0x200040 && o.n.translation38 === 7 + count,
        `failure${where}/${how} retains dependency and exactly completed effects`);
      if (how === 'throw' || how === 'return' || how === 'reenter') r.animateJoint(o.id, recording().effects);
    }
  }
  {
    const r = createSourceJObjAnimationRuntime(), o = joint(r, {flags14: 0x200000});
    rejects(() => r.animateJoint(o.id, {...recording().effects, interpretAObj() {return Promise.resolve() as unknown as void;}}), 'return undefined');
    check(o.n.flags14 === 0x200040, 'thenable return rejected with dependency write retained');
  }
  // Real AObj/FObj/JObj composition, with explicit refusal of unsupported RObj
  // and DObj work. These are absent lists, not guessed custom implementations.
  {
    const j = createSourceJObjAnimationRuntime(), child = joint(j), owner = joint(j, {child10: child.id});
    child.b.parent0c = owner.id;
    const f = createSourceFObjScalarCallbackRuntime(owner.id), data = f.createData(Uint8Array.from([2, 10, 4, 2, 18]));
    const node = f.createNode({next00: null, cursor04: data, base08: data, length0c: 5,
      flags10: 1, byte11: 0, byte12: 0, track13: 5, format14: 0x80, format15: 0x80,
      half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 3, rate: 2, fobjs: node});
    const aid = Symbol('owned AObj'), counts = createSourceAObjCounters();
    owner.b.aobj7c = aid; owner.b.classUpdate50 = f.createCallback(j.updateScalar);
    const e: SourceJObjAnimationEffects = {
      interpretAObj(id, target, cb) {
        if (id !== aid || target !== owner.id) throw Error('unbound AObj/owner');
        interpretSourceAObj(a, cb, f.effects, counts);
      },
      animateRObjs(list) {if (list !== null) throw Error('unsupported RObj');},
      animateDObjs(list) {if (list !== null) throw Error('unsupported DObj');},
    };
    requestSourceAObj(a, 0, f.effects); check(a.flags === AOBJ_REQUEST, 'actual AObj request prepared');
    j.animateJoint(owner.id, e);
    check(a.frame === 0 && owner.n.translation38 === 10 && owner.n.flags14 === 0x40 && child.n.flags14 === 0x40 && counts.running === 1,
      'per-joint dispatcher runs real requested linear FObj and scalar dirty subtree');
    j.animateJoint(owner.id, e);
    check(a.frame === 2 && owner.n.translation38 === 14 && counts.running === 2, 'real second animation tick');
    j.animateJoint(owner.id, e);
    check(a.frame === 4 && owner.n.translation38 === 18 && (a.flags & AOBJ_STOPPED) !== 0 && counts.stopped === 1,
      'real end overshoot and stop persist through source JObj dispatch');
    owner.b.robj80 = Symbol('not implemented');
    rejects(() => j.animateJoint(owner.id, e), 'unsupported RObj');
    check(a.frame === 4 && counts.stopped === 1 && owner.n.translation38 === 18,
      'unsupported RObj is not swallowed after stopped AObj');
  }
  console.log('[jobj-animation] PASS: source dependency and one-joint ordered AObj/RObj/DObj effects with real bounded AObj/FObj/JObj composition; synthetic, no original replay or live integration');
}
