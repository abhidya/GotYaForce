import {consumeSourceBattleOrderedActorDistances} from './battle-outer-frame.js';
import {invokeSourceActorFrameFromOrdered} from './actor-frame-lifecycle.js';
import {createSourceActorChargeEffectsRuntime} from './actor-charge-effects.js';
import {createBattleParticipantViewTestFixture} from './battle-participant-view.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
import {createSourceActorOrderedFrameRuntime} from './actor-ordered-frame.js';
import {createSourceActorFrameLifecycleRuntime} from './actor-frame-lifecycle.js';
import {createSourceActorReadyTransitionsRuntime} from './actor-ready-transitions.js';
export function createBattleOrderedActorStageTestFixture(make:typeof createBattleTargetPreparationTestFixture){
const x=createBattleParticipantViewTestFixture(make,false,0);
for(const [i,id]of x.physicalIdentities.entries()){x.actors[i]!.active0=i===0?1:0;x.world.getActorBinding(id).mode4a0=0;x.status.getActualBorg(id).burstArmFrames=0;}
x.stageState.lifecycle18=1;x.header.mode4a1=0;
const frame=createSourceActorFrameLifecycleRuntime(x.frameSources);frame.bindActor(x.actor);
const ready=x.readyTransitions??createSourceActorReadyTransitionsRuntime({world:x.world,status:x.status,stageBounds:x.stageBounds,control:x.actorControl!});
if(!x.readyTransitions)ready.bindActor(x.actor,{byte19:1,byte1a:2,byte1b:3});else ready.getActorBinding(x.actor).byte19=1;
Object.assign(x.matchGlobals,{byte1f:0,byte45:5,byteEB:0});
const existingEffects=x.commandAdmission.getChargeRuntime().getEffects();
const effects=existingEffects??createSourceActorChargeEffectsRuntime({world:x.world,data:{},sound:{}});
if(!existingEffects)effects.bindActor(x.actor,{pointer7ec:0});
Object.assign(x.stageBounds.getTerrainGlobals(),{minX3c:-10000,maxX38:10000,minZ44:-10000,maxZ40:10000});
const ordered=createSourceActorOrderedFrameRuntime({world:x.world,stage:x.stageBounds,status:x.status,history:x.history,globals:x.matchGlobals,frame,ready,cue0:x.cue0,effects,matrices:x.normal,data:{float804373e0:20,float80437250:0}});
ordered.bindActor(x.actor,{field6dc:99,byte1ca:5,byte730:0,byte731:7,byte488:8,vector724:{x:1,y:2,z:3},pointer7f0:0});
Object.assign(x.outerSources,{orderedActors:ordered});
return Object.assign(x,{actorFrame:frame,ordered,orderedState:ordered.getActorBinding(x.actor),orderedReady:ready});
}

