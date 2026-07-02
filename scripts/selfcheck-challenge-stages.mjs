#!/usr/bin/env node
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import { createBattle, emptyInput, JUMP } from "../packages/combat/dist/index.js";
import { hitBin } from "../packages/formats/dist/index.js";
import { CHALLENGE_STAGE_BYTES } from "../packages/missions/dist/index.js";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const FRAMES_PER_STAGE = 1200;
const GROUND_SNAP_UP = 35;

const borgs = readJson("packages/assets/data/borgs.json").borgs;
const stageCatalog = readJson("apps/game/public/stages/manifest.json");
const officialChallengeStageIds = [...new Set(CHALLENGE_STAGE_BYTES.map((byte) => `st${byte.toString(16).padStart(2, "0")}`))];

const summaries = [];
for (const stageId of officialChallengeStageIds) {
  const stage = loadStageResources(stageId);
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

function loadStageResources(stageId) {
  const exportedStage = stageCatalog.stages.find((stage) => stage.id === stageId);
  if (!exportedStage) throw new Error(`stage ${stageId} is not in public stage catalog`);
  if (exportedStage.collisionCount <= 0) throw new Error(`stage ${stageId} has no cataloged collision bins`);

  const manifest = readJson(`apps/game/public/stages/${stageId}/manifest.json`);
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
      const target = cellsByKey.get(key) ?? { index: cell.index, triangleIndices: [] };
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

function floorSurfaceYAt(collision, x, z, maxSurfaceY) {
  const primary = candidateTriangles(collision, x, z);
  const primaryBest = bestFloorFromCandidates(primary, x, z, maxSurfaceY);
  if (primaryBest != null || primary.length === collision.triangles.length) return primaryBest;
  return bestFloorFromCandidates(collision.triangles, x, z, maxSurfaceY);
}

function candidateTriangles(collision, x, z) {
  const grid = collision.grid;
  if (!grid) return collision.triangles;
  const cx = Math.floor((x - grid.origin.x) / grid.cellSize.x);
  const cz = Math.floor((z - grid.origin.z) / grid.cellSize.z);
  if (cx < 0 || cz < 0 || cx >= grid.gridCells.x || cz >= grid.gridCells.z) return [];
  const cell = grid.cells[cz * grid.gridCells.x + cx];
  if (!cell || cell.triangleIndices.length === 0) return [];
  const out = [];
  for (const index of cell.triangleIndices) {
    const tri = collision.triangles[index];
    if (tri) out.push(tri);
  }
  return out;
}

function bestFloorFromCandidates(triangles, x, z, maxSurfaceY) {
  let best = null;
  for (const tri of triangles) {
    if (tri.marker !== 0xcccccccc) continue;
    if (!isFiniteVec(tri.normal) || tri.normal.y < 0.5) continue;
    if (!tri.vertices.every(isFiniteVec)) continue;
    if (x < tri.bounds2d.minX || x > tri.bounds2d.maxX || z < tri.bounds2d.minZ || z > tri.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y == null || y > maxSurfaceY) continue;
    if (best == null || y > best) best = y;
  }
  return best;
}

function yAtTriangleXZ(tri, x, z) {
  const [a, b, c] = tri.vertices;
  const denom = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
  if (Math.abs(denom) < 1e-5) return null;
  const wa = ((b.z - c.z) * (x - c.x) + (c.x - b.x) * (z - c.z)) / denom;
  const wb = ((c.z - a.z) * (x - c.x) + (a.x - c.x) * (z - c.z)) / denom;
  const wc = 1 - wa - wb;
  if (wa < -1e-4 || wb < -1e-4 || wc < -1e-4) return null;
  return wa * a.y + wb * b.y + wc * c.y;
}

function isFiniteVec(v) {
  return Number.isFinite(v.x) && Number.isFinite(v.y) && Number.isFinite(v.z);
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
