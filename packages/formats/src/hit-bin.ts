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

const STIH_HEADER_BYTES = 0x28;
const STAGE_RECORD_SIZE = 0x38;

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

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
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
