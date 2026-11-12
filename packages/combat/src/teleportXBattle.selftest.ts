/** Actual-input Teleport Ninja ordinary X regressions.
 * Oracle: chunk_0038.c FUN_80146dcc/zz_0146ed8_/FUN_80146f6c/FUN_80147094,
 * source type2 command records, and zz_00686f0_ charged-release arbitration.
 * Arena/body overlap, target anchors and bound-model scale remain host seams.
 * No command, source phase/timer, damage callback or successful contact is injected.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { SHOT, STATE } from './constants.js';
import type { RomActor, Vec3 } from './rom/actor.js';
import type { BorgStats } from './stats.js';
import { getTeleportXState } from './teleportX.js';
import { emptyInput, type StageCollision } from './types.js';
import data from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (data as { borgs: BorgStats[] }).borgs;
const f = Math.fround;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[teleportXBattle] ${message}`);
}
function near(actual: number, expected: number, message: string, tolerance = 1e-4): void {
  assert(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
}
function same(actual: Vec3, expected: Vec3, message: string): void {
  for (const axis of ['x', 'y', 'z'] as const) near(actual[axis], expected[axis], `${message} ${axis}`);
}
function floor(): StageCollision {
  const vertices: [Vec3, Vec3, Vec3][] = [
    [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
    [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
  ];
  return { triangles: vertices.map((points, index) => ({ index, vertices: points,
    normal: v(0, 1, 0), planeD: 0, layerIndex: 0, marker: 0xcccccccc,
    bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
  })) };
}
function setup(options: { id?: string; distance?: number; replacement?: boolean; enemyId?: string } = {}) {
  const id = options.id ?? 'pl0005';
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floor(), forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: options.replacement ? [id, id] : [id] },
    { team: 1, ownerPlayer: 'p2', borgIds: [options.enemyId ?? 'pl0615'] },
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find(b => b.ownerPlayer === 'p1')!;
  const target = state.borgs.find(b => b.ownerPlayer === 'p2')!;
  assert(owner.romDriver instanceof RomDriverBridge, `${id}: real family bridge`);
  const driver = owner.romDriver;
  owner.pos = v(0, 10, 0); owner.vel = v(0, 0, 0); owner.rotY = 0; owner.grounded = true;
  target.pos = v(0, 10, options.distance ?? 2000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  let elapsed = 0;
  const entries: { frame: number; action: number; variant: number; pos: Vec3; older: Vec3 }[] = [];
  const root = driver.actor.rootAction!;
  driver.actor.rootAction = (actor: RomActor) => {
    if (actor.fbPhaseSlots[0] === 0) entries.push({ frame: elapsed, action: actor.actionIndex,
      variant: actor.variantIndex, pos: { ...actor.pos }, older: { ...actor.targetCache5e8 } });
    root(actor);
  };
  const events: { frame: number; address: number; row: number }[] = [];
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row }); spawn(actor, address, row);
  };
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted }); return accepted;
  };
  const cues: number[] = []; battle.onRomCue = cue => cues.push(cue);
  const tick = () => { elapsed++; return battle.step(1 / 60, inputs); };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, driver, inputs, entries, events, allocations, cues,
    tick, press, release, get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function ticks(t: Fixture, count: number): void { for (let i = 0; i < count; i++) t.tick(); }
function shots(t: Fixture) { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }
function source(t: Fixture) {
  const result = getTeleportXState(t.driver.actor);
  assert(result, 'actual ordinary X enters the dedicated source phase machine'); return result;
}
function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false; ticks(t, 3);
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'actual jump establishes air admission');
}
function idle(t: Fixture): void {
  for (let i = 0; i < 120 && (t.owner.state === 'special' || t.owner.cooldowns['romSpecialActive']); i++) t.tick();
  assert(t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'], 'ordinary source recovery releases Battle ownership');
}
function noPayload(t: Fixture, label: string): void {
  assert(t.events.length === 0 && shots(t).length === 0, `${label}: actor-only teleport has neither fake146ed8 child nor generic payload`);
}

function testActualAdmissionAndClocks(): void {
  for (const air of [false, true]) {
    const t = setup(); if (air) jump(t);
    const before = { ...t.owner.pos }, admittedAt = t.frame + 1, bAmmo = t.owner.weaponCells![0]!.cur;
    t.press(); source(t);
    assert(t.owner.command?.exact && t.owner.command.type === 2 && t.owner.command.actionIndex === 2 &&
      t.owner.command.recordAddress === (air ? '0x8033e9c8' : '0x8033e9b8') &&
      t.driver.actor.variantIndex === (air ? 4 : 0), 'real ground/air X selects its ordinary action2 record on press');
    assert(t.owner.state === 'special' && t.driver.actor.fbPhaseSlots[0] === 1 && t.driver.actor.handlerTimer === 3,
      'admission runs phase0 and phase1 in one call, leaving setup timer3');
    assert(t.allocations.length === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 &&
      t.allocations[0]!.mode === 1 && t.allocations[0]!.accepted, 'admission requests exactly one consuming source cell2 allocation');
    assert(t.owner.weaponCells![0]!.cur === bAmmo, 'ordinary X preserves B ammunition');
    if (!air) same(t.owner.pos, before, 'stationary X cannot invent target-distance movement');
    for (let relative = 1; relative <= 21; relative++) {
      t.inputs.p1.special = false; t.tick();
      if (relative < 3) assert(t.driver.actor.fbPhaseSlots[0] === 1 && t.driver.actor.handlerTimer === 3 - relative,
        `setup includes admission; relative tick${relative}`);
      else if (relative < 19) assert(Number(t.driver.actor.fbPhaseSlots[0]) === 2 && t.driver.actor.handlerTimer === 19 - relative,
        `sixteen-update travel clock at relative tick${relative}`);
      else if (relative < 21) assert(Number(t.driver.actor.fbPhaseSlots[0]) === 3 && t.driver.actor.handlerTimer === 21 - relative,
        `two-update recovery clock at relative tick${relative}`);
      if (relative === 19 || relative === 20) {
        const recovery = source(t).stream;
        assert(recovery?.slot === (air ? 13 : 0) && recovery.frame === 0 && recovery.blendTotal === 3,
          'verified recovery uses ground0/air13 with mode1 blend2+1, staying on authored frame0');
        assert(t.owner.sourceAnimSample?.frame === 0 && t.driver.actor.contactP0 === 0 &&
          t.driver.actor.dashStrength1d0f === 0 && t.driver.actor.faceGate1d10 === 0,
          'recovery publishes source animation frame and authored reset writes');
      }
      if (relative < 21) assert(t.owner.state === 'special', 'no generic timeout or early ownership release');
      noPayload(t, `relative tick${relative}`);
    }
    assert(t.frame === admittedAt + 21 && t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'],
      'source 4+16+2 sequence completes after22 total dispatches including admission');
    assert(!t.owner.sourceAnimSample, 'terminal recovery clears the source animation sample');
    assert(t.cues.filter(cue => cue === 0xf2).length === 2, 'source plays one disappearance and one return cue');
    ticks(t, 100); noPayload(t, 'short release and later idle');
    assert(t.allocations.length === 1, 'short release cannot masquerade as a charged action or spend again');
  }
}

function testOwnMotionDestinationAndTravel(): void {
  for (const air of [false, true]) {
    const t = setup();
    t.inputs.p1.moveX = 1; ticks(t, 12); if (air) jump(t);
    const before = { ...t.owner.pos }; t.press();
    const s = source(t), entry = t.entries.find(e => e.action === 2)!;
    assert(entry && entry.pos.x !== entry.older.x, 'actual locomotion supplies a nonzero own-history delta');
    const motion = v(f(entry.pos.x - entry.older.x), f(entry.pos.y - entry.older.y), f(entry.pos.z - entry.older.z));
    const destination = v(f(entry.pos.x + f(50 * motion.x)), f(entry.pos.y + f(50 * motion.y)), f(entry.pos.z + f(50 * motion.z)));
    same(s.destination9c, destination, 'source9c is position plus50 times own previous motion');
    near(t.owner.pos.x, f(entry.pos.x + motion.x), 'same-call setup carries one unscaled motion step');
    assert(Math.abs(t.owner.pos.x - before.x) < Math.abs(destination.x - before.x), 'admission is not an immediate teleport to9c');
    t.inputs.p1.moveX = 0; t.inputs.p1.special = false;
    for (let i = 0; i < 3; i++) t.tick();
    near(t.owner.pos.x, f(entry.pos.x + 4 * motion.x), 'four setup dispatches preserve unscaled motion');
    for (let i = 0; i < 16; i++) {
      const previous = t.owner.pos.x;
      t.tick();
      // zz_0046588_ independently scales9c and current position before adding.
      near(t.owner.pos.x, f(f(destination.x * f(.1)) + f(previous * f(1 - f(.1)))), `travel lerp${i + 1}`);
      same(s.destination9c, destination, 'destination remains captured while own history advances');
      noPayload(t, 'moving teleport');
    }
    assert(t.owner.pos.x > before.x && t.owner.pos.x < destination.x, 'source16-step lerp moves substantially without snapping to destination');
    ticks(t, 2); idle(t);
  }
}

function testTapHoldAndRepeat(): void {
  for (const hold of [1, 8, 30, 90]) {
    const t = setup(); t.press(); ticks(t, hold - 1); t.release(); ticks(t, 100);
    assert(t.entries.filter(e => e.action === 2).length === 1 && t.allocations.length === 1,
      `${hold}-frame hold admits only its fresh ordinary press`);
    noPayload(t, `${hold}-frame subthreshold release`);
  }
  const t = setup(); t.press(); t.release(); t.press(); ticks(t, 90);
  assert(t.allocations.length === 1, 'busy re-press is discarded rather than queued after recovery');
  t.release(); t.press(); source(t);
  assert(Number(t.allocations.length) === 2, 'fresh eligible re-press starts a second ordinary teleport');
}

function testAmmoAndIncrementalRefill(): void {
  const t = setup(), x = t.owner.weaponCells![1]!;
  assert(t.owner.weaponCells![2] === x && x.max === 2 && x.cur === 2 &&
    x.refillType === 1 && x.refillParam === 180 && x.timer === 0,
    'source Xcell2 aliases HUD X with decoded max2/type1/180 and no initial debt');
  t.press();
  assert(Number(x.cur) === 1 && Number(x.timer) === 180, 'first ordinary press spends one X and adds180 debt immediately');
  t.release();
  assert(Number(x.cur) === 1 && Number(x.timer) === 179, 'aliased source cell refills once per Battle tick, never fractionally');
  idle(t);
  const before = x.timer; t.press();
  assert(Number(x.cur) === 0 && x.timer === before - 1 + 180,
    'second actual press consumes second X and adds180 to existing refill debt');
  t.release(); idle(t); t.press();
  assert(t.allocations.length === 2 && !getTeleportXState(t.driver.actor), 'empty press is denied before source allocation');
  t.release();
  while (x.timer > 200) t.tick();
  t.press(); // A short denied hold crosses the first refill without becoming a charge.
  while (x.timer > 180) t.tick();
  assert(Number(x.timer) === 180 && Number(x.cur) === 0, 'source type1 integer grant remains zero at debt180 boundary');
  t.tick();
  assert(Number(x.timer) === 179 && Number(x.cur) === 1 && t.allocations.length === 2,
    'crossing below180 restores one charge without replaying held empty press');
  t.release();
  while (x.timer > 0) t.tick();
  assert(Number(x.cur) === 2 && x.timer === 0 && t.allocations.length === 2,
    'full refill restores second charge without replaying held empty press');
  t.press(); source(t);
  assert(Number(t.allocations.length) === 3 && Number(x.cur) === 1, 'fresh press after source refill starts normally');

  const paused = setup(), cell = paused.owner.weaponCells![1]!;
  paused.press(); paused.owner.sourceAmmoRefillPauseMask = 4; paused.tick();
  assert(cell.timer === 180, 'source slot2 pause bit freezes the aliased X debt');
  paused.owner.sourceAmmoRefillPauseMask = 2; paused.tick();
  assert(Number(cell.timer) === 179, 'HUD slot1 bit does not pause source cell2');
}

function testDistinctChargedRelease(): void {
  for (const held of [129, 130]) {
    const t = setup(); t.press(); ticks(t, held - 1);
    assert(t.allocations.length === 1 && !getTeleportXState(t.driver.actor),
      'holding X through ordinary recovery never repeats action2');
    const cell = t.owner.weaponCells![1]!, ammoBefore = cell.cur, debtBefore = cell.timer;
    const bAmmoBefore = t.owner.weaponCells![0]!.cur;
    t.release();
    if (held === 129) {
      assert(t.owner.command?.type !== 5 && t.owner.state !== 'special' && t.owner.weaponCells![1]!.cur === ammoBefore,
        'ten-update ramp plus119 bank is below genuine source charge threshold120');
    } else {
      assert(t.owner.command?.exact && t.owner.command.type === 5 && t.owner.command.actionIndex === 3 &&
        t.owner.state === 'special', 'ten-update ramp plus120 bank retains distinct type5/action3 legacy release');
      assert(!getTeleportXState(t.driver.actor), 'genuine charged release is not relabeled as ordinary teleport');
      // The charged payload remains legacy. This protects only its retained
      // one-X-bullet policy now that ordinary X binds source type1 ammo debt.
      assert(ammoBefore === 1 && cell.cur === ammoBefore - 1 && cell.timer === debtBefore - 1 + 180 &&
        t.owner.weaponCells![2] === cell && t.owner.weaponCells![0]!.cur === bAmmoBefore,
        'fully charged legacy release spends one additional aliased source X and adds180 debt, preserving B ammo');
      const afterReleaseDebt = cell.timer;
      t.tick();
      assert(cell.cur === 0 && cell.timer === afterReleaseDebt - 1,
        'next source refill update decrements debt once without refunding the charged-release debit');
    }
    assert(t.entries.filter(e => e.action === 2).length === 1 && t.events.length === 0,
      'charge arbitration cannot manufacture another ordinary source dispatch or fake child');
  }
}

function testDefenseWindowAndVisibility(): void {
  const clock = setup(); clock.press();
  for (let relative = 0; relative <= 21; relative++) {
    if (relative > 0) clock.tick();
    assert(Boolean(clock.owner.sourceDefenseDisabled) === (relative < 21),
      `source272 bit2 protects setup/travel/recovery until terminal relative tick${relative}`);
    assert(Boolean(clock.owner.sourceHidden) === (relative >= 4 && relative < 19),
      `source82 hides only actual travel dispatches, relative tick${relative}`);
    const observation = clock.battle.observe();
    const observed = observation.actors.find(actor => actor.uid === clock.owner.uid)!;
    assert(Boolean(observed.sourceHidden) === Boolean(clock.owner.sourceHidden) &&
      Boolean(observed.sourceDefenseDisabled) === Boolean(clock.owner.sourceDefenseDisabled),
      'public Battle snapshot publishes the current source visibility and receiver gates');
    const before = JSON.stringify({ pos: clock.owner.pos, phase: clock.driver.actor.fbPhaseSlots[0],
      timer: clock.driver.actor.handlerTimer, ammo: clock.owner.weaponCells![1]!.cur });
    for (let i = 0; i < 10; i++) assert(clock.battle.observe() === observation, 'observe reuses this fixed-step snapshot');
    assert(JSON.stringify({ pos: clock.owner.pos, phase: clock.driver.actor.fbPhaseSlots[0],
      timer: clock.driver.actor.handlerTimer, ammo: clock.owner.weaponCells![1]!.cur }) === before,
      'observation/pause cannot advance source phase, movement, ammo or protection');
  }

  for (const relative of [0, 5, 19, 21]) {
    const t = setup({ enemyId: 'pl0106', distance: 100 });
    t.inputs.p2.attack = true; t.tick(); t.inputs.p2.attack = false;
    const mine = t.state.projectiles.find(p => p.ownerUid === t.target.uid && p.timeBomberSource?.kind === 'mine');
    assert(mine?.timeBomberSource?.kind === 'mine', 'enemy actual B input creates an independent source mine');
    const child = () => { const s = mine.timeBomberSource; assert(s?.kind === 'mine', 'contact fixture remains a typed mine'); return s; };
    t.press(); t.inputs.p1.special = false; ticks(t, relative);
    assert(!child().hitUids.includes(t.owner.uid) && !child().contactPending, 'receiver has not already consumed mine contact');
    // Explicit host geometry fixture: relocate the DEFENDER into the real input-created
    // mine. No projectile state, hit history, contact flag or callback is changed.
    t.owner.pos = { ...mine.pos }; t.owner.vel = v(0, 0, 0);
    assert(t.owner.invincTimer === 0 && t.owner.team !== mine.team, 'defense fixture has no unrelated immunity or ally filter');
    const hp = t.owner.hp; t.tick();
    assert(Math.hypot(t.owner.pos.x - mine.pos.x, t.owner.pos.y - mine.pos.y, t.owner.pos.z - mine.pos.z) <=
      mine.hitRadius + SHOT.TARGET_BODY_RADIUS, 'receiver actually overlaps the active mine after movement on the tested pass');
    if (relative < 21) {
      assert(t.owner.hp === hp && !child().contactPending && !child().hitUids.includes(t.owner.uid),
        `relative tick${relative}: missing defensive registration cannot damage or consume mine hit history`);
    } else {
      assert(t.owner.hp < hp && child().contactPending && child().hitUids.includes(t.owner.uid),
        'after terminal cleanup the same real mine receiver route accepts damage normally');
    }
  }
}

function testInterruptionsAndDeath(): void {
  for (const relative of [0, 5, 19]) {
    const t = setup(); t.press(); t.inputs.p1.special = false; ticks(t, relative);
    // Explicit host lifecycle injection tests interruption, never source admission.
    t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20;
    t.tick();
    assert(!getTeleportXState(t.driver.actor) && !t.owner.cooldowns['romSpecialActive'],
      `hit interruption clears source ownership from relative tick${relative}`);
    assert(!t.owner.sourceHidden && !t.owner.sourceDefenseDisabled, 'interruption restores host visibility and defensive reception');
    ticks(t, 100); noPayload(t, 'interrupted actor');
    assert(t.allocations.length === 1, 'interrupted actor cannot resume or debit again');
    t.press(); source(t); assert(Number(t.allocations.length) === 2, 'later fresh press works after interruption');
  }
  const t = setup({ replacement: true }); t.press(); t.inputs.p1.special = false;
  t.owner.hp = 0; t.owner.state = 'death'; t.owner.stateTime = STATE.DEATH_DURATION - 1;
  t.tick();
  assert(!getTeleportXState(t.driver.actor), 'owner death clears the old actor source state');
  assert(!t.owner.sourceHidden && !t.owner.sourceDefenseDisabled, 'death clears teleport-only presentation and receiver gates');
  ticks(t, STATE.DEATH_DURATION + STATE.SPAWN_DURATION + 10);
  const replacement = t.state.borgs.find(b => b.ownerPlayer === 'p1' && b.uid !== t.owner.uid);
  assert(replacement, 'death fixture reaches actual replacement deployment');
  assert(t.allocations.length === 1, 'replacement cannot inherit old pending teleport or refund');
  noPayload(t, 'dead original actor');
}

function testOtherFamilies(): void {
  for (const id of ['pl0000', 'pl000a', 'pl0003', 'pl0004', 'pl0009', 'pl0101', 'pl0106', 'pl0615']) {
    const t = setup({ id }); t.press();
    assert(t.owner.command?.type === 2, `${id}: negative control executes real ordinary X input`);
    for (let i = 0; i < 100; i++) {
      assert(!getTeleportXState(t.driver.actor), `${id}: unrelated family never enters Teleport Ninja action clock`);
      t.tick();
    }
  }
}

export function runTeleportXBattleSelfTest(): void {
  testActualAdmissionAndClocks();
  testOwnMotionDestinationAndTravel();
  testTapHoldAndRepeat();
  testAmmoAndIncrementalRefill();
  testDistinctChargedRelease();
  testDefenseWindowAndVisibility();
  testInterruptionsAndDeath();
  testOtherFamilies();
  console.log('[teleportXBattle] PASS: actual tap/movement/jump, phase clocks, own-history travel, source ammo/refill, distinct charge, defense/visibility, repeat/interruption/death and family isolation');
}
