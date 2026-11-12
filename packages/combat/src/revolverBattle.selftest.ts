/** Actual Battle input coverage for Revolver Gunman and Billy source action 2.
 * Muzzles use decoded static binds, not animated joint matrices. Collision checks
 * exercise the declared host sphere/sweep and root target-center approximations,
 * not exact source HIT-shape geometry or the unavailable owner-local shell art.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { stepProjectiles } from './combat.js';
import { STATE } from './constants.js';
import type { Vec3 } from './rom/actor.js';
import { spawnRevolverSource } from './revolverProjectileRuntime.js';
import { runSelfTest as runRevolverProjectileSelfTest } from './revolverProjectile.selftest.js';
import type { BorgStats } from './stats.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const ids = ['pl0100', 'pl0108'] as const;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[revolverBattle] ${message}`);
}
function near(actual: number, expected: number, message: string, tolerance = 1e-6): void {
  assert(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
}
function same(actual: Vec3, expected: Vec3, message: string, tolerance = 1e-6): void {
  for (const axis of ['x', 'y', 'z'] as const) near(actual[axis], expected[axis], `${message} ${axis}`, tolerance);
}
function floorAndWall(wallZ?: number): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
    [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
  ];
  if (wallZ !== undefined) vertices.push([v(-2000, -1000, wallZ), v(2000, -1000, wallZ), v(0, 3000, wallZ)]);
  return { triangles: vertices.map((points, index) => ({ index, layerIndex: 0, marker: 0xcccccccc,
    vertices: points, normal: index === 2 ? v(0, 0, -1) : v(0, 1, 0), planeD: 0,
    bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
  })) };
}
interface SetupOptions {
  id?: string;
  extraTarget?: boolean;
  targetReplacement?: boolean;
  ownerReplacement?: boolean;
  reverseActors?: boolean;
  wallZ?: number;
}
function setup(options: SetupOptions = {}) {
  const id = options.id ?? 'pl0100';
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floorAndWall(options.wallZ),
    forces: [
      { team: 0, ownerPlayer: 'p1', borgIds: options.ownerReplacement ? [id, id] : [id] },
      { team: 1, ownerPlayer: 'p2', borgIds: options.targetReplacement ? ['pl0615', 'pl0615'] : ['pl0615'] },
      ...(options.extraTarget ? [{ team: 1, ownerPlayer: 'p3', borgIds: ['pl0615'] }] : []),
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
  // Relocation must pass through the real two-frame own-history sampler before
  // admission; resetting the history at attack entry would hide movement defects.
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  if (options.reverseActors) state.borgs.reverse();
  let elapsed = 0;
  const events: { frame: number; address: number; row: number; phase: number; contact: number;
    auxiliary: number; stateByte: number; pos: Vec3; heading: number; scale: number }[] = [];
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const cues: number[] = [];
  battle.onRomCue = cue => cues.push(cue);
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row, phase: actor.fbPhaseSlots[0]!, contact: actor.contactP1,
      auxiliary: (actor.parts[0] as typeof actor.parts[0] & { c?: number }).c ?? 0,
      stateByte: actor.parts[0]!.stateByte, pos: { ...actor.pos }, heading: actor.heading,
      scale: actor.modelScale * actor.sizeScale });
    spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted });
    return accepted;
  };
  const tick = () => { elapsed++; return battle.step(1 / 60, inputs); };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, tick, press, release,
    get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function shots(test: Fixture): Projectile[] {
  return test.state.projectiles.filter(p => p.ownerUid === test.owner.uid);
}
function launch(test: Fixture): Projectile[] {
  test.press();
  for (let i = 0; i < 14; i++) test.tick();
  const volley = shots(test);
  assert(volley.length === 2 && volley.every(p => p.revolverSource), 'actual X produces two dedicated source shells');
  return volley;
}
function waitIdle(test: Fixture, limit = 150): void {
  for (let i = 0; i < limit && (test.owner.state === 'special' || test.owner.cooldowns['romSpecialActive']); i++) test.tick();
  assert(test.owner.state !== 'special' && !test.owner.cooldowns['romSpecialActive'], 'source action releases Battle ownership');
}
function jump(test: Fixture): void {
  test.inputs.p1.jump = true; test.tick();
  test.inputs.p1.jump = false;
  for (let i = 0; i < 3; i++) test.tick();
  assert(!test.owner.grounded && test.owner.pos.y > 10, 'real jump input establishes airborne admission');
}

function testAdmissionAndRelease(): void {
  for (const id of ids) for (const airborne of [false, true]) {
    const t = setup({ id });
    const cell = t.owner.weaponCells![1]!;
    assert(t.owner.weaponCells![2] === cell && cell.cur === 1 && cell.max === 1 && cell.timer === 0,
      `${id}: full HUD X cell aliases source slot2 with no initial debt`);
    assert(cell.refillType === 0 && cell.refillParam === (id === 'pl0100' ? 180 : 120), `${id}: decoded baseline refill`);
    const bAmmo = t.owner.weaponCells![0]!.cur;
    if (airborne) jump(t);
    const before = { ...t.owner.pos }, start = t.frame + 1;
    t.press();
    assert(t.owner.command?.type === 2 && t.owner.command.actionIndex === 2 && t.owner.command.exact,
      `${id}: real press selects exact type2/action2`);
    assert(t.owner.command.recordAddress === (airborne ? '0x802d46a8' : '0x802d4668') &&
      t.driver.actor.variantIndex === (airborne ? 4 : 0) && t.driver.actor.fbCue === (airborne ? 45 : 44),
      `${id}: ground/air command bytes reach the actual cue dispatcher`);
    assert(t.driver.actor.streamSlot === (airborne ? 1 : 0), `${id}: matching g4 stream selected`);
    if (!airborne) same(t.owner.pos, before, `${id}: stationary X is not a target-distance teleport`);
    assert(t.events.length === 0 && t.allocations.length === 0 && cell.cur === 1 && shots(t).length === 0,
      'admission has no early allocation, shell, or generic fallback');
    for (let frame = 1; frame < 14; frame++) {
      t.tick();
      assert(t.events.length === 0 && t.allocations.length === 0 && cell.cur === 1 && shots(t).length === 0,
        `${id}: source gate remains closed at frame${frame}`);
    }
    t.tick();
    assert(t.events.map(e => e.row).join(',') === (id === 'pl0100' ? '0,1' : '13,14'), `${id}: exact ordered dual rows`);
    assert(t.events.every(e => e.address === 0x80084600 && e.frame === start + 14 && e.phase === 2 &&
      e.contact === 1 && e.auxiliary === 1 && e.stateByte === 0), 'authored part0 aux14, not physical contact, releases both children');
    assert(Number(t.allocations.length) === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 &&
      t.allocations[0]!.mode === 1 && t.allocations[0]!.accepted && t.allocations[0]!.frame === start + 14,
      'both children share exactly one consuming source allocation');
    assert(Number(cell.cur) === 0 && Number(cell.timer) === cell.refillParam && t.owner.weaponCells![0]!.cur === bAmmo,
      'release spends X once, seeds full debt and leaves B untouched');
    const volley = shots(t);
    assert(volley.length === 2 && volley.every(p => p.revolverSource && !p.poweredSource && !p.gatlingSource),
      'only dedicated source shells, never generic B/Powered/Gatling substitutes');
    assert(volley.every(p => p.life === 600 && p.romShotKind === 0 && p.damageRecord?.index === 1 &&
      p.damageRecord.hpDamage === 30 && p.hitRadius === 20 && p.flightVisual?.bankTexId !== 11),
      'constructor preserves source life/HIT0/damage1 and does not mislabel owner-local model11 as global FX11');
    assert(t.battle.observe().poweredLaunchFlashes.length === 0, 'effect5 is not misrepresented as Powered effect0');
    for (let i = 0; i < volley.length; i++) {
      const event = t.events[i]!, left = i === 0;
      const x = (left ? -185.59277391433716 : 185.59280443191528) * event.scale;
      const y = (left ? 142.1260347366333 : 142.12609577178955) * event.scale;
      const z = (left ? 22.99999614616 : 22.9999860628) * event.scale;
      const yaw = event.heading * Math.PI * 2 / 65536;
      same(volley[i]!.pos, v(event.pos.x + x * Math.cos(yaw) + z * Math.sin(yaw),
        event.pos.y + y, event.pos.z - x * Math.sin(yaw) + z * Math.cos(yaw)), 'static-bind muzzle, no constructor flight step');
    }
    const observed = t.battle.observe();
    assert(observed.revolverLaunchFlashes.length === 2 && new Set(observed.revolverLaunchFlashes.map(f => f.uid)).size === 2,
      'two successful children publish two distinct source effect5 instances');
    for (let i = 0; i < 2; i++) {
      const flash = observed.revolverLaunchFlashes[i]!;
      same(flash.pos, volley[i]!.pos, 'launch presentation captures constructor muzzle, not later flight');
      assert(flash.effectId === 5 && flash.ownerUid === t.owner.uid && flash.baseScale === t.events[i]!.scale &&
        flash.layers.map(layer => `${layer.modelId}:${layer.lifeFrames}:${layer.ageFrames}`).join(',') === '92:2:0,35:7:0',
        'effect5 carries its two distinct global models and authored lifetimes');
    }
    assert(t.cues.filter(cue => cue === 6).length === 2, 'one source cue6 per successfully initialized child');
    for (let i = 0; i < 5; i++) assert(t.battle.observe() === observed, 'render-only observation is cached and cannot advance source life');
    t.tick();
    assert(volley.every(p => p.life === 599) && observed.projectiles.every(p => p.life === 600),
      'first later Battle tick advances once; previous observation remains detached');
    assert(observed.revolverLaunchFlashes.every(f => f.layers.every(layer => layer.ageFrames === 0)) &&
      t.battle.observe().revolverLaunchFlashes.every(f => f.layers.every(layer => layer.ageFrames === 1)),
      'presentation ages once on simulation frames and previous snapshots stay detached');
    for (let i = 0; i < 6; i++) t.tick();
    assert(t.battle.observe().revolverLaunchFlashes.length === 0, 'both effect5 instances expire after longest layer7');
    waitIdle(t);
    for (let i = 0; i < 250; i++) t.tick();
    assert(Number(t.events.length) === 2 && Number(t.allocations.length) === 1, 'holding X through recovery and refill cannot repeat');
    t.release(); t.press();
    for (let i = 0; i < 14; i++) t.tick();
    assert(Number(t.events.length) === 4 && Number(t.allocations.length) === 2, 'fresh repress produces one new dual volley');
  }
}

function testInputDenialsAndRecovery(): void {
  for (const id of ids) {
    const tap = setup({ id }); tap.press(); tap.inputs.p1.special = false;
    for (let i = 0; i < 14; i++) tap.tick();
    assert(tap.events.length === 2 && tap.allocations.length === 1, `${id}: one-frame tap completes authored release`);
    for (let i = 0; i < 200; i++) tap.tick();
    assert(tap.events.length === 2, 'release cannot create a second action');
    for (const mode of ['empty', 'depleted', 'interrupted', 'busy'] as const) {
      const t = setup({ id });
      const cell = t.owner.weaponCells![1]!;
      if (mode === 'empty') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      t.press();
      if (mode === 'depleted') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'interrupted') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      const hp = t.target.hp;
      for (let i = 0; i < 230; i++) {
        const observed = t.tick();
        assert(observed.projectiles.every(p => p.ownerUid !== t.owner.uid), `${id}/${mode}: no transient damaging fallback`);
      }
      assert(t.events.length === 0 && t.target.hp === hp, `${id}/${mode}: no dual shot or hidden damage`);
      assert(mode === 'depleted' ? t.allocations.length === 1 && !t.allocations[0]!.accepted : t.allocations.length === 0,
        `${id}/${mode}: only late depletion attempts source allocation`);
      t.release(); t.press();
      for (let i = 0; i < 14; i++) t.tick();
      assert(Number(t.events.length) === 2, `${id}/${mode}: denial/interrupt does not poison later real X or queue held input`);
    }
    const blocked = setup({ id }); blocked.press();
    blocked.release(); blocked.press(); // New rising edge while the first action owns the actor.
    for (let i = 0; i < 250; i++) blocked.tick();
    assert(blocked.events.length === 2 && blocked.allocations.length === 1,
      `${id}: fresh press during ROM ownership is discarded, not buffered until recovery/refill`);
    const windup = setup({ id }); windup.target.pos = v(20, 10, 0); const hp = windup.target.hp;
    windup.press();
    for (let i = 0; i < 13; i++) windup.tick();
    assert(windup.target.hp === hp && windup.events.length === 0, 'close target receives no body/effect damage during windup');
    windup.owner.state = 'hit'; windup.owner.stateTime = 0; windup.owner.cooldowns['hitstun'] = 20;
    for (let i = 0; i < 100; i++) windup.tick();
    assert(windup.target.hp === hp && windup.events.length === 0, 'interruption removes pending release without ghost damage');
  }
}

function testAuthoredRecovery(): void {
  for (const id of ids) for (const airborne of [false, true]) {
    const t = setup({ id }); if (airborne) jump(t);
    t.press();
    for (let frame = 1; frame <= 56; frame++) {
      t.tick();
      assert(t.owner.state === 'special' && (t.driver.actor.controlWord & 3) !== 0,
        `${id}/${airborne ? 'air' : 'ground'}: recovery must not exit before authored completion at frame${frame}`);
      if (frame >= 45) assert(t.driver.actor.contactP0 === (airborne ? -1 : 0),
        'air stream supplies negative part0 state; grounded nonnegative state is not an exit signal');
    }
    t.tick();
    assert(t.owner.state === 'idle' && (t.driver.actor.controlWord & 3) === 0 && t.driver.actor.wallContact !== 0,
      'decoded terminal stream completion releases the source action and clears ownership');
    assert(t.events.length === 2 && t.allocations.length === 1, 'recovery never repeats the release gate');
  }
}

function testAmmoBoundaries(): void {
  for (const id of ids) {
    const t = setup({ id }); launch(t); t.inputs.p1.special = false;
    const cell = t.owner.weaponCells![1]!;
    for (let i = 1; i < cell.refillParam; i++) {
      t.tick();
      assert(cell.cur === 0 && cell.timer === cell.refillParam - i, `${id}: source debt ticks exactly once through frame${i}`);
    }
    t.tick(); assert(cell.cur === 1 && Number(cell.timer) === 0, `${id}: exact baseline refill boundary`);
    cell.cur = 0; cell.timer = cell.refillParam; t.owner.sourceAmmoRefillPauseMask = 4;
    t.tick(); assert(cell.timer === cell.refillParam, 'source slot2 pause bit4 pauses HUD X alias');
    t.owner.sourceAmmoRefillPauseMask = 2;
    t.tick(); assert(Number(cell.timer) === cell.refillParam - 1, 'HUD index1 pause bit2 does not pause source slot2');
  }
}

function testCapturedTargetIdentity(): void {
  for (const id of ids) {
    const moving = setup({ id }); moving.press();
    moving.target.pos = v(4000, 10, 0);
    for (let i = 0; i < 14; i++) moving.tick();
    const volley = shots(moving);
    assert(volley.length === 2 && volley.every(p => p.aimedTargetUid === moving.target.uid), 'moving target retains captured identity');
    assert(volley.every(p => p.vel.x > 0 && Math.abs(p.vel.x) > Math.abs(p.vel.z)),
      'windup aim follows captured target movement, not frozen admission position');

    const relock = setup({ id, extraTarget: true }); assert(relock.other, 'switch-lock fixture has another live enemy');
    relock.press(); relock.inputs.p1.switchLock = true; relock.tick(); relock.inputs.p1.switchLock = false;
    assert(relock.owner.targetLockState?.activeTargetUid === relock.other.uid, 'real R input changes active lock to B');
    for (let i = 0; i < 13; i++) relock.tick();
    assert(shots(relock).every(p => p.aimedTargetUid === relock.target.uid), 'release preserves attack target A despite current lock B');
    const control = setup({ id, extraTarget: true }); const unchanged = launch(control);
    for (let i = 0; i < 2; i++) {
      near(relock.events[i]!.heading, control.events[i]!.heading, 'R-switch cannot turn the attack body toward replacement lock B');
      same(shots(relock)[i]!.pos, unchanged[i]!.pos, 'R-switch cannot move the source muzzle toward B');
      same(shots(relock)[i]!.vel, unchanged[i]!.vel, 'R-switch preserves the captured-A launch direction as well as target UID');
    }

    const lost = setup({ id, extraTarget: true }); assert(lost.other, 'target-loss fixture has replacement lock');
    lost.press(); lost.target.hp = 0; lost.target.state = 'death'; lost.target.stateTime = 0;
    for (let i = 0; i < 14; i++) lost.tick();
    assert(lost.owner.targetLockState?.activeTargetUid === lost.other.uid, 'host acquires B after A dies');
    assert(shots(lost).length === 2 && shots(lost).every(p => p.aimedTargetUid === null),
      'dead captured pointer clears without replacing it with active B');

    const absent = setup({ id, targetReplacement: true });
    absent.target.hp = 0; absent.target.state = 'death'; absent.target.stateTime = STATE.DEATH_DURATION - 2;
    absent.press(); assert(absent.owner.targetLockState?.activeTargetUid === null, 'admission really has no available target');
    for (let i = 0; i < 14; i++) absent.tick();
    const replacement = absent.state.borgs.find(b => b.ownerPlayer === 'p2' && b.uid !== absent.target.uid && b.alive);
    assert(replacement && absent.owner.targetLockState?.activeTargetUid === replacement.uid, 'real force replacement becomes a new active lock during windup');
    assert(shots(absent).length === 2 && shots(absent).every(p => p.aimedTargetUid === null),
      'targetless admission cannot acquire the newly deployed target for its pending shot');
  }
}

function testRangeAndInFlightTargetLoss(): void {
  for (const id of ids) {
    for (const range of [5999.99, 6000, 6000.01]) {
      const t = setup({ id }); t.target.pos = v(0, 10, range);
      for (let i = 0; i < 3; i++) t.tick();
      const volley = launch(t);
      assert(t.owner.revolverAttack?.trackingEnabled === (range <= 6000), 'captured source range flag includes exactly6000');
      for (const projectile of volley) {
        assert(projectile.revolverSource?.kind === 'flight', 'range fixture initializes source flight');
        assert(projectile.revolverSource.flight.targetUid === (range <= 6000 ? t.target.uid : null),
          'constructor retains or clears tracking using admission range, without deleting the shot');
      }
    }
    const t = setup({ id, extraTarget: true }); assert(t.other, 'in-flight loss fixture has a second enemy');
    const volley = launch(t);
    t.target.hp = 0; t.target.state = 'death'; t.target.stateTime = 0;
    t.tick();
    assert(t.owner.targetLockState?.activeTargetUid === t.other.uid, 'host switches active target after captured target dies');
    for (const projectile of volley) {
      assert(projectile.revolverSource?.kind === 'flight' && projectile.revolverSource.flight.targetUid === null,
        'in-flight captured target clears and never rebinds to active lock');
      assert(t.state.projectiles.includes(projectile) && projectile.life === 599,
        'losing tracking does not kill the projectile or skip its flight update');
    }
  }
}

function testActorOrderAim(): void {
  for (const id of ids) {
    const probe = (reverseActors: boolean) => {
      const t = setup({ id, reverseActors });
      t.inputs.p2.moveX = 1;
      const volley = launch(t);
      return { target: { ...t.target.pos }, shots: volley.map(p => ({ pos: { ...p.pos }, vel: { ...p.vel } })) };
    };
    const normal = probe(false), reversed = probe(true);
    same(normal.target, reversed.target, 'target walking is independent of owner array order');
    for (let i = 0; i < 2; i++) {
      same(normal.shots[i]!.pos, reversed.shots[i]!.pos, `${id}: captured-identity aim prepass makes muzzle order-independent`);
      same(normal.shots[i]!.vel, reversed.shots[i]!.vel, `${id}: source launch aim is independent of actor iteration order`);
    }
  }
}

function testExistingActorAimBarrier(): void {
  for (const id of ['pl0101', 'pl0102']) {
    const probe = (reverseActors: boolean) => {
      const t = setup({ id, reverseActors }); t.inputs.p2.moveX = 1;
      t.press(); for (let i = 0; i < 16; i++) t.tick();
      assert(t.events.length > 0, `${id}: normal source release actually ran`);
      const aim = id === 'pl0101' ? t.owner.poweredNormalAim : t.owner.gatlingSavedAim;
      assert(aim?.targetUid === t.target.uid && t.target.sourceFramePose, 'existing lane retains target identity and frame snapshot');
      same(aim.pos, t.target.sourceFramePose.pos, 'existing actor aim reads the shared pre-movement target pose');
      assert(Math.hypot(t.target.pos.x - aim.pos.x, t.target.pos.z - aim.pos.z) > 0,
        'moving-target fixture distinguishes frame-start aim from post-movement root');
      return { aim: { ...aim.pos }, heading: t.events[0]!.heading };
    };
    const normal = probe(false), reversed = probe(true);
    same(normal.aim, reversed.aim, `${id}: pre-movement aim is independent of actor array order`);
    near(normal.heading, reversed.heading, `${id}: launch body heading cannot sample a later actor pose`);
  }
}

function testCollisionAndLifecycle(): void {
  for (const id of ids) {
    const wall = setup({ id, wallZ: 350 }); const volley = launch(wall);
    const seen = new Map<string, string>();
    for (let i = 0; i < 30 && seen.size < 2; i++) {
      const observed = wall.tick();
      for (const gone of observed.projectileDespawns) if (volley.some(p => p.uid === gone.uid)) {
        seen.set(gone.uid, gone.reason); near(gone.pos.z, 350, 'real terrain sweep ends on wall');
      }
      assert(observed.projectiles.every(p => p.revolverSource), 'terrain never produces an explosion, split, or unrelated child');
    }
    assert(seen.size === 2 && [...seen.values()].every(reason => reason === 'hit-terrain'), `${id}: both natural trajectories hit terrain with exact reasons`);
    assert(wall.cues.every(cue => cue !== 12), 'terrain creates no Gatling explosion cue');

    // At range800 the wide static muzzles and authored one-degree turn cap
    // legitimately pass outside this host body proxy. Use a reachable trajectory.
    const contact = setup({ id }); contact.target.pos = v(0, 10, 1500);
    for (let i = 0; i < 3; i++) contact.tick();
    const hp = contact.target.hp, hits = contact.battle.observe().telemetry.hitsByTeam[0] ?? 0;
    const fired = launch(contact); let connected = false;
    for (let i = 0; i < 150 && !connected; i++) {
      const observed = contact.tick();
      connected = observed.projectileDespawns.some(p => fired.some(shot => shot.uid === p.uid) && p.reason === 'hit-target');
    }
    assert(connected && contact.target.hp < hp, `${id}: input-created source flight naturally reaches victim damage`);
    assert((contact.battle.observe().telemetry.hitsByTeam[0] ?? 0) > hits, 'real victim connection reaches Battle telemetry');

    const ownerDeath = setup({ id, ownerReplacement: true }); const beforeDeath = launch(ownerDeath);
    ownerDeath.owner.hp = 0; ownerDeath.owner.state = 'death'; ownerDeath.owner.stateTime = STATE.DEATH_DURATION - 1;
    const deathFrame = ownerDeath.tick();
    assert(beforeDeath.every(p => deathFrame.projectileDespawns.some(gone => gone.uid === p.uid && gone.reason === 'owner-dead')),
      'real owner death removes both children, independently of later owner replacement');

    const expiry = setup({ id }); const [primary] = launch(expiry); assert(primary, 'expiry starts from actual input-created shell');
    // Isolate long-flight boundaries on the same source lifecycle seam, without
    // terrain or target collisions ending a valid trajectory before life600.
    const byUid = new Map(expiry.state.borgs.map(b => [b.uid, b]));
    byUid.delete(expiry.target.uid);
    let surviving = [primary];
    for (let frame = 1; frame < 600; frame++) {
      surviving = stepProjectiles(surviving, [], new Map(), byUid);
      assert(surviving.length === 1 && primary.life === 600 - frame, `natural source lifetime survives update${frame}`);
    }
    surviving = stepProjectiles(surviving, [], new Map(), byUid);
    assert(surviving.length === 0 && primary.despawnReason === 'expired', '600th flight update expires without explosion');
    const bounds = setup({ id }); const outside = launch(bounds)[0]!;
    const result = stepProjectiles([outside], [], new Map(), new Map(bounds.state.borgs.map(b => [b.uid, b])),
      { bounds: { minX: -1, maxX: 1, minZ: -1, maxZ: 1 }, collision: null });
    assert(result.length === 0 && outside.despawnReason === 'out-of-bounds', 'input-created shell preserves bounds termination reason');
  }
}

function testOtherFamilies(): void {
  for (const id of ['pl0101', 'pl0102', 'pl0104', 'pl0615']) {
    const t = setup({ id }); t.press();
    for (let i = 0; i < 70; i++) {
      const observation = t.tick();
      assert(observation.projectiles.every(p => !p.revolverSource), `${id}: unrelated family never receives Revolver state`);
    }
    assert(t.events.every(event => event.address !== 0x80084600), `${id}: no Revolver family dispatch`);
  }
}

function testStrictAdapterScope(): void {
  const t = setup(); launch(t);
  const sourceAction = t.driver.actor.actionIndex;
  t.driver.actor.actionIndex = 0;
  assert(spawnRevolverSource(t.owner, t.driver.actor, 0x80084600, 0) === null, 'B action is outside the dedicated X adapter');
  t.driver.actor.actionIndex = sourceAction;
  assert(spawnRevolverSource(t.owner, t.driver.actor, 0x8007db5c, 0) === null, 'another spawner is outside the dedicated adapter');
  assert(spawnRevolverSource(t.owner, t.driver.actor, 0x80084600, 13)?.length === 0, 'Billy row cannot enter Revolver source lane');
  const other = setup({ id: 'pl0102' }); other.driver.actor.actionIndex = 2;
  assert(spawnRevolverSource(other.owner, other.driver.actor, 0x80084600, 0) === null, 'unrelated owner is outside the dedicated adapter');
}

export function runRevolverBattleSelfTest(): void {
  runRevolverProjectileSelfTest();
  testAdmissionAndRelease();
  testInputDenialsAndRecovery();
  testAuthoredRecovery();
  testAmmoBoundaries();
  testCapturedTargetIdentity();
  testRangeAndInFlightTargetLoss();
  testActorOrderAim();
  testExistingActorAimBarrier();
  testCollisionAndLifecycle();
  testOtherFamilies();
  testStrictAdapterScope();
  console.log('Revolver/Billy source-X Battle integration: passed (static binds and host collision geometry)');
}
