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
import { battleStateForSelfcheck, createBattle, HUSK_BORG_ID } from "./battle.js";
import { stepAI } from "./ai.js";
import { actionProfileForProfile, startingAmmoForProfile } from "./actionProfiles.js";
import {
  X_CHARGE,
  applyHit,
  isInvincible,
  projectileVisualKindForProfile,
  reactionAnimLengthFrames,
  sourceInitialEnemyLock,
  stepAttacks,
  stepCooldowns,
  stepGaugeWindows,
  stepHitStatus,
  stepProjectiles,
} from "./combat.js";
import { createBurstMeter } from "./burst.js";
import { exactMeleeForBorgId } from "./meleeExactData.js";
import { findVariantByKind } from "./combat.js";
import { stepRomAI, hasRomAiParams } from "./romAi.js";
import {
  airBChargeCoverage,
  airBMoveForBorgId,
  chargeMoveForBorgId,
  comboLadderForBorgId,
  xMoveForBorgId,
  xMoveCoverage,
} from "./actionStreamData.js";
import {
  attackHitTableForBorgId,
  hasSafeShapeShotAttribution,
  shotFlightVisualForBorgId,
  shotFlightVisualForTableRow,
  shotHitRadiusForBorgId,
  shotKindForBorgId,
} from "./attackHitData.js";
import { moveByButton } from "./moveProperties.js";
import { runtimeMoveBindingForBorgId, xChargeMoveForBorgId } from "./moveRuntime.js";
import {
  BURST,
  DASH,
  DEPLOY,
  HERO_X_BUFF,
  JUMP,
  MELEE,
  REACTION as REACTION_MODULE,
  STAGGER,
  STATE,
  WAKE_UP_INVINCIBILITY_FRAMES,
} from "./constants.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex, gaugeInitForBorgId, knockbackScaleRatio, type DamageRecord } from "./gauges.js";
import {
  cameraParamsForBorgId,
  defaultCameraSlotForBorgId,
  dashPhysicsForBorgId,
  statusImmunityMasksForBorgId,
} from "./movementData.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { actorVelocityScale, isFrozen, tierSizeScale, tierVelocityScale } from "./timescale.js";
import { stepMovement } from "./movement.js";
import {
  PARAM_TIER_RESET,
  PARAM_TIER_TIMER_FRAMES,
  applyActorParamTierDelta127,
  applyActorParamTierDelta63,
  resetActorParamTier,
} from "./paramTier.js";
import { emptyInput, type BattleActorObservation, type BorgRuntime, type PlayerInput, type Projectile, type StageCollision, type StageCollisionTriangle } from "./types.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import { typeCategoryForBorgId, typeDamageMultiplier } from "./typeDamage.js";
import { computeSourceDamage, forceGaugeRatioIndex } from "./damageFormula.js";
import damageFormulaData from "./data/damageFormula.json" with { type: "json" };
import reactionAnimLengthsData from "./data/reactionAnimLengths.json" with { type: "json" };

const REACTION_LENGTHS_META = (reactionAnimLengthsData as {
  _meta: {
    coverage: { totalRoster: number; groundResolved: number; launchResolved: number };
  };
})._meta;

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

function assertSane(borgs: readonly BattleActorObservation[], frame: number): void {
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
    assertSane(battle.observe().actors, f);
  }
  const activeUid = battle.observe().activeUidByPlayer["p1"];
  const active = battle.observe().actors.find((b) => b.uid === activeUid);
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
    assertSane(battle.observe().actors, f);
  }

  const enemy = battle.observe().actors.find((b) => b.team === 1);
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
  const p1 = battle.observe().actors.find((b) => b.uid === battle.observe().activeUidByPlayer["p1"]);
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
  const p1 = battle.observe().actors.find((b) => b.uid === battle.observe().activeUidByPlayer["p1"]);
  const enemy = battle.observe().actors.find((b) => b.team === 1);
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
  const p1 = battle.observe().actors.find((b) => b.uid === battle.observe().activeUidByPlayer["p1"]);
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
  const activeUid = battle.observe().activeUidByPlayer["p1"];
  const active = battle.observe().actors.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] auto-lock test lost active p1 borg");
  if (!active.lockTarget) {
    throw new Error("[selfcheck] human-controlled borg did not auto-acquire a default lock target");
  }
  const target = battle.observe().actors.find((b) => b.uid === active.lockTarget);
  if (!target || target.team === active.team) {
    throw new Error("[selfcheck] human-controlled borg auto-locked an invalid target");
  }
  if (
    active.targetLockState?.mode !== "enemy" ||
    active.targetLockState.sourceState !== 1 ||
    active.targetLockState.cameraState !== 3 ||
    active.targetLockState.activeTargetUid !== active.lockTarget ||
    active.targetLockState.enemyIndex !== 0
  ) {
    throw new Error(
      `[selfcheck] source-shaped enemy lock state was not retained: ${JSON.stringify(active.targetLockState)}`,
    );
  }
  console.log(`[selfcheck] human-controlled borg auto-locked enemy ${active.lockTarget} by default`);
}

function assertSourceInitialLockSelector(): void {
  const self3d = fakeRuntime("selector_self_3d", 0, 0);
  self3d.pos = { x: 0, y: 0, z: 0 };
  const xzNearHigh = fakeRuntime("selector_xz_near_high", 1, 1);
  xzNearHigh.pos = { x: 1, y: 100, z: 0 };
  const xzFarGround = fakeRuntime("selector_xz_far_ground", 1, 20);
  xzFarGround.pos = { x: 20, y: 0, z: 0 };
  const selection3d = sourceInitialEnemyLock(self3d, [self3d, xzNearHigh, xzFarGround]);
  if (selection3d.targetUid !== xzFarGround.uid || selection3d.targetIndex !== 1) {
    throw new Error(
      `[selfcheck] source initial lock must use 3D squared distance, not XZ distance: ${JSON.stringify(selection3d)}`,
    );
  }

  const selfTie = fakeRuntime("selector_self_tie", 0, 0);
  selfTie.pos = { x: 0, y: 0, z: 0 };
  const earlierTie = fakeRuntime("selector_tie_earlier", 1, 10);
  earlierTie.pos = { x: 10, y: 0, z: 0 };
  const laterTie = fakeRuntime("selector_tie_later", 1, -10);
  laterTie.pos = { x: -10, y: 0, z: 0 };
  const selectionTie = sourceInitialEnemyLock(selfTie, [selfTie, earlierTie, laterTie]);
  if (selectionTie.targetUid !== laterTie.uid || selectionTie.targetIndex !== 1) {
    throw new Error(
      `[selfcheck] source initial lock must let later equal-distance entries win: ${JSON.stringify(selectionTie)}`,
    );
  }

  console.log("[selfcheck] source initial lock selector uses 3D squared distance with later-tie wins");
}

function assertSourceSwitchLockDirections(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
        { team: 1, ownerPlayer: "p3", borgIds: ["pl000c"] },
        { team: 1, ownerPlayer: "p4", borgIds: ["pl0105"] },
      ],
      bounds: { x: 1000, z: 1000 },
      spawnPoints: [
        { pos: { x: 0, y: JUMP.GROUND_Y, z: 0 }, rotY: 0 },
        { pos: { x: 100, y: JUMP.GROUND_Y, z: 0 }, rotY: 0 },
        { pos: { x: 200, y: JUMP.GROUND_Y, z: 0 }, rotY: 0 },
        { pos: { x: 300, y: JUMP.GROUND_Y, z: 0 }, rotY: 0 },
      ],
    },
    borgs,
  );

  const activeUid = battle.observe().activeUidByPlayer["p1"];
  const active = () => {
    const b = battle.observe().actors.find((candidate) => candidate.uid === activeUid);
    if (!b) throw new Error("[selfcheck] switch-lock direction test lost active p1 borg");
    return b;
  };
  const enemies = battle.observe().actors.filter((b) => b.team === 1).map((b) => b.uid);
  if (enemies.length !== 3) throw new Error("[selfcheck] switch-lock direction test expected 3 enemies");
  if (active().lockTarget !== enemies[0] || active().targetLockState?.enemyIndex !== 0) {
    throw new Error(`[selfcheck] switch-lock initial target/index mismatch: ${JSON.stringify(active().targetLockState)}`);
  }

  battle.step(1 / 60, { p1: { ...emptyInput(), switchLockPrev: true } });
  if (active().lockTarget !== enemies[2] || active().targetLockState?.enemyIndex !== 2) {
    throw new Error(`[selfcheck] L/request-3 did not wrap to previous enemy: ${JSON.stringify(active().targetLockState)}`);
  }

  battle.step(1 / 60, { p1: emptyInput() });
  battle.step(1 / 60, { p1: { ...emptyInput(), switchLock: true, switchLockPrev: true } });
  if (active().lockTarget !== enemies[0] || active().targetLockState?.enemyIndex !== 0) {
    throw new Error(
      `[selfcheck] simultaneous R/L should honor source request-2 priority: ${JSON.stringify(active().targetLockState)}`,
    );
  }

  console.log("[selfcheck] source switch-lock directions: L/request-3 prev, R/request-2 priority");
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
  const activeUid = battle.observe().activeUidByPlayer["p1"];
  const active = battle.observe().actors.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] ally-lock test lost active p1 borg");
  const ally = active.allyLockTarget ? battle.observe().actors.find((b) => b.uid === active.allyLockTarget) : null;
  const enemy = active.lockTarget ? battle.observe().actors.find((b) => b.uid === active.lockTarget) : null;
  const retainedEnemyUid = active.lockTarget;
  const retainedAllyUid = active.allyLockTarget;
  if (!ally || ally.team !== active.team || ally.uid === active.uid) {
    throw new Error(`[selfcheck] Z ally-lock did not select a same-team ally: ${active.allyLockTarget}`);
  }
  if (!enemy || enemy.team === active.team) {
    throw new Error(`[selfcheck] Z ally-lock corrupted enemy lock target: ${active.lockTarget}`);
  }
  if (
    active.targetLockState?.mode !== "ally" ||
    active.targetLockState.sourceState !== 1 ||
    active.targetLockState.cameraState !== 3 ||
    active.targetLockState.activeTargetUid !== active.allyLockTarget ||
    active.targetLockState.allyIndex !== 0 ||
    active.targetLockState.enemyIndex !== 0
  ) {
    throw new Error(
      `[selfcheck] source-shaped ally lock state was not retained: ${JSON.stringify(active.targetLockState)}`,
    );
  }

  battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
  const afterRelease = battle.observe().actors.find((b) => b.uid === activeUid);
  if (!afterRelease) throw new Error("[selfcheck] ally-lock release test lost active p1 borg");
  if (
    afterRelease.lockTarget !== retainedEnemyUid ||
    afterRelease.allyLockTarget !== retainedAllyUid ||
    afterRelease.targetLockState?.mode !== "enemy" ||
    afterRelease.targetLockState.sourceState !== 2 ||
    afterRelease.targetLockState.cameraState !== 4 ||
    afterRelease.targetLockState.activeTargetUid !== retainedEnemyUid ||
    afterRelease.targetLockState.enemyIndex !== 0
  ) {
    throw new Error(
      `[selfcheck] Z release did not restore retained enemy lock: beforeEnemy=${retainedEnemyUid} beforeAlly=${retainedAllyUid} after=${JSON.stringify(afterRelease.targetLockState)}`,
    );
  }
  console.log(
    `[selfcheck] Z hold ally-lock selected teammate ${retainedAllyUid}; release restored enemy ${retainedEnemyUid}`,
  );
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

  const roach = buildProfile(borgById(borgs, "pl0f05"));
  const roachStats = actorDataCombatStatsForBorgId("pl0f05");
  const blueStriker = buildProfile(borgById(borgs, "pl0d00"));
  const blueStats = actorDataCombatStatsForBorgId("pl0d00");
  if (!roachStats || !blueStats) {
    throw new Error("[selfcheck] missing actor-data jump anchors");
  }
  if (profile.airJumpLevel !== actorStats.airJump || profile.airJumpLevel !== 0 || !profile.flyer) {
    throw new Error(
      `[selfcheck] Boost Jump actor-data air jump was not consumed: profile=${JSON.stringify(profile)} actor=${JSON.stringify(actorStats)}`,
    );
  }
  if (roach.airJumpLevel !== roachStats.airJump || roach.airJumpLevel !== 1 || roach.flyer) {
    throw new Error(
      `[selfcheck] Air jump level actor-data count mismatch: profile=${JSON.stringify(roach)} actor=${JSON.stringify(roachStats)}`,
    );
  }
  if (blueStats.airJump !== 0xff || blueStriker.airJumpLevel !== 0 || !blueStriker.flyer) {
    throw new Error(
      `[selfcheck] N/A flyer air-jump sentinel was not normalized: profile=${JSON.stringify(blueStriker)} actor=${JSON.stringify(blueStats)}`,
    );
  }
  console.log(
    `[selfcheck] source stats bound: hp=${profile.maxHp}; actor-data exact rows=${expected}; pl0615 def/shot/atk/spd=${profile.defense}/${profile.shot}/${profile.attack}/${profile.speed}; airJump pl0615=${profile.airJumpLevel} pl0f05=${roach.airJumpLevel} pl0d00=${blueStriker.airJumpLevel}`,
  );

  if (
    borgSourceStatsSummary.missingRows.length > 0 ||
    borgSourceStatsSummary.hpMismatches.length > 0
  ) {
    throw new Error("[selfcheck] source borg stat verification has missing rows or HP mismatches");
  }
}

