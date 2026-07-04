// Self-test for the deterministic battle core. Runnable via node after a tsc transpile, or
// directly with a TS-aware loader. Creates a 1v3 battle, steps ~600 frames with an idle
// human player + AI opponents, and asserts: no NaN anywhere, and the battle resolves.
//
// Run (from repo root), after building, e.g.:
//   D:/GotYaForce/tools/node/node.exe path/to/selfcheck.js
// or transpile this file and run it. main() returns an exit code.

import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, resolve } from "node:path";

import { distXZ, isFiniteVec, yAtTriangleXZ } from "@gf/physics";

import { actorDataCombatStatsForBorgId, actorDataCombatStatsSummary } from "./actorDataStats.js";
import { borgSourceStatsSummary, sourceStatsForBorgId } from "./sourceBorgStats.js";
import { createBattle, HUSK_BORG_ID } from "./battle.js";
import { stepAI } from "./ai.js";
import { actionProfileForProfile, startingAmmoForProfile } from "./actionProfiles.js";
import {
  X_CHARGE,
  applyHit,
  projectileVisualKindForProfile,
  stepAttacks,
  stepCooldowns,
  stepGaugeWindows,
  stepProjectiles,
} from "./combat.js";
import { createBurstMeter } from "./burst.js";
import { moveByButton } from "./moveProperties.js";
import { runtimeMoveBindingForBorgId, xChargeMoveForBorgId } from "./moveRuntime.js";
import { BURST, DASH, JUMP, MELEE, STAGGER, STATE, WAKE_UP_INVINCIBILITY_FRAMES } from "./constants.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex, gaugeInitForBorgId, type DamageRecord } from "./gauges.js";
import { stepMovement } from "./movement.js";
import {
  PARAM_TIER_RESET,
  PARAM_TIER_TIMER_FRAMES,
  applyActorParamTierDelta127,
  applyActorParamTierDelta63,
  resetActorParamTier,
} from "./paramTier.js";
import { emptyInput, type BorgRuntime, type PlayerInput, type Projectile, type StageCollision, type StageCollisionTriangle } from "./types.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import { typeCategoryForBorgId, typeDamageMultiplier } from "./typeDamage.js";
import { computeSourceDamage } from "./damageFormula.js";
import damageFormulaData from "./data/damageFormula.json" with { type: "json" };

function loadBorgs(): BorgStats[] {
  const here = dirname(fileURLToPath(import.meta.url));
  // selfcheck.js lives in packages/combat/dist (or src); borgs.json is in packages/assets/data.
  const candidates = [
    resolve(here, "../../assets/data/borgs.json"),
    resolve(here, "../../../assets/data/borgs.json"),
    resolve(here, "../../../packages/assets/data/borgs.json"),
  ];
  for (const c of candidates) {
    try {
      const raw = readFileSync(c, "utf8");
      const json = JSON.parse(raw) as { borgs: BorgStats[] };
      return json.borgs;
    } catch {
      // try next
    }
  }
  throw new Error("selfcheck: could not locate borgs.json");
}

function assertSane(borgs: BorgRuntime[], frame: number): void {
  for (const b of borgs) {
    if (!Number.isFinite(b.hp)) throw new Error(`NaN hp on ${b.uid} @frame ${frame}`);
    if (!Number.isFinite(b.rotY)) throw new Error(`NaN rotY on ${b.uid} @frame ${frame}`);
    if (!Number.isFinite(b.invincTimer)) throw new Error(`NaN invincTimer on ${b.uid} @frame ${frame}`);
    if (!isFiniteVec(b.pos)) throw new Error(`NaN pos on ${b.uid} @frame ${frame}`);
    if (!isFiniteVec(b.vel)) throw new Error(`NaN vel on ${b.uid} @frame ${frame}`);
  }
}

function assertRectBoundsClamp(borgs: BorgStats[]): void {
  const bounds = { minX: -30, maxX: 40, minZ: -20, maxZ: 50 };
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds,
    },
    borgs,
  );
  const moveRight: PlayerInput = { ...emptyInput(), moveX: 1 };
  for (let f = 0; f < 90; f += 1) {
    battle.step(1 / 60, { p1: moveRight, p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] rectangular bounds test lost active p1 borg");
  if (active.pos.x > bounds.maxX || active.pos.x < bounds.minX) {
    throw new Error(`[selfcheck] rectangular bounds clamp failed: x=${active.pos.x}`);
  }
  console.log(`[selfcheck] rectangular STIH-style bounds clamp kept p1 at x=${active.pos.x}`);
}

function assertTriangleFloorGrounding(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const actor = fakeRuntime("floor", 0, 0);
  actor.grounded = false;
  actor.state = "jump";
  const collision = singleCellCollision({
    index: 0,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices: [
      { x: -100, y: 20, z: -100 },
      { x: 100, y: 20, z: -100 },
      { x: 0, y: 20, z: 100 },
    ],
    normal: { x: 0, y: 1, z: 0 },
    planeD: -20,
    bounds2d: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
  });
  stepMovement(actor, profile, emptyInput(), gridCollisionContext(collision));
  assertSane([actor], 0);
  if (Math.abs(actor.pos.y - 30) > 0.001) {
    throw new Error(`[selfcheck] STIH grid triangle floor grounding failed: y=${actor.pos.y}`);
  }
  console.log(`[selfcheck] STIH grid triangle floor grounded actor at y=${actor.pos.y}`);
}

function assertTriangleFloorEdgeBlocksMovement(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const actor = fakeRuntime("floor-edge", 0, 0);
  actor.pos = { x: 0, y: 30, z: 0 };
  const edgeX = 30;
  const collision = singleCellCollision({
    index: 0,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices: [
      { x: -100, y: 20, z: -100 },
      { x: edgeX, y: 20, z: 0 },
      { x: -100, y: 20, z: 100 },
    ],
    normal: { x: 0, y: 1, z: 0 },
    planeD: -20,
    bounds2d: { minX: -100, maxX: edgeX, minZ: -100, maxZ: 100 },
  });
  const ctx = gridCollisionContext(collision);
  const moveRight: PlayerInput = { ...emptyInput(), moveX: 1 };
  for (let f = 0; f < 90; f += 1) {
    stepMovement(actor, profile, moveRight, ctx);
    assertSane([actor], f);
  }
  if (actor.pos.x > edgeX + 0.25) {
    throw new Error(`[selfcheck] STIH grid floor edge failed to block movement: x=${actor.pos.x}`);
  }
  console.log(`[selfcheck] STIH grid floor edge kept actor on supported floor at x=${actor.pos.x}`);
}

function assertCpuEnemyCannotWalkOffDisconnectedStage(borgs: BorgStats[]): void {
  const collision: StageCollision = {
    triangles: [
      ...floorRectTriangles(0, -100, -20, -80, 80, 20),
      ...floorRectTriangles(2, 20, 100, -80, 80, 20),
    ],
  };
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0200"] },
      ],
      bounds: { minX: -120, maxX: 120, minZ: -100, maxZ: 100 },
      collision,
      spawnPoints: [
        { pos: { x: -80, y: 30, z: 0 }, rotY: Math.PI / 2 },
        { pos: { x: 80, y: 30, z: 0 }, rotY: -Math.PI / 2 },
      ],
    },
    borgs,
  );

  for (let f = 0; f < 180; f += 1) {
    battle.step(1 / 60, { p1: emptyInput() });
    assertSane(battle.state.borgs, f);
  }

  const enemy = battle.state.borgs.find((b) => b.team === 1);
  if (!enemy) throw new Error("[selfcheck] CPU offstage regression lost enemy borg");
  if (enemy.pos.x < 20 || !hasSupportedFloorAt(collision, enemy.pos.x, enemy.pos.z, enemy.pos.y)) {
    throw new Error(`[selfcheck] CPU enemy walked off disconnected stage: pos=${JSON.stringify(enemy.pos)}`);
  }
  console.log(`[selfcheck] CPU enemy stayed on supported floor while chasing across a gap at x=${enemy.pos.x}`);
}

function assertCollisionSpawnUsesPlayableFloor(borgs: BorgStats[]): void {
  const collision = singleCellCollision({
    index: 0,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices: [
      { x: -1000, y: 20, z: -1000 },
      { x: 1000, y: 20, z: -1000 },
      { x: 0, y: 20, z: 1000 },
    ],
    normal: { x: 0, y: 1, z: 0 },
    planeD: -20,
    bounds2d: { minX: -1000, maxX: 1000, minZ: -1000, maxZ: 1000 },
  });
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
      ],
      bounds: { minX: -10000, maxX: 10000, minZ: -10000, maxZ: 10000 },
      collision,
    },
    borgs,
  );
  const p1 = battle.state.borgs.find((b) => b.uid === battle.state.activeUidByPlayer["p1"]);
  if (!p1) throw new Error("[selfcheck] collision spawn test lost active p1 borg");
  if (Math.abs(p1.pos.x) > 1 || Math.abs(p1.pos.z) > 400 || Math.abs(p1.pos.y - 30) > 0.001) {
    throw new Error(`[selfcheck] collision spawn used broad bounds edge: pos=${JSON.stringify(p1.pos)}`);
  }
  console.log(`[selfcheck] collision-backed spawn used playable floor at ${JSON.stringify(p1.pos)}`);
}

function assertExactSpawnPointsOverrideRadialSpawn(borgs: BorgStats[]): void {
  const playerSpawn = { pos: { x: 4980, y: 0, z: 1079.937 }, rotY: (26760 / 32768) * Math.PI };
  const enemySpawn = { pos: { x: 4538.932, y: 132.806, z: 1670.764 }, rotY: (-8694 / 32768) * Math.PI };
  const exact = [
    playerSpawn,
    enemySpawn,
  ];
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0a05"] },
      ],
      bounds: { minX: -10000, maxX: 10000, minZ: -10000, maxZ: 10000 },
      spawnPoints: exact,
    },
    borgs,
  );
  const p1 = battle.state.borgs.find((b) => b.uid === battle.state.activeUidByPlayer["p1"]);
  const enemy = battle.state.borgs.find((b) => b.team === 1);
  if (!p1 || !enemy) throw new Error("[selfcheck] exact spawn test lost active borgs");
  if (
    Math.abs(p1.pos.x - playerSpawn.pos.x) > 0.001 ||
    Math.abs(p1.pos.y - playerSpawn.pos.y) > 0.001 ||
    Math.abs(p1.pos.z - playerSpawn.pos.z) > 0.001
  ) {
    throw new Error(`[selfcheck] exact player spawn was not honored: ${JSON.stringify(p1.pos)}`);
  }
  if (
    Math.abs(enemy.pos.x - enemySpawn.pos.x) > 0.001 ||
    Math.abs(enemy.pos.y - enemySpawn.pos.y) > 0.001 ||
    Math.abs(enemy.pos.z - enemySpawn.pos.z) > 0.001
  ) {
    throw new Error(`[selfcheck] exact enemy spawn was not honored: ${JSON.stringify(enemy.pos)}`);
  }
  console.log("[selfcheck] explicit spawnPoints override radial/floor-repaired spawn placement");
}

function assertDisconnectedSpawnRepairsUnsupportedCenter(borgs: BorgStats[]): void {
  const collision: StageCollision = {
    triangles: [
      floorTriangle(0, [
        { x: -1000, y: 20, z: -100 },
        { x: -800, y: 20, z: -100 },
        { x: -1000, y: 20, z: 100 },
      ]),
      floorTriangle(1, [
        { x: 800, y: 20, z: -100 },
        { x: 1000, y: 20, z: -100 },
        { x: 1000, y: 20, z: 100 },
      ]),
    ],
  };
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
      ],
      bounds: { minX: -1500, maxX: 1500, minZ: -500, maxZ: 500 },
      collision,
    },
    borgs,
  );
  const p1 = battle.state.borgs.find((b) => b.uid === battle.state.activeUidByPlayer["p1"]);
  if (!p1) throw new Error("[selfcheck] disconnected spawn test lost active p1 borg");
  if (Math.abs(p1.pos.x) < 700 || Math.abs(p1.pos.y - 30) > 0.001) {
    throw new Error(`[selfcheck] disconnected spawn fell back to unsupported center: pos=${JSON.stringify(p1.pos)}`);
  }
  console.log(`[selfcheck] disconnected floor spawn repaired to supported triangle at ${JSON.stringify(p1.pos)}`);
}

function assertTriangleWallCollision(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const wallX = 20;
  const actor = fakeRuntime("wall", 0, 0);
  actor.pos = { x: 0, y: JUMP.GROUND_Y, z: 0 };
  const collision = singleCellCollision({
    index: 0,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices: [
      { x: wallX, y: -20, z: -100 },
      { x: wallX, y: 100, z: 100 },
      { x: wallX, y: -20, z: 100 },
    ],
    normal: { x: -1, y: 0, z: 0 },
    planeD: wallX,
    bounds2d: { minX: wallX, maxX: wallX, minZ: -100, maxZ: 100 },
  });
  const ctx = gridCollisionContext(collision);
  const moveRight: PlayerInput = { ...emptyInput(), moveX: 1 };
  for (let f = 0; f < 40; f += 1) {
    stepMovement(actor, profile, moveRight, ctx);
    assertSane([actor], f);
  }
  if (actor.pos.x >= wallX || actor.pos.x < wallX - 2) {
    throw new Error(`[selfcheck] STIH grid triangle wall collision failed: x=${actor.pos.x}`);
  }
  console.log(`[selfcheck] STIH grid triangle wall stopped actor at x=${actor.pos.x}`);
}

function assertTriangleCeilingCollision(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const ceilingY = 24;
  const actor = fakeRuntime("ceiling", 0, 0);
  actor.pos = { x: 0, y: JUMP.GROUND_Y, z: 0 };
  const collision = singleCellCollision({
    index: 0,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices: [
      { x: -100, y: ceilingY, z: -100 },
      { x: 0, y: ceilingY, z: 100 },
      { x: 100, y: ceilingY, z: -100 },
    ],
    normal: { x: 0, y: -1, z: 0 },
    planeD: ceilingY,
    bounds2d: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
  });
  const ctx = gridCollisionContext(collision);

  let maxTopY = actor.pos.y + JUMP.GROUND_Y;
  stepMovement(actor, profile, { ...emptyInput(), jump: true }, ctx);
  for (let f = 0; f < 45; f += 1) {
    stepMovement(actor, profile, emptyInput(), ctx);
    assertSane([actor], f);
    maxTopY = Math.max(maxTopY, actor.pos.y + JUMP.GROUND_Y);
  }

  if (maxTopY > ceilingY + 0.01) {
    throw new Error(`[selfcheck] STIH grid triangle ceiling collision failed: topY=${maxTopY}`);
  }
  console.log(`[selfcheck] STIH grid triangle ceiling capped actor top at y=${maxTopY}`);
}

function singleCellCollision(triangle: StageCollisionTriangle): StageCollision {
  return {
    triangles: [triangle],
    grid: {
      origin: { x: -100, z: -100 },
      cellSize: { x: 200, z: 200 },
      gridCells: { x: 1, z: 1, total: 1 },
      cells: [{ index: 0, triangleIndices: [triangle.index] }],
    },
  };
}

