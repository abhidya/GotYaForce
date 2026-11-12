import {createRomActor} from './rom/actor.js';
import type {BorgRuntime} from './types.js';
import {prepareNinjaX,clearNinjaX} from './ninjaX.js';
import {spawnNinjaSource,advanceNinjaSource,ninjaMuzzle,createNinjaImpact} from './ninjaProjectile.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[ninjaProjectile] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<1e-5,`${msg}: ${a} != ${b}`);}
function fixture(id='pl0000'){
 const owner={uid:'owner',borgId:id,team:0,alive:true,hp:100,state:'idle',pos:{x:10,y:300,z:20},rotY:.3} as BorgRuntime;
 const target={uid:'target',borgId:'pl0615',team:1,alive:true,hp:100,state:'idle',pos:{x:10,y:300,z:2020},rotY:0} as BorgRuntime;
 const actor=createRomActor();actor.actionIndex=2;actor.borgNumber=id==='pl0000'?0:10;actor.pos={...owner.pos};actor.heading=0;
 actor.modelScale=2;actor.collisionScale=.5;prepareNinjaX(actor,target.uid,target.pos);
 const pr=spawnNinjaSource(owner,actor,0x8007db5c,id==='pl0000'?0:3,[owner,target])![0]!;
 return {owner,target,actor,pr,map:new Map([[owner.uid,owner],[target.uid,target]])};
}
export function runNinjaProjectileSelfTest():void{
 for(const id of ['pl0000','pl000a']){
  const {owner,target,actor,pr,map}=fixture(id);assert(pr.ninjaSource?.kind==='primary','dedicated source allocation');const s=pr.ninjaSource;
  assert(s.flight.phase==='pending'&&pr.damageRecord?.hpDamage===10&&pr.damageRecord.flagsA===0,'pending and exact family damage1');
  near(pr.hitRadius,5,'radius10 uses independent inheritedc0');
  const saved={...s.flight.initialAimPoint!};target.pos.z+=300;owner.pos.x+=10;
  advanceNinjaSource(pr,map);assert(String(s.flight.phase)==='active'&&s.flight.life===599&&s.flight.hitActive,'same-pass init and active');
  assert(JSON.stringify(s.flight.initialAimPoint)===JSON.stringify(saved),'allocation-saved aim is not replaced during init');
  const origin=ninjaMuzzle(owner.pos,owner.rotY,2);
  near(s.flight.previousPos.x,origin.x,'init recomputes current static attachment');near(s.flight.visualScale,4,'draw2 is separate fromHITc0');
  clearNinjaX(actor);advanceNinjaSource(pr,map);assert(String(s.flight.phase)==='active','owner action completion does not destroy independent child');
  s.hitUids.push('old-victim');s.contactPending=true;const contactPos={...pr.pos};const out=advanceNinjaSource(pr,map);
  const impact=out.find(p=>p.ninjaSource?.kind==='impact');assert(impact&&impact.ninjaSource?.kind==='impact','contact emits separate row0 impact');
  assert(impact.uid!==pr.uid&&impact.ninjaSource.hitUids.length===0&&impact.romShotKind===3&&impact.damageRecord?.hpDamage===20&&impact.damageRecord.flagsA===32,'separate HIT3/globaldamage1 identity');
  assert(JSON.stringify(impact.pos)===JSON.stringify(contactPos)&&!s.flight.hitActive,'contact retires before movement');
  owner.alive=false;advanceNinjaSource(impact,map);assert(impact.ninjaSource.age===1,'impact survives owner death');
  const direct=createNinjaImpact(pr,contactPos,1),d=direct.ninjaSource;assert(d?.kind==='impact','impact fixture');
  for(let i=0;i<13;i++)advanceNinjaSource(direct,map);near(d.scale,1.25,'13 expansion updates to source maximum');
  for(let i=0;i<3;i++)advanceNinjaSource(direct,map);assert(d.phase==='hold','three subsequent hold passes collide');
  advanceNinjaSource(direct,map);assert(String(d.phase)==='tail','fourth hold update disables HIT in collision adapter');
  for(let i=0;i<30;i++)assert(advanceNinjaSource(direct,map).length===1,'30 tail passes retained');
  assert(advanceNinjaSource(direct,map).length===0,'next tail dispatch frees');
 }
 {
  const {owner,pr,map}=fixture();owner.alive=false;let out=advanceNinjaSource(pr,map);
  assert(pr.ninjaSource?.kind==='primary'&&pr.ninjaSource.flight.phase==='released'&&!pr.ninjaSource.flight.visible&&out.length===1,'owner invalidation same-dispatch release without impact');
  assert(advanceNinjaSource(pr,map).length===0&&pr.despawnReason==='owner-dead','next dispatch frees');
 }
 {
  const {pr,map}=fixture();const out=advanceNinjaSource(pr,map,{terrainImpact:(_a,b)=>({...b,y:0})});
  assert(pr.ninjaSource?.kind==='primary'&&pr.ninjaSource.flight.reason==='terrain'&&pr.ninjaSource.flight.hitActive,'terrain impact preserves original one-pass HIT until retirement');
  assert(out.some(p=>p.ninjaSource?.kind==='impact'),'terrain impact emits row0');advanceNinjaSource(pr,map);
  assert(!pr.ninjaSource.flight.hitActive,'next dispatch unregisters terrain-retired HIT');
 }
 {
  const {pr,map}=fixture();const out=advanceNinjaSource(pr,map,{outsideBounds:()=>true});
  assert(out.length===1&&pr.ninjaSource?.kind==='primary'&&pr.ninjaSource.flight.reason==='bounds','bounds never emits damaging impact');
 }
 console.log('[ninjaProjectile] PASS: static attachment, allocation snapshots, independent scales, lifecycle, impact identity and owner isolation');
}
