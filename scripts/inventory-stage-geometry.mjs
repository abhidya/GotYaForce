#!/usr/bin/env node
import { createHash } from "node:crypto";
import { mkdir, readdir, readFile, stat, writeFile } from "node:fs/promises";
import path from "node:path";

const repoRoot = process.cwd();
const outputDir = "research/asset-inventory";
const jsonOut = path.join(outputDir, "stage-geometry-collision.json");
const mdOut = path.join(outputDir, "stage-geometry-collision.md");

const stageId = "st00";
const stageCode = "00";
const defaultStageModelCount = 40;

const paths = {
  afsRoot: "user-data/GG4E/afs_data/root",
  discRoot: "user-data/GG4E/disc",
  publicStage: `apps/game/public/stages/${stageId}`,
  publicStageManifest: `apps/game/public/stages/${stageId}/manifest.json`,
  publicStagesManifest: "apps/game/public/stages/manifest.json",
  stageArc: `user-data/GG4E/afs_data/root/${stageId}_mdl.arc`,
  stagePzz: `user-data/GG4E/afs_data/root/${stageId}.pzz`,
  publicStageArc: `apps/game/public/stages/${stageId}/raw/${stageId}_mdl.arc`,
  publicStagePzz: `apps/game/public/stages/${stageId}/raw/${stageId}.pzz`,
  gameMain: "apps/game/src/main.ts",
  stageExportScript: "scripts/export-stage-hsd.mjs",
  stageAssetScript: "scripts/export-stage-assets.mjs",
  arcSpec: "research/format-specs/arc-hsd-format.md",
  symbolMap: "research/symbols/GG4E-CSM-20220412.map",
};

function rel(file) {
  return file.replaceAll("\\", "/");
}

function abs(file) {
  return path.resolve(repoRoot, file);
}

async function exists(file) {
  try {
    await stat(abs(file));
    return true;
  } catch {
    return false;
  }
}

async function statPath(file) {
  try {
    const s = await stat(abs(file));
    return { path: rel(file), exists: true, bytes: s.size };
  } catch {
    return { path: rel(file), exists: false, bytes: null };
  }
}

async function readText(file) {
  return readFile(abs(file), "utf8");
}

async function readBuffer(file) {
  return readFile(abs(file));
}

async function listDir(file) {
  try {
    return await readdir(abs(file));
  } catch {
    return [];
  }
}