function floorTriangle(index: number, vertices: StageCollisionTriangle["vertices"]): StageCollisionTriangle {
  const xs = vertices.map((v) => v.x);
  const zs = vertices.map((v) => v.z);
  return {
    index,
    layerIndex: 0,
    marker: 0xcccccccc,
    vertices,
    normal: { x: 0, y: 1, z: 0 },
    planeD: -vertices[0].y,
    bounds2d: {
      minX: Math.min(...xs),
      maxX: Math.max(...xs),
      minZ: Math.min(...zs),
      maxZ: Math.max(...zs),
    },
  };
}

function floorRectTriangles(
  startIndex: number,
  minX: number,
  maxX: number,
  minZ: number,
  maxZ: number,
  y: number,
): StageCollisionTriangle[] {
  return [
    floorTriangle(startIndex, [
      { x: minX, y, z: minZ },
      { x: maxX, y, z: minZ },
      { x: minX, y, z: maxZ },
    ]),
    floorTriangle(startIndex + 1, [
      { x: maxX, y, z: minZ },
      { x: maxX, y, z: maxZ },
      { x: minX, y, z: maxZ },
    ]),
  ];
}

function hasSupportedFloorAt(collision: StageCollision, x: number, z: number, maxActorY: number): boolean {
  for (const tri of collision.triangles) {
    if (tri.marker !== 0xcccccccc || tri.normal.y < 0.5) continue;
    if (x < tri.bounds2d.minX || x > tri.bounds2d.maxX || z < tri.bounds2d.minZ || z > tri.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y != null && y <= maxActorY) return true;
  }
  return false;
}

function gridCollisionContext(collision: StageCollision) {
  return {
    lockTargetPos: null,
    bounds: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
    collision,
  };
}

function assertPlayersAutoLockByDefault(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: 100, z: 100 },
    },
    borgs,
  );
  battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] auto-lock test lost active p1 borg");
  if (!active.lockTarget) {
    throw new Error("[selfcheck] human-controlled borg did not auto-acquire a default lock target");
  }
  const target = battle.state.borgs.find((b) => b.uid === active.lockTarget);
  if (!target || target.team === active.team) {
    throw new Error("[selfcheck] human-controlled borg auto-locked an invalid target");
  }
  console.log(`[selfcheck] human-controlled borg auto-locked enemy ${active.lockTarget} by default`);
}

function assertAllyLockTargetsTeammate(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 0, ownerPlayer: null, borgIds: ["pl020a"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: 100, z: 100 },
    },
    borgs,
  );
  battle.step(1 / 60, { p1: { ...emptyInput(), allyLock: true }, p2: emptyInput() });
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] ally-lock test lost active p1 borg");
  const ally = active.allyLockTarget ? battle.state.borgs.find((b) => b.uid === active.allyLockTarget) : null;
  const enemy = active.lockTarget ? battle.state.borgs.find((b) => b.uid === active.lockTarget) : null;
  if (!ally || ally.team !== active.team || ally.uid === active.uid) {
    throw new Error(`[selfcheck] Z ally-lock did not select a same-team ally: ${active.allyLockTarget}`);
  }
  if (!enemy || enemy.team === active.team) {
    throw new Error(`[selfcheck] Z ally-lock corrupted enemy lock target: ${active.lockTarget}`);
  }
  console.log(`[selfcheck] Z ally-lock selected teammate ${active.allyLockTarget} without changing enemy lock`);
}

function assertActorDataStatsBound(borgs: BorgStats[]): void {
  const expected = actorDataCombatStatsSummary.matchedMetadataRows;
  for (const field of ["defense", "shot", "attack", "speed"] as const) {
    if (actorDataCombatStatsSummary.exactMatches[field] !== expected) {
      throw new Error(`[selfcheck] actor-data ${field} exact matches changed`);
    }
  }
  if (actorDataCombatStatsSummary.mismatches.length > 0) {
    throw new Error("[selfcheck] actor-data stat offsets have mismatches");
  }

  const gRed = borgById(borgs, "pl0615");
  const actorStats = actorDataCombatStatsForBorgId(gRed.id);
  if (!actorStats) throw new Error("[selfcheck] missing actor-data stats for pl0615");

  const spoofedRosterStats: BorgStats = {
    ...gRed,
    hp: 1,
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 0,
  };
  const profile = buildProfile(spoofedRosterStats);
  const sourceStats = sourceStatsForBorgId(gRed.id);
  if (!sourceStats) throw new Error("[selfcheck] missing source stat row for pl0615");
  if (
    profile.maxHp !== sourceStats.maxHp ||
    profile.defense !== actorStats.defense ||
    profile.shot !== actorStats.shot ||
    profile.attack !== actorStats.attack ||
    profile.speed !== actorStats.speed
  ) {
    throw new Error(
      `[selfcheck] buildProfile did not bind pl####data.bin stats: profile=${JSON.stringify(profile)} actor=${JSON.stringify(actorStats)}`,
    );
  }
  console.log(
    `[selfcheck] source stats bound: hp=${profile.maxHp}; actor-data exact rows=${expected}; pl0615 def/shot/atk/spd=${profile.defense}/${profile.shot}/${profile.attack}/${profile.speed}`,
  );

  if (
    borgSourceStatsSummary.missingRows.length > 0 ||
    borgSourceStatsSummary.hpMismatches.length > 0
  ) {
    throw new Error("[selfcheck] source borg stat verification has missing rows or HP mismatches");
  }
}

function assertLockRelativeControls(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const bounds = { minX: -500, maxX: 500, minZ: -500, maxZ: 500 };
  const ctx = {
    lockTargetPos: { x: 0, y: JUMP.GROUND_Y, z: -100 },
    bounds,
    collision: null,
  };
  let uid = 0;
  const makeLocked = (): BorgRuntime => {
    const b = fakeRuntime(`locked_${uid++}`, 0, 0);
    b.pos = { x: 0, y: JUMP.GROUND_Y, z: 0 };
    b.rotY = 0;
    b.state = "idle";
    b.grounded = true;
    return b;
  };

  const forward = makeLocked();
  stepMovement(forward, profile, { ...emptyInput(), moveZ: 1 }, ctx);
  if (!(forward.vel.z < -0.1 && Math.abs(forward.vel.x) < 0.001)) {
    throw new Error(`[selfcheck] lock-relative forward should approach target: vel=${JSON.stringify(forward.vel)}`);
  }

  const back = makeLocked();
  stepMovement(back, profile, { ...emptyInput(), moveZ: -1 }, ctx);
  if (!(back.vel.z > 0.1 && Math.abs(back.vel.x) < 0.001)) {
    throw new Error(`[selfcheck] lock-relative back should retreat straight away: vel=${JSON.stringify(back.vel)}`);
  }

  const lateral = makeLocked();
  stepMovement(lateral, profile, { ...emptyInput(), moveX: 1 }, ctx);
  if ((lateral.cooldowns["dashActive"] ?? 0) !== DASH.DURATION || Math.abs(lateral.vel.x) < DASH.SPEED * 0.9) {
    throw new Error(`[selfcheck] lock-relative pure lateral should dodge dash: vel=${JSON.stringify(lateral.vel)}`);
  }

  const lateralOnCooldown = makeLocked();
  lateralOnCooldown.cooldowns["dash"] = DASH.COOLDOWN;
  stepMovement(lateralOnCooldown, profile, { ...emptyInput(), moveX: 1 }, ctx);
  if ((lateralOnCooldown.cooldowns["dashActive"] ?? 0) > 0 || Math.hypot(lateralOnCooldown.vel.x, lateralOnCooldown.vel.z) > 0.001) {
    throw new Error(`[selfcheck] lock-relative pure lateral should not become steady walk on dash cooldown: vel=${JSON.stringify(lateralOnCooldown.vel)}`);
  }

  const diagonal = makeLocked();
  stepMovement(diagonal, profile, { ...emptyInput(), moveX: 1, moveZ: 1 }, ctx);
  if ((diagonal.cooldowns["dashActive"] ?? 0) > 0 || !(diagonal.vel.x < -0.1 && diagonal.vel.z < -0.1)) {
    throw new Error(`[selfcheck] lock-relative forward+lateral should circle-strafe, not dodge: vel=${JSON.stringify(diagonal.vel)}`);
  }

  console.log("[selfcheck] lock-relative controls: forward approach, back retreat, lateral dodge, diagonal circle-strafe");
}

function borgById(borgs: BorgStats[], id: string): BorgStats {
  const borg = borgs.find((entry) => entry.id === id);
  if (!borg) throw new Error(`[selfcheck] missing borg stats for ${id}`);
  return borg;
}

function assertProjectileVisualKinds(borgs: BorgStats[]): void {
  const gatling = buildProfile(borgById(borgs, "pl0102"));
  const beam = buildProfile(borgById(borgs, "pl0104"));
  const flame = buildProfile(borgById(borgs, "pl0500"));
  if (projectileVisualKindForProfile(gatling) !== "muzzle") {
    throw new Error("[selfcheck] Gatling Gunner projectile visual should use exported muzzle flash");
  }
  if (projectileVisualKindForProfile(beam) !== "energy") {
    throw new Error("[selfcheck] Beam Gunner projectile visual should use exported energy dot");
  }
  if (projectileVisualKindForProfile(flame) !== "flame") {
    throw new Error("[selfcheck] Flame Dragon projectile visual should use exported flame core");
  }

  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0102"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { minX: -300, maxX: 300, minZ: -300, maxZ: 300 },
    },
    borgs,
  );
  for (let f = 0; f < STATE.SPAWN_DURATION; f += 1) {
    battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }
  battle.step(1 / 60, { p1: { ...emptyInput(), attack: true }, p2: emptyInput() });
  const projectile = battle.state.projectiles[0];
  if (!projectile) throw new Error("[selfcheck] Gatling Gunner did not spawn a projectile");
  if (projectile.visualKind !== "muzzle") {
    throw new Error(`[selfcheck] spawned Gatling Gunner projectile visualKind=${projectile.visualKind}`);
  }
  console.log(`[selfcheck] projectile visuals mapped gun/beam/flame assets; spawned ${projectile.visualKind}`);
}

function assertProjectilesCullOutsideStageFloor(): void {
  const bounds = { minX: -100, maxX: 100, minZ: -100, maxZ: 100 };
  const inside = fakeProjectile("inside", { x: -50, y: 40, z: 0 }, { x: 10, y: 0, z: 0 });
  const outside = fakeProjectile("outside", { x: 90, y: 40, z: 0 }, { x: 20, y: 0, z: 0 });
  const collision = singleCellCollision(
    floorTriangle(0, [
      { x: -100, y: 20, z: -100 },
      { x: 100, y: 20, z: -100 },
      { x: -100, y: 20, z: 100 },
    ]),
  );

  const bounded = stepProjectiles([inside, outside], [], new Map(), new Map(), { bounds, collision });
  if (bounded.length !== 1 || bounded[0]?.uid !== "inside") {
    throw new Error(`[selfcheck] projectile bounds cull failed: survivors=${bounded.map((p) => p.uid).join(",")}`);
  }

  const disconnected: StageCollision = {
    triangles: [
      floorTriangle(0, [
        { x: -100, y: 20, z: -100 },
        { x: -20, y: 20, z: -100 },
        { x: -100, y: 20, z: 100 },
      ]),
      floorTriangle(1, [
        { x: 20, y: 20, z: -100 },
        { x: 100, y: 20, z: -100 },
        { x: 100, y: 20, z: 100 },
      ]),
    ],
  };
  const overGap = fakeProjectile("gap", { x: -25, y: 40, z: 0 }, { x: 25, y: 0, z: 0 });
  const floorCull = stepProjectiles([overGap], [], new Map(), new Map(), { bounds, collision: disconnected });
  if (floorCull.length !== 0) {
    throw new Error("[selfcheck] projectile floor cull let a shot cross unsupported gap");
  }
  console.log("[selfcheck] projectile arena cull removes shots outside bounds or unsupported floor");
}

/** Advance one manual combat frame: tick cooldowns, then run stepAttacks with a held state. */
function pumpAttackFrame(
  b: BorgRuntime,
  p: BorgProfile,
  attackHeld: boolean,
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
): Projectile[] {
  stepCooldowns(b);
  return stepAttacks(b, p, attackHeld, false, all, profiles).projectiles;
}

function assertActionProfilesDrivePrimaryAttacks(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const swordKnight = buildProfile(borgById(borgs, "pl0200"));
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));

  const gRedRuntime = fakeRuntime("gred", 0, 0);
  gRedRuntime.borgId = gRed.id;
  gRedRuntime.ammo = startingAmmoForProfile(gRed);
  const gRedEnemy = fakeRuntime("gred_enemy", 1, 220);
  const gRedProfiles = new Map([
    [gRedRuntime.uid, gRed],
    [gRedEnemy.uid, enemyProfile],
  ]);
  // G RED's shot is chargeable (hero line): holding B charges, releasing fires.
  const whileHeld = pumpAttackFrame(gRedRuntime, gRed, true, [gRedRuntime, gRedEnemy], gRedProfiles);
  const onRelease = pumpAttackFrame(gRedRuntime, gRed, false, [gRedRuntime, gRedEnemy], gRedProfiles);
  if (
    actionProfileForProfile(gRed).primary !== "shot" ||
    whileHeld.length !== 0 ||
    onRelease.length === 0 ||
    gRedRuntime.anim !== "shoot"
  ) {
    throw new Error("[selfcheck] action profile did not make mixed G RED charge-and-release as its primary B attack");
  }

  const closeGRedRuntime = fakeRuntime("gred_close", 0, 0);
  closeGRedRuntime.borgId = gRed.id;
  closeGRedRuntime.ammo = startingAmmoForProfile(gRed);
  const closeGRedEnemy = fakeRuntime("gred_close_enemy", 1, 42);
  const closeGRedProfiles = new Map([
    [closeGRedRuntime.uid, gRed],
    [closeGRedEnemy.uid, enemyProfile],
  ]);
  const closeResult = pumpAttackFrame(closeGRedRuntime, gRed, true, [closeGRedRuntime, closeGRedEnemy], closeGRedProfiles);
  if (closeGRedRuntime.anim !== "melee" || closeResult.length !== 0) {
    throw new Error(
      `[selfcheck] contextual B resolver did not route close G RED B press to B Attack: anim=${closeGRedRuntime.anim}, projectiles=${closeResult.length}`,
    );
  }

  const swordRuntime = fakeRuntime("sword", 0, 0);
  swordRuntime.borgId = swordKnight.id;
  swordRuntime.ammo = startingAmmoForProfile(swordKnight);
  const swordEnemy = fakeRuntime("sword_enemy", 1, 42);
  const swordProfiles = new Map([
    [swordRuntime.uid, swordKnight],
    [swordEnemy.uid, enemyProfile],
  ]);
  const swordResult = stepAttacks(swordRuntime, swordKnight, true, false, [swordRuntime, swordEnemy], swordProfiles);
  if (actionProfileForProfile(swordKnight).primary !== "melee" || swordResult.projectiles.length !== 0 || swordRuntime.anim !== "melee") {
    throw new Error("[selfcheck] action profile did not keep Sword Knight melee as its primary B attack");
  }

  console.log("[selfcheck] action profiles route mixed/ranged borgs to shots and sword borgs to melee");
}

