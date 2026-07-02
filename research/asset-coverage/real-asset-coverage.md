# Real Asset Coverage Audit

Generated: 2026-07-02T05:44:18.763Z

## Summary

- Runtime screens audited: 10
- Screens using at least one real exported UI asset: 10
- Screens with handcoded/CSS/SVG surface signals: 9
- Screens mounting a real exported UI scene model: 7
- UI texture export: 831 images from apps/game/public/ui/manifest.json
- Requested UI scene models exported: 12 from apps/game/public/ui/scenes/manifest.json
- Stage exports complete visually: 40/40
- Stage render-state exports: 40/40
- Runtime stage collision bounds from STIH: yes
- Runtime stage triangle collision from STIH: yes
- Runtime lateral wall collision from STIH: yes
- Runtime upward ceiling collision from STIH: yes
- Runtime projectile FX from exported textures: yes
- Runtime battle HUD uses exported font/roundel: yes
- Runtime battle HUD uses as_icon: no (manifest marks as_icon low-confidence for battle HUD)
- Runtime lock target uses arrow_mdl geometry: yes
- Common battle archive inventoried: yes
- Common battle data exact actor matches: 2
- Runtime actor-data bytes bound to combat formulas: yes
- Runtime type damage matrix from DOL tables: yes
- Runtime knockback direction from DOL function: yes
- Runtime battle camera mode-1 blend from DOL constants: yes
- Runtime borg animation direct matches: 1402/1404
- Runtime borg animation fallbacks/missing: 2/0
- Runtime fly uses exported boost clip: yes
- Runtime items/powerups modeled: no
- Runtime audio from exported cues: yes
- Shared binary parsers implemented: 4/4
- Runtime stage fallback: st00
- Runtime accepts exported stage catalog ids: yes
- Runtime Challenge CPU spawn pools from DOL table: yes

## Format Parser Coverage

Archive inventory: research/asset-inventory/pzz-arz-inventory.json (252 PZZ archives, 3104 PZZ members, 103 direct ARZ files).
HIT inventory: research/asset-inventory/hit-bin-inventory.json (54 STIH stage files, 210 player hit tables, 2 common hit tables).

| Format | Implemented | Source | Evidence |
| --- | --- | --- | --- |
| PZZ | yes | packages/formats/src/pzz.ts | Exports archive member-table unpacking and compressed member decompression. |
| ARZ | yes | packages/formats/src/arz.ts | Direct ARZ/PZZP wrapper; pzz-arz inventory currently lists 103 direct ARZ files. |
| STIH stage HIT | yes | packages/formats/src/hit-bin.ts | Shared parser for STIH stage collision grids; hit-bin inventory currently lists 54 stage files. |
| Actor/common HIT | yes | packages/formats/src/hit-bin.ts | Shared raw parser for pl####hit.bin/comhit*.bin remap headers plus 0xF4 records; inventory lists 210 player and 2 common files. |

## Runtime Screens

| Screen | Coverage | Real exported assets used | Handcoded signals | Next replacement |
| --- | --- | --- | --- | --- |
| main-menu | real-scene-partial-layout | ASSETS.mainMenuOption<br>/ui/scenes/tl00/model_00.dae<br>/ui/scenes/optn00/model_00.dae | none | Export/wire the real 3D desk/menu scene instead of CSS ellipse gears and text labels. |
| select-difficulty | real-scene-partial-layout | /ui/scenes/vsel00/model_00.dae | css-grid-backdrop:54<br>css-gradient-surface:25<br>css-menu-gear:77<br>css-option-pad:76<br>runtime-text-layout:57 | Use the original Challenge select scene textures/models for the three GF-energy pads and cursor. |
| select-players | real-scene-partial-layout | /ui/scenes/vsel01/model_00.dae | css-grid-backdrop:48<br>css-option-pad:74<br>css-label-pill:75<br>handcoded-player-silhouette:28<br>runtime-text-layout:32 | Replace CSS silhouettes/pills/controllers with the real Challenge player-count select scene. |
| load-box-data | real-scene-partial-layout | /ui/scenes/box00/model_00.dae | css-grid-backdrop:27<br>runtime-text-layout:28 | Keep the real box DAE, but replace handwritten gold screen copy/rules with original load/box scene assets. |
| select-force | real-scene-partial-layout | ASSETS.entryControls<br>borgBannerPath<br>borgMiniPath<br>borgFacePath<br>/models/pl0615/model_00.dae<br>/ui/scenes/entry00/model_00.dae | css-grid-backdrop:52<br>css-force-platform:60<br>runtime-text-layout:55 | Replace CSS platform/cost/name layout with the real force-slot/select scene and save/box data. |
| force-builder | mixed-real-assets-handcoded-surface | ASSETS.unitAllAtlas<br>borgBannerPath<br>borgMiniPath | handcoded-force-grid:79<br>handcoded-force-ring:91<br>handcoded-force-slot:160<br>runtime-text-layout:74 | Replace the CSS grid/ring/hex slots with original Edit Force layout data and model/collection assets. |
| battle-intro | real-scene-partial-layout | ASSETS.briefingVs<br>ASSETS.vsSelectLabels<br>borgMiniPath<br>/ui/scenes/brif00/model_00.dae | runtime-text-layout:52 | Use the real briefing/entry scene sequencing, not only low-opacity extracted texture sheets over CSS plates. |
| battle-hud | mixed-real-assets-handcoded-surface | ASSETS.faceMarkerRoundel<br>borgBannerPath<br>ASSETS.fontAscii | svg-hud-gauge:76<br>css-lockon-reticle:146<br>runtime-text-layout:126 | Map original HUD widgets, lock-on cursor, weapon prompts, and battle data instead of CSS/SVG gauges. |
| results | real-scene-partial-layout | ASSETS.resultsWin<br>ASSETS.resultsLose<br>ASSETS.resultsStartPrompt<br>ASSETS.resultsGameOver<br>/ui/scenes/rpot20/model_00.dae<br>/ui/scenes/rpot23/model_00.dae | css-results-row:113<br>runtime-text-layout:113 | Export and mount the real result/podium scenes instead of CSS rows and sky backdrop. |
| pause-menu | mixed-real-assets-handcoded-surface | ASSETS.fontAscii | css-pause-box:33 | Find the original pause menu data/assets; current overlay is entirely recreated CSS/text. |

## UI Scene Export Coverage

