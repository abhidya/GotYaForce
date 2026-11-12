/** Actual grounded neutral NEO/G BLACK X. Root target geometry and floor probes remain
 * host approximations; no console trajectory parity or new directional/air lane
 * is claimed. Runtime source observations do not replace real input admission. */
import {RomDriverBridge} from './bridge.js';
import {getGRedCrashState} from './gredCrash.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredFamilyCrashBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0629',distance=500){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const arms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,kind,status,arg)=>{arms.push([kind,status,arg]);arm?.(a,kind,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,arms,get frame(){return frame;},get crash(){return getGRedCrashState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
function admit(t:Fixture){
 t.input.p1.special=true;t.tick();t.input.p1.special=false;
 assert(t.owner.command?.exact&&t.owner.command.actionIndex===2&&t.owner.command.variantIndex===0,'actual neutral X admits action2/v0');
 assert(t.crash,'grounded family receives scoped source X state');
}
function until(t:Fixture,test:()=>boolean,label:string,limit=240){
 for(let i=0;i<limit&&!test();i++)t.tick();
 assert(test(),`${label}; phase=${t.actor.fbPhaseSlots[0]}, frame=${t.crash?.stream?.frame}`);
}
const familyIds=['pl0629','pl062a'] as const;
function noFloor(t:Fixture){
 // No-floor/raised-root fixture only after genuine grounded neutral X admission.
 t.owner.pos.y=t.actor.pos.y=10000;
 t.actor.physicsRuntime={clampToGround:(pos,velY)=>({y:pos.y,velY,grounded:false}),probeMotion:(_old,_pos,velY)=>({velY,grounded:false}),isSupported:()=>false};
}
function testStartAndCallback(){
 for(const id of familyIds){
  const t=setup(id);t.actor.poseAccum7c=123;t.actor.poseAccum7e=-456;t.actor.poseAccum80=789;admit(t);const s=t.crash!,stream=s.stream!;
  assert(t.owner.sourceAnimSample?.frame===36,'simulation publishes authored animation start36');
  assert(stream.frame===36&&stream.blendMode===1&&stream.blendTotal===(id==='pl0629'?17:7),'distinct source blend starts animation36');
  assert(JSON.stringify(t.arms)===JSON.stringify([[29,0,255]])&&s.contactFlags709===1,'source HIT29/status metadata and709set1 forwarded');
  assert(t.actor.yVel===0&&t.actor.gravityCoeff===0,'nonRED launch has no vertical impulse or forced gravity');
  assert(t.actor.poseAccum7c===0&&t.actor.poseAccum7e===0&&t.actor.poseAccum80===0,'source entry clears all three seeded pose accumulators');
  assert(t.animations.length===1&&t.animations[0]!.group===4&&t.animations[0]!.slot===3,'family stream plays g4s3 rather than RED g4s0');
  const beforeY=t.owner.pos.y,original=s.targetUid;
  t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;const selected=t.owner.lockTarget;
  assert(selected!==original&&s.targetUid===original,'real R changes selection without premature source recapture');
  for(let i=0;i<40&&Number(stream.blendMode)!==0;i++){assert(stream.frame===36,'mode1 blend holds authored start36');t.tick();}
  assert(Number(stream.blendMode)===0,'original blend completes');
  assert(t.owner.pos.y===beforeY,'zero launch remains vertically stationary during source blend');
  let callbackFrame:number|undefined;
  for(let i=0;i<30&&s.callbackRefreshCount===0;i++){const prior=stream.frame;t.tick();if(s.callbackRefreshCount)callbackFrame=prior;}
  assert(callbackFrame===40&&s.targetUid===selected&&s.noTargetLatch541===0,'callback40 refreshes current selected in-range target');
  assert(t.actor.fbPhaseSlots[0]===2&&s.acceptedContactCount===0,'authored40 starts phase2 without a HIT');
 }
}
function testLandingAndNegativeTimer(){
 for(const id of familyIds){
  const land=setup(id);admit(land);const ls=land.crash!;
  until(land,()=>!land.crash,'family ground landing returns');
  assert(ls.exitKind==='landing'&&ls.lastGroundProbe!==0&&land.owner.grounded,'accepted floor returns immediately');
  assert(land.actor.stateTimer===1+land.actor.dt,'landing694 seeded1+dt');
  const air=setup(id,3000);admit(air);noFloor(air);const s=air.crash!;
  const initialSerial=air.owner.sourceAnimSample!.serial;
  until(air,()=>Boolean(s.stream&&s.stream.waitCount>0),'family reaches mode8 hold');
  assert(air.owner.sourceAnimSample?.frame===63,'simulation sample follows hold entry63');
  for(let i=0;i<9;i++){air.tick();assert(air.owner.sourceAnimSample?.frame===63&&air.owner.sourceAnimSample.serial===initialSerial,'source sample freezes without new animation instance during hold');}
  until(air,()=>air.actor.fbPhaseSlots[0]===3,'authored negative contact enters phase3',300);
  assert(s.callbackRefreshCount===1&&s.noTargetLatch541!==0&&s.targetUid===null,'family callback40 reapplies range and keeps explicit fallback');
  assert(air.actor.handlerTimer===120,'phase3 seeds original120 timer');
  until(air,()=>Boolean(s.stream?.recovery),'family enters authored recovery');
  assert(Number(air.owner.sourceAnimSample?.frame)===0&&air.owner.sourceAnimSample?.serial!==initialSerial,'recovery publishes new serial and frame0');
  until(air,()=>Boolean(s.stream?.completed),'source animation finishes before air timer',200);
  assert(air.crash===s&&air.actor.handlerTimer>=0,'nonRED does not exit on animation completion');
  until(air,()=>Number(air.actor.handlerTimer)===0,'timer reaches exact zero',200);
  assert(air.crash===s,'zero timer still owns action');air.tick();
  assert(!air.crash&&Number(air.actor.handlerTimer)<0&&s.lastGroundProbe===0&&s.exitKind==='timer','only negative timer takes no-floor return');
  assert(!air.owner.sourceAnimSample,'timer exit clears source animation sampling');
 }
}
function followReceiver(t:Fixture,z:number,y=0){
 // Root+yaw shape approximation: place receiver after actual source motion,
 // before the real resolver, using the explicitly injected no-floor probe seam.
 const place=()=>{const yaw=t.actor.heading*Math.PI/32768;t.target.pos=v(t.actor.pos.x+Math.sin(yaw)*z,t.actor.pos.y+y,t.actor.pos.z+Math.cos(yaw)*z);t.target.vel=v(0,0,0);};
 const physics=t.actor.physicsRuntime!;const probe=physics.probeMotion;
 physics.probeMotion=(old,pos,vel)=>{place();return probe?.(old,pos,vel)??{velY:vel,grounded:false};};
}
function lateFixture(id:string){
 const t=setup(id,3000);admit(t);noFloor(t);const s=t.crash!;
 until(t,()=>Boolean(s.stream&&s.stream.frame>=52),'family late window is about to activate');
 assert(s.acceptedContactCount===0,'fixture has no earlier contacts');return t;
}
function testDistinctVolumesAndSharedHistory(){
 for(const id of familyIds)for(const [name,z,y,record] of [
  ['firstOnly',-40,0,41],['secondOnly',280,20,42],['overlap',145,10,41],['outside',400,0,0],['vertical',145,1000,0],
 ] as const){
  const t=lateFixture(id),s=t.crash!;followReceiver(t,z,y);const before=t.target.hp;t.tick();
  assert(s.stream?.frame===53,'test observes first authored active frame');
  if(record){assert(s.acceptedContactCount===1&&s.hitRecordIndex===record&&t.target.hp<before,`${id}/${name}: correct distinct sphere accepts once`);}
  else assert(s.acceptedContactCount===0&&t.target.hp===before,`${id}/${name}: source radius rejects`);
 }
 for(const id of familyIds){
  const t=lateFixture(id),s=t.crash!;followReceiver(t,145,10);
  const contacts:{update:number;frame:number;identity:number}[]=[];let previous=0,update=0;
  while(t.crash===s&&(s.stream?.frame??100)<=64&&update<40){
   // Immunity/survival override isolates identity cadence; damage still uses the
   // real collision/resolver. Natural immunity-free repeated hits are not claimed.
   t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';t.tick();
   const count=s.acceptedContactCount;
   assert(count-previous<=1,'overlapping pair never doubles same-pass damage');
   if(count>previous)contacts.push({update,frame:s.stream!.frame,identity:s.hitActivationSerial});
   previous=count;update++;
  }
  assert(JSON.stringify(contacts.map(c=>c.update))===JSON.stringify([0,1,7,8,14,15]),'independent7/0 counters yield shared renewal union, not plain7');
  assert(new Set(contacts.map(c=>c.identity)).size===contacts.length,'every union renewal gives one new actor-wide identity');
  assert(contacts[4]!.frame===63&&contacts[5]!.frame===63,'paired renewals continue through frozen animationframe63');
  assert(s.hitRenewalCount>=5,'source lifecycle renewals are observed independently of animation');
 }
}
function testInterruptionAndAirScope(){
 for(const id of familyIds){
  const t=setup(id);admit(t);const s=t.crash!;t.owner.hp=0;t.tick();assert(!t.crash&&!t.owner.sourceAnimSample,'death clears family source action and animation sample');
  for(let i=0;i<60;i++)t.tick();assert(s.callbackRefreshCount===0,'interrupted blend never executes later callback');
  const air=setup(id);air.input.p1.jump=true;air.tick();air.input.p1.jump=false;assert(!air.owner.grounded,'real jump establishes exact air-X context');
  air.input.p1.special=true;air.tick();assert(air.crash&&air.actor.variantIndex===4&&air.actor.fbCue===45,'exact family air X uses source variant4/cue45');
 }
}
export function runGredFamilyCrashBattleSelfTest(){testStartAndCallback();testLandingAndNegativeTimer();testDistinctVolumesAndSharedHistory();testInterruptionAndAirScope();console.log('[gredFamilyCrashBattle] PASS: scoped NEO/BLACK starts, callbacks, landing and negative timer');}
