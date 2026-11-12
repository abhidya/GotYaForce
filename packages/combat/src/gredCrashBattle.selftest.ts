/** Actual grounded neutral RED X. Root target geometry and floor probes remain
 * host approximations; no console trajectory parity or new directional/air lane
 * is claimed. Runtime source observations do not replace real input admission. */
import {RomDriverBridge} from './bridge.js';
import {getGRedCrashState} from './gredCrash.js';
import {createBattle,battleStateForSelfcheck} from './battle.js';
import {emptyInput,type StageCollision} from './types.js';
import type {BorgStats} from './stats.js';
import type {Vec3} from './rom/actor.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(x:unknown,s:string):asserts x {if(!x)throw Error(`[gredCrashBattle] ${s}`);}
function floor():StageCollision{
 const vertices:[Vec3,Vec3,Vec3][]=[[v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],[v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
 return {triangles:vertices.map((vertices,index)=>({index,vertices,normal:v(0,1,0),planeD:0,layerIndex:0,marker:0xcccccccc,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(id='pl0615',distance=500){
 const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
 {team:0,ownerPlayer:'p1',borgIds:[id]},{team:1,ownerPlayer:'p2',borgIds:['pl0615']},{team:1,ownerPlayer:'p3',borgIds:['pl0615']}]},stats);
 const input={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};let frame=0;
 const tick=()=>{frame++;battle.step(1/60,input);};for(let i=0;i<100;i++)tick();
 const state=battleStateForSelfcheck(battle),owner=state.borgs.find(b=>b.ownerPlayer==='p1')!,target=state.borgs.find(b=>b.ownerPlayer==='p2')!,alternate=state.borgs.find(b=>b.ownerPlayer==='p3')!;
 owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;target.pos=v(0,10,distance);target.vel=v(0,0,0);alternate.pos=v(400,10,distance);alternate.vel=v(0,0,0);owner.lockTarget=target.uid;
 for(let i=0;i<4;i++)tick();assert(owner.romDriver instanceof RomDriverBridge,'real source driver');const driver=owner.romDriver,actor=driver.actor;
 const animations:{group:number;slot:number;at:number}[]=[];const play=driver.ctx.onPlayAnim;
 driver.ctx.onPlayAnim=(a,group,slot,blend)=>{animations.push({group,slot,at:frame});play?.(a,group,slot,blend);};
 return {battle,state,owner,target,alternate,input,tick,actor,driver,animations,get frame(){return frame;},get crash(){return getGRedCrashState(actor);}};
}
type Fixture=ReturnType<typeof setup>;
function admit(t:Fixture){
 t.input.p1.special=true;t.tick();t.input.p1.special=false;
 assert(t.owner.command?.exact&&t.owner.command.actionIndex===2&&t.owner.command.variantIndex===0,'actual neutral X admits action2/v0');
 assert(t.crash,'grounded RED receives source X state');
}
function until(t:Fixture,test:()=>boolean,label:string,limit=240){
 for(let i=0;i<limit&&!test();i++)t.tick();
 assert(test(),`${label}; phase=${t.actor.fbPhaseSlots[0]}, frame=${t.crash?.stream?.frame}`);
}
function testAuthoredDescentAndLanding(){
 const t=setup('pl0615',3000);admit(t);const s=t.crash!;
 until(t,()=>Boolean(s.stream&&s.stream.frame>=35),'real source reaches late startup');
 assert(Number(t.actor.fbPhaseSlots[0])===1&&s.acceptedContactCount===0,'late startup remains phase1 without hit');
 assert(t.actor.gravityCoeff===0&&t.actor.yVel===4,'source launch retains zero gravity coefficient and vertical launch speed');
 assert(!t.owner.grounded&&t.owner.pos.y>10,'runtime airborne flag follows actual launch');
 assert(!t.animations.some(a=>a.group===0&&a.slot===14),'recovery animation is not played at startup');
 let callbackFrame:number|undefined;
 for(let i=0;i<80&&s.callbackRefreshCount===0;i++){const before=s.stream?.frame;t.tick();if(s.callbackRefreshCount>0)callbackFrame=before;}
 assert(callbackFrame===40&&s.callbackRefreshCount===1,'callback2 is reached at authored frame40, not a guessed X elapsed tick');
 assert(Number(t.actor.fbPhaseSlots[0])===2&&s.acceptedContactCount===0,'authored positive P0 starts descent even on miss');
 until(t,()=>t.owner.vel.y<0,'actual aim and acceleration produce downward velocity');
 assert(!t.owner.grounded,'descending in air is not reported grounded');
 until(t,()=>!t.crash,'actual landing releases source ownership');
 assert(s.exitKind==='landing'&&s.lastGroundProbe!==0&&t.owner.grounded,'accepted floor probe returns immediately through landing path');
 assert(t.actor.stateTimer===1+t.actor.dt,'landing return seeds shared694 to1+dt');
 assert(s.callbackRefreshCount===1,'callback refresh is not repeated');
}
function testTargetRefreshAndRange(){
 const t=setup();admit(t);const s=t.crash!;
 until(t,()=>Boolean(s.stream&&s.stream.frame>=20),'before callback target switch');
 const original=s.targetUid;t.input.p1.switchLock=true;t.tick();t.input.p1.switchLock=false;
 assert(t.owner.lockTarget!==original,'real R input selects another target');const selected=t.owner.lockTarget;
 assert(s.targetUid===original,'captured target remains until source callback');
 until(t,()=>s.callbackRefreshCount===1,'callback recaptures selected target');
 assert(s.targetUid===selected&&s.noTargetLatch541===0,'callback2 uses newly selected in-range target');
 const far=setup();admit(far);const fs=far.crash!;
 until(far,()=>Boolean(fs.stream&&fs.stream.frame>=20),'before out-of-range relocation');
 // Geometry-only change to the selected actor, not an injected targeting callback.
 far.target.pos=v(0,10,10000);far.alternate.pos=v(10000,10,10000);
 until(far,()=>fs.callbackRefreshCount===1,'callback reapplies source range');
 assert(fs.noTargetLatch541!==0&&fs.targetUid===null,'out-of-range callback takes explicit no-target fallback');
 assert(Number.isFinite(far.actor.steerYaw)&&Number.isFinite(far.actor.activeYaw),'fallback produces finite aim');
}
function noFloorAfterAdmission(t:Fixture){
 // Explicit host no-floor seam, installed only after real grounded X admission.
 // Raise the actor in this fixture to keep unrelated arena kill-height rules out.
 t.owner.pos.y=10000;t.actor.pos.y=10000;
 t.actor.physicsRuntime={clampToGround:(pos,velY)=>({y:pos.y,velY,grounded:false}),
  probeMotion:(_previous,_pos,velY)=>({velY,grounded:false}),isSupported:()=>false};
}
function testHoldAndAirRecovery(){
 const t=setup('pl0615',3000);admit(t);const s=t.crash!;
 until(t,()=>Boolean(s.stream&&s.stream.frame>=5),'actual startup before no-floor seam');noFloorAfterAdmission(t);
 until(t,()=>Boolean(s.stream&&s.stream.waitCount>0),'real source reaches mode8 hold');
 const stream=s.stream!,heldFrame=stream.frame,heldElapsed=stream.elapsed;
 assert(Number(stream.waitCount)===10&&heldFrame===63,'frame62 block advances once then initializes ten-count hold');
 for(let i=1;i<10;i++){t.tick();assert(Number(stream.waitCount)===10-i&&Number(stream.frame)===heldFrame&&Number(stream.elapsed)===heldElapsed,'positive hold countdown freezes animation and elapsed clock');}
 t.tick();assert(Number(stream.waitCount)===0&&Number(stream.frame)===64,'countdown release resumes animation once');
 assert(t.crash===s&&!t.animations.some(a=>a.group===0&&a.slot===14),'old exporter event64 cannot prematurely finish or recover');
 until(t,()=>stream.recovery,'main reaches original end80 and starts recovery');
 assert(t.animations.map(a=>`${a.group}/${a.slot}`).join(',')==='4/0,0/14','recovery follows main, never startup');
 assert(Number(stream.frame)===0&&Number(stream.elapsed)===0&&stream.endFrame===1,'recovery resets clocks using original raw end1');
 for(let i=0;i<15;i++){t.tick();assert(t.crash===s,'no-floor recovery remains owned until elapsed15 wait is checked');}
 t.tick();assert(!t.crash&&s.exitKind==='stream-end'&&s.lastGroundProbe===0,'no accepted floor waits for full recovery then air return');
}
function testRealAcceptedHitDoesNotStartDescent(){
 const t=setup();admit(t);const s=t.crash!;
 // Receiver root relocation is a host geometry fixture, not an injected hit.
 for(let i=0;i<40&&s.acceptedContactCount===0;i++){
  t.target.pos=v(t.owner.pos.x,t.owner.pos.y,t.owner.pos.z+40);t.target.vel=v(0,0,0);t.tick();
 }
 assert(s.acceptedContactCount>0&&t.target.hp<t.target.maxHp,'active source HIT15 actually damages receiver');
 assert(Number(t.actor.fbPhaseSlots[0])===1&&s.callbackRefreshCount===0,'accepted early hit is not the authored phase1 transition');
 // Explicit immunity/survival fixture: same early activation remains deduped.
 while((s.stream?.frame??0)<=16){
  t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';
  t.target.pos=v(t.owner.pos.x,t.owner.pos.y,t.owner.pos.z+40);t.target.vel=v(0,0,0);t.tick();
 }
 assert(s.acceptedContactCount===1&&s.hitRecordIndex===33,'early refresh0 source record admits target exactly once');
 t.target.pos=v(0,10,10000);t.alternate.pos=v(10000,10,10000);
 until(t,()=>s.callbackRefreshCount===1,'hit case still waits for source callback40');
 assert(Number(t.actor.fbPhaseSlots[0])===2,'authored contact40 transitions hit case too');
}
function testLateHitRefresh(){
 const t=setup('pl0615',3000);admit(t);const s=t.crash!;
 until(t,()=>Boolean(s.stream&&s.stream.frame>=5),'startup before refresh fixture');noFloorAfterAdmission(t);
 until(t,()=>Boolean(s.stream&&s.stream.frame>=52),'late HIT window is about to open');
 assert(s.acceptedContactCount===0,'no earlier hit contaminated late identity fixture');
 const contacts:{tick:number;frame:number;frozen:boolean;identity:number}[]=[];let update=0,previous=0;
 while(t.crash===s&&s.stream!.frame<=64&&update<50){
  // Explicit receiver survival/immunity + root geometry fixture permits repeated
  // real resolver contacts without claiming natural immunity-free gameplay.
  t.target.hp=t.target.maxHp;t.target.invincTimer=0;t.target.state='idle';
  t.target.pos=v(t.owner.pos.x,t.owner.pos.y,t.owner.pos.z+40);t.target.vel=v(0,0,0);
  const previousFrame=s.stream!.frame,previousWait=s.stream!.waitCount;t.tick();update++;
  if(s.acceptedContactCount!==previous){assert(s.acceptedContactCount===previous+1,'one accepted contact per update');assert(s.hitRecordIndex===21,'late window binds original HIT record21');contacts.push({tick:update,frame:s.stream!.frame,frozen:previousFrame===s.stream!.frame&&previousWait>0,identity:s.hitActivationSerial});previous=s.acceptedContactCount;}
  if(contacts.length>0&&update===contacts[0]!.tick+1&&Number(t.actor.fbPhaseSlots[0])===2)
   assert(t.actor.faceGate1d10===0,'accepted1d9 is consumed next update to clear aim face gate');
 }
 assert(contacts.length>=3,'late refresh admits repeated real contacts including mode8 hold');
 for(let i=1;i<contacts.length;i++){assert(contacts[i]!.tick-contacts[i-1]!.tick===7,'late attack identity renews every seven source updates');assert(contacts[i]!.identity!==contacts[i-1]!.identity,'each renewal has a fresh activation identity');}
 assert(contacts.every(c=>c.frame>=53&&c.frame<=64),'renewed contacts remain inside authored late window');
 assert(contacts.some(c=>c.frame===63&&c.frozen),'seven-update identity refresh admits a new contact during frozen frame63');
}
function testVerticalHitRejection(){
 const t=setup();admit(t);const s=t.crash!;
 for(let i=0;i<50&&(s.stream?.frame??0)<17;i++){
  // Explicit root geometry control: horizontal overlap, vertical separation1000.
  t.target.pos=v(t.owner.pos.x,t.owner.pos.y+1000,t.owner.pos.z);t.target.vel=v(0,0,0);t.tick();
 }
 assert(s.stream&&s.stream.frame>=17,'negative control observes full early active window');
 assert(s.acceptedContactCount===0&&t.target.hp===t.target.maxHp,'source3D radius rejects vertically distant receiver');
}
function testInterruptionAndIsolation(){
 const t=setup();admit(t);const s=t.crash!;t.owner.hp=0;t.tick();
 assert(!t.crash,'death interrupts admitted source X');for(let i=0;i<60;i++)t.tick();
 assert(s.callbackRefreshCount===0,'interrupted startup cannot later run callback2');
 for(const id of ['pl0629','pl062a']){const n=setup(id);n.input.p1.special=true;n.tick();assert(n.owner.command?.actionIndex===2&&n.crash?.family!=='red',`${id} retains its own family source route rather than RED timing`);}
 const air=setup();air.input.p1.jump=true;air.tick();air.input.p1.jump=false;
 assert(!air.owner.grounded,'real jump establishes exact air-X context');air.input.p1.special=true;air.tick();assert(air.crash&&air.actor.variantIndex===4&&air.actor.fbCue===45,'exact air X receives source variant4/cue45 rather than grounded variant0');
}
export function runGredCrashBattleSelfTest(){testAuthoredDescentAndLanding();testTargetRefreshAndRange();testHoldAndAirRecovery();testRealAcceptedHitDoesNotStartDescent();testLateHitRefresh();testVerticalHitRejection();testInterruptionAndIsolation();console.log('[gredCrashBattle] PASS: authored neutral-X timing, targeting, motion and lifecycle');}
