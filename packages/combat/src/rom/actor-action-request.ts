/** Bounded actual8005a298, chunk_0007.c:2772–2811 and authenticated
 * archived8005a298..8005a378 instructions (read_archived_ready_lifecycle_evidence.py).
 * The optional shared10514 runtime continues zero4a1 through actual input
 * edge priority4/8/10 and canonical73c writes. Missing ingress retains the
 * original10514 boundary. The same helper supports6b450 early returns through
 * source housekeeping73f and signed73c, then refuses active target selection.
 * Nonzero4a1 refuses BEFORE loading pointer508:
 * Borg.targetLockState.activeTargetUid and matrix link4a4 do not yet share
 * an authenticated pointer identity domain. No comparison is fabricated.
 *
 * Actual statusWord5b4/housekeeping73f/slot/inputEdge5d4 and world.mode4a1
 * retain their canonical owners. Only absent7d2/73c have explicit copied
 * sealed partial cells. Wrong-owner cells and aliases are rejected by
 * descriptor presence at admission and calls, without reading their values.
 * No defaults, predicate callback, shadow pointers or tick activation.
 * Stable synchronous non-proxy own-data owners, raw bytes and unsigned32
 * words are admission bounds. Source scalar reads and writable checks are
 * reached lazily. Methods retain captured receivers; caught mutation reentry
 * poisons the enclosing call. Prior writes are never rolled back.
 */
import type {RomActor} from './actor.js';
import {isSourceActorSlotStatusRuntime,type SourceActorSlotStatusRuntime} from './actor-slot-status.js';
import type {SourceActorWorldMatrixRuntime, SourceActorWorldMatrixBinding} from './actor-world-matrix.js';

