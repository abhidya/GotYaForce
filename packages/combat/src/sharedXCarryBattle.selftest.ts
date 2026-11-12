/** Actual shared-X phase0 carry only. Later special clocks, callbacks and recovery
 * are deliberately not claimed repaired; host movement and terrain are adapters. */
import {RomDriverBridge} from './bridge.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import type {RomHelperScratch} from './rom/helpers.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[sharedXCarryBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0000',distance=1000){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const familyEvents:number[][]=[];const family=driver.ctx.onFamilyProjectile;driver.ctx.onFamilyProjectile=(a,address,row)=>{familyEvents.push([address,row]);family?.(a,address,row);};
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;driver.ctx.onArmHit=(a,k,status,arg)=>{hitArms.push([k,status,arg]);arm?.(a,k,status,arg);};
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,hitArms,familyEvents,get frame(){return frame;},};
}
type Fixture=ReturnType<typeof setup>;
const ids=['pl0000','pl000a','pl000c'] as const;
function press(t:Fixture,loseTarget=false){
 const observation:{before?:Vec3;history?:Vec3;saved?:Vec3;after?:Vec3;motion?:Vec3;reset?:number[]}={};
 t.actor.poseAccum7c=123;t.actor.poseAccum7e=-456;t.actor.poseAccum80=789;t.actor.accumulator80c=123;
 const root=t.actor.rootAction!;
 t.actor.rootAction=a=>{
  const phase0=a.actionIndex===2&&a.fbPhaseSlots[0]===0;
  if(phase0){
   // Target-loss adjunct after genuine X selection. It tests the
   // source handler's no-target branch, not the host's automatic targeting UI.
   if(loseTarget)(a as typeof a & RomHelperScratch).lockTarget=null;
   observation.before={...a.pos};observation.history={...a.targetCache5e8};observation.saved={...a.savedGroundPos};
  }
  root(a);
  if(phase0){observation.after={...a.pos};observation.motion={...a.motion};observation.reset=[a.poseAccum7c,a.poseAccum7e,a.poseAccum80,a.accumulator80c];}
 };
 t.input.p1.special=true;t.tick();t.input.p1.special=false;t.actor.rootAction=root;
 const c=t.owner.command;assert(c?.exact&&c.actionIndex===2,'actual X selects family special action2');
 assert(observation.before&&observation.history&&observation.after&&observation.motion,'original phase0 was observed without replacing it');
 for(const axis of ['x','y','z'] as const){const expected=Math.fround(Math.fround(observation.before[axis]-observation.history[axis])*Math.fround(.95));assert(observation.motion[axis]===expected,'f32 carry derives from own5e8 regardless of lock target');}
 assert(observation.reset?.every(n=>n===0),'source resets all pose accumulators and80c');
 return observation;
}

function testStationaryDistances(){
 for(const id of ids){
  const traces:Vec3[][]=[];
  for(const distance of [500,1000,2000]){
   const t=setup(id,distance),before={...t.owner.pos};const o=press(t);
   assert(o.motion!.x===0&&o.motion!.y===0&&o.motion!.z===0,'stationary own-history contributes zero carry');
   assert(t.owner.pos.x===before.x&&t.owner.pos.z===before.z,'actual X does not teleport away by enemy distance');
   const trace=[{...t.owner.pos}];for(let i=0;i<8;i++){t.tick();trace.push({...t.owner.pos});}
   assert(trace.every(p=>p.x===before.x&&p.z===before.z),'phase0 cannot seed target-distance drift into later calls');traces.push(trace);
  }
  assert(JSON.stringify(traces[0])===JSON.stringify(traces[1])&&JSON.stringify(traces[1])===JSON.stringify(traces[2]),'same-family short traces do not depend on target distance');
 }
}
function testMovingHistoryAndTargetLoss(){
 for(const id of ids)for(const lost of [false,true]){
  const t=setup(id,2000);t.input.p1.moveZ=1;for(let i=0;i<4;i++)t.tick();t.input.p1.moveZ=0;
  const o=press(t,lost);
  assert(Math.abs(o.motion!.x)+Math.abs(o.motion!.y)+Math.abs(o.motion!.z)>0,'actual movement supplies nonzero own previous-position carry');
  for(const axis of ['x','z'] as const)assert(o.after![axis]===Math.fround(o.before![axis]+o.motion![axis]),'phase0 adds f32 own carry once with or without captured target');
  assert(Math.hypot(o.after!.x-o.before!.x,o.after!.z-o.before!.z)<50,'moving carry remains bounded independently of enemy distance');
 }
}
function testTerrainOrdering(){
 const t=setup();t.input.p1.moveZ=1;for(let i=0;i<4;i++)t.tick();t.input.p1.moveZ=0;
 const physics=t.actor.physicsRuntime!,original=physics.probeMotion;const observed:Vec3[]=[];
 // Explicit host probe seam: records the carried position but preserves ordinary
 // collision behavior. It does not assert original triangle/bone geometry parity.
 physics.probeMotion=(previous,pos,velY)=>{observed.push({...pos});return original?original(previous,pos,velY):{velY,grounded:true};};
 const o=press(t);if(original)physics.probeMotion=original;else delete physics.probeMotion;
 assert(observed.some(p=>p.x===o.after!.x&&p.z===o.after!.z),'terrain adapter observes phase0 carried position');
 assert(Number.isFinite(t.owner.pos.x)&&Number.isFinite(t.owner.pos.z),'host terrain result remains finite');
}
export function runSharedXCarryBattleSelfTest(){testStationaryDistances();testMovingHistoryAndTargetLoss();testTerrainOrdering();console.log('[sharedXCarryBattle] PASS: actual X own-history carry, target independence and terrain seam');}
