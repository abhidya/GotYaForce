import {createRomActor, type RomActor} from './actor.js';
import {createSourceActorCeilingLifecycleRuntime, isSourceActorCeilingLifecycleRuntime} from './actor-ceiling-lifecycle.js';
import {createSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateSources} from './actor-matrix-update.js';
import {createSourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorTerrainGlobals} from './actor-terrain-query.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-ceiling-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, text: string): void {
  let message = ''; try {run();} catch (error) {message = String(error);}
  check(message.includes(text), `expected ${text}, got ${message || 'success'}`);
}
function absent(value: object, key: string): void {Reflect.deleteProperty(value, key);}
function readonly(value: object, key: string): void {Object.defineProperty(value, key, {writable: false});}
const F32_MAX = (2 - 2 ** -23) * 2 ** 127, TINY = 2 ** -149;

/** Explicit read-only owner seams isolate the bounded helper; the matrix and
 * stage-boundary runtimes are genuine. Unrequested source effects throw. The
 * attached-setup-animation tests exercise the fully composed real graph. */
function fixture(defer = false, wrap?: (actor: RomActor) => RomActor) {
  const raw = Object.assign(createRomActor(), {hoverOffset668: 2});
  raw.pos.y = 12; raw.savedGroundPos.y = 3; raw.yVel = 4;
  const actual = (wrap ? wrap(raw) : raw) as typeof raw;
  const id = Symbol('ceiling actor'), worldState = {} as SourceActorWorldMatrixBinding, mappingState = {};
  const statusState = {}, globals = {maskD2: 0, byteD9: 0}, terrain = {upper34: 10};
  const hooks: Record<string, (() => unknown) | undefined> = {};
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'captured world actor receiver/id');
      return (hooks.actual ? hooks.actual() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === world && key === id, 'captured world binding receiver/id');
      return (hooks.world ? hooks.world() : worldState) as SourceActorWorldMatrixBinding;},
    getMappingActor(key: symbol) {check(this === world && key === id, 'captured world mapping receiver/id');
      return (hooks.mapping ? hooks.mapping() : mappingState) as object;},
  };
  const unsupported = (): never => {throw Error('unrequested source effect');};
  const matrix = createSourceActorMatrixUpdateRuntime({
    world: {getActualActor: () => actual, getActorBinding: () => worldState,
      getWorldMatrix: unsupported, prepareActor: unsupported, rebuildActor: unsupported,
      copyActorMatrices: unsupported, bindCorrectedTraversalState: () => undefined},
    mapping: {getActor: () => mappingState},
    movement: {getActorBinding: () => ({}), getDescriptorBinding: unsupported},
    metadata: {getActorBinding: () => ({})}, globals,
  } as unknown as SourceActorMatrixUpdateSources);
  matrix.bindActor(id, {count1d96: 0, count1d97: 0, field1d60: 0, byte660: 0, link4a4: null});
  const stageBounds = createSourceActorStageBoundsRuntime({
    world: {getActualActor: () => actual, getActorBinding: () => worldState},
    status: {getActualActor: () => actual, getActorBinding: () => statusState},
    terrain: {getTerrainGlobals: () => terrain as SourceActorTerrainGlobals},
  });
  stageBounds.bindActor(id, {});
  const sources = {world, matrix, stageBounds}, runtime = createSourceActorCeilingLifecycleRuntime(sources);
  const bind = () => runtime.bindActor(id), run = () => runtime.updateActor(id);
  if (!defer) bind();
  return {id, raw, actual, worldState, mappingState, statusState, globals, terrain, world, matrix,
    stageBounds, sources, runtime, hooks, bind, run};
}

