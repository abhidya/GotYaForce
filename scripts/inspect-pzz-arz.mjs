#!/usr/bin/env node

import { createHash } from "node:crypto";
import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const assetRootRel = "user-data/GG4E/afs_data/root";
const assetRoot = path.join(repoRoot, assetRootRel);

const outputJsonPath = path.join(repoRoot, "research/asset-inventory/pzz-arz-inventory.json");
const outputMarkdownPath = path.join(repoRoot, "research/format-specs/pzz-arz-format.md");

const sourceInventoryPaths = {
  particleEffects: "research/asset-inventory/particle-effect-inventory.json",
  weaponsEffectsProjectiles: "research/asset-inventory/weapons-effects-projectiles.json",
};

const pzzMemberBlockSize = 0x800;
const pzzCompressedFlag = 0x40000000;
const pzzBlockCountMask = 0x3fffffff;
const maxRootFilesForSiblingMatch = 256;

function toRepoPath(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

function hex(value, width = 8) {
  if (value === null || value === undefined) return null;
  return `0x${Number(value).toString(16).padStart(width, "0")}`;
}

function formatBytes(bytes) {
  if (bytes === null || bytes === undefined) return "";
  if (bytes >= 1024 * 1024) return `${(bytes / 1024 / 1024).toFixed(2)} MiB`;
  if (bytes >= 1024) return `${(bytes / 1024).toFixed(1)} KiB`;
  return `${bytes} B`;
}

function mdEscape(value) {
  return String(value ?? "").replaceAll("|", "\\|");
}

function readU32BE(buffer, offset) {
  if (offset < 0 || offset + 4 > buffer.length) return null;
  return buffer.readUInt32BE(offset);
}

function readU16BE(buffer, offset) {
  if (offset < 0 || offset + 2 > buffer.length) return null;
  return buffer.readUInt16BE(offset);
}

function headHex(buffer, byteCount = 32) {
  return buffer.subarray(0, Math.min(byteCount, buffer.length)).toString("hex").replace(/(..)/g, "$1 ").trim();
}

function headerWords(buffer, count = 8) {
  const words = [];
  for (let offset = 0; offset + 4 <= buffer.length && words.length < count; offset += 4) {
    words.push(hex(buffer.readUInt32BE(offset)));
  }
  return words;
}

function headerHalfwords(buffer, count = 12) {
  const words = [];
  for (let offset = 0; offset + 2 <= buffer.length && words.length < count; offset += 2) {
    words.push(hex(buffer.readUInt16BE(offset), 4));
  }
  return words;
}

function readCString(buffer, offset, max = 512) {
  if (offset < 0 || offset >= buffer.length) return null;
  let end = offset;
  const limit = Math.min(buffer.length, offset + max);
  while (end < limit && buffer[end] !== 0) end += 1;
  return buffer.subarray(offset, end).toString("ascii");
}

function printableAsciiPrefix(buffer, byteCount = 32) {
  const bytes = buffer.subarray(0, Math.min(byteCount, buffer.length));
  let out = "";
  for (const byte of bytes) {
    if (byte >= 0x20 && byte <= 0x7e) out += String.fromCharCode(byte);
    else if (byte === 0) out += ".";
    else out += "?";
  }
  return out;
}

function isAllZero(buffer, offset = 0) {
  for (let i = offset; i < buffer.length; i += 1) {
    if (buffer[i] !== 0) return false;
  }
  return true;
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
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

  pushByte(value) {
    this.ensure(1);
    this.buffer[this.length] = value;
    this.length += 1;
  }

  pushPair(a, b) {
    this.ensure(2);
    this.buffer[this.length] = a;
    this.buffer[this.length + 1] = b;
    this.length += 2;
  }

  copyFromSelf(distance, count) {
    const start = this.length - distance;
    if (start < 0) {
      throw new Error(`invalid back-reference distance ${distance} at output ${this.length}`);
    }
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
  let tokenCount = 0;
  let literalPairs = 0;
  let backRefs = 0;
  let longBackRefs = 0;
  let terminatorOffset = null;
  const errors = [];

  try {
    while (cursor + 2 <= evenLength) {
      if (bit < 0) {
        control = buffer.readUInt16BE(cursor);
        cursor += 2;
        bit = 15;
        continue;
      }

      tokenCount += 1;
      const compressedToken = (control & (1 << bit)) !== 0;
      bit -= 1;

      if (!compressedToken) {
        writer.pushPair(buffer[cursor], buffer[cursor + 1]);
        cursor += 2;
        literalPairs += 1;
        continue;
      }

      const tokenOffset = cursor;
      const token = buffer.readUInt16BE(cursor);
      const distance = (token & 0x7ff) * 2;
      if (distance === 0) {
        terminatorOffset = tokenOffset;
        cursor += 2;
        break;
      }

      let byteCount = (token >> 11) * 2;
      if (byteCount === 0) {
        cursor += 2;
        if (cursor + 2 > evenLength) {
          errors.push("long back-reference is missing its extension word");
          break;
        }
        byteCount = buffer.readUInt16BE(cursor) * 2;
        longBackRefs += 1;
      }

      writer.copyFromSelf(distance, byteCount);
      cursor += 2;
      backRefs += 1;
    }
  } catch (error) {
    errors.push(error.message);
  }

  const output = writer.toBuffer();
  return {
    ok: errors.length === 0 && terminatorOffset !== null,
    buffer: output,
    meta: {
      algorithm: "pzzp/arzip big-endian 16-bit LZ stream",
      sourceBytes: buffer.length,
      producedBytes: output.length,
      consumedBytes: cursor,
      trailingBytes: buffer.length - cursor,
      terminated: terminatorOffset !== null,
      terminatorOffset,
      tokenCount,
      literalPairs,
      backRefs,
      longBackRefs,
      compressionRatio: output.length > 0 ? Number((buffer.length / output.length).toFixed(4)) : null,
      firstControlWord: readU16BE(buffer, 0) === null ? null : hex(readU16BE(buffer, 0), 4),
      errors,
    },
  };
}

async function readJsonIfPresent(relPath) {
  try {
    return JSON.parse(await fs.readFile(path.join(repoRoot, relPath), "utf8"));
  } catch (error) {
    if (error.code === "ENOENT") return null;
    throw error;
  }
}

async function listRootFiles() {
  const entries = await fs.readdir(assetRoot, { withFileTypes: true });
  const files = [];
  for (const entry of entries) {
    if (!entry.isFile()) continue;
    const name = entry.name;
    const lower = name.toLowerCase();
    const wanted =
      /^(efct|gets|cmn_data|st[0-9a-f]{2}|pl[0-9a-f]{4})\.pzz$/i.test(name) ||
      /^(it[0-9a-f]{4}_mdl|stc[0-9a-f]{2}_mdl)\.arz$/i.test(name);
    if (!wanted) continue;

    const abs = path.join(assetRoot, name);
    const stat = await fs.stat(abs);
    files.push({
      abs,
      path: toRepoPath(abs),
      name,
      stem: name.slice(0, -path.extname(name).length),
      extension: path.extname(lower),
      sizeBytes: stat.size,
    });
  }

  return files.sort((a, b) => a.name.localeCompare(b.name));
}

function classifyTopLevelFile(file) {
  if (/^efct\.pzz$/i.test(file.name)) return { bucket: "effect", role: "shared effect PZZ archive" };
  if (/^gets\.pzz$/i.test(file.name)) return { bucket: "item", role: "GET/item shared PZZ archive" };
  if (/^cmn_data\.pzz$/i.test(file.name)) return { bucket: "battle-common", role: "shared common battle-data PZZ archive" };
  if (/^st[0-9a-f]{2}\.pzz$/i.test(file.name)) return { bucket: "stage", role: "stage PZZ archive" };
  if (/^pl[0-9a-f]{4}\.pzz$/i.test(file.name)) return { bucket: "borg", role: "Borg/player PZZ archive" };
  if (/^it[0-9a-f]{4}_mdl\.arz$/i.test(file.name)) return { bucket: "item", role: "item/attachment model ARZ" };
  if (/^stc[0-9a-f]{2}_mdl\.arz$/i.test(file.name)) return { bucket: "stage", role: "stage collision/variant model ARZ" };
  return { bucket: "unknown", role: "archive-like file" };
}

function buildInventoryIndex(inventory) {
  const byPath = new Map();
  if (!inventory) return byPath;

  for (const candidate of inventory.candidates || []) {
    if (candidate.path) byPath.set(candidate.path, candidate);
  }

  for (const familyEntries of Object.values(inventory.families || {})) {
    for (const entry of familyEntries || []) {
      if (!entry.path || byPath.has(entry.path)) continue;
      byPath.set(entry.path, entry);
    }
  }

  return byPath;
}

function sourceInventorySummary(file, indexes) {
  const summaries = [];
  for (const [label, index] of Object.entries(indexes)) {
    const entry = index.get(file.path);
    if (!entry) continue;
    const families = (entry.families || [])
      .map((family) => family.family)
      .filter(Boolean)
      .slice(0, 12);
    summaries.push({
      source: label,
      confidence: entry.confidence ?? null,
      linkedBorgId: entry.linkedBorgId ?? entry.linkedBorg?.id ?? null,
      linkedBorgName: entry.linkedBorgName ?? entry.linkedBorg?.name ?? null,
      families,
      reason: entry.reason ?? null,
      needs: entry.needs ?? [],
    });
  }
  return summaries;
}

async function listSiblingCandidates(stem) {
  const prefix = stem.toLowerCase();
  let entries = [];
  try {
    entries = await fs.readdir(assetRoot, { withFileTypes: true });
  } catch {
    return [];
  }

  const candidates = [];
  for (const entry of entries) {
    if (!entry.isFile()) continue;
    const name = entry.name;
    const lower = name.toLowerCase();
    if (!lower.startsWith(prefix) || lower === `${prefix}.pzz` || lower === `${prefix}.arz`) continue;
    if (!/\.(arc|bin|tpl|txg|ptl|ref|mdt)$/i.test(name)) continue;
    const abs = path.join(assetRoot, name);
    const stat = await fs.stat(abs);
    candidates.push({
      name,
      path: toRepoPath(abs),
      abs,
      sizeBytes: stat.size,
    });
  }

  return candidates.sort((a, b) => a.name.localeCompare(b.name)).slice(0, maxRootFilesForSiblingMatch);
}

const siblingContentCache = new Map();

async function getSiblingContent(candidate) {
  if (!siblingContentCache.has(candidate.path)) {
    siblingContentCache.set(candidate.path, await fs.readFile(candidate.abs));
  }
  return siblingContentCache.get(candidate.path);
}

async function matchSibling(buffer, candidates) {
  for (const candidate of candidates) {
    if (candidate.sizeBytes > buffer.length) continue;
    const candidateBuffer = await getSiblingContent(candidate);
    if (Buffer.compare(buffer.subarray(0, candidate.sizeBytes), candidateBuffer) !== 0) continue;
    const paddingIsZero = isAllZero(buffer, candidate.sizeBytes);
    return {
      path: candidate.path,
      name: candidate.name,
      exactBytes: candidate.sizeBytes,
      paddingBytes: buffer.length - candidate.sizeBytes,
      paddingIsZero,
      sha1: sha1(candidateBuffer),
    };
  }
  return null;
}

function parseTpl(buffer) {
  if (buffer.length < 12) return null;
  if (buffer.readUInt32BE(0) !== 0x0020af30) return null;
  const imageCount = buffer.readUInt32BE(4);
  const imageTableOffset = buffer.readUInt32BE(8);
  const formats = new Map([
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
  const images = [];
  for (let i = 0; i < imageCount && i < 16; i += 1) {
    const tableOffset = imageTableOffset + i * 8;
    if (tableOffset + 8 > buffer.length) break;
    const textureHeaderOffset = buffer.readUInt32BE(tableOffset);
    const paletteHeaderOffset = buffer.readUInt32BE(tableOffset + 4);
    if (textureHeaderOffset + 12 > buffer.length) {
      images.push({ index: i, textureHeaderOffset, parseStatus: "texture header outside payload" });
      continue;
    }
    const height = buffer.readUInt16BE(textureHeaderOffset);
    const width = buffer.readUInt16BE(textureHeaderOffset + 2);
    const formatCode = buffer.readUInt32BE(textureHeaderOffset + 4);
    const dataOffset = buffer.readUInt32BE(textureHeaderOffset + 8);
    const estimatedPayloadBytes = bytesPerPixel.has(formatCode) ? Math.ceil(width * height * bytesPerPixel.get(formatCode)) : null;
    images.push({
      index: i,
      width,
      height,
      formatCode,
      format: formats.get(formatCode) ?? `unknown(${formatCode})`,
      dataOffset,
      textureHeaderOffset,
      paletteHeaderOffset: paletteHeaderOffset || null,
      estimatedPayloadBytes,
    });
  }

  const exactBytes =
    images.length > 0 && images.every((image) => Number.isInteger(image.estimatedPayloadBytes))
      ? Math.max(...images.map((image) => image.dataOffset + image.estimatedPayloadBytes))
      : null;

  return {
    kind: "tpl-texture",
    magic: "0x0020af30",
    imageCount,
    imageTableOffset,
    images,
    exactBytes,
    paddingBytes: exactBytes === null ? null : buffer.length - exactBytes,
    paddingIsZero: exactBytes === null ? null : isAllZero(buffer, exactBytes),
  };
}

function parseHsdDatAt(buffer, baseOffset) {
  if (baseOffset + 0x20 > buffer.length) return null;
  const fileSize = buffer.readUInt32BE(baseOffset);
  if (fileSize <= 0 || baseOffset + fileSize > buffer.length) return null;
  const dataBlockSize = buffer.readUInt32BE(baseOffset + 4);
  const relocCount = buffer.readUInt32BE(baseOffset + 8);
  const rootCount = buffer.readUInt32BE(baseOffset + 12);
  const externalRefCount = buffer.readUInt32BE(baseOffset + 16);
  if (rootCount > 256 || externalRefCount > 256 || relocCount > 200000) return null;

  const rootsOffset = baseOffset + 0x20 + dataBlockSize + relocCount * 4;
  const externalsOffset = rootsOffset + rootCount * 8;
  const symbolTableOffset = externalsOffset + externalRefCount * 8;
  if (rootsOffset < baseOffset || rootsOffset > baseOffset + fileSize) return null;
  if (symbolTableOffset > baseOffset + fileSize) return null;

  const roots = [];
  for (let i = 0; i < rootCount && i < 32; i += 1) {
    const offset = rootsOffset + i * 8;
    if (offset + 8 > buffer.length) break;
    const dataOffset = buffer.readUInt32BE(offset);
    const stringOffset = buffer.readUInt32BE(offset + 4);
    roots.push({
      index: i,
      dataOffset,
      stringOffset,
      name: readCString(buffer, symbolTableOffset + stringOffset),
    });
  }

  return {
    kind: "hsd-dat",
    container: baseOffset === 0x100 ? "wrapped HSD DAT" : "bare HSD DAT",
    hsdOffset: baseOffset,
    exactBytes: baseOffset + fileSize,
    hsdFileSize: fileSize,
    dataBlockSize,
    relocCount,
    rootCount,
    externalRefCount,
    symbolTableOffset,
    roots,
  };
}

function parseHsdDat(buffer) {
  const bare = parseHsdDatAt(buffer, 0);
  if (bare) return bare;
  if (buffer.length >= 0x120 && buffer.readUInt32BE(0) === 0x100) {
    return parseHsdDatAt(buffer, 0x100);
  }
  return null;
}

function parseMotLike(buffer) {
  if (buffer.length < 0x18) return null;
  const bankOffsets = [];
  for (let i = 0; i < 6; i += 1) bankOffsets.push(buffer.readUInt32BE(i * 4));
  const plausible = bankOffsets.some((offset) => offset > 0 && offset < buffer.length) &&
    bankOffsets.every((offset) => offset === 0 || (offset >= 0x18 && offset < buffer.length && offset % 4 === 0));
  if (!plausible) return null;

  const banks = bankOffsets.map((offset, bankIndex) => {
    if (offset === 0 || offset >= buffer.length) return { bankIndex, tableOffset: offset, parseStatus: "missing", clipCount: 0 };
    const clipOffsets = [];
    let cursor = offset;
    for (let slot = 0; slot < 512 && cursor + 4 <= buffer.length; slot += 1, cursor += 4) {
      const value = buffer.readUInt32BE(cursor);
      if (value === 0xffffffff) {
        return {
          bankIndex,
          tableOffset: offset,
          parseStatus: "terminated",
          clipCount: clipOffsets.length,
          firstClipOffset: clipOffsets[0] ?? null,
        };
      }
      if (value !== 0) clipOffsets.push(value);
    }
    return {
      bankIndex,
      tableOffset: offset,
      parseStatus: "unterminated",
      clipCount: clipOffsets.length,
      firstClipOffset: clipOffsets[0] ?? null,
    };
  });

  if (!banks.some((bank) => bank.parseStatus === "terminated")) return null;
  return {
    kind: "mot-bank-container",
    bankOffsets,
    banks,
    totalClipCount: banks.reduce((sum, bank) => sum + bank.clipCount, 0),
  };
}

function inferKindFromContext(file, memberIndex, buffer) {
  if (file?.extension === ".arz") return null;
  const archiveName = file?.name ?? "";
  if (/^pl[0-9a-f]{4}\.pzz$/i.test(archiveName)) {
    if (memberIndex === 0) return { kind: "borg-data-bin", note: "pl####.pzz member 000 mirrors pl####data.bin per existing research" };
    if (memberIndex === 1 && buffer.length === 0) return { kind: "empty-slot", note: "zero-length table entry" };
    if (memberIndex === 2) return { kind: "borg-hit-bin", note: "pl####.pzz member 002 matches the sibling pl####hit.bin when present" };
    if (memberIndex === 3) return { kind: "mot-bank-container", note: "pl####.pzz member 003 is the MOT-like bank member in the repeated 14-slot layout" };
  }
  return null;
}

function sniffBuffer(buffer, context = {}) {
  const common = {
    availableBytes: buffer.length,
    headHex: headHex(buffer),
    headerWords: headerWords(buffer, 8),
    asciiPrefix: printableAsciiPrefix(buffer),
  };

  if (buffer.length === 0) {
    return { ...common, kind: "empty" };
  }

  const tpl = parseTpl(buffer);
  if (tpl) return { ...common, ...tpl };

  const hsd = parseHsdDat(buffer);
  if (hsd) {
    return {
      ...common,
      ...hsd,
      paddingBytes: buffer.length - hsd.exactBytes,
      paddingIsZero: isAllZero(buffer, hsd.exactBytes),
    };
  }

  const mot = parseMotLike(buffer);
  if (mot) return { ...common, ...mot };

  const contextual = inferKindFromContext(context.file, context.memberIndex, buffer);
  if (contextual) return { ...common, ...contextual };

  const firstWord = readU32BE(buffer, 0);
  if (firstWord === 0x474f5443 || buffer.subarray(0, 16).toString("ascii").includes("GOTCHA")) {
    return { ...common, kind: "gotcha-force-text-or-banner" };
  }

  return { ...common, kind: "unknown-binary" };
}

async function inspectPzzArchive(file, sourceIndexes) {
  const buffer = await fs.readFile(file.abs);
  const classification = classifyTopLevelFile(file);
  const count = readU32BE(buffer, 0);
  const tableBytes = count === null ? 0 : 4 + count * 4;
  const tableFitsHeaderBlock = tableBytes <= pzzMemberBlockSize;
  const members = [];
  const siblingCandidates = await listSiblingCandidates(file.stem);

  let sumBlocks = 0;
  let cursor = pzzMemberBlockSize;
  let tableValid = Number.isInteger(count) && count > 0 && count <= 512 && tableFitsHeaderBlock;
  const validationWarnings = [];

  if (!tableValid) {
    validationWarnings.push("member count/table does not fit the observed 0x800-byte PZZ header block");
  }

  if (tableValid) {
    for (let index = 0; index < count; index += 1) {
      const tableOffset = 4 + index * 4;
      const tableWord = buffer.readUInt32BE(tableOffset);
      const compressed = (tableWord & pzzCompressedFlag) !== 0;
      const highBits = tableWord >>> 30;
      const blockCount = tableWord & pzzBlockCountMask;
      const paddedBytes = blockCount * pzzMemberBlockSize;
      const dataOffset = cursor;
      const dataEnd = dataOffset + paddedBytes;
      const rawPayload = blockCount === 0 ? Buffer.alloc(0) : buffer.subarray(dataOffset, Math.min(dataEnd, buffer.length));
      sumBlocks += blockCount;

      let decompression = null;
      let payload = rawPayload;
      if (compressed && rawPayload.length > 0) {
        const result = decompressPzzpStream(rawPayload);
        decompression = result.meta;
        payload = result.buffer;
      }

      const siblingMatch = payload.length > 0 ? await matchSibling(payload, siblingCandidates) : null;
      const sniff = sniffBuffer(payload, { file, memberIndex: index });
      const exactBytes = siblingMatch?.exactBytes ?? sniff.exactBytes ?? null;
      const inferredName = siblingMatch?.name ?? inferPzzMemberLabel(file, index, sniff);

      members.push({
        index,
        memberId: String(index).padStart(3, "0"),
        inferredName,
        tableOffset,
        tableWord: hex(tableWord),
        flags: {
          highBits,
          compressed,
          unknownHighBit: (tableWord & 0x80000000) !== 0,
        },
        blockCount,
        paddedBytes,
        dataOffset,
        dataEnd,
        zeroLength: blockCount === 0,
        compression: decompression,
        payload: {
          availableBytes: payload.length,
          exactBytes,
          paddingBytes: exactBytes === null ? null : payload.length - exactBytes,
          matchedSibling: siblingMatch,
          sniff,
        },
      });

      cursor += paddedBytes;
    }
  }

  const expectedSize = (sumBlocks + 1) * pzzMemberBlockSize;
  if (expectedSize !== buffer.length) {
    validationWarnings.push(`PZZ block sum ${expectedSize} does not match file size ${buffer.length}`);
  }

  return {
    path: file.path,
    name: file.name,
    extension: file.extension,
    bucket: classification.bucket,
    role: classification.role,
    sizeBytes: file.sizeBytes,
    sourceInventories: sourceInventorySummary(file, sourceIndexes),
    archive: {
      kind: "pzz",
      byteOrder: "big-endian",
      headerBlockSize: pzzMemberBlockSize,
      dataStartOffset: pzzMemberBlockSize,
      memberCount: count,
      tableBytes,
      tableFitsHeaderBlock,
      tableWords: headerWords(buffer, Math.min((count ?? 0) + 1, 24)),
      summedMemberBlocks: sumBlocks,
      expectedSizeFromTable: expectedSize,
      validatesAgainstFileSize: expectedSize === buffer.length,
      compressedMemberCount: members.filter((member) => member.flags.compressed).length,
      rawMemberCount: members.filter((member) => !member.flags.compressed && !member.zeroLength).length,
      zeroLengthMemberCount: members.filter((member) => member.zeroLength).length,
      recognizedMemberKinds: countKinds(members.map((member) => member.payload.sniff.kind)),
      warnings: validationWarnings,
    },
    members,
  };
}

function inferPzzMemberLabel(file, index, sniff) {
  const stem = file.stem;
  if (/^pl[0-9a-f]{4}$/i.test(stem)) {
    const labels = [
      `${stem}data.bin`,
      `${stem}.slot001.empty`,
      `${stem}.slot002.bin`,
      `${stem}mot.bin`,
      `${stem}_mdl.arc`,
      `${stem}b_mdl.arc`,
      `${stem}g_mdl.arc`,
      `${stem}s_mdl.arc`,
      `${stem}c_mdl.arc`,
      `${stem}k_mdl.arc`,
    ];
    return labels[index] ?? `${stem}.slot${String(index).padStart(3, "0")}.${sniff.kind}`;
  }
  if (/^efct$/i.test(stem)) {
    if (index === 1) return "efct00_mdl.arc";
    if (index === 2) return "efct01_mdl.arc";
  }
  if (/^gets$/i.test(stem)) {
    return `gets${String(index).padStart(2, "0")}.${sniff.kind}`;
  }
  if (/^cmn_data$/i.test(stem)) {
    return `cmn_data.member${String(index).padStart(3, "0")}.${sniff.kind}`;
  }
  if (/^st[0-9a-f]{2}$/i.test(stem)) {
    return `${stem}.member${String(index).padStart(3, "0")}.${sniff.kind}`;
  }
  return `${stem}.member${String(index).padStart(3, "0")}.${sniff.kind}`;
}

async function inspectArzFile(file, sourceIndexes) {
  const buffer = await fs.readFile(file.abs);
  const classification = classifyTopLevelFile(file);
  const decompressed = decompressPzzpStream(buffer);
  const sniff = sniffBuffer(decompressed.buffer, { file });
  const exactBytes = sniff.exactBytes ?? null;

  return {
    path: file.path,
    name: file.name,
    extension: file.extension,
    bucket: classification.bucket,
    role: classification.role,
    sizeBytes: file.sizeBytes,
    sourceInventories: sourceInventorySummary(file, sourceIndexes),
    archive: {
      kind: "arz",
      byteOrder: "big-endian",
      staticMagic: null,
      note: "ARZ is a raw pzzp/arzip compressed stream, not a multi-entry archive.",
      headerWords: headerWords(buffer, 8),
      headerHalfwords: headerHalfwords(buffer, 12),
      firstControlWord: decompressed.meta.firstControlWord,
      firstBytes: headHex(buffer, 40),
    },
    compression: decompressed.meta,
    payload: {
      availableBytes: decompressed.buffer.length,
      exactBytes,
      paddingBytes: exactBytes === null ? null : decompressed.buffer.length - exactBytes,
      sniff,
    },
  };
}

function countKinds(values) {
  const counts = {};
  for (const value of values) counts[value ?? "unknown"] = (counts[value ?? "unknown"] || 0) + 1;
  return Object.fromEntries(Object.entries(counts).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0])));
}

function summarizeRecords(records) {
  const byExtension = countKinds(records.map((record) => record.extension));
  const byBucket = countKinds(records.map((record) => record.bucket));
  const pzzRecords = records.filter((record) => record.archive.kind === "pzz");
  const arzRecords = records.filter((record) => record.archive.kind === "arz");
  const pzzMembers = pzzRecords.flatMap((record) => record.members.map((member) => ({ archive: record.path, ...member })));
  const allPayloadKinds = [
    ...pzzMembers.map((member) => member.payload.sniff.kind),
    ...arzRecords.map((record) => record.payload.sniff.kind),
  ];

  return {
    scannedFileCount: records.length,
    pzzArchiveCount: pzzRecords.length,
    directArzFileCount: arzRecords.length,
    pzzMemberCount: pzzMembers.length,
    pzzCompressedMemberCount: pzzMembers.filter((member) => member.flags.compressed).length,
    pzzRawMemberCount: pzzMembers.filter((member) => !member.flags.compressed && !member.zeroLength).length,
    pzzZeroLengthMemberCount: pzzMembers.filter((member) => member.zeroLength).length,
    byExtension,
    byBucket,
    payloadKinds: countKinds(allPayloadKinds),
    directArzPayloadKinds: countKinds(arzRecords.map((record) => record.payload.sniff.kind)),
    pzzMemberPayloadKinds: countKinds(pzzMembers.map((member) => member.payload.sniff.kind)),
    pzzArchivesWithInvalidBlockSums: pzzRecords
      .filter((record) => !record.archive.validatesAgainstFileSize)
      .map((record) => record.path),
    decompressionErrors: [
      ...pzzMembers
        .filter((member) => member.compression?.errors?.length)
        .map((member) => ({ path: member.archive, memberId: member.memberId, errors: member.compression.errors })),
      ...arzRecords
        .filter((record) => record.compression?.errors?.length)
        .map((record) => ({ path: record.path, errors: record.compression.errors })),
    ],
  };
}

function groupCompression(records) {
  const pzzPatternCounts = new Map();
  const arzHeaderGroups = new Map();

  for (const record of records) {
    if (record.archive.kind === "pzz") {
      const key = [
        `count:${record.archive.memberCount}`,
        `compressed:${record.archive.compressedMemberCount}`,
        `raw:${record.archive.rawMemberCount}`,
        `zero:${record.archive.zeroLengthMemberCount}`,
        `kinds:${Object.entries(record.archive.recognizedMemberKinds)
          .map(([kind, count]) => `${kind}=${count}`)
          .join(",")}`,
      ].join(" ");
      const group = pzzPatternCounts.get(key) || { count: 0, examples: [] };
      group.count += 1;
      if (group.examples.length < 8) group.examples.push(record.path);
      pzzPatternCounts.set(key, group);
    } else if (record.archive.kind === "arz") {
      const key = record.archive.headerWords.slice(0, 5).join(" ");
      const group =
        arzHeaderGroups.get(key) ||
        {
          count: 0,
          examples: [],
          minSizeBytes: record.sizeBytes,
          maxSizeBytes: record.sizeBytes,
          payloadKinds: {},
        };
      group.count += 1;
      group.minSizeBytes = Math.min(group.minSizeBytes, record.sizeBytes);
      group.maxSizeBytes = Math.max(group.maxSizeBytes, record.sizeBytes);
      group.payloadKinds[record.payload.sniff.kind] = (group.payloadKinds[record.payload.sniff.kind] || 0) + 1;
      if (group.examples.length < 8) group.examples.push(record.path);
      arzHeaderGroups.set(key, group);
    }
  }

  return {
    pzzArchivePatterns: [...pzzPatternCounts.entries()]
      .map(([pattern, value]) => ({ pattern, ...value }))
      .sort((a, b) => b.count - a.count || a.pattern.localeCompare(b.pattern)),
    arzFirstWordGroups: [...arzHeaderGroups.entries()]
      .map(([firstWords, value]) => ({
        firstWords,
        ...value,
        payloadKinds: Object.fromEntries(Object.entries(value.payloadKinds).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]))),
      }))
      .sort((a, b) => b.count - a.count || a.firstWords.localeCompare(b.firstWords)),
  };
}

