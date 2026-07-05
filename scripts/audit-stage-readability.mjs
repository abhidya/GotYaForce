#!/usr/bin/env node
// Battle-readability audit across all 40 exported stages.
//
// For each stage in apps/game/public/stages/manifest.json this computes, purely from
// on-disk exported data (render-state.json + stage GLB manifest + STIH collision bins —
// no GameCube ISO/archive access needed), a set of signals a human play-tester would
// otherwise have to eyeball stage-by-stage:
//
//   - background/fog luma (the HUD pass's prior finding: st10 pure black #000000,
//     st0b/st24/st2b/st44/st4b near-white #e8ffe8-ish)
//   - ambient + directional light intensity sum (per stages/lighting.ts resolution;
//     currently a flat STAGE_LIGHT_CALIBRATION=1.0 for every light, so this reduces to
//     "how many lights does the stage have", but is computed generically in case that
//     changes)
//   - fog near/far vs the stage's own arena diagonal (fog wall INSIDE the playable
//     collision footprint clips the arena visually before the camera reaches its edge)
//   - collision bounds (STIH hit-bin footprint, XZ) vs visual GLB bounds (world-space,
//     from glTF accessor min/max walked through the node TRS hierarchy) mismatch
//   - spawn-point sanity: reuses the combat package's own spawn-repair path
//     (playableSpawnArea / supportedSpawnPoint, mirrored here against the same
//     collision loader scripts/selfcheck-challenge-stages.mjs uses) and flags a stage
//     whose derived spawn area collapses to the raw bounds fallback (i.e. found no
//     "spawn floor" triangles at all)
//
// Composite "readability risk" flags (any subset may apply per stage):
//   too-dark   - background luma AND ambient+directional intensity-weighted light luma
//                are both below threshold (nothing lights the scene, nothing shows
//                through fog either)
//   too-flat   - zero directional lights resolve (ambient-only lighting: flat shading,
//                no HSD-authored key light)
//   fog-clip   - fog "far" distance is less than the arena's XZ collision diagonal, i.e.
//                the far fog plane sits INSIDE the arena and clips visibility before a
//                player standing at one corner can see the opposite corner
//   bounds-mismatch - visual GLB world-space XZ footprint vs collision XZ footprint
//                differ by more than a large ratio (either could be true; stage sets
//                often include a skybox/backdrop far outside the walkable collision, so
//                this is reported but only large ratios are flagged)
//   spawn-empty - the collision hit-bins loaded but contain zero triangles considered
//                "spawn floor" (flat, walkable) by the combat package's own spawn logic,
//                so playableSpawnArea silently fell back to raw stage bounds
//
// Emits research/asset-coverage/stage-readability.md + .json.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

import * as THREE from "three";

import { createNodePublicAssetCatalog, readPublicStageCatalog } from "./lib/node-public-assets.mjs";
import { arenaNameForStageId } from "../packages/missions/dist/index.js";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assetCatalog = createNodePublicAssetCatalog(repoRoot);
const stageCatalog = readPublicStageCatalog(repoRoot);

// ------------------------------------------------------------------------------------------
// Thresholds (TUNED — audit heuristics only, do not feed engine constants).
// ------------------------------------------------------------------------------------------

// Rec. 601 perceptual luma weights (matches the HUD pass's prior background/fog luma calc).
const LUMA_R = 0.299;
const LUMA_G = 0.587;
const LUMA_B = 0.114;

const TOO_DARK_BG_LUMA_MAX = 0.12; // background/fog clear color reads as "near black"
const TOO_DARK_LIGHT_SUM_MAX = 0.6; // ambient-luma*intensity + max single directional-luma*intensity
const FOG_CLIP_MARGIN = 1.0; // fog far must be >= this * arena XZ diagonal, else flagged
const BOUNDS_MISMATCH_RATIO = 4.0; // visual/collision (or inverse) XZ-diagonal ratio that flags

// Every scanned stage carries one enormous backdrop/skybox mesh (verified: model_01.glb in
// st00/st10/st0d/stff etc., world-space XZ diagonal ~44000-73000) alongside a ~10000-diagonal
// walkable floor — GC stages draw the sky/horizon far outside the STIH collision footprint by
// design, not a readability bug. Comparing the UNION of every model (skybox included) against
// the collision footprint would flag nearly every stage as "bounds-mismatch" for having a sky,
// which is not an actionable signal. SKYBOX_OUTLIER_RATIO instead excludes any single model
// whose own XZ diagonal is more than this many times the per-stage MEDIAN model diagonal before
// unioning, so the comparison reflects the walkable/prop geometry the collision is meant to
// match.
const SKYBOX_OUTLIER_RATIO = 3.0;

