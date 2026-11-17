import {
  AOBJ_LOOP as LOOP, AOBJ_NO_CALLBACK as SILENT, AOBJ_REQUEST as REQUEST,
  AOBJ_STOPPED as STOPPED, AOBJ_WRAPPED as WRAPPED,
  createSourceAObj, createSourceAObjCounters, interpretSourceAObj, requestSourceAObj, setSourceAObjRate,
  setSourceAObjFlags, clearSourceAObjFlags,
  type SourceAObj, type SourceAObjEffects,
} from './aobj-clock.js';
import {createSourceFObjScalarCallbackRuntime} from './fobj-callback.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[aobj-clock] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = '';
  try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected rejection containing ${text}, got ${diagnostic}`);
}
const list1 = Symbol('list1'), list2 = Symbol('list2'), list3 = Symbol('list3');
const callback = Symbol('source callback');
type Event = {kind: string; list: symbol | null; value: number; callback?: symbol | null};
function fixture(initial: Partial<SourceAObj> = {}) {
  const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 10, rate: 1, fobjs: list1, ...initial});
  const counts = createSourceAObjCounters();
  const events: Event[] = [];
  // Explicit test-double effects, not production FObj implementations.
  const effects: SourceAObjEffects = {
    requestAll(list, value) { events.push({kind: 'request', list, value}); },
    stopAll(list, value, cb) { events.push({kind: 'stop', list, value, callback: cb}); },
    interpretAll(list, value, cb) { events.push({kind: 'interpret', list, value, callback: cb}); },
  };
  return {a, counts, events, effects, tick: () => interpretSourceAObj(a, callback, effects, counts)};
}
export function runAObjClockSelfTest(): void {
  for (const [change, set] of [[setSourceAObjFlags, true], [clearSourceAObjFlags, false]] as const) {
    const poison = new Proxy({}, {get() {throw Error('mask must not be coerced');}}) as number;
    for (const mask of [NaN, Infinity, -1, 0x100000000, .5, poison]) {
      check(change(null, mask) === undefined, 'null flags target bypasses mask validation');
    }
    for (const before of [0, 0xffffffff, 0x81234567, STOPPED | REQUEST | WRAPPED]) {
      for (const mask of [0, 0xffffffff, LOOP, SILENT, LOOP | SILENT, STOPPED | REQUEST | WRAPPED | 3]) {
        const f = fixture({flags: before}), snapshot = {...f.a};
        const expected = (set ? before | (mask & 0x30000000) : before & ~(mask & 0x30000000)) >>> 0;
        check(change(f.a, mask) === undefined && f.a.flags === expected, 'source flag helper masks changes to 0x30000000 and preserves uint32 bits');
        check((['frame', 'rewind', 'end', 'rate', 'fobjs'] as const).every(key => Object.is(f.a[key], snapshot[key])) &&
          f.events.length === 0 && f.counts.running === 0 && f.counts.stopped === 0,
        'flag helper changes no clocks/list/effects/counters');
      }
    }
    const f = fixture({flags: 0x81234567}), before = f.a.flags;
    for (const mask of [NaN, Infinity, -1, 0x100000000, .5, poison]) {
      rejects(() => change(f.a, mask), 'expected uint32'); check(f.a.flags === before, 'invalid masks fail before flags store');
    }
    for (const oldFlags of [NaN, Infinity, -1, 0x100000000, .5]) {
      f.a.flags = oldFlags; rejects(() => change(f.a, 0), 'expected uint32');
      check(Object.is(f.a.flags, oldFlags), 'old consumed flags must be uint32 even with zero mask');
    }
    const foreign = {...fixture().a}; rejects(() => change(foreign, LOOP), 'factory-created');
    const proxy = new Proxy(f.a, {
      get() {throw Error('foreign flags target must not be read');},
      getOwnPropertyDescriptor() {throw Error('foreign flags target must not be inspected');},
    });
    rejects(() => change(proxy, LOOP), 'factory-created');
    rejects(() => change(Object.create(f.a) as SourceAObj, LOOP), 'factory-created');
    for (const freeze of [false, true]) {
      const a = fixture().a;
      if (freeze) Object.freeze(a); else Object.defineProperty(a, 'flags', {writable: false});
      rejects(() => change(a, 0), 'non-writable flags'); check(a.flags === 0, 'readonly flags refused even for zero selected mask');
    }
    const narrow = fixture({flags: 0x81234567});
    narrow.a.frame = NaN; narrow.a.rewind = Infinity; narrow.a.end = .1; narrow.a.rate = NaN;
    narrow.a.fobjs = poison as unknown as symbol;
    for (const key of ['frame', 'rewind', 'end', 'rate', 'fobjs']) Object.defineProperty(narrow.a, key, {writable: false});
    change(narrow.a, 0xffffffff);
    check(narrow.a.flags === (set ? 0xb1234567 : 0x81234567), 'flag-only helper ignores every unrelated invalid/frozen AObj field');
    rejects(narrow.tick, 'non-writable'); rejects(() => requestSourceAObj(narrow.a, 0, narrow.effects), 'non-writable');
  }
  {
    // Actual packed interpolation invokes both helpers while AObj interpretation
    // is active, without weakening request/interpret same-AObj reentry guards.
    const owner = Symbol('flag callback owner'), r = createSourceFObjScalarCallbackRuntime(owner);
    const base = r.createData(Uint8Array.from([2, 3, 4, 2, 11]));
    const node = r.createNode({next00: null, cursor04: base, base08: base, length0c: 5,
      flags10: 1, byte11: 0, byte12: 0, track13: 7, format14: 0x80, format15: 0x80,
      half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
    const a = createSourceAObj({flags: 0x80, frame: 0, rewind: 0, end: 9, rate: 1, fobjs: node});
    const counts = createSourceAObjCounters(); let calls = 0;
    const callback = r.createCallback((target, track, value) => {
      check(target === owner && track === 7 && value === 7, 'actual flag callback interpolation'); calls++;
      setSourceAObjFlags(a, 0xffffffff); check(a.flags === (LOOP | SILENT | 0x80), 'active callback sets selected bits only');
      clearSourceAObjFlags(a, 0xffffffff); check(a.flags === 0x80, 'active callback clears selected bits only');
    });
    requestSourceAObj(a, 2, r.effects); interpretSourceAObj(a, callback, r.effects, counts);
    check(calls === 1 && a.flags === 0x80 && a.frame === 2 && counts.running === 1 && counts.stopped === 0,
      'source flag helpers remain available during real interpretation');
  }
  {
    const f = fixture({flags: (STOPPED | WRAPPED | 0x80000001) >>> 0, rate: -0});
    const request = 1 + 2 ** -25;
    requestSourceAObj(f.a, request, f.effects);
    check(f.a.frame === 1 && f.events[0]!.value === request && f.events[0]!.value !== f.a.frame,
      'request stores float32 but forwards original double (premature-rounding negative control)');
    check(f.a.flags === ((WRAPPED | REQUEST | 0x80000001) >>> 0), 'request preserves unrelated uint32 bits');
    f.tick();
    check(f.a.frame === 1 && f.a.flags === 0x80000001 && Object.is(f.events[1]!.value, 0),
      'request suppresses one advance and clears wrapped, with positive zero');
    f.a.rate = 2; f.tick();
    check(f.a.frame === 3 && f.events[2]!.value === 2 && f.counts.running === 2, 'next tick advances');
  }
  {
    const f = fixture({flags: STOPPED | REQUEST | WRAPPED});
    const before = JSON.stringify(f.a);
    f.tick(); interpretSourceAObj(null, callback, f.effects, f.counts);
    requestSourceAObj(null, Infinity, f.effects);
    check(JSON.stringify(f.a) === before && !f.events.length && !f.counts.running && !f.counts.stopped,
      'stopped/null are unchanged and uncounted');
  }
  {
    const f = fixture();
    requestSourceAObj(f.a, -0, f.effects);
    check(Object.is(f.a.frame, -0) && Object.is(f.events[0]!.value, -0), 'request preserves signed zero');
    f.tick();
    check(Object.is(f.a.frame, -0) && Object.is(f.events[1]!.value, 0), 'suppression keeps stored negative zero but passes positive-zero delta');
    const minimum = 2 ** -149;
    requestSourceAObj(f.a, minimum, f.effects);
    check(f.a.frame === minimum && f.events.at(-1)!.value === minimum, 'finite binary32 subnormal request under admitted IEEE environment');
  }
  for (const [frame, rate, rewind, end, expected] of [
    [9, 1, 0, 10, 0], [9, 26, 2, 10, 3], [10, 0, 10, 10, 10],
    [11, -1, 12, 10, 10], [3, -2, 0, 10, 1], [3, 0, 0, 10, 3],
  ] as const) {
    const f = fixture({flags: LOOP | WRAPPED, frame, rate, rewind, end}); f.tick();
    const wraps = end! <= frame! + rate!;
    check(f.a.frame === expected && !!(f.a.flags & WRAPPED) === wraps, 'loop/clamp/negative/zero-rate clock');
    const order = wraps && rewind! < end! ? 'stop,request,interpret' : 'interpret';
    check(f.events.map(e => e.kind).join() === order, 'strict rewind/end chooses stop/request versus clamp');
    check(Object.is(f.events.at(-1)!.value, wraps ? 0 : rate) && f.counts.running === 1, 'loop delta/accounting');
  }
  {
    const f = fixture({frame: 9, rate: 4, flags: WRAPPED | SILENT}); f.tick();
    check(f.a.frame === 13 && f.a.flags === (STOPPED | SILENT), 'nonloop overshoot not clamped');
    check(f.events.map(e => e.kind).join() === 'interpret,stop' && f.events[0]!.callback === null &&
      f.events[1]!.callback === callback && f.events[1]!.value === 4 && f.counts.stopped === 1,
      'suppression affects interpretation only, not completion stop');
  }
  {
    const f = fixture({flags: LOOP | SILENT, frame: 9}); f.tick();
    check(f.events[0]!.callback === callback && f.events[2]!.callback === null,
      'suppression does not suppress wrap-stop callback');
  }
  {
    const f = fixture({frame: 16777216, end: 33554432}); f.tick();
    check(f.a.frame === 16777216, 'advance fadds rounds before comparison/effects');
    const w = fixture({flags: LOOP | REQUEST, frame: 16777216, rewind: -1, end: 10}); w.tick();
    const expected = Math.fround(-1 + Math.fround(16777216 - -1) % Math.fround(10 - -1));
    const naive = Math.fround(-1 + (16777216 - -1) % (10 - -1));
    check(w.a.frame === expected && expected !== naive, 'float32 subtraction before fmod negative control');
    const d = fixture({flags: LOOP | REQUEST, frame: 16777216, rewind: -1, end: 16777216}); d.tick();
    check(d.a.frame === -1, 'denominator also uses fsubs');
    // A remainder of two finite binary32 operands is itself binary32 representable.
    // Thus no fabricated witness for rounding that remainder early: retain audited
    // double fadd/frsp sequence in module, without claiming a distinguishing test.
  }
  {
    const f = fixture({flags: LOOP, frame: 9});
    const stop = f.effects.stopAll;
    f.effects.stopAll = (list, delta, cb) => {
      stop(list, delta, cb);
      f.a.frame = 29; f.a.rewind = 3; f.a.end = 11; f.a.fobjs = list2;
      f.a.flags = (SILENT | 0x80000001) >>> 0;
    };
    const request = f.effects.requestAll;
    f.effects.requestAll = (list, frame) => {
      request(list, frame); f.a.flags = (f.a.flags | LOOP) >>> 0; f.a.fobjs = list3;
    };
    f.tick();
    check(f.a.frame === 5 && f.events[1]!.value === 5 && f.events[1]!.list === list2 &&
      f.events[2]!.list === list3 && f.events[2]!.callback === null,
      'wrap reloads callback-mutated operands, flags and each list identity');
    check(f.a.flags === ((SILENT | LOOP | WRAPPED | 0x80000001) >>> 0), 'reload flags before wrapped');
    check(f.a.frame !== 0, 'precomputed/stale-state wrap would incorrectly produce frame zero');
  }
  {
    const f = fixture({flags: LOOP, frame: 1});
    const interpret = f.effects.interpretAll;
    f.effects.interpretAll = (list, delta, cb) => {
      interpret(list, delta, cb);
      f.a.flags = SILENT; f.a.frame = 20; f.a.end = 19; f.a.rate = -3; f.a.fobjs = list2;
    };
    const stop = f.effects.stopAll;
    f.effects.stopAll = (list, delta, cb) => {
      stop(list, delta, cb);
      f.a.flags = (LOOP | REQUEST | 0x80000001) >>> 0; f.a.frame = -4; f.a.end = 30;
    };
    f.tick();
    check(f.events.map(e => e.kind).join() === 'interpret,stop' && f.events[1]!.list === list2 &&
      f.events[1]!.value === -3 && f.events[1]!.callback === callback,
      'post-interpret decision reloads flags/end/frame/rate/list, never precomputed');
    check(f.a.frame === -4 && f.a.flags === ((LOOP | REQUEST | STOPPED | 0x80000001) >>> 0) &&
      f.counts.stopped === 1, 'completion reloads flags after callback, sets stopped regardless of new loop');
  }
  {
    // Re-evaluate both live comparison operands, even when loop stays clear.
    for (const change of ['frame', 'end'] as const) {
      const f = fixture({frame: 9});
      f.effects.interpretAll = () => { if (change === 'frame') f.a.frame = 0; else f.a.end = 20; };
      f.tick();
      check(f.counts.running === 1 && !f.events.length, `live ${change} cancels completion`);
    }
    const f = fixture({flags: LOOP, frame: 9});
    f.effects.stopAll = () => { f.a.frame = -7; f.a.rewind = 3; f.a.end = -1; };
    f.tick();
    check(f.a.frame === 1, 'negative post-callback fmod denominator/numerator use truncating remainder');
  }
  {
    const f = fixture({frame: 9});
    f.effects.interpretAll = () => { f.a.end = 20; f.a.flags = STOPPED; };
    f.tick();
    check(f.counts.stopped === 1 && f.events.length === 0, 'final stopped flag counts even without end stop');
    const g = fixture({frame: 9});
    g.effects.interpretAll = () => { g.a.flags = LOOP; };
    g.counts.running = 0xffffffff; g.tick();
    check(g.counts.running === 0 && !g.events.length, 'new loop cancels completion; uint32 counter wraps');
    const h = fixture({frame: 9}); h.counts.stopped = 0xffffffff; h.tick();
    check(h.counts.stopped === 0, 'stopped uint32 counter wraps');
    const changed = fixture();
    changed.effects.interpretAll = () => { changed.counts.running = 40; };
    changed.tick();
    check(changed.counts.running === 41, 'final accounting reads callback-mutated counter');
  }
  {
    const f = fixture();
    rejects(() => requestSourceAObj(f.a, Infinity, f.effects), 'finite double');
    rejects(() => requestSourceAObj(f.a, 1e40, f.effects), 'overflow');
    check(f.a.frame === 0 && f.a.flags === 0 && !f.events.length, 'invalid request rejected before writes');
    rejects(() => createSourceAObj({...f.a, rate: .1}), 'finite source float32');
    rejects(() => createSourceAObj({...f.a, flags: -1}), 'uint32');
    rejects(() => interpretSourceAObj({...f.a}, callback, f.effects, f.counts), 'factory-created');
    rejects(() => requestSourceAObj(f.a, 2, {} as SourceAObjEffects), 'effects are required');
    const o = fixture({frame: Math.fround(3e38), rate: Math.fround(3e38)});
    rejects(o.tick, 'advance'); check(o.a.frame === Math.fround(3e38) && !o.events.length, 'advance overflow before store');
  }
  {
    const f = fixture({flags: LOOP, frame: 9});
    let calls = 0;
    f.effects.stopAll = () => { calls++; f.a.rewind = f.a.end; };
    rejects(f.tick, 'zero denominator');
    check(calls === 1 && f.a.frame === 10 && f.a.rewind === 10 && f.counts.running === 0,
      'invalid post-stop fmod preserves already executed effect, no rollback/accounting');
    const g = fixture({flags: LOOP, frame: 9});
    g.effects.stopAll = () => { g.a.frame = Infinity; };
    rejects(g.tick, 'after wrap stopAll.frame');
    check(g.a.frame === Infinity && !g.events.length, 'invalid callback state fails before later effects');
    const h = fixture(); h.effects.interpretAll = () => { h.a.frame = 7; throw Error('unsupported FObj'); };
    rejects(h.tick, 'unsupported FObj');
    check(h.a.frame === 7 && h.counts.running === 0, 'thrown effect preserves partial writes, no counter increment');
    const j = fixture();
    j.effects.interpretAll = (() => Promise.resolve()) as unknown as SourceAObjEffects['interpretAll'];
    rejects(j.tick, 'synchronously');
    const k = fixture(); k.effects.interpretAll = () => requestSourceAObj(k.a, 4, k.effects);
    rejects(k.tick, 'reentry');
    const overflow = fixture({flags: LOOP, frame: 9});
    overflow.effects.stopAll = () => { overflow.a.frame = Math.fround(3e38); overflow.a.rewind = -Math.fround(3e38); };
    rejects(overflow.tick, 'wrap frame-rewind');
    check(overflow.a.frame === Math.fround(3e38), 'subtraction overflow retains prior callback write');
    const denominator = fixture({flags: LOOP, frame: 9});
    denominator.effects.stopAll = () => {
      denominator.a.frame = 0; denominator.a.rewind = -Math.fround(3e38); denominator.a.end = Math.fround(3e38);
    };
    rejects(denominator.tick, 'wrap end-rewind');
    check(denominator.a.frame === 0 && !denominator.events.length && denominator.counts.running === 0,
      'denominator overflow fails before request/interpret and retains prior callback state');
    const request = fixture();
    request.effects.requestAll = () => { throw Error('unsupported request'); };
    rejects(() => requestSourceAObj(request.a, 4, request.effects), 'unsupported request');
    check(request.a.frame === 4 && request.a.flags === REQUEST, 'request failure does not roll back stored clock/flags');
    const m = fixture(); m.effects.interpretAll = () => { Object.freeze(m.a); };
    rejects(m.tick, 'non-writable');
  }
  {
    const poison = new Proxy({}, {get() { throw Error('rate must not be inspected or coerced'); }});
    for (const rate of [NaN, Infinity, -Infinity, Number.MAX_VALUE, 1 + 2 ** -25, poison as number]) {
      check(setSourceAObjRate(null, rate) === undefined, 'null rate target bypasses all argument validation');
    }
    const f = fixture({flags: STOPPED | REQUEST | WRAPPED, frame: -0, rewind: -2, end: 9});
    const before = {...f.a}, exact = 1 + 2 ** -23;
    check(setSourceAObjRate(f.a, exact) === undefined && f.a.rate === exact,
      'owned rate setter stores an already-finite source float32 and returns undefined');
    check((['flags', 'frame', 'rewind', 'end', 'fobjs'] as const).every(key => Object.is(f.a[key], before[key])) &&
      f.events.length === 0 && f.counts.running === 0 && f.counts.stopped === 0,
      'rate setter performs only the rate store, without flags, clocks, effects or accounting');
    const maximum = (2 - 2 ** -23) * 2 ** 127, minimum = 2 ** -149;
    for (const rate of [0, -2, maximum, -maximum, minimum, -minimum, 2 ** -126, -(2 ** -126), -0]) {
      setSourceAObjRate(f.a, rate);
      check(Object.is(f.a.rate, rate), 'rate setter preserves exact float32 extremes, subnormals and signed zero');
    }
    for (const rate of [NaN, Infinity, -Infinity, poison as number]) {
      rejects(() => setSourceAObjRate(f.a, rate), 'finite source float32');
      check(Object.is(f.a.rate, -0), 'invalid double rate is rejected before any write or coercion');
    }
    for (const rate of [1 + 2 ** -25, .1, 2 ** -150, -(2 ** -150), Number.MIN_VALUE, -Number.MIN_VALUE,
      2 ** 128, -(2 ** 128), Number.MAX_VALUE, -Number.MAX_VALUE]) {
      rejects(() => setSourceAObjRate(f.a, rate), 'finite source float32');
      check(Object.is(f.a.rate, -0), 'widened/underflow/overflow double rate is rejected rather than rounded');
    }
  }
  {
    const f = fixture();
    const foreign = {...f.a};
    rejects(() => setSourceAObjRate(foreign, 4), 'factory-created');
    check(foreign.rate === 1 && f.a.rate === 1, 'lookalike rate target cannot mutate owned state');
    const poison = new Proxy(f.a, {
      get() { throw Error('foreign target must not be read'); },
      getOwnPropertyDescriptor() { throw Error('foreign target must not be inspected'); },
    });
    rejects(() => setSourceAObjRate(poison, 4), 'factory-created');
    rejects(() => setSourceAObjRate(Object.create(f.a) as SourceAObj, 4), 'factory-created');
    for (const freezeAll of [false, true]) {
      const frozen = fixture().a;
      if (freezeAll) Object.freeze(frozen);
      else Object.defineProperty(frozen, 'rate', {writable: false});
      rejects(() => setSourceAObjRate(frozen, 4), 'non-writable rate');
      check(frozen.rate === 1, 'non-writable owned rate is rejected without mutation');
    }
  }
  {
    const f = fixture();
    f.a.flags = -1; f.a.frame = NaN; f.a.rewind = Infinity; f.a.end = .1;
    f.a.fobjs = new Proxy({}, {get() { throw Error('unrelated FObj state must not be read'); }}) as unknown as symbol;
    for (const key of ['flags', 'frame', 'rewind', 'end', 'fobjs']) {
      Object.defineProperty(f.a, key, {writable: false});
    }
    const before = {...f.a};
    for (const oldRate of [NaN, Infinity, -Infinity, .1]) {
      f.a.rate = oldRate;
      setSourceAObjRate(f.a, 3);
      check(f.a.rate === 3 && (['flags', 'frame', 'rewind', 'end', 'fobjs'] as const)
        .every(key => Object.is(f.a[key], before[key])),
      'rate-only store overwrites invalid old rate and ignores unrelated invalid/frozen fields');
    }
    rejects(f.tick, 'non-writable');
    rejects(() => requestSourceAObj(f.a, 0, f.effects), 'non-writable');
    check(f.a.rate === 3 && !f.events.length, 'narrow setter does not weaken interpreter/request validation');
  }
  {
    // Actual packed opcode6 stream and real FObj effects, not an injected interpreter.
    const owner = Symbol('rate callback owner'), r = createSourceFObjScalarCallbackRuntime(owner);
    const bytes = Uint8Array.from([0x16, 3, 3, 5]), base = r.createData(bytes);
    const id = r.createNode({next00: null, cursor04: base, base08: base, length0c: bytes.length,
      flags10: 1, byte11: 0, byte12: 0, track13: 7, format14: 0x80, format15: 0x80,
      half16: 0, offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0});
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 0, rate: 1, fobjs: id});
    const counts = createSourceAObjCounters(), values: number[] = [], oldRates: number[] = [];
    const cb = r.createCallback((callbackOwner, track, value) => {
      check(callbackOwner === owner && track === 7, 'real FObj callback preserves owner/track');
      values.push(value); oldRates.push(a.rate);
      setSourceAObjRate(a, value);
    });
    requestSourceAObj(a, 0, r.effects);
    interpretSourceAObj(a, cb, r.effects, counts);
    check(values.join() === '3,5' && oldRates.join() === '1,3' && a.rate === 5 && a.frame === 0,
      'rate setter is allowed in ordinary and end-stop callbacks while the AObj is busy');
    check(r.getNode(id).frame1c === 3 && (r.getNode(id).flags10 & 15) === 0 && a.flags === STOPPED &&
      counts.stopped === 1 && counts.running === 0,
      'same interpreter reloads rate3 for real stopAll, reaching the final key instead of using stale rate1');
  }
  console.log('[aobj-clock] PASS: offline request/clock control, ordered mutable effects, rounding, counters and rejection boundaries (not retail replay)');
}
