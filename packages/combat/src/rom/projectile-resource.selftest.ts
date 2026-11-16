import {getSourceProjectileResourceJointPointer,completeSourceProjectileResourceDescriptor} from './source-object-allocation.js';
import {createProjectileInitializerTailTestFixture} from './projectile-initializer-tail.selftest.js';
import {createSourceProjectileResourceRuntime,invokeSourceProjectileResource,type SourceJObjClassFields,type SourceJObjMemoryEntry,type SourceJObjFreeBlock} from './projectile-resource.js';
import type {createProjectileInitializerTailBaseTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createProjectileInitializerTailBaseTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[resource-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let m='';try{f();}catch(e){m=String(e);}check(m.includes(part),'expected '+part+', got '+m);}
export function createProjectileResourceTestFixture(make:Make){
 const x=createProjectileInitializerTailTestFixture(make);
 const cls=(init:number):SourceJObjClassFields=>{const c:SourceJObjClassFields={0:init,4:0,8:0,12:0,16:0,18:0,20:null,24:0,28:0,32:0,36:0};for(let k=40;k<=80;k+=4)c[k]=0;return c;};
 const classes={jobj:cls(0x802524e8),parent:cls(0x8025acb8),base:cls(0x8025cfec)};
 const jointDescriptor={className00:null},selectedRecord={pointer00:jointDescriptor},table={14:selectedRecord},scene={pointer00:table},bank={pointer10:scene};
 const slot=x.allocator.readS8(x.child,0x97),banks={[slot]:{pointer600:bank}},loaderGlobals={override80436980:null};
 const sources={allocator:x.allocator,banks,loaderGlobals,classes};
 const resource=createSourceProjectileResourceRuntime(sources);Object.assign(x.rootSources,{resources:resource});
 return Object.assign(x,{resource,resourceSources:sources,classes,jointDescriptor,selectedRecord,resourceTable:table,scene,bank,loaderGlobals});
}
export function runProjectileResourceSelfTests(make:Make):void{
 let count=0;const fresh=()=>{count++;return createProjectileResourceTestFixture(make);};
 {
  const x=fresh();const descriptor=x.allocator.readPointer(x.child,0xe0)!;check(x.allocator.readPointer(descriptor,0x0c)===null,'real06d4c already cleared oldjoint');
  refuses(()=>x.frame.runFrame(),'allocator8025cef0');
  check(x.classes.jobj[4]===1&&x.classes.parent[4]===1&&x.classes.base[4]===1,'all three source initializers ran');
  check(x.classes.jobj[40]===0x8025cef0&&x.classes.parent[40]===x.classes.base[40],'actual inherited allocator values');
  check(x.classes.jobj[44]===0x80251eb4&&x.classes.parent[44]===0x8025cf48&&x.classes.jobj[60]===0x8024f638,'source overrides after inheritance');
  check(x.classes.jobj[16]===136&&x.classes.jobj[18]===84&&x.classes.parent[16]===8&&x.classes.base[16]===4,'source sizes');
  check(x.classes.base[28]===x.classes.parent&&x.classes.parent[28]===x.classes.jobj,'source child lists');
  check(x.allocator.readPointer(descriptor,0xc)===null,'allocator boundary never invents JObj result');
  refuses(()=>x.frame.runFrame(),'incomplete');
 }
 {
  const x=fresh();delete x.classes.parent[4];refuses(()=>x.frame.runFrame(),'own data');
  check(x.classes.jobj[4]===1&&x.classes.jobj[16]===136&&x.classes.jobj[20]===x.classes.parent,'earlier child header survives parent read failure');check(x.classes.base[4]===0,'no eager root initialization');
 }
 {
  const x=fresh();Object.defineProperty(x.classes.parent,'40',{writable:false});refuses(()=>x.frame.runFrame(),'readonly inherited');
  check(x.classes.base[40]===0x8025cef0&&x.classes.base[44]===0x8025cf48,'root stores survive failed logical memcpy');check(x.classes.jobj[44]===0,'no premature JObj overrides');
 }
 {
  const x=fresh();delete (x.loaderGlobals as {override80436980?:null}).override80436980;refuses(()=>x.frame.runFrame(),'override80436980');check(x.classes.jobj[4]===0,'no default override');
 }
 {
  const x=fresh();refuses(()=>invokeSourceProjectileResource(x.resource,x.root,x.child,Symbol('wrong lifetime')),'private exact');check(x.classes.jobj[4]===0,'public helper cannot steal scope');refuses(()=>x.frame.runFrame(),'allocator8025cef0');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(!injected&&o===x.classes.base&&String(k)==='40'){injected=true;try{x.frame.runFrame();}catch{}}return native(o,k);}) as typeof native;
  try{refuses(()=>x.frame.runFrame(),'private exact');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&x.classes.base[40]===0&&x.classes.jobj[44]===0,'caught outer reentry blocks next class store');
 }
 {
  const x=fresh(),descriptor=x.allocator.readPointer(x.child,0xe0)!;
  x.allocator.writePointer(descriptor,0x0c,x.child);delete (x.resourceTable as {14?:object})[14];
  refuses(()=>x.frame.runFrame(),'14: own data');check(x.classes.jobj[4]===0,'record selection precedes oldjoint gate');
 }
 {
  const x=fresh(),descriptor=x.allocator.readPointer(x.child,0xe0)!;
  x.allocator.writePointer(descriptor,0x0c,x.child);refuses(()=>x.frame.runFrame(),'8024fd74');
  check(x.classes.jobj[4]===0&&x.allocator.readPointer(descriptor,0x0c)===x.child,'nonnull old joint never fabricated Unref');
 }
 {
  const x=fresh();x.resourceSources.classes.base=x.classes.parent;refuses(()=>x.frame.runFrame(),'alias');check(x.classes.jobj[4]===1,'late base alias preserves earlier JObj header');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(!changed&&o===x.classes.base&&String(k)==='40'){changed=true;x.resourceSources.loaderGlobals={override80436980:null};}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'owner changed');}finally{Object.getOwnPropertyDescriptor=native;}
  check(changed&&x.classes.base[40]===0,'late retained owner replacement blocks store');
 }
 {
  const x=fresh();x.classes.jobj[4]=1;x.classes.jobj[40]=0x8025cef0;
  delete (x.resourceSources.classes as {parent?:object}).parent;delete (x.resourceSources.classes as {base?:object}).base;
  refuses(()=>x.frame.runFrame(),'allocator8025cef0');check(x.classes.jobj[44]===0,'explicit ready-class path does not inspect unused inheritance');
 }
 {
  const x=fresh(),descriptor=x.allocator.readPointer(x.child,0xe0)!,descriptorBytes=x.allocator.getDescriptor(descriptor),native=Object.getOwnPropertyDescriptor;
  const slot=x.allocator.readS8(x.child,0x97);(x.resourceSources.banks[slot]! as {pointer600:object|null}).pointer600=null;
  let reachedBank=false,e0Reads=0,oldJointReads=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.resourceSources.banks[slot]&&k==='pointer600')reachedBank=true;
   if(reachedBank&&o===x.objectBytes&&String(k)==='224')e0Reads++;
   if(reachedBank&&o===descriptorBytes&&String(k)==='12')oldJointReads++;
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'bank pointer10 dereference is null');}finally{Object.getOwnPropertyDescriptor=native;}
  check(reachedBank&&e0Reads>0&&oldJointReads===0,'null bank returns through6f78 and caller E0 load before6fb4 dereference');
  check(x.classes.jobj[4]===0&&x.allocator.readF32(x.child,0x154)===2,'null bank preserves earlier initializer prefix without class stores');
 }
 {
  const x=fresh(),descriptor=x.allocator.readPointer(x.child,0xe0)!,descriptorBytes=x.allocator.getDescriptor(descriptor),native=Object.getOwnPropertyDescriptor;
  (x.bank as {pointer10:object|null}).pointer10=null;let captured=false,oldReads=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.bank&&k==='pointer10')captured=true;if(captured&&o===descriptorBytes&&String(k)==='12')oldReads++;return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'scene pointer00 dereference is null');}finally{Object.getOwnPropertyDescriptor=native;}
  check(oldReads>0&&x.classes.jobj[4]===0,'null scene captured before old0c load and only then dereferenced');
 }
 for(const nonnullOld of [false,true]){
  const x=fresh(),descriptor=x.allocator.readPointer(x.child,0xe0)!;
  (x.resourceTable as {14:object|null})[14]=null;if(nonnullOld)x.allocator.writePointer(descriptor,0x0c,x.child);
  refuses(()=>x.frame.runFrame(),nonnullOld?'8024fd74':'selected record pointer00 dereference is null');
  check(x.classes.jobj[4]===0,'nullable selected record preserves oldjoint gate ordering');
 }
 const heapFixture=()=>{
  const x=fresh(),next:SourceJObjFreeBlock={0:null},head:SourceJObjFreeBlock={0:next},entry:SourceJObjMemoryEntry={8:2,12:head};
  const heap={count80436a0c:5,table80436a08:{4:entry}};
  Object.assign(x.resourceSources,{heapGlobals:heap});return Object.assign(x,{heap,entry,head,next});
 };
 {
  const x=heapFixture();refuses(()=>x.frame.runFrame(),'8025d0fc memset');
  check(x.entry[12]===x.next&&x.entry[8]===1&&x.head[0]===x.next,'pop preserves original head contents');
  check(x.classes.jobj[32]===1&&x.classes.jobj[36]===1,'real current/max accounting');
 }
 {
  const x=heapFixture();Object.defineProperty(x.entry,8,{writable:false});refuses(()=>x.frame.runFrame(),'writable source');
  check(x.entry[12]===x.next&&x.entry[8]===2&&x.classes.jobj[32]===0,'readonly count preserves prior head pop only');
 }
 {
  const x=heapFixture();x.entry[8]=0;refuses(()=>x.frame.runFrame(),'8025d0fc memset');check(x.entry[8]===0xffffffff,'raw free count wraps');
 }
 {
  const x=heapFixture(),secondHead={0:null},secondEntry={8:7,12:secondHead},secondTable={4:secondEntry};
  const native=Object.getOwnPropertyDescriptor;let loads=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.heap&&k==='table80436a08'&&++loads===2)(x.heap as {table80436a08:object}).table80436a08=secondTable;return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'8025d0fc memset');}finally{Object.getOwnPropertyDescriptor=native;}
  check(loads===2&&secondEntry[12]===null&&secondEntry[8]===6&&x.entry[12]===x.head,'fresh table reload selects actual returned entry');
 }
 {
  const x=heapFixture(),native=Object.getOwnPropertyDescriptor;let caught=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(!caught&&o===x.entry&&String(k)==='8'){caught=true;try{x.frame.runFrame();}catch{}}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'private exact');}finally{Object.getOwnPropertyDescriptor=native;}
  check(caught&&x.entry[12]===x.next&&x.entry[8]===2,'caught parent reentry after pop prevents decrement');
 }
 {
  const x=heapFixture();(x.entry as {12:object})[12]=x.classes.jobj;refuses(()=>x.frame.runFrame(),'alias');check(x.entry[8]===2,'heap block alias refuses before pop');
 }
 {
  const x=heapFixture(),native=Object.getOwnPropertyDescriptor;let popped=false,currentReads=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.entry&&String(k)==='8')popped=true;
   if(popped&&o===x.classes.jobj&&String(k)==='32'&&++currentReads===3)x.classes.jobj[32]=9;
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'8025d0fc memset');}finally{Object.getOwnPropertyDescriptor=native;}
  check(currentReads===3&&x.classes.jobj[32]===9&&x.classes.jobj[36]===9,'class max compares freshly reloaded current');
 }
 const storageFixture=()=>{const x=heapFixture(),bytes=new Uint8Array(136).fill(0xa5);x.head.bytes=bytes;return Object.assign(x,{bytes});};
 {
  const x=storageFixture();refuses(()=>x.frame.runFrame(),'8024f638 JObjLoad');
  const data=new DataView(x.bytes.buffer);
  check(x.head[0]===x.classes.jobj&&x.entry[12]===x.next,'same allocated identity receives real class pointer');
  check(data.getUint32(0x14)===0x40&&[0x2c,0x30,0x34].every(k=>data.getFloat32(k)===1),'actual JObjInit flags/scales');
  check(x.bytes.every((v,i)=>[0x17,0x2c,0x2d,0x30,0x31,0x34,0x35].includes(i)||v===0),'real memset clears original nonzero bytes');
 }
 {
  const x=storageFixture();Object.defineProperty(x.head,0,{writable:false});refuses(()=>x.frame.runFrame(),'writable pointer overlay');
  check(x.bytes.every(v=>v===0xa5)&&x.entry[12]===x.next&&x.classes.jobj[32]===1,'readonly overlay refuses logical clear after allocation');
 }
 {
  const x=storageFixture();x.head.bytes=new Uint8Array(135);refuses(()=>x.frame.runFrame(),'exact136-byte');
  check(x.bytes.every(v=>v===0xa5)&&x.entry[8]===1,'invalid bytes lazy after real allocation');
 }
 {
  const x=storageFixture(),native=Object.getOwnPropertyDescriptor;let injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.head&&k==='bytes'&&!injected){injected=true;try{x.frame.runFrame();}catch{}}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'private exact');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&x.bytes.every(v=>v===0xa5)&&x.head[0]===x.next,'caught parent reentry before memset prevents clear');
 }
 {
  const x=storageFixture(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.head&&k==='bytes'&&!changed){changed=true;x.classes.parent[44]=0;}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'unselected class method2c');}finally{Object.getOwnPropertyDescriptor=native;}
  check(x.head[0]===x.classes.jobj&&x.bytes.every(v=>v===0),'real clear/class store precedes live parent initializer refusal');
 }
 {
  const x=storageFixture();Object.assign(x.head,{20:0});refuses(()=>x.frame.runFrame(),'scalar shadow');
  check(x.bytes.every(v=>v===0xa5),'numeric shadows never become second scalar owners');
 }
 {
  const x=storageFixture();x.head.bytes=new Uint8Array(new SharedArrayBuffer(136));refuses(()=>x.frame.runFrame(),'nonshared allocated buffer');
  check(x.head[0]===x.next,'shared backing rejected before memset overlay');
 }
 {
  const x=storageFixture();structuredClone(x.bytes.buffer,{transfer:[x.bytes.buffer]});refuses(()=>x.frame.runFrame(),'exact136-byte');
  check(x.head[0]===x.next&&x.entry[8]===1,'detached storage rejected lazily after allocation');
 }
 {
  const x=storageFixture(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.classes.parent&&String(k)==='44'&&x.head[0]===x.classes.jobj&&!changed){changed=true;x.head.bytes=new Uint8Array(136);}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'storage changed');}finally{Object.getOwnPropertyDescriptor=native;}
  check(changed&&x.bytes.every(v=>v===0),'late backing replacement blocks JObjInit after clear/class store');
 }
 for(const target of ['fill','setUint32','setFloat32','constructor']as const){
  const x=storageFixture(),descriptor=Object.getOwnPropertyDescriptor,fill=Uint8Array.prototype.fill,uint=DataView.prototype.setUint32,float=DataView.prototype.setFloat32,View=DataView;
  let installed=false,calls=0;
  const attemptedReentry=()=>{calls++;try{x.frame.runFrame();}catch{}};
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.head&&k==='bytes'&&!installed){installed=true;
    if(target==='fill')Uint8Array.prototype.fill=function(value:number,start?:number,end?:number){attemptedReentry();return fill.call(this,value,start,end);};
    if(target==='setUint32')DataView.prototype.setUint32=function(offset:number,value:number,little?:boolean){attemptedReentry();return uint.call(this,offset,value,little);};
    if(target==='setFloat32')DataView.prototype.setFloat32=function(offset:number,value:number,little?:boolean){attemptedReentry();return float.call(this,offset,value,little);};
    if(target==='constructor')globalThis.DataView=function(buffer:ArrayBufferLike,offset?:number,length?:number){attemptedReentry();return new View(buffer,offset,length);}as unknown as DataViewConstructor;
   }
   return descriptor(o,k);
  })as typeof descriptor;
  try{refuses(()=>x.frame.runFrame(),'8024f638 JObjLoad');}finally{Object.getOwnPropertyDescriptor=descriptor;Uint8Array.prototype.fill=fill;DataView.prototype.setUint32=uint;DataView.prototype.setFloat32=float;globalThis.DataView=View;}
  check(installed&&calls===0&&x.head[0]===x.classes.jobj,'captured '+target+' cannot become a post-check callback');
  check(new View(x.bytes.buffer).getUint32(0x14)===0x40,'actual native stores still execute');
 }
 const leafFixture=()=>{
  const x=storageFixture(),descriptorBytes=new Uint8Array(64),view=new DataView(descriptorBytes.buffer);
  for(const offset of [8,12,16,24,120,128,132])Object.defineProperty(x.head,offset,{value:null,writable:true,configurable:true,enumerable:true});
  for(const [offset,value]of [[0x14,2],[0x18,3],[0x1c,4],[0x20,5],[0x24,6],[0x28,7],[0x2c,8],[0x30,9],[0x34,10]])view.setFloat32(offset!,value!,false);
  Object.assign(x.jointDescriptor,{bytes:descriptorBytes,dobj10:null,robj3c:null,inverse38:null,child08:null,sibling0c:null,address32:0x1000});
  const idEntry={0:null,4:0x1000,8:null as object|null},idTable={[4*(0x1000%101)]:idEntry};
  Object.assign(x.resourceSources,{identityConstants:{float8043ca68:1,float8043ca6c:0},idTable803fa55c:idTable});
  return Object.assign(x,{descriptorBytes,descriptorView:view,idEntry,idTable});
 };
 {
  const x=leafFixture();refuses(()=>x.frame.runFrame(),'8007e150');const view=new DataView(x.bytes.buffer);
  check([2,3,4,5,6,7,8,9,10].every((v,i)=>view.getFloat32([0x1c,0x20,0x24,0x2c,0x30,0x34,0x38,0x3c,0x40][i]!)===v),'source raw transform copies');
  check(Array.from({length:12},(_,i)=>view.getFloat32(0x44+4*i)).every((v,i)=>v===(i===0||i===5||i===10?1:0)),'actual paired Identity order completes');
  check((x.head as unknown as Record<number,unknown>)[24]===null&&(x.head as unknown as Record<number,unknown>)[128]===null,'real null-descriptor helper results stored');
 }
 {
  const x=leafFixture();Object.assign(x.jointDescriptor,{dobj10:{}});refuses(()=>x.frame.runFrame(),'nonnull DObjLoadDesc');
  check(new DataView(x.bytes.buffer).getFloat32(0x2c)===1,'mandatory nonnull helper not skipped and transforms not copied');
 }
 {
  const x=leafFixture();Object.assign(x.jointDescriptor,{robj3c:{}});refuses(()=>x.frame.runFrame(),'nonnull RObjLoadDesc');
  check(new DataView(x.bytes.buffer).getFloat32(0x2c)===1,'RObj boundary before transform writes');
 }
 {
  const x=leafFixture();delete (x.jointDescriptor as {bytes?:Uint8Array}).bytes;refuses(()=>x.frame.runFrame(),'bytes: own data');
  check((x.head as unknown as Record<number,unknown>)[16]===null&&new DataView(x.bytes.buffer).getUint32(0x14)===0x40,'missing descriptor bytes preserves earlier pointer clears/JObjInit');
 }
 {
  const x=leafFixture(),native=Object.getOwnPropertyDescriptor;let changed=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===x.jointDescriptor&&k==='robj3c'&&!changed){changed=true;x.normalizeProcessor.gqr0=1;}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'Identity explicit GQR0');}finally{Object.getOwnPropertyDescriptor=native;}
  check(new DataView(x.bytes.buffer).getFloat32(0x40)===10&&new DataView(x.bytes.buffer).getUint32(0x44)===0,'invalid profile refuses only at Identity after transform copies');
 }
 {
  const x=leafFixture();Object.defineProperty(x.idEntry,8,{writable:false});refuses(()=>x.frame.runFrame(),'writable source');
  check(x.idEntry[4]===0x1000&&x.idEntry[8]===null&&(x.head as unknown as Record<number,unknown>)[132]===null,'ID key store precedes failed value store and descriptor84 remains unstored');
 }
 {
  const x=leafFixture();(x.idTable as Record<number,object|null>)[4*(0x1000%101)]=null;refuses(()=>x.frame.runFrame(),'802572f0');
  check((x.head as unknown as Record<number,unknown>)[132]===null,'fresh ID entry is not fabricated');
 }
 {
  const x=leafFixture();Object.assign(x.jointDescriptor,{child08:{}});refuses(()=>x.frame.runFrame(),'child allocation unsupported');
  check(x.idEntry[8]===x.head&&(x.head as unknown as Record<number,unknown>)[132]===x.jointDescriptor,'actual ID update and descriptor store precede unsupported child');
 }
 {
  const x=leafFixture(),descriptor=x.allocator.readPointer(x.child,0xe0)!;
  refuses(()=>getSourceProjectileResourceJointPointer(x.allocator,x.resource,x.head,{}),'private exact');
  refuses(()=>getSourceProjectileResourceJointPointer({}as typeof x.allocator,x.resource,x.head,{}),'genuine resource');
  refuses(()=>getSourceProjectileResourceJointPointer(x.allocator,x.resource,{},{}),'private exact');
  refuses(()=>completeSourceProjectileResourceDescriptor(x.allocator,x.resource,x.head,Symbol('wrong descriptor'),{}),'private exact');
  refuses(()=>x.frame.runFrame(),'8007e150');
  const pointer=x.allocator.readPointer(descriptor,0xc)!;
  check(pointer!==null&&x.allocator.getPointerTarget(pointer)===x.head,'actual6fb4 stores exact allocated JObj identity');
  check(x.allocator.readU32(descriptor,0x14)===14&&x.allocator.readU8(descriptor,0xb)===0&&x.allocator.readU8(descriptor,0x10)===1,'actual6fb4 four stores complete in source widths');
  refuses(()=>getSourceProjectileResourceJointPointer(x.allocator,x.resource,x.head,{}),'incomplete');
 }
 {
  const x=leafFixture(),descriptor=x.allocator.readPointer(x.child,0xe0)!,bytes=x.allocator.getDescriptor(descriptor),native=Object.getOwnPropertyDescriptor;let injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(o===bytes&&String(k)==='12'&&x.idEntry[8]===x.head&&!injected){injected=true;try{x.frame.runFrame();}catch{}}return native(o,k);})as typeof native;
  try{refuses(()=>x.frame.runFrame(),'caught same-runtime reentry');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&x.allocator.readPointer(descriptor,0xc)===null&&x.idEntry[8]===x.head,'caught late parent reentry preserves completed ID but prevents descriptor pointer store');
 }
 {
  const x=leafFixture();delete (x.jointDescriptor as {sibling0c?:null}).sibling0c;refuses(()=>x.frame.runFrame(),'sibling0c: own data');
  check(x.idEntry[8]===x.head,'Resolve reads descriptor sibling even when joint sibling null');
 }
 {
  const x=leafFixture(),native=Object.getOwnPropertyDescriptor,freeze=Object.freeze;let armed=false,exposed=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.head&&k==='bytes'&&!armed){armed=true;Object.freeze=((value:object)=>{if(value!==null&&typeof value==='object'&&!Array.isArray(value)&&Reflect.ownKeys(value).length===0)exposed++;return freeze(value);})as typeof freeze;}
   return native(o,k);
  })as typeof native;
  try{refuses(()=>x.frame.runFrame(),'8007e150');}finally{Object.getOwnPropertyDescriptor=native;Object.freeze=freeze;}
  check(armed&&exposed===0,'private joint token never passes through replaceable freeze');
 }
 console.log(`[projectile-resource] PASS ${count}: genuine nonnull descriptor, source class initialization/inheritance, allocator barrier and failure prefixes`);
}
