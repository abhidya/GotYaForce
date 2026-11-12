import {createGRedAirMeleeStream,tickGRedAirMeleeStream} from './gredAirMeleeStream.js';
import {GRED_AIR_MELEE_PROFILES,NEO_G_RED_AIR_MELEE_CONFIG,gredAirMeleeStreamProfile} from './gredAirMeleeConfig.js';
function assert(ok:unknown,message:string):asserts ok {if(!ok)throw Error(`[neoAirMeleeStream] ${message}`);}
export function runNeoAirMeleeStreamSelfTest():void {
 const c=NEO_G_RED_AIR_MELEE_CONFIG;
 assert(c.seedSlot===33&&c.proximityRange===300&&c.pursuitTimer===20&&c.recoveryTimer===4&&c.launchSpeed===40&&c.driftScale===Math.fround(.9),'NEO engine differs from BLACK');
 for(const slot of [33,34]){
  const p=gredAirMeleeStreamProfile('neo',slot)!;
  assert(p.initialGroup===undefined&&p.initialDash===24&&p.blendByte===2&&p.statusId===25&&p.statusArg===255,'original startup preserves group/control and uses dash24/status25');
  assert(p.hitKind===slot-9&&p.hitRecords[0]===slot+6&&p.animSlot===slot-14,'per-stream HIT and animation mapping');
  for(const dt of [1,.5]){
   const s=createGRedAirMeleeStream(dt,'neo',slot),gates:{tick:number;gate:number}[]=[];
   let tick=0,recoveryTick=0;
   for(;tick<150&&!s.completed;){
    tick++;const before=s.frame,e=tickGRedAirMeleeStream(s,dt);
    if(e.gate!==undefined){
     assert(before>=e.gate,'gate evaluates prior frame');gates.push({tick,gate:e.gate});
     if(e.gate===3)assert(e.contact===1&&e.aux===0,'gate3 contact');
     if(e.gate===5)assert(e.contact===0&&e.flags6e9===1,'gate5 resumes contact0');
     if(e.gate===(slot===33?14:15))assert(e.contact===-1&&e.aux===-1&&e.flags6e9===2,'negative auxiliary opens retap continuation');
    }
    if(e.recovery){
     assert(!recoveryTick,'only one recovery play');recoveryTick=tick;
     assert(s.frame===0&&s.elapsed===0&&s.blendElapsed===dt&&s.blendTotal===16&&s.endFrame===1,'new recovery play has no same-call advance');
     assert(e.contact===0&&e.aux===0&&e.dashStrength===-1&&e.faceGate===0&&e.clearContactFlags,'recovery clears chain and requests gravity');
    }
    if(recoveryTick&&tick<recoveryTick+15/dt)assert(!s.completed,'elapsed15 cannot finish early');
   }
   assert(JSON.stringify(gates)===JSON.stringify([6,8,slot===33?17:18].map((n,i)=>({tick:n/dt,gate:[3,5,slot===33?14:15][i]}))),`independent slot${slot}/dt${dt} gates`);
   const end=slot===33?30:45;
   assert(recoveryTick===(end+3)/dt&&tick===(end+18)/dt+1&&s.completed,'original main and recovery completion counts');
   const frozen=JSON.stringify(s);tickGRedAirMeleeStream(s,dt);assert(JSON.stringify(s)===frozen,'finished recovery is inert');
  }
 }
 const final=gredAirMeleeStreamProfile('neo',35)!;
 assert(final.streamAddress===gredAirMeleeStreamProfile('black',24)!.streamAddress&&final.hitKind===6&&final.initialDash===0&&!final.recovery,'slot35 is terminal BLACK stream alias');
 assert(GRED_AIR_MELEE_PROFILES.neo.engine===c&&c.launchSpeed===40&&c.recoveryTimer===4,'stream alias never replaces NEO engine');
 for(const dt of [1,.5]){const s=createGRedAirMeleeStream(dt,'neo',35);let n=0;for(;n<130&&!s.completed;n++){const e=tickGRedAirMeleeStream(s,dt);assert(!e.recovery&&(e.aux===undefined||e.aux===0),'final stream cannot rechain or play opener recovery');}assert(n===56/dt,'final end50 timing');}
 assert(!gredAirMeleeStreamProfile('neo',36)&&!gredAirMeleeStreamProfile('black',33),'no fourth or cross-family admission');
 let rejected=false;try{createGRedAirMeleeStream(1,'neo',36);}catch{rejected=true;}assert(rejected,'unverified stream rejected');
 console.log('[neoAirMeleeStream] PASS: six independent traces, recovery elapsed timing, profile isolation and terminal alias');
}
