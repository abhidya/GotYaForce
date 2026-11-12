/** Scoped RED/NEO action3/v0, original179814 + cfg80365854. Saved target
 * point, root/joint geometry, floor and browser input are explicit host seams.
 * BLACK179d20 and the legacy shared-charge engine are deliberately untouched. */
import type {RomActor,Vec3} from './rom/actor.js';
import {toS16,type RomHelperScratch} from './rom/helpers.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {dispatchUpperBodyCue} from './rom/dispatch.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {romAirKnockoutReturn,romGroundIdleReturn} from './families/shared-idle-return.js';
import {tickGredCharge,GRED_CHARGE_CONFIG,type GredChargeState,type GredChargeHooks} from './families/gred-charge-engine.js';
import {createGRedChargeStream,tickGRedChargeStream,type GRedChargeStream} from './gredChargeStream.js';
type Actor=RomActor & RomHelperScratch & {grounded?:boolean;return590?:number;return690?:number;return71b?:number};
const f=Math.fround;
export class GRedChargeState implements GredChargeState {
  constructor(readonly actor:Actor,public targetUid:string|null,point:Vec3){
    if(actor.borgNumber!==0x615&&actor.borgNumber!==0x629)throw Error('Unadmitted charged B family');
    this.family=actor.borgNumber===0x615?'red':'neo';this.aimTarget524={...point};
    // A live triplet is necessary: the source engine clears each component.
    this.poseAccum7c={get x(){return actor.poseAccum7c;},set x(v:number){actor.poseAccum7c=v;},
      get y(){return actor.poseAccum7e;},set y(v:number){actor.poseAccum7e=v;},
      get z(){return actor.poseAccum80;},set z(v:number){actor.poseAccum80=v;}};
  }
  readonly family:'red'|'neo';readonly poseAccum7c:Vec3;
  aimTarget524:Vec3;stream:GRedChargeStream|null=null;streamMask=0;
  chargeTimer560=0;extensionBudget54e=0;chargeState6f7=0;releaseSubphase542=0;
  freshInput5bc=0;releaseCount=0;contactFlags709=0;
  equipment1d74=0;equipment1d75=0;equipment1d94=0;equipment1d95=0;
  /** Opcode0a kind0 skips registration. Status14/255 is metadata only; its
   * original43d/6f8 conditional storage/consumer is not bound here. */
  statusId=14;statusArg=255;
  captureBlocked6b8=false;
  /** Original pitch anchor is JOINT1. No animated transform is available;
   * the explicit null seam uses verified bind joint1 height129.60008239746094, not animated pose. */
  joint1AimAnchor:Vec3|null=null;
  lastGroundProbe:0|1=0;exitKind:'landing'|'air-return'|'ground-return'|null=null;
  get phase(){return this.actor.fbPhaseSlots[0]??0;} set phase(v:number){this.actor.fbPhaseSlots[0]=v;}
  get heading72(){return this.actor.heading;} set heading72(v:number){this.actor.heading=v;}
  get activeYaw(){return this.actor.activeYaw;} set activeYaw(v:number){this.actor.activeYaw=v;}
  get lockYaw(){return this.actor.lockYaw;} set lockYaw(v:number){this.actor.lockYaw=v;}
  get pos(){return this.actor.pos;} set pos(v:Vec3){this.actor.pos=v;}
  get savedGroundPos(){return this.actor.targetCache5e8;} set savedGroundPos(v:Vec3){this.actor.targetCache5e8=v;}
  get motion(){return this.actor.motion;} set motion(v:Vec3){this.actor.motion=v;}
  get hSpeed(){return this.actor.hSpeed;} set hSpeed(v:number){this.actor.hSpeed=v;}
  get yVel(){return this.actor.yVel;} set yVel(v:number){this.actor.yVel=v;}
  get hDecel(){return this.actor.hDecel;} set hDecel(v:number){this.actor.hDecel=v;}
  get gravityCoeff(){return this.actor.gravityCoeff;} set gravityCoeff(v:number){this.actor.gravityCoeff=v;}
  get shift18da(){return this.actor.steerYaw;} set shift18da(v:number){this.actor.steerYaw=v;}
  get streamSlot6ea(){return this.actor.streamSlot;} set streamSlot6ea(v:number){this.actor.streamSlot=v;}
  get dashStrength1d0f(){return this.actor.dashStrength1d0f;} set dashStrength1d0f(v:number){this.actor.dashStrength1d0f=v;}
  get contactP0(){return this.actor.contactP0;} set contactP0(v:number){this.actor.contactP0=v;}
  get wallContact(){return this.actor.wallContact;} set wallContact(v:number){this.actor.wallContact=v;}
  get actionFlag73f(){return this.actor.housekeeping73f;} set actionFlag73f(v:number){this.actor.housekeeping73f=v;}
  get controlWord(){return this.actor.controlWord;} set controlWord(v:number){this.actor.controlWord=v;}
  get landingTimer694(){return this.actor.stateTimer;} set landingTimer694(v:number){this.actor.stateTimer=v;}
  get target():object|null{return this.actor.lockTarget??null;}
  set target(v:object|null){this.actor.lockTarget=v as Vec3|null;if(v===null)this.targetUid=null;}
  get descriptorGravity6c(){return this.actor.descriptor?.handlerData6c??-1;}
  get dt(){return this.actor.dt;}
}
const states=new WeakMap<RomActor,GRedChargeState>();
export function getGRedChargeState(a:RomActor){return states.get(a);}
export function prepareGRedCharge(a:RomActor,targetUid:string|null,point:Vec3){
  const s=new GRedChargeState(a,targetUid,point);states.set(a,s);return s;
}
export function clearGRedCharge(a:RomActor):void{const s=states.get(a);if(s)s.chargeState6f7=0;states.delete(a);}
function groundProbe(s:GRedChargeState):number {
  const a=s.actor,r=a.physicsRuntime?.probeMotion?.(a.savedGroundPos,a.pos,a.yVel)??a.physicsRuntime?.clampToGround(a.pos,a.yVel);
  if(!r){s.lastGroundProbe=0;return 0;}
  if('y' in r&&typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;return s.lastGroundProbe;
}
/** 6d1a8/6e39c seek saved524 even after target loss. BAM trig is a host
 * adapter; signed f32 descriptorAE*dt approach is retained locally. */
function aim(s:GRedChargeState,pitch:boolean):void {
  const a=s.actor,t=s.aimTarget524,p=pitch?(s.joint1AimAnchor??{x:a.pos.x,y:a.pos.y+129.60008239746094*a.modelScale*a.sizeScale,z:a.pos.z}):a.pos;
  const angle=toS16(Math.trunc(f(f(Math.atan2(pitch?t.y-p.y:t.x-p.x,
    pitch?Math.hypot(t.x-p.x,t.z-p.z):t.z-p.z))*10430.3779296875)));
  const desired=pitch?Math.max(-0x4000,Math.min(0x4000,toS16(-toS16(a.bodyPitch)-angle))):angle;
  const current=toS16(pitch?a.steerYaw:a.heading),diff=toS16(desired-current);
  const step=toS16(Math.trunc(f(toS16(a.descriptor?.turnStep1??3072)*a.dt)));
  const next=Math.abs(diff)<=step?desired:toS16(current+(diff<0?-step:step));
  if(pitch)a.steerYaw=next;
  else {a.activeYaw=desired;a.turnErrorYaw=toS16(desired-next);a.heading=next;a.lockYaw=next;}
}
export function stepGRedCharge(a:RomActor,ctx:StreamContext):void {
  const s=states.get(a);if(!s||a.actionIndex!==3||a.variantIndex!==0)return;
  const h:GredChargeHooks={
    face6d1a8:()=>aim(s,false),pitch6e39c:()=>aim(s,true),
    setupCallback:()=>{a.lockYaw=a.heading;a.yVel=8;a.gravityCoeff=0;},
    releaseCallback:()=>{s.releaseCount++;ctx.onFamilyProjectile?.(a,0x800e19a8,15);},
    startStream:(_s,m,g,slot,r)=>startStream(a,m,g,slot,r),tickStream:(_s,m)=>tickStream(a,m,ctx),
    groundProbe677b0:()=>groundProbe(s),physics67310:(_s,g,y)=>integratePhysicsPrimary(g,a,y),
    landing6a750:()=>{s.exitKind='landing';dispatchUpperBodyCue(a,7);},
    airReturn6a5a4:()=>{s.exitKind='air-return';s.actor.return590=1;s.actor.return690=0;s.actor.return71b=0;romAirKnockoutReturn(a);},
    groundReturn6a474:()=>{s.exitKind='ground-return';romGroundIdleReturn(a);},
  };
  tickGredCharge(s,GRED_CHARGE_CONFIG,h);
}
export function startGRedChargeStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s||a.actionIndex!==3||a.variantIndex!==0||group!==4||slot!==2)return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;
  s.stream=createGRedChargeStream(a.dt);
  if(s.streamMask&1){a.wallContact=0;a.contactP0=0;a.contactP1=0;a.streamHold1b03=1;
    // The hook observes metadata; bridge explicitly skips HIT0 registration.
    ctx.onArmHit?.(a,0,14,255);}
  if(s.streamMask&2){a.dashStrength1d0f=0;a.faceGate1d10=1;
    a.controlWord=(a.controlWord&0xfffff00f)|0x40;s.contactFlags709|=1;}
  ctx.onPlayAnim?.(a,4,1,false);return true;
}
export function tickGRedChargeStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const e=tickGRedChargeStream(s.stream,a.dt);
  if(s.streamMask&1){a.streamHold1b03=s.stream.blendMode;
    if(e.contact!==undefined){a.contactP0=e.contact;a.parts[0]!.stateByte=e.contact;}
    if(e.equipment){s.equipment1d74=s.equipment1d94=e.equipment[0];s.equipment1d75=s.equipment1d95=e.equipment[1];}
    if(e.completed)a.wallContact=1;}
  if(s.streamMask&2){if(e.dashStrength!==undefined)a.dashStrength1d0f=e.dashStrength;if(e.faceGate!==undefined)a.faceGate1d10=e.faceGate;}
  if(e.animation)ctx.onPlayAnim?.(a,e.animation[0],e.animation[1],false);
  if(e.completed)for(let p=0;p<a.parts.length;p++)if(s.streamMask&(1<<p)){a.parts[p]!.streamPtr=-1;a.parts[p]!.active=0;}
  return true;
}
