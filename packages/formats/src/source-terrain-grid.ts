import type { StageHitGrid, StageHitHeader, StageHitTriangle, StageHitVec3 } from "./hit-bin.js";

/** Offsets in DAT_8043625c, not semantic floor/wall names or merged layer indices. */
export type SourceTerrainLayerOffset = 0x1c | 0x20 | 0x24;

export interface SourceTerrainList {
  /** File-relative address after adding the source loader's +8 relocation base. */
  readonly offset: number;
  /** Address of the first 0xffffffff word. Nothing after this word is consumed. */
  readonly sentinelOffset: number;
  /** Includes the actual first -1 read from bytes; array length is not a sentinel. */
  readonly entries: readonly (StageHitTriangle | -1)[];
  /** Existing decoded records, in source pointer order (including duplicates). */
  readonly triangles: readonly StageHitTriangle[];
}

export interface SourceTerrainCell {
  readonly index: number;
  readonly x: number;
  readonly z: number;
  readonly tableOffset: number;
  readonly list: SourceTerrainList;
}

export interface SourceTerrainGrid {
  readonly globalLayerOffset: SourceTerrainLayerOffset;
  /** Explicit owners; neither the bytes nor the decoded geometry is copied. */
  readonly bytes: Uint8Array;
  readonly grid: StageHitGrid;
  readonly header: StageHitHeader;
  readonly cellTableOffset: number;
  readonly recordOffset: number;
  /** X-column-major: index = x * header.gridCells.z + z. */
  readonly cells: readonly SourceTerrainCell[];
}

const HEADER_BYTES = 0x28;
const RELOCATION_BASE = 8;
const RECORD_BYTES = 0x38;
export type SourceTerrainHeaderField = "originX" | "originZ" | "rowStride";
export type SourceTerrainTriangleFloatOffset =
  0x04 | 0x08 | 0x0c | 0x10 | 0x14 | 0x18 | 0x1c | 0x20 | 0x24 | 0x28 | 0x2c | 0x30;

interface SourceTerrainOwner {
  readHeader(field: SourceTerrainHeaderField): number;
  readCellTable(): void;
  readCell(index: number): SourceTerrainCell;
  readListEntry(list: SourceTerrainList, index: number): StageHitTriangle | -1;
  readTriangleFloat(triangle: StageHitTriangle, offset: SourceTerrainTriangleFloatOffset): number;
}
const owners = new WeakMap<object, SourceTerrainOwner>();

/** Brand only: queries must not inspect an unread layer/record's fields eagerly. */
export function assertSourceTerrainGrid(value: unknown): asserts value is SourceTerrainGrid {
  ownerFor(value);
}

/** Validate only this source load, leaving unrelated header fields unread. */
export function readSourceTerrainHeader(grid: SourceTerrainGrid, field: SourceTerrainHeaderField): number {
  return ownerFor(grid).readHeader(field);
}

/** `index` is the consumer's already-computed source integer index, not world coordinates. */
export function readSourceTerrainCell(grid: SourceTerrainGrid, index: number): SourceTerrainCell {
  return ownerFor(grid).readCell(index);
}

/** The table-pointer load precedes the selected cell-word load in source order. */
export function readSourceTerrainCellTable(grid: SourceTerrainGrid): void {
  ownerFor(grid).readCellTable();
}

/** Read the actual pointer/sentinel word; no triangle body is inspected here. */
export function readSourceTerrainListEntry(
  grid: SourceTerrainGrid, list: SourceTerrainList, index: number,
): StageHitTriangle | -1 {
  return ownerFor(grid).readListEntry(list, index);
}

/** Read one reached source float, preserving the supplied decoded vector owner. */
export function readSourceTerrainTriangleFloat(
  grid: SourceTerrainGrid, triangle: StageHitTriangle, offset: SourceTerrainTriangleFloatOffset,
): number {
  return ownerFor(grid).readTriangleFloat(triangle, offset);
}

function ownerFor(value: unknown): SourceTerrainOwner {
  const owner = typeof value === "object" && value !== null ? owners.get(value) : undefined;
  if (!owner) fail("grid was not created from explicit source bytes and parsed storage");
  return owner;
}

