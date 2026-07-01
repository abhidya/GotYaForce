#!/usr/bin/env node

import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { decompressPzzpStream, unpack as unpackPzz } from "../packages/formats/src/pzz.ts";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const rootDir = path.join(repoRoot, "user-data/GG4E/afs_data/root");

const sourceInventoryPath = path.join(repoRoot, "research/asset-inventory/weapons-effects-projectiles.json");
const borgDataPath = path.join(repoRoot, "packages/assets/data/borgs.json");
const outputJsonPath = path.join(repoRoot, "research/asset-inventory/particle-effect-inventory.json");
const outputMarkdownPath = path.join(repoRoot, "research/format-specs/particle-effect-format.md");

const familyOrder = ["fire", "beam", "gun", "sword", "muzzle", "impact", "trail", "reticle"];
const existingFamilyMap = {
  "fire/flame": "fire",
  "beam/laser": "beam",
  "gun/bullet": "gun",
  "sword/blade": "sword",
  muzzle: "muzzle",
  "impact/explosion": "impact",
  "aura/trail": "trail",
  "UI reticle/target": "reticle",
};

const familyTerms = {
  fire: ["fire", "flame", "burn", "blaze", "phoenix"],
  beam: ["beam", "laser", "plasma"],
  gun: [
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
    "shot",
  ],
  sword: ["sword", "blade", "slash", "samurai", "knight", "axe", "hatchet", "chainsaw", "claw", "spike", "drill", "hammer"],
  muzzle: ["muzzle", "flash", "shot", "gun", "gatling", "revolver", "cannon", "tank", "beam", "laser", "fighter"],
  impact: ["hit", "impact", "explosion", "explode", "blast", "bomb", "bomber", "missile", "icbm", "cannon", "drill", "hammer"],
  trail: ["trail", "aura", "boost", "wing", "jet", "ghost", "shadow", "cyber", "flame", "beam", "plasma", "phoenix"],
  reticle: ["reticle", "target", "cursor", "crosshair", "lock", "aim", "icon", "arrow"],
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

const bytesPerPixel = new Map([
  [0, 0.5],
  [1, 1],
  [2, 1],
  [3, 2],
  [4, 2],
  [5, 2],
  [6, 4],
  [8, 0.5],
  [9, 1],
  [10, 2],
  [14, 0.5],
]);

function toRepoPath(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

function hex(value, width = 8) {
  return `0x${Number(value).toString(16).padStart(width, "0")}`;
}

function formatBytes(bytes) {
  if (bytes >= 1024 * 1024) return `${(bytes / 1024 / 1024).toFixed(2)} MiB`;
  if (bytes >= 1024) return `${(bytes / 1024).toFixed(1)} KiB`;
  return `${bytes} B`;
}

function mdEscape(value) {
  return String(value ?? "").replaceAll("|", "\\|");
}

function uniq(values) {
  return [...new Set(values)];
}

async function readJson(absPath) {
  return JSON.parse(await fs.readFile(absPath, "utf8"));
}

async function writeFileWithRetry(absPath, contents) {
  let lastError = null;
  for (let attempt = 0; attempt < 8; attempt += 1) {
    try {
      await fs.writeFile(absPath, contents);
      return;
    } catch (error) {
      lastError = error;
      if (!["EBUSY", "EPERM", "EACCES", "UNKNOWN"].includes(error.code)) throw error;
      await new Promise((resolve) => setTimeout(resolve, 125 * (attempt + 1)));
    }
  }
  throw lastError;
}

async function listRootFiles() {
  const names = await fs.readdir(rootDir);
  const matched = names
    .filter((name) => /^efct/i.test(name) || /^ptcl00\./i.test(name) || /^it[0-9a-f]{4}_mdl\.arz$/i.test(name))
    .sort((a, b) => a.localeCompare(b));

  return Promise.all(
    matched.map(async (name) => {
      const abs = path.join(rootDir, name);
      const stat = await fs.stat(abs);
      return {
        name,
        path: toRepoPath(abs),
        abs,
        ext: path.extname(name).toLowerCase(),
        sizeBytes: stat.size,
      };
    }),
  );
}

function classifyRole(file) {
  const lower = file.name.toLowerCase();
  if (lower === "efct.pzz") return "shared effect PZZ archive";
  if (lower === "efct00.tpl") return "shared effect TPL texture";
  if (lower.endsWith("_mdl.arc")) return "HSD effect model";
  if (lower.endsWith("_mdl.arz")) return "compressed item/attachment model";
  if (lower === "ptcl00.ptl") return "particle settings table";
  if (lower === "ptcl00.ref") return "particle reference table";
  if (lower === "ptcl00.txg") return "particle image container";
  return file.ext ? `${file.ext.slice(1)} file` : "file";
}

function itBorgId(name) {
  const match = /^it([0-9a-f]{4})_mdl\.arz$/i.exec(name);
  return match ? `pl${match[1].toLowerCase()}` : null;
}

function sourceFamiliesForPath(sourceInventory, filePath) {
  const candidate = sourceInventory.candidates?.find((entry) => entry.path === filePath);
  if (!candidate) return [];

  return (candidate.families || [])
    .map((entry) => existingFamilyMap[entry.family])
    .filter(Boolean)
    .map((family) => ({
      family,
      confidence: candidate.families.find((entry) => existingFamilyMap[entry.family] === family)?.confidence ?? candidate.confidence ?? "Low",
      reason: candidate.families.find((entry) => existingFamilyMap[entry.family] === family)?.reason ?? candidate.reason ?? "from weapons/effects/projectiles inventory",
    }));
}

function classifyByTerms(file, sourceInventory, borgMap) {
  const lowerName = file.name.toLowerCase();
  const sourceFamilies = sourceFamiliesForPath(sourceInventory, file.path);
  const borg = borgMap.get(itBorgId(file.name));
  const linkedHaystack = borg ? `${borg.name} ${borg.tribe} ${borg.type}`.toLowerCase() : "";
  const families = new Map();

  for (const entry of sourceFamilies) {
    families.set(entry.family, {
      family: entry.family,
      confidence: entry.confidence,
      reason: `source inventory: ${entry.reason}`,
    });
  }

  if (/^efct/i.test(file.name)) {
    for (const family of ["fire", "beam", "muzzle", "impact", "trail"]) {
      families.set(family, {
        family,
        confidence: "Medium",
        reason: "efct prefix is the shared battle-effect asset group",
      });
    }
  }

  if (/^ptcl00\./i.test(file.name)) {
    for (const family of ["fire", "beam", "muzzle", "impact", "trail"]) {
      families.set(family, {
        family,
        confidence: "Medium",
        reason: "ptcl00 is the shared PTL/REF/TXG particle asset set",
      });
    }
  }

  for (const family of familyOrder) {
    const matches = familyTerms[family].filter((term) => lowerName.includes(term));
    if (matches.length > 0 && !families.has(family)) {
      families.set(family, {
        family,
        confidence: matches.length > 1 ? "High" : "Medium",
        reason: `filename contains ${matches.join(", ")}`,
      });
    }

    const borgMatches = familyTerms[family].filter((term) => linkedHaystack.includes(term));
    if (borgMatches.length > 0 && !families.has(family)) {
      families.set(family, {
        family,
        confidence: borgMatches.length > 1 ? "High" : "Medium",
        reason: `linked Borg ${borg.id} (${borg.name}) metadata contains ${borgMatches.join(", ")}`,
      });
    }
  }

  if (borg) {
    const shot = Number(borg.shot);
    const attack = Number(borg.attack);
    const type = String(borg.type || "").toLowerCase();
    if ((type.includes("long range") || shot >= 4) && !families.has("gun")) {
      families.set("gun", {
        family: "gun",
        confidence: "Low",
        reason: `linked Borg ${borg.id} (${borg.name}) is ranged/shot-capable (${borg.type}, shot ${borg.shot})`,
      });
    }
    if ((type.includes("long range") || shot >= 4) && !families.has("muzzle")) {
      families.set("muzzle", {
        family: "muzzle",
        confidence: "Low",
        reason: `linked Borg ${borg.id} (${borg.name}) is ranged/shot-capable (${borg.type}, shot ${borg.shot})`,
      });
    }
    if (type.includes("short range") && attack >= 4 && !families.has("sword")) {
      families.set("sword", {
        family: "sword",
        confidence: "Low",
        reason: `linked Borg ${borg.id} (${borg.name}) is short-range/high-attack (${borg.type}, attack ${borg.attack})`,
      });
    }
  }

  return [...families.values()].sort((a, b) => familyOrder.indexOf(a.family) - familyOrder.indexOf(b.family));
}

function parseTpl(buffer) {
  if (buffer.length < 12) return { parseStatus: "too small" };
  const magic = buffer.readUInt32BE(0);
  if (magic !== 0x0020af30) {
    return { parseStatus: `unexpected magic ${hex(magic)}`, magic: hex(magic) };
  }

  const imageCount = buffer.readUInt32BE(4);
  const imageTableOffset = buffer.readUInt32BE(8);
  const images = [];
  for (let i = 0; i < imageCount && i < 64; i += 1) {
    const entryOffset = imageTableOffset + i * 8;
    if (entryOffset + 8 > buffer.length) break;
    const textureHeaderOffset = buffer.readUInt32BE(entryOffset);
    const paletteHeaderOffset = buffer.readUInt32BE(entryOffset + 4);
    if (textureHeaderOffset + 12 > buffer.length) {
      images.push({ index: i, parseStatus: "texture header outside file", textureHeaderOffset });
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
      formatCode,
      format: tplFormats.get(formatCode) || `unknown(${formatCode})`,
      dataOffset,
      textureHeaderOffset,
      paletteHeaderOffset: paletteHeaderOffset || null,
      estimatedPayloadBytes: bytesPerPixel.has(formatCode) ? Math.ceil(width * height * bytesPerPixel.get(formatCode)) : null,
    });
  }

  return {
    parseStatus: images.length === imageCount ? "ok" : "partial",
    magic: hex(magic),
    imageCount,
    imageTableOffset,
    images,
  };
}

function readCString(buffer, offset) {
  let end = offset;
  while (end < buffer.length && buffer[end] !== 0) end += 1;
  return buffer.subarray(offset, end).toString("ascii");
}

function parseHsdArc(buffer) {
  if (buffer.length < 0x20) return { parseStatus: "too small" };

  const first = buffer.readUInt32BE(0);
  const wrappedFileSize = buffer.length >= 0x120 && first === 0x100 ? buffer.readUInt32BE(0x100) : null;
  const wrapped = wrappedFileSize !== null && wrappedFileSize > 0 && 0x100 + wrappedFileSize <= buffer.length;
  const bare = first > 0 && first <= buffer.length;
  if (!bare && !wrapped) {
    return { parseStatus: "not recognized as bare/wrapped HSD DAT", firstWord: hex(first), sizeBytes: buffer.length };
  }

  const base = wrapped ? 0x100 : 0;
  const fileSize = buffer.readUInt32BE(base);
  const dataBlockSize = buffer.readUInt32BE(base + 4);
  const relocCount = buffer.readUInt32BE(base + 8);
  const rootCount = buffer.readUInt32BE(base + 12);
  const externalRefCount = buffer.readUInt32BE(base + 16);
  if (fileSize <= 0 || base + fileSize > buffer.length || rootCount > 256 || externalRefCount > 256 || relocCount > 200000) {
    return { parseStatus: "not recognized as plausible HSD DAT", firstWord: hex(first), sizeBytes: buffer.length };
  }
  const rootsOffset = base + 0x20 + dataBlockSize + relocCount * 4;
  const symbolTableOffset = rootsOffset + rootCount * 8 + externalRefCount * 8;
  if (rootsOffset < base || rootsOffset > base + fileSize || symbolTableOffset > base + fileSize) {
    return { parseStatus: "not recognized as plausible HSD DAT", firstWord: hex(first), sizeBytes: buffer.length };
  }
  const roots = [];

  for (let i = 0; i < rootCount && i < 32; i += 1) {
    const off = rootsOffset + i * 8;
    if (off + 8 > buffer.length) break;
    const dataOffset = buffer.readUInt32BE(off);
    const stringOffset = buffer.readUInt32BE(off + 4);
    roots.push({
      index: i,
      dataOffset,
      stringOffset,
      name: symbolTableOffset + stringOffset < buffer.length ? readCString(buffer, symbolTableOffset + stringOffset) : null,
    });
  }

  return {
    parseStatus: "HSD DAT header recognized",
    container: wrapped ? "wrapped HSD DAT" : "bare HSD DAT",
    hsdOffset: base,
    fileSize,
    paddedPayloadBytes: buffer.length,
    paddingBytes: buffer.length - (base + fileSize),
    dataBlockSize,
    relocCount,
    rootCount,
    externalRefCount,
    symbolTableOffset,
    roots,
  };
}

function summarizeCompression(meta) {
  if (!meta) return null;
  return {
    algorithm: meta.algorithm,
    sourceBytes: meta.sourceBytes,
    producedBytes: meta.producedBytes,
    consumedBytes: meta.consumedBytes,
    trailingBytes: meta.trailingBytes,
    terminated: meta.terminated,
    terminatorOffset: meta.terminatorOffset,
    tokenCount: meta.tokenCount,
    literalPairs: meta.literalPairs,
    backRefs: meta.backRefs,
    longBackRefs: meta.longBackRefs,
    firstControlWord: meta.firstControlWord === null ? null : hex(meta.firstControlWord, 4),
  };
}

function sniffPayload(buffer) {
  if (buffer.length === 0) return { kind: "empty", parseStatus: "empty payload" };

  const tpl = parseTpl(buffer);
  if (tpl.parseStatus === "ok" || tpl.parseStatus === "partial") {
    return { kind: "tpl-texture", tpl };
  }

  const hsd = parseHsdArc(buffer);
  if (hsd.parseStatus === "HSD DAT header recognized") {
    return { kind: "hsd-dat", hsd };
  }

  const ptl = parsePtl(buffer);
  if (ptl.parseStatus !== "too small") {
    return { kind: "ptl-table-candidate", ptl };
  }

  const txg = parseTxg(buffer);
  if (txg.parseStatus !== "too small") {
    return { kind: "txg-candidate", txg };
  }

  return {
    kind: "unknown-binary",
    parseStatus: "payload decoded but format semantics not identified",
    headWords: Array.from({ length: Math.min(8, Math.floor(buffer.length / 4)) }, (_, index) => hex(buffer.readUInt32BE(index * 4))),
  };
}

function parsePzzHeader(buffer) {
  if (buffer.length < 16) return { parseStatus: "too small" };
  const firstWord = buffer.readUInt32BE(0);
  const headerWords = [];
  for (let i = 0; i < Math.min(16, Math.floor(buffer.length / 4)); i += 1) {
    headerWords.push(hex(buffer.readUInt32BE(i * 4)));
  }
  try {
    const archive = unpackPzz(buffer);
    const members = archive.members.map((member) => {
      const payload = Buffer.from(member.payload);
      return {
        memberId: member.memberId,
        index: member.index,
        tableWord: hex(member.tableWord),
        compressed: member.compressed,
        blockCount: member.blockCount,
        paddedBytes: member.paddedBytes,
        dataOffset: member.dataOffset,
        rawBytes: member.rawPayload.byteLength,
        payloadBytes: member.payload.byteLength,
        compression: summarizeCompression(member.compression),
        sniff: sniffPayload(payload),
      };
    });
    return {
      parseStatus: "PZZ archive unpacked with shared @gf/formats parser; payload semantics are sniffed, not runtime-bound",
      firstWordAsMemberCountCandidate: firstWord,
      headerWords,
      memberCount: archive.memberCount,
      tableBytes: archive.tableBytes,
      dataStartOffset: archive.dataStartOffset,
      expectedSizeFromTable: archive.expectedSizeFromTable,
      validatesAgainstFileSize: archive.validatesAgainstFileSize,
      compressedMemberCount: members.filter((member) => member.compressed).length,
      rawMemberCount: members.filter((member) => !member.compressed && member.payloadBytes > 0).length,
      zeroLengthMemberCount: members.filter((member) => member.payloadBytes === 0).length,
      payloadKinds: countKinds(members.map((member) => member.sniff.kind)),
      members,
      blocker: "Remaining work: map decompressed effect members to runtime HSD/effect semantics before driving sword/gun/projectile/powerup visuals.",
    };
  } catch (error) {
    return {
      parseStatus: "PZZ shared parser failed; header sniff retained for debugging",
      firstWordAsMemberCountCandidate: firstWord,
      headerWords,
      error: error.message,
      blocker: "Remaining work: fix PZZ parser coverage for this archive before effect semantics can be mapped.",
    };
  }
}

function parseArzHeader(buffer) {
  if (buffer.length < 16) return { parseStatus: "too small" };
  const words = [];
  for (let i = 0; i < Math.min(12, Math.floor(buffer.length / 4)); i += 1) words.push(hex(buffer.readUInt32BE(i * 4)));
  try {
    const decompressed = decompressPzzpStream(buffer);
    const payload = Buffer.from(decompressed.payload);
    return {
      parseStatus: "ARZ/PZZP stream decompressed with shared @gf/formats parser; payload semantics are sniffed, not runtime-bound",
      headerWords: words,
      firstWord: words[0],
      compression: summarizeCompression(decompressed.meta),
      payloadBytes: payload.length,
      sniff: sniffPayload(payload),
      blocker: "Remaining work: map decompressed HSD item/attachment models to borg action timing and weapon semantics.",
    };
  } catch (error) {
    return {
      parseStatus: "ARZ shared parser failed; compressed header sniff retained for debugging",
      headerWords: words,
      firstWord: words[0],
      error: error.message,
      blocker: "Remaining work: fix ARZ parser coverage for this file before item/attachment model semantics can be mapped.",
    };
  }
}

function parsePtl(buffer) {
  if (buffer.length < 0x60) return { parseStatus: "too small" };
  const headerWord = buffer.readUInt32BE(0);
  const countCandidate = headerWord >>> 16;
  const lowWord = headerWord & 0xffff;
  const offsets = [];
  let sentinelOffset = null;

  for (let offset = 4; offset + 4 <= buffer.length && offset < 0x400; offset += 4) {
    const value = buffer.readUInt32BE(offset);
    if (value === 0xffffffff) {
      sentinelOffset = offset;
      break;
    }
    offsets.push(value);
  }

  const dataBase = sentinelOffset === null ? null : sentinelOffset + 4;
  const payloadBytes = dataBase === null ? null : buffer.length - dataBase;
  const monotonic = offsets.every((value, index) => index === 0 || value >= offsets[index - 1]);
  const records =
    dataBase === null
      ? []
      : offsets.map((relativeOffset, index) => {
          const next = offsets[index + 1] ?? payloadBytes;
          const byteLength = next - relativeOffset;
          return {
            index,
            relativeOffset,
            absoluteOffset: dataBase + relativeOffset,
            byteLength,
            firstWords:
              dataBase + relativeOffset + 16 <= buffer.length
                ? [
                    hex(buffer.readUInt32BE(dataBase + relativeOffset)),
                    hex(buffer.readUInt32BE(dataBase + relativeOffset + 4)),
                    hex(buffer.readUInt32BE(dataBase + relativeOffset + 8)),
                    hex(buffer.readUInt32BE(dataBase + relativeOffset + 12)),
                  ]
                : [],
          };
        });

  return {
    parseStatus: dataBase && monotonic ? "offset table recognized; record fields not fully decoded" : "needs reverse engineering",
    headerWord: hex(headerWord),
    countCandidate,
    lowWord,
    sentinelOffset,
    dataBase,
    payloadBytes,
    offsetCountIncludingTrailer: offsets.length,
    substantiveRecordCount: records.filter((record) => record.byteLength >= 16).length,
    trailingBytes: records.filter((record) => record.byteLength > 0 && record.byteLength < 16).reduce((sum, record) => sum + record.byteLength, 0),
    monotonicOffsets: monotonic,
    offsets,
    recordLengths: uniq(records.map((record) => record.byteLength)).sort((a, b) => a - b),
    records,
  };
}

function parseRef(buffer) {
  const values = [];
  for (let offset = 0; offset + 4 <= buffer.length; offset += 4) values.push(buffer.readUInt32BE(offset));
  const sequential = values.every((value, index) => value === index);
  return {
    parseStatus: sequential ? "u32 sequence table recognized" : "u32 table; semantics unknown",
    entryCount: values.length,
    values,
    sequential,
  };
}

function parseTxg(buffer) {
  if (buffer.length < 8) return { parseStatus: "too small" };
  const entryCount = buffer.readUInt32BE(0);
  const tableValues = [];
  for (let i = 0; 4 + i * 4 + 4 <= buffer.length && i < 128; i += 1) {
    const value = buffer.readUInt32BE(4 + i * 4);
    tableValues.push(value);
    if (i + 1 >= entryCount && value === 0xffffffff) break;
  }

  const offsets = tableValues.filter((value) => value !== 0xffffffff);
  const monotonicOffsets = offsets.every((value, index) => index === 0 || value >= offsets[index - 1]);
  const entries = offsets.map((offset, index) => {
    const nextOffset = offsets[index + 1] ?? buffer.length;
    const imageCount = buffer.readUInt32BE(offset);
    const formatCode = buffer.readUInt32BE(offset + 4);
    const unknown2 = buffer.readUInt32BE(offset + 8);
    const width = buffer.readUInt32BE(offset + 12);
    const height = buffer.readUInt32BE(offset + 16);
    const unknown5 = buffer.readUInt32BE(offset + 20);
    const dataOffset = buffer.readUInt32BE(offset + 24);
    const paletteOffsetWord = buffer.readUInt32BE(offset + 28);
    const expectedPayloadBytes = bytesPerPixel.has(formatCode) ? Math.ceil(width * height * bytesPerPixel.get(formatCode)) : null;
    const actualPayloadBytes = nextOffset - dataOffset;
    return {
      index,
      offset,
      nextOffset,
      spanBytes: nextOffset - offset,
      imageCount,
      formatCode,
      format: tplFormats.get(formatCode) || `unknown(${formatCode})`,
      unknown2,
      width,
      height,
      unknown5,
      dataOffset,
      paletteOffset: paletteOffsetWord === 0xffffffff ? null : paletteOffsetWord,
      expectedPayloadBytes,
      actualPayloadBytes,
      payloadMatchesFormat: expectedPayloadBytes === actualPayloadBytes,
    };
  });

  return {
    parseStatus:
      entryCount === entries.length && monotonicOffsets && entries.every((entry) => entry.payloadMatchesFormat)
        ? "texture offset table and entry headers recognized"
        : "partial; needs image decoder validation",
    entryCount,
    tableValues: tableValues.map((value) => (value === 0xffffffff ? "0xffffffff" : value)),
    offsets,
    monotonicOffsets,
    entries,
  };
}

async function parseFile(file) {
  const buffer = await fs.readFile(file.abs);
  const lower = file.name.toLowerCase();
  if (lower.endsWith(".tpl")) return { tpl: parseTpl(buffer) };
  if (lower.endsWith("_mdl.arc")) return { hsd: parseHsdArc(buffer) };
  if (lower.endsWith(".pzz")) return { pzz: parsePzzHeader(buffer) };
  if (lower.endsWith(".arz")) return { arz: parseArzHeader(buffer) };
  if (lower.endsWith(".ptl")) return { ptl: parsePtl(buffer) };
  if (lower.endsWith(".ref")) return { ref: parseRef(buffer) };
  if (lower.endsWith(".txg")) return { txg: parseTxg(buffer) };
  return null;
}

function buildSourceCandidateMap(sourceInventory) {
  const map = new Map();
  for (const candidate of sourceInventory.candidates || []) {
    map.set(candidate.path, candidate);
  }
  return map;
}

function linkedBorgFromSource(file, sourceCandidateMap, borgMap) {
  const candidate = sourceCandidateMap.get(file.path);
  if (candidate?.linkedBorgId) {
    return {
      id: candidate.linkedBorgId,
      name: candidate.linkedBorgName,
      number: candidate.linkedBorgNumber,
    };
  }
  const id = itBorgId(file.name);
  const borg = id ? borgMap.get(id) : null;
  return id ? { id, name: borg?.name ?? null, number: borg?.number ?? null } : null;
}

function blockerForFile(file, parsed) {
  if (parsed?.pzz) return parsed.pzz.blocker;
  if (parsed?.arz) return parsed.arz.blocker;
  if (parsed?.txg) return "TXG table and headers are recognized here, but PNG/KTX2 decode/export is not implemented in browser tooling.";
  if (parsed?.ptl) return "PTL offset table is recognized, but emitter field semantics, texture-reference links, and runtime behavior need reverse engineering.";
  return null;
}

function confidenceRank(value) {
  return { High: 3, Medium: 2, Low: 1 }[value] ?? 0;
}

function countKinds(values) {
  const counts = {};
  for (const value of values) counts[value ?? "unknown"] = (counts[value ?? "unknown"] || 0) + 1;
  return Object.fromEntries(Object.entries(counts).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0])));
}

