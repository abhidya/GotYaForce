/** Actual owned-runtime lifetime tests, not event-only allocator mocks. */
import {createSourceFObjRuntime, type SourceFObjHeader, type SourceFObjRuntime} from './fobj-list.js';
import {createSourceFObjNullCallbackRuntime} from './fobj-timing.js';
import {evaluateSourceFObjLinearValue} from './fobj-linear.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-removal] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
function node(r: SourceFObjRuntime, fields: Partial<SourceFObjHeader> = {}): symbol {
  return r.createNode({next00: null, cursor04: null, base08: null, length0c: 0,
    flags10: 0, byte11: 0, byte12: 0, track13: 7, format14: 0x80, format15: 0x80,
    half16: 0, offset18: 0, half1a: 0, frame1c: -0,
    value20: 10, value24: 20, value28: 30, value2c: 40, ...fields});
}
function unchanged(n: SourceFObjHeader, before: SourceFObjHeader): void {
  check((Object.keys(before) as (keyof SourceFObjHeader)[]).every(key => Object.is(n[key], before[key])),
    'logical release leaves cached JS fields unchanged');
}
function released(r: SourceFObjRuntime, id: symbol, cached: SourceFObjHeader): void {
  rejects(() => r.getNode(id), 'unknown/non-owned');
  rejects(() => r.validateNode(cached), 'non-owned header');
  rejects(() => r.loadData(cached), 'non-owned header');
  rejects(() => r.loadWait(cached), 'non-owned header');
  rejects(() => evaluateSourceFObjLinearValue(r, cached), 'non-owned header');
  rejects(() => r.effects.interpretAll(id, 0, null), 'unknown/non-owned');
}
export function runFObjRemovalSelfTest(): void {
  {
    const r = createSourceFObjRuntime(() => {});
    r.removeNode(null); r.removeAll(null);
    const tail = node(r), head = node(r, {next00: tail});
    const h = r.getNode(head), t = r.getNode(tail), before = {...h};
    r.removeNode(head); released(r, head, h); unchanged(h, before);
    check(r.getNode(tail) === t, 'single removal does not traverse or release tail');
    rejects(() => r.removeNode(head), 'unknown/non-owned');
    rejects(() => r.removeAll(head), 'unknown/non-owned');
    const survivor = node(r, {next00: tail});
    r.removeNode(tail); released(r, tail, t);
    rejects(() => r.removeAll(survivor), 'unknown/non-owned');
    r.validateNode(r.getNode(survivor)); // dangling link refuses without releasing prefix
    r.removeNode(survivor);
    const foreignRuntime = createSourceFObjRuntime(() => {}), foreign = node(foreignRuntime);
    rejects(() => r.removeNode(foreign), 'unknown/non-owned');
    rejects(() => r.removeAll(foreign), 'unknown/non-owned');
    foreignRuntime.validateNode(foreignRuntime.getNode(foreign));
    rejects(() => r.removeNode(12 as unknown as symbol), 'opaque symbol');
    rejects(() => r.removeAll(undefined as unknown as symbol), 'opaque symbol');
  }
  {
    const r = createSourceFObjRuntime(() => {});
    const tail = node(r), head = node(r, {next00: tail});
    const h = r.getNode(head), t = r.getNode(tail);
    Object.assign(t, {next00: 7, flags10: NaN, frame1c: Infinity});
    const before = {...h}, tailBefore = {...t};
    rejects(() => r.removeAll(head), 'next00');
    check(r.getNode(head) === h && r.getNode(tail) === t, 'malformed tail releases no prefix');
    unchanged(h, before); unchanged(t, tailBefore);
    // Single release must ignore even malformed links and unused scalars.
    r.removeNode(tail); released(r, tail, t); unchanged(t, tailBefore);
    h.next00 = null; h.flags10 = NaN;
    Object.defineProperty(h, 'next00', {writable: false});
    const readonlyBefore = {...h};
    r.removeAll(head); released(r, head, h); unchanged(h, readonlyBefore);
  }
  {
    const r = createSourceFObjRuntime(() => {}), foreign = Symbol('foreign');
    const tail = node(r, {next00: foreign}), head = node(r, {next00: tail});
    rejects(() => r.removeAll(head), 'unknown/non-owned');
    r.validateNode(r.getNode(head)); r.validateNode(r.getNode(tail));
    r.getNode(tail).next00 = head;
    rejects(() => r.removeAll(head), 'cycle/revisited');
    r.validateNode(r.getNode(head)); r.validateNode(r.getNode(tail));
    r.getNode(tail).next00 = tail;
    rejects(() => r.removeAll(tail), 'cycle/revisited');
    r.getNode(tail).next00 = null; r.removeAll(head);
  }
  {
    const r = createSourceFObjRuntime(() => {}, 2);
    const tail = node(r), middle = node(r, {next00: tail}), head = node(r, {next00: middle});
    rejects(() => r.removeAll(head), 'node budget');
    for (const id of [head, middle, tail]) r.validateNode(r.getNode(id));
    r.removeAll(middle); // exact budget accepted
    rejects(() => r.getNode(middle), 'unknown/non-owned');
    rejects(() => r.getNode(tail), 'unknown/non-owned');
    r.removeNode(head);
  }
  for (const count of [10, 12001]) {
    const r = createSourceFObjRuntime(() => {}, count);
    let head: symbol | null = null;
    const saved: {id: symbol; n: SourceFObjHeader; before: SourceFObjHeader}[] = [];
    for (let i = 0; i < count; i++) {
      head = node(r, {next00: head});
      const n = r.getNode(head); saved.push({id: head, n, before: {...n}});
    }
    r.removeAll(head);
    for (const entry of saved) {
      released(r, entry.id, entry.n); unchanged(entry.n, entry.before);
    }
  }
  // Both public timing factories must invalidate identity and cached-header APIs.
  for (const r of [createSourceFObjNullCallbackRuntime(), createSourceFObjScalarCallbackRuntime(null)]) {
    const id = node(r), n = r.getNode(id);
    r.removeAll(id); released(r, id, n);
    rejects(() => r.interpretNode(id, NaN, null), 'unknown/non-owned');
    r.interpretNode(null, NaN, Symbol('ignored'));
  }
  {
    const r = createSourceFObjNullCallbackRuntime();
    const input = Uint8Array.from([1, 10, 3, 1, 20, 4, 1, 30]);
    const base = r.createData(input); input.fill(255);
    const fields = {base08: base, cursor04: base, length0c: 8, flags10: 1};
    const first = node(r, fields), survivor = node(r, fields);
    r.interpretNode(first, 1, null);
    const n = r.getNode(first), cursor = n.cursor04!;
    check(r.cursorOffset(base, cursor) === 5 && n.value24 === 20, 'copied stream decodes');
    r.removeNode(first); released(r, first, n);
    check(r.cursorAt(base, 5) === cursor && r.cursorOffset(base, cursor) === 5, 'canonical cursors survive');
    r.interpretNode(survivor, 1, null);
    check(r.getNode(survivor).value24 === 20, 'existing shared-stream node survives');
    r.removeAll(survivor);
    const fresh = node(r, fields);
    r.effects.requestAll(fresh, 0); r.interpretNode(fresh, 1, null);
    check(r.getNode(fresh).cursor04 === cursor && r.getNode(fresh).value24 === 20,
      'fresh identity replays retained copied data after every prior node is released');
  }
  {
    let calls = 0;
    const r = createSourceFObjRuntime(() => {
      calls++;
      r.removeNode(null); r.removeAll(null);
      for (const target of [head, other, Symbol('foreign')]) {
        rejects(() => r.removeNode(target), 'same-runtime reentry');
        rejects(() => r.removeAll(target), 'same-runtime reentry');
      }
    });
    const head = node(r, {byte12: 6, flags10: 0x86}), other = node(r);
    rejects(() => r.effects.interpretAll(head, 0, null), 'removal reentry was refused');
    rejects(() => r.effects.stopAll(head, 0, null), 'removal reentry was refused');
    check(calls === 2, 'custom list interpreter busy guard covers interpret and stop');
    check(r.getNode(head).flags10 === 0x86, 'caught refusal prevents post-interpreter stop flag clear');
    r.validateNode(r.getNode(head)); r.validateNode(r.getNode(other));
    r.removeNode(head); r.removeAll(other);
  }
  {
    const r = createSourceFObjScalarCallbackRuntime(null);
    const id = node(r, {flags10: 4, byte12: 1, half1a: 4, frame1c: 1});
    const cb = r.createCallback(() => {
      rejects(() => r.removeNode(id), 'same-runtime reentry');
    });
    rejects(() => r.interpretNode(id, 1, cb), 'removal reentry was refused');
    check(r.getNode(id).frame1c === 2 && r.getNode(id).flags10 === 4,
      'caught direct removal refusal retains earlier clock write but prevents later state5 store');
    const nullOnly = r.createCallback(() => { r.removeNode(null); r.removeAll(null); });
    r.interpretNode(id, 0, nullOnly);
    check(r.getNode(id).flags10 === 5, 'null removals do not poison active timing callback');
    r.removeAll(id);
  }
  {
    const r = createSourceFObjRuntime(() => { r.removeNode(null); r.removeAll(null); });
    const id = node(r, {byte12: 6, flags10: 0x86});
    r.effects.stopAll(id, 0, null);
    check(r.getNode(id).flags10 === 0x80, 'null removals do not poison custom interpreter');
    r.removeAll(id);
  }
  for (const entry of ['direct', 'list', 'stop'] as const) {
    const r = createSourceFObjScalarCallbackRuntime(null);
    const head = node(r, {flags10: 0x86, byte12: 6}), other = node(r);
    let calls = 0;
    const cb = r.createCallback(() => {
      calls++;
      r.removeNode(null); r.removeAll(null);
      for (const target of [head, other, Symbol('foreign')]) {
        rejects(() => r.removeNode(target), 'same-runtime reentry');
        rejects(() => r.removeAll(target), 'same-runtime reentry');
      }
    });
    rejects(() => {
      if (entry === 'direct') r.interpretNode(head, 0, cb);
      else if (entry === 'list') r.effects.interpretAll(head, 0, cb);
      else r.effects.stopAll(head, 0, cb);
    }, 'removal reentry was refused');
    check(calls === 1, 'actual scalar callback executed');
    r.validateNode(r.getNode(head)); r.validateNode(r.getNode(other));
    r.removeAll(head); r.removeNode(other);
  }
}
