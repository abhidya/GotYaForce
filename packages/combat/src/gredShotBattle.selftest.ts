/** Actual ordinary B inputs for scoped source c3be0 rows43/101/102.
 * Root/joint transforms, target geometry and stage collision are host adapters;
 * source projectile state is observed rather than synthesized. */
import {RomDriverBridge} from './bridge.js';
import {spawnTimeBomberMine} from './timeBomberMineAdapter.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredShotBattle] ${s}`);}
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
 const familyEvents:number[][]=[];const family=driver.ctx.onFamilyProjectile;driver.ctx.onFamilyProjectile=(a,address,row)=>{familyEvents.push([address,row]);family?.(a,address,row);};
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,k,status,arg)=>{hitArms.push([k,status,arg]);arm?.(a,k,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,familyEvents,get frame(){return frame;},};
}
type Fixture=ReturnType<typeof setup>;
const ids=['pl0615','pl0629','pl062a'] as const;
const rowFor=(id:string)=>id==='pl0615'?43:id==='pl0629'?101:102;
function until(t:Fixture,test:()=>boolean,label:string,limit=380){for(let i=0;i<limit&&!test();i++)t.tick();assert(test(),label);}
function fire(t:Fixture){
 const ammo=t.owner.ammo;t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
 const c=t.owner.command;assert(c?.exact&&c.actionIndex===0&&c.variantIndex===0,'real far B admits unchanged action0/v0');
 until(t,()=>t.state.projectiles.some(p=>p.ownerUid===t.owner.uid),'unchanged actor source callback emits projectile',40);
 const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid)!;
 assert(p.gredRangedSource?.row===rowFor(t.owner.borgId),'correct c3be0 row receives dedicated source flight');
 assert(t.familyEvents.filter(e=>e[0]===0x800c3be0&&e[1]===rowFor(t.owner.borgId)).length===1,'actual source callback fires once');
 assert(t.owner.ammo===ammo-1&&t.owner.weaponCells![0]!.cur===ammo-1,'one normal shot debits one source cell only');
 assert(p.damageRecord?.hpDamage===20&&p.romShotKind===0,'original HIT0 supplies damage0 HP20');
 return p;
}
function testAdmissionVisibility(){
 for(const id of ids){
  const t=setup(id),bit=t.actor.visibilityBit,otherBit=0x80;
  // Explicit mask fixture observes the real B-admission writer, not init-guard bypass.
  t.target.targetVisibilityMask5e6=otherBit;
  t.alternate.targetVisibilityMask5e6=otherBit|bit;
  assert((t.target.targetVisibilityMask5e6&bit)===0,'selected target begins without owner visibility');
  const p=fire(t);
  assert(t.target.targetVisibilityMask5e6===(otherBit|bit),'real admission adds only owner bit to captured target');
  assert(t.alternate.targetVisibilityMask5e6===otherBit,'real admission removes stale owner bit while preserving another owner');
  assert(p.gredRangedSource!.targetUid===t.target.uid,'source init guard accepts visibility supplied by real admission');
 }
 for(const id of ['pl0101','pl0104']){
  const t=setup(id),mask=0x80|t.actor.visibilityBit;
  t.alternate.targetVisibilityMask5e6=mask;
  t.input.p1.attack=true;t.tick();
  assert(t.alternate.targetVisibilityMask5e6===mask,'other-family admission does not run scoped visibility writer');
 }
}
function testReachAndIdentity(){
 for(const id of ids)for(const distance of [500,1000,2000]){
  const t=setup(id,distance),hp=t.target.hp,p=fire(t);
  until(t,()=>t.target.hp<hp,'source normal shot reaches real ranged receiver',100);
  assert(p.gredRangedSource!.hitUids.includes(t.target.uid)&&p.gredRangedSource!.contactPending,'real accepted hit is recorded for next child update');
  t.tick();assert(p.gredRangedSource!.flight.phase==='contact-tail'&&!p.gredRangedSource!.flight.hitActive,'following child update disables HIT and starts contact tail');
  const tail=p.gredRangedSource!.flight,pos={...tail.pos},length=tail.length,speed=tail.speed;t.tick();
  assert(JSON.stringify(p.gredRangedSource!.flight.pos)===JSON.stringify(pos)&&p.gredRangedSource!.flight.length===Math.fround(length-speed),'contact tail is stationary and retracts by current speed');
  assert(t.state.projectiles.filter(q=>q.ownerUid===t.owner.uid).every(q=>q.gredRangedSource),'no generic duplicate shot or invented impact child');
  for(let i=0;i<80;i++)t.tick();assert(!t.state.projectiles.includes(p),'source contact tail retires');
 }
}
function testVisualTrailIsNotAttack(){
 for(const id of ids){
  const t=setup(id,5000),p=fire(t);for(let i=0;i<10;i++)t.tick();
  assert(t.state.projectiles.includes(p),'source projectile survives far beyond old three-pass floor failure');
  const n=Math.hypot(p.vel.x,p.vel.y,p.vel.z);assert(n>0,'source flight has forward direction');
  // Explicit receiver placement behind current head, inside the long visual
  // trail but outside the next head sweep. Visual length is not attack reach.
  t.alternate.pos=v(p.pos.x-p.vel.x/n*200,p.pos.y-p.vel.y/n*200,p.pos.z-p.vel.z/n*200);t.alternate.vel=v(0,0,0);
  const hp=t.alternate.hp;t.tick();
  assert(t.alternate.hp===hp&&!p.gredRangedSource!.hitUids.includes(t.alternate.uid),'visual trail cannot damage a receiver behind projectile head');
 }
}
function testOwnerEndAndInvalidation(){
 for(const mode of ['death','form'] as const){
  const t=setup('pl0615',5000),p=fire(t);until(t,()=>t.owner.state==='idle','source actor reaches ordinary completion',100);
  assert(t.owner.state==='idle'&&t.state.projectiles.includes(p),'ordinary actor action end does not kill independent source projectile');
  if(mode==='death')t.owner.hp=0;
  else t.owner.combatFormId='fixture-replacement-form'; // Explicit metadata invalidation.
  t.tick();const hp=t.target.hp;
  for(let i=0;i<10;i++)t.tick();
  assert(!t.state.projectiles.includes(p)&&t.target.hp===hp,'invalidated owner suppresses further projectile collision and frees source child');
 }
 const empty=setup();empty.owner.ammo=0;empty.owner.weaponCells![0]!.cur=0;empty.input.p1.attack=true;empty.tick();empty.input.p1.attack=false;
 for(let i=0;i<10;i++)empty.tick();assert(!empty.familyEvents.some(e=>e[0]===0x800c3be0)&&!empty.state.projectiles.some(p=>p.ownerUid===empty.owner.uid),'empty source cell suppresses ordinary shot allocation');
}
function testFlightInitializationAndAcceleration(){
 for(const id of ids){
  const t=setup(id,5000),p=fire(t),s=p.gredRangedSource!,f=s.flight;
  assert(f.phase==='active'&&f.life===300&&f.speed===80,'first projectile pass initializes original life300/speed80 without active aging');
  assert(Math.abs(Math.hypot(f.pos.x-f.origin.x,f.pos.y-f.origin.y,f.pos.z-f.origin.z)-1)<.0001,'initial tip is exactly one normalized unit from source attachment');
  const collision=Math.fround(Math.fround(40/36.959999084472656)*t.actor.modelScale);
  assert(f.collisionScale===collision&&Math.abs(p.hitRadius-20*collision)<.0001,'original width normalization controls collision independently of trail');
  for(let i=0;i<20;i++){
   const before={...s.flight.pos},speed=s.flight.speed,life=s.flight.life;t.tick();
   const now=s.flight;assert(now.phase==='active','unobstructed source shot remains active');
   assert(Math.abs(Math.hypot(now.pos.x-before.x,now.pos.y-before.y,now.pos.z-before.z)-speed)<.001,'active update moves using current speed without generic gravity');
   assert(now.speed===Math.min(160,speed+.5)&&now.life===life-1,'acceleration is applied after motion and life decrements once');
  }
  assert(s.flight.length===(id==='pl0629'?500:1000),'family-specific visual maximum length is preserved');
  assert(s.flight.collisionScale===collision&&Math.abs(p.hitRadius-20*collision)<.0001,'visual growth never inflates HIT sphere');
 }
}
function testExpiryTailAdjunct(){
 const t=setup('pl0615',5000),p=fire(t),s=p.gredRangedSource!;
 for(let i=0;i<5;i++)t.tick();
 // Synthetic near-expiry counter only. Real source admission/flight above is
 // unchanged; this isolates the adapter's lifetime-retirement branch.
 s.flight.life=1;t.tick();
 assert(s.flight.phase==='expire-tail'&&!s.flight.hitActive&&s.flight.reason==='lifetime','lifetime expiry disables HIT before moving fade tail');
 const before={...s.flight.pos},width=s.flight.widthScale;t.tick();
 assert(s.flight.widthScale===Math.fround(width*Math.fround(.9)),'expiry tail shrinks width by source.9');
 assert(s.flight.pos.x!==before.x||s.flight.pos.y!==before.y||s.flight.pos.z!==before.z,'expiry tail keeps moving unlike stationary contact tail');
 for(let i=0;i<100;i++)t.tick();assert(!t.state.projectiles.includes(p),'expiry tail eventually frees source child');
}

