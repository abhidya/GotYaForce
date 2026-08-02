# Title And Global Menu Mode Flow

> **2026-08-01 source correction:** `0x801dca30` is an actor-viewer/customization
> scene, not the title/main-menu controller. Consequently, `DAT_80390ad0` rows
> 30..37 are not proven physical-menu mode mappings. The verified title-intro
> owner is `0x801c795c`: it selects stage `0x11` (`stff`), loads `tdc00..09` and
> `tl00_mdl.arc`, seeds G RED/Sasuke, and creates the ten `stff` title props. The
> physical desk controller is the global-state-2 chain beginning at `0x800bf8d4`;
> its `FUN_801cd90c` widgets are now rendered from the recovered `stff` drawable table
> (`DAT_8038a760`) rather than from native-capture backgrounds.

This note links the reviewed Ghidra decompile, the copied filesystem tree, and the UI/UX research for the title/main-menu path.

## Dispatcher

`0x8008c3ac dispatch_global_menu_mode` is the per-frame global menu render dispatcher:

```c
menu_mode = (char)PTR_DAT_80433930[0x3e];
(*(code *)(&PTR_FUN_802da780)[menu_mode])();
zz_009752c_();
```

`0x8008c3a0 set_global_menu_mode` writes `PTR_DAT_80433930[0x3e]`.

The dispatch table at `PTR_FUN_802da780` has 11 reviewed entries. The copied tree now routes the setter, dispatcher, and table entries to `research/decomp/organized/game/modes/global-menu/`.

| mode | address | reviewed name |
| ---: | --- | --- |
| 0 | `0x8008cb64` | `global_menu_mode_00_render` |
| 1 | `0x8008cec8` | `global_menu_mode_01_render` |
| 2 | `0x8008cf20` | `global_menu_mode_02_render` |
| 3 | `0x8008d050` | `global_menu_mode_03_render` |
| 4 | `0x8008d1c4` | `global_menu_mode_04_render` |
| 5 | `0x8008d2e8` | `global_menu_mode_05_render` |
| 6 | `0x8008d35c` | `global_menu_mode_06_render` |
| 7 | `0x8008d468` | `global_menu_mode_07_render` |
| 8 | `0x8008d524` | `global_menu_mode_08_render` |
| 9 | `0x8008d5d0` | `global_menu_mode_09_title_menu_render` |
| 10 | `0x8008d64c` | `global_menu_mode_10_frontend_transition_render` |

## Title/Main Menu Ownership Status

The dispatcher selects render recipes but does not prove which high-level controller owns
the physical desk menu. Earlier labels attached that ownership to `0x801dca30`; reviewing
its actor allocation, camera orbit, and widget callbacks shows that cluster belongs to an
actor viewer/customization scene instead. Its `set_global_menu_mode(9)` call proves only
the render recipe it uses.

The verified boot dispatcher is `0x80017918`, whose table at `0x802c4a00` enters the title
task through `0x800179e8 -> 0x801c7908`. The title task's own two-entry table is stored at
`0x80435a88`: `0x801c795c` initializes it and `0x801c7b68` ticks it. When the script ends,
`0x800179e8` sets the global dispatcher at `0x802d2e48` to state 2, whose entry is
`0x800bf8d4`. That controller recreates stage `0x11`, calls `0x801cd90c` to instantiate
the physical-menu widgets from `DAT_8038a720`, and routes its seven selection indices
through `PTR_FUN_802cfdc4` at `0x802cfdc4`. Index 1 dispatches directly to the recovered
Challenge controller at `0x80195f2c`.

## Physical Menu Drawables

`FUN_801cd90c` walks 15 four-byte descriptors at `DAT_8038a720`: seven kind-0 entry
objects (indices 0..6), one kind-1 cursor, and seven kind-2 label objects (indices 0..6).
The kind handlers are selected by four byte-verified function tables:

