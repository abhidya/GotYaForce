# Gotcha Force particle/effect format notes

Generated: 2026-07-01T03:42:49.855Z
Scanner: `scripts/inspect-particle-effects.mjs`

## Inputs

- `research/asset-inventory/weapons-effects-projectiles.json`
- `packages/assets/data/borgs.json`
- `user-data/GG4E/afs_data/root/efct*`
- `user-data/GG4E/afs_data/root/ptcl00.ptl`
- `user-data/GG4E/afs_data/root/ptcl00.ref`
- `user-data/GG4E/afs_data/root/ptcl00.txg`
- `user-data/GG4E/afs_data/root/it####_mdl.arz`
- `research/format-specs/*.md`

## Summary

- Direct particle/effect files scanned: 97
- it####_mdl.arz compressed item-model archives: 90
- Existing weapons/effects/projectiles candidates read: 1485
- Family group sizes: fire 48, beam 79, gun 294, sword 263, muzzle 292, impact 263, trail 255, reticle 13

## Confirmed byte-level observations

- `user-data/GG4E/afs_data/root/efct.pzz` (572.0 KiB): PZZ unpacked, 3 member(s), payload kinds hsd-dat:2, tpl-texture:1.
- `user-data/GG4E/afs_data/root/efct00_mdl.arc` (408.2 KiB): bare HSD DAT, root(s): scene_data.
- `user-data/GG4E/afs_data/root/efct00.tpl` (32.1 KiB): 1 TPL image, 256x64 RGB5A3.
- `user-data/GG4E/afs_data/root/efct01_mdl.arc` (398.7 KiB): bare HSD DAT, root(s): scene_data.
- `user-data/GG4E/afs_data/root/ptcl00.ptl` (2.3 KiB): 21 PTL records + 2 trailer byte(s); offset table recognized; record fields not fully decoded.
- `user-data/GG4E/afs_data/root/ptcl00.ref` (80 B): 20 REF u32 entries; u32 sequence table recognized.
- `user-data/GG4E/afs_data/root/ptcl00.txg` (15.1 KiB): 8 TXG textures; texture offset table and entry headers recognized.

### PTL
`ptcl00.ptl` has header word `0x00430000`, a count-like high word of 67, a sentinel at `0x5c`, and record data beginning at `0x60`.
The scanner sees 22 offsets before `0xffffffff`, 21 records of 16+ bytes, and 2 trailing byte(s). Record lengths observed: 2, 20, 72, 76, 104, 112, 120, 128, 144, 160 bytes.

### REF
`ptcl00.ref` is 20 big-endian u32 values and currently reads as a simple 0..19 sequence.

### TXG
`ptcl00.txg` has 8 texture entries. Every entry has one image and an exact payload-size match for its GC texture format.

| Index | Offset | Dimensions | Format | Payload |
|---:|---:|---:|---|---:|
| 0 | `0x0040` | 32x32 | I4 | 512 B |
| 1 | `0x0260` | 32x32 | RGB565 | 2.0 KiB |
| 2 | `0x0a80` | 16x16 | RGB565 | 512 B |
| 3 | `0x0ca0` | 32x32 | I8 | 1.0 KiB |
| 4 | `0x10c0` | 16x16 | I8 | 256 B |
| 5 | `0x11e0` | 16x16 | RGB565 | 512 B |
| 6 | `0x1400` | 32x32 | RGB565 | 2.0 KiB |
| 7 | `0x1c20` | 64x64 | RGB565 | 8.0 KiB |

## Family groups

