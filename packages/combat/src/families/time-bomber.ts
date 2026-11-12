/** Time Bomber type2/action0 variants0/1/3, including airborne fallback4.
 * 8013088c -> 801309b8 -> 801313bc -> 80130ad0; original stream803351e4.
 * This clock retains the animation-end/relative-wait distinction lost by the
 * generated event schedule. No actor attack HIT is armed by this stream.
 */
import type { RomActor } from '../rom/actor.js';
import type { StreamContext } from '../rom/stream-vm.js';
import { allocateWeapon, stepTargetYaw, groundSnapRevert, toS16, stepAfterimage, type RomHelperScratch } from '../rom/helpers.js';
import { integratePhysicsPrimary, groundProbe77b0 } from '../rom/physics.js';
import { dispatchCommandRecord, dispatchFullBodyCue, dispatchUpperBodyCue } from '../rom/dispatch.js';
import { romGroundIdleReturn, romAirKnockoutReturn } from './shared-idle-return.js';

export interface TimeBomberAction {
  fallback?:boolean; mask?:number; blendElapsed:number; frame:number; stage:'windup'|'wait'|'tail'|'done'; wait:number;
  timer560:number; timer558:number; timer55c:number; remaining6ef:number;
}
type Actor = RomActor & { timeBomberAction?:TimeBomberAction };
export function isTimeBomberGroundAction(actor:RomActor):boolean {
  return actor.borgNumber===0x106 && actor.actionIndex===0 && actor.variantIndex===0;
}
function carry(actor:RomActor):void {
  const k=Math.fround(.95);
  actor.motion.x*=k; actor.motion.y*=k; actor.motion.z*=k;
  actor.pos.x+=actor.motion.x; actor.pos.y+=actor.motion.y; actor.pos.z+=actor.motion.z;
  groundSnapRevert(actor);
}
/** Source animation mode6 blends for override4+1 frames. Opcode0d does not
 * suppress the immediate animation update, so admission elapsed is2 at dt1.
 * AOBJ EndFrame20/9 are original MOT values, not baked sample counts21/10. */
function tickActionStream(actor:RomActor,s:TimeBomberAction,ctx:StreamContext,dt:number):void {
  if(s.stage==='windup') {
    if(s.frame>=20) {s.stage='wait';s.wait=8;return;}
    if(actor.streamHold1b03!==0) {
      s.blendElapsed+=dt;
      if(s.blendElapsed>=5) actor.streamHold1b03=0;
      // Mode1 updates its animation clock during blending; mode6 does not.
      if(s.fallback)s.frame+=dt;
    } else s.frame+=dt;
  } else if(s.stage==='wait') {
    s.wait-=dt;
    if(s.wait<=0) {
      s.stage='tail';s.frame=s.fallback?0:dt;
      actor.contactP0=-1;actor.parts[0]!.stateByte=-1;
      ctx.onPlayAnim?.(actor,s.fallback?0:2,s.fallback?14:34,true);
    }
  } else if(s.stage==='tail') {
    if(s.frame>=(s.fallback?15:9)) {s.stage='done';actor.wallContact=1;for(let i=0;i<actor.parts.length;i++)if((s.mask??15)&(1<<i))actor.parts[i]!.streamPtr=-1;}
    else s.frame+=dt;
  }
}
export function timeBomberGroundAction(actor:RomActor,ctx:StreamContext):void {
  const a=actor as Actor;
  const phase=actor.fbPhaseSlots[0]??0;
  if(phase===0) {
    const s:TimeBomberAction={blendElapsed:2*actor.dt,frame:0,stage:'windup',wait:0,
      timer560:20,timer558:4,timer55c:0,remaining6ef:5};
    a.timeBomberAction=s;
    actor.fbPhaseSlots[0]=1;
    actor.wallContact=0;actor.contactP0=1;actor.streamHold1b03=6;
    for(const part of actor.parts){part.streamPtr=Number.MAX_SAFE_INTEGER;part.active=1;}
    actor.parts[0]!.stateByte=1;
    ctx.onPlayAnim?.(actor,2,30,true);
    stepTargetYaw(actor,0xc1);
    actor.controlWord&=0xffffff4f;
    actor.hSpeed=0;actor.yVel=0;actor.hDecel=0;actor.gravityCoeff=0;
    actor.poseAccum7c=0;actor.poseAccum7e=0;actor.poseAccum80=0;actor.accumulator80c=0;
    actor.motion={x:actor.pos.x-actor.targetCache5e8.x,y:actor.pos.y-actor.targetCache5e8.y,z:actor.pos.z-actor.targetCache5e8.z};
    carry(actor);
    return;
  }
  const s=a.timeBomberAction;if(!s)return;
  if(phase===1) {
    tickActionStream(actor,s,ctx,actor.contactP0!==0&&actor.streamHold1b03===0?0:actor.dt);
    const ready=stepTargetYaw(actor,0xc1);
    if(!ready)s.timer560-=actor.dt;
    if((ready||s.timer560<=0)&&actor.contactP0!==0&&actor.streamHold1b03===0) {
      actor.fbPhaseSlots[0]=2;s.timer560=20;s.timer558=4;s.timer55c=0;
      if(s.remaining6ef>0&&allocateWeapon(actor,ctx,2,1,true))
        ctx.onFamilyProjectile?.(actor,0x800fe668,2);
      s.remaining6ef=0;
    }
    carry(actor);return;
  }
  if(phase===2) {
    if(s.timer55c<=0)tickActionStream(actor,s,ctx,actor.dt);else s.timer55c-=actor.dt;
    if(s.timer558>0)s.timer558-=actor.dt;
    if((actor.inputHeld5d8&0xf0)!==0||(actor.inputEdge5d4&1)!==0||actor.wallContact!==0) {
      actor.housekeeping73f=0;actor.controlWord&=~3;romGroundIdleReturn(actor);
      for(const part of actor.parts)part.streamPtr=-1;
    } else carry(actor);
  }
}

