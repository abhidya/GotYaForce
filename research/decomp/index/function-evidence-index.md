# Ghidra Function Evidence Index

Generated: 2026-07-01T09:36:51.788Z

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
| force-setup | 1565 | `packages/missions/src/challenge.ts`<br>`packages/combat/src/battle.ts`<br>`apps/game/src/ui/screens/SelectForce.ts` |
| knockback-targeting | 2045 | `packages/combat/src/combat.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |
| movement-physics | 2765 | `packages/combat/src/movement.ts`<br>`packages/physics/src/index.ts`<br>`apps/game/src/sim/battleScene.ts` |
| stage-load-collision | 28 | `apps/game/src/sim/adapter.ts`<br>`apps/game/src/main.ts`<br>`packages/formats/src/hit-bin.ts` |

## Known Porting Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x8002e2a8 | `zz_002e2a8_` | `per_borg_update_damage_dispatch` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7457` |
| 0x800300bc | `zz_00300bc_` | `compute_knockback_launch_direction` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:8515` |
| 0x8003cd5c | `zz_003cd5c_` | `compute_base_damage_formula` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting | `research/decomp/ghidra-export/chunk_0004.c:6667` |
| 0x8003d344 | `zz_003d344_` | `apply_hp_damage_subtract_clamp` | challenge-menu-flow, battle-initialization, damage | `research/decomp/ghidra-export/chunk_0004.c:6832` |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0007.c:896` |
| 0x80066298 | `zz_0066298_` | `lookup_type_category_table` | damage | `research/decomp/ghidra-export/chunk_0008.c:2976` |
| 0x802807ac | `cPlayer::ClearSwapControllerTimer(void)` | `player_clear_swap_controller_timer` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:3819` |
| 0x80281c38 | `zz_0281c38_` | `death_swap_flow_candidate` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:4844` |
| 0x80297538 | `zz_0297538_` | `team_player_lookup_band_head` |  | `research/decomp/ghidra-export/chunk_0076.c:18706` |
| 0x802a3938 | `cTeam::GetPlayer(int)` | `team_get_player` | force-setup | `research/decomp/ghidra-export/chunk_0078.c:2079` |

## Usage

- Query by address to get current name, chunk/line, callers/callees, globals, constants, strings/assets, and related web modules.
- Treat `inferredName` as a navigation hint only; original-game evidence remains call graph, constants/tables, asset opens, traces, and behavior.
- For Challenge flow, start from `challenge-menu-flow`, `force-setup`, and `battle-initialization` topics before replacing browser player-facing behavior.

