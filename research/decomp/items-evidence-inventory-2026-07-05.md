# Battle items / powerups — evidence inventory (2026-07-05)

Question: do battle items/powerups have decodable source evidence — drop tables, pickup
effects, spawn logic — sufficient to implement a minimal source-backed item runtime?

**Answer in one line: Gotcha Force has NO in-battle item/powerup pickups at all (honest
negative, evidence below) — but the game's actual "item" system, the hidden Borg GET /
Gotcha-Box drop system, is now FULLY DECODED from the DOL, its 197-row drop table is
extracted and 197/197 cross-validated against the community dataset, and it is
IMPLEMENTABLE with static evidence only.**

Everything below is corpus-quoted (`research/decomp/ghidra-export/`) or DOL-extracted
(`user-data/GG4E/disc/sys/boot.dol`, section mapping per
`scripts/scan-damage-table-bindings.mjs:10-18`). Wiki facts are labeled OBSERVED_WIKI.

---

## 1. What item assets exist

### 1a. `it####_mdl.arz` — 90 archives, per-borg weapon/attachment models, NOT battle pickups

- 90 files `it####_mdl.arz` in `user-data/GG4E/afs_data/root/` (157–175 KB each).
- **Every one of the 90 ids is a subset of the `pl####` borg roster** (verified by direct
  ls cross-check: 90/90 have a matching `pl####.pzz`). Examples: `it0006` ↔ pl0006
  FLAME NINJA, `it0615` absent but `it0613`/`it0616` present, etc.
- Content (per `research/asset-inventory/pzz-arz-inventory.json`, bucket `item`, role
  "item/attachment model ARZ"): ARZ = single pzzp/arzip LZ stream decompressing to a
  **bare HSD DAT with exactly one root `scene_data`** (e.g. it0006: 247,527 bytes, 700
  relocs, root at 0x3BBB4). These are 3D models keyed by borg id — the weapon/attachment
  geometry family (`research/asset-inventory/weapon-attachment-map.md:309` treats them as
  attachment leads for weapon-like borgs).
- **No DOL string references them** — boot.dol contains NO filename strings at all for
  `*_mdl`/`*.arz`/`*.pzz` (python string scan over the whole DOL: zero hits for
  `mdl|arz|pzz`). AFS loading is by index, so static filename→code binding is impossible;
  which runtime system attaches these models is still an open (asset-side) question.
- Correction to `behavior-notes.md` §t: it cites "`it0100_mdl.arz` for pl0100 REVOLVER
  GUNMAN" — **`it0100_mdl.arz` does not exist on disc** (the 01xx range has only
  it0102/it0104/it0108). The family claim stands; that specific example is wrong.

### 1b. Leads from the prompt that are REFUTED as item evidence

- **`comhit.bin`**: already proven to be the global common combat hit/attack table
  (shared sibling of `pl####hit.bin`; 256 records × 0x50 stride read by `zz_008ae60_`
  @0x8008ae60) — see `research/format-specs/comhit-bin-notes.md`. Not items. (The prompt's
  "83×0xF4 records" reading was the pre-2026-07-03 stride artifact, also corrected there.)
- **`as_icon.tpl`**: UI icon atlas (battle-HUD candidate per
  `research/asset-inventory/adventure-flow-ai.md`) — no item semantics.
- **`allbox.bin` / `trialbox.bin`**: force-setup/collection UI data (raw-only schema),
  not battle drops (`research/asset-inventory/ui-hud-assets.md:36`).

### 1c. Assets that DO belong to the real drop system

- `gets.pzz`, `gets00_mdl.arc`…`gets06_mdl.arc` (root): borg-acquisition cinematics —
  OBSERVED_WIKI: "`gets06_mdl.arc` is for obtaining Neo G Red"
  (`research/format-specs/re-wiki-gotcha-force.md:60`).
- Post-battle box-open presentation code confirmed in the corpus (§2d).

---

## 2. What the DOL/corpus provably contains — the Borg GET drop system, fully decoded

The only "drop" mechanic in the battle loop is invisible accrual on kill + post-battle
Gotcha-Box rolls. Chain of custody, all addresses verified this session:

