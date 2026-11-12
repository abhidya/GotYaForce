/** Real Battle input regressions for Double Ninja pl0003 ordinary source action2.
 * Projectile timing/data are source-backed. Natural contacts deliberately exercise
 * the host sweep and static-bind muzzle adapters, not original joint/HIT geometry.
 * The true charged release remains an explicitly tested legacy fallback: these
 * cases do not restore clone arming, clone rendering, or actual-input row2.
 * Death/empty-ammo/late-depletion and receiver relocation are labeled host
 * lifecycle/geometry fixture adjuncts; no source contact or callback is injected.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { STATE } from './constants.js';
import { getNinjaXState } from './ninjaX.js';
import type { Vec3 } from './rom/actor.js';
import type { BorgStats } from './stats.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import data from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (data as { borgs: BorgStats[] }).borgs;
const ids = ['pl0003'] as const;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[doubleNinjaXBattle] ${message}`);
}
function near(actual: number, expected: number, message: string, tolerance = 1e-6): void {
  assert(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
}
function same(actual: Vec3, expected: Vec3, message: string): void {
  for (const axis of ['x', 'y', 'z'] as const) near(actual[axis], expected[axis], `${message} ${axis}`);
}
function stage(wallZ?: number): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
    [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
  ];
  if (wallZ !== undefined) vertices.push([v(-2000, -1000, wallZ), v(2000, -1000, wallZ), v(0, 3000, wallZ)]);
  return { triangles: vertices.map((points, index) => ({ index, vertices: points,
    normal: index === 2 ? v(0, 0, -1) : v(0, 1, 0), planeD: 0, layerIndex: 0, marker: 0xcccccccc,
    bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
  })) };
}
interface SetupOptions {
  id?: string;
  distance?: number;
  extraTarget?: boolean;
  ownerReplacement?: boolean;
  targetReplacement?: boolean;
  wallZ?: number;
  reverseActors?: boolean;
}
function setup(options: SetupOptions = {}) {
  const id = options.id ?? 'pl0003';
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: stage(options.wallZ),
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
  target.pos = v(0, 10, options.distance ?? 2000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  if (other) { other.pos = v(3000, 10, 4000); other.vel = v(0, 0, 0); }
  // Feed relocation through the ordinary own-history sampler, not a special-entry reset.
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  if (options.reverseActors) state.borgs.reverse();
  let elapsed = 0;
  const events: { frame: number; address: number; row: number; phase: number; contact: number;
    dash: number; hSpeed: number; yVel: number; pos: Vec3; yaw: number; modelScale: number }[] = [];
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const cues: number[] = [];
  battle.onRomCue = cue => cues.push(cue);
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row, phase: actor.fbPhaseSlots[0]!, contact: actor.contactP0,
      dash: actor.dashStrength1d0f, hSpeed: actor.hSpeed, yVel: actor.yVel, pos: { ...actor.pos },
      yaw: actor.heading * Math.PI * 2 / 65536, modelScale: actor.modelScale });
    spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted });
    return accepted;
  };
  const seen = new Map<string, Projectile>();
  const tick = () => {
    elapsed++;
    const observation = battle.step(1 / 60, inputs);
    for (const child of state.projectiles) if (child.ownerUid === owner.uid) seen.set(child.uid, child);
    return observation;
  };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, seen, tick, press, release,
    get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function shots(t: Fixture): Projectile[] {
  return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid);
}
function primary(t: Fixture): Projectile {
  const child = shots(t).filter(p => p.ninjaSource?.kind === 'primary').at(-1);
  assert(child?.ninjaSource?.kind === 'primary', 'real X creates dedicated Ninja source primary');
  return child;
}
function waitRelease(t: Fixture, previous = 0): Projectile {
  for (let i = 0; i < 100 && Number(t.events.length) === previous; i++) t.tick();
  assert(Number(t.events.length) === previous + 1, 'one source callback from actual input');
  return primary(t);
}
function waitIdle(t: Fixture): void {
  for (let i = 0; i < 180 && (t.owner.state === 'special' || t.owner.cooldowns['romSpecialActive']); i++) t.tick();
  assert(t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'], 'source recovery releases Battle ownership');
}
function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false;
  for (let i = 0; i < 3; i++) t.tick();
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'actual jump establishes airborne admission');
}

function testAdmissionAndRelease(): void {
  for (const id of ids) for (const air of [false, true]) {
    const t = setup({ id }); if (air) jump(t);
    const cell = t.owner.weaponCells![1]!, bAmmo = t.owner.weaponCells![0]!.cur;
    assert(t.owner.weaponCells![2] === cell && cell.cur === 5 && cell.max === 5,
      `${id}: source cell2 aliases HUD X with decoded five-round capacity`);
    assert(cell.refillType === 0 && cell.refillParam === 300 && cell.timer === 0,
      'decoded X refill is type0/300 with no debt while full');
    const before = { ...t.owner.pos }, admittedAt = t.frame + 1;
    t.press();
    assert(t.owner.command?.type === 2 && t.owner.command.actionIndex === 2 && t.owner.command.exact,
      `${id}: actual X selects exact source action2`);
    assert(t.owner.command.recordAddress === (air ? '0x8033b148' : '0x8033b108') &&
      t.driver.actor.variantIndex === (air ? 4 : 0) && t.driver.actor.fbCue === (air ? 45 : 44),
      `${id}: actual ground/air command and cue survive admission`);
    assert(getNinjaXState(t.driver.actor)?.stream?.slot === (air ? 1 : 0), 'ground/air source g4 stream');
    if (!air) same(t.owner.pos, before, 'stationary X does not teleport away by target distance');
    assert(Number(t.events.length) === 0 && Number(t.allocations.length) === 0 && cell.cur === 5 && shots(t).length === 0,
      'admission has no premature source allocation or generic child');
    for (let tick = 1; tick < 21; tick++) {
      t.tick();
      assert(Number(t.events.length) === 0 && Number(t.allocations.length) === 0 && shots(t).length === 0 && cell.cur === 5,
        `source frame14 plus source blend6 gate remains closed at relative tick${tick}`);
    }
    t.tick(); const child = primary(t);
    assert(Number(t.events.length) === 1 && t.events[0]!.frame === admittedAt + 21,
      'source frame14, blend6+1 duration and pre-advance wait release at relative tick21');
    assert(child.life === 599 && child.romShotKind === 1 && child.damageRecord?.index === 1 &&
      child.sourceHitCollisionFlags === 1 && child.damageRecord.hpDamage === 10,
      'constructor takes its one source flight step and binds HIT1/record1/flags1');
    assert(child.life > 5, 'ordinary Double Ninja cannot regress to the generic release payload');
    near(child.hitRadius, 10 * t.driver.actor.modelScale * t.driver.actor.sizeScale,
      'source HIT1 radius10 is independent of doubled draw scale');
    assert(child.flightVisual?.bankTexId !== 14, 'owner-local weapon model14 cannot masquerade as global efct14');
    assert(t.events[0]!.address === 0x8007db5c && t.events[0]!.row === 1,
      'Double Ninja ordinary X selects source row1, never clone row2 or primary B variants');
    assert(Number(t.allocations.length) === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 &&
      t.allocations[0]!.mode === 1 && t.allocations[0]!.accepted && Number(cell.cur) === 4,
      'one accepted source cell2 allocation consumes exactly one X');
    assert(getNinjaXState(t.driver.actor)?.callbackCount === 1 && getNinjaXState(t.driver.actor)?.fireCount === 1,
      'one source phase transition invokes one callback and one accepted throw');
    const event = t.events[0]!;
    assert(child.ninjaSource?.kind === 'primary', 'row1 flight carries source primary state');
    // Fresh ARC1271 static joint11 + local[55,0,0], not Normal's bind and
    // not animated-joint parity. Compare its pre-flight point independently.
    const c = Math.cos(event.yaw), sin = Math.sin(event.yaw), scale = event.modelScale;
    same(child.ninjaSource.flight.previousPos, {
      x: Math.fround(event.pos.x + (116 * c + 0.00000251267192652449 * sin) * scale),
      y: Math.fround(event.pos.y + 118 * scale),
      z: Math.fround(event.pos.z + (-116 * sin + 0.00000251267192652449 * c) * scale),
    }, 'Double-specific static muzzle initializes source flight before its first step');
    assert(getNinjaXState(t.driver.actor)?.doubleClone?.arm7c8 === 0,
      'real ordinary admission remains unarmed; fixture-only clone seam is not a live producer');
    assert(event.contact === 1 && event.phase === 2 && event.dash === (air ? 32 : 0),
      'authored P0/part1 gate advances phase once, independently of target contact');
    assert(event.hSpeed === (air ? 10 : 0) && event.yVel === (air ? 15 : 0),
      'only airborne source dash32 seeds backflip10/15; grounded throw has no recoil');
    assert(t.owner.weaponCells![0]!.cur === bAmmo, 'X allocation preserves B ammo');
    assert(shots(t).length === 1 && !child.poweredSource && !child.gatlingSource,
      'one dedicated Ninja child without generic, Powered or Gatling payload');
    const snapshot = t.battle.observe(), previousLife = child.life, previousPosition = { ...child.pos };
    for (let i = 0; i < 8; i++) assert(t.battle.observe() === snapshot, 'observing cannot advance flight or callbacks');
    t.tick();
    assert(child.life === previousLife - 1 && snapshot.projectiles.find(p => p.uid === child.uid)?.life === previousLife,
      'one later Battle tick advances once while old observation stays detached');
    assert(Math.hypot(child.pos.x - previousPosition.x, child.pos.y - previousPosition.y, child.pos.z - previousPosition.z) > 0,
      'source shuriken travels after release');
    const source = getNinjaXState(t.driver.actor)!;
    const terminalTick = air ? 56 : 57;
    while (t.frame < admittedAt + terminalTick - 1) {
      t.tick(); assert(t.owner.state === 'special', 'source main/recovery clocks retain action ownership before terminal');
    }
    t.tick();
    assert(t.frame === admittedAt + terminalTick && t.owner.state !== 'special' && source.stream?.completed,
      `${id}/${air ? 'air' : 'ground'}: source recovery completes at relative tick${terminalTick}`);
    assert(source.exitKind === 'stream-end', 'fixture reaches source terminal rather than a generic timeout');
    waitIdle(t);
    while (t.frame < admittedAt + 89) t.tick();
    assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1,
      'held ordinary X does not repeat across source recovery');
    t.release(); t.press(); waitRelease(t, 1);
    assert(Number(t.allocations.length) === 2, 'fresh repress produces exactly one new source allocation');
  }
}

/** 686f0 warmup10 + source rate1 bank120: the 129/130 edge is real input,
 * never a fabricated command, charge field, cloned owner, or phase override. */
