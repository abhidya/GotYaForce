/** Bounded cfg80365634 tests. Real B validates the live dispatch and motion;
 * direct phase probes isolate config boundaries. Existing target-distance,
 * lunge-speed, stream and physics adapters are not full source-engine parity. */
import {createRomActor,type Vec3} from './rom/actor.js';
import {createGRedRootAction} from './families/gred.js';
import {createSharedMeleeGRed,GRED_ACTION1_VARIANT0_CONFIG,GRED_MELEE_CONFIG} from './families/shared-melee-gred.js';
import {battleStateForSelfcheck,createBattle} from './battle.js';
import {RomDriverBridge} from './bridge.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import borgsData from '../../assets/data/borgs.json' with {type:'json'};
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
const K=Math.fround(.95);
function assert(value:unknown,message:string):asserts value {if(!value)throw Error(`[gredMeleeConfig] ${message}`);}
function near(actual:number,expected:number,message:string) {assert(Math.abs(actual-expected)<1e-8,`${message}: ${actual} != ${expected}`);}
function actor(phase=0) {
  const a=Object.assign(createRomActor(),{grounded:true,lockTarget:v(0,1000,10000),curSpeed:200,
    altChainGate:false,altInput:false,bRetap:false,swingReArm:false,swingChainBit:false,
    onStartStream:(_group:number,_slot:number,_mask:number)=>true});
  a.pos=v(0,1000,0);a.savedGroundPos={...a.pos};a.actionIndex=1;a.variantIndex=0;a.borgNumber=0x615;
  a.fbPhaseSlots[0]=phase;a.activeYaw=0;a.heading=0;a.lockYaw=0;a.hSpeed=0;a.yVel=0;a.hDecel=0;a.contactP0=1;
  a.actionSpeedRows=[600,900,1200];a.prevActionIndex=0;return a;
}
function testDecodedConfigAndPhaseZero() {
  const c=GRED_ACTION1_VARIANT0_CONFIG;
  assert(c.seedSlot===0 && c.proximityRange===150 && c.timerFrames===20 && c.decel===0.949999988079071,
    'original config fields are seed0, proximity150, timer20 and exact f32 decel');
  assert(c.chainCallback===undefined && c.altChainCallback===undefined,'both original null callback slots stay absent');
  const a=actor(),starts:{group:number;slot:number;mask:number}[]=[];
  a.onStartStream=(group,slot,mask)=>{starts.push({group,slot,mask});return true;};
  createGRedRootAction({})(a);
  assert(a.fbPhaseSlots[0]===1 && a.streamSlot===1 && a.handlerTimer===60,'phase0 preserves facing timer60 and increments seed0');
  assert(starts.length===1 && starts[0]!.group===3 && starts[0]!.slot===0 && starts[0]!.mask===15,'actual config starts g3/slot0 with full part mask');
}
function testTimerAndProximity() {
  const drive=createSharedMeleeGRed(GRED_ACTION1_VARIANT0_CONFIG,{}),a=actor(1);a.handlerTimer=60;
  drive(a);assert(a.fbPhaseSlots[0]===2 && a.handlerTimer===20 && a.hSpeed===30,'face-ready phase1 seeds20 and row600/20 lunge');
  for(let i=1;i<20;i++){drive(a);assert(a.fbPhaseSlots[0]===2 && a.handlerTimer===20-i,`far target active update${i} retains exact timer`);}
  drive(a);assert(Number(a.fbPhaseSlots[0])===3 && Number(a.handlerTimer)===0,'twentieth active update reaches timer boundary');
  for(const distance of [149.999,150,150.001]) {
    const b=actor(2);b.handlerTimer=10;b.lockTarget=v(0,1000,distance);drive(b);
    assert(b.fbPhaseSlots[0]===(distance<=150?3:2),`host proximity adapter preserves inclusive150 boundary at${distance}`);
  }
  const half=actor(2);half.handlerTimer=.5;half.dt=.5;drive(half);
  assert(half.handlerTimer===0 && half.fbPhaseSlots[0]===3,'timer uses actor dt at fractional expiry boundary');
}
function testDecelerationAndRecovery() {
  const drive=createSharedMeleeGRed(GRED_ACTION1_VARIANT0_CONFIG,{});
  for(const phase of [2,3]) {
    const a=actor(phase);a.handlerTimer=20;a.hSpeed=20;a.yVel=4;
    drive(a);near(a.hSpeed,20*K,`phase${phase} scales horizontal speed before integration`);
    near(a.yVel,4*K,`phase${phase} scales vertical speed`);
    near(a.pos.z,20*K,`phase${phase} integrates one decelerated step`);near(a.pos.y,1000+4*K,`phase${phase} integrates vertical once`);
    drive(a);near(a.hSpeed,20*K*K,`phase${phase} deceleration compounds once per call`);
  }
  const brake=actor(3);brake.curSpeed=149.999;brake.hSpeed=20;brake.yVel=4;
  drive(brake);assert(brake.hSpeed===0 && brake.yVel===0 && brake.pos.z===0,'phase3 retains existing strict lower-than150 extra brake');
  const boundary=actor(3);boundary.curSpeed=150;boundary.hSpeed=20;drive(boundary);
  near(boundary.hSpeed,20*K,'curSpeed150 does not trigger strict extra brake');
  const callback=actor(3);callback.altChainGate=true;callback.swingReArm=true;callback.bRetap=true;callback.altInput=true;
  callback.streamSlot=1;drive(callback);
  assert(callback.fbPhaseSlots[0]===2 && callback.handlerTimer===20 && callback.streamSlot===2,
    'synthetic shared-engine rearm with null callbacks retains existing next-slot path and exact timer');
}
function testDispatchScope() {
  const root=createGRedRootAction({});
  for(const [id,variant] of [[0x615,0],[0x615,1],[0x615,2],[0x615,3],[0x615,4],[0x629,0],[0x629,1],[0x62a,0],[0x62a,1]] as const) {
    const exact=id===0x615 && variant===0,a=actor(1);a.borgNumber=id;a.variantIndex=variant;a.handlerTimer=60;root(a);
    assert(a.handlerTimer===(exact?20:30),`root config timer remains bounded for ${id.toString(16)}/${variant}`);
    near(a.hSpeed,600/(exact?20:30),'selected timer feeds existing lunge speed');
    const range=actor(2);range.borgNumber=id;range.variantIndex=variant;range.handlerTimer=10;range.lockTarget=v(0,1000,125);root(range);
    assert(range.fbPhaseSlots[0]===(exact?3:2),'only exact variant uses150 rather than legacy100');
    const motion=actor(2);motion.borgNumber=id;motion.variantIndex=variant;motion.handlerTimer=10;motion.hSpeed=20;root(motion);
    near(motion.hSpeed,20*(exact?K:1),'other IDs/variants retain prior no-decel path');
  }
  assert(GRED_MELEE_CONFIG.seedSlot===0 && GRED_MELEE_CONFIG.timerFrames===30 && GRED_MELEE_CONFIG.proximityRange===100 && GRED_MELEE_CONFIG.decel===undefined,
    'shared legacy placeholder object was not mutated');
}
function floor():StageCollision {
  const vertices:[Vec3,Vec3,Vec3][]=[
    [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
    [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)],
  ];
  return {triangles:vertices.map((vertices,index)=>({index,vertices,layerIndex:0,marker:0xcccccccc,normal:v(0,1,0),planeD:0,
    bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function testRealFreshB() {
  for(const id of ['pl0615','pl0629','pl062a']) {
    const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
      {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},
    ]},stats),inputs={p1:emptyInput(),p2:emptyInput()};
    const tick=()=>battle.step(1/60,inputs);for(let i=0;i<100;i++)tick();
    const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!;
    owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;owner.grounded=true;target.pos=v(0,10,170);target.vel=v(0,0,0);owner.lockTarget=target.uid;
    for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real actor has source bridge');
    const a=owner.romDriver.actor;inputs.p1.attack=true;tick();
    assert(owner.command?.exact && owner.command.type===1 && owner.command.actionIndex===1 && owner.command.variantIndex===0,'actual close B selects exact action1/v0');
    // Move target clear only after real close-B admission, isolating phase2 motion.
    target.pos=v(0,10,10000);target.vel=v(0,0,0);
    for(let i=0;i<8 && a.fbPhaseSlots[0]!==2;i++)tick();
    // All three fresh admitted families use source-backed20/.95 chains; direct legacy root probes above remain unchanged.
    const exact=id==='pl0615'||id==='pl0629'||id==='pl062a';assert(a.fbPhaseSlots[0]===2 && a.handlerTimer===(exact?20:30),`${id}: real source dispatch selects bounded timer`);
    const speed=a.hSpeed,before={...owner.pos},yaw=a.activeYaw*Math.PI/32768;
    tick();
    const expectedSpeed=exact?Math.fround(speed*K):speed;
    near(a.hSpeed,expectedSpeed,`${id}: actual phase2 speed decay`);
    near(owner.pos.x-before.x,expectedSpeed*Math.sin(yaw)*a.timescale*a.tierScale,`${id}: actual X movement integrates once`);
    near(owner.pos.z-before.z,expectedSpeed*Math.cos(yaw)*a.timescale*a.tierScale,`${id}: actual Z movement integrates once`);
    assert(Number(a.handlerTimer)===(exact?19:29),`${id}: actual timer advances once`);
  }
}
export function runGredMeleeConfigSelfTest():void {
  testDecodedConfigAndPhaseZero();testTimerAndProximity();testDecelerationAndRecovery();testDispatchScope();testRealFreshB();
  console.log('G RED action1/variant0 exact config: passed (pure boundaries and real B dispatch)');
}
