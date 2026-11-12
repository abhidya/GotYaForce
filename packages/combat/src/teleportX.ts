/** Scoped pl0005 ordinary X. Original146dcc/146ed8/146f6c/147094;
 * source input686f0 and69b98. Host terrain, target geometry, normalization and
 * the recent-melee144 producer remain explicit boundaries, not full parity. */
import type {BorgRuntime} from './types.js';
import type {RomActor,Vec3} from './rom/actor.js';
import type {StreamContext} from './rom/stream-vm.js';
import {allocateWeapon} from './rom/helpers.js';
import {romAirKnockoutReturn,romGroundIdleReturn} from './families/shared-idle-return.js';
import {tickTeleportXEngine,type TeleportXEngineState} from './teleportXEngine.js';

const f=Math.fround;
export const isSourceTeleportX=(id:string):boolean=>id==='pl0005';
/** Input+0x768 is a rate, not animation dt and not literal768. The existing
 * source ammo rate binds its status/burst writer; input charge applies6fc*10. */
export function stepTeleportXInput(b:BorgRuntime,held:boolean,activeType5=false){
  const s=b.teleportXInput??={held:false,pressEdge:false,releasedReady:false,warmup:0,charge:0,pending:false};
  s.pressEdge=held&&!s.held;s.held=held;s.releasedReady=false;
  const rate=b.sourceAmmoRefillRate??1;
  if(activeType5||((b.sourceTeleportInputBlock58e??0)&0x20)!==0){s.warmup=s.charge=0;}
  else if(!held){s.releasedReady=s.charge>=120;s.warmup=0;s.charge=Math.max(0,f(s.charge-f(2*rate)));}
  else if(s.warmup<10){s.warmup=f(s.warmup+1);}
  else s.charge=Math.min(120,f(s.charge+f(rate*(b.burstPaired?10:1))));
  s.pending=true;return s;
}

export interface TeleportXState extends TeleportXEngineState {
  targetUid:string|null;lastGroundProbe:0|1;feedback9Count:number;feedback10Count:number;
  exitKind:'ground'|'air'|null;flags6e8:number;flags6e9:number;stateMode71d:number;
  /** Verified g0s0/13 recovery play, overridden to mode1/blend2. The actor
   * exits after two dispatches, before either authored ended wait can matter. */
  stream:{slot:0|13;frame:number;elapsed:number;blendElapsed:number;blendTotal:number}|null;
}
type Actor=RomActor&{grounded?:boolean};
const states=new WeakMap<RomActor,TeleportXState>();
export function getTeleportXState(a:RomActor):TeleportXState|undefined{return states.get(a);}
export function prepareTeleportX(a:RomActor,b:BorgRuntime,targetUid:string|null,targetPoint:Vec3|null):TeleportXState{
  const s:TeleportXState={
    get phase(){return a.fbPhaseSlots[0]??0;},set phase(v){a.fbPhaseSlots[0]=v;},
    get dt(){return a.dt;},set dt(v){a.dt=v;},pos:a.pos,savedOwnPos5e8:a.targetCache5e8,motion:a.motion,
    destination9c:{x:0,y:0,z:0},targetUid,capturedTargetCc:targetUid!==null,target518:targetPoint?{...targetPoint}:{...a.pos},
    recentMeleeTimer144:b.sourceTeleportRecentMeleeTimer144??0,
    get modelScaleB4(){return a.modelScale;},set modelScaleB4(v){a.modelScale=v;},
    get controlWord(){return a.controlWord;},set controlWord(v){a.controlWord=v;},airLatch54a:0,
    get timer558(){return a.handlerTimer;},set timer558(v){a.handlerTimer=v;},
    flags272:b.deathFlags??0,visibility82:0x41,movementFlag87:0,movementCue5e4:0,
    get actionFlag73f(){return a.housekeeping73f;},set actionFlag73f(v){a.housekeeping73f=v;},
    get carriedSlot96(){return a.carriedSlot96;},set carriedSlot96(v){a.carriedSlot96=v;},
    get hSpeed(){return a.hSpeed;},set hSpeed(v){a.hSpeed=v;},get yVel(){return a.yVel;},set yVel(v){a.yVel=v;},
    get hDecel(){return a.hDecel;},set hDecel(v){a.hDecel=v;},get gravityCoeff(){return a.gravityCoeff;},set gravityCoeff(v){a.gravityCoeff=v;},
    descriptorGravity6c:a.descriptor?.handlerData6c??-1,lastGroundProbe:0,feedback9Count:0,feedback10Count:0,exitKind:null,flags6e8:0,flags6e9:0,stateMode71d:0,stream:null,
  };
  states.set(a,s);return s;
}
export function clearTeleportX(a:RomActor,b?:BorgRuntime):void{
  states.delete(a);
  if(b){delete b.sourceDefenseDisabled;delete b.sourceHidden;}
}
export function stepTeleportX(a:Actor,ctx:StreamContext):void{
  const s=states.get(a);if(!s)return;
  tickTeleportXEngine(s,{
    normalize6ebb4(v){const n=Math.hypot(v.x,v.y,v.z);if(n>0){v.x=f(v.x/n);v.y=f(v.y/n);v.z=f(v.z/n);}else{v.x=0;v.y=1;v.z=0;}},
    feedback061a8(_s,code){if(code===9)s.feedback9Count++;else s.feedback10Count++;},
    ground677b0(){const p=a.physicsRuntime,r=p?.probeMotion?p.probeMotion(a.savedGroundPos,a.pos,a.yVel):p?.clampToGround(a.pos,a.yVel);
      if(!r){s.lastGroundProbe=0;return;}if('y'in r&&typeof r.y==='number')a.pos.y=r.y;
      a.yVel=r.velY;a.grounded=r.grounded;s.lastGroundProbe=r.grounded?1:0;
    },
    ammo6dbe0(){return allocateWeapon(a,ctx,2,1,true);},
    cueF036c(_s,code){ctx.onPlayCue?.(a,code);},
    startStream(_s,_mask,_group,slot){
      s.stream={slot,frame:0,elapsed:0,blendElapsed:a.dt,blendTotal:f(2+a.dt)};
      // Original8033d68e/8033d786: opcode02 resets state, opcode03 replaces
      // posture with0/40. Opcode01 clears71d; original support pose is unbound.
      a.contactP0=a.contactP1=0;a.parts[0]!.stateByte=0;s.flags6e8=s.flags6e9=s.stateMode71d=0;
      a.dashStrength1d0f=a.faceGate1d10=0;
      a.controlWord=(a.controlWord&~0xff0)|(slot===0?0:0x40);
      (a as Actor&{stateMode?:number}).stateMode=0;
      ctx.onPlayAnim?.(a,0,slot===0?0:14,false);
    },
    tickStream(){if(s.stream){s.stream.elapsed=f(s.stream.elapsed+a.dt);s.stream.blendElapsed=f(s.stream.blendElapsed+a.dt);s.stream.frame=Math.max(0,f(s.stream.blendElapsed-s.stream.blendTotal));}},
    groundIdle6a474(){s.exitKind='ground';romGroundIdleReturn(a);},
    airReturn6a5a4(){s.exitKind='air';romAirKnockoutReturn(a);},
  });
}
