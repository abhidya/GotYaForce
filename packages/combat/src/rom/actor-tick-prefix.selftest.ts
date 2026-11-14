import {createSourceActorInputPrefixRuntime} from './actor-input-prefix.js';
import {createSourceActorTickPrefixRuntime, isSourceActorTickPrefixClaimedActor,
  type SourceActorTickRawDistances, type SourceActorTickPrefixBinding} from './actor-tick-prefix.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {RomDriverBridge} from '../bridge.js';
import type {BorgRuntime} from '../types.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-tick-prefix-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
const raw = (targetDistance760 = 12, horizontalDistance764 = 10): SourceActorTickRawDistances =>
  ({boundary: 'externally-decoded-pre59068-raw', targetDistance760, horizontalDistance764});

/** Real5bab8 executes, with isolated actual owner records behind getters.
 * The attached graph separately supplies real world/status owners. No Proxy,
 * accessor execution or fake callee success is used to claim source ordering. */
function fixture(defer = false) {
  const id = Symbol('tick-prefix actor'), actual = Object.assign(createRomActor(), {collisionScale: 7});
  actual.modelScale = 2; actual.controlWord = 0x80100041;
  const borg = {downGaugeBase: 100, downGauge: 7, paramTier: {tier: 16, deltaAccum: 7, timerFrames: 3}};
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
  const gauges = createSourceActorGaugeScaleRuntime({world, status});
  gauges.bindActor(id, borg, {short7d6: 30, short7dc: 8, targetScaleB8: 2.5, byte7c9: 0, fieldC4: 6});
  const sources = {world, gauges}, runtime = createSourceActorTickPrefixRuntime(sources);
  const initial: Partial<SourceActorTickPrefixBinding> = {byte598: 23};
  const bind = () => runtime.bindActor(id, borg, initial);
  if (!defer) bind();
  const run = (epoch = 0, inputs = raw()) => runtime.ingestRawDistancesAndRun(id, epoch, inputs);
  const holdScale = (value: number) => {actual.modelScale = value; gauges.getActorBinding(id).targetScaleB8 = value;};
  return {id, actual, borg, state, scale, worldState, world, status, hooks, sources, gauges, runtime, bind, initial, run, holdScale,
    binding: () => runtime.getActorBinding(id)};
}

