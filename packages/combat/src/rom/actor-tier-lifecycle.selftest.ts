import {createSourceActorTierLifecycleRuntime, isSourceActorTierLifecycleRuntime,
  type SourceActorTierLifecycleBinding, type SourceActorTierLifecycleSources} from './actor-tier-lifecycle.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorRateLifecycleRuntime} from './actor-rate-lifecycle.js';
import {createSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateSources} from './actor-matrix-update.js';
import {createSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshSources} from './actor-attribute-refresh.js';
import type {SourceActorStatusTimersBinding, SourceActorStatusBorgOwner} from './actor-status-timers.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';
import {createRomActor} from './actor.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-tier-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
const bits = new DataView(new ArrayBuffer(4));
function raw(value: number): number {bits.setFloat32(0, value, false); return bits.getUint32(0, false);}
function readonly(owner: object, key: string): void {Object.defineProperty(owner, key, {writable: false});}
function absent(owner: object, key: string): void {Reflect.deleteProperty(owner, key);}

/** Real gauge/rate/matrix runtimes and real4ac registry; explicit owner getters
 * isolate this helper. Unused world effects throw rather than report success.
 * The attached graph suite separately exercises genuine world/status owners. */
function fixture(defer = false, missingOutput?: 'targetScaleB8' | 'field1dd0', splitGauge?: 'world' | 'tier') {
  const id = Symbol('tier actor'), actual = createRomActor(); absent(actual, 'dt');
  actual.tierScale = 9;
  const worldState = {mode4a0: 0, mode4a1: 0, scale58: {x: 1, y: 1, z: 1}} as SourceActorWorldMatrixBinding;
  const mappingState = {timestep1dc8: 7} as SourceActorJointMappingHeader;
  const statusState: Partial<SourceActorStatusTimersBinding> = {byte6fc: 0, byte71c: 0, field1dcc: 1};
  const borg = {downGaugeBase: 100, downGauge: 7, paramTier: {tier: 16, deltaAccum: 6, timerFrames: 0},
    slowHitTimer: 0, hasteHitTimer: 0, slowAuraLevel: 0, hasteAuraLevel: 0, slowHitLevel: 0, hasteHitLevel: 0};
  const globals = {maskD2: 0, byte1f: 0}, movementState = {byte661: 0, field66c: 0, field670: 0};
  const hooks: Record<string, (() => unknown) | undefined> = {}, calls: Record<string, number> = {};
  const get = <T>(key: string, normal: () => T): T => {
    calls[key] = (calls[key] ?? 0) + 1;
    return (hooks[key] ? hooks[key]() : normal()) as T;
  };
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'captured world receiver/identity'); return get('actual', () => actual);},
    getActorBinding(key: symbol) {check(this === world && key === id, 'captured world receiver/identity'); return get('world', () => worldState);},
    getMappingActor(key: symbol) {check(this === world && key === id, 'captured world receiver/identity'); return get('mapping', () => mappingState);},
  };
  const mapping = {getActor: () => mappingState};
  const unused = (): never => {throw Error('unreached source effect must not execute');};
  const attributes = createSourceActorAttributeRefreshRuntime({
    world, mapping: {...mapping, getDescriptor: unused},
    movement: {getActualActor: () => actual, getActorBinding: () => movementState, updateActor: unused},
  } as SourceActorAttributeRefreshSources);
  const parameter = attributes.createParameterDescriptor({byteA3: 0});
  attributes.bindActor(id, {parameter4ac: parameter});
  const attributeState = attributes.getActorBinding(id);
  const attributeSource = {
    getActualActor(key: symbol) {check(this === attributeSource && key === id, 'captured attribute receiver'); return get('attributeActual', () => actual);},
    getActorBinding(key: symbol) {check(this === attributeSource && key === id, 'captured attribute receiver'); return get('attribute', () => attributeState);},
    getParameterDescriptor(key: symbol) {check(this === attributeSource, 'captured descriptor receiver');
      return get('descriptor', () => attributes.getParameterDescriptor(key));},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'captured status receiver'); return get('statusActual', () => actual);},
    getActorBinding(key: symbol) {check(this === status && key === id, 'captured status receiver'); return get('status', () => statusState);},
    getActualBorg(key: symbol) {check(this === status && key === id, 'captured status receiver');
      return get('borg', () => borg) as unknown as SourceActorStatusBorgOwner;},
    getWorldBinding: () => get('statusWorld', () => worldState),
    getMappingActor: () => get('statusMapping', () => mappingState),
    getAttributeBinding: () => get('statusAttribute', () => attributeState),
  };
  let corrected: unknown;
  const matrix = createSourceActorMatrixUpdateRuntime({
    world: {getActualActor: () => actual, getActorBinding: () => worldState,
      getWorldMatrix: unused, prepareActor: unused, rebuildActor: unused, copyActorMatrices: unused,
      bindCorrectedTraversalState(_key: symbol, state: object) {corrected = state;}},
    movement: {getActorBinding: () => movementState, getDescriptorBinding: unused},
    metadata: {getActorBinding: () => ({byte1d74: 0, byte1d75: 0, byte1d76: 0, byte1d77: 0,
      byte1d94: 0, byte1d95: 0, byte1d98: 0, byte1d99: 0, byte1d9b: 0})}, mapping, globals,
  } as SourceActorMatrixUpdateSources);
  matrix.bindActor(id, {count1d96: 0, count1d97: 0, field1d60: 0, byte660: 0, link4a4: null});
  equal(corrected, matrix.getActorBinding(id), 'matrix and world retain same corrected traversal state');
  const otherWorld = {...worldState, scale58: {...worldState.scale58}};
  const gaugeWorld = splitGauge === 'world' ? {getActualActor: () => actual, getActorBinding: () => otherWorld} : world;
  const gauges = createSourceActorGaugeScaleRuntime({world: gaugeWorld, status});
  gauges.bindActor(id, borg, missingOutput === 'targetScaleB8' ? {} : {targetScaleB8: 7});
  if (splitGauge === 'tier') borg.paramTier = {...borg.paramTier};
  const rates = createSourceActorRateLifecycleRuntime({world, mapping, status, matrix});
  rates.bindActor(id, missingOutput === 'field1dd0' ? {} : {field1dd0: 8});
  const sources: SourceActorTierLifecycleSources = {world, status, attributes: attributeSource, gauges, rates, matrix};
  const runtime = createSourceActorTierLifecycleRuntime(sources);
  const initial: Partial<SourceActorTierLifecycleBinding> = {signed74b: -9, signed74c: 15, signed74d: 17};
  const bind = () => runtime.bindActor(id, initial);
  if (!defer) bind();
  return {id, actual, borg, worldState, mappingState, statusState, globals, world, status, attributes, attributeSource,
    parameter, attributeState, gauges, rates, matrix, sources, hooks, calls, initial, runtime, bind,
    binding: () => runtime.getActorBinding(id), descriptor: () => attributes.getParameterDescriptor(parameter),
    run: () => runtime.refreshActor(id), delta: (n: number) => runtime.applyDelta127(id, n)};
}
function outputs(x: ReturnType<typeof fixture>): readonly number[] {
  return [x.gauges.getActorBinding(x.id).targetScaleB8!, x.rates.getActorBinding(x.id).field1dd0!, x.actual.tierScale];
}
function outputBits(x: ReturnType<typeof fixture>, expected: readonly number[], why: string): void {
  outputs(x).forEach((value, index) => equal(raw(value), expected[index], `${why} destination${index}`));
}
export function runActorTierLifecycleSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorTierLifecycleRuntime(x.runtime), 'genuine tier brand');
    for (const fake of [{...x.runtime}, Object.create(x.runtime), {}, null, undefined])
      check(!isSourceActorTierLifecycleRuntime(fake), 'brand cannot be copied or inherited');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'immutable methods and sealed partial binding');
    equal(Object.keys(x.binding()).join(','), 'signed74b,signed74c,signed74d', 'only absent74b/c/d get storage');
    equal(x.runtime.getActualActor(x.id), x.actual, 'same actual actor');
    equal(x.runtime.getActualBorg(x.id), x.borg, 'same actual Borg');
    equal(x.runtime.getTierOwner(x.id), x.borg.paramTier, 'same actual tier owner');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'same world');
    equal(x.runtime.getMappingActor(x.id), x.mappingState, 'same mapping');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'same status');
    equal(x.runtime.getAttributeBinding(x.id), x.attributeState, 'same4ac owner');
    equal(x.runtime.getGaugeBinding(x.id), x.gauges.getActorBinding(x.id), 'same B8 owner');
    equal(x.gauges.getWorldBinding(x.id), x.runtime.getWorldBinding(x.id), 'same retained gauge world');
    equal(x.gauges.getTierOwner(x.id), x.runtime.getTierOwner(x.id), 'same retained gauge tier');
    equal(x.runtime.getRateBinding(x.id), x.rates.getActorBinding(x.id), 'same1dd0 owner');
    equal(x.runtime.getMatrixBinding(x.id), x.matrix.getActorBinding(x.id), 'same matrix owner');
    equal(x.runtime.getMatchGlobals(), x.matrix.getGlobals(), 'same match global owner');
    x.initial.signed74c = 100; equal(x.binding().signed74c, 15, 'initial copy not a second live owner');
    equal(x.run(), undefined, 'refresh source void return');
    outputBits(x, [0x3f800000, 0x3f800000, 0x3f800000], 'neutral authenticated words');
    equal(x.borg.paramTier.tier, 16, 'refresh does not change canonical tier');
    const second = createSourceActorTierLifecycleRuntime(x.sources);
    rejects(() => second.bindActor(x.id, {}), 'actual actor already claimed');
    rejects(() => x.runtime.bindActor(x.id, {}), 'new symbol actor identity');
    rejects(() => x.runtime.refreshActor(Symbol()), 'unknown/non-owned');
    rejects(() => x.runtime.applyDelta127(Symbol(), 0), 'unknown/non-owned');
    check(!Reflect.set(x.binding(), 'tier', 16), 'cannot extend sealed tier cells');
    for (const key of ['gauges', 'rates', 'matrix'] as const)
      rejects(() => createSourceActorTierLifecycleRuntime({...x.sources, [key]: {...x.sources[key]}}), `${key} requires genuine`);
    for (const split of ['world', 'tier'] as const) {
      const y = fixture(true, undefined, split);
      rejects(y.bind, `gauge ${split}: owner changed`);
    }
  }
  {
    // Six independent literal bit vectors, never rounded extracted JSON.
    const expected = [
      [[0x3f4f5c29, 0x3f800000, 0x3f4f5c29], [0x3f800000, 0x3f800000, 0x3f800000], [0x3fb33333, 0x3f7ae148, 0x3fb33333]],
      [[0x3f4f5c29, 0x3f800000, 0x3f4f5c29], [0x3f800000, 0x3f800000, 0x3f800000], [0x3f99999a, 0x3f7ae148, 0x3f99999a]],
    ];
    const x = fixture();
    for (const selector of [0, 1]) for (const tier of [15, 16, 17]) {
      x.descriptor().byteA3 = selector; x.borg.paramTier.tier = tier; x.run();
      equal(x.binding().signed74b, tier, 'selected tier is stored');
      outputBits(x, expected[selector]![tier - 15]!, `selector${selector} row${tier}`);
    }
    equal(x.mappingState.timestep1dc8, 7, 'refresh never updates timestep');
    equal(x.borg.paramTier.deltaAccum, 6, 'refresh never changes accumulator');
    const replacement = x.attributes.createParameterDescriptor({byteA3: 0});
    x.attributeState.parameter4ac = replacement; x.run();
    outputBits(x, expected[0]![2]!, 'live4ac pointer changes selected row');
  }
  {
    const x = fixture(true); Object.keys(x.initial).forEach(key => absent(x.initial, key)); x.bind();
    x.attributeState.parameter4ac = null; x.borg.paramTier.tier = NaN;
    x.borg.paramTier = {...x.borg.paramTier};
    x.hooks.descriptor = () => {throw Error('unreached descriptor');};
    equal(x.run(), undefined, 'initial null4ac returns before tier owner/scalars/limits/descriptor');
    equal(Object.keys(x.binding()).length, 0, 'null path invents no74b/c/d');
    equal(outputs(x).join(','), '7,8,9', 'null path leaves all outputs');
    const y = fixture(); y.attributeState.parameter4ac = Symbol('unbound first pointer');
    y.binding().signed74d = NaN; rejects(y.run, 'signed74d: integer');
    equal(y.calls.descriptor ?? 0, 0, 'initial4ac is not dereferenced');
    y.binding().signed74d = 17; rejects(y.run, 'explicitly owned parameter descriptor');
    equal(y.binding().signed74b, 16, 'unknown second descriptor keeps74b store');
  }
  {
    for (const tier of [-128, -127, -1, 0, 14, 15, 16, 17, 18, 127]) {
      const x = fixture(); x.borg.paramTier.tier = tier; x.run();
      equal(x.binding().signed74b, tier < 15 ? 15 : tier > 17 ? 17 : tier, 'signed clamp to explicit limits');
      equal(x.borg.paramTier.tier, tier, 'refresh preserves unclamped canonical tier');
    }
    const x = fixture(true); delete x.initial.signed74c; x.bind(); x.borg.paramTier.tier = 127;
    x.run(); equal(x.binding().signed74b, 17, 'upper branch never reads absent lower');
    x.borg.paramTier.tier = 17; rejects(x.run, 'signed74c: own data');
    const y = fixture(); y.binding().signed74c = 17; y.binding().signed74d = 15;
    y.borg.paramTier.tier = 16; y.run(); equal(y.binding().signed74b, 15, 'inverted bounds upper branch wins');
    y.borg.paramTier.tier = 15; y.run(); equal(y.binding().signed74b, 17, 'upper equality reaches lower despite inversion');
    y.binding().signed74d = -128; y.binding().signed74c = NaN;
    rejects(y.run, '800682dc unsupported table row -128'); equal(y.binding().signed74b, -128, 'negative upper byte keeps signed representation');
    const z = fixture(); z.borg.paramTier.tier = -128; z.binding().signed74c = -127;
    rejects(z.run, 'table row -127'); equal(z.binding().signed74b, -127, 'negative lower byte is signed');
  }
  {
    for (const selector of [2, 127, 128, 255]) {
      const x = fixture(); x.descriptor().byteA3 = selector; x.binding().signed74d = 127; x.borg.paramTier.tier = 100;
      rejects(x.run, `800682d4 unsupported selector ${selector}`);
      equal(x.binding().signed74b, 100, 'selector refuses after74b, before row-range check');
      equal(outputs(x).join(','), '7,8,9', 'selector refusal has no float stores');
    }
    for (const row of [-128, -1, 0, 14, 18, 127]) {
      const x = fixture(); x.binding().signed74c = -128; x.binding().signed74d = 127; x.borg.paramTier.tier = row;
      rejects(x.run, `800682dc unsupported table row ${row}`);
      equal(x.binding().signed74b, row, 'unsupported row persists signed74b store');
      equal(outputs(x).join(','), '7,8,9', 'unsupported row does not fabricate table values');
    }
    const x = fixture(); x.attributeState.parameter4ac = x.attributes.createParameterDescriptor({});
    rejects(x.run, 'byteA3: own data'); equal(x.binding().signed74b, 16, 'absent selector failure follows74b');
    for (const selector of [-1, 256, 0.5, NaN, Infinity]) {
      const y = fixture(); y.descriptor().byteA3 = selector; rejects(y.run, 'byteA3: integer');
      equal(y.binding().signed74b, 16, 'live selector width validation follows74b');
    }
  }
  {
    for (const key of ['signed74b', 'targetScaleB8', 'field1dd0', 'tierScale'] as const) {
      const x = fixture(); x.borg.paramTier.tier = 17;
      const owner = key === 'signed74b' ? x.binding() : key === 'targetScaleB8' ? x.gauges.getActorBinding(x.id) :
        key === 'field1dd0' ? x.rates.getActorBinding(x.id) : x.actual;
      readonly(owner, key); rejects(x.run, `${key}: non-writable`);
      equal(x.binding().signed74b, key === 'signed74b' ? -9 : 17, 'clamped-store prefix');
      const expected = key === 'signed74b' || key === 'targetScaleB8' ? [7, 8, 9] :
        key === 'field1dd0' ? [Math.fround(1.4), 8, 9] : [Math.fround(1.4), Math.fround(0.98), 9];
      outputs(x).forEach((v, i) => equal(v, expected[i], `readonly ${key} retains float prefix${i}`));
    }
    for (const key of ['targetScaleB8', 'field1dd0'] as const) {
      const x = fixture(false, key); rejects(x.run, `${key}: own data`);
      equal(x.binding().signed74b, 16, 'missing output keeps74b');
      equal(x.actual.tierScale, 9, 'missing earlier output prevents5f8');
      if (key === 'field1dd0') equal(x.gauges.getActorBinding(x.id).targetScaleB8, 1, 'missing1dd0 retains B8');
    }
    const x = fixture(); absent(x.actual, 'tierScale'); rejects(x.run, 'tierScale: own data');
    equal(x.gauges.getActorBinding(x.id).targetScaleB8, 1, 'absent5f8 keeps B8');
    equal(x.rates.getActorBinding(x.id).field1dd0, 1, 'absent5f8 keeps1dd0');
    const y = fixture(); y.gauges.getActorBinding(y.id).targetScaleB8 = NaN;
    y.rates.getActorBinding(y.id).field1dd0 = Infinity; y.actual.tierScale = NaN; y.binding().signed74b = NaN;
    y.run(); outputBits(y, [0x3f800000, 0x3f800000, 0x3f800000], 'stores overwrite invalid old destination values');
  }
  {
    for (const gate of [1, 127, 128, 255]) {
      const x = fixture(true); Object.keys(x.initial).forEach(key => absent(x.initial, key)); x.bind();
      x.globals.byte1f = gate; x.borg.paramTier.tier = NaN; x.attributeState.parameter4ac = undefined as unknown as symbol;
      x.borg.paramTier = {...x.borg.paramTier};
      equal(x.delta(NaN), undefined, 'nonzero signed global byte gates before tier owner/delta/4ac');
      equal(outputs(x).join(','), '7,8,9', 'gated delta leaves rows untouched');
    }
    const cases = [
      [-128, 0, -127], [-127, -1, -127], [127, 1, 127], [16, -1, 15], [16, 0, 16], [16, 1, 17],
      [127, 2147483647, -127], [-128, -2147483648, 127], [0, -2147483648, -127], [0, 2147483647, 127],
      [-128, 2147483647, 127], [127, -2147483648, -127], [-1, 1, 0],
    ];
    for (const [start, delta, expected] of cases) {
      const x = fixture(); x.borg.paramTier.tier = start!; equal(x.delta(delta!), undefined, 'source delta void return');
      equal(x.borg.paramTier.tier, expected, 'signed32 wrapped add before signed127 clamp');
      equal(x.binding().signed74b, expected! < 15 ? 15 : expected! > 17 ? 17 : expected, 'real refresh called after canonical store');
      equal(x.borg.paramTier.deltaAccum, 6, 'delta127 does not alter accumulator');
      equal(x.borg.paramTier.timerFrames, 0, 'delta127 does not alter timer');
    }
    const x = fixture(); x.attributeState.parameter4ac = null; x.delta(1);
    equal(x.borg.paramTier.tier, 17, 'delta store remains with null4ac refresh');
    equal(x.binding().signed74b, -9, 'null4ac callee does not store74b');
    const y = fixture(); readonly(y.borg.paramTier, 'tier'); rejects(() => y.delta(0), 'tier: non-writable');
    equal(y.binding().signed74b, -9, 'readonly tier prevents callee');
    const z = fixture(); readonly(z.rates.getActorBinding(z.id), 'field1dd0');
    rejects(() => z.delta(1), 'field1dd0: non-writable'); equal(z.borg.paramTier.tier, 17, 'callee refusal retains canonical delta');
    equal(z.binding().signed74b, 17, 'callee refusal retains74b');
    equal(z.gauges.getActorBinding(z.id).targetScaleB8, Math.fround(1.4), 'callee refusal retains B8');
  }
  {
    for (const value of [-129, 128, 0.5, NaN, Infinity]) {
      const x = fixture(); x.borg.paramTier.tier = value; rejects(x.run, 'tier: integer');
      rejects(() => x.delta(0), 'tier: integer'); equal(x.binding().signed74b, -9, 'bad tier has no writes');
    }
    for (const key of ['signed74b', 'signed74c', 'signed74d'] as const) for (const value of [-129, 128, 0.5, NaN]) {
      const x = fixture(true); x.initial[key] = value; rejects(x.bind, `${key}: integer`);
      x.initial[key] = key === 'signed74b' ? 16 : key === 'signed74c' ? 15 : 17; x.bind();
    }
    for (const value of [-2147483649, 2147483648, 0.5, NaN, Infinity]) {
      const x = fixture(); rejects(() => x.delta(value), 'signedDelta: integer');
      equal(x.borg.paramTier.tier, 16, 'bad delta before canonical store');
    }
    for (const value of [-1, 256, 0.5, NaN, Infinity]) {
      const x = fixture(); x.globals.byte1f = value; x.borg.paramTier.tier = NaN;
      rejects(() => x.delta(NaN), 'byte1f: integer'); equal(x.binding().signed74b, -9, 'bad gate precedes tier/delta');
    }
    const x = fixture(); absent(x.globals, 'byte1f'); rejects(() => x.delta(0), 'byte1f: own data');
    x.run(); equal(x.binding().signed74b, 16, 'refresh has no global gate');
  }
  {
    for (const [owner, key] of [['actual', 'dt'], ['actual', 'tier'], ['borg', 'signed74c'],
      ['worldState', 'targetScaleB8'], ['mappingState', 'field1dd0'], ['statusState', 'tierScale'],
      ['globals', 'parameter4ac'], ['actual', 'byte1f'], ['actual', 'byteA3']] as const) {
      const x = fixture(true); let invoked = false;
      Object.defineProperty(x[owner], key, {get() {invoked = true; return 0;}, configurable: true});
      rejects(x.bind, 'competing tier-lifecycle'); check(!invoked, 'shadow detection never invokes getter');
      absent(x[owner], key); x.bind();
      Object.defineProperty(x[owner], key, {value: 0, configurable: true});
      rejects(x.run, 'competing tier-lifecycle'); equal(x.binding().signed74b, -9, 'new competing owner refuses before stores');
    }
    const x = fixture(true); Object.assign(x.initial, {tier: 16}); rejects(x.bind, 'tier: competing');
    absent(x.initial, 'tier'); x.bind();
    const y = fixture(); y.borg.paramTier = {...y.borg.paramTier}; rejects(y.run, 'actual Borg.paramTier: owner changed');
    for (const [hook, expected] of [['actual', 'world actor'], ['world', 'world binding'], ['mapping', 'world mapping'],
      ['statusActual', 'status actor'], ['borg', 'status Borg'], ['status', 'status binding'],
      ['statusWorld', 'status world'], ['statusMapping', 'status mapping'], ['statusAttribute', 'status attributes'],
      ['attributeActual', 'attribute actor'], ['attribute', 'attribute binding']] as const) {
      const z = fixture(); z.hooks[hook] = () => ({}); rejects(z.run, `${expected}: owner changed`);
      equal(z.binding().signed74b, -9, 'owner substitution before stores');
      z.hooks[hook] = () => Promise.resolve({}); rejects(z.run, `${expected}: owner changed`);
    }
    const z = fixture(); z.run(); z.hooks.descriptor = () => ({byteA3: 0});
    rejects(z.run, 'parameter4ac descriptor: owner changed');
    const w = fixture(); w.hooks.descriptor = () => w.actual;
    rejects(w.run, 'parameter4ac descriptor aliases'); equal(w.binding().signed74b, 16, 'descriptor alias refusal retains74b');
  }
  {
    const x = fixture();
    x.world.getActualActor = () => {throw Error('replacement world method');};
    x.status.getActorBinding = () => {throw Error('replacement status method');};
    x.attributeSource.getParameterDescriptor = () => {throw Error('replacement registry method');};
    x.sources.attributes = {...x.attributeSource}; x.run();
    equal(x.binding().signed74b, 16, 'captured methods and original receivers survive replacements');
    const y = fixture(); y.hooks.descriptor = () => {try {y.delta(1);} catch {} return y.descriptor();};
    rejects(y.run, 'caught same-runtime reentry'); equal(y.binding().signed74b, 16, 'reentry poison preserves earlier74b');
    equal(outputs(y).join(','), '7,8,9', 'reentry poison prevents later stores');
    y.hooks.descriptor = undefined; y.run(); equal(y.actual.tierScale, 1, 'fresh call after poison succeeds');
    const z = fixture(true); z.hooks.borg = () => {try {z.bind();} catch {} return z.borg;};
    rejects(z.bind, 'caught same-runtime reentry'); z.hooks.borg = undefined; z.bind();
    equal(z.runtime.getActualActor(z.id), z.actual, 'failed reentrant admission leaves claim available');
    const w = fixture(); w.hooks.attribute = () => {try {w.run();} catch {} return w.attributeState;};
    rejects(() => w.delta(1), 'caught same-runtime reentry'); equal(w.borg.paramTier.tier, 16, 'pre-store reentry stops delta');
  }
}
