/** Genuine source80068b8c and its three authenticated handlers, restricted to
 * the first685c0 call (38f8,614..617,20), optional second (3904,618..61b,40),
 * optional third (3910,61c..61f,80), fourth (391c,624..627,200),
 * fifth (3928,600..603,1), sixth (3934,604..607,2), seventh (3940,608..60b,4),
 * eighth (394c,60c..60f,8), ninth (3958,610..613,10), and tenth (3964,628..62b,2000).
 * Tables are explicitly supplied decoded owners, not synthesized callbacks,
 * implicit retail hydration or live provenance. Shared table records remain
 * shared; only missing per-actor bytes receive copied/sealed binding cells.
 * Source ordering, signed post-decrement and partial stores survive failure.
 * Plain non-proxy own-data records and stable synchronous owners are bounds.
 * Standalone binding is offline; only the joined tick claim excludes the
 * browser bridge. All ten wrappers may return, but that does not implement
 * charge686f0, full59068 or production activation.
 */
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
export interface SourceActorInputMachineBinding {
  byte614: number; byte615: number; byte616: number; byte617: number;
  byte618: number; byte619: number; byte61a: number; byte61b: number;
  byte61c: number; byte61d: number; byte61e: number; byte61f: number;
  byte624: number; byte625: number; byte626: number; byte627: number;
  byte600: number; byte601: number; byte602: number; byte603: number;
  byte604: number; byte605: number; byte606: number; byte607: number;
  byte608: number; byte609: number; byte60a: number; byte60b: number;
  byte60c: number; byte60d: number; byte60e: number; byte60f: number;
  byte610: number; byte611: number; byte612: number; byte613: number;
  byte628: number; byte629: number; byte62a: number; byte62b: number;
}
export interface SourceActorInputMachineTables {
  /** Explicit decoded 32-bit code addresses. Never host function values. */
  dispatch3988: readonly number[];
  /** Explicit decoded big-endian u16 cells at802d38f8. Index4 starts masks. */
  descriptor38f8: readonly number[];
  /** Optional distinct decoded 12-byte second descriptor. No default hydration. */
  descriptor3904?: readonly number[];
  /** Optional distinct decoded 12-byte third descriptor; its input mask is400. */
  descriptor3910?: readonly number[];
  /** Optional distinct decoded 12-byte fourth descriptor. No default hydration. */
  descriptor391c?: readonly number[];
  /** Optional distinct decoded 12-byte fifth descriptor. No default hydration. */
  descriptor3928?: readonly number[];
  /** Optional distinct decoded 12-byte sixth descriptor. No default hydration. */
  descriptor3934?: readonly number[];
  /** Optional distinct decoded 12-byte seventh descriptor. No default hydration. */
  descriptor3940?: readonly number[];
  /** Optional distinct decoded 12-byte eighth descriptor. No default hydration. */
  descriptor394c?: readonly number[];
  /** Optional distinct decoded 12-byte ninth descriptor. No default hydration. */
  descriptor3958?: readonly number[];
  /** Optional distinct decoded 12-byte tenth descriptor. No default hydration. */
  descriptor3964?: readonly number[];
}
export interface SourceActorInputMachineSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'>;
  tables: SourceActorInputMachineTables;
}
export interface SourceActorInputMachineRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorInputMachineBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActorBinding(identity: symbol): Partial<SourceActorInputMachineBinding>;
  getTables(): SourceActorInputMachineTables;
  hasSecondMachine(): boolean;
  hasThirdMachine(): boolean;
  hasFourthMachine(): boolean;
  hasFifthMachine(): boolean;
  hasSixthMachine(): boolean;
  hasSeventhMachine(): boolean;
  hasEighthMachine(): boolean;
  hasNinthMachine(): boolean;
  hasTenthMachine(): boolean;
  updateFirstMachine(identity: symbol): 0 | 1;
  updateSecondMachine(identity: symbol): 0 | 1;
  updateThirdMachine(identity: symbol): 0 | 1;
  updateFourthMachine(identity: symbol): 0 | 1;
  updateFifthMachine(identity: symbol): 0 | 1;
  updateSixthMachine(identity: symbol): 0 | 1;
  updateSeventhMachine(identity: symbol): 0 | 1;
  updateEighthMachine(identity: symbol): 0 | 1;
  updateNinthMachine(identity: symbol): 0 | 1;
  updateTenthMachine(identity: symbol): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>();
