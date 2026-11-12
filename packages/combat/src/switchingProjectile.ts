/** Switching Ninja1e29fc field and flagsA10 receiver adapter. Source lifecycle,
 * collision-pass reservations and forced-move timing are explicit. Host root
 * centers/capsules replace original animated +64 geometry and +6d0 supports. */
import type {BorgRuntime,Projectile} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import {getSwitchingXState} from './switchingX.js';
import {createSwitchingField,stepSwitchingField,type SwitchingFieldState} from './switchingField.js';
import {attackHitRecordsForKind} from './attackHitData.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {romGroundIdleReturn,romAirKnockoutReturn} from './families/shared-idle-return.js';
import {statusImmunityMasksForBorgId} from './movementData.js';
export interface SwitchingSource {
  kind:'field';field:SwitchingFieldState;ownerBorgId:string;ownerFormId:string;
  captureFlagsD0:number;contactPending:boolean;
}
interface Bounds {minX:number;maxX:number;minZ:number;maxZ:number}
const f=Math.fround;
function clamp(pos:Vec3,bounds?:Bounds):Vec3{
  return {x:bounds?Math.min(bounds.maxX,Math.max(bounds.minX,pos.x)):pos.x,y:pos.y,
    z:bounds?Math.min(bounds.maxZ,Math.max(bounds.minZ,pos.z)):pos.z};
}
let serial=0;
export function spawnSwitchingSource(owner:BorgRuntime,actor:RomActor,address:number,row:number):Projectile[]|null{
  if(owner.borgId!=='pl0009'||address!==0x801e29fc||row!==0)return null;
  const state=getSwitchingXState(actor);if(!state||actor.actionIndex!==2)return null;
  const hit=attackHitRecordsForKind(owner.borgId,12)[0],record=hit&&familyDamageRecordForBorg(owner.borgId,hit.damageRecordIndex);
  if(!hit||!record)throw Error('Verified Switching HIT12 / damage12 missing');
  const field=createSwitchingField(actor.modelScale,actor.collisionScale??actor.modelScale);
  return [{uid:`switching-field-${++serial}`,ownerUid:owner.uid,team:owner.team,pos:{...actor.pos},vel:{x:0,y:0,z:0},
    damage:1,hitstun:0,knockback:1,damageRecord:record,homingTurn:0,homingTarget:null,
    aimedTargetUid:owner.switchingCapturedTargetUid??null,life:89,hitRadius:hit.radius*field.collisionScale,
    visualKind:'energy',romShotKind:12,sourceHitCollisionFlags:hit.collisionFlags,consumeOnHit:false,romScale:[0,0,0],
    switchingSource:{kind:'field',field,ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId,
      captureFlagsD0:state.captureFlagsD0,contactPending:false}}];
}
export function advanceSwitchingSource(pr:Projectile,byUid:Map<string,BorgRuntime>,bounds?:Bounds,onCue?:(cue:number)=>void):Projectile[]{
  const s=pr.switchingSource!,owner=byUid.get(pr.ownerUid);
  const invalid=!owner||!owner.alive||owner.hp<=0||owner.state==='death'?'owner-dead':
    owner.borgId!==s.ownerBorgId||(owner.combatFormId??owner.borgId)!==s.ownerFormId?'owner-changed':undefined;
  const wasPending=s.field.phase==='pending';
  s.field=stepSwitchingField(s.field,{
    ...(invalid?{ownerInvalid:invalid}:{}),priorContact10:s.contactPending,
    initialPosition:()=>{
      // INIT reads owner+c8 NOW, not child's copied c8, and has no dead-target
      // test. The host retains identity but approximates animated +64 by root.
      const target=owner?.switchingCapturedTargetUid?byUid.get(owner.switchingCapturedTargetUid):null;
      if(target&&(s.captureFlagsD0&4)!==0)return {...target.pos};
      return clamp({x:f(owner!.pos.x+Math.sin(owner!.rotY)*2000),y:owner!.pos.y,
        z:f(owner!.pos.z+Math.cos(owner!.rotY)*2000)},bounds);
    },
  });
  s.contactPending=false;pr.pos={...s.field.pos};pr.romScale=[0,0,0];pr.life--;
  if(wasPending&&s.field.visible)onCue?.(0x103);
  if(s.field.phase==='freed'){pr.despawnReason=invalid?'owner-dead':'expired';return [];}
  return [pr];
}
export interface SwitchingForcedMove {
  destination:Vec3;dispatches:number;previousState:BorgRuntime['state'];previousAnim:string;
  previousStateTime:number;hadAction:boolean;
  previousRom?:{fbCue:number;ubCue:number;fbState:number;ubState:number};
}
type ReactionSnapshot=Pick<BorgRuntime,'state'|'anim'|'stateTime'|'invincTimer'|'reactionKind'|'reactionDecelFramesRemaining'>&{vel:Vec3};
function reactionSnapshot(actor:BorgRuntime):ReactionSnapshot{return {state:actor.state,anim:actor.anim,stateTime:actor.stateTime,
  invincTimer:actor.invincTimer,reactionKind:actor.reactionKind,reactionDecelFramesRemaining:actor.reactionDecelFramesRemaining,vel:{...actor.vel}};}
