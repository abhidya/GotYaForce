# Ghidra Function Evidence Index

Generated: 2026-07-01T10:44:47.231Z

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
| damage | 149 | `packages/combat/src/combat.ts`<br>`packages/combat/src/constants.ts`<br>`packages/combat/src/stats.ts` |
| force-setup | 1566 | `packages/missions/src/challenge.ts`<br>`packages/combat/src/battle.ts`<br>`apps/game/src/ui/screens/SelectForce.ts` |
| knockback-targeting | 2051 | `packages/combat/src/combat.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |
| movement-physics | 2765 | `packages/combat/src/movement.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |

## Known Porting Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x8002bb14 | `FUN_8002bb14` | `battle_frame_target_action_dispatch` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:5844` |
| 0x8002cb20 | `zz_002cb20_` | `mutual_actor_contact_mask_update` | force-setup, knockback-targeting | `research/decomp/ghidra-export/chunk_0003.c:6454` |
| 0x8002d7c4 | `zz_002d7c4_` | `collision_hit_pair_pass_active_vs_borgs` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7026` |
| 0x8002db58 | `zz_002db58_` | `collision_hit_pair_pass_active_vs_secondary` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7168` |
| 0x8002df08 | `zz_002df08_` | `collision_hit_pair_pass_object_lists` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7310` |
| 0x8002e2a8 | `zz_002e2a8_` | `resolve_hitbox_target_effects_and_damage` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7473` |
| 0x800300bc | `zz_00300bc_` | `compute_knockback_launch_direction` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:8540` |
| 0x8003cd5c | `zz_003cd5c_` | `compute_base_damage_formula` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting | `research/decomp/ghidra-export/chunk_0004.c:6667` |
| 0x8003d344 | `zz_003d344_` | `apply_hp_damage_subtract_clamp` | challenge-menu-flow, battle-initialization, damage | `research/decomp/ghidra-export/chunk_0004.c:6832` |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0007.c:896` |
| 0x800680d4 | `zz_00680d4_` | `dispatch_slot_action_update` | challenge-menu-flow, force-setup, battle-initialization, knockback-targeting | `research/decomp/ghidra-export/chunk_0008.c:4366` |
| 0x80068138 | `FUN_80068138` | `reset_actor_param_tier` | challenge-menu-flow, battle-initialization | `research/decomp/ghidra-export/chunk_0008.c:4389` |
| 0x8006817c | `zz_006817c_` | `apply_actor_param_tier_delta_127` | challenge-menu-flow, battle-initialization | `research/decomp/ghidra-export/chunk_0008.c:4410` |
| 0x800681e4 | `zz_00681e4_` | `apply_actor_param_tier_delta_63` | challenge-menu-flow, battle-initialization, knockback-targeting | `research/decomp/ghidra-export/chunk_0008.c:4442` |
| 0x8006826c | `zz_006826c_` | `refresh_actor_param_tier_table` |  | `research/decomp/ghidra-export/chunk_0008.c:4484` |
| 0x80066298 | `zz_0066298_` | `lookup_type_category_table` | damage | `research/decomp/ghidra-export/chunk_0008.c:2976` |
| 0x8006ab04 | `zz_006ab04_` | `start_forced_move_to_point` | knockback-targeting | `research/decomp/ghidra-export/chunk_0009.c:1056` |
| 0x8006abd4 | `zz_006abd4_` | `react_to_slot_target_object` | force-setup, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0009.c:1115` |
| 0x8006ace8 | `zz_006ace8_` | `start_status_reaction_by_side` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0009.c:1161` |
| 0x801962c4 | `build_challenge_battle_setup` | `challenge_force_slot_team_setup` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0048.c:234` |
| 0x802807ac | `cPlayer::ClearSwapControllerTimer(void)` | `player_clear_swap_controller_timer` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:3819` |
| 0x80281c38 | `zz_0281c38_` | `death_swap_flow_candidate` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:4844` |
| 0x80297538 | `zz_0297538_` | `team_player_lookup_band_head` |  | `research/decomp/ghidra-export/chunk_0076.c:18706` |
| 0x802a3938 | `cTeam::GetPlayer(int)` | `team_get_player` | force-setup | `research/decomp/ghidra-export/chunk_0078.c:2079` |

## Usage

- Query by address to get current name, chunk/line, callers/callees, globals, constants, strings/assets, and related web modules.
- Treat `inferredName` as a navigation hint only; original-game evidence remains call graph, constants/tables, asset opens, traces, and behavior.
- For Challenge flow, start from `challenge-menu-flow`, `force-setup`, and `battle-initialization` topics before replacing browser player-facing behavior.

