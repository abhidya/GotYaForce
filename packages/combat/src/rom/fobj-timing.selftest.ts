import {createSourceFObjNullCallbackRuntime} from './fobj-timing.js';
import {AOBJ_LOOP, AOBJ_NO_CALLBACK, AOBJ_STOPPED, createSourceAObj, createSourceAObjCounters,
  interpretSourceAObj} from './aobj-clock.js';
import type {SourceFObjHeader} from './fobj-list.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-timing] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
function fixture(bytes: number[] = [], fields: Partial<SourceFObjHeader> = {}, budget = 65536) {
  const r = createSourceFObjNullCallbackRuntime(budget), base = r.createData(Uint8Array.from(bytes));
  const id = r.createNode({next00: null, cursor04: base, base08: base, length0c: bytes.length,
    flags10: 1, byte11: 0, byte12: 0, track13: 7, format14: 0x80, format15: 0x80,
    half16: 0, offset18: 0, half1a: 0, frame1c: 0,
    value20: 10, value24: 20, value28: 30, value2c: 40, ...fields});
  const n = r.getNode(id);
  return {r, n, id, base, run: (delta = 0) => r.interpretNode(id, delta, null),
    offset: () => r.cursorOffset(base, n.cursor04!)};
}
export function runFObjTimingSelfTest(): void {
  {
    const f = fixture([], {flags10: 0, frame1c: -0});
    f.r.interpretNode(null, NaN, Symbol('ignored on null node'));
    f.r.effects.interpretAll(null, NaN, Symbol('ignored on null list'));
    f.run(NaN); f.run(1 + 2 ** -25);
    f.r.interpretNode(null, 1 + 2 ** -25, null);
    f.r.effects.interpretAll(null, 1 + 2 ** -25, null);
    check(Object.is(f.n.frame1c, -0), 'state0 and null no-ops return before delta read or frame store');
    rejects(() => f.r.interpretNode(f.id, 1, Symbol()), 'non-null callback');
    rejects(() => f.r.effects.interpretAll(f.id, 1, Symbol()), 'non-null callback');
    check(Object.is(f.n.frame1c, -0), 'callback refusal precedes mutation');
  }
  for (const state of [1, 2, 3, 4, 5, 6]) {
    const f = fixture([], {flags10: 0xe0 | state, frame1c: -2}); f.run(.5);
    check(f.n.frame1c === -1.5 && f.n.flags10 === (0xe0 | state) && f.offset() === 0,
      'negative clock returns before every active state');
  }
  for (const frame of [-(2 ** -149), 2 ** -149, -0, 0]) {
    const f = fixture([], {flags10: 6, frame1c: frame}); f.run(-0);
    const expected = frame < 0 ? frame : Math.fround(Math.fround(frame + -0) + 0);
    check(Object.is(f.n.frame1c, expected), 'signed-zero/subnormal advance and end addition');
  }
  {
    const cancellation = fixture([], {flags10: 6, frame1c: -1}); cancellation.run(1 + 2 ** -23);
    check(cancellation.n.frame1c === 2 ** -23, 'supported single delta survives cancellation');
    for (const state of [1, 2, 3, 4, 5, 6]) {
      for (const delta of [2 ** 24 + .5, 1 + 2 ** -25, 2 ** 80 + 2 ** 56]) {
        const f = fixture([], {flags10: state, frame1c: state === 1 ? -1 : 1});
        const before = {...f.n};
        rejects(() => f.run(delta), 'float32 delta');
        check((Object.keys(before) as (keyof SourceFObjHeader)[]).every(key => Object.is(f.n[key], before[key])),
          'unsupported delta fails before every active-state write, including negative clock');
      }
    }
    const g = fixture([], {flags10: 4, half1a: 1, frame1c: -0}); g.run(-0);
    check(Object.is(g.n.frame1c, -0) && g.n.flags10 === 5, 'nonnegative -0 reaches state4 without changing sign');
  }
  for (const state of [1, 2, 3, 6]) {
    const f = fixture([], {flags10: 0x60 | state, byte11: 6, byte12: 2}); f.run(2);
    check(f.n.frame1c === 2 && f.n.flags10 === (0xa0 | state) && f.n.byte12 === 6 &&
      f.n.value20 === 20 && f.n.value28 === 30 && f.n.value2c === 40,
      'EOF/end flush preserves stored state and slopes, clears40 sets80');
    f.run(1);
    check(f.n.frame1c === 3 && f.n.flags10 === (0xa0 | state) && f.n.value28 === 30 &&
      f.n.value2c === 40 && f.n.value20 === 20, 'repeated EOF follows persisted state, preserves80/20 and slopes');
  }
  for (const state of [4, 5]) {
    const f = fixture([], {flags10: 0xa0 | state, half1a: 7, frame1c: 2, byte12: 2}); f.run(1);
    check(f.n.flags10 === 0xa5 && f.n.frame1c === 3 && f.n.value28 === 30 && f.n.value2c === 40 &&
      f.n.value20 === 10, 'wait>frame stores5, retains20 and no slope calculation');
    f.run(4);
    check(f.n.flags10 === 0xa3 && f.n.frame1c === 7, 'wait equality subtracts then EOF restores consumed wait, not state6');
  }
  {
    const f = fixture([1, 10, 3, 1, 20, 4, 1, 30]);
    f.r.effects.requestAll(f.id, 0); f.r.effects.interpretAll(f.id, 1, null);
    check(f.n.flags10 === 0x25 && f.n.frame1c === 1 && f.n.half1a === 3 && f.offset() === 5 &&
      f.n.value20 === 10 && f.n.value24 === 20, 'request-loader-wait-loader pauses in state5');
    f.run(7);
    check(f.n.frame1c === 5 && f.n.flags10 === 0x23 && f.offset() === 8 &&
      f.n.value20 === 20 && f.n.value24 === 30, 'multiple waits restore LAST wait4, not sum7, after EOF');
    const cursor = f.n.cursor04;
    f.r.effects.requestAll(f.id, 0); f.run(8);
    check(f.n.cursor04 === cursor && f.n.frame1c === 5, 'request replays immutable bytes and canonical cursor');
  }
  {
    const f = fixture([0x21, 10, 0, 20, 0, 30]); f.run();
    check(f.offset() === 6 && f.n.half16 === 0 && f.n.frame1c === 0 && f.n.flags10 === 0x23 &&
      f.n.value20 === 20 && f.n.value24 === 30, 'repeated value groups and zero waits finish with bounded progress');
    const g = fixture([0x15, 8, 9, 1, 10], {}, 8); g.run();
    check(g.n.value28 === 8 && g.n.value2c === 9 && g.n.value24 === 10 && g.n.flags10 === 3,
      'repeated opcode5 loader return stays state1 until real value then EOF');
    const h = fixture([0, 99]); h.run(2);
    check(h.n.flags10 === 1 && h.n.frame1c === 2 && h.offset() === 1,
      'loader local return0 stops without storing zero');
  }
  for (const [bytes, wait] of [ [[0], 0], [[127], 127], [[128, 1], 128],
    [[255, 255, 3], 65535], [[128, 128, 4], 0], [[255, 255, 255, 255, 127], 65535],
    [[128, 128, 128, 128, 0], 0] ] as const) {
    const f = fixture([...bytes], {flags10: 0x83});
    check(f.r.loadWait(f.n) === 2 && f.n.half1a === wait && f.n.flags10 === 0xa2 &&
      f.offset() === bytes.length, 'OR-varint bounded shifts, truncating halfword and flag stores');
  }
  {
    const f = fixture([], {flags10: 3, half1a: 17});
    check(f.r.loadWait(f.n) === 6 && f.n.flags10 === 3 && f.n.half1a === 17, 'wait EOF has no header writes');
    const g = fixture([1], {flags10: 3, length0c: 0}); g.n.cursor04 = g.r.cursorAt(g.base, 1);
    check(g.r.loadWait(g.n) === 6 && g.n.flags10 === 3, 'cursor beyond declared end returns local6');
    for (const bytes of [[128], [128, 128, 128, 128, 128, 0]]) {
      const h = fixture(bytes, {flags10: 3, half1a: 17});
      rejects(h.run, bytes.length === 1 ? 'truncated wait' : 'oversized encoding');
      check(h.offset() === Math.min(bytes.length, 5) && h.n.half1a === 17 && h.n.flags10 === 3,
        'failed wait keeps consumed cursor but no duration/flag stores');
    }
    const h = fixture([128, 0], {flags10: 3, length0c: 1}); rejects(h.run, 'truncated wait');
    check(h.offset() === 1, 'declared length checked independently of storage');
    const i = fixture([], {flags10: 3, length0c: 1}); rejects(i.run, 'truncated wait');
    check(i.offset() === 0, 'unreadable bounded byte does not advance cursor');
  }
  {
    const f = fixture([1], {flags10: 4}); rejects(() => f.r.loadWait(f.n), 'source assertion');
    f.n.flags10 = 3; f.n.cursor04 = null; rejects(f.run, 'null stream');
    f.n.cursor04 = Symbol(); rejects(f.run, 'provenance');
    rejects(() => f.r.loadWait({...f.n}), 'non-owned');
    const g = fixture([], {flags10: 6}); g.n.frame1c = Infinity; rejects(g.run, 'finite source float32');
  }
  for (const state of [7, 15]) {
    const f = fixture([], {flags10: state, frame1c: 1}); rejects(() => f.run(1), 'unsupported state');
    check(f.n.frame1c === 1, 'unsupported state fails before clock write');
  }
  for (const delta of [NaN, Infinity, -Infinity, Number.MAX_VALUE]) {
    const f = fixture([], {flags10: 6, frame1c: 1}); rejects(() => f.run(delta),
      Number.isFinite(delta) ? 'float32 delta' : 'finite double');
    check(f.n.frame1c === 1, 'invalid clock aborts without storing nonfinite');
  }
  {
    const max = (2 - 2 ** -23) * 2 ** 127;
    const f = fixture([], {flags10: 6, frame1c: max});
    rejects(() => f.run(max), 'overflow');
    check(f.n.frame1c === max, 'supported inputs producing overflow fail before frame store');
  }
  {
    const f = fixture([], {flags10: 5, half1a: 1, frame1c: 2}, 1);
    rejects(f.run, 'transition budget');
    check(f.n.flags10 === 4 && f.n.frame1c === 2, 'budget abort retains state5->4 write');
    const g = fixture([0x25, 1, 2, 3], {}, 2); rejects(g.run, 'transition budget');
    check(g.n.value2c === 2 && g.n.half16 === 1 && g.offset() === 3, 'budget bounds repeated loader work');
    rejects(() => createSourceFObjNullCallbackRuntime(0), 'transition budget');
  }
  {
    const f = fixture([], {flags10: 0xe5, byte12: 6, half1a: 3});
    f.r.effects.stopAll(f.id, 1, null);
    check(f.n.flags10 === 0xe0 && f.n.frame1c === 1, 'stop runs real timing when prior opcode6 then clears state');
    const g = fixture([], {flags10: 5, byte12: 2}); g.r.effects.stopAll(g.id, 1, null);
    check(g.n.flags10 === 0 && g.n.frame1c === 0, 'stop skips timing for other prior opcodes');
    g.n.flags10 = 5;
    rejects(() => g.r.effects.stopAll(g.id, 1, Symbol()), 'non-null callback');
    check(g.n.flags10 === 5, 'factory refuses callbacks even if stop would not invoke them');
  }
  {
    const f = fixture([], {flags10: 0xa6, byte11: 6, byte12: 6});
    const a = createSourceAObj({flags: AOBJ_NO_CALLBACK, frame: 0, rewind: 0, end: 2, rate: 1, fobjs: f.id});
    const counts = createSourceAObjCounters(), callback = Symbol('opaque callback');
    interpretSourceAObj(a, callback, f.r.effects, counts);
    check(a.frame === 1 && f.n.frame1c === 1 && counts.running === 1,
      'AObj suppresses callback on ordinary interpreter path');
    rejects(() => interpretSourceAObj(a, callback, f.r.effects, counts), 'non-null callback');
    check(a.frame === 2 && f.n.frame1c === 2 && !(a.flags & AOBJ_STOPPED) && counts.running === 1 &&
      counts.stopped === 0 && f.n.flags10 === 0xa6,
      'AObj end stop forwards unsuppressed callback: refuse without rolling back preceding clock writes');
    a.flags = AOBJ_LOOP | AOBJ_NO_CALLBACK; a.frame = 1;
    rejects(() => interpretSourceAObj(a, callback, f.r.effects, counts), 'non-null callback');
    check(a.frame === 2 && f.n.frame1c === 2 && a.flags === (AOBJ_LOOP | AOBJ_NO_CALLBACK) && counts.running === 1,
      'AObj wrap stop refuses original callback before rewind/request/interpret');
  }
  console.log('[fobj-timing] PASS: bounded callback-null source clock/wait/state progression; synthetic tests, no interpolation or live integration');
}
