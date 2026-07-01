# Challenge Flow Evidence Map

Generated: 2026-07-01T09:41:43.642Z

## Principle

Do not replace player-facing Challenge flow with fake menus/stages/mechanics. Each step below must be driven by original functions, data tables, asset opens, traces, or behavior.

## main menu -> Challenge Mode selection

### Original Function Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x80195fbc | `FUN_80195fbc` | `challenge-menu-flow_candidate_80195fbc` | challenge-menu-flow, battle-initialization | `research/decomp/ghidra-export/chunk_0048.c:127` |
| 0x801962c4 | `FUN_801962c4` | `challenge-menu-flow_candidate_801962c4` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0048.c:226` |
| 0x80199da0 | `zz_0199da0_` | `challenge-menu-flow_candidate_80199da0` | challenge-menu-flow | `research/decomp/ghidra-export/chunk_0048.c:2797` |

### Supporting Artifacts

- `research/asset-inventory/ui-hud-assets.md`

### Topic Fallback Candidates

- 0x801969a0 `FUN_801969a0` at `research/decomp/ghidra-export/chunk_0048.c:451`; globals DAT_80436378, PTR_DAT_80433930, PTR_DAT_80433934.
- 0x80196030 `FUN_80196030` at `research/decomp/ghidra-export/chunk_0048.c:145`; globals DAT_80436378, PTR_DAT_80433944, DAT_804356d0, PTR_DAT_80433934, DAT_8036f554.
- 0x80195f2c `FUN_80195f2c` at `research/decomp/ghidra-export/chunk_0048.c:109`; globals DAT_80436378, DAT_803d4960, PTR_DAT_80433930, PTR_FUN_8036f560.
- 0x80196188 `FUN_80196188` at `research/decomp/ghidra-export/chunk_0048.c:191`; globals DAT_80436378, PTR_DAT_80435a30, PTR_DAT_80433944, DAT_803bfe20.
- 0x80196a9c `FUN_80196a9c` at `research/decomp/ghidra-export/chunk_0048.c:495`; globals DAT_80436378, PTR_DAT_80433930.
- 0x80196cec `FUN_80196cec` at `research/decomp/ghidra-export/chunk_0048.c:603`; globals DAT_80436378, PTR_DAT_80433930.

### Current Web Evidence

- `apps/game/src/main.ts:9` contains `MainMenu -> (challenge)`.
- `apps/game/src/ui/screens/MainMenu.ts:4` contains `The real game renders this as a 3D desk diorama`.

### Required Before Player-Facing Port

- Identify the selected menu mode state variable and transition value that enters Challenge.
- Confirm asset opens for title/menu objects/textures before replacing player-facing MainMenu.

## Challenge selection -> force/player setup

### Original Function Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x802a3938 | `cTeam::GetPlayer(int)` | `team_get_player` | force-setup | `research/decomp/ghidra-export/chunk_0078.c:2079` |
| 0x802807ac | `cPlayer::ClearSwapControllerTimer(void)` | `player_clear_swap_controller_timer` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:3819` |
| 0x80281c38 | `zz_0281c38_` | `death_swap_flow_candidate` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:4844` |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0007.c:896` |

### Supporting Artifacts

- `research/asset-inventory/borg-assets.md`
- `research/animation-actions/borg-action-assets.md`

### Topic Fallback Candidates

- 0x8002bb14 `FUN_8002bb14` at `research/decomp/ghidra-export/chunk_0003.c:5844`; globals DAT_803b068c, PTR_DAT_80433934, DAT_80436154, DAT_803b069c, DAT_803b0690.
- 0x800289fc `FUN_800289fc` at `research/decomp/ghidra-export/chunk_0003.c:3897`; globals PTR_DAT_80433934, FLOAT_80436ef8, DAT_803c4e84, PTR_DAT_80433930, DAT_8031a074.
- 0x8002e2a8 `zz_002e2a8_` at `research/decomp/ghidra-export/chunk_0003.c:7457`; globals FLOAT_80436fa0, DOUBLE_80436fb0, FLOAT_80436f7c, FLOAT_80436f78, DOUBLE_80436f88.
- 0x800a98a4 `FUN_800a98a4` at `research/decomp/ghidra-export/chunk_0016.c:4168`; globals PTR_DAT_80433934, FLOAT_80438150, FLOAT_80438154, FLOAT_80438158, FLOAT_8043815c.
- 0x8009cc48 `FUN_8009cc48` at `research/decomp/ghidra-export/chunk_0015.c:3230`; globals PTR_DAT_80433934, DAT_803c4e84, FLOAT_80437ec8, FLOAT_80437ecc, FLOAT_80437ed0.
- 0x801c795c `FUN_801c795c` at `research/decomp/ghidra-export/chunk_0055.c:2227`; globals PTR_DAT_80433934, DAT_8038a4ec, DAT_80436238, DAT_803c71dc, DAT_803c71e0.
- 0x800107a0 `zz_00107a0_` at `research/decomp/ghidra-export/chunk_0001.c:3244`; globals PTR_DAT_80433934.

