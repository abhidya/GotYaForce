/** Independent original G RED clocks, not original-console output parity.
 * Source slots0/1/2: AOBJ ends27/35/35; mode1/2/1 blend5/4/5.
 * Ratebyte0 preserves an existing rate; these isolated traces assume rate1.
 * Waits inspect the saved frame before advancing once per update. */
import {createNeoMeleeStream,tickNeoMeleeStream,type NeoMeleeSlot} from './neoMeleeStream.js';
function assert(v:unknown,s:string):asserts v {if(!v)throw Error(`[gredMeleeStream] ${s}`);}
function same(a:unknown,b:unknown,s:string){assert(JSON.stringify(a)===JSON.stringify(b),`${s}: ${JSON.stringify(a)} != ${JSON.stringify(b)}`);}
const traces=[
 {slot:0,dt:1,mode:1,blend:5,end:27,endTick:32,complete:33,gates:[[11,5],[16,10]]},
 {slot:1,dt:1,mode:2,blend:4,end:35,endTick:36,complete:37,gates:[[7,5],[15,13]]},
 {slot:2,dt:1,mode:1,blend:5,end:35,endTick:40,complete:41,gates:[[18,12],[25,19]]},
 {slot:0,dt:.5,mode:1,blend:5,end:27,endTick:65,complete:66,gates:[[22,5],[32,10]]},
 {slot:1,dt:.5,mode:2,blend:4,end:35,endTick:71,complete:72,gates:[[12,5],[28,13]]},
 {slot:2,dt:.5,mode:1,blend:5,end:35,endTick:81,complete:82,gates:[[36,12],[50,19]]},
] as const;
function testTraces(){
 for(const t of traces){
  const s=createNeoMeleeStream(t.slot as NeoMeleeSlot,t.dt),seen:number[][]=[];
  same([s.frame,s.elapsed,s.blendMode,s.blendTotal,s.blendElapsed,s.endFrame],[0,0,t.mode,t.blend+1,t.dt,t.end],'source initial clock');
  for(let tick=1;tick<=t.complete;tick++){
   const before=s.frame,e=tickNeoMeleeStream(s,t.dt);
   if(e.gate!==undefined){
    seen.push([tick,e.gate]);assert(before>=e.gate,'wait observes old frame');same(s.frame,before+t.dt,'one advance after block');
    if(t.slot===2 && e.gate===12){same(e.clearDash,true,'third12 clears dash');same([e.contact,e.aux],[undefined,undefined],'third12 does not invent part writes');}
    else {
     const terminal=e.gate!==5;
     same([e.contact,e.aux],[terminal?-1:1,terminal?(t.slot===2?0:-1):0],'source contact/aux packet, second usesFF not NEO FE');
     same([e.flags6e8,e.flags6e9],[0,0],'source RED part flags');
     if(terminal)same(e.clearContactFlags,true,'terminal gate clears709mask1f');
     if(t.slot!==2&&terminal)same(e.clearDash,true,'first/second terminal clears dash');
    }
   }
   assert(!e.groundWave&&!e.recovery,'no unverified child callback or recovery');
   same(e.completed===true,tick===t.complete,'terminal checked after original raw end');
   if(tick<t.endTick)assert(!s.ended,'no premature raw end');
   if(tick===t.endTick)same([s.frame,s.ended],[t.end,true],'original raw AOBJ end');
   same(s.slot,t.slot,'clock does not implicitly chain');
  }
  same(seen,t.gates,'independent source gate ticks');
  const end=JSON.stringify(s);for(let i=0;i<5;i++){same(tickNeoMeleeStream(s,t.dt),{completed:true},'stable terminal');same(JSON.stringify(s),end,'terminal noadvance');}
 }
}
function testBoundary(){
 for(const [slot,gate] of [[0,5],[0,10],[1,5],[1,13],[2,12],[2,19]] as const){
  const s=createNeoMeleeStream(slot as NeoMeleeSlot,1);s.blendMode=0;s.frame=gate-1;s.waitIndex=gate===5||gate===12?0:1;
  assert(tickNeoMeleeStream(s,1).gate===undefined,'advance onto gate does not parse it early');same(tickNeoMeleeStream(s,1).gate,gate,'exact gate parses next call');
 }
}
export function runGredMeleeStreamSelfTest(){testTraces();testBoundary();console.log('[gredMeleeStream] PASS: original RED gates, flags, blend clocks and terminal behavior');}
