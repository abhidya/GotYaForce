/** Bounded G BLACK action3/v0 ->179d20. This state is separate from
 * RED/NEO179814: no live beam pointer, duration or button-edge extension.
 * Root target/part anchor and floor geometry remain explicit host adapters. */
import type {RomActor,Vec3} from './rom/actor.js';
import {stepTargetYaw,stepPartTargetPitch,type RomHelperScratch} from './rom/helpers.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {romAirKnockoutReturn} from './families/shared-idle-return.js';
import {tickGblackCharge,GBLACK_CHARGE_CONFIG,type GblackChargeState,type GblackChargeHooks} from './families/gblack-charge-engine.js';
import {createGBlackChargeStream,tickGBlackChargeStream,type GBlackChargeStream} from './gblackChargeStream.js';
type Actor=RomActor & RomHelperScratch & {grounded?:boolean;return590?:number;return690?:number;return71b?:number};
export class GBlackChargeState implements GblackChargeState {
  constructor(readonly actor:Actor,public targetUid:string|null){
    if(actor.borgNumber!==0x62a)throw Error('Unadmitted BLACK charge family');
    this.poseAccum7c={get x(){return actor.poseAccum7c;},set x(v:number){actor.poseAccum7c=v;},
      get y(){return actor.poseAccum7e;},set y(v:number){actor.poseAccum7e=v;},
      get z(){return actor.poseAccum80;},set z(v:number){actor.poseAccum80=v;}};
  }
  readonly family='black' as const;readonly poseAccum7c:Vec3;
  stream:GBlackChargeStream|null=null;streamMask=0;
  /** This source branch input is not inferred from projectile contact. */
  subphase541=0;setupCount=0;
  contactFlags709=0;flags57a=0;flags57b=0;
  lastGroundProbe:0|1=0;exitKind:'early'|'stream-end'|null=null;
  get phase(){return this.actor.fbPhaseSlots[0]??0;} set phase(v:number){this.actor.fbPhaseSlots[0]=v;}
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
  get faceGate1d10(){return this.actor.faceGate1d10;} set faceGate1d10(v:number){this.actor.faceGate1d10=v;}
  get contactP0(){return this.actor.contactP0;} set contactP0(v:number){this.actor.contactP0=v;}
  get wallContact(){return this.actor.wallContact;} set wallContact(v:number){this.actor.wallContact=v;}
  get actionFlag73f(){return this.actor.housekeeping73f;} set actionFlag73f(v:number){this.actor.housekeeping73f=v;}
  get controlWord(){return this.actor.controlWord;} set controlWord(v:number){this.actor.controlWord=v;}
  get landingTimer694(){return this.actor.stateTimer;} set landingTimer694(v:number){this.actor.stateTimer=v;}
  get descriptorGravity6c(){return this.actor.descriptor?.handlerData6c??-1;}
  get dt(){return this.actor.dt;}
}
const states=new WeakMap<RomActor,GBlackChargeState>();
export function getGBlackChargeState(a:RomActor){return states.get(a);}
export function prepareGBlackCharge(a:RomActor,targetUid:string|null){const s=new GBlackChargeState(a,targetUid);states.set(a,s);return s;}
export function clearGBlackCharge(a:RomActor):void{states.delete(a);}
function groundProbe(s:GBlackChargeState):number {
  const a=s.actor,r=a.physicsRuntime?.probeMotion?.(a.savedGroundPos,a.pos,a.yVel)??a.physicsRuntime?.clampToGround(a.pos,a.yVel);
  if(!r){s.lastGroundProbe=0;return 0;}
  if('y' in r&&typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;return s.lastGroundProbe;
}
export function stepGBlackCharge(a:RomActor,ctx:StreamContext):void {
  const s=states.get(a);if(!s||a.borgNumber!==0x62a||a.actionIndex!==3||a.variantIndex!==0)return;
  const h:GblackChargeHooks={
    face6d144:()=>{Object.assign(a.aimOrigin518,a.pos);stepTargetYaw(a,0xc1,0,true);},
    pitch6e1ac:()=>{stepPartTargetPitch(a,0xc1);},
    setupCallback:()=>{s.setupCount++;ctx.onFamilyProjectile?.(a,0x8016cc24,0x10);a.hSpeed=0;a.hDecel=0;a.yVel=4;a.gravityCoeff=0;},
    startStream:(_s,m,g,slot,r)=>startStream(a,m,g,slot,r),tickStream:(_s,m)=>tickStream(a,m,ctx),
    groundProbe677b0:()=>groundProbe(s),physics67310:(_s,g,y)=>integratePhysicsPrimary(g,a,y),
    airReturn6a5a4:()=>{s.exitKind=s.contactP0>0&&s.subphase541>0?'early':'stream-end';
      s.actor.return590=1;s.actor.return690=0;s.actor.return71b=0;romAirKnockoutReturn(a);},
  };
  tickGblackCharge(s,GBLACK_CHARGE_CONFIG,h);
}
export function startGBlackChargeStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s||a.actionIndex!==3||a.variantIndex!==0||group!==4||slot!==3)return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;s.stream=createGBlackChargeStream(a.dt);
  if(s.streamMask&1){s.flags57a&=~0xff;s.flags57b&=~0xff;a.defaultGroup=1;
    a.wallContact=0;a.contactP0=0;a.contactP1=0;a.streamHold1b03=2;}
  if(s.streamMask&2){a.dashStrength1d0f=0;a.faceGate1d10=1;
    a.controlWord=(a.controlWord&0xfffff00f)|0x40;s.contactFlags709|=1;}
  ctx.onPlayAnim?.(a,4,2,false);return true;
}
export function tickGBlackChargeStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const e=tickGBlackChargeStream(s.stream,a.dt);
  if(s.streamMask&1){a.streamHold1b03=s.stream.blendMode;
    if(e.contact!==undefined){a.contactP0=e.contact;a.parts[0]!.stateByte=e.contact;}
    if(e.completed)a.wallContact=1;}
  if(s.streamMask&2){if(e.dashStrength!==undefined)a.dashStrength1d0f=e.dashStrength;if(e.faceGate!==undefined)a.faceGate1d10=e.faceGate;}
  if(e.recovery)ctx.onPlayAnim?.(a,0,14,false);
  if(e.completed)for(let p=0;p<a.parts.length;p++)if(s.streamMask&(1<<p)){a.parts[p]!.streamPtr=-1;a.parts[p]!.active=0;}
  return true;
}