export function isSourceActorInputMachineRuntime(value: unknown): value is SourceActorInputMachineRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-input-machine] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
const fields = ['byte614', 'byte615', 'byte616', 'byte617', 'byte618', 'byte619', 'byte61a', 'byte61b', 'byte61c', 'byte61d', 'byte61e', 'byte61f',
  'byte624', 'byte625', 'byte626', 'byte627', 'byte600', 'byte601', 'byte602', 'byte603',
  'byte604', 'byte605', 'byte606', 'byte607', 'byte608', 'byte609', 'byte60a', 'byte60b',
  'byte60c', 'byte60d', 'byte60e', 'byte60f', 'byte610', 'byte611', 'byte612', 'byte613',
  'byte628', 'byte629', 'byte62a', 'byte62b'] as const;
type Field = typeof fields[number];
interface Machine {
  descriptor: readonly number[]; key: 'descriptor38f8' | 'descriptor3904' | 'descriptor3910' | 'descriptor391c' | 'descriptor3928' | 'descriptor3934' | 'descriptor3940' | 'descriptor394c' | 'descriptor3958' | 'descriptor3964';
  mask: 0x20 | 0x40 | 0x80 | 0x200 | 0x1 | 0x2 | 0x4 | 0x8 | 0x10 | 0x2000;
  phase: Field; timer: Field; index: Field; tail: Field;
}
export function createSourceActorInputMachineRuntime(sources: SourceActorInputMachineSources): SourceActorInputMachineRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (r: unknown, key: string): unknown => {const value = own(r, key); check(); return value;};
  const write = (r: unknown, key: string, value: number): void => {
    own(r, key, true); check(); (r as Record<string, unknown>)[key] = value; check();
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const world = read(sources, 'world'), method = read(world, 'getActualActor');
  if (typeof method !== 'function') fail('world.getActualActor: own data-function required');
  const worldActual = (id: symbol): unknown => {const value = Reflect.apply(method, world, [id]); check(); return value;};
  const tables = record(read(sources, 'tables'), 'decoded machine tables') as SourceActorInputMachineTables;
  const dispatch = read(tables, 'dispatch3988'), descriptor = read(tables, 'descriptor38f8');
  if (!Array.isArray(dispatch) || !Array.isArray(descriptor)) fail('explicit own-data arrays required for decoded tables');
  const secondProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3904');
  const second = secondProperty === undefined ? undefined : read(tables, 'descriptor3904');
  if (second !== undefined && !Array.isArray(second)) fail('explicit own-data array required for second descriptor');
  if (secondProperty !== undefined && second === undefined) fail('explicit second descriptor cannot be undefined');
  const thirdProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3910');
  const third = thirdProperty === undefined ? undefined : read(tables, 'descriptor3910');
  if (third !== undefined && !Array.isArray(third)) fail('explicit own-data array required for third descriptor');
  if (thirdProperty !== undefined && third === undefined) fail('explicit third descriptor cannot be undefined');
  const fourthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor391c');
  const fourth = fourthProperty === undefined ? undefined : read(tables, 'descriptor391c');
  if (fourth !== undefined && !Array.isArray(fourth)) fail('explicit own-data array required for fourth descriptor');
  if (fourthProperty !== undefined && fourth === undefined) fail('explicit fourth descriptor cannot be undefined');
  const fifthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3928');
  const fifth = fifthProperty === undefined ? undefined : read(tables, 'descriptor3928');
  if (fifth !== undefined && !Array.isArray(fifth)) fail('explicit own-data array required for fifth descriptor');
  if (fifthProperty !== undefined && fifth === undefined) fail('explicit fifth descriptor cannot be undefined');
  const sixthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3934');
  const sixth = sixthProperty === undefined ? undefined : read(tables, 'descriptor3934');
  if (sixth !== undefined && !Array.isArray(sixth)) fail('explicit own-data array required for sixth descriptor');
  if (sixthProperty !== undefined && sixth === undefined) fail('explicit sixth descriptor cannot be undefined');
  const seventhProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3940');
  const seventh = seventhProperty === undefined ? undefined : read(tables, 'descriptor3940');
  if (seventh !== undefined && !Array.isArray(seventh)) fail('explicit own-data array required for seventh descriptor');
  if (seventhProperty !== undefined && seventh === undefined) fail('explicit seventh descriptor cannot be undefined');
  const eighthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor394c');
  const eighth = eighthProperty === undefined ? undefined : read(tables, 'descriptor394c');
  if (eighth !== undefined && !Array.isArray(eighth)) fail('explicit own-data array required for eighth descriptor');
  if (eighthProperty !== undefined && eighth === undefined) fail('explicit eighth descriptor cannot be undefined');
  const ninthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3958');
  const ninth = ninthProperty === undefined ? undefined : read(tables, 'descriptor3958');
  if (ninth !== undefined && !Array.isArray(ninth)) fail('explicit own-data array required for ninth descriptor');
  if (ninthProperty !== undefined && ninth === undefined) fail('explicit ninth descriptor cannot be undefined');
  const tenthProperty = Object.getOwnPropertyDescriptor(tables, 'descriptor3964');
  const tenth = tenthProperty === undefined ? undefined : read(tables, 'descriptor3964');
  if (tenth !== undefined && !Array.isArray(tenth)) fail('explicit own-data array required for tenth descriptor');
  if (tenthProperty !== undefined && tenth === undefined) fail('explicit tenth descriptor cannot be undefined');
  const owners: object[] = [tables, dispatch, descriptor, ...(second === undefined ? [] : [second as number[]]),
    ...(third === undefined ? [] : [third as number[]]), ...(fourth === undefined ? [] : [fourth as number[]]),
    ...(fifth === undefined ? [] : [fifth as number[]]), ...(sixth === undefined ? [] : [sixth as number[]]),
    ...(seventh === undefined ? [] : [seventh as number[]]), ...(eighth === undefined ? [] : [eighth as number[]]),
    ...(ninth === undefined ? [] : [ninth as number[]]), ...(tenth === undefined ? [] : [tenth as number[]])];
  if (new Set(owners).size !== owners.length) fail('shared table/descriptor owner alias');
  const first: Machine = {descriptor, key: 'descriptor38f8', mask: 0x20,
    phase: 'byte614', timer: 'byte615', index: 'byte616', tail: 'byte617'};
  const secondMachine: Machine | undefined = second === undefined ? undefined : {
    descriptor: second as readonly number[], key: 'descriptor3904', mask: 0x40,
    phase: 'byte618', timer: 'byte619', index: 'byte61a', tail: 'byte61b'};
  const thirdMachine: Machine | undefined = third === undefined ? undefined : {
    descriptor: third as readonly number[], key: 'descriptor3910', mask: 0x80,
    phase: 'byte61c', timer: 'byte61d', index: 'byte61e', tail: 'byte61f'};
  const fourthMachine: Machine | undefined = fourth === undefined ? undefined : {
    descriptor: fourth as readonly number[], key: 'descriptor391c', mask: 0x200,
    phase: 'byte624', timer: 'byte625', index: 'byte626', tail: 'byte627'};
  const fifthMachine: Machine | undefined = fifth === undefined ? undefined : {
    descriptor: fifth as readonly number[], key: 'descriptor3928', mask: 0x1,
    phase: 'byte600', timer: 'byte601', index: 'byte602', tail: 'byte603'};
  const sixthMachine: Machine | undefined = sixth === undefined ? undefined : {
    descriptor: sixth as readonly number[], key: 'descriptor3934', mask: 0x2,
    phase: 'byte604', timer: 'byte605', index: 'byte606', tail: 'byte607'};
  const seventhMachine: Machine | undefined = seventh === undefined ? undefined : {
    descriptor: seventh as readonly number[], key: 'descriptor3940', mask: 0x4,
    phase: 'byte608', timer: 'byte609', index: 'byte60a', tail: 'byte60b'};
  const eighthMachine: Machine | undefined = eighth === undefined ? undefined : {
    descriptor: eighth as readonly number[], key: 'descriptor394c', mask: 0x8,
    phase: 'byte60c', timer: 'byte60d', index: 'byte60e', tail: 'byte60f'};
  const ninthMachine: Machine | undefined = ninth === undefined ? undefined : {
    descriptor: ninth as readonly number[], key: 'descriptor3958', mask: 0x10,
    phase: 'byte610', timer: 'byte611', index: 'byte612', tail: 'byte613'};
  const tenthMachine: Machine | undefined = tenth === undefined ? undefined : {
    descriptor: tenth as readonly number[], key: 'descriptor3964', mask: 0x2000,
    phase: 'byte628', timer: 'byte629', index: 'byte62a', tail: 'byte62b'};
  const u8 = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const u32 = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const half = (machine: Machine, index: number): number => {
    if (index < 0 || index >= 6) fail(`${machine.key}: indexed halfword outside explicit12-byte descriptor`);
    return integer(read(machine.descriptor, String(index)), 0, 65535, `${machine.key}[${index}]`);
  };
  const exclusive = (actual: object): void => {
    for (const key of [...fields, 'inputFlags5d4', 'inputEdges5bc', 'flags5e0']) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing source owner present`);
      check();
    }
  };
  interface Entry {actual: RomActor; binding: Partial<SourceActorInputMachineBinding>}
  const actors = new Map<symbol, Entry>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned input-machine actor'); return value;};
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const decrementTimer = (binding: Partial<SourceActorInputMachineBinding>, machine: Machine): boolean => {
    const next = (u8(binding, machine.timer) - 1) & 255;
    write(binding, machine.timer, next);
    if ((next << 24 >> 24) > 0) return true;
    write(binding, machine.phase, 0); return false;
  };
  const phaseTwo = ({actual, binding}: Entry, machine: Machine): void => {
    if (!decrementTimer(binding, machine)) return;
    const flags = half(machine, 1);
    if ((flags & 2) !== 0 && (u32(actual, 'controlWord') & 0x40) !== 0) return;
    if ((flags & 4) !== 0 && (u32(actual, 'controlWord') & 0x40) === 0) return;
    if ((flags & 8) !== 0 && (u32(actual, 'statusWord5b4') & 0xf0000) === 0) return;
    const input = u32(actual, (flags & 1) === 0 ? 'statusWord5bc' : 'statusWord5b4');
    const mask = half(machine, 4 + u8(binding, machine.index));
    const matched = (flags & 0x10) === 0 ? (input & mask) === mask : (input & mask) !== 0;
    if (matched) {write(binding, machine.phase, 0); write(binding, machine.tail, half(machine, 3) & 255);}
  };
  const phaseOne = ({actual, binding}: Entry, machine: Machine): void => {
    if (!decrementTimer(binding, machine)) return;
    const index = u8(binding, machine.index);
    const input = u32(actual, 'statusWord5bc');
    if ((input & half(machine, 4 + index)) === 0) return;
    write(binding, machine.timer, half(machine, 2) & 255);
    const next = (u8(binding, machine.index) + 1) & 255; write(binding, machine.index, next);
    if (next === half(machine, 0) - 1) write(binding, machine.phase, 2);
  };
  const phaseZero = (actor: Entry, machine: Machine): void => {
    const {actual, binding} = actor;
    write(binding, machine.index, 0);
    if (half(machine, 0) === 1) {
      write(binding, machine.phase, 2); write(binding, machine.timer, 127); phaseTwo(actor, machine);
    } else {
      const input = u32(actual, 'statusWord5bc');
      if ((input & half(machine, 4)) !== 0) {
        write(binding, machine.phase, 1); write(binding, machine.index, 1); write(binding, machine.timer, half(machine, 2) & 255);
      }
    }
  };
  const update = (id: symbol, machine: Machine): 0 | 1 => guard(() => {
      const actor = entry(id), {actual, binding} = actor;
      stable(worldActual(id), actual, 'world actor'); exclusive(actual);
      stable(read(tables, 'dispatch3988'), dispatch, 'dispatch3988');
      stable(read(tables, machine.key), machine.descriptor, machine.key);
      const index = u8(binding, machine.phase);
      if (index >= 3) fail('dispatch3988: indexed target outside explicit three-entry table');
      const target = u32(dispatch, String(index));
      if (target === 0x80068c14) phaseZero(actor, machine);
      else if (target === 0x80068c84) phaseOne(actor, machine);
      else if (target === 0x80068d04) phaseTwo(actor, machine);
      else fail(`80068bc8 reached unsupported source target ${target.toString(16)}`);
      // Real wrapper disregards the handler's return. Tail byte alone selects
      // decrement/edge OR and the returned Boolean, even for expired phases.
      const tail = u8(binding, machine.tail);
      if (tail === 0) return 0;
      write(binding, machine.tail, (tail - 1) & 255);
      write(actual, 'inputEdge5d4', (u32(actual, 'inputEdge5d4') | machine.mask) >>> 0);
      return 1;
    });
  const runtime: SourceActorInputMachineRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActual(id), 'actual actor') as RomActor; exclusive(actual);
      if (owners.includes(actual)) fail('actual actor aliases shared machine storage');
      if (claimed.has(actual)) fail('actual actor already claimed by source input-machine runtime');
      record(initial, 'initial machine binding');
      if ([actual, ...owners].includes(initial)) fail('initial binding aliases retained owner');
      const binding: Partial<SourceActorInputMachineBinding> = {};
      for (const key of fields) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = u8(initial, key);
      check(); actors.set(id, {actual, binding: Object.seal(binding)}); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActorBinding(id) {return entry(id).binding;},
    getTables() {return tables;},
    hasSecondMachine() {return secondMachine !== undefined;},
    hasThirdMachine() {return thirdMachine !== undefined;},
    hasFourthMachine() {return fourthMachine !== undefined;},
    hasFifthMachine() {return fifthMachine !== undefined;},
    hasSixthMachine() {return sixthMachine !== undefined;},
    hasSeventhMachine() {return seventhMachine !== undefined;},
    hasEighthMachine() {return eighthMachine !== undefined;},
    hasNinthMachine() {return ninthMachine !== undefined;},
    hasTenthMachine() {return tenthMachine !== undefined;},
    updateFirstMachine(id) {return update(id, first);},
    updateSecondMachine(id) {
      if (!secondMachine) fail('80068610 reached unsupported second source call 80068b8c (descriptor802d3904, actor+618, mask40)');
      return update(id, secondMachine);
    },
    updateThirdMachine(id) {
      if (!thirdMachine) fail('80068628 reached unsupported third source call 80068b8c (descriptor802d3910, actor+61c, mask80)');
      return update(id, thirdMachine);
    },
    updateFourthMachine(id) {
      if (!fourthMachine) fail('80068640 reached unsupported fourth source call 80068b8c (descriptor802d391c, actor+624, mask200)');
      return update(id, fourthMachine);
    },
    updateFifthMachine(id) {
      if (!fifthMachine) fail('80068658 reached unsupported fifth source call 80068b8c (descriptor802d3928, actor+600, mask1)');
      return update(id, fifthMachine);
    },
    updateSixthMachine(id) {
      if (!sixthMachine) fail('80068670 reached unsupported sixth source call 80068b8c (descriptor802d3934, actor+604, mask2)');
      return update(id, sixthMachine);
    },
    updateSeventhMachine(id) {
      if (!seventhMachine) fail('80068688 reached unsupported seventh source call 80068b8c (descriptor802d3940, actor+608, mask4)');
      return update(id, seventhMachine);
    },
    updateEighthMachine(id) {
      if (!eighthMachine) fail('800686a0 reached unsupported eighth source call 80068b8c (descriptor802d394c, actor+60c, mask8)');
      return update(id, eighthMachine);
    },
    updateNinthMachine(id) {
      if (!ninthMachine) fail('800686b8 reached unsupported ninth source call 80068b8c (descriptor802d3958, actor+610, mask10)');
      return update(id, ninthMachine);
    },
    updateTenthMachine(id) {
      if (!tenthMachine) fail('800686d0 reached unsupported tenth source call 80068b8c (descriptor802d3964, actor+628, mask2000)');
      return update(id, tenthMachine);
    },
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
