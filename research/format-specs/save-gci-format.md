# Gotcha Force save format (.gci, GG4E08 "GG4E_GOTCHA_FORCE_USA")

Decoded from the Ghidra bulk-decompile corpus (`research/decomp/ghidra-export/`)
plus differential analysis of three independent save images at the repo root:

| image | comment date | notes |
|---|---|---|
| `gotcha_force_100_usa.gci` | 01/15/2025 | 100% catalog, player "Bidoof" |
| `allborgsgotcha-force.28411.gci` | 03/04/2023 | "all borgs", player "Danny" |
| `gblack-galatic-emperor-save=gotcha-force.22132.gci` | 11/17/2011 | crafted save, player "Kou", G Black + Galactic Emperor |

Inspector: `scripts/inspect-gotcha-save.mjs` (run with `tools/node/node.exe`).

Confidence tags:
- **DERIVED_ROM** — backed by decompiled game code (function cited).
- **DATA_INFERRED** — inferred from byte patterns / cross-save differentials only.
- **UNKNOWN** — not decoded.

All multi-byte values are **big-endian**.

## 1. GCI container (standard Nintendo GCX/GCI directory entry, 0x40 bytes)

`0x40`-byte GCI header, then 10 blocks x 8192 bytes = 0x14000 payload ("save
image"). File total 81984 bytes. Header fields observed: game code `GG4E`,
maker `08`, filename `GG4E_GOTCHA_FORCE_USA`, block count 10 @0x38.
All image offsets below are relative to the payload start (file offset 0x40).

## 2. Save image layout (0x14000)

The game builds the whole image in RAM and writes it in one shot (writer state
machine in `chunk_0014.c`, buffer `DAT_804362c4` sized 0x14000, memset in
`zz_008db4c_`, chunk_0013.c). **DERIVED_ROM** for all boundaries below — the
writer memcpy's each section from its live struct at these exact offsets/sizes:

| image offset | size | contents |
|---|---|---|
| 0x00000 | 0x2040 | banner header: comment + banner/icon gfx (plaintext) |
| 0x02040 | 2 | CRC of 0x0000..0x2040 |
| 0x02042 | 5 | presence flags, one byte per section 1..5 (1 = present) |
| 0x02047 | 0x14 | 20-byte keyed digest of section 2 (plaintext of it) |
| 0x0205B | 0x14 | digest of section 3 |
| 0x0206F | 0x14 | digest of section 5 |
| 0x02084 | 0x40 | **section 1** — options/system (plaintext) |
| 0x020C4 | 2 | CRC of section 1 |
| 0x020C8 | 0xABE4 | **section 2** — Gotcha Box + acquisition log (XOR-scrambled) |
| 0x0CCAC | 2 | CRC of section 2 (over the scrambled bytes) |
| 0x0CCB0 | 0x2190 | **section 3** — force + member pool + player name (scrambled) |
| 0x0EE40 | 2 | CRC of section 3 |
| 0x0EE44 | 0x4628 | **section 4** — story progress (plaintext) |
| 0x1346C | 2 | CRC of section 4 |
| 0x13470 | 0x258 | **section 5** — save metadata (scrambled) |
| 0x136C8 | 2 | CRC of section 5 |
| 0x136CA | ... | unused (zero) |

Erasing a section = writing 0xFFFF over its CRC slot (see `zz_008f1b8_`,
chunk_0014.c, the `*(iVar5 + 0x20c4) = 0xff` writes).

### 2.1 Banner header (0x0000..0x2040, plaintext)

- +0x00: comment line 1, 32 bytes ASCII — `"GOTCHA FORCE"` (loaded from disc
  offset 0xA34000 via `zz_00f19f8_`).
- +0x20: comment line 2, 32 bytes — sprintf `"%02d/%02d/%04d %02d:%02d:%02d"`
  of the save timestamp. **DERIVED_ROM** (writer, chunk_0014.c ~line 305).
- +0x40..0x2040: banner + icon pixel data. Not further decoded (UNKNOWN detail).

## 3. Integrity: CRC + keyed digest + XOR scramble

### 3.1 Section CRC — `zz_008e704_` (8008e704, chunk_0013.c) **DERIVED_ROM**

CRC-16 with polynomial 0x1021 held in bits 8..23 of a 24-bit register,
init 0; each data byte is OR-ed into bits 0..7 before 8 shift steps
(XOR 0x102100 on bit-24 overflow); result `(reg >> 8) & 0xFFFF`, stored
big-endian directly after the section. Verification runs over
section+CRC and must yield 0. Validated: **all six regions of all three
sample saves pass.**

```js
reg = 0;
for (byte of region_plus_stored_crc) {
  reg |= byte;
  for (i = 0; i < 8; i++) { reg <<= 1; if (reg & 0x1000000) reg ^= 0x102100; }
}
ok = ((reg >> 8) & 0xffff) === 0;
```

### 3.2 Keyed digest + scramble — `zz_00916c4_`/`zz_0091298_`/`zz_0091608_` (chunk_0014.c) **DERIVED_ROM**

On write, for sections 2/3/5: a 20-byte keyed digest (key strings
`BNK_KEY_...` at `PTR_s_BNK_KEY_Foinweruia5_802dad8c`, 0x13 bytes each,
one per section index) is computed over the **plaintext** section and
stored in the header (0x2047/0x205B/0x206F). Then the section is
scrambled: **every byte XOR-ed with the single constant byte
`LUT1[digest[0]] ^ LUT2[digest[1]]`** (LUTs `DAT_802daed8`/`DAT_802dafd8`,
256 bytes each, in ROM .data). The CRC is computed after scrambling.
On load the order reverses and the recomputed digest is memcmp'd.

Practical decode without ROM LUTs (used by the inspector):
- sections 2/3: unused space is zero-filled (live structs are memset at
  init, chunk_0052.c), so the XOR key = modal byte value of the section;
- section 5: bytes +0x1D..0x1F are the high bytes of the seconds field
  (always 0), so key = raw byte at +0x1D. Verified by matching the
  decoded timestamp against the plaintext comment (matches on all three).

Sections 1 and 4 are **not** scrambled and have no digest.

## 4. Section 1 — options (0x40 bytes @0x2084) — mostly UNKNOWN

Copy of `DAT_803c4ea0`. Observed nearly identical across saves
(`01020304050607 xx` repeated 4x + `020302000404040101...`) — looks like
controller/option defaults. One or two bytes differ per save. UNKNOWN detail.

## 5. Section 2 — Gotcha Box (0xABE4 bytes @0x20C8, scrambled)

Live struct `DAT_80436224` (memset 0xABE4 in chunk_0052.c:604).

| offset | size | field |
|---|---|---|
| +0x0000 | 2000 x 16 | box cell array (ends 0x7D00) |
| +0x7D00 | 1000 x 12 | acquisition log (ends 0xABE0) |
| +0xABE0 | u16 | occupied box-cell count |
| +0xABE2 | u16 | used acquisition-log record count |

**Box cell (16 bytes)** — field roles **DERIVED_ROM** from `zz_017fe18_`
(8017fe18, chunk_0045.c: cell read at `sec2 + index*0x10`) and
`zz_0066168_` (80066168, chunk_0008.c: cost = `table[id>>8][color + (id&0xFF)*6]`,
6 entries per variant = the 6 color variants):

| off | type | field | notes |
|---|---|---|---|
| +0 | u16 | borg id `(family<<8)\|variant` | 0xFFFF = empty cell; ids match `packages/assets/data/borgs.json` `pl%04x` keys — 100% hit rate on both real saves |
| +2 | u8 | color variant 0..5 (normal/alt/gold/silver/crystal/black) | with +3 this is the documented `(color<<8)\|level` u16 (behavior-notes (an) §6/(ap)) |
| +3 | u8 | level (0-based; in-game LV = value+1) | DERIVED_ROM position, 0-based-ness DATA_INFERRED (values 0..9 seen) |
| +4 | u32 | acquisition sequence number | DATA_INFERRED: every value ≤ the global counter at s5+0x50, unique-ish |
| +8 | u32 | exp | DATA_INFERRED via cross-save: same borg instance has equal acq# but growing exp/level in the newer save (Neo G Red: acq#63, exp 99/L3 → exp 214/L6) |
| +12 | u32 | unknown (0 in all observed box cells) | UNKNOWN |

The box is 2000 cells (25 pages x 80). The ROM "box full" test is
`*(short*)(sec2 + 44000) > 1999` i.e. the count at +0xABE0 (chunk_0045.c:3416).
The count fields at +0xABE0/+0xABE2 exactly match the parsed occupancy on
all three saves (230/456, 216/491, 0/0). **DATA_INFERRED** (count
semantics), **DERIVED_ROM** (offset usage).

**Acquisition log record (12 bytes)** — array position **DERIVED_ROM** from
`zz_01cee38_` (801cee38, chunk_0056.c: scans `sec2+32000` with stride 0x18,
500 iterations, two 12-byte records per iteration → exactly [0x7D00,0xABE0)):

| off | type | field |
|---|---|---|
| +0 | u16 | borg id (0xFFFF = unused record) |
| +2 | u8 | color variant (ROM collects `1 << rec[2]` bitmask per id) |
| +3 | u8 | unknown selector — ROM matches it against a value from section 4 (+0x3C region); values 0,1,3,4 observed. Possibly playthrough number. DATA_INFERRED guess |
| +4 | u32 | acquisition sequence number (≤ s5+0x50 counter) |
| +8 | u32 | unknown (0 observed) |

Purpose: appears to be the collection/duplicate log used by shop/catalog UI
("which colors of borg X do you have"). Exact in-game meaning UNKNOWN.

## 6. Section 3 — force data (0x2190 bytes @0xCCB0, scrambled)

Live struct `DAT_80436220`. Layout **DERIVED_ROM** from `zz_017fe18_`
(force at `sec3 + forceIdx*0x6C`, members via s16 indexes at +0x30 into the
pool at `sec3 + poolIdx*0x20 + 0x870`) and `zz_008f1b8_` (pool count checked
vs 199 at +0x2172):

| offset | size | field |
|---|---|---|
| +0x0000 | 20 x 0x6C | force slots (20 x 0x6C = 0x870 exactly). Only slot 0 used in all three saves — story mode has a single player force; slots 1..19 observed empty (purpose UNKNOWN — likely VS/rental force slots) |
| +0x0870 | 200 x 0x20 | force member pool: the borgs currently in your force (removed from the box). Same entry layout as a box cell, widened to 0x20 bytes |
| +0x2170 | u16 | =1 in all saves (active force index+1? flag?) UNKNOWN |
| +0x2172 | u16 | pool used count (ROM full-check vs 199) |
| +0x2174 | ~0x1C | player name, Shift-JIS, NUL-terminated (duplicate of s5+0x00) **DATA_INFERRED** (matches s5 name on all three saves) |

**Force slot (0x6C bytes):**

| off | type | field |
|---|---|---|
| +0x00 | 0x1E | force name, Shift-JIS NUL-terminated ("G RED FORCE" in the 2011 save). Bytes after the NUL are stale buffer residue. DATA_INFERRED |
| +0x1E..0x28 | | UNKNOWN (zeros observed) |
| +0x29 | u8 | battle lineup count **DERIVED_ROM** (`zz_017fe18_` loop bound) |
| +0x2A | u16 | UNKNOWN |
| +0x2C | u32 | lineup total cost (300/500/900 observed = cost of the single lineup borg) DATA_INFERRED |
| +0x30 | s16[30] | lineup: indexes into the member pool, -1 = empty **DERIVED_ROM** |

**Pool entry (0x20 bytes):** +0 u16 id, +2 u8 color, +3 u8 level, +4 u32
acquisition#, +8 u32 exp (same semantics as box cell; the exp/level
cross-save evidence above comes from pool entries), +0xC..0x11 unknown
(zeros), +0x12 u16 flag (1 seen on the borg that is in the battle lineup;
DATA_INFERRED), +0x14..0x1F zeros.

