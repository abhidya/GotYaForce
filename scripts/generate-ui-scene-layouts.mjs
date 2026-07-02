#!/usr/bin/env node
import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  manifest: "apps/game/public/ui/scenes/manifest.json",
  output: "apps/game/src/ui/layout.generated.ts",
};

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

function round(value, places = 3) {
  return Number.isFinite(value) ? Number(value.toFixed(places)) : value;
}

function emptyBounds() {
  return {
    minX: Infinity,
    maxX: -Infinity,
    minY: Infinity,
    maxY: -Infinity,
    minZ: Infinity,
    maxZ: -Infinity,
  };
}

function includePoint(bounds, x, y, z) {
  bounds.minX = Math.min(bounds.minX, x);
  bounds.maxX = Math.max(bounds.maxX, x);
  bounds.minY = Math.min(bounds.minY, y);
  bounds.maxY = Math.max(bounds.maxY, y);
  bounds.minZ = Math.min(bounds.minZ, z);
  bounds.maxZ = Math.max(bounds.maxZ, z);
}

function includeBounds(bounds, other) {
  includePoint(bounds, other.minX, other.minY, other.minZ);
  includePoint(bounds, other.maxX, other.maxY, other.maxZ);
}

function finalizeBounds(bounds) {
  if (!Number.isFinite(bounds.minX)) {
    return { minX: 0, maxX: 1, minY: 0, maxY: 1, minZ: 0, maxZ: 1 };
  }
  return Object.fromEntries(Object.entries(bounds).map(([key, value]) => [key, round(value)]));
}

function parsePositionBounds(daeText) {
  const bounds = emptyBounds();
  const regex = /<float_array\b[^>]*id="[^"]*POSITION-array"[^>]*>([\s\S]*?)<\/float_array>/g;
  let match;
  while ((match = regex.exec(daeText))) {
    const values = match[1].trim().split(/\s+/).map(Number);
    for (let i = 0; i + 2 < values.length; i += 3) {
      const x = values[i];
      const y = values[i + 1];
      const z = values[i + 2];
      if (Number.isFinite(x) && Number.isFinite(y) && Number.isFinite(z)) {
        includePoint(bounds, x, y, z);
      }
    }
  }
  return finalizeBounds(bounds);
}

function rectFromBounds(bounds, sceneBounds, verticalAxis) {
  const horizontalSpan = Math.max(1, sceneBounds.maxX - sceneBounds.minX);
  const verticalMin = verticalAxis === "y" ? sceneBounds.minY : sceneBounds.minZ;
  const verticalMax = verticalAxis === "y" ? sceneBounds.maxY : sceneBounds.maxZ;
  const boundsVerticalMin = verticalAxis === "y" ? bounds.minY : bounds.minZ;
  const boundsVerticalMax = verticalAxis === "y" ? bounds.maxY : bounds.maxZ;
  const verticalSpan = Math.max(1, verticalMax - verticalMin);
  const left = ((bounds.minX - sceneBounds.minX) / horizontalSpan) * 100;
  const right = ((bounds.maxX - sceneBounds.minX) / horizontalSpan) * 100;
  const top = (1 - (boundsVerticalMax - verticalMin) / verticalSpan) * 100;
  const bottom = (1 - (boundsVerticalMin - verticalMin) / verticalSpan) * 100;
  return {
    left: round(left),
    top: round(top),
    width: round(Math.max(0.001, right - left)),
    height: round(Math.max(0.001, bottom - top)),
    centerX: round((left + right) / 2),
    centerY: round((top + bottom) / 2),
  };
}

function inflateRect(rect, scaleX, scaleY = scaleX) {
  const width = rect.width * scaleX;
  const height = rect.height * scaleY;
  return {
    left: round(rect.centerX - width / 2),
    top: round(rect.centerY - height / 2),
    width: round(width),
    height: round(height),
    centerX: rect.centerX,
    centerY: rect.centerY,
  };
}