interface Reservation {destination:Vec3;state:BorgRuntime['state'];anim:string;stateTime:number;hadAction:boolean}
export interface SwitchingSwapPass {outgoing:Set<string>;incoming:Set<string>;slots:Map<string,Reservation>;reactions:Map<string,ReactionSnapshot>}
export function createSwitchingSwapPass(all:readonly BorgRuntime[]=[]):SwitchingSwapPass{return {outgoing:new Set(),incoming:new Set(),slots:new Map(),
  reactions:new Map(all.map(actor=>[actor.uid,reactionSnapshot(actor)]))};}
/** Narrow mirrors for fields not yet shared by the general ROM actor adapter. */
export type SwitchingForcedRomActor=RomActor&{moveKind7c9?:number;movePhase7ca?:number;moveTimer7cb?:number;flags272?:number;state71b?:number};
function romActor(actor:BorgRuntime):SwitchingForcedRomActor|undefined{return (actor.romDriver as unknown as {actor?:SwitchingForcedRomActor}|undefined)?.actor;}
/** 2f8dc: directional dedup, not a combined already-swapped flag. Snapshot
 * before damage; a later outgoing contact may overwrite an incoming slot. */
export function stageSwitchingSwap(pass:SwitchingSwapPass,owner:BorgRuntime,victim:BorgRuntime):boolean{
  if((owner.targetEligibility83??0)!==0||(victim.targetEligibility83??0)!==0||
    (((victim.sourceSwitchingResistance59c??statusImmunityMasksForBorgId(victim.borgId).immunityA)&0x10)!==0)||
    pass.outgoing.has(owner.uid)||pass.incoming.has(victim.uid))return false;
  pass.outgoing.add(owner.uid);pass.incoming.add(victim.uid);
  if(!pass.reactions.has(victim.uid))pass.reactions.set(victim.uid,reactionSnapshot(victim));
  const a=owner.sourceSupportHeight6d0??0,b=victim.sourceSupportHeight6d0??0;
  const reserve=(actor:BorgRuntime,other:BorgRuntime,delta:number)=>pass.slots.set(actor.uid,{
    destination:{...other.pos,y:f(other.pos.y+f(delta))},state:actor.state,anim:actor.anim,stateTime:actor.stateTime,
    hadAction:(actor.cooldowns['romSpecialActive']??0)>0||actor.state==='attack'||actor.state==='special',
  });
  reserve(owner,victim,b-a);reserve(victim,owner,a-b);return true;
}
/** 2cda4 final loop ->6ab04. Do not protect participants inside collision loop:
 * all pairs in this pass must still see the prior defense registration. */
