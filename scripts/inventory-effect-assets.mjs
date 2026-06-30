#!/usr/bin/env node

import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const inputRoots = [
  "user-data/GG4E/afs_data/root",
  "user-data/GG4E/disc",
  "research/format-specs",
  "packages/assets/data",
];

const outputJsonPath = path.join(
  repoRoot,
  "research/asset-inventory/weapons-effects-projectiles.json",
);
const outputMarkdownPath = path.join(
  repoRoot,
  "research/asset-inventory/weapons-effects-projectiles.md",
);

const familyNames = [
  "sword/blade",
  "fire/flame",
  "gun/bullet",
  "beam/laser",
  "muzzle",
  "impact/explosion",
  "aura/trail",
  "UI reticle/target",
];

const familyTerms = {
  "sword/blade": [
    "sword",
    "blade",
    "slash",
    "samurai",
    "knight",
    "axe",
    "hatchet",
    "chainsaw",
    "claw",
    "spike",
    "musashi",
  ],
  "fire/flame": ["fire", "flame", "burn", "blaze", "phoenix"],
  "gun/bullet": [
    "gun",
    "bullet",
    "gatling",
    "revolver",
    "cannon",
    "tank",
    "arrow",
    "shuriken",
    "missile",
    "icbm",
    "bomb",
    "bomber",
    "fighter",
    "saucer",
    "projectile",
  ],
  "beam/laser": ["beam", "laser", "plasma"],
  muzzle: [
    "muzzle",
    "flash",
    "shot",
    "gun",
    "gatling",
    "revolver",
    "cannon",
    "tank",
    "beam",
    "laser",
    "fighter",
  ],
  "impact/explosion": [
    "hit",
    "impact",
    "explosion",
    "explode",
    "blast",
    "bomb",
    "bomber",
    "missile",
    "icbm",
    "cannon",
  ],
  "aura/trail": [
    "aura",
    "trail",
    "boost",
    "wing",
    "jet",
    "ghost",
    "shadow",
    "cyber",
    "flame",
    "beam",
    "plasma",
  ],
  "UI reticle/target": [
    "reticle",
    "target",
    "cursor",
    "crosshair",
    "lock",
    "aim",
    "icon",
    "arrow",
  ],
};

const tplFormats = new Map([
  [0, "I4"],
  [1, "I8"],
  [2, "IA4"],
  [3, "IA8"],
  [4, "RGB565"],
  [5, "RGB5A3"],
  [6, "RGBA8"],
  [8, "C4"],
  [9, "C8"],
  [10, "C14X2"],
  [14, "CMPR"],
]);

const confidenceRank = { High: 3, Medium: 2, Low: 1 };
const motCache = new Map();
const binaryMetaCache = new Map();

