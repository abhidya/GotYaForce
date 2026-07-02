// hit-bin.ts — parsers for Gotcha Force HIT/STIH binaries.
//
// The stage collision files (`hitSSN.bin`) are STIH grids: a big-endian spatial
// grid plus 0x38-byte triangle records. Layer semantics are not proven yet, so
// this parser exposes conservative structural data and bounds without naming
// gameplay behavior.

export interface StageHitBounds2d {
  minX: number;
  maxX: number;
  minZ: number;
  maxZ: number;
}

export interface StageHitVec3 {
  x: number;
  y: number;
  z: number;
}

export interface StageHitHeader {
  declaredBytes: number;
  cellSize: { x: number; z: number };
  gridCells: { x: number; z: number; total: number };
  origin: { x: number; z: number };
  bounds2d: StageHitBounds2d;
  unknown20: number;
  recordSentinelOffset: number;
}

export interface StageHitRecordSummary {
  offset: number;
  bytes: number;
  recordSize: 0x38;
  recordCount: number;
  wholeRecords: boolean;
}

export interface StageHitCell {
  index: number;
  x: number;
  z: number;
  offset: number;
  nextOffset: number;
  recordIndices: number[];
  anomalous: boolean;
}

export interface StageHitTriangle {
  index: number;
  recordOffset: number;
  marker: number;
  vertices: [StageHitVec3, StageHitVec3, StageHitVec3];
  normal: StageHitVec3;
  planeD: number;
  bounds2d: StageHitBounds2d;
  minY: number;
  maxY: number;
}

export interface StageHitGrid {
  magic: "STIH";
  header: StageHitHeader;
  records: StageHitRecordSummary;
  cells: StageHitCell[];
  triangles: StageHitTriangle[];
}

export type ActorHitTableKind = "player" | "comhit" | "comhit2";

export interface ParseActorHitTableOptions {
  /**
   * Selects one of the three observed actor/common HIT table layouts. If omitted,
   * `fileName` is used to infer `comhit`/`comhit2`; otherwise the player-borg layout
   * (`pl####hit.bin`) is used.
   */
  kind?: ActorHitTableKind;
  fileName?: string;
}

export interface ActorHitTableLayout {
  kind: ActorHitTableKind;
  category: "player-borg-hit-table" | "global-common-hit-table" | "secondary-common-hit-table";
  remapOffset: number;
  remapBytes: number;
  recordOffset: number;
  recordSize: 0xf4;
  expectedRecords: number | null;
}

export interface ActorHitRemapEntry {
  index: number;
  value: number;
}

export interface ActorHitRecord {
  index: number;
  offset: number;
  raw: Uint8Array;
  nonZero: boolean;
  firstWord: number;
  firstBytes: [number, number, number, number];
  word8: number;
  candidateFloats10: number[];
}

export interface ActorHitTable {
  layout: ActorHitTableLayout;
  bytes: number;
  valid: boolean;
  remapEntries: ActorHitRemapEntry[];
  uniqueRemapValues: number[];
  remapHasOutOfRangePlayerSlots: boolean;
  records: ActorHitRecord[];
  trailingBytes: number;
  trailingLooksLikePadding: boolean;
}

const STIH_HEADER_BYTES = 0x28;
const STAGE_RECORD_SIZE = 0x38;
export const ACTOR_HIT_RECORD_SIZE = 0xf4;

