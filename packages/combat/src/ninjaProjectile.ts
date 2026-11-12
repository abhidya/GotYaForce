/** Normal Ninja/Sasuke715f8 ->7db5c rows0/3 ->85e00 row0.
 * Source phases and identities are separate from this bounded host adapter:
 * static joint11 bind, target roots, swept spheres and triangle terrain are not
 * original animated HIT/attachment parity. Incoming833a4/833ec/83610/83714
 * influences remain unbound, rather than being replaced by generic gravity. */
import type {BorgRuntime,Projectile} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import type {DamageRecord} from './gauges.js';
import {getNinjaXState,isSourceNinjaX} from './ninjaX.js';
import {livingAttackTarget,actorAimTarget} from './sourceAttackTarget.js';
import {attackHitRecordsForKind} from './attackHitData.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {stepGatlingExplosion,type GatlingExplosionState} from './gatlingProjectile.js';
import {createNinjaShurikenFlight,stepNinjaShurikenFlight,type NinjaShurikenFlightState} from './ninjaShurikenFlight.js';
export interface NinjaPrimarySource {
  kind:'primary';flight:NinjaShurikenFlightState;ownerBorgId:string;ownerFormId:string;
  hitUids:string[];contactPending:boolean;
}
export interface NinjaImpactSource extends Omit<GatlingExplosionState,'kind'> {kind:'impact'}
export type NinjaSource=NinjaPrimarySource|NinjaImpactSource;
export const NINJA_PROJECTILE_SOURCE={spawner:0x8007db5c,hitKind:1,hitRecord:1,radius:10,
  // Fresh original static joint11 composition including local[55,0,0].
  muzzle:[116.06508512135164,118.12734573990589,-.000012228569289618463] as const} as const;
export const NINJA_IMPACT_DAMAGE:DamageRecord&{knockbackDirMode:number}={index:1,hpDamage:20,
  downGaugeDamage:100,balanceGaugeDamage:100,comboScoreValue:100,attackerHpCurveIndex:0,forceGaugeCurveIndex:0,
  hitStrength:0,impactEffectId:0,reactionFlags:2,reactionAnimVariant:4,knockbackDirMode:1,
  flagsA:0x20,flagsB:0,knockbackYawTrim:0,knockbackPitchTrim:56,rehitIntervalFrames:0};
