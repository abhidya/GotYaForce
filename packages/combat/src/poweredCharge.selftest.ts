import { spawnPoweredSource, capturePoweredNormalAim } from "./poweredProjectileRuntime.js";
import { stepDiverXRefill, refreshDiverAmmoRate } from "./diverAmmo.js";
import { stepProjectiles } from "./combat.js";
import { stepPoweredCharge, commitPoweredCharge } from './poweredCharge.js';
import { runSelfTest as runFlightTests } from './poweredProjectile.selftest.js';
import { createBattle, battleStateForSelfcheck } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { emptyInput, type BorgRuntime } from './types.js';
import type { BorgStats } from './stats.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
function assert(v:unknown,msg:string):asserts v { if(!v) throw new Error(`[poweredCharge] ${msg}`); }
function setup(){
 const battle=createBattle({stageId:'st00',bounds:{x:10000,z:10000},forces:[
 {team:0,ownerPlayer:'p1',borgIds:['pl0101']},{team:1,ownerPlayer:'p2',borgIds:['pl0615']} ]},stats);
 const inputs={p1:emptyInput(),p2:emptyInput()};
 for(let n=0;n<100;n++)battle.step(1/60,inputs);
 const state=battleStateForSelfcheck(battle),owner=state.borgs[0]!,driver=owner.romDriver as RomDriverBridge;
 owner.pos={x:0,y:0,z:0};state.borgs[1]!.pos={x:0,y:0,z:6000};
 return {battle,inputs,state,owner,driver};
}
/** Real Battle input path: admission and the authored resource gate are separate. */
function runPoweredNormalSelfTest():void {
 const instrument=()=>{
  const test=setup();
  const events:{addr:number,row:number}[]=[];
  const allocations:{slot:number,count:number,mode:number|undefined,accepted:boolean}[]=[];
  const spawn=test.driver.ctx.onFamilyProjectile!;
  test.driver.ctx.onFamilyProjectile=(a,addr,row)=>{events.push({addr,row});spawn(a,addr,row);};
  const allocate=test.driver.ctx.onAllocateResource!;
  test.driver.ctx.onAllocateResource=(a,slot,count,mode)=>{
   const accepted=allocate(a,slot,count,mode);allocations.push({slot,count,mode,accepted});return accepted;
  };
  return {...test,events,allocations};
 };
 {
  const {battle,inputs,state,owner,driver,events,allocations}=instrument();
  const cell=owner.weaponCells![1]!;const full=cell.cur;
  assert(full>0,'normal-X fixture starts with ammo');
  inputs.p1.special=true;battle.step(1/60,inputs);
  assert(owner.command?.type===2&&owner.command.actionIndex===2&&owner.command.recordAddress==='0x8034ea20','normal press selects exact type2/action2');
  assert(driver.actor.actionIndex===2,'normal press enters ROM action2');
  const savedAim=owner.poweredNormalAim;
  assert(savedAim?.targetUid===state.borgs[1]!.uid&&savedAim.pos.z===6000,'normal admission snapshots selected target root');
  state.borgs[1]!.pos={x:6000,y:0,z:0};
  assert(cell.cur===full&&allocations.length===0&&events.length===0,'normal press admits without spend or spawn');
  for(let i=0;i<15;i++){
   battle.step(1/60,inputs);
   assert(Number(events.length)===0&&Number(allocations.length)===0&&cell.cur===full,'no normal allocation/spawn before authored frame16');
  }
  battle.step(1/60,inputs);
  assert(events.map(e=>`${e.addr.toString(16)}:${e.row}`).join(',')==='8016d584:0,8016d584:1,8016d584:2,8016d584:3','normal frame16 dispatches all four source ports');
  assert(Number(allocations.length)===1&&allocations[0]!.slot===2&&allocations[0]!.count===1&&allocations[0]!.accepted,'one source weapon2 cell allocation at gate');
  assert(cell.cur===full-1,'source weapon2 spends exactly one browser weapon1 cell');
  const children=state.projectiles.filter(p=>p.ownerUid===owner.uid);
  assert(owner.state==='special','normal launch remains special, not generic shooting slot');
  const flashes=battle.observe().poweredLaunchFlashes;
  assert(flashes.length===4&&flashes.every(f=>f.cause==='normal'&&f.ageFrames===0&&f.effectId===0),'four normal launch flashes, not sixteen');
  assert(children.length===16&&children.every(p=>p.poweredSource?.kind==='secondary'),'normal emits only sixteen source secondaries, no generic fallback');
  for(const port of [0,1,2,3])assert(children.filter(p=>p.poweredSource?.kind==='secondary'&&p.poweredSource.port===port).length===4,`four normal children on port ${port}`);
  const firstPort=children.filter(p=>p.poweredSource?.kind==='secondary'&&p.poweredSource.port===0);
  const origin=firstPort[0]!.pos;const aimLength=Math.hypot(savedAim.pos.x-origin.x,savedAim.pos.y-origin.y,savedAim.pos.z-origin.z);
  const coneSum=firstPort.reduce((sum,p)=>{const child=p.poweredSource!;assert(child.kind==='secondary','normal secondary state');return {x:sum.x+child.direction.x,y:sum.y+child.direction.y,z:sum.z+child.direction.z};},{x:0,y:0,z:0});
  const coneLength=Math.hypot(coneSum.x,coneSum.y,coneSum.z);
  assert(Math.abs(coneSum.x/coneLength-(savedAim.pos.x-origin.x)/aimLength)<1e-8&&Math.abs(coneSum.z/coneLength-(savedAim.pos.z-origin.z)/aimLength)<1e-8,'normal fire uses entry snapshot, not target moved during windup');
  assert(children.every(p=>p.life===40&&p.romShotKind===0&&p.flightVisual?.bankTexId===26&&p.hitRadius===20),'normal source life/HIT/visuals and no constructor movement');
  battle.step(1/60,inputs);
  assert(children.every(p=>p.life===39),'normal child advances once on subsequent frame');
  for(let i=0;i<80;i++)battle.step(1/60,inputs);
  assert(Number(events.length)===4&&Number(allocations.length)===1,'held normal never repeats after action ends');
  inputs.p1.special=false;battle.step(1/60,inputs);
  for(let i=0;i<45;i++)battle.step(1/60,inputs);
  assert(cell.cur===full,'source refill completes before normal repress');
  assert(Number(events.length)===4&&Number(allocations.length)===1,'short release never duplicates normal volley');
  inputs.p1.special=true;battle.step(1/60,inputs);
  assert(driver.actor.actionIndex===2,'fresh repress starts another normal action');
  for(let i=0;i<16;i++)battle.step(1/60,inputs);
  assert(Number(events.length)===8&&Number(allocations.length)===2,'fresh repress fires exactly one fresh normal volley');
 }
 {
  const {battle,inputs,owner}=setup();const cell=owner.weaponCells![1]!;
  assert(owner.weaponCells![2]===cell&&cell.timer===0&&cell.cur===cell.max&&cell.refillParam===120,`Powered full source cell2 aliases browser cell1 with zero initial debt and period120: ${JSON.stringify(cell)}, alias=${owner.weaponCells![2]===cell}`);
  cell.cur=cell.max-1;cell.timer=120;
  for(let i=0;i<119;i++)battle.step(1/60,inputs);
  assert(Number(cell.timer)===1&&cell.cur===cell.max-1,'baseline refill retains integer ammo for119 frames');
  battle.step(1/60,inputs);assert(Number(cell.timer)===0&&cell.cur===cell.max,'baseline source refill completes on frame120');
  cell.cur=cell.max-1;cell.timer=120;owner.sourceAmmoRefillPauseMask=4;
  battle.step(1/60,inputs);assert(Number(cell.timer)===120,'source slot2 mask bit4 pauses X refill');
  owner.sourceAmmoRefillPauseMask=2;
  battle.step(1/60,inputs);assert(Number(cell.timer)===119,'browser slot1 mask bit2 does not pause source X');
  owner.sourceAmmoRefillPauseMask=0;owner.sourceAmmoRefillRate=1;owner.burstPaired=true;
  cell.timer=120;stepDiverXRefill(cell,owner);
  assert(Number(cell.timer)===110,'paired first refill uses cached baseline times source multiplier10');
  refreshDiverAmmoRate(owner);stepDiverXRefill(cell,owner);
  assert(Number(cell.timer)===95,'paired subsequent refill uses refreshed base1.5 times source multiplier10');
 }
 {
  const {owner,driver}=setup();
  driver.actor.pos={x:500,y:70,z:-900};driver.actor.heading=16384;
  driver.actor.modelScale=2;driver.actor.sizeScale=1;
  capturePoweredNormalAim(owner,driver.actor,[]);
  const aim=owner.poweredNormalAim!;
  assert(aim.targetUid===null&&Math.abs(aim.pos.x-20000)<1e-8&&Math.abs(aim.pos.z)<1e-8,'targetless aim uses absolute source yaw endpoint, without adding owner X/Z');
  assert(Math.abs(aim.pos.y-(70+2*124.89293384552002))<1e-8,'targetless aim uses decoded joint3 height and actor scale');
 }
 {
  const {battle,inputs,events,allocations}=instrument();
  inputs.p1.special=true;battle.step(1/60,inputs);
  inputs.p1.special=false;
  for(let i=0;i<15;i++){battle.step(1/60,inputs);assert(events.length===0,'short tap still waits for authored frame16');}
  battle.step(1/60,inputs);
  assert(Number(events.length)===4&&allocations.length===1,'short tap completes exactly one source normal volley');
  for(let i=0;i<90;i++)battle.step(1/60,inputs);
  assert(Number(events.length)===4&&allocations.length===1,'short tap release cannot trigger a second volley');
 }
 for(const mode of ['empty','depleted','interrupted','busy'] as const){
  const {battle,inputs,state,owner,events,allocations}=instrument();
  if(mode==='empty')owner.weaponCells![1]!.cur=0;
  if(mode==='busy'){owner.state='hit';owner.stateTime=0;owner.cooldowns['hitstun']=20;}
  inputs.p1.special=true;battle.step(1/60,inputs);
  if(mode==='depleted')owner.weaponCells![1]!.cur=0;
  if(mode==='interrupted'){owner.state='hit';owner.stateTime=0;owner.cooldowns['hitstun']=20;}
  for(let i=0;i<90;i++)battle.step(1/60,inputs);
  assert(battle.observe().poweredLaunchFlashes.length===0,`${mode}: no launch presentation`);
  assert(events.length===0&&state.projectiles.filter(p=>p.ownerUid===owner.uid).length===0,`${mode}: no normal volley or generic fallback`);
  if(mode==='depleted')assert(allocations.length===1&&!allocations[0]!.accepted,'depletion after admission fails exactly one source allocation');
  else assert(allocations.length===0,`${mode}: no allocation before admitted fire gate`);
  inputs.p1.special=false;battle.step(1/60,inputs);
  assert(events.length===0,`${mode}: release does not buffer or duplicate normal action`);
 }
}
export function runPoweredChargeSelfTest():void {
 runFlightTests();
 runPoweredPresentationSelfTest();
 runPoweredNormalSelfTest();
 for(const boosted of [false,true]){
 const b={burstActive:boosted,burstPaired:boosted} as BorgRuntime;
 const readyFrame=boosted?28:190;
 for(let i=1;i<readyFrame;i++)assert(!stepPoweredCharge(b,true).ready,`early ready ${i}/${readyFrame}`);
 assert(stepPoweredCharge(b,true).ready,'threshold');
 const release=stepPoweredCharge(b,false);assert(release.releasedReady&&release.charge===178,'release before decay');
 stepPoweredCharge(b,true);assert(Number(b.poweredCharge!.charge)===178&&Number(b.poweredCharge!.warmup)===1,'retained residual');
 commitPoweredCharge(b);assert(Number(b.poweredCharge!.charge)===0&&Number(b.poweredCharge!.warmup)===0,'commit reset');
 for(let i=0;i<30;i++)stepPoweredCharge(b,true,true);
 assert(Number(b.poweredCharge!.charge)===0,'active type5 reset');
 }
 for(const ammo of [0,1]){
 const {battle,inputs,state,owner,driver}=setup();
 const events:{addr:number,row:number}[]=[];let allocations=0;
 const chargedCues:number[]=[];battle.onRomCue=c=>chargedCues.push(c);
 const spawn=driver.ctx.onFamilyProjectile!;
 driver.ctx.onFamilyProjectile=(a,addr,row)=>{events.push({addr,row});spawn(a,addr,row);};
 const alloc=driver.ctx.onAllocateResource!;
 driver.ctx.onAllocateResource=(a,slot,count,mode)=>{allocations++;return alloc(a,slot,count,mode);};
 owner.weaponCells![1]!.cur=ammo;
 inputs.p1.special=true;
 for(let i=0;i<189;i++)battle.step(1/60,inputs);
 assert(Number(owner.poweredCharge!.charge)===179,'actual raw hold below threshold despite normal-X action');
 assert(events.every(e=>e.addr!==0x8007db5c),'holding never emits charged primaries');
 battle.step(1/60,inputs);assert(owner.poweredCharge!.ready,'actual frame190 ready');
 owner.weaponCells![1]!.cur=ammo;
 events.length=0;allocations=0;chargedCues.length=0;
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(owner.command?.type===5&&owner.command.actionIndex===3&&owner.command.recordAddress==='0x8034ead0','exact source command');
 assert(driver.actor.actionIndex===3,'bridge action3');
 assert(Number(owner.poweredCharge!.charge)===0,'live commit reset');
 for(let i=0;i<90&&Number(events.length)===0;i++)battle.step(1/60,inputs);
 assert(events.map(e=>e.row).join(',')==='8,9,6,7',`four source rows (sound is separate): ${JSON.stringify(events)}`);
 assert(chargedCues.filter(c=>c===6).length===1,'charged fire plays source cue6 once');
 assert(allocations===0,'no charged ammo allocation');
 const primaries=state.projectiles.filter(p=>p.poweredSource?.kind==='primary');
 assert(owner.state==='special','charged launch remains special, not generic shooting slot');
 const primaryFlashes=battle.observe().poweredLaunchFlashes;
 assert(primaryFlashes.length===4&&primaryFlashes.every(f=>f.cause==='primary'),'charged launches four independent flashes');
 assert(primaries.length===4,`four primary projectiles, got ${primaries.length}`);
 assert(primaries.every(p=>p.romShotKind===15&&p.flightVisual?.bankTexId===125&&p.romScale?.[0]===.4),'exact source visuals/HIT');
 assert(primaries.every(p=>p.pos.y>0),'static bind attachments above floor');
 assert(primaries.every(p=>p.hitRadius===20),'host max-extent geometry must not collapse to raw radius0');
 assert(primaries.map(p=>(p.poweredSource as {row:number}).row).join(',')==='8,9,6,7','row identity survives');
 assert(primaries.every(p=>p.life===599),'constructor update exactly once on battle spawn frame');
 const p=primaries[0]!;
 const byUid=new Map(state.borgs.map(b=>[b.uid,b]));
 const stepped=stepProjectiles([p],[],new Map(),byUid);
 assert(stepped[0]!.life===598,'first subsequent frame advances once');
 const source=p.poweredSource!;assert(source.kind==='primary','primary state');
 source.targetUid=state.borgs[1]!.uid;
 source.pos={x:0,y:100,z:0};p.pos={...source.pos};
 state.borgs[1]!.pos={x:0,y:100,z:250};
 const children=stepProjectiles([p],[],new Map(),byUid);
 assert(children.length===4&&children.every(c=>c.poweredSource?.kind==='secondary'),'proximity replacement before collision');
 assert(children.every(c=>c.life===40&&c.pos.z===0&&c.romShotKind===0),'new children do not fly immediately');
 assert(children.every(c=>c.hitRadius===20),'secondary max-extent collision radius');
 assert(children.every(c=>c.sourceHitCollisionFlags===1)&&p.sourceHitCollisionFlags===5,'distinct HIT flags preserved');
 const moved=stepProjectiles(children,[],new Map(),byUid);
 assert(moved.every(c=>c.life===39&&Math.hypot(c.pos.x,c.pos.z)>0),'secondary next frame moves');
 const secondary=moved[0]!;assert(secondary.poweredSource!.kind==='secondary','secondary');
 secondary.poweredSource!.life=1;
 const shrinking=stepProjectiles([secondary],[],new Map(),byUid);
 assert(shrinking.length===1&&shrinking[0]!.poweredSource!.kind==='secondary'&&shrinking[0]!.poweredSource!.phase==='shrink','secondary expiry shrinks');
 owner.alive=false;
 const dyingChild=moved[1]!;const originalScale=dyingChild.poweredSource!.scale;
 const deadOwner=stepProjectiles([dyingChild],[],new Map(),byUid);
 assert(deadOwner.length===1&&deadOwner[0]!.poweredSource!.kind==='secondary'&&deadOwner[0]!.poweredSource!.phase==='shrink','dead owner secondary enters shrink');
 assert(deadOwner[0]!.poweredSource!.scale===originalScale*.8,'dead owner first shrink update');
 const continuing=stepProjectiles(deadOwner,[],new Map(),byUid);
 assert(continuing.length===1&&continuing[0]!.poweredSource!.scale<originalScale*.8,'dead owner does not erase shrinking child');
 assert(stepProjectiles([primaries[1]!],[],new Map(),byUid).length===0,'dead owner primary cannot split or move');
 owner.alive=true;
 // Interrupt/repeat resets choreography and requires a fresh complete hold.
 state.projectiles.length=0;state.borgs[1]!.pos={x:0,y:0,z:6000};
 driver.interrupt();owner.state='idle';owner.anim='idle';owner.cooldowns['special']=0;
 events.length=0;inputs.p1.special=true;
 for(let i=0;i<190;i++)battle.step(1/60,inputs);
 assert(events.every(e=>e.addr!==0x8007db5c),'repeat hold never auto-fires charged primaries');
 events.length=0;
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(Number(events.length)===0&&driver.actor.contactP1===0,'repeat resets part0 aux gate');
 for(let i=0;i<15;i++) { battle.step(1/60,inputs); assert(Number(events.length)===0,'repeat may not fire before authored frame16'); }
 for(let i=0;i<30&&Number(events.length)===0;i++)battle.step(1/60,inputs);
 assert(Number(events.length)===4,'repeat release starts fresh four-shot source volley');
 }
 {
 const {battle,inputs,owner,driver}=setup();let shots=0;
 const spawn=driver.ctx.onFamilyProjectile!;driver.ctx.onFamilyProjectile=(a,addr,row)=>{shots++;spawn(a,addr,row);};
 inputs.p1.special=true;for(let i=0;i<90;i++)battle.step(1/60,inputs);
 const heldShots=shots;
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(owner.command?.type!==5&&shots===heldShots,'old90-frame threshold cannot activate source action3 or duplicate normal-X');
 assert(Number(owner.poweredCharge!.charge)===78,'underready residual preserved');
 }
 {
 const {battle,inputs,state,owner,driver}=setup();let shots=0;
 const spawn=driver.ctx.onFamilyProjectile!;driver.ctx.onFamilyProjectile=(a,addr,row)=>{shots++;spawn(a,addr,row);};
 owner.weaponCells![1]!.cur=0;
 inputs.p1.special=true;for(let i=0;i<190;i++)battle.step(1/60,inputs);
 inputs.p1.special=false;battle.step(1/60,inputs);
 const target=state.borgs[1]!;target.pos={x:owner.pos.x+20,y:owner.pos.y,z:owner.pos.z};const hp=target.hp;
 for(let i=0;i<5;i++)battle.step(1/60,inputs);
 assert(target.hp===hp&&shots===0,'close target receives no pre-spawn body/effect damage');
 owner.state='hit';owner.stateTime=0;owner.cooldowns['hitstun']=20;
 for(let i=0;i<80;i++)battle.step(1/60,inputs);
 assert(shots===0,'hit interrupts windup without a late volley');
 assert(target.poweredCharge===undefined,'unrelated borg receives no source charge state');
 }
 {
 const {owner,driver}=setup();driver.actor.actionIndex=3;driver.actor.pos={x:0,y:0,z:0};driver.actor.heading=0;
 const shots=spawnPoweredSource(owner,driver.actor,0x8007db5c,8,[])!;
 assert(shots.length===1&&shots[0]!.poweredInitialPosition?.z===30-0.00000385384,'constructor keeps muzzle origin');
 const result=stepProjectiles(shots,[],new Map(),new Map(),{
 bounds:{minX:-2000,maxX:2000,minZ:-2000,maxZ:2000},
 collision:{triangles:[{index:0,layerIndex:0,marker:0xcccccccc,
 vertices:[{x:-1000,y:-1000,z:60},{x:1000,y:-1000,z:60},{x:0,y:1000,z:60}],
 normal:{x:0,y:0,z:1},planeD:60,bounds2d:{minX:-1000,maxX:1000,minZ:60,maxZ:60}}]}});
 assert(result.length===0&&shots[0]!.despawnReason==='hit-terrain'&&shots[0]!.pos.z===60,'constructor segment hits wall between muzzle and endpoint');
 }
 console.log('Powered normal/charged-X integration: passed');
}

