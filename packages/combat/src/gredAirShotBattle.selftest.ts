/** Actual jump then far B. Source actor/stream invariants are tested separately
 * from host lower-body locomotion, static attachment and target/terrain adapters. */
import {getGRedShotState} from './gredShot.js';
import {getGRedAirShotState} from './gredAirShot.js';
import {RomDriverBridge} from './bridge.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredAirShotBattle] ${s}`);}
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
 const familyEvents:number[][]=[];const family=driver.ctx.onFamilyProjectile;driver.ctx.onFamilyProjectile=(a,address,row)=>{familyEvents.push([address,row,frame]);family?.(a,address,row);};
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,k,status,arg)=>{hitArms.push([k,status,arg]);arm?.(a,k,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,familyEvents,get frame(){return frame;},get shot(){return getGRedAirShotState(actor);},get groundShot(){return getGRedShotState(actor);},};
}
type Fixture=ReturnType<typeof setup>;
const ids=['pl0615','pl0629','pl062a'] as const;
const rowFor=(id:string)=>id==='pl0615'?43:id==='pl0629'?101:102;
function until(t:Fixture,test:()=>boolean,label:string,limit=380){for(let i=0;i<limit&&!test();i++)t.tick();assert(test(),label);}

function jump(t:Fixture){t.input.p1.jump=true;t.tick();t.input.p1.jump=false;assert(!t.owner.grounded,'actual jump establishes airborne input context');}
function admit(t:Fixture){jump(t);t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
 const c=t.owner.command;assert(c?.exact&&c.actionIndex===0&&c.variantIndex===3,'real airborne far B decodes action0/v3');
 assert(c.recordAddress==='0x80365d98','actual neutral air direction uses original subtype4 direction0 row');
}
function testLowerLocomotion(){
 for(const id of ids){
  const control=setup(id),shot=setup(id);jump(control);admit(shot);control.tick();
  assert(shot.owner.pos.y===control.owner.pos.y&&shot.owner.vel.y===control.owner.vel.y&&shot.owner.vel.y>0,'upper-body admission preserves actual jump motion instead of freezing velocity');
  for(let i=0;i<4;i++){control.tick();shot.tick();assert(shot.owner.pos.y===control.owner.pos.y&&shot.owner.vel.y===control.owner.vel.y,'early source upper-body shot permits the same lower-body jump updates');}
 }
}
function testShotAndLanding(){
 for(const id of ids){
  const t=setup(id,1000),ammo=t.owner.ammo,hp=t.target.hp;admit(t);
  until(t,()=>t.familyEvents.some(e=>e[0]===0x800c3be0),'real air source releases projectile',120);
  const events=t.familyEvents.filter(e=>e[0]===0x800c3be0);assert(events.length===1&&events[0]![1]===rowFor(id),'family source shot callback, no duplicate');
  assert(t.owner.ammo===ammo-1,'actual air shot debits exactly one source cell');
  const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.gredRangedSource);assert(p?.gredRangedSource?.targetUid===t.target.uid,'air admission supplies source visibility/capture for target');
  until(t,()=>t.target.hp<hp,'actual air shot reaches receiver',120);
  until(t,()=>t.owner.grounded,'normal jump lands during or after upper-body action',120);
 }
}