| table | address | entries |
| --- | --- | --- |
| task state | `0x8038a79c` | `0x801cd9e4`, `0x801cda40`, `0x801cda7c`, `0x801cda90` |
| init by kind | `0x8038a7ac` | `0x801cdaec`, `0x801cde60`, `0x801ce01c` |
| update by kind | `0x8038a7b8` | `0x801cdbe0`, `0x801cdf08`, `0x801ce084` |
| draw by kind | `0x8038a7c4` | `0x801cde10`, `0x801cdf84`, `0x801ce0dc` |

Kind 0 indexes the three-u16 rows at `DAT_8038a760`. The first two models form the
entry/selection pair and the third is the corresponding kind-2 label:

| menu index | base | selection | label |
| ---: | ---: | ---: | ---: |
| 0 | 41 | 61 | 40 |
| 1 | 43 | 62 | 42 |
| 2 | 35 | 63 | 44 |
| 3 | 39 | 59 | 36 |
| 4 | 45 | 64 | 46 |
| 5 | 37 | 60 | 38 |
| 6 | 66 | 67 | 68 |

All are authored models in `stff_mdl.arc`. `FUN_801cde60` loads cursor model `0x38`
(56) and `zz_01cdf08_` copies the selected kind-0 entry position into it. The seven
signed BAM rotation increments at `DAT_8038a78c` are all `0x0200` (512); the cursor advances by
literal `0x400` BAM per frame. The browser renderer consumes these generated values and
uses the authored `stff` camera/lights and retained GLB transforms.

## Desk Intro Script

The 3D desk/title intro is also driven by an earlier front-end script cluster:

| address | current name | role |
| --- | --- | --- |
| `0x801c795c` | `FUN_801c795c` | initializes the front-end desk/title sequence, preloads scene assets, installs script pointer `DAT_8038a3ec`, then calls `sndSeqContinue` |
| `0x801c7b68` | `sndSeqContinue` | per-frame script runner wrapper |
| `0x801c7de4` | `zz_01c7de4_` | reads the current bytecode from `*(state+0x20)`, dispatches via `PTR_FUN_8038a4f8`, advances by `DAT_8038a3b8[opcode] + 1` |
| `0x801c8128` | `FUN_801c8128` | script opcode `0x0b`; waits for/attaches the preloaded desk scene archives via `zz_0042954_` and `zz_0042b20_` |
| `0x801c81a0` | `FUN_801c81a0` | script opcode `0x0d`; controls borg actor slots and starts actor animations through `zz_0057ff8_` |

The front-end preload at `0x80042a58 zz_0042a58_` loads archive ids `0xa86..0xa8f` plus `0xaa6`. In the copied AFS rebuild table, `0xaa6` is `tl00_mdl.arc` (the desk diorama scene), and `0xa86..0xa8f` are `tdc00..tdc09.arc` — 10 bare HSD DATs (root name `scene_data`, 1.3–1.8 KB each, no geometry, dense float tracks) attached as scene assets by opcode `0x0b`. They are **not** the actor motion banks: the actor commands select each borg's own family group-5 stream, which maps into that borg's g0 motion file. `FUN_801c795c` also seeds the actor descriptor table at `PTR_DAT_80433934+0x10` from `DAT_8038a4ec`; that block is a FLAT array of 6 big-endian u16 borg ids (proven at chunk_0006.c:7055 `Battle_SpawnActiveBorgFromSlotTables` and chunk_0046.c:1176-1192's stride-2/6-slot layout): `[0]=0x0615` (G-Red pl0615), `[1]=0x000a` (Sasuke pl000a — Kakeru's partner borg), `[2..5]=0xffff` (empty). The variant lives in a separate `+0xa0` byte table seeded elsewhere, not in this block.

Runtime trace `user-data/dolphin-trace/traces/input-bridge-action-only/gdb-trace-2026-07-02T21-06-13-352Z.json` confirms `sndSeqContinue` executing with `state+0x20 = 0x8038a3ec`. The captured bytes begin:

```text
00 01 06 ff 07 00 00 00 01 00 00 00 00 3c 02 13
00 1b 14 01 05 00 78 0a 0b 09 01 07 00 03 01 00
02 14 00 08 03 06 0c 0c 01 07 00 00 01 08 00 15
01 7c 05 00 1e 00 03 0d 01 00 00 0d 01 01 00 0d
```

