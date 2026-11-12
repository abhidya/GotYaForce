/** Bounded18d350 phase0 arithmetic/order. These direct fixtures do not claim
 * ordinary-shot stream timing, later phases, projectile or pad-admission parity. */
import {createGRedDash,GRED_DASH} from './families/gred-dash.js';
import {createRomActor,type Vec3} from './rom/actor.js';
const f=Math.fround;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(ok:unknown,message:string):asserts ok{if(!ok)throw Error(`[gredShotCarry] ${message}`);}
function same(actual:unknown,expected:unknown,message:string){assert(JSON.stringify(actual)===JSON.stringify(expected),`${message}: ${JSON.stringify(actual)} != ${JSON.stringify(expected)}`);}
function fixture(id=0x615){
 const a=Object.assign(createRomActor(),{lockTarget:null as Vec3|null,onStartStream:(_g:number,_s:number,_m:number)=>true});
 a.borgNumber=id;a.actionIndex=0;a.variantIndex=0;a.fbPhaseSlots[0]=0;
 a.pos=v(100,200,300);a.targetCache5e8=v(99,198,296);a.savedGroundPos={...a.pos};
 a.hSpeed=9;a.hDecel=8;a.yVel=7;a.gravityCoeff=6;a.poseAccum7c=5;a.poseAccum7e=4;a.poseAccum80=3;a.accumulator80c=2;
 return a;
}
export function runGredShotCarrySelfTest():void{
 const drive=createGRedDash();
 for(const id of [0x615,0x629,0x62a])for(const target of [null,v(1,2,3),v(90000,-5000,70000)]){
  const a=fixture(id);a.lockTarget=target;drive(a);
  const motion=v(f(f(100-99)*f(.95)),f(f(200-198)*f(.95)),f(f(300-296)*f(.95)));
  same(a.motion,motion,'own5e8 controls carry independently of target');
  same(a.pos,v(f(100+motion.x),f(200+motion.y),f(300+motion.z)),'carry added once with f32 boundaries');
  same([a.hSpeed,a.hDecel,a.yVel,a.gravityCoeff,a.poseAccum7c,a.poseAccum7e,a.poseAccum80,a.accumulator80c],Array(8).fill(0),'source entry clears velocity/pose/afterimage fields');
 }
 for(const target of [null,v(10000,200,-10000)]){
  const a=fixture();a.lockTarget=target;a.targetCache5e8={...a.pos};drive(a);
  same(a.motion,v(0,0,0),'stationary entry cannot acquire target-distance carry');same(a.pos,v(100,200,300),'stationary position remains unchanged');
 }
 {
  const a=fixture(),events:string[]=[];a.controlWord=0xb3;a.streamSlot=7;
  a.onStartStream=(group,slot,mask)=>{events.push('stream');same([group,slot,mask],[2,7,15],'entry keeps authored stream selection');
   same([a.hSpeed,a.hDecel,a.yVel,a.gravityCoeff,a.poseAccum7c,a.poseAccum7e,a.poseAccum80],[9,8,7,6,5,4,3],'stream starts before zeroing motion/pose');return true;};
  a.physicsRuntime={clampToGround:(pos,velY)=>{events.push('floor');
   same([a.hSpeed,a.hDecel,velY,a.gravityCoeff,a.poseAccum7c,a.poseAccum7e,a.poseAccum80],Array(7).fill(0),'floor probe follows source resets');
   assert(pos.z>300&&a.accumulator80c===2,'carry precedes floor;80c reset follows it');return {y:150,velY:0,grounded:true};}};
  drive(a);same(events,['stream','floor'],'source start/reset/carry/probe ordering');
  same([a.pos.y,a.accumulator80c,a.controlWord],[150,0,3],'floor result followed by80c reset and sourcecontrol mask');
 }
 {
  const a=fixture();a.pos=v(f(1e7),f(.000123),f(-98765.5));a.targetCache5e8=v(f(-.3),f(-.000001),f(1.125));
  const pos={...a.pos},old={...a.targetCache5e8};drive(a);
  for(const axis of ['x','y','z'] as const){const expected=f(f(pos[axis]-old[axis])*f(.95));
   same(a.motion[axis],expected,'subtract and scale round separately');same(a.pos[axis],f(pos[axis]+expected),'addition rounds after stored carry');}
 }
 {
  const a=fixture();a.savedGroundPos=v(40,50,60);a.physicsRuntime={isSupported:()=>false,clampToGround:()=>{throw Error('unsupported floor must not clamp');}};
  drive(a);same(a.pos,v(40,50,60),'existing679d0 unsupported-floor adapter restores current saved position');
  assert(a.accumulator80c===0,'80c resets after unsupported-floor return too');
 }
 assert(GRED_DASH.MOTION_DECAY===.95&&GRED_DASH.MOTION_DECAY!==GRED_DASH.ENTRY_CARRY,'other phases retain their preexisting numeric constant');
 console.log('[gredShotCarry] PASS: own-history f32 carry, null-target behavior, pose resets and source phase0 ordering');
}
