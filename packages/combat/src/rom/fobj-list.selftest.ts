import {createSourceFObjRuntime, type SourceFObjHeader, type SourceFObjInterpreter} from './fobj-list.js';
import {AOBJ_LOOP, AOBJ_NO_CALLBACK, AOBJ_REQUEST, AOBJ_STOPPED, createSourceAObj, createSourceAObjCounters,
  interpretSourceAObj, requestSourceAObj} from './aobj-clock.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-list] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = '';
  try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
const base = Symbol('data'), cursor = Symbol('cursor'), callback = Symbol('callback');
function header(overrides: Partial<SourceFObjHeader> = {}): SourceFObjHeader {
  return {length0c: 0, track13: 0, format14: 0, format15: 0, next00: null, cursor04: cursor, base08: base, flags10: 255, byte11: 17, byte12: 6,
    half16: 65535, offset18: -1, half1a: 123, frame1c: 9, value20: -2, value24: 3,
    value28: -4, value2c: 5, ...overrides};
}
export function runFObjListSelfTest(): void {
  {
    const r = createSourceFObjRuntime(() => { throw Error('request must not interpret'); });
    const tail = r.createNode(header({offset18: 32767}));
    const input = header({next00: tail});
    const head = r.createNode(input);
    input.offset18 = 0;
    const original = 1 + 2 ** -23;
    r.effects.requestAll(head, original);
    const n = r.getNode(head), t = r.getNode(tail);
    check(n.frame1c === 2 ** -23, 'supported single operand cancellation preserves low bits');
    check(t.frame1c === Math.fround(32767 + original), 'request traverses tail');
    check(n.next00 === tail && n.base08 === base && n.cursor04 === base && n.offset18 === -1,
      'copies inputs, resets cursor, preserves next/base/signed offset');
    check(n.flags10 === 0xb1 && n.byte11 === 0 && n.byte12 === 0 && n.half16 === 0 && n.half1a === 0,
      'clears bit40 and low nibble, sets state1, resets byte/halfword fields');
    check([n.value20, n.value24, n.value28, n.value2c].every(v => Object.is(v, 0)), 'source positive zeros');
    for (const flags of [0, 1, 0x40, 0x7f, 0x80, 0xff]) {
      n.flags10 = flags; r.effects.requestAll(head, -32768);
      check(n.flags10 === ((flags & 0xb0) | 1), 'all flag regions preserved/reset');
    }
    n.offset18 = 1;
    for (const unsupported of [1 + 2 ** -25, 2 ** 24 + .5, 2 ** 80 + 2 ** 56]) {
      const before = {...n}, tailBefore = {...t};
      rejects(() => r.effects.requestAll(head, unsupported), 'float32 request');
      check((Object.keys(before) as (keyof SourceFObjHeader)[]).every(key =>
        Object.is(n[key], before[key]) && Object.is(t[key], tailBefore[key])),
        'unsupported request fails before writes to any list node');
    }
    n.offset18 = -32768; r.effects.requestAll(head, 32768);
    check(Object.is(n.frame1c, 0), 'signed short minimum and cancellation');
    n.offset18 = 0; r.effects.requestAll(head, -0);
    check(Object.is(n.frame1c, 0), 'positive integer zero plus negative double zero');
    r.effects.requestAll(head, 2 ** -149);
    check(n.frame1c === 2 ** -149, 'finite float32 subnormal');
  }
  {
    const calls: SourceFObjHeader[] = [];
    const r = createSourceFObjRuntime((n, delta, cb) => {
      calls.push(n); check(delta === -2 && cb === callback, 'forwards interpreter operands');
      n.flags10 = 0x6f; n.byte12 = 0; n.next00 = replacement;
    });
    const skipped = r.createNode(header());
    const replacement = r.createNode(header({byte12: 5, flags10: 0x9d}));
    const head = r.createNode(header({next00: skipped}));
    r.effects.stopAll(head, -2, callback);
    check(calls.length === 1 && calls[0] === r.getNode(head), 'only byte12 six invokes interpreter');
    check(r.getNode(head).flags10 === 0x60 && r.getNode(replacement).flags10 === 0x90 &&
      r.getNode(skipped).flags10 === 0xff, 'stop reloads flags and next after callback, clears non-six too');
  }
  {
    const calls: SourceFObjHeader[] = [];
    const r = createSourceFObjRuntime((n, delta, cb) => {
      check(Object.is(delta, -0) && cb === null, 'preserves negative-zero delta/null callback');
      calls.push(n);
      if (n === r.getNode(head)) { n.next00 = replacement; r.getNode(replacement).byte12 = 7; }
      else n.next00 = null;
    });
    const skipped = r.createNode(header());
    const replacement = r.createNode(header({byte12: 0, next00: skipped}));
    const head = r.createNode(header({next00: skipped, byte12: 0}));
    r.effects.interpretAll(head, -0, null);
    check(calls.length === 2 && calls[1] === r.getNode(replacement) && r.getNode(head).flags10 === 255,
      'interpret invokes all states, follows changed next, reloads termination, never clears flags');
  }
  {
    const events: string[] = [];
    const r = createSourceFObjRuntime((n, delta, cb) => {
      events.push(`${n.frame1c}:${delta}:${cb === callback}`);
      n.byte12 = 6; // Explicit test interpreter fixture, not a decoder.
    });
    const id = r.createNode(header());
    const a = createSourceAObj({flags: AOBJ_LOOP | AOBJ_NO_CALLBACK, frame: 9, rewind: 2, end: 10, rate: 1, fobjs: id});
    const counts = createSourceAObjCounters();
    interpretSourceAObj(a, callback, r.effects, counts);
    check(events.join() === '9:1:true,1:0:false' && a.frame === 2 && r.getNode(id).flags10 === 0xb1,
      'AObj adapter stop/request/interpret ordering, real header reset, suppressed interpret callback');
    a.flags = 0; a.frame = 9; events.length = 0;
    interpretSourceAObj(a, callback, r.effects, counts);
    check(events.join() === '1:1:true,1:1:true' && a.flags === AOBJ_STOPPED && r.getNode(id).flags10 === 0xb0,
      'AObj completion interpret then state-six stop, synchronous effects');
    const original = 1 + 2 ** -25, before = {...r.getNode(id)};
    rejects(() => requestSourceAObj(a, original, r.effects), 'float32 request');
    check(a.frame === 1 && a.flags === AOBJ_REQUEST, 'unsupported forwarded request retains earlier AObj frame and flags');
    check((Object.keys(before) as (keyof SourceFObjHeader)[]).every(key =>
      Object.is(r.getNode(id)[key], before[key])), 'restricted FObj adapter rejects original double without header writes');
    requestSourceAObj(a, 1 + 2 ** -23, r.effects);
    check(r.getNode(id).frame1c === 2 ** -23, 'supported single request succeeds after rejected adapter call');
  }
  {
    // Derived numeric observation, capture06 pair54 nested in AObj pair53,
    // pad105. Eight original nodes, not raw RAM/stream bytes. See source plan.
    const request = 0.6333333849906921; // f64 3fe4444460000000; f32 3f222223
    const r = createSourceFObjRuntime(() => { throw Error('request must not interpret'); });
    const data = Array.from({length: 8}, () => Symbol('captured stream alias'));
    const lengths = [5, 5, 5, 11, 5, 5, 5, 5];
    const tracks = [9, 4, 5, 2, 3, 6, 7, 8];
    const formats = [0x8788, 0x8788, 0x8788, 0x4f88, 0x8888, 0x8888, 0x8888, 0x8888];
    const ids: symbol[] = [];
    for (let i = 7; i >= 0; i--) ids[i] = r.createNode(header({next00: ids[i + 1] ?? null,
      cursor04: null, base08: data[i]!, flags10: 0, byte11: 0, byte12: 0, half16: 0,
      length0c: lengths[i]!, track13: tracks[i]!, format14: formats[i]! >> 8, format15: formats[i]! & 255,
      offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0}));
    const a = createSourceAObj({flags: AOBJ_STOPPED, frame: 0, rewind: 0, end: 60, rate: 1, fobjs: ids[0]!});
    requestSourceAObj(a, request, r.effects);
    check(a.flags === 0x08000000 && a.frame === request && Object.is(a.rewind, 0) &&
      a.end === 60 && a.rate === 1 && a.fobjs === ids[0], 'capture06 observed AObj request fields');
    for (let i = 0; i < ids.length; i++) {
      const n = r.getNode(ids[i]!);
      check(n.next00 === (ids[i + 1] ?? null) && n.cursor04 === data[i] && n.base08 === data[i] &&
        n.length0c === lengths[i] && n.track13 === tracks[i] &&
        n.format14 === (formats[i]! >> 8) && n.format15 === (formats[i]! & 255) &&
        n.flags10 === 1 && n.byte11 === 0 && n.byte12 === 0 && n.half16 === 0 &&
        n.offset18 === 0 && n.half1a === 0 && n.frame1c === request &&
        [n.value20, n.value24, n.value28, n.value2c].every(v => Object.is(v, 0)),
        'capture06 observed FObj request fields');
    }
  }
  {
    rejects(() => createSourceFObjRuntime(undefined as unknown as SourceFObjInterpreter), 'interpreter required');
    const r = createSourceFObjRuntime(() => { throw Error('unsupported decoder'); });
    r.effects.requestAll(null, Infinity);
    r.effects.stopAll(null, NaN, 12 as unknown as symbol);
    r.effects.interpretAll(null, Infinity, null);
    rejects(() => r.effects.requestAll(Symbol(), 0), 'non-owned');
    rejects(() => r.createNode(header({offset18: 32768})), 'offset18');
    rejects(() => r.createNode(header({flags10: 256})), 'flags10');
    rejects(() => r.createNode(header({frame1c: .1})), 'float32');
    rejects(() => r.createNode(header({base08: 0x80400000 as unknown as symbol})), 'opaque symbol');
    const id = r.createNode(header());
    rejects(() => r.effects.stopAll(id, 1, callback), 'unsupported decoder');
    check(r.getNode(id).flags10 === 255, 'failed interpreter does not silently clear flags');
    rejects(() => r.effects.requestAll(id, Infinity), 'finite double');
    check(r.getNode(id).cursor04 === cursor, 'invalid argument before stores');
    rejects(() => r.effects.requestAll(id, 1e40), 'float32 request');
    check(r.getNode(id).cursor04 === cursor && r.getNode(id).frame1c === 9, 'unsupported request fails before cursor store');
  }
  {
    const r = createSourceFObjRuntime(n => { n.flags10 = 0x7f; n.next00 = Symbol('unknown'); });
    const id = r.createNode(header());
    rejects(() => r.effects.stopAll(id, 1, null), 'non-owned');
    check(r.getNode(id).flags10 === 0x70, 'valid callback then stop clear precedes failed next resolution');
    r.getNode(id).next00 = id;
    rejects(() => r.effects.requestAll(id, 2), 'cycle');
    check(r.getNode(id).flags10 === 0x31, 'cycle rejection preserves completed request');
    r.getNode(id).next00 = null; r.effects.requestAll(id, 3);
    check(r.getNode(id).frame1c === 2, 'busy guard released after failure');
    const limited = createSourceFObjRuntime(() => {}, 1);
    const tail = limited.createNode(header()), head = limited.createNode(header({next00: tail}));
    rejects(() => limited.effects.requestAll(head, 2), 'budget');
    check(limited.getNode(head).frame1c === 1 && limited.getNode(tail).frame1c === 9, 'budget does not touch next node');
  }
  {
    for (const kind of ['throw', 'async', 'reentry', 'invalid', 'frozen'] as const) {
      const r = createSourceFObjRuntime(n => {
        n.flags10 = 0x5f;
        if (kind === 'throw') throw Error('decoder failure');
        if (kind === 'async') return Promise.resolve() as unknown as void;
        if (kind === 'reentry') r.effects.requestAll(id, 3);
        if (kind === 'invalid') n.frame1c = Infinity;
        if (kind === 'frozen') Object.freeze(n);
      });
      const id = r.createNode(header());
      rejects(() => r.effects.stopAll(id, 0, callback),
        {throw: 'decoder failure', async: 'synchronously', reentry: 'reentry', invalid: 'float32', frozen: 'non-writable'}[kind]);
      check(r.getNode(id).flags10 === 0x5f, 'failure retains callback store and skips post-call clear');
    }
  }
  {
    let first = true;
    const r = createSourceFObjRuntime(n => {
      if (first) { first = false; r.effects.requestAll(id, 4); }
      n.value20 = 12;
    });
    const id = r.createNode(header());
    rejects(() => r.effects.interpretAll(id, 0, null), 'reentry');
    r.effects.interpretAll(id, 0, null);
    check(r.getNode(id).value20 === 12, 'callback failure releases runtime guard');
    const other = createSourceFObjRuntime(() => {});
    rejects(() => other.effects.requestAll(id, 0), 'non-owned');
  }
  {
    const seen: SourceFObjHeader[] = [];
    const r = createSourceFObjRuntime(n => {
      seen.push(n);
      if (n === r.getNode(oldHead)) a.fobjs = newHead;
    });
    const oldHead = r.createNode(header());
    const newHead = r.createNode(header({offset18: 3}));
    const a = createSourceAObj({flags: AOBJ_LOOP, frame: 9, rewind: 2, end: 10, rate: 1, fobjs: oldHead});
    interpretSourceAObj(a, callback, r.effects, createSourceAObjCounters());
    check(seen.length === 2 && seen[0] === r.getNode(oldHead) && seen[1] === r.getNode(newHead) &&
      r.getNode(oldHead).frame1c === 9 && r.getNode(newHead).frame1c === 5,
      'AObj adapter resolves changed head for subsequent request/interpret effects');
  }
  console.log('[fobj-list] PASS: offline reset/walkers/AObj adapter and one observed request sample; external interpreter required, not full retail replay');
}
