# Challenge Stage Naming + Rotation Verification (2026-07-05)

VERDICT: **WIRE** — authentic user-facing arena names exist in the game data, the full
stage-byte -> st## archive mapping is now **DOL-table-proven** (no longer trace-pending),
and the Challenge rotation extraction is verified exact vs the DOL. Name table + recipe
below. One caveat is flagged (name-row binding is corroborated, not pixel-traced) with a
cheap optional confirmation task.

All addresses are GG4E (USA) `boot.dol` at `user-data/GG4E/disc/sys/boot.dol`, decomp at
`research/decomp/ghidra-export/`. Byte values below were re-read independently from the
DOL section headers (not copied from prior JSON).

---

## 1. Verification of the existing rotation extraction

### 1.1 `scripts/extract-challenge-tables.py` — evidence chain re-checked

Re-read raw bytes from the DOL (independent parse of the 18 section headers):

| Item | Address | Re-read value | Matches extraction/JSON? |
| --- | --- | --- | --- |
| Stage rotation pool (11 bytes) | `0x8036F548` | `00 01 02 03 04 05 08 0a 0b 0c 0e` | YES (`stagePool` in `challenge-battle-tables-8036f360.json`) |
| Battle counts | `0x804356D0` | `5, 10, 15` | YES |
| Energy limits | `0x8036F554` | `1500, 2000, 2500` | YES |
| Stage variant counts | `0x802DA5D0` | `4×9, 5, 4×6` (u32[16]; index 9 = 5) | YES (`CHALLENGE_STAGE_VARIANT_COUNTS`) |

Rotation logic (`zz_0196dac_` @0x80196dac, chunk_0048.c:643-663) re-read from decomp:

- `[0x1c]` (stage byte) = `DAT_8036f548[rand % 11]`, re-rolled while equal to the
  previous battle's stage byte. Matches `selectChallengeStage()` in
  `packages/missions/src/challenge-reference.ts` (note: the port caps re-roll attempts at
  11 to keep the RNG total; the original loops unbounded — behaviorally equivalent).
- `[0x1d]` = `rand % 3` (see 1.2 — this is the **pzz family selector**, previously opaque
  "stageSubtable").
- `[0x1e]` = `rand % variantCount(stage)` via the lookup wrapper
  (`StageVariantCount_Lookup` @0x800825bc reading `DAT_802da5d0`), guarded 0 -> 1.

Caller `FUN_801969a0` @0x801969a0 (chunk_0048.c:466-506) advances only on winner mask
`([0x1f] & 1<<side) && [0x1f] <= 2` and then calls, in order:
`zz_0196dac_()` -> `zz_0042454_()` -> `zz_0042690_()` -> `zz_00437b0_(...,2)`.
These three loaders are what turns the rotation bytes into archives (1.2).

**Conclusion: the 11-stage rotation pool per run (shared by all three difficulties — the
pool is NOT per-difficulty; only battle counts/budgets/spawn pools are) is complete and
exact vs the DOL. No gaps found in the extracted values.** Never confuse it with the
13-entry pool `DAT_802c4b00` = `{00-08, 0a, 0b, 0c, 0e}` used by the title/attract-demo
stage picker (chunk_0002.c:742) — that one additionally contains st06/st07.

### 1.2 NEW: stage byte -> st## archive mapping is now table-proven (gap closed)

`research/asset-inventory/stage-code-evidence.md` and
`research/decomp/index/archive-load-xrefs.md` previously said the st## selection was
"unproven — needs runtime DVDOpen trace" (boot.dol contains zero `st##` ASCII). The trace
is no longer needed: the DOL opens AFS members **by TOC index**, and the index tables are
static in the DOL. Decoded via the AFS table of contents
(`user-data/GG4E/afs_data/sys/afs_rebuild.csv`, `index -> filename`):

**Stage model archive:** `zz_0042454_` @0x80042454 (chunk_0004.c:10299) loads AFS file
`u32 DAT_802d05c4[ [0x1d] ][ [0x1c] ]` (base `0x802d05c4`, row stride 0x48 = 18 u32).
Decoded (all 54 entries resolve to real AFS members):

