/** Scoped BLACK18ee30 ->16cc24(row0x10), not a held beam. Original child
 * phase/timeline/HIT gates are separate from static joint12 and host sweep/
 * terrain geometry. The effect16 impact is an independent85e00 attack. */
import type {BorgRuntime,Projectile} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import type {DamageRecord} from './gauges.js';
import {getGBlackChargeState} from './gblackCharge.js';
import {attackHitRecordsForKind} from './attackHitData.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {actorAimTarget,livingAttackTarget} from './sourceAttackTarget.js';
import {stepGatlingExplosion,type GatlingExplosionState} from './gatlingProjectile.js';
export const GBLACK_CHARGE_CHILD={spawner:0x8016cc24,row:0x10,hitKind:28,hitRecord:37,
  radius:30,baseZ:43.37525939941406,launchDistance:10000,cone:Math.fround(Math.PI/4),
  joint:[70.31999206542969,166.96002197265625,0.00002288818348157698] as const,
  durations:[25,6,10] as const} as const;
export interface GBlackChargeSweepState {
  kind:'sweep';phase:'pending'|'active'|'retiring'|'freed';stage:0|1|2;subphase:0|1|2;
  age:number;duration:number;modelScale:number;collisionScale:number;ownerBorgId:string;ownerFormId:string;
  targetUid:string|null;target518:Vec3|null;origin:Vec3;direction:Vec3;pos:Vec3;start:Vec3;end:Vec3;
  visualScale:[number,number,number];collisionGate272:number;hitActive:boolean;hitUids:string[];
  contactPoint:Vec3|null;terrainImpact:boolean;
}
export interface GBlackChargeImpactState extends Omit<GatlingExplosionState,'kind'> {kind:'impact'}
export type GBlackChargeSource=GBlackChargeSweepState|GBlackChargeImpactState;
export interface GBlackChargeOwner {dt:number;modelScale:number;collisionScale:number;controlWord?:number;target518?:Vec3}
export const GBLACK_CHARGE_IMPACT_DAMAGE:DamageRecord & {knockbackDirMode:number}={index:23,
  hpDamage:20,downGaugeDamage:100,balanceGaugeDamage:100,comboScoreValue:100,
  attackerHpCurveIndex:0,forceGaugeCurveIndex:0,hitStrength:0,impactEffectId:0,
  reactionFlags:2,reactionAnimVariant:4,knockbackDirMode:1,flagsA:0x20,flagsB:0,
  knockbackYawTrim:0,knockbackPitchTrim:32,rehitIntervalFrames:0};
