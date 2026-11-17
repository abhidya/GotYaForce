import {createSourceActorActionRequestRuntime, isSourceActorActionRequestRuntime,
  type SourceActorActionRequestBinding, type SourceActorActionRequestSources} from './actor-action-request.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-action-request-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes('[actor-action-request]') && error.includes(fragment) &&
    error.includes('offline execution aborted, prior writes/effects are not rolled back'),
  `expected action refusal ${fragment}, got ${error || 'success'}`);
}
/** Explicit owner seams isolate the helper, never source predicate effects. */
function fixture(defer = false) {
  const id = Symbol('action-request actor'), actual = createRomActor();
  const worldState: Partial<SourceActorWorldMatrixBinding> = {mode4a1: 0};
  const hooks: {actual?: () => unknown; world?: () => unknown} = {};
  const calls = {actual: 0, world: 0};
  const world = {
    getActualActor(key: symbol) {
      check(this === world && key === id, 'actual owner captured receiver/identity'); calls.actual++;
      return (hooks.actual ? hooks.actual() : actual) as typeof actual;
    },
    getActorBinding(key: symbol) {
      check(this === world && key === id, 'world owner captured receiver/identity'); calls.world++;
      return (hooks.world ? hooks.world() : worldState) as SourceActorWorldMatrixBinding;
    },
  };
  const sources = {world}, runtime = createSourceActorActionRequestRuntime(sources);
  const initial: Partial<SourceActorActionRequestBinding> = {byte7d2: 1, byte73c: 9};
  const bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  const ordinary = () => {runtime.getActorBinding(id).byte7d2 = 0; runtime.getActorBinding(id).byte73c = 0;};
  return {id, actual, worldState, hooks, calls, world, sources, runtime, initial, bind, ordinary,
    run: () => runtime.updateActor(id), binding: () => runtime.getActorBinding(id)};
}

