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
  CHALLENGE_STAGE_BYTES,
  STAGE_ARENA_NAMES,
  arenaNameForStageByte,
  arenaNameForStageId,
} from "../packages/missions/dist/index.js";
import { createNodePublicAssetCatalog, readPublicStageCatalog } from "./lib/node-public-assets.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assetCatalog = createNodePublicAssetCatalog(repoRoot);
const FRAMES_PER_STAGE = 1200;
const GROUND_SNAP_UP = 35;

const borgs = readJson("packages/assets/data/borgs.json").borgs;
const stageCatalog = readPublicStageCatalog(repoRoot);
const officialChallengeStageIds = [...new Set(CHALLENGE_STAGE_BYTES.map((byte) => `st${byte.toString(16).padStart(2, "0")}`))];

const summaries = [];
for (const stageId of officialChallengeStageIds) {
  const stage = await loadStageResources(stageId);
  const battle = createBattle(
    {
      stageId,
      bounds: stage.bounds,
      collision: stage.collision,
      timeLimitFrames: FRAMES_PER_STAGE,
      forces: [
        { team: 0, ownerPlayer: "p0", borgIds: ["pl0615"] },
        { team: 0, ownerPlayer: null, borgIds: ["pl020a"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008", "pl000c"] },
      ],
    },
    borgs,
  );

  let firstEnergyChangeFrame = -1;
  const startEnergy = { ...battle.state.energy };
  for (let frame = 0; frame < FRAMES_PER_STAGE && battle.state.result === "ongoing"; frame += 1) {
    battle.step(1 / 60, { p0: playerInput(battle) });
    assertSaneStage(stageId, stage, battle, frame);
    if (firstEnergyChangeFrame < 0 && energyChanged(startEnergy, battle.state.energy)) {
      firstEnergyChangeFrame = frame;
    }
  }
  summaries.push({
    stageId,
    triangles: stage.collision.triangles.length,
    frames: battle.state.frame,
    result: battle.state.result,
    firstEnergyChangeFrame,
  });
}

console.log(
  `Challenge stage collision smoke PASS stages=${summaries.length} framesPerStage=${FRAMES_PER_STAGE} ` +
    summaries
      .map((s) => `${s.stageId}:tri=${s.triangles}:frames=${s.frames}:energyFrame=${s.firstEnergyChangeFrame}`)
      .join(" "),
);

// DERIVED — research/decomp/challenge-stage-naming-2026-07-05.md section 1.2:
// [0x1d] (Challenge rand%3) selects the st0x/st2x/st4x archive family for
// outdoor arenas. Spot-check that a st2x AND a st4x family variant actually
// resolve exported assets and load real (non-degenerate) collision, the same
// way the base st0x stages above did.
const familyVariantSummaries = [];
for (const stageId of ["st2c", "st4c"]) {
  const stage = await loadStageResources(stageId);
  if (stage.collision.triangles.length <= 0) {
    throw new Error(`family-variant stage ${stageId} loaded zero collision triangles`);
  }
  const battle = createBattle(
    {
      stageId,
      bounds: stage.bounds,
      collision: stage.collision,
      timeLimitFrames: FRAMES_PER_STAGE,
      forces: [
        { team: 0, ownerPlayer: "p0", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0008"] },
      ],
    },
    borgs,
  );
  for (let frame = 0; frame < 120 && battle.state.result === "ongoing"; frame += 1) {
    battle.step(1 / 60, { p0: playerInput(battle) });
    assertSaneStage(stageId, stage, battle, frame);
  }
  familyVariantSummaries.push({ stageId, triangles: stage.collision.triangles.length, frames: battle.state.frame });
}
console.log(
  `Challenge stage FAMILY VARIANT smoke PASS ` +
    familyVariantSummaries.map((s) => `${s.stageId}:tri=${s.triangles}:frames=${s.frames}`).join(" "),
);

// DERIVED — every challenge-pool stage byte must resolve an authentic arena
// name (research/decomp/challenge-stage-naming-2026-07-05.md section 2.4),
// and family-variant st## ids (st2x/st4x) must share their base byte's name.
for (const stageByte of CHALLENGE_STAGE_BYTES) {
  const name = arenaNameForStageByte(stageByte);
  if (typeof name !== "string" || name.length === 0) {
    throw new Error(`challenge-pool stage byte 0x${stageByte.toString(16)} has no arena name`);
  }
}
if (Object.keys(STAGE_ARENA_NAMES).length !== 18) {
  throw new Error(`expected 18 authentic arena names, found ${Object.keys(STAGE_ARENA_NAMES).length}`);
}
if (arenaNameForStageId("st2c") !== arenaNameForStageByte(0x0c) || arenaNameForStageId("st4c") !== arenaNameForStageByte(0x0c)) {
  throw new Error("st2c/st4c family variants must share st0c's arena name (LITTLE HILL)");
}
console.log(`Challenge arena name coverage PASS names=${Object.keys(STAGE_ARENA_NAMES).length} pool=${CHALLENGE_STAGE_BYTES.length}`);

function playerInput(battle) {
  const activeUid = battle.state.activeUidByPlayer.p0;
  const self = battle.state.borgs.find((borg) => borg.uid === activeUid);
  if (!self) return emptyInput();
  const target = nearestEnemy(battle, self);
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

function nearestEnemy(battle, self) {
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

function assertSaneStage(stageId, stage, battle, frame) {
  for (const borg of battle.state.borgs) {
    if (!Number.isFinite(borg.hp)) throw new Error(`${stageId}: NaN hp on ${borg.uid} at frame ${frame}`);
    for (const key of ["x", "y", "z"]) {
      if (!Number.isFinite(borg.pos[key])) throw new Error(`${stageId}: NaN pos.${key} on ${borg.uid} at frame ${frame}`);
      if (!Number.isFinite(borg.vel[key])) throw new Error(`${stageId}: NaN vel.${key} on ${borg.uid} at frame ${frame}`);
    }
    const floorY = floorSurfaceYAt(stage.collision, borg.pos.x, borg.pos.z, borg.pos.y - JUMP.GROUND_Y + GROUND_SNAP_UP);
    if (floorY == null) {
      throw new Error(`${stageId}: ${borg.uid} left supported floor at frame ${frame} pos=${JSON.stringify(borg.pos)}`);
    }
  }
  for (const value of Object.values(battle.state.energy)) {
    if (!Number.isFinite(value)) throw new Error(`${stageId}: NaN team energy at frame ${frame}`);
  }
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