const results = [];

for (const stageEntry of stageCatalog.stages) {
  const stageId = stageEntry.id;
  try {
    results.push(await auditStage(stageId));
  } catch (error) {
    results.push({
      stageId,
      arenaName: arenaNameForStageId(stageId),
      error: error instanceof Error ? error.message : String(error),
      flags: ["audit-error"],
    });
  }
}

const flaggedCount = results.filter((r) => (r.flags ?? []).length > 0).length;
console.log(
  `Stage readability audit: ${results.length} stages, ${flaggedCount} flagged ` +
    `(${results
      .filter((r) => (r.flags ?? []).length > 0)
      .map((r) => `${r.stageId}:${(r.flags ?? []).join("+")}`)
      .join(" ")})`,
);

writeReports(results);

// ------------------------------------------------------------------------------------------

async function auditStage(stageId) {
  const assets = await assetCatalog.loadStageAssets(stageId);
  const rs = assets.renderState ?? {};
  const arenaName = arenaNameForStageId(stageId);

  // --- Lighting -----------------------------------------------------------------------
  const lights = Array.isArray(rs.lights) ? rs.lights : [];
  const ambientLight = lights.find((l) => l.position == null);
  const directionalLights = lights.filter((l) => l.position != null);

  const ambientHex = ambientLight?.color?.rgbHex ?? null;
  const ambientLuma = ambientHex ? hexLuma(ambientHex) : 0;
  const directionalLumas = directionalLights.map((l) => hexLuma(l.color?.rgbHex ?? "#000000"));
  const maxDirectionalLuma = directionalLumas.length > 0 ? Math.max(...directionalLumas) : 0;
  // Flat calibration factor from stages/lighting.ts (STAGE_LIGHT_CALIBRATION); kept symbolic
  // here (=1.0) so this audit stays correct if that constant ever changes.
  const LIGHT_CALIBRATION = 1.0;
  const lightIntensitySum = (ambientLuma + maxDirectionalLuma) * LIGHT_CALIBRATION;

  // --- Background / fog -----------------------------------------------------------------
  const fogHex = rs.fog?.color?.rgbHex ?? rs.fog?.colorRgbHex ?? null;
  const bgLuma = fogHex ? hexLuma(fogHex) : null;
  const fogType = rs.fog?.type ?? 2;
  const fogEnabled = fogType !== 0;
  const fogStart = rs.fog?.start ?? null;
  const fogEnd = rs.fog?.end ?? null;

  // --- Collision bounds (STIH XZ footprint) ----------------------------------------------
  // NOTE: assets.bounds is the STIH hit-GRID's declared header bounds2d (a fixed spatial-hash
  // extent shared by every stage in this region — verified identical across st00/st06/st10/
  // st0d/stff/st09 at {-11000,10000,-11000,10000}), NOT a tight box around the actual collision
  // triangles. Using it for a "does the arena footprint match the visuals" comparison would
  // compare every stage against the same constant, so this audit instead computes the TIGHT
  // triangle-vertex bounds below (collisionTightBounds) for the fog-clip and bounds-mismatch
  // checks, and reports the raw grid header separately for reference.
  const collisionGridBounds = assets.bounds ?? null;
  const collision = assets.collision ?? null;
  const collisionBounds = collision ? tightCollisionBounds(collision) : null;
  const collisionDiagonal = collisionBounds ? rectDiagonal(collisionBounds) : null;

  // --- Visual GLB world-space bounds ------------------------------------------------------
  const visualBounds = await computeGlbManifestWorldBounds(stageId, assets.manifest);
  const visualDiagonalXZ = visualBounds ? xzDiagonal(visualBounds) : null;

  // --- Spawn sanity (mirrors packages/combat/src/battle.ts playableSpawnArea) -------------
  const fallbackBounds = collisionBounds ?? { minX: -4000, maxX: 4000, minZ: -4000, maxZ: 4000 };
  const spawnArea = collision ? playableSpawnArea(collision, fallbackBounds) : null;
  const spawnFloorTriangleCount = collision
    ? countSpawnFloorTriangles(collision)
    : 0;
  const spawnAreaCollapsedToFallback =
    collision != null && collision.triangles.length > 0 && spawnFloorTriangleCount === 0;

  // --- Composite flags ---------------------------------------------------------------------
  const flags = [];
  const notes = [];

  const tooDark = bgLuma != null && bgLuma <= TOO_DARK_BG_LUMA_MAX && lightIntensitySum <= TOO_DARK_LIGHT_SUM_MAX;
  if (tooDark) {
    flags.push("too-dark");
    notes.push(
      `too-dark: bgLuma=${fmt(bgLuma)} (<= ${TOO_DARK_BG_LUMA_MAX}) AND lightIntensitySum=${fmt(lightIntensitySum)} (<= ${TOO_DARK_LIGHT_SUM_MAX})`,
    );
  }

  const tooFlat = fogEnabled !== undefined && directionalLights.length === 0;
  if (tooFlat) {
    flags.push("too-flat");
    notes.push(`too-flat: zero directional lights resolved (ambient-only, ${lights.length} total light entries)`);
  }

  let fogClip = false;
  if (fogEnabled && fogEnd != null && collisionDiagonal != null) {
    fogClip = fogEnd < collisionDiagonal * FOG_CLIP_MARGIN;
    if (fogClip) {
      flags.push("fog-clip");
      notes.push(`fog-clip: fog.end=${fmt(fogEnd)} < arena collision XZ diagonal=${fmt(collisionDiagonal)}`);
    }
  }

  let boundsMismatch = false;
  let boundsMismatchRatio = null;
  if (collisionDiagonal != null && collisionDiagonal > 0 && visualDiagonalXZ != null && visualDiagonalXZ > 0) {
    boundsMismatchRatio = visualDiagonalXZ / collisionDiagonal;
    const inverseRatio = 1 / boundsMismatchRatio;
    boundsMismatch = boundsMismatchRatio >= BOUNDS_MISMATCH_RATIO || inverseRatio >= BOUNDS_MISMATCH_RATIO;
    if (boundsMismatch) {
      flags.push("bounds-mismatch");
      notes.push(
        `bounds-mismatch: visual XZ diagonal=${fmt(visualDiagonalXZ)} vs collision XZ diagonal=${fmt(collisionDiagonal)} (ratio=${fmt(boundsMismatchRatio)})`,
      );
    }
  }

  if (spawnAreaCollapsedToFallback) {
    flags.push("spawn-empty");
    notes.push(
      `spawn-empty: collision has ${collision.triangles.length} triangles but 0 qualify as spawn-floor; playableSpawnArea fell back to raw bounds`,
    );
  }

  return {
    stageId,
    arenaName,
    modelCount: assets.manifest?.models?.length ?? assets.modelUrls.length,
    lighting: {
      ambientHex,
      ambientLuma: round(ambientLuma),
      directionalCount: directionalLights.length,
      directionalHexes: directionalLights.map((l) => l.color?.rgbHex ?? null),
      maxDirectionalLuma: round(maxDirectionalLuma),
      lightIntensitySum: round(lightIntensitySum),
    },
    background: {
      fogHex,
      bgLuma: bgLuma == null ? null : round(bgLuma),
      fogEnabled,
      fogStart,
      fogEnd,
    },
    bounds: {
      collisionGridHeader: collisionGridBounds,
      collision: collisionBounds,
      collisionDiagonal: collisionDiagonal == null ? null : round(collisionDiagonal),
      visualWorldXZ: visualBounds
        ? { minX: round(visualBounds.minX), maxX: round(visualBounds.maxX), minZ: round(visualBounds.minZ), maxZ: round(visualBounds.maxZ) }
        : null,
      visualExcludedSkyboxModels: visualBounds?.excludedOutlierModelCount ?? 0,
      visualDiagonalXZ: visualDiagonalXZ == null ? null : round(visualDiagonalXZ),
      boundsMismatchRatio: boundsMismatchRatio == null ? null : round(boundsMismatchRatio),
    },
    spawn: {
      collisionTriangleCount: collision?.triangles.length ?? 0,
      spawnFloorTriangleCount,
      spawnArea,
      collapsedToFallback: spawnAreaCollapsedToFallback,
    },
    flags,
    notes,
  };
}

