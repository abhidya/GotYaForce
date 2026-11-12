/** Real-input G BLACK source chain tests. Target relocation isolates host collision geometry;
 * no contact flag, action command, stream, or retap is synthesized. */
import {RomDriverBridge} from './bridge.js';
import {spawnTimeBomberMine} from './timeBomberMineAdapter.js';
import {battleStateForSelfcheck,createBattle} from './battle.js';
import {getNeoGredMeleeState} from './neoGredMelee.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import {type Vec3} from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with {type:'json'};
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(value:unknown,label:string):asserts value {if(!value)throw Error(`[gblackMeleeBattle] ${label}`);}
function floor():StageCollision {
 const vertices:[Vec3,Vec3,Vec3][]=[
 [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
 [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,layerIndex:0,marker:0xcccccccc,
 normal:v(0,1,0),planeD:0,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl062a') {
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']} ]},stats);
 const inputs={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,inputs);};
 for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!;
 const receiver=state.borgs.find(b=>b.ownerPlayer==='p3')!;receiver.pos=v(-15000,10,-15000);
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;owner.grounded=true;
 target.pos=v(0,10,170);target.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();
 assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const actor=owner.romDriver.actor;
 const starts:{group:number;slot:number;frame:number}[]=[];
 const streamActor=actor as typeof actor & {onStartStream:(group:number,slot:number,mask:number)=>boolean};
 const animations:{group:number;slot:number}[]=[];
 const play=owner.romDriver.ctx.onPlayAnim;
 owner.romDriver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot});play?.(a,group,slot,blend);};
 const start=streamActor.onStartStream;
 streamActor.onStartStream=(group,slot,mask)=>{starts.push({group,slot,frame});return start(group,slot,mask);};
 const motion:{y:number;vy:number;grounded:boolean}[]=[];
 const near=()=>{target.pos=v(owner.pos.x+Math.sin(owner.rotY)*80,owner.pos.y,owner.pos.z+Math.cos(owner.rotY)*80);target.vel=v(0,0,0);};
 const far=()=>{target.pos=v(15000,10,15000);target.vel=v(0,0,0);};
 return {battle,state,owner,target,receiver,actor,inputs,tick,starts,animations,motion,near,far,get frame(){return frame;},get neo(){return getNeoGredMeleeState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
/** Simulation contract only: the renderer's pose sampling is tested separately. */
function sourceSample(t:Fixture):number {
 const stream=t.neo?.stream,sample=t.owner.sourceAnimSample;
 assert(stream&&sample,'admitted source melee publishes an animation sample');
 assert(sample.frame===stream.frame,'sample exactly follows current source animation frame');
 return sample.serial;
}
function testAnimationHoldAndReplay(){
 const t=setup();admit(t);t.inputs.p1.attack=false;const serial=sourceSample(t);
 for(let i=0;i<20&&t.neo?.stream?.blendMode!==0;i++){
  assert(t.neo?.stream?.frame===0,'mode1 initial blend holds frame0');
  t.far();t.tick();assert(sourceSample(t)===serial,'blend updates preserve animation instance');
 }
 until(t,()=>t.neo?.stream?.frame===7,'actual intermediate source frame7',t.far);
 assert(t.owner.sourceAnimSample?.frame===7&&sourceSample(t)===serial,'intermediate sample is exact, not free-running');
 until(t,()=>!t.neo,'unretapped source opener completes',t.far);
 assert(!t.owner.sourceAnimSample,'normal source exit clears sampling');
 for(let i=0;i<180&&(t.owner.state!=='idle'||(t.owner.cooldowns['shot']??0)>0);i++){t.far();t.tick();}
 assert(t.owner.state==='idle','actual recovery completes before fresh replay');
 for(let i=0;i<4;i++){t.near();t.tick();}
 admit(t);assert(sourceSample(t)!==serial,'fresh play of same animation gets a new instance serial');
}
function admit(t:Fixture){
 t.inputs.p1.attack=true;t.tick();
 assert(t.owner.command?.exact && t.owner.command.actionIndex===1 && t.owner.command.variantIndex===0,'real neutral B admits source action1/v0');
 assert(t.neo?.stream?.slot===13 && t.starts.some(s=>s.group===3&&s.slot===13),'G BLACK opens source slot13');
}
function until(t:Fixture,predicate:()=>boolean,label:string,place=t.near,limit=180){
 for(let i=0;i<limit&&!predicate();i++){place();t.tick();if(t.neo?.stream)sourceSample(t);assert(t.actor.variantIndex!==6,'G BLACK null callback never redirects to NEO variant6');}
 assert(predicate(),`${label}; slot=${t.neo?.stream?.slot} frame=${t.neo?.stream?.frame} count=${t.neo?.acceptedContactCount}`);
}
function retap(t:Fixture){t.inputs.p1.attack=false;t.near();t.tick();t.inputs.p1.attack=true;t.near();t.tick();}
function chainToThird(){
 const t=setup();admit(t);const s=t.neo!;let animationSerial=sourceSample(t);
 for(const slot of [14,15]){
  const before=s.acceptedContactCount;
  until(t,()=>s.acceptedContactCount>before,'actual swing contact accepted');retap(t);
  until(t,()=>s.stream?.slot===slot,`fresh retap advances to${slot}`);
  const nextSerial=sourceSample(t);assert(nextSerial!==animationSerial,'next combo play renews animation instance');animationSerial=nextSerial;
  assert(s.acceptedContactCount===before+1,'paired source records resolve once per swing and target');
 }
 assert(t.starts.filter(s=>s.group===3).map(s=>s.slot).join(',')==='13,14,15','exact three-swing stream sequence');
 return t;
}
function testChain(){
 const t=chainToThird(),s=t.neo!;
 t.inputs.p1.attack=false;until(t,()=>s.acceptedContactCount===3,'third swing receives actual contact');
 retap(t); // A fresh edge plus third-swing contact still cannot bypass authored aux0.
 until(t,()=>!t.neo,'source chain completes naturally');
 assert(!t.owner.sourceAnimSample,'chain terminal clears animation sampling');
 assert(s.acceptedContactCount===3,'third paired records do not multiply melee damage');
 assert(s.launchCount===0 && t.actor.variantIndex!==6,'no NEO finisher launch');
 assert(!t.starts.some(s=>s.group===3&&s.slot===16),'no implicit fourth swing');
 assert(t.animations.map(a=>`${a.group}/${a.slot}`).join(',')==='3/24,3/4,3/23','source animation mapping');
}
function testNegatives(){
 for(const mode of ['held','miss','invincible','stick'] as const){
  const t=setup();admit(t);const s=t.neo!;
  if(mode==='invincible')t.target.invincTimer=1000;
  if(mode==='held'||mode==='stick')until(t,()=>s.acceptedContactCount>0,'negative control has real contact');
  if(mode==='stick'){t.inputs.p1.attack=false;t.inputs.p1.moveX=1;}
  if(mode==='miss'||mode==='invincible'){t.inputs.p1.attack=false;(mode==='miss'?t.far:t.near)();t.tick();t.inputs.p1.attack=true;}
  for(let i=0;i<100&&t.neo===s;i++){(mode==='miss'?t.far:t.near)();t.tick();}
  assert(!t.starts.some(s=>s.group===3&&(s.slot===14||s.slot===15)),`${mode} never chains`);
  if(mode==='miss'||mode==='invincible')assert(s.acceptedContactCount===0,`${mode} has no accepted contact`);
 }
 const t=setup();admit(t);t.inputs.p1.attack=false;
 // Explicit lifecycle injection, not synthesized successful chain admission.
 t.owner.hp=0;t.tick();assert(!t.owner.sourceAnimSample,'death clears animation sampling');assert(!t.neo,'death clears source action');
 for(let i=0;i<50;i++)t.tick();assert(!t.starts.some(s=>s.slot===14||s.slot===15),'interruption does not resume chain');
 for(const id of ['pl0615','pl0629']){const n=setup(id);n.inputs.p1.attack=true;n.tick();assert(!n.starts.some(s=>s.group===3&&s.slot===13),`${id} never takes G BLACK stream`);}
}
function waves(t:Fixture){return t.state.projectiles.filter(p=>p.gblackGroundWaveSource!==undefined);}
function spawnWave(collisionScale?:number){
 const t=chainToThird();if(collisionScale!==undefined)t.actor.collisionScale=collisionScale;t.inputs.p1.attack=false;const s=t.neo!;
 until(t,()=>s.groundWaveCount>0,'actual third stream callback creates wave');
 assert(s.groundWaveCount===1,'callback allocates one wave');
 assert(waves(t).filter(p=>p.gblackGroundWaveSource?.kind==='parent').length===1,'one real parent emitter');
 return t;
}
function testWaveChildren(){
 const t=spawnWave(.6),s=t.neo!,parent=waves(t).find(p=>p.gblackGroundWaveSource?.kind==='parent')!;
 const first=waves(t).find(p=>p.gblackGroundWaveSource?.kind==='child')!;
 assert(first?.gblackGroundWaveSource?.phase==='pending','host ordering: callback parent initializes now, new child waits until next projectile pass (not claimed source scheduler parity)');
 t.far();t.tick();
 const child=()=>{const c=first.gblackGroundWaveSource!;assert(c.kind==='child','child source kind');return c;};assert( child().phase==='active' && child().age===0 && child().life===30 && child().hitActive,'next host pass registers child at age0/life30');
 assert(child().collisionScale===.6 && child().modelScale!==.6 && first.hitRadius===90,'explicit c0 changes collision radius independently of model scale and visual squash');
 assert(first.damageRecord?.index===9 && first.damageRecord.hpDamage===20 && first.damageRecord.flagsA===0x20,'pulse retains global damage9 HP20 flags20, not family-local9');
 // Receiver relocation is explicit geometry setup, with an untouched third fighter.
 t.receiver.pos={...first.pos};t.receiver.vel=v(0,0,0);const hp=t.receiver.hp;t.tick();
 assert(t.receiver.hp<hp && child().hitUids.includes(t.receiver.uid),'real wave pulse damages fresh overlapping receiver');
 const after=t.receiver.hp;t.receiver.pos={...first.pos};t.receiver.vel=v(0,0,0);t.tick();
 assert(t.receiver.hp===after,'same pulse does not damage its victim twice');
 until(t,()=>waves(t).some(p=>p!==first&&p.gblackGroundWaveSource?.kind==='child'&&p.gblackGroundWaveSource.phase==='active'),'another child becomes independently active',t.far);
 const next=waves(t).find(p=>p!==first&&p.gblackGroundWaveSource?.kind==='child'&&p.gblackGroundWaveSource.phase==='active')!;
 assert(next.uid!==first.uid && !next.gblackGroundWaveSource!.hitUids.includes(t.receiver.uid),'each child owns fresh identity and victim history');
 // Explicitly clear receiver immunity only to isolate independent pulse admission.
 t.receiver.invincTimer=0;t.receiver.pos={...next.pos};t.receiver.vel=v(0,0,0);const hp2=t.receiver.hp;t.tick();
 assert(t.receiver.hp<hp2 && next.gblackGroundWaveSource!.hitUids.includes(t.receiver.uid),'new pulse can damage same receiver independently');
 t.receiver.pos=v(-15000,10,-15000);
 until(t,()=>child().age===29,'first pulse reaches final active age',t.far);
 assert(!child().hitUids.includes(t.target.uid),'expiry receiver has not been hit by this pulse');
 t.target.pos={...first.pos};t.target.vel=v(0,0,0);const expiryHp=t.target.hp;t.tick();
 assert(t.target.hp===expiryHp && !child().hitUids.includes(t.target.uid),'age30 disables HIT before collision with a fresh victim');
 assert(child().age===30 && !child().hitActive,'age30 turns collision off before that pass');
 assert(parent.gblackGroundWaveSource?.phase==='active','pulse lifetime is independent from live emitter');
 assert(s.groundWaveCount===1,'later source updates do not repeat callback allocation');
}
function testWaveInvalidationAndGates(){
 {
  const t=spawnWave();t.far();t.tick();
  const parent=waves(t).find(p=>p.gblackGroundWaveSource?.kind==='parent')!,child=waves(t).find(p=>p.gblackGroundWaveSource?.kind==='child')!;
  // Synthetic near-expiry counter isolates parent/child lifetime independence.
  parent.gblackGroundWaveSource!.life=1;t.tick();
  assert(parent.gblackGroundWaveSource?.phase==='retiring','parent normal expiry retires emitter');
  assert(child.gblackGroundWaveSource?.phase==='active' && child.gblackGroundWaveSource.kind==='child' && child.gblackGroundWaveSource.hitActive,'normal emitter expiry leaves child independently active');
 }

 for(const invalidation of ['death','borg','form'] as const){
  const t=spawnWave();t.far();t.tick();
  const existing=waves(t);assert(existing.some(p=>p.gblackGroundWaveSource?.kind==='child'),'fixture has child');
  // Explicit owner-lifecycle injections, distinct from real input admission.
  if(invalidation==='death')t.owner.hp=0;else if(invalidation==='borg')t.owner.borgId='pl0615';else t.owner.combatFormId='fixture-other-form';
  t.tick();
  assert(existing.every(p=>p.gblackGroundWaveSource?.phase==='released'||p.gblackGroundWaveSource?.phase==='freed'),`${invalidation} invalidates parent and children`);
  assert(existing.every(p=>p.gblackGroundWaveSource?.kind!=='child'||!p.gblackGroundWaveSource.hitActive),`${invalidation} disables child HIT immediately`);
 }
 for(const gate of ['support','airFlag'] as const){
  const t=chainToThird();t.inputs.p1.attack=false;const s=t.neo!;
  until(t,()=>s.stream!.frame>=21,'approach source callback boundary');
  // Explicit source flag fixtures test callback gates, not a synthetic attack.
  if(gate==='support')t.actor.supportContact1db=1;else t.actor.controlWord|=0x40;
  until(t,()=>s.stream!.frame>22,'cross callback boundary',t.far);
  assert(s.groundWaveCount===0 && waves(t).length===0,`${gate} rejects functional callback`);
 }
}
function testWaveMineReception(){
 for(const mode of ['differentOwner','sameOwnerDrift','sameOwnerBob'] as const){
  const t=spawnWave();t.far();t.tick();
  const pulse=waves(t).find(p=>p.gblackGroundWaveSource?.kind==='child'&&p.gblackGroundWaveSource.phase==='active')!;
  assert(pulse,'real B chain creates active wave pulse');
  const owner=mode==='differentOwner'?t.receiver:t.owner;
  assert(owner.romDriver instanceof RomDriverBridge,'mine fixture owner has actor');
  // Actual mine constructor plus explicit active-state/geometry fixture. This is
  // not Time Bomber input admission; no cell was consumed, so no refund is owed.
  const mine=spawnTimeBomberMine(owner,owner.romDriver.actor),m=mine.timeBomberSource!;
  assert(m.kind==='mine','constructor produces mine source');
  const pos=v(pulse.pos.x+100,pulse.pos.y+80,pulse.pos.z);
  Object.assign(m,{phase:'active',motion:mode==='sameOwnerBob'?'bob':'drift',pos:{...pos},center:{...pos},
    direction:v(0,0,0),speed:5,life:100,bobPhase:0,floorTarget:0,resourceOwed:false});
  mine.pos={...pos};t.state.projectiles.push(mine);t.far();t.tick();
  const source=mine.timeBomberSource!;assert(source.kind==='mine','mine remains typed');
  if(mode==='sameOwnerDrift'){
   assert(source.phase==='active'&&source.durability===1&&!source.receivedAttackUids.includes(pulse.uid),'same-owner drift rejects pulse');
   assert(!pulse.gblackGroundWaveSource!.hitUids.includes(mine.uid),'rejected pair does not consume pulse victim slot');
  }else{
   assert(source.phase==='active'&&source.durability===0&&source.receivedAttackUids.includes(pulse.uid),`${mode} pulse destroys HP1 mine during collision`);
   assert(pulse.gblackGroundWaveSource!.hitUids.includes(mine.uid),'pulse records mine victim independently');
   assert(!t.state.projectiles.some(p=>p.timeBomberSource?.kind==='explosion'),'collision does not explode mine on same child update');
   t.far();t.tick();
   assert(mine.timeBomberSource?.kind==='mine'&&mine.timeBomberSource.phase==='retiring'&&t.state.projectiles.some(p=>p.timeBomberSource?.kind==='explosion'),'next child update retires destroyed mine and spawns explosion');
  }
 }
}
export function runGblackMeleeBattleSelfTest(){testAnimationHoldAndReplay();testChain();testNegatives();testWaveChildren();testWaveInvalidationAndGates();testWaveMineReception();console.log('[gblackMeleeBattle] PASS: real chain, paired-hit dedup, wave pulses/lifetimes, callback gates and negative controls');}
