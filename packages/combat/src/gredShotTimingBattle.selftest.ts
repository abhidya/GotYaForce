/** Actual grounded neutral B timing and repeat inputs. Source-clock assertions
 * are separate from host target/terrain and charge-entry approximations. */
import {getGRedShotState} from './gredShot.js';
import {getGRedChargeState} from './gredCharge.js';
import {getGBlackChargeState} from './gblackCharge.js';
import {RomDriverBridge} from './bridge.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredShotTimingBattle] ${s}`);}
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
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,familyEvents,get frame(){return frame;},get shot(){return getGRedShotState(actor);},};
}
type Fixture=ReturnType<typeof setup>;
const ids=['pl0615','pl0629','pl062a'] as const;
const rowFor=(id:string)=>id==='pl0615'?43:id==='pl0629'?101:102;
function until(t:Fixture,test:()=>boolean,label:string,limit=380){for(let i=0;i<limit&&!test();i++)t.tick();assert(test(),label);}
function fire(t:Fixture,held=false){
 const ammo=t.owner.ammo;t.input.p1.attack=true;t.tick();t.input.p1.attack=held;
 const c=t.owner.command;assert(c?.exact&&c.actionIndex===0&&c.variantIndex===0,'real far B admits unchanged action0/v0');
 until(t,()=>t.state.projectiles.some(p=>p.ownerUid===t.owner.uid),'source callback emits projectile',100);
 const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid)!;
 assert(p.gredRangedSource?.row===rowFor(t.owner.borgId),'correct c3be0 row receives dedicated source flight');
 assert(t.familyEvents.filter(e=>e[0]===0x800c3be0&&e[1]===rowFor(t.owner.borgId)).length===1,'actual source callback fires once');
 assert(t.owner.ammo===ammo-1&&t.owner.weaponCells![0]!.cur===ammo-1,'one normal shot debits one source cell only');
 assert(p.damageRecord?.hpDamage===20&&p.romShotKind===0,'original HIT0 supplies damage0 HP20');
 return p;
}

const count=(t:Fixture)=>t.familyEvents.filter(e=>e[0]===0x800c3be0).length;
function testTapAndHeld(){
 for(const id of ids)for(const held of [false,true]){
  const t=setup(id,5000),start=t.frame,ammo=t.owner.ammo;fire(t,held);
  assert(t.familyEvents[0]![2]!>start+4,'source shot is not legacy flat-schedule tick4');
  assert(t.actor.fbPhaseSlots[0]===2,'source fire enters repeat phase');
  for(let i=0;i<90;i++)t.tick();
  assert(count(t)===1&&t.owner.ammo===ammo-1,'tap or held-only B cannot synthesize fresh repeat edges');
 }
}
function testFreshRepeatAndExhaustion(){
 for(const id of ids){
  const t=setup(id,5000);fire(t);const first=t.familyEvents[0]![2]!,ammo=t.owner.ammo;
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  until(t,()=>count(t)===2,'fresh edge latched through family repeat timer',60);
  const gap=t.familyEvents[1]![2]!-first;
  assert(gap===(id==='pl0615'?14:id==='pl0629'?10:18),'source timer checks before decrement and restarts before next-phase fire');
  assert(t.owner.ammo===ammo-1,'repeat validates without debit then source fire debits exactly once');
  // Explicit resource exhaustion after real second shot, before a new repeat edge.
  t.owner.ammo=0;t.owner.weaponCells![0]!.cur=0;
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  for(let i=0;i<40;i++)t.tick();
  assert(count(t)===2&&t.owner.ammo===0,'failed repeat allocation produces no projectile or negative ammo');
  assert((t.actor.controlWord&3)===0,'failed repeat ammo releases source ownership');
 }
}
function testRetarget(){
 for(const id of ids){
  const t=setup(id,5000);fire(t);const old=t.owner.lockTarget;
  t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;
  assert(t.owner.lockTarget!==old,'actual R selects a different receiver');const selected=t.owner.lockTarget;
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  until(t,()=>count(t)===2,'retargeted fresh repeat fires',80);
  const p=t.state.projectiles.filter(p=>p.ownerUid===t.owner.uid&&p.gredRangedSource).at(-1);
  assert(p?.gredRangedSource?.targetUid===selected,'repeat refreshes capture to actual selected target');
 }
}

