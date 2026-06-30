# Borg Action Animation Asset Inventory

Generated: 2026-06-30T22:48:33.868Z
Script: `scripts/inventory-borg-action-assets.mjs`

This is an inventory pipeline, not gameplay behavior. Action rows are candidates backed by exported/source assets.

## Summary

| Metric | Count |
|---|---:|
| Borg records | 219 |
| Source models | 207 |
| Source MOT files | 102 |
| Exported models | 1 |
| Exported anim indexes | 102 |
| Exported indexed clips | 4541 |
| Source MOT structural clips | 4321 |

## Action Coverage

| Action | Borgs with exported candidate |
|---|---:|
| `idle` | 102 |
| `walk/run` | 99 |
| `jump` | 99 |
| `fly/air` | 99 |
| `dash` | 99 |
| `shoot/gun` | 93 |
| `beam` | 5 |
| `melee/sword` | 94 |
| `hit` | 90 |
| `death` | 91 |
| `spawn` | 102 |

## Priority Borgs

### pl0615 G RED

- Source model: `user-data/GG4E/afs_data/root/pl0615_mdl.arc`
- Source MOT: `user-data/GG4E/afs_data/root/pl0615mot.bin`
- Exported anim index: `apps/game/public/models/pl0615/anim_index.json`
- Exported indexed clips: 55
- Source MOT structural clips: 55

| Action | Candidate clips | Evidence |
|---|---|---|
| `idle` | `idle` `g0s0` 61f | exported label is idle |
| `walk/run` | `move` `g0s1` 33f | exported label is move |
| `jump` | `jump_takeoff` `g0s6` 11f<br>`jump_land` `g0s7` 11f | exported label is jump_takeoff |
| `fly/air` | `fly_transition` `g0s9` 21f<br>`boost` `g0s23` 37f | exported label is fly_transition |
| `dash` | `dash_fwd` `g0s2` 25f<br>`dash_back` `g0s3` 25f<br>`dash_left` `g0s4` 25f<br>`dash_right` `g0s5` 25f<br>`boost` `g0s23` 37f | exported label is dash_fwd |
| `shoot/gun` | `attack_s4` `g1s4` 41f<br>`attack_s5` `g1s5` 41f<br>`attack_s6` `g1s6` 56f<br>`attack_s7` `g1s7` 31f<br>`attack_s8` `g1s8` 46f | attack clip plus ranged metadata (G RED, Machine Borg, Almighty type, shot 4, attack 4) |
| `beam` | none |  |
| `melee/sword` | `attack_lunge_s1` `g1s1` 28f<br>`attack_lunge_s2` `g1s2` 36f<br>`attack_lunge_s3` `g1s3` 51f<br>`attack_lunge_s16` `g1s16` 36f<br>`attack_s4` `g1s4` 41f | exported lunge attack label is attack_lunge_s1 |
| `hit` | `hit_react_s0` `g3s0` 12f<br>`hit_react_s1` `g3s1` 12f<br>`hit_react_s2` `g3s2` 12f<br>`hit_react_s5` `g3s5` 12f<br>`hit_react_s6` `g3s6` 12f | exported label is hit_react_s0 |
| `death` | `death` `g5s1` 181f | exported label is death |
| `spawn` | `pose_short` `g0s14` 2f<br>`pose_short` `g0s24` 2f<br>`idle` `g0s0` 61f | exported label is pose_short |

Notes: no exported candidate for: beam; 10 exported anim JSON files are not listed in anim_index.json

### pl0109 DEATH BORG BETA

- Source model: `user-data/GG4E/afs_data/root/pl0109_mdl.arc`
- Source MOT: `user-data/GG4E/afs_data/root/pl0109mot.bin`
- Exported anim index: `apps/game/public/models/pl0109/anim_index.json`
- Exported indexed clips: 41
- Source MOT structural clips: 41

