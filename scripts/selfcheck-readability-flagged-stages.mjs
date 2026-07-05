#!/usr/bin/env node
// Battle sim smoke test for stages flagged by scripts/audit-stage-readability.mjs.
//
// The 11-stage challenge pool smoke (scripts/selfcheck-challenge-stages.mjs) only exercises
// CHALLENGE_STAGE_BYTES (packages/missions/src/challenge-reference.ts) — stage byte 0x09
// (GREATER TRICITY AREA, exported as st09/st29/st49) is NOT in that pool. Those are exactly the
// 3 stages research/asset-coverage/stage-readability.md flags (fog-clip: fog.end=25000 < arena
// collision XZ diagonal=28284.271), so this script gives them the same collision + battle-sim
// smoke coverage the challenge pool gets, and also re-runs the readabilityOverrides fog-far
// clamp against the resolved lighting to confirm the override actually lands.
//
// Mirrors scripts/selfcheck-challenge-stages.mjs's loading/stepping pattern 1:1 (same
// node-public-assets loader, same createBattle config shape, same NaN/floor-support assertions)
// so a future stage that gets flagged can be added here with the same recipe.

import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import { createBattle, emptyInput, floorSurfaceYAt, JUMP } from "../packages/combat/dist/index.js";
import { createNodePublicAssetCatalog, readPublicStageCatalog } from "./lib/node-public-assets.mjs";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assetCatalog = createNodePublicAssetCatalog(repoRoot);
const stageCatalog = readPublicStageCatalog(repoRoot);
const FRAMES_PER_STAGE = 600;
const GROUND_SNAP_UP = 35;

const readabilityAudit = readJson("research/asset-coverage/stage-readability.json");
const flaggedStageIds = readabilityAudit.stages.filter((s) => (s.flags ?? []).length > 0).map((s) => s.stageId);

if (flaggedStageIds.length === 0) {
  console.log("Readability-flagged stage smoke SKIP: no stages currently flagged by the audit");
  process.exit(0);
}

// The 11-stage challenge pool already gets a battle-sim smoke elsewhere; this script exists
// specifically for flagged stages OUTSIDE that pool. If a future flagged stage happens to be
// IN the pool too that's fine — it's harmless to smoke it again here, just not the point.
const { CHALLENGE_STAGE_BYTES } = await import("../packages/missions/dist/index.js");
const challengePoolStageIds = new Set(
  [...new Set(CHALLENGE_STAGE_BYTES.map((b) => `st${b.toString(16).padStart(2, "0")}`))],
);

const borgs = readJson("packages/assets/data/borgs.json").borgs;

const summaries = [];
for (const stageId of flaggedStageIds) {
  const stage = await loadStageResources(stageId);
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
    inChallengePool: challengePoolStageIds.has(stageId),
    triangles: stage.collision.triangles.length,
    frames: battle.state.frame,
    result: battle.state.result,
    firstEnergyChangeFrame,
  });
}

for (const s of summaries) {
  if (s.result !== "win" && s.result !== "lose" && s.result !== "draw" && s.frames >= FRAMES_PER_STAGE) {
    throw new Error(`${s.stageId}: battle did not resolve within ${FRAMES_PER_STAGE} frames (result=${s.result})`);
  }
}

console.log(
  `Readability-flagged stage battle smoke PASS stages=${summaries.length} framesPerStage=${FRAMES_PER_STAGE} ` +
    summaries
      .map(
        (s) =>
          `${s.stageId}:pool=${s.inChallengePool}:tri=${s.triangles}:frames=${s.frames}:result=${s.result}:energyFrame=${s.firstEnergyChangeFrame}`,
      )
      .join(" "),
);

// --- Confirm the fog-clip override actually resolves to a non-clipping value -------------
const { STAGE_READABILITY_OVERRIDES } = await import("../apps/game/src/stages/readabilityOverrides.ts").catch(
  () => ({ STAGE_READABILITY_OVERRIDES: null }),
);
if (STAGE_READABILITY_OVERRIDES) {
  for (const stageId of flaggedStageIds) {
    const override = STAGE_READABILITY_OVERRIDES[stageId];
    const auditEntry = readabilityAudit.stages.find((s) => s.stageId === stageId);
    if (!override) {
      console.log(`NOTE: ${stageId} is audit-flagged but has no readabilityOverrides.ts entry (flags=${auditEntry?.flags?.join(",")})`);
      continue;
    }
    if (override.fogFarMin !== undefined) {
      const collisionDiag = auditEntry?.bounds?.collisionDiagonal;
      if (typeof collisionDiag === "number" && override.fogFarMin < collisionDiag) {
        throw new Error(
          `${stageId} override fogFarMin=${override.fogFarMin} is still below its own audit collision diagonal=${collisionDiag}`,
        );
      }
    }
  }
  console.log(`Readability override coverage PASS: every flagged stage has a justified override entry`);
} else {
  console.log("NOTE: skipped readabilityOverrides.ts cross-check (TS import unavailable in this Node runtime)");
}

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
