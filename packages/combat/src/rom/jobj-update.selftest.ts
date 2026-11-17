import {createSourceJObjScalarRuntime, type SourceJObjScalarHeader, type SourceJObjScalarRuntime} from './jobj-update.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
import type {SourceFObjHeader, SourceFObjRuntime} from './fobj-list.js';
import {AOBJ_NO_CALLBACK, AOBJ_STOPPED, createSourceAObj, createSourceAObjCounters,
  interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';

function check(ok: boolean, message: string): void { if (!ok) throw Error(`[jobj-update] ${message}`); }
function rejects(run: () => void, expected: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(expected), `expected ${expected}, got ${diagnostic}`);
}
function fields(patch: Partial<SourceJObjScalarHeader> = {}): SourceJObjScalarHeader {
  return {sibling08: null, child10: null, flags14: 0, rotation1c: -0, rotation20: 2, rotation24: 3,
    scale2c: 4, scale30: -0, scale34: 6, translation38: 7, translation3c: 8, translation40: -0, ...patch};
}
function joint(r: SourceJObjScalarRuntime, patch: Partial<SourceJObjScalarHeader> = {}) {
  const id = r.createJoint(fields(patch)); return {id, n: r.getJoint(id)};
}
function same(actual: SourceJObjScalarHeader, expected: SourceJObjScalarHeader, message: string): void {
  check((Object.keys(expected) as (keyof SourceJObjScalarHeader)[]).every(key => Object.is(actual[key], expected[key])), message);
}
function fobj(r: SourceFObjRuntime, bytes: number[] = [], patch: Partial<SourceFObjHeader> = {}) {
  const base = r.createData(Uint8Array.from(bytes));
  const id = r.createNode({next00: null, cursor04: base, base08: base, length0c: bytes.length,
    flags10: 1, byte11: 0, byte12: 0, track13: 7, format14: 0x80, format15: 0x80,
    half16: 0, offset18: 0, half1a: 0, frame1c: 0,
    value20: 0, value24: 0, value28: 0, value2c: 0, ...patch});
  return {id, n: r.getNode(id)};
}
const trackFields = [[1, 'rotation1c'], [2, 'rotation20'], [3, 'rotation24'],
  [5, 'translation38'], [6, 'translation3c'], [7, 'translation40'],
  [8, 'scale2c'], [9, 'scale30'], [10, 'scale34']] as const;

