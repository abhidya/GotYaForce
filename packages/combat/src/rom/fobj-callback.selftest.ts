import {createSourceFObjScalarCallbackRuntime, type SourceFObjScalarHandler} from './fobj-callback.js';
import {createSourceFObjNullCallbackRuntime} from './fobj-timing.js';
import type {SourceFObjHeader, SourceFObjRuntime} from './fobj-list.js';
import {AOBJ_LOOP, AOBJ_NO_CALLBACK, AOBJ_STOPPED, AOBJ_WRAPPED, createSourceAObj,
  createSourceAObjCounters, interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-callback] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
function node(r: SourceFObjRuntime, bytes: number[] = [], fields: Partial<SourceFObjHeader> = {}) {
  const base = r.createData(Uint8Array.from(bytes));
  const id = r.createNode({next00: null, cursor04: base, base08: base, length0c: bytes.length,
    flags10: 4, byte11: 1, byte12: 1, track13: 7, format14: 0x80, format15: 0x80,
    half16: 0, offset18: 0, half1a: 4, frame1c: 2,
    value20: 10, value24: 18, value28: 30, value2c: 40, ...fields});
  return {id, base, n: r.getNode(id), offset: () => r.cursorOffset(base, r.getNode(id).cursor04!)};
}
function fixture(bytes: number[] = [], fields: Partial<SourceFObjHeader> = {}, transitions = 65536, nodes = 4096) {
  const owner = Symbol('explicit owner'), r = createSourceFObjScalarCallbackRuntime(owner, transitions, nodes);
  return {r, owner, ...node(r, bytes, fields)};
}
interface Call { owner: symbol | null; track: number; value: number; header: SourceFObjHeader }
function record(f: ReturnType<typeof fixture>, handler?: SourceFObjScalarHandler) {
  const calls: Call[] = [];
  const cb = f.r.createCallback((owner, track, value) => {
    calls.push({owner, track, value, header: {...f.n}});
    if (handler) return handler(owner, track, value);
  });
  return {cb, calls, run: (delta = 0) => f.r.interpretNode(f.id, delta, cb)};
}
function snapshot(r: SourceFObjRuntime, n: SourceFObjHeader) {
  return {...n, base08: n.base08 === null ? null : 'base', next00: n.next00 === null ? null : 'next',
    cursor04: n.base08 === null || n.cursor04 === null ? null : r.cursorOffset(n.base08, n.cursor04)};
}
export function runFObjCallbackSelfTest(): void {
  // Real dispatch is tested at each call site, including the state3-only80 gate.
  for (const phase of [3, 4, 6]) {
    for (const frame of [2, 4]) {
      if (phase === 4 && frame === 4) continue; // Equality consumes the wait first.
      const f = fixture([10, 0], {flags10: 0xa0 | phase, frame1c: frame});
      const c = record(f); c.run();
      check(c.calls.length === 1 && c.calls[0]!.value === (frame < 4 ? 10 : 18) &&
        c.calls[0]!.header.flags10 === (0xa0 | phase), 'constant phase value and preserved20/80');
      check(c.calls[0]!.owner === f.owner && c.calls[0]!.track === 7, 'explicit owner/track/scalar ABI');
    }
    const dirty = fixture([10, 0], {flags10: 0xa0 | phase, byte12: 2});
    const d = record(dirty); d.run();
    check(d.calls.length === 1 && d.calls[0]!.value === 14 && d.calls[0]!.header.value28 === 2 &&
      d.calls[0]!.header.flags10 === (0x80 | phase), 'dirty linear clear then subtract/divide in each phase');
    const cached = fixture([10, 0], {flags10: 0x80 | phase, byte12: 2, frame1c: 1.5,
      value20: -(2 ** -126), value28: 1 + 2 ** -23});
    const c = record(cached); c.run();
    check(c.calls.length === 1 && c.calls[0]!.value === 1.5 + 2 ** -23 &&
      c.calls[0]!.header.value28 === 1 + 2 ** -23, 'cached linear fused witness at all three sites');
    const key = fixture([10, 0], {flags10: 0xa0 | phase, byte12: 6});
    const k = record(key); k.run();
    check(k.calls.length === 1 && k.calls[0]!.value === 10 &&
      k.calls[0]!.header.flags10 === (0x20 | phase), 'key copies start then clears80 before every call');
    const skip = fixture([10, 0], {flags10: phase, byte12: 6}); const s = record(skip); s.run();
    check(s.calls.length === 0, 'key without80 skips in all phases');
  }
  for (const phase of [3, 6]) {
    const f = fixture([10, 0], {flags10: 0xa0 | phase, byte12: 2, half1a: 0});
    const c = record(f); c.run();
    check(c.calls.length === 1 && c.calls[0]!.value === 18 && c.calls[0]!.header.value20 === 18 &&
      Object.is(c.calls[0]!.header.value28, 0), 'zero duration linear stores +0 slope and endpoint before callback');
  }
  for (const op of [1, 2]) {
    const f = fixture([10, 0], {flags10: 3, byte12: op}); const c = record(f); c.run();
    check(c.calls.length === 0, 'state3 requires80 for ordinary interpolation too');
    for (const phase of [4, 6]) {
      const g = fixture([], {flags10: phase, byte12: op}); const d = record(g); d.run();
      check(d.calls.length === 1, 'state4/6 ordinary interpolation does not require80');
    }
  }
  {
    const f = fixture([], {flags10: 0x66, byte11: 6, byte12: 3}); const c = record(f); c.run();
    check(c.calls.length === 1 && c.calls[0]!.value === 18 && c.calls[0]!.header.byte12 === 6 &&
      c.calls[0]!.header.flags10 === 0x26, 'end promotes40 and opcode/start before callback selection and key clear');
    c.run(1); check(c.calls.length === 1 && f.n.flags10 === 0x26, 'key EOF is not dispatched again without80');
  }
  for (const op of [1, 2, 6]) {
    const f = fixture([], {flags10: 0x83, byte12: op}); const c = record(f); c.run();
    check(c.calls.length === (op === 6 ? 1 : 2) && f.n.flags10 === (op === 6 ? 3 : 0x83),
      'wait EOF invokes state3 then local6; ordinary opcodes retain80, key clears it');
    c.run(1);
    check(c.calls.length === (op === 6 ? 1 : 4) && (f.n.flags10 & 15) === 3,
      'repeated EOF retains stored3, ordinary callbacks repeat while key stays consumed');
  }
  {
    const f = fixture([], {flags10: 0x83, byte12: 6});
    const c = record(f, () => { if (c.calls.length === 1) f.n.flags10 |= 0x80; }); c.run();
    check(c.calls.length === 2 && f.n.flags10 === 3, 'handler-rearmed80 is read by later end callback');
  }
  {
    // Actual packed opcode6 stream, not a substituted per-node interpreter.
    const f = fixture([0x16, 10, 3, 20], {flags10: 1, frame1c: 0, byte11: 0, byte12: 0});
    const c = record(f); f.r.effects.requestAll(f.id, 0); c.run(1);
    check(c.calls.length === 1 && c.calls[0]!.value === 10 && f.n.flags10 === 0x65 &&
      f.n.frame1c === 1 && f.offset() === 4, 'key stream loader/wait first pending delivery');
    c.run(2);
    check(c.calls.length === 2 && c.calls[1]!.value === 20 && c.calls[1]!.header.frame1c === 3 &&
      f.n.flags10 === 0x23, 'end restores last wait and flushes final key before return');
    c.run(1); check(c.calls.length === 2 && f.n.frame1c === 4, 'completed key stream repeated EOF');
  }
  {
    const f = fixture([1, 10, 3, 1, 20, 4, 1, 30], {flags10: 1, frame1c: 0, byte11: 0, byte12: 0});
    const c = record(f); f.r.effects.requestAll(f.id, 0); c.run(1); c.run(7);
    check(c.calls.map(x => x.value).join(',') === '10,30' && c.calls[1]!.header.frame1c === 5,
      'actual constant stream uses state4 then last-consumed-wait restoration at end');
    const g = fixture([2, 10, 4, 2, 18], {flags10: 1, frame1c: 0, byte11: 0, byte12: 0});
    const d = record(g); g.r.effects.requestAll(g.id, 0); d.run(2);
    check(d.calls.length === 1 && d.calls[0]!.value === 14 && g.n.value28 === 2 && g.n.flags10 === 5,
      'actual linear stream integrates loader, wait, dirty slope and callback');
  }
  {
    // State3 callback updates every wait-reader input; no stale cursor or length.
    const f = fixture([99], {flags10: 0x83});
    const replacement = f.r.createData(Uint8Array.from([99, 7, 0]));
    const c = record(f, () => {
      f.n.base08 = replacement; f.n.cursor04 = f.r.cursorAt(replacement, 1); f.n.length0c = 3;
      f.n.half1a = 77; f.n.frame1c = 1; f.n.flags10 = 0x13; f.n.track13 = 19;
    }); c.run();
    check(c.calls.length === 1 && f.n.half1a === 7 && f.n.flags10 === 0x32 &&
      f.r.cursorOffset(replacement, f.n.cursor04!) === 3 && f.n.frame1c === 1,
      'state3 re-reads live base/cursor/length and writes wait after callback');
    const bad = fixture([9], {flags10: 0x83}); const b = record(bad, () => { bad.n.flags10 = 4; });
    rejects(b.run, 'wait state must be 3');
    check(bad.offset() === 0 && bad.n.flags10 === 4, 'state3 live assertion precedes consuming wait');
  }
  {
    const f = fixture([1], {flags10: 0x84, frame1c: 5, half1a: 4});
    const c = record(f, () => {
      if (c.calls.length === 1) { f.n.cursor04 = f.r.cursorAt(f.base, 1); f.n.half1a = 100; f.n.frame1c = 2; }
    }); c.run();
    check(c.calls.length === 2 && c.calls[0]!.header.frame1c === 1 && c.calls[1]!.header.frame1c === 6,
      'callback half1a mutation does not replace locally saved consumed wait');
  }
  {
    const f = fixture([], {flags10: 0x84}); const c = record(f, (_owner, _track, value) => {
      value = 999; // Local copied scalar has no header alias.
      f.n.flags10 = 0x72; f.n.frame1c = 17; f.n.track13 = 19;
      check(value === 999, 'handler scalar is an ordinary by-value number');
    }); c.run();
    check(f.n.flags10 === 0x75 && f.n.frame1c === 17 && f.n.value20 === 10 && c.calls[0]!.value === 10,
      'state4 reloads high flags and overwrites low state only after handler');
    const g = fixture([], {flags10: 6}); const d = record(g, () => { g.n.flags10 = 0x72; g.n.frame1c = 17; }); d.run();
    check(g.n.flags10 === 0x72 && g.n.frame1c === 17, 'state6 has no continuation stores after callback');
  }
  {
    const f = fixture([], {flags10: 0x84, track13: 1});
    const skipped = node(f.r, [], {track13: 2}), tail = node(f.r, [], {track13: 3}); f.n.next00 = skipped.id;
    const tracks: number[] = [];
    const cb = f.r.createCallback((_owner, track) => {
      tracks.push(track);
      if (track === 1) { f.n.next00 = tail.id; tail.n.track13 = 9; }
      if (track === 9) tail.n.next00 = null;
    }); f.r.effects.interpretAll(f.id, 0, cb);
    check(tracks.join(',') === '1,9' && skipped.n.flags10 === 4 && tail.n.flags10 === 5,
      'list follows live next after handler, loads track at actual later call');
    const stop = fixture([], {flags10: 0x84, byte12: 6, track13: 1});
    const bypassed = node(stop.r, [], {flags10: 5, track13: 2}), last = node(stop.r, [], {flags10: 0x83, byte12: 1});
    stop.n.next00 = bypassed.id;
    const s = record(stop, () => { stop.n.flags10 = 0x7f; stop.n.byte12 = 1; stop.n.next00 = last.id; });
    stop.r.effects.stopAll(stop.id, 0, s.cb);
    check(s.calls.length === 1 && stop.n.flags10 === 0x70 && last.n.flags10 === 0x80 &&
      last.n.frame1c === 2 && bypassed.n.flags10 === 5,
      'StopAll chooses initial opcode6, reloads next and clears low flags even on skipped nodes');
  }
  for (const phase of [3, 4, 6]) {
    for (const kind of ['throw', 'return', 'async', 'invalid', 'frozen'] as const) {
      const f = fixture([1], {flags10: 0x80 | phase, byte12: 6});
      const c = record(f, () => {
        f.n.value24 = 42;
        if (kind === 'throw') throw Error('synthetic handler failure');
        if (kind === 'return') return 7 as unknown as void;
        if (kind === 'async') return Promise.resolve() as unknown as void;
        if (kind === 'invalid') f.n.frame1c = Infinity;
        if (kind === 'frozen') Object.freeze(f.n);
      });
      rejects(c.run, {throw: 'synthetic handler failure', return: 'synchronously', async: 'synchronously',
        invalid: 'finite source float32', frozen: 'non-writable'}[kind]);
      check(c.calls.length === 1 && f.n.flags10 === phase && f.n.value24 === 42 && f.offset() === 0,
        'handler failure preserves key clear and handler writes, skips phase continuation');
    }
  }
  for (const entry of ['direct', 'list', 'stop'] as const) {
    for (const nested of ['direct', 'list', 'stop', 'request', 'loadData', 'loadWait'] as const) {
      const f = fixture([], {flags10: 0x84, byte12: 6}); let first = true;
      const cb = f.r.createCallback(() => {
        f.n.value24 = 42;
        if (!first) return; first = false;
        if (nested === 'direct') f.r.interpretNode(f.id, 1, cb);
        if (nested === 'list') f.r.effects.interpretAll(f.id, 1, cb);
        if (nested === 'stop') f.r.effects.stopAll(f.id, 1, cb);
        if (nested === 'request') f.r.effects.requestAll(f.id, 1);
        if (nested === 'loadData') f.r.loadData(f.n);
        if (nested === 'loadWait') f.r.loadWait(f.n);
      });
      const run = () => entry === 'direct' ? f.r.interpretNode(f.id, 0, cb) : entry === 'list'
        ? f.r.effects.interpretAll(f.id, 0, cb) : f.r.effects.stopAll(f.id, 0, cb);
      rejects(run, 'same-runtime reentry');
      check(f.n.flags10 === 4 && f.n.value24 === 42 && f.n.frame1c === 2,
        'reentry refuses before nested writes and retains outer prefix, including StopAll clear not reached');
      f.n.flags10 = 0x84; run();
      check(f.n.flags10 === (entry === 'stop' ? 0 : 5), 'shared guard releases after exception');
    }
  }
  {
    const f = fixture(); const other = fixture(); const foreign = other.r.createCallback(() => {});
    for (const entry of ['direct', 'list', 'stop'] as const) {
      const run = () => entry === 'direct' ? f.r.interpretNode(f.id, 1, foreign) : entry === 'list'
        ? f.r.effects.interpretAll(f.id, 1, foreign) : f.r.effects.stopAll(f.id, 1, foreign);
      rejects(run, 'non-owned callback'); check(f.n.frame1c === 2 && f.n.flags10 === 4, 'callback preflight precedes writes');
    }
    rejects(() => f.r.createCallback(null as unknown as SourceFObjScalarHandler), 'handler required');
    rejects(() => createSourceFObjScalarCallbackRuntime(undefined as unknown as symbol), 'explicit owner');
    const r = createSourceFObjScalarCallbackRuntime(null), n = node(r); let seen = false;
    r.interpretNode(n.id, 0, r.createCallback(owner => { seen = owner === null; }));
    check(seen, 'explicit null owner supported without guessing an AObj owner');
    f.r.interpretNode(null, NaN, foreign); f.r.effects.interpretAll(null, NaN, foreign);
    f.r.effects.stopAll(null, NaN, foreign); f.r.effects.requestAll(null, NaN);
    f.n.flags10 = 0; f.r.interpretNode(f.id, NaN, f.r.createCallback(() => { throw Error('state0'); }));
    check(f.n.frame1c === 2, 'null identities and direct state0 preserve their early-return contracts');
  }
  for (const phase of [3, 4, 6]) {
    for (const op of [0, 3, 4, 5, 7, 15, 255]) {
      const f = fixture([1], {flags10: 0xa0 | phase, byte12: op}); const c = record(f);
      rejects(() => c.run(1), `unsupported eligible opcode ${op}`);
      check(c.calls.length === 0 && f.n.frame1c === 3 && f.n.flags10 === (0xa0 | phase) && f.offset() === 0,
        'unsupported eligible interpolation refuses with completed clock but no callback or invented zero');
      const skip = fixture([10, 0], {flags10: 3, byte12: op}); const s = record(skip); s.run();
      check(s.calls.length === 0, 'unsupported but ineligible state3 opcode is not prematurely rejected');
    }
  }
  {
    const max = (2 - 2 ** -23) * 2 ** 127;
    for (const phase of [3, 4, 6]) {
      const f = fixture([], {flags10: 0xa0 | phase, byte12: 2, value20: -max, value24: max});
      const c = record(f); rejects(c.run, 'overflow');
      check(c.calls.length === 0 && f.n.flags10 === (0x80 | phase) && f.n.value28 === 30,
        'linear arithmetic refusal retains dirty clear but no handler or state continuation');
    }
    const f = fixture([], {flags10: 5}, 1); const c = record(f); rejects(c.run, 'transition budget');
    check(f.n.flags10 === 4 && c.calls.length === 0, 'transition budget retains completed state5 store');
    const g = fixture([], {flags10: 0x83}, 1); const d = record(g); rejects(d.run, 'transition budget');
    check(d.calls.length === 1 && g.n.flags10 === 0x83, 'budget retains completed state3 callback before next phase refusal');
    const h = fixture([], {}, 65536, 1), tail = node(h.r); h.n.next00 = tail.id;
    const e = record(h); rejects(() => h.r.effects.interpretAll(h.id, 0, e.cb), 'node budget');
    check(e.calls.length === 1 && h.n.flags10 === 5 && tail.n.flags10 === 4, 'node budget preserves earlier handler/phase writes');
    h.n.next00 = h.id; rejects(() => h.r.effects.interpretAll(h.id, 0, e.cb), 'cycle');
    rejects(() => createSourceFObjScalarCallbackRuntime(null, 0), 'transition budget');
    rejects(() => createSourceFObjScalarCallbackRuntime(null, 1, 0), 'maxNodes');
  }
  {
    // New null-callback calls and the explicit null-only runtime share all writes.
    for (const bytes of [[], [1, 10, 3, 1, 20], [0x16, 10, 3, 20], [128], [0x25, 1, 2, 3]]) {
      for (const state of [0, 1, 2, 3, 4, 5, 6, 7]) {
        const fields = {flags10: 0xe0 | state, byte11: 6, byte12: 2, frame1c: 1};
        const scalar = fixture(bytes, fields, 12), r = createSourceFObjNullCallbackRuntime(12), nil = node(r, bytes, fields);
        let a = '', b = '';
        try { scalar.r.interpretNode(scalar.id, 1, null); } catch (error) { a = String(error); }
        try { r.interpretNode(nil.id, 1, null); } catch (error) { b = String(error); }
        const left = snapshot(scalar.r, scalar.n), right = snapshot(r, nil.n);
        check(a === b && (Object.keys(left) as (keyof typeof left)[]).every(key => Object.is(left[key], right[key])),
          'null callback equivalence includes errors and all partial writes');
      }
    }
  }
  {
    const f = fixture([], {flags10: 0x86, byte12: 6}); const c = record(f);
    const a = createSourceAObj({flags: AOBJ_NO_CALLBACK, frame: 0, rewind: 0, end: 2, rate: 1, fobjs: f.id});
    const counts = createSourceAObjCounters();
    interpretSourceAObj(a, c.cb, f.r.effects, counts);
    check(c.calls.length === 0 && f.n.flags10 === 0x86 && counts.running === 1, 'AObj NO_CALLBACK suppresses ordinary path');
    interpretSourceAObj(a, c.cb, f.r.effects, counts);
    check(c.calls.length === 1 && c.calls[0]!.header.frame1c === 5 && f.n.flags10 === 0 &&
      (a.flags & AOBJ_STOPPED) !== 0 && counts.stopped === 1,
      'AObj NO_CALLBACK does not suppress end-stop key callback or postcallback state clear');
    const g = fixture([], {flags10: 0x86, byte12: 6}); const d = record(g);
    const wrap = createSourceAObj({flags: AOBJ_LOOP | AOBJ_NO_CALLBACK, frame: 9, rewind: 2, end: 10, rate: 1, fobjs: g.id});
    interpretSourceAObj(wrap, d.cb, g.r.effects, createSourceAObjCounters());
    check(d.calls.length === 1 && wrap.frame === 2 && (wrap.flags & AOBJ_WRAPPED) !== 0 &&
      g.n.frame1c === 2 && g.n.flags10 === 1, 'NO_CALLBACK wrap stop dispatches key before request/reset and suppressed ordinary path');
  }
  {
    const f = fixture([], {flags10: 0x86, byte12: 6});
    const next = node(f.r, [1, 10, 9, 1, 20], {flags10: 0, frame1c: 0});
    const a = createSourceAObj({flags: AOBJ_LOOP | AOBJ_NO_CALLBACK, frame: 9, rewind: 2, end: 10, rate: 1, fobjs: f.id});
    const c = record(f, () => { a.frame = 13; a.rewind = 3; a.end = 7; a.fobjs = next.id; a.rate = 2; });
    const counts = createSourceAObjCounters(); interpretSourceAObj(a, c.cb, f.r.effects, counts);
    check(c.calls.length === 1 && a.frame === 5 && next.n.frame1c === 5 && next.n.flags10 === 0x25 &&
      f.n.flags10 === 0 && counts.running === 1, 'AObj wrap reloads callback-mutated clocks and list before request/ordinary interpret');
    const stop = fixture([], {flags10: 0x86, byte12: 6});
    const b = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 10, rate: 1, fobjs: stop.id});
    const counts2 = createSourceAObjCounters();
    const d = record(stop, () => { b.flags = AOBJ_STOPPED; }); interpretSourceAObj(b, d.cb, stop.r.effects, counts2);
    check(counts2.stopped === 1 && counts2.running === 0, 'final AObj accounting observes callback flag mutation');
    const reenter = fixture([], {flags10: 0x86, byte12: 6});
    const x = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 10, rate: 1, fobjs: reenter.id});
    const e = record(reenter, () => { requestSourceAObj(x, 5, reenter.r.effects); });
    rejects(() => interpretSourceAObj(x, e.cb, reenter.r.effects, createSourceAObjCounters()), 'same-AObj reentry');
    check(x.frame === 1 && reenter.n.flags10 === 6, 'AObj reentry retains preceding clocks and key clear');
  }
  console.log('[fobj-callback] PASS: bounded scalar1/2/6 callbacks through actual loader/timing and AObj effects; synthetic coverage, no full FObj or live integration');
}