| Scene | Status | Source archive | Model files | Next |
| --- | --- | --- | --- | --- |
| box00 | exported | user-data/GG4E/afs_data/root/box00_mdl.arc | apps/game/public/ui/scenes/box00/model_00.dae | wired asset available |
| brif00 | exported | user-data/GG4E/afs_data/root/brif00_mdl.arc | apps/game/public/ui/scenes/brif00/model_00.dae<br>apps/game/public/ui/scenes/brif00/model_01.dae<br>apps/game/public/ui/scenes/brif00/model_02.dae<br>apps/game/public/ui/scenes/brif00/model_03.dae<br>apps/game/public/ui/scenes/brif00/model_04.dae<br>apps/game/public/ui/scenes/brif00/model_05.dae<br>apps/game/public/ui/scenes/brif00/model_06.dae<br>apps/game/public/ui/scenes/brif00/model_07.dae<br>apps/game/public/ui/scenes/brif00/model_08.dae<br>apps/game/public/ui/scenes/brif00/model_09.dae<br>apps/game/public/ui/scenes/brif00/model_10.dae<br>apps/game/public/ui/scenes/brif00/model_11.dae<br>apps/game/public/ui/scenes/brif00/model_12.dae<br>apps/game/public/ui/scenes/brif00/model_13.dae<br>apps/game/public/ui/scenes/brif00/model_14.dae<br>apps/game/public/ui/scenes/brif00/model_15.dae<br>apps/game/public/ui/scenes/brif00/model_16.dae<br>apps/game/public/ui/scenes/brif00/model_17.dae<br>apps/game/public/ui/scenes/brif00/model_18.dae<br>apps/game/public/ui/scenes/brif00/model_19.dae<br>apps/game/public/ui/scenes/brif00/model_20.dae<br>apps/game/public/ui/scenes/brif00/model_21.dae<br>apps/game/public/ui/scenes/brif00/model_22.dae<br>apps/game/public/ui/scenes/brif00/model_23.dae<br>apps/game/public/ui/scenes/brif00/model_24.dae<br>apps/game/public/ui/scenes/brif00/model_25.dae<br>apps/game/public/ui/scenes/brif00/model_26.dae | wired asset available |
| entry00 | exported | user-data/GG4E/afs_data/root/entry00_mdl.arc | apps/game/public/ui/scenes/entry00/model_00.dae<br>apps/game/public/ui/scenes/entry00/model_01.dae<br>apps/game/public/ui/scenes/entry00/model_02.dae<br>apps/game/public/ui/scenes/entry00/model_03.dae<br>apps/game/public/ui/scenes/entry00/model_04.dae<br>apps/game/public/ui/scenes/entry00/model_05.dae<br>apps/game/public/ui/scenes/entry00/model_06.dae<br>apps/game/public/ui/scenes/entry00/model_07.dae<br>apps/game/public/ui/scenes/entry00/model_08.dae<br>apps/game/public/ui/scenes/entry00/model_09.dae<br>apps/game/public/ui/scenes/entry00/model_10.dae<br>apps/game/public/ui/scenes/entry00/model_11.dae<br>apps/game/public/ui/scenes/entry00/model_12.dae<br>apps/game/public/ui/scenes/entry00/model_13.dae<br>apps/game/public/ui/scenes/entry00/model_14.dae<br>apps/game/public/ui/scenes/entry00/model_15.dae<br>apps/game/public/ui/scenes/entry00/model_16.dae<br>apps/game/public/ui/scenes/entry00/model_17.dae<br>apps/game/public/ui/scenes/entry00/model_18.dae<br>apps/game/public/ui/scenes/entry00/model_19.dae<br>apps/game/public/ui/scenes/entry00/model_20.dae<br>apps/game/public/ui/scenes/entry00/model_21.dae<br>apps/game/public/ui/scenes/entry00/model_22.dae<br>apps/game/public/ui/scenes/entry00/model_23.dae<br>apps/game/public/ui/scenes/entry00/model_24.dae<br>apps/game/public/ui/scenes/entry00/model_25.dae<br>apps/game/public/ui/scenes/entry00/model_26.dae<br>apps/game/public/ui/scenes/entry00/model_27.dae<br>apps/game/public/ui/scenes/entry00/model_28.dae | wired asset available |
| optn00 | exported | user-data/GG4E/afs_data/root/optn00_mdl.arc | apps/game/public/ui/scenes/optn00/model_00.dae<br>apps/game/public/ui/scenes/optn00/model_01.dae<br>apps/game/public/ui/scenes/optn00/model_02.dae<br>apps/game/public/ui/scenes/optn00/model_03.dae<br>apps/game/public/ui/scenes/optn00/model_04.dae<br>apps/game/public/ui/scenes/optn00/model_05.dae<br>apps/game/public/ui/scenes/optn00/model_06.dae<br>apps/game/public/ui/scenes/optn00/model_07.dae<br>apps/game/public/ui/scenes/optn00/model_08.dae<br>apps/game/public/ui/scenes/optn00/model_09.dae<br>apps/game/public/ui/scenes/optn00/model_10.dae<br>apps/game/public/ui/scenes/optn00/model_11.dae<br>apps/game/public/ui/scenes/optn00/model_12.dae<br>apps/game/public/ui/scenes/optn00/model_13.dae<br>apps/game/public/ui/scenes/optn00/model_14.dae<br>apps/game/public/ui/scenes/optn00/model_15.dae<br>apps/game/public/ui/scenes/optn00/model_16.dae<br>apps/game/public/ui/scenes/optn00/model_17.dae<br>apps/game/public/ui/scenes/optn00/model_18.dae<br>apps/game/public/ui/scenes/optn00/model_19.dae<br>apps/game/public/ui/scenes/optn00/model_20.dae<br>apps/game/public/ui/scenes/optn00/model_21.dae<br>apps/game/public/ui/scenes/optn00/model_22.dae | wired asset available |
| rpot20 | exported | user-data/GG4E/afs_data/root/rpot20_mdl.arc | apps/game/public/ui/scenes/rpot20/model_00.dae<br>apps/game/public/ui/scenes/rpot20/model_01.dae<br>apps/game/public/ui/scenes/rpot20/model_02.dae<br>apps/game/public/ui/scenes/rpot20/model_03.dae<br>apps/game/public/ui/scenes/rpot20/model_04.dae<br>apps/game/public/ui/scenes/rpot20/model_05.dae<br>apps/game/public/ui/scenes/rpot20/model_06.dae<br>apps/game/public/ui/scenes/rpot20/model_07.dae<br>apps/game/public/ui/scenes/rpot20/model_08.dae<br>apps/game/public/ui/scenes/rpot20/model_09.dae<br>apps/game/public/ui/scenes/rpot20/model_10.dae<br>apps/game/public/ui/scenes/rpot20/model_11.dae<br>apps/game/public/ui/scenes/rpot20/model_12.dae<br>apps/game/public/ui/scenes/rpot20/model_13.dae<br>apps/game/public/ui/scenes/rpot20/model_14.dae<br>apps/game/public/ui/scenes/rpot20/model_15.dae<br>apps/game/public/ui/scenes/rpot20/model_16.dae<br>apps/game/public/ui/scenes/rpot20/model_17.dae<br>apps/game/public/ui/scenes/rpot20/model_18.dae<br>apps/game/public/ui/scenes/rpot20/model_19.dae<br>apps/game/public/ui/scenes/rpot20/model_20.dae | wired asset available |
| rpot21 | exported | user-data/GG4E/afs_data/root/rpot21_mdl.arc | apps/game/public/ui/scenes/rpot21/model_00.dae<br>apps/game/public/ui/scenes/rpot21/model_01.dae<br>apps/game/public/ui/scenes/rpot21/model_02.dae<br>apps/game/public/ui/scenes/rpot21/model_03.dae<br>apps/game/public/ui/scenes/rpot21/model_04.dae<br>apps/game/public/ui/scenes/rpot21/model_05.dae<br>apps/game/public/ui/scenes/rpot21/model_06.dae<br>apps/game/public/ui/scenes/rpot21/model_07.dae<br>apps/game/public/ui/scenes/rpot21/model_08.dae<br>apps/game/public/ui/scenes/rpot21/model_09.dae<br>apps/game/public/ui/scenes/rpot21/model_10.dae<br>apps/game/public/ui/scenes/rpot21/model_11.dae<br>apps/game/public/ui/scenes/rpot21/model_12.dae<br>apps/game/public/ui/scenes/rpot21/model_13.dae<br>apps/game/public/ui/scenes/rpot21/model_14.dae<br>apps/game/public/ui/scenes/rpot21/model_15.dae<br>apps/game/public/ui/scenes/rpot21/model_16.dae<br>apps/game/public/ui/scenes/rpot21/model_17.dae<br>apps/game/public/ui/scenes/rpot21/model_18.dae<br>apps/game/public/ui/scenes/rpot21/model_19.dae<br>apps/game/public/ui/scenes/rpot21/model_20.dae | wired asset available |
| rpot22 | exported | user-data/GG4E/afs_data/root/rpot22_mdl.arc | apps/game/public/ui/scenes/rpot22/model_00.dae<br>apps/game/public/ui/scenes/rpot22/model_01.dae<br>apps/game/public/ui/scenes/rpot22/model_02.dae<br>apps/game/public/ui/scenes/rpot22/model_03.dae<br>apps/game/public/ui/scenes/rpot22/model_04.dae<br>apps/game/public/ui/scenes/rpot22/model_05.dae<br>apps/game/public/ui/scenes/rpot22/model_06.dae<br>apps/game/public/ui/scenes/rpot22/model_07.dae<br>apps/game/public/ui/scenes/rpot22/model_08.dae<br>apps/game/public/ui/scenes/rpot22/model_09.dae<br>apps/game/public/ui/scenes/rpot22/model_10.dae<br>apps/game/public/ui/scenes/rpot22/model_11.dae<br>apps/game/public/ui/scenes/rpot22/model_12.dae<br>apps/game/public/ui/scenes/rpot22/model_13.dae<br>apps/game/public/ui/scenes/rpot22/model_14.dae<br>apps/game/public/ui/scenes/rpot22/model_15.dae<br>apps/game/public/ui/scenes/rpot22/model_16.dae<br>apps/game/public/ui/scenes/rpot22/model_17.dae<br>apps/game/public/ui/scenes/rpot22/model_18.dae<br>apps/game/public/ui/scenes/rpot22/model_19.dae<br>apps/game/public/ui/scenes/rpot22/model_20.dae | wired asset available |
| rpot23 | exported | user-data/GG4E/afs_data/root/rpot23_mdl.arc | apps/game/public/ui/scenes/rpot23/model_00.dae<br>apps/game/public/ui/scenes/rpot23/model_01.dae<br>apps/game/public/ui/scenes/rpot23/model_02.dae<br>apps/game/public/ui/scenes/rpot23/model_03.dae<br>apps/game/public/ui/scenes/rpot23/model_04.dae<br>apps/game/public/ui/scenes/rpot23/model_05.dae<br>apps/game/public/ui/scenes/rpot23/model_06.dae<br>apps/game/public/ui/scenes/rpot23/model_07.dae<br>apps/game/public/ui/scenes/rpot23/model_08.dae<br>apps/game/public/ui/scenes/rpot23/model_09.dae<br>apps/game/public/ui/scenes/rpot23/model_10.dae<br>apps/game/public/ui/scenes/rpot23/model_11.dae<br>apps/game/public/ui/scenes/rpot23/model_12.dae<br>apps/game/public/ui/scenes/rpot23/model_13.dae<br>apps/game/public/ui/scenes/rpot23/model_14.dae<br>apps/game/public/ui/scenes/rpot23/model_15.dae<br>apps/game/public/ui/scenes/rpot23/model_16.dae<br>apps/game/public/ui/scenes/rpot23/model_17.dae<br>apps/game/public/ui/scenes/rpot23/model_18.dae<br>apps/game/public/ui/scenes/rpot23/model_19.dae<br>apps/game/public/ui/scenes/rpot23/model_20.dae | wired asset available |
| staff00 | exported | user-data/GG4E/afs_data/root/staff00_mdl.arc | apps/game/public/ui/scenes/staff00/model_00.dae<br>apps/game/public/ui/scenes/staff00/model_01.dae<br>apps/game/public/ui/scenes/staff00/model_02.dae<br>apps/game/public/ui/scenes/staff00/model_03.dae<br>apps/game/public/ui/scenes/staff00/model_04.dae<br>apps/game/public/ui/scenes/staff00/model_05.dae<br>apps/game/public/ui/scenes/staff00/model_06.dae<br>apps/game/public/ui/scenes/staff00/model_07.dae<br>apps/game/public/ui/scenes/staff00/model_08.dae<br>apps/game/public/ui/scenes/staff00/model_09.dae<br>apps/game/public/ui/scenes/staff00/model_10.dae<br>apps/game/public/ui/scenes/staff00/model_11.dae<br>apps/game/public/ui/scenes/staff00/model_12.dae<br>apps/game/public/ui/scenes/staff00/model_13.dae<br>apps/game/public/ui/scenes/staff00/model_14.dae<br>apps/game/public/ui/scenes/staff00/model_15.dae<br>apps/game/public/ui/scenes/staff00/model_16.dae<br>apps/game/public/ui/scenes/staff00/model_17.dae<br>apps/game/public/ui/scenes/staff00/model_18.dae<br>apps/game/public/ui/scenes/staff00/model_19.dae<br>apps/game/public/ui/scenes/staff00/model_20.dae<br>apps/game/public/ui/scenes/staff00/model_21.dae<br>apps/game/public/ui/scenes/staff00/model_22.dae<br>apps/game/public/ui/scenes/staff00/model_23.dae<br>apps/game/public/ui/scenes/staff00/model_24.dae<br>apps/game/public/ui/scenes/staff00/model_25.dae<br>apps/game/public/ui/scenes/staff00/model_26.dae<br>apps/game/public/ui/scenes/staff00/model_27.dae<br>apps/game/public/ui/scenes/staff00/model_28.dae<br>apps/game/public/ui/scenes/staff00/model_29.dae<br>apps/game/public/ui/scenes/staff00/model_30.dae<br>apps/game/public/ui/scenes/staff00/model_31.dae<br>apps/game/public/ui/scenes/staff00/model_32.dae<br>apps/game/public/ui/scenes/staff00/model_33.dae<br>apps/game/public/ui/scenes/staff00/model_34.dae<br>apps/game/public/ui/scenes/staff00/model_35.dae<br>apps/game/public/ui/scenes/staff00/model_36.dae<br>apps/game/public/ui/scenes/staff00/model_37.dae<br>apps/game/public/ui/scenes/staff00/model_38.dae<br>apps/game/public/ui/scenes/staff00/model_39.dae<br>apps/game/public/ui/scenes/staff00/model_40.dae<br>apps/game/public/ui/scenes/staff00/model_41.dae<br>apps/game/public/ui/scenes/staff00/model_42.dae<br>apps/game/public/ui/scenes/staff00/model_43.dae<br>apps/game/public/ui/scenes/staff00/model_44.dae<br>apps/game/public/ui/scenes/staff00/model_45.dae<br>apps/game/public/ui/scenes/staff00/model_46.dae<br>apps/game/public/ui/scenes/staff00/model_47.dae<br>apps/game/public/ui/scenes/staff00/model_48.dae<br>apps/game/public/ui/scenes/staff00/model_49.dae<br>apps/game/public/ui/scenes/staff00/model_50.dae<br>apps/game/public/ui/scenes/staff00/model_51.dae<br>apps/game/public/ui/scenes/staff00/model_52.dae<br>apps/game/public/ui/scenes/staff00/model_53.dae<br>apps/game/public/ui/scenes/staff00/model_54.dae<br>apps/game/public/ui/scenes/staff00/model_55.dae<br>apps/game/public/ui/scenes/staff00/model_56.dae<br>apps/game/public/ui/scenes/staff00/model_57.dae<br>apps/game/public/ui/scenes/staff00/model_58.dae<br>apps/game/public/ui/scenes/staff00/model_59.dae<br>apps/game/public/ui/scenes/staff00/model_60.dae<br>apps/game/public/ui/scenes/staff00/model_61.dae<br>apps/game/public/ui/scenes/staff00/model_62.dae<br>apps/game/public/ui/scenes/staff00/model_63.dae<br>apps/game/public/ui/scenes/staff00/model_64.dae<br>apps/game/public/ui/scenes/staff00/model_65.dae<br>apps/game/public/ui/scenes/staff00/model_66.dae<br>apps/game/public/ui/scenes/staff00/model_67.dae<br>apps/game/public/ui/scenes/staff00/model_68.dae<br>apps/game/public/ui/scenes/staff00/model_69.dae<br>apps/game/public/ui/scenes/staff00/model_70.dae<br>apps/game/public/ui/scenes/staff00/model_71.dae<br>apps/game/public/ui/scenes/staff00/model_72.dae<br>apps/game/public/ui/scenes/staff00/model_73.dae<br>apps/game/public/ui/scenes/staff00/model_74.dae<br>apps/game/public/ui/scenes/staff00/model_75.dae<br>apps/game/public/ui/scenes/staff00/model_76.dae<br>apps/game/public/ui/scenes/staff00/model_77.dae<br>apps/game/public/ui/scenes/staff00/model_78.dae<br>apps/game/public/ui/scenes/staff00/model_79.dae | wired asset available |
| tl00 | exported | user-data/GG4E/afs_data/root/tl00_mdl.arc | apps/game/public/ui/scenes/tl00/model_00.dae<br>apps/game/public/ui/scenes/tl00/model_01.dae<br>apps/game/public/ui/scenes/tl00/model_02.dae<br>apps/game/public/ui/scenes/tl00/model_03.dae<br>apps/game/public/ui/scenes/tl00/model_04.dae<br>apps/game/public/ui/scenes/tl00/model_05.dae<br>apps/game/public/ui/scenes/tl00/model_06.dae<br>apps/game/public/ui/scenes/tl00/model_07.dae<br>apps/game/public/ui/scenes/tl00/model_08.dae<br>apps/game/public/ui/scenes/tl00/model_09.dae<br>apps/game/public/ui/scenes/tl00/model_10.dae<br>apps/game/public/ui/scenes/tl00/model_11.dae<br>apps/game/public/ui/scenes/tl00/model_12.dae<br>apps/game/public/ui/scenes/tl00/model_13.dae<br>apps/game/public/ui/scenes/tl00/model_14.dae<br>apps/game/public/ui/scenes/tl00/model_15.dae<br>apps/game/public/ui/scenes/tl00/model_16.dae<br>apps/game/public/ui/scenes/tl00/model_17.dae<br>apps/game/public/ui/scenes/tl00/model_18.dae<br>apps/game/public/ui/scenes/tl00/model_19.dae<br>apps/game/public/ui/scenes/tl00/model_20.dae<br>apps/game/public/ui/scenes/tl00/model_21.dae<br>apps/game/public/ui/scenes/tl00/model_22.dae<br>apps/game/public/ui/scenes/tl00/model_23.dae<br>apps/game/public/ui/scenes/tl00/model_24.dae<br>apps/game/public/ui/scenes/tl00/model_25.dae<br>apps/game/public/ui/scenes/tl00/model_26.dae<br>apps/game/public/ui/scenes/tl00/model_27.dae<br>apps/game/public/ui/scenes/tl00/model_28.dae<br>apps/game/public/ui/scenes/tl00/model_29.dae<br>apps/game/public/ui/scenes/tl00/model_30.dae<br>apps/game/public/ui/scenes/tl00/model_31.dae<br>apps/game/public/ui/scenes/tl00/model_32.dae<br>apps/game/public/ui/scenes/tl00/model_33.dae<br>apps/game/public/ui/scenes/tl00/model_34.dae<br>apps/game/public/ui/scenes/tl00/model_35.dae<br>apps/game/public/ui/scenes/tl00/model_36.dae | wired asset available |
| vsel00 | exported | user-data/GG4E/afs_data/root/vsel00_mdl.arc | apps/game/public/ui/scenes/vsel00/model_00.dae<br>apps/game/public/ui/scenes/vsel00/model_01.dae<br>apps/game/public/ui/scenes/vsel00/model_02.dae<br>apps/game/public/ui/scenes/vsel00/model_03.dae<br>apps/game/public/ui/scenes/vsel00/model_04.dae<br>apps/game/public/ui/scenes/vsel00/model_05.dae<br>apps/game/public/ui/scenes/vsel00/model_06.dae<br>apps/game/public/ui/scenes/vsel00/model_07.dae<br>apps/game/public/ui/scenes/vsel00/model_08.dae<br>apps/game/public/ui/scenes/vsel00/model_09.dae<br>apps/game/public/ui/scenes/vsel00/model_10.dae<br>apps/game/public/ui/scenes/vsel00/model_100.dae<br>apps/game/public/ui/scenes/vsel00/model_101.dae<br>apps/game/public/ui/scenes/vsel00/model_102.dae<br>apps/game/public/ui/scenes/vsel00/model_103.dae<br>apps/game/public/ui/scenes/vsel00/model_104.dae<br>apps/game/public/ui/scenes/vsel00/model_105.dae<br>apps/game/public/ui/scenes/vsel00/model_106.dae<br>apps/game/public/ui/scenes/vsel00/model_107.dae<br>apps/game/public/ui/scenes/vsel00/model_108.dae<br>apps/game/public/ui/scenes/vsel00/model_109.dae<br>apps/game/public/ui/scenes/vsel00/model_11.dae<br>apps/game/public/ui/scenes/vsel00/model_110.dae<br>apps/game/public/ui/scenes/vsel00/model_111.dae<br>apps/game/public/ui/scenes/vsel00/model_112.dae<br>apps/game/public/ui/scenes/vsel00/model_113.dae<br>apps/game/public/ui/scenes/vsel00/model_114.dae<br>apps/game/public/ui/scenes/vsel00/model_115.dae<br>apps/game/public/ui/scenes/vsel00/model_116.dae<br>apps/game/public/ui/scenes/vsel00/model_117.dae<br>apps/game/public/ui/scenes/vsel00/model_118.dae<br>apps/game/public/ui/scenes/vsel00/model_119.dae<br>apps/game/public/ui/scenes/vsel00/model_12.dae<br>apps/game/public/ui/scenes/vsel00/model_120.dae<br>apps/game/public/ui/scenes/vsel00/model_121.dae<br>apps/game/public/ui/scenes/vsel00/model_122.dae<br>apps/game/public/ui/scenes/vsel00/model_123.dae<br>apps/game/public/ui/scenes/vsel00/model_124.dae<br>apps/game/public/ui/scenes/vsel00/model_125.dae<br>apps/game/public/ui/scenes/vsel00/model_126.dae<br>apps/game/public/ui/scenes/vsel00/model_127.dae<br>apps/game/public/ui/scenes/vsel00/model_128.dae<br>apps/game/public/ui/scenes/vsel00/model_129.dae<br>apps/game/public/ui/scenes/vsel00/model_13.dae<br>apps/game/public/ui/scenes/vsel00/model_130.dae<br>apps/game/public/ui/scenes/vsel00/model_131.dae<br>apps/game/public/ui/scenes/vsel00/model_132.dae<br>apps/game/public/ui/scenes/vsel00/model_133.dae<br>apps/game/public/ui/scenes/vsel00/model_134.dae<br>apps/game/public/ui/scenes/vsel00/model_135.dae<br>apps/game/public/ui/scenes/vsel00/model_136.dae<br>apps/game/public/ui/scenes/vsel00/model_137.dae<br>apps/game/public/ui/scenes/vsel00/model_138.dae<br>apps/game/public/ui/scenes/vsel00/model_139.dae<br>apps/game/public/ui/scenes/vsel00/model_14.dae<br>apps/game/public/ui/scenes/vsel00/model_140.dae<br>apps/game/public/ui/scenes/vsel00/model_141.dae<br>apps/game/public/ui/scenes/vsel00/model_142.dae<br>apps/game/public/ui/scenes/vsel00/model_143.dae<br>apps/game/public/ui/scenes/vsel00/model_144.dae<br>apps/game/public/ui/scenes/vsel00/model_145.dae<br>apps/game/public/ui/scenes/vsel00/model_146.dae<br>apps/game/public/ui/scenes/vsel00/model_147.dae<br>apps/game/public/ui/scenes/vsel00/model_148.dae<br>apps/game/public/ui/scenes/vsel00/model_149.dae<br>apps/game/public/ui/scenes/vsel00/model_15.dae<br>apps/game/public/ui/scenes/vsel00/model_150.dae<br>apps/game/public/ui/scenes/vsel00/model_151.dae<br>apps/game/public/ui/scenes/vsel00/model_152.dae<br>apps/game/public/ui/scenes/vsel00/model_153.dae<br>apps/game/public/ui/scenes/vsel00/model_154.dae<br>apps/game/public/ui/scenes/vsel00/model_155.dae<br>apps/game/public/ui/scenes/vsel00/model_156.dae<br>apps/game/public/ui/scenes/vsel00/model_157.dae<br>apps/game/public/ui/scenes/vsel00/model_158.dae<br>apps/game/public/ui/scenes/vsel00/model_159.dae<br>apps/game/public/ui/scenes/vsel00/model_16.dae<br>apps/game/public/ui/scenes/vsel00/model_160.dae<br>apps/game/public/ui/scenes/vsel00/model_161.dae<br>apps/game/public/ui/scenes/vsel00/model_162.dae<br>apps/game/public/ui/scenes/vsel00/model_163.dae<br>apps/game/public/ui/scenes/vsel00/model_164.dae<br>apps/game/public/ui/scenes/vsel00/model_165.dae<br>apps/game/public/ui/scenes/vsel00/model_17.dae<br>apps/game/public/ui/scenes/vsel00/model_18.dae<br>apps/game/public/ui/scenes/vsel00/model_19.dae<br>apps/game/public/ui/scenes/vsel00/model_20.dae<br>apps/game/public/ui/scenes/vsel00/model_21.dae<br>apps/game/public/ui/scenes/vsel00/model_22.dae<br>apps/game/public/ui/scenes/vsel00/model_23.dae<br>apps/game/public/ui/scenes/vsel00/model_24.dae<br>apps/game/public/ui/scenes/vsel00/model_25.dae<br>apps/game/public/ui/scenes/vsel00/model_26.dae<br>apps/game/public/ui/scenes/vsel00/model_27.dae<br>apps/game/public/ui/scenes/vsel00/model_28.dae<br>apps/game/public/ui/scenes/vsel00/model_29.dae<br>apps/game/public/ui/scenes/vsel00/model_30.dae<br>apps/game/public/ui/scenes/vsel00/model_31.dae<br>apps/game/public/ui/scenes/vsel00/model_32.dae<br>apps/game/public/ui/scenes/vsel00/model_33.dae<br>apps/game/public/ui/scenes/vsel00/model_34.dae<br>apps/game/public/ui/scenes/vsel00/model_35.dae<br>apps/game/public/ui/scenes/vsel00/model_36.dae<br>apps/game/public/ui/scenes/vsel00/model_37.dae<br>apps/game/public/ui/scenes/vsel00/model_38.dae<br>apps/game/public/ui/scenes/vsel00/model_39.dae<br>apps/game/public/ui/scenes/vsel00/model_40.dae<br>apps/game/public/ui/scenes/vsel00/model_41.dae<br>apps/game/public/ui/scenes/vsel00/model_42.dae<br>apps/game/public/ui/scenes/vsel00/model_43.dae<br>apps/game/public/ui/scenes/vsel00/model_44.dae<br>apps/game/public/ui/scenes/vsel00/model_45.dae<br>apps/game/public/ui/scenes/vsel00/model_47.dae<br>apps/game/public/ui/scenes/vsel00/model_48.dae<br>apps/game/public/ui/scenes/vsel00/model_49.dae<br>apps/game/public/ui/scenes/vsel00/model_50.dae<br>apps/game/public/ui/scenes/vsel00/model_51.dae<br>apps/game/public/ui/scenes/vsel00/model_52.dae<br>apps/game/public/ui/scenes/vsel00/model_53.dae<br>apps/game/public/ui/scenes/vsel00/model_54.dae<br>apps/game/public/ui/scenes/vsel00/model_55.dae<br>apps/game/public/ui/scenes/vsel00/model_56.dae<br>apps/game/public/ui/scenes/vsel00/model_57.dae<br>apps/game/public/ui/scenes/vsel00/model_58.dae<br>apps/game/public/ui/scenes/vsel00/model_59.dae<br>apps/game/public/ui/scenes/vsel00/model_60.dae<br>apps/game/public/ui/scenes/vsel00/model_61.dae<br>apps/game/public/ui/scenes/vsel00/model_62.dae<br>apps/game/public/ui/scenes/vsel00/model_63.dae<br>apps/game/public/ui/scenes/vsel00/model_64.dae<br>apps/game/public/ui/scenes/vsel00/model_65.dae<br>apps/game/public/ui/scenes/vsel00/model_66.dae<br>apps/game/public/ui/scenes/vsel00/model_67.dae<br>apps/game/public/ui/scenes/vsel00/model_68.dae<br>apps/game/public/ui/scenes/vsel00/model_69.dae<br>apps/game/public/ui/scenes/vsel00/model_70.dae<br>apps/game/public/ui/scenes/vsel00/model_71.dae<br>apps/game/public/ui/scenes/vsel00/model_72.dae<br>apps/game/public/ui/scenes/vsel00/model_73.dae<br>apps/game/public/ui/scenes/vsel00/model_74.dae<br>apps/game/public/ui/scenes/vsel00/model_75.dae<br>apps/game/public/ui/scenes/vsel00/model_76.dae<br>apps/game/public/ui/scenes/vsel00/model_77.dae<br>apps/game/public/ui/scenes/vsel00/model_78.dae<br>apps/game/public/ui/scenes/vsel00/model_79.dae<br>apps/game/public/ui/scenes/vsel00/model_80.dae<br>apps/game/public/ui/scenes/vsel00/model_81.dae<br>apps/game/public/ui/scenes/vsel00/model_82.dae<br>apps/game/public/ui/scenes/vsel00/model_83.dae<br>apps/game/public/ui/scenes/vsel00/model_84.dae<br>apps/game/public/ui/scenes/vsel00/model_85.dae<br>apps/game/public/ui/scenes/vsel00/model_86.dae<br>apps/game/public/ui/scenes/vsel00/model_87.dae<br>apps/game/public/ui/scenes/vsel00/model_88.dae<br>apps/game/public/ui/scenes/vsel00/model_89.dae<br>apps/game/public/ui/scenes/vsel00/model_90.dae<br>apps/game/public/ui/scenes/vsel00/model_91.dae<br>apps/game/public/ui/scenes/vsel00/model_92.dae<br>apps/game/public/ui/scenes/vsel00/model_93.dae<br>apps/game/public/ui/scenes/vsel00/model_94.dae<br>apps/game/public/ui/scenes/vsel00/model_95.dae<br>apps/game/public/ui/scenes/vsel00/model_96.dae<br>apps/game/public/ui/scenes/vsel00/model_97.dae<br>apps/game/public/ui/scenes/vsel00/model_98.dae<br>apps/game/public/ui/scenes/vsel00/model_99.dae | wired asset available |
| vsel01 | exported | user-data/GG4E/afs_data/root/vsel01_mdl.arc | apps/game/public/ui/scenes/vsel01/model_00.dae<br>apps/game/public/ui/scenes/vsel01/model_01.dae<br>apps/game/public/ui/scenes/vsel01/model_02.dae<br>apps/game/public/ui/scenes/vsel01/model_03.dae<br>apps/game/public/ui/scenes/vsel01/model_04.dae<br>apps/game/public/ui/scenes/vsel01/model_05.dae<br>apps/game/public/ui/scenes/vsel01/model_06.dae<br>apps/game/public/ui/scenes/vsel01/model_07.dae<br>apps/game/public/ui/scenes/vsel01/model_08.dae<br>apps/game/public/ui/scenes/vsel01/model_09.dae<br>apps/game/public/ui/scenes/vsel01/model_10.dae<br>apps/game/public/ui/scenes/vsel01/model_100.dae<br>apps/game/public/ui/scenes/vsel01/model_101.dae<br>apps/game/public/ui/scenes/vsel01/model_102.dae<br>apps/game/public/ui/scenes/vsel01/model_103.dae<br>apps/game/public/ui/scenes/vsel01/model_104.dae<br>apps/game/public/ui/scenes/vsel01/model_105.dae<br>apps/game/public/ui/scenes/vsel01/model_106.dae<br>apps/game/public/ui/scenes/vsel01/model_107.dae<br>apps/game/public/ui/scenes/vsel01/model_108.dae<br>apps/game/public/ui/scenes/vsel01/model_109.dae<br>apps/game/public/ui/scenes/vsel01/model_11.dae<br>apps/game/public/ui/scenes/vsel01/model_110.dae<br>apps/game/public/ui/scenes/vsel01/model_111.dae<br>apps/game/public/ui/scenes/vsel01/model_112.dae<br>apps/game/public/ui/scenes/vsel01/model_113.dae<br>apps/game/public/ui/scenes/vsel01/model_114.dae<br>apps/game/public/ui/scenes/vsel01/model_115.dae<br>apps/game/public/ui/scenes/vsel01/model_116.dae<br>apps/game/public/ui/scenes/vsel01/model_117.dae<br>apps/game/public/ui/scenes/vsel01/model_118.dae<br>apps/game/public/ui/scenes/vsel01/model_119.dae<br>apps/game/public/ui/scenes/vsel01/model_12.dae<br>apps/game/public/ui/scenes/vsel01/model_120.dae<br>apps/game/public/ui/scenes/vsel01/model_121.dae<br>apps/game/public/ui/scenes/vsel01/model_122.dae<br>apps/game/public/ui/scenes/vsel01/model_123.dae<br>apps/game/public/ui/scenes/vsel01/model_124.dae<br>apps/game/public/ui/scenes/vsel01/model_125.dae<br>apps/game/public/ui/scenes/vsel01/model_126.dae<br>apps/game/public/ui/scenes/vsel01/model_127.dae<br>apps/game/public/ui/scenes/vsel01/model_128.dae<br>apps/game/public/ui/scenes/vsel01/model_129.dae<br>apps/game/public/ui/scenes/vsel01/model_13.dae<br>apps/game/public/ui/scenes/vsel01/model_130.dae<br>apps/game/public/ui/scenes/vsel01/model_131.dae<br>apps/game/public/ui/scenes/vsel01/model_132.dae<br>apps/game/public/ui/scenes/vsel01/model_133.dae<br>apps/game/public/ui/scenes/vsel01/model_134.dae<br>apps/game/public/ui/scenes/vsel01/model_135.dae<br>apps/game/public/ui/scenes/vsel01/model_136.dae<br>apps/game/public/ui/scenes/vsel01/model_137.dae<br>apps/game/public/ui/scenes/vsel01/model_138.dae<br>apps/game/public/ui/scenes/vsel01/model_139.dae<br>apps/game/public/ui/scenes/vsel01/model_14.dae<br>apps/game/public/ui/scenes/vsel01/model_140.dae<br>apps/game/public/ui/scenes/vsel01/model_141.dae<br>apps/game/public/ui/scenes/vsel01/model_142.dae<br>apps/game/public/ui/scenes/vsel01/model_143.dae<br>apps/game/public/ui/scenes/vsel01/model_144.dae<br>apps/game/public/ui/scenes/vsel01/model_145.dae<br>apps/game/public/ui/scenes/vsel01/model_146.dae<br>apps/game/public/ui/scenes/vsel01/model_147.dae<br>apps/game/public/ui/scenes/vsel01/model_148.dae<br>apps/game/public/ui/scenes/vsel01/model_149.dae<br>apps/game/public/ui/scenes/vsel01/model_15.dae<br>apps/game/public/ui/scenes/vsel01/model_150.dae<br>apps/game/public/ui/scenes/vsel01/model_151.dae<br>apps/game/public/ui/scenes/vsel01/model_152.dae<br>apps/game/public/ui/scenes/vsel01/model_153.dae<br>apps/game/public/ui/scenes/vsel01/model_154.dae<br>apps/game/public/ui/scenes/vsel01/model_155.dae<br>apps/game/public/ui/scenes/vsel01/model_156.dae<br>apps/game/public/ui/scenes/vsel01/model_157.dae<br>apps/game/public/ui/scenes/vsel01/model_158.dae<br>apps/game/public/ui/scenes/vsel01/model_159.dae<br>apps/game/public/ui/scenes/vsel01/model_16.dae<br>apps/game/public/ui/scenes/vsel01/model_160.dae<br>apps/game/public/ui/scenes/vsel01/model_161.dae<br>apps/game/public/ui/scenes/vsel01/model_162.dae<br>apps/game/public/ui/scenes/vsel01/model_163.dae<br>apps/game/public/ui/scenes/vsel01/model_164.dae<br>apps/game/public/ui/scenes/vsel01/model_17.dae<br>apps/game/public/ui/scenes/vsel01/model_18.dae<br>apps/game/public/ui/scenes/vsel01/model_19.dae<br>apps/game/public/ui/scenes/vsel01/model_20.dae<br>apps/game/public/ui/scenes/vsel01/model_21.dae<br>apps/game/public/ui/scenes/vsel01/model_22.dae<br>apps/game/public/ui/scenes/vsel01/model_23.dae<br>apps/game/public/ui/scenes/vsel01/model_24.dae<br>apps/game/public/ui/scenes/vsel01/model_25.dae<br>apps/game/public/ui/scenes/vsel01/model_26.dae<br>apps/game/public/ui/scenes/vsel01/model_27.dae<br>apps/game/public/ui/scenes/vsel01/model_28.dae<br>apps/game/public/ui/scenes/vsel01/model_29.dae<br>apps/game/public/ui/scenes/vsel01/model_30.dae<br>apps/game/public/ui/scenes/vsel01/model_31.dae<br>apps/game/public/ui/scenes/vsel01/model_32.dae<br>apps/game/public/ui/scenes/vsel01/model_33.dae<br>apps/game/public/ui/scenes/vsel01/model_34.dae<br>apps/game/public/ui/scenes/vsel01/model_35.dae<br>apps/game/public/ui/scenes/vsel01/model_36.dae<br>apps/game/public/ui/scenes/vsel01/model_37.dae<br>apps/game/public/ui/scenes/vsel01/model_38.dae<br>apps/game/public/ui/scenes/vsel01/model_39.dae<br>apps/game/public/ui/scenes/vsel01/model_40.dae<br>apps/game/public/ui/scenes/vsel01/model_41.dae<br>apps/game/public/ui/scenes/vsel01/model_42.dae<br>apps/game/public/ui/scenes/vsel01/model_43.dae<br>apps/game/public/ui/scenes/vsel01/model_44.dae<br>apps/game/public/ui/scenes/vsel01/model_45.dae<br>apps/game/public/ui/scenes/vsel01/model_46.dae<br>apps/game/public/ui/scenes/vsel01/model_47.dae<br>apps/game/public/ui/scenes/vsel01/model_48.dae<br>apps/game/public/ui/scenes/vsel01/model_49.dae<br>apps/game/public/ui/scenes/vsel01/model_50.dae<br>apps/game/public/ui/scenes/vsel01/model_51.dae<br>apps/game/public/ui/scenes/vsel01/model_52.dae<br>apps/game/public/ui/scenes/vsel01/model_53.dae<br>apps/game/public/ui/scenes/vsel01/model_54.dae<br>apps/game/public/ui/scenes/vsel01/model_55.dae<br>apps/game/public/ui/scenes/vsel01/model_56.dae<br>apps/game/public/ui/scenes/vsel01/model_57.dae<br>apps/game/public/ui/scenes/vsel01/model_58.dae<br>apps/game/public/ui/scenes/vsel01/model_59.dae<br>apps/game/public/ui/scenes/vsel01/model_60.dae<br>apps/game/public/ui/scenes/vsel01/model_61.dae<br>apps/game/public/ui/scenes/vsel01/model_62.dae<br>apps/game/public/ui/scenes/vsel01/model_63.dae<br>apps/game/public/ui/scenes/vsel01/model_64.dae<br>apps/game/public/ui/scenes/vsel01/model_65.dae<br>apps/game/public/ui/scenes/vsel01/model_66.dae<br>apps/game/public/ui/scenes/vsel01/model_67.dae<br>apps/game/public/ui/scenes/vsel01/model_68.dae<br>apps/game/public/ui/scenes/vsel01/model_69.dae<br>apps/game/public/ui/scenes/vsel01/model_70.dae<br>apps/game/public/ui/scenes/vsel01/model_71.dae<br>apps/game/public/ui/scenes/vsel01/model_72.dae<br>apps/game/public/ui/scenes/vsel01/model_73.dae<br>apps/game/public/ui/scenes/vsel01/model_74.dae<br>apps/game/public/ui/scenes/vsel01/model_75.dae<br>apps/game/public/ui/scenes/vsel01/model_76.dae<br>apps/game/public/ui/scenes/vsel01/model_77.dae<br>apps/game/public/ui/scenes/vsel01/model_78.dae<br>apps/game/public/ui/scenes/vsel01/model_79.dae<br>apps/game/public/ui/scenes/vsel01/model_80.dae<br>apps/game/public/ui/scenes/vsel01/model_81.dae<br>apps/game/public/ui/scenes/vsel01/model_82.dae<br>apps/game/public/ui/scenes/vsel01/model_83.dae<br>apps/game/public/ui/scenes/vsel01/model_84.dae<br>apps/game/public/ui/scenes/vsel01/model_85.dae<br>apps/game/public/ui/scenes/vsel01/model_86.dae<br>apps/game/public/ui/scenes/vsel01/model_87.dae<br>apps/game/public/ui/scenes/vsel01/model_88.dae<br>apps/game/public/ui/scenes/vsel01/model_89.dae<br>apps/game/public/ui/scenes/vsel01/model_90.dae<br>apps/game/public/ui/scenes/vsel01/model_91.dae<br>apps/game/public/ui/scenes/vsel01/model_92.dae<br>apps/game/public/ui/scenes/vsel01/model_93.dae<br>apps/game/public/ui/scenes/vsel01/model_94.dae<br>apps/game/public/ui/scenes/vsel01/model_95.dae<br>apps/game/public/ui/scenes/vsel01/model_96.dae<br>apps/game/public/ui/scenes/vsel01/model_97.dae<br>apps/game/public/ui/scenes/vsel01/model_98.dae<br>apps/game/public/ui/scenes/vsel01/model_99.dae | wired asset available |

