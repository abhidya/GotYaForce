/** Actual jump then BLACK airborne B. Target/root-volume and floor placement
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
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gblackAirMeleeBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl062a',distance=100){
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
 assert(t.air&&t.actor.fbPhaseSlots[0]===1,'BLACK enters source airborne B phase1');
 assert(t.hitArms.some(a=>a.join(',')==='6,25,255'),'source forwards HIT6/status25/255 without claiming a defender status consumer');
 assert(t.animations.some(a=>a.group===3&&a.slot===21),'source plays original g3s21');
 assert(observed.before&&observed.cache&&observed.after,'observe original phase0 without replacing it');
 assert(observed.before.y>observed.cache.y,'real jump gives nonzero motion history');
 for(const axis of ['x','y','z'] as const){
  const expected=Math.fround(observed.before[axis]+Math.fround(Math.fround(observed.before[axis]-observed.cache[axis])*Math.fround(.95)));
  assert(observed.after[axis]===expected,'source phase0 carries own saved position, not enemy displacement');
 }
 assert(observed.speed===0&&observed.vy===0&&observed.gravity===0,'air B zeros launch velocity/gravity without an invented upward launch');
 assert(observed.timer===30,'source initial yaw-alignment timeout is30');
 assert(Number(t.actor.poseAccum7c)===0&&Number(t.actor.poseAccum7e)===0&&Number(t.actor.poseAccum80)===0,'source phase0 clears all three pose accumulators');
 assert(t.air.family==='black'&&t.air.stream?.family==='black','BLACK gets its own source profile and clock');
 assert(t.air.stream.endFrame===50&&t.air.stream.blendTotal===6,'original BLACK clip end50 and blend5+1');
 assert(t.air.flags6e8===2&&t.air.flags6e9===0&&t.air.contactFlags709===1,'original startup flags and709set1');
 checkSample(t);return t.air;
}
function testPhasesAndGates(){
 const t=setup(),s=admit(t),serial=checkSample(t),phases=new Set<number>([1]);
 const gates:number[]=[];let brakeCalls=0,held=false;
 const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const phase=a.fbPhaseSlots[0],before=s.stream!.frame,speed=a.hSpeed,vy=a.yVel,pos={...a.pos};root(a);
  if(phase===3){brakeCalls++;assert(a.fbPhaseSlots[0]===4,'BLACK brake0 still executes exactly one phase3 dispatch');assert(a.hSpeed===Math.fround(speed*Math.fround(.9))&&a.yVel===Math.fround(vy*Math.fround(.9)),'brake damps both velocity scalars');assert(a.pos.x!==pos.x||a.pos.y!==pos.y||a.pos.z!==pos.z,'zero brake integrates motion');}
  if(s.stream!.frame!==before){
   if(before===13){gates.push(13);assert(a.contactP0===1,'gate13 sets positive contact');}
   if(before===14){gates.push(14);assert(a.contactP0===0&&s.flags6e9===1,'gate14 resets contact and sets part flag1');}
   if(before===19){gates.push(19);assert(a.gravityCoeff===-1&&a.faceGate1d10===0,'gate19 restores gravity and disables aim');}
   if(before===23){gates.push(23);assert(s.flags6e9===2,'gate23 sets part flag2');}
   if(before===27){gates.push(27);assert(a.contactP0===-1&&s.flags6e8===3&&s.flags6e9===0&&s.contactFlags709===0,'gate27 negative contact and flag cleanup');}
  }
 };
 for(let i=0;i<200&&t.air;i++){
  const before=s.stream!.frame,blend=s.stream!.blendMode;t.tick();phases.add(t.actor.fbPhaseSlots[0]);
  if(t.air){assert(checkSample(t)===serial,'single source play retains animation serial');if(blend===1&&before===0&&s.stream!.frame===0)held=true;}
 }
 t.actor.rootAction=root;
 assert([1,2,3,4].every(p=>phases.has(p))&&brakeCalls===1,'actual jump/B traverses scoped five-phase engine');
 assert(held&&gates.join(',')==='13,14,19,23,27','source blend and every BLACK gate observed');
 assert(!t.air&&s.exitKind==='landing'&&t.owner.grounded&&!t.owner.sourceAnimSample,'normal BLACK trajectory lands after gate27');
 assert(t.actor.stateTimer===2,'source landing writes1+dt');
}
function testRangeAndTimeout(){
 const near=setup(),ns=admit(near);
 until(near,()=>near.actor.fbPhaseSlots[0]===2,'phase2 ready');
 // Geometry seam after genuine admission: distance350 becomes290 after speed60,
 // within BLACK300 but outside RED200, proving the family proximity selection.
 near.target.pos=v(near.owner.pos.x,near.owner.pos.y,near.owner.pos.z+350);near.target.vel=v(0,0,0);near.tick();
 assert(near.actor.fbPhaseSlots[0]===3&&near.actor.handlerTimer===0,'BLACK range300 ends pursuit after one60 step toward350 target');
 assert(ns.profile.engine.proximityRange===300,'profile exposes original300 proximity');
 const far=setup(),s=admit(far,v(0,10,3000));
 assert(s.noTargetLatch541===1&&s.targetUid===null,'out-of-range captured-root adjunct uses persistent fallback');
 let stalled=0,phase2Calls=0;const root=far.actor.rootAction!;
 far.actor.rootAction=a=>{const phase=a.fbPhaseSlots[0],frame=s.stream!.frame;root(a);if(phase===2){phase2Calls++;if(frame>=13&&s.stream!.frame===frame)stalled++;}};
 until(far,()=>far.actor.fbPhaseSlots[0]===4,'fallback pursues then brakes');far.actor.rootAction=root;
 assert(phase2Calls===20&&stalled>0,'pursuit timer20 advances while positiveP0 stops animation');
}
function testNoFloorAndInterruption(){
 const t=setup(),s=admit(t,v(0,10,3000));
 // Explicit no-floor seam after real admission isolates the source end branch.
 t.owner.pos.y=10000;t.actor.pos.y=10000;const physics=t.actor.physicsRuntime!;
 physics.probeMotion=(_old,_pos,vel)=>({velY:vel,grounded:false});physics.clampToGround=(pos,vel)=>({y:pos.y,velY:vel,grounded:false});
 until(t,()=>!t.air,'original end50 completes without landing');
 assert(s.exitKind==='stream-end'&&s.stream!.completed&&s.stream!.frame===50&&!t.owner.sourceAnimSample,'end50 returns airborne and clears sampling');
 const dead=setup(),ds=admit(dead);dead.owner.hp=0;dead.tick();
 assert(!dead.air&&!dead.owner.sourceAnimSample,'death clears BLACK source ownership');
 for(let i=0;i<80;i++)dead.tick();assert(ds.acceptedContactCount===0,'interrupted startup cannot later damage');
}
type Placement='capsule'|'sphere'|'overlap'|'vertical'|'outside';
function geometry(t:Fixture,placement:Placement){
 const physics=t.actor.physicsRuntime!,probe=physics.probeMotion;
 physics.probeMotion=(old,pos,vel)=>{
  const local=placement==='capsule'?v(0,0,240):placement==='sphere'?v(90,-40,50):placement==='overlap'?v(0,0,50):placement==='vertical'?v(0,1000,50):v(0,0,500);
  const yaw=t.actor.heading*Math.PI/32768,c=Math.cos(yaw),sn=Math.sin(yaw),scale=t.actor.modelScale;
  t.target.pos=v(pos.x+(c*local.x+sn*local.z)*scale,pos.y+local.y*scale,pos.z+(-sn*local.x+c*local.z)*scale);t.target.vel=v(0,0,0);
  return probe?.(old,pos,vel)??{velY:vel,grounded:false};
 };
 return ()=>{if(probe)physics.probeMotion=probe;else delete physics.probeMotion;};
}
function testSourceVolumesAndSharedIdentity(){
 for(const placement of ['capsule','sphere','overlap','vertical','outside'] as const){
  const t=setup(),s=admit(t),restore=geometry(t,placement),contacts:{frame:number;record:number|null;serial:number}[]=[];let retap=false;
  for(let i=0;i<200&&t.air;i++){
   // Labeled receiver survival/immunity reset isolates refresh0/shared-ID
   // dedup; all acceptances still pass through real input and damage resolver.
   t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';
   if(s.acceptedContactCount>0&&!retap){t.input.p1.attack=true;retap=true;}else t.input.p1.attack=false;
   const before=s.acceptedContactCount;t.tick();
   if(s.acceptedContactCount>before){assert(s.acceptedContactCount-before===1,'overlapping live records never multiply same-pass damage');assert(t.target.hp<t.target.maxHp,'real resolver applies HP damage');contacts.push({frame:s.stream!.frame,record:s.hitRecordIndex,serial:s.hitActivationSerial});}
  }
  restore();
  if(placement==='vertical'||placement==='outside'){assert(contacts.length===0,'3D/outside volumes reject receiver');continue;}
  if(placement==='sphere')assert(contacts.length===1&&contacts[0]!.frame===17&&contacts[0]!.record===19,'sphere-only geometry hits only original record19 at17');
  else {assert(contacts.length===2&&contacts[0]!.frame===15&&contacts[1]!.frame===17,'shared actor identity allows capsule contact again at second registration17');assert(contacts.every(c=>c.record===6),'capsule remains eligible when sphere activates');assert(contacts[0]!.serial!==contacts[1]!.serial,'second registration renews shared identity');}
  assert(t.animations.filter(a=>a.group===3&&a.slot===21).length===1,'actual hit+retap cannot continue aux0 BLACK stream');
 }
}
function testFamilyIsolation(){
 const neo=setup('pl0629');neo.input.p1.jump=true;neo.tick();neo.input.p1.jump=false;neo.input.p1.attack=true;neo.tick();
 assert(neo.owner.command?.actionIndex===1&&neo.owner.command.variantIndex===4&&neo.air?.family==='neo'&&neo.air.stream?.slot===33,'NEO air combo receives its own source profile, not BLACK');
 const ground=setup('pl062a',170);ground.input.p1.attack=true;ground.tick();
 assert(ground.actor.variantIndex===0&&!ground.air&&getNeoGredMeleeState(ground.actor)?.family==='black','BLACK grounded source chain remains independent');
}
export function runGblackAirMeleeBattleSelfTest(){testPhasesAndGates();testRangeAndTimeout();testNoFloorAndInterruption();testSourceVolumesAndSharedIdentity();testFamilyIsolation();console.log('[gblackAirMeleeBattle] PASS: real air B, BLACK profile/phases, source capsule/sphere waves and isolation');}
