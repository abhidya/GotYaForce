#!/usr/bin/env node
import crypto from "node:crypto";
import fs from "node:fs";
import path from "node:path";

const region = process.argv[2] ?? "GG4E";
const stagesRoot = path.resolve("apps/game/public/stages");
const sourceRoot = path.resolve("user-data", region, "afs_data", "root");
const VISUAL_EXPORT_SUMMARY = "export-summary.json";

function sortedDirEntries(dir) {
  return fs.existsSync(dir)
    ? fs.readdirSync(dir, { withFileTypes: true }).sort((a, b) => a.name.localeCompare(b.name))
    : [];
}

function fileRecord(filePath, root) {
  const stats = fs.statSync(filePath);
  return {
    path: path.relative(root, filePath).replaceAll("\\", "/"),
    bytes: stats.size,
  };
}

fs.mkdirSync(stagesRoot, { recursive: true });

const stages = [];
for (const entry of sortedDirEntries(stagesRoot)) {
  if (!entry.isDirectory() || !/^st[0-9a-f]{2}$/i.test(entry.name)) continue;
  const id = entry.name.toLowerCase();
  const code = id.slice(2);
  const stageDir = path.join(stagesRoot, entry.name);
  const modelDir = path.join(stageDir, "model");
  const rawManifestPath = path.join(stageDir, "manifest.json");
  const rawManifest = readJsonIfExists(rawManifestPath).value ?? {};
  const models = sortedDirEntries(modelDir)
    .filter((modelEntry) => modelEntry.isFile() && /^model_\d+\.glb$/i.test(modelEntry.name))
    .map((modelEntry) => fileRecord(path.join(modelDir, modelEntry.name), stageDir));
  const textures = sortedDirEntries(modelDir)
    .filter((textureEntry) => textureEntry.isFile() && /\.(png|tpl)$/i.test(textureEntry.name))
    .map((textureEntry) => fileRecord(path.join(modelDir, textureEntry.name), stageDir));
  const collision = sortedDirEntries(path.join(stageDir, "collision"))
    .filter((collisionEntry) => collisionEntry.isFile() && /^hit[0-9a-f]{3}\.bin$/i.test(collisionEntry.name))
    .map((collisionEntry) => fileRecord(path.join(stageDir, "collision", collisionEntry.name), stageDir));
  const setArcs = sortedDirEntries(path.join(stageDir, "set"))
    .filter((setEntry) => setEntry.isFile() && /^set[0-9a-f]{4}\.arc$/i.test(setEntry.name))
    .map((setEntry) => fileRecord(path.join(stageDir, "set", setEntry.name), stageDir));

  const exportSummaryPath = path.join(modelDir, VISUAL_EXPORT_SUMMARY);
  const exportSummary = readJsonIfExists(exportSummaryPath);
  const modelIndices = models
    .map((model) => path.basename(model.path).match(/^model_([0-9]+)\.glb$/i))
    .filter(Boolean)
    .map((match) => Number(match[1]))
    .sort((a, b) => a - b);
  const maxModelIndex = modelIndices.length > 0 ? modelIndices.at(-1) : null;
  const missingModelIndices =
    maxModelIndex == null ? [] : range(0, maxModelIndex).filter((index) => !modelIndices.includes(index));
  const zeroByteGlbFiles = models.filter((model) => model.bytes === 0).map((model) => model.path);
  const expectedGlbIndices = expectedGlbIndicesFromSummary(exportSummary.value, modelIndices);
  const missingExpectedGlbIndices = expectedGlbIndices.filter((index) => !modelIndices.includes(index));
  const unexpectedGlbIndices = modelIndices.filter(
    (index) => expectedGlbIndices.length > 0 && !expectedGlbIndices.includes(index),
  );
  const failedModelIndices = numericArray(exportSummary.value?.failedModelIndices);
  const skippedNullRootJointIndices = numericArray(exportSummary.value?.skippedNullRootJointIndices);
  const hasCompleteGlbExport =
    models.length > 0 &&
    zeroByteGlbFiles.length === 0 &&
    missingExpectedGlbIndices.length === 0 &&
    unexpectedGlbIndices.length === 0 &&
    exportSummary.ok &&
    exportSummary.value?.complete === true &&
    failedModelIndices.length === 0;

  const source = inspectSource(code);
  const copied = {
    stageArc: relPublic(path.join(stageDir, "raw", `${id}_mdl.arc`)),
    stagePzz: relPublic(path.join(stageDir, "raw", `${id}.pzz`)),
    hitBins: collision.map((file) => `${id}/${file.path}`),
    setArcs: setArcs.map((file) => `${id}/${file.path}`),
  };
  const missingSourceHitFiles = source.hitFiles.filter(
    (file) => !collision.some((exported) => path.basename(exported.path).toLowerCase() === file.toLowerCase()),
  );
  const visual = {
    hasGlbPieces: models.length > 0 && zeroByteGlbFiles.length === 0,
    hasContiguousGlbSequence: models.length > 0 && zeroByteGlbFiles.length === 0 && missingModelIndices.length === 0,
    hasCompleteGlbExport,
    glbCount: models.length,
    nonEmptyGlbCount: models.filter((model) => model.bytes > 0).length,
    maxModelIndex,
    missingModelIndices,
    expectedGlbIndices,
    missingExpectedGlbIndices,
    unexpectedGlbIndices,
    zeroByteGlbFiles,
    textureCount: textures.length,
    exportSummary: {
      path: path.relative(stageDir, exportSummaryPath).replaceAll("\\", "/"),
      exists: fs.existsSync(exportSummaryPath),
      parses: exportSummary.ok,
      error: exportSummary.error,
      exporter: exportSummary.value?.exporter ?? null,
      expectedSlotCount: exportSummary.value?.expectedSlotCount ?? null,
      expectedGlbCount: exportSummary.value?.expectedDaeCount ?? expectedGlbIndices.length,
      exportedModelCount: exportSummary.value?.exportedModelCount ?? null,
      failedModelIndices,
      skippedNullRootJointIndices,
      complete: exportSummary.value?.complete ?? null,
    },
  };
  const status = verifiedStatus({
    visual,
    source,
    raw: {
      stageArcMatchesSource: filesMatch(path.join(stageDir, "raw", `${id}_mdl.arc`), source.stageArc),
      stagePzzMatchesSource: filesMatch(path.join(stageDir, "raw", `${id}.pzz`), source.stagePzz),
    },
    collision: {
      missingSourceHitFiles,
    },
  });
  const renderStatus = hasCompleteGlbExport ? "glb-complete" : models.length > 0 ? "glb-partial" : "raw-only";

  const notes = sanitizeRuntimeNotes(rawManifest.notes);
  const manifest = {
    ...rawManifest,
    region,
    id,
    source: rawManifest.source ?? `user-data/${region}/afs_data/root`,
    status,
    copied,
    visual,
    modelCount: models.length,
    models,
    textures,
    collision,
    setArcs,
    renderStatus,
    ...(notes.length > 0 ? { notes } : {}),
  };
  fs.writeFileSync(path.join(stageDir, "manifest.json"), `${JSON.stringify(manifest, null, 2)}\n`);
  stages.push({
    id,
    status,
    modelCount: models.length,
    renderStatus,
    visualComplete: hasCompleteGlbExport,
    collisionCount: collision.length,
    setArcCount: setArcs.length,
  });
}

