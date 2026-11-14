/** Bounded actual 8005568c, including its unconditional leaf 8006dcc0.
 * Source: chunk_0006.c:7812–8085, chunk_0009.c:2909–2973 and the fixed
 * archived status-timer evidence reader. Explicit RN00/NI0, finite binary32,
 * non-proxy own-data records, stable synchronous owners are admission bounds.
 * Reads, destination checks and stores follow the reached source prefix.
 * Refusals keep all earlier effects. No callbacks stand in for source callees.
 *
 * Full return is admitted with zero poison, null children, no reached f0104,
 * 5c290, unbound3d3e8/3d444, and no reached mode1 positive-debt divide. Mode0 ammo is
 * active, mode1 expiry is active, other modes genuinely skip. This is not a
 * whole tick/spawn, production activation or retail-provenance claim.
 *
 * All existing fields stay on actual world/movement/mapping/attribute/stream,
 * BorgRuntime and WeaponCell owners. Only missing offsets are stored here.
 * mapping.timestep1dc8 is the source clock, NOT legacy RomActor.dt. Stream
 * marker709 is the source byte, NOT legacy contactFlags. Borg invincTimer is
 * the selected source720 owner; actors with legacy invulnTimer are refused.
 * Three explicit distinct source ammo cells avoid browser HUD/X-pool aliases.
 */
import type {BorgRuntime, WeaponCell} from '../types.js';
import type {RomActor} from './actor.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import type {SourceActorMovementFollowupRuntime} from './actor-movement-followup.js';
import type {SourceActorAttributeRefreshRuntime} from './actor-attribute-refresh.js';
import type {SourceStreamWaitRuntime} from './stream-wait.js';
import {addSourceFloat32} from './source-float.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';

export interface SourceActorStatusTimersBinding {
  field690: number; field69c: number; field6a0: number; field6a4: number;
  byte6fc: number; byte7de: number; byte71c: number;
  byte656: number; byte593: number; byte594: number; byte596: number;
  byte707: number; byte708: number;
  bytea8: number; bytea9: number; byteaa: number; byteab: number; byteac: number; bytead: number;
  short736: number; short738: number; short73a: number; byte747: number;
  field1dcc: number; field7d8: number; short272: number;
  /** Explicit missing source pointer storage. Borrowed, not copied. */
  readonly childPointers440: readonly (symbol | null)[];
  byte7d4: number; field8c8: number;
  /** Reaction prefix only; the actual 5c290 remains unsupported. */
  byte6fd: number; byte702: number; short282: number; short284: number; short6b6: number;
}
/** A borrow of the actual intended host runtime, never a copied snapshot. */
export type SourceActorStatusBorgOwner = Pick<BorgRuntime, 'hp' | 'hitDrainFrames' |
  'balanceGauge' | 'balanceGaugeMax' | 'balanceRefillDelay' | 'downResetDelay' |
  'comboWindow' | 'comboAccum' | 'comboRank' | 'invincTimer' | 'sourceAmmoRefillPauseMask'> &
  /** Existing Borg cells, required lazily by reached ready/rate lifecycle paths. */
  Partial<Pick<BorgRuntime, 'maxHp' | 'colorVariant' | 'slowHitTimer' | 'hasteHitTimer' |
    'slowAuraLevel' | 'hasteAuraLevel' | 'slowHitLevel' | 'hasteHitLevel'>>;