function testStartupSamplesAndEdges(){
 for(const id of ids){
  const t=setup(id,5000),ammo=t.owner.ammo;t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  const s=t.shot;assert(s?.stream&&t.owner.sourceAnimSample,'real admission owns source clock/sample');
  const serial=t.owner.sourceAnimSample.serial;
  assert(s.stream.stage==='startup'&&s.stream.frame===0&&s.stream.blendMode===6,'initial opcode0d holds source center frame0');
  assert(t.owner.ammo===ammo&&s.fireCount===0,'initial admission does not debit before source release');
  t.tick();t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  assert(s.phase===1&&s.latch745===0,'fresh B during phase1 cannot pre-latch a phase2 repeat');
  assert(t.owner.sourceAnimSample?.serial===serial&&t.owner.sourceAnimSample.frame===s.stream.frame,'blend sample stays on same source epoch');
  until(t,()=>s.fireCount===1,'source first release');
  assert(Number(s.stream.frame)===1&&String(s.stream.stage)==='repeat','startup ended wait falls into repeat positive P0 and signals release at frame1');
  const epochs=new Set([serial]);
  for(let i=0;i<100&&t.shot;i++){t.tick();if(t.shot){assert(t.owner.sourceAnimSample?.frame===s.stream!.frame,'each sample equals authoritative source frame');epochs.add(t.owner.sourceAnimSample.serial);}}
  assert(!t.shot&&count(t)===1&&epochs.size===2,'source falls through second clip then completes without phase1 repeat');
  assert(!t.owner.sourceAnimSample&&(t.owner.cooldowns['shot']??0)===0,'cleanup clears sample without invented20 attack lockout');
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  assert(getGRedShotState(t.actor)?.stream?.stage==='startup'&&t.actor.streamSlot===0,'next real fresh admission immediately resets source slot6ee to0');
 }
}
function testInitialCaptureAndDeath(){
 for(const id of ids){
  const t=setup(id,5000);t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  const s=t.shot!;const captured=s.targetUid;
  t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;
  assert(t.owner.lockTarget!==captured&&s.targetUid===captured,'initial source target stays captured across real R input');
  until(t,()=>s.fireCount===1,'captured initial shot');
  const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.gredRangedSource);
  assert(p?.gredRangedSource?.targetUid===captured,'initial projectile uses captured rather than newly selected receiver');
  t.owner.hp=0;t.tick();assert(!t.shot&&!t.owner.sourceAnimSample,'death cleans source actor clock/sample');
 }
}
function testGroundAdmissionPosture(){
 for(const id of ids){
  const t=setup(id,5000);
  // Explicit stale source-bit fixture: real host posture remains grounded.
  // Only fresh decoded grounded B admission may reconcile this stale bit.
  t.actor.controlWord|=0x40;
  t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  assert(t.owner.command?.exact&&t.owner.command.subtype===0&&t.shot,'real grounded B still selects scoped admission');
  assert((t.actor.controlWord&0x40)===0,'fresh grounded admission clears inconsistent prior airborne source bit');
  t.actor.controlWord|=0x40;t.tick();
  assert((t.actor.controlWord&0x40)!==0,'later source ticks do not continuously erase airborne source state');
 }
}
function testBufferedA(){
 for(const id of ids)for(const at of [2,10]){
  const t=setup(id,5000);t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  const s=t.shot!;
  for(let tick=2;tick<=at;tick++){t.input.p1.jump=tick===at;t.tick();}
  t.input.p1.jump=false;
  until(t,()=>s.fireCount===1,'A does not cancel initial source release');
  t.tick();
  if(at===2)assert(t.shot===s&&!s.completed,'A edge aged beyond16 updates cannot cancel repeat phase');
  else assert(!t.shot&&s.completed&&s.idleTransitionFrames===20,'recent A edge buffered into phase2 exits without an attack cooldown');
 }
}
function testEmptyAndCharge(){
 for(const id of ids){
  const empty=setup(id);empty.owner.ammo=0;empty.owner.weaponCells![0]!.cur=0;
  empty.input.p1.attack=true;empty.tick();empty.input.p1.attack=false;for(let i=0;i<80;i++)empty.tick();
  assert(count(empty)===0&&empty.owner.ammo===0,'actual empty B cannot create source shot');
  const t=setup(id,5000);t.input.p1.attack=true;
  until(t,()=>(t.owner.cooldowns['chargeFrames']??0)>=8,'host held bookkeeping banks charge',200);
  const ammo=t.owner.ammo;t.input.p1.attack=false;t.tick();
  assert(t.owner.command?.actionIndex===3&&!t.shot,'actual banked release leaves ordinary shot route for charge');
  assert(id==='pl062a'?Boolean(getGBlackChargeState(t.actor)):Boolean(getGRedChargeState(t.actor)),'banked release retains family-specific source charge handler');
  assert(t.owner.ammo===ammo,'charge handoff does not add a normal-shot ammo debit');
 }
}
export function runGredShotTimingBattleSelfTest(){testTapAndHeld();testFreshRepeatAndExhaustion();testRetarget();testStartupSamplesAndEdges();testInitialCaptureAndDeath();testGroundAdmissionPosture();testBufferedA();testEmptyAndCharge();console.log('[gredShotTimingBattle] PASS: actual source clock, tap/held/repeat, ammo, retarget and charge');}
