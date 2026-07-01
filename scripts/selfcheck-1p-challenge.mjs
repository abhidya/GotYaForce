#!/usr/bin/env node
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import { createBattle, emptyInput } from "../packages/combat/dist/index.js";
import { hitBin } from "../packages/formats/dist/index.js";
import {
  CHALLENGE_DIFFICULTIES,
  CHALLENGE_ENEMY_BUDGETS,
  createChallengeRun,
} from "../packages/missions/dist/index.js";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const STAGE_ID = "st00";
const PLAYER_ID = "p0";

const borgsData = readJson("packages/assets/data/borgs.json");
const stageCatalog = readJson("apps/game/public/stages/manifest.json");
const stageManifest = readJson(`apps/game/public/stages/${STAGE_ID}/manifest.json`);

const borgs = borgsData.borgs;
const firstBattle = buildChallengeBattle();
const stage = loadStageResources(STAGE_ID, stageManifest);
const combatConfig = convertBattleConfig(firstBattle, STAGE_ID, stage.bounds, stage.collision);
const battle = createBattle(combatConfig, borgs);

const startEnergy = { ...battle.state.energy };
let firstEnergyChangeFrame = -1;
let resolvedFrame = -1;
const maxFrames = 18000;

for (let frame = 0; frame < maxFrames; frame += 1) {
  battle.step(1 / 60, { [PLAYER_ID]: playerInput() });
  assertSane(frame);
  if (firstEnergyChangeFrame < 0 && energyChanged(startEnergy, battle.state.energy)) {
    firstEnergyChangeFrame = frame;
  }
  if (battle.state.result !== "ongoing") {
    resolvedFrame = frame;
    break;
  }
}

if (firstEnergyChangeFrame < 0) {
  throw new Error("1P Challenge smoke failed: no team energy changed");
}
if (resolvedFrame < 0) {
  throw new Error(`1P Challenge smoke failed: battle did not resolve within ${maxFrames} frames`);
}
const resolvedByDepletion = (battle.state.energy[0] ?? -1) === 0 || (battle.state.energy[1] ?? -1) === 0;
const resolvedByTimer = battle.state.result === "draw" && battle.state.timeRemainingFrames === 0;
if (!resolvedByDepletion && !resolvedByTimer) {
  throw new Error("1P Challenge smoke failed: resolved battle without KO or timer expiry");
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
    `result=${battle.state.result}`,
    `finalEnergy=${JSON.stringify(battle.state.energy)}`,
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

function loadStageResources(stageId, manifest) {
  const exportedStage = stageCatalog.stages.find((stage) => stage.id === stageId);
  if (!exportedStage) throw new Error(`stage ${stageId} is not in public stage catalog`);
  if (exportedStage.collisionCount <= 0) throw new Error(`stage ${stageId} has no cataloged collision bins`);
  const collisionFiles = [...(manifest.collision ?? [])].sort((a, b) => a.path.localeCompare(b.path));
  if (collisionFiles.length === 0) throw new Error(`stage ${stageId} manifest has no collision files`);

  const parsed = collisionFiles.map((file) => {
    const bytes = readFileSync(resolveRepo(`apps/game/public/stages/${stageId}/${file.path}`));
    return hitBin.parseStageHitGrid(new Uint8Array(bytes));
  });
  const first = parsed[0];
  if (!first) throw new Error(`stage ${stageId} collision parser returned no grids`);

  const triangles = [];
  const cellsByKey = new Map();
  let base = 0;
  for (let layerIndex = 0; layerIndex < parsed.length; layerIndex += 1) {
    const grid = parsed[layerIndex];
    for (const tri of grid.triangles) {
      triangles.push({
        index: base + tri.index,
        layerIndex,
        marker: tri.marker,
        vertices: tri.vertices,
        normal: tri.normal,
        planeD: tri.planeD,
        bounds2d: tri.bounds2d,
      });
    }
    for (const cell of grid.cells) {
      const key = `${cell.x}:${cell.z}`;
      const target =
        cellsByKey.get(key) ??
        { index: cell.index, triangleIndices: [] };
      target.triangleIndices.push(...cell.recordIndices.map((recordIndex) => base + recordIndex));
      cellsByKey.set(key, target);
    }
    base += grid.triangles.length;
  }

  return {
    bounds: hitBin.stageBoundsFromHitGrid(first),
    collision: {
      triangles,
      grid: {
        origin: first.header.origin,
        cellSize: first.header.cellSize,
        gridCells: first.header.gridCells,
        cells: [...cellsByKey.values()].sort((a, b) => a.index - b.index),
      },
    },
  };
}

function convertBattleConfig(config, stageId, bounds, collision) {
  return {
    stageId,
    bounds,
    collision,
    timeLimitFrames: config.timeLimitFrames,
    forces: config.forces.map((force) => ({
      team: force.team === "player" ? 0 : 1,
      ownerPlayer: force.ownerPlayer == null ? null : `p${force.ownerPlayer}`,
      borgIds: [...force.borgIds],
    })),
  };
}

function playerInput() {
  const activeUid = battle.state.activeUidByPlayer[PLAYER_ID];
  const self = battle.state.borgs.find((borg) => borg.uid === activeUid);
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
  for (const other of battle.state.borgs) {
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
  for (const borg of battle.state.borgs) {
    if (!Number.isFinite(borg.hp)) throw new Error(`NaN hp on ${borg.uid} at frame ${frame}`);
    if (!Number.isFinite(borg.rotY)) throw new Error(`NaN rotY on ${borg.uid} at frame ${frame}`);
    for (const key of ["x", "y", "z"]) {
      if (!Number.isFinite(borg.pos[key])) throw new Error(`NaN pos.${key} on ${borg.uid} at frame ${frame}`);
      if (!Number.isFinite(borg.vel[key])) throw new Error(`NaN vel.${key} on ${borg.uid} at frame ${frame}`);
    }
  }
  for (const value of Object.values(battle.state.energy)) {
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
