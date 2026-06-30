# Real Asset Coverage Audit

Generated: 2026-06-30T22:47:10.453Z

## Summary

- Runtime screens audited: 10
- Screens using at least one real exported UI asset: 5
- Screens with handcoded/CSS/SVG surface signals: 10
- Screens mounting a real exported UI scene model: 1
- UI texture export: 831 images from apps/game/public/ui/manifest.json
- Requested UI scene models exported: 1 from apps/game/public/ui/scenes/manifest.json
- Stage exports complete visually: 40/40
- Runtime stage fallback: st00

## Runtime Screens

| Screen | Coverage | Real exported assets used | Handcoded signals | Next replacement |
| --- | --- | --- | --- | --- |
| main-menu | handcoded-or-unverified | none | css-menu-gear:85<br>runtime-text-layout:86 | Export/wire the real 3D desk/menu scene instead of CSS ellipse gears and text labels. |
| select-difficulty | handcoded-or-unverified | none | css-grid-backdrop:48<br>css-gradient-surface:23<br>css-menu-gear:67<br>css-option-pad:66<br>runtime-text-layout:49 | Use the original Challenge select scene textures/models for the three GF-energy pads and cursor. |
| select-players | handcoded-or-unverified | none | css-grid-backdrop:55<br>css-option-pad:77<br>css-label-pill:78<br>handcoded-player-silhouette:27<br>runtime-text-layout:42 | Replace CSS silhouettes/pills/controllers with the real Challenge player-count select scene. |
| load-box-data | real-scene-partial-layout | /ui/scenes/box00/model_00.dae | css-grid-backdrop:29<br>runtime-text-layout:30 | Keep the real box DAE, but replace handwritten gold screen copy/rules with original load/box scene assets. |
| select-force | mixed-real-assets-handcoded-surface | ASSETS.entryControls<br>borgBannerPath<br>borgMiniPath<br>borgFacePath | css-grid-backdrop:39<br>css-force-platform:45<br>runtime-text-layout:40 | Replace CSS platform/cost/name layout with the real force-slot/select scene and save/box data. |
| force-builder | mixed-real-assets-handcoded-surface | borgBannerPath<br>borgMiniPath | handcoded-force-grid:73<br>handcoded-force-ring:85<br>handcoded-force-slot:154<br>runtime-text-layout:68 | Replace the CSS grid/ring/hex slots with original Edit Force layout data and model/collection assets. |
| battle-intro | mixed-real-assets-handcoded-surface | ASSETS.briefingVs<br>ASSETS.vsSelectLabels<br>borgMiniPath | runtime-text-layout:49 | Use the real briefing/entry scene sequencing, not only low-opacity extracted texture sheets over CSS plates. |
| battle-hud | mixed-real-assets-handcoded-surface | borgBannerPath | svg-hud-gauge:73<br>css-lockon-reticle:139<br>runtime-text-layout:107 | Map original HUD widgets, lock-on cursor, weapon prompts, and battle data instead of CSS/SVG gauges. |
| results | handcoded-or-unverified | none | css-results-backdrop:56<br>css-results-row:90<br>runtime-text-layout:64 | Export and mount the real result/podium scenes instead of CSS rows and sky backdrop. |
| pause-menu | handcoded-or-unverified | none | css-pause-box:32<br>runtime-text-layout:33 | Find the original pause menu data/assets; current overlay is entirely recreated CSS/text. |

## UI Scene Export Coverage

| Scene | Status | Source archive | Model files | Next |
| --- | --- | --- | --- | --- |
| box00 | exported | user-data/GG4E/afs_data/root/box00_mdl.arc | apps/game/public/ui/scenes/box00/model_00.dae | wired asset available |
| brif00 | not-exported | user-data/GG4E/afs_data/root/brif00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/brif00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| entry00 | not-exported | user-data/GG4E/afs_data/root/entry00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/entry00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| optn00 | not-exported | user-data/GG4E/afs_data/root/optn00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/optn00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| rpot20 | not-exported | user-data/GG4E/afs_data/root/rpot20_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/rpot20_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| rpot21 | not-exported | user-data/GG4E/afs_data/root/rpot21_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/rpot21_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| rpot22 | not-exported | user-data/GG4E/afs_data/root/rpot22_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/rpot22_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| rpot23 | not-exported | user-data/GG4E/afs_data/root/rpot23_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/rpot23_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| staff00 | not-exported | user-data/GG4E/afs_data/root/staff00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/staff00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| tl00 | not-exported | user-data/GG4E/afs_data/root/tl00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/tl00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| vsel00 | not-exported | user-data/GG4E/afs_data/root/vsel00_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/vsel00_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |
| vsel01 | not-exported | user-data/GG4E/afs_data/root/vsel01_mdl.arc | none | Need validated DAE/glTF export for user-data/GG4E/afs_data/root/vsel01_mdl.arc; current scripts/export-ui-scenes.mjs only copies existing validated exports. |

## Stage Coverage

Public stage manifest has 40 stage folders; 40 have complete visual DAE exports and 18 have collision bins.

Runtime loader refs: apps/game/src/main.ts:416, apps/game/src/main.ts:420, apps/game/src/main.ts:457, apps/game/src/main.ts:685

Exports cover many real stages, but arena-name to st## routing still falls back to st00 unless cfg.arena is already a literal st## id.

## Challenge / Adventure / Story Risk

Runtime screen comments and flow are Challenge-oriented, while packages/assets/data/stages.json declares Story Mode data and adventure-flow inventory discusses Adventure. Do not use Story/Adventure mission rows as a verified Challenge stage/menu mapping.

- packages/assets/data/stages.json:3
- research/asset-inventory/adventure-flow-ai.json:78
- 9 audited runtime screens identify themselves as Challenge or in-battle Challenge UI.

## Next Replacements

- Wire stageIdForArena to a traced arena-name -> st## table; public exports now cover 40 visual stages, but runtime fallback still collapses non-st## arenas to st00.
- Generalize UI scene model export beyond box00 so tl00/optn00/vsel00/vsel01/brif00/entry00/rpot20-23 can replace CSS scene recreations.
- Replace ForceBuilder/SelectForce surfaces with unitall/plcmndata/allbox/gets-driven original layouts; they currently use real borg icons/banners inside handcoded DOM.
- Map battle HUD from comhit/cmn_data/as_icon/arrow/font assets and DOL HUD state instead of CSS/SVG gauges.

## Verification

```bash
rtk node scripts/audit-real-asset-coverage.mjs
rtk node -e "JSON.parse(require('fs').readFileSync('research/asset-coverage/real-asset-coverage.json','utf8')); console.log('asset coverage json ok')"
```
