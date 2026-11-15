import {captureMissingLeaderIngress} from './battle-leader-ingress.selftest.js';
import {createActorThirdPassTestFixture} from './actor-third-pass.selftest.js';
import {hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {refineSourceTargetDistance,readSourceTargetDistance,sourceTargetDistanceSeed} from './source-target-distance.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';

type Make=typeof createBattleTargetPreparationTestFixture;
type Visit=(owner:object,key:PropertyKey)=>void;
const next='pointer38: own data property required',half='double80437660',three='double80437668';
const axes=['x','y','z'] as const;
function check(ok:boolean,why:string):void {if(!ok)throw Error(`[actor-secondary-positive-test] ${why}`);}
function equal(a:unknown,b:unknown,why:string):void {check(Object.is(a,b),`${why}: got ${String(a)}, expected ${String(b)}`);}
function refuses(run:()=>unknown,part:string):void {let message='';try{run();}catch(error){message=String(error);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);}
function f64(value:number):string {const v=new DataView(new ArrayBuffer(8));v.setFloat64(0,value,false);return v.getBigUint64(0,false).toString(16).padStart(16,'0');}
function decode(value:string):number {const v=new DataView(new ArrayBuffer(8));v.setBigUint64(0,BigInt('0x'+value),false);return v.getFloat64(0,false);}
function f32(value:number):number {const v=new DataView(new ArrayBuffer(4));v.setFloat32(0,value,false);return v.getUint32(0,false);}
function decode32(value:number):number {const v=new DataView(new ArrayBuffer(4));v.setUint32(0,value,false);return v.getFloat32(0,false);}
// Independent integer/Fraction RN-even oracle, transcribed from the retained
// feasibility proof. No production helper generated these exact-bit expectations.
// Evidence: target-refinement-feasibility report/verify.py/results.json, and
// terrain-orientation-evidence-2026-11-13.md:333–389 for model-backed seeds only.
const expected=[{"square":0.25,"seed":"3ffffe8000000000","rounds":[{"q":"400ffd0012000000","h":"3feffe8000000000","c":"400000bffb800000","e":"3fffffffe5006c00"},{"q":"400fffffca00d817","h":"3fefffffe5006c00","c":"400000000d7fc9fa","e":"3fffffffffffffdd"},{"q":"400fffffffffffba","h":"3fefffffffffffdd","c":"4000000000000012","e":"4000000000000000"}],"product":"3fe0000000000000","frsp":"3f000000","stack_reload_f64":"3fe0000000000000"},{"square":1,"seed":"3feffe8000000000","rounds":[{"q":"3feffd0012000000","h":"3fdffe8000000000","c":"400000bffb800000","e":"3fefffffe5006c00"},{"q":"3fefffffca00d817","h":"3fdfffffe5006c00","c":"400000000d7fc9fa","e":"3fefffffffffffdd"},{"q":"3fefffffffffffba","h":"3fdfffffffffffdd","c":"4000000000000012","e":"3ff0000000000000"}],"product":"3ff0000000000000","frsp":"3f800000","stack_reload_f64":"3ff0000000000000"},{"square":4,"seed":"3fdffe8000000000","rounds":[{"q":"3fcffd0012000000","h":"3fcffe8000000000","c":"400000bffb800000","e":"3fdfffffe5006c00"},{"q":"3fcfffffca00d817","h":"3fcfffffe5006c00","c":"400000000d7fc9fa","e":"3fdfffffffffffdd"},{"q":"3fcfffffffffffba","h":"3fcfffffffffffdd","c":"4000000000000012","e":"3fe0000000000000"}],"product":"4000000000000000","frsp":"40000000","stack_reload_f64":"4000000000000000"},{"square":16,"seed":"3fcffe8000000000","rounds":[{"q":"3faffd0012000000","h":"3fbffe8000000000","c":"400000bffb800000","e":"3fcfffffe5006c00"},{"q":"3fafffffca00d817","h":"3fbfffffe5006c00","c":"400000000d7fc9fa","e":"3fcfffffffffffdd"},{"q":"3fafffffffffffba","h":"3fbfffffffffffdd","c":"4000000000000012","e":"3fd0000000000000"}],"product":"4010000000000000","frsp":"40800000","stack_reload_f64":"4010000000000000"},{"square":64,"seed":"3fbffe8000000000","rounds":[{"q":"3f8ffd0012000000","h":"3faffe8000000000","c":"400000bffb800000","e":"3fbfffffe5006c00"},{"q":"3f8fffffca00d817","h":"3fafffffe5006c00","c":"400000000d7fc9fa","e":"3fbfffffffffffdd"},{"q":"3f8fffffffffffba","h":"3fafffffffffffdd","c":"4000000000000012","e":"3fc0000000000000"}],"product":"4020000000000000","frsp":"41000000","stack_reload_f64":"4020000000000000"}] as const;
export function runSourceTargetDistanceRefinementSelfTests():void {
 for(const row of expected) {
  equal(f64(sourceTargetDistanceSeed(row.square)!),row.seed,'production selector uses authenticated estimate bits');
  const result=refineSourceTargetDistance(row.square,decode(row.seed),.5,3);
  equal(f64(result.seed),row.seed,'model-backed estimate seed bits');
  equal(result.rounds.length,3,'three binary64 source rounds');
  for(let i=0;i<3;i++)for(const key of ['q','h','c','e'] as const)
   equal(f64(result.rounds[i]![key]),row.rounds[i]![key],`s=${row.square} round${i} ${key}`);
  equal(f64(result.product),row.product,'final binary64 product');
  equal(f32(result.value).toString(16).padStart(8,'0'),row.frsp,'frsp and stack reload f32');
  equal(f64(result.value),row.stack_reload_f64,'stack reload double representation');
  for(const address of ['8006afbc','8006b03c','8006b218','8006b298'] as const)
   equal(readSourceTargetDistance(row.square,{fpscrControl:0},{[half]:.5,[three]:3},()=>{},address),result.value,'both estimator PCs');
  // Round two ALREADY has the same final f32. A final-value-only test cannot
  // kill dropping round three, exact-root substitution or alternate exact seed.
  equal(Math.fround(row.square*result.rounds[1]!.e),result.value,'honest two-round final equivalence');
  check(f64(result.rounds[1]!.e)!==f64(result.rounds[2]!.e),'third round pinned by intermediate bits');
  check(Math.fround(row.square*decode(row.seed))!==result.value,'zero rounds distinguished');
  check(Math.fround(row.square*result.rounds[0]!.e)!==result.value,'one round distinguished');
  let single=decode(row.seed),badSquare=decode(row.seed);
  for(let i=0;i<3;i++) {
   const q=Math.fround(single*single),h=Math.fround(.5*single),c=-Math.fround(row.square*q-3);
   single=Math.fround(h*c);
   const badHalf=.5*badSquare,badCorrection=-(row.square*(badHalf*badHalf)-3);
   badSquare=badHalf*badCorrection;
  }
  check(Math.fround(row.square*single)!==result.value,'all-f32 refinement distinguished');
  check(Math.fround(row.square*badSquare)!==result.value,'squaring half estimate distinguished');
 }
 // Multiplication by the admitted powers of two is exact. Nonfused correction
 // and reassociations can be intermediate-equivalent here. Static source
 // schedule witnesses, not dishonest numeric mutation claims, protect them.
 console.log('[source-target-distance-refinement] PASS: five independent seed/three-round/product/frsp bit vectors; bounded model evidence, no console capture');
}
function fixture(make:Make,position:readonly number[]=[1,0,0]) {
 const x=createActorThirdPassTestFixture(make);let dereferences=0;
 const cc={};for(const key of ['x','y','z','pos'])Object.defineProperty(cc,key,{get(){dereferences++;throw Error('opaque cc dereference');}});
 Reflect.set(x.sourceActor,'visibilityTarget',cc);x.admissionState.pointerc8=x.bytes;
 for(let i=0;i<3;i++)x.allocator.writeU32(x.id,0x64+4*i,0);
 axes.forEach((axis,i)=>x.pos[axis]=position[i]!);
 Reflect.set(x.processor,'fpscrControl',0);Reflect.set(x.data,half,.5);Reflect.set(x.data,three,3);
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
   if(owner===x.data&&[half,three,'float80437658'].includes(String(key)))events.push(String(key));
   if(owner===x.pos&&axes.includes(key as typeof axes[number]))events.push('A'+String(key));
   if(owner===x.bytes&&['100','104','108'].includes(String(key)))events.push('B'+String(key));
   if(owner===x.aim&&axes.includes(key as typeof axes[number]))events.push('aim'+String(key));
   if(owner===x.sourceActor&&['targetDistance760','horizontalDistance764'].includes(String(key)))events.push(String(key));
   before(owner,key);
  }
  const result=native(owner,key);if(secondary)after?.(owner,key);return result;
 }) as typeof native;
 try{refuses(()=>x.frame.runFrame(),part);}finally{Object.getOwnPropertyDescriptor=native;}
 if(part===next)leaderPrefix.assert();
 equal(x.dereferences(),0,'actual cc opaque');equal(x.sourceActor.targetDistance758,20000,'primary total sentinel unchanged');
 equal(x.sourceActor.horizontalDistance75c,20000,'primary horizontal sentinel unchanged');
 check(hasIncompleteSourceActorDoubleLifecycle(x.sourceActor),'refusal closes actor');
 refuses(()=>x.frame.runFrame(),'permanently incomplete');
 refuses(()=>x.scheduler.runGroup(9),'exclusively owned');
 return events;
}
function distances(x:Fixture,total=61,horizontal=63):void {
 equal(x.sourceActor.targetDistance760,total,'exact total partial store');equal(x.sourceActor.horizontalDistance764,horizontal,'exact horizontal partial store');
}
/** Positive/zero domains and actual computed-square candidates. Neither ideal
 * Euclidean classification nor an axis-only shortcut can admit these fixtures. */
