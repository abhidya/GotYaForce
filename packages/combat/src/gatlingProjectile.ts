/** Gatling X, zz_007db5c row4 -> zz_0085e00 row13.
 * Original DOL/comhit byte provenance: gatling-source-x-2026-11-12.md.
 * Source timing and state are independent of renderer updates. Collision and animated
 * joint matrices remain explicitly bounded host approximations. */
import { createPoweredPrimary, stepPoweredPrimary, type PoweredPrimaryState } from './poweredProjectile.js';
import type { BorgRuntime, Projectile } from './types.js';
import type { Vec3 } from '@gf/physics';
import type { RomActor } from './rom/actor.js';
import type { DamageRecord } from './gauges.js';
import { activeSourceTarget } from './targetLock.js';
import { tierSizeScale } from './timescale.js';
import { attackHitRecordsForKind } from './attackHitData.js';
import { familyDamageRecordForBorg } from './familyDamageData.js';

export interface GatlingPrimaryState { kind:'primary'; flight:PoweredPrimaryState }
export interface GatlingExplosionState {
  kind:'explosion'; phase:'expand'|'hold'|'tail'; age:number; tailAge:number;
  ownerScale:number; scale:number; velocity:number; alpha:number; hold:number;
  /** Source draw yaw is kept deterministic, without consuming gameplay RNG. */
  yaw:number; ringAge:number; ringScale:Vec3; ringAlpha:number;
  hitUids:string[];
}
export type GatlingSourceState = GatlingPrimaryState | GatlingExplosionState;
export const GATLING_EXPLOSION_DAMAGE:DamageRecord & {knockbackDirMode:number}={index:20,hpDamage:20,downGaugeDamage:100,
  balanceGaugeDamage:100,comboScoreValue:100,attackerHpCurveIndex:0,forceGaugeCurveIndex:0,
  hitStrength:0,impactEffectId:0,reactionFlags:2,reactionAnimVariant:4,knockbackDirMode:1,
  flagsA:0x20,flagsB:0,knockbackYawTrim:0,knockbackPitchTrim:56,rehitIntervalFrames:0};
