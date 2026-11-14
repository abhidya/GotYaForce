import {createSourceActorGaugeScaleRuntime, isSourceActorGaugeScaleRuntime,
  type SourceActorGaugeScaleBinding} from './actor-gauge-scale.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-gauge-scale-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
/** Isolated owner records supply getters only. No stand-in callee effects:
 * actual status/world composition is covered by the attached graph selftest. */
function fixture(defer = false) {
  const id = Symbol('gauge actor'), actual = Object.assign(createRomActor(), {collisionScale: 9});
  const borg = {downGaugeBase: 100, downGauge: 7, paramTier: {tier: 16, deltaAccum: 7, timerFrames: 0}};
  const state = {field7d8: 44}, scale = {x: 9, y: 8, z: 7}, worldState = {scale58: scale};
  const hooks: {worldActor?: () => unknown; world?: () => unknown; statusActor?: () => unknown;
    borg?: () => unknown; status?: () => unknown} = {};
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'world actor receiver/identity');
      return (hooks.worldActor ? hooks.worldActor() : actual) as typeof actual;},
    getActorBinding(key: symbol) {check(this === world && key === id, 'world binding receiver/identity');
      return (hooks.world ? hooks.world() : worldState) as ReturnType<SourceActorWorldMatrixRuntime['getActorBinding']>;},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'status actor receiver/identity');
      return (hooks.statusActor ? hooks.statusActor() : actual) as typeof actual;},
    getActualBorg(key: symbol) {check(this === status && key === id, 'status Borg receiver/identity');
      return (hooks.borg ? hooks.borg() : borg) as unknown as ReturnType<SourceActorStatusTimersRuntime['getActualBorg']>;},
    getActorBinding(key: symbol) {check(this === status && key === id, 'status binding receiver/identity');
      return (hooks.status ? hooks.status() : state) as ReturnType<SourceActorStatusTimersRuntime['getActorBinding']>;},
  };
  const sources = {world, status}, runtime = createSourceActorGaugeScaleRuntime(sources);
  const initial: Partial<SourceActorGaugeScaleBinding> = {
    short7d6: -200, short7dc: 4, targetScaleB8: 1.5, byte7c9: 0, fieldC4: 6,
  };
  const bind = () => runtime.bindActor(id, borg, initial);
  if (!defer) bind();
  return {id, actual, borg, state, scale, worldState, world, status, sources, runtime, initial, bind, hooks,
    binding: () => runtime.getActorBinding(id), run: () => runtime.updateActor(id),
    down: () => runtime.resetDownGauge(id), secondary: () => runtime.resetSecondaryGauge(id)};
}

