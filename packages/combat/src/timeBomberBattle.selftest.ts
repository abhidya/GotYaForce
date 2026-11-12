/** Bounded ground-neutral X integration. Attacks enter through real Battle input.
 * Position/HP setup only builds fixtures; no command dispatch or injected contact.
 * Geometry remains the host sphere/sweep approximation, not source HIT geometry. */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { stepProjectiles } from './combat.js';
import { STATE } from './constants.js';
import { runSelfTest as runTimeBomberProjectileSelfTest } from './timeBomberProjectile.selftest.js';
import { emptyInput, type StageCollision } from './types.js';
import type { BorgStats } from './stats.js';
import type { TimeBomberAction } from './families/time-bomber.js';
import type { Vec3 } from './rom/actor.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[timeBomberBattle] ${message}`);
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
function launch(t: Fixture) {
  t.press();
  assert(t.owner.command?.exact && t.owner.command.type === 2 && t.owner.command.actionIndex === 0 &&
    t.owner.command.variantIndex === 0 && t.owner.command.recordAddress === '0x803361d8', 'actual neutral ground X selects exact action0/variant0');
  assert(t.driver.actor.streamHold1b03 === 6 && t.driver.actor.contactP0 === 1, 'source animation blend and part0 stream state gate admission');
  assert(shots(t).length === 0 && t.events.length === 0 && t.allocations.length === 0, 'admission has no immediate generic projectile or ammo allocation');
  // Source startup elapsed2 advances through blend elapsed3/4/5; aligned
  // facing releases on the third post-admission update (801309b8).
  for (let i = 0; i < 2; i++) { t.tick(); assert(t.events.length === 0 && shots(t).length === 0, 'source blend gate blocks early release'); }
  t.tick();
  assert(Number(t.events.length) === 1 && t.events[0]!.address === 0x800fe668 && t.events[0]!.row === 2,
    'actual X reaches exactly one source Time Bomber row2 child');
  const projectile = shots(t)[0];
  assert(shots(t).length === 1 && projectile?.timeBomberSource?.kind === 'primary', 'source launch publishes one dedicated primary, never a generic projectile');
  return projectile;
}
function idle(t: Fixture) {
  for (let i = 0; i < 180 && (t.owner.state === 'special' || t.owner.cooldowns['romSpecialActive']); i++) t.tick();
  assert(t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'], 'source recovery releases Battle ownership');
}
function testAdmissionAmmoAndRepeat(): void {
  const t = setup();
  const x = t.owner.weaponCells![1]!, b = t.owner.weaponCells![0]!;
  assert(t.owner.weaponCells![2] === x && x.cur > 0, 'HUD X aliases original source slot2');
  const before = x.cur, bBefore = b.cur;
  launch(t);
  assert(t.allocations.length === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 && t.allocations[0]!.accepted,
    'one source-slot2 consuming allocation for one bomb');
  assert(x.cur === before - 1 && b.cur === bBefore && x.timer === 300 && x.refillParam === 300, 'source launch spends X once, seeds debt300, and leaves B untouched');
  // Original MOT END20/9 and realtime wait8, with wait-before-update semantics.
  while (t.frame < 41) {
    t.tick();
    const stream = (t.driver.actor as typeof t.driver.actor & { timeBomberAction?: TimeBomberAction }).timeBomberAction!;
    if (t.frame === 25) assert(stream.stage === 'wait' && stream.wait === 8, 'wait starts after original animation END20, without same-frame decrement');
    if (t.frame === 33) assert(stream.stage === 'tail' && stream.frame === 1, 'eight realtime ticks start tail with its immediate update');
    if (t.frame === 41) assert(stream.stage === 'tail' && stream.frame === 9, 'tail reaches original MOT END9 before terminal test');
    assert(t.owner.state === 'special', `source retains ownership through inputframe41 (frame${t.frame}, flag${t.owner.cooldowns['romSpecialActive']}, state${t.owner.state})`);
  }
  t.tick();
  assert(t.frame === 42 && !t.owner.cooldowns['romSpecialActive'] && t.owner.state !== 'special', 'authored END20/wait8/END9 releases ownership at inputframe42');
  idle(t);
  for (let i = 0; i < 100; i++) t.tick();
  assert(t.events.length === 1, 'holding X through recovery never repeats the source launch');
  t.release();
  for (let i = 0; i < 1000 && (x.cur < 1 || (t.owner.cooldowns['special'] ?? 0) > 0); i++) t.tick();
  assert(x.cur >= 1, 'original source refill permits another action');
  t.press();
  for (let i = 0; i < 90 && t.events.length < 2; i++) t.tick();
  assert(Number(t.events.length) === 2 && Number(t.allocations.length) === 2, 'released and repressed X launches again after recovery');
}
function testFacingAndRefill(): void {
  const facing = setup(); facing.owner.rotY = Math.PI;
  facing.press(); for (let i = 0; i < 3; i++) facing.tick();
  assert(facing.events.length === 0 && shots(facing).length === 0, 'opposite facing does not release merely because blend completed');
  for (let i = 0; i < 30 && facing.events.length === 0; i++) facing.tick();
  assert(Number(facing.events.length) === 1 && facing.allocations.length === 1, 'source yaw completion or timer admits exactly one delayed shot');
  const refill = setup(); const cell = refill.owner.weaponCells![1]!; launch(refill);
  for (let i = 0; i < 299; i++) refill.tick();
  assert(cell.cur === 2 && cell.timer === 1, 'source refill is integer ammunition with one debt tick remaining');
  refill.tick();
  assert(Number(cell.cur) === 3 && Number(cell.timer) === 0, 'source debt300 grants the next integer round at the original boundary');
}
function testEmptyAndScope(): void {
  const empty = setup(); const x = empty.owner.weaponCells![1]!; x.cur = 0; x.timer = x.refillParam * x.max;
  empty.press(); for (let i = 0; i < 30; i++) empty.tick();
  assert(empty.events.length === 0 && shots(empty).length === 0, 'empty X cannot manufacture a source or generic shot');
  for (const id of ['pl0103', 'pl0107', 'pl0100', 'pl0102']) {
    const t = setup(id); t.press(); for (let i = 0; i < 70; i++) t.tick();
    assert(t.events.every(e => e.address !== 0x800fe668), `${id}: unrelated family never enters Time Bomber spawner`);
  }
  const directional = setup(); directional.inputs.p1.moveX = 1; directional.press();
  for (let i = 0; i < 60; i++) directional.tick();
  assert(directional.events.every(e => e.address !== 0x800fe668), 'directional X remains outside neutral-only source lane');
  const primary = setup(); primary.inputs.p1.attack = true; primary.tick(); primary.inputs.p1.attack = false;
  primary.tick();
  assert(shots(primary).length === 1 && shots(primary)[0]!.timeBomberSource?.kind === 'mine' && primary.owner.weaponCells![0]!.cur === 9, 'B press creates one dedicated mine and release does not duplicate it');
  for (let i = 0; i < 60; i++) primary.tick();
  assert(primary.events.every(e => e.address !== 0x800fe668), 'B remains outside bounded X source lane');
}
function testRangeAndCapturedTarget(): void {
  for (const range of [6000, 6001]) {
    const t = setup();
    t.target.pos = v(t.owner.pos.x, t.owner.pos.y, t.owner.pos.z + range);
    for (let i = 0; i < 3; i++) t.tick();
    assert(Math.hypot(t.target.pos.x - t.owner.pos.x, t.target.pos.y - t.owner.pos.y, t.target.pos.z - t.owner.pos.z) === range,
      `static admission fixture is exactly${range} from owner origin`);
    const bomb = launch(t); const source = bomb.timeBomberSource;
    assert(source?.kind === 'primary' && source.targetUid === (range === 6000 ? t.target.uid : null),
      `actual admission${range} binds the inclusive source homing limit`);
    assert(bomb.aimedTargetUid === t.target.uid, 'outside steering range still preserves constructor target aim');
    const aim = t.owner.timeBomberSavedAim!.pos;
    const delta = v(aim.x - bomb.pos.x, aim.y - bomb.pos.y, aim.z - bomb.pos.z);
    const length = Math.hypot(delta.x, delta.y, delta.z);
    for (const axis of ['x', 'y', 'z'] as const)
      assert(Math.abs(bomb.vel[axis] - delta[axis] / length * 20) < 1e-6, 'initial velocity aims at captured target even outside homing range');
  }
  const absent = setup(); absent.target.hp = 0; absent.target.state = 'death'; absent.target.stateTime = 0;
  const unguided = launch(absent);
  assert(absent.owner.timeBomberSavedAim?.targetUid === null && unguided.timeBomberSource?.kind === 'primary' &&
    unguided.timeBomberSource.targetUid === null && unguided.aimedTargetUid === null,
    'actual targetless admission creates unguided source primary');
  assert(Math.abs(unguided.vel.x) < 1e-6 && Math.abs(unguided.vel.y) < 1e-6 && Math.abs(unguided.vel.z - 20) < 1e-6,
    'targetless source constructor uses forward heading instead of stale target');
  const switched = setup('pl0106', undefined, true); assert(switched.other, 'R-switch fixture has another enemy');
  switched.press(); switched.inputs.p1.switchLock = true; switched.tick(); switched.inputs.p1.switchLock = false;
  assert(switched.owner.targetLockState?.activeTargetUid === switched.other.uid, 'real R changes active target during windup');
  switched.tick(); switched.tick();
  const shot = shots(switched)[0];
  assert(switched.events.length === 1 && shot?.timeBomberSource?.kind === 'primary' &&
    shot.timeBomberSource.targetUid === switched.target.uid && shot.aimedTargetUid === switched.target.uid &&
    switched.owner.timeBomberSavedAim?.targetUid === switched.target.uid,
    'R-switch cannot retarget the pending source primary away from its admitted target');
}
function testNaturalCollision(): void {
  const wall = setup('pl0106', 350); const bomb = launch(wall);
  let explosion = shots(wall).find(p => p.timeBomberSource?.kind === 'explosion');
  let wallImpact = false;
  for (let i = 0; i < 60 && !explosion; i++) {
    const observed = wall.tick();
    wallImpact ||= observed.projectileDespawns.some(p => p.uid === bomb.uid && p.reason === 'hit-terrain');
    explosion = shots(wall).find(p => p.timeBomberSource?.kind === 'explosion');
  }
  assert(wallImpact && explosion, 'input-created primary naturally sweeps wall and creates explosion19');
  assert(Math.abs(explosion.pos.z - 350) < 1e-6 && explosion.romShotKind === 179 && explosion.damageRecord?.index === 26,
    'wall explosion uses impact point and common HIT179/damage26, not per-borg primary damage');
  assert(explosion.flightVisual?.bankTexId === 22 && wall.cues.filter(c => c === 12).length === 1,
    'explosion19 presents original global model22 and emits cue12 exactly once');
  const contact = setup(); contact.target.pos = v(0, 10, 1500);
  for (let i = 0; i < 3; i++) contact.tick();
  const hp = contact.target.hp; const projectile = launch(contact);
  let connected = false, spawnedExplosion = false;
  for (let i = 0; i < 150 && !connected; i++) {
    const observed = contact.tick();
    connected ||= observed.projectileDespawns.some(p => p.uid === projectile.uid && p.reason === 'hit-target');
    spawnedExplosion ||= shots(contact).some(p => p.timeBomberSource?.kind === 'explosion');
  }
  assert(connected && spawnedExplosion && contact.target.hp < hp, 'natural primary contact damages enemy and creates explosion19');
}
function testProjectileEndings(): void {
  const expiry = setup(); const primary = launch(expiry);
  assert(primary.life === 300, 'source primary retains row2 lifetime300 at construction');
  const byUid = new Map(expiry.state.borgs.map(b => [b.uid, b]));
  byUid.delete(expiry.target.uid);
  let surviving = [primary];
  if (primary.timeBomberSource?.kind === 'primary' && primary.timeBomberSource.pending) {
    const pos = { ...primary.pos };
    surviving = stepProjectiles(surviving, [], new Map(), byUid);
    assert(primary.life === 300 && Math.hypot(primary.pos.x - pos.x, primary.pos.y - pos.y, primary.pos.z - pos.z) === 0, 'pending source initialization neither flies nor decrements life');
  }
  for (let frame = 1; frame <= 300; frame++) {
    surviving = stepProjectiles(surviving, [], new Map(), byUid);
    assert(surviving.length === 1 && primary.life === 300 - frame, `primary survives source flight update${frame}`);
  }
  surviving = stepProjectiles(surviving, [], new Map(), byUid);
  assert(surviving.length === 0 && primary.despawnReason === 'expired', 'natural lifetime retires without an explosion child');
  const outside = setup(); const boundsShot = launch(outside);
  const bounded = stepProjectiles([boundsShot], [], new Map(), new Map(outside.state.borgs.map(b => [b.uid, b])),
    { bounds: { minX: -1, maxX: 1, minZ: -1, maxZ: 1 }, collision: null });
  assert(bounded.length === 0 && boundsShot.despawnReason === 'out-of-bounds', 'bounds termination never creates explosion19');
  const changed = setup(); const oldForm = launch(changed); changed.owner.borgId = 'pl0103';
  const invalidated = stepProjectiles([oldForm], [], new Map(), new Map(changed.state.borgs.map(b => [b.uid, b])));
  assert(invalidated.length === 0 && oldForm.despawnReason === 'owner-dead', 'owner form identity change retires original source child');
  const death = setup(); const orphan = launch(death);
  death.owner.hp = 0; death.owner.state = 'death'; death.owner.stateTime = STATE.DEATH_DURATION - 1;
  const observed = death.tick();
  assert(observed.projectileDespawns.some(p => p.uid === orphan.uid && p.reason === 'owner-dead'),
    'real owner death retires input-created child with owner-dead reason');
}
export function runTimeBomberBattleSelfTest(): void {
  runTimeBomberProjectileSelfTest();
  testAdmissionAmmoAndRepeat();
  testEmptyAndScope();
  testFacingAndRefill();
  testProjectileEndings();
  testNaturalCollision();
  testRangeAndCapturedTarget();
  console.log('Time Bomber bounded ground-neutral X Battle integration: passed');
}
