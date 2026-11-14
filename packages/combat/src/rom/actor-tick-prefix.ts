/** Offline bounded actual80059068 prefix, not a complete actor tick.
 * Archived entry: lfs760/B4,fdivs,stfs760 @5907c..59088; fresh
 * lfs764/B4,fdivs,stfs764 @5908c..59098; real5bab8 @5909c;67a70
 * @590a4; unreconstructed59e58 @590ac. 67a70 clears control5e0 bit00100000
 * then byte598, and only its zero-contact1db branch genuinely returns here.
 * Nonzero contact refuses at the existing unsupported1e4 owner, not a shadow
 * pointer. All paths eventually refuse; no callback stands in for a callee.
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
 * No movement, matrix rebuild, clocks, legacy step or production activation.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeBorgOwner,
  type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';

export interface SourceActorTickPrefixBinding {byte598: number}
export interface SourceActorTickRawDistances {
  readonly boundary: 'externally-decoded-pre59068-raw';
  readonly targetDistance760: number;
  readonly horizontalDistance764: number;
}
export interface SourceActorTickPrefixSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  gauges: SourceActorGaugeScaleRuntime;
}
export interface SourceActorTickPrefixRuntime {
  bindActor(identity: symbol, actualBorg: SourceActorGaugeBorgOwner,
    initial: Readonly<Partial<SourceActorTickPrefixBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorGaugeBorgOwner;
  getActorBinding(identity: symbol): Partial<SourceActorTickPrefixBinding>;
  /** Always refuses at the first unreconstructed reached source helper. */
  ingestRawDistancesAndRun(identity: symbol, epoch: number, raw: SourceActorTickRawDistances): never;
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
  const f = (value: unknown, key: string): number => float(read(value, key), key);
  const noLegacyDistances = (actual: object): void => {
    for (const key of ['speedScalar760', 'speedScalar764', 'kfmSpeedScalar760', 'kfmSpeedScalar764', 'curTargetDist']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`source760/764 owner conflict: legacy ${key} is present`);
      check();
    }
  };
  interface Entry {
    actual: RomActor; borg: SourceActorGaugeBorgOwner; world: object; status: object;
    gauge: object; binding: Partial<SourceActorTickPrefixBinding>; lastEpoch: number;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const actor = actors.get(id); if (!actor) fail('unknown/non-owned tick-prefix actor'); return actor;};
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): void => {
    if (get(id) !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const owners = (id: symbol, actor: Entry): void => {
    stable(worldActor, id, actor.actual, 'world actor'); stable(gaugeActor, id, actor.actual, 'gauge actor');
    stable(gaugeBorg, id, actor.borg, 'gauge Borg'); stable(worldBinding, id, actor.world, 'world binding');
    stable(gaugeStatus, id, actor.status, 'status binding'); stable(gaugeBinding, id, actor.gauge, 'gauge binding');
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
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value)))
        fail('source owner alias: distinct actual actor/Borg/world/status/gauge required');
      noLegacyDistances(actual); record(initial, 'initial tick-prefix binding');
      const binding: Partial<SourceActorTickPrefixBinding> = {};
      if (Object.getOwnPropertyDescriptor(initial, 'byte598') !== undefined)
        binding.byte598 = integer(read(initial, 'byte598'), 0, 255, 'byte598');
      check(); actors.set(id, {actual, borg, world, status, gauge, binding: Object.seal(binding), lastEpoch: -1});
      records.forEach(value => assigned.add(value)); assigned.add(binding); claimedActors.add(actual);
    });},
    getActualActor(id: symbol) {return entry(id).actual;},
    getActualBorg(id: symbol) {return entry(id).borg;},
    getActorBinding(id: symbol) {return entry(id).binding;},
    ingestRawDistancesAndRun(id: symbol, epoch: number, raw: SourceActorTickRawDistances): never {return guard(() => {
      const actor = entry(id);
      const next = integer(epoch, 0, Number.MAX_SAFE_INTEGER, 'pre59068 raw-input epoch');
      if (next <= actor.lastEpoch) fail('pre59068 raw-input epoch already consumed or out of order');
      actor.lastEpoch = next; // Once attempted, never retry or silently normalize twice.
      owners(id, actor); noLegacyDistances(actor.actual); record(raw, 'explicit decoded raw distances');
      if (assigned.has(raw) || raw === read(actor.world, 'scale58') || raw === read(actor.borg, 'paramTier'))
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
      fail('800590ac reached unsupported source call 80059e58');
    });},
  });
}