| `[0x1c]` | sub 0 | sub 1 | sub 2 |
| --- | --- | --- | --- |
| 0x00-0x05 | st00-st05.pzz | st20-st25.pzz | st40-st45.pzz |
| 0x06 | st06.pzz | st06.pzz | st06.pzz |
| 0x07 | st07.pzz | st07.pzz | st07.pzz |
| 0x08 | st08.pzz | st08.pzz | st08.pzz |
| 0x09 | st09.pzz | st29.pzz | st49.pzz |
| 0x0a | st0a.pzz | st2a.pzz | st4a.pzz |
| 0x0b | st0b.pzz | st2b.pzz | st4b.pzz |
| 0x0c | st0c.pzz | st2c.pzz | st4c.pzz |
| 0x0d | st0d.pzz | st0d.pzz | st0d.pzz |
| 0x0e | st0e.pzz | st2e.pzz | st4e.pzz |
| 0x0f | st0f.pzz | st0f.pzz | st0f.pzz |
| 0x10 | st10.pzz | st10.pzz | st10.pzz |
| 0x11 | stff.pzz | stff.pzz | stff.pzz |

So **`[0x1d]` (Challenge `rand%3`) selects the st0x / st2x / st4x archive family** —
i.e. the alternate lighting/time-of-day builds of the same arena (identical pzz sizes,
different content). Only the "outdoor" arenas have families; the lair/base/sky arenas
reuse the base file in all three rows. Versus mode instead uses a **fixed** family per
stage (`[0x1d] = u16 DAT_80351828[stage]`, chunk_0044.c:353, values
`0,1,2,0,1,2,...` by stage) and always `[0x1e] = 3`.

**Set (object layout) archive:** `zz_0042690_` @0x80042690 (chunk_0005.c:18-23) loads AFS
file `u32 (PTR_DAT_802d07a0[stage*3 + sub])[ [0x1e] ]` (pointer table @0x802d07a0). All
three subs share the same per-stage list: `set{stage}00..03.arc` (stage 0x09 has 5 slots,
all `set0904.arc`; stages 0x10/0x11 are NULL). Load is **skipped when `[0x1e] == 0x10`**
— the Story/Adventure mission table uses 0x10 as its "mission provides its own set"
sentinel. This confirms `CHALLENGE_STAGE_VARIANT_COUNTS` is consumed exactly as the port
models it.

**Verification method:** `DAT_802d05c4`/`PTR_DAT_802d07a0` values were decoded as AFS TOC
indices and every one resolved to the expected filename (e.g. `st00.pzz` = index 0x1bb).
Loaders bottom out in `zz_000af84_` @0x8000af84 (index-based AFS read), which is why no
`st##` strings exist in the DOL and why the earlier RAM-string hunt
(`research/traces/GG4E/challenge-battle1-memory-evidence.md`) found nothing.

**Port fidelity gap found:** `challengeStageId()` in
`packages/missions/src/challenge-reference.ts` derives `st##` from the stage byte only and
ignores `stageSubtable`, so the port always loads the st0x family. The original picks
st2x/st4x on ~2/3 of Challenge battles for the 10 pool arenas that have families (all
pool stages except st08). Exports for st2x/st4x already exist (40 exported stage folders).

---

## 2. Authentic arena names — FOUND (with recipe)

### 2.1 Where the names live

The user-facing arena names are **texture-rendered**, not MDT text. All six MDT text
archives (`msg00`, `msg01`, `tr_msg`, `nm_msg`, `mc_msg00`, `sh_msg`) were unpacked with
`tools/NeoGF/mdttool/mdttool.py --charset USA`: they contain Story dialog / shop / name
strings only; arena names appear there solely as prose ("Sunnyside Park is safe now!").
No name<->stage table exists in any MDT.

The name list texture is in the Versus stage-select archive **`vsel00_mdl.arc`**, already
exported by the UI pipeline as
`apps/game/public/ui/hsd/vsel00_mdl/texture_016_CI4.png` — an 18-row white-on-black text
strip (rows top to bottom):

