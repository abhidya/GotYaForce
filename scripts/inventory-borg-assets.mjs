#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";

const repoRoot = path.resolve(".");

const paths = {
  discRoot: path.join(repoRoot, "user-data", "GG4E", "afs_data", "root"),
  browserModels: path.join(repoRoot, "apps", "game", "public", "models"),
  borgData: path.join(repoRoot, "packages", "assets", "data", "borgs.json"),
  formatSpecs: path.join(repoRoot, "research", "format-specs"),
  browserManifest: path.join(repoRoot, "apps", "game", "public", "models", "library", "manifest.json"),
  outputDir: path.join(repoRoot, "research", "asset-inventory"),
};

const outputJson = path.join(paths.outputDir, "borg-assets.json");
const outputMarkdown = path.join(paths.outputDir, "borg-assets.md");

for (const input of [paths.discRoot, paths.browserModels, paths.borgData, paths.formatSpecs]) {
  mustExist(input);
}

const metadata = readJson(paths.borgData);
if (!metadata || !Array.isArray(metadata.borgs)) {
  fail(`expected borgs array in ${rel(paths.borgData)}`);
}

const recordsById = new Map();

for (const borg of metadata.borgs) {
  const id = normalizeBorgId(borg.id);
  if (!id) continue;
  const record = getRecord(id);
  record.name = borg.name ?? record.name;
  record.energy = typeof borg.energy === "number" ? borg.energy : record.energy;
  record.number = borg.number ?? null;
  record.tribe = borg.tribe ?? null;
  record.type = borg.type ?? null;
  record.rarity = borg.rarity ?? null;
  record.metadata = {
    present: true,
    model: borg.model ?? null,
    anim: borg.anim ?? null,
    hasModel: Boolean(borg.hasModel),
    hasAnim: Boolean(borg.hasAnim),
  };
}

for (const file of scanFiles(paths.discRoot)) {
  const id = idFromBasename(file);
  if (!id) continue;
  const record = getRecord(id);
  addDiscFile(record, file);
}

const browserManifest = readManifest();
for (const manifestRecord of browserManifest.values()) {
  const id = normalizeBorgId(manifestRecord.id);
  if (!id) continue;
  const record = getRecord(id);
  record.browserManifest = {
    present: true,
    dae: manifestRecord.dae ?? null,
    bones: manifestRecord.bones ?? null,
    meshes: manifestRecord.meshes ?? null,
    tris: manifestRecord.tris ?? null,
    textures: Array.isArray(manifestRecord.textures) ? [...manifestRecord.textures] : [],
  };
  record.name ??= manifestRecord.name ?? null;
  record.energy ??= typeof manifestRecord.energy === "number" ? manifestRecord.energy : null;
  record.tribe ??= manifestRecord.tribe ?? null;
}

for (const file of scanFiles(paths.browserModels)) {
  const id = idFromPathSegments(file, paths.browserModels) ?? idFromBasename(file);
  if (!id) continue;
  const record = getRecord(id);
  addBrowserFile(record, file);
}

const records = [...recordsById.values()].map(finalizeRecord).sort(compareBorgIds);
const inventory = {
  generatedAt: new Date().toISOString(),
  generatedBy: rel(new URL(import.meta.url).pathname),
  inputs: {
    discRoot: rel(paths.discRoot),
    browserModels: rel(paths.browserModels),
    borgData: rel(paths.borgData),
    formatSpecs: scanFiles(paths.formatSpecs)
      .filter((file) => file.toLowerCase().endsWith(".md"))
      .map((file) => fileInfo(file)),
  },
  summary: buildSummary(records),
  records,
};

fs.mkdirSync(paths.outputDir, { recursive: true });
writeJson(outputJson, inventory);

const inventoryFromJson = readJson(outputJson);
fs.writeFileSync(`${outputMarkdown}.tmp`, renderMarkdown(inventoryFromJson), "utf8");
fs.renameSync(`${outputMarkdown}.tmp`, outputMarkdown);