## Stage Coverage

Public stage manifest has 40 stage folders; 40 have complete visual DAE exports, 40 have render-state JSON, and 18 have collision bins.

Runtime loader refs: apps/game/src/main.ts:881, apps/game/src/main.ts:886, apps/game/src/main.ts:793, apps/game/src/main.ts:805, apps/game/src/main.ts:926, apps/game/src/main.ts:1264

Runtime collision parser: @gf/formats (bounds wired, triangles wired, walls wired, ceilings wired)

Challenge stage selector: DOL selector bytes wired to exported runtime stage routing (packages/missions/src/challenge-reference.ts:32; apps/game/src/sim/adapter.ts:59).
Challenge CPU spawn pools: generated from recovered 0x80380804 table (22 groups, 145 borg ids; packages/missions/src/challenge-spawn-pools.generated.ts:32; packages/missions/src/challenge.ts:364).

Runtime authorizes literal exported st## ids, uses DOL-backed Challenge selector metadata to route exported stage subtable families when present, and builds CPU rosters from the recovered Challenge spawn-pool table; unverified Adventure/human arena names still fall back to st00.

Stage-code evidence: research/asset-inventory/stage-code-evidence.json (0 boot.dol hits, 0 unique stage codes, 0 verified arena-name mappings).

This scan proves the exported st## codes are present in disc/runtime artifacts, but it does not prove any human arena-name or Challenge rotation mapping. Keep runtime name mapping on st## literals until Dolphin/DOL control-flow tracing identifies the table that chooses stages.

