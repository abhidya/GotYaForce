import {createSourceActorControlLifecycleRuntime, isSourceActorControlLifecycleRuntime,
  type SourceActorControlLifecycleBinding, type SourceActorControlLifecycleSources} from './actor-control-lifecycle.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersBinding} from './actor-status-timers.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-control-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
/** Owner seams isolate this helper; they do not emulate source effects. */
function fixture(defer = false) {
  const id = Symbol('control-lifecycle actor'), actual = createRomActor();
  const worldState: Partial<SourceActorWorldMatrixBinding> = {mode4a1: 0, mode4a0: 0, flags48a: 0};
  const statusState: Partial<SourceActorStatusTimersBinding> = {byte6fc: 0};
  const hooks: {worldActor?: () => unknown; statusActor?: () => unknown;
    world?: () => unknown; status?: () => unknown; statusWorld?: () => unknown} = {};
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'world actor receiver/id');
      return (hooks.worldActor ? hooks.worldActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === world && key === id, 'world binding receiver/id');
      return (hooks.world ? hooks.world() : worldState) as SourceActorWorldMatrixBinding;},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'status actor receiver/id');
      return (hooks.statusActor ? hooks.statusActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === status && key === id, 'status binding receiver/id');
      return (hooks.status ? hooks.status() : statusState) as Partial<SourceActorStatusTimersBinding>;},
    getWorldBinding(key: symbol) {check(this === status && key === id, 'status world receiver/id');
      return (hooks.statusWorld ? hooks.statusWorld() : worldState) as SourceActorWorldMatrixBinding;},
  };
  const sources = {world, status}, runtime = createSourceActorControlLifecycleRuntime(sources);
  const initial: Partial<SourceActorControlLifecycleBinding> = {byte490: 2, short49a: 3, short49c: 7};
  const bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  return {id, actual, worldState, statusState, hooks, world, status, sources, runtime, initial, bind,
    run: () => runtime.updateActor(id), binding: () => runtime.getActorBinding(id)};
}

