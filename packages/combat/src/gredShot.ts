/** Admitted grounded G RED-family action0/v0. Original18d350/438/534 owns
 * timing; only the middle of opcode0d's three clips is presented. Animated
 * side blending, analog direction buffering, aim numerics and floor geometry
 * remain explicit host adapters. Other action0 variants retain their old route. */
import type {RomActor,Vec3} from './rom/actor.js';
import {allocateWeapon,groundSnapRevert,stepTargetYaw,type RomHelperScratch} from './rom/helpers.js';
import {startStream,tickStream,type StreamContext} from './rom/stream-vm.js';
import {romGroundIdleReturn} from './families/shared-idle-return.js';
import {tickGRedShotEngine,type GRedShotEngineState,type GRedShotEngineHooks} from './gredShotEngine.js';
import {createGRedShotStream,tickGRedShotStream,type GRedShotStream,type GRedShotStreamEvent} from './gredShotStream.js';
type Actor=RomActor & RomHelperScratch & {aimPitch1900?:number;dashAimTimer560?:number;dashLatch745?:boolean;dashProjectilesRemaining?:number;grounded?:boolean};
export class GRedShotState implements GRedShotEngineState {
  constructor(readonly actor:Actor,public targetUid:string|null){
    if(![0x615,0x629,0x62a].includes(actor.borgNumber))throw Error('Unadmitted normal-shot family');
    this.family=actor.borgNumber===0x615?'red':actor.borgNumber===0x629?'neo':'black';
    this.poseAccum7c={get x(){return actor.poseAccum7c;},set x(v:number){actor.poseAccum7c=v;},
      get y(){return actor.poseAccum7e;},set y(v:number){actor.poseAccum7e=v;},
      get z(){return actor.poseAccum80;},set z(v:number){actor.poseAccum80=v;}};
  }
  readonly family:'red'|'neo'|'black';readonly poseAccum7c:Vec3;
  stream:GRedShotStream|null=null;streamMask=0;
  pendingStartOverride:{startFrame:number;blend:number}|undefined;
  fireCount=0;repeatCount=0;completed=false;idleTransitionFrames=0;
  input5d4=0;input5d8=0;ammo774=0;actionFlag6e8=0;
  /** Default equipment byte remains unbound. Raw opcode07 is [0,4,255]. */
  equipment:[number,number]|null=null;
  onCaptureTarget:(()=>void)|undefined;
  onReadAmmo:(()=>number)|undefined;
  get phase(){return this.actor.fbPhaseSlots[0]??0;}set phase(v:number){this.actor.fbPhaseSlots[0]=v;}
  get dt(){return this.actor.dt;}set dt(v:number){this.actor.dt=v;}
  get pos(){return this.actor.pos;}set pos(v:Vec3){this.actor.pos=v;}
  get savedGroundPos(){return this.actor.targetCache5e8;}set savedGroundPos(v:Vec3){this.actor.targetCache5e8=v;}
  get motion(){return this.actor.motion;}set motion(v:Vec3){this.actor.motion=v;}
  get controlWord(){return this.actor.controlWord;}set controlWord(v:number){this.actor.controlWord=v;}
  get hSpeed(){return this.actor.hSpeed;}set hSpeed(v:number){this.actor.hSpeed=v;}
  get yVel(){return this.actor.yVel;}set yVel(v:number){this.actor.yVel=v;}
  get hDecel(){return this.actor.hDecel;}set hDecel(v:number){this.actor.hDecel=v;}
  get gravityCoeff(){return this.actor.gravityCoeff;}set gravityCoeff(v:number){this.actor.gravityCoeff=v;}
  get rootAngle1900(){return this.actor.aimPitch1900??0;}set rootAngle1900(v:number){this.actor.aimPitch1900=v;}
  get shift18da(){return this.actor.steerYaw;}set shift18da(v:number){this.actor.steerYaw=v;}
  get sideBlend1dfc(){return this.actor.aimRoll1dfc??0;}set sideBlend1dfc(v:number){this.actor.aimRoll1dfc=v;}
  get latch745(){return this.actor.dashLatch745?1:0;}set latch745(v:number){this.actor.dashLatch745=v!==0;}
  get timer560(){return this.actor.dashAimTimer560??0;}set timer560(v:number){this.actor.dashAimTimer560=v;}
  get repeatTimer558(){return this.actor.handlerTimer;}set repeatTimer558(v:number){this.actor.handlerTimer=v;}
  get streamSlot6ee(){return this.actor.streamSlot;}set streamSlot6ee(v:number){this.actor.streamSlot=v;}
  get remaining6ef(){return this.actor.dashProjectilesRemaining??0;}set remaining6ef(v:number){this.actor.dashProjectilesRemaining=v;}
  get contactP0(){return this.actor.contactP0;}set contactP0(v:number){this.actor.contactP0=v;}
  get completed1cee(){return this.stream?.completed?1:0;}set completed1cee(_v:number){/* Clock owns completion. */}
  get actionFlag73f(){return this.actor.housekeeping73f;}set actionFlag73f(v:number){this.actor.housekeeping73f=v;}
  get accumulator80c(){return this.actor.accumulator80c;}set accumulator80c(v:number){this.actor.accumulator80c=v;}
}
const states=new WeakMap<RomActor,GRedShotState>();
export function getGRedShotState(a:RomActor){return states.get(a);}
export function prepareGRedShot(a:RomActor,targetUid:string|null,freshIdle=true){
  const s=new GRedShotState(a,targetUid);states.set(a,s);
  // Original18cef8 resets these while outside action mode. Scope that invariant
  // to this fresh grounded admission instead of altering other family actions.
  if(freshIdle){s.streamSlot6ee=0;s.sideBlend1dfc=0;}return s;
}
export function clearGRedShot(a:RomActor):void{states.delete(a);}
export function stepGRedShot(a:RomActor,ctx:StreamContext):void {
  const s=states.get(a);if(!s||a.actionIndex!==0||a.variantIndex!==0)return;
  s.ammo774=s.onReadAmmo?.()??s.ammo774;
  const hooks:GRedShotEngineHooks={
    aim6d0dc:()=>stepTargetYaw(a,0xc1,0),
    startStream:(_s,m,g,slot,frame,blend)=>{
      s.pendingStartOverride=frame!==undefined&&blend!==undefined?{startFrame:frame,blend}:undefined;
      startStream(a,m,g,slot,-1);s.pendingStartOverride=undefined;
    },
    tickStream:(_s,m)=>tickStream(a,m,ctx),
    ammo6dbe0:(_s,cell,count,debit)=>{const ok=allocateWeapon(a,ctx,cell,count,debit);s.ammo774=s.onReadAmmo?.()??s.ammo774;return ok;},
    spawnC3be0:(_s,row)=>{s.fireCount++;ctx.onFamilyProjectile?.(a,0x800c3be0,row);},
    capture6bf80:()=>{s.repeatCount++;s.onCaptureTarget?.();},
    ground679d0:()=>{groundSnapRevert(a);},
    groundIdle6a474:()=>{romGroundIdleReturn(a);s.completed=true;},
    // 6a668 still requests a20-unit idle transition, but its694 lockout branch
    // cannot execute after the source cleanup has cleared the action bits.
    idleTransition6a668:()=>{s.idleTransitionFrames=20;},
    redispatch6a3d0:()=>{
      // Source handoff leaves the scoped grounded machine. The pre-existing v3
      // engine is still approximate; no new airborne parity is claimed here.
      a.cmdButton=0;a.cmdSubtype=3;a.prevActionIndex=0;a.actionIndex=0;a.variantIndex=3;
      a.fbPhaseSlots[0]=0;states.delete(a);
    },
  };
  tickGRedShotEngine(s,hooks);
}
function applyEvents(a:RomActor,s:GRedShotState,events:readonly GRedShotStreamEvent[],ctx:StreamContext):void {
  for(const e of events){
    if(e.type==='play'){ctx.onPlayAnim?.(a,e.group,e.slot,false);}
    else if(e.type==='contact'&&(s.streamMask&1)){
      a.defaultGroup=1;a.contactP0=e.value;a.contactP1=e.aux;s.actionFlag6e8=e.actionFlag6e8;
      a.parts[0]!.stateByte=e.value;
    }else if(e.type==='movement'&&(s.streamMask&2)){a.dashStrength1d0f=e.dashStrength;a.faceGate1d10=e.faceGate;}
    else if(e.type==='equipment'&&(s.streamMask&1)){s.equipment=[...e.value];}
    else if(e.type==='completed')for(let p=0;p<a.parts.length;p++)if(s.streamMask&(1<<p)){a.parts[p]!.streamPtr=-1;a.parts[p]!.active=0;}
  }
  if(s.streamMask&1)a.streamHold1b03=s.stream?.blendMode??0;
}
export function startGRedShotStream(a:RomActor,group:number,slot:number,mask:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s||a.actionIndex!==0||a.variantIndex!==0||group!==2||(slot!==0&&slot!==1))return false;
  s.streamMask=mask&a.weaponPartMask;if(!s.streamMask)return false;
  const out=createGRedShotStream(slot,a.dt,s.pendingStartOverride);s.stream=out.stream;
  applyEvents(a,s,out.events,ctx);return true;
}
export function tickGRedShotStreamPart(a:RomActor,index:number,ctx:StreamContext):boolean {
  const s=states.get(a);if(!s?.stream||!(s.streamMask&(1<<index)))return false;
  if(index!==(31-Math.clz32(s.streamMask&-s.streamMask)))return true;
  applyEvents(a,s,tickGRedShotStream(s.stream,a.dt),ctx);return true;
}
