/** Arrow Ninja/Shijima X: 800a2684/800a2850/800a2980 and type0 tether
 * 800a2d7c/800a3394. Numeric constants are original DOL values. Static host
 * attachment/root target centers, JS trig and swept hit volumes are approximations. */
import type { BorgRuntime, Projectile, PlayerInput } from './types.js';
import type { Vec3 } from '@gf/physics';
import type { RomActor } from './rom/actor.js';
import { actorAimTarget, livingAttackTarget } from './sourceAttackTarget.js';
import { activeSourceTarget } from './targetLock.js';
import { attackHitRecordsForKind } from './attackHitData.js';
import { familyDamageRecordForBorg } from './familyDamageData.js';
import { SHOT } from './constants.js';
import { tierSizeScale } from './timescale.js';
import captureMass from './data/arrowCaptureMass.json' with { type:'json' };
export const isArrowNinja = (id:string):boolean => id==='pl0002'||id==='pl000b';
export const ARROW_CONTRACT = Object.freeze({speed:55,life:600,turnDegrees:3,correctionInterval:2,
  detachDistance:100,spinBam:0xf000,model:12,tetherLife:1200,tetherLength:600,massLimit:50000});
export interface ArrowDrawBasis {right:Vec3;up:Vec3;forward:Vec3}
export type ArrowSourceState = {
  kind:'arrow'; row:0|1; ownerBorgId:string; targetUid:string|null; correctionTimer:number;
  spinBam:number; skipAdvance:boolean;
} | {kind:'tether'; ownerBorgId:string; targetUid:string; anchor:Vec3; endpoint:Vec3; drawBasis:ArrowDrawBasis; life:number; correction:Vec3|null};
let serial=0;
export function stepArrowInput(owner:BorgRuntime,held:boolean){
  const input=owner.arrowInput??={held:false,pressEdge:false,pending:false};
  input.pressEdge=held&&!input.held;input.held=held;input.pending=true;return input;
}
/** +749 = popcount(+5bc & 0xf0f00), not held duration or cumulative presses.
 * Same bounded browser-axis quantization as Beam's raw input adapter. */
export function stepArrowMashInput(owner:BorgRuntime,input:PlayerInput):void{
  const x=Math.trunc(Math.max(-1,Math.min(1,-input.moveX))*127);
  const y=Math.trunc(Math.max(-1,Math.min(1,input.moveZ))*127);
  const angle=Math.trunc(Math.fround(Math.fround(Math.atan2(y,x))*10430.3779296875))&0xffff;
  const octants=[2,10,8,9,1,5,4,6];
  const stick=x*x+y*y<900?0:octants[((angle+0x1000)>>13)&7]!;
  const buttons=(stick<<16)|(input.jump?0x100:0)|(input.attack?0x200:0)|(input.special?0x400:0)|(input.hyper?0x800:0);
  let edges=(buttons&~(owner.sourceArrowInputButtons??0))&0xf0f00,count=0;
  while(edges){edges&=edges-1;count++;}
  owner.sourceArrowInputButtons=buttons;owner.sourceArrowMash749=count;
}
export function captureArrowAttack(owner:BorgRuntime,actor:RomActor,all:readonly BorgRuntime[]):void{
  const target=actorAimTarget(activeSourceTarget(owner,all));
  owner.arrowAttack={targetUid:target?.uid??null,pos:{...(target?.pos??actor.pos)},trackingEnabled:owner.sourceArrowTrackingEnabled??(!!target&&Math.hypot(target.pos.x-actor.pos.x,target.pos.y-actor.pos.y,target.pos.z-actor.pos.z)<=5500)};
}
const magnitude=(v:Vec3)=>Math.hypot(v.x,v.y,v.z);
const sub=(a:Vec3,b:Vec3):Vec3=>({x:a.x-b.x,y:a.y-b.y,z:a.z-b.z});
const scale=(v:Vec3,n:number):Vec3=>({x:v.x*n,y:v.y*n,z:v.z*n});
/** Owner animated af0/b00/b10 is unavailable: explicit host attachment seam,
 * otherwise root center. Never pretend the generic B muzzle is source data. */
