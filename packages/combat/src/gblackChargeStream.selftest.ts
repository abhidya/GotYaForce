import {createGBlackChargeStream,tickGBlackChargeStream} from './gblackChargeStream.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[gblackChargeStream] ${msg}`);}
/** Independent interpreter-call counts from source mode2 blend8+1 and end38.
 * No RED pause, positive-contact beam release, duration timer or mash budget. */
export function runGBlackChargeStreamSelfTest():void {
 for(const dt of [1,.5]){
  const s=createGBlackChargeStream(dt),events:number[]=[];
  const expected=dt===1?[21,26,40,49]:[40,50,78,95];
  let tick=0;
  for(;tick<110&&!s.completed;){
   tick++;const before={...s},e=tickGBlackChargeStream(s,dt);
   if(Object.keys(e).length)events.push(tick);
   if(e.gate!==undefined){
    assert(before.frame>=e.gate,'gate compares old frame');
    if(e.gate===19)assert(e.contact===1,'frame19 positive contact');
    if(e.gate===24)assert(e.faceGate===0,'frame24 facing disabled');
   }
   if(!before.recovery&&before.blendMode===2){
    if(before.blendElapsed+dt<before.blendTotal)assert(s.frame===before.frame+dt,'mode2 startup advances while blending');
    else assert(s.frame===before.frame,'blend completion drops exact zero overflow');
   }
   if(e.recovery){
    assert(before.ended&&before.frame===38,'main must end before recovery');
    assert(s.frame===0&&s.elapsed===0&&s.blendElapsed===dt&&s.blendTotal===9&&s.endFrame===1,'recovery reset has no same-call advance');
    assert(e.contact===-1&&e.dashStrength===-1,'recovery negative contact and gravity event');
   }
   if(e.completed)assert(before.recovery&&before.elapsed===8,'terminal tests elapsed8 before advance');
  }
  assert(JSON.stringify(events)===JSON.stringify(expected),`independent dt${dt} trace ${events}`);
  assert(s.completed&&s.frame===0&&s.elapsed===8,'elapsed terminal precedes recovery animation advance');
  const terminal=JSON.stringify(s);tickGBlackChargeStream(s,dt);assert(JSON.stringify(s)===terminal,'completed stream inert');
 }
 console.log('[gblackChargeStream] PASS: two independent mode2/gate/recovery traces');
}
