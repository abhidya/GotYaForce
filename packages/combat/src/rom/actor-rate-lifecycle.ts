/** Bounded actual8005a378, archived8005a378..8005a580 and chunk_0007.c:2816–2900.
 * read_archived_actor_rate_evidence.py authenticates instructions, constants and
 * only table indices1/2. Other nonzero signed indices refuse at the table load.
 * Final timestep is fmuls(1dd0, fmuls(1dcc,768)), NOT the C's left grouping.
 * The actual actor owns768/5f4/5e0, mapping owns1dc8, status owns6fc/71c/1dcc,
 * and the SAME actual Borg owns710/712/70c..70f. Only absent1dd0 is copied.
 * Optional genuine actor-tier-lifecycle supplies its producer6826c on this
 * same1dd0 binding; no universal1/default or automatic hydration is inferred.
 * Mode2 needs the genuine matrix owner's4a4 and an already-bound actor identity.
 * No generic pointer resolver, effect callback, legacy dt/freeze adoption or tick
 * activation. Permanent claims and brands cannot be copied into a fake runtime.
 *
 * Finite exact binary32, RN00/NI0, distinct stable synchronous own-data non-proxy
 * owners are admission bounds, not measured live FPSCR or source-RAM claims.
 * Source scalar reads and writable checks follow reached instructions. Signed
 * zero/subnormals survive; overflow refuses before its destination store. Earlier
 * stores survive every refusal. Captured methods retain receivers and caught
 * same-runtime mutation reentry poisons the enclosing call.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorJointMappingRuntime, SourceActorJointMappingHeader} from './actor-joint-mapping.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding, SourceActorStatusBorgOwner} from './actor-status-timers.js';
import {isSourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateRuntime, type SourceActorMatrixUpdateBinding} from './actor-matrix-update.js';

export interface SourceActorRateLifecycleBinding {field1dd0: number}
export interface SourceActorRateLifecycleSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' |
    'getWorldBinding' | 'getMappingActor' | 'getActualBorg'>;
  /** Optional genuine4a4 owner. Without it, mode2 refuses before the pointer load. */
  matrix?: SourceActorMatrixUpdateRuntime;
}
export interface SourceActorRateLifecycleRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorRateLifecycleBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorStatusBorgOwner;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMappingActor(identity: symbol): SourceActorJointMappingHeader;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getMatrixBinding(identity: symbol): SourceActorMatrixUpdateBinding | undefined;
  getActorBinding(identity: symbol): Partial<SourceActorRateLifecycleBinding>;
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorRateLifecycleRuntime(value: unknown): value is SourceActorRateLifecycleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-rate-lifecycle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
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
/** Two finite f32 significands multiply exactly in binary64 (at most48 bits,
 * exponent range[-298,256]); fround therefore performs the sole source rounding. */
function multiply(a: number, b: number, address: string): number {
  return float(Math.fround(a * b), `${address} fmuls result`);
}
const bits = new DataView(new ArrayBuffer(4));
function fromBits(value: number): number {bits.setUint32(0, value, false); return bits.getFloat32(0, false);}
const ONE = fromBits(0x3f800000), BURST = fromBits(0x3fc00000), FREEZE = fromBits(0x3cf5c28f);
// Four authenticated words, not an inferred allocation or arbitrary table reader.
const SLOW1 = fromBits(0x3f333333), SLOW2 = fromBits(0x3ecccccd);
const HASTE1 = fromBits(0x3fa00000), HASTE2 = fromBits(0x3fc00000);