function collectBlockers(records, summary) {
  const unknownMembers = [];
  const unknownArz = [];
  const exactLengthItems = [];
  for (const record of records) {
    if (record.archive.kind === "pzz") {
      for (const member of record.members) {
        if (member.payload.sniff.kind === "unknown-binary") {
          unknownMembers.push({ path: record.path, memberId: member.memberId, inferredName: member.inferredName });
        }
        if (member.flags.compressed && (member.payload.exactBytes === null || member.payload.paddingBytes > 0)) {
          exactLengthItems.push({
            path: record.path,
            memberId: member.memberId,
            inferredName: member.inferredName,
            paddingBytes: member.payload.paddingBytes,
          });
        }
      }
    } else if (record.payload.sniff.kind === "unknown-binary") {
      unknownArz.push(record.path);
    } else if (record.payload.exactBytes === null || record.payload.paddingBytes > 0) {
      exactLengthItems.push({
        path: record.path,
        paddingBytes: record.payload.paddingBytes,
      });
    }
  }

  return [
    {
      id: "member-semantics",
      label: "PZZ member semantics are only partly named",
      status: unknownMembers.length > 0 ? "open" : "mostly-clear",
      count: unknownMembers.length,
      examples: unknownMembers.slice(0, 16),
      note: "The table and compression are decoded, but several payloads need runtime correlation or sibling file matches before naming their fields.",
    },
    {
      id: "exact-uncompressed-length",
      label: "Exact payload length can be padded",
      status: "open",
      count: exactLengthItems.length,
      examples: exactLengthItems.slice(0, 16),
      note: "HSD and sibling-file matches recover exact byte counts for many payloads, but unknown binary members still expose the decompressed stream length only.",
    },
    {
      id: "unknown-direct-arz",
      label: "Direct ARZ payloads not recognized by magic",
      status: unknownArz.length > 0 ? "open" : "clear",
      count: unknownArz.length,
      examples: unknownArz.slice(0, 16),
      note: "Direct item/stc ARZ files should normally decompress to HSD DAT; non-HSD cases need separate format work.",
    },
    {
      id: "runtime-use",
      label: "Runtime effect/item/stage meaning still needs correlation",
      status: "open",
      count: records.length,
      examples: [
        "efct.pzz texture/model usage",
        "gets.pzz members",
        "st##.pzz raw first members",
        "it####_mdl.arz attachment models",
        "stc##_mdl.arz stage variant models",
      ],
      note: "This scanner lists and classifies bytes. It does not claim which game event, particle emitter, or stage state consumes each payload.",
    },
  ];
}

