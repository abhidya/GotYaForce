/** Actual-input Switching Ninja ordinary X regressions.
 * Attacks enter through Battle input. Explicit scheduler/helper adjuncts below
 * do not claim to exercise original admission or damage; relocation/lifecycle
 * fixtures exercise host collision seams, not original animated joint geometry.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { STATE } from './constants.js';
import { getSwitchingXState, stepSwitchingX } from './switchingX.js';
import { createSwitchingSwapPass, stageSwitchingSwap, commitSwitchingSwapPass, stepSwitchingForcedMove,
  type SwitchingForcedRomActor } from './switchingProjectile.js';
import type { Vec3 } from './rom/actor.js';
import type { BorgStats } from './stats.js';
import { emptyInput, type Projectile, type StageCollision } from './types.js';
import data from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (data as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[switchingXBattle] ${message}`);
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
interface SetupOptions {
  id?: string;
  targetId?: string;
  distance?: number;
  extraTarget?: boolean;
  ownerReplacement?: boolean;
  targetReplacement?: boolean;
  reverseActors?: boolean;
}
function setup(options: SetupOptions = {}) {
  const id = options.id ?? 'pl0009', targetId = options.targetId ?? 'pl0615';
  const battle = createBattle({ stageId: 'st00', bounds: { x: 20000, z: 20000 }, collision: floor(), forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: options.ownerReplacement ? [id, id] : [id] },
    { team: 1, ownerPlayer: 'p2', borgIds: options.targetReplacement ? [targetId, targetId] : [targetId] },
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
  target.pos = v(0, 10, options.distance ?? 4000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  if (other) { other.pos = v(3000, 10, 4000); other.vel = v(0, 0, 0); }
  for (let i = 0; i < 4; i++) battle.step(1 / 60, inputs);
  if (options.reverseActors) state.borgs.reverse();
  let elapsed = 0;
  const events: { frame: number; address: number; row: number; pos: Vec3 }[] = [];
  const allocations: { frame: number; slot: number; count: number; mode: number | undefined; accepted: boolean }[] = [];
  const cues: number[] = []; battle.onRomCue = cue => cues.push(cue);
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ frame: elapsed, address, row, pos: { ...actor.pos } }); spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ frame: elapsed, slot, count, mode, accepted }); return accepted;
  };
  const tick = () => { elapsed++; return battle.step(1 / 60, inputs); };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, other, driver, inputs, events, allocations, cues, tick, press, release,
    get frame() { return elapsed; } };
}
type Fixture = ReturnType<typeof setup>;
function ticks(t: Fixture, count: number): void { for (let i = 0; i < count; i++) t.tick(); }
function shots(t: Fixture): Projectile[] { return t.state.projectiles.filter(p => p.ownerUid === t.owner.uid); }
function jump(t: Fixture): void {
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false; ticks(t, 3);
  assert(!t.owner.grounded && t.owner.pos.y > 10, 'actual jump establishes airborne admission');
}
function idle(t: Fixture): void {
  for (let i = 0; i < 180 && (t.owner.state === 'special' || t.owner.cooldowns['romSpecialActive']); i++) t.tick();
  assert(t.owner.state !== 'special' && !t.owner.cooldowns['romSpecialActive'], 'source recovery releases Battle ownership');
}

function field(t: Fixture): Projectile & { switchingSource: NonNullable<Projectile['switchingSource']> } {
  const child = shots(t).find(p => p.switchingSource);
  assert(child?.switchingSource, 'actual ordinary X creates its dedicated stationary source field');
  return child as Projectile & { switchingSource: NonNullable<Projectile['switchingSource']> };
}
function releaseField(t: Fixture): ReturnType<typeof field> {
  t.press(); t.inputs.p1.special = false;
  for (let i = 0; i < 40 && !t.events.length; i++) t.tick();
  assert(t.events.length === 1, 'actual X reaches exactly one authored release');
  return field(t);
}
function warningEnd(t: Fixture, child: ReturnType<typeof field>): void {
  for (let i = 0; i < 70 && child.switchingSource.field.timer > 0; i++) t.tick();
  assert(child.switchingSource.field.timer === 0 && !child.switchingSource.field.hitActive,
    'warning reaches zero without an early registration');
}

function testInputReleaseAndWarning(): void {
  for (const air of [false, true]) {
    const t = setup(); if (air) jump(t);
    const cell = t.owner.weaponCells![1]!, bAmmo = t.owner.weaponCells![0]!.cur;
    assert(t.owner.weaponCells![2] === cell && cell.max === 1 && cell.cur === 1 &&
      cell.refillType === 0 && cell.refillParam === 180 && cell.timer === 0,
      'decoded source cell2 aliases HUD X with max1/type0/refill180');
    const admittedAt = t.frame + 1, initial = { ...t.owner.pos }, hp = t.target.hp;
    t.press();
    assert(t.owner.command?.exact && t.owner.command.type === 2 && t.owner.command.actionIndex === 2 &&
      t.owner.command.recordAddress === (air ? '0x8033eab8' : '0x8033ea78') &&
      t.driver.actor.variantIndex === (air ? 4 : 0) && t.driver.actor.fbCue === (air ? 45 : 44),
      'actual ground/air ordinary X selects source action2 and cue44/45');
    assert(getSwitchingXState(t.driver.actor)?.stream?.slot === (air ? 5 : 4), 'source g4s4/5 selected by actual grounded state');
    if (!air) same(t.owner.pos, initial, 'stationary admission has no invented target-distance travel');
    assert(t.events.length === 0 && t.allocations.length === 0 && shots(t).length === 0 && cell.cur === 1,
      'admission neither spends ammunition nor creates a generic fallback');
    t.inputs.p1.special = false;
    for (let relative = 1; relative < 28; relative++) {
      t.tick();
      assert(t.events.length === 0 && t.allocations.length === 0 && shots(t).length === 0 && cell.cur === 1,
        `authored wait remains closed at relative source dispatch${relative}`);
    }
    t.tick(); const child = field(t), released = { ...child.pos };
    assert(Number(t.events.length) === 1 && t.events[0]!.frame === admittedAt + 28 &&
      t.events[0]!.address === 0x801e29fc && t.events[0]!.row === 0,
      'stream tick28 after phase0 admission releases exactly one original field constructor');
    assert(Number(t.allocations.length) === 1 && t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1 &&
      t.allocations[0]!.mode === 1 && t.allocations[0]!.accepted && Number(cell.cur) === 0 && Number(cell.timer) === 180,
      'release consumes one source cell2 and starts its180 update debt');
    assert(t.owner.weaponCells![0]!.cur === bAmmo, 'ordinary X leaves B ammunition intact');
    assert(child.damageRecord?.index === 12 && child.damageRecord.hpDamage === 30 && child.damageRecord.flagsA === 0x11,
      'field binds verified source damage record12 HP30 flagsA0x11');
    near(child.hitRadius, 270 * child.switchingSource.field.collisionScale, 'source capsule radius270 scales independently of draw state');
    assert(shots(t).length === 1 && !child.ninjaSource && !child.poweredSource && !child.gatlingSource,
      'one field replaces the generic X payload without unrelated family tags');
    assert(child.switchingSource.field.timer === 60 && !child.switchingSource.field.hitActive && child.switchingSource.field.visible,
      'INIT places the stationary warning and returns with timer60');
    for (let warning = 1; warning <= 60; warning++) {
      t.tick();
      assert(child.switchingSource.field.timer === 60 - warning && !child.switchingSource.field.hitActive,
        `warning update${warning} does not register HIT early`);
      same(child.pos, released, 'field never drifts during warning');
      assert(t.target.hp === hp && !t.owner.switchingForcedMove && !t.target.switchingForcedMove,
        'warning cannot damage, reserve a swap, or force actor movement');
    }
    t.tick();
    assert(child.switchingSource.field.hitActive && Number(child.switchingSource.field.timer) === 25,
      '61st post-INIT update registers HIT and keeps all25 active passes');
    assert(t.target.hp < hp && child.switchingSource.contactPending && child.hitConfirmedThisFrame,
      `natural field overlap enters real damage reception only at HIT registration: ${JSON.stringify({air,hp,after:t.target.hp,contact:child.switchingSource.contactPending,confirmed:child.hitConfirmedThisFrame,pos:child.pos,target:t.target.pos,ownerSwap:t.owner.switchingForcedMove,targetSwap:t.target.switchingForcedMove})}`);
    assert(t.owner.switchingForcedMove?.dispatches === 0 && t.target.switchingForcedMove?.dispatches === 0,
      'collision pass stages both participants but cannot run their first forced update');
    const sample = t.battle.observe(), stateBefore = JSON.stringify({ field: child.switchingSource.field,
      owner: t.owner.pos, target: t.target.pos, swap: t.owner.switchingForcedMove, ammo: cell });
    for (let i = 0; i < 8; i++) assert(t.battle.observe() === sample, 'observe reuses a fixed-step snapshot');
    assert(JSON.stringify({ field: child.switchingSource.field, owner: t.owner.pos, target: t.target.pos,
      swap: t.owner.switchingForcedMove, ammo: cell }) === stateBefore, 'observation cannot advance warning, swap or ammunition');
  }
}

function testDeferredSwapAndSupport(): void {
  for (const reverseActors of [false, true]) for (const supports of [false, true]) {
    const t = setup({ reverseActors }); const child = releaseField(t); warningEnd(t, child);
    // Explicit support-anchor fixture adjunct. The host has no original animated
    // +6d0 producer; these offsets test the verified algebra, not original geometry.
    if (supports) { t.owner.sourceSupportHeight6d0 = 17; t.target.sourceSupportHeight6d0 = 53; }
    const ownerBefore = { ...t.owner.pos }, targetBefore = { ...t.target.pos };
    const ownerYaw = t.owner.rotY, targetYaw = t.target.rotY;
    const offset = supports ? 36 : 0;
    const ownerDestination = { ...targetBefore, y: targetBefore.y + offset };
    const targetDestination = { ...ownerBefore, y: ownerBefore.y - offset };
    t.tick();
    assert(t.owner.switchingForcedMove && t.target.switchingForcedMove, 'accepted contact stages the source pair');
    same(t.owner.switchingForcedMove.destination, ownerDestination, 'owner destination includes victim6d0 minus owner6d0');
    same(t.target.switchingForcedMove.destination, targetDestination, 'victim destination includes owner6d0 minus victim6d0');
    same(t.owner.pos, ownerBefore, 'contact cannot instantly teleport owner');
    same(t.target.pos, targetBefore, 'contact cannot instantly teleport victim');
    assert(t.owner.sourceDefenseDisabled && t.target.sourceDefenseDisabled,
      'post-collision activation protects both admitted forced actors');
    for (let dispatch = 1; dispatch <= 5; dispatch++) {
      t.tick();
      same(t.owner.pos, dispatch < 3 ? ownerBefore : ownerDestination, `owner forced dispatch${dispatch}`);
      same(t.target.pos, dispatch < 3 ? targetBefore : targetDestination, `victim forced dispatch${dispatch}`);
      assert(Boolean(t.owner.sourceDefenseDisabled) === (dispatch < 5) && Boolean(t.target.sourceDefenseDisabled) === (dispatch < 5),
        `forced protection expires only at dispatch5, observed${dispatch}`);
      if (dispatch < 5) assert(t.owner.switchingForcedMove?.dispatches === dispatch && t.target.switchingForcedMove?.dispatches === dispatch,
        'both actors receive one forced update independent of array order');
      else assert(!t.owner.switchingForcedMove && !t.target.switchingForcedMove, 'fifth update restores both actor handlers');
      if (dispatch === 3) {
        same(t.driver.actor.pos, ownerDestination, 'forced write reaches original actor position shadow');
        same(t.driver.actor.targetCache5e8, ownerDestination, 'forced move resets older own-position history');
        same(t.driver.actor.savedGroundPos, ownerDestination, 'forced move resets saved ground-position history');
      }
    }
    near(t.owner.rotY, ownerYaw, 'kind2 swap does not rotate owner');
    near(t.target.rotY, targetYaw, 'kind2 swap does not rotate victim');
    assert((child.switchingSource.field.flags272 & 1) !== 0 && child.switchingSource.field.visible,
      'prior child contact disables later HIT reception while visual lifetime continues');
    const hp = t.target.hp; ticks(t, 8); assert(t.target.hp === hp, 'same field cannot damage again on later updates');
  }
}

function testMultipleVictimsSamePass(): void {
  for (const reverseActors of [false, true]) {
    const t = setup({ extraTarget: true, reverseActors }); const child = releaseField(t); warningEnd(t, child);
    assert(t.other, 'third actor fixture is deployed');
    // Explicit host collision geometry adjunct: two real receivers overlap one
    // actual-input field. No hit flags, callbacks or projectile timers are injected.
    t.other.pos = { ...t.target.pos }; t.other.vel = v(0, 0, 0);
    const targetHp = t.target.hp, otherHp = t.other.hp;
    const first = t.state.borgs.find(b => b.uid === t.target.uid || b.uid === t.other!.uid)!;
    const second = first === t.target ? t.other : t.target;
    t.tick();
    assert(t.target.hp < targetHp && t.other.hp < otherHp,
      'all same-pass eligible receivers take ordinary damage despite first outgoing swap reservation');
    assert(t.owner.switchingForcedMove && first.switchingForcedMove && !second.switchingForcedMove,
      'outgoing/incoming reservation admits only the first compatible source pair in actual receiver order');
    assert(child.switchingSource.field.flags272 === 0 && child.switchingSource.contactPending,
      'same-pass child contact is latched, never prematurely consumed as a removal');
    t.tick(); assert((child.switchingSource.field.flags272 & 1) !== 0, 'next child update consumes prior contact once');
  }
}

function testMissLifetimeAndPlacement(): void {
  const t = setup({ extraTarget: true }); t.press(); t.inputs.p1.special = false;
  assert(t.other, 'alternate target deployed');
  const captured = t.target.uid;
  t.inputs.p1.switchLock = true; t.tick(); t.inputs.p1.switchLock = false;
  assert(t.owner.lockTarget !== captured && getSwitchingXState(t.driver.actor)?.targetUid === captured,
    'actual lock switch cannot replace an already captured ordinary X target');
  t.inputs.p2.moveX = 1;
  while (!t.events.length && t.frame < 40) t.tick();
  t.inputs.p2.moveX = 0;
  const child = field(t), placed = { ...child.pos };
  same(placed, t.target.pos, 'INIT samples captured target current position after actual locomotion');
  assert(child.aimedTargetUid === captured, 'field attribution retains the originally captured identity');
  // Explicit relocation adjunct creates an unobstructed miss without injecting
  // registration, contact or damage. This is not an original movement oracle.
  t.target.pos = v(-10000, 10, -10000); t.target.vel = v(0, 0, 0);
  const hp = t.target.hp; warningEnd(t, child); t.tick();
  assert(child.switchingSource.field.hitActive && child.switchingSource.field.timer === 25 && !child.switchingSource.contactPending,
    'miss still registers its full source active clock');
  for (let pass = 1; pass <= 24; pass++) {
    t.tick();
    assert(child.switchingSource.field.hitActive && child.switchingSource.field.timer === 25 - pass,
      `registration plus${pass} subsequent updates retains HIT`);
    same(child.pos, placed, 'field does not home after placement');
  }
  t.tick(); assert(!child.switchingSource.field.hitActive && !child.switchingSource.field.visible && child.switchingSource.field.phase === 'retiring',
    '25th following update disables HIT and hides the field');
  t.tick(); assert(String(child.switchingSource.field.phase) === 'released', 'next dispatch releases child resources');
  t.tick(); assert(!shots(t).includes(child), 'following dispatch frees child without duplicate callback');
  assert(t.target.hp === hp && t.events.length === 1, 'natural miss never manufactures damage or another release');
}

function testAmmoAndPressEdges(): void {
  const t = setup({ distance: 12000 }), child = releaseField(t), cell = t.owner.weaponCells![1]!;
  t.inputs.p1.special = true; t.tick(); t.inputs.p1.special = false; t.tick();
  assert(t.events.length === 1 && t.allocations.length === 1, 'busy re-press cannot duplicate the source throw');
  idle(t); t.press(); t.release();
  assert(t.events.length === 1 && !getSwitchingXState(t.driver.actor), 'empty ordinary X is denied without generic fallback');
  while (cell.timer > 1) { t.inputs.p1.special = true; t.tick(); }
  assert(cell.cur === 0 && cell.timer === 1, 'type0 stays empty through the final debt update');
  t.tick(); assert(Number(cell.cur) === 1 && Number(cell.timer) === 0 && t.events.length === 1,
    'exactly180 post-release updates refill one X without replaying held input');
  ticks(t, 40); assert(t.events.length === 1 && t.allocations.length === 1 && !shots(t).includes(child),
    'held denied input remains discarded after refill and old field retirement');
  t.release(); t.press(); t.inputs.p1.special = false; ticks(t, 28);
  assert(Number(t.events.length) === 2 && Number(t.allocations.length) === 2 && cell.cur === 0,
    'fresh eligible press releases exactly one new source field');

  const paused = setup({ distance: 12000 }); releaseField(paused);
  const pc = paused.owner.weaponCells![1]!; paused.owner.sourceAmmoRefillPauseMask = 4; paused.tick();
  assert(pc.timer === 180, 'source cell2 pause bit freezes aliased X debt');
  paused.owner.sourceAmmoRefillPauseMask = 2; paused.tick();
  assert(Number(pc.timer) === 179, 'HUD cell1 bit does not pause source cell2 refill');
}

function testPlacementRangeAndVelocity(): void {
  for (const distance of [5499, 5501, 12000]) {
    const t = setup({ distance }); const child = releaseField(t);
    assert(Boolean(child.switchingSource.captureFlagsD0 & 4) === (distance < 5500),
      'bounded target-range adapter preserves the decoded5500 capture flag boundary');
    same(child.pos, distance < 5500 ? t.target.pos : v(0, 10, 2000),
      'target capture places at its current root; out-of-range fallback uses decoded forward2000');
  }

  for (const air of [false, true]) {
    const t = setup(), child = releaseField(t); warningEnd(t, child);
    const control = setup(); ticks(control, t.frame);
    // Actual movement inputs are sampled on the activating pass. The field's
    // capsule is tall enough to receive either ordinary lateral motion or jump.
    t.inputs.p2.moveX = control.inputs.p2.moveX = 1;
    t.inputs.p2.jump = control.inputs.p2.jump = air; const hp = t.target.hp;
    control.tick();
    t.tick(); t.inputs.p2.moveX = 0; t.inputs.p2.jump = false;
    assert(t.target.hp < hp && t.target.switchingForcedMove, 'moving receiver takes real field damage and activates swap');
    const motion = { ...t.target.vel };
    assert(Math.abs(motion.x) > 0 && (air ? motion.y > 0 : motion.y === 0),
      'velocity fixture establishes nonzero actual locomotion/jump, regardless of camera-relative heading');
    same(motion, control.target.vel, 'accepted incoming swap retains no-field control velocity instead of generic knockback');
    for (let dispatch = 1; dispatch <= 5; dispatch++) { t.tick(); same(t.target.vel, motion, `forced dispatch${dispatch} preserves incoming velocity`); }
  }
}

/** Scheduler and unsupported-geometry adjuncts only. These call the bounded
 * helpers explicitly, so they are not evidence of an original admission path. */