/**
 * Source-only view of an explicitly supplied, unrelocated STIH layer and its
 * existing parseStageHitGrid record owner. This does not replace the tolerant
 * host parser or feed the live StageCollision route.
 *
 * zz_003d4a0_ (chunk_0004.c:6909-6957) installs the three layer pointers at global
 * +1c/+20/+24, adds fileBase+8 to header +20/+24 and cell-list offsets, and walks
 * each list only until -1. It does not use the next cell's pointer as an end.
 * The source query readers use the relocated header at file+8, so its +10/+14
 * origins and +c Z stride correspond to file+18/+1c and +14 here.
 *
 * We resolve pointers without mutating the input. Equal list addresses share a
 * view, and equal record addresses share the supplied decoded record. This is
 * an owned-memory view, not an emulation of in-place loader writes. Callers must
 * keep these explicit owners together; no host recordIndices, guessed header,
 * empty-cell substitute, filtered triangle set, or fallback scan is consulted.
 * Coordinate arithmetic and query-time cell selection belong to the consumer.
 * All constructor-reached lists/records are validated here. Subsequent queries
 * use the readSourceTerrain* helpers, which reject drift only as each field is
 * loaded. In particular, a nonempty-list refusal does not inspect its triangle
 * body, and a skipped triangle does not require an unread normal/Y component.
 */