export interface SourceActorStatusAmmoSlot {
  readonly cell: WeaponCell;
  /** Explicit otherwise-missing source +776 (+8*slot), not a HUD alias. */
  mirror776?: number;
}
export interface SourceActorStatusTimersSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  mapping: Pick<SourceActorJointMappingRuntime, 'getActor'>;
  movement: Pick<SourceActorMovementFollowupRuntime, 'getActualActor' | 'getActorBinding'>;
  attributes: Pick<SourceActorAttributeRefreshRuntime, 'getActorBinding' | 'getParameterDescriptor'>;
  streams: Pick<SourceStreamWaitRuntime, 'getStartActorBinding'>;
}
export interface SourceActorStatusTimersRuntime {
  bindActor(identity: symbol, actualBorg: SourceActorStatusBorgOwner,
    initial: Readonly<Partial<SourceActorStatusTimersBinding>>,
    ammoSlots: readonly [SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot]): void;
  getActorBinding(identity: symbol): Partial<SourceActorStatusTimersBinding>;
  getActualActor(identity: symbol): RomActor;
  /** Existing borrowed owners, exposed for source charge/lifecycle agreement. */
  getWorldBinding(identity: symbol): object;
  getMappingActor(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getMovementBinding(identity: symbol): object;
  getActualBorg(identity: symbol): SourceActorStatusBorgOwner;
  /** Explicit late connection to the genuine reset pair on these same owners. */
  bindGaugeResetSources(identity: symbol, gauges: SourceActorGaugeScaleRuntime): void;
  updateActor(identity: symbol): void;
}
const FLOATS = ['field690', 'field69c', 'field6a0', 'field6a4', 'field1dcc', 'field7d8', 'field8c8'] as const;
const BYTES = ['byte6fc', 'byte7de', 'byte71c', 'byte656', 'byte593', 'byte594', 'byte596',
  'byte707', 'byte708', 'bytea8', 'bytea9', 'byteaa', 'byteab', 'byteac', 'bytead', 'byte747', 'byte7d4', 'byte6fd', 'byte702'] as const;
const SHORTS = ['short736', 'short738', 'short73a', 'short272', 'short282', 'short284', 'short6b6'] as const;
function fail(reason: string): never {
  throw Error(`[actor-status-timers] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
const s16 = (value: number): number => value << 16 >> 16;
export function createSourceActorStatusTimersRuntime(sources: SourceActorStatusTimersSources): SourceActorStatusTimersRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (record: unknown, key: string): unknown => {const value = own(record, key); check(); return value;};
  const write = (record: unknown, key: string, value: number): void => {
    own(record, key, true); check(); (record as Record<string, unknown>)[key] = value; check();
  };
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual owned record required`);
    return value;
  };
  const capture = (name: keyof SourceActorStatusTimersSources, key: string) => {
    const receiver = own(sources, name), fn = own(receiver, key);
    if (typeof fn !== 'function') fail(`${name}.${key}: own data-function required`);
    return (id: symbol): unknown => {const result = Reflect.apply(fn, receiver, [id]); check(); return result;};
  };
  const worldActor = capture('world', 'getActualActor'), worldBinding = capture('world', 'getActorBinding');
  const mappingActor = capture('mapping', 'getActor'), movementActor = capture('movement', 'getActualActor');
  const movementBinding = capture('movement', 'getActorBinding'), attributes = capture('attributes', 'getActorBinding');
  const parameters = capture('attributes', 'getParameterDescriptor'), streams = capture('streams', 'getStartActorBinding');
  const f = (r: unknown, key: string): number => float(read(r, key), key);
  const b = (r: unknown, key: string): number => integer(read(r, key), 0, 255, key);
  const h = (r: unknown, key: string): number => integer(read(r, key), -32768, 32767, key);
  const u = (r: unknown, key: string): number => integer(read(r, key), 0, 0xffffffff, key);
  const pointer = (value: unknown, where: string): symbol | null => {
    if (value !== null && typeof value !== 'symbol') fail(`${where}: decoded symbol or null required`); return value;
  };
  const noLegacy720 = (actual: object): void => {
    if (Object.getOwnPropertyDescriptor(actual, 'invulnTimer') !== undefined)
      fail('source720 owner conflict: legacy RomActor.invulnTimer is present; actual BorgRuntime.invincTimer is the selected owner');
    check();
  };
  interface Entry {
    actual: RomActor; world: object; mapping: object; movement: object; attribute: object; stream: object;
    borg: SourceActorStatusBorgOwner; binding: Partial<SourceActorStatusTimersBinding>;
    slots: readonly SourceActorStatusAmmoSlot[]; cells: readonly object[]; slotRecords: readonly object[];
    children: object | undefined;
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>(), parameterOwners = new Map<symbol, object>();
  interface GaugeSources {actor: () => unknown; borg: () => unknown; status: () => unknown; down: () => unknown; secondary: () => unknown}
  const gaugeSources = new Map<symbol, GaugeSources>();
  const parameterIdentities = new WeakMap<object, symbol>();
  const entry = (id: symbol): Entry => {const found = actors.get(id); if (!found) fail('unknown/non-owned status actor'); return found;};
  const stable = (get: (id: symbol) => unknown, id: symbol, expected: object, where: string): object => {
    if (get(id) !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`); return expected;
  };
  const parameter = (id: symbol, actor: Entry): object => {
    stable(attributes, id, actor.attribute, 'attribute');
    const selected = pointer(read(actor.attribute, 'parameter4ac'), 'parameter4ac');
    if (selected === null) fail('parameter4ac requires an explicitly owned parameter descriptor');
    const actual = record(parameters(selected), 'parameter4ac');
    const prior = parameterOwners.get(selected);
    if (prior !== undefined && prior !== actual) fail('parameter4ac owner changed its actual record');
    const otherIdentity = parameterIdentities.get(actual);
    if (assigned.has(actual) || (otherIdentity !== undefined && otherIdentity !== selected))
      fail('parameter4ac aliases another source owner or parameter identity');
    parameterOwners.set(selected, actual); parameterIdentities.set(actual, selected); return actual;
  };
  const ammo = (actor: Entry): void => {
    // 6dcc4 precedes 6dcc8 even though the decompiler prints the opposite order.
    const burst = b(actor.binding, 'byte6fc');
    let rate = f(actor.actual, 'aimRateScale');
    if (burst !== 0) rate = float(Math.fround(rate * 10), 'fmuls rate*10 result');
    for (let index = 0; index < 3; index++) {
      // Fresh source597 for every slot. No timer/mode/mirror read in paused slots.
      if ((b(actor.borg, 'sourceAmmoRefillPauseMask') & (1 << index)) !== 0) continue;
      if (read(actor.slots, String(index)) !== actor.slotRecords[index]) fail('source ammo slot owner changed');
      const slot = actor.slotRecords[index]!, cell = actor.cells[index]!;
      if (read(slot, 'cell') !== cell) fail('source ammo cell owner changed');
      const debt = f(cell, 'timer');
      if (debt <= 0) continue;
      const mode = h(cell, 'refillType');
      if (mode !== 0 && mode !== 1) continue;
      write(cell, 'timer', addSourceFloat32(debt, -rate));
      const remaining = f(cell, 'timer');
      if (remaining <= 0) {
        write(cell, 'cur', h(cell, 'max'));
        write(slot, 'mirror776', h(cell, 'max')); // Separate max reload after cur store.
        if (mode === 0) write(cell, 'timer', 0);
      } else if (mode === 1) {
        // Actual signed parameter conversion and max/current loads precede fdivs.
        h(cell, 'refillParam'); h(cell, 'max'); h(cell, 'cur');
        fail('8006ddbc mode1 positive-debt fdivs is outside the admitted arithmetic domain');
      }
    }
  };
  return Object.freeze({
    bindActor(id: symbol, actualBorg: SourceActorStatusBorgOwner,
      initial: Readonly<Partial<SourceActorStatusTimersBinding>>,
      ammoSlots: readonly [SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot, SourceActorStatusAmmoSlot]): void {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (movementActor(id) !== actual) fail('world/movement actual RomActor owners differ');
      noLegacy720(actual);
      const world = record(worldBinding(id), 'world binding'), mapping = record(mappingActor(id), 'mapping actor');
      const movement = record(movementBinding(id), 'movement binding'), attribute = record(attributes(id), 'attribute binding');
      const stream = record(streams(id), 'stream start binding'), borg = record(actualBorg, 'actual BorgRuntime');
      record(initial, 'initial binding');
      if (!Array.isArray(ammoSlots) || read(ammoSlots, 'length') !== 3) fail('three explicit source ammo slots required');
      const slotRecords = [0, 1, 2].map(i => record(read(ammoSlots, String(i)), 'source ammo slot'));
      const cells = slotRecords.map(slot => record(read(slot, 'cell'), 'actual source WeaponCell'));
      const records = [actual, world, mapping, movement, attribute, stream, borg, ammoSlots, ...slotRecords, ...cells];
      const binding: Partial<SourceActorStatusTimersBinding> = {};
      for (const key of FLOATS) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = f(initial, key);
      for (const key of BYTES) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = b(initial, key);
      for (const key of SHORTS) if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = h(initial, key);
      let children: object | undefined;
      if (Object.getOwnPropertyDescriptor(initial, 'childPointers440') !== undefined) {
        const slots = read(initial, 'childPointers440');
        if (!Array.isArray(slots) || read(slots, 'length') !== 8) fail('eight explicit child pointer slots required');
        children = slots; Object.assign(binding, {childPointers440: slots}); records.push(slots);
      }
      if (new Set(records).size !== records.length || records.some(value => assigned.has(value) || parameterIdentities.has(value)))
        fail('source owner alias: three distinct source ammo cells and separate actor storage required');
      check(); actors.set(id, {actual, world, mapping, movement, attribute, stream, borg: actualBorg,
        binding: Object.seal(binding), slots: ammoSlots, slotRecords, cells, children});
      for (const value of records) assigned.add(value);
    });},
    getActorBinding(id: symbol) {return entry(id).binding;},
    getActualActor(id: symbol) {return entry(id).actual;},
    getWorldBinding(id: symbol) {return entry(id).world;},
    getMappingActor(id: symbol) {return entry(id).mapping;},
    getAttributeBinding(id: symbol) {return entry(id).attribute;},
    getMovementBinding(id: symbol) {return entry(id).movement;},
    getActualBorg(id: symbol) {return entry(id).borg;},
    bindGaugeResetSources(id: symbol, gauges: SourceActorGaugeScaleRuntime): void {guard(() => {
      const actor = entry(id);
      if (gaugeSources.has(id)) fail('gauge reset sources already bound');
      if (!isSourceActorGaugeScaleRuntime(gauges)) fail('gauge resets require the genuine source runtime, not callback effects');
      const method = (key: keyof SourceActorGaugeScaleRuntime) => {
        const fn = read(gauges, key);
        if (typeof fn !== 'function') fail(`${key}: own data-function required`);
        return (): unknown => {const result = Reflect.apply(fn, gauges, [id]); check(); return result;};
      };
      const bound = {actor: method('getActualActor'), borg: method('getActualBorg'), status: method('getStatusBinding'),
        down: method('resetDownGauge'), secondary: method('resetSecondaryGauge')};
      if (bound.actor() !== actor.actual || bound.borg() !== actor.borg || bound.status() !== actor.binding)
        fail('gauge reset actual actor/Borg/status owners differ');
      gaugeSources.set(id, bound);
    });},
    updateActor(id: symbol): void {guard(() => {
      const actor = entry(id), a = actor.actual, s = actor.binding, host = actor.borg;
      stable(worldActor, id, a, 'world actor');
      if ((u(a, 'controlWord') & 3) === 0) {
        const timer = f(a, 'stateTimer');
        if (timer > 0) {
          stable(mappingActor, id, actor.mapping, 'mapping');
          write(a, 'stateTimer', addSourceFloat32(timer, -f(actor.mapping, 'timestep1dc8')));
          if (f(a, 'stateTimer') <= 0) {
            write(a, 'stateTimer', 0); write(a, 'controlWord', (u(a, 'controlWord') & 0xfffffffc) >>> 0);
            write(a, 'housekeeping73f', 0);
          }
        }
      }
      for (const [owner, key] of [[s, 'field690'], [a, 'slopeMode698'], [s, 'field69c'], [s, 'field6a0'], [s, 'field6a4']] as const) {
        const timer = f(owner, key);
        if (timer > 0) {
          write(owner, key, addSourceFloat32(timer, -f(a, 'aimRateScale')));
          if (f(owner, key) < 0) write(owner, key, 0);
        }
      }
      if (b(s, 'byte6fc') !== 0) write(s, 'byte7de', 1);
      else {const count = b(s, 'byte7de'); if (count !== 0) write(s, 'byte7de', (count - 1) & 255);}
      stable(worldBinding, id, actor.world, 'world binding');
      const yaw = h(actor.world, 'yawOffset6b8');
      if (yaw !== 0) {
        if (b(actor.world, 'mode4a1') !== 0) write(actor.world, 'yawOffset6b8', 0);
        else if (b(s, 'byte71c') === 0) write(actor.world, 'yawOffset6b8', s16(yaw - 1));
      }
      for (const key of ['byte656', 'byte593', 'byte594', 'byte596'] as const) {
        const count = b(s, key); if (count !== 0) write(s, key, (count - 1) & 255);
      }
      if (h(host, 'hitDrainFrames') !== 0) fail('80055890 reached poison lifecycle handling is outside the admitted zero-poison domain');
      for (let index = 0; index < 6; index++) {
        if ((b(s, 'byte708') & (1 << index)) === 0) continue;
        stable(streams, id, actor.stream, 'stream marker709');
        const key = BYTES[9 + index]!;
        if ((b(actor.stream, 'marker709') & (1 << index)) !== 0) write(s, key, 2);
        const count = b(s, key); if (count !== 0) write(s, key, (count - 1) & 255);
      }
      stable(streams, id, actor.stream, 'stream marker709');
      const marker = b(actor.stream, 'marker709'), active = b(s, 'byte708'), inhibited = b(s, 'byte707');
      if ((marker & active & ~inhibited & 255) !== 0) fail('80055a28 reached unsupported source call 800f0104');
      stable(movementActor, id, a, 'movement actor'); stable(movementBinding, id, actor.movement, 'movement binding');
      const cls = b(actor.movement, 'byte661'), special = cls === 2 || cls === 3 || cls === 6;
      const allowed = special ? (u(a, 'controlWord') & 0x80) === 0 :
        b(stable(attributes, id, actor.attribute, 'attribute'), 'byte87') === 0;
      if (allowed) {
        const delay = h(s, 'short73a');
        if (delay !== 0) write(s, 'short73a', s16(delay - 1));
        else {
          const descriptor = parameter(id, actor), before = h(s, 'short736'), increment = h(descriptor, 'field08');
          write(s, 'short736', s16(before + increment));
          const limitDescriptor = parameter(id, actor), current = h(s, 'short736'), cap = h(limitDescriptor, 'field04');
          if (current > cap) write(s, 'short736', cap);
        }
        if (!special) write(s, 'byte747', 0);
      }
      const expire = (owner: object, key: string, effect: () => void): void => {
        const timer = f(owner, key);
        if (timer > 0) {
          write(owner, key, addSourceFloat32(timer, -f(s, 'field1dcc')));
          if (f(owner, key) <= 0) {write(owner, key, 0); effect();}
        }
      };
      if ((u(a, 'controlWord') & 0x01000000) === 0) {
        expire(host, 'balanceRefillDelay', () => {
          // Existing host gauge storage is unsigned16; source lha sign extends
          // its bits, but this sth copy preserves all sixteen bits unchanged.
          write(host, 'balanceGauge', integer(read(host, 'balanceGaugeMax'), 0, 65535, 'balanceGaugeMax'));
        });
        const resetGauge = (secondary: boolean): void => {
          const gauges = gaugeSources.get(id);
          if (!gauges) fail(secondary ? '80055ba8 reached unsupported source call 8003d444' :
            '80055b70 reached unsupported source call 8003d3e8');
          if (gauges.actor() !== a || gauges.borg() !== host || gauges.status() !== s)
            fail('gauge reset actual actor/Borg/status owners changed');
          if ((secondary ? gauges.secondary() : gauges.down()) !== undefined)
            fail('gauge reset effect must complete synchronously and return undefined');
        };
        expire(host, 'downResetDelay', () => resetGauge(false));
        expire(s, 'field7d8', () => resetGauge(true));
        expire(host, 'comboWindow', () => {write(host, 'comboAccum', 0); write(host, 'comboRank', 0);});
      }
      noLegacy720(a);
      expire(host, 'invincTimer', () => write(s, 'short272', 0));
      const children = read(s, 'childPointers440');
      if (children !== actor.children || !Array.isArray(children) || read(children, 'length') !== 8) fail('child pointer storage owner changed or is missing');
      for (let index = 0; index < 8; index++) {
        if (pointer(read(children, String(index)), 'child pointer440') !== null)
          fail('80055c38 reached child lifecycle handling is outside the admitted null-child domain');
      }
      ammo(actor);
      // 55d0c control is retained across both tests, not reloaded at 55d24.
      const control = u(a, 'controlWord');
      if ((control & 0x80000000) === 0 && b(s, 'byte7d4') !== 0) {
        if ((control & 0x02000000) === 0) {
          const cap = h(parameter(id, actor), 'field04');
          write(s, 'short738', cap); write(s, 'short736', cap); write(s, 'byte747', 0);
        } else {
          write(s, 'byte6fd', 0x26); write(s, 'byte702', 8); write(s, 'short282', -10240);
          write(s, 'short284', s16(integer(read(a, 'lockYaw'), 0, 65535, 'lockYaw') + 0x2000));
          h(s, 'short6b6');
          fail('80055d58 reached unsupported source call 8005c290');
        }
      }
      if ((integer(read(a, 'fbState'), -128, 255, 'fbState') & 255) === 1) {
        const timer = f(s, 'field8c8');
        if (timer >= 0) write(s, 'field8c8', addSourceFloat32(timer, f(s, 'field1dcc')));
      } else write(s, 'field8c8', 0);
    });},
  });
}
