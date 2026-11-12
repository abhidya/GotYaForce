/** Actual jump then airborne G RED-family X. Root target geometry and floor probes remain
 * host approximations; no console trajectory or full air-admission parity
 * is claimed. Host air selection uses its existing grounded context; original
 * control80 admission semantics are not thereby proven. Runtime observations
 * do not replace real input admission. */
import {RomDriverBridge} from './bridge.js';
import {getGRedCrashState} from './gredCrash.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredAirCrashBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0615',distance=1000){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,get frame(){return frame;},get crash(){return getGRedCrashState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
function admitAir(t:Fixture){
 t.input.p1.jump=true;t.tick();t.input.p1.jump=false;
 assert(!t.owner.grounded,'real jump establishes airborne context');
 const observation:{before?:Vec3;cache?:Vec3;after?:Vec3;motion?:Vec3;launchY?:number;gravity?:number}={};
 const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const capture=a.actionIndex===2&&a.variantIndex===4&&a.fbPhaseSlots[0]===0;
  if(capture){observation.before={...a.pos};observation.cache={...a.targetCache5e8};}
  root(a);
  if(capture){observation.after={...a.pos};observation.motion={...a.motion};observation.launchY=a.yVel;observation.gravity=a.gravityCoeff;}
 };
 t.input.p1.special=true;t.tick();t.input.p1.special=false;t.actor.rootAction=root;
 const c=t.owner.command;
 assert(c?.exact&&c.type===2&&c.subtype===4&&c.actionIndex===2&&c.variantIndex===4&&c.recordAddress==='0x80365de0','actual air X selects exact original row45/3/2/4');
 assert(t.actor.fbCue===45&&t.actor.ubCue===45&&t.actor.fbState===61&&t.actor.ubState===0,'air admission dispatches cue45 and original state61/0');
 assert(t.actor.cmdButton===2&&t.actor.prevActionIndex===2&&t.actor.cmdSubtype===4,'button snapshot2 and subtype4 remain distinct');
 assert(t.crash&&t.actor.fbPhaseSlots[0]===1&&t.owner.state==='special','variant4 remains owned in source phase1 instead of instant recovery');
 assert(observation.before&&observation.cache&&observation.after&&observation.motion,'real phase0 was observed without replacing it');
 assert(observation.before.y>observation.cache.y&&observation.motion.y>0,'actual jump provides nonzero own-history carry');
 for(const axis of ['x','y','z'] as const){
  const expected=Math.fround(Math.fround(observation.before[axis]-observation.cache[axis])*Math.fround(.95));
  assert(observation.motion[axis]===expected,'real air X carries own saved5e8 displacement');
  assert(observation.after[axis]===Math.fround(observation.before[axis]+expected),'real phase0 adds f32 own-motion carry once');
 }
 assert(observation.launchY===(t.owner.borgId==='pl0615'?4:0)&&observation.gravity===0,'source launchRED4 versus NEO/BLACK0 with gravity0');
 return t.crash;
}
function until(t:Fixture,test:()=>boolean,label:string,limit=240){
 for(let i=0;i<limit&&!test();i++)t.tick();
 assert(test(),`${label}; phase=${t.actor.fbPhaseSlots[0]}, frame=${t.crash?.stream?.frame}`);
}
const ids=['pl0615','pl0629','pl062a'] as const;
function checkSample(t:Fixture){assert(t.owner.sourceAnimSample&&t.crash?.stream&&t.owner.sourceAnimSample.frame===t.crash.stream.frame,'air sample follows actual family source clock');}
function testAirMotionAndLanding(){
 for(const id of ids){
  const t=setup(id);const s=admitAir(t);checkSample(t);
  assert(s.stream?.frame===(id==='pl0615'?0:36),'air lane uses each family authored initial frame');
  const serial=t.owner.sourceAnimSample!.serial;
  for(let i=0;i<3;i++){t.tick();assert(t.crash===s&&t.actor.variantIndex===4,'air action cannot prematurely recover during initial source blend');checkSample(t);assert(t.owner.sourceAnimSample!.serial===serial,'same animation play retains serial');}
  let beforeCallback:number|undefined;
  for(let i=0;i<160&&s.callbackRefreshCount===0;i++){const frame=s.stream?.frame;t.tick();if(s.callbackRefreshCount)beforeCallback=frame;}
  assert(beforeCallback===40&&Number(t.actor.fbPhaseSlots[0])===2&&s.acceptedContactCount===0,'air miss still transitions on authored callback40');
  assert(s.targetUid===t.target.uid&&s.noTargetLatch541===0,'air callback captures actual selected in-range target');
  let descended=false;
  for(let i=0;i<260&&t.crash;i++){t.tick();if(t.owner.vel.y<0)descended=true;if(t.crash)checkSample(t);}
  assert(descended&&!t.crash&&s.exitKind==='landing'&&t.owner.grounded,'actual air source trajectory descends and lands');
  assert(!t.owner.sourceAnimSample,'landing clears airborne source sample');
 }
}
function testAirTargetRefreshAndDamage(){
 for(const id of ids){
  const t=setup(id);const s=admitAir(t),original=s.targetUid;
  t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;const selected=t.owner.lockTarget;
  assert(selected!==original&&s.targetUid===original,'real R selection remains pending until source callback');
  until(t,()=>s.callbackRefreshCount===1,'air callback refreshes target');assert(s.targetUid===selected,'air callback uses newly selected target');
  const hit=setup(id),hs=admitAir(hit),physics=hit.actor.physicsRuntime!,probe=physics.probeMotion;
  // Receiver geometry only: place its root after source motion and before the
  // real collision pass. Bone-origin parity is not claimed or synthesized.
  physics.probeMotion=(old,pos,vel)=>{
   const yaw=hit.actor.heading*Math.PI/32768;
   hit.target.pos=v(pos.x+Math.sin(yaw)*50,pos.y,pos.z+Math.cos(yaw)*50);hit.target.vel=v(0,0,0);
   return probe?.(old,pos,vel)??{velY:vel,grounded:false};
  };
  until(hit,()=>hs.acceptedContactCount>0,'air source HIT damages real receiver');
  assert(hit.target.hp<hit.target.maxHp,'actual resolver changes target HP');
  const frame=hs.stream!.frame;
  assert(id==='pl0615'?frame>=8&&frame<=16:frame>=53&&frame<=64,'air contact uses the audited family HIT window');
  if(probe)physics.probeMotion=probe;else delete physics.probeMotion;
 }
}
function testAirInterruptionAndGroundVariant(){
 for(const id of ids){
  const t=setup(id);const s=admitAir(t);t.owner.hp=0;t.tick();assert(!t.crash&&!t.owner.sourceAnimSample,'death interrupts air source ownership and sample');
  for(let i=0;i<80;i++)t.tick();assert(s.callbackRefreshCount===0,'dead air startup cannot later run callback');
  const g=setup(id);g.input.p1.special=true;g.tick();assert(g.crash&&g.actor.variantIndex===0&&g.actor.fbCue===44,'grounded neutral X remains distinct variant0/cue44');
 }
}
export function runGredAirCrashBattleSelfTest(){testAirMotionAndLanding();testAirTargetRefreshAndDamage();testAirInterruptionAndGroundVariant();console.log('[gredAirCrashBattle] PASS: real jump/X, exact air row, source carry/clocks, targeting, hits, landing and cleanup');}
