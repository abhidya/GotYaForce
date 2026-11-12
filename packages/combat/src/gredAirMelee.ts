/** Scoped G RED-family airborne close-B: command80365dc8 ->178394.
 * Source state/control/clock are bound separately from host root targets,
 * terrain and unavailable joint3/attack-bone transforms. Other variants retain
 * their previous handlers. No generic shared-engine changes.
 */
import type {RomActor,Vec3} from './rom/actor.js';
import {stepTargetYaw,stepPartTargetPitch,toS16,type RomHelperScratch} from './rom/helpers.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {dispatchUpperBodyCue} from './rom/dispatch.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {romAirKnockoutReturn} from './families/shared-idle-return.js';
import {tickGredAirMelee,type GredAirMeleeState,type GredAirMeleeHooks} from './families/gred-air-melee-engine.js';
import {createGRedAirMeleeStream,tickGRedAirMeleeStream,type GRedAirMeleeStream} from './gredAirMeleeStream.js';
import {GRED_AIR_MELEE_PROFILES,gredAirMeleeStreamProfile,type GRedAirMeleeFamily,type GRedAirMeleeProfile} from './gredAirMeleeConfig.js';

type Actor=RomActor & RomHelperScratch & {grounded?:boolean;return590?:number;return690?:number;return71b?:number;
  movementTrailFlag1d9b?:number;launchYaw1db0?:number;launchSpeed1dac?:number};
