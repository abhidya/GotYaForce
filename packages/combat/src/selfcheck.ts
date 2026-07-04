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

import { isFiniteVec, yAtTriangleXZ } from "@gf/physics";

import { actorDataCombatStatsForBorgId, actorDataCombatStatsSummary } from "./actorDataStats.js";
import { createBattle } from "./battle.js";
import { stepAI } from "./ai.js";
import { actionProfileForProfile, startingAmmoForProfile } from "./actionProfiles.js";
import {
  applyHit,
  projectileVisualKindForProfile,
  stepAttacks,
  stepCooldowns,
  stepGaugeWindows,
  stepProjectiles,
} from "./combat.js";
import { DASH, JUMP, MELEE, STAGGER, WAKE_UP_INVINCIBILITY_FRAMES } from "./constants.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex, gaugeInitForBorgId } from "./gauges.js";
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
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 0,
  };
  const profile = buildProfile(spoofedRosterStats);
  if (
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
    `[selfcheck] actor-data stat bytes bound: ${expected} exact rows; pl0615 def/shot/atk/spd=${profile.defense}/${profile.shot}/${profile.attack}/${profile.speed}`,
  );
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
  for (let f = 0; f < 25; f += 1) {
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

function assertSameTeamDamageDivisor(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("attacker", 0, 0);
  const ally = fakeRuntime("ally", 0, 20);
  const enemy = fakeRuntime("enemy", 1, 20);
  const profile = buildProfile(borgById(borgs, "pl0615"));
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
  if (input.moveX <= 0) {
    throw new Error("[selfcheck] AI target memory failed: ignored valid lockTarget for nearer enemy");
  }
  console.log("[selfcheck] AI kept valid lockTarget before nearest-enemy fallback");
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
    lockTarget: null,
    allyLockTarget: null,
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
  assertSameTeamDamageDivisor(borgs);
  assertTypeDamageMatrixWired(borgs);
  assertMeleeRefreshesInvincibility(borgs);
  assertAiKeepsLockedTarget(borgs);
  assertFrozenBattleTimerNeverExpires(borgs);
  assertActorParamTierMatchesCClamp();
  assertGaugeStaggerModel(borgs);

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
