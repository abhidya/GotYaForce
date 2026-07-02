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
  // The vsel00 export stacks every pad/gear object at the scene X-center: the
  // per-difficulty placement lives on empty JOBJ joint nodes whose transforms the
  // DAE geometry nodes never reference, so three distinct pad positions do NOT
  // exist in the extracted geometry. The only defensible anchor is the option
  // stage (the large pad ellipse) that the difficulty tiles sit on: the biggest
  // foreground element (near-depth, below the header billboard band).
  const stage = elements
    .filter((element) => element.bounds.maxZ > -2000)
    .filter((element) => element.rectXY.centerY > 40)
    .filter((element) => element.rectXY.width < 40)
    .sort((a, b) => b.rectXY.width * b.rectXY.height - a.rectXY.width * a.rectXY.height)[0];
  if (!stage) return null;

  return {
    caveat:
      "vsel00 exports stack the pad/gear objects at the scene X-center (their placement transforms sit on empty JOBJ joints the geometry nodes never instance), so per-difficulty X offsets are NOT derivable; only the shared option-stage ellipse is. Consumers must keep hand-tuned pad spread.",
    optionStage: stage.rectXY,
    sourceModels: [stage.key],
  };
}

function makeResultsAnchors(elements) {
  // rpot2x scenes carry a 640x480 quad (the GC screen plane) as their backdrop;
  // normalizing against it, rather than whole-scene bounds, yields true screen
  // coordinates (the verdict badge is parked off-screen at rest, widening scene
  // bounds).
  const isScreenQuad = (bounds) =>
    Math.abs(bounds.minX + 320) < 2 &&
    Math.abs(bounds.maxX - 320) < 2 &&
    Math.abs(bounds.minY + 240) < 2 &&
    Math.abs(bounds.maxY - 240) < 2;
  const panel = elements.find((element) => isScreenQuad(element.bounds));
  if (!panel) return null;
  const panelWidth = panel.bounds.maxX - panel.bounds.minX;
  const panelHeight = panel.bounds.maxY - panel.bounds.minY;

  // Row pills: >=3 same-geometry elements (identical world width/height/centerX)
  // spanning a meaningful share of the panel, stacked vertically.
  const groups = new Map();
  for (const element of elements) {
    if (element === panel) continue;
    const width = element.bounds.maxX - element.bounds.minX;
    const height = element.bounds.maxY - element.bounds.minY;
    const centerX = (element.bounds.minX + element.bounds.maxX) / 2;
    if (width < panelWidth * 0.25) continue;
    if (isScreenQuad(element.bounds)) continue;
    const key = `${width.toFixed(1)}|${height.toFixed(1)}|${centerX.toFixed(1)}`;
    if (!groups.has(key)) groups.set(key, []);
    groups.get(key).push(element);
  }
  const pills = [...groups.values()]
    .filter((group) => group.length >= 3)
    .sort((a, b) => b.length - a.length)[0];
  if (!pills) return null;
  pills.sort((a, b) => b.bounds.maxY - a.bounds.maxY);

  const toPanelX = (x) => ((x - panel.bounds.minX) / panelWidth) * 100;
  const toPanelY = (y) => ((panel.bounds.maxY - y) / panelHeight) * 100;
  const first = pills[0];
  const last = pills[pills.length - 1];
  const centers = pills.map((pill) => toPanelY((pill.bounds.minY + pill.bounds.maxY) / 2));
  const strides = centers.slice(1).map((center, index) => center - centers[index]);
  const rowStride = strides.reduce((sum, value) => sum + value, 0) / Math.max(1, strides.length);

  return {
    caveat:
      "Rest-state export: only the exported row-pill instances are present (the full table and the verdict badge are placed by runtime animation; the badge sits off-screen here), so trust the horizontal extent - vertical values describe the rest pose. Coordinates are normalized against the 640x480 screen quad, not whole-scene bounds.",
    rows: {
      left: round(toPanelX(first.bounds.minX)),
      top: round(toPanelY(first.bounds.maxY)),
      width: round(((first.bounds.maxX - first.bounds.minX) / panelWidth) * 100),
      height: round(toPanelY(last.bounds.minY) - toPanelY(first.bounds.maxY)),
      rowHeight: round(((first.bounds.maxY - first.bounds.minY) / panelHeight) * 100),
      rowStride: round(rowStride),
    },
    sourceModels: [panel.key, ...pills.map((pill) => pill.key)],
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
  if (/^rpot2\d$/.test(asset.id)) {
    const results = makeResultsAnchors(elements);
    if (results) semantics.results = results;
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
  for (const id of ["rpot20", "rpot23"]) {
    const results = layouts[id]?.semantics?.results;
    if (results) console.log(`${id} results source models: ${results.sourceModels.join(", ")}`);
  }
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