/** Source variants1/3 own part0 only. The bridge composes this with host locomotion
 * until the host movement states are continuously mirrored into ROM part1.
 * Source control10 selects group2 slot15, neutral slot18; both alias803351e4
 * byte-for-byte (including animation triplets31/30/32 and35/34/36). This
 * bounded renderer still presents their center animations30/34 only. */
export function isTimeBomberPartAction(actor:RomActor):boolean {
  return actor.borgNumber===0x106 && actor.actionIndex===0 && (actor.variantIndex===1 || actor.variantIndex===3);
}
/** zz_006dee8_(actor,1): missing target resolves to heading (relative yaw zero),
 * unlike the older shared helper's invalid-target sentinel. */
function airAim(actor:RomActor):number {
  const a=actor as RomActor & RomHelperScratch;
  const target=a.lockTarget;
  const relative=target ? toS16(Math.round(Math.atan2(target.x-actor.aimOrigin518.x,
    target.z-actor.aimOrigin518.z)*0x10000/(2*Math.PI))-actor.heading) : 0;
  if(Math.abs(relative)>0x4800)return -1;
  const desired=Math.max(-0x4000,Math.min(0x4000,relative));
  const current=toS16(a.aimRoll1dfc??0);
  const difference=desired-current;
  if(Math.abs(difference)<=0x800){a.aimRoll1dfc=desired;return 1;}
  a.aimRoll1dfc=toS16(current+Math.sign(difference)*0x800);return 0;
}
export function timeBomberAirAction(actor:RomActor,ctx:StreamContext):void {
  const a=actor as Actor;
  const phase=actor.fbPhaseSlots[0]??0;
  if(phase===0){
    a.timeBomberAction={mask:1,blendElapsed:2*actor.dt,frame:0,stage:'windup',wait:0,
      timer560:20,timer558:4,timer55c:0,remaining6ef:5};
    actor.fbPhaseSlots[0]=1;
    actor.wallContact=0;actor.contactP0=1;actor.streamHold1b03=6;
    actor.parts[0]!.streamPtr=Number.MAX_SAFE_INTEGER;actor.parts[0]!.active=1;
    actor.parts[0]!.stateByte=1;
    ctx.onPlayAnim?.(actor,2,30,true);
    return;
  }
  const s=a.timeBomberAction;if(!s)return;
  if(phase===1){
    const ready=airAim(actor);
    tickActionStream(actor,s,ctx,actor.contactP0!==0&&actor.streamHold1b03===0?0:actor.dt);
    if(ready<0){
      // Source redispatches variant4 in air or variant0 on the floor. The
      // airborne fallback is implemented below, never as a generic projectile.
      const air=(actor.controlWord&0x40)!==0;
      dispatchCommandRecord(actor,{cueId:air?45:44,stateMode:3,actionIndex:0,variantIndex:air?4:0});
      return;
    }
    if(ready===0)s.timer560-=actor.dt;
    if((ready>0||s.timer560<=0)&&actor.contactP0!==0&&actor.streamHold1b03===0){
      actor.fbPhaseSlots[0]=2;s.timer560=20;s.timer558=4;s.timer55c=0;
      if(s.remaining6ef>0&&allocateWeapon(actor,ctx,2,1,true))
        ctx.onFamilyProjectile?.(actor,0x800fe668,2);
      s.remaining6ef=0;
    }
    return;
  }
  if(phase===2){
    if(s.timer55c<=0)tickActionStream(actor,s,ctx,actor.dt);else s.timer55c-=actor.dt;
    if(s.timer558>0)s.timer558-=actor.dt;
    if((actor.inputHeld5d8&0xf0)!==0||actor.wallContact!==0){
      actor.housekeeping73f=0;actor.controlWord&=~3;
      dispatchFullBodyCue(actor,actor.ubCue);
      actor.parts[0]!.streamPtr=-1;
    }
  }
}