const rootManifest = {
  region,
  generatedBy: "scripts/build-stage-manifests.mjs",
  stages,
};
fs.writeFileSync(path.join(stagesRoot, "manifest.json"), `${JSON.stringify(rootManifest, null, 2)}\n`);
console.log(JSON.stringify(rootManifest, null, 2));

function inspectSource(code) {
  const stageArc = path.join(sourceRoot, `st${code}_mdl.arc`);
  const stagePzz = path.join(sourceRoot, `st${code}.pzz`);
  const hitFiles = fs.existsSync(sourceRoot)
    ? fs
        .readdirSync(sourceRoot)
        .filter((file) => new RegExp(`^hit${code}[0-9a-f]\\.bin$`, "i").test(file))
        .sort()
    : [];
  return {
    stageArc,
    stagePzz,
    hasStageArc: fs.existsSync(stageArc),
    hasStagePzz: fs.existsSync(stagePzz),
    hitFiles,
  };
}

function verifiedStatus(record) {
  if (!record.visual.hasGlbPieces) return "missing-visual-glb";
  if (record.visual.zeroByteGlbFiles.length > 0) return "partial-visual-zero-byte-glb";
  if (!record.visual.exportSummary.exists) return "partial-visual-export-unverified";
  if (record.visual.exportSummary.exists && record.visual.exportSummary.failedModelIndices.length > 0) {
    return "partial-visual-export-failed";
  }
  if (!record.visual.hasCompleteGlbExport) return "partial-visual-glb-missing-slots";
  if (
    (record.source.hasStageArc && !record.raw.stageArcMatchesSource) ||
    (record.source.hasStagePzz && !record.raw.stagePzzMatchesSource)
  ) {
    return "visual-exported-raw-mismatch";
  }
  if (record.source.hitFiles.length > 0 && record.collision.missingSourceHitFiles.length > 0) {
    return "visual-exported-missing-hit-files";
  }
  if (record.source.hitFiles.length === 0) return "visual-exported-no-source-hit-files";
  return "verified-visual-and-collision";
}

function relPublic(file) {
  return fs.existsSync(file) ? path.relative(stagesRoot, file).replaceAll("\\", "/") : null;
}

function filesMatch(left, right) {
  if (!left || !right || !fs.existsSync(left) || !fs.existsSync(right)) return false;
  const leftStat = fs.statSync(left);
  const rightStat = fs.statSync(right);
  return leftStat.size === rightStat.size && sha1(left) === sha1(right);
}

function sha1(file) {
  return crypto.createHash("sha1").update(fs.readFileSync(file)).digest("hex");
}

function readJsonIfExists(file) {
  try {
    return { ok: true, value: JSON.parse(fs.readFileSync(file, "utf8")), error: null };
  } catch (error) {
    if (error.code === "ENOENT") return { ok: false, value: null, error: "missing" };
    return { ok: false, value: null, error: error.message };
  }
}

function expectedGlbIndicesFromSummary(summary, modelIndices) {
  const expected = numericArray(summary?.expectedDaeIndices);
  if (expected.length > 0) return expected;
  const maxModelIndex = modelIndices.length > 0 ? modelIndices.at(-1) : null;
  return maxModelIndex == null ? [] : range(0, maxModelIndex);
}

function numericArray(value) {
  return Array.isArray(value)
    ? value.filter((item) => Number.isInteger(item) && item >= 0).sort((left, right) => left - right)
    : [];
}

function range(start, endInclusive) {
  return Array.from({ length: endInclusive - start + 1 }, (_, index) => start + index);
}

function sanitizeRuntimeNotes(notes) {
  if (!Array.isArray(notes)) return [];
  return notes.map((note) =>
    typeof note === "string"
      ? note.replace("Visual DAE pieces are imported render assets", "Visual GLB pieces are imported render assets")
      : note,
  );
}