console.log("borg asset inventory");
console.log(`records: ${inventory.summary.totalRecords}`);
console.log(`metadata records: ${inventory.summary.metadataRecords}`);
console.log(`disc borg ids: ${inventory.summary.discBorgIds}`);
console.log(`source primary models: ${inventory.summary.sourcePrimaryModels}`);
console.log(`source MOT files: ${inventory.summary.sourceMotFiles}`);
console.log(`browser DAE exports: ${inventory.summary.browserDaeExports}`);
console.log(`browser animation mapped: ${inventory.summary.browserAnimationMapped}`);
console.log(`safe static render now: ${inventory.summary.safeStaticRenderNow}`);
console.log(`safe animated render now: ${inventory.summary.safeAnimatedRenderNow}`);
console.log(`T-pose MOT mapping risk: ${inventory.summary.tPoseMotMappingRisk}`);
console.log(`wrote ${rel(outputJson)}`);
console.log(`wrote ${rel(outputMarkdown)}`);

function getRecord(id) {
  const normalized = normalizeBorgId(id);
  if (!normalized) fail(`invalid borg id "${id}"`);
  if (!recordsById.has(normalized)) {
    recordsById.set(normalized, {
      id: normalized,
      name: null,
      energy: null,
      number: null,
      tribe: null,
      type: null,
      rarity: null,
      metadata: { present: false, model: null, anim: null, hasModel: false, hasAnim: false },
      browserManifest: { present: false, dae: null, bones: null, meshes: null, tris: null, textures: [] },
      _disc: {
        archives: [],
        modelArcs: [],
        motBins: [],
        dataBins: [],
        hitBins: [],
        other: [],
      },
      _browser: {
        daeFiles: [],
        texturePngs: [],
        animationJsons: [],
        other: [],
      },
    });
  }
  return recordsById.get(normalized);
}

function addDiscFile(record, file) {
  const name = path.basename(file);
  const lower = name.toLowerCase();
  const info = fileInfo(file);
  if (lower === `${record.id}.pzz`) {
    record._disc.archives.push(info);
  } else if (lower === `${record.id}mot.bin`) {
    record._disc.motBins.push(info);
  } else if (/^pl[0-9a-f]{4}[a-z]?_mdl\.arc$/i.test(lower)) {
    record._disc.modelArcs.push({
      ...info,
      variant: modelVariant(lower, record.id),
      primary: lower === `${record.id}_mdl.arc`,
    });
  } else if (/^pl[0-9a-f]{4}data\d*\.bin$/i.test(lower)) {
    record._disc.dataBins.push(info);
  } else if (lower === `${record.id}hit.bin`) {
    record._disc.hitBins.push(info);
  } else {
    record._disc.other.push(info);
  }
}

function addBrowserFile(record, file) {
  const lower = path.basename(file).toLowerCase();
  const info = fileInfo(file);
  if (lower.endsWith(".dae")) {
    record._browser.daeFiles.push(info);
  } else if (lower.endsWith(".png")) {
    record._browser.texturePngs.push(info);
  } else if (/^anim_.*\.json$/i.test(lower)) {
    record._browser.animationJsons.push(info);
  } else {
    record._browser.other.push(info);
  }
}