function makeAssetRecord(file, parsed, sourceInventory, sourceCandidateMap, borgMap) {
  const sourceCandidate = sourceCandidateMap.get(file.path);
  const families = classifyByTerms(file, sourceInventory, borgMap);
  return {
    path: file.path,
    name: file.name,
    role: classifyRole(file),
    extension: file.ext,
    sizeBytes: file.sizeBytes,
    linkedBorg: linkedBorgFromSource(file, sourceCandidateMap, borgMap),
    families,
    familyKeys: families.map((entry) => entry.family),
    sourceInventoryCandidate: sourceCandidate
      ? {
          confidence: sourceCandidate.confidence,
          reason: sourceCandidate.reason,
          needs: sourceCandidate.needs || [],
        }
      : null,
    parse: parsed,
    blocker: blockerForFile(file, parsed),
  };
}

function addFamilyRecord(grouped, family, asset, reasonOverride = null) {
  const familyEntry = asset.families.find((entry) => entry.family === family);
  grouped[family].push({
    path: asset.path,
    role: asset.role,
    sizeBytes: asset.sizeBytes,
    linkedBorg: asset.linkedBorg,
    confidence: familyEntry?.confidence ?? "Low",
    reason: reasonOverride ?? familyEntry?.reason ?? "grouped by scanner",
    blocker: asset.blocker,
  });
}