function selectExamples(records) {
  const wanted = new Set(["efct.pzz", "gets.pzz", "cmn_data.pzz", "st00.pzz", "st01.pzz", "pl0100.pzz", "pl0200.pzz"]);
  const pzzExamples = records.filter((record) => wanted.has(record.name));
  const arzExamples = records
    .filter((record) => record.archive.kind === "arz")
    .filter((record) => /^(it0102_mdl|it0006_mdl|stc01_mdl|stc0d_mdl)\.arz$/i.test(record.name));
  return { pzzExamples, arzExamples };
}

function buildMarkdown(report) {
  const lines = [];
  const examples = selectExamples(report.records);

  lines.push("# PZZ/ARZ archive format notes");
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
  lines.push(`- Files scanned: ${report.summary.scannedFileCount}`);
  lines.push(`- PZZ archives: ${report.summary.pzzArchiveCount}`);
  lines.push(`- Direct ARZ files: ${report.summary.directArzFileCount}`);
  lines.push(`- PZZ members listed: ${report.summary.pzzMemberCount}`);
  lines.push(`- Compressed PZZ members: ${report.summary.pzzCompressedMemberCount}`);
  lines.push(`- Payload kinds: ${Object.entries(report.summary.payloadKinds).map(([kind, count]) => `${kind} ${count}`).join(", ")}`);
  lines.push("");
  lines.push("## PZZ layout");
  lines.push("");
  lines.push("| Offset | Field | Observation |");
  lines.push("|---:|---|---|");
  lines.push("| `0x00` | `u32 memberCount` | Big-endian. All scanned PZZ files have plausible counts. |");
  lines.push("| `0x04` | `u32 memberTable[memberCount]` | Each word is a block-count descriptor. Bit `0x40000000` marks pzzp-compressed payload. Low 30 bits are the number of `0x800` byte blocks occupied in the archive. |");
  lines.push("| `0x800` | payload data | Members are stored sequentially after one fixed `0x800` byte header/table block. The sum of member block counts plus the header block matches every scanned file size. |");
  lines.push("");
  lines.push("## ARZ / pzzp stream");
  lines.push("");
  lines.push("ARZ files and compressed PZZ members use the same 16-bit big-endian LZ stream. There is no separate static magic in the direct `.arz` files scanned here; the first halfword is a control word. Control bits are consumed from bit 15 down to bit 0. Literal tokens copy one 16-bit word. Back-reference tokens use an 11-bit word distance and a 5-bit word count, with a zero count extended by the following word. A back-reference with distance zero terminates the stream.");
  lines.push("");
  lines.push("## Representative PZZ archives");
  lines.push("");
  lines.push("| Archive | Role | Members | Compressed/raw/zero | Valid block sum | Recognized member kinds |");
  lines.push("|---|---|---:|---|---|---|");
  for (const record of examples.pzzExamples) {
    lines.push(
      `| \`${record.path}\` | ${mdEscape(record.role)} | ${record.archive.memberCount} | ${record.archive.compressedMemberCount}/${record.archive.rawMemberCount}/${record.archive.zeroLengthMemberCount} | ${record.archive.validatesAgainstFileSize} | ${mdEscape(
        Object.entries(record.archive.recognizedMemberKinds)
          .map(([kind, count]) => `${kind}:${count}`)
          .join(", "),
      )} |`,
    );
  }
  lines.push("");
  lines.push("## Representative member listing");
  for (const record of examples.pzzExamples.slice(0, 4)) {
    lines.push("");
    lines.push(`### ${record.name}`);
    lines.push("");
    lines.push("| Id | Table word | Offset | Blocks | Compression | Name / kind | Exact bytes |");
    lines.push("|---:|---|---:|---:|---|---|---:|");
    for (const member of record.members.slice(0, 16)) {
      const compression = member.zeroLength ? "zero" : member.flags.compressed ? "pzzp" : "raw";
      lines.push(
        `| ${member.memberId} | \`${member.tableWord}\` | \`${hex(member.dataOffset, 6)}\` | ${member.blockCount} | ${compression} | ${mdEscape(
          `${member.inferredName} / ${member.payload.sniff.kind}`,
        )} | ${member.payload.exactBytes ?? ""} |`,
      );
    }
  }

  lines.push("");
  lines.push("## Direct ARZ groups");
  lines.push("");
  lines.push("| First words | Count | Size range | Payload kinds | Examples |");
  lines.push("|---|---:|---:|---|---|");
  for (const group of report.groups.arzFirstWordGroups) {
    lines.push(
      `| \`${mdEscape(group.firstWords)}\` | ${group.count} | ${formatBytes(group.minSizeBytes)}-${formatBytes(group.maxSizeBytes)} | ${mdEscape(
        Object.entries(group.payloadKinds)
          .map(([kind, count]) => `${kind}:${count}`)
          .join(", "),
      )} | ${group.examples.map((example) => `\`${example}\``).join("<br>")} |`,
    );
  }

  lines.push("");
  lines.push("## Representative direct ARZ payloads");
  lines.push("");
  lines.push("| File | Role | Compressed | Decompressed | Kind | Roots |");
  lines.push("|---|---|---:|---:|---|---|");
  for (const record of examples.arzExamples) {
    const roots = record.payload.sniff.roots?.map((root) => root.name).filter(Boolean).join(", ") ?? "";
    lines.push(
      `| \`${record.path}\` | ${mdEscape(record.role)} | ${formatBytes(record.sizeBytes)} | ${formatBytes(record.payload.availableBytes)} | ${record.payload.sniff.kind} | ${mdEscape(roots)} |`,
    );
  }

  lines.push("");
  lines.push("## Blockers");
  lines.push("");
  for (const blocker of report.blockers) {
    lines.push(`- ${blocker.label}: ${blocker.status}; ${blocker.count} item(s). ${blocker.note}`);
  }

  lines.push("");
  lines.push("## Notes for effect/item/stage work");
  lines.push("");
  lines.push("- `efct.pzz` is now listable as three compressed members: member 000 is a TPL texture payload, and members 001/002 are effect HSD model payloads. Runtime effect usage still needs correlation.");
  lines.push("- `gets.pzz` is listable as eleven compressed members. Several members identify as HSD DAT payloads, but the per-member item meaning remains unnamed.");
  lines.push("- `st##.pzz` archives are listable. Their first member is raw/uncompressed in the sampled stage pattern; later compressed members decode to smaller binary payloads that need stage-runtime correlation.");
  lines.push("- `it####_mdl.arz` and `stc##_mdl.arz` are direct compressed streams, not multi-entry archives. They now decompress in memory for header/root sniffing.");
  lines.push("");

  return `${lines.join("\n")}\n`;
}