function testRepeatAndLandingHandoff(){
 for(const id of ids){
  const t=setup(id,5000);admit(t);const s=t.shot;assert(s?.partMode,'source v3 owns upper body only');
  until(t,()=>s.fireCount===1,'first upper source shot');
  until(t,()=>t.owner.grounded,'actual lower jump lands');
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  until(t,()=>Boolean(t.groundShot),'landed fresh repeat hands off to grounded v0',80);
  assert(t.actor.variantIndex===0&&!t.shot,'landing redirect transfers source ownership, not a forced v4 remap');
  until(t,()=>t.familyEvents.filter(e=>e[0]===0x800c3be0).length===2,'grounded continuation fires second source shot',80);
 }
}
function testAirRepeatsAndSamples(){
 for(const id of ids){
  const t=setup(id,5000);jump(t);
  // Elevated-root fixture after actual jump keeps the host lower body airborne
  // long enough to isolate a repeat. This is not a source jump-height oracle.
  t.owner.pos.y=1000;t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  const s=t.shot;assert(s?.stream&&s.partMode,'genuine air input admits upper-only source state');
  assert(t.owner.sourceAnimSample?.frame===s.stream.frame,'upper source frame reaches visual sample');
  const serial=t.owner.sourceAnimSample.serial;
  until(t,()=>s.fireCount===1,'first source airborne shot');const first=t.frame;
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  until(t,()=>s.fireCount===2,'fresh edge repeats while still airborne',80);
  assert(t.frame-first===(id==='pl0615'?14:id==='pl0629'?10:18),'air source timer uses family-specific repeat cadence');
  assert(s.variant===3&&s.partMode&&!t.owner.grounded,'ordinary in-cone air repeat remains v3 upper-body');
  assert(t.owner.sourceAnimSample&&t.owner.sourceAnimSample.serial!==serial&&t.owner.sourceAnimSample.frame===s.stream!.frame,'repeat restarts source sample epoch');
  t.owner.hp=0;t.tick();assert(!t.shot&&!t.owner.sourceAnimSample,'death clears upper source ownership/sample');
 }
}
function testOutOfConeHandoff(){
 for(const id of ids){
  const t=setup(id,5000);admit(t);const s=t.shot;assert(s,'actual v3 source admission');
  // Captured target geometry is moved behind the owner to cross the original
  // inclusive yaw cone; no direct direction2 command is fabricated.
  t.target.pos=v(t.owner.pos.x,t.owner.pos.y,t.owner.pos.z-5000);
  until(t,()=>t.actor.variantIndex===4,'out-of-cone airborne source redirects to v4',10);
  assert(t.shot===s,'source redirect retains instance rather than remapping original input');
  until(t,()=>Boolean(s.lowerStream),'v4 starts independent lower stream',10);
  assert(!s.partMode&&s.lowerStream,'v4 temporarily owns lower and upper streams');
  until(t,()=>s.fireCount===1,'v4 source releases after aim/clock readiness',100);
  assert(s.partMode,'v4 fire returns lower movement ownership before shared upper continuation');
 }
}

function testHoldCaptureAndCleanup(){
 for(const id of ids){
  const held=setup(id,5000);jump(held);held.input.p1.attack=true;held.tick();
  const hs=held.shot;assert(hs,'held actual air B admits source');
  until(held,()=>!held.shot,'upper source completes even while B remains held',120);
  for(let i=0;i<10;i++)held.tick();
  assert(hs.fireCount===1&&held.familyEvents.filter(e=>e[0]===0x800c3be0).length===1,'held B cannot latch repeat or synthesize fresh admission after cleanup');
  const t=setup(id,5000);admit(t);const s=t.shot!;const captured=s.targetUid;
  t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;
  assert(t.owner.lockTarget!==captured&&s.targetUid===captured,'actual R changes selection without replacing initial source capture');
  until(t,()=>s.fireCount===1,'initial captured shot');
  const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.gredRangedSource);
  assert(p?.gredRangedSource?.targetUid===captured,'first source child uses retained captured receiver');
  until(t,()=>!t.shot,'ordinary upper source cleanup');
  assert(!t.owner.sourceAnimSample&&(t.owner.cooldowns['shot']??0)===0,'upper cleanup clears source sample without invented20 attack lockout');
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  assert(t.groundShot||t.shot,'fresh B immediately after cleanup is not swallowed by stale generic latch');
 }
}
export function runGredAirShotBattleSelfTest(){testLowerLocomotion();testShotAndLanding();testRepeatAndLandingHandoff();testAirRepeatsAndSamples();testOutOfConeHandoff();testHoldCaptureAndCleanup();console.log('[gredAirShotBattle] PASS: actual jump/B locomotion, source clocks/repeats, handoffs, shots and landing');}
