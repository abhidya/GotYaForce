/** Scoped RED/NEO g4s2 @80367144. Source4cd24 wait ordering and487ec/4892c
 * animation clocks; original AOBJ ends25/25/1, no loop. Retained rate0 is
 * bound to the admitted host rate1, not a renderer-owned elapsed clock. */
export interface GRedChargeStream {
  stage:'main'|'recoil'|'recovery';frame:number;elapsed:number;
  blendMode:0|1|2;blendElapsed:number;blendTotal:number;endFrame:number;
  stopped:boolean;ended:boolean;waitIndex:number;waitCount:number;completed:boolean;
}
export interface GRedChargeStreamEvent {
  gate?:number;contact?:number;dashStrength?:number;faceGate?:number;
  equipment?:readonly [number,number];animation?:readonly [number,number];completed?:boolean;
}
export function createGRedChargeStream(dt=1):GRedChargeStream {
  return {stage:'main',frame:0,elapsed:0,blendMode:1,blendElapsed:dt,blendTotal:6,
    endFrame:25,stopped:false,ended:false,waitIndex:0,waitCount:0,completed:false};
}
function advance(s:GRedChargeStream,dt:number):void {
  const f=Math.fround;s.elapsed=f(s.elapsed+dt);
  if(s.blendMode){
    s.blendElapsed=f(s.blendElapsed+dt);
    if(s.blendElapsed>=s.blendTotal){
      s.frame=f(s.frame+f(s.blendElapsed-s.blendTotal));
      if(s.frame>=s.endFrame)s.stopped=true;
      s.blendMode=0; // End marking is suppressed on this completion update.
    }else if(s.blendMode===2)s.frame=f(s.frame+dt);
  }else{
    if(!s.stopped)s.frame=f(s.frame+dt);
    if(s.frame>=s.endFrame){s.stopped=true;s.ended=true;}
  }
}
function play(s:GRedChargeStream,stage:'recoil'|'recovery',dt:number):void {
  s.stage=stage;s.frame=0;s.elapsed=0;s.blendMode=stage==='recoil'?2:1;
  s.blendElapsed=dt;s.blendTotal=stage==='recoil'?5:21;
  s.endFrame=stage==='recoil'?25:1;s.stopped=false;s.ended=false;
}
/** Caller owns the phase2 conditional tick. No automatic frame advance while
 * the charge engine suppresses its interpreter. */
export function tickGRedChargeStream(s:GRedChargeStream,dt:number):GRedChargeStreamEvent {
  if(s.completed)return {completed:true};
  if(s.stage==='recovery'){
    if(s.elapsed>=20){s.completed=true;return {completed:true};}
  }else if(s.stage==='recoil'){
    if(s.ended){play(s,'recovery',dt);return {animation:[0,14]};}
  }else{
    if(s.waitCount>0){
      s.waitCount=Math.max(0,Math.fround(s.waitCount-dt));
      if(s.waitCount===0)advance(s,dt);
      return {};
    }
    const gate=([9,11,12,19] as const)[s.waitIndex];
    if(gate!==undefined && s.frame>=gate){
      s.waitIndex++;
      const event:GRedChargeStreamEvent={gate};
      if(gate===9)s.waitCount=12;
      if(gate===11)event.equipment=[2,2];
      if(gate===12)event.contact=1;
      if(gate===19)event.contact=-1;
      advance(s,dt);return event;
    }
    if(gate===undefined && s.ended){
      play(s,'recoil',dt);return {animation:[4,4],contact:-1,dashStrength:-1,faceGate:0};
    }
  }
  advance(s,dt);return {};
}
