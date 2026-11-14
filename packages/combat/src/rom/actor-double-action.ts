/** Bounded actual Double action2 dispatch, offline only.
 * Source:55568/65dfc/6facc/71598/715d4/ff2bc/ff30c and6d144/669d0/66a30.
 * Exact instruction operands and vectors are authenticated by the fixed
 * read_archived_double_action_evidence.py reader, not inferred from C order.
 * See research/decomp/double-action-envelope-evidence-2026-11-14.md.
 * Explicit decoded tables select numeric source functions, never host callbacks
 * or legacy Ninja streams. Only authenticated UB return, FB root, action2,
 * variant0 and phase0 bodies are supported. Unknown targets refuse when reached.
 * The caller captures UB then FB before marker1, dispatches saved UB before saved
 * FB and owns the578 stores. No state reload, default table or mode0 substitution.
 *
 * Actual actor owns540/580/581, yaw andCC; cue reset owns541; prehook owns4b4;
 * attributes owns4ac and its signed+ae; mapping owns1dc8. All are retained, never
 * copied. NullCC yaw runs actual6d144->669d0->66a30 including signed negative
 * rate behavior. Non-nullCC refuses actual6660c, not a host target approximation.
 * Paired-vector helpers preserve XY/Z load/store order with explicit GQR0=0.
 * Optional genuine677b0 supplies the query-backed no-contact continuation,
 * then authenticated fixed config0/1, signed6ea capture/increment, the same
 * genuine4beb8 stream runtime, and80c only after its return. This can execute
 * real copied commands/setup/mode1 with explicit inputs, not retail schedules.
 * Float32 RN00/NI0, paired-single enablement and finite signed32 conversion are
 * host bounds, not observed processor configuration. Failed
 * operations retain prior stores and permanently latch the shared incomplete
 * Double lifecycle, so changed selectors cannot replay a partial handler.
 */
import {isSourceActorGroundProbeRuntime, type SourceActorGroundProbeRuntime} from './actor-ground-probe.js';
import type {RomActor} from './actor.js';
import {addSourceFloat32} from './source-float.js';
import {isSourceActorDoublePrehookRuntime, markIncompleteSourceActorDoubleLifecycle,
  requireCompleteSourceActorDoubleLifecycle, type SourceActorDoublePrehookRuntime} from './actor-double-prehook.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime} from './actor-cue-reset.js';