### 2a. Kill-site registration (spawn site of "drops")

`resolve_hitbox_target_effects_and_damage`'s kill branch, right after the kill-event
accounting call `zz_002f8dc_` (`chunk_0003.c:8054-8076`):

- Adventure mode (`PTR_DAT_80433930[0x32] == 0`), cross-team kill by a scoring actor:
  `zz_018214c_(victim_u16_+0x3ea /*borgId*/, victim_byte_+0x3ed /*colorVariant*/)`
  (`chunk_0003.c:8066`). If the victim has an attached co-unit (`+0x4a0 == 1`), the
  co-unit at `+0x4a4` is registered too (`chunk_0003.c:8067-8070`).
- **Special case** (`chunk_0003.c:8061-8064`): victim borgId `0x503` (pl0503 CYBER DEATH
  DRAGON, a fusion with no GET row) instead registers **0x505 (DEATH HEAD) and 0x506
  (CYBER DRAGON)** — its two fusion components.
- Challenge mode (`[0x32] == 1`): no GET accrual; instead `zz_0006c24_` @0x80006c24
  (`chunk_0000.c:1290-1308`) appends the victim borgId to a per-killer-player log at
  matchState `+0x17f8[player]` (cap 0x1000 entries).
- Color variant byte `+0x3ed` semantics corroborated by `behavior-notes.md` §(am).6:
  variants 0=normal, 1=alt color, 2=gold, 3=silver, 4=crystal, 5=black.

### 2b. Accrual — `zz_018214c_` @0x8018214c (`chunk_0045.c:4727-4762`)

- Pool: `DAT_80436354 + 0x1518`, up to **1536** packed u32 entries, count at `+0x2d18`,
  each stored XOR `0xFFFFFFFF` (light obfuscation):
  `variant<<28 | borgId<<16 | points(low 16)`.
- Lookup by exact (variant, borgId) high half; appends a new entry if absent.
- Increment per kill: `(rng8() & 0xF) + 1` = **random 1..16 points** via the global 8-bit
  RNG `zz_00055fc_` @0x800055fc (`chunk_0000.c:373-386`: state DAT_804360c6/c7,
  `next = (((hi<<8|lo)*3)>>8)&0xFF` family). Saturates below 0x10000.
- Matches OBSERVED_WIKI exactly: "GET counter increments by a random value between 1 and
  16" (`re-wiki-gotcha-force.md:66`).

### 2c. Revert-on-abandon — `zz_01820d4_` @0x801820d4 / `zz_0182110_` @0x80182110 (`chunk_0045.c:4703-4723`)

Backup/restore of the whole pool (0x1800 bytes + count) to `+0x2d1c`/`+0x451c`. Matches
OBSERVED_WIKI "Abandoning or losing a battle reverts all counters to their pre-battle
states" (`re-wiki-gotcha-force.md:69`).

### 2d. Drop roll + drop table — `zz_0182228_` @0x80182228 (`chunk_0045.c:4766-4817`)

Scans the pool in insertion order against the **DOL drop table `DAT_8035b2dc`**
(VA 0x8035b2dc, boot.dol file offset **0x3582dc**): rows of **8 big-endian s16**
(16 bytes), terminated by a negative first short —