export function runActorCeilingLifecycleSelfTests(): void {
  {
    const x = fixture();
    equal(x.runtime.getActualActor(x.id), x.actual, 'canonical actual actor');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'canonical world binding');
    equal(x.runtime.getMappingActor(x.id), x.mappingState, 'canonical mapping actor');
    equal(x.runtime.getMatrixBinding(x.id), x.matrix.getActorBinding(x.id), 'canonical matrix binding');
    equal(x.runtime.getTerrainGlobals(), x.stageBounds.getTerrainGlobals(), 'shared actual terrain');
    equal(x.runtime.getMatchGlobals(), x.matrix.getGlobals(), 'shared actual match globals');
    check(Object.isFrozen(x.runtime) && isSourceActorCeilingLifecycleRuntime(x.runtime), 'genuine frozen runtime');
    check(!('getActorBinding' in x.runtime), 'no unnecessary shadow helper binding');
    for (const fake of [{...x.runtime}, Object.create(x.runtime), null, undefined, {}])
      check(!isSourceActorCeilingLifecycleRuntime(fake), 'brand cannot be copied');
    const actualKeys = Object.keys(x.actual).join(','), worldBefore = JSON.stringify(x.worldState);
    equal(x.run(), 1, 'complete admitted tail returns1'); equal(x.actual.yVel, 0, 'stores positive zero');
    equal(x.actual.pos.y, 8, 'upper minus actual hover'); equal(x.actual.savedGroundPos.y, 3, 'saved position untouched');
    equal(Object.keys(x.actual).join(','), actualKeys, 'no source fields fabricated');
    equal(JSON.stringify(x.worldState), worldBefore, 'world binding untouched');
    equal(x.run(), 0, 'next call equality gate returns0');
    x.actual.pos.y = 12; x.actual.savedGroundPos.y = 9; x.actual.yVel = 4;
    equal(x.run(), 1, 'savedY branch returns1'); equal(x.actual.pos.y, 9, 'orderedGT selects savedY');
    x.actual.pos.y = 12; x.actual.savedGroundPos.y = 8; x.actual.yVel = 4;
    equal(x.run(), 1, 'equality follows difference branch'); equal(x.actual.pos.y, 8, 'equal result');
    x.terrain.upper34 = 20; x.actual.hoverOffset668 = 3; x.actual.pos.y = 30; x.actual.yVel = 1;
    x.run(); equal(x.actual.pos.y, 17, 'stage/hover mutations consumed on later calls');
  }
  {
    // Every nonzero raw byte returns0, including high-bit values; no boolean
    // normalization, default value or downstream scalar validation is allowed.
    const g = fixture(); absent(g.actual, 'supportContact1db'); absent(g.actual, 'hoverOffset668');
    g.actual.pos.y = NaN; g.actual.yVel = NaN; g.terrain.upper34 = NaN;
    for (let byte = 1; byte < 256; byte++) {
      g.globals.byteD9 = byte; equal(g.run(), 0, 'all nonzero unsigned global bytes short circuit');
    }
    g.globals.byteD9 = 0; rejects(g.run, 'supportContact1db: own data');
    const s = fixture(); absent(s.actual, 'hoverOffset668'); s.actual.pos.y = NaN; s.actual.yVel = NaN;
    for (let byte = 1; byte < 256; byte++) {
      s.actual.supportContact1db = byte; equal(s.run(), 0, 'all nonzero signed support bytes short circuit');
    }
    s.actual.supportContact1db = 0; rejects(s.run, 'y: finite');
    const missing = fixture(true); absent(missing.globals, 'byteD9'); absent(missing.actual, 'hoverOffset668'); missing.bind();
    rejects(missing.run, 'byteD9: own data'); check(!('byteD9' in missing.globals), 'missing global never defaulted');
    const zero = fixture(); zero.globals.byteD9 = -0; zero.actual.supportContact1db = -0;
    equal(zero.run(), 1, 'integer negative zero has raw-zero meaning');
    for (const bad of [-1, 256, 0.5, NaN, Infinity]) {
      const x = fixture(); x.globals.byteD9 = bad; rejects(x.run, 'byteD9: raw byte'); equal(x.actual.yVel, 4, 'invalid global before writes');
      const y = fixture(); y.actual.supportContact1db = bad; rejects(y.run, 'supportContact1db: raw byte');
    }
  }
  {
    const x = fixture(); x.actual.yVel = NaN; x.actual.savedGroundPos.y = NaN;
    for (const y of [-20, 8]) {x.actual.pos.y = y; equal(x.run(), 0, 'lower/equal threshold skips velocity/savedY');}
    x.actual.pos.y = 12; rejects(x.run, 'yVel: finite');
    for (const velocity of [-100, -TINY, -0, 0]) {
      const v = fixture(); v.actual.yVel = velocity; v.actual.savedGroundPos.y = NaN;
      equal(v.run(), 0, 'notGT velocity skips savedY'); equal(v.actual.yVel, velocity, 'early return preserves velocity sign');
    }
    for (const value of [NaN, Infinity, -Infinity, 1.1]) {
      for (const key of ['position', 'hover', 'upper', 'velocity', 'saved'] as const) {
        const f = fixture();
        if (key === 'position') f.actual.pos.y = value;
        if (key === 'hover') f.actual.hoverOffset668 = value;
        if (key === 'upper') f.terrain.upper34 = value;
        if (key === 'velocity') f.actual.yVel = value;
        if (key === 'saved') f.actual.savedGroundPos.y = value;
        rejects(f.run, 'finite exact source float32');
        equal(f.actual.yVel, key === 'saved' ? 0 : key === 'velocity' ? value : 4, 'refusal preserves precise velocity prefix');
        equal(f.actual.pos.y, key === 'position' ? value : 12, 'no position write on invalid input');
      }
    }
  }
  {
    // fadds ties must round before the ordered threshold test.
    for (const [y, h, upper, expected] of [[2 ** 24, 1, 2 ** 24, 0],
      [2 ** 24 + 2, 1, 2 ** 24 + 2, 1], [1, 2 ** -24, 1, 0],
      [1 + 2 ** -23, 2 ** -24, 1 + 2 ** -23, 1]] as const) {
      const x = fixture(); x.actual.pos.y = y; x.actual.hoverOffset668 = h; x.terrain.upper34 = upper;
      equal(x.run(), expected, 'nearest-even addition gates');
    }
    const sub = fixture(); sub.actual.pos.y = 2 ** 25; sub.actual.hoverOffset668 = 1;
    sub.terrain.upper34 = 2 ** 24 + 4; sub.actual.savedGroundPos.y = 0; sub.run();
    equal(sub.actual.pos.y, 2 ** 24 + 4, 'subtraction halfway rounds to even upper word');
    const tiny = fixture(); tiny.actual.pos.y = 0; tiny.actual.hoverOffset668 = TINY; tiny.terrain.upper34 = 0;
    tiny.actual.savedGroundPos.y = -2 * TINY; tiny.actual.yVel = TINY;
    equal(tiny.run(), 1, 'subnormal positive gates preserved'); equal(tiny.actual.pos.y, -TINY, 'gradual underflow result preserved');
    equal(tiny.actual.yVel, 0, 'subnormal velocity cleared to positive zero');
    for (const [upper, hover, saved, expected] of [[-0, 0, 0, -0], [0, -0, -0, 0], [-0, -0, -0, 0], [0, 0, -0, 0]] as const) {
      const z = fixture(); z.actual.pos.y = 1; z.actual.hoverOffset668 = hover; z.terrain.upper34 = upper;
      z.actual.savedGroundPos.y = saved; z.run(); equal(z.actual.pos.y, expected, 'equal signed-zero selects difference, never Math.max');
    }
    const add = fixture(); add.actual.pos.y = F32_MAX; add.actual.hoverOffset668 = F32_MAX; add.terrain.upper34 = NaN;
    rejects(add.run, 'overflow float32'); equal(add.actual.yVel, 4, 'addition overflow before upper read and velocity store');
    const overflow = fixture(); overflow.actual.pos.y = -F32_MAX; overflow.actual.hoverOffset668 = F32_MAX;
    overflow.terrain.upper34 = -F32_MAX; overflow.actual.savedGroundPos.y = NaN;
    rejects(overflow.run, 'y: finite'); equal(overflow.actual.yVel, 0, 'savedY read occurs after velocity clear and before subtraction overflow');
    overflow.actual.yVel = 4; overflow.actual.savedGroundPos.y = 0;
    rejects(overflow.run, 'overflow float32'); equal(overflow.actual.yVel, 0, 'subtraction overflow retains velocity clear');
    equal(overflow.actual.pos.y, -F32_MAX, 'subtraction overflow has no position store');
  }
  {
    const velocity = fixture(); readonly(velocity.actual, 'yVel'); velocity.actual.savedGroundPos.y = NaN;
    rejects(velocity.run, 'yVel: non-writable'); equal(velocity.actual.yVel, 4, 'first readonly store fails before saved read');
    const position = fixture(); readonly(position.actual.pos, 'y'); rejects(position.run, 'y: non-writable');
    equal(position.actual.yVel, 0, 'readonly position retains prior velocity clear'); equal(position.actual.pos.y, 12, 'readonly position unchanged');
    const saved = fixture(); absent(saved.actual.savedGroundPos, 'y'); rejects(saved.run, 'y: own data');
    equal(saved.actual.yVel, 0, 'missing savedY retains source prefix');
    for (const field of ['byteD9', 'supportContact1db', 'hoverOffset668', 'upper34', 'yVel', 'savedY'] as const) {
      const x = fixture(); let touched = false;
      const owner = field === 'byteD9' ? x.globals : field === 'upper34' ? x.terrain : field === 'savedY' ? x.actual.savedGroundPos : x.actual;
      Object.defineProperty(owner, field === 'savedY' ? 'y' : field, {get() {touched = true; return 0;}, configurable: true});
      rejects(x.run, 'own data property'); check(!touched, 'source accessor rejected without invoking it');
      if (field === 'savedY') equal(x.actual.yVel, 0, 'saved accessor rejection retains prior store');
    }
    const unneeded = fixture(); unneeded.globals.byteD9 = 1; let touched = false;
    Object.defineProperty(unneeded.actual, 'supportContact1db', {get() {touched = true; throw Error('must not run');}});
    equal(unneeded.run(), 0, 'global short circuit skips unsupported source accessor'); check(!touched, 'unreached accessor not touched');
  }
  {
    // Owner disagreement cannot be hidden by an early scalar return.
    for (const name of ['actual', 'world', 'mapping']) {
      const x = fixture(); x.globals.byteD9 = 1; x.hooks[name] = () => ({});
      rejects(x.run, 'owner changed'); equal(x.actual.yVel, 4, 'owner replacement before writes');
    }
    const p = fixture(); p.actual.pos = {...p.actual.pos}; rejects(p.run, 'actual position: owner changed');
    const saved = fixture(); saved.actual.savedGroundPos = {...saved.actual.savedGroundPos};
    rejects(saved.run, 'actual saved position: owner changed'); equal(saved.actual.yVel, 0, 'saved vector check at reached load retains velocity clear');
    const gated = fixture(); gated.actual.savedGroundPos = {...gated.actual.savedGroundPos}; gated.globals.byteD9 = 1;
    equal(gated.run(), 0, 'unreached saved vector does not affect global return');
    const mismatch = fixture(true), otherMapping = {}; mismatch.hooks.mapping = () => otherMapping;
    rejects(mismatch.bind, 'matrix mapping: owner changed');
    mismatch.hooks.mapping = undefined; mismatch.bind(); equal(mismatch.run(), 1, 'failed binding did not claim actor');
    for (const key of ['matrix', 'stageBounds'] as const) {
      const x = fixture(); rejects(() => createSourceActorCeilingLifecycleRuntime({...x.sources, [key]: {...x.sources[key]}}), 'genuine source runtime');
      rejects(() => createSourceActorCeilingLifecycleRuntime({...x.sources, [key]: Object.create(x.sources[key])}), 'genuine source runtime');
    }
    const duplicate = fixture(); rejects(duplicate.bind, 'new symbol actor');
    const other = createSourceActorCeilingLifecycleRuntime(duplicate.sources);
    rejects(() => other.bindActor(duplicate.id), 'already claimed');
    rejects(() => duplicate.runtime.updateActor(Symbol('unbound')), 'unknown/non-owned');
    const asynchronous = fixture(); asynchronous.hooks.actual = () => Promise.resolve(asynchronous.actual);
    rejects(asynchronous.run, 'owner changed');
  }
  {
    for (const [name, key] of [['actual', 'airborneNoFloor1db'], ['actual', 'field668'], ['worldState', 'hoverOffset668'],
      ['mappingState', 'supportContact1db'], ['terrain', 'byteD9'], ['globals', 'upper34']] as const) {
      const x = fixture(true); let touched = false;
      Object.defineProperty(x[name], key, {get() {touched = true; return 0;}, configurable: true});
      rejects(x.bind, 'competing ceiling-lifecycle storage'); check(!touched, 'shadow alias accessor not invoked');
      absent(x[name], key); x.bind(); Object.defineProperty(x[name], key, {value: 0});
      rejects(x.run, 'competing ceiling-lifecycle storage'); equal(x.actual.yVel, 4, 'new alias refused before source writes');
    }
    const vectors = fixture(true); vectors.actual.savedGroundPos = vectors.actual.pos;
    rejects(vectors.bind, 'source owner alias');
    const captured = fixture(); captured.world.getActualActor = () => {throw Error('replacement must not execute');};
    captured.sources.world = {} as typeof captured.world; equal(captured.run(), 1, 'methods and original receiver captured');
    const reentry = fixture(); reentry.hooks.actual = () => {try {reentry.run();} catch {} return reentry.actual;};
    rejects(reentry.run, 'caught same-runtime reentry'); equal(reentry.actual.yVel, 4, 'caught reentry cannot allow later store');
    reentry.hooks.actual = undefined; equal(reentry.run(), 1, 'new independent call resets poison');
    const bindReentry = fixture(true); bindReentry.hooks.actual = () => {try {bindReentry.bind();} catch {} return bindReentry.actual;};
    rejects(bindReentry.bind, 'caught same-runtime reentry'); bindReentry.hooks.actual = undefined; bindReentry.bind();
    equal(bindReentry.run(), 1, 'failed nested admission never claims actor');
  }
  {
    // Hostile Proxy probes are OUTSIDE the admitted non-proxy source domain.
    // They test defensive store prefixes and reload ordering only, not RAM or
    // retail equivalence. Ordinary source accessors remain forbidden above.
    let enabled = false, fresh: (() => void) | undefined;
    const x = fixture(false, actor => new Proxy(actor, {set(target, key, value, receiver) {
      const result = Reflect.set(target, key, value, receiver);
      if (enabled && key === 'yVel') fresh?.();
      return result;
    }}));
    fresh = () => {x.actual.hoverOffset668 = 4; x.terrain.upper34 = 20;};
    enabled = true; equal(x.run(), 1, 'successful reload probe');
    equal(x.actual.pos.y, 16, 'fresh hover and upper reads after velocity store, not either cached value');
    x.raw.pos.y = 12; x.raw.yVel = 4; x.raw.hoverOffset668 = 2; x.terrain.upper34 = 10;
    fresh = () => {x.actual.savedGroundPos.y = 18;};
    equal(x.run(), 1, 'successful saved reload probe'); equal(x.actual.pos.y, 18, 'fresh savedY read after velocity store');
    let arm = false, nested: (() => void) | undefined;
    const r = fixture(false, actor => new Proxy(actor, {set(target, key, value, receiver) {
      const result = Reflect.set(target, key, value, receiver);
      if (arm && key === 'yVel') nested?.();
      return result;
    }}));
    nested = () => {try {r.run();} catch {}}; arm = true;
    rejects(r.run, 'caught same-runtime reentry'); equal(r.actual.yVel, 0, 'earlier real store survives caught setter reentry');
    equal(r.actual.pos.y, 12, 'poison blocks later position write');
  }
  console.log('[actor-ceiling-lifecycle-test] genuine owners,510 byte exits,f32 edges,source-ordered partial prefixes and complete0/1 returns passed');
}
