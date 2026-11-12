import {getGRedAirShotState} from './gredAirShot.js';
import {getGRedShotState} from './gredShot.js';
/** Scoped 800c3be0 normal shots: RED43, NEO101, BLACK102. Actor fire timing is
 * owned separately by the admitted source action or legacy variant route. Original joint7 bind data supplies a static attachment,
 * not animated pose parity. Target roots, sphere sweeps and terrain are host seams. */
import type {BorgRuntime,Projectile} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import {activeSourceTarget} from './targetLock.js';
import {livingAttackTarget} from './sourceAttackTarget.js';
import {attackHitRecordsForKind} from './attackHitData.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {SHOT} from './constants.js';
import {createGredRangedFlight,stepGredRangedFlight,GRED_RANGED_FLIGHT_CONSTANTS,
  type GredRangedFlightState,type GredRangedFlightContext,type GredRangedRow} from './gredRangedFlight.js';
export const GRED_RANGED_SOURCE={spawner:0x800c3be0,joint:7,hitKind:0,hitRecord:15,
  jointBind:[-106.55999755859375,166.96005249023438,0.000041961669921875] as const,
  captureRange:7000} as const;
export interface GredRangedSource {
  row:GredRangedRow;flight:GredRangedFlightState;ownerBorgId:string;ownerFormId:string;
  /** Scoped 6ae60/6bf80 capture; root centers and spawn-time snapshot are approximations. */
  captureFlags:number;ownerVisibilityBit:number;targetUid:string|null;hitUids:string[];contactPending:number;
}
const f=Math.fround;
const rowFor=(borgId:string):GredRangedRow|null=>borgId==='pl0615'?43:borgId==='pl0629'?101:borgId==='pl062a'?102:null;
function attachment(owner:BorgRuntime,row:GredRangedRow,scale:number):Vec3 {
  const [bx,by,bz]=GRED_RANGED_SOURCE.jointBind;
  const x=f(bx+(row===101?-196.8000030517578:-106.80000305175781));
  const y=f(by-3.5999999046325684),z=f(bz+30),c=Math.cos(owner.rotY),s=Math.sin(owner.rotY);
  return {x:f(owner.pos.x+(x*c+z*s)*scale),y:f(owner.pos.y+y*scale),z:f(owner.pos.z+(-x*s+z*c)*scale)};
}
function launch(owner:BorgRuntime,row:GredRangedRow,scale:number,target:BorgRuntime|null,flags:number){
  const origin=attachment(owner,row,scale);
  const delta=target?{x:target.pos.x-origin.x,y:target.pos.y-origin.y,z:target.pos.z-origin.z}:null;
  const n=delta?Math.hypot(delta.x,delta.y,delta.z):0;
  const direction=delta&&n>0?{x:delta.x/n,y:delta.y/n,z:delta.z/n}:{x:Math.sin(owner.rotY),y:0,z:Math.cos(owner.rotY)};
  return {origin,direction,ownerModelScale:scale,targetPoint:target&&(flags&4)!==0?{...target.pos}:null};
}
/** Original6a104 fresh-command visibility writes, before cue and ammo checks.
 * Deliberately unlike6bf80: initial admission does not test target control high bit.
 * Called only for the scoped ordinary G RED-family route, not generic dispatch. */