export function createSourceActorRateLifecycleRuntime(sources: SourceActorRateLifecycleSources): SourceActorRateLifecycleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {busy = false;}
  };
  const read = (r: unknown, key: string): unknown => {const value = own(r, key); check(); return value;};
  const write = (r: unknown, key: string, value: number): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorRateLifecycleSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const mappingActor = capture('mapping', 'getActor');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusWorld = capture('status', 'getWorldBinding'), statusMapping = capture('status', 'getMappingActor');
  const statusBorg = capture('status', 'getActualBorg');
  let matrix: {actor: (id: symbol) => unknown; world: (id: symbol) => unknown;
    mapping: (id: symbol) => unknown; binding: (id: symbol) => unknown} | undefined;
  if (Object.getOwnPropertyDescriptor(sources, 'matrix') !== undefined) {
    if (!isSourceActorMatrixUpdateRuntime(read(sources, 'matrix')))
      fail('matrix requires genuine source runtime, not a pointer callback');
    matrix = {actor: capture('matrix', 'getActualActor'), world: capture('matrix', 'getWorldBinding'),
      mapping: capture('matrix', 'getMappingActor'), binding: capture('matrix', 'getActorBinding')};
  }
  const byte = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const short = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const word = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const f = (r: unknown, key: string): number => float(read(r, key), key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; mapping: SourceActorJointMappingHeader;
    status: Partial<SourceActorStatusTimersBinding>; borg: SourceActorStatusBorgOwner;
    matrix: SourceActorMatrixUpdateBinding | undefined; binding: Partial<SourceActorRateLifecycleBinding>;
  }
  const owners = (e: Entry): object[] => [e.actual, e.world, e.mapping, e.status, e.borg, e.binding,
    ...(e.matrix === undefined ? [] : [e.matrix])];
  const noShadowOwners = (e: Entry): void => {
    const canonical = new Map<string, object | undefined>([
      ['aimRateScale', e.actual], ['timescale', e.actual], ['controlWord', e.actual],
      ['mode4a0', e.world], ['mode4a1', e.world], ['timestep1dc8', e.mapping],
      ['byte6fc', e.status], ['byte71c', e.status], ['field1dcc', e.status],
      ['slowHitTimer', e.borg], ['hasteHitTimer', e.borg], ['slowAuraLevel', e.borg],
      ['hasteAuraLevel', e.borg], ['slowHitLevel', e.borg], ['hasteHitLevel', e.borg],
      ['field1dd0', e.binding], ['link4a4', e.matrix],
    ]);
    const aliases = ['dt', 'freezeFrames', 'aimRateScale768', 'timescale5f4', 'field768', 'field5f4',
      'field1dc8', 'byte4a0', 'byte4a1', 'flags5e0', 'word5e0', 'short710', 'short712',
      'byte70c', 'byte70d', 'byte70e', 'byte70f', 'pointer4a4'];
    for (const owner of owners(e)) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing rate-lifecycle storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing rate-lifecycle storage alias`);
        check();
      }
    }
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned rate-lifecycle actor'); return value;
  };
  const checkMapping = (id: symbol, e: Entry): void => {
    stable(mappingActor(id), e.mapping, 'mapping actor'); stable(statusMapping(id), e.mapping, 'status mapping');
    stable(worldMapping(id), e.mapping, 'world mapping');
  };
  const checkStatus = (id: symbol, e: Entry): void => {
    stable(statusActor(id), e.actual, 'status actor'); stable(statusBinding(id), e.status, 'status binding');
    stable(statusWorld(id), e.world, 'status world');
  };
  const checkMatrix = (id: symbol, e: Entry): void => {
    stable(matrix!.actor(id), e.actual, 'matrix actor'); stable(matrix!.world(id), e.world, 'matrix world');
    stable(matrix!.mapping(id), e.mapping, 'matrix mapping'); stable(matrix!.binding(id), e.matrix!, 'matrix binding');
  };
  const timer = (e: Entry, field: string, level: string): void => {
    const old = short(e.borg, field);
    if (old !== 0) {
      const next = (old - 1) << 16 >> 16;
      write(e.borg, field, next);
      if (next <= 0) write(e.borg, level, 0);
    }
  };
  const scale = (e: Entry, level: string, slow: boolean, load: string, multiplyAt: string): void => {
    const index = byte(e.borg, level) << 24 >> 24;
    if (index === 0) return;
    const rate = f(e.actual, 'aimRateScale'); // lfs768 precedes the indexed table load.
    if (index !== 1 && index !== 2)
      fail(`${load} unsupported ${slow ? '802dd57c' : '802dd58c'} table index ${index}; only authenticated indices1/2 are admitted`);
    const factor = slow ? (index === 1 ? SLOW1 : SLOW2) : (index === 1 ? HASTE1 : HASTE2);
    write(e.actual, 'aimRateScale', multiply(rate, factor, multiplyAt));
  };
  const runtime: SourceActorRateLifecycleRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source rate-lifecycle runtime');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const mapping = record(mappingActor(id), 'mapping actor') as SourceActorJointMappingHeader;
      const status = record(statusBinding(id), 'status binding') as Partial<SourceActorStatusTimersBinding>;
      const borg = record(statusBorg(id), 'actual Borg') as SourceActorStatusBorgOwner;
      const binding: Partial<SourceActorRateLifecycleBinding> = {};
      const e: Entry = {actual, world, mapping, status, borg, binding,
        matrix: matrix === undefined ? undefined : record(matrix.binding(id), 'matrix binding') as SourceActorMatrixUpdateBinding};
      checkStatus(id, e); stable(statusMapping(id), mapping, 'status mapping'); stable(worldMapping(id), mapping, 'world mapping');
      if (matrix !== undefined) checkMatrix(id, e);
      const records = owners(e);
      if (new Set(records).size !== records.length || records.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual/world/mapping/status/Borg/matrix/binding required');
      record(initial, 'initial rate-lifecycle binding'); noShadowOwners(e); noShadowOwners({...e, binding: initial});
      if (Object.getOwnPropertyDescriptor(initial, 'field1dd0') !== undefined) binding.field1dd0 = f(initial, 'field1dd0');
      Object.seal(binding); check(); actors.set(id, e);
      records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActualBorg(id) {return entry(id).borg;},
    getWorldBinding(id) {return entry(id).world;},
    getMappingActor(id) {return entry(id).mapping;},
    getStatusBinding(id) {return entry(id).status;},
    getMatrixBinding(id) {return entry(id).matrix;},
    getActorBinding(id) {return entry(id).binding;},
    updateActor(id) {guard(() => {
      const e = entry(id), {actual, world, status, mapping, borg} = e;
      stable(worldActor(id), actual, 'world actor'); stable(worldBinding(id), world, 'world binding'); noShadowOwners(e);
      if (byte(world, 'mode4a1') !== 0) {
        checkMapping(id, e); write(mapping, 'timestep1dc8', ONE);
        write(actual, 'timescale', ONE); write(actual, 'aimRateScale', ONE); return;
      }
      if (byte(world, 'mode4a0') === 2) {
        if (matrix === undefined) fail('8005a3a4 reached unsupported source pointer4a4 load; genuine matrix owner is required');
        checkMatrix(id, e);
        const link = read(e.matrix, 'link4a4');
        if (typeof link !== 'symbol' || !actors.has(link))
          fail('8005a3a8 linked4a4 requires an already-bound rate actor identity; linked768 load has not executed');
        const peer = entry(link); noShadowOwners(peer); stable(worldActor(link), peer.actual, 'linked actual actor');
        write(actual, 'aimRateScale', f(peer.actual, 'aimRateScale'));
        write(actual, 'timescale', f(peer.actual, 'timescale'));
        checkMapping(link, peer); const timestep = f(peer.mapping, 'timestep1dc8');
        checkMapping(id, e); write(mapping, 'timestep1dc8', timestep); return;
      }
      stable(statusBorg(id), borg, 'actual Borg');
      timer(e, 'slowHitTimer', 'slowHitLevel'); timer(e, 'hasteHitTimer', 'hasteHitLevel');
      write(actual, 'aimRateScale', ONE);
      checkStatus(id, e);
      if (byte(status, 'byte6fc') !== 0) write(actual, 'aimRateScale', BURST);
      scale(e, 'hasteAuraLevel', false, '8005a44c', '8005a450');
      scale(e, 'hasteHitLevel', false, '8005a47c', '8005a480');
      if ((word(actual, 'controlWord') & 0x01000000) === 0 && byte(status, 'byte6fc') === 0 && byte(world, 'mode4a0') === 0) {
        scale(e, 'slowAuraLevel', true, '8005a4d0', '8005a4d4');
        scale(e, 'slowHitLevel', true, '8005a500', '8005a504');
      }
      const freeze = byte(status, 'byte71c');
      if (freeze !== 0) {
        const next = (freeze - 1) & 255; write(status, 'byte71c', next);
        if (next !== 0) {
          write(actual, 'timescale', FREEZE); checkMapping(id, e); write(mapping, 'timestep1dc8', FREEZE); return;
        }
      }
      write(actual, 'timescale', f(actual, 'aimRateScale'));
      const statusRate = f(status, 'field1dcc'), rate = f(actual, 'aimRateScale'), baseRate = f(e.binding, 'field1dd0');
      const first = multiply(statusRate, rate, freeze === 0 ? '8005a570' : '8005a54c');
      const timestep = multiply(baseRate, first, freeze === 0 ? '8005a574' : '8005a550');
      checkMapping(id, e); write(mapping, 'timestep1dc8', timestep);
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
