import {createBattleOrderedActorStageTestFixture} from './battle-ordered-actor-stage.selftest.js';
import type {createBattleTargetPreparationTestFixture} from './attached-setup-animation.selftest.js';
type Make=typeof createBattleTargetPreparationTestFixture;
function check(ok:boolean,why:string):void{if(!ok)throw Error('[battle-team-candidates-test] '+why);}
function refuses(f:()=>unknown,part:string):void{let message='';try{f();}catch(e){message=String(e);}check(message.includes(part),`expected ${part}, got ${message}`);}
export function runBattleTeamCandidatesSelfTests(make:Make):void{
 let cases=0;
 const fresh=()=>{cases++;const x=createBattleOrderedActorStageTestFixture(make);x.matchGlobals.maskD2=255;x.sourceActor.visibilityBit=1;return x;};
 {
  const x=fresh();refuses(()=>x.frame.runFrame(),'8002948c reached mandatory80087cf0');
  check(x.massPreparation.teamCounts[0]===1&&x.teamRows103[0]!.charged,'real nonempty charged team is not bypassed');
  check(x.status.getActualBorg(x.actor).burstArmFrames===0&&x.orderedState.byte1ca===0,'zero6fb survives real scan/countdown after full paused suffix');
 }
 {
  const x=fresh();x.matchGlobals.activeMask=1;x.teamRows103[0]!.meter=3000;x.status.getActualBorg(x.actor).burstArmFrames=1;
  refuses(()=>x.frame.runFrame(),'mandatory8005b678');
  check(x.status.getActualBorg(x.actor).burstArmFrames===1&&x.teamRows103[0]!.charged,'accepted threshold refuses before combination or countdown');
 }
 for(const fault of ['selector','alias','reentry','inactive'] as const){
  const x=fresh(),borg=x.status.getActualBorg(x.actor);let injected=false;
  if(fault==='inactive')borg.burstArmFrames=1;
  const native=Object.getOwnPropertyDescriptor;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   if(!injected&&o===borg&&k==='burstArmFrames'){
    injected=true;
    if(fault==='selector')Object.defineProperty(x.teamRows103[0]!,'byte1',{get(){throw Error('must not call selector accessor');},configurable:true});
    if(fault==='alias')Object.assign(x.sourceActor,{byte6fb:0});
    if(fault==='reentry')try{x.frame.runFrame();}catch{}
    if(fault==='inactive'){x.sourceActor.active0=0;x.stageState.lifecycle18=NaN;}
   }
   return native(o,k);
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),fault==='selector'?'byte1: own data':fault==='alias'?'competing':fault==='reentry'?'caught same-runtime reentry':'mandatory80087cf0');}finally{Object.getOwnPropertyDescriptor=native;}
  check(injected,'candidate actual6fb read reached');
  check(x.orderedState.byte1ca===0,'candidate fault preserves completed prior actor suffix');
  if(fault==='inactive')check(borg.burstArmFrames===0,'inactive candidate skips lifecycle but receives final countdown');
 }
 {
  const x=fresh(),native=Object.getOwnPropertyDescriptor;let dropped=false,selector=false,pointer=false;
  Object.getOwnPropertyDescriptor=((o:object,k:PropertyKey)=>{
   const p=native(o,k);
   if(x.orderedState.byte1ca===0){
    if(!dropped&&o===x.massPreparation.teamCounts&&k==='0'){dropped=true;x.massPreparation.teamCounts[0]=0;}
    if(dropped&&o===x.teamRows103[0]&&k==='byte1')selector=true;
    if(dropped&&o===x.massPreparation.teamPointers&&k==='0')pointer=true;
   }
   return p;
  }) as typeof native;
  try{refuses(()=>x.frame.runFrame(),'mandatory80087cf0');}finally{Object.getOwnPropertyDescriptor=native;}
  check(dropped&&selector&&!pointer,'fresh pre-first loop count skips pointer but still reads final selector');
 }
 {
  const x=fresh();x.status.getActualBorg(x.actor).burstArmFrames=1;
  refuses(()=>x.frame.runFrame(),'mandatory80087cf0');
  check(x.teamRows103[0]!.byte1!==1&&x.status.getActualBorg(x.actor).burstArmFrames===0,'one accepted with alternate selector returns then real countdown');
 }
 console.log(`[battle-team-candidates] PASS: ${cases} genuine source compositions`);
}