export interface SourceActorDoubleActionTables {
  /** Decoded source u32 code words. Sparse arrays retain missing-cell refusals. */
  upper37a8: readonly number[];
  full36a8: readonly number[];
  actions3b68: readonly number[];
  variants3c48: readonly number[];
  phases1f000: readonly number[];
}
export interface SourceActorDoubleActionSources {
  prehook: SourceActorDoublePrehookRuntime;
  attributes: SourceActorAttributeRefreshRuntime;
  cues: SourceActorCueResetRuntime;
  tables: SourceActorDoubleActionTables;
  /** Genuine677b0 continuation; absence preserves the historical boundary. */
  ground?: SourceActorGroundProbeRuntime;
  /** Required only when a reached vector helper uses GQR0 float loads/stores. */
  processor?: {gqr0: number};
}
/** Private-runtime-authenticated saved source locals. Copying this object does not grant authority. */
export interface SourceActorDoubleStateSelectors {readonly upper: number; readonly full: number}
export interface SourceActorDoubleActionRuntime {
  bindActor(identity: symbol): void;
  getActualActor(identity: symbol): RomActor;
  getPrehookRuntime(): SourceActorDoublePrehookRuntime;
  getGroundRuntime(): SourceActorGroundProbeRuntime | undefined;
  getPrehookBinding(identity: symbol): object;
  getMappingActor(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getCueBinding(identity: symbol): object;
  getDispatchBinding(identity: symbol): object;
  getTables(): SourceActorDoubleActionTables;
  /** Retained canonical owners, including reached parameters; no field snapshots. */
  getSourceOwners(identity: symbol): readonly object[];
  assertActorComplete(identity: symbol): void;
  captureStateSelectors(identity: symbol): SourceActorDoubleStateSelectors;
  dispatchUpper(identity: symbol, saved: SourceActorDoubleStateSelectors): void;
  dispatchFull(identity: symbol, saved: SourceActorDoubleStateSelectors): void;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
export function isSourceActorDoubleActionRuntime(value: unknown): value is SourceActorDoubleActionRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-double-action] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(value, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
const TABLES = ['upper37a8', 'full36a8', 'actions3b68', 'variants3c48', 'phases1f000'] as const;
export function createSourceActorDoubleActionRuntime(sources: SourceActorDoubleActionSources): SourceActorDoubleActionRuntime {
  const prehook = own(sources, 'prehook'), attributes = own(sources, 'attributes'), cues = own(sources, 'cues');
  if (!isSourceActorDoublePrehookRuntime(prehook)) fail('genuine Double prehook runtime required');
  if (!isSourceActorAttributeRefreshRuntime(attributes)) fail('genuine source attribute runtime required');
  if (!isSourceActorCueResetRuntime(cues)) fail('genuine source cue-reset runtime required');
  const ground = Object.getOwnPropertyDescriptor(sources, 'ground') === undefined ? undefined : own(sources, 'ground');
  if (ground !== undefined && !isSourceActorGroundProbeRuntime(ground)) fail('genuine source ground-probe runtime required');
  const streams = prehook.getStreamsRuntime();
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const write = (value: object, key: string, next: number | null): void => {
    own(value, key, true); check(); (value as Record<string, unknown>)[key] = next; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const call = <T>(run: () => T): T => {const result = run(); check(); return result;};
  const tables = record(read(sources, 'tables'), 'decoded Double dispatch tables') as SourceActorDoubleActionTables;
  const processor = Object.getOwnPropertyDescriptor(sources, 'processor') === undefined ? undefined :
    record(read(sources, 'processor'), 'processor');
  const arrays = {} as Record<typeof TABLES[number], readonly number[]>;
  for (const key of TABLES) {
    const value = read(tables, key); if (!Array.isArray(value)) fail(`${key}: explicit decoded array required`);
    arrays[key] = value;
  }
  if (new Set([tables, ...Object.values(arrays)]).size !== 6) fail('dispatch table owner alias');
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 0, 255, key);
  const signedByte = (owner: unknown, key: string): number => byte(owner, key) << 24 >> 24;
  const state = (owner: unknown, key: string): number => integer(read(owner, key), -128, 127, key);
  const bam = (owner: unknown, key: string): number => integer(read(owner, key), 0, 65535, key);
  const f = (owner: unknown, key: string): number => float(read(owner, key), key);
  const word = (owner: unknown, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const s16 = (value: number): number => value << 16 >> 16;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: canonical owner changed or differs`);
  };
  interface Entry {actual: RomActor; prehook: object; mapping: object; attribute: object; cue: object; dispatch: object;
    pos: object; motion: object; history: object}
  const shared = (): object[] => [tables, ...Object.values(arrays), ...(processor ? [processor] : [])];
  const parameters = new Set<object>();
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const snapshots = new WeakMap<object, {id: symbol; stage: 'upper' | 'full' | 'done'}>();
  const pending = new Map<symbol, SourceActorDoubleStateSelectors>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned Double action actor'); return e;};
  const noShadows = (e: Entry, extras: readonly object[] = []): void => {
    const canonical = new Map<string, object>([
      ...['fbPhase','actionIndex','variantIndex','ubState','fbState','visibilityTarget','activeYaw','turnErrorYaw','heading','lockYaw',
        'hSpeed','yVel','hDecel','gravityCoeff','poseAccum80','poseAccum7e','poseAccum7c','pos','motion','targetCache5e8','streamSlot','accumulator80c'].map(key => [key,e.actual] as [string, object]),
      ['byte541', e.cue], ['pointer4b4', e.prehook], ['pointer4bc', e.prehook], ['pointer4c0', e.prehook],
      ['parameter4ac', e.attribute], ['timestep1dc8', e.mapping], ['marker578', e.dispatch],
    ]);
    const owners = [...Object.values(e), ...shared(), ...extras];
    for (const owner of owners) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing source storage owner`);
        check();
      }
      if (!parameters.has(owner) && Object.getOwnPropertyDescriptor(owner, 'fieldAe') !== undefined)
        fail('fieldAe: competing parameter4ac storage owner');
      check();
      for (const key of ['byte540','phase540','byte580','action580','byte581','variant581','byte5da','byte5db','pointerCC','pointercc',
        'field4ac','pointer4ac','field1dc8','phaseSlots','fbPhaseSlots','lockTarget']) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing source storage alias`);
        check();
      }
    }
    for (const key of ['rootAction', 'preState', 'postState']) if (read(e.actual, key) !== null) fail(`${key}: legacy callable conflicts with source ownership`);
  };
  const owners = (id: symbol, e: Entry): void => {
    requireCompleteSourceActorDoubleLifecycle(e.actual); check();
    stable(call(() => prehook.getActualActor(id)), e.actual, 'prehook actual');
    stable(call(() => attributes.getActualActor(id)), e.actual, 'attribute actual');
    stable(call(() => cues.getActualActor(id)), e.actual, 'cue actual');
    stable(call(() => prehook.getActorBinding(id)), e.prehook, 'prehook binding');
    stable(call(() => prehook.getMappingActor(id)), e.mapping, 'prehook mapping');
    stable(call(() => attributes.getMappingActor(id)), e.mapping, 'attribute mapping');
    stable(call(() => cues.getMappingActor(id)), e.mapping, 'cue mapping');
    stable(call(() => attributes.getActorBinding(id)), e.attribute, 'attribute binding');
    stable(call(() => prehook.getAttributeBinding(id)), e.attribute, 'prehook attribute');
    stable(call(() => cues.getActorBinding(id)), e.cue, 'cue binding');
    stable(call(() => cues.getDispatchBinding(id)), e.dispatch, 'dispatch binding');
    stable(call(() => prehook.getStreamsRuntime()), streams, 'stream runtime');
    stable(call(() => streams.getStartActorBinding(id)), call(() => prehook.getStartBinding(id)), 'source stream start');
    if (ground !== undefined) {
      stable(call(() => ground.getActualActor(id)), e.actual, 'ground actual');
      stable(call(() => ground.getWorldBinding(id)), call(() => prehook.getWorldBinding(id)), 'ground world');
      stable(call(() => ground.getStatusBinding(id)), call(() => prehook.getStatusBinding(id)), 'ground status');
      noShadows(e, call(() => ground.getSourceOwners(id)));
    }
    for (const key of TABLES) stable(read(tables, key), arrays[key], key);
    stable(read(e.actual, 'pos'), e.pos, 'position20'); stable(read(e.actual, 'motion'), e.motion, 'motion38');
    stable(read(e.actual, 'targetCache5e8'), e.history, 'own history5e8');
    noShadows(e);
  };
  const selected = (key: typeof TABLES[number], index: number): number => {
    if (index < 0) fail(`${key}: unsupported signed selector ${index} before table base`);
    return word(arrays[key], String(index));
  };
  const expectTarget = (actual: number, expected: number, site: string): void => {
    if (actual !== expected) fail(`${site}: unsupported target0x${actual.toString(16)}`);
  };
  const target = (actual: object): object | null => {
    const value = read(actual, 'visibilityTarget');
    return value === null ? null : record(value, 'actualCC target');
  };
  const nullTargetYaw = (e: Entry): void => {
    const a = e.actual;
    // actual6d144, not a null-target early return. This writes before4ac is read.
    if (target(a) !== null) fail('8006d144 reached unsupported actual8006660c target-yaw helper');
    const sourceHeading = bam(a, 'heading'), sourceActive = bam(a, 'activeYaw');
    write(a, 'turnErrorYaw', (sourceActive - sourceHeading) & 65535);
    const pointer = read(e.attribute, 'parameter4ac');
    if (typeof pointer !== 'symbol') fail('800669d0 parameter4ac: owned descriptor identity required');
    const parameter = record(call(() => attributes.getParameterDescriptor(pointer)), 'parameter4ac descriptor');
    if ([...Object.values(e), ...shared()].includes(parameter)) fail('parameter4ac owner alias');
    parameters.add(parameter); noShadows(e, [parameter]);
    const timestep = f(e.mapping, 'timestep1dc8');
    const rate = integer(read(parameter, 'fieldAe'), -32768, 32767, 'parameter4ac+ae');
    const product = float(Math.fround(rate * timestep), '669d0 fmuls result');
    let step = s16(integer(Math.trunc(product), -2147483648, 2147483647, '669d0 fctiwz signed32 result'));
    const error = s16(bam(a, 'turnErrorYaw')), capturedHeading = bam(a, 'heading');
    if (step < Math.abs(error)) {
      if (error < 0) step = s16(-step);
      const heading = (capturedHeading + step) & 65535;
      write(a, 'turnErrorYaw', (bam(a, 'turnErrorYaw') - step) & 65535);
      write(a, 'lockYaw', heading); write(a, 'heading', heading);
    } else {
      write(a, 'turnErrorYaw', 0);
      const heading = (capturedHeading + error) & 65535;
      write(a, 'lockYaw', heading); write(a, 'heading', heading);
    }
  };
  const vectorProfile = (): void => {
    if (!processor) fail('reached8020ba78 requires explicit GQR0 float processor profile');
    if (word(processor, 'gqr0') !== 0) fail('GQR0 must explicitly select float load/store type0 scale0');
  };
  const pairStore = (destination: object, x: number, y: number): void => {
    // One psq_st XY cannot partially commit because its second host field is readonly.
    own(destination, 'x', true); check(); own(destination, 'y', true); check();
    (destination as {x: number}).x = x; check(); (destination as {y: number}).y = y; check();
  };
  const pairArithmetic = (a: object, b: object, destination: object, subtract: boolean): void => {
    const ax = f(a, 'x'), ay = f(a, 'y'), bx = f(b, 'x'), by = f(b, 'y');
    const x = addSourceFloat32(ax, subtract ? -bx : bx), y = addSourceFloat32(ay, subtract ? -by : by);
    pairStore(destination, x, y);
    const az = f(a, 'z'), bz = f(b, 'z');
    write(destination, 'z', addSourceFloat32(az, subtract ? -bz : bz));
  };
  const carry = (e: Entry): void => {
    vectorProfile();
    pairArithmetic(e.pos, e.history, e.motion, true); // actual8020ba78
    // actual8020ba9c captures XYZ before its XY store, unlike add/subtract.
    const x = f(e.motion, 'x'), y = f(e.motion, 'y'), z = f(e.motion, 'z');
    const scale = 0.949999988079071; // authenticated804392d0=3f733333
    pairStore(e.motion, float(Math.fround(x * scale), 'scaleX'), float(Math.fround(y * scale), 'scaleY'));
    write(e.motion, 'z', float(Math.fround(z * scale), 'scaleZ'));
    pairArithmetic(e.pos, e.motion, e.pos, false); // actual8020ba54
  };
  const phaseZero = (id: symbol, e: Entry): void => {
    const a = e.actual;
    write(a, 'fbPhase', (byte(a, 'fbPhase') + 1) & 255);
    if (target(a) === null) write(a, 'activeYaw', bam(a, 'heading'));
    nullTargetYaw(e);
    for (const key of ['gravityCoeff','yVel','hDecel','hSpeed','poseAccum80','poseAccum7e','poseAccum7c']) write(a, key, 0);
    carry(e);
    if (ground === undefined) fail('800ff30c reached unsupported actual800677b0 ground height/normal probe before config slots and stream start');
    call(() => ground.runActor(id)); // source ignores the genuine0/1 result
    // Signed configuration halfwords80433868/6a are fixed authenticated0/1.
    // The first6ea store precedes the fresh5e0 load even on the air branch.
    write(a, 'streamSlot', 0);
    if ((word(a, 'controlWord') & 0x40) !== 0) write(a, 'streamSlot', 1);
    const slot = signedByte(a, 'streamSlot');
    write(a, 'streamSlot', (slot + 1) & 255);
    if (call(() => streams.startStream(id, 15, 4, slot, -1, 0xffffffff, 0xffffffff)) !== undefined)
      fail('actual8004beb8 returned unexpectedly');
    write(a, 'accumulator80c', 0);
  };
  const fullRoot = (id: symbol, e: Entry): void => {
    expectTarget(word(e.prehook, 'pointer4b4'), 0x8006facc, '80065dfc actual4b4');
    expectTarget(selected('actions3b68', signedByte(e.actual, 'actionIndex')), 0x80071598, '8006facc action');
    expectTarget(selected('variants3c48', signedByte(e.actual, 'variantIndex')), 0x800715d4, '80071598 variant');
    // Actual715d4 supplies fixed r4 ADDRESS80433868 to the directff2bc call.
    // It is not a function-pointer cell. Config pointee is not read before677b0.
    if (byte(e.cue, 'byte541') !== 0) write(e.actual, 'visibilityTarget', null);
    expectTarget(selected('phases1f000', signedByte(e.actual, 'fbPhase')), 0x800ff30c, '800ff2bc phase');
    phaseZero(id, e);
  };
  const dispatch = (id: symbol, saved: SourceActorDoubleStateSelectors, upper: boolean): void => guard(() => {
    const e = entry(id); owners(id, e);
    const snapshot = snapshots.get(saved);
    if (!snapshot || snapshot.id !== id || pending.get(id) !== saved || snapshot.stage !== (upper ? 'upper' : 'full'))
      fail('saved selector capability missing, consumed or out of order');
    snapshot.stage = upper ? 'full' : 'done';
    try {
      const address = selected(upper ? 'upper37a8' : 'full36a8', upper ? saved.upper : saved.full);
      if (address === 0x8005f238) { /* authenticated bare return, no synthetic work */ }
      else if (!upper && address === 0x80065dfc) fullRoot(id, e);
      else fail(`${upper ? 'upper' : 'full'} state: unsupported target0x${address.toString(16)}`);
      check();
      if (!upper) pending.delete(id);
    } catch (error) {markIncompleteSourceActorDoubleLifecycle(e.actual); throw error;}
  });
  const runtime: SourceActorDoubleActionRuntime = {
    bindActor(id) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(call(() => prehook.getActualActor(id)), 'actual actor') as RomActor;
      if (claimed.has(actual)) fail('actual actor already claimed by a Double action runtime');
      const e: Entry = {actual, prehook: record(call(() => prehook.getActorBinding(id)), 'prehook binding'),
        mapping: record(call(() => attributes.getMappingActor(id)), 'mapping'), attribute: record(call(() => attributes.getActorBinding(id)), 'attribute'),
        cue: record(call(() => cues.getActorBinding(id)), 'cue'), dispatch: record(call(() => cues.getDispatchBinding(id)), 'dispatch'),
        pos: record(read(actual, 'pos'), 'position20'), motion: record(read(actual, 'motion'), 'motion38'),
        history: record(read(actual, 'targetCache5e8'), 'own history5e8')};
      const values = Object.values(e);
      if (new Set([...values, ...shared()]).size !== values.length + shared().length || values.some(value => assigned.has(value)))
        fail('Double action source owner alias');
      owners(id, e); actors.set(id, e); values.forEach(value => assigned.add(value)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getPrehookRuntime() {return prehook;}, getGroundRuntime() {return ground;},
    getPrehookBinding(id) {return entry(id).prehook;}, getMappingActor(id) {return entry(id).mapping;},
    getAttributeBinding(id) {return entry(id).attribute;}, getCueBinding(id) {return entry(id).cue;},
    getDispatchBinding(id) {return entry(id).dispatch;}, getTables() {return tables;},
    getSourceOwners(id) {return Object.freeze([...new Set([...Object.values(entry(id)), ...shared(), ...attributes.getKnownParameterDescriptors(),
      ...(ground === undefined ? [] : ground.getSourceOwners(id)),
      ...(ground === undefined ? [] : [streams.getStartActorBinding(id), streams.getActorBinding(id),
        ...[0,1,2,3].map(index => streams.getPartBinding(id, index))])])]);},
    assertActorComplete(id) {requireCompleteSourceActorDoubleLifecycle(entry(id).actual);},
    captureStateSelectors(id) {return guard(() => {
      const e = entry(id); owners(id, e);
      if (pending.has(id)) fail('previous saved selectors have not completed');
      const upper = state(e.actual, 'ubState'), full = state(e.actual, 'fbState');
      const saved = Object.freeze({upper, full}); snapshots.set(saved, {id, stage: 'upper'}); pending.set(id, saved); return saved;
    });},
    dispatchUpper(id, saved) {dispatch(id, saved, true);}, dispatchFull(id, saved) {dispatch(id, saved, false);},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
