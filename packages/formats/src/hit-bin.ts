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

export interface ActorHitRemapEntry {
  /** Remap slot index (section A: one u8 per slot; section B/comhit: 4-byte slots). */
  slot: number;
  /** Position within the slot (always 0 for 1-byte slots; 0..3 for 4-byte slots). */
  position: number;
  /** Record index this entry points at (0xFF entries are inactive and skipped). */
  value: number;
}

/**
 * One 0x50-byte hitbox-placement record. Field semantics are VERIFIED against the
 * DOL spawners (chunk_0013.c zz_008ab30_ @0x8008ab30:1297, zz_008ac80_ @0x8008ac80:1349,
 * zz_008ae60_ @0x8008ae60:1439; consumer FUN_8008a65c :1121; shape eval
 * chunk_0004.c FUN_8003c8b4 :6481).
 */
export interface ActorHitRecord {
  index: number;
  offset: number;
  raw: Uint8Array;
  nonZero: boolean;
  /** +0x00 u8 — hitbox shape kind (dispatch PTR_FUN_802da740/802da758). */
  shapeKind: number;
  /** +0x01 u8 low 7 bits — attach bone (actor+0x8d4 + bone*0x30). */
  boneIndex: number;
  /** +0x01 bit 0x80 — attach to the actor root matrix (+0x1aa4) instead of a bone. */
  attachToRoot: boolean;
  /** +0x02 u16 — collision-list flags (zz_008a2bc_ chunk_0013.c:973; bit 0x40 = attack list). */
  collisionFlags: number;
  /** +0x04 u16 — damage-record index into the 0x18-stride DOL table at actor+0x27c. */
  damageRecordIndex: number;
  /** +0x06 s16 — active-start (borgs: anim-frame threshold vs actor+0x1cdc). */
  activeStart: number;
  /** +0x08 s16 — active-end; -1 = persistent (body hurtboxes). */
  activeEnd: number;
  /** +0x0C f32[3] — local offset (transformed by the attach matrix). */
  localOffset: [number, number, number];
  /** +0x18 f32[3] — capsule half-extent axis (endpoints = offset ± this). */
  halfExtent: [number, number, number];
  /** +0x24 f32 — radius, scaled by actor scale (+0xc0). */
  radius: number;
}

export interface ActorHitTableSection {
  /** Body hurtboxes (persistent) vs attack/child-object hitboxes. */
  name: "bodyHurtboxes" | "attackHitboxes" | "commonHitboxes";
  remapOffset: number;
  remapBytes: number;
  /** Bytes per remap slot: 1 (section A u8 entries) or 4 (0xFF-terminated u8[4] slots). */
  remapSlotStride: 1 | 4;
  recordOffset: number;
  recordCount: number;
  remapEntries: ActorHitRemapEntry[];
  records: ActorHitRecord[];
}

export interface ActorHitTable {
  kind: ActorHitTableKind;
  category:
    | "player-borg-hit-table"
    | "global-common-hit-table"
    | "secondary-common-hit-table-UNVERIFIED";
  bytes: number;
  /**
   * True when the byte-exact verified layout applies. `comhit2.bin` (0x3D40) fits
   * neither the old 0xF4 model nor the proven 0x50 two-section model cleanly and is
   * EXPLICITLY OPEN — it parses to zero sections with valid=false.
   */
  valid: boolean;
  sections: ActorHitTableSection[];
}

const STIH_HEADER_BYTES = 0x28;
const STAGE_RECORD_SIZE = 0x38;
/**
 * Actor/common hit record stride. VERIFIED 0x50 from the executed indexing in the DOL
 * (record = base + idx*0x50 in all three spawners, chunk_0013.c:1297/1349/1439). The
 * previous 0xF4 model was a statistical artifact: 32*0xF4+0x20 and the real
 * two-section layout both happen to sum to the 0x1EA0 pl file size.
 */
export const ACTOR_HIT_RECORD_SIZE = 0x50;
/** pl####hit.bin exact size (also how actor+0x3fc pages are strided: chunk_0006.c:7126). */
export const PLAYER_HIT_FILE_SIZE = 0x1ea0;
/** comhit.bin exact size: 0x400 remap (256 x 4B slots) + 256 x 0x50 records. */
export const COMHIT_FILE_SIZE = 0x5400;

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
  const cells = parseCells(view, cellCount, gridZ, offsetTableEnd, recordSentinelOffset, recordBytes);
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

/**
 * Parse the actor/common hit tables to the DOL-verified layout:
 *
 *   pl####hit.bin (0x1EA0):
 *     [0x000] 32 x u8 remap A            — persistent body hurtbox selection
 *     [0x020] 32 x 0x50 records          — body hurtboxes (activeEnd = -1)
 *     [0xA20] 32 x u8[4] remap B slots   — attack/child hitboxes, 0xFF-terminated
 *     [0xAA0] 64 x 0x50 records
 *   comhit.bin (0x5400):
 *     [0x000] 256 x u8[4] remap slots
 *     [0x400] 256 x 0x50 records
 *
 * Spawner indexing (record = base + idx*0x50) proven at chunk_0013.c:1297 (own table
 * via actor+0x3fc), :1349 (child/projectile, remap base+0xa20+kind*4), :1439 (comhit
 * via PTR_DAT_80433934+0x98, remap base+slot*4, 0xFF-terminated).
 *
 * comhit2.bin (0x3D40) fits neither model cleanly and is EXPLICITLY OPEN: it returns
 * zero sections with valid=false rather than guessing a stride.
 */