export interface SourceActorActionRequestBinding {byte7d2: number; byte73c: number}
export interface SourceActorActionRequestSources {
  world: Pick<SourceActorWorldMatrixRuntime, 'getActualActor' | 'getActorBinding'>;
  /** Optional explicit shared10514 owner, attached before first reached call. */
  slotStatus?: SourceActorSlotStatusRuntime;
}
export interface SourceActorActionRequestRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorActionRequestBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getWorldBinding(identity: symbol): SourceActorWorldMatrixBinding;
  getActorBinding(identity: symbol): Partial<SourceActorActionRequestBinding>;
  getSlotStatusRuntime(): SourceActorSlotStatusRuntime | undefined;
  /** Shallow canonical records only; no recursion through optional helper. */
  getRetainedStorageOwners(): readonly object[];
  /** Bounded6b450 early-return paths; active target selection still refuses. */
  prepareTarget(identity: symbol): void;
  updateActor(identity: symbol): void;
}
const runtimes = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceActorActionRequestRuntime(value: unknown): value is SourceActorActionRequestRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-action-request] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
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
export function createSourceActorActionRequestRuntime(sources: SourceActorActionRequestSources): SourceActorActionRequestRuntime {
  let busy = false, poisoned = false, joinedCheck: (()=>void) | undefined;
  const check = (): void => {
    if (poisoned) fail('caught same-runtime reentry');
    joinedCheck?.();
  };
  const guard = (run: () => void): void => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {run(); check();} finally {joinedCheck=undefined;busy = false;}
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
  const receiver = read(sources, 'world');
  const capture = (key: string) => {
    const method = read(receiver, key);
    if (typeof method !== 'function') fail(`world.${key}: own data-function required`);
    return (id: symbol): unknown => {const value = Reflect.apply(method, receiver, [id]); check(); return value;};
  };
  const worldActor = capture('getActualActor'), worldBinding = capture('getActorBinding');
  const byte = (r: unknown, key: string): number => integer(read(r, key), 255, key);
  const word = (r: unknown, key: string): number => integer(read(r, key), 0xffffffff, key);
  const stable = (value: unknown, expected: object, where: string): void => {
    if (value !== expected) fail(`${where}: owner changed its actual record or returned asynchronously`);
  };
  interface Entry {actual: RomActor; world: SourceActorWorldMatrixBinding; binding: Partial<SourceActorActionRequestBinding>}
  const noShadowOwners = (e: Entry): void => {
    const canonical = new Map<string, object>([
      ['byte43d',e.actual], ['statusWord5b4', e.actual], ['housekeeping73f', e.actual], ['slot', e.actual], ['inputEdge5d4', e.actual],
      ['mode4a1', e.world], ['byte7d2', e.binding], ['byte73c', e.binding],
    ]);
    const aliases = ['flags7d2', 'actionRequest73c', 'byte73f', 'word5b4', 'flags5b4',
      'word5d4', 'byte3e4', 'slot3e4', 'byte4a1','byte43D','field43d','status43d','1085'];
    for (const owner of [e.actual, e.world, e.binding]) {
      for (const [key, expected] of canonical) {
        if (owner !== expected && Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing action-request storage on another owner`);
        check();
      }
      for (const key of aliases) {
        if (Object.getOwnPropertyDescriptor(owner, key) !== undefined)
          fail(`${key}: competing action-request storage alias`);
        check();
      }
    }
  };
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>();
  const entry = (id: symbol): Entry => {
    const value = actors.get(id); if (!value) fail('unknown/non-owned action-request actor'); return value;
  };
  let slotOwner: SourceActorSlotStatusRuntime | undefined;
  const slotRuntime=(): SourceActorSlotStatusRuntime | undefined=>{
    const present=Object.getOwnPropertyDescriptor(sources,'slotStatus');check();
    if(present===undefined) {if(slotOwner) fail('slotStatus: canonical owner removed');return undefined;}
    const selected=read(sources,'slotStatus');
    if(!isSourceActorSlotStatusRuntime(selected)) fail('slotStatus: genuine source helper required');
    if(slotOwner && slotOwner!==selected) fail('slotStatus: canonical owner changed');
    slotOwner=selected;return selected;
  };
  const readSlotStatus=(e: Entry,id: symbol,slot: number,site: string): number=>{
    const helper=slotRuntime();
    if(helper===undefined) fail(`${site} reached unsupported source call 80010514(slot=${slot}); later action stores have not executed`);
    const scheduler=helper.getSchedulerRuntime(),spawns=scheduler.getRootRuntime().getSpawnRuntime();
    if(spawns.getAdmissionRuntime().getActionRuntime()!==runtime ||
      scheduler.getAllocatorRuntime().getActualActor(id)!==e.actual ||
      spawns.getAdmissionRuntime().getActualActor(id)!==e.actual)
      fail('slotStatus: exact scheduler/action/actual actor graph required');
    if(helper.getRetainedStorageOwners().some(owner=>[sources,e.actual,e.world,e.binding].includes(owner)))
      fail('slotStatus: source storage aliases action owners');
    // Read-only metadata getters remain available after graph closure. They
    // must not let this newly continued action path mutate73c afterward.
    const allocator=scheduler.getAllocatorRuntime();
    // Continue checking the joined graph after every later own-data access,
    // including inputEdge and destination preflight, until this guard exits.
    joinedCheck=()=>allocator.assertActorComplete(id);
    allocator.assertActorComplete(id);check();
    const value=helper.readSlot(slot);check();
    allocator.assertActorComplete(id);check();return value;
  };
  const runtime: SourceActorActionRequestRuntime = {
    bindActor(id, initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(worldActor(id), 'world actor') as RomActor;
      if (claimedActors.has(actual)) fail('actual actor already claimed by a source action-request runtime');
      const world = record(worldBinding(id), 'world binding') as SourceActorWorldMatrixBinding;
      const owners = [actual, world];
      if (new Set(owners).size !== owners.length || owners.some(owner => assigned.has(owner)))
        fail('source owner alias: distinct actual actor/world required');
      record(initial, 'initial action-request binding');
      const binding: Partial<SourceActorActionRequestBinding> = {};
      const e: Entry = {actual, world, binding};
      noShadowOwners(e);
      // The copied input can seed only the absent cells, never a shadow of
      // a retained canonical owner or an alternative spelling of that cell.
      noShadowOwners({...e, binding: initial});
      for (const key of ['byte7d2', 'byte73c'] as const)
        if (Object.getOwnPropertyDescriptor(initial, key) !== undefined) binding[key] = byte(initial, key);
      Object.seal(binding); check(); actors.set(id, e);
      [...owners, binding].forEach(owner => assigned.add(owner)); claimedActors.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},
    getWorldBinding(id) {return entry(id).world;},
    getActorBinding(id) {return entry(id).binding;},
    getSlotStatusRuntime() {return slotRuntime();},
    getRetainedStorageOwners() {return Object.freeze([sources,receiver as object,...[...actors.values()].flatMap(e=>[e.actual,e.world,e.binding])]);},
    prepareTarget(id) {guard(()=>{
      const e=entry(id),{actual,binding}=e;
      stable(worldActor(id),actual,'world actor');noShadowOwners(e);
      const slot=byte(actual,'slot')<<24>>24;
      if(readSlotStatus(e,id,slot,'8006b474')!==0) return;
      if(byte(actual,'housekeeping73f')!==0) return;
      const request=byte(binding,'byte73c')<<24>>24;
      if(request<=1) return;
      if(request===4) fail('8006b4f4 reached unsupported target pointer6e0 load');
      if(request===5) fail('8006b4c0 reached unsupported target pointer508 load before6e0 store');
      if(request===2 || request===3) fail('8006b544 reached unsupported target selector byte73d load');
      fail('8006b544 reached unsupported target selector saved-register state');
    });},
    updateActor(id) {guard(() => {
      const e = entry(id), {actual, world, binding} = e;
      stable(worldActor(id), actual, 'world actor'); noShadowOwners(e);
      if ((byte(binding, 'byte7d2') & 3) === 1) {
        if ((word(actual, 'statusWord5b4') & 0x10) === 0) write(binding, 'byte73c', 4);
        return;
      }
      // lbz/extsb zero comparisons are equivalent over admitted raw bytes.
      if (byte(actual, 'housekeeping73f') !== 0) return;
      if (byte(binding, 'byte73c') !== 0) return;
      stable(worldBinding(id), world, 'world binding');
      if (byte(world, 'mode4a1') === 0) {
        const slot = byte(actual, 'slot') << 24 >> 24;
        if(readSlotStatus(e,id,slot,'8005a300')!==0) return;
        const edges=word(actual,'inputEdge5d4');
        if((edges&4)!==0) write(binding,'byte73c',2);
        else if((edges&8)!==0) write(binding,'byte73c',3);
        else if((edges&0x10)!==0) write(binding,'byte73c',5);
        return;
      }
      fail('8005a34c reached unsupported source pointer508 load; actual target508 and link4a4 identities are unreconciled, later4a4 load/comparison/store have not executed');
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