function testMineReception(){
 for(const id of ids){
  const t=setup(id,5000),p=fire(t),f=p.gredRangedSource!.flight;
  assert(t.alternate.romDriver instanceof RomDriverBridge,'mine fixture owner has real actor');
  // Actual Time Bomber constructor plus explicit active-state/predicted-head
  // geometry fixture. No mine B cell was consumed and no refund is claimed.
  const mine=spawnTimeBomberMine(t.alternate,t.alternate.romDriver.actor),m=mine.timeBomberSource!;
  assert(m.kind==='mine','real constructor supplies mine lifecycle');
  const pos=v(Math.fround(f.pos.x+f.velocity.x),Math.fround(f.pos.y+f.velocity.y),Math.fround(f.pos.z+f.velocity.z));
  Object.assign(m,{phase:'active',motion:'drift',pos:{...pos},center:{...pos},direction:v(0,0,0),speed:5,life:100,bobPhase:0,floorTarget:0,resourceOwed:false});
  mine.pos={...pos};t.state.projectiles.push(mine);t.tick();
  const hit=mine.timeBomberSource!;assert(hit.kind==='mine'&&hit.phase==='active'&&hit.durability===0&&hit.receivedAttackUids.includes(p.uid),'normal source shot destroys HP1 mine with its own identity');
  assert(p.gredRangedSource!.hitUids.includes(mine.uid)&&p.gredRangedSource!.contactPending,'mine acceptance records source contact for deferred retirement');
  assert(!t.state.projectiles.some(q=>q.timeBomberSource?.kind==='explosion'),'collision does not eagerly run mine explosion update');
  t.tick();assert(mine.timeBomberSource?.kind==='mine'&&mine.timeBomberSource.phase==='retiring'&&p.gredRangedSource!.flight.phase==='contact-tail','next child pass retires both registered attacks through separate lifecycles');
 }
}
function testOtherFamilyScope(){
 for(const id of ['pl0101','pl0104']){
  const t=setup(id,2000);t.input.p1.attack=true;t.tick();t.input.p1.attack=false;
  let sawShot=false;
  for(let i=0;i<60;i++){sawShot ||= t.state.projectiles.some(p=>p.ownerUid===t.owner.uid);assert(!t.state.projectiles.some(p=>p.ownerUid===t.owner.uid&&p.gredRangedSource),'other family normal B cannot acquire scoped G RED flight');t.tick();}
  assert(sawShot,'scope negative exercised a real other-family shot');
 }
}
export function runGredShotBattleSelfTest(){testAdmissionVisibility();testReachAndIdentity();testFlightInitializationAndAcceleration();testVisualTrailIsNotAttack();testExpiryTailAdjunct();testOwnerEndAndInvalidation();testMineReception();testOtherFamilyScope();console.log('[gredShotBattle] PASS: real source normal-B reach, family flight, retirement, mine reception and ammo');}
