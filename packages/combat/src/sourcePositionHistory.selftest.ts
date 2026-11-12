/** Source actor history, exercised through the real Battle frame/admission seams.
 * zz_005685c_ (chunk_0007.c:201-206), spawn initialization (699-704), and
 * FUN_80054070 (chunk_0006.c:6965-6967). No target position belongs in these fields.
 */
import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { RomDriverBridge } from "./bridge.js";
import { STATE } from "./constants.js";
import type { RomActor, Vec3 } from "./rom/actor.js";
import type { BorgStats } from "./stats.js";
import { emptyInput, type StageCollision } from "./types.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

const stats = (borgsData as { borgs: BorgStats[] }).borgs;
const v = (x: number, y: number, z: number): Vec3 => ({ x, y, z });
const floor: StageCollision = { triangles: [
  [v(-20000, 0, -20000), v(20000, 0, -20000), v(20000, 0, 20000)],
  [v(-20000, 0, -20000), v(20000, 0, 20000), v(-20000, 0, 20000)],
].map((vertices, index) => ({ index, layerIndex: 0, marker: 0xcccccccc,
  vertices: vertices as [Vec3, Vec3, Vec3], normal: v(0, 1, 0), planeD: 0,
  bounds2d: { minX: -20000, maxX: 20000, minZ: -20000, maxZ: 20000 },
})) };

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[sourcePositionHistory] ${message}`);
}
function same(actual: Vec3, expected: Vec3, message: string): void {
  assert(["x", "y", "z"].every(axis => Math.abs(actual[axis as keyof Vec3] - expected[axis as keyof Vec3]) < 1e-7),
    `${message}: ${JSON.stringify(actual)} != ${JSON.stringify(expected)}`);
}
function setup(id = "pl0100", range = 6000, replacement = false) {
  const battle = createBattle({ stageId: "st00", bounds: { x: 20000, z: 20000 }, collision: floor,
    forces: [
      { team: 0, ownerPlayer: "p1", borgIds: replacement ? [id, id] : [id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
    ] }, stats);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find(b => b.ownerPlayer === "p1")!;
  const target = state.borgs.find(b => b.ownerPlayer === "p2")!;
  assert(owner.romDriver instanceof RomDriverBridge, `${id}: bridge attached`);
  const driver = owner.romDriver;
  same(driver.actor.pos, owner.pos, "attachment seeds current position");
  same(driver.actor.savedGroundPos, owner.pos, "attachment seeds +2c from spawn");
  same(driver.actor.targetCache5e8, owner.pos, "attachment seeds +5e8 from spawn");
  assert(driver.actor.pos !== owner.pos && driver.actor.savedGroundPos !== owner.pos
    && driver.actor.targetCache5e8 !== driver.actor.savedGroundPos, "history samples do not alias live position");
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  const tick = () => battle.step(1 / 60, inputs);
  for (let i = 0; i < 100; i++) tick();
  owner.pos = v(120, 0, -70); owner.vel = v(0, 0, 0); owner.rotY = 0; owner.grounded = true;
  target.pos = v(120, 0, range); target.vel = v(0, 0, 0);
  // Fixture relocation is real movement to the history sampler. Let both samples
  // settle normally; production must never reset history on arbitrary state changes.
  for (let i = 0; i < 4; i++) tick();
  return { battle, state, owner, target, driver, inputs, tick };
}

function testStationaryFamilies(): void {
  // All four gunman handlers plus unrelated Girl and Knight handlers consume +5e8.
  for (const id of ["pl0100", "pl0108", "pl0102", "pl0101", "pl0104", "pl0305", "pl0208"]) {
    for (const range of [400, 6000]) {
      const t = setup(id, range);
      const before = { ...t.owner.pos };
      t.inputs.p1.special = true; t.tick();
      assert(t.owner.state === "special", `${id}: actual input admitted special`);
      same(t.driver.actor.targetCache5e8, before, `${id}: target range does not alter own history`);
      same(t.driver.actor.motion, v(0, 0, 0), `${id}: stationary admission has no false target-distance carry`);
      same(t.owner.pos, before, `${id}: supported floor cannot hide a false teleport`);
    }
  }
}

function testMovementAndAirborneHistory(): void {
  for (const airborne of [false, true]) {
    const t = setup();
    if (airborne) { t.owner.pos.y = 500; t.owner.grounded = false; t.owner.vel.y = 3; }
    t.inputs.p1.moveX = 1;
    let priorStart = { ...t.driver.actor.savedGroundPos };
    for (let i = 0; i < 5; i++) {
      const frameStart = { ...t.owner.pos };
      t.tick();
      same(t.driver.actor.savedGroundPos, frameStart, "inactive driver records frame start, including airborne Y");
      same(t.driver.actor.targetCache5e8, priorStart, "older own sample advances during ordinary movement");
      priorStart = frameStart;
    }
    const actionStart = { ...t.owner.pos };
    let entry: { pos: Vec3; older: Vec3; previous: Vec3 } | null = null;
    const root = t.driver.actor.rootAction!;
    t.driver.actor.rootAction = (actor: RomActor) => {
      entry = { pos: { ...actor.pos }, older: { ...actor.targetCache5e8 }, previous: { ...actor.savedGroundPos } };
      root(actor);
    };
    t.inputs.p1.special = true; t.tick();
    assert(entry, "actual movement-to-attack admission invoked family root");
    const sample = entry as { pos: Vec3; older: Vec3; previous: Vec3 };
    same(sample.older, priorStart, "admission retains the older pre-movement frame sample");
    same(sample.previous, actionStart, "admission does not overwrite +2c after generic movement");
    same(t.driver.actor.motion, v((sample.pos.x - priorStart.x) * .95,
      (sample.pos.y - priorStart.y) * .95, (sample.pos.z - priorStart.z) * .95),
    "moving attack preserves source movement carry rather than zeroing it");
    assert(t.driver.actor.motion.x > 0, "source carry remains nonzero after real walking");
    if (airborne) assert(sample.previous.y > 100 && sample.older.y > 100, "air samples are not last-grounded positions");
  }
}

function testOncePerFrameAndInterrupt(): void {
  const t = setup();
  const frame = t.state.frame;
  const priorStart = { ...t.driver.actor.savedGroundPos };
  t.owner.pos.x += 7;
  const frameStart = { ...t.owner.pos };
  t.driver.beginFrame(t.owner, frame);
  t.owner.pos.x += 9;
  t.driver.syncIn(t.owner, t.state.borgs);
  t.driver.beginFrame(t.owner, frame);
  t.target.pos.z += 1000;
  t.driver.syncIn(t.owner, t.state.borgs);
  assert(t.driver.tryStartXSpecial(t.owner, t.state.borgs), "first same-frame admission handled");
  assert(!t.driver.tryStartXSpecial(t.owner, t.state.borgs), "second same-frame admission refused");
  same(t.driver.actor.savedGroundPos, frameStart, "repeated sync/admission does not advance current sample");
  same(t.driver.actor.targetCache5e8, priorStart, "repeated sync/admission does not advance older sample");
  t.driver.interrupt();
  same(t.driver.actor.savedGroundPos, frameStart, "interrupt retains movement history");
  same(t.driver.actor.targetCache5e8, priorStart, "interrupt retains older movement history");
  // Battle's own prepass is also idempotent for this same frame token.
  t.owner.state = "hit"; t.owner.stateTime = 0; t.owner.cooldowns["hitstun"] = 20;
  t.tick();
  same(t.driver.actor.savedGroundPos, frameStart, "same-frame Battle prepass cannot advance twice");
  const nextStart = { ...t.owner.pos };
  t.tick();
  same(t.driver.actor.savedGroundPos, nextStart, "hit frame still samples current own position");
  same(t.driver.actor.targetCache5e8, frameStart, "hit frame advances older own position");
}

function testDeathAndReplacement(): void {
  const t = setup("pl0100", 6000, true);
  t.owner.hp = 0; t.owner.state = "death"; t.owner.stateTime = 0;
  t.owner.pos.y = 500; t.owner.vel.y = -2; t.owner.grounded = false;
  const deathStart = { ...t.owner.pos };
  const priorStart = { ...t.driver.actor.savedGroundPos };
  t.tick();
  same(t.driver.actor.savedGroundPos, deathStart, "death branch samples own position before physics");
  same(t.driver.actor.targetCache5e8, priorStart, "death branch does not skip history shift");
  for (let i = 0; i < STATE.DEATH_DURATION + 5 && t.owner.alive; i++) t.tick();
  const replacement = t.state.borgs.find(b => b.ownerPlayer === "p1" && b.uid !== t.owner.uid);
  assert(replacement?.romDriver instanceof RomDriverBridge, "real force replacement receives a new bridge");
  assert(replacement.romDriver !== t.driver, "deployment never reuses defeated history");
  same(replacement.romDriver.actor.savedGroundPos, replacement.pos, "replacement +2c seeds from new spawn");
  same(replacement.romDriver.actor.targetCache5e8, replacement.pos, "replacement +5e8 seeds from new spawn");
}

export function runSourcePositionHistorySelfTest(): void {
  testStationaryFamilies();
  testMovementAndAirborneHistory();
  testOncePerFrameAndInterrupt();
  testDeathAndReplacement();
  console.log("[sourcePositionHistory] spawn/frame history, idle/air movement carry, target independence, repeated admission, interruption/death/redeployment passed");
}
