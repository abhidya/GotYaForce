/** Source8005913c's ordered tail69814 ->696f4 ->69038 ->69354 ->68f9c,
 * including the real694c0 gate and genuine8006a750 cue resets. Evidence:
 * read_archived_actor_cue0_tail_evidence.py (all159 authenticated instructions).
 * Also exposes the five integer control40 helpers authenticated by
 * read_archived_control40_helper_evidence.py; the cue0 tail schedule is unchanged.
 * No callbacks, synthetic helper returns, live-team/player mapping or hydration.
 * Existing actor/team, movement661, status736 and Borg burstArmFrames(+6fb)
 * remain canonical. Only absent57c/58f/7cd get partial copied binding cells.
 * Team+103 is an explicit shared boolean BurstMeterState.charged row subset on
 * the SAME retained charge global; no copied byte array or absent-row default.
 * Raw byte/signed-halfword domains and reached-only source loads/stores apply.
 * Stable synchronous non-proxy own-data owners are admission bounds. Permanent
 * actor claims and incomplete-call poison preserve every effectful prefix.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorMovementFollowupRuntime, SourceActorMovementFollowupBinding} from './actor-movement-followup.js';
import type {SourceActorStatusTimersRuntime, SourceActorStatusTimersBinding, SourceActorStatusBorgOwner} from './actor-status-timers.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime,
  type SourceActorInputChargeBinding, type SourceActorInputChargeGlobal} from './actor-input-charge.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime, type SourceActorCueResetBinding} from './actor-cue-reset.js';
import type {SourceActorAnimationDispatchBinding} from './actor-animation-dispatch.js';
import {isSourceActorAttributeRefreshRuntime, type SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {requireSourceActorNormalInvocation} from './actor-double-prehook.js';

export interface SourceActorCue0TailBinding {byte57c: number; byte58f: number; byte7cd: number}
export interface SourceActorCue0TailSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActualActor' | 'getActorBinding'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getActualBorg' | 'getWorldBinding' | 'getMappingActor' | 'getMovementBinding' | 'getAttributeBinding'>;
  charge: SourceActorInputChargeRuntime;
  cues: SourceActorCueResetRuntime;
  /** Genuine SAME4ac registry. Absent is lazy until69210 actually loads9f. */
  attributes?: SourceActorAttributeRefreshRuntime;
}
export interface SourceActorCue0TailRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorCue0TailBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getMovementBinding(identity: symbol): SourceActorMovementFollowupBinding;
  getStatusBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getActualBorg(identity: symbol): SourceActorStatusBorgOwner;
  getMappingActor(identity: symbol): object;
  getChargeRuntime(): SourceActorInputChargeRuntime;
  getChargeBinding(identity: symbol): Partial<SourceActorInputChargeBinding>;
  getGlobal(): SourceActorInputChargeGlobal;
  getCueRuntime(): SourceActorCueResetRuntime;
  getCueBinding(identity: symbol): Partial<SourceActorCueResetBinding>;
  getDispatchBinding(identity: symbol): SourceActorAnimationDispatchBinding;
  getActorBinding(identity: symbol): Partial<SourceActorCue0TailBinding>;
  /** Additional NEW binding only, never canonical or shared owner duplicates. */
  getSourceOwners(identity: symbol): readonly object[];
  /** Already reached table/row identities only; never loads a source pointer. */
  getKnownTeamStorageOwners(): readonly object[];
  assertActorComplete(identity: symbol): void;
  updateActor(identity: symbol): void;
  test80069814(identity: symbol): 0;
  test800694c0(identity: symbol): 0 | 1;
  test800696f4(identity: symbol): 0 | 1;
  test80069038(identity: symbol): 0 | 1;
  test80069354(identity: symbol): 0 | 1;
  test80068f9c(identity: symbol): 0 | 1;
  test80069210(identity: symbol): 0 | 1;
  test800693fc(identity: symbol): 0 | 1;
  test8006965c(identity: symbol): 0 | 1;
  test800695c4(identity: symbol): 0 | 1;
  test8006952c(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>(), incomplete = new WeakSet<object>();
export function isSourceActorCue0TailRuntime(value: unknown): value is SourceActorCue0TailRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function hasIncompleteSourceActorCue0Tail(actual: object): boolean {return incomplete.has(actual);}
function fail(reason: string): never {
  throw Error(`[actor-cue0-tail] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string, writable = false): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(owner, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
const s8 = (value: number): number => value << 24 >> 24;
export function createSourceActorCue0TailRuntime(sources: SourceActorCue0TailSources): SourceActorCue0TailRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const property = (owner: object, key: string): PropertyDescriptor | undefined => {
    const value = Object.getOwnPropertyDescriptor(owner, key); check(); return value;
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorCue0TailSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const value = Reflect.apply(method, receiver, args); check(); return value;};
  };
  const charge = read(sources, 'charge'), cues = read(sources, 'cues');
  if (!isSourceActorInputChargeRuntime(charge)) fail('charge requires genuine source runtime');
  if (!isSourceActorCueResetRuntime(cues)) fail('cues requires genuine source runtime');
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const movementActor = capture('movement', 'getActualActor'), movementBinding = capture('movement', 'getActorBinding');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusBorg = capture('status', 'getActualBorg'), statusWorld = capture('status', 'getWorldBinding');
  const statusMapping = capture('status', 'getMappingActor'), statusMovement = capture('status', 'getMovementBinding');
  const statusAttribute = capture('status', 'getAttributeBinding');
  const chargeActor = capture('charge', 'getActualActor'), chargeBinding = capture('charge', 'getActorBinding');
  const chargeStatus = capture('charge', 'getStatusBinding'), chargeMapping = capture('charge', 'getMappingActor');
  const chargeGlobal = capture('charge', 'getGlobal'), chargeAttribute = capture('charge', 'getAttributeBinding');
  const chargeData = capture('charge', 'getData'), chargeDescriptors = capture('charge', 'getKnownDescriptorRecords');
  const cueActor = capture('cues', 'getActualActor'), cueMapping = capture('cues', 'getMappingActor');
  const cueBinding = capture('cues', 'getActorBinding'), cueDispatch = capture('cues', 'getDispatchBinding');
  const upperCue = capture('cues', 'dispatchUpperBodyCue');
  const attributeProperty = property(sources, 'attributes');
  const attributes = attributeProperty === undefined ? undefined : read(sources, 'attributes');
  if (attributeProperty !== undefined && !isSourceActorAttributeRefreshRuntime(attributes))
    fail('attributes requires genuine source runtime');
  const attributeActor = attributes === undefined ? undefined : capture('attributes', 'getActualActor');
  const attributeBinding = attributes === undefined ? undefined : capture('attributes', 'getActorBinding');
  const attributeMapping = attributes === undefined ? undefined : capture('attributes', 'getMappingActor');
  const attributeMovement = attributes === undefined ? undefined : capture('attributes', 'getMovementBinding');
  const parameterDescriptor = attributes === undefined ? undefined : capture('attributes', 'getParameterDescriptor');
  const knownParameters = attributes === undefined ? undefined : capture('attributes', 'getKnownParameterDescriptors');
  const global = record(chargeGlobal(), 'source global80433934') as SourceActorInputChargeGlobal;
  const data = record(chargeData(), 'charge data');
  if (global === data) fail('charge global/data owner alias');
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 0, 255, key);
  const word = (owner: unknown, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const half = (owner: unknown, key: string): number => integer(read(owner, key), 0, 0xffff, key);
  const signedHalf = (owner: unknown, key: string): number => integer(read(owner, key), -32768, 32767, key);
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; movement: SourceActorMovementFollowupBinding;
    status: Partial<SourceActorStatusTimersBinding>; borg: SourceActorStatusBorgOwner; mapping: object; attribute: object;
    charge: Partial<SourceActorInputChargeBinding>; cue: Partial<SourceActorCueResetBinding>;
    dispatch: SourceActorAnimationDispatchBinding; binding: Partial<SourceActorCue0TailBinding>; extras: readonly object[];
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  let teamTable: object | undefined;
  const teamRows = new Map<number, object>(), knownTeamOwners = new Set<object>();
  const parameterOwners = new Set<object>(), parameters = new Map<symbol, object>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned cue0-tail actor'); return e;};
  const owners = (e: Entry): object[] => [e.actual, e.world, e.movement, e.status, e.borg, e.mapping,
    e.attribute, e.charge, e.cue, e.dispatch, e.binding];
  const descriptors = (): readonly object[] => {
    const values = chargeDescriptors();
    if (!Array.isArray(values)) fail('charge known descriptors: synchronous owner array required');
    for (const value of values) record(value, 'known charge descriptor');
    return values as object[];
  };
  // Only object-reference metadata is inspected. No table elements/scalars,
  // accessor invocation, or source pointer dereference is performed here.
  const referencedStorage = (e: Entry): readonly object[] => {
    const values: object[] = [];
    const reference = (owner: object, key: string): void => {
      const p = property(owner, key);
      if (p && 'value' in p && p.value !== null && typeof p.value === 'object') values.push(p.value as object);
    };
    reference(data, 'held3970'); reference(data, 'release397c');
    const actuals = new Set<object>([e.actual, ...[...actors.values()].map(actor => actor.actual)]);
    for (const actual of actuals) reference(actual, 'cueTable');
    return values;
  };
  const noShadows = (e: Entry, extra: readonly object[] = []): void => {
    const canonical = new Map<string, object>([
      ['team', e.actual], ['controlWord', e.actual], ['inputEdge5d4', e.actual],
      ['statusWord5b4', e.actual], ['inputHeld5d8', e.actual], ['byte661', e.movement],
      ['short736', e.status], ['burstArmFrames', e.borg], ['byte57c', e.binding],
      ['byte58f', e.binding], ['byte7cd', e.binding], ['ubCue', e.actual], ['ubState', e.actual],
      ['byte588', e.cue], ['byte747', e.status], ['parameter4ac', e.attribute],
    ]);
    const aliases = ['team88', 'byte88', 'field88', 'word5e0', 'flags5e0', 'field5e0', 'controlWord5e0',
      'word5d4', 'flags5d4', 'field5d4', 'inputFlags5d4', 'word5b4', 'flags5b4', 'field5b4',
      'half5d8', 'short5d8', 'word5d8', 'field5d8', 'field661', 'move661',
      'field736', 'timer736', 'byte6fb', 'field6fb', 'timer6fb', 'field57c', 'flags57c',
      'field58f', 'flags58f', 'field7cd', 'flags7cd', 'byte103', 'field103',
      'field588', 'flags588', 'field747', 'flags747', 'field4ac', 'descriptor4ac', 'pointer4ac', 'field9f', 'parameter9f'];
    for (const owner of [...owners(e), global, data, ...extra]) {
      for (const [key, expected] of canonical) if (owner !== expected && property(owner, key) !== undefined)
        fail(`${key}: competing cue0-tail storage on another owner`);
      for (const key of aliases) if (property(owner, key) !== undefined) fail(`${key}: competing cue0-tail storage alias`);
      if (!parameterOwners.has(owner) && property(owner, 'byte9f') !== undefined)
        fail('byte9f: competing cue0-tail parameter storage');
      if (owner !== global && property(owner, 'teamRows103') !== undefined)
        fail('teamRows103: competing cue0-tail global storage');
    }
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(movementActor(id), e.actual, 'movement actor'); stable(movementBinding(id), e.movement, 'movement binding');
    stable(statusActor(id), e.actual, 'status actor'); stable(statusBinding(id), e.status, 'status binding');
    stable(statusBorg(id), e.borg, 'status Borg'); stable(statusWorld(id), e.world, 'status world');
    stable(statusMapping(id), e.mapping, 'status mapping');
    stable(statusMovement(id), e.movement, 'status movement'); stable(statusAttribute(id), e.attribute, 'status attribute');
    stable(chargeActor(id), e.actual, 'charge actor'); stable(chargeBinding(id), e.charge, 'charge binding');
    stable(chargeStatus(id), e.status, 'charge status'); stable(chargeMapping(id), e.mapping, 'charge mapping');
    stable(chargeAttribute(id), e.attribute, 'charge attribute'); stable(chargeGlobal(), global, 'charge global');
    stable(chargeData(), data, 'charge data');
    stable(cueActor(id), e.actual, 'cue actor'); stable(cueMapping(id), e.mapping, 'cue mapping');
    stable(cueBinding(id), e.cue, 'cue binding'); stable(cueDispatch(id), e.dispatch, 'cue dispatch');
    if (attributeActor) {
      stable(attributeActor(id), e.actual, 'attribute actor'); stable(attributeBinding!(id), e.attribute, 'attribute binding');
      stable(attributeMapping!(id), e.mapping, 'attribute mapping'); stable(attributeMovement!(id), e.movement, 'attribute movement');
      const values = knownParameters!();
      if (!Array.isArray(values)) fail('known parameters: synchronous owner array required');
      for (const value of values) parameterOwners.add(record(value, 'known parameter descriptor'));
    }
    const knownDescriptors = descriptors();
    if ([...owners(e), global, data, ...knownTeamOwners].some(owner => knownDescriptors.includes(owner)))
      fail('source owner aliases a known charge descriptor');
    if (parameterOwners.size !== 0 && ([...owners(e), global, data, ...knownTeamOwners, ...knownDescriptors].some(owner => parameterOwners.has(owner)) ||
      referencedStorage(e).some(owner => parameterOwners.has(owner)))) fail('parameter descriptor aliases another source owner');
    if (knownTeamOwners.size !== 0 && referencedStorage(e).some(owner => knownTeamOwners.has(owner)))
      fail('known team storage aliases charge data or actual cue table');
    noShadows(e, [...knownTeamOwners, ...parameterOwners]);
  };
  const assertComplete = (actual: object): void => {
    if (incomplete.has(actual)) fail('actual actor has known incomplete cue0 tail');
  };
  const write = (e: Entry, owner: object, key: string, value: number): void => {
    own(owner, key, true); check(); (owner as Record<string, unknown>)[key] = value;
    incomplete.add(e.actual); check(); // Marker precedes caught mutation-reentry check.
  };
  const cue = (id: symbol, e: Entry, value: number): 0 | 1 => {
    // A genuine reset can store a prefix then fail, so mark before delegation.
    incomplete.add(e.actual);
    const result = upperCue(id, value);
    if (result !== 0 && result !== 1) fail('genuine upper-body cue returned asynchronously or unexpectedly');
    return result;
  };
  const test69814 = (e: Entry): 0 => {
    const rawTeam = byte(e.actual, 'team'); //69814 lbz precedes69818 global pointer.
    stable(chargeGlobal(), global, 'source global80433934');
    const table = record(read(global, 'teamRows103'), 'teamRows103 table');
    if (!Array.isArray(table)) fail('teamRows103: explicit existing row-reference array required');
    if (teamTable !== undefined && teamTable !== table) fail('teamRows103 table owner changed');
    if (assigned.has(table) || table === global || table === data || parameterOwners.has(table) || descriptors().includes(table) || referencedStorage(e).includes(table))
      fail('teamRows103 table aliases another source owner');
    teamTable = table; knownTeamOwners.add(table);
    const team = s8(rawTeam), length = integer(read(table, 'length'), 0, 0xffffffff, 'teamRows103 length');
    if (team < 0 || team >= length) fail('signed team*60+103 outside explicitly owned team rows');
    const row = record(read(table, String(team)), 'teamRows103 selected row');
    if (teamRows.has(team) && teamRows.get(team) !== row) fail('teamRows103 selected row owner changed');
    if (assigned.has(row) || row === table || row === global || row === data || parameterOwners.has(row) || descriptors().includes(row) || referencedStorage(e).includes(row))
      fail('teamRows103 row aliases another source owner');
    teamRows.set(team, row); knownTeamOwners.add(row); noShadows(e, [table, row]);
    const charged = read(row, 'charged'); // Existing boolean semantic owner is precisely the0/1 subset.
    if (typeof charged !== 'boolean') fail('team+103 charged: existing boolean0/1 subset required');
    if (!charged) return 0;
    if ((word(e.actual, 'inputEdge5d4') & 0x200) === 0) return 0;
    write(e, e.borg, 'burstArmFrames', 6);
    return 0;
  };
  const test694c0 = (e: Entry): 0 | 1 => {
    if (s8(byte(e.binding, 'byte7cd')) === 0) return 1;
    return signedHalf(e.status, 'short736') > 0 ? 1 : 0; // One lha retained through neg/andc/srwi.
  };
  const test69210 = (id: symbol, e: Entry): 0 | 1 => {
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((word(e.actual, 'inputEdge5d4') & 2) === 0) return 0;
    if (s8(byte(e.cue, 'byte588')) === 0) return 0;
    const raw7cd = byte(e.binding, 'byte7cd'); // Retained raw r4, never loaded twice.
    if (s8(raw7cd) === 0) {
      const selected = read(e.attribute, 'parameter4ac'); // Capture before747, dereference after747.
      const raw747 = byte(e.status, 'byte747');
      if (!parameterDescriptor) fail('69210 active4ac+9f requires genuine attribute runtime');
      if (typeof selected !== 'symbol') fail('parameter4ac: explicitly owned non-null decoded symbol required');
      const parameter = record(parameterDescriptor(selected), 'parameter4ac descriptor');
      if (!parameterOwners.has(parameter)) fail('parameter4ac descriptor missing from genuine registry');
      if (parameters.has(selected) && parameters.get(selected) !== parameter) fail('parameter4ac descriptor owner changed');
      parameters.set(selected, parameter);
      if (s8(raw747) >= byte(parameter, 'byte9f')) return 0;
    } else if (s8(raw7cd) === 1 && signedHalf(e.status, 'short736') <= 0) return 0;
    return cue(id, e, 8);
  };
  const consumeHeldNibble = (e: Entry): 1 => {
    write(e, e.binding, 'byte58f', (half(e.actual, 'inputHeld5d8') >>> 4) & 15);
    write(e, e.actual, 'inputHeld5d8', half(e.actual, 'inputHeld5d8') & 0xff0f);
    return 1;
  };
  const test693fc = (id: symbol, e: Entry): 0 | 1 => {
    const movement = s8(byte(e.movement, 'byte661')); // One load for both comparisons.
    if (movement === 2 || movement === 5) return 0;
    if (test694c0(e) === 0) return 0;
    if ((word(e.actual, 'controlWord') & 1) !== 0) return 0;
    if ((half(e.actual, 'inputHeld5d8') & 0xf0) === 0) return 0;
    if (cue(id, e, 15) === 0) return 0;
    return consumeHeldNibble(e);
  };
  const test6965c = (id: symbol, e: Entry): 0 | 1 => {
    if (byte(e.movement, 'byte661') !== 2) return 0; // Unsigned lbz comparison, no extsb.
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((half(e.actual, 'inputHeld5d8') & 0xf0) === 0) return 0;
    if (cue(id, e, 22) === 0) return 0;
    return consumeHeldNibble(e);
  };
  const test695c4 = (id: symbol, e: Entry): 0 | 1 => {
    if (byte(e.movement, 'byte661') !== 2) return 0;
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((word(e.actual, 'statusWord5b4') & 0xf0000) === 0) return 0;
    return cue(id, e, 19);
  };
  const test6952c = (id: symbol, e: Entry): 0 | 1 => {
    if (byte(e.movement, 'byte661') !== 2) return 0;
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((word(e.actual, 'statusWord5b4') & 0x100) === 0) return 0;
    return cue(id, e, 18);
  };
  const test696f4 = (id: symbol, e: Entry): 0 | 1 => {
    const movement = s8(byte(e.movement, 'byte661'));
    if (movement !== 2 && movement !== 5) return 0;
    if (test694c0(e) === 0) return 0;
    if ((word(e.actual, 'controlWord') & 3) !== 0) return 0;
    if ((word(e.actual, 'inputEdge5d4') & 0x80) === 0) return 0;
    return cue(id, e, 0x20);
  };
  const test69038 = (id: symbol, e: Entry): 0 | 1 => {
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((word(e.actual, 'inputEdge5d4') & 1) === 0) return 0;
    if ((word(e.actual, 'statusWord5b4') & 0x100) === 0) return 0;
    write(e, e.binding, 'byte57c', 0);
    return cue(id, e, 4);
  };
  const test69354 = (id: symbol, e: Entry): 0 | 1 => {
    if ((word(e.actual, 'controlWord') & 1) !== 0) return 0;
    if ((half(e.actual, 'inputHeld5d8') & 0xf0) === 0) return 0;
    if (cue(id, e, byte(e.movement, 'byte661') === 6 ? 0x25 : 0xc) === 0) return 0;
    write(e, e.binding, 'byte58f', (half(e.actual, 'inputHeld5d8') >>> 4) & 15);
    write(e, e.actual, 'inputHeld5d8', half(e.actual, 'inputHeld5d8') & 0xff0f);
    return 1;
  };
  const test68f9c = (id: symbol, e: Entry): 0 | 1 => {
    if ((word(e.actual, 'controlWord') & 2) !== 0) return 0;
    if ((word(e.actual, 'statusWord5b4') & 0xf0000) === 0) return 0;
    return cue(id, e, byte(e.movement, 'byte661') === 6 ? 0x1d : 1);
  };
  const execute = <T>(id: symbol, run: (e: Entry) => T, normalOnly = false): T => guard(() => {
    const e = entry(id); assertComplete(e.actual);
    if (normalOnly) requireSourceActorNormalInvocation(e.actual);
    admit(id, e);
    const result = run(e); check(); incomplete.delete(e.actual); return result;
  });
  const runtime: SourceActorCue0TailRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source cue0-tail runtime');
      const binding: Partial<SourceActorCue0TailBinding> = {};
      const e: Entry = {actual, world: record(worldBinding(id), 'world binding') as Entry['world'],
        movement: record(movementBinding(id), 'movement binding') as Entry['movement'],
        status: record(statusBinding(id), 'status binding'), borg: record(statusBorg(id), 'actual Borg') as Entry['borg'],
        mapping: record(worldMapping(id), 'mapping actor'), attribute: record(chargeAttribute(id), 'attribute binding'),
        charge: record(chargeBinding(id), 'charge binding'), cue: record(cueBinding(id), 'cue binding'),
        dispatch: record(cueDispatch(id), 'dispatch binding') as Entry['dispatch'], binding, extras: []};
      admit(id, e);
      const records = owners(e);
      if (new Set(records).size !== records.length || records.some(owner => assigned.has(owner) || owner === global ||
        owner === data || knownTeamOwners.has(owner))) fail('source owner alias: distinct canonical and new binding owners required');
      record(initial, 'initial cue0-tail binding'); noShadows({...e, binding: initial});
      for (const key of ['byte57c', 'byte58f', 'byte7cd'] as const)
        if (property(initial, key) !== undefined) binding[key] = byte(initial, key);
      Object.seal(binding); e.extras = Object.freeze([binding]);
      check(); actors.set(id, e); records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getWorldBinding(id) {return entry(id).world;},
    getMovementBinding(id) {return entry(id).movement;}, getStatusBinding(id) {return entry(id).status;},
    getActualBorg(id) {return entry(id).borg;}, getMappingActor(id) {return entry(id).mapping;},
    getChargeRuntime() {return charge;}, getChargeBinding(id) {return entry(id).charge;}, getGlobal() {return global;},
    getCueRuntime() {return cues;}, getCueBinding(id) {return entry(id).cue;}, getDispatchBinding(id) {return entry(id).dispatch;},
    getActorBinding(id) {return entry(id).binding;}, getSourceOwners(id) {return entry(id).extras;},
    getKnownTeamStorageOwners() {return Object.freeze([...knownTeamOwners]);},
    assertActorComplete(id) {assertComplete(entry(id).actual);},
    updateActor(id) {execute(id, e => {
      test69814(e); // Source always returns0, including after the actual6fb store.
      if (test696f4(id, e) !== 0) return;
      if (test69038(id, e) !== 0) return;
      if (test69354(id, e) !== 0) return;
      test68f9c(id, e); // The enclosing caller ignores this final return.
    });},
    test80069814(id) {return execute(id, test69814);}, test800694c0(id) {return execute(id, test694c0);},
    test800696f4(id) {return execute(id, e => test696f4(id, e));},
    test80069038(id) {return execute(id, e => test69038(id, e));},
    test80069354(id) {return execute(id, e => test69354(id, e));},
    test80068f9c(id) {return execute(id, e => test68f9c(id, e));},
    test80069210(id) {return execute(id, e => test69210(id, e), true);},
    test800693fc(id) {return execute(id, e => test693fc(id, e), true);},
    test8006965c(id) {return execute(id, e => test6965c(id, e), true);},
    test800695c4(id) {return execute(id, e => test695c4(id, e), true);},
    test8006952c(id) {return execute(id, e => test6952c(id, e), true);},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