| short | meaning |
|---|---|
| [0] | borgId (matches pool entry's 12-bit id field) |
| [1] | partsKind: 1 = whole-unit drop; 2..5 = borg is split into N collectible parts; row absent = borg never drops |
| [2..7] | GET threshold per color variant 0..5 (normal, alt, gold, silver, crystal, black); −1 = that variant can never drop |

Roll semantics (line-exact): entry qualifies when `points >= threshold[variant]`
(`chunk_0045.c:4792`); on success the entry's points are **reset to 0**
(`:4793-4794` — keeps variant+id, clears low 16), and the function outputs
`(borgId, variant, partIndex)` where partsKind==1 → partIndex=0 ("UNIT GET") and
partsKind N>1 → partIndex = `(rng8()>>4) mod N + 1` ("PARTS GET", a random one of the
N parts, `:4806-4810`). One drop per call; the caller loops.

**Extracted table: 197 rows** (pl0000..pl0f06). Full dump reproduced this session
(python, section-map pattern from `scripts/scan-damage-table-bindings.mjs`).
Validation:

- **197/197 rows byte-exact against the community dataset**
  `research/symbols/eu_borgs_GET_values.csv` (all 6 threshold columns; the CSV's
  Normal/Another Color/Gold/Silver/Crystal/Black headers confirm the variant order;
  the table is region-identical EU↔NTSC-U).
- The CSV does NOT have the partsKind column — that is **new DERIVED data**:
  107 borgs kind=1, 44 kind=2, 25 kind=3, 17 kind=4, 4 kind=5
  (pl0504 COSMIC DRAGON, pl0505 DEATH HEAD, pl0506 CYBER DRAGON, pl0e04).
- OBSERVED_WIKI cross-checks: "Gold Death Borg: 40" → death-borg rows (pl0f00-0f06)
  thresholds (400,600,**40**,28,24,36), gold = column 2 ✓. "Galactic Emperor: −1
  special case" → pl0e04 is the **only** row with all thresholds −1 (kind=5,
  registered but permanently undroppable) ✓. "No-GET borgs: Cyber Death Dragon,
  Machine Dragon, G Red" → exactly pl0503/pl0507, pl050f/pl0513, pl0615 have no row
  (the other row-less ids are the story/DLC-tier pl0602/060a/060c/060e Cyber Machines,
  pl0629 NEO G RED, pl062a G BLACK; 208-roster − 197 rows = 11) ✓.

### 2e. Post-battle consumer (where "drops" become boxes)

- `FUN_80180598` @0x80180598 (`chunk_0045.c:3325-3419+`) — the post-battle GETS screen
  state machine: state 1 calls `zz_0182228_(out DAT_80436354+0x4520 borgId, +0x4522
  variant, +0x4523 partIndex)`; on success states 2–3 run the box/cinematic
  presentation (`zz_0182648_(partIndex)`, `zz_01ce174_(...)`), then loops back for the
  next drop; when the roll returns 0 it proceeds to exit states.
- Box-open UI `FUN_801ce5ec` @0x801ce5ec (`chunk_0056.c:1733-1900`) formats the debug
  strings — DOL strings located and mapped this session (file offset → VA → referencing
  code at 0x801ce970/998/9c8, inside FUN_801ce5ec):
  - `"UNIT GET !! : %04X %d"` @0x802b36c8 (type byte 0)
  - `"PARTS GET !! : %04X %d %d"` @0x802b36e0 (type 1: borgId, variant, partIndex)
  - `"PARTS GOUSEI !! : %04X %d %d"` @0x802b36fc (type 2: assembling collected parts
    into the unit — the parts-completion path)
  - `"G_RED POWER UP !!"` @0x802b371c (type 3: story G-Red upgrade presentation)
- Collection hand-off: `zz_01e053c_`/`zz_01e05dc_` @0x801e053c/0x801e05dc
  (`chunk_0058.c:3781-3823`) spawn the GET-popup UI widgets; the actual collection
  store update goes through `zz_01cee38_` (called from FUN_80180598 case 10 with
  collection caps gate `*(short*)(DAT_80436220+0x2172) > 199 && *(short*)(DAT_80436224+
  0xABE0) > 1999`) — **not yet decoded** (see §4).

### 2f. Honest negative: NO in-battle pickups exist

- boot.dol full ASCII-string scan: zero item/pickup/capsule/crystal/health strings; the
  only reward strings are the four §2e strings (plus `BOX_KEY_AoIUcoijWbi`, an unrelated
  key constant).
- The kill path's complete side-effect list (chunk_0003.c:7834-8330, decoded across
  results-scoring-decode-2026-07-04.md + this session): scoring counters, team score
  +100, GET accrual (§2a), challenge kill-log, death FX/state — **no entity spawn for a
  collectible, no walk-over grant handler anywhere in the chain**.
- `zz_0182228_`'s pool is the ONLY reader of the accrued points, and it runs post-battle.
  In-battle the accrual is invisible — consistent with 20+ years of player-facing wiki
  describing GET counters as hidden.
