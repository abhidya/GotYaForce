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
   - `0x000..0x3FF`: remap/index area (0xFF = empty; 248 non-0xFF bytes).
   - `0x400..0x531B`: 83 complete records of stride **0xF4** — the exact
     record size of `pl####hit.bin` (32 records) and `comhit2.bin` (64).
   - `0x531C..0x53FF`: verified all-zero tail padding.

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

## Remap/index area observation (unproven, recorded honestly)

The 0x400-byte header reads naturally as **256 slots x 4 bytes**, each
slot holding up to 4 record-index-like bytes packed from the left with
0xFF padding, e.g. the first slots: `[00 8c][01][02 03][04][05]...` —
mostly ascending single entries with occasional multi-entry slots. The
values span 0..247, which **exceeds the 83 local records**, so either the
index space spans more than this file (83 + comhit2's 64 = 147 still does
not cover 247) or the bytes are not plain record indices. The slot key
space (0..255) is consistent with the per-Borg-`number` keying lead noted
in `behavior-notes.md` (BetaIII(80)->29, Gamma(81)->30, DeltaII(84)->31),
but that lead resolved only 3 of 8 tested Borgs. **No schema is asserted
here beyond the slot layout observation.**

## Field semantics status

Unchanged from `hit-bin-format.md`: the 0xF4 record body is still not
semantically decoded (flags, action IDs, damage, hitbox shape, bone IDs,
effect IDs, timing all unknown). Nothing in this pass identified — or
fabricated — field meanings.

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