export function spawnArrowSource(owner:BorgRuntime,actor:RomActor,address:number,row:number,all:readonly BorgRuntime[]):Projectile[]|null{
  if(!isArrowNinja(owner.borgId)||actor.actionIndex!==2||address!==0x800a2684||(row!==0&&row!==1))return null;
  const hit=attackHitRecordsForKind(owner.borgId,0)[0];
  const record=hit&&familyDamageRecordForBorg(owner.borgId,hit.damageRecordIndex);
  if(!hit||!record)return [];
  const aim=owner.arrowAttack;
  const target=aim?.targetUid?all.find(b=>b.uid===aim.targetUid):null;
  const valid=livingAttackTarget(target);
  const pos={...(owner.sourceArrowAttachment??actor.pos)};
  const delta=valid?sub(aim?.pos??target.pos,pos):{x:0,y:0,z:0};
  const yaw=actor.heading*Math.PI/32768;
  const direction=magnitude(delta)>0?scale(delta,1/magnitude(delta)):{x:Math.sin(yaw),y:0,z:Math.cos(yaw)};
  const size=actor.modelScale*actor.sizeScale;
  return [{uid:`arrow-${++serial}`,ownerUid:owner.uid,team:owner.team,pos,vel:scale(direction,55),damage:1,
    hitstun:0,knockback:1,damageRecord:record,homingTurn:0,homingTarget:null,
    aimedTargetUid:valid?target.uid:null,life:600,hitRadius:Math.max(hit.radius,...hit.halfExtent)*size,
    visualKind:'energy',romShotKind:0,sourceHitCollisionFlags:hit.collisionFlags,romScale:[size,size,size],
    arrowSource:{kind:'arrow',row,ownerBorgId:owner.combatFormId??owner.borgId,targetUid:valid&&aim?.trackingEnabled?target.uid:null,
      correctionTimer:2,spinBam:0,skipAdvance:true}}];
}
function turn(velocity:Vec3,delta:Vec3):Vec3{
  const distance=magnitude(delta);if(distance<1e-12)return velocity;
  const a=scale(velocity,1/magnitude(velocity)),b=scale(delta,1/distance);
  const angle=Math.acos(Math.max(-1,Math.min(1,a.x*b.x+a.y*b.y+a.z*b.z)));
  const limit=3*Math.PI/180;if(angle<=limit)return scale(b,55);
  const sine=Math.sin(angle);
  if(Math.abs(sine)<1e-12)return {x:55*(a.x*Math.cos(limit)+a.z*Math.sin(limit)),y:55*a.y,
    z:55*(-a.x*Math.sin(limit)+a.z*Math.cos(limit))}; // source degenerate axis = world +Y
  const left=Math.sin(angle-limit)/sine,right=Math.sin(limit)/sine;
  return {x:55*(a.x*left+b.x*right),y:55*(a.y*left+b.y*right),z:55*(a.z*left+b.z*right)};
}
export function advanceArrowSource(pr:Projectile,byUid:Map<string,BorgRuntime>):Projectile[]{
  const s=pr.arrowSource!;const owner=byUid.get(pr.ownerUid);
  if(!livingAttackTarget(owner)||(owner.combatFormId??owner.borgId)!==s.ownerBorgId){pr.despawnReason='owner-dead';return [];}
  if(s.kind==='tether'){
    const target=byUid.get(s.targetUid);s.correction=null;
    if(!livingAttackTarget(target)||target.burstPaired||target.sourceFusionCarried||(target.sourceFusionRole??0)!==0||target.fusionState!==0||target.sourceArrowTetherBlocked){pr.despawnReason='expired';return [];}
    s.life-=1+3*(target.sourceArrowMash749??0);pr.life=s.life;
    if(s.life<=0){pr.despawnReason='expired';return [];}
    s.endpoint={...target.pos};
    s.drawBasis=arrowTetherBasis(sub(s.endpoint,s.anchor),s.drawBasis.up);
    const delta=sub(s.anchor,s.endpoint),distance=magnitude(delta);
    if(distance>600)s.correction=scale(delta,(distance-600)/distance);
    return [pr];
  }
  if(s.skipAdvance){s.skipAdvance=false;return [pr];}
  if(--pr.life<=0){pr.despawnReason='expired';return [];}
  s.spinBam=(s.spinBam+0xf000)&0xffff;
  const target=s.targetUid?byUid.get(s.targetUid):undefined;
  if(!livingAttackTarget(target)||magnitude(sub(target.pos,pr.pos))-SHOT.TARGET_BODY_RADIUS*tierSizeScale(target)<=100)s.targetUid=null;
  if(s.targetUid&&target&&--s.correctionTimer<=0){s.correctionTimer=2;pr.vel=turn(pr.vel,sub(target.pos,pr.pos));}
  pr.pos={x:pr.pos.x+pr.vel.x,y:pr.pos.y+pr.vel.y,z:pr.pos.z+pr.vel.z};return [pr];
}
/** 80053b30: base mass >=50000 is unscaled. Mounted passenger totals remain
 * an explicit sourceArrowMass204 override until ride chains are represented. */
