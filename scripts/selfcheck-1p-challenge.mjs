#!/usr/bin/env node
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import {
  createBattle,
  emptyInput,
  floorSurfaceYAt,
  JUMP,
} from "../packages/combat/dist/index.js";
import {
  CHALLENGE_DIFFICULTIES,
  CHALLENGE_ENEMY_BUDGETS,
  createChallengeRun,
  toCombatBattleConfig,
} from "../packages/missions/dist/index.js";
import { createNodePublicAssetCatalog, readPublicStageCatalog } from "./lib/node-public-assets.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assetCatalog = createNodePublicAssetCatalog(repoRoot);
const STAGE_ID = "st00";
const PLAYER_ID = "p0";
const GROUND_SNAP_UP = 35;

const borgsData = readJson("packages/assets/data/borgs.json");
const stageCatalog = readPublicStageCatalog(repoRoot);

const borgs = borgsData.borgs;
const firstBattle = buildChallengeBattle();
const stage = await loadStageResources(STAGE_ID);
const combatConfig = toCombatBattleConfig(firstBattle, {
  stageId: STAGE_ID,
  bounds: stage.bounds,
  collision: stage.collision,
});
const battle = createBattle(combatConfig, borgs);

const startEnergy = { ...battle.observe().energy };
let firstEnergyChangeFrame = -1;
let resolvedFrame = -1;
const maxFrames = 18000;

for (let frame = 0; frame < maxFrames; frame += 1) {
  battle.step(1 / 60, { [PLAYER_ID]: playerInput() });
  assertSane(frame);
  if (firstEnergyChangeFrame < 0 && energyChanged(startEnergy, battle.observe().energy)) {
    firstEnergyChangeFrame = frame;
  }
  if (battle.observe().result !== "ongoing") {
    resolvedFrame = frame;
    break;
  }
}

if (firstEnergyChangeFrame < 0) {
  throw new Error("1P Challenge smoke failed: no team energy changed");
}
// DERIVED — original Challenge battles CANNOT end by timeout: setup writes the 18000-frame
// timer AND the pause flag PTR_DAT_80433934[0x50]=1 (chunk_0048.c:390-392), and both the
// countdown and the judge's timeout branches are gated on [0x50]==0 (chunk_0003.c:4631-4638,
// :4519-4553). The old "resolvedByTimer" pass criterion relied on a timeout draw the source
// game doesn't have — it was masking a stalemate, not proving resolution.
// This smoke's job is sim integrity over the real BATTLE 1 force shape. Full-force
// depletion (10 enemy borgs) within 18000 frames needs the still-TUNED combat pacing, so:
// resolution by depletion = PASS; still ongoing = PASS only if real attrition happened
// (enemy energy dropped), which proves the kill/energy pipeline works end-to-end.
const resolvedByDepletion = (battle.observe().energy[0] ?? -1) === 0 || (battle.observe().energy[1] ?? -1) === 0;
if (battle.observe().result !== "ongoing" && !resolvedByDepletion) {
  throw new Error(`1P Challenge smoke failed: resolved battle without KO (result=${battle.observe().result})`);
}
if (battle.observe().timeRemainingFrames !== 18000) {
  throw new Error(
    `1P Challenge smoke failed: frozen Challenge timer ticked (remaining=${battle.observe().timeRemainingFrames})`,
  );
}
const enemyAttrition = (startEnergy[1] ?? 0) - (battle.observe().energy[1] ?? 0);
if (resolvedFrame < 0 && enemyAttrition <= 0) {
  throw new Error("1P Challenge smoke failed: battle neither resolved nor produced enemy attrition");
}

console.log(
  [
    "1P Challenge smoke PASS",
    `stage=${STAGE_ID}`,
    `bounds=${Math.round(stage.bounds.minX)}..${Math.round(stage.bounds.maxX)}/${Math.round(stage.bounds.minZ)}..${Math.round(stage.bounds.maxZ)}`,
    `triangles=${stage.collision.triangles.length}`,
    `startEnergy=${JSON.stringify(startEnergy)}`,
    `firstEnergyChangeFrame=${firstEnergyChangeFrame}`,
    `resolvedFrame=${resolvedFrame}`,
    `result=${battle.observe().result}`,
    `finalEnergy=${JSON.stringify(battle.observe().energy)}`,
  ].join(" "),
);

