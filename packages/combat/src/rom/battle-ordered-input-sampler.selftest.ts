import {createSourceActorInputSamplerRuntime,invokeSourceActorInputSamplerFromOrdered} from './actor-input-sampler.js';
import {createSourceActorChargeEffectsRuntime} from './actor-charge-effects.js';
import {createBattleParticipantViewTestFixture} from './battle-participant-view.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
import {createSourceActorOrderedFrameRuntime} from './actor-ordered-frame.js';
import {createSourceActorFrameLifecycleRuntime} from './actor-frame-lifecycle.js';
import {createSourceActorReadyTransitionsRuntime} from './actor-ready-transitions.js';
export function createBattleOrderedInputSamplerTestFixture(make:typeof createBattleTargetPreparationTestFixture, mode=0){
const x=createBattleParticipantViewTestFixture(make,false,0);
for(const [i,id]of x.physicalIdentities.entries()){x.actors[i]!.active0=i===0?1:0;x.world.getActorBinding(id).mode4a0=0;x.status.getActualBorg(id).burstArmFrames=0;}
x.stageState.lifecycle18=1;x.header.mode4a1=0;
const frame=createSourceActorFrameLifecycleRuntime(x.frameSources);frame.bindActor(x.actor);
const ready=x.readyTransitions??createSourceActorReadyTransitionsRuntime({world:x.world,status:x.status,stageBounds:x.stageBounds,control:x.actorControl!});
if(!x.readyTransitions)ready.bindActor(x.actor,{byte19:2,byte1a:2,byte1b:3});else ready.getActorBinding(x.actor).byte19=2;
Object.assign(x.matchGlobals,{byte1f:0,byte45:4,byte1829:0,byteEB:0});
const existingEffects=x.commandAdmission.getChargeRuntime().getEffects();
const effects=existingEffects??createSourceActorChargeEffectsRuntime({world:x.world,data:{},sound:{}});
if(!existingEffects)effects.bindActor(x.actor,{pointer7ec:0});
Object.assign(x.stageBounds.getTerrainGlobals(),{minX3c:-10000,maxX38:10000,minZ44:-10000,maxZ40:10000});
Object.assign(x.outerSources.systemGlobals!,{byte32:0});
const input=frame.getTickRuntime().getInputRuntime()!;
const pad={word0:0x00aa1357,byte15:9,byte16:128,byte17:255,byte18:3,byte19:4,byte1a:5,byte1b:6};
const pads:Record<number,object>={[x.sourceActor.slot]:pad,[x.sourceActor.slot%4]:pad};
const sampler=createSourceActorInputSamplerRuntime({world:x.world,input,view:x.outerSources.systemGlobals!,globals:x.matchGlobals,pads});
sampler.bindActor(x.actor,{byte3e6:0,byte5c9:1,byte5cc:20,byte5cd:21,byte5ce:22,byte5cf:23,word5c0:99,word5c4:88});
const ordered=createSourceActorOrderedFrameRuntime({world:x.world,stage:x.stageBounds,status:x.status,history:x.history,globals:x.matchGlobals,frame,sampler,ready,cue0:x.cue0,effects,matrices:x.normal,data:{float804373e0:20,float80437250:0}});
ordered.bindActor(x.actor,{field6dc:99,byte1ca:5,byte730:0,byte731:7,byte488:mode,vector724:{x:1,y:2,z:3},pointer7f0:0});
Object.assign(x.outerSources,{orderedActors:ordered});
return Object.assign(x,{sampler,pad,pads,input,samplerState:sampler.getActorBinding(x.actor),inputState:input.getActorBinding(x.actor),actorFrame:frame,ordered,orderedState:ordered.getActorBinding(x.actor),orderedReady:ready});
}

