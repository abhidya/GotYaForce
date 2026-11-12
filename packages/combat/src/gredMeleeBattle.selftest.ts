/** Real-input G RED source chain tests. Target relocation isolates host collision geometry;
 * no contact flag, action command, stream, or retap is synthesized. */
import {RomDriverBridge} from './bridge.js';
import {battleStateForSelfcheck,createBattle} from './battle.js';
import {getNeoGredMeleeState} from './neoGredMelee.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import {type Vec3} from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with {type:'json'};
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(value:unknown,label:string):asserts value {if(!value)throw Error(`[gredMeleeBattle] ${label}`);}
function floor():StageCollision {
 const vertices:[Vec3,Vec3,Vec3][]=[
 [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
 [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,layerIndex:0,marker:0xcccccccc,
 normal:v(0,1,0),planeD:0,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0615') {
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
 const sampleSlots:(number|undefined)[]=[];
 const driver=owner.romDriver,sourceTick=driver.tick.bind(driver);
 driver.tick=(actor,dt,all,input,emit)=>sourceTick(actor,dt,all,input,sample=>{sampleSlots.push(getNeoGredMeleeState(driver.actor)?.stream?.slot);emit?.(sample);});
 const hitArms:number[][]=[];const arm=driver.ctx.onArmHit;
 driver.ctx.onArmHit=(a,kind,status,arg)=>{hitArms.push([kind,status,arg]);arm?.(a,kind,status,arg);};
 const start=streamActor.onStartStream;
 streamActor.onStartStream=(group,slot,mask)=>{starts.push({group,slot,frame});return start(group,slot,mask);};
 const motion:{y:number;vy:number;grounded:boolean}[]=[];
 const near=()=>{target.pos=v(owner.pos.x+Math.sin(owner.rotY)*80,owner.pos.y,owner.pos.z+Math.cos(owner.rotY)*80);target.vel=v(0,0,0);};
 const far=()=>{target.pos=v(15000,10,15000);target.vel=v(0,0,0);};
 return {battle,state,owner,target,receiver,actor,inputs,tick,starts,animations,motion,sampleSlots,hitArms,near,far,get frame(){return frame;},get neo(){return getNeoGredMeleeState(actor);}};
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
 assert(t.neo?.stream?.slot===0 && t.starts.some(s=>s.group===3&&s.slot===0),'G RED opens source slot0');
}
function until(t:Fixture,predicate:()=>boolean,label:string,place=t.near,limit=180){
 for(let i=0;i<limit&&!predicate();i++){place();t.tick();if(t.neo?.stream)sourceSample(t);assert(t.actor.variantIndex!==6,'G RED null callback never redirects to NEO variant6');}
 assert(predicate(),`${label}; slot=${t.neo?.stream?.slot} frame=${t.neo?.stream?.frame} count=${t.neo?.acceptedContactCount}`);
}
function retap(t:Fixture){t.inputs.p1.attack=false;t.near();t.tick();t.inputs.p1.attack=true;t.near();t.tick();}
function chainToThird(){
 const t=setup();admit(t);const s=t.neo!;let animationSerial=sourceSample(t);
 for(const slot of [1,2]){
  const before=s.acceptedContactCount;
  until(t,()=>s.acceptedContactCount>before,'actual swing contact accepted');retap(t);
  until(t,()=>s.stream?.slot===slot,`fresh retap advances to${slot}`);
  const nextSerial=sourceSample(t);assert(nextSerial!==animationSerial,'next combo play renews animation instance');animationSerial=nextSerial;
  assert(s.acceptedContactCount===before+1,'paired source records resolve once per swing and target');
 }
 assert(t.starts.filter(s=>s.group===3).map(s=>s.slot).join(',')==='0,1,2','exact three-swing stream sequence');
 return t;
}
function testChain(){
 const t=chainToThird(),s=t.neo!;
 t.inputs.p1.attack=false;until(t,()=>s.acceptedContactCount===3,'third swing receives actual contact');
 retap(t); // A fresh edge plus third-swing contact still cannot bypass authored aux0.
 until(t,()=>!t.neo,'source chain completes naturally');
 assert(!t.owner.sourceAnimSample,'chain terminal clears animation sampling');
 assert(s.acceptedContactCount===3,'third paired records do not multiply melee damage');
 assert(t.sampleSlots.length>0&&t.sampleSlots.every(slot=>slot===0),`mine receiving samples remain scoped to opener: ${t.sampleSlots.join(',')}`);
 assert(JSON.stringify(t.hitArms)===JSON.stringify([[1,0,255],[2,0,255],[20,25,255]]),'source HIT/status metadata is forwarded, without claiming an unbound defender status effect');
 assert(t.animations.map(a=>`${a.group}/${a.slot}`).join(',')==='3/0,3/1,3/15','source animation sequence, no invented recovery');
 assert(s.launchCount===0 && t.actor.variantIndex!==6,'no NEO finisher launch');
 assert(!t.starts.some(s=>s.group===3&&s.slot===3),'no implicit fourth swing');
}
function testNegatives(){
 for(const mode of ['held','miss','invincible','stick'] as const){
  const t=setup();admit(t);const s=t.neo!;
  if(mode==='invincible')t.target.invincTimer=1000;
  if(mode==='held'||mode==='stick')until(t,()=>s.acceptedContactCount>0,'negative control has real contact');
  if(mode==='stick'){t.inputs.p1.attack=false;t.inputs.p1.moveX=1;}
  if(mode==='miss'||mode==='invincible'){t.inputs.p1.attack=false;(mode==='miss'?t.far:t.near)();t.tick();t.inputs.p1.attack=true;}
  for(let i=0;i<100&&t.neo===s;i++){(mode==='miss'?t.far:t.near)();t.tick();}
  assert(!t.starts.some(s=>s.group===3&&(s.slot===1||s.slot===2)),`${mode} never chains`);
  if(mode==='miss'||mode==='invincible')assert(s.acceptedContactCount===0,`${mode} has no accepted contact`);
 }
 const t=setup();admit(t);t.inputs.p1.attack=false;
 // Explicit lifecycle injection, not synthesized successful chain admission.
 t.owner.hp=0;t.tick();assert(!t.owner.sourceAnimSample,'death clears animation sampling');assert(!t.neo,'death clears source action');
 for(let i=0;i<50;i++)t.tick();assert(!t.starts.some(s=>s.slot===1||s.slot===2),'interruption does not resume chain');
 for(const id of ['pl062a','pl0629']){const n=setup(id);n.inputs.p1.attack=true;n.tick();assert(!n.starts.some(s=>s.group===3&&s.slot===0),`${id} never takes G RED stream`);}
}
export function runGredMeleeBattleSelfTest(){testAnimationHoldAndReplay();testChain();testNegatives();console.log('[gredMeleeBattle] PASS: actual source chain, accepted hit/retap gating, terminal and interruption');}
