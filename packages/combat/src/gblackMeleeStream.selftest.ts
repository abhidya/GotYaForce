/** Inert G BLACK clock checks, not gameplay or groundwave implementation.
 * Source13/14/15 waits and raw AOBJ ends are audited original values.
 * Mode1 holds frame0 through blend(duration+1, initialized with dt).
 * Waits observe the old frame, then advance once. Rate1 is the test baseline;
 * original playAnim rate byte0 preserves an existing rate, not authored rate1.
 */
import {createNeoMeleeStream,tickNeoMeleeStream,type NeoMeleeSlot} from './neoMeleeStream.js';
import {G_BLACK_NEUTRAL_MELEE_CONFIG as config,G_BLACK_MELEE_STREAMS,gblackMeleeStreamConfig} from './gblackMeleeConfig.js';
function check(v:unknown,label:string):asserts v {if(!v)throw Error(`[gblackMeleeStream] ${label}`);}
function same(a:unknown,b:unknown,label:string){check(JSON.stringify(a)===JSON.stringify(b),`${label}: ${JSON.stringify(a)} != ${JSON.stringify(b)}`);}
const packets=[
 {slot:13,blend:4,end:35,events:[
  {gate:5,contact:0,aux:0,flags6e8:2,flags6e9:1},
  {gate:17,contact:-1,aux:-1,flags6e8:2,flags6e9:0,clearDash:true},
  {gate:19,contact:-1,aux:-1,flags6e8:3,flags6e9:2,clearContactFlags:true}]},
 {slot:14,blend:5,end:40,events:[
  {gate:7,contact:0,aux:0,flags6e8:2,flags6e9:1},
  {gate:11,contact:0,aux:0,flags6e8:2,flags6e9:2},
  {gate:15,contact:-1,aux:-2,flags6e8:3,flags6e9:2,clearDash:true,clearContactFlags:true}]},
 {slot:15,blend:4,end:70,events:[
  {gate:11,contact:0,aux:0,flags6e8:2,flags6e9:1},
  {gate:19,clearDash:true},
  {gate:22,groundWave:true},
  {gate:29,contact:-1,aux:0,flags6e8:2,flags6e9:2},
  {gate:33,contact:-1,aux:0,flags6e8:3,flags6e9:0,clearContactFlags:true}]},
] as const;
function testTraces() {
 for(const p of packets)for(const dt of [1,.5]){
  const s=createNeoMeleeStream(p.slot as NeoMeleeSlot,dt);
  same([s.frame,s.elapsed,s.blendMode,s.blendElapsed,s.blendTotal,s.endFrame],[0,0,1,dt,p.blend+1,p.end],`slot${p.slot} initial clock`);
  const endTick=(p.blend+1-dt+p.end)/dt,completeTick=endTick+1;
  let index=0,waves=0;
  for(let tick=1;tick<=completeTick;tick++){
   const oldFrame=s.frame,event=tickNeoMeleeStream(s,dt);
   if(event.gate!==undefined){
    const expected=p.events[index++]!;check(expected,'no extra source block');
    for(const [key,value] of Object.entries(expected))same((event as unknown as Record<string,unknown>)[key],value,`slot${p.slot} gate${event.gate} ${key}`);
    same(tick,(p.blend+1-dt+event.gate)/dt+1,`slot${p.slot} gate${event.gate} independently derived wait tick`);
    check(oldFrame>=event.gate,'wait checks frame before advance');
    same(s.frame,oldFrame+dt,'non-animation block advances once');
    if('groundWave' in event && event.groundWave){waves++;same([event.contact,event.aux,event.flags6e8,event.flags6e9,event.clearDash],[undefined,undefined,undefined,undefined,undefined],'callback22 has no invented part or dash writes');}
   }
   same(event.completed===true,tick===completeTick,'completion follows raw end on next check');
   if(tick<endTick)check(!s.ended,'raw end not reached early');
   if(tick===endTick)same([s.frame,s.ended,s.stopped],[p.end,true,true],'original raw end reached');
   check(!s.recovery,'no invented recovery animation');same(s.slot,p.slot,'no implicit next or fourth swing');
  }
  same(index,p.events.length,'all source blocks observed');same(waves,p.slot===15?1:0,'groundwave emitted exactly once only by third swing');
  const done=JSON.stringify(s);
  for(let i=0;i<8;i++){same(tickNeoMeleeStream(s,dt),{completed:true},'terminal event is stable');same(JSON.stringify(s),done,'terminal state neither advances nor repeats callback');}
 }
}
function testGateBoundaryAndOvershoot(){
 for(const p of packets)for(let i=0;i<p.events.length;i++){
  const gate=p.events[i]!.gate,s=createNeoMeleeStream(p.slot as NeoMeleeSlot,1);
  // Explicit clock injection isolates interpreter boundary; not gameplay input.
  s.blendMode=0;s.frame=gate-1;s.waitIndex=i;
  check(tickNeoMeleeStream(s,1).gate===undefined,'reaching gate during advance does not parse early');
  same(tickNeoMeleeStream(s,1).gate,gate,'next call observes exact gate');
 }
 const s=createNeoMeleeStream(15 as NeoMeleeSlot,1);s.blendMode=0;s.frame=30;
 const gates=[];for(let i=0;i<4;i++)gates.push(tickNeoMeleeStream(s,1).gate);
 same(gates,[11,19,22,29],'overshoot parses one successive source block per update, not catch-up loop');
}
function testConfig(){
 same([config.borgNumber,config.seedSlot,config.proximityRange,config.timerFrames,config.decel,config.chainCallback,config.altChainCallback],
 [0x62a,13,150,20,0.949999988079071,null,null],'original inert config, including both null callbacks');
 for(const [slot,anim,hit,dash] of [[13,24,31,24],[14,4,17,32],[15,23,30,24]] as const){
  const c=G_BLACK_MELEE_STREAMS[slot];same([c.animSlot,c.hitKind,c.dashStrength],[anim,hit,dash],'source animation/HIT/dash bindings');
 }
 for(const slot of [12,16,25,26,27])check(gblackMeleeStreamConfig(slot)===undefined,'inert lookup does not capture neighboring or NEO slots');
}
export function runGblackMeleeStreamSelfTest(){testConfig();testTraces();testGateBoundaryAndOvershoot();console.log('[gblackMeleeStream] PASS: inert source clocks, writes, once-only groundwave event and terminal behavior');}