type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[ordered-input-sampler-test] '+why);}
function refusal(run:()=>unknown,part:string):void{let message='';try{run();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message}`);}
export function runBattleOrderedInputSamplerSelfTests(make:Make):void{
 let cases=0;
 const fresh=(mode=0)=>{cases++;const x=createBattleOrderedInputSamplerTestFixture(make,mode);Object.defineProperty(x.gates,'marker578',{writable:false});return x;};
 {
  const x=fresh();x.sourceActor.statusWord5b4=0x12345678;
  refusal(()=>x.frame.runFrame(),'marker578');
  check(x.inputState.ushort5b8===0x1234&&x.inputState.ushort5ba===0x5678,'actual stw preserves both canonical prior halves');
  check(x.sourceActor.statusWord5b4===0xaa1357&&x.sourceActor.statusWord5bc===(0xaa1357&~0x12345678),'real masked pad word and press edge');
  check(x.samplerState.word5c0===(0x12345678&~0xaa1357)&&x.samplerState.word5c4===0,'real release edge/clear');
  check(x.inputState.stickX5ca===-128&&x.inputState.stickY5cb===-1&&x.samplerState.byte5cf===6&&x.samplerState.byte5c9===9,'raw analog bytes share signed stick owners');
  check(x.orderedReady.getActorBinding(x.actor).byte19===2&&x.orderedState.field6dc===99,'index2 does not increment19 or reach suffix after readonly55568 marker');
 }
 for(const mode of [1,2,3,128,255]){
  const x=fresh(mode);x.sourceActor.statusWord5b4=0x12345678;const oldX=x.inputState.stickX5ca;
  refusal(()=>x.frame.runFrame(),'marker578');
  check(x.inputState.ushort5b8===0x1234&&x.inputState.ushort5ba===0x5678,'all modes capture priorword');
  if(mode===1)check(x.sourceActor.statusWord5b4===0x12345678&&x.inputState.stickX5ca===oldX&&x.sourceActor.statusWord5bc===0,'mode1 retains current analog/digital');
  else if(mode===3)check(x.orderedState.byte488===0&&x.sourceActor.statusWord5bc===0&&x.samplerState.word5c0===0,'reset mode clears edges after actual sampling');
  else check(x.sourceActor.statusWord5b4===0&&x.inputState.stickX5ca===0&&x.samplerState.byte5cf===0&&x.samplerState.word5c0===0x12345678,'signed other modes zero analog/current then compute release');
 }
 for(const override of ['global','phase']){
  const x=fresh();if(override==='global')Object.assign(x.matchGlobals,{byte1829:1});else x.matchGlobals.byte45=5;
  refusal(()=>x.frame.runFrame(),'marker578');check(x.sourceActor.statusWord5b4===0&&x.orderedState.byte488===0&&x.samplerState.byte5c9===9,'effective mode2 override retains source488 and earlier byte15 load');
 }
 {
  const x=fresh(1);x.samplerState.byte3e6=1;x.sourceActor.statusWord5b4=0x89abcdef;
  refusal(()=>x.frame.runFrame(),'mandatory AI8001c9d0');check(x.inputState.ushort5b8===0x89ab&&x.inputState.ushort5ba===0xcdef&&x.samplerState.word5c4===88,'mandatory AI refuses after actual prior store before tail');
 }
 {
  const x=fresh(2);x.samplerState.byte3e6=1;refusal(()=>x.frame.runFrame(),'marker578');check(x.samplerState.byte5c9===1&&x.samplerState.word5c4===0,'actual AI mode2 bypasses pad/AI but runs full tail');
 }
 {
  const x=fresh(3);x.sourceActor.statusWord5b4=0x12345678;Object.defineProperty(x.inputState,'ushort5ba',{writable:false});
  const hi=x.inputState.ushort5b8,lo=x.inputState.ushort5ba;refusal(()=>x.frame.runFrame(),'both writable halves');
  check(x.inputState.ushort5b8===hi&&x.inputState.ushort5ba===lo&&x.orderedState.byte488===0&&x.samplerState.byte5c9===9,'atomic prior stw refuses both halves but preserves earlier source stores');
 }
 for(const key of ['byte16','ushort5ba','word5c0']){
  const x=fresh(),initialHi=x.inputState.ushort5b8,initialLo=x.inputState.ushort5ba;let fired=false;const native=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner:object,k:PropertyKey)=>{if(!fired&&k===key&&(owner===x.pad||owner===x.inputState||owner===x.samplerState)){fired=true;try{x.frame.runFrame();}catch{}}return native(owner,k);}) as typeof native;
  try{refusal(()=>x.frame.runFrame(),'private exact active ordered actor invocation');}finally{Object.getOwnPropertyDescriptor=native;}
  check(fired,'caught parent reentry at actual sampler cell');
  if(key==='byte16')check(x.inputState.stickX5ca!==-128,'reentry prevents analog store');
  if(key==='ushort5ba')check(x.inputState.ushort5b8===initialHi&&x.inputState.ushort5ba===initialLo,'reentry prevents atomic prior store');
  if(key==='word5c0')check(x.samplerState.word5c0===99,'reentry prevents release edge');
 }
 {
  const x=fresh();refusal(()=>invokeSourceActorInputSamplerFromOrdered(x.ordered,x.sampler,x.actor),'private exact single-use54cd0');
  refusal(()=>x.sampler.bindActor(Symbol('foreign'),{}),'exclusively');
  refusal(()=>x.frame.runFrame(),'marker578');
 }
 {
  const x=fresh();let injected=false;const native=Object.getOwnPropertyDescriptor,oldHigh=x.inputState.ushort5b8;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{if(!injected&&o===x.inputState&&k==='ushort5ba'){injected=true;Object.assign(x.sourceActor,{priorWord5b8:0});}return native(o,k);}) as typeof native;
  try{refusal(()=>x.frame.runFrame(),'competing sampler source owner');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected&&x.inputState.ushort5b8===oldHigh,'late priorWord5b8 shadow blocks atomic store');
 }
 console.log(`[ordered-input-sampler] PASS: ${cases} genuine index2 compositions`);
}

/** Explicit supported source entry, not a retail-hydrated frame. The source
 * sampler/tick may replace these initial selectors; no mid-call writes occur. */
export function createBattleOrderedInputSamplerValidEntryTestFixture(make:Make){
 const x=createBattleOrderedInputSamplerTestFixture(make);
 x.actionTables.full36a8[0]=0x8005f238; // authenticated802d36a8[0], real bareBLR
 Object.assign(x.sourceActor,{ubState:0,fbState:61,actionIndex:2,variantIndex:0,fbPhase:1});
 Object.assign(x.pad,{word0:0,byte15:0,byte16:0,byte17:0,byte18:0,byte19:0,byte1a:0,byte1b:0});
 x.normal.bindAttributesRuntime(x.attributes);x.normal.bindActiveCorrectionSources(x.stageBounds,x.commandAdmission);
 return x;
}
export function runBattleOrderedInputSamplerValidEntrySelfTests(make:Make):void{
 const x=createBattleOrderedInputSamplerValidEntryTestFixture(make);
 check(x.sourceActor.fbState===61&&x.orderedReady.getActorBinding(x.actor).byte19===2&&x.matchGlobals.byte45===4,'explicit supported entry selectors/substate/phase');
 refusal(()=>x.frame.runFrame(),'8002948c reached mandatory80087cf0');
 check(x.sourceActor.fbState===0&&x.sourceActor.ubState===0,'real sampler/tick-produced selector0 uses authenticated dispatch');
 check(x.orderedState.byte1ca===0&&x.orderedState.byte731===0&&Object.values(x.orderedState.vector724!).every(v=>v===0),'55568 returns and actual54070 suffix finishes');
 check(x.massPreparation.teamCounts[0]===1&&x.teamRows103[0]!.charged&&x.status.getActualBorg(x.actor).burstArmFrames===0,'natural nonempty charged-team rejection/countdown finishes53a2c');
 refusal(()=>x.frame.runFrame(),'incomplete');
 console.log('[ordered-input-valid-entry] PASS: actual index2 sampler/frame/suffix and nonempty6fb0 scan, next87cf0; explicit entry only, not complete battle frame');
}
