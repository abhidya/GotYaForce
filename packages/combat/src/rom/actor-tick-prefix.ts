/** Offline bounded actual80059068, not a complete enclosing actor frame.
 * Archived entry: lfs760/B4,fdivs,stfs760 @5907c..59088; fresh
 * lfs764/B4,fdivs,stfs764 @5908c..59098; real5bab8 @5909c;67a70
 * @590a4; optionally genuine bounded59e58 @590ac. 67a70 clears control5e0 bit00100000
 * then byte598, and only its zero-contact1db branch genuinely returns here.
 * Nonzero contact refuses at the existing unsupported1e4 owner, not a shadow
 * pointer. Without stageBounds,59e58 remains the historical refusal. With the
 * genuine stage runtime it either refuses a reached cue or returns to the
 * next685c0 @590b4. Optional genuine inputPrefix advances its admitted
 * angular/input/ten-machine/charge path. Absent inputPrefix retains historical
 * 685c0 refusal; a genuine return reaches the next5a190 call @590bc. Optional
 * genuine actorControl admits its returned-zero gates/countdowns, then reaches
 * signed actual5e4 table dispatch @590e0/590e8. Without normalLifecycle this
 * remains the historical refusal. An explicitly bound genuine ready transition may
 * instead return1, skipping the two indirect calls and59f5c/5a144. That path
 * reaches5a298 @59110; optional genuine actionRequest admits its bounded
 * returns, then reaches5a378 @59118. Optional genuine actorRates performs
 * rate/status/clock writes on the same owners, then reaches68030 @59120.
 * Optional genuine ceiling supplies that final helper and its8b290 leaf, with
 * shared stage and reconciled matrix/charge match globals; this admitted branch
 * then genuinely returns void. Optional normalLifecycle supplies authenticated
 * cue9, actual4c8 and bounded59f5c/5a144 before that same common tail. Missing
 * normalLifecycle retains the historical table refusal. Incomplete6bc expiry
 * refuses all later ticks before their first mutation, including ready bypasses.
 * Optional normal rotation damping supplies the genuine active movement body
 * on existing correction owners. Partial damping is likewise guarded, and
 * its retained storage is excluded from raw input aliases.
 * No source call is skipped and no callback stands in for a callee. Completion
 * of this branch does not execute55568 or claim a full actor frame/playability.
 *
 * An explicit externally decoded/synthetic raw-input boundary writes the
 * actual actor.targetDistance760 (full3D) and horizontalDistance764 (XZ).
 * It does NOT implement/authenticate6ae60/6bda8, target capture, sqrt, or the
 * no-target constant. Its ordered ingestion stores are HOST boundary effects,
 * not claimed source instructions. It never implicitly adopts old bridge data.
 * The tag asserts a boundary, not provenance: a caller copying normalized data
 * into a new input cannot be detected. Production stays closed until the real
 * producer/provenance and exclusive lifecycle are supplied.
 * A nonnegative increasing safe-integer epoch identifies this pre59068 input
 * refresh only, not all later raw writes (command6a104 may capture again).
 * Each attempted epoch is consumed before ingestion and retained on failure.
 * Binding permanently claims the actor against legacy bridge.syncIn: there
 * is no fallback/unclaim without a future explicit retirement lifecycle.
 *
 * Non-proxy own-data records, stable synchronous owners, finite exact binary32
 * operands and RN00/NI0 are bounds, not observed hardware state. Exact rational
 * nearest-even division retains subnormals/signed zero; zero divisors and
 * rounded overflow refuse. Checks are lazy; all completed effects are retained.
 * Optional cue0 performs real bounded position correction; its unfinished
 * calls block all later branches before raw ingress. No general movement,
 * matrix rebuild, animation advance, legacy step or production activation.
 */
import {isSourceActorCue0LifecycleRuntime, hasIncompleteSourceActorCue0Lifecycle,
  type SourceActorCue0LifecycleRuntime} from './actor-cue0-lifecycle.js';