export function parseStageHitGrid(input: Uint8Array | ArrayBuffer): StageHitGrid {
  const bytes = asBytes(input);
  if (bytes.byteLength < STIH_HEADER_BYTES) {
    throw new RangeError(`STIH file too small: ${bytes.byteLength} bytes`);
  }
  if (bytes[0] !== 0x53 || bytes[1] !== 0x54 || bytes[2] !== 0x49 || bytes[3] !== 0x48) {
    throw new Error("missing STIH magic");
  }

  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const declaredBytes = view.getUint32(0x04, false);
  if (declaredBytes !== bytes.byteLength) {
    throw new Error(`STIH declared size ${declaredBytes} does not match ${bytes.byteLength}`);
  }

  const cellSizeX = view.getUint32(0x08, false);
  const cellSizeZ = view.getUint32(0x0c, false);
  const gridX = view.getUint32(0x10, false);
  const gridZ = view.getUint32(0x14, false);
  const originX = view.getInt32(0x18, false);
  const originZ = view.getInt32(0x1c, false);
  const unknown20 = view.getUint32(0x20, false);
  const recordSentinelOffset = view.getUint32(0x24, false);
  const cellCount = gridX * gridZ;
  const offsetTableEnd = STIH_HEADER_BYTES + cellCount * 4;
  if (offsetTableEnd > bytes.byteLength) {
    throw new Error("STIH cell offset table extends beyond file");
  }
  if (recordSentinelOffset + 8 > bytes.byteLength || recordSentinelOffset < offsetTableEnd) {
    throw new Error("STIH record sentinel offset is outside the file");
  }

  const recordOffset = recordSentinelOffset + 8;
  const recordBytes = bytes.byteLength - recordOffset;
  const recordCount = Math.floor(recordBytes / STAGE_RECORD_SIZE);
  const cells = parseCells(view, cellCount, gridX, offsetTableEnd, recordSentinelOffset, recordBytes);
  const triangles = parseTriangles(view, recordOffset, recordCount);
  return {
    magic: "STIH",
    header: {
      declaredBytes,
      cellSize: { x: cellSizeX, z: cellSizeZ },
      gridCells: { x: gridX, z: gridZ, total: cellCount },
      origin: { x: originX, z: originZ },
      bounds2d: {
        minX: originX,
        maxX: originX + cellSizeX * gridX,
        minZ: originZ,
        maxZ: originZ + cellSizeZ * gridZ,
      },
      unknown20,
      recordSentinelOffset,
    },
    records: {
      offset: recordOffset,
      bytes: recordBytes,
      recordSize: STAGE_RECORD_SIZE,
      recordCount,
      wholeRecords: recordBytes % STAGE_RECORD_SIZE === 0,
    },
    cells,
    triangles,
  };
}

export function stageBoundsFromHitGrid(grid: StageHitGrid): StageHitBounds2d {
  return { ...grid.header.bounds2d };
}

export function parseActorHitTable(
  input: Uint8Array | ArrayBuffer,
  options: ParseActorHitTableOptions = {},
): ActorHitTable {
  const bytes = asBytes(input);
  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const layout = actorHitLayout(options);
  if (bytes.byteLength < layout.recordOffset) {
    throw new RangeError(`actor HIT table too small for ${layout.category}: ${bytes.byteLength} bytes`);
  }

  const completeRecordCount = Math.floor((bytes.byteLength - layout.recordOffset) / ACTOR_HIT_RECORD_SIZE);
  const recordCount = layout.expectedRecords ?? completeRecordCount;
  if (completeRecordCount < recordCount) {
    throw new Error(
      `actor HIT table has ${completeRecordCount} complete records, expected ${recordCount} for ${layout.category}`,
    );
  }

  const remapEntries = activeActorHitRemapEntries(view, layout.remapOffset, layout.remapBytes, bytes.byteLength);
  const uniqueRemapValues = [...new Set(remapEntries.map((entry) => entry.value))].sort((a, b) => a - b);
  const remapHasOutOfRangePlayerSlots = layout.kind === "player" && uniqueRemapValues.some((value) => value >= 32);
  const records = Array.from({ length: recordCount }, (_, index) =>
    parseActorHitRecord(bytes, view, layout.recordOffset + index * ACTOR_HIT_RECORD_SIZE, index),
  );
  const trailingBytes = bytes.byteLength - layout.recordOffset - recordCount * ACTOR_HIT_RECORD_SIZE;
  const trailingLooksLikePadding =
    trailingBytes >= 0 && bytes.subarray(bytes.byteLength - trailingBytes).every((byte) => byte === 0);

  return {
    layout,
    bytes: bytes.byteLength,
    valid:
      recordCount > 0 &&
      trailingBytes >= 0 &&
      !remapHasOutOfRangePlayerSlots &&
      (layout.kind !== "player" || bytes.byteLength === 0x1ea0),
    remapEntries,
    uniqueRemapValues,
    remapHasOutOfRangePlayerSlots,
    records,
    trailingBytes,
    trailingLooksLikePadding,
  };
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}

function actorHitLayout(options: ParseActorHitTableOptions): ActorHitTableLayout {
  const lower = options.fileName?.toLowerCase() ?? "";
  const kind = options.kind ?? (lower === "comhit.bin" ? "comhit" : lower === "comhit2.bin" ? "comhit2" : "player");
  if (kind === "comhit") {
    return {
      kind,
      category: "global-common-hit-table",
      remapOffset: 0,
      remapBytes: 0x400,
      recordOffset: 0x400,
      recordSize: ACTOR_HIT_RECORD_SIZE,
      expectedRecords: null,
    };
  }
  if (kind === "comhit2") {
    return {
      kind,
      category: "secondary-common-hit-table",
      remapOffset: 0,
      remapBytes: 0x20,
      recordOffset: 0x20,
      recordSize: ACTOR_HIT_RECORD_SIZE,
      expectedRecords: 64,
    };
  }
  return {
    kind,
    category: "player-borg-hit-table",
    remapOffset: 0,
    remapBytes: 0x20,
    recordOffset: 0x20,
    recordSize: ACTOR_HIT_RECORD_SIZE,
    expectedRecords: 32,
  };
}