type Make=typeof createBattleTargetPreparationTestFixture;
type Fixture=ReturnType<typeof createBattleOrderedActorStageTestFixture>;
const MATRIX='46f08 genuine shared attribute674 owner required';
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-ordered-actor-stage-test] '+why);}
function refuses(f:()=>unknown,part:string):string{let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message||'success'}`);return message;}
function run(x:Fixture,expected:string,visit:(o:object,k:PropertyKey)=>void=()=>{}):void{
 const native=Object.getOwnPropertyDescriptor;let ordered=false;
 Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
  if(o===x.outerSources&&k==='orderedActors')ordered=true;
  if(ordered)visit(o,k);
  return native(o,k);
 }) as typeof native;
 try{refuses(()=>x.frame.runFrame(),expected);}finally{Object.getOwnPropertyDescriptor=native;}
 check(ordered,'genuine one-entry ordered table reached');
 refuses(()=>x.frame.runFrame(),'incomplete');
 refuses(()=>x.allocator.writeU8(x.nextChild,0,1),'incomplete');
}
export function runBattleOrderedActorStageSelfTests(make:Make):void{
 let count=0;
 const fresh=()=>{count++;return createBattleOrderedActorStageTestFixture(make);};
 {
  const x=fresh(),initial={...x.sourceActor.pos};let marker=false,heightStore=false;
  run(x,MATRIX,(o,k)=>{
   if(o===x.gates&&k==='marker578'&&!marker){marker=true;
    check(x.sourceActor.savedGroundPos.x===initial.x&&x.sourceActor.savedGroundPos.z===initial.z,'5685c history precedes actual55568 marker');
    check(x.historyState.previousStepHeight6d4===0,'source history step height retained');
   }
   if(o===x.orderedState&&k==='field6dc'){heightStore=true;check(marker,'55568 precedes ordered height suffix');}
  });
  check(marker&&heightStore,'genuine55568 and postframe suffix both execute');
  check(x.massPreparation.orderCount.count80436260===1&&x.actors.slice(1).every(a=>a.active0===0),'one actor admitted from entry, no activation trick');
  check(x.orderedState.field6dc===Math.fround(x.sourceActor.pos.y+x.sourceActor.stepHeight),'actual suffix height store survives unsupported matrix handler');
  check(x.orderedState.byte1ca===5&&x.orderedState.vector724!.x===1,'later clears not fabricated');
 }
 {
  const x=fresh();x.matchGlobals.byte45=0;
  run(x,'byte438: own data property required');
  check(x.orderedState.field6dc===99,'ordinary audio refusal precedes suffix height store');
 }
 {
  const x=fresh();Object.assign(x.stageBounds.getTerrainGlobals(),{minX3c:-100,maxX38:100,minZ44:-300,maxZ40:300});
  run(x,'8005a580 reached unsupported lower-X clamp');
  check(x.orderedState.field6dc!==99&&x.orderedState.byte1ca===5,'original bounded stage preserves prior height but no clears');
 }
 {
  const x=fresh();Object.defineProperty(x.orderedState,'field6dc',{writable:false});
  run(x,'field6dc');check(x.orderedState.field6dc===99,'readonly suffix destination preserves value after55568');
 }
 {
  const x=fresh();x.matchGlobals.maskD2=255;x.sourceActor.visibilityBit=1;const marker=x.gates.marker578;
  run(x,'8005b2b8 reached mandatory live candidate scan');
  check(x.gates.marker578===marker,'pause skips55568, not history or suffix');
  check(x.historyState.previousStepHeight6d4===0&&x.orderedState.field6dc===2,'pause still snapshots then stores actual position+height');
  check(x.orderedState.byte1ca===0&&x.orderedState.byte730===0&&x.orderedState.byte731===0&&Object.values(x.orderedState.vector724!).every(v=>v===0),'all reached suffix clears precede genuine candidate boundary');
 }
 for(const lifecycle of [true,false]){
  const x=fresh();if(lifecycle)x.stageState.lifecycle18=0;else x.orderedReady.getActorBinding(x.actor).byte19=0;
  run(x,lifecycle?'unselected lifecycle':'unselected substate');
  check(x.historyState.previousStepHeight6d4===0&&x.orderedState.field6dc===99,'history survives unsupported dispatch, suffix untouched');
 }
 {
  const x=fresh();x.matchGlobals.maskD2=255;x.sourceActor.visibilityBit=1;Object.defineProperty(x.orderedState,'byte731',{writable:false});
  run(x,'byte731');check(x.orderedState.byte1ca===0&&x.orderedState.byte730===0&&x.orderedState.byte731===7&&x.orderedState.vector724!.x===1,'source-ordered partial clears survive readonly later byte');
 }
 for(const location of ['history','frame','bind']as const){
  const x=fresh();let fired=false;const before={...x.sourceActor.savedGroundPos};
  run(x,location==='bind'?'incomplete':'private exact active ordered actor invocation',(o,k)=>{if(!fired&&(location==='history'?o===x.sourceActor.savedGroundPos&&k==='x':o===x.gates&&k==='marker578')){
   fired=true;try{if(location==='bind')x.ordered.bindActor(Symbol('reentry'),{});else x.frame.runFrame();}catch{}
  }});
  check(fired,'caught nested entry reached actual child boundary');
  if(location==='history')check(x.sourceActor.savedGroundPos.x===before.x&&x.sourceActor.savedGroundPos.y===before.y,'caught outer reentry blocks later history stores');
  check(x.orderedState.field6dc===99,'caught child reentry blocks suffix');
 }
 for(const readonly of [true,false]){
  const x=fresh(),actor=x.sourceActor;x.sourceActor.modelScale=2;x.gates.marker578=99;
  let injected=false,raw760:number|undefined,raw764:number|undefined;
  run(x,readonly?'non-writable':'private exact active ordered actor invocation',(o,k)=>{
   if(o===x.historyState.rotation76&&k==='x'){
    raw760=actor.targetDistance760;raw764=actor.horizontalDistance764;
    if(readonly&&!injected){injected=true;Object.defineProperty(actor,'targetDistance760',{writable:false});Object.defineProperty(actor,'horizontalDistance764',{writable:false});}
   }
   if(!readonly&&!injected&&o===actor&&k==='horizontalDistance764'&&raw760!==undefined&&actor.targetDistance760!==raw760){
    injected=true;try{x.frame.runFrame();}catch{}
   }
  });
  check(injected&&x.gates.marker578===2,'source55568 marker/attributes/status precede reached normalization');
  check(raw760===20000&&raw764===20000,'actual outer paired source values reach history without host rewrite');
  check(actor.targetDistance760===(readonly?20000:10000)&&actor.horizontalDistance764===20000,'readonly first store or caught reentry preserves exact source normalization prefix');
 }
 {
  const x=fresh();
  refuses(()=>consumeSourceBattleOrderedActorDistances(x.frame,x.ordered,x.actor),'private');
  refuses(()=>invokeSourceActorFrameFromOrdered(x.ordered,x.actorFrame,x.actor,{}),'private');
  refuses(()=>x.history.snapshotActor(x.actor),'exclusively');
  refuses(()=>x.actorFrame.ingestRawDistancesAndRun(x.actor,1,{boundary:'externally-decoded-pre55568-raw',targetDistance760:3,horizontalDistance764:4}),'ordered');
  check(x.actorFrame.getActualActor(x.actor)===x.sourceActor&&x.ordered.getActorBinding(x.actor)===x.orderedState,'idle readonly identities remain diagnostic, not execution authority');
  run(x,MATRIX);
 }
 for(const key of ['field6dc','byte730','pointer7f0']as const){
  const x=fresh();x.matchGlobals.maskD2=255;x.sourceActor.visibilityBit=1;let injected=false;
  run(x,'competing ordered source cell',(o,k)=>{if(!injected&&o===x.orderedState&&k===key){
   injected=true;Object.assign(x.sourceActor,{[key]:0});
  }});
  check(injected,'late competing scalar owner reached');
  if(key==='field6dc')check(x.orderedState.field6dc===99,'late height alias prevents store');
  else check(x.orderedState.field6dc===2,'later alias preserves prior genuine height store');
  if(key==='pointer7f0')check(x.orderedState.byte1ca===0&&x.orderedState.vector724!.z===0,'late second channel alias preserves completed clears');
 }
 console.log(`[battle-ordered-actor-stage] PASS: ${count} one-active genuine compositions; history then55568 and partial suffix, honest audio/clamp/matrix boundaries`);
}