function testShortHoldsAndChargedBoundary(): void {
  for (const held of [1, 8, 30, 90, 129, 130]) {
    const t = setup(); t.press();
    for (let i = 1; i < held; i++) t.tick();
    const cell = t.owner.weaponCells![1]!, before = cell.cur, bAmmo = t.owner.weaponCells![0]!.cur;
    const callbacks = t.events.length;
    if (held >= 129) assert(t.owner.doubleNinjaXInput?.warmup === 10 &&
      t.owner.doubleNinjaXInput.charge === held - 10,
      `${held} real held frames sample source charge even while ordinary action owns the actor`);
    t.release();
    if (held < 130) {
      assert(t.owner.command?.type !== 5, `${held}-frame hold cannot promote a short release to source type5`);
      assert(cell.cur === before, `${held}-frame short release cannot spend a second X charge`);
    } else {
      assert(t.owner.command?.exact && t.owner.command.type === 5 && t.owner.command.actionIndex === 3 &&
        t.owner.command.recordAddress === '0x8033b17c' && t.owner.command.subtype === 5 && t.owner.state === 'special',
        `130 held frames retain exact grounded type5/action3 command as an explicitly legacy fallback: ${JSON.stringify({command:t.owner.command,state:t.owner.state,input:t.owner.doubleNinjaXInput,cell,grounded:t.owner.grounded})}`);
      assert(cell.cur === before - 1 && cell.timer === 0 && t.owner.weaponCells![2] === cell,
        'true-ready legacy release spends one additional aliased X unit without inventing partial refill debt');
      assert(t.owner.weaponCells![0]!.cur === bAmmo && t.events.length === callbacks,
        'legacy charge release preserves B ammo and does not manufacture a Ninja source callback');
      assert(!getNinjaXState(t.driver.actor), 'legacy action3 cannot masquerade as restored ordinary action2');
    }
    for (let i = 0; i < 130; i++) t.tick();
    assert(Number(t.events.length) === 1 && t.events[0]!.row === 1 && Number(t.allocations.length) === 1,
      `${held}-frame hold produces exactly one ordinary row1 source callback and source allocation`);
    assert([...t.seen.values()].filter(p => p.ninjaSource?.kind === 'primary').length === 1 &&
      [...t.seen.values()].every(p => p.ninjaSource?.kind !== 'primary' || p.ninjaSource.flight.row === 1),
      'real ordinary or charged inputs cannot create clone row2, a duplicate primary, or another Ninja row');
    const generic = [...t.seen.values()].filter(p => !p.ninjaSource);
    assert(generic.length === (held === 130 ? 1 : 0),
      `${held}-frame input: only the genuine charge threshold retains one explicitly generic legacy payload`);
  }
  const air = setup(); air.press();
  for (let i = 1; i < 129; i++) air.tick();
  air.inputs.p1.jump = true; air.tick(); air.inputs.p1.jump = false;
  assert(!air.owner.grounded && air.owner.pos.y > 10, 'actual jump establishes airborne charged-release admission');
  air.release();
  assert(air.owner.command?.exact && air.owner.command.type === 5 && air.owner.command.actionIndex === 3 &&
    air.owner.command.variantIndex === 3 && air.owner.command.recordAddress === '0x8033b178' &&
    air.owner.command.subtype === 4 && air.owner.state === 'special',
    'actual airborne ready release keeps its distinct type5/action3/variant3 legacy command');
  for (let i = 0; i < 130; i++) air.tick();
  assert(air.events.length === 1 && air.events[0]!.row === 1 &&
    [...air.seen.values()].filter(p => !p.ninjaSource).length === 1 &&
    [...air.seen.values()].every(p => p.ninjaSource?.kind !== 'primary' || p.ninjaSource.flight.row === 1),
    'airborne charged fallback produces no actual-input clone or duplicate ordinary shuriken');

  // Host ammo fixture adjunct: an already-empty magazine is close to refill.
  // Actual held input must not replay a rejected press when that refill arrives.
  const empty = setup(), cell = empty.owner.weaponCells![1]!;
  cell.cur = 0; cell.timer = 60; empty.press();
  for (let i = 1; i < 90; i++) empty.tick();
  assert(Number(cell.cur) === 5 && empty.events.length === 0 && empty.allocations.length === 0,
    'source refill crossed under a short held empty press without replaying ordinary X');
  empty.release(); empty.press(); waitRelease(empty);
  assert(Number(cell.cur) === 4, 'fresh edge after held-empty refill admits ordinary source X');
}