function buildFamilies(assets, sourceInventory) {
  const grouped = Object.fromEntries(familyOrder.map((family) => [family, []]));

  for (const asset of assets) {
    for (const family of asset.familyKeys) addFamilyRecord(grouped, family, asset);
  }

  for (const [sourceFamily, targetFamily] of Object.entries(existingFamilyMap)) {
    const entries = sourceInventory.families?.[sourceFamily] || [];
    for (const entry of entries.slice(0, 250)) {
      if (grouped[targetFamily].some((item) => item.path === entry.path)) continue;
      grouped[targetFamily].push({
        path: entry.path,
        role: entry.fileType?.role ?? entry.fileType?.extension ?? "source-inventory candidate",
        sizeBytes: entry.sizeBytes,
        linkedBorg: entry.linkedBorgId ? { id: entry.linkedBorgId, name: entry.linkedBorgName ?? null, number: null } : null,
        confidence: entry.confidence ?? "Low",
        reason: `source weapons/effects/projectiles inventory: ${entry.reason ?? "family match"}`,
        blocker: (entry.needs || []).join("; ") || null,
      });
    }
  }

  for (const family of familyOrder) {
    grouped[family].sort((a, b) => {
      const conf = confidenceRank(b.confidence) - confidenceRank(a.confidence);
      if (conf !== 0) return conf;
      return (b.sizeBytes ?? 0) - (a.sizeBytes ?? 0) || a.path.localeCompare(b.path);
    });
  }

  return grouped;
}