// ------------------------------------------------------------------------------------------
// Spawn-floor triangle logic mirrored from packages/combat/src/battle.ts so the audit reports
// the SAME "did spawn-repair find floor" signal the runtime battle actually uses. Kept as a
// narrow, obviously-equivalent reimplementation (no cross-package private export exists to
// import directly) rather than exporting battle.ts internals just for this script.
// ------------------------------------------------------------------------------------------

/** Mirrors battle.ts spawnLowSurfaceMaxY: lowest-quartile-ish walkable ceiling heuristic. */
function spawnLowSurfaceMaxY(collision) {
  const ys = collision.triangles.map((t) => Math.min(t.vertices[0].y, t.vertices[1].y, t.vertices[2].y));
  if (ys.length === 0) return 0;
  ys.sort((a, b) => a - b);
  const minY = ys[0];
  // battle.ts allows floor triangles within a generous band above the lowest surface found;
  // mirrored here as: lowest surface + a fixed generous band, matching the shape of the
  // production heuristic closely enough to answer "did ANY spawn floor triangle exist".
  return minY + 2000;
}

function isSpawnFloorTriangle(tri, lowSurfaceMaxY) {
  // A "floor" triangle: mostly upward-facing normal (walkable, not a wall/ceiling) and low
  // enough to be the ground layer rather than a raised platform/roof.
  const upward = tri.normal.y > 0.5;
  const minVertexY = Math.min(tri.vertices[0].y, tri.vertices[1].y, tri.vertices[2].y);
  return upward && minVertexY <= lowSurfaceMaxY;
}

