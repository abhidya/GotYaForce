# Ghidra Function Evidence Index

Generated: 2026-07-03T07:30:54.431Z

## Warning

inferredName values are local hints only. Verify with callers/callees, constants, globals, strings/assets, traces, or behavior before porting.

## Summary

- Functions indexed: 11972
- Source corpus: `research/decomp/ghidra-export`
- JSON: `research/decomp/index/function-evidence-index.json`

## Topic Counts

| Topic | Functions | Related web modules |
| --- | ---: | --- |
| assets-animation | 599 | `packages/formats/src/hsd-anim.ts`<br>`apps/game/src/sim/battleScene.ts`<br>`apps/game/public/models` |
| audio | 43 | `packages/audio/src/index.ts`<br>`apps/game/src/main.ts` |
| battle-initialization | 369 | `packages/combat/src/battle.ts`<br>`apps/game/src/sim/adapter.ts`<br>`apps/game/src/main.ts` |
| camera | 74 | `apps/game/src/main.ts`<br>`apps/game/src/sim/battleScene.ts`<br>`packages/render/src/index.ts` |
| challenge-menu-flow | 569 | `apps/game/src/main.ts`<br>`apps/game/src/ui/screens`<br>`packages/missions/src/challenge.ts` |
| damage | 152 | `packages/combat/src/combat.ts`<br>`packages/combat/src/constants.ts`<br>`packages/combat/src/stats.ts` |
| force-setup | 1566 | `packages/missions/src/challenge.ts`<br>`packages/combat/src/battle.ts`<br>`apps/game/src/ui/screens/SelectForce.ts` |
| front-end-menu | 68 | `research/decomp/index/title-main-menu-flow.md`<br>`apps/game/UI-FIDELITY-SPEC.md`<br>`apps/game/src/ui/screens/MainMenu.ts`<br>`apps/game/src/ui/sceneModel.ts`<br>`apps/game/public/ui/scenes/manifest.json` |
| global-menu-mode | 13 | `research/decomp/index/title-main-menu-flow.md`<br>`research/decomp/index/start-code-flow.md`<br>`apps/game/UI-FIDELITY-SPEC.md`<br>`apps/game/src/ui/screens/MainMenu.ts` |
| knockback-targeting | 2054 | `packages/combat/src/combat.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |
| movement-physics | 2765 | `packages/combat/src/movement.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |
| stage-load-collision | 4 | `apps/game/src/sim/adapter.ts`<br>`apps/game/src/main.ts`<br>`packages/formats/src/hit-bin.ts` |

