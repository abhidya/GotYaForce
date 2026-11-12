/** Source ordinary airborne B: upper-onlyv3 and its authored full-bodyv4
 * fallback. Lower movement is a host adapter, not original locomotion parity.
 * The renderer follows only the upper center clip, not the two-layer pose.
 * The optional source speed>3 carry FX is unbound; no particle/RNG parity. */
import type {RomActor} from './rom/actor.js';
import {allocateWeapon,stepTargetYaw,toS16} from './rom/helpers.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {integratePhysicsPrimary} from './rom/physics.js';
import {romAirKnockoutReturn} from './families/shared-idle-return.js';
import {GRedShotState} from './gredShot.js';
import {createGRedShotStream,tickGRedShotStream,type GRedShotStreamEvent} from './gredShotStream.js';
import {tickGRedAirShotEngine,type GRedAirShotEngineState,type GRedAirShotEngineHooks} from './gredAirShotEngine.js';
import {createGRedAirShotLowerStream,tickGRedAirShotLowerStream,type GRedAirShotLowerStream} from './gredAirShotLowerStream.js';
export class GRedAirShotState extends GRedShotState implements GRedAirShotEngineState {
  lowerStream:GRedAirShotLowerStream|null=null;
  physicsAdvanced=false;targetEligible=false;
  movementCue5e4=0;animationGroup1afc=2;animationSlot1afd=0;stateMode71d=0;
  readonly handoffHistory:Array<'air-v4'|'ground-v0'|'part-return'|'unsupported'>=[];
  onRedispatch:((subtype:0|4)=>void)|undefined;
  get variant():1|2|3|4{return this.actor.variantIndex as 1|2|3|4;}set variant(v:1|2|3|4){this.actor.variantIndex=v;}
  get partMode(){return (this.actor.controlWord&2)===0;}
  get lockYaw5ae(){return this.actor.lockYaw;}set lockYaw5ae(v:number){this.actor.lockYaw=v;}
  get faceGate1d10(){return this.actor.faceGate1d10;}set faceGate1d10(v:number){this.actor.faceGate1d10=v;}
  get lowerState5db(){return this.actor.ubState;}set lowerState5db(v:number){this.actor.ubState=v;}
}
const states=new WeakMap<RomActor,GRedAirShotState>();
export function getGRedAirShotState(a:RomActor){return states.get(a);}
export function prepareGRedAirShot(a:RomActor,targetUid:string|null){
  const s=new GRedAirShotState(a,targetUid);states.set(a,s);
  // Fresh idle admission only. Subsequent source redispatch preserves6ee.
  s.streamSlot6ee=0;s.sideBlend1dfc=0;return s;
}
export function clearGRedAirShot(a:RomActor):void{states.delete(a);}
/**6672c returns heading without an eligible captured target. The source therefore
 * seeks roll zero, not an artificial -1 fallback. Atan2/root centers are host
 * geometry/numeric seams; the signed cone and per-call approach are explicit. */