```
KOU'S HOME / NEO ELEMENTARY / SUNNYSIDE PARK / CONSTRUCTION ZONE / SERENITY STREET /
KAKERU'S HOME / RED DEATH LAIR / BLUE DEATH LAIR / THE PIT / GREATER TRICITY AREA /
SAFARITOWN MARKET PLACE / STONE RIVER / LITTLE HILL / SKY FORTRESS / MANA'S HOME /
DEATH BASE / STRATOSPHERE / ????
```

(`texture_015_CI4.png` in the same arc is the menu-verb strip — JOIN/CHOOSE/CONFIRM/... —
confirming this arc is the source of stage-select UI text.)

### 2.2 The code that binds names to stage bytes

Versus stage-select record table @**0x8035162c** (2 bytes per menu entry; 18 entries):
byte+1 is the **stage byte** — `PTR_DAT_80433934[0x1c] = DAT_8035162d[menuVal*2]`
(chunk_0044.c:352). The select-screen draw (chunk_0043.c:3049-3063) takes the same
stage byte (`cVar1`) and draws the name via id
`u16 DAT_80350158[stageByte]`. Decoded @0x80350158: `112,113,...,129` — i.e.
**name asset id = 112 + stageByte**, strictly sequential over exactly 18 stages, matching
the 18 rows of `texture_016`. The name lookup is keyed by the stage byte itself, so the
name rows are in stage-byte order.

### 2.3 Independent cross-check: Story mission table vs wiki walkthrough

(Cross-check only — Story rows are NOT Challenge evidence.) The Adventure/Story mission
entry table @**0x80358be4** (stride 0x1c; entry -> record ptr; `record[1]` = stage byte,
`record[2]` = set variant, consumed by `zz_018014c_` @0x8018014c chunk_0045.c:3174-3176)
was decoded for 90 entries and compared against the wiki walkthrough data in
`packages/assets/data/stages.json` (Fury_Hikari FAQ):

- entry 1 = 0x0c, wiki mission 1 arena "Little Hill" -> row 12 = LITTLE HILL ✔
- entry 2 = 0x05, wiki mission 2 "Kakeru's Home" -> row 5 = KAKERU'S HOME ✔
- entry 3 = 0x0e, wiki mission 3 "Mana's Home" -> row 14 = MANA'S HOME ✔
- entry 4 = 0x02, wiki mission 4 "Sunnyside Park" -> row 2 = SUNNYSIDE PARK ✔
- entries 18/19 = 0x06 (early majors), wiki M1/M4 "(Red Death Lair)" ✔; entry 29 = 0x07,
  wiki M2 "(Blue Death Lair)" ✔
- entry 24 = 0x0f, wiki M3 "(Death Base)" ✔; entry 23 = 0x0d, wiki M5 "(Sky Fortress)" ✔
- entry 22 = 0x10, wiki M7 final "(Stratosphere)" ✔; entry 21 = 0x09, wiki M6 "Greater
  Tricity Area" ✔
- "retake" arc entries cover 0x08 The Pit, 0x0a Safaritown Marketplace, 0x0b Stone River,
  0x01 Neo Elementary, 0x03 Construction Zone, 0x04 Serenity Street, 0x00 Kou's/"Your
  Home" ✔ (all consistent)

Every one of the 17 named arenas is pinned by at least one independent story/wiki match.

### 2.4 The verified stage-byte -> arena-name table

| Stage byte | Archive (sub0/1/2) | Arena name (US) | In Challenge pool? |
| --- | --- | --- | --- |
| 0x00 | st00/st20/st40 | KOU'S HOME | YES |
| 0x01 | st01/st21/st41 | NEO ELEMENTARY | YES |
| 0x02 | st02/st22/st42 | SUNNYSIDE PARK | YES |
| 0x03 | st03/st23/st43 | CONSTRUCTION ZONE | YES |
| 0x04 | st04/st24/st44 | SERENITY STREET | YES |
| 0x05 | st05/st25/st45 | KAKERU'S HOME | YES |
| 0x06 | st06 | RED DEATH LAIR | no |
| 0x07 | st07 | BLUE DEATH LAIR | no |
| 0x08 | st08 | THE PIT | YES |
| 0x09 | st09/st29/st49 | GREATER TRICITY AREA | no |
| 0x0a | st0a/st2a/st4a | SAFARITOWN MARKET PLACE | YES |
| 0x0b | st0b/st2b/st4b | STONE RIVER | YES |
| 0x0c | st0c/st2c/st4c | LITTLE HILL | YES |
| 0x0d | st0d | SKY FORTRESS | no |
| 0x0e | st0e/st2e/st4e | MANA'S HOME | YES |
| 0x0f | st0f | DEATH BASE | no |
| 0x10 | st10 | STRATOSPHERE | no |
| 0x11 | stff | ???? (literal in-game display) | no |