export function runActorTickPrefixSelfTests(): void {
  {
    const x = fixture();
    check(!Object.hasOwn(x.actual, 'targetDistance760') && !Object.hasOwn(x.actual, 'horizontalDistance764'), 'bind creates no default distances');
    equal(x.runtime.getActualActor(x.id), x.actual, 'actual actor identity'); equal(x.runtime.getActualBorg(x.id), x.borg, 'actual Borg identity');
    equal(Object.keys(x.binding()).join(','), 'byte598', 'only absent byte598 belongs to binding');
    check(isSourceActorTickPrefixClaimedActor(x.actual), 'successful bind permanently claims actual actor');
    check(!isSourceActorTickPrefixClaimedActor({...x.actual}), 'claim is not copied with properties');
    const observed: unknown[] = [];
    x.hooks.statusActor = () => {observed.push(x.actual.targetDistance760, x.actual.horizontalDistance764, x.actual.modelScale); return x.actual;};
    rejects(() => x.run(), '80059e58');
    equal(observed.join(','), '6,5,2', 'both source quotients precede real gauge owner reads, using pre-update B4');
    equal(x.actual.targetDistance760, 6, 'full3D quotient'); equal(x.actual.horizontalDistance764, 5, 'horizontalXZ quotient');
    equal(x.actual.modelScale, 2.049999952316284, 'genuine gauge interpolation'); equal(x.borg.paramTier.timerFrames, 2, 'genuine timer decrement');
    equal(x.scale.x, x.actual.modelScale, 'same world scale owner'); equal(x.actual.collisionScale, x.actual.modelScale, 'same actual collision scale');
    equal(x.actual.controlWord, 0x80000041, 'support clears only00100000 preserving high bits'); equal(x.binding().byte598, 0, 'support byte598 clear');
    equal(x.actual.dt, 1, 'no clock change'); equal(x.state.field7d8, 44, 'no copied or reset status clock');
    rejects(() => x.run(), 'epoch already consumed'); equal(x.actual.targetDistance760, 6, 'same epoch cannot divide again');
    equal(x.borg.paramTier.timerFrames, 2, 'same epoch cannot run gauge again');
    rejects(() => x.run(1, raw(20, 8)), '80059e58');
    equal(x.actual.targetDistance760, Math.fround(20 / 2.049999952316284), 'new epoch explicitly refreshes raw owner before divide');
  }
  {
    const x = fixture(); x.actual.targetDistance760 = 500; x.actual.horizontalDistance764 = 400;
    rejects(() => x.run(0, raw(18, 8)), '80059e58'); equal(x.actual.targetDistance760, 9, 'explicit raw replaces prior possibly normalized bridge value');
    const y = fixture(); const input = raw() as unknown as {boundary: string}; input.boundary = 'normalized';
    rejects(() => y.run(0, input as SourceActorTickRawDistances), 'raw boundary required');
    check(!Object.hasOwn(y.actual, 'targetDistance760'), 'missing assertion refuses before ingestion');
    rejects(() => y.run(), 'epoch already consumed');
    const z = fixture(); rejects(() => z.run(0, z.actual as unknown as SourceActorTickRawDistances), 'must not alias');
    rejects(() => z.run(), 'epoch already consumed');
  }
  {
    const x = fixture(); x.holdScale(2); const min = 2 ** -149;
    rejects(() => x.run(0, raw(3 * min, min)), '80059e58');
    equal(x.actual.targetDistance760, 2 * min, 'underflow halfway rounds odd significand upward to even');
    equal(x.actual.horizontalDistance764, 0, 'underflow halfway rounds even zero downward');
    const y = fixture(); y.holdScale(-2); rejects(() => y.run(0, raw(0, min)), '80059e58');
    equal(y.actual.targetDistance760, -0, 'zero numerator sign includes negative denominator');
    equal(y.actual.horizontalDistance764, -0, 'negative underflow retains signed zero');
    const z = fixture(); z.holdScale(-2); rejects(() => z.run(0, raw(-0, -4)), '80059e58');
    equal(z.actual.targetDistance760, 0, 'negative zero divided by negative is positive zero'); equal(z.actual.horizontalDistance764, 2, 'finite negative signs');
    const w = fixture(); w.holdScale(min); rejects(() => w.run(0, raw(2 * min, 3 * min)), '80059e58');
    equal(w.actual.targetDistance760, 2, 'subnormal dividend/divisor exact ratio'); equal(w.actual.horizontalDistance764, 3, 'second subnormal ratio');
    const v = fixture(); v.holdScale(3); rejects(() => v.run(0, raw(1, 2)), '80059e58');
    equal(v.actual.targetDistance760, 0.3333333432674408, 'nonterminating rational nearest-even');
    equal(v.actual.horizontalDistance764, 0.6666666865348816, 'independent rational quotient');
  }
  {
    const max = (2 - 2 ** -23) * 2 ** 127;
    const x = fixture(); x.holdScale(0.5); rejects(() => x.run(0, raw(2, max)), 'fdivs result');
    equal(x.actual.targetDistance760, 4, 'second quotient overflow keeps first SOURCE division store');
    equal(x.actual.horizontalDistance764, max, 'second overflow preserves raw ingestion value'); equal(x.borg.paramTier.timerFrames, 3, 'second overflow precedes gauge');
    rejects(() => x.run(), 'epoch already consumed'); equal(x.actual.targetDistance760, 4, 'failed epoch never redivides first result');
    const y = fixture(); y.holdScale(0.5); rejects(() => y.run(0, raw(max, 2)), 'fdivs result');
    equal(y.actual.targetDistance760, max, 'first overflow preserves raw input'); equal(y.actual.horizontalDistance764, 2, 'second source pair not reached');
    for (const zero of [0, -0]) {
      const z = fixture(); z.holdScale(zero); rejects(() => z.run(), 'zero divisor');
      equal(z.actual.targetDistance760, 12, 'zero denominator preserves ingested first raw distance'); equal(z.actual.horizontalDistance764, 10, 'zero denominator preserves second raw distance');
      equal(z.borg.paramTier.timerFrames, 3, 'zero denominator does not call gauge');
    }
    for (const invalid of [NaN, Infinity, -Infinity, 1.1]) {
      const z = fixture(); z.actual.modelScale = invalid; rejects(() => z.run(), 'modelScale: finite');
      equal(z.actual.targetDistance760, 12, 'invalid source B4 refuses after host ingestion');
      const w = fixture(); rejects(() => w.run(0, raw(invalid, 3)), 'targetDistance760: finite');
      check(!Object.hasOwn(w.actual, 'targetDistance760'), 'invalid raw first input does not establish destination');
    }
  }
  {
    // These are HOST ingestion destination failures, not witnesses of a source
    // division destination failure: stable writable cells stay writable during
    // the two arithmetic/store pairs. No Proxy/accessor trick is admitted.
    const x = fixture(); Object.defineProperty(x.actual, 'targetDistance760', {value: 17, writable: false});
    let readLater = false; const input = raw(); Object.defineProperty(input, 'horizontalDistance764', {get() {readLater = true; return 8;}});
    rejects(() => x.run(0, input), 'targetDistance760: non-writable'); equal(x.actual.targetDistance760, 17, 'first host destination preserved');
    check(!readLater, 'first host destination failure stops later input read'); rejects(() => x.run(), 'epoch already consumed');
    const y = fixture(); Object.defineProperty(y.actual, 'horizontalDistance764', {value: 19, writable: false});
    rejects(() => y.run(), 'horizontalDistance764: non-writable'); equal(y.actual.targetDistance760, 12, 'second host destination failure preserves first raw write, not quotient');
    equal(y.actual.horizontalDistance764, 19, 'second host destination preserved'); equal(y.borg.paramTier.timerFrames, 3, 'ingestion failure cannot run gauge');
    rejects(() => y.run(), 'epoch already consumed');
    const z = fixture(); const bad = raw(); Object.defineProperty(bad, 'horizontalDistance764', {get() {readLater = true; return 8;}});
    rejects(() => z.run(0, bad), 'horizontalDistance764: own data'); equal(z.actual.targetDistance760, 12, 'later input validation retains earlier host ingestion'); check(!readLater, 'input accessor never invoked');
    const w = fixture(); Object.preventExtensions(w.actual); rejects(() => w.run(), 'absent raw-input destination');
    check(!Object.hasOwn(w.actual, 'targetDistance760'), 'nonextensible actor gets no fabricated fields');
  }
  {
    const x = fixture(); x.borg.paramTier.timerFrames = 1;
    rejects(() => x.run(), '8006817c'); equal(x.actual.targetDistance760, 6, 'unsupported gauge expiry retains first quotient');
    equal(x.actual.horizontalDistance764, 5, 'unsupported gauge expiry retains second quotient'); equal(x.borg.paramTier.timerFrames, 0, 'real gauge expiry retains decrement');
    equal(x.actual.controlWord, 0x80100041, 'gauge failure precedes support clear'); equal(x.binding().byte598, 23, 'gauge failure leaves598');
    rejects(() => x.run(), 'epoch already consumed'); equal(x.borg.paramTier.timerFrames, 0, 'expired failed epoch cannot retry helper');
    const y = fixture(); y.gauges.getActorBinding(y.id).targetScaleB8 = Math.fround(2.02);
    rejects(() => y.run(), '80059e58'); equal(y.actual.modelScale, Math.fround(2.02), 'real gauge completion clamps');
    equal(y.borg.downGauge, 151, 'real reset uses post-clamp scale and separately rounded correction'); equal(y.actual.targetDistance760, 6, 'clamp never retroactively changes earlier ratio');
    const z = fixture(); Object.defineProperty(z.scale, 'y', {writable: false});
    rejects(() => z.run(), 'y: non-writable'); equal(z.scale.x, z.actual.modelScale, 'real gauge partial scale copy retained'); equal(z.scale.z, 7, 'gauge later copies absent');
    equal(z.actual.targetDistance760, 6, 'gauge destination failure retains source quotient'); equal(z.binding().byte598, 23, 'support not reached');
  }
  {
    const x = fixture(); Object.defineProperty(x.actual, 'controlWord', {writable: false});
    rejects(() => x.run(), 'controlWord: non-writable'); equal(x.actual.targetDistance760, 6, 'support destination failure retains ratios');
    equal(x.borg.paramTier.timerFrames, 2, 'support failure retains real gauge effects'); equal(x.binding().byte598, 23, 'control destination failure precedes598');
    const y = fixture(); Object.defineProperty(y.binding(), 'byte598', {writable: false});
    rejects(() => y.run(), 'byte598: non-writable'); equal(y.actual.controlWord, 0x80000041, '598 failure retains preceding source clear');
    const z = fixture(true); delete z.initial.byte598; z.bind(); rejects(() => z.run(), 'byte598: own data');
    equal(z.actual.controlWord, 0x80000041, 'missing598 discovered after genuine control clear');
    for (const contact of [1, 127, 128, 255]) {
      const w = fixture(); w.actual.supportContact1db = contact;
      Object.defineProperty(w.actual, 'linkedOwner1e4', {get() {throw Error('unsupported pointer read');}});
      rejects(() => w.run(), 'unsupported actual pointer1e4'); equal(w.binding().byte598, 0, 'nonzero support refuses after actual clears');
      equal(w.actual.controlWord, 0x80000041, 'all raw nonzero signed byte patterns keep control clear');
      check(!Object.hasOwn(w.binding(), 'linkedOwner1e4'), 'no invented support pointer binding');
    }
    const w = fixture(); w.actual.supportContact1db = -1; rejects(() => w.run(), 'supportContact1db: integer');
    equal(w.binding().byte598, 0, 'actual owner convention is rawu8, signed conversion happens after read');
    const v = fixture(); Object.defineProperty(v.actual, 'linkedOwner1e4', {get() {throw Error('unreached pointer');}});
    rejects(() => v.run(), '80059e58'); equal(v.binding().byte598, 0, 'zero support returns without inspecting unrelated pointer');
  }
  {
    for (const key of ['speedScalar760', 'speedScalar764', 'kfmSpeedScalar760', 'kfmSpeedScalar764', 'curTargetDist']) {
      const x = fixture(true); Object.defineProperty(x.actual, key, {value: undefined});
      rejects(x.bind, `legacy ${key}`); check(!isSourceActorTickPrefixClaimedActor(x.actual), 'failed alias bind does not claim actor');
      const y = fixture(); Object.defineProperty(y.actual, key, {value: 3});
      rejects(() => y.run(), `legacy ${key}`); check(!Object.hasOwn(y.actual, 'targetDistance760'), 'entry alias conflict precedes ingestion');
      rejects(() => y.run(), 'epoch already consumed'); check(isSourceActorTickPrefixClaimedActor(y.actual), 'entry refusal does not silently unclaim');
    }
    const x = fixture(true); let invoked = false; Object.defineProperty(x.initial, 'byte598', {get() {invoked = true; return 0;}});
    rejects(x.bind, 'own data'); check(!invoked && !isSourceActorTickPrefixClaimedActor(x.actual), 'bad initial accessor is never invoked or claimed');
    const y = fixture(); rejects(y.bind, 'new symbol');
    const second = createSourceActorTickPrefixRuntime(y.sources); rejects(() => second.bindActor(y.id, y.borg, {byte598: 0}), 'already claimed');
    const z = fixture(true); rejects(() => z.runtime.bindActor(z.id, {...z.borg}, {byte598: 0}), 'gauge Borg');
    check(!isSourceActorTickPrefixClaimedActor(z.actual), 'wrong Borg fails before claim');
    rejects(() => createSourceActorTickPrefixRuntime({...z.sources, gauges: {...z.gauges}}), 'genuine source runtime');
    rejects(() => createSourceActorTickPrefixRuntime({...z.sources, actorRates: {} as never}), 'actor rates require the genuine source runtime');
    rejects(() => createSourceActorTickPrefixRuntime({...z.sources, actorRates: undefined as never}), 'actor rates require the genuine source runtime');
    rejects(() => createSourceActorTickPrefixRuntime({...z.sources, ceiling: {} as never}), 'ceiling requires the genuine source runtime');
    rejects(() => createSourceActorTickPrefixRuntime({...z.sources, ceiling: undefined as never}), 'ceiling requires the genuine source runtime');
    const w = fixture(true); w.hooks.world = () => w.state; rejects(w.bind, 'source owner alias');
    const v = fixture(true); v.hooks.worldActor = () => Promise.resolve(v.actual); rejects(v.bind, 'synchronous actual owned record');
  }
  {
    const x = fixture(); x.hooks.worldActor = () => createRomActor(); rejects(() => x.run(), 'world actor');
    check(!Object.hasOwn(x.actual, 'targetDistance760'), 'changed actual owner refuses before ingestion');
    delete x.hooks.worldActor; rejects(() => x.run(), 'epoch already consumed');
    check(!Object.hasOwn(x.actual, 'targetDistance760'), 'repairing owner does not revive failed epoch');
    const y = fixture(); y.hooks.world = () => ({...y.worldState}); rejects(() => y.run(), 'world binding');
    const z = fixture(); z.borg.paramTier = {...z.borg.paramTier}; rejects(() => z.run(), 'paramTier owner changed');
    equal(z.actual.targetDistance760, 6, 'genuine gauge lazily catches tier owner replacement after division');
    const w = fixture(); w.hooks.statusActor = () => createRomActor(); rejects(() => w.run(), 'status actor');
    equal(w.actual.horizontalDistance764, 5, 'genuine gauge owner failure retains both quotients');
    const v = fixture(); v.world.getActualActor = () => {throw Error('mutated method');};
    v.world.getActorBinding = () => {throw Error('mutated method');}; v.sources.world = {} as typeof v.world;
    v.sources.gauges = {} as typeof v.gauges; rejects(() => v.run(), '80059e58');
    equal(v.actual.targetDistance760, 6, 'captured methods and receivers retain real owner/callee linkage');
  }
  {
    const x = fixture(); x.hooks.worldActor = () => {try {x.run(1);} catch {} return x.actual;};
    rejects(() => x.run(), 'caught same-runtime reentry'); check(!Object.hasOwn(x.actual, 'targetDistance760'), 'early caught reentry poisons before ingestion');
    delete x.hooks.worldActor; rejects(() => x.run(), 'epoch already consumed'); rejects(() => x.run(1), '80059e58');
    const y = fixture(); y.hooks.statusActor = () => {try {y.run(1);} catch {} return y.actual;};
    rejects(() => y.run(), 'caught same-runtime reentry'); equal(y.actual.targetDistance760, 6, 'late reentry retains division');
    // The gauge owner callback is outside prefix-runtime control; its real
    // effects complete before prefix poison is observed when it returns.
    equal(y.borg.paramTier.timerFrames, 2, 'late reentry retains genuine callee effects'); equal(y.binding().byte598, 23, 'poison blocks next support call');
    delete y.hooks.statusActor; rejects(() => y.run(), 'epoch already consumed');
    for (const epoch of [-1, 0.5, NaN, Infinity, Number.MAX_SAFE_INTEGER + 1]) {
      const z = fixture(); rejects(() => z.run(epoch), 'epoch: integer'); check(!Object.hasOwn(z.actual, 'targetDistance760'), 'invalid epoch has no effects');
    }
    const w = fixture(); rejects(() => w.run(2), '80059e58'); rejects(() => w.run(1), 'out of order');
    rejects(() => w.runtime.ingestRawDistancesAndRun(Symbol('other'), 3, raw()), 'unknown/non-owned');
  }
  {
    const x = fixture(), oldRoster: readonly BorgRuntime[] = [];
    // Invoke the actual bridge method with just the fields its refusal may
    // inspect. A claimed actor must fail before receiver OR actor mutation.
    const receiver = {actor: x.actual, arrowRoster: oldRoster} as unknown as RomDriverBridge;
    const attemptedRoster = [{} as BorgRuntime];
    rejects(() => RomDriverBridge.prototype.syncIn.call(receiver, attemptedRoster[0]!, attemptedRoster), 'before any legacy writes');
    equal((receiver as unknown as {arrowRoster: unknown}).arrowRoster, oldRoster, 'bridge guard precedes arrowRoster first write');
    equal(x.actual.controlWord, 0x80100041, 'bridge guard leaves actor unchanged before first epoch');
    rejects(() => x.run(), '80059e58');
    rejects(() => RomDriverBridge.prototype.syncIn.call(receiver, attemptedRoster[0]!, attemptedRoster), 'no fallback');
    equal(x.actual.targetDistance760, 6, 'bridge cannot overwrite or renormalize after partial source execution');
    equal(x.borg.paramTier.timerFrames, 2, 'bridge refusal does not duplicate gauge update');
  }
  {
    const x = fixture(true);
    const inputPrefix = createSourceActorInputPrefixRuntime({world: x.world, gauges: x.gauges});
    inputPrefix.bindActor(x.id, {});
    rejects(() => createSourceActorTickPrefixRuntime({...x.sources, inputPrefix: {...inputPrefix}}), 'genuine source runtime');
    const joined = createSourceActorTickPrefixRuntime({...x.sources, inputPrefix});
    joined.bindActor(x.id, x.borg, {byte598: 7});
    // Genuine optional input does not bypass the preceding absent stage helper.
    rejects(() => joined.ingestRawDistancesAndRun(x.id, 1, raw()), '80059e58');
    equal(x.actual.inputEdge5d4, 0, 'historical input value unchanged before reached input');
  }
  {
    const x = fixture(true), otherBorg = {...x.borg};
    const inputPrefix = createSourceActorInputPrefixRuntime({world: x.world,
      gauges: {getActualActor: () => x.actual, getActualBorg: () => otherBorg}});
    inputPrefix.bindActor(x.id, {});
    const joined = createSourceActorTickPrefixRuntime({...x.sources, inputPrefix});
    rejects(() => joined.bindActor(x.id, x.borg, {}), 'input Borg');
    check(!isSourceActorTickPrefixClaimedActor(x.actual), 'mismatched input owner never claims tick');
  }
  console.log('[actor-tick-prefix-test] explicit raw-input epochs, real gauge prefix, support clears and honest refusals passed');
}