function toRepoPath(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

function isInsideInput(relPath) {
  return inputRoots.some((root) => relPath === root || relPath.startsWith(`${root}/`));
}

async function walkFiles(root) {
  const results = [];

  async function visit(current) {
    let entries;
    try {
      entries = await fs.readdir(current, { withFileTypes: true });
    } catch (error) {
      if (error.code === "ENOENT") return;
      throw error;
    }

    for (const entry of entries) {
      const abs = path.join(current, entry.name);
      if (entry.isDirectory()) {
        await visit(abs);
        continue;
      }
      if (!entry.isFile()) continue;
      const stat = await fs.stat(abs);
      const rel = toRepoPath(abs);
      if (isInsideInput(rel)) {
        results.push({
          abs,
          path: rel,
          name: entry.name,
          base: path.basename(entry.name, path.extname(entry.name)),
          ext: path.extname(entry.name).toLowerCase(),
          sizeBytes: stat.size,
        });
      }
    }
  }

  await visit(path.join(repoRoot, root));
  return results;
}

async function readJson(relPath) {
  const text = await fs.readFile(path.join(repoRoot, relPath), "utf8");
  return JSON.parse(text);
}

function extractBorgId(name) {
  const match = /^(?:pl|it)([0-9a-f]{4})([a-z]?)(?:_|mot|hit|data|\.|$)/i.exec(name);
  if (!match) return null;
  return {
    id: `pl${match[1].toLowerCase()}`,
    sourcePrefix: name.slice(0, 2).toLowerCase(),
    suffix: match[2]?.toLowerCase() || "",
  };
}

function fileRole(file) {
  const lower = file.name.toLowerCase();
  if (lower.endsWith("_mdl.arc")) return "HSD model";
  if (lower.endsWith("_mdl.arz")) return "compressed model archive";
  if (lower.endsWith("mot.bin")) return "animation/motion bank";
  if (lower.endsWith("hit.bin") || /^hit[0-9a-f]+\.bin$/i.test(lower) || lower.startsWith("comhit")) {
    return "hit/impact data";
  }
  if (lower.endsWith("data.bin")) return "borg data table";
  if (file.ext === ".tpl") return "texture";
  if (file.ext === ".txg") return "particle image container";
  if (file.ext === ".ptl") return "particle settings";
  if (file.ext === ".ref") return "particle references";
  if (file.ext === ".pzz") return "compressed archive";
  if (file.ext === ".arc") return "HSD/archive model";
  if (file.ext === ".bin") return "binary data";
  return file.ext ? `${file.ext.slice(1)} file` : "file";
}

function inferNeededScripts(file) {
  const lower = file.name.toLowerCase();
  const needs = [];

  if (file.ext === ".pzz") {
    needs.push("PZZ unpack/list integration before browser conversion");
  }
  if (file.ext === ".arz") {
    needs.push("ARZ decompression/list integration before model export");
  }
  if (file.ext === ".txg" || file.ext === ".ptl" || file.ext === ".ref") {
    needs.push("PTL/REF/TXG particle parser and TXG image decoder");
  }
  if (lower.endsWith("_mdl.arc") || lower.endsWith("_mdl.arz") || lower === "arrow_mdl.arc") {
    needs.push("HSD model export path to DAE/GLB for effect, projectile, and attachment meshes");
  }
  if (file.ext === ".tpl") {
    needs.push("TPL texture decode to PNG/KTX2 for browser use");
  }
  if (
    lower.endsWith("hit.bin") ||
    /^hit[0-9a-f]+\.bin$/i.test(lower) ||
    lower.startsWith("comhit") ||
    lower.endsWith("data.bin")
  ) {
    needs.push("hit/data BIN schema parser for collision, impact, and weapon metadata");
  }
  if (lower.endsWith("mot.bin")) {
    needs.push("MOT bank semantic labels for attack/projectile timing");
  }

  return [...new Set(needs)];
}

async function parseTpl(file) {
  const buffer = await fs.readFile(file.abs);
  if (buffer.length < 12) return { parseStatus: "too small for TPL header" };

  const magic = buffer.readUInt32BE(0);
  if (magic !== 0x0020af30) {
    return { parseStatus: `unexpected magic 0x${magic.toString(16).padStart(8, "0")}` };
  }

  const imageCount = buffer.readUInt32BE(4);
  const imageTableOffset = buffer.readUInt32BE(8);
  const images = [];
  const maxImages = Math.min(imageCount, 64);

  for (let i = 0; i < maxImages; i += 1) {
    const entryOffset = imageTableOffset + i * 8;
    if (entryOffset + 8 > buffer.length) break;

    const textureHeaderOffset = buffer.readUInt32BE(entryOffset);
    const paletteHeaderOffset = buffer.readUInt32BE(entryOffset + 4);
    if (textureHeaderOffset + 12 > buffer.length) {
      images.push({
        index: i,
        parseStatus: "texture header outside file",
        textureHeaderOffset,
        paletteHeaderOffset,
      });
      continue;
    }

    const height = buffer.readUInt16BE(textureHeaderOffset);
    const width = buffer.readUInt16BE(textureHeaderOffset + 2);
    const formatCode = buffer.readUInt32BE(textureHeaderOffset + 4);
    const dataOffset = buffer.readUInt32BE(textureHeaderOffset + 8);
    images.push({
      index: i,
      width,
      height,
      format: tplFormats.get(formatCode) || `unknown(${formatCode})`,
      formatCode,
      dataOffset,
      textureHeaderOffset,
      paletteHeaderOffset: paletteHeaderOffset || null,
    });
  }

  return {
    parseStatus: images.length === imageCount ? "ok" : "partial",
    imageCount,
    imageTableOffset,
    images,
  };
}

async function parseTxg(file) {
  const buffer = await fs.readFile(file.abs);
  if (buffer.length < 8) return { parseStatus: "too small for TXG offset table" };

  const entryCount = buffer.readUInt32BE(0);
  const offsets = [];
  const maxEntries = Math.min(entryCount, 128);
  for (let i = 0; i < maxEntries; i += 1) {
    const off = 4 + i * 4;
    if (off + 4 > buffer.length) break;
    const value = buffer.readUInt32BE(off);
    if (value !== 0xffffffff) offsets.push(value);
  }

  const saneOffsets =
    entryCount > 0 &&
    entryCount <= 128 &&
    offsets.every((value) => value >= 0 && value < buffer.length) &&
    offsets.slice(1).every((value, index) => value >= offsets[index]);

  return {
    parseStatus: saneOffsets ? "offset table plausible" : "offset table needs reverse engineering",
    entryCount,
    offsets,
  };
}

async function parseArc(file) {
  const buffer = await fs.readFile(file.abs);
  if (buffer.length < 0x20) return { parseStatus: "too small for HSD header" };

  const first = buffer.readUInt32BE(0);
  const bareLooksHsd = first === buffer.length;
  const wrappedLooksHsd =
    buffer.length >= 0x120 &&
    first === 0x100 &&
    buffer.readUInt32BE(0x100) === buffer.length - 0x100;

  const baseOffset = wrappedLooksHsd ? 0x100 : 0;
  if (!bareLooksHsd && !wrappedLooksHsd) {
    return { parseStatus: "not recognized as bare/wrapped HSD DAT header" };
  }

  return {
    parseStatus: "HSD DAT header recognized",
    container: wrappedLooksHsd ? "wrapped HSD DAT" : "bare HSD DAT",
    hsdOffset: baseOffset,
    hsdFileSize: buffer.readUInt32BE(baseOffset),
    dataBlockSize: buffer.readUInt32BE(baseOffset + 4),
    relocCount: buffer.readUInt32BE(baseOffset + 8),
    rootCount: buffer.readUInt32BE(baseOffset + 12),
    externalRefCount: buffer.readUInt32BE(baseOffset + 16),
  };
}

async function parseMot(file) {
  if (motCache.has(file.path)) return motCache.get(file.path);

  const buffer = await fs.readFile(file.abs);
  if (buffer.length < 0x18) {
    const result = { parseStatus: "too small for MOT master table" };
    motCache.set(file.path, result);
    return result;
  }

  const bankOffsets = [];
  for (let i = 0; i < 6; i += 1) bankOffsets.push(buffer.readUInt32BE(i * 4));

  const banks = bankOffsets.map((offset, bankIndex) => {
    if (offset === 0 || offset >= buffer.length) {
      return { bankIndex, tableOffset: offset, parseStatus: "missing/outside file", clipCount: 0 };
    }

    const clipOffsets = [];
    let emptySlots = 0;
    let cursor = offset;
    for (let slot = 0; slot < 512 && cursor + 4 <= buffer.length; slot += 1, cursor += 4) {
      const value = buffer.readUInt32BE(cursor);
      if (value === 0xffffffff) {
        return {
          bankIndex,
          tableOffset: offset,
          parseStatus: "ok",
          clipCount: clipOffsets.length,
          emptySlots,
          firstClipOffset: clipOffsets[0] ?? null,
          clipOffsets: clipOffsets.slice(0, 24),
        };
      }
      if (value === 0) emptySlots += 1;
      else clipOffsets.push(value);
    }

    return {
      bankIndex,
      tableOffset: offset,
      parseStatus: "unterminated table",
      clipCount: clipOffsets.length,
      emptySlots,
      firstClipOffset: clipOffsets[0] ?? null,
      clipOffsets: clipOffsets.slice(0, 24),
    };
  });

  const result = {
    parseStatus: banks.every((bank) => bank.parseStatus === "ok") ? "ok" : "partial",
    bankOffsets,
    banks,
    totalClipCount: banks.reduce((sum, bank) => sum + bank.clipCount, 0),
  };
  motCache.set(file.path, result);
  return result;
}

async function binaryMetadata(file) {
  if (binaryMetaCache.has(file.path)) return binaryMetaCache.get(file.path);

  let result = null;
  const lower = file.name.toLowerCase();
  if (file.ext === ".tpl") result = { texture: await parseTpl(file) };
  else if (file.ext === ".txg") result = { txg: await parseTxg(file) };
  else if (lower.endsWith("_mdl.arc") || file.ext === ".arc") result = { model: await parseArc(file) };
  else if (lower.endsWith("mot.bin")) result = { mot: await parseMot(file) };

  binaryMetaCache.set(file.path, result);
  return result;
}

function collectTermMatches(haystack, terms) {
  const found = [];
  for (const term of terms) {
    if (haystack.includes(term)) found.push(term);
  }
  return found;
}

function scoreToConfidence(score) {
  if (score >= 7) return "High";
  if (score >= 4) return "Medium";
  return "Low";
}

function addFamilySignal(signals, family, score, reason) {
  const existing = signals.get(family);
  if (existing) {
    existing.score += score;
    existing.reasons.push(reason);
    return;
  }
  signals.set(family, { family, score, reasons: [reason] });
}

function classifyFile(file, borgMap) {
  const lowerName = file.name.toLowerCase();
  const lowerPath = file.path.toLowerCase();
  const role = fileRole(file);
  const signals = new Map();
  const borgRef = extractBorgId(file.name);
  const linkedBorg = borgRef ? borgMap.get(borgRef.id) : null;
  const borgHaystack = linkedBorg
    ? `${linkedBorg.name} ${linkedBorg.tribe} ${linkedBorg.type}`.toLowerCase()
    : "";

  for (const family of familyNames) {
    const nameMatches = collectTermMatches(lowerName, familyTerms[family]);
    if (nameMatches.length > 0) {
      addFamilySignal(
        signals,
        family,
        nameMatches.length >= 2 ? 5 : 4,
        `filename contains ${nameMatches.join(", ")}`,
      );
    }

    if (linkedBorg) {
      const borgMatches = collectTermMatches(borgHaystack, familyTerms[family]);
      if (borgMatches.length > 0) {
        addFamilySignal(
          signals,
          family,
          borgMatches.length >= 2 ? 5 : 4,
          `linked Borg ${linkedBorg.id} (${linkedBorg.name}) metadata contains ${borgMatches.join(", ")}`,
        );
      }
    }
  }

  if (/^efct/i.test(file.name)) {
    for (const family of ["fire/flame", "beam/laser", "muzzle", "impact/explosion", "aura/trail"]) {
      addFamilySignal(signals, family, 5, "global efct asset prefix is a likely shared battle-effect lead");
    }
  }

  if (/^ptcl00\./i.test(file.name)) {
    for (const family of ["fire/flame", "muzzle", "impact/explosion", "aura/trail", "beam/laser"]) {
      addFamilySignal(signals, family, 5, "ptcl00 particle asset prefix and TXG/PTL/REF particle formats");
    }
  }

  if (/^(hit[0-9a-f]+|comhit2?)\.bin$/i.test(file.name) || lowerName.endsWith("hit.bin")) {
    addFamilySignal(signals, "impact/explosion", 6, "hit/comhit binary naming is direct impact/collision evidence");
  }

  if (lowerName === "arrow_mdl.arc") {
    addFamilySignal(signals, "gun/bullet", 7, "arrow_mdl.arc is a direct projectile model name");
    addFamilySignal(signals, "UI reticle/target", 3, "arrow name can also support targeting UI/indicator investigation");
  }

  if (lowerName === "as_icon.tpl" || lowerName === "icon.bin" || /^vs[0-9a-f]+\.tpl$/i.test(lowerName)) {
    addFamilySignal(signals, "UI reticle/target", 4, "UI-like icon/versus texture naming");
  }

  if (linkedBorg) {
    if (linkedBorg.type?.toLowerCase().includes("long range") || Number(linkedBorg.shot) >= 4) {
      addFamilySignal(
        signals,
        "gun/bullet",
        2,
        `linked Borg is ranged/shot-capable (${linkedBorg.type}, shot ${linkedBorg.shot})`,
      );
      addFamilySignal(
        signals,
        "muzzle",
        2,
        `linked Borg is ranged/shot-capable (${linkedBorg.type}, shot ${linkedBorg.shot})`,
      );
    }
    if (linkedBorg.type?.toLowerCase().includes("short range") && Number(linkedBorg.attack) >= 4) {
      addFamilySignal(
        signals,
        "sword/blade",
        2,
        `linked Borg is short-range/high-attack (${linkedBorg.type}, attack ${linkedBorg.attack})`,
      );
    }
  }

  const isLikelyAssetType =
    lowerName.endsWith("_mdl.arc") ||
    lowerName.endsWith("_mdl.arz") ||
    lowerName.endsWith("mot.bin") ||
    lowerName.endsWith("hit.bin") ||
    lowerName.endsWith("data.bin") ||
    file.ext === ".pzz" ||
    file.ext === ".tpl" ||
    file.ext === ".txg" ||
    file.ext === ".ptl" ||
    file.ext === ".ref" ||
    /^hit[0-9a-f]+\.bin$/i.test(lowerName) ||
    /^comhit2?\.bin$/i.test(lowerName);

  if (signals.size === 0 || !isLikelyAssetType) return null;

  const families = [...signals.values()]
    .map((signal) => ({
      family: signal.family,
      confidence: scoreToConfidence(signal.score),
      score: signal.score,
      reason: [...new Set(signal.reasons)].join("; "),
    }))
    .sort((a, b) => {
      const conf = confidenceRank[b.confidence] - confidenceRank[a.confidence];
      if (conf !== 0) return conf;
      return b.score - a.score || a.family.localeCompare(b.family);
    });

  const attachmentLead = inferAttachmentLead(file, borgRef, linkedBorg, lowerName);

  return {
    path: file.path,
    fileType: {
      extension: file.ext || null,
      role,
    },
    sizeBytes: file.sizeBytes,
    linkedBorgId: linkedBorg?.id ?? borgRef?.id ?? null,
    linkedBorgName: linkedBorg?.name ?? null,
    linkedBorgNumber: linkedBorg?.number ?? null,
    families,
    confidence: families[0]?.confidence ?? "Low",
    reason: families[0]?.reason ?? "candidate from filename/metadata scan",
    attachmentLead,
    needs: inferNeededScripts(file),
  };
}

function inferAttachmentLead(file, borgRef, linkedBorg, lowerName) {
  if (!borgRef && lowerName !== "arrow_mdl.arc") return null;

  const parts = [];
  if (borgRef?.sourcePrefix === "it") {
    parts.push("item-model archive is a strong weapon/projectile/attachment lead");
  }
  if (borgRef?.suffix) {
    parts.push(`pl model suffix '${borgRef.suffix}' is a part/LOD/attachment lead from HSD format notes`);
  }
  if (lowerName.endsWith("mot.bin")) {
    parts.push("motion banks can expose attack/projectile timing once bank semantics are labelled");
  }
  if (lowerName.endsWith("hit.bin")) {
    parts.push("hit binary can expose collision/impact attachment timing once parsed");
  }
  if (lowerName.endsWith("data.bin")) {
    parts.push("data binary may carry weapon/action metadata once parsed");
  }
  if (lowerName === "arrow_mdl.arc") {
    parts.push("standalone arrow model is a direct projectile/attachment lead");
  }
  if (linkedBorg) {
    parts.push(`linked to ${linkedBorg.id} ${linkedBorg.name}`);
  }

  return parts.length > 0 ? parts.join("; ") : null;
}

function groupByFamily(candidates) {
  const grouped = Object.fromEntries(familyNames.map((family) => [family, []]));

  for (const candidate of candidates) {
    for (const familyEntry of candidate.families) {
      grouped[familyEntry.family].push({
        path: candidate.path,
        fileType: candidate.fileType,
        sizeBytes: candidate.sizeBytes,
        linkedBorgId: candidate.linkedBorgId,
        linkedBorgName: candidate.linkedBorgName,
        confidence: familyEntry.confidence,
        reason: familyEntry.reason,
        attachmentLead: candidate.attachmentLead,
        needs: candidate.needs,
      });
    }
  }

  for (const family of familyNames) {
    grouped[family].sort(compareCandidateLike);
  }

  return grouped;
}

function compareCandidateLike(a, b) {
  const conf = confidenceRank[b.confidence] - confidenceRank[a.confidence];
  if (conf !== 0) return conf;
  return b.sizeBytes - a.sizeBytes || a.path.localeCompare(b.path);
}

function extensionCounts(files) {
  const counts = {};
  for (const file of files) {
    const ext = file.ext || "(none)";
    counts[ext] = (counts[ext] || 0) + 1;
  }
  return Object.fromEntries(Object.entries(counts).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0])));
}

