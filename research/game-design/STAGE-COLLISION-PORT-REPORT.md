# Stage Collision Port Report

Date: 2026-07-02

## Status

PASS with runtime hardening. Exported STIH hit bins are available for real stages, `loadStage` parses them, combat receives both rectangular stage bounds and collision triangles, movement consumes those triangles for floor, lateral wall, and upward ceiling resolution, spawns now repair to supported floor, and projectiles are culled when they leave bounds or unsupported floor. Official Challenge stages are covered by an all-stage collision smoke.

## Evidence

- Original C grounding:
  - `zz_003d4a0_` relocates three stage collision grids into `DAT_8043625c +0x1c/+0x20/+0x24`
    (`research/decomp/ghidra-export/chunk_0004.c:6896`).
  - Stage collision files are selected by stage id/subtable
    (`research/decomp/ghidra-export/chunk_0004.c:10277`).
  - `FUN_8003d6e4` scans candidate triangles, computes plane Y, and returns the best floor
    under the actor (`research/decomp/ghidra-export/chunk_0004.c:6962`).
  - Actor update clamps pending X/Z to stage min/max, runs collision/floor handling, then
    commits live position (`research/decomp/ghidra-export/chunk_0004.c:8393`).
  - The rectangular in-bounds predicate checks X against `+0x3c/+0x38` and Z against
    `+0x44/+0x40` (`research/decomp/ghidra-export/chunk_0004.c:8531`).
  - Wall/ceiling handling is real but still generically named: segment collision
    `FUN_80037b98` is called when actor collision mode is enabled
    (`research/decomp/ghidra-export/chunk_0004.c:8431`), and `zz_003f320_` queries upper
    surfaces from the other collision grids (`research/decomp/ghidra-export/chunk_0004.c:8219`).
- Generated asset coverage: `apps/game/public/stages/manifest.json:6` identifies `st00`, `:7` marks it `verified-visual-and-collision`, and `:11` reports `collisionCount: 3`. The generated runtime catalog mirrors that at `apps/game/src/stages/catalog.generated.ts:16-22`.
- `st00` manifest includes copied real collision bins `collision/hit000.bin`, `collision/hit001.bin`, and `collision/hit002.bin` at `apps/game/public/stages/st00/manifest.json:93`, `:97`, and `:101`; it records the export command at `:117` and says source assets were compared against the browser public stage folder at `:123`.
- STIH format inventory says there are 54 stage hit bins, 0x38-byte records, a big-endian 42x42 grid, and `0xCCCCCCCC` triangle markers at `research/asset-inventory/hit-bin-inventory.json:63`, `:66`, `:105`, `:175`, and `:180`.
- Shared parser: `packages/formats/src/hit-bin.ts:123` parses STIH grids and `:188` derives rectangular bounds from the header.
- Runtime load path: `apps/game/src/main.ts:815` loads stage collision, `:827` calls `hitBin.parseStageHitGrid`, `:866` calls `stageBoundsFromHitGrid`, `:914` returns resources from `loadStage`, and `:1309` passes `stageBounds` plus `stageResources.collision` into `convertBattleConfig`.
- Adapter/decomp stage selector evidence: `apps/game/src/sim/adapter.ts:49-53` documents the DOL-backed stage selector bytes and `PTR_DAT_802d07a0` lookup; the decomp shows the same lookup in `research/decomp/ghidra-export/chunk_0005.c:16-24`.
- Movement consumption: `packages/combat/src/movement.ts:150-156` clamps bounds, resolves lateral/ceiling collision, blocks unsupported floor exits, and queries ground height. Grid-backed floor candidates are selected in the same file; wall and ceiling segment candidates use the same grid path.
- Spawn consumption: `packages/combat/src/battle.ts` derives a low, floor-backed spawn area from STIH floor triangles and falls back to the nearest valid floor centroid instead of unsupported center/broad-bounds positions.
- Spawn height selection is per-stage now: the low playable band is derived from each stage's own minimum floor height, and spawn queries pick the lowest supported floor in that band. This fixes elevated stages such as `st08` without placing `st00` spawns onto overhead platforms.
- Exact-spawn plumbing: `packages/combat/src/types.ts` now exposes optional
  `BattleConfig.spawnPoints[]`, and `packages/combat/src/battle.ts` honors those per-force
  points before falling back to the repaired radial spawn. This lets recovered original
  stage/slot spawn tables feed the sim without changing core deploy flow.
- Original spawn-vector read path is now identified: actor init reads
  `PTR_DAT_80433934 + slot*0x0c + 0x1604/+0x1608/+0x160c` into actor
  `+0x20/+0x24/+0x28`; if the source Y is zero, it calls `FUN_8003d6e4` to query
  the floor (`research/decomp/ghidra-export/chunk_0007.c:449`,
  `:452`, `:455`, `:479`, `:494`, `:497`, `:502`).
- Original spawn-vector writer path is partly identified:
  `zz_0186964_` copies mission/table spawn vectors from `PTR_DAT_8037f5d0` and
  `DAT_8037f8f4/+0x8/+0xc` into the same slot source fields
  (`research/decomp/ghidra-export/chunk_0046.c:1088`, `:1155`, `:1225-1228`).
  Dynamic slot-add paths also copy struct fields `+0x14/+0x18/+0x1c` into those
  offsets (`research/decomp/ghidra-export/chunk_0046.c:1643-1645`,
  `:1923-1925`).