function assertMeleeComboChains(borgs: BorgStats[]): void {
  const swordKnight = buildProfile(borgById(borgs, "pl0200"));
  const action = actionProfileForProfile(swordKnight);
  const meleeDef = action.melee;
  if (!meleeDef || meleeDef.comboHits < 2) {
    throw new Error(`[selfcheck] Sword Knight should have a multi-hit combo chain: ${JSON.stringify(meleeDef)}`);
  }

  const attacker = fakeRuntime("combo", 0, 0);
  attacker.borgId = swordKnight.id;
  const enemy = fakeRuntime("combo_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, swordKnight],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  let maxStep = 0;
  let swingStarts = 0;
  let prevMeleeActive = 0;
  for (let f = 0; f < 240; f += 1) {
    pumpAttackFrame(attacker, swordKnight, true, [attacker, enemy], profiles);
    const active = attacker.cooldowns["meleeActive"] ?? 0;
    if (active > prevMeleeActive) swingStarts += 1; // meleeActive only grows on a new swing
    prevMeleeActive = active;
    maxStep = Math.max(maxStep, attacker.cooldowns["comboStep"] ?? 0);
    assertSane([attacker, enemy], f);
  }
  if (maxStep !== meleeDef.comboHits - 1) {
    throw new Error(`[selfcheck] combo chain never reached its finisher: maxStep=${maxStep}, comboHits=${meleeDef.comboHits}`);
  }
  if (swingStarts < meleeDef.comboHits) {
    throw new Error(`[selfcheck] combo chain produced too few swings: ${swingStarts}`);
  }
  if (enemy.hp >= enemy.maxHp) {
    throw new Error("[selfcheck] combo chain dealt no damage");
  }
  console.log(
    `[selfcheck] melee combo chained to step ${maxStep} (${meleeDef.comboHits} hits) over ${swingStarts} swings while holding B`,
  );
}

function assertMeleeHitsOncePerSwing(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0200"));
  const attacker = fakeRuntime("onehit", 0, 0);
  attacker.borgId = profile.id;
  const enemy = fakeRuntime("onehit_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  const meleeDef = actionProfileForProfile(profile).melee;
  if (!meleeDef) throw new Error("[selfcheck] one-hit-per-swing test needs a melee profile");
  // One press -> one swing; run through the whole active window.
  pumpAttackFrame(attacker, profile, true, [attacker, enemy], profiles);
  for (let f = 0; f < meleeDef.startup + meleeDef.active + 2; f += 1) {
    pumpAttackFrame(attacker, profile, false, [attacker, enemy], profiles);
  }
  const damage = enemy.maxHp - enemy.hp;
  // Generous single-hit ceiling (1.5x covers type-matrix boosts) — the old bug applied the
  // hit on EVERY active frame (~6-9x), which this bound catches.
  const singleHitCap = (MELEE.DMG_BASE + profile.attack * MELEE.DMG_PER_STAT) * meleeDef.damageMultiplier * 1.5;
  if (damage <= 0 || damage > singleHitCap) {
    throw new Error(`[selfcheck] melee swing did not hit exactly once: damage=${damage}, singleHitCap=${singleHitCap}`);
  }
  console.log(`[selfcheck] melee swing hit once per target (damage=${damage} within single-hit cap)`);
}

function assertChargeShotTiers(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const action = actionProfileForProfile(gRed);
  const shotDef = action.shot;
  if (!shotDef?.chargeable) {
    throw new Error("[selfcheck] G RED (pl0615, hero line) should have a chargeable shot");
  }

  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));
  const fireAfterHold = (holdFrames: number): Projectile => {
    const b = fakeRuntime("charge", 0, 0);
    b.borgId = gRed.id;
    b.ammo = startingAmmoForProfile(gRed);
    const enemy = fakeRuntime("charge_enemy", 1, 500);
    const profiles = new Map([
      [b.uid, gRed],
      [enemy.uid, enemyProfile],
    ]);
    for (let f = 0; f < holdFrames; f += 1) {
      const spawned = pumpAttackFrame(b, gRed, true, [b, enemy], profiles);
      if (spawned.length > 0) throw new Error("[selfcheck] chargeable shot fired while still holding");
    }
    const released = pumpAttackFrame(b, gRed, false, [b, enemy], profiles);
    const proj = released[0];
    if (!proj) throw new Error(`[selfcheck] charge release after ${holdFrames} held frames spawned nothing`);
    return proj;
  };

  const tier0 = fireAfterHold(3);
  const tier1 = fireAfterHold(shotDef.chargeTier1Frames + 5);
  const tier2 = fireAfterHold(shotDef.chargeTier2Frames + 30); // accumulator caps at tier2Frames
  const r1 = tier1.damage / tier0.damage;
  const r2 = tier2.damage / tier0.damage;
  if (Math.abs(r1 - shotDef.chargeTier1DamageMult) > 1e-6 || Math.abs(r2 - shotDef.chargeTier2DamageMult) > 1e-6) {
    throw new Error(`[selfcheck] charge tier damage scaling wrong: r1=${r1}, r2=${r2}`);
  }
  const speed0 = Math.hypot(tier0.vel.x, tier0.vel.z);
  const speed2 = Math.hypot(tier2.vel.x, tier2.vel.z);
  if (!(speed2 > speed0) || !(tier2.hitRadius > tier0.hitRadius)) {
    throw new Error("[selfcheck] tier-2 charge shot should be faster and larger than a tap shot");
  }
  if (shotDef.bulletDrop > 0 && tier0.drop !== shotDef.bulletDrop) {
    throw new Error(`[selfcheck] ballistic drop not applied to spawned bullet: ${tier0.drop}`);
  }
  console.log(
    `[selfcheck] charge tiers OK: tap=${tier0.damage.toFixed(1)} dmg, tier1 x${r1.toFixed(2)}, tier2 x${r2.toFixed(2)} (drop=${tier0.drop ?? 0})`,
  );
}

// ATK-002 case 5: chargeable shooter — hold N frames < tier1 releases tier 0, hold >= tier2
// releases tier 2; also pins the projectile's damageRecordIndex (DERIVED mapping, gauges.ts):
// tier0 uses the normal-shot record (SHOT=0), a charged release (tier>=1) uses the
// charge/special record (CHARGE_OR_SPECIAL=2) — spawnProjectile in combat.ts.
function assertResolverChargeTierSelectsDamageRecord(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const action = actionProfileForProfile(gRed);
  const shotDef = action.shot;
  if (!shotDef?.chargeable) {
    throw new Error("[selfcheck] resolver charge tier: G RED (pl0615) should have a chargeable shot");
  }
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));
  const fireAfterHold = (holdFrames: number): Projectile => {
    const b = fakeRuntime("resolver_charge", 0, 0);
    b.borgId = gRed.id;
    b.ammo = startingAmmoForProfile(gRed);
    const enemy = fakeRuntime("resolver_charge_enemy", 1, 500);
    const profiles = new Map([
      [b.uid, gRed],
      [enemy.uid, enemyProfile],
    ]);
    for (let f = 0; f < holdFrames; f += 1) pumpAttackFrame(b, gRed, true, [b, enemy], profiles);
    const released = pumpAttackFrame(b, gRed, false, [b, enemy], profiles);
    const proj = released[0];
    if (!proj) throw new Error(`[selfcheck] resolver charge tier: release after ${holdFrames} frames spawned nothing`);
    return proj;
  };

  const belowTier1 = fireAfterHold(Math.max(1, shotDef.chargeTier1Frames - 5));
  const atOrAboveTier2 = fireAfterHold(shotDef.chargeTier2Frames + 10);
  if ((belowTier1.damageRecordIndex ?? DAMAGE_RECORD_INDEX.SHOT) !== DAMAGE_RECORD_INDEX.SHOT) {
    throw new Error(
      `[selfcheck] resolver charge tier: below-tier1 release should use the SHOT record: got=${belowTier1.damageRecordIndex}`,
    );
  }
  if (atOrAboveTier2.damageRecordIndex !== DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL) {
    throw new Error(
      `[selfcheck] resolver charge tier: tier-2 release should use the CHARGE_OR_SPECIAL record: got=${atOrAboveTier2.damageRecordIndex}`,
    );
  }
  if (!(atOrAboveTier2.damage > belowTier1.damage)) {
    throw new Error(
      `[selfcheck] resolver charge tier: tier-2 damage multiplier should exceed tier-0: tier0=${belowTier1.damage}, tier2=${atOrAboveTier2.damage}`,
    );
  }
  console.log(
    `[selfcheck] resolver charge tier: below-tier1 release=SHOT record, tier2 release=CHARGE_OR_SPECIAL record (damage ${belowTier1.damage.toFixed(2)} -> ${atOrAboveTier2.damage.toFixed(2)})`,
  );
}

