/** Genuine80010514 over the SAME live803c4e84 owner as the scheduler.
 * New slot records represent803c73b0 + slot*3e4; state18 is the byte at+18.
 * Explicit current bytes only, not a source constructor/default initializer.
 * Reads state18, live slot pointer, actual43d, then the reached switch word.
 * This read-only helper grants no scheduler/frame/epoch execution capability.
 * Six live actor slots and13 source player records are bounded host domains.
 * Stable synchronous non-proxy own-data records are required; identity checks
 * are metadata admission, not source scalar reads. No successful callback,
 * copied target list, cached pointer target or implicit dispatch word is used.
 */
import {isSourceObjectSchedulerRuntime,type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
export interface SourceActorPlayerSlotRecord {state18?: number}
export interface SourceActorSlotStatusSources {
  scheduler: SourceObjectSchedulerRuntime;
  slotRecords?: Readonly<Record<number,SourceActorPlayerSlotRecord>>;
  /** Explicit source802c3938 words, checked against authenticated local blocks. */
  dispatch3938?: Readonly<Record<number,number>>;
}
export interface SourceActorSlotStatusRuntime {
  getSchedulerRuntime(): SourceObjectSchedulerRuntime;
  /** Direct helper owners only. Never recurse through scheduler inventory. */
  getRetainedStorageOwners(): readonly object[];
  readSlot(slot: number): number;
}
const runtimes=new WeakSet<object>(),claims=new WeakMap<object,SourceActorSlotStatusRuntime>(),
  storageClaims=new WeakMap<object,SourceActorSlotStatusRuntime>();
export function isSourceActorSlotStatusRuntime(value: unknown): value is SourceActorSlotStatusRuntime {
  return value!==null && typeof value==='object' && runtimes.has(value);
}
function fail(reason: string): never {throw Error(`[actor-slot-status] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(value: unknown,key: string): unknown {
  if(value===null || typeof value!=='object') fail(`${key}: own data record required`);
  const p=Object.getOwnPropertyDescriptor(value,key);
  if(!p || !('value' in p)) fail(`${key}: own data property required`);return p.value;
}
function record(value: unknown,where: string): object {
  if(value===null || typeof value!=='object' || value instanceof Promise || ArrayBuffer.isView(value))
    fail(`${where}: synchronous own-data record required`);return value;
}
function uint(value: unknown,max: number,where: string): number {
  if(typeof value!=='number' || !Number.isInteger(value) || value<0 || value>max) fail(`${where}: raw unsigned integer required`);
  return value===0?0:value;
}
// Forty bytes authenticated in both snapshots after a separately frozen scope.
const TARGETS: readonly number[]=Object.freeze([0x800105ac,0x800105ac,0x80010570,0x80010578,
  0x80010580,0x80010588,0x80010590,0x80010598,0x800105a0,0x800105a8]);
export function createSourceActorSlotStatusRuntime(sources: SourceActorSlotStatusSources): SourceActorSlotStatusRuntime {
  const scheduler=own(sources,'scheduler');
  if(!isSourceObjectSchedulerRuntime(scheduler)) fail('genuine scheduler required');
  if(claims.has(scheduler)) fail('scheduler already has a canonical slot-status owner');
  const root=scheduler.getRootRuntime(),spawns=root.getSpawnRuntime(),allocator=scheduler.getAllocatorRuntime(),
    action=spawns.getAdmissionRuntime().getActionRuntime();
  let busy=false,poisoned=false,tableOwner: object|undefined;
  const retained=new Map<string,object>();
  const check=(): void=>{if(poisoned) fail('caught same-runtime reentry');};
  const read=(owner: unknown,key: string): unknown=>{const value=own(owner,key);check();return value;};
  const call=<T>(run: ()=>T): T=>{const value=run();check();return value;};
  const noShadows=(owner: object,keys: readonly string[]): void=>{
    for(const key of keys) {const p=Object.getOwnPropertyDescriptor(owner,key);check();if(p!==undefined) fail(`${key}: competing source cell owner`);}
  };
  const forbidden=(): readonly object[]=>[sources,scheduler,root,spawns,allocator,
    ...call(()=>scheduler.getRetainedStorageOwners()),...call(()=>action.getRetainedStorageOwners())];
  const retain=(name: string,value: unknown): object=>{
    const selected=record(value,name),old=retained.get(name);
    if(old && old!==selected) fail(`${name}: canonical owner changed`);
    if(selected===tableOwner || forbidden().includes(selected) ||
      [...retained].some(([key,owner])=>key!==name && owner===selected)) fail(`${name}: source storage alias`);
    const claim=storageClaims.get(selected);if(claim && claim!==runtime) fail(`${name}: storage already claimed`);
    retained.set(name,selected);storageClaims.set(selected,runtime);return selected;
  };
  const runtime: SourceActorSlotStatusRuntime={
    getSchedulerRuntime() {return scheduler;},
    getRetainedStorageOwners() {return Object.freeze([sources,...retained.values()]);},
    readSlot(slot) {
      if(busy) {poisoned=true;fail('same-runtime reentry unsupported');}
      busy=true;poisoned=false;
      try {
        if(read(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
          root.getSpawnRuntime()!==spawns || scheduler.getAllocatorRuntime()!==allocator ||
          spawns.getAdmissionRuntime().getActionRuntime()!==action) fail('canonical scheduler graph changed');
        if(!Number.isInteger(slot) || slot<0 || slot>=13) fail('reached player slot outside bounded13-record owner');
        const rows=retain('slotRecords',read(sources,'slotRecords')),
          row=retain(`slotRecord${slot}`,read(rows,String(slot)));
        noShadows(row,['byte0','byte18','status18','24']);
        const state=uint(read(row,'state18'),255,'state18');
        const high=state===2?0x80000000:0;
        // The high flag never returns early: the source always reaches43d.
        const table=record(call(()=>scheduler.getActorSlotTable()),'same803c4e84');
        if(tableOwner && tableOwner!==table) fail('canonical actor slot table changed');
        if(table===sources || [...retained.values()].includes(table)) fail('actor slot table aliases status storage');
        tableOwner=table;
        if(slot>=6) fail('reached actor slot outside bounded six-word table');
        const id=read(table,String(slot));
        if(typeof id!=='symbol') fail('nonnull source actor slot pointer required');
        if(call(()=>allocator.getInteriorAddress(id))!==null) fail('source actor slot requires a base identity');
        const actor=record(call(()=>allocator.getPointerTarget(id)),'selected actual actor');
        if([...retained.values()].includes(actor)) fail('selected actor aliases status storage');
        noShadows(actor,['byte43D','field43d','field43D','status43d','mode43d','1085']);
        const selected=uint(read(actor,'byte43d'),255,'byte43d')&0x7f;
        if(selected>9) return high;
        const dispatch=retain('dispatch3938',read(sources,'dispatch3938'));
        const target=uint(read(dispatch,String(selected)),0xffffffff,'dispatch3938 word');
        if(target!==TARGETS[selected]) fail('dispatch3938 differs from authenticated target');
        const masks: Readonly<Record<number,number>>={0x80010570:1,0x80010578:2,0x80010580:4,
          0x80010588:8,0x80010590:16,0x80010598:32,0x800105a0:64,0x800105a8:128,0x800105ac:0};
        if(!Object.hasOwn(masks,target)) fail('unsupported10514 local target');
        return (high|masks[target]!)>>>0;
      } finally {busy=false;}
    },
  };
  runtimes.add(runtime);claims.set(scheduler,runtime);return Object.freeze(runtime);
}
