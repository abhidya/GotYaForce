/** Actual-input tests for the bounded pl0106 airborne neutral X lane.
 * Real jump/special edges drive admission. Positions only establish fixtures.
 * Host collision, static muzzle pose, and air physics are not full source parity. */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { emptyInput, type StageCollision } from './types.js';
import type { BorgStats } from './stats.js';
import { timeBomberAirAction, type TimeBomberAction } from './families/time-bomber.js';
import type { RomHelperScratch } from './rom/helpers.js';
import type { Vec3 } from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[timeBomberAirBattle] ${message}`);
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
function setup(id = 'pl0106', wallZ?: number, extraTarget = false) {
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floor(wallZ), forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: [id] },
    { team: 1, ownerPlayer: 'p2', borgIds: ['pl0615'] },
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
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, tick, press, release, get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function shots(t: Fixture) { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }

function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false;
  for (let i = 0; i < 3; i++) t.tick();
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'real jump establishes airborne admission');
}
function stream(t: Fixture): TimeBomberAction | undefined {
  return (t.driver.actor as typeof t.driver.actor & { timeBomberAction?: TimeBomberAction }).timeBomberAction;
}
function admit(t: Fixture): void {
  t.press();
  assert(t.owner.command?.exact && t.owner.command.type === 2 && t.owner.command.actionIndex === 0 &&
    t.owner.command.variantIndex === 3 && t.owner.command.recordAddress === '0x80336218',
    'actual airborne neutral X selects exact action0/variant3');
  assert(t.driver.actor.fbCue === 45 && (t.driver.actor.controlWord & 3) === 1 && stream(t)?.mask === 1,
    'air command retains cue45 mode1 and source part0-only mask');
  assert(stream(t)?.stage === 'windup', 'actual jump X enters dedicated source action, not generic special');
  assert(t.events.length === 0 && shots(t).length === 0 && t.allocations.length === 0,
    'air admission has no early allocation or generic projectile');
}

function launch(t: Fixture) {
  const height = t.owner.pos.y;
  admit(t);
  for (let i = 0; i < 2; i++) {
    t.tick();
    assert(t.events.length === 0 && shots(t).length === 0, 'air blend gate blocks early source release');
  }
  t.tick();
  assert(t.events.length === 1 && t.events[0]!.address === 0x800fe668 && t.events[0]!.row === 2,
    'air blend completion emits exactly one original row2 child');
  const bomb = shots(t)[0];
  assert(shots(t).length === 1 && bomb?.timeBomberSource?.kind === 'primary',
    'air launch publishes dedicated source primary without generic duplicate');
  assert(!t.owner.grounded && t.owner.pos.y > height, 'jump ascent continues through airborne windup and release');
  return bomb;
}
function finish(t: Fixture): void {
  for (let i = 0; i < 180; i++) t.tick();
  assert(t.owner.grounded && !t.owner.cooldowns['romSpecialActive'] && t.owner.state !== 'special',
    'natural landing and source recovery release special ownership');
}
function testAirAdmissionAndFlight(): void {
  const t = setup(); jump(t);
  const cell = t.owner.weaponCells![1]!, before = cell.cur, bBefore = t.owner.weaponCells![0]!.cur;
  const start = t.frame;
  const bomb = launch(t);
  assert(t.owner.weaponCells![2] === cell && cell.cur === before - 1 && cell.timer === 300,
    'air launch consumes aliased source cell2 once and starts debt300');
  assert(t.allocations.length === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 && t.allocations[0]!.accepted,
    'air action allocates exactly one source round');
  assert(t.owner.weaponCells![0]!.cur === bBefore && bomb.romShotKind === 17 && bomb.life === 300,
    'air action preserves B and constructs same source HIT17 lifetime300 primary');
  const firstHeight = t.owner.pos.y;
  let fell = false, previous = firstHeight;
  for (let i = 0; i < 100; i++) {
    t.tick(); fell ||= t.owner.pos.y < previous; previous = t.owner.pos.y;
    const age = t.frame - start;
    if (age === 25) assert(stream(t)?.stage === 'wait' && stream(t)?.wait === 8,
      'air stream reaches original END20 then starts realtime wait8');
    if (age === 33) assert(stream(t)?.stage === 'tail' && stream(t)?.frame === 1,
      'air wait8 starts original tail with same-frame update');
    if (age === 41) assert(stream(t)?.stage === 'tail' && stream(t)?.frame === 9,
      'air tail reaches original END9 before terminal test');
    if (age === 42) assert(!t.owner.cooldowns['romSpecialActive'],
      'air stream releases ownership on original END20/wait8/END9 boundary');
  }
  assert(fell && t.owner.grounded, 'source action does not freeze the real jump arc');
  finish(t);
  assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1, 'held X never repeats across source recovery or landing');
  t.release();
  for (let i = 0; i < 400 && (cell.cur < 1 || (t.owner.cooldowns['special'] ?? 0) > 0); i++) t.tick();
  jump(t); t.press();
  for (let i = 0; i < 15 && t.events.length < 2; i++) t.tick();
  assert(Number(t.events.length) === 2 && Number(t.allocations.length) === 2,
    'release and repress after recovery admits another airborne source shot');
}
function testTargetlessAndCapturedAim(): void {
  const absent = setup(); absent.target.hp = 0; absent.target.state = 'death'; absent.target.stateTime = 0;
  jump(absent); const bomb = launch(absent);
  assert(absent.owner.timeBomberSavedAim?.targetUid === null && bomb.aimedTargetUid === null &&
    bomb.timeBomberSource?.kind === 'primary' && bomb.timeBomberSource.targetUid === null,
    'targetless actual jump X admits an unguided dedicated primary');
  assert(Math.abs(bomb.vel.x) < 1e-6 && Math.abs(bomb.vel.y) < 1e-6 && Math.abs(bomb.vel.z - 20) < 1e-6,
    'targetless air constructor uses forward heading');
  const moving = setup('pl0106', undefined, true); jump(moving); admit(moving);
  const saved = { ...moving.owner.timeBomberSavedAim!.pos };
  moving.inputs.p2.moveX = 1;
  moving.inputs.p1.switchLock = true; moving.tick(); moving.inputs.p1.switchLock = false;
  for (let i = 0; i < 30 && moving.events.length === 0; i++) moving.tick();
  const shot = shots(moving)[0];
  assert(moving.target.pos.x !== saved.x && shot?.timeBomberSource?.kind === 'primary',
    'real target movement occurs during source windup');
  assert(moving.owner.targetLockState?.activeTargetUid === moving.other!.uid &&
    moving.owner.timeBomberSavedAim!.targetUid === moving.target.uid && shot.aimedTargetUid === moving.target.uid,
    'real R switch cannot replace admitted moving-target identity');
  const refreshed = moving.owner.timeBomberSavedAim!.pos;
  assert(refreshed.x === moving.target.sourceFramePose!.pos.x && refreshed.x !== saved.x,
    'captured identity uses refreshed global pre-movement target point');
  const delta = v(refreshed.x-shot.pos.x,refreshed.y-shot.pos.y,refreshed.z-shot.pos.z);
  const length = Math.hypot(delta.x,delta.y,delta.z);
  for (const axis of ['x','y','z'] as const)
    assert(Math.abs(shot.vel[axis]-delta[axis]/length*20)<1e-6, 'air launch velocity uses captured aim point');
}
function testEmptyAndLateLanding(): void {
  const empty = setup(); const cell = empty.owner.weaponCells![1]!; cell.cur = 0; cell.timer = cell.refillParam * cell.max;
  jump(empty); empty.press(); for (let i=0;i<60;i++) empty.tick();
  assert(empty.events.length === 0 && shots(empty).length === 0, 'empty airborne X cannot manufacture source or generic projectile');
  const late = setup(); jump(late);
  for (let i=0;i<120 && !(late.owner.vel.y < 0 && late.owner.pos.y < 45);i++) late.tick();
  assert(!late.owner.grounded && late.owner.vel.y < 0 && late.owner.pos.y < 45,
    'real jump supplies a descending fixture just before landing');
  late.press();
  for (let i=0;i<60;i++) late.tick();
  assert(late.owner.grounded && !late.owner.cooldowns['romSpecialActive'] && late.owner.state !== 'special',
    'landing during source windup cannot strand airborne action ownership');
  assert(late.events.length === 1 && late.allocations.length === 1,
    'variant3 retains its one source release across landing during blend');
}
function testPairedJumpTrajectory(): void {
  for (const moving of [false,true]) {
    const active = setup(), control = setup(); jump(active); jump(control);
    active.press(); control.tick();
    for (let i=0;i<(moving?4:60);i++) {
      for (const axis of ['x','y','z'] as const) {
        assert(Math.abs(active.owner.pos[axis]-control.owner.pos[axis])<1e-6,
          `variant3 preserves paired no-X jump position ${axis} at update${i}, moving${moving}`);
        assert(Math.abs(active.owner.vel[axis]-control.owner.vel[axis])<1e-6,
          `variant3 preserves paired no-X jump velocity ${axis} at update${i}, moving${moving}`);
      }
      assert(active.owner.grounded === control.owner.grounded, 'air action preserves paired landing time');
      if (moving) active.inputs.p1.moveX = control.inputs.p1.moveX = 1;
      active.tick(); control.tick();
    }
  }
}
function testMovementCancellation(): void {
  const t = setup(); jump(t); launch(t);
  t.inputs.p1.moveX = 1; t.tick();
  for (let i=0;i<6;i++) t.tick();
  assert(!t.owner.cooldowns['romSpecialActive'] && t.owner.state !== 'special',
    'real held movement cancels airborne source recovery');
  t.inputs.p1.moveX = 0;
  finish(t);
  assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1,
    'movement cancellation leaves no stale pending source release or held-X replay');
}
/** Synthetic adjunct: sentinel state is not a claim of full lower-body parity. */
function testPartMaskSentinel(): void {
  const t = setup(); jump(t);
  const actor = t.driver.actor, part = actor.parts[1]!;
  part.streamPtr = 123456; part.stateByte = 71; part.active = 1;
  actor.fbPhaseSlots[0] = 0;
  timeBomberAirAction(actor,t.driver.ctx);
  assert(part.streamPtr === 123456 && part.stateByte === 71 && part.active === 1,
    'synthetic part1 sentinel survives mask1 initializer');
  const action = stream(t)!; action.stage = 'tail'; action.frame = 9; actor.fbPhaseSlots[0] = 2;
  actor.inputHeld5d8 = 0;
  timeBomberAirAction(actor,t.driver.ctx);
  assert(part.streamPtr === 123456 && part.stateByte === 71 && part.active === 1,
    'synthetic part1 sentinel survives mask1 terminal stream');
}
/** Synthetic angle adjunct isolates source roll from host auto-facing. */
function testForwardConeEdge(): void {
  for (const angle of [0x4800,-0x4800]) {
    const t = setup(); jump(t); admit(t);
    const actor = t.driver.actor as typeof t.driver.actor & RomHelperScratch;
    const radians = angle*Math.PI*2/65536;
    actor.heading = 0; actor.aimOrigin518 = v(0,0,0);
    actor.lockTarget = v(Math.sin(radians)*4000,10,Math.cos(radians)*4000);
    actor.aimRoll1dfc = 0;
    for (let i=1;i<=8;i++) {
      timeBomberAirAction(actor,t.driver.ctx);
      assert(actor.variantIndex === 3 && actor.aimRoll1dfc === Math.sign(angle)*Math.min(i*0x800,0x4000),
        'synthetic inclusive cone clamps to signed4000 and advances roll by fixed800');
      if(i<8) assert(t.events.length === 0, 'edge-cone source waits for roll convergence');
    }
    assert(t.events.length === 1 && shots(t)[0]?.timeBomberSource?.kind === 'primary',
      'synthetic inclusive edge-cone aim releases one dedicated primary');
  }
}
function testBehindTargetFallback(): void {
  const t = setup('pl0106',undefined,true); jump(t);
  // Set the spatial fixture behind the existing heading only after jumping.
  t.target.pos = v(0,10,-4000); t.other!.pos = v(3000,10,4000);
  const before = t.owner.weaponCells![1]!.cur;
  admit(t);
  t.inputs.p1.switchLock = true; t.tick(); t.inputs.p1.switchLock = false;
  assert(t.driver.actor.variantIndex === 4 && (t.driver.actor.controlWord & 3) === 3,
    'actual behind-target windup reissues full-body variant4');
  assert(t.owner.timeBomberSavedAim?.targetUid === t.other!.uid,
    'real R switch is resnapshotted when source reissues variant4');
  assert(t.events.length === 0 && t.allocations.length === 0 && !stream(t)?.fallback,
    'variant4 redispatch does not initialize or launch in the same actor update');
  const preFallbackY = t.owner.pos.y, preFallbackVelocity = t.driver.actor.yVel;
  t.tick();
  assert(Math.abs(t.owner.pos.y-preFallbackY-preFallbackVelocity)<1e-6,
    'fallback initialization applies source vertical displacement once, without host double movement');
  assert(stream(t)?.fallback && stream(t)?.mask === 15 && stream(t)?.frame === 0,
    'next actor update initializes source whole-body fallback clock');
  for (let i=0;i<40 && t.events.length === 0;i++) t.tick();
  assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1 && shots(t)[0]?.timeBomberSource?.kind === 'primary',
    'fallback emits one dedicated source primary');
  assert(shots(t)[0]!.aimedTargetUid === t.other!.uid && t.owner.weaponCells![1]!.cur === before-1,
    'fallback launch uses recaptured target and spends cell2 once');
  finish(t);
  assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1,
    'held X cannot repeat after fallback landing and recovery');
}
function testFallbackLandingCooldown(): void {
  const t = setup(); jump(t); t.target.pos = v(0,10,-4000); admit(t);
  for(let i=0;i<180 && !(t.driver.actor.variantIndex===4 && t.driver.actor.ubCue===7 &&
    t.driver.actor.stateTimer>0 && !t.owner.cooldowns['romSpecialActive']);i++) t.tick();
  assert(t.owner.grounded && t.driver.actor.stateTimer === 17 && t.events.length === 1,
    'fallback landing seeds source timer694 to16+dt');
  t.release(); t.press();
  assert(t.driver.actor.stateTimer>0 && !t.owner.cooldowns['romSpecialActive'] && t.events.length === 1,
    'fresh X edge cannot bypass positive source landing cooldown');
  t.release();
  for(let i=0;i<30 && t.driver.actor.stateTimer>0;i++)t.tick();
  assert(Number(t.driver.actor.stateTimer)===0, 'source landing cooldown expires at zero');
  t.press();
  assert(t.owner.cooldowns['romSpecialActive'], 'fresh X edge is admitted when source landing cooldown reaches zero');
  for(let i=0;i<30 && t.events.length<2;i++)t.tick();
  assert(Number(t.events.length)===2 && t.allocations.length===2,
    'post-cooldown action emits exactly one additional source projectile and debit');
}
function testDeathDuringWindup(): void {
  const t = setup(); jump(t); admit(t);
  const before = t.owner.weaponCells![1]!.cur;
  t.owner.hp=0; t.owner.state='death'; t.owner.stateTime=0;
  for(let i=0;i<60;i++)t.tick();
  assert(t.events.length===0 && t.allocations.length===0 && shots(t).length===0,
    'death during actual airborne windup clears pending source launch');
  assert(t.owner.weaponCells![1]!.cur===before && !t.owner.cooldowns['romSpecialActive'] && t.owner.state==='death',
    'death cannot restore stale jump presentation or spend pending ammunition');
}
export function runTimeBomberAirBattleSelfTest(): void {
  testPairedJumpTrajectory();
  testAirAdmissionAndFlight();
  testTargetlessAndCapturedAim();
  testEmptyAndLateLanding();
  testMovementCancellation();
  testPartMaskSentinel();
  testForwardConeEdge();
  testBehindTargetFallback();
  testFallbackLandingCooldown();
  testDeathDuringWindup();
  console.log('Time Bomber bounded airborne-neutral X Battle integration: passed');
}