function assertSwordBeamFinisher(borgs: BorgStats[]): void {
  const run = (id: string, forceMelee: boolean): Projectile[] => {
    const profile = buildProfile(borgById(borgs, id));
    const meleeDef = actionProfileForProfile(profile).melee;
    if (!meleeDef?.swordBeam) {
      throw new Error(`[selfcheck] ${id} should have a sword-beam finisher`);
    }
    const attacker = fakeRuntime(`beam_${id}`, 0, 0);
    attacker.borgId = profile.id;
    const enemy = fakeRuntime(`beam_enemy_${id}`, 1, 40);
    enemy.hp = enemy.maxHp = 5000;
    const profiles = new Map([
      [attacker.uid, profile],
      [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
    ]);
    const hasShot = actionProfileForProfile(profile).shot !== null;
    const beams: Projectile[] = [];
    for (let f = 0; f < 300; f += 1) {
      if (forceMelee || hasShot) {
        // Route any shooter onto its sword (empty magazine + reloading) so every spawned
        // projectile in this loop is a sword beam, not a gun shot.
        attacker.ammo = 0;
        attacker.cooldowns["reload"] = 10;
      }
      beams.push(...pumpAttackFrame(attacker, profile, true, [attacker, enemy], profiles));
      assertSane([attacker, enemy], f);
    }
    return beams;
  };

  const knightBeams = run("pl0200", false); // sword-family melee-primary borg
  const gRedBeams = run("pl0615", true); // hero line, melee forced via empty magazine
  if (knightBeams.length === 0 || gRedBeams.length === 0) {
    throw new Error(`[selfcheck] sword-beam finisher spawned nothing: knight=${knightBeams.length}, gRed=${gRedBeams.length}`);
  }
  for (const beam of [...knightBeams, ...gRedBeams]) {
    if (beam.visualKind !== "energy") {
      throw new Error(`[selfcheck] sword beam should reuse the existing 'energy' visual, got ${beam.visualKind}`);
    }
  }
  console.log(
    `[selfcheck] sword-beam finishers fired: Sword Knight x${knightBeams.length}, G RED x${gRedBeams.length} (energy visuals)`,
  );
}

function assertActionProfileFallbackDefaults(borgs: BorgStats[]): void {
  // An id with no generated profile entry must resolve to the generic TUNED defaults:
  // single-hit melee, no sword beam, non-chargeable autofire shot, no bullet drop.
  const base = buildProfile(borgById(borgs, "pl0615"));
  const unknown = { ...base, id: "zz9999" };
  const action = actionProfileForProfile(unknown);
  if (action.confidence !== "fallback") {
    throw new Error(`[selfcheck] unknown borg id should resolve fallback confidence, got ${action.confidence}`);
  }
  if (!action.melee || action.melee.comboHits !== 1 || action.melee.swordBeam !== null) {
    throw new Error(`[selfcheck] fallback melee defaults wrong: ${JSON.stringify(action.melee)}`);
  }
  if (!action.shot || action.shot.chargeable || action.shot.bulletDrop !== 0) {
    throw new Error(`[selfcheck] fallback shot defaults wrong: ${JSON.stringify(action.shot)}`);
  }

  // And behavior: a non-chargeable shooter autofires on the first held frame. (Shot-only
  // spoof: the mixed spoof above resolves melee-primary via the stats fallback, so it would
  // swing instead of shoot.)
  const shooter = { ...base, id: "zz9998", hasMelee: false };
  const b = fakeRuntime("fallback", 0, 0);
  b.ammo = action.shot.ammoMax;
  const enemy = fakeRuntime("fallback_enemy", 1, 500);
  const profiles = new Map([
    [b.uid, shooter],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const spawned = pumpAttackFrame(b, shooter, true, [b, enemy], profiles);
  if (spawned.length === 0) {
    throw new Error("[selfcheck] fallback-profile shooter did not autofire while holding attack");
  }
  console.log("[selfcheck] fallback action profile keeps generic single-hit melee + autofire shot");
}

// ---------------------------------------------------------------------------------------
// ATK-002: pin the CURRENT B/X contextual-resolver selection order with synthetic
// BorgProfiles (unregistered ids, so RAW_PROFILES has no entry and resolveActionProfile()
// falls back to chooseFallbackPrimary purely from hasMelee/hasShot/rangePref — the same
// synthetic-profile pattern as assertActionProfileFallbackDefaults above). Evidence: stepAttacks
// order from actionProfile.primary (combat.ts:592-635); charge accumulate/release (:610-633);
// combo window/step (:598-609, :710-726); special AoE (:549-589). BEFORE the resolver
// restructure (ATK-003) so this is a regression net for the selection order specifically.
// ---------------------------------------------------------------------------------------
function assertResolverPrimaryMeleeHybridStartsMelee(borgs: BorgStats[]): void {
  const base = buildProfile(borgById(borgs, "pl0615"));
  // Hybrid (both melee and shot usable) with rangePref "melee" -> chooseFallbackPrimary
  // picks "melee" (actionProfiles.ts chooseFallbackPrimary: hasMelee && !hasShot -> melee;
  // otherwise falls through to rangePref==="ranged" ? shot : melee).
  const hybridMelee = { ...base, id: "zzatk002a", hasMelee: true, hasShot: true, rangePref: "melee" as const };
  if (actionProfileForProfile(hybridMelee).primary !== "melee") {
    throw new Error("[selfcheck] resolver: melee-preferring hybrid synthetic profile should resolve primary=melee");
  }
  // MELEE WORKSTREAM UPDATE: hybrids with BOTH melee and shot defs now select by PROXIMITY
  // (combat.ts resolveBActionOrder — commandMoveTables B-far/B-close type-0/1 evidence), so
  // the enemy sits INSIDE the engage window here (100 < MELEE.ENGAGE_RANGE) where melee wins.
  const attacker = fakeRuntime("resolver_melee_hybrid", 0, 0);
  const enemy = fakeRuntime("resolver_melee_hybrid_enemy", 1, 100);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, hybridMelee],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  attacker.ammo = startingAmmoForProfile(hybridMelee);
  const result = pumpAttackFrame(attacker, hybridMelee, true, [attacker, enemy], profiles);
  if (attacker.state !== "attack" || attacker.anim !== "melee") {
    throw new Error(
      `[selfcheck] resolver: primary=melee hybrid held B should start melee: state=${attacker.state}, anim=${attacker.anim}`,
    );
  }
  if (result.length !== 0) {
    throw new Error("[selfcheck] resolver: primary=melee hybrid should not fire a shot on the same B press");
  }

  // And OUTSIDE the engage window, the same melee-primary hybrid selects the gun by
  // proximity instead of whiff-swinging at range (the B-far / type-0 path).
  const farAttacker = fakeRuntime("resolver_melee_hybrid_far", 0, 0);
  farAttacker.ammo = startingAmmoForProfile(hybridMelee);
  const farEnemy = fakeRuntime("resolver_melee_hybrid_far_enemy", 1, 400);
  const farProfiles = new Map([
    [farAttacker.uid, hybridMelee],
    [farEnemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const farResult = pumpAttackFrame(farAttacker, hybridMelee, true, [farAttacker, farEnemy], farProfiles);
  if (farResult.length === 0 || farAttacker.anim !== "shoot") {
    throw new Error(
      `[selfcheck] resolver: primary=melee hybrid far from any target should fire its gun (B-far/type-0): anim=${farAttacker.anim}, projectiles=${farResult.length}`,
    );
  }
  console.log(
    "[selfcheck] resolver: melee/shot hybrid selects by proximity — melee inside the engage window, gun outside it",
  );
}

function assertResolverPrimaryShotHybridFiresShotFirst(borgs: BorgStats[]): void {
  const base = buildProfile(borgById(borgs, "pl0615"));
  // Hybrid with rangePref "ranged" -> chooseFallbackPrimary picks "shot".
  const hybridShot = { ...base, id: "zzatk002b", hasMelee: true, hasShot: true, rangePref: "ranged" as const };
  if (actionProfileForProfile(hybridShot).primary !== "shot") {
    throw new Error("[selfcheck] resolver: ranged-preferring hybrid synthetic profile should resolve primary=shot");
  }
  const shooter = fakeRuntime("resolver_shot_hybrid", 0, 0);
  const enemy = fakeRuntime("resolver_shot_hybrid_enemy", 1, 220);
  shooter.ammo = startingAmmoForProfile(hybridShot);
  const startAmmo = shooter.ammo;
  const profiles = new Map([
    [shooter.uid, hybridShot],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const spawned = pumpAttackFrame(shooter, hybridShot, true, [shooter, enemy], profiles);
  if (spawned.length === 0 || shooter.ammo !== startAmmo - 1) {
    throw new Error(
      `[selfcheck] resolver: primary=shot hybrid held B should fire the shot first: spawned=${spawned.length}, ammo=${shooter.ammo}/${startAmmo}`,
    );
  }
  if (shooter.state !== "attack" || shooter.anim !== "shoot") {
    throw new Error(
      `[selfcheck] resolver: primary=shot hybrid should end up in the shoot anim: state=${shooter.state}, anim=${shooter.anim}`,
    );
  }
  console.log("[selfcheck] resolver: primary=shot hybrid at B held fires the shot first (ammo decremented, projectile spawned)");
}

function assertResolverMeleeOnlyNeverAttemptsShot(borgs: BorgStats[]): void {
  const base = buildProfile(borgById(borgs, "pl0615"));
  const meleeOnly = { ...base, id: "zzatk002c", hasMelee: true, hasShot: false };
  const action = actionProfileForProfile(meleeOnly);
  if (action.primary !== "melee" || action.shot !== null) {
    throw new Error(`[selfcheck] resolver: melee-only synthetic profile should have primary=melee, shot=null: ${JSON.stringify(action)}`);
  }
  const attacker = fakeRuntime("resolver_melee_only", 0, 0);
  const enemy = fakeRuntime("resolver_melee_only_enemy", 1, 220);
  enemy.hp = enemy.maxHp = 5000;
  attacker.ammo = 0; // melee-only borgs never carry ammo; confirms a shot cannot be attempted
  const profiles = new Map([
    [attacker.uid, meleeOnly],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const result = pumpAttackFrame(attacker, meleeOnly, true, [attacker, enemy], profiles);
  if (attacker.state !== "attack" || attacker.anim !== "melee" || result.length !== 0) {
    throw new Error(
      `[selfcheck] resolver: melee-only B should start melee and never spawn a shot: state=${attacker.state}, anim=${attacker.anim}, projectiles=${result.length}`,
    );
  }
  console.log("[selfcheck] resolver: melee-only (shot=null) at B starts melee; shot never attempted");
}

function assertResolverShotOnlyNeverAttemptsMelee(borgs: BorgStats[]): void {
  const base = buildProfile(borgById(borgs, "pl0615"));
  const shotOnly = { ...base, id: "zzatk002d", hasMelee: false, hasShot: true };
  const action = actionProfileForProfile(shotOnly);
  if (action.primary !== "shot" || action.melee !== null) {
    throw new Error(`[selfcheck] resolver: shot-only synthetic profile should have primary=shot, melee=null: ${JSON.stringify(action)}`);
  }
  const shooter = fakeRuntime("resolver_shot_only", 0, 0);
  const enemy = fakeRuntime("resolver_shot_only_enemy", 1, 220);
  shooter.ammo = startingAmmoForProfile(shotOnly);
  const profiles = new Map([
    [shooter.uid, shotOnly],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const spawned = pumpAttackFrame(shooter, shotOnly, true, [shooter, enemy], profiles);
  if (spawned.length === 0 || shooter.anim !== "shoot") {
    throw new Error(
      `[selfcheck] resolver: shot-only B should fire a shot: spawned=${spawned.length}, anim=${shooter.anim}`,
    );
  }
  console.log("[selfcheck] resolver: shot-only (melee=null) at B fires a shot");
}

function assertResolverSpecialHitsOnceAndSetsCooldown(borgs: BorgStats[]): void {
  // 6) X PRESS EDGE -> special AoE damages a borg in radius exactly once, sets cooldown.
  // SPECIALS-WORKSTREAM UPDATE: stepAttacks now edge-detects the X held boolean via the
  // specialHeld latch (mirroring attackHeld), so this test's first frame is a fresh edge
  // (latch empty) and the follow-up frames below exercise BOTH gates: a continued hold is
  // no longer a press at all (latch), and a genuine re-press is still blocked by the active
  // cooldown/attackLock — the original intent of this assert, adjusted to edge semantics.
  const base = buildProfile(borgById(borgs, "pl0615"));
  const attacker = fakeRuntime("resolver_special", 0, 0);
  const target = fakeRuntime("resolver_special_target", 1, 20); // inside SPECIAL.RADIUS (110)
  target.hp = target.maxHp = 5000;
  // Synthetic id: default AoE special profile; NOTE attacker.borgId stays the fakeRuntime
  // default pl0615, which has no OBSERVED_WIKI "X Charge" row — so the plain press-edge
  // (non-charging) X path is the one under test here.
  const profile = { ...base, id: "zzatk002e" };
  const profiles = new Map([
    [attacker.uid, profile],
    [target.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const specialCooldown = actionProfileForProfile(profile).special.cooldown;

  stepCooldowns(attacker);
  const result = stepAttacks(attacker, profile, false, true, [attacker, target], profiles);
  const damageAfterOneHit = target.maxHp - target.hp;
  if (damageAfterOneHit <= 0) {
    throw new Error("[selfcheck] resolver: X special did not damage a borg inside its radius");
  }
  if (attacker.cooldowns["special"] !== specialCooldown) {
    throw new Error(
      `[selfcheck] resolver: X special did not set its cooldown: got=${attacker.cooldowns["special"]}, want=${specialCooldown}`,
    );
  }
  if (attacker.state !== "special" || result.projectiles.length !== 0) {
    throw new Error(`[selfcheck] resolver: X special should enter the special state: state=${attacker.state}`);
  }

  // A continued HOLD is not a press (latch: no edge)...
  stepCooldowns(attacker);
  stepAttacks(attacker, profile, false, true, [attacker, target], profiles);
  // ...and a genuine release -> re-press while the cooldown/attackLock is still active is a
  // fresh edge but must ALSO not deal a second hit (cooldown gate unchanged).
  stepCooldowns(attacker);
  stepAttacks(attacker, profile, false, false, [attacker, target], profiles);
  stepCooldowns(attacker);
  stepAttacks(attacker, profile, false, true, [attacker, target], profiles);
  const damageAfterSecondPress = target.maxHp - target.hp;
  if (damageAfterSecondPress !== damageAfterOneHit) {
    throw new Error(
      `[selfcheck] resolver: X special should not re-hit on hold or on an in-cooldown re-press: first=${damageAfterOneHit}, after=${damageAfterSecondPress}`,
    );
  }
  console.log(
    `[selfcheck] resolver: X special hit the in-radius target exactly once (damage=${damageAfterOneHit}) and set cooldown=${attacker.cooldowns["special"]}`,
  );
}

function assertSameTeamDamageDivisor(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("attacker", 0, 0);
  const ally = fakeRuntime("ally", 0, 20);
  const enemy = fakeRuntime("enemy", 1, 20);
  // Synthetic id -> DEFAULT_SPECIAL (AoE archetype): G Red's real special became the
  // projectile-archetype G Crash in the specials workstream, which no longer radial-hits the
  // two adjacent victims this divisor test relies on. The divisor under test is archetype-
  // independent (it lives in computeSourceDamage), so the generic AoE keeps the intent.
  // attacker.borgId stays pl0615 (no 'X Charge' row) -> plain press-edge X fires immediately.
  const profile = { ...buildProfile(borgById(borgs, "pl0615")), id: "zzffdivisor" };
  const profiles = new Map([
    [attacker.uid, profile],
    [ally.uid, profile],
    [enemy.uid, profile],
  ]);

  stepAttacks(attacker, profile, false, true, [attacker, ally, enemy], profiles);

  const allyDamage = ally.maxHp - ally.hp;
  const enemyDamage = enemy.maxHp - enemy.hp;
  if (!(allyDamage > 0 && allyDamage < enemyDamage)) {
    throw new Error(`[selfcheck] same-team routed damage failed: ally=${allyDamage}, enemy=${enemyDamage}`);
  }
  console.log(`[selfcheck] same-team hit divisor reduced raw damage: ally=${allyDamage}, enemy=${enemyDamage}`);
}

// ---------------------------------------------------------------------------------------
// ATK-014: friendly-fire regression tests. ROM: same team && !(flagsA & 0x1000) -> x0.25
// (FLOAT_80437024); (flagsA & 0x1000) && victim+0x59c & 0x1000 -> /40; floor at 1
// (zz_003cd5c_ step 18, behavior-notes.md (ah)/(o), chunk_0004.c:6811-6821). Port:
// damageFormula.ts:133-138; teammates hittable via canReceiveHit (combat.ts:118-120) in
// melee (:655) and special (:560) loops; projectiles hit any non-owner (:903).
// ---------------------------------------------------------------------------------------
function assertFriendlyFireFormulaExactly0p25x(borgs: BorgStats[]): void {
  // 1) Formula-level: identical hit context, enemy vs teammate victim -> teammate damage is
  //    exactly 0.25x (subject to the floor(1) and int truncation — computed THROUGH
  //    computeSourceDamage itself with only the victim's team swapped).
  //
  // defenderSideRank is pinned explicitly: computeSourceDamage's default side-rank picks
  // Challenge-NORMAL byte 0 for team 0 vs byte 1 for team 1 (defaultChallengeNormalSideRank,
  // damageFormula.ts), which would otherwise vary the defenseRankCurves multiplier between the
  // enemy (team 1) and teammate (team 0) calls below — a confound unrelated to the same-team
  // 0.25x reducer under test here. attackerSideRank is pinned for the same reason.
  const attackerProfile = buildProfile(borgById(borgs, "pl0615"));
  const victimProfile = buildProfile(borgById(borgs, "pl0008"));
  const attacker = fakeRuntime("ff_attacker", 0, 0);
  attacker.borgId = attackerProfile.id;
  const record = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);
  const pinnedSideRank = 16;

  const makeVictim = (team: number): BorgRuntime => {
    const v = fakeRuntime("ff_victim", team, 100);
    v.borgId = victimProfile.id;
    v.maxHp = v.hp = 10_000_000; // stabilize the defender hp-ratio curve index
    return v;
  };

  const enemyVictim = makeVictim(1);
  const teammateVictim = makeVictim(0); // same team as attacker (team 0)
  const enemyDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: enemyVictim,
    victimProfile,
    record,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  const teammateDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: teammateVictim,
    victimProfile,
    record,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  const expectedTeammateDamage = Math.max(1, Math.trunc(enemyDamage * 0.25));
  if (teammateDamage !== expectedTeammateDamage) {
    throw new Error(
      `[selfcheck] friendly fire: expected exactly 0.25x (floor 1) of enemy damage: enemy=${enemyDamage}, teammate=${teammateDamage}, expected=${expectedTeammateDamage}`,
    );
  }

  // 2) Synthetic record with flagsA = 0x1000: teammate damage NOT reduced (exemption channel).
  const exemptRecord: DamageRecord = { ...record, flagsA: record.flagsA | 0x1000 };
  const exemptTeammateVictim = makeVictim(0);
  const exemptTeammateDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: exemptTeammateVictim,
    victimProfile,
    record: exemptRecord,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  if (exemptTeammateDamage !== enemyDamage) {
    throw new Error(
      `[selfcheck] friendly fire: flagsA 0x1000 should exempt same-team hits from the 0.25x reducer: enemy=${enemyDamage}, exemptTeammate=${exemptTeammateDamage}`,
    );
  }

  // 5) blockDivisorActive + flagsA 0x1000 -> damage divided by 40 (formula-level; no sim
  //    caller yet — assert the formula path works so future guard wiring has coverage).
  const blockDivVictim = makeVictim(0);
  const blockDivDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: blockDivVictim,
    victimProfile,
    record: exemptRecord,
    blockDivisorActive: true,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  const expectedBlockDivDamage = Math.max(1, Math.trunc(enemyDamage / 40));
  if (blockDivDamage !== expectedBlockDivDamage) {
    throw new Error(
      `[selfcheck] friendly fire: blockDivisorActive + flagsA 0x1000 should divide by 40: got=${blockDivDamage}, expected=${expectedBlockDivDamage}`,
    );
  }

  console.log(
    `[selfcheck] friendly fire formula pinned: enemy=${enemyDamage}, teammate=${teammateDamage} (0.25x), ` +
      `flagsA-exempt teammate=${exemptTeammateDamage}, blockDiv/40=${blockDivDamage}`,
  );
}

function assertFriendlyFireMeleeSimLevel(borgs: BorgStats[]): void {
  // 3) Sim-level: two same-team borgs, one melee swing connecting -> teammate takes damage > 0
  //    (teammates are hittable via canReceiveHit) and less than the enemy-case damage.
  const profile = buildProfile(borgById(borgs, "pl0200")); // Sword Knight (melee-primary)
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));

  const runMelee = (victimTeam: number): number => {
    const attacker = fakeRuntime("ff_melee_attacker", 0, 0);
    attacker.borgId = profile.id;
    const victim = fakeRuntime("ff_melee_victim", victimTeam, 20);
    victim.hp = victim.maxHp = 5000;
    const profiles = new Map([
      [attacker.uid, profile],
      [victim.uid, victimTeam === 0 ? profile : enemyProfile],
    ]);
    pumpAttackFrame(attacker, profile, true, [attacker, victim], profiles);
    const meleeDef = actionProfileForProfile(profile).melee;
    if (!meleeDef) throw new Error("[selfcheck] friendly fire melee sim test needs a melee profile");
    for (let f = 0; f < meleeDef.startup + meleeDef.active + 2; f += 1) {
      pumpAttackFrame(attacker, profile, false, [attacker, victim], profiles);
    }
    return victim.maxHp - victim.hp;
  };

  const teammateDamage = runMelee(0);
  const enemyDamage = runMelee(1);
  if (!(teammateDamage > 0 && teammateDamage < enemyDamage)) {
    throw new Error(
      `[selfcheck] friendly fire: melee swing should damage a teammate but less than an enemy: teammate=${teammateDamage}, enemy=${enemyDamage}`,
    );
  }
  console.log(
    `[selfcheck] friendly fire melee sim: teammate hittable and reduced (teammate=${teammateDamage} < enemy=${enemyDamage})`,
  );
}

function assertFriendlyFireProjectileSimLevel(borgs: BorgStats[]): void {
  // 4) Projectile same-team: teammate hit consumes the projectile and applies reduced damage.
  const shooterProfile = buildProfile(borgById(borgs, "pl0102")); // Gatling Gunner
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));

  const shooter = fakeRuntime("ff_proj_shooter", 0, 0);
  shooter.borgId = shooterProfile.id;
  const teammateVictim = fakeRuntime("ff_proj_teammate", 0, 40);
  teammateVictim.hp = teammateVictim.maxHp = 5000;
  const enemyVictim = fakeRuntime("ff_proj_enemy", 1, 40);
  enemyVictim.hp = enemyVictim.maxHp = 5000;
  const profiles = new Map([
    [shooter.uid, shooterProfile],
    [teammateVictim.uid, shooterProfile],
    [enemyVictim.uid, enemyProfile],
  ]);
  const byUid = new Map([
    [shooter.uid, shooter],
    [teammateVictim.uid, teammateVictim],
    [enemyVictim.uid, enemyVictim],
  ]);

  const projTeammate = fakeProjectile("ff_proj_1", { x: 40, y: 0, z: 0 }, { x: 0, y: 0, z: 0 });
  projTeammate.ownerUid = shooter.uid;
  projTeammate.team = shooter.team;
  projTeammate.damage = 20;
  projTeammate.hitRadius = 50;

  const survivorsAfterTeammateHit = stepProjectiles(
    [projTeammate],
    [shooter, teammateVictim],
    profiles,
    byUid,
  );
  const teammateDamage = teammateVictim.maxHp - teammateVictim.hp;
  if (survivorsAfterTeammateHit.length !== 0) {
    throw new Error("[selfcheck] friendly fire: same-team projectile hit should be consumed, not survive");
  }
  if (teammateDamage <= 0) {
    throw new Error("[selfcheck] friendly fire: same-team projectile hit dealt no damage");
  }

  const projEnemy = fakeProjectile("ff_proj_2", { x: 40, y: 0, z: 0 }, { x: 0, y: 0, z: 0 });
  projEnemy.ownerUid = shooter.uid;
  projEnemy.team = shooter.team;
  projEnemy.damage = 20;
  projEnemy.hitRadius = 50;
  stepProjectiles([projEnemy], [shooter, enemyVictim], profiles, byUid);
  const enemyDamage = enemyVictim.maxHp - enemyVictim.hp;

  if (!(teammateDamage < enemyDamage)) {
    throw new Error(
      `[selfcheck] friendly fire: projectile teammate damage should be reduced vs enemy damage: teammate=${teammateDamage}, enemy=${enemyDamage}`,
    );
  }
  console.log(
    `[selfcheck] friendly fire projectile sim: teammate hit consumed the projectile and applied reduced damage (teammate=${teammateDamage} < enemy=${enemyDamage})`,
  );
}

function assertTypeDamageMatrixWired(borgs: BorgStats[]): void {
  const missing = borgs.filter((borg) => typeCategoryForBorgId(borg.id) === null).map((borg) => borg.id);
  if (missing.length > 0) {
    throw new Error(`[selfcheck] borg ids missing type category: ${missing.slice(0, 8).join(", ")}`);
  }
  if (typeCategoryForBorgId("pl0b00") !== 15 || typeCategoryForBorgId("pl0701") !== 12) {
    throw new Error("[selfcheck] type category remap changed for pl0b00/pl0701");
  }
  if (typeDamageMultiplier("pl0b00", "pl0701") !== 1.25) {
    throw new Error("[selfcheck] type damage matrix expected pl0b00 -> pl0701 multiplier 1.25");
  }

  const attacker = fakeRuntime("attacker", 0, 0);
  const boosted = fakeRuntime("boosted", 1, 20);
  const neutral = fakeRuntime("neutral", 1, 25);
  attacker.borgId = "pl0b00";
  boosted.borgId = "pl0701";
  neutral.borgId = "pl0b00";

  const base = buildProfile(borgById(borgs, "pl0b00"));
  const attackerProfile = { ...base, id: "pl0b00", attack: 10, hasMelee: true, hasShot: false };
  const boostedProfile = { ...base, id: "pl0701", defense: 0, maxHp: 1000 };
  const neutralProfile = { ...base, id: "pl0b00", defense: 0, maxHp: 1000 };
  boosted.hp = boosted.maxHp = boostedProfile.maxHp;
  neutral.hp = neutral.maxHp = neutralProfile.maxHp;

  const profiles = new Map([
    [attacker.uid, attackerProfile],
    [boosted.uid, boostedProfile],
    [neutral.uid, neutralProfile],
  ]);

  stepAttacks(attacker, attackerProfile, false, true, [attacker, boosted, neutral], profiles);

  const boostedDamage = boosted.maxHp - boosted.hp;
  const neutralDamage = neutral.maxHp - neutral.hp;
  if (!(boostedDamage > neutralDamage)) {
    throw new Error(`[selfcheck] type damage was not applied: boosted=${boostedDamage}, neutral=${neutralDamage}`);
  }
  console.log(`[selfcheck] type matrix maps ${borgs.length} borgs and boosts pl0b00 -> pl0701 damage: ${boostedDamage} > ${neutralDamage}`);
}

function assertMeleeRefreshesInvincibility(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("attacker", 0, 0);
  const enemy = fakeRuntime("enemy", 1, 20);
  const profile = buildProfile(borgById(borgs, "pl0200"));
  attacker.borgId = profile.id;
  const profiles = new Map([
    [attacker.uid, profile],
    [enemy.uid, profile],
  ]);

  stepAttacks(attacker, profile, true, false, [attacker, enemy], profiles);

  if (attacker.invincTimer !== WAKE_UP_INVINCIBILITY_FRAMES) {
    throw new Error(`[selfcheck] melee i-frame refresh failed: invincTimer=${attacker.invincTimer}`);
  }
  console.log(`[selfcheck] melee active handler refreshed i-frames to ${attacker.invincTimer}`);
}

function assertAiKeepsLockedTarget(borgs: BorgStats[]): void {
  const self = fakeRuntime("self", 0, 0);
  const closerEnemy = fakeRuntime("closer", 1, -800);
  const lockedEnemy = fakeRuntime("locked", 1, 900);
  self.lockTarget = lockedEnemy.uid;

  const input = stepAI(self, buildProfile(borgById(borgs, "pl0615")), [self, closerEnemy, lockedEnemy]);
  // Locked AI emits TARGET-RELATIVE movement (+moveZ = toward the lock target — stepMovement's
  // resolveHorizontalIntent resolves the stick relative to the lock vector). Had the AI dropped
  // the lock for the nearer enemy, lockedToTarget would be false and it would emit the
  // world-space fallback (moveX toward x=-800, i.e. negative).
  if (!(input.moveZ > 0 && input.moveX === 0)) {
    throw new Error("[selfcheck] AI target memory failed: ignored valid lockTarget for nearer enemy");
  }
  console.log("[selfcheck] AI kept valid lockTarget before nearest-enemy fallback (lock-relative approach)");
}

function assertFrozenBattleTimerNeverExpires(borgs: BorgStats[]): void {
  // DERIVED — Challenge writes timeLimit=18000 AND the pause flag [0x50]=1
  // (chunk_0048.c:390-392); the countdown zz_0029b58_ (chunk_0003.c:4631-4638)
  // and the judge's timeout branches (chunk_0003.c:4519-4529/4547-4553) are all
  // gated on [0x50]==0. A frozen-timer battle must never resolve to "draw" by
  // time; a running-timer battle must.
  const mk = (timerFrozen: boolean) =>
    createBattle(
      {
        stageId: "st00",
        forces: [
          { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
          { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
        ],
        bounds: { x: 4000, z: 4000 },
        // Spawn the two forces far apart so nobody dies inside the window.
        spawnPoints: [
          { pos: { x: -3500, y: 10, z: -3500 } },
          { pos: { x: 3500, y: 10, z: 3500 } },
        ],
        timeLimitFrames: 30,
        timerFrozen,
      },
      borgs,
    );
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };

  const frozen = mk(true);
  for (let f = 0; f < 90; f++) frozen.step(1 / 60, idleInputs);
  if (frozen.state.result === "draw") {
    throw new Error("[selfcheck] frozen battle timer expired: Challenge-style timer must never time out");
  }
  if (frozen.state.timeRemainingFrames !== 30) {
    throw new Error(
      `[selfcheck] frozen battle timer ticked: timeRemainingFrames=${frozen.state.timeRemainingFrames}, want 30`,
    );
  }

  const running = mk(false);
  let drawFrame = -1;
  for (let f = 0; f < 90; f++) {
    running.step(1 / 60, idleInputs);
    if (running.state.result === "draw") {
      drawFrame = f;
      break;
    }
  }
  if (drawFrame < 0) {
    throw new Error("[selfcheck] running battle timer never expired (expected timeout draw at ~30 frames)");
  }
  console.log(
    `[selfcheck] battle timer [0x50] gate ok: frozen timer held at 30 frames; running timer drew at frame ${drawFrame}`,
  );
}

function assertSpawnDeployLockDuration(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
      ],
      bounds: { x: 4000, z: 4000 },
      spawnPoints: [
        { pos: { x: -3500, y: 10, z: -3500 } },
        { pos: { x: 3500, y: 10, z: 3500 } },
      ],
    },
    borgs,
  );
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const activeNow = () => battle.state.borgs.find((b) => b.uid === activeUid);
  if (!activeNow()) throw new Error("[selfcheck] spawn duration test lost p1 borg");
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };

  for (let f = 0; f < STATE.SPAWN_DURATION - 1; f += 1) battle.step(1 / 60, idleInputs);
  if (activeNow()?.state !== "spawn") {
    throw new Error(`[selfcheck] spawn lock ended early at frame ${STATE.SPAWN_DURATION - 1}`);
  }
  battle.step(1 / 60, idleInputs);
  const after = activeNow();
  if (after?.state !== "idle") {
    throw new Error(`[selfcheck] spawn lock did not end at ${STATE.SPAWN_DURATION} frames: ${after?.state}`);
  }
  console.log(`[selfcheck] spawn deploy lock matched source total ${STATE.SPAWN_DURATION} frames`);
}

function assertDeathAccountingAtKillEvent(borgs: BorgStats[]): void {
  // DERIVED - kill-event accounting is immediate in zz_002f8dc_
  // (chunk_0003.c:8212-8330), while borg_death_entry/animation is a separate path
  // (zz_005bbc0_, chunk_0007.c:3716-3751). Team force energy should drop as soon as
  // HP reaches 0, but the next queued borg should still wait for the death timer.
  const firstEnemyId = "pl0008";
  const nextEnemyId = "pl000c";
  const firstEnemyProfile = buildProfile(borgById(borgs, firstEnemyId));
  const nextEnemyProfile = buildProfile(borgById(borgs, nextEnemyId));
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: [firstEnemyId, nextEnemyId] },
      ],
      bounds: { x: 4000, z: 4000 },
      spawnPoints: [
        { pos: { x: -3500, y: 10, z: -3500 } },
        { pos: { x: 3500, y: 10, z: 3500 } },
      ],
    },
    borgs,
  );
  const enemy = battle.state.borgs.find((b) => b.team === 1 && b.borgId === firstEnemyId);
  if (!enemy) throw new Error("[selfcheck] death accounting test lost first enemy");
  const startEnergy = battle.state.energy[1] ?? 0;
  const expectedStart = firstEnemyProfile.energy + nextEnemyProfile.energy;
  if (startEnergy !== expectedStart) {
    throw new Error(`[selfcheck] unexpected starting enemy energy: ${startEnergy}, want ${expectedStart}`);
  }

  enemy.hp = 1;
  enemy.invincTimer = 0;
  enemy.state = "idle";
  const dealt = applyHit(
    enemy,
    firstEnemyProfile,
    9999,
    0,
    { x: 0, y: 0, z: 0 },
    { x: enemy.pos.x, y: enemy.pos.y, z: enemy.pos.z - 10 },
  );
  const enemyStateAfterHit = enemy.state as BorgRuntime["state"];
  if (dealt <= 0 || enemy.hp !== 0 || enemyStateAfterHit !== "death") {
    throw new Error(`[selfcheck] lethal hit did not enter death state: dealt=${dealt}, hp=${enemy.hp}, state=${enemy.state}`);
  }

  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };
  battle.step(1 / 60, idleInputs);
  if ((battle.state.defeated[1] ?? 0) !== 1 || (battle.state.defeatedEnergy[1] ?? 0) !== firstEnemyProfile.energy) {
    throw new Error(
      `[selfcheck] kill-event defeated counters wrong: defeated=${battle.state.defeated[1]}, energy=${battle.state.defeatedEnergy[1]}`,
    );
  }
  if ((battle.state.energy[1] ?? 0) !== nextEnemyProfile.energy) {
    throw new Error(
      `[selfcheck] enemy force energy did not drop at kill event: got ${battle.state.energy[1]}, want queued ${nextEnemyProfile.energy}`,
    );
  }
  const enemyStateAfterAccounting = enemy.state as BorgRuntime["state"];
  if (!enemy.alive || !enemy.defeatAccounted || enemyStateAfterAccounting !== "death") {
    throw new Error("[selfcheck] death visual state should remain alive-but-accounted until removal");
  }
  if (battle.state.borgs.some((b) => b.team === 1 && b.borgId === nextEnemyId)) {
    throw new Error("[selfcheck] next enemy deployed before death-state removal");
  }

  let deployed = false;
  for (let f = 0; f < STATE.DEATH_DURATION + 2; f += 1) {
    battle.step(1 / 60, idleInputs);
    deployed = battle.state.borgs.some((b) => b.team === 1 && b.borgId === nextEnemyId);
    if (deployed) break;
  }
  if (!deployed) throw new Error("[selfcheck] queued enemy did not deploy after death timer");
  if ((battle.state.defeated[1] ?? 0) !== 1 || (battle.state.defeatedEnergy[1] ?? 0) !== firstEnemyProfile.energy) {
    throw new Error("[selfcheck] death timer double-counted defeated energy");
  }
  console.log("[selfcheck] kill-event force accounting is immediate; queued deploy still waits for death timer");
}

/**
 * W17 (wiki-mechanics-queue.md): a player whose force is exhausted while a same-team ally
 * still fights respawns as the hidden pl0f07 husk (1 HP / 1 ammo, live-verified via GDB
 * probe of the owned 2v2 save), keeps respawning per husk death, contributes 0 energy,
 * and is excluded from the defeated counters. No husk once every allied force is gone.
 */
function assertHuskDeploysOnForceExhaustion(borgs: BorgStats[]): void {
  const gRed = borgs.find((b) => b.id === "pl0615");
  if (!gRed) throw new Error("[selfcheck] husk test needs pl0615 in borgs.json");
  const gRedProfile = buildProfile(gRed);

  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 0, ownerPlayer: null, borgIds: ["pl0615"] }, // the surviving ally force
        { team: 1, ownerPlayer: null, borgIds: ["pl0615"] },
      ],
      bounds: { x: 4000, z: 4000 },
      spawnPoints: [
        { pos: { x: -3500, y: 10, z: -3500 } },
        { pos: { x: -3500, y: 10, z: 0 } },
        { pos: { x: 3500, y: 10, z: 3500 } },
      ],
    },
    borgs,
  );
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };
  const killActive = (uid: string): void => {
    const b = battle.state.borgs.find((x) => x.uid === uid);
    if (!b) throw new Error(`[selfcheck] husk test lost borg ${uid}`);
    b.invincTimer = 0;
    b.state = "idle";
    // Victim profile only shapes damage scaling; 9999 is lethal for any test borg.
    applyHit(b, gRedProfile, 9999, 0, { x: 0, y: 0, z: 0 }, { x: b.pos.x, y: b.pos.y, z: b.pos.z - 10 });
  };
  const stepUntil = (pred: () => boolean, label: string): void => {
    for (let f = 0; f < STATE.DEATH_DURATION + 60; f += 1) {
      battle.step(1 / 60, idleInputs);
      if (pred()) return;
    }
    throw new Error(`[selfcheck] husk test timed out waiting for ${label}`);
  };
  const p1Active = (): BorgRuntime | undefined =>
    battle.state.borgs.find((b) => b.ownerPlayer === "p1" && b.alive && b.hp > 0);

  const first = p1Active();
  if (!first || first.borgId !== "pl0615") throw new Error("[selfcheck] husk test: p1 borg missing at start");

  // Exhaust p1's force -> the husk must deploy in its place.
  killActive(first.uid);
  stepUntil(() => p1Active()?.borgId === HUSK_BORG_ID, "first husk deploy");
  const husk = p1Active();
  if (!husk) throw new Error("[selfcheck] husk vanished after deploy");
  if (husk.hp !== 1 || husk.maxHp !== 1 || husk.ammo !== 1) {
    throw new Error(`[selfcheck] husk stats wrong: hp=${husk.hp}/${husk.maxHp}, ammo=${husk.ammo} (want 1/1, 1)`);
  }
  if ((battle.state.energy[0] ?? 0) !== gRedProfile.energy) {
    throw new Error(
      `[selfcheck] husk must add 0 energy: team0=${battle.state.energy[0]}, want ally-only ${gRedProfile.energy}`,
    );
  }
  if ((battle.state.defeated[0] ?? 0) !== 1) {
    throw new Error(`[selfcheck] defeated[0] after real-borg death: ${battle.state.defeated[0]}, want 1`);
  }
  if (battle.state.result !== "ongoing") throw new Error("[selfcheck] battle ended by husk deploy");

  // Husk death -> another husk (respawns while the ally fights), still uncounted.
  killActive(husk.uid);
  stepUntil(() => {
    const active = p1Active();
    return !!active && active.borgId === HUSK_BORG_ID && active.uid !== husk.uid;
  }, "husk respawn");
  if ((battle.state.defeated[0] ?? 0) !== 1 || (battle.state.defeatedEnergy[0] ?? 0) !== gRedProfile.energy) {
    throw new Error(
      `[selfcheck] husk death must not count: defeated=${battle.state.defeated[0]}, energy=${battle.state.defeatedEnergy[0]}`,
    );
  }

  // Ally falls -> team 0 has no real force left: battle resolves, no fresh husk chain.
  const ally = battle.state.borgs.find((b) => b.team === 0 && b.ownerPlayer === null && b.alive && b.hp > 0);
  if (!ally || ally.borgId !== "pl0615") throw new Error("[selfcheck] husk test lost the ally borg");
  killActive(ally.uid);
  stepUntil(() => battle.state.result !== "ongoing", "battle resolution after ally death");
  // step() mutates result; re-widen past the earlier "ongoing" narrowing (same pattern as
  // assertDeathAccountingAtKillEvent's state casts).
  const finalResult: string = battle.state.result;
  if (finalResult !== "lose") {
    throw new Error(`[selfcheck] expected p1 loss once all real team-0 forces fell: ${finalResult}`);
  }
  console.log("[selfcheck] W17 husk: deploys on force exhaustion, respawns, 0 energy, uncounted, ends with ally");
}

