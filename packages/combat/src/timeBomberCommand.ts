/** Bounded pl0106 walk/run X command adapter, not a global command resolver.
 * 8005f3a0/8005f578 set control10 -> subtype1. 8006c674 classifies the
 * currently selected target in actor-root coordinates, before attack capture.
 * Only upright, uniform-scale host roots are admitted by battle.ts. Source
 * roll/6b8 correction and stop-tail state are not represented by this adapter.
 */
import { commandMoveRecordsForBorgButton } from './commandMoveTables.js';
import { activeSourceTarget } from './targetLock.js';
import type { BorgRuntime, ResolvedCommandState } from './types.js';
import type { Vec3 } from '@gf/physics';

/** Signed thresholds are strict; equality at the inner boundary stays forward. */
export function timeBomberDirectionForYaw(angle:number):0|1|2|3 {
  if(angle>0x5000)return 2;
  if(angle>0x2800)return 1;
  if(angle < -0x2800)return angle < -0x5000 ? 2 : 3;
  return 0;
}

/** Upright reduction of4516c inverse root +452a0 atan2. The host-to-root
 * heading conversion matches bridge.ts. The source angle conversion itself
 * uses frsp/fmuls and truncation, never Math.round. JS trig/matrix arithmetic
 * is not a claim of full PowerPC parity. GQR5=0x00070007 selects signed16
 * unit quantization: truncate and saturate, including the +/-pi endpoints.
 */
export function timeBomberTargetYaw(owner:Pick<BorgRuntime,'pos'|'rotY'>,target:{pos:Vec3}|null):number {
  if(!target)return 0;
  const heading=((Math.round(owner.rotY*0x10000/(2*Math.PI))&0xffff)*2*Math.PI)/0x10000;
  const dx=target.pos.x-owner.pos.x,dz=target.pos.z-owner.pos.z;
  const x=dx*Math.cos(heading)-dz*Math.sin(heading);
  const z=dx*Math.sin(heading)+dz*Math.cos(heading);
  return Math.max(-0x8000,Math.min(0x7fff,Math.trunc(Math.fround(Math.fround(Math.atan2(x,z))*10430.3779296875))));
}

export function resolveTimeBomberWalkCommand(owner:BorgRuntime,all:readonly BorgRuntime[]):ResolvedCommandState|null {
  const command=owner.command;
  if(owner.borgId!=='pl0106' || !owner.timeBomberInput?.walking || !owner.grounded || owner.state!=='move' ||
     !command?.exact || command.type!==2 || command.actionIndex!==0)return command??null;
  const direction=timeBomberDirectionForYaw(timeBomberTargetYaw(owner,activeSourceTarget(owner,all)));
  const record=commandMoveRecordsForBorgButton('pl0106','X').find(row=>row.subtype===1 && row.direction===direction);
  if(!record)return command;
  return {...command,subtype:record.subtype,recordAddress:record.address,actionIndex:record.actionIndex,variantIndex:record.variantIndex};
}