function summarizeArchives(files) {
  const archiveFiles = files.filter((file) => [".pzz", ".arz", ".arc"].includes(file.ext));
  const archiveDirs = files
    .map((file) => path.dirname(file.path))
    .filter((dir) => /\.(pzz|arz|arc)(\/|$)/i.test(dir));

  return {
    archiveLikeFileCount: archiveFiles.length,
    byExtension: extensionCounts(archiveFiles),
    alreadyUnpackedArchiveDirectoryCount: new Set(archiveDirs).size,
    note:
      archiveDirs.length > 0
        ? "Found files under directories named like archives; these were included in the scan."
        : "No already-unpacked archive subdirectories were visible under the contracted input roots.",
  };
}

function scriptNeeds(candidates, files) {
  const needs = new Map();
  for (const candidate of candidates) {
    for (const need of candidate.needs) {
      const entry = needs.get(need) || { need, candidateCount: 0, examples: [] };
      entry.candidateCount += 1;
      if (entry.examples.length < 8) entry.examples.push(candidate.path);
      needs.set(need, entry);
    }
  }

  const pzzCount = files.filter((file) => file.ext === ".pzz").length;
  const arzCount = files.filter((file) => file.ext === ".arz").length;
  if (pzzCount > 0 && !needs.has("PZZ unpack/list integration before browser conversion")) {
    needs.set("PZZ unpack/list integration before browser conversion", {
      need: "PZZ unpack/list integration before browser conversion",
      candidateCount: pzzCount,
      examples: files.filter((file) => file.ext === ".pzz").slice(0, 8).map((file) => file.path),
    });
  }
  if (arzCount > 0 && !needs.has("ARZ decompression/list integration before model export")) {
    needs.set("ARZ decompression/list integration before model export", {
      need: "ARZ decompression/list integration before model export",
      candidateCount: arzCount,
      examples: files.filter((file) => file.ext === ".arz").slice(0, 8).map((file) => file.path),
    });
  }

  return [...needs.values()].sort((a, b) => b.candidateCount - a.candidateCount || a.need.localeCompare(b.need));
}

