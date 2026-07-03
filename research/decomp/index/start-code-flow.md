# Start Code Flow

Generated: 2026-07-03T07:31:46.612Z

## Summary

- Root: `0x80003154` `start` at `game/unsorted/80003154_start.c`
- Static reachable functions: 876 / 11972 (7.32%)
- Direct callees from `start`: 13
- Reachable known anchors: 7
- Reachable class methods: 0

## Boot Flow

| Callee | Route | Static subtree | Notes |
|---|---|---:|---|
| `0x800032b0` `__init_registers` | `sdk/libc` | 1 | CPU/register bootstrap stub. |
| `0x80003400` `gnt4-__init_hardware-bl` | `sdk/libc` | 21 | OS/FPU/cache hardware init. |
| `0x80003340` `zz_0003340_` | `game/unsorted` | 5 | Copies initialized sections and clears BSS-style regions. |
| `0x80231370` `knockback-targeting_candidate_80231370` | `game/combat/knockback` | 261 |  |
| `0x80003140` `__set_debug_bba` | `sdk/libc` | 1 | Debug / MetroTRK / boot-mode handling. |
| `0x8020ae10` `zz_020ae10_` | `game/ui` | 1 |  |
| `0x801feda4` `audio_candidate_801feda4` | `game/audio` | 173 |  |
| `0x80003100` `__check_pad3` | `sdk/libc` | 153 | Debug / MetroTRK / boot-mode handling. |
| `0x8000314c` `zz_000314c_` | `game/unsorted` | 1 |  |
| `0x80231408` `InitMetroTRK_BBA` | `game/combat/knockback` | 261 | Debug / MetroTRK / boot-mode handling. |
| `0x80207464` `gnt4-__init_user-bl` | `sdk/libc` | 2 | User runtime initialization before game handoff. |
| `0x800527d8` `run_main_game_loop` | `game/battle` | 674 | Application handoff into the infinite main loop. |
| `0x802331c4` `FUN_802331c4` | `game/unsorted` | 7 | Terminal/runtime tail after user handoff. |

## Main Loop Body

Function: `0x800527d8` `run_main_game_loop` at `game/battle/800527d8_run_main_game_loop.c`

| # | Phase | Callee | Route | Static subtree | Notes |
|---:|---|---|---|---:|---|
| 1 | pre-loop init | `0x8002a3e4` `assets-animation_candidate_8002a3e4` | `game/assets/animation` | 313 |  |
| 2 | pre-loop init | `0x8002a638` `challenge-menu-flow_candidate_8002a638` | `game/modes/challenge` | 243 |  |
| 3 | per-frame loop | `0x8010d450` `zz_010d450_` | `game/unsorted` | 57 |  |
| 4 | per-frame loop | `0x8008c088` `zz_008c088_` | `game/systems` | 1 |  |
| 5 | per-frame loop | `0x80080278` `zz_0080278_` | `game/systems` | 1 |  |
| 6 | per-frame loop | `0x80052838` `challenge-menu-flow_candidate_80052838` | `game/modes/challenge` | 4 |  |
| 7 | per-frame loop | `0x800e9994` `zz_00e9994_` | `game/unsorted` | 50 |  |
| 8 | per-frame loop | `0x8008dbe0` `zz_008dbe0_` | `game/systems` | 37 |  |
| 9 | per-frame loop | `0x8000a004` `dispatch_pending_io_request` | `game/unsorted` | 1 | Dispatches current pending I/O/load request via `PTR_FUN_802c3818`. |
| 10 | per-frame loop | `0x80018b10` `challenge-menu-flow_candidate_80018b10` | `game/modes/challenge` | 21 |  |
| 11 | per-frame loop | `0x800efda8` `zz_00efda8_` | `game/unsorted` | 69 |  |
| 12 | per-frame loop | `0x8002a4b0` `assets-animation_candidate_8002a4b0` | `game/assets/animation` | 7 |  |
| 13 | per-frame loop | `0x8008c3ac` `dispatch_global_menu_mode` | `game/modes/global-menu` | 44 | Dispatches current menu/game mode via `PTR_FUN_802da780`. |
| 14 | per-frame loop | `0x800528b4` `zz_00528b4_` | `game/battle` | 109 |  |
| 15 | per-frame loop | `0x800802a8` `knockback-targeting_candidate_800802a8` | `game/combat/knockback` | 42 |  |
| 16 | per-frame loop | `0x8008c2dc` `zz_008c2dc_` | `game/systems` | 36 |  |
| 17 | per-frame loop | `0x8008c344` `zz_008c344_` | `game/systems` | 36 |  |
| 18 | per-frame loop | `0x80027c34` `challenge-menu-flow_candidate_80027c34` | `game/modes/challenge` | 27 |  |
| 19 | per-frame loop | `0x8002a4d4` `assets-animation_candidate_8002a4d4` | `game/assets/animation` | 87 |  |