| Action | Candidate clips | Evidence |
|---|---|---|
| `idle` | `idle` `g0s0` 117f | exported label is idle |
| `walk/run` | `move` `g0s1` 33f<br>`move_s15` `g0s15` 11f<br>`move_s16` `g0s16` 38f | exported label is move |
| `jump` | `jump_takeoff` `g0s6` 12f<br>`jump_land` `g0s7` 12f | exported label is jump_takeoff |
| `fly/air` | `fly_transition` `g0s9` 22f<br>`boost` `g0s23` 23f | exported label is fly_transition |
| `dash` | `dash_fwd` `g0s2` 37f<br>`dash_back` `g0s3` 37f<br>`dash_left` `g0s4` 37f<br>`dash_right` `g0s5` 37f<br>`boost` `g0s23` 23f | exported label is dash_fwd |
| `shoot/gun` | none |  |
| `beam` | none |  |
| `melee/sword` | `attack_lunge_s1` `g1s1` 32f<br>`attack_lunge_s2` `g1s2` 40f<br>`attack_lunge_s3` `g1s3` 42f<br>`attack_lunge_s4` `g1s4` 36f<br>`attack_lunge_s5` `g1s5` 49f | exported lunge attack label is attack_lunge_s1 |
| `hit` | `guard_s11` `g3s11` 19f<br>`guard_s12` `g3s12` 30f<br>`guard_s19` `g3s19` 19f | exported label is guard_s11 |
| `death` | `death` `g5s1` 161f<br>`win_or_death` `g5s0` 71f | exported label is death |
| `spawn` | `pose_short` `g0s14` 2f<br>`pose_short` `g0s24` 2f<br>`idle` `g0s0` 117f | exported label is pose_short |

Notes: no exported candidate for: shoot/gun, beam; 2 exported anim JSON files are not listed in anim_index.json

## All Borgs

