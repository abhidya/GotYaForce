/** Bounded charge callees:800061cc->800061f0(actor,cue,0), and
 *800f0104(actor,1,4). Explicit offline owners, not retail hydration.
 * Color13/14 stores only initialize7df/7e4/7ec/7f4..7f7; the numeric script
 * pointer preserves its explicit source table word, not hydrated script bytes.
 * Sound uses the actual carriedSlot96 byte, sign-extended, to select the
 * shared DAT_803d3ae8 record at s8(96)*0x80+4*0x10. Supplied active records
 * are never fabricated. Equal FIRST s16 values, even at different pointers,
 * genuinely skip initialization and refresh owner5c/countdown54 only.
 * Unequal heads stop at800f0180->800f02d0. Null script58 stores the desired
 * pointer then stops at800f01a4->80207058. No clock/audio substitute runs.
 * That partially activated row is thereafter inadmissible across runtimes:
 * its stored pointer cannot prove the refused activation completed. This is
 * an ownership boundary, not an extra source instruction; recovery is unmodeled.
 *
 * Borrowed tables/records/descriptors keep stable identities. Only the missing
 * actor color cells are copied/sealed. Own-data, non-proxy synchronous records
 * and finite exact binary32 are admission bounds. Validation follows reached
 * source reads/stores; refusals retain prior stores. Caught mutation reentry
 * poisons the outer operation. This is not a sound scheduler or color renderer.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';

export interface SourceActorChargeEffectsBinding {
  byte7df: number; field7e4: number; pointer7ec: number;
  byte7f4: number; byte7f5: number; byte7f6: number; byte7f7: number;
}
export interface SourceActorChargeEffectsData {
  float80436a20?: number;
  /** Source PTR_DAT_802c3770[0x13] and [0x14], stored but not dereferenced. */
  colorPointer802c37bc?: number; colorPointer802c37c0?: number;
}
export interface SourceActorChargeSoundRecord {
  /** Explicit source pointer bits. Zero is the null-pointer path. */
  script58?: number;
  owner5c?: RomActor | null;
  countdown54?: number;
}
/** Explicit live offline descriptor, not inferred retail memory. The archived
 * cue1 head at8031b454 is126; any supplied live overlay is the caller's input. */
export interface SourceActorChargeSoundScript {firstS16?: number}
export interface SourceActorChargeSoundSources {
  cue1Pointer8031b698?: number;
  /** Keys are signed BYTE OFFSETS from DAT_803d3ae8, not actor IDs or slots. */
  records3ae8?: Readonly<Record<number, SourceActorChargeSoundRecord>>;
  /** Explicit pointer-address owners of just the reached first signed halfword. */
  scripts?: Readonly<Record<number, SourceActorChargeSoundScript>>;
}
export interface SourceActorChargeEffectsSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'>;
  data: SourceActorChargeEffectsData;
  sound: SourceActorChargeSoundSources;
}
export interface SourceActorChargeEffectsRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorChargeEffectsBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceActorChargeEffectsBinding>;
  getData(): SourceActorChargeEffectsData;
  getSound(): SourceActorChargeSoundSources;
  keepChargeSound(identity: symbol): void;
  initializeReadyColor(identity: symbol, cue: 0x13 | 0x14): void;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