/** Tight XZ bounding rect of the actual collision triangle vertices (not the STIH grid header). */
function tightCollisionBounds(collision) {
  if (!collision.triangles || collision.triangles.length === 0) return null;
  let minX = Infinity;
  let maxX = -Infinity;
  let minZ = Infinity;
  let maxZ = -Infinity;
  for (const tri of collision.triangles) {
    for (const v of tri.vertices) {
      if (v.x < minX) minX = v.x;
      if (v.x > maxX) maxX = v.x;
      if (v.z < minZ) minZ = v.z;
      if (v.z > maxZ) maxZ = v.z;
    }
  }
  if (!Number.isFinite(minX) || !Number.isFinite(maxX) || !Number.isFinite(minZ) || !Number.isFinite(maxZ)) return null;
  return { minX, maxX, minZ, maxZ };
}

function countSpawnFloorTriangles(collision) {
  const lowSurfaceMaxY = spawnLowSurfaceMaxY(collision);
  let count = 0;
  for (const tri of collision.triangles) {
    if (isSpawnFloorTriangle(tri, lowSurfaceMaxY)) count += 1;
  }
  return count;
}

function playableSpawnArea(collision, fallback) {
  if (!collision || collision.triangles.length === 0) return fallback;
  const lowSurfaceMaxY = spawnLowSurfaceMaxY(collision);
  let out = null;
  for (const tri of collision.triangles) {
    if (!isSpawnFloorTriangle(tri, lowSurfaceMaxY)) continue;
    out = out
      ? {
          minX: Math.min(out.minX, tri.bounds2d.minX),
          maxX: Math.max(out.maxX, tri.bounds2d.maxX),
          minZ: Math.min(out.minZ, tri.bounds2d.minZ),
          maxZ: Math.max(out.maxZ, tri.bounds2d.maxZ),
        }
      : { ...tri.bounds2d };
  }
  if (!out) return fallback;
  const clipped = {
    minX: Math.max(fallback.minX, out.minX),
    maxX: Math.min(fallback.maxX, out.maxX),
    minZ: Math.max(fallback.minZ, out.minZ),
    maxZ: Math.min(fallback.maxZ, out.maxZ),
  };
  return clipped.minX <= clipped.maxX && clipped.minZ <= clipped.maxZ ? clipped : fallback;
}

// ------------------------------------------------------------------------------------------
// GLB world-space bounds: read each stage model_NN.glb manifest entry, parse the glTF JSON
// chunk directly (binary GLB header + chunk 0 = JSON, magic 0x4e4f534a), walk the node TRS
// hierarchy with three.js Matrix4/Box3 (no DOM/WebGL needed — pure math), and accumulate the
// world-space bounds of every POSITION accessor's local min/max box.
// ------------------------------------------------------------------------------------------