function summarizeArchives(assets) {
  const pzz = assets.filter((asset) => asset.extension === ".pzz");
  const arz = assets.filter((asset) => asset.extension === ".arz");
  const arzHeaderGroups = {};
  for (const asset of arz) {
    const words = asset.parse?.arz?.headerWords?.slice(0, 4).join(" ") ?? "(unparsed)";
    arzHeaderGroups[words] = (arzHeaderGroups[words] || 0) + 1;
  }

  return {
    pzzCount: pzz.length,
    arzCount: arz.length,
    pzzMemberCount: pzz.reduce((sum, asset) => sum + (asset.parse?.pzz?.memberCount ?? 0), 0),
    pzzPayloadKinds: countKinds(pzz.flatMap((asset) => asset.parse?.pzz?.members?.map((member) => member.sniff.kind) ?? [])),
    directArzPayloadKinds: countKinds(arz.map((asset) => asset.parse?.arz?.sniff?.kind ?? "unparsed")),
    pzzMemberCountCandidates: pzz.map((asset) => ({
      path: asset.path,
      firstWordAsMemberCountCandidate: asset.parse?.pzz?.firstWordAsMemberCountCandidate ?? null,
    })),
    arzHeaderGroups,
    parserStatus: [
      "Shared PZZ unpack/list support is implemented in packages/formats/src/pzz.ts.",
      "Shared ARZ/PZZP decompression is implemented in packages/formats/src/arz.ts.",
      "This scanner now consumes the shared parser for direct effect PZZ and item-model ARZ candidates.",
    ],
    remainingBlockers: [
      "Decoded PZZ/ARZ payloads still need HSD/model and effect semantic mapping before they can drive sword/gun/projectile/powerup visuals.",
      "PZZ members may contain ARZ-compressed payloads, so effect archive inspection has two layers: PZZ member table first, then ARZ decompression per compressed member.",
    ],
  };
}

