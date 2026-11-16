/** Authentic2cda4 stores and2cc78 list traversal. Standalone source helper only:
 * no outer2bb14 admission, callback substitution, or completed-frame claim. */
import {isSourceObjectSchedulerRuntime,type SourceObjectSchedulerRuntime} from './source-object-scheduler.js';
import {isSourceActorNormalLifecycleRuntime,type SourceActorNormalLifecycleRuntime} from './actor-normal-lifecycle.js';
import {isSourceActorSlotStatusRuntime,type SourceActorSlotStatusRuntime} from './actor-slot-status.js';
import {isSourcePlayerTableStorage} from './source-storage-claims.js';
export interface SourceContactResetSources {
 scheduler:SourceObjectSchedulerRuntime;
 normal?:SourceActorNormalLifecycleRuntime;
 players?:SourceActorSlotStatusRuntime;
 constants?:{float80436f68?:number};
}
export interface SourceContactResetRuntime {
 resetActor(id:symbol):void;
 resetPlayer(index:number):void;
 runGroupReset(groupBits:number):void;
}
const native=Reflect.getOwnPropertyDescriptor;
function fail(why:string):never{throw Error('[source-contact-reset] '+why);}
function raw(v:unknown,max:number,label:string):number{if(typeof v!=='number'||!Number.isInteger(v)||v<0||v>max)fail(label+': explicit raw unsigned value required');return v;}
export function createSourceContactResetRuntime(sources:SourceContactResetSources):SourceContactResetRuntime{
 const field=native(sources,'scheduler'),scheduler=field&&'value'in field?field.value:undefined;
 if(!isSourceObjectSchedulerRuntime(scheduler))fail('genuine scheduler required');
 const allocator=scheduler.getAllocatorRuntime(),root=scheduler.getRootRuntime(),spawns=root.getSpawnRuntime();
 let busy=false,poisoned=false,incomplete=false,validating=false;
 let slotTable:object|undefined;
 const edges:{o:object;k:PropertyKey;value:unknown}[]=[];
 const live=new Map<string,object>(),actorOwners=new Map<symbol,{actual:object;binding:object}>(),groups=new Map<number,object>();
 const exact=():void=>{
  const f=native(sources,'scheduler');if(!f||!('value'in f)||f.value!==scheduler)fail('scheduler owner changed');
  for(const e of edges){const d=native(e.o,e.k);if(!d||!('value'in d)||d.value!==e.value)fail('retained reset owner changed');}
 };
 const check=():void=>{if(poisoned||incomplete)fail('incomplete reset invocation');if(validating)return;validating=true;
  try{if(scheduler.getAllocatorRuntime()!==allocator||scheduler.getRootRuntime()!==root||root.getSpawnRuntime()!==spawns||spawns.getAllocatorRuntime()!==allocator)fail('canonical reset graph changed');if(slotTable&&scheduler.getActorSlotTable()!==slotTable)fail('reset actor-slot owner changed');for(const [index,owner]of groups)if(allocator.getGroup(index)!==owner)fail('reset group owner changed');exact();if(poisoned)fail('caught reset reentry');}finally{validating=false;}
 };
 const own=(o:object,k:PropertyKey):unknown=>{const d=Object.getOwnPropertyDescriptor(o,k);check();if(!d||!('value'in d))fail(String(k)+': own data required');return d.value;};
 const record=(v:unknown,label:string):object=>{if(v===null||typeof v!=='object'||Array.isArray(v)||ArrayBuffer.isView(v)||v instanceof Promise)fail(label+': source record required');return v;};
 const keep=(name:string,o:object):object=>{const old=live.get(name);if(old&&old!==o)fail(name+': canonical owner changed');if([...live].some(([k,v])=>k!==name&&v===o)||o===sources)fail(name+': reset storage alias');if(name==='constants'&&[...actorOwners.values()].some(v=>v.actual===o||v.binding===o))fail('constants alias actor reset owner');live.set(name,o);return o;};
 const link=(name:string,o:object,k:PropertyKey):object=>{const v=keep(name,record(own(o,k),name));if(!edges.some(e=>e.o===o&&e.k===k))edges.push({o,k,value:v});exact();return v;};
 const aliases=(o:object,k:string,offset:number,terminal=false):void=>{
  const hex=offset.toString(16),keys=[String(offset),...['field','byte','half','float','word'].flatMap(p=>[p+hex,p+hex.toUpperCase()])];
  for(const key of new Set(keys))if(key!==k){const d=terminal?native(o,key):Object.getOwnPropertyDescriptor(o,key);if(!terminal)check();if(d)fail(k+': competing reset source field');}
 };
 type Cell={o:object;k:string;offset:number};
 type Target={guard:()=>void;cell:(offset:number,width:number)=>Cell;node?:symbol};
 const load=(t:Target,offset:number):number=>{
  t.guard();if(t.node!==undefined){const v=allocator.readU8(t.node,offset);t.guard();return v;}
  const c=t.cell(offset,1);aliases(c.o,c.k,offset);const v=own(c.o,c.k);t.guard();aliases(c.o,c.k,offset,true);return raw(v,255,c.k);
 };
 const store=(t:Target,offset:number,value:number,width:number):void=>{
  t.guard();if(t.node!==undefined){
   // Same original allocation bytes. Poll this helper's private operation after
   // every observable admission, then commit the single scalar store atomically.
   // Allocator's own closure alone cannot see a caught reset-parent reentry.
   const bytes=allocator.getObject(t.node),buffer=new ArrayBuffer(width),view=new DataView(buffer);
   if(width===1)view.setUint8(0,value);else if(width===2)view.setUint16(0,value,false);else view.setFloat32(0,value,false);
   for(let i=0;i<width;i++){const d=Object.getOwnPropertyDescriptor(bytes,String(offset+i));t.guard();if(!d||!('value'in d)||!d.writable)fail('node scalar requires writable own bytes');}
   t.guard();for(let i=0;i<width;i++){const d=native(bytes,String(offset+i));if(!d||!('value'in d)||!d.writable)fail('node scalar destination changed');}
   exact();for(let i=0;i<width;i++)bytes[offset+i]=view.getUint8(i);check();return;
  }
  const c=t.cell(offset,width);aliases(c.o,c.k,offset);const d=Object.getOwnPropertyDescriptor(c.o,c.k);check();if(!d||!('value'in d)||!d.writable)fail(c.k+': writable own destination required');
  t.guard();const last=native(c.o,c.k);if(!last||!('value'in last)||!last.writable)fail(c.k+': destination changed');aliases(c.o,c.k,offset,true);exact();
  (c.o as Record<string,unknown>)[c.k]=value;check();
 };
 const zero=():number=>{const o=link('constants',sources,'constants'),v=own(o,'float80436f68');check();if(!Object.is(v,0))fail('authenticated float80436f68 +0 required');return 0;};
 const reset=(t:Target):void=>{
  const z=zero();for(const offset of [0x1cc,0x1d0,0x1d4])store(t,offset,z,4);
  store(t,0x1d9,0,1);store(t,0x1da,0,1);const support=load(t,0x1db);store(t,0x1de,support,1);
  for(const offset of [0x1db,0x1dc,0x1dd,0x280])store(t,offset,0,1);
  const old274=load(t,0x274);store(t,0x275,old274,1);store(t,0x274,0,1);
  const dec=(offset:number):void=>{const b=load(t,offset);if((b<<24>>24)!==0)store(t,offset,(b-1)&255,1);};
  dec(0x1df);store(t,0x270,0,2);store(t,0x286,0,2);dec(0x2ae);dec(0x2af);dec(0x1e8);
 };
 const actor=(id:symbol):Target=>{
  const normal=link('normal',sources,'normal') as SourceActorNormalLifecycleRuntime;if(!isSourceActorNormalLifecycleRuntime(normal))fail('genuine normal-lifecycle required');
  const actual=normal.getActualActor(id),binding=normal.getActorBinding(id);check();const old=actorOwners.get(id);if(old&&(old.actual!==actual||old.binding!==binding))fail('actor owner changed');actorOwners.set(id,{actual,binding});
  const guard=():void=>{check();if(normal.getActualActor(id)!==actual||normal.getActorBinding(id)!==binding||allocator.getPointerTarget(id)!==actual)fail('canonical actor reset owner changed');check();aliases(actual,'__no_actual_1d9_owner',0x1d9,true);aliases(actual,'supportContact1db',0x1db,true);};
  guard();return{guard,cell:(offset,width)=>offset===0x1d9?{o:binding,k:'byte1d9',offset}:{o:actual,k:offset===0x1db?'supportContact1db':(width===4?'float':width===2?'half':'byte')+offset.toString(16),offset}};
 };
 const player=(index:number):Target=>{
  raw(index,11,'reset player index');const status=link('players',sources,'players')as SourceActorSlotStatusRuntime;
  if(!isSourceActorSlotStatusRuntime(status)||status.getSchedulerRuntime()!==scheduler||spawns.getAdmissionRuntime().getActionRuntime().getSlotStatusRuntime()!==status)fail('canonical player status required');
  const view=status.getViewPointer(index),address=allocator.getInteriorAddress(view);if(!address||address.byteOffset!==index*0x3e4+0x394)fail('canonical player address required');
  const rows=allocator.getPointerTarget(address.base);if(!isSourcePlayerTableStorage(rows,status,allocator))fail('canonical player storage required');
  const row=keep('player:'+index,record(own(rows,String(index)),'player row'));edges.push({o:rows,k:String(index),value:row});
  const guard=():void=>{check();if(status.getSchedulerRuntime()!==scheduler||status.getViewPointer(index)!==view||allocator.getPointerTarget(address.base)!==rows)fail('player reset owner changed');check();for(let i=0;i<13;i++){if(i===index)continue;const d=native(rows,String(i));if(d&&'value'in d&&d.value===row)fail('player reset row alias');}};
  guard();return{guard,cell:(offset,width)=>({o:row,k:(width===4?'float':width===2?'half':'byte')+offset.toString(16),offset})};
 };
 const node=(id:symbol):Target=>{const bytes=allocator.getObject(id);return{node:id,guard(){check();if(allocator.getObject(id)!==bytes)fail('node reset storage changed');check();},cell(){fail('node fields stay canonical bytes');}};};
 const pointer=(v:unknown):symbol|null=>{if(v!==null&&typeof v!=='symbol')fail('explicit source list pointer required');return v;};
 const walk=(groupBits:number):void=>{
  const group=(groupBits&0x3fffffff)>>>0,owner=allocator.getGroup(group);check();keep('group:'+group,owner);groups.set(group,owner);check();
  let current=pointer(own(owner,'head'));const visited=new Set<symbol>();
  while(current!==null){if(visited.has(current))fail('source reset cycle unsupported');visited.add(current);
   const enabled=allocator.readS8(current,0);check();if(enabled!==0){const resettable=allocator.readS8(current,0x86);check();if(resettable!==0)reset(node(current));}
   current=allocator.readPointer(current,8);check();
  }
 };
 const operation=(f:()=>void):void=>{if(busy){poisoned=true;fail('same-runtime reset reentry');}if(incomplete)fail('permanently incomplete reset');busy=true;try{check();f();check();}catch(e){incomplete=true;throw e;}finally{busy=false;}};
 return Object.freeze({resetActor(id:symbol){operation(()=>reset(actor(id)));},resetPlayer(index:number){operation(()=>reset(player(index)));},runGroupReset(bits:number){operation(()=>{
  raw(bits,0xffffffff,'group register');walk(bits);
  if((bits|0)<56&&(bits&7)===0){
   for(let i=0;i<6;i++){const table=scheduler.getActorSlotTable();if(slotTable&&slotTable!==table)fail('reset actor-slot owner changed');slotTable=table;check();const id=pointer(own(table,String(i)));if(id===null)fail('null actor slot at active0 load');
    const a=allocator.getPointerTarget(id);check();aliases(a,'active0',0);const active=raw(own(a,'active0'),255,'actor active0');aliases(a,'active0',0,true);
    if((active<<24>>24)!==0)walk((bits+i+1)>>>0);
   }
   walk((bits+7)>>>0);
  }
 });}});
}