## Route Counts

| Route | Reachable functions |
|---|---:|
| `sdk/os` | 159 |
| `game/ui` | 139 |
| `game/unsorted` | 132 |
| `game/combat/knockback` | 100 |
| `sdk/libc` | 90 |
| `sdk/gx` | 75 |
| `game/assets/animation` | 41 |
| `game/battle/force-setup` | 34 |
| `game/physics/movement` | 34 |
| `engine/shared` | 19 |
| `game/systems` | 14 |
| `game/battle` | 9 |
| `game/audio` | 8 |
| `sdk/audio` | 7 |
| `game/modes/challenge` | 5 |
| `game/combat` | 4 |
| `game/combat/damage` | 2 |
| `sdk/math` | 2 |
| `game/modes/global-menu` | 1 |
| `sdk/hsd` | 1 |

## Known Anchor Paths

| Anchor | Route | Shortest static path from start |
|---|---|---|
| `0x8000a004` `dispatch_pending_io_request` | `game/unsorted` | `start` -> `run_main_game_loop` -> `dispatch_pending_io_request` |
| `0x800527d8` `run_main_game_loop` | `game/battle` | `start` -> `run_main_game_loop` |
| `0x8008c3ac` `dispatch_global_menu_mode` | `game/modes/global-menu` | `start` -> `run_main_game_loop` -> `dispatch_global_menu_mode` |
| `0x800e91d4` `enqueue_resource_transition_job` | `game/unsorted` | `start` -> `run_main_game_loop` -> `challenge-menu-flow_candidate_80018b10` -> `zz_00e9b08_` -> `enqueue_resource_transition_job` |
| `0x800e9340` `process_resource_transition_queue` | `game/unsorted` | `start` -> `run_main_game_loop` -> `zz_00e9994_` -> `process_resource_transition_queue` |
| `0x800e95a4` `update_resource_transition_progress` | `game/unsorted` | `start` -> `run_main_game_loop` -> `zz_00e9994_` -> `knockback-targeting_candidate_800e9654` -> `update_resource_transition_progress` |
| `0x800e99c8` `queue_resource_scene_transition` | `game/physics/movement` | `start` -> `run_main_game_loop` -> `zz_00e9994_` -> `knockback-targeting_candidate_800e9654` -> `queue_resource_scene_transition` |

## Indirect Dispatch Sites

| Function | Route | Source |
|---|---|---|
| `0x8000a004` `dispatch_pending_io_request` | `game/unsorted` | `game/unsorted/8000a004_dispatch_pending_io_request.c` |
| `0x8008c3ac` `dispatch_global_menu_mode` | `game/modes/global-menu` | `game/modes/global-menu/8008c3ac_dispatch_global_menu_mode.c` |
| `0x800e9340` `process_resource_transition_queue` | `game/unsorted` | `game/unsorted/800e9340_process_resource_transition_queue.c` |

## Static Flow Limits

- This is a name-based static call graph from the Ghidra C export.
- Function-pointer dispatch tables are a known gap; Challenge flow uses dispatch arrays such as `PTR_FUN_*` and will need table decoding.
- Data/global anchors are resolved separately in `address-resolution.md`.