function assertActorParamTierMatchesCClamp(): void {
  const state = resetActorParamTier();
  expectParamTierState(state, PARAM_TIER_RESET, 0, 0, "reset");

  const up = applyActorParamTierDelta63(state, 100);
  if (up !== 47) throw new Error(`[selfcheck] param-tier +63 applied delta mismatch: up=${up}`);
  expectParamTierState(state, 0x3f, 47, PARAM_TIER_TIMER_FRAMES, "+63 clamp");

  const saturated = applyActorParamTierDelta63(state, 1);
  if (saturated !== 0) throw new Error(`[selfcheck] param-tier saturation applied delta mismatch: ${saturated}`);
  expectParamTierState(state, 0x3f, 47, PARAM_TIER_TIMER_FRAMES, "saturation");

  const down = applyActorParamTierDelta63(state, -200);
  if (down !== -126) throw new Error(`[selfcheck] param-tier -63 applied delta mismatch: down=${down}`);
  expectParamTierState(state, -0x3f, -79, PARAM_TIER_TIMER_FRAMES, "-63 clamp");

  const wide = resetActorParamTier();
  const wideDown = applyActorParamTierDelta127(wide, -200);
  const wideUp = applyActorParamTierDelta127(wide, 300);
  if (wideDown !== -143 || wideUp !== 254 || wide.tier !== 0x7f) {
    throw new Error(`[selfcheck] param-tier +/-127 clamp mismatch: down=${wideDown} up=${wideUp} state=${JSON.stringify(wide)}`);
  }
  console.log("[selfcheck] actor param-tier reset and delta clamps match recovered C");
}

