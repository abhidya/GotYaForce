/** Actual8008ac80 over the completed projectile's canonical allocation bytes.
 * Owner27c/3fc are explicit previously missing source pointer fields, not copies
 * of a legacy combat hit object. Their data remains registered by identity.
 * Interior table/matrix pointers retain base+offset; registration never reads or
 * fabricates a matrix, damage table body, shape evaluation or future8a65c call.
 * No scheduler or failed-frame continuation is provided. Partial effects close
 * the shared parent/allocator permanently. Synchronous non-proxy storage only.
 */
import {isSourceActorProjectileSpawnRuntime, markIncompleteSourceActorProjectileSpawn,
  type SourceActorProjectileSpawnRuntime} from './actor-projectile-spawn.js';
import {isSourceActorDoubleFrameClaimed} from './actor-double-prehook.js';
import type {SourceAllocationBytes} from './source-object-allocation.js';
import type {RomActor} from './actor.js';

export interface SourceProjectileHitOwnerBinding {
  pointer27c: object | null;
  pointer3fc: SourceAllocationBytes | null;
}
export interface SourceProjectileHitRuntime {
  bindActor(identity: symbol, binding: Partial<SourceProjectileHitOwnerBinding>): void;
  getActorBinding(identity: symbol): Partial<SourceProjectileHitOwnerBinding>;
  getActualActor(identity: symbol): RomActor;
  getSpawnRuntime(): SourceActorProjectileSpawnRuntime;
  registerHit(projectile: symbol, kind: number): 0 | 1;
}
const runtimes = new WeakSet<object>(), claimedBindings = new WeakSet<object>(), claimedActors = new WeakSet<object>();
export function isSourceProjectileHitRuntime(value: unknown): value is SourceProjectileHitRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[projectile-hit-registration] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data owner required`);
  const p = Object.getOwnPropertyDescriptor(owner,key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: source integer required`);
  return value === 0 ? 0 : value;
}
export function createSourceProjectileHitRuntime(spawns: SourceActorProjectileSpawnRuntime): SourceProjectileHitRuntime {
  if (!isSourceActorProjectileSpawnRuntime(spawns)) fail('genuine spawn runtime required');
  const allocator = spawns.getAllocatorRuntime();
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const call = <T>(run: () => T): T => {const value = run(); check(); return value;};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown,key: string): unknown => {const value = own(owner,key); check(); return value;};
  interface Entry {actual: RomActor; binding: Partial<SourceProjectileHitOwnerBinding>; incomplete: boolean}
  const actors = new Map<symbol,Entry>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown HIT owner'); return e;};
  const owners = (id: symbol,e: Entry): void => {
    if (e.incomplete) fail('known incomplete HIT owner');
    call(() => spawns.assertActorComplete(id));
    if (call(() => spawns.getActualActor(id)) !== e.actual) fail('actual HIT owner changed');
    for (const r of call(() => spawns.getSourceOwners(id))) {
      for (const key of ['pointer27c','pointer3fc','damageTable27c','hitTable3fc']) {
        if (Object.getOwnPropertyDescriptor(r,key) !== undefined) fail(`${key}: competing source pointer storage`); check();
      }
    }
  };
  const sourcePointer = (e: Entry,key: 'pointer27c' | 'pointer3fc'): symbol | null => {
    const value = read(e.binding,key);
    if (value === null) return null;
    if (typeof value !== 'object') fail(`${key}: explicit source pointer owner required`);
    return call(() => allocator.getPointerIdentity(value));
  };
  const byteAt = (base: symbol | null,offset: number): number => {
    if (base === null) fail('null source3fc at reached HIT data dereference');
    integer(offset,0,0xffff,'HIT byte offset');
    const bytes = call(() => allocator.getPointerTarget(base));
    return integer(read(bytes,String(offset)),0,255,`HIT byte${offset.toString(16)}`);
  };
  const halfAt = (base: symbol | null,offset: number): number => byteAt(base,offset)*256+byteAt(base,offset+1);
  const pointer = (id:symbol,off:number):symbol|null => call(() => allocator.readPointer(id,off));
  const byte = (id:symbol,off:number):number => call(() => allocator.readU8(id,off));
  const put8 = (id:symbol,off:number,value:number):void => {call(() => allocator.writeU8(id,off,value));};
  const put16 = (id:symbol,off:number,value:number):void => {call(() => allocator.writeU16(id,off,value));};
  const put32 = (id:symbol,off:number,value:number):void => {call(() => allocator.writeU32(id,off,value));};
  const putPointer = (id:symbol,off:number,value:symbol|null):void => {call(() => allocator.writePointer(id,off,value));};
  const interior = (base:symbol|null,offset:number):symbol => {
    if (base === null) fail('null source base at reached interior pointer');
    return call(() => allocator.getInteriorPointer(base,offset));
  };
  const runtime: SourceProjectileHitRuntime = {
    bindActor(id,binding) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new HIT owner identity required');
      if (binding === null || typeof binding !== 'object' || Array.isArray(binding) || ArrayBuffer.isView(binding) || binding instanceof Promise)
        fail('explicit synchronous HIT pointer binding required');
      if (claimedBindings.has(binding) || spawns.getSourceOwners(id).includes(binding)) fail('HIT pointer binding already claimed or aliases source owner');
      for (const key of Reflect.ownKeys(binding)) if (key !== 'pointer27c' && key !== 'pointer3fc') fail(`${String(key)}: not missing HIT pointer storage`);
      const e = {actual:call(() => spawns.getActualActor(id)),binding,incomplete:false};
      if (claimedActors.has(e.actual)) fail('actual actor already claimed by HIT pointer owner');
      owners(id,e);actors.set(id,e);claimedBindings.add(binding);claimedActors.add(e.actual);
    });},
    getActorBinding(id) {return entry(id).binding;}, getActualActor(id) {return entry(id).actual;}, getSpawnRuntime() {return spawns;},
    registerHit(child,kind) {return guard(() => {
      const origin = call(() => spawns.getSpawnOwnerIdentity(child)),e = entry(origin);
      if (isSourceActorDoubleFrameClaimed(e.actual)) fail('frame-owned actor requires its unimplemented later source object scheduler');
      try {
        owners(origin,e); integer(kind,-0x80000000,0x7fffffff,'kind register');
        const parent = pointer(child,0x90);
        if (parent === null) return 0;
        if (parent !== origin || call(() => allocator.getPointerTarget(parent)) !== e.actual) fail('pointer90 outside genuine original main-actor domain');
        putPointer(child,0x27c,sourcePointer(e,'pointer27c'));
        const table = sourcePointer(e,'pointer3fc');
        let cursor = 0xa20 + Math.imul(kind,4), count = 0, result:0|1 = 0;
        while (true) {
          // Source reloads/sign-tests the next remap BEFORE count<4, including
          // the fifth byte after four attempts. Never eager-read four entries.
          if ((byteAt(table,cursor)<<24>>24) < 0 || count >= 4) break;
          const hit = call(() => spawns.allocateProjectileHit(child));
          if (hit !== null) {
            put8(hit,0,1);put32(hit,0xc,0x8008a65c);putPointer(hit,0x20,child);put8(hit,0x14,kind&255);
            const owner = pointer(child,0x90);
            putPointer(hit,0x24,owner === null ? pointer(child,0x8c) : owner);
            const row = 0xaa0 + (byteAt(table,cursor)<<24>>24)*0x50;
            putPointer(hit,0x28,interior(table,row));
            if (byte(child,0x83) === 0) {
              const bone = byteAt(table,row+1);
              putPointer(hit,0x60,interior(child,(bone&0x80) === 0 ? 0x8d4+bone*0x30 : 0x1aa4));
              // Exact byte order and sign arithmetic are checked against the
              // instruction schedule in projectile-hit-evidence-2026-11-14.md.
              const group = call(() => allocator.readS8(child,0x1cec));
              const action = call(() => allocator.readS8(child,0x1ced));
              put16(hit,0x4c,(action+group*0x1000)&65535);
            } else putPointer(hit,0x60,interior(child,0x114));
            putPointer(hit,0x5c,hit);result=1;
            putPointer(hit,0x2c,pointer(child,0x27c));
            put8(hit,0x11,halfAt(table,row+4)&255);
            put16(hit,0x48,halfAt(table,row+6));put16(hit,0x4a,halfAt(table,row+8));
            put8(child,0x86,1);put8(child,0x1d8,0);
            put8(hit,0x12,byteAt(table,cursor));
          }
          cursor++;count++;
        }
        return result;
      } catch(error) {e.incomplete=true;markIncompleteSourceActorProjectileSpawn(spawns,origin);throw error;}
    });},
  };
  runtimes.add(runtime);return Object.freeze(runtime);
}
