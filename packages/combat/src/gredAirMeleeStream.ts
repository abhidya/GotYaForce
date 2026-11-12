/** Admitted G RED-family airborne B clocks. Original mode1/start0, retained
 * rate0 (host rate1), per-stream raw AOBJ ends and authored recovery.
 * Callers own conditional advancement; this clock must not tick every frame
 * merely because the action is active. No functional child callback.
 */
import {GRED_AIR_MELEE_PROFILES,gredAirMeleeStreamProfile,type GRedAirMeleeFamily,type GRedAirMeleeGate} from './gredAirMeleeConfig.js';
export interface GRedAirMeleeStream {
  family:GRedAirMeleeFamily;
  slot:number;recovery:boolean;
  frame:number;elapsed:number;blendMode:0|1;blendElapsed:number;blendTotal:number;
  endFrame:number;ended:boolean;stopped:boolean;waitIndex:number;completed:boolean;
}
export interface GRedAirMeleeStreamEvent extends Partial<GRedAirMeleeGate> {
  completed?:boolean;recovery?:boolean;
}
export function createGRedAirMeleeStream(dt=1,family:GRedAirMeleeFamily='red',slot=GRED_AIR_MELEE_PROFILES[family].engine.seedSlot):GRedAirMeleeStream {
  const profile=gredAirMeleeStreamProfile(family,slot);
  if(!profile)throw Error(`Unadmitted ${family} airborne melee stream ${slot}`);
  return {family,slot,recovery:false,frame:0,elapsed:0,blendMode:1,blendElapsed:dt,blendTotal:profile.blendByte+1,endFrame:profile.endFrame,
    ended:false,stopped:false,waitIndex:0,completed:false};
}
/** Source wait4cd24 tests before the one animation update. Blend completion
 * suppresses end byte until the next normal update, even if AOBJ already STOPped.
 */
export function tickGRedAirMeleeStream(s:GRedAirMeleeStream,dt:number):GRedAirMeleeStreamEvent {
  if(s.completed)return {completed:true};
  const profile=gredAirMeleeStreamProfile(s.family,s.slot)!;
  let event:GRedAirMeleeStreamEvent={};
  if(s.recovery){
    // Recovery terminal0001000f compares elapsed(+8), not animation frame.
    if(s.elapsed>=15){s.completed=true;return {completed:true};}
  }else{
    const gate=profile.gates[s.waitIndex];
    if(gate && s.frame>=gate.gate){s.waitIndex++;event={...gate};}
    else if(!gate && s.ended){
      if(!profile.recovery){s.completed=true;return {completed:true};}
      // Mode0/-1 falls through to playg0s14: mode1, blend15, start0, end1.
      // This starts a fresh clock without advancing it on the same parse call.
      s.recovery=true;s.frame=0;s.elapsed=0;s.blendMode=1;s.blendElapsed=dt;s.blendTotal=16;
      s.endFrame=1;s.ended=false;s.stopped=false;
      return {recovery:true,contact:0,aux:0,flags6e8:3,flags6e9:0,
        dashStrength:-1,faceGate:0,clearContactFlags:true};
    }
  }
  s.elapsed=Math.fround(s.elapsed+dt);
  if(s.blendMode!==0){
    s.blendElapsed=Math.fround(s.blendElapsed+dt);
    if(s.blendElapsed>=s.blendTotal){
      s.frame=Math.fround(s.frame+Math.fround(s.blendElapsed-s.blendTotal));
      if(s.frame>=s.endFrame)s.stopped=true;
      s.blendMode=0;
    }
  }else{
    if(!s.stopped)s.frame=Math.fround(s.frame+dt);
    if(s.frame>=s.endFrame){s.stopped=true;s.ended=true;}
  }
  return event;
}
