/** Bounded actual54070 ->5475c ->54c78 ->55568, never a scheduler callback.
 * Authenticated dispatch cells select lifecycle1/substate1 only. Source history
 * precedes pause; suffix calls and partial writes are never skipped. Explicit
 * current bindings are not retail initialization or a completed battle frame.
 */
import {isSourceActorWorldMatrixRuntime,type SourceActorWorldMatrixRuntime} from './actor-world-matrix.js';
import {isSourceActorStageBoundsRuntime,type SourceActorStageBoundsRuntime} from './actor-stage-bounds.js';
import {isSourceActorStatusTimersRuntime,type SourceActorStatusTimersRuntime} from './actor-status-timers.js';
import {isSourceActorTransformHistoryRuntime,claimSourceActorTransformHistoryForOrdered,
  invokeSourceActorTransformHistoryFromOrdered,type SourceActorTransformHistoryRuntime} from './actor-transform-history.js';
import {isSourceActorFrameLifecycleRuntime,claimSourceActorFrameForOrdered,invokeSourceActorFrameFromOrdered,
  type SourceActorFrameLifecycleRuntime} from './actor-frame-lifecycle.js';
import {isSourceActorReadyTransitionsRuntime,type SourceActorReadyTransitionsRuntime} from './actor-ready-transitions.js';
import {isSourceActorCue0LifecycleRuntime,type SourceActorCue0LifecycleRuntime} from './actor-cue0-lifecycle.js';
import {isSourceActorChargeEffectsRuntime,type SourceActorChargeEffectsRuntime} from './actor-charge-effects.js';
import {isSourceActorMatrixUpdateRuntime,type SourceActorMatrixUpdateRuntime} from './actor-matrix-update.js';
import {consumeSourceActorVoiceRngInvocation,checkSourceActorVoiceRngInvocation,type SourceActorCommandAdmissionRuntime} from './actor-command-admission.js';
import {addSourceFloat32} from './source-float.js';
import {markIncompleteSourceActorDoubleLifecycle,requireCompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {enterSourceBattleOrderedActorInvocation,checkSourceBattleOrderedActorInvocation,
  consumeSourceBattleOrderedActorDistances,requireSourceBattleOrderedActorMatrices,requireSourceBattleOrderedVoiceRng,rejectSourceBattleOrderedActorReentry,type SourceBattleOuterFrameRuntime} from './battle-outer-frame.js';
export interface SourceActorOrderedFrameBinding {
  field6dc:number;byte1ca:number;byte730:number;byte731:number;byte488:number;
  readonly vector724:{x:number;y:number;z:number};pointer7f0:number;
}
export interface SourceActorOrderedFrameSources {
  world:SourceActorWorldMatrixRuntime;stage:SourceActorStageBoundsRuntime;status:SourceActorStatusTimersRuntime;
  history:SourceActorTransformHistoryRuntime;globals:object;
  frame?:SourceActorFrameLifecycleRuntime;ready?:SourceActorReadyTransitionsRuntime;
  cue0?:SourceActorCue0LifecycleRuntime;effects?:SourceActorChargeEffectsRuntime;matrices?:SourceActorMatrixUpdateRuntime;
  data?:{float804373e0?:number;float80437250?:number};
}
export interface SourceActorOrderedFrameRuntime {
  bindActor(id:symbol,initial:Readonly<Partial<SourceActorOrderedFrameBinding>>):void;
  getActorBinding(id:symbol):Partial<SourceActorOrderedFrameBinding>;
  getWorldRuntime():SourceActorWorldMatrixRuntime;getStageRuntime():SourceActorStageBoundsRuntime;
  getStatusRuntime():SourceActorStatusTimersRuntime;getMatchGlobals():object;
}
const runtimes=new WeakSet<object>();
const pendingFrames=new WeakMap<object,SourceActorFrameLifecycleRuntime>(),pendingHistories=new WeakMap<object,SourceActorTransformHistoryRuntime>();
interface Authority {
  run(outer:SourceBattleOuterFrameRuntime,id:symbol):void;
  frame(frame:SourceActorFrameLifecycleRuntime,id:symbol,token:object):void;
  history(history:SourceActorTransformHistoryRuntime,id:symbol):void;
  historyCheck(history:SourceActorTransformHistoryRuntime,id:symbol):void;
  frameCheck(frame:SourceActorFrameLifecycleRuntime,id:symbol,token:object):void;
  voicePosition(command:SourceActorCommandAdmissionRuntime,id:symbol,site:number):void;
  voiceConsume(command:SourceActorCommandAdmissionRuntime,id:symbol,site:number):object;
  voiceCheck(command:SourceActorCommandAdmissionRuntime,id:symbol,site:number,state:object):void;reject():void;
}
const authorities=new WeakMap<object,Authority>();
export function isSourceActorOrderedFrameRuntime(value:unknown):value is SourceActorOrderedFrameRuntime {
  return value!==null&&typeof value==='object'&&runtimes.has(value);
}
export function isPendingSourceActorOrderedFrameClaim(stage:SourceActorOrderedFrameRuntime,frame:SourceActorFrameLifecycleRuntime):boolean {
  return isSourceActorOrderedFrameRuntime(stage)&&pendingFrames.get(stage)===frame;
}
export function isPendingSourceActorOrderedHistoryClaim(stage:SourceActorOrderedFrameRuntime,history:SourceActorTransformHistoryRuntime):boolean {
  return isSourceActorOrderedFrameRuntime(stage)&&pendingHistories.get(stage)===history;
}
export function requireSourceActorOrderedFrameInvocation(stage:SourceActorOrderedFrameRuntime,frame:SourceActorFrameLifecycleRuntime,id:symbol,token:object):void {
  const scope=authorities.get(stage);if(!scope)fail('private ordered55568 invocation required');scope.frame(frame,id,token);
}
export function requireSourceActorOrderedHistoryInvocation(stage:SourceActorOrderedFrameRuntime,history:SourceActorTransformHistoryRuntime,id:symbol):void {
  const scope=authorities.get(stage);if(!scope)fail('private ordered5685c invocation required');scope.history(history,id);
}
export function checkSourceActorOrderedFrameInvocation(stage:SourceActorOrderedFrameRuntime,frame:SourceActorFrameLifecycleRuntime,id:symbol,token:object):void {
  const scope=authorities.get(stage);if(!scope)fail('private ordered55568 invocation required');scope.frameCheck(frame,id,token);
}
export function checkSourceActorOrderedHistoryInvocation(stage:SourceActorOrderedFrameRuntime,history:SourceActorTransformHistoryRuntime,id:symbol):void {
  const scope=authorities.get(stage);if(!scope)fail('private ordered5685c invocation required');scope.historyCheck(history,id);
}
export function rejectSourceActorOrderedFrameReentry(stage:SourceActorOrderedFrameRuntime):void {authorities.get(stage)?.reject();}
export function invokeSourceActorOrderedFrameFromOuter(outer:SourceBattleOuterFrameRuntime,stage:SourceActorOrderedFrameRuntime,id:symbol):void {
  const scope=authorities.get(stage);if(!scope)fail('genuine54070 runtime required');scope.run(outer,id);
}
const activeOrderedStages:SourceActorOrderedFrameRuntime[]=[];
export function checkSourceActorOrderedVoicePosition(stage:SourceActorOrderedFrameRuntime,command:SourceActorCommandAdmissionRuntime,id:symbol,site:number):void {
  const scope=authorities.get(stage);if(!scope)fail('private active55568 voice position required');scope.voicePosition(command,id,site);
}
export function consumeActiveSourceActorOrderedVoiceRng(command:SourceActorCommandAdmissionRuntime,id:symbol,callsite:number):object {
  const active=activeOrderedStages[activeOrderedStages.length-1],scope=active&&authorities.get(active);
  if(!scope)fail('800055fc requires private active source voice invocation');return scope.voiceConsume(command,id,callsite);
}
export function checkActiveSourceActorOrderedVoiceRng(command:SourceActorCommandAdmissionRuntime,id:symbol,callsite:number,state:object):void {
  const active=activeOrderedStages[activeOrderedStages.length-1],scope=active&&authorities.get(active);
  if(!scope)fail('800055fc requires private active source voice invocation');scope.voiceCheck(command,id,callsite,state);
}
const activeOrderedChecks:(()=>void)[]=[];
let checkingOrderedParent=false;
/** Read-only liveness poll for genuine child helpers; no caller can install a scope. */
export function checkActiveSourceActorOrderedInvocation():void {
  if(checkingOrderedParent)return;const active=activeOrderedChecks[activeOrderedChecks.length-1];if(!active)return;
  checkingOrderedParent=true;try{active();}finally{checkingOrderedParent=false;}
}
function fail(reason:string):never {throw Error(`[actor-ordered-frame] ${reason}; prior source effects are not rolled back`);}
const native=Reflect.getOwnPropertyDescriptor;
function record(value:unknown,where:string):object {
  if(value===null||typeof value!=='object'||ArrayBuffer.isView(value)||value instanceof Promise)fail(`${where}: synchronous source owner required`);return value;
}
function own(owner:unknown,key:string):unknown {
  const field=Object.getOwnPropertyDescriptor(record(owner,key),key);
  if(!field||!('value' in field))fail(`${key}: own data property required`);return field.value;
}
function uint(value:unknown,max:number,key:string):number {
  if(typeof value!=='number'||!Number.isInteger(value)||value<0||value>max)fail(`${key}: raw unsigned source integer required`);return value===0?0:value;
}
function f32(value:unknown,key:string):number {
  if(typeof value!=='number'||!Number.isFinite(value)||!Object.is(value,Math.fround(value)))fail(`${key}: finite exact source float32 required`);return value;
}
const s8=(value:number):number=>value<<24>>24;
export function createSourceActorOrderedFrameRuntime(sources:SourceActorOrderedFrameSources):SourceActorOrderedFrameRuntime {
  const world=own(sources,'world'),stage=own(sources,'stage'),status=own(sources,'status'),history=own(sources,'history'),globals=record(own(sources,'globals'),'80433934');
  if(!isSourceActorWorldMatrixRuntime(world)||!isSourceActorStageBoundsRuntime(stage)||!isSourceActorStatusTimersRuntime(status)||
    !isSourceActorTransformHistoryRuntime(history)||history.getWorldRuntime()!==world)fail('genuine canonical ordered owner graph required');
  const actors=new Map<symbol,{actual:object;world:object;stage:object;status:object;binding:Partial<SourceActorOrderedFrameBinding>}>();
  let outer:SourceBattleOuterFrameRuntime|undefined,activeId:symbol|undefined,poisoned=false,incomplete=false;
  let historyActive=false,historyPending=false,framePending:{frame:SourceActorFrameLifecycleRuntime;token:object;entered:boolean}|undefined;
  const check=():void=>{
    if(poisoned||incomplete)fail('incomplete ordered actor stage');
    if(outer&&activeId!==undefined)checkSourceBattleOrderedActorInvocation(outer,runtime,activeId);
  };
  const read=(owner:unknown,key:string):unknown=>{const value=own(owner,key);check();return value;};
  const byte=(owner:object,key:string):number=>uint(read(owner,key),255,key);
  const f=(owner:object,key:string):number=>f32(read(owner,key),key);
  const entry=(id:symbol)=>{const e=actors.get(id);if(!e)fail('unknown/non-owned ordered actor');return e;};
  const owners=(id:symbol):void=>{
    const e=entry(id);
    if(read(sources,'world')!==world||read(sources,'stage')!==stage||read(sources,'status')!==status||read(sources,'history')!==history||read(sources,'globals')!==globals||
      world.getActualActor(id)!==e.actual||world.getActorBinding(id)!==e.world||stage.getActualActor(id)!==e.actual||stage.getActorBinding(id)!==e.stage||
      status.getActualActor(id)!==e.actual||status.getWorldBinding(id)!==e.world||status.getActorBinding(id)!==e.status||
      history.getActualActor(id)!==e.actual||history.getWorldBinding(id)!==e.world)fail('canonical ordered actor owner changed');check();
  };
  const cellAliases:Record<string,readonly string[]>={
    field6dc:['field6DC','float6dc','float6DC','byte6dc','1756'],
    byte1ca:['byte1CA','field1ca','field1CA','458'],byte730:['field730','1840'],byte731:['field731','1841'],
    byte488:['field488','1160'],pointer7f0:['pointer7F0','field7f0','field7F0','2032'],
    vector724:['field724','float724','1828','field728','float728','1832','field72c','field72C','float72c','1836'],
  };
  const cellGuard=(id:symbol,key:string,expected:object=entry(id).binding,extra?:readonly string[]):void=>{
    const aliases=extra??cellAliases[key];if(!aliases)return;
    const e=entry(id);owners(id);
    const records=[sources,globals,e.actual,e.world,e.stage,e.status,e.binding,status.getActualBorg(id),
      status.getMappingActor(id),status.getMovementBinding(id),status.getAttributeBinding(id),history.getActorBinding(id),expected];
    for(const value of records)for(const name of value===expected?aliases:[key,...aliases]) {
      const descriptor=Object.getOwnPropertyDescriptor(value,name);check();if(descriptor!==undefined)fail(`${name}: competing ordered source cell`);
    }
    for(const value of records)for(const name of value===expected?aliases:[key,...aliases])
      if(native(value,name)!==undefined)fail(`${name}: competing ordered source cell`);
  };
  const bindingByte=(id:symbol,key:'byte730'|'byte731'|'byte1ca'|'byte488'):number=>{
    cellGuard(id,key);const value=byte(entry(id).binding,key);cellGuard(id,key);return value;
  };
  const inheritedAliases:Record<string,readonly string[]>={byte19:['field19','25'],byte1a:['byte1A','field1a','26'],
    byte1b:['byte1B','field1b','27'],short272:['half272','field272','626'],byte732:['field732','1842']};
  const storeGuard=(id:symbol,owner:object,key:string):void=>{
    const e=entry(id);
    if(owner===e.binding)cellGuard(id,key);
    else if(owner===e.binding.vector724)cellGuard(id,'vector724');
    else if(inheritedAliases[key])cellGuard(id,key,owner,inheritedAliases[key]);
  };
  const write=(id:symbol,owner:object,key:string,value:number):void=>{
    owners(id);storeGuard(id,owner,key);
    own(owner,key);check();owners(id);storeGuard(id,owner,key);
    const field=native(owner,key);if(!field||!('value' in field)||!field.writable)fail(`${key}: live writable source cell required`);
    (owner as Record<string,unknown>)[key]=value;check();
  };
  const constant=(key:'float804373e0'|'float80437250',expected:number):number=>{
    const data=record(read(sources,'data'),'ordered source constants'),value=f(data,key);
    if(!Object.is(value,expected))fail(`${key}: authenticated source bits differ`);return value;
  };
  const match=():object=>{if(read(sources,'globals')!==globals)fail('canonical80433934 changed');return globals;};
  const ready=(id:symbol)=>{
    const owner=read(sources,'ready');if(!isSourceActorReadyTransitionsRuntime(owner))fail('5475c genuine ready/substate owner required');
    const e=entry(id);if(owner.getActualActor(id)!==e.actual||owner.getWorldBinding(id)!==e.world||owner.getStageBinding(id)!==e.stage||owner.getStatusBinding(id)!==e.status)
      fail('5475c canonical ready owner differs');owner.assertActorComplete(id);return owner.getActorBinding(id);
  };
  const stageClamp=(id:symbol):void=>{
    const e=entry(id);if(s8(byte(e.world,'mode4a1'))!==0)return;
    const first=record(stage.getTerrainGlobals(),'8043625c'),margin=constant('float804373e0',20),minX=f(first,'minX3c');
    const position=record(read(e.actual,'pos'),'position20'),x=f(position,'x');
    if(x<addSourceFloat32(margin,minX))fail('8005a580 reached unsupported lower-X clamp');
    if(x>addSourceFloat32(f(first,'maxX38'),-margin))fail('8005a580 reached unsupported upper-X clamp');
    const second=record(stage.getTerrainGlobals(),'8043625c'),zMargin=constant('float804373e0',20),minZ=f(second,'minZ44');
    const z=f(record(read(e.actual,'pos'),'position20'),'z');
    if(z<addSourceFloat32(zMargin,minZ))fail('8005a580 reached unsupported lower-Z clamp');
    if(z>addSourceFloat32(f(second,'maxZ40'),-zMargin))fail('8005a580 reached unsupported upper-Z clamp');
  };
  const body=(id:symbol):void=>{
    const e=entry(id);owners(id);requireCompleteSourceActorDoubleLifecycle(e.actual);
    const frameField=native(sources,'frame');
    if(frameField&&'value' in frameField&&isSourceActorFrameLifecycleRuntime(frameField.value)) {
      const cue=frameField.value.getTickRuntime().getNormalLifecycleRuntime()?.getCue0Runtime();
      if(cue&&cue.getHistoryBinding(id)!==history.getActorBinding(id))fail('54070 history differs from canonical55568 history owner');
    }
    historyActive=true;historyPending=true;try{invokeSourceActorTransformHistoryFromOrdered(runtime,history,id);}finally{historyActive=false;historyPending=false;}
    const owner=match(),visibility=byte(e.actual,'visibilityBit'),pause=byte(owner,'maskD2');
    if((s8(visibility)&pause)===0) {
      const lifecycle=s8(byte(e.stage,'lifecycle18'));
      if(lifecycle!==1)fail('54070 reached unselected lifecycle table802d3264 entry');
      const binding=ready(id);cellGuard(id,'byte19',binding,['field19','25']);
      const substate=s8(byte(binding,'byte19'));cellGuard(id,'byte19',binding,['field19','25']);
      if((substate===1||substate===2)&&s8(byte(match(),'byte1f'))!==0) {
        write(id,binding,'byte19',3);write(id,binding,'byte1b',0);write(id,binding,'byte1a',0);write(id,e.binding,'byte488',2);
      }
      if(s8(byte(binding,'byte19'))!==1)fail('5475c reached unselected substate table802d3274 entry');
      if(byte(match(),'byte45')===4) {write(id,binding,'byte19',(byte(binding,'byte19')+1)&255);write(id,e.status,'short272',0);}
      const frame=read(sources,'frame');if(!isSourceActorFrameLifecycleRuntime(frame))fail('54ca8 genuine55568 owner required');
      if(frame.getActualActor(id)!==e.actual||frame.getStatusRuntime()!==status)fail('54ca8 canonical55568 owner differs');
      const token=consumeSourceBattleOrderedActorDistances(outer!,runtime,id);
      framePending={frame,token,entered:false};
      try{invokeSourceActorFrameFromOrdered(runtime,frame,id,token);}finally{framePending=undefined;}
    }
    const position=record(read(e.actual,'pos'),'position20');
    const y=f(position,'y'),height=f(e.actual,'stepHeight');write(id,e.binding,'field6dc',addSourceFloat32(y,height));
    if(byte(match(),'byteEB')===0&&s8(bindingByte(id,'byte730'))!==0&&byte(e.stage,'lifecycle18')===1)
      fail('54070 reached unsupported3d6e4/vector724 correction');
    stageClamp(id);
    const lifecycle=s8(byte(e.stage,'lifecycle18'));
    if(lifecycle===1||lifecycle===2) {
      const matrices=read(sources,'matrices');if(!isSourceActorMatrixUpdateRuntime(matrices))fail('54160 genuine465fc required');
      if(matrices.getActualActor(id)!==e.actual||matrices.getWorldBinding(id)!==e.world)fail('54160 matrix owner differs');
      requireSourceBattleOrderedActorMatrices(outer!,runtime,id,matrices);matrices.updateActor(id);check();
    }
    const zero=constant('float80437250',0);
    write(id,e.binding,'byte1ca',0);
    const cue0=read(sources,'cue0');if(!isSourceActorCue0LifecycleRuntime(cue0)||cue0.getActualActor(id)!==e.actual||cue0.getWorldBinding(id)!==e.world)
      fail('54174 canonical732 owner required');
    cellGuard(id,'byte732',cue0.getActorBinding(id),['field732','1842']);
    write(id,cue0.getActorBinding(id),'byte732',0);write(id,e.binding,'byte730',0);write(id,e.binding,'byte731',0);
    cellGuard(id,'vector724');const vector=record(read(e.binding,'vector724'),'vector724');cellGuard(id,'vector724');
    write(id,vector,'x',zero);write(id,vector,'y',zero);write(id,vector,'z',zero);
    const effects=read(sources,'effects');if(!isSourceActorChargeEffectsRuntime(effects)||effects.getActualActor(id)!==e.actual)fail('06284 canonical7ec owner required');
    const color=effects.getActorBinding(id);cellGuard(id,'pointer7ec',color,['pointer7EC','field7ec','2028']);
    if(uint(read(color,'pointer7ec'),0xffffffff,'pointer7ec')!==0)fail('06284 reached unsupported first color channel');
    cellGuard(id,'pointer7f0');const secondChannel=uint(read(e.binding,'pointer7f0'),0xffffffff,'pointer7f0');cellGuard(id,'pointer7f0');
    if(secondChannel!==0)fail('06284 reached unsupported second color channel');
  };
  const runtime:SourceActorOrderedFrameRuntime={
    bindActor(id,initial){
      if(outer){reject();fail('ordered actor binding during execution unsupported');}
      if(incomplete)fail('ordered actor binding after incomplete execution unsupported');
      if(actors.has(id))fail('ordered actor already bound');
      const actual=world.getActualActor(id),worldBinding=world.getActorBinding(id),stageBinding=stage.getActorBinding(id),statusBinding=status.getActorBinding(id);
      if(stage.getActualActor(id)!==actual||status.getActualActor(id)!==actual||status.getWorldBinding(id)!==worldBinding||history.getActualActor(id)!==actual||history.getWorldBinding(id)!==worldBinding)
        fail('canonical ordered actor bindings differ');
      const binding:Partial<SourceActorOrderedFrameBinding>={};
      for(const key of ['byte1ca','byte730','byte731','byte488'] as const)if(native(initial,key)!==undefined)binding[key]=uint(own(initial,key),255,key);
      if(native(initial,'field6dc')!==undefined)binding.field6dc=f32(own(initial,'field6dc'),'field6dc');
      if(native(initial,'pointer7f0')!==undefined)binding.pointer7f0=uint(own(initial,'pointer7f0'),0xffffffff,'pointer7f0');
      if(native(initial,'vector724')!==undefined) {
        const vector=record(own(initial,'vector724'),'vector724');
        Object.defineProperty(binding,'vector724',{value:Object.seal({x:f32(own(vector,'x'),'x'),y:f32(own(vector,'y'),'y'),z:f32(own(vector,'z'),'z')}),enumerable:true});
      }
      actors.set(id,{actual,world:worldBinding,stage:stageBinding,status:statusBinding,binding:Object.seal(binding)});
    },
    getActorBinding(id){return entry(id).binding;},getWorldRuntime(){return world;},getStageRuntime(){return stage;},getStatusRuntime(){return status;},getMatchGlobals(){return globals;},
  };
  const reject=():void=>{if(outer){poisoned=true;rejectSourceBattleOrderedActorReentry(outer);}};
  authorities.set(runtime,{
    run(selected,id){
      if(outer){reject();fail('same ordered runtime reentry');}if(incomplete)fail('permanently incomplete ordered stage');
      const actual=enterSourceBattleOrderedActorInvocation(selected,runtime,id);
      if(entry(id).actual!==actual)fail('outer ordered actual differs');outer=selected;activeId=id;poisoned=false;
      activeOrderedChecks.push(check);activeOrderedStages.push(runtime);
      try{body(id);check();}catch(error){incomplete=true;markIncompleteSourceActorDoubleLifecycle(actual);rejectSourceBattleOrderedActorReentry(selected);throw error;}
      finally{activeOrderedStages.pop();activeOrderedChecks.pop();outer=undefined;activeId=undefined;historyActive=false;historyPending=false;framePending=undefined;}
    },
    history(selected,id){if(!outer||activeId!==id||selected!==history||!historyPending){reject();fail('private exact5408c history invocation required');}historyPending=false;check();},
    frame(selected,id,token){const pending=framePending;if(!outer||activeId!==id||!pending||pending.frame!==selected||pending.token!==token||pending.entered){reject();fail('private exact single-use54ca8 invocation required');}pending.entered=true;check();},
    historyCheck(selected,id){if(!outer||activeId!==id||selected!==history||!historyActive||historyPending){reject();fail('private active5408c history invocation required');}check();},
    frameCheck(selected,id,token){const pending=framePending;if(!outer||activeId!==id||!pending||pending.frame!==selected||pending.token!==token||!pending.entered){reject();fail('private active54ca8 invocation required');}check();},
    voicePosition(command,id,site){
      if(!outer||activeId!==id||!framePending?.entered||command.getGlobal()!==globals){reject();fail('private exact active55568 voice RNG scope required');}
      checkSourceActorVoiceRngInvocation(command,id,site);check();
    },
    voiceConsume(command,id,site){
      if(!outer||activeId!==id||!framePending?.entered||command.getGlobal()!==globals){reject();fail('private exact active55568 voice RNG scope required');}
      check();consumeSourceActorVoiceRngInvocation(command,id,site);check();
      return requireSourceBattleOrderedVoiceRng(outer,runtime,id,command,site);
    },
    voiceCheck(command,id,site,state){
      if(!outer||activeId!==id||!framePending?.entered||command.getGlobal()!==globals){reject();fail('private exact active55568 voice RNG scope required');}
      checkSourceActorVoiceRngInvocation(command,id,site);check();requireSourceBattleOrderedVoiceRng(outer,runtime,id,command,site,state);
    },
    reject,
  });
  runtimes.add(runtime);pendingHistories.set(runtime,history);
  try{claimSourceActorTransformHistoryForOrdered(runtime,history);}finally{pendingHistories.delete(runtime);}
  const frameField=native(sources,'frame');
  if(frameField&&'value' in frameField&&frameField.value!==undefined) {
    const frame=frameField.value;if(!isSourceActorFrameLifecycleRuntime(frame))fail('genuine ordered55568 runtime required');
    pendingFrames.set(runtime,frame);try{claimSourceActorFrameForOrdered(runtime,frame);}finally{pendingFrames.delete(runtime);}
  }
  return Object.freeze(runtime);
}
