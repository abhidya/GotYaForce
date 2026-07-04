# ptcl00.txg cell map — battle-FX identification

Source: `user-data/GG4E/afs_data/root/ptcl00.txg` (8-entry shared particle image
container), canonical export via HSDRaw GXImageConverter to
`apps/game/public/ui/txg/ptcl00/image_*.png`
(see `ptcl00-txg-export-results.json`). Plus the shared effect atlas
`efct00.tpl#0` (`apps/game/public/fx/efct00_atlas.png`, 256x64 RGB5A3).

## Identification method and confidence

UPDATE 2026-07-04: the hit-impact effect SELECTION chain IS now decoded
(damage record impactEffectId -> effect-def table 0x802c7ed0 -> variant
handlers with per-layer texIds/lifetimes/keyframe tracks — see
`research/decomp/impact-effect-id-decode-2026-07-04.md`), but its texIds
index the particle-DEFINITION bank (`ptcl00.ptl` entries, values up to 146),
not the 8-cell txg directly, and `ptcl00.ptl`/`ptcl00.ref` remain unparsed —
so the final texId -> txg-cell hop, and therefore every effect->cell
assignment below, is still **TUNED-visual**: identified by inspecting the
decoded pixels (upscaled) and cross-referencing
`particle-effect-inventory.json` family counts and
`weapons-effects-projectiles.md` (which confirm muzzle / impact-explosion /
fire / beam / trail as the dominant shared particle families, and confirm
ptcl00.* as the only direct shared particle files). The *pixels* are real
extracted assets; the *mapping* of effect to cell is visual.

Format notes:

- **RGB565** cells have no alpha: black = transparent, must be drawn with
  additive blending (matches GX additive particle blending).
- **I4/I8** cells are intensity masks exported as white RGB + alpha=intensity.
- Cells #2, #5, #6 are **mirror-wrap quadrants**: the stored image is one
  quadrant of a radially symmetric sprite with the bright centre at the
  image's top-right corner. The full sprite is reconstructed by sampling with
  mirrored wrap (GX `WRAP_MIRROR`); in three.js:
  `wrapS = wrapT = MirroredRepeatWrapping; repeat.set(2, 2)` maps the bright
  corner (uv 1,1) to the sprite centre. Rendering these quadrants unmirrored
  (as the pre-export code did) shows an off-centre corner gradient — the
  giveaway that they are quadrants.

## Cell map

| Cell | File | Size / fmt | Appearance (decoded) | Identified as | Wired to | Confidence |
|---|---|---|---|---|---|---|
| #0 | `image_00_I4.png` | 32x32 I4 | Wispy white star/burst with ragged radial arms | **Dash/boost burst** — the white star flash seen in battle captures on boost dashes | `spawnDashBurst` (edge-triggered on dash slot entry) | Medium (TUNED-visual) |
| #1 | `image_01_RGB565.png` | 32x32 RGB565 | Orange/red fireball, white-yellow hot centre | **Explosion / flame core** | Flame projectiles + death-explosion core | High (unmistakably a fireball) |
| #2 | `image_02_RGB565.png` | 16x16 RGB565, quadrant | Black -> red -> orange -> white corner gradient | **Hit spark / hot ember flash** (mirrored: radial white-hot flash) | `spawnHitSpark` (edge-triggered on hit state) | Medium-High (TUNED-visual) |
| #3 | `image_03_I8.png` | 32x32 I8 | Nearly full-intensity quad with one soft rounded-off corner arc | Unidentified — possibly a rounded-square blob/shadow quadrant or falloff ramp | **Not wired** (no confident reading) | Low |
| #4 | `image_04_I8.png` | 16x16 I8 | Soft diagonal white streak/comet | Spark streak / speed-line / trail particle | **Not wired yet** (candidate for dash trails) | Medium (TUNED-visual) |
| #5 | `image_05_RGB565.png` | 16x16 RGB565, quadrant | Black -> indigo -> violet -> white corner gradient | **Energy shot glow** (mirrored: radial blue-violet energy dot) | Energy projectiles | Medium-High (TUNED-visual; matches beam/energy family colors) |
| #6 | `image_06_RGB565.png` | 32x32 RGB565, quadrant | Orange/white rays fanning out of the corner with dark spokes | **Muzzle flash** (mirrored: full ray starburst) | Muzzle-kind projectiles + `spawnMuzzleFlash` on shoot entry | High (classic ray-burst muzzle sprite) |
| #7 | `image_07_RGB565.png` | 64x64 RGB565 | Large magenta/pink spiral galaxy glow, white core | **Charge glow / energy aura** | Charge-shot glow (`syncChargeGlow`, driven by `cooldowns["chargeFrames"]`), spun in the view plane | Medium (TUNED-visual; only large aura sheet in the container) |

## efct00.tpl#0 atlas cells (256x64, real alpha)

Measured by alpha/luminance tile scan (16px grid):

| Rect (x,y,w,h) | Appearance | Identified as | Wired to |
|---|---|---|---|
| (0,0,32,32) | White ring / donut | **Shockwave ring** | Death-explosion expanding ring |
| (0,32,32,32) | Bright white crescent puff | Ground dust puff | Not wired yet |
| (32,0,24,32) | Black soft blob (alpha) | Dark smoke blob | Not wired (big version used instead) |
| (64,0,32,32) | 2x2 block of four 16x16 white crescents | **Dissipating puff frame sequence** (subtle per-cell variation reads as frames) | Projectile-impact flipbook (4 frames, order TL,TR,BL,BR — TUNED-visual) |
| (96,0,48,32) | Black soft ellipse (alpha) | Drop shadow / flat smoke | Not wired |
| (160,0,64,64) | Big black soft ball (alpha) | **Smoke ball** | Death-explosion smoke |

## Runtime wiring summary (apps/game/src/sim/battleScene.ts)

- Primary textures: `/ui/txg/ptcl00/image_*.png` canonical exports; the older
  hand-extracted `/fx/*.png` copies of the same cells are load-failure
  fallbacks (`loadFxTexture`).
- Effects now on real sheets: energy/flame/muzzle projectiles, hit spark,
  muzzle flash (on shoot entry), death explosion (core #1 + efct00 ring +
  efct00 smoke), dash burst (#0), charge glow (#7, ramped by
  `chargeFrames`, tier thresholds 30/90 mirroring actionProfiles defaults).
- Flipbook: projectile impacts step through the 4 efct00 puff cells over the
  sprite lifetime.
- The canvas-drawn lock-on reticle and the arrow ally marker are untouched
  (still TUNED stand-ins; no reticle texture exists in ptcl00).
