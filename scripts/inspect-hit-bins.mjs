#!/usr/bin/env node
import { createHash } from "node:crypto";
import { mkdir, readdir, readFile, stat, writeFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const afsRoot = "user-data/GG4E/afs_data/root";
const outputJson = "research/asset-inventory/hit-bin-inventory.json";
const stageInventoryPath = "research/asset-inventory/stage-geometry-collision.json";
const effectsInventoryPath = "research/asset-inventory/weapons-effects-projectiles.json";
const borgDataPath = "packages/assets/data/borgs.json";

const STAGE_RECORD_SIZE = 0x38;
// VERIFIED 0x50 from the DOL spawner indexing (record = base + idx*0x50):
// chunk_0013.c zz_008ab30_ @0x8008ab30:1297, zz_008ac80_ @0x8008ac80:1349,
// zz_008ae60_ @0x8008ae60:1439. The old 0xF4 model was a size coincidence
// (32*0xF4 + 0x20 == 0x20 + 32*0x50 + 0x80 + 64*0x50 == 0x1EA0).
const HITBOX_RECORD_SIZE = 0x50;

function abs(relPath) {
  return path.resolve(repoRoot, relPath);
}

function rel(filePath) {
  return path.relative(repoRoot, path.resolve(filePath)).replaceAll(path.sep, "/");
}

function hex(value, width = 8) {
  if (value == null) return null;
  return `0x${Number(value >>> 0).toString(16).padStart(width, "0")}`;
}

function round(value) {
  return Number.isFinite(value) ? Number(value.toFixed(3)) : value;
}

function sha1(buffer) {
  return createHash("sha1").update(buffer).digest("hex");
}

function readAscii(buffer, start, end) {
  return buffer.toString("ascii", start, end).replace(/[^\x20-\x7e]/g, ".");
}

async function readJsonIfExists(relPath) {
  try {
    return JSON.parse(await readFile(abs(relPath), "utf8"));
  } catch {
    return null;
  }
}

async function fileInfo(relPath) {
  try {
    const info = await stat(abs(relPath));
    return { path: relPath, exists: true, bytes: info.size };
  } catch {
    return { path: relPath, exists: false, bytes: null };
  }
}

function emptyBounds3() {
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

function finishBounds3(bounds) {
  if (!Number.isFinite(bounds.min.x)) return null;
  return {
    min: { x: round(bounds.min.x), y: round(bounds.min.y), z: round(bounds.min.z) },
    max: { x: round(bounds.max.x), y: round(bounds.max.y), z: round(bounds.max.z) },
    extent: {
      x: round(bounds.max.x - bounds.min.x),
      y: round(bounds.max.y - bounds.min.y),
      z: round(bounds.max.z - bounds.min.z),
    },
  };
}

function byteHistogram(bytes) {
  const counts = new Map();
  for (const byte of bytes) counts.set(byte, (counts.get(byte) ?? 0) + 1);
  return [...counts.entries()]
    .sort((a, b) => b[1] - a[1] || a[0] - b[0])
    .slice(0, 12)
    .map(([value, count]) => ({ value, hex: hex(value, 2), count }));
}

function activeRemapEntries(buffer, start, byteLength) {
  const entries = [];
  for (let i = 0; i < byteLength && start + i < buffer.length; i += 1) {
    const value = buffer[start + i];
    if (value !== 0xff) entries.push({ index: i, value, hex: hex(value, 2) });
  }
  return entries;
}

function nonZeroSlice(buffer, start, byteLength) {
  const end = Math.min(buffer.length, start + byteLength);
  for (let i = start; i < end; i += 1) {
    if (buffer[i] !== 0) return true;
  }
  return false;
}

function parseStageName(name) {
  const match = /^hit([0-9a-f]{2})([0-2])\.bin$/i.exec(name);
  if (!match) return null;
  const layer = Number(match[2]);
  const layerLabels = [
    "layer-0-primary-stage-collision-candidate",
    "layer-1-secondary-stage-collision-candidate",
    "layer-2-sparse-or-special-stage-collision-candidate",
  ];
  return {
    stageCode: match[1].toLowerCase(),
    stageId: `st${match[1].toLowerCase()}`,
    layer,
    layerLabel: layerLabels[layer] ?? "unknown-stage-collision-layer",
  };
}

function parseStageHit(buffer, relPath) {
  const name = path.basename(relPath);
  const stage = parseStageName(name);
  const magic = readAscii(buffer, 0, 4);
  const declaredBytes = buffer.length >= 8 ? buffer.readUInt32BE(4) : null;

  if (buffer.length < 0x28 || magic !== "STIH") {
    return {
      path: relPath,
      fileName: name,
      category: "stage-spatial-collision",
      valid: false,
      reason: "missing STIH header",
      bytes: buffer.length,
      sha1: sha1(buffer),
    };
  }

  const cellSizeX = buffer.readUInt32BE(0x08);
  const cellSizeZ = buffer.readUInt32BE(0x0c);
  const gridX = buffer.readUInt32BE(0x10);
  const gridZ = buffer.readUInt32BE(0x14);
  const originX = buffer.readInt32BE(0x18);
  const originZ = buffer.readInt32BE(0x1c);
  const unknown20 = buffer.readUInt32BE(0x20);
  const recordSentinelOffset = buffer.readUInt32BE(0x24);
  const offsetTableStart = 0x28;
  const cellCount = gridX * gridZ;
  const nominalCellListStart = offsetTableStart + cellCount * 4;
  const observedCellListStart = buffer.readUInt32BE(offsetTableStart);
  const recordStart = recordSentinelOffset + 8;
  const recordBytes = buffer.length - recordStart;
  const recordCount = Number.isInteger(recordBytes / STAGE_RECORD_SIZE)
    ? recordBytes / STAGE_RECORD_SIZE
    : Math.floor(Math.max(recordBytes, 0) / STAGE_RECORD_SIZE);
  const recordSectionHasWholeRecords = recordBytes >= 0 && recordBytes % STAGE_RECORD_SIZE === 0;
  const tableFits = nominalCellListStart <= buffer.length && recordSentinelOffset <= buffer.length;
  const listFits = nominalCellListStart <= recordSentinelOffset;
  const sentinelWords =
    recordSentinelOffset + 8 <= buffer.length
      ? [buffer.readUInt32BE(recordSentinelOffset), buffer.readUInt32BE(recordSentinelOffset + 4)].map((v) => hex(v))
      : [];

  const cellOffsets = [];
  if (tableFits) {
    for (let i = 0; i < cellCount; i += 1) {
      cellOffsets.push(buffer.readUInt32BE(offsetTableStart + i * 4));
    }
  }

  const cellOffsetAnomalies = [];
  for (let i = 0; i < cellOffsets.length; i += 1) {
    const offset = cellOffsets[i];
    if (offset < nominalCellListStart || offset >= recordSentinelOffset || offset % 4 !== 0) {
      cellOffsetAnomalies.push({ cellIndex: i, offset: hex(offset) });
      if (cellOffsetAnomalies.length >= 8) break;
    }
  }

  let offsetTableMonotonic = true;
  for (let i = 1; i < cellOffsets.length; i += 1) {
    if (cellOffsets[i] < cellOffsets[i - 1]) {
      offsetTableMonotonic = false;
      break;
    }
  }

  let listWordCount = 0;
  let listSentinelCount = 0;
  let recordRefCount = 0;
  let invalidRecordRefCount = 0;
  let anomalousSpanInvalidWordCount = 0;
  let nonEmptyCellCount = 0;
  let maxRefsInCell = 0;
  let maxRefsCellIndex = null;
  const invalidRecordRefSamples = [];

  if (listFits) {
    for (let cellIndex = 0; cellIndex < cellOffsets.length; cellIndex += 1) {
      const listOffset = cellOffsets[cellIndex];
      const nextOffset = cellIndex + 1 < cellOffsets.length ? cellOffsets[cellIndex + 1] : recordSentinelOffset;
      const anomalousSpan =
        listOffset < nominalCellListStart ||
        listOffset >= recordSentinelOffset ||
        nextOffset < listOffset ||
        nextOffset > recordSentinelOffset ||
        listOffset % 4 !== 0 ||
        nextOffset % 4 !== 0;
      if (nextOffset < listOffset || nextOffset > recordSentinelOffset) continue;

      let refs = 0;
      for (let offset = listOffset; offset + 4 <= nextOffset; offset += 4) {
        listWordCount += 1;
        const value = buffer.readUInt32BE(offset);
        if (value === 0xffffffff) {
          listSentinelCount += 1;
          continue;
        }
        refs += 1;
        if (value % STAGE_RECORD_SIZE !== 0 || value < 0 || value >= recordBytes) {
          if (anomalousSpan) {
            anomalousSpanInvalidWordCount += 1;
          } else {
            invalidRecordRefCount += 1;
            if (invalidRecordRefSamples.length < 8) invalidRecordRefSamples.push({ offset: hex(offset), value: hex(value) });
          }
        } else if (!anomalousSpan) {
          recordRefCount += 1;
        }
      }
      if (!anomalousSpan && refs > 0) nonEmptyCellCount += 1;
      if (!anomalousSpan && refs > maxRefsInCell) {
        maxRefsInCell = refs;
        maxRefsCellIndex = cellIndex;
      }
    }
  }

  const bounds = emptyBounds3();
  let markerOkCount = 0;
  let markerOtherCount = 0;
  let normalLengthMin = Infinity;
  let normalLengthMax = -Infinity;
  let planeDMin = Infinity;
  let planeDMax = -Infinity;
  const sampleRecords = [];

  for (let index = 0; index < recordCount; index += 1) {
    const offset = recordStart + index * STAGE_RECORD_SIZE;
    if (offset + STAGE_RECORD_SIZE > buffer.length) break;
    const marker = buffer.readUInt32BE(offset);
    if (marker === 0xcccccccc) markerOkCount += 1;
    else markerOtherCount += 1;

    const v0 = {
      x: buffer.readFloatBE(offset + 0x04),
      y: buffer.readFloatBE(offset + 0x08),
      z: buffer.readFloatBE(offset + 0x0c),
    };
    const v1 = {
      x: buffer.readFloatBE(offset + 0x10),
      y: buffer.readFloatBE(offset + 0x14),
      z: buffer.readFloatBE(offset + 0x18),
    };
    const v2 = {
      x: buffer.readFloatBE(offset + 0x1c),
      y: buffer.readFloatBE(offset + 0x20),
      z: buffer.readFloatBE(offset + 0x24),
    };
    const normal = {
      x: buffer.readFloatBE(offset + 0x28),
      y: buffer.readFloatBE(offset + 0x2c),
      z: buffer.readFloatBE(offset + 0x30),
    };
    const planeD = buffer.readFloatBE(offset + 0x34);
    includePoint(bounds, v0.x, v0.y, v0.z);
    includePoint(bounds, v1.x, v1.y, v1.z);
    includePoint(bounds, v2.x, v2.y, v2.z);

    const normalLength = Math.hypot(normal.x, normal.y, normal.z);
    normalLengthMin = Math.min(normalLengthMin, normalLength);
    normalLengthMax = Math.max(normalLengthMax, normalLength);
    planeDMin = Math.min(planeDMin, planeD);
    planeDMax = Math.max(planeDMax, planeD);

    if (sampleRecords.length < 3) {
      sampleRecords.push({
        index,
        offset: hex(offset),
        marker: hex(marker),
        vertices: [
          { x: round(v0.x), y: round(v0.y), z: round(v0.z) },
          { x: round(v1.x), y: round(v1.y), z: round(v1.z) },
          { x: round(v2.x), y: round(v2.y), z: round(v2.z) },
        ],
        normal: { x: round(normal.x), y: round(normal.y), z: round(normal.z) },
        planeD: round(planeD),
      });
    }
  }

  return {
    path: relPath,
    fileName: name,
    category: "stage-spatial-collision",
    stage,
    valid:
      declaredBytes === buffer.length &&
      tableFits &&
      listFits &&
      recordSectionHasWholeRecords &&
      markerOtherCount === 0 &&
      invalidRecordRefCount === 0,
    bytes: buffer.length,
    sha1: sha1(buffer),
    magic,
    header: {
      declaredBytes,
      cellSize: { x: cellSizeX, z: cellSizeZ },
      gridCells: { x: gridX, z: gridZ, total: cellCount },
      origin: { x: originX, z: originZ },
      bounds2d: {
        minX: originX,
        minZ: originZ,
        maxX: originX + cellSizeX * gridX,
        maxZ: originZ + cellSizeZ * gridZ,
      },
      unknown20: hex(unknown20),
      recordSentinelOffset: hex(recordSentinelOffset),
    },
    sections: {
      offsetTable: {
        offset: hex(offsetTableStart),
        bytes: cellCount * 4,
        entries: cellOffsets.length,
        monotonic: offsetTableMonotonic,
        nominalEnd: hex(nominalCellListStart),
        observedFirstCellListOffset: hex(observedCellListStart),
        anomalies: cellOffsetAnomalies,
      },
      cellLists: {
        nominalOffset: hex(nominalCellListStart),
        observedOffset: hex(observedCellListStart),
        endOffset: hex(recordSentinelOffset),
        words: listWordCount,
        sentinelCount: listSentinelCount,
        recordRefCount,
        invalidRecordRefCount,
        anomalousSpanInvalidWordCount,
        invalidRecordRefSamples,
        nonEmptyCellCount,
        maxRefsInCell,
        maxRefsCellIndex,
        note: "Offsets define per-cell spans; non-sentinel span values are record-relative byte offsets and observed valid values are multiples of 0x38.",
      },
      records: {
        sentinelWords,
        offset: hex(recordStart),
        bytes: recordBytes,
        recordSize: STAGE_RECORD_SIZE,
        recordCount,
        wholeRecords: recordSectionHasWholeRecords,
        markerCounts: { cccccccc: markerOkCount, other: markerOtherCount },
        bounds3d: finishBounds3(bounds),
        normalLengthRange: {
          min: Number.isFinite(normalLengthMin) ? round(normalLengthMin) : null,
          max: Number.isFinite(normalLengthMax) ? round(normalLengthMax) : null,
        },
        planeDRange: {
          min: Number.isFinite(planeDMin) ? round(planeDMin) : null,
          max: Number.isFinite(planeDMax) ? round(planeDMax) : null,
        },
        sampleRecords,
      },
    },
    unknowns: [
      "The 0x20 header word is always 0x20 in the scanned STIH files, but its semantic name is not proven.",
      "The first two cell-offset entries point before the nominal cell-list start in every scanned file; they look like unused edge/padding cells.",
      "Layer suffix meanings (0/1/2) are inferred only from density and naming, not from game code.",
    ],
  };
}

function parseActorHitSectionStats(buffer, sectionName, remapOffset, remapBytes, remapSlotStride, recordOffset, recordCount) {
  const remapEntries = [];
  for (let slot = 0; slot < remapBytes / remapSlotStride; slot += 1) {
    for (let position = 0; position < remapSlotStride; position += 1) {
      const value = buffer.readUInt8(remapOffset + slot * remapSlotStride + position);
      if (value === 0xff) break; // 0xFF terminates a slot's list (chunk_0013.c:1439)
      remapEntries.push({ slot, position, value });
    }
  }
  const remapValues = remapEntries.map((entry) => entry.value);

  const sampleRecords = [];
  let nonZeroRecordCount = 0;
  let maxNonZeroRecordIndex = null;
  let persistentCount = 0;
  const damageIndexCounts = new Map();
  for (let index = 0; index < recordCount; index += 1) {
    const offset = recordOffset + index * HITBOX_RECORD_SIZE;
    const nonZero = nonZeroSlice(buffer, offset, HITBOX_RECORD_SIZE);
    if (!nonZero) continue;
    nonZeroRecordCount += 1;
    maxNonZeroRecordIndex = index;
    const activeEnd = buffer.readInt16BE(offset + 0x08);
    if (activeEnd === -1) persistentCount += 1;
    const damageRecordIndex = buffer.readUInt16BE(offset + 0x04);
    damageIndexCounts.set(damageRecordIndex, (damageIndexCounts.get(damageRecordIndex) ?? 0) + 1);
    if (sampleRecords.length < 8) {
      const bone = buffer.readUInt8(offset + 0x01);
      sampleRecords.push({
        index,
        offset: hex(offset),
        shapeKind: buffer.readUInt8(offset + 0x00),
        boneIndex: bone & 0x7f,
        attachToRoot: (bone & 0x80) !== 0,
        collisionFlags: hex(buffer.readUInt16BE(offset + 0x02)),
        damageRecordIndex,
        activeStart: buffer.readInt16BE(offset + 0x06),
        activeEnd,
        localOffset: [0x0c, 0x10, 0x14].map((o) => round(buffer.readFloatBE(offset + o))),
        halfExtent: [0x18, 0x1c, 0x20].map((o) => round(buffer.readFloatBE(offset + o))),
        radius: round(buffer.readFloatBE(offset + 0x24)),
      });
    }
  }

  return {
    name: sectionName,
    layout: {
      remapOffset: hex(remapOffset),
      remapBytes,
      remapSlotStride,
      recordOffset: hex(recordOffset),
      recordSize: HITBOX_RECORD_SIZE,
      recordCount,
    },
    remap: {
      activeCount: remapEntries.length,
      uniqueActiveCount: new Set(remapValues).size,
      maxValue: remapValues.length > 0 ? Math.max(...remapValues) : null,
      activeValueHistogram: byteHistogram(remapValues),
      sampleEntries: remapEntries.slice(0, 32),
    },
    records: {
      nonZeroRecordCount,
      zeroRecordCount: recordCount - nonZeroRecordCount,
      maxNonZeroRecordIndex,
      persistentRecordCount: persistentCount,
      damageRecordIndexHistogram: [...damageIndexCounts.entries()]
        .sort((a, b) => b[1] - a[1] || a[0] - b[0])
        .slice(0, 12)
        .map(([value, count]) => ({ value, count })),
      sampleRecords,
    },
  };
}

function parseActorHit(buffer, relPath, borgMap) {
  const name = path.basename(relPath);
  const isPlayer = /^pl[0-9a-f]{4}hit\.bin$/i.test(name);
  const lower = name.toLowerCase();
  const borgId = isPlayer ? name.slice(0, 6).toLowerCase() : null;
  const base = {
    path: relPath,
    fileName: name,
    bytes: buffer.length,
    sha1: sha1(buffer),
    linkedBorgId: borgId,
    linkedBorgName: borgId ? borgMap.get(borgId)?.name ?? null : null,
  };

  if (lower === "comhit2.bin") {
    // EXPLICITLY OPEN: 0x3D40 fits neither the refuted 0xF4 model nor the proven
    // 0x50 two-section model cleanly. Do not guess a stride.
    return {
      ...base,
      category: "secondary-common-hit-table-UNVERIFIED",
      valid: false,
      sections: [],
      unknowns: [
        "comhit2.bin (0x3D40) layout is unresolved: no DOL reader indexing it has been identified yet.",
      ],
    };
  }

  if (lower === "comhit.bin") {
    const valid = buffer.length === 0x5400;
    return {
      ...base,
      category: "global-common-hit-table",
      valid,
      sections: valid
        ? [parseActorHitSectionStats(buffer, "commonHitboxes", 0x000, 0x400, 4, 0x400, 256)]
        : [],
      unknowns: [
        "comhit remap slot -> gameplay event mapping (which slot each common effect uses) is consumer-side (zz_008ae60_ arg), not in the file.",
      ],
    };
  }

  const valid = buffer.length === 0x1ea0;
  return {
    ...base,
    category: "player-borg-hit-table",
    valid,
    sections: valid
      ? [
          parseActorHitSectionStats(buffer, "bodyHurtboxes", 0x000, 0x20, 1, 0x020, 32),
          parseActorHitSectionStats(buffer, "attackHitboxes", 0xa20, 0x80, 4, 0xaa0, 64),
        ]
      : [],
    unknowns: [
      "Record bytes +0x28..+0x4F are zero in sampled borg records; other shape kinds may use them.",
      "Attack remap slot index -> move/animation mapping is consumer-side (zz_008ac80_ kind arg).",
    ],
  };
}

function extractCrossReferences(stageInventory, effectsInventory) {
  return {
    stageGeometryCollision: stageInventory
      ? {
          path: stageInventoryPath,
          generatedBy: stageInventory.generatedBy ?? null,
          stageId: stageInventory.stageId ?? null,
          priorHitBinCount: stageInventory.collision?.hitBins?.length ?? null,
          priorInferredArenaBounds: stageInventory.collision?.inferredArenaBounds ?? null,
          note: "Used as context for st00 STIH header/bounds; this script scans all stage hit bins directly.",
        }
      : { path: stageInventoryPath, available: false },
    weaponsEffectsProjectiles: effectsInventory
      ? {
          path: effectsInventoryPath,
          scanner: effectsInventory.scanner ?? null,
          hitDataNeed: (effectsInventory.needsExtractionConversion ?? []).find((need) =>
            String(need.need).includes("hit/data BIN schema parser"),
          ) ?? null,
          note: "Used as context that hit/comhit/pl####hit binaries are weapon, impact, and collision parser leads.",
        }
      : { path: effectsInventoryPath, available: false },
  };
}

async function main() {
  const [stageInventory, effectsInventory, borgData] = await Promise.all([
    readJsonIfExists(stageInventoryPath),
    readJsonIfExists(effectsInventoryPath),
    readJsonIfExists(borgDataPath),
  ]);
  const borgMap = new Map((borgData?.borgs ?? []).map((borg) => [String(borg.id).toLowerCase(), borg]));

  const rootAbs = abs(afsRoot);
  const names = (await readdir(rootAbs)).sort((a, b) => a.localeCompare(b));
  const hitNames = names.filter((name) => /^hit[0-9a-f]{3}\.bin$/i.test(name));
  const commonNames = names.filter((name) => /^comhit2?\.bin$/i.test(name));
  const playerNames = names.filter((name) => /^pl[0-9a-f]{4}hit\.bin$/i.test(name));

  const stage = [];
  for (const name of hitNames) {
    const file = path.join(rootAbs, name);
    stage.push(parseStageHit(await readFile(file), rel(file)));
  }

  const common = [];
  for (const name of commonNames) {
    const file = path.join(rootAbs, name);
    common.push(parseActorHit(await readFile(file), rel(file), borgMap));
  }

  const player = [];
  for (const name of playerNames) {
    const file = path.join(rootAbs, name);
    player.push(parseActorHit(await readFile(file), rel(file), borgMap));
  }

  const stageByLayer = {};
  for (const file of stage) {
    const key = String(file.stage?.layer ?? "unknown");
    stageByLayer[key] ??= { count: 0, recordCount: 0, recordRefCount: 0 };
    stageByLayer[key].count += 1;
    stageByLayer[key].recordCount += file.sections.records.recordCount;
    stageByLayer[key].recordRefCount += file.sections.cellLists.recordRefCount;
  }

  const playerActiveCounts = {};
  for (const file of player) {
    const total = (file.sections ?? []).reduce((sum, section) => sum + section.remap.activeCount, 0);
    const key = String(total);
    playerActiveCounts[key] = (playerActiveCounts[key] ?? 0) + 1;
  }

  const inventory = {
    generatedBy: "scripts/inspect-hit-bins.mjs",
    generatedAt: new Date().toISOString(),
    scope: "Stage STIH collision grids plus common and per-Borg hit table binaries.",
    sources: {
      afsRoot: await fileInfo(afsRoot),
      stageGeometryCollision: await fileInfo(stageInventoryPath),
      weaponsEffectsProjectiles: await fileInfo(effectsInventoryPath),
      borgData: await fileInfo(borgDataPath),
    },
    crossReferences: extractCrossReferences(stageInventory, effectsInventory),
    summary: {
      fileCount: stage.length + common.length + player.length,
      stageHitBinCount: stage.length,
      commonHitBinCount: common.length,
      playerHitBinCount: player.length,
      stageRecordSize: STAGE_RECORD_SIZE,
      actorHitRecordSize: HITBOX_RECORD_SIZE,
      stageByLayer,
      playerActiveRemapCountHistogram: playerActiveCounts,
      observedFormats: [
        "STIH stage spatial collision grid: big-endian header, 42x42 cells, 0x38-byte triangle plane records.",
        "pl####hit actor hit table (0x1EA0, VERIFIED vs DOL spawners chunk_0013.c:1297/1349): [0x000 32 x u8 remap A][0x020 32 x 0x50 body hurtbox records][0xA20 32 x u8[4] remap B slots, 0xFF-terminated][0xAA0 64 x 0x50 attack/child hitbox records].",
        "comhit global table (0x5400, VERIFIED vs zz_008ae60_ chunk_0013.c:1439): [0x000 256 x u8[4] remap slots][0x400 256 x 0x50 records]; no tail padding.",
        "comhit2 (0x3D40): EXPLICITLY OPEN — fits neither the refuted 0xF4 model nor the 0x50 two-section model; no DOL reader identified.",
      ],
    },
    formatFindings: {
      endian: "big-endian",
      stageStihHeader: [
        { offset: "0x00", type: "char[4]", name: "magic", observed: "STIH" },
        { offset: "0x04", type: "u32", name: "declaredBytes", observed: "equals file size" },
        { offset: "0x08", type: "u32", name: "cellSizeX", observed: 500 },
        { offset: "0x0c", type: "u32", name: "cellSizeZ", observed: 500 },
        { offset: "0x10", type: "u32", name: "gridCellsX", observed: 42 },
        { offset: "0x14", type: "u32", name: "gridCellsZ", observed: 42 },
        { offset: "0x18", type: "s32", name: "originX", observed: -11000 },
        { offset: "0x1c", type: "s32", name: "originZ", observed: -11000 },
        { offset: "0x20", type: "u32", name: "unknown20", observed: "0x00000020" },
        { offset: "0x24", type: "u32", name: "recordSentinelOffset", observed: "followed by two 0xFFFFFFFF words; records start at +8" },
      ],
      stageRecord38: [
        { offset: "0x00", type: "u32", name: "marker", observed: "0xCCCCCCCC" },
        { offset: "0x04", type: "f32[3]", name: "vertex0" },
        { offset: "0x10", type: "f32[3]", name: "vertex1" },
        { offset: "0x1c", type: "f32[3]", name: "vertex2" },
        { offset: "0x28", type: "f32[3]", name: "normal" },
        { offset: "0x34", type: "f32", name: "planeD_or_distance_candidate" },
      ],
      actorHitRecord50: {
        status: "VERIFIED against DOL readers (chunk_0013.c FUN_8008a65c:1121, zz_008ab30_:1297, zz_008ac80_:1349, zz_008ae60_:1439; chunk_0004.c FUN_8003c8b4:6481)",
        fields: [
          { offset: "0x00", type: "u8", name: "shapeKind", note: "dispatch PTR_FUN_802da740/802da758" },
          { offset: "0x01", type: "u8", name: "boneIndex", note: "bit 0x80 = actor root matrix (+0x1aa4), else actor+0x8d4+bone*0x30" },
          { offset: "0x02", type: "u16", name: "collisionFlags", note: "zz_008a2bc_ chunk_0013.c:973; bit 0x40 = attack list gated by i-frames" },
          { offset: "0x04", type: "u16", name: "damageRecordIndex", note: "into the 0x18-stride DOL damage table at actor+0x27c (borg family: 9 records @0x802d46e0)" },
          { offset: "0x06", type: "s16", name: "activeStart", note: "borgs: anim-frame threshold vs actor+0x1cdc" },
          { offset: "0x08", type: "s16", name: "activeEnd", note: "-1 = persistent (body hurtboxes)" },
          { offset: "0x0c", type: "f32[3]", name: "localOffset" },
          { offset: "0x18", type: "f32[3]", name: "halfExtent", note: "capsule endpoints = offset ± this" },
          { offset: "0x24", type: "f32", name: "radius", note: "scaled by actor scale +0xc0" },
        ],
        unknown: ["Bytes +0x28..+0x4F (zero in sampled borg records; other shape kinds may use them)."],
      },
    },
    files: { stage, common, player },
    stillUnknown: [
      "STIH cell offset entries 0 and 1 are anomalous in every file; they may be unused edge cells or table padding.",
      "STIH layer suffixes 0/1/2 are not semantically named by the binaries alone.",
      "comhit2.bin (0x3D40) layout — EXPLICITLY OPEN, no DOL reader identified.",
      "Attack remap slot -> move/animation mapping is consumer-side (spawner args), not in the files.",
    ],
  };

  await mkdir(abs(path.dirname(outputJson)), { recursive: true });
  await writeFile(abs(outputJson), `${JSON.stringify(inventory, null, 2)}\n`);

  console.log(`wrote ${outputJson}`);
  console.log(`stage hit bins: ${stage.length}`);
  console.log(`common hit bins: ${common.length}`);
  console.log(`player hit bins: ${player.length}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
