/** Actual Battle X-input coverage for Arrow Ninja and Shijima.
 * Source release is observed through the live callback, not manually dispatched.
 * Static-bind muzzle and host collision geometry are explicit approximations.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { runArrowStreamSelfTest } from './arrowStream.selftest.js';
import { tierSizeScale } from './timescale.js';
import { arrowCaptureMass, advanceArrowSource, applyArrowTetherCorrections, applyPendingArrowCorrection, createArrowTether } from './arrowProjectile.js';
import { STATE } from './constants.js';
import { RomDriverBridge } from './bridge.js';
import type { Vec3 } from './rom/actor.js';
import type { BorgStats } from './stats.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const ids = ['pl0002', 'pl000b'] as const;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[arrowBattle] ${message}`);
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
  const id = options.id ?? 'pl0002';
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

function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false;
  for (let i = 0; i < 3; i++) t.tick();
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'real jump establishes airborne admission');
}
function waitRelease(t: Fixture): Projectile[] {
  for (let i = 0; i < 100 && t.events.length === 0; i++) t.tick();
  assert(t.events.length === 1, 'one source callback reached from real input');
  assert(shots(t).length === 1, 'one dedicated child at source release');
  return shots(t);
}
function waitIdle(t: Fixture): void {
  for (let i = 0; i < 180 && (t.owner.state === 'special' || t.owner.cooldowns['romSpecialActive']); i++) t.tick();
  assert(t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'], 'authored recovery releases ownership');
}
function testAdmissionAndAmmo(): void {
  for (const id of ids) for (const air of [false, true]) {
    const t = setup({ id }); if (air) jump(t);
    const cell = t.owner.weaponCells![1]!, bAmmo = t.owner.weaponCells![0]!.cur;
    assert(t.owner.weaponCells![2] === cell, `${id}: source cell2 aliases HUD X`);
    assert(cell.cur === 8 && cell.max === 8 && cell.refillParam === 300 && cell.timer === 0,
      `${id}: full decoded X magazine has no refill debt`);
    const before = { ...t.owner.pos }, admissionFrame = t.frame + 1; t.press();
    assert(t.owner.command?.type === 2 && t.owner.command.actionIndex === 2 && t.owner.command.exact,
      `${id}: X selects exact source action2`);
    assert(t.owner.command.recordAddress === (air ? '0x8030e180' : '0x8030e140') &&
      t.driver.actor.variantIndex === (air ? 4 : 0), 'ground/air exact command records survive admission');
    near(t.owner.pos.x, before.x, 'stationary horizontal history does not teleport X');
    near(t.owner.pos.z, before.z, 'stationary horizontal history does not teleport away from a distant lock');
    if (!air) near(t.owner.pos.y, before.y, 'ground admission preserves height');
    assert(t.events.length === 0 && shots(t).length === 0 && cell.cur === 8,
      'admission cannot allocate, spawn, or consume early');
    assert((t.driver.actor.controlWord & 0x40) === (air ? 0x40 : 0), 'admission carries real ground/air source bit');
    assert(t.driver.actor.fbCue === (air ? 45 : 44), 'ground/air source cue44/45');
    const fired = waitRelease(t);
    assert(t.events[0]!.frame === admissionFrame + 25, 'blend4 plus authored frame21 gate releases at relative tick25');
    if (air) assert(t.driver.actor.hSpeed === 10 && t.driver.actor.yVel === 4 && t.driver.actor.gravityCoeff === -1,
      'air gate seeds source recoil speed10/rise4/gravity-1');

    assert(t.events[0]!.address === 0x800a2684 && t.events[0]!.row === (id === 'pl0002' ? 0 : 1),
      'borg-specific source child variant, never primary B kind');
    assert(t.allocations.length === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.mode === 1 &&
      t.allocations[0]!.accepted && Number(cell.cur) === 7 && t.owner.weaponCells![0]!.cur === bAmmo,
      'one source allocation spends one X and preserves B');
    assert(fired[0]!.life > 5, 'source child is not Arrow row0 generic six-frame fallback');
    const snapshot = t.battle.observe();
    for (let i = 0; i < 5; i++) assert(t.battle.observe() === snapshot, 'observation cannot step source child');
    if (!air) {
      while (t.frame < admissionFrame + 48) { t.tick(); assert(t.owner.state === 'special', 'ground recovery waits for source terminal'); }
      t.tick(); assert(t.owner.state === 'idle' && t.frame === admissionFrame + 49,
        'ground source animation45/blend4 completes at relative tick49');
    }
    waitIdle(t); for (let i = 0; i < 320; i++) t.tick();
    assert(Number(t.events.length) === 1 && t.allocations.length === 1, 'held X never repeats across recovery/refill');
    t.release(); t.press();
    for (let i = 0; i < 100 && t.events.length < 2; i++) t.tick();
    assert(Number(t.events.length) === 2 && Number(t.allocations.length) === 2, 'fresh repress reaches exactly one new source release');
  }
}
function testDenialsAndInterruption(): void {
  for (const id of ids) {
    const tap = setup({ id }); tap.press(); tap.inputs.p1.special = false; waitRelease(tap);
    for (const mode of ['empty', 'depleted', 'interrupt', 'busy'] as const) {
      const t = setup({ id }), cell = t.owner.weaponCells![1]!;
      if (mode === 'empty') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      t.press();
      if (mode === 'depleted') { cell.cur = 0; cell.timer = cell.refillParam; }
      if (mode === 'interrupt') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
      const hp = t.target.hp;
      for (let i = 0; i < 120; i++) {
        t.tick(); assert(shots(t).length === 0, `${id}/${mode}: no transient generic fallback or source child`);
      }
      assert(t.events.length === 0 && t.target.hp === hp, `${id}/${mode}: no ghost release or damage`);
      assert(mode === 'depleted' ? t.allocations.length === 1 && !t.allocations[0]!.accepted : t.allocations.length === 0,
        `${id}/${mode}: only late depletion reaches a failed allocation`);
    }
    const t = setup({ id }); t.press(); t.release(); t.press();
    for (let i = 0; i < 160; i++) t.tick();
    assert(t.events.length === 1, 'fresh press while occupied is discarded, not queued');
  }
}
function testMagazineAndRefill(): void {
  for (const id of ids) {
    const t = setup({ id }), cell = t.owner.weaponCells![1]!;
    for (let round = 0; round < 8; round++) {
      t.press();
      for (let i = 0; i < 100 && t.events.length === round; i++) t.tick();
      assert(t.events.length === round + 1 && cell.cur === 7 - round,
        `${id}: round${round + 1} spends exactly one of eight charges`);
      if (round < 7) assert(cell.timer === 0, 'magazine has no refill debt until exhausted');
      t.inputs.p1.special = false; waitIdle(t);
    }
    const before = t.events.length; t.press();
    for (let i = 0; i < 80; i++) t.tick();
    assert(t.events.length === before && cell.cur === 0, 'ninth press denies exhausted source magazine');
    for (let i = 0; i < 320; i++) t.tick();
    assert(t.events.length === before, 'held denied press is not buffered across refill');
    assert(Number(cell.cur) === 8 && Number(cell.timer) === 0, 'source magazine restores at completed refill');
    t.release(); t.press();
    for (let i = 0; i < 100 && t.events.length === before; i++) t.tick();
    assert(t.events.length === before + 1 && Number(cell.cur) === 7, 'fresh press after refill fires normally');
  }
}
function testCapturedTargetAndTracking(): void {
  for (const id of ids) {
    for (const range of [5499.99, 5500, 5500.01]) {
      const r = setup({ id }); r.target.pos = v(0, 10, range);
      for (let i = 0; i < 4; i++) r.tick();
      r.press(); const [child] = waitRelease(r);
      assert(child?.arrowSource?.kind === 'arrow', 'range fixture produces source arrow');
      assert(r.owner.arrowAttack?.trackingEnabled === (range <= 5500) &&
        child.arrowSource.targetUid === (range <= 5500 ? r.target.uid : null),
        'actual captured-target range5500 is inclusive without explicit tracking override');
    }
    const t = setup({ id, extraTarget: true }); assert(t.other, 'target-switch fixture has enemy B');
    t.owner.sourceArrowTrackingEnabled = true; t.press();
    t.inputs.p1.switchLock = true; t.tick(); t.inputs.p1.switchLock = false;
    assert(t.owner.targetLockState?.activeTargetUid === t.other.uid, 'actual R changes current lock');
    const [arrow] = waitRelease(t);
    assert(arrow?.arrowSource?.kind === 'arrow' && arrow.aimedTargetUid === t.target.uid &&
      arrow.arrowSource.targetUid === t.target.uid, 'captured attack target survives R switch');
    const byUid = new Map(t.state.borgs.map(b => [b.uid, b]));
    t.target.pos = v(1000, arrow.pos.y, arrow.pos.z + 2000);
    const initial = { ...arrow.vel }; advanceArrowSource(arrow, byUid);
    same(arrow.vel, initial, 'first flight tick does not pass two-frame homing gate');
    advanceArrowSource(arrow, byUid);
    const dot = initial.x * arrow.vel.x + initial.y * arrow.vel.y + initial.z * arrow.vel.z;
    near(Math.acos(Math.max(-1, Math.min(1, dot / (55 * 55)))) * 180 / Math.PI, 3,
      'second update turns exactly source three-degree cap', 1e-5);
    t.target.hp = 0; advanceArrowSource(arrow, byUid);
    assert(arrow.arrowSource.targetUid === null, 'lost captured target clears, never substitutes live current lock');
    const absent = setup({ id, extraTarget: true }); absent.press(); absent.target.hp = 0;
    const [orphan] = waitRelease(absent);
    assert(orphan?.aimedTargetUid === null, 'target loss during windup cannot bind replacement target');
  }
}
function testNaturalVictimContact(): void {
  for (const id of ids) {
    const t = setup({ id }); t.target.pos = v(0, 10, 1500);
    for (let i = 0; i < 4; i++) t.tick();
    const hp = t.target.hp, hits = t.battle.observe().telemetry.hitsByTeam[0] ?? 0;
    t.press(); const [arrow] = waitRelease(t); assert(arrow, 'natural collision starts with actual input');
    let contact = false;
    for (let i = 0; i < 120 && !contact; i++) {
      const observation = t.tick();
      contact = observation.projectileDespawns.some(p => p.uid === arrow.uid && p.reason === 'hit-target');
    }
    assert(contact && t.target.hp < hp, `${id}: input-created arrow naturally reaches victim damage`);
    assert((t.battle.observe().telemetry.hitsByTeam[0] ?? 0) > hits, 'natural source hit reaches telemetry');
    const tether = shots(t).find(p => p.arrowSource?.kind === 'tether');
    assert(tether?.arrowSource?.kind === 'tether' && tether.arrowSource.targetUid === t.target.uid,
      'natural victim hit creates exactly the victim-bound source tether');
    assert(shots(t).filter(p => p.arrowSource?.kind === 'tether').length === 1, 'one collision creates one tether');
    let life = tether.life;
    t.inputs.p2.moveX = 1; t.tick();
    assert(t.target.sourceArrowMash749 === 1 && tether.life === life - 4, 'fresh stick edge costs baseline1 plus3');
    life = tether.life; t.tick();
    assert(Number(t.target.sourceArrowMash749) === 0 && tether.life === life - 1, 'held stick is not a repeated or cumulative mash');
    life = tether.life; t.inputs.p2.jump = true; t.inputs.p2.attack = true; t.tick();
    assert(Number(t.target.sourceArrowMash749) === 2 && tether.life === life - 7, 'fresh A+B edges count separately');
    life = tether.life; t.tick();
    assert(Number(t.target.sourceArrowMash749) === 0 && tether.life === life - 1, 'held face buttons do not accelerate decay');

  }
}
function testFlightAndTetherLifecycle(): void {
  for (const id of ids) {
    const t = setup({ id }); t.press(); const [arrow] = waitRelease(t);
    assert(arrow?.arrowSource?.kind === 'arrow', 'actual input child uses dedicated source flight');
    assert(arrow.arrowSource.row === (id === 'pl0002' ? 0 : 1) && arrow.life === 600,
      'source child variant and constructor lifetime survive without same-frame flight');
    near(Math.hypot(arrow.vel.x, arrow.vel.y, arrow.vel.z), 55, 'source flight speed');
    const pos = { ...arrow.pos }, old = t.battle.observe(); t.tick();
    assert(Number(arrow.life) === 599 && old.projectiles.find(p => p.uid === arrow.uid)?.life === 600,
      'first later tick advances life once and leaves prior observation detached');
    near(Math.hypot(arrow.pos.x - pos.x, arrow.pos.y - pos.y, arrow.pos.z - pos.z), 55, 'one source flight step');
    const expiry = { ...arrow, pos: { ...arrow.pos }, vel: { ...arrow.vel }, arrowSource: { ...arrow.arrowSource }, life: 2 };
    const byUid = new Map(t.state.borgs.map(b => [b.uid, b]));
    assert(advanceArrowSource(expiry, byUid).length === 1 && expiry.life === 1, 'flight survives penultimate update');
    assert(advanceArrowSource(expiry, byUid).length === 0 && expiry.despawnReason === 'expired', 'flight expires at exact source boundary');

    // The same input-created child crosses the post-hit constructor seam. Host
    // collision reachability is exercised separately below, not claimed here.
    near(arrowCaptureMass(t.target), 200 * tierSizeScale(t.target), 'normal borg uses recovered mass200 with source scale');
    const savedDelta = t.target.sizeTierDelta; t.target.sizeTierDelta = -14;
    near(tierSizeScale(t.target), 0.08, 'shrink selects decoded source size0.08');
    near(arrowCaptureMass(t.target), 16, 'normal descriptor mass200 scales to16 when shrunk');
    const savedId = t.target.borgId; t.target.borgId = 'pl0e00';
    near(arrowCaptureMass(t.target), 50000, 'giant threshold descriptor remains unscaled');
    assert(createArrowTether(arrow, t.target) === null, 'decoded giant descriptor cannot be captured');
    t.target.borgId = savedId;
    if (savedDelta === undefined) delete t.target.sizeTierDelta; else t.target.sizeTierDelta = savedDelta;
    t.target.sourceArrowMass204 = 50000;
    assert(createArrowTether(arrow, t.target) === null, 'mass50000 excludes tether construction');
    t.target.sourceArrowMass204 = 49999;
    t.target.targetEligibility83 = 1;
    assert(createArrowTether(arrow, t.target) === null, 'nonzero eligibility byte excludes tether construction');
    t.target.targetEligibility83 = 0;
    const tether = createArrowTether(arrow, t.target);
    assert(tether?.arrowSource?.kind === 'tether' && tether.life === 1199, 'contact constructor seeds life1200 then performs immediate source update');
    const anchor = { ...tether.arrowSource.anchor };
    t.target.pos = v(anchor.x + 900, anchor.y, anchor.z);
    advanceArrowSource(tether, byUid); applyArrowTetherCorrections([tether], byUid);
    near(t.target.pos.x - anchor.x, 900, 'correction queues until the next victim actor update');
    applyPendingArrowCorrection(t.target, 10);
    near(t.target.pos.x - anchor.x, 600, 'tether correction returns target to source length');
    same(tether.arrowSource.anchor, anchor, 'target movement cannot move fixed anchor');
    assert(Number(tether.life) === 1198, 'ordinary tether tick costs one life');
    t.target.sourceArrowMash749 = 1; advanceArrowSource(tether, byUid);
    assert(Number(tether.life) === 1194, 'explicit signed749 value1 costs four life');
    t.target.sourceArrowMash749 = 0; tether.arrowSource.life = 1;
    assert(advanceArrowSource(tether, byUid).length === 0 && tether.despawnReason === 'expired', 'tether expiry is exact');
    for (const mode of ['owner', 'victim', 'burst', 'blocked'] as const) {
      const c = setup({ id }); c.press(); const [shot] = waitRelease(c); assert(shot, 'lifecycle fixture has child');
      const bound = createArrowTether(shot, c.target); assert(bound, 'lifecycle fixture has tether');
      const live = new Map(c.state.borgs.map(b => [b.uid, b]));
      if (mode === 'owner') c.owner.hp = 0;
      if (mode === 'victim') c.target.hp = 0;
      if (mode === 'burst') c.target.burstPaired = true;
      if (mode === 'blocked') c.target.sourceArrowTetherBlocked = true;
      assert(advanceArrowSource(bound, live).length === 0, `${mode}: tether terminates without retained correction`);
    }
    const dead = setup({ id, ownerReplacement: true }); dead.press(); const [child] = waitRelease(dead); assert(child, 'death fixture has live child');
    dead.owner.hp = 0; dead.owner.state = 'death'; dead.owner.stateTime = STATE.DEATH_DURATION - 1;
    const observed = dead.tick();
    assert(observed.projectileDespawns.some(p => p.uid === child.uid && p.reason === 'owner-dead'),
      'real owner death removes source child before replacement can inherit it');
  }
}
function testOtherFamilyIsolation(): void {
  for (const id of ['pl0100', 'pl0101', 'pl0102', 'pl0104', 'pl0615']) {
    const t = setup({ id }); t.press(); for (let i = 0; i < 100; i++) t.tick();
    assert(t.events.every(event => event.address !== 0x800a2684), `${id}: no Arrow source dispatch`);
  }
}
export function runArrowBattleSelfTest(): void {
  runArrowStreamSelfTest();
  testAdmissionAndAmmo();
  testDenialsAndInterruption();
  testMagazineAndRefill();
  testFlightAndTetherLifecycle();
  testNaturalVictimContact();
  testCapturedTargetAndTracking();
  testOtherFamilyIsolation();
  console.log('Arrow Ninja/Shijima source-X Battle integration: passed');
}
