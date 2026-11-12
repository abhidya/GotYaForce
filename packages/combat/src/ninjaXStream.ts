/** Original Ninja g4s0/1 at802be5ee/802be656. Main raw AOBJ ends45/40,
 * descriptor rate is1. Recovery0/0 end120 flags5 loops;0/14 end1 flags1 does
 * not. The descriptor05 byte is flags, never a five-times playback rate.
 * All waits inspect the old clock before one normal animation update. */
export interface NinjaXStream {
  slot:0|1;frame:number;elapsed:number;blendMode:0|1;blendElapsed:number;blendTotal:number;
  endFrame:number;loop:boolean;ended:boolean;stopped:boolean;waitIndex:number;
  recovery:boolean;completed:boolean;
}
export interface NinjaXStreamEvent {
  gate?:number;contact?:number;flags6e8?:number;stateMode?:number;
  dashStrength?:number;faceGate?:number;control?:number;
  animation?:readonly[number,number];completed?:boolean;
}
export function createNinjaXStream(slot:0|1,dt=1):NinjaXStream {
  return {slot,frame:0,elapsed:0,blendMode:1,blendElapsed:dt,blendTotal:7,
    endFrame:slot===0?45:40,loop:false,ended:false,stopped:false,waitIndex:0,recovery:false,completed:false};
}
const f=Math.fround;
function advance(s:NinjaXStream,dt:number):void{
  s.elapsed=f(s.elapsed+dt);
  if(s.blendMode){
    s.blendElapsed=f(s.blendElapsed+dt);
    if(s.blendElapsed>=s.blendTotal){
      s.frame=f(s.frame+f(s.blendElapsed-s.blendTotal));
      if(!s.loop&&s.frame>=s.endFrame)s.stopped=true;
      s.blendMode=0; // Source b76c still observes the old nonzero mode here.
    }
  }else{
    if(!s.stopped)s.frame=f(s.frame+dt);
    if(s.loop){
      // The admitted four-elapsed-unit recovery finishes before its120-frame
      // looping boundary. This wrap is only a defensive out-of-range dt seam.
      if(s.frame>=s.endFrame)s.frame=f(s.frame%s.endFrame);
    }else if(s.frame>=s.endFrame){s.stopped=true;s.ended=true;}
  }
}
export function tickNinjaXStream(s:NinjaXStream,dt:number):NinjaXStreamEvent{
  if(s.completed)return {completed:true};
  if(s.recovery){
    if(s.elapsed>=(s.slot===0?4:8)){s.completed=true;return {completed:true};}
    advance(s,dt);return {};
  }
  const gate=(s.slot===0?[2,11,14,31,34]:[1,14])[s.waitIndex];
  let e:NinjaXStreamEvent={};
  if(gate!==undefined&&s.frame>=gate){
    s.waitIndex++;e={gate};
    if(gate===(s.slot===0?2:1))e.flags6e8=2;
    else if(gate===11)e.stateMode=1;
    else if(gate===14){e.contact=1;e.flags6e8=0;e.dashStrength=s.slot===0?0:32;e.faceGate=0;}
    else if(gate===31){e.dashStrength=0;e.faceGate=0;e.control=0;}
    else if(gate===34){e.contact=-1;e.flags6e8=0;}
  }else if(gate===undefined&&s.ended){
    s.recovery=true;s.frame=0;s.elapsed=0;s.blendMode=1;s.blendElapsed=dt;
    s.blendTotal=s.slot===0?5:9;s.endFrame=s.slot===0?120:1;s.loop=s.slot===0;
    s.stopped=false;s.ended=false;
    return s.slot===0?{animation:[0,0]}:{animation:[0,14],contact:-1,flags6e8:0};
  }
  advance(s,dt);return e;
}