| Borg | Name | Source MOT | Anim index | Clips | Missing exported action candidates |
|---|---|---:|---:|---:|---|
| `pl0615` | G RED | yes | yes | 55 | beam |
| `pl0109` | DEATH BORG BETA | yes | yes | 41 | shoot/gun, beam |
| `pl0000` | NORMAL NINJA | yes | yes | 56 | beam |
| `pl0001` | SHURIKEN NINJA | yes | yes | 50 | beam |
| `pl0002` | ARROW NINJA | yes | yes | 56 | beam |
| `pl0003` | DOUBLE NINJA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0004` | ACCELERATION NINJA | yes | yes | 51 | beam |
| `pl0005` | TELEPORT NINJA | yes | yes | 53 | beam |
| `pl0006` | FLAME NINJA | yes | yes | 51 | beam |
| `pl0007` | CYBER NINJA | yes | yes | 61 | beam |
| `pl0008` | DEATH BORG ALPHA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0009` | SWITCHING NINJA | yes | yes | 32 | beam |
| `pl000a` | SASUKE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl000b` | SHIJIMA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl000c` | DEATH BORG ALPHA II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0100` | REVOLVER GUNMAN | yes | yes | 64 | beam |
| `pl0101` | POWERED GUNMAN | yes | yes | 64 | beam |
| `pl0102` | GATLING GUNNER | yes | yes | 68 | beam |
| `pl0103` | WIRE GUNNER | yes | yes | 73 | beam |
| `pl0104` | BEAM GUNNER | yes | yes | 71 | none |
| `pl0105` | DEATH BORG BETA II | yes | yes | 64 | beam |
| `pl0106` | TIME BOMBER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0107` | REMOTE BOMBER | yes | yes | 68 | beam |
| `pl0108` | BILLY | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl010a` | DEATH BORG BETA III | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0200` | SWORD KNIGHT | yes | yes | 35 | beam |
| `pl0201` | CHAINSAW KNIGHT | yes | yes | 39 | shoot/gun, beam |
| `pl0202` | ELEMENTAL KNIGHT | yes | yes | 43 | beam |
| `pl0203` | SPIKE KNIGHT | yes | yes | 39 | beam |
| `pl0204` | AXE KNIGHT | yes | yes | 39 | beam |
| `pl0205` | DARK KNIGHT | yes | yes | 40 | beam |
| `pl0206` | DEATH BORG GAMMA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0207` | ALIEN INSECT | yes | yes | 41 | beam |
| `pl0208` | SAPPHIRE KNIGHT | yes | yes | 55 | beam |
| `pl0209` | IMPERIAL KNIGHT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020a` | NORMAL KNIGHT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020b` | GHOST KNIGHT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020c` | HAMMER KNIGHT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020d` | HATCHET KNIGHT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020e` | RUBY KNIGHT | yes | yes | 51 | beam |
| `pl020f` | DEATH BORG GAMMA II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0300` | BATTLE GIRL | yes | yes | 47 | beam |
| `pl0301` | WIRE GIRL | yes | yes | 48 | beam |
| `pl0302` | BARRIER GIRL | yes | yes | 49 | beam |
| `pl0303` | DEATH BORG DELTA II | yes | yes | 50 | beam |
| `pl0304` | KILLER GIRL | yes | yes | 50 | beam |
| `pl0305` | CYBER GIRL SUPER | yes | yes | 50 | beam |
| `pl0306` | COMMAND GIRL | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0307` | SPINNER GIRL | yes | yes | 53 | beam |
| `pl0308` | SHADOW GIRL | yes | yes | 49 | shoot/gun, beam |
| `pl0309` | CYBER GIRL | yes | yes | 47 | beam |
| `pl030a` | CYBER GIRL HYPER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl030b` | KEI | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl030c` | DEATH BORG DELTA | yes | yes | 48 | shoot/gun, beam |
| `pl030d` | DEATH BORG DELTA III | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0400` | CLAW ROBOT | yes | yes | 31 | beam |
| `pl0401` | DRILL ROBOT | yes | yes | 34 | beam |
| `pl0402` | BUILD ROBOT | yes | yes | 33 | beam |
| `pl0403` | HAMMER ROBOT | yes | yes | 31 | beam |
| `pl0404` | THUNDER ROBOT | yes | yes | 31 | beam |
| `pl0405` | MAGNET ROBOT (+) | yes | yes | 33 | beam |
| `pl0406` | DEATH BORG OMEGA | yes | yes | 31 | shoot/gun, beam |
| `pl0407` | MEGATON ROBOT | yes | yes | 34 | beam |
| `pl0408` | ARMY ROBOT | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0409` | MAGNET ROBOT (-) | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040a` | ISAAC | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040b` | DEATH BORG OMEGA II | yes | yes | 32 | beam |
| `pl040c` | DEATH BORG OMEGA III | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040d` | DEATH BORG OMEGA IV | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0500` | FLAME DRAGON | yes | yes | 33 | beam, death |
| `pl0501` | ALIEN WORM | yes | yes | 38 | beam |
| `pl0502` | PHOENIX DRAGON | yes | yes | 37 | beam |
| `pl0503` | CYBER DEATH DRAGON | yes | yes | 36 | beam, death |
| `pl0504` | COSMIC DRAGON | yes | yes | 45 | beam, death |
| `pl0505` | DEATH HEAD | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0506` | CYBER DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0507` | CYBER DEATH DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0508` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0509` | PLASMA DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050a` | BLIZZARD DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050b` | VENOM WORM | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050c` | FIRE DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050d` | CLAW WORM | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050e` | WING DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050f` | MACHINE DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0510` | SPACE DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0511` | MACHINE HEAD | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0512` | MECHANICAL DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0513` | MACHINE DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0514` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0515` | THUNDER DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0516` | ICE DRAGON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0517` | POISON WORM | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0600` | MACHINE RED | yes | yes | 42 | beam |
| `pl0601` | MACHINE BLUE | yes | yes | 68 | beam |
| `pl0602` | CYBER MACHINE SEIRYU | yes | yes | 42 | beam |
| `pl0603` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0604` | TITAN ROBOT | yes | yes | 45 | beam, hit |
| `pl0606` | EAGLE ROBOT | yes | yes | 38 | beam |
| `pl0608` | CYBER MARS | yes | yes | 42 | beam |
| `pl0609` | CYBER ATLAS | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060a` | CYBER MACHINE SUZAKU | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060b` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060c` | CYBER MACHINE BYAKKO | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060d` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060e` | CYBER MACHINE GENBU | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060f` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0610` | VICTORY KING | yes | yes | 53 | beam, hit |
| `pl0613` | PANTHER ROBOT | yes | yes | 40 | beam, hit |
| `pl0616` | PROTO RED | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0617` | PROTO BLUE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0618` | PROTO TITAN | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0619` | TITAN TANK | yes | yes | 26 | walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death |
| `pl061a` | PROTO EAGLE | yes | yes | 38 | beam |
| `pl061b` | EAGLE JET | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061c` | PROTO MARS | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061d` | PROTO ATLAS | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061e` | PROTO KING | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061f` | VICTORY TANK | yes | yes | 39 | walk/run, jump, fly/air, dash, beam, melee/sword, hit, death |
| `pl0620` | VICTORY JET | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0621` | VICTORY DUKE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0623` | VICTORY BARON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0625` | VICTORY MACHINE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0627` | PROTO PANTHER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0628` | PANTHER VEHICLE | yes | yes | 25 | walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death |
| `pl0629` | NEO G RED | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl062a` | G BLACK | yes | yes | 58 | beam |
| `pl0700` | NORMAL SAMURAI | yes | yes | 32 | beam |
| `pl0701` | DEMON SAMURAI | yes | yes | 33 | beam |
| `pl0702` | VAMPIRE KNIGHT | yes | yes | 32 | beam |
| `pl0703` | SONIC SAMURAI | yes | yes | 32 | beam |
| `pl0704` | SAMURAI SHOGUN | yes | yes | 32 | beam |
| `pl0705` | DEATH BORG ZETA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0706` | BEAM SAMURAI | yes | yes | 32 | none |
| `pl0707` | CHRONO SAMURAI | yes | yes | 28 | beam |
| `pl0708` | AKUMA SAMURAI | yes | yes | 32 | beam |
| `pl0709` | MUSASHI | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070a` | VLAD | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070b` | DEATH BORG ZETA II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070c` | DEATH BORG ZETA III | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070d` | DEATH BORG ZETA IV | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0800` | KUNG-FU MASTER | yes | yes | 33 | beam |
| `pl0801` | TAO MASTER | yes | yes | 34 | beam |
| `pl0802` | GOLD HERO | yes | yes | 54 | beam |
| `pl0803` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0804` | STAR HERO | yes | yes | 43 | beam |
| `pl0805` | JELLY DIVER | yes | yes | 56 | beam |
| `pl0806` | COPY MAN | yes | yes | 35 | beam |
| `pl0807` | DEATH BORG TAU | yes | yes | 33 | shoot/gun, beam |
| `pl0808` | CYBER HERO | yes | yes | 42 | beam, hit |
| `pl0809` | WALKING BOMB | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080a` | METAL HERO | yes | yes | 45 | shoot/gun, beam |
| `pl080b` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080c` | PLANET HERO | yes | yes | 41 | beam |
| `pl080d` | TAR DIVER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080e` | JACK | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080f` | DEATH BORG OMICRON | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0900` | ANGEL NURSE | yes | yes | 32 | beam |
| `pl0901` | BUG WITCH | yes | yes | 34 | beam |
| `pl0902` | PATRA WITCH | yes | yes | 34 | beam |
| `pl0903` | GUARD WITCH | yes | yes | 32 | beam |
| `pl0904` | POP HONEY | yes | yes | 34 | beam |
| `pl0905` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0906` | DEATH BORG THETA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0907` | BASTET WITCH | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0908` | ANGEL RESCUE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0909` | ISIS WITCH | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090a` | SHIELD WITCH | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090b` | DEATH BORG IOTA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090c` | SEKHMET WITCH | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090d` | NAO | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a00` | WING SOLDIER | yes | yes | 72 | beam |
| `pl0a01` | JET HERO | yes | yes | 74 | beam |
| `pl0a02` | DEMON WING | yes | yes | 61 | beam |
| `pl0a03` | BEAM WING BLUE | yes | yes | 78 | none |
| `pl0a04` | ANUBIS WING | yes | yes | 74 | beam |
| `pl0a05` | DEATH BORG SIGMA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a06` | BEAM WING RED | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a07` | DEATH WING | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a08` | BLADE WING | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a09` | GARUDA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a0a` | DEATH BORG SIGMA II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0b00` | QUICK VALKRIE | yes | yes | 58 | beam |
| `pl0b01` | ICE VALKRIE | yes | yes | 54 | beam |
| `pl0b02` | TORNADO VALKRIE | yes | yes | 54 | beam |
| `pl0b03` | WIND VALKRIE | yes | yes | 58 | beam |
| `pl0b04` | RING VALKRIE | yes | yes | 54 | beam |
| `pl0b05` | DEATH BORG LAMBDA | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0b06` | SLOW VALKRIE | yes | yes | 58 | beam |
| `pl0b07` | DEATH BORG LAMBDA II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0c00` | NORMAL TANK | yes | yes | 26 | beam, melee/sword, hit, death |
| `pl0c01` | GATLING TANK | yes | yes | 27 | beam, melee/sword, hit, death |
| `pl0c02` | BEAM TANK | yes | yes | 26 | melee/sword, hit, death |
| `pl0c03` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0c04` | ULTIMATE CANNON | yes | yes | 20 | melee/sword, hit, death |
| `pl0c05` | ICBM TANK | yes | yes | 26 | beam, melee/sword, hit, death |
| `pl0c06` | LEOPARD | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d00` | BLUE STRIKER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d01` | RED ATTACKER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d02` | CARRIER HELICOPTER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d03` | FLYING SAUCER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d04` | ORANGE FIGHTER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d05` | VIOLET ATTACKER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d06` | DEATH ICBM | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d07` | DEATH BOMB | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e00` | SIRIUS | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e01` | BEAM SATELLITE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e02` | DEATH SAUCER | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e03` | ANTARES | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e04` | GALACTIC EMPEROR | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e05` | DEATH ARC | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f00` | DEATH BORG MU | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f01` | DEATH BORG NU | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f02` | DEATH BORG NU II | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f03` | DEATH BORG NU III | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f04` | DEATH BORG CHI | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f05` | ROACH | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f06` | DEATH EYE | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f07` |  | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |

## Reproduce

```bash
rtk node scripts/inventory-borg-action-assets.mjs
```
