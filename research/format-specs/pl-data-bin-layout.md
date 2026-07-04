# pl####data.bin — per-borg actor data layout (GG4E)

Scope: the 432-byte `pl####data.bin` files in `user-data/GG4E/afs_data/root/` (198 files;
`plcmndata.bin` is 864 bytes and is NOT one of these records). Each file is one per-borg
actor-data record keyed by the borg id in the filename.

Status: **6 of 432 bytes are DERIVED** (proven against independent metadata with zero
exceptions in their verifiable domain). Everything else is either constant, an
unexplained float block, or a lead. Generated runtime data lives in
`packages/combat/src/data/actorDataStats.json` (emitted by
`scripts/gen-borg-actor-data-stats.mjs`, which HARD-FAILS on any cross-check mismatch).

## Verification methodology

Analysis script: `scripts/analyze-pl-data-bytes.mjs` (exhaustive column scan).

- Matrix: all 198 records × 432 bytes. Candidate encodings tested at every legal offset:
  `u8` (all 432), `u16be`/`s16be` (even offsets), `u32be`/`f32be` (4-aligned offsets).
- Ground truth (independent of the bin files):
  - `packages/assets/data/borgs.json` — 190 of the 198 records have a metadata row
    (energy cost, catalog number, "L1/L10" hp string, rarity, tribe, type, jump,
    defense/shot/attack/speed).
  - `research/symbols/NTSC_Borgs.csv` — same 190 matched by filename (adds Data
    Crystals Required and Level-up Schedule).
- Numeric proof bar: exact affine relationship `column = a*gt + b` (identity is the
  `a=1,b=0` case) across ALL matched borgs, with the ground-truth column taking >= 4
  distinct values (>= 3 for the air-jump subdomain). Integer encodings require
  near-exact equality (abs tol 1e-3); f32 columns are pre-filtered to plausible
  magnitudes (all values 0 or 1e-4..1e6) and use relative tolerance 1e-6.
- Categorical proof bar: column constant within every category AND distinct across
  categories (bijective enum), across ALL matched borgs, after case-normalizing the
  metadata labels (borgs.json mixes e.g. "Almighty Type"/"Almighty type").
- Two scan pitfalls were found and fixed during this work; both had produced false
  "exact" fits and are worth remembering:
  1. f32 reads at non-float offsets yield denormals (~1e-38); any absolute tolerance
     accepts everything. Float columns must be magnitude-filtered first.
  2. relative tolerance on u32 (~1.7e9) allows +/-1700 of slop, which "fits" unrelated
     bytes. Integer encodings must be compared near-exactly.
- `research/asset-inventory/weapon-attachment-map.json` was considered as ground truth
  for weapon-family bytes and REJECTED: it is itself a filename-heuristic evidence map
  ("This is an evidence map, not runtime binding behavior"), so nothing proven against
  it would be derived.

## PROVEN byte map

| Offset | Enc | Meaning | Verification |
| ------ | --- | ------- | ------------ |
| 0x1a0 | u8 | Borg type enum: 0=long range, 1=short range, 2=speed, 3=almighty, 4=support | Bijective vs normalized borgs.json `type` for **190/190** matched borgs, zero exceptions |
| 0x1a3 | u8 | Air-jump count | Equals N for **78/78** "Air jump level N" borgs; equals 0 for **97/97** "Boost jump" borgs; the 15 "N/A" flyers have no numeric metadata (observed: 0xff for 14, 0 for pl0f00 DEATH BORG MU) |
| 0x1a4 | u8 | Defense stat | 190/190 exact vs borgs.json (pre-existing) |
| 0x1a5 | u8 | Shot stat | 190/190 exact vs borgs.json (pre-existing) |
| 0x1a6 | u8 | Attack stat | 190/190 exact vs borgs.json (pre-existing) |
| 0x1a7 | u8 | Speed stat | 190/190 exact vs borgs.json (pre-existing) |

So 0x1a0..0x1a7 is a coherent stat/classification block (0x1a1/0x1a2 are small varying
bytes, meaning unknown).

## Negative results (searched exhaustively, NOT present)

Under all tested encodings/offsets, no exact or affine encoding exists for:

- **HP (L1 or L10)** — HP is not stored in this file. (0x0b8 f32, range 135..2000,
  looked promising but is constant per model family — see leads.)
- energy cost, catalog number, data crystals required
- rarity, tribe (tribe is implied by the id prefix / file series, not stored),
  level-up schedule