### fire

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0500.pzz` | compressed archive | 928.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0500 (FLAME DRAGON) metadata contains flame / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl050c.pzz` | compressed archive | 928.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl050c (FIRE DRAGON) metadata contains fire / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0006.pzz` | compressed archive | 926.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0006 (FLAME NINJA) metadata contains flame / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0502.pzz` | compressed archive | 826.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0502 (PHOENIX DRAGON) metadata contains phoenix / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/efct.pzz` | shared effect PZZ archive | 572.0 KiB | Medium | efct prefix is the shared battle-effect asset group / Remaining work: map decompressed effect members to runtime HSD/effect semantics before driving sword/gun/projectile/powerup visuals. |
| `user-data/GG4E/afs_data/root/efct00_mdl.arc` | HSD effect model | 408.2 KiB | Medium | efct prefix is the shared battle-effect asset group |
| `user-data/GG4E/afs_data/root/efct01_mdl.arc` | HSD effect model | 398.7 KiB | Medium | efct prefix is the shared battle-effect asset group |
| `user-data/GG4E/afs_data/root/pl0006mot.bin` | animation/motion bank | 273.1 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0006 (FLAME NINJA) metadata contains flame / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0502mot.bin` | animation/motion bank | 242.8 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0502 (PHOENIX DRAGON) metadata contains phoenix / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0500mot.bin` | animation/motion bank | 241.6 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0500 (FLAME DRAGON) metadata contains flame / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0500_mdl.arc` | HSD model | 208.1 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0500 (FLAME DRAGON) metadata contains flame / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0500b_mdl.arc` | HSD model | 208.1 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0500 (FLAME DRAGON) metadata contains flame / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl050c_mdl.arc` | HSD model | 208.1 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl050c (FIRE DRAGON) metadata contains fire / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0006b_mdl.arc` | HSD model | 195.6 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0006 (FLAME NINJA) metadata contains flame / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |

### beam

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0a06.pzz` | compressed archive | 1.08 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a06 (BEAM WING RED) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a03.pzz` | compressed archive | 1.07 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a03 (BEAM WING BLUE) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0104.pzz` | compressed archive | 1.05 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0509.pzz` | compressed archive | 856.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0509 (PLASMA DRAGON) metadata contains plasma / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0706.pzz` | compressed archive | 776.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0706 (BEAM SAMURAI) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/efct.pzz` | shared effect PZZ archive | 572.0 KiB | Medium | efct prefix is the shared battle-effect asset group / Remaining work: map decompressed effect members to runtime HSD/effect semantics before driving sword/gun/projectile/powerup visuals. |
| `user-data/GG4E/afs_data/root/pl0e01.pzz` | compressed archive | 498.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0e01 (BEAM SATELLITE) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c02.pzz` | compressed archive | 452.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0c02 (BEAM TANK) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a03mot.bin` | animation/motion bank | 412.4 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a03 (BEAM WING BLUE) metadata contains beam / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/efct00_mdl.arc` | HSD effect model | 408.2 KiB | Medium | efct prefix is the shared battle-effect asset group |
| `user-data/GG4E/afs_data/root/pl0104mot.bin` | animation/motion bank | 406.2 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains beam / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/efct01_mdl.arc` | HSD effect model | 398.7 KiB | Medium | efct prefix is the shared battle-effect asset group |
| `user-data/GG4E/afs_data/root/pl0104_mdl.arc` | HSD model | 205.8 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains beam / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0104b_mdl.arc` | HSD model | 205.8 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains beam / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |

