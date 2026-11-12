/** Actual Battle input regressions for Gatling Gunner's source action-2/X lane.
 * These fixtures exercise the declared host collision stand-in, not animated
 * source joint matrices or exact source HIT shape overlap.
 */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { RomDriverBridge } from './bridge.js';
import { STATE } from './constants.js';
import { stepProjectiles } from './combat.js';
import { gatlingMuzzle } from './gatlingProjectile.js';
import { runSelfTest as runGatlingProjectileSelfTest } from './gatlingProjectile.selftest.js';
import { emptyInput, type BorgRuntime, type Projectile, type StageCollision, type StageCollisionTriangle } from './types.js';
import type { BorgStats } from './stats.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };

const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number) => ({ x, y, z });
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[gatlingBattle] ${message}`);
}
function near(actual: number, expected: number, message: string, tolerance = 1e-6): void {
  assert(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
}
function triangle(index: number, vertices: StageCollisionTriangle['vertices'], normal: StageCollisionTriangle['normal']): StageCollisionTriangle {
  return { index, layerIndex: 0, marker: 0xcccccccc, vertices, normal, planeD: 0,
    bounds2d: { minX: -10000, maxX: 10000, minZ: -10000, maxZ: 10000 } };
}
function floorAndWall(wallZ: number): StageCollision {
  return { triangles: [
    triangle(0, [v(-10000, 0, -10000), v(10000, 0, -10000), v(10000, 0, 10000)], v(0, 1, 0)),
    triangle(1, [v(-10000, 0, -10000), v(10000, 0, 10000), v(-10000, 0, 10000)], v(0, 1, 0)),
    triangle(2, [v(-2000, -1000, wallZ), v(2000, -1000, wallZ), v(0, 3000, wallZ)], v(0, 0, -1)),
  ] };
}
function setup(collision?: StageCollision, extraTarget = false, targetReplacement = false) {
  const battle = createBattle({ stageId: 'st00', bounds: { x: 10000, z: 10000 }, forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: ['pl0102'] },
    { team: 1, ownerPlayer: 'p2', borgIds: targetReplacement ? ['pl0615', 'pl0615'] : ['pl0615'] },
    ...(extraTarget ? [{ team: 1, ownerPlayer: 'p3', borgIds: ['pl0615'] }] : []),
  ], ...(collision ? { collision } : {}) }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput(), p3: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find(b => b.ownerPlayer === 'p1')!;
  const target = state.borgs.find(b => b.ownerPlayer === 'p2')!;
  assert(owner.romDriver instanceof RomDriverBridge, 'Gatling has the live family bridge');
  const driver = owner.romDriver;
  owner.pos = v(0, 0, 0); owner.rotY = 0; owner.vel = v(0, 0, 0); owner.grounded = true;
  target.pos = v(0, 0, 6000); target.vel = v(0, 0, 0); owner.lockTarget = target.uid;
  const other = state.borgs.find(b => b.ownerPlayer === 'p3');
  if (other) other.pos = v(3000, 0, 6000);
  const events: { address: number; row: number; hSpeed: number; yVel: number; contact: number; auxiliary: number }[] = [];
  const allocations: { slot: number; count: number; accepted: boolean }[] = [];
  const cues: number[] = [];
  battle.onRomCue = cue => cues.push(cue);
  const spawn = driver.ctx.onFamilyProjectile!;
  driver.ctx.onFamilyProjectile = (actor, address, row) => {
    events.push({ address, row, hSpeed: actor.hSpeed, yVel: actor.yVel, contact: actor.contactP0,
      auxiliary: actor.parts[0].stateByte });
    spawn(actor, address, row);
  };
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ slot, count, accepted });
    return accepted;
  };
  const tick = () => battle.step(1 / 60, inputs);
  const press = () => { inputs.p1.special = true; return tick(); };
  return { battle, inputs, state, owner, target, other, driver, events, allocations, cues, tick, press };
}
type Fixture = ReturnType<typeof setup>;
function primaryFor(test: Fixture): Projectile {
  const primary = test.state.projectiles.find(p => p.ownerUid === test.owner.uid && p.gatlingSource?.kind === 'primary');
  assert(primary, 'input-created Gatling primary exists');
  return primary;
}
function launch(test: Fixture): Projectile {
  test.press();
  for (let i = 0; i < 16; i++) test.tick();
  return primaryFor(test);
}

function testAdmissionAndAmmo(): void {
  const test = setup();
  const { owner, driver, events, allocations, state, battle, inputs } = test;
  const cell = owner.weaponCells![1]!;
  assert(owner.weaponCells![2] === cell && cell.max === 4 && cell.cur === 4 && cell.timer === 0,
    'source cell2 aliases HUD X cell1, full four-round magazine and no refill debt');
  const bAmmo = owner.weaponCells![0]!.cur;
  test.press();
  assert(owner.command?.type === 2 && owner.command.actionIndex === 2 && owner.command.recordAddress === '0x80338298',
    'actual X press selects Gatling type2/action2 exact command');
  assert(driver.actor.actionIndex === 2 && owner.state === 'special', 'ROM action2 owns X admission');
  assert(events.length === 0 && allocations.length === 0 && cell.cur === 4,
    'admission neither consumes ammo nor emits an early generic projectile');
  for (let i = 0; i < 15; i++) {
    test.tick();
    assert(events.length === 0 && allocations.length === 0 && cell.cur === 4,
      `authored fire gate is closed before frame16 (${i + 1})`);
  }
  test.tick();
  assert(Number(events.length) === 1 && events[0]!.address === 0x8007db5c && events[0]!.row === 4,
    'frame16 dispatches exactly shared spawner row4');
  assert(events[0]!.contact > 0 && events[0]!.auxiliary === events[0]!.contact,
    'authored part0 +0x1cef state, mirrored by the stream VM, opens the fire gate');
  assert(Number(allocations.length) === 1 && allocations[0]!.slot === 2 && allocations[0]!.count === 1 && allocations[0]!.accepted,
    'one source cell2 allocation at the gate');
  assert(Number(cell.cur) === 3 && owner.weaponCells![0]!.cur === bAmmo, 'X consumes once and leaves B ammo alone');
  assert(state.projectiles.length === 1, 'single source round, no generic or Powered fallback');
  const primary = primaryFor(test);
  assert(primary.gatlingSource?.kind === 'primary', 'source primary state');
  const flight = primary.gatlingSource.flight;
  assert(flight.row === 4 && primary.life === 599 && flight.life === 599, 'row4 constructor advances exactly once from life600');
  assert(flight.gravityTimer === 3, 'constructor consumes first of four gravity-query frames');
  near(flight.gravity, .3, 'row4 source gravity');
  assert(primary.flightVisual?.bankTexId !== 10 && primary.romShotKind === 0 && primary.romScale?.[0] === 2,
    'row4 carries HIT0 and draw scale2 without misidentifying weapon-bank model10 as global FX10');
  assert(!primary.poweredSource && battle.observe().poweredLaunchFlashes.length === 0,
    'Gatling primary has no Powered children or launch presentation');
  assert(events[0]!.hSpeed === 0 && events[0]!.yVel === 0, 'zero dash strength does not add source recoil');
  const first = battle.observe();
  for (let i = 0; i < 10; i++) assert(battle.observe() === first, 'render-only observations cannot advance flight');
  test.tick();
  assert(Number(primary.life) === 598 && first.projectiles[0]!.life === 599,
    'subsequent Battle frame advances once and previous observation remains immutable');
  for (let i = 0; i < 100; i++) test.tick();
  assert(Number(events.length) === 1 && Number(allocations.length) === 1, 'holding X cannot repeat after action exit');
  inputs.p1.special = false; test.tick();
  for (let i = 0; i < 200; i++) test.tick();
  test.press();
  for (let i = 0; i < 16; i++) test.tick();
  assert(Number(events.length) === 2 && Number(allocations.length) === 2, 'fresh repress starts exactly one fresh row4 shot');

  const refill = setup(), x = refill.owner.weaponCells![1]!;
  x.cur = x.max - 1; x.timer = x.refillParam;
  for (let i = 1; i < x.refillParam; i++) refill.tick();
  assert(x.cur === x.max - 1 && x.timer === 1, 'aliased X cell receives one refill tick per Battle frame');
  refill.tick(); assert(x.cur === x.max && Number(x.timer) === 0, 'source refill restores integer ammo at exact period');
  x.cur = x.max - 1; x.timer = x.refillParam; refill.owner.sourceAmmoRefillPauseMask = 4;
  refill.tick(); assert(x.timer === x.refillParam, 'source slot2 pause bit pauses HUD X cell');
  refill.owner.sourceAmmoRefillPauseMask = 2; refill.tick();
  assert(x.timer === x.refillParam - 1, 'browser HUD index1 pause bit does not pause source cell2');
}

function testNegativeControls(): void {
  const tap = setup(); tap.press(); tap.inputs.p1.special = false;
  for (let i = 0; i < 16; i++) tap.tick();
  assert(tap.events.length === 1 && tap.allocations.length === 1, 'short tap completes one authored delayed shot');
  for (let i = 0; i < 100; i++) tap.tick();
  assert(tap.events.length === 1, 'release after tap does not buffer another shot');

  for (const mode of ['empty', 'depleted', 'interrupted', 'busy'] as const) {
    const t = setup();
    if (mode === 'empty') t.owner.weaponCells![1]!.cur = 0;
    if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
    t.press();
    if (mode === 'depleted') t.owner.weaponCells![1]!.cur = 0;
    if (mode === 'interrupted') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
    const hp = t.target.hp;
    assert(t.state.projectiles.every(p => p.ownerUid !== t.owner.uid), `${mode}: admission has no damaging fallback`);
    for (let i = 0; i < 100; i++) {
      const observation = t.tick();
      assert(observation.projectiles.every(p => p.ownerUid !== t.owner.uid),
        `${mode}: no transient generic projectile on denied/interrupted frame${i + 1}`);
    }
    assert(t.events.length === 0 && t.state.projectiles.every(p => p.ownerUid !== t.owner.uid),
      `${mode}: no row4 shot, explosion, or generic damaging fallback`);
    assert(t.target.hp === hp, `${mode}: no hidden damage`);
    assert(mode === 'depleted' ? t.allocations.length === 1 && !t.allocations[0]!.accepted : t.allocations.length === 0,
      `${mode}: only admitted-but-depleted fire gate attempts allocation`);
    t.inputs.p1.special = false; t.tick();
    assert(t.events.length === 0, `${mode}: release does not retry a denied action`);
  }
  const recoil = setup(); recoil.press(); recoil.driver.actor.dashStrength1d0f = 1;
  for (let i = 0; i < 16; i++) recoil.tick();
  assert(recoil.events.length === 1 && recoil.events[0]!.hSpeed === 10 && recoil.events[0]!.yVel === 15,
    'nonzero source dashStrength seeds recoil only at the authored fire gate');

  const windup = setup(); windup.target.pos = v(20, 0, 0);
  const hp = windup.target.hp;
  windup.press();
  for (let i = 0; i < 15; i++) windup.tick();
  assert(windup.target.hp === hp && windup.events.length === 0,
    'close target receives no speculative body/effect damage during X windup');
  windup.owner.state = 'hit'; windup.owner.cooldowns['hitstun'] = 20;
  for (let i = 0; i < 100; i++) windup.tick();
  assert(windup.target.hp === hp && windup.events.length === 0, 'interrupt does not leave hidden delayed damage');
}

function testSavedAimAndMuzzle(): void {
  const test = setup();
  test.press();
  assert(test.owner.gatlingSavedAim?.targetUid === test.target.uid && test.owner.gatlingSavedAim.pos.z === 6000,
    'admission captures source saved target aim');
  test.target.pos = v(6000, 0, 0);
  for (let i = 0; i < 16; i++) test.tick();
  const primary = primaryFor(test);
  assert(primary.gatlingSource?.kind === 'primary', 'saved-aim fixture primary');
  assert(Math.abs(primary.gatlingSource.flight.vel.x) < 1 && primary.gatlingSource.flight.vel.z > 20,
    `constructor aims toward admission snapshot, not target moved during windup: ${JSON.stringify(primary.vel)}`);
  const bind = gatlingMuzzle(v(0, 0, 0), 0);
  near(bind.x, 132.59280443191528, 'static joint11 plus row4 local-X offset');
  near(bind.y, 136.1260986328125, 'static joint11 muzzle Y');
  near(bind.z, -.000013937185372014937, 'static joint11 muzzle Z');
  const transformed = gatlingMuzzle(v(10, 20, 30), Math.PI / 2, 2);
  near(transformed.x, 10 + bind.z * 2, 'static muzzle yaw/scale X');
  near(transformed.y, 20 + bind.y * 2, 'static muzzle yaw/scale Y');
  near(transformed.z, 30 - bind.x * 2, 'static muzzle yaw/scale Z');
}

function testTargetPointerSnapshot(): void {
  const relock = setup(undefined, true);
  assert(relock.other, 'two distinct target UIDs for real switch-lock input');
  relock.press();
  assert(relock.owner.gatlingSavedAim?.targetUid === relock.target.uid, 'admission snapshots target A identity');
  relock.inputs.p1.switchLock = true; relock.tick();
  relock.inputs.p1.switchLock = false;
  assert(relock.owner.targetLockState?.activeTargetUid === relock.other.uid, 'R press actually selects target B during windup');
  for (let i = 0; i < 15; i++) relock.tick();
  const primary = primaryFor(relock);
  assert(primary.gatlingSource?.kind === 'primary', 'relock source primary');
  assert(primary.gatlingSource.flight.targetUid === relock.target.uid && primary.aimedTargetUid === relock.target.uid,
    'constructor copies admitted source target pointer A, never the newer active lock B');

  const acquire = setup(undefined, false, true);
  // Start the existing enemy near the end of its death lifecycle. Battle deploys
  // the real reserved replacement during the source windup; no target pointer is injected.
  acquire.target.hp = 0; acquire.target.state = 'death'; acquire.target.stateTime = STATE.DEATH_DURATION - 2;
  acquire.press();
  assert(acquire.owner.gatlingSavedAim?.targetUid === null && acquire.owner.targetLockState?.activeTargetUid === null,
    'no-target X admission really has no selectable enemy');
  for (let i = 0; i < 5; i++) acquire.tick();
  const replacement = acquire.state.borgs.find(b => b.ownerPlayer === 'p2' && b.uid !== acquire.target.uid && b.alive);
  assert(replacement && acquire.owner.targetLockState?.activeTargetUid === replacement.uid,
    'Battle deploys and acquires the actual reserved replacement during windup');
  for (let i = 0; i < 11; i++) acquire.tick();
  const untracked = primaryFor(acquire);
  assert(untracked.gatlingSource?.kind === 'primary', 'no-target admission source primary');
  assert(untracked.gatlingSource.flight.targetUid === null && untracked.aimedTargetUid === null,
    'no-target admission cannot silently acquire a constructor target later');

  const lost = setup(undefined, true);
  assert(lost.other, 'remaining enemy after captured target dies');
  lost.press();
  assert(lost.owner.gatlingSavedAim?.targetUid === lost.target.uid, 'target-loss fixture admitted A');
  lost.target.hp = 0; lost.target.state = 'death'; lost.target.stateTime = 0;
  lost.tick();
  assert(lost.owner.targetLockState?.activeTargetUid === lost.other.uid, 'Battle reacquires live B after A dies');
  for (let i = 0; i < 15; i++) lost.tick();
  const orphaned = primaryFor(lost);
  assert(orphaned.gatlingSource?.kind === 'primary', 'captured-target-loss source primary');
  assert(orphaned.gatlingSource.flight.targetUid === null && orphaned.aimedTargetUid === null,
    'invalid captured pointer clears without replacing it with newly selected B');
}

function waitForExplosion(test: Fixture, frames = 580): Projectile {
  const despawns: unknown[] = [];
  for (let i = 0; i < frames; i++) {
    const explosion = test.state.projectiles.find(p => p.gatlingSource?.kind === 'explosion');
    if (explosion) return explosion;
    despawns.push(...test.tick().projectileDespawns);
  }
  throw new Error(`[gatlingBattle] input-created projectile did not produce an impact explosion: ${JSON.stringify({ despawns, projectiles: test.state.projectiles })}`);
}

/** Hold a victim in the declared host collision volume, so knockback/invincibility
 * cannot conceal an accidental repeated damage application in the next frame. */
function placeVictim(victim: BorgRuntime, pos: Projectile['pos']): void {
  victim.pos = { ...pos }; victim.vel = v(0, 0, 0); victim.grounded = false;
  victim.state = 'idle'; victim.stateTime = 0; victim.invincTimer = 0;
  victim.freezeFrames = 0; victim.cooldowns['hitstun'] = 0;
}

function testTerrainExplosionAndDamage(): void {
  const test = setup(floorAndWall(350), true);
  const primary = launch(test);
  const explosion = waitForExplosion(test);
  const first = test.battle.observe();
  assert(explosion.gatlingSource?.kind === 'explosion', 'terrain impact creates row13 child');
  const child = explosion.gatlingSource;
  assert(primary.despawnReason === 'hit-terrain' && first.projectileDespawns.some(p => p.uid === primary.uid && p.reason === 'hit-terrain'),
    'real wall crossing records primary terrain despawn in public observation');
  near(explosion.pos.z, 350, 'explosion spawns at actual terrain intersection');
  assert(first.projectiles.length === 1 && first.projectiles[0]!.uid === explosion.uid,
    'terrain replacement exposes one child and no hidden generic projectile');
  assert(explosion.romShotKind === 107 && explosion.damageRecord?.hpDamage === 20 && explosion.damageRecord.index === 20,
    'row13 resolves global comhit107 and global damage20 rather than family damage');
  assert(child.age === 0 && child.phase === 'expand' && child.hitUids.length === 0 && explosion.flightVisual?.bankTexId === 22,
    'constructor observation starts global22 expansion before any damage step');
  near(child.scale, .01, 'constructor child scale');
  assert(test.cues.filter(c => c === 12).length === 1, 'impact emits source explosion cue12 exactly once');
  assert(test.other, 'second live target for multi-victim explosion');
  const victims = [test.target, test.other];
  const before = victims.map(b => b.hp);
  const hitsBefore = first.telemetry.hitsByTeam[0] ?? 0;
  const damageBefore = first.telemetry.damageByTeam[0] ?? 0;
  const ownerHp = test.owner.hp;
  const inside = () => victims.forEach((b, i) => placeVictim(b, v(explosion.pos.x + (i === 0 ? -20 : 20), explosion.pos.y, explosion.pos.z)));
  inside(); test.tick();
  assert(victims.every((b, i) => b.hp < before[i]!), 'one actual expansion step damages both victims');
  assert(Number(child.hitUids.length) === 2 && new Set(child.hitUids).size === 2, 'same-frame multiple targets each enter once-per-explosion hit set');
  const after = victims.map(b => b.hp);
  const observed = test.battle.observe();
  assert((observed.telemetry.hitsByTeam[0] ?? 0) === hitsBefore + 2,
    'two real damage connections reach Battle telemetry');
  assert((observed.telemetry.damageByTeam[0] ?? 0) - damageBefore === before.reduce((sum, hp, i) => sum + hp - after[i]!, 0),
    'Battle damage telemetry matches the actual two HP reductions');
  assert(test.owner.hp === ownerHp, 'explosion does not hit its owner');
  assert(first.projectiles[0]!.gatlingSource?.kind === 'explosion' && first.projectiles[0]!.gatlingSource.age === 0 &&
    first.projectiles[0]!.gatlingSource.hitUids.length === 0,
    'previous observation does not mutate when source child ages or gains hit targets');
  for (let age = 2; age <= 12; age++) {
    inside(); test.tick();
    assert(child.age === age && child.phase === 'expand', `expansion remains active through source update${age}`);
    near(child.scale, .01 + .1 * age, `source expansion scale update${age}`);
    assert(victims.every((b, i) => b.hp === after[i]), 'cleared invincibility and repeated overlap cannot rehit an already recorded victim');
  }
  inside(); test.tick();
  assert(Number(child.age) === 13 && String(child.phase) === 'hold' && child.hold === 4, 'thirteenth expansion update enters four-frame hold');
  near(child.scale, 1.25, 'expansion clamps at source owner-scale target');
  for (let i = 1; i <= 3; i++) {
    inside(); test.tick();
    assert(String(child.phase) === 'hold' && child.hold === 4 - i, 'hold retains collision for first three subsequent updates');
  }
  inside(); test.tick();
  assert(String(child.phase) === 'tail' && Number(explosion.flightVisual?.bankTexId) === 23 && child.tailAge === 0,
    'fourth hold update switches to non-damaging global23 tail');
  assert(test.cues.filter(c => c === 12).length === 1, 'tail transition does not replay explosion sound');
  // A new UID inside a visual tail must not turn the fading art back into damage.
  child.hitUids.length = 0;
  for (let i = 1; i <= 30; i++) {
    inside(); test.tick();
    assert(victims.every((b, n) => b.hp === after[n]), 'visual tail remains non-damaging even without prior-hit IDs');
    assert(test.battle.observe().projectiles.some(p => p.uid === explosion.uid), 'source tail persists through update30');
  }
  test.tick();
  assert(!test.battle.observe().projectiles.some(p => p.uid === explosion.uid) &&
    test.battle.observe().projectileDespawns.some(p => p.uid === explosion.uid && p.reason === 'expired'),
    'tail expires once through public despawn observation');
}

function testContactExplosion(): void {
  const test = setup(); test.target.pos = v(0, 0, 700);
  const hp = test.target.hp;
  const primary = launch(test);
  const explosion = waitForExplosion(test);
  const observed = test.battle.observe();
  assert(primary.despawnReason === 'hit-target' && test.target.hp < hp,
    'actual X press and natural flight reach target damage before contact replacement');
  assert(explosion.gatlingSource?.kind === 'explosion' && explosion.gatlingSource.age === 0,
    'contact creates the same deferred-update explosion child');
  assert(observed.projectileDespawns.some(p => p.uid === primary.uid && p.reason === 'hit-target'),
    'public observation distinguishes target impact from terrain impact');
  assert(test.cues.filter(c => c === 12).length === 1, 'target contact also emits one source cue12');
}

function launchIntoConstructorWall(tier = 16) {
  const collision = floorAndWall(350);
  collision.triangles.pop();
  const test = setup(collision);
  test.owner.paramTier.tier = tier;
  let wallZ = 0, ownerScale = 0;
  const spawn = test.driver.ctx.onFamilyProjectile!;
  test.driver.ctx.onFamilyProjectile = (actor, address, row) => {
    // Place fixture geometry against the live muzzle immediately before the
    // source constructor. The real input, source spawn, and Battle sweep run unchanged.
    ownerScale = actor.modelScale * actor.sizeScale;
    wallZ = gatlingMuzzle(actor.pos, actor.heading * Math.PI * 2 / 65536, ownerScale).z + 20;
    collision.triangles.push(floorAndWall(wallZ).triangles[2]!);
    spawn(actor, address, row);
  };
  test.press();
  for (let i = 0; i < 40 && test.events.length === 0; i++) test.tick();
  const explosion = test.state.projectiles.find(p => p.gatlingSource?.kind === 'explosion');
  assert(explosion, 'constructor muzzle-to-endpoint sweep cannot tunnel through a close wall');
  near(explosion.pos.z, wallZ, 'constructor collision child starts at wall, not already-advanced endpoint');
  return { test, explosion, ownerScale };
}

function testNonImpactTermination(): void {
  for (const mode of ['expired', 'out-of-bounds', 'owner-dead'] as const) {
    const test = setup(); const primary = launch(test);
    assert(primary.gatlingSource?.kind === 'primary', `${mode}: source fixture`);
    const flight = primary.gatlingSource.flight;
    if (mode === 'expired') flight.life = 1;
    if (mode === 'owner-dead') { test.owner.alive = false; test.owner.hp = 0; }
    // Start from an input-created source projectile, then isolate the otherwise
    // unreachable boundary on the shared live lifecycle seam, not a fabricated shot.
    const result = stepProjectiles([primary], [], new Map(), new Map(test.state.borgs.map(b => [b.uid, b])),
      mode === 'out-of-bounds' ? { bounds: { minX: -1, maxX: 1, minZ: -1, maxZ: 1 }, collision: null,
        onSourceCue: cue => test.cues.push(cue) } : undefined);
    assert(result.length === 0 && primary.despawnReason === mode, `${mode}: primary disappears with exact reason`);
    assert(test.cues.filter(c => c === 12).length === 0, `${mode}: cannot create an impact explosion or cue`);
  }

  launchIntoConstructorWall();
}

function testOwnerScaleIndependence(): void {
  const { test, explosion, ownerScale } = launchIntoConstructorWall(17);
  assert(explosion.gatlingSource?.kind === 'explosion', 'scaled-owner input-created explosion');
  const child = explosion.gatlingSource;
  near(ownerScale, 1.4, 'non-default source owner scale reaches constructor');
  near(child.ownerScale, ownerScale, 'explosion captures owner scale, not primary draw scale2');
  near(child.scale, .01 * ownerScale, 'explosion initial scale excludes primary factor2');
  near(child.velocity, .1 * ownerScale, 'explosion expansion uses source owner scale');
  test.owner.paramTier.tier = 16;
  for (let i = 0; i < 13; i++) test.tick();
  near(child.scale, 1.25 * ownerScale, 'existing explosion keeps captured owner scale after owner changes size');
  near(explosion.hitRadius, 310 * 1.25 * ownerScale, 'host extent scales once, independently of primary draw2');
}

export function runGatlingBattleSelfTest(): void {
  runGatlingProjectileSelfTest();
  testAdmissionAndAmmo();
  testNegativeControls();
  testSavedAimAndMuzzle();
  testTargetPointerSnapshot();
  testTerrainExplosionAndDamage();
  testContactExplosion();
  testNonImpactTermination();
  testOwnerScaleIndependence();
  console.log('Gatling source-X Battle integration: passed');
}
