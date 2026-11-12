# Powered source firing presentation

This bounded lane connects effect id 0 to the existing tracked efct00 bank mesh 35.
No original assets were imported or uploaded. The generic B-shot muzzle heuristic
is unchanged; this lane serves source normal-X and charged-X only.

## Source contracts

- FUN_80166fa8, chunk_0042:3825–3840: normal action 2 allocates resource 2 once,
  then calls FUN_8016d584 ports 0–3. Charged action 3 calls zz_007db5c_ rows 8, 9, 6, 7
  without an ammo call, then zz_00f036c_(actor, 6). The latter is SOUND, not an
  effect spawner or fifth damaging projectile (chunk_0026:790–870).
- FUN_8016d584, chunk_0043:4646–4768: each port allocates four children, copies
  the same mode 5 base matrix into each, then creates ONE launch effect using the
  last child's matrix. Spread rotations occur later in FUN_8016d9ac:4796 onward.
  Thus launch forward follows the unsplayed aim, not the fourth child's cone.
- Raw tracked shotVariantKinds.json table 0x80350660, stride 0x30: +0x2d is 0 for
  all eight rows. +0x2f is 6 for normal rows 0–3, 255 for split rows 4–7.
- Primary table 0x802d6d68 rows 6–9 byte+0x34 is 0. Primary init creates its flash
  before immediate flight update, at the muzzle with basis mode 5 (initial velocity,
  reference = (vz, 0, -vx)); chunk_0011:4450–4465. A proximity split calls
  FUN_8016d584 before primary removal (chunk_0011:4535).
- zz_00aedc0_, chunk_0017:2382: copies the launch matrix. FUN_800af054 extracts
  and normalizes its columns, chooses random local-Z spin (row 0 is not exempt),
  loads mesh 35 and samples team material frame. FUN_800af488 multiplies curves by
  maximum base X/Y magnitude. Here mode 5 columns are unit length: no owner-scale
  inflation. Life 4, scale keys (0:1,1,1),(1:.25,.25,.25),(4:0,0,.25), alpha
  (0:1),(1:1),(4:0). Existing mesh/curve evidence: efct-consumers-decode-2026-07-04.md.

Counts: normal 4 flashes + 4 cue-6 calls; charged 4 initial flashes + 1 cue-6 call; each charged
primary that splits adds 1 flash + 1 cue-255 call, independently of its four children.

## Host lifetime and limitations

Battle owns a separate short-lived flash list. Birth age 0 and subsequent fixed
simulation steps ages 1, 2, 3 are observable; age 4 retires. Snapshots are cloned,
read-only in the public API and not mutated on subsequent steps. Render-only
observations/pause do not advance or re-emit effects. Child collision/removal
cannot prematurely remove a flash. Renderer reconciles stable flash IDs and
source ages rather than using the existing wall-clock transient FX lifecycle.

A dedicated deterministic xorshift visual stream selects one byte per flash for
local-Z spin. It deliberately does not consume gameplay RNG. Original global
object initialization/RNG scheduling is not reconstructed: exact random spin or
global RNG parity is not claimed. Existing static-bind muzzle, actor-root target,
and degenerate-basis host approximations remain. Neutral fixed-step timing only.

Cues 6 and 255 route through existing Battle.onRomCue / audio cue resolver. Neither
se_006 nor se_0ff exists in the tracked origin/main audio manifest at df8cea9;
no fallback sound is invented. Existing host audio callback does not reproduce
source per-actor volume/pan (zz_00f04b4_). Source charge glow is still unported.

## Regression coverage

Powered source math tests assert base basis independent of spread RNG and actor
scale. Actual Battle tests cover four normal events versus 16 children, denied or
interrupted input, four charged launch events, one event per split, separate cue
counts 6/255, muzzle before first movement, source-age lifetime, render-only reads,
snapshot stability, survival after child removal, visual spin variation and
unrelated-borg isolation. Family tests positively assert charged cue 6 once and
no sound callback on the projectile route. Existing lifecycle suite remains the
aggregate simulation regression gate.

## Final verification

Passed on the final code: combat build; repository policy; workspace/game
typecheck; browser POC gate unit tests; menu flow (including morph, size and Diver
renderer regressions); force builder; game session; pause edges; input focus;
title frontend; camera; challenge flow; render disposal; the dedicated Powered
launch-flash renderer selfcheck; ROM selfcheck; combat lifecycle; OGhidra import
tests; and production game build. The build retains the existing large-chunk
warning. `git diff --check` passed.

The `verify:contributor` aggregate stopped at the HUD asset check because this
sparse checkout lacks three pre-existing assets: ASCII font image, fmg00 marker
texture, and bn0000 banner image. Every later aggregate stage was then run
independently and passed. This is not a claim that the whole aggregate passed.
The renderer tests exercise actual Three.js scene objects, not a browser visual
capture. No original-asset upload or extraction was used to bypass the gap.

`verify:docs` was also attempted on this snapshot. It stopped in
`docs-site/scripts/curate-data.mjs` with ENOENT for the pre-existing missing
`research/asset-inventory/borg-assets.json`; the downstream documentation build
therefore did not run. No replacement inventory or asset payload was invented.
