import {createNinjaXStream,tickNinjaXStream} from './ninjaXStream.js';
const assert=(ok:unknown,msg:string)=>{if(!ok)throw Error(`[ninjaXStream] ${msg}`);};
export function runNinjaXStreamSelfTest():void {
 for(const slot of [0,1] as const)for(const dt of [1,.5]){
  const s=createNinjaXStream(slot,dt),gates:number[]=[];let n=0,release=0,recovery=0;
  assert(s.frame===0&&s.elapsed===0&&s.blendElapsed===dt&&s.blendTotal===7,'fresh play never advances');
  while(!s.completed&&n<150){
   n++;const old={...s},e=tickNinjaXStream(s,dt);
   if(e.gate!==undefined){assert(old.frame>=e.gate,'wait inspects old frame');gates.push(e.gate);}
   if(e.gate===14){release=n;assert(e.contact===1&&e.dashStrength===(slot===0?0:32)&&e.faceGate===0&&e.flags6e8===0,'ground/air callback and opcode02 packet');}
   if(old.blendMode&&old.blendElapsed+dt<old.blendTotal)assert(s.frame===old.frame,'mode1 holds playhead');
   if(e.animation){recovery=n;assert(s.frame===0&&s.elapsed===0&&s.blendElapsed===dt,'recovery resets without same-call advance');
    assert(s.endFrame===(slot===0?120:1)&&s.loop===(slot===0),'descriptor flags5 loop, not rate5');}
   if(e.completed)assert(old.elapsed===(slot===0?4:8),'terminal uses elapsed, not frame or clip end');
  }
  assert(release===(dt===1?21:42),'independent source blend6 and preadvance release');
  assert(JSON.stringify(gates)===JSON.stringify(slot===0?[2,11,14,31,34]:[1,14]),'complete raw gate sequence');
  assert(recovery===(dt===1?(slot===0?52:47):(slot===0?104:94)),'main end and next interpreter recovery');
  assert(n===(dt===1?(slot===0?57:56):(slot===0?113:111)),'elapsed terminal completes later call');
  const frozen=JSON.stringify(s);tickNinjaXStream(s,dt);assert(JSON.stringify(s)===frozen,'completed clock inert');
 }
 const s=createNinjaXStream(0);tickNinjaXStream(s,60);const cross=s.frame;
 assert(s.stopped&&!s.ended,'overshoot stops AOBJ while end flag remains blend-suppressed');
 tickNinjaXStream(s,1);assert(s.frame===cross&&s.ended,'next normal update observes frozen overshoot');
 console.log('[ninjaXStream] PASS: independent clocks, authored callback, recovery flags, elapsed completion and overshoot');
}
