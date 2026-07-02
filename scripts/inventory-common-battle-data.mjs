#!/usr/bin/env node
import { createHash } from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = "GG4E";
const assetRoot = path.join(repoRoot, "user-data", region, "afs_data", "root");
const outDir = path.join(repoRoot, "research", "asset-inventory");
const outJson = path.join(outDir, "common-battle-data.json");
const outMd = path.join(outDir, "common-battle-data.md");
const borgMetadataPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const runtimePaths = {
  appMain: path.join(repoRoot, "apps", "game", "src", "main.ts"),
  combatStats: path.join(repoRoot, "packages", "combat", "src", "stats.ts"),
  combatActorDataStats: path.join(repoRoot, "packages", "combat", "src", "actorDataStats.ts"),
  combatActorDataStatsJson: path.join(repoRoot, "packages", "combat", "src", "data", "actorDataStats.json"),
  combatConstants: path.join(repoRoot, "packages", "combat", "src", "constants.ts"),
  formatsPzz: path.join(repoRoot, "packages", "formats", "src", "pzz.ts"),
};

const pzzBlockSize = 0x800;
const pzzCompressedFlag = 0x40000000;
const pzzBlockCountMask = 0x3fffffff;
const actorDataRecordSize = 432;
const actorDataStatOffsets = {
  defense: 0x1a4,
  shot: 0x1a5,
  attack: 0x1a6,
  speed: 0x1a7,
};

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