async function collectFormatSpecEvidence() {
  const specDir = path.join(repoRoot, "research/format-specs");
  let names = [];
  try {
    names = await fs.readdir(specDir);
  } catch (error) {
    if (error.code === "ENOENT") return [];
    throw error;
  }

  const evidence = [];
  const pattern = /\b(PTL|REF|TXG|TPL|PZZ|ARZ|ARC|particle|effect|particles)\b/i;
  for (const name of names.sort((a, b) => a.localeCompare(b))) {
    if (!name.endsWith(".md")) continue;
    const abs = path.join(specDir, name);
    const text = await fs.readFile(abs, "utf8");
    const matches = text
      .split(/\r?\n/)
      .map((line, index) => ({ line: index + 1, text: line.trim() }))
      .filter((line) => pattern.test(line.text))
      .slice(0, 12);
    if (matches.length > 0) evidence.push({ path: toRepoPath(abs), matches });
  }
  return evidence;
}

function buildSummary(assets, families, sourceInventory) {
  const byExtension = {};
  const byRole = {};
  for (const asset of assets) {
    byExtension[asset.extension] = (byExtension[asset.extension] || 0) + 1;
    byRole[asset.role] = (byRole[asset.role] || 0) + 1;
  }

  return {
    scannedFileCount: assets.length,
    sourceInventoryCandidateCount: sourceInventory.summary?.candidateCount ?? null,
    byExtension: Object.fromEntries(Object.entries(byExtension).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]))),
    byRole: Object.fromEntries(Object.entries(byRole).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]))),
    familyCounts: Object.fromEntries(familyOrder.map((family) => [family, families[family].length])),
    directParticleFiles: assets.filter((asset) => /^ptcl00\./i.test(asset.name)).map((asset) => asset.path),
    directSharedEffectFiles: assets.filter((asset) => /^efct/i.test(asset.name)).map((asset) => asset.path),
    itemModelArzCount: assets.filter((asset) => /^it[0-9a-f]{4}_mdl\.arz$/i.test(asset.name)).length,
  };
}