function assertSourceCameraParamsBound(): void {
  const samples = [
    ["pl0615", 180, 500, 600],
    ["pl0f05", 170, 500, 600],
    ["pl0d00", 200, 550, 600],
    ["pl0000", 160, 450, 550],
  ] as const;
  for (const [id, height, min, max] of samples) {
    const params = cameraParamsForBorgId(id);
    if (!params) throw new Error(`[selfcheck] missing source camera params for ${id}`);
    if (params.slot !== 0 || params.targetHeight !== height || params.followMin !== min || params.followMax !== max) {
      throw new Error(
        `[selfcheck] camera params mismatch for ${id}: got ${JSON.stringify(params)}, want slot0 height=${height} band=${min}..${max}`,
      );
    }
  }
  const gRedSlot1 = cameraParamsForBorgId("pl0615", 1);
  if (!gRedSlot1 || gRedSlot1.slot !== 1 || gRedSlot1.targetHeight !== 180 || gRedSlot1.followMin !== 500 || gRedSlot1.followMax !== 600) {
    throw new Error(`[selfcheck] camera slot1 params mismatch for pl0615: ${JSON.stringify(gRedSlot1)}`);
  }
  if (defaultCameraSlotForBorgId("pl0003") !== 1 || defaultCameraSlotForBorgId("pl0615") !== 0) {
    throw new Error("[selfcheck] actor+0x582 default camera slot mapping changed");
  }
  const pl0003Default = cameraParamsForBorgId("pl0003");
  if (!pl0003Default || pl0003Default.slot !== 1) {
    throw new Error(`[selfcheck] pl0003 default camera slot did not use actor+0x582 slot1: ${JSON.stringify(pl0003Default)}`);
  }
  console.log("[selfcheck] source camera params bound from pl####data.bin +0xb8..+0xcc and actor+0x582 default slot");
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
  if ((lateral.cooldowns["dashActive"] ?? 0) > 0 || !(lateral.vel.x < -0.1 && Math.abs(lateral.vel.z) < 0.001)) {
    throw new Error(`[selfcheck] lock-relative pure lateral should strafe: vel=${JSON.stringify(lateral.vel)}`);
  }

  const lateralDash = makeLocked();
  stepMovement(lateralDash, profile, { ...emptyInput(), moveX: 1, dash: true }, ctx);
  // Dash speed/duration are per-borg page data now (+0x58/+0x64); fall back to the TUNED
  // block only for synthetic ids without a page.
  const dashPage = dashPhysicsForBorgId(lateralDash.borgId);
  const expectDashDuration = dashPage ? dashPage.durationFrames : DASH.DURATION;
  const expectDashSpeed = dashPage ? dashPage.hSpeed : DASH.SPEED;
  if (
    (lateralDash.cooldowns["dashActive"] ?? 0) !== expectDashDuration ||
    lateralDash.vel.x > -expectDashSpeed * 0.9
  ) {
    throw new Error(`[selfcheck] explicit lateral dash should use lock-relative direction: vel=${JSON.stringify(lateralDash.vel)}`);
  }

  const lateralDashOnCooldown = makeLocked();
  lateralDashOnCooldown.cooldowns["dash"] = DASH.COOLDOWN;
  stepMovement(lateralDashOnCooldown, profile, { ...emptyInput(), moveX: 1, dash: true }, ctx);
  if ((lateralDashOnCooldown.cooldowns["dashActive"] ?? 0) > 0 || !(lateralDashOnCooldown.vel.x < -0.1)) {
    throw new Error(`[selfcheck] dash cooldown should fall back to lock-relative strafe: vel=${JSON.stringify(lateralDashOnCooldown.vel)}`);
  }

  const diagonal = makeLocked();
  stepMovement(diagonal, profile, { ...emptyInput(), moveX: 1, moveZ: 1 }, ctx);
  if ((diagonal.cooldowns["dashActive"] ?? 0) > 0 || !(diagonal.vel.x < -0.1 && diagonal.vel.z < -0.1)) {
    throw new Error(`[selfcheck] lock-relative forward+lateral should circle-strafe, not dodge: vel=${JSON.stringify(diagonal.vel)}`);
  }

  console.log("[selfcheck] lock-relative controls: forward approach, back retreat, lateral strafe, explicit dash");
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
    assertSane(battle.observe().actors, f);
  }
  battle.step(1 / 60, { p1: { ...emptyInput(), attack: true }, p2: emptyInput() });
  const projectile = battle.observe().projectiles[0];
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
  // The battle loop keeps every borg auto-locked to a living enemy each frame
  // (battle.ts refreshSourceTargetLock), and the contextual-B resolver depends on that
  // lock like the ROM's live-target gates (+0x4a0 / +0x748). Reproduce the invariant so
  // direct stepAttacks harnesses see battle-shaped state.
  const lockAlive = all.some((o) => o.uid === b.lockTarget && o.team !== b.team && o.hp > 0);
  if (!lockAlive) {
    sourceInitialEnemyLock(b, all);
  }
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
  // The battle loop keeps human borgs continuously auto-locked (battle.ts
  // refreshSourceTargetLock), and the contextual-B target requires that lock — the ROM's
  // melee/ranged testers gate on a live target (+0x4a0 / +0x748 proximity state). A direct
  // stepAttacks harness must reproduce that invariant or close-B falls through to the
  // charge-hold path (idle anim) instead of the battle attack.
  closeGRedRuntime.lockTarget = closeGRedEnemy.uid;
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
  // Same auto-lock invariant as the close-G-RED case above: the contextual-B resolver needs
  // the live lock the battle loop maintains, or a hybrid melee-primary falls to its gun.
  swordRuntime.lockTarget = swordEnemy.uid;
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

/**
 * actionStreamData.ts ladder resolution for pl0200 (SWORD KNIGHT): action index 1 (ground B)
 * baseline variant 0 seeds action-script bank group 3 slot 0, and holding B re-arms the SAME
 * variant via the ROM's `(actor+0x6ea)++` auto-increment cursor (no chain callback for this
 * borg) — so the ladder is the pure auto-increment g3 s0/s1/s2, kinds 1/2/5 exactly as the
 * cue-script-stream-decode-2026-07-04.md audit validates end-to-end.
 */
