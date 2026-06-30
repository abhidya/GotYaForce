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

export interface StageHitGrid {
  magic: "STIH";
  header: StageHitHeader;
  records: StageHitRecordSummary;
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
      recordCount: Math.floor(recordBytes / STAGE_RECORD_SIZE),
      wholeRecords: recordBytes % STAGE_RECORD_SIZE === 0,
    },
  };
}

export function stageBoundsFromHitGrid(grid: StageHitGrid): StageHitBounds2d {
  return { ...grid.header.bounds2d };
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}