## Combat FX

Projectile visual kind in sim state: yes
Projectile visual kind derived from borg profile: yes
Projectile renderer uses exported FX textures: yes

| Projectile texture | Exists |
| --- | --- |
| /fx/energy_dot.png | yes |
| /fx/flame_core.png | yes |
| /fx/muzzle_flash.png | yes |
| /fx/efct00_atlas.png | yes |
| /fx/hit_spark.png | yes |

## Battle HUD Asset Evidence

Manifest: apps/game/public/ui/hud/manifest.json
Gotcha Force does NOT ship its in-battle HUD overlay (the green/red energy meter, the circular HP gauge, A/B/X/Y button icons, the lock-on reticle, ALLY/ENEMY/CPU labels, the '!' alert) as discrete pre-rendered sprite textures. After decoding every 'battle HUD' category source (301 source assets, 327 images) plus the dedicated icon/font files (as_icon, ascii, font_00, mini_t, dc000/dc001, fmg00_mdl, arrow_mdl), none of those gauge/meter/button/reticle elements exist as a standalone texture. They are drawn at runtime by the game's HSD/GX pipeline (billboard geometry + vertex colors), and HUD text/numbers are rendered glyph-by-glyph from the font atlases below. The real, reusable in-battle HUD art that IS available as image assets is the font/glyph atlases and a couple of icon textures.