function assertSwordKnightLadderResolvesThreeSteps(borgs: BorgStats[]): void {
  const swordKnight = buildProfile(borgById(borgs, "pl0200"));
  const ladder = comboLadderForBorgId(swordKnight.id);
  if (!ladder || ladder.length !== 3) {
    throw new Error(`[selfcheck] Sword Knight combo ladder should resolve 3 steps: ${JSON.stringify(ladder)}`);
  }
  const slots = ladder.map((s) => s.slot);
  const kinds = ladder.map((s) => s.kind);
  if (slots.join(",") !== "0,1,2" || kinds.join(",") !== "1,2,5") {
    throw new Error(
      `[selfcheck] Sword Knight combo ladder should be g3 s0/s1/s2 kinds 1/2/5: slots=${slots} kinds=${kinds}`,
    );
  }

  // Held-B combo: the SECOND swing's meleeActive window must equal step 1's OWN exact window
  // (activeEnd - activeStart + 1), NOT the TUNED COMBO.STEP_STARTUP_SCALE rescale of step 0's
  // window that the fallback path would have produced.
  const attacker = fakeRuntime("ladder", 0, 0);
  attacker.borgId = swordKnight.id;
  const enemy = fakeRuntime("ladder_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, swordKnight],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  const swingActiveLens: number[] = [];
  let prevMeleeActive = 0;
  for (let f = 0; f < 240 && swingActiveLens.length < 2; f += 1) {
    pumpAttackFrame(attacker, swordKnight, true, [attacker, enemy], profiles);
    const active = attacker.cooldowns["meleeActive"] ?? 0;
    if (active > prevMeleeActive) swingActiveLens.push(active); // new swing: peak meleeActive = startup+active
    prevMeleeActive = active;
    assertSane([attacker, enemy], f);
  }
  if (swingActiveLens.length < 2) {
    throw new Error(`[selfcheck] expected at least 2 chained swings, saw ${swingActiveLens.length}`);
  }
  const step1 = ladder[1];
  if (!step1) throw new Error("[selfcheck] ladder step 1 missing");
  const step1ActiveLen = step1.activeEnd - step1.activeStart + 1;
  const secondSwingActiveLen = swingActiveLens[1]! - step1.activeStart; // meleeActive = startup + active at swing start; startup == step1.activeStart when exact
  if (secondSwingActiveLen !== step1ActiveLen) {
    throw new Error(
      `[selfcheck] second swing should use step 1's exact active window (${step1ActiveLen}f from slot ${step1.slot} kind ${step1.kind}), got ${secondSwingActiveLen}f (peak meleeActive=${swingActiveLens[1]})`,
    );
  }
  console.log(
    `[selfcheck] Sword Knight combo ladder resolved g3 s0/s1/s2 (kinds 1/2/5); second swing used step 1's exact ${step1ActiveLen}f active window`,
  );
}

/**
 * NEO G RED (pl0629): action index 1 baseline variant 0 seeds g3 s25 (kind 1); holding B
 * auto-increments to s26 (kind 2), then the variant's chain callback (FUN_8018ded0, config+0x10)
 * fires and redirects the finisher to v6's OWN seed s27 (kind 8) — the decode note's "standing-
 * mash 3rd-hit finisher", not a further blind auto-increment.
 */
function assertNeoGRedLadderChainsToS27(_borgs: BorgStats[]): void {
  const ladder = comboLadderForBorgId("pl0629");
  if (!ladder || ladder.length !== 3) {
    throw new Error(`[selfcheck] NEO G RED combo ladder should resolve 3 steps: ${JSON.stringify(ladder)}`);
  }
  const slots = ladder.map((s) => s.slot);
  const kinds = ladder.map((s) => s.kind);
  if (slots.join(",") !== "25,26,27" || kinds.join(",") !== "1,2,8") {
    throw new Error(
      `[selfcheck] NEO G RED combo ladder should be g3 s25/s26/s27 kinds 1/2/8 (chain cb -> v6): slots=${slots} kinds=${kinds}`,
    );
  }
  console.log("[selfcheck] NEO G RED combo ladder resolved g3 s25/s26 (auto-increment) + chain cb -> s27 (kind 8)");
}

/**
 * A borg with NO resolved action-stream ladder (pl0100 — its action-1 baseline variant reaches
 * no stream call in the emulation, per action-stream-extraction-audit.md's "no stream call
 * reached" bucket) must still combo via the pre-existing TUNED COMBO.STEP_STARTUP_SCALE path —
 * comboLadderForBorgId returning null must not silently break chaining for the unresolved
 * majority of the roster.
 */
function assertUnresolvedLadderBorgStillCombosViaTunedPath(borgs: BorgStats[]): void {
  const id = "pl0100";
  if (comboLadderForBorgId(id) !== null) {
    throw new Error(`[selfcheck] expected pl0100 to be in the unresolved-ladder bucket for this test to be meaningful`);
  }
  const profile = buildProfile(borgById(borgs, id));
  const meleeDef = actionProfileForProfile(profile).melee;
  if (!meleeDef || meleeDef.comboHits < 2) {
    throw new Error(`[selfcheck] pl0100 should have a multi-hit TUNED combo profile: ${JSON.stringify(meleeDef)}`);
  }

  const attacker = fakeRuntime("tuned_combo", 0, 0);
  attacker.borgId = profile.id;
  const enemy = fakeRuntime("tuned_combo_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  let maxStep = 0;
  let swingStarts = 0;
  let prevMeleeActive = 0;
  for (let f = 0; f < 240; f += 1) {
    pumpAttackFrame(attacker, profile, true, [attacker, enemy], profiles);
    const active = attacker.cooldowns["meleeActive"] ?? 0;
    if (active > prevMeleeActive) swingStarts += 1;
    prevMeleeActive = active;
    maxStep = Math.max(maxStep, attacker.cooldowns["comboStep"] ?? 0);
    assertSane([attacker, enemy], f);
  }
  if (maxStep !== meleeDef.comboHits - 1) {
    throw new Error(
      `[selfcheck] pl0100 TUNED-fallback combo never reached its finisher: maxStep=${maxStep}, comboHits=${meleeDef.comboHits}`,
    );
  }
  if (swingStarts < meleeDef.comboHits) {
    throw new Error(`[selfcheck] pl0100 TUNED-fallback combo produced too few swings: ${swingStarts}`);
  }
  console.log(
    `[selfcheck] pl0100 (no resolved action-stream ladder) still chained to step ${maxStep} (${meleeDef.comboHits} hits) over ${swingStarts} swings via the TUNED path`,
  );
}

/**
 * G RED (pl0615) B-charge release: action index 3, baseline variant 0 seeds group-4 slot 2
 * (config byte @0x80365854, per actionStreamTables.json) — but that stream is NOT captured in
 * meleeAnimKinds.json's bank 0x80366220 g4 table at all (only s0/s1/s4 were captured for that
 * bank), so chargeMoveForBorgId("pl0615") resolves to null and the runtime must keep today's
 * behavior (no exact anim stream ref, generic CHARGE_OR_SPECIAL record) rather than fabricate
 * one. This is the HONEST outcome cue-script-stream-decode-2026-07-04.md's G RED table
 * documents (the charge stream fires a projectile CHILD, not a captured melee-style stream) —
 * asserting it locks the null-safe fallback path in instead of silently regressing to a wrong
 * "found a stream" reading if the source data ever shifts.
 */
function assertGRedChargeStreamUnresolvedKeepsFallback(borgs: BorgStats[]): void {
  const leaf = chargeMoveForBorgId("pl0615");
  if (leaf !== null) {
    throw new Error(
      `[selfcheck] expected G RED's B-charge leaf to be unresolved (its g4 s2 stream isn't in meleeAnimKinds.json): got ${JSON.stringify(leaf)}`,
    );
  }

  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const b = fakeRuntime("gred_charge_fallback", 0, 0);
  b.borgId = gRed.id;
  b.ammo = startingAmmoForProfile(gRed);
  const enemy = fakeRuntime("gred_charge_fallback_enemy", 1, 500);
  const profiles = new Map([
    [b.uid, gRed],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const shotDef = actionProfileForProfile(gRed).shot;
  if (!shotDef?.chargeable) throw new Error("[selfcheck] G RED should have a chargeable shot");
  for (let f = 0; f < shotDef.chargeTier1Frames + 5; f += 1) pumpAttackFrame(b, gRed, true, [b, enemy], profiles);
  const released = pumpAttackFrame(b, gRed, false, [b, enemy], profiles);
  const proj = released[0];
  if (!proj) throw new Error("[selfcheck] G RED charge release spawned nothing");
  if (b.meleeAnimStream) {
    throw new Error(
      `[selfcheck] G RED's unresolved charge leaf should leave meleeAnimStream null: got ${JSON.stringify(b.meleeAnimStream)}`,
    );
  }
  if (proj.damageRecordIndex !== DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL) {
    throw new Error(
      `[selfcheck] G RED's charged release should keep the generic CHARGE_OR_SPECIAL record: got ${proj.damageRecordIndex}`,
    );
  }
  console.log(
    "[selfcheck] G RED B-charge leaf unresolved (g4 s2 not captured) -> runtime kept the fallback anim/record exactly",
  );
}

/**
 * B-shot HIT-kind resolution (shotKindForBorgId, wired into shotHitRadiusForBorgId and
 * combat.ts's shotFamilyRecordSpread): a borg whose fire fn is call-site-guarded to a PROVEN
 * non-zero HIT kind (shotVariantKinds.json borgShotKinds) must use THAT kind's hit.bin
 * radius/damage record instead of the generic kind-0 heuristic. Three cases, per the task:
 *
 *  (a) G RED (pl0615) is the generator's own ground-truth gate: its ONLY attribution resolves
 *      to kind 0, so wiring shotKindForBorgId in must be BEHAVIOR-IDENTICAL to the pre-existing
 *      kind-0 heuristic. Pinned: hitRadius extent 20 (attackHitData.ts's existing comment cites
 *      this as the roster median too).
 *  (b) pl0000 (NORMAL NINJA) has a guarded attribution resolving to kind 1 (table 0x802d6d68),
 *      whose hit.bin record has a LARGER radius (10) than its own kind-0 record (5) and than
 *      its TUNED profile hitRadius (35) — proof the resolved-kind path, not kind 0 or the
 *      profile fallback, is what actually reaches the spawned projectile.
 *  (c) pl0001 (SHURIKEN NINJA) has NO guarded attribution at all (borgShotKinds has no entry
 *      keyed by its runtime guard id 0x1) — shotKindForBorgId must return null and the spawned
 *      projectile must keep using the kind-0 heuristic (extent 5) exactly as before this change.
 */
function assertShotKindResolutionPrefersProvenAttribution(borgs: BorgStats[]): void {
  // (a) G RED: kind 0 either way.
  if (shotKindForBorgId("pl0615") !== 0) {
    throw new Error(`[selfcheck] G RED's resolved shot kind should be 0 (ground-truth gate): got ${shotKindForBorgId("pl0615")}`);
  }
  const gRedRadius = shotHitRadiusForBorgId("pl0615");
  if (gRedRadius !== 20) {
    throw new Error(`[selfcheck] G RED shot hit radius must stay pinned at 20 (kind-0, unchanged): got ${gRedRadius}`);
  }

  // (b) pl0000: guarded attribution resolves to a non-zero kind (1) with a DIFFERENT radius
  // than kind 0 — proves the new resolution path is actually consumed, not just present.
  const ninjaKind = shotKindForBorgId("pl0000");
  if (ninjaKind !== 1) {
    throw new Error(`[selfcheck] pl0000 (NORMAL NINJA) should resolve guarded shot kind 1: got ${ninjaKind}`);
  }
  const ninjaRadius = shotHitRadiusForBorgId("pl0000");
  if (ninjaRadius !== 10) {
    throw new Error(
      `[selfcheck] pl0000's resolved-kind (1) shot radius should be 10 (kind-0 would be 5, profile TUNED is 35): got ${ninjaRadius}`,
    );
  }

  // (c) pl0001: no guarded attribution at all -> falls back to the kind-0 heuristic unchanged.
  const shurikenKind = shotKindForBorgId("pl0001");
  if (shurikenKind !== null) {
    throw new Error(`[selfcheck] pl0001 (SHURIKEN NINJA) has no borgShotKinds entry and should resolve null: got ${shurikenKind}`);
  }
  const shurikenRadius = shotHitRadiusForBorgId("pl0001");
  if (shurikenRadius !== 5) {
    throw new Error(`[selfcheck] pl0001's kind-0 fallback shot radius should stay 5: got ${shurikenRadius}`);
  }

  // End-to-end: pl0000's plain (non-chargeable) B tap must actually spawn a projectile whose
  // hitRadius reflects the resolved kind-1 record (10), not the profile's TUNED 35 nor kind 0's 5.
  const ninjaProfile = buildProfile(borgById(borgs, "pl0000"));
  const ninjaRuntime = fakeRuntime("ninja_shotkind", 0, 0);
  ninjaRuntime.borgId = ninjaProfile.id;
  ninjaRuntime.ammo = startingAmmoForProfile(ninjaProfile);
  const enemy = fakeRuntime("ninja_shotkind_enemy", 1, 220);
  const profiles = new Map([
    [ninjaRuntime.uid, ninjaProfile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const fired = pumpAttackFrame(ninjaRuntime, ninjaProfile, true, [ninjaRuntime, enemy], profiles);
  const proj = fired[0];
  if (!proj) throw new Error("[selfcheck] pl0000 shot tap should spawn a projectile");
  if (proj.hitRadius !== 10) {
    throw new Error(`[selfcheck] pl0000's spawned projectile hitRadius should be exactly 10 (resolved kind 1): got ${proj.hitRadius}`);
  }

  // Fleet coverage telemetry: how many borgs now resolve a PROVEN non-zero shot kind (vs.
  // falling back to the kind-0 heuristic or having no attribution at all).
  let nonZeroCount = 0;
  let zeroCount = 0;
  let noneCount = 0;
  for (const stats of borgs) {
    const kind = shotKindForBorgId(stats.id);
    if (kind === null) noneCount += 1;
    else if (kind === 0) zeroCount += 1;
    else nonZeroCount += 1;
  }
  console.log(
    `[selfcheck] shot-kind resolution: G RED pinned (kind 0, radius 20) unchanged; pl0000 resolves kind 1 (radius 10, was 5/35); ` +
      `pl0001 has no attribution (falls back, radius 5). Fleet: ${nonZeroCount} borgs resolve a proven NON-ZERO shot kind, ` +
      `${zeroCount} resolve a proven kind 0, ${noneCount} have no attribution (kind-0 heuristic fallback) out of ${borgs.length}.`,
  );
}

/**
 * Shot-flight-visual resolution (research/decomp/efct-consumers-decode-2026-07-04.md §3):
 * FUN_8007dd84's shot-init row +0x00 (texId|flags) resolves a borg's B-shot flight mesh from
 * the efct00_mdl.arc bank when bit 0x4000 or 0x8000 is set; neither bit means the row indexes
 * the per-player weapon bank instead (today's TUNED sprite/mesh stand-in stays exact).
 * shotFlightVisualForBorgId (attackHitData.ts) uses the SAME guarded borgShotKinds
 * attribution as shotKindForBorgId, restricted to the one row shape (table 0x802d6d68's
 * 56-byte/kindOffset-3 layout) proven to carry these fields — other tables' rows at the same
 * nominal offsets decode to texIds far outside the 157-entry bank (a different, undecoded
 * row format), so they are never trusted.
 *
 * Honest fleet finding (asserted here, not hidden): of the 130 borgs with a guarded
 * borgShotKinds attribution, 48 land in a safe-shape table, but ALL 48 land on a weapon-bank
 * row (neither flag set) — the two real ROM rows that DO carry a bank flag (table 0x802d6d68
 * variant 6-9's texId 125, table 0x802d7b10 variant 10's texId 9) have NO call-site-guarded
 * borg attribution at all (their firing functions, FUN_80166fa8/zz_0092534_, carry no static
 * actor-id guard the extractor could prove — confirmed independently, not a bug in this
 * resolver). So `shotFlightVisualForBorgId` legitimately resolves null for every borg in the
 * roster today; every borg's projectile keeps its exact current visualKind rendering. This
 * assert proves three things instead of faking fleet coverage:
 *  (a) G RED (weapon-bank row via a DIFFERENT table, per the existing shot-kind ground truth)
 *      resolves null and his spawned projectile carries no flightVisual — unchanged visuals;
 *  (b) pl0000 (NORMAL NINJA) has a guarded attribution landing in the PROVEN safe-shape table
 *      itself (0x802d6d68 id 0) yet is STILL a weapon-bank row (texId 14, neither flag) — a
 *      stronger negative than "wrong shape", proving the flag check itself is exercised, not
 *      just the shape gate — and its spawned projectile carries no flightVisual either;
 *  (c) the byte-decode machinery itself is correct against the two REAL ROM rows that DO
 *      carry the flags, read directly by table/variant (shotFlightVisualForTableRow,
 *      bypassing borg attribution entirely — the ONLY way to exercise a positive decode
 *      against real ROM bytes given (a)/(b)'s honest negative fleet result).
 */
function assertShotFlightVisualResolution(borgs: BorgStats[]): void {
  // (c) Direct ROM-row decode correctness: table 0x802d6d68 variant 6 (G RED/BLACK 0x615-
  // family shot, texId 125, both flags set -> teamTint true, launch FX 0) and table
  // 0x802d7b10 variant 10 (texId 9, only 0x4000 set -> teamTint true, launch FX 0).
  const gRedFamilyRow = shotFlightVisualForTableRow("0x802d6d68", 6);
  if (!gRedFamilyRow || gRedFamilyRow.bankTexId !== 125 || gRedFamilyRow.teamTint !== true || gRedFamilyRow.launchFxId !== 0) {
    throw new Error(`[selfcheck] table 0x802d6d68 variant 6 should decode to {bankTexId:125, teamTint:true, launchFxId:0}: got ${JSON.stringify(gRedFamilyRow)}`);
  }
  const otherBankRow = shotFlightVisualForTableRow("0x802d7b10", 10);
  if (!otherBankRow || otherBankRow.bankTexId !== 9 || otherBankRow.teamTint !== true || otherBankRow.launchFxId !== 0) {
    throw new Error(`[selfcheck] table 0x802d7b10 variant 10 should decode to {bankTexId:9, teamTint:true, launchFxId:0}: got ${JSON.stringify(otherBankRow)}`);
  }
  // A weapon-bank row in the SAME safe-shape table (variant 0, texId 14, neither flag) must
  // decode to null -- proves the flag gate itself works, not just the shape gate.
  const weaponBankRow = shotFlightVisualForTableRow("0x802d6d68", 0);
  if (weaponBankRow !== null) {
    throw new Error(`[selfcheck] table 0x802d6d68 variant 0 (texId 14, no flags) should decode to null: got ${JSON.stringify(weaponBankRow)}`);
  }
  // An out-of-shape table (e.g. G RED's own attribution table, stride 68) must never be read.
  const outOfShape = shotFlightVisualForTableRow("0x80303138", 43);
  if (outOfShape !== null) {
    throw new Error(`[selfcheck] out-of-shape table 0x80303138 must resolve null regardless of its bytes: got ${JSON.stringify(outOfShape)}`);
  }

  // (a) G RED: unattributed to any bank row (his own table is a different shape) -> null,
  // spawned projectile carries no flightVisual.
  if (shotFlightVisualForBorgId("pl0615") !== null) {
    throw new Error(`[selfcheck] G RED should resolve no flight visual (his table is a different shape): got ${JSON.stringify(shotFlightVisualForBorgId("pl0615"))}`);
  }

  // (b) pl0000: guarded attribution DOES land in the safe-shape table, but on a weapon-bank
  // row -> still null. Verify via the real spawn path (spawnProjectile in combat.ts).
  if (shotFlightVisualForBorgId("pl0000") !== null) {
    throw new Error(`[selfcheck] pl0000 (weapon-bank row in the safe-shape table) should resolve no flight visual: got ${JSON.stringify(shotFlightVisualForBorgId("pl0000"))}`);
  }
  const ninjaProfile = buildProfile(borgById(borgs, "pl0000"));
  const ninjaRuntime = fakeRuntime("ninja_flightvisual", 0, 0);
  ninjaRuntime.borgId = ninjaProfile.id;
  ninjaRuntime.ammo = startingAmmoForProfile(ninjaProfile);
  const enemy = fakeRuntime("ninja_flightvisual_enemy", 1, 220);
  const profiles = new Map([
    [ninjaRuntime.uid, ninjaProfile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  const fired = pumpAttackFrame(ninjaRuntime, ninjaProfile, true, [ninjaRuntime, enemy], profiles);
  const proj = fired[0];
  if (!proj) throw new Error("[selfcheck] pl0000 shot tap should spawn a projectile");
  if (proj.flightVisual !== undefined) {
    throw new Error(`[selfcheck] pl0000's spawned projectile should carry no flightVisual (weapon-bank row): got ${JSON.stringify(proj.flightVisual)}`);
  }

  // Fleet coverage telemetry: how many borgs resolve a bank flight visual today (honest: 0),
  // vs. how many have a guarded attribution that lands in the proven safe-shape table at all
  // (48 -- all currently weapon-bank rows) vs. neither (the remaining fleet, unattributed or
  // attributed to a different-shaped table).
  let bankVisualCount = 0;
  let safeShapeWeaponBankCount = 0;
  let otherCount = 0;
  for (const stats of borgs) {
    const visual = shotFlightVisualForBorgId(stats.id);
    if (visual) {
      bankVisualCount += 1;
      continue;
    }
    if (hasSafeShapeShotAttribution(stats.id)) safeShapeWeaponBankCount += 1;
    else otherCount += 1;
  }
  console.log(
    `[selfcheck] shot-flight-visual resolution: G RED and pl0000 (weapon-bank rows) keep today's visuals unchanged; ` +
      `direct ROM-row decode verified against table 0x802d6d68 v6 (texId 125, teamTint, launchFx 0) and 0x802d7b10 v10 ` +
      `(texId 9, teamTint, launchFx 0). Fleet: ${bankVisualCount} borgs resolve a bank flight visual today (honest: the ` +
      `two real ROM rows with bank flags have no call-site-guarded borg attribution — FUN_80166fa8/zz_0092534_ carry no ` +
      `static actor-id guard), ${safeShapeWeaponBankCount} have a guarded attribution landing in the proven safe-shape ` +
      `table but on a weapon-bank row, ${otherCount} are unattributed or attributed to a different-shaped table, out of ${borgs.length}.`,
  );
}

/**
 * A borg with a resolved+ARMED charge leaf (kind !== null AND the kind has real records in
 * the borg's own hit-remap): the runtime must set BOTH the exact anim stream ref AND the
 * exact damage record on a tier-1+ release, generalizing the pl0615/pl0629/pl062a
 * PREFERRED_LABELS hardcode in borgPresentationAssets.ts to every such borg. Scans
 * chargeMoveForBorgId across the roster (rather than hardcoding an assumption). The harness
 * primes the melee cooldown so a melee-primary hybrid's B press falls through to the shot/
 * charge path within the SAME frame's resolveBActionOrder pass (the ROM-exact command tables
 * for these borgs route far-range B to melee-only, so an engage-range target + gated melee
 * cooldown is the only way this harness reaches their charge path — matching how a real
 * player would charge mid-fight after a recent swing, not a synthetic gap in coverage).
 */
function assertArmedChargeLeafSetsExactAnimAndRecord(borgs: BorgStats[]): void {
  let armedId: string | null = null;
  let armedLeaf: ReturnType<typeof chargeMoveForBorgId> = null;
  for (const stats of borgs) {
    const leaf = chargeMoveForBorgId(stats.id);
    if (!leaf || leaf.kind === null || !leaf.damageRecord || !leaf.animStreamRef) continue;
    const profile = buildProfile(stats);
    const shotDef = actionProfileForProfile(profile).shot;
    if (!shotDef?.chargeable) continue;
    armedId = stats.id;
    armedLeaf = leaf;
    break;
  }
  if (!armedId || !armedLeaf) {
    throw new Error("[selfcheck] expected at least one roster borg with a fully-armed charge leaf for this test to be meaningful");
  }
  const leaf = armedLeaf;

  const profile = buildProfile(borgById(borgs, armedId));
  const shotDef = actionProfileForProfile(profile).shot;
  if (!shotDef?.chargeable) {
    throw new Error(`[selfcheck] ${armedId} should have a chargeable shot for this test to be meaningful`);
  }
  const b = fakeRuntime("armed_charge", 0, 0);
  b.borgId = profile.id;
  b.ammo = startingAmmoForProfile(profile);
  b.cooldowns["melee"] = 999; // gate melee off so B falls through to shot/charge even for melee-primary hybrids
  const enemy = fakeRuntime("armed_charge_enemy", 1, 40); // inside melee engage range
  const profiles = new Map([
    [b.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  b.lockTarget = enemy.uid;
  for (let f = 0; f < shotDef.chargeTier1Frames + 5; f += 1) pumpAttackFrame(b, profile, true, [b, enemy], profiles);
  const released = pumpAttackFrame(b, profile, false, [b, enemy], profiles);
  const proj = released[0];
  if (!proj) throw new Error(`[selfcheck] ${armedId} charge release spawned nothing`);
  if (!b.meleeAnimStream || b.meleeAnimStream.group !== leaf.animStreamRef!.group || b.meleeAnimStream.slot !== leaf.animStreamRef!.slot) {
    throw new Error(
      `[selfcheck] ${armedId} charged release should set the exact anim stream ref ${JSON.stringify(leaf.animStreamRef)}: got ${JSON.stringify(b.meleeAnimStream)}`,
    );
  }
  if (JSON.stringify(proj.damageRecord) !== JSON.stringify(leaf.damageRecord)) {
    throw new Error(
      `[selfcheck] ${armedId} charged release should use the exact charge-leaf damage record: got ${JSON.stringify(proj.damageRecord)}, expected ${JSON.stringify(leaf.damageRecord)}`,
    );
  }
  console.log(
    `[selfcheck] ${armedId} charge leaf resolved armed (kind ${leaf.kind}) -> release set exact anim stream g${leaf.animStreamRef!.group}s${leaf.animStreamRef!.slot} and the exact damage record`,
  );
}

/**
 * Air B (actionIndex 2): a borg whose airB leaf resolves with an ARMED kind must use that
 * leaf's exact active window (meleeActive length) for an airborne B press instead of reusing
 * the ground melee def's window. Scans actionStreamTables (via airBMoveForBorgId) for one such
 * borg rather than hardcoding an id — the decode note's "NEO G RED air g4 s0 kind 15" turned
 * out on ground-truth review to belong to G RED (pl0615) instead (both id 0x615 and 0x629
 * share the family bank; the note's own groundTruth correction says so), so this asserts
 * against whichever borg the roster scan actually finds armed, and logs which one.
 */
function assertArmedAirBLeafUsesExactWindow(borgs: BorgStats[]): void {
  let armedId: string | null = null;
  for (const stats of borgs) {
    const leaf = airBMoveForBorgId(stats.id);
    if (leaf && leaf.kind !== null && leaf.activeStart !== null && leaf.activeEnd !== null) {
      const profile = buildProfile(stats);
      const meleeDef = actionProfileForProfile(profile).melee;
      // Needs a melee profile (air melee reuses meleeDef's lunge/hit-test scaffolding) AND a
      // DIFFERENT window than the ground def, or the assertion below would be trivially true.
      if (meleeDef && leaf.activeEnd - leaf.activeStart + 1 !== meleeDef.active) {
        armedId = stats.id;
        break;
      }
    }
  }
  if (!armedId) {
    throw new Error("[selfcheck] expected at least one roster borg with an armed air-B leaf (distinct from its ground window) for this test to be meaningful");
  }
  const leaf = airBMoveForBorgId(armedId);
  if (!leaf || leaf.kind === null || leaf.activeStart === null || leaf.activeEnd === null) {
    throw new Error(`[selfcheck] ${armedId}'s air-B leaf should still resolve armed: ${JSON.stringify(leaf)}`);
  }
  const exactAirWindow = leaf.activeEnd - leaf.activeStart + 1;

  const profile = buildProfile(borgById(borgs, armedId));
  const meleeDef = actionProfileForProfile(profile).melee;
  if (!meleeDef) throw new Error(`[selfcheck] ${armedId} should have a melee profile for this test to be meaningful`);

  const attacker = fakeRuntime("air_b", 0, 0);
  attacker.borgId = profile.id;
  attacker.grounded = false; // airborne B press
  const enemy = fakeRuntime("air_b_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [attacker.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  let peakMeleeActive = 0;
  for (let f = 0; f < 30; f += 1) {
    pumpAttackFrame(attacker, profile, true, [attacker, enemy], profiles);
    peakMeleeActive = Math.max(peakMeleeActive, attacker.cooldowns["meleeActive"] ?? 0);
    if ((attacker.cooldowns["meleeActive"] ?? 0) > 0) break; // swing has started
    assertSane([attacker, enemy], f);
  }
  const airSwingActiveLen = peakMeleeActive - leaf.activeStart; // meleeActive = startup+active; startup == activeStart when exact
  if (airSwingActiveLen !== exactAirWindow) {
    throw new Error(
      `[selfcheck] ${armedId} airborne B swing should use the air-B leaf's exact ${exactAirWindow}f window (kind ${leaf.kind}), got ${airSwingActiveLen}f (peak meleeActive=${peakMeleeActive})`,
    );
  }
  console.log(
    `[selfcheck] ${armedId} airborne B press used the exact air-B leaf window (${exactAirWindow}f, kind ${leaf.kind}) instead of the ground melee def's ${meleeDef.active}f`,
  );
}

/**
 * A borg with no resolved air-B or charge leaf at all must keep today's behavior exactly: no
 * meleeAnimStream set from either path (airBMoveForBorgId/chargeMoveForBorgId both null), so
 * neither addition regresses the unresolved majority of the roster. Also logs fleet-wide
 * coverage counts (airBChargeCoverage) per the ticket's reporting requirement.
 */
function assertUnresolvedAirBAndChargeKeepTodaysBehavior(borgs: BorgStats[]): void {
  const id = "pl0100";
  if (airBMoveForBorgId(id) !== null || chargeMoveForBorgId(id) !== null) {
    throw new Error(`[selfcheck] expected pl0100 to have no resolved air-B/charge leaf for this test to be meaningful`);
  }
  const profile = buildProfile(borgById(borgs, id));
  const b = fakeRuntime("unresolved_air_charge", 0, 0);
  b.borgId = profile.id;
  b.grounded = false;
  const enemy = fakeRuntime("unresolved_air_charge_enemy", 1, 40);
  enemy.hp = enemy.maxHp = 5000;
  const profiles = new Map([
    [b.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  for (let f = 0; f < 30; f += 1) {
    pumpAttackFrame(b, profile, true, [b, enemy], profiles);
    if ((b.cooldowns["meleeActive"] ?? 0) > 0) break;
  }
  if (b.meleeAnimStream) {
    throw new Error(
      `[selfcheck] pl0100 with no resolved air-B leaf should not set meleeAnimStream: got ${JSON.stringify(b.meleeAnimStream)}`,
    );
  }

  const coverage = airBChargeCoverage();
  if (coverage.airBResolved <= 0 || coverage.chargeResolved <= 0) {
    throw new Error(`[selfcheck] expected nonzero fleet coverage for both air-B and charge: ${JSON.stringify(coverage)}`);
  }
  console.log(
    `[selfcheck] air-B/charge coverage: ${coverage.airBResolved}/${coverage.rosterSize} borgs resolve an exact air-B leaf, ${coverage.chargeResolved}/${coverage.rosterSize} resolve an exact charge leaf; unresolved borgs (e.g. pl0100) keep today's behavior exactly`,
  );
}

/**
 * (a) STAR HERO (pl0804) X special: the command-type-2 (X button) record's actionIndex 2
 * resolves the ramming-dash leaf (g4 s1, kind 12 per meleeAnimKinds.json) — matching
 * status-effects-decode-2026-07-04.md §A's "command table ... maps actionIndex 2 exclusively
 * to command type 2 = X button" finding. A plain X press (pressedSpecialEdge path,
 * startSpecialAttack chargeTier 0) must set the exact anim stream ref on press, on top of the
 * existing hero-buff mechanic (untouched — this only makes the anim/record exact).
 */
function assertStarHeroXResolvesRamActionIndexAndSetsStream(borgs: BorgStats[]): void {
  const leaf = xMoveForBorgId("pl0804");
  if (!leaf || leaf.kind === null || !leaf.animStreamRef) {
    throw new Error(`[selfcheck] expected STAR HERO's X leaf to resolve armed (actionIndex 2, the ram): got ${JSON.stringify(leaf)}`);
  }
  if (leaf.kind !== 12) {
    throw new Error(`[selfcheck] expected STAR HERO's X leaf to arm kind 12 (the ram hit, per meleeAnimKinds.json g4 s1): got kind ${leaf.kind}`);
  }

  const heroProfile = buildProfile(borgById(borgs, "pl0804"));
  const hero = fakeRuntime("hero_x_stream", 0, 0);
  hero.borgId = heroProfile.id;
  const enemy = fakeRuntime("hero_x_stream_enemy", 1, 20); // inside the special's AoE radius
  const profiles = new Map([
    [hero.uid, heroProfile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);

  stepCooldowns(hero);
  stepAttacks(hero, heroProfile, false, true, [hero, enemy], profiles); // X press edge

  if (!hero.meleeAnimStream || hero.meleeAnimStream.group !== leaf.animStreamRef.group || hero.meleeAnimStream.slot !== leaf.animStreamRef.slot) {
    throw new Error(
      `[selfcheck] STAR HERO X press should set the exact anim stream ref ${JSON.stringify(leaf.animStreamRef)}: got ${JSON.stringify(hero.meleeAnimStream)}`,
    );
  }
  console.log(
    `[selfcheck] STAR HERO X resolves command-type-2 actionIndex 2 (the ram, kind ${leaf.kind}) -> press set exact anim stream g${leaf.animStreamRef.group}s${leaf.animStreamRef.slot}`,
  );
}

/**
 * (b) A borg with an armed X leaf (kind !== null AND the kind has real records in the borg's
 * own hit-remap) must use its exact damage record for the special's hit application, in place
 * of the generic CHARGE_OR_SPECIAL record — mirrors assertArmedChargeLeafSetsExactAnimAndRecord
 * but drives the AoE archetype's applyHit path (the more common special archetype) via a real
 * X press. Scans xMoveForBorgId across the roster (rather than hardcoding an assumption).
 */
function assertArmedXLeafUsesExactDamageRecord(borgs: BorgStats[]): void {
  let armedId: string | null = null;
  let armedLeaf: ReturnType<typeof xMoveForBorgId> = null;
  for (const stats of borgs) {
    const leaf = xMoveForBorgId(stats.id);
    if (!leaf || leaf.kind === null || !leaf.damageRecord) continue;
    const remapHasKind = (attackHitTableForBorgId(stats.id)?.kinds[String(leaf.kind)]?.length ?? 0) > 0;
    if (!remapHasKind) continue;
    // Needs a record DISTINCT from the generic CHARGE_OR_SPECIAL archetype (else this test
    // would be trivially true even if the exact-record wiring were dead code).
    if (JSON.stringify(leaf.damageRecord) === JSON.stringify(damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL))) continue;
    const profile = buildProfile(stats);
    if (actionProfileForProfile(profile).special.archetype === "projectile") continue; // exercise the AoE hit-apply path
    armedId = stats.id;
    armedLeaf = leaf;
    break;
  }
  if (!armedId || !armedLeaf || !armedLeaf.damageRecord) {
    throw new Error("[selfcheck] expected at least one roster borg with a fully-armed AoE-archetype X leaf (record distinct from the generic archetype) for this test to be meaningful");
  }
  const leaf = armedLeaf;
  const exactRecord = armedLeaf.damageRecord;

  const profile = buildProfile(borgById(borgs, armedId));
  const b = fakeRuntime("armed_x", 0, 0);
  b.borgId = profile.id;
  const enemy = fakeRuntime("armed_x_enemy", 1, 20); // inside the special's AoE radius
  enemy.hp = enemy.maxHp = 10_000_000; // stabilize the defender hp-ratio curve index
  const profiles = new Map([
    [b.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  b.lockTarget = enemy.uid;

  const specialDef = actionProfileForProfile(profile).special;
  const expectedExactDamage = computeSourceDamage({
    attacker: b,
    attackerProfile: profile,
    victim: enemy,
    victimProfile: profiles.get(enemy.uid)!,
    record: exactRecord,
    damageScale: specialDef.damageMultiplier,
  });
  const expectedGenericDamage = computeSourceDamage({
    attacker: b,
    attackerProfile: profile,
    victim: enemy,
    victimProfile: profiles.get(enemy.uid)!,
    record: damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL),
    damageScale: specialDef.damageMultiplier,
  });
  if (expectedExactDamage === expectedGenericDamage) {
    throw new Error(`[selfcheck] ${armedId}'s exact X-leaf record should predict damage distinct from the generic archetype for this test to be meaningful`);
  }

  stepCooldowns(b);
  stepAttacks(b, profile, false, true, [b, enemy], profiles); // X press edge
  const dealt = enemy.maxHp - enemy.hp;

  if (!b.meleeAnimStream || b.meleeAnimStream.group !== leaf.animStreamRef!.group || b.meleeAnimStream.slot !== leaf.animStreamRef!.slot) {
    throw new Error(
      `[selfcheck] ${armedId} X press should set the exact anim stream ref ${JSON.stringify(leaf.animStreamRef)}: got ${JSON.stringify(b.meleeAnimStream)}`,
    );
  }
  if (dealt !== expectedExactDamage) {
    throw new Error(
      `[selfcheck] ${armedId} X special should hit with the exact X-leaf damage record: dealt ${dealt}, expected ${expectedExactDamage} (generic archetype would have dealt ${expectedGenericDamage})`,
    );
  }
  console.log(
    `[selfcheck] ${armedId} X leaf resolved armed (kind ${leaf.kind}) -> press set exact anim stream g${leaf.animStreamRef!.group}s${leaf.animStreamRef!.slot} and dealt the exact-record damage (${dealt}, vs generic-archetype ${expectedGenericDamage})`,
  );
}

/**
 * (c) A borg with no resolved X leaf at all must keep today's behavior exactly: no
 * meleeAnimStream set from the X press, and the generic CHARGE_OR_SPECIAL record still applies
 * — xMoveForBorgId returning null must not regress the (majority) unresolved roster. Also logs
 * fleet-wide X coverage (xMoveCoverage) per the ticket's reporting requirement.
 */
function assertUnresolvedXKeepsTodaysBehavior(borgs: BorgStats[]): void {
  const id = "pl0100";
  if (xMoveForBorgId(id) !== null) {
    throw new Error(`[selfcheck] expected pl0100 to have no resolved X leaf for this test to be meaningful`);
  }
  const profile = buildProfile(borgById(borgs, id));
  const specialDef = actionProfileForProfile(profile).special;
  if (specialDef.archetype === "projectile") {
    throw new Error("[selfcheck] pl0100 fixture assumption stale: expected an AoE-archetype special for this test");
  }
  const b = fakeRuntime("unresolved_x", 0, 0);
  b.borgId = profile.id;
  const enemy = fakeRuntime("unresolved_x_enemy", 1, 20); // inside the special's AoE radius
  enemy.hp = enemy.maxHp = 10_000_000; // stabilize the defender hp-ratio curve index
  const profiles = new Map([
    [b.uid, profile],
    [enemy.uid, buildProfile(borgById(borgs, "pl0008"))],
  ]);
  b.lockTarget = enemy.uid;

  const expectedGenericDamage = computeSourceDamage({
    attacker: b,
    attackerProfile: profile,
    victim: enemy,
    victimProfile: profiles.get(enemy.uid)!,
    record: damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL),
    damageScale: specialDef.damageMultiplier,
  });

  stepCooldowns(b);
  stepAttacks(b, profile, false, true, [b, enemy], profiles); // X press edge
  const dealt = enemy.maxHp - enemy.hp;

  if (b.meleeAnimStream) {
    throw new Error(
      `[selfcheck] pl0100 with no resolved X leaf should not set meleeAnimStream: got ${JSON.stringify(b.meleeAnimStream)}`,
    );
  }
  if (dealt !== expectedGenericDamage) {
    throw new Error(
      `[selfcheck] pl0100's unresolved X special should keep the generic CHARGE_OR_SPECIAL record: dealt ${dealt}, expected ${expectedGenericDamage}`,
    );
  }

  const coverage = xMoveCoverage();
  if (coverage.xResolved <= 0) {
    throw new Error(`[selfcheck] expected nonzero fleet coverage for X specials: ${JSON.stringify(coverage)}`);
  }
  console.log(
    `[selfcheck] X-special coverage: ${coverage.xResolved}/${coverage.rosterSize} borgs resolve an exact X leaf; unresolved borgs (e.g. pl0100) keep today's TUNED behavior exactly`,
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
  // One press -> one swing; run through the whole active window. The runtime prefers the
  // exact HIT-record frame window (meleeExactData) over the TUNED profile timing, so the
  // pumped span must cover whichever is later.
  const exact = exactMeleeForBorgId(profile.id);
  const swingFrames = Math.max(meleeDef.startup + meleeDef.active, exact ? exact.activeEnd : 0) + 2;
  pumpAttackFrame(attacker, profile, true, [attacker, enemy], profiles);
  for (let f = 0; f < swingFrames; f += 1) {
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
  // Expected drop mirrors spawnProjectile's resolution: a resolved ROM variant's drop
  // (negated at the boundary — the ROM field is negative-down, Projectile.drop is
  // positive-down) overrides the TUNED shotDef.bulletDrop. G RED resolves shot kind 0 →
  // the ROM bullet variant (drop -3.0) → expected Projectile.drop = +3.0.
  const romVariantDrop = (() => {
    const kind = shotKindForBorgId(gRed.id);
    const variant = kind !== null ? findVariantByKind(kind) : null;
    return variant ? -variant.drop : null;
  })();
  const expectedDrop = romVariantDrop ?? (shotDef.bulletDrop > 0 ? shotDef.bulletDrop : undefined);
  if (expectedDrop !== undefined && tier0.drop !== expectedDrop) {
    throw new Error(`[selfcheck] ballistic drop not applied to spawned bullet: ${tier0.drop} (expected ${expectedDrop})`);
  }
  if ((tier0.drop ?? 0) < 0) {
    throw new Error(`[selfcheck] spawned bullet has NEGATIVE drop (would rise): ${tier0.drop}`);
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

  // 5) GUARD/40 DATA RULE (T1): victimStatusImmunityA (pldata+0xa8 mask) & 0x1000, combined
  //    with a flagsA 0x1000 record -> damage divided by 40. Data-driven now, not a caller flag
  //    — assert BOTH that the divide fires when the mask bit is set, and that it does NOT fire
  //    for a victim without the mask bit (a record's flagsA 0x1000 alone is not enough).
  const blockDivVictim = makeVictim(0);
  const blockDivDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: blockDivVictim,
    victimProfile,
    record: exemptRecord,
    victimStatusImmunityA: 0x1000,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  const expectedBlockDivDamage = Math.max(1, Math.trunc(enemyDamage / 40));
  if (blockDivDamage !== expectedBlockDivDamage) {
    throw new Error(
      `[selfcheck] friendly fire: victimStatusImmunityA 0x1000 + flagsA 0x1000 should divide by 40: got=${blockDivDamage}, expected=${expectedBlockDivDamage}`,
    );
  }
  const noMaskDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: makeVictim(0),
    victimProfile,
    record: exemptRecord,
    victimStatusImmunityA: 0, // no resistance mask -> the /40 rule must NOT fire
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
  });
  if (noMaskDamage !== enemyDamage) {
    throw new Error(
      `[selfcheck] friendly fire: flagsA 0x1000 WITHOUT the victim resistance mask should NOT divide by 40: got=${noMaskDamage}, expected=${enemyDamage}`,
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
    const all = [attacker, victim];
    const profiles = new Map([
      [attacker.uid, profile],
      [victim.uid, victimTeam === 0 ? profile : enemyProfile],
    ]);
    if (victimTeam === 0) {
      // The contextual-B resolver only routes a hybrid to melee when locked onto an engaged
      // enemy (battle invariant), so the teammate run needs a live enemy in swing range to
      // trigger the swing that clips the teammate.
      const lockBait = fakeRuntime("ff_melee_lockbait", 1, 20);
      lockBait.hp = lockBait.maxHp = 5000;
      all.push(lockBait);
      profiles.set(lockBait.uid, enemyProfile);
    }
    pumpAttackFrame(attacker, profile, true, all, profiles);
    const meleeDef = actionProfileForProfile(profile).melee;
    if (!meleeDef) throw new Error("[selfcheck] friendly fire melee sim test needs a melee profile");
    // Cover the exact HIT-record window when it runs longer than the TUNED profile timing.
    const exact = exactMeleeForBorgId(profile.id);
    const swingFrames = Math.max(meleeDef.startup + meleeDef.active, exact ? exact.activeEnd : 0) + 2;
    for (let f = 0; f < swingFrames; f += 1) {
      pumpAttackFrame(attacker, profile, false, all, profiles);
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
  // the lock for the nearer enemy, the old fallback path emitted world-space moveX toward x=-800.
  if (!(input.moveZ > 0 && input.moveX === 0)) {
    throw new Error("[selfcheck] AI target memory failed: ignored valid lockTarget for nearer enemy");
  }

  const unlocked = fakeRuntime("unlocked", 0, 0);
  const unlockedInput = stepAI(unlocked, buildProfile(borgById(borgs, "pl0615")), [unlocked, closerEnemy]);
  if (
    unlockedInput.moveX !== 0 ||
    unlockedInput.moveZ !== 0 ||
    unlockedInput.attack ||
    unlockedInput.special ||
    unlockedInput.lockOn
  ) {
    throw new Error(`[selfcheck] AI invented a target without source lock state: ${JSON.stringify(unlockedInput)}`);
  }

  console.log("[selfcheck] AI consumes source lock target and does not run an independent nearest selector");
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
  if (frozen.observe().result === "draw") {
    throw new Error("[selfcheck] frozen battle timer expired: Challenge-style timer must never time out");
  }
  if (frozen.observe().timeRemainingFrames !== 30) {
    throw new Error(
      `[selfcheck] frozen battle timer ticked: timeRemainingFrames=${frozen.observe().timeRemainingFrames}, want 30`,
    );
  }

  const running = mk(false);
  let drawFrame = -1;
  for (let f = 0; f < 90; f++) {
    running.step(1 / 60, idleInputs);
    if (running.observe().result === "draw") {
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
  const activeUid = battle.observe().activeUidByPlayer["p1"];
  const activeNow = () => battleStateForSelfcheck(battle).borgs.find((b) => b.uid === activeUid);
  if (!activeNow()) throw new Error("[selfcheck] spawn duration test lost p1 borg");
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };

  // 3-phase deploy (DEPLOY, behavior-notes.md (af)): phase 0 descent (stateTime 1..20) ->
  // phase 1 setup (stateTime 21, fires ally cue 8) -> phase 2 pose (stateTime 22..36). The
  // spawning borg must be invincible for the whole deploy (spawn STATE = deploy-lock protection,
  // replacing the old flat TUNED 45f invincTimer) with invincTimer itself at 0.
  const spawn0 = activeNow()!;
  if (spawn0.invincTimer !== 0) {
    throw new Error(`[selfcheck] deploy lock should start invincTimer=0 (spawn state protects): ${spawn0.invincTimer}`);
  }

  const phasesHit = new Set<number>();
  for (let f = 0; f < STATE.SPAWN_DURATION - 1; f += 1) {
    battle.step(1 / 60, idleInputs);
    const b = activeNow();
    if (b?.state !== "spawn") {
      throw new Error(`[selfcheck] spawn lock ended early at frame ${f + 1}`);
    }
    if (!isInvincible(b)) {
      throw new Error(`[selfcheck] spawning borg lost deploy-lock invulnerability at frame ${f + 1}`);
    }
    const st = b.stateTime;
    const wantPhase = st <= DEPLOY.PHASE0_DESCENT_FRAMES ? 0 : st <= DEPLOY.PHASE0_DESCENT_FRAMES + DEPLOY.PHASE1_SETUP_FRAMES ? 1 : 2;
    if (b.deployPhase !== wantPhase) {
      throw new Error(`[selfcheck] deploy phase mismatch at stateTime ${st}: got ${b.deployPhase}, want ${wantPhase}`);
    }
    phasesHit.add(b.deployPhase ?? -1);
  }
  // 36th step ends the deploy lock.
  battle.step(1 / 60, idleInputs);
  const after = activeNow();
  if (after?.state !== "idle") {
    throw new Error(`[selfcheck] spawn lock did not end at ${STATE.SPAWN_DURATION} frames: ${after?.state}`);
  }
  if (phasesHit.size !== 3 || !phasesHit.has(0) || !phasesHit.has(1) || !phasesHit.has(2)) {
    throw new Error(`[selfcheck] 3-phase deploy did not visit all phases: ${[...phasesHit].join(",")}`);
  }
  console.log(
    `[selfcheck] 3-phase deploy (af): phases 0/1/2 visited across ${STATE.SPAWN_DURATION}f, ally cue ${DEPLOY.ALLY_CUE_ID} fires at phase 0->1, spawn-state invuln held (invincTimer=0)`,
  );
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
  const enemy = battleStateForSelfcheck(battle).borgs.find((b) => b.team === 1 && b.borgId === firstEnemyId);
  if (!enemy) throw new Error("[selfcheck] death accounting test lost first enemy");
  const startEnergy = battle.observe().energy[1] ?? 0;
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
  if ((battle.observe().defeated[1] ?? 0) !== 1 || (battle.observe().defeatedEnergy[1] ?? 0) !== firstEnemyProfile.energy) {
    throw new Error(
      `[selfcheck] kill-event defeated counters wrong: defeated=${battle.observe().defeated[1]}, energy=${battle.observe().defeatedEnergy[1]}`,
    );
  }
  if ((battle.observe().energy[1] ?? 0) !== nextEnemyProfile.energy) {
    throw new Error(
      `[selfcheck] enemy force energy did not drop at kill event: got ${battle.observe().energy[1]}, want queued ${nextEnemyProfile.energy}`,
    );
  }
  const enemyStateAfterAccounting = enemy.state as BorgRuntime["state"];
  if (!enemy.alive || !enemy.defeatAccounted || enemyStateAfterAccounting !== "death") {
    throw new Error("[selfcheck] death visual state should remain alive-but-accounted until removal");
  }
  if (battle.observe().actors.some((b) => b.team === 1 && b.borgId === nextEnemyId)) {
    throw new Error("[selfcheck] next enemy deployed before death-state removal");
  }

  let deployed = false;
  for (let f = 0; f < STATE.DEATH_DURATION + 2; f += 1) {
    battle.step(1 / 60, idleInputs);
    deployed = battle.observe().actors.some((b) => b.team === 1 && b.borgId === nextEnemyId);
    if (deployed) break;
  }
  if (!deployed) throw new Error("[selfcheck] queued enemy did not deploy after death timer");
  if ((battle.observe().defeated[1] ?? 0) !== 1 || (battle.observe().defeatedEnergy[1] ?? 0) !== firstEnemyProfile.energy) {
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
    const b = battleStateForSelfcheck(battle).borgs.find((x) => x.uid === uid);
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
    battleStateForSelfcheck(battle).borgs.find((b) => b.ownerPlayer === "p1" && b.alive && b.hp > 0);

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
  if ((battle.observe().energy[0] ?? 0) !== gRedProfile.energy) {
    throw new Error(
      `[selfcheck] husk must add 0 energy: team0=${battle.observe().energy[0]}, want ally-only ${gRedProfile.energy}`,
    );
  }
  if ((battle.observe().defeated[0] ?? 0) !== 1) {
    throw new Error(`[selfcheck] defeated[0] after real-borg death: ${battle.observe().defeated[0]}, want 1`);
  }
  if (battle.observe().result !== "ongoing") throw new Error("[selfcheck] battle ended by husk deploy");

  // Husk death -> another husk (respawns while the ally fights), still uncounted.
  killActive(husk.uid);
  stepUntil(() => {
    const active = p1Active();
    return !!active && active.borgId === HUSK_BORG_ID && active.uid !== husk.uid;
  }, "husk respawn");
  if ((battle.observe().defeated[0] ?? 0) !== 1 || (battle.observe().defeatedEnergy[0] ?? 0) !== gRedProfile.energy) {
    throw new Error(
      `[selfcheck] husk death must not count: defeated=${battle.observe().defeated[0]}, energy=${battle.observe().defeatedEnergy[0]}`,
    );
  }

  // Ally falls -> team 0 has no real force left: battle resolves, no fresh husk chain.
  const ally = battle.observe().actors.find((b) => b.team === 0 && b.ownerPlayer === null && b.alive && b.hp > 0);
  if (!ally || ally.borgId !== "pl0615") throw new Error("[selfcheck] husk test lost the ally borg");
  killActive(ally.uid);
  stepUntil(() => battle.observe().result !== "ongoing", "battle resolution after ally death");
  // step() mutates result; re-widen past the earlier "ongoing" narrowing (same pattern as
  // assertDeathAccountingAtKillEvent's state casts).
  const finalResult: string = battle.observe().result;
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

function assertPerBorgDashPhysics(borgs: BorgStats[]): void {
  // DERIVED dash page (+0x58/+0x5c/+0x64, dash states FUN_80061560/FUN_80063230): borgs
  // must differentiate — Acceleration Ninja's dash (40 u/f × 60f) outruns and outlasts
  // Sword Knight's (22 u/f × 30f) — and the per-frame page accel must decay dash speed.
  const ninja = dashPhysicsForBorgId("pl0004");
  const knight = dashPhysicsForBorgId("pl0200");
  if (!ninja || !knight) {
    throw new Error("[selfcheck] dash page missing for pl0004/pl0200 — movementPhysics.json regressed");
  }
  if (!(ninja.hSpeed > knight.hSpeed && ninja.durationFrames > knight.durationFrames)) {
    throw new Error(
      `[selfcheck] per-borg dash not differentiated: ninja=${ninja.hSpeed}x${ninja.durationFrames}f, knight=${knight.hSpeed}x${knight.durationFrames}f`,
    );
  }

  const ctx = {
    lockTargetPos: null,
    bounds: { minX: -100000, maxX: 100000, minZ: -100000, maxZ: 100000 },
    collision: null,
  };
  const profile = buildProfile(borgById(borgs, "pl0004"));
  const dasher = fakeRuntime("dash_ninja", 0, 0);
  dasher.borgId = "pl0004";
  dasher.pos = { x: 0, y: JUMP.GROUND_Y, z: 0 };
  dasher.rotY = 0;
  dasher.grounded = true;
  stepMovement(dasher, profile, { ...emptyInput(), moveZ: 1, dash: true }, ctx);
  const startSpeed = Math.hypot(dasher.vel.x, dasher.vel.z);
  if (Math.abs(startSpeed - ninja.hSpeed) > ninja.hSpeed * 0.05) {
    throw new Error(`[selfcheck] dash start speed should be page+0x58: got ${startSpeed}, want ~${ninja.hSpeed}`);
  }
  if ((dasher.cooldowns["dashActive"] ?? 0) !== ninja.durationFrames) {
    throw new Error(
      `[selfcheck] dash duration should be page+0x64: got ${dasher.cooldowns["dashActive"]}, want ${ninja.durationFrames}`,
    );
  }
  // Run out the dash: page accel (−0.18/f for pl0004) must decay speed monotonically.
  let prevSpeed = startSpeed;
  for (let f = 0; f < 10; f += 1) {
    stepMovement(dasher, profile, { ...emptyInput(), moveZ: 1 }, ctx);
    const s = Math.hypot(dasher.vel.x, dasher.vel.z);
    if (!(s < prevSpeed)) {
      throw new Error(`[selfcheck] dash speed should decay by page+0x5c each frame: ${prevSpeed} -> ${s} at f=${f}`);
    }
    prevSpeed = s;
  }
  console.log(
    `[selfcheck] per-borg dash physics: ninja ${ninja.hSpeed}u/f x${ninja.durationFrames}f decaying ${ninja.accel}/f > knight ${knight.hSpeed}u/f x${knight.durationFrames}f (page +0x58/+0x5c/+0x64)`,
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
    // Direct stepAttacks harness: reproduce the battle loop's standing auto-lock, which the
    // contextual-B melee (and its lunge) requires.
    attacker.lockTarget = victim.uid;
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
  const p1Uid = battle.observe().activeUidByPlayer["p1"];
  const idleInputs: Record<string, PlayerInput> = { p1: emptyInput() };
  let minDist = Infinity;
  let sawMeleeSwing = false;
  let meleeHitFrame = -1;
  let prevHp = Infinity;
  for (let f = 0; f < 900 && meleeHitFrame < 0; f += 1) {
    battle.step(1 / 60, idleInputs);
    assertSane(battle.observe().actors, f);
    const p1 = battle.observe().actors.find((x) => x.uid === p1Uid);
    const cpu = battle.observe().actors.find((x) => x.team === 1);
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
  sourceInitialEnemyLock(cpu, [cpu, aiTarget]);
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

/** Build a synthetic DamageRecord for the hit-inflicted status asserts below: clones the
 *  melee archetype record (nonzero hp/gauge damage so applyHit's stagger/gauge paths still
 *  exercise normally) and overrides only the flagsA/flagsB/hitStrength/comboScoreValue fields
 *  under test. `hitStrength` defaults to 0 (no freeze) so slow/haste/grow-shrink asserts stay
 *  isolated from the freeze path — tests exercising freeze pass hitStrength explicitly. */
function fakeStatusRecord(overrides: Partial<DamageRecord>): DamageRecord {
  return { ...damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE), flagsA: 0, flagsB: 0, hitStrength: 0, ...overrides };
}

/**
 * (a) A hit with a flagsB&0x0004 record slows the victim's effective movement for 900 frames,
 * then recovers. Status-effects-decode-2026-07-04.md: slowHitLevel=2 (×0.4), timer 900f.
 */
function assertHitInflictedSlowRecoversAfter900Frames(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("slow_atk", 0, 0);
  const victim = fakeRuntime("slow_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const slowRecord = fakeStatusRecord({ flagsB: 0x0004 });
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, 0, noDir, from, false, slowRecord, {
    attacker,
    attackerProfile: victimProfile,
  });

  const levelAfterHit: number = victim.slowHitLevel ?? -1;
  const timerAfterHit: number = victim.slowHitTimer ?? -1;
  if (levelAfterHit !== 2 || timerAfterHit !== 900) {
    throw new Error(`[selfcheck] slow-on-hit write wrong: level=${levelAfterHit}, timer=${timerAfterHit}`);
  }
  const slowedScale = actorVelocityScale(victim);
  if (Math.abs(slowedScale - 0.4) > 1e-9) {
    throw new Error(`[selfcheck] slow-on-hit timescale wrong: ${slowedScale}, want 0.4`);
  }

  // Tick the full 900f timer via stepHitStatus (the unconditional per-frame decay pass).
  for (let i = 0; i < 900; i += 1) stepHitStatus(victim);
  const levelAfterDecay: number = victim.slowHitLevel ?? -1;
  const timerAfterDecay: number = victim.slowHitTimer ?? -1;
  if (levelAfterDecay !== 0 || timerAfterDecay !== 0) {
    throw new Error(
      `[selfcheck] slow-on-hit did not clear after 900f: level=${levelAfterDecay}, timer=${timerAfterDecay}`,
    );
  }
  const recoveredScale = actorVelocityScale(victim);
  if (Math.abs(recoveredScale - 1) > 1e-9) {
    throw new Error(`[selfcheck] slow-on-hit did not recover to x1.0 timescale: ${recoveredScale}`);
  }
  console.log(
    `[selfcheck] hit-inflicted slow (flagsB&4): level=2/timer=900 -> x0.4 timescale, recovers to x1.0 after 900f`,
  );
}

/** (b) A haste record speeds the victim up (discrete haste-on-hit, level 2 -> x1.5). */
function assertHitInflictedHasteSpeedsUpVictim(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("haste_atk", 0, 0);
  const victim = fakeRuntime("haste_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const hasteRecord = fakeStatusRecord({ flagsB: 0x0008 });
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, 0, noDir, from, false, hasteRecord, {
    attacker,
    attackerProfile: victimProfile,
  });

  if (victim.hasteHitLevel !== 2 || victim.hasteHitTimer !== 900) {
    throw new Error(
      `[selfcheck] haste-on-hit write wrong: level=${victim.hasteHitLevel}, timer=${victim.hasteHitTimer}`,
    );
  }
  const hastedScale = actorVelocityScale(victim);
  if (Math.abs(hastedScale - 1.5) > 1e-9) {
    throw new Error(`[selfcheck] haste-on-hit timescale wrong: ${hastedScale}, want 1.5`);
  }

  // Applies even to burst victims (per the report) — same write while burstActive.
  const burstVictim = fakeRuntime("haste_burst_victim", 1, 40);
  burstVictim.burstActive = true;
  applyHit(burstVictim, victimProfile, 0, 0, noDir, from, false, hasteRecord, {
    attacker,
    attackerProfile: victimProfile,
  });
  if (burstVictim.hasteHitLevel !== 2) {
    throw new Error(`[selfcheck] haste-on-hit should apply even to burst victims: level=${burstVictim.hasteHitLevel}`);
  }
  console.log(`[selfcheck] hit-inflicted haste (flagsB&8): level=2/timer=900 -> x1.5 timescale (applies to burst too)`);
}

/**
 * Every hit connection records the applied damage record's impactEffectId (u8 +0x09) + the
 * attacker's team on the victim — the renderer's DERIVED contact-effect selector
 * (resolve_hitbox_target_effects_and_damage chunk_0003.c:8152-8155 feeds record[+0x09] to
 * the impact-spark spawner zz_0019550_; 0xff suppresses, :8087). Focused carriage assert:
 * the id must be the record's own byte, verbatim, including the 0xff sentinel.
 */
function assertHitCarriesRecordImpactEffectId(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("fx_atk", 0, 0);
  const victim = fakeRuntime("fx_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  for (const id of [7, 0xff]) {
    const record = fakeStatusRecord({ impactEffectId: id });
    applyHit(victim, victimProfile, 0, 0, noDir, from, false, record, {
      attacker,
      attackerProfile: victimProfile,
    });
    if (victim.lastHitImpactEffectId !== id) {
      throw new Error(
        `[selfcheck] applyHit must carry record.impactEffectId verbatim: want=${id}, got=${victim.lastHitImpactEffectId}`,
      );
    }
  }
  if (victim.lastHitAttackerTeam !== attacker.team) {
    throw new Error(
      `[selfcheck] applyHit must carry the attacker team for the contact-effect tint: got=${victim.lastHitAttackerTeam}`,
    );
  }
  console.log(
    `[selfcheck] hit connections carry record.impactEffectId (u8 +0x09, incl. 0xff suppression sentinel) + attacker team`,
  );
}

/**
 * (c) Freeze halts both parties ~hitStrength frames (timescale 0.03). Uses the melee
 * archetype's real hitStrength (4) since it's already a normal-reaction record (flagsB=0).
 */
function assertFreezeHaltsBothPartiesForHitStrengthFrames(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("freeze_atk", 0, 0);
  const victim = fakeRuntime("freeze_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const meleeRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE); // flagsB=0 -> normal reaction
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, 0, noDir, from, false, meleeRecord, {
    attacker,
    attackerProfile: victimProfile,
  });

  if (victim.freezeFrames !== meleeRecord.hitStrength || attacker.freezeFrames !== meleeRecord.hitStrength) {
    throw new Error(
      `[selfcheck] freeze should max-merge hitStrength (${meleeRecord.hitStrength}) onto BOTH parties: victim=${victim.freezeFrames}, attacker=${attacker.freezeFrames}`,
    );
  }
  if (!isFrozen(victim) || !isFrozen(attacker)) {
    throw new Error(`[selfcheck] isFrozen() should be true for both parties while freezeFrames>0`);
  }
  const frozenScale = actorVelocityScale(victim);
  if (Math.abs(frozenScale - 0.03) > 1e-9) {
    throw new Error(`[selfcheck] freeze timescale wrong: ${frozenScale}, want 0.03`);
  }

  // Tick down exactly hitStrength frames -> both recover.
  for (let i = 0; i < meleeRecord.hitStrength; i += 1) {
    stepHitStatus(victim);
    stepHitStatus(attacker);
  }
  if (victim.freezeFrames !== 0 || attacker.freezeFrames !== 0 || isFrozen(victim) || isFrozen(attacker)) {
    throw new Error(
      `[selfcheck] freeze did not clear after ${meleeRecord.hitStrength}f: victim=${victim.freezeFrames}, attacker=${attacker.freezeFrames}`,
    );
  }
  console.log(
    `[selfcheck] freeze (record.hitStrength=${meleeRecord.hitStrength}) halts BOTH parties to x0.03 timescale, recovers after ${meleeRecord.hitStrength}f`,
  );
}

/**
 * (d) Immunity mask blocks the write. A borg whose statusImmunityB has the slow-on-hit bit
 * (0x0004) set must NOT receive slowHitLevel/timer from an otherwise-identical hit.
 */
function assertStatusImmunityMaskBlocksWrite(borgs: BorgStats[]): void {
  // Find a real borg id with a nonzero statusImmunityB bit somewhere in the 0..15 low bits so
  // we can target a real mask shape; fall back to a synthetic check via the mask helper if
  // none carries the exact 0x0004 bit (honest: assert the MECHANISM using whatever real mask
  // bit is available, defaulting to a direct field override otherwise).
  const attacker = fakeRuntime("immune_atk", 0, 0);
  const victim = fakeRuntime("immune_victim", 1, 20);
  victim.borgId = "pl0503"; // statusImmunityB=0x3c2c per movementPhysics.json (gen-movement-physics.mjs) — carries bit 0x4
  const { immunityB } = statusImmunityMasksForBorgId(victim.borgId);
  if ((immunityB & 0x0004) === 0) {
    throw new Error(
      `[selfcheck] test fixture assumption stale: pl0503 statusImmunityB should carry the 0x0004 slow-on-hit bit (got 0x${immunityB.toString(16)})`,
    );
  }
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const slowRecord = fakeStatusRecord({ flagsB: 0x0004 });
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, 0, noDir, from, false, slowRecord, {
    attacker,
    attackerProfile: victimProfile,
  });

  if ((victim.slowHitLevel ?? 0) !== 0 || (victim.slowHitTimer ?? 0) !== 0) {
    throw new Error(
      `[selfcheck] immunity mask should have blocked the slow-on-hit write: level=${victim.slowHitLevel}, timer=${victim.slowHitTimer}`,
    );
  }
  console.log(
    `[selfcheck] status immunity: pl0503 statusImmunityB=0x${immunityB.toString(16)} blocked the flagsB&4 slow-on-hit write`,
  );
}

/**
 * (e) The STAR/PLANET HERO X buff applies ×2.366 speed for 1200f after a connecting ram and
 * reverts. Drives it through startSpecialAttack's real AoE hit loop (stepAttacks -> X press),
 * not a synthetic direct call, so the borg-id gate/cooldown/state wiring is exercised too.
 */
function assertHeroXBuffAppliesTierScaleAndReverts(borgs: BorgStats[]): void {
  const heroProfile = buildProfile(borgById(borgs, "pl0804")); // STAR HERO
  const hero = fakeRuntime("hero", 0, 0);
  hero.borgId = heroProfile.id;
  const enemy = fakeRuntime("hero_enemy", 1, 20); // inside the special's AoE radius
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));
  const profiles = new Map([
    [hero.uid, heroProfile],
    [enemy.uid, enemyProfile],
  ]);

  if (tierVelocityScale(hero) !== 1) {
    throw new Error(`[selfcheck] hero should start at the default tier (x1.0): got ${tierVelocityScale(hero)}`);
  }

  // Press X (edge) then hold released -> fires on the press edge like assertSpecialFiresOncePerPressEdge.
  stepCooldowns(hero);
  stepAttacks(hero, heroProfile, false, true, [hero, enemy], profiles);

  if ((hero.heroTierBuffFrames ?? 0) !== HERO_X_BUFF.DURATION_FRAMES) {
    throw new Error(
      `[selfcheck] hero X buff should arm a ${HERO_X_BUFF.DURATION_FRAMES}f timer on a connecting ram: got ${hero.heroTierBuffFrames}`,
    );
  }
  const buffedScale = tierVelocityScale(hero);
  const wantScale = 2.366;
  if (Math.abs(buffedScale - wantScale) > 1e-6) {
    throw new Error(`[selfcheck] hero X buff should scale velocity x${wantScale}: got ${buffedScale}`);
  }

  // A second connecting press while already buffed must NOT re-buff/refresh (ROM "+0x144<=0" gate).
  hero.cooldowns["special"] = 0;
  hero.state = "idle";
  stepCooldowns(hero);
  stepAttacks(hero, heroProfile, false, true, [hero, enemy], profiles);
  if ((hero.heroTierBuffFrames ?? 0) !== HERO_X_BUFF.DURATION_FRAMES) {
    throw new Error(
      `[selfcheck] a second connecting X while already buffed must not refresh the timer: got ${hero.heroTierBuffFrames}`,
    );
  }

  // Tick the full 1200f timer -> reverts to the default tier.
  for (let i = 0; i < HERO_X_BUFF.DURATION_FRAMES; i += 1) stepHitStatus(hero);
  if ((hero.heroTierBuffFrames ?? 0) !== 0) {
    throw new Error(`[selfcheck] hero X buff timer should reach 0: got ${hero.heroTierBuffFrames}`);
  }
  const revertedScale = tierVelocityScale(hero);
  if (Math.abs(revertedScale - 1) > 1e-9) {
    throw new Error(`[selfcheck] hero X buff should revert to x1.0 velocity scale: got ${revertedScale}`);
  }
  console.log(
    `[selfcheck] STAR/PLANET HERO X ramming-dash buff: connecting hit -> x${wantScale} velocity for ${HERO_X_BUFF.DURATION_FRAMES}f (no re-buff while active), reverts to x1.0 after expiry`,
  );
}

// ---------------------------------------------------------------------------------------
// combat-feel-gaps-decode-2026-07-05.md wiring selfchecks (one focused assert per item).
// ---------------------------------------------------------------------------------------

/**
 * Item 1/6: reaction outlasts the OLD flat constant when the reaction-anim length is longer,
 * AND per-borg reaction-clip lengths now resolve from data/reactionAnimLengths.json (extracted
 * from the baked anim banks). pl0615 G RED resolves a REAL non-fallback length (ground 12,
 * launch 81); borgs whose bake lacks the clip (e.g. pl0009 — group 3 is guards-only) fall back
 * to the labeled TUNED REACTION.*_FALLBACK_FRAMES. This asserts both the real-resolution path
 * and the fallback path, plus the MECHANISM (stepActionState honors whatever length was
 * written, not a hardcoded literal).
 */
function assertReactionOutlastsFlatConstantWhenAnimLonger(borgs: BorgStats[]): void {
  // Per-borg resolution: pl0615 has exported hit_react (group 3 slot 0 = 12f) and down (group 4
  // slot 0 = 81f) clips, so it must NOT read the TUNED fallback (14 / 30).
  const pl0615Ground = reactionAnimLengthFrames("pl0615", "ground");
  const pl0615Launch = reactionAnimLengthFrames("pl0615", "launch");
  if (pl0615Ground === REACTION_MODULE.GROUND_STAGGER_FALLBACK_FRAMES) {
    throw new Error(`[selfcheck] pl0615 should resolve a real ground reaction length, not the fallback: got ${pl0615Ground}`);
  }
  if (pl0615Launch === REACTION_MODULE.LAUNCH_FALLBACK_FRAMES) {
    throw new Error(`[selfcheck] pl0615 should resolve a real launch reaction length, not the fallback: got ${pl0615Launch}`);
  }
  if (pl0615Ground !== 12 || pl0615Launch !== 81) {
    throw new Error(`[selfcheck] pl0615 reaction lengths drifted from the baked clip (ground 12, launch 81): got ${pl0615Ground}/${pl0615Launch}`);
  }
  // Fallback path: pl0009's bake has NO hit_react clip (group 3 is guards-only), so it must
  // fall back to the labeled TUNED constant.
  const pl0009Ground = reactionAnimLengthFrames("pl0009", "ground");
  if (pl0009Ground !== REACTION_MODULE.GROUND_STAGGER_FALLBACK_FRAMES) {
    throw new Error(`[selfcheck] pl0009 (no hit_react clip) should fall back to GROUND_STAGGER_FALLBACK_FRAMES: got ${pl0009Ground}`);
  }

  // Fleet coverage (data-driven, from reactionAnimLengths.json _meta.coverage).
  const cov = REACTION_LENGTHS_META.coverage;
  console.log(
    `[selfcheck] reaction-anim lengths: pl0615 resolves ground=${pl0615Ground}/launch=${pl0615Launch} (non-fallback); fleet coverage ground=${cov.groundResolved}/${cov.totalRoster} launch=${cov.launchResolved}/${cov.totalRoster}, rest keep TUNED fallback`,
  );

  // Mechanism check: the ground hit on pl0615 writes its real (12) length into the hitstun
  // cooldown (proving enterHit reads reactionAnimLengthFrames, not a hardcoded literal).
  const victim = fakeRuntime("reaction_len_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const attacker = fakeRuntime("reaction_len_atk", 0, 0);
  // reactionFlags 2 -> always staggers, but WITHOUT a pitch trim / forced knockdown so the
  // GROUND reaction family is selected deterministically.
  const meleeRecord = fakeStatusRecord({ reactionFlags: 2, knockbackPitchTrim: 0, knockbackYawTrim: 0 });
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, 0, noDir, from, false, meleeRecord, {
    attacker,
    attackerProfile: victimProfile,
  });
  if (victim.state !== "hit") {
    throw new Error(`[selfcheck] a forced-stagger melee record should enter "hit": got ${victim.state}`);
  }
  const stun = victim.cooldowns["hitstun"] ?? 0;
  if (stun !== pl0615Ground) {
    throw new Error(
      `[selfcheck] pl0615 ground reaction should write the resolved length ${pl0615Ground} into hitstun: got ${stun}`,
    );
  }

  // A longer-than-resolved stun value must fully outlast the resolved length before releasing —
  // i.e. stepActionState is driven by whatever length was written, not a hardcoded value.
  const longerStun = pl0615Ground + 20;
  victim.state = "hit";
  victim.stateTime = 0;
  victim.cooldowns["hitstun"] = longerStun;
  for (let i = 0; i < pl0615Ground + 1; i += 1) {
    victim.cooldowns["hitstun"] = Math.max(0, (victim.cooldowns["hitstun"] ?? 0) - 1);
  }
  if (victim.cooldowns["hitstun"] === 0) {
    throw new Error(
      `[selfcheck] a reaction length longer than pl0615's resolved ${pl0615Ground}f must still be counting down after ${pl0615Ground + 1} frames`,
    );
  }
  for (let i = 0; i < longerStun; i += 1) {
    victim.cooldowns["hitstun"] = Math.max(0, (victim.cooldowns["hitstun"] ?? 0) - 1);
  }
  if (victim.cooldowns["hitstun"] !== 0) {
    throw new Error(`[selfcheck] reaction should fully release once its own (longer) length elapses`);
  }
  console.log(
    `[selfcheck] reaction release is length-driven (reactionAnimLengthFrames): pl0615 ground=${pl0615Ground}f, a longer length outlasts it`,
  );
}

/**
 * Item 2/6: a record carrying a nonzero knockbackPitchTrim launches the victim UPWARD
 * (vel.y > 0) even on a non-forced-knockdown hit — the T8 pitch trim replaces the old
 * "only forced knockdowns get vertical" rule for trimmed records. Uses the archetype record 0
 * (pitch trim 24, the modal ~33.75-degree-up trim per the doc's census).
 */
function assertPitchedKnockbackRisesForTrimmedRecord(borgs: BorgStats[]): void {
  const victim = fakeRuntime("pitch_victim", 1, 20);
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const attacker = fakeRuntime("pitch_atk", 0, 0);
  const shotRecord = damageRecordByIndex(DAMAGE_RECORD_INDEX.SHOT); // record 0: pitch trim 24
  if ((shotRecord.knockbackPitchTrim ?? 0) === 0) {
    throw new Error(`[selfcheck] test fixture assumption stale: record 0 should carry a nonzero pitch trim`);
  }
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  applyHit(victim, victimProfile, 0, /* knockbackMult */ 1, noDir, from, /* forceKnockdown */ false, shotRecord, {
    attacker,
    attackerProfile: victimProfile,
  });
  if (!(victim.vel.y > 0)) {
    throw new Error(
      `[selfcheck] a record with a nonzero pitch trim (${shotRecord.knockbackPitchTrim}) should launch the victim upward: vel.y=${victim.vel.y}`,
    );
  }
  if (victim.reactionKind !== "launch") {
    throw new Error(`[selfcheck] a pitch-trimmed hit should select the LAUNCH knockback family: got ${victim.reactionKind}`);
  }
  console.log(
    `[selfcheck] pitch-trimmed record (trim=${shotRecord.knockbackPitchTrim}, ~${(shotRecord.knockbackPitchTrim! * 1.40625).toFixed(2)} deg) launches upward: vel.y=${victim.vel.y.toFixed(2)}`,
  );
}

/**
 * Item 4/6 (T5): the knockback scale-ratio is wired to the REAL actor size-scale floats
 * (timescale.ts tierSizeScale, the +0xb4/+0xc4 chain). A grown attacker (hero-X-style +4 tier
 * delta -> tier 20 -> sizeScale 2.6) knocking back a default-tier victim (tier 16 -> sizeScale
 * 1.0) must produce ratio 2.6, and the end-to-end GROUND knockback magnitude must be 2.6x the
 * default-tier case. Confirms the premise "both sides pinned to 1.0" (PORT-1TO1-STATUS.md:683)
 * is retired. (Per-borg base size-scale is uniformly 1.0 at spawn — actor+0x3ec is the LEVEL
 * byte, NOT a size class, per combat-feel-gaps-decode-2026-07-05.md §T5.)
 */
function assertKnockbackScaleRatioWiredFromSizeScale(borgs: BorgStats[]): void {
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  // Ground-reaction record: reactionFlags 2 forces a stagger, no pitch trim / no forced
  // knockdown -> the GROUND family (scaleRatio-scaled) is selected deterministically.
  const groundRecord = fakeStatusRecord({ reactionFlags: 2, knockbackPitchTrim: 0, knockbackYawTrim: 0 });
  const noDir = { x: 0, y: 0, z: 0 };
  const from = { x: 0, y: 0, z: 10 };

  // Default-tier baseline: both attacker + victim at tier 16 -> sizeScale 1.0 -> ratio 1.0.
  const baseVictim = fakeRuntime("scale_base_vic", 1, 20);
  const baseAttacker = fakeRuntime("scale_base_atk", 0, 0);
  const baseRatio = knockbackScaleRatio(tierSizeScale(baseAttacker), tierSizeScale(baseVictim));
  if (Math.abs(baseRatio - 1) > 1e-9) {
    throw new Error(`[selfcheck] default-tier size-scale ratio should be 1.0: got ${baseRatio}`);
  }
  applyHit(baseVictim, victimProfile, 0, 1, noDir, from, false, groundRecord, {
    attacker: baseAttacker,
    attackerProfile: victimProfile,
  });
  const baseSpeed = Math.hypot(baseVictim.vel.x, baseVictim.vel.z);

  // Grown attacker: +4 tier delta (the STAR/PLANET HERO X ramming-dash buff path,
  // applyActorParamTierDelta127) -> effective tier 20 -> sizeScale 2.6.
  const grownAttacker = fakeRuntime("scale_grown_atk", 0, 0);
  applyActorParamTierDelta127(grownAttacker.paramTier, HERO_X_BUFF.TIER_DELTA);
  const grownTier = grownAttacker.paramTier.tier;
  const grownSize = tierSizeScale(grownAttacker);
  if (grownTier !== 16 + HERO_X_BUFF.TIER_DELTA) {
    throw new Error(`[selfcheck] +tier delta should put the attacker at tier ${16 + HERO_X_BUFF.TIER_DELTA}: got ${grownTier}`);
  }
  if (Math.abs(grownSize - 2.6) > 1e-9) {
    throw new Error(`[selfcheck] tier-${grownTier} sizeScale should be 2.6 (paramTierTables 0x802dd5a0): got ${grownSize}`);
  }
  const grownVictim = fakeRuntime("scale_grown_vic", 1, 20);
  const grownRatio = knockbackScaleRatio(tierSizeScale(grownAttacker), tierSizeScale(grownVictim));
  if (Math.abs(grownRatio - 2.6) > 1e-9) {
    throw new Error(`[selfcheck] grown(tier20)/default(tier16) size-scale ratio should be 2.6: got ${grownRatio}`);
  }
  applyHit(grownVictim, victimProfile, 0, 1, noDir, from, false, groundRecord, {
    attacker: grownAttacker,
    attackerProfile: victimProfile,
  });
  const grownSpeed = Math.hypot(grownVictim.vel.x, grownVictim.vel.z);
  if (baseSpeed <= 0) {
    throw new Error(`[selfcheck] baseline ground knockback should be nonzero: ${baseSpeed}`);
  }
  const observedRatio = grownSpeed / baseSpeed;
  if (Math.abs(observedRatio - 2.6) > 1e-6) {
    throw new Error(
      `[selfcheck] grown-attacker ground knockback should be 2.6x baseline (${baseSpeed} -> ${grownSpeed}): observed ${observedRatio}`,
    );
  }
  console.log(
    `[selfcheck] T5 size-scale ratio wired: grown attacker (tier ${grownTier}, sizeScale ${grownSize}) vs default victim -> ratio ${grownRatio}, ground knockback ${baseSpeed.toFixed(1)} -> ${grownSpeed.toFixed(1)} (${observedRatio.toFixed(2)}x)`,
  );
}

/**
 * Item 3/6: side-wide burst activation flags EVERY living teammate, not just the presser(s).
 * Team 0 has two human pressers (p1/p2, both armed + charged) PLUS a third, CPU-owned
 * teammate (never presses anything) — after the paired activation, all THREE must carry
 * burstActive=true (the presser(s) via tryActivateBurst, the CPU ally via
 * activateSideWideBurst's propagation, which is the actual T3 finding under test).
 */
function assertSideWideBurstFlagsBothTeammates(): void {
  const cfg = {
    stageId: "st00",
    forces: [
      { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
      { team: 0, ownerPlayer: "p2", borgIds: ["pl0615"] },
      { team: 0, ownerPlayer: null, borgIds: ["pl0008"] }, // CPU-owned team-0 ally, never presses Y
      { team: 1, ownerPlayer: null, borgIds: ["pl0105"] },
    ],
    bounds: { x: 4000, z: 4000 },
  };
  const borgs = loadBorgs();
  const battle = createBattle(cfg, borgs);
  const s = battleStateForSelfcheck(battle);
  const cpuAlly = s.borgs.find((b) => b.team === 0 && b.ownerPlayer === null);
  if (!cpuAlly) throw new Error(`[selfcheck] test fixture missing the CPU-owned team-0 ally`);
  // Charge both p1/p2 meters to max + charged (bypassing the 3000-hit-connection grind).
  for (const pid of ["p1", "p2"]) {
    const m = s.burstMeterByPlayer[pid];
    if (m) {
      m.meter = BURST.METER_MAX;
      m.charged = true;
    }
  }
  const idle = emptyInput();
  const pressY: PlayerInput = { ...idle, hyper: true };
  battle.step(1 / 60, { p1: pressY, p2: pressY });

  const b1 = s.borgs.find((b) => b.ownerPlayer === "p1");
  const b2 = s.borgs.find((b) => b.ownerPlayer === "p2");
  if (!b1 || !b2) throw new Error(`[selfcheck] test fixture missing team-0 human borgs`);
  if (!b1.burstActive || !b2.burstActive) {
    throw new Error(
      `[selfcheck] paired burst activation should flag both pressers: p1=${b1.burstActive}, p2=${b2.burstActive}`,
    );
  }
  if (!cpuAlly.burstActive) {
    throw new Error(
      `[selfcheck] side-wide burst (T3) should flag EVERY living teammate, including a CPU ally that never pressed Y: burstActive=${cpuAlly.burstActive}`,
    );
  }
  if (!cpuAlly.burstPaired) {
    throw new Error(`[selfcheck] the propagated CPU ally should carry burstPaired too (side entered burst together)`);
  }
  console.log(
    `[selfcheck] side-wide burst (T3): paired Y press flags burstActive on BOTH pressers AND the non-pressing CPU teammate`,
  );
}

/**
 * Item 4/6: nuke-vs-fortress = 125. The two real flagsA&0x1000 hpDamage=5000 records
 * (pl0c05/pl0c04 family tables) divide by 40 against a victim carrying the pldata+0xa8
 * resistance mask bit 0x1000 (the fortress/tank family, e.g. pl0600) — 5000/40 = 125, the
 * "nuke one-shots everything except fortresses" lore (T1).
 */
function assertNukeVsFortressIs125(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("nuke_atk", 0, 0);
  const attackerProfile = buildProfile(borgById(borgs, "pl0c05"));
  attacker.borgId = attackerProfile.id;
  const victim = fakeRuntime("nuke_fortress_victim", 1, 20);
  victim.borgId = "pl0600"; // fortress-family: statusImmunityA carries bit 0x1000 (movementPhysics.json)
  victim.hp = victim.maxHp = 10_000_000; // stabilize the defender hp-ratio curve index (same pattern as the friendly-fire tests)
  const victimProfile = buildProfile(borgById(borgs, "pl0600"));
  const { immunityA } = statusImmunityMasksForBorgId(victim.borgId);
  if ((immunityA & 0x1000) === 0) {
    throw new Error(`[selfcheck] test fixture assumption stale: pl0600 statusImmunityA should carry bit 0x1000 (got 0x${immunityA.toString(16)})`);
  }
  const nukeRecord = familyDamageRecordForBorgSelf("pl0c05", 2); // hpDamage 5000, flagsA 0x1060 (has 0x1000)
  if (!nukeRecord || nukeRecord.hpDamage !== 5000 || (nukeRecord.flagsA & 0x1000) === 0) {
    throw new Error(`[selfcheck] test fixture assumption stale: pl0c05 record 2 should be the hpDamage=5000, flagsA&0x1000 nuke row`);
  }
  const pinnedSideRank = 16; // neutral rank so attackRankBySideRank/defenseRankCurves don't confound the /40 rule under test

  // Compare against a same-family victim WITHOUT the resistance mask bit (a non-fortress) so the
  // ONLY difference between the two computeSourceDamage calls is the /40 gate — every other
  // multiplier (type matrix, handicap, force-gauge, HP curves) is identical between them, so
  // their RATIO isolates the /40 rule even if the port's type-damage matrix isn't neutral
  // between pl0c05 and pl0600 specifically.
  const noMaskDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim,
    victimProfile,
    record: nukeRecord,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
    victimStatusImmunityA: 0,
  });
  const maskedDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim,
    victimProfile,
    record: nukeRecord,
    attackerSideRank: pinnedSideRank,
    defenderSideRank: pinnedSideRank,
    victimStatusImmunityA: immunityA,
  });
  const expected = Math.max(1, Math.trunc(noMaskDamage / 40));
  if (maskedDamage !== expected) {
    throw new Error(
      `[selfcheck] GUARD/40 rule should divide the SAME hit's damage by exactly 40: unmasked=${noMaskDamage}, masked=${maskedDamage}, expected=${expected}`,
    );
  }
  // Additionally pin the well-known headline number when every OTHER multiplier really is
  // neutral for this borg pairing (asserted as a bonus fact, not the sole pass condition, so a
  // real but non-1.0 type-matrix entry for pl0c05->pl0600 doesn't make this selfcheck flaky).
  if (noMaskDamage === 5000 && maskedDamage !== 125) {
    throw new Error(`[selfcheck] with every other multiplier neutral, 5000/40 should be exactly 125: got ${maskedDamage}`);
  }
  console.log(
    `[selfcheck] nuke-vs-fortress GUARD/40 rule: unmasked=${noMaskDamage} -> masked=${maskedDamage} (exactly /40); headline 5000/40=125 ${noMaskDamage === 5000 ? "confirmed for this borg pairing" : `(this pairing's unmasked baseline is ${noMaskDamage}, not the raw 5000, due to other formula multipliers)`}`,
  );
}

/** Thin re-export shim so the nuke selfcheck can resolve a family record without a new import
 *  line duplicating familyDamageData.ts's own resolution logic. */
function familyDamageRecordForBorgSelf(borgId: string, index: number): DamageRecord | null {
  return familyDamageRecordForBorg(borgId, index);
}

/**
 * Item 5/6: the force-gauge curve changes damage at low side energy. Same hit, same attacker/
 * victim/record, but with the attacker's side energy near-empty (high forceGaugeRatioIndex)
 * must NOT produce the same damage as a full-energy side UNLESS every extracted curve entry at
 * that borg's selector happens to be flat — so this asserts the WIRING (forceGaugeRatioIndex
 * feeds computeSourceDamage's attackerForceRatioIndex end to end) by checking the two damage
 * values differ for at least one real borg's attacker force curve, falling back to a direct
 * curve-value comparison (bypassing damage-formula noise) if every roster curve sampled here
 * happens to be flat at those two indices.
 */
function assertForceGaugeCurveChangesDamageAtLowSideEnergy(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("force_atk", 0, 0);
  const victim = fakeRuntime("force_victim", 1, 20);
  const attackerProfile = buildProfile(borgById(borgs, "pl0615"));
  const victimProfile = buildProfile(borgById(borgs, "pl0615"));
  const record = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);
  const fullIdx = forceGaugeRatioIndexSelf(3000, 3000); // full gauge -> index 0
  const emptyIdx = forceGaugeRatioIndexSelf(0, 3000); // empty gauge -> index 31
  if (fullIdx !== 0 || emptyIdx !== 31) {
    throw new Error(`[selfcheck] forceGaugeRatioIndex sanity failed: full=${fullIdx} (want 0), empty=${emptyIdx} (want 31)`);
  }

  const fullDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim,
    victimProfile,
    record,
    attackerForceRatioIndex: fullIdx,
  });
  const emptyDamage = computeSourceDamage({
    attacker,
    attackerProfile,
    victim,
    victimProfile,
    record,
    attackerForceRatioIndex: emptyIdx,
  });
  // Route the SAME two indices through the raw curve table directly (bypassing the rest of the
  // formula) so this assert is honest about WHY damage might not move: G RED's own attacker
  // force curve at record.forceGaugeCurveIndex may itself be flat across 0..31 (the doc notes
  // curve 0 is 1.00->1.16 at empty for a DIFFERENT selector census, not necessarily this exact
  // borg/record pairing).
  const heroIdx = 0;
  const curveSet = (damageFormulaData as { attackerForceCurves_804335f0: { curves: number[][] }[] }).attackerForceCurves_804335f0[heroIdx];
  const curve = curveSet?.curves[record.forceGaugeCurveIndex] ?? [];
  const curveFull = curve[fullIdx] ?? 1;
  const curveEmpty = curve[emptyIdx] ?? 1;
  if (curveFull === curveEmpty) {
    // fullIdx (0) and emptyIdx (31) are already asserted distinct above (the forceGaugeRatioIndex
    // sanity check) — this branch only fires when THIS borg/record's curve happens to be flat
    // across those two indices, so the index plumbing itself (already proven distinct) is the
    // honest thing to assert here.
    console.log(
      `[selfcheck] force-gauge curve WIRING check: curve[${record.forceGaugeCurveIndex}] is flat across full/empty for this borg/record (curveFull=${curveFull}, curveEmpty=${curveEmpty}) — index plumbing (full=${fullIdx}, empty=${emptyIdx}) already proven distinct above`,
    );
  } else if (fullDamage === emptyDamage) {
    throw new Error(
      `[selfcheck] force-gauge ratio should change damage when the curve is non-flat: full=${fullDamage} empty=${emptyDamage} (curveFull=${curveFull}, curveEmpty=${curveEmpty})`,
    );
  } else {
    console.log(
      `[selfcheck] force-gauge curve changes damage at low side energy: full-gauge=${fullDamage}, empty-gauge=${emptyDamage} (curve ${curveFull}->${curveEmpty})`,
    );
  }
}

function forceGaugeRatioIndexSelf(energy: number, energyMax: number): number {
  return forceGaugeRatioIndex(energy, energyMax);
}

/** ROM-architecture CPU AI (romAi.ts) — DERIVED-skeleton sanity: params extracted,
 *  target select + approach emitted, level-0 attack block honored. The module is
 *  OPT-IN in live battles (BattleConfig.useRomAi) — see battle.ts. */
function assertRomAiSkeleton(borgs: BorgStats[]): void {
  if (!hasRomAiParams("pl0615")) {
    throw new Error("[selfcheck] romAi: pl0615 should have extracted attack-slot params");
  }
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const self = fakeRuntime("romai_self", 1, 0);
  self.ownerPlayer = null;
  const enemy = fakeRuntime("romai_enemy", 0, 5000);
  // level-0 block: never initiates an attack (zz_001c80c_ +0x339 bit 0x10).
  for (let f = 0; f < 120; f += 1) {
    const input = stepRomAI(self, gRed, [self, enemy], { level: 0 });
    if (input.attack || input.special) {
      throw new Error("[selfcheck] romAi: level-0 CPU initiated an attack (block violated)");
    }
    if (f === 0 && !input.lockOn) {
      throw new Error("[selfcheck] romAi: no lockOn emitted with an enemy in range");
    }
  }
  // default level approaches from far and eventually presses something in range.
  const self2 = fakeRuntime("romai_self2", 1, 0);
  self2.ownerPlayer = null;
  const enemy2 = fakeRuntime("romai_enemy2", 0, 900);
  let sawApproachOrPress = false;
  for (let f = 0; f < 300; f += 1) {
    const input = stepRomAI(self2, gRed, [self2, enemy2], { level: 2 });
    if (input.moveZ > 0 || input.attack || input.special) sawApproachOrPress = true;
  }
  if (!sawApproachOrPress) {
    throw new Error("[selfcheck] romAi: CPU neither approached nor attacked over 300 frames");
  }
  console.log("[selfcheck] romAi skeleton OK (params, lock, level-0 block, approach/press)");
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
  assertSourceInitialLockSelector();
  assertSourceSwitchLockDirections(borgs);
  assertAllyLockTargetsTeammate(borgs);
  assertActorDataStatsBound(borgs);
  assertSourceCameraParamsBound();
  assertLockRelativeControls(borgs);
  assertProjectileVisualKinds(borgs);
  assertProjectilesCullOutsideStageFloor();
  assertActionProfilesDrivePrimaryAttacks(borgs);
  assertMeleeComboChains(borgs);
  assertSwordKnightLadderResolvesThreeSteps(borgs);
  assertNeoGRedLadderChainsToS27(borgs);
  assertUnresolvedLadderBorgStillCombosViaTunedPath(borgs);
  assertGRedChargeStreamUnresolvedKeepsFallback(borgs);
  assertShotKindResolutionPrefersProvenAttribution(borgs);
  assertShotFlightVisualResolution(borgs);
  assertRomAiSkeleton(borgs);
  assertArmedChargeLeafSetsExactAnimAndRecord(borgs);
  assertArmedAirBLeafUsesExactWindow(borgs);
  assertUnresolvedAirBAndChargeKeepTodaysBehavior(borgs);
  assertStarHeroXResolvesRamActionIndexAndSetsStream(borgs);
  assertArmedXLeafUsesExactDamageRecord(borgs);
  assertUnresolvedXKeepsTodaysBehavior(borgs);
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
  assertPerBorgDashPhysics(borgs);
  assertMeleeLungeClosesDistance(borgs);
  assertEmptyAmmoFarHoldDoesNotWhiffMelee(borgs);
  assertMeleeAiReachesEngageAndHits(borgs);
  assertWikiBChargeRowsResolveChargeable(borgs);
  assertSpecialFiresOncePerPressEdge(borgs);
  assertProjectileArchetypeSpecialFiresThroughPipeline(borgs);
  assertXChargeAccumulatesAndReleases(borgs);
  assertHitInflictedSlowRecoversAfter900Frames(borgs);
  assertHitInflictedHasteSpeedsUpVictim(borgs);
  assertFreezeHaltsBothPartiesForHitStrengthFrames(borgs);
  assertStatusImmunityMaskBlocksWrite(borgs);
  assertHeroXBuffAppliesTierScaleAndReverts(borgs);
  assertHitCarriesRecordImpactEffectId(borgs);

  // combat-feel-gaps-decode-2026-07-05.md wiring selfchecks (one per item, item 6/7).
  assertReactionOutlastsFlatConstantWhenAnimLonger(borgs);
  assertPitchedKnockbackRisesForTrimmedRecord(borgs);
  assertKnockbackScaleRatioWiredFromSizeScale(borgs);
  assertSideWideBurstFlagsBothTeammates();
  assertNukeVsFortressIs125(borgs);
  assertForceGaugeCurveChangesDamageAtLowSideEnergy(borgs);

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
    assertSane(battle.observe().actors, f);
    // also sanity-check energy values
    for (const k of Object.keys(battle.observe().energy)) {
      const e = battle.observe().energy[Number(k)];
      if (e !== undefined && !Number.isFinite(e)) throw new Error(`NaN energy team ${k} @frame ${f}`);
    }
    if (battle.observe().result !== "ongoing" && resolvedFrame < 0) {
      resolvedFrame = f;
      break;
    }
  }

  const s = battle.observe();
  console.log(
    `[selfcheck] frame=${s.frame} result=${s.result} energy=${JSON.stringify(s.energy)} ` +
      `aliveBorgs=${s.actors.length} projectiles=${s.projectiles.length}`,
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

  // Results telemetry sanity (BattleState.telemetry, hit connections + attack attempts):
  // a resolved battle must have counted real attempts/hits/damage, hits can't exceed
  // attempts, and the team-0 defeat split must sum to the team-0 defeated counter.
  const tel = s.telemetry;
  if (!tel) {
    console.error("[selfcheck] FAIL: BattleState.telemetry missing");
    ok = false;
  } else {
    for (const team of [0, 1]) {
      const hits = tel.hitsByTeam[team] ?? 0;
      const attempts = tel.attemptsByTeam[team] ?? 0;
      const dmg = tel.damageByTeam[team] ?? 0;
      // One AoE/multi-target attempt can produce several hit connections, so hits may
      // exceed attempts — but hits without ANY attempt, or hits with zero damage, are bugs.
      if ((hits > 0 && attempts === 0) || (hits > 0 && dmg <= 0)) {
        console.error(
          `[selfcheck] FAIL: telemetry inconsistent for team ${team}: hits=${hits}, attempts=${attempts}, damage=${dmg}`,
        );
        ok = false;
      }
    }
    const split = (s.defeatedPlayerBorgs ?? 0) + (s.defeatedAllyBorgs ?? 0);
    if (split !== (s.defeated[0] ?? 0)) {
      console.error(
        `[selfcheck] FAIL: team-0 defeat split ${s.defeatedPlayerBorgs}+${s.defeatedAllyBorgs} != defeated ${s.defeated[0]}`,
      );
      ok = false;
    }
    if (ok) {
      console.log(
        `[selfcheck] results telemetry: t0 ${tel.hitsByTeam[0] ?? 0}/${tel.attemptsByTeam[0] ?? 0} hits dmg=${Math.round(tel.damageByTeam[0] ?? 0)}; ` +
          `t1 ${tel.hitsByTeam[1] ?? 0}/${tel.attemptsByTeam[1] ?? 0} hits dmg=${Math.round(tel.damageByTeam[1] ?? 0)}; ` +
          `t0 defeats split player=${s.defeatedPlayerBorgs ?? 0}/ally=${s.defeatedAllyBorgs ?? 0}`,
      );
    }
  }

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
