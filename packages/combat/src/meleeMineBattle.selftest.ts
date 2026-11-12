/** Actual fresh-B G RED source-owned ground opener versus real Time Bomber B mines.
 * Audited source animation window10..12 is exercised, not elapsed time after arm.
 * Root geometry remains bounded host glue, not original-console output parity. No driver bypass or injected attacks.
 * Relocations isolate host front/XZ/vertical geometry, not animated source HIT parity. */
import { RomDriverBridge } from './bridge.js';
import {getNeoGredMeleeState} from './neoGredMelee.js';
import { battleStateForSelfcheck,createBattle } from './battle.js';
import { emptyInput,type StageCollision,type Projectile,type MineReceiverMeleeAttack } from './types.js';
import type { BorgStats } from './stats.js';
import type { Vec3 } from './rom/actor.js';
import type { TimeBomberMineSource } from './timeBomberMineAdapter.js';
import borgsData from '../../assets/data/borgs.json' with {type:'json'};
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
type Mine=Projectile&{timeBomberSource:TimeBomberMineSource};
function assert(value:unknown,message:string):asserts value {if(!value)throw Error(`[meleeMineBattle] ${message}`);}
function floor():StageCollision {
  const vertices:[Vec3,Vec3,Vec3][]=[
    [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
    [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)],
  ];
  return {triangles:vertices.map((vertices,index)=>({index,vertices,layerIndex:0,marker:0xcccccccc,
    normal:v(0,1,0),planeD:0,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0615',count=1) {
  const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
    {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0106']},
    {team:1,ownerPlayer:'p3',borgIds:['pl0615']},
  ]},stats);
  const inputs={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
  const tick=()=>{frame++;return battle.step(1/60,inputs);};
  const ticks=(n:number)=>{for(let i=0;i<n;i++)tick();};ticks(100);
  const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,bomber=state.borgs.find(b=>b.ownerPlayer==='p2')!,target=state.borgs.find(b=>b.ownerPlayer==='p3')!;
  owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;owner.grounded=true;
  bomber.pos=v(6000,10,-4000);bomber.vel=v(0,0,0);target.pos=v(0,10,170);target.vel=v(0,0,0);owner.lockTarget=target.uid;ticks(4);
  const mines:Mine[]=[];
  for(let i=0;i<count;i++) {
    bomber.pos.x=6000+i*500;inputs.p2.attack=true;tick();
    const mine=state.projectiles.find(p=>p.ownerUid===bomber.uid && p.timeBomberSource?.kind==='mine' && !mines.includes(p as Mine));
    assert(mine?.timeBomberSource?.kind==='mine','real B creates mine');mines.push(mine as Mine);inputs.p2.attack=false;tick();ticks(4);
  }
  const samples:MineReceiverMeleeAttack[]=[],sampleFrames:number[]=[],sampleClockFrames:(number|undefined)[]=[],observedClockFrames:number[]=[],armFrames:number[]=[];
  const sampleFixture={zeroDamage:false,onClock:undefined as ((frame:number|undefined)=>void)|undefined};
  assert(owner.romDriver instanceof RomDriverBridge,'fixture has native source driver');
  const driver=owner.romDriver;
  const sourceFrame=()=>getNeoGredMeleeState(driver.actor)?.stream?.frame;
  const arm=owner.romDriver.ctx.onArmHit!;
  owner.romDriver.ctx.onArmHit=(actor,kind,statusId,statusArg)=>{if(kind===1)armFrames.push(frame);arm(actor,kind,statusId,statusArg);};
  const sourceTick=owner.romDriver.tick.bind(owner.romDriver);
  owner.romDriver.tick=(actor,dt,all,input,emit)=>{const result=sourceTick(actor,dt,all,input,sample=>{samples.push(sample);sampleFrames.push(frame);sampleClockFrames.push(sourceFrame());emit?.(sampleFixture.zeroDamage?{...sample,damageRecord:{...sample.damageRecord,hpDamage:0}}:sample);});const clock=sourceFrame();if(clock!==undefined)observedClockFrames.push(clock);sampleFixture.onClock?.(clock);return result;};
  return {battle,state,owner,bomber,target,mines,inputs,tick,ticks,samples,sampleFrames,sampleClockFrames,observedClockFrames,armFrames,sampleFixture,sourceFrame,get frame(){return frame;}};
}
type Fixture=ReturnType<typeof setup>;
function relative(t:Fixture,x:number,y:number,z:number):Vec3 {
  const c=Math.cos(t.owner.rotY),s=Math.sin(t.owner.rotY);
  return v(t.owner.pos.x+x*c+z*s,t.owner.pos.y+y,t.owner.pos.z-x*s+z*c);
}
/** Stationary geometry adjunct, not a claim about mine direction or animated sword pose. */
function put(mine:Mine,pos:Vec3) {
  mine.pos={...pos};mine.timeBomberSource.pos={...pos};mine.timeBomberSource.center={...pos};
  mine.timeBomberSource.motion='drift';mine.timeBomberSource.speed=5;mine.timeBomberSource.direction=v(0,0,0);
}
function targetNear(t:Fixture) {t.target.pos=relative(t,0,0,170);t.target.vel=v(0,0,0);}
function targetFar(t:Fixture) {t.target.pos=relative(t,0,0,4000);t.target.vel=v(0,0,0);}
function isGeneric(t:Fixture) {return t.owner.state==='attack' && t.owner.anim==='melee' && (t.owner.cooldowns['meleeActive']??0)>0;}
function admit(t:Fixture) {
  targetNear(t);t.inputs.p1.attack=true;t.tick();
  assert(t.owner.command?.exact && t.owner.command.type===1 && t.owner.command.actionIndex===1 && t.owner.command.variantIndex===0,
    'fresh real B admits exact source-owned ground opener action1/variant0');
  assert(!isGeneric(t),'fresh B remains in source bridge, not generic melee fallback');
  for(let i=0;i<5&&t.sourceFrame()===undefined;i++){targetNear(t);t.tick();}
  assert(t.sourceFrame()!==undefined,'actual admitted source stream starts');
}
function explosions(t:Fixture) {return t.state.projectiles.filter(p=>p.ownerUid===t.bomber.uid && p.timeBomberSource?.kind==='explosion');}
function testFreshTimingAndMultiple() {
  for(const reverse of [false,true]) {
    const t=setup('pl0615',2);admit(t);
    const place=()=>{put(t.mines[0]!,relative(t,-50,0,140));put(t.mines[1]!,relative(t,50,0,140));};
    if(reverse)t.state.projectiles.reverse();const hits=t.battle.observe().telemetry.hitsByTeam[0]??0;
    for(let age=2;age<=30 && t.samples.length===0;age++) {
      targetFar(t);place();t.tick();
      if(t.samples.length===0)assert(t.mines.every(m=>m.timeBomberSource.durability===1),'actual source startup never registers receiving damage');
    }
    assert(t.samples.length===1 && t.sampleClockFrames[0]===10,'first active sample uses source animation frame10, not elapsed arm time');
    assert(t.mines.every(m=>m.timeBomberSource.durability<1 && m.timeBomberSource.phase==='active' && m.timeBomberSource.receivedAttackUids.length===1),
      'fresh source active opener damages all overlapping mines in either order');
    const uid=t.mines[0]!.timeBomberSource.receivedAttackUids[0],sample=t.samples[0]!;
    assert(t.samples.length===1 && sample.uid===uid && sample.damageRecord.index===2 && sample.damageRecord.hpDamage===30 &&
      sample.damageRecord.flagsA===1 && sample.damageRecord.flagsB===0 && sample.reach===170 && sample.yTolerance===50,
      'source sample keeps stable identity, authored record2 HP30 flags1/B0 and bounded reach170/y50');
    assert(t.mines[1]!.timeBomberSource.receivedAttackUids[0]===uid,'one source swing has one stable contact identity across mines');
    assert(explosions(t).length===0 && t.bomber.weaponCells![0]!.cur===8,'active collision does not same-frame retire/explode/refund');
    assert((t.battle.observe().telemetry.hitsByTeam[0]??0)===hits,'mine-only melee contacts do not count as fighter hits');
    t.tick();assert(explosions(t).length===2 && t.mines.every(m=>m.timeBomberSource.phase==='retiring'),'next child update explodes both destroyed mines');
    assert(t.bomber.weaponCells![0]!.cur===8,'retirement frame still owes resource');
    t.tick();assert(Number(t.bomber.weaponCells![0]!.cur)===10,'following child update refunds exactly two');
    t.inputs.p1.attack=false;t.tick();assert(t.mines.every(m=>!t.state.projectiles.includes(m)),'later update frees mines');
  }
}
function testWindowAndGeometry() {
  for(const frame of [9,10,11,12,13,18]) {
    const t=setup(),mine=t.mines[0]!;admit(t);
    // Geometry-only relocation after actor update chooses the audited animation
    // frame seen by resolveHits. It does not alter stream time or admission.
    t.sampleFixture.onClock=clock=>put(mine,clock===frame?relative(t,0,0,120):v(6000,300,-5000));
    for(let i=0;i<80&&(t.sourceFrame()??-1)<frame;i++){targetFar(t);t.tick();}
    assert(t.sourceFrame()===frame,'actual source animation reaches requested boundary');
    const active=frame>=10 && frame<=12;
    assert((mine.timeBomberSource.durability<1)===active,`source animation frame${frame} contact=${active}`);
    if(!active)assert(mine.timeBomberSource.receivedAttackUids.length===0 && explosions(t).length===0,'startup/recovery cannot invent a receiver sample');
  }
  for(const mode of ['rear','vertical','outside'] as const) {
    const t=setup(),mine=t.mines[0]!;admit(t);
    for(let i=0;i<100 && t.sourceFrame()!==undefined;i++) {
      targetFar(t);put(mine,relative(t,0,mode==='vertical'?500:0,mode==='rear'?-120:mode==='outside'?1000:120));t.tick();
    }
    assert(t.sourceFrame()===undefined&&t.observedClockFrames.includes(12),'geometry negative observes complete active window without early interruption');
    assert(mine.timeBomberSource.durability===1 && mine.timeBomberSource.receivedAttackUids.length===0 && explosions(t).length===0,`${mode} does not invent a melee contact`);
  }
}
function testSwingIdentity() {
  const t=setup(),mine=t.mines[0]!;
  // Explicit zero-HP sample/lifetime override lets one real B mine survive two swings.
  // Natural HP30 versus HP1 destruction is covered separately, not this identity fixture.
  t.sampleFixture.zeroDamage=true;mine.timeBomberSource.life=1000;
  const swing=()=>{
    admit(t);
    t.sampleFixture.onClock=clock=>put(mine,clock!==undefined&&clock>=10&&clock<=12?relative(t,0,0,120):v(6000,300,-5000));
    for(let i=0;i<100 && t.sourceFrame()!==undefined;i++){targetFar(t);t.tick();}
    t.sampleFixture.onClock=undefined;
    assert(t.sourceFrame()===undefined,'source opener completed');
    t.inputs.p1.attack=false;
  };
  swing();assert(t.sampleClockFrames.join(',')==='10,11,12',`all opener samples use only audited source frames10..12: ${t.sampleClockFrames.join(',')}`);const first=mine.timeBomberSource.receivedAttackUids[0];
  assert(mine.timeBomberSource.durability===1 && mine.timeBomberSource.receivedAttackUids.length===1,'all three active frames share one source swing identity');
  put(mine,v(6000,300,-5000));
  for(let i=0;i<160 && (t.owner.state!=='idle' || (t.owner.cooldowns['shot']??0)>0);i++){targetFar(t);t.tick();}
  targetNear(t);t.ticks(4);swing();
  assert(Number(mine.timeBomberSource.durability)===1 && Number(mine.timeBomberSource.receivedAttackUids.length)===2 && mine.timeBomberSource.receivedAttackUids[1]!==first,
    'fresh real B source swing renews identity and can register surviving zero-HP fixture mine again');
}
function testExcludedLanes() {
  for(const id of ['pl0629','pl0200']) {
    const t=setup(id),mine=t.mines[0]!;targetNear(t);t.inputs.p1.attack=true;t.tick();
    assert(t.owner.state==='attack','unrelated source lane receives real B attack');
    for(let frame=2;frame<=16;frame++){targetFar(t);put(mine,relative(t,0,0,120));t.tick();}
    assert(mine.timeBomberSource.durability===1 && mine.timeBomberSource.receivedAttackUids.length===0,`${id} is not silently promoted to G RED sample`);
  }
  const air=setup();air.inputs.p1.jump=true;air.tick();air.inputs.p1.jump=false;
  assert(!air.owner.grounded,'real jump establishes airborne input');
  targetNear(air);air.inputs.p1.attack=true;air.tick();
  for(let frame=2;frame<=16;frame++){targetFar(air);put(air.mines[0]!,relative(air,0,0,120));air.tick();}
  assert(air.mines[0]!.timeBomberSource.durability===1 && air.mines[0]!.timeBomberSource.receivedAttackUids.length===0,'airborne source action creates no ground sample');
  const generic=setup(),mine=generic.mines[0]!;admit(generic);let found=false;
  // Hold through the initial source action, keeping mine far away, until real
  // host generic fallback starts. No driver disable or command injection.
  for(let i=0;i<140;i++){targetNear(generic);generic.tick();if(isGeneric(generic)){found=true;break;}}
  assert(found,'actual held B eventually enters generic fallback');generic.inputs.p1.attack=false;
  while((generic.owner.cooldowns['meleeActive']??0)>0){targetFar(generic);put(mine,relative(generic,0,0,120));generic.tick();}
  assert(mine.timeBomberSource.durability===1 && mine.timeBomberSource.receivedAttackUids.length===0,'generic fallback melee is outside source-owned registration lane');
}
export function runMeleeMineBattleSelfTest():void {
  testFreshTimingAndMultiple();testWindowAndGeometry();testSwingIdentity();testExcludedLanes();
  console.log('G RED fresh source-owned grounded B opener versus Time Bomber mines: passed (host geometry and source animation clock)');
}
