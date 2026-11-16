/** Authenticated6f78/6fb4, class initialization and bounded free-block allocation.
 * No LoadJoint success, retail resource hydration or libc internal fault-order claim. */
import {isSourceObjectAllocationRuntime,type SourceObjectAllocationRuntime} from './source-object-allocation.js';
import {requireSourceProjectileResourceInvocation,checkSourceProjectileResourceInvocation,type SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import {claimSourceHelperStorage} from './source-storage-claims.js';
export type SourceJObjClassFields=Record<number,unknown>;
export interface SourceJObjFreeBlock {0:SourceJObjFreeBlock|SourceJObjClassFields|null;bytes?:Uint8Array}
export interface SourceJObjMemoryEntry {8:number;12:SourceJObjFreeBlock|null}
export interface SourceJObjHeapGlobals {count80436a0c:number;table80436a08:Record<number,SourceJObjMemoryEntry|null>}
export interface SourceProjectileResourceSources {
 heapGlobals?:SourceJObjHeapGlobals;
 allocator:SourceObjectAllocationRuntime;
 banks:Record<number,{pointer600:object|null}>;
 loaderGlobals:{override80436980:SourceJObjClassFields|null};
 classes:{jobj:SourceJObjClassFields;parent:SourceJObjClassFields;base:SourceJObjClassFields};
}
export interface SourceProjectileResourceRuntime {getAllocatorRuntime():SourceObjectAllocationRuntime;getRetainedStorageOwners():readonly object[]}
const entries=new WeakMap<object,(root:SourceProjectileRootRuntime,child:symbol,lifetime:symbol)=>never>();
export function isSourceProjectileResourceRuntime(x:unknown):x is SourceProjectileResourceRuntime{return x!==null&&typeof x==='object'&&entries.has(x);}
export function invokeSourceProjectileResource(runtime:SourceProjectileResourceRuntime,root:SourceProjectileRootRuntime,child:symbol,lifetime:symbol):never{
 const run=entries.get(runtime);if(!run)fail('genuine private resource runtime required');return run(root,child,lifetime);
}
function fail(s:string):never{throw Error('[projectile-resource] '+s);}
const native=Reflect.getOwnPropertyDescriptor,nativeKeys=Reflect.ownKeys;
const NativeDataView=DataView,nativeFill=Uint8Array.prototype.fill;
const nativeSetUint32=DataView.prototype.setUint32,nativeSetFloat32=DataView.prototype.setFloat32;
const typedPrototype=Object.getPrototypeOf(Uint8Array.prototype);
const typedBuffer=native(typedPrototype,'buffer')!.get!,typedLength=native(typedPrototype,'byteLength')!.get!,typedOffset=native(typedPrototype,'byteOffset')!.get!;
const viewBuffer=native(DataView.prototype,'buffer')!.get!;
const bufferLength=native(ArrayBuffer.prototype,'byteLength')!.get!,bufferResizable=native(ArrayBuffer.prototype,'resizable')?.get;
export function createSourceProjectileResourceRuntime(sources:SourceProjectileResourceSources):SourceProjectileResourceRuntime{
 const allocationField=native(sources,'allocator');
 const allocator=allocationField&&'value'in allocationField?allocationField.value:undefined;if(!isSourceObjectAllocationRuntime(allocator))fail('genuine allocator required');
 let active:{root:SourceProjectileRootRuntime;child:symbol;lifetime:symbol}|undefined,poisoned=false,failed=false;
 const owners=new Map<string,object>();
 let memory:{block:object;bytes:Uint8Array;buffer:ArrayBuffer}|undefined;
 const edges:{owner:object;key:PropertyKey;value:object}[]=[];
 const check=():void=>{if(poisoned||failed)fail('incomplete resource invocation');
  const a=native(sources,'allocator');if(!a||!('value'in a)||a.value!==allocator)fail('resource allocator owner changed');if(active)checkSourceProjectileResourceInvocation(active.root,runtime,active.child,active.lifetime);
  if(memory){const d=native(memory.block,'bytes');if(!d||!('value'in d)||d.value!==memory.bytes||typedBuffer.call(memory.bytes)!==memory.buffer||typedLength.call(memory.bytes)!==136||bufferLength.call(memory.buffer)!==136)fail('allocated block storage changed');for(const key of nativeKeys(memory.block))if(typeof key==='string'&&/^(0|[1-9][0-9]*)$/.test(key)&&key!=='0')fail('allocated block scalar shadow');}
  for(const edge of edges){const d=native(edge.owner,edge.key);if(!d||!('value'in d)||d.value!==edge.value)fail('retained resource owner changed');}};
 const read=(o:unknown,key:PropertyKey):unknown=>{if(o===null||typeof o!=='object')fail(String(key)+': source owner required');const d=Object.getOwnPropertyDescriptor(o,key);check();if(!d||!('value'in d))fail(String(key)+': own data required');return d.value;};
 const write=(o:object,key:number,value:unknown):void=>{read(o,key);check();const d=native(o,key);if(!d||!('value'in d)||!d.writable)fail(String(key)+': writable source field required');(o as SourceJObjClassFields)[key]=value;check();};
 const uint=(v:unknown,max=0xffffffff):number=>{if(typeof v!=='number'||!Number.isInteger(v)||v<0||v>max)fail('unsigned source integer required');return v;};
 const retain=(name:string,value:unknown):object=>{
  if(value===null||typeof value!=='object'||Array.isArray(value)||ArrayBuffer.isView(value)||value instanceof Promise)fail(name+': explicit record required');
  const prior=owners.get(name);if(prior&&prior!==value)fail(name+': owner changed');
  if([...owners].some(([k,v])=>k!==name&&v===value)||value===sources||allocator.getRetainedStorageOwners().includes(value)||active?.root.getRetainedStorageOwners().includes(value))fail(name+': source storage alias');
  if(!claimSourceHelperStorage(value,runtime))fail(name+': claimed storage alias');owners.set(name,value);check();return value;
 };
 const bind=(name:string,o:object,key:PropertyKey):object=>{const value=retain(name,read(o,key));edges.push({owner:o,key,value});check();return value;};
 const call=<T>(f:()=>T):T=>{const v=f();check();return v;};
 const method=(c:object,offset:number,expected:number):void=>{if(uint(read(c,offset))!==expected)fail('unselected class method'+offset.toString(16));};
 let jobj:object,parent:object|undefined,base:object|undefined,classes:object;
 const initInfo=(child:object,p:object,objectSize:number,classSize:number,library:number,name:number):void=>{
  write(child,4,1);write(child,8,library);write(child,12,name);write(child,16,objectSize);write(child,18,classSize);write(child,20,p);
  for(const offset of [28,24,32,36])write(child,offset,0);
  if((uint(read(p,4))&1)===0)initialize(p);
  const size=(x:object,k:number)=>uint(read(x,k),65535)<<16>>16;
  if(size(child,16)<size(p,16)||size(child,18)<size(p,18))fail('actual class size assertion');
  const length=size(p,18)-40;if(length<0||length%4||length>44)fail('unsupported class memcpy size');
  if(child===p)fail('class memcpy overlap');
  // Explicit nonalias logical memcpy: actual parent values, no supplied methods.
  // No claim about libc internal load/store or fault ordering.
  const copied:number[]=[];for(let k=0;k<length;k+=4)copied.push(uint(read(p,40+k)));
  for(let k=0;k<length;k+=4){read(child,40+k);const d=native(child,40+k);if(!d||!('value'in d)||!d.writable)fail('readonly inherited method');}
  check();for(let k=0;k<length;k+=4){const d=native(child,40+k);if(!d||!('value'in d)||!d.writable)fail('changed inherited method');}
  for(let k=0;k<length;k+=4)(child as SourceJObjClassFields)[40+k]=copied[k/4];check();
  const sibling=read(p,28);write(child,24,sibling);write(p,28,child);
 };
 const initialize=(c:object):void=>{
  if(c===base){method(c,0,0x8025cfec);write(c,4,1);write(c,8,0x803ad7c4);write(c,12,0x803ad7dc);write(c,16,4);write(c,18,60);write(c,20,null);for(const k of [28,24,32,36])write(c,k,0);
   for(const [k,v]of [[40,0x8025cef0],[44,0x8025cf48],[48,0x8025cf50],[52,0x8025cf54],[56,0x8025cfc0]])write(c,k!,v!);
  }else if(c===parent){method(c,0,0x8025acb8);base=bind('classBase',classes,'base');initInfo(c,base,8,60,0x803ad584,0x80436038);
  }else if(c===jobj){method(c,0,0x802524e8);parent=bind('classParent',classes,'parent');initInfo(c,parent,136,84,0x803acfac,0x803acfc4);
   for(const [k,v]of [[44,0x80251eb4],[48,0x802523ec],[56,0x80252484],[64,0x8024d224],[68,0x80253174],[72,0x80253380],[60,0x8024f638],[76,0x80251f18],[80,0x8024e120]])write(c,k!,v!);
  }else fail('unselected class initializer owner');
 };
 // Only the authenticated size136/index4 path with an explicit existing free
 // block is supported. No heap growth, splitting, zeroed memory or JObj result.
 const allocateClass=(c:object):object|null=>{
  const size=uint(read(c,16),65535)<<16>>16;
  if(size!==136)fail('allocator8025cef0 unsupported signed object size');
  const heap=bind('heapGlobals',sources,'heapGlobals');
  const count=uint(read(heap,'count80436a0c'))|0;
  if(4>=count)fail('actual GetMemoryEntry requires unsupported table growth');
  const table1=retain('heapTableFirst',read(heap,'table80436a08'));
  const first=read(table1,4);
  if(first===null)fail('actual GetMemoryEntry requires unsupported entry creation');
  const firstEntry=retain('heapEntryFirst',first);
  // Source performs a fresh global/table load even on its existing-entry path.
  // Mutable table pointer and entries are deliberately not retained edges.
  const table2Value=read(heap,'table80436a08');
  const table2=table2Value===table1?table1:retain('heapTableReload',table2Value);
  const entryPointer=read(table2,4);
  if(entryPointer===null)return null;
  const entry=entryPointer===firstEntry?firstEntry:retain('heapEntryReload',entryPointer),headPointer=read(entry,12);
  if(headPointer===null)fail('actual hsdAllocMemPiece requires unsupported empty free-list path');
  const head=retain('allocatedBlock',headPointer),next=read(head,0);
  if(next!==null){if(next===head)fail('cyclic free block');retain('nextFreeBlock',next);}
  write(entry,12,next);
  const freeCount=uint(read(entry,8));write(entry,8,(freeCount-1)>>>0);
  const allocated=uint(read(c,32));write(c,32,(allocated+1)>>>0);
  const current=uint(read(c,32)),maximum=uint(read(c,36));
  if(current>maximum)write(c,36,current);
  return head;
 };
 const initializeBlock=(block:object,c:object,size:number):void=>{
  if(!native(block,'bytes'))fail('actual8025d0fc memset requires explicit allocated block byte storage; nonnull LoadJoint incomplete');
  const bytes=read(block,'bytes');
  if(!(bytes instanceof Uint8Array)||Object.getPrototypeOf(bytes)!==Uint8Array.prototype||size!==136||typedOffset.call(bytes)!==0||typedLength.call(bytes)!==136)fail('explicit exact136-byte allocated storage required');
  check();const buffer=typedBuffer.call(bytes) as ArrayBuffer;
  if(!(buffer instanceof ArrayBuffer)||Object.getPrototypeOf(buffer)!==ArrayBuffer.prototype||bufferLength.call(buffer)!==136||bufferResizable?.call(buffer)===true)fail('fixed nonshared allocated buffer required');
  check();
  for(const owner of [sources,...owners.values(),...allocator.getRetainedStorageOwners(),...(active?.root.getRetainedStorageOwners()??[])]){
   if(owner===bytes||owner===buffer||(ArrayBuffer.isView(owner)&&(owner instanceof NativeDataView?viewBuffer.call(owner):typedBuffer.call(owner))===buffer))fail('allocated block backing alias');
  }
  check();if(!claimSourceHelperStorage(bytes,runtime)||!claimSourceHelperStorage(buffer,runtime))fail('allocated block backing already claimed');
  memory={block,bytes,buffer};check();
  // Own canonical symbolic word0 overlays bytes0..3. No scalar field shadows.
  for(const key of nativeKeys(block))if(typeof key==='string'&&/^(0|[1-9][0-9]*)$/.test(key)&&key!=='0')fail('allocated block scalar shadow');
  read(block,0);check();const zero=native(block,0);
  if(!zero||!('value'in zero)||!zero.writable)fail('logical memset requires writable pointer overlay');
  // Logical nonalias memset: no libc internal store/fault-order claim. Admission
  // completes before callback-free zeroing of real supplied bytes and overlay.
  check();const finalZero=native(block,0);if(!finalZero||!('value'in finalZero)||!finalZero.writable)fail('logical memset pointer overlay changed');
  nativeFill.call(bytes,0);(block as SourceJObjClassFields)[0]=null;
  check();write(block,0,c); // actual8025d100, same returned free-block identity.
  method(c,44,0x80251eb4);
  // JObjInit reads the live canonical JObj class parent cell803acc24, not an
  // assumed parent implementation or a host-created initialized object.
  const parentPointer=read(jobj,20);
  if(parentPointer===null)fail('actual JObjInit parent init dereference is null');
  const actualParent=parentPointer===parent?parent:retain('jobjInitParent',parentPointer);
  method(actualParent!,44,0x8025cf48); // authenticated actual parent init returns0.
  // Immutable decoded source constant8043d308 = binary32 one.
  const one=1;
  const data=new NativeDataView(buffer);
  const store=(offset:number,value:number,float=false):void=>{
   check();if(float)nativeSetFloat32.call(data,offset,value,false);else nativeSetUint32.call(data,offset,value,false);check();
  };
  store(0x14,0x40);store(0x2c,one,true);store(0x30,one,true);store(0x34,one,true);
  // hsdNew/JObjAlloc returned the exact allocated object. LoadJoint next reads
  // that object's current class and dispatches its actual +3c load method.
  const actualClass=read(block,0);if(actualClass!==c)fail('allocated class pointer changed');
  method(c,60,0x8024f638);
  fail('actual LoadJoint reached8024f638 JObjLoad; descriptor load body incomplete');
 };
 const runtime:SourceProjectileResourceRuntime={getAllocatorRuntime:()=>allocator,getRetainedStorageOwners:()=>Object.freeze([sources,...owners.values(),...(memory?[memory.bytes,memory.buffer]:[])])};
 entries.set(runtime,(root,child,lifetime)=>{
  if(active){poisoned=true;fail('same-runtime resource reentry');}if(failed)fail('permanently incomplete resource runtime');
  requireSourceProjectileResourceInvocation(root,runtime,child,lifetime);active={root,child,lifetime};
  try{
   if(root.getSpawnRuntime().getAllocatorRuntime()!==allocator)fail('resource allocator differs');check();
   const banks=bind('banks',sources,'banks'),slot=call(()=>allocator.readS8(child,0x97));
   const row=bind('bankSlot'+slot,banks,String(slot)),bankPointer=read(row,'pointer600');
   //6f78 returns its pointer unchanged, including null. The caller's E0 load
   // precedes the actual6fb4 bank+10 dereference even on this failing path.
   const bank=bankPointer===null?null:retain('bank',bankPointer);
   if(bank!==null){edges.push({owner:row,key:'pointer600',value:bank});check();}
   //6f78 returns;7e144 then loads actual descriptor pointer, not child+E0 view.
   const descriptor=call(()=>allocator.readPointer(child,0xe0));
   if(bank===null)fail('actual6fb4 bank pointer10 dereference is null');
   const scenePointer=read(bank,'pointer10'),scene=scenePointer===null?null:retain('scene',scenePointer);
   if(scene!==null){edges.push({owner:bank,key:'pointer10',value:scene});check();}
   if(descriptor===null)fail('null E0 descriptor at actual6fb4 dereference');call(()=>allocator.getDescriptor(descriptor));
   const old=call(()=>allocator.readPointer(descriptor,0x0c));
   if(scene===null)fail('actual6fb4 scene pointer00 dereference is null');
   const table=bind('descriptorTable',scene,'pointer00'),selected=read(table,'14'),record=selected===null?null:retain('selectedRecord',selected);
   if(record!==null){edges.push({owner:table,key:'14',value:record});check();}
   if(old!==null)fail('actual80006ff0 reached unsupported8024fd74 JObjUnref');
   if(record===null)fail('actual6fb4 selected record pointer00 dereference is null');
   const desc=read(record,'pointer00');
   if(desc===null)fail('explicit null LoadJoint path not part of nonnull resource prefix');
   const jointDescriptor=retain('jointDescriptor',desc);edges.push({owner:record,key:'pointer00',value:jointDescriptor});check();
   if(read(jointDescriptor,'className00')!==null)fail('actual8024f864 reached unsupported8025d4e8 class search');
   const globals=bind('loaderGlobals',sources,'loaderGlobals');classes=bind('classes',sources,'classes');
   const override=read(globals,'override80436980');
   jobj=bind('classJObj',classes,'jobj');
   if(override!==null&&override!==jobj)fail('unselected explicit JObj class override');
   if((uint(read(jobj,4))&1)===0)initialize(jobj);
   method(jobj,40,0x8025cef0);
   if(!native(sources,'heapGlobals'))fail('actual8025d0c4 reached inherited allocator8025cef0; nonnull LoadJoint incomplete');
   const block=allocateClass(jobj);
   if(block===null)fail('actual JObjAlloc null result reaches assertion; nonnull LoadJoint incomplete');
   if((uint(read(jobj,4))&1)===0)initialize(jobj);
   const objectSize=uint(read(jobj,16),65535)<<16>>16;
   initializeBlock(block,jobj,objectSize);
   fail('unreachable source JObj initialization continuation');
  }catch(error){failed=true;throw error;}finally{active=undefined;}
 });return Object.freeze(runtime);
}