/** Real simulation observation lifetime, separate from projectile/render lifetime. */
function runPoweredPresentationSelfTest():void {
 const {battle,inputs,state}=setup();
 const cues:number[]=[];battle.onRomCue=cue=>cues.push(cue);
 inputs.p1.special=true;
 for(let i=0;i<17;i++)battle.step(1/60,inputs);
 const first=battle.observe();
 assert(first.poweredLaunchFlashes.length===4,'normal admitted fire yields four live events');
 assert(cues.filter(c=>c===6).length===4,'normal sound6 once per port');
 assert(new Set(first.poweredLaunchFlashes.map(f=>f.spin)).size>1,'visual RNG varies across first volley without gameplay RNG draws');
 for(const f of first.poweredLaunchFlashes){
  for(const axis of Object.values(f.basis))assert(Math.abs(Math.hypot(axis.x,axis.y,axis.z)-1)<1e-8,'unit launch basis never inherits actor scale');
 }
 for(let i=0;i<20;i++)assert(battle.observe()===first,'render-only and pause observation cannot age or replay events');
 state.projectiles.length=0;
 for(let age=1;age<4;age++){
  const observed=battle.step(1/60,inputs);
  assert(observed.poweredLaunchFlashes.length===4&&observed.poweredLaunchFlashes.every(f=>f.ageFrames===age),'flash persists independently after children disappear');
  assert(first.poweredLaunchFlashes.every(f=>f.ageFrames===0),'previous observation remains immutable over steps');
 }
 assert(battle.step(1/60,inputs).poweredLaunchFlashes.length===0,'flash retires on source frame4');
 assert(cues.filter(c=>c===6).length===4,'aging does not replay cue');
 // Source charged split event survives its primary and does not depend on owner action.
 const test=setup();test.driver.actor.actionIndex=3;
 const initial:import('./poweredProjectile.js').PoweredLaunchSeed[]=[];
 const primary=spawnPoweredSource(test.owner,test.driver.actor,0x8007db5c,8,test.state.borgs,(_o,e)=>initial.push(e))![0]!;
 assert(initial.length===1&&initial[0]!.cause==='primary','primary FX once before flight');
 assert(initial[0]!.pos.z===primary.poweredInitialPosition!.z&&initial[0]!.pos.z!==primary.pos.z,'primary flash at muzzle, not advanced endpoint');
 const src=primary.poweredSource!;assert(src.kind==='primary','primary fixture');
 primary.poweredSkipAdvance=false;src.targetUid=test.state.borgs[1]!.uid;
 src.pos={x:0,y:100,z:0};primary.pos={...src.pos};test.state.borgs[1]!.pos={x:0,y:100,z:250};
 test.state.projectiles=[primary];const splitCues:number[]=[];test.battle.onRomCue=c=>splitCues.push(c);
 const splitObs=test.battle.step(1/60,test.inputs);
 assert(splitObs.poweredLaunchFlashes.length===1&&splitObs.poweredLaunchFlashes[0]!.cause==='split','one flash per four-child split');
 assert(splitCues.filter(c=>c===255).length===1,'split source sound is255, not6');
 assert(!splitObs.projectiles.some(p=>p.uid===primary.uid),'split primary removed while flash survives');
 const unrelated=spawnPoweredSource(test.state.borgs[1]!,test.driver.actor,0x8016d584,0,[],()=>{throw new Error('unrelated flash');});
 assert(unrelated===null,'unrelated borg presentation unchanged');
}
