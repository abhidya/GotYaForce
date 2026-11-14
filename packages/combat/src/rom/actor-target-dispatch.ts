/** Bounded genuine8006b7f4 over the retained scheduler/admission graph.
 * Inactive stores are byte502, word508, word504 in that order. Pointer words
 * use the EXISTING admission cells: no byte aliases or second pointer domain.
 * Active signed502 indexes source802d39a0 without a source range guard. Only
 * authenticated entry0 is admitted by this host; no table extent is inferred.
 * Entry0 selects genuine6b850, whose nonzero73f branch returns unchanged.
 * Zero73f reads explicit candidate count before clearing the shared scratch
 * count. Zero candidates return; nonzero stops before the first list load. All source
 * data is explicit and live; there are no defaults, callbacks or scheduler
 * capabilities. Stable synchronous non-proxy own-data records are host bounds.
 */
import {claimSourceHelperStorage} from './source-storage-claims.js';
import {isSourceObjectSchedulerRuntime,type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
export interface SourceActorTargetDispatchSources {
  scheduler: SourceObjectSchedulerRuntime;
  /** Exactly the independently authenticated cell802d39a0, not a table size. */
  dispatch39a0?: Readonly<Record<number,number>>;
  /** Shared explicit globals; half count, then word scratch count. No defaults. */
  candidateGlobals?: {half80436242?: number; count804361a0?: number};
}
export interface SourceActorTargetDispatchRuntime {
  getSchedulerRuntime(): SourceObjectSchedulerRuntime;
  /** Direct sources and reached table only; no recursive scheduler inventory. */
  getRetainedStorageOwners(): readonly object[];
  dispatchActor(identity: symbol): void;
}
const runtimes=new WeakSet<object>(),claims=new WeakMap<object,SourceActorTargetDispatchRuntime>();
export function isSourceActorTargetDispatchRuntime(value: unknown): value is SourceActorTargetDispatchRuntime {
  return value!==null && typeof value==='object' && runtimes.has(value);
}
function fail(reason: string): never {throw Error(`[actor-target-dispatch] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(owner: unknown,key: string,writable=false): unknown {
  if(owner===null || typeof owner!=='object') fail(`${key}: own data record required`);
  const p=Object.getOwnPropertyDescriptor(owner,key);
  if(!p || !('value' in p)) fail(`${key}: own data property required`);
  if(writable && !p.writable) fail(`${key}: non-writable field`);
  return p.value;
}
function record(value: unknown,where: string): object {
  if(value===null || typeof value!=='object' || value instanceof Promise || ArrayBuffer.isView(value))
    fail(`${where}: synchronous own-data record required`);return value;
}
function uint(value: unknown,max: number,where: string): number {
  if(typeof value!=='number' || !Number.isInteger(value) || value<0 || value>max)
    fail(`${where}: raw unsigned source integer required`);return value===0?0:value;
}
export function createSourceActorTargetDispatchRuntime(sources: SourceActorTargetDispatchSources): SourceActorTargetDispatchRuntime {
  const scheduler=own(sources,'scheduler');
  if(!isSourceObjectSchedulerRuntime(scheduler)) fail('genuine scheduler required');
  if(claims.has(scheduler)) fail('scheduler already has a canonical target-dispatch owner');
  const root=scheduler.getRootRuntime(),spawns=root.getSpawnRuntime(),allocator=scheduler.getAllocatorRuntime(),
    admission=spawns.getAdmissionRuntime(),action=admission.getActionRuntime();
  let busy=false,poisoned=false,activeId: symbol|undefined,tableOwner: object|undefined,globalsOwner: object|undefined;
  const bindings=new Map<symbol,object>();
  const check=(): void=>{
    if(poisoned) fail('caught same-runtime reentry');
    if(activeId!==undefined) allocator.assertActorComplete(activeId);
  };
  const read=(owner: unknown,key: string): unknown=>{const value=own(owner,key);check();return value;};
  const write=(owner: object,key: string,value: number|null): void=>{
    own(owner,key,true);check();(owner as Record<string,unknown>)[key]=value;check();
  };
  const call=<T>(run: ()=>T): T=>{const result=run();check();return result;};
  const byte=(owner: object,key: string): number=>uint(read(owner,key),255,key);
  const noShadows=(owner: object,keys: readonly string[]): void=>{
    for(const key of keys) {const p=Object.getOwnPropertyDescriptor(owner,key);check();if(p!==undefined) fail(`${key}: competing source cell owner`);}
  };
  const forbidden=(): readonly object[]=>[sources,scheduler,root,spawns,allocator,admission,action,
    ...call(()=>scheduler.getRetainedStorageOwners()),...call(()=>action.getRetainedStorageOwners()),...bindings.values(),
    ...(call(()=>action.getSlotStatusRuntime())?.getRetainedStorageOwners()??[]),
    ...(call(()=>action.getSlotStatusRuntime())?.getDeclaredStorageOwners()??[])];
  const dispatchTable=(): object=>{
    const table=record(read(sources,'dispatch39a0'),'dispatch39a0');
    if(tableOwner && tableOwner!==table) fail('dispatch39a0: canonical owner changed');
    if(table===globalsOwner || forbidden().includes(table)) fail('dispatch39a0: source storage alias');
    if(!claimSourceHelperStorage(table,runtime)) fail('dispatch39a0: storage already claimed');
    noShadows(table,['active0','byte502','pointer504','pointer508','housekeeping73f']);
    tableOwner=table;return table;
  };
  const runtime: SourceActorTargetDispatchRuntime={
    getSchedulerRuntime() {return scheduler;},
    getRetainedStorageOwners() {return Object.freeze([sources,...(tableOwner?[tableOwner]:[]),...(globalsOwner?[globalsOwner]:[])]);},
    dispatchActor(id) {
      if(busy) {poisoned=true;fail('same-runtime reentry unsupported');}
      busy=true;poisoned=false;let actual: object|undefined;
      try {
        actual=record(allocator.getActualActor(id),'actual actor');activeId=id;check();
        if(read(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
          root.getSpawnRuntime()!==spawns || scheduler.getAllocatorRuntime()!==allocator ||
          spawns.getAdmissionRuntime()!==admission || admission.getActionRuntime()!==action ||
          call(()=>admission.getActualActor(id))!==actual || call(()=>action.getActualActor(id))!==actual)
          fail('canonical scheduler/admission/actor graph changed');
        if(call(()=>scheduler.getRetainedStorageOwners()).includes(sources) ||
          call(()=>action.getRetainedStorageOwners()).includes(sources) ||
          (call(()=>action.getSlotStatusRuntime())?.getDeclaredStorageOwners()??[]).includes(sources))
          fail('target-dispatch sources alias canonical storage');
        const binding=record(call(()=>admission.getActorBinding(id)),'canonical pointer binding'),old=bindings.get(id);
        if(old && old!==binding) fail('canonical pointer owner changed');
        if(binding===actual || binding===sources || binding===tableOwner || binding===globalsOwner || actual===sources || actual===tableOwner || actual===globalsOwner)
          fail('canonical source storage alias');
        bindings.set(id,binding);
        const owners=[actual,binding,call(()=>admission.getWorldBinding(id)),call(()=>admission.getStatusBinding(id)),
          call(()=>admission.getMappingActor(id)),call(()=>admission.getAttributeBinding(id)),
          call(()=>admission.getChargeBinding(id)),call(()=>admission.getActionBinding(id)),
          call(()=>admission.getCueBinding(id)),call(()=>admission.getDispatchBinding(id)),
          call(()=>admission.getStartBinding(id)),call(()=>admission.getStreamBinding(id))];
        for(const owner of owners) {
          if(owner!==actual) noShadows(owner,['active0','byte502','housekeeping73f']);
          if(owner!==binding) noShadows(owner,['pointer504','pointer508']);
          noShadows(owner,['state502','targetState502','field502','1282','field504','field508',
            'byte504','byte505','byte506','byte507','byte508','byte509','byte50a','byte50b','byte50A','byte50B',
            '1284','1285','1286','1287','1288','1289','1290','1291']);
        }
        // The source loads no previous destination value on this branch.
        if(byte(actual,'active0')===0) {
          write(actual,'byte502',0);write(binding,'pointer508',null);write(binding,'pointer504',null);return;
        }
        const state=byte(actual,'byte502')<<24>>24;
        if(state!==0) fail(`8006b834 signed target index ${state} outside authenticated entry0 host bound`);
        const table=dispatchTable(),target=uint(read(table,'0'),0xffffffff,'dispatch39a0 word');
        if(target!==0x8006b850) fail('dispatch39a0 entry0 differs from authenticated8006b850 target');
        if(byte(actual,'housekeeping73f')!==0) return;
        const globals=record(read(sources,'candidateGlobals'),'candidateGlobals');
        if(globalsOwner && globalsOwner!==globals) fail('candidateGlobals: canonical owner changed');
        if(globals===tableOwner || forbidden().includes(globals)) fail('candidateGlobals: source storage alias');
        if(!claimSourceHelperStorage(globals,runtime)) fail('candidateGlobals: storage already claimed');
        noShadows(globals,['active0','byte502','pointer504','pointer508','housekeeping73f','byte80436242','word80436242']);
        globalsOwner=globals;
        const count=uint(read(globals,'half80436242'),65535,'half80436242');
        write(globals,'count804361a0',0);
        if(count!==0) fail('8006b898 reached unsupported candidate list803c1d7c load');
        if(uint(read(globals,'count804361a0'),0xffffffff,'count804361a0')===0) return;
        fail('8006b924 reached unsupported candidate-positive source path');
      } catch(error) {if(actual) markIncompleteSourceActorDoubleLifecycle(actual);throw error;}
      finally {activeId=undefined;busy=false;}
    },
  };
  if(!claimSourceHelperStorage(sources,runtime)) fail('target-dispatch sources storage already claimed');
  runtimes.add(runtime);claims.set(scheduler,runtime);return Object.freeze(runtime);
}