- jump category as a single clean enum (0x1a3 covers the count; the "N/A" group is
  heterogeneous)

## Leads (NOT derived — do not wire)

- **0x09f u8**: equals the air-jump level for all 78 "Air jump level N" borgs (same
  subdomain as 0x1a3), but is 4/5/6 for boost-jump borgs and 5 for "N/A" borgs.
  Possibly a total jump/boost-segment count; full-domain semantics unverified.
- **0x09e u8**: small values 0/1/2, varies within jump categories; unknown.
- **0x0b8 f32be**: 135..2000, constant per model family (Ninja 150-160, Gunman 180,
  Knight 170, Dark Knight 230...). Looks like a size/height/collision scalar, not HP.
- **0x0d8..0x0ef**: a block that is byte-identical across every borg except the
  Fortress Borg records. The categorical scan flags it as "tribe" but it is almost
  certainly a float block (camera/size?) with fortress-specific values — 19 of 20
  tribes share one value, so it encodes nothing tribe-shaped.
- **Float parameter regions** (plausible varying f32be columns, 73 total): 0x18..0x2c
  (0..18), 0x30..0x38 (0.002..0.1), 0x44..0x7c (movement-scale magnitudes, some
  negative — gravity/acceleration candidates), 0x80..0x98 (0..50000). No ground truth
  exists to prove any of them; a runtime memory-watch trace would be the way in.
- 141 of 432 byte columns are constant across all 198 files (structure padding or
  engine defaults).

## Decomp-proven runtime float fields

These fields are not proven by metadata correlation; they are proven by static runtime copy/read
sites. `FUN_800562b8` copies them from the actor-data page (`actor+0x4ac`) to runtime actor
fields, and `FUN_8000fc2c` consumes the copied camera fields in gameplay camera mode 1.

| Source offset | Enc | Runtime field | Meaning | Evidence |
| ------ | --- | ------- | ------- | ------- |
| 0x0b8 | f32be | actor+0x88c | camera target-height slot 0 | `chunk_0007.c:171`, `chunk_0001.c:1257` |
| 0x0bc | f32be | actor+0x890 | camera target-height slot 1 | `chunk_0007.c:172`, selected by actor+0x582 slot |
| 0x0c0 | f32be | actor+0x894 | camera follow min-distance slot 0 | `chunk_0007.c:173`, `FUN_8000fc2c` clamp |
| 0x0c4 | f32be | actor+0x898 | camera follow max-distance slot 0 | `chunk_0007.c:174`, `FUN_8000fc2c` clamp/init |
| 0x0c8 | f32be | actor+0x89c | camera follow min-distance slot 1 | `chunk_0007.c:175`, selected by actor+0x582 slot |
| 0x0cc | f32be | actor+0x8a0 | camera follow max-distance slot 1 | `chunk_0007.c:176`, selected by actor+0x582 slot |

## What is wired into the port

- `scripts/gen-borg-actor-data-stats.mjs` now also emits `typeCode` (0x1a0) and
  `airJump` (0x1a3) into `actorDataStats.json`, cross-checking every emitted value and
  hard-failing generation on any mismatch (current run: typeCode 190/190, airJump
  175/175 verifiable + 15 unverifiable "N/A" rows, 0 mismatches).
- `packages/combat/src/stats.ts` `rangePrefOf` now prefers the DERIVED `typeCode`
  (0 -> ranged, 1 -> melee, else stat-based mixed heuristic) over the borgs.json type
  string, which remains as fallback for borgs without an actor-data record.
- `airJump` is now consumed for the discrete mid-air-jump count in
  `packages/combat/src/stats.ts`: verifiable raw counts are used directly, while
  the "N/A" sentinel `0xff` is normalized to zero discrete air jumps. `parseJump`
  still supplies the flyer/non-flyer distinction and fallback behavior for borgs
  without actor-data records.
- `scripts/gen-movement-physics.mjs` emits the decomp-proven camera block
  (`0x0b8..0x0cc`) into `movementPhysics.json`, and `apps/game/src/sim/camera.ts`
  consumes it through `cameraParamsForBorgId` for target height and follow-distance bands.
  `defaultCameraSlotForBorgId` mirrors the static `actor+0x582` default writer
  (`FUN_8006f7c0`: slot 1 only for borg id `pl0003`, else slot 0); dynamic special-state
  rewrites of `actor+0x582` are still unported.
