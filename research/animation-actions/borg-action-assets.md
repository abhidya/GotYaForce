# Borg Action Animation Asset Inventory

Generated: 2026-07-01T03:54:47.986Z
Script: `scripts/inventory-borg-action-assets.mjs`

This is an inventory pipeline, not gameplay behavior. Action rows are candidates backed by exported/source assets.

## Summary

| Metric | Count |
|---|---:|
| Borg records | 219 |
| Source models | 207 |
| Source MOT files | 104 |
| Exported models | 1 |
| Exported anim indexes | 105 |
| Exported indexed clips | 4709 |
| Source MOT structural clips | 4433 |
| PZZ member records joined | 2926 |
| Borgs with PZZ member records | 209 |
| Borgs with PZZ motion-bank members | 185 |
| Borgs with PZZ hit-data members | 209 |
| Borgs with PZZ model members | 209 |
| Borgs with PZZ texture members | 208 |

## Action Coverage

| Action | Borgs with exported candidate |
|---|---:|
| `idle` | 105 |
| `walk/run` | 102 |
| `jump` | 102 |
| `fly/air` | 102 |
| `dash` | 102 |
| `shoot/gun` | 96 |
| `beam` | 5 |
| `melee/sword` | 97 |
| `hit` | 93 |
| `death` | 94 |
| `spawn` | 105 |

## Priority Borgs

### pl0615 G RED

- Source model: `user-data/GG4E/afs_data/root/pl0615_mdl.arc`
- Source MOT: `user-data/GG4E/afs_data/root/pl0615mot.bin`
- PZZ source members: 14 (hsd-model 6, texture 4, borg-data 1, empty-slot 1, hit-collision-data 1, motion-bank 1)
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
- PZZ source members: 14 (hsd-model 6, texture 4, borg-data 1, empty-slot 1, hit-collision-data 1, motion-bank 1)
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