function testIndependentButtonLanes(): void {
  const b = setup(); b.inputs.p1.attack = true;
  for (let i = 0; i < 30; i++) b.tick();
  assert(!getNinjaXState(b.driver.actor) && [...b.seen.values()].every(p => !p.ninjaSource),
    'Double Ninja B never enters ordinary X action or source child lane');
  b.inputs.p1.attack = false; for (let i = 0; i < 90; i++) b.tick();
  b.press(); waitRelease(b);
  assert(b.events[0]!.row === 1, 'ordinary X still works after independent actual B input');
}

function testSourceRecoveryInput(): void {
  for (const id of ids) for (const air of [false, true]) {
    const t = setup({ id }); if (air) jump(t);
    const admittedAt = t.frame + 1; t.press(); waitRelease(t);
    const source = getNinjaXState(t.driver.actor)!;
    t.inputs.p1.moveX = 1;
    const inputGate = air ? 47 : 41;
    while (t.frame < admittedAt + inputGate - 1) {
      t.tick(); assert(t.owner.state === 'special', 'held movement cannot cancel before authored P0negative gate');
    }
    t.tick();
    assert(t.owner.state !== 'special' && source.exitKind === 'input' && !source.stream?.completed,
      `${id}/${air ? 'air' : 'ground'}: actual stick input exits at source relative tick${inputGate}`);
    assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1,
      'source recovery cancel cannot repeat the shuriken release or debit');
  }
}