function finalizeRecord(record) {
  sortFiles(record._disc.archives);
  sortFiles(record._disc.modelArcs);
  sortFiles(record._disc.motBins);
  sortFiles(record._disc.dataBins);
  sortFiles(record._disc.hitBins);
  sortFiles(record._disc.other);
  sortFiles(record._browser.daeFiles);
  sortFiles(record._browser.texturePngs);
  sortFiles(record._browser.animationJsons);
  sortFiles(record._browser.other);

  const sourceModelArcs = record._disc.modelArcs;
  const primaryModels = sourceModelArcs.filter((file) => file.primary);
  const expectedMot = Boolean(record.metadata.hasAnim || record.metadata.anim);
  const sourceMotPresent = record._disc.motBins.length > 0;
  const browserDaePresent = record._browser.daeFiles.length > 0;
  const browserAnimationsPresent = record._browser.animationJsons.length > 0;
  const textureStatus = getTextureStatus(record, browserDaePresent);
  const safeStaticRenderNow =
    browserDaePresent && (textureStatus.status === "exported-png-ready" || textureStatus.status === "no-exported-textures");
  const safeAnimatedRenderNow = safeStaticRenderNow && browserAnimationsPresent;
  const wouldTPoseBecauseMotMappingMissing =
    safeStaticRenderNow && (expectedMot || sourceMotPresent) && !browserAnimationsPresent;
  const missingPieces = [];

  if (!record.metadata.present) missingPieces.push("metadata");
  if (primaryModels.length === 0) missingPieces.push("source-primary-model");
  if (record._disc.archives.length === 0) missingPieces.push("source-pzz");
  if (expectedMot && !sourceMotPresent) missingPieces.push("source-mot");
  if (!browserDaePresent) missingPieces.push("browser-dae");
  if (textureStatus.status === "missing-exported-png") missingPieces.push("browser-textures");
  if ((expectedMot || sourceMotPresent) && browserDaePresent && !browserAnimationsPresent) {
    missingPieces.push("browser-animation-mapping");
  }

  return {
    id: record.id,
    name: record.name,
    energy: record.energy,
    number: record.number,
    tribe: record.tribe,
    type: record.type,
    rarity: record.rarity,
    metadata: record.metadata,
    sourceFiles: {
      archives: record._disc.archives,
      modelArcs: sourceModelArcs,
      motBins: record._disc.motBins,
      dataBins: record._disc.dataBins,
      hitBins: record._disc.hitBins,
      other: record._disc.other,
    },
    exportedBrowserModel: {
      status: browserDaePresent ? "ready" : "missing",
      daeFiles: record._browser.daeFiles,
      directories: unique(record._browser.daeFiles.map((file) => path.posix.dirname(file.path))),
      manifest: record.browserManifest,
    },
    motStatus: {
      status: browserAnimationsPresent
        ? "browser-mapped"
        : sourceMotPresent
          ? "source-present-mapping-missing"
          : expectedMot
            ? "metadata-expected-source-missing"
            : "none-known",
      expectedFromMetadata: expectedMot,
      sourcePresent: sourceMotPresent,
      sourceFiles: record._disc.motBins,
      browserMapped: browserAnimationsPresent,
      browserAnimationFiles: record._browser.animationJsons,
    },
    textureStatus,
    renderReadiness: safeAnimatedRenderNow
      ? "animated-ready"
      : wouldTPoseBecauseMotMappingMissing
        ? "static-ready-but-mot-mapping-missing"
        : safeStaticRenderNow
          ? "static-ready"
          : browserDaePresent
            ? "browser-model-incomplete"
            : "not-exported",
    safeStaticRenderNow,
    safeAnimatedRenderNow,
    wouldTPoseBecauseMotMappingMissing,
    missingPieces,
  };
}

function getTextureStatus(record, browserDaePresent) {
  const textures = record._browser.texturePngs;
  if (textures.length > 0) {
    return {
      status: "exported-png-ready",
      exportedPngFiles: textures,
      expectedFromManifest: record.browserManifest.textures,
    };
  }
  if (browserDaePresent && record.browserManifest.present && record.browserManifest.textures.length === 0) {
    return {
      status: "no-exported-textures",
      exportedPngFiles: [],
      expectedFromManifest: [],
    };
  }
  if (browserDaePresent) {
    return {
      status: "missing-exported-png",
      exportedPngFiles: [],
      expectedFromManifest: record.browserManifest.textures,
    };
  }
  return {
    status: "not-exported",
    exportedPngFiles: [],
    expectedFromManifest: record.browserManifest.textures,
  };
}

function buildSummary(records) {
  const missingCategoryCounts = new Map();
  for (const record of records) {
    for (const piece of record.missingPieces) {
      missingCategoryCounts.set(piece, (missingCategoryCounts.get(piece) ?? 0) + 1);
    }
  }

  return {
    totalRecords: records.length,
    metadataRecords: records.filter((record) => record.metadata.present).length,
    discBorgIds: records.filter((record) => hasAnySourceFile(record)).length,
    sourcePrimaryModels: records.filter((record) => record.sourceFiles.modelArcs.some((file) => file.primary)).length,
    sourceMotFiles: records.filter((record) => record.sourceFiles.motBins.length > 0).length,
    browserDaeExports: records.filter((record) => record.exportedBrowserModel.status === "ready").length,
    browserTextureExports: records.filter((record) => record.textureStatus.exportedPngFiles.length > 0).length,
    browserAnimationMapped: records.filter((record) => record.motStatus.browserMapped).length,
    safeStaticRenderNow: records.filter((record) => record.safeStaticRenderNow).length,
    safeAnimatedRenderNow: records.filter((record) => record.safeAnimatedRenderNow).length,
    tPoseMotMappingRisk: records.filter((record) => record.wouldTPoseBecauseMotMappingMissing).length,
    topMissingCategories: [...missingCategoryCounts.entries()]
      .map(([category, count]) => ({ category, count }))
      .sort((a, b) => b.count - a.count || a.category.localeCompare(b.category)),
  };
}

