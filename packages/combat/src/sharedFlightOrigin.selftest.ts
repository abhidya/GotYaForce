/** FUN_80149758 subtracts actor's own position history at +0x5e8, never
 * the target. This prevents repeated lance-flight entry from amplifying the
 * distance between fighters. Synthetic fixtures test the source-owned inputs. */
import {createRomActor} from './rom/actor.js';
import {createSharedFlightX, FLIGHT_X_FAMILY4_CONFIG} from './families/shared-flight-x.js';
import {createSonicXSpecial,createShogunXSpecial} from './families/samurai.js';
import {configureMachineBlueFamily,configureMachineRedFamily} from './families/machine-red-blue.js';
import {createValkrieAirMelee,createValkrieXSpecial} from './families/valkrie.js';
import {createMeleeGirlLunge} from './families/melee-girl-lunge.js';
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
 for(const [name,make] of [['sonic',createSonicXSpecial],['shogun',createShogunXSpecial]] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   make({})(b);
   assert(Math.abs(b.pos.x-109.5)<1e-5 && Math.abs(b.pos.y-219)<1e-5 && Math.abs(b.pos.z-328.5)<1e-5,
    `${name} carries own history independently of target`);
  }
 }
 for(const [name,action] of [
  ['red X',2],
  ['blue aimed X',2],
  ['blue deploy',4],
 ] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   if(name==='red X') configureMachineRedFamily(b,'pl0600',{}); else configureMachineBlueFamily(b,'pl0609',{});
   b.actionIndex=action;b.variantIndex=0;b.rootAction!(b);
   assert(Math.abs(b.pos.x-109.5)<1e-4 && Math.abs(b.pos.y-219)<1e-4 && Math.abs(b.pos.z-328.5)<1e-4,
    `${name} carries own history independently of target`);
  }
 }
 for(const [name,make,scale] of [
  ['Valkrie air melee',createValkrieAirMelee,0.95],
  ['Valkrie X',createValkrieXSpecial,0.98],
  ['Girl lunge',createMeleeGirlLunge,0.95],
 ] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   make({})(b);
   assert(Math.abs(b.pos.x-(100+10*scale))<1e-4 && Math.abs(b.pos.y-(200+20*scale))<1e-4 &&
    Math.abs(b.pos.z-(300+30*scale))<1e-4,`${name} carries own history independently of target`);
  }
 }
 console.log('[sharedFlightOrigin] PASS: own-position history and no-target entry');
}