export function runJObjUpdateSelfTest(): void {
  for (const [track, field] of trackFields) {
    for (const value of [13.25, 0, -0, 2 ** -149, -(2 ** -149), 2 ** -126 - 2 ** -149,
      2 ** -126, (2 - 2 ** -23) * 2 ** 127]) {
      const r = createSourceJObjScalarRuntime(), j = joint(r, {flags14: 0x80000000});
      const before = {...j.n};
      check(r.updateScalar(j.id, track, value) === undefined, 'scalar handler returns undefined synchronously');
      same(j.n, {...before, [field]: value, flags14: 0x80000040}, `exact track${track} field and unrelated scalars/uint32 bits`);
    }
  }
  {
    const r = createSourceJObjScalarRuntime(), initial = fields(), id = r.createJoint(initial), n = r.getJoint(id);
    initial.rotation1c = 99; initial.child10 = Symbol('foreign'); n.translation40 = 123;
    check(Object.is(n.rotation1c, -0) && n.child10 === null && Object.is(initial.translation40, -0) &&
      Object.isSealed(n) && !Object.isFrozen(n), 'factory makes independent sealed mutable data records');
    const frozenInput = Object.freeze(fields()); r.updateScalar(r.createJoint(frozenInput), 1, 5);
    rejects(() => r.validateJoint(fields()), 'non-owned joint header');
    const other = createSourceJObjScalarRuntime(), foreign = joint(other);
    rejects(() => r.validateJoint(foreign.n), 'non-owned joint header');
    rejects(() => r.getJoint(Symbol('foreign')), 'non-owned joint identity');
    rejects(() => r.updateScalar(foreign.id, 1, 5), 'non-owned joint identity');
    rejects(() => r.updateScalar(n as unknown as symbol, 1, 5), 'non-owned joint identity');
    let getterRead = false;
    const accessor = fields(); Object.defineProperty(accessor, 'rotation1c', {get() { getterRead = true; return 1; }});
    rejects(() => r.createJoint(accessor), 'own data property'); check(!getterRead, 'input accessors are not invoked');
    rejects(() => r.createJoint(Object.create(fields()) as SourceJObjScalarHeader), 'own data property');
    rejects(() => r.createJoint(null as unknown as SourceJObjScalarHeader), 'data record');
    rejects(() => r.createJoint(fields({child10: 3 as unknown as symbol})), 'opaque joint symbol');
    const ignored = {valueOf() { throw Error('null owner inspected an argument'); }} as unknown as number;
    r.updateScalar(null, ignored, ignored); r.updateScalar(null, NaN, Infinity);
    check(n.flags14 === 0, 'null owner genuinely returns without any argument validation or writes');
  }
  for (const track of [0, 4, 11, 12, 50, 255, -1, 1.5, NaN, Infinity, '1' as unknown as number]) {
    const r = createSourceJObjScalarRuntime(), j = joint(r), before = {...j.n};
    rejects(() => r.updateScalar(j.id, track, 9), 'unsupported scalar track'); same(j.n, before, 'unimplemented track refuses before writes');
  }
  for (const [track] of trackFields) {
    for (const bits of [0x20000, 0x200000, 0x220000]) {
      const r = createSourceJObjScalarRuntime(), j = joint(r, {flags14: bits}), before = {...j.n};
      if (track <= 3 && (bits & 0x20000) !== 0) {
        rejects(() => r.updateScalar(j.id, track, 9), 'quaternion'); same(j.n, before, 'quaternion refusal has no writes');
      } else if (track === 1 && (bits & 0x200000) !== 0) {
        rejects(() => r.updateScalar(j.id, track, 9), 'RObj'); same(j.n, before, 'RObj branch refused without stubbed effects');
      } else {
        r.updateScalar(j.id, track, 9); check(j.n.flags14 === (bits | 0x40), 'unrelated quaternion/RObj flags remain admitted');
      }
    }
  }
  for (const value of [NaN, Infinity, -Infinity, 0.1, 2 ** 128, undefined as unknown as number]) {
    const r = createSourceJObjScalarRuntime(), j = joint(r), before = {...j.n};
    rejects(() => r.updateScalar(j.id, 7, value), 'finite source float32'); same(j.n, before, 'invalid value preflight');
    rejects(() => r.createJoint(fields({scale34: value})), 'finite source float32');
  }
  for (const value of [-1, 1.5, NaN, Infinity, 0x100000000]) {
    rejects(() => createSourceJObjScalarRuntime().createJoint(fields({flags14: value})), 'uint32');
  }
  for (const max of [0, -1, 1.5, Infinity, NaN, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => createSourceJObjScalarRuntime(max), 'maxNodes');
  }
  // Exhaust root flag combinations. Root independence (01000000) is ignored;
  // suppression (02000000), logical dirty and prune are distinct gates.
  for (let mask = 0; mask < 32; mask++) {
    const bits = [0x02000000, 0x01000000, 0x00800000, 0x40, 0x1000]
      .reduce((flags, bit, index) => flags | ((mask & (1 << index)) ? bit : 0), 0);
    const r = createSourceJObjScalarRuntime(), child = joint(r), sibling = joint(r);
    const root = joint(r, {flags14: bits, child10: child.id, sibling08: sibling.id});
    const dirty = (bits & 0x02000000) === 0 && !((bits & 0x00800000) === 0 && (bits & 0x40) !== 0);
    r.updateScalar(root.id, 7, 27);
    check(root.n.translation40 === 27 && root.n.flags14 === (dirty ? bits | 0x40 : bits) &&
      child.n.flags14 === (dirty && (bits & 0x1000) === 0 ? 0x40 : 0) && sibling.n.flags14 === 0,
      `root mask${mask} selected store, root-only gates, child descent and no root sibling`);
  }
  // Descendant gates differ from root gates; quaternion/RObj flags on a
  // descendant never trigger the owner's rotation-specific exclusions.
  for (let mask = 0; mask < 32; mask++) {
    const bits = [0x02000000, 0x01000000, 0x00800000, 0x40, 0x1000]
      .reduce((flags, bit, index) => flags | ((mask & (1 << index)) ? bit : 0), 0) | 0x220000;
    const r = createSourceJObjScalarRuntime(), leaf = joint(r), sibling = joint(r);
    const child = joint(r, {flags14: bits, child10: leaf.id, sibling08: sibling.id});
    const root = joint(r, {child10: child.id});
    const dirty = (bits & 0x01000000) === 0 && !((bits & 0x00800000) === 0 && (bits & 0x40) !== 0);
    r.updateScalar(root.id, 1, 19);
    check(root.n.rotation1c === 19 && root.n.flags14 === 0x40 && child.n.flags14 === (dirty ? bits | 0x40 : bits) &&
      leaf.n.flags14 === (dirty && (bits & 0x1000) === 0 ? 0x40 : 0) && sibling.n.flags14 === 0x40,
      `child mask${mask} skip/prune preserves sibling continuation and root-only exclusions`);
  }
  {
    // Lazy links: even corrupt host values are not read on source-pruned paths.
    const bad = 123 as unknown as symbol;
    for (const rootBits of [0x02000000, 0x40, 0x1000]) {
      const r = createSourceJObjScalarRuntime(), root = joint(r, {flags14: rootBits});
      root.n.child10 = bad; root.n.sibling08 = bad;
      r.updateScalar(root.id, 5, 21); check(root.n.translation38 === 21, 'unfollowed root links remain unread');
    }
    for (const childBits of [0x01000000, 0x40, 0x1000]) {
      const r = createSourceJObjScalarRuntime(), tail = joint(r), child = joint(r, {flags14: childBits, sibling08: tail.id});
      const root = joint(r, {child10: child.id}); child.n.child10 = bad; root.n.sibling08 = bad;
      r.updateScalar(root.id, 5, 21); check(tail.n.flags14 === 0x40, 'unfollowed child link does not stop later sibling');
    }
    const r = createSourceJObjScalarRuntime(), root = joint(r), child = joint(r, {flags14: 0x1000});
    root.n.child10 = child.id; child.n.child10 = child.id;
    r.updateScalar(root.id, 5, 21); check(child.n.flags14 === 0x1040, 'cycle hidden by prune is not inspected');
  }
  for (const fault of ['frozen', 'float', 'flags', 'link', 'foreign'] as const) {
    const r = createSourceJObjScalarRuntime(), bad = joint(r), first = joint(r, {sibling08: bad.id});
    const root = joint(r, {child10: first.id, scale30: 19}), before = {...bad.n};
    if (fault === 'frozen') Object.freeze(bad.n);
    if (fault === 'float') bad.n.rotation20 = Infinity;
    if (fault === 'flags') bad.n.flags14 = -1;
    if (fault === 'link') first.n.sibling08 = 7 as unknown as symbol;
    if (fault === 'foreign') first.n.sibling08 = createSourceJObjScalarRuntime().createJoint(fields());
    rejects(() => r.updateScalar(root.id, 9, -0), {frozen: 'non-writable', float: 'finite source float32',
      flags: 'uint32', link: 'opaque joint symbol', foreign: 'non-owned joint identity'}[fault]);
    check(Object.is(root.n.scale30, -0) && root.n.flags14 === 0x40 && first.n.flags14 === 0x40 &&
      bad.n.flags14 === (fault === 'flags' ? -1 : before.flags14), 'lazy failure preserves scalar/root/earlier child writes only');
  }
  for (const fault of ['frozen', 'float', 'flags'] as const) {
    const r = createSourceJObjScalarRuntime(), root = joint(r);
    if (fault === 'frozen') Object.freeze(root.n);
    if (fault === 'float') root.n.scale2c = NaN;
    if (fault === 'flags') root.n.flags14 = -1;
    const before = {...root.n};
    rejects(() => r.updateScalar(root.id, 5, 17), {frozen: 'non-writable', float: 'finite source float32', flags: 'uint32'}[fault]);
    same(root.n, before, 'invalid owned root refuses before selected store');
  }
  // Each field is part of the explicit mutable-record contract. Freezing every
  // property would not catch a regression that checks only flags writability.
  for (const key of Object.keys(fields()) as (keyof SourceJObjScalarHeader)[]) {
    const r = createSourceJObjScalarRuntime(), root = joint(r), before = {...root.n};
    Object.defineProperty(root.n, key, {writable: false});
    rejects(() => r.updateScalar(root.id, 5, 17), `${key}: non-writable`);
    same(root.n, before, `individually non-writable root ${key} refuses before scalar store`);

    const s = createSourceJObjScalarRuntime(), hidden = joint(s);
    const child = joint(s, {flags14: 0x01000000, child10: hidden.id}), owner = joint(s, {child10: child.id});
    const childBefore = {...child.n};
    Object.defineProperty(child.n, key, {writable: false});
    rejects(() => s.updateScalar(owner.id, 5, 18), `${key}: non-writable`);
    check(owner.n.translation38 === 18 && owner.n.flags14 === 0x40 && hidden.n.flags14 === 0,
      `individually non-writable skipped child ${key} preserves only earlier root writes`);
    same(child.n, childBefore, `non-writable skipped child ${key} remains unchanged`);
  }
  {
    const r = createSourceJObjScalarRuntime(), hidden = joint(r), skipped = joint(r, {flags14: 0x01000000, child10: hidden.id});
    const root = joint(r, {child10: skipped.id}); Object.freeze(hidden.n);
    r.updateScalar(root.id, 5, 17); check(root.n.flags14 === 0x40 && hidden.n.flags14 === 0, 'unvisited frozen subtree is not preflighted');
    root.n.flags14 = 0; skipped.n.scale34 = Infinity;
    rejects(() => r.updateScalar(root.id, 5, 18), 'finite source float32');
    check(root.n.translation38 === 18 && root.n.flags14 === 0x40 && skipped.n.flags14 === 0x01000000,
      'examined skipped header still has explicit host scalar validation, after root writes');
  }
  for (const childBits of [0, 0x01000000, 0x40, 0x00800040]) {
    const r = createSourceJObjScalarRuntime(), child = joint(r, {flags14: childBits}), root = joint(r, {child10: child.id});
    child.n.sibling08 = child.id;
    rejects(() => r.updateScalar(root.id, 7, 31), 'cycle/revisited');
    check(root.n.translation40 === 31 && root.n.flags14 === 0x40 &&
      child.n.flags14 === (childBits === 0 || childBits === 0x00800040 ? childBits | 0x40 : childBits),
      'cycle guard counts skipped siblings and retains prior writes');
  }
  {
    const r = createSourceJObjScalarRuntime(), root = joint(r); root.n.child10 = root.id;
    rejects(() => r.updateScalar(root.id, 7, 31), 'cycle/revisited');
    check(root.n.translation40 === 31 && root.n.flags14 === 0x40, 'ancestor cycle host refusal occurs after initial writes');
    const s = createSourceJObjScalarRuntime(), shared = joint(s), b = joint(s, {child10: shared.id});
    const a = joint(s, {child10: shared.id, sibling08: b.id}), head = joint(s, {child10: a.id});
    rejects(() => s.updateScalar(head.id, 7, 31), 'cycle/revisited');
    check([head, a, shared, b].every(x => x.n.flags14 === 0x40), 'DAG revisit rejected even when source would skip dirty target');
  }
  {
    // Every possible budget cut witnesses preorder writes beyond the source's
    // inlined levels, then sibling continuation through pruned/skipped nodes.
    const build = (budget: number) => {
      const r = createSourceJObjScalarRuntime(budget), root = joint(r), branch = joint(r);
      root.n.child10 = branch.id;
      const inspected = [root, branch]; let last = branch;
      for (let depth = 0; depth < 9; depth++) {
        const next = joint(r); last.n.child10 = next.id; inspected.push(next); last = next;
      }
      const pruned = joint(r, {flags14: 0x1000, child10: Symbol('unvisited')}), independent = joint(r, {flags14: 0x01000000});
      const dirty = joint(r, {flags14: 0x40}), tail = joint(r);
      branch.n.sibling08 = pruned.id; pruned.n.sibling08 = independent.id;
      independent.n.sibling08 = dirty.id; dirty.n.sibling08 = tail.id;
      inspected.push(pruned, independent, dirty, tail);
      return {r, root, inspected, before: inspected.map(x => x.n.flags14)};
    };
    const length = build(100).inspected.length;
    for (let budget = 1; budget <= length; budget++) {
      const f = build(budget), run = () => f.r.updateScalar(f.root.id, 7, 97);
      if (budget < length) rejects(run, 'inspected-node budget'); else run();
      check(f.root.n.translation40 === 97, 'scalar precedes even earliest traversal budget failure');
      for (let index = 0; index < length; index++) {
        const before = f.before[index]!;
        check(f.inspected[index]!.n.flags14 === (index < budget && (before & 0x01000000) === 0 ? before | 0x40 : before),
          `DFS budget${budget} index${index}: no breadth-first writes or skipped-node budget holes`);
      }
    }
    // No hidden recursion/depth-six cap and no call-stack-sized limit.
    const r = createSourceJObjScalarRuntime(12001), root = joint(r); let last = root;
    for (let i = 0; i < 12000; i++) { const child = joint(r); last.n.child10 = child.id; last = child; }
    r.updateScalar(root.id, 5, 11); check(last.n.flags14 === 0x40, 'deep iterative source traversal reaches final descendant');
  }
  // Real packed streams feed the receiver through the existing FObj handler,
  // not a recorded effect or substituted per-node interpolator.
  for (const scenario of [
    {bytes: [1, 10, 3, 1, 20, 4, 1, 30], track: 1, delta: 1, value: 10, next: 7, final: 30},
    {bytes: [2, 10, 4, 2, 18], track: 7, delta: 2, value: 14, next: 1, final: 16},
    {bytes: [0x16, 10, 3, 20], track: 9, delta: 1, value: 10, next: 2, final: 20},
  ]) {
    const j = createSourceJObjScalarRuntime(), leaf = joint(j), child = joint(j, {child10: leaf.id}), root = joint(j, {child10: child.id});
    const r = createSourceFObjScalarCallbackRuntime(root.id), f = fobj(r, scenario.bytes, {track13: scenario.track});
    const callback = r.createCallback(j.updateScalar);
    r.effects.requestAll(f.id, 0); r.effects.interpretAll(f.id, scenario.delta, callback);
    const field = trackFields.find(([track]) => track === scenario.track)![1];
    check(root.n[field] === scenario.value && [root, child, leaf].every(x => x.n.flags14 === 0x40),
      'owned constant/linear/key stream writes actual joint transform and descendant dirty flags');
    r.effects.interpretAll(f.id, scenario.next, callback);
    check(root.n[field] === scenario.final, 'later stream delivery updates an already-dirty owner');
  }
  {
    const j = createSourceJObjScalarRuntime(), child = joint(j), root = joint(j, {child10: child.id});
    const r = createSourceFObjScalarCallbackRuntime(root.id), f = fobj(r, [2, 10, 4, 2, 18], {track13: 5});
    const callback = r.createCallback(j.updateScalar), counts = createSourceAObjCounters();
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 20, rate: 2, fobjs: f.id});
    requestSourceAObj(a, 0, r.effects); interpretSourceAObj(a, callback, r.effects, counts);
    check(a.frame === 0 && root.n.translation38 === 10 && child.n.flags14 === 0x40 && counts.running === 1,
      'AObj request gate and real linear callback write owned JObj subtree');
    interpretSourceAObj(a, callback, r.effects, counts);
    check(a.frame === 2 && root.n.translation38 === 14 && counts.running === 2, 'AObj clock advances real FObj linear receiver');
  }
  {
    const j = createSourceJObjScalarRuntime(), child = joint(j), root = joint(j, {child10: child.id});
    const r = createSourceFObjScalarCallbackRuntime(root.id), f = fobj(r, [], {flags10: 0x86, byte12: 6, value20: 22, track13: 8});
    const callback = r.createCallback(j.updateScalar), counts = createSourceAObjCounters();
    const a = createSourceAObj({flags: AOBJ_NO_CALLBACK, frame: 0, rewind: 0, end: 2, rate: 1, fobjs: f.id});
    interpretSourceAObj(a, callback, r.effects, counts);
    check(root.n.scale2c === 4 && child.n.flags14 === 0 && f.n.flags10 === 0x86, 'ordinary NO_CALLBACK path does not touch receiver');
    interpretSourceAObj(a, callback, r.effects, counts);
    check(root.n.scale2c === 22 && child.n.flags14 === 0x40 && f.n.flags10 === 0 && (a.flags & AOBJ_STOPPED) !== 0 &&
      counts.stopped === 1, 'end StopAll dispatches actual key receiver despite NO_CALLBACK');
  }
  {
    const j = createSourceJObjScalarRuntime(), root = joint(j, {flags14: 0x200000}), before = {...root.n};
    const r = createSourceFObjScalarCallbackRuntime(root.id), f = fobj(r, [], {flags10: 0x86, byte12: 6, value20: 22, track13: 1});
    const callback = r.createCallback(j.updateScalar);
    rejects(() => r.interpretNode(f.id, 1, callback), 'RObj');
    same(root.n, before, 'unsupported receiver branch refuses all JObj writes');
    check(f.n.flags10 === 6 && f.n.frame1c === 1, 'receiver refusal retains earlier FObj clock and key80 clear');
    const nil = createSourceFObjScalarCallbackRuntime(null), n = fobj(nil, [], {flags10: 0x86, byte12: 6, track13: 4, value20: 22});
    nil.interpretNode(n.id, 1, nil.createCallback(j.updateScalar));
    check(n.n.flags10 === 6, 'explicit null JObj owner consumes actual key callback without inspecting unsupported track');
  }
  {
    const j = createSourceJObjScalarRuntime(1), child = joint(j), root = joint(j, {child10: child.id});
    const r = createSourceFObjScalarCallbackRuntime(root.id), f = fobj(r, [], {flags10: 0x84, byte12: 6, half1a: 9, value20: 22, track13: 10});
    const callback = r.createCallback(j.updateScalar);
    rejects(() => r.interpretNode(f.id, 1, callback), 'inspected-node budget');
    check(f.n.flags10 === 4 && f.n.frame1c === 1 && root.n.scale34 === 22 && root.n.flags14 === 0x40 && child.n.flags14 === 0,
      'receiver lazy failure retains FObj key clear and JObj partial writes, without FObj state4 continuation');
  }
  console.log('[jobj-update] PASS: bounded nine-track JObj scalar stores and actual subtree dirty writes with FObj/AObj composition; synthetic tests, no original replay or live integration');
}