function domainTests(create:(position?:readonly number[])=>Fixture):void {
 for(const m of [.5,1,2,4,8])for(const position of [[m,0,0],[0,m,0],[0,0,m],[m,m/8192,m/8192],[Math.fround(.6*m),0,Math.fround(.8*m)]]) {
  const x=create(position),events=trace(x);distances(x,m,position[0]===0&&position[2]===0?0:m);
  equal(events.filter(e=>e==='c8').length,1,'c8 captured once');
  const constants=events.filter(e=>e===half||e===three);
  equal(constants.join(','),[half,three,...(position[0]===0&&position[2]===0?[]:[half,three])].join(','),'half then three freshly loaded at each positive estimator');
  const store=events.indexOf('targetDistance760');
  equal(events.slice(store,store+6).join(','),['targetDistance760','float80437658','Ax','B100','Az','B108'].join(','),'total store then fresh zero, A.x B.x A.z B.z');
  axes.forEach(axis=>equal(x.aim[axis],0,'integer copy used OBJECT before numerical estimators'));
 }
 // Entire zero branch remains valid with all new optional data absent.
 {
  const x=create([0,0,0]);Reflect.deleteProperty(x.data,half);Reflect.deleteProperty(x.data,three);Reflect.deleteProperty(x.processor,'fpscrControl');
  const events=trace(x);distances(x,0,0);check(!events.includes(half)&&!events.includes(three),'zero branch constants stay lazy');
 }
 for(const [initial,later,total,horizontal] of [[[0,0,0],[1,0,0],0,1],[[1,0,0],[0,0,0],1,0],[[1,0,0],[4,0,0],1,4]] as const) {
  const x=create(initial);let changed=false;
  trace(x,next,(owner,key)=>{if(!changed&&owner===x.data&&key==='float80437658'&&x.sourceActor.targetDistance760!==61){changed=true;axes.forEach((axis,i)=>x.pos[axis]=later[i]!);x.admissionState.pointerc8=null;x.sourceActor.visibilityTarget=null;}});
  check(changed,'live coordinates changed after total store');distances(x,total,horizontal);
 }
 // Adjacent f32 positions yield unsupported neighboring actual square results,
 // and must refuse before loading any refinement constants or storing760.
 for(const m of [.5,1,2,4,8])for(const direction of [-1,1]) {
  const x=create([decode32(f32(m)+direction),0,0]),events=trace(x,'8006b218');distances(x);
  check(!events.includes(half)&&!events.includes(three),'unsupported total square before constants');
 }
 {
  const x=create();let changed=false;
  const events=trace(x,'8006b298',(owner,key)=>{if(!changed&&owner===x.data&&key==='float80437658'&&x.sourceActor.targetDistance760===1){changed=true;x.pos.x=decode32(f32(1)+1);}});
  check(changed,'unsupported horizontal square independently computed');distances(x,1);
  equal(events.filter(e=>e===half).length,1,'unsupported horizontal before second constant pair');
 }
}
function admissionTests(create:(position?:readonly number[])=>Fixture):void {
 for(const horizontal of [false,true])for(const key of [half,three,'fpscrControl'])for(const kind of ['missing','wrong','accessor'] as const) {
  const x=create();let invoked=0,changed=false;
  const mutate=()=>{changed=true;const owner=key==='fpscrControl'?x.processor:x.data;
   if(kind==='missing')Reflect.deleteProperty(owner,key);
   else if(kind==='wrong')Reflect.set(owner,key,key==='fpscrControl'?1:decode(key===half?'3fe0000000000001':'4008000000000001'));
   else Object.defineProperty(owner,key,{get(){invoked++;return 0;},configurable:true});
  };
  if(!horizontal)mutate();
  trace(x,key,(owner,field)=>{if(horizontal&&!changed&&owner===x.data&&field==='float80437658'&&x.sourceActor.targetDistance760===1)mutate();});
  check(changed,'admission mutation reached');equal(invoked,0,'accessor data not invoked');distances(x,horizontal?1:61);
 }
 for(const value of [undefined,true,-1,0x100000000,.5,NaN,...Array.from({length:8},(_,i)=>2**i)]) {
  const x=create();Reflect.set(x.processor,'fpscrControl',value);trace(x,'fpscrControl');distances(x);
 }
 {
  const x=create();Reflect.set(x.processor,'fpscrControl',0xffffff00);trace(x);distances(x,1,1);
  equal(Reflect.get(x.processor,'fpscrControl'),0xffffff00,'unmodeled status preserved');
 }
 // Changes after capturing a constant must not replace that live register.
 {
  const x=create();let count=0;
  trace(x,next,()=>{},(owner,key)=>{if(owner===x.data&&key===three){count++;Reflect.set(x.data,half,.25);if(count===1)Reflect.set(x.data,half,.5);}});
  distances(x,1,1);equal(count,2,'two actual three loads');
 }
 for(const site of ['total','horizontal'] as const)for(const kind of ['readonly','accessor','owner','alias','lifecycle','reentry'] as const) {
  const x=create();let hit=false,invoked=0;const destination=site==='total'?'targetDistance760':'horizontalDistance764';
  const expected=kind==='owner'?'processor':kind==='alias'?'competing':kind==='lifecycle'?'incomplete':kind==='reentry'?'reentry':destination;
  trace(x,expected,(owner,key)=>{if(hit||owner!==x.sourceActor||key!==destination)return;hit=true;
   if(kind==='readonly')Object.defineProperty(owner,key,{writable:false});
   else if(kind==='accessor')Object.defineProperty(owner,key,{get(){invoked++;return 0;},set(){invoked++;},configurable:true});
   else if(kind==='owner')Reflect.set(x.rootSources,'processor',{gqr0:0,fpscrControl:0});
   else if(kind==='alias')Reflect.set(x.outerSources,half,.5);
   else if(kind==='lifecycle')markIncompleteSourceActorDoubleLifecycle(x.sourceActor);
   else refuses(()=>x.frame.runFrame(),'reentry');
  });check(hit,'reached distance-store mutation');equal(invoked,0,'destination accessor never invoked');
  if(kind!=='accessor')distances(x,site==='horizontal'?1:61);
  else equal(site==='total'?x.sourceActor.horizontalDistance764:x.sourceActor.targetDistance760,site==='total'?63:1,'other distance preserved');
 }
}
/** Fault at each last observable metadata read, immediately before the native
 * terminal check. Checking eventual refusal alone would miss a leaked store. */