### Current Web Evidence

- `packages/missions/src/challenge.ts:7` contains `FIGHT ALONE`.
- `apps/game/src/ui/screens/SelectForce.ts:49` contains `SELECT A FORCE`.
- `apps/game/src/ui/screens/ForceBuilder.ts:2` contains `ForceBuilder`.

### Required Before Player-Facing Port

- Trace slot/team table writes for PTR_DAT_80433934 offsets 0x10, 0x20, 0x32, 0x3e, 0x5a, 0xa0, and 0xcb.
- Confirm the original ordered-force spawn/death swap path before changing Challenge roster behavior.

## force setup -> stage/load flow

### Original Function Anchors

No original C function anchor is confirmed by the current index for this step.

### Supporting Artifacts

- `research/asset-inventory/stage-code-evidence.md`
- `research/asset-inventory/stage-geometry-collision.md`
- `research/asset-inventory/stage-lighting-render-state.md`

### Current Web Evidence

- `apps/game/src/sim/adapter.ts:23` contains `DEFAULT_ARENA_STAGE`.
- `apps/game/src/sim/adapter.ts:35` contains `normalized === "challenge"`.
- `apps/game/src/main.ts:559` contains `async function loadStage`.

### Required Before Player-Facing Port

- Break/trace archive open path for Challenge battle 1 and record the selected st## ids.
- Only map arena names to st## after a DOL/load trace or direct data table proves the mapping.

## stage/load flow -> battle initialization