function testForcedMoveHelperAdjuncts(): void {
  {
    const t = setup({ extraTarget: true }); assert(t.other, 'directional adjunct has three actors');
    const a = { ...t.owner.pos }, b = { ...t.target.pos }, c = { ...t.other.pos };
    const pass = createSwitchingSwapPass(t.state.borgs);
    assert(stageSwitchingSwap(pass, t.owner, t.target), 'adjunct A to B reserves two directional sides');
    assert(!stageSwitchingSwap(pass, t.owner, t.other), 'adjunct repeated outgoing A is rejected');
    assert(!stageSwitchingSwap(pass, t.other, t.target), 'adjunct repeated incoming B is rejected');
    assert(stageSwitchingSwap(pass, t.target, t.other), 'adjunct incoming B may independently become outgoing B');
    commitSwitchingSwapPass(pass, t.state.borgs);
    same(t.owner.switchingForcedMove!.destination, b, 'A retains B original position');
    same(t.target.switchingForcedMove!.destination, c, 'B later outgoing reservation replaces incoming destination');
    same(t.other.switchingForcedMove!.destination, b, 'C receives B original position, not A staged destination');
    same(t.owner.pos, a, 'helper activation alone never moves actors');
  }
  {
    const t = setup(), actor = t.driver.actor as SwitchingForcedRomActor;
    actor.moveKind7c9 = 2;
    const pass = createSwitchingSwapPass(t.state.borgs); assert(stageSwitchingSwap(pass, t.owner, t.target), 'guard adjunct still reserves collision pair');
    commitSwitchingSwapPass(pass, t.state.borgs);
    assert(!t.owner.switchingForcedMove && t.target.switchingForcedMove,
      'nonzero source7c9 rejects only that actor; paired participant still activates');
  }
  {
    const t = setup(); t.target.pos = v(25000, -250, -27000);
    const pass = createSwitchingSwapPass(t.state.borgs); stageSwitchingSwap(pass, t.owner, t.target); commitSwitchingSwapPass(pass, t.state.borgs);
    const bounds = { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 };
    for (let i = 0; i < 3; i++) stepSwitchingForcedMove(t.owner, bounds);
    same(t.owner.pos, v(20000, -250, -20000), 'kind2 clamps staged XZ only and retains negative staged Y without floor reprobe');
    same(t.driver.actor.targetCache5e8, t.owner.pos, 'clamped helper destination resets older history');
    same(t.driver.actor.savedGroundPos, t.owner.pos, 'clamped helper destination resets ground history');
  }
}

