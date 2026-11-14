/** Bounded genuine8006b7f4 over the retained scheduler/admission graph.
 * Inactive stores are byte502, word508, word504 in that order. Pointer words
 * use the EXISTING admission cells: no byte aliases or second pointer domain.
 * Active signed502 indexes source802d39a0 without a source range guard. Only
 * authenticated entry0 is admitted by this host; no table extent is inferred.
 * Entry0 selects genuine6b850, whose nonzero73f branch returns unchanged.
 * Zero73f reads explicit candidate count before clearing the shared scratch
 * count. Positive lists use the same allocator object/actor pointers and stage
 * lifecycle owners. Rejected lists return; accepted candidates preserve ordered
 * scratch count/list stores before the descriptor4b0 boundary. All source
 * data is explicit and live; there are no defaults, callbacks or scheduler
 * capabilities. Stable synchronous non-proxy own-data records are host bounds.
 */
import {claimSourceHelperStorage} from './source-storage-claims.js';
import {isSourceObjectSchedulerRuntime,type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {markIncompleteSourceActorDoubleLifecycle,requireCompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
export interface SourceActorTargetDispatchSources {
  scheduler: SourceObjectSchedulerRuntime;
  /** Exactly the independently authenticated cell802d39a0, not a table size. */
  dispatch39a0?: Readonly<Record<number,number>>;
  /** Shared explicit globals; half count, then word scratch count. No defaults. */
  candidateGlobals?: {half80436242?: number; count804361a0?: number};
  /** Actual803c1d7c list and803b2208 scratch list, not target snapshots. */
  candidateList1d7c?: Readonly<Record<number,symbol|null>>;
  scratchCandidates2208?: Record<number,symbol|null>;
}
export interface SourceActorTargetDispatchRuntime {
  getSchedulerRuntime(): SourceObjectSchedulerRuntime;
  /** Direct sources and reached table/globals/lists; no recursive graph inventory. */
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
  const root=scheduler.getRootRuntime(),spawns=root.getSpawnRuntime(),allocator=scheduler.getAllocatorRuntime(),stage=root.getStageRuntime(),
    admission=spawns.getAdmissionRuntime(),action=admission.getActionRuntime();
  let busy=false,poisoned=false,activeId: symbol|undefined,activeCandidate: object|undefined,tableOwner: object|undefined,globalsOwner: object|undefined;
  const bindings=new Map<symbol,object>(),lists=new Map<string,object>(),candidateStages=new Map<symbol,object>();
  const check=(): void=>{
    if(poisoned) fail('caught same-runtime reentry');
    if(activeId!==undefined) allocator.assertActorComplete(activeId);
    if(activeCandidate!==undefined) requireCompleteSourceActorDoubleLifecycle(activeCandidate);
  };
  const read=(owner: unknown,key: string): unknown=>{const value=own(owner,key);check();return value;};
  const write=(owner: object,key: string,value: number|symbol|null): void=>{
    own(owner,key,true);check();(owner as Record<string,unknown>)[key]=value;check();
  };
  const call=<T>(run: ()=>T): T=>{const result=run();check();return result;};
  const byte=(owner: object,key: string): number=>uint(read(owner,key),255,key);
  const noShadows=(owner: object,keys: readonly string[]): void=>{
    for(const key of keys) {const p=Object.getOwnPropertyDescriptor(owner,key);check();if(p!==undefined) fail(`${key}: competing source cell owner`);}
  };
  const forbidden=(): readonly object[]=>[sources,scheduler,root,spawns,allocator,admission,action,
    ...call(()=>scheduler.getRetainedStorageOwners()),
    ...call(()=>spawns.getPrehookRuntime().getStatusRuntime().getRetainedStorageOwners()),
    ...call(()=>action.getRetainedStorageOwners()),...bindings.values(),...candidateStages.values(),
    ...(call(()=>action.getSlotStatusRuntime())?.getRetainedStorageOwners()??[]),
    ...(call(()=>action.getSlotStatusRuntime())?.getDeclaredStorageOwners()??[])];
  const dispatchTable=(): object=>{
    const table=record(read(sources,'dispatch39a0'),'dispatch39a0');
    if(tableOwner && tableOwner!==table) fail('dispatch39a0: canonical owner changed');
    if(table===globalsOwner || [...lists.values()].includes(table) || forbidden().includes(table)) fail('dispatch39a0: source storage alias');
    if(!claimSourceHelperStorage(table,runtime)) fail('dispatch39a0: storage already claimed');
    noShadows(table,['active0','byte502','pointer504','pointer508','housekeeping73f']);
    tableOwner=table;return table;
  };
  const list=(name: 'candidateList1d7c'|'scratchCandidates2208'): object=>{
    const selected=record(read(sources,name),name),old=lists.get(name);
    if(old && old!==selected) fail(`${name}: canonical owner changed`);
    if(selected===tableOwner || selected===globalsOwner || forbidden().includes(selected) ||
      [...lists].some(([key,value])=>key!==name && value===selected)) fail(`${name}: source storage alias`);
    if(!claimSourceHelperStorage(selected,runtime)) fail(`${name}: storage already claimed`);
    noShadows(selected,['active0','team','byte502','pointer504','pointer508','housekeeping73f','lifecycle18',
      'half80436242','count804361a0']);
    lists.set(name,selected);return selected;
  };
  const scan=(actual: object,count: number,globals: object): void=>{
    if(count===0) return;
    // Missing optional ingress preserves the previous precisely reached site.
    const present=Object.getOwnPropertyDescriptor(sources,'candidateList1d7c');check();
    if(present===undefined) fail('8006b898 reached unsupported candidate list803c1d7c load');
    const candidates=list('candidateList1d7c');
    for(let index=0;index<count;index++) {
      activeCandidate=undefined;check();
      if(index>=4096) fail('8006b898 candidate scan host visit bound4096 reached');
      if(list('candidateList1d7c')!==candidates) fail('candidate list canonical owner changed');
      const object=read(candidates,String(index));
      if(object===null) continue;
      if(typeof object!=='symbol') fail('candidate list: source pointer identity required');
      // A source object record is not a copied actor or legacy HIT object.
      // The same registered BE bytes and pointer encoding are used here.
      call(()=>allocator.getObject(object));
      const pointer=call(()=>allocator.readPointer(object,0x20));
      if(pointer===null) continue;
      if(call(()=>allocator.getInteriorAddress(pointer))!==null) fail('candidate actor requires base identity');
      const candidate=record(call(()=>allocator.getPointerTarget(pointer)),'candidate actual actor');
      activeCandidate=candidate;check();
      if(candidate===sources || candidate===tableOwner || candidate===globalsOwner ||
        [...lists.values()].includes(candidate)) fail('candidate actor source storage alias');
      noShadows(candidate,['team88','byte88','field88','136','lifecycle18','byte18','state18','24']);
      if(byte(candidate,'active0')===0) continue;
      if(candidate===actual) continue;
      const callerTeam=byte(actual,'team')<<24>>24,candidateTeam=byte(candidate,'team')<<24>>24;
      if(callerTeam===candidateTeam || candidateTeam===4) continue;
      // Lifecycle18 is reached only after every preceding source gate. Reuse
      // the same canonical stage runtime, never a raw18 shadow on the actor.
      if(root.getStageRuntime()!==stage || call(()=>stage.getActualActor(pointer))!==candidate)
        fail('candidate canonical stage actor differs');
      const binding=record(call(()=>stage.getActorBinding(pointer)),'candidate stage18 owner'),old=candidateStages.get(pointer);
      if(old && old!==binding) fail('candidate stage18 owner changed');
      if(binding===candidate || binding===actual || binding===sources || binding===tableOwner ||
        binding===globalsOwner || [...lists.values()].includes(binding)) fail('candidate stage18 storage alias');
      noShadows(binding,['active0','team','team88','byte88','field88','136','byte18','state18','24']);
      candidateStages.set(pointer,binding);
      if((byte(binding,'lifecycle18')<<24>>24)>=2) continue;
      const captured=uint(read(globals,'count804361a0'),0xffffffff,'count804361a0');
      write(globals,'count804361a0',(captured+1)>>>0);
      // Source increments the count BEFORE its indexed pointer store. A bad
      // scratch destination therefore preserves that increment, with no rollback.
      if(captured>=4096) fail('8006b90c scratch candidate index outside host bound4096');
      write(list('scratchCandidates2208'),String(captured),object);
    }
  };
  const runtime: SourceActorTargetDispatchRuntime={
    getSchedulerRuntime() {return scheduler;},
    getRetainedStorageOwners() {return Object.freeze([sources,...(tableOwner?[tableOwner]:[]),...(globalsOwner?[globalsOwner]:[]),...lists.values()]);},
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
        if(globals===tableOwner || [...lists.values()].includes(globals) || forbidden().includes(globals)) fail('candidateGlobals: source storage alias');
        if(!claimSourceHelperStorage(globals,runtime)) fail('candidateGlobals: storage already claimed');
        noShadows(globals,['active0','byte502','pointer504','pointer508','housekeeping73f','byte80436242','word80436242']);
        globalsOwner=globals;
        const count=uint(read(globals,'half80436242'),65535,'half80436242');
        write(globals,'count804361a0',0);
        scan(actual,count,globals);
        if(uint(read(globals,'count804361a0'),0xffffffff,'count804361a0')===0) return;
        fail('8006b924 reached unsupported candidate-positive source path');
      } catch(error) {if(actual) markIncompleteSourceActorDoubleLifecycle(actual);throw error;}
      finally {activeCandidate=undefined;activeId=undefined;busy=false;}
    },
  };
  if(!claimSourceHelperStorage(sources,runtime)) fail('target-dispatch sources storage already claimed');
  runtimes.add(runtime);claims.set(scheduler,runtime);return Object.freeze(runtime);
}