const f=Math.fround;
const along=(p:Vec3,d:Vec3,n:number):Vec3=>({x:p.x+d.x*n,y:p.y+d.y*n,z:p.z+d.z*n});
function attachment(owner:BorgRuntime,scale:number):Vec3 {
  const [x,y,z]=GBLACK_CHARGE_CHILD.joint,c=Math.cos(owner.rotY),s=Math.sin(owner.rotY);
  return {x:owner.pos.x+(x*c+z*s)*scale,y:owner.pos.y+y*scale,z:owner.pos.z+(-x*s+z*c)*scale};
}
function captureMatrix(s:GBlackChargeSweepState,owner:BorgRuntime,byUid:Map<string,BorgRuntime>,aim:boolean):void {
  s.origin=attachment(owner,s.modelScale);s.direction={x:Math.sin(owner.rotY),y:0,z:Math.cos(owner.rotY)};
  if(!aim)return;
  // Original16d060 reads the owner's saved518 even after target loss. The
  // root-position eligibility adapter may refresh this sample, never zero it
  // or reacquire a different target. Initial missing source cache stays unbound.
  const cached=owner.gblackChargeOwner?.target518;
  const target=actorAimTarget(s.targetUid?byUid.get(s.targetUid):null);
  if(cached)s.target518={...cached};else if(target)s.target518={...target.pos};
  if(!s.target518)return;
  const delta={x:s.target518.x-s.origin.x,y:s.target518.y-s.origin.y,z:s.target518.z-s.origin.z};
  const n=Math.hypot(delta.x,delta.y,delta.z);if(n===0)return;
  delta.x/=n;delta.y/=n;delta.z/=n;
  if(delta.x*s.direction.x+delta.y*s.direction.y+delta.z*s.direction.z>=Math.cos(GBLACK_CHARGE_CHILD.cone))s.direction=delta;
}
function visual(s:GBlackChargeSweepState):void {
  const a=s.age;let x:number,y:number,z:number;
  if(s.stage===0){x=a<=5?1-a*.1:.5*(1-Math.min(20,a-5)/20);y=z=x;}
  else if(s.stage===1){x=a<=5?1+(f(1.1)-1)*a/5:f(1.1)*(1-Math.min(1,a-5));y=z=x;}
  else {x=a<=2?1+(f(.1)-1)*a/2:f(.1)*(1-Math.min(8,a-2)/8);y=x;z=1;}
  s.visualScale=[x*s.modelScale,y*s.modelScale,z*s.modelScale];
}
let serial=0;
export function spawnGBlackChargeSource(owner:BorgRuntime,actor:RomActor,address:number,row:number):Projectile[]|null {
  if(owner.borgId!=='pl062a'||address!==GBLACK_CHARGE_CHILD.spawner||row!==0x10)return null;
  const admitted=getGBlackChargeState(actor);if(!admitted||actor.actionIndex!==3||actor.variantIndex!==0)return [];
  const pos={...actor.pos},hit=attackHitRecordsForKind(owner.borgId,28)[0],damageRecord=hit&&familyDamageRecordForBorg(owner.borgId,hit.damageRecordIndex);
  if(!hit||!damageRecord)throw Error('Verified BLACK HIT28 damage record missing');
  const s:GBlackChargeSweepState={kind:'sweep',phase:'pending',stage:0,subphase:0,age:0,duration:25,
    modelScale:actor.modelScale,collisionScale:actor.collisionScale??actor.modelScale,
    ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId,targetUid:admitted.targetUid,
    target518:(actor as RomActor&{lockTarget?:Vec3|null}).lockTarget
      ?{...(actor as RomActor&{lockTarget:Vec3}).lockTarget}:owner.gblackChargeOwner?.target518?{...owner.gblackChargeOwner.target518}:null,
    origin:{...pos},direction:{x:0,y:0,z:1},pos,start:{...pos},end:{...pos},visualScale:[0,0,0],
    collisionGate272:-1,hitActive:false,hitUids:[],contactPoint:null,terrainImpact:false};
  return [{uid:`gblack-charge-sweep-${++serial}`,ownerUid:owner.uid,team:owner.team,pos,vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord,homingTurn:0,homingTarget:null,life:0,
    aimedTargetUid:admitted.targetUid,hitRadius:30*s.collisionScale,visualKind:'energy',romShotKind:28,
    sourceHitCollisionFlags:hit.collisionFlags,consumeOnHit:false,romScale:[0,0,0],gblackChargeSource:s}];
}
function createImpact(parent:Projectile,pos:Vec3,modelScale:number):Projectile {
  const s:GBlackChargeImpactState={kind:'impact',phase:'expand',age:0,tailAge:0,ownerScale:modelScale,
    scale:f(.01)*modelScale,velocity:f(.1)*modelScale,alpha:1,hold:4,yaw:0,ringAge:0,
    ringScale:{x:modelScale,y:modelScale,z:modelScale},ringAlpha:1,hitUids:[]};
  return {uid:`gblack-charge-impact-${++serial}`,ownerUid:parent.ownerUid,team:parent.team,pos:{...pos},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord:GBLACK_CHARGE_IMPACT_DAMAGE,homingTurn:0,homingTarget:null,
    aimedTargetUid:parent.aimedTargetUid??null,life:48,hitRadius:310*s.scale,visualKind:'energy',romShotKind:110,
    sourceHitCollisionFlags:1,consumeOnHit:false,romScale:[s.scale,s.scale,s.scale],gblackChargeSource:s};
}
export interface GBlackChargeProjectileContext {
  /** Host triangle segment clips source84170; no exact source terrain normals claimed. */
  terrainImpact?:(start:Vec3,end:Vec3)=>Vec3|null;
  onCue?:(cue:number)=>void;
}
export function advanceGBlackChargeSource(pr:Projectile,byUid:Map<string,BorgRuntime>,ctx:GBlackChargeProjectileContext={}):Projectile[] {
  const s=pr.gblackChargeSource!;
  if(s.kind==='impact'){
    // Same85e00 row16 lifecycle constants as existing rows13/19, separate HIT/damage.
    const clock:GatlingExplosionState={...s,kind:'explosion'};
    if(!stepGatlingExplosion(clock)){pr.despawnReason='expired';return [];}
    const {kind:_kind,...next}=clock;void _kind;Object.assign(s,next);
    pr.hitRadius=310*s.scale;pr.romScale=[s.scale,s.scale,s.scale];pr.life--;return [pr];
  }
  const owner=byUid.get(pr.ownerUid);
  const invalid=!livingAttackTarget(owner)||owner.borgId!==s.ownerBorgId||(owner.combatFormId??owner.borgId)!==s.ownerFormId
    ||owner.sourceAmmoSlowImmune===true||((owner.gblackChargeOwner?.controlWord??0)&0x01000000)!==0;
  if(invalid&&(s.phase==='pending'||s.phase==='active')){s.phase='retiring';s.hitActive=false;}
  if(s.phase==='retiring'){s.phase='freed';pr.despawnReason=invalid?'owner-dead':'expired';return [pr];}
  if(s.phase==='freed')return [];
  const live=owner!;let children:Projectile[]=[];
  if(s.phase==='pending'){
    s.phase='active';captureMatrix(s,live,byUid,false);
    s.pos=along(s.origin,s.direction,GBLACK_CHARGE_CHILD.baseZ);s.start={...s.pos};s.end={...s.pos};visual(s);
  }else{
    s.age=f(s.age+(live.gblackChargeOwner?.dt??1));
    if(s.subphase===0){
      if(s.age>=s.duration){
        s.stage=(s.stage+1) as 1|2;s.age=0;s.duration=GBLACK_CHARGE_CHILD.durations[s.stage];
        if(s.stage===2){s.subphase=1;s.collisionGate272=0;s.hitActive=true;}
      }
      if(s.stage===0)captureMatrix(s,live,byUid,true);
      s.start={...s.pos};
      s.pos=along(s.origin,s.direction,GBLACK_CHARGE_CHILD.baseZ+(s.stage===2?GBLACK_CHARGE_CHILD.launchDistance:0));
      if(s.stage===2){const clipped=ctx.terrainImpact?.(s.start,s.pos);if(clipped){s.pos={...clipped};s.terrainImpact=true;}}
      s.end={...s.pos};
    }else if(s.subphase===1){
      // Next dispatch disables registered HIT before the collision pass, then
      // allocates independent effect16 on accepted object or terrain contact.
      s.subphase=2;s.hitActive=false; //8aff0 unregisters HIT;272 is not rewritten.
      if(s.contactPoint||s.terrainImpact){children=[createImpact(pr,s.contactPoint??s.pos,s.modelScale)];ctx.onCue?.(12);}
    }else if(s.age>=s.duration){s.phase='retiring';s.hitActive=false;}
    visual(s);
  }
  pr.pos={...s.pos};pr.vel={...s.direction};pr.romScale=[...s.visualScale];pr.hitRadius=30*s.collisionScale;
  return [pr,...children];
}
