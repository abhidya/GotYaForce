/** Scoped Switching Ninja ordinary X: 147180/147280/14734c.
 * Authored part0 state triggers the throw, not a collision. Original animated
 * attachment/support geometry and shared aim helper rounding remain host seams. */
import type {BorgRuntime} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {stepTargetYaw,allocateWeapon,stepAfterimage,type RomHelperScratch} from './rom/helpers.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {dispatchUpperBodyCue} from './rom/dispatch.js';
import {romAirKnockoutReturn,romGroundIdleReturn} from './families/shared-idle-return.js';
import {createSwitchingXStream,tickSwitchingXStream,type SwitchingXStream} from './switchingXStream.js';

type Actor=RomActor&RomHelperScratch&{grounded?:boolean;stateMode?:number};
export const isSourceSwitchingX=(id:string):boolean=>id==='pl0009';
export interface SwitchingXState {
  targetUid:string|null;targetPoint:Vec3|null;noTargetLatch541:number;
  stream:SwitchingXStream|null;streamMask:number;callbackCount:number;fireCount:number;
  captureFlagsD0:number;resourceDenied:boolean;flags6e8:number;flags6e9:number;stateMode71d:number;
  /** Opcode08(1) sets source support offset6d0 to0. Host floor does not model
   * original animated support anchors; the exact shadow stays observable. */
  supportHeight6d0:number|null;lastGroundProbe:0|1;
  exitKind:'landing'|'input'|'stream-end'|null;
}
export function stepSwitchingXInput(b:BorgRuntime,held:boolean){
  const input=b.switchingXInput??={held:false,pressEdge:false,pending:false};
  input.pressEdge=held&&!input.held;input.held=held;input.pending=true;return input;
}
const states=new WeakMap<RomActor,SwitchingXState>();
export function getSwitchingXState(a:RomActor):SwitchingXState|undefined{return states.get(a);}
export function prepareSwitchingX(a:RomActor,targetUid:string|null,targetPoint:Vec3|null):SwitchingXState{
  const s:SwitchingXState={targetUid,targetPoint:targetPoint?{...targetPoint}:null,noTargetLatch541:0,
    stream:null,streamMask:0,callbackCount:0,fireCount:0,captureFlagsD0:targetPoint&&Math.hypot(targetPoint.x-a.pos.x,targetPoint.y-a.pos.y,targetPoint.z-a.pos.z)<=5500?4:0,resourceDenied:false,flags6e8:0,flags6e9:0,
    stateMode71d:0,supportHeight6d0:null,lastGroundProbe:0,exitKind:null};
  states.set(a,s);return s;
}
export function clearSwitchingX(a:RomActor):void{states.delete(a);}
const f=Math.fround;
function probe(a:Actor,s:SwitchingXState):0|1{
  const p=a.physicsRuntime;
  const r=p?.probeMotion?p.probeMotion(a.savedGroundPos,a.pos,a.yVel):p?.clampToGround(a.pos,a.yVel);
  if(!r){s.lastGroundProbe=0;return 0;}
  if('y'in r&&typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;return s.lastGroundProbe;
}
/** FUN_80147280 consumes source cell2 only when authored part0 becomes positive. */
export function releaseSwitchingX(a:Actor,s:SwitchingXState,ctx:StreamContext):void{
  s.callbackCount++;
  if(!allocateWeapon(a,ctx,2,1,true)){s.resourceDenied=true;return;}
  s.captureFlagsD0=s.targetPoint&&Math.hypot(s.targetPoint.x-a.pos.x,s.targetPoint.y-a.pos.y,s.targetPoint.z-a.pos.z)<=5500?4:0;
  if(a.borgNumber===9){s.fireCount++;ctx.onFamilyProjectile?.(a,0x801e29fc,0);}
}
export function stepSwitchingX(a:Actor,ctx:StreamContext):void{
  const s=states.get(a);if(!s)return;
  if(s.noTargetLatch541){s.targetUid=null;a.lockTarget=null;}
  switch(a.fbPhaseSlots[0]??0){
    case 0:{
      a.fbPhaseSlots[0]=1;if(!a.lockTarget)a.activeYaw=a.heading;
      stepTargetYaw(a,0xc1,0,true);
      a.gravityCoeff=a.yVel=a.hDecel=a.hSpeed=0;a.poseAccum80=a.poseAccum7e=a.poseAccum7c=0;
      for(const axis of ['x','y','z'] as const){a.motion[axis]=f(f(a.pos[axis]-a.targetCache5e8[axis])*f(.95));a.pos[axis]=f(a.pos[axis]+a.motion[axis]);}
      probe(a,s);
      const slot=(a.controlWord&0x40)!==0?5:4;a.streamSlot=slot+1;
      startStream(a,0xf,4,slot,-1);a.accumulator80c=0;return;
    }
    case 1:
      tickStream(a,0xf,ctx);stepTargetYaw(a,0xc1,0,true);
      for(const axis of ['x','y','z'] as const){a.motion[axis]=f(a.motion[axis]*f(.95));a.pos[axis]=f(a.pos[axis]+a.motion[axis]);}
      probe(a,s);
      if(a.contactP0>0){a.fbPhaseSlots[0]=2;releaseSwitchingX(a,s,ctx);}
      if(Math.hypot(a.motion.x,a.motion.y,a.motion.z)>3)stepAfterimage(a);
      return;
    case 2:{
      tickStream(a,0xf,ctx);integratePhysicsPrimary(1,a,a.lockYaw);
      const landed=probe(a,s)!==0;
      const landingExit=landed&&a.contactP0<0;
      if(!landingExit&&a.wallContact===0)return;
      s.exitKind=landingExit?'landing':'stream-end';
      a.housekeeping73f=0;a.controlWord&=~3;
      if(landingExit)dispatchUpperBodyCue(a,7);
      else if(!landed)romAirKnockoutReturn(a);
      else romGroundIdleReturn(a);
      a.stateTimer=f(8+a.dt);return;
    }
  }
}
export function startSwitchingXStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean{
  const s=states.get(a);if(!s||group!==4||(slot!==4&&slot!==5))return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;
  s.stream=createSwitchingXStream(slot,a.dt);
  if(s.streamMask&1){a.wallContact=0;a.contactP0=0;a.contactP1=0;s.flags6e8=s.flags6e9=0;}
  if(s.streamMask&2){s.stateMode71d=0;s.supportHeight6d0=null;(a as Actor).stateMode=0;a.dashStrength1d0f=0;a.faceGate1d10=1;a.controlWord=(a.controlWord&~0xff0)|0x40;
    if(slot===5)setMode(a,s);}
  a.streamHold1b03=s.stream.blendMode;ctx.onPlayAnim?.(a,4,slot-2,false);return true;
}
function setMode(a:RomActor,s:SwitchingXState):void{
  s.stateMode71d=1;s.supportHeight6d0=0;(a as Actor).stateMode=1;
}
export function tickSwitchingXStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean{
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const e=tickSwitchingXStream(s.stream,a.dt);
  if(s.streamMask&1){
    if(e.contact!==undefined){a.contactP0=e.contact;a.parts[0]!.stateByte=e.contact;}
  }
  if(s.streamMask&2){
    if(e.dashStrength!==undefined)a.dashStrength1d0f=e.dashStrength;
    if(e.faceGate!==undefined)a.faceGate1d10=e.faceGate;
    if(e.control!==undefined)a.controlWord=(a.controlWord&~0xff0)|(e.control&0xff0);
  }
  if(e.animation){
    // Opcode01 resets71d before its support query; non-forced6d0 remains
    // unbound because the host floor has no original animated support anchors.
    if(s.streamMask&2){s.stateMode71d=0;s.supportHeight6d0=null;(a as Actor).stateMode=0;}
    ctx.onPlayAnim?.(a,e.animation[0],e.animation[1],false);
  }
  a.streamHold1b03=s.stream.blendMode;
  if(e.completed){for(let i=0;i<a.parts.length;i++)if(s.streamMask&(1<<i)){a.parts[i]!.streamPtr=-1;a.parts[i]!.active=0;}if(s.streamMask&1)a.wallContact=1;}
  return true;
}
