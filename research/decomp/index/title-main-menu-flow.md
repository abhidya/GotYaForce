# Title And Global Menu Mode Flow

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

## Title/Main Menu Scene

The dispatcher does not own the title scene or UI state by itself. It only selects a render recipe. The title/main-menu scene lives in the front-end menu cluster:

| address | reviewed name | role |
| --- | --- | --- |
| `0x801dca30` | `title_main_menu_scene_enter` | enters the title/main-menu scene, loads scene/camera/model state, sets mode 9, spawns widgets, starts fade |
| `0x801dcf7c` | `title_main_menu_scene_tick` | wrapper around the per-frame title/main-menu update/draw |
| `0x801dcfa0` | `title_main_menu_scene_update_draw` | handles title/menu camera input, updates widgets/layers, draws menu UI passes |
| `0x801dd63c` | `title_menu_reset_camera` | resets menu camera state |
| `0x801dd6b0` | `title_menu_update_orbit_camera` | updates the orbiting menu camera |
| `0x801dd7d4` | `title_menu_spawn_base_widgets` | walks the base widget descriptor table |
| `0x801dd820` | `title_menu_spawn_base_widget` | allocates one title/menu widget and installs update/draw callbacks |
| `0x801dd8d8` | `title_menu_widget_update_dispatch` | dispatches per-widget update callbacks |
| `0x801de9e0` | `title_menu_widget_draw` | draws title/menu widgets |

`0x801dca30` calls `set_global_menu_mode(9)`, so mode 9 is the render side used by the title/main menu. `0x8008d5d0` performs a three-pass render using `PTR_DAT_80433930[0x34]` and render helpers such as `zz_008c440_`.

`0x801f5bd4 frontend_menu_branch_load_transition` later calls `set_global_menu_mode(10)`, making mode 10 the front-end transition/render branch.

## Desk Intro Script

The 3D desk/title intro is also driven by an earlier front-end script cluster:

| address | current name | role |
| --- | --- | --- |
| `0x801c795c` | `FUN_801c795c` | initializes the front-end desk/title sequence, preloads scene assets, installs script pointer `DAT_8038a3ec`, then calls `sndSeqContinue` |
| `0x801c7b68` | `sndSeqContinue` | per-frame script runner wrapper |
| `0x801c7de4` | `zz_01c7de4_` | reads the current bytecode from `*(state+0x20)`, dispatches via `PTR_FUN_8038a4f8`, advances by `DAT_8038a3b8[opcode] + 1` |
| `0x801c8128` | `FUN_801c8128` | script opcode `0x0b`; waits for/attaches the preloaded desk scene archives via `zz_0042954_` and `zz_0042b20_` |
| `0x801c81a0` | `FUN_801c81a0` | script opcode `0x0d`; controls borg actor slots and starts actor animations through `zz_0057ff8_` |

The front-end preload at `0x80042a58 zz_0042a58_` loads archive ids `0xa86..0xa8f` plus `0xaa6`. In the copied AFS rebuild table, `0xaa6` is `tl00_mdl.arc`, matching the extracted title/desk scene asset. `FUN_801c795c` also seeds a small borg/actor descriptor list from `DAT_8038a4ec`; the first halfword in that block is `0x0615`, matching G-Red's borg id.

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

So the G-Red/second-borg "run onto the desk/table" beats are most likely these scripted `0x0d` actor commands. The exact visual name for each animation id still needs confirmation against the exported `pl0615mot.bin`/`pl0000mot.bin` motion-bank labels or a frame-stepped runtime capture.

## Main Menu Handoff

The later menu handoff is:

```text
front-end selection flow
  -> 0x801dc8e8 zz_01dc8e8_(scene_index, input_index, list_kind, borg_entry)
  -> 0x801dc970 zz_01dc970_()
  -> 0x801dca30 title_main_menu_scene_enter
  -> set_global_menu_mode(9)
  -> title_menu_reset_camera
  -> title_menu_spawn_base_widgets
```

`zz_01dc8e8_` stores the selected scene/resource index in `DAT_80436398[0x14]`, the input/player index in `DAT_80436398[0x15]`, and copies the selected borg id/variant through `zz_01dd5d4_`. `title_main_menu_scene_enter` then creates the active actor, positions it, switches to global menu mode `9`, and spawns the menu option widgets.

## UI/UX Evidence

The web/UI research describes the visible title/main-menu as a 3D desk diorama with selectable menu items and a red gear cursor. That matches the decomp cluster:

- `DAT_80390ad0` is a 98-row base widget descriptor table consumed by `title_menu_spawn_base_widgets`.
- `PTR_FUN_8039131c` is the base widget update callback table.
- `DAT_80435b88` and `PTR_FUN_803a13b8` cover optional extra widget descriptors/callbacks.
- The scene assets are exported as `tl00` and `optn00` in `apps/game/public/ui/scenes/manifest.json`.
- `apps/game/UI-FIDELITY-SPEC.md` and `apps/game/src/ui/screens/MainMenu.ts` hold the current recreated UI/UX target notes.

Important correction: `titles.tpl` is the Sofdec/ADX boot splash. It is not the 3D desk title/main-menu scene.
