import {createSourceActorNormalLifecycleRuntime, isSourceActorNormalLifecycleRuntime,
  isSourceActorNormalLifecycleClaimedActor, hasIncompleteSourceActorNormalCountdown,
  hasIncompleteSourceActorNormalCueSync,
  sourceActorNormalReturn80059138, sourceActorNormalReturn8006f950, sourceActorNormalReturn8018cfe4,
  type SourceActorNormalLifecycleBinding, type SourceActorNormalLifecycleSources} from './actor-normal-lifecycle.js';
import {createSourceActorCueResetRuntime, type SourceActorCueResetBinding} from './actor-cue-reset.js';
import {createRomActor} from './actor.js';
import type {SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorJointMappingHeader} from './actor-joint-mapping.js';
import type {SourceActorStatusTimersBinding} from './actor-status-timers.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[actor-normal-lifecycle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function absent(owner: object, key: string): void {Reflect.deleteProperty(owner, key);}
function readonly(owner: object, key: string): void {Object.defineProperty(owner, key, {writable: false});}

/** Real cue-reset implementation and explicit same-record source getters.
 * Fixtures are synthetic admissions, never a claimed family4c8 producer. */
function fixture(defer = false, withCues = true) {
  const id = Symbol('normal actor'), actual = createRomActor();
  delete (actual as Partial<typeof actual>).fbPhaseSlots;
  delete (actual as Partial<typeof actual>).shotByte1db3;
  actual.ubCue = 9; actual.fbCue = 9; actual.controlWord = 0;
  actual.stateFlagA = 1; actual.stateFlagB = 4;
  actual.fbState = -3; actual.prevFbState = -4; actual.fbPhase = 8;
  actual.cueTable = new Int8Array(20); actual.cueTable.fill(-1); actual.cueTable[18] = 7;
  const worldState = {} as SourceActorWorldMatrixBinding;
  const mapping = {} as SourceActorJointMappingHeader;
  const movementState = {byte661: 10, field66c: 0, field670: 0};
  const statusState: Partial<SourceActorStatusTimersBinding> = {};
  const gates = {family1d88: null, shared1d8c: null, marker578: 0, marker1db3: 0};
  const hooks: Record<string, (() => unknown) | undefined> = {};
  const calls: Record<string, number> = {};
  const get = <T>(name: string, value: T): T => {
    calls[name] = (calls[name] ?? 0) + 1;
    return (hooks[name] ? hooks[name]!() : value) as T;
  };
  const world = {
    getActualActor(key: symbol) {check(this === world && key === id, 'captured world actor receiver'); return get('actual', actual);},
    getActorBinding(key: symbol) {check(this === world && key === id, 'captured world binding receiver'); return get('world', worldState);},
    getMappingActor(key: symbol) {check(this === world && key === id, 'captured world mapping receiver'); return get('mapping', mapping);},
  };
  const movement = {
    getActualActor(key: symbol) {check(this === movement && key === id, 'captured movement actor receiver'); return get('movementActual', actual);},
    getActorBinding(key: symbol) {check(this === movement && key === id, 'captured movement binding receiver'); return get('movement', movementState);},
  };
  const status = {
    getActualActor(key: symbol) {check(this === status && key === id, 'captured status actor receiver'); return get('statusActual', actual);},
    getActorBinding(key: symbol) {check(this === status && key === id, 'captured status binding receiver'); return get('status', statusState);},
    getWorldBinding: () => get('statusWorld', worldState), getMappingActor: () => get('statusMapping', mapping),
    getMovementBinding: () => get('statusMovement', movementState),
  };
  const dispatch = {getSourceActor: () => get('dispatchMapping', mapping), getActorBinding: () => get('dispatch', gates)};
  const cues = createSourceActorCueResetRuntime({world, dispatch});
  const cueInitial: Partial<SourceActorCueResetBinding> = {byte541: 11, byte542: 12, byte543: 13, byte7cf: 22};
  cues.bindActor(id, cueInitial);
  const sources: SourceActorNormalLifecycleSources = {world, movement, status, ...(withCues ? {cues} : {})};
  const runtime = createSourceActorNormalLifecycleRuntime(sources);
  const initial: Partial<SourceActorNormalLifecycleBinding> = {
    callback4c8: 0x8018cfe4, callback4dc: null, short6bc: 2, byte1d9: 0,
  };
  const bind = () => runtime.bindActor(id, initial); if (!defer) bind();
  return {id, actual, worldState, mapping, movementState, statusState, gates, hooks, calls,
    world, movement, status, dispatch, cues, sources, initial, runtime, bind,
    binding: () => runtime.getActorBinding(id), cueBinding: () => cues.getActorBinding(id),
    run: () => runtime.updateActor(id), cue: () => runtime.dispatchCue(id),
    sync: () => runtime.updateCueState(id), countdown: () => runtime.updateCountdown(id)};
}
export function runActorNormalLifecycleSelfTests(): void {
  {
    const x = fixture();
    for (const rotation of [undefined, null, {}, {updateActor() {}}]) {
      rejects(() => createSourceActorNormalLifecycleRuntime({...x.sources, rotation: rotation as never}),
        'rotation requires genuine source runtime');
    }
  }
  {
    const x = fixture();
    check(isSourceActorNormalLifecycleRuntime(x.runtime), 'genuine runtime brand');
    for (const fake of [null, undefined, {}, {...x.runtime}, Object.create(x.runtime)])
      check(!isSourceActorNormalLifecycleRuntime(fake), 'brand cannot be copied or inherited');
    check(Object.isFrozen(x.runtime) && Object.isSealed(x.binding()), 'frozen methods and sealed explicit cells');
    check(isSourceActorNormalLifecycleClaimedActor(x.actual), 'permanent actual actor claim');
    check(!isSourceActorNormalLifecycleClaimedActor({...x.actual}), 'claim is actual identity');
    equal(x.runtime.getActualActor(x.id), x.actual, 'canonical actual');
    equal(x.runtime.getWorldBinding(x.id), x.worldState, 'canonical world');
    equal(x.runtime.getMappingActor(x.id), x.mapping, 'canonical mapping');
    equal(x.runtime.getMovementBinding(x.id), x.movementState, 'canonical move661');
    equal(x.runtime.getStatusBinding(x.id), x.statusState, 'canonical status');
    equal(x.runtime.getCueRuntime(), x.cues, 'genuine cue implementation');
    equal(x.runtime.getCueBinding(x.id), x.cueBinding(), 'canonical cue bytes');
    equal(x.runtime.getDispatchBinding(x.id), x.gates, 'canonical dispatch bytes');
    equal(Object.keys(x.binding()).sort().join(','), 'byte1d9,callback4c8,callback4dc,short6bc', 'only four missing source cells');
    equal(x.run(), undefined, 'both actual fixed callees and helpers return source void');
    equal(x.binding().short6bc, 1, 'countdown executed after both dispatches and helper');
    equal(x.initial.short6bc, 2, 'initial copied once, not another live owner');
    x.run(); equal(x.binding().short6bc, 0, 'second explicit run executes null expiry');
    equal(x.runtime.assertActorComplete(x.id), undefined, 'null expiry complete');
    rejects(() => createSourceActorNormalLifecycleRuntime(x.sources).bindActor(x.id, {}), 'actual actor already claimed');
    rejects(() => x.runtime.bindActor(x.id, {}), 'new symbol actor identity');
    rejects(() => x.runtime.updateActor(Symbol()), 'unknown/non-owned');
    rejects(() => createSourceActorNormalLifecycleRuntime({...x.sources, cues: {...x.cues}}), 'cues requires genuine');
    rejects(() => createSourceActorNormalLifecycleRuntime({...x.sources, cues: Object.create(x.cues)}), 'cues requires genuine');
    equal(x.actual.rootAction, null, 'family rootAction never selected as4c8');
  }
  {
    // The independent authenticated blr leaves must not read, inspect or write
    // the supplied actor, including through a host getter or proxy trap.
    const noAccess = new Proxy({}, {get() {throw Error('leaf get');}, set() {throw Error('leaf set');},
      getOwnPropertyDescriptor() {throw Error('leaf descriptor');}, ownKeys() {throw Error('leaf keys');}});
    equal(sourceActorNormalReturn80059138(noAccess), undefined, 'cue9 leaf has no actor access');
    equal(sourceActorNormalReturn8006f950(noAccess), undefined, 'actual Double Ninja4c8 target has no actor access');
    equal(sourceActorNormalReturn8018cfe4(noAccess), undefined, 'actual4c8 leaf has no actor access');
    const double = fixture(); double.binding().callback4c8 = 0x8006f950;
    double.run(); equal(double.binding().short6bc, 1, 'explicit actual Double Ninja target reaches both following helpers');
    for (let raw = 0; raw < 256; raw++) {
      const x = fixture(true); Object.keys(x.initial).forEach(key => absent(x.initial, key)); x.bind();
      x.actual.ubCue = raw;
      if (raw === 9) equal(x.cue(), undefined, 'proven cue9 returns without4c8/59f5c reads');
      else if (raw === 0) rejects(x.cue, 'actual cue target8005913c');
      else if (raw === 44) rejects(x.cue, 'actual cue target80059cd0');
      else {
        const signed = raw < 128 ? raw : raw - 256;
        const cell = 0x802d3300 + signed * 4;
        rejects(x.cue, `entry ${cell.toString(16)} before indirect call800590e8`);
      }
      equal(Object.keys(x.binding()).length, 0, 'cue selection creates no source fields');
    }
    const x = fixture(); x.actual.ubCue = 0; x.binding().callback4c8 = NaN;
    rejects(x.run, 'target8005913c'); equal(x.binding().short6bc, 2, 'cue0 body gap prevents4c8 and helpers');
    for (const raw of [-1, 256, 1.5, NaN, Infinity]) {
      const y = fixture(); y.actual.ubCue = raw; rejects(y.cue, 'ubCue: integer');
    }
  }
  {
    for (const target of [null, 0, 0x80059138, 0x8005913c, 0x8006f954, 0x8006f958, 0x8018cfe8, 0xffffffff]) {
      const x = fixture(); x.binding().callback4c8 = target;
      x.actual.controlWord = NaN; x.binding().short6bc = NaN;
      let called = false;
      x.actual.rootAction = x.actual.preState = x.actual.postState = () => {called = true;};
      rejects(x.run, `actual4c8 target ${target === null || target === 0 ? 'null' : target.toString(16)}`);
      check(!called, 'other actual callbacks never substitute for4c8');
    }
    const x = fixture(true); delete x.initial.callback4c8; x.bind();
    x.actual.controlWord = NaN; rejects(x.run, 'callback4c8: own data');
    for (const bad of [-1, 0x100000000, 1.5, NaN, Infinity, () => {}]) {
      const y = fixture(); y.binding().callback4c8 = bad as number;
      rejects(y.run, 'callback4c8: integer'); equal(y.binding().short6bc, 2, 'invalid4c8 blocks helpers');
    }
  }
  {
    for (const flag of [1, 2, 0x1000000, 0x80000000, 0x81000003]) {
      const x = fixture(true, false); delete x.initial.byte1d9; x.bind();
      x.actual.controlWord = flag; x.actual.ubCue = NaN; x.actual.fbCue = NaN;
      x.movementState.byte661 = NaN; rejects(x.sync, 'byte1d9: own data');
      const y = fixture(false, false); y.actual.controlWord = flag; y.binding().byte1d9 = 15;
      absent(y.actual, 'ubCue'); absent(y.actual, 'fbCue'); absent(y.actual, 'stateFlagA'); absent(y.actual, 'stateFlagB');
      y.movementState.byte661 = NaN; equal(y.sync(), undefined, 'masked1d9 low nibble returns without cue/movement/57a/b');
    }
    for (const metadata of [0x10, 0x20, 0x80, 0xf0, 0xff]) {
      const x = fixture(); x.actual.controlWord = 1; x.binding().byte1d9 = metadata;
      x.actual.ubCue = NaN; x.movementState.byte661 = NaN;
      x.actual.stateFlagA = 0x81; x.actual.stateFlagB = 0x56; x.sync();
      equal(x.actual.stateFlagA, 0xd7, 'source57a OR57b onto actual owner');
      equal(x.actual.stateFlagB, 0x56, '57b source preserved');
    }
    for (const flag of [0, 4, 0x40, 0x1000, 0x20000000]) {
      const x = fixture(true, false); delete x.initial.byte1d9; x.bind(); x.actual.controlWord = flag;
      equal(x.sync(), undefined, 'other control bits do not enter57a branch');
    }
    const x = fixture(); x.actual.controlWord = 1; x.binding().byte1d9 = 0x10;
    readonly(x.actual, 'stateFlagA'); x.actual.stateFlagB = NaN;
    rejects(x.sync, 'stateFlagB: integer'); equal(x.actual.stateFlagA, 1, '57b read precedes57a writable check');
    x.actual.stateFlagB = 4; rejects(x.sync, 'stateFlagA: non-writable');
    const y = fixture(); y.actual.controlWord = 1; y.binding().byte1d9 = 0x10;
    absent(y.actual, 'stateFlagA'); y.actual.stateFlagB = NaN; rejects(y.sync, 'stateFlagA: own data');
    const z = fixture(true); delete z.initial.short6bc; z.bind();
    z.actual.controlWord = 1; z.binding().byte1d9 = 0x10;
    rejects(z.run, 'short6bc: own data'); equal(z.actual.stateFlagA, 5, 'missing countdown retains preceding57a store');
    const w = fixture(); w.actual.controlWord = 1; w.binding().byte1d9 = 0x10;
    readonly(w.binding(), 'short6bc'); rejects(w.run, 'short6bc: non-writable');
    equal(w.actual.stateFlagA, 5, 'readonly countdown retains preceding57a store');
    equal(w.binding().short6bc, 2, 'readonly countdown does not decrement');
  }
  {
    const x = fixture(); x.actual.fbCue = 8; x.sync();
    equal(x.actual.fbCue, 9, 'real6a6fc synchronizes full cue');
    equal(x.cueBinding().byte7cf, 8, 'real6a6fc saves prior full cue');
    equal(x.actual.prevFbState, -3, 'real6a6fc preserves previous full state');
    equal(x.actual.fbState, 7, 'real6a6fc reads actual table');
    equal(x.actual.fbPhase, 0, 'real6a6fc clears actual phase');
    check(!hasIncompleteSourceActorNormalCueSync(x.actual), 'native1 clears cue synchronization guard');
    for (const key of ['byte543', 'byte542', 'byte541'] as const) equal(x.cueBinding()[key], 0, 'real6a6fc clears source byte');
    const y = fixture(); y.actual.fbCue = 8; y.actual.cueTable![18] = -1; y.sync();
    equal(y.actual.fbCue, 8, 'genuine sentinel0 result ignored, no fabricated synchronization');
    equal(y.actual.fbPhase, 8, 'genuine sentinel leaves phase');
    check(!hasIncompleteSourceActorNormalCueSync(y.actual), 'native0 clears cue synchronization guard');
    const z = fixture(false, false); z.actual.fbCue = 8; z.movementState.byte661 = NaN;
    rejects(z.sync, '80059f9c reached unsupported source call8006a6fc');
    check(!hasIncompleteSourceActorNormalCueSync(z.actual), 'missing callee is not marked as an attempted call');
    const w = fixture(); w.actual.ubCue = 255; w.actual.fbCue = 9;
    rejects(w.sync, 'cueTable: indexed byte outside explicitly owned storage');
    equal(w.actual.fbCue, 9, 'negative signed cue passes full32 register bits, not low8 index');
    for (const move of [0, 9, 11, 128, 255]) {
      const a = fixture(); a.actual.fbCue = 8; a.movementState.byte661 = move;
      rejects(a.sync, '80059fac reached unsupported rotation damping');
      equal(a.actual.fbCue, 9, 'rotation refusal retains completed source cue synchronization');
      equal(a.binding().short6bc, 2, 'direct59f5c never touches countdown');
      rejects(a.run, '80059fac'); equal(a.binding().short6bc, 2, 'complete sequence does not skip rotation refusal');
    }
    const a = fixture(); a.actual.fbCue = 8; readonly(a.actual, 'fbPhase');
    rejects(a.run, 'fbPhase: non-writable'); equal(a.actual.fbCue, 9, 'callee partial prefix retained');
    equal(a.binding().short6bc, 2, 'partial callee prevents countdown');
    const b = fixture(); b.actual.fbCue = 8; b.movementState.byte661 = NaN;
    rejects(b.sync, 'byte661: integer'); equal(b.actual.fbCue, 9, 'move load follows real cue reset');
  }
  {
    for (const stop of ['fbPhase', 'byte542'] as const) {
      const x = fixture(); x.actual.fbCue = 8; x.actual.fbPhase = 5;
      readonly(stop === 'fbPhase' ? x.actual : x.cueBinding(), stop);
      rejects(x.run, `${stop}: non-writable`);
      equal(x.actual.fbCue, 9, 'partial real callee retains its early cue store');
      equal(x.actual.prevFbState, -3, 'partial real callee retains previous state');
      equal(x.actual.fbState, 7, 'partial real callee retains selected state');
      equal(x.cueBinding().byte543, 0, 'partial real callee retains preceding phase clear');
      equal(x.cueBinding().byte542, stop === 'byte542' ? 12 : 0, 'stopped or completed542 store');
      equal(x.cueBinding().byte541, stop === 'byte542' ? 11 : 0, 'unreached or completed541 store');
      equal(x.actual.fbPhase, 5, 'failed real callee preserves final phase destination');
      equal(x.binding().short6bc, 2, 'failed synchronization cannot reach countdown');
      check(hasIncompleteSourceActorNormalCueSync(x.actual), 'partial real callee permanently guards actual identity');
      check(!hasIncompleteSourceActorNormalCueSync({...x.actual}), 'cue synchronization guard is identity-based');
      rejects(x.run, 'known incomplete cue synchronization');
      equal(x.binding().short6bc, 2, 'equal cues cannot turn retained prefix into completed normal call');
      // Changing both cues or the control mask must not launder the partial
      // call into either a mismatch-free return or the other59f5c branch.
      x.actual.ubCue = x.actual.fbCue = 0;
      x.actual.controlWord = 1; x.binding().byte1d9 = 0x10;
      const reads = JSON.stringify(x.calls);
      rejects(x.run, 'known incomplete cue synchronization');
      rejects(x.sync, 'known incomplete cue synchronization');
      rejects(x.countdown, 'known incomplete cue synchronization');
      rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete cue synchronization');
      equal(JSON.stringify(x.calls), reads, 'host guard precedes owner callbacks and source scalar reads');
      equal(x.actual.stateFlagA, 1, 'changed mask cannot execute57a merge after incomplete cue reset');
      equal(x.binding().short6bc, 2, 'changed cues cannot execute countdown after incomplete cue reset');
      x.actual.ubCue = 9; equal(x.cue(), undefined, 'independent cue9 leaf remains independently callable');
      check(hasIncompleteSourceActorNormalCueSync(x.actual), 'independent leaf does not clear incomplete call');
    }
  }
  {
    for (const value of [-32768, -1, 0, 2, 32767]) {
      const x = fixture(true); delete x.initial.callback4dc; x.initial.short6bc = value; x.bind();
      equal(x.countdown(), undefined, 'non-expiring countdown does not demand4dc');
      equal(x.binding().short6bc, value > 0 ? value - 1 : value, 'signed countdown result');
    }
    for (const nullPointer of [null, 0]) {
      const x = fixture(); x.binding().short6bc = 1; x.binding().callback4dc = nullPointer;
      equal(x.countdown(), undefined, 'explicit zero pointer returns after expiry');
      equal(x.binding().short6bc, 0, 'null expiry retains source decrement');
      check(!hasIncompleteSourceActorNormalCountdown(x.actual), 'null expiry clears host guard');
    }
    for (const target of [0x8018cfe4, 0x80059138, 1, 0xffffffff]) {
      const x = fixture(); x.binding().short6bc = 1; x.binding().callback4dc = target;
      rejects(x.countdown, '8005a17c reached unsupported actual4dc'); equal(x.binding().short6bc, 0, 'nonnull callback refusal follows decrement');
      check(hasIncompleteSourceActorNormalCountdown(x.actual), 'nonnull expiry remains incomplete');
      x.binding().callback4dc = null; x.actual.ubCue = NaN;
      rejects(x.countdown, 'known incomplete6bc expiry'); rejects(x.run, 'known incomplete6bc expiry');
      rejects(x.sync, 'known incomplete6bc expiry');
      rejects(() => x.runtime.assertActorComplete(x.id), 'known incomplete6bc expiry');
    }
    const x = fixture(true); delete x.initial.callback4dc; x.initial.short6bc = 1; x.bind();
    rejects(x.countdown, 'callback4dc: own data'); equal(x.binding().short6bc, 0, 'absent4dc keeps prior decrement');
    rejects(x.countdown, 'known incomplete6bc expiry');
    const y = fixture(); y.binding().short6bc = 1; y.binding().callback4dc = NaN;
    rejects(y.countdown, 'callback4dc: integer'); equal(y.binding().short6bc, 0, 'bad4dc keeps prior decrement');
    rejects(y.run, 'known incomplete6bc expiry');
    const z = fixture(); z.binding().short6bc = 1; readonly(z.binding(), 'short6bc');
    z.binding().callback4dc = NaN; rejects(z.countdown, 'short6bc: non-writable');
    check(!hasIncompleteSourceActorNormalCountdown(z.actual), 'failed store did not expire source timer');
    for (const bad of [-32769, 32768, 1.5, NaN, Infinity]) {
      const a = fixture(); a.binding().short6bc = bad; rejects(a.countdown, 'short6bc: integer');
    }
    for (const bad of [-1, 256, 1.5, NaN, Infinity]) {
      const a = fixture(); a.actual.controlWord = 1; a.binding().byte1d9 = bad;
      rejects(a.sync, 'byte1d9: integer'); equal(a.actual.stateFlagA, 1, 'invalid1d9 prevents57a reads/stores');
    }
    for (const [key, bad] of [['callback4c8', -1], ['callback4dc', 0x100000000],
      ['short6bc', -32769], ['byte1d9', 256]] as const) {
      const a = fixture(true); a.initial[key] = bad; rejects(a.bind, `${key}: integer`);
      a.initial[key] = key === 'callback4c8' ? 0x8006f950 : 0; a.bind();
    }
  }
  {
    const shadows = ['callback4c8', 'callback4dc', 'short6bc', 'byte1d9', 'byte661', 'flags57a', 'byte57a',
      'flags57b', 'byte57b', 'metadata1d9', 'hitReact', 'flyingBounce1d9', 'aerialXDamaged', 'field6bc'];
    for (const key of shadows) {
      const x = fixture(true); let invoked = false;
      Object.defineProperty(x.actual, key, {get() {invoked = true; return 0;}, configurable: true});
      rejects(x.bind, 'competing normal-lifecycle'); check(!invoked, 'shadow check never invokes source accessor');
      absent(x.actual, key); x.bind();
      Object.defineProperty(x.actual, key, {value: 0, configurable: true});
      rejects(x.run, 'competing normal-lifecycle'); equal(x.binding().short6bc, 2, 'shadow refusal before effects');
    }
    for (const key of ['controlWord', 'ubCue', 'fbCue', 'stateFlagA', 'stateFlagB', 'byte661', 'byte57a']) {
      const x = fixture(true); Object.assign(x.initial, {[key]: 0}); rejects(x.bind, 'competing normal-lifecycle');
    }
    const expected = {actual: 'world actor', world: 'world binding', mapping: 'world mapping', movementActual: 'movement actor',
      movement: 'movement binding', statusActual: 'status actor', status: 'status binding', statusWorld: 'status world',
      statusMapping: 'status mapping', statusMovement: 'status movement'};
    for (const [hook, name] of Object.entries(expected)) {
      const x = fixture(); x.hooks[hook] = () => ({}); rejects(x.run, `${name}: owner changed`);
      x.hooks[hook] = () => Promise.resolve({}); rejects(x.run, `${name}: owner changed`);
      equal(x.binding().short6bc, 2, 'owner substitution blocks source prefix');
    }
    const x = fixture(true); x.hooks.statusMovement = () => ({...x.movementState});
    rejects(x.bind, 'status movement: owner changed'); x.hooks.statusMovement = undefined; x.bind();
    const y = fixture(); y.hooks.dispatchMapping = () => ({}); y.actual.fbCue = 8;
    rejects(y.sync, 'dispatch mapping: owner changed'); equal(y.actual.fbCue, 8, 'real cue callee checks mapping owner');
    const z = fixture();
    let accessed = false; Object.defineProperty(z.actual, 'ubCue', {get() {accessed = true; return 9;}});
    rejects(z.cue, 'ubCue: own data'); check(!accessed, 'source getters not executed');
  }
  {
    const x = fixture(); x.world.getActualActor = () => {throw Error('replacement world method');};
    x.movement.getActorBinding = () => {throw Error('replacement movement method');};
    x.status.getMovementBinding = () => {throw Error('replacement status method');};
    x.sources.world = {...x.world}; x.sources.cues = {...x.cues};
    x.actual.fbCue = 8; x.run(); equal(x.actual.fbCue, 9, 'captured real cue callee and source receivers survive replacements');
    const y = fixture(); y.hooks.statusMovement = () => {try {y.run();} catch {} return y.movementState;};
    rejects(y.run, 'caught same-runtime reentry'); equal(y.binding().short6bc, 2, 'caught reentry before source mutations');
    y.hooks.statusMovement = undefined; y.run(); equal(y.binding().short6bc, 1, 'fresh independent operation after pre-store poison');
    const z = fixture(true); z.hooks.statusActual = () => {try {z.bind();} catch {} return z.actual;};
    rejects(z.bind, 'caught same-runtime reentry'); check(!isSourceActorNormalLifecycleClaimedActor(z.actual), 'failed admission does not claim actor');
    z.hooks.statusActual = undefined; z.bind();
    const w = fixture(); w.actual.fbCue = 8;
    const before = w.calls.actual ?? 0;
    w.hooks.actual = () => {if (w.calls.actual === before + 2) {try {w.countdown();} catch {}} return w.actual;};
    rejects(w.run, 'caught same-runtime reentry');
    equal(w.actual.fbCue, 9, 'caught reentry in genuine callee retains its completed source prefix');
    equal(w.binding().short6bc, 2, 'outer poison prevents subsequent countdown');
    check(hasIncompleteSourceActorNormalCueSync(w.actual), 'caught reentry prevents accepting the genuine callee return');
    w.hooks.actual = undefined; w.actual.ubCue = w.actual.fbCue = 9;
    rejects(w.run, 'known incomplete cue synchronization');
    rejects(w.sync, 'known incomplete cue synchronization');
    equal(w.binding().short6bc, 2, 'caught reentry marker cannot be laundered by equal cues');
  }
  console.log('[actor-normal-lifecycle-test] 256 signed cue cells, fixed leaves, canonical owners, real cue synchronization, bounded59f5c and signed6bc expiry passed');
}