const f=Math.fround;
const rangeRows=[1000,1200,1300] as const;
/** Accessors keep stream/physics hook writes visible during the same engine call. */
export class GRedAirMeleeState implements GredAirMeleeState {
  constructor(readonly actor:Actor,public targetUid:string|null){
    if(actor.borgNumber!==0x615&&actor.borgNumber!==0x62a&&actor.borgNumber!==0x629)throw Error('Unadmitted airborne melee family');
    this.family=actor.borgNumber===0x62a?'black':actor.borgNumber===0x629?'neo':'red';
    this.profile=GRED_AIR_MELEE_PROFILES[this.family];
  }
  readonly family:GRedAirMeleeFamily;
  readonly profile:GRedAirMeleeProfile;
  stream:GRedAirMeleeStream|null=null;
  streamMask=0;
  pendingContact=0;input1d9=0;acceptedContactCount=0;
  hitActivationSerial=0;hitRecordIndex:number|null=null;
  noTargetLatch541=0;retap746=0;alt745=0;pitch54e=0;
  /** Authored shadows only: post18cf54's AF/sound pulse and clearing of6e9
   * are not bound to live presentation by this lane. */
  contactFlags709=0;flags6e8=0;flags6e9=0;
  /** Raw op07 state only. Equipment rendering/consumers are not fabricated. */
  equipment1d74=0;equipment1d75:number|null=null;
  equipment1d94=0;equipment1d95:number|null=null;
  transitionFxCount=0;
  lastGroundProbe:0|1=0;
  exitKind:'landing'|'stream-end'|null=null;
  /** Explicit original1dd80 override; no inferred burst/hitstun binding. */
  forceRange1dd80=false;
  /** Original family+10 selects JOINT matrix3, not partAimAnchors[3]. This
   * unbound seam falls back to the current actor root, never a guessed bone. */
  joint3AimAnchor:Vec3|null=null;
  get phase(){return this.actor.fbPhaseSlots[0]??0;} set phase(v:number){this.actor.fbPhaseSlots[0]=v;}
  get target():object|null{return this.actor.lockTarget??null;}
  set target(v:object|null){this.actor.lockTarget=v as Vec3|null;if(v===null)this.targetUid=null;}
  get heading72(){return this.actor.heading;} set heading72(v:number){this.actor.heading=v;}
  get activeYaw(){return this.actor.activeYaw;} set activeYaw(v:number){this.actor.activeYaw=v;}
  get lockYaw(){return this.actor.lockYaw;} set lockYaw(v:number){this.actor.lockYaw=v;}
  get handlerTimer(){return this.actor.handlerTimer;} set handlerTimer(v:number){this.actor.handlerTimer=v;}
  get pos(){return this.actor.pos;} set pos(v:Vec3){this.actor.pos=v;}
  get savedGroundPos(){return this.actor.targetCache5e8;} set savedGroundPos(v:Vec3){this.actor.targetCache5e8=v;}
  get motion(){return this.actor.motion;} set motion(v:Vec3){this.actor.motion=v;}
  get hSpeed(){return this.actor.hSpeed;} set hSpeed(v:number){this.actor.hSpeed=v;}
  get yVel(){return this.actor.yVel;} set yVel(v:number){this.actor.yVel=v;}
  get hDecel(){return this.actor.hDecel;} set hDecel(v:number){this.actor.hDecel=v;}
  get gravityCoeff(){return this.actor.gravityCoeff;} set gravityCoeff(v:number){this.actor.gravityCoeff=v;}
  get shift18da(){return this.actor.steerYaw;} set shift18da(v:number){this.actor.steerYaw=v;}
  get poseAccum7c(){return {x:this.actor.poseAccum7c,y:this.actor.poseAccum7e,z:this.actor.poseAccum80};}
  set poseAccum7c(v:Vec3){this.actor.poseAccum7c=v.x;this.actor.poseAccum7e=v.y;this.actor.poseAccum80=v.z;}
  get streamSlot6ea(){return this.actor.streamSlot;} set streamSlot6ea(v:number){this.actor.streamSlot=v;}
  get dashStrength1d0f(){return this.actor.dashStrength1d0f;} set dashStrength1d0f(v:number){this.actor.dashStrength1d0f=v;}
  get aimMode1d10(){return this.actor.faceGate1d10;} set aimMode1d10(v:number){this.actor.faceGate1d10=v;}
  get inputEdges5d4(){return this.actor.inputEdge5d4;} set inputEdges5d4(v:number){this.actor.inputEdge5d4=v;}
  get contactP0(){return this.actor.contactP0;} set contactP0(v:number){this.actor.contactP0=v;}
  get contactP1(){return this.actor.contactP1;} set contactP1(v:number){this.actor.contactP1=v;}
  get streamHold1b03(){return this.actor.streamHold1b03;} set streamHold1b03(v:number){this.actor.streamHold1b03=v;}
  get wallContact(){return this.actor.wallContact;} set wallContact(v:number){this.actor.wallContact=v;}
  get actionFlag73f(){return this.actor.housekeeping73f;} set actionFlag73f(v:number){this.actor.housekeeping73f=v;}
  get controlWord(){return this.actor.controlWord;} set controlWord(v:number){this.actor.controlWord=v;}
  get landingTimer694(){return this.actor.stateTimer;} set landingTimer694(v:number){this.actor.stateTimer=v;}
  get descriptorGravity6c(){return this.actor.descriptor?.handlerData6c??-1;}
  get rangeRow86c(){
    const row=((this.actor.prevActionIndex<<24)>>24)%3,value=rangeRows[row];
    if(value===undefined)throw Error('RED air B has an unbound source range row');return value;
  }
  get dt(){return this.actor.dt;}
}
const states=new WeakMap<RomActor,GRedAirMeleeState>();
export function getGRedAirMeleeState(a:RomActor):GRedAirMeleeState|undefined{return states.get(a);}
export function prepareGRedAirMelee(a:RomActor,targetUid:string|null):GRedAirMeleeState {
  const s=new GRedAirMeleeState(a,targetUid);states.set(a,s);return s;
}
export function clearGRedAirMelee(a:RomActor):void{states.delete(a);}
export function beginGRedAirMeleeTick(a:RomActor):void {
  const s=states.get(a);if(s){s.input1d9=s.pendingContact;s.pendingContact=0;}
}
export function acceptGRedAirMeleeContact(a:RomActor,s:GRedAirMeleeState):void {
  if(states.get(a)!==s)return;s.pendingContact|=0x10;s.acceptedContactCount++;
}
function range(s:GRedAirMeleeState,value:number,threeD:boolean):number {
  const t=s.actor.lockTarget;if(!t)return -1;if(s.forceRange1dd80)return 1;
  return Math.hypot(t.x-s.pos.x,threeD?t.y-s.pos.y:0,t.z-s.pos.z)<=f(value*s.actor.modelScale)?1:0;
}
function groundProbe(s:GRedAirMeleeState):number {
  const a=s.actor,r=a.physicsRuntime?.probeMotion?.(a.savedGroundPos,a.pos,a.yVel)??a.physicsRuntime?.clampToGround(a.pos,a.yVel);
  if(!r){s.lastGroundProbe=0;return 0;}
  if('y' in r && typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;return s.lastGroundProbe;
}
/** 6e514 uses AC*dt and a joint3 origin. JS atan2/BAM conversion and the
 * unavailable joint transform remain explicit host numeric/geometry adapters. */
function pitch(s:GRedAirMeleeState):void {
  const a=s.actor,t=a.lockTarget,current=toS16(s.pitch54e);
  if(!t){s.pitch54e=toS16(Math.trunc(f(current*f(.9))));return;}
  const p=s.joint3AimAnchor??a.pos;
  const targetPitch=toS16(Math.round(Math.atan2(t.y-p.y,Math.hypot(t.x-p.x,t.z-p.z))/(Math.PI*2)*0x10000));
  const desired=Math.max(-0x4000,Math.min(0x4000,toS16(-toS16(a.bodyPitch)-targetPitch)));
  const step=toS16(Math.trunc(f(toS16(a.descriptor?.turnStep0??2560)*a.dt)));
  const difference=toS16(desired-current);
  s.pitch54e=Math.abs(difference)<=step?desired:toS16(current+(difference<0?-step:step));
}
export function stepGRedAirMelee(a:RomActor,ctx:StreamContext):void {
  const s=states.get(a);if(!s||a.borgNumber!==s.profile.borgNumber||a.actionIndex!==1||a.variantIndex!==4)return;
  const h:GredAirMeleeHooks={
    range66838:(_state,r)=>range(s,r,false),proximity668cc:(_state,r)=>range(s,r,true),
    face6d144:()=>{Object.assign(a.aimOrigin518,a.pos);return stepTargetYaw(a,0xc0,0,true)?1:0;},
    pitch6e514:()=>pitch(s),pitch6e1ac:()=>{stepPartTargetPitch(a,0xc0);},
    startStream:(_state,mask,group,slot,rate)=>startStream(a,mask,group,slot,rate),
    tickStream:(_state,mask)=>tickStream(a,mask,ctx),groundProbe677b0:()=>groundProbe(s),
    physics67310:(_state,g,yaw)=>integratePhysicsPrimary(g,a,yaw),
    // 92dcc cosmetic child allocation/RNG is unbound, never a guessed particle.
    transition92dcc:()=>{s.transitionFxCount++;},
    landing6a750:()=>{s.exitKind='landing';dispatchUpperBodyCue(a,7);},
    airReturn6a5a4:()=>{
      s.exitKind='stream-end';s.actor.return590=1;s.actor.return690=0;s.actor.return71b=0;
      if(s.actor.movementTrailFlag1d9b){a.lockYaw=toS16((s.actor.launchYaw1db0??0)+a.heading);a.hSpeed=s.actor.launchSpeed1dac??0;}
      romAirKnockoutReturn(a);
    },
  };
  tickGredAirMelee(s,s.profile.engine,h);
}
export function startGRedAirMeleeStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s||a.borgNumber!==s.profile.borgNumber||a.actionIndex!==1||a.variantIndex!==4||group!==3)return false;
  const stream=gredAirMeleeStreamProfile(s.family,slot);if(!stream)return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;
  s.stream=createGRedAirMeleeStream(a.dt,s.family,slot);
  if(s.streamMask&1){a.wallContact=0;a.contactP0=0;a.contactP1=0;
    if(stream.initialGroup!==undefined)a.defaultGroup=stream.initialGroup;
    s.flags6e8=stream.initialFlags6e8;s.flags6e9=0;a.streamHold1b03=s.stream.blendMode;
    // Op070003ff supplies mode3, while FF requests the family default.
    // Keep that unbound default unknown rather than guessing a presentation byte.
    if(stream.equipment){s.equipment1d74=s.equipment1d94=3;s.equipment1d75=s.equipment1d95=null;}
    ctx.onArmHit?.(a,stream.hitKind,stream.statusId,stream.statusArg);}
  if(s.streamMask&2){a.dashStrength1d0f=stream.initialDash;a.faceGate1d10=1;s.contactFlags709=1;}
  ctx.onPlayAnim?.(a,3,stream.animSlot,false);return true;
}
export function tickGRedAirMeleeStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const e=tickGRedAirMeleeStream(s.stream,a.dt);
  if(s.streamMask&1){a.streamHold1b03=s.stream.blendMode;
    if(e.contact!==undefined){a.contactP0=e.contact;a.parts[0]!.stateByte=e.contact;}
    if(e.aux!==undefined)a.contactP1=e.aux;
    if(e.flags6e8!==undefined)s.flags6e8=e.flags6e8;
    if(e.flags6e9!==undefined)s.flags6e9=e.flags6e9;
    if(e.completed)a.wallContact=1;
  }
  if(s.streamMask&2){
    if(e.dashStrength!==undefined)a.dashStrength1d0f=e.dashStrength;
    if(e.faceGate!==undefined)a.faceGate1d10=e.faceGate;
    if(e.clearContactFlags)s.contactFlags709&=~0x1f;
  }
  if(e.recovery)ctx.onPlayAnim?.(a,0,14,false);
  if(e.completed)for(let p=0;p<a.parts.length;p++)if(s.streamMask&(1<<p)){a.parts[p]!.streamPtr=-1;a.parts[p]!.active=0;}
  return true;
}