function testInputDenialsAndInterruption(): void {
  for (const id of ids) {
    const tap = setup({ id }); tap.press(); tap.inputs.p1.special = false; waitRelease(tap);
    for (let i = 0; i < 120; i++) tap.tick();
    assert(Number(tap.events.length) === 1 && Number(tap.allocations.length) === 1, 'short tap completes once without a held button');
    for (const mode of ['empty', 'depleted', 'interrupt', 'busy'] as const) {
      const t = setup({ id }), cell = t.owner.weaponCells![1]!;
      if (mode === 'empty') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      t.press();
      if (mode === 'depleted') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'interrupt') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      const hp = t.target.hp;
      for (let i = 0; i < 120; i++) {
        t.tick(); assert(shots(t).length === 0, `${id}/${mode}: no transient generic or delayed source payload`);
      }
      assert(Number(t.events.length) === 0 && t.target.hp === hp, `${id}/${mode}: no ghost callback or hidden damage`);
      assert(mode === 'depleted' ? Number(t.allocations.length) === 1 && !t.allocations[0]!.accepted : Number(t.allocations.length) === 0,
        `${id}/${mode}: only admitted late depletion attempts source allocation`);
      t.release(); assert(Number(t.events.length) === 0, 'release cannot resurrect denied or interrupted special');
    }
    const busy = setup({ id }); busy.press(); busy.release(); busy.press();
    for (let i = 0; i < 90; i++) busy.tick();
    assert(Number(busy.events.length) === 1 && Number(busy.allocations.length) === 1, 'busy re-press is discarded, not queued');
    busy.release(); busy.press(); waitRelease(busy, 1);
    assert(Number(busy.events.length) === 2, 'later fresh press works after discarded busy re-press');
  }
}