| Asset | Source | Size | Confidence | Used in BattleHud | Role |
| --- | --- | --- | --- | --- | --- |
| fontAscii | user-data/GG4E/afs_data/root/ascii.tpl | 128x128 | high | yes | Monospaced ASCII glyph atlas (0-9, A-Z, a-z, punctuation). This is the source for HUD numerals -> hit/combo digits, timers, counts. Composite digits by blitting cells from this atlas. |
| fontJp | user-data/GG4E/afs_data/root/font_00.tpl | 256x320 | high | no | Main game font atlas (Japanese kana + Latin + digits + symbols). Source glyphs for any on-screen HUD/menu text labels. |
| asIcon | user-data/GG4E/afs_data/root/as_icon.tpl | 64x64 | low | no | Small circular icon/badge (adventure-select / status icon). Possible HUD status badge; role not definitively a battle-HUD element. |
| faceIconRoundel | user-data/GG4E/afs_data/root/fmg00_mdl.arc (texture_001) | unknown | medium | yes | Circular Borg face icon/roundel used as an in-battle character marker, plus a small icon strip (see faceIconStrip). |
| faceIconStrip | user-data/GG4E/afs_data/root/fmg00_mdl.arc (texture_000) | unknown | low | no | Small icon strip from the face-marker model atlas. |