function formatBytes(bytes) {
  if (bytes >= 1024 * 1024) return `${(bytes / 1024 / 1024).toFixed(2)} MiB`;
  if (bytes >= 1024) return `${(bytes / 1024).toFixed(1)} KiB`;
  return `${bytes} B`;
}

function familyCounts(grouped) {
  return Object.fromEntries(familyNames.map((family) => [family, grouped[family].length]));
}

async function buildTextureCatalog(files) {
  const textures = [];
  for (const file of files.filter((entry) => entry.ext === ".tpl" || entry.ext === ".txg")) {
    const metadata = await binaryMetadata(file);
    textures.push({
      path: file.path,
      fileType: file.ext === ".tpl" ? "TPL texture" : "TXG particle image container",
      sizeBytes: file.sizeBytes,
      ...(metadata || {}),
    });
  }
  return textures.sort((a, b) => a.path.localeCompare(b.path));
}

async function enrichCandidates(candidates, fileByPath) {
  for (const candidate of candidates) {
    const file = fileByPath.get(candidate.path);
    const metadata = file ? await binaryMetadata(file) : null;
    if (metadata) {
      candidate.metadata = metadata;
    }
  }
}

function buildAttachmentLeads(candidates) {
  const byBorg = new Map();

  for (const candidate of candidates) {
    if (!candidate.linkedBorgId || !candidate.attachmentLead) continue;
    const entry =
      byBorg.get(candidate.linkedBorgId) ||
      {
        linkedBorgId: candidate.linkedBorgId,
        linkedBorgName: candidate.linkedBorgName,
        families: new Set(),
        files: [],
        notes: new Set(),
        mot: null,
      };

    for (const family of candidate.families) entry.families.add(family.family);
    entry.files.push({
      path: candidate.path,
      role: candidate.fileType.role,
      sizeBytes: candidate.sizeBytes,
      confidence: candidate.confidence,
    });
    entry.notes.add(candidate.attachmentLead);
    if (candidate.metadata?.mot) entry.mot = candidate.metadata.mot;
    byBorg.set(candidate.linkedBorgId, entry);
  }

  return [...byBorg.values()]
    .map((entry) => ({
      linkedBorgId: entry.linkedBorgId,
      linkedBorgName: entry.linkedBorgName,
      families: [...entry.families].sort(),
      files: entry.files.sort(compareCandidateLike).slice(0, 20),
      notes: [...entry.notes].slice(0, 12),
      motSummary: entry.mot
        ? {
            totalClipCount: entry.mot.totalClipCount,
            banks: entry.mot.banks.map((bank) => ({
              bankIndex: bank.bankIndex,
              clipCount: bank.clipCount,
              emptySlots: bank.emptySlots,
              firstClipOffset: bank.firstClipOffset,
            })),
          }
        : null,
    }))
    .sort((a, b) => b.files.length - a.files.length || a.linkedBorgId.localeCompare(b.linkedBorgId));
}

