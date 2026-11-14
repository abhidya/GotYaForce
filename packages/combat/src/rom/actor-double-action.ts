/** Bounded actual Double action2 dispatch, offline only.
 * Source:55568/65dfc/6facc/71598/715d4/ff2bc/ff30c/ff418 and6d144/669d0/66a30.
 * Exact instruction operands and vectors are authenticated by the fixed
 * read_archived_double_action_evidence.py and read_archived_phase1_entry_evidence.py
 * readers, not inferred from C order. See the Double action envelope evidence
 * and terrain-orientation-evidence-2026-11-13.md under research/decomp/.
 * Explicit decoded tables select numeric source functions, never host callbacks
 * or legacy Ninja streams. Only authenticated UB return, FB root, action2,
 * variant0 and bounded phase0/phase1 bodies are supported. Unknown targets
 * refuse when reached.
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
 * Phase1 calls the same genuine4cd24(mask15), then yaw, existing-motion scale/add
 * and677b0 before its signed part0.state1b load. Positive state increments540
 * then runs the actual nonnull715f8 callback: conditional part1 backflip stores,
 * genuine6dbe0 slot2 consumption and signed family dispatch. Successful Ninja
 * consumption reaches the optional genuine7db5c row1 runtime. Without it, the
 * historical boundary remains before Double7c8. Row1 completion precedes7c8;
 * nonzero7c8 reaches the unauthenticated row2 boundary before its allocation.
 * A returned callback reaches the explicit8020bb38 frsqrte boundary after the
 * authenticated8020bb14 square prefix. Its genuine zero-square return is
 * retained, never manufactured. Callback/ammo instruction order and constants:
 * the fixed read_archived_callback_ammo_evidence.py reader, not C expression order.
 * Both stream-part states stay on their retained genuine owners, never legacy
 * contact/dash fields. Source byte/float reads and writability remain lazy.
 * Float32 RN00/NI0, paired-single enablement and finite signed32 conversion are
 * host bounds, not observed processor configuration. Failed
 * operations retain prior stores and permanently latch the shared incomplete
 * Double lifecycle, so changed selectors cannot replay a partial handler.
 */
import {isSourceActorProjectileSpawnRuntime, bindSourceActorProjectileSpawnFrame, markIncompleteSourceActorProjectileSpawn, type SourceActorProjectileSpawnRuntime} from './actor-projectile-spawn.js';
import {isPendingSourceActorFrameClaim, type SourceActorFrameLifecycleRuntime} from './actor-frame-lifecycle.js';
import type {SourceActorTickFrameOwners} from './actor-tick-prefix.js';
import {isSourceActorGroundProbeRuntime, type SourceActorGroundProbeRuntime} from './actor-ground-probe.js';
import type {RomActor} from './actor.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32} from './source-float.js';
import {isSourceActorDoublePrehookRuntime, markIncompleteSourceActorDoubleLifecycle,
  requireCompleteSourceActorDoubleLifecycle, requireSourceActorDoubleInvocation, isSourceActorDoubleFrameAccess,
  type SourceActorDoubleFrameAccess, type SourceActorDoublePrehookRuntime} from './actor-double-prehook.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime} from './actor-cue-reset.js';