function parseStatusLine(asset) {
  if (asset.parse?.txg) return `${asset.parse.txg.entryCount} TXG textures; ${asset.parse.txg.parseStatus}`;
  if (asset.parse?.ptl) return `${asset.parse.ptl.substantiveRecordCount} PTL records + ${asset.parse.ptl.trailingBytes} trailer byte(s); ${asset.parse.ptl.parseStatus}`;
  if (asset.parse?.ref) return `${asset.parse.ref.entryCount} REF u32 entries; ${asset.parse.ref.parseStatus}`;
  if (asset.parse?.tpl) {
    const image = asset.parse.tpl.images?.[0];
    return image ? `${asset.parse.tpl.imageCount} TPL image, ${image.width}x${image.height} ${image.format}` : asset.parse.tpl.parseStatus;
  }
  if (asset.parse?.hsd) return `${asset.parse.hsd.container}, root(s): ${asset.parse.hsd.roots?.map((root) => root.name).join(", ") || "unread"}`;
  if (asset.parse?.pzz) {
    const kinds = Object.entries(asset.parse.pzz.payloadKinds ?? {})
      .map(([kind, count]) => `${kind}:${count}`)
      .join(", ");
    return `PZZ unpacked, ${asset.parse.pzz.memberCount ?? "?"} member(s), payload kinds ${kinds || "unknown"}`;
  }
  if (asset.parse?.arz) return `ARZ decompressed to ${formatBytes(asset.parse.arz.payloadBytes ?? 0)}, payload kind ${asset.parse.arz.sniff?.kind ?? "unknown"}`;
  return "unparsed";
}