function renderMarkdown(inventory) {
  const records = inventory.records;
  const safeStatic = records.filter((record) => record.safeStaticRenderNow);
  const safeAnimated = records.filter((record) => record.safeAnimatedRenderNow);
  const tPoseRisk = records.filter((record) => record.wouldTPoseBecauseMotMappingMissing);

  const lines = [];
  lines.push("# Borg Asset Inventory");
  lines.push("");
  lines.push(`Generated by \`${inventory.generatedBy}\` at \`${inventory.generatedAt}\`.`);
  lines.push(`This markdown is generated from \`${rel(outputJson)}\` in the same script run.`);
  lines.push("");
  lines.push("## Input Sources");
  lines.push("");
  lines.push(`- Disc root: \`${inventory.inputs.discRoot}\``);
  lines.push(`- Browser models: \`${inventory.inputs.browserModels}\``);
  lines.push(`- Borg metadata: \`${inventory.inputs.borgData}\``);
  lines.push(
    `- Format specs inspected: ${inventory.inputs.formatSpecs.map((file) => `\`${file.path}\``).join(", ") || "none"}`,
  );
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push("| Metric | Count |");
  lines.push("|---|---:|");
  lines.push(`| Inventory records | ${inventory.summary.totalRecords} |`);
  lines.push(`| Metadata records | ${inventory.summary.metadataRecords} |`);
  lines.push(`| Disc borg ids with any source file | ${inventory.summary.discBorgIds} |`);
  lines.push(`| Source primary models | ${inventory.summary.sourcePrimaryModels} |`);
  lines.push(`| Source MOT files | ${inventory.summary.sourceMotFiles} |`);
  lines.push(`| Browser DAE exports | ${inventory.summary.browserDaeExports} |`);
  lines.push(`| Browser texture exports | ${inventory.summary.browserTextureExports} |`);
  lines.push(`| Browser animation mapped | ${inventory.summary.browserAnimationMapped} |`);
  lines.push(`| Safe static render now | ${inventory.summary.safeStaticRenderNow} |`);
  lines.push(`| Safe animated render now | ${inventory.summary.safeAnimatedRenderNow} |`);
  lines.push(`| T-pose MOT mapping risk | ${inventory.summary.tPoseMotMappingRisk} |`);
  lines.push("");
  lines.push("## Top Missing Categories");
  lines.push("");
  lines.push("| Missing piece | Records |");
  lines.push("|---|---:|");
  for (const item of inventory.summary.topMissingCategories.slice(0, 10)) {
    lines.push(`| ${md(item.category)} | ${item.count} |`);
  }
  lines.push("");
  lines.push("## Safe To Render Now");
  lines.push("");
  lines.push(
    "Safe static render means an exported browser DAE exists and exported PNG texture state is complete or explicitly empty.",
  );
  lines.push("");
  lines.push(`- Static-safe count: ${safeStatic.length}`);
  lines.push(`- Animated-safe count: ${safeAnimated.length}`);
  lines.push("");
  lines.push("| ID | Name | Textures | Anim JSON |");
  lines.push("|---|---|---:|---:|");
  for (const record of safeStatic) {
    lines.push(
      `| \`${record.id}\` | ${md(displayName(record))} | ${record.textureStatus.exportedPngFiles.length} | ${record.motStatus.browserAnimationFiles.length} |`,
    );
  }
  lines.push("");
  lines.push("## Would T-Pose Without MOT Mapping");
  lines.push("");
  lines.push(
    "These have browser model exports and a known/expected MOT source, but no exported browser animation JSON mapping yet.",
  );
  lines.push("");
  lines.push(`T-pose risk count: ${tPoseRisk.length}`);
  lines.push("");
  lines.push("| ID | Name | Source MOT | Browser model | Missing |");
  lines.push("|---|---|---:|---|---|");
  for (const record of tPoseRisk) {
    lines.push(
      `| \`${record.id}\` | ${md(displayName(record))} | ${record.sourceFiles.motBins.length} | ${md(record.exportedBrowserModel.directories.join(", "))} | ${md(record.missingPieces.join(", "))} |`,
    );
  }
  lines.push("");
  lines.push("## Full Inventory");
  lines.push("");
  lines.push(
    "| ID | Name | Energy | Source model | Source MOT | Browser DAE | PNG | Anim JSON | Readiness | Missing |",
  );
  lines.push("|---|---|---:|---:|---:|---:|---:|---:|---|---|");
  for (const record of records) {
    lines.push(
      [
        `\`${record.id}\``,
        md(displayName(record)),
        record.energy ?? "",
        record.sourceFiles.modelArcs.filter((file) => file.primary).length,
        record.sourceFiles.motBins.length,
        record.exportedBrowserModel.daeFiles.length,
        record.textureStatus.exportedPngFiles.length,
        record.motStatus.browserAnimationFiles.length,
        md(record.renderReadiness),
        md(record.missingPieces.join(", ") || "none"),
      ].join(" | ").replace(/^/, "| ") + " |",
    );
  }
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function readManifest() {
  if (!fs.existsSync(paths.browserManifest)) return new Map();
  const manifest = readJson(paths.browserManifest);
  if (!Array.isArray(manifest)) fail(`expected array in ${rel(paths.browserManifest)}`);
  return new Map(
    manifest
      .filter((record) => record && normalizeBorgId(record.id))
      .map((record) => [normalizeBorgId(record.id), record]),
  );
}

