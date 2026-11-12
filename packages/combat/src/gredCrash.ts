/** Fresh G RED-family neutral ground v0 / airborne v4 X only. Source18e838/18e888/18ea54/
 * 18eb2c/18ec34, g4s0/1/4 and callback18d120. Other X routes retain
 * their prior implementation. Target roots, part-1 aim anchor and floor probes
 * are explicit host geometry adapters, not original animated collision parity. */
import type { RomActor } from './rom/actor.js';
import { startStream, tickStream, type StreamContext } from './rom/stream-vm.js';
import { stepTargetYaw, stepPartTargetPitch, toS16, type RomHelperScratch } from './rom/helpers.js';
import { integratePhysicsPrimary } from './rom/physics.js';
import { dispatchUpperBodyCue } from './rom/dispatch.js';
import { romAirKnockoutReturn } from './families/shared-idle-return.js';
import { refreshTargetVisibility } from './families/shared-aimed-shot-x.js';
import { createGRedCrashStream, tickGRedCrashStream, type GRedCrashStream, type GRedCrashFamily } from './gredCrashStream.js';

type Actor = RomActor & RomHelperScratch & {
  grounded?: boolean; return590?: number; return690?: number; return71b?: number;
  movementTrailFlag1d9b?: number; launchYaw1db0?: number; launchSpeed1dac?: number;
};
const f = Math.fround;
/** Original all three descriptors138/144/150 -> actor86c/878/884. */
export const G_RED_CRASH_RANGE_ROWS = [1000, 1200, 1300] as const;
export interface GRedCrashState {
  family: GRedCrashFamily;
  targetUid: string | null;
  noTargetLatch541: number;
  forceRange1dd80: boolean;
  /** Explicit source6b8 admission gate; host does not infer it from hitstun. */
  captureBlocked6b8: boolean;
  stream: GRedCrashStream | null;
  streamMask: number;
  pendingContact: number;
  input1d9: number;
  acceptedContactCount: number;
  hitActivationSerial: number;
  hitRecordIndex: number | null;
  hitRenewalCount: number;
  callbackRefreshCount: number;
  contactFlags709: number;
  flags6e8: number;
  flags6e9: number;
  callbackState6f6: number;
  contactMetadata: number | null;
  lastGroundProbe: 0 | 1;
  exitKind: 'landing' | 'stream-end' | 'timer' | null;
  /** Refreshes current selected target without resetting the actor's in-flight pose. */
  onRefreshTarget?: () => void;
}
const states = new WeakMap<RomActor, GRedCrashState>();
export function getGRedCrashState(actor: RomActor): GRedCrashState | undefined { return states.get(actor); }
export function prepareGRedCrash(actor: RomActor, targetUid: string | null): GRedCrashState {
  const family=actor.borgNumber===0x615?'red':actor.borgNumber===0x629?'neo':'black';
  const state: GRedCrashState = { family, targetUid, noTargetLatch541: 0, forceRange1dd80: false,
    captureBlocked6b8: false, stream: null, streamMask: 0, pendingContact: 0, input1d9: 0,
    acceptedContactCount: 0, hitActivationSerial: 0, hitRecordIndex: null, hitRenewalCount: 0,
    callbackRefreshCount: 0, contactFlags709: 0, flags6e8: 0, flags6e9: 0,
    callbackState6f6: 0, contactMetadata: null, lastGroundProbe: 0, exitKind: null };
  states.set(actor,state); return state;
}
export function clearGRedCrash(actor: RomActor): void { states.delete(actor); }
export function acceptGRedCrashContact(actor: RomActor, admitted: GRedCrashState): void {
  if (states.get(actor) !== admitted) return;
  admitted.pendingContact |= 0x10; admitted.acceptedContactCount++;
}
export function beginGRedCrashTick(actor: RomActor): void {
  const state=states.get(actor); if (!state) return;
  state.input1d9=state.pendingContact; state.pendingContact=0;
}
function rangeAndFallback(a: Actor, s: GRedCrashState): void {
  const row=((a.prevActionIndex<<24)>>24)%3;
  const range=G_RED_CRASH_RANGE_ROWS[row];
  if (range === undefined) throw new Error('G RED X has an unbound source range row');
  const target=a.lockTarget;
  const admitted=!!target && (s.forceRange1dd80 ||
    Math.hypot(target.x-a.pos.x,target.z-a.pos.z)<=range*a.modelScale);
  if (!admitted) {
    s.noTargetLatch541=1; s.targetUid=null; a.lockTarget=null; a.activeYaw=a.lockYaw;
  }
  if (!a.lockTarget) a.activeYaw=(a.controlWord&0xa0)===0?a.heading:a.lockYaw;
}
function callback(a: Actor, s: GRedCrashState, kind: 1 | 2, arg: number, ctx: StreamContext): void {
  if (kind===2) {
    s.callbackRefreshCount++;
    s.onRefreshTarget?.();
    if (s.captureBlocked6b8) {s.targetUid=null;a.lockTarget=null;a.visibilityTarget=null;}
    refreshTargetVisibility(a); ctx.onRefreshTargetVisibility?.(a);
    s.noTargetLatch541=0; rangeAndFallback(a,s);
  } else if (arg!==4) {
    // Source callback1's persistent6f6 shadow. Arg4 is presentation only;
    // neither this shadow nor the unbound original FX invents combat damage.
    s.callbackState6f6=arg+1;
  }
  ctx.onIndirect?.(a,kind,arg);
}
function groundProbe(a: Actor, s: GRedCrashState): 0 | 1 {
  const result=a.physicsRuntime?.probeMotion?.(a.savedGroundPos,a.pos,a.yVel)
    ??a.physicsRuntime?.clampToGround(a.pos,a.yVel);
  if (!result) {s.lastGroundProbe=0;return 0;}
  if ('y' in result && typeof result.y==='number') a.pos.y=result.y;
  a.yVel=result.velY;a.grounded=result.grounded;
  // Source77b0 returns1 for accepted landing. Flat host grounded is a bounded
  // substitute for the original normal/step-height/support-object tests.
  s.lastGroundProbe=result.grounded?1:0;return s.lastGroundProbe;
}
function pitch(a: Actor): void {
  if (!a.lockTarget) a.steerYaw=toS16(Math.trunc(f(toS16(a.steerYaw)*f(.9))));
  else stepPartTargetPitch(a,0xc1); // actor768 rate, explicit root-anchor fallback.
}
function teardown(a: Actor, s: GRedCrashState, landing: boolean): void {
  s.callbackState6f6=0;a.housekeeping73f=0;a.controlWord&=~3;
  s.exitKind=landing?'landing':s.family==='red'?'stream-end':'timer';
  if (landing) {dispatchUpperBodyCue(a,7);a.stateTimer=f(1+a.dt);}
  else {
    a.return590=1;a.return690=0;a.return71b=0;
    if(a.movementTrailFlag1d9b){a.lockYaw=toS16((a.launchYaw1db0??0)+a.heading);a.hSpeed=a.launchSpeed1dac??0;}
    romAirKnockoutReturn(a);
  }
}
export function stepGRedCrash(a: Actor, ctx: StreamContext): void {
  const s=states.get(a);if(!s)return;
  if(s.noTargetLatch541){s.targetUid=null;a.lockTarget=null;}
  switch(a.fbPhaseSlots[0]??0){
    case 0:
      a.fbPhaseSlots[0]=1;rangeAndFallback(a,s);stepTargetYaw(a,0xc1,0,true);
      a.streamSlot=s.family==='red'?1:s.family==='neo'?2:5;
      a.hSpeed=0;a.hDecel=0;a.yVel=s.family==='red'?4:0;a.gravityCoeff=0;
      if(s.family!=='red')a.poseAccum7c=a.poseAccum7e=a.poseAccum80=0;
      for(const axis of ['x','y','z'] as const){
        a.motion[axis]=f(f(a.pos[axis]-a.targetCache5e8[axis])*f(.95));
        a.pos[axis]=f(a.pos[axis]+a.motion[axis]);
      }
      groundProbe(a,s);startStream(a,0xf,4,a.streamSlot-1,-1);return;
    case 1:
      if(s.input1d9)s.contactMetadata=0x12; //107a0 metadata consumer remains unbound.
      tickStream(a,0xf,ctx);stepTargetYaw(a,0xc1,0,true);
      if(a.faceGate1d10!==0)pitch(a);
      integratePhysicsPrimary(1,a,a.lockYaw);
      for(const axis of ['x','y','z'] as const){a.motion[axis]=f(a.motion[axis]*f(.95));a.pos[axis]=f(a.pos[axis]+a.motion[axis]);}
      groundProbe(a,s);
      if(a.contactP0>0){a.fbPhaseSlots[0]=2;a.motion={x:0,y:10,z:60};}
      return;
    case 2: {
      if(s.input1d9)a.faceGate1d10=0;
      tickStream(a,0xf,ctx);
      if(a.faceGate1d10!==0){stepTargetYaw(a,0xc1,0,true);pitch(a);}
      a.motion.x=f(a.motion.y*a.dt+a.motion.x);if(a.motion.z<a.motion.x)a.motion.x=a.motion.z;
      const angle=f(toS16(a.steerYaw)*.0000958738019107841);
      a.hSpeed=f(a.motion.x*f(Math.cos(angle)));a.yVel=f(-a.motion.x*f(Math.sin(angle)));
      integratePhysicsPrimary(1,a,a.lockYaw);groundProbe(a,s);
      if(a.contactP0<0){a.fbPhaseSlots[0]=3;a.handlerTimer=120;a.gravityCoeff=a.descriptor?.handlerData6c??-1;}
      return;
    }
    case 3:
      tickStream(a,0xf,ctx);
      a.steerYaw=toS16(Math.trunc(f(toS16(a.steerYaw)*f(.9))));
      integratePhysicsPrimary(1,a,a.lockYaw);
      if(groundProbe(a,s)!==0)teardown(a,s,true);
      else if(s.family==='red'){if(a.wallContact!==0)teardown(a,s,false);}
      else {a.handlerTimer=f(a.handlerTimer-a.dt);if(a.handlerTimer<0)teardown(a,s,false);}
  }
}
export function startGRedCrashStream(actor: RomActor, group: number, slot: number, mask: number, ctx: StreamContext): boolean {
  const s=states.get(actor);if(!s||group!==4||slot!==(s.family==='red'?0:s.family==='neo'?1:4))return false;
  s.streamMask=mask&actor.weaponPartMask;if(s.streamMask===0)return false;
  s.stream=createGRedCrashStream(actor.dt,s.family);
  if(s.streamMask&1){actor.wallContact=0;actor.contactP0=0;actor.contactP1=0;
    s.flags6e8=s.family==='red'?0:2;s.flags6e9=0;ctx.onArmHit?.(actor,s.family==='red'?15:29,0,255);}
  if(s.streamMask&2){actor.dashStrength1d0f=0;actor.faceGate1d10=s.family==='red'?0:1;
    actor.controlWord=(actor.controlWord&~0xff0)|0x40;s.contactFlags709=1;}
  actor.streamHold1b03=s.stream.blendMode;
  ctx.onPlayAnim?.(actor,4,s.family==='red'?0:3,false);return true;
}
export function tickGRedCrashStreamPart(actor: RomActor,index: number,ctx: StreamContext): boolean {
  const s=states.get(actor);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  const event=tickGRedCrashStream(s.stream,actor.dt);
  if(s.streamMask&1){
    if(event.contact!==undefined){actor.contactP0=event.contact;actor.parts[0]!.stateByte=event.contact;}
    if(event.aux!==undefined)actor.contactP1=event.aux;
    if(event.flags6e8!==undefined)s.flags6e8=event.flags6e8;
    for(const cb of event.callbacks??[])callback(actor,s,cb.callback,cb.arg,ctx);
  }
  if(s.streamMask&2){
    if(event.strength!==undefined)actor.dashStrength1d0f=event.strength;
    if(event.faceGate!==undefined)actor.faceGate1d10=event.faceGate;
  }
  if(event.recovery)ctx.onPlayAnim?.(actor,0,14,false);
  actor.streamHold1b03=s.stream.blendMode;
  if(event.completed){
    for(let part=0;part<actor.parts.length;part++)if(s.streamMask&(1<<part)){actor.parts[part]!.streamPtr=-1;actor.parts[part]!.active=0;}
    if(s.streamMask&1)actor.wallContact=1;
  }
  return true;
}
