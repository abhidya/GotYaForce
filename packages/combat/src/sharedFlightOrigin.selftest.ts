/** FUN_80149758 subtracts actor's own position history at +0x5e8, never
 * the target. This prevents repeated lance-flight entry from amplifying the
 * distance between fighters. Synthetic fixtures test the source-owned inputs. */
import {createRomActor} from './rom/actor.js';
import {createSharedEngineRootAction} from './families/shared-engine.js';
import {configureArrowNinjaFamily} from './families/arrow-ninja.js';
import {configureJetHeroFamily} from './families/unregistered-cluster.js';
import {createSharedFlightX, FLIGHT_X_FAMILY4_CONFIG} from './families/shared-flight-x.js';
import {createSonicXSpecial,createShogunXSpecial} from './families/samurai.js';
import {configureMachineBlueFamily,configureMachineRedFamily} from './families/machine-red-blue.js';
import {createValkrieAirMelee,createValkrieXSpecial} from './families/valkrie.js';
import {createMeleeGirlLunge} from './families/melee-girl-lunge.js';
import {createBarrierGirlX} from './families/girl-cluster.js';
import {createEagleRobotAction0} from './families/eagle-robot.js';
import {createStarHeroRootAction} from './families/star-hero.js';
import {createMeleeSamurai,SAMURAI_MELEE_DEFAULT_CONFIG} from './families/melee-samurai.js';
import {createSharedCharge,GRED_CHARGE_CONFIG} from './families/shared-charge.js';
import {createSharedCharge3,FAMILY1_CHARGE3_CONFIG} from './families/shared-charge3.js';
import {createKnightMeleeTable28,knightMeleeEntry00,knightMeleeEntry14} from './families/shared-knight-melee.js';
import {createSharedMorphXSpecial,TITAN_MORPH_CONFIG} from './families/shared-morph-x.js';
import {createSwordKnightRootAction} from './families/sword-knight.js';
import {createRobotRootAction} from './families/robot.js';
import {createOmega2RootAction} from './families/omega2-robot.js';
import {createHammerRootAction} from './families/hammer-robot.js';
import {createMagnetRobotRootAction} from './families/magnet-robot.js';
function assert(v:unknown,m:string):asserts v {if(!v) throw Error(`[sharedFlightOrigin] ${m}`);}
export function runSharedFlightOriginSelfTest():void {
 for(const target of [{x:-4000,y:-9000,z:6000},null]) {
  for(const name of ['engine','ninja','jet'] as const) {
   const b=createRomActor(); b.pos={x:100,y:200,z:300}; b.targetCache5e8={x:90,y:180,z:270}; b.lockTarget=target;
   if(name==='engine') { b.actionIndex=0; createSharedEngineRootAction({dash:{seedSlot:0,proximityRange:100,timerFrames:20,repositionScale:0.95}})(b); }
   else if(name==='ninja') { configureArrowNinjaFamily(b,'pl0002',{}); b.actionIndex=1; b.variantIndex=1; b.rootAction!(b); }
   else { configureJetHeroFamily(b,{}); b.actionIndex=2; b.rootAction!(b); }
   assert(Math.abs(b.pos.x-109.5)<1e-4 && Math.abs(b.pos.y-219)<1e-4 && Math.abs(b.pos.z-328.5)<1e-4,`${name} carries own history regardless of target`);
  }
 }
 const run=createSharedFlightX(FLIGHT_X_FAMILY4_CONFIG,{});
 for(const target of [{x:-4000,y:-9000,z:6000},null]) {
  const a=createRomActor();a.pos={x:100,y:200,z:300};a.targetCache5e8={x:90,y:180,z:270};a.lockTarget=target;
  run(a);
  assert(Math.abs(a.pos.x-109.5)<1e-5 && Math.abs(a.pos.y-219)<1e-5 && Math.abs(a.pos.z-328.5)<1e-5,
   'entry carries own previous-motion delta regardless of target');
 }
 for(const [name,run,scale] of [
  ['morph',createSharedMorphXSpecial(TITAN_MORPH_CONFIG,{}),TITAN_MORPH_CONFIG.repositionScale],
  ['sword knight',createSwordKnightRootAction({}),0.95],
  ['build robot',createRobotRootAction({}),0.95],
  ['omega robot',createOmega2RootAction({}),0.95],
  ['hammer robot',createHammerRootAction({}),0.95],
  ['magnet robot',createMagnetRobotRootAction({}),0.95],
 ] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.actionIndex=2;b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   run(b);
   assert(Math.abs(b.pos.x-(100+10*scale))<1e-4 && Math.abs(b.pos.y-(200+20*scale))<1e-4 &&
    Math.abs(b.pos.z-(300+30*scale))<1e-4,`${name} uses own history regardless of target`);
  }
 }
 // Source flight phases 0-2 each invoke terrain collision after carrying motion.
 {
  const b=createRomActor(); b.pos={x:0,y:10,z:0}; b.targetCache5e8={x:0,y:10,z:-20};
  const calls:number[]=[];
  b.physicsRuntime={
   clampToGround:(pos,velY)=>({y:pos.y,velY,grounded:true}),
   probeMotion:(previous,pos,velY)=>{calls.push(previous.z); pos.z=Math.min(pos.z,10);return {velY,grounded:true};}};
  run(b); assert(b.pos.z===10 && calls[0]===0,'flight entry terrain blocks wall crossing');
  b.fbPhaseSlots[0]=1;run(b);b.fbPhaseSlots[0]=2;run(b);
  assert(calls.length===3 && calls[1]===10 && calls[2]===10 && b.pos.z===10,'each windup phase probes once from prior point');
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
 for(const [name,make,action] of [
  ['Barrier Girl X',createBarrierGirlX,2],
  ['Eagle Robot burst',createEagleRobotAction0,0],
  ['Star Hero X',createStarHeroRootAction,2],
 ] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   b.actionIndex=action;b.variantIndex=0;make({})(b);
   assert(Math.abs(b.motion.x-9.5)<1e-4 && Math.abs(b.motion.y-19)<1e-4 && Math.abs(b.motion.z-28.5)<1e-4,
    `${name} derives scaled carry from own history independently of target`);
  }
 }
 for(const [name,run,scale] of [
  ['samurai melee',createMeleeSamurai({}, {...SAMURAI_MELEE_DEFAULT_CONFIG,repositionScale:0.95}),0.95],
  ['shared charge',createSharedCharge({...GRED_CHARGE_CONFIG,onSetup:null},{}),GRED_CHARGE_CONFIG.repositionScale],
  ['shared charge3',createSharedCharge3(FAMILY1_CHARGE3_CONFIG,{}),FAMILY1_CHARGE3_CONFIG.repositionScale],
 ] as const) {
  for(const target of [{x:-4000,y:-9000,z:6000},null]) {
   const b=createRomActor();b.pos={x:100,y:200,z:300};b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
   run(b);
   assert(Math.abs(b.pos.x-(100+10*scale))<1e-4 && Math.abs(b.pos.y-(200+20*scale))<1e-4 &&
    Math.abs(b.pos.z-(300+30*scale))<1e-4,`${name} uses own history regardless of target`);
  }
 }
 for(const target of [{x:-4000,y:-9000,z:6000},null]) {
  const b=createRomActor();b.borgNumber=0x208;b.pos={x:100,y:200,z:300};
  b.targetCache5e8={x:90,y:180,z:270};b.lockTarget=target;
  createKnightMeleeTable28({})(b);
  assert(Math.abs(b.pos.x-109.5)<1e-4 && Math.abs(b.pos.y-219)<1e-4 && Math.abs(b.pos.z-328.5)<1e-4,
   'knight dive carries own history regardless of target');
  for(const entry of [knightMeleeEntry00,knightMeleeEntry14]) {
   const c=createRomActor();c.pos={x:100,y:200,z:300};c.targetCache5e8={x:90,y:180,z:270};c.lockTarget=target;
   c.motion={x:3,y:4,z:5};c.accumulator80c=42;entry(c,()=>{});
   assert(c.pos.x===100&&c.pos.y===200&&c.pos.z===300&&c.motion.x===3&&c.motion.y===4&&c.motion.z===5,
    'knight entry visual prelude does not teleport or overwrite motion');
   assert(c.accumulator80c===0,'phase-zero source accumulator is cleared');
  }
 }
 console.log('[sharedFlightOrigin] PASS: own-position history and no-target entry');
}
