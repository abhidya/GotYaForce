import {createRomActor} from './rom/actor.js';
import {prepareGBlackCharge,clearGBlackCharge} from './gblackCharge.js';
import {spawnGBlackChargeSource,advanceGBlackChargeSource,GBLACK_CHARGE_CHILD,type GBlackChargeSweepState} from './gblackChargeProjectile.js';
import type {BorgRuntime,Projectile} from './types.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[gblackChargeProjectile] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<1e-5,`${msg}: ${a} != ${b}`);}
function fixture(scale=1){
 const actor=createRomActor();actor.borgNumber=0x62a;actor.actionIndex=3;actor.variantIndex=0;
 actor.modelScale=scale;actor.collisionScale=scale;prepareGBlackCharge(actor,null);
 // Minimal pure-adapter owner. Real combat/input routing is independently tested
 // in gblackChargeBattle; no target/bone/physics fidelity is inferred here.
 const owner={uid:'owner',borgId:'pl062a',team:0,alive:true,hp:100,state:'idle',pos:{x:0,y:0,z:0},rotY:0,
  gblackChargeOwner:{dt:1,modelScale:scale,collisionScale:scale}} as unknown as BorgRuntime;
 const byUid=new Map([[owner.uid,owner]]);
 const pr=spawnGBlackChargeSource(owner,actor,0x8016cc24,0x10)![0]!;
 const s=pr.gblackChargeSource as GBlackChargeSweepState;
 const tick=()=>advanceGBlackChargeSource(pr,byUid);
 return {actor,owner,byUid,pr,s,tick};
}
export function runGBlackChargeProjectileSelfTest():void{
 for(const scale of [1,2]){
  const t=fixture(scale);
  assert(t.s.phase==='pending'&&!t.s.hitActive,'allocation does not damage');t.tick();
  assert(String(t.s.phase)==='active'&&t.s.age===0&&t.s.stage===0&&!t.s.hitActive,'initialization is separate from age advance');
  near(t.s.origin.x,GBLACK_CHARGE_CHILD.joint[0]*scale,'static joint translation scales');
  near(t.s.pos.z-t.s.origin.z,GBLACK_CHARGE_CHILD.baseZ,'normalized base distance does not scale');
  near(t.pr.hitRadius,30*scale,'collision radius uses separate c0 scale');
  clearGBlackCharge(t.actor);
  for(let i=1;i<=24;i++){t.tick();assert(t.s.stage===0&&!t.s.hitActive,'stage0 windup is non-damaging even without actor state');}
  t.tick();assert(Number(t.s.stage)===1&&t.s.age===0&&!t.s.hitActive,'25th age enters stage1/reset');
  const origin={...t.s.origin},direction={...t.s.direction};t.owner.pos.x+=200;t.owner.rotY=Math.PI/2;
  for(let i=0;i<5;i++){t.tick();assert(Number(t.s.stage)===1&&!t.s.hitActive,'six-update stage1 delay');}
  t.tick();assert(Number(t.s.stage)===2&&t.s.age===0&&t.s.hitActive&&t.s.collisionGate272===0,'launch admits one attack pass');
  assert(JSON.stringify(t.s.origin)===JSON.stringify(origin)&&JSON.stringify(t.s.direction)===JSON.stringify(direction),'matrix freezes after stage0');
  near(Math.hypot(t.s.end.x-t.s.start.x,t.s.end.y-t.s.start.y,t.s.end.z-t.s.start.z),10000,'unscaled launch distance');
  assert(t.tick().length===1&&!t.s.hitActive,'whiff disables hit next update without impact');
  for(let i=0;i<12;i++)t.tick();assert(String(t.s.phase)==='freed','tail retires and frees');
 }
 {
  const t=fixture();t.tick();for(let i=0;i<31;i++)t.tick();
  assert(t.s.hitActive,'accepted-contact fixture starts on active pass');
  t.s.hitUids.push('victim');t.s.contactPoint={x:10,y:20,z:30};
  const out=t.tick(),impact=out.find(p=>p.gblackChargeSource?.kind==='impact')!;
  assert(out.length===2&&impact&&impact.uid!==t.pr.uid,'independent impact identity emitted once');
  assert(impact.damageRecord?.hpDamage===20&&t.pr.damageRecord?.hpDamage===30,'source parent and impact records stay distinct');
  assert(impact.gblackChargeSource?.hitUids.length===0,'impact does not inherit parent hit history');
  assert(JSON.stringify(impact.pos)===JSON.stringify(t.s.contactPoint),'impact uses accepted contact fixture point');
  assert(t.tick().length===1,'later parent updates cannot reallocate impact');
  let p:Projectile|undefined=impact;for(let i=0;i<80&&p;i++)p=advanceGBlackChargeSource(p,t.byUid)[0];
  assert(!p,'independent expansion/tail eventually retires');
 }
 {
  const t=fixture();t.owner.hp=0;const out=t.tick();
  assert(!t.s.hitActive&&String(t.s.phase)==='freed'&&!out.some(p=>p.gblackChargeSource?.kind==='impact'),'dead owner cannot launch or fabricate impact');
  assert(t.tick().length===0,'freed child is gone next pass');
 }
 {
  const t=fixture();t.tick();for(let i=0;i<30;i++)t.tick();
  const clipped={x:0,y:100,z:400};
  advanceGBlackChargeSource(t.pr,t.byUid,{terrainImpact:()=>clipped});
  assert(t.s.hitActive&&t.s.terrainImpact&&JSON.stringify(t.s.end)===JSON.stringify(clipped),'terrain clip bounds active sweep');
  const effect=t.tick().find(p=>p.gblackChargeSource?.kind==='impact');
  assert(effect&&JSON.stringify(effect.pos)===JSON.stringify(clipped),'terrain-only contact creates separate impact');
 }
 {
  const t=fixture();t.owner.gblackChargeOwner!.controlWord=0x01000000;
  t.tick();assert(!t.s.hitActive&&String(t.s.phase)==='freed','exact owner control bit invalidates before launch');
 }
 {
  const t=fixture();t.owner.gblackChargeOwner!.target518={x:250,y:200,z:1000};
  t.tick();t.tick();const point={...t.s.target518!},direction={...t.s.direction};
  assert(direction.x>0.1,'non-forward target fixture exercises cone correction');
  delete t.owner.gblackChargeOwner!.target518;t.s.targetUid='lost';
  t.tick();assert(JSON.stringify(t.s.target518)===JSON.stringify(point),'missing target retains last518 point');
  near(t.s.direction.x,direction.x,'retained point continues aim rather than forward reset');
 }
 console.log('[gblackChargeProjectile] PASS: staged single sweep, scaled attachment/unscaled ray, independent impact, whiff/death/terrain');
}