The runtime level setter `zz_005814c_` (behavior-notes (ak): u16 actor+0x3EA,
byte +0x3EC) is fed from these color/level bytes via the team-builder copy in
`zz_017fe18_` (`__s[1] byte = entry+2`, `__s byte +3 = entry+3`).

## 7. Section 4 — story progress (0x4628 bytes @0xEE44, plaintext)

Live struct `DAT_80436354`. Mostly UNKNOWN; decoded fields:

| off | type | field | confidence |
|---|---|---|---|
| +0x40 | u32 | mode selector; when ==2, lineup budget is forced to 0x898 = 2200 | **DERIVED_ROM** `zz_0181c30_` (80181c30, chunk_0045.c) |
| +0x50 | u32 | player-force-exists flag (`zz_0181c70_`) | DERIVED_ROM |
| +0x74 | u32 | 1500 / 1000 / 0 observed — max GF energy attained? | DATA_INFERRED |
| +0x78 | u32 | **GF energy** (force capacity budget): 1100 / 810 / 0 observed | **DERIVED_ROM** `zz_0181c30_` returns it as the lineup capacity |
| +0x4C | u32 | current force index (multiplied by 0x6C in `zz_017fe18_`) | DERIVED_ROM |
| +0x9EC | ptr | raw RAM pointer saved verbatim (0x8035xxxx observed) — s4 is a live-struct dump incl. pointers | DATA_INFERRED |
| +0x4520 | u16 | a borg id (0x0102/0x0207 observed) — shop/collection UI cursor, passed to `zz_01cee38_` | DERIVED_ROM (usage), meaning inferred |

