/** Actual B-input Battle integration. Static joint8/joint1 pose and host collision are approximations. */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { STATE } from './constants.js';
import { emptyInput, type StageCollision } from './types.js';
import type { BorgStats } from './stats.js';
import type { Vec3 } from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[timeBomberMineBattle] ${message}`);
}
function floor(wallZ?: number): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
    [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
  ];
  if (wallZ !== undefined) vertices.push([v(-5000, -1000, wallZ), v(5000, -1000, wallZ), v(0, 5000, wallZ)]);
  return { triangles: vertices.map((points, index) => ({ index, layerIndex: 0, marker: 0xcccccccc,
    vertices: points, normal: index === 2 ? v(0, 0, -1) : v(0, 1, 0), planeD: 0,
    bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
  })) };
}
function setup(id = 'pl0106', wallZ?: number, extraTarget = false, replacement = false, targetId = 'pl0615') {
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floor(wallZ), forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: replacement ? [id,'pl0103'] : [id] },
    { team: 1, ownerPlayer: 'p2', borgIds: [targetId] },
    ...(extraTarget ? [{ team: 1, ownerPlayer: 'p3', borgIds: ['pl0615'] }] : []),
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput(), p3: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find(b => b.ownerPlayer === 'p1')!;
  const target = state.borgs.find(b => b.ownerPlayer === 'p2')!;
  const other = state.borgs.find(b => b.ownerPlayer === 'p3');
  assert(owner.romDriver instanceof RomDriverBridge, `${id}: live family bridge`);
  const driver = owner.romDriver;
  owner.pos = v(0, 10, 0); owner.vel = v(0, 0, 0); owner.rotY = 0; owner.grounded = true;
  target.pos = v(0, 10, 4000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  if (other) { other.pos = v(3000, 10, 4000); other.vel = v(0, 0, 0); }
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  let elapsed = 0;
  const cues: number[] = []; battle.onRomCue = cue => cues.push(cue);
  const events: { frame: number; address: number; row: number }[] = [];
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row }); spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted }); return accepted;
  };
  const tick = () => { elapsed++; return battle.step(1 / 60, inputs); };
  const press = () => { inputs.p1.attack = true; return tick(); };
  const release = () => { inputs.p1.attack = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, tick, press, release, get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function shots(t: Fixture) { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }
function mines(t: Fixture) { return shots(t).filter(p => p.timeBomberSource?.kind === 'mine'); }
function mine(t: Fixture) {
  const p = mines(t).at(-1); assert(p?.timeBomberSource?.kind === 'mine', 'actual B press creates dedicated mine');
  return p as typeof p & { timeBomberSource: Extract<NonNullable<typeof p.timeBomberSource>, {kind:'mine'}> };
}
function ticks(t: Fixture, n: number) { for(let i=0;i<n;i++) t.tick(); }
function testEdgesAndInitialization() {
  const t=setup(), x=t.owner.weaponCells![1]!.cur;
  t.press(); const p=mine(t), s=p.timeBomberSource, pos={...p.pos}, life=s.life;
  assert(shots(t).length===1 && Number(t.owner.weaponCells![0]!.cur)===9, 'press allocates one mine/cell0, no generic duplicate');
  assert(s.phase==='active' && s.speed===5 && life>=180 && life<=243, 'spawn frame initializes phase0, without age or drift');
  assert(s.durability===1 && p.damageRecord?.hpDamage===30, 'mine has shootable HP1 and direct contact HP30');
  assert(t.driver.actor.stateTimer===5,'post-action B arms shared694 to4+dt');
  t.tick();
  assert(p.timeBomberSource.life===life-1 && Math.abs(Math.hypot(p.pos.x-pos.x,p.pos.y-pos.y,p.pos.z-pos.z)-4.9)<1e-3,
    'first next-frame child update drifts4.9 and ages once');
  ticks(t,12); assert(mines(t).length===1,'holding B does not repeat');
  t.release(); assert(mines(t).length===1 && shots(t).length===1,'release creates no generic charged shot');
  t.press(); assert(mines(t).length===2 && Number(t.owner.weaponCells![0]!.cur)===8,'fresh eligible raw press creates another mine');
  assert(t.owner.weaponCells![1]!.cur===x && t.owner.weaponCells![2]===t.owner.weaponCells![1], 'B leaves X cells untouched');
  t.release(); t.press(); assert(mines(t).length===2,'early re-press is blocked by shared cooldown');
  ticks(t,10);assert(mines(t).length===2,'blocked press is not buffered for later automatic replay');
}
function testTenLiveAndEmpty() {
  const t=setup(), cell=t.owner.weaponCells![0]!;
  // Position fixtures separate mines so armed bob contact cannot detonate a cluster.
  for(let i=0;i<10;i++) { t.owner.pos.x=i*500; t.press(); assert(mines(t).length===i+1 && Number(cell.cur)===9-i,`real press${i+1} consumes exactly one cell`);t.release();ticks(t,4); }
  assert(mines(t).length===10 && Number(cell.cur)===0,'all ten source mines remain live concurrently');
  t.press(); assert(mines(t).length===10 && t.driver.actor.stateTimer===5,'empty B still arms cooldown without an eleventh mine');
  t.release();ticks(t,40);assert(Number(cell.cur)===0 && mines(t).length===10,'no passive cell0 refill while ten mines remain alive');
  for(let i=0;i<300 && (cell.cur<10 || mines(t).some(p=>p.timeBomberSource?.kind==='mine' && p.timeBomberSource.resourceOwed));i++) {
    t.tick();
    const held=mines(t).filter(p=>p.timeBomberSource?.kind==='mine' && p.timeBomberSource.resourceOwed).length;
    assert(cell.cur+held===10,`cell0 conservation through natural expiry frame${i}: ammo${cell.cur}+held${held}`);
  }
  assert(Number(cell.cur)===10,'normal child retirement returns all ten held resources');
  ticks(t,5); assert(Number(cell.cur)===10,'later free updates never double-refund');
}
function testParallelX() {
  for(const mode of ['ground','air','run'] as const) {
    const t=setup();
    if(mode==='air'){t.inputs.p1.jump=true;t.tick();t.inputs.p1.jump=false;ticks(t,3);assert(!t.owner.grounded,'real jump fixture');}
    if(mode==='run'){t.inputs.p1.moveZ=1;ticks(t,12);assert(t.owner.state==='move','real established running fixture');}
    t.inputs.p1.special=true;t.press();
    assert(mines(t).length===1 && Number(t.owner.weaponCells![0]!.cur)===9,`${mode} simultaneous B+X creates one mine`);
    assert(t.owner.command?.exact && t.owner.command.type===2,`${mode} simultaneous B does not replace X command`);
    const count=mines(t).length;t.release();t.press();
    assert((t.driver.actor.controlWord&3)!==0 && t.driver.actor.stateTimer>0 && mines(t).length===count,
      `${mode} early B re-press while X owns actor is blocked by positive shared694`);
    ticks(t,30);
    assert(t.events.filter(e=>e.address===0x800fe668).length===1,`${mode} X launches one source primary`);
    assert(shots(t).every(p=>p.timeBomberSource),`${mode} neither B nor X creates generic duplicate`);
    t.inputs.p1.special=false;t.release();ticks(t,80);t.press();
    assert(mines(t).length===count+1,`${mode} fresh B after X recovery is admitted`);
    const during=setup();
    if(mode==='air'){during.inputs.p1.jump=true;during.tick();during.inputs.p1.jump=false;ticks(during,3);}
    if(mode==='run'){during.inputs.p1.moveZ=1;ticks(during,12);}
    during.inputs.p1.special=true;during.tick();during.tick();during.press();
    assert(mines(during).length===1 && (during.driver.actor.controlWord&3)!==0,`${mode} B while X owns actor creates mine without interrupting X: mines=${mines(during).length}, timer=${during.driver.actor.stateTimer}, state=${during.owner.state}, flag=${during.owner.cooldowns['romSpecialActive']}, low=${during.driver.actor.controlWord&3}, input=${JSON.stringify(during.owner.timeBomberBInput)}`);
    ticks(during,30);assert(during.events.filter(e=>e.address===0x800fe668).length===1,`${mode} B during windup preserves pending X launch`);
  }
}
/** Lifecycle injections below establish edge fixtures, never substitute for B input admission. */
function testRetirementAndIdentity() {
  const t=setup();t.press();const p=mine(t),cell=t.owner.weaponCells![0]!;
  p.timeBomberSource.life=1;t.tick();
  assert(String(p.timeBomberSource.phase)==='retiring' && Number(cell.cur)===9,'expiry enters retirement without same-update refund');
  assert(shots(t).filter(q=>q.timeBomberSource?.kind==='explosion').length===1,'expiry creates explosion19');
  t.tick();assert(String(p.timeBomberSource.phase)==='released' && Number(cell.cur)===10,'next child update refunds');
  t.tick();assert(!shots(t).includes(p) && Number(cell.cur)===10,'following update frees without duplicate refund');
  const dead=setup();dead.press();const orphan=mine(dead);dead.owner.hp=0;dead.owner.state='death';dead.owner.stateTime=0;dead.tick();
  assert(orphan.timeBomberSource.phase==='released' && dead.owner.weaponCells![0]!.cur===10,'owner invalidation refunds on same child update');
  assert(!shots(dead).some(q=>q.timeBomberSource?.kind==='explosion'),'owner invalidation does not explode');
  const deployed=setup('pl0106',undefined,false,true);deployed.press();const lost=mine(deployed);deployed.inputs.p1.attack=false;deployed.owner.hp=0;deployed.owner.state='death';deployed.owner.stateTime=STATE.DEATH_DURATION-1;deployed.tick();
  ticks(deployed,STATE.DEATH_DURATION+100);
  const replacement=deployed.state.borgs.find(b=>b.team===0 && b.uid!==deployed.owner.uid);
  assert(replacement && lost.timeBomberSource.resourceOwed===false && !deployed.state.projectiles.includes(lost),'real deployment replacement uses new UID and old mine is fully retired');
  const replacementAmmo=replacement.weaponCells![0]!.cur;ticks(deployed,5);
  assert(replacement.weaponCells![0]!.cur===replacementAmmo,'old mine cannot grant delayed refund to replacement UID');
  const changed=setup();changed.press();const old=mine(changed),oldCell=changed.owner.weaponCells![0]!;
  changed.inputs.p1.attack=false;changed.owner.borgId='pl0103';changed.owner.ammo=4;changed.owner.weaponCells=[{...oldCell,cur:4},changed.owner.weaponCells![1]!,changed.owner.weaponCells![2]!];changed.tick();
  assert(old.timeBomberSource.phase==='released' && changed.owner.weaponCells![0]!.cur===5,'same owner object form change returns source resource to its current cell0');
}
function testObservationPause() {
  const t=setup();t.press();const p=mine(t),before=JSON.stringify(p.timeBomberSource),ammo=t.owner.weaponCells![0]!.cur,timer=t.driver.actor.stateTimer;
  for(let i=0;i<100;i++)t.battle.observe();
  assert(JSON.stringify(p.timeBomberSource)===before && Number(t.owner.weaponCells![0]!.cur)===ammo && t.driver.actor.stateTimer===timer,
    'host pause by withholding steps does not advance child, resource or shared cooldown');
  // Battle.step is explicitly fixed-step: dt=0 is not a supported pause API.
  t.tick();assert(JSON.stringify(p.timeBomberSource)!==before,'resuming fixed steps resumes mine lifecycle');
}
function testContactAndBounds() {
  const t=setup();t.press();const p=mine(t);const hp=t.target.hp;
  // Fixture positioning only; actual Battle overlap resolves the hit.
  t.target.pos={...p.pos};t.target.vel=v(0,0,0);t.tick();
  // Source damage curves may scale authored HP30; prove the direct record and contact separately.
  assert(p.damageRecord?.hpDamage===30 && t.target.hp<hp && p.timeBomberSource.contactPending,`host natural overlap applies distinct mine direct HP30: hp=${hp}->${t.target.hp}, pending=${p.timeBomberSource.contactPending}, hitUids=${JSON.stringify(p.timeBomberSource.hitUids)}, pos=${JSON.stringify(t.target.pos)}, mine=${JSON.stringify(p.pos)}`);
  assert(!shots(t).some(q=>q.timeBomberSource?.kind==='explosion'),'direct contact does not update explosion in same child pass');
  t.tick();assert(shots(t).some(q=>q.timeBomberSource?.kind==='explosion'),'contact creates separate explosion19 on next child update');
  assert(Number(t.owner.weaponCells![0]!.cur)===9,'contact retirement keeps resource until following child update');
  t.tick();assert(Number(t.owner.weaponCells![0]!.cur)===10,'contact retirement refunds once');
  // Bounds injection is a lifecycle adjunct, not proof of source terrain geometry.
  const outside=setup();outside.press();const q=mine(outside);q.pos.x=q.timeBomberSource.pos.x=21000;outside.tick();
  assert(q.timeBomberSource.phase==='retiring' && q.timeBomberSource.reason==='bounds','bounds retires without explosion');
  assert(!shots(outside).some(r=>r.timeBomberSource?.kind==='explosion'),'bounds does not explode');
  outside.tick();assert(outside.owner.weaponCells![0]!.cur===10,'bounds refund occurs next child update');
}
function testEnemyShotDamage() {
  const t=setup();t.press();const p=mine(t);
  t.inputs.p2.attack=true;t.tick();t.inputs.p2.attack=false;t.tick();
  for(let i=0;i<30 && !t.state.projectiles.some(q=>q.ownerUid===t.target.uid);i++)t.tick();
  const enemy=t.state.projectiles.find(q=>q.ownerUid===t.target.uid);assert(enemy,'opponent actual B emits a projectile');
  assert(enemy.gredRangedSource, 'opponent real B uses dedicated source flight');
  // Geometry injection isolates receiving damage, not original aim/bone parity.
  // The source flight owns its trajectory; generic pos/vel writes are overwritten.
  const f=enemy.gredRangedSource.flight;
  const pos=v(Math.fround(f.pos.x+f.velocity.x),Math.fround(f.pos.y+f.velocity.y),Math.fround(f.pos.z+f.velocity.z));
  Object.assign(p.timeBomberSource,{pos:{...pos},center:{...pos},direction:v(0,0,0)});
  p.pos={...pos};t.tick();
  assert(p.timeBomberSource.durability<1,'enemy attack damages shootable HP1 mine');
  t.tick();assert(String(p.timeBomberSource.phase)==='retiring' && p.timeBomberSource.reason==='durability','next child update retires shot mine');
  assert(shots(t).some(q=>q.timeBomberSource?.kind==='explosion'),'destroyed mine emits explosion19');
  t.tick();assert(Number(t.owner.weaponCells![0]!.cur)===10,'destroyed mine returns its cell once');
}
/** Explicit allocator-failure seam; raw B admission still comes from Battle input. */
function testAllocationFailure() {
  const t=setup();let attempts=0;const original=t.driver.ctx.onTimeBomberMine;
  t.driver.ctx.onTimeBomberMine=()=>{attempts++;return false;};t.press();
  assert(attempts===1 && shots(t).length===0 && Number(t.owner.weaponCells![0]!.cur)===10,'failed child allocation immediately returns consumed cell once');
  assert(t.driver.actor.stateTimer===5,'failed allocation still arms shared694');
  ticks(t,10);assert(attempts===1 && Number(t.owner.weaponCells![0]!.cur)===10,'held B never retries failed allocation');
  if(original)t.driver.ctx.onTimeBomberMine=original;else delete t.driver.ctx.onTimeBomberMine;t.release();t.press();assert(mines(t).length===1 && Number(t.owner.weaponCells![0]!.cur)===9,'fresh edge after failure can allocate normally');
}
function testWallAndSharedReset() {
  const wall=setup('pl0106',60);wall.press();const p=mine(wall);
  for(let i=0;i<60 && p.timeBomberSource.phase==='active';i++)wall.tick();
  assert(p.timeBomberSource.phase==='retiring' && p.timeBomberSource.reason==='wall','input-created mine naturally reaches host wall sweep');
  assert(shots(wall).some(q=>q.timeBomberSource?.kind==='explosion'),'wall contact creates explosion19');
  assert(wall.owner.weaponCells![0]!.cur===9,'wall retirement defers resource refund');
  wall.tick();assert(Number(wall.owner.weaponCells![0]!.cur)===10,'wall next child update refunds');
  const reset=setup();reset.press();reset.inputs.p1.special=true;reset.release();
  assert(reset.driver.actor.stateTimer===0 && (reset.driver.actor.controlWord&3)!==0,'later X admission resets existing B shared694');
  reset.press();assert(mines(reset).length===2,'fresh B during X is admitted after source reset');
}
/** Same-pass collision registration adjuncts. B creates every mine; overlap/bob are injected geometry. */
function testCollisionOrderIndependence() {
  for(const reverse of [false,true]) {
    const t=setup('pl0106',undefined,false,false,'pl0106');t.press();t.inputs.p2.attack=true;t.tick();
    const a=mine(t),b=t.state.projectiles.find(q=>q.ownerUid===t.target.uid && q.timeBomberSource?.kind==='mine');
    assert(b?.timeBomberSource?.kind==='mine','opponent actual B creates second mine');
    for(const q of [a,b]) {
      assert(q.timeBomberSource?.kind==='mine','mine fixture type');
      q.pos=v(1000,200,1000);q.timeBomberSource.pos={...q.pos};q.timeBomberSource.center={...q.pos};
      q.timeBomberSource.motion='bob';q.timeBomberSource.bobPhase=0;q.timeBomberSource.floorTarget=150;
    }
    if(reverse)t.state.projectiles.reverse();t.tick();
    assert(a.timeBomberSource.durability<1 && b.timeBomberSource.durability<1,
      `both mine receiver registrations survive same-pass damage, reverse=${reverse}`);
    assert(a.timeBomberSource.contactPending && b.timeBomberSource.contactPending &&
      a.timeBomberSource.phase==='active' && b.timeBomberSource.phase==='active',
      `both attacks connect before next child update, reverse=${reverse}`);
    assert(a.timeBomberSource.receivedAttackUids.filter(uid=>uid===b.uid).length===1 &&
      b.timeBomberSource.receivedAttackUids.filter(uid=>uid===a.uid).length===1,'mutual mine pair recorded exactly once each');
    assert(!t.state.projectiles.some(q=>q.timeBomberSource?.kind==='explosion'),'same-pass mutual contact cannot explode early');
    t.tick();
    assert(String(a.timeBomberSource.phase)==='retiring' && String(b.timeBomberSource.phase)==='retiring' &&
      t.state.projectiles.filter(q=>q.timeBomberSource?.kind==='explosion').length===2,'both mutual contacts retire and explode on next child update');
  }
  const t=setup('pl0106',undefined,true);t.press();const p=mine(t);
  t.inputs.p2.attack=true;t.tick();t.inputs.p2.attack=false;t.tick();
  for(let i=0;i<30 && !t.state.projectiles.some(q=>q.ownerUid===t.target.uid);i++)t.tick();
  const enemy=t.state.projectiles.find(q=>q.ownerUid===t.target.uid);assert(enemy && t.other,'real enemy projectile and third actor fixture');
  assert(enemy.gredRangedSource,'real enemy source flight owns collision-order trajectory');
  // Place the real mine and third actor on the predicted head, not generic projectile fields.
  const f=enemy.gredRangedSource.flight;
  const pos=v(Math.fround(f.pos.x+f.velocity.x),Math.fround(f.pos.y+f.velocity.y),Math.fround(f.pos.z+f.velocity.z));
  Object.assign(p.timeBomberSource,{pos:{...pos},center:{...pos},direction:v(0,0,0)});
  p.pos={...pos};t.other.pos={...pos};t.other.vel=v(0,0,0);
  t.state.projectiles.sort((a,b)=>a===enemy?-1:b===enemy?1:0);t.tick();
  assert(p.timeBomberSource.durability<1 && p.timeBomberSource.receivedAttackUids.includes(enemy.uid),'earlier projectile kills mine durability in current collision pass');
  assert(p.timeBomberSource.hitUids.includes(t.other.uid) && p.timeBomberSource.contactPending && p.timeBomberSource.phase==='active',
    'already registered mine attack still connects later in the same pass after projectile damage');
  t.tick();assert(String(p.timeBomberSource.phase)==='retiring','shot-and-contact mine retires only on next child update');
}
export function runTimeBomberMineBattleSelfTest(): void {
 testEdgesAndInitialization();testTenLiveAndEmpty();testParallelX();testRetirementAndIdentity();testObservationPause();testContactAndBounds();testEnemyShotDamage();testAllocationFailure();testWallAndSharedReset();testCollisionOrderIndependence();
 console.log('Time Bomber B mine actual-input Battle integration: passed');
}
