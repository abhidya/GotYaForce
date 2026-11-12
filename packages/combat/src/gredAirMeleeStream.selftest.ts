import { createGRedAirMeleeStream, tickGRedAirMeleeStream } from './gredAirMeleeStream.js';
function assert(ok:unknown,message:string):asserts ok {if(!ok)throw new Error(`[gredAirMeleeStream] ${message}`);}
export function runGredAirMeleeStreamSelfTest():void {
 for(const dt of [1,.5]){
  const s=createGRedAirMeleeStream(dt),events:{tick:number;gate:number}[]=[];
  assert(s.frame===0&&s.blendMode===1&&s.endFrame===30,'source start0/mode1/end30');
  let tick=0;
  for(;tick<100&&!s.completed;){
   tick++;const before=s.frame,e=tickGRedAirMeleeStream(s,dt);
   if(e.gate!==undefined){
    events.push({tick,gate:e.gate});assert(before>=e.gate,'gate evaluates prior animation frame');
    if(e.gate===10)assert(e.contact===1,'frame10 opens authored contact');
    if(e.gate===15)assert(e.dashStrength===24&&e.faceGate===1,'frame15 requests source dash');
    if(e.gate===20)assert(e.dashStrength===-1&&e.faceGate===0,'frame20 requests gravity');
    if(e.gate===26)assert(e.contact===-1&&e.clearContactFlags,'frame26 permits landing and clears709');
   }
   if(tick*dt<=5)assert(s.frame===0,'mode1 blend holds first pose');
  }
  const scale=1/dt;
  assert(JSON.stringify(events)===JSON.stringify([16,21,26,32].map((t,i)=>({tick:t*scale,gate:[10,15,20,26][i]}))),`independent dt${dt} gate trace`);
  assert(s.completed&&tick===36*scale,'end30 terminal completes on following parser call');
  const snapshot=JSON.stringify(s);const late=tickGRedAirMeleeStream(s,dt);
  assert(JSON.stringify(s)===snapshot&&late.gate===undefined,'completed stream is inert');
 }
 // The caller may suspend tickStream during pursuit. Holding this object must
 // not acquire a second clock or replay a gate when simulation resumes.
 const held=createGRedAirMeleeStream();let contact=false;
 for(let i=0;i<40&&!contact;i++)contact=tickGRedAirMeleeStream(held,1).contact===1;
 assert(contact,'fixture reaches conditional-pursuit hold');
 const frame=held.frame,serial=JSON.stringify(held);
 for(let i=0;i<20;i++)assert(JSON.stringify(held)===serial,'no elapsed-time side channel');
 const resumed=tickGRedAirMeleeStream(held,1);
 assert(held.frame===frame+1&&resumed.gate!==10,'resuming neither catches up nor repeats contact gate');
 console.log('[gredAirMeleeStream] PASS: independent dt1/.5 traces, source gates, held continuation and terminal');
}