let serial=0;
function targetData(b:BorgRuntime|null|undefined){
  return b&&b.alive&&b.hp>0&&b.state!=='death'?{uid:b.uid,pos:{...b.pos},scale:tierSizeScale(b)}:null;
}
/** Sample every battle frame, including busy/ROM-owned frames: a blocked press is not buffered. */
export function stepGatlingInput(owner:BorgRuntime,held:boolean){
  const input=owner.gatlingInput??={held:false,pressEdge:false,pending:false};
  input.pressEdge=held&&!input.held;input.held=held;input.pending=true;return input;
}
export function captureGatlingAim(owner:BorgRuntime,actor:RomActor,all:readonly BorgRuntime[]):void{
  const target=targetData(activeSourceTarget(owner,all));
  // No target: the constructor uses heading/pitch0 and never reads this aim.
  owner.gatlingSavedAim={pos:target?{...target.pos}:{...actor.pos},targetUid:target?.uid??null};
}
export function gatlingMuzzle(pos:Vec3,yaw:number,scale=1):Vec3{
  // Source joint11 bind translation, plus row-local [65,0,0]. Animation unavailable here.
  const x=67.59280443191528+65,y=136.1260986328125,z=-.000013937185372014937;
  return {x:pos.x+(x*Math.cos(yaw)+z*Math.sin(yaw))*scale,y:pos.y+y*scale,z:pos.z+(-x*Math.sin(yaw)+z*Math.cos(yaw))*scale};
}
export function spawnGatlingSource(owner:BorgRuntime,actor:RomActor,address:number,row:number,all:readonly BorgRuntime[]):Projectile[]|null{
  if(owner.borgId!=='pl0102'||actor.actionIndex!==2||address!==0x8007db5c||row!==4)return null;
  const yaw=actor.heading*Math.PI*2/65536,ownerScale=actor.modelScale*actor.sizeScale;
  // Admission snapshots attack pointers +c8/+cc separately from the live lock.
  // Windup can invalidate that target, but cannot acquire a replacement.
  const savedUid=owner.gatlingSavedAim?.targetUid;
  const target=targetData(savedUid?all.find(b=>b.uid===savedUid):null);
  const pos=gatlingMuzzle(actor.pos,yaw,ownerScale);
  // Source copies saved +518 and the surviving admission-time attack pointer.
  const flight=createPoweredPrimary(4,pos,yaw,target,ownerScale,owner.gatlingSavedAim?.pos??target?.pos??null);
  const hit=attackHitRecordsForKind('pl0102',0)[0]!;
  const record=familyDamageRecordForBorg('pl0102',hit.damageRecordIndex)!;
  return [{uid:`gatling-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...flight.pos},vel:{...flight.vel},
    damage:1,hitstun:0,knockback:1,damageRecord:record,homingTurn:0,homingTarget:null,
    aimedTargetUid:target?.uid??null,life:flight.life,hitRadius:Math.max(hit.radius,...hit.halfExtent)*ownerScale,
    visualKind:'energy',romShotKind:0,sourceHitCollisionFlags:hit.collisionFlags,
    // Primary model10 is owner-local, NOT global efct10; renderer must resolve its bank.
    romScale:[flight.scale,flight.scale,flight.scale],
    gatlingSource:{kind:'primary',flight},gatlingSkipAdvance:true,gatlingInitialPosition:{...pos}}];
}
export function createGatlingExplosion(primary:Projectile,onCue?:(cue:number)=>void):Projectile{
  const source=primary.gatlingSource;
  if(source?.kind!=='primary')throw new Error('Gatling explosion requires row4 primary');
  const ownerScale=source.flight.ownerScale;
  const s:GatlingExplosionState={kind:'explosion',phase:'expand',age:0,tailAge:0,ownerScale,
    scale:Math.fround(.01)*ownerScale,velocity:Math.fround(.1)*ownerScale,alpha:1,hold:4,
    yaw:0,ringAge:0,ringScale:{x:ownerScale,y:ownerScale,z:ownerScale},ringAlpha:1,hitUids:[]};
  onCue?.(12);
  return {uid:`gatling-explosion-${++serial}`,ownerUid:primary.ownerUid,team:primary.team,pos:{...primary.pos},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord:GATLING_EXPLOSION_DAMAGE,homingTurn:0,homingTarget:null,
    aimedTargetUid:primary.aimedTargetUid??null,life:48,hitRadius:310*s.scale,visualKind:'energy',romShotKind:107,
    sourceHitCollisionFlags:1,flightVisual:{bankTexId:22,teamTint:false,launchFxId:null},romScale:[s.scale,s.scale,s.scale],gatlingSource:s};
}
/** Source init does not advance expansion. Call once per subsequent battle frame. */
export function stepGatlingExplosion(s:GatlingExplosionState):boolean{
  s.age++;
  if(s.phase==='expand'){
    s.scale+=s.velocity;
    if(s.scale>=1.25*s.ownerScale){s.scale=1.25*s.ownerScale;s.phase='hold';}
    s.velocity=Math.max(Math.fround(.02)*s.ownerScale,Math.min(9*s.ownerScale,s.velocity));
  }else if(s.phase==='hold'){
    if(--s.hold<1){s.phase='tail';s.tailAge=0;s.ringAlpha=0;}
  }else{
    if(++s.tailAge>30)return false;
    s.scale=1.25*s.ownerScale*(1+.25*s.tailAge/30);s.alpha=1-s.tailAge/30;
  }
  if(s.phase!=='tail'){
    s.ringAge++;
    const a=s.ringAge;
    const x=a<=1?1+a:2+.5*Math.min(9,a-1)/9;
    s.ringScale={x:x*s.ownerScale,y:s.ownerScale,z:x*s.ownerScale};
    s.ringAlpha=a>10?0:a<=1?1:1-(a-1)/9;
  }
  return true;
}
export function advanceGatlingSource(pr:Projectile,byUid:Map<string,BorgRuntime>):Projectile[]{
  const s=pr.gatlingSource!;
  if(s.kind==='primary'){
    const owner=byUid.get(pr.ownerUid);
    if(owner&&(!owner.alive||owner.hp<=0||owner.state==='death')){pr.despawnReason='owner-dead';return [];}
    if(pr.gatlingSkipAdvance){pr.gatlingSkipAdvance=false;return [pr];}
    const next=stepPoweredPrimary(s.flight,targetData(s.flight.targetUid?byUid.get(s.flight.targetUid):null));
    if(!next.alive){pr.despawnReason='expired';return [];}
    s.flight=next.state;pr.pos={...next.state.pos};pr.vel={...next.state.vel};pr.life=next.state.life;
  }else{
    if(!stepGatlingExplosion(s)){pr.despawnReason='expired';return [];}
    pr.hitRadius=310*s.scale;pr.life--;
    pr.romScale=[s.scale,s.scale,s.scale];
    pr.flightVisual={bankTexId:s.phase==='tail'?23:22,teamTint:false,launchFxId:null};
  }
  return [pr];
}