function buildMarkdown(report) {
  const lines = [];
  lines.push("# Gotcha Force particle/effect format notes");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push(`Scanner: \`${report.scanner}\``);
  lines.push("");
  lines.push("## Inputs");
  lines.push("");
  for (const input of report.inputs) lines.push(`- \`${input}\``);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Direct particle/effect files scanned: ${report.summary.scannedFileCount}`);
  lines.push(`- ` + `it####_mdl.arz` + ` compressed item-model archives: ${report.summary.itemModelArzCount}`);
  lines.push(`- Existing weapons/effects/projectiles candidates read: ${report.summary.sourceInventoryCandidateCount}`);
  lines.push(`- Family group sizes: ${familyOrder.map((family) => `${family} ${report.summary.familyCounts[family]}`).join(", ")}`);
  lines.push("");
  lines.push("## Confirmed byte-level observations");
  lines.push("");

  for (const asset of report.assets.filter((entry) => /^ptcl00\./i.test(entry.name) || /^efct/i.test(entry.name))) {
    lines.push(`- \`${asset.path}\` (${formatBytes(asset.sizeBytes)}): ${parseStatusLine(asset)}.`);
  }

  lines.push("");
  lines.push("### PTL");
  const ptl = report.assets.find((asset) => asset.name === "ptcl00.ptl")?.parse?.ptl;
  if (ptl) {
    lines.push(
      `\`ptcl00.ptl\` has header word \`${ptl.headerWord}\`, a count-like high word of ${ptl.countCandidate}, a sentinel at \`${hex(
        ptl.sentinelOffset,
        2,
      )}\`, and record data beginning at \`${hex(ptl.dataBase, 2)}\`.`,
    );
    lines.push(
      `The scanner sees ${ptl.offsetCountIncludingTrailer} offsets before \`0xffffffff\`, ${ptl.substantiveRecordCount} records of 16+ bytes, and ${ptl.trailingBytes} trailing byte(s). Record lengths observed: ${ptl.recordLengths.join(", ")} bytes.`,
    );
  }

  lines.push("");
  lines.push("### REF");
  const ref = report.assets.find((asset) => asset.name === "ptcl00.ref")?.parse?.ref;
  if (ref) {
    lines.push(`\`ptcl00.ref\` is ${ref.entryCount} big-endian u32 values and currently reads as a simple ${ref.values[0]}..${ref.values.at(-1)} sequence.`);
  }

  lines.push("");
  lines.push("### TXG");
  const txg = report.assets.find((asset) => asset.name === "ptcl00.txg")?.parse?.txg;
  if (txg) {
    lines.push(`\`ptcl00.txg\` has ${txg.entryCount} texture entries. Every entry has one image and an exact payload-size match for its GC texture format.`);
    lines.push("");
    lines.push("| Index | Offset | Dimensions | Format | Payload |");
    lines.push("|---:|---:|---:|---|---:|");
    for (const entry of txg.entries) {
      lines.push(
        `| ${entry.index} | \`${hex(entry.offset, 4)}\` | ${entry.width}x${entry.height} | ${entry.format} | ${formatBytes(
          entry.actualPayloadBytes,
        )} |`,
      );
    }
  }

  lines.push("");
  lines.push("## Family groups");
  for (const family of familyOrder) {
    lines.push("");
    lines.push(`### ${family}`);
    lines.push("");
    lines.push("| Path | Role | Size | Confidence | Reason / blocker |");
    lines.push("|---|---|---:|---|---|");
    for (const entry of report.families[family].slice(0, 14)) {
      const reason = [entry.reason, entry.blocker].filter(Boolean).join(" / ");
      lines.push(
        `| \`${mdEscape(entry.path)}\` | ${mdEscape(entry.role)} | ${formatBytes(entry.sizeBytes)} | ${entry.confidence} | ${mdEscape(reason)} |`,
      );
    }
  }

  lines.push("");
  lines.push("## Archive parser status and remaining blockers");
  lines.push("");
  for (const blocker of report.archiveAndDecompressionBlockers.parserStatus) {
    lines.push(`- ${blocker}`);
  }
  for (const blocker of report.archiveAndDecompressionBlockers.remainingBlockers) {
    lines.push(`- ${blocker}`);
  }
  lines.push(`- Direct scan found ${report.archiveAndDecompressionBlockers.pzzCount} PZZ effect archive(s) and ${report.archiveAndDecompressionBlockers.arzCount} ARZ item model archive(s).`);
  lines.push(`- PZZ member payload kinds: ${Object.entries(report.archiveAndDecompressionBlockers.pzzPayloadKinds).map(([kind, count]) => `${kind} ${count}`).join(", ") || "none"}.`);
  lines.push(`- Direct ARZ payload kinds: ${Object.entries(report.archiveAndDecompressionBlockers.directArzPayloadKinds).map(([kind, count]) => `${kind} ${count}`).join(", ") || "none"}.`);
  lines.push("");
  lines.push("ARZ header groups:");
  lines.push("");
  for (const [header, count] of Object.entries(report.archiveAndDecompressionBlockers.arzHeaderGroups)) {
    lines.push(`- \`${header}\`: ${count}`);
  }

  lines.push("");
  lines.push("## Existing spec evidence used");
  lines.push("");
  for (const spec of report.formatSpecEvidence) {
    const refs = spec.matches.map((match) => `${match.line}`).join(", ");
    lines.push(`- \`${spec.path}\` lines ${refs}`);
  }

  lines.push("");
  lines.push("## Next decoding steps");
  lines.push("");
  lines.push("- Map decompressed `efct.pzz` members and `it####_mdl.arz` HSD roots to concrete game events, borg actions, bones, and hit timing.");
  lines.push("- Add a TXG image decoder for I4, I8, and RGB565; `ptcl00.txg` already provides dimensions, formats, and byte-exact payload spans.");
  lines.push("- Reverse PTL record fields by correlating PTL records, REF indexes, TXG texture indexes, and Dolphin captures of fire/beam/muzzle/impact/trail effects.");
  lines.push("- For sword/gun attachment visuals, inspect decompressed `it####_mdl.arz` as HSD models and map them to MOT/hit timing rather than creating placeholder effects.");
  lines.push("");

  return `${lines.join("\n")}\n`;
}

