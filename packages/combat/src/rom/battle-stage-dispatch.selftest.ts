import {requireSourceObjectSchedulerFrameParent} from './source-object-scheduler.js';
import {invokeSourceProjectileHitFromRoot} from './projectile-hit-registration.js';
import {invokeSourceProjectileHitAllocation} from './actor-projectile-spawn.js';
import {allocateSourceProjectileHitFromSpawn} from './source-object-allocation.js';
import {createBattleOrderedInputSamplerValidEntryTestFixture} from './battle-ordered-input-sampler.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-stage-dispatch-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message}`);}
export function createBattleStageDispatchTestFixture(make:Make,state=1){
 const x=createBattleOrderedInputSamplerValidEntryTestFixture(make),stage=x.stageBounds.getTerrainGlobals();
 Object.assign(stage,{byte0:state,byte8:0});
 Object.assign(x.rootSources,{initializationStack:{rotationX:x.matrices.createMatrix(Array(12).fill(37)),rotationY:x.matrices.createMatrix(Array(12).fill(-19))}});
 // Explicit initially empty ancillary groups; the existing initialized
 // projectile remains in its real group9 and draw list, without relocation.
 for(const group of [...Array.from({length:8},(_,i)=>i),...Array.from({length:16},(_,i)=>16+i),56])
  if(x.groups[group]===undefined)x.groups[group]={head:null,tail:null};
 return Object.assign(x,{stageDispatchOwner:stage});
}
export function runBattleStageDispatchSelfTests(make:Make):void{
 let cases=0;const fresh=(state=1)=>{cases++;return createBattleStageDispatchTestFixture(make,state);};
 {
  const x=fresh(0);refuses(()=>x.frame.runFrame(),'unsupported scene setup after source byte0/byte8 stores');
  check(x.stageDispatchOwner.byte0===1&&x.stageDispatchOwner.byte8===1&&x.orderedState.byte1ca===0,'actual stage0 partial setup follows completed actor stage');
 }
 {
  const x=fresh(0);delete x.stageDispatchOwner.byte8;refuses(()=>x.frame.runFrame(),'byte8: own data');
  check(x.stageDispatchOwner.byte0===1,'missing8 preserves earlier actual selector increment');
 }
 for(const state of [2,128,255]){const x=fresh(state);refuses(()=>x.frame.runFrame(),'unselected signed stage dispatch');check(x.stageDispatchOwner.byte0===state&&x.stageDispatchOwner.byte8===0,'unselected state never becomes default1');}
 {
  const x=fresh(0);Object.defineProperty(x.stageDispatchOwner,'byte0',{writable:false});refuses(()=>x.frame.runFrame(),'byte0');check(x.stageDispatchOwner.byte0===0&&x.stageDispatchOwner.byte8===0,'readonly state blocks later8 store');
 }
 for(const fault of ['alias','reentry'] as const){
  const x=fresh(0),native=Object.getOwnPropertyDescriptor;let injected=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!injected&&o===x.stageDispatchOwner&&k==='byte0'){
    injected=true;if(fault==='alias')Object.assign(o,{field0:0});else try{x.frame.runFrame();}catch{}
   }
   return native(o,k);
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),fault==='alias'?'competing':'caught same-runtime reentry');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&x.stageDispatchOwner.byte0===0&&x.stageDispatchOwner.byte8===0,'late stage alias/caught parent reentry blocks stage stores');
 }
 {
  const x=fresh(),before=x.hitPool.count,child=x.child,native=Object.getOwnPropertyDescriptor,groups:number[]=[];let later=false;
  check(x.groups[9]!.head===child,'original projectile stays in original group9 at entry');
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.stageDispatchOwner&&k==='byte0')later=true;
   if(later&&k==='head')for(const group of [1,0,7,17,16,23,9])if(o===x.groups[group])groups.push(group);
   return native(o,k);
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),'8007e074 reached actual8020bab8 Normalize');}finally{Object.getOwnPropertyDescriptor=native;}
  check(groups.join(',')==='1,0,7,17,16,23,9','actual slot-first wrapper0/16/8 group order');
  check(x.groups[9]!.head===child&&x.drawList.head===child&&x.drawList.tail===child,'real retained projectile is registered, never cleared or relocated');
  check(x.hitPool.count===before-1&&x.allocator.readU8(child,0x18)===1,'real pool4 allocation and state increment precede normalization');
  check([0x38,0x3c,0x40].map(o=>x.allocator.readF32(child,o)).join(',')==='0,0,1','actual flight direction stores produce proven unit input');
 }
 for(const offset of [44,133]){
  const x=fresh(),bytes=x.objectBytes,native=Object.getOwnPropertyDescriptor;bytes[offset]=255;let fired=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!fired&&o===bytes&&k===String(offset)&&x.orderedState.byte1ca===0){fired=true;try{x.frame.runFrame();}catch{}}
   return native(o,k);
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),'reentry');}finally{Object.getOwnPropertyDescriptor=native;}
  check(fired&&bytes[offset]===255,'caught parent reentry blocks reached snapshot/root destination');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let injected=false,setter=0;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   const p=native(o,k);
   if(!injected&&o===x.drawList&&k==='tail'&&x.orderedState.byte1ca===0){injected=true;Object.defineProperty(o,k,{set(){setter++;},get(){throw Error('not called');},configurable:true});}
   return p;
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),'draw destination changed before store');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&setter===0&&x.drawList.head===x.child,'native final draw guard rejects accessor after real head store');
 }
 {
  const x=fresh(),before=x.hitPool.count;
  refuses(()=>requireSourceObjectSchedulerFrameParent(x.scheduler,x.root,x.child,x.actor,x.sourceActor),'private');
  refuses(()=>invokeSourceProjectileHitFromRoot(x.hits,x.root,x.child,1),'private');
  refuses(()=>invokeSourceProjectileHitAllocation(x.projectiles,x.hits,x.child),'private');
  refuses(()=>allocateSourceProjectileHitFromSpawn(x.allocator,x.projectiles,x.child,x.actor,Symbol('forged')),'private');
  check(x.hitPool.count===before,'idle forged joins never allocate');
 }
 console.log(`[battle-stage-dispatch] PASS: ${cases} real stage dispatch prerequisite/partial-store fixtures`);
}
