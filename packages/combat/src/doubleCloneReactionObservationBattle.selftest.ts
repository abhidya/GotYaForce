/** Observation transport only, never source-reaction parity. Real input and host
 * contact coverage follows Ninja/Nurse Battle fixtures. Positions, HP, immunity
 * and death timers are explicit host fixture adjuncts, not source flag/gauge
 * writers. The overflow stress case is explicitly an applyHit seam adjunct. */
import {battleStateForSelfcheck, createBattle} from './battle.js';
import {applyHit} from './combat.js';
import {STATE} from './constants.js';
import {RomDriverBridge} from './bridge.js';
import {getNinjaXState} from './ninjaX.js';
import {familyDamageRecordForBorg} from './familyDamageData.js';
import {buildProfile, type BorgStats} from './stats.js';
import {emptyInput, type StageCollision} from './types.js';
import type {Vec3} from './rom/actor.js';
import {beginDoubleCloneReactionObservation, finalizeDoubleCloneReactionObservation,
  readDoubleCloneReactionObservation as read, DOUBLE_CLONE_OBSERVATION_CONTACT_LIMIT,
  type DoubleCloneReactionObservation} from './doubleCloneReactionObservation.js';
import data from '../../assets/data/borgs.json' with {type:'json'};
const stats=(data as {borgs:BorgStats[]}).borgs;
const v=(x:number,y:number,z:number):Vec3=>({x,y,z});
function assert(value:unknown,message:string):asserts value {
  if(!value)throw new Error(`[doubleCloneReactionObservationBattle] ${message}`);
}
function floor():StageCollision {
  const triangles:[Vec3,Vec3,Vec3][]=[
    [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
    [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)]];
  return {triangles:triangles.map((vertices,index)=>({index,vertices,normal:v(0,1,0),
    planeD:0,layerIndex:0,marker:0xcccccccc,
    bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(nurses=false,replacement=false) {
  const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},...(nurses?{}:{collision:floor()}),forces:[
    {team:0,ownerPlayer:'p1',borgIds:[nurses?'pl0900':'pl0000']},
    {team:nurses?0:1,ownerPlayer:'p2',borgIds:replacement?['pl0003','pl0003']:['pl0003']},
    ...(nurses?[
      {team:0,ownerPlayer:'p3',borgIds:['pl0900']},
      {team:1,ownerPlayer:'p4',borgIds:['pl0615']},
    ]:[]),
  ]},stats);
  const inputs={p1:emptyInput(),p2:emptyInput(),p3:emptyInput(),p4:emptyInput()};
  const tick=()=>battle.step(1/60,inputs);
  for(let i=0;i<100;i++)tick();
  const state=battleStateForSelfcheck(battle);
  const attacker=state.borgs.find(b=>b.ownerPlayer==='p1')!;
  const owner=state.borgs.find(b=>b.ownerPlayer==='p2')!;
  const other=state.borgs.find(b=>b.ownerPlayer==='p3');
  attacker.pos=v(nurses?-40:0,nurses?0:10,0);attacker.vel=v(0,0,0);attacker.rotY=0;attacker.grounded=true;
  owner.pos=v(0,nurses?0:10,nurses?50:1500);owner.vel=v(0,0,0);attacker.lockTarget=owner.uid;
  if(other){other.pos=v(40,0,0);other.vel=v(0,0,0);other.rotY=0;other.grounded=true;}
  const enemy=state.borgs.find(b=>b.ownerPlayer==='p4');
  if(enemy)enemy.pos=v(4000,10,4000);
  for(let i=0;i<4;i++)tick();
  return {battle,state,attacker,owner,other,inputs,tick};
}
function unknown(frame:DoubleCloneReactionObservation):void {
  assert(frame.complete&&frame.sourceObservation==='unknown'&&frame.unknownReasons.length>=4,
    'closed host evidence remains explicitly source-unknown');
  assert(!('reaction' in frame)&&!('flags6fd' in frame)&&!('flags1da' in frame),
    'host transport must not manufacture source reaction or source flag bytes');
}
function testNaturalProjectileAndRejection():void {
  for(const invincible of [false,true]) {
    const t=setup(), hp=t.owner.hp, hits=t.battle.observe().telemetry.hitsByTeam[0]??0;
    if(invincible)t.owner.invincTimer=1000;
    t.inputs.p1.special=true;
    let observed=0, confirmed=0;
    const ids=new Set<string>();
    let saved:DoubleCloneReactionObservation|null=null;
    for(let i=0;i<180;i++) {
      t.tick();
      const frame=read(t.owner);assert(frame,'live Double receives a Battle frame');unknown(frame);
      observed+=frame.acceptedContactCount;
      for(const contact of frame.contacts){
        assert(!ids.has(contact.eventId),'one accepted contact cannot replay across frames');ids.add(contact.eventId);
        assert(contact.attackerUid===t.attacker.uid,'contact retains actual attacker identity');
        assert(contact.hostBefore.hp>=t.owner.hp,'snapshot precedes host damage');
      }
      if(frame.contacts.length)saved=frame;
      confirmed=t.battle.observe().telemetry.hitsByTeam[0]??0;
      const before=JSON.stringify(frame), snapshot=t.battle.observe();
      for(let j=0;j<3;j++)assert(t.battle.observe()===snapshot&&read(t.owner)===frame,
        'read/observe neither steps simulation nor replays contacts');
      assert(JSON.stringify(frame)===before,'observer reads preserve detached snapshot');
    }
    assert(invincible?observed===0&&t.owner.hp===hp:observed>0&&t.owner.hp<hp,
      'actual input projectile accepts damage, while invincible receiver rejects all contacts');
    assert(observed===confirmed-hits,'every accepted real contact transported exactly once with telemetry');
    assert(read(t.attacker)===null,'Normal Ninja attacker cannot acquire Double-only observation');
    if(saved)assert(saved.contacts.length>0&&saved.frameId<read(t.owner)!.frameId,
      'historical contact frame survives successor empty frames without accumulation');
    assert(t.owner.romDriver instanceof RomDriverBridge,'Double victim has live bridge');
    assert(!getNinjaXState(t.owner.romDriver.actor)?.doubleClone?.arm7c8,
      'incoming observations never activate or arm a clone');
    assert(t.state.projectiles.every(p=>p.ninjaSource?.kind!=='primary'||p.ninjaSource.flight.row!==2),
      'ordinary real input does not create clone row2');
  }
}
function testRealHealingContact():void {
  const t=setup(true);assert(t.other,'Nurse control fixture');
  t.other.pos=v(4000,0,4000);t.owner.maxHp=10000;t.owner.hp=1000;
  t.inputs.p1.allyLock=true;t.tick();
  for(let i=0;i<4;i++)t.tick();
  t.inputs.p1.special=true;
  let accepted=0;
  for(let i=0;i<180;i++){
    // Explicit host geometry fixture, as in close Nurse Battle tests.
    t.attacker.pos=v(0,0,0);t.owner.pos=v(0,0,50);
    t.attacker.vel=v(0,0,0);t.owner.vel=v(0,0,0);
    t.tick();const frame=read(t.owner)!;unknown(frame);
    accepted+=frame.acceptedContactCount;
    for(const contact of frame.contacts)assert((contact.record.flagsA&2)!==0&&
      contact.attackerUid===t.attacker.uid,'real Nurse HIT transports signed-HP healing contact');
  }
  assert(accepted===1&&t.owner.hp===1200,
    'one actual-input Nurse heal is accepted once despite negative damage, without suppressing restoration');
}
function testIsolationAndReplacement():void {
  const a=setup(false,true),b=setup();
  assert(a.owner.uid===b.owner.uid,'independent Battles intentionally reuse deployment UID');
  const bFrame=read(b.owner)!;
  a.inputs.p1.special=true;
  let contactFrame:DoubleCloneReactionObservation|null=null;
  for(let i=0;i<150&&!contactFrame;i++){a.tick();const frame=read(a.owner)!;if(frame.contacts.length)contactFrame=frame;}
  assert(contactFrame&&read(b.owner)===bFrame&&bFrame.contacts.length===0,
    'same UID in independent Battle cannot inherit accepted contacts');
  a.owner.hp=0;a.owner.state='death';a.owner.stateTime=STATE.DEATH_DURATION-1;a.tick();
  const oldFrame=read(a.owner);assert(oldFrame?.complete,'old deployment finalizes before replacement');
  let replacement=a.state.borgs.find(x=>x.ownerPlayer==='p2'&&x!==a.owner);
  for(let i=0;i<STATE.DEATH_DURATION+STATE.SPAWN_DURATION+30&&!replacement;i++){
    a.tick();replacement=a.state.borgs.find(x=>x.ownerPlayer==='p2'&&x!==a.owner);
  }
  assert(replacement&&replacement.uid!==a.owner.uid,'ordinary death lifecycle deploys new owner identity');
  a.tick();
  assert(read(a.owner)===oldFrame&&read(replacement)?.ownerUid===replacement.uid&&
    read(replacement)!.contacts.length===0,'replacement gets fresh observation and cannot mutate dead deployment');
  assert(contactFrame.contacts.length>0,'retained pre-death accepted evidence stays intact');
}
/** Explicit applyHit stress adjunct, not a claim that live Battle produces 67
 * same-frame heals. Uses the real Nurse record unchanged; no source seed fields. */
function testBoundedAcceptedHitStress():void {
  const t=setup(true),control=setup(true);
  const record=familyDamageRecordForBorg('pl0900',3)!;
  const profile=buildProfile(stats.find(b=>b.id==='pl0003')!);
  for(const fixture of [t,control]){fixture.owner.maxHp=100000;fixture.owner.hp=100;}
  const frameId=t.state.frame+10;
  beginDoubleCloneReactionObservation(t.owner,frameId);
  for(let i=0;i<DOUBLE_CLONE_OBSERVATION_CONTACT_LIMIT+3;i++){
    for(const fixture of [t,control])applyHit(fixture.owner,profile,record.hpDamage,0,
      v(0,0,1),fixture.attacker.pos,false,record);
  }
  finalizeDoubleCloneReactionObservation(t.owner,frameId);
  const frame=read(t.owner)!;unknown(frame);
  assert(frame.contacts.length===64&&frame.acceptedContactCount===67&&frame.droppedContactCount===3&&
    frame.unknownReasons.includes('contact-observation-overflow'),'bounded overflow is counted and explicitly unknown');
  assert(frame.contacts[0]!.ordinal===1&&frame.contacts[63]!.ordinal===64,
    'bounded first 64 contacts retain unique arrival ordinals');
  assert(new Set(frame.contacts.map(c=>c.eventId)).size===64,
    'distinct same-owner same-frame accepted contacts are never victim-UID deduplicated');
  const gameplay=(fixture:typeof t)=>JSON.stringify({hp:fixture.owner.hp,state:fixture.owner.state,
    down:fixture.owner.downGauge,balance:fixture.owner.balanceGauge,velocity:fixture.owner.vel,
    invinc:fixture.owner.invincTimer,combo:fixture.owner.comboAccum,freeze:fixture.owner.freezeFrames});
  assert(gameplay(t)===gameplay(control),'open collector versus closed collector cannot alter hit gameplay');
  assert(read(control.owner)!.contacts.length===0,'closed frames reject out-of-Battle helper writes');
  applyHit(t.owner,profile,record.hpDamage,0,v(0,0,1),t.attacker.pos,false,record);
  assert(read(t.owner)===frame,'closed frame cannot replay subsequent helper contact');
}
export function runDoubleCloneReactionObservationBattleSelfTest():void {
  testNaturalProjectileAndRejection();testRealHealingContact();testIsolationAndReplacement();testBoundedAcceptedHitStress();
  console.log('[doubleCloneReactionObservationBattle] PASS: real input/contact transport, rejection, identity isolation and bounded unknown observation');
}
