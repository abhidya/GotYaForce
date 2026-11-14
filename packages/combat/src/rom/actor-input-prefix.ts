/** Bounded source800685c0 -> real68980 + real6de44, offline only.
 * Actual actor owns5b4/5bc/5d4 and HALFWORD5d8, independent of states5da/5db.
 * The same actual Borg as the gauge/tick graph owns sourceArrowMash749.
 * Only absent5b8/5ca/5cb/5fc..5ff get explicit cells, without defaults.
 * 8b73c retains its genuine integer-radius zero return. Reached psq_l at8b778
 * requires an explicit signed8/scale0 processor profile. An optional genuine
 * angular runtime closes axis paths and table lookup; its optional genuine atan
 * runtime extends this to every canonical signed-byte X/Y pair.
 * HID2[PSE/LSQE]=1 and big-endian are host domain preconditions, not measured
 * hardware. Missing atan retains diagonal refusals; no Math.atan2 substitute.
 * After68980 returns,5d4 is cleared. Optional genuine firstMachine executes
 * actual68b8c at685f8; optional descriptor3904 continues the second call at68610.
 * Optional descriptors3910/391c/3928/3934/3940/394c/3958/3964 continue the third through tenth calls.
 * Absent optional owners preserve their original callsite refusals.
 * Optional genuine charge686f0 admits its bounded skip/reset/release/warmup
 * returns or preserves reached sound/effect refusals; optional genuine color
 * initialization/sound keepalive use explicit shared owners. No fulltick, input capture
 * or production activation. The outer59068 caller still refuses its next helper.
 * Non-proxy own records and stable synchronous exclusive owners are bounds.
 * Every reached failure retains prior writes. Binding permanently excludes
 * the legacy browser mash producer for this Borg, without implicit migration.
 */
import type {BorgRuntime} from '../types.js';
import type {RomActor} from './actor.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorGaugeScaleRuntime, SourceActorGaugeBorgOwner} from './actor-gauge-scale.js';
import {isSourceActorInputMachineRuntime, type SourceActorInputMachineRuntime} from './actor-input-machine.js';
import {isSourceActorInputChargeRuntime, type SourceActorInputChargeRuntime} from './actor-input-charge.js';
import {loadSourceInputSignedByte} from './source-input-quantized.js';
import {isSourceInputAngleRuntime, type SourceInputAngleRuntime, type SourceInputAngleProcessorState} from './source-input-angle.js';
export interface SourceActorInputPrefixBinding {
  /** Actual lhz at5b8: high half of a big-endian prior word, not low16. */
  ushort5b8: number;
  stickX5ca: number; stickY5cb: number;
  byte5fc: number; byte5fd: number; byte5fe: number; byte5ff: number;
}
export type SourceActorInputBorgOwner = SourceActorGaugeBorgOwner & Pick<BorgRuntime, 'sourceArrowMash749'>;
export interface SourceActorInputProcessorState extends SourceInputAngleProcessorState {gqr4: number}
export interface SourceActorInputPrefixSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor'> & Partial<Pick<SourceActorWorldMatrixRuntime, 'getMappingActor'>>;
  gauges: Pick<SourceActorGaugeScaleRuntime, 'getActualActor' | 'getActualBorg'> & Partial<Pick<SourceActorGaugeScaleRuntime, 'getStatusBinding'>>;
  /** Optional real first68b8c call; absent preserves its historical refusal. */
  firstMachine?: SourceActorInputMachineRuntime;
  /** Optional real686f0. Requires the same world/mapping/status owners. */
  charge?: SourceActorInputChargeRuntime;
  /** Actual caller-owned register record; absence retains8b778 refusal. */
  processor?: SourceActorInputProcessorState;
  /** Optional genuine angular/table path and finite atan opt-in, with the same processor. */
  angular?: SourceInputAngleRuntime;
}
export interface SourceActorInputPrefixRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorInputPrefixBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getActualBorg(identity: symbol): SourceActorInputBorgOwner;
  getActorBinding(identity: symbol): Partial<SourceActorInputPrefixBinding>;
  /** Retained genuine runtime for shared match-global agreement; no source reads. */
  getChargeRuntime(): SourceActorInputChargeRuntime | undefined;
  /** Genuine685c0 return only after all ten wrappers and bounded charge return. */
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimed = new WeakSet<object>(), claimedBorgs = new WeakSet<object>();
export function isSourceActorInputPrefixRuntime(value: unknown): value is SourceActorInputPrefixRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
export function isSourceActorInputPrefixClaimedBorg(value: unknown): boolean {
  return value !== null && typeof value === 'object' && claimedBorgs.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-input-prefix] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
