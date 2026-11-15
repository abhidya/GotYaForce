import {captureMissingLeaderIngress} from './battle-leader-ingress.selftest.js';
import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {requireSourceObjectSchedulerSnapshot} from './source-object-scheduler.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const axes=['x','y','z'] as const,next='pointer38: own data property required';
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-secondary-nonnull-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):void {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);}
function bits(value:number):number {const v=new DataView(new ArrayBuffer(4));v.setFloat32(0,value,false);return v.getUint32(0,false);}
function number(word:number):number {const v=new DataView(new ArrayBuffer(4));v.setUint32(0,word,false);return v.getFloat32(0,false);}
/** Explicit bounded synthetic six-row graph, not retail actor hydration. The
 * empty genuine selector leaves primary508 null; secondary c8 independently
 * names an original registered OBJECT. Actualcc is a different opaque record. */
function fixture(make:Make) {
 const x=createActorThirdPassTestFixture(make);let dereferences=0;
 const cc={};for(const key of ['x','y','z','pos','eligibility83'])Object.defineProperty(cc,key,{get(){dereferences++;throw Error('opaque cc');}});
 Reflect.set(x.sourceActor,'visibilityTarget',cc);x.admissionState.pointerc8=x.bytes;
 Object.assign(x.pos,{x:5,y:6,z:7});
 return Object.assign(x,{cc,dereferences:()=>dereferences});
}
type Fixture=ReturnType<typeof fixture>;
function trace(x:Fixture,part=next,before:Visit=()=>{},after?:Visit):string[] {
 const leaderPrefix=captureMissingLeaderIngress(x);
 const native=Object.getOwnPropertyDescriptor,events:string[]=[];let secondary=false;
 Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{
  leaderPrefix.observe(owner,key);
  if(owner===x.sourceActor&&key==='visibilityTarget')secondary=true;
  if(secondary) {
   if(owner===x.admissionState&&key==='pointerc8')events.push('c8');
   if(owner===x.bytes&&/^\d+$/.test(String(key))&&Number(key)>=100&&Number(key)<112)events.push('byte'+String(key));
   if(owner===x.aim&&axes.includes(key as typeof axes[number]))events.push('aim'+String(key));
   if(owner===x.pos&&axes.includes(key as typeof axes[number]))events.push('pos'+String(key));
   if(owner===x.sourceActor&&['targetDistance760','horizontalDistance764'].includes(String(key)))events.push(String(key));
   if(owner===x.processor&&key==='gqr0')events.push('gqr0');
   before(owner,key);
  }
  const result=native(owner,key);if(secondary)after?.(owner,key);return result;
 }) as typeof native;
 try{refuses(()=>x.frame.runFrame(),part);}finally{Object.getOwnPropertyDescriptor=native;}
 if(part===next)leaderPrefix.assert();
 equal(x.dereferences(),0,'actual cc never dereferenced');equal(x.sourceActor.targetDistance758,20000,'primary758 retained');
 equal(x.sourceActor.horizontalDistance75c,20000,'primary75c retained');
 check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'caller terminally closed');
 refuses(()=>x.frame.runFrame(),'permanently incomplete');refuses(()=>x.allocator.assertActorComplete(x.actor),'incomplete');
 refuses(()=>x.scheduler.runGroup(9),'exclusively owned');refuses(()=>requireSourceObjectSchedulerSnapshot(x.scheduler,x.allocator,x.child),'private active');
 return events;
}
function aim(x:Fixture,values:readonly number[]):void {axes.forEach((key,i)=>equal(x.aim[key],values[i],`aim ${key} exact prefix`));}
function distances(x:Fixture,total=61,horizontal=63):void {equal(x.sourceActor.targetDistance760,total,'760 prefix');equal(x.sourceActor.horizontalDistance764,horizontal,'764 prefix');}
/** Recompute each last public metadata observation from an unmodified graph,
 * then inject the fault there on a fresh graph. Merely checking that a later
 * error occurs would miss a pending store that escaped before that error. */
