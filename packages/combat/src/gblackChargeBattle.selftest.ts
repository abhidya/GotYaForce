/** Actual BLACK banked-B release. Host precharge bookkeeping is an entry
 * approximation, not an original hold-time oracle. Root attachment and explicit
 * collision fixtures do not claim animated-joint or console geometry parity. */
import {RomDriverBridge} from './bridge.js';
import {getGBlackChargeState} from './gblackCharge.js';
import {getGRedChargeState} from './gredCharge.js';
import {spawnTimeBomberMine} from './timeBomberMineAdapter.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gblackChargeBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl062a',distance=1000){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const familyEvents:number[][]=[];const family=driver.ctx.onFamilyProjectile;driver.ctx.onFamilyProjectile=(a,spawner,row)=>{familyEvents.push([spawner,row]);family?.(a,spawner,row);};
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,k,status,arg)=>{hitArms.push([k,status,arg]);arm?.(a,k,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,familyEvents,get frame(){return frame;},get charge(){return getGBlackChargeState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
function checkSample(t:Fixture){assert(t.charge?.stream&&t.owner.sourceAnimSample,'BLACK charge publishes source sample');assert(t.owner.sourceAnimSample.frame===t.charge.stream.frame,'sample matches source clock');return t.owner.sourceAnimSample.serial;}
function until(t:Fixture,test:()=>boolean,label:string,limit=260){for(let i=0;i<limit&&!test();i++){t.tick();if(t.charge)checkSample(t);}assert(test(),`${label}: phase=${t.actor.fbPhaseSlots[0]} frame=${t.charge?.stream?.frame}`);}
function bank(t:Fixture){t.input.p1.attack=true;until(t,()=>(t.owner.cooldowns['chargeFrames']??0)>=8,'actual held B banks existing host entry charge',200);assert(!t.charge,'held bank is not a source release');}
function release(t:Fixture){
 const ammo=t.owner.weaponCells![0]!.cur,before={...t.owner.pos},eventCount=t.familyEvents.length;
 t.input.p1.attack=false;t.tick();const c=t.owner.command;
 assert(c?.exact&&c.type===3&&c.subtype===5&&c.actionIndex===3&&c.variantIndex===0&&c.recordAddress==='0x80365e38','actual release selects original charged row');
 assert(t.actor.actionIndex===3&&t.charge?.family==='black'&&!getGRedChargeState(t.actor),'BLACK enters its separate two-phase source engine');
 assert(t.charge.phase===1&&t.charge.setupCount===1&&t.charge.subphase541===0,'source setup runs once and starts normal phase1/541zero');
 assert(t.familyEvents.length===eventCount+1&&t.familyEvents[eventCount]![0]===0x8016cc24&&t.familyEvents[eventCount]![1]===0x10,'actual setup calls8016cc24 with literal row0x10, not e19a8/row17');
 assert(t.actor.yVel===4&&t.actor.gravityCoeff===0,'BLACK setup uses yVel4, not RED8');
 assert(t.owner.weaponCells![0]!.cur===ammo&&t.owner.ammo===ammo,'source type3 release does not debit another ammo');
 assert(Math.hypot(t.owner.pos.x-before.x,t.owner.pos.z-before.z)<1,'own-position carry cannot teleport toward lock target');
 assert(t.charge.stream?.frame===0&&t.charge.stream.endFrame===38&&t.charge.stream.blendMode===2&&t.charge.stream.blendTotal===9,'original main end38/mode2/blend8+1');
 assert(t.animations.some(a=>a.group===4&&a.slot===2),'main animation is originalg4s2');
 assert(!t.state.projectiles.some(p=>p.ownerUid===t.owner.uid&&p.beamSource),'BLACK release is not an e19a8 beam route');
 checkSample(t);return t.charge;
}
function testMainAndNoMashTimer(){
 const traces:string[][]=[];
 for(const mash of [false,true]){
  const t=setup();bank(t);const s=release(t),serial=checkSample(t),trace:string[]=[];let recoverySerial:number|undefined;
  for(let i=0;i<160&&t.charge;i++){
   if(mash){t.input.p1.attack=i%2===0;t.input.p1.special=i%2===0;t.input.p1.jump=i%2===0;}
   const frame=s.stream!.frame;t.tick();trace.push([s.stream!.recovery,s.stream!.frame,s.stream!.elapsed,s.phase,!!t.charge].join('/'));
   if(t.charge){
    if(!s.stream!.recovery){assert(checkSample(t)===serial,'main source instance remains stable');if(frame===0)assert(s.stream!.frame===1,'mode2 advances during blend, unlike mode1');}
    else{recoverySerial=checkSample(t);assert(recoverySerial!==serial,'recovery creates a new animation instance');}
   }
  }
  assert(!t.charge&&s.exitKind==='stream-end'&&s.setupCount===1&&!t.owner.sourceAnimSample,'ordinary stream completion returns and clears ownership');
  assert(recoverySerial!==undefined&&t.animations.some(a=>a.group===0&&a.slot===14),'original recovery clip is observed');
  traces.push(trace);
 }
 assert(JSON.stringify(traces[0])===JSON.stringify(traces[1]),'fresh button mashing cannot import RED duration/extension behavior into BLACK');
}
function testAmmoAndNeighbors(){
 const t=setup();bank(t);t.owner.ammo=0;t.owner.weaponCells![0]!.cur=0;const s=release(t);for(let i=0;i<5;i++)t.tick();assert(s.setupCount===1,'empty banked release works once and repeated false input cannot duplicate setup');
 const tap=setup();tap.input.p1.attack=true;tap.tick();tap.input.p1.attack=false;tap.tick();assert(!tap.charge,'unbanked tap retains ordinary shot route');
 for(const id of ['pl0615','pl0629']){const n=setup(id);bank(n);n.input.p1.attack=false;n.tick();assert(!n.charge&&getGRedChargeState(n.actor),'RED/NEO retain their separate sustained beam charge engine');}
 const close=setup('pl062a',100);close.input.p1.attack=true;close.tick();assert(close.owner.command?.actionIndex===1&&!close.charge,'BLACK neutral melee remains independent');
 const air=setup('pl062a',100);air.input.p1.jump=true;air.tick();air.input.p1.jump=false;air.input.p1.attack=true;air.tick();assert(air.owner.command?.actionIndex===1&&air.owner.command.variantIndex===4&&!air.charge,'BLACK airborne melee remains independent');
 const x=setup();x.input.p1.special=true;x.tick();assert(x.owner.command?.actionIndex===2&&!x.charge,'BLACK X remains independent');
}
function getSweep(t:Fixture){
 const p=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.gblackChargeSource?.kind==='sweep');
 assert(p?.gblackChargeSource?.kind==='sweep','setup creates source8016cc24 row16 sweep child');return p;
}
function sweepState(p:ReturnType<typeof getSweep>){assert(p.gblackChargeSource?.kind==='sweep','sweep discriminator remains stable');return p.gblackChargeSource;}
function testDelayedSweepAndSeparateImpact(){
 const t=setup();bank(t);const s=release(t),p=getSweep(t);
 assert(p.damageRecord?.hpDamage===30&&!p.beamSource,'source sweep carries HIT28 damage32 HP30, never beam17');
 assert(sweepState(p).stage===0&&sweepState(p).age===0&&!sweepState(p).hitActive,'setup projectile pass initializes stage0 without aging or attacking');
 const hp=t.target.hp;let stages=new Set<number>([0]);const stageCalls=[0,0];
 for(let i=0;i<100&&sweepState(p).stage!==2;i++){
  const old=sweepState(p);if(old.stage<2)stageCalls[old.stage]=(stageCalls[old.stage]??0)+1;
  // Receiver placement follows the actual source ray endpoints. This tests
  // host root/ray geometry, not original joint12 or swept animated-bone parity.
  if(old.stage===1){const u=.5;t.target.pos=v(old.start.x+(old.end.x-old.start.x)*u,old.start.y+(old.end.y-old.start.y)*u,old.start.z+(old.end.z-old.start.z)*u);t.target.vel=v(0,0,0);}
  t.tick();const now=sweepState(p);stages.add(now.stage);
  if(now.stage<2)assert(!now.hitActive&&(now.collisionGate272&1)!==0&&t.target.hp===hp,'stages0/1 suppress damage despite registered HIT');
 }
 const launched=sweepState(p);
 assert(stageCalls.join(',')==='25,6','after same-pass init, original stage durations25/6 precede launch');
 assert(stages.has(1)&&launched.stage===2&&launched.hitActive&&launched.collisionGate272===0,'stage2 launch opens exactly the source attack pass');
 assert(launched.hitUids.includes(t.target.uid)&&t.target.hp<hp,'launch resolves real direct-hit damage');
 assert(s.subphase541===0,'accepted projectile contact does not invent an actor541 early-exit writer');
 t.tick();assert(!sweepState(p).hitActive&&sweepState(p).collisionGate272===0,'next child update unregisters HIT without inventing a272 write');
 const impact=t.state.projectiles.find(q=>q.ownerUid===t.owner.uid&&q.gblackChargeSource?.kind==='impact');
 assert(impact&&impact.uid!==p.uid&&impact.damageRecord?.hpDamage===20,'accepted contact emits separate85e00 effect16 with HP20 and independent attack identity');
 // Do not assert30+20 HP loss: immunity and the damage resolver may reject or
 // reduce one of these separately registered source attacks.
 for(let i=0;i<80;i++)t.tick();assert(!t.state.projectiles.includes(p)&&!t.state.projectiles.includes(impact),'ray visual tail and impact lifecycle retire');
}
function testClearMissHasNoImpact(){
 const t=setup();bank(t);t.target.pos.y=600;release(t);const p=getSweep(t);
 // Aim the real child upward, then move the receiver away after its matrix
 // freezes in stage1. This distinguishes a clear miss from terrain contact.
 until(t,()=>sweepState(p).stage===1,'source matrix reaches frozen stage1');
 t.target.pos=v(15000,600,-15000);t.target.vel=v(0,0,0);const hp=t.target.hp;
 let impactSeen=false;for(let i=0;i<70;i++){t.tick();impactSeen ||= t.state.projectiles.some(q=>q.gblackChargeSource?.kind==='impact');}
 assert(t.target.hp===hp&&sweepState(p).hitUids.length===0,'clear upward miss never accepts a target hit');
 assert(!impactSeen,'clear miss cannot invent impact attack');
}
function testChildInvalidation(){
 for(const mode of ['death','form'] as const){
  const t=setup();bank(t);release(t);const p=getSweep(t),hp=t.target.hp;
  if(mode==='death')t.owner.hp=0;
  else t.owner.combatFormId='synthetic-replacement-form'; // Metadata-only invalidation fixture.
  t.tick();assert(!sweepState(p).hitActive&&sweepState(p).phase==='freed','invalid owner suppresses pending child attack');
  for(let i=0;i<60;i++)t.tick();
  assert(!t.state.projectiles.includes(p)&&!t.state.projectiles.some(q=>q.gblackChargeSource?.kind==='impact'),'invalidated pre-launch child cannot create delayed impact');
  assert(t.target.hp===hp,'invalidated child never damages receiver');
  if(mode==='death')assert(!t.charge&&!t.owner.sourceAnimSample,'owner death clears actor source state/sample');
 }
}
function fixtureMine(t:Fixture,pos:Vec3){
 assert(t.alternate.romDriver instanceof RomDriverBridge,'mine fixture owner has real actor');
 // Real Time Bomber constructor, synthetic active state/geometry only. No B
 // cell was consumed, so resourceOwed=false deliberately avoids a fake refund.
 const mine=spawnTimeBomberMine(t.alternate,t.alternate.romDriver.actor),m=mine.timeBomberSource!;
 assert(m.kind==='mine','constructor creates source mine');
 Object.assign(m,{phase:'active',motion:'drift',pos:{...pos},center:{...pos},direction:v(0,0,0),speed:5,life:100,bobPhase:0,floorTarget:0,resourceOwed:false});
 mine.pos={...pos};t.state.projectiles.push(mine);return mine;
}
function placeMine(mine:ReturnType<typeof fixtureMine>,pos:Vec3){const m=mine.timeBomberSource!;assert(m.kind==='mine','mine kind stable');m.pos={...pos};m.center={...pos};mine.pos={...pos};}
function testMineReceivers(){
 {
  const t=setup();bank(t);release(t);const p=getSweep(t),mine=fixtureMine(t,sweepState(p).pos);
  for(let i=0;i<40&&sweepState(p).stage!==2;i++){
   placeMine(mine,sweepState(p).pos);t.tick();const m=mine.timeBomberSource!;assert(m.kind==='mine','mine source persists');
   if(sweepState(p).stage<2)assert(m.durability===1&&m.receivedAttackUids.length===0,'prelaunch overlapping mine is not damaged');
  }
  const m=mine.timeBomberSource!;assert(m.kind==='mine'&&m.phase==='active'&&m.durability===0&&m.receivedAttackUids.includes(p.uid),'launch pass destroys HP1 mine with parent identity');
  assert(sweepState(p).hitUids.includes(mine.uid)&&!t.state.projectiles.some(q=>q.timeBomberSource?.kind==='explosion'),'ray records mine victim but mine explosion waits another child update');
  t.tick();assert(mine.timeBomberSource?.kind==='mine'&&mine.timeBomberSource.phase==='retiring'&&t.state.projectiles.some(q=>q.timeBomberSource?.kind==='explosion'),'next child update retires destroyed mine and creates its explosion');
  const impact=t.state.projectiles.find(q=>q.gblackChargeSource?.kind==='impact');assert(impact&&impact.uid!==p.uid,'mine contact produces independently identified BLACK impact');
 }
 {
  const t=setup();bank(t);release(t);const p=getSweep(t);
  until(t,()=>sweepState(p).stage===1,'impact fixture reaches frozen aim');
  for(let i=0;i<20&&sweepState(p).stage!==2;i++){t.target.pos={...sweepState(p).start};t.target.vel=v(0,0,0);t.tick();}
  assert(sweepState(p).stage===2,'impact fixture reaches launch');
  assert(sweepState(p).contactPoint,'real fighter contact establishes impact');t.tick();
  const impact=t.state.projectiles.find(q=>q.gblackChargeSource?.kind==='impact');assert(impact,'separate impact exists');
  const mine=fixtureMine(t,impact.pos);t.tick();const m=mine.timeBomberSource!;
  assert(m.kind==='mine'&&m.durability===0&&m.receivedAttackUids.includes(impact.uid)&&!m.receivedAttackUids.includes(p.uid),'fresh mine receives independent impact identity, not disabled parent');
  assert(impact.gblackChargeSource?.hitUids.includes(mine.uid),'impact records mine victim separately');
  assert(!t.state.projectiles.some(q=>q.timeBomberSource?.kind==='explosion'),'impact collision does not eagerly explode the mine');
  t.tick();assert(mine.timeBomberSource?.kind==='mine'&&mine.timeBomberSource.phase==='retiring','impact-destroyed mine retires on following child pass');
 }
}
export function runGblackChargeBattleSelfTest(){testMainAndNoMashTimer();testDelayedSweepAndSeparateImpact();testClearMissHasNoImpact();testChildInvalidation();testMineReceivers();testAmmoAndNeighbors();console.log('[gblackChargeBattle] PASS: real BLACK release, two-phase clock, delayed ray/impact and isolation');}