export function runActorGaugeScaleSelfTests(): void {
  {
    const x = fixture(); x.actual.modelScale = 1.5; x.down(); x.secondary();
    equal(x.borg.downGauge, 125, 'actual source6c6 reset'); equal(x.binding().short7dc, -250, 'actual source7dc reset');
    equal(x.borg.downGaugeBase, 100, 'base unchanged'); equal(x.state.field7d8, 44, 'status7d8 is not duplicated or reset');
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual actor'); equal(x.runtime.getActualBorg(x.id), x.borg, 'same actual Borg');
    equal(x.runtime.getStatusBinding(x.id), x.state, 'same existing status binding');
    check(isSourceActorGaugeScaleRuntime(x.runtime), 'concrete runtime provenance');
    check(!isSourceActorGaugeScaleRuntime({...x.runtime}), 'method-copy callback adapter has no provenance');
    check(!('modelScale' in x.binding()) && !('collisionScale' in x.binding()) && !('field7d8' in x.binding()), 'no copied existing owners');
    x.borg.downGaugeBase = 65535; x.actual.modelScale = 3; x.down(); equal(x.borg.downGauge, 65534, 'raw u16 base sign-extends');
    x.borg.downGaugeBase = 32768; x.actual.modelScale = 1; x.down(); equal(x.borg.downGauge, 32768, 'signed minimum preserves raw bits');
    x.borg.downGaugeBase = 32767; x.binding().short7d6 = 32767; x.actual.modelScale = 3;
    x.down(); x.secondary(); equal(x.borg.downGauge, 65534, 'raw sth final wrapping'); equal(x.binding().short7dc, -2, 'decoded sth final wrapping');
  }
  {
    const x = fixture(); x.borg.downGaugeBase = 3; x.actual.modelScale = 0.5; x.down();
    equal(x.borg.downGauge, 3, 'negative fractional correction truncates toward zero before base addition');
    x.borg.downGaugeBase = 21845; x.actual.modelScale = 7; x.down(); equal(x.borg.downGauge, 21844, 'correction65535 wraps to signed minus1');
    x.borg.downGaugeBase = 1; x.actual.modelScale = -4294967296; x.down(); equal(x.borg.downGauge, 1, 'signed32 minimum conversion admitted');
    x.actual.modelScale = 4294967296; rejects(x.down, 'fctiwz'); equal(x.borg.downGauge, 1, 'out-of-range conversion refuses before destination');
    x.actual.modelScale = Math.fround(3.4e38); x.borg.downGaugeBase = 32767;
    rejects(x.down, 'fmuls'); equal(x.borg.downGauge, 1, 'overflow refuses without reset');
    x.actual.modelScale = -0; x.borg.downGaugeBase = 100; x.down(); equal(x.borg.downGauge, 50, 'negative zero model is valid source float');
  }
  {
    const x = fixture(); x.borg.downGaugeBase = 36732; x.actual.modelScale = -63.16080856323242; x.down();
    equal(x.borg.downGauge, 43272, 'separate source fsubs/fmuls stages, not collapsed arithmetic43271');
    x.borg.downGaugeBase = 19404; x.actual.modelScale = -14085.1826171875; x.down();
    equal(x.borg.downGauge, 63356, 'final source fmuls rounding before conversion, not unrounded product63357');
  }
  {
    const x = fixture(); x.run();
    const first = 1.0499999523162842;
    equal(x.actual.modelScale, first, 'one source fadds of archived .05f'); equal(x.borg.downGauge, 7, 'noncompletion does not reset gauge');
    equal(x.scale.x, first, 'actual world58'); equal(x.scale.y, first, 'actual world5c'); equal(x.scale.z, first, 'actual world60');
    equal(x.actual.collisionScale, first, 'actual optional property c0'); equal(x.binding().fieldC4, first, 'explicit c4');
    equal(x.actual.sizeScale, 1, 'legacy sizeScale unchanged'); equal(x.borg.paramTier.tier, 16, 'no host tier approximation');
    x.actual.modelScale = 2; x.run(); equal(x.actual.modelScale, 1.9500000476837158, 'downward fsubs');
    x.actual.modelScale = Math.fround(1.98); x.binding().targetScaleB8 = 2; x.run();
    equal(x.actual.modelScale, 2, 'up overshoot clamps to target'); equal(x.borg.downGauge, 150, 'clamp invokes actual reset');
    x.actual.modelScale = Math.fround(2.02); x.borg.downGauge = 1; x.run();
    equal(x.actual.modelScale, 2, 'down overshoot clamps to target'); equal(x.borg.downGauge, 150, 'down completion reset');
    equal(x.scale.x, 2, 'completion copies post-reset model scale');
  }
  {
    const x = fixture(); x.borg.paramTier.timerFrames = 3; x.borg.paramTier.deltaAccum = NaN; x.borg.paramTier.tier = NaN;
    x.run(); equal(x.borg.paramTier.timerFrames, 2, 'actual positive750 decrements'); equal(x.actual.modelScale, 1.0499999523162842, 'nonexpiry continues scale');
    const y = fixture(); y.borg.paramTier.timerFrames = 1; y.actual.modelScale = NaN;
    rejects(y.run, '8006817c'); equal(y.borg.paramTier.timerFrames, 0, 'expiry retains true decrement prefix');
    equal(y.borg.paramTier.deltaAccum, 7, 'unsupported call prevents accumulator clear'); equal(y.borg.paramTier.tier, 16, 'no fabricated tier success');
    equal(y.scale.x, 9, 'expiry stops before scale copies'); check(Number.isNaN(y.actual.modelScale), 'expiry never reads invalid B4');
    const z = fixture(); z.borg.paramTier.timerFrames = 1; z.borg.paramTier.deltaAccum = 128;
    rejects(z.run, 'deltaAccum'); equal(z.borg.paramTier.timerFrames, 0, 'signed accumulator failure follows decrement');
    const w = fixture(); w.borg.paramTier.timerFrames = -32768; w.run(); equal(w.borg.paramTier.timerFrames, -32768, 'negative timer untouched');
    const v = fixture(); v.borg.paramTier.timerFrames = 32768; rejects(v.run, 'timerFrames'); equal(v.actual.modelScale, 1, '750 signed width checked before scale');
  }
  {
    const x = fixture(true); delete x.initial.byte7c9; delete x.initial.fieldC4;
    x.initial.targetScaleB8 = 1; x.bind(); delete (x.actual as {collisionScale?: number}).collisionScale;
    x.run(); equal(x.scale.x, 9, 'equal B8/B4 skips byte and every copy');
    const y = fixture(); y.binding().byte7c9 = 255; y.binding().fieldC4 = NaN;
    Object.defineProperty(y.actual, 'modelScale', {writable: false}); y.run();
    equal(y.scale.x, 9, 'signed nonzero byte gate skips model and destination checks');
    const z = fixture(); z.binding().targetScaleB8 = -0; z.actual.modelScale = 0; z.binding().byte7c9 = NaN;
    z.run(); equal(z.actual.modelScale, 0, 'fcmpu treats both signed zeros as equal'); equal(z.scale.x, 9, 'signed zero equality does not copy');
    const w = fixture(); w.binding().targetScaleB8 = NaN;
    let invoked = false; Object.defineProperty(w.actual, 'modelScale', {get() {invoked = true; return 1;}});
    rejects(w.run, 'targetScaleB8'); check(!invoked, 'B8 validates before B4 and never calls accessor');
  }
  {
    const x = fixture(); delete (x.actual as {collisionScale?: number}).collisionScale;
    rejects(x.run, 'collisionScale'); equal(x.actual.modelScale, 1.0499999523162842, 'missing c0 retains interpolation');
    equal(x.scale.z, x.actual.modelScale, 'missing c0 retains all preceding world stores'); equal(x.binding().fieldC4, 6, 'missing c0 prevents c4 store');
    const y = fixture(true); delete y.initial.fieldC4; y.bind(); rejects(y.run, 'fieldC4');
    equal(y.actual.collisionScale, y.actual.modelScale, 'missing c4 retains actual collision write');
    const z = fixture(); Object.defineProperty(z.scale, 'y', {writable: false}); rejects(z.run, 'y: non-writable');
    equal(z.scale.x, z.actual.modelScale, 'readonly5c retains58'); equal(z.scale.z, 7, 'readonly5c stops60'); equal(z.actual.collisionScale, 9, 'readonly5c stopsc0');
    const w = fixture(); w.actual.modelScale = Math.fround(1.98); w.binding().targetScaleB8 = 2;
    Object.defineProperty(w.borg, 'downGauge', {writable: false}); rejects(w.run, 'downGauge: non-writable');
    equal(w.actual.modelScale, 2, 'failed completion reset retains target clamp'); equal(w.scale.x, 9, 'reset failure precedes58');
    const v = fixture(); Object.defineProperty(v.actual, 'modelScale', {writable: false}); rejects(v.run, 'modelScale: non-writable'); equal(v.scale.x, 9, 'readonly B4 precedes copies');
  }
  {
    const x = fixture(true); delete x.initial.short7d6; x.bind(); x.actual.modelScale = NaN;
    rejects(x.secondary, 'short7d6'); equal(x.binding().short7dc, 4, 'missing signed base precedes model read');
    const y = fixture(true); delete y.initial.short7dc; y.bind(); y.actual.modelScale = 1.5;
    rejects(y.secondary, 'short7dc'); equal(y.borg.downGauge, 7, 'missing secondary destination never touches primary gauge');
    const z = fixture(); z.borg.downGaugeBase = -1; rejects(z.down, 'downGaugeBase'); equal(z.borg.downGauge, 7, 'host base requires raw u16 bits');
    const w = fixture(); w.actual.modelScale = 1.1; rejects(w.down, 'float32'); equal(w.borg.downGauge, 7, 'non-f32 scale refused');
  }
  {
    const x = fixture(); x.borg.paramTier = {...x.borg.paramTier}; rejects(x.run, 'paramTier owner changed');
    equal(x.actual.modelScale, 1, 'tier replacement refused before source timer'); x.down(); equal(x.borg.downGauge, 100, 'reset does not reach unused tier owner');
    const y = fixture(); y.worldState.scale58 = {...y.scale}; rejects(y.run, 'scale58 owner changed');
    equal(y.actual.modelScale, 1.0499999523162842, 'changed vector discovered at first copy, not eagerly'); equal(y.scale.x, 9, 'old vector untouched after owner change');
    const z = fixture(); z.hooks.status = () => ({...z.state}); rejects(z.down, 'status binding'); equal(z.borg.downGauge, 7, 'status identity substitution refused');
    const w = fixture(); w.hooks.worldActor = () => Promise.resolve(w.actual); rejects(w.run, 'world actor'); equal(w.actual.modelScale, 1, 'async actual owner refused');
    const v = fixture(); v.hooks.borg = () => ({...v.borg}); rejects(v.run, 'status Borg'); equal(v.actual.modelScale, 1, 'Borg clone refused');
  }
  {
    const x = fixture(); x.world.getActualActor = () => {throw Error('mutated method called');};
    x.status.getActorBinding = () => {throw Error('mutated method called');};
    x.sources.world = {} as typeof x.world; x.sources.status = {} as typeof x.status;
    x.run(); equal(x.actual.modelScale, 1.0499999523162842, 'captured methods and receivers stay fixed');
    const y = fixture(); y.hooks.worldActor = () => {try {y.runtime.resetDownGauge(y.id);} catch {} return y.actual;};
    rejects(y.run, 'caught same-runtime reentry'); equal(y.actual.modelScale, 1, 'caught reentry poisons before first source effect');
    const z = fixture(); z.hooks.world = () => {try {z.runtime.updateActor(z.id);} catch {} return z.worldState;};
    rejects(z.run, 'caught same-runtime reentry'); equal(z.actual.modelScale, 1.0499999523162842, 'late reentry keeps interpolation'); equal(z.scale.x, 9, 'late poison prevents58');
    delete z.hooks.world; z.run(); equal(z.actual.modelScale, 1.0999999046325684, 'new outer call recovers after poisoned failure');
  }
  {
    const x = fixture(); rejects(x.bind, 'new symbol'); rejects(() => x.runtime.updateActor(Symbol('other')), 'unknown/non-owned');
    const y = fixture(true); y.hooks.statusActor = () => createRomActor(); rejects(y.bind, 'status actor');
    const z = fixture(true); (z.borg as unknown as {paramTier: object}).paramTier = z.scale;
    rejects(z.bind, 'source owner alias');
    const w = fixture(true); let readAccessor = false;
    Object.defineProperty(w.initial, 'byte7c9', {get() {readAccessor = true; return 0;}});
    rejects(w.bind, 'own data property'); check(!readAccessor, 'initial accessor is not executed');
  }
  console.log('[actor-gauge-scale-test] actual gauge reset pair and bounded scale lifecycle passed');
}
