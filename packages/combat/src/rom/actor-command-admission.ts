/** Bounded ordinary command admission: authentic 8006c674 null508 return,
 * 80069f8c direction store, source-addressed 4ec dispatch and
 * 8006a104, including mandatory 8006bda8 capture, genuine cue resets, all six
 * visibility stores, canonical stream/ammo owners and the real ea2ec early
 * return for explicitly supplied signed match.byte45 >=5. Evidence:
 * read_archived_actor_command_admission_evidence.py and its fixed witness.
 *
 * This is NOT ordinary active-match audio: byte45<5 refuses at its RNG call.
 * Non-null direction targets, active captured targets, nonzero trig, active
 * 4beb8 and ammo debit/sound remain ordered boundaries. No callbacks stand in
 * for those callees and no owner/default forces a skip. Zero trig requires the
 * explicit GQR5 signed16/scale0 profile, RN00/NI0 and authenticated constants.
 * Existing actual/world/mapping/attribute/charge/action/stream/status owners
 * remain live; only absent504/508/c8/d0 get copied partial cells. Explicit raw
 * bytes extend actual.commandTable; normalized command records are not used.
 * Stable synchronous non-proxy own-data owners are host admission bounds.
 * Reads and destination checks stay lazy; failures retain their prefix and
 * permanently mark an effectful incomplete call. No tick or input hydration.
 */
import type {RomActor, RomVisibilityTarget} from './actor.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import type {SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import {isSourceStreamWaitRuntime, type SourceStreamWaitRuntime} from './stream-wait.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime,
  type SourceActorInputChargeBinding, type SourceActorInputChargeGlobal, type SourceActorInputChargeData} from './actor-input-charge.js';
import {isSourceActorActionRequestRuntime, type SourceActorActionRequestRuntime,
  type SourceActorActionRequestBinding} from './actor-action-request.js';
import {isSourceActorCueResetRuntime, type SourceActorCueResetRuntime,
  type SourceActorCueResetBinding} from './actor-cue-reset.js';
import type {SourceActorAnimationDispatchBinding} from './actor-animation-dispatch.js';

