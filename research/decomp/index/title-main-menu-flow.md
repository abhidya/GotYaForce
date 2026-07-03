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

## UI/UX Evidence

The web/UI research describes the visible title/main-menu as a 3D desk diorama with selectable menu items and a red gear cursor. That matches the decomp cluster:

- `DAT_80390ad0` is a 98-row base widget descriptor table consumed by `title_menu_spawn_base_widgets`.
- `PTR_FUN_8039131c` is the base widget update callback table.
- `DAT_80435b88` and `PTR_FUN_803a13b8` cover optional extra widget descriptors/callbacks.
- The scene assets are exported as `tl00` and `optn00` in `apps/game/public/ui/scenes/manifest.json`.
- `apps/game/UI-FIDELITY-SPEC.md` and `apps/game/src/ui/screens/MainMenu.ts` hold the current recreated UI/UX target notes.

Important correction: `titles.tpl` is the Sofdec/ADX boot splash. It is not the 3D desk title/main-menu scene.