function buildChallengeBattle() {
  const run = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1,
    playerForces: [{ player: 0, borgIds: ["pl0615"] }],
    borgs: borgsData,
  });
  const battleConfig = run.getCurrentBattle();
  if (!battleConfig) throw new Error("Challenge run did not create BATTLE 1");
  const expectedEnemyTarget = CHALLENGE_ENEMY_BUDGETS[0][0];
  if (battleConfig.meta?.enemyTargetEnergy !== expectedEnemyTarget) {
    throw new Error(`Challenge BATTLE 1 target changed: ${battleConfig.meta?.enemyTargetEnergy}`);
  }
  const cpuAlly = battleConfig.forces.find((force) => force.team === "player" && force.ownerPlayer == null);
  if (!cpuAlly?.cpuAlly) throw new Error("FIGHT ALONE did not add a CPU ally force");
  const enemy = battleConfig.forces.find((force) => force.team === "enemy");
  if (!enemy || enemy.ownerPlayer !== null || enemy.borgIds.length === 0) {
    throw new Error("Challenge BATTLE 1 did not create a CPU enemy force");
  }
  return battleConfig;
}

async function loadStageResources(stageId) {
  const exportedStage = stageCatalog.stages.find((stage) => stage.id === stageId);
  if (!exportedStage) throw new Error(`stage ${stageId} is not in public stage catalog`);
  if (exportedStage.collisionCount <= 0) throw new Error(`stage ${stageId} has no cataloged collision bins`);
  const resources = await assetCatalog.loadStageAssets(stageId);
  if (!resources.bounds || !resources.collision) {
    throw new Error(`stage ${stageId} collision assembly returned no resources`);
  }
  return resources;
}

function playerInput() {
  const activeUid = battle.observe().activeUidByPlayer[PLAYER_ID];
  const self = battle.observe().actors.find((borg) => borg.uid === activeUid);
  if (!self) return emptyInput();
  const target = nearestEnemy(self);
  if (!target) return emptyInput();

  const dx = target.pos.x - self.pos.x;
  const dz = target.pos.z - self.pos.z;
  const d = Math.hypot(dx, dz);
  const inv = d > 1e-3 ? 1 / d : 0;
  return {
    ...emptyInput(),
    moveX: dx * inv,
    moveZ: dz * inv,
    lockOn: true,
    attack: d < 750,
    special: d < 180,
  };
}

function nearestEnemy(self) {
  let best = null;
  let bestD = Infinity;
  for (const other of battle.observe().actors) {
    if (!other.alive || other.team === self.team) continue;
    const d = Math.hypot(other.pos.x - self.pos.x, other.pos.z - self.pos.z);
    if (d < bestD) {
      best = other;
      bestD = d;
    }
  }
  return best;
}

function assertSane(frame) {
  for (const borg of battle.observe().actors) {
    if (!Number.isFinite(borg.hp)) throw new Error(`NaN hp on ${borg.uid} at frame ${frame}`);
    if (!Number.isFinite(borg.rotY)) throw new Error(`NaN rotY on ${borg.uid} at frame ${frame}`);
    for (const key of ["x", "y", "z"]) {
      if (!Number.isFinite(borg.pos[key])) throw new Error(`NaN pos.${key} on ${borg.uid} at frame ${frame}`);
      if (!Number.isFinite(borg.vel[key])) throw new Error(`NaN vel.${key} on ${borg.uid} at frame ${frame}`);
    }
    const floorY = floorSurfaceYAt(stage.collision, borg.pos.x, borg.pos.z, borg.pos.y - JUMP.GROUND_Y + GROUND_SNAP_UP);
    if (floorY == null) {
      throw new Error(`1P Challenge smoke failed: ${borg.uid} left stage floor at frame ${frame} pos=${JSON.stringify(borg.pos)}`);
    }
  }
  for (const value of Object.values(battle.observe().energy)) {
    if (!Number.isFinite(value)) throw new Error(`NaN team energy at frame ${frame}`);
  }
}

function energyChanged(before, after) {
  const teams = new Set([...Object.keys(before), ...Object.keys(after)]);
  for (const team of teams) {
    if ((before[team] ?? 0) !== (after[team] ?? 0)) return true;
  }
  return false;
}

function readJson(file) {
  return JSON.parse(readFileSync(resolveRepo(file), "utf8"));
}

function resolveRepo(file) {
  return path.join(repoRoot, file);
}