function testMagazineAndRefill(): void {
  for (const id of ids) {
    const t = setup({ id }), cell = t.owner.weaponCells![1]!;
    for (let round = 0; round < 5; round++) {
      t.press(); waitRelease(t, round);
      assert(cell.cur === 4 - round && Number(t.allocations.length) === round + 1,
        `${id}: round${round + 1} spends exactly one of five source X charges`);
      if (round < 4) assert(cell.timer === 0, 'partly full type0 magazine has no refill debt');
      t.inputs.p1.special = false; waitIdle(t);
    }
    assert(cell.cur === 0 && cell.timer > 0, 'fifth throw starts source empty-magazine refill');
    t.press();
    for (let i = 0; i < 20; i++) t.tick();
    t.release();
    for (let i = 0; i < 320; i++) t.tick();
    assert(Number(t.events.length) === 5 && Number(t.allocations.length) === 5, 'empty press and short release are not buffered across refill');
    assert(Number(cell.cur) === 5 && Number(cell.timer) === 0, 'source type0 refill restores full five-charge magazine');
    t.release(); t.press(); waitRelease(t, 5);
    assert(Number(cell.cur) === 4, 'fresh press after refill consumes one charge normally');

    const paused = setup({ id }), x = paused.owner.weaponCells![1]!;
    x.cur = 0; x.timer = x.refillParam; paused.owner.sourceAmmoRefillPauseMask = 4;
    paused.tick(); assert(x.timer === 300, 'source slot2 pause bit freezes aliased HUD X refill');
    paused.owner.sourceAmmoRefillPauseMask = 2; paused.tick();
    assert(Number(x.timer) === 299, 'HUD slot1 pause bit cannot pause source slot2');
    paused.owner.sourceAmmoRefillPauseMask = 0;
    for (let i = 0; i < 298; i++) paused.tick();
    assert(x.cur === 0 && Number(x.timer) === 1, 'cell alias is ticked exactly once through penultimate refill frame');
    paused.tick(); assert(Number(x.cur) === 5 && Number(x.timer) === 0, 'exact source refill boundary restores five charges');
  }
}

