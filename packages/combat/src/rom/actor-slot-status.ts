import {checkSourceBattlePlayerContactInvocation,type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
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
import {claimSourceHelperStorage,isSourcePlayerTableStorage} from './source-storage-claims.js';
import {isSourceObjectSchedulerRuntime,type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {getSourceActorPlayerTablePointer,type SourceObjectAllocationRuntime} from './source-object-allocation.js';
import {requireSourceActorActionSlotStatusOwner} from './actor-action-request.js';
export interface SourceActorPlayerSlotRecord {state18?: number;byte10?:number;
  /** Same physical player record; raw endpoint words are copied before float admission. */
  active0?:number;contact26f?:number;word2e8?:number;word2ec?:number;word2f0?:number;
  word300?:number;word304?:number;word308?:number;
}
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
  /** Metadata-only explicit reference inventory, including unreached rows. */
  getDeclaredStorageOwners(): readonly object[];
  readSlot(slot: number): number;
  /** Opaque803c73b0 + index*3e4 +394. Formation reads no row scalar. */
  getViewPointer(recordIndex:number):symbol;
  /** Fresh canonical row+10 read through a genuine retained view identity. */
  readViewMetadata(pointer:symbol):number;
}
const contactChecks=new WeakMap<object,()=>void>();
/** Read-only retained identity check, not an execution capability or row accessor. */
export function checkSourcePlayerContactStorage(helper:SourceActorSlotStatusRuntime):void {contactChecks.get(helper)?.();}
const contactRows=new WeakMap<object,(outer:SourceBattleOuterFrameRuntime,index:number)=>object>();
export function getSourcePlayerContactRow(helper:SourceActorSlotStatusRuntime,outer:SourceBattleOuterFrameRuntime,index:number):object {
  checkSourceBattlePlayerContactInvocation(outer,helper);
  const access=contactRows.get(helper);if(!access)fail('canonical contact player helper required');
  return access(outer,index);
}
const runtimes=new WeakSet<object>(),claims=new WeakMap<object,SourceActorSlotStatusRuntime>();
const addressScopes=new WeakMap<object,(allocator:SourceObjectAllocationRuntime,table:object)=>void>();
const terminalDescriptor=Reflect.getOwnPropertyDescriptor;
const terminalDescriptors=Object.getOwnPropertyDescriptors;
/** Private exact synchronous scope; knowing the helper or table is insufficient. */
export function requireSourceActorPlayerTableAddressability(helper:SourceActorSlotStatusRuntime,
  allocator:SourceObjectAllocationRuntime,table:object):void {
  const scope=addressScopes.get(helper);
  if(!isSourceActorSlotStatusRuntime(helper)||!scope)fail('private player-table addressability required');
  scope(allocator,table);
}
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
  let busy=false,poisoned=false,tableOwner: object|undefined,addressTable:object|undefined;
  const views=new Map<symbol,{table:object;index:number;base:symbol}>();
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
    const otherOwners=forbidden(),addressable=name==='slotRecords'&&isSourcePlayerTableStorage(selected,runtime,allocator);
    if(selected===tableOwner || (otherOwners.includes(selected) && !addressable) ||
      [...retained].some(([key,owner])=>key!==name && owner===selected)) fail(`${name}: source storage alias`);
    if(addressable) {
      // The pointer target itself is a deliberate shared identity, not an
      // exemption for other root/stack/profile/actor roles pointing at it.
      // Only genuine frozen allocator interior metadata may refer to its base.
      for(const owner of otherOwners)if(owner!==selected)for(const [key,field]of Object.entries(terminalDescriptors(owner))) {
        check();if(!('value'in field)||field.value!==selected||(owner===sources&&key==='slotRecords'))continue;
        let interior=false;
        if(key==='base'&&Object.isFrozen(owner)) {
          let id:symbol|undefined;try{id=allocator.getPointerIdentity(owner);}catch{/* Not an allocator pointer target. */}
          if(id!==undefined) {
            const address=call(()=>allocator.getInteriorAddress(id));
            interior=address!==null&&allocator.getPointerTarget(address.base)===selected;
          }
        }
        if(!interior)fail('player table aliases another source storage role');
      }
    }
    if(!claimSourceHelperStorage(selected,runtime)) fail(`${name}: storage already claimed`);
    retained.set(name,selected);return selected;
  };
  const graph=():void=>{
    if(read(sources,'scheduler')!==scheduler || scheduler.getRootRuntime()!==root ||
      root.getSpawnRuntime()!==spawns || scheduler.getAllocatorRuntime()!==allocator ||
      spawns.getAdmissionRuntime().getActionRuntime()!==action || call(()=>action.getSlotStatusRuntime())!==runtime)
      fail('exact canonical player-table scheduler/action graph required');
  };
  const viewOperation=<T>(run:()=>T):T=>{
    if(busy){poisoned=true;fail('same-runtime reentry unsupported');}
    busy=true;poisoned=false;
    try{
      graph();const result=run();check();requireSourceActorActionSlotStatusOwner(action,runtime);
      const selected=terminalDescriptor(sources,'scheduler'),rows=terminalDescriptor(sources,'slotRecords');
      if(!selected||!('value'in selected)||selected.value!==scheduler || !rows||!('value'in rows)||
        rows.value!==retained.get('slotRecords'))fail('terminal canonical player graph changed');
      return result;
    }finally{addressTable=undefined;busy=false;}
  };
  const runtime: SourceActorSlotStatusRuntime={
    getSchedulerRuntime() {return scheduler;},
    getRetainedStorageOwners() {return Object.freeze([sources,...retained.values()]);},
    getDeclaredStorageOwners() {
      // References only. Missing/accessor fields are left to their reached
      // source load; this inventory never invokes a getter or reads a scalar.
      const values: object[]=[sources];
      const reference=(owner: object,key: string): object|undefined=>{
        const p=Object.getOwnPropertyDescriptor(owner,key);check();
        if(p && 'value' in p && p.value!==null && typeof p.value==='object') {
          values.push(p.value);return p.value;
        }
        return undefined;
      };
      const rows=reference(sources,'slotRecords');
      if(rows) for(let index=0;index<13;index++) reference(rows,String(index));
      reference(sources,'dispatch3938');return Object.freeze(values);
    },
    getViewPointer(index) {return viewOperation(()=>{
      if(!Number.isInteger(index)||index<0||index>=13)fail('view record outside bounded13-record owner');
      const rows=retain('slotRecords',read(sources,'slotRecords'));addressTable=rows;
      const base=call(()=>getSourceActorPlayerTablePointer(allocator,runtime,rows));
      const pointer=call(()=>allocator.getInteriorPointer(base,(index*0x3e4+0x394)>>>0));
      requireSourceActorPlayerTableAddressability(runtime,allocator,rows);
      retain('slotRecords',read(sources,'slotRecords'));
      views.set(pointer,{table:rows,index,base});return pointer;
    });},
    readViewMetadata(pointer) {return viewOperation(()=>{
      const view=views.get(pointer);if(!view)fail('genuine owned player view pointer required');
      const rows=retain('slotRecords',read(sources,'slotRecords'));
      if(rows!==view.table)fail('captured player view table changed');
      const address=call(()=>allocator.getInteriorAddress(pointer));
      if(address?.base!==view.base || address.byteOffset!==view.index*0x3e4+0x394 ||
        call(()=>allocator.getPointerTarget(view.base))!==rows)fail('canonical player view address changed');
      const row=retain(`slotRecord${view.index}`,read(rows,String(view.index)));
      const uniqueRow=():void=>{
        for(let index=0;index<13;index++)if(index!==view.index) {
          const field=terminalDescriptor(rows,String(index));
          if(field&&'value'in field&&field.value===row)fail('player view row aliases another logical record');
        }
      };
      uniqueRow();
      noShadows(row,['metadata10','field10','16']);
      const value=uint(read(row,'byte10'),255,'byte10');
      graph();
      retain('slotRecords',rows); // Terminal role/alias admission, no repeated scalar read.
      // Last observable metadata hooks cannot swap the row/table behind a
      // captured interior pointer. No source scalar is reread here.
      const sourceTable=terminalDescriptor(sources,'slotRecords'),selected=terminalDescriptor(rows,String(view.index));
      if(!sourceTable||!('value'in sourceTable)||sourceTable.value!==rows ||
        !selected||!('value'in selected)||selected.value!==row)fail('canonical player view row changed');
      for(const key of ['metadata10','field10','16'])if(terminalDescriptor(row,key))fail('competing player metadata owner');
      uniqueRow();
      check();return value;
    });},
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
  const contactSelected=new Map<number,object>();
  contactChecks.set(runtime,()=>{
    if(contactSelected.size===0)return;
    const table=terminalDescriptor(sources,'slotRecords'),rows=retained.get('slotRecords');
    if(!table||!('value'in table)||table.value!==rows||!rows)fail('canonical contact table changed');
    for(const [index,row]of contactSelected){const p=terminalDescriptor(rows,String(index));
      if(!p||!('value'in p)||p.value!==row)fail('canonical contact row changed');}
  });
  contactRows.set(runtime,(outer,index)=>viewOperation(()=>{
    checkSourceBattlePlayerContactInvocation(outer,runtime);
    if(!Number.isInteger(index)||index<0||index>=13)fail('contact player outside physical13-record domain');
    graph();const rows=retain('slotRecords',read(sources,'slotRecords'));
    const row=retain(`slotRecord${index}`,read(rows,String(index)));
    for(let i=0;i<13;i++)if(i!==index){const d=terminalDescriptor(rows,String(i));if(d&&'value'in d&&d.value===row)fail('contact player aliases another row');}
    contactSelected.set(index,row);graph();checkSourceBattlePlayerContactInvocation(outer,runtime);
    const a=terminalDescriptor(sources,'slotRecords'),b=terminalDescriptor(rows,String(index));
    if(!a||!('value'in a)||a.value!==rows||!b||!('value'in b)||b.value!==row)fail('canonical contact row changed');
    return row;
  }));
  addressScopes.set(runtime,(selected,table)=>{
    if(!busy||poisoned||addressTable!==table||selected!==allocator||retained.get('slotRecords')!==table)
      fail('private active player-table addressability required');
    if(scheduler.getAllocatorRuntime()!==allocator||scheduler.getRootRuntime()!==root||
      root.getSpawnRuntime()!==spawns||spawns.getAdmissionRuntime().getActionRuntime()!==action||
      action.getSlotStatusRuntime()!==runtime)fail('player-table address graph changed');
    const tableField=terminalDescriptor(sources,'slotRecords'),schedulerField=terminalDescriptor(sources,'scheduler');
    if(!tableField||!('value'in tableField)||tableField.value!==table ||
      !schedulerField||!('value'in schedulerField)||schedulerField.value!==scheduler||poisoned)
      fail('canonical player-table address owner changed');
  });
  if(!claimSourceHelperStorage(sources,runtime)) fail('slot-status sources storage already claimed');
  runtimes.add(runtime);claims.set(scheduler,runtime);return Object.freeze(runtime);
}