function expectParamTierState(
  state: { tier: number; deltaAccum: number; timerFrames: number },
  tier: number,
  deltaAccum: number,
  timerFrames: number,
  label: string,
): void {
  if (state.tier !== tier || state.deltaAccum !== deltaAccum || state.timerFrames !== timerFrames) {
    throw new Error(`[selfcheck] param-tier ${label} mismatch: ${JSON.stringify(state)}`);
  }
}

function assertGaugeStaggerModel(borgs: BorgStats[]): void {
  // DERIVED model under test (see gauges.ts / combat.ts applyHit): no flat per-hit hitstun —
  // a hit interrupts only via down-gauge depletion, balance-gauge break, or forced reaction
  // flags (chunk_0003.c:6255-6263).
  const victimProfile = buildProfile(borgById(borgs, "pl0615")); // G RED
  const init = gaugeInitForBorgId("pl0615");
  if (init.balanceGaugeMax !== 500 || init.downGaugeBase !== 100) {
    throw new Error(`[selfcheck] G RED gauge init mismatch: ${JSON.stringify(init)}`);
  }
  const shotRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.SHOT); // record 0: down 25 / balance 25 / flags 1
  const meleeRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE); // record 1: flags 2 -> forced stagger
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  // 1) A single shot dents the gauges but must NOT put the victim into the "hit" state.
  const victim = fakeRuntime("gauge_shot", 1, 0);
  const dealt = applyHit(victim, victimProfile, 2, 0, noDir, from, false, shotRecord);
  if (dealt <= 0) throw new Error("[selfcheck] gauge model: shot hit dealt no HP damage");
  if (victim.state !== "idle" || (victim.cooldowns["hitstun"] ?? 0) !== 0) {
    throw new Error(`[selfcheck] gauge model: a single shot flinched the victim (state=${victim.state})`);
  }
  if (victim.balanceGauge !== 475 || victim.downGauge !== 75) {
    throw new Error(
      `[selfcheck] gauge model: shot gauge damage wrong: balance=${victim.balanceGauge}, down=${victim.downGauge}`,
    );
  }
  if (victim.balanceRefillDelay !== STAGGER.BALANCE_REFILL_DELAY) {
    throw new Error(`[selfcheck] gauge model: hit did not arm the 60f windows (${victim.balanceRefillDelay})`);
  }

  // 2) Repeated shots that deplete the balance gauge MUST stagger. A tank-like down gauge
  //    isolates the balance path (real borgs go up to 30000 down base, e.g. the boss entry).
  const tank = fakeRuntime("gauge_tank", 1, 0);
  tank.downGauge = tank.downGaugeBase = 30000;
  let staggerHit = -1;
  for (let i = 1; i <= 40; i += 1) {
    applyHit(tank, victimProfile, 2, 0, noDir, from, false, shotRecord);
    if (tank.state === "hit") {
      staggerHit = i;
      break;
    }
  }
  if (staggerHit !== 20) {
    // balance 500 / 25 per shot -> the 20th shot breaks the gauge.
    throw new Error(`[selfcheck] gauge model: balance break staggered at hit ${staggerHit}, want 20`);
  }
  if (tank.balanceGauge !== tank.balanceGaugeMax) {
    // The ROM refills the balance gauge to max IMMEDIATELY on break (chunk_0003.c:8014-8015).
    throw new Error(`[selfcheck] gauge model: balance not refilled on break (${tank.balanceGauge})`);
  }
  if (tank.invincTimer !== STAGGER.STAGGER_IFRAMES) {
    throw new Error(`[selfcheck] gauge model: stagger i-frames missing (${tank.invincTimer})`);
  }

  // 3) A melee hit (record 1, reactionFlags bit 2) staggers immediately and resets the down gauge.
  const meleeVictim = fakeRuntime("gauge_melee", 1, 0);
  applyHit(meleeVictim, victimProfile, 2, 0, noDir, from, false, meleeRecord);
  if (meleeVictim.state !== "hit") {
    throw new Error(`[selfcheck] gauge model: forced-flag melee hit did not stagger (state=${meleeVictim.state})`);
  }
  if (meleeVictim.downGauge !== meleeVictim.downGaugeBase) {
    throw new Error(`[selfcheck] gauge model: stagger did not reset the down gauge (${meleeVictim.downGauge})`);
  }
  // DERIVED — the 60 stagger i-frames are BALANCE-BREAK ONLY (zz_005c290_ gates the +0x720
  // write on 0x6fd & 0x80, chunk_0007.c:3985-4050). A flag-forced melee stagger must NOT
  // grant them, or melee chains throttle to one damaging hit per stagger.
  if (meleeVictim.invincTimer !== 0) {
    throw new Error(
      `[selfcheck] gauge model: flag-forced stagger wrongly granted i-frames (${meleeVictim.invincTimer})`,
    );
  }

  // 4) 60+ hit-free frames refill the balance gauge to max (and reset the down gauge).
  const recovering = fakeRuntime("gauge_refill", 1, 0);
  applyHit(recovering, victimProfile, 2, 0, noDir, from, false, shotRecord);
  for (let f = 0; f < STAGGER.BALANCE_REFILL_DELAY - 1; f += 1) stepGaugeWindows(recovering);
  if (recovering.balanceGauge !== 475) {
    throw new Error(`[selfcheck] gauge model: balance refilled early (${recovering.balanceGauge})`);
  }
  stepGaugeWindows(recovering);
  if (recovering.balanceGauge !== recovering.balanceGaugeMax || recovering.downGauge !== recovering.downGaugeBase) {
    throw new Error(
      `[selfcheck] gauge model: 60f windows did not restore gauges: balance=${recovering.balanceGauge}, down=${recovering.downGauge}`,
    );
  }

  console.log(
    "[selfcheck] gauge stagger model OK: shots don't flinch, balance break staggers at hit 20 " +
      "(refill-to-max + 60 i-frames), forced melee staggers immediately (no i-frames), " +
      "60f windows restore gauges",
  );
}

// ---------------------------------------------------------------------------------------
// ATK-013: resistance/falloff pin-down tests. The wiki's "hidden per-target damage
// resistance" is NOT a separate mechanic — it IS the already-ported combo-rank falloff
// (comboRankScale_802c7ca0, damageFormula.ts). See the guard comment above the falloff line
// in damageFormula.ts and research/tasks/attack-port/ATK-013-resistance-falloff-audit-note.md.
// ---------------------------------------------------------------------------------------
function assertResistanceFalloffPinned(borgs: BorgStats[]): void {
  const comboRankScale: number[] = (damageFormulaData as { comboRankScale_802c7ca0: number[] })
    .comboRankScale_802c7ca0;
  const attackerProfile = buildProfile(borgById(borgs, "pl0615"));
  const victimProfile = buildProfile(borgById(borgs, "pl0008"));
  const attacker = fakeRuntime("falloff_attacker", 0, 0);
  attacker.borgId = attackerProfile.id;
  // Large hpDamage minimizes Math.trunc() rounding noise so the outputs' ratios closely
  // track the extracted table ratios (computeSourceDamage truncates once, at the very end).
  const bigRecord: DamageRecord = { ...damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE), hpDamage: 1_000_000 };

  // 1) Same victim hit repeatedly fast enough to roll the accumulator: damage at comboRank
  //    0,1,2,3 must track the extracted falloff table's ratios (via computeSourceDamage).
  const dmgAtRank = (rank: number): number => {
    const victim = fakeRuntime("falloff_victim", 1, 100);
    victim.borgId = victimProfile.id;
    victim.maxHp = victim.hp = 10_000_000; // keep hp-ratio curve index stable across ranks
    victim.comboRank = rank;
    return computeSourceDamage({
      attacker,
      attackerProfile,
      victim,
      victimProfile,
      record: bigRecord,
    });
  };
  const d0 = dmgAtRank(0);
  const d1 = dmgAtRank(1);
  const d2 = dmgAtRank(2);
  const d3 = dmgAtRank(3);
  if (d0 <= 0) throw new Error("[selfcheck] resistance falloff: baseline comboRank 0 damage was <=0");
  for (const [rank, dmg] of [
    [0, d0],
    [1, d1],
    [2, d2],
    [3, d3],
  ] as const) {
    const expectedRatio = comboRankScale[rank] ?? 1;
    const actualRatio = dmg / d0;
    if (Math.abs(actualRatio - expectedRatio) > 1e-3) {
      throw new Error(
        `[selfcheck] resistance falloff: comboRank ${rank} ratio ${actualRatio} did not match extracted table ratio ${expectedRatio} (d0=${d0}, dmg=${dmg})`,
      );
    }
  }

  // 2) flagsB & 0x4000 record: falloff skipped (damage independent of comboRank).
  const exemptRecord: DamageRecord = { ...bigRecord, flagsB: bigRecord.flagsB | 0x4000 };
  const exemptAtRank = (rank: number): number => {
    const victim = fakeRuntime("falloff_exempt_victim", 1, 100);
    victim.borgId = victimProfile.id;
    victim.maxHp = victim.hp = 10_000_000;
    victim.comboRank = rank;
    return computeSourceDamage({
      attacker,
      attackerProfile,
      victim,
      victimProfile,
      record: exemptRecord,
    });
  };
  const e0 = exemptAtRank(0);
  const e3 = exemptAtRank(3);
  if (e0 <= 0 || e0 !== e3) {
    throw new Error(`[selfcheck] resistance falloff: flagsB 0x4000 record should skip falloff, e0=${e0} e3=${e3}`);
  }

  // 3) 60 frames without a hit (stepGaugeWindows) -> comboAccum/comboRank reset -> damage
  //    back to full (i.e. matches the comboRank-0 case again through computeSourceDamage).
  const recovering = fakeRuntime("falloff_recover", 1, 100);
  recovering.borgId = victimProfile.id;
  recovering.maxHp = recovering.hp = 10_000_000;
  recovering.comboAccum = 42;
  recovering.comboRank = 3;
  recovering.comboWindow = STAGGER.COMBO_WINDOW;
  for (let f = 0; f < STAGGER.COMBO_WINDOW; f += 1) stepGaugeWindows(recovering);
  if (recovering.comboAccum !== 0 || recovering.comboRank !== 0) {
    throw new Error(
      `[selfcheck] resistance falloff: 60f window did not reset combo accumulator/rank: accum=${recovering.comboAccum}, rank=${recovering.comboRank}`,
    );
  }
  const dmgAfterReset = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: recovering,
    victimProfile,
    record: bigRecord,
  });
  if (Math.abs(dmgAfterReset / d0 - 1) > 1e-3) {
    throw new Error(
      `[selfcheck] resistance falloff: damage after 60f reset should match comboRank-0 baseline: dmgAfterReset=${dmgAfterReset}, d0=${d0}`,
    );
  }

  console.log(
    `[selfcheck] resistance falloff pinned: ranks 0-3 track extracted table ratios ` +
      `(${comboRankScale.slice(0, 4).join(", ")}); flagsB 0x4000 skips falloff; 60f window resets to full damage`,
  );
}