### gun

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0100.pzz` | compressed archive | 1.09 MiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0102.pzz` | compressed archive | 1.00 MiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0107.pzz` | compressed archive | 872.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0107 (REMOTE BOMBER) metadata contains gun, bomb, bomber; linked Borg is ranged/shot-capable (Long range type, shot 4) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0106.pzz` | compressed archive | 824.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0106 (TIME BOMBER) metadata contains gun, bomb, bomber; linked Borg is ranged/shot-capable (Long range type, shot 4) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c04.pzz` | compressed archive | 630.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c04 (ULTIMATE CANNON) metadata contains cannon, tank; linked Borg is ranged/shot-capable (Long range type, shot 10) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c01.pzz` | compressed archive | 478.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c01 (GATLING TANK) metadata contains gatling, tank; linked Borg is ranged/shot-capable (Long range type, shot 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c05.pzz` | compressed archive | 422.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c05 (ICBM TANK) metadata contains tank, icbm; linked Borg is ranged/shot-capable (Long range type, shot 10) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0100mot.bin` | animation/motion bank | 403.7 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0107mot.bin` | animation/motion bank | 400.8 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0107 (REMOTE BOMBER) metadata contains gun, bomb, bomber; linked Borg is ranged/shot-capable (Long range type, shot 4) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0102mot.bin` | animation/motion bank | 397.7 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0100_mdl.arc` | HSD model | 220.5 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0100b_mdl.arc` | HSD model | 220.5 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0102_mdl.arc` | HSD model | 210.9 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0102b_mdl.arc` | HSD model | 208.1 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |

### sword

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0203.pzz` | compressed archive | 1012.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0203 (SPIKE KNIGHT) metadata contains knight, spike; linked Borg is short-range/high-attack (Short range type, attack 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0204.pzz` | compressed archive | 952.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0204 (AXE KNIGHT) metadata contains knight, axe; linked Borg is short-range/high-attack (Short range type, attack 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl020d.pzz` | compressed archive | 944.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl020d (HATCHET KNIGHT) metadata contains knight, hatchet; linked Borg is short-range/high-attack (Short range type, attack 5) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0200.pzz` | compressed archive | 868.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0200 (SWORD KNIGHT) metadata contains sword, knight; linked Borg is short-range/high-attack (Short range type, attack 4) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0201.pzz` | compressed archive | 856.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0201 (CHAINSAW KNIGHT) metadata contains knight, chainsaw; linked Borg is short-range/high-attack (Short range type, attack 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0204mot.bin` | animation/motion bank | 296.8 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0204 (AXE KNIGHT) metadata contains knight, axe; linked Borg is short-range/high-attack (Short range type, attack 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0203mot.bin` | animation/motion bank | 281.4 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0203 (SPIKE KNIGHT) metadata contains knight, spike; linked Borg is short-range/high-attack (Short range type, attack 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0201mot.bin` | animation/motion bank | 277.6 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0201 (CHAINSAW KNIGHT) metadata contains knight, chainsaw; linked Borg is short-range/high-attack (Short range type, attack 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0200mot.bin` | animation/motion bank | 270.5 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0200 (SWORD KNIGHT) metadata contains sword, knight; linked Borg is short-range/high-attack (Short range type, attack 4) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0203_mdl.arc` | HSD model | 223.4 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0203 (SPIKE KNIGHT) metadata contains knight, spike; linked Borg is short-range/high-attack (Short range type, attack 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0203b_mdl.arc` | HSD model | 223.4 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0203 (SPIKE KNIGHT) metadata contains knight, spike; linked Borg is short-range/high-attack (Short range type, attack 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0200_mdl.arc` | HSD model | 186.8 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0200 (SWORD KNIGHT) metadata contains sword, knight; linked Borg is short-range/high-attack (Short range type, attack 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0200b_mdl.arc` | HSD model | 186.8 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0200 (SWORD KNIGHT) metadata contains sword, knight; linked Borg is short-range/high-attack (Short range type, attack 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0201b_mdl.arc` | HSD model | 171.3 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0201 (CHAINSAW KNIGHT) metadata contains knight, chainsaw; linked Borg is short-range/high-attack (Short range type, attack 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |

### muzzle

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0100.pzz` | compressed archive | 1.09 MiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0104.pzz` | compressed archive | 1.05 MiB | High | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains gun, beam; linked Borg is ranged/shot-capable (Long range type, shot 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0102.pzz` | compressed archive | 1.00 MiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c04.pzz` | compressed archive | 630.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c04 (ULTIMATE CANNON) metadata contains cannon, tank; linked Borg is ranged/shot-capable (Long range type, shot 10) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c01.pzz` | compressed archive | 478.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c01 (GATLING TANK) metadata contains gatling, tank; linked Borg is ranged/shot-capable (Long range type, shot 6) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0c02.pzz` | compressed archive | 452.0 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0c02 (BEAM TANK) metadata contains tank, beam; linked Borg is ranged/shot-capable (Almighty type, shot 5) / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0104mot.bin` | animation/motion bank | 406.2 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains gun, beam; linked Borg is ranged/shot-capable (Long range type, shot 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0100mot.bin` | animation/motion bank | 403.7 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0102mot.bin` | animation/motion bank | 397.7 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0100_mdl.arc` | HSD model | 220.5 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0100b_mdl.arc` | HSD model | 220.5 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0100 (REVOLVER GUNMAN) metadata contains gun, revolver; linked Borg is ranged/shot-capable (Long range type, shot 4) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0102_mdl.arc` | HSD model | 210.9 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0102b_mdl.arc` | HSD model | 208.1 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0102 (GATLING GUNNER) metadata contains gun, gatling; linked Borg is ranged/shot-capable (Long range type, shot 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0104_mdl.arc` | HSD model | 205.8 KiB | High | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains gun, beam; linked Borg is ranged/shot-capable (Long range type, shot 6) / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |

### impact

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/hit100.bin` | hit/impact data | 251.7 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit020.bin` | hit/impact data | 210.7 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit040.bin` | hit/impact data | 194.9 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit0e1.bin` | hit/impact data | 183.6 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit081.bin` | hit/impact data | 148.2 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hitff1.bin` | hit/impact data | 142.1 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hitff0.bin` | hit/impact data | 139.3 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit0a1.bin` | hit/impact data | 137.9 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit041.bin` | hit/impact data | 130.8 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit021.bin` | hit/impact data | 124.0 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit080.bin` | hit/impact data | 122.3 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit0b0.bin` | hit/impact data | 121.9 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit011.bin` | hit/impact data | 106.0 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/hit0a0.bin` | hit/impact data | 99.3 KiB | High | source weapons/effects/projectiles inventory: filename contains hit; hit/comhit binary naming is direct impact/collision evidence / hit/data BIN schema parser for collision, impact, and weapon metadata |

### trail

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/pl0a02.pzz` | compressed archive | 1.21 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a02 (DEMON WING) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a09.pzz` | compressed archive | 1.12 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a09 (GARUDA) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a08.pzz` | compressed archive | 1.11 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a08 (BLADE WING) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl060e.pzz` | compressed archive | 1.10 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl060e (CYBER MACHINE GENBU) metadata contains cyber / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl060a.pzz` | compressed archive | 1.10 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl060a (CYBER MACHINE SUZAKU) metadata contains cyber / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a04.pzz` | compressed archive | 1.09 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a04 (ANUBIS WING) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a06.pzz` | compressed archive | 1.08 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a06 (BEAM WING RED) metadata contains wing, beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl060c.pzz` | compressed archive | 1.07 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl060c (CYBER MACHINE BYAKKO) metadata contains cyber / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0602.pzz` | compressed archive | 1.07 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0602 (CYBER MACHINE SEIRYU) metadata contains cyber / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a03.pzz` | compressed archive | 1.07 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a03 (BEAM WING BLUE) metadata contains wing, beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0104.pzz` | compressed archive | 1.05 MiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0104 (BEAM GUNNER) metadata contains beam / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a00.pzz` | compressed archive | 1004.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a00 (WING SOLDIER) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a07.pzz` | compressed archive | 988.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a07 (DEATH WING) metadata contains wing / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0a01.pzz` | compressed archive | 980.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0a01 (JET HERO) metadata contains jet / PZZ unpack/list integration before browser conversion |

### reticle

| Path | Role | Size | Confidence | Reason / blocker |
|---|---|---:|---|---|
| `user-data/GG4E/afs_data/root/as_icon.tpl` | texture | 4.6 KiB | High | source weapons/effects/projectiles inventory: filename contains icon; UI-like icon/versus texture naming / TPL texture decode to PNG/KTX2 for browser use |
| `user-data/GG4E/afs_data/root/arrow_mdl.arc` | HSD model | 2.8 KiB | High | source weapons/effects/projectiles inventory: filename contains arrow; arrow name can also support targeting UI/indicator investigation / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002.pzz` | compressed archive | 886.0 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / PZZ unpack/list integration before browser conversion |
| `user-data/GG4E/afs_data/root/pl0002mot.bin` | animation/motion bank | 327.9 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / MOT bank semantic labels for attack/projectile timing |
| `user-data/GG4E/afs_data/root/pl0002_mdl.arc` | HSD model | 148.9 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002b_mdl.arc` | HSD model | 148.9 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002c_mdl.arc` | HSD model | 144.4 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002g_mdl.arc` | HSD model | 144.4 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002s_mdl.arc` | HSD model | 144.4 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002k_mdl.arc` | HSD model | 63.8 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / HSD model export path to DAE/GLB for effect, projectile, and attachment meshes |
| `user-data/GG4E/afs_data/root/pl0002hit.bin` | hit/impact data | 7.7 KiB | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / hit/data BIN schema parser for collision, impact, and weapon metadata |
| `user-data/GG4E/afs_data/root/vs005.tpl` | texture | 928 B | Medium | source weapons/effects/projectiles inventory: UI-like icon/versus texture naming / TPL texture decode to PNG/KTX2 for browser use |
| `user-data/GG4E/afs_data/root/pl0002data.bin` | borg data table | 432 B | Medium | source weapons/effects/projectiles inventory: linked Borg pl0002 (ARROW NINJA) metadata contains arrow / hit/data BIN schema parser for collision, impact, and weapon metadata |

## Archive parser status and remaining blockers

- Shared PZZ unpack/list support is implemented in packages/formats/src/pzz.ts.
- Shared ARZ/PZZP decompression is implemented in packages/formats/src/arz.ts.
- This scanner now consumes the shared parser for direct effect PZZ and item-model ARZ candidates.
- Decoded PZZ/ARZ payloads still need HSD/model and effect semantic mapping before they can drive sword/gun/projectile/powerup visuals.
- PZZ members may contain ARZ-compressed payloads, so effect archive inspection has two layers: PZZ member table first, then ARZ decompression per compressed member.
- Direct scan found 1 PZZ effect archive(s) and 90 ARZ item model archive(s).
- PZZ member payload kinds: hsd-dat 2, tpl-texture 1.
- Direct ARZ payload kinds: hsd-dat 90.

ARZ header groups:

- `0x00400003 0xc6e70003 0xbbc40000 0x02bc0000`: 1
- `0x00400003 0xc6970003 0xbb840000 0x02b80000`: 89

## Existing spec evidence used

- `research/format-specs/arc-hsd-format.md` lines 1, 7, 9, 13, 14, 22, 33, 49, 57, 61, 70, 71
- `research/format-specs/borg-animation-banks.md` lines 52, 53, 159
- `research/format-specs/hit-bin-format.md` lines 116, 124, 140
- `research/format-specs/hsd-animation-semantics.md` lines 36, 54, 59
- `research/format-specs/mot-animation-format.md` lines 7, 69, 70
- `research/format-specs/particle-effect-format.md` lines 1, 4, 11, 12, 13, 14, 19, 20, 26, 27, 28, 29
- `research/format-specs/pzz-arz-format.md` lines 1, 4, 9, 11, 12, 13, 14, 15, 16, 17, 22, 23
- `research/format-specs/re-wiki-gotcha-force.md` lines 21, 22, 30, 31, 32, 34, 36, 40, 42, 44, 47, 49

## Next decoding steps

- Map decompressed `efct.pzz` members and `it####_mdl.arz` HSD roots to concrete game events, borg actions, bones, and hit timing.
- Add a TXG image decoder for I4, I8, and RGB565; `ptcl00.txg` already provides dimensions, formats, and byte-exact payload spans.
- Reverse PTL record fields by correlating PTL records, REF indexes, TXG texture indexes, and Dolphin captures of fire/beam/muzzle/impact/trail effects.
- For sword/gun attachment visuals, inspect decompressed `it####_mdl.arz` as HSD models and map them to MOT/hit timing rather than creating placeholder effects.