as_icon public export: /ui/tpl/as_icon/image_00_CI8.png (exists). It remains unwired in BattleHud because the HUD manifest classifies its battle-HUD role as low-confidence.

arrow_mdl geometry binding: source archive exists, HSDRaw OBJ exists, generated module exists, runtime scene uses geometry yes (84 verts, 72 tris).

Original HUD elements not available as discrete sprites:
| Element | Evidence |
| --- | --- |
| energyBarFill | GAME-DRAWN. No texture. The green/red energy meter is runtime geometry filled with vertex color; render as a colored quad. |
| energyBarFrame | GAME-DRAWN. No texture. Meter frame is geometry, not a sprite. |
| hpGaugeRing | GAME-DRAWN. No texture. The circular HP gauge ring is runtime geometry (arc/torus), not a sprite. |
| hpGaugeFill | GAME-DRAWN. No texture. The HP arc fill is vertex-colored geometry. |
| btnA | GAME-DRAWN / font. No discrete A button icon texture; button prompts are letters drawn from the font atlas, not glyph-shaped sprites. |
| btnB | GAME-DRAWN / font. See btnA. |
| btnX | GAME-DRAWN / font. See btnA. |
| btnY | GAME-DRAWN / font. See btnA. |
| reticle | GAME-DRAWN. arrow_mdl.arc (the lock-on arrow/target indicator) is HSD geometry with NO embedded texture; it is drawn as vertex-colored geometry. No reticle sprite exists. |
| labelAlly | GAME-DRAWN / font. 'ALLY' is text rendered from the font atlas, not a baked label sprite. |
| labelEnemy | GAME-DRAWN / font. 'ENEMY' is text from the font atlas. |
| labelCpu | GAME-DRAWN / font. 'CPU' is text from the font atlas. |
| alert | GAME-DRAWN / font. The '!' alert is a font glyph, not a dedicated sprite. |
| comboDigits | Use font_ascii_atlas.png (or font_jp_atlas.png) digit cells; no pre-baked combo-number sprite sheet exists. |