- Spawn trace extractor: `scripts/extract-spawn-evidence.py` decodes MEM1 bins and
  Dolphin LZ4 save states, reads `*(u32*)0x80433934` / `*(u32*)0x803c4e84`,
  and dumps slot spawn-source plus live actor position evidence to
  `research/traces/GG4E/spawn-evidence.json`.
- Static spawn-table extractor: `scripts/extract-static-spawn-tables.py` reads
  `boot.dol`, follows `PTR_DAT_8037f5d0`, and writes 200 mission spawn records plus
  the 85 referenced enemy spawn rows to `research/decomp/data/static-spawn-tables.json`.
  This artifact includes exact table values such as record `0` player spawn
  `(-1000, 0, -1200)` and other-side spawn `(-1200, 0, -1000)`, matching the C writer
  offsets above.
- Respawn/camera path also consumes those same slot spawn-source vectors at
  `research/decomp/ghidra-export/chunk_0048.c:3516-3518`, with a separate
  fallback table when `PTR_DAT_80433930[0x32]` is nonzero.
- Projectile consumption: `packages/combat/src/combat.ts` now receives bounds/collision context from `Battle.step()` and drops shots outside stage bounds or over missing STIH floor before rendering can keep them alive off-map.

## Patch

Strengthened `packages/combat/src/selfcheck.ts` so the floor, wall, ceiling, disconnected-spawn, and projectile-cull checks drive the combat core directly against STIH-like collision geometry. This covers the same grid-indexed path used by imported real stage collision and prevents the known void/off-stage cases from reappearing.

Added a targeted regression for the reported enemy-walked-off-stage bug: a CPU-controlled enemy
spawns on one supported floor island, chases a player across an unsupported gap, and must remain
on its own supported floor instead of crossing/falling into the void.

## Verification

- `rtk proxy pnpm --filter @gf/combat build` passed.
- `rtk proxy node packages/combat/dist/selfcheck.js` passed; probes reported floor `y=30`, wall stopped at `x=19.75`, ceiling top capped at `y=23.75`, disconnected spawn repaired to a supported triangle, and projectile arena cull removed shots outside bounds or unsupported floor.
- The combat selfcheck also verifies a CPU enemy cannot walk off a disconnected STIH floor while
  chasing the player across an unsupported gap.
- The combat selfcheck also verifies that explicit `spawnPoints` override the radial/floor
  fallback, using trace-shaped coordinates from the active actor table path.
- `rtk proxy pnpm selfcheck:1p` passed; real `st00` collision imported with bounds `-11000..10000/-11000..10000` and `1989` triangles.
- `rtk proxy pnpm selfcheck:challenge-stages` passed; all original Challenge stage bytes with public hit bins (`st00`, `st01`, `st02`, `st03`, `st04`, `st05`, `st08`, `st0a`, `st0b`, `st0c`, `st0e`) ran 1200 frames without any borg leaving supported STIH floor.

## Remaining Gaps

- Exact original static spawn-position values are now extracted, but not safely wired into
  browser battles yet. The remaining missing link is the original mission/battle index mapping
  from `DAT_80436354 + 0x9c8` / menu selection tables to the current browser `BattleConfig`.
  The current traces are also after battle entry:
  `battle1_start_checkpoint.sav`, `mem1_t1.bin`, and `mem1_t2.bin` all decode
  `*(u32*)0x80433934 = 0x803c5420` and show zeroed spawn-source vectors for slots 0-3.
  Need a trace at `zz_0186964_` / dynamic slot-add time, or a decoded menu/mission mapping
  from `DAT_80436354 + 0x9c8`, before replacing browser defaults.
- Active actor table parsing is proven but not enough to replace defaults:
  all three extracted sources decode `*(u32*)0x803c4e84 = 0x805dbdc0`, stride `0x1e00`,
  with live slot positions at actor `+0x20/+0x24/+0x28`. Example checkpoint values are
  G RED `(4980, 0, 1079.937)`, ally `pl020a` `(4774.616, 0, 1086.596)`, and enemy slots
  `(4538.932, 132.806, 1670.764)` / `(4903.476, 0, 639.54)`. HP values in that checkpoint
  are already damaged, so this is live-position/table-path evidence, not battle-entry
  spawn default proof.
- Challenge stage variant-count selection now uses the recovered DOL table instead of the
  former literal `4`. The lookup body reads `*(u32*)(&DAT_802da5d0 + stage_id*4)`
  (`research/decomp/ghidra-export/chunk_0012.c:5777-5782`); `packages/missions/src/challenge-reference.ts`
  carries that table and preserves the `st09 = 5` entry even though official Challenge
  stage bytes all resolve to count `4`.
- Render/collision family mapping is not final. Collision-backed base stages are used where
  available, but copied stage assets such as `set*.arc` and raw `st00.pzz` members are still
  classified as copied/not decoded rather than fully rendered scene pieces.
- No active-borg "kill when offstage" rule has been proven. The recovered code points to
  clamp/contain behavior for actors and culling/flags for camera/visibility, so the browser
  should keep actors on supported floor rather than kill them after falling off.
- STIH layer suffix meanings `0/1/2` are still inferred from density/naming, not named by recovered caller code.
- Collision currently uses point/segment probes with small clearances, not a traced player capsule radius.
- Some exported visual-family stages have no source hit files in the public catalog, so runtime stage selection now prefers collision-backed base stages where available instead of using visual-only collision gaps.