export function runActorControlLifecycleSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual5e0 owner');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'same4a1/4a0/48a owner');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'same6fc owner');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'runtime frozen and copied binding sealed');
    equal(Object.keys(x.binding()).join(','), 'byte490,short49a,short49c', 'only absent fields get storage');
    check(isSourceActorControlLifecycleRuntime(x.runtime), 'genuine runtime brand');
    for (const value of [{...x.runtime}, Object.create(x.runtime), {}, null, undefined, () => x.runtime])
      check(!isSourceActorControlLifecycleRuntime(value), 'brand cannot be forged by shape or prototype');
    const before = JSON.stringify(x.actual), world = JSON.stringify(x.worldState), status = JSON.stringify(x.statusState);
    equal(x.run(), 0, 'literal source returned0'); equal(x.binding().short49a, 2, 'ordinary positive countdown');
    equal(x.binding().short49c, 7, 'ordinary branch does not touch49c');
    equal(JSON.stringify(x.actual), before, 'actual unchanged'); equal(JSON.stringify(x.worldState), world, 'world unchanged');
    equal(JSON.stringify(x.statusState), status, 'status unchanged'); equal(x.initial.short49a, 3, 'initial copied');
    x.initial.short49a = 100; equal(x.binding().short49a, 2, 'initial is not live storage');
    rejects(() => Object.assign(x.binding(), {extra: 1}), 'not extensible');
  }
  {
    // Every raw byte at each ordered signed-zero gate. Poison later scalars
    // rather than executing getters or assuming Proxy behavior is source evidence.
    for (const gate of ['mode4a1', 'mode4a0', 'byte6fc'] as const) {
      const x = fixture();
      for (let raw = 0; raw <= 255; raw++) {
        x.worldState.mode4a1 = 0; x.worldState.mode4a0 = 0; x.statusState.byte6fc = 0;
        x.worldState.flags48a = raw === 0 ? 0 : NaN; x.binding().short49a = 3;
        if (gate === 'byte6fc') x.statusState.byte6fc = raw;
        else x.worldState[gate] = raw;
        if (raw !== 0 && gate === 'mode4a1') {x.worldState.mode4a0 = NaN; x.statusState.byte6fc = NaN;}
        if (raw !== 0 && gate === 'mode4a0') x.statusState.byte6fc = NaN;
        equal(x.run(), 0, `${gate} raw byte returns0`);
        equal(x.binding().short49a, raw === 0 ? 2 : 3, `${gate} raw byte ordered gate`);
      }
    }
    const x = fixture(true); delete x.initial.byte490; delete x.initial.short49a; delete x.initial.short49c; x.bind();
    x.worldState.mode4a1 = 1; delete x.worldState.mode4a0; delete x.statusState.byte6fc; delete x.worldState.flags48a;
    equal(x.run(), 0, 'first gate permits all later fields absent'); equal(Object.keys(x.binding()).length, 0, 'missing stays missing');
    x.worldState.mode4a1 = 0; rejects(x.run, 'mode4a0: own data');
    x.worldState.mode4a0 = 0; rejects(x.run, 'byte6fc: own data');
    x.statusState.byte6fc = 0; rejects(x.run, 'flags48a: own data');
    x.worldState.flags48a = 2; rejects(x.run, 'short49c: own data');
    x.worldState.flags48a = 0; rejects(x.run, 'byte490: own data');
  }
  {
    const x = fixture(); x.actual.controlWord = NaN;
    for (let raw = 0; raw <= 255; raw++) {
      x.worldState.flags48a = raw; x.binding().short49a = 3; x.binding().short49c = 7;
      equal(x.run(), 0, 'all unsigned48a byte values');
      equal(x.binding().short49a, raw === 2 ? 3 : 2, 'only48a==2 selects49c');
      equal(x.binding().short49c, raw === 2 ? 6 : 7, '49c has priority');
    }
    x.worldState.flags48a = 0;
    for (let raw = 0; raw <= 255; raw++) {
      x.binding().byte490 = raw; x.binding().short49a = raw === 2 ? 3 : NaN;
      equal(x.run(), 0, 'all unsigned490 byte values');
      equal(x.binding().short49a, raw === 2 ? 2 : NaN, 'only490==2 reaches49a');
    }
    const priority = fixture(true); delete priority.initial.byte490; delete priority.initial.short49a; priority.bind();
    priority.worldState.flags48a = 2; priority.binding().short49c = 1; priority.actual.controlWord = NaN;
    equal(priority.run(), 0, '49c1->0 does not test readiness'); equal(priority.binding().short49c, 0, '49c reaches0');
    rejects(priority.run, 'controlWord: integer'); equal(priority.binding().short49c, 0, 'next call reaches readiness');
    priority.actual.controlWord = 1; equal(priority.run(), 0, '49c blocked returns0 without other branch');
    priority.actual.controlWord = 0; rejects(priority.run, '8005a204');
  }
  {
    const c = fixture(); c.worldState.flags48a = 2; c.actual.controlWord = 1;
    const a = fixture(); a.actual.controlWord = 0x1000;
    let ready = fixture(); ready.actual.controlWord = 0;
    // Full signed16 domain in each counter. This reference uses ordinary
    // arithmetic, independent of the implementation's extsh expression.
    for (let value = -32768; value <= 32767; value++) {
      c.binding().short49c = value; equal(c.run(), 0, '49c signed domain return');
      equal(c.binding().short49c, value > 0 ? value - 1 : value, '49c signed domain countdown');
      a.binding().short49a = value; equal(a.run(), 0, 'blocked49a signed domain return');
      equal(a.binding().short49a, value > 1 ? value - 1 : value === 1 ? 1 : value, 'blocked49a signed domain countdown/rearm');
      ready.binding().short49a = value;
      if (value === 1) rejects(ready.run, '8005a25c'); else equal(ready.run(), 0, 'ready49a signed domain return');
      equal(ready.binding().short49a, value > 0 ? value - 1 : value, 'ready49a signed domain preserves store on refusal');
      if (value === 1) ready = fixture(); // The next independent source case needs a fresh, complete actor.
    }
    for (const value of [-32768, -1, 0]) {
      a.binding().short49a = value; a.actual.controlWord = NaN;
      equal(a.run(), 0, 'initial nonpositive49a bypasses readiness'); equal(a.binding().short49a, value, 'no initial49a rearm');
    }
  }
  {
    // Every single bit distinguishes both masks, including signed JS bit31.
    for (let bit = 0; bit < 32; bit++) {
      const c = fixture(); c.worldState.flags48a = 2; c.binding().short49c = 0;
      const a = fixture();
      const value = 2 ** bit; c.actual.controlWord = value; a.actual.controlWord = value; a.binding().short49a = 1;
      if ([0, 1, 12, 24, 28, 31].includes(bit)) equal(c.run(), 0, '6ab9c relevant bit blocks');
      else rejects(c.run, '8005a204 reached unsupported source call 8006aab0');
      if ([12, 24, 28, 31].includes(bit)) {equal(a.run(), 0, '6abb8 relevant bit blocks'); equal(a.binding().short49a, 1, 'blocked rearm1');}
      else {rejects(a.run, '8005a25c reached unsupported source call 8006a980'); equal(a.binding().short49a, 0, 'ready refusal keeps decrement');}
    }
    for (const value of [0, 3, 0x6effeffc, 0x91001003, 0xffffffff]) {
      const c = fixture(); c.worldState.flags48a = 2; c.binding().short49c = 0;
      const a = fixture();
      c.actual.controlWord = value; a.actual.controlWord = value; a.binding().short49a = 1;
      if (value === 0 || value === 0x6effeffc) rejects(c.run, '8006aab0'); else equal(c.run(), 0, '6ab9c combined mask');
      if (value === 0 || value === 3 || value === 0x6effeffc) rejects(a.run, '8006a980'); else equal(a.run(), 0, '6abb8 combined mask');
    }
    for (const branch of ['49c', '49a'] as const) {
      const x = fixture(); x.worldState.flags48a = branch === '49c' ? 2 : 0; x.binding().short49c = 0;
      x.actual.controlWord = 0; x.binding().short49a = 1;
      let touched = false;
      for (const key of ['team', 'byte489', 'byte19'])
        Object.defineProperty(x.actual, key, {get() {touched = true; throw Error('later transition field read');}});
      rejects(x.run, branch === '49c' ? '8006aab0' : '8006a980');
      check(!touched, 'transition refusal precedes later field loads/stores');
    }
  }
  {
    for (const branch of ['49c', '49a'] as const) {
      const x = fixture(); x.worldState.flags48a = branch === '49c' ? 2 : 0;
      x.binding().short49c = 0; x.binding().short49a = 1; x.actual.controlWord = 0;
      const actorBefore = JSON.stringify(x.actual);
      rejects(x.run, branch === '49c' ? '8006aab0' : '8006a980');
      equal(x.binding().short49a, branch === '49c' ? 1 : 0, 'known incomplete transition retains exact prior stores');
      equal(JSON.stringify(x.actual), actorBefore, 'host incomplete marker is not a source actor write');
      rejects(x.run, 'known incomplete control transition');
      x.worldState.mode4a1 = 1; rejects(x.run, 'known incomplete control transition');
      x.worldState.mode4a1 = 0; x.worldState.mode4a0 = 1; rejects(x.run, 'known incomplete control transition');
      x.worldState.mode4a0 = 0; x.statusState.byte6fc = 1; rejects(x.run, 'known incomplete control transition');
      x.statusState.byte6fc = 0; x.binding().short49a = 27; x.binding().short49c = 29;
      x.actual.controlWord = 0xffffffff; x.worldState.flags48a = branch === '49c' ? 0 : 2;
      rejects(x.run, 'known incomplete control transition');
      equal(x.binding().short49a, 27, 'changed timer cannot permit later stores');
      equal(x.binding().short49c, 29, 'changed branch cannot permit later stores');
      Object.defineProperty(x.worldState, 'mode4a1', {get() {throw Error('scalar read before incomplete guard');}});
      x.hooks.worldActor = () => {throw Error('source owner call before incomplete guard');};
      rejects(x.run, 'known incomplete control transition');
      const independent = fixture(); equal(independent.run(), 0, 'independent actual actor remains admitted');
      equal(independent.binding().short49a, 2, 'independent actor writes normally');
    }
  }
  {
    const x = fixture(); x.binding().short49a = 1; x.actual.controlWord = NaN;
    rejects(x.run, 'controlWord: integer'); equal(x.binding().short49a, 0, 'invalid reached word retains prior decrement');
    equal(x.run(), 0, 'next explicit call observes retained0 without readiness');
    const y = fixture(); y.worldState.flags48a = 2; y.binding().short49c = 0; y.actual.controlWord = NaN;
    rejects(y.run, 'controlWord: integer'); equal(y.binding().short49c, 0, '49c readiness has no earlier store');
    for (const key of ['short49a', 'short49c'] as const) {
      const r = fixture(); r.worldState.flags48a = key === 'short49c' ? 2 : 0; r.binding()[key] = 1;
      Object.defineProperty(r.binding(), key, {writable: false}); r.actual.controlWord = NaN;
      rejects(r.run, `${key}: non-writable`); equal(r.binding()[key], 1, 'readonly decrement refused before word load');
      r.worldState.mode4a1 = 1; equal(r.run(), 0, 'unreached readonly destination admitted');
    }
    const r = fixture(); r.binding().short49a = 0; Object.defineProperty(r.binding(), 'short49a', {writable: false});
    equal(r.run(), 0, 'no write required for initial zero49a');
    const s = fixture(); s.worldState.flags48a = 2; s.binding().short49c = 0; s.actual.controlWord = 1;
    Object.defineProperty(s.binding(), 'short49c', {writable: false}); equal(s.run(), 0, 'blocked49c does not require writable counter');
    const missing = fixture(true); delete missing.initial.short49a; missing.bind(); rejects(missing.run, 'short49a: own data');
    let touched = false; const accessor = fixture();
    Object.defineProperty(accessor.actual, 'controlWord', {get() {touched = true; return 0;}}); accessor.binding().short49a = 1;
    rejects(accessor.run, 'controlWord: own data'); check(!touched, 'no scalar accessor invocation');
    equal(accessor.binding().short49a, 0, 'accessor refusal retains prior store');
  }
  {
    for (const value of [NaN, Infinity, -Infinity, -1, 256, 1.5]) {
      const x = fixture(); x.worldState.mode4a1 = value; rejects(x.run, 'mode4a1: integer');
      x.worldState.mode4a1 = 0; x.worldState.mode4a0 = value; rejects(x.run, 'mode4a0: integer');
      x.worldState.mode4a0 = 0; x.statusState.byte6fc = value; rejects(x.run, 'byte6fc: integer');
      x.statusState.byte6fc = 0; x.worldState.flags48a = value; rejects(x.run, 'flags48a: integer');
      x.worldState.flags48a = 0; x.binding().byte490 = value; rejects(x.run, 'byte490: integer');
      const initial = fixture(true); initial.initial.byte490 = value; rejects(initial.bind, 'byte490: integer');
    }
    for (const key of ['short49a', 'short49c'] as const) for (const value of [-32769, 32768, NaN, Infinity, 0.5]) {
      const x = fixture(); x.worldState.flags48a = key === 'short49c' ? 2 : 0; x.binding()[key] = value;
      rejects(x.run, `${key}: integer`); equal(x.binding()[key], value, 'invalid short not wrapped into range');
      const initial = fixture(true); initial.initial[key] = value; rejects(initial.bind, `${key}: integer`);
    }
    for (const value of [-1, 0x100000000, NaN, Infinity, 0.5]) {
      const x = fixture(); x.binding().short49a = 1; x.actual.controlWord = value;
      rejects(x.run, 'controlWord: integer'); equal(x.binding().short49a, 0, 'invalid u32 keeps decrement');
    }
    const zero = fixture(true); zero.initial.short49a = -0; zero.initial.short49c = -0; zero.initial.byte490 = -0; zero.bind();
    for (const key of ['short49a', 'short49c', 'byte490'] as const) equal(zero.binding()[key], 0, 'integer signed zero canonicalized');
  }
  {
    for (const owner of ['worldActor', 'statusActor', 'world', 'status', 'statusWorld'] as const) {
      const x = fixture(); x.hooks[owner] = () => ({}); rejects(x.run, 'owner changed'); equal(x.binding().short49a, 3, 'owner replacement before stores');
      x.hooks[owner] = () => Promise.resolve({}); rejects(x.run, 'owner changed');
    }
    const mismatch = fixture(true); mismatch.hooks.statusWorld = () => ({...mismatch.worldState});
    rejects(mismatch.bind, 'status world binding: owner changed');
    delete mismatch.hooks.statusWorld; mismatch.bind(); equal(mismatch.run(), 0, 'failed admission does not claim actual');
    const async = fixture(true); async.hooks.worldActor = () => Promise.resolve(async.actual);
    rejects(async.bind, 'synchronous actual owned record');
    const x = fixture(); rejects(x.bind, 'new symbol actor identity');
    const again = createSourceActorControlLifecycleRuntime(x.sources); rejects(() => again.bindActor(x.id, x.initial), 'already claimed');
    for (const read of [x.runtime.getActualActor, x.runtime.getActorBinding, x.runtime.getWorldBinding, x.runtime.getStatusBinding, x.runtime.updateActor])
      rejects(() => read(Symbol('unknown')), 'unknown/non-owned');
    for (const key of ['byte490', 'short49a', 'field49a', 'short49c', 'field49c', 'mode4a1', 'byte4a1',
      'mode4a0', 'byte4a0', 'flags48a', 'byte48a', 'byte6fc', 'flags5e0', 'word5e0']) {
      const atBind = fixture(true); Object.defineProperty(atBind.actual, key, {value: undefined}); rejects(atBind.bind, 'competing control-lifecycle storage');
      const after = fixture(); Object.defineProperty(after.actual, key, {get() {throw Error('shadow getter invoked');}});
      after.worldState.mode4a1 = 1; rejects(after.run, 'competing control-lifecycle storage');
    }
    const captured = fixture();
    captured.world.getActualActor = () => {throw Error('replacement called');};
    captured.sources.world = {} as typeof captured.world; captured.sources.status = {} as typeof captured.status;
    equal(captured.run(), 0, 'captured functions and receivers stay fixed');
  }
  {
    for (const pair of ['world-actual', 'status-actual', 'world-status'] as const) {
      const x = fixture(true);
      if (pair === 'world-actual') {x.hooks.world = () => x.actual; x.hooks.statusWorld = () => x.actual;}
      if (pair === 'status-actual') x.hooks.status = () => x.actual;
      if (pair === 'world-status') x.hooks.status = () => x.worldState;
      rejects(x.bind, 'source owner alias');
    }
    const actuals = new Map<symbol, ReturnType<typeof createRomActor>>();
    const worlds = new Map<symbol, SourceActorWorldMatrixBinding>(), statuses = new Map<symbol, Partial<SourceActorStatusTimersBinding>>();
    const sources = {
      world: {getActualActor: (id: symbol) => actuals.get(id)!, getActorBinding: (id: symbol) => worlds.get(id)!},
      status: {getActualActor: (id: symbol) => actuals.get(id)!, getActorBinding: (id: symbol) => statuses.get(id)!, getWorldBinding: (id: symbol) => worlds.get(id)!},
    };
    const runtime = createSourceActorControlLifecycleRuntime(sources), first = Symbol('first'), second = Symbol('second');
    actuals.set(first, createRomActor()); actuals.set(second, createRomActor());
    worlds.set(first, {mode4a1: 1} as SourceActorWorldMatrixBinding); worlds.set(second, worlds.get(first)!);
    statuses.set(first, {}); statuses.set(second, {}); runtime.bindActor(first, {byte490: 2, short49a: 1, short49c: 0});
    rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    worlds.set(second, {mode4a1: 1} as SourceActorWorldMatrixBinding); statuses.set(second, statuses.get(first)!);
    rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    statuses.set(second, runtime.getActorBinding(first) as object); rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    statuses.set(second, {}); runtime.bindActor(second, {}); equal(runtime.updateActor(second), 0, 'distinct actors own independent records');
    Object.assign(worlds.get(first)!, {mode4a1: 0, mode4a0: 0, flags48a: 0}); statuses.get(first)!.byte6fc = 0;
    rejects(() => runtime.updateActor(first), '8006a980');
    rejects(() => runtime.updateActor(first), 'known incomplete control transition');
    equal(runtime.updateActor(second), 0, 'incomplete actor does not block another actor in the same runtime');
  }
  {
    for (const nestedAction of ['update', 'bind'] as const) {
      const x = fixture(); let entered = false;
      x.hooks.statusWorld = () => {
        if (!entered) {entered = true; try {
          if (nestedAction === 'update') x.run(); else x.runtime.bindActor(Symbol('nested'), {});
        } catch { /* A source seam cannot swallow reentry and permit the outer mutation. */ }}
        return x.worldState;
      };
      rejects(x.run, 'caught same-runtime reentry'); equal(x.binding().short49a, 3, 'poison stops outer stores');
      delete x.hooks.statusWorld; equal(x.run(), 0, 'later independent call recovers');
    }
    const x = fixture(true); let entered = false;
    x.hooks.worldActor = () => {if (!entered) {entered = true; try {x.bind();} catch { /* caught */ }} return x.actual;};
    rejects(x.bind, 'caught same-runtime reentry'); delete x.hooks.worldActor; x.bind(); equal(x.run(), 0, 'poisoned bind never claims actor');
    const initial = fixture(true); let touched = false;
    Object.defineProperty(initial.initial, 'short49a', {get() {touched = true; return 1;}});
    rejects(initial.bind, 'short49a: own data'); check(!touched, 'initial accessor is not invoked');
    const accessorSources = fixture(true);
    Object.defineProperty(accessorSources.world, 'getActualActor', {get() {touched = true; return () => accessorSources.actual;}});
    rejects(() => createSourceActorControlLifecycleRuntime(accessorSources.sources), 'getActualActor: own data');
    check(!touched, 'source method accessor not invoked');
    const inherited = Object.create(accessorSources.sources) as SourceActorControlLifecycleSources;
    rejects(() => createSourceActorControlLifecycleRuntime(inherited), 'world: own data');
  }
  console.log('[actor-control-lifecycle-test] actual returned0 paths, raw-byte gates, signed16 domains, masks, retained refusal prefixes and incomplete-transition guard passed');
}
