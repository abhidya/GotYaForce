import { spawnTimeBomberMine, type TimeBomberMineSource } from './timeBomberMineAdapter.js';
/** pl0106 grounded X: 800fe668/800fe818/800feae8 row2, explosion80085e00 row19.
 * Original numeric provenance: time-bomber-source-attack-2026-11-12.md.
 * Source frame math; static joint pose and spherical host collision remain approximations.
 */
import type {Vec3} from '@gf/physics';
import type {BorgRuntime,Projectile} from './types.js';
import type {RomActor} from './rom/actor.js';
import type {DamageRecord} from './gauges.js';
import {actorAimTarget} from './sourceAttackTarget.js';
import {tierSizeScale} from './timescale.js';
import {activeSourceTarget} from './targetLock.js';
import {attackHitRecordsForKind} from './attackHitData.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {stepGatlingExplosion,type GatlingExplosionState} from './gatlingProjectile.js';
export interface TimeBomberTarget {uid:string;pos:Vec3;radius:number}
export interface TimeBomberPrimaryState {
 kind:'primary';pos:Vec3;vel:Vec3;speed:number;life:number;durability:number;
 ownerScale:number;ownerBorgId?:string;targetUid:string|null;steeringTimer:number;pending:boolean;alive:boolean;
}
export type TimeBomberSourceState=TimeBomberPrimaryState|TimeBomberMineSource|(GatlingExplosionState & { mineOrigin?:true });
const norm=(v:Vec3,fallback:Vec3):Vec3=>{const n=Math.hypot(v.x,v.y,v.z);return n>1e-10?{x:v.x/n,y:v.y/n,z:v.z/n}:{...fallback};};
const mul=(v:Vec3,n:number):Vec3=>({x:v.x*n,y:v.y*n,z:v.z*n});
function steer(v:Vec3,to:Vec3):Vec3{
 const a=norm(v,{x:0,y:0,z:1}),b=norm(to,a);
 const angle=Math.acos(Math.max(-1,Math.min(1,a.x*b.x+a.y*b.y+a.z*b.z)));
 const turn=Math.min(angle,Math.fround(3*0.01745329238474369));
 if(angle<1e-10)return a;
 let axis=norm({x:a.y*b.z-a.z*b.y,y:a.z*b.x-a.x*b.z,z:a.x*b.y-a.y*b.x},{x:0,y:1,z:0});
 const c=Math.cos(turn),s=Math.sin(turn),d=axis.x*a.x+axis.y*a.y+axis.z*a.z;
 return norm({x:a.x*c+(axis.y*a.z-axis.z*a.y)*s+axis.x*d*(1-c),y:a.y*c+(axis.z*a.x-axis.x*a.z)*s+axis.y*d*(1-c),z:a.z*c+(axis.x*a.y-axis.y*a.x)*s+axis.z*d*(1-c)},a);
}
/** Allocator leaves initializer pending; neither construction nor initialization flies. */
export function createTimeBomberPrimary(pos:Vec3,yaw:number,target:TimeBomberTarget|null,ownerScale=1,aim:Vec3|null=target?.pos??null,homing=true):TimeBomberPrimaryState{
 const forward={x:Math.sin(yaw),y:0,z:Math.cos(yaw)};
 const direction=target&&aim?norm({x:aim.x-pos.x,y:aim.y-pos.y,z:aim.z-pos.z},forward):forward;
 return {kind:'primary',pos:{...pos},vel:mul(direction,20),speed:20,life:300,durability:1,ownerScale,targetUid:homing?(target?.uid??null):null,steeringTimer:4,pending:true,alive:true};
}
export function stepTimeBomberPrimary(input:TimeBomberPrimaryState,target:TimeBomberTarget|null):TimeBomberPrimaryState{
 const s={...input,pos:{...input.pos},vel:{...input.vel}};
 if(!s.alive)return s;
 if(s.pending){s.pending=false;return s;}
 if(s.life<1||s.durability<1){s.alive=false;return s;}
 s.speed=s.speed<60?s.speed+8:60;
 let direction=norm(s.vel,{x:0,y:0,z:1});
 const valid=s.targetUid!==null&&target?.uid===s.targetUid?target:null;
 // 80083874 uses distance to the target shape surface, not merely its root.
 // radius is the host body approximation supplied by the adapter.
 if(!valid||Math.hypot(valid.pos.x-s.pos.x,valid.pos.y-s.pos.y,valid.pos.z-s.pos.z)-valid.radius<=200)s.targetUid=null;
 else if(--s.steeringTimer<1){s.steeringTimer=4;direction=steer(direction,{x:valid.pos.x-s.pos.x,y:valid.pos.y-s.pos.y,z:valid.pos.z-s.pos.z});}
 s.vel=mul(direction,s.speed);s.pos={x:s.pos.x+s.vel.x,y:s.pos.y+s.vel.y,z:s.pos.z+s.vel.z};s.life--;return s;
}
let serial=0;
function targetData(b:BorgRuntime|null|undefined):TimeBomberTarget|null{
 return b&&b.alive&&b.hp>0&&b.state!=='death'?{uid:b.uid,pos:{...b.pos},radius:60*tierSizeScale(b)}:null;
}
export function stepTimeBomberInput(owner:BorgRuntime,held:boolean){const input=owner.timeBomberInput??={held:false,pressEdge:false,pending:false};input.pressEdge=held&&!input.held;input.held=held;input.pending=true;return input;}
// 8006ae60/8006bda8 snapshot d0 bit4: original pl0106 enemy/friendly range6000.
// Actor6b8 suppression is not represented by the current host adapter.
export function captureTimeBomberAim(owner:BorgRuntime,actor:RomActor,all:readonly BorgRuntime[]):void{const target=actorAimTarget(activeSourceTarget(owner,all));owner.timeBomberSavedAim={pos:target?{...target.pos}:{...actor.pos},targetUid:target?.uid??null,homing:!!target&&Math.hypot(target.pos.x-actor.pos.x,target.pos.y-actor.pos.y,target.pos.z-actor.pos.z)<=6000};}
/** Original joint7 bind-world matrix is identity rotation plus this translation.
 * Animated pose is not yet available to this source adapter. */
