# Hit BIN Format Notes

Generated from `scripts/inspect-hit-bins.mjs` against `user-data/GG4E/afs_data/root` on 2026-06-30.

The scan covers:

- Stage collision grids: `hit*.bin`, specifically `hitSS0.bin`, `hitSS1.bin`, `hitSS2.bin`.
- Common hit tables: `comhit.bin`, `comhit2.bin`.
- Per-Borg hit tables: `pl####hit.bin`.

The machine-readable inventory is `research/asset-inventory/hit-bin-inventory.json`.

## Conventions

- Multi-byte values observed here are big-endian.
- Stage coordinates are in the same broad world-unit scale as exported stage geometry.
- `0xffffffff` is used heavily as a sentinel or empty marker.
- Unknown names below are intentionally conservative; the scanner validates layout and record sizes, but not gameplay semantics.

## File Families

| Family | Files scanned | Header or magic | Dimensions | Category |
| --- | ---: | --- | --- | --- |
| Stage `STIH` grids | 54 | ASCII `STIH` at `0x00` | 42 x 42 cells, 500 x 500 units, 0x38-byte triangle records | Stage spatial collision |
| `pl####hit.bin` | 210 | no ASCII magic | 0x20-byte remap header plus 32 x 0xF4-byte records | Per-Borg hit/action table |
| `comhit2.bin` | 1 | no ASCII magic | 0x20-byte remap header plus 64 complete x 0xF4-byte records, then 0x20 zero tail bytes | Secondary common hit table |
| `comhit.bin` | 1 | no ASCII magic | 0x400-byte remap/index area plus 83 complete x 0xF4-byte records, then 0xE4 zero tail bytes | Global common hit table |

## Stage STIH Grid

All scanned stage files use the same header dimensions:

- `cellSizeX = 500`
- `cellSizeZ = 500`
- `gridCellsX = 42`
- `gridCellsZ = 42`
- `originX = -11000`
- `originZ = -11000`
- inferred X/Z bounds: `-11000..10000`, `-11000..10000`

Header:

| Offset | Type | Name | Observed meaning |
| ---: | --- | --- | --- |
| `0x00` | char[4] | magic | `STIH` |
| `0x04` | u32 | declaredBytes | equals file size |
| `0x08` | u32 | cellSizeX | 500 |
| `0x0c` | u32 | cellSizeZ | 500 |
| `0x10` | u32 | gridCellsX | 42 |
| `0x14` | u32 | gridCellsZ | 42 |
| `0x18` | s32 | originX | -11000 |
| `0x1c` | s32 | originZ | -11000 |
| `0x20` | u32 | unknown20 | always `0x20` in scanned files |
| `0x24` | u32 | recordSentinelOffset | followed by two `0xffffffff` words; records start at `recordSentinelOffset + 8` |
| `0x28` | u32[] | cellOffsetTable | 1764 monotonic offsets for cell spans |

Cell references:

- The offset table has 1764 entries, one per 42 x 42 cell.
- Consecutive entries define a per-cell span; the last span ends at `recordSentinelOffset`.
- Non-`0xffffffff` span values are byte offsets relative to the record block.
- Valid references are multiples of `0x38` and less than the record-section byte length.
- Entries 0 and 1 point 8 and 4 bytes before the nominal end of the offset table in every scanned file. The scanner reports these as anomalous spans and ignores their invalid words when validating the rest of the file.

Stage collision record, size `0x38`:

| Offset | Type | Name | Observed meaning |
| ---: | --- | --- | --- |
| `0x00` | u32 | marker | always `0xcccccccc` in scanned records |
| `0x04` | f32[3] | vertex0 | triangle vertex |
| `0x10` | f32[3] | vertex1 | triangle vertex |
| `0x1c` | f32[3] | vertex2 | triangle vertex |
| `0x28` | f32[3] | normal | unit-length plane normal |
| `0x34` | f32 | planeD candidate | plane distance or related scalar |

Layer categories:

| Suffix | Files | Total records | Total cell refs | Probable role |
| --- | ---: | ---: | ---: | --- |
| `0` | 18 | 21325 | 97356 | Primary stage collision candidate |
| `1` | 18 | 19396 | 34476 | Secondary/detail or vertical collision candidate |
| `2` | 18 | 1625 | 4579 | Sparse/special collision candidate |

The layer names are not proven by code yet; they are density and naming-based labels.

## Actor/Common Hit Tables

`pl####hit.bin` files are fixed at 7840 bytes:

- `0x00..0x1f`: 32 remap/order bytes. `0xff` means empty.
- `0x20..EOF`: 32 records x `0xf4` bytes.
- Active remap byte counts range from 2 to 25 across the 210 player files.

`comhit2.bin`:

- `0x00..0x1f`: 32 remap/order bytes; 3 non-`0xff` values observed.
- `0x20..0x3d1f`: 64 complete `0xf4` records.
- `0x3d20..0x3d3f`: zero tail/padding.

`comhit.bin`:

- `0x000..0x3ff`: 0x400-byte remap/index area; 248 non-`0xff` bytes observed.
- `0x400..0x531b`: 83 complete `0xf4` records.
- `0x531c..0x53ff`: zero tail/padding.

0xF4 record skeleton:

| Offset | Type | Status |
| ---: | --- | --- |
| `0x00` | u32 or u8[4] | packed flags/IDs candidate |
| `0x04` | u32 | often zero, not proven |
| `0x08` | u32 or u16[2] | often `0xffff0000` |
| `0x0c` | u32/f32 | mixed/unknown |
| `0x10..` | mixed f32/u32 | many values decode as plausible offsets, radii, or dimensions |

The actor/common record body is not semantically decoded yet. Treat it as a fixed-size record with named raw fields until gameplay code or traces identify actions, bones, hitbox shapes, damage, effect IDs, and timing.

## Shared Parser

`packages/formats/src/hit-bin.ts` implements the reusable runtime/shared parser:

- `parseStageHitGrid()` parses STIH headers, cells, record references, and 0x38 triangle records.
- `stageBoundsFromHitGrid()` returns the decoded STIH arena rectangle.
- `parseActorHitTable()` parses `pl####hit.bin`, `comhit.bin`, and `comhit2.bin` remap/index headers plus raw 0xF4 records without assigning unproven gameplay field names.

`scripts/inspect-hit-bins.mjs` implements the research inventory scanner:

- Validates `STIH` headers and declared file sizes.
- Parses STIH grid dimensions, bounds, cell offset spans, record references, and 0x38 triangle records.
- Validates record markers, normal lengths, record ref alignment, and record-section divisibility.
- Classifies `hitSSN.bin` by stage code and layer suffix.
- Parses `pl####hit.bin`, `comhit.bin`, and `comhit2.bin` as remap headers plus 0xF4 records.
- Emits per-file categories, counts, sample records, unknowns, and cross-references to existing stage/effects inventories.

Run:

```bash
rtk node scripts/inspect-hit-bins.mjs
```

## Still Unknown

- Semantic name of STIH header word `0x20`.
- Why STIH cell entries 0 and 1 point into the last two words of the offset table.
- Exact gameplay meaning of stage layer suffixes `0`, `1`, and `2`.
- Actor/common 0xF4 field meanings: flags, action IDs, damage, hitbox shape, bone/attachment IDs, effect IDs, and timing.
- The input index space for `comhit.bin`'s 0x400-byte remap/index area.