function roll6dee8(s:GRedAirShotState):number {
  const a=s.actor,t=s.targetEligible?a.lockTarget:null;
  const bearing=t?toS16(Math.round(Math.atan2(t.x-a.pos.x,t.z-a.pos.z)*32768/Math.PI)):toS16(a.heading);
  const relative=toS16(bearing-toS16(a.heading));
  if(relative < -0x4800 || relative > 0x4800)return -1;
  a.cmdChargedRanged=0;
  const desired=Math.max(-0x4000,Math.min(0x4000,relative)),current=toS16(s.sideBlend1dfc),delta=desired-current;
  if(delta>0x800){s.sideBlend1dfc=toS16(current+0x800);return 0;}
  if(delta< -0x800){s.sideBlend1dfc=toS16(current-0x800);return 0;}
  s.sideBlend1dfc=desired;return 0x8444;
}
function ground677b0(s:GRedAirShotState):void {
  const a=s.actor,r=a.physicsRuntime?.probeMotion?.(a.savedGroundPos,a.pos,a.yVel)??a.physicsRuntime?.clampToGround(a.pos,a.yVel);
  if(!r)return;
  if('y' in r&&typeof r.y==='number')a.pos.y=r.y;
  a.yVel=r.velY;a.grounded=r.grounded;
}
export function stepGRedAirShot(a:RomActor,ctx:StreamContext):void {
  const s=states.get(a);if(!s||a.actionIndex!==0||(a.variantIndex!==3&&a.variantIndex!==4))return;
  s.physicsAdvanced=false;s.ammo774=s.onReadAmmo?.()??s.ammo774;
  const h:GRedAirShotEngineHooks={
    roll6dee8:()=>roll6dee8(s),aim6d0dc:()=>stepTargetYaw(a,0x81,0),
    startStream:(_s,m,g,slot,frame,blend)=>{
      s.pendingStartOverride=frame!==undefined&&blend!==undefined?{startFrame:frame,blend}:undefined;
      startStream(a,m,g,slot,-1);s.pendingStartOverride=undefined;
    },
    tickStream:(_s,m)=>tickStream(a,m,ctx),
    primary67310:(_s,scale,yaw)=>{s.physicsAdvanced=true;integratePhysicsPrimary(scale,a,yaw);},
    ground677b0:()=>ground677b0(s),
    airReturn6a5a4:()=>{romAirKnockoutReturn(a);s.handoffHistory.push('part-return');},
    ammo6dbe0:(_s,cell,count,debit)=>{const ok=allocateWeapon(a,ctx,cell,count,debit);s.ammo774=s.onReadAmmo?.()??s.ammo774;return ok;},
    spawnC3be0:(_s,row)=>{s.fireCount++;ctx.onFamilyProjectile?.(a,0x800c3be0,row);},
    capture6bf80:()=>{s.repeatCount++;s.onCaptureTarget?.();},
    idleTransition6a668:()=>{s.idleTransitionFrames=20;},
  };
  const outcome=tickGRedAirShotEngine(s,h);
  if(outcome.type==='cleanup')s.completed=true;
  else if(outcome.type==='redispatch'){
    s.handoffHistory.push(outcome.subtype===4?'air-v4':'ground-v0');
    if(!s.onRedispatch)throw Error('Missing G RED air-shot redispatch adapter');
    s.onRedispatch(outcome.subtype);
  }else if(outcome.type==='unsupported'){
    // Unbound run/step controls must not silently execute a neutral clock.
    s.handoffHistory.push('unsupported');s.completed=true;a.controlWord&=~3;
  }
}
function applyUpper(a:RomActor,s:GRedAirShotState,events:readonly GRedShotStreamEvent[],ctx:StreamContext):void {
  for(const e of events){
    if(e.type==='play'){s.animationGroup1afc=e.group;s.animationSlot1afd=e.slot;ctx.onPlayAnim?.(a,e.group,e.slot,false);}
    else if(e.type==='contact'){a.defaultGroup=e.group;a.contactP0=e.value;a.contactP1=e.aux;
      s.actionFlag6e8=e.actionFlag6e8;a.parts[0]!.stateByte=e.value;}
    else if(e.type==='equipment')s.equipment=[...e.value];
    // Source upper mask1 cannot apply opcode03's mask2 writes.
    else if(e.type==='completed'){a.parts[0]!.streamPtr=-1;a.parts[0]!.active=0;}
  }
  a.streamHold1b03=s.stream?.blendMode??0;
}
export function startGRedAirShotStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s||a.actionIndex!==0)return false;
  if(group===2&&(slot===4||slot===5||slot===6||slot===7)&&(mask&a.weaponPartMask&1)){
    s.streamMask=1;
    const out=createGRedShotStream(slot,a.dt,s.pendingStartOverride);s.stream=out.stream;
    applyUpper(a,s,out.events,ctx);return true;
  }
  if(group===0&&slot===13&&(mask&a.weaponPartMask&2)){
    s.lowerStream=createGRedAirShotLowerStream(a.dt).stream;
    // Only lower-part startup control is global. Its independent clock and pose
    // are retained below; one renderer playhead deliberately stays upper-only.
    a.controlWord=(a.controlWord&0xfffff00f)|0x40;
    a.dashStrength1d0f=0;a.faceGate1d10=0;s.stateMode71d=0;return true;
  }
  return false;
}
export function tickGRedAirShotStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s)return false;
  if(index===0&&s.stream){applyUpper(a,s,tickGRedShotStream(s.stream,a.dt),ctx);return true;}
  if(index===1&&s.lowerStream){
    tickGRedAirShotLowerStream(s.lowerStream,a.dt);
    if(s.lowerStream.completed){a.parts[1]!.streamPtr=-1;a.parts[1]!.active=0;}
    return true;
  }
  return false;
}