/** Explicit forced-scheduler adjunct using a live actual-input source action.
 * The host bridge treats control lowbits0 as its action-complete gate. We test
 * original handler restoration here without claiming that generic host gate is
 * an original scheduler oracle. */
function testSuspendedSourceAction(): void {
  const t = setup(); t.press(); t.release(); ticks(t, 10);
  const rom = t.driver.actor as SwitchingForcedRomActor;
  const source = getSwitchingXState(rom);
  assert(source?.stream && t.owner.state === 'special', 'actual ordinary X supplies a live source handler for scheduler adjunct');
  rom.controlWord &= ~3;
  const pass = createSwitchingSwapPass(t.state.borgs);
  stageSwitchingSwap(pass, t.owner, t.target); commitSwitchingSwapPass(pass, t.state.borgs);
  const move = t.owner.switchingForcedMove;
  assert(move?.previousRom, 'helper activation suspends the live source action');
  const frame = source.stream.frame, phases = [...rom.fbPhaseSlots], saved = { ...move.previousRom };
  assert(rom.fbCue === 0x23 && rom.ubCue === 0x23 && rom.moveKind7c9 === 2 && rom.movePhase7ca === 0 && rom.flags272 === 0xffff,
    'post-pass activation binds the original forced cue/kind without running phase0 early');
  for (let dispatch = 1; dispatch <= 5; dispatch++) {
    t.tick();
    assert(getSwitchingXState(rom) === source && source.stream.frame === frame,
      `forced dispatch${dispatch} suspends rather than cancels or advances original source action`);
    assert(rom.fbPhaseSlots.every((value, index) => value === phases[index]), 'forced cue setters preserve suspended source phase slots');
  }
  assert(rom.fbCue === saved.fbCue && rom.ubCue === saved.ubCue && rom.fbState === saved.fbState && rom.ubState === saved.ubState &&
    Number(rom.moveKind7c9) === 0 && Number(rom.movePhase7ca) === 3 && rom.moveTimer7cb === 0 && Number(rom.flags272) === 0 && !(rom.controlWord & 0x1000),
    'fifth forced dispatch restores saved source handlers and clears only forced-move gates');
  stepSwitchingX(rom, t.driver.ctx);
  assert(getSwitchingXState(rom) === source && source.stream.frame > frame,
    'restored original handler resumes the same animation clock when dispatched directly');
}

