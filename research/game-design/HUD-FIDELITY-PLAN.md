# Battle HUD Fidelity Plan (GG4E)

Rebuild record for `apps/game/src/ui/hud/BattleHud.ts` against the real in-battle
captures. Layout truth: `apps/game/reference/captures/challenge-8-in-battle-hud.png`
(normal state, ally 300 / enemy 1267 / HP 185 / ammo 5) and
`challenge-9-battle-critical-hp.png` (critical state, enemy 564 / HP 7).
All measurements below are fractions of the native 640x480 frame, converted to
design px. The web HUD is now authored on a literal 640x480 stage and scaled to
the container, so these numbers are used verbatim in code.

## ascii.tpl glyph-mapping bug (root cause)

`ascii.tpl` (exported at `apps/game/public/ui/tpl/ascii/image_00_IA4.png` and
`public/ui/hud/font_ascii_atlas.png`, 128x128, 16x16 grid of 8px cells) is laid
out as:

| atlas row | content |
|---|---|
| 0 | blank |
| 1 | hex header row `0123456789ABCDEF` (thin) |
| 2..7 | **thin ASCII block**, chars 0x20..0x7E, 16/row |
| 8 | blank |
| 9 | hex header row (bold) |
| 10..15 | **bold ASCII block** (white core + baked black outline), chars 0x20..0x7E |

The regressed code mapped `row = floor((code-0x20)/16)` with **no row offset**,
assuming the ASCII block started at atlas row 0. Every glyph therefore rendered
two rows too high: `ENEMY` → `%.%-9`, `ALLY` → `!,,9` (transcribed in playtest
as "1,,9"), digits only *looked* half-right because the hex header row happens
to contain `0..9` at the same columns. Fix: `ASCII_THIN_ROW_OFFSET = 2` /
`ASCII_BOLD_ROW_OFFSET = 10` in `apps/game/src/ui/bitmapText.ts`.
Regression guard: `node scripts/assert-ascii-glyphs.mjs` (verifies the mapping
against the atlas pixels themselves; the offset-less mapping is a tripwire).

The HUD now uses the **bold** block for all labels/numbers, tinted per element
by recoloring the white glyph cores on a canvas (preserving the baked outline),
which is how the tinted text in the captures reads.

## Capture measurements → implementation (challenge-8 unless noted)