Candidate playthrough counter: byte +0x06 (=7 on both completed saves, 0 on
the fresh one); +0x00..0x02 = `03 0a 1e|14` also differ. Regions +0x1B4,
+0x1F4, ... (stride 0x40) hold increasing byte lists — per-area stage/unlock
lists. All DATA_INFERRED / UNKNOWN.

Note: the crafted 2011 save has section 4 absent (presence flag 0, region
zeroed) — the game accepts saves with missing sections.

## 8. Section 5 — save metadata (0x258 bytes @0x13470, scrambled)

Live struct `DAT_803ca85c` / `&DAT_803bfe20`. Writer: chunk_0014.c ~line 300.

| off | type | field | confidence |
|---|---|---|---|
| +0x00 | ~0x1A | **player name**, Shift-JIS NUL-terminated ("Bidoof"/"Danny"/"Kou") | DATA_INFERRED (three saves; duplicated at s3+0x2174) |
| +0x1C | u32[10] | OSCalendarTime of last save: sec,min,hour,mday,mon(0-based),year,wday,yday,msec,usec | **DERIVED_ROM** (writer sprintf's the same values into the comment) |
| +0x44 | u32 | save counter (incremented every save: 346/290/8) | **DERIVED_ROM** (`*(int*)(buf+0x134b4) += 1`) |
| +0x48 | u64 | console/card identity from `zz_008e4c8_` (compared on load to detect foreign saves) | DERIVED_ROM |
| +0x50 | u32 | global acquisition counter (total gotcha pulls: 3493/3427/5); box/pool/log acq# fields never exceed it | DATA_INFERRED |
| +0x54 | u32 | UNKNOWN (0x0001FFFF / 0x0001FFFF / 0x00000041 observed) |
| +0x58 | u8[206] | per-borg color bitmask array A (bit N = color N; catalog order). 206 = catalog size | DATA_INFERRED |
| +0x126..0x157 | | zeros (padding / UNKNOWN) |
| +0x158 | u8[206] | per-borg color bitmask array B; superset of A (A = current-playthrough?, B = all-time catalog: 206/206 on both completed saves) | DATA_INFERRED |
| +0x226.. | | zeros |

The load path compares +0x1C..0x4F against the previously-loaded copy
(chunk_0014.c ~line 180) to detect save identity changes.

## 9. Special borg ids (validation)

Roster ids from `borgs.json` (`pl%04x` = `(family<<8)|variant`), 208 entries.
The starter-selection code (`zz_017fe18_`) hardcodes 0x0615 (G RED) and
0x0629 (NEO G RED): `use 0x629 if owned, else 0x615` — matching the known id
encoding. Observed per save:

| id | borg | 100% (Bidoof) | allborgs (Danny) | gblack (Kou) |
|---|---|---|---|---|
| 0x0615 | G RED | box x5, pool | box x5, pool | pool only |
| 0x0629 | NEO G RED | box x1, pool (L6, exp 214) | box x1, pool (L3, exp 99) | — |
| 0x062A | G BLACK | pool idx29 | pool idx20 | pool idx1 |
| 0x0E04 | GALACTIC EMPEROR | pool idx163 | pool idx164 | pool idx2 |

Both "100%" saves contain all four; the 2011 save contains exactly
G RED + G BLACK + GALACTIC EMPEROR in the pool with an otherwise empty box —
as advertised. Roster-id hit rate of every parsed box/pool/log entry is 100%
across all three saves.

Note: the Bidoof and Danny saves share identical acquisition numbers for
some instances (e.g. Neo G Red acq#63) and identical box prefixes — they are
clearly related lineages (one grew from the other), which is what makes the
exp/level differential meaningful.

## 10. What remains UNKNOWN

- ROM XOR LUTs / digest algorithm internals (not needed for decode; the
  digest cannot be re-generated without the ROM tables, so **edited saves
  cannot currently be re-signed** — the game will reject them even with a
  fixed CRC).
- Box cell +0x0C; log record +0x03 (playthrough?) and +0x08.
- Force slot +0x1E..0x28, +0x2A; pool entry +0x0C..0x11, +0x14..;
  purpose of force slots 1..19; s3+0x2170.
- Nearly all of section 4 (story flags, playthrough count, battle
  counters, unlocks) and section 1 (options bytes).
- s5+0x54; exact ordering of the 206-entry catalog arrays vs borg ids.