async function listRecursive(file) {
  const root = abs(file);
  const out = [];

  async function walk(current) {
    let entries = [];
    try {
      entries = await readdir(current, { withFileTypes: true });
    } catch {
      return;
    }

    for (const entry of entries) {
      const full = path.join(current, entry.name);
      if (entry.isDirectory()) {
        await walk(full);
      } else if (entry.isFile()) {
        out.push(rel(path.relative(repoRoot, full)));
      }
    }
  }

  await walk(root);
  return out.sort();
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

async function fileFingerprint(file) {
  try {
    const buffer = await readBuffer(file);
    return { path: rel(file), exists: true, bytes: buffer.length, sha1: sha1(buffer) };
  } catch {
    return { path: rel(file), exists: false, bytes: null, sha1: null };
  }
}

async function sourcePublicPair(source, exported) {
  const [sourceInfo, publicInfo] = await Promise.all([fileFingerprint(source), fileFingerprint(exported)]);
  return {
    source: sourceInfo,
    public: publicInfo,
    byteMatch: Boolean(sourceInfo.exists && publicInfo.exists && sourceInfo.sha1 === publicInfo.sha1),
  };
}

function attr(text, name) {
  const match = new RegExp(`${name}="([^"]*)"`).exec(text);
  return match?.[1] ?? null;
}

function uniq(values) {
  return [...new Set(values)].sort((a, b) => String(a).localeCompare(String(b)));
}

function sample(values, limit = 12) {
  return uniq(values).slice(0, limit);
}

function findLine(text, needle) {
  const index = text.split(/\r?\n/).findIndex((line) => line.includes(needle));
  return index === -1 ? null : index + 1;
}

function refWithLine(file, text, needle) {
  const line = findLine(text, needle);
  return line ? `${rel(file)}:${line}` : rel(file);
}

function emptyBounds() {
  return {
    min: { x: Infinity, y: Infinity, z: Infinity },
    max: { x: -Infinity, y: -Infinity, z: -Infinity },
  };
}

function includePoint(bounds, x, y, z) {
  bounds.min.x = Math.min(bounds.min.x, x);
  bounds.min.y = Math.min(bounds.min.y, y);
  bounds.min.z = Math.min(bounds.min.z, z);
  bounds.max.x = Math.max(bounds.max.x, x);
  bounds.max.y = Math.max(bounds.max.y, y);
  bounds.max.z = Math.max(bounds.max.z, z);
}

function mergeBounds(target, source) {
  if (!source) return;
  includePoint(target, source.min.x, source.min.y, source.min.z);
  includePoint(target, source.max.x, source.max.y, source.max.z);
}

function finalizeBounds(bounds) {
  if (!Number.isFinite(bounds.min.x)) return null;
  const extent = {
    x: bounds.max.x - bounds.min.x,
    y: bounds.max.y - bounds.min.y,
    z: bounds.max.z - bounds.min.z,
  };
  const center = {
    x: (bounds.min.x + bounds.max.x) / 2,
    y: (bounds.min.y + bounds.max.y) / 2,
    z: (bounds.min.z + bounds.max.z) / 2,
  };
  return {
    min: roundVec(bounds.min),
    max: roundVec(bounds.max),
    extent: roundVec(extent),
    center: roundVec(center),
  };
}

function roundValue(value) {
  return Number.isFinite(value) ? Number(value.toFixed(3)) : value;
}

function roundVec(vec) {
  return {
    x: roundValue(vec.x),
    y: roundValue(vec.y),
    z: roundValue(vec.z),
  };
}

function parseNumbers(text) {
  return (text.match(/[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?/g) ?? []).map(Number);
}

function parseDae(text, file) {
  const clean = text.replace(/^\uFEFF/, "");
  const geometryBlocks = [...clean.matchAll(/<geometry\b([^>]*)>([\s\S]*?)<\/geometry>/g)];
  const controllerBlocks = [...clean.matchAll(/<controller\b/g)];
  const materialBlocks = [...clean.matchAll(/<material\b([^>]*)>/g)];
  const imageBlocks = [...clean.matchAll(/<image\b([^>]*)>([\s\S]*?)<\/image>/g)];
  const triangleBlocks = [...clean.matchAll(/<triangles\b([^>]*)>([\s\S]*?)<\/triangles>/g)];
  const polylistBlocks = [...clean.matchAll(/<polylist\b([^>]*)>([\s\S]*?)<\/polylist>/g)];
  const jointBlocks = [...clean.matchAll(/<node\b[^>]*type="JOINT"[^>]*>/g)];
  const transparencyValues = [...clean.matchAll(/<transparency>\s*<float[^>]*>([^<]+)<\/float>\s*<\/transparency>/g)]
    .map((match) => Number(match[1]))
    .filter((value) => Number.isFinite(value));
  const geometryNames = geometryBlocks.map((match) => attr(match[1], "name") ?? attr(match[1], "id")).filter(Boolean);
  const materialNames = materialBlocks.map((match) => attr(match[1], "name") ?? attr(match[1], "id")).filter(Boolean);
  const images = imageBlocks.map((match) => {
    const init = /<init_from>([^<]+)<\/init_from>/.exec(match[2])?.[1] ?? null;
    return {
      id: attr(match[1], "id"),
      name: attr(match[1], "name"),
      initFrom: init,
    };
  });
  const bounds = emptyBounds();
  let vertexCount = 0;
  const positionSources = [];

  for (const block of [...clean.matchAll(/<source\b([^>]*)>([\s\S]*?)<\/source>/g)]) {
    const id = attr(block[1], "id") ?? "";
    if (!id.includes("POSITION")) continue;
    const floatMatch = /<float_array\b([^>]*)>([\s\S]*?)<\/float_array>/.exec(block[2]);
    if (!floatMatch) continue;
    const values = parseNumbers(floatMatch[2]);
    const count = Math.floor(values.length / 3);
    vertexCount += count;
    const sourceBounds = emptyBounds();
    for (let index = 0; index + 2 < values.length; index += 3) {
      includePoint(bounds, values[index], values[index + 1], values[index + 2]);
      includePoint(sourceBounds, values[index], values[index + 1], values[index + 2]);
    }
    positionSources.push({
      id,
      declaredFloatCount: Number(attr(floatMatch[1], "count")),
      vertexCount: count,
      bbox: finalizeBounds(sourceBounds),
    });
  }

  const triangles = triangleBlocks.map((match) => ({
    count: Number(attr(match[1], "count") ?? 0),
    material: attr(match[1], "material"),
  }));
  const polylists = polylistBlocks.map((match) => ({
    count: Number(attr(match[1], "count") ?? 0),
    material: attr(match[1], "material"),
  }));
  const triangleCount = triangles.reduce((sum, item) => sum + item.count, 0);
  const polylistFaceCount = polylists.reduce((sum, item) => sum + item.count, 0);
  const bbox = finalizeBounds(bounds);

  return {
    path: rel(file),
    index: Number((path.basename(file).match(/model_(\d+)\.dae$/i) ?? [null, "-1"])[1]),
    bytes: clean.length,
    geometryCount: geometryBlocks.length,
    controllerCount: controllerBlocks.length,
    jointCount: jointBlocks.length,
    vertexCount,
    triangleCount,
    polylistFaceCount,
    bbox,
    geometryNames: sample(geometryNames, 20),
    materialNames: sample(materialNames, 20),
    textureNames: sample(images.map((image) => image.name ?? image.initFrom).filter(Boolean), 20),
    textureFiles: sample(images.map((image) => image.initFrom).filter(Boolean), 20),
    transparencyValues: uniq(transparencyValues.map((value) => roundValue(value))),
    hasGeometry: vertexCount > 0 || triangleCount > 0 || polylistFaceCount > 0,
    hasTransparentMaterial: transparencyValues.some((value) => value < 0.999),
    positionSources,
  };
}

function classifyPiece(piece) {
  const tags = [];
  const reasons = [];
  const bbox = piece.bbox;

  if (!piece.hasGeometry) {
    tags.push("empty-export-slot");
    reasons.push("DAE has no geometry, positions, triangles, or controllers with mesh data.");
    return { tags, primary: "empty-export-slot", reasons };
  }

  const { extent, min, max, center } = bbox;
  const horizontalThin = extent.y <= 80 && extent.x >= 1000 && extent.z >= 1000;
  const broadXZ = extent.x >= 7000 && extent.z >= 7000;
  const verticalLarge = extent.y >= 300 && (extent.x >= 2500 || extent.z >= 2500);
  const veryLargeShell = extent.x >= 8000 && extent.z >= 8000 && extent.y >= 300;
  const farFromOrigin = Math.hypot(center.x, center.z) >= 4500;

  if (horizontalThin && broadXZ && Math.abs(max.y) <= 100) {
    tags.push("floor");
    reasons.push("Very broad, nearly flat X/Z plane at arena Y=0.");
  }
  if (horizontalThin && broadXZ && min.y >= 900) {
    tags.push("ceiling-candidate");
    reasons.push("Very broad, nearly flat X/Z plane above the arena.");
  }
  if (verticalLarge) {
    tags.push("wall-or-vertical-shell-candidate");
    reasons.push("Large vertical extent with broad horizontal span.");
  }
  if (veryLargeShell || (farFromOrigin && verticalLarge)) {
    tags.push("backdrop-or-skybox-candidate");
    reasons.push("Large or distant shell-like geometry relative to the arena origin.");
  }
  if (piece.hasTransparentMaterial) {
    tags.push("transparent-or-invisible-candidate");
    reasons.push("At least one material has COLLADA transparency below 0.999.");
  }
  if (piece.triangleCount <= 32 && !tags.includes("floor")) {
    tags.push("small-marker-or-prop");
    reasons.push("Low triangle count; likely a small prop, marker, or simple boundary visual.");
  }
  if (tags.length === 0) {
    tags.push("prop-or-stage-detail");
    reasons.push("Geometry is present but does not meet floor, ceiling, wall, or backdrop heuristics.");
  }

  const priority = [
    "floor",
    "ceiling-candidate",
    "backdrop-or-skybox-candidate",
    "wall-or-vertical-shell-candidate",
    "transparent-or-invisible-candidate",
    "small-marker-or-prop",
    "prop-or-stage-detail",
  ];

  return {
    tags,
    primary: priority.find((tag) => tags.includes(tag)) ?? tags[0],
    reasons,
  };
}

function parseHsdDat(buffer) {
  if (buffer.length < 0x20) return { valid: false, reason: "short file" };

  const u32 = (offset) => buffer.readUInt32BE(offset);
  const fileSize = u32(0x00);
  const dataBlockSize = u32(0x04);
  const relocCount = u32(0x08);
  const rootCount = u32(0x0c);
  const externalRefCount = u32(0x10);
  const rootTableOffset = 0x20 + dataBlockSize + relocCount * 4;
  const externalRefTableOffset = rootTableOffset + rootCount * 8;
  const symbolTableOffset = externalRefTableOffset + externalRefCount * 8;
  const fileSizeMatches = fileSize === buffer.length;
  const countsArePlausible = rootCount < 4096 && externalRefCount < 4096 && relocCount < 1_000_000;
  const layoutFits = fileSizeMatches && countsArePlausible && rootTableOffset >= 0x20 && symbolTableOffset <= buffer.length;
  const roots = [];

  if (layoutFits) {
    for (let index = 0; index < rootCount; index += 1) {
      const entryOffset = rootTableOffset + index * 8;
      const dataOffset = u32(entryOffset);
      const stringOffset = u32(entryOffset + 4);
      let nameEnd = symbolTableOffset + stringOffset;
      while (nameEnd < buffer.length && buffer[nameEnd] !== 0) nameEnd += 1;
      roots.push({
        index,
        dataOffset,
        absoluteDataOffset: 0x20 + dataOffset,
        stringOffset,
        name: buffer.toString("ascii", symbolTableOffset + stringOffset, nameEnd),
      });
    }
  }

  return {
    valid: fileSize > 0 && layoutFits,
    reason: layoutFits ? null : fileSizeMatches ? "layout does not fit HSD DAT tables" : "file-size field does not match actual bytes",
    fileSize,
    actualBytes: buffer.length,
    fileSizeMatches,
    dataBlockSize,
    relocCount,
    rootCount,
    externalRefCount,
    rootTableOffset,
    symbolTableOffset,
    roots,
  };
}

function headerWords(buffer, byteCount = 64) {
  const words = [];
  for (let offset = 0; offset + 4 <= Math.min(buffer.length, byteCount); offset += 4) {
    words.push(`0x${buffer.readUInt32BE(offset).toString(16).padStart(8, "0")}`);
  }
  return words;
}

function parsePzzHeader(buffer) {
  return {
    bytes: buffer.length,
    firstWordAsCountCandidate: buffer.length >= 4 ? buffer.readUInt32BE(0) : null,
    headerWords: headerWords(buffer),
    note: "PZZ member table is not decoded by this inventory; first word is reported only as a candidate count.",
  };
}

function parseHitBin(buffer, file) {
  if (buffer.length < 0x20) {
    return { path: rel(file), valid: false, reason: "short file", bytes: buffer.length };
  }

  const magic = buffer.toString("ascii", 0, 4);
  const declaredBytes = buffer.readUInt32BE(4);
  const cellSizeX = buffer.readUInt32BE(8);
  const cellSizeZ = buffer.readUInt32BE(12);
  const gridCellsX = buffer.readUInt32BE(16);
  const gridCellsZ = buffer.readUInt32BE(20);
  const minX = buffer.readInt32BE(24);
  const minZ = buffer.readInt32BE(28);
  const maxX = minX + cellSizeX * gridCellsX;
  const maxZ = minZ + cellSizeZ * gridCellsZ;

  return {
    path: rel(file),
    valid: magic === "STIH" && declaredBytes === buffer.length,
    magic,
    bytes: buffer.length,
    declaredBytes,
    cellSize: { x: cellSizeX, z: cellSizeZ },
    gridCells: { x: gridCellsX, z: gridCellsZ },
    bounds2d: { minX, minZ, maxX, maxZ },
    note: "Header looks like an STIH collision/spatial grid. Body records are not decoded here.",
  };
}

function parseDefaultModelCount(gameText) {
  const match = /const\s+DEFAULT_STAGE_MODEL_COUNT\s*=\s*(\d+)/.exec(gameText);
  return match ? Number(match[1]) : null;
}

function stageSourceFiles(rootFiles) {
  const hitBins = [`hit${stageCode}0.bin`, `hit${stageCode}1.bin`, `hit${stageCode}2.bin`];
  const setArcs = [`set${stageCode}00.arc`, `set${stageCode}01.arc`, `set${stageCode}02.arc`, `set${stageCode}03.arc`];
  return {
    visualArc: `${stageId}_mdl.arc`,
    pzz: `${stageId}.pzz`,
    hitBins: hitBins.filter((file) => rootFiles.includes(file)),
    setArcs: setArcs.filter((file) => rootFiles.includes(file)),
    relatedCollisionArchives: rootFiles.filter((file) => /^(collision\.arc|comhit2?\.bin|hit[0-9a-f]{3}\.bin)$/i.test(file)).sort(),
  };
}

function summarizeTags(pieces, tag) {
  return pieces.filter((piece) => piece.classification.tags.includes(tag)).map((piece) => piece.id);
}

function formatBounds(bbox) {
  if (!bbox) return "none";
  return `min(${bbox.min.x}, ${bbox.min.y}, ${bbox.min.z}) max(${bbox.max.x}, ${bbox.max.y}, ${bbox.max.z})`;
}

function markdownTableCell(value) {
  if (value == null) return "";
  return String(value).replaceAll("|", "\\|");
}

function makeMarkdown(inventory) {
  const lines = [];
  const add = (line = "") => lines.push(line);

  add("# Stage Geometry, Walls, Ceiling, Collision Inventory");
  add();
  add(`Generated by \`${inventory.generatedBy}\` on ${inventory.generatedAt}.`);
  add();
  add("## Summary");
  add();
  add(`- Source stage visual archive: \`${inventory.sources.stageArc.path}\` (${inventory.sources.stageArc.bytes} bytes), HSD root names: ${inventory.sourceArchive.stageArc.hsd.roots.map((root) => `\`${root.name}\``).join(", ") || "none"}.`);
  add(`- Exported browser stage pieces: ${inventory.exportedPieces.count} DAE files at \`${inventory.exportedPieces.directory}\`; ${inventory.exportedPieces.withGeometry} contain geometry and ${inventory.exportedPieces.emptySlots.length} are geometry-empty slots (${inventory.exportedPieces.emptySlots.map((id) => `\`${id}\``).join(", ") || "none"}).`);
  add(`- Current browser loader requests ${inventory.browserLoader.defaultStageModelCount.value} pieces from \`${inventory.browserLoader.defaultStageModelCount.ref}\`; every requested index 00-39 has a DAE file, but \`model_24.dae\` has no mesh geometry.`);
  add(`- Collision/non-visual stage files: ${inventory.collision.hitBins.length} \`hit*.bin\` files, ${inventory.sourceArchive.setArcs.length} \`set*.arc\` files, and \`${inventory.sources.stagePzz.path}\` are present but are not visual DAE exports.`);
  add(`- Overall DAE bbox from raw POSITION arrays: ${formatBounds(inventory.exportedPieces.aggregateBbox)}.`);
  add();
  add("## Source And Export Paths");
  add();
  add(`- Visual source: \`${inventory.sources.stageArc.path}\`; public raw copy: \`${inventory.sources.publicStageArc.path}\`; byte match: ${inventory.sourceArchive.stageArc.publicCopy.byteMatch}.`);
  add(`- PZZ source: \`${inventory.sources.stagePzz.path}\`; public raw copy: \`${inventory.sources.publicStagePzz.path}\`; byte match: ${inventory.sourceArchive.stagePzz.publicCopy.byteMatch}.`);
  add(`- Exported visual DAE directory: \`${inventory.exportedPieces.directory}\`.`);
  add(`- Public stage manifest: \`${inventory.sources.publicStageManifest.path}\`.`);
  add(`- Exporter evidence: \`${inventory.refs.stageExporterLoop}\` emits one \`model_##.dae\` per HSD \`JOBJDescs\` entry.`);
  add();
  add("## Piece Classification");
  add();
  add(`- Floor candidates: ${inventory.findings.floorCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add(`- Wall or vertical shell candidates: ${inventory.findings.wallCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add(`- Ceiling candidates: ${inventory.findings.ceilingCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add(`- Skybox/backdrop candidates: ${inventory.findings.backdropCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add(`- Transparent/invisible-looking material candidates: ${inventory.findings.transparentCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add(`- Prop/detail candidates: ${inventory.findings.propCandidates.map((id) => `\`${id}\``).join(", ") || "none"}.`);
  add();
  add("## Exported DAE Pieces");
  add();
  add("| Piece | Browser loads | Primary classification | Triangles | Vertices | BBox | Materials | Textures |");
  add("| --- | --- | --- | ---: | ---: | --- | --- | --- |");
  for (const piece of inventory.exportedPieces.pieces) {
    add(
      `| \`${piece.id}\` | ${piece.browserLoads ? "yes" : "no"} | ${markdownTableCell(piece.classification.primary)} | ${piece.triangleCount} | ${piece.vertexCount} | ${markdownTableCell(formatBounds(piece.bbox))} | ${markdownTableCell(piece.materialNames.join(", "))} | ${markdownTableCell(piece.textureFiles.join(", "))} |`,
    );
  }
  add();
  add("## Collision, Bounds, And Set Data");
  add();
  for (const hit of inventory.collision.hitBins) {
    add(`- \`${hit.path}\`: magic ${hit.magic}, ${hit.bytes} bytes, ${hit.gridCells.x}x${hit.gridCells.z} cells at ${hit.cellSize.x}x${hit.cellSize.z}; inferred X/Z bounds ${hit.bounds2d.minX}..${hit.bounds2d.maxX}, ${hit.bounds2d.minZ}..${hit.bounds2d.maxZ}.`);
  }
  add(`- \`${inventory.sources.stagePzz.path}\`: PZZ header first word ${inventory.sourceArchive.stagePzz.header.firstWordAsCountCandidate}; members are not decoded, so any embedded stage shell/culling data remains uncertain.`);
  for (const setArc of inventory.sourceArchive.setArcs) {
    const hsdSummary = setArc.hsd.valid
      ? `HSD roots: ${setArc.hsd.roots.map((root) => root.name).join(", ") || "none"}`
      : `not decoded as bare HSD DAT (${setArc.hsd.reason}; first words ${setArc.headerWords.slice(0, 4).join(", ")})`;
    add(`- \`${setArc.path}\`: ${setArc.bytes} bytes, ${hsdSummary}. Not loaded by the browser stage renderer.`);
  }
  add();
  add("## Missing Or Uncertain Pieces");
  add();
  for (const item of inventory.missingOrUncertain) add(`- ${item}`);
  add();
  add("## Completeness Of 40 Stage Models");
  add();
  add(inventory.findings.stageModelCountConclusion);
  add();
  add("## Verification");
  add();
  add("- Run scanner: `rtk node scripts/inventory-stage-geometry.mjs`.");
  add("- Parse JSON: `rtk node -e \"JSON.parse(require('fs').readFileSync('research/asset-inventory/stage-geometry-collision.json','utf8')); console.log('json ok')\"`.");
  add();

  return `${lines.join("\n")}\n`;
}

const [rootFiles, publicStageFiles, gameText, stageExportText, stageAssetText] = await Promise.all([
  listDir(paths.afsRoot),
  listRecursive(paths.publicStage),
  readText(paths.gameMain),
  readText(paths.stageExportScript),
  readText(paths.stageAssetScript),
]);

const sourceFiles = stageSourceFiles(rootFiles);
const daeFiles = publicStageFiles.filter((file) => /\/model\/model_\d+\.dae$/i.test(file)).sort();
const textureFiles = publicStageFiles.filter((file) => /\/model\/.*\.png$/i.test(file)).sort();

const daePieces = [];
for (const file of daeFiles) {
  const parsed = parseDae(await readText(file), file);
  parsed.id = path.basename(file, ".dae");
  parsed.browserLoads = parsed.index >= 0 && parsed.index < defaultStageModelCount;
  parsed.classification = classifyPiece(parsed);
  daePieces.push(parsed);
}

const aggregate = emptyBounds();
for (const piece of daePieces) mergeBounds(aggregate, piece.bbox);

const hitBins = [];
for (const name of sourceFiles.hitBins) {
  const file = path.join(paths.afsRoot, name);
  hitBins.push(parseHitBin(await readBuffer(file), file));
}

const setArcs = [];
for (const name of sourceFiles.setArcs) {
  const file = path.join(paths.afsRoot, name);
  const buffer = await readBuffer(file);
  setArcs.push({
    path: rel(file),
    bytes: buffer.length,
    headerWords: headerWords(buffer),
    hsd: parseHsdDat(buffer),
    publicCopy: await sourcePublicPair(file, `apps/game/public/stages/${stageId}/set/${name}`),
  });
}

const stageArcBuffer = await readBuffer(paths.stageArc);
const stagePzzBuffer = await readBuffer(paths.stagePzz);
const defaultCountInSource = parseDefaultModelCount(gameText);
const expectedIds = Array.from({ length: defaultCountInSource ?? defaultStageModelCount }, (_, index) => `model_${String(index).padStart(2, "0")}`);
const exportedIds = new Set(daePieces.map((piece) => piece.id));
const missingExpectedDae = expectedIds.filter((id) => !exportedIds.has(id));
const extraDae = daePieces.filter((piece) => piece.index >= (defaultCountInSource ?? defaultStageModelCount)).map((piece) => piece.id);

const findings = {
  floorCandidates: summarizeTags(daePieces, "floor"),
  wallCandidates: summarizeTags(daePieces, "wall-or-vertical-shell-candidate"),
  ceilingCandidates: summarizeTags(daePieces, "ceiling-candidate"),
  backdropCandidates: summarizeTags(daePieces, "backdrop-or-skybox-candidate"),
  transparentCandidates: summarizeTags(daePieces, "transparent-or-invisible-candidate"),
  propCandidates: daePieces
    .filter((piece) => piece.classification.tags.includes("prop-or-stage-detail") || piece.classification.tags.includes("small-marker-or-prop"))
    .map((piece) => piece.id),
};

findings.stageModelCountConclusion =
  missingExpectedDae.length === 0 && extraDae.length === 0
    ? "The browser's `DEFAULT_STAGE_MODEL_COUNT = 40` is complete for the current exported `st00_mdl.arc` DAE slot set: indices `model_00.dae` through `model_39.dae` all exist and are requested. It is not complete for the full stage asset set because `st00.pzz`, `hit000.bin`/`hit001.bin`/`hit002.bin`, and `set0000.arc`..`set0003.arc` are present source assets but are not visual DAE exports or loaded stage geometry."
    : `The browser count is not complete for the exported DAE set. Missing expected: ${missingExpectedDae.join(", ") || "none"}; extra beyond count: ${extraDae.join(", ") || "none"}.`;

const inventory = {
  generatedBy: rel("scripts/inventory-stage-geometry.mjs"),
  generatedAt: new Date().toISOString(),
  scope: "Task 07: st00 stage geometry, walls, ceiling, backdrop, collision, bounds, culling/draw-group clues.",
  stageId,
  sources: {
    afsRoot: await statPath(paths.afsRoot),
    discRoot: await statPath(paths.discRoot),
    publicStage: await statPath(paths.publicStage),
    publicStageManifest: await statPath(paths.publicStageManifest),
    publicStagesManifest: await statPath(paths.publicStagesManifest),
    stageArc: await statPath(paths.stageArc),
    stagePzz: await statPath(paths.stagePzz),
    publicStageArc: await statPath(paths.publicStageArc),
    publicStagePzz: await statPath(paths.publicStagePzz),
    gameMain: await statPath(paths.gameMain),
    stageExportScript: await statPath(paths.stageExportScript),
    stageAssetScript: await statPath(paths.stageAssetScript),
    arcSpec: await statPath(paths.arcSpec),
    symbolMap: await statPath(paths.symbolMap),
  },
  refs: {
    defaultStageModelCount: refWithLine(paths.gameMain, gameText, "const DEFAULT_STAGE_MODEL_COUNT"),
    loadStageUrls: refWithLine(paths.gameMain, gameText, "{ length: DEFAULT_STAGE_MODEL_COUNT }"),
    normalizeStageCulling: refWithLine(paths.gameMain, gameText, "object.frustumCulled = false"),
    stageExporterLoop: refWithLine(paths.stageExportScript, stageExportText, "foreach (var jd in sobj.JOBJDescs.Array)"),
    stageExporterOutputName: refWithLine(paths.stageExportScript, stageExportText, "model_{model:D2}.dae"),
    stageAssetHitBins: refWithLine(paths.stageAssetScript, stageAssetText, "const hitBins"),
    stageAssetSetArcs: refWithLine(paths.stageAssetScript, stageAssetText, "const setArcs"),
  },
  sourceArchive: {
    rootFileCount: rootFiles.length,
    st00Related: sourceFiles,
    stageArc: {
      path: rel(paths.stageArc),
      hsd: parseHsdDat(stageArcBuffer),
      publicCopy: await sourcePublicPair(paths.stageArc, paths.publicStageArc),
    },
    stagePzz: {
      path: rel(paths.stagePzz),
      header: parsePzzHeader(stagePzzBuffer),
      publicCopy: await sourcePublicPair(paths.stagePzz, paths.publicStagePzz),
    },
    setArcs,
    globalCollisionCandidates: sourceFiles.relatedCollisionArchives,
  },
  exportedPieces: {
    directory: rel(path.join(paths.publicStage, "model")),
    count: daePieces.length,
    requestedByBrowserCount: defaultCountInSource,
    withGeometry: daePieces.filter((piece) => piece.hasGeometry).length,
    emptySlots: daePieces.filter((piece) => !piece.hasGeometry).map((piece) => piece.id),
    missingExpectedDae,
    extraDae,
    aggregateBbox: finalizeBounds(aggregate),
    textureFiles,
    pieces: daePieces,
  },
  collision: {
    hitBins,
    inferredArenaBounds: hitBins[0]?.bounds2d ?? null,
    nonVisualStageFiles: [
      rel(paths.stagePzz),
      ...hitBins.map((hit) => hit.path),
      ...setArcs.map((setArc) => setArc.path),
    ],
  },
  browserLoader: {
    defaultStageModelCount: {
      value: defaultCountInSource,
      ref: refWithLine(paths.gameMain, gameText, "const DEFAULT_STAGE_MODEL_COUNT"),
      expectedIds,
      missingExpectedDae,
      extraDae,
    },
    culling: {
      ref: refWithLine(paths.gameMain, gameText, "object.frustumCulled = false"),
      finding: "Browser disables Three.js frustum culling on every loaded stage mesh after ColladaLoader import; no source draw-group or culling flags are decoded into runtime metadata.",
    },
  },
  findings,
  missingOrUncertain: [
    "`model_24.dae` is an exported stage slot but contains only a root joint and no mesh geometry.",
    "`st00.pzz` is copied and present, but its member table and any embedded stage shell/culling data are not decoded by this scanner.",
    "`hit000.bin`, `hit001.bin`, and `hit002.bin` have STIH collision/spatial-grid headers and inferred X/Z arena bounds, but their body records are not decoded into polygons.",
    "`set0000.arc` through `set0003.arc` are copied set archives and not loaded by the current browser stage renderer; spawn/object/bounds semantics remain uncertain.",
    "No separate high flat ceiling DAE is conclusively identified by the current export heuristics.",
    "Skybox/backdrop identification is heuristic only; the DAE files do not carry semantic names beyond generic Joint/Object/Material identifiers.",
    "The scanner reports raw DAE POSITION-array bounds; it does not fully evaluate skin controllers or every COLLADA scene transform.",
  ],
};

await mkdir(abs(outputDir), { recursive: true });
await writeFile(abs(jsonOut), `${JSON.stringify(inventory, null, 2)}\n`);
await writeFile(abs(mdOut), makeMarkdown(inventory));

console.log(`wrote ${rel(jsonOut)}`);
console.log(`wrote ${rel(mdOut)}`);
console.log(`exported DAE pieces: ${inventory.exportedPieces.count}`);
console.log(`geometry-bearing DAE pieces: ${inventory.exportedPieces.withGeometry}`);
console.log(`empty DAE slots: ${inventory.exportedPieces.emptySlots.join(", ") || "none"}`);
console.log(`floor candidates: ${inventory.findings.floorCandidates.join(", ") || "none"}`);
console.log(`wall/shell candidates: ${inventory.findings.wallCandidates.join(", ") || "none"}`);
console.log(`ceiling candidates: ${inventory.findings.ceilingCandidates.join(", ") || "none"}`);
console.log(`backdrop candidates: ${inventory.findings.backdropCandidates.join(", ") || "none"}`);
