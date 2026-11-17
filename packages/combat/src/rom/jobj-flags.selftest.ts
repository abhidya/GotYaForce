import {createSourceJObjScalarRuntime, type SourceJObjScalarHeader, type SourceJObjScalarRuntime} from './jobj-update.js';

function check(ok: boolean, message: string): void { if (!ok) throw Error(`[jobj-flags] ${message}`); }
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
const methods = ['setFlags', 'clearFlags', 'setFlagsAll', 'clearFlagsAll'] as const;
export function runJObjFlagsSelfTest(): void {
  // Exhaust the two independent predicates, including source's surprising clear8
  // and mask0 cases, and flags that suppress scalar updates but NOT these helpers.
  for (const method of methods) for (let selection = 0; selection < 64; selection++) {
    const before = [8, 0x40, 0x00800000, 0x01000000, 0x02000000, 0x1000]
      .reduce((f, bit, i) => f | ((selection & (1 << i)) ? bit : 0), 0);
    for (const mask of [0, 8, 0x40, 0x48, 0x80000000, 0xffffffff]) {
      const r = createSourceJObjScalarRuntime(), root = joint(r, {flags14: before});
      const untouched = {...root.n};
      const dirty = ((before ^ mask) & 8) !== 0 && !((before & 0x00800000) === 0 && (before & 0x40) !== 0);
      const afterDirty = dirty ? before | 0x40 : before;
      const expected = (method.startsWith('clear') ? afterDirty & ~mask : afterDirty | mask) >>> 0;
      r[method](root.id, mask);
      check(root.n.flags14 === expected, `${method} XOR predicate, mask store and unsigned result`);
      for (const key of Object.keys(untouched) as (keyof SourceJObjScalarHeader)[]) {
        if (key !== 'flags14') check(Object.is(root.n[key], untouched[key]), `${method} leaves ${key} unchanged`);
      }
    }
  }
  for (const method of methods) {
    const r = createSourceJObjScalarRuntime(), root = joint(r);
    const invalid = {valueOf() { throw Error('coercion'); }} as unknown as number;
    r[method](null, invalid); r[method](null, NaN);
    for (const mask of [-1, 0x100000000, NaN, Infinity, 1.5, invalid, '8' as unknown as number]) {
      rejects(() => r[method](root.id, mask), 'mask: expected uint32');
      check(root.n.flags14 === 0, 'invalid mask cannot dirty or store');
    }
    rejects(() => r[method](Symbol('foreign'), 0), 'non-owned joint identity');
    rejects(() => r[method](createSourceJObjScalarRuntime().createJoint(fields()), 0), 'non-owned joint identity');
    for (const key of Object.keys(fields()) as (keyof SourceJObjScalarHeader)[]) {
      const s = createSourceJObjScalarRuntime(), n = joint(s);
      Object.defineProperty(n.n, key, {writable: false});
      rejects(() => s[method](n.id, 8), `${key}: non-writable`);
      check(n.n.flags14 === 0, 'whole-header writability refusal precedes dirty/store');
    }
    root.n.scale30 = Infinity;
    rejects(() => r[method](root.id, 8), 'finite source float32');
    root.n.scale30 = 0; root.n.flags14 = -1;
    rejects(() => r[method](root.id, 8), 'flags14: expected uint32');
  }
  // A failed dirty walk prevents the pending final mask store, including a mask
  // that would have pruned or cleared dirty. No callback/delegate can stand in.
  for (const method of methods) {
    const clear = method.startsWith('clear');
    const r = createSourceJObjScalarRuntime(), first = joint(r), bad = joint(r);
    const root = joint(r, {flags14: clear ? 8 : 0, child10: first.id});
    first.n.sibling08 = bad.id; bad.n.rotation24 = NaN;
    rejects(() => r[method](root.id, clear ? 0x40 : 0x1008), 'finite source float32');
    check(root.n.flags14 === (clear ? 0x48 : 0x40) && first.n.flags14 === 0x40 && bad.n.flags14 === 0,
      'dirty-before-store failure prefix retains old bit8, dirty root/first, no mask store');
  }
  for (const method of ['setFlags', 'clearFlags'] as const) {
    const r = createSourceJObjScalarRuntime(), child = joint(r), sibling = joint(r);
    const root = joint(r, {child10: child.id, sibling08: sibling.id});
    r[method](root.id, 8);
    check(root.n.flags14 === (method === 'setFlags' ? 0x48 : 0x40) && child.n.flags14 === 0x40 && sibling.n.flags14 === 0,
      'single helper still propagates actual dirtiness, but only root gets mask');
    root.n.flags14 = 0x40; root.n.child10 = 17 as unknown as symbol;
    r[method](root.id, 8); // Logical dirty suppresses traversal, not mask store.
    check(root.n.flags14 === (method === 'setFlags' ? 0x48 : 0x40), 'logical-dirty short circuit ignores bad descendant');
  }
  {
    const r = createSourceJObjScalarRuntime(), leaf = joint(r), root = joint(r, {child10: leaf.id});
    r.setFlagsAll(root.id, 0x1008);
    check(root.n.flags14 === 0x1048 && leaf.n.flags14 === 0x40, 'dirty descent precedes mask-induced All pruning');
    root.n.flags14 = 0x1008; leaf.n.flags14 = 8;
    r.clearFlagsAll(root.id, 0x1000);
    check(root.n.flags14 === 0x48 && leaf.n.flags14 === 0x48, 'clear removes old prune before All descends, each child dirties independently');
  }
  {
    const r = createSourceJObjScalarRuntime(), leaf = joint(r, {flags14: 0x1001});
    const child = joint(r, {flags14: 0x1000, child10: leaf.id}), root = joint(r, {child10: child.id});
    r.clearFlagsAll(root.id, 0x1000);
    check(root.n.flags14 === 0 && child.n.flags14 === 0 && leaf.n.flags14 === 1,
      'post-store child prune opens its own descendants during clearAll');
  }
  for (const method of ['setFlagsAll', 'clearFlagsAll'] as const) {
    const r = createSourceJObjScalarRuntime(), hidden = joint(r), tail = joint(r, {flags14: 0x80000001});
    const child = joint(r, {flags14: 0x01001001, child10: hidden.id, sibling08: tail.id});
    const root = joint(r, {flags14: 1, child10: child.id}); root.n.sibling08 = 3 as unknown as symbol;
    child.n.child10 = 4 as unknown as symbol;
    r[method](root.id, 1);
    check(child.n.flags14 === (method === 'setFlagsAll' ? 0x01001001 : 0x01001000) &&
      tail.n.flags14 === (method === 'setFlagsAll' ? 0x80000001 : 0x80000000) && hidden.n.flags14 === 0,
      'flag All ignores independence, prunes child post-store, follows sibling, excludes root sibling');
    // Mutations between calls are live; no cached child/sibling plan.
    const later = joint(r, {flags14: 1}); child.n.sibling08 = later.id;
    r[method](root.id, 1);
    check(later.n.flags14 === (method === 'setFlagsAll' ? 1 : 0), 'later sibling link is read live');
  }
  for (const fault of ['foreign', 'link', 'frozen', 'float', 'flags'] as const) {
    const r = createSourceJObjScalarRuntime(), bad = joint(r), first = joint(r, {sibling08: bad.id}), root = joint(r, {child10: first.id});
    if (fault === 'foreign') first.n.sibling08 = Symbol('foreign');
    if (fault === 'link') first.n.sibling08 = 0 as unknown as symbol;
    if (fault === 'frozen') Object.freeze(bad.n);
    if (fault === 'float') bad.n.scale2c = NaN;
    if (fault === 'flags') bad.n.flags14 = -1;
    rejects(() => r.setFlagsAll(root.id, 1), {foreign: 'non-owned joint identity', link: 'opaque joint symbol',
      frozen: 'non-writable', float: 'finite source float32', flags: 'uint32'}[fault]);
    check(root.n.flags14 === 1 && first.n.flags14 === 1 && bad.n.flags14 === (fault === 'flags' ? -1 : 0),
      'lazy flag failure preserves only visited preorder mask stores');
  }
  {
    const r = createSourceJObjScalarRuntime(), root = joint(r); root.n.child10 = root.id;
    rejects(() => r.setFlagsAll(root.id, 1), 'flag traversal cycle/revisited');
    check(root.n.flags14 === 1, 'flag ancestor cycle occurs after initial store');
    const clear = createSourceJObjScalarRuntime(), clearRoot = joint(clear, {flags14: 8});
    clearRoot.n.child10 = clearRoot.id;
    rejects(() => clear.clearFlagsAll(clearRoot.id, 8), 'flag traversal cycle/revisited');
    check(clearRoot.n.flags14 === 0, 'root is already visited before a cycle could dirty its changed flags a second time');
    const s = createSourceJObjScalarRuntime(), shared = joint(s), b = joint(s, {child10: shared.id});
    const a = joint(s, {child10: shared.id, sibling08: b.id}), head = joint(s, {child10: a.id});
    rejects(() => s.setFlagsAll(head.id, 1), 'flag traversal cycle/revisited');
    check([head, a, shared, b].every(x => x.n.flags14 === 1), 'DAG revisit follows earlier DFS stores');
    const t = createSourceJObjScalarRuntime(), cycle = joint(t); cycle.n.child10 = cycle.id;
    rejects(() => t.setFlagsAll(cycle.id, 8), 'cycle/revisited');
    check(cycle.n.flags14 === 0x40, 'dirty cycle fires before root mask store or flag cycle check');
  }
  for (const budget of [0, -1, 1.5, Infinity, NaN, Number.MAX_SAFE_INTEGER + 1]) {
    rejects(() => createSourceJObjScalarRuntime(4096, budget), 'maxFlagNodes');
  }
  {
    const build = (budget: number) => {
      const r = createSourceJObjScalarRuntime(1, budget), root = joint(r), first = joint(r), leaf = joint(r), tail = joint(r);
      root.n.child10 = first.id; first.n.child10 = leaf.id; first.n.sibling08 = tail.id;
      return {r, nodes: [root, first, leaf, tail]};
    };
    for (let budget = 1; budget <= 4; budget++) {
      const {r, nodes} = build(budget), run = () => r.setFlagsAll(nodes[0]!.id, 1);
      if (budget < 4) rejects(run, 'flag inspected-node budget'); else run();
      check(nodes.every((n, index) => n.n.flags14 === (index < budget ? 1 : 0)), 'exact preorder flag budget includes root');
    }
    const r = createSourceJObjScalarRuntime(1, 20), child = joint(r), root = joint(r, {child10: child.id});
    rejects(() => r.setFlagsAll(root.id, 8), 'inspected-node budget');
    check(root.n.flags14 === 0x40 && child.n.flags14 === 0, 'dirty budget is independent and fires before root flag store');
    const prefix = createSourceJObjScalarRuntime(2, 1), pc = joint(prefix), ph = joint(prefix, {child10: pc.id});
    rejects(() => prefix.setFlagsAll(ph.id, 8), 'flag inspected-node budget');
    check(ph.n.flags14 === 0x48 && pc.n.flags14 === 0x40,
      'root dirty traversal reaches child before flag budget stops its own mask store');
    const s = createSourceJObjScalarRuntime(2, 2), c = joint(s), h = joint(s, {child10: c.id});
    s.setFlagsAll(h.id, 8);
    check(h.n.flags14 === 0x48 && c.n.flags14 === 0x48, 'dirty visits do not consume flag budget or mark flag revisits');
    const t = createSourceJObjScalarRuntime(1, 3), c2 = joint(t, {flags14: 0x1008});
    const c1 = joint(t, {flags14: 0x1008, sibling08: c2.id}), head = joint(t, {child10: c1.id});
    t.setFlagsAll(head.id, 1);
    check(c1.n.flags14 === 0x1049 && c2.n.flags14 === 0x1049, 'each nested dirty traversal has a fresh budget and set');
    const defaults = createSourceJObjScalarRuntime(), defaultRoot = joint(defaults);
    let defaultTail = defaultRoot;
    for (let i = 1; i < 4096; i++) {
      const next = joint(defaults); defaultTail.n.child10 = next.id; defaultTail = next;
    }
    defaults.setFlagsAll(defaultRoot.id, 1);
    check(defaultTail.n.flags14 === 1, 'default flag budget admits exactly 4096 visited nodes');
    const overflow = joint(defaults); defaultTail.n.child10 = overflow.id;
    rejects(() => defaults.setFlagsAll(defaultRoot.id, 2), 'flag inspected-node budget');
    check(defaultRoot.n.flags14 === 3 && defaultTail.n.flags14 === 3 && overflow.n.flags14 === 0,
      'default flag budget rejects node4097 after the 4096-node write prefix');
    const large = createSourceJObjScalarRuntime(1, 12001), top = joint(large); let last = top;
    for (let i = 0; i < 12000; i++) { const next = joint(large); last.n.child10 = next.id; last = next; }
    large.setFlagsAll(top.id, 1); check(last.n.flags14 === 1, 'iterative All walk beyond source inline depths and host stack');
  }
  console.log('[jobj-flags] PASS: bounded single/subtree set/clear with source XOR gate and actual dirty-before-store writes; synthetic, no replay/live integration');
}
