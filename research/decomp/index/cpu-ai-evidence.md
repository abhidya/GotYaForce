# CPU AI / Targeting Evidence

> **SUPERSEDED 2026-07-06 — the decision brain WAS found statically.** See
> `research/decomp/cpu-ai-decode-2026-07-06.md`: AI root = `zz_001c9d0_` @0x8001c9d0,
> dispatched from the per-actor input refresh `FUN_80056900` when the CPU flag
> actor+0x3e6 is set (bound at `FUN_800541ac` init from the pad-present mask — this
> file's 2026-07-03 lead, confirmed). The AI writes the actor-embedded virtual pad
> (+0x5b4/+0x5ca) directly; the `set_slot_action_handler` table below remains correctly
> ruled OUT (replay input-stream buffers). The "Dolphin write-watch needed" next step is
> replaced by the static decode; a Dolphin pass is now only CONFIRMATION (doc §5).
> Anchors below are kept for their still-valid per-function evidence.

Generated: 2026-07-01T11:00:00.390Z

## Principle

CPU AI porting must use original target/action/effect code and confirmed slot/team data. These names are evidence labels; unconfirmed decision-brain code remains unrenamed.

## Function Anchors

| Address | Current name | Inferred name | System | Source |
| --- | --- | --- | --- | --- |
| 0x801962c4 | `build_challenge_battle_setup` | `challenge_force_slot_team_setup` | Challenge CPU/player slot setup | `research/decomp/ghidra-export/chunk_0048.c:234` |
| 0x8002bb14 | `battle_frame_target_action_dispatch` | `battle_frame_target_action_dispatch` | Per-frame CPU/player shared target and action dispatch | `research/decomp/ghidra-export/chunk_0003.c:5844` |
| 0x8002cb20 | `mutual_actor_contact_mask_update` | `mutual_actor_contact_mask_update` | Actor eligibility / contact mask update | `research/decomp/ghidra-export/chunk_0003.c:6454` |
| 0x8002e2a8 | `resolve_hitbox_target_effects_and_damage` | `resolve_hitbox_target_effects_and_damage` | Hitbox target effects, target memory, and damage dispatch | `research/decomp/ghidra-export/chunk_0003.c:7473` |
| 0x800681e4 | `apply_actor_param_tier_delta_63` | `apply_actor_param_tier_delta_63` | Actor param-tier modifier applied from per-slot effect delta | `research/decomp/ghidra-export/chunk_0008.c:4442` |
| 0x8006ab04 | `start_forced_move_to_point` | `start_forced_move_to_point` | Forced move / point reaction | `research/decomp/ghidra-export/chunk_0009.c:1056` |
| 0x8006abd4 | `react_to_slot_target_object` | `react_to_slot_target_object` | Stored target reaction | `research/decomp/ghidra-export/chunk_0009.c:1115` |
| 0x8010d880 | `set_slot_action_handler` | `set_slot_action_handler` | Per-slot action handler dispatch | `research/decomp/ghidra-export/chunk_0030.c:2601` |

### 0x801962c4 challenge_force_slot_team_setup

Builds Challenge slot/team state and force roster entries before active actors spawn.

- Current function: `build_challenge_battle_setup`
- Callers: none indexed
- Callees: 0x800055fc `zz_00055fc_`, 0x800064d4 `zz_00064d4_`, 0x8000685c `zz_000685c_`, 0x80027c1c `zz_0027c1c_`, 0x80029fd4 `zz_0029fd4_`, 0x80066168 `zz_0066168_`, 0x80196eb8 `zz_0196eb8_`
- Related web modules: `packages/missions/src/challenge.ts`, `packages/combat/src/battle.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0048.c:281` contains `PTR_DAT_80433934[iVar4 + 0xcb] = 0xff`
  - `research/decomp/ghidra-export/chunk_0048.c:327` contains `PTR_DAT_80433934[iVar4 + 0xcb] = 1`
  - `research/decomp/ghidra-export/chunk_0048.c:360` contains `PTR_DAT_80433934[iVar4 + 0x5a] = PTR_DAT_80433934[iVar4 + 0x5a] +`
  - `research/decomp/ghidra-export/chunk_0048.c:3146` contains `*(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb]`

### 0x8002bb14 battle_frame_target_action_dispatch

Main active actor loop resets slot target/effect state, runs target/contact passes, applies target reactions, and dispatches per-slot action updates.

- Current function: `battle_frame_target_action_dispatch`
- Callers: 0x80029434 `zz_0029434_`, 0x80029708 `zz_0029708_`
- Callees: 0x8002c994 `zz_002c994_`, 0x8002caa8 `zz_002caa8_`, 0x8002cb20 `mutual_actor_contact_mask_update`, 0x8002cc78 `zz_002cc78_`, 0x8002cda4 `zz_002cda4_`, 0x8002ce44 `zz_002ce44_`, 0x8002cf80 `zz_002cf80_`, 0x8002d198 `zz_002d198_`, 0x8002d35c `zz_002d35c_`, 0x8002d58c `zz_002d58c_`, 0x8002d7c4 `collision_hit_pair_pass_active_vs_borgs`, 0x8002db58 `collision_hit_pair_pass_active_vs_secondary`, 0x8002df08 `collision_hit_pair_pass_object_lists`, 0x8002e1c8 `zz_002e1c8_`, 0x8002f8dc `zz_002f8dc_`, 0x8003d3e8 `zz_003d3e8_`
- Related web modules: `packages/combat/src/ai.ts`, `packages/combat/src/battle.ts`, `packages/combat/src/combat.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0003.c:5956` contains `*(undefined4 *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4) = 0`
  - `research/decomp/ghidra-export/chunk_0003.c:5960` contains `(&DAT_8043612c)[pcVar10[0x3e4]] = 0`
  - `research/decomp/ghidra-export/chunk_0003.c:6248` contains `apply_actor_param_tier_delta_63((int)pcVar10,(int)(char)(&DAT_8043612c)[pcVar10[0x3e4]])`
  - `research/decomp/ghidra-export/chunk_0003.c:6302` contains `react_to_slot_target_object((int)pcVar10,*(int *)(&DAT_803b06a8 + pcVar10[0x3e4] * 4))`
  - `research/decomp/ghidra-export/chunk_0003.c:6262` contains `dVar25 = (double)dispatch_slot_action_update((int)pcVar10,0)`

### 0x8002cb20 mutual_actor_contact_mask_update

Pairwise active actor pass gated by mutual 0x71e/0x71f slot masks before contact-vector update.

- Current function: `mutual_actor_contact_mask_update`
- Callers: 0x8002bb14 `battle_frame_target_action_dispatch`
- Callees: 0x80035ca4 `zz_0035ca4_`
- Related web modules: `packages/combat/src/ai.ts`, `packages/combat/src/combat.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0003.c:6479` contains `((int)pcVar4[0x71e] & 1 << (int)pcVar3[0x3e4])`
  - `research/decomp/ghidra-export/chunk_0003.c:6482` contains `((int)pcVar3[0x71f] & 1 << (int)pcVar4[0x3e4])`
  - `research/decomp/ghidra-export/chunk_0003.c:6489` contains `zz_0035ca4_((int)pcVar4,(float *)(pcVar3 + 0x1cc))`

### 0x8002e2a8 resolve_hitbox_target_effects_and_damage

Shared hit/effect resolver. It writes target pointers, last-enemy markers, effect deltas, damage accounting, knockback direction, base damage, and HP subtraction.

- Current function: `resolve_hitbox_target_effects_and_damage`
- Callers: 0x8002d7c4 `collision_hit_pair_pass_active_vs_borgs`, 0x8002db58 `collision_hit_pair_pass_active_vs_secondary`, 0x8002df08 `collision_hit_pair_pass_object_lists`
- Callees: 0x800061a8 `FUN_800061a8`, 0x80006c24 `zz_0006c24_`, 0x80019550 `zz_0019550_`, 0x8002f8d0 `zz_002f8d0_`, 0x8002f8dc `zz_002f8dc_`, 0x8002fc18 `zz_002fc18_`, 0x8002fcbc `zz_002fcbc_`, 0x800300bc `zz_00300bc_`, 0x8003cd5c `zz_003cd5c_`, 0x8003d344 `zz_003d344_`, 0x800db250 `zz_00db250_`, 0x8010e158 `zz_010e158_`, 0x8013f300 `zz_013f300_`, 0x80176ec0 `zz_0176ec0_`, 0x8018214c `zz_018214c_`, 0x801dff24 `zz_01dff24_`
- Related web modules: `packages/combat/src/combat.ts`, `packages/combat/src/ai.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0003.c:7718` contains `*(char **)(&DAT_803b06a8 + pcVar16[0x3e4] * 4) = pcVar18`
  - `research/decomp/ghidra-export/chunk_0003.c:7910` contains `pcVar18[2000] = pcVar16[0x3e4]`
  - `research/decomp/ghidra-export/chunk_0003.c:7911` contains `pcVar18[0x7d1] = '\x0f'`
  - `research/decomp/ghidra-export/chunk_0003.c:7763` contains `(&DAT_8043612c)[pcVar18[0x3e4]]`
  - `research/decomp/ghidra-export/chunk_0003.c:7945` contains `zz_00300bc_(param_1,param_2,(int)*(char *)(puVar17 + 7))`
  - `research/decomp/ghidra-export/chunk_0003.c:7948` contains `uVar10 = zz_003cd5c_(puVar17,iVar19,pcVar18)`
  - `research/decomp/ghidra-export/chunk_0003.c:7989` contains `uVar10 = zz_003d344_((int)pcVar18,(short)uVar10)`

### 0x800681e4 apply_actor_param_tier_delta_63

Applies the signed DAT_8043612c slot delta to actor+0x74a with a narrower [-63, 63] clamp, then refreshes table-backed actor params.

- Current function: `apply_actor_param_tier_delta_63`
- Callers: 0x8002bb14 `battle_frame_target_action_dispatch`
- Callees: 0x8006817c `apply_actor_param_tier_delta_127`
- Related web modules: `packages/combat/src/stats.ts`, `packages/combat/src/combat.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0008.c:4459` contains `current_tier = (int)*(char *)(actor + 0x74a)`
  - `research/decomp/ghidra-export/chunk_0008.c:4461` contains `if (desired_tier < 0x40)`
  - `research/decomp/ghidra-export/chunk_0008.c:4475` contains `*(undefined2 *)(actor + 0x750) = 900`
  - `research/decomp/ghidra-export/chunk_0008.c:4477` contains `apply_actor_param_tier_delta_127(actor,applied_delta)`

### 0x8006ab04 start_forced_move_to_point

Stores a per-slot world target vector and enters a movement/action state. This is evidence for target-vector mechanics, not enough by itself to rename CPU decision code.

- Current function: `start_forced_move_to_point`
- Callers: 0x8002bb14 `battle_frame_target_action_dispatch`, 0x8006478c `FUN_8006478c`
- Callees: 0x8006a7b4 `zz_006a7b4_`, 0x8006a7f4 `zz_006a7f4_`, 0x800f036c `zz_00f036c_`
- Related web modules: `packages/combat/src/movement.ts`, `packages/combat/src/ai.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0009.c:1073` contains `*(undefined4 *)(actor + 0x7bc) = *target_vec3`
  - `research/decomp/ghidra-export/chunk_0009.c:1071` contains `*(uint *)(actor + 0x5e0) = *(uint *)(actor + 0x5e0) | 0x1000`
  - `research/decomp/ghidra-export/chunk_0009.c:1080` contains `zz_006a7b4_(actor,0x23)`

### 0x8006abd4 react_to_slot_target_object

Consumes DAT_803b06a8 target pointer, reads target object type/category, enters status/action state, and plays a side-aware cue.

- Current function: `react_to_slot_target_object`
- Callers: 0x8002bb14 `battle_frame_target_action_dispatch`
- Callees: 0x8006a868 `zz_006a868_`, 0x80176ec0 `zz_0176ec0_`
- Related web modules: `packages/combat/src/ai.ts`, `packages/combat/src/combat.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0009.c:1128` contains `if (*(char *)(target_actor + 0x4a0) == '\0')`
  - `research/decomp/ghidra-export/chunk_0009.c:1131` contains `zz_006a868_(actor,*(undefined2 *)(target_actor + 1000)`
  - `research/decomp/ghidra-export/chunk_0009.c:1133` contains `*(undefined2 *)(actor + 0x49a) = 900`
  - `research/decomp/ghidra-export/chunk_0009.c:1153` contains `zz_0176ec0_(actor,*(undefined1 *)(actor + 0x88),1)`

### 0x8010d880 set_slot_action_handler

Writes a slot's action handler from a 6-entry mode table when the slot is active. This is the final shared dispatch path reached after target/effect resolution.

- Current function: `set_slot_action_handler`
- Callers: 0x800680d4 `dispatch_slot_action_update`, 0x800ff698 `zz_00ff698_`
- Callees: none indexed
- Related web modules: `packages/combat/src/battle.ts`, `packages/combat/src/ai.ts`
- Evidence:
  - `research/decomp/ghidra-export/chunk_0030.c:2612` contains `PTR_DAT_8043394c[0x30] & 1 << slot_index`
  - `research/decomp/ghidra-export/chunk_0030.c:2615` contains `(&DAT_803c735c)[slot_index] = (&PTR_DAT_80325af4)[action_mode % 6]`
  - `research/decomp/ghidra-export/chunk_0030.c:2616` contains `(&DAT_803c736c)[slot_index] = 0`

## Field / Struct Aliases

| Owner | Offset/global | Inferred name | Confidence | Evidence |
| --- | --- | --- | --- | --- |
| ActiveBorgObject | `0x83` | `action_state` | evidence-backed | `research/decomp/ghidra-export/chunk_0003.c:7519`<br>`research/decomp/ghidra-export/chunk_0003.c:7591` |
| ActiveBorgObject | `0x88` | `match_side_from_slot_table` | confirmed | `research/decomp/ghidra-export/chunk_0048.c:3146` |
| ActiveBorgObject | `0x3e4` | `active_slot_index` | confirmed | `research/decomp/ghidra-export/chunk_0003.c:5956`<br>`research/decomp/ghidra-export/chunk_0003.c:6479` |
| ActiveBorgObject | `0x71e/0x71f` | `mutual_actor_slot_masks` | evidence-backed | `research/decomp/ghidra-export/chunk_0003.c:6479`<br>`research/decomp/ghidra-export/chunk_0003.c:6482` |
| ActiveBorgObject | `2000 / 0x7d1` | `last_enemy_slot_and_timer` | evidence-backed | `research/decomp/ghidra-export/chunk_0003.c:7910`<br>`research/decomp/ghidra-export/chunk_0003.c:7911`<br>`research/decomp/ghidra-export/chunk_0003.c:5917` |
| ActiveBorgObject | `0x74a/0x74b/0x74c/0x74d/0x74e/0x750` | `param_tier_state` | evidence-backed | `research/decomp/ghidra-export/chunk_0008.c:4423`<br>`research/decomp/ghidra-export/chunk_0008.c:4504`<br>`research/decomp/ghidra-export/chunk_0008.c:4475` |
| Global | `DAT_803b06a8` | `slot_target_object_ptrs` | confirmed | `research/decomp/ghidra-export/chunk_0003.c:5956`<br>`research/decomp/ghidra-export/chunk_0003.c:7718`<br>`research/decomp/ghidra-export/chunk_0003.c:6302` |
| Global | `DAT_8043612c` | `slot_param_tier_delta` | evidence-backed | `research/decomp/ghidra-export/chunk_0003.c:5960`<br>`research/decomp/ghidra-export/chunk_0003.c:7763`<br>`research/decomp/ghidra-export/chunk_0003.c:6248` |
| Global | `DAT_803b06c0/DAT_803b06c4/DAT_803b06c8` | `slot_world_target_vec3` | evidence-backed | `research/decomp/ghidra-export/chunk_0003.c:7694`<br>`research/decomp/ghidra-export/chunk_0003.c:6270` |
| PTR_DAT_80433934 | `slot+0xcb / slot+0xcc` | `slot_match_side` | confirmed | `research/decomp/ghidra-export/chunk_0048.c:281`<br>`research/decomp/ghidra-export/chunk_0048.c:291` |

## Class Aliases

- `ActiveBorgObject`: struct alias only; Repeated DAT_803c4e84 active loop with 0x1e00 stride and active fields. No original C++ class name confirmed yet.
- `MatchState`: struct alias only; PTR_DAT_80433934 carries match/force/slot state, active slot masks, rosters, and per-side values.
- `cTeam`: symbol-map confirmed; 0x802a3938 cTeam::GetPlayer(int)
- `cPlayer`: symbol-map confirmed; 0x802807ac cPlayer::ClearSwapControllerTimer(void)

## Porting Notes

- Do not implement CPU AI as nearest-enemy-only long term. Original code keeps per-slot target object pointers and short-lived last-enemy slot memory.
- Keep object+0x88 as match side/team from PTR_DAT_80433934[slot+0xcb]. It is not a borg display type.
- DAT_8043612c is an effect-driven signed param-tier delta, not proven CPU desire/input.
- The CPU decision-brain function is not fully isolated by this pass; current evidence covers shared target/effect/action dispatch used by CPU and player-controlled actors.



## Update 2026-07-03: 0x8010d880 mode-table lead closed (negative)

The 6-entry table `PTR_DAT_80325af4` consumed by `set_slot_action_handler` @0x8010d880 was
extracted from the DOL: entries are DATA pointers (0x80434510/518/520 blocks of
{bufferAddr 0x800a4000/0x80144000/0x801e4000, mask 0xffff0000}; mode 3 -> const block
0x80325ae8), i.e. per-slot INPUT-STREAM/replay-buffer descriptors, not behavior functions.
`set_slot_action_handler` is demo/input-source plumbing. The CPU decision brain remains
NOT isolated; the "shared dispatch only" conclusion of this document stands. Next viable
lead: trace who WRITES the per-slot PlayerInput-equivalent for slots whose pad mask bit in
PTR_DAT_80433930[2] is clear (CPU slots) inside the per-frame loop — a Dolphin write-watch
on the pad-state mirror for a CPU slot is the cheapest decisive capture.
