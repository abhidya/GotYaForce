/** Independent original NEO/BLACK source-clock traces. Source start36, mode1
 * blends16/6, raw AOBJ end80 and recovery end1 were read from original data.
 * Ratebyte0 retains rate; these fixtures assume rate1, not console-output parity.
 * HIT lifecycle renewal is separate from this frozen animation clock. */
import {createGRedCrashStream,tickGRedCrashStream} from './gredCrashStream.js';
function assert(x:unknown,s:string):asserts x{if(!x)throw Error(`[gredFamilyCrashStream] ${s}`);}
function same(a:unknown,b:unknown,s:string){assert(JSON.stringify(a)===JSON.stringify(b),`${s}: ${JSON.stringify(a)} != ${JSON.stringify(b)}`);}
const traces=[
 {family:'neo',dt:1,blend:16,gates:[[21,40],[22,41],[33,52],[43,62],[54,64]],end:69,recovery:70,done:86},
 {family:'black',dt:1,blend:6,gates:[[11,40],[12,41],[23,52],[33,62],[44,64]],end:59,recovery:60,done:76},
 {family:'neo',dt:.5,blend:16,gates:[[42,40],[44,41],[66,52],[86,62],[109,64]],end:140,recovery:141,done:172},
 {family:'black',dt:.5,blend:6,gates:[[22,40],[24,41],[46,52],[66,62],[89,64]],end:120,recovery:121,done:152},
] as const;
export function runGredFamilyCrashStreamSelfTest(){
 for(const t of traces){
  const s=createGRedCrashStream(t.dt,t.family),gates:number[][]=[],callbacks:number[][]=[];
  same([s.family,s.frame,s.elapsed,s.blendMode,s.blendElapsed,s.blendTotal,s.endFrame],[t.family,36,0,1,t.dt,t.blend+1,80],'source initial family clock');
  let ended=0,recovered=0,frozen=0;
  for(let tick=1;tick<=t.done;tick++){
   const before={frame:s.frame,elapsed:s.elapsed,wait:s.waitCount,blend:s.blendMode};const e=tickGRedCrashStream(s,t.dt);
   if(before.wait>t.dt){frozen++;same([s.frame,s.elapsed],[before.frame,before.elapsed],'mode8 positive countdown freezes both clocks');}
   if(before.blend===1&&!s.recovery&&s.blendMode===1)same(s.frame,36,'mode1 blend holds authored36');
   if(e.gate!==undefined){
    assert(before.frame>=e.gate,'wait checks saved frame before advance');gates.push([tick,e.gate]);
    if(e.gate===40)same([e.contact,e.aux,e.flags6e8],[1,0,2],'gate40 authored descent packet');
    if(e.gate===64)same([e.contact,e.aux,e.strength,e.faceGate,e.flags6e8],[-1,0,-1,0,3],'gate64 recovery packet');
    for(const c of e.callbacks??[])callbacks.push([e.gate,c.callback,c.arg]);
   }
   if(s.ended&&!s.recovery&&ended===0)ended=tick;
   if(e.recovery){recovered=tick;same([s.frame,s.elapsed,s.blendMode,s.blendTotal,s.endFrame,e.contact,e.flags6e8],[0,0,1,16,1,-1,0],'recovery resets clocks and applies family part packet');}
   same(e.completed===true,tick===t.done,'terminal elapsed15 wait');
  }
  same(gates,t.gates,'independent hand-derived gate ticks');same([ended,recovered],[t.end,t.recovery],'original end and next-check recovery');
  same(callbacks,[[40,2,0],[41,1,4],[52,1,0],[52,1,2],[64,1,3]],'source callback order, no RED gate68');
  same(frozen,10/t.dt-1,'source hold positive-update count');
  const done=JSON.stringify(s);for(let i=0;i<4;i++){same(tickGRedCrashStream(s,t.dt),{completed:true},'stable completion');same(JSON.stringify(s),done,'terminal clock stable');}
 }
 console.log('[gredFamilyCrashStream] PASS: distinct source starts/blends, gates, hold and recovery');
}
