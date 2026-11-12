/** Actual Battle input coverage for Beam Gunner source action 2.
 * Muzzles use decoded static binds, not animated joint matrices. Collision checks
 * exercise the declared host sphere/sweep and root target-center approximations,
 * not exact source HIT-shape geometry or animated weapon-bank presentation.
 * Browser face-button mapping is an explicit adapter, not pad parity proof.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { beamMuzzle, spawnBeamSource } from './beamProjectile.js';
import { RomDriverBridge } from './bridge.js';
import { applyHit, stepProjectiles } from './combat.js';
import { buildProfile } from './stats.js';
import { STATE } from './constants.js';
import type { Vec3 } from './rom/actor.js';
import type { GunmanScratch } from './families/gunman-cluster.js';
import type { BorgStats } from './stats.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };

// Updated only after auditing the authored stream/animation boundary.
const RELEASE_FRAME = 69;
const stats = (borgsData as { borgs: BorgStats[] }).borgs;

const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[beamBattle] ${message}`);
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
  const id = options.id ?? 'pl0104';
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
function streamFlags(t: Fixture): { beamFlags6e8?: number; beamFlags6e9?: number; beamContactFlags709?: number } {
  return t.driver.actor as typeof t.driver.actor & { beamFlags6e8?: number; beamFlags6e9?: number; beamContactFlags709?: number };
}
function scratch(t: Fixture): GunmanScratch { return t.driver.actor as typeof t.driver.actor & GunmanScratch; }
function shots(t: Fixture): Projectile[] { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }
function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false;
  for (let i = 0; i < 3; i++) t.tick();
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'actual jump establishes airborne admission');
}
function launch(t: Fixture): Projectile {
  t.press();
  for (let i = 0; i < RELEASE_FRAME - 1; i++) t.tick();
  const beam = shots(t)[0];
  assert(beam?.beamSource && shots(t).length === 1, 'real X creates exactly one source emitter');
  return beam;
}
function testAdmissionAndTiming(): void {
  for (const airborne of [false, true]) {
    const t = setup(); if (airborne) jump(t);
    const x = t.owner.weaponCells![1]!, bAmmo = t.owner.weaponCells![0]!.cur;
    const start = t.frame + 1;
    t.press();
    assert(t.owner.command?.type === 2 && t.owner.command.actionIndex === 2 && t.owner.command.exact,
      'actual X selects exact action2');
    assert(t.owner.command.recordAddress === (airborne ? '0x80321448' : '0x80321408') &&
      t.driver.actor.variantIndex === (airborne ? 4 : 0) && t.driver.actor.fbCue === (airborne ? 45 : 44),
      'ground/air command identity and source cue44/45 reach bridge');
    assert(scratch(t).gmBeamTimer560 === 60 && scratch(t).gmBeamCharge54e === 60,
      'source entry seeds independent sixty-frame timer and sixty-event extension budget');
    assert((t.driver.actor.controlWord & 0xff0) === 0x40 && t.driver.actor.defaultGroup === 1 &&
      t.driver.actor.contactP1 === 0 && streamFlags(t).beamFlags6e8 === 0 && streamFlags(t).beamFlags6e9 === 0 &&
      streamFlags(t).beamContactFlags709 === 1,
      'slot0 writes posture40/group1/709=1 and clears part1/6e8/6e9');
    assert(shots(t).length === 0 && t.events.length === 0, 'admission has no early generic projectile');
    for (let i = 1; i < RELEASE_FRAME - 1; i++) {
      t.tick(); assert(shots(t).length === 0 && t.events.length === 0, `no premature beam at windup${i}`);
      if (i === 25) assert(t.driver.actor.contactP0 === 1 && t.driver.actor.wallContact === 0,
        'first animation-end contact at t25 is not the terminal release gate');
      if (i === 27) assert(t.driver.actor.contactP0 === 0 && streamFlags(t).beamFlags6e9 === 2,
        't27 clears the contact pulse and writes source6e9=2');
    }
    t.tick();
    assert(Number(t.events.length) === 1 && t.events[0]!.frame === start + RELEASE_FRAME - 1 &&
      t.events[0]!.address === 0x800e19a8 && t.events[0]!.row === 1,
      'authored gate dispatches source row1, not the initial zero owner-state byte');
    assert((t.driver.actor.controlWord & 0xff0) === 0 && t.driver.actor.contactP1 === 0 &&
      streamFlags(t).beamFlags6e8 === 0 && streamFlags(t).beamFlags6e9 === 2 && streamFlags(t).beamContactFlags709 === 0,
      'slot1 clears posture and709 while retaining source6e9=2');
    const beam = shots(t)[0]!;
    assert(beam?.beamSource && shots(t).length === 1, 'one input-created emitter');
    assert(t.owner.weaponCells![2] === x && x.cur === x.max - 1 && t.owner.weaponCells![0]!.cur === bAmmo,
      'source slot2 allocation consumes HUD X once, leaving B intact');
    assert(t.allocations.filter(a => a.mode === 1 && a.accepted).length === 1,
      'exactly one consuming resource allocation');
    assert(beam.beamSource.age === 0 && !beam.beamSource.pulse && beam.beamSource.scale === 0,
      'constructor observation has no active damage pulse or growth update');
    const observation = t.battle.observe();
    for (let i = 0; i < 8; i++) assert(t.battle.observe() === observation, 'render observations do not step the emitter');
    const oldBeam = observation.projectiles.find(p => p.uid === beam.uid)!;
    t.tick();
    assert(beam.beamSource.phase === 'active' && Number(beam.beamSource.age) === 1 && oldBeam.beamSource?.age === 0,
      'next Battle update activates once without mutating earlier observation');
    assert(scratch(t).gmBeamTimer560 === 59 && scratch(t).gmBeamCharge54e === 60,
      'holding X spends no extension budget');
    for (let i = 1; i < 60; i++) t.tick();
    assert(scratch(t).gmBeamTimer560 === 0 && scratch(t).gmBeamState6f7 === 2 && t.driver.actor.fbPhaseSlots[0] === 2,
      'sixtieth active callback decrements to zero but does not exit early');
    t.tick();
    assert(scratch(t).gmBeamState6f7 === 0 && Number(t.driver.actor.fbPhaseSlots[0]) === 3,
      'following source callback clears the live owner state and enters recovery');
    assert((t.driver.actor.controlWord & 0xff0) === 0 && t.driver.actor.defaultGroup === 1 &&
      streamFlags(t).beamFlags6e9 === 0 && streamFlags(t).beamContactFlags709 === 0,
      'slot2 recovery clears posture/6e9/709 and restores default group1');
    assert(Number(t.events.length) === 1 && t.allocations.filter(a => a.mode === 1 && a.accepted).length === 1,
      'sustained frames do not spawn extra emitters or consume extra ammo');
    for (let frame = 1; frame < 15; frame++) {
      t.tick(); assert(t.owner.state === 'special' && (t.driver.actor.controlWord & 3) !== 0,
        `authored recovery retains ownership through tick${frame}`);
    }
    t.tick();
    assert(t.owner.state === 'idle' && (t.driver.actor.controlWord & 3) === 0,
      'recovery animation-end wait plus terminal marker releases at tick15');
  }
}
function testInputExtension(): void {
  for (const mode of ['held', 'tap', 'repress'] as const) {
    const t = setup(); launch(t);
    if (mode === 'tap') t.inputs.p1.special = false;
    let extensions = 0;
    for (let i = 1; i <= 60; i++) {
      if (mode === 'repress') { t.inputs.p1.special = i % 2 === 0; if (i % 2 === 0) extensions++; }
      t.tick();
      assert(scratch(t).gmBeamCharge54e === 60 - extensions, `${mode}: only fresh input edges spend extension budget`);
      assert(scratch(t).gmBeamTimer560 === 60 - i + extensions, `${mode}: exact source timer refund`);
      assert(t.events.length === 1, `${mode}: repeated input extends the existing beam instead of queuing another`);
    }
    t.inputs.p1.special = true;
    for (let i = 0; i < 150; i++) t.tick();
    assert(t.events.length === 1 && !t.owner.cooldowns['romSpecialActive'], `${mode}: held input cannot restart after recovery`);
    for (let i = 0; i < 300; i++) t.tick();
    t.release(); t.press(); for (let i = 0; i < RELEASE_FRAME - 1; i++) t.tick();
    assert(Number(t.events.length) === 2, `${mode}: fresh X after refill admits one fresh emitter`);
  }
  const t = setup(); launch(t);
  // Several simultaneous face-button and decoded stick-direction edges count separately.
  // Lock-change controls are excluded by source mask 0xf0f00.
  t.inputs.p1.special = false; t.tick();
  t.inputs.p1.special = true; t.inputs.p1.attack = true; t.inputs.p1.jump = true; t.inputs.p1.hyper = true;
  t.inputs.p1.moveX = 1; t.inputs.p1.moveZ = 1; t.tick();
  assert(scratch(t).gmBeamCharge54e === 54 && scratch(t).gmBeamTimer560 === 64,
    'simultaneous four face-button and two stick-direction rising edges refund six, not one');
  for (let i = 0; i < 100 && scratch(t).gmBeamCharge54e! > 0; i++) {
    const pressed = i % 2 === 1;
    t.inputs.p1.special = pressed; t.inputs.p1.attack = pressed; t.inputs.p1.jump = pressed; t.inputs.p1.hyper = pressed;
    t.inputs.p1.moveX = pressed ? 1 : 0; t.inputs.p1.moveZ = pressed ? 1 : 0; t.tick();
  }
  assert(scratch(t).gmBeamCharge54e === 0, 'repeated real button edges exhaust the sixty-unit refund cap');
  const timer = scratch(t).gmBeamTimer560!;
  t.inputs.p1.special = false; t.tick(); t.inputs.p1.special = true; t.tick();
  assert(scratch(t).gmBeamCharge54e === 0 && scratch(t).gmBeamTimer560 === timer - 2,
    'extra repress cannot refund after budget depletion');
}
function testDenialsAndInterruption(): void {
  for (const mode of ['empty', 'depleted', 'busy', 'windup-hit'] as const) {
    const t = setup();
    if (mode === 'empty') t.owner.weaponCells![1]!.cur = 0;
    if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
    t.press();
    if (mode === 'depleted') { t.owner.weaponCells![1]!.cur = 0; t.owner.weaponCells![1]!.timer = 300; }
    if (mode === 'windup-hit') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
    const hp = t.target.hp;
    for (let i = 0; i < 150; i++) {
      t.tick(); assert(shots(t).length === 0, `${mode}: no transient generic or source projectile`);
    }
    assert(t.events.length === 0 && t.target.hp === hp, `${mode}: denied/interrupted windup cannot create ghost damage`);
    assert(!t.owner.cooldowns['romSpecialActive'], `${mode}: no stuck source ownership`);
    if (mode === 'depleted') {
      for (let i = 0; i < 300; i++) t.tick();
      assert(t.owner.weaponCells![1]!.cur === 1, 'externally depleted windup refills normally');
      t.release(); t.press(); for (let i = 1; i < RELEASE_FRAME; i++) t.tick();
      assert(Number(t.events.length) === 1 && shots(t).some(p => p.beamSource),
        'resource-peek rejection must not permanently mark X impotent after refill');
    }
  }
  const interrupted = setup(); const beam = launch(interrupted);
  interrupted.tick(); interrupted.owner.state = 'hit'; interrupted.owner.stateTime = 0;
  interrupted.owner.cooldowns['hitstun'] = 20;
  interrupted.owner.pos.x += 50; interrupted.owner.rotY = .2;
  interrupted.tick();
  same(beam.beamSource!.origin, beamMuzzle(interrupted.owner.pos, interrupted.owner.rotY, beam.beamSource!.ownerScale),
    'interrupted tail remains attached to the live host owner transform');
  assert(!shots(interrupted).some(p => p.uid === beam.uid && p.beamSource?.phase === 'active'),
    'hit interruption stops the live emitter immediately; a harmless tail may remain');
  for (let i = 0; i < 150; i++) interrupted.tick();
  assert(shots(interrupted).length === 0 && interrupted.events.length === 1,
    'interrupted beam tail terminates and held input never recreates it');

  const death = setup({ ownerReplacement: true }); const old = launch(death);
  death.tick(); death.owner.hp = 0; death.owner.state = 'death'; death.owner.stateTime = STATE.DEATH_DURATION - 1;
  const gone = death.tick();
  assert(!gone.projectiles.some(p => p.uid === old.uid && p.beamSource?.phase === 'active'),
    'owner death ends damaging beam before replacement');
  for (let i = 0; i < STATE.SPAWN_DURATION + 30; i++) death.tick();
  const replacement = death.state.borgs.find(b => b.ownerPlayer === 'p1' && b.uid !== death.owner.uid && b.alive);
  assert(replacement && replacement.borgId === 'pl0104', 'real reserve redeploys Beam Gunner');
  assert(death.state.projectiles.every(p => p.ownerUid !== death.owner.uid), 'old emitter cannot bind replacement actor');
  assert(!replacement.cooldowns['romSpecialActive'], 'replacement does not inherit old source ownership');
  death.inputs.p1.special = false; death.tick(); death.inputs.p1.special = true;
  for (let i = 0; i < RELEASE_FRAME; i++) death.tick();
  assert(death.state.projectiles.some(p => p.ownerUid === replacement.uid && p.beamSource),
    'replacement accepts fresh actual X and creates its own emitter');
}
function testCapturedAim(): void {
  const control = setup({ extraTarget: true }); const normal = launch(control);
  const switched = setup({ extraTarget: true }); assert(switched.other, 'relock fixture has target B');
  switched.press(); switched.inputs.p1.switchLock = true; switched.tick(); switched.inputs.p1.switchLock = false;
  for (let i = 0; i < RELEASE_FRAME - 2; i++) switched.tick();
  const beam = shots(switched)[0]!;
  assert(switched.owner.targetLockState?.activeTargetUid === switched.other.uid, 'actual R input selects B during windup');
  assert(beam.beamSource?.targetUid === switched.target.uid && normal.beamSource?.targetUid === control.target.uid,
    'source emitter retains the admitted A pointer despite newer active lock B');
  same(beam.beamSource.direction, normal.beamSource.direction, 'relock cannot rotate captured-A beam');
  same(beam.pos, normal.pos, 'relock cannot move captured-A muzzle');

  const order = (reverseActors: boolean) => {
    const t = setup({ reverseActors }); t.inputs.p2.moveX = 1; const p = launch(t);
    t.tick();
    assert(p.beamSource, 'actor-order fixture creates a source emitter');
    return { pos: { ...p.pos }, direction: { ...p.beamSource.direction } };
  };
  const first = order(false), reversed = order(true);
  same(first.pos, reversed.pos, 'moving-target muzzle is independent of actor iteration order');
  same(first.direction, reversed.direction, 'moving-target beam direction is independent of actor iteration order');

  const lost = setup({ extraTarget: true }); assert(lost.other, 'captured target loss fixture has B');
  const orphan = launch(lost); lost.target.hp = 0; lost.target.state = 'death'; lost.target.stateTime = 0;
  lost.tick();
  assert(lost.owner.targetLockState?.activeTargetUid === lost.other.uid, 'host reacquires B after A dies');
  assert(orphan.beamSource?.targetUid !== lost.other.uid,
    'live beam never silently rebinds to replacement target B');

  const absent = setup({ targetReplacement: true });
  absent.target.hp = 0; absent.target.state = 'death'; absent.target.stateTime = STATE.DEATH_DURATION - 2;
  const untracked = launch(absent);
  const replacement = absent.state.borgs.find(b => b.ownerPlayer === 'p2' && b.uid !== absent.target.uid && b.alive);
  assert(replacement && absent.owner.targetLockState?.activeTargetUid === replacement.uid,
    'actual reserve becomes active lock during targetless windup');
  assert(untracked.beamSource?.targetUid === null && untracked.aimedTargetUid === null,
    'targetless admission cannot acquire a newly deployed target for its beam');
}
/** Keep target bodies in the declared host capsule and clear reaction gates, so
 * victim knockback/invulnerability cannot conceal duplicate or missing pulses.
 * This deliberately isolates host geometry; it is not exact animated HIT parity. */
