import {
  AOBJ_LOOP as LOOP, AOBJ_NO_CALLBACK as SILENT, AOBJ_REQUEST as REQUEST,
  AOBJ_STOPPED as STOPPED, AOBJ_WRAPPED as WRAPPED,
  createSourceAObj, createSourceAObjCounters, interpretSourceAObj, requestSourceAObj,
  type SourceAObj, type SourceAObjEffects,
} from './aobj-clock.js';
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
  console.log('[aobj-clock] PASS: offline request/clock control, ordered mutable effects, rounding, counters and rejection boundaries (not retail replay)');
}
