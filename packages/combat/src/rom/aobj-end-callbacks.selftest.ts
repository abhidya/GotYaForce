import {AOBJ_STOPPED, createSourceAObj, interpretSourceAObj,
  type SourceAObjEffects} from './aobj-clock.js';
import {createSourceAObjEndCallbackRuntime,
  type SourceAObjEndCallbackNode} from './aobj-end-callbacks.js';

function check(ok: boolean, message: string): void { if (!ok) throw Error(`[aobj-end-callbacks] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = '';
  try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected rejection containing ${text}, got ${diagnostic}`);
}
function setUnchecked(record: object, key: string, value: unknown): void {
  Object.defineProperty(record, key, {value});
}
function readOnly(record: object, key: string): void {
  Object.defineProperty(record, key, {writable: false});
}
function fixture(maxNodes = 4096) {
  const runtime = createSourceAObjEndCallbackRuntime(maxNodes);
  const events: string[] = [];
  const makeNode = (label: string, next00: symbol | null = null): symbol => runtime.createNode({
    next00, callback04: runtime.createCallback(() => { events.push(label); }),
  });
  runtime.counts.stopped = 1;
  return {runtime, events, makeNode};
}
export function runAObjEndCallbackSelfTest(): void {
  {
    const {runtime: r} = fixture();
    let calls = 0;
    const callback04 = r.createCallback(function (this: unknown) {
      check(this === undefined && arguments.length === 0, 'callback has no receiver and exactly zero arguments');
      calls++;
    });
    const initial = {next00: null, callback04};
    const head = r.createNode(initial);
    initial.callback04 = Symbol('mutated backing input');
    check(Object.isFrozen(r) && Object.isSealed(r.state) && Object.isSealed(r.counts) &&
      Object.isSealed(r.getNode(head)) && r.getNode(head).callback04 === callback04,
    'frozen bindings and independent sealed mutable factory records');
    r.state.head28 = head;
    const {invoke} = r;
    invoke(); invoke();
    check(calls === 2 && r.counts.stopped === 1 && r.counts.running === 0 && r.state.head28 === head,
      'detached method works; invoke does not consume callback list or reset accounting');
    const copied = r.createNode(Object.freeze({next00: head, callback04}));
    r.getNode(copied).next00 = null;
    check(r.getNode(copied).next00 === null, 'read-only initial data is copied into writable owned fields');
  }
  {
    const {runtime: r, events, makeNode} = fixture();
    r.state.head28 = makeNode('eligible');
    for (const [stopped, running, calls] of [[0, 0, 0], [0, 1, 0], [1, 1, 0], [1, 0, 1],
      [0xffffffff, 0, 2], [1, 0xffffffff, 2]] as const) {
      r.counts.stopped = stopped; r.counts.running = running; r.invoke();
      check(events.length === calls, 'both gate conditions, including full uint32 range');
    }
    r.counts.stopped = 1; r.counts.running = 0; r.state.head28 = null; r.invoke();
    check(events.length === 2, 'eligible null head is a no-op');
  }
  {
    const r = createSourceAObjEndCallbackRuntime();
    setUnchecked(r.state, 'head28', 123);
    r.counts.running = NaN;
    r.invoke();
    r.counts.stopped = 1; r.counts.running = 1; r.invoke();
    readOnly(r.state, 'head28'); r.invoke();
    check(r.counts.running === 1, 'excluded traversal ignores malformed and non-writable head, with stopped short circuit');
    r.counts.running = 0;
    rejects(r.invoke, 'head28: non-writable');
    const s = createSourceAObjEndCallbackRuntime();
    readOnly(s.counts, 'running');
    s.invoke();
    check(s.counts.stopped === 0, 'zero stopped does not inspect running writability');
  }
  {
    const {runtime: r, makeNode} = fixture();
    const head = makeNode('unvisited'); r.state.head28 = head;
    Object.freeze(r.state); Object.freeze(r.getNode(head));
    r.counts.stopped = NaN; r.counts.running = -1;
    r.init();
    check(r.counts.stopped === 0 && r.counts.running === 0 && r.state.head28 === head,
      'init overwrites invalid old count values but never reads or resets head/list');
    const a = fixture().runtime;
    a.counts.stopped = 5; a.counts.running = 7; readOnly(a.counts, 'stopped');
    rejects(a.init, 'stopped: non-writable');
    check(a.counts.stopped === 5 && a.counts.running === 7, 'first init write failure prevents both stores');
    const b = fixture().runtime;
    b.counts.stopped = 5; b.counts.running = 7; readOnly(b.counts, 'running');
    rejects(b.init, 'running: non-writable');
    check(b.counts.stopped === 0 && b.counts.running === 7,
      'init stores stopped before checking/storing running; partial reset is retained');
  }
  {
    const {runtime: r, events, makeNode} = fixture();
    const skipped = makeNode('stale next'), wrongHead = makeNode('changed global head');
    const changedNext = makeNode('stale callback');
    const replacement = r.createCallback(() => { events.push('replacement callback'); });
    let head: symbol;
    head = r.createNode({next00: skipped, callback04: r.createCallback(() => {
      events.push('first');
      r.counts.stopped = 0; r.counts.running = 1; r.state.head28 = wrongHead;
      r.getNode(head).next00 = changedNext;
      r.getNode(changedNext).callback04 = replacement;
      r.getNode(head).callback04 = Symbol('already-consumed callback may change');
    })});
    r.state.head28 = head; r.invoke();
    check(events.join() === 'first,replacement callback' && r.counts.running === 1 && r.counts.stopped === 0,
      'eligibility/head selected once, current next and later callback loaded after mutation, no stale-field preflight');
    r.invoke();
    check(events.length === 2, 'next invocation applies its own eligibility gate');
  }
  {
    const {runtime: r, events} = fixture();
    let head: symbol;
    head = r.createNode({next00: Symbol('unresolved original next'), callback04: r.createCallback(() => {
      events.push('first');
      const callback04 = r.createCallback(() => { events.push('appended'); });
      r.getNode(head).next00 = r.createNode({next00: null, callback04});
    })});
    setUnchecked(r.getNode(head), 'next00', 123);
    r.state.head28 = head; r.invoke();
    check(events.join() === 'first,appended', 'callback can repair malformed next and register an owned node before next is read');
    r.getNode(head).callback04 = r.createCallback(() => { events.push('truncate'); r.getNode(head).next00 = null; });
    r.invoke();
    check(events.join() === 'first,appended,truncate', 'post-callback null truncates the former continuation');
  }
  {
    const {runtime: r, events, makeNode} = fixture();
    const tail = makeNode('tail');
    let head: symbol;
    head = r.createNode({next00: tail, callback04: r.createCallback(() => {
      events.push('first');
      r.counts.stopped = NaN; r.counts.running = -1;
      setUnchecked(r.state, 'head28', 123);
      Object.freeze(r.state); Object.freeze(r.counts);
      readOnly(r.getNode(head), 'callback04');
    })});
    r.state.head28 = head; r.invoke();
    check(events.join() === 'first,tail', 'already-read head/counters/callback fields are not revalidated after handlers');
  }
  {
    const {runtime: r, events, makeNode} = fixture(), foreign = fixture();
    const callback04 = r.createCallback(() => { events.push('owned'); });
    const otherCallback = foreign.runtime.createCallback(() => { events.push('foreign callback must not run'); });
    const head = r.createNode({next00: null, callback04: otherCallback});
    r.state.head28 = head;
    rejects(r.invoke, 'unknown/non-owned callback');
    check(events.length === 0, 'foreign callback is rejected only when dispatched');
    r.getNode(head).callback04 = callback04; r.invoke();
    check(events.join() === 'owned', 'failed invocation releases reentry guard and permits repaired callback');
    const foreignNode = foreign.makeNode('foreign node');
    r.state.head28 = foreignNode;
    rejects(r.invoke, 'unknown/non-owned node');
    rejects(() => r.getNode(foreignNode), 'unknown/non-owned node');
    rejects(() => r.getNode(Symbol('unknown')), 'unknown/non-owned node');
    const first = makeNode('before foreign next', foreign.makeNode('also foreign'));
    r.state.head28 = first;
    rejects(r.invoke, 'unknown/non-owned node');
    check(events.at(-1) === 'before foreign next', 'unresolved next refuses after preceding callback effects');
    r.state.head28 = r.createNode({next00: null, callback04: Symbol('unknown callback')});
    rejects(r.invoke, 'unknown/non-owned callback');
  }
  {
    const r = createSourceAObjEndCallbackRuntime();
    const callback04 = r.createCallback(() => {});
    for (const key of ['next00', 'callback04'] as const) {
      let getterCalls = 0;
      const input = {next00: null, callback04};
      Object.defineProperty(input, key, {get() { getterCalls++; return key === 'next00' ? null : callback04; }});
      rejects(() => r.createNode(input), `${key}: own data property`);
      check(getterCalls === 0, 'initial accessors are rejected without getter invocation');
      const inherited = Object.create({next00: null, callback04}) as SourceAObjEndCallbackNode;
      Object.defineProperty(inherited, key === 'next00' ? 'callback04' : 'next00',
        {value: key === 'next00' ? callback04 : null});
      rejects(() => r.createNode(inherited), `${key}: own data property`);
    }
    rejects(() => r.createNode(null as unknown as SourceAObjEndCallbackNode), 'data record');
    rejects(() => r.createNode({next00: 1 as unknown as symbol, callback04}), 'next00: expected');
    rejects(() => r.createNode({next00: null, callback04: null as unknown as symbol}), 'callback04: expected');
    rejects(() => r.createCallback(null as unknown as () => void), 'handler required');
  }
  {
    for (const value of [-1, 0x100000000, 0.5, NaN, Infinity, '1', null]) {
      const r = fixture().runtime;
      setUnchecked(r.counts, 'stopped', value); rejects(r.invoke, 'stopped: expected uint32');
      r.counts.stopped = 1;
      setUnchecked(r.counts, 'running', value); rejects(r.invoke, 'running: expected uint32');
    }
    const {runtime: r, events, makeNode} = fixture();
    setUnchecked(r.state, 'head28', 123); rejects(r.invoke, 'head28: expected');
    const head = makeNode('before bad next'); r.state.head28 = head;
    setUnchecked(r.getNode(head), 'callback04', null); rejects(r.invoke, 'callback04: expected');
    check(events.length === 0, 'malformed callback fails before dispatch');
    r.getNode(head).callback04 = r.createCallback(() => { events.push('before bad next'); });
    setUnchecked(r.getNode(head), 'next00', 123); rejects(r.invoke, 'next00: expected');
    check(events.join() === 'before bad next', 'malformed next fails after dispatch');
  }
  {
    for (const key of ['stopped', 'running'] as const) {
      const {runtime: r, events, makeNode} = fixture();
      r.state.head28 = makeNode('must not run'); readOnly(r.counts, key);
      rejects(r.invoke, `${key}: non-writable`);
      check(events.length === 0, 'accessed non-writable counter rejected before callbacks');
    }
    for (const key of ['callback04', 'next00'] as const) {
      const {runtime: r, events, makeNode} = fixture();
      const head = makeNode('called'); r.state.head28 = head; readOnly(r.getNode(head), key);
      rejects(r.invoke, `${key}: non-writable`);
      check(events.length === (key === 'next00' ? 1 : 0), 'node writability is checked at each source field boundary');
    }
    const {runtime: r, events} = fixture();
    let head: symbol;
    head = r.createNode({next00: null, callback04: r.createCallback(() => {
      events.push('freeze next'); readOnly(r.getNode(head), 'next00');
    })});
    r.state.head28 = head; rejects(r.invoke, 'next00: non-writable');
    check(events.join() === 'freeze next', 'post-callback next writability failure retains callback effects');
  }
  {
    const {runtime: r, events, makeNode} = fixture();
    const tail = makeNode('unreached');
    r.state.head28 = r.createNode({next00: tail, callback04: r.createCallback(() => {
      events.push('partial'); r.counts.running = 23; r.state.head28 = null; throw Error('unsupported handler body');
    })});
    rejects(r.invoke, 'unsupported handler body');
    check(events.join() === 'partial' && r.counts.running === 23 && r.state.head28 === null,
      'throw preserves handler writes and effects without reaching the next callback');
    for (const result of [false, 0, null, {}, Promise.resolve()]) {
      const f = fixture();
      const head = f.runtime.createNode({next00: f.makeNode('unreached'),
        callback04: f.runtime.createCallback((() => {
          f.events.push('synchronous prefix'); f.runtime.counts.stopped = 9; return result;
        }) as unknown as () => void)});
      f.runtime.state.head28 = head;
      rejects(f.runtime.invoke, 'synchronously and return undefined');
      check(f.events.join() === 'synchronous prefix' && f.runtime.counts.stopped === 9,
        'non-undefined and async returns retain synchronous prefix and abort before continuation');
    }
  }
  {
    for (const maxNodes of [0, -1, 1.5, Infinity, NaN, Number.MAX_SAFE_INTEGER + 1]) {
      rejects(() => createSourceAObjEndCallbackRuntime(maxNodes), 'positive safe integer');
    }
    const {runtime: r, events, makeNode} = fixture(1);
    const tail = makeNode('tail'), head = makeNode('head', tail); r.state.head28 = head;
    rejects(r.invoke, 'budget exhausted');
    check(events.join() === 'head', 'node budget retains exactly the completed prefix');
    r.getNode(head).next00 = null; r.invoke(); r.invoke();
    check(events.join() === 'head,head,head', 'one-node exact budget passes and budget resets per invocation');
    const cycle = fixture();
    const a = cycle.makeNode('a'), b = cycle.makeNode('b', a);
    cycle.runtime.getNode(a).next00 = b; cycle.runtime.state.head28 = a;
    rejects(cycle.runtime.invoke, 'cycle/revisit');
    check(cycle.events.join() === 'a,b', 'two-node cycle refuses before repeated callback');
    cycle.runtime.getNode(a).next00 = a;
    rejects(cycle.runtime.invoke, 'cycle/revisit');
    check(cycle.events.join() === 'a,b,a', 'self-cycle also refuses before repeated callback');
    // At the revisit the graph is no longer cyclic; repeated identity is still
    // outside the bounded host domain, rather than silently invoking a twice.
    cycle.runtime.getNode(a).next00 = b;
    cycle.runtime.getNode(b).callback04 = cycle.runtime.createCallback(() => {
      cycle.events.push('uncycle'); cycle.runtime.getNode(a).next00 = null;
    });
    rejects(cycle.runtime.invoke, 'cycle/revisit');
    check(cycle.events.join() === 'a,b,a,a,uncycle', 'callback-mutated acyclic revisit is explicitly unsupported');
  }
  {
    for (const operation of ['invoke', 'init'] as const) for (const caught of [false, true]) {
      const {runtime: r, events, makeNode} = fixture();
      const tail = makeNode('unreached');
      const head = r.createNode({next00: tail, callback04: r.createCallback(() => {
        events.push('partial'); r.counts.stopped = 7;
        if (caught) { try { r[operation](); } catch { events.push('caught'); } }
        else r[operation]();
      })});
      r.state.head28 = head; rejects(r.invoke, 'reentry');
      check(events.join() === (caught ? 'partial,caught' : 'partial') && r.counts.stopped === 7,
        'same-runtime invocation/init reentry aborts before nested resets, even if handler catches it');
      r.getNode(head).callback04 = r.createCallback(() => {}); r.invoke();
      check(events.at(-1) === 'unreached', 'guard clears after rejected reentry');
    }
    const outer = fixture(), inner = fixture();
    inner.runtime.state.head28 = inner.makeNode('inner');
    outer.runtime.state.head28 = outer.runtime.createNode({next00: null,
      callback04: outer.runtime.createCallback(() => { inner.runtime.invoke(); outer.events.push('outer'); })});
    outer.runtime.invoke();
    check(inner.events.join() === 'inner' && outer.events.join() === 'outer', 'independent runtimes may invoke one another');
  }
  {
    const {runtime: r, events, makeNode} = fixture();
    r.state.head28 = makeNode('all completed');
    const a = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 1, rate: 1, fobjs: null});
    const b = createSourceAObj({flags: 0, frame: 0, rewind: 0, end: 2, rate: 1, fobjs: null});
    const effectsSeen: string[] = [];
    // Explicit scalar AObj test-double effects; no fake counter accounting and
    // no claim that these empty-list effects implement retail FObj behavior.
    const effects: SourceAObjEffects = {
      requestAll() { effectsSeen.push('request'); },
      stopAll() { effectsSeen.push('stop'); },
      interpretAll() { effectsSeen.push('interpret'); },
    };
    r.init();
    interpretSourceAObj(a, null, effects, r.counts);
    interpretSourceAObj(b, null, effects, r.counts);
    r.invoke();
    check(r.counts.stopped === 1 && r.counts.running === 1 && events.length === 0 &&
      !!(a.flags & AOBJ_STOPPED) && !(b.flags & AOBJ_STOPPED), 'real AObj completion accounting suppresses end callbacks while another runs');
    r.init();
    interpretSourceAObj(a, null, effects, r.counts);
    interpretSourceAObj(b, null, effects, r.counts);
    r.invoke();
    check(r.counts.stopped === 1 && r.counts.running === 0 && events.join() === 'all completed' &&
      effectsSeen.join() === 'interpret,stop,interpret,interpret,stop',
    'actual completion enables end callbacks; already stopped AObj is uncounted');
    r.init();
    interpretSourceAObj(a, null, effects, r.counts); interpretSourceAObj(b, null, effects, r.counts);
    interpretSourceAObj(null, null, effects, r.counts); r.invoke();
    check(r.counts.stopped === 0 && r.counts.running === 0 && events.length === 1,
      'later all-stopped/null pass produces no completion event without newly counted stops');
  }
  console.log('[aobj-end-callbacks] PASS: ordered global reset, gated mutable list callbacks, owned AObj counters and bounded failure prefixes (not retail replay)');
}