function mdEscape(value) {
  return String(value ?? "").replaceAll("|", "\\|");
}

function summarizeTexture(texture) {
  if (texture.texture?.images?.length) {
    const first = texture.texture.images[0];
    const suffix = texture.texture.imageCount > 1 ? ` +${texture.texture.imageCount - 1} more` : "";
    return `${first.width}x${first.height} ${first.format}${suffix}`;
  }
  if (texture.txg) {
    return `${texture.txg.entryCount} TXG entries (${texture.txg.parseStatus})`;
  }
  return "unparsed";
}

function candidateLine(candidate) {
  const borg = candidate.linkedBorgId ? `${candidate.linkedBorgId} ${candidate.linkedBorgName ?? ""}`.trim() : "-";
  return `| \`${mdEscape(candidate.path)}\` | ${mdEscape(candidate.fileType.role)} | ${formatBytes(
    candidate.sizeBytes,
  )} | ${mdEscape(borg)} | ${candidate.confidence} | ${mdEscape(candidate.reason)} |`;
}

function buildMarkdown(report) {
  const lines = [];
  lines.push("# Weapons, Effects, Projectiles Asset Inventory");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Inputs scanned");
  lines.push("");
  for (const input of report.inputs) lines.push(`- \`${input}\``);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Files scanned: ${report.summary.fileCount}`);
  lines.push(`- Candidates: ${report.summary.candidateCount}`);
  lines.push(`- Texture files parsed/catalogued: ${report.summary.textureCount}`);
  lines.push(`- Archive observation: ${report.archiveInventory.note}`);
  lines.push("");
  lines.push("Family counts:");
  lines.push("");
  for (const [family, count] of Object.entries(report.summary.familyCounts)) {
    lines.push(`- ${family}: ${count}`);
  }

  lines.push("");
  lines.push("## High-signal family leads");
  for (const family of familyNames) {
    const entries = report.families[family].slice(0, 12);
    lines.push("");
    lines.push(`### ${family}`);
    if (entries.length === 0) {
      lines.push("");
      lines.push("No candidates found by this filename/metadata pass.");
      continue;
    }
    lines.push("");
    lines.push("| Path | Type | Size | Borg | Confidence | Reason |");
    lines.push("|---|---:|---:|---|---|---|");
    for (const candidate of entries) lines.push(candidateLine(candidate));
  }

  lines.push("");
  lines.push("## Texture scan");
  lines.push("");
  lines.push("| Path | Size | Parsed texture data |");
  lines.push("|---|---:|---|");
  for (const texture of report.textureCatalog.slice(0, 20)) {
    lines.push(`| \`${mdEscape(texture.path)}\` | ${formatBytes(texture.sizeBytes)} | ${mdEscape(summarizeTexture(texture))} |`);
  }
  if (report.textureCatalog.length > 20) {
    lines.push(`| ... | ... | ${report.textureCatalog.length - 20} more texture entries are in the JSON catalog |`);
  }

  lines.push("");
  lines.push("## Attachment and weapon-bone leads");
  lines.push("");
  lines.push(
    "No named weapon bones are visible from the contracted filename-level inputs. The actionable leads are Borg-linked `pl####` model suffixes, `it####_mdl.arz` item model archives, `pl####mot.bin` motion banks, and `pl####hit.bin` hit data. Actual JOBJ/bone names still require HSD model export/inspection.",
  );
  lines.push("");
  lines.push("| Borg | Families | Representative files | MOT clips | Notes |");
  lines.push("|---|---|---|---:|---|");
  for (const lead of report.attachmentWeaponBoneLeads.slice(0, 20)) {
    const files = lead.files
      .slice(0, 6)
      .map((file) => `\`${file.path}\``)
      .join("<br>");
    const motClips = lead.motSummary?.totalClipCount ?? "";
    lines.push(
      `| ${mdEscape(`${lead.linkedBorgId} ${lead.linkedBorgName ?? ""}`.trim())} | ${mdEscape(
        lead.families.join(", "),
      )} | ${files} | ${motClips} | ${mdEscape(lead.notes[0] ?? "")} |`,
    );
  }

  lines.push("");
  lines.push("## Needs extraction/conversion scripts");
  lines.push("");
  for (const need of report.needsExtractionConversion) {
    lines.push(`- ${need.need}: ${need.candidateCount} candidate(s). Examples: ${need.examples.map((example) => `\`${example}\``).join(", ")}`);
  }

  lines.push("");
  lines.push("## Concise findings");
  lines.push("");
  lines.push("- `efct.pzz`, `efct00.tpl`, `efct00_mdl.arc`, and `efct01_mdl.arc` are the strongest shared effect leads.");
  lines.push("- `ptcl00.ptl`, `ptcl00.ref`, and `ptcl00.txg` are real particle-system leads; TXG exposes a plausible offset table but needs a decoder.");
  lines.push("- `hit*.bin`, `comhit.bin`, `comhit2.bin`, and per-Borg `pl####hit.bin` are real impact/collision data leads.");
  lines.push("- `it####_mdl.arz` files linked to weapon-like Borg IDs are strong compressed attachment/projectile model leads and need ARZ decompression before HSD export.");
  lines.push("- `pl####mot.bin` files parse as MOT bank tables and provide attack-timing leads, but clip semantics still need labels.");
  lines.push("");

  return `${lines.join("\n")}\n`;
}

