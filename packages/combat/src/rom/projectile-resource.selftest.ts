import {createProjectileInitializerTailTestFixture} from './projectile-initializer-tail.selftest.js';
import {createSourceProjectileResourceRuntime,invokeSourceProjectileResource,type SourceJObjClassFields} from './projectile-resource.js';
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
 console.log(`[projectile-resource] PASS ${count}: genuine nonnull descriptor, source class initialization/inheritance, allocator barrier and failure prefixes`);
}