function makeVselDifficultyAnchors(elements) {
  const candidates = elements
    .filter((element) => element.key !== "model_00")
    .filter((element) => element.rectXY.centerY > 46)
    .filter((element) => element.rectXY.width > 2 && element.rectXY.height > 2)
    .sort((a, b) => b.rectXY.width * b.rectXY.height - a.rectXY.width * a.rectXY.height)
    .slice(0, 8)
    .sort((a, b) => {
      const centerDelta = Math.abs(a.rectXY.centerY - 64) - Math.abs(b.rectXY.centerY - 64);
      if (Math.abs(centerDelta) > 4) return centerDelta;
      return a.rectXY.centerX - b.rectXY.centerX;
    })
    .slice(0, 3)
    .sort((a, b) => a.rectXY.centerX - b.rectXY.centerX);

  if (candidates.length !== 3) return null;

  return {
    caveat:
      "Semantic names are inferred from vsel00 lower-scene object order; DAE nodes are generic JOBJ/model labels.",
    normal: inflateRect(candidates[0].rectXY, 1.18, 1.1),
    tuff: inflateRect(candidates[1].rectXY, 1.18, 1.1),
    insane: inflateRect(candidates[2].rectXY, 1.18, 1.1),
    sourceModels: candidates.map((candidate) => candidate.key),
  };
}

function makeEntrySelectForceAnchors(elements) {
  const byModel = new Map(elements.map((element) => [path.basename(element.modelPath), element]));
  const platformSource = byModel.get("model_05.dae") ?? byModel.get("model_24.dae");
  const titleSource = byModel.get("model_03.dae");
  if (!platformSource) return null;

  const platformRect = platformSource.rectXY;
  const titleRect = titleSource?.rectXY ?? null;
  return {
    caveat:
      "Semantic names are inferred from entry00 model file roles; DAE nodes are generic JOBJ/model labels.",
    platform: {
      left: platformRect.centerX,
      top: platformRect.centerY,
      width: round(Math.min(45, Math.max(34, platformRect.width * 0.55))),
      height: round(Math.min(20, Math.max(14, platformRect.height * 0.34))),
    },
    title: titleRect ? inflateRect(titleRect, 1.06, 1.16) : null,
    sourceModels: [platformSource.key, ...(titleSource ? [titleSource.key] : [])],
  };
}

async function buildScene(asset) {
  const modelFiles = asset.modelFiles ?? [];
  const sceneBounds = emptyBounds();
  const rawElements = [];

  for (const [index, model] of modelFiles.entries()) {
    const file = abs(model.path);
    const text = await fs.readFile(file, "utf8");
    const bounds = parsePositionBounds(text);
    includeBounds(sceneBounds, bounds);
    rawElements.push({
      key: `model_${String(index).padStart(2, "0")}`,
      modelPath: model.path,
      publicPath: model.publicPath,
      bounds,
    });
  }

  const finalSceneBounds = finalizeBounds(sceneBounds);
  const elements = rawElements.map((element) => ({
    ...element,
    rectXZ: rectFromBounds(element.bounds, finalSceneBounds, "z"),
    rectXY: rectFromBounds(element.bounds, finalSceneBounds, "y"),
  }));

  const semantics = {};
  if (asset.id === "vsel00") {
    const difficulty = makeVselDifficultyAnchors(elements);
    if (difficulty) semantics.difficulty = difficulty;
  }
  if (asset.id === "entry00") {
    const selectForce = makeEntrySelectForceAnchors(elements);
    if (selectForce) semantics.selectForce = selectForce;
  }

  return {
    sceneId: asset.id,
    sourceArchive: asset.sourceArchive?.sourcePath ?? null,
    modelCount: elements.length,
    bounds: finalSceneBounds,
    elements,
    semantics,
  };
}

function renderModule(layouts) {
  const banner = `// Generated by scripts/generate-ui-scene-layouts.mjs from apps/game/public/ui/scenes/manifest.json.\n// Do not hand-edit; rerun the generator after updating UI scene exports.\n`;
  return `${banner}\nexport const UI_SCENE_LAYOUTS = ${JSON.stringify(layouts, null, 2)} as const;\n\nexport type UiSceneLayouts = typeof UI_SCENE_LAYOUTS;\n`;
}

async function main() {
  const manifest = JSON.parse(await fs.readFile(abs(paths.manifest), "utf8"));
  const exported = (manifest.assets ?? []).filter((asset) => asset.status === "exported" && asset.kind === "ui-scene-model");
  const layouts = {};
  for (const asset of exported) {
    layouts[asset.id] = await buildScene(asset);
  }
  await fs.writeFile(abs(paths.output), renderModule(layouts), "utf8");
  console.log(`wrote ${paths.output}`);
  console.log(`scenes: ${Object.keys(layouts).join(", ")}`);
  const vsel = layouts.vsel00?.semantics?.difficulty;
  if (vsel) console.log(`vsel00 difficulty source models: ${vsel.sourceModels.join(", ")}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