/** Host floor-contact adapter for 00677b0. The battle does not yet supply the
 * source surface-normal probe; use its existing floor clamp, without the
 * ground-only off-mesh position revert. Direct ROM fixtures can supply the
 * richer probe and retain its wall/slope handling. */
function fallbackGroundProbe(actor:RomActor):boolean {
  const floor=actor.physicsRuntime;
  if(floor && 'surfaceProbe' in floor)return groundProbe77b0(actor)!==0;
  if(!floor)return false;
  const result=floor.clampToGround(actor.pos,actor.yVel);
  actor.pos.y=result.y;actor.yVel=result.velY;
  return result.grounded;
}

/** The proven behind-target redispatch of variant3: full-body variant4, slot21.
 * Opcode01 mode1 counts animation frames during its five-tick blend. Its tail
 * is an explicit frame15 wait, not the MOT END or the 16-tick blend duration. */
export function timeBomberAirFallback(actor:RomActor,ctx:StreamContext):void {
  const a=actor as Actor & RomHelperScratch;
  a.aimRoll1dfc=toS16(a.aimRoll1dfc??0)>>1;
  const phase=actor.fbPhaseSlots[0]??0;
  if(phase===0){
    actor.fbPhaseSlots[0]=1;
    stepTargetYaw(actor,0x81);
    actor.controlWord&=~0x80;
    integratePhysicsPrimary(1,actor,actor.lockYaw);fallbackGroundProbe(actor);
    a.timeBomberAction={fallback:true,mask:15,blendElapsed:actor.dt,frame:0,stage:'windup',wait:0,
      timer560:20,timer558:4,timer55c:0,remaining6ef:5};
    actor.wallContact=0;actor.contactP0=1;actor.streamHold1b03=1;
    for(const part of actor.parts){part.streamPtr=Number.MAX_SAFE_INTEGER;part.active=1;}
    actor.parts[0]!.stateByte=1;
    ctx.onPlayAnim?.(actor,2,33,true);
    actor.accumulator80c=0;
    return;
  }
  const s=a.timeBomberAction;if(!s)return;
  if(phase===1){
    tickActionStream(actor,s,ctx,actor.contactP0!==0&&actor.streamHold1b03===0?0:actor.dt);
    integratePhysicsPrimary(1,actor,actor.lockYaw);fallbackGroundProbe(actor);
    const ready=stepTargetYaw(actor,0x81);
    if(!ready)s.timer560-=actor.dt;
    if((ready||s.timer560<=0)&&actor.contactP0!==0&&actor.streamHold1b03===0){
      s.timer560=20;s.timer558=4;s.timer55c=0;
      if(s.remaining6ef>0&&allocateWeapon(actor,ctx,2,1,true))
        ctx.onFamilyProjectile?.(actor,0x800fe668,2);
      s.remaining6ef=0;actor.fbPhaseSlots[0]=3;
      // Original pl0106 descriptor +6c, not an invented launch impulse.
      actor.gravityCoeff=-0.699999988079071;
    }
    stepAfterimage(actor);return;
  }
  if(phase===3){
    if(s.timer55c<=0)tickActionStream(actor,s,ctx,actor.dt);else s.timer55c-=actor.dt;
    integratePhysicsPrimary(1,actor,actor.lockYaw);
    const landed=fallbackGroundProbe(actor);
    if(landed){
      actor.housekeeping73f=0;actor.controlWord&=~3;
      dispatchUpperBodyCue(actor,7);actor.stateTimer=16+actor.dt;
    }else if((actor.inputHeld5d8&0xf0)!==0||actor.wallContact!==0){
      actor.housekeeping73f=0;actor.controlWord&=~3;romAirKnockoutReturn(actor);
    }
  }
}