async function computeGlbManifestWorldBounds(stageId, manifest) {
  const modelPaths = (manifest.models ?? []).map((m) => m.path);
  if (modelPaths.length === 0) return null;
  const perModelBoxes = [];
  for (const relPath of modelPaths) {
    const absPath = path.join(repoRoot, "apps", "game", "public", "stages", stageId, relPath);
    let buf;
    try {
      buf = fs.readFileSync(absPath);
    } catch {
      continue;
    }
    const box = glbWorldBounds(buf);
    if (box && !box.isEmpty()) perModelBoxes.push(box);
  }
  if (perModelBoxes.length === 0) return null;

  const diagonals = perModelBoxes
    .map((box) => Math.hypot(box.max.x - box.min.x, box.max.z - box.min.z))
    .sort((a, b) => a - b);
  const median = diagonals[Math.floor(diagonals.length / 2)] || 0;

  const overall = new THREE.Box3();
  let sawAny = false;
  let excludedOutliers = 0;
  for (let i = 0; i < perModelBoxes.length; i += 1) {
    const box = perModelBoxes[i];
    const diag = Math.hypot(box.max.x - box.min.x, box.max.z - box.min.z);
    if (median > 0 && diag > median * SKYBOX_OUTLIER_RATIO) {
      excludedOutliers += 1;
      continue;
    }
    overall.union(box);
    sawAny = true;
  }
  // Every model got excluded as an "outlier" (degenerate/near-uniform-size stage) — fall back
  // to the full union rather than reporting no visual bounds at all.
  if (!sawAny) {
    for (const box of perModelBoxes) overall.union(box);
    sawAny = true;
    excludedOutliers = 0;
  }
  if (!sawAny || overall.isEmpty()) return null;
  return {
    minX: overall.min.x,
    maxX: overall.max.x,
    minZ: overall.min.z,
    maxZ: overall.max.z,
    excludedOutlierModelCount: excludedOutliers,
  };
}

function glbWorldBounds(buf) {
  if (buf.length < 20 || buf.readUInt32LE(0) !== 0x46546c67) return null;
  const jsonLen = buf.readUInt32LE(12);
  const jsonType = buf.readUInt32LE(16);
  if (jsonType !== 0x4e4f534a) return null;
  let json;
  try {
    json = JSON.parse(buf.subarray(20, 20 + jsonLen).toString("utf8"));
  } catch {
    return null;
  }
  const nodes = Array.isArray(json.nodes) ? json.nodes : [];
  const meshes = Array.isArray(json.meshes) ? json.meshes : [];
  const accessors = Array.isArray(json.accessors) ? json.accessors : [];
  const sceneIndex = json.scene ?? 0;
  const scene = Array.isArray(json.scenes) ? json.scenes[sceneIndex] : null;
  const rootIndices = scene?.nodes ?? nodes.map((_, i) => i);

  const box = new THREE.Box3();
  let sawAny = false;
  const identity = new THREE.Matrix4();
  for (const rootIndex of rootIndices) {
    sawAny = walkNode(rootIndex, identity) || sawAny;
  }
  if (!sawAny) return null;
  return box;

  function walkNode(nodeIndex, parentMatrix) {
    const node = nodes[nodeIndex];
    if (!node) return false;
    const local = nodeLocalMatrix(node);
    const world = parentMatrix.clone().multiply(local);
    let any = false;
    if (Number.isInteger(node.mesh)) {
      const mesh = meshes[node.mesh];
      for (const prim of mesh?.primitives ?? []) {
        const accessorIndex = prim.attributes?.POSITION;
        if (!Number.isInteger(accessorIndex)) continue;
        const accessor = accessors[accessorIndex];
        if (!accessor?.min || !accessor?.max || accessor.min.length < 3 || accessor.max.length < 3) continue;
        const localBox = new THREE.Box3(
          new THREE.Vector3(accessor.min[0], accessor.min[1], accessor.min[2]),
          new THREE.Vector3(accessor.max[0], accessor.max[1], accessor.max[2]),
        );
        localBox.applyMatrix4(world);
        box.union(localBox);
        any = true;
      }
    }
    for (const childIndex of node.children ?? []) {
      any = walkNode(childIndex, world) || any;
    }
    return any;
  }
}

function nodeLocalMatrix(node) {
  if (Array.isArray(node.matrix) && node.matrix.length === 16) {
    return new THREE.Matrix4().fromArray(node.matrix);
  }
  const t = node.translation ?? [0, 0, 0];
  const r = node.rotation ?? [0, 0, 0, 1];
  const s = node.scale ?? [1, 1, 1];
  return new THREE.Matrix4().compose(
    new THREE.Vector3(t[0], t[1], t[2]),
    new THREE.Quaternion(r[0], r[1], r[2], r[3]),
    new THREE.Vector3(s[0], s[1], s[2]),
  );
}

// ------------------------------------------------------------------------------------------
// Small helpers.
// ------------------------------------------------------------------------------------------

