# Hit BIN Format Notes

Generated from `scripts/inspect-hit-bins.mjs` against `user-data/GG4E/afs_data/root` on 2026-06-30.
Actor/common table sections REVISED 2026-07-03: the record stride is **0x50**, proven by the
DOL spawner indexing (`record = base + idx*0x50`, chunk_0013.c `zz_008ab30_` @0x8008ab30:1297,
`zz_008ac80_` @0x8008ac80:1349, `zz_008ae60_` @0x8008ae60:1439). The former 0xF4 model was a
size coincidence (`32*0xF4 + 0x20 == 0x20 + 32*0x50 + 0x80 + 64*0x50 == 0x1EA0`).

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
| `pl####hit.bin` | 210 | no ASCII magic | two sections: 32-byte remap A + 32 x 0x50 body hurtboxes; 0x80 remap B + 64 x 0x50 attack hitboxes | Per-Borg hitbox tables |
| `comhit2.bin` | 1 | no ASCII magic | 0x3D40 — layout EXPLICITLY OPEN (fits neither 0xF4 nor 0x50 cleanly; no DOL reader found) | Secondary common hit table |
| `comhit.bin` | 1 | no ASCII magic | 0x400 remap (256 x 4-byte slots) plus 256 x 0x50 records, no tail | Global common hitbox table |

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

## Actor/Common Hit Tables (VERIFIED 0x50 layout, 2026-07-03)

The record stride is `0x50`, and the tables are hitbox-PLACEMENT records; per-hit damage
values live in separate 0x18-stride tables in the DOL (borg family: 9 records at
`0x802d46e0`, bound via `actor+0x27c` by `zz_0072048_` @0x80072048; extracted to
`research/decomp/data/damage-records-802d46e0.json`).

`pl####hit.bin` (fixed 0x1EA0 = 7840 bytes; also the per-slot stride of the loaded table
pages: `actor+0x3fc = *(PTR_DAT_80433934+0x9c) + slot*0x1EA0`, chunk_0006.c:7126):

- `0x000..0x01f`: remap A — 32 x u8 record indices (`0xff` = empty). Consumed by
  `zz_008ab30_` (record = `base + remapByte*0x50 + 0x20`).
- `0x020..0xA1f`: 32 x `0x50` records — persistent BODY HURTBOXES (`activeEnd = -1`).
- `0xA20..0xA9f`: remap B — 32 slots x 4 bytes, each slot a `0xff`-terminated list of up
  to 4 u8 record indices. Consumed by `zz_008ac80_` (child/projectile hitboxes, slot
  selected by spawner `kind` arg: `base+0xa20+kind*4`).
- `0xAA0..0x1E9f`: 64 x `0x50` records — attack/child-object hitboxes with authored
  active-frame windows.

`comhit.bin` (0x5400, no tail padding):

- `0x000..0x3ff`: remap — 256 slots x 4 bytes, `0xff`-terminated u8 lists. Consumed by
  `zz_008ae60_` via `*(PTR_DAT_80433934+0x98)` (`base+slot*4`).
- `0x400..0x53ff`: 256 x `0x50` records. This resolves the old "remap values up to 247
  exceed 83 records" anomaly — there are 256 record slots, not 83.

`comhit2.bin` (0x3D40): layout EXPLICITLY OPEN. It fits neither the refuted 0xF4 model nor
the 0x50 two-section model cleanly, and no DOL reader indexing it has been identified.

0x50 record fields (VERIFIED against chunk_0013.c `FUN_8008a65c` :1121 and chunk_0004.c
`FUN_8003c8b4` :6481):

| Offset | Type | Name | Meaning |
| ---: | --- | --- | --- |
| `0x00` | u8 | shapeKind | hitbox shape dispatch (`PTR_FUN_802da740`/`802da758`) |
| `0x01` | u8 | boneIndex | bit `0x80` = actor root matrix (`+0x1aa4`), else `actor+0x8d4+bone*0x30`; checked vs destroyed-parts mask `+0x76c` |
| `0x02` | u16 | collisionFlags | collision-list flags (`zz_008a2bc_` chunk_0013.c:973; bit `0x40` = attack list gated by i-frames `+0x720 <= 0`) |
| `0x04` | u16 | damageRecordIndex | index into the 0x18-stride DOL damage table at `actor+0x27c` |
| `0x06` | s16 | activeStart | borgs: anim-frame threshold vs `actor+0x1cdc`; non-borgs: countdown |
| `0x08` | s16 | activeEnd | `-1` = persistent (body hurtboxes) |
| `0x0c` | f32[3] | localOffset | transformed by the attach matrix |
| `0x18` | f32[3] | halfExtent | capsule endpoints = offset ± this |
| `0x24` | f32 | radius | scaled by actor scale (`+0xc0`) |
| `0x28..0x4f` | — | (zero in sampled borg records) | other shape kinds may use them |

## Shared Parser

`packages/formats/src/hit-bin.ts` implements the reusable runtime/shared parser:

- `parseStageHitGrid()` parses STIH headers, cells, record references, and 0x38 triangle records.
- `stageBoundsFromHitGrid()` returns the decoded STIH arena rectangle.
- `parseActorHitTable()` parses `pl####hit.bin` (two 0x50-record sections) and `comhit.bin` (one section) with the VERIFIED field names above; `comhit2.bin` returns an explicit `valid: false` zero-section result.

`scripts/inspect-hit-bins.mjs` implements the research inventory scanner:

- Validates `STIH` headers and declared file sizes.
- Parses STIH grid dimensions, bounds, cell offset spans, record references, and 0x38 triangle records.
- Validates record markers, normal lengths, record ref alignment, and record-section divisibility.
- Classifies `hitSSN.bin` by stage code and layer suffix.
- Parses `pl####hit.bin` and `comhit.bin` as remap slots plus decoded 0x50 records; reports `comhit2.bin` as explicitly open.
- Emits per-file categories, counts, sample records, unknowns, and cross-references to existing stage/effects inventories.

Run:

```bash
rtk node scripts/inspect-hit-bins.mjs
```

## Still Unknown

- Semantic name of STIH header word `0x20`.
- Why STIH cell entries 0 and 1 point into the last two words of the offset table.
- Exact gameplay meaning of stage layer suffixes `0`, `1`, and `2`.
- `comhit2.bin` (0x3D40) layout — EXPLICITLY OPEN, no DOL reader identified.
- Record bytes `+0x28..+0x4f` for non-capsule shape kinds.
- The consumer-side mapping from attack remap slot (`kind` arg of `zz_008ac80_`) / comhit
  slot to specific moves/effects.
