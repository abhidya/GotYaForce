import {createSourceActorRateLifecycleRuntime, isSourceActorRateLifecycleRuntime,
  type SourceActorRateLifecycleBinding, type SourceActorRateLifecycleSources} from './actor-rate-lifecycle.js';
import {createSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateSources,
  type SourceActorMatrixUpdateBinding} from './actor-matrix-update.js';
import {createRomActor} from './actor.js';
import type {SourceActorStatusBorgOwner, SourceActorStatusTimersBinding} from './actor-status-timers.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-rate-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes('[actor-rate-lifecycle]') && error.includes(fragment) &&
    error.includes('offline execution aborted, prior writes/effects are not rolled back'),
  `expected rate refusal ${fragment}, got ${error || 'success'}`);
}
const bits = new DataView(new ArrayBuffer(4));
function value(raw: number): number {bits.setUint32(0, raw, false); return bits.getFloat32(0, false);}
function raw(f: number): number {bits.setFloat32(0, f, false); return bits.getUint32(0, false);}
function readonly(record: object, key: string): void {Object.defineProperty(record, key, {writable: false});}
function absent(record: object, key: string): void {Reflect.deleteProperty(record, key);}

/** Explicit owner seams isolate the helper. No adapter supplies source effects.
 * The optional matrix runtime's binding is genuine; its unused effects throw. */
function fixture(defer = false, withMatrix = false) {
  const make = () => {
    const actual = createRomActor(); absent(actual, 'dt');
    actual.aimRateScale = 9; actual.timescale = 8; actual.controlWord = 0;
    const worldState = {mode4a0: 0, mode4a1: 0} as SourceActorWorldMatrixBinding;
    const mappingState = {timestep1dc8: 7} as SourceActorJointMappingHeader;
    const statusState: Partial<SourceActorStatusTimersBinding> = {byte6fc: 0, byte71c: 0, field1dcc: 0.5};
    const borg = {slowHitTimer: 0, hasteHitTimer: 0, slowAuraLevel: 0,
      hasteAuraLevel: 0, slowHitLevel: 0, hasteHitLevel: 0} as SourceActorStatusBorgOwner;
    return {id: Symbol('rate actor'), actual, worldState, mappingState, statusState, borg,
      corrected: undefined as SourceActorMatrixUpdateBinding | undefined};
  };
  const current = make(), actors = new Map([[current.id, current]]);
  const lookup = (id: symbol) => {const e = actors.get(id); check(e !== undefined, 'fixture identity is owned'); return e!;};
  const hooks: Record<string, ((id: symbol) => unknown) | undefined> = {};
  const calls: Record<string, number> = {};
  const get = (key: string, id: symbol, normal: () => unknown): unknown => {
    calls[key] = (calls[key] ?? 0) + 1; return hooks[key]?.(id) ?? normal();
  };
  const world = {
    getActualActor(id: symbol) {check(this === world, 'captured world receiver'); return get('actual', id, () => lookup(id).actual) as typeof current.actual;},
    getActorBinding(id: symbol) {check(this === world, 'captured world receiver'); return get('world', id, () => lookup(id).worldState) as SourceActorWorldMatrixBinding;},
    getMappingActor(id: symbol) {check(this === world, 'captured world receiver'); return get('worldMapping', id, () => lookup(id).mappingState) as object;},
  };
  const mapping = {
    getActor(id: symbol) {check(this === mapping, 'captured mapping receiver'); return get('mapping', id, () => lookup(id).mappingState) as SourceActorJointMappingHeader;},
  };
  const status = {
    getActualActor(id: symbol) {check(this === status, 'captured status receiver'); return get('statusActual', id, () => lookup(id).actual) as typeof current.actual;},
    getActorBinding(id: symbol) {check(this === status, 'captured status receiver'); return get('status', id, () => lookup(id).statusState) as Partial<SourceActorStatusTimersBinding>;},
    getWorldBinding(id: symbol) {check(this === status, 'captured status receiver'); return get('statusWorld', id, () => lookup(id).worldState) as object;},
    getMappingActor(id: symbol) {check(this === status, 'captured status receiver'); return get('statusMapping', id, () => lookup(id).mappingState) as object;},
    getActualBorg(id: symbol) {check(this === status, 'captured status receiver'); return get('borg', id, () => lookup(id).borg) as SourceActorStatusBorgOwner;},
  };
  const unsupported = (): never => {throw Error('unreached matrix effect must not execute');};
  const matrix = withMatrix ? createSourceActorMatrixUpdateRuntime({
    world: {...world, getWorldMatrix: unsupported, prepareActor: unsupported, rebuildActor: unsupported,
      copyActorMatrices: unsupported,
      bindCorrectedTraversalState(id, state) {lookup(id).corrected = state as SourceActorMatrixUpdateBinding;},
      // Methods of this independent test owner use their own captured receiver.
      getActualActor(id) {return lookup(id).actual;}, getActorBinding(id) {return lookup(id).worldState;},
    },
    mapping,
    movement: {getActorBinding: () => ({byte661: 0, field66c: 0, field670: 0}), getDescriptorBinding: unsupported},
    metadata: {getActorBinding: () => ({byte1d74: 0, byte1d75: 0, byte1d76: 0, byte1d77: 0,
      byte1d94: 0, byte1d95: 0, byte1d98: 0, byte1d99: 0, byte1d9b: 0})}, globals: {maskD2: 0},
  } as SourceActorMatrixUpdateSources) : undefined;
  const sources: SourceActorRateLifecycleSources = {world, mapping, status, ...(matrix === undefined ? {} : {matrix})};
  const runtime = createSourceActorRateLifecycleRuntime(sources);
  const initial: Partial<SourceActorRateLifecycleBinding> = {field1dd0: 2};
  const bindOne = (e: typeof current, seed: Partial<SourceActorRateLifecycleBinding>) => {
    matrix?.bindActor(e.id, {count1d96: 0, count1d97: 0, field1d60: 0, byte660: 0, link4a4: null});
    runtime.bindActor(e.id, seed);
  };
  const bind = () => bindOne(current, initial);
  if (!defer) bind();
  const peer = () => {const e = make(); actors.set(e.id, e); bindOne(e, {field1dd0: 1}); return e;};
  return {...current, initial, sources, runtime, world, status, mapping, matrix, hooks, calls, bind, peer,
    binding: () => runtime.getActorBinding(current.id), run: () => runtime.updateActor(current.id)};
}