## Common Battle Archive Evidence

Inventory: research/asset-inventory/pzz-arz-inventory.json
cmn_data.bin exists unpacked: no
cmn_data.pzz: user-data/GG4E/afs_data/root/cmn_data.pzz; 4 members (4 compressed, 0 raw, 0 zero), valid block sum true.
Recognized member kinds: unknown-binary:3, mot-bank-container:1.

| Member | Name | Table | Blocks | Compression | Payload | Kind | MOT banks | Matched source |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 000 | comhit.bin | 0x40000003 | 3 | pzzp | 21504 | unknown-binary |  | user-data/GG4E/afs_data/root/comhit.bin |
| 001 | comhit2.bin | 0x40000001 | 1 | pzzp | 15680 | unknown-binary |  | user-data/GG4E/afs_data/root/comhit2.bin |
| 002 | cmn_data.member002.mot-bank-container | 0x400000aa | 170 | pzzp | 437888 | mot-bank-container | b0:13, b1:15, b2:14, b3:1, b4:0, b5:2 (45 unique clips) | none |
| 003 | cmn_data.member003.unknown-binary | 0x40000001 | 1 | pzzp | 864 | unknown-binary |  | none |

Member 003 numeric probes: halfwords 0x01f4, 0x0064, 0x2710, 0x0000, 0x07d0, 0x0000, 0x0000, 0x0000; f32 words 0, 0, 0, 0, 0, 0. These are byte-level probes only, not named fields.