import {isSourceActorStatusTimersRuntime} from './actor-status-timers.js';

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
  /** Genuine8007db5c row1 continuation; absence preserves the historical boundary. */
  projectiles?: SourceActorProjectileSpawnRuntime;
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
  getProjectileRuntime(): SourceActorProjectileSpawnRuntime | undefined;
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
const frameBinders = new WeakMap<object, (id: symbol, access: SourceActorDoubleFrameAccess) => void>();
/** Internal join only; the access token is never returned by the action runtime. */
export function bindSourceActorDoubleActionFrame(frame: SourceActorFrameLifecycleRuntime,
  runtime: SourceActorDoubleActionRuntime, id: symbol, owners: SourceActorTickFrameOwners,
  access: SourceActorDoubleFrameAccess): void {
  if (!isPendingSourceActorFrameClaim(frame, id, owners) || !isSourceActorDoubleActionRuntime(runtime) ||
      runtime.getActualActor(id) !== owners.actual || !isSourceActorDoubleFrameAccess(access, owners.actual))
    fail('action frame join requires private genuine frame binding');
  const bind = frameBinders.get(runtime); if (!bind) fail('genuine action frame binder missing'); bind(id, access);
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
  const projectiles = Object.getOwnPropertyDescriptor(sources, 'projectiles') === undefined ? undefined : own(sources, 'projectiles');
  if (projectiles !== undefined && !isSourceActorProjectileSpawnRuntime(projectiles)) fail('genuine source projectile spawn runtime required');
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
  const half = (owner: unknown, key: string): number => integer(read(owner, key), -32768, 32767, key);
  const f = (owner: unknown, key: string): number => float(read(owner, key), key);
  const word = (owner: unknown, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const s16 = (value: number): number => value << 16 >> 16;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: canonical owner changed or differs`);
  };
  interface Entry {actual: RomActor; prehook: object; mapping: object; attribute: object; cue: object; dispatch: object;
    pos: object; motion: object; history: object;
    start: object; wait: object; part0: object; part1: object; part2: object; part3: object}
  const shared = (): object[] => [tables, ...Object.values(arrays), ...(processor ? [processor] : [])];
  const parameters = new Set<object>();
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const ammoOwners = new Map<symbol, {slot: object; cell: object}>();
  const snapshots = new WeakMap<object, {id: symbol; stage: 'upper' | 'full' | 'done'}>();
  const pending = new Map<symbol, SourceActorDoubleStateSelectors>();
  const frameAccesses = new Map<symbol, SourceActorDoubleFrameAccess>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned Double action actor'); return e;};
  const noShadows = (e: Entry, extras: readonly object[] = []): void => {
    const canonical = new Map<string, object>([
      ...['fbPhase','actionIndex','variantIndex','ubState','fbState','visibilityTarget','activeYaw','turnErrorYaw','heading','lockYaw',
        'hSpeed','yVel','hDecel','gravityCoeff','borgNumber','poseAccum80','poseAccum7e','poseAccum7c','pos','motion','targetCache5e8','streamSlot','accumulator80c','byte6e8','byte6e9','controlWord'].map(key => [key,e.actual] as [string, object]),
      ['byte541', e.cue], ['pointer4b4', e.prehook], ['pointer4bc', e.prehook], ['pointer4c0', e.prehook],
      ['parameter4ac', e.attribute], ['timestep1dc8', e.mapping], ['marker578', e.dispatch],
      ...['familyBank1d80','sharedBank1d84','defaultSelector582','marker709'].map(key => [key,e.start] as [string, object]),
      ...['activeMask579','blockedMask1d9a','marker71d'].map(key => [key,e.wait] as [string, object]),
    ]);
    const parts = [e.part0, e.part1, e.part2, e.part3];
    const owners = [...Object.values(e), ...shared(), ...extras];
    for (const owner of owners) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing source storage owner`);
        check();
      }
      for (const key of ['state1b', 'auxiliary1c']) {
        if (!parts.includes(owner) && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing source stream-part storage owner`);
        check();
      }
      if (!parameters.has(owner) && Object.getOwnPropertyDescriptor(owner, 'fieldAe') !== undefined)
        fail('fieldAe: competing parameter4ac storage owner');
      check();
      for (const key of ['byte540','phase540','byte580','action580','byte581','variant581','byte5da','byte5db','pointerCC','pointercc',
        'field4ac','pointer4ac','field1dc8','phaseSlots','fbPhaseSlots','lockTarget',
        'byte1cef','state1cef','field1cef','byte1cf0','auxiliary1cf0','field1cf0',
        'byte1d0f','state1d0f','field1d0f','byte1d10','auxiliary1d10','field1d10']) {
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
    stable(call(() => streams.getStartActorBinding(id)), e.start, 'source stream start');
    stable(call(() => prehook.getStartBinding(id)), e.start, 'prehook stream start');
    stable(call(() => streams.getActorBinding(id)), e.wait, 'source stream wait');
    stable(call(() => streams.getMappingActor(id)), e.mapping, 'source stream mapping');
    for (const [index, part] of [e.part0, e.part1, e.part2, e.part3].entries())
      stable(call(() => streams.getPartBinding(id, index)), part, `source stream part${index}`);
    if (call(() => streams.hasActualActorBinding(id))) {
      stable(call(() => streams.getActualActor(id)), e.actual, 'source stream actual');
      stable(call(() => streams.getMappingActor(id)), e.mapping, 'source stream mapping');
    }
    if (ground !== undefined) {
      stable(call(() => ground.getActualActor(id)), e.actual, 'ground actual');
      stable(call(() => ground.getWorldBinding(id)), call(() => prehook.getWorldBinding(id)), 'ground world');
      stable(call(() => ground.getStatusBinding(id)), call(() => prehook.getStatusBinding(id)), 'ground status');
      noShadows(e, call(() => ground.getSourceOwners(id)));
    }
    if (projectiles !== undefined) {
      stable(call(() => projectiles.getActualActor(id)),e.actual,'projectile actual');
      stable(call(() => projectiles.getPrehookRuntime()),prehook,'projectile prehook');
      stable(call(() => projectiles.getCueRuntime()),cues,'projectile cues');
      call(() => projectiles.assertActorComplete(id));
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
  const vectorProfile = (site: string): void => {
    if (!processor) fail(`reached${site} requires explicit GQR0 float processor profile`);
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
  const scaleAndAdd = (e: Entry): void => {
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
    vectorProfile('8020ba78');
    pairArithmetic(e.pos, e.history, e.motion, true); // actual8020ba78, phase0 only
    scaleAndAdd(e);
    if (ground === undefined) fail('800ff30c reached unsupported actual800677b0 ground height/normal probe before config slots and stream start');
    const access = frameAccesses.get(id);
    call(() => access === undefined ? ground.runActor(id) : access.invoke('ground', ground, () => ground.runActor(id))); // source ignores0/1
    // Signed configuration halfwords80433868/6a are fixed authenticated0/1.
    // The first6ea store precedes the fresh5e0 load even on the air branch.
    write(a, 'streamSlot', 0);
    if ((word(a, 'controlWord') & 0x40) !== 0) write(a, 'streamSlot', 1);
    const slot = signedByte(a, 'streamSlot');
    write(a, 'streamSlot', (slot + 1) & 255);
    const start = () => streams.startStream(id, 15, 4, slot, -1, 0xffffffff, 0xffffffff);
    if (call(() => access === undefined ? start() : access.invoke('stream', streams, start)) !== undefined)
      fail('actual8004beb8 returned unexpectedly');
    write(a, 'accumulator80c', 0);
  };
  const motionMagnitude = (motion: object): number => {
    // Authenticated8020bb14/68: XY load and paired products precede Z load.
    // W1 supplies1 in the second Z lane. All paired arithmetic executes even
    // where its second lane is unused. RN00/NI0 and finite f32 remain bounds.
    vectorProfile('8020bb14');
    const x = f(motion, 'x'), y = f(motion, 'y');
    const xx = float(Math.fround(x * x), '8020bb1c squareX');
    const yy = float(Math.fround(y * y), '8020bb1c squareY');
    const z = f(motion, 'z');
    const zero = addSourceFloat32(0.5, -0.5); // authenticated8043ca90, bb24
    const zx = fusedMultiplyAddSourceFloat32(z, z, xx);
    fusedMultiplyAddSourceFloat32(1, 1, yy); // second ps_madd lane, bb28
    const square = addSourceFloat32(zx, yy); // ps_sum0, bb2c
    if (square === zero) return square; // source bb30/34 -> bb54 bare return
    fail('800ff418 reached unsupported actual8020bb14 motion magnitude at8020bb38 frsqrte numerical boundary before threshold804392c8 and conditional800b22f4');
  };
  const consumeCallbackAmmo = (id: symbol, e: Entry): boolean => {
    // The actual fixed call is6dbe0(actor,2,1,1). Do not substitute the legacy
    // allocator's callback/default success or its max0 unlimited convention.
    // The genuine status runtime retains784/786/788/7a0/7a2 on this same cell.
    const status = call(() => prehook.getStatusRuntime());
    if (!isSourceActorStatusTimersRuntime(status)) fail('actual8006dbe0 requires genuine status runtime');
    stable(call(() => status.getActualActor(id)), e.actual, 'ammo actual');
    stable(call(() => status.getMappingActor(id)), e.mapping, 'ammo mapping');
    stable(call(() => status.getWorldBinding(id)), call(() => prehook.getWorldBinding(id)), 'ammo world');
    stable(call(() => status.getActorBinding(id)), call(() => prehook.getStatusBinding(id)), 'ammo status');
    stable(call(() => status.getAttributeBinding(id)), e.attribute, 'ammo attribute');
    stable(call(() => status.getStartBinding(id)), e.start, 'ammo stream start');
    const slot = record(call(() => status.getAmmoSlot(id, 2)), 'source slot2'), cell = record(read(slot, 'cell'), 'source slot2 cell');
    const existing = [...Object.values(e), ...shared(), ...call(() => attributes.getKnownParameterDescriptors()),
      ...call(() => prehook.getSourceOwners(id)), ...(ground === undefined ? [] : call(() => ground.getSourceOwners(id)))];
    const prior = ammoOwners.get(id);
    if (prior !== undefined) {
      stable(slot, prior.slot, 'source slot2'); stable(cell, prior.cell, 'source slot2 cell');
    } else {
      if (slot === cell || existing.includes(slot) || existing.includes(cell)) fail('source slot2 owner alias');
      ammoOwners.set(id, {slot, cell});
    }
    noShadows(e, [slot, cell]); // identity/storage admission, never an ammo scalar load
    // Metadata-only exclusions are local to this reached slot2. Other actual
    // source slots legitimately have their own cur/timer/etc, so do not inspect
    // them or demand any of their fields here.
    for (const owner of [...existing, slot, cell]) {
      for (const key of ['cur','timer','refillType','refillParam','mirror776']) {
        const expected = key === 'mirror776' ? slot : cell;
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing slot2 source storage owner`);
        check();
      }
      for (const key of ['byte784','short784','field784','cur784','byte786','short786','field786','mirror786',
        'float788','field788','timer788','short7a0','field7a0','refillType7a0','short7a2','field7a2','refillParam7a2']) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined) fail(`${key}: competing slot2 source storage alias`);
        check();
      }
    }
    const current = half(cell, 'cur'); //6dbec lha; signed comparison against1
    if (current < 1) return false;
    write(slot, 'mirror776', current); //6dc10 keeps the initially captured count
    write(cell, 'cur', s16(half(cell, 'cur') - 1)); //6dc14 reload,6dc1c sth
    const mode = half(cell, 'refillType'); //6dc20, after both stores
    if (mode === 1) {
      const parameter = half(cell, 'refillParam'); //6dc7c precedes old timer load
      const timer = f(cell, 'timer'); //6dc94, before conversion subtraction
      //804376a0's signed-half conversion is exact; fsubs rounds to the same f32.
      write(cell, 'timer', addSourceFloat32(timer, parameter)); //6dca0/4
    } else if (mode === 0) {
      if (half(cell, 'cur') === 0) { //6dc48 fresh post-debit lha
        const parameter = half(cell, 'refillParam');
        write(cell, 'timer', parameter); //6dc70/74 exact signed-half conversion
      }
    } else if (mode === 2 || mode === 3) write(cell, 'timer', 0); //80437658 +0
    return true; // negative and >=4 modes genuinely skip timer/parameter reads
  };
  const throwCallback = (id: symbol, e: Entry): void => {
    // Authenticated715f8, fixed8043386c; the part1 lbz/extsb tests nonzero.
    // The four constants are41200000/00000000/41700000/bf800000 respectively.
    if (signedByte(e.part1, 'state1b') !== 0) {
      const heading = s16(bam(e.actual, 'heading')); //71618 lha
      write(e.actual, 'lockYaw', (heading - 0x8000) & 65535); //71630 sth
      write(e.actual, 'hSpeed', 10); write(e.actual, 'hDecel', 0);
      write(e.actual, 'yVel', 15); write(e.actual, 'gravityCoeff', -1);
    }
    if (!consumeCallbackAmmo(id, e)) return;
    const borg = s16(bam(e.actual, 'borgNumber')); //71664 lha only after success
    if (borg === 0 || borg === 3 || borg === 10) {
      const variant = borg === 0 ? 0 : borg === 3 ? 1 : 3;
      // Double's optional second variant2 and7c8 load are AFTER variant1 returns.
      // No clone owner is read or manufactured before this genuine first call.
      if (projectiles === undefined)
        fail(`800715f8 reached unsupported actual8007db5c projectile variant${variant} after genuine8006dbe0 consumption`);
      const access = frameAccesses.get(id), spawn = (selected: number) => projectiles.spawn(id,selected);
      call(() => access === undefined ? spawn(variant) : access.invoke('projectile',projectiles,() => spawn(variant)));
      if (borg === 3) {
        // Actual7169c reads current7c8 only after the complete variant1 return.
        const clone = call(() => prehook.getCloneOwner(id));
        if (clone === undefined) fail('actual7c8 requires existing explicit persistent clone owner');
        if (byte(clone,'arm7c8') !== 0)
          call(() => access === undefined ? spawn(2) : access.invoke('projectile',projectiles,() => spawn(2)));
      }
    }
  };
  const phaseOne = (id: symbol, e: Entry): void => {
    const a = e.actual, access = frameAccesses.get(id);
    // Host identity admission is lazy at this reached source call. It also
    // enables the stream runtime's private stage and permanent failure guards.
    if (!call(() => streams.hasActualActorBinding(id)))
      fail('800ff418 reached actual8004cd24 without genuine stream actual-actor join');
    stable(call(() => streams.getActualActor(id)), a, 'phase1 stream actual');
    stable(call(() => streams.getMappingActor(id)), e.mapping, 'phase1 stream mapping');
    const update = () => streams.update(id, 15);
    call(() => access === undefined ? update() : access.invoke('stream', streams, update)); // source ignores0/1
    owners(id, e); // identity-only admission after executable stream continuation
    nullTargetYaw(e); // actual8006d144(actor,c1); no phase0 active-yaw initialization
    vectorProfile('8020ba9c');
    scaleAndAdd(e); // existing motion38, never pos-history subtraction
    if (ground === undefined) fail('800ff418 reached unsupported actual800677b0 ground height/normal probe before signed part0 state');
    call(() => access === undefined ? ground.runActor(id) : access.invoke('ground', ground, () => ground.runActor(id)));
    if (signedByte(e.part0, 'state1b') > 0) {
      write(a, 'fbPhase', (byte(a, 'fbPhase') + 1) & 255);
      // Actual715d4 retains fixed config80433868. Its authenticated+4 word is
      // nonnull800715f8, not an injectable callback or a nullable fixture knob.
      throwCallback(id, e);
    }
    // ff4a4 always reads current motion after the optional callback returns.
    // No positive state bypasses its earlier nonnull callback. The restricted
    // matrix-axis estimator is not a general-motion implementation.
    const magnitude = motionMagnitude(e.motion);
    if (magnitude > 3) // authenticated804392c8=40400000, after magnitude returns
      fail('800ff418 reached unsupported actual800b22f4 afterimage effect');
  };
  const fullRoot = (id: symbol, e: Entry): void => {
    expectTarget(word(e.prehook, 'pointer4b4'), 0x8006facc, '80065dfc actual4b4');
    expectTarget(selected('actions3b68', signedByte(e.actual, 'actionIndex')), 0x80071598, '8006facc action');
    expectTarget(selected('variants3c48', signedByte(e.actual, 'variantIndex')), 0x800715d4, '80071598 variant');
    // Actual715d4 supplies fixed r4 ADDRESS80433868 to the directff2bc call.
    // It is not a function-pointer cell. Config pointee is not read before677b0.
    if (byte(e.cue, 'byte541') !== 0) write(e.actual, 'visibilityTarget', null);
    const phase = selected('phases1f000', signedByte(e.actual, 'fbPhase'));
    if (phase === 0x800ff30c) phaseZero(id, e);
    else if (phase === 0x800ff418) phaseOne(id, e);
    else fail(`800ff2bc phase: unsupported target0x${phase.toString(16)}`);
  };
  const dispatch = (id: symbol, saved: SourceActorDoubleStateSelectors, upper: boolean): void => guard(() => {
    const e = entry(id); requireSourceActorDoubleInvocation(e.actual, upper ? 'upper' : 'full', runtime); owners(id, e);
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
    } catch (error) {
      markIncompleteSourceActorDoubleLifecycle(e.actual);
      if (projectiles !== undefined) markIncompleteSourceActorProjectileSpawn(projectiles,id);
      throw error;
    }
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
        history: record(read(actual, 'targetCache5e8'), 'own history5e8'),
        start: record(call(() => streams.getStartActorBinding(id)), 'stream start'),
        wait: record(call(() => streams.getActorBinding(id)), 'stream wait'),
        part0: record(call(() => streams.getPartBinding(id, 0)), 'stream part0'),
        part1: record(call(() => streams.getPartBinding(id, 1)), 'stream part1'),
        part2: record(call(() => streams.getPartBinding(id, 2)), 'stream part2'),
        part3: record(call(() => streams.getPartBinding(id, 3)), 'stream part3')};
      const values = Object.values(e);
      if (new Set([...values, ...shared()]).size !== values.length + shared().length || values.some(value => assigned.has(value)))
        fail('Double action source owner alias');
      owners(id, e); actors.set(id, e); values.forEach(value => assigned.add(value)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getPrehookRuntime() {return prehook;}, getGroundRuntime() {return ground;}, getProjectileRuntime() {return projectiles;},
    getPrehookBinding(id) {return entry(id).prehook;}, getMappingActor(id) {return entry(id).mapping;},
    getAttributeBinding(id) {return entry(id).attribute;}, getCueBinding(id) {return entry(id).cue;},
    getDispatchBinding(id) {return entry(id).dispatch;}, getTables() {return tables;},
    getSourceOwners(id) {return Object.freeze([...new Set([...Object.values(entry(id)), ...shared(), ...attributes.getKnownParameterDescriptors(),
      ...(ammoOwners.has(id) ? Object.values(ammoOwners.get(id)!) : []),
      ...(ground === undefined ? [] : ground.getSourceOwners(id)),
      ...(projectiles === undefined ? [] : projectiles.getSourceOwners(id))])]);},
    assertActorComplete(id) {requireCompleteSourceActorDoubleLifecycle(entry(id).actual);},
    captureStateSelectors(id) {return guard(() => {
      const e = entry(id); requireSourceActorDoubleInvocation(e.actual, 'capture', runtime); owners(id, e);
      if (pending.has(id)) fail('previous saved selectors have not completed');
      const upper = state(e.actual, 'ubState'), full = state(e.actual, 'fbState');
      const saved = Object.freeze({upper, full}); snapshots.set(saved, {id, stage: 'upper'}); pending.set(id, saved); return saved;
    });},
    dispatchUpper(id, saved) {dispatch(id, saved, true);}, dispatchFull(id, saved) {dispatch(id, saved, false);},
  };
  runtimes.add(runtime);
  frameBinders.set(runtime, (id, access) => {entry(id); if (frameAccesses.has(id)) fail('action already has a frame binding'); frameAccesses.set(id, access);
    if (projectiles !== undefined) bindSourceActorProjectileSpawnFrame(runtime,projectiles,id,access);
  });
  return Object.freeze(runtime);
}