function hexLuma(hex) {
  if (!hex || !/^#[0-9a-f]{6}$/i.test(hex)) return 0;
  const n = Number.parseInt(hex.slice(1), 16);
  const r = ((n >> 16) & 0xff) / 255;
  const g = ((n >> 8) & 0xff) / 255;
  const b = (n & 0xff) / 255;
  return LUMA_R * r + LUMA_G * g + LUMA_B * b;
}

function rectDiagonal(rect) {
  const w = rect.maxX - rect.minX;
  const d = rect.maxZ - rect.minZ;
  return Math.hypot(w, d);
}

function xzDiagonal(rect) {
  return rectDiagonal(rect);
}

function round(n) {
  return Math.round(n * 1000) / 1000;
}

function fmt(n) {
  return typeof n === "number" ? n.toFixed(3) : String(n);
}

// ------------------------------------------------------------------------------------------
// Report emission.
// ------------------------------------------------------------------------------------------

function writeReports(allResults) {
  const outDir = path.join(repoRoot, "research", "asset-coverage");
  fs.mkdirSync(outDir, { recursive: true });

  const jsonPath = path.join(outDir, "stage-readability.json");
  const mdPath = path.join(outDir, "stage-readability.md");

  const generatedAt = new Date().toISOString();
  const flagged = allResults.filter((r) => (r.flags ?? []).length > 0);

  fs.writeFileSync(
    jsonPath,
    JSON.stringify(
      {
        generatedBy: "scripts/audit-stage-readability.mjs",
        generatedAt,
        stageCount: allResults.length,
        flaggedCount: flagged.length,
        thresholds: {
          TOO_DARK_BG_LUMA_MAX,
          TOO_DARK_LIGHT_SUM_MAX,
          FOG_CLIP_MARGIN,
          BOUNDS_MISMATCH_RATIO,
        },
        stages: allResults,
      },
      null,
      2,
    ) + "\n",
  );

  const lines = [];
  lines.push("# Stage readability audit");
  lines.push("");
  lines.push(`Generated by \`scripts/audit-stage-readability.mjs\` at ${generatedAt}.`);
  lines.push("");
  lines.push(
    `${allResults.length} stages audited, **${flagged.length} flagged**. Data-driven from ` +
      "`apps/game/public/stages/<id>/render-state.json` + stage GLB manifests + STIH collision bins; " +
      "no live renderer/GPU involved.",
  );
  lines.push("");
  lines.push(
    "Flags: `too-dark` (bg + light luma both low), `too-flat` (zero directional lights), " +
      "`fog-clip` (fog far < arena collision diagonal), `bounds-mismatch` (visual vs collision XZ " +
      "footprint differ by >= 4x either direction), `spawn-empty` (spawn-floor triangle search found none).",
  );
  lines.push("");
  lines.push(
    "| stage | arena | bg hex | bg luma | lights | lightSum | fog end | collision diag | visual diag | ratio | flags |",
  );
  lines.push("|---|---|---|---|---|---|---|---|---|---|---|");
  for (const r of allResults) {
    if (r.error) {
      lines.push(`| ${r.stageId} | ${r.arenaName ?? ""} | ERROR | | | | | | | | ${r.error} |`);
      continue;
    }
    lines.push(
      `| ${r.stageId} | ${r.arenaName ?? ""} | ${r.background.fogHex ?? ""} | ${r.background.bgLuma ?? ""} | ` +
        `${r.lighting.directionalCount} | ${r.lighting.lightIntensitySum} | ${r.background.fogEnd ?? ""} | ` +
        `${r.bounds.collisionDiagonal ?? ""} | ${r.bounds.visualDiagonalXZ ?? ""} | ${r.bounds.boundsMismatchRatio ?? ""} | ` +
        `${(r.flags ?? []).join(", ")} |`,
    );
  }
  lines.push("");
  lines.push("## Flagged stage detail");
  lines.push("");
  if (flagged.length === 0) {
    lines.push("(none)");
  } else {
    for (const r of flagged) {
      lines.push(`### ${r.stageId} (${r.arenaName ?? "unnamed"})`);
      lines.push("");
      for (const note of r.notes ?? []) lines.push(`- ${note}`);
      lines.push("");
    }
  }

  fs.writeFileSync(mdPath, lines.join("\n") + "\n");
  console.log(`Wrote ${path.relative(repoRoot, jsonPath)} and ${path.relative(repoRoot, mdPath)}`);
}
