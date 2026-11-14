/** Bounded actual8006826c and8006817c, explicit offline calls only.
 * Evidence: actor-tier-lifecycle-evidence-2026-11-14.md and
 * read_archived_actor_tier_evidence.py authenticate the complete spans.
 * Archived instructions fix signed clamp precedence, the second4ac load, the
 * unsigned descriptor+a3 selector and three successive lfs/stfs pairs. Only
 * pointer cells804339e0/e4 and rows15/16/17 of their selected targets are
 * authenticated. These six rows do not establish table extents or production
 * family/descriptor provenance. No generic address/table callback is admitted.
 *
 * Actual74a stays on the SAME Borg.paramTier.tier; only absent74b/c/d are
 * explicit decoded signed-byte cells. stb keeps its low byte, represented here
 * as signed[-128,127], exactly as the existing tier owner. B8,1dd0 and5f8 stay
 * on genuine gauge/rate/actual owners. Shared match1f stays on matrix globals.
 * No tier, rate, timestep, descriptor or global snapshot/default is created.
 *
 * Non-proxy own-data records and stable synchronous borrowed owners are host
 * admission bounds. Reached reads/stores remain lazy; prior stores survive
 * refusal. Methods preserve captured receivers, caught reentry poisons the
 * call, brands are immutable and actual-actor claims are permanent. This is
 * not full56180 hydration, full59068, production activation or replay proof.
 */
import type {ActorParamTier} from '../types.js';
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding} from './actor-status-timers.js';
import type {SourceActorAttributeRefreshRuntime, SourceActorAttributeRefreshBinding,
  SourceActorAttributeParameterDescriptor} from './actor-attribute-refresh.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeScaleRuntime,
  type SourceActorGaugeScaleBinding, type SourceActorGaugeBorgOwner} from './actor-gauge-scale.js';
import {isSourceActorRateLifecycleRuntime, type SourceActorRateLifecycleRuntime,
  type SourceActorRateLifecycleBinding} from './actor-rate-lifecycle.js';
import {isSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateRuntime,
  type SourceActorMatrixUpdateBinding, type SourceActorMatrixUpdateGlobals} from './actor-matrix-update.js';