function terminalObservationTests(create:()=>Fixture):void {
 const keys=['x','y','z','targetDistance760','horizontalDistance764'] as const;
 const old=[-51,-52,-53,61,63],done=[5,6,7,0,0];
 const run=(x:Fixture,expected:string,at=-1,mutate:()=>void=()=>{}):number[]=>{
  const descriptor=Object.getOwnPropertyDescriptor,descriptors=Object.getOwnPropertyDescriptors,native=Reflect.getOwnPropertyDescriptor;
  let count=0,index=0,hit=false;const last:number[]=[];
  const observation=():void=>{
   if(index<keys.length&& !Object.is(native(index<3?x.aim:x.sourceActor,keys[index]!)?.value,old[index])) {
    last[index]=count;index++;
   }
   count++;if(count===at){hit=true;mutate();}
  };
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{observation();return descriptor(owner,key);}) as typeof descriptor;
  Object.getOwnPropertyDescriptors=((owner:object)=>{observation();return descriptors(owner);}) as typeof descriptors;
  try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=descriptor;Object.getOwnPropertyDescriptors=descriptors;}
  if(at>=0)check(hit,'last public observation replay reached');
  check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'terminal replay closes caller');
  return last;
 };
 const baseline=run(create(),next);equal(baseline.length,5,'observed all five nonnull stores');
 for(let index=0;index<keys.length;index++)for(const kind of ['direct','nested','numeric','selected-reference','selected-alias','position-field','position-numeric'] as const) {
  if(index<3&&kind.startsWith('position-'))continue;
  const x=create();run(x,'secondary terminal',baseline[index],()=>{
   if(kind==='direct')Reflect.set(x.outerSources,'pointerc8',x.bytes);
   else if(kind==='nested')Reflect.set(x.outerSources,'lateNestedOwner',{pointerc8:x.bytes});
   else if(kind==='numeric')Reflect.set(x.sourceActor,'200',x.bytes);
   else if(kind==='selected-reference')Reflect.set(x.outerSources,'lateSelected',x.vector);
   else if(kind==='selected-alias')Reflect.set(x.sourceActor,'field50c',0);
   else Reflect.set(x.sourceActor,kind==='position-field'?'field20':'32',0);
  });
  keys.forEach((key,i)=>equal(Reflect.getOwnPropertyDescriptor(i<3?x.aim:x.sourceActor,key)?.value,
   i<index?done[i]:old[i],`${kind} terminal ${keys[index]} preserves exact completed prefix`));
 }
}
export function runActorSecondaryNonnullSelfTests(make:Make):void {
 let fixtures=0;const create=()=>{fixtures++;return fixture(make);};
 {
  const x=create(),events=trace(x);
  const byte=(offset:number)=>Array.from({length:4},(_,i)=>'byte'+(offset+i));
  equal(events.join(','),['c8',...byte(100),...byte(104),'aimx','aimy',...byte(108),'aimz',
   'gqr0','posy','posz','gqr0',...byte(104),...byte(108),'gqr0','posx','posy','gqr0',...byte(100),...byte(104),
   'targetDistance760','posx',...byte(100),'posz',...byte(108),'horizontalDistance764'].join(','),'exact integer-copy / paired distance / scalar X X Z Z sequence');
  aim(x,[5,6,7]);distances(x,0,0);
 }
 // Registered descriptor memory is not an OBJECT, even with valid XYZ bytes.
 {
  const x=create(),descriptor={...x.bytes};x.allocator.registerDescriptor(Symbol('synthetic descriptor'),descriptor);
  x.admissionState.pointerc8=descriptor;
  const events=trace(x,'unknown/non-owned object identity');aim(x,[-51,-52,-53]);distances(x);
  equal(events.includes('aimx'),false,'non-OBJECT rejected before first aim admission');
 }
 // Capture is once, and X/Y integer loads precede any destination admission.
 {
  const x=create();let yLoaded=false,zLoaded=false;
  trace(x,next,(owner,key)=>{
   if(owner===x.bytes&&key==='107')yLoaded=true;
   if(owner===x.aim&&key==='x') {check(yLoaded,'Y loaded before first store');x.admissionState.pointerc8=null;x.sourceActor.visibilityTarget=null;}
   if(owner===x.aim&&key==='y') {equal(x.aim.x,5,'X completed before Y');const word=bits(9);for(let i=0;i<4;i++)x.bytes[0x6c+i]=(word>>>(24-8*i))&255;x.pos.z=9;}
   if(owner===x.bytes&&key==='108'&&!zLoaded) {zLoaded=true;equal(x.aim.y,6,'Y completed before Z load');}
  });aim(x,[5,6,9]);distances(x,0,0);
 }
 for(const word of [0,0x80000000,1,0x80000001,0x007fffff,0x00800000,0x3f800001,0x7f7fffff,0xff7fffff]) {
  const x=create(),value=number(word);x.allocator.writeU32(x.id,0x64,word);x.pos.x=value;
  trace(x);equal(bits(x.aim.x),word,'finite copied X bit pattern preserved');distances(x,0,0);
 }
 for(const index of [0,1,2])for(const word of [0x7f800000,0xff800000,0x7fc00001,0x7f800001,0xffffffff]) {
  const x=create();x.allocator.writeU32(x.id,0x64+index*4,word);
  const events=trace(x,'unsupported nonfinite integer-copy bits');
  aim(x,index===0?[-51,-52,-53]:index===1?[5,-52,-53]:[5,6,-53]);distances(x);
  check(events.includes('byte107'),'Y integer operand loaded even when X bits unsupported');
  equal(events.includes('byte108'),index===2,'Z not prevalidated before earlier stores');
 }
 {
  const x=create();x.pos.x=2;trace(x,'8006b218');aim(x,[5,6,7]);distances(x);
 }
 {
  const x=create();let seen=false;
  trace(x,'8006b298',(owner,key)=>{if(owner===x.sourceActor&&key==='targetDistance760'){seen=true;x.pos.x=2;}});
  check(seen,'total zero store reached');aim(x,[5,6,7]);distances(x,0);
 }
 for(const index of [0,1,2]) {
  const x=create();let hit=false;
  trace(x,'byte',(owner,key)=>{if(!hit&&owner===x.bytes&&key===String(0x64+index*4)) {hit=true;Reflect.set(owner,key,256);}});
  check(hit,'reached raw byte load fault');aim(x,index<2?[-51,-52,-53]:[5,6,-53]);distances(x);
 }
 for(const key of ['pointerC8','fieldc8','bytec8','pointerc8','200']) {
  const x=create();trace(x,'competing',(owner,field)=>{if(owner===x.sourceActor&&field==='visibilityTarget')Reflect.set(x.sourceActor,key,0);});aim(x,[-51,-52,-53]);distances(x);
 }
 for(const site of ['outer','root'] as const) {
  const x=create();Reflect.set(site==='outer'?x.outerSources:x.rootSources,'pointerc8',x.bytes);
  trace(x,'competing secondary canonical source storage');aim(x,[-51,-52,-53]);distances(x);
 }
 for(const axis of axes)for(const kind of ['readonly','missing','accessor','alias','replace','incomplete','reentry','admission'] as const) {
  const x=create();let hit=false,invoked=0;
  trace(x,kind==='alias'?'alias':kind==='replace'?'aimOrigin518':kind==='incomplete'||kind==='admission'?'incomplete':kind==='reentry'?'reentry':axis,(owner,key)=>{
   if(hit||owner!==x.aim||key!==axis)return;hit=true;
   if(kind==='readonly')Object.defineProperty(owner,key,{writable:false});
   else if(kind==='missing')Reflect.deleteProperty(owner,key);
   else if(kind==='accessor')Object.defineProperty(owner,key,{get(){invoked++;return 0;},set(){invoked++;},configurable:true});
   else if(kind==='alias')Reflect.set(x.sourceActor,'motion',x.aim);
   else if(kind==='replace')Reflect.set(x.sourceActor,'aimOrigin518',{x:0,y:0,z:0});
   else if(kind==='incomplete')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
   else if(kind==='reentry')refuses(()=>x.frame.runFrame(),'reentry');
   else refuses(()=>x.commandAdmission.dispatchSubtypeDirection(x.actor),'signed585');
  });check(hit,'reached aim store mutation');equal(invoked,0,'accessors never invoked');distances(x);
  const old=[-51,-52,-53],expected=[5,6,7],at=axes.indexOf(axis);
  axes.forEach((key,i)=>{if(i!==at)equal(x.aim[key],i<at?expected[i]:old[i],'prior stores survive');});
 }
 // Mutation after the public final snapshot must not cross the retained native
 // own-data descriptor check. No getter/setter is invoked by the pending store.
 for(const axis of axes)for(const kind of ['readonly','missing','accessor'] as const) {
  const x=create(),native=Object.getOwnPropertyDescriptors;let admitted=false,hit=false,invoked=0;
  Object.getOwnPropertyDescriptors=((owner:object)=>{
   const fields=native(owner);if(owner!==x.aim)return fields;let enumerated=false;
   return new Proxy(fields,{ownKeys(target){enumerated=true;return Reflect.ownKeys(target);},get(target,key,receiver){
    if(admitted&&!enumerated&&!hit&&key===axis){hit=true;
     if(kind==='readonly')Object.defineProperty(owner,key,{writable:false});
     else if(kind==='missing')Reflect.deleteProperty(owner,key);
     else Object.defineProperty(owner,key,{get(){invoked++;return 0;},set(){invoked++;},configurable:true});
    }return Reflect.get(target,key,receiver);
   }});
  }) as typeof native;
  try{trace(x,axis,(owner,key)=>{if(owner===x.aim&&key===axis)admitted=true;});}finally{Object.getOwnPropertyDescriptors=native;}
  check(hit,'terminal descriptor mutation reached');equal(invoked,0,'terminal accessor remains untouched');distances(x);
 }
 for(const site of ['pos','processor','data'] as const) {
  const x=create();let hit=false;
  trace(x,site==='processor'?'GQR0':site==='data'?'float80437658':'position',(owner,key)=>{
   if(!hit&&owner===x.aim&&key==='z'){hit=true;
    if(site==='pos')Reflect.set(x.sourceActor,'pos',{x:5,y:6,z:7});
    else if(site==='processor')Reflect.set(x.processor,'gqr0',1);
    else Reflect.set(x.data,'float80437658',-0);
   }
  });check(hit,'post-copy dependency fault reached');aim(x,[5,6,7]);distances(x);
 }
 terminalObservationTests(create);
 console.log(`[actor-secondary-nonnull] PASS (${fixtures} bounded synthetic graph fixtures): captured c8, opaque actual cc, ordered integer-copy bits, canonical aim ownership, total/horizontal zero stores and unsupported positive estimator barriers, partial-store and terminal closure; absent27764 row38 remains blocked after the third RNG draw, no full-frame claim`);
}
