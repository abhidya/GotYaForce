/** Actual jump then NEO airborne B. Target/root-volume and floor placement
 * are explicit host geometry fixtures, not original animated-bone or admission
 * parity. No action, contact, or successful input is synthesized. */
import {RomDriverBridge} from './bridge.js';
import {getGRedAirMeleeState} from './gredAirMelee.js';
import {getNeoGredMeleeState} from './neoGredMelee.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import type {RomHelperScratch} from './rom/helpers.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[neoAirMeleeBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0629',distance=100){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;
 driver.ctx.onArmHit=(a,kind,status,arg)=>{hitArms.push([kind,status,arg]);arm?.(a,kind,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,get frame(){return frame;},get air(){return getGRedAirMeleeState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
function checkSample(t:Fixture){
 assert(t.air?.stream&&t.owner.sourceAnimSample,'air B publishes source animation sampling');
 assert(t.air.stream.frame===t.owner.sourceAnimSample.frame,'sample matches source animation, including stopped clocks');
 return t.owner.sourceAnimSample.serial;
}
function until(t:Fixture,predicate:()=>boolean,label:string,limit=240){
 for(let i=0;i<limit&&!predicate();i++){t.tick();if(t.air?.stream)checkSample(t);}
 assert(predicate(),`${label}; phase=${t.actor.fbPhaseSlots[0]}, frame=${t.air?.stream?.frame}`);
}
function admit(t:Fixture,entryTargetGeometry?:Vec3){
 t.input.p1.jump=true;t.tick();t.input.p1.jump=false;
 assert(!t.owner.grounded,'real jump establishes air context');
 t.actor.poseAccum7c=123;t.actor.poseAccum7e=-456;t.actor.poseAccum80=789;
 const observed:{before?:Vec3;cache?:Vec3;after?:Vec3;speed?:number;vy?:number;gravity?:number;timer?:number}={};
 const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const entry=a.actionIndex===1&&a.variantIndex===4&&a.fbPhaseSlots[0]===0;
  if(entry){
   // Optional geometry-only adjunct: the host selected its real close-B row
   // before this observer. Move the captured root out of range to isolate the
   // original range branch that host contextual command selection hides.
   const aim=a as typeof a & RomHelperScratch;
   if(entryTargetGeometry&&aim.lockTarget){Object.assign(aim.lockTarget,entryTargetGeometry);t.target.pos={...entryTargetGeometry};}
   observed.before={...a.pos};observed.cache={...a.targetCache5e8};
  }
  root(a);
  if(entry){observed.after={...a.pos};observed.speed=a.hSpeed;observed.vy=a.yVel;observed.gravity=a.gravityCoeff;observed.timer=a.handlerTimer;}
 };
 t.input.p1.attack=true;t.tick();t.input.p1.attack=false;t.actor.rootAction=root;
 const c=t.owner.command;
 assert(c?.exact&&c.type===1&&c.subtype===4&&c.actionIndex===1&&c.variantIndex===4&&c.recordAddress==='0x80365dc8','real air B uses exact decoded action1/v4 row');
 assert(t.actor.fbCue===45&&t.actor.ubCue===45&&t.actor.fbState===61&&t.actor.ubState===0,'air B dispatches exact cue45 state61/0');
 assert(t.actor.cmdButton===1&&t.actor.prevActionIndex===1&&t.actor.cmdSubtype===4,'button1 snapshot remains distinct from subtype4');
 assert(t.air&&t.actor.fbPhaseSlots[0]===1,'NEO enters source airborne B phase1');
 assert(t.hitArms.some(a=>a.join(',')==='24,25,255'),'source forwards HIT24/status25/255 without claiming a defender status consumer');
 assert(t.animations.some(a=>a.group===3&&a.slot===19),'source plays original g3s19');
 assert(observed.before&&observed.cache&&observed.after,'observe original phase0 without replacing it');
 assert(observed.before.y>observed.cache.y,'real jump gives nonzero motion history');
 for(const axis of ['x','y','z'] as const){
  const expected=Math.fround(observed.before[axis]+Math.fround(Math.fround(observed.before[axis]-observed.cache[axis])*Math.fround(.9)));
  assert(observed.after[axis]===expected,'source phase0 carries own saved position, not enemy displacement');
 }
 assert(observed.speed===0&&observed.vy===0&&observed.gravity===0,'air B zeros launch velocity/gravity without an invented upward launch');
 assert(observed.timer===30,'source initial yaw-alignment timeout is30');
 assert(Number(t.actor.poseAccum7c)===0&&Number(t.actor.poseAccum7e)===0&&Number(t.actor.poseAccum80)===0,'source phase0 clears all three pose accumulators');
 assert(t.air.family==='neo'&&t.air.stream?.family==='neo','NEO gets its own source profile and clock');
 assert(t.air.stream.endFrame===30&&t.air.stream.blendTotal===3,'original NEO clip end30 and blend2+1');
 assert(t.air.flags6e8===2&&t.air.flags6e9===0&&t.air.contactFlags709===1,'original startup flags and709set1');
 checkSample(t);return t.air;
}
function geometry(t:Fixture,outside=false){
 const physics=t.actor.physicsRuntime!,probe=physics.probeMotion;
 physics.probeMotion=(old,pos,vel)=>{const yaw=t.actor.heading*Math.PI/32768,range=outside?2000:100;
  t.target.pos=v(pos.x+Math.sin(yaw)*range,pos.y,pos.z+Math.cos(yaw)*range);t.target.vel=v(0,0,0);
  return probe?.(old,pos,vel)??{velY:vel,grounded:false};};
 return ()=>{if(probe)physics.probeMotion=probe;else delete physics.probeMotion;};
}
function retap(t:Fixture){t.input.p1.attack=false;t.tick();t.input.p1.attack=true;t.tick();t.input.p1.attack=false;}
function testActualChain(){
 const t=setup(),s=admit(t),restore=geometry(t),serials=[checkSample(t)],target=s.targetUid;
 let brakeCalls=0;const continuations:number[]=[];const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const phase=a.fbPhaseSlots[0],slot=s.stream!.slot,pos={...a.pos},timer=a.handlerTimer,fx=s.transitionFxCount,speed=a.hSpeed,vy=a.yVel;root(a);
  if(phase===3)brakeCalls++;
  if(s.stream!.slot!==slot){
   continuations.push(s.stream!.slot);
   assert(a.fbPhaseSlots[0]===4&&a.handlerTimer===timer&&s.transitionFxCount===fx,'continuation preserves phase/timer/transition FX');
   assert(a.pos.x===pos.x&&a.pos.y===pos.y&&a.pos.z===pos.z,'continuation returns before motion integration');
   assert(s.targetUid===target&&s.retap746===0&&s.alt745===0,'continuation retains captured target and clears both input/contact latches');
   assert(s.profile.engine.launchSpeed===40&&s.profile.engine.recoveryTimer===4&&s.profile.engine.driftScale===Math.fround(.9),'aliased stream never replaces NEO engine profile');
   if(s.stream!.slot===34)assert(Math.abs(Math.hypot(a.hSpeed,a.yVel)-40)<.001,'new dash24 uses NEO speed40 without damping that call');
   else assert(a.hSpeed===speed&&a.yVel===vy,'terminal dash0 does not overwrite velocity on start');
   assert(s.stream!.frame===0,'next stream resets its source animation frame');
  }
 };
 until(t,()=>s.acceptedContactCount===1,'opener has real accepted contact');
 assert(s.stream!.slot===33&&s.hitRecordIndex===39&&s.stream!.frame>=7&&s.stream!.frame<=10,'HIT24 uses original record39 window');
 retap(t);until(t,()=>s.stream!.slot===34,'hit plus fresh B starts34');serials.push(checkSample(t));
 until(t,()=>s.acceptedContactCount===2,'second source stream has real accepted contact');
 assert(Number(s.hitRecordIndex)===40&&s.stream!.frame>=7&&s.stream!.frame<=9,'HIT25 uses original record40 window');
 retap(t);until(t,()=>Number(s.stream!.slot)===35,'second hit plus fresh B starts terminal35');serials.push(checkSample(t));
 assert(s.stream!.endFrame===50&&s.stream!.blendTotal===6,'aliased final stream has BLACK clock while NEO engine persists');
 const finalHits:{frame:number;serial:number}[]=[];let finalRetap=false;
 for(let i=0;i<200&&t.air;i++){
  // Final-wave survival fixture separates source shared-identity dedup from
  // target invulnerability. Initial two chain contacts above need no reset.
  t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';
  const count=s.acceptedContactCount;
  if(finalHits.length&&!finalRetap){t.input.p1.attack=true;finalRetap=true;}else t.input.p1.attack=false;
  t.tick();
  if(s.acceptedContactCount>count){assert(s.acceptedContactCount-count===1,'terminal overlapping volumes admit one hit per pass');finalHits.push({frame:s.stream!.frame,serial:s.hitActivationSerial});}
 }
 t.actor.rootAction=root;restore();
 assert(brakeCalls===4,'NEO brake4 executes four initial phase3 calls');
 assert(continuations.join(',')==='34,35'&&new Set(serials).size===3,'two actual continuation plays have distinct animation instances');
 assert(finalHits.map(h=>h.frame).join(',')==='15,17'&&finalHits[0]!.serial!==finalHits[1]!.serial,'aliased final HIT6 retains shared waves15/17');
 assert(!t.air&&!t.owner.sourceAnimSample&&Number(s.stream!.slot)===35,'terminal aux0 exits with no fourth stream');
 assert(t.animations.filter(a=>a.group===3).map(a=>a.slot).join(',')==='19,20,21','actual chain plays only original three main animations');
 assert(t.hitArms.map(a=>a.join(',')).join(';')==='24,25,255;25,25,255;6,25,255','raw0a1819ff/0a1919ff/0a0619ff metadata forwards exactly, without claiming a defender status consumer');
}
function testNoChainNegatives(){
 for(const mode of ['held','stick','miss','invincible'] as const){
  const t=setup(),s=admit(t),restore=geometry(t,mode==='miss');
  if(mode==='held')t.input.p1.attack=true;
  let tapped=false;const serial=checkSample(t);let recoverySerial:number|undefined;
  for(let i=0;i<220&&t.air;i++){
   if(mode==='invincible')t.target.invincTimer=1000;
   if(mode==='stick'&&s.acceptedContactCount>0)t.input.p1.moveX=1;
   if((mode==='miss'||mode==='invincible')&&!tapped&&s.stream!.frame>=8){t.input.p1.attack=true;tapped=true;}else if(mode!=='held')t.input.p1.attack=false;
   t.tick();
   if(t.air){assert(s.stream!.slot===33,'missing contact or missing new B edge cannot continue');if(s.stream!.recovery){recoverySerial=checkSample(t);assert(recoverySerial!==serial,'uncontinued opener recovery gets a new animation instance');}}
  }
  restore();assert(!t.air&&s.stream!.slot===33,'negative case completes only opener');
  if(mode==='miss'||mode==='invincible')assert(s.acceptedContactCount===0,'miss/rejection does not supply accepted-contact latch');
  else assert(s.acceptedContactCount>0,'held/stick negative truly had accepted contact');
  // Natural ground contact can exit at the negative aux gate before recovery.
  if(recoverySerial!==undefined)assert(t.animations.some(a=>a.group===0&&a.slot===14),'source recovery uses originalg0s14');
 }
}
function testRecoveryAndCleanup(){
 const t=setup(),s=admit(t);
 // No-floor fixture after real admission exposes recovery instead of landing
 // at the negative contact gate. No command/contact/retap is injected.
 t.owner.pos.y=10000;t.actor.pos.y=10000;const physics=t.actor.physicsRuntime!;
 physics.probeMotion=(_old,_pos,vel)=>({velY:vel,grounded:false});physics.clampToGround=(pos,vel)=>({y:pos.y,velY:vel,grounded:false});
 const restore=geometry(t),serial=checkSample(t);until(t,()=>s.stream!.recovery,'uncontinued main enters authored recovery');
 assert(s.stream!.frame===0&&s.stream!.endFrame===1&&s.stream!.blendTotal===16&&checkSample(t)!==serial,'recovery resets frame and uses new end1/blend15 instance');
 assert(s.acceptedContactCount>0&&s.alt745!==0,'recovery negative genuinely retains an earlier accepted-contact latch');
 assert(t.actor.contactP0===0&&t.actor.contactP1===0&&s.contactFlags709===0,'recovery closes continuation window and clears709');
 retap(t);until(t,()=>!t.air,'terminal elapsed15 completes recovery');restore();
 assert(s.stream!.slot===33&&s.stream!.completed&&s.exitKind==='stream-end'&&!t.owner.sourceAnimSample,'late retap cannot escape recovery');
 const dead=setup(),ds=admit(dead);dead.owner.hp=0;dead.tick();assert(!dead.air&&!dead.owner.sourceAnimSample,'death clears source state/sample');for(let i=0;i<100;i++)dead.tick();assert(ds.acceptedContactCount===0,'dead source cannot later hit');
 const ground=setup('pl0629',170);ground.input.p1.attack=true;ground.tick();assert(!ground.air&&getNeoGredMeleeState(ground.actor)?.family==='neo','grounded NEO chain retains separate source engine');
}
export function runNeoAirMeleeBattleSelfTest(){testActualChain();testNoChainNegatives();testRecoveryAndCleanup();console.log('[neoAirMeleeBattle] PASS: actual accepted-hit/retap chain, NEO profile, terminal waves, negatives and cleanup');}