export function parseActorHitTable(
  input: Uint8Array | ArrayBuffer,
  options: ParseActorHitTableOptions = {},
): ActorHitTable {
  const bytes = asBytes(input);
  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const lower = options.fileName?.toLowerCase() ?? "";
  const kind =
    options.kind ?? (lower === "comhit.bin" ? "comhit" : lower === "comhit2.bin" ? "comhit2" : "player");

  if (kind === "comhit2") {
    return {
      kind,
      category: "secondary-common-hit-table-UNVERIFIED",
      bytes: bytes.byteLength,
      valid: false,
      sections: [],
    };
  }

  if (kind === "comhit") {
    if (bytes.byteLength !== COMHIT_FILE_SIZE) {
      throw new RangeError(`comhit.bin must be 0x${COMHIT_FILE_SIZE.toString(16)} bytes, got ${bytes.byteLength}`);
    }
    return {
      kind,
      category: "global-common-hit-table",
      bytes: bytes.byteLength,
      valid: true,
      sections: [actorHitSection(bytes, view, "commonHitboxes", 0x000, 0x400, 4, 0x400, 256)],
    };
  }

  if (bytes.byteLength !== PLAYER_HIT_FILE_SIZE) {
    throw new RangeError(
      `pl####hit.bin must be 0x${PLAYER_HIT_FILE_SIZE.toString(16)} bytes, got ${bytes.byteLength}`,
    );
  }
  return {
    kind,
    category: "player-borg-hit-table",
    bytes: bytes.byteLength,
    valid: true,
    sections: [
      actorHitSection(bytes, view, "bodyHurtboxes", 0x000, 0x20, 1, 0x020, 32),
      actorHitSection(bytes, view, "attackHitboxes", 0xa20, 0x80, 4, 0xaa0, 64),
    ],
  };
}

function asBytes(input: Uint8Array | ArrayBuffer): Uint8Array {
  return input instanceof Uint8Array ? input : new Uint8Array(input);
}

function actorHitSection(
  bytes: Uint8Array,
  view: DataView,
  name: ActorHitTableSection["name"],
  remapOffset: number,
  remapBytes: number,
  remapSlotStride: 1 | 4,
  recordOffset: number,
  recordCount: number,
): ActorHitTableSection {
  const remapEntries: ActorHitRemapEntry[] = [];
  for (let slot = 0; slot < remapBytes / remapSlotStride; slot += 1) {
    for (let position = 0; position < remapSlotStride; position += 1) {
      const value = view.getUint8(remapOffset + slot * remapSlotStride + position);
      if (value === 0xff) break; // 0xFF terminates a slot's entry list (chunk_0013.c:1439)
      remapEntries.push({ slot, position, value });
    }
  }
  const records = Array.from({ length: recordCount }, (_, index) =>
    parseActorHitRecord(bytes, view, recordOffset + index * ACTOR_HIT_RECORD_SIZE, index),
  );
  return { name, remapOffset, remapBytes, remapSlotStride, recordOffset, recordCount, remapEntries, records };
}

function parseActorHitRecord(bytes: Uint8Array, view: DataView, offset: number, index: number): ActorHitRecord {
  const bone = view.getUint8(offset + 0x01);
  return {
    index,
    offset,
    raw: bytes.slice(offset, offset + ACTOR_HIT_RECORD_SIZE),
    nonZero: bytes.subarray(offset, offset + ACTOR_HIT_RECORD_SIZE).some((byte) => byte !== 0),
    shapeKind: view.getUint8(offset + 0x00),
    boneIndex: bone & 0x7f,
    attachToRoot: (bone & 0x80) !== 0,
    collisionFlags: view.getUint16(offset + 0x02, false),
    damageRecordIndex: view.getUint16(offset + 0x04, false),
    activeStart: view.getInt16(offset + 0x06, false),
    activeEnd: view.getInt16(offset + 0x08, false),
    localOffset: [
      view.getFloat32(offset + 0x0c, false),
      view.getFloat32(offset + 0x10, false),
      view.getFloat32(offset + 0x14, false),
    ],
    halfExtent: [
      view.getFloat32(offset + 0x18, false),
      view.getFloat32(offset + 0x1c, false),
      view.getFloat32(offset + 0x20, false),
    ],
    radius: view.getFloat32(offset + 0x24, false),
  };
}

function parseCells(
  view: DataView,
  cellCount: number,
  // STIH cell-offset tables are X-COLUMN-major: flat index = cx * gridZ + cz (EMPIRICALLY
  // PROVEN 2026-07-05 — st00 wall tri at world cell (15,28) lives at flat 658 = 15*42+28;
  // the old X-row-major reading transposed every cell and made walls walk-through).
  gridZ: number,
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
      x: Math.floor(index / gridZ),
      z: index % gridZ,
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