function activeActorHitRemapEntries(
  view: DataView,
  start: number,
  byteLength: number,
  fileLength: number,
): ActorHitRemapEntry[] {
  const entries: ActorHitRemapEntry[] = [];
  const end = Math.min(fileLength, start + byteLength);
  for (let offset = start; offset < end; offset += 1) {
    const value = view.getUint8(offset);
    if (value !== 0xff) entries.push({ index: offset - start, value });
  }
  return entries;
}

function parseActorHitRecord(bytes: Uint8Array, view: DataView, offset: number, index: number): ActorHitRecord {
  return {
    index,
    offset,
    raw: bytes.slice(offset, offset + ACTOR_HIT_RECORD_SIZE),
    nonZero: bytes.subarray(offset, offset + ACTOR_HIT_RECORD_SIZE).some((byte) => byte !== 0),
    firstWord: view.getUint32(offset, false),
    firstBytes: [
      view.getUint8(offset),
      view.getUint8(offset + 1),
      view.getUint8(offset + 2),
      view.getUint8(offset + 3),
    ],
    word8: view.getUint32(offset + 0x08, false),
    candidateFloats10: Array.from({ length: 8 }, (_, i) => view.getFloat32(offset + 0x10 + i * 4, false)),
  };
}

function parseCells(
  view: DataView,
  cellCount: number,
  gridX: number,
  offsetTableEnd: number,
  recordSentinelOffset: number,
  recordBytes: number,
): StageHitCell[] {
  const offsets = Array.from({ length: cellCount }, (_, i) => view.getUint32(STIH_HEADER_BYTES + i * 4, false));
  return offsets.map((offset, index) => {
    const nextOffset = offsets[index + 1] ?? recordSentinelOffset;
    const anomalous =
      offset < offsetTableEnd ||
      offset > recordSentinelOffset ||
      nextOffset < offset ||
      nextOffset > recordSentinelOffset ||
      offset % 4 !== 0 ||
      nextOffset % 4 !== 0;
    const recordIndices: number[] = [];
    if (!anomalous) {
      for (let cursor = offset; cursor + 4 <= nextOffset; cursor += 4) {
        const value = view.getUint32(cursor, false);
        if (value === 0xffffffff) continue;
        if (value % STAGE_RECORD_SIZE === 0 && value >= 0 && value < recordBytes) {
          recordIndices.push(value / STAGE_RECORD_SIZE);
        }
      }
    }
    return {
      index,
      x: index % gridX,
      z: Math.floor(index / gridX),
      offset,
      nextOffset,
      recordIndices,
      anomalous,
    };
  });
}

function parseTriangles(view: DataView, recordOffset: number, recordCount: number): StageHitTriangle[] {
  return Array.from({ length: recordCount }, (_, index) => {
    const offset = recordOffset + index * STAGE_RECORD_SIZE;
    const vertices = [
      readVec3(view, offset + 0x04),
      readVec3(view, offset + 0x10),
      readVec3(view, offset + 0x1c),
    ] as [StageHitVec3, StageHitVec3, StageHitVec3];
    return {
      index,
      recordOffset: offset,
      marker: view.getUint32(offset, false),
      vertices,
      normal: readVec3(view, offset + 0x28),
      planeD: view.getFloat32(offset + 0x34, false),
      bounds2d: triangleBounds2d(vertices),
      minY: Math.min(...vertices.map((v) => v.y)),
      maxY: Math.max(...vertices.map((v) => v.y)),
    };
  });
}

function readVec3(view: DataView, offset: number): StageHitVec3 {
  return {
    x: view.getFloat32(offset, false),
    y: view.getFloat32(offset + 4, false),
    z: view.getFloat32(offset + 8, false),
  };
}

function triangleBounds2d(vertices: [StageHitVec3, StageHitVec3, StageHitVec3]): StageHitBounds2d {
  const xs = vertices.map((v) => v.x);
  const zs = vertices.map((v) => v.z);
  return {
    minX: Math.min(...xs),
    maxX: Math.max(...xs),
    minZ: Math.min(...zs),
    maxZ: Math.max(...zs),
  };
}
