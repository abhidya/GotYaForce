/** Bounded actual800699d8, its six ordered testers and descriptor gate80069dd0.
 * Evidence: chunk_0009.c:220–487 and read_archived_actor_input_testers_evidence.py.
 * All six unconditional595 clears are actual separate stores. Native mode2
 * success and the actual descriptor sentinel/type-other returns are preserved.
 * Optional genuine command admission continues69ea4 after its actual selector.
 * Linked4a4 dereference,5c080 and69fe0 remain explicit boundaries, never
 * callbacks or manufactured return values. No tick activation or input hydration.
 *
 * Existing actual/world/status/mapping/attribute/charge/action-request owners
 * remain live and unique. Only missing595/748/7cc receive copied partial storage.
 * Raw unsigned bytes are sign-extended at source extsb sites; slw uses low SIX
 * bits, with shifts32..63 producing zero. Descriptor+b8 addresses raw8c+2c,
 * bounded by the explicitly supplied array, not an invented six-action limit.
 * Stable synchronous non-proxy own-data records are admission bounds. Captured
 * receivers, lazy scalar/destination checks, permanent actual claims, and a
 * host-only incomplete marker preserve prefixes and prevent effectful retries.
 */
import type {RomActor} from './actor.js';
import {isSourceActorCommandAdmissionRuntime, hasIncompleteSourceActorCommandAdmission,
  type SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';
import type {SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime,
  type SourceActorInputChargeBinding} from './actor-input-charge.js';
import {isSourceActorActionRequestRuntime, type SourceActorActionRequestRuntime,
  type SourceActorActionRequestBinding} from './actor-action-request.js';

export interface SourceActorInputTestersBinding {byte595: number; byte748: number; byte7cc: number}
export interface SourceActorInputTestersSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding' | 'getMappingActor'>;
  status: Pick<SourceActorStatusTimersRuntime, 'getActualActor' | 'getActorBinding' | 'getWorldBinding' | 'getMappingActor' | 'getAttributeBinding'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor'>;
  charge: SourceActorInputChargeRuntime;
  actionRequest?: SourceActorActionRequestRuntime;
  /** Optional genuine6c674/6a104 child; absence preserves historical69ea4 refusal. */
  commandAdmission?: SourceActorCommandAdmissionRuntime;
}
export interface SourceActorInputTestersRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorInputTestersBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getStatusBinding(identity: symbol): object;
  getMappingActor(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getChargeRuntime(): SourceActorInputChargeRuntime;
  getChargeBinding(identity: symbol): Partial<SourceActorInputChargeBinding>;
  getActionRuntime(): SourceActorActionRequestRuntime | undefined;
  getActionBinding(identity: symbol): Partial<SourceActorActionRequestBinding> | undefined;
  getCommandAdmissionRuntime(): SourceActorCommandAdmissionRuntime | undefined;
  getActorBinding(identity: symbol): Partial<SourceActorInputTestersBinding>;
  /** Additional owners only; canonical actual/world/status/mapping/attribute are omitted. */
  getSourceOwners(identity: symbol): readonly object[];
  getKnownDescriptorRecords(): readonly object[];
  assertActorComplete(identity: symbol): void;
  updateActor(identity: symbol): 0 | 1;
  testDescriptor(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>(), incomplete = new WeakSet<object>();
export function isSourceActorInputTestersRuntime(value: unknown): value is SourceActorInputTestersRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function hasIncompleteSourceActorInputTesters(actual: object): boolean {return incomplete.has(actual);}
function fail(reason: string): never {
  throw Error(`[actor-input-testers] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max)
    fail(`${where}: unsigned integer out of bounds`);
  return value === 0 ? 0 : value;
}
const s8 = (value: number): number => value << 24 >> 24;
const slw1 = (count: number): number => (count & 63) >= 32 ? 0 : (1 << (count & 63)) >>> 0;
export function createSourceActorInputTestersRuntime(sources: SourceActorInputTestersSources): SourceActorInputTestersRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const value = run(); check(); return value;} finally {busy = false;}
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
  const capture = (name: keyof SourceActorInputTestersSources, key: string) => {
    const receiver = read(sources, name), method = read(receiver, key);
    if (typeof method !== 'function') fail(`${name}.${key}: own data-function required`);
    return (...args: unknown[]): unknown => {const value = Reflect.apply(method, receiver, args); check(); return value;};
  };
  const charge = read(sources, 'charge');
  if (!isSourceActorInputChargeRuntime(charge)) fail('charge requires genuine source runtime');
  const actionProperty = property(sources, 'actionRequest');
  const action = actionProperty === undefined ? undefined : read(sources, 'actionRequest');
  if (actionProperty !== undefined && !isSourceActorActionRequestRuntime(action)) fail('actionRequest requires genuine source runtime');
  const actionRuntime = action as SourceActorActionRequestRuntime | undefined;
  const commandProperty = property(sources, 'commandAdmission');
  const command = commandProperty === undefined ? undefined : read(sources, 'commandAdmission');
  if (commandProperty !== undefined && !isSourceActorCommandAdmissionRuntime(command))
    fail('commandAdmission requires genuine source runtime');
  const commandRuntime = command as SourceActorCommandAdmissionRuntime | undefined;
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const worldMapping = capture('world', 'getMappingActor');
  const statusActor = capture('status', 'getActualActor'), statusBinding = capture('status', 'getActorBinding');
  const statusWorld = capture('status', 'getWorldBinding'), statusMapping = capture('status', 'getMappingActor');
  const statusAttribute = capture('status', 'getAttributeBinding');
  const mappingActor = capture('mapping', 'getActor');
  const chargeActor = capture('charge', 'getActualActor'), chargeBinding = capture('charge', 'getActorBinding');
  const chargeStatus = capture('charge', 'getStatusBinding'), chargeMapping = capture('charge', 'getMappingActor');
  const chargeAttribute = capture('charge', 'getAttributeBinding');
  // This genuine charge resolver shares its retained descriptor registry. It
  // is invoked only at an actual descriptor load, never during admission.
  const chargeDescriptor = capture('charge', 'getMappingDescriptor');
  const chargeKnownDescriptors = capture('charge', 'getKnownDescriptorRecords');
  const knownDescriptors = (): readonly object[] => {
    const values = chargeKnownDescriptors();
    if (!Array.isArray(values)) fail('charge known descriptors: synchronous owner array required');
    for (const value of values) record(value, 'charge known descriptor');
    return Object.freeze([...values]) as readonly object[];
  };
  const actionActor = actionRuntime === undefined ? undefined : capture('actionRequest', 'getActualActor');
  const actionWorld = actionRuntime === undefined ? undefined : capture('actionRequest', 'getWorldBinding');
  const actionBinding = actionRuntime === undefined ? undefined : capture('actionRequest', 'getActorBinding');
  const commandActor = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getActualActor');
  const commandWorld = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getWorldBinding');
  const commandStatus = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getStatusBinding');
  const commandMapping = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getMappingActor');
  const commandAttribute = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getAttributeBinding');
  const commandCharge = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getChargeRuntime');
  const commandChargeBinding = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getChargeBinding');
  const commandAction = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getActionRuntime');
  const commandActionBinding = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getActionBinding');
  const commandBinding = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getActorBinding');
  const commandSourceOwners = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getSourceOwners');
  const commandStart = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getStartBinding');
  const commandStream = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getStreamBinding');
  const commandCue = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getCueBinding');
  const commandDispatch = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getDispatchBinding');
  const commandData = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getData');
  const commandGlobal = commandRuntime === undefined ? undefined : capture('commandAdmission', 'getGlobal');
  const chargeData = commandRuntime === undefined ? undefined : capture('charge', 'getData');
  const chargeGlobal = commandRuntime === undefined ? undefined : capture('charge', 'getGlobal');
  const runCommand = commandRuntime === undefined ? undefined : capture('commandAdmission', 'dispatchSubtypeDirection');
  const data = commandData === undefined ? undefined : record(commandData(), 'command data');
  const global = commandGlobal === undefined ? undefined : record(commandGlobal(), 'command global');
  const byte = (owner: unknown, key: string): number => integer(read(owner, key), 255, key);
  const word = (owner: unknown, key: string): number => integer(read(owner, key), 0xffffffff, key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {
    actual: RomActor; world: SourceActorWorldMatrixBinding; status: object; mapping: object; attribute: object;
    charge: Partial<SourceActorInputChargeBinding>; action: Partial<SourceActorActionRequestBinding> | undefined;
    binding: Partial<SourceActorInputTestersBinding>; extras: readonly object[];
    command?: {binding: object; start: object; stream: object; cue: object; dispatch: object};
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned input-testers actor'); return e;};
  const owners = (e: Entry): object[] => [e.actual, e.world, e.status, e.mapping, e.attribute, e.charge, e.binding,
    ...(e.action === undefined ? [] : [e.action]), ...(e.command === undefined ? [] :
      [e.command.binding, e.command.start, e.command.stream, e.command.cue, e.command.dispatch])];
  const noShadows = (e: Entry, extra?: object): void => {
    const canonical = new Map<string, object>([
      ['cmdButton', e.actual], ['prevActionIndex', e.actual], ['controlWord', e.actual],
      ['cmdSubtype', e.actual], ['cmdChargedRanged', e.actual], ['stateTimer', e.actual], ['ubCue', e.actual],
      ['inputEdge5d4', e.actual], ['stateFlagA', e.actual], ['mode4a0', e.world],
      ['byte593', e.status], ['descriptor4b0', e.mapping], ['byte58e', e.charge],
      ['byte595', e.binding], ['byte748', e.binding], ['byte7cc', e.binding],
    ]);
    if (e.action !== undefined) canonical.set('byte7d2', e.action);
    const aliases = ['byte585', 'field585', 'command585', 'byte584', 'field584', 'word5e0', 'flags5e0',
      'field5e0', 'word5d4', 'flags5d4', 'inputFlags5d4', 'byte57a', 'flags57a',
      'byte4a0', 'actorMode4a0', 'field4a0', 'field593', 'timer593', 'pointer4b0', 'field4b0',
      'flags58e', 'field58e', 'flags7d2', 'field7d2', 'field595', 'flags595', 'field748', 'proximity748',
      'field7cc', 'flags7cc', 'byte586', 'field586', 'byte587', 'field587', 'field694', 'timer694'];
    for (const owner of [...owners(e), ...(extra === undefined ? [] : [extra])]) {
      for (const [key, expected] of canonical) if (owner !== expected && property(owner, key) !== undefined)
        fail(`${key}: competing input-testers storage on another owner`);
      if (e.action === undefined && property(owner, 'byte7d2') !== undefined)
        fail('byte7d2: competing input-testers storage without genuine action-request owner');
      for (const key of aliases) if (property(owner, key) !== undefined) fail(`${key}: competing input-testers storage alias`);
    }
  };
  const admit = (id: symbol, e: Entry): void => {
    stable(worldActor(id), e.actual, 'world actor'); stable(worldBinding(id), e.world, 'world binding');
    stable(worldMapping(id), e.mapping, 'world mapping');
    stable(statusActor(id), e.actual, 'status actor'); stable(statusBinding(id), e.status, 'status binding');
    stable(statusWorld(id), e.world, 'status world'); stable(statusMapping(id), e.mapping, 'status mapping');
    stable(statusAttribute(id), e.attribute, 'status attribute'); stable(mappingActor(id), e.mapping, 'mapping actor');
    stable(chargeActor(id), e.actual, 'charge actor'); stable(chargeBinding(id), e.charge, 'charge binding');
    stable(chargeStatus(id), e.status, 'charge status'); stable(chargeMapping(id), e.mapping, 'charge mapping');
    stable(chargeAttribute(id), e.attribute, 'charge attribute');
    if (actionActor) {
      stable(actionActor(id), e.actual, 'action actor'); stable(actionWorld!(id), e.world, 'action world');
      stable(actionBinding!(id), e.action!, 'action binding');
    }
    if (e.command) {
      stable(commandActor!(id), e.actual, 'command actual'); stable(commandWorld!(id), e.world, 'command world');
      stable(commandStatus!(id), e.status, 'command status'); stable(commandMapping!(id), e.mapping, 'command mapping');
      stable(commandAttribute!(id), e.attribute, 'command attribute'); stable(commandChargeBinding!(id), e.charge, 'command charge binding');
      if (commandCharge!() !== charge || actionRuntime === undefined || commandAction!() !== actionRuntime ||
          commandActionBinding!(id) !== e.action) fail('command/testers require the same genuine charge/action owners');
      stable(commandBinding!(id), e.command.binding, 'command binding'); stable(commandStart!(id), e.command.start, 'command stream start');
      stable(commandStream!(id), e.command.stream, 'command stream'); stable(commandCue!(id), e.command.cue, 'command cue');
      stable(commandDispatch!(id), e.command.dispatch, 'command dispatch');
      if (commandData!() !== data || chargeData!() !== data || commandGlobal!() !== global || chargeGlobal!() !== global)
        fail('command/testers require the same retained charge global/data');
      const additional = commandSourceOwners!(id);
      if (!Array.isArray(additional) || additional.length !== 1 || additional[0] !== e.command.binding)
        fail('command source owners must retain only the new binding');
      if (global === data || owners(e).includes(global!) || owners(e).includes(data!))
        fail('command global/data aliases an actor source owner');
    }
    noShadows(e);
  };
  const assertComplete = (actual: object): void => {
    if (hasIncompleteSourceActorCommandAdmission(actual)) fail('actual actor has known incomplete command admission');
    if (incomplete.has(actual)) fail('actual actor has known incomplete input testers');
  };
  const write = (e: Entry, owner: object, key: string, value: number): void => {
    own(owner, key, true); check(); (owner as Record<string, unknown>)[key] = value;
    incomplete.add(e.actual); check();
  };
  const descriptorByte = (id: symbol, e: Entry, rawIndex: number): number => {
    // Caller has already loaded585. Source next loads4b0; no descriptor
    // dereference, range validation or type read is hoisted before that load.
    const raw = record(chargeDescriptor(id), 'descriptor4b0 raw8c');
    if (!Array.isArray(raw)) fail('descriptor4b0: explicit raw8c byte array required');
    if (assigned.has(raw)) fail('descriptor4b0 aliases another input-testers source owner');
    noShadows(e, raw);
    const at = 0x2c + s8(rawIndex), length = integer(read(raw, 'length'), 0xffffffff, 'raw8c length');
    if (at < 0 || at >= length) fail('descriptor+b8: addressing outside explicitly owned raw8c storage');
    return s8(byte(raw, String(at)));
  };
  const selectType1 = (id: symbol, e: Entry): 0 | 1 => {
    if (!runCommand) fail('80069e78 reached unsupported source call80069ea4');
    //69ec4 loads the timer BEFORE69ec8's constant.595 nonzero skips both.
    if (s8(byte(e.binding, 'byte595')) === 0) {
      const timer = read(e.actual, 'stateTimer');
      if (typeof timer !== 'number' || !Number.isFinite(timer) || !Object.is(timer, Math.fround(timer)))
        fail('stateTimer: finite exact source float32 required');
      if (!Object.is(read(data, 'float8043762c'), 0)) fail('float8043762c: authenticated positive zero required');
      if (timer > 0) return 0;
    }
    const flags = word(e.actual, 'controlWord'); //69edc retained across every branch.
    let subtype: number;
    if ((flags & 0x100) !== 0) subtype = 5;
    else if ((flags & 0x80) !== 0) subtype = 4;
    else if ((flags & 0x20) !== 0) subtype = s8(byte(e.binding, 'byte7cc')) !== 0 ? 2 : (flags & 0x40) !== 0 ? 3 : 0;
    else if ((flags & 0x40) !== 0 || byte(e.actual, 'ubCue') === 4) subtype = 3;
    else subtype = (flags & 0x10) !== 0 ? 1 : 0;
    write(e, e.actual, 'cmdSubtype', subtype);
    incomplete.add(e.actual); // The child can retain a genuine effectful prefix.
    const result = runCommand(id);
    if (result !== 0 && result !== 1) fail('genuine command admission returned asynchronously or unexpectedly');
    return result;
  };
  const testDescriptor = (id: symbol, e: Entry): 0 | 1 => {
    const rawIndex = byte(e.actual, 'cmdButton'); //69de4, before4b0.
    if (descriptorByte(id, e, rawIndex) === -1) return 0;
    if ((word(e.actual, 'controlWord') & 3) !== 0) {
      const flags = byte(e.actual, 'stateFlagA');
      if ((s8(flags) & slw1(s8(rawIndex))) === 0) return 0;
      fail('80069e38 reached unsupported source call8005c080 before byte595=1 store');
    }
    const type = descriptorByte(id, e, byte(e.actual, 'cmdButton'));
    if (type === 1) return selectType1(id, e);
    if (type === 0) fail('80069e84 reached unsupported source call80069fe0');
    return 0;
  };
  const clear = (e: Entry): void => write(e, e.binding, 'byte595', 0);
  const test69cb0 = (e: Entry): 0 | 1 => {
    clear(e);
    if (s8(byte(e.world, 'mode4a0')) === 0) return 0;
    if ((word(e.actual, 'controlWord') & 2) !== 0 && s8(byte(e.actual, 'prevActionIndex')) === 5) return 0;
    if (s8(byte(e.status, 'byte593')) < 1) {
      if ((byte(e.charge, 'byte58e') & 0x20) !== 0) return 0;
      if ((word(e.actual, 'inputEdge5d4') & 0x1000) === 0) return 0;
      write(e, e.status, 'byte593', 6);
    }
    if (s8(byte(e.world, 'mode4a0')) === 2) return 1;
    // There is no synthetic null/zero linked actor. The authentic source's
    // next access is4a4, before either linked3e6 or linked593 is read.
    fail('80069d50 reached unsupported source pointer4a4 load before linked3e6/593');
  };
  const testMasked = (id: symbol, e: Entry, disabled: number, edge: number, command: number, charged: boolean): 0 | 1 => {
    clear(e);
    if ((byte(e.charge, 'byte58e') & disabled) !== 0) return 0;
    if ((word(e.actual, 'inputEdge5d4') & edge) === 0) return 0;
    write(e, e.actual, 'cmdButton', command);
    if (charged) write(e, e.binding, 'byte595', 1);
    return testDescriptor(id, e);
  };
  const test69b10 = (id: symbol, e: Entry): 0 | 1 => {
    clear(e);
    if ((word(e.actual, 'inputEdge5d4') & 0x40) === 0) return 0;
    if (byte(e.binding, 'byte748') === 1) return 0;
    const disabled = byte(e.charge, 'byte58e'); // One retained load for both masks.
    if ((disabled & 2) !== 0) return 0;
    if ((disabled & 1) === 0) {
      if (e.action === undefined) fail('reached byte7d2 requires genuine actionRequest runtime');
      if ((byte(e.action, 'byte7d2') & 8) === 0) return 0;
    }
    write(e, e.actual, 'cmdButton', 1);
    return testDescriptor(id, e);
  };
  const test69a88 = (id: symbol, e: Entry): 0 | 1 => {
    clear(e);
    if ((word(e.actual, 'inputEdge5d4') & 0x20) === 0) return 0;
    const near = byte(e.binding, 'byte748') === 2;
    const selected = near || (byte(e.charge, 'byte58e') & 1) !== 0 ? 1 : 0;
    write(e, e.actual, 'cmdButton', selected);
    const rawIndex = byte(e.actual, 'cmdButton'), disabled = byte(e.charge, 'byte58e');
    if ((disabled & slw1(s8(rawIndex))) !== 0) return 0;
    return testDescriptor(id, e);
  };
  const execute = (id: symbol, run: (e: Entry) => 0 | 1): 0 | 1 => guard(() => {
    const e = entry(id); assertComplete(e.actual); admit(id, e);
    const result = run(e); check(); incomplete.delete(e.actual); return result;
  });
  const runtime: SourceActorInputTestersRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source input-testers runtime');
      const binding: Partial<SourceActorInputTestersBinding> = {};
      const e: Entry = {actual, world: record(worldBinding(id), 'world binding') as Entry['world'],
        status: record(statusBinding(id), 'status binding'), mapping: record(mappingActor(id), 'mapping actor'),
        attribute: record(statusAttribute(id), 'attribute binding'), charge: record(chargeBinding(id), 'charge binding'),
        action: actionBinding === undefined ? undefined : record(actionBinding(id), 'action binding'), binding, extras: []};
      if (commandRuntime) e.command = {binding: record(commandBinding!(id), 'command binding'),
        start: record(commandStart!(id), 'command stream start'), stream: record(commandStream!(id), 'command stream'),
        cue: record(commandCue!(id), 'command cue'), dispatch: record(commandDispatch!(id), 'command dispatch')};
      admit(id, e);
      const records = owners(e), known = knownDescriptors();
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value) || known.includes(value)))
        fail('source owner alias: distinct actual/world/status/mapping/attribute/charge/action/tester owners required');
      record(initial, 'initial input-testers binding'); noShadows({...e, binding: initial});
      for (const key of ['byte595', 'byte748', 'byte7cc'] as const) if (property(initial, key) !== undefined) binding[key] = byte(initial, key);
      Object.seal(binding); e.extras = Object.freeze([binding, e.charge, ...(e.action === undefined ? [] : [e.action]),
        ...(e.command === undefined ? [] : [e.command.binding])]);
      check(); actors.set(id, e); records.forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getStatusBinding(id) {return entry(id).status;},
    getMappingActor(id) {return entry(id).mapping;},
    getAttributeBinding(id) {return entry(id).attribute;},
    getChargeRuntime() {return charge;},
    getChargeBinding(id) {return entry(id).charge;},
    getActionRuntime() {return actionRuntime;},
    getActionBinding(id) {return entry(id).action;},
    getCommandAdmissionRuntime() {return commandRuntime;},
    getActorBinding(id) {return entry(id).binding;},
    getSourceOwners(id) {return entry(id).extras;},
    getKnownDescriptorRecords() {return knownDescriptors();},
    assertActorComplete(id) {assertComplete(entry(id).actual);},
    updateActor(id) {return execute(id, e => {
      if (test69cb0(e) !== 0) return 1;
      if (testMasked(id, e, 0x20, 0x1000, 5, true) !== 0) return 1;
      if (testMasked(id, e, 8, 0x400, 3, true) !== 0) return 1;
      if (testMasked(id, e, 4, 0x80, 2, false) !== 0) return 1;
      if (test69b10(id, e) !== 0) return 1;
      return test69a88(id, e) === 0 ? 0 : 1;
    });},
    testDescriptor(id) {return execute(id, e => testDescriptor(id, e));},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