function testCapturedTargetAndWindupContact(): void {
  for (const id of ids) {
    const t = setup({ id, extraTarget: true }); assert(t.other, 'lock-switch fixture has two targets');
    t.press();
    assert(getNinjaXState(t.driver.actor)?.targetUid === t.target.uid, 'actual admission captures source target');
    t.inputs.p1.switchLock = true; t.tick(); t.inputs.p1.switchLock = false;
    assert(t.owner.targetLockState?.activeTargetUid === t.other.uid, 'actual R input switches current lock');
    t.inputs.p2.moveX = 1;
    const child = waitRelease(t);
    const savedPoint = getNinjaXState(t.driver.actor)?.targetPoint;
    assert(savedPoint && savedPoint.x !== 0 && child.ninjaSource?.kind === 'primary' &&
      child.ninjaSource.flight.initialAimPoint?.x === Math.fround(savedPoint.x),
      'actual target movement refreshes captured aim through windup before constructor copy');
    assert(child.aimedTargetUid === t.target.uid && getNinjaXState(t.driver.actor)?.targetUid === t.target.uid,
      'throw remains aimed at admitted target rather than replacement UI lock');
    const lost = setup({ id, extraTarget: true, targetReplacement: true }); lost.press();
    lost.target.hp = 0; lost.target.state = 'death'; lost.target.stateTime = STATE.DEATH_DURATION - 1;
    const orphan = waitRelease(lost);
    assert(orphan.aimedTargetUid === null, 'target death in windup cannot redirect throw to a replacement');
    assert(lost.state.borgs.some(b => b.ownerPlayer === 'p2' && b.uid !== lost.target.uid),
      'target-loss fixture actually deployed the replacement');

    const close = setup({ id, distance: 20 }), hp = close.target.hp;
    close.press();
    for (let i = 0; i < 20; i++) {
      close.tick();
      assert(Number(close.events.length) === 0 && close.target.hp === hp,
        'nearby actor cannot synthesize release or body damage before authored source gate');
    }
    close.owner.state = 'hit'; close.owner.stateTime = 0; close.owner.cooldowns['hitstun'] = 20;
    for (let i = 0; i < 100; i++) close.tick();
    assert(Number(close.events.length) === 0 && close.target.hp === hp && shots(close).length === 0,
      'interrupt immediately before the release leaves no delayed hit or child');
  }
}

function testNaturalContacts(): void {
  for (const id of ids) for (const reverseActors of [false, true]) {
    const t = setup({ id, distance: 1500, reverseActors });
    const hp = t.target.hp, hits = t.battle.observe().telemetry.hitsByTeam[0] ?? 0;
    t.press(); const child = waitRelease(t);
    assert(t.target.hp === hp, 'distant victim has no speculative body damage before shuriken contact');
    let contacted = false;
    for (let i = 0; i < 150 && !contacted; i++) {
      t.tick(); contacted = child.hitConfirmedThisFrame === true;
    }
    assert(contacted && t.target.hp < hp, `${id}: actual-input source shuriken naturally reaches victim`);
    assert(child.ninjaSource?.kind === 'primary' && child.ninjaSource.contactPending &&
      child.ninjaSource.flight.phase === 'active', 'accepted host contact queues the next source dispatch');
    assert((t.battle.observe().telemetry.hitsByTeam[0] ?? 0) === hits + 1, 'direct source contact reaches hit telemetry once');
    t.tick();
    assert(String(child.ninjaSource.flight.phase) === 'retiring' && child.ninjaSource.flight.reason === 'contact' &&
      !child.ninjaSource.flight.hitActive, 'next source dispatch consumes prior contact and disables primary HIT');
    const impacts = shots(t).filter(p => p.ninjaSource?.kind === 'impact');
    assert(impacts.length === 1 && impacts[0]!.uid !== child.uid,
      'one accepted primary contact creates one independently identified source impact');
    const impact = impacts[0]!;
    assert(impact.romShotKind === 3 && impact.damageRecord?.hpDamage === 20,
      'source impact0 uses common HIT3/global HP20 rather than family shuriken HP10');
    assert(impact.ninjaSource?.kind === 'impact', 'source impact state is present');
    near(impact.hitRadius, 310 * impact.ninjaSource.scale, 'impact collision follows dynamic source scale');
    for (let i = 0; i < 120; i++) t.tick();
    assert(shots(t).length === 0, 'contact primary and impact finish without ghost children');
  }
  for (const id of ids) {
    const t = setup({ id, wallZ: 500 }), hp = t.target.hp;
    t.press(); const child = waitRelease(t);
    let blocked = false;
    for (let i = 0; i < 100 && !blocked; i++) {
      t.tick(); blocked = child.ninjaSource?.kind === 'primary' && child.ninjaSource.flight.reason === 'terrain';
    }
    assert(blocked && t.target.hp === hp, `${id}: host wall contact terminates the source child before target`);
    for (let i = 0; i < 120; i++) t.tick();
    assert(t.target.hp === hp, 'wall effect does not leak damage through terrain');
  }
}

