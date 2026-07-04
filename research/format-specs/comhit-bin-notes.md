# comhit.bin — HUD-Layout Hypothesis Check (verdict: NOT HUD layout)

Date: 2026-07-02. Source inspected: `user-data/GG4E/afs_data/root/comhit.bin`
(21504 bytes, 0x5400), read-only python hex analysis in the main checkout.

## Why this file was investigated

`research/game-design/HUD-FIDELITY-PLAN.md` listed `comhit.bin` as
"combo/hit HUD layout data; schema unmapped — may encode the real meter
positions (would replace manual capture measurement)".

## Verdict

**`comhit.bin` is the global common combat hit/attack table — the shared
sibling of the per-Borg `pl####hit.bin` files — not a HUD layout schema.**
The HUD-plan hypothesis is refuted; the capture-derived measurements in
`HUD-FIDELITY-PLAN.md` remain the only layout source. No further HUD work
should target this file.

## Evidence

1. **Structure is byte-identical in kind to the known hit-table family**
   (already catalogued in `research/format-specs/hit-bin-format.md` and
   parsed by `packages/formats/src/hit-bin.ts` `parseActorHitTable()`):
   - `0x000..0x3FF`: remap area — 256 slots x 4 bytes, `0xFF`-terminated
     u8 record-index lists (248 active entries).
   - `0x400..0x53FF`: 256 records of stride **0x50** — REVISED 2026-07-03;
     the stride is proven by the DOL reader `zz_008ae60_` @0x8008ae60
     (chunk_0013.c:1439: remap `base+slot*4`, record `base+0x400+idx*0x50`).
     The earlier "83 x 0xF4 + 0xE4 tail" reading was a stride artifact;
     there is NO tail padding — 0x400 + 256*0x50 = 0x5400 exactly.

2. **Record contents share the pl####hit.bin skeleton.** Record offset
   0x08 carries the same `0xFFFF`/zero sentinel pattern seen in
   `pl0000hit.bin` (first record of both files has `ffff0000` at +0x08);
   record byte 0 clusters on the same small flag-like set (0x00 x35,
   0x41 x15, 0x43 x8, 0xC1 x6, ...).

3. **Float fields are world-unit combat values, not screen coordinates.**
   Decoding the record block as big-endian f32 yields 2108 plausible
   non-zero values in range **-3495..+4771** (samples: 190, 220, 175,
   258, -383, 417, 4771). These match hitbox radii/offsets/velocities in
   Borg world units (Borg scale ~ hundreds of units) and include large
   negatives — impossible for a 640x480 screen-layout table.

4. **Screen-coordinate test fails at chance level.** Reading the record
   block as big-endian u16: only 267 of 10126 values (2.6%) fall in
   1..640; 7055 are zero and 248 are 0xFFFF sentinels. A layout table of
   meter rects would be dominated by 0..640 x 0..480 values.

5. **Decomp cross-evidence points at combat, not HUD**
   (`research/decomp/behavior-notes.md`): the attack-formula helper
   `zz_003cd5c_(ushort* record, ...)` consumes a per-move data pointer
   into the `plxxxxhit.bin`/`comhit.bin` record space, and the low-tier
   Death Borg variants have near-empty personal `hit.bin` files — their
   attack data is expected to live in these shared `comhit*` tables.

## Remap/index area (RESOLVED 2026-07-03)

The 0x400-byte header is **256 slots x 4 bytes**, each slot a
`0xFF`-terminated list of up to 4 u8 record indices — and with the proven
0x50 stride the record area holds **256 records**, so remap values up to
247 are perfectly in range. The old "values exceed the 83 local records"
anomaly was an artifact of the wrong 0xF4 stride and is withdrawn. Slot
selection is consumer-side: `zz_008ae60_` receives the slot index as an
argument (`base+slot*4`); which gameplay event uses which slot remains
untraced.

## Field semantics status (REVISED 2026-07-03)

The 0x50 record body IS now semantically decoded — see the field table in
`hit-bin-format.md` (shapeKind, boneIndex, collisionFlags,
damageRecordIndex, activeStart/End, localOffset, halfExtent, radius; all
VERIFIED against chunk_0013.c/chunk_0004.c readers). Records are hitbox
PLACEMENTS; per-hit damage lives in the separate 0x18-stride DOL table
(`DAT_802c4760` for comhit-driven hits) — extracted to
`research/decomp/data/damage-records-802d46e0.json`. `comhit2.bin`
(0x3D40) fits neither stride model cleanly and remains EXPLICITLY OPEN.

## Consequence for the HUD plan

- Remove `comhit.bin` from the HUD "export-needed" list; it has no HUD
  role and nothing to export as an image.
- HUD meter positions stay sourced from the capture measurements table in
  `research/game-design/HUD-FIDELITY-PLAN.md` (that data is authored as
  runtime HSD/GX geometry in the DOL, not as an on-disc layout file, per
  `research/asset-inventory/ui-hud-assets.md`).

## Related finding from the same pass: mini_t.tpl is not the digit font

`mini_t.tpl` (192x104 CI8) is exported at
`apps/game/public/ui/tpl/mini_t/image_00_CI8.png` and decodes to the
**mini Gotcha Force title logo** ("mini_t" = mini title), not the chunky
HP/ammo digit sheet hypothesized in the HUD plan. The chunky yellow-green
digits in `apps/game/reference/captures/challenge-8-in-battle-hud.png`
have no matching on-disc sprite among the decodable UI exports; the HUD's
current approach (bold `ascii.tpl` block scaled and tinted `#cde23c` in
`apps/game/src/ui/bitmapText.ts` / `apps/game/src/ui/hud/BattleHud.ts`)
remains the closest real-asset source and is unchanged.