import type {RomActor} from './actor.js';
import {isSourceActorCommandAdmissionRuntime, hasIncompleteSourceActorCommandAdmission,
  type SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import {isSourceActorCue0TailRuntime, hasIncompleteSourceActorCue0Tail,
  type SourceActorCue0TailRuntime} from './actor-cue0-tail.js';
import {isSourceActorInputTestersRuntime, hasIncompleteSourceActorInputTesters,
  type SourceActorInputTestersRuntime} from './actor-input-testers.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeBorgOwner,
  type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {isSourceActorStageBoundsRuntime, type SourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import {isSourceActorInputPrefixRuntime, type SourceActorInputPrefixRuntime} from './actor-input-prefix.js';
import {isSourceActorControlLifecycleRuntime, type SourceActorControlLifecycleRuntime} from './actor-control-lifecycle.js';
import {isSourceActorReadyTransitionsRuntime, type SourceActorReadyTransitionsRuntime} from './actor-ready-transitions.js';
import {isSourceActorActionRequestRuntime, type SourceActorActionRequestRuntime} from './actor-action-request.js';
import {isSourceActorRateLifecycleRuntime, type SourceActorRateLifecycleRuntime} from './actor-rate-lifecycle.js';
import {isSourceActorCeilingLifecycleRuntime, type SourceActorCeilingLifecycleRuntime} from './actor-ceiling-lifecycle.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime} from './actor-input-charge.js';
import {isSourceActorTierLifecycleRuntime, type SourceActorTierLifecycleRuntime} from './actor-tier-lifecycle.js';
import {isSourceActorNormalLifecycleRuntime, hasIncompleteSourceActorNormalCountdown, hasIncompleteSourceActorNormalCueSync,
  type SourceActorNormalLifecycleRuntime} from './actor-normal-lifecycle.js';
import type {SourceActorCueResetRuntime} from './actor-cue-reset.js';
import {isSourceActorRotationDampingRuntime, hasIncompleteSourceActorRotationDamping,
  type SourceActorRotationDampingRuntime} from './actor-rotation-damping.js';

export interface SourceActorTickPrefixBinding {byte598: number}
export interface SourceActorTickRawDistances {
  readonly boundary: 'externally-decoded-pre59068-raw';
  readonly targetDistance760: number;
  readonly horizontalDistance764: number;
}
export interface SourceActorTickPrefixSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'> &
    Partial<Pick<SourceActorWorldMatrixRuntime, 'getMappingActor'>>;
  gauges: SourceActorGaugeScaleRuntime;
  /** Optional genuine59e58. Without it the historical refusal is unchanged. */
  stageBounds?: SourceActorStageBoundsRuntime;
  /** Optional genuine685c0 prefix; absent retains historical refusal. */
  inputPrefix?: SourceActorInputPrefixRuntime;
  /** Optional genuine5a190 gates/countdowns; absent retains its historical refusal. */
  actorControl?: SourceActorControlLifecycleRuntime;
  /** Genuine control-zero cue/4c8/59f5c/5a144 continuation; missing retains table refusal. */
  normalLifecycle?: SourceActorNormalLifecycleRuntime;
  /** Common tail reached after either genuine control branch completes. */
  actionRequest?: SourceActorActionRequestRuntime;
  /** Optional genuine5a378 writing existing rate/status/mapping owners. */
  actorRates?: SourceActorRateLifecycleRuntime;
  /** Genuine final68030, with reconciled shared match and stage globals. */
  ceiling?: SourceActorCeilingLifecycleRuntime;
}
export interface SourceActorTickPrefixRuntime {
  bindActor(identity: symbol, actualBorg: SourceActorGaugeBorgOwner,
    initial: Readonly<Partial<SourceActorTickPrefixBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorGaugeBorgOwner;
  getActorBinding(identity: symbol): Partial<SourceActorTickPrefixBinding>;
  /** A fully admitted ready or normal branch returns source void; other reached gaps refuse.
   * This does not execute the enclosing actor frame or produce raw target inputs. */
  ingestRawDistancesAndRun(identity: symbol, epoch: number, raw: SourceActorTickRawDistances): void;
}
const claimedActors = new WeakSet<object>();
/** Genuine permanent claim, not a mutable property a bridge adapter can copy. */
export function isSourceActorTickPrefixClaimedActor(value: unknown): boolean {
  return value !== null && typeof value === 'object' && claimedActors.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-tick-prefix] ${reason}; offline execution aborted, prior writes/effects and consumed epoch are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
const floatBits = new DataView(new ArrayBuffer(4));
function dyadic(value: number): {mantissa: bigint; exponent: number; negative: boolean} {
  floatBits.setFloat32(0, value, false);
  const bits = floatBits.getUint32(0, false), e = (bits >>> 23) & 255;
  return {mantissa: BigInt((bits & 0x7fffff) | (e === 0 ? 0 : 0x800000)),
    exponent: e === 0 ? -149 : e - 150, negative: (bits >>> 31) !== 0};
}
/** Same bounded exact rational construction as actor-terrain-query. Kept local
 * rather than exporting its terrain runtime or widening source-float's API.
 * floor(log2(exact quotient)) sets a 24-bit quantum, capped at2^-149.
 * Integer quotient/remainder resolve ties to even without a binary64 divide. */
function div32(a: number, b: number): number {
  const x = dyadic(a), y = dyadic(b), negative = x.negative !== y.negative;
  if (y.mantissa === 0n) fail('fdivs zero divisor outside finite domain');
  if (x.mantissa === 0n) return negative ? -0 : 0;
  let power = x.mantissa.toString(2).length - y.mantissa.toString(2).length;
  if (power >= 0 ? x.mantissa < (y.mantissa << BigInt(power)) :
    (x.mantissa << BigInt(-power)) < y.mantissa) power--;
  const exponent = x.exponent - y.exponent;
  const quantum = Math.max(-149, power + exponent - 23), shift = exponent - quantum;
  const numerator = shift >= 0 ? x.mantissa << BigInt(shift) : x.mantissa;
  const denominator = shift < 0 ? y.mantissa << BigInt(-shift) : y.mantissa;
  let rounded = numerator / denominator;
  const twiceRemainder = (numerator % denominator) * 2n;
  if (twiceRemainder > denominator || (twiceRemainder === denominator && (rounded & 1n) !== 0n)) rounded++;
  return float((negative ? -1 : 1) * Number(rounded) * 2 ** quantum, 'fdivs result');
}
export function createSourceActorTickPrefixRuntime(sources: SourceActorTickPrefixSources): SourceActorTickPrefixRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const gauges = own(sources, 'gauges');
  if (!isSourceActorGaugeScaleRuntime(gauges)) fail('gauge stage requires the genuine source runtime, not callback effects');
  const capture = (name: keyof SourceActorTickPrefixSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const result = Reflect.apply(fn, receiver, [id]); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const gaugeActor = capture('gauges', 'getActualActor'), gaugeBorg = capture('gauges', 'getActualBorg');
  const gaugeStatus = capture('gauges', 'getStatusBinding'), gaugeBinding = capture('gauges', 'getActorBinding');
  const updateGauge = capture('gauges', 'updateActor');
  const gaugeTiers = capture('gauges', 'getTierLifecycleRuntime');
  const stage = Object.getOwnPropertyDescriptor(sources, 'stageBounds');
  if (stage !== undefined && !isSourceActorStageBoundsRuntime(read(sources, 'stageBounds')))
    fail('stage bounds require the genuine source runtime, not callback effects');
  const stageActor = stage === undefined ? undefined : capture('stageBounds', 'getActualActor');
  const stageWorld = stage === undefined ? undefined : capture('stageBounds', 'getWorldBinding');
  const stageStatus = stage === undefined ? undefined : capture('stageBounds', 'getStatusBinding');
  const stageBinding = stage === undefined ? undefined : capture('stageBounds', 'getActorBinding');
  const updateStage = stage === undefined ? undefined : capture('stageBounds', 'updateActor');
  const input = Object.getOwnPropertyDescriptor(sources, 'inputPrefix');
  if (input !== undefined && !isSourceActorInputPrefixRuntime(read(sources, 'inputPrefix')))
    fail('input prefix requires the genuine source runtime, not callback effects');
  const inputActor = input === undefined ? undefined : capture('inputPrefix', 'getActualActor');
  const inputBorg = input === undefined ? undefined : capture('inputPrefix', 'getActualBorg');
  const inputBinding = input === undefined ? undefined : capture('inputPrefix', 'getActorBinding');
  const updateInput = input === undefined ? undefined : capture('inputPrefix', 'updateActor');
  const control = Object.getOwnPropertyDescriptor(sources, 'actorControl');
  if (control !== undefined && !isSourceActorControlLifecycleRuntime(read(sources, 'actorControl')))
    fail('actor control requires the genuine source runtime, not callback effects');
  const controlActor = control === undefined ? undefined : capture('actorControl', 'getActualActor');
  const controlWorld = control === undefined ? undefined : capture('actorControl', 'getWorldBinding');
  const controlStatus = control === undefined ? undefined : capture('actorControl', 'getStatusBinding');
  const controlBinding = control === undefined ? undefined : capture('actorControl', 'getActorBinding');
  const controlReady = control === undefined ? undefined : capture('actorControl', 'getReadyRuntime');
  const updateControl = control === undefined ? undefined : capture('actorControl', 'updateActor');
  const normal = Object.getOwnPropertyDescriptor(sources, 'normalLifecycle');
  if (normal !== undefined && !isSourceActorNormalLifecycleRuntime(read(sources, 'normalLifecycle')))
    fail('normal lifecycle requires the genuine source runtime, not callback effects');
  const normalActor = normal === undefined ? undefined : capture('normalLifecycle', 'getActualActor');
  const normalWorld = normal === undefined ? undefined : capture('normalLifecycle', 'getWorldBinding');
  const normalStatus = normal === undefined ? undefined : capture('normalLifecycle', 'getStatusBinding');
  const normalMapping = normal === undefined ? undefined : capture('normalLifecycle', 'getMappingActor');
  const normalWorldMapping = normal === undefined ? undefined : capture('world', 'getMappingActor');
  const normalMovement = normal === undefined ? undefined : capture('normalLifecycle', 'getMovementBinding');
  const normalBinding = normal === undefined ? undefined : capture('normalLifecycle', 'getActorBinding');
  const normalCues = normal === undefined ? undefined : capture('normalLifecycle', 'getCueRuntime');
  const normalRotation = normal === undefined ? undefined : capture('normalLifecycle', 'getRotationRuntime');
  const normalCue0 = normal === undefined ? undefined : capture('normalLifecycle', 'getCue0Runtime');
  const normalCueBinding = normal === undefined ? undefined : capture('normalLifecycle', 'getCueBinding');
  const normalDispatch = normal === undefined ? undefined : capture('normalLifecycle', 'getDispatchBinding');
  const stageCues = normal === undefined || stage === undefined ? undefined : capture('stageBounds', 'getCueRuntime');
  const updateNormal = normal === undefined ? undefined : capture('normalLifecycle', 'updateActor');
  const assertNormalComplete = normal === undefined ? undefined : capture('normalLifecycle', 'assertActorComplete');
  const action = Object.getOwnPropertyDescriptor(sources, 'actionRequest');
  if (action !== undefined && !isSourceActorActionRequestRuntime(read(sources, 'actionRequest')))
    fail('action request requires the genuine source runtime, not callback effects');
  const actionRuntime = action === undefined ? undefined : read(sources, 'actionRequest');
  const actionActor = action === undefined ? undefined : capture('actionRequest', 'getActualActor');
  const actionWorld = action === undefined ? undefined : capture('actionRequest', 'getWorldBinding');
  const actionBinding = action === undefined ? undefined : capture('actionRequest', 'getActorBinding');
  const updateAction = action === undefined ? undefined : capture('actionRequest', 'updateActor');
  const rates = Object.getOwnPropertyDescriptor(sources, 'actorRates');
  if (rates !== undefined && !isSourceActorRateLifecycleRuntime(read(sources, 'actorRates')))
    fail('actor rates require the genuine source runtime, not callback effects');
  const rateActor = rates === undefined ? undefined : capture('actorRates', 'getActualActor');
  const rateBorg = rates === undefined ? undefined : capture('actorRates', 'getActualBorg');
  const rateWorld = rates === undefined ? undefined : capture('actorRates', 'getWorldBinding');
  const rateStatus = rates === undefined ? undefined : capture('actorRates', 'getStatusBinding');
  const rateMapping = rates === undefined ? undefined : capture('actorRates', 'getMappingActor');
  const rateBinding = rates === undefined ? undefined : capture('actorRates', 'getActorBinding');
  const rateMatrix = rates === undefined ? undefined : capture('actorRates', 'getMatrixBinding');
  const worldMapping = rates === undefined ? undefined : capture('world', 'getMappingActor');
  const updateRates = rates === undefined ? undefined : capture('actorRates', 'updateActor');
  const ceiling = Object.getOwnPropertyDescriptor(sources, 'ceiling');
  if (ceiling !== undefined && !isSourceActorCeilingLifecycleRuntime(read(sources, 'ceiling')))
    fail('ceiling requires the genuine source runtime, not callback effects');
  if (ceiling !== undefined && (stage === undefined || input === undefined))
    fail('ceiling completion requires the same genuine stage and input owners');
  const ceilingActor = ceiling === undefined ? undefined : capture('ceiling', 'getActualActor');
  const ceilingWorld = ceiling === undefined ? undefined : capture('ceiling', 'getWorldBinding');
  const ceilingMapping = ceiling === undefined ? undefined : capture('ceiling', 'getMappingActor');
  const ceilingMatrix = ceiling === undefined ? undefined : capture('ceiling', 'getMatrixBinding');
  const ceilingTerrain = ceiling === undefined ? undefined : capture('ceiling', 'getTerrainGlobals');
  const ceilingGlobals = ceiling === undefined ? undefined : capture('ceiling', 'getMatchGlobals');
  const stageTerrain = stage === undefined ? undefined : capture('stageBounds', 'getTerrainGlobals');
  const inputCharge = input === undefined ? undefined : capture('inputPrefix', 'getChargeRuntime');
  const ceilingWorldMapping = ceiling === undefined ? undefined : capture('world', 'getMappingActor');
  const updateCeiling = ceiling === undefined ? undefined : capture('ceiling', 'updateActor');
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const noLegacyDistances = (actual: object): void => {
    for (const key of ['speedScalar760', 'speedScalar764', 'kfmSpeedScalar760', 'kfmSpeedScalar764', 'curTargetDist']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`source760/764 owner conflict: legacy ${key} is present`);
      check();
    }
  };
  type TailGetter = 'getActualActor' | 'getWorldBinding' | 'getMovementBinding' | 'getStatusBinding' |
    'getActualBorg' | 'getMappingActor' | 'getChargeRuntime' | 'getChargeBinding' | 'getGlobal' |
    'getCueRuntime' | 'getCueBinding' | 'getDispatchBinding' | 'getActorBinding' | 'getKnownTeamStorageOwners';
  interface TailOwners {
    runtime: SourceActorCue0TailRuntime; value: (key: TailGetter, id: symbol) => unknown;
    charge: SourceActorInputChargeRuntime; chargeBinding: object; binding: object; global: object; data: object;
    chargeGlobal: () => unknown; chargeData: () => unknown; descriptors: () => object[];
  }
  interface CommandOwners {
    runtime: SourceActorCommandAdmissionRuntime;
    value: (key: keyof SourceActorCommandAdmissionRuntime, id: symbol) => unknown;
    binding: object; start: object; stream: object; global: object; data: object;
  }
  interface Entry {
    actual: RomActor; borg: SourceActorGaugeBorgOwner; world: object; status: object;
    gauge: object; stage?: object; input?: object; control?: object; action?: object;
    rates?: {binding: object; mapping: object};
    normal?: {binding: object; mapping: object; movement: object;
      cues: SourceActorCueResetRuntime | undefined; cue: object | undefined; dispatch: object | undefined;
      rotation: SourceActorRotationDampingRuntime | undefined; rotationOwners: readonly object[];
      cue0: SourceActorCue0LifecycleRuntime | undefined; cue0Owners: readonly object[]; cue0Terrain?: object; cue0Attribute?: object;
      testers: SourceActorInputTestersRuntime | undefined; testerAction?: object; tail?: TailOwners; command?: CommandOwners};
    ceiling?: {mapping: object; matrix: object; terrain: object; globals: object;
      charge: SourceActorInputChargeRuntime; chargeGlobal: () => unknown};
    ready?: {runtime: SourceActorReadyTransitionsRuntime; binding: object};
    binding: Partial<SourceActorTickPrefixBinding>; lastEpoch: number;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const actor = actors.get(id); if (!actor) fail('unknown/non-owned tick-prefix actor'); return actor;};
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): void => {
    if (get(id) !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const readyValue = (runtime: SourceActorReadyTransitionsRuntime, key: string, id: symbol): unknown => {
    const method = read(runtime, key);
    if (typeof method !== 'function') fail(`ready ${key}: own data-function required`);
    const value = Reflect.apply(method, runtime, [id]); check(); return value;
  };
  const readyOwners = (id: symbol, actor: Entry): void => {
    const current = controlReady?.(id);
    if (current !== actor.ready?.runtime) fail('control ready runtime changed after tick admission');
    if (!actor.ready) return;
    const runtime = actor.ready.runtime;
    const expected: readonly [string, object | undefined][] = [
      ['getActualActor', actor.actual], ['getWorldBinding', actor.world], ['getStatusBinding', actor.status],
      ['getStageBinding', actor.stage], ['getControlBinding', actor.control], ['getActualBorg', actor.borg],
      ['getActorBinding', actor.ready.binding],
    ];
    for (const [key, owner] of expected)
      if (owner === undefined || readyValue(runtime, key, id) !== owner) fail(`ready ${key}: canonical source owner mismatch`);
  };
  const ceilingOwners = (id: symbol, actor: Entry): void => {
    if (!actor.ceiling) return;
    const c = actor.ceiling;
    stable(ceilingActor!, id, actor.actual, 'ceiling actor');
    stable(ceilingWorld!, id, actor.world, 'ceiling world');
    stable(ceilingMapping!, id, c.mapping, 'ceiling mapping');
    stable(ceilingWorldMapping!, id, c.mapping, 'ceiling/world mapping');
    stable(ceilingMatrix!, id, c.matrix, 'ceiling matrix');
    const rateMatrixOwner = rateMatrix?.(id);
    if (rateMatrixOwner !== undefined && rateMatrixOwner !== c.matrix) fail('ceiling/rate canonical matrix4a4 owner mismatch');
    stable(ceilingTerrain!, id, c.terrain, 'ceiling terrain');
    stable(stageTerrain!, id, c.terrain, 'ceiling/stage terrain');
    stable(ceilingGlobals!, id, c.globals, 'ceiling match globals');
    if (inputCharge!(id) !== c.charge || c.chargeGlobal() !== c.globals)
      fail('ceiling/input charge must retain the same PTR_DAT_80433934 match globals');
    check();
  };
  const rotationRecords = (runtime: SourceActorRotationDampingRuntime, method: 'getStorageOwners' | 'getKnownDescriptorRecords', id: symbol): object[] => {
    const fn = read(runtime, method); if (typeof fn !== 'function') fail(`rotation ${method}: own data-function required`);
    const values = Reflect.apply(fn, runtime, [id]); check();
    if (!Array.isArray(values)) fail(`rotation ${method}: actual owner array required`);
    return values.map(value => record(value, `rotation ${method}`));
  };
  const cue0Value = (runtime: SourceActorCue0LifecycleRuntime, key: keyof SourceActorCue0LifecycleRuntime, id: symbol): unknown => {
    const fn = read(runtime, key); if (typeof fn !== 'function') fail(`cue0 ${key}: own data-function required`);
    const value = Reflect.apply(fn, runtime, [id]); check(); return value;
  };
  const cue0Records = (runtime: SourceActorCue0LifecycleRuntime, id: symbol): object[] => {
    const values = cue0Value(runtime, 'getSourceOwners', id);
    if (!Array.isArray(values)) fail('cue0 source owner array required');
    return values.map(value => record(value, 'cue0 source owner'));
  };
  const testerValue = (runtime: SourceActorInputTestersRuntime, key: keyof SourceActorInputTestersRuntime, id: symbol): unknown => {
    const fn = read(runtime, key); if (typeof fn !== 'function') fail(`input testers ${key}: own data-function required`);
    const value = Reflect.apply(fn, runtime, [id]); check(); return value;
  };
  const testerDescriptors = (runtime: SourceActorInputTestersRuntime, id: symbol): object[] => {
    const values = testerValue(runtime, 'getKnownDescriptorRecords', id);
    if (!Array.isArray(values)) fail('input tester descriptor owner array required');
    return values.map(value => record(value, 'input tester descriptor owner'));
  };
  const captureCommand = (runtime: SourceActorCommandAdmissionRuntime, id: symbol): CommandOwners => {
    const methods = new Map<keyof SourceActorCommandAdmissionRuntime, (...args: unknown[]) => unknown>();
    const keys: (keyof SourceActorCommandAdmissionRuntime)[] = ['getActualActor', 'getWorldBinding', 'getStatusBinding',
      'getMappingActor', 'getAttributeBinding', 'getChargeRuntime', 'getChargeBinding', 'getActionRuntime', 'getActionBinding',
      'getCueRuntime', 'getCueBinding', 'getDispatchBinding', 'getActorBinding', 'getStartBinding', 'getStreamBinding',
      'getGlobal', 'getData', 'getKnownStorageOwners', 'getKnownStorageEntries'];
    for (const key of keys) {
      const fn = read(runtime, key); if (typeof fn !== 'function') fail(`command admission ${key}: own data-function required`);
      methods.set(key, (...args: unknown[]): unknown => {const value = Reflect.apply(fn, runtime, args); check(); return value;});
    }
    const value = (key: keyof SourceActorCommandAdmissionRuntime, actorId: symbol): unknown => methods.get(key)!(actorId);
    return {runtime, value, binding: record(value('getActorBinding', id), 'command binding'),
      start: record(value('getStartBinding', id), 'command start'), stream: record(value('getStreamBinding', id), 'command stream'),
      global: record(value('getGlobal', id), 'command match global'), data: record(value('getData', id), 'command data')};
  };
  const commandEntries = (command: CommandOwners, id: symbol): readonly Readonly<{owner: object; kind: string}>[] => {
    const values = command.value('getKnownStorageEntries', id);
    if (!Array.isArray(values)) fail('known command storage entry array required');
    return values.map(value => {
      const owner = record(read(value, 'owner'), 'known command storage owner'), kind = read(value, 'kind');
      if (typeof kind !== 'string') fail('known command storage kind required');
      return {owner, kind};
    });
  };
  const commandStorage = (command: CommandOwners, id: symbol): object[] => {
    const values = command.value('getKnownStorageOwners', id);
    if (!Array.isArray(values)) fail('command storage owner array required');
    return values.map(owner => record(owner, 'command storage owner'));
  };
  const captureTail = (runtime: SourceActorCue0TailRuntime, id: symbol): TailOwners => {
    const methods = new Map<TailGetter, (...args: unknown[]) => unknown>();
    const keys: TailGetter[] = ['getActualActor', 'getWorldBinding', 'getMovementBinding', 'getStatusBinding',
      'getActualBorg', 'getMappingActor', 'getChargeRuntime', 'getChargeBinding', 'getGlobal',
      'getCueRuntime', 'getCueBinding', 'getDispatchBinding', 'getActorBinding', 'getKnownTeamStorageOwners'];
    for (const key of keys) {
      const fn = read(runtime, key); if (typeof fn !== 'function') fail(`cue0 tail ${key}: own data-function required`);
      methods.set(key, (...args: unknown[]): unknown => {const value = Reflect.apply(fn, runtime, args); check(); return value;});
    }
    const value = (key: TailGetter, actorId: symbol): unknown => methods.get(key)!(actorId);
    const charge = value('getChargeRuntime', id);
    if (!isSourceActorInputChargeRuntime(charge)) fail('cue0 tail requires genuine charge runtime');
    const captureCharge = (key: 'getGlobal' | 'getData' | 'getKnownDescriptorRecords') => {
      const fn = read(charge, key); if (typeof fn !== 'function') fail(`tail charge ${key}: own data-function required`);
      return (): unknown => {const result = Reflect.apply(fn, charge, []); check(); return result;};
    };
    const chargeGlobal = captureCharge('getGlobal'), chargeData = captureCharge('getData');
    const getDescriptors = captureCharge('getKnownDescriptorRecords');
    const descriptors = (): object[] => {
      const values = getDescriptors(); if (!Array.isArray(values)) fail('tail charge descriptor owner array required');
      return values.map(owner => record(owner, 'tail charge descriptor'));
    };
    return {runtime, value, charge, chargeBinding: record(value('getChargeBinding', id), 'tail charge binding'),
      binding: record(value('getActorBinding', id), 'tail binding'), global: record(value('getGlobal', id), 'tail match global'),
      data: record(chargeData(), 'tail charge data'), chargeGlobal, chargeData, descriptors};
  };
  const teamOwners = (tail: TailOwners, id: symbol): object[] => {
    const values = tail.value('getKnownTeamStorageOwners', id);
    if (!Array.isArray(values)) fail('tail team storage owner array required');
    return values.map(owner => record(owner, 'tail team storage owner'));
  };
  // Shared tables/rows may belong to several actors. They are never actor-only
  // extras or claims, but must not alias any retained composed actor storage.
  const actorRecords = (actor: Entry): object[] => {
    const n = actor.normal;
    const optional = [actor.stage, actor.input, actor.control, actor.action, actor.ready?.binding,
      actor.rates?.mapping, actor.rates?.binding, actor.ceiling?.matrix,
      actor.rates || !actor.ceiling ? undefined : actor.ceiling.mapping,
      n?.binding, n?.movement, n?.cue, n?.dispatch,
      actor.rates || actor.ceiling ? undefined : n?.mapping,
      n?.tail && !n.testers ? n.tail.chargeBinding : undefined];
    return [actor.actual, actor.borg, actor.world, actor.status, actor.gauge, actor.binding,
      ...optional.filter((owner): owner is object => owner !== undefined), ...(n?.rotationOwners ?? []),
      ...(n?.cue0Owners ?? []).filter(owner => owner !== n?.testerAction)];
  };
  const nestedTailStorage = (actor: Entry): object[] => {
    const tail = actor.normal?.tail; if (!tail) return [];
    const result: object[] = [];
    // Owner-reference metadata only: do not read a selected table element or
    // invoke an accessor while admitting an otherwise unreached source path.
    const fields: [object, string][] = [[actor.actual, 'cueTable'], [actor.world, 'scale58'],
      [actor.borg, 'paramTier'], [tail.data, 'held3970'], [tail.data, 'release397c']];
    for (const [owner, key] of fields) {
      const p = Object.getOwnPropertyDescriptor(owner, key); check();
      if (p && 'value' in p && p.value !== null && typeof p.value === 'object') result.push(p.value);
    }
    return result;
  };
  const nestedCommandStorage = (actor: Entry): object[] => {
    const command = actor.normal?.command; if (!command) return [];
    const result: object[] = [];
    const fields: [object, string][] = [[actor.actual, 'cueTable'], [actor.actual, 'actionSpeedRows'], [actor.actual, 'parts'],
      [actor.world, 'scale58'], [actor.world, 'offset1dbc'], [actor.world, 'adjusted1d54'], [actor.world, 'preRotation1d64'],
      [actor.borg, 'paramTier'], [command.data, 'held3970'], [command.data, 'release397c']];
    for (const [owner, key] of fields) {
      const p = Object.getOwnPropertyDescriptor(owner, key); check();
      if (p && 'value' in p && p.value !== null && typeof p.value === 'object') result.push(p.value);
    }
    return result;
  };
  const commandRawReferences = (actor: Entry): object[] => {
    const command = actor.normal?.command; if (!command) return [];
    const result: object[] = [];
    for (const [owner, key] of [[actor.actual, 'commandTable'], [actor.actual, 'aimOrigin518'],
      [actor.actual, 'visibilityRoster'], [actor.actual, 'visibilityTarget'], [command.data, 'flags3994'],
      [command.binding, 'pointer504'], [command.binding, 'pointer508'], [command.binding, 'pointerc8']] as const) {
      const p = Object.getOwnPropertyDescriptor(owner, key); check();
      if (p && 'value' in p && p.value !== null && typeof p.value === 'object') result.push(p.value);
    }
    return result;
  };
  const assertCommandOwners = (id: symbol, actor: Entry, raw?: object): void => {
    const n = actor.normal, command = n?.command; if (!n || !command) return;
    const expected: [keyof SourceActorCommandAdmissionRuntime, object | undefined][] = [
      ['getActualActor', actor.actual], ['getWorldBinding', actor.world], ['getStatusBinding', actor.status],
      ['getMappingActor', n.mapping], ['getAttributeBinding', n.cue0Attribute], ['getChargeRuntime', inputCharge?.(id) as object | undefined],
      ['getChargeBinding', n.testers ? testerValue(n.testers, 'getChargeBinding', id) as object : undefined],
      ['getActionRuntime', actionRuntime as object | undefined], ['getActionBinding', actor.action],
      ['getCueRuntime', n.cues], ['getCueBinding', n.cue], ['getDispatchBinding', n.dispatch],
      ['getActorBinding', command.binding], ['getStartBinding', command.start], ['getStreamBinding', command.stream],
      ['getGlobal', command.global], ['getData', command.data],
    ];
    for (const [key, owner] of expected)
      if (owner === undefined || command.value(key, id) !== owner) fail(`command ${key}: canonical tick source owner mismatch`);
    if (![command.binding, command.start, command.stream].every(owner => n.cue0Owners.includes(owner)))
      fail('cue0 must retain command binding and canonical stream owners');
    if (actor.ceiling && actor.ceiling.globals !== command.global) fail('command/ceiling match global owner mismatch');
    if (n.tail && (n.tail.global !== command.global || n.tail.data !== command.data)) fail('command/tail shared owner mismatch');
    const knownEntries = commandEntries(command, id), known = knownEntries.map(({owner}) => owner);
    const kinds = new Map(knownEntries.map(({owner, kind}) => [owner, kind]));
    const records = actorRecords(actor), nested = nestedCommandStorage(actor);
    const descriptors = [...(n.testers ? testerDescriptors(n.testers, id) : []),
      ...(n.rotation ? rotationRecords(n.rotation, 'getKnownDescriptorRecords', id) : [])];
    const forbidden = (owner: object): boolean => assigned.has(owner) || records.includes(owner) || nested.includes(owner) ||
      descriptors.includes(owner) || owner === n.cue0Terrain || owner === actor.ceiling?.terrain;
    if (command.global === command.data || forbidden(command.global) || forbidden(command.data) ||
        known.some(owner => forbidden(owner) || owner === command.global || owner === command.data ||
          (n.tail !== undefined && teamOwners(n.tail, id).includes(owner))))
      fail('command storage aliases a tick source owner or descriptor');
    if (raw !== undefined && (known.includes(raw) || raw === command.global || raw === command.data || nested.includes(raw) || commandRawReferences(actor).includes(raw)))
      fail('raw input must not alias command storage');
    // A new child binding and shared storage cannot become a second owner for
    // a caller field, even when the ready branch bypasses the child itself.
    const canonical = new Map<string, object>([
      ['controlWord', actor.actual], ['ubCue', actor.actual], ['fbCue', actor.actual],
      ['targetDistance760', actor.actual], ['horizontalDistance764', actor.actual],
      ['cmdButton', actor.actual], ['cmdSubtype', actor.actual], ['cmdChargedRanged', actor.actual],
      ['commandTable', actor.actual], ['visibilityTarget', actor.actual], ['visibilityRoster', actor.actual],
      ['pointer504', command.binding], ['pointer508', command.binding], ['pointerc8', command.binding], ['byteD0', command.binding],
      ['marker709', command.start], ['blockedMask1d9a', command.stream], ['byte45', command.global],
      ['float8043762c', command.data], ['float80437678', command.data], ['float80437078', command.data], ['flags3994', command.data],
      ['byte598', actor.binding], ['callback4c8', n.binding], ['callback4dc', n.binding], ['short6bc', n.binding], ['byte1d9', n.binding],
    ]);
    for (const owner of [...records, command.global, command.data, ...known]) {
      for (const [key, expected] of canonical) {
        const p = Object.getOwnPropertyDescriptor(owner, key); check();
        if (owner !== expected && !(key === 'controlWord' && kinds.get(owner) === 'visibility-target') && p !== undefined)
          fail(`${key}: competing command/tick storage on another owner`);
      }
      for (const key of ['field504', 'field508', 'fieldc8', 'pointerC8', 'pointerCC', 'pointercc', 'fieldD0', 'byte709', 'byte1d9a']) {
        const p = Object.getOwnPropertyDescriptor(owner, key); check();
        if (p !== undefined) fail(`${key}: competing command/tick storage alias`);
      }
    }
    for (const [otherId, other] of actors) {
      if (known.some(owner => nestedCommandStorage(other).includes(owner) || owner === other.normal?.cue0Terrain ||
          owner === other.ceiling?.terrain || (other.normal?.testers && testerDescriptors(other.normal.testers, otherId).includes(owner)) ||
          (other.normal?.rotation && rotationRecords(other.normal.rotation, 'getKnownDescriptorRecords', otherId).includes(owner))))
        fail('command storage aliases another actor terrain or descriptor');
    }
  };
  const assertTeamOwners = (id: symbol, actor: Entry, raw?: object): void => {
    const tail = actor.normal?.tail; if (!tail) return;
    const descriptors = [...tail.descriptors(), ...(actor.normal?.rotation ?
      rotationRecords(actor.normal.rotation, 'getKnownDescriptorRecords', id) : [])];
    const records = [...actorRecords(actor), ...nestedTailStorage(actor)], teams = teamOwners(tail, id);
    const forbidden = (owner: object): boolean => assigned.has(owner) || records.includes(owner) || descriptors.includes(owner) ||
      owner === actor.normal?.cue0Terrain || owner === actor.ceiling?.terrain;
    if (forbidden(tail.global) || forbidden(tail.data) || tail.global === tail.data ||
        teams.some(owner => owner === tail.global || owner === tail.data || forbidden(owner)))
      fail('tail shared storage aliases a tick source owner or descriptor');
    if (raw !== undefined && teams.includes(raw)) fail('raw input must not alias tail team storage');
    for (const [otherId, other] of actors) {
      if (teams.some(owner => nestedTailStorage(other).includes(owner) || owner === other.normal?.cue0Terrain || owner === other.ceiling?.terrain ||
          (other.normal?.rotation && rotationRecords(other.normal.rotation, 'getKnownDescriptorRecords', otherId).includes(owner)) ||
          (other.normal?.testers && testerDescriptors(other.normal.testers, otherId).includes(owner))))
        fail('tail team storage aliases another actor terrain or descriptor');
    }
  };
  const tailOwners = (id: symbol, actor: Entry): void => {
    const n = actor.normal; if (!n?.cue0) return;
    const tail = n.tail;
    if (cue0Value(n.cue0, 'getTailRuntime', id) !== tail?.runtime) fail('cue0 tail runtime changed after tick admission');
    if (!tail) return;
    const expected: [TailGetter, object | undefined][] = [
      ['getActualActor', actor.actual], ['getWorldBinding', actor.world], ['getStatusBinding', actor.status],
      ['getActualBorg', actor.borg], ['getMappingActor', n.mapping], ['getMovementBinding', n.movement],
      ['getCueRuntime', n.cues], ['getCueBinding', n.cue], ['getDispatchBinding', n.dispatch],
      ['getActorBinding', tail.binding], ['getChargeBinding', tail.chargeBinding], ['getGlobal', tail.global],
    ];
    for (const [key, owner] of expected)
      if (owner === undefined || tail.value(key, id) !== owner) fail(`tail ${key}: canonical tick source owner mismatch`);
    if (tail.value('getChargeRuntime', id) !== tail.charge || inputCharge?.(id) !== tail.charge ||
        tail.chargeGlobal() !== tail.global || tail.chargeData() !== tail.data)
      fail('tail/input prefix must retain the same genuine charge runtime and global');
    if (actor.ceiling && actor.ceiling.globals !== tail.global) fail('tail/ceiling match global owner mismatch');
    if (!n.cue0Owners.includes(tail.binding)) fail('cue0 must retain the new tail binding');
    assertTeamOwners(id, actor);
  };
  // Cue44 writes the SAME source588 cell already owned by cue resets. Keep
  // this admission check independent of command admission and of the selected
  // ready/control branch, including before explicit raw input is ingested.
  const assertCueControlOwners = (id: symbol, actor: Entry, raw?: object): void => {
    const n = actor.normal; if (!n?.cue0 || !n.cue) return;
    const extra = [n.cue0Terrain, actor.ceiling?.globals, actor.ceiling?.terrain,
      n.tail?.global, n.tail?.data, n.command?.global, n.command?.data, raw]
      .filter((value): value is object => value !== undefined);
    const records = [...actorRecords(actor), ...extra,
      ...(n.tail ? teamOwners(n.tail, id) : []),
      ...(n.command ? commandEntries(n.command, id).map(({owner}) => owner) : []),
      ...(n.testers ? testerDescriptors(n.testers, id) : []),
      ...(n.rotation ? rotationRecords(n.rotation, 'getKnownDescriptorRecords', id) : [])];
    const canonical = new Map<string, object>([['byte588', n.cue], ['stateFlagA', actor.actual],
      ['inputEdge5d4', actor.actual], ['statusWord5b4', actor.actual]]);
    for (const owner of records) {
      for (const [key, expected] of canonical) {
        const p = Object.getOwnPropertyDescriptor(owner, key); check();
        if (owner !== expected && p !== undefined) fail(`${key}: competing cue-control storage on another owner`);
      }
      for (const key of ['field588', 'flags588', 'command588', 'byte57a', 'field57a', 'flags57a',
        'field5d4', 'word5d4', 'flags5d4', 'inputFlags5d4', 'field5b4', 'word5b4', 'flags5b4']) {
        const alias = Object.getOwnPropertyDescriptor(owner, key); check();
        if (alias !== undefined) fail(`${key}: competing cue-control storage alias`);
      }
    }
  };
  const normalOwners = (id: symbol, actor: Entry): void => {
    if (!actor.normal) return;
    const n = actor.normal;
    stable(normalActor!, id, actor.actual, 'normal actor');
    stable(normalWorld!, id, actor.world, 'normal world');
    stable(normalStatus!, id, actor.status, 'normal status');
    stable(normalMapping!, id, n.mapping, 'normal mapping');
    stable(normalWorldMapping!, id, n.mapping, 'normal/world mapping');
    stable(normalMovement!, id, n.movement, 'normal movement');
    stable(normalBinding!, id, n.binding, 'normal binding');
    if (normalCues!(id) !== n.cues || normalCueBinding!(id) !== n.cue || normalDispatch!(id) !== n.dispatch)
      fail('normal cue owners changed after tick admission');
    if (normalCue0!(id) !== n.cue0) fail('normal cue0 runtime changed after tick admission');
    if (n.cue0) {
      const current = cue0Records(n.cue0, id);
      if (current.length !== n.cue0Owners.length || current.some((owner, i) => owner !== n.cue0Owners[i]))
        fail('normal cue0 source owners changed');
      if (cue0Value(n.cue0, 'getTerrainGlobals', id) !== n.cue0Terrain ||
          cue0Value(n.cue0, 'getAttributeBinding', id) !== n.cue0Attribute)
        fail('normal cue0 shared owners changed');
      if (stageTerrain && stageTerrain(id) !== n.cue0Terrain)
        fail('cue0/stage must share the same terrain-global owner');
      if (cue0Value(n.cue0, 'getInputTestersRuntime', id) !== n.testers)
        fail('cue0 input tester runtime changed after tick admission');
      if (n.testers) {
        if (testerValue(n.testers, 'getCommandAdmissionRuntime', id) !== n.command?.runtime)
          fail('input tester command admission runtime changed after tick admission');
        if (testerValue(n.testers, 'getStatusBinding', id) !== actor.status)
          fail('input tester/tick status owner mismatch');
        if (testerValue(n.testers, 'getChargeRuntime', id) !== inputCharge?.(id))
          fail('input testers and input prefix must share the same genuine charge runtime');
        const action = testerValue(n.testers, 'getActionRuntime', id);
        if (action !== undefined && action !== actionRuntime)
          fail('input testers and tick must share the same genuine actionRequest runtime');
        if (testerValue(n.testers, 'getActionBinding', id) !== n.testerAction ||
            (n.testerAction !== undefined && n.testerAction !== actor.action))
          fail('input tester/tick action owner mismatch');
        if (testerDescriptors(n.testers, id).some(owner => assigned.has(owner)))
          fail('input tester descriptor aliases a bound actor source owner');
      }
    }
    if (normalRotation!(id) !== n.rotation) fail('normal rotation runtime changed after tick admission');
    if (n.rotation) {
      const current = rotationRecords(n.rotation, 'getStorageOwners', id);
      if (current.length !== n.rotationOwners.length || current.some((owner, i) => owner !== n.rotationOwners[i]))
        fail('normal rotation storage owners changed');
      if (rotationRecords(n.rotation, 'getKnownDescriptorRecords', id).some(owner => assigned.has(owner)))
        fail('rotation descriptor aliases a bound actor source owner');
    }
    tailOwners(id, actor); assertCommandOwners(id, actor); assertCueControlOwners(id, actor);
    const stageCue = stageCues?.(id);
    if (stageCue !== undefined && n.cues !== undefined && stageCue !== n.cues)
      fail('normal/stage must share the same genuine cue runtime');
  };
  // Gauge/tier construction is cyclic, so genuine late binding is checked on
  // every invocation. It may add no duplicate rate, descriptor or match owner.
  const tierValue = (runtime: SourceActorTierLifecycleRuntime, key: keyof SourceActorTierLifecycleRuntime, id: symbol): unknown => {
    const fn = read(runtime, key); if (typeof fn !== 'function') fail(`tier ${key}: own data-function required`);
    const result = Reflect.apply(fn, runtime, [id]); check(); return result;
  };
  const tierOwners = (id: symbol, actor: Entry): object[] => {
    const runtime = gaugeTiers(id);
    if (runtime === undefined) return [];
    if (!isSourceActorTierLifecycleRuntime(runtime)) fail('gauge tier lifecycle must be genuine');
    const expected: [keyof SourceActorTierLifecycleRuntime, object][] = [
      ['getActualActor', actor.actual], ['getActualBorg', actor.borg], ['getWorldBinding', actor.world],
      ['getStatusBinding', actor.status], ['getGaugeBinding', actor.gauge],
      ['getTierOwner', record(read(actor.borg, 'paramTier'), 'actual paramTier')],
    ];
    if (actor.rates) expected.push(['getRateBinding', actor.rates.binding], ['getMappingActor', actor.rates.mapping]);
    if (actor.ceiling) expected.push(['getMatrixBinding', actor.ceiling.matrix], ['getMatchGlobals', actor.ceiling.globals]);
    for (const [key, owner] of expected)
      if (tierValue(runtime, key, id) !== owner) fail(`tier ${key}: canonical source owner mismatch`);
    const globals = record(tierValue(runtime, 'getMatchGlobals', id), 'tier match globals');
    if (actor.normal?.command && actor.normal.command.global !== globals) fail('command/tier match global owner mismatch');
    if (actor.normal?.tail && actor.normal.tail.global !== globals) fail('tail/tier match global owner mismatch');
    const charge = inputCharge?.(id);
    if (charge !== undefined) {
      if (!isSourceActorInputChargeRuntime(charge)) fail('tier/input charge must be genuine');
      const fn = read(charge, 'getGlobal'); if (typeof fn !== 'function') fail('charge global requires own data-function');
      if (Reflect.apply(fn, charge, []) !== globals) fail('tier/input charge must share the same PTR_DAT_80433934 match globals');
      check();
    }
    const binding = record(tierValue(runtime, 'getActorBinding', id), 'tier binding');
    const attribute = record(tierValue(runtime, 'getAttributeBinding', id), 'tier attribute binding');
    const rate = record(tierValue(runtime, 'getRateBinding', id), 'tier rate binding');
    if (actor.normal?.cue0 && actor.normal.cue0Attribute !== attribute)
      fail('cue0/tier canonical attribute owner mismatch');
    const known = [actor.actual, actor.borg, actor.world, actor.status, actor.gauge, actor.binding,
      actor.stage, actor.input, actor.control, actor.action, actor.ready?.binding,
      actor.rates?.mapping, actor.rates?.binding, actor.ceiling?.matrix, actor.ceiling?.terrain,
      actor.normal?.binding, actor.normal?.movement, actor.normal?.cue, actor.normal?.dispatch,
      actor.rates ? undefined : actor.normal?.mapping, ...(actor.normal?.rotationOwners ?? []),
      ...(actor.normal?.cue0Owners ?? []).filter(owner => owner !== attribute && owner !== actor.normal?.testerAction)].filter(value => value !== undefined);
    if (new Set([...known, globals, binding, attribute]).size !== known.length + 3)
      fail('tier source owner alias: distinct shared and actor-specific records required');
    if (actor.normal?.tail && teamOwners(actor.normal.tail, id).some(owner =>
        owner === globals || owner === binding || owner === attribute || owner === rate))
      fail('tail team storage aliases a tier source owner');
    if (actor.normal?.command && commandStorage(actor.normal.command, id).some(owner =>
        owner === globals || owner === binding || owner === attribute || owner === rate))
      fail('command storage aliases a tier source owner');
    return [globals, binding, attribute, rate];
  };
  const owners = (id: symbol, actor: Entry): void => {
    stable(worldActor, id, actor.actual, 'world actor'); stable(gaugeActor, id, actor.actual, 'gauge actor');
    stable(gaugeBorg, id, actor.borg, 'gauge Borg'); stable(worldBinding, id, actor.world, 'world binding');
    stable(gaugeStatus, id, actor.status, 'status binding'); stable(gaugeBinding, id, actor.gauge, 'gauge binding');
    if (stageActor) {
      stable(stageActor, id, actor.actual, 'stage actor'); stable(stageWorld!, id, actor.world, 'stage world');
      stable(stageStatus!, id, actor.status, 'stage status'); stable(stageBinding!, id, actor.stage!, 'stage binding');
    }
    if (inputActor) {
      stable(inputActor, id, actor.actual, 'input actor'); stable(inputBorg!, id, actor.borg, 'input Borg');
      stable(inputBinding!, id, actor.input!, 'input binding');
    }
    if (controlActor) {
      stable(controlActor, id, actor.actual, 'control actor');
      stable(controlWorld!, id, actor.world, 'control world');
      stable(controlStatus!, id, actor.status, 'control status');
      stable(controlBinding!, id, actor.control!, 'control binding');
    }
    readyOwners(id, actor);
    if (actionActor) {
      stable(actionActor, id, actor.actual, 'action request actor');
      stable(actionWorld!, id, actor.world, 'action request world');
      stable(actionBinding!, id, actor.action!, 'action request binding');
    }
    if (rateActor) {
      stable(rateActor, id, actor.actual, 'actor rates actor');
      stable(rateBorg!, id, actor.borg, 'actor rates Borg');
      stable(rateWorld!, id, actor.world, 'actor rates world');
      stable(rateStatus!, id, actor.status, 'actor rates status');
      stable(rateMapping!, id, actor.rates!.mapping, 'actor rates mapping');
      stable(worldMapping!, id, actor.rates!.mapping, 'actor rates/world mapping');
      stable(rateBinding!, id, actor.rates!.binding, 'actor rates binding');
    }
    ceilingOwners(id, actor); normalOwners(id, actor); tierOwners(id, actor);
  };
  // Host boundary only: explicit raw input may establish absent canonical cells.
  // Existing cells must be own writable data. No zero/default/legacy fallback.
  const ingest = (actual: RomActor, key: 'targetDistance760' | 'horizontalDistance764', value: number): void => {
    const descriptor = Object.getOwnPropertyDescriptor(actual, key); check();
    if (descriptor !== undefined) {write(actual, key, value); return;}
    if (key in actual || !Object.isExtensible(actual)) fail(`${key}: absent raw-input destination cannot be established`);
    Object.defineProperty(actual, key, {value, writable: true, enumerable: true, configurable: true}); check();
  };
  return Object.freeze({
    bindActor(id: symbol, actualBorg: SourceActorGaugeBorgOwner,
      initial: Readonly<Partial<SourceActorTickPrefixBinding>>): void {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source tick-prefix runtime');
      stable(gaugeActor, id, actual, 'gauge actor');
      const borg = record(actualBorg, 'actual BorgRuntime') as SourceActorGaugeBorgOwner;
      stable(gaugeBorg, id, borg, 'gauge Borg');
      const world = record(worldBinding(id), 'world binding'), status = record(gaugeStatus(id), 'status binding');
      const gauge = record(gaugeBinding(id), 'gauge binding');
      const records = [actual, borg, world, status, gauge];
      let stageOwner: object | undefined;
      if (stageActor) {
        stable(stageActor, id, actual, 'stage actor'); stable(stageWorld!, id, world, 'stage world');
        stable(stageStatus!, id, status, 'stage status');
        stageOwner = record(stageBinding!(id), 'stage binding'); records.push(stageOwner);
      }
      let inputOwner: object | undefined;
      if (inputActor) {
        stable(inputActor, id, actual, 'input actor'); stable(inputBorg!, id, borg, 'input Borg');
        inputOwner = record(inputBinding!(id), 'input binding'); records.push(inputOwner);
      }
      let controlOwner: object | undefined;
      if (controlActor) {
        stable(controlActor, id, actual, 'control actor'); stable(controlWorld!, id, world, 'control world');
        stable(controlStatus!, id, status, 'control status');
        controlOwner = record(controlBinding!(id), 'control binding'); records.push(controlOwner);
      }
      let actionOwner: object | undefined;
      if (actionActor) {
        stable(actionActor, id, actual, 'action request actor'); stable(actionWorld!, id, world, 'action request world');
        actionOwner = record(actionBinding!(id), 'action request binding'); records.push(actionOwner);
      }
      let rateOwners: Entry['rates'];
      if (rateActor) {
        stable(rateActor, id, actual, 'actor rates actor'); stable(rateBorg!, id, borg, 'actor rates Borg');
        stable(rateWorld!, id, world, 'actor rates world'); stable(rateStatus!, id, status, 'actor rates status');
        const mapping = record(rateMapping!(id), 'actor rates mapping');
        stable(worldMapping!, id, mapping, 'actor rates/world mapping');
        rateOwners = {mapping, binding: record(rateBinding!(id), 'actor rates binding')};
        records.push(rateOwners.mapping, rateOwners.binding);
      }
      let ceilingOwnersAtBind: Entry['ceiling'];
      if (ceilingActor) {
        stable(ceilingActor, id, actual, 'ceiling actor'); stable(ceilingWorld!, id, world, 'ceiling world');
        const mapping = record(ceilingMapping!(id), 'ceiling mapping');
        stable(ceilingWorldMapping!, id, mapping, 'ceiling/world mapping');
        if (rateOwners && rateOwners.mapping !== mapping) fail('ceiling/rate canonical mapping mismatch');
        const matrix = record(ceilingMatrix!(id), 'ceiling matrix');
        const rateMatrixOwner = rateMatrix?.(id);
        if (rateMatrixOwner !== undefined && rateMatrixOwner !== matrix) fail('ceiling/rate canonical matrix4a4 owner mismatch');
        const terrain = record(ceilingTerrain!(id), 'ceiling terrain');
        stable(stageTerrain!, id, terrain, 'ceiling/stage terrain');
        const globals = record(ceilingGlobals!(id), 'ceiling match globals');
        const charge = inputCharge!(id);
        if (!isSourceActorInputChargeRuntime(charge)) fail('ceiling completion requires genuine input charge');
        const getter = read(charge, 'getGlobal');
        if (typeof getter !== 'function') fail('charge global requires own data-function');
        const chargeGlobal = (): unknown => {const value = Reflect.apply(getter, charge, []); check(); return value;};
        if (chargeGlobal() !== globals) fail('ceiling/input charge must share the same PTR_DAT_80433934 match globals');
        if (!rateOwners) records.push(mapping);
        records.push(matrix);
        // Shared globals are allowed across actors, but never alias an actor's cells.
        if (new Set([...records, terrain, globals]).size !== records.length + 2)
          fail('ceiling source owner alias: distinct stage/match/actor records required');
        ceilingOwnersAtBind = {mapping, matrix, terrain, globals, charge, chargeGlobal};
      }
      let normalOwnersAtBind: Entry['normal'];
      if (normalActor) {
        stable(normalActor, id, actual, 'normal actor'); stable(normalWorld!, id, world, 'normal world');
        stable(normalStatus!, id, status, 'normal status');
        const mapping = record(normalMapping!(id), 'normal mapping');
        stable(normalWorldMapping!, id, mapping, 'normal/world mapping');
        if ((rateOwners && rateOwners.mapping !== mapping) ||
            (ceilingOwnersAtBind && ceilingOwnersAtBind.mapping !== mapping))
          fail('normal/rate/ceiling canonical mapping mismatch');
        const movement = record(normalMovement!(id), 'normal movement');
        const binding = record(normalBinding!(id), 'normal binding');
        const cues = normalCues!(id) as SourceActorCueResetRuntime | undefined;
        const cueValue = normalCueBinding!(id), dispatchValue = normalDispatch!(id);
        const cue = cueValue === undefined ? undefined : record(cueValue, 'normal cue binding');
        const dispatch = dispatchValue === undefined ? undefined : record(dispatchValue, 'normal dispatch binding');
        if (!rateOwners && !ceilingOwnersAtBind) records.push(mapping);
        records.push(movement, binding);
        if (cue) records.push(cue);
        if (dispatch) records.push(dispatch);
        const rotationValue = normalRotation!(id);
        if (rotationValue !== undefined && !isSourceActorRotationDampingRuntime(rotationValue))
          fail('normal rotation must be genuine');
        const rotation = rotationValue as SourceActorRotationDampingRuntime | undefined;
        const rotationOwners = rotation ? rotationRecords(rotation, 'getStorageOwners', id) : [];
        records.push(...rotationOwners);
        const cue0ValueAtBind = normalCue0!(id);
        if (cue0ValueAtBind !== undefined && !isSourceActorCue0LifecycleRuntime(cue0ValueAtBind))
          fail('normal cue0 must be genuine');
        const cue0 = cue0ValueAtBind as SourceActorCue0LifecycleRuntime | undefined;
        const cue0Owners = cue0 ? cue0Records(cue0, id) : [];
        const cue0Terrain = cue0 ? record(cue0Value(cue0, 'getTerrainGlobals', id), 'cue0 terrain') : undefined;
        const cue0Attribute = cue0 ? record(cue0Value(cue0, 'getAttributeBinding', id), 'cue0 attribute') : undefined;
        if (cue0Terrain && stageTerrain && stageTerrain(id) !== cue0Terrain)
          fail('cue0/stage must share the same terrain-global owner');
        const testersValue = cue0 ? cue0Value(cue0, 'getInputTestersRuntime', id) : undefined;
        if (testersValue !== undefined && !isSourceActorInputTestersRuntime(testersValue))
          fail('cue0 input testers must be genuine');
        const testers = testersValue as SourceActorInputTestersRuntime | undefined;
        let testerAction: object | undefined;
        if (testers) {
          if (testerValue(testers, 'getStatusBinding', id) !== status)
            fail('input tester/tick status owner mismatch');
          if (testerValue(testers, 'getChargeRuntime', id) !== inputCharge?.(id))
            fail('input testers and input prefix must share the same genuine charge runtime');
          const runtime = testerValue(testers, 'getActionRuntime', id);
          const binding = testerValue(testers, 'getActionBinding', id);
          if (runtime !== undefined && (runtime !== actionRuntime || binding !== actionOwner))
            fail('input testers and tick must share the same genuine actionRequest runtime');
          if (binding !== undefined) testerAction = record(binding, 'input tester action binding');
        }
        const commandValue = testers ? testerValue(testers, 'getCommandAdmissionRuntime', id) : undefined;
        if (commandValue !== undefined && !isSourceActorCommandAdmissionRuntime(commandValue))
          fail('input tester command admission must be genuine');
        const command = commandValue === undefined ? undefined : captureCommand(commandValue as SourceActorCommandAdmissionRuntime, id);
        const tailValue = cue0 ? cue0Value(cue0, 'getTailRuntime', id) : undefined;
        if (tailValue !== undefined && !isSourceActorCue0TailRuntime(tailValue)) fail('cue0 tail must be genuine');
        const tail = tailValue === undefined ? undefined : captureTail(tailValue as SourceActorCue0TailRuntime, id);
        if (tail && !testers) records.push(tail.chargeBinding);
        records.push(...cue0Owners.filter(owner => owner !== testerAction));
        if (cue0Terrain && records.includes(cue0Terrain)) fail('cue0 terrain aliases an actor source owner');
        normalOwnersAtBind = {mapping, movement, binding, cues, cue, dispatch, rotation, rotationOwners,
          cue0, cue0Owners, testers, ...(command === undefined ? {} : {command}), ...(tail === undefined ? {} : {tail}), ...(testerAction === undefined ? {} : {testerAction}), ...(cue0Terrain === undefined ? {} : {cue0Terrain, cue0Attribute: cue0Attribute!})};
      }
      const readyRuntime = controlReady?.(id);
      let ready: Entry['ready'];
      if (readyRuntime !== undefined) {
        if (!isSourceActorReadyTransitionsRuntime(readyRuntime)) fail('control ready runtime must be genuine');
        ready = {runtime: readyRuntime, binding: record(readyValue(readyRuntime, 'getActorBinding', id), 'ready binding')};
        records.push(ready.binding);
      }
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value)))
        fail('source owner alias: distinct actual actor/Borg/world/status/gauge required');
      if (ceilingOwnersAtBind && new Set([...records, ceilingOwnersAtBind.terrain, ceilingOwnersAtBind.globals]).size !== records.length + 2)
        fail('ceiling source owner alias: stage/match globals must differ from every actor owner');
      noLegacyDistances(actual); record(initial, 'initial tick-prefix binding');
      const binding: Partial<SourceActorTickPrefixBinding> = {};
      if (Object.getOwnPropertyDescriptor(initial, 'byte598') !== undefined)
        binding.byte598 = integer(read(initial, 'byte598'), 0, 255, 'byte598');
      const actor: Entry = {actual, borg, world, status, gauge,
        ...(stageOwner === undefined ? {} : {stage: stageOwner}),
        ...(inputOwner === undefined ? {} : {input: inputOwner}),
        ...(controlOwner === undefined ? {} : {control: controlOwner}),
        ...(actionOwner === undefined ? {} : {action: actionOwner}),
        ...(rateOwners === undefined ? {} : {rates: rateOwners}),
        ...(normalOwnersAtBind === undefined ? {} : {normal: normalOwnersAtBind}),
        ...(ceilingOwnersAtBind === undefined ? {} : {ceiling: ceilingOwnersAtBind}),
        ...(ready === undefined ? {} : {ready}), binding: Object.seal(binding), lastEpoch: -1};
      readyOwners(id, actor); ceilingOwners(id, actor); normalOwners(id, actor); tierOwners(id, actor); check(); actors.set(id, actor);
      records.forEach(value => assigned.add(value)); assigned.add(binding); claimedActors.add(actual);
    });},
    getActualActor(id: symbol) {return entry(id).actual;},
    getActualBorg(id: symbol) {return entry(id).borg;},
    getActorBinding(id: symbol) {return entry(id).binding;},
    ingestRawDistancesAndRun(id: symbol, epoch: number, raw: SourceActorTickRawDistances): void {return guard(() => {
      const actor = entry(id);
      const next = integer(epoch, 0, Number.MAX_SAFE_INTEGER, 'pre59068 raw-input epoch');
      if (next <= actor.lastEpoch) fail('pre59068 raw-input epoch already consumed or out of order');
      actor.lastEpoch = next; // Once attempted, never retry or silently normalize twice.
      // A prior6bc expiry may already have stored zero before an unsupported4dc.
      // Never let a later ready branch silently skip that outstanding source call.
      if (hasIncompleteSourceActorCommandAdmission(actor.actual)) fail('actual actor has known incomplete command admission; source continuation is unsupported');
      if (hasIncompleteSourceActorCue0Tail(actor.actual)) fail('actual actor has a known incomplete cue0 tail; source continuation is unsupported');
      if (hasIncompleteSourceActorInputTesters(actor.actual)) fail('actual actor has known incomplete input testers; source continuation is unsupported');
      if (hasIncompleteSourceActorCue0Lifecycle(actor.actual)) fail('actual actor has a known incomplete cue0 lifecycle; source continuation is unsupported');
      if (hasIncompleteSourceActorRotationDamping(actor.actual)) fail('actual actor has a known incomplete rotation damping; source continuation is unsupported');
      if (hasIncompleteSourceActorNormalCueSync(actor.actual)) fail('actual actor has a known incomplete cue synchronization; source continuation is unsupported');
      if (hasIncompleteSourceActorNormalCountdown(actor.actual)) fail('actual actor has a known incomplete6bc expiry; source continuation is unsupported');
      if (assertNormalComplete && assertNormalComplete(id) !== undefined) fail('normal completion assertion returned unexpectedly');
      owners(id, actor); noLegacyDistances(actor.actual); record(raw, 'explicit decoded raw distances');
      assertCommandOwners(id, actor, raw); assertCueControlOwners(id, actor, raw);
      if ((actor.normal?.tail && (nestedTailStorage(actor).includes(raw) || teamOwners(actor.normal.tail, id).includes(raw) || actor.normal.tail.descriptors().includes(raw) ||
          raw === actor.normal.tail.global || raw === actor.normal.tail.data || raw === actor.normal.tail.chargeBinding)) || assigned.has(raw) || (actor.normal?.testers && testerDescriptors(actor.normal.testers, id).includes(raw)) || (actor.normal?.rotation && rotationRecords(actor.normal.rotation, 'getKnownDescriptorRecords', id).includes(raw)) || tierOwners(id, actor).includes(raw) || raw === actor.normal?.cue0Terrain || raw === actor.ceiling?.globals || raw === actor.ceiling?.terrain ||
          raw === read(actor.world, 'scale58') || raw === read(actor.borg, 'paramTier'))
        fail('raw input must not alias a bound source owner');
      if (read(raw, 'boundary') !== 'externally-decoded-pre59068-raw') fail('explicit externally decoded pre59068 raw boundary required');
      ingest(actor.actual, 'targetDistance760', f(raw, 'targetDistance760'));
      ingest(actor.actual, 'horizontalDistance764', f(raw, 'horizontalDistance764'));
      // Actual instruction order starts here. Each divisor is a fresh B4 load;
      // real5bab8 cannot change B4 until BOTH division/store pairs finish.
      const distance760 = f(actor.actual, 'targetDistance760'), scale760 = f(actor.actual, 'modelScale');
      write(actor.actual, 'targetDistance760', div32(distance760, scale760));
      const distance764 = f(actor.actual, 'horizontalDistance764'), scale764 = f(actor.actual, 'modelScale');
      write(actor.actual, 'horizontalDistance764', div32(distance764, scale764));
      if (updateGauge(id) !== undefined) fail('genuine gauge stage returned asynchronously or unexpectedly');
      // Genuine67a70 prefix: source raw byte1db is explicitly sign-extended.
      write(actor.actual, 'controlWord', (integer(read(actor.actual, 'controlWord'), 0, 0xffffffff, 'controlWord') & ~0x100000) >>> 0);
      write(actor.binding, 'byte598', 0);
      const contact = integer(read(actor.actual, 'supportContact1db'), 0, 255, 'supportContact1db') << 24 >> 24;
      if (contact !== 0) fail('80067a70 nonzero support reached unsupported actual pointer1e4 ownership');
      if (!updateStage) fail('800590ac reached unsupported source call 80059e58');
      if (updateStage(id) !== undefined) fail('genuine stage-boundary stage returned asynchronously or unexpectedly');
      if (!updateInput) fail('800590b4 reached unsupported source call 800685c0');
      if (updateInput(id) !== undefined) fail('genuine input prefix returned asynchronously or unexpectedly');
      if (!updateControl) fail('800590bc reached unsupported source call 8005a190');
      const controlResult = updateControl(id);
      if (controlResult !== 0 && controlResult !== 1) fail('bounded genuine actor control returned unexpectedly or asynchronously');
      if (controlResult === 0) {
        if (!updateNormal) {
          // Historical boundary: signed5e4 is read before the unresolved table.
          const cue = integer(read(actor.actual, 'ubCue'), 0, 255, 'ubCue');
          const dispatchAddress = (0x802d3300 + ((cue << 24 >> 24) << 2)) >>> 0;
          fail(`800590e0 reached unsupported source table802d3300 entry ${dispatchAddress.toString(16)} before indirect call800590e8`);
        }
        if (updateNormal(id) !== undefined) fail('genuine normal lifecycle returned asynchronously or unexpectedly');
        assertTeamOwners(id, actor, raw); assertCommandOwners(id, actor, raw);
      }
      // Both source branches meet here only after every reached call completes.
      if (!updateAction) fail('80059110 reached unsupported source call 8005a298');
      if (updateAction(id) !== undefined) fail('genuine action request returned asynchronously or unexpectedly');
      if (!updateRates) fail('80059118 reached unsupported source call 8005a378');
      if (updateRates(id) !== undefined) fail('genuine actor rates returned asynchronously or unexpectedly');
      if (!updateCeiling) fail('80059120 reached unsupported source call 80068030');
      const ceilingResult = updateCeiling(id);
      if (ceilingResult !== 0 && ceilingResult !== 1) fail('genuine ceiling tail returned asynchronously or unexpectedly');
      // Source59068 ignores68030's native result and returns void at59134.
      return;
    });},
  });
}