| Borg | Name | Source MOT | PZZ MOT | Anim index | Clips | Missing exported action candidates |
|---|---|---:|---:|---:|---:|---|
| `pl0615` | G RED | yes | yes | yes | 55 | beam |
| `pl0109` | DEATH BORG BETA | yes | yes | yes | 41 | shoot/gun, beam |
| `pl0000` | NORMAL NINJA | yes | yes | yes | 56 | beam |
| `pl0001` | SHURIKEN NINJA | yes | yes | yes | 50 | beam |
| `pl0002` | ARROW NINJA | yes | yes | yes | 56 | beam |
| `pl0003` | DOUBLE NINJA | no | yes | yes | 56 | beam |
| `pl0004` | ACCELERATION NINJA | yes | yes | yes | 51 | beam |
| `pl0005` | TELEPORT NINJA | yes | yes | yes | 53 | beam |
| `pl0006` | FLAME NINJA | yes | yes | yes | 51 | beam |
| `pl0007` | CYBER NINJA | yes | yes | yes | 61 | beam |
| `pl0008` | DEATH BORG ALPHA | yes | yes | yes | 56 | beam |
| `pl0009` | SWITCHING NINJA | yes | yes | yes | 32 | beam |
| `pl000a` | SASUKE | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl000b` | SHIJIMA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl000c` | DEATH BORG ALPHA II | yes | yes | yes | 56 | beam |
| `pl0100` | REVOLVER GUNMAN | yes | yes | yes | 64 | beam |
| `pl0101` | POWERED GUNMAN | yes | yes | yes | 64 | beam |
| `pl0102` | GATLING GUNNER | yes | yes | yes | 68 | beam |
| `pl0103` | WIRE GUNNER | yes | yes | yes | 73 | beam |
| `pl0104` | BEAM GUNNER | yes | yes | yes | 71 | none |
| `pl0105` | DEATH BORG BETA II | yes | yes | yes | 64 | beam |
| `pl0106` | TIME BOMBER | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0107` | REMOTE BOMBER | yes | yes | yes | 68 | beam |
| `pl0108` | BILLY | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl010a` | DEATH BORG BETA III | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0200` | SWORD KNIGHT | yes | yes | yes | 35 | beam |
| `pl0201` | CHAINSAW KNIGHT | yes | yes | yes | 39 | shoot/gun, beam |
| `pl0202` | ELEMENTAL KNIGHT | yes | yes | yes | 43 | beam |
| `pl0203` | SPIKE KNIGHT | yes | yes | yes | 39 | beam |
| `pl0204` | AXE KNIGHT | yes | yes | yes | 39 | beam |
| `pl0205` | DARK KNIGHT | yes | yes | yes | 40 | beam |
| `pl0206` | DEATH BORG GAMMA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0207` | ALIEN INSECT | yes | yes | yes | 41 | beam |
| `pl0208` | SAPPHIRE KNIGHT | yes | yes | yes | 55 | beam |
| `pl0209` | IMPERIAL KNIGHT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020a` | NORMAL KNIGHT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020b` | GHOST KNIGHT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020c` | HAMMER KNIGHT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020d` | HATCHET KNIGHT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl020e` | RUBY KNIGHT | yes | yes | yes | 51 | beam |
| `pl020f` | DEATH BORG GAMMA II | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0300` | BATTLE GIRL | yes | yes | yes | 47 | beam |
| `pl0301` | WIRE GIRL | yes | yes | yes | 48 | beam |
| `pl0302` | BARRIER GIRL | yes | yes | yes | 49 | beam |
| `pl0303` | DEATH BORG DELTA II | yes | yes | yes | 50 | beam |
| `pl0304` | KILLER GIRL | yes | yes | yes | 50 | beam |
| `pl0305` | CYBER GIRL SUPER | yes | yes | yes | 50 | beam |
| `pl0306` | COMMAND GIRL | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0307` | SPINNER GIRL | yes | yes | yes | 53 | beam |
| `pl0308` | SHADOW GIRL | yes | yes | yes | 49 | shoot/gun, beam |
| `pl0309` | CYBER GIRL | yes | yes | yes | 47 | beam |
| `pl030a` | CYBER GIRL HYPER | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl030b` | KEI | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl030c` | DEATH BORG DELTA | yes | yes | yes | 48 | shoot/gun, beam |
| `pl030d` | DEATH BORG DELTA III | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0400` | CLAW ROBOT | yes | yes | yes | 31 | beam |
| `pl0401` | DRILL ROBOT | yes | yes | yes | 34 | beam |
| `pl0402` | BUILD ROBOT | yes | yes | yes | 33 | beam |
| `pl0403` | HAMMER ROBOT | yes | yes | yes | 31 | beam |
| `pl0404` | THUNDER ROBOT | yes | yes | yes | 31 | beam |
| `pl0405` | MAGNET ROBOT (+) | yes | yes | yes | 33 | beam |
| `pl0406` | DEATH BORG OMEGA | yes | yes | yes | 31 | shoot/gun, beam |
| `pl0407` | MEGATON ROBOT | yes | yes | yes | 34 | beam |
| `pl0408` | ARMY ROBOT | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0409` | MAGNET ROBOT (-) | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040a` | ISAAC | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040b` | DEATH BORG OMEGA II | yes | yes | yes | 32 | beam |
| `pl040c` | DEATH BORG OMEGA III | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl040d` | DEATH BORG OMEGA IV | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0500` | FLAME DRAGON | yes | yes | yes | 33 | beam, death |
| `pl0501` | ALIEN WORM | yes | yes | yes | 38 | beam |
| `pl0502` | PHOENIX DRAGON | yes | yes | yes | 37 | beam |
| `pl0503` | CYBER DEATH DRAGON | yes | yes | yes | 36 | beam, death |
| `pl0504` | COSMIC DRAGON | yes | yes | yes | 45 | beam, death |
| `pl0505` | DEATH HEAD | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0506` | CYBER DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0507` | CYBER DEATH DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0508` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0509` | PLASMA DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050a` | BLIZZARD DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050b` | VENOM WORM | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050c` | FIRE DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050d` | CLAW WORM | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050e` | WING DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl050f` | MACHINE DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0510` | SPACE DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0511` | MACHINE HEAD | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0512` | MECHANICAL DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0513` | MACHINE DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0514` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0515` | THUNDER DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0516` | ICE DRAGON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0517` | POISON WORM | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0600` | MACHINE RED | yes | yes | yes | 42 | beam |
| `pl0601` | MACHINE BLUE | yes | yes | yes | 68 | beam |
| `pl0602` | CYBER MACHINE SEIRYU | yes | yes | yes | 42 | beam |
| `pl0603` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0604` | TITAN ROBOT | yes | yes | yes | 45 | beam, hit |
| `pl0606` | EAGLE ROBOT | yes | yes | yes | 38 | beam |
| `pl0608` | CYBER MARS | yes | yes | yes | 42 | beam |
| `pl0609` | CYBER ATLAS | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060a` | CYBER MACHINE SUZAKU | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060b` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060c` | CYBER MACHINE BYAKKO | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060d` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060e` | CYBER MACHINE GENBU | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl060f` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0610` | VICTORY KING | yes | yes | yes | 53 | beam, hit |
| `pl0613` | PANTHER ROBOT | yes | yes | yes | 40 | beam, hit |
| `pl0616` | PROTO RED | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0617` | PROTO BLUE | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0618` | PROTO TITAN | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0619` | TITAN TANK | yes | yes | yes | 26 | walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death |
| `pl061a` | PROTO EAGLE | yes | yes | yes | 38 | beam |
| `pl061b` | EAGLE JET | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061c` | PROTO MARS | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061d` | PROTO ATLAS | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061e` | PROTO KING | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl061f` | VICTORY TANK | yes | yes | yes | 39 | walk/run, jump, fly/air, dash, beam, melee/sword, hit, death |
| `pl0620` | VICTORY JET | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0621` | VICTORY DUKE | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0623` | VICTORY BARON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0625` | VICTORY MACHINE | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0627` | PROTO PANTHER | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0628` | PANTHER VEHICLE | yes | yes | yes | 25 | walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death |
| `pl0629` | NEO G RED | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl062a` | G BLACK | yes | yes | yes | 58 | beam |
| `pl0700` | NORMAL SAMURAI | yes | yes | yes | 32 | beam |
| `pl0701` | DEMON SAMURAI | yes | yes | yes | 33 | beam |
| `pl0702` | VAMPIRE KNIGHT | yes | yes | yes | 32 | beam |
| `pl0703` | SONIC SAMURAI | yes | yes | yes | 32 | beam |
| `pl0704` | SAMURAI SHOGUN | yes | yes | yes | 32 | beam |
| `pl0705` | DEATH BORG ZETA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0706` | BEAM SAMURAI | yes | yes | yes | 32 | none |
| `pl0707` | CHRONO SAMURAI | yes | yes | yes | 28 | beam |
| `pl0708` | AKUMA SAMURAI | yes | yes | yes | 32 | beam |
| `pl0709` | MUSASHI | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070a` | VLAD | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070b` | DEATH BORG ZETA II | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070c` | DEATH BORG ZETA III | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl070d` | DEATH BORG ZETA IV | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0800` | KUNG-FU MASTER | yes | yes | yes | 33 | beam |
| `pl0801` | TAO MASTER | yes | yes | yes | 34 | beam |
| `pl0802` | GOLD HERO | yes | yes | yes | 54 | beam |
| `pl0803` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0804` | STAR HERO | yes | yes | yes | 43 | beam |
| `pl0805` | JELLY DIVER | yes | yes | yes | 56 | beam |
| `pl0806` | COPY MAN | yes | yes | yes | 35 | beam |
| `pl0807` | DEATH BORG TAU | yes | yes | yes | 33 | shoot/gun, beam |
| `pl0808` | CYBER HERO | yes | yes | yes | 42 | beam, hit |
| `pl0809` | WALKING BOMB | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080a` | METAL HERO | yes | yes | yes | 45 | shoot/gun, beam |
| `pl080b` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080c` | PLANET HERO | yes | yes | yes | 41 | beam |
| `pl080d` | TAR DIVER | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080e` | JACK | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl080f` | DEATH BORG OMICRON | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0900` | ANGEL NURSE | yes | yes | yes | 32 | beam |
| `pl0901` | BUG WITCH | yes | yes | yes | 34 | beam |
| `pl0902` | PATRA WITCH | yes | yes | yes | 34 | beam |
| `pl0903` | GUARD WITCH | yes | yes | yes | 32 | beam |
| `pl0904` | POP HONEY | yes | yes | yes | 34 | beam |
| `pl0905` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0906` | DEATH BORG THETA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0907` | BASTET WITCH | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0908` | ANGEL RESCUE | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0909` | ISIS WITCH | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090a` | SHIELD WITCH | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090b` | DEATH BORG IOTA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090c` | SEKHMET WITCH | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl090d` | NAO | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a00` | WING SOLDIER | yes | yes | yes | 72 | beam |
| `pl0a01` | JET HERO | yes | yes | yes | 74 | beam |
| `pl0a02` | DEMON WING | yes | yes | yes | 61 | beam |
| `pl0a03` | BEAM WING BLUE | yes | yes | yes | 78 | none |
| `pl0a04` | ANUBIS WING | yes | yes | yes | 74 | beam |
| `pl0a05` | DEATH BORG SIGMA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a06` | BEAM WING RED | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a07` | DEATH WING | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a08` | BLADE WING | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a09` | GARUDA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0a0a` | DEATH BORG SIGMA II | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0b00` | QUICK VALKRIE | yes | yes | yes | 58 | beam |
| `pl0b01` | ICE VALKRIE | yes | yes | yes | 54 | beam |
| `pl0b02` | TORNADO VALKRIE | yes | yes | yes | 54 | beam |
| `pl0b03` | WIND VALKRIE | yes | yes | yes | 58 | beam |
| `pl0b04` | RING VALKRIE | yes | yes | yes | 54 | beam |
| `pl0b05` | DEATH BORG LAMBDA | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0b06` | SLOW VALKRIE | yes | yes | yes | 58 | beam |
| `pl0b07` | DEATH BORG LAMBDA II | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0c00` | NORMAL TANK | yes | yes | yes | 26 | beam, melee/sword, hit, death |
| `pl0c01` | GATLING TANK | yes | yes | yes | 27 | beam, melee/sword, hit, death |
| `pl0c02` | BEAM TANK | yes | yes | yes | 26 | melee/sword, hit, death |
| `pl0c03` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0c04` | ULTIMATE CANNON | yes | yes | yes | 20 | melee/sword, hit, death |
| `pl0c05` | ICBM TANK | yes | yes | yes | 26 | beam, melee/sword, hit, death |
| `pl0c06` | LEOPARD | no | yes | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d00` | BLUE STRIKER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d01` | RED ATTACKER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d02` | CARRIER HELICOPTER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d03` | FLYING SAUCER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d04` | ORANGE FIGHTER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d05` | VIOLET ATTACKER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d06` | DEATH ICBM | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0d07` | DEATH BOMB | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e00` | SIRIUS | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e01` | BEAM SATELLITE | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e02` | DEATH SAUCER | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e03` | ANTARES | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e04` | GALACTIC EMPEROR | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0e05` | DEATH ARC | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f00` | DEATH BORG MU | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f01` | DEATH BORG NU | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f02` | DEATH BORG NU II | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f03` | DEATH BORG NU III | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f04` | DEATH BORG CHI | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f05` | ROACH | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f06` | DEATH EYE | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |
| `pl0f07` |  | no | no | no | 0 | idle, walk/run, jump, fly/air, dash, shoot/gun, beam, melee/sword, hit, death, spawn |

## Reproduce

```bash
rtk node scripts/inventory-borg-action-assets.mjs
```