export interface SourceActorTierLifecycleBinding {
  /** Explicit decoded signed bytes, not unsigned raw-byte aliases. */
  signed74b: number; signed74c: number; signed74d: number;
}
export interface SourceActorTierLifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActualBorg' | 'getActorBinding' |
    'getWorldBinding' | 'getMappingActor' | 'getAttributeBinding'>;
  attributes: Pick<SourceActorAttributeRefreshRuntime, 'getActualActor' | 'getActorBinding' | 'getParameterDescriptor'>;
  gauges: SourceActorGaugeScaleRuntime;
  rates: SourceActorRateLifecycleRuntime;
  matrix: SourceActorMatrixUpdateRuntime;
}
export interface SourceActorTierLifecycleRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorTierLifecycleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorGaugeBorgOwner;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): object;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getAttributeBinding(identity: symbol): Partial<SourceActorAttributeRefreshBinding>;
  getGaugeBinding(identity: symbol): Partial<SourceActorGaugeScaleBinding>;
  getRateBinding(identity: symbol): Partial<SourceActorRateLifecycleBinding>;
  getMatrixBinding(identity: symbol): SourceActorMatrixUpdateBinding;
  getTierOwner(identity: symbol): ActorParamTier;
  getActorBinding(identity: symbol): Partial<SourceActorTierLifecycleBinding>;
  getMatchGlobals(): SourceActorMatrixUpdateGlobals;
  refreshActor(identity: symbol): void;
  applyDelta127(identity: symbol, signedDelta: number): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorTierLifecycleRuntime(value: unknown): value is SourceActorTierLifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-tier-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(value: unknown, key: string, writable = false): unknown {
  if (value === null || typeof value !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(value, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
const words = new DataView(new ArrayBuffer(4));
function fromBits(bits: number): number {words.setUint32(0, bits, false); return words.getFloat32(0, false);}
// Six authenticated12-byte windows, NOT inferred allocations or host JSON.
const ROWS = Object.freeze([
  Object.freeze([
    Object.freeze([0x3f4f5c29, 0x3f800000, 0x3f4f5c29]),
    Object.freeze([0x3f800000, 0x3f800000, 0x3f800000]),
    Object.freeze([0x3fb33333, 0x3f7ae148, 0x3fb33333]),
  ]),
  Object.freeze([
    Object.freeze([0x3f4f5c29, 0x3f800000, 0x3f4f5c29]),
    Object.freeze([0x3f800000, 0x3f800000, 0x3f800000]),
    Object.freeze([0x3f99999a, 0x3f7ae148, 0x3f99999a]),
  ]),
]);
export function createSourceActorTierLifecycleRuntime(sources: SourceActorTierLifecycleSources): SourceActorTierLifecycleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const read = (value: unknown, key: string): unknown => {const result = own(value, key); check(); return result;};
  const write = (value: unknown, key: string, next: number): void => {
    own(value, key, true); check(); (value as Record<string, unknown>)[key] = next; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorTierLifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  if (!isSourceActorGaugeScaleRuntime(read(sources, 'gauges'))) fail('gauges requires genuine source runtime');
  if (!isSourceActorRateLifecycleRuntime(read(sources, 'rates'))) fail('rates requires genuine source runtime');
  if (!isSourceActorMatrixUpdateRuntime(read(sources, 'matrix'))) fail('matrix requires genuine source runtime');
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const statusActor = capture('status', 'getActualActor'), statusBorg = capture('status', 'getActualBorg');
  const statusBinding = capture('status', 'getActorBinding'), statusWorld = capture('status', 'getWorldBinding');
  const statusMapping = capture('status', 'getMappingActor'), statusAttribute = capture('status', 'getAttributeBinding');
  const attributeActor = capture('attributes', 'getActualActor'), attributeBinding = capture('attributes', 'getActorBinding');
  const parameterDescriptor = capture('attributes', 'getParameterDescriptor');
  const gaugeActor = capture('gauges', 'getActualActor'), gaugeBorg = capture('gauges', 'getActualBorg');
  const gaugeStatus = capture('gauges', 'getStatusBinding'), gaugeBinding = capture('gauges', 'getActorBinding');
  const gaugeWorld = capture('gauges', 'getWorldBinding'), gaugeTier = capture('gauges', 'getTierOwner');
  const rateActor = capture('rates', 'getActualActor'), rateBorg = capture('rates', 'getActualBorg');
  const rateWorld = capture('rates', 'getWorldBinding'), rateMapping = capture('rates', 'getMappingActor');
  const rateStatus = capture('rates', 'getStatusBinding'), rateBinding = capture('rates', 'getActorBinding');
  const rateMatrix = capture('rates', 'getMatrixBinding');
  const matrixActor = capture('matrix', 'getActualActor'), matrixWorld = capture('matrix', 'getWorldBinding');
  const matrixMapping = capture('matrix', 'getMappingActor'), matrixBinding = capture('matrix', 'getActorBinding');
  const matrixGlobals = capture('matrix', 'getGlobals');
  const globals = record(matrixGlobals(), 'shared match globals80433934') as SourceActorMatrixUpdateGlobals;
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const signed = (value: unknown, key: string): number => integer(read(value, key), -128, 127, key);
  const byte = (value: unknown, key: string): number => integer(read(value, key), 0, 255, key);
  const pointer = (value: unknown): symbol | null => {
    if (value !== null && typeof value !== 'symbol') fail('parameter4ac: decoded symbol or null required');
    return value;
  };
  interface Entry {
    actual: RomActor; borg: SourceActorGaugeBorgOwner; tier: ActorParamTier;
    world: SourceActorWorldMatrixBinding; mapping: object; status: Partial<SourceActorStatusTimersBinding>;
    attributes: Partial<SourceActorAttributeRefreshBinding>; gauge: Partial<SourceActorGaugeScaleBinding>;
    rate: Partial<SourceActorRateLifecycleBinding>; matrix: SourceActorMatrixUpdateBinding;
    binding: Partial<SourceActorTierLifecycleBinding>;
  }
  const owners = (e: Entry): object[] => [e.actual, e.borg, e.tier, e.world, e.mapping, e.status,
    e.attributes, e.gauge, e.rate, e.matrix, e.binding];
  const noShadowOwners = (e: Entry, descriptor?: object): void => {
    const canonical = new Map<string, object | undefined>([
      ['paramTier', e.borg], ['tier', e.tier], ['deltaAccum', e.tier], ['timerFrames', e.tier],
      ['signed74b', e.binding], ['signed74c', e.binding], ['signed74d', e.binding],
      ['parameter4ac', e.attributes], ['byteA3', descriptor], ['targetScaleB8', e.gauge],
      ['field1dd0', e.rate], ['tierScale', e.actual], ['byte1f', globals],
      ['timescale', e.actual], ['aimRateScale', e.actual], ['timestep1dc8', e.mapping],
      ['field1dcc', e.status],
    ]);
    const aliases = ['byte74a', 'byte74b', 'byte74c', 'byte74d', 'field74a', 'field74b', 'field74c',
      'field74d', 'tier74a', 'pointer4ac', 'fieldB8', 'scaleB8', 'field5f8', 'tierScale5f8',
      'global1f', 'field1f', 'selectorA3', 'dt', 'field1dc8', 'field768', 'field5f4'];
    for (const owner of [...owners(e), globals, ...(descriptor === undefined ? [] : [descriptor])]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing tier-lifecycle storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing tier-lifecycle storage alias`);
        check();
      }
    }
  };
  const checkOwners = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(statusActor(id), e.actual, 'status actor'); stable(statusBorg(id), e.borg, 'status Borg');
    stable(statusBinding(id), e.status, 'status binding'); stable(statusWorld(id), e.world, 'status world');
    stable(statusMapping(id), e.mapping, 'status mapping'); stable(statusAttribute(id), e.attributes, 'status attributes');
    stable(attributeActor(id), e.actual, 'attribute actor'); stable(attributeBinding(id), e.attributes, 'attribute binding');
    stable(gaugeActor(id), e.actual, 'gauge actor'); stable(gaugeBorg(id), e.borg, 'gauge Borg');
    stable(gaugeStatus(id), e.status, 'gauge status'); stable(gaugeBinding(id), e.gauge, 'gauge binding');
    stable(gaugeWorld(id), e.world, 'gauge world'); stable(gaugeTier(id), e.tier, 'gauge tier');
    stable(rateActor(id), e.actual, 'rate actor'); stable(rateBorg(id), e.borg, 'rate Borg');
    stable(rateWorld(id), e.world, 'rate world'); stable(rateMapping(id), e.mapping, 'rate mapping');
    stable(rateStatus(id), e.status, 'rate status'); stable(rateBinding(id), e.rate, 'rate binding');
    stable(matrixActor(id), e.actual, 'matrix actor'); stable(matrixWorld(id), e.world, 'matrix world');
    stable(matrixMapping(id), e.mapping, 'matrix mapping'); stable(matrixBinding(id), e.matrix, 'matrix binding');
    // Rate mode2 may be deliberately unavailable, but cannot name another4a4 owner.
    const linked = rateMatrix(id); if (linked !== undefined) stable(linked, e.matrix, 'rate matrix');
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const descriptors = new Map<symbol, Partial<SourceActorAttributeParameterDescriptor>>();
  const descriptorOwners = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned tier-lifecycle actor'); return value;
  };
  const refresh = (id: symbol, e: Entry): void => {
    checkOwners(id, e); noShadowOwners(e);
    //6826c first4ac only tests null. It does not dereference the descriptor.
    if (pointer(read(e.attributes, 'parameter4ac')) === null) return;
    stable(read(e.borg, 'paramTier'), e.tier, 'actual Borg.paramTier');
    const tier = signed(e.tier, 'tier'), upper = signed(e.binding, 'signed74d');
    if (tier > upper) write(e.binding, 'signed74b', upper);
    else {
      const lower = signed(e.binding, 'signed74c');
      write(e.binding, 'signed74b', tier < lower ? lower : tier);
    }
    //682b4 reload4ac BEFORE682bc reload74b, BEFORE682c4 descriptor+a3.
    const selected = pointer(read(e.attributes, 'parameter4ac'));
    const rowIndex = signed(e.binding, 'signed74b');
    if (selected === null) fail('800682c4 reloaded parameter4ac is null before descriptor+a3 load');
    const descriptor = record(parameterDescriptor(selected), 'parameter4ac descriptor') as Partial<SourceActorAttributeParameterDescriptor>;
    const prior = descriptors.get(selected);
    if (prior !== undefined) stable(descriptor, prior, 'parameter4ac descriptor');
    else {
      if (descriptor === globals || assigned.has(descriptor) || descriptorOwners.has(descriptor))
        fail('parameter4ac descriptor aliases another source owner');
      descriptors.set(selected, descriptor); descriptorOwners.add(descriptor);
    }
    noShadowOwners(e, descriptor);
    const selector = byte(descriptor, 'byteA3');
    if (selector !== 0 && selector !== 1)
      fail(`800682d4 unsupported selector ${selector}; only pointer cells804339e0/e4 are authenticated`);
    if (rowIndex < 15 || rowIndex > 17)
      fail(`800682dc unsupported table row ${rowIndex}; only rows15/16/17 are authenticated`);
    const row = ROWS[selector]![rowIndex - 15]!;
    write(e.gauge, 'targetScaleB8', fromBits(row[0]!));
    write(e.rate, 'field1dd0', fromBits(row[1]!));
    write(e.actual, 'tierScale', fromBits(row[2]!));
  };
  const runtime: SourceActorTierLifecycleRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'actual actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source tier-lifecycle runtime');
      const borg = record(gaugeBorg(id), 'actual Borg') as SourceActorGaugeBorgOwner;
      const e: Entry = {actual, borg, tier: record(read(borg, 'paramTier'), 'actual Borg.paramTier') as ActorParamTier,
        world: record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding,
        mapping: record(worldMapping(id), 'mapping actor'),
        status: record(statusBinding(id), 'status binding') as Partial<SourceActorStatusTimersBinding>,
        attributes: record(attributeBinding(id), 'attribute binding') as Partial<SourceActorAttributeRefreshBinding>,
        gauge: record(gaugeBinding(id), 'gauge binding') as Partial<SourceActorGaugeScaleBinding>,
        rate: record(rateBinding(id), 'rate binding') as Partial<SourceActorRateLifecycleBinding>,
        matrix: record(matrixBinding(id), 'matrix binding') as SourceActorMatrixUpdateBinding, binding: {}};
      checkOwners(id, e);
      const records = owners(e);
      if (new Set([...records, globals]).size !== records.length + 1 ||
          records.some(value => assigned.has(value) || descriptorOwners.has(value)))
        fail('source owner alias: distinct actor/Borg/tier/world/mapping/status/attribute/gauge/rate/matrix/binding/globals required');
      record(initial, 'initial tier binding'); noShadowOwners(e); noShadowOwners({...e, binding: initial});
      for (const key of ['signed74b', 'signed74c', 'signed74d'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) e.binding[key] = signed(initial, key);
      Object.seal(e.binding); check(); actors.set(id, e);
      records.forEach(value => assigned.add(value)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActualBorg(id) {return entry(id).borg;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getStatusBinding(id) {return entry(id).status;},
    getAttributeBinding(id) {return entry(id).attributes;},
    getGaugeBinding(id) {return entry(id).gauge;},
    getRateBinding(id) {return entry(id).rate;},
    getMatrixBinding(id) {return entry(id).matrix;},
    getTierOwner(id) {return entry(id).tier;},
    getActorBinding(id) {return entry(id).binding;},
    getMatchGlobals() {return globals;},
    refreshActor(id) {guard(() => refresh(id, entry(id)));},
    applyDelta127(id, signedDelta) {guard(() => {
      const e = entry(id); checkOwners(id, e); noShadowOwners(e);
      stable(matrixGlobals(), globals, 'shared match globals80433934');
      if ((byte(globals, 'byte1f') << 24 >> 24) !== 0) return;
      stable(read(e.borg, 'paramTier'), e.tier, 'actual Borg.paramTier');
      const before = signed(e.tier, 'tier');
      const delta = integer(signedDelta, -2147483648, 2147483647, 'signedDelta');
      const sum = (before + delta) | 0; //681a0 add wraps before signed compares.
      write(e.tier, 'tier', sum > 127 ? 127 : sum < -127 ? -127 : sum);
      refresh(id, e); // Genuine6826c, within the same guarded call, no host helper.
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