// ---------------------------------------------------------------------------------------
// Melee workstream: engage window + lunge + charge-lock + empty-ammo whiff gate + melee AI.
// Sim side: combat.ts resolveBActionOrder / targetWithinMeleeEngage / melee lunge drive /
// startMeleeAttack; constants.ts MELEE.ENGAGE_* and MELEE.LUNGE_* (all TUNED — the ROM's
// engage threshold FLOAT_8043762c is T1-blocked per behavior-notes.md (ai)/(av); the
// close=battle-attack mechanism is CONFIRMED_MANUAL per (ao)).
// ---------------------------------------------------------------------------------------
function assertContextualMeleeBeatsChargeAtEngageRange(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const meleeDef = actionProfileForProfile(gRed).melee;
  if (!meleeDef) throw new Error("[selfcheck] engage test needs G RED's melee def");
  if (!(MELEE.ENGAGE_RANGE > meleeDef.range)) {
    throw new Error(
      `[selfcheck] MELEE.ENGAGE_RANGE (${MELEE.ENGAGE_RANGE}) should extend beyond the damage reach (${meleeDef.range})`,
    );
  }
  const b = fakeRuntime("engage_charge", 0, 0);
  b.borgId = gRed.id;
  b.ammo = startingAmmoForProfile(gRed);
  // Target BEYOND the damage reach but INSIDE the engage window — before this workstream the
  // resolver only selected melee within meleeDef.range AND honored a banked charge first, so
  // this press charged the gun instead of swinging.
  const engageDist = Math.floor((meleeDef.range + MELEE.ENGAGE_RANGE) / 2);
  const enemy = fakeRuntime("engage_charge_enemy", 1, engageDist);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [b.uid, gRed],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  b.cooldowns["chargeFrames"] = 20; // banked charge must NOT keep the shot path first in context
  const spawned = pumpAttackFrame(b, gRed, true, [b, enemy], profiles);
  if (b.state !== "attack" || b.anim !== "melee" || spawned.length !== 0) {
    throw new Error(
      `[selfcheck] contextual B at engage range (${engageDist}) should select melee over a held charge: state=${b.state}, anim=${b.anim}, projectiles=${spawned.length}`,
    );
  }
  console.log(
    `[selfcheck] contextual B at ${engageDist} units (reach ${meleeDef.range}, engage ${MELEE.ENGAGE_RANGE}) selected melee over a banked charge`,
  );
}

function assertMeleeLungeClosesDistance(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const meleeDef = actionProfileForProfile(gRed).melee;
  if (!meleeDef) throw new Error("[selfcheck] lunge test needs G RED's melee def");
  const startDist = 150; // inside the engage window (180), well outside the reach (64)
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));
  const ctxBounds = { minX: -1000, maxX: 1000, minZ: -1000, maxZ: 1000 };

  const runOnce = (): { finalX: number; finalDist: number; victimHp: number } => {
    const attacker = fakeRuntime("lunge", 0, 0);
    attacker.borgId = gRed.id;
    attacker.ammo = startingAmmoForProfile(gRed);
    const victim = fakeRuntime("lunge_victim", 1, startDist);
    victim.hp = victim.maxHp = 5000;
    const profiles = new Map([
      [attacker.uid, gRed],
      [victim.uid, enemyProfile],
    ]);
    const ctx = { lockTargetPos: victim.pos, bounds: ctxBounds, collision: null };
    for (let f = 0; f < meleeDef.duration + 6; f += 1) {
      stepCooldowns(attacker);
      // Movement runs before attacks (battle.ts order): integrates the lunge velocity the
      // attack step set on the previous frame, with the combat-state MOVE.DECEL applied.
      stepMovement(attacker, gRed, emptyInput(), ctx);
      stepAttacks(attacker, gRed, f === 0, false, [attacker, victim], profiles);
      assertSane([attacker, victim], f);
    }
    return { finalX: attacker.pos.x, finalDist: distXZ(attacker.pos, victim.pos), victimHp: victim.hp };
  };

  const r1 = runOnce();
  const r2 = runOnce();
  if (r1.finalX !== r2.finalX || r1.victimHp !== r2.victimHp) {
    throw new Error(
      `[selfcheck] melee lunge is not deterministic: x=${r1.finalX}/${r2.finalX}, hp=${r1.victimHp}/${r2.victimHp}`,
    );
  }
  if (!(r1.finalDist < startDist - 50)) {
    throw new Error(`[selfcheck] melee lunge did not close distance: ${startDist} -> ${r1.finalDist}`);
  }
  if (r1.victimHp >= 5000) {
    throw new Error(
      `[selfcheck] lunge swing from ${startDist} units did not land its hit (final dist ${r1.finalDist}, reach ${meleeDef.range})`,
    );
  }
  console.log(
    `[selfcheck] melee lunge closed ${startDist} -> ${r1.finalDist.toFixed(1)} units deterministically and landed the swing`,
  );
}

function assertEmptyAmmoFarHoldDoesNotWhiffMelee(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615")); // primary:'shot' hybrid
  const b = fakeRuntime("noammo", 0, 0);
  b.borgId = gRed.id;
  b.ammo = 0; // empty magazine: the shot path is gated; the old fall-through air-swung here
  const enemy = fakeRuntime("noammo_enemy", 1, 600); // far outside the engage window
  const profiles = new Map([
    [b.uid, gRed],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  for (let f = 0; f < 30; f += 1) {
    const spawned = pumpAttackFrame(b, gRed, true, [b, enemy], profiles);
    if (spawned.length !== 0) {
      throw new Error("[selfcheck] empty-magazine far hold should not spawn projectiles");
    }
    if (b.anim === "melee" || b.state === "attack") {
      throw new Error(`[selfcheck] empty-ammo far-range hold whiff-swung at 600 units (frame ${f})`);
    }
  }
  console.log("[selfcheck] empty-ammo far-range hold no longer air-swings (whiff gate on the engage window)");
}

function assertMeleeAiReachesEngageAndHits(borgs: BorgStats[]): void {
  const swordKnight = buildProfile(borgById(borgs, "pl0200"));
  const meleeDef = actionProfileForProfile(swordKnight).melee;
  if (!meleeDef || swordKnight.rangePref === "ranged") {
    throw new Error("[selfcheck] melee AI test needs melee-pref Sword Knight");
  }
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0200"] }, // melee-pref CPU
      ],
      bounds: { minX: -1000, maxX: 1000, minZ: -1000, maxZ: 1000 },
      spawnPoints: [
        { pos: { x: -300, y: 10, z: 0 }, rotY: Math.PI / 2 },
        { pos: { x: 300, y: 10, z: 0 }, rotY: -Math.PI / 2 },
      ],
    },
    borgs,
  );
  const p1Uid = battle.state.activeUidByPlayer["p1"];
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };
  let minDist = Infinity;
  let sawMeleeSwing = false;
  let meleeHitFrame = -1;
  let prevHp = Infinity;
  for (let f = 0; f < 900 && meleeHitFrame < 0; f += 1) {
    battle.step(1 / 60, idleInputs);
    assertSane(battle.state.borgs, f);
    const p1 = battle.state.borgs.find((x) => x.uid === p1Uid);
    const cpu = battle.state.borgs.find((x) => x.team === 1);
    if (!p1 || !cpu) break;
    const d = distXZ(cpu.pos, p1.pos);
    minDist = Math.min(minDist, d);
    if (cpu.anim === "melee") sawMeleeSwing = true;
    // A melee hit: hp dropped this frame while the CPU is mid-swing within its reach
    // (a homing charge shot could also drop hp, but only the melee swing satisfies both).
    if (p1.hp < prevHp && cpu.anim === "melee" && d <= meleeDef.range + 5) meleeHitFrame = f;
    prevHp = p1.hp;
  }
  if (minDist > meleeDef.range + 5 || !sawMeleeSwing || meleeHitFrame < 0) {
    throw new Error(
      `[selfcheck] melee-pref AI failed to close and land melee from 600 units: minDist=${minDist.toFixed(1)}, swung=${sawMeleeSwing}, hitFrame=${meleeHitFrame}`,
    );
  }
  console.log(
    `[selfcheck] melee-pref AI closed 600 -> ${minDist.toFixed(1)} units and landed a melee hit at frame ${meleeHitFrame}`,
  );
}

// ---------------------------------------------------------------------------------------
// Specials workstream (sim runtime phase) asserts: broadened B-charge coverage, X press-edge
// semantics, projectile-archetype specials through the normal pipeline, and X-Charge
// hold/release (OBSERVED_WIKI rows in data/borgMoveProperties.json; TUNED tiers in combat.ts
// X_CHARGE).
// ---------------------------------------------------------------------------------------

/** (a) Every borg with an OBSERVED_WIKI "B Charge" row must resolve a chargeable shot —
 *  wave-1 broadened actionProfiles.json chargeable to the union of the family heuristic and
 *  the wiki "B Charge" rows; this pins that union roster-wide, anchored on G Red the same way
 *  assertChargeShotTiers is. */
function assertWikiBChargeRowsResolveChargeable(borgs: BorgStats[]): void {
  // Anchor first (mirrors assertChargeShotTiers): G Red (pl0615, hero line) carries a wiki
  // "B Charge" row and must resolve chargeable.
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  if (moveByButton(gRed.id, "B Charge") === null) {
    throw new Error("[selfcheck] G Red anchor lost its OBSERVED_WIKI 'B Charge' row");
  }
  if (!actionProfileForProfile(gRed).shot?.chargeable) {
    throw new Error("[selfcheck] G Red anchor: 'B Charge' row did not resolve chargeable:true");
  }
  let checked = 0;
  for (const stats of borgs) {
    if (moveByButton(stats.id, "B Charge") === null) continue;
    const shot = actionProfileForProfile(buildProfile(stats)).shot;
    if (!shot?.chargeable) {
      throw new Error(
        `[selfcheck] ${stats.id} has an OBSERVED_WIKI 'B Charge' move but resolves chargeable=${shot?.chargeable ?? "no shot def"}`,
      );
    }
    checked += 1;
  }
  // The harvest catalogs 34 'B Charge' rows; keep a loose floor so a data regen that drops
  // most of them fails loudly without pinning the exact count.
  if (checked < 30) {
    throw new Error(`[selfcheck] suspiciously few 'B Charge' rows resolved chargeable: ${checked}`);
  }
  console.log(`[selfcheck] all ${checked} OBSERVED_WIKI 'B Charge' borgs resolve chargeable shots`);
}

/** (b) Press-edge latch: holding X across the special's cooldown expiry fires exactly ONCE
 *  per press edge — the old held-as-pressed code re-fired on every cooldown expiry. Also
 *  verifies a fresh edge after cooldown fires again, and that the AI still lands specials
 *  under edge semantics (it holds for one decision frame per press). */
