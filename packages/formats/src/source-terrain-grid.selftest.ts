import { parseStageHitGrid } from "./hit-bin.js";
import {
  assertSourceTerrainGrid, createSourceTerrainGrid, readSourceTerrainHeader, readSourceTerrainCellTable, readSourceTerrainCell,
  readSourceTerrainListEntry, readSourceTerrainTriangleFloat,
  type SourceTerrainGrid, type SourceTerrainLayerOffset,
} from "./source-terrain-grid.js";

// Independently authored STIH data only. No extracted assets or capture fixtures.
function fixture(options: {
  x?: number; z?: number; originX?: number; originZ?: number; tableOffset?: number;
  lists?: number[][]; cellLists?: number[]; recordCount?: number; trailingBytes?: number;
} = {}) {
  const x = options.x ?? 2;
  const z = options.z ?? 3;
  const tableOffset = options.tableOffset ?? 0x40;
  const lists = options.lists ?? [[0, -1, 7], [0x38, 0, -1], [-1], [0, 0, -1]];
  const cellLists = options.cellLists ?? [1, 0, 2, 3, 0, 1];
  const listOffsets: number[] = [];
  let cursor = tableOffset + x * z * 4;
  for (const list of lists) { listOffsets.push(cursor); cursor += list.length * 4; }
  const recordOffset = cursor + 8;
  const bytes = new Uint8Array(recordOffset + (options.recordCount ?? 2) * 0x38 + (options.trailingBytes ?? 0));
  const view = new DataView(bytes.buffer);
  const word = (offset: number, value: number) => view.setUint32(offset, value >>> 0, false);
  word(0, 0x53544948); word(4, bytes.length);
  // Deliberately unlike the query's separate 500.0 constant: preserve, do not infer.
  word(8, 13); word(0xc, 17); word(0x10, x); word(0x14, z);
  word(0x18, options.originX ?? -1000); word(0x1c, options.originZ ?? -1500);
  word(0x20, tableOffset - 8); word(0x24, recordOffset - 8);
  cellLists.forEach((listIndex, cellIndex) => word(tableOffset + cellIndex * 4, listOffsets[listIndex]! - 8));
  lists.forEach((list, index) => list.forEach((value, j) => word(listOffsets[index]! + j * 4, value)));
  word(recordOffset - 8, -1); word(recordOffset - 4, -1);
  for (let index = 0; index < (options.recordCount ?? 2); index += 1) {
    const offset = recordOffset + index * 0x38;
    word(offset, 0xabc00000 + index);
    const floats = [0, index * 10, 0, 20, index * 10, 0, 0, index * 10, 20, 0, 1, 0, -index * 10];
    floats.forEach((value, j) => view.setFloat32(offset + 4 + j * 4, value, false));
  }
  return { bytes, view, word, tableOffset, listOffsets, recordOffset, grid: parseStageHitGrid(bytes) };
}

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[source-terrain-grid] ${message}`);
}
function rejects(run: () => unknown, message: string, expected?: string): void {
  let error: unknown;
  try { run(); } catch (caught) { error = caught; }
  assert(error instanceof RangeError, `${message}: expected explicit RangeError, got ${String(error)}`);
  if (expected) assert(error.message.includes(expected), `${message}: ${error.message}`);
}

function testSourceOffsetsAndOwnership(): void {
  const f = fixture();
  const bytesBefore = f.bytes.slice();
  const hostBefore = JSON.stringify(f.grid);
  for (const layer of [0x1c, 0x20, 0x24] as const) {
    const source = createSourceTerrainGrid(f.bytes, f.grid, layer);
    assertSourceTerrainGrid(source);
    readSourceTerrainCellTable(source);
    assert(readSourceTerrainHeader(source, "originX") === -1000
      && readSourceTerrainHeader(source, "originZ") === -1500
      && readSourceTerrainHeader(source, "rowStride") === 3, "source header fields load through actual owner");
    assert(source.globalLayerOffset === layer, "preserves the selected source global layer identity");
    assert(source.bytes === f.bytes && source.grid === f.grid && source.header === f.grid.header,
      "raw bytes, parsed grid, and real header keep owner identity");
    assert(source.cellTableOffset === 0x40 && source.recordOffset === f.recordOffset,
      "table location comes from actual header +20 plus8, not hard-coded +28");
    assert(source.cells.map(cell => `${cell.x},${cell.z}`).join(";") === "0,0;0,1;0,2;1,0;1,1;1,2",
      "rectangular grid uses X-column-major table order");
    assert(source.cells[0]!.list.offset === f.listOffsets[1], "each list pointer adds the +8 base");
    assert(source.cells[0]!.list.triangles[0] === f.grid.triangles[1]
      && source.cells[0]!.list.triangles[1] === f.grid.triangles[0], "record order and ownership are exact");
    assert(source.cells[0]!.list.entries[2] === -1, "entries retain the actual sentinel word");
    assert(readSourceTerrainCell(source, 0) === source.cells[0]
      && readSourceTerrainListEntry(source, source.cells[0]!.list, 0) === f.grid.triangles[1]
      && readSourceTerrainListEntry(source, source.cells[0]!.list, 2) === -1,
      "loaded cell, record pointer, and actual sentinel preserve identity");
    for (const [offset, expected] of [[4, 0], [8, 10], [0xc, 0], [0x10, 20], [0x14, 10], [0x18, 0],
      [0x1c, 0], [0x20, 10], [0x24, 20], [0x28, 0], [0x2c, 1], [0x30, 0]] as const) {
      assert(readSourceTerrainTriangleFloat(source, f.grid.triangles[1]!, offset) === expected,
        "source float offset selects the exact decoded vertex/normal component");
    }
    assert(source.cells[1]!.list.triangles.length === 1, "-1 terminates before invalid unread trailing garbage");
    assert(source.cells[1]!.list.sentinelOffset === f.listOffsets[0]! + 4, "records actual sentinel address");
    assert(source.cells[2]!.list.entries.length === 1 && source.cells[2]!.list.entries[0] === -1,
      "empty means a real -1 read, not a fabricated absent cell");
    assert(source.cells[3]!.list.triangles[0] === source.cells[3]!.list.triangles[1],
      "repeated record addresses retain duplicate identity and order");
    assert(source.cells[0]!.list === source.cells[5]!.list && source.cells[1]!.list === source.cells[4]!.list,
      "same list addresses preserve aliasing despite unsorted cell pointers");
    assert(source.cells[0]!.list.triangles[0]!.vertices === f.grid.triangles[1]!.vertices
      && source.cells[0]!.list.triangles[0]!.normal === f.grid.triangles[1]!.normal,
      "existing vertex and normal ownership is not reconstructed");
    assert(Object.isFrozen(source) && Object.isFrozen(source.cells) && Object.isFrozen(source.cells[0]!)
      && Object.isFrozen(source.cells[0]!.list) && Object.isFrozen(source.cells[0]!.list.entries),
      "source metadata and sentinel arrays cannot be replaced");
    assert(!Object.isFrozen(f.grid.header) && !Object.isFrozen(f.grid.triangles[0]!),
      "construction does not freeze the separate tolerant host owner");
  }
  assert(f.bytes.every((byte, index) => byte === bytesBefore[index]) && JSON.stringify(f.grid) === hostBefore,
    "strict construction never rewrites source pointers or tolerant host parsing");
  assert(f.grid.cells.some(cell => cell.anomalous), "fixture exposes host tolerance without relying on it");
}

function testTerminationAndReachedPointers(): void {
  const single = () => fixture({ x: 1, z: 1, lists: [[0, -1, 3]], cellLists: [0] });
  {
    const f = single();
    const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    f.word(f.listOffsets[0]! + 8, 0x7fffffff);
    assertSourceTerrainGrid(source); // Unread trailing bytes are outside the captured source read set.
    assert(source.cells[0]!.list.entries.length === 2, "unread garbage cannot become a second record");
  }
  for (const bad of [1, -2, 0x70, 0x7ffffff8]) {
    const f = single(); f.word(f.listOffsets[0]!, bad);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), `bad reached record ${bad}`);
  }
  for (const bad of [0, 1, -8, 0x7ffffff8]) {
    const f = single(); f.word(f.tableOffset, bad);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), `bad reached cell pointer ${bad}`);
  }
  {
    const f = single();
    // Valid record pointer at the last word, followed by no readable sentinel.
    f.word(f.tableOffset, f.bytes.length - 12); f.word(f.bytes.length - 4, 0);
    f.grid = parseStageHitGrid(f.bytes);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "missing sentinel", "-1 sentinel");
  }
  {
    const f = fixture({ x: 1, z: 1, lists: [[0x70, -1]], cellLists: [0], trailingBytes: 4 });
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "partial trailing record is not an owner");
  }
}

function testHeaderDomainsAndOwnerMismatch(): void {
  for (const origin of [-0x80000000, 0x7fffffff]) {
    const f = fixture({ originX: origin, originZ: -1 });
    const source = createSourceTerrainGrid(f.bytes, f.grid, 0x20);
    assert(source.header.origin.x === origin && source.header.origin.z === -1,
      "signed origins are preserved without converting to unsigned or rounding for queries");
  }
  for (const [x, z] of [[0, 3], [2, 0], [0, 0x7fffffff]]) {
    const f = fixture({ x: x!, z: z!, lists: [], cellLists: [] });
    assert(createSourceTerrainGrid(f.bytes, f.grid, 0x24).cells.length === 0,
      "zero source dimension creates no cell addresses or invented sentinel lists");
  }
  for (const offset of [0x10, 0x14]) {
    const f = fixture(); f.word(offset, 0x80000000);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "negative signed dimensions", "negative signed");
  }
  {
    const f = fixture(); f.word(0x10, 0x7fffffff); f.word(0x14, 0x7fffffff);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "unsafe count product", "integer domain");
  }
  {
    const f = fixture(); f.word(0x10, 1000000);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "table exceeds owned byte range", "cell table");
  }
  for (const offset of [0x20, 0x24]) {
    for (const word of [0, 1, 0x7ffffff8]) {
      const f = fixture(); f.word(offset, word);
      rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "bad source header pointer");
    }
  }
  {
    const f = fixture(); const other = fixture({ originX: 123 });
    rejects(() => createSourceTerrainGrid(f.bytes, other.grid, 0x1c), "foreign parsed header", "header");
  }
  {
    const f = fixture(); f.grid.triangles[0]!.vertices[0].x += 1;
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "unrelated decoded geometry", "triangle");
  }
  {
    const f = fixture(); f.grid.records.offset += 4;
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "foreign record base", "storage");
  }
  {
    const f = fixture(); f.grid.header.gridCells.total += 1;
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "invented cell count", "header");
  }
  {
    const f = fixture();
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x28 as SourceTerrainLayerOffset), "unknown layer identity");
    rejects(() => createSourceTerrainGrid(new Uint8Array(3), f.grid, 0x1c), "truncated header");
    f.word(0, 0); rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "bad magic");
  }
  {
    const f = fixture(); f.word(4, f.bytes.length - 1);
    rejects(() => createSourceTerrainGrid(f.bytes, f.grid, 0x1c), "declared length mismatch");
  }
  {
    const f = fixture();
    const backing = new Uint8Array(f.bytes.length + 24); backing.set(f.bytes, 12);
    const slice = backing.subarray(12, backing.length - 12);
    const source = createSourceTerrainGrid(slice, parseStageHitGrid(slice), 0x1c);
    assert(source.bytes === slice && source.cells[0]!.list.entries.length === 3,
      "DataView addresses respect an explicitly supplied byte slice");
    assert(createSourceTerrainGrid(f.bytes.buffer, f.grid, 0x1c).cells.length === 6, "ArrayBuffer inputs work");
  }
}

function testQueryTimeOwnershipGuards(): void {
  type F = ReturnType<typeof fixture>;
  const readOrigin = (source: SourceTerrainGrid) => readSourceTerrainHeader(source, "originX");
  const readX = (source: SourceTerrainGrid, f: F) => readSourceTerrainTriangleFloat(source, f.grid.triangles[0]!, 4);
  const readNormalY = (source: SourceTerrainGrid, f: F) => readSourceTerrainTriangleFloat(source, f.grid.triangles[0]!, 0x2c);
  const mutations: [mutate: (f: F) => void, load: (source: SourceTerrainGrid, f: F) => unknown][] = [
    [f => { f.grid.header = { ...f.grid.header }; }, readOrigin],
    [f => { f.grid.header.origin = { ...f.grid.header.origin }; }, readOrigin],
    [f => { f.grid.header.origin.x += 1; }, readOrigin],
    [f => { f.grid.header.gridCells = { ...f.grid.header.gridCells }; }, source => readSourceTerrainHeader(source, "rowStride")],
    [f => { f.grid.header.unknown20 += 4; }, readSourceTerrainCellTable],
    [f => { f.word(0x20, 0); }, readSourceTerrainCellTable],
    [f => { f.grid.triangles = [...f.grid.triangles]; }, readX],
    [f => { f.grid.triangles[0] = { ...f.grid.triangles[0]! }; }, readX],
    [f => { f.grid.triangles[0]!.vertices = [...f.grid.triangles[0]!.vertices]; }, readX],
    [f => { f.grid.triangles[0]!.vertices[0] = { ...f.grid.triangles[0]!.vertices[0] }; }, readX],
    [f => { f.grid.triangles[0]!.normal = { ...f.grid.triangles[0]!.normal }; }, readNormalY],
    [f => { f.grid.triangles[0]!.normal.y = -1; }, readNormalY],
    [f => { f.grid.triangles[0]!.vertices[0].x += 1; }, readX],
    [f => { f.word(f.tableOffset, f.listOffsets[0]! - 8); }, source => readSourceTerrainCell(source, 0)],
    [f => { f.word(f.listOffsets[0]! + 4, 0); }, source => readSourceTerrainListEntry(source, source.cells[1]!.list, 1)],
    [f => { f.view.setFloat32(f.recordOffset + 4, 3, false); f.grid.triangles[0]!.vertices[0].x = 3; }, readX],
  ];
  for (const [mutate, load] of mutations) {
    const f = fixture(); const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    mutate(f);
    assertSourceTerrainGrid(source); // Brand is deliberately not a whole-layer scan.
    rejects(() => load(source, f), "actual source load rejects stale/replaced ownership");
  }
  {
    const f = fixture(); const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    rejects(() => assertSourceTerrainGrid({ ...source }), "structural copy is not source-owned");
    rejects(() => assertSourceTerrainGrid({ cells: [] }), "fabricated empty cells cannot be admitted");
    rejects(() => assertSourceTerrainGrid(null), "missing owner cannot be admitted");
    rejects(() => readSourceTerrainCell(source, -1), "no fallback for negative flat index");
    rejects(() => readSourceTerrainCell(source, 6), "no fallback beyond table");
    rejects(() => readSourceTerrainCell(source, 1.5), "no invented rounding of flat index");
    rejects(() => readSourceTerrainListEntry(source, { ...source.cells[0]!.list }, 0), "foreign list rejected");
    rejects(() => readSourceTerrainListEntry(source, source.cells[0]!.list, 3), "no invented sentinel at array end");
    // The tolerant host's projection is neither trusted nor changed by this view.
    f.grid.cells = [];
    assertSourceTerrainGrid(source);
    assert(source.cells.length === 6, "missing host cells cannot trigger source fallback");
  }
  {
    const f = fixture({ x: 1, z: 1, lists: [[-1]], cellLists: [0] });
    const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    f.grid.triangles[1]!.normal.y = 123; // Not reached by any source list.
    assertSourceTerrainGrid(source);
    assert(source.cells[0]!.list.triangles.length === 0, "no whole-mesh scan is invented for empty source lists");
  }
  {
    const f = fixture(); const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    let getterCalls = 0;
    Object.defineProperty(f.grid.triangles[0]!.normal, "y", { get: () => { getterCalls += 1; return 1; } });
    Object.defineProperty(f.grid.triangles[0]!.vertices[0], "y", { get: () => { getterCalls += 1; return 0; } });
    f.grid.header.cellSize.x = 999;
    f.grid.header.origin.z = 999;
    assertSourceTerrainGrid(source);
    assert(readSourceTerrainHeader(source, "originX") === -1000, "unread originZ/cell-size fields stay unread");
    const entry = readSourceTerrainListEntry(source, readSourceTerrainCell(source, 1).list, 0);
    assert(entry === f.grid.triangles[0], "nonempty-list refusal can inspect pointer without touching body");
    assert(readSourceTerrainTriangleFloat(source, entry, 4) === 0, "vertexX does not load unread Y or normal");
    assert(getterCalls === 0, "unread numeric getters have no effects");
    rejects(() => readSourceTerrainTriangleFloat(source, entry, 8), "reached vertexY accessor rejected");
    rejects(() => readSourceTerrainTriangleFloat(source, entry, 0x2c), "reached normalY accessor rejected");
    assert(getterCalls === 0, "reached non-data properties are rejected without invoking getters");
  }
  {
    const f = fixture(); const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    f.word(f.tableOffset, 0); // Corrupt a cell other than the actual selected cell.
    f.word(f.listOffsets[0]! + 4, 0); // Corrupt an entry after the actual first entry.
    const cell = readSourceTerrainCell(source, 1);
    assert(readSourceTerrainListEntry(source, cell.list, 0) === f.grid.triangles[0],
      "unselected cell and later list word do not become eager query dependencies");
    rejects(() => readSourceTerrainCell(source, 0), "corrupt cell rejected when selected");
    rejects(() => readSourceTerrainListEntry(source, cell.list, 1), "changed sentinel rejected when read");
  }
}

function testReachedHeaderByteDrift(): void {
  const fields = [
    { field: "originX", offset: 0x18, expected: -1000 },
    { field: "originZ", offset: 0x1c, expected: -1500 },
    { field: "rowStride", offset: 0x14, expected: 3 },
  ] as const;
  for (const changed of fields) {
    const f = fixture();
    const source = createSourceTerrainGrid(f.bytes, f.grid, 0x1c);
    // Change only source bytes. The unchanged decoded value alone cannot prove
    // this field still belongs to its original admitted source word.
    f.word(changed.offset, changed.expected + 1);
    assertSourceTerrainGrid(source);
    for (const untouched of fields) {
      if (untouched.field !== changed.field) {
        assert(readSourceTerrainHeader(source, untouched.field) === untouched.expected,
          `unread ${changed.field} byte drift does not invalidate ${untouched.field}`);
      }
    }
    rejects(() => readSourceTerrainHeader(source, changed.field),
      `reached ${changed.field} rejects byte-only drift`, "owned source word changed");
    f.word(changed.offset, changed.expected);
    assert(readSourceTerrainHeader(source, changed.field) === changed.expected,
      `${changed.field} reads its unchanged decoded owner when source bytes agree again`);
  }
}

export function runSourceTerrainGridSelfTest(): void {
  testSourceOffsetsAndOwnership();
  testTerminationAndReachedPointers();
  testHeaderDomainsAndOwnerMismatch();
  testQueryTimeOwnershipGuards();
  testReachedHeaderByteDrift();
  console.log("[source-terrain-grid] synthetic pointer, sentinel, domain, and owner checks passed");
}