function placeVictim(victim: Fixture['target'], pos: Vec3): void {
  victim.pos = { ...pos }; victim.vel = v(0, 0, 0); victim.grounded = false;
  victim.state = 'idle'; victim.stateTime = 0; victim.invincTimer = 0;
  victim.freezeFrames = 0; victim.cooldowns['hitstun'] = 0;
}
function testCollisionAndTail(): void {
  const t = setup({ extraTarget: true }); assert(t.other, 'two targets for a simultaneous pulse');
  const beam = launch(t); assert(beam.beamSource, 'real input-created source beam');
  const ownerHp = t.owner.hp;
  const victims = [t.target, t.other];
  const before = victims.map(b => b.hp);
  const hits = t.battle.observe().telemetry.hitsByTeam[0] ?? 0;
  const damage = t.battle.observe().telemetry.damageByTeam[0] ?? 0;
  const inside = () => victims.forEach((b, i) => placeVictim(b, v(0, beam.pos.y, 4000 + i * 1000)));
  inside(); t.tick();
  assert(victims.every((b, i) => b.hp === before[i]), 'first active update creates only a start-point hit, not an instant full beam');
  const initialPulse = beam.beamSource.pulses[0]!;
  assert(initialPulse.stage === 'init' && initialPulse.hitUids.length === 0, 'fresh pulse starts its own attack identity');
  same(initialPulse.start, initialPulse.end, 'initial pulse is only the source start point');
  const initialRadius = initialPulse.radius;
  const initialEndpoint = { ...beam.beamSource.end };
  inside(); t.tick();
  assert(String(initialPulse.stage) === 'sweep' && initialPulse.radius === initialRadius, 'second pulse update preserves attack identity and initial radius');
  same(initialPulse.end, beam.beamSource.end, 'sweep reads the live parent endpoint, not allocation-time endpoint');
  assert(initialPulse.end.z > initialEndpoint.z + 1000, 'growth fixture distinguishes live endpoint from frozen endpoint');
  assert(Number(initialPulse.hitUids.length) === 2 && new Set(initialPulse.hitUids).size === 2, 'one pulse records both victims once');
  assert(victims.every((b, i) => b.hp < before[i]!), 'second-update pulse sweep connects to both overlapping victims');
  assert(t.owner.hp === ownerHp, 'beam cannot damage its owner');
  assert(t.state.projectiles.includes(beam) && beam.beamSource.pulse, 'contacts do not consume the emitter');
  const observed = t.battle.observe();
  assert((observed.telemetry.hitsByTeam[0] ?? 0) === hits + 2, 'two actual victim connections reach telemetry');
  assert((observed.telemetry.damageByTeam[0] ?? 0) - damage === before.reduce((sum, hp, i) => sum + hp - victims[i]!.hp, 0),
    'reported damage equals actual HP reductions');
  const after = victims.map(b => b.hp);
  inside(); t.tick();
  assert(!beam.beamSource.pulses.includes(initialPulse), 'third object update cleans the old pulse');
  assert(victims.every((b, i) => b.hp < after[i]!), 'fresh next-frame source pulse can hit each victim again');
  assert((t.battle.observe().telemetry.hitsByTeam[0] ?? 0) === hits + 4, 'exactly one connection per victim per pulse');

  // Move targets clear and let the real owner timer end the sustained phase.
  t.target.pos = v(10000, 0, -10000); t.other.pos = v(-10000, 0, -10000);
  for (let i = 0; i < 100 && scratch(t).gmBeamState6f7 !== 0; i++) t.tick();
  assert(beam.beamSource.phase === 'tail' && !beam.beamSource.pulse, 'live owner state zero begins a harmless tail');
  const tail = t.battle.observe().projectiles.find(p => p.uid === beam.uid)!;
  for (let i = 1; i <= 10; i++) {
    inside(); const hp = victims.map(b => b.hp); t.tick();
    assert(victims.every((b, j) => b.hp === hp[j]), `tail update${i} cannot damage overlapping targets`);
    if (i < 10) assert(t.state.projectiles.includes(beam), `full-grown tail survives update${i}`);
  }
  assert(!t.state.projectiles.includes(beam) && beam.despawnReason === 'expired', 'tenth shrink update terminates the tail');
  assert(tail.beamSource?.tailAge === 0 && tail.beamSource.scale === 3, 'old tail observation stays immutable');
}
function testPulseIdentityAcrossStages(): void {
  const t = setup({ extraTarget: true }); assert(t.other, 'pulse identity fixture has a second victim');
  const beam = launch(t); assert(beam.beamSource, 'input-created source emitter');
  placeVictim(t.other, v(beam.pos.x, beam.pos.y, beam.pos.z + 2));
  const hp = t.other.hp; t.tick();
  const first = beam.beamSource.pulses[0]!;
  assert(t.other.hp < hp && first.hitUids.includes(t.other.uid), 'initial start-point stage can damage its local victim');
  const after = t.other.hp;
  placeVictim(t.other, v(0, beam.pos.y, 4000)); t.tick();
  assert(first.stage === 'sweep' && first.hitUids.filter(uid => uid === t.other!.uid).length === 1,
    'sweep shares the start-point attack identity instead of renewing it');
  assert(t.other.hp === after, 'victim already hit at start cannot be hit again by the same pulse sweep');
}
function testTerrainAndIndependentPulse(): void {
  // Audited parent/pulse path has no generic terrain-clipping/consumption call.
  // This does not claim every original global terrain pass is reconstructed.
  const wall = setup({ wallZ: 1000 }); const beam = launch(wall);
  placeVictim(wall.target, v(0, beam.pos.y, 2000)); const hp = wall.target.hp;
  wall.tick(); placeVictim(wall.target, v(0, beam.pos.y, 2000)); const observed = wall.tick();
  assert(wall.target.hp < hp && wall.state.projectiles.includes(beam),
    'bounded source pulse path reaches target beyond wall without generic bolt consumption');
  assert(beam.beamSource!.end.z > 1000 && observed.projectileDespawns.every(p => p.uid !== beam.uid),
    'wall does not truncate the source endpoint or report a terrain despawn');

  const death = setup({ ownerReplacement: true }); const child = launch(death);
  placeVictim(death.target, v(0, child.pos.y, 2000)); death.tick();
  assert(child.beamSource?.scale === .2 && child.beamSource.pulses.length === 1,
    'early invalidation fixture has one pending start-point pulse at first ramp frame');
  const pulse = child.beamSource.pulses[0]!, before = death.target.hp;
  death.owner.hp = 0; death.owner.state = 'death'; death.owner.stateTime = 0;
  placeVictim(death.target, v(0, child.pos.y, 2000)); death.tick();
  assert(death.target.hp < before && pulse.stage === 'sweep',
    'independent pending pulse still completes its sweep when early owner death removes beam art');
  assert(Number(child.beamSource.scale) === 0 && !child.beamSource.pulse,
    'pending child does not keep dead owner visual growing or create new pulses');
  const after = death.target.hp;
  placeVictim(death.target, v(0, child.pos.y, 2000)); death.tick();
  assert(death.target.hp === after && !death.state.projectiles.includes(child),
    'finished orphan pulse cleans up without duplicate damage or new emitter');
}
function testMixedHitsAndMissingOwner(): void {
  // This is a host-integration regression, not original same-frame HP parity.
  // The source-collision pass currently never fills its disabled HP-defer set;
  // these real Battle cases cannot prove sensitivity to that dormant flag.
  const run = (mode: 'beam' | 'generic' | 'mixed' | 'reversed') => {
    const t = setup(), beam = launch(t); t.tick();
    placeVictim(t.target, v(0, beam.pos.y, 4000));
    const generic: Projectile = { ...beam, uid: `mixed-control-${mode}`, pos: { ...t.target.pos },
      vel: v(0, 0, 0), life: 10, hitRadius: 20, romScale: [1, 1, 1] };
    delete generic.beamSource;
    t.state.projectiles = mode === 'beam' ? [beam] : mode === 'generic' ? [generic] :
      mode === 'mixed' ? [generic, beam] : [beam, generic];
    const hp = t.target.hp, hits = t.battle.observe().telemetry.hitsByTeam[0] ?? 0;
    const observation = t.tick();
    return { damage: hp - t.target.hp, hits: (observation.telemetry.hitsByTeam[0] ?? 0) - hits,
      genericConsumed: observation.projectileDespawns.some(p => p.uid === generic.uid && p.reason === 'hit-target') };
  };
  const beam = run('beam'), generic = run('generic'), mixed = run('mixed'), reversed = run('reversed');
  assert(beam.damage > 0 && beam.hits === 1 && generic.damage > 0 && generic.hits === 1 && generic.genericConsumed,
    'each isolated beam/generic hit reaches the victim once; generic retains ordinary consumption');
  for (const result of [mixed, reversed]) {
    assert(result.hits === 2 && result.damage > Math.max(beam.damage, generic.damage) && result.genericConsumed,
      'mixed beam and generic shots both connect in either ordering without changing generic consumption');
  }

  // Remove the owner only from the actual projectile-update lookup, preserving
  // the input-created pending child and its source damage record.
  const orphan = setup(), pending = launch(orphan); orphan.tick();
  assert(pending.beamSource && pending.damageRecord?.index === 9 && pending.damageRecord.hpDamage === 3,
    'missing-owner fixture retains source family record9 base damage3');
  const segment = pending.beamSource;
  placeVictim(orphan.target, v((segment.start.x + segment.end.x) / 2,
    (segment.start.y + segment.end.y) / 2, (segment.start.z + segment.end.z) / 2));
  const profile = buildProfile(stats.find(s => s.id === orphan.target.borgId)!);
  const reference = { ...orphan.target, romDriver: null, pos: { ...orphan.target.pos },
    vel: { ...orphan.target.vel }, cooldowns: { ...orphan.target.cooldowns } };
  const expected = applyHit(reference, profile, 3, 1, pending.beamSource.direction,
    pending.beamSource.pulses[0]!.start, false, pending.damageRecord);
  const before = orphan.target.hp;
  const survivors = stepProjectiles([pending], [orphan.target], new Map([[orphan.target.uid, profile]]),
    new Map([[orphan.target.uid, orphan.target]]));
  assert(expected > 1 && before - orphan.target.hp === expected,
    `owner-missing pulse uses record base3, not raw1: expected${expected}, actual${before - orphan.target.hp}, pulse${JSON.stringify(pending.beamSource.pulses)}`);
  assert(survivors.includes(pending) && pending.beamSource.pulses[0]?.stage === 'sweep',
    'orphan pending pulse survives parent teardown long enough to finish its sweep');
}
function testAmmoBoundaries(): void {
  const t = setup(), cell = t.owner.weaponCells![1]!;
  assert(t.owner.weaponCells![2] === cell && cell.max === 1 && cell.cur === 1 && cell.timer === 0,
    'decoded source cell2 aliases one-round HUD X with no full-magazine debt');
  assert(cell.refillType === 0 && cell.refillParam === 300, 'ISO source row has baseline refill300');
  cell.cur = 0; cell.timer = 300;
  for (let i = 1; i < 300; i++) {
    t.tick(); assert(cell.cur === 0 && cell.timer === 300 - i, `one aliased ammo tick at frame${i}`);
  }
  t.tick(); assert(Number(cell.cur) === 1 && Number(cell.timer) === 0, 'three-hundredth frame refills exactly once');
  cell.cur = 0; cell.timer = 300; t.owner.sourceAmmoRefillPauseMask = 4;
  t.tick(); assert(Number(cell.timer) === 300, 'source slot2 pause bit4 pauses HUD X alias');
  t.owner.sourceAmmoRefillPauseMask = 2; t.tick();
  assert(Number(cell.timer) === 299, 'HUD index1 pause bit2 does not pause source slot2');
}
function testStrictAdapterScope(): void {
  const t = setup(); launch(t);
  assert(spawnBeamSource(t.owner, t.driver.actor, 0x800e19a8, 0)?.length === 0,
    'initial owner-state byte0 is not a valid row for this bounded X adapter');
  assert(spawnBeamSource(t.owner, t.driver.actor, 0x800e19a8, 2)?.length === 0,
    'other spawner rows cannot silently enter the dedicated row1 lane');
  assert(spawnBeamSource(t.owner, t.driver.actor, 0x80084600, 1) === null,
    'another family spawner is outside Beam adapter');
  const oldAction = t.driver.actor.actionIndex; t.driver.actor.actionIndex = 0;
  assert(spawnBeamSource(t.owner, t.driver.actor, 0x800e19a8, 1) === null,
    'B action is outside the dedicated X adapter');
  t.driver.actor.actionIndex = oldAction;
  assert(spawnBeamSource({ ...t.owner, borgId: 'pl0102' }, t.driver.actor, 0x800e19a8, 1) === null,
    'unrelated borg cannot inherit Beam behavior');
}
function testOtherFamilies(): void {
  for (const id of ['pl0100', 'pl0101', 'pl0102', 'pl0108', 'pl0615']) {
    const t = setup({ id }); t.press();
    for (let i = 0; i < 80; i++) {
      const observed = t.tick();
      assert(observed.projectiles.every(p => !p.beamSource), `${id}: unrelated family never receives Beam source state`);
    }
    assert(t.events.every(e => e.address !== 0x800e19a8), `${id}: no Beam family dispatch`);
  }
}

export function runBeamBattleSelfTest(): void {
  testAdmissionAndTiming();
  testInputExtension();
  testDenialsAndInterruption();
  testCapturedAim();
  testCollisionAndTail();
  testPulseIdentityAcrossStages();
  testTerrainAndIndependentPulse();
  testMixedHitsAndMissingOwner();
  testAmmoBoundaries();
  testStrictAdapterScope();
  testOtherFamilies();
  console.log('Beam Gunner source-X Battle integration: passed (static muzzle and host collision geometry)');
}
