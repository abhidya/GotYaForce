/** Real Z -> X coverage. Actor relocation/injury are fixture setup; action admission,
 * source contacts and healing must all run through Battle.step, never injected hits.
 * The bridge currently approximates HIT geometry with a root-radius check, so the
 * close fixture is 50 units away. 180/360 tick loops are observation budgets, not
 * claims about recovered animation timing. Far remains explicitly unsupported. */
import { battleStateForSelfcheck, createBattle } from './battle.js';
import { activeSourceTargetUid } from './combat.js';
import { RomDriverBridge } from './bridge.js';
import { getNurseXState } from './nurseX.js';
import attackHits from './data/attackHitTables.json' with { type: 'json' };
import { emptyInput } from './types.js';
import type { BorgStats } from './stats.js';
import borgsData from '../../assets/data/borgs.json' with { type: 'json' };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const ids = ['pl0900', 'pl0908', 'pl090d'] as const;
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[nurseBattle] ${message}`);
}
function setup(id: string = 'pl0900', range = 50, airborne = false) {
  const battle = createBattle({ stageId: 'st00', bounds: { x: 10000, z: 10000 }, forces: [
    { team: 0, ownerPlayer: 'p1', borgIds: [id] },
    { team: 0, ownerPlayer: 'p2', borgIds: ['pl0615'] },
    { team: 1, ownerPlayer: 'p3', borgIds: ['pl0008'] },
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput(), p3: emptyInput() };
  const tick = () => battle.step(1 / 60, inputs);
  for (let i = 0; i < 100; i++) tick();
  const state = battleStateForSelfcheck(battle);
  const [owner, target, enemy] = state.borgs;
  assert(owner && target && enemy, 'fixture roster');
  assert(owner.romDriver instanceof RomDriverBridge, 'live ROM bridge');
  const driver = owner.romDriver;
  owner.pos = { x: 0, y: 0, z: 0 }; owner.vel = { x: 0, y: 0, z: 0 }; owner.rotY = 0;
  target.pos = { x: 0, y: 0, z: range }; target.vel = { x: 0, y: 0, z: 0 };
  enemy.pos = { x: 4000, y: 0, z: 4000 }; target.maxHp = 1000; target.hp = 100;
  if (airborne) {
    // Establish flight through the player's real jump input, then acquire held Z.
    inputs.p1.jump = true; tick(); inputs.p1.jump = false;
    assert(!owner.grounded && owner.pos.y > 0, `${id}: real jump establishes flight`);
  }
  inputs.p1.allyLock = true; tick();
  assert(activeSourceTargetUid(owner) === target.uid, 'real Z selects injured ally');
  if (!airborne) for (let i = 0; i < 4; i++) tick();
  const armedKinds: number[] = [];
  const arm = driver.ctx.onArmHit!;
  driver.ctx.onArmHit = (actor, kind, p1, p2) => {
    armedKinds.push(kind); arm(actor, kind, p1, p2);
  };
  const allocations: { slot: number; count: number; accepted: boolean }[] = [];
  const allocate = driver.ctx.onAllocateResource!;
  driver.ctx.onAllocateResource = (actor, slot, count, mode) => {
    const accepted = allocate(actor, slot, count, mode);
    allocations.push({ slot, count, accepted }); return accepted;
  };
  const animations: { group: number; slot: number }[] = [];
  const play = driver.ctx.onPlayAnim!;
  driver.ctx.onPlayAnim = (actor, group, slot, blend) => {
    animations.push({ group, slot }); play(actor, group, slot, blend);
  };
  const press = () => { inputs.p1.special = true; return tick(); };
  const release = () => { inputs.p1.special = false; return tick(); };
  return { battle, state, owner, target, enemy, driver, inputs, tick, press, release, allocations, armedKinds, animations };
}
type Fixture = ReturnType<typeof setup>;
function advance(t: Fixture, frames = 180): void { for (let i = 0; i < frames; i++) t.tick(); }
function testRealInputHealing(): void {
  for (const id of ids) {
    const t = setup(id); const hp = t.target.hp;
    const xCell = t.owner.weaponCells![1]!, xBefore = xCell.cur;
    t.press();
    assert(t.owner.command?.type === 2 && t.owner.command.actionIndex === 2 && t.owner.command.exact,
      `${id}: X selects exact action2`);
    assert(t.owner.command.variantIndex === 0, `${id}: grounded X selects variant0`);
    assert(xCell.cur === xBefore - 1 && xCell.timer > 0,
      `${id}: real admission spends exactly one X and starts source refill debt`);
    const bAmmo = t.owner.weaponCells![0]!.cur;
    const enemyHp = t.enemy.hp;
    advance(t);
    assert(t.enemy.hp === enemyHp && t.owner.weaponCells![0]!.cur === bAmmo,
      `${id}: allied healing leaves distant enemy and B ammo untouched`);
    const amount = id === 'pl0908' ? 400 : 200;
    assert(t.target.hp === Math.min(t.target.maxHp, hp + amount),
      `${id}: real Z->X must reach HP restoration (${t.target.hp}, expected ${Math.min(t.target.maxHp, hp + amount)})`);
    assert(t.owner.weaponCells![2] === xCell, `${id}: source cell2 aliases HUD X`);
    assert(t.allocations.length === 1 && t.allocations[0]!.slot === 2 &&
      t.allocations[0]!.count === 1 && t.allocations[0]!.accepted,
      `${id}: exactly one accepted source cell2 allocation: ${JSON.stringify(t.allocations)}`);
    if (xCell.max > 0) assert(xCell.cur <= xBefore, `${id}: source allocation never creates ammo`);
    assert(t.armedKinds.filter(kind => kind === 4).length === 1,
      `${id}: actual source action arms one healing kind4 window`);

  }
}
function testAirborneHealing(): void {
  for (const id of ids) {
    const t = setup(id, 50, true), cell = t.owner.weaponCells![1]!;
    const before = cell.cur, bAmmo = t.owner.weaponCells![0]!.cur, enemyHp = t.enemy.hp;
    t.press();
    assert(t.owner.command?.exact && t.owner.command.type === 2 &&
      t.owner.command.actionIndex === 2 && t.owner.command.variantIndex === 1,
      `${id}: jump -> held Z -> X selects exact airborne variant1, not variant4`);
    assert((t.driver.actor.controlWord & 0x40) !== 0, `${id}: airborne seed sets source control40`);
    assert(t.driver.actor.fbCue === 45, `${id}: airborne admission selects cue45, not grounded cue44`);
    assert(cell.cur === before - 1 && cell.timer > 0,
      `${id}: airborne admission spends exactly one X and starts refill debt`);
    const table = attackHits.borgs[id];
    assert(table.kinds['4'][0] === 6 && table.records['6'].damageRecordIndex === (id === 'pl0908' ? 8 : 4),
      `${id}: kind4 selects the same-family healing damage record`);
    let contacts = 0, sawRecovery = false, airRecoveryTicks = 0, sawAirRecoveryWait = false;
    for (let i = 0; i < 180; i++) {
      const hp = t.target.hp;
      const beforeState = getNurseXState(t.driver.actor);
      if (beforeState?.subphase === 2) airRecoveryTicks++;
      t.tick();
      const state = getNurseXState(t.driver.actor);
      if (state?.subphase === 2) {
        sawAirRecoveryWait = true;
        assert(!t.owner.grounded, `${id}: airborne aux6 selects timer recovery`);
      }
      if (t.target.hp !== hp) {
        contacts++;
        assert(!t.owner.grounded && t.owner.pos.y > 0, `${id}: healing contact really occurs airborne`);
        assert(state && state.stream.frame >= 9 && state.stream.frame <= 10,
          `${id}: real contact occurs in authored frame9-10 HIT window`);
      }
      if (state?.stream.stage === 'recover') {
        sawRecovery = true;
        assert((t.driver.actor.controlWord & 0x40) === 0, `${id}: recovery stream clears source control40`);
      }
      assert(t.state.projectiles.every(p => p.ownerUid !== t.owner.uid), `${id}: airborne X has no fallback projectile`);
    }
    assert(contacts === 1 && t.target.hp === (id === 'pl0908' ? 500 : 300),
      `${id}: airborne source contact restores exactly ${id === 'pl0908' ? 400 : 200} HP once`);
    assert(sawAirRecoveryWait && airRecoveryTicks === 20,
      `${id}: airborne recovery waits authored 20 ticks, not grounded HOLD60 (${airRecoveryTicks})`);
    assert(sawRecovery && t.animations.some(a => a.group === 4 && a.slot === 3),
      `${id}: airborne continuation reaches actual recovery animation`);
    assert(!t.owner.cooldowns['romSpecialActive'] && t.owner.state !== 'special',
      `${id}: airborne recovery releases action ownership`);
    assert(t.allocations.length === 1 && t.allocations[0]!.accepted &&
      t.allocations[0]!.slot === 2 && t.allocations[0]!.count === 1,
      `${id}: airborne action allocates source cell2 exactly once`);
    assert(t.owner.weaponCells![2] === cell && t.armedKinds.filter(k => k === 4).length === 1,
      `${id}: airborne kind4 uses aliased X cell, armed once`);
    assert(t.owner.weaponCells![0]!.cur === bAmmo && t.enemy.hp === enemyHp,
      `${id}: airborne healing leaves B ammo and distant enemy untouched`);
    advance(t, cell.refillParam + 180);
    assert(cell.cur === cell.max && cell.timer === 0, `${id}: airborne expenditure refills exactly`);
    assert(t.allocations.length === 1, `${id}: held airborne X never repeats across refill`);
  }
}
function jumpAgain(t: Fixture): void {
  returnToCloseRange(t); t.release();
  t.inputs.p1.jump = true; t.tick(); t.inputs.p1.jump = false;
  t.tick();
  assert(!t.owner.grounded && activeSourceTargetUid(t.owner) === t.target.uid,
    'fresh jump retains held-Z ally lock');
}
function testAirborneInterruptionAndEdges(): void {
  for (const id of ids) {
    const interrupted = setup(id, 50, true); interrupted.press();
    for (let i = 0; i < 30 && !interrupted.armedKinds.includes(4); i++) interrupted.tick();
    assert(interrupted.armedKinds.includes(4) && interrupted.target.hp === 100,
      `${id}: interrupt a real armed airborne window before contact`);
    interrupted.owner.state = 'hit'; interrupted.owner.stateTime = 0;
    interrupted.owner.cooldowns['hitstun'] = 20;
    advance(interrupted, 360);
    assert(interrupted.target.hp === 100, `${id}: interrupted airborne action leaves no stale contact`);
    assert(!getNurseXState(interrupted.driver.actor), `${id}: interruption clears airborne continuation`);
    const held = setup(id, 50, true); held.press(); advance(held, 360);
    const healed = held.target.hp;
    assert(healed === (id === 'pl0908' ? 500 : 300), `${id}: first airborne press heals`);
    advance(held, 360);
    assert(held.target.hp === healed && held.allocations.length === 1,
      `${id}: held airborne X cannot repeat or spend again`);
    jumpAgain(held); held.press();
    assert(held.owner.command?.variantIndex === 1, `${id}: airborne repress still selects variant1`);
    advance(held);
    assert(Number(held.allocations.length) === 2 && held.target.hp === Math.min(1000, healed + (id === 'pl0908' ? 400 : 200)),
      `${id}: fresh airborne repress performs one new heal`);
    const tap = setup(id, 50, true); tap.press(); tap.release(); advance(tap);
    assert(tap.target.hp === (id === 'pl0908' ? 500 : 300), `${id}: airborne tap completes continuation`);
  }
}
function testClampAndNoRevive(): void {
  for (const id of ids) for (const airborne of [false, true]) {
    const full = setup(id, 50, airborne); full.target.hp = full.target.maxHp - 1;
    full.press(); advance(full);
    assert(full.target.hp === full.target.maxHp, `${id}: real contact cannot overheal`);
    const dead = setup(id, 50, airborne); dead.press(); dead.target.hp = 0;
    advance(dead);
    assert(dead.target.hp === 0 && !dead.target.alive, `${id}: target lost during action cannot revive`);
  }
}
function testUnsupportedAdmissions(): void {
  for (const id of ids) for (const airborne of [false, true]) for (const mode of ['far', 'enemy', 'busy'] as const) {
    const t = setup(id, mode === 'far' ? 4000 : 50, airborne);
    if (mode === 'enemy') {
      t.inputs.p1.allyLock = false; t.tick();
      assert(activeSourceTargetUid(t.owner) === t.enemy.uid, 'releasing Z restores enemy lock');
    }
    if (mode === 'busy') { t.owner.state = 'hit'; t.owner.stateTime = 0; t.owner.cooldowns['hitstun'] = 20; }
    const hp = t.target.hp, enemyHp = t.enemy.hp;
    const ammo = t.owner.weaponCells!.map(c => c.cur);
    t.press();
    for (let i = 0; i < 180; i++) {
      t.tick();
      assert(t.state.projectiles.every(p => p.ownerUid !== t.owner.uid), `${id}/${mode}: no generic fallback projectile`);
    }
    assert(t.target.hp === hp && t.enemy.hp === enemyHp, `${id}/${mode}: no fabricated healing or damage`);
    assert(t.owner.weaponCells!.every((c, i) => c.cur === ammo[i]), `${id}/${mode}: no fabricated ammo use`);
  }
}
function testTargetLeavesContact(): void {
  for (const id of ids) for (const airborne of [false, true]) {
    const t = setup(id, 50, airborne); t.press();
    t.target.pos.y = 1000;
    for (let i = 0; i < 60; i++) {
      // Keep the live recipient above the 3D contact volume, not merely above the
      // admission check. This manipulates geometry, never a hit or HP outcome.
      t.target.pos.y = 1000; t.target.vel.y = 0; t.tick();
    }
    assert(t.target.hp === 100, `${id}: target leaving vertically cannot be hit by XZ-only contact`);
  }
}
function testEmptyAmmo(): void {
  for (const id of ids) for (const airborne of [false, true]) {
    const t = setup(id, 50, airborne), cell = t.owner.weaponCells![1]!;
    if (cell.max === 0) continue; // Zero-capacity source rows do not have a finite magazine to deplete.
    cell.cur = 0; cell.timer = cell.refillParam;
    t.press(); advance(t);
    assert(t.target.hp === 100, `${id}: empty magazine cannot heal`);
    assert(t.state.projectiles.length === 0, `${id}: empty magazine cannot fall back to generic X`);
    advance(t, cell.refillParam + 180);
    assert(t.target.hp === 100, `${id}: held denied press is not queued across refill`);
    assert(cell.cur === cell.max && cell.timer === 0, `${id}: completed source refill restores magazine exactly`);
    if (airborne) jumpAgain(t); else t.release();
    t.press(); advance(t);
    assert(Number(t.target.hp) === (id === 'pl0908' ? 500 : 300), `${id}: fresh press after refill can heal`);
  }
}
function returnToCloseRange(t: Fixture): void {
  // Reset only geometry between completed actions; hit reaction can displace the
  // recipient. The next action still requires an actual fresh input edge.
  t.owner.pos = { x: 0, y: 0, z: 0 }; t.owner.vel = { x: 0, y: 0, z: 0 }; t.owner.rotY = 0;
  t.target.pos = { x: 0, y: 0, z: 50 }; t.target.vel = { x: 0, y: 0, z: 0 };
  for (let i = 0; i < 4; i++) t.tick();
}
function testInterruptionAndInputEdges(): void {
  for (const id of ids) {
    const interrupted = setup(id); interrupted.press();
    interrupted.owner.state = 'hit'; interrupted.owner.stateTime = 0;
    interrupted.owner.cooldowns['hitstun'] = 20;
    advance(interrupted);
    assert(interrupted.target.hp === 100, `${id}: interruption before contact leaves no ghost heal`);
    const held = setup(id); held.press(); advance(held);
    const healed = held.target.hp;
    const allocations = held.allocations.length;
    advance(held, 360);
    assert(held.allocations.length === allocations, `${id}: held X cannot spend again`);
    assert(held.target.hp === healed, `${id}: held X never repeats`);
    returnToCloseRange(held); held.release(); held.press(); advance(held);
    assert(held.allocations.length === allocations + 1, `${id}: fresh press allocates once`);
    assert(held.target.hp === Math.min(held.target.maxHp, healed + (id === 'pl0908' ? 400 : 200)),
      `${id}: fresh repress starts a new heal`);
    const tap = setup(id); tap.press(); tap.release(); advance(tap);
    assert(tap.target.hp === (id === 'pl0908' ? 500 : 300), `${id}: tap completes source action`);
  }
}
export function runNurseBattleSelfTest(): void {
  testRealInputHealing();
  testAirborneHealing();
  testAirborneInterruptionAndEdges();
  testClampAndNoRevive();
  testUnsupportedAdmissions();
  testInterruptionAndInputEdges();
  testEmptyAmmo();
  testTargetLeavesContact();
  console.log('[nurseBattle] PASS: real ground/air Z -> X healing');
}