function terminalTests(create:(position?:readonly number[])=>Fixture):void {
 const keys=['targetDistance760','horizontalDistance764'] as const;
 const run=(x:Fixture,at=-1,mutate:()=>void=()=>{},part=next):number[]=>{
  const descriptor=Object.getOwnPropertyDescriptor,descriptors=Object.getOwnPropertyDescriptors,native=Reflect.getOwnPropertyDescriptor;
  let count=0,index=0,hit=false;const last:number[]=[];
  const observation=()=>{if(index<2&&native(x.sourceActor,keys[index]!)?.value===1){last[index]=count;index++;}count++;if(count===at){hit=true;mutate();}};
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{observation();return descriptor(owner,key);}) as typeof descriptor;
  Object.getOwnPropertyDescriptors=((owner:object)=>{observation();return descriptors(owner);}) as typeof descriptors;
  try{refuses(()=>x.frame.runFrame(),part);}finally{Object.getOwnPropertyDescriptor=descriptor;Object.getOwnPropertyDescriptors=descriptors;}
  if(at>=0)check(hit,'last observation replay reached');return last;
 };
 const baseline=run(create());equal(baseline.length,2,'both positive destination stores witnessed');
 for(let index=0;index<2;index++)for(const kind of ['direct','nested','processor','processor-reference','destination'] as const) {
  const x=create();run(x,baseline[index],()=>{
   if(kind==='direct')Reflect.set(x.outerSources,half,.5);
   else if(kind==='nested')Reflect.set(x.outerSources,'lateConstantOwner',{[three]:3});
   else if(kind==='processor')Reflect.set(x.rootSources,'processor',{gqr0:0,fpscrControl:0});
   else if(kind==='processor-reference')Reflect.set(x.outerSources,'lateNestedProcessor',{alias:x.processor});
   else Object.defineProperty(x.sourceActor,keys[index]!,{writable:false});
  },kind==='destination'?keys[index]!:'secondary terminal');
  distances(x,index===0?61:1);
 }
}
export function runActorSecondaryPositiveSelfTests(make:Make):void {
 let count=0;const create=(position?:readonly number[])=>{count++;if(count%10===0)console.log(`[actor-secondary-positive] starting fixture ${count}`);return fixture(make,position);};
 runSourceTargetDistanceRefinementSelfTests();domainTests(create);
 console.log(`[actor-secondary-positive] computed-square domains/order PASS (${count} fixtures)`);
 admissionTests(create);console.log(`[actor-secondary-positive] lazy data/control/store faults PASS (${count} fixtures)`);
 terminalTests(create);
 console.log(`[actor-secondary-positive] PASS (${count} bounded synthetic graph fixtures): both positive estimators, actual multi-component squares, live horizontal/captured c8, exact constant/operand order, lazy controls/data, terminal aliases and partial stores; absent27764 row38 remains blocked after the third RNG draw`);
}
