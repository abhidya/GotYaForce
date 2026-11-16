/** Active47904 uses real shared owners and preconstructed canonical row12. */
import {createBattleOrderedActorStageTestFixture} from './battle-ordered-actor-stage.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[actor-matrix-active-test] '+why);}
function refuses(run:()=>unknown,part:string):void{let m='';try{run();}catch(e){m=String(e);}check(m.includes(part),`expected ${part}, got ${m||'success'}`);}
export function runActorMatrixActiveSelfTests(make:Make,smallMake?:Make):void{
 let count=0;
 const fresh=(commands=true,join=true)=>{
  count++;const x=createBattleOrderedActorStageTestFixture(make);
  if(join)x.normal.bindActiveCorrectionSources(x.stageBounds,commands?x.commandAdmission:undefined);
  x.sourceActor.controlWord=0;x.sourceActor.heading=0;x.sourceActor.flyer741=0;
  x.header.mode4a0=0;x.metadata.getActorBinding(x.actor).byte1d98=1;
  x.movement.getActorBinding(x.actor).byte661=0;x.normalState.byte660=0;
  x.stageState.lifecycle18=1;x.commandAdmission.getActorBinding(x.actor).pointer508=null;
  const row=x.world.getStorage(x.actor).corrections18d4[12]!;
  check(row!==undefined,'13 source correction rows constructed at entry');row.x=100;row.y=-100;
  return Object.assign(x,{correction12:row,commandState508:x.commandAdmission.getActorBinding(x.actor)});
 };
 type F=ReturnType<typeof fresh>;
 const observe=(x:F,visit:(o:object,k:PropertyKey)=>void)=>{
  const native=Object.getOwnPropertyDescriptor;let active=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(o===x.stageState&&k==='lifecycle18')active=true;
   if(active)visit(o,k);return native(o,k);
  }) as typeof native;
  try{x.normal.updateActor(x.actor);}finally{Object.getOwnPropertyDescriptor=native;}
 };
 {
  const x=fresh();let pointers=0,headings=0;
  observe(x,(o,k)=>{if(o===x.commandState508&&k==='pointer508')pointers++;if(o===x.sourceActor&&k==='heading')headings++;});
  check(x.correction12.x===96&&x.correction12.y===-96,'ordinary null-target helper damping');
  check(pointers===2&&headings===2,'66580 and6c728 fresh508, caller freshheading');
 }
 for(const control of [1,2,3]){
  const x=fresh();x.sourceActor.controlWord=control;let pointers=0;
  observe(x,(o,k)=>{if(o===x.commandState508&&k==='pointer508')pointers++;});
  check(pointers===1&&x.correction12.x===96&&x.correction12.y===-96,'low2control uses local damping without helper508');
 }
 for(const life of [0,2,255]){
  const x=fresh();x.stageState.lifecycle18=life;const stores:string[]=[];
  observe(x,(o,k)=>{if(o===x.correction12&&(k==='x'||k==='y'))stores.push(String(k));});
  check(x.correction12.x===0&&x.correction12.y===0,'nonlife1 source clears before damping');
  check(stores[0]==='y','initial clearY precedes clearX');
 }
 {
  const x=fresh();x.sourceActor.controlWord=0x01000000;x.normal.updateActor(x.actor);
  check(x.correction12.x===0&&x.correction12.y===0,'actualcontrolbit24 clears');
 }
 {
  const x=fresh();x.correction12.x=32767;x.correction12.y=-32768;x.normal.updateActor(x.actor);
  check(x.correction12.x===31456&&x.correction12.y===-31457,'signedhalf extrema f32 multiply then trunc');
 }
 {
  const x=fresh();x.correction12.x=1;x.correction12.y=-1;x.normal.updateActor(x.actor);
  check(Object.is(x.correction12.x,0)&&Object.is(x.correction12.y,0),'sourceintegerzero not negativezero or floor');
 }
 for(const delta of [0x5000,-0x5000,0x4fff,-0x4fff]){
  const x=fresh();let headings=0,pointers=0;
  observe(x,(o,k)=>{
   if(o===x.sourceActor&&k==='heading'&&++headings===2)x.sourceActor.heading=(-delta)&65535;
   if(o===x.commandState508&&k==='pointer508')pointers++;
  });
  check(pointers===(Math.abs(delta)===0x5000?1:2),'strict signed delta thresholds with live callerheading');
 }
 {
  const x=fresh();let reads=0;
  refuses(()=>observe(x,(o,k)=>{if(o===x.commandState508&&k==='pointer508'&&++reads===2)x.commandState508.pointer508={};}),'nonnull508 geometry');
  check(reads===2&&x.correction12.x===100&&x.correction12.y===-100,'fresh helperpointer refuses before damping');
 }
 {
  const x=fresh();x.commandState508.pointer508={};x.stageState.lifecycle18=2;
  refuses(()=>x.normal.updateActor(x.actor),'66580 nonnull508');check(x.correction12.x===0&&x.correction12.y===0,'nonnull heading path retains earlier clearstores');
 }
 {
  const x=fresh(false);x.stageState.lifecycle18=0;
  refuses(()=>x.normal.updateActor(x.actor),'genuine shared command508');check(x.correction12.x===0&&x.correction12.y===0,'missingcommand after reachedclears');
 }
 {
  const x=fresh();Object.defineProperty(x.correction12,'y',{writable:false});
  refuses(()=>x.normal.updateActor(x.actor),'y:');check(x.correction12.x===96&&x.correction12.y===-100,'readonlyY retains priorX damping');
 }
 {
  const x=fresh();x.stageState.lifecycle18=2;Object.defineProperty(x.correction12,'x',{writable:false});
  refuses(()=>x.normal.updateActor(x.actor),'x:');check(x.correction12.y===0&&x.correction12.x===100,'readonlyX retains earlierY clear');
 }
 {
  const x=fresh();let caught=false;
  refuses(()=>observe(x,(o,k)=>{if(o===x.commandState508&&k==='pointer508'&&!caught){caught=true;try{x.normal.updateActor(x.actor);}catch{}}}),'reentry');
  check(caught&&x.correction12.x===100&&x.correction12.y===-100,'caught inner reentry stops later writes');
 }
 {
  const x=fresh();Object.assign(x.sourceActor,{pointer508:null});
  refuses(()=>x.normal.updateActor(x.actor),'competing source cell');check(x.correction12.x===100,'no duplicate target owner');
 }
 {
  const x=fresh();Object.assign(x.sourceActor,{field191c:100});
  refuses(()=>x.normal.updateActor(x.actor),'competing source cell');check(x.correction12.x===100,'no duplicate correction cell');
 }
 {
  const x=fresh(true,false);refuses(()=>x.normal.bindActiveCorrectionSources({...x.stageBounds},x.commandAdmission),'genuine stage');
  x.normal.bindActiveCorrectionSources(x.stageBounds,x.commandAdmission);
  refuses(()=>x.normal.bindActiveCorrectionSources(x.stageBounds,x.commandAdmission),'once');
  x.normal.updateActor(x.actor);
 }
 if(smallMake){
  count++;const x=createBattleOrderedActorStageTestFixture(smallMake);
  x.normal.bindActiveCorrectionSources(x.stageBounds,x.commandAdmission);
  x.sourceActor.controlWord=0;x.header.mode4a0=0;x.metadata.getActorBinding(x.actor).byte1d98=1;
  x.movement.getActorBinding(x.actor).byte661=0;x.normalState.byte660=0;x.stageState.lifecycle18=1;
  x.commandAdmission.getActorBinding(x.actor).pointer508=null;
  check(x.world.getStorage(x.actor).corrections18d4.length===2,'historical storage remains two rows');
  refuses(()=>x.normal.updateActor(x.actor),'explicit canonical correction row12');
  check(x.world.getStorage(x.actor).corrections18d4.length===2,'missing source slot never fabricated');
 }
 console.log(`[actor-matrix-active] PASS: ${count} genuine fixtures; active47904 clears, liveheading/target, source truncation, canonicalrow12 and partial closure`);
}
