/** Actual RED/NEO banked-B release. Host precharge bookkeeping is an entry
 * approximation, not an original hold-time oracle. Root attachment and explicit
 * collision fixtures do not claim animated-joint or console geometry parity. */
import {RomDriverBridge} from './bridge.js';
import {getGRedChargeState} from './gredCharge.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredChargeBattle] ${s}`);}
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
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,k,status,arg)=>{hitArms.push([k,status,arg]);arm?.(a,k,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,get frame(){return frame;},get charge(){return getGRedChargeState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
const ids=['pl0615','pl0629'] as const;
function checkSample(t:Fixture){assert(t.charge?.stream&&t.owner.sourceAnimSample,'charge source publishes animation sample');assert(t.owner.sourceAnimSample.frame===t.charge.stream.frame,'sample follows conditional source clock');return t.owner.sourceAnimSample.serial;}
function until(t:Fixture,test:()=>boolean,label:string,limit=260){for(let i=0;i<limit&&!test();i++){t.tick();if(t.charge)checkSample(t);}assert(test(),`${label}: phase=${t.actor.fbPhaseSlots[0]} frame=${t.charge?.stream?.frame}`);}
function bank(t:Fixture,amount=8){
 // This observes existing host charge bookkeeping. It is deliberately not a
 // claim that original charge admission uses these frame thresholds.
 t.input.p1.attack=true;until(t,()=>(t.owner.cooldowns['chargeFrames']??0)>=amount,'actual held B banks host charge',200);
 assert(!t.charge&&!t.state.projectiles.some(p=>p.beamSource?.sourceRow===15),'holding alone does not enter source release or create charge beam');
}
function release(t:Fixture){
 const ammo=t.owner.weaponCells![0]!.cur,before={...t.owner.pos};
 t.input.p1.attack=false;t.tick();const c=t.owner.command;
 assert(c?.exact&&c.type===3&&c.subtype===5&&c.actionIndex===3&&c.variantIndex===0&&c.recordAddress==='0x80365e38','real banked release resolves exact source charged row');
 assert(t.actor.actionIndex===3&&t.charge,'actual release dispatches action3 rather than leaving actor on prior ordinary shot');
 assert(t.owner.weaponCells![0]!.cur===ammo&&t.owner.ammo===ammo,'charged source entry does not debit another ammo cell');
 assert(Math.hypot(t.owner.pos.x-before.x,t.owner.pos.z-before.z)<1,'stationary source release does not teleport toward or away from locked target');
 assert(t.actor.yVel===8&&t.actor.gravityCoeff===0,'source setup callback supplies yVel8 and gravity0');
 assert(t.charge.releaseCount===0&&!t.state.projectiles.some(p=>p.ownerUid===t.owner.uid),'source release input does not immediately produce generic twin shots');
 assert(t.charge.chargeTimer560===30&&t.charge.extensionBudget54e===30,'source timer and edge extension budget initialize independently');
 assert(t.hitArms.some(a=>a.join(',')==='0,14,255'),'source forwards HIT0/status14/255 metadata without inventing an attack');
 checkSample(t);return t.charge;
}
function testSourceReleaseAndLifecycle(){
 for(const id of ids){
  const t=setup(id);bank(t);const s=release(t),initialSerial=checkSample(t);
  let held=0,callbackFrame:number|undefined;const epochs=new Set<number>([initialSerial]);
  for(let i=0;i<180&&s.releaseCount===0;i++){
   const frame=s.stream!.frame,wait=s.stream!.waitCount;t.tick();if(wait>0&&s.stream!.frame===frame)held++;
   if(s.releaseCount)callbackFrame=frame;
  }
  assert(callbackFrame===12&&s.releaseCount===1&&held>0,'authored gate12 after mode8 pause invokes exactly one source release callback');
  const beam=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.beamSource?.sourceRow===15);
  assert(beam?.beamSource&&t.state.projectiles.filter(p=>p.ownerUid===t.owner.uid).length===1,'one row15 source beam replaces generic two-shot fallback');
  assert(beam.damageRecord?.hpDamage===1,'row15 HIT27 uses damage31 HP1');
  assert(beam.beamSource.scale<=1,'row15 max scale differs from Beam Gunman row1');
  let recoil=false,recovery=false;
  for(let i=0;i<260&&t.charge;i++){
   t.tick();if(t.charge){epochs.add(checkSample(t));recoil ||= s.stream!.stage==='recoil';recovery ||= s.stream!.stage==='recovery';}
  }
  assert(!t.charge&&s.releaseCount===1&&recoil&&recovery&&epochs.size===3,'source plays main/recoil/recovery once and completes');
  assert(!t.owner.sourceAnimSample,'completion clears source sample');
  for(let i=0;i<30;i++)t.tick();assert(!t.state.projectiles.includes(beam),'owner state drop releases beam through bounded tail');
 }
}
function testIndependentPulsesAndDeathTail(){
 const t=setup();bank(t);const s=release(t);until(t,()=>s.releaseCount===1,'source beam callback');
 const beam=t.state.projectiles.find(p=>p.ownerUid===t.owner.uid&&p.beamSource?.sourceRow===15)!;
 assert(beam?.beamSource,'real source emitter exists');
 until(t,()=>beam.beamSource!.pulses.some(p=>p.stage==='init'),'first pulse init pass');
 const first=beam.beamSource.pulses.find(p=>p.stage==='init')!,id=first.attackUid;
 assert(first.start.x===first.end.x&&first.start.y===first.end.y&&first.start.z===first.end.z,'new child begins as one init sphere');
 // Root receiver placement along the existing live beam, not a fabricated hit.
 const b=beam.beamSource;t.target.pos=v(b.start.x+(b.end.x-b.start.x)*.1,b.start.y+(b.end.y-b.start.y)*.1,b.start.z+(b.end.z-b.start.z)*.1);t.target.vel=v(0,0,0);
 const hp=t.target.hp;t.tick();
 const sweep=beam.beamSource.pulses.find(p=>p.attackUid===id);
 assert(sweep?.stage==='sweep'&&sweep.hitUids.includes(t.target.uid)&&t.target.hp<hp,'same child identity sweeps and deals actual row15 damage');
 assert(new Set(sweep.hitUids).size===sweep.hitUids.length,'one pulse records each victim only once');
 const fresh=beam.beamSource.pulses.find(p=>p.stage==='init');assert(fresh&&fresh.attackUid!==id,'next pulse has independent identity');
 const pending=new Set(beam.beamSource.pulses.map(p=>p.attackUid));t.owner.hp=0;t.tick();
 assert(beam.beamSource.phase==='tail'&&!t.charge,'owner death starts beam tail and clears action');
 assert(beam.beamSource.pulses.every(p=>pending.has(p.attackUid)),'death permits pending child completion but no newly allocated pulse');
 for(let i=0;i<30;i++)t.tick();assert(!t.state.projectiles.includes(beam),'death tail and pending children eventually retire');
}
function testFreshEdgeExtension(){
 const t=setup();bank(t);const s=release(t);until(t,()=>s.phase===2,'source release enters phase2');
 assert(s.extensionBudget54e===30,'phase2 starts with source extension budget30');
 t.input.p1.attack=true;t.tick();assert(Number(s.extensionBudget54e)===29,'one fresh B raw edge consumes one extension unit');
 for(let i=0;i<3;i++)t.tick();assert(Number(s.extensionBudget54e)===29,'holding B does not repeatedly extend source timer');
 for(let i=0;i<12;i++){
  t.input.p1.attack=false;t.input.p1.jump=false;t.input.p1.special=false;t.tick();
  const before=s.extensionBudget54e;t.input.p1.attack=true;t.input.p1.jump=true;t.input.p1.special=true;t.tick();
  assert(s.extensionBudget54e===Math.max(0,before-3),'three actual fresh buttons count raw bits, capped by remaining budget');
  assert(s.phase===2&&s.releaseCount===1,'extension preserves single active release rather than redispatching attacks');
 }
 assert(Number(s.extensionBudget54e)===0,'source extension budget saturates at0 after30 fresh bits');
 t.input.p1.attack=false;t.input.p1.jump=false;t.input.p1.special=false;
 until(t,()=>!t.charge,'extended action still completes');
}
function testAmmoAndReleaseEdges(){
 for(const id of ids){
  const t=setup(id);bank(t);t.owner.ammo=0;t.owner.weaponCells![0]!.cur=0;
  const s=release(t);until(t,()=>s.releaseCount===1,'banked release still emits with cell0 empty');
  assert(s.releaseCount===1,'source callback requires no additional ammo debit');
  for(let i=0;i<5;i++){t.input.p1.attack=false;t.tick();}assert(s.releaseCount===1,'repeated released state cannot duplicate callback');
  const tap=setup(id);tap.input.p1.attack=true;tap.tick();tap.input.p1.attack=false;tap.tick();
  assert(!tap.charge,'unbanked tap keeps ordinary B route');
 }
}
function testInterruptionAndIsolation(){
 for(const id of ids){
  const t=setup(id);bank(t);const s=release(t);t.owner.hp=0;t.tick();
  assert(!t.charge&&!t.owner.sourceAnimSample,'death interrupts source startup');
  for(let i=0;i<100;i++)t.tick();assert(s.releaseCount===0&&!t.state.projectiles.some(p=>p.beamSource?.sourceRow===15),'interrupted startup never emits later');
  const close=setup(id,100);close.input.p1.attack=true;close.tick();assert(close.owner.command?.actionIndex===1&&!close.charge,'close neutral B retains its melee route');
  const air=setup(id,100);air.input.p1.jump=true;air.tick();air.input.p1.jump=false;air.input.p1.attack=true;air.tick();assert(air.owner.command?.actionIndex===1&&air.owner.command.variantIndex===4&&!air.charge,'actual air B retains its melee route');
  const x=setup(id);x.input.p1.special=true;x.tick();assert(x.owner.command?.actionIndex===2&&!x.charge,'X remains separate source action2');
 }
 const black=setup('pl062a');bank(black);black.input.p1.attack=false;black.tick();assert(!black.charge,'BLACK separate charge engine remains outside this lane');
 const beam=setup('pl0104');beam.input.p1.special=true;beam.tick();until(beam,()=>beam.state.projectiles.some(p=>p.ownerUid===beam.owner.uid&&p.beamSource),'Beam Gunman original X startup reaches row1 beam');assert(beam.state.projectiles.some(p=>p.ownerUid===beam.owner.uid&&p.beamSource&&p.beamSource.sourceRow!==15),'Beam Gunman X retains its separate row1 beam');
}
export function runGredChargeBattleSelfTest(){testSourceReleaseAndLifecycle();testIndependentPulsesAndDeathTail();testFreshEdgeExtension();testAmmoAndReleaseEdges();testInterruptionAndIsolation();console.log('[gredChargeBattle] PASS: real banked release, source callback/beam, ammo, lifecycle and isolation');}