export function createSourceTerrainGrid(
  input: Uint8Array | ArrayBuffer,
  grid: StageHitGrid,
  globalLayerOffset: SourceTerrainLayerOffset,
): SourceTerrainGrid {
  if (globalLayerOffset !== 0x1c && globalLayerOffset !== 0x20 && globalLayerOffset !== 0x24) {
    fail("layer identity must be global +0x1c, +0x20, or +0x24");
  }
  const bytes = input instanceof Uint8Array ? input : new Uint8Array(input);
  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const sourceWords = new Map<number, number>();
  requireRange(0, HEADER_BYTES, "header");
  for (let offset = 0; offset < HEADER_BYTES; offset += 4) rememberWord(offset);
  if (view.getUint32(0, false) !== 0x53544948 || grid.magic !== "STIH") fail("missing STIH magic");

  const declaredBytes = view.getUint32(4, false);
  if (declaredBytes !== bytes.byteLength) fail("declared size does not match supplied bytes");
  // The constructor's nested loops and the query's stride are signed int32s.
  // Negative dimensions are not silently turned into host-sized unsigned grids.
  const gridX = view.getInt32(0x10, false);
  const gridZ = view.getInt32(0x14, false);
  if (gridX < 0 || gridZ < 0) fail("negative signed grid dimension");
  const cellCount = gridX * gridZ;
  if (!Number.isSafeInteger(cellCount)) fail("grid cell count exceeds the exact integer domain");
  const cellTableOffset = view.getInt32(0x20, false) + RELOCATION_BASE;
  const recordOffset = view.getInt32(0x24, false) + RELOCATION_BASE;
  if (cellTableOffset < HEADER_BYTES || cellTableOffset % 4 !== 0) fail("invalid cell table pointer");
  requireRange(cellTableOffset, cellCount * 4, "cell table");
  if (recordOffset < HEADER_BYTES || recordOffset % 4 !== 0) fail("invalid record storage pointer");
  requireRange(recordOffset, 0, "record storage");

  const header = grid.header;
  const originX = view.getInt32(0x18, false);
  const originZ = view.getInt32(0x1c, false);
  const cellSizeX = view.getUint32(0x08, false);
  const cellSizeZ = view.getUint32(0x0c, false);
  const headerOwners = [header.cellSize, header.gridCells, header.origin, header.bounds2d];
  const records = grid.records;
  const triangleStorage = grid.triangles;
  const recordBytes = bytes.byteLength - recordOffset;
  const recordCount = Math.floor(recordBytes / RECORD_BYTES);
  validateHeaderAndStorage();

  function validateHeaderAndStorage(): void {
    if (grid.header !== header || grid.records !== records || grid.triangles !== triangleStorage
        || [header.cellSize, header.gridCells, header.origin, header.bounds2d]
          .some((owner, index) => owner !== headerOwners[index])) {
      fail("supplied header or record storage owner was replaced");
    }
    if (grid.magic !== "STIH" || header.declaredBytes !== declaredBytes
      || header.cellSize.x !== cellSizeX || header.cellSize.z !== cellSizeZ
      || header.gridCells.x !== gridX || header.gridCells.z !== gridZ || header.gridCells.total !== cellCount
      || header.origin.x !== originX || header.origin.z !== originZ
      || header.unknown20 !== view.getUint32(0x20, false)
      || header.recordSentinelOffset !== view.getUint32(0x24, false)
      || header.bounds2d.minX !== originX || header.bounds2d.minZ !== originZ
      || header.bounds2d.maxX !== originX + cellSizeX * gridX
      || header.bounds2d.maxZ !== originZ + cellSizeZ * gridZ) {
      fail("supplied parsed header does not belong to these bytes");
    }
    if (grid.records.offset !== recordOffset || grid.records.bytes !== recordBytes
      || grid.records.recordSize !== RECORD_BYTES || grid.records.recordCount !== recordCount
      || grid.records.wholeRecords !== (recordBytes % RECORD_BYTES === 0)
      || grid.triangles.length !== recordCount) {
      fail("supplied decoded record storage does not belong to these bytes");
    }
  }

  const lists = new Map<number, SourceTerrainList>();
  const validatedRecords = new Set<number>();
  const recordOwners = new Map<StageHitTriangle, {
    index: number; offset: number; vertices: StageHitTriangle["vertices"];
    vertexOwners: StageHitVec3[]; normal: StageHitVec3;
  }>();
  const cells: SourceTerrainCell[] = [];
  for (let index = 0; index < cellCount; index += 1) {
    const tableOffset = cellTableOffset + index * 4;
    rememberWord(tableOffset);
    const listOffset = view.getInt32(tableOffset, false) + RELOCATION_BASE;
    let list = lists.get(listOffset);
    if (!list) {
      if (listOffset < HEADER_BYTES || listOffset % 4 !== 0) {
        fail(`cell ${index} has an invalid list pointer`);
      }
      const triangles: StageHitTriangle[] = [];
      let cursor = listOffset;
      for (;;) {
        requireRange(cursor, 4, `cell ${index} list lacks an in-bounds -1 sentinel`);
        rememberWord(cursor);
        const relativeRecordOffset = view.getInt32(cursor, false);
        if (relativeRecordOffset === -1) break;
        if (relativeRecordOffset < 0 || relativeRecordOffset % RECORD_BYTES !== 0) {
          fail(`cell ${index} has an invalid reached record pointer at ${hex(cursor)}`);
        }
        const recordIndex = relativeRecordOffset / RECORD_BYTES;
        const triangle = grid.triangles[recordIndex];
        if (!triangle || recordIndex >= recordCount) {
          fail(`cell ${index} reached a record outside supplied storage at ${hex(cursor)}`);
        }
        if (!validatedRecords.has(recordIndex)) {
          const offset = recordOffset + relativeRecordOffset;
          validateRecord(triangle, recordIndex, offset);
          for (let word = offset; word < offset + RECORD_BYTES; word += 4) rememberWord(word);
          const vertices = triangle.vertices;
          const vertexOwners = [...vertices];
          const normal = triangle.normal;
          recordOwners.set(triangle, { index: recordIndex, offset, vertices, vertexOwners, normal });
          validatedRecords.add(recordIndex);
        }
        triangles.push(triangle);
        cursor += 4;
      }
      list = Object.freeze({ offset: listOffset, sentinelOffset: cursor,
        entries: Object.freeze([...triangles, -1] as (StageHitTriangle | -1)[]),
        triangles: Object.freeze(triangles) });
      lists.set(listOffset, list);
    }
    cells.push(Object.freeze({ index, x: Math.floor(index / gridZ), z: index % gridZ, tableOffset, list }));
  }
  const result: SourceTerrainGrid = Object.freeze({ globalLayerOffset, bytes, grid, header,
    cellTableOffset, recordOffset, cells: Object.freeze(cells) });
  const listOwners = new Set(lists.values());
  owners.set(result, {
    readHeader(field) {
      requireOwner(grid, "header", header);
      if (field === "rowStride") {
        requireOwner(header, "gridCells", headerOwners[1]);
        checkWord(0x14);
        return requireNumber(header.gridCells, "z", gridZ);
      }
      if (field !== "originX" && field !== "originZ") fail("unknown source header field");
      requireOwner(header, "origin", headerOwners[2]);
      checkWord(field === "originX" ? 0x18 : 0x1c);
      return requireNumber(header.origin, field === "originX" ? "x" : "z", field === "originX" ? originX : originZ);
    },
    readCellTable() {
      requireOwner(grid, "header", header);
      checkWord(0x20);
      requireNumber(header, "unknown20", cellTableOffset - RELOCATION_BASE);
    },
    readCell(index) {
      if (!Number.isSafeInteger(index) || index < 0 || index >= cells.length) {
        fail(`source cell index ${index} is outside constructed storage`);
      }
      const cell = cells[index]!;
      checkWord(cell.tableOffset);
      return cell;
    },
    readListEntry(list, index) {
      if (!listOwners.has(list)) fail("list does not belong to this source grid");
      if (!Number.isSafeInteger(index) || index < 0 || index >= list.entries.length) {
        fail("list entry index does not reach an owned pointer or sentinel");
      }
      checkWord(list.offset + index * 4);
      return list.entries[index]!;
    },
    readTriangleFloat(triangle, relativeOffset) {
      const record = recordOwners.get(triangle);
      if (!record) fail("triangle does not belong to a reached source record");
      if (!Number.isInteger(relativeOffset) || relativeOffset < 4 || relativeOffset > 0x30 || relativeOffset % 4 !== 0) {
        fail("float offset is not a source vertex/normal component");
      }
      requireOwner(grid, "triangles", triangleStorage);
      requireOwner(triangleStorage, String(record.index), triangle);
      requireNumber(triangle, "index", record.index);
      requireNumber(triangle, "recordOffset", record.offset);
      const axis = ["x", "y", "z"][(relativeOffset - 4) / 4 % 3]!;
      let vector: StageHitVec3;
      if (relativeOffset >= 0x28) {
        requireOwner(triangle, "normal", record.normal);
        vector = record.normal;
      } else {
        const vertexIndex = Math.floor((relativeOffset - 4) / 12);
        requireOwner(triangle, "vertices", record.vertices);
        vector = record.vertexOwners[vertexIndex]!;
        requireOwner(record.vertices, String(vertexIndex), vector);
      }
      checkWord(record.offset + relativeOffset);
      return requireNumber(vector, axis, view.getFloat32(record.offset + relativeOffset, false));
    },
  });
  return result;

  function rememberWord(offset: number): void {
    sourceWords.set(offset, view.getUint32(offset, false));
  }

  function checkWord(offset: number): void {
    if (!sourceWords.has(offset) || view.getUint32(offset, false) !== sourceWords.get(offset)) {
      fail(`owned source word changed at ${hex(offset)}`);
    }
  }

  function requireRange(offset: number, length: number, label: string): void {
    if (!Number.isSafeInteger(offset) || !Number.isSafeInteger(length)
        || offset < 0 || length < 0 || offset + length > bytes.byteLength) {
      fail(`${label} is outside supplied bytes`);
    }
  }

  function validateRecord(triangle: StageHitTriangle, index: number, offset: number): void {
    requireRange(offset, RECORD_BYTES, "reached triangle record");
    if (triangle.index !== index || triangle.recordOffset !== offset
        || triangle.marker !== view.getUint32(offset, false)
        || !Array.isArray(triangle.vertices) || triangle.vertices.length !== 3
        || !sameVec(triangle.vertices[0], offset + 4)
        || !sameVec(triangle.vertices[1], offset + 0x10)
        || !sameVec(triangle.vertices[2], offset + 0x1c)
        || !sameVec(triangle.normal, offset + 0x28)
        || !Object.is(triangle.planeD, view.getFloat32(offset + 0x34, false))) {
      fail(`decoded triangle ${index} does not belong to its source record`);
    }
  }

  function sameVec(vec: StageHitVec3 | undefined, offset: number): boolean {
    return vec !== undefined && vec !== null
      && Object.is(vec.x, view.getFloat32(offset, false))
      && Object.is(vec.y, view.getFloat32(offset + 4, false))
      && Object.is(vec.z, view.getFloat32(offset + 8, false));
  }
}

function fail(message: string): never {
  throw new RangeError(`source terrain: ${message}`);
}

function ownValue(owner: object, key: string): unknown {
  const descriptor = Object.getOwnPropertyDescriptor(owner, key);
  if (!descriptor || !("value" in descriptor)) fail(`source field ${key} is not an own data property`);
  return descriptor.value;
}

function requireOwner(owner: object, key: string, expected: unknown): void {
  if (ownValue(owner, key) !== expected) fail(`source field ${key} owner was replaced`);
}

function requireNumber(owner: object, key: string, expected: number): number {
  const value = ownValue(owner, key);
  if (typeof value !== "number" || !Object.is(value, expected)) fail(`source field ${key} differs from its owned bytes`);
  return value;
}

function hex(value: number): string {
  return `0x${value.toString(16)}`;
}
