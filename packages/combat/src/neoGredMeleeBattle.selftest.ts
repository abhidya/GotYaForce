/** Real-input NEO source chain tests. Target relocation isolates host collision geometry;
 * no contact flag, action command, stream, or retap is synthesized. */
import {RomDriverBridge} from './bridge.js';
import {battleStateForSelfcheck,createBattle} from './battle.js';
import {getNeoGredMeleeState,prepareNeoGredMelee,stepNeoGredMelee} from './neoGredMelee.js';
import {emptyInput,type StageCollision} from './types.js';
import {buildProfile,type BorgStats} from './stats.js';
import {applyHit} from './combat.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {createRomActor,type Vec3} from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with {type:'json'};
const stats=(borgsData as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(value:unknown,label:string):asserts value {if(!value)throw Error(`[neoGredMeleeBattle] ${label}`);}
function floor():StageCollision {
 const vertices:[Vec3,Vec3,Vec3][]=[
 [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
 [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,layerIndex:0,marker:0xcccccccc,
 normal:v(0,1,0),planeD:0,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0629') {
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']} ]},stats);
 const inputs={p1:emptyInput(),p2:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,inputs);};
 for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!;
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
 return {battle,state,owner,target,actor,inputs,tick,starts,animations,motion,near,far,get frame(){return frame;},get neo(){return getNeoGredMeleeState(actor);}};
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
function admit(t:Fixture) {
 t.inputs.p1.attack=true;t.tick();
 assert(t.owner.command?.exact && t.owner.command.actionIndex===1 && t.owner.command.variantIndex===0,'real close B admits ground source action1/v0');
 assert(t.neo && t.starts.some(s=>s.group===3 && s.slot===25),'NEO starts source slot25');
 assert(t.neo.contactFlags709===1,'source shared opener sets709bit1');
}
function until(t:Fixture,predicate:()=>boolean,label:string,place=t.near,limit=180) {
 for(let i=0;i<limit&&!predicate();i++){
  const state=t.neo,count=state?.acceptedContactCount??0,slot=state?.stream?.slot;
  place();t.tick();if(t.neo?.stream)sourceSample(t);t.motion.push({y:t.owner.pos.y,vy:t.owner.vel.y,grounded:t.owner.grounded});
  if(slot===27 && t.neo===state)assert((state?.acceptedContactCount??0)-count<=1,'finisher overlapping boxes admit at most one contact per target per update');
 }
 assert(predicate(),`${label}; slot=${t.neo?.stream?.slot} frame=${t.neo?.stream?.frame} phase=${t.actor.fbPhaseSlots[0]} accepted=${t.neo?.acceptedContactCount}`);
}
function retap(t:Fixture) {t.inputs.p1.attack=false;t.near();t.tick();t.inputs.p1.attack=true;t.near();t.tick();}
function testContactAndRetapChain() {
 const t=setup();admit(t);const neo=t.neo!;const firstSerial=sourceSample(t);
 until(t,()=>neo.acceptedContactCount>0,'real opener collision accepted');
 assert(t.target.hp<t.target.maxHp,'actual collision lowers target HP');
 assert(neo.pendingContact!==0 || neo.alt745!==0,'accepted collision supplies source contact latch');
 retap(t);until(t,()=>neo.stream?.slot===26,'fresh retap plus accepted contact starts26');
 const secondSerial=sourceSample(t);assert(secondSerial!==firstSerial,'second combo has a new animation instance');
 until(t,()=>neo.stream?.frame===2,'mode2 blend advances to actual frame2');
 assert(neo.stream?.blendMode===2&&t.owner.sourceAnimSample?.frame===2,'mode2 blend advances its sample rather than freezing');
 assert(t.starts.filter(s=>s.group===3).map(s=>s.slot).join(',')==='25,26','actual stream sequence25,26');
 const accepted=neo.acceptedContactCount;
 until(t,()=>neo.acceptedContactCount>accepted,'second swing collision accepted');
 retap(t);until(t,()=>t.actor.variantIndex===6 && neo.stream?.slot===27,'second hit plus fresh retap enters finisher27');
 assert(t.starts.filter(s=>s.group===3).map(s=>s.slot).join(',')==='25,26,27','no extraneous source stream in chain');
 const finisherSerial=sourceSample(t);assert(finisherSerial!==secondSerial,'finisher starts a new animation instance');
 const beforeFinisherContacts=neo.acceptedContactCount;
 t.inputs.p1.attack=false;
 until(t,()=>neo.launchCount>0,'finisher performs actual launch');
 assert(neo.launchCount===1,'one finisher launch');
 until(t,()=>neo.stream?.recovery===true,'finisher reaches authored recovery');
 const finisherContacts=neo.acceptedContactCount-beforeFinisherContacts;
 assert(finisherContacts>0 && finisherContacts<=2,`finisher contacts ${finisherContacts}, prior=${beforeFinisherContacts}, targetHP=${t.target.hp}, state=${t.target.state}, invinc=${t.target.invincTimer}`);
 assert(neo.targetUid===t.target.uid,'finisher redispatch retains the actual locked target');
 assert(neo.stream?.slot===27 && neo.stream.frame===0,'recovery resets animation frame');
 assert(sourceSample(t)!==finisherSerial&&Number(t.owner.sourceAnimSample?.frame)===0,'recovery has a new instance at source frame0');
 until(t,()=>!t.neo,'finisher relinquishes source ownership',t.far);
 assert(!t.owner.sourceAnimSample,'finisher exit clears source animation sample');
 assert(neo.launchCount===1,'recovery does not relaunch');
 assert(t.motion.some(m=>m.y>30 && !m.grounded) && t.motion.some(m=>m.vy>0),'finisher produces observable upward displacement, vertical velocity and airborne state');
 until(t,()=>t.owner.grounded,'finisher eventually lands through actual physics',t.far,240);
 assert(t.animations.map(a=>`${a.group}/${a.slot}`).join(',')==='3/0,3/1,3/18,0/14','source stream animation mapping includes recovery');
 assert(t.actor.dt===1,'integration exercises admitted source dt1; other clocks are pure-tested separately');
}
function testInputAndContactNegatives() {
 for(const mode of ['held','noHit','stick','invincible'] as const) {
  const t=setup();admit(t);const neo=t.neo!;
  if(mode==='invincible')t.target.invincTimer=1000;
  if(mode!=='noHit' && mode!=='invincible')until(t,()=>neo.acceptedContactCount>0,`${mode} establishes actual contact`);
  if(mode==='noHit'||mode==='invincible'){t.inputs.p1.attack=false;(mode==='noHit'?t.far:t.near)();t.tick();t.inputs.p1.attack=true;}
  if(mode==='stick'){t.inputs.p1.attack=false;t.inputs.p1.moveX=1;}
  for(let i=0;i<100&&t.neo===neo;i++){(mode==='noHit'?t.far:t.near)();t.tick();}
  assert(!t.starts.some(s=>s.group===3 && (s.slot===26||s.slot===27)),`${mode} cannot chain`);
  assert(neo.launchCount===0,`${mode} cannot launch finisher`);
  if(mode==='noHit'||mode==='invincible')assert(neo.acceptedContactCount===0,`${mode} never supplies accepted contact`);
 }
}
function testInterruptionAndNeighbors() {
 const t=setup();admit(t);const neo=t.neo!;t.inputs.p1.attack=false;
 // Explicit lifecycle injection, separate from the positive real-input chain.
 t.owner.hp=0;t.tick();assert(!t.owner.sourceAnimSample,'death clears animation sampling');assert(!t.neo,'death clears admitted source state');
 for(let i=0;i<50;i++)t.tick();
 assert(neo.launchCount===0 && !t.starts.some(s=>s.slot===26||s.slot===27),'interruption cannot resurrect chain or launch');
 for(const id of ['pl0615','pl062a']) {
  const n=setup(id);n.inputs.p1.attack=true;n.tick();
  assert(n.neo?.family!=='neo' && !n.starts.some(s=>s.group===3 && s.slot===25),`${id} does not enter NEO source state`);
 }
}
/** Lower-level resolver contract adjunct, not a synthetic successful input chain. */
function testZeroHpAcceptanceContract() {
 const t=setup(),ownerProfile=buildProfile(stats.find(b=>b.id===t.owner.borgId)!),targetProfile=buildProfile(stats.find(b=>b.id===t.target.borgId)!);
 const record={...familyDamageRecordForBorg('pl0629',2)!,hpDamage:0};let accepted=0;
 const hp=t.target.hp;
 applyHit(t.target,targetProfile,0,0,v(0,0,1),t.owner.pos,false,record,
 {attacker:t.owner,attackerProfile:ownerProfile,onContactAccepted:()=>{accepted++;}});
 assert(accepted===1 && t.target.hp===hp,'zero-HP admitted resolver contact still calls acceptance');
 t.target.invincTimer=100;
 applyHit(t.target,targetProfile,0,0,v(0,0,1),t.owner.pos,false,record,
 {attacker:t.owner,attackerProfile:ownerProfile,onContactAccepted:()=>{accepted++;}});
 assert(accepted===1,'rejected zero-HP contact never calls acceptance');
}
/** Pure phase fixture isolates signed18da wrapper+engine arithmetic. It does not
 * claim a synthesized command or contact is reachable through player input. */
function testSignedWrapperAndEngineShift() {
 for(const variant of [0,6])for(const input of [17,-17,32767,32768,65535]) {
  const a=createRomActor();a.borgNumber=0x629;a.actionIndex=1;a.variantIndex=variant;
  a.fbPhaseSlots[0]=1;a.steerYaw=input;a.handlerTimer=20;a.contactP0=1;a.streamHold1b03=0;
  prepareNeoGredMelee(a,null);stepNeoGredMelee(a,{});
  const signed=(input<<16)>>16,expected=signed>>(variant===6?2:1);
  assert(a.steerYaw===expected,`variant${variant} signed18da ${input} becomes${expected}, got${a.steerYaw}`);
 }
}
export function runNeoGredMeleeBattleSelfTest() {
 testAnimationHoldAndReplay();testContactAndRetapChain();testInputAndContactNegatives();testInterruptionAndNeighbors();testZeroHpAcceptanceContract();testSignedWrapperAndEngineShift();
 console.log('[neoGredMeleeBattle] PASS: actual contact and fresh B chain, finisher, input negatives, interruption and isolation');
}
