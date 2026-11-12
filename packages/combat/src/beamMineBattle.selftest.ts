/** Real Time Bomber B and Beam Gunner X admissions. Relocated mines isolate the
 * bounded host sphere/capsule receiver; animated/source HIT geometry is not claimed.
 * Zero-damage, owner identity, and retired-phase controls are labeled injections. */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import type { BorgStats } from './stats.js';
import type { Vec3 } from './rom/actor.js';
import type { BeamSourceState } from './beamProjectile.js';
import type { TimeBomberMineSource } from './timeBomberMineAdapter.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
type Mine = Projectile & { timeBomberSource: TimeBomberMineSource };
type Beam = Projectile & { beamSource: BeamSourceState };
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[beamMineBattle] ${message}`);
}
function floor(): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000,0,-20000),v(20000,0,-20000),v(20000,0,20000)],
    [v(-20000,0,-20000),v(20000,0,20000),v(-20000,0,20000)],
  ];
  return {triangles: vertices.map((points,index)=>({index,layerIndex:0,marker:0xcccccccc,
    vertices:points,normal:v(0,1,0),planeD:0,bounds2d:{minX:-20000,maxX:20000,minZ:-20000,maxZ:20000}}))};
}
function setup(count=1) {
  const battle=createBattle({stageId:'st00',bounds:{x:20000,z:20000},collision:floor(),forces:[
    {team:0,ownerPlayer:'p1',borgIds:['pl0104']},
    {team:1,ownerPlayer:'p2',borgIds:['pl0106']},
    {team:1,ownerPlayer:'p3',borgIds:['pl0615']},
  ]},stats);
  const inputs={p1:emptyInput(),p2:emptyInput(),p3:emptyInput()};
  const tick=()=>battle.step(1/60,inputs);
  const ticks=(n:number)=>{for(let i=0;i<n;i++)tick();};
  ticks(100);
  const state=battleStateForSelfcheck(battle);
  const owner=state.borgs.find(b=>b.ownerPlayer==='p1')!, bomber=state.borgs.find(b=>b.ownerPlayer==='p2')!, target=state.borgs.find(b=>b.ownerPlayer==='p3')!;
  owner.pos=v(0,10,0);owner.vel=v(0,0,0);owner.rotY=0;owner.grounded=true;
  bomber.pos=v(6000,10,-4000);bomber.vel=v(0,0,0);bomber.grounded=true;
  target.pos=v(0,10,10000);target.vel=v(0,0,0);owner.lockTarget=target.uid;ticks(4);
  const mines:Mine[]=[];
  for(let i=0;i<count;i++) {
    bomber.pos.x=6000+i*500;inputs.p2.attack=true;tick();
    const mine=state.projectiles.find(p=>p.ownerUid===bomber.uid && p.timeBomberSource?.kind==='mine' && !mines.includes(p as Mine));
    assert(mine?.timeBomberSource?.kind==='mine','actual B press creates one source mine');mines.push(mine as Mine);
    inputs.p2.attack=false;tick();ticks(4);
  }
  const beforeX=owner.weaponCells![1]!.cur;
  inputs.p1.special=true;tick();ticks(68);
  const beam=state.projectiles.find(p=>p.ownerUid===owner.uid && p.beamSource);
  assert(beam?.beamSource && owner.weaponCells![1]!.cur===beforeX-1,'actual X creates source beam and consumes one X round');
  assert(beam.damageRecord?.hpDamage===3 && beam.damageRecord.flagsA===1,'authored beam record retains HP3 and flagsA1');
  assert(mines.every(p=>p.timeBomberSource.phase==='active' && p.timeBomberSource.durability===1),'natural HP1 mines remain live before beam geometry setup');
  return {battle,state,inputs,owner,bomber,target,mines,beam:beam as Beam,tick,ticks};
}
type Fixture=ReturnType<typeof setup>;
function along(beam:Beam,fraction:number):Vec3 {
  const s=beam.beamSource;
  return v(s.start.x+(s.end.x-s.start.x)*fraction,s.start.y+(s.end.y-s.start.y)*fraction,s.start.z+(s.end.z-s.start.z)*fraction);
}
/** Explicit relocation fixture; retain natural lifetime and receiving HP. */
function put(mine:Mine,pos:Vec3) {
  mine.pos={...pos};mine.timeBomberSource.pos={...pos};mine.timeBomberSource.center={...pos};
  mine.timeBomberSource.motion='bob';mine.timeBomberSource.bobPhase=0;mine.timeBomberSource.floorTarget=pos.y;
}
function explosions(t:Fixture) {return t.state.projectiles.filter(p=>p.ownerUid===t.bomber.uid && p.timeBomberSource?.kind==='explosion');}
function testSweepAllMinesAndOrder() {
  for(const reverse of [false,true]) {
    const t=setup(2),[a,b]=t.mines as [Mine,Mine];t.tick();
    const pulse=t.beam.beamSource.pulses[0]!;assert(pulse.stage==='init','first live pulse is only its init sphere');
    put(a,along(t.beam,.35));put(b,along(t.beam,.75));
    if(reverse)t.state.projectiles.reverse();
    const hits=t.battle.observe().telemetry.hitsByTeam[0]??0;t.tick();
    assert(t.mines.every(p=>p.timeBomberSource.durability<1 && p.timeBomberSource.phase==='active'),`one beam sweep damages every overlapping HP1 mine, reverse=${reverse}`);
    assert(t.mines.every(p=>p.timeBomberSource.receivedAttackUids.includes(pulse.attackUid) && pulse.hitUids.includes(p.uid)),
      'both receiver and pulse track the stable pulse identity, not emitter UID');
    assert(t.mines.every(p=>!p.timeBomberSource.receivedAttackUids.includes(t.beam.uid)),'emitter UID is not an attack identity');
    assert(t.state.projectiles.includes(t.beam) && t.beam.beamSource.phase==='active','mine contact does not consume beam');
    assert(explosions(t).length===0 && t.bomber.weaponCells![0]!.cur===8,'damage frame neither explodes nor refunds');
    assert((t.battle.observe().telemetry.hitsByTeam[0]??0)===hits,'mine-only contacts do not fabricate fighter-hit telemetry');
    t.tick();assert(t.mines.every(p=>p.timeBomberSource.phase==='retiring') && explosions(t).length===2,'next child update creates two mine explosions');
    assert(t.bomber.weaponCells![0]!.cur===8,'retirement still owes both cells');
    t.tick();assert(Number(t.bomber.weaponCells![0]!.cur)===10,'following child update refunds exactly two cells');
    t.tick();assert(t.mines.every(p=>!t.state.projectiles.includes(p)) && t.state.projectiles.includes(t.beam),'mines free while beam continues');
  }
}
function testInitAndPulseIdentity() {
  const t=setup(),mine=t.mines[0]!;
  // Synthetic zero-HP record keeps this real HP1 mine alive across pulse stages.
  // Natural HP3 destruction is covered separately above and below.
  t.beam.damageRecord={...t.beam.damageRecord!,hpDamage:0};put(mine,{...t.beam.pos});t.tick();
  const first=t.beam.beamSource.pulses[0]!;
  assert(first.stage==='init' && first.hitUids.includes(mine.uid) && mine.timeBomberSource.receivedAttackUids.length===1,
    'initial sphere can register a mine at the beam start');
  assert(mine.timeBomberSource.durability===1,'zero-HP negative control registers without killing HP1 mine');
  put(mine,along(t.beam,.5));t.tick();
  assert(String(first.stage)==='sweep' && first.hitUids.filter(uid=>uid===mine.uid).length===1 && mine.timeBomberSource.receivedAttackUids.length===1,
    'same pulse init and sweep share one mine contact identity');
  const second=t.beam.beamSource.pulses.find(p=>p!==first)!;
  assert(second && second.attackUid!==first.attackUid,'fresh pulse receives a distinct identity');
  put(mine,along(t.beam,.3));t.tick();
  assert(Number(mine.timeBomberSource.receivedAttackUids.length)===2 && mine.timeBomberSource.receivedAttackUids.includes(second.attackUid),
    'fresh pulse can independently register the same surviving fixture mine');
  assert(mine.timeBomberSource.durability===1 && explosions(t).length===0,'zero-HP repeated pulses never cause retirement');
  const real=setup(),victim=real.mines[0]!;put(victim,{...real.beam.pos});real.tick();
  assert(victim.timeBomberSource.durability<1 && victim.timeBomberSource.phase==='active','authored HP3 initial sphere kills natural HP1 mine');
}
function testGeometryAndReceiverGates() {
  for(const mode of ['outside-y','same-owner-drift','retired','healing','team-filter'] as const) {
    const t=setup(),mine=t.mines[0]!;t.tick();const point=along(t.beam,.5);
    if(mode==='outside-y')point.y+=500;
    put(mine,point);
    // Explicit metadata/phase controls isolate existing receiver gates.
    if(mode==='same-owner-drift') {t.beam.ownerUid=t.bomber.uid;mine.timeBomberSource.motion='drift';mine.timeBomberSource.speed=5;mine.timeBomberSource.direction=v(0,0,0);}
    if(mode==='retired') {mine.timeBomberSource.phase='released';mine.timeBomberSource.resourceOwed=false;mine.timeBomberSource.reason='bounds';}
    if(mode==='healing')t.beam.damageRecord={...t.beam.damageRecord!,flagsA:t.beam.damageRecord!.flagsA|2};
    if(mode==='team-filter') {t.beam.team=mine.team;t.beam.damageRecord={...t.beam.damageRecord!,flagsA:t.beam.damageRecord!.flagsA|0x80};}
    t.tick();assert(mine.timeBomberSource.durability===1,`${mode}: excluded or nondamaging pulse does not kill mine`);
    if(mode!=='healing')assert(mine.timeBomberSource.receivedAttackUids.length===0,`${mode}: no receiver registration`);
    assert(explosions(t).length===0,`${mode}: no explosion`);
  }
  const armed=setup(),bob=armed.mines[0]!;armed.tick();put(bob,along(armed.beam,.5));
  // Paired metadata-injection control: target bob state enables same-owner contact.
  armed.beam.ownerUid=armed.bomber.uid;armed.tick();
  assert(bob.timeBomberSource.durability<1 && bob.timeBomberSource.receivedAttackUids.length===1,
    'same-owner bob mine accepts pending beam sweep, unlike the drift control');
}
function testPendingPulseAndTail() {
  const t=setup(),mine=t.mines[0]!;t.tick();const pulse=t.beam.beamSource.pulses[0]!;
  put(mine,along(t.beam,.5));
  // Owner-death injection tests the already input-created independent child.
  t.owner.hp=0;t.owner.state='death';t.owner.stateTime=0;t.tick();
  assert(pulse.stage==='sweep' && mine.timeBomberSource.durability<1,'pending pulse completes its mine sweep after beam owner dies');
  assert(!t.beam.beamSource.pulse && t.beam.beamSource.pulses.every(p=>p.attackUid===pulse.attackUid),'dead owner emits no fresh pulse');
  t.tick();assert(explosions(t).length===1 && !t.state.projectiles.includes(t.beam),'orphan pulse cleans up and mine explodes on its next child update');
  const tail=setup(),safe=tail.mines[0]!;put(safe,v(-10000,300,-10000));tail.tick();
  for(let i=0;i<100 && tail.beam.beamSource.phase!=='tail';i++)tail.tick();
  assert(safe.timeBomberSource.phase==='active' && safe.timeBomberSource.durability===1,'off-path mine survives active beam before tail control');
  assert(tail.beam.beamSource.phase==='tail' && !tail.beam.beamSource.pulse,'natural owner timer ends pulse generation');
  tail.tick(); // Any independently pending prior pulse finishes before this control.
  put(safe,along(tail.beam,.1));const life=safe.timeBomberSource.life;
  for(let i=0;i<5;i++){put(safe,along(tail.beam,.1));tail.tick();}
  assert(safe.timeBomberSource.durability===1 && safe.timeBomberSource.receivedAttackUids.length===0 && safe.timeBomberSource.life<life,
    'visual tail produces no new damaging pulses while mine lifecycle continues');
}
export function runBeamMineBattleSelfTest():void {
  testSweepAllMinesAndOrder();testInitAndPulseIdentity();testGeometryAndReceiverGates();testPendingPulseAndTail();
  console.log('Beam Gunner X pulses versus Time Bomber B mines: passed (host geometry fixtures)');
}