So the **Challenge rotation = the 11 "everyday town" arenas**; the six boss/lair/sky
arenas and the hidden stff arena are excluded — a semantically coherent pool, which is
itself a soft sanity check on the extraction.

### 2.5 Extraction recipe (repeatable)

1. `python tools/NeoGF/mdttool/mdttool.py --unpack <mdt> out --charset USA` — proves no
   text-table alternative exists (optional negative control).
2. Name strip: already exported at
   `apps/game/public/ui/hsd/vsel00_mdl/texture_016_CI4.png` (source
   `user-data/GG4E/afs_data/root/vsel00_mdl.arc`, via `scripts/export-ui-assets.mjs`).
   Rows top-to-bottom = stage bytes 0x00..0x11.
3. Binding tables (read u-values big-endian from boot.dol using its section header map):
   - `0x80350158`: u16[18] name ids = 112+stage (chunk_0043.c:3057).
   - `0x8035162c`: versus menu records, byte+1 = stage (chunk_0044.c:352).
   - `0x802d05c4`: u32[3][18] AFS index of st##.pzz per (family, stage).
   - `0x802d07a0`: ptr[18*3] -> u32 lists, AFS index of set####.arc per variant.
   - Resolve AFS indices with `user-data/GG4E/afs_data/sys/afs_rebuild.csv` (col 2 = hex
     index, col 1 = filename).
4. Story cross-check (optional): mission entries @`0x80358be4` stride 0x1c, `rec[1]` =
   stage byte, vs `packages/assets/data/stages.json`.

### 2.6 Residual caveat (why one optional check remains)

The chain "name id 112+N -> Nth row of texture_016" is inferred from id sequentiality +
row count + the story/wiki cross-matches (which pin all 17 named rows consistently). It
has not been confirmed by literally rendering the Versus select screen in Dolphin and
reading the highlighted name for a known stage byte. That 10-minute Dolphin check is the
only remaining step to upgrade the binding from "corroborated on 17/17 names" to
"pixel-traced". It does not block wiring — a mismatch would have produced at least one
story/wiki contradiction, and none exists.

---

## 3. Verdict and wiring guidance

**WIRE.**

- Add a stage-name table keyed by stage byte (source: this doc / the recipe above) — e.g.
  `STAGE_ARENA_NAMES` next to `CHALLENGE_STAGE_BYTES` in
  `packages/missions/src/challenge-reference.ts`, or in the stage catalog generator
  (`scripts/build-stage-catalog-module.mjs`, which currently emits no names). Keep the
  `st##` id as the primary key; names are display-layer.
- Names apply to ALL modes (they are the Versus stage-select strings keyed by stage
  byte), so the dev picker and Challenge HUD/results can drop the "unverified" label once
  wired. `st11`'s authentic display name is literally `????` (stff).
- Fix the family-selection fidelity gap: Challenge should map
  `stageSubtable` 0/1/2 -> st0x/st2x/st4x per the `DAT_802d05c4` table above (fallback to
  st0x where no family exists: st06, st07, st08, st0d, st0f, st10, st11); Versus uses the
  fixed per-stage family from `DAT_80351828`.
- Update stale claims: `research/asset-inventory/stage-code-evidence.md` ("0 verified
  arena-name mappings", "requires runtime archive-open tracing") and
  `research/decomp/index/archive-load-xrefs.md` ("Do not map human arena names ... until
  the trace") are superseded by the static-table proof in this doc.
