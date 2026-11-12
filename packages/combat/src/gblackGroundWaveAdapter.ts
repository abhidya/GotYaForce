/** G BLACK18d1d8 -> fc208(type5), emitter/pulse bridge. Source lifecycles are
 * pure; root yaw, target roots, terrain triangles and collision scale fallback
 * are explicit host seams. No generic projectile flight or contact consumption.
 */
import type { RomActor } from './rom/actor.js';
import type { BorgRuntime, Projectile } from './types.js';
import type { DamageRecord } from './gauges.js';
import { getNeoGredMeleeState } from './neoGredMelee.js';
import { createGBlackGroundWaveParent, createGBlackGroundWaveChild,
  stepGBlackGroundWaveParent, stepGBlackGroundWaveChild, G_BLACK_GROUND_WAVE,
  type GBlackGroundWaveParentState, type GBlackGroundWaveChildState,
  type GBlackGroundWaveParentContext, type GBlackGroundWaveChildSpawn,
} from './gblackGroundWave.js';

type OwnerIdentity = { ownerBorgId: string; ownerFormId: string; hitUids: string[] };
export type GBlackGroundWaveSource = (GBlackGroundWaveParentState | GBlackGroundWaveChildState) & OwnerIdentity;
/** Global damage row9, not the owner's family-local row9. */
export const G_BLACK_GROUND_WAVE_DAMAGE: DamageRecord & { knockbackDirMode: number } = Object.freeze({
  index: 9, hpDamage: 20, downGaugeDamage: 100, balanceGaugeDamage: 100, comboScoreValue: 50,
  attackerHpCurveIndex: 0, forceGaugeCurveIndex: 0, hitStrength: 0, impactEffectId: 0,
  reactionFlags: 2, reactionAnimVariant: 4, knockbackDirMode: 1,
  flagsA: 0x20, flagsB: 0, knockbackYawTrim: 0, knockbackPitchTrim: 32, rehitIntervalFrames: 0,
});
let serial = 0;
/** Source matrix8d4 is approximated by root translation, yaw and modelScale.
 * Source+c0 is separate. The absent explicit field binds to host modelScale;
 * multiplying visual sizeScale here would silently conflate distinct source fields.
 */
export function spawnGBlackGroundWaveSource(owner: BorgRuntime, actor: RomActor, address: number, kind: number): Projectile[] | null {
  if(owner.borgId!=='pl062a'||address!==G_BLACK_GROUND_WAVE.spawner||kind!==5)return null;
  const admitted=getNeoGredMeleeState(actor);
  if(!admitted||admitted.family!=='black'||actor.actionIndex!==1||actor.variantIndex!==0||
    admitted.stream?.slot!==15||(actor.controlWord&0x40)!==0||actor.supportContact1db!==0)return [];
  const yaw=actor.heading*Math.PI*2/65536;
  const facing={x:Math.sin(yaw),y:0,z:Math.cos(yaw)};
  const pos={x:actor.pos.x+facing.x*50*actor.modelScale,y:actor.pos.y,z:actor.pos.z+facing.z*50*actor.modelScale};
  const state:GBlackGroundWaveSource={...createGBlackGroundWaveParent({pos,facing,
    modelScale:actor.modelScale,collisionScale:actor.collisionScale??actor.modelScale,targetUid:admitted.targetUid}),
    ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId,hitUids:[]};
  return [{uid:`gblack-wave-parent-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...pos},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,homingTurn:0,homingTarget:null,aimedTargetUid:admitted.targetUid,
    life:0,hitRadius:0,visualKind:'flame',romScale:[0,0,0],gblackGroundWaveSource:state}];
}
function createPulse(parent:Projectile,spawn:GBlackGroundWaveChildSpawn):Projectile {
  const source=parent.gblackGroundWaveSource!;
  const state:GBlackGroundWaveSource={...createGBlackGroundWaveChild(spawn),ownerBorgId:source.ownerBorgId,
    ownerFormId:source.ownerFormId,hitUids:[]};
  return {uid:`gblack-wave-child-${++serial}`,ownerUid:parent.ownerUid,team:parent.team,pos:{...spawn.pos},
    vel:{x:0,y:0,z:0},damage:1,hitstun:0,knockback:1,damageRecord:G_BLACK_GROUND_WAVE_DAMAGE,
    homingTurn:0,homingTarget:null,aimedTargetUid:parent.aimedTargetUid??null,life:0,
    hitRadius:G_BLACK_GROUND_WAVE.hitRadius*spawn.collisionScale,visualKind:'flame',romShotKind:84,
    sourceHitCollisionFlags:1,sourceSelfContactEnabled:false,consumeOnHit:false,
    romScale:[0,0,0],gblackGroundWaveSource:state};
}
export interface GBlackGroundWaveAdapterContext {
  terrainHeight: GBlackGroundWaveParentContext['terrainHeight'];
  wallSegment?: NonNullable<GBlackGroundWaveParentContext['wallSegment']>;
  outsideBounds?: NonNullable<GBlackGroundWaveParentContext['outsideBounds']>;
  /** No generic projectile impact can substitute for the source attraction gate. */
  attraction83714?: NonNullable<GBlackGroundWaveParentContext['attraction83714']>;
  rngByte: () => number;
}
export function advanceGBlackGroundWave(pr:Projectile,byUid:Map<string,BorgRuntime>,ctx:GBlackGroundWaveAdapterContext):Projectile[] {
  const source=pr.gblackGroundWaveSource!;
  const owner=byUid.get(pr.ownerUid);
  const ownerInvalid=!owner||!owner.alive||owner.hp<=0||owner.state==='death'?'owner-dead' as const:
    owner.borgId!==source.ownerBorgId||(owner.combatFormId??owner.borgId)!==source.ownerFormId?'owner-changed' as const:undefined;
  let next:GBlackGroundWaveParentState|GBlackGroundWaveChildState;
  let children:Projectile[]=[];
  if(source.kind==='parent'){
    const result=stepGBlackGroundWaveParent(source,{...ctx,...(ownerInvalid?{ownerInvalid}:{}),
      // Capture identity at admission; never acquire a changed player lock. The
      // last runtime root remains readable before target invalidation after motion.
      targetPosition:uid=>byUid.get(uid)?.pos??null,
      //83874 also clears on source state/656 and captured HIT-volume penetration
      // at threshold0. Those shape/state inputs are not bound by this root adapter.
      targetInvalid:uid=>{const target=byUid.get(uid);return !target||!target.alive||target.hp<=0||target.state==='death';},
    });
    next=result.state;children=result.children.map(spawn=>createPulse(pr,spawn));
  }else next=stepGBlackGroundWaveChild(source,{terrainHeight:ctx.terrainHeight,rngByte:ctx.rngByte,...(ownerInvalid?{ownerInvalid}:{})}).state;
  pr.gblackGroundWaveSource={...source,...next};pr.pos={...next.pos};pr.life=next.life;
  pr.vel=next.kind==='parent'?{...next.motion}:{x:0,y:0,z:0};
  pr.romScale=next.kind==='child'?[...next.visualScale]:[0,0,0];
  if(next.phase!=='active'&&next.phase!=='pending')pr.despawnReason=ownerInvalid?'owner-dead':'expired';
  // Explicit host scheduler: children allocated here remain pending through this
  // pass, then initialize HIT before RNG in their next projectile update. Original
  // pool-slot same-frame dispatch order has not been established.
  return next.phase==='freed'?children:[pr,...children];
}
