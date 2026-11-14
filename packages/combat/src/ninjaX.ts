/** Scoped Normal/Sasuke/Double Ninja ordinary X: ff2bc/ff30c/ff418/ff4d4 and715f8.
 * Authored part0 state triggers the throw, not a collision. Original animated
 * attachment/support geometry and shared aim helper rounding remain host seams. */
import type {BorgRuntime} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {stepTargetYaw,toS16,allocateWeapon,type RomHelperScratch} from './rom/helpers.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {dispatchUpperBodyCue} from './rom/dispatch.js';
import {romAirKnockoutReturn,romGroundIdleReturn} from './families/shared-idle-return.js';
import {createNinjaXStream,tickNinjaXStream,type NinjaXStream} from './ninjaXStream.js';

type Actor=RomActor&RomHelperScratch&{grounded?:boolean;stateMode?:number};
export const isSourceNinjaX=(id:string):boolean=>id==='pl0000'||id==='pl000a'||id==='pl0003';
export interface DoubleNinjaOwnerState {arm7c8:number;offset7b0:Vec3}
// Source6f7c0/6f8d4 and6f88c access owner7c8/7b0 across actions. The ordinary
// action cleanup must not own their lifetime. A fresh RomActor gets an unarmed
// record on first ordinary-X use; this is not a charged producer or reset policy.
const doubleOwners=new WeakMap<RomActor,DoubleNinjaOwnerState>();
export function getDoubleNinjaOwnerState(a:RomActor):DoubleNinjaOwnerState|undefined{return doubleOwners.get(a);}
function doubleOwner(a:RomActor):DoubleNinjaOwnerState|null{
  if(a.borgNumber!==3)return null;
  let owner=doubleOwners.get(a);
  if(!owner){owner={arm7c8:0,offset7b0:{x:0,y:0,z:0}};doubleOwners.set(a,owner);}
  return owner;
}
export interface NinjaXState {
  /** Reference to persistent owner storage, not action-local clone state.
   * Charged arming, rendering and authoritative reaction reset remain unbound. */
  doubleClone: DoubleNinjaOwnerState|null;
  targetUid:string|null;targetPoint:Vec3|null;noTargetLatch541:number;
  stream:NinjaXStream|null;streamMask:number;callbackCount:number;fireCount:number;
  resourceDenied:boolean;flags6e8:number;flags6e9:number;stateMode71d:number;
  /** Opcode08(1) sets source support offset6d0 to0. Host floor does not model
   * original animated support anchors; the exact shadow stays observable. */
  supportHeight6d0:number|null;lastGroundProbe:0|1;
  exitKind:'landing'|'input'|'stream-end'|null;
}
export function stepNinjaXInput(b:BorgRuntime,held:boolean){
  const input=b.ninjaXInput??={held:false,pressEdge:false,pending:false};
  input.pressEdge=held&&!input.held;input.held=held;input.pending=true;return input;
}
const states=new WeakMap<RomActor,NinjaXState>();
export function getNinjaXState(a:RomActor):NinjaXState|undefined{return states.get(a);}
export function prepareNinjaX(a:RomActor,targetUid:string|null,targetPoint:Vec3|null):NinjaXState{
  const s:NinjaXState={doubleClone:doubleOwner(a),targetUid,targetPoint:targetPoint?{...targetPoint}:null,noTargetLatch541:0,
    stream:null,streamMask:0,callbackCount:0,fireCount:0,resourceDenied:false,flags6e8:0,flags6e9:0,
    stateMode71d:0,supportHeight6d0:null,lastGroundProbe:0,exitKind:null};
  states.set(a,s);return s;
}
/** End only the X action. Generic interruption is not evidence of source6f88c. */
export function clearNinjaX(a:RomActor):void{states.delete(a);}
const f=Math.fround;
function probe(a:Actor,s:NinjaXState):0|1{
  const p=a.physicsRuntime;
  const r=p?.probeMotion?p.probeMotion(a.savedGroundPos,a.pos,a.yVel):p?.clampToGround(a.pos,a.yVel);
  if(!r){s.lastGroundProbe=0;return 0;}
  if('y'in r&&typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;return s.lastGroundProbe;
}
/** The conditional backflip precedes the ammo check, even on a denied throw. */
export function releaseNinjaX(a:Actor,s:NinjaXState,ctx:StreamContext):void{
  s.callbackCount++;
  if(a.dashStrength1d0f!==0){
    a.lockYaw=toS16(a.heading-0x8000);a.hSpeed=10;a.hDecel=0;a.yVel=15;a.gravityCoeff=-1;
  }
  if(!allocateWeapon(a,ctx,2,1,true)){s.resourceDenied=true;return;}
  s.fireCount++;
  ctx.onFamilyProjectile?.(a,0x8007db5c,a.borgNumber===3?1:a.borgNumber===0xa?3:0);
  if(a.borgNumber===3&&(s.doubleClone?.arm7c8??0)!==0)ctx.onFamilyProjectile?.(a,0x8007db5c,2);
}
export function stepNinjaX(a:Actor,ctx:StreamContext):void{
  const s=states.get(a);if(!s)return;
  if(s.noTargetLatch541){s.targetUid=null;a.lockTarget=null;}
  switch(a.fbPhaseSlots[0]??0){
    case 0:{
      a.fbPhaseSlots[0]=1;if(!a.lockTarget)a.activeYaw=a.heading;
      stepTargetYaw(a,0xc1,0,true);
      a.gravityCoeff=a.yVel=a.hDecel=a.hSpeed=0;a.poseAccum80=a.poseAccum7e=a.poseAccum7c=0;
      for(const axis of ['x','y','z'] as const){a.motion[axis]=f(f(a.pos[axis]-a.targetCache5e8[axis])*f(.95));a.pos[axis]=f(a.pos[axis]+a.motion[axis]);}
      probe(a,s);
      const slot=(a.controlWord&0x40)!==0?1:0;a.streamSlot=slot+1;
      startStream(a,0xf,4,slot,-1);a.accumulator80c=0;return;
    }
    case 1:
      tickStream(a,0xf,ctx);stepTargetYaw(a,0xc1,0,true);
      for(const axis of ['x','y','z'] as const){a.motion[axis]=f(a.motion[axis]*f(.95));a.pos[axis]=f(a.pos[axis]+a.motion[axis]);}
      probe(a,s);
      if(a.contactP0>0){a.fbPhaseSlots[0]=2;releaseNinjaX(a,s,ctx);}
      // b22f4 afterimage (motion magnitude>3) is an unbound presentation/RNG seam.
      return;
    case 2:{
      tickStream(a,0xf,ctx);integratePhysicsPrimary(1,a,a.lockYaw);
      const landed=probe(a,s)!==0,air=(a.controlWord&0x40)!==0;
      const landingExit=landed&&air&&a.contactP0<0;
      const inputExit=a.contactP0<0&&(a.inputHeld5d8&0xf0)!==0;
      if(!landingExit&&!inputExit&&a.wallContact===0)return;
      s.exitKind=landingExit?'landing':inputExit?'input':'stream-end';
      a.housekeeping73f=0;a.controlWord&=~3;
      if(landingExit)dispatchUpperBodyCue(a,7);
      else if(!landed)romAirKnockoutReturn(a);
      else if(!air)romGroundIdleReturn(a);
      else dispatchUpperBodyCue(a,7);
      a.stateTimer=f(4+a.dt);return;
    }
  }
}
export function startNinjaXStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean{
  const s=states.get(a);if(!s||group!==4||(slot!==0&&slot!==1))return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;
  s.stream=createNinjaXStream(slot,a.dt);
  if(s.streamMask&1){a.wallContact=0;a.contactP0=0;a.contactP1=0;s.flags6e8=s.flags6e9=0;}
  if(s.streamMask&2){s.stateMode71d=0;s.supportHeight6d0=null;(a as Actor).stateMode=0;a.dashStrength1d0f=0;a.faceGate1d10=1;a.controlWord=(a.controlWord&~0xff0)|0x40;
    if(slot===1)setMode(a,s);}
  a.streamHold1b03=s.stream.blendMode;ctx.onPlayAnim?.(a,4,slot,false);return true;
}
function setMode(a:RomActor,s:NinjaXState):void{
  s.stateMode71d=1;s.supportHeight6d0=0;(a as Actor).stateMode=1;
}
export function tickNinjaXStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean{
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const e=tickNinjaXStream(s.stream,a.dt);
  if(s.streamMask&1){
    if(e.contact!==undefined){a.contactP0=e.contact;a.parts[0]!.stateByte=e.contact;}
    if(e.flags6e8!==undefined)s.flags6e8=e.flags6e8;
  }
  if(s.streamMask&2){
    if(e.dashStrength!==undefined)a.dashStrength1d0f=e.dashStrength;
    if(e.faceGate!==undefined)a.faceGate1d10=e.faceGate;
    if(e.control!==undefined)a.controlWord=(a.controlWord&~0xff0)|(e.control&0xff0);
    if(e.stateMode!==undefined)setMode(a,s);
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
