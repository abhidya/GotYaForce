/** Actual jump then RED airborne B. Target/root-volume and floor placement
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
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredAirMeleeBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0615',distance=100){
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
 assert(t.air&&t.actor.fbPhaseSlots[0]===1,'RED enters source airborne B phase1');
 assert(t.hitArms.some(a=>a.join(',')==='18,25,255'),'source forwards HIT18/status25/255 without claiming a defender status consumer');
 assert(t.animations.some(a=>a.group===3&&a.slot===22),'source plays original g3s22');
 assert(observed.before&&observed.cache&&observed.after,'observe original phase0 without replacing it');
 assert(observed.before.y>observed.cache.y,'real jump gives nonzero motion history');
 for(const axis of ['x','y','z'] as const){
  const expected=Math.fround(observed.before[axis]+Math.fround(Math.fround(observed.before[axis]-observed.cache[axis])*Math.fround(.95)));
  assert(observed.after[axis]===expected,'source phase0 carries own saved position, not enemy displacement');
 }
 assert(observed.speed===0&&observed.vy===0&&observed.gravity===0,'air B zeros launch velocity/gravity without an invented upward launch');
 assert(observed.timer===30,'source initial yaw-alignment timeout is30');
 assert(Number(t.actor.poseAccum7c)===0&&Number(t.actor.poseAccum7e)===0&&Number(t.actor.poseAccum80)===0,'source phase0 clears all three pose accumulators');
 checkSample(t);return t.air;
}
function testSourcePhasesAndLanding(){
 const t=setup(),s=admit(t),serial=checkSample(t);
 const phases=new Set<number>([1]);let groundedBeforeExit=false;
 const frameSnapshots:{phase:number;before:number;after:number;blend:number}[]=[];
 for(let i=0;i<240&&t.air;i++){
  const phase=t.actor.fbPhaseSlots[0],before=s.stream?.frame,blend=s.stream?.blendMode;
  t.tick();phases.add(t.actor.fbPhaseSlots[0]);
  if(t.air){
   assert(checkSample(t)===serial,'single source animation never silently restarts');
   if(before!==undefined&&blend!==undefined)frameSnapshots.push({phase,before,after:s.stream!.frame,blend});
   if(t.owner.grounded){groundedBeforeExit=true;assert(!s.stream!.completed,'landing before negative contact does not end unfinished stream');}
  }
 }
 assert([1,2,3,4].every(p=>phases.has(p)),'actual input traverses all four post-entry source phases');
 assert(!t.air&&s.exitKind==='stream-end'&&s.stream!.completed,'natural close-target trajectory completes stream after gate15 relaunch');
 assert(groundedBeforeExit,'floor contact before source negative-P0 gate retains action');
 assert(!t.owner.sourceAnimSample,'source return clears animation ownership');
 assert(frameSnapshots.some(x=>x.blend===1&&x.before===0&&x.after===0),'initial source mode1 blend holds frame0');
 assert(frameSnapshots.some(x=>x.phase===4&&x.after>x.before),'phase4 advances original animation clock');
 assert(s.stream!.frame>=26,'natural source action passes authored negative contact gate26');
 until(t,()=>t.owner.grounded,'natural trajectory eventually lands after source return');
}
function testAcceptedLandingGate(){
 const t=setup(),s=admit(t),physics=t.actor.physicsRuntime!,probe=physics.probeMotion;
 // Explicit accepted-floor probe fixture, after genuine admission. Natural
 // target-height geometry can relaunch upward at gate15; this isolates the
 // source landing decision rather than claiming a console trajectory.
 physics.probeMotion=(old,pos,vel)=>t.actor.fbPhaseSlots[0]===4?{y:0,velY:0,grounded:true}:probe?.(old,pos,vel)??{velY:vel,grounded:false};
 let retained=false;
 for(let i=0;i<160&&t.air;i++){t.tick();if(t.air&&t.owner.grounded&&t.actor.contactP0>=0)retained=true;}
 assert(retained&&!t.air&&s.exitKind==='landing'&&s.stream!.frame===27,'accepted landing waits for pre-advance gate26 negative contact');
 assert(t.actor.stateTimer===2&&!t.owner.sourceAnimSample,'landing sets1+dt timer and clears sample');
 if(probe)physics.probeMotion=probe;else delete physics.probeMotion;
}
function testPursuitStallAndBrake(){
 const t=setup(),s=admit(t,v(0,10,3000));
 let stalled=0,brakeCalls=0,sawLaunchReset=false,sawGravityRestore=false;
 const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const phase=a.fbPhaseSlots[0],frame=s.stream!.frame,blend=s.stream!.blendMode;
  const speed=a.hSpeed,vy=a.yVel,pos={...a.pos};
  root(a);
  if(phase===2&&blend===0&&s.stream!.frame===frame&&frame>=10)stalled++;
  if(phase===3){
   brakeCalls++;
   assert(a.fbPhaseSlots[0]===4,'zero brake timer still executes one phase3 call');
   assert(a.hSpeed===Math.fround(speed*Math.fround(.9))&&a.yVel===Math.fround(vy*Math.fround(.9)),'phase3 damps both velocity scalars once');
   assert(a.pos.x!==pos.x||a.pos.y!==pos.y||a.pos.z!==pos.z,'zero-duration brake still integrates motion');
  }
  if(phase===4&&frame===15){
   sawLaunchReset=true;
   assert(Math.abs(Math.hypot(a.hSpeed,a.yVel)-54)<.001,'dash24 gate resets source chase speed60 then applies .9 damping');
  }
  if(phase===4&&frame===20){sawGravityRestore=true;assert(a.gravityCoeff===-1,'negative dash restores descriptor gravity at gate20');}
 };
 until(t,()=>!t.air,'fallback action finishes');t.actor.rootAction=root;
 assert(stalled>0,'positive contact gate stops phase2 animation while pursuit timer continues');
 assert(brakeCalls===1&&sawLaunchReset&&sawGravityRestore,'actual route covers brake and both dash gates');
}
function testAirReturnWithoutFloor(){
 const t=setup(),s=admit(t,v(0,10,3000));
 // Explicit no-floor seam after genuine jump/B admission; raised root avoids
 // unrelated host killplane while observing the source completion branch.
 t.owner.pos.y=10000;t.actor.pos.y=10000;
 const physics=t.actor.physicsRuntime!;
 physics.probeMotion=(_old,_pos,vel)=>({velY:vel,grounded:false});
 physics.clampToGround=(pos,vel)=>({y:pos.y,velY:vel,grounded:false});
 until(t,()=>!t.air,'no-floor source stream completion');
 assert(s.exitKind==='stream-end'&&s.stream!.completed&&!t.owner.sourceAnimSample,'without accepted landing, original animation completion returns airborne');
}
function testTargetCaptureAndFallback(){
 const t=setup(),s=admit(t),original=s.targetUid;
 assert(original===t.target.uid&&s.noTargetLatch541===0,'in-range target captured at source admission');
 t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;
 assert(t.owner.lockTarget!==original&&s.targetUid===original,'changing user lock does not replace airborne melee captured target');
 const far=setup(),fs=admit(far,v(0,10,3000));
 assert(fs.noTargetLatch541===1&&fs.targetUid===null,'outside type1 range1200 uses persistent fallback');
 far.target.pos=v(0,far.owner.pos.y,100);far.tick();
 assert(fs.noTargetLatch541===1&&fs.targetUid===null,'later entering range does not clear no-target latch');
}
function testRealHitWindows(){
 for(const window of ['early','late'] as const){
  const t=setup(),s=admit(t),physics=t.actor.physicsRuntime!,probe=physics.probeMotion;
  // Geometry-only receiver placement follows source movement. Original bone18
  // and bone15 centers are approximated by the host root minus30Y.
  physics.probeMotion=(old,pos,vel)=>{
   const frame=s.stream?.frame??0;
   t.target.pos=frame>=(window==='early'?15:19)?v(pos.x,pos.y-30,pos.z):v(15000,10,15000);
   t.target.vel=v(0,0,0);
   return probe?.(old,pos,vel)??{velY:vel,grounded:false};
  };
  until(t,()=>s.acceptedContactCount>0,`${window} source volume accepts real receiver`);
  const frame=s.stream!.frame;
  assert(window==='early'?frame>=15&&frame<=16:frame>=19&&frame<=21,'accepted contact lies within original source window');
  assert(t.target.hp<t.target.maxHp&&s.hitRecordIndex===(window==='early'?26:27),'real damage uses correct original HIT18 record');
  if(probe)physics.probeMotion=probe;else delete physics.probeMotion;
 }
 const vertical=setup(),vs=admit(vertical),physics=vertical.actor.physicsRuntime!,probe=physics.probeMotion;
 physics.probeMotion=(old,pos,vel)=>{vertical.target.pos=v(pos.x,pos.y+1000,pos.z);vertical.target.vel=v(0,0,0);return probe?.(old,pos,vel)??{velY:vel,grounded:false};};
 until(vertical,()=>!vertical.air,'vertical rejection reaches actual action completion');
 assert(vs.acceptedContactCount===0&&vertical.target.hp===vertical.target.maxHp,'3D volumes reject vertically distant target');
 if(probe)physics.probeMotion=probe;else delete physics.probeMotion;
}
function testWaveDedupAndNoContinuation(){
 const t=setup(),s=admit(t),physics=t.actor.physicsRuntime!,probe=physics.probeMotion;
 physics.probeMotion=(old,pos,vel)=>{t.target.pos=v(pos.x,pos.y-30,pos.z);t.target.vel=v(0,0,0);return probe?.(old,pos,vel)??{velY:vel,grounded:false};};
 const contacts:{frame:number;record:number|null;serial:number}[]=[];let retapped=false;
 for(let i=0;i<240&&t.air;i++){
  // Survival/immunity fixture only: every resolver contact still uses real
  // source registration and geometry. This exposes refresh0 dedup independently
  // of host invulnerability or defender hitstun suppressing a second contact.
  t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';
  if(s.acceptedContactCount>0&&!retapped){t.input.p1.attack=true;retapped=true;}else t.input.p1.attack=false;
  const before=s.acceptedContactCount;t.tick();
  if(s.acceptedContactCount>before){assert(s.acceptedContactCount-before===1,'one resolver acceptance per active source pass');contacts.push({frame:s.stream!.frame,record:s.hitRecordIndex,serial:s.hitActivationSerial});}
 }
 assert(contacts.length===2&&contacts[0]!.record===26&&contacts[1]!.record===27,'each refresh0 activation accepts receiver only once');
 assert(contacts[0]!.serial!==contacts[1]!.serial,'two disjoint source windows have distinct activation identities');
 assert(retapped&&t.animations.filter(a=>a.group===3&&a.slot===22).length===1,'real hit plus fresh B edge cannot chain auxiliary0 into another source stream');
 if(probe)physics.probeMotion=probe;else delete physics.probeMotion;
}
function testInterruptionAndIsolation(){
 const t=setup(),s=admit(t);t.owner.hp=0;t.tick();
 assert(!t.air&&!t.owner.sourceAnimSample,'death clears airborne B source state/sample');
 const count=s.acceptedContactCount;for(let i=0;i<50;i++)t.tick();assert(s.acceptedContactCount===count,'interrupted stream cannot later collide');
 for(const id of ['pl0629','pl062a']){
  const n=setup(id);n.input.p1.jump=true;n.tick();n.input.p1.jump=false;n.input.p1.attack=true;n.tick();
  assert(n.owner.command?.actionIndex===1&&n.owner.command.variantIndex===4,'neighbor retains actual air-B command');
  assert(n.air?.family===(id==='pl062a'?'black':'neo'),'neighbors receive their own airborne profiles, never RED');
 }
 const ground=setup('pl0615',170);ground.input.p1.attack=true;ground.tick();
 assert(ground.actor.variantIndex===0&&!ground.air&&getNeoGredMeleeState(ground.actor)?.family==='red','ground neutral B retains separate source chain');
}
export function runGredAirMeleeBattleSelfTest(){testSourcePhasesAndLanding();testAcceptedLandingGate();testPursuitStallAndBrake();testAirReturnWithoutFloor();testTargetCaptureAndFallback();testRealHitWindows();testWaveDedupAndNoContinuation();testInterruptionAndIsolation();console.log('[gredAirMeleeBattle] PASS: actual air B source entry/phases, target, HIT windows, landing and isolation');}