function testLaunchedChildSurvivesActionInterruption(): void {
  for (const id of ids) {
    const t = setup({ id, distance: 4000 }), hp = t.target.hp;
    t.press(); const child = waitRelease(t), life = child.life;
    t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20;
    t.tick();
    assert(shots(t).some(p => p.uid === child.uid) && child.life === life - 1,
      'owner action interruption cannot erase an already independent source child');
    let contacted = false;
    for (let i = 0; i < 180 && !contacted; i++) {
      t.tick(); contacted = child.hitConfirmedThisFrame === true;
    }
    assert(contacted && t.target.hp < hp, 'launched source shuriken still reaches victim after owner hit interruption');
    assert(Number(t.events.length) === 1 && Number(t.allocations.length) === 1,
      'interrupted owner never adds another source callback or ammo debit');
  }
}

function testImpactOutlivesOwner(): void {
  for (const id of ids) {
    const t = setup({ id, distance: 1500, ownerReplacement: true, extraTarget: true });
    assert(t.other, 'impact owner-death fixture has a fresh receiver');
    const receiver = t.other, untouchedHp = receiver.hp;
    t.press(); const child = waitRelease(t);
    for (let i = 0; i < 150 && !child.hitConfirmedThisFrame; i++) t.tick();
    assert(child.hitConfirmedThisFrame, 'impact owner-death fixture reaches a real victim contact');
    t.tick();
    const impact = shots(t).find(p => p.ninjaSource?.kind === 'impact');
    assert(impact?.ninjaSource?.kind === 'impact', 'source contact allocated independent impact before owner death');
    const life = impact.life;
    t.owner.hp = 0; t.owner.state = 'death'; t.owner.stateTime = STATE.DEATH_DURATION - 1;
    t.tick();
    assert(shots(t).some(p => p.uid === impact.uid) && impact.life === life - 1,
      'independent HIT3 impact keeps its source lifecycle after owner death');
    assert(!t.owner.alive && !t.state.borgs.some(b => b.uid === t.owner.uid),
      'original owner has completed death and left the active actor list before receiver contact');
    assert(receiver.hp === untouchedHp && !impact.ninjaSource.hitUids.includes(receiver.uid),
      'fresh receiver has not already been damaged or consumed by this impact identity');
    // Explicit host geometry/immunity adjunct: move an untouched receiver into
    // the already input-created impact only AFTER its original owner is dead.
    // No collision callback, source contact byte or damage function is injected.
    receiver.pos = { ...impact.pos }; receiver.vel = v(0, 0, 0);
    receiver.grounded = false; receiver.invincTimer = 0;
    t.tick();
    assert(receiver.hp < untouchedHp && impact.hitConfirmedThisFrame &&
      impact.ninjaSource.hitUids.includes(receiver.uid),
      'original independent HIT3 impact accepts a fresh contact and damages after owner death');
    for (let i = 0; i < 120; i++) t.tick();
    assert(!shots(t).some(p => p.uid === impact.uid), 'orphaned impact expires normally without surviving indefinitely');
  }
}