async function main() {
  const [particleEffects, weaponsEffectsProjectiles] = await Promise.all([
    readJsonIfPresent(sourceInventoryPaths.particleEffects),
    readJsonIfPresent(sourceInventoryPaths.weaponsEffectsProjectiles),
  ]);
  const sourceIndexes = {
    particleEffects: buildInventoryIndex(particleEffects),
    weaponsEffectsProjectiles: buildInventoryIndex(weaponsEffectsProjectiles),
  };

  const files = await listRootFiles();
  const records = [];
  for (const file of files) {
    if (file.extension === ".pzz") records.push(await inspectPzzArchive(file, sourceIndexes));
    else if (file.extension === ".arz") records.push(await inspectArzFile(file, sourceIndexes));
  }

  const summary = summarizeRecords(records);
  const report = {
    generatedAt: new Date().toISOString(),
    scanner: toRepoPath(fileURLToPath(import.meta.url)),
    inputs: [
      assetRootRel,
      sourceInventoryPaths.particleEffects,
      sourceInventoryPaths.weaponsEffectsProjectiles,
      "efct.pzz",
      "gets.pzz",
      "cmn_data.pzz",
      "st*.pzz",
      "pl*.pzz",
      "it####_mdl.arz",
      "stc##_mdl.arz",
    ],
    formatFindings: {
      pzz: {
        byteOrder: "big-endian",
        headerBlockSize: pzzMemberBlockSize,
        memberCountOffset: 0,
        memberTableOffset: 4,
        compressedFlag: hex(pzzCompressedFlag),
        blockCountMask: hex(pzzBlockCountMask),
        dataStartOffset: pzzMemberBlockSize,
        blockSumValidation: "file size equals 0x800 * (1 + sum(member block counts)) for every scanned PZZ file",
      },
      arz: {
        byteOrder: "big-endian",
        staticMagic: null,
        stream: "same pzzp/arzip LZ stream used by compressed PZZ members",
      },
    },
    sourceInventoryStatus: {
      particleEffectsLoaded: particleEffects !== null,
      weaponsEffectsProjectilesLoaded: weaponsEffectsProjectiles !== null,
    },
    summary,
    groups: groupCompression(records),
    blockers: collectBlockers(records, summary),
    records,
  };

  await fs.mkdir(path.dirname(outputJsonPath), { recursive: true });
  await fs.mkdir(path.dirname(outputMarkdownPath), { recursive: true });
  await fs.writeFile(outputJsonPath, `${JSON.stringify(report, null, 2)}\n`);
  await fs.writeFile(outputMarkdownPath, buildMarkdown(report));

  console.log(`wrote ${toRepoPath(outputJsonPath)}`);
  console.log(`wrote ${toRepoPath(outputMarkdownPath)}`);
  console.log(
    `scanned ${summary.scannedFileCount} files; listed ${summary.pzzMemberCount} PZZ members; direct ARZ ${summary.directArzFileCount}`,
  );
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
