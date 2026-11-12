import { spawnPoweredSource } from "./poweredProjectileRuntime.js";
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
export function runPoweredChargeSelfTest():void {
 runFlightTests();
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
 const spawn=driver.ctx.onFamilyProjectile!;
 driver.ctx.onFamilyProjectile=(a,addr,row)=>{events.push({addr,row});spawn(a,addr,row);};
 const alloc=driver.ctx.onAllocateResource!;
 driver.ctx.onAllocateResource=(a,slot,count,mode)=>{allocations++;return alloc(a,slot,count,mode);};
 owner.weaponCells![1]!.cur=ammo;
 inputs.p1.special=true;
 for(let i=0;i<189;i++)battle.step(1/60,inputs);
 assert(Number(owner.poweredCharge!.charge)===179&&Number(events.length)===0,'actual below threshold/no held fire');
 battle.step(1/60,inputs);assert(owner.poweredCharge!.ready,'actual frame190 ready');
 owner.weaponCells![1]!.cur=ammo;
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(owner.command?.type===5&&owner.command.actionIndex===3&&owner.command.recordAddress==='0x8034ead0','exact source command');
 assert(driver.actor.actionIndex===3,'bridge action3');
 assert(Number(owner.poweredCharge!.charge)===0,'live commit reset');
 for(let i=0;i<90&&Number(events.length)===0;i++)battle.step(1/60,inputs);
 assert(events.map(e=>e.row).join(',')==='8,9,6,7,6',`four source rows/effect: ${JSON.stringify(events)}`);
 assert(allocations===0,'no charged ammo allocation');
 const primaries=state.projectiles.filter(p=>p.poweredSource?.kind==='primary');
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
 driver.interrupt();owner.state='idle';owner.anim='idle';owner.cooldowns['special']=0;
 events.length=0;inputs.p1.special=true;
 for(let i=0;i<190;i++)battle.step(1/60,inputs);
 assert(Number(events.length)===0,'repeat hold never auto-fires');
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(Number(events.length)===0&&driver.actor.contactP1===0,'repeat resets part0 aux gate');
 for(let i=0;i<15;i++) { battle.step(1/60,inputs); assert(Number(events.length)===0,'repeat may not fire before authored frame16'); }
 for(let i=0;i<30&&Number(events.length)===0;i++)battle.step(1/60,inputs);
 assert(Number(events.length)===5,'repeat release starts fresh four-shot source volley');
 }
 {
 const {battle,inputs,owner,driver}=setup();let shots=0;
 const spawn=driver.ctx.onFamilyProjectile!;driver.ctx.onFamilyProjectile=(a,addr,row)=>{shots++;spawn(a,addr,row);};
 inputs.p1.special=true;for(let i=0;i<90;i++)battle.step(1/60,inputs);
 inputs.p1.special=false;battle.step(1/60,inputs);
 assert(owner.command?.type!==5&&shots===0,'old90-frame threshold cannot activate source action3');
 assert(Number(owner.poweredCharge!.charge)===78,'underready residual preserved');
 }
 {
 const {battle,inputs,state,owner,driver}=setup();let shots=0;
 const spawn=driver.ctx.onFamilyProjectile!;driver.ctx.onFamilyProjectile=(a,addr,row)=>{shots++;spawn(a,addr,row);};
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
 console.log('Powered charged-X integration: passed');
}
