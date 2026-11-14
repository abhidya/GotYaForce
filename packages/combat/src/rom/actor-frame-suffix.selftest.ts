import {createSourceActorFrameSuffixRuntime,isSourceActorFrameSuffixRuntime,type SourceActorFrameSuffixBinding} from './actor-frame-suffix.js';
import {createSourceActorDoublePrehookRuntime,hasIncompleteSourceActorDoubleLifecycle,markIncompleteSourceActorDoubleLifecycle} from './actor-double-prehook.js';
import {createSourceActorStatusTimersRuntime,type SourceActorStatusTimersSources} from './actor-status-timers.js';
import {createSourceActorInputChargeRuntime} from './actor-input-charge.js';
import {createSourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {createSourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {createSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {createSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {createSourceJObjAnimationRuntime} from './jobj-animation.js';
import {createSourceStreamWaitRuntime} from './stream-wait.js';
import {createSourceStreamWaitTargetRuntime} from './stream-wait-target.js';
import {createSourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {createRomActor} from './actor.js';
import {bindDoubleNinjaOwnerState} from '../ninjaX.js';
function check(ok:boolean,why:string):void {if (!ok) throw Error(`[actor-frame-suffix-test] ${why}`);}
function equal(actual:unknown,expected:unknown,why:string):void {check(Object.is(actual,expected),`${why}: got ${String(actual)}, expected ${String(expected)}`);}
function rejects(run:()=>unknown,fragment:string):void {
  let error=''; try {run();} catch (caught) {error=String(caught);}
  check(error.includes(fragment),`expected ${fragment}, got ${error || 'success'}`);
}
function watch(run:()=>void,observe:(owner:object,key:PropertyKey)=>void):void {
  const original=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((owner:object,key:PropertyKey)=>{observe(owner,key);return original(owner,key);}) as typeof original;
  try {run();} finally {Object.getOwnPropertyDescriptor=original;}
}
/** All executed leaves are genuine. Unused lower adapters expose actual records
 * only; their source-effect operations throw. No sound table is hydrated here. */
function fixture(options:{defer?:boolean;metadata?:boolean;metadataParts?:number;dispatchParts?:number;clone?:boolean;fields?:Partial<SourceActorFrameSuffixBinding>}={}) {
  const unsupported=():never=>{throw Error('unexpected unrelated source operation');};
  const joints=createSourceJObjAnimationRuntime(),feedback=createSourceJointAnimationFeedbackRuntime(joints);
  const mapping=createSourceActorJointMappingRuntime(joints,feedback,
    {interpretAObj:unsupported,animateRObjs:unsupported,animateDObjs:unsupported},{convertEulerToQuaternion:unsupported});
  const parts=Array.from({length:2},()=>Array.from({length:4},()=>mapping.createPart(
    {frame0c:0,duration24:0,segment2d:0,complete2e:0,mode2f:0,mirror30:0},
    {descriptor00:null,scaleIndex32:0,jointBank33:0,poseBuffer35:0})));
  const id=mapping.createActor({descriptor4b0:mapping.createDescriptor([]),jointCount1d90:0,
    boundary1d91:0,boundary1d92:0,boundary1d93:0,jointBank1db4:null,jointBank1db8:null,timestep1dc8:1},{parts,poses:[[],[]]});
  const dispatch=createSourceActorAnimationDispatchRuntime(mapping,feedback);
  dispatch.bindActor(id,{family1d88:null,shared1d8c:null,marker578:2,marker1db3:0});
  for (const part of parts[0]!.slice(0,options.dispatchParts??4)) dispatch.bindPart(part,{elapsed08:7,previous10:6,previous14:4,linked36:0});
  const targets=createSourceStreamWaitTargetRuntime(mapping,feedback,dispatch);
  const streams=createSourceStreamWaitRuntime({mapping,feedback,dispatch,targets});
  streams.bindActor(id,{activeMask579:0,blockedMask1d9a:0},Array.from({length:4},()=>({current00:null,wait14:0,finished1a:0,event1e:0})));
  streams.bindStartActor(id,{familyBank1d80:null,sharedBank1d84:null,defaultSelector582:0,marker709:0});
  const actual=createRomActor(); actual.borgNumber=3; actual.controlWord=0; actual.soundEventTable=null;
  const attribute={byte87:88},world={scale58:{x:1,y:1,z:1}},movement={};
  const worldSource={getActualActor:()=>actual,getActorBinding:()=>world as ReturnType<SourceActorStatusTimersSources['world']['getActorBinding']>,getMappingActor:()=>mapping.getActor(id)};
  const attributeSource={getActualActor:()=>actual,getActorBinding:()=>attribute as ReturnType<SourceActorStatusTimersSources['attributes']['getActorBinding']>,getParameterDescriptor:unsupported};
  const status=createSourceActorStatusTimersRuntime({world:worldSource,mapping,attributes:attributeSource,streams,
    movement:{getActualActor:()=>actual,getActorBinding:()=>movement as ReturnType<SourceActorStatusTimersSources['movement']['getActorBinding']>}});
  const borg={hp:100,hitDrainFrames:0,balanceGauge:10,balanceGaugeMax:10,balanceRefillDelay:0,downResetDelay:0,
    comboWindow:0,comboAccum:0,comboRank:0,invincTimer:0,sourceAmmoRefillPauseMask:0,
    downGaugeBase:100,downGauge:100,paramTier:{tier:0,deltaAccum:0,timerFrames:0}};
  const slot=()=>({cell:{cur:0,max:0,refillType:0,refillParam:0,timer:0},mirror776:0});
  status.bindActor(id,borg,{short272:5},[slot(),slot(),slot()]);
  const charge=createSourceActorInputChargeRuntime({world:worldSource,status,mapping,attributes:attributeSource,global:{},data:{}});
  charge.bindActor(id,{});
  const clone={arm7c8:7,offset7b0:{x:9,y:8,z:7}};
  if (options.clone!==false) bindDoubleNinjaOwnerState(actual,clone);
  const prehook=createSourceActorDoublePrehookRuntime({status,charge,streams});
  prehook.bindActor(id,{pointer4c0:0x8006f88c});
  const gauges=createSourceActorGaugeScaleRuntime({world:worldSource,status}); gauges.bindActor(id,borg,{byte7c9:0});
  const attached=new Map(parts[0]!.map(part=>[part,{rewind26:0,loop2c:0}]));
  const metadata=createSourceAnimationSetupMetadataRuntime({actors:mapping,feedback,
    descriptors:{readByte:unsupported},attached:{getPartBinding(part){const value=attached.get(part);if(!value) return unsupported();return value;}}});
  metadata.bindActor(id,{byte1d74:0,byte1d75:0,byte1d76:0,byte1d77:0,byte1d94:0,byte1d95:0,byte1d98:0,byte1d99:0,byte1d9b:0});
  for (const part of parts[0]!.slice(0,options.metadataParts??4)) metadata.bindPart(part,{selector2a:0,selector2b:0,auxiliary37:255});
  const sources={prehook,gauges,dispatch,...(options.metadata?{metadata}:{})},runtime=createSourceActorFrameSuffixRuntime(sources);
  const initial=options.fields??{byte8cc:0,byte1eb:91,byte276:92},bind=()=>runtime.bindActor(id,initial);
  if (!options.defer) bind();
  return {id,actual,clone,attribute,world,mapping,status,prehook,gauges,dispatch,metadata,parts,sources,runtime,initial,bind,
    binding:()=>runtime.getActorBinding(id),gauge:()=>gauges.getActorBinding(id),statusBinding:()=>status.getActorBinding(id),
    post:()=>runtime.runPosthook(id),house:()=>runtime.runHousekeeping(id),sound:()=>runtime.runSoundEvents(id)};
}
export function runActorFrameSuffixSelfTests():void {
  {
    const x=fixture(); check(isSourceActorFrameSuffixRuntime(x.runtime),'genuine suffix brand');
    check(!isSourceActorFrameSuffixRuntime({...x.runtime}),'copied API cannot forge brand');
    check(Object.isFrozen(x.runtime)&&Object.isSealed(x.binding())&&x.binding()!==x.initial,'missing fields copied/sealed only');
    equal(x.runtime.getActualActor(x.id),x.actual,'actual owner retained'); equal(x.runtime.getAttributeBinding(x.id),x.attribute,'87 owner');
    equal(x.runtime.getGaugeBinding(x.id),x.gauge(),'7c9 owner'); equal(x.runtime.getStatusBinding(x.id),x.statusBinding(),'272 owner');
    equal(x.runtime.getPrehookBinding(x.id),x.prehook.getActorBinding(x.id),'4c0 owner');
    equal(x.post(),undefined,'genuine Double posthook return'); equal(x.clone.arm7c8,7,'clear gate off retains arm');
    x.actual.controlWord=0x02000000; x.post(); equal(x.clone.arm7c8,0,'fresh02000000 clears arm');
    equal(x.clone.offset7b0.x,9,'posthook does not reset persistent offset');
    x.house(); equal(x.binding().byte1eb,1,'product1 below2'); equal(x.binding().byte276,0,'20000000 clear');
    equal(x.sound(),undefined,'explicit null4e8 genuine return'); x.runtime.assertActorComplete(x.id);
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'completed bounded leaves do not poison');
  }
  for (const borg of [0,3,32767,32768,65535]) {
    const x=fixture({clone:false}); x.actual.borgNumber=borg; x.post();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'signed non10 returns without missing clone/6e9');
  }
  {
    const x=fixture(); x.actual.borgNumber=10; x.actual.controlWord=0x02000000;
    rejects(x.post,'unsupported Sasuke actual6e9'); equal(x.clone.arm7c8,0,'earlier clear retained before Sasuke boundary');
    rejects(x.house,'incomplete'); rejects(x.sound,'incomplete'); rejects(()=>x.prehook.runActor(x.id),'incomplete');
    const y=fixture({clone:false}); y.actual.controlWord=0x02000000; rejects(y.post,'explicit persistent clone owner');
  }
  {
    const x=fixture(); x.prehook.getActorBinding(x.id).pointer4c0=0;
    rejects(x.post,'unsupported actual4c0 target0x0'); equal(x.clone.arm7c8,7,'null pointer not synthesized no-op');
    const y=fixture(); markIncompleteSourceActorDoubleLifecycle(y.actual); rejects(y.post,'incomplete');
  }
  for (const mode of [1,2,127,128,255]) {
    const x=fixture(); x.binding().byte8cc=mode; x.actual.modelScale=NaN; x.actual.sizeScale=NaN;
    x.house(); equal(x.binding().byte1eb,mode===1?0:1,'signed8cc branch avoids scale loads');
  }
  for (const [size,model,expected] of [[1,2,0],[Math.fround(1.99999988),1,1],[2,1,0],[2,2,0],[-1,2,1],[-0,1,1]] as const) {
    const x=fixture(); x.actual.sizeScale=size; x.actual.modelScale=model; x.house();
    equal(x.binding().byte1eb,expected,'single multiply threshold and signed zero');
  }
  {
    const x=fixture(); x.actual.sizeScale=Math.fround(3e38); x.actual.modelScale=2;
    rejects(x.house,'fmuls result'); equal(x.attribute.byte87,0,'overflow keeps87 prefix'); equal(x.binding().byte1eb,91,'overflow before1eb store');
    const y=fixture(); y.actual.sizeScale=NaN; y.actual.modelScale=NaN; rejects(y.house,'sizeScale');
  }
  {
    const x=fixture(); const order:string[]=[];
    watch(x.house,(owner,key)=>{
      if (owner===x.actual&&(key==='sizeScale'||key==='modelScale')) order.push(String(key));
      if (owner===x.binding()&&key==='byte1eb') x.actual.controlWord=0x20000000;
    });
    equal(order.join(','),'sizeScale,modelScale','source7fc thenb4 load order');
    equal(x.attribute.byte87,0,'first control read retained'); equal(x.binding().byte276,1,'second control freshly reloaded after1eb');
    const y=fixture(); y.actual.controlWord=0x40; y.house(); equal(y.attribute.byte87,1,'87 bit6 extraction');
  }
  for (const gauge of [1,127,128,255]) {
    const x=fixture(); x.gauge().byte7c9=gauge; x.statusBinding().short272=-32768; x.house();
    equal(x.statusBinding().short272,-1,'signed nonzero7c9 lha/ori/sth becomes-1');
  }
  {
    const x=fixture(); x.statusBinding().short272=NaN; x.house();
    check(Number.isNaN(x.statusBinding().short272),'zero7c9 never loads272');
    const y=fixture(); y.gauge().byte7c9=1; y.statusBinding().short272=NaN;
    rejects(y.house,'short272'); equal(y.binding().byte276,0,'invalid272 occurs after276 store');
  }
  for (const key of ['byte8cc','byte1eb','byte276'] as const) {
    const fields:Partial<SourceActorFrameSuffixBinding>={byte8cc:1,byte1eb:91,byte276:92}; delete fields[key];
    const x=fixture({fields}); check(!Object.hasOwn(x.binding(),key),'missing field never defaulted');
    rejects(x.house,key); equal(x.attribute.byte87,0,'missing suffix field retains87');
    if (key==='byte276') equal(x.binding().byte1eb,0,'missing276 retains1eb');
  }
  for (const key of ['byte87','byte1eb','byte276','short272','arm7c8'] as const) {
    const x=fixture(); x.actual.controlWord=0x02000040; x.gauge().byte7c9=1;
    const owner=key==='byte87'?x.attribute:key==='short272'?x.statusBinding():key==='arm7c8'?x.clone:x.binding();
    Object.defineProperty(owner,key,{writable:false}); rejects(key==='arm7c8'?x.post:x.house,`${key}: non-writable`);
    if (key==='short272') {equal(x.binding().byte276,0,'272 refusal preserves276');equal(x.statusBinding().short272,5,'readonly272 retained');}
    if (key==='byte276') equal(x.binding().byte1eb,1,'276 refusal preserves1eb');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'write refusal permanently latches shared lifecycle');
  }
  {
    const x=fixture(); for (const key of ['controlWord','borgNumber','sizeScale','modelScale','soundEventTable']) Object.defineProperty(x.actual,key,{writable:false});
    Object.defineProperty(x.binding(),'byte8cc',{writable:false}); Object.defineProperty(x.gauge(),'byte7c9',{writable:false});
    x.post(); x.house(); x.sound(); equal(x.binding().byte1eb,1,'readonly input fields admitted');
  }
  {
    const x=fixture({defer:true}); Object.assign(x.actual,{byte8cc:0}); rejects(x.bind,'competing');
    delete (x.actual as unknown as Record<string,unknown>).byte8cc; x.bind();
    Object.assign(x.world,{soundEventTable4e8:null}); rejects(x.sound,'competing');
    const y=fixture(); const second=createSourceActorFrameSuffixRuntime(y.sources);
    rejects(()=>second.bindActor(y.id,{}),'already claimed');
    for (const key of ['prehook','gauges','dispatch'] as const) rejects(()=>createSourceActorFrameSuffixRuntime({...y.sources,[key]:{...y.sources[key]}}),'genuine');
    const z=fixture({metadata:true}); rejects(()=>createSourceActorFrameSuffixRuntime({...z.sources,metadata:{...z.metadata}}),'genuine');
  }
  {
    const x=fixture(); let triggered=false;
    watch(()=>rejects(x.house,'caught same-runtime reentry'),(owner,key)=>{
      if (!triggered&&owner===x.actual&&key==='controlWord') {triggered=true;try{x.sound();}catch{/* outer remains poisoned */}}
    });
    equal(x.attribute.byte87,88,'caught reentry blocks first store'); check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'caught reentry latches');
    rejects(x.house,'incomplete');
  }
  {
    const x=fixture(); let triggered=false;
    watch(()=>rejects(x.house,'caught same-runtime reentry'),(owner,key)=>{
      if(!triggered&&owner===x.binding()&&key==='byte1eb') {triggered=true;try{x.post();}catch{/* keep prior87 */}}
    });
    equal(x.attribute.byte87,0,'caught late reentry retains87 prefix'); equal(x.binding().byte1eb,91,'poison prevents1eb store');
    const y=fixture(); y.actual.controlWord=0x02000000; y.clone.arm7c8=NaN;
    y.post(); equal(y.clone.arm7c8,0,'posthook overwrites arm without loading its old value');
  }
  {
    const x=fixture({metadata:true,metadataParts:0,dispatchParts:0}); x.sound();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'null sound needs no unbound metadata or dispatch parts');
    x.actual.soundEventTable=new Uint8Array(0); rejects(x.sound,'unknown/non-owned metadata part');
    const y=fixture({metadata:true,metadataParts:3,dispatchParts:0}); y.actual.soundEventTable=new Uint8Array(0);
    rejects(y.sound,'unknown/non-owned metadata part');
    const z=fixture({metadata:true,dispatchParts:0}); z.actual.soundEventTable=new Uint8Array(0); z.sound();
    check(!hasIncompleteSourceActorDoubleLifecycle(z.actual),'explicit four-1 skip needs no dispatch bindings');
  }
  {
    const x=fixture({metadata:true}); const owners=x.runtime.getSourceOwners(x.id);
    for (const part of x.parts[0]!) check(owners.includes(x.metadata.getPartBinding(part)),'all metadata records excluded from host raw aliases');
    x.actual.soundEventTable=new Uint8Array(0); x.actual.sizeScale=NaN;
    x.sound(); equal(x.actual.soundEventTable.length,0,'all four explicit-1 skip without any payload or scale reads');
    for (const part of x.parts[0]!) equal(x.metadata.getPartBinding(part).auxiliary37,255,'sound scan never rewrites metadata');
    check(x.runtime.getSourceOwners(x.id).includes(x.actual.soundEventTable),'nonnull table excluded from raw aliases');
    const y=fixture(); y.actual.soundEventTable=new Uint8Array(0); rejects(y.sound,'auxiliary37 metadata owner');
  }
  {
    const x=fixture({metadata:true}); x.actual.soundEventTable=new Uint8Array(8);
    x.metadata.getPartBinding(x.parts[0]![0]!).auxiliary37=0;
    rejects(x.sound,'actual8005b98c sound event at byte0 (current=7, previous=6)');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'reached event refuses permanently');
    const y=fixture({metadata:true}); y.actual.soundEventTable=new Uint8Array(8);
    y.metadata.getPartBinding(y.parts[0]![0]!).auxiliary37=254; rejects(y.sound,'negative sound event index -2');
    const z=fixture({metadata:true}); z.actual.soundEventTable=new Uint8Array(2);
    z.metadata.getPartBinding(z.parts[0]![0]!).auxiliary37=0; rejects(z.sound,'2: own data property');
  }
  {
    const x=fixture({metadata:true}),part=x.parts[0]![0]!;
    x.actual.soundEventTable=new Uint8Array(8); x.metadata.getPartBinding(part).auxiliary37=0;
    const fresh=Uint8Array.from([0,0,1,0,0,0,255,0]);
    x.dispatch.getActualFeedback().getPart(part).frame0c=5;
    x.dispatch.getActualFeedback().getPart(part).duration24=NaN;
    watch(()=>rejects(x.sound,'current=5, previous=4'),(owner,key)=>{
      if(owner===x.metadata.getPartBinding(part)&&key==='auxiliary37') x.actual.soundEventTable=fresh;
    });
    const y=fixture({metadata:true}),other=y.parts[0]![0]!;
    y.actual.soundEventTable=new Uint8Array(8); y.metadata.getPartBinding(other).auxiliary37=0;
    y.dispatch.getActualFeedback().getPart(other).frame0c=NaN;
    y.dispatch.getPartBinding(other).previous14=NaN;
    rejects(y.sound,'current=7, previous=6');
    const z=fixture({metadata:true}),last=z.parts[0]![0]!;
    z.actual.soundEventTable=new Uint8Array(8); z.metadata.getPartBinding(last).auxiliary37=0;
    watch(()=>rejects(z.sound,'fresh actual4e8'),(owner,key)=>{
      if(owner===z.metadata.getPartBinding(last)&&key==='auxiliary37') z.actual.soundEventTable=null;
    });
  }
  for (const [now,previous,duration,expected] of [[5,4,99,5],[4,4,99,4],[1,4,10,11],[1,4,-2,-1]] as const) {
    const x=fixture({metadata:true}),part=x.parts[0]![0]!; x.actual.soundEventTable=Uint8Array.from([0,0,1,0,0,0,255,0]);
    x.metadata.getPartBinding(part).auxiliary37=0;
    const state=x.dispatch.getActualFeedback().getPart(part); state.frame0c=now; state.duration24=duration;
    x.dispatch.getPartBinding(part).previous14=previous;
    rejects(x.sound,`actual8005b98c sound event at byte0 (current=${expected}, previous=${previous})`);
  }
  {
    const x=fixture({metadata:true}); x.actual.soundEventTable=new Uint8Array(8);
    x.metadata.getPartBinding(x.parts[0]![3]!).auxiliary37=0;
    rejects(x.sound,'actual8005b98c');
    const y=fixture({metadata:true}); y.actual.soundEventTable=new Uint8Array(8);
    y.metadata.getPartBinding(y.parts[0]![1]!).auxiliary37=256;
    rejects(y.sound,'auxiliary37');
  }
  console.log('[actor-frame-suffix-test] source posthook, signed housekeeping, explicit no-event sound returns and retained refusal boundaries passed');
}
