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
import {createSourceActorSoundTable,readSourceActorSoundTableByte} from './actor-sound-table.js';
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
// Synthetic bounded payloads exercise the authenticated instructions, not retail
// hydration or audio execution. The fourth byte is kind; byte2 only picks clocks.
function event(frame:number,window=0,kind=0,soundId=0,marker=255):Uint8Array {
  return Uint8Array.from([frame>>>8,frame&255,window,kind,soundId>>>8,soundId&255,marker,0]);
}
function soundFixture(table:Uint8Array=event(7)) {
  const x=fixture({metadata:true}),part=x.parts[0]![0]!;
  x.actual.soundEventTable=table; x.metadata.getPartBinding(part).auxiliary37=0;
  return {...x,table,part,clock:x.dispatch.getPartBinding(part),feedback:x.dispatch.getActualFeedback().getPart(part)};
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
    const x=soundFixture(event(7,0,0,0xabcd));
    rejects(x.sound,'actual800f036c sound event at byte0 (current=7, previous=6, kind=0, soundId=43981)');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'reached audio refuses permanently');
    x.actual.soundEventTable=null; rejects(x.sound,'incomplete'); rejects(x.house,'incomplete'); rejects(x.post,'incomplete');
    const y=soundFixture(); y.metadata.getPartBinding(y.part).auxiliary37=254;
    rejects(y.sound,'negative sound event index -2');
    const z=soundFixture(new Uint8Array(2)); rejects(z.sound,'2: own data property');
  }
  // All u16 event frames convert exactly. Positive gates are (previous,current]
  // crossings with strict previous<frame, not a signed16 or current-only test.
  for (const frame of [1,7,32768,65535]) for (const now of [frame-1,frame,frame+1])
    for (const previous of [frame-1,frame,frame+1]) {
      const x=soundFixture(event(frame,0,0,0x1234)); x.clock.elapsed08=now; x.clock.previous10=previous;
      if(now>=frame&&previous<frame) rejects(x.sound,'soundId=4660)');
      else {x.sound();check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'noncrossing helper and chain genuinely return');}
    }
  for (const now of [-Math.fround(3e38),-(2**-149),-0,0,2**-149,1]) for (const previous of [-1,0,1]) {
    const x=soundFixture(event(0)); x.clock.elapsed08=now; x.clock.previous10=previous;
    if(now<=0) rejects(x.sound,'actual800f036c'); else x.sound();
  }
  for (const kind of [4,127,128,255]) {
    const x=soundFixture(event(7,0,kind)); x.actual.modelScale=NaN; x.table[4]=255; x.table[5]=255;
    const bytes:string[]=[]; watch(x.sound,(owner,key)=>{if(owner===x.table&&/^\d+$/.test(String(key))) bytes.push(String(key));});
    equal(bytes.join(','),'2,0,1,3,6','unsigned kind>=4 returns without id/padding reads');
    x.runtime.assertActorComplete(x.id);
  }
  {
    const x=soundFixture(event(8,0,1)); x.actual.modelScale=NaN;
    const bytes:string[]=[]; watch(x.sound,(owner,key)=>{if(owner===x.table&&/^\d+$/.test(String(key))) bytes.push(String(key));});
    equal(bytes.join(','),'2,0,1,6','nonfiring event skips kind/id/scale then reads marker');
    const y=soundFixture(event(7,0,0)); y.actual.modelScale=NaN; y.feedback.frame0c=NaN; y.clock.previous14=NaN;
    rejects(y.sound,'current=7, previous=6');
  }
  // Byte2 selects elapsed vs frame clocks independently of byte3 dispatch kind.
  for (const window of [1,2,128,255]) {
    const x=soundFixture(event(5,window,0,2)); x.feedback.frame0c=5; x.clock.previous14=4;
    x.feedback.duration24=NaN; x.clock.elapsed08=NaN; x.clock.previous10=NaN;
    rejects(x.sound,'current=5, previous=4, kind=0, soundId=2');
    const y=soundFixture(event(6,window,1)); y.feedback.frame0c=5; y.clock.previous14=4;
    y.feedback.duration24=NaN; y.actual.modelScale=NaN; y.sound();
  }
  for (const [now,previous,duration,frame,expected] of [
    [5,4,NaN,5,5],[1,4,10,11,11],[1,4,-2,0,-1],[-1,0,32767,32766,32766],
    [1,4,-32768,0,-32767],[Math.fround(1.0000001192092896),2,10,11,11],
  ] as const) {
    const x=soundFixture(event(frame,1)); x.feedback.frame0c=now; x.feedback.duration24=duration; x.clock.previous14=previous;
    rejects(x.sound,`actual800f036c sound event at byte0 (current=${expected}, previous=${previous}`);
  }
  {
    const x=soundFixture(event(5,1,1)); x.feedback.frame0c=4; x.clock.previous14=4;
    x.feedback.duration24=NaN; x.actual.modelScale=NaN; x.sound();
    const y=soundFixture(event(12,1,1)); y.feedback.frame0c=1; y.clock.previous14=4;
    y.feedback.duration24=10; y.actual.modelScale=NaN; y.sound();
  }
  for (const [scale,id,expected] of [
    [Math.fround(0.6999999),1,0],[0.699999988079071,1,1],[Math.fround(0.7000001),1,1],
    [Math.fround(1.9999999),65535,65535],[2,65535,65535],[Math.fround(2.0000002),65535,65536],
    [-0,0,4294967295],[-1,65535,65534],[Math.fround(3e38),0,1],
  ] as const) {
    const x=soundFixture(event(7,0,1,id)); x.actual.modelScale=scale;
    const order:string[]=[];
    watch(()=>rejects(x.sound,`kind=1, soundId=${expected})`),(owner,key)=>{
      if(owner===x.table&&/^\d+$/.test(String(key))) order.push(String(key));
      if(owner===x.actual&&key==='modelScale') order.push('modelScale');
    });
    equal(order.join(','),'2,0,1,3,modelScale,4,5','one scale load precedes id and audio refusal precedes marker');
  }
  for (const kind of [2,3]) {
    const x=soundFixture(event(7,0,kind,65535)); x.actual.modelScale=NaN;
    const order:string[]=[];
    watch(()=>rejects(x.sound,`actual800f061c sound event at byte0 (current=7, previous=6, kind=${kind}, soundId=65535, scalar=0.20000000298023224)`),
      (owner,key)=>{if(owner===x.table&&/^\d+$/.test(String(key))) order.push(String(key));});
    equal(order.join(','),'2,0,1,3,4,5','2/3 id precedes scalar/audio boundary, no marker');
  }
  for (const value of [NaN,Infinity,-Infinity,0.7]) {
    const x=soundFixture(event(7,0,1)); x.actual.modelScale=value;
    const order:string[]=[]; watch(()=>rejects(x.sound,'modelScale: finite exact source float32'),
      (owner,key)=>{if(owner===x.table&&/^\d+$/.test(String(key))) order.push(String(key));});
    equal(order.join(','),'2,0,1,3','invalid reached scale fails before id and marker');
  }
  {
    const x=soundFixture(event(7,0,1)); delete (x.actual as unknown as Record<string,unknown>).modelScale;
    rejects(x.sound,'modelScale: own data property');
    const y=soundFixture(event(7,0,1)); let called=false;
    Object.defineProperty(y.actual,'modelScale',{get(){called=true;return 1;}});
    rejects(y.sound,'modelScale: own data property'); check(!called,'source accessor rejected without invoking getter');
    const z=soundFixture(event(8,0,1)); delete (z.actual as unknown as Record<string,unknown>).modelScale;
    z.sound(); check(!hasIncompleteSourceActorDoubleLifecycle(z.actual),'unread missing scale does not fail');
  }
  // Truncated arrays fail only at reached bytes. Byte7 is never required and
  // an audio boundary must precede even a missing marker after its call.
  for (const [length,frame,kind,fragment] of [
    [0,7,0,'2: own data property'],[2,7,0,'2: own data property'],[3,7,0,'3: own data property'],
    [3,8,0,'6: own data property'],[4,7,0,'4: own data property'],[5,7,0,'5: own data property'],
    [6,7,0,'actual800f036c'],[6,7,4,'6: own data property'],[6,8,0,'6: own data property'],
  ] as const) {
    const x=soundFixture(event(frame,0,kind).slice(0,length)); rejects(x.sound,fragment);
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'truncation/boundary latches shared lifecycle');
  }
  for (const [frame,kind] of [[8,0],[7,4],[7,255]] as const) {
    const x=soundFixture(event(frame,0,kind).slice(0,7)); x.sound();
    check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'terminal seven-byte decoded view never reads padding');
  }
  {
    const x=soundFixture(event(7,0,1).slice(0,4)); x.actual.modelScale=NaN;
    rejects(x.sound,'modelScale: finite exact source float32');
    const y=soundFixture(event(7,0,1).slice(0,4)); y.actual.modelScale=1;
    rejects(y.sound,'4: own data property');
  }
  for (const marker of [0,1,127,128,254]) {
    const first=event(8,0,1,65535,marker),last=event(7,0,255);
    const x=soundFixture(Uint8Array.from([...first,...last]).slice(0,15)); x.actual.modelScale=NaN;
    const bytes:string[]=[]; watch(x.sound,(owner,key)=>{if(owner===x.table&&/^\d+$/.test(String(key))) bytes.push(String(key));});
    equal(bytes.join(','),'2,0,1,6,10,8,9,11,14','non-ff chain marker advances by8, never indexes marker');
    const y=soundFixture(first); rejects(y.sound,'10: own data property');
  }
  {
    const x=soundFixture(Uint8Array.from([...event(8,0,1,0,0),...event(12)]));
    x.feedback.frame0c=0; x.clock.previous14=0;
    const order:string[]=[];
    watch(()=>rejects(x.sound,'byte8 (current=12, previous=11'),(owner,key)=>{
      if(owner===x.table&&/^\d+$/.test(String(key))) {
        order.push(String(key));
        if(key==='6') {x.table[10]=255;x.feedback.frame0c=12;x.clock.previous14=11;x.clock.elapsed08=NaN;}
      }
    });
    equal(order.join(','),'2,0,1,6,10,8,9,11,12,13','fresh per-record byte2/clocks and no marker after firing second event');
    const y=soundFixture(Uint8Array.from([...event(8,0,0,0,0),...event(9)]));
    watch(()=>rejects(y.sound,'byte8 (current=9, previous=8'),(owner,key)=>{
      if(owner===y.table&&key==='6') {y.clock.elapsed08=9;y.clock.previous10=8;}
    });
  }
  {
    const x=soundFixture(Uint8Array.from([...event(7,0,255,0,0),...event(7,0,255)]));
    x.metadata.getPartBinding(x.parts[0]![1]!).auxiliary37=0;
    const fresh=event(7,0,255),order:string[]=[];
    watch(x.sound,(owner,key)=>{
      if((owner===x.table||owner===fresh)&&/^\d+$/.test(String(key))) {
        order.push(`${owner===x.table?'old':'fresh'}:${String(key)}`);
        if(owner===x.table&&key==='3') x.actual.soundEventTable=fresh;
      }
    });
    equal(order.join(','),'old:2,old:0,old:1,old:3,old:6,old:10,old:8,old:9,old:11,old:14,fresh:2,fresh:0,fresh:1,fresh:3,fresh:6',
      'old pointer retained for helper/marker/continuation and reloaded only on next active row');
    const y=soundFixture(event(7,0,255));
    watch(y.sound,(owner,key)=>{if(owner===y.table&&key==='3') y.actual.soundEventTable=null;});
    check(!hasIncompleteSourceActorDoubleLifecycle(y.actual),'terminal marker still uses old table after pointer becomes null');
  }
  {
    const x=soundFixture(); const fresh=event(5,1);
    x.feedback.frame0c=5; x.feedback.duration24=NaN;
    watch(()=>rejects(x.sound,'current=5, previous=4'),(owner,key)=>{
      if(owner===x.metadata.getPartBinding(x.part)&&key==='auxiliary37') x.actual.soundEventTable=fresh;
    });
    const y=soundFixture();
    watch(()=>rejects(y.sound,'fresh actual4e8'),(owner,key)=>{
      if(owner===y.metadata.getPartBinding(y.part)&&key==='auxiliary37') y.actual.soundEventTable=null;
    });
  }
  {
    const table=Uint8Array.from([0,1,2,3].flatMap(i=>[...event(7,0,255,i)])),x=soundFixture(table);
    const rowIds=x.parts[0]!,rows=rowIds.map(part=>x.metadata.getPartBinding(part));
    rows.forEach((row,i)=>{row.auxiliary37=i;});
    const order:string[]=[];
    watch(x.sound,(owner,key)=>{
      const row=rows.indexOf(owner as typeof rows[number]);if(row!==-1&&key==='auxiliary37') order.push(`row${row}`);
      if(owner===table&&key==='6') rows[1]!.auxiliary37=2;
      if(owner===table&&/^\d+$/.test(String(key))) order.push(String(key));
    });
    equal(order.join(','),'row0,2,0,1,3,6,row1,18,16,17,19,22,row2,18,16,17,19,22,row3,26,24,25,27,30',
      'four rows visited in order with fresh selector and selected record, not cached row values');
    const y=fixture({metadata:true}); y.actual.soundEventTable=event(7);
    y.metadata.getPartBinding(y.parts[0]![3]!).auxiliary37=0; rejects(y.sound,'actual800f036c');
    const z=fixture({metadata:true}); z.actual.soundEventTable=event(7);
    z.metadata.getPartBinding(z.parts[0]![1]!).auxiliary37=256; rejects(z.sound,'auxiliary37');
  }
  {
    const x=soundFixture(event(7)); x.metadata.getPartBinding(x.part).auxiliary37=127;
    rejects(x.sound,'1018: own data property');
    const y=soundFixture(Uint8Array.from([...new Uint8Array(8),...event(7,0,255)]));
    y.metadata.getPartBinding(y.part).auxiliary37=1; y.sound();
    const z=soundFixture(); (z.actual as unknown as Record<string,unknown>).soundEventTable={};
    rejects(z.sound,'actual4e8 requires explicit decoded');
  }
  // Disjoint decoded windows keep their true offsets and refuse only reached
  // gaps. Missing id bytes are fine on a returning predicate/kind path.
  for (const [frame,kind] of [[8,1],[7,4],[7,255]] as const) {
    const x=soundFixture(),payload=event(frame,0,kind),offset=127*8;
    x.actual.soundEventTable=createSourceActorSoundTable([
      {offset,bytes:payload.slice(0,4)},{offset:offset+6,bytes:payload.slice(6,7)},
    ]);
    x.metadata.getPartBinding(x.part).auxiliary37=127; x.actual.modelScale=NaN;
    x.sound(); x.runtime.assertActorComplete(x.id);
    check(x.runtime.getSourceOwners(x.id).includes(x.actual.soundEventTable),'opaque source table remains canonical excluded owner');
  }
  {
    const x=soundFixture(),payload=event(7,0,255);
    x.actual.soundEventTable=createSourceActorSoundTable([{offset:0,bytes:payload.slice(0,4)}]);
    rejects(x.sound,'uncovered'); check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'reached uncovered marker latches lifecycle');
    const y=soundFixture(),firing=event(7);
    y.actual.soundEventTable=createSourceActorSoundTable([{offset:0,bytes:firing.slice(0,6)}]);
    rejects(y.sound,'actual800f036c');
    const z=soundFixture();
    z.actual.soundEventTable=createSourceActorSoundTable([{offset:2,bytes:Uint8Array.of(0)}]);
    z.clock.elapsed08=NaN; rejects(z.sound,'elapsed08');
  }
  {
    const x=soundFixture(),payload=event(8,0,0,0,0);
    x.actual.soundEventTable=createSourceActorSoundTable([
      {offset:0,bytes:payload.slice(0,3)},{offset:6,bytes:payload.slice(6,7)},
      {offset:8,bytes:event(7,0,255).slice(0,4)},{offset:14,bytes:Uint8Array.of(255)},
    ]);
    x.sound(); check(!hasIncompleteSourceActorDoubleLifecycle(x.actual),'chain spans disjoint covered reads without invented padding/id');
    const y=soundFixture();
    y.actual.soundEventTable=createSourceActorSoundTable([{offset:0,bytes:payload.slice(0,7)}]);
    rejects(y.sound,'uncovered');
    const z=soundFixture();let called=false;
    (z.actual as unknown as Record<string,unknown>).soundEventTable={readByte(){called=true;return 255;}};
    rejects(z.sound,'actual4e8 requires explicit decoded'); check(!called,'arbitrary table callback cannot inject success');
  }
  for (const [windows,fragment] of [
    [[{offset:2,bytes:Uint8Array.of(0)}],'byte0: uncovered'],
    [[{offset:0,bytes:Uint8Array.of(0)},{offset:2,bytes:Uint8Array.of(0)}],'byte1: uncovered'],
    [[{offset:0,bytes:Uint8Array.of(0,7,0)}],'byte3: uncovered'],
  ] as const) {
    const x=soundFixture();x.actual.soundEventTable=createSourceActorSoundTable(windows);rejects(x.sound,fragment);
  }
  {
    const x=fixture({metadata:true});
    (x.actual as unknown as Record<string,unknown>).soundEventTable=Object.create(Uint8Array.prototype);
    rejects(x.sound,'actual4e8 requires explicit decoded');
    const y=soundFixture(event(8));let child=false;
    watch(()=>rejects(y.sound,'[actor-sound-table] caught same-runtime reentry'),(owner,key)=>{
      if(!child&&owner===y.table&&key==='0') {child=true;try{readSourceActorSoundTableByte(y.table,0);}catch{/* child read stays poisoned */}}
    });
    check(hasIncompleteSourceActorDoubleLifecycle(y.actual),'caught child read reentry permanently latches actor');
    y.actual.soundEventTable=null;rejects(y.sound,'incomplete');
  }
  for (const window of [0,1]) {
    const x=soundFixture(event(7,window,255)),order:string[]=[];
    if(window!==0) {x.feedback.frame0c=3;x.clock.previous14=4;x.feedback.duration24=4;}
    watch(x.sound,(owner,key)=>{
      if(owner===x.table&&/^\d+$/.test(String(key))) order.push(String(key));
      if(owner===x.clock&&(key==='elapsed08'||key==='previous10'||key==='previous14')) order.push(String(key));
      if(owner===x.feedback&&(key==='frame0c'||key==='duration24')) order.push(String(key));
    });
    equal(order.join(','),window===0?'2,elapsed08,previous10,0,1,3,6':'2,frame0c,previous14,duration24,0,1,3,6',
      'clock/duration source reads precede helper frame load and terminating marker');
  }
  // Missing/invalid reached clocks retain the exact source read prefix. Zero
  // event time does not inspect previous in the callee, but caller still loads it.
  for (const [window,key] of [[0,'elapsed08'],[0,'previous10'],[1,'frame0c'],[1,'previous14']] as const) {
    for (const invalid of [NaN,Infinity,0.1]) {
      const x=soundFixture(event(0,window)),owner=key==='frame0c'?x.feedback:x.clock;
      (owner as unknown as Record<string,unknown>)[key]=invalid; rejects(x.sound,`${key}: finite exact source float32`);
    }
    const y=soundFixture(event(0,window)),owner=key==='frame0c'?y.feedback:y.clock;
    // Explicit undefined is missing decoded data, not a default source zero.
    (owner as unknown as Record<string,unknown>)[key]=undefined; rejects(y.sound,`${key}: finite exact source float32`);
  }
  for (const duration of [NaN,32768,-32769,0.5]) {
    const x=soundFixture(event(7,1)); x.feedback.frame0c=1; x.clock.previous14=4; x.feedback.duration24=duration;
    rejects(x.sound,'duration24: integer out of bounds');
  }
  {
    const x=soundFixture(event(7,0,1)),order:string[]=[];let triggered=false;
    watch(()=>rejects(x.sound,'caught same-runtime reentry'),(owner,key)=>{
      if(owner===x.table&&/^\d+$/.test(String(key))) order.push(String(key));
      if(!triggered&&owner===x.actual&&key==='modelScale') {triggered=true;try{x.sound();}catch{/* outer must fail before id */}}
    });
    equal(order.join(','),'2,0,1,3','caught helper reentry cannot reach id/audio/marker');
    check(hasIncompleteSourceActorDoubleLifecycle(x.actual),'helper reentry permanently latches');
    const y=soundFixture(event(8)); let late=false;
    watch(()=>rejects(y.sound,'caught same-runtime reentry'),(owner,key)=>{
      if(!late&&owner===y.table&&key==='6') {late=true;try{y.house();}catch{/* outer must fail at marker */}}
    });
    check(hasIncompleteSourceActorDoubleLifecycle(y.actual),'returning-chain reentry permanently latches');
  }
  console.log('[actor-frame-suffix-test] source posthook, housekeeping, exact sound predicates/operands and returning event-chain traversal passed; audio remains refused');
}