### Original Function Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | challenge-menu-flow, force-setup, battle-initialization, movement-physics | `research/decomp/ghidra-export/chunk_0007.c:896` |
| 0x8002e2a8 | `zz_002e2a8_` | `per_borg_update_damage_dispatch` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:7457` |

### Supporting Artifacts

- `research/decomp/data/type-category-remap-802f2e28.json`

### Topic Fallback Candidates

- 0x80083714 `zz_0083714_` at `research/decomp/ghidra-export/chunk_0012.c:2829`; globals FLOAT_80437ae4, PTR_DAT_80433934, FLOAT_80437b10, FLOAT_80437b08, FLOAT_80437b0c.
- 0x8000726c `zz_000726c_` at `research/decomp/ghidra-export/chunk_0000.c:1713`; globals PTR_DAT_80433934, DOUBLE_80436a48.
- 0x8002bb14 `FUN_8002bb14` at `research/decomp/ghidra-export/chunk_0003.c:5844`; globals DAT_803b068c, PTR_DAT_80433934, DAT_80436154, DAT_803b069c, DAT_803b0690.
- 0x8002844c `FUN_8002844c` at `research/decomp/ghidra-export/chunk_0003.c:3628`; globals PTR_DAT_80433934, PTR_DAT_80433930, DAT_80436238, DAT_803c71dc, DAT_803c71e0.
- 0x800289fc `FUN_800289fc` at `research/decomp/ghidra-export/chunk_0003.c:3897`; globals PTR_DAT_80433934, FLOAT_80436ef8, DAT_803c4e84, PTR_DAT_80433930, DAT_8031a074.
- 0x80069814 `FUN_80069814` at `research/decomp/ghidra-export/chunk_0009.c:102`; globals PTR_DAT_80433934.
- 0x8008b290 `zz_008b290_` at `research/decomp/ghidra-export/chunk_0013.c:1674`; globals PTR_DAT_80433934.
- 0x8008b480 `zz_008b480_` at `research/decomp/ghidra-export/chunk_0013.c:1769`; globals PTR_DAT_80433934.

### Current Web Evidence

- `packages/combat/src/battle.ts:326` contains `export function createBattle`.
- `apps/game/src/sim/adapter.ts:10` contains `convertBattleConfig`.
- `apps/game/src/main.ts:1028` contains `const battle = createBattle`.

### Required Before Player-Facing Port

- Map active borg object fields copied from slot table into combat runtime shape.
- Preserve object+0x88 as slot/team state and object+1000 as the separate type-category source.

## battle initialization -> HUD/gameplay

### Original Function Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x8003d344 | `zz_003d344_` | `apply_hp_damage_subtract_clamp` | challenge-menu-flow, battle-initialization, damage | `research/decomp/ghidra-export/chunk_0004.c:6832` |
| 0x8003cd5c | `zz_003cd5c_` | `compute_base_damage_formula` | challenge-menu-flow, force-setup, battle-initialization, damage, knockback-targeting | `research/decomp/ghidra-export/chunk_0004.c:6667` |
| 0x80066298 | `zz_0066298_` | `lookup_type_category_table` | damage | `research/decomp/ghidra-export/chunk_0008.c:2976` |
| 0x800300bc | `zz_00300bc_` | `compute_knockback_launch_direction` | knockback-targeting, movement-physics | `research/decomp/ghidra-export/chunk_0003.c:8515` |

### Supporting Artifacts

- `research/decomp/data/type-multiplier-matrix-802c5d60.json`
- `research/asset-inventory/common-battle-data.md`
- `research/asset-inventory/weapons-effects-projectiles.md`

### Topic Fallback Candidates

- 0x8002bb14 `FUN_8002bb14` at `research/decomp/ghidra-export/chunk_0003.c:5844`; globals DAT_803b068c, PTR_DAT_80433934, DAT_80436154, DAT_803b069c, DAT_803b0690.
- 0x80218a1c `zz_0218a1c_` at `research/decomp/ghidra-export/chunk_0065.c:4213`; globals DAT_80436770, DAT_803dfbec, DAT_803dfc44, DAT_803dfc5a, DAT_803dfc5c.
- 0x8002e2a8 `zz_002e2a8_` at `research/decomp/ghidra-export/chunk_0003.c:7457`; globals FLOAT_80436fa0, DOUBLE_80436fb0, FLOAT_80436f7c, FLOAT_80436f78, DOUBLE_80436f88.
- 0x801d35a0 `FUN_801d35a0` at `research/decomp/ghidra-export/chunk_0056.c:4963`; globals FLOAT_8043be3c, FLOAT_8043be38, DAT_8038b240, DAT_8038b234, DAT_8038b230.
- 0x800e075c `FUN_800e075c` at `research/decomp/ghidra-export/chunk_0024.c:818`; globals DAT_80316f00, DAT_80316efc, DAT_80316f04, DAT_80316f08, DAT_80316f0c.
- 0x800141d8 `zz_00141d8_` at `research/decomp/ghidra-export/chunk_0001.c:5964`; globals DOUBLE_80436bd0, FLOAT_80436c60, FLOAT_80436c64, DAT_804361fc, FLOAT_80436c68.
- 0x800fe818 `FUN_800fe818` at `research/decomp/ghidra-export/chunk_0028.c:1290`; globals DAT_8031ef80, DAT_8031ef38, DAT_802b0cb8, DAT_802b0cb4, DAT_802b0cbc.
- 0x80128fec `FUN_80128fec` at `research/decomp/ghidra-export/chunk_0034.c:442`; globals DAT_80330b08, DAT_803309fe, DAT_803309f8, DAT_803309fc, DAT_803309ea.

### Current Web Evidence

- `packages/combat/src/combat.ts:114` contains `function applyHit`.
- `packages/combat/src/constants.ts:3` contains `TUNED`.
- `apps/game/src/ui/hud/BattleHud.ts:2` contains `BattleHud`.

### Required Before Player-Facing Port

- Port damage from zz_003cd5c_ only after table inputs and object+1000 category source are confirmed.
- Port knockback as computed direction from zz_00300bc_, not as flat tuned scalar.
- Keep HUD mirrors separate from authoritative HP fields.

## HUD/gameplay -> victory/defeat/progression

### Original Function Anchors

| Address | Current name | Inferred hint | Topics | Source |
| --- | --- | --- | --- | --- |
| 0x802807ac | `cPlayer::ClearSwapControllerTimer(void)` | `player_clear_swap_controller_timer` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:3819` |
| 0x80281c38 | `zz_0281c38_` | `death_swap_flow_candidate` | force-setup | `research/decomp/ghidra-export/chunk_0076.c:4844` |

### Supporting Artifacts

- `packages/missions/src/challenge.ts`

### Current Web Evidence

- `packages/missions/src/challenge.ts:111` contains `next(result: BattleResults)`.
- `apps/game/src/main.ts:1269` contains `function advanceRun`.
- `apps/game/src/ui/screens/Results.ts:2` contains `Results`.

### Required Before Player-Facing Port

- Trace player swap/death transition around cPlayer::ClearSwapControllerTimer and adjacent functions.
- Confirm original Challenge win/loss branch and next-battle counter before replacing Results progression.