export function runActorRateLifecycleSelfTests(): void {
  {
    const x = fixture();
    check(isSourceActorRateLifecycleRuntime(x.runtime), 'genuine runtime brand');
    for (const fake of [{...x.runtime}, Object.create(x.runtime), {}, null, undefined])
      check(!isSourceActorRateLifecycleRuntime(fake), 'brand is not structurally forgeable');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'runtime frozen and partial storage sealed');
    equal(Object.keys(x.binding()).join(','), 'field1dd0', 'only missing1dd0 gets new storage');
    equal(x.runtime.getActualActor(x.id), x.actual, 'retained actual actor');
    equal(x.runtime.getActualBorg(x.id), x.borg, 'retained actual Borg');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'retained world owner');
    equal(x.runtime.getMappingActor(x.id), x.mappingState, 'retained mapping owner');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'retained status owner');
    equal(x.runtime.getMatrixBinding(x.id), undefined, 'no implicit matrix owner');
    equal(x.run(), undefined, 'normal source void return');
    equal(x.actual.aimRateScale, 1, 'normal source768'); equal(x.actual.timescale, 1, 'normal source5f4');
    equal(x.mappingState.timestep1dc8, 1, 'normal source1dc8 = 2*(.5*1)');
    x.initial.field1dd0 = 99; equal(x.binding().field1dd0, 2, 'initial copied, not live');
    check(!Reflect.set(x.binding(), 'extra', 3), 'cannot add arbitrary missing fields');
    const second = createSourceActorRateLifecycleRuntime(x.sources);
    rejects(() => second.bindActor(x.id, {field1dd0: 2}), 'actual actor already claimed');
    rejects(() => x.runtime.bindActor(x.id, {}), 'new symbol actor identity');
    rejects(() => x.runtime.updateActor(Symbol()), 'unknown/non-owned');
  }
  {
    // Nonzero4a1 has no timer/status/index/1dd0 reads and overwrites old values.
    for (const mode of [1, 128, 255]) {
      const x = fixture(true); delete x.initial.field1dd0; x.bind();
      x.worldState.mode4a1 = mode; x.worldState.mode4a0 = NaN;
      x.actual.aimRateScale = NaN; x.actual.timescale = NaN; x.mappingState.timestep1dc8 = NaN;
      x.hooks.borg = x.hooks.status = () => {throw Error('unreached owner');};
      x.run(); equal(x.mappingState.timestep1dc8, 1, 'nonzero4a1 first1dc8=1');
      equal(x.actual.timescale, 1, 'nonzero4a1 second5f4=1'); equal(x.actual.aimRateScale, 1, 'nonzero4a1 third768=1');
      equal(Object.keys(x.binding()).length, 0, 'no default1dd0');
    }
    for (const destination of ['timestep1dc8', 'timescale', 'aimRateScale']) {
      const x = fixture(); x.worldState.mode4a1 = 1;
      readonly(destination === 'timestep1dc8' ? x.mappingState : x.actual, destination);
      rejects(x.run, `${destination}: non-writable`);
      equal(x.mappingState.timestep1dc8, destination === 'timestep1dc8' ? 7 : 1, 'ordered fast1dc8 prefix');
      equal(x.actual.timescale, destination === 'aimRateScale' ? 1 : 8, 'ordered fast5f4 prefix');
      equal(x.actual.aimRateScale, 9, 'failed/untouched fast768 retained');
    }
  }
  {
    for (const start of [-32768, -32767, -1, 0, 1, 2, 32767]) {
      const x = fixture(); x.borg.slowHitTimer = x.borg.hasteHitTimer = start;
      x.borg.slowHitLevel = x.borg.hasteHitLevel = 1;
      x.run();
      const next = start === 0 ? 0 : start === -32768 ? 32767 : start - 1;
      equal(x.borg.slowHitTimer, next, 'signed710 decrement/wrap');
      equal(x.borg.hasteHitTimer, next, 'signed712 decrement/wrap');
      equal(x.borg.slowHitLevel, start !== 0 && next <= 0 ? 0 : 1, 'slow expiry uses wrapped signed result');
      equal(x.borg.hasteHitLevel, start !== 0 && next <= 0 ? 0 : 1, 'haste expiry uses wrapped signed result');
    }
    const x = fixture(); x.borg.slowHitTimer = 1; x.borg.slowHitLevel = NaN;
    x.borg.hasteHitTimer = 0; readonly(x.borg, 'hasteHitTimer');
    x.run(); equal(x.borg.slowHitLevel, 0, 'expiry store never validates overwritten level');
    const y = fixture(); y.borg.slowHitTimer = 1; readonly(y.borg, 'slowHitLevel');
    y.borg.hasteHitTimer = NaN; rejects(y.run, 'slowHitLevel: non-writable');
    equal(y.borg.slowHitTimer, 0, 'expiry failure keeps prior710 decrement');
    equal(y.actual.aimRateScale, 9, 'expiry failure before768 reset');
    const z = fixture(); z.borg.slowHitTimer = 2; z.borg.hasteHitTimer = 1;
    readonly(z.borg, 'hasteHitTimer'); rejects(z.run, 'hasteHitTimer: non-writable');
    equal(z.borg.slowHitTimer, 1, 'earlier timer survives later refusal');
  }
  {
    const cases = [
      {slowAuraLevel: 1, hasteAuraLevel: 0, slowHitLevel: 0, hasteHitLevel: 0, bits: 0x3f333333},
      {slowAuraLevel: 2, hasteAuraLevel: 0, slowHitLevel: 0, hasteHitLevel: 0, bits: 0x3ecccccd},
      {slowAuraLevel: 0, hasteAuraLevel: 1, slowHitLevel: 0, hasteHitLevel: 0, bits: 0x3fa00000},
      {slowAuraLevel: 0, hasteAuraLevel: 2, slowHitLevel: 0, hasteHitLevel: 0, bits: 0x3fc00000},
      {slowAuraLevel: 0, hasteAuraLevel: 1, slowHitLevel: 0, hasteHitLevel: 2, bits: 0x3ff00000},
      {slowAuraLevel: 1, hasteAuraLevel: 1, slowHitLevel: 2, hasteHitLevel: 2, bits: 0x3f066667},
    ];
    for (const test of cases) {
      const x = fixture(); Object.assign(x.borg, test); x.run();
      equal(raw(x.actual.aimRateScale), test.bits, 'audited table words and rounded source multiply sequence');
      equal(x.actual.timescale, x.actual.aimRateScale, '5f4 copies final768');
      equal(x.mappingState.timestep1dc8, x.actual.aimRateScale, 'final1dc8 uses canonical status/base');
    }
    for (const gate of ['burst', 'flag', 'mode'] as const) {
      const x = fixture(); x.borg.slowAuraLevel = NaN; x.borg.slowHitLevel = NaN;
      x.borg.hasteAuraLevel = 1; x.borg.hasteHitLevel = 2;
      if (gate === 'burst') x.statusState.byte6fc = 255;
      if (gate === 'flag') x.actual.controlWord = 0x01000000;
      if (gate === 'mode') x.worldState.mode4a0 = 255;
      x.run(); equal(x.actual.aimRateScale, gate === 'burst' ? 2.8125 : 1.875, 'gate skips only slow loads');
    }
    for (const [field, address] of [['hasteAuraLevel', '8005a44c'], ['hasteHitLevel', '8005a47c'],
      ['slowAuraLevel', '8005a4d0'], ['slowHitLevel', '8005a500']] as const) {
      for (const unsupported of [3, 127, 128, 255]) {
        const x = fixture(); x.borg[field] = unsupported;
        x.borg.slowHitTimer = 2; x.borg.hasteHitTimer = 2;
        rejects(x.run, `${address} unsupported`);
        equal(x.borg.slowHitTimer, 1, 'unproven table index retains710 decrement');
        equal(x.borg.hasteHitTimer, 1, 'unproven table index retains712 decrement');
        equal(x.actual.aimRateScale, 1, 'unproven table index retains768 reset');
        equal(x.actual.timescale, 8, 'unproven table refuses before5f4');
      }
    }
    const x = fixture(); x.borg.hasteAuraLevel = 1; x.borg.hasteHitLevel = 3;
    rejects(x.run, 'table index 3'); equal(x.actual.aimRateScale, 1.25, 'first multiplication survives second table refusal');
    const y = fixture(); y.borg.hasteAuraLevel = 255; rejects(y.run, 'table index -1');
  }
  {
    for (const freeze of [0, 1, 2, 128, 255]) {
      const x = fixture(); x.statusState.byte71c = freeze; x.borg.hasteAuraLevel = 1;
      x.run(); equal(x.statusState.byte71c, freeze === 0 ? 0 : freeze - 1, 'unsigned freeze countdown');
      equal(x.actual.aimRateScale, 1.25, 'freeze does not overwrite768');
      equal(raw(x.actual.timescale), freeze > 1 ? 0x3cf5c28f : 0x3fa00000, 'freeze constant only while remaining byte nonzero');
      equal(x.mappingState.timestep1dc8, x.actual.timescale, 'freeze1dc8 or normal1dc8');
    }
    const x = fixture(true); delete x.initial.field1dd0; x.bind(); x.statusState.byte71c = 2;
    x.statusState.field1dcc = NaN; x.run(); equal(raw(x.mappingState.timestep1dc8), 0x3cf5c28f, 'freeze skips both final factors');
    x.statusState.byte71c = 1; rejects(x.run, 'field1dcc: finite exact source float32');
    equal(x.statusState.byte71c, 0, 'expired freeze retained despite missing factor');
    equal(x.actual.timescale, 1, '5f4 precedes final factor refusal');
    const y = fixture(); y.statusState.byte71c = 2; readonly(y.statusState, 'byte71c');
    rejects(y.run, 'byte71c: non-writable'); equal(y.actual.aimRateScale, 1, 'rate computed before freeze write');
    equal(y.actual.timescale, 8, 'freeze write refusal precedes5f4');
    const z = fixture(); z.statusState.byte71c = 2; readonly(z.mappingState, 'timestep1dc8');
    rejects(z.run, 'timestep1dc8: non-writable'); equal(z.statusState.byte71c, 1, 'freeze count retained');
    equal(raw(z.actual.timescale), 0x3cf5c28f, 'freeze5f4 survives1dc8 refusal');
  }
  {
    // Regression against Ghidra C's apparent (1dd0*1dcc)*768 grouping.
    const x = fixture(); x.borg.hasteAuraLevel = 1;
    x.statusState.field1dcc = value(0x3e04bb6b); x.binding().field1dd0 = value(0x3e10f44d);
    x.run(); equal(raw(x.mappingState.timestep1dc8), 0x3cbbe439, 'archived fmuls grouping');
    equal(raw(Math.fround(Math.fround(x.binding().field1dd0! * x.statusState.field1dcc!) * 1.25)),
      0x3cbbe438, 'wrong C grouping differs by one ulp');
    const numeric = [
      {status: -0, base: 1, expected: 0x80000000}, {status: 0, base: -1, expected: 0x80000000},
      {status: -0, base: -1, expected: 0}, {status: value(1), base: 1, expected: 1},
      {status: value(1), base: 0.5, expected: 0}, {status: -value(1), base: 0.5, expected: 0x80000000},
      {status: value(3), base: 0.5, expected: 2}, {status: value(0x007fffff), base: 1, expected: 0x007fffff},
    ];
    for (const test of numeric) {
      const y = fixture(); y.statusState.field1dcc = test.status; y.binding().field1dd0 = test.base;
      y.run(); equal(raw(y.mappingState.timestep1dc8), test.expected, 'source f32 signedzero/subnormal/tie');
    }
    for (const stage of ['first', 'second'] as const) {
      const y = fixture(); y.statusState.field1dcc = value(0x7f7fffff);
      if (stage === 'first') {y.borg.hasteAuraLevel = 2; y.binding().field1dd0 = 0;}
      else y.binding().field1dd0 = 2;
      rejects(y.run, `${stage === 'first' ? '8005a570' : '8005a574'} fmuls result`);
      equal(y.actual.timescale, stage === 'first' ? 1.5 : 1, 'overflow preserves prior5f4');
      equal(y.mappingState.timestep1dc8, 7, 'overflow refuses before final1dc8');
    }
    const y = fixture(true); delete y.initial.field1dd0; y.bind();
    y.statusState.field1dcc = value(0x7f7fffff); y.borg.hasteAuraLevel = 2;
    rejects(y.run, 'field1dd0: own data property'); // lfs1dd0 precedes first overflowing fmuls.
    for (const bad of [NaN, Infinity, -Infinity, 0.1]) {
      const z = fixture(); z.statusState.field1dcc = bad; rejects(z.run, 'finite exact source float32');
      equal(z.actual.timescale, 1, 'bad reached f32 preserves5f4');
    }
  }
  {
    const x = fixture(); x.worldState.mode4a0 = 2; x.borg.slowHitTimer = NaN;
    rejects(x.run, '8005a3a4 reached unsupported source pointer4a4 load');
    equal(x.actual.aimRateScale, 9, 'no fake linked write');
    rejects(() => createSourceActorRateLifecycleRuntime({...x.sources, matrix: {} as never}), 'genuine source runtime');
    const y = fixture(false, true), peer = y.peer(); y.worldState.mode4a0 = 2;
    equal(y.runtime.getMatrixBinding(y.id), y.matrix!.getActorBinding(y.id), 'same canonical4a4 owner');
    rejects(y.run, 'linked4a4 requires an already-bound');
    y.matrix!.getActorBinding(y.id).link4a4 = Symbol('unknown'); rejects(y.run, 'linked4a4 requires an already-bound');
    y.matrix!.getActorBinding(y.id).link4a4 = peer.id;
    peer.actual.aimRateScale = -0; peer.actual.timescale = value(1); peer.mappingState.timestep1dc8 = -2.5;
    y.statusState.byte6fc = NaN; y.borg.slowHitTimer = NaN;
    y.run(); equal(y.actual.aimRateScale, -0, 'linked768 signedzero');
    equal(y.actual.timescale, value(1), 'linked5f4 subnormal'); equal(y.mappingState.timestep1dc8, -2.5, 'linked mapping1dc8');
    peer.actual.aimRateScale = 3; peer.actual.timescale = NaN;
    rejects(y.run, 'timescale: finite exact'); equal(y.actual.aimRateScale, 3, 'linked768 survives invalid linked5f4');
    equal(y.actual.timescale, value(1), 'failed linked5f4 not written');
    peer.actual.timescale = 4; peer.mappingState.timestep1dc8 = NaN;
    rejects(y.run, 'timestep1dc8: finite exact'); equal(y.actual.timescale, 4, 'linked5f4 survives invalid linked1dc8');
    y.matrix!.getActorBinding(y.id).link4a4 = y.id; y.mappingState.timestep1dc8 = 5;
    y.run(); equal(y.actual.aimRateScale, 3, 'self-link preserves768'); equal(y.mappingState.timestep1dc8, 5, 'self-link preserves1dc8');
  }
  {
    // Descriptor-only shadow detection never invokes an accessor, including a
    // newly inserted legacy alias after admission. Wrong sources cannot claim.
    for (const [owner, key] of [['actual', 'dt'], ['borg', 'freezeFrames'], ['actual', 'field1dd0'],
      ['worldState', 'slowHitTimer'], ['mappingState', 'aimRateScale'], ['statusState', 'link4a4']] as const) {
      const x = fixture(true); let touched = false;
      Object.defineProperty(x[owner], key, {get() {touched = true; return 0;}, configurable: true});
      rejects(x.bind, 'competing rate-lifecycle'); check(!touched, 'shadow accessor not invoked');
      absent(x[owner], key); x.bind();
      Object.defineProperty(x[owner], key, {value: 0, configurable: true});
      rejects(x.run, 'competing rate-lifecycle'); equal(x.actual.aimRateScale, 9, 'post-bind shadow refuses before writes');
    }
    const x = fixture(true); Object.assign(x.initial, {slowHitTimer: 5}); rejects(x.bind, 'slowHitTimer: competing');
    const y = fixture(true); y.hooks.worldMapping = () => ({}); rejects(y.bind, 'world mapping: owner changed');
    y.hooks.worldMapping = undefined; y.bind(); y.hooks.statusMapping = () => Promise.resolve(y.mappingState);
    y.worldState.mode4a1 = 1; rejects(y.run, 'status mapping: owner changed');
    equal(y.mappingState.timestep1dc8, 7, 'async mapping owner refused before first fast write');
    const z = fixture(); z.hooks.borg = () => ({}); rejects(z.run, 'actual Borg: owner changed');
    equal(z.actual.aimRateScale, 9, 'changed Borg refused before timer/rate writes');
  }
  {
    // Mutating methods are captured at construction; receiver identity remains.
    const x = fixture(); x.world.getActualActor = () => {throw Error('replacement method');};
    x.status.getActorBinding = () => {throw Error('replacement method');}; x.run();
    const y = fixture(); y.hooks.status = () => {try {y.run();} catch {} return y.statusState;};
    rejects(y.run, 'caught same-runtime reentry'); equal(y.actual.aimRateScale, 1, 'earlier768 reset retained after caught reentry');
    equal(y.actual.timescale, 8, 'poison prevents later source work');
    y.hooks.status = undefined; y.run(); equal(y.actual.timescale, 1, 'fresh separate call is admitted');
    const z = fixture(true); z.hooks.borg = () => {try {z.bind();} catch {} return z.borg;};
    rejects(z.bind, 'caught same-runtime reentry'); z.hooks.borg = undefined; z.bind();
    equal(z.runtime.getActualActor(z.id), z.actual, 'failed reentrant admission did not claim actor');
  }
}