export function commitSwitchingSwapPass(pass:SwitchingSwapPass,all:readonly BorgRuntime[],onCue?:(cue:number)=>void):void{
  for(const actor of all){
    const slot=pass.slots.get(actor.uid);
    const rom=romActor(actor);
    if(!slot||!actor.alive||actor.hp<=0||actor.state==='death'||actor.switchingForcedMove||(rom?.moveKind7c9??0)!==0)continue;
    // Original additional status/object-reaction priority is not represented by
    // the host's generic states; those remain a documented scheduler seam.
    // The incoming relocation replaces reaction dispatch, not collision damage,
    // status writes, gauge accumulation or death. Preserve pre-pass motion.
    if(pass.incoming.has(actor.uid)){const reaction=pass.reactions.get(actor.uid);if(reaction)Object.assign(actor,{...reaction,vel:{...reaction.vel}});}
    actor.switchingForcedMove={destination:{...slot.destination},dispatches:0,previousState:actor.state,
      previousAnim:actor.anim,previousStateTime:actor.stateTime,hadAction:rom?(rom.controlWord&3)!==0:slot.hadAction,
      ...(rom?{previousRom:{fbCue:rom.fbCue,ubCue:rom.ubCue,fbState:rom.fbState,ubState:rom.ubState}}:{})};
    if(rom){
      rom.moveKind7c9=2;rom.movePhase7ca=rom.moveTimer7cb=0;rom.flags272=0xffff;rom.state71b=0;rom.controlWord|=0x1000;
      //6a7b4/6a7f4 deliberately DO NOT clear the suspended phase registers.
      rom.fbCue=rom.ubCue=0x23;rom.fbState=rom.cueTable?.[0x23*2]??0;rom.ubState=rom.cueTable?.[0x23*2+1]??43;
    }
    actor.sourceDefenseDisabled=true;onCue?.(0xf2);
  }
}
/** Source64548: five actual actor dispatches, independent of animation dt.
 * No motion/facing reset. Kind2 uses stage bounds only, not floor/wall placement. */
export function stepSwitchingForcedMove(actor:BorgRuntime,bounds?:Bounds):boolean{
  const move=actor.switchingForcedMove;if(!move)return false;
  if(!actor.alive||actor.hp<=0||actor.state==='death'){
    const rom=romActor(actor);if(rom){rom.moveKind7c9=0;rom.flags272=0;rom.controlWord&=~0x1000;}
    delete actor.switchingForcedMove;delete actor.sourceDefenseDisabled;return false;
  }
  const rom=romActor(actor);
  move.dispatches++;
  if(rom){rom.flags272=0xffff;rom.movePhase7ca=move.dispatches<3?1:2;rom.moveTimer7cb=move.dispatches===1||move.dispatches===3?2:1;}
  if(move.dispatches===3){
    move.destination=clamp(move.destination,bounds);Object.assign(actor.pos,move.destination);
    // Host bridge exposes actor storage; keep both source histories coherent so
    // the next command cannot treat relocation as own-motion recoil.
    if(rom){Object.assign(rom.pos,actor.pos);Object.assign(rom.savedGroundPos,actor.pos);Object.assign(rom.targetCache5e8,actor.pos);}
  }
  if(move.dispatches>=5){
    if(rom){rom.moveKind7c9=0;rom.movePhase7ca=3;rom.moveTimer7cb=0;rom.flags272=0;rom.controlWord&=~0x1000;}
    if(rom?(rom.controlWord&3)!==0:move.hadAction){
      const control=rom?.controlWord??0;
      actor.romDriver?.interrupt();
      if(rom){
        rom.controlWord=control;
        if((control&2)===0){rom.housekeeping73f=0;rom.controlWord&=~3;}
        // Original661 class selector is not exported by generic host locomotion.
        if(actor.grounded)romGroundIdleReturn(rom);else romAirKnockoutReturn(rom);
      }
      actor.state=actor.grounded?'idle':'jump';actor.anim=actor.state;actor.stateTime=0;
    }else {
      if(rom&&move.previousRom)Object.assign(rom,move.previousRom);
      actor.state=move.previousState;actor.anim=move.previousAnim;actor.stateTime=move.previousStateTime;
    }
    delete actor.switchingForcedMove;delete actor.sourceDefenseDisabled;
  }
  return true;
}