function testOwnerDeathAndFamilyIsolation(): void {
  for (const id of ids) {
    const windup = setup({ id, ownerReplacement: true }); windup.press();
    windup.owner.hp = 0; windup.owner.state = 'death'; windup.owner.stateTime = 0;
    for (let i = 0; i < STATE.DEATH_DURATION + STATE.SPAWN_DURATION + 30; i++) windup.tick();
    assert(Number(windup.events.length) === 0 && Number(windup.allocations.length) === 0 && shots(windup).length === 0,
      'death during windup prevents source callback, debit and ghost child');
    assert(windup.state.borgs.some(b => b.ownerPlayer === 'p1' && b.uid !== windup.owner.uid),
      'windup death reaches ordinary replacement lifecycle');
    const t = setup({ id, ownerReplacement: true }); t.press(); const child = waitRelease(t);
    t.owner.hp = 0; t.owner.state = 'death'; t.owner.stateTime = STATE.DEATH_DURATION - 1;
    const observation = t.tick();
    assert(child.ninjaSource?.kind === 'primary' && child.ninjaSource.flight.phase === 'released' &&
      !child.ninjaSource.flight.hitActive && !child.ninjaSource.flight.visible,
      'owner guard immediately disables HIT and hides the released source child');
    const observed = observation.projectiles.find(p => p.uid === child.uid);
    assert(!observed || (observed.ninjaSource?.kind === 'primary' &&
      !observed.ninjaSource.flight.visible && !observed.ninjaSource.flight.hitActive),
      'renderer observation cannot expose released primary as visible or HIT-active');
    const freed = t.tick();
    assert(freed.projectileDespawns.some(p => p.uid === child.uid && p.reason === 'owner-dead'),
      'following source dispatch frees owner-dead child before replacement can inherit it');
    assert(shots(t).length === 0, 'owner cleanup cannot turn flight into a damaging impact');
  }
  for (const id of ['pl0001', 'pl0002', 'pl000b', 'pl0102', 'pl0101', 'pl0005', 'pl0008', 'pl0615']) {
    const t = setup({ id }); t.press();
    assert(t.owner.command?.type === 2, `${id}: control executes a real X command`);
    if (['pl0001', 'pl0002', 'pl000b', 'pl0101', 'pl0102', 'pl0615'].includes(id)) {
      assert(t.owner.state === 'special', `${id}: control starts its existing family action`);
    }
    for (let i = 0; i < 120; i++) {
      t.tick();
      assert(shots(t).every(p => !p.ninjaSource), `${id}: another family cannot enter dedicated Ninja source projectile lane`);
      assert(!getNinjaXState(t.driver.actor), `${id}: another family cannot enter dedicated Ninja action clock`);
    }
  }
  for (const id of ids) {
    const t = setup({ id }); t.inputs.p1.attack = true;
    for (let i = 0; i < 120; i++) {
      t.tick(); assert(shots(t).every(p => !p.ninjaSource), `${id}: B route remains separate from X source lane`);
    }
    assert(!getNinjaXState(t.driver.actor), 'primary attack does not create Ninja X state');
  }
}

export function runDoubleNinjaXBattleSelfTest(): void {
  testAdmissionAndRelease();
  testShortHoldsAndChargedBoundary();
  testIndependentButtonLanes();
  testSourceRecoveryInput();
  testInputDenialsAndInterruption();
  testMagazineAndRefill();
  testCapturedTargetAndWindupContact();
  testNaturalContacts();
  testLaunchedChildSurvivesActionInterruption();
  testImpactOutlivesOwner();
  testOwnerDeathAndFamilyIsolation();
  console.log('[doubleNinjaXBattle] PASS: actual Double Ninja ordinary X admission, source payload, input edges, explicit legacy charge boundary, contacts and lifecycle');
}