const incompleteActivations = new WeakSet<object>();
export function isSourceActorChargeEffectsRuntime(value: unknown): value is SourceActorChargeEffectsRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
const BYTES = ['byte7df','byte7f4','byte7f5','byte7f6','byte7f7'] as const;
const COLOR = [...BYTES, 'field7e4', 'pointer7ec'] as const;
function fail(reason: string): never {
  throw Error(`[actor-charge-effects] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
export function createSourceActorChargeEffectsRuntime(sources: SourceActorChargeEffectsSources): SourceActorChargeEffectsRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (r: unknown, key: string): unknown => {const value = own(r, key); check(); return value;};
  const write = (r: unknown, key: string, value: unknown): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise)
      fail(`${where}: synchronous actual owned record required`);
    check(); return value;
  };
  const roles = new WeakMap<object, string>(), owners = new Map<string, object>();
  const retain = (value: unknown, role: string): object => {
    const actual = record(value, role), prior = owners.get(role), other = roles.get(actual);
    if (prior !== undefined && prior !== actual) fail(`${role}: owner changed its actual record`);
    if (other !== undefined && other !== role) fail(`${role}: source owner aliases ${other}`);
    owners.set(role, actual); roles.set(actual, role); return actual;
  };
  const world = retain(read(sources, 'world'), 'world owner');
  const getActualActor = read(world, 'getActualActor');
  if (typeof getActualActor !== 'function') fail('world.getActualActor: own data-function required');
  const data = retain(read(sources, 'data'), 'color data') as SourceActorChargeEffectsData;
  const sound = retain(read(sources, 'sound'), 'sound source') as SourceActorChargeSoundSources;
  const actualActor = (id: symbol): RomActor => {
    if (read(sources, 'world') !== world) fail('world owner changed its actual record');
    const value = Reflect.apply(getActualActor, world, [id]); check();
    return record(value, 'world actor') as RomActor;
  };
  const exclusive = (actual: object): void => {
    for (const key of [...COLOR, 'byte96', 'signedByte96']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing source owner present`);
      check();
    }
  };
  interface Entry {actual: RomActor; binding: Partial<SourceActorChargeEffectsBinding>}
  const actors = new Map<symbol, Entry>();
  const entry = (id: symbol): Entry => {
    const found = actors.get(id); if (!found) fail('unknown/non-owned charge effect actor'); return found;
  };
  const actorForCall = (id: symbol): Entry => {
    const actor = entry(id);
    if (actualActor(id) !== actor.actual) fail('world actor owner changed its actual record');
    exclusive(actor.actual); return actor;
  };
  const b = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const u = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const sourceSound = (): void => {
    if (read(sources, 'sound') !== sound) fail('sound source owner changed its actual record');
  };
  const soundTable = (key: 'records3ae8' | 'scripts'): object => {
    sourceSound(); return retain(read(sound, key), `sound ${key}`);
  };
  const soundRecord = (offset: number): object =>
    retain(read(soundTable('records3ae8'), String(offset)), `scheduler offset ${offset}`);
  const soundHead = (address: number): number => {
    const script = retain(read(soundTable('scripts'), String(address)), `sound script ${address}`);
    return integer(read(script, 'firstS16'), -0x8000, 0x7fff, 'firstS16');
  };
  const desiredPointer = (): number => {
    sourceSound(); const value = u(sound, 'cue1Pointer8031b698');
    if (value !== 0x8031b454) fail('cue1Pointer8031b698: authenticated source pointer bits required');
    return value;
  };
  const runtime: SourceActorChargeEffectsRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = actualActor(id); exclusive(actual);
      if (claimed.has(actual)) fail('actual actor already claimed by a source charge effects runtime');
      if (roles.has(actual)) fail('actual actor source owner alias');
      record(initial, 'initial color binding');
      if (roles.has(initial) || initial === actual) fail('initial color binding source owner alias');
      const binding: Partial<SourceActorChargeEffectsBinding> = {};
      for (const key of BYTES) {
        const property = Object.getOwnPropertyDescriptor(initial, key); check();
        if (property !== undefined) binding[key] = b(initial, key);
      }
      const field7e4 = Object.getOwnPropertyDescriptor(initial, 'field7e4'); check();
      if (field7e4 !== undefined) binding.field7e4 = float(read(initial, 'field7e4'), 'field7e4');
      const pointer7ec = Object.getOwnPropertyDescriptor(initial, 'pointer7ec'); check();
      if (pointer7ec !== undefined) binding.pointer7ec = u(initial, 'pointer7ec');
      actors.set(id, {actual, binding: Object.seal(binding)});
      roles.set(actual, 'actual actor'); roles.set(binding, 'color binding'); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActorBinding(id) {return entry(id).binding;},
    getData() {return data;},
    getSound() {return sound;},
    initializeReadyColor(id, cue) {guard(() => {
      const {binding} = actorForCall(id);
      if (cue !== 0x13 && cue !== 0x14) fail('only explicit ready-color cues13/14 are bounded');
      // 61cc wrapper passes r5=0 at61dc. 61fc precedes both data loads.
      write(binding, 'byte7df', 0);
      if (read(sources, 'data') !== data) fail('color data owner changed its actual record');
      const zero = float(read(data, 'float80436a20'), 'float80436a20'); // 620c
      if (!Object.is(zero, 0)) fail('float80436a20: authenticated positive-zero source bits required');
      const key = cue === 0x13 ? 'colorPointer802c37bc' : 'colorPointer802c37c0';
      const pointer = u(data, key); // 6210: reached source table word only.
      if (pointer !== (cue === 0x13 ? 0x802c36b0 : 0x802c36e0)) fail(`${key}: authenticated source pointer bits required`);
      write(binding, 'pointer7ec', pointer); // 621c
      write(binding, 'field7e4', zero); // 6220
      write(binding, 'byte7f7', 255); // 6224
      write(binding, 'byte7f4', 0); // 6228
      write(binding, 'byte7f5', 0); // 622c
      write(binding, 'byte7f6', 0); // 6230
    });},
    keepChargeSound(id) {guard(() => {
      const {actual} = actorForCall(id);
      const slot = b(actual, 'carriedSlot96') << 24 >> 24;
      const selected = soundRecord(slot * 0x80 + 4 * 0x10);
      if (incompleteActivations.has(selected))
        fail('known-incomplete sound activation: source row is outside the admitted active-record boundary; recovery is unmodeled');
      const current = u(selected, 'script58'); // f0148
      if (current !== 0) {
        const currentHead = soundHead(current); // f016c before desired table load.
        const desired = desiredPointer(); // f0170
        const desiredHead = soundHead(desired); // f0174
        if (currentHead !== desiredHead)
          fail('800f0180 reached unsupported source call 800f02d0 before replacement stores');
        // Equal heads branch over activation/timestamp/audio, even for distinct pointers.
        write(selected, 'owner5c', actual); // f01ec
        write(selected, 'countdown54', 2); // f01f4
        return;
      }
      const desired = desiredPointer(); // f019c, no head comparison on null.
      write(selected, 'script58', desired); // f01a0 is retained on the call refusal.
      incompleteActivations.add(selected);
      fail('800f01a4 reached unsupported source call 80207058 after script58 pointer store');
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
