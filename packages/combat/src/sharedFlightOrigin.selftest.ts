/** FUN_80149758 subtracts actor's own position history at +0x5e8, never
 * the target. This prevents repeated lance-flight entry from amplifying the
 * distance between fighters. Synthetic fixtures test the source-owned inputs. */
import {createRomActor} from './rom/actor.js';
import {createSharedFlightX, FLIGHT_X_FAMILY4_CONFIG} from './families/shared-flight-x.js';
function assert(v:unknown,m:string):asserts v {if(!v) throw Error(`[sharedFlightOrigin] ${m}`);}
export function runSharedFlightOriginSelfTest():void {
 const run=createSharedFlightX(FLIGHT_X_FAMILY4_CONFIG,{});
 for(const target of [{x:-4000,y:-9000,z:6000},null]) {
  const a=createRomActor();a.pos={x:100,y:200,z:300};a.targetCache5e8={x:90,y:180,z:270};a.lockTarget=target;
  run(a);
  assert(Math.abs(a.pos.x-109.5)<1e-5 && Math.abs(a.pos.y-219)<1e-5 && Math.abs(a.pos.z-328.5)<1e-5,
   'entry carries own previous-motion delta regardless of target');
 }
 const a=createRomActor();a.pos={x:0,y:100,z:0};a.lockTarget={x:0,y:-10000,z:0};
 for(let i=0;i<100;i++){a.fbPhaseSlots[0]=0;a.targetCache5e8={...a.pos};run(a);}
 assert(a.pos.y===100,'repeated zero-motion entries cannot amplify distance to target');
 console.log('[sharedFlightOrigin] PASS: own-position history and no-target entry');
}