function scanFiles(dir) {
  const result = [];
  for (const entry of fs.readdirSync(dir, { withFileTypes: true }).sort((a, b) => a.name.localeCompare(b.name))) {
    const child = path.join(dir, entry.name);
    if (entry.isDirectory()) {
      result.push(...scanFiles(child));
    } else if (entry.isFile()) {
      result.push(child);
    }
  }
  return result;
}

function fileInfo(file) {
  return {
    path: rel(file),
    bytes: fs.statSync(file).size,
  };
}

function idFromBasename(file) {
  const match = path.basename(file).match(/^(pl[0-9a-f]{4})/i);
  return match ? match[1].toLowerCase() : null;
}

function idFromPathSegments(file, root) {
  const relative = path.relative(root, file);
  for (const segment of relative.split(path.sep)) {
    const id = normalizeBorgId(segment);
    if (id) return id;
  }
  return null;
}

function normalizeBorgId(value) {
  if (typeof value !== "string") return null;
  const lower = value.toLowerCase();
  return /^pl[0-9a-f]{4}$/.test(lower) ? lower : null;
}

function modelVariant(name, id) {
  const match = name.match(new RegExp(`^${id}([a-z]?)_mdl\\.arc$`, "i"));
  if (!match) return "unknown";
  return match[1] ? match[1].toLowerCase() : "primary";
}

function hasAnySourceFile(record) {
  return Object.values(record.sourceFiles).some((files) => Array.isArray(files) && files.length > 0);
}

function sortFiles(files) {
  files.sort((a, b) => a.path.localeCompare(b.path));
}

function unique(values) {
  return [...new Set(values.filter(Boolean))].sort();
}

function compareBorgIds(a, b) {
  return a.id.localeCompare(b.id);
}

function displayName(record) {
  return record.name ?? "(unknown)";
}

function md(value) {
  return String(value ?? "").replace(/\|/g, "\\|");
}

function rel(file) {
  let normalized = file;
  if (normalized.startsWith("/")) {
    const windowsPath = normalized.match(/^\/([A-Za-z]:\/.*)$/);
    if (windowsPath) normalized = windowsPath[1];
  }
  return path.relative(repoRoot, normalized).split(path.sep).join("/");
}

function readJson(file) {
  return JSON.parse(fs.readFileSync(file, "utf8"));
}

function writeJson(file, value) {
  fs.writeFileSync(`${file}.tmp`, `${JSON.stringify(value, null, 2)}\n`, "utf8");
  fs.renameSync(`${file}.tmp`, file);
}

function mustExist(file) {
  if (!fs.existsSync(file)) fail(`missing input: ${rel(file)}`);
}

function fail(message) {
  console.error(`inventory-borg-assets: ${message}`);
  process.exit(1);
}
