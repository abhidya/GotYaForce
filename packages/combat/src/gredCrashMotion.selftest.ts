/** Four bounded G Crash math corrections. Pure phase fixtures isolate arithmetic;
 * real neutral X verifies live own-history carry, not directional admission or
 * source stream/contact/timeout parity. JS trig approximates original helpers. */
import {createGRedRootAction} from './families/gred.js';
import {createRomActor,type Vec3} from './rom/actor.js';
import {RomDriverBridge} from './bridge.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs,f=Math.fround;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(a:unknown,s:string):asserts a {if(!a)throw Error(`[gredCrashMotion] ${s}`);}
function same(a:unknown,b:unknown,s:string){assert(JSON.stringify(a)===JSON.stringify(b),`${s}: ${JSON.stringify(a)} != ${JSON.stringify(b)}`);}
function near(a:number,b:number,s:string){assert(Math.abs(a-b)<1e-7,`${s}: ${a} != ${b}`);}
const drive=createGRedRootAction({});
function actor(phase:number,id=0x615){
 const a=Object.assign(createRomActor(),{grounded:false,lockTarget:null as Vec3|null,onStartStream:()=>true});
 a.borgNumber=id;a.actionIndex=2;a.variantIndex=0;a.fbPhaseSlots[0]=phase;
 a.pos=v(100,1000,200);a.savedGroundPos={...a.pos};a.targetCache5e8={...a.pos};a.motion=v(0,0,0);
 a.activeYaw=0;a.heading=0;a.steerYaw=0;a.dt=1;a.timescale=1;a.tierScale=1;
 a.gravityCoeff=0;a.hDecel=0;a.maxHSpeed=0;a.maxRise=0;a.maxFall=-1000;a.contactP0=0;
 return a;
}
function testOwnHistoryCarry(){
 for(const id of [0x615,0x629,0x62a])for(const target of [null,v(100,1000,500),v(9000,3000,-7000)]){
  const a=actor(0,id);a.lockTarget=target;a.targetCache5e8=v(99,998,196);drive(a);
  const expected=v(f(1*f(.95)),f(2*f(.95)),f(4*f(.95)));
  same(a.motion,expected,'phase0 uses own saved5e8 even without target');
  same(a.pos,v(f(100+expected.x),f(1000+expected.y),f(200+expected.z)),'phase0 adds own carry once');
  same([a.hSpeed,a.yVel,a.gravityCoeff],[0,id===0x615?4:0,0],'unchanged identity-specific launch constants');
 }
 const still=actor(0);still.lockTarget=v(10000,1000,-10000);drive(still);
 same(still.motion,v(0,0,0),'stationary own history yields zero carry despite distant enemy');
 same(still.pos,v(100,1000,200),'phase0 cannot teleport relative to enemy');
}
function testAccelerationAndTrig(){
 for(const yaw of [0,0x4000,-0x4000,0x8000,0xffff,12345]){
  const a=actor(2);a.motion=v(0,10,60);a.steerYaw=yaw;const before={...a.pos};drive(a);
  const signed=(yaw<<16)>>16,angle=f(signed*.0000958738019107841),h=f(10*f(Math.cos(angle))),y=f(-10*f(Math.sin(angle)));
  same(a.motion,v(10,10,60),'phase2 increments x accumulator, leaving acceleration and cap unchanged');
  // Existing integrator clamps horizontal velocity after displacement; observe
  // preclamp signed projection through position, not a new physics contract.
  near(a.pos.z-before.z,h,'signed BAM cosine projects horizontal movement');near(a.pos.y-before.y,y,'signed BAM sine projects vertical movement');
  near(a.hSpeed,Math.max(0,h),'inherited horizontal floor remains');near(a.yVel,y,'zero-gravity fixture preserves projected vertical speed');
 }
 const a=actor(2);a.motion=v(0,10,60);for(let i=1;i<=8;i++){drive(a);same(a.motion,v(Math.min(10*i,60),10,60),'linear acceleration reaches cap without doubling y');}
 const fractional=actor(2);fractional.dt=.5;fractional.motion=v(58,10,60);drive(fractional);same(fractional.motion,v(60,10,60),'fractional positive dt clamps accumulator at cap');
 const fused=actor(2);fused.dt=.75;fused.motion=v(f(.1),f(1.0000001192092896),60);
 const expected=f(fused.motion.y*fused.dt+fused.motion.x),doubleRounded=f(f(fused.motion.y*fused.dt)+fused.motion.x);
 assert(expected!==doubleRounded,'fixture distinguishes one-rounding multiply-add');drive(fused);same(fused.motion.x,expected,'one final f32 rounding for source fmadds');
 const transition=actor(1);transition.contactP0=1;drive(transition);same([transition.fbPhaseSlots[0],transition.motion],[2,v(0,10,60)],'existing phase1 contact transition seeds accumulator/acceleration/cap');
}
function testRecoveryDecay(){
 for(const input of [0,1,-1,17,-17,32767,32768,65535]){
  const a=actor(3);a.steerYaw=input;const expected=(Math.trunc(f(((input<<16)>>16)*f(.9)))<<16)>>16;
  drive(a);same(a.steerYaw,expected,'phase3 signed conversion and truncation, no invented176 subtraction');
 }
 const zero=actor(3);for(let i=0;i<5;i++)drive(zero);same(zero.steerYaw,0,'zero steering remains zero throughout recovery');
}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function realX(id:string,distance:number){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[{team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput()},tick=()=>battle.step(1/60,input);for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'live source driver');
 const before={...owner.pos};input.p1.special=true;tick();assert(owner.command?.exact&&owner.command.actionIndex===2,'real neutral X admits action2');
 const trace=[{x:owner.pos.x-before.x,y:owner.pos.y-before.y,z:owner.pos.z-before.z}];
 input.p1.special=false;for(let i=0;i<3;i++){tick();trace.push({x:owner.pos.x-before.x,y:owner.pos.y-before.y,z:owner.pos.z-before.z});}
 assert(trace.every(p=>Math.hypot(p.x,p.z)<1),'stationary real X has no target-distance horizontal teleport');
 return trace;
}
export function runGredCrashMotionSelfTest(){
 testOwnHistoryCarry();testAccelerationAndTrig();testRecoveryDecay();
 for(const id of ['pl0615','pl0629','pl062a'])same(realX(id,300),realX(id,3000),`${id}: near/far enemy cannot change initial own-history X motion; vertical behavior is compared only within this ID`);
 console.log('[gredCrashMotion] PASS: own-history carry, scalar acceleration, signed BAM projection, recovery conversion and actual X');
}