Decoded against `DAT_8038a3b8` and `PTR_FUN_8038a4f8`, the actor-animation commands in the first part of the script are:

| script offset | command | meaning |
| ---: | --- | --- |
| `0x37` | `0d 01 00 00` | reset actor slot 0 |
| `0x3b` | `0d 01 01 00` | reset actor slot 1 |
| `0x3f` | `0d 00 00 00` | start actor slot 0 animation `0` via `zz_0057ff8_(slot0, 5, 0)` |
| `0x43` | `0d 00 01 00` | start actor slot 1 animation `0` via `zz_0057ff8_(slot1, 5, 0)` |
| `0x63` | `0d 00 00 01` | start actor slot 0 animation `1` |
| `0x7a` | `0d 00 01 01` | start actor slot 1 animation `1` |
| `0x91` | `0d 00 00 06` | start actor slot 0 animation `6` |
| `0x9d` | `0d 00 01 06` | start actor slot 1 animation `6` |
| `0xa9` | `0d 00 00 03` | start actor slot 0 animation `3` |
| `0xad` | `0d 00 01 03` | start actor slot 1 animation `3` |
| `0xb9` | `0d 00 01 04` | start actor slot 1 animation `4` |
| `0xc5` | `0d 00 00 04` | start actor slot 0 animation `4` |
| `0xd1` | `0d 00 00 07` | start actor slot 0 animation `7` |
| `0xd5` | `0d 00 01 07` | start actor slot 1 animation `7` |

`FUN_801c81a0` treats command mode `0` as the real animation start path:

```c
zz_0057ff8_((&DAT_803c4e84)[slot], 5, anim_id);
```

`zz_0057ff8_` then selects actor animation data through:

```c
zz_004beb8_(rate, actor, 0xf, action_group, anim_id, -1, -1);
```

The recovered family streams establish the exact source mapping used by the port: script ids `0..5` and `7` select the same-numbered g0 animations, while script id `6` selects g0 animation `9` for both intro actors. Root translation from those baked clips is retained, so the `0x0d` commands — not synthetic movement constants — drive their choreography. The playback-rate operand carried by id `3` is recovered as `30`, but its engine unit remains unpinned; the port therefore leaves that clip at its baked rate instead of inventing a conversion.

### Camera timeline correction (2026-08-01)

Raw PPC for opcode `0x08` proves it is `waitForSceneFrame`, not a fade setter. Opcode
`0x07` installs a selected COBJ animation timeline and calls `zz_00088a4_`; the per-frame
tick advances that HSD camera frame, while `0x08` blocks until the requested frame (or
the `0xff` completion sentinel). The ten tdc end frames are 39, 23, 60, 49, 49, 80, 31,
49, 29, and 29. Their camera/eye/target FOBJ tracks are exported to
`apps/game/public/ui/scenes/tl00/tdc-camera-anims.json` and sampled by the renderer.
Opcode `0x01`, not `0x07`, owns full-screen color. With these waits restored, the
fixed-frame script reaches Press Start at frame 1222.

## Main Menu Handoff

The verified handoff is:

```text
0x800179e8 (title reports end)
  -> global dispatcher state 2
  -> 0x800bf8d4 physical-menu controller
  -> DAT_80301cf0 seven-row directional graph
  -> selected index 1
  -> PTR_FUN_802cfdc4[1] = 0x80195f2c dispatch_challenge_flow_state
```

`0x801dc8e8 -> 0x801dca30` remains an actor-viewer/customization handoff and must not be
used as the desk-menu transition.

## UI/UX Evidence

The web/UI research describes a 3D desk diorama with selectable menu items and a red
gear cursor. The scene assets are exported as `tl00` and `optn00`, and native captures
remain useful visual evidence. They do not establish controller ownership. In particular,
`DAT_80390ad0` and its callback tables belong to the actor-viewer/customization cluster
and cannot be treated as physical-menu option mappings.

Important correction: `titles.tpl` is the Sofdec/ADX boot splash. It is not the 3D desk title/main-menu scene.