| Element | Measured (% of 640x480) | Design px | Notes |
|---|---|---|---|
| Ally energy tab "300 ◄ ALLY" | x 29.1–46.5%, y 1.7–6.3% | 186..298, 8..30 | left-tipped green arrow plate; mint number `#c8ffd4`, yellow `ALLY` `#ffd428`, chevron divider |
| Ally bar fill | x 12.5–45.8%, y 7.7–10.4% | 80..293, 37..50 | two-tone green (`#8aff54` over `#2ce518`), left-anchored, depletes from the right |
| Ally torn lead-in zigzag | x 4.5–12.5%, centerline y 9.0% | 29..80, y 43 | fixed dark-brown zigzag stroke |
| Black torn zigzag (between rows) | x 35.3–45.9%, y ~11.5–13% | 226..294, y 60 | fixed decoration |
| Enemy bar fill | right edge 35.3%, y 12.3–14.8% | right-anchored at x 226, 59..71 | two-tone red (`#ff7a52` over `#f2200a`); right-anchored, depletes from the left (564 → short bar in challenge-9) |
| Enemy tab "ENEMY ► 1267" | x 4.3–20.8%, y 16.3–20.4% | 27..133, 78..98 | right-tipped maroon arrow plate; yellow `ENEMY`, pink number `#ff9ed8` |
| "!" alert roundel | center (49.7%, 9.8%), dia ~4.7%W | (318, 47), r 15 | yellow disc, black ring, inner white ring, black bold `!` glyph |
| Boost gear (top-right) | center (75.5%, 10.0%), outer dia ~11%W | (483, 48), r ~35 | dark gear silhouette + cyan `#3fe8c4` inner ring; ring is full in challenge-9 → treated as 0..1 gauge (`boost01`) — **SUPERSEDED**: the ring is the Power Burst gauge, see the 2026-07-03 addendum row below |
| Power Burst gauge (gear ring) | same gear, ring anchored at 6 o'clock; challenge-8 ~20–25% filled, challenge-9 complete | (483, 48), ring r 15, stroke 7 | **capture-verified rebind (2026-07-03)**: challenge-8 shows the ring part-filled while the borg stands GROUNDED (boost fuel refills on land → a fuel ring would read full); challenge-9 (late battle, heavy inflicted damage) shows it complete — matches the manual/StrategyWiki "circle fills with inflicted damage" burst gauge (behavior-notes (ao), CONFIRMED_MANUAL) and the ported per-player meter (Q4 RESOLVED, findings §S: +0x126 / max +0x124 = 3000, +50 per attacker hit, `charged` +0x103 one frame after max). Driven by `burst01`; flashes bright when `burstCharged` (flash period TUNED). Fill start = bottom (capture); fill DIRECTION cw/ccw TUNED (single frame). Boost fuel demoted to a small TUNED secondary arc (r 7) in the gear hub, hidden at full so the at-rest HUD still matches the captures |
| DEFEATED banner | — no capture exists | TUNED: left 236, top 228 (centered on 640x480), scale-3 bold ascii.tpl, red `#ff2f1a` | shown while the local player's active borg is dead/absent awaiting redeploy or the battle is lost (`HudState.defeated`, presentation.ts). Position, wording ("DEFEATED") and art are ALL stand-ins until a real banner capture is taken |
| Player tag ("1P"/"2P") | — no capture exists | TUNED: left 8, top 8, scale-2 bold, yellow | hidden unless `HudState.playerLabel` set (multi-local sessions only); placeholder for future multi-viewport work — needs a 2P quadrant-HUD capture |
| HP ring gauge | center (7.7%, 82.9%), outer dia ~10%W | (49, 398), outer r 32 | glossy green ring w/ specular; arc = hp/maxHp |
| HP digits | x 9.4–17%, cap height ~5.4%H | left 60, top 384, 24px digits | chunky yellow-green `#cde23c`, advance 21px |
| Critical capsule (challenge-9) | x 4.1–22.0%, y 84.4–89.5% | 26..141, 405..430 | red pill + darker ring knob + yellow tick; replaces the ring; digits shift into it |
| X special prompt | center (93.8%, 74.0%) | (600, 355) | white disc r 13.5 + dashed cooldown ring r 24 (dashes brighten with `cooldown01`), black bold `X` |
| Reload pill | x 76.0–88.4%, y 86.0–89.3% | 486..566, 413..429 | cyan `#3fe8cf` fill w/ white top highlight over dark track |
| Ammo digits | center ~ (81%, 83%) | left 506, top 380, 24px digits | same chunky style as HP |
| B attack disc | center (88.3%, 90.6%), dia 4.4%W | (565, 435), r 14 | white disc, black bold `B`; dark-red arc `#8c1710` sweeping (487,448)→(585,420) beneath |
| Teammate plate ("CPU") | label x 56–60%, y 21.5–23.5%; bar x 56.2–66%, y 25.2–26.4% | bar 63x6px | white bold label + green-on-red mini HP bar; world-anchored — exposed as optional `HudState.teammates` (screen-normalized positions supplied by the caller) |
| Lock-on reticle | center of locked target, dia ~10.5%W | — | world-space; owned by battleScene, intentionally NOT drawn by BattleHud |

Note on the captures' button glyphs: the real prompts are **X** (special, dashed
ring) and **B** (attack, ammo + reload); the previous web HUD showed a "Y"
button, now corrected to X.

## What is real vs. reconstructed