## Known Porting Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x8000a004 | `zz_000a004_` | `dispatch_pending_io_request` |  | `research/decomp/ghidra-export/chunk_0000.c:4560` |
| 0x8002bb14 | `battle_frame_target_action_dispatch` | `battle_frame_target_action_dispatch` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics, stage-load-collision | `research/decomp/ghidra-export/chunk_0003.c:5844` |
| 0x8002cb20 | `mutual_actor_contact_mask_update` | `mutual_actor_contact_mask_update` | force-setup, knockback-targeting | `research/decomp/ghidra-export/chunk_0003.c:6454` |
| 0x8002d7c4 | `collision_hit_pair_pass_active_vs_borgs` | `collision_hit_pair_pass_active_vs_borgs` | damage, knockback-targeting, movement-physics, stage-load-collision | `research/decomp/ghidra-export/chunk_0003.c:7026` |
| 0x8002db58 | `collision_hit_pair_pass_active_vs_secondary` | `collision_hit_pair_pass_active_vs_secondary` | damage, knockback-targeting, movement-physics, stage-load-collision | `research/decomp/ghidra-export/chunk_0003.c:7168` |
| 0x8002df08 | `collision_hit_pair_pass_object_lists` | `collision_hit_pair_pass_object_lists` | damage, knockback-targeting, movement-physics, stage-load-collision | `research/decomp/ghidra-export/chunk_0003.c:7310` |
| 0x8002e2a8 | `resolve_hitbox_target_effects_and_damage` | `resolve_hitbox_target_effects_and_damage` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7473` |
| 0x800300bc | `zz_00300bc_` | `compute_knockback_launch_direction` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:8540` |
| 0x8003cd5c | `zz_003cd5c_` | `compute_base_damage_formula` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting | `research/decomp/ghidra-export/chunk_0004.c:6667` |
| 0x8003d344 | `zz_003d344_` | `apply_hp_damage_subtract_clamp` | challenge-menu-flow, battle-initialization, damage | `research/decomp/ghidra-export/chunk_0004.c:6832` |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0007.c:896` |
| 0x800680d4 | `dispatch_slot_action_update` | `dispatch_slot_action_update` | challenge-menu-flow, force-setup, battle-initialization, knockback-targeting | `research/decomp/ghidra-export/chunk_0008.c:4366` |
| 0x80068138 | `reset_actor_param_tier` | `reset_actor_param_tier` | challenge-menu-flow, battle-initialization | `research/decomp/ghidra-export/chunk_0008.c:4389` |
| 0x8006817c | `apply_actor_param_tier_delta_127` | `apply_actor_param_tier_delta_127` | challenge-menu-flow, battle-initialization | `research/decomp/ghidra-export/chunk_0008.c:4410` |
| 0x800681e4 | `apply_actor_param_tier_delta_63` | `apply_actor_param_tier_delta_63` | challenge-menu-flow, battle-initialization, knockback-targeting | `research/decomp/ghidra-export/chunk_0008.c:4442` |
| 0x8006826c | `refresh_actor_param_tier_table` | `refresh_actor_param_tier_table` |  | `research/decomp/ghidra-export/chunk_0008.c:4485` |
| 0x8008c3a0 | `set_global_menu_mode` | `set_global_menu_mode` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:2606` |
| 0x8008c3ac | `dispatch_global_menu_mode` | `dispatch_global_menu_mode` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:2617` |
| 0x8008cb64 | `FUN_8008cb64` | `global_menu_mode_00_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3059` |
| 0x8008cec8 | `zz_008cec8_` | `global_menu_mode_01_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3221` |
| 0x8008cf20 | `zz_008cf20_` | `global_menu_mode_02_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3241` |
| 0x8008d050 | `zz_008d050_` | `global_menu_mode_03_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3290` |
| 0x8008d1c4 | `zz_008d1c4_` | `global_menu_mode_04_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3349` |
| 0x8008d2e8 | `zz_008d2e8_` | `global_menu_mode_05_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3396` |
| 0x8008d35c | `zz_008d35c_` | `global_menu_mode_06_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3424` |
| 0x8008d468 | `zz_008d468_` | `global_menu_mode_07_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3470` |
| 0x8008d524 | `zz_008d524_` | `global_menu_mode_08_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3506` |
| 0x8008d5d0 | `zz_008d5d0_` | `global_menu_mode_09_title_menu_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3540` |
| 0x8008d64c | `zz_008d64c_` | `global_menu_mode_10_frontend_transition_render` | global-menu-mode, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0013.c:3570` |
| 0x800e8f84 | `FUN_800e8f84` | `resource_transition_begin_job` |  | `research/decomp/ghidra-export/chunk_0025.c:803` |
| 0x800e8fe0 | `FUN_800e8fe0` | `resource_transition_attach_scene_job` | movement-physics | `research/decomp/ghidra-export/chunk_0025.c:824` |
| 0x800e90ac | `FUN_800e90ac` | `resource_transition_reset_slot_job` | movement-physics | `research/decomp/ghidra-export/chunk_0025.c:860` |
| 0x800e9138 | `FUN_800e9138` | `resource_transition_set_slot_phase_job` | movement-physics | `research/decomp/ghidra-export/chunk_0025.c:897` |
| 0x800e91d4 | `zz_00e91d4_` | `enqueue_resource_transition_job` |  | `research/decomp/ghidra-export/chunk_0025.c:926` |
| 0x800e9340 | `zz_00e9340_` | `process_resource_transition_queue` |  | `research/decomp/ghidra-export/chunk_0025.c:1015` |
| 0x800e95a4 | `zz_00e95a4_` | `update_resource_transition_progress` |  | `research/decomp/ghidra-export/chunk_0025.c:1119` |
| 0x800e99c8 | `zz_00e99c8_` | `queue_resource_scene_transition` | movement-physics | `research/decomp/ghidra-export/chunk_0025.c:1387` |
| 0x80066298 | `zz_0066298_` | `lookup_type_category_table` | damage | `research/decomp/ghidra-export/chunk_0008.c:2976` |
| 0x8006ab04 | `start_forced_move_to_point` | `start_forced_move_to_point` | knockback-targeting | `research/decomp/ghidra-export/chunk_0009.c:1056` |
| 0x8006abd4 | `react_to_slot_target_object` | `react_to_slot_target_object` | force-setup, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0009.c:1115` |
| 0x8006ace8 | `start_status_reaction_by_side` | `start_status_reaction_by_side` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0009.c:1162` |
| 0x8010d880 | `set_slot_action_handler` | `set_slot_action_handler` |  | `research/decomp/ghidra-export/chunk_0030.c:2601` |
| 0x800527d8 | `zz_00527d8_` | `run_main_game_loop` |  | `research/decomp/ghidra-export/chunk_0006.c:5790` |
| 0x801dca30 | `FUN_801dca30` | `title_main_menu_scene_enter` | front-end-menu | `research/decomp/ghidra-export/chunk_0058.c:1286` |
| 0x801dcf7c | `zz_01dcf7c_` | `title_main_menu_scene_tick` |  | `research/decomp/ghidra-export/chunk_0058.c:1521` |
| 0x801dcfa0 | `zz_01dcfa0_` | `title_main_menu_scene_update_draw` | front-end-menu, challenge-menu-flow, force-setup, battle-initialization | `research/decomp/ghidra-export/chunk_0058.c:1534` |
| 0x801dd3e8 | `zz_01dd3e8_` | `title_menu_refresh_borg_status_slots` | front-end-menu, movement-physics | `research/decomp/ghidra-export/chunk_0058.c:1686` |
| 0x801dd60c | `zz_01dd60c_` | `title_menu_refresh_selected_borg_state` | front-end-menu | `research/decomp/ghidra-export/chunk_0058.c:1791` |
| 0x801dd63c | `zz_01dd63c_` | `title_menu_reset_camera` | front-end-menu, challenge-menu-flow, camera | `research/decomp/ghidra-export/chunk_0058.c:1804` |
| 0x801dd6b0 | `FUN_801dd6b0` | `title_menu_update_orbit_camera` | front-end-menu, knockback-targeting, camera | `research/decomp/ghidra-export/chunk_0058.c:1820` |
| 0x801dd7d4 | `zz_01dd7d4_` | `title_menu_spawn_base_widgets` | front-end-menu | `research/decomp/ghidra-export/chunk_0058.c:1863` |
| 0x801dd820 | `zz_01dd820_` | `title_menu_spawn_base_widget` |  | `research/decomp/ghidra-export/chunk_0058.c:1878` |
| 0x801dd8d8 | `FUN_801dd8d8` | `title_menu_widget_update_dispatch` | front-end-menu | `research/decomp/ghidra-export/chunk_0058.c:1911` |
| 0x801de6e8 | `zz_01de6e8_` | `title_menu_widget_draw_text` | front-end-menu | `research/decomp/ghidra-export/chunk_0058.c:2475` |
| 0x801de9e0 | `FUN_801de9e0` | `title_menu_widget_draw` |  | `research/decomp/ghidra-export/chunk_0058.c:2547` |
| 0x801eee28 | `zz_01eee28_` | `title_menu_spawn_extra_widgets` | front-end-menu | `research/decomp/ghidra-export/chunk_0060.c:2159` |
| 0x801eee6c | `zz_01eee6c_` | `title_menu_spawn_extra_widget` |  | `research/decomp/ghidra-export/chunk_0060.c:2174` |
| 0x801eeef4 | `FUN_801eeef4` | `title_menu_extra_widget_update_dispatch` | front-end-menu | `research/decomp/ghidra-export/chunk_0060.c:2196` |
| 0x801ef1c8 | `FUN_801ef1c8` | `title_menu_extra_widget_draw` | knockback-targeting, movement-physics, assets-animation | `research/decomp/ghidra-export/chunk_0060.c:2329` |
| 0x801f5bd4 | `FUN_801f5bd4` | `frontend_menu_branch_load_transition` | front-end-menu, challenge-menu-flow | `research/decomp/ghidra-export/chunk_0061.c:1922` |
| 0x801f6024 | `zz_01f6024_` | `frontend_menu_resource_load_callback` | front-end-menu | `research/decomp/ghidra-export/chunk_0061.c:2151` |
| 0x801f60d0 | `zz_01f60d0_` | `frontend_menu_spawn_widgets` |  | `research/decomp/ghidra-export/chunk_0061.c:2219` |
| 0x801962c4 | `build_challenge_battle_setup` | `challenge_force_slot_team_setup` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0048.c:234` |
| 0x802807ac | `cPlayer::ClearSwapControllerTimer(void)` | `player_clear_swap_controller_timer` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:3819` |
| 0x80281c38 | `zz_0281c38_` | `death_swap_flow_candidate` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:4844` |
| 0x80297538 | `zz_0297538_` | `team_player_lookup_band_head` |  | `research/decomp/ghidra-export/chunk_0076.c:18706` |
| 0x802a3938 | `cTeam::GetPlayer(int)` | `team_get_player` | force-setup | `research/decomp/ghidra-export/chunk_0078.c:2079` |

## Usage

- Query by address to get current name, chunk/line, callers/callees, globals, constants, strings/assets, and related web modules.
- Treat `inferredName` as a navigation hint only; original-game evidence remains call graph, constants/tables, asset opens, traces, and behavior.
- For Challenge flow, start from `challenge-menu-flow`, `force-setup`, and `battle-initialization` topics before replacing browser player-facing behavior.