function testInterruptionsDeathAndResistance(): void {
  const early = setup(); early.press(); early.release();
  // Explicit lifecycle fixture: interrupt before the authored release. Attacks
  // still enter through actual input; no successful hit or damage is fabricated.
  early.owner.state = 'hit'; early.owner.stateTime = 0; early.owner.cooldowns['hitstun'] = 20; early.tick();
  ticks(early, 100);
  assert(!getSwitchingXState(early.driver.actor) && early.events.length === 0 && early.allocations.length === 0 && shots(early).length === 0,
    'pre-release interruption cancels pending source throw without spending');

  const late = setup(); const live = releaseField(late);
  late.owner.state = 'hit'; late.owner.stateTime = 0; late.owner.cooldowns['hitstun'] = 20; late.tick();
  assert(!getSwitchingXState(late.driver.actor) && live.switchingSource.field.phase === 'active',
    'owner interruption after release clears action but leaves its independent stationary field');
  warningEnd(late, live); const lateHp = late.target.hp; late.tick();
  assert(late.target.hp < lateHp && late.owner.switchingForcedMove,
    'released field survives nonlethal interruption and keeps real damage/swap reception');

  const dead = setup({ ownerReplacement: true }); const orphan = releaseField(dead);
  dead.owner.hp = 0; dead.owner.state = 'death'; dead.owner.stateTime = STATE.DEATH_DURATION - 1; dead.tick();
  assert(!getSwitchingXState(dead.driver.actor) && !orphan.switchingSource.field.hitActive && !orphan.switchingSource.field.visible,
    'owner death cancels action and retires independent child before it can register');
  ticks(dead, STATE.DEATH_DURATION + STATE.SPAWN_DURATION + 10);
  assert(dead.state.borgs.some(b => b.ownerPlayer === 'p1' && b.uid !== dead.owner.uid) && shots(dead).length === 0 && dead.events.length === 1,
    'actual replacement deployment cannot inherit old field or delayed throw');

  const resist = setup(); const guarded = releaseField(resist); warningEnd(resist, guarded);
  // Explicit source59c fixture adjunct. Its gameplay producer is outside this lane.
  resist.target.sourceSwitchingResistance59c = 0x10;
  const hp = resist.target.hp; resist.tick();
  assert(resist.target.hp < hp && !resist.owner.switchingForcedMove && !resist.target.switchingForcedMove,
    'source59c bit0x10 refuses the swap without suppressing ordinary field damage');

  const lethal = setup({ targetReplacement: true }); const killer = releaseField(lethal); warningEnd(lethal, killer);
  lethal.target.hp = 1; const before = { ...lethal.target.pos }; lethal.tick();
  assert(lethal.target.hp <= 0 && !lethal.target.switchingForcedMove && lethal.owner.switchingForcedMove,
    'lethal collision independently excludes dead victim while living owner still activates');
  ticks(lethal, 3); same(lethal.owner.pos, before, 'surviving participant reaches its staged destination after partner death');

  for (const ownerDies of [false, true]) {
    const t = setup({ ownerReplacement: true, targetReplacement: true }), child = releaseField(t);
    warningEnd(t, child); t.tick();
    const deadParticipant = ownerDies ? t.owner : t.target, survivor = ownerDies ? t.target : t.owner;
    const destination = { ...survivor.switchingForcedMove!.destination };
    // Explicit lifecycle adjunct after a real accepted contact, before the
    // first forced update. No source phase, destination or contact is injected.
    deadParticipant.hp = 0; deadParticipant.state = 'death'; deadParticipant.stateTime = 0;
    t.tick();
    assert(!deadParticipant.switchingForcedMove && survivor.switchingForcedMove?.dispatches === 1,
      'participant death cancels only its own pending forced handler');
    ticks(t, 2); same(survivor.pos, destination, 'living paired actor still relocates on its third actual dispatch');
    ticks(t, 2); assert(!survivor.switchingForcedMove && !survivor.sourceDefenseDisabled,
      'living paired actor restores independently on its fifth actual dispatch');
  }
}

function testOtherFamilies(): void {
  for (const id of ['pl0000', 'pl000a', 'pl0003', 'pl0004', 'pl0005', 'pl0101', 'pl0106', 'pl0615']) {
    const t = setup({ id }); t.press(); t.inputs.p1.special = false;
    assert(t.owner.command?.type === 2, `${id}: negative control enters actual ordinary X`);
    for (let i = 0; i < 100; i++) {
      assert(!getSwitchingXState(t.driver.actor) && shots(t).every(p => !p.switchingSource),
        `${id}: unrelated ordinary X never enters Switching source action or field`);
      t.tick();
    }
  }
}

export function runSwitchingXBattleSelfTest(): void {
  testInputReleaseAndWarning();
  testDeferredSwapAndSupport();
  testMultipleVictimsSamePass();
  testMissLifetimeAndPlacement();
  testAmmoAndPressEdges();
  testPlacementRangeAndVelocity();
  testForcedMoveHelperAdjuncts();
  testSuspendedSourceAction();
  testInterruptionsDeathAndResistance();
  testOtherFamilies();
  console.log('[switchingXBattle] PASS: actual ground/air X, delayed field, deferred support-adjusted swap, same-pass receivers, source ammo, targeting, interruption/death/resistance and family isolation');
}
