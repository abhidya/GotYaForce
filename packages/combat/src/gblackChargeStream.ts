/** Original BLACK g4s3 @803671b8. Main animation g4s2/MOT4s2 has
 * raw EndFrame38; recoveryg0s14/MOT0s24 end1. Retained rate0 is bound
 * to admitted rate1. Callers own opcode shadows and projectile setup. */
export interface GBlackChargeStream {
  recovery:boolean;frame:number;elapsed:number;blendMode:0|1|2;
  blendElapsed:number;blendTotal:number;endFrame:number;
  ended:boolean;stopped:boolean;waitIndex:number;completed:boolean;
}
export interface GBlackChargeStreamEvent {
  gate?:number;contact?:number;faceGate?:number;dashStrength?:number;
  recovery?:boolean;completed?:boolean;
}
export function createGBlackChargeStream(dt=1):GBlackChargeStream {
  return {recovery:false,frame:0,elapsed:0,blendMode:2,blendElapsed:dt,
    blendTotal:9,endFrame:38,ended:false,stopped:false,waitIndex:0,completed:false};
}
export function tickGBlackChargeStream(s:GBlackChargeStream,dt:number):GBlackChargeStreamEvent {
  if(s.completed)return {completed:true};
  let e:GBlackChargeStreamEvent={};
  if(s.recovery){
    if(s.elapsed>=8){s.completed=true;return {completed:true};}
  }else{
    const gate=([19,24] as const)[s.waitIndex];
    if(gate!==undefined&&s.frame>=gate){
      s.waitIndex++;e=gate===19?{gate,contact:1}:{gate,faceGate:0};
    }else if(gate===undefined&&s.ended){
      // play resets elapsed/frame, seeds blendElapsed=dt, and does not advance
      // on the same interpreter call. Terminalmode1/8 uses elapsed, not frame.
      s.recovery=true;s.frame=0;s.elapsed=0;s.blendMode=1;s.blendElapsed=dt;
      s.blendTotal=9;s.endFrame=1;s.ended=false;s.stopped=false;
      return {recovery:true,contact:-1,dashStrength:-1,faceGate:0};
    }
  }
  const f=Math.fround;s.elapsed=f(s.elapsed+dt);
  if(s.blendMode){
    s.blendElapsed=f(s.blendElapsed+dt);
    if(s.blendElapsed>=s.blendTotal){
      s.frame=f(s.frame+f(s.blendElapsed-s.blendTotal));
      if(s.frame>=s.endFrame)s.stopped=true;s.blendMode=0;
    }else if(s.blendMode===2)s.frame=f(s.frame+dt);
  }else{
    if(!s.stopped)s.frame=f(s.frame+dt);
    if(s.frame>=s.endFrame){s.stopped=true;s.ended=true;}
  }
  return e;
}