async function main() {
  const files = (await Promise.all(inputRoots.map((root) => walkFiles(root))))
    .flat()
    .sort((a, b) => a.path.localeCompare(b.path));

  const borgData = await readJson("packages/assets/data/borgs.json");
  const borgMap = new Map((borgData.borgs || []).map((borg) => [borg.id.toLowerCase(), borg]));
  const fileByPath = new Map(files.map((file) => [file.path, file]));

  const candidates = files
    .map((file) => classifyFile(file, borgMap))
    .filter(Boolean)
    .sort(compareCandidateLike);

  await enrichCandidates(candidates, fileByPath);

  const families = groupByFamily(candidates);
  const textureCatalog = await buildTextureCatalog(files);
  const attachmentWeaponBoneLeads = buildAttachmentLeads(candidates);

  const report = {
    generatedAt: new Date().toISOString(),
    scanner: toRepoPath(fileURLToPath(import.meta.url)),
    inputs: inputRoots,
    summary: {
      fileCount: files.length,
      candidateCount: candidates.length,
      textureCount: textureCatalog.length,
      extensionCounts: extensionCounts(files),
      familyCounts: familyCounts(families),
      linkedBorgCandidateCount: candidates.filter((candidate) => candidate.linkedBorgId).length,
    },
    archiveInventory: summarizeArchives(files),
    needsExtractionConversion: scriptNeeds(candidates, files),
    candidates,
    families,
    textureCatalog,
    attachmentWeaponBoneLeads,
  };

  await fs.mkdir(path.dirname(outputJsonPath), { recursive: true });
  await fs.writeFile(outputJsonPath, `${JSON.stringify(report, null, 2)}\n`);
  await fs.writeFile(outputMarkdownPath, buildMarkdown(report));

  console.log(`wrote ${toRepoPath(outputJsonPath)}`);
  console.log(`wrote ${toRepoPath(outputMarkdownPath)}`);
  console.log(
    `scanned ${report.summary.fileCount} files, found ${report.summary.candidateCount} candidates across ${familyNames.length} families`,
  );
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