cmn_data is present as a PZZ archive and now inventoried at member-table level. Treat its contents as common battle/HUD candidate data until DOL/runtime traces map consumers and field semantics.

## Common Battle Data Evidence

Inventory: research/asset-inventory/common-battle-data.json
Source: member 003 from user-data/GG4E/afs_data/root/cmn_data.pzz; 864 bytes.
Actor data reference files: 198 (432 bytes each).

| Record | Offset | SHA1 | Non-zero | First halfwords | First f32 probes |
| --- | --- | --- | --- | --- | --- |
| 0 | 0x0000 | a397fd9ce9a186e3caf0daa3ee9dc22895e23794 | 245 | 0x01f4 0x0064 0x2710 0x0000 0x07d0 0x0000 0x0000 0x0000 | 0 0 0 0 0 0 6 5.5 |
| 1 | 0x01b0 | e15dedd41ca34460a54b07928e0ee40388235739 | 222 | 0x01f4 0x0064 0x2710 0x0000 0x07d0 0x0000 0x0000 0x0000 | 0 0 0 0 0 0 5 2.5 |

| Record | Actor data | Borg | Stats |
| --- | --- | --- | --- |
| 0 | user-data/GG4E/afs_data/root/pl0f05data.bin | pl0f05 ROACH | GF 30, HP 60/78, shot 1, attack 0, speed 2 |
| 1 | user-data/GG4E/afs_data/root/pl0f06data.bin | pl0f06 DEATH EYE | GF 10, HP 30/48, shot 1, attack 0, speed 2 |

cmn_data.pzz member 003 cleanly splits into 432-byte records, the same stride as pl####data.bin actor data. defense/shot/attack/speed are now exact-mapped actor-data bytes and runtime-bound; the remaining common-record fields still require DOL/runtime trace or HexWorkshop bookmark correlation.

Actor-data combat-stat offsets:
defense/shot/attack/speed are exact unsigned-byte matches at pl####data.bin offsets 0x1a4..0x1a7 for every actor-data file that has borgs.json metadata.

Runtime binding:
- App imports borgs.json: yes (apps/game/src/main.ts:23)
- Generated actor-data stats JSON: yes (packages/combat/src/data/actorDataStats.json)
- Combat buildProfile consumes actor-data stats: yes (packages/combat/src/stats.ts:108)
- Combat buildProfile consumes stats: yes (packages/combat/src/stats.ts:108)
- Combat formulas still marked tuned: yes (packages/combat/src/constants.ts:28)
- Generic PZZ package parser implemented: yes (packages/formats/src/pzz.ts:103)
Runtime combat profiles now bind defense/shot/attack/speed to original pl####data.bin actor-data bytes via packages/combat/src/data/actorDataStats.json. Energy, HP, jump, and the absolute damage coefficients still use the existing roster/tuned formula path until their binary fields or formula consumers are proven.

Type damage matrix:
- Generated from DOL tables: yes (packages/combat/src/typeDamage.generated.ts:720)
- Runtime imports generated tables: yes (packages/combat/src/typeDamage.ts:11)
- Damage pipeline uses multiplier: yes (packages/combat/src/combat.ts:88)
- Shape: remap 16 rows; matrix 20x20; mapped borg ids 208.
- Selfcheck covers sample multiplier: yes.

Knockback direction:
- Generated from DOL function evidence: yes (packages/physics/src/knockback.generated.ts:7)
- Runtime imports generated constants: yes (packages/physics/src/knockback.ts:58)
- Combat pipeline uses direction helper: yes (packages/combat/src/combat.ts:12)
- Shape/constants: 5 modes; BAM16/radian 10430.3779296875; degenerate threshold 0.009999999776482582.

Battle camera mode-1 blend:
- Generated from boot.dol/decomp: yes (apps/game/src/sim/camera.generated.ts:6)
- Runtime imports generated constants: yes (apps/game/src/sim/camera.ts:40)
- Runtime uses mode-1 blend: yes.
- Shape/constants: eye previous weight 4; denominator 5; half blend 0.5.

## Borg Animation Coverage

Validator report: research/asset-inventory/borg-animation-action-gaps.md
Runtime resolver refs: apps/game/src/main.ts:384, apps/game/src/main.ts:423, apps/game/src/main.ts:635, apps/game/src/sim/battleScene.ts:140
Animation indexes parsed: 108/108; exported banks: 4894; canonical slot checks: 1404.
Direct matches: 1402; fallbacks: 2; missing: 0; parse errors: 0.
Fly/boost mapping: fly state resolves through exported boost labels.

| Slot | Direct | Fallback | Missing | Notes |
| --- | --- | --- | --- | --- |
| idle | 108 | 0 | 0 | none |
| move | 108 | 0 | 0 | none |
| dash_fwd | 108 | 0 | 0 | none |
| dash_back | 108 | 0 | 0 | none |
| dash_left | 108 | 0 | 0 | none |
| dash_right | 108 | 0 | 0 | none |
| jump | 108 | 0 | 0 | none |
| fly | 108 | 0 | 0 | none |
| shoot | 108 | 0 | 0 | none |
| melee | 108 | 0 | 0 | none |
| special | 108 | 0 | 0 | none |
| hit | 106 | 2 | 0 | idle -> idle x2 |
| death | 108 | 0 | 0 | none |

## Powerup / Item Runtime Gap

Items/powerups in BattleState: no
Runtime spawns item/drop/pickup entities: no
Evidence refs: packages/combat/src/types.ts:181, packages/combat/src/battle.ts:126, packages/combat/src/battle.ts:253, research/asset-inventory/particle-effect-inventory.json, research/asset-inventory/ui-hud-assets.md
Asset leads: item model ARZ count 90, as_icon documented yes, comhit documented yes.
Combat state has no item/drop/pickup collection yet. Do not add gameplay powerups until DOL/runtime evidence identifies drop tables and pickup effects; safest next asset work is HUD/icon/comhit inventory.

## Audio

Audio package dependency: yes
Runtime imports audio manager: yes
Runtime queues menu/battle BGM: yes
Runtime plays confirm/back/edit SFX: yes

| Cue | Exists |
| --- | --- |
| bgm00 | yes |
| bgm01 | yes |
| se00_00 | yes |
| se00_01 | yes |
| se00_02 | yes |

Manifest counts: {"bgm":33,"sfx":5,"voice":46}

## Challenge / Adventure / Story Risk

Runtime screen comments and flow are Challenge-oriented, while packages/assets/data/stages.json declares Story Mode data and adventure-flow inventory discusses Adventure. Do not use Story/Adventure mission rows as a verified Challenge stage/menu mapping.

- packages/assets/data/stages.json:3
- research/asset-inventory/adventure-flow-ai.json:78
- 9 audited runtime screens identify themselves as Challenge or in-battle Challenge UI.

## Next Replacements

- Trace and wire the original arena-name/Challenge rotation -> st## table; runtime now authorizes exported literal st## ids through a generated catalog, but untraced names still fall back to st00.
- Use the now-exported tl00/optn00/staff00/vsel00/vsel01/brif00/entry00/rpot20-23 scene models plus generated layout bounds to replace the remaining CSS/DOM menu surfaces.
- Replace ForceBuilder/SelectForce surfaces with unitall/plcmndata/allbox/gets-driven original layouts; they currently use real borg icons/banners inside handcoded DOM.
- Map remaining battle HUD from comhit/cmn_data/as_icon/font assets and DOL HUD state; arrow_mdl target geometry is now wired, while the center HUD reticle/gauges are still CSS/SVG.
- Resolve remaining borg animation fallbacks/misses from research/asset-inventory/borg-animation-action-gaps.md, especially missing move clips and fallback hit/death labels.

## Verification

```bash
rtk node scripts/audit-real-asset-coverage.mjs
rtk node -e "JSON.parse(require('fs').readFileSync('research/asset-coverage/real-asset-coverage.json','utf8')); console.log('asset coverage json ok')"
```