- **Real extracted art now used:** `ascii.tpl` bold glyph block for every HUD
  label/number (tinted like the game's vertex-colored font quads); optional
  per-borg `bn<code>` name banner.
- **Reconstructed as vector geometry (faithful by measurement):** meter bars +
  torn zigzags, arrow tab plates, alert roundel, boost gear, HP ring/critical
  capsule, X/B discs, dashed cooldown ring, reload pill, red arc, teammate mini
  bars. Per `apps/game/public/ui/hud/manifest.json` and
  `research/asset-inventory/ui-hud-assets.md`, the original draws all of these
  as runtime HSD/GX geometry with vertex colors — **no source sprite exists on
  disc**, so vector reconstruction *is* the faithful approach.

## Export-needed list (do not run disc exports here; source archives per ui-hud-assets.md)

| Item | Source (user-data/GG4E/afs_data/root) | Why |
|---|---|---|
| `mini_t.tpl` (192x104 C8) | battle HUD / fonts group | possible source of the chunky HP/ammo digit style; if it decodes to the big bubbly digits, swap the scaled ascii bold digits for it |
| `arrow_mdl.arc` | Adventure select / battle HUD | lock-on arrow/target indicator model (vertex-colored HSD geometry, no texture) — needed if battleScene's reticle should be rebuilt from source geometry rather than measurement |
| `fmg00_mdl.arc` textures (partially exported) | battle HUD | face-marker roundel (`face_icon_roundel.png` exported, W/H unrecorded) — candidate for teammate/world markers, not used by the screen HUD per captures |
| `comhit.bin` | battle HUD | combo/hit HUD layout data; schema unmapped — may encode the real meter positions (would replace manual capture measurement) |
| `as_icon.tpl` (exported as `hud/as_icon.png`) | main menu / battle HUD | 64x64 roundel; role unconfirmed (manifest confidence "low") — not placed until it is seen in a capture |

## Verification

- `node scripts/assert-ascii-glyphs.mjs` — glyph mapping vs. atlas pixels (passes).
- `node <repo>/node_modules/typescript/lib/tsc.js --noEmit -p apps/game/tsconfig.json` — clean.
- Visual: enter a Challenge battle and compare against `challenge-8`/`challenge-9`
  captures at the same aspect; the HUD stage scales to the container 1:1.

## Addendum (2026-07-02, export round 2 — supersedes stale export-needed rows above)

- `mini_t.tpl`: EXPORTED — it is the mini title logo, NOT the chunky digit font (hypothesis
  refuted by inspection). The capture's chunky digits have no decodable on-disc sprite; the
  tinted bold ascii.tpl rendering stands as the closest real asset.
- `comhit.bin`: NOT a HUD layout schema — it is a common combat hit table (83 x 0xF4 records,
  same family as pl####hit.bin; see research/format-specs/comhit-bin-notes.md). Dropped from
  the HUD export list; capture measurements remain the layout truth.
- `fmg00_mdl.arc`: FULLY EXPORTED (torn-zigzag/V-marker shapes + face roundel textures under
  apps/game/public/ui/hsd/fmg00_mdl/).
- `arrow_mdl.arc`: confirmed vertex-colored geometry only (no textures to decode); covered by
  arrowMdlGeometry.generated.ts.

## Addendum (2026-07-03, burst gauge + DEFEATED wave)

**Gear-ring rebind (boost → burst).** Re-examining the two captures against the ported
per-player Power Burst meter (Q4 RESOLVED — research/decomp/attack-mechanics-open-questions.md
Q4, attack-mechanics-findings.md §S) settles what the top-right cyan ring is:

- challenge-8: the borg is standing **grounded** yet the ring shows only a small cyan arc
  anchored at the bottom of the gear (~20–25%). Boost fuel refills on landing
  (movement.ts), so a fuel gauge would read **full** here — the partial ring refutes the
  boost reading.
- challenge-9: late battle (enemy 1267 → 564, critical HP), ring **complete** — consistent
  with a gauge that fills with inflicted damage over the battle.
- The official NA manual / StrategyWiki describe the burst gauge as a circle that fills with
  inflicted damage and "press Y when the burst gauge is at max" (behavior-notes (ao),
  CONFIRMED_MANUAL).

BattleHud.ts therefore drives the ring from `burst01` (meter / BURST.METER_MAX, sim state
`BattleState.burstMeterByPlayer`) and flashes it bright while `burstCharged` (ROM +0x103, one
frame after max; flash period TUNED). Fill anchor = 6 o'clock (measured, challenge-8); fill
direction is TUNED (unmeasurable from one frame). The TUNED `boost01` fuel readout is demoted
to a small secondary arc inside the gear hub, hidden while full so the at-rest HUD still
matches the captures (which show an empty hub). The gauge is **display-only** until ATK-012
lands burst gameplay effects (BURST.ENABLED stays false; Q5 speed boost still open). CPU-owned
attackers do not fill a meter this wave (documented in packages/combat burst.ts) — the HUD
surfaces exactly what the sim provides.

**DEFEATED banner.** New center-screen scale-3 red bold ascii.tpl banner behind
`HudState.defeated` (local active borg dead/absent awaiting redeploy, or result = lose —
presentation.ts battleHudState). Everything about it (position, the word "DEFEATED", color)
is TUNED until a real capture exists.

**Melee reticle sync.** presentation.ts focusHasMeleeRangeTarget now evaluates the sim's own
contextual-B SELECTION window (combat.ts targetWithinMeleeEngage / meleeEngageRangeFor —
MELEE.ENGAGE_RANGE / ENGAGE_Y_TOLERANCE widened by the borg's reach) so the yellow→red
reticle flip matches when B actually selects melee. Mechanism CONFIRMED_MANUAL
(behavior-notes (ao)); the numeric threshold FLOAT_8043762c remains untraced → TUNED.

### Remaining capture needs (research follow-ups)

| Need | Unblocks |
|---|---|
| DEFEATED banner frame (die in a Dolphin battle, capture the banner) | real placement/art/wording for the TUNED center-screen banner |
| 2P quadrant HUD (splitscreen VS capture) | player-tag placement + per-quadrant HUD layout for multi-viewport |
| Center-screen team-energy variant (user-described; no capture) | whether/when the ally/enemy meters move center-screen — **do not move them** until captured |
| Ammo-pips variant (user-described; no capture) | whether some borgs show ammo as pips instead of digits — **keep digits** until captured |
| Burst ring mid-fill + charged-state frames (hit-count-correlated captures) | fill direction (cw/ccw), exact ring radii/stroke, real charged-flash treatment |
