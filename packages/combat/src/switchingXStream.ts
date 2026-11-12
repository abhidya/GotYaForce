/** Original Switching Ninja g4s4/5 (8033dd96/8033ddc6). Descriptor4/2→
 * MOT4/0 end80;4/3→MOT4/1 end78; recovery0/14→MOT0/24 end1.
 * Opcode01 mode1/blend2 starts0; waits inspect the pre-advance clock.
 */
export interface SwitchingXStream {
  slot:4|5;frame:number;elapsed:number;blendMode:0|1;blendElapsed:number;blendTotal:number;
  endFrame:number;ended:boolean;stopped:boolean;releaseParsed:boolean;recovery:boolean;completed:boolean;
}
export interface SwitchingXStreamEvent {
  contact?:number;dashStrength?:number;faceGate?:number;control?:number;
  animation?:readonly[number,number];completed?:boolean;
}
const f=Math.fround;
export function createSwitchingXStream(slot:4|5,dt=1):SwitchingXStream {
  return {slot,frame:0,elapsed:0,blendMode:1,blendElapsed:dt,blendTotal:f(2+dt),
    endFrame:slot===4?80:78,ended:false,stopped:false,releaseParsed:false,recovery:false,completed:false};
}
function advance(s:SwitchingXStream,dt:number):void {
  s.elapsed=f(s.elapsed+dt);
  if(s.blendMode){
    s.blendElapsed=f(s.blendElapsed+dt);
    if(s.blendElapsed>=s.blendTotal){s.frame=f(s.frame+f(s.blendElapsed-s.blendTotal));s.blendMode=0;if(s.frame>=s.endFrame)s.stopped=true;}
  }else{
    if(!s.stopped)s.frame=f(s.frame+dt);
    if(s.frame>=s.endFrame){s.stopped=true;s.ended=true;}
  }
}
export function tickSwitchingXStream(s:SwitchingXStream,dt:number):SwitchingXStreamEvent {
  if(s.completed)return {completed:true};
  if(s.recovery){
    if(s.elapsed>=15){s.completed=true;return {completed:true};}
    advance(s,dt);return {};
  }
  let e:SwitchingXStreamEvent={};
  if(!s.releaseParsed&&s.frame>=25){
    s.releaseParsed=true;e=s.slot===4?{contact:1,dashStrength:0,faceGate:0,control:0}:{contact:1};
  }else if(s.releaseParsed&&s.ended){
    if(s.slot===4){s.completed=true;return {completed:true};}
    s.recovery=true;s.frame=s.elapsed=0;s.blendMode=1;s.blendElapsed=dt;s.blendTotal=f(15+dt);
    s.endFrame=1;s.ended=s.stopped=false;
    return {animation:[0,14],contact:-1,dashStrength:-1,faceGate:0};
  }
  advance(s,dt);return e;
}