function assertSpecialFiresOncePerPressEdge(borgs: BorgStats[]): void {
  const base = buildProfile(borgById(borgs, "pl0615"));
  const profile = { ...base, id: "zzspecialedge" }; // default AoE special; borgId below is non-X-charge
  const attacker = fakeRuntime("special_edge", 0, 0);
  attacker.borgId = profile.id; // unknown id -> no OBSERVED_WIKI 'X Charge' row -> plain press-edge X
  const target = fakeRuntime("special_edge_target", 1, 20);
  target.hp = target.maxHp = 50000;
  const profiles = new Map([
    [attacker.uid, profile],
    [target.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const specialDef = actionProfileForProfile(profile).special;

  // One long HOLD spanning the whole cooldown + recovery: must hit exactly once.
  let hits = 0;
  let prevHp = target.hp;
  const holdFrames = specialDef.cooldown + specialDef.duration + 30;
  for (let f = 0; f < holdFrames; f += 1) {
    stepCooldowns(attacker);
    stepAttacks(attacker, profile, false, true, [attacker, target], profiles);
    if (target.hp < prevHp) hits += 1;
    prevHp = target.hp;
  }
  if (hits !== 1) {
    throw new Error(`[selfcheck] held X across cooldown expiry should fire exactly once, fired ${hits}x`);
  }
  // Release, then a fresh press edge (cooldown long since expired): second hit.
  stepCooldowns(attacker);
  stepAttacks(attacker, profile, false, false, [attacker, target], profiles);
  stepCooldowns(attacker);
  stepAttacks(attacker, profile, false, true, [attacker, target], profiles);
  if (target.hp >= prevHp) {
    throw new Error("[selfcheck] fresh X press edge after cooldown did not fire the special again");
  }

  // AI check (the ai.ts special block now paces presses off the specialHeld latch): a
  // melee-pref CPU with a close target must still land a special under edge semantics.
  const knight = buildProfile(borgById(borgs, "pl0200"));
  const cpu = fakeRuntime("special_edge_ai", 1, 0);
  cpu.borgId = knight.id;
  const aiTarget = fakeRuntime("special_edge_ai_target", 0, 60); // inside the AI's 120-unit special window
  aiTarget.hp = aiTarget.maxHp = 50000;
  const aiProfiles = new Map([
    [cpu.uid, knight],
    [aiTarget.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  let aiFired = false;
  for (let f = 0; f < 300 && !aiFired; f += 1) {
    stepCooldowns(cpu);
    const input = stepAI(cpu, knight, [cpu, aiTarget]);
    stepAttacks(cpu, knight, input.attack, input.special, [cpu, aiTarget], aiProfiles);
    if (cpu.state === "special") aiFired = true;
  }
  if (!aiFired) {
    throw new Error("[selfcheck] AI never fired a special under press-edge semantics");
  }
  console.log("[selfcheck] X special fires once per press edge (hold never re-fires; AI still specials)");
}

/** (c) Projectile-archetype special (wave-1 SpecialActionDef.archetype): G Red's X (G Crash,
 *  OBSERVED_WIKI) spawns a projectile carrying the CHARGE_OR_SPECIAL damage record, and that
 *  projectile flows through the NORMAL stepProjectiles pipeline — hit-target despawn reason,
 *  damage application, and burst-meter crediting via the applyHit `source` all intact. */
function assertProjectileArchetypeSpecialFiresThroughPipeline(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const specialDef = actionProfileForProfile(gRed).special;
  if (specialDef.archetype !== "projectile") {
    throw new Error(
      `[selfcheck] G Red's X special (G Crash) should be projectile-archetype, got ${specialDef.archetype}`,
    );
  }
  const attacker = fakeRuntime("special_proj", 0, 0); // borgId pl0615; rotY 0 faces +z
  attacker.ammo = startingAmmoForProfile(gRed);
  const enemy = fakeRuntime("special_proj_enemy", 1, 0);
  enemy.pos = { x: 0, y: 0, z: 150 }; // downrange of the +z muzzle
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, gRed],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  stepCooldowns(attacker);
  const res = stepAttacks(attacker, gRed, false, true, [attacker, enemy], profiles);
  const proj = res.projectiles[0];
  if (!proj || attacker.state !== "special") {
    throw new Error(
      `[selfcheck] projectile-archetype X press spawned nothing: projectiles=${res.projectiles.length}, state=${attacker.state}`,
    );
  }
  if (proj.damageRecordIndex !== DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL) {
    throw new Error(
      `[selfcheck] special projectile should carry the CHARGE_OR_SPECIAL record: got=${proj.damageRecordIndex}`,
    );
  }

  // Fly it through the normal pipeline with burst-meter plumbing attached.
  const byUid = new Map([
    [attacker.uid, attacker],
    [enemy.uid, enemy],
  ]);
  const burstMeters = { p1: createBurstMeter() };
  let flying = res.projectiles;
  for (let f = 0; f < 60 && flying.length > 0; f += 1) {
    flying = stepProjectiles(flying, [attacker, enemy], profiles, byUid, undefined, { burstMeters });
  }
  if (enemy.hp >= enemy.maxHp) {
    throw new Error("[selfcheck] special projectile never damaged the downrange target");
  }
  if (proj.despawnReason !== "hit-target") {
    throw new Error(
      `[selfcheck] special projectile should despawn via the normal hit-target path: got=${proj.despawnReason}`,
    );
  }
  if (burstMeters.p1.meter !== BURST.FILL_PER_HIT) {
    throw new Error(
      `[selfcheck] special projectile hit should credit the attacker's burst meter +${BURST.FILL_PER_HIT}: got=${burstMeters.p1.meter}`,
    );
  }
  console.log(
    `[selfcheck] projectile-archetype special (G Crash) hit downrange via the normal pipeline (record 2, burst +${BURST.FILL_PER_HIT})`,
  );
}

/** (d) X Charge (OBSERVED_WIKI 'X Charge' rows, 17 borgs): holding X accumulates
 *  xChargeFrames (capped at the tier-2 threshold) without firing; releasing fires the special
 *  scaled by the reached tier (X_CHARGE mirrors the B-charge tiers, TUNED), resets the
 *  accumulator, and the moveRuntime command status is live (no longer "x-charge-blocked"). */
function assertXChargeAccumulatesAndReleases(borgs: BorgStats[]): void {
  const cosmic = buildProfile(borgById(borgs, "pl0504")); // Cosmic Dragon: 'X Charge' row "Black Hole"
  if (xChargeMoveForBorgId("pl0504") === null) {
    throw new Error("[selfcheck] pl0504 should carry an OBSERVED_WIKI 'X Charge' row (Black Hole)");
  }
  const specialDef = actionProfileForProfile(cosmic).special;
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));

  const releaseAfterHold = (holdFrames: number): Projectile => {
    const b = fakeRuntime("xcharge", 0, 0);
    b.borgId = cosmic.id;
    b.ammo = startingAmmoForProfile(cosmic);
    const enemy = fakeRuntime("xcharge_enemy", 1, 500);
    const profiles = new Map([
      [b.uid, cosmic],
      [enemy.uid, enemyProfile],
    ]);
    for (let f = 0; f < holdFrames; f += 1) {
      stepCooldowns(b);
      const held = stepAttacks(b, cosmic, false, true, [b, enemy], profiles);
      if (held.projectiles.length > 0 || b.state === "special") {
        throw new Error("[selfcheck] X-charge borg fired while still holding X");
      }
    }
    const expectFrames = Math.min(X_CHARGE.TIER2_FRAMES, holdFrames);
    if ((b.cooldowns["xChargeFrames"] ?? 0) !== expectFrames) {
      throw new Error(
        `[selfcheck] xChargeFrames accumulated wrong: got=${b.cooldowns["xChargeFrames"]}, want=${expectFrames}`,
      );
    }
    stepCooldowns(b);
    const released = stepAttacks(b, cosmic, false, false, [b, enemy], profiles);
    const proj = released.projectiles[0];
    if (!proj || b.state !== "special") {
      throw new Error(
        `[selfcheck] X-charge release after ${holdFrames} held frames did not fire: projectiles=${released.projectiles.length}, state=${b.state}`,
      );
    }
    if ((b.cooldowns["xChargeFrames"] ?? 0) !== 0) {
      throw new Error("[selfcheck] xChargeFrames should reset on release");
    }
    if (b.cooldowns["special"] !== specialDef.cooldown) {
      throw new Error(
        `[selfcheck] X-charge release should arm the special cooldown: got=${b.cooldowns["special"]}, want=${specialDef.cooldown}`,
      );
    }
    return proj;
  };

  const tier0 = releaseAfterHold(3);
  const tier2 = releaseAfterHold(X_CHARGE.TIER2_FRAMES + 25); // also exercises the accumulator cap
  const ratio = tier2.damage / tier0.damage;
  if (Math.abs(ratio - X_CHARGE.TIER2_DAMAGE_MULT) > 1e-6) {
    throw new Error(
      `[selfcheck] X-charge tier-2 damage scaling wrong: ratio=${ratio}, want=${X_CHARGE.TIER2_DAMAGE_MULT}`,
    );
  }
  const binding = runtimeMoveBindingForBorgId("pl0504", "X Charge");
  if (binding?.commandStatus !== "x-charge-release") {
    throw new Error(
      `[selfcheck] moveRuntime 'X Charge' status should be live (x-charge-release): got=${binding?.commandStatus}`,
    );
  }
  console.log(
    `[selfcheck] X-charge holds accumulate (cap ${X_CHARGE.TIER2_FRAMES}f) and release-fire (tier2 x${ratio.toFixed(2)}); moveRuntime status live`,
  );
}

function fakeRuntime(uid: string, team: number, x: number): BorgRuntime {
  return {
    uid,
    borgId: "pl0615",
    team,
    ownerPlayer: team === 0 ? "p1" : null,
    hp: 100,
    maxHp: 100,
    pos: { x, y: 0, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 0,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 0,
    cooldowns: {},
    invincTimer: 0,
    // Modal gauge init (matches pl0615: balance 500, down 100 — data/gaugeInit.json).
    balanceGauge: 500,
    balanceGaugeMax: 500,
    downGauge: 100,
    downGaugeBase: 100,
    balanceRefillDelay: 0,
    downResetDelay: 0,
    comboWindow: 0,
    comboAccum: 0,
    comboRank: 0,
    paramTier: resetActorParamTier(),
      statusId: 0,
      statusTimer: 0,
      statusImmunityMask: 0,
      lockTarget: null,
      allyLockTarget: null,
      burstArmFrames: 0,
      burstActive: false,
      burstPaired: false,
      fusionPartnerUid: null,
      fusionState: 0,
      defeatAccounted: false,
      alive: true,
    };
  }

function fakeProjectile(uid: string, pos: Projectile["pos"], vel: Projectile["vel"]): Projectile {
  return {
    uid,
    ownerUid: "owner",
    team: 0,
    pos: { ...pos },
    vel: { ...vel },
    damage: 1,
    hitstun: 1,
    knockback: 0,
    homingTurn: 0,
    homingTarget: null,
    life: 10,
    hitRadius: 10,
    visualKind: "energy",
  };
}

export function main(): number {
  const borgs = loadBorgs();
  console.log(`[selfcheck] loaded ${borgs.length} borgs from borgs.json`);
  assertRectBoundsClamp(borgs);
  assertTriangleFloorGrounding(borgs);
  assertTriangleFloorEdgeBlocksMovement(borgs);
  assertCpuEnemyCannotWalkOffDisconnectedStage(borgs);
  assertCollisionSpawnUsesPlayableFloor(borgs);
  assertExactSpawnPointsOverrideRadialSpawn(borgs);
  assertDisconnectedSpawnRepairsUnsupportedCenter(borgs);
  assertTriangleWallCollision(borgs);
  assertTriangleCeilingCollision(borgs);
  assertPlayersAutoLockByDefault(borgs);
  assertAllyLockTargetsTeammate(borgs);
  assertActorDataStatsBound(borgs);
  assertLockRelativeControls(borgs);
  assertProjectileVisualKinds(borgs);
  assertProjectilesCullOutsideStageFloor();
  assertActionProfilesDrivePrimaryAttacks(borgs);
  assertMeleeComboChains(borgs);
  assertMeleeHitsOncePerSwing(borgs);
  assertChargeShotTiers(borgs);
  assertSwordBeamFinisher(borgs);
  assertActionProfileFallbackDefaults(borgs);
  assertResolverPrimaryMeleeHybridStartsMelee(borgs);
  assertResolverPrimaryShotHybridFiresShotFirst(borgs);
  assertResolverMeleeOnlyNeverAttemptsShot(borgs);
  assertResolverShotOnlyNeverAttemptsMelee(borgs);
  assertResolverChargeTierSelectsDamageRecord(borgs);
  assertResolverSpecialHitsOnceAndSetsCooldown(borgs);
  assertSameTeamDamageDivisor(borgs);
  assertFriendlyFireFormulaExactly0p25x(borgs);
  assertFriendlyFireMeleeSimLevel(borgs);
  assertFriendlyFireProjectileSimLevel(borgs);
  assertTypeDamageMatrixWired(borgs);
  assertMeleeRefreshesInvincibility(borgs);
  assertAiKeepsLockedTarget(borgs);
  assertFrozenBattleTimerNeverExpires(borgs);
  assertSpawnDeployLockDuration(borgs);
  assertDeathAccountingAtKillEvent(borgs);
  assertHuskDeploysOnForceExhaustion(borgs);
  assertActorParamTierMatchesCClamp();
  assertGaugeStaggerModel(borgs);
  assertResistanceFalloffPinned(borgs);
  assertContextualMeleeBeatsChargeAtEngageRange(borgs);
  assertMeleeLungeClosesDistance(borgs);
  assertEmptyAmmoFarHoldDoesNotWhiffMelee(borgs);
  assertMeleeAiReachesEngageAndHits(borgs);
  assertWikiBChargeRowsResolveChargeable(borgs);
  assertSpecialFiresOncePerPressEdge(borgs);
  assertProjectileArchetypeSpecialFiresThroughPipeline(borgs);
  assertXChargeAccumulatesAndReleases(borgs);

  // 1v3: human on team 0 (one G RED), CPU team 1 with three Death Borgs. The human is IDLE,
  // so the three AI-controlled CPU borgs must close, lock on, and wear G RED down — i.e. the
  // full pipeline (deploy -> AI seek -> movement -> melee/shot -> damage -> death -> win/lose)
  // has to function for the battle to resolve. A tight synthetic arena keeps it inside the
  // frame budget now that real collision-backed stages spawn away from the broad bounds edge.
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] }, // G RED
        { team: 1, ownerPlayer: null, borgIds: ["pl0008", "pl000c", "pl0105"] }, // 3 Death Borgs (CPU)
      ],
      bounds: { x: 40, z: 40 },
    },
    borgs,
  );

  const idle: PlayerInput = emptyInput();
  const inputs: Record<string, PlayerInput> = { p1: idle };

  let resolvedFrame = -1;
  // Asset-backed action profiles add per-borg attack recovery/reload, so the old generic
  // 1200-frame cap can stop just before the idle-player loss resolves.
  const MAX = 2400;
  for (let f = 0; f < MAX; f++) {
    battle.step(1 / 60, inputs);
    assertSane(battle.state.borgs, f);
    // also sanity-check energy values
    for (const k of Object.keys(battle.state.energy)) {
      const e = battle.state.energy[Number(k)];
      if (e !== undefined && !Number.isFinite(e)) throw new Error(`NaN energy team ${k} @frame ${f}`);
    }
    if (battle.state.result !== "ongoing" && resolvedFrame < 0) {
      resolvedFrame = f;
      break;
    }
  }

  const s = battle.state;
  console.log(
    `[selfcheck] frame=${s.frame} result=${s.result} energy=${JSON.stringify(s.energy)} ` +
      `aliveBorgs=${s.borgs.length} projectiles=${s.projectiles.length}`,
  );

  // With an idle human and AI Death Borgs swarming, either side can win, but the AI should
  // make *something* happen — assert energy actually changed from the start (combat occurred),
  // and that the sim never produced NaN (already checked each frame).
  const startEnergyT1 = borgs
    .filter((b) => ["pl0008", "pl000c", "pl0105"].includes(b.id))
    .reduce((a, b) => a + b.energy, 0);
  const t1Now = s.energy[1] ?? 0;
  const t0Now = s.energy[0] ?? 0;

  let ok = true;
  if (s.result === "ongoing") {
    console.error(`[selfcheck] FAIL: battle did not resolve within ${MAX} frames`);
    ok = false;
  } else {
    console.log(`[selfcheck] battle RESOLVED at frame ${resolvedFrame}: result=${s.result}`);
    // A resolution requires one team's energy to have hit 0.
    if ((s.energy[0] ?? -1) !== 0 && (s.energy[1] ?? -1) !== 0) {
      console.error("[selfcheck] FAIL: resolved but neither team's energy is 0");
      ok = false;
    }
  }

  console.log(`[selfcheck] team0 energy=${t0Now}, team1 energy=${t1Now} (team1 start=${startEnergyT1})`);

  if (ok) {
    console.log(`[selfcheck] PASS: sim ran ${s.frame} frames with no NaN and the battle resolved (${s.result}).`);
    return 0;
  }
  return 1;
}

// Execute when run directly.
if (import.meta.url === `file://${process.argv[1]}` || process.argv[1]?.endsWith("selfcheck.js")) {
  process.exit(main());
}