const fields = ['ushort5b8', 'stickX5ca', 'stickY5cb', 'byte5fc', 'byte5fd', 'byte5fe', 'byte5ff'] as const;
export function createSourceActorInputPrefixRuntime(sources: SourceActorInputPrefixSources): SourceActorInputPrefixRuntime {
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
  const capture = (name: keyof SourceActorInputPrefixSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(fn, receiver, [id]); check(); return value;};
  };
  const worldActual = capture('world', 'getActualActor'), gaugeActual = capture('gauges', 'getActualActor');
  const gaugeBorg = capture('gauges', 'getActualBorg');
  const processorProperty = Object.getOwnPropertyDescriptor(sources, 'processor');
  const processor = processorProperty === undefined ? undefined : record(read(sources, 'processor'), 'processor record');
  const angleProperty = Object.getOwnPropertyDescriptor(sources, 'angular');
  const angular = angleProperty === undefined ? undefined : read(sources, 'angular');
  if (angleProperty !== undefined && !isSourceInputAngleRuntime(angular))
    fail('angular path requires the genuine source runtime, not callback results');
  const angleRuntime = angular as SourceInputAngleRuntime | undefined;
  if (angleRuntime && angleRuntime.getProcessor() !== processor) fail('angular path requires the same explicit processor owner');
  const angleData = angleRuntime?.getData();
  const atanData = angleRuntime?.getAtanRuntime()?.getData();
  const angleDirection = angleRuntime === undefined ? undefined : read(angleRuntime, 'direction');
  if (angleRuntime && typeof angleDirection !== 'function') fail('angular.direction: own data-function required');
  const machine = Object.getOwnPropertyDescriptor(sources, 'firstMachine');
  if (machine !== undefined && !isSourceActorInputMachineRuntime(read(sources, 'firstMachine')))
    fail('first machine requires the genuine source runtime, not callback effects');
  const machineActual = machine === undefined ? undefined : capture('firstMachine', 'getActualActor');
  const machineBinding = machine === undefined ? undefined : capture('firstMachine', 'getActorBinding');
  const updateMachine = machine === undefined ? undefined : capture('firstMachine', 'updateFirstMachine');
  const hasSecondMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasSecondMachine();
  const updateSecondMachine = !hasSecondMachine ? undefined : capture('firstMachine', 'updateSecondMachine');
  const hasThirdMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasThirdMachine();
  const updateThirdMachine = !hasThirdMachine ? undefined : capture('firstMachine', 'updateThirdMachine');
  const hasFourthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasFourthMachine();
  const updateFourthMachine = !hasFourthMachine ? undefined : capture('firstMachine', 'updateFourthMachine');
  const hasFifthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasFifthMachine();
  const updateFifthMachine = !hasFifthMachine ? undefined : capture('firstMachine', 'updateFifthMachine');
  const hasSixthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasSixthMachine();
  const updateSixthMachine = !hasSixthMachine ? undefined : capture('firstMachine', 'updateSixthMachine');
  const hasSeventhMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasSeventhMachine();
  const updateSeventhMachine = !hasSeventhMachine ? undefined : capture('firstMachine', 'updateSeventhMachine');
  const hasEighthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasEighthMachine();
  const updateEighthMachine = !hasEighthMachine ? undefined : capture('firstMachine', 'updateEighthMachine');
  const hasNinthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasNinthMachine();
  const updateNinthMachine = !hasNinthMachine ? undefined : capture('firstMachine', 'updateNinthMachine');
  const hasTenthMachine = machine === undefined ? false :
    (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).hasTenthMachine();
  const updateTenthMachine = !hasTenthMachine ? undefined : capture('firstMachine', 'updateTenthMachine');
  const machineTables = machine === undefined ? undefined : (read(sources, 'firstMachine') as SourceActorInputMachineRuntime).getTables();
  const chargeProperty = Object.getOwnPropertyDescriptor(sources, 'charge');
  if (chargeProperty !== undefined && !isSourceActorInputChargeRuntime(read(sources, 'charge')))
    fail('charge requires the genuine source runtime, not callback effects');
  const chargeRuntime = chargeProperty === undefined ? undefined : read(sources, 'charge') as SourceActorInputChargeRuntime;
  const chargeActual = !chargeRuntime ? undefined : capture('charge', 'getActualActor');
  const chargeBinding = !chargeRuntime ? undefined : capture('charge', 'getActorBinding');
  const chargeStatus = !chargeRuntime ? undefined : capture('charge', 'getStatusBinding');
  const chargeMapping = !chargeRuntime ? undefined : capture('charge', 'getMappingActor');
  const chargeAttribute = !chargeRuntime ? undefined : capture('charge', 'getAttributeBinding');
  const updateCharge = !chargeRuntime ? undefined : capture('charge', 'updateActor');
  const gaugeStatus = !chargeRuntime ? undefined : capture('gauges', 'getStatusBinding');
  const worldMapping = !chargeRuntime ? undefined : capture('world', 'getMappingActor');
  const chargeGlobal = chargeRuntime?.getGlobal(), chargeData = chargeRuntime?.getData();
  const chargeEffects = chargeRuntime?.getEffects(), effectData = chargeEffects?.getData(), effectSound = chargeEffects?.getSound();
  interface ChargeOwners {binding: object; status: object; mapping: object; attribute: object; effect?: object}
  const u8 = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const s8 = (r: unknown, key: string): number => integer(read(r, key), -128, 127, key);
  const u16 = (r: unknown, key: string): number => integer(read(r, key), 0, 65535, key);
  const u32 = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const exclusive = (actual: object): void => {
    for (const key of ['inputFlags5d4', 'inputFlags5d8', 'inputEdges5bc', 'sourceArrowMash749', 'byte749', ...fields]) {
      if (Object.getOwnPropertyDescriptor(actual, key) !== undefined) fail(`${key}: competing source owner present`);
      check();
    }
  };
  // Ownership preflight inspects only optional own-data references. It neither
  // requires missing tables nor reads any selected source byte/constant early.
  // Repeating it at entry catches aliases introduced after the initial claim.
  const independentOwners = (actual: object, borg: object, machineOwner: object | undefined, binding: object, charge?: ChargeOwners): void => {
    const present = (owner: object | undefined, key: string): object | undefined => {
      if (!owner) return undefined;
      const property = Object.getOwnPropertyDescriptor(owner, key); check();
      const value: unknown = property && 'value' in property ? property.value : undefined;
      return value !== null && typeof value === 'object' ? value : undefined;
    };
    const soundRecords = present(effectSound, 'records3ae8'), soundScripts = present(effectSound, 'scripts');
    const references = (owner: object | undefined): object[] => {
      if (!owner) return [];
      const values = Object.values(Object.getOwnPropertyDescriptors(owner)); check();
      return values.filter(p => 'value' in p && p.value !== null && typeof p.value === 'object').map(p => p.value as object);
    };
    const owners = [actual, borg, machineOwner, binding, processor, angleData, atanData, machineTables,
      charge?.binding, charge?.status, charge?.mapping, charge?.attribute, charge?.effect, chargeGlobal, chargeData,
      effectData, effectSound, soundRecords, soundScripts, ...references(soundRecords), ...references(soundScripts),
      present(chargeData, 'held3970'), present(chargeData, 'release397c'),
      present(machineTables, 'dispatch3988'), present(machineTables, 'descriptor38f8'),
      present(machineTables, 'descriptor3904'), present(machineTables, 'descriptor3910'), present(machineTables, 'descriptor391c'),
      present(machineTables, 'descriptor3928'), present(machineTables, 'descriptor3934'), present(machineTables, 'descriptor3940'),
      present(machineTables, 'descriptor394c'), present(machineTables, 'descriptor3958'), present(machineTables, 'descriptor3964'),
      present(angleData, 'direction80433928'),
      present(atanData, 'atanHi802b5168'), present(atanData, 'atanLo802b5188'), present(atanData, 'coefficients802b51a8')]
      .filter((owner): owner is object => owner !== undefined);
    if (new Set(owners).size !== owners.length) fail('retained input/global/processor storage owner alias');
  };
  interface Entry {actual: RomActor; borg: SourceActorInputBorgOwner; machine?: object; charge?: ChargeOwners; binding: Partial<SourceActorInputPrefixBinding>}
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const value = actors.get(id); if (!value) fail('unknown/non-owned input actor'); return value;};
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  const direction = (binding: Partial<SourceActorInputPrefixBinding>, threshold: 20 | 52): number => {
    // The actor callsite loads X then Y; 8b73c masks/extsb, integer squares,
    // unsigned comparison. Every signed-byte pair fits this exact JS domain.
    const x = s8(binding, 'stickX5ca'), y = s8(binding, 'stickY5cb');
    if (x * x + y * y < threshold * threshold) return 0;
    if (!processor) fail('8008b778 reached unsupported source psq_l/GQR conversion before 800452a0 direction/table work');
    // Source stack bytes retain the earlier X/Y loads. Each quantized load
    // reads the same actual GQR4 record at its own reached instruction.
    const f2 = loadSourceInputSignedByte(x, u32(processor, 'gqr4'))[0]; // X at8b778
    const f1 = loadSourceInputSignedByte(y, u32(processor, 'gqr4'))[0]; // Y at8b77c
    if (!angleDirection) fail('8008b780 reached unsupported source angular call 800452a0 after genuine signed8/scale0 conversion');
    const result = Reflect.apply(angleDirection as (...args: number[]) => unknown, angleRuntime, [f2, f1]); check();
    return integer(result, 0, 255, 'genuine angular/table byte return');
  };
  const runtime: SourceActorInputPrefixRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActual(id), 'actual actor') as RomActor; exclusive(actual);
      stable(gaugeActual(id), actual, 'gauge actor');
      const borg = record(gaugeBorg(id), 'actual Borg') as SourceActorInputBorgOwner;
      if ((actual as object) === borg || assigned.has(actual) || assigned.has(borg)) fail('source owner alias');
      if (claimed.has(actual) || claimedBorgs.has(borg)) fail('actual actor/Borg already claimed by source input runtime');
      let machineOwner: object | undefined;
      if (machineActual) {
        stable(machineActual(id), actual, 'machine actor');
        machineOwner = record(machineBinding!(id), 'machine binding');
        if (machineOwner === actual || machineOwner === borg || assigned.has(machineOwner)) fail('source machine owner alias');
      }
      let chargeOwners: ChargeOwners | undefined;
      if (chargeActual) {
        stable(chargeActual(id), actual, 'charge actor');
        chargeOwners = {binding: record(chargeBinding!(id), 'charge binding'),
          status: record(chargeStatus!(id), 'charge status'), mapping: record(chargeMapping!(id), 'charge mapping'),
          attribute: record(chargeAttribute!(id), 'charge attribute'),
          ...(chargeEffects ? {effect: record(chargeEffects.getActorBinding(id), 'charge effect binding')} : {})};
        stable(gaugeStatus!(id), chargeOwners.status, 'gauge/charge status');
        stable(worldMapping!(id), chargeOwners.mapping, 'world/charge mapping');
        if (Object.values(chargeOwners).some(value => assigned.has(value))) fail('charge owner aliases another bound input actor');
      }
      if (processor && (processor === actual || processor === borg || processor === machineOwner)) fail('processor record aliases mutable source owner');
      if (angleData && (angleData === actual || angleData === borg || angleData === machineOwner)) fail('angular data aliases mutable source owner');
      record(initial, 'initial input binding');
      const binding: Partial<SourceActorInputPrefixBinding> = {};
      for (const key of fields) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined)
        binding[key] = key === 'ushort5b8' ? u16(initial, key) : key.startsWith('stick') ? s8(initial, key) : u8(initial, key);
      independentOwners(actual, borg, machineOwner, binding, chargeOwners);
      check(); actors.set(id, {actual, borg, ...(machineOwner === undefined ? {} : {machine: machineOwner}),
        ...(chargeOwners === undefined ? {} : {charge: chargeOwners}), binding: Object.seal(binding)});
      assigned.add(actual); assigned.add(borg); if (machineOwner) assigned.add(machineOwner);
      if (chargeOwners) Object.values(chargeOwners).forEach(value => assigned.add(value));
      claimed.add(actual); claimedBorgs.add(borg);
    });},
    getActualActor(id) {return entry(id).actual;},
    getActualBorg(id) {return entry(id).borg;},
    getActorBinding(id) {return entry(id).binding;},
    getChargeRuntime() {return chargeRuntime;},
    updateActor(id): void {return guard(() => {
      const actor = entry(id), {actual, borg, binding} = actor;
      stable(worldActual(id), actual, 'world actor'); stable(gaugeActual(id), actual, 'gauge actor');
      stable(gaugeBorg(id), borg, 'gauge Borg'); exclusive(actual);
      if (machineActual) {
        stable(machineActual(id), actual, 'machine actor');
        stable(machineBinding!(id), actor.machine!, 'machine binding');
      }
      if (actor.charge) {
        stable(chargeActual!(id), actual, 'charge actor');
        stable(chargeBinding!(id), actor.charge.binding, 'charge binding');
        stable(chargeStatus!(id), actor.charge.status, 'charge status');
        stable(chargeMapping!(id), actor.charge.mapping, 'charge mapping');
        stable(chargeAttribute!(id), actor.charge.attribute, 'charge attribute');
        if (chargeEffects) stable(chargeEffects.getActorBinding(id), actor.charge.effect!, 'charge effect binding');
        stable(gaugeStatus!(id), actor.charge.status, 'gauge/charge status');
        stable(worldMapping!(id), actor.charge.mapping, 'world/charge mapping');
      }
      independentOwners(actual, borg, actor.machine, binding, actor.charge);
      // Real returned direction bytes drive the source's two independent gates.
      // Each clear/store/reload remains separate, including second-gate H&mask.
      if ((u8(binding, 'byte5fc') & 1) === 0) {
        const mask = direction(binding, 20);
        if (mask !== 0) {
          write(binding, 'byte5fc', u8(binding, 'byte5fc') | 1);
          write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & 0xfff0);
          write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') | mask);
          write(binding, 'byte5fd', (u16(actual, 'inputHeld5d8') & 0xc) === 0 ? 2 : 3);
        }
      }
      if ((u8(binding, 'byte5fc') & 2) === 0) {
        const mask = direction(binding, 52);
        if (mask !== 0) {
          write(binding, 'byte5fc', u8(binding, 'byte5fc') | 2);
          write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & 0xff0f);
          const held = u16(actual, 'inputHeld5d8');
          write(actual, 'inputHeld5d8', held | ((held & mask) << 4));
          write(binding, 'byte5fd', 20);
        }
      }
      const heldLatch = u8(binding, 'byte5fc');
      if ((heldLatch & 8) === 0) {
        const held = u32(actual, 'statusWord5b4') & 0xf0000;
        if (held !== 0) {
          write(binding, 'byte5fc', heldLatch | 8);
          write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & 0xf0ff);
          const masked = u16(actual, 'inputHeld5d8');
          write(actual, 'inputHeld5d8', masked | ((held >>> 8) & (masked >>> 4)));
          write(binding, 'byte5ff', 20);
        }
      } else if ((u32(actual, 'statusWord5b4') & 0xf0000) === 0) {
        write(binding, 'byte5fc', 0);
        write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & 0xfff);
        const prior = u16(binding, 'ushort5b8');
        write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') | ((prior & 15) << 12));
        write(binding, 'byte5fe', 16);
      }
      for (const key of ['byte5fd', 'byte5ff'] as const) {
        const old = u8(binding, key);
        if (old !== 0) {
          const next = (old - 1) & 255; write(binding, key, next);
          if ((next << 24 >> 24) < 1)
            write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & (key === 'byte5fd' ? 0xff00 : 0xf0ff));
        }
      }
      const release = u8(binding, 'byte5fe');
      if (release !== 0) {
        const next = (release - 1) & 255; write(binding, 'byte5fe', next);
        if (next === 0) write(actual, 'inputHeld5d8', u16(actual, 'inputHeld5d8') & 0xfff);
      }
      // Real6de44 visits four groups of eight low bits, arithmetic-shifting
      // between groups. For the fixed positive mask every set bit is counted.
      let bits = u32(actual, 'statusWord5bc') & 0xf0f00, count = 0;
      for (let group = 0; group < 4; group++) {
        for (let bit = 0; bit < 8; bit++) count += (bits >> bit) & 1;
        bits >>= 8;
      }
      write(borg, 'sourceArrowMash749', count);
      write(actual, 'inputEdge5d4', 0);
      if (!updateMachine) fail('800685f8 reached unsupported source call 80068b8c (descriptor802d38f8, actor+614, mask20)');
      const machineResult = updateMachine(id);
      if (machineResult !== 0 && machineResult !== 1) fail('genuine first input machine returned asynchronously or unexpectedly');
      if (!updateSecondMachine) fail('80068610 reached unsupported second source call 80068b8c (descriptor802d3904, actor+618, mask40)');
      const secondResult = updateSecondMachine(id);
      if (secondResult !== 0 && secondResult !== 1) fail('genuine second input machine returned asynchronously or unexpectedly');
      if (!updateThirdMachine) fail('80068628 reached unsupported third source call 80068b8c (descriptor802d3910, actor+61c, mask80)');
      const thirdResult = updateThirdMachine(id);
      if (thirdResult !== 0 && thirdResult !== 1) fail('genuine third input machine returned asynchronously or unexpectedly');
      if (!updateFourthMachine) fail('80068640 reached unsupported fourth source call 80068b8c (descriptor802d391c, actor+624, mask200)');
      const fourthResult = updateFourthMachine(id);
      if (fourthResult !== 0 && fourthResult !== 1) fail('genuine fourth input machine returned asynchronously or unexpectedly');
      if (!updateFifthMachine) fail('80068658 reached unsupported fifth source call 80068b8c (descriptor802d3928, actor+600, mask1)');
      const fifthResult = updateFifthMachine(id);
      if (fifthResult !== 0 && fifthResult !== 1) fail('genuine fifth input machine returned asynchronously or unexpectedly');
      if (!updateSixthMachine) fail('80068670 reached unsupported sixth source call 80068b8c (descriptor802d3934, actor+604, mask2)');
      const sixthResult = updateSixthMachine(id);
      if (sixthResult !== 0 && sixthResult !== 1) fail('genuine sixth input machine returned asynchronously or unexpectedly');
      if (!updateSeventhMachine) fail('80068688 reached unsupported seventh source call 80068b8c (descriptor802d3940, actor+608, mask4)');
      const seventhResult = updateSeventhMachine(id);
      if (seventhResult !== 0 && seventhResult !== 1) fail('genuine seventh input machine returned asynchronously or unexpectedly');
      if (!updateEighthMachine) fail('800686a0 reached unsupported eighth source call 80068b8c (descriptor802d394c, actor+60c, mask8)');
      const eighthResult = updateEighthMachine(id);
      if (eighthResult !== 0 && eighthResult !== 1) fail('genuine eighth input machine returned asynchronously or unexpectedly');
      if (!updateNinthMachine) fail('800686b8 reached unsupported ninth source call 80068b8c (descriptor802d3958, actor+610, mask10)');
      const ninthResult = updateNinthMachine(id);
      if (ninthResult !== 0 && ninthResult !== 1) fail('genuine ninth input machine returned asynchronously or unexpectedly');
      if (!updateTenthMachine) fail('800686d0 reached unsupported tenth source call 80068b8c (descriptor802d3964, actor+628, mask2000)');
      const tenthResult = updateTenthMachine(id);
      if (tenthResult !== 0 && tenthResult !== 1) fail('genuine tenth input machine returned asynchronously or unexpectedly');
      if (!updateCharge) fail('800686d8 reached unsupported source charge helper 800686f0');
      if (updateCharge(id) !== undefined) fail('genuine charge helper returned asynchronously or unexpectedly');
      // Actual685c0 now returns. The caller owns the next59068 operation.
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
