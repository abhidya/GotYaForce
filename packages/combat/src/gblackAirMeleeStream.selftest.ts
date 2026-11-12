import {createGRedAirMeleeStream,tickGRedAirMeleeStream} from './gredAirMeleeStream.js';
import {G_BLACK_AIR_MELEE_CONFIG,GRED_AIR_MELEE_PROFILES} from './gredAirMeleeConfig.js';
function assert(ok:unknown,message:string):asserts ok {if(!ok)throw Error(`[gblackAirMeleeStream] ${message}`);}
export function runGblackAirMeleeStreamSelfTest():void {
 const c=G_BLACK_AIR_MELEE_CONFIG,p=GRED_AIR_MELEE_PROFILES.black;
 assert(c.seedSlot===24&&c.proximityRange===300&&c.pursuitTimer===20&&c.recoveryTimer===0,'original BLACK engine profile');
 assert(c.launchSpeed===60&&c.driftScale===Math.fround(.95)&&c.transitionScale===.25&&c.recoveryDamping===Math.fround(.9),'source motion constants');
 assert(p.animSlot===21&&p.hitKind===6&&p.hitRecords.join(',')==='6,19'&&p.endFrame===50,'separate BLACK stream/HIT/clip');
 for(const dt of [1,.5]){
  const s=createGRedAirMeleeStream(dt,'black'),events:{tick:number;gate:number}[]=[];
  assert(s.family==='black'&&s.frame===0&&s.blendMode===1&&s.endFrame===50,'BLACK starts its original clip at0');
  let tick=0;
  for(;tick<150&&!s.completed;){
   tick++;const before=s.frame,e=tickGRedAirMeleeStream(s,dt);
   assert(e.dashStrength===undefined||e.dashStrength<0,'BLACK never inherits RED positive dash24 event');
   if(e.gate!==undefined){
    assert(before>=e.gate,'source gate reads current frame before animation update');events.push({tick,gate:e.gate});
    if(e.gate===13)assert(e.contact===1&&e.aux===0&&e.flags6e8===2&&e.flags6e9===0,'gate13 contact');
    if(e.gate===14)assert(e.contact===0&&e.aux===0&&e.flags6e9===1,'gate14 removes contact and requests effect shadow');
    if(e.gate===19)assert(e.dashStrength===-1&&e.faceGate===0,'gate19 gravity request');
    if(e.gate===23)assert(e.contact===0&&e.flags6e9===2,'gate23 second effect shadow');
    if(e.gate===27)assert(e.contact===-1&&e.aux===0&&e.flags6e8===3&&e.flags6e9===0&&e.clearContactFlags,'gate27 landing eligibility and709clear');
   }
   if(tick*dt<=5)assert(s.frame===0,'source blend holds first pose');
  }
  assert(JSON.stringify(events)===JSON.stringify([19,20,25,29,33].map((n,i)=>({tick:n/dt,gate:[13,14,19,23,27][i]}))),`independent dt${dt} trace`);
  assert(s.completed&&tick===56/dt,'BLACK terminal follows frame50 ended flag');
  const frozen=JSON.stringify(s);tickGRedAirMeleeStream(s,dt);assert(JSON.stringify(s)===frozen,'terminal is inert');
 }
 console.log('[gblackAirMeleeStream] PASS: independent profile, dt1/.5 gates, no RED dash and end50');
}