export function arrowCaptureMass(target:BorgRuntime):number{
  if(target.sourceArrowMass204!==undefined)return target.sourceArrowMass204;
  const base=(captureMass.borgs as Record<string,number>)[target.combatFormId??target.borgId];
  if(base===undefined)return Infinity; // unknown descriptors cannot silently gain capture eligibility
  return base>=50000?base:base*tierSizeScale(target);
}
export function createArrowTether(pr:Projectile,target:BorgRuntime,owner?:BorgRuntime):Projectile|null{
  if(pr.arrowSource?.kind!=='arrow'||(target.targetEligibility83??0)!==0||arrowCaptureMass(target)>=50000)return null;
  // Init immediately dispatches type0 update; known capture-break states never survive it.
  if(!livingAttackTarget(target)||target.burstPaired||target.sourceFusionCarried||(target.sourceFusionRole??0)!==0||target.fusionState!==0||target.sourceArrowTetherBlocked)return null;
  const life=1200-1-3*(target.sourceArrowMash749??0);if(life<=0)return null;
  const anchor={...target.pos};
  const size=owner?tierSizeScale(owner):pr.romScale?.[0]??1;
  return {...pr,uid:`arrow-tether-${++serial}`,pos:{...anchor},vel:{x:0,y:0,z:0},life,hitRadius:0,romScale:[size,size,size],
    arrowSource:{kind:'tether',ownerBorgId:pr.arrowSource.ownerBorgId,targetUid:target.uid,anchor,endpoint:{...anchor},drawBasis:{right:{x:1,y:0,z:0},up:{x:0,y:1,z:0},forward:{x:0,y:0,z:1}},life,correction:null}};
}
/** 80084498 averages all nonzero submissions for the next actor update, not sequential clamps. */
export function applyArrowTetherCorrections(projectiles:readonly Projectile[],byUid:Map<string,BorgRuntime>):void{
  const sums=new Map<string,{v:Vec3;n:number}>();
  for(const pr of projectiles){const s=pr.arrowSource;if(s?.kind!=='tether'||!s.correction)continue;
    const sum=sums.get(s.targetUid)??{v:{x:0,y:0,z:0},n:0};
    sum.v.x+=s.correction.x;sum.v.y+=s.correction.y;sum.v.z+=s.correction.z;sum.n++;sums.set(s.targetUid,sum);}
  for(const [uid,{v,n}] of sums){const target=byUid.get(uid);if(target)target.sourceArrowPendingCorrection=scale(v,1/n);}
}

/** Apply queued source correction after the victim's next actor update, with the
 * floor sampled BEFORE displacement. Host ground query replaces the source collision helper. */
export function applyPendingArrowCorrection(target:BorgRuntime,groundY:number):void{
  const correction=target.sourceArrowPendingCorrection;delete target.sourceArrowPendingCorrection;
  if(!correction||!livingAttackTarget(target)||target.sourceArrowTetherBlocked)return;
  target.pos={x:target.pos.x+correction.x,y:Math.max(groundY,target.pos.y+correction.y),z:target.pos.z+correction.z};
}

const cross=(a:Vec3,b:Vec3):Vec3=>({x:a.y*b.z-a.z*b.y,y:a.z*b.x-a.x*b.z,z:a.x*b.y-a.y*b.x});
/** Direction mode5 (800463ac): transported reference-up, not renderer world-up.
 * The parallel-axis fallback is a bounded host safeguard pending full matrix fallback parity. */
export function arrowTetherBasis(direction:Vec3,reference:Vec3):ArrowDrawBasis{
  const length=magnitude(direction);if(length<=.001)return {right:{x:1,y:0,z:0},up:{x:0,y:1,z:0},forward:{x:0,y:0,z:1}};
  const forward=scale(direction,1/length);
  let right=cross(reference,forward);
  if(magnitude(right)<1e-12)right=cross(Math.abs(forward.y)<.9?{x:0,y:1,z:0}:{x:1,y:0,z:0},forward);
  right=scale(right,1/magnitude(right));
  const up=cross(forward,right);return {right,up:scale(up,1/magnitude(up)),forward};
}