export interface SourceActorCommandAdmissionBinding {
  pointer504: object | null;
  pointer508: RomVisibilityTarget | null;
  pointerc8: object | null;
  byteD0: number;
}
export interface SourceActorCommandAdmissionSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor' | 'getWorldMatrix'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getWorldBinding' |
    'getMappingActor' | 'getAttributeBinding' | 'getAmmoSlot' | 'getStartBinding'>;
  attributes: Pick<SourceActorAttributeRefreshRuntime, 'getActualActor' | 'getActorBinding' | 'getDescriptorBinding'>;
  charge: SourceActorInputChargeRuntime;
  actionRequest: SourceActorActionRequestRuntime;
  cues: SourceActorCueResetRuntime;
  streams: SourceStreamWaitRuntime;
  /** Explicit host profile; no inference from another runtime or live GQR. */
  gqr5?: number;
}
export interface SourceActorCommandAdmissionRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorCommandAdmissionBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getStatusBinding(identity: symbol): object;
  getMappingActor(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getChargeRuntime(): SourceActorInputChargeRuntime;
  getChargeBinding(identity: symbol): Partial<SourceActorInputChargeBinding>;
  getActionRuntime(): SourceActorActionRequestRuntime;
  getActionBinding(identity: symbol): Partial<SourceActorActionRequestBinding>;
  getCueRuntime(): SourceActorCueResetRuntime;
  getCueBinding(identity: symbol): Partial<SourceActorCueResetBinding>;
  getDispatchBinding(identity: symbol): SourceActorAnimationDispatchBinding;
  getStartBinding(identity: symbol): object;
  getStreamBinding(identity: symbol): object;
  getGlobal(): SourceActorInputChargeGlobal;
  getData(): SourceActorInputChargeData;
  getActorBinding(identity: symbol): Partial<SourceActorCommandAdmissionBinding>;
  /** Only new absent-field binding; not copies of canonical source owners. */
  getSourceOwners(identity: symbol): readonly object[];
  /** Already reached owners only; this getter never loads source pointers. */
  getKnownStorageOwners(): readonly object[];
  getKnownStorageEntries(): readonly Readonly<{owner: object; kind: string}>[];
  assertActorComplete(identity: symbol): void;
  dispatchSubtypeDirection(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>(), incomplete = new WeakSet<object>();
export function isSourceActorCommandAdmissionRuntime(value: unknown): value is SourceActorCommandAdmissionRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function hasIncompleteSourceActorCommandAdmission(actual: object): boolean {return incomplete.has(actual);}
function fail(reason: string): never {
  throw Error(`[actor-command-admission] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
const s8 = (value: number): number => value << 24 >> 24;
const s16 = (value: number): number => value << 16 >> 16;
const FLAGS = Object.freeze([58, 4, 56, 4, 56, 0, 56, 0, 56, 0, 56, 0]);
const WARMUPS = ['field63c', 'field640', 'field644'] as const;
const BANKS = ['field648', 'field64c', 'field650'] as const;
export function createSourceActorCommandAdmissionRuntime(sources: SourceActorCommandAdmissionSources): SourceActorCommandAdmissionRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const property = (owner: object, key: string): PropertyDescriptor | undefined => {
    const result = Object.getOwnPropertyDescriptor(owner, key); check(); return result;
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const pointer = (value: unknown, where: string): object | null => value === null ? null : record(value, where);
  const capture = (name: keyof SourceActorCommandAdmissionSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const result = Reflect.apply(method, receiver, args); check(); return result;};
  };
  const charge = read(sources, 'charge'), action = read(sources, 'actionRequest'), cues = read(sources, 'cues');
  if (!isSourceStreamWaitRuntime(read(sources, 'streams'))) fail('streams requires genuine source runtime');
  if (!isSourceActorInputChargeRuntime(charge)) fail('charge requires genuine source runtime');
  if (!isSourceActorActionRequestRuntime(action)) fail('actionRequest requires genuine source runtime');
  if (!isSourceActorCueResetRuntime(cues)) fail('cues requires genuine source runtime');
  const profile = property(sources, 'gqr5');
  if (profile && !('value' in profile)) fail('gqr5: own data property required');
  const gqr5: unknown = profile?.value;
  const wa = capture('world', 'getActualActor'), wb = capture('world', 'getActorBinding');
  const wm = capture('world', 'getMappingActor'), matrix = capture('world', 'getWorldMatrix');
  const sa = capture('status', 'getActualActor'), sb = capture('status', 'getActorBinding');
  const sw = capture('status', 'getWorldBinding'), sm = capture('status', 'getMappingActor');
  const sat = capture('status', 'getAttributeBinding'), ammo = capture('status', 'getAmmoSlot');
  const ss = capture('status', 'getStartBinding');
  const aa = capture('attributes', 'getActualActor'), ab = capture('attributes', 'getActorBinding');
  const descriptor = capture('attributes', 'getDescriptorBinding');
  const ca = capture('charge', 'getActualActor'), cb = capture('charge', 'getActorBinding');
  const cs = capture('charge', 'getStatusBinding'), cm = capture('charge', 'getMappingActor');
  const cat = capture('charge', 'getAttributeBinding'), cg = capture('charge', 'getGlobal'), cd = capture('charge', 'getData');
  const knownDescriptors = capture('charge', 'getKnownDescriptorRecords');
  const ra = capture('actionRequest', 'getActualActor'), rw = capture('actionRequest', 'getWorldBinding');
  const rb = capture('actionRequest', 'getActorBinding');
  const qa = capture('cues', 'getActualActor'), qm = capture('cues', 'getMappingActor');
  const qb = capture('cues', 'getActorBinding'), qd = capture('cues', 'getDispatchBinding');
  const full = capture('cues', 'dispatchFullBodyCue'), upper = capture('cues', 'dispatchUpperBodyCue');
  const start = capture('streams', 'getStartActorBinding'), stream = capture('streams', 'getActorBinding');
  const global = record(cg(), 'shared match global') as SourceActorInputChargeGlobal;
  const data = record(cd(), 'shared charge constants/data') as SourceActorInputChargeData;
  if (global === data) fail('shared global/data owner alias');
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 0, 255, key);
  const word = (owner: unknown, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const half = (owner: unknown, key: string): number => integer(read(owner, key), 0, 65535, key);
  const signedHalf = (owner: unknown, key: string): number => integer(read(owner, key), -32768, 32767, key);
  const f = (owner: unknown, key: string): number => float(read(owner, key), key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {
    id: symbol; actual: RomActor; world: SourceActorWorldMatrixBinding; status: object; mapping: object; attribute: object;
    charge: Partial<SourceActorInputChargeBinding>; action: Partial<SourceActorActionRequestBinding>;
    cue: Partial<SourceActorCueResetBinding>; dispatch: SourceActorAnimationDispatchBinding;
    start: object; stream: object; binding: Partial<SourceActorCommandAdmissionBinding>; extras: readonly object[];
    commandRoot?: object; aim?: object;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const storage = new Map<object, string>(), exclusiveStorage = new Map<object, symbol>();
  const roots = new Map<object, object>(), pointerRoots = new Map<object, object>();
  const rows = new Map<object, Map<number, object>>();
  const descriptorRows = new Map<symbol, object>(), descriptorIds = new Map<object, symbol>();
  const matrixRows = new Map<symbol, Map<number, object>>(), ammoRows = new Map<symbol, Map<number, object>>();
  const ammoCells = new Map<object, object>();
  let roster: object | undefined, flagTable: object | undefined;
  const rosterRows = new Map<number, object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned admission actor'); return value;};
  const owners = (e: Entry): object[] => [e.actual, e.world, e.status, e.mapping, e.attribute, e.charge,
    e.action, e.cue, e.dispatch, e.start, e.stream, e.binding];
  const descriptors = (): readonly object[] => {
    const values = knownDescriptors();
    if (!Array.isArray(values)) fail('charge known descriptors: synchronous array required');
    for (const value of values) record(value, 'known charge descriptor');
    return values;
  };
  const noShadows = (e: Entry, extras: readonly object[] = [], target?: object): void => {
    const canonical = new Map<string, object>([
      ['cmdButton', e.actual], ['cmdSubtype', e.actual], ['cmdChargedRanged', e.actual], ['prevActionIndex', e.actual],
      ['actionIndex', e.actual], ['variantIndex', e.actual], ['controlWord', e.actual], ['stateTimer', e.actual],
      ['visibilityTarget', e.actual], ['visibilityRoster', e.actual], ['visibilityBit', e.actual], ['heading', e.actual],
      ['aimOrigin518', e.actual], ['targetDistance760', e.actual], ['horizontalDistance764', e.actual],
      ['stateFlagA', e.actual], ['stateFlagB', e.actual], ['commandTable', e.actual], ['descriptor4b0', e.mapping],
      ['yawOffset6b8', e.world], ['byte7d2', e.action], ['marker709', e.start], ['blockedMask1d9a', e.stream],
      ['pointer504', e.binding], ['pointer508', e.binding], ['pointerc8', e.binding], ['byteD0', e.binding],
      ...WARMUPS.map(key => [key, e.charge] as [string, object]), ...BANKS.map(key => [key, e.charge] as [string, object]),
    ]);
    const aliases = ['byte585','byte586','byte587','byte584','byte580','byte581','field694','pointer4ec','field4ec',
      'pointer4b0','pointerCC','pointercc','pointerC8','field504','field508','fieldc8','fieldD0','byte709',
      'byte595','field595','flags595','byte1d9a','field518','field51c','field520','field760','field764','byte57a','byte57b','byte3e5'];
    for (const owner of [...owners(e), global, data, ...extras]) {
      for (const [key, expected] of canonical) if (owner !== expected &&
        !(key === 'controlWord' && (owner === target || storage.get(owner) === 'visibility-target')) && property(owner, key) !== undefined)
        fail(`${key}: competing command-admission storage on another owner`);
      for (const key of aliases) if (property(owner, key) !== undefined) fail(`${key}: competing command-admission storage alias`);
      if (owner !== global && property(owner, 'byte45') !== undefined) fail('byte45: competing match-global storage');
      for (const key of ['float8043762c', 'float80437678', 'float80437078', 'flags3994'])
        if (owner !== data && property(owner, key) !== undefined) fail(`${key}: competing shared data storage`);
    }
  };
  // Metadata-only references prevent new storage from aliasing a distinct live
  // canonical vector/table. No source scalar or source pointer is read here.
  const referenced = (value: object, allowed: string): void => {
    const refs: [object, string, string][] = [[data, 'held3970', 'held'], [data, 'release397c', 'release'], [data, 'flags3994', 'flags']];
    for (const e of actors.values()) for (const [key, kind] of [['pos','position'],['motion','motion'],['savedGroundPos','saved-position'],
      ['afterimageSamplePos','afterimage-position'],['targetCache5e8','target-cache'],['partAimAnchors','legacy-anchors'],
      ['actionSpeedRows','speed-rows'],['aimOrigin518','aim'],
      ['commandTable','command-root'],['visibilityRoster','roster'],['cueTable','cue-table']] as const) refs.push([e.actual,key,kind]);
    for (const [owner, key, kind] of refs) {
      const p = property(owner, key);
      if (p && 'value' in p && p.value === value && kind !== allowed) fail(`${allowed}: storage aliases ${key}`);
    }
  };
  const retain = (e: Entry, value: object, kind: string): void => {
    const prior = storage.get(value);
    if (['aim', 'matrix-row', 'ammo-slot', 'ammo-cell'].includes(kind)) {
      if (exclusiveStorage.has(value) && exclusiveStorage.get(value) !== e.id) fail(`${kind}: cross-actor storage alias`);
      exclusiveStorage.set(value, e.id);
    }
    if (assigned.has(value) || value === global || value === data || descriptors().includes(value) || (prior !== undefined && prior !== kind))
      fail(`${kind}: aliases another source owner`);
    referenced(value, kind); noShadows(e, [value], kind === 'visibility-target' ? value : undefined); storage.set(value, kind);
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(wa(id), e.actual, 'world actor'); stable(wb(id), e.world, 'world binding'); stable(wm(id), e.mapping, 'world mapping');
    stable(sa(id), e.actual, 'status actor'); stable(sb(id), e.status, 'status binding'); stable(sw(id), e.world, 'status world');
    stable(sm(id), e.mapping, 'status mapping'); stable(sat(id), e.attribute, 'status attribute'); stable(ss(id), e.start, 'status stream start');
    stable(aa(id), e.actual, 'attribute actor'); stable(ab(id), e.attribute, 'attribute binding');
    stable(ca(id), e.actual, 'charge actor'); stable(cb(id), e.charge, 'charge binding'); stable(cs(id), e.status, 'charge status');
    stable(cm(id), e.mapping, 'charge mapping'); stable(cat(id), e.attribute, 'charge attribute');
    stable(cg(), global, 'charge global'); stable(cd(), data, 'charge data');
    stable(ra(id), e.actual, 'action actor'); stable(rw(id), e.world, 'action world'); stable(rb(id), e.action, 'action binding');
    stable(qa(id), e.actual, 'cue actor'); stable(qm(id), e.mapping, 'cue mapping'); stable(qb(id), e.cue, 'cue binding');
    stable(qd(id), e.dispatch, 'dispatch binding'); stable(start(id), e.start, 'stream start'); stable(stream(id), e.stream, 'stream binding');
    for (const d of descriptors()) if (assigned.has(d) || storage.has(d) || d === global || d === data)
      fail('known mapping descriptor aliases command-admission storage');
    noShadows(e, [...storage.keys()]);
  };
  const assertComplete = (actual: object): void => {if (incomplete.has(actual)) fail('actual actor has known incomplete command admission');};
  const write = (e: Entry, owner: object, key: string, value: unknown): void => {
    own(owner, key, true); check(); incomplete.add(e.actual);
    (owner as Record<string, unknown>)[key] = value; incomplete.add(e.actual); check();
  };
  const constant = (key: string, expected: number): number => {
    const value = f(data, key); if (!Object.is(value, expected)) fail(`${key}: authenticated constant required`); return value;
  };
  const aim = (e: Entry): object => {
    const value = record(read(e.actual, 'aimOrigin518'), 'actual aimOrigin518 vector');
    if (e.aim !== undefined) stable(value, e.aim, 'aimOrigin518');
    retain(e, value, 'aim'); e.aim = value; return value;
  };
  const trig = (heading: number, cosine: boolean): number => {
    // 45204/45238 sth -> psq_l W=1,I=5 -> fmuls -> mandatory double sin/cos, then frsp.
    if (gqr5 !== 0x00070007) fail('GQR5: explicit signed16/scale0 profile0x00070007 required');
    const factor = constant('float80437078', 0.0000958738019107841 /* authenticated f32 bits0x38c90fdb */);
    const angle = Math.fround(factor * heading);
    if (angle !== 0) fail(`${cosine ? '80045238' : '80045204'} reached unsupported nonzero source trig`);
    // Authenticated direct kernels: positive-zero sin returns+0; cos returns1.
    return cosine ? 1 : 0;
  };
  const captureTarget = (id: symbol, e: Entry): void => {
    write(e, e.binding, 'pointerc8', pointer(read(e.binding, 'pointer504'), 'pointer504'));
    write(e, e.actual, 'visibilityTarget', pointer(read(e.binding, 'pointer508'), 'pointer508'));
    write(e, e.binding, 'byteD0', byte(e.action, 'byte7d2'));
    if (signedHalf(e.world, 'yawOffset6b8') !== 0) {
      write(e, e.binding, 'pointerc8', null); write(e, e.actual, 'visibilityTarget', null); write(e, e.binding, 'byteD0', 0);
    }
    if (pointer(read(e.actual, 'visibilityTarget'), 'visibilityTarget') !== null)
      fail('8006be04 reached unsupported active-target snapshot before c8/target position loads');
    const distance = constant('float80437678', 20000);
    write(e, e.actual, 'horizontalDistance764', distance); write(e, e.actual, 'targetDistance760', distance);
    const sine = trig(s16(half(e.actual, 'heading')), false);
    const x = Math.fround(f(e.actual, 'horizontalDistance764') * sine);
    write(e, aim(e), 'x', float(x, 'snapshot x'));
    const selected = read(e.mapping, 'descriptor4b0');
    if (typeof selected !== 'symbol') fail('descriptor4b0: explicit owned descriptor identity required');
    const meta = record(descriptor(selected), 'descriptor+10 metadata');
    if (descriptorRows.has(selected)) stable(meta, descriptorRows.get(selected)!, 'descriptor metadata');
    if (descriptorIds.has(meta) && descriptorIds.get(meta) !== selected) fail('descriptor metadata aliases another identity');
    retain(e, meta, 'descriptor-metadata'); descriptorRows.set(selected, meta); descriptorIds.set(meta, selected);
    const joint = s8(byte(meta, 'byte10'));
    const row = record(matrix(id, joint), 'world matrix row');
    const known = matrixRows.get(id) ?? new Map<number, object>();
    if (known.has(joint)) stable(row, known.get(joint)!, 'world matrix row');
    retain(e, row, 'matrix-row'); known.set(joint, row); matrixRows.set(id, known);
    if (!Array.isArray(row) || word(row, 'length') !== 12) fail('world matrix: actual twelve-lane row required');
    write(e, aim(e), 'y', f(row, '7'));
    const cosine = trig(s16(half(e.actual, 'heading')), true);
    const z = Math.fround(f(e.actual, 'horizontalDistance764') * cosine);
    write(e, aim(e), 'z', float(z, 'snapshot z'));
  };
  const command = (e: Entry): {row: object; offset: number} => {
    // Authentic69f94..69fb8 register schedule loads all three bytes before4ec.
    const button = s8(byte(e.actual, 'cmdButton')), subtype = s8(byte(e.actual, 'cmdSubtype'));
    const direction = s8(byte(e.actual, 'cmdChargedRanged'));
    const root = record(read(e.actual, 'commandTable'), 'actual commandTable4ec');
    if (e.commandRoot !== undefined) stable(root, e.commandRoot, 'commandTable4ec');
    retain(e, root, 'command-root'); e.commandRoot = root;
    const pointers = record(read(root, 'sourceTables'), 'sourceTables4ec pointer entries');
    if (!Array.isArray(pointers)) fail('sourceTables4ec: explicit source pointer array required');
    if (roots.has(root)) stable(pointers, roots.get(root)!, 'sourceTables4ec');
    // Host representation bound: one pointer-table owner has one4ec wrapper.
    // Actors may share that wrapper; byte rows may still share across slots.
    if (pointerRoots.has(pointers) && pointerRoots.get(pointers) !== root)
      fail('sourceTables4ec: pointer storage has competing command-root identities');
    retain(e, pointers, 'command-pointers'); roots.set(root, pointers); pointerRoots.set(pointers, root);
    const length = word(pointers, 'length');
    if (button < 0 || button >= length) fail('signed585 pointer slot outside explicit sourceTables4ec');
    const row = record(read(pointers, String(button)), 'selected4ec command byte row');
    if (!Array.isArray(row)) fail('selected4ec: explicit raw byte array required');
    const known = rows.get(pointers) ?? new Map<number, object>();
    if (known.has(button)) stable(row, known.get(button)!, 'selected4ec command byte row');
    retain(e, row, 'command-row'); known.set(button, row); rows.set(pointers, known);
    return {row, offset: subtype * 16 + direction * 4};
  };
  const recordByte = (cmd: {row: object; offset: number}, offset: number): number => {
    const at = cmd.offset + offset, length = word(cmd.row, 'length');
    if (at < 0 || at >= length) fail('command record address outside explicitly owned raw byte storage');
    return byte(cmd.row, String(at));
  };
  const flag = (e: Entry, offset: number): number => {
    const value = record(read(data, 'flags3994'), 'flags3994 table');
    if (!Array.isArray(value)) fail('flags3994: explicit raw byte array required');
    if (flagTable !== undefined) stable(value, flagTable, 'flags3994');
    retain(e, value, 'flags'); flagTable = value;
    if (offset < 0 || offset >= FLAGS.length || offset >= word(value, 'length'))
      fail('flags3994: outside authenticated twelve-byte source window');
    const selected = byte(value, String(offset));
    if (selected !== FLAGS[offset]) fail('flags3994: authenticated selected byte required');
    return selected;
  };
  const visibilityRow = (e: Entry, index: number): object => {
    const table = record(read(e.actual, 'visibilityRoster'), 'six source visibility pointers');
    if (!Array.isArray(table) || word(table, 'length') !== 6) fail('visibilityRoster: six explicit source pointer slots required');
    if (roster !== undefined) stable(table, roster, 'shared visibilityRoster');
    retain(e, table, 'roster'); roster = table;
    const target = record(read(table, String(index)), `visibility pointer${index}`);
    if (rosterRows.has(index)) stable(target, rosterRows.get(index)!, `visibility pointer${index}`);
    retain(e, target, 'visibility-target'); rosterRows.set(index, target); return target;
  };
  const cue = (id: symbol, e: Entry, index: number, isUpper: boolean): void => {
    incomplete.add(e.actual);
    const result = (isUpper ? upper : full)(id, index >>> 0);
    if (result !== 0 && result !== 1) fail('genuine cue returned asynchronously or unexpectedly');
  };
  const executeCommand = (id: symbol, e: Entry, cmd: {row: object; offset: number}): 0 | 1 => {
    if (s8(recordByte(cmd, 0)) === -1) return 0;
    write(e, e.actual, 'prevActionIndex', byte(e.actual, 'cmdButton'));
    captureTarget(id, e);
    const previous = word(e.actual, 'controlWord');
    if ((previous & 3) === 3 && recordByte(cmd, 1) === 1) {
      cue(id, e, (previous & 0x40) !== 0 ? 6 : 0, true);
      if ((previous & 0x40) === 0) fail('8006a1a0 reached unsupported active8004beb8 after genuine upper cue0');
    }
    const actionIndex = recordByte(cmd, 2), zero = constant('float8043762c', 0);
    write(e, e.actual, 'actionIndex', actionIndex);
    write(e, e.actual, 'variantIndex', recordByte(cmd, 3));
    write(e, e.actual, 'controlWord', (word(e.actual, 'controlWord') & 0xfffffffc) >>> 0);
    const control = word(e.actual, 'controlWord'), mode = recordByte(cmd, 1);
    write(e, e.actual, 'controlWord', (control | mode) >>> 0);
    write(e, e.actual, 'stateTimer', zero);
    if (recordByte(cmd, 1) === 3) write(e, e.start, 'marker709', 0);
    write(e, e.actual, 'stateFlagA', flag(e, s8(byte(e.actual, 'prevActionIndex')) * 2));
    write(e, e.actual, 'stateFlagB', flag(e, s8(byte(e.actual, 'prevActionIndex')) * 2 + 1));
    write(e, e.stream, 'blockedMask1d9a', 0);
    const rechargeIndex = s8(byte(e.actual, 'prevActionIndex'));
    if (rechargeIndex >= 3) {
      const retainedZero = constant('float8043762c', 0);
      const warmup = WARMUPS[rechargeIndex - 3];
      if (warmup === undefined) fail('source630+4*signed584 is outside canonical charge warmups');
      write(e, e.charge, warmup, retainedZero);
      const bank = BANKS[s8(byte(e.actual, 'prevActionIndex')) - 3];
      if (bank === undefined) fail('source63c+4*signed584 is outside canonical charge banks');
      write(e, e.charge, bank, retainedZero);
    }
    // First actor-bit load precedes slot0; later pointers precede their bit load.
    let bit = byte(e.actual, 'visibilityBit');
    for (let index = 0; index < 6; index++) {
      const target = visibilityRow(e, index);
      if (index !== 0) bit = byte(e.actual, 'visibilityBit');
      write(e, target, 'visibilityMask5e6', byte(target, 'visibilityMask5e6') & (~bit & 255));
    }
    const selected = pointer(read(e.actual, 'visibilityTarget'), 'visibilityTarget');
    if (selected !== null) {
      retain(e, selected, 'visibility-target');
      if (s8(byte(selected, 'eligibility83')) === 0) {
        const mask = byte(selected, 'visibilityMask5e6'), actorBit = byte(e.actual, 'visibilityBit');
        write(e, selected, 'visibilityMask5e6', mask | actorBit);
      }
    }
    cue(id, e, s8(recordByte(cmd, 0)), false);
    if (recordByte(cmd, 1) === 3) cue(id, e, s8(recordByte(cmd, 0)), true);
    const ammoIndex = s8(byte(e.actual, 'prevActionIndex'));
    if (ammoIndex === 0 || ammoIndex === 2) {
      const slot = record(ammo(id, ammoIndex), 'canonical status ammo slot');
      const known = ammoRows.get(id) ?? new Map<number, object>();
      if (known.has(ammoIndex)) stable(slot, known.get(ammoIndex)!, 'status ammo slot');
      retain(e, slot, 'ammo-slot'); known.set(ammoIndex, slot); ammoRows.set(id, known);
      const cell = record(read(slot, 'cell'), 'canonical status WeaponCell');
      if (ammoCells.has(slot)) stable(cell, ammoCells.get(slot)!, 'status WeaponCell');
      retain(e, cell, 'ammo-cell'); ammoCells.set(slot, cell);
      if (signedHalf(cell, 'max') !== 0 && signedHalf(cell, 'refillType') !== 3)
        fail('8006a37c reached unsupported source8006dbe0 ammo check before11cc4 sound');
    }
    // Actual ea2c8 supplies event2 and -1, then ea2ec first loads shared45.
    stable(cg(), global, 'shared voice global');
    if (s8(byte(global, 'byte45')) < 5) fail('800ea324 reached unsupported source800055fc RNG before active-match audio');
    return 1;
  };
  const runtime: SourceActorCommandAdmissionRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(wa(id), 'actual actor') as RomActor;
      if (claimed.has(actual)) fail('actual actor already claimed by source command admission');
      const binding: Partial<SourceActorCommandAdmissionBinding> = {};
      const e: Entry = {id, actual, world: record(wb(id), 'world') as SourceActorWorldMatrixBinding,
        status: record(sb(id), 'status'), mapping: record(wm(id), 'mapping'), attribute: record(ab(id), 'attribute'),
        charge: record(cb(id), 'charge binding'), action: record(rb(id), 'action binding'), cue: record(qb(id), 'cue binding'),
        dispatch: record(qd(id), 'dispatch') as SourceActorAnimationDispatchBinding,
        start: record(start(id), 'stream start'), stream: record(stream(id), 'stream binding'), binding, extras: []};
      admit(id, e);
      const records = owners(e);
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value) || storage.has(value) || value === global || value === data))
        fail('source owner alias: distinct canonical and new binding owners required');
      record(initial, 'initial admission binding'); noShadows({...e, binding: initial});
      for (const key of ['pointer504', 'pointer508', 'pointerc8'] as const)
        if (property(initial, key) !== undefined) Object.assign(binding, {[key]: pointer(read(initial, key), key)});
      if (property(initial, 'byteD0') !== undefined) binding.byteD0 = byte(initial, 'byteD0');
      Object.seal(binding); e.extras = Object.freeze([binding]);
      check(); actors.set(id, e); records.forEach(value => assigned.add(value)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;}, getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;}, getMappingActor(id) {return entry(id).mapping;},
    getAttributeBinding(id) {return entry(id).attribute;}, getChargeRuntime() {return charge;},
    getChargeBinding(id) {return entry(id).charge;}, getActionRuntime() {return action;}, getActionBinding(id) {return entry(id).action;},
    getCueRuntime() {return cues;}, getCueBinding(id) {return entry(id).cue;}, getDispatchBinding(id) {return entry(id).dispatch;},
    getStartBinding(id) {return entry(id).start;}, getStreamBinding(id) {return entry(id).stream;},
    getGlobal() {return global;}, getData() {return data;}, getActorBinding(id) {return entry(id).binding;},
    getSourceOwners(id) {return entry(id).extras;}, getKnownStorageOwners() {return Object.freeze([...storage.keys()]);},
    getKnownStorageEntries() {return Object.freeze([...storage].map(([owner, kind]) => Object.freeze({owner, kind})));},
    assertActorComplete(id) {assertComplete(entry(id).actual);},
    dispatchSubtypeDirection(id) {return guard(() => {
      const e = entry(id); assertComplete(e.actual); admit(id, e);
      if (pointer(read(e.binding, 'pointer508'), 'pointer508') !== null)
        fail('8006c6a8 reached unsupported source80066408 target direction before587 store');
      write(e, e.actual, 'cmdChargedRanged', 0);
      const result = executeCommand(id, e, command(e));
      check(); incomplete.delete(e.actual); return result;
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