export function prepareGredRangedEntryVisibility(actor:RomActor,captureBlocked6b8=false):void {
  const bit=actor.visibilityBit&0xff;
  for(const target of actor.visibilityRoster.slice(0,6))target.visibilityMask5e6&=~bit;
  const target=captureBlocked6b8?null:actor.visibilityTarget;
  if(target&&target.eligibility83===0)target.visibilityMask5e6|=bit;
}
let serial=0;
export function spawnGredRangedSource(owner:BorgRuntime,actor:RomActor,address:number,row:number,all:readonly BorgRuntime[]):Projectile[]|null {
  const expected=rowFor(owner.borgId);
  if(expected===null||address!==GRED_RANGED_SOURCE.spawner||row!==expected||actor.actionIndex!==0)return null;
  const hit=attackHitRecordsForKind(owner.borgId,0)[0];
  const record=hit&&familyDamageRecordForBorg(owner.borgId,hit.damageRecordIndex);
  if(!hit||!record)throw Error('Verified G RED normal-shot HIT0/record15 missing');
  // 6bda8 clears captured c8/cc/d0 when6b8 is nonzero. The optional byte is an
  // explicit seam: generic host actor admission does not reproduce every writer.
  const shot=getGRedAirShotState(actor)??getGRedShotState(actor);
  // Admitted source shots capture identity at6a104 and refresh only
  // at repeat6bf80. Legacy variants retain the prior spawn-time snapshot seam.
  const captured=shot?all.find(t=>t.uid===shot.targetUid):undefined;
  const target=owner.sourceGredRangedCaptureBlocked6b8?null:shot?
    (livingAttackTarget(captured)?captured:null):activeSourceTarget(owner,all);
  const captureFlags=target?1|(target.team!==owner.team?2:0)|
    (Math.hypot(target.pos.x-actor.pos.x,target.pos.y-actor.pos.y,target.pos.z-actor.pos.z)<=7000?4:0):0;
  const pose=launch(owner,expected,actor.modelScale,target,captureFlags);
  const flight=createGredRangedFlight(expected,pose.origin,pose.direction,actor.modelScale,pose.targetPoint);
  const source:GredRangedSource={row:expected,flight,ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId,
    captureFlags,ownerVisibilityBit:actor.visibilityBit,targetUid:target?.uid??null,hitUids:[],contactPending:0};
  return [{uid:`gred-ranged-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...pose.origin},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord:record,homingTurn:0,homingTarget:null,
    aimedTargetUid:target?.uid??null,life:300,hitRadius:0,visualKind:'energy',romShotKind:0,
    sourceHitCollisionFlags:hit.collisionFlags,consumeOnHit:false,romScale:[0,0,0],gredRangedSource:source}];
}
export interface GredRangedProjectileContext {
  terrainImpact?:(start:Vec3,end:Vec3)=>Vec3|null;
  outsideBounds?:(pos:Vec3)=>boolean;
  onCue?:(cue:number)=>void;
}
export function advanceGredRangedSource(pr:Projectile,byUid:Map<string,BorgRuntime>,ctx:GredRangedProjectileContext={}):Projectile[] {
  const source=pr.gredRangedSource!,owner=byUid.get(pr.ownerUid);
  const target=source.targetUid?byUid.get(source.targetUid):undefined;
  const valid=livingAttackTarget(target);
  const ownerInvalid=!livingAttackTarget(owner)?'owner-dead':owner.borgId!==source.ownerBorgId||
    (owner.combatFormId??owner.borgId)!==source.ownerFormId?'owner-changed':undefined;
  const input:GredRangedFlightContext={
    ...(ownerInvalid?{ownerInvalid}:{}),priorContactBits:source.contactPending,
    ...(valid?{targetPoint:{...target.pos}}:{}),
    // 83874 includes shape-dependent target-volume penetration. This bounded
    // root/body-radius check is not an original animated HIT-pair calculation.
    validateTarget:s=>valid&&Math.hypot(target.pos.x-s.pos.x,target.pos.y-s.pos.y,target.pos.z-s.pos.z)>SHOT.TARGET_BODY_RADIUS,
    terrain84170:s=>{const hit=ctx.terrainImpact?.(s.previousPos,s.pos);if(!hit)return false;s.pos={...hit};return true;},
    ...(ctx.outsideBounds?{outsideBounds:ctx.outsideBounds}:{}),
    // Incoming834b0/83524 modifiers and83714 attraction are deliberately unbound.
  };
  if(owner&&source.flight.phase==='pending'){
    // Source6ec84 runs before83e64: invalid visibility clears captured c8 and
    // initial aim falls back to owner forward, even with a living selected target.
    const eligible=valid&&((target.targetEligibility83??0)!==0||
      (((target.targetVisibilityMask5e6??0)&source.ownerVisibilityBit)!==0));
    if(!eligible)source.targetUid=null;
    input.initPose=()=>launch(owner,source.row,source.flight.ownerModelScale,eligible?target:null,source.captureFlags);
  }
  const result=stepGredRangedFlight(source.flight,input);source.flight=result.state;source.contactPending=0;
  if(result.state.phase!=='pending'&&!result.state.targetPoint)source.targetUid=null;
  for(const event of result.events)if(event.kind==='initialized')ctx.onCue?.(event.sound);
  const s=result.state;
  pr.pos={...s.pos};pr.vel={...s.velocity};pr.life=s.life;pr.hitRadius=GRED_RANGED_FLIGHT_CONSTANTS.hitRadius*s.collisionScale;
  pr.romScale=[s.visualScale.x,s.visualScale.y,s.visualScale.z];
  if(s.phase==='freed'){pr.despawnReason=s.reason==='owner-dead'||s.reason==='owner-changed'?'owner-dead':'expired';return [];}
  return [pr];
}
