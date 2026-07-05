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
  // DERIVED — research/decomp/challenge-stage-naming-2026-07-05.md §1.2: the [0x1d]
  // Challenge rand%3 selects the st0x / st2x / st4x archive FAMILY for outdoor
  // arenas. The on-disc HIT bins (user-data/GG4E/afs_data/root) only exist for the
  // BASE byte (hit0XX.bin / hit1XX.bin / hitffX.bin); there is NO hit2XX / hit4XX
  // on disc because the family variants reuse the base arena's collision geometry.
  // The exported collision bins under st2x/st4x/collision/ are byte-identical copies
  // of the base stage's hit0XX.bin triplet (sha1-verified below). This wires the
  // family-variant stages as DERIVED-shared-base collision so the manifest `status`
  // no longer mislabels them "visual-exported-no-source-hit-files".
  const familyBase = source.familyBase;
  const collisionDerivation = familyBase
    ? deriveFamilyCollision(stageDir, id, familyBase)
    : null;
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
      collisionDerivation,
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
    ...(collisionDerivation ? { collisionDerivation } : {}),
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
  // DERIVED — family-variant codes (st2x / st4x) have no hit2XX / hit4XX on disc;
  // they reuse the base stage st0x's hit0XX.bin triplet. Gather the base triplet
  // (and the base stage folder for byte-identity verification) so verifiedStatus can
  // recognize the shared-base collision instead of flagging "no source hit files".
  const familyBase = familyVariantBaseCode(code);
  const baseHitFiles =
    familyBase && fs.existsSync(sourceRoot)
      ? fs
          .readdirSync(sourceRoot)
          .filter((file) => new RegExp(`^hit${familyBase}[0-9a-f]\\.bin$`, "i").test(file))
          .sort()
      : [];
  return {
    stageArc,
    stagePzz,
    hasStageArc: fs.existsSync(stageArc),
    hasStagePzz: fs.existsSync(stagePzz),
    hitFiles,
    familyBase,
    baseHitFiles,
  };
}

/**
 * Map a stage code to its base st0x code when the code is a family variant
 * (first nibble 2 or 4 — the Challenge [0x1d] rand%3 family roll). Returns null
 * for base stages and stff. Citation: research/decomp/challenge-stage-naming-2026-07-05.md §1.2.
 */
function familyVariantBaseCode(code) {
  if (code.length !== 2) return null;
  const fam = code.charAt(0);
  const sub = code.charAt(1);
  if ((fam === "2" || fam === "4") && /^[0-9a-f]$/.test(sub)) {
    return "0" + sub;
  }
  return null;
}

/**
 * DERIVED — verify the exported family-variant collision bins are byte-identical
 * (sha1) to the base stage's exported collision bins. The base stage folder is the
 * canonical DERIVED source for the family variant's collision geometry.
 */
function deriveFamilyCollision(stageDir, familyId, baseCode) {
  const baseId = `st${baseCode}`;
  const baseDir = path.join(stagesRoot, baseId);
  const familyCollisionDir = path.join(stageDir, "collision");
  const baseCollisionDir = path.join(baseDir, "collision");
  if (!fs.existsSync(baseCollisionDir) || !fs.existsSync(familyCollisionDir)) {
    return { kind: "DERIVED_FAMILY_VARIANT", fromBaseStage: baseId, layers: [], byteIdentical: false };
  }
  const familyCode = familyId.slice(2);
  const layers = ["0", "1", "2"].map((layer) => {
    const familyFile = path.join(familyCollisionDir, `hit${familyCode}${layer}.bin`);
    const baseFile = path.join(baseCollisionDir, `hit${baseCode}${layer}.bin`);
    const exists = fs.existsSync(familyFile) && fs.existsSync(baseFile);
    const shaMatch = exists && filesMatch(familyFile, baseFile);
    return {
      layer: Number(layer),
      familyFile: exists ? path.relative(stagesRoot, familyFile).replaceAll("\\", "/") : null,
      baseFile: exists ? path.relative(stagesRoot, baseFile).replaceAll("\\", "/") : null,
      shaMatch: shaMatch === true,
    };
  });
  return {
    kind: "DERIVED_FAMILY_VARIANT",
    fromBaseStage: baseId,
    layers,
    byteIdentical: layers.every((entry) => entry.shaMatch),
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
  if (record.source.hitFiles.length === 0) {
    // DERIVED — family variants (st2x/st4x) have no on-disc hit2XX/hit4XX but reuse
    // the base stage's hit0XX.bin triplet. If the exported family collision bins are
    // sha1-identical to the base stage's exported bins, recognize the shared-base
    // collision as verified. Otherwise (base absent on disc, or copy drifted) the
    // stage genuinely has no source hit bin → keep the rect-bounds fallback label.
    const derived = record.collision.collisionDerivation;
    if (derived && derived.byteIdentical && (record.source.baseHitFiles?.length ?? 0) > 0) {
      return "verified-visual-and-collision-derived";
    }
    return "visual-exported-no-source-hit-files";
  }
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