- Conclusion: the port "models NO items" is not a gap in battle simulation — **the game
  has no battle items**. The real gap was the GET/drop meta-system, which is now decoded.

---

## 3. VERDICT: IMPLEMENTABLE (static evidence only)

Minimal source-backed item runtime = the Borg GET drop pipeline. Pieces + evidence:

1. **Drop table data** — extract `DAT_8035b2dc` (197 × 8 s16) from boot.dol
   → `packages/combat/src/data/borgGetDropTable.json` (DERIVED). Evidence: §2d.
2. **Per-(borgId,colorVariant) points pool** (cap 1536 entries, points cap 0xFFFF)
   on the adventure/meta state. Evidence: §2b pool layout.
3. **Kill hook** (adventure battles only): on cross-team kill of a scoring actor, add
   `rand1..16` points for (victimBorgId, victimVariant); credit attached co-unit too;
   special-case CYBER DEATH DRAGON → DEATH HEAD + CYBER DRAGON. Evidence: §2a.
   (The port's kill accounting `packages/combat/src/battle.ts` accountPendingDefeats is
   the natural hook point — same event as zz_002f8dc_.)
4. **Snapshot/restore**: snapshot pool at battle start; restore on lose/abandon; keep on
   win. Evidence: §2c.
5. **Post-battle roll loop**: repeatedly take the first pool entry (insertion order)
   with points ≥ threshold[variant]; reset its points to 0; emit UNIT (kind 1) or a
   random part 1..N (kind 2..5); stop when no entry qualifies. Evidence: §2d.
6. **RNG**: ROM uses the global 8-bit RNG (§2b). For 1:1 parity port `zz_00055fc_`
   verbatim (`(( (hi<<8|lo) *3 )>>8)` byte generator, seeds DAT_804360c6/c7); otherwise
   document as the port's RNG with identical ranges (1..16, part 1..N uniform-ish via
   `(r>>4) mod N`).

### Extraction script sketch (do NOT write runtime code yet)

`scripts/extract-borg-get-drop-table.mjs`:

```
read boot.dol; build 18-section offset/address/size map        // scan-damage-table-bindings.mjs:10-18
off = vaToOffset(0x8035b2dc)                                   // = 0x3582dc
rows = []; while (s16BE(row[0]) >= 0) rows.push(8 x s16BE)     // 197 rows expected
emit packages/combat/src/data/borgGetDropTable.json:
  { source: "boot.dol@0x8035b2dc", rows: [{ borgId: "pl%04x", partsCount,
    thresholds: { normal, altColor, gold, silver, crystal, black } }],
    killCredits: { pl0503: ["pl0505","pl0506"] },              // chunk_0003.c:8061-8064
    pointsPerKill: { min: 1, max: 16 },                        // chunk_0045.c:4754-4757
    poolCap: 1536, pointsCap: 65535 }
assert: 197 rows; thresholds equal research/symbols/eu_borgs_GET_values.csv 197/197
```

---

## 4. What remains missing (deferred, with next traces)

- **Parts-completion / GOUSEI check + collection persistence**: which store counts owned
  parts, and where "all N parts collected → assemble unit" is decided. Candidate:
  `zz_01cee38_` and the `DAT_80436220`/`DAT_80436224` collection blocks
  (FUN_80180598 case 10). Next trace: static read of zz_01cee38_ + the DAT_80436220
  struct writers; save-side counterpart in the GCI datamine (§(aq) behavior-notes).
- **GET-pool save persistence layout** (counters persist across sessions per wiki;
  GCI field unknown).
- **`it####_mdl.arz` runtime binding** — which loader attaches the per-borg item model
  (asset-pipeline question, orthogonal to drops; AFS index-based loads defeat static
  string binding).
- **Presentation fidelity** (gets## cinematic selection by `zz_0182648_(partIndex)`,
  box models) — UI work, not required for a correct drop runtime.

## 5. Corrections to earlier notes made here

- behavior-notes §t's `it0100_mdl.arz` example file does not exist (§1a).
- The prompt's "comhit ties to zz_003cd5c_ / 83×0xF4" framing is superseded by
  comhit-bin-notes.md's 256×0x50 reader-proven layout (§1b).
