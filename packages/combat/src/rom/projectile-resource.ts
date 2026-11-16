/** Authenticated6f78/6fb4 and real class initialization prefix. No allocation,
 * LoadJoint success, retail resource hydration or libc internal fault order. */
import {isSourceObjectAllocationRuntime,type SourceObjectAllocationRuntime} from './source-object-allocation.js';
import {requireSourceProjectileResourceInvocation,checkSourceProjectileResourceInvocation,type SourceProjectileRootRuntime} from './projectile-root-lifecycle.js';
import {claimSourceHelperStorage} from './source-storage-claims.js';
export type SourceJObjClassFields=Record<number,unknown>;
export interface SourceProjectileResourceSources {
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
const native=Reflect.getOwnPropertyDescriptor;
export function createSourceProjectileResourceRuntime(sources:SourceProjectileResourceSources):SourceProjectileResourceRuntime{
 const allocationField=native(sources,'allocator');
 const allocator=allocationField&&'value'in allocationField?allocationField.value:undefined;if(!isSourceObjectAllocationRuntime(allocator))fail('genuine allocator required');
 let active:{root:SourceProjectileRootRuntime;child:symbol;lifetime:symbol}|undefined,poisoned=false,failed=false;
 const owners=new Map<string,object>();
 const edges:{owner:object;key:PropertyKey;value:object}[]=[];
 const check=():void=>{if(poisoned||failed)fail('incomplete resource invocation');
  const a=native(sources,'allocator');if(!a||!('value'in a)||a.value!==allocator)fail('resource allocator owner changed');if(active)checkSourceProjectileResourceInvocation(active.root,runtime,active.child,active.lifetime);
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
 const runtime:SourceProjectileResourceRuntime={getAllocatorRuntime:()=>allocator,getRetainedStorageOwners:()=>Object.freeze([sources,...owners.values()])};
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
   fail('actual8025d0c4 reached inherited allocator8025cef0; nonnull LoadJoint incomplete');
  }catch(error){failed=true;throw error;}finally{active=undefined;}
 });return Object.freeze(runtime);
}