export function timeBomberMuzzle(pos:Vec3,yaw:number,scale=1):Vec3{
 const x=-178.58972215652508,y=130.12603759765625,z=31.60999780971141;
 return {x:pos.x+(x*Math.cos(yaw)+z*Math.sin(yaw))*scale,y:pos.y+y*scale,z:pos.z+(-x*Math.sin(yaw)+z*Math.cos(yaw))*scale};
}
export function spawnTimeBomberSource(owner:BorgRuntime,actor:RomActor,address:number,row:number,all:readonly BorgRuntime[]):Projectile[]|null{
 if(owner.borgId==='pl0106'&&address===0x800e058c&&row===2)return [spawnTimeBomberMine(owner,actor)];
 if(owner.borgId!=='pl0106'||actor.actionIndex!==0||address!==0x800fe668||row!==2)return null;
 const yaw=actor.heading*Math.PI*2/65536,ownerScale=actor.modelScale*actor.sizeScale;
 const uid=owner.timeBomberSavedAim?.targetUid;
 const target=targetData(uid?all.find(b=>b.uid===uid):null);
 const pos=timeBomberMuzzle(actor.pos,yaw,ownerScale);
 const state=createTimeBomberPrimary(pos,yaw,target,ownerScale,owner.timeBomberSavedAim?.pos??target?.pos??null,owner.timeBomberSavedAim?.homing??false);
 state.ownerBorgId=owner.borgId;
 const hit=attackHitRecordsForKind('pl0106',17)[0]!;
 const record=familyDamageRecordForBorg('pl0106',hit.damageRecordIndex)!;
 return [{uid:`time-bomber-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...pos},vel:{...state.vel},damage:1,hitstun:0,knockback:1,
 damageRecord:record,homingTurn:0,homingTarget:null,aimedTargetUid:target?.uid??null,life:300,
 hitRadius:Math.max(hit.radius,...hit.halfExtent)*ownerScale,visualKind:'energy',romShotKind:17,sourceHitCollisionFlags:hit.collisionFlags,
 // Model3 is OWNER-local; generic procedural shell is an explicit visual approximation.
 romScale:[ownerScale,ownerScale,ownerScale],timeBomberSource:state}];
}
export const TIME_BOMBER_EXPLOSION_DAMAGE:DamageRecord & {knockbackDirMode:number}={index:26,hpDamage:20,downGaugeDamage:100,
 balanceGaugeDamage:100,comboScoreValue:50,attackerHpCurveIndex:0,forceGaugeCurveIndex:0,
 hitStrength:0,impactEffectId:0,reactionFlags:2,reactionAnimVariant:4,knockbackDirMode:1,
 flagsA:0x60,flagsB:0,knockbackYawTrim:0,knockbackPitchTrim:32,rehitIntervalFrames:0};
export function createTimeBomberExplosion(primary:Projectile,onCue?:(cue:number)=>void):Projectile{
 const source=primary.timeBomberSource;if(source?.kind!=='primary'&&source?.kind!=='mine')throw Error('Time Bomber explosion requires a flight child');
 const ownerScale=source.ownerScale;
 const s:GatlingExplosionState & {mineOrigin?:true}={...(source.kind==='mine'?{mineOrigin:true as const}:{}),kind:'explosion',phase:'expand',age:0,tailAge:0,ownerScale,
 scale:Math.fround(.01)*ownerScale,velocity:Math.fround(.1)*ownerScale,alpha:1,hold:4,
 yaw:0,ringAge:0,ringScale:{x:ownerScale,y:ownerScale,z:ownerScale},ringAlpha:1,hitUids:[]};
 onCue?.(12);
 return {uid:`time-bomber-explosion-${++serial}`,ownerUid:primary.ownerUid,team:primary.team,pos:{...primary.pos},vel:{x:0,y:0,z:0},
 damage:1,hitstun:0,knockback:1,damageRecord:TIME_BOMBER_EXPLOSION_DAMAGE,homingTurn:0,homingTarget:null,
 aimedTargetUid:primary.aimedTargetUid??null,life:48,hitRadius:310*s.scale,visualKind:'energy',romShotKind:179,
 sourceHitCollisionFlags:1,sourceSelfContactEnabled:true,flightVisual:{bankTexId:22,teamTint:false,launchFxId:null},romScale:[s.scale,s.scale,s.scale],timeBomberSource:s};
}
export const stepTimeBomberExplosion=stepGatlingExplosion;
export function advanceTimeBomberSource(pr:Projectile,byUid:Map<string,BorgRuntime>,onCue?:(cue:number)=>void):Projectile[]{
 const s=pr.timeBomberSource!;
 if(s.kind==='mine')throw Error('Mine lifecycle must use the Battle adapter');
 if(s.kind==='primary'){
 const owner=byUid.get(pr.ownerUid);if(owner&&(!owner.alive||owner.hp<=0||owner.state==='death'||(s.ownerBorgId!==undefined&&owner.borgId!==s.ownerBorgId))){pr.despawnReason='owner-dead';return [];}
 if(s.pending)onCue?.(235);
 const next=stepTimeBomberPrimary(s,targetData(s.targetUid?byUid.get(s.targetUid):null));
 if(!next.alive){pr.despawnReason='expired';return [];}
 pr.timeBomberSource=next;pr.pos={...next.pos};pr.vel={...next.vel};pr.life=next.life;
 }else{
 if(!stepTimeBomberExplosion(s)){pr.despawnReason='expired';return [];}
 pr.hitRadius=310*s.scale;pr.life--;pr.romScale=[s.scale,s.scale,s.scale];pr.flightVisual={bankTexId:s.phase==='tail'?23:22,teamTint:false,launchFxId:null};
 }
 return [pr];
}