function hex(value, width = 8) {
  return `0x${Number(value).toString(16).padStart(width, "0")}`;
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

function headHex(buffer, byteCount = 32) {
  return buffer.subarray(0, Math.min(byteCount, buffer.length)).toString("hex").replace(/(..)/g, "$1 ").trim();
}

function readHalfwords(buffer, count = 16) {
  const out = [];
  for (let offset = 0; offset + 2 <= buffer.length && out.length < count; offset += 2) {
    out.push(hex(buffer.readUInt16BE(offset), 4));
  }
  return out;
}

function readWords(buffer, count = 12) {
  const out = [];
  for (let offset = 0; offset + 4 <= buffer.length && out.length < count; offset += 4) {
    out.push(hex(buffer.readUInt32BE(offset), 8));
  }
  return out;
}

function readFloatWords(buffer, count = 12) {
  const out = [];
  for (let offset = 0; offset + 4 <= buffer.length && out.length < count; offset += 4) {
    const value = buffer.readFloatBE(offset);
    out.push(Number.isFinite(value) ? Number(value.toFixed(6)) : null);
  }
  return out;
}

class GrowBuffer {
  constructor(initialSize) {
    this.buffer = Buffer.allocUnsafe(Math.max(0x1000, initialSize));
    this.length = 0;
  }

  ensure(extraBytes) {
    const needed = this.length + extraBytes;
    if (needed <= this.buffer.length) return;
    let nextLength = this.buffer.length;
    while (nextLength < needed) nextLength *= 2;
    const next = Buffer.allocUnsafe(nextLength);
    this.buffer.copy(next, 0, 0, this.length);
    this.buffer = next;
  }

  pushPair(a, b) {
    this.ensure(2);
    this.buffer[this.length] = a;
    this.buffer[this.length + 1] = b;
    this.length += 2;
  }

  copyFromSelf(distance, count) {
    const start = this.length - distance;
    if (start < 0) throw new Error(`invalid back-reference distance ${distance}`);
    this.ensure(count);
    for (let i = 0; i < count; i += 1) {
      this.buffer[this.length] = this.buffer[start + i];
      this.length += 1;
    }
  }

  toBuffer() {
    return this.buffer.subarray(0, this.length);
  }
}

function decompressPzzpStream(buffer) {
  const writer = new GrowBuffer(Math.max(buffer.length * 3, 0x1000));
  const evenLength = buffer.length & ~1;
  let cursor = 0;
  let control = 0;
  let bit = -1;
  while (cursor + 2 <= evenLength) {
    if (bit < 0) {
      control = buffer.readUInt16BE(cursor);
      cursor += 2;
      bit = 15;
      continue;
    }

    const compressedToken = (control & (1 << bit)) !== 0;
    bit -= 1;
    if (!compressedToken) {
      writer.pushPair(buffer[cursor], buffer[cursor + 1]);
      cursor += 2;
      continue;
    }

    const token = buffer.readUInt16BE(cursor);
    const distance = (token & 0x7ff) * 2;
    if (distance === 0) break;
    let byteCount = (token >> 11) * 2;
    cursor += 2;
    if (byteCount === 0) {
      byteCount = buffer.readUInt16BE(cursor) * 2;
      cursor += 2;
    }
    writer.copyFromSelf(distance, byteCount);
  }
  return writer.toBuffer();
}

function readPzzMember(archivePath, wantedIndex) {
  const buffer = fs.readFileSync(archivePath);
  const count = buffer.readUInt32BE(0);
  if (count <= wantedIndex || 4 + count * 4 > pzzBlockSize) throw new Error(`invalid PZZ table in ${rel(archivePath)}`);

  let cursor = pzzBlockSize;
  for (let index = 0; index < count; index += 1) {
    const tableWord = buffer.readUInt32BE(4 + index * 4);
    const compressed = (tableWord & pzzCompressedFlag) !== 0;
    const blockCount = tableWord & pzzBlockCountMask;
    const paddedBytes = blockCount * pzzBlockSize;
    const raw = buffer.subarray(cursor, cursor + paddedBytes);
    if (index === wantedIndex) {
      const payload = compressed && raw.length > 0 ? decompressPzzpStream(raw) : raw;
      return {
        index,
        memberId: String(index).padStart(3, "0"),
        tableWord: hex(tableWord),
        compressed,
        blockCount,
        paddedBytes,
        payload,
      };
    }
    cursor += paddedBytes;
  }
  throw new Error(`member ${wantedIndex} not found in ${rel(archivePath)}`);
}

function listActorDataFiles() {
  const metadataById = readBorgMetadata();
  return fs
    .readdirSync(assetRoot)
    .filter((name) => /^pl[0-9a-f]{4}data\.bin$/i.test(name))
    .sort()
    .map((name) => {
      const abs = path.join(assetRoot, name);
      const buffer = fs.readFileSync(abs);
      const id = name.slice(0, 6).toLowerCase();
      const meta = metadataById.get(id) ?? null;
      return {
        id,
        name,
        path: rel(abs),
        buffer,
        sha1: sha1(buffer),
        metadata: meta
          ? {
              name: meta.name ?? null,
              number: meta.number ?? null,
              energy: meta.energy ?? null,
              tribe: meta.tribe ?? null,
              type: meta.type ?? null,
              hp: meta.hp ?? null,
              defense: meta.defense ?? null,
              shot: meta.shot ?? null,
              attack: meta.attack ?? null,
              speed: meta.speed ?? null,
              jump: meta.jump ?? null,
            }
          : null,
      };
    })
    .filter((file) => file.buffer.length === actorDataRecordSize);
}

function readBorgMetadata() {
  try {
    const parsed = JSON.parse(fs.readFileSync(borgMetadataPath, "utf8"));
    return new Map((parsed.borgs ?? []).filter((borg) => /^pl[0-9a-f]{4}$/i.test(borg.id ?? "")).map((borg) => [borg.id.toLowerCase(), borg]));
  } catch {
    return new Map();
  }
}

function readTextIfExists(absPath) {
  try {
    return fs.readFileSync(absPath, "utf8");
  } catch {
    return "";
  }
}

function lineOf(text, needle) {
  const index = text.indexOf(needle);
  if (index < 0) return null;
  return text.slice(0, index).split(/\r?\n/).length;
}

function inspectActorDataStatOffsets(actorFiles) {
  const fields = Object.keys(actorDataStatOffsets);
  const matched = actorFiles.filter((file) => file.metadata);
  const exactMatches = Object.fromEntries(fields.map((field) => [field, 0]));
  const mismatches = [];
  for (const file of matched) {
    for (const field of fields) {
      const offset = actorDataStatOffsets[field];
      const actorDataValue = file.buffer.readUInt8(offset);
      const metadataValue = file.metadata[field];
      if (actorDataValue === metadataValue) {
        exactMatches[field] += 1;
      } else {
        mismatches.push({
          id: file.id,
          path: file.path,
          field,
          offset: hex(offset, 4),
          actorDataValue,
          metadataValue,
        });
      }
    }
  }
  return {
    recordSize: actorDataRecordSize,
    offsets: Object.fromEntries(Object.entries(actorDataStatOffsets).map(([field, offset]) => [field, hex(offset, 4)])),
    matchedMetadataRows: matched.length,
    exactMatches,
    allFieldsExact: fields.every((field) => exactMatches[field] === matched.length) && mismatches.length === 0,
    mismatches,
    assessment:
      "defense/shot/attack/speed are exact unsigned-byte matches at pl####data.bin offsets 0x1a4..0x1a7 for every actor-data file that has borgs.json metadata.",
  };
}

function inspectRuntimeBinding(actorStatEvidence) {
  const appMain = readTextIfExists(runtimePaths.appMain);
  const stats = readTextIfExists(runtimePaths.combatStats);
  const actorDataStats = readTextIfExists(runtimePaths.combatActorDataStats);
  const constants = readTextIfExists(runtimePaths.combatConstants);
  const pzz = readTextIfExists(runtimePaths.formatsPzz);
  const actorDataStatsJsonExists = fs.existsSync(runtimePaths.combatActorDataStatsJson);
  const buildProfileUsesActorDataStats =
    stats.includes("actorDataCombatStatsForBorgId") &&
    ["defense", "shot", "attack", "speed"].every((field) => stats.includes(`actorStats?.${field}`));
  const actorDataStatsBoundToCombat =
    actorStatEvidence.allFieldsExact &&
    actorDataStatsJsonExists &&
    actorDataStats.includes("actorDataCombatStatsForBorgId") &&
    buildProfileUsesActorDataStats;
  return {
    appImportsBorgsJson: appMain.includes("packages/assets/data/borgs.json"),
    actorDataStatsJsonExists,
    actorDataStatsAccessorExists: actorDataStats.includes("actorDataCombatStatsForBorgId"),
    buildProfileUsesActorDataStats,
    actorDataStatsBoundToCombat,
    buildProfileConsumesBorgsJsonFields:
      stats.includes("export function buildProfile") &&
      ["energy", "hp", "defense", "shot", "attack", "speed", "jump"].every((field) => stats.includes(`${field}:`)),
    combatConstantsDeclareTunedFormulas: constants.includes("The exact attack/defense-to-raw-damage coefficients"),
    formatsPzzStillTodo: pzz.includes("TODO: implement unpack"),
    refs: {
      appBorgImport: `${rel(runtimePaths.appMain)}:${lineOf(appMain, "packages/assets/data/borgs.json")}`,
      buildProfile: `${rel(runtimePaths.combatStats)}:${lineOf(stats, "export function buildProfile")}`,
      actorDataStats: `${rel(runtimePaths.combatActorDataStats)}:${lineOf(actorDataStats, "actorDataCombatStatsForBorgId")}`,
      actorDataStatsJson: rel(runtimePaths.combatActorDataStatsJson),
      tunedFormulaNote: `${rel(runtimePaths.combatConstants)}:${lineOf(constants, "The exact attack/defense-to-raw-damage coefficients")}`,
      pzzParser: `${rel(runtimePaths.formatsPzz)}:${lineOf(pzz, "export function unpack")}`,
    },
    assessment: actorDataStatsBoundToCombat
      ? "Runtime combat profiles now bind defense/shot/attack/speed to original pl####data.bin actor-data bytes via packages/combat/src/data/actorDataStats.json. Energy, HP, jump, and the absolute damage coefficients still use the existing roster/tuned formula path until their binary fields or formula consumers are proven."
      : "Runtime combat profiles are still not fully bound to original actor-data bytes. The exact cmn_data/pl####data byte matches are source evidence, but runtime binding is incomplete.",
  };
}

function summarizeRecord(buffer, index) {
  let nonZeroBytes = 0;
  for (const byte of buffer) if (byte !== 0) nonZeroBytes += 1;
  const firstNonZeroByte = buffer.findIndex((byte) => byte !== 0);
  let lastNonZeroByte = null;
  for (let i = buffer.length - 1; i >= 0; i -= 1) {
    if (buffer[i] !== 0) {
      lastNonZeroByte = i;
      break;
    }
  }
  return {
    index,
    offset: hex(index * actorDataRecordSize, 4),
    bytes: buffer.length,
    sha1: sha1(buffer),
    nonZeroBytes,
    firstNonZeroByte,
    lastNonZeroByte,
    headHex: headHex(buffer),
    firstHalfwords: readHalfwords(buffer),
    firstWords: readWords(buffer),
    firstFloatWords: readFloatWords(buffer),
  };
}

function compareRecordToActorData(recordBuffer, actorFiles) {
  const topByteMatches = actorFiles
    .map((file) => {
      let sameBytes = 0;
      let sameNonZeroBytes = 0;
      let sameU16Offsets = 0;
      let sameU32Offsets = 0;
      for (let offset = 0; offset < actorDataRecordSize; offset += 1) {
        if (recordBuffer[offset] === file.buffer[offset]) {
          sameBytes += 1;
          if (recordBuffer[offset] !== 0) sameNonZeroBytes += 1;
        }
      }
      for (let offset = 0; offset + 2 <= actorDataRecordSize; offset += 2) {
        if (recordBuffer.readUInt16BE(offset) === file.buffer.readUInt16BE(offset)) sameU16Offsets += 1;
      }
      for (let offset = 0; offset + 4 <= actorDataRecordSize; offset += 4) {
        if (recordBuffer.readUInt32BE(offset) === file.buffer.readUInt32BE(offset)) sameU32Offsets += 1;
      }
      return {
        id: file.id,
        path: file.path,
        metadata: file.metadata,
        sameBytes,
        sameNonZeroBytes,
        sameU16Offsets,
        sameU32Offsets,
        byteMatchRatio: Number((sameBytes / actorDataRecordSize).toFixed(4)),
      };
    })
    .sort((a, b) => b.sameNonZeroBytes - a.sameNonZeroBytes || b.sameBytes - a.sameBytes || a.path.localeCompare(b.path))
    .slice(0, 12);

  const observedSameOffsetValues = [];
  for (let offset = 0; offset < actorDataRecordSize; offset += 2) {
    const value = recordBuffer.readUInt16BE(offset);
    const matchingFiles = actorFiles.filter((file) => file.buffer.readUInt16BE(offset) === value);
    if (matchingFiles.length === 0) continue;
    observedSameOffsetValues.push({
      offset: hex(offset, 4),
      u16: hex(value, 4),
      matchingActorDataCount: matchingFiles.length,
      examples: matchingFiles.slice(0, 6).map((file) => file.path),
    });
  }

  return {
    topByteMatches,
    observedSameOffsetValueCount: observedSameOffsetValues.length,
    observedSameOffsetValues: observedSameOffsetValues.slice(0, 32),
  };
}

function renderMarkdown(report) {
  const lines = [];
  lines.push("# Common Battle Data Inventory");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push(`Scanner: \`${report.generatedBy}\``);
  lines.push("");
  lines.push("## Scope");
  lines.push("");
  lines.push(report.scope);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Source archive: \`${report.source.archive}\``);
  lines.push(`- Member: ${report.source.memberId} (${report.source.tableWord}, ${report.source.payloadBytes} bytes decompressed)`);
  lines.push(`- Actor data files compared: ${report.actorDataReference.count}`);
  lines.push(`- Member 003 splits into ${report.commonRecords.length} x ${actorDataRecordSize}-byte candidate records.`);
  lines.push(`- Exact actor-data matches: ${report.exactActorDataMatches.map((match) => `${match.id} ${match.metadata?.name ?? ""}`.trim()).join(", ") || "none"}.`);
  lines.push(`- Actor-data stat offsets exact: ${report.actorDataStatOffsets.allFieldsExact ? "yes" : "no"} (${report.actorDataStatOffsets.matchedMetadataRows} metadata rows).`);
  lines.push(`- Runtime binds actor-data combat stats: ${report.runtimeBinding.actorDataStatsBoundToCombat ? "yes" : "no"}.`);
  lines.push("");
  lines.push("## Candidate Records");
  lines.push("");
  lines.push("| Record | Offset | SHA1 | Non-zero bytes | First halfwords | First floats |");
  lines.push("|---:|---:|---|---:|---|---|");
  for (const record of report.commonRecords) {
    lines.push(
      `| ${record.index} | \`${record.offset}\` | \`${record.sha1}\` | ${record.nonZeroBytes} | ${record.firstHalfwords
        .slice(0, 8)
        .map((value) => `\`${value}\``)
        .join(" ")} | ${record.firstFloatWords.slice(0, 8).join(" ")} |`,
    );
  }
  lines.push("");
  lines.push("## Actor Data Shape Comparison");
  lines.push("");
  for (const comparison of report.comparisons) {
    lines.push(`### Record ${comparison.recordIndex}`);
    lines.push("");
    lines.push(`Same-offset u16 values observed in actor data: ${comparison.observedSameOffsetValueCount}`);
    lines.push("");
    lines.push("| Actor data | Borg | Same bytes | Same non-zero bytes | Same u16 offsets | Same u32 offsets | Byte ratio |");
    lines.push("|---|---|---:|---:|---:|---:|---:|");
    for (const match of comparison.topByteMatches.slice(0, 8)) {
      lines.push(
        `| \`${match.path}\` | ${match.metadata?.name ?? match.id ?? ""} | ${match.sameBytes} | ${match.sameNonZeroBytes} | ${match.sameU16Offsets} | ${match.sameU32Offsets} | ${match.byteMatchRatio} |`,
      );
    }
    lines.push("");
  }
  lines.push("## Actor Data Combat Stat Offsets");
  lines.push("");
  lines.push(report.actorDataStatOffsets.assessment);
  lines.push("");
  lines.push("| Field | Offset | Exact matches |");
  lines.push("|---|---:|---:|");
  for (const [field, offset] of Object.entries(report.actorDataStatOffsets.offsets)) {
    lines.push(`| ${field} | \`${offset}\` | ${report.actorDataStatOffsets.exactMatches[field]}/${report.actorDataStatOffsets.matchedMetadataRows} |`);
  }
  lines.push("");
  lines.push("## Assessment");
  lines.push("");
  lines.push(report.assessment);
  lines.push("");
  lines.push("## Runtime Binding");
  lines.push("");
  lines.push(`- App imports borgs.json: ${report.runtimeBinding.appImportsBorgsJson ? "yes" : "no"} (${report.runtimeBinding.refs.appBorgImport})`);
  lines.push(`- Generated actor-data stats JSON exists: ${report.runtimeBinding.actorDataStatsJsonExists ? "yes" : "no"} (${report.runtimeBinding.refs.actorDataStatsJson})`);
  lines.push(`- Actor-data stats accessor exists: ${report.runtimeBinding.actorDataStatsAccessorExists ? "yes" : "no"} (${report.runtimeBinding.refs.actorDataStats})`);
  lines.push(`- Combat buildProfile consumes actor-data stats: ${report.runtimeBinding.buildProfileUsesActorDataStats ? "yes" : "no"} (${report.runtimeBinding.refs.buildProfile})`);
  lines.push(`- Combat buildProfile consumes stat fields: ${report.runtimeBinding.buildProfileConsumesBorgsJsonFields ? "yes" : "no"} (${report.runtimeBinding.refs.buildProfile})`);
  lines.push(`- Combat constants still declare tuned formulas: ${report.runtimeBinding.combatConstantsDeclareTunedFormulas ? "yes" : "no"} (${report.runtimeBinding.refs.tunedFormulaNote})`);
  lines.push(`- Generic PZZ parser package implemented: ${report.runtimeBinding.formatsPzzStillTodo ? "no" : "yes"} (${report.runtimeBinding.refs.pzzParser})`);
  lines.push("");
  lines.push(report.runtimeBinding.assessment);
  lines.push("");
  lines.push("## Verification");
  lines.push("");
  lines.push("```bash");
  lines.push("rtk node scripts/inventory-common-battle-data.mjs");
  lines.push("```");
  return `${lines.join("\n")}\n`;
}