const f=Math.fround;
export function ninjaMuzzle(pos:Vec3,yaw:number,scale:number):Vec3{
  const [x,y,z]=NINJA_PROJECTILE_SOURCE.muzzle,c=Math.cos(yaw),s=Math.sin(yaw);
  return {x:f(pos.x+(x*c+z*s)*scale),y:f(pos.y+y*scale),z:f(pos.z+(-x*s+z*c)*scale)};
}
let serial=0;
export function spawnNinjaSource(owner:BorgRuntime,actor:RomActor,address:number,row:number,all:readonly BorgRuntime[]):Projectile[]|null{
  if(!isSourceNinjaX(owner.borgId)||address!==0x8007db5c||row!==(owner.borgId==='pl000a'?3:0))return null;
  const state=getNinjaXState(actor);if(!state||actor.actionIndex!==2)return null;
  const target=actorAimTarget(state.targetUid?all.find(b=>b.uid===state.targetUid):null);
  const yaw=actor.heading*Math.PI*2/65536,scale=actor.modelScale;
  const flight=createNinjaShurikenFlight(row as 0|3,{origin:ninjaMuzzle(actor.pos,yaw,scale),yaw,
    ownerScale:scale,collisionScale:actor.collisionScale??scale,
    initialAimPoint:state.targetPoint,targetUid:target?.uid??null,targetPoint:target?.pos??null});
  const hit=attackHitRecordsForKind(owner.borgId,1)[0],record=hit&&familyDamageRecordForBorg(owner.borgId,hit.damageRecordIndex);
  if(!hit||!record)throw Error('Verified Ninja HIT1/family damage1 missing');
  return [{uid:`ninja-shuriken-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...flight.pos},vel:{...flight.velocity},
    damage:1,hitstun:0,knockback:1,damageRecord:record,homingTurn:0,homingTarget:null,
    aimedTargetUid:target?.uid??null,life:flight.life,hitRadius:10*flight.collisionScale,visualKind:'energy',romShotKind:1,
    sourceHitCollisionFlags:hit.collisionFlags,consumeOnHit:false,romScale:[0,0,0],
    ninjaSource:{kind:'primary',flight,ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId,hitUids:[],contactPending:false}}];
}
export function createNinjaImpact(parent:Projectile,pos:Vec3,scale:number):Projectile{
  const s:NinjaImpactSource={kind:'impact',phase:'expand',age:0,tailAge:0,ownerScale:scale,scale:f(.01)*scale,
    velocity:f(.1)*scale,alpha:1,hold:4,yaw:0,ringAge:0,ringScale:{x:scale,y:scale,z:scale},ringAlpha:1,hitUids:[]};
  return {uid:`ninja-impact-${++serial}`,ownerUid:parent.ownerUid,team:parent.team,pos:{...pos},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord:NINJA_IMPACT_DAMAGE,homingTurn:0,homingTarget:null,
    aimedTargetUid:parent.aimedTargetUid??null,life:48,hitRadius:310*s.scale,visualKind:'energy',romShotKind:3,
    sourceHitCollisionFlags:1,consumeOnHit:false,romScale:[s.scale,s.scale,s.scale],ninjaSource:s};
}
export interface NinjaProjectileContext {
  terrainImpact?:(from:Vec3,to:Vec3)=>Vec3|null;outsideBounds?:(pos:Vec3)=>boolean;onCue?:(cue:number)=>void;
}
export function advanceNinjaSource(pr:Projectile,byUid:Map<string,BorgRuntime>,ctx:NinjaProjectileContext={}):Projectile[]{
  const s=pr.ninjaSource!;
  if(s.kind==='impact'){
    const clock:GatlingExplosionState={...s,kind:'explosion'};
    if(!stepGatlingExplosion(clock)){pr.despawnReason='expired';return [];}
    const {kind:_,...next}=clock;void _;Object.assign(s,next);
    pr.hitRadius=310*s.scale;pr.romScale=[s.scale,s.scale,s.scale];pr.life--;return [pr];
  }
  const owner=byUid.get(pr.ownerUid),target=actorAimTarget(s.flight.targetUid?byUid.get(s.flight.targetUid):null);
  const invalid=!livingAttackTarget(owner)?'owner-dead':owner.borgId!==s.ownerBorgId||
    (owner.combatFormId??owner.borgId)!==s.ownerFormId?'owner-changed':undefined;
  const result=stepNinjaShurikenFlight(s.flight,{
    ...(invalid?{ownerInvalid:invalid}:{}),priorContact:s.contactPending,
    currentTarget:target?{uid:target.uid,point:target.pos,valid:true}:null,
    ...(owner?{initPose:()=>({origin:ninjaMuzzle(owner.pos,owner.rotY,s.flight.ownerScale),yaw:owner.rotY,
      initialAimEnabled:!!target})}:{}),
    ...(ctx.outsideBounds?{outsideBounds:ctx.outsideBounds}:{}),
    terrain84170:state=>ctx.terrainImpact?.(state.previousPos,state.pos)??null,
  });
  s.flight=result.state;s.contactPending=false;
  const children:Projectile[]=[];
  for(const e of result.events)if(e.kind==='impact'){children.push(createNinjaImpact(pr,e.pos,result.state.modelScale));ctx.onCue?.(12);}
  const state=result.state;
  pr.pos={...state.pos};pr.vel={...state.velocity};pr.life=state.life;pr.hitRadius=10*state.collisionScale;
  pr.romScale=[state.visualScale,state.visualScale,state.visualScale];
  if(state.phase==='freed'){pr.despawnReason=state.reason==='owner-dead'||state.reason==='owner-changed'?'owner-dead':'expired';return children;}
  return [pr,...children];
}