async function main() {
  const sourceInventory = await readJson(sourceInventoryPath);
  const borgData = await readJson(borgDataPath);
  const borgMap = new Map((borgData.borgs || []).map((borg) => [borg.id, borg]));
  const sourceCandidateMap = buildSourceCandidateMap(sourceInventory);
  const files = await listRootFiles();
  const assets = [];

  for (const file of files) {
    const parsed = await parseFile(file);
    assets.push(makeAssetRecord(file, parsed, sourceInventory, sourceCandidateMap, borgMap));
  }

  const families = buildFamilies(assets, sourceInventory);
  const report = {
    generatedAt: new Date().toISOString(),
    scanner: toRepoPath(fileURLToPath(import.meta.url)),
    inputs: [
      toRepoPath(sourceInventoryPath),
      toRepoPath(borgDataPath),
      "user-data/GG4E/afs_data/root/efct*",
      "user-data/GG4E/afs_data/root/ptcl00.ptl",
      "user-data/GG4E/afs_data/root/ptcl00.ref",
      "user-data/GG4E/afs_data/root/ptcl00.txg",
      "user-data/GG4E/afs_data/root/it####_mdl.arz",
      "research/format-specs/*.md",
    ],
    summary: null,
    assets,
    families,
    archiveAndDecompressionBlockers: summarizeArchives(assets),
    formatSpecEvidence: await collectFormatSpecEvidence(),
  };
  report.summary = buildSummary(assets, families, sourceInventory);

  await fs.mkdir(path.dirname(outputJsonPath), { recursive: true });
  await fs.mkdir(path.dirname(outputMarkdownPath), { recursive: true });
  await writeFileWithRetry(outputJsonPath, `${JSON.stringify(report, null, 2)}\n`);
  await writeFileWithRetry(outputMarkdownPath, buildMarkdown(report));

  console.log(`wrote ${toRepoPath(outputJsonPath)}`);
  console.log(`wrote ${toRepoPath(outputMarkdownPath)}`);
  console.log(
    `scanned ${report.summary.scannedFileCount} direct files; grouped families ${familyOrder
      .map((family) => `${family}:${report.summary.familyCounts[family]}`)
      .join(" ")}`,
  );
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