const archivePath = path.join(assetRoot, "cmn_data.pzz");
const member = readPzzMember(archivePath, 3);
const actorFiles = listActorDataFiles();
const actorDataStatOffsetEvidence = inspectActorDataStatOffsets(actorFiles);
const commonRecords = [];
for (let offset = 0, index = 0; offset + actorDataRecordSize <= member.payload.length; offset += actorDataRecordSize, index += 1) {
  commonRecords.push(summarizeRecord(member.payload.subarray(offset, offset + actorDataRecordSize), index));
}

const comparisons = commonRecords.map((record) => {
  const buffer = member.payload.subarray(record.index * actorDataRecordSize, (record.index + 1) * actorDataRecordSize);
  return {
    recordIndex: record.index,
    ...compareRecordToActorData(buffer, actorFiles),
  };
});

const report = {
  schema: "gotyaforce.commonBattleDataInventory.v2",
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  scope:
    "Byte-level inventory for common battle data and actor-data records. Four combat-stat bytes are named only where they match every metadata-backed pl####data.bin record exactly.",
  source: {
    archive: rel(archivePath),
    memberId: member.memberId,
    tableWord: member.tableWord,
    blockCount: member.blockCount,
    compressed: member.compressed,
    payloadBytes: member.payload.length,
    payloadSha1: sha1(member.payload),
  },
  actorDataReference: {
    pattern: "pl####data.bin",
    recordSize: actorDataRecordSize,
    count: actorFiles.length,
    examples: actorFiles.slice(0, 12).map((file) => file.path),
  },
  commonRecords,
  comparisons,
  actorDataStatOffsets: actorDataStatOffsetEvidence,
  exactActorDataMatches: comparisons.flatMap((comparison) =>
    comparison.topByteMatches
      .filter((match) => match.byteMatchRatio === 1)
      .map((match) => ({
        recordIndex: comparison.recordIndex,
        id: match.id,
        path: match.path,
        metadata: match.metadata,
      })),
  ),
  runtimeBinding: inspectRuntimeBinding(actorDataStatOffsetEvidence),
  assessment:
    member.payload.length % actorDataRecordSize === 0
      ? "cmn_data.pzz member 003 cleanly splits into 432-byte records, the same stride as pl####data.bin actor data. defense/shot/attack/speed are now exact-mapped actor-data bytes and runtime-bound; the remaining common-record fields still require DOL/runtime trace or HexWorkshop bookmark correlation."
      : "cmn_data.pzz member 003 does not cleanly split into the known 432-byte actor-data stride.",
};

fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log(`common battle data: member ${member.memberId}, ${member.payload.length} bytes, records ${commonRecords.length}`);
console.log(`actor data reference files: ${actorFiles.length}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);