export function runActorActionRequestSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getActualActor(x.id), x.actual, 'same canonical actor');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'same canonical4a1 owner');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'frozen runtime and sealed partial storage');
    equal(Object.keys(x.binding()).join(','), 'byte7d2,byte73c', 'only absent fields get copied storage');
    check(isSourceActorActionRequestRuntime(x.runtime), 'genuine runtime branded');
    for (const value of [{...x.runtime}, Object.create(x.runtime), {}, null, undefined, () => x.runtime])
      check(!isSourceActorActionRequestRuntime(value), 'runtime brand cannot be forged');
    const before = JSON.stringify(x.actual), worldBefore = JSON.stringify(x.worldState);
    equal(x.run(), undefined, 'source void return'); equal(x.binding().byte73c, 4, 'special request store4');
    equal(JSON.stringify(x.actual), before, 'actual scalar owners unchanged');
    equal(JSON.stringify(x.worldState), worldBefore, 'world owner unchanged');
    equal(x.initial.byte73c, 9, 'initial storage copied'); x.initial.byte73c = 77;
    equal(x.binding().byte73c, 4, 'initial no longer live');
    check(!Reflect.set(x.binding(), 'extra', 1), 'sealed storage cannot gain fields');
    equal(x.calls.world, 1, 'special branch does not resolve unreached world owner again');
  }
  {
    const x = fixture();
    // Independent arithmetic residue reference, all raw flag values. Poison
    // every field the selected branch must not consume.
    for (let raw = 0; raw <= 255; raw++) {
      const special = raw % 4 === 1;
      x.binding().byte7d2 = raw; x.binding().byte73c = special ? 99 : NaN;
      x.actual.statusWord5b4 = special ? 0 : NaN;
      x.actual.housekeeping73f = special ? NaN : 1; x.worldState.mode4a1 = NaN;
      equal(x.run(), undefined, 'all flags return at source-selected early branch');
      equal(x.binding().byte73c, special ? 4 : NaN, 'only residue1 writes4');
    }
    equal(x.calls.world, 1, 'all these flag branches leave world owner unread');
    for (let bit = 0; bit < 32; bit++) {
      const w = fixture(); w.actual.statusWord5b4 = 2 ** bit;
      w.actual.housekeeping73f = NaN; w.worldState.mode4a1 = NaN; w.binding().byte73c = NaN;
      equal(w.run(), undefined, 'all32 status-word bits');
      equal(w.binding().byte73c, bit === 4 ? NaN : 4, 'only bit4 inhibits store, old destination never loaded');
    }
    for (const value of [0, 0x10, 0xffffffef, 0xffffffff, 0x80000000, 0x80000010]) {
      const w = fixture(); w.actual.statusWord5b4 = value;
      equal(w.run(), undefined, 'combined unsigned word');
      equal(w.binding().byte73c, Math.floor(value / 16) % 2 === 0 ? 4 : 9, 'combined bit4 result');
    }
  }
  {
    const h = fixture(); h.binding().byte7d2 = 0; h.actual.statusWord5b4 = NaN;
    h.worldState.mode4a1 = NaN;
    for (let raw = 0; raw <= 255; raw++) {
      h.actual.housekeeping73f = raw; h.binding().byte73c = raw === 0 ? 1 : NaN;
      equal(h.run(), undefined, 'all housekeeping raw bytes, signed-zero equivalent');
      equal(h.binding().byte73c, raw === 0 ? 1 : NaN, 'housekeeping never mutates request');
    }
    equal(h.calls.world, 1, 'housekeeping/request early returns leave world owner unread');
    const r = fixture(); r.binding().byte7d2 = 0; r.actual.statusWord5b4 = NaN;
    r.actual.slot = NaN; r.worldState.mode4a1 = 1;
    for (let raw = 0; raw <= 255; raw++) {
      r.binding().byte73c = raw;
      if (raw === 0) rejects(r.run, '8005a34c reached unsupported source pointer508 load');
      else equal(r.run(), undefined, 'all nonzero request raw bytes return');
      equal(r.binding().byte73c, raw, 'request read does not rewrite byte');
    }
    equal(r.calls.world, 2, 'only request0 resolves world owner after admission');
    const m = fixture(); m.ordinary(); m.actual.slot = 128; m.actual.inputEdge5d4 = NaN;
    for (let raw = 0; raw <= 255; raw++) {
      m.worldState.mode4a1 = raw;
      rejects(m.run, raw === 0 ? '80010514(slot=-128)' : '8005a34c reached unsupported source pointer508 load');
      equal(m.binding().byte73c, 0, 'all mode bytes preserve request at boundary');
    }
    m.worldState.mode4a1 = 0;
    for (let raw = 0; raw <= 255; raw++) {
      m.actual.slot = raw;
      rejects(m.run, `80010514(slot=${raw < 128 ? raw : raw - 256})`);
    }
    equal(m.actual.slot, 255, 'sign extension never rewrites canonical raw slot');
    equal(m.actual.inputEdge5d4, NaN, 'no global result or input edge is fabricated');
  }
  {
    const x = fixture(true); delete x.initial.byte73c; x.bind(); x.actual.statusWord5b4 = 0x10;
    let touched = false;
    for (const key of ['housekeeping73f', 'slot', 'inputEdge5d4'])
      Object.defineProperty(x.actual, key, {get() {touched = true; throw Error('unreached scalar read');}});
    Object.defineProperty(x.worldState, 'mode4a1', {get() {touched = true; throw Error('unreached mode read');}});
    x.hooks.world = () => {throw Error('unreached world owner called');};
    equal(x.run(), undefined, 'inhibited special request needs no73c or later owner/scalar');
    equal(Object.keys(x.binding()).join(','), 'byte7d2', 'missing73c stays absent');
    x.actual.statusWord5b4 = 0; rejects(x.run, 'byte73c: own data property required');
    check(!touched, 'failed reached store precedes all later source reads');
    const y = fixture(true); delete y.initial.byte73c; y.bind();
    y.binding().byte7d2 = 0; y.actual.housekeeping73f = 255;
    y.hooks.world = () => {throw Error('unreached world owner');};
    equal(y.run(), undefined, 'nonzero73f needs no73c');
    y.actual.housekeeping73f = 0; rejects(y.run, 'byte73c: own data property required');
    const missing = fixture(true); delete missing.initial.byte7d2; delete missing.initial.byte73c; missing.bind();
    equal(Object.keys(missing.binding()).length, 0, 'empty partial storage remains empty');
    rejects(missing.run, 'byte7d2: own data property required');
    const set = fixture(); set.binding().byte73c = NaN;
    Object.defineProperty(set.actual, 'housekeeping73f', {get() {touched = true; return 0;}});
    set.hooks.world = () => {throw Error('unreached world owner');};
    equal(set.run(), undefined, 'special store ignores invalid old73c and all ordinary gates');
    equal(set.binding().byte73c, 4, 'special destination overwrites invalid old value'); check(!touched, 'getter not invoked');
  }
  {
    const x = fixture(); Object.defineProperty(x.binding(), 'byte73c', {writable: false});
    x.actual.statusWord5b4 = 0x10; equal(x.run(), undefined, 'unreached readonly store accepted');
    x.actual.statusWord5b4 = 0; rejects(x.run, 'byte73c: non-writable'); equal(x.binding().byte73c, 9, 'refused store preserves old request');
    x.binding().byte7d2 = 0; equal(x.run(), undefined, 'readonly nonzero request can be read');
    const r = fixture(); Object.defineProperty(r.binding(), 'byte7d2', {writable: false});
    Object.defineProperty(r.actual, 'statusWord5b4', {writable: false});
    equal(r.run(), undefined, 'source read-only input fields accepted'); equal(r.binding().byte73c, 4, 'writable destination used');
    // A later explicit refusal does not undo a completed previous source store.
    const retained = fixture(); retained.run(); retained.binding().byte7d2 = 0;
    retained.actual.housekeeping73f = NaN; rejects(retained.run, 'housekeeping73f: unsigned integer');
    equal(retained.binding().byte73c, 4, 'reached failure retains previous store');
    const b = fixture(); b.ordinary(); let touched = false;
    for (const key of ['inputEdge5d4', 'visibilityTargetcc', 'target508', 'pointer508', 'link4a4'])
      Object.defineProperty(b.actual, key, {get() {touched = true; throw Error('unsupported later scalar');}});
    Object.defineProperty(b.worldState, 'link4a4', {get() {touched = true; throw Error('later pointer');}});
    rejects(b.run, '8005a300 reached unsupported source call 80010514(slot=0)');
    b.worldState.mode4a1 = 1;
    Object.defineProperty(b.actual, 'slot', {get() {touched = true; throw Error('unreached signed slot');}});
    rejects(b.run, '8005a34c reached unsupported source pointer508 load');
    check(!touched, 'both exact boundaries precede later arguments, input and shadow pointers');
    equal(b.binding().byte73c, 0, 'no request2/3/5 manufactured');
  }
  {
    for (const key of ['byte7d2', 'byte73c'] as const) {
      for (const value of [-1, 256, NaN, Infinity, -Infinity, 0.5]) {
        const initial = fixture(true); initial.initial[key] = value; rejects(initial.bind, `${key}: unsigned integer`);
        const active = fixture(); active.binding()[key] = value;
        if (key === 'byte73c') active.binding().byte7d2 = 0;
        rejects(active.run, `${key}: unsigned integer`);
      }
      const initial = fixture(true); let touched = false;
      Object.defineProperty(initial.initial, key, {get() {touched = true; return 0;}});
      rejects(initial.bind, `${key}: own data`); check(!touched, 'initial accessor not invoked');
    }
    for (const key of ['housekeeping73f', 'slot'] as const) {
      for (const value of [-129, -128, -1, 256, NaN, Infinity, -Infinity, 0.5]) {
        const x = fixture(); x.ordinary(); x.actual[key] = value;
        rejects(x.run, `${key}: unsigned integer`);
      }
      const x = fixture(); x.ordinary(); let touched = false;
      Object.defineProperty(x.actual, key, {get() {touched = true; return 0;}});
      rejects(x.run, `${key}: own data`); check(!touched, 'actual accessor not invoked');
      const missing = fixture(); missing.ordinary(); Reflect.deleteProperty(missing.actual, key);
      rejects(missing.run, `${key}: own data`);
    }
    for (const value of [-1, 256, NaN, Infinity, 0.5]) {
      const x = fixture(); x.ordinary(); x.worldState.mode4a1 = value; rejects(x.run, 'mode4a1: unsigned integer');
    }
    const noMode = fixture(); noMode.ordinary(); delete noMode.worldState.mode4a1;
    rejects(noMode.run, 'mode4a1: own data');
    for (const value of [-1, 0x100000000, NaN, Infinity, -Infinity, 0.5]) {
      const x = fixture(); x.actual.statusWord5b4 = value; rejects(x.run, 'statusWord5b4: unsigned integer');
      equal(x.binding().byte73c, 9, 'invalid reached word precedes store');
    }
    const word = fixture(); let touched = false;
    Object.defineProperty(word.actual, 'statusWord5b4', {get() {touched = true; return 0;}});
    rejects(word.run, 'statusWord5b4: own data'); check(!touched, 'word accessor never invoked');
    const missingWord = fixture(); Reflect.deleteProperty(missingWord.actual, 'statusWord5b4');
    rejects(missingWord.run, 'statusWord5b4: own data');
    const zero = fixture(true); zero.initial.byte7d2 = -0; zero.initial.byte73c = -0; zero.bind();
    equal(zero.binding().byte7d2, 0, 'flag signed zero normalized'); equal(zero.binding().byte73c, 0, 'request signed zero normalized');
    zero.actual.slot = -0; zero.worldState.mode4a1 = -0; zero.actual.housekeeping73f = -0;
    rejects(zero.run, '80010514(slot=0)');
  }
  {
    const x = fixture(); rejects(x.bind, 'new symbol actor identity');
    const other = createSourceActorActionRequestRuntime(x.sources);
    rejects(() => other.bindActor(x.id, x.initial), 'actual actor already claimed');
    rejects(() => x.runtime.bindActor('wrong' as unknown as symbol, {}), 'new symbol actor identity');
    for (const method of [x.runtime.getActualActor, x.runtime.getWorldBinding, x.runtime.getActorBinding, x.runtime.updateActor])
      rejects(() => method(Symbol('unknown')), 'unknown/non-owned');
    for (const owner of ['actual', 'world'] as const) {
      const changed = fixture(); changed.ordinary();
      changed.hooks[owner] = () => ({}); rejects(changed.run, 'owner changed');
      changed.hooks[owner] = () => Promise.resolve({}); rejects(changed.run, 'owner changed');
      equal(changed.binding().byte73c, 0, 'changed owner precedes source store');
      const admission = fixture(true); admission.hooks[owner] = () => Promise.resolve({});
      rejects(admission.bind, 'synchronous actual owned record');
      delete admission.hooks[owner]; admission.bind(); equal(admission.run(), undefined, 'failed bind does not claim actual');
    }
    const lazy = fixture(); lazy.hooks.world = () => ({});
    equal(lazy.run(), undefined, 'unreached world owner not prematurely revalidated');
    lazy.binding().byte7d2 = 0; equal(lazy.run(), undefined, 'nonzero73c leaves world owner unread');
    lazy.binding().byte73c = 0; rejects(lazy.run, 'world binding: owner changed');
    const captured = fixture(); captured.world.getActualActor = () => {throw Error('replacement method called');};
    captured.world.getActorBinding = () => {throw Error('replacement binding method called');};
    captured.sources.world = {} as typeof captured.world;
    equal(captured.run(), undefined, 'source methods and receiver captured');
    captured.ordinary(); rejects(captured.run, '8005a300');
  }
  {
    const actualKeys = ['statusWord5b4', 'housekeeping73f', 'slot', 'inputEdge5d4'];
    const aliases = ['flags7d2', 'actionRequest73c', 'byte73f', 'word5b4', 'flags5b4',
      'word5d4', 'byte3e4', 'slot3e4', 'byte4a1'];
    const wrongOwnerKeys = {
      actual: ['byte7d2', 'byte73c', 'mode4a1', ...aliases],
      worldState: ['byte7d2', 'byte73c', ...actualKeys, ...aliases],
      initial: ['mode4a1', ...actualKeys, ...aliases],
    };
    for (const owner of ['actual', 'worldState', 'initial'] as const)
      for (const key of wrongOwnerKeys[owner]) for (const shape of ['data', 'accessor'] as const) {
        const before = fixture(true); let touched = false;
        const descriptor = shape === 'data' ? {value: undefined, configurable: true} :
          {get() {touched = true; throw Error('shadow getter invoked');}, configurable: true};
        Object.defineProperty(before[owner], key, descriptor);
        rejects(before.bind, `${key}: competing action-request storage`);
        check(!touched, 'wrong-owner admission checks descriptor presence only');
        Reflect.deleteProperty(before[owner], key); before.bind();
        equal(before.run(), undefined, 'rejected shadow admission did not claim actor');
        equal(before.binding().byte73c, 4, 'canonical source store after removing shadow');
        if (owner === 'initial') continue; // The initial input is copied, not retained.
        const after = fixture(); Object.defineProperty(after[owner], key, descriptor);
        rejects(after.run, `${key}: competing action-request storage`);
        check(!touched, 'late wrong-owner descriptor never invokes shadow accessor');
        equal(after.binding().byte73c, 9, 'late shadow refusal precedes source store');
        equal(after.calls.world, 1, 'shadow check inspects retained world without calling its owner');
        Reflect.deleteProperty(after[owner], key);
        equal(after.run(), undefined, 'canonical owner remains usable after shadow removal');
      }
    // Canonical-but-unreached cells need not be valid or present. Structural
    // exclusion must not turn into an eager source scalar load at admission.
    const lazy = fixture(true); delete lazy.initial.byte73c; lazy.actual.statusWord5b4 = 0x10;
    let touched = false;
    for (const key of ['housekeeping73f', 'slot', 'inputEdge5d4'])
      Object.defineProperty(lazy.actual, key, {get() {touched = true; throw Error('unreached canonical scalar');}});
    Object.defineProperty(lazy.worldState, 'mode4a1', {get() {touched = true; throw Error('unreached canonical mode');}});
    Object.defineProperty(lazy.worldState, 'unrelatedScalar', {get() {touched = true; throw Error('unrelated world scalar');}});
    Object.defineProperty(lazy.initial, 'unrelatedScalar', {get() {touched = true; throw Error('unrelated initial scalar');}});
    lazy.bind(); lazy.hooks.world = () => {throw Error('unreached world owner');};
    equal(lazy.run(), undefined, 'unreached canonical accessors remain lazy across admission/call');
    check(!touched, 'canonical and unrelated scalar accessors remain untouched');
    const absent = fixture(true); delete absent.initial.byte73c; absent.actual.statusWord5b4 = 0x10;
    for (const key of ['housekeeping73f', 'slot', 'inputEdge5d4']) Reflect.deleteProperty(absent.actual, key);
    delete absent.worldState.mode4a1; absent.bind();
    equal(absent.run(), undefined, 'canonical exclusion does not require unreachable cells');
    const copied = fixture();
    Object.defineProperty(copied.initial, 'statusWord5b4', {get() {touched = true; throw Error('discarded initial');}});
    equal(copied.run(), undefined, 'discarded initial does not become a retained owner');
    check(!touched, 'discarded initial is never read again');
  }
  {
    const aliased = fixture(true); aliased.hooks.world = () => aliased.actual;
    rejects(aliased.bind, 'source owner alias'); delete aliased.hooks.world; aliased.bind();
    equal(aliased.run(), undefined, 'alias admission failure does not claim actual');
    const actuals = new Map<symbol, ReturnType<typeof createRomActor>>();
    const worlds = new Map<symbol, SourceActorWorldMatrixBinding>();
    const sources = {world: {getActualActor: (id: symbol) => actuals.get(id)!,
      getActorBinding: (id: symbol) => worlds.get(id)!}};
    const runtime = createSourceActorActionRequestRuntime(sources), first = Symbol('first'), second = Symbol('second');
    actuals.set(first, createRomActor()); actuals.set(second, createRomActor());
    worlds.set(first, {mode4a1: 0} as SourceActorWorldMatrixBinding); worlds.set(second, worlds.get(first)!);
    runtime.bindActor(first, {byte7d2: 1, byte73c: 0});
    rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    worlds.set(second, runtime.getActorBinding(first) as SourceActorWorldMatrixBinding);
    rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    worlds.set(second, actuals.get(first)! as unknown as SourceActorWorldMatrixBinding);
    rejects(() => runtime.bindActor(second, {}), 'source owner alias');
    worlds.set(second, {mode4a1: 0} as SourceActorWorldMatrixBinding);
    runtime.bindActor(second, {byte7d2: 1, byte73c: 8});
    runtime.updateActor(first); runtime.updateActor(second);
    equal(runtime.getActorBinding(first).byte73c, 4, 'first independent actor store');
    equal(runtime.getActorBinding(second).byte73c, 4, 'second independent actor store');
    actuals.get(first)!.statusWord5b4 = NaN;
    rejects(() => runtime.updateActor(first), 'statusWord5b4: unsigned integer');
    equal(runtime.updateActor(second), undefined, 'independent actor not affected by refusal');
  }
  {
    for (const owner of ['actual', 'world'] as const) for (const action of ['update', 'bind'] as const) {
      const x = fixture(); if (owner === 'world') x.ordinary();
      let entered = false;
      x.hooks[owner] = () => {
        if (!entered) {entered = true; try {
          if (action === 'update') x.run(); else x.runtime.bindActor(Symbol('nested'), {});
        } catch { /* A seam cannot swallow reentry and permit outer effects. */ }}
        return owner === 'actual' ? x.actual : x.worldState;
      };
      rejects(x.run, 'caught same-runtime reentry');
      equal(x.binding().byte73c, owner === 'actual' ? 9 : 0, 'caught reentry poisons enclosing call');
      delete x.hooks[owner];
      if (owner === 'actual') {equal(x.run(), undefined, 'later independent call recovers'); equal(x.binding().byte73c, 4, 'recovered source store');}
      else rejects(x.run, '8005a300');
    }
    const binding = fixture(true); let entered = false;
    binding.hooks.actual = () => {if (!entered) {entered = true; try {binding.bind();} catch { /* caught */ }} return binding.actual;};
    rejects(binding.bind, 'caught same-runtime reentry'); delete binding.hooks.actual; binding.bind();
    equal(binding.run(), undefined, 'poisoned bind did not claim actual');
    const x = fixture(true); let touched = false;
    Object.defineProperty(x.world, 'getActualActor', {get() {touched = true; return () => x.actual;}});
    rejects(() => createSourceActorActionRequestRuntime(x.sources), 'getActualActor: own data');
    check(!touched, 'source method accessor not invoked');
    rejects(() => createSourceActorActionRequestRuntime(Object.create(x.sources) as SourceActorActionRequestSources), 'world: own data');
    const inherited = fixture(true); inherited.sources.world = Object.create(inherited.world) as typeof inherited.world;
    rejects(() => createSourceActorActionRequestRuntime(inherited.sources), 'getActualActor: own data');
    const nonMethod = fixture(true); Object.assign(nonMethod.world, {getActorBinding: 1});
    rejects(() => createSourceActorActionRequestRuntime(nonMethod.sources), 'own data-function required');
  }
  console.log('[actor-action-request-test] bounded actual8005a298: full raw-byte gates/slots,32 word bits, exact10514/508 boundaries, canonical owners, partial storage and reentry passed');
}
