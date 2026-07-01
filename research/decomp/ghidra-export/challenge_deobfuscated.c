/*
 * Deobfuscated Challenge-mode companion for the raw Ghidra export.
 *
 * This is a readable C sidecar, not a replacement for the generated chunks.
 * It gives stable names to the relevant raw functions and tables:
 *
 *   0x80195fbc  FUN_80195fbc      Challenge_ClearSlotState_80195fbc
 *   0x801962c4  FUN_801962c4      Challenge_SetupBattle_801962c4
 *   0x80196dac  zz_0196dac_       Challenge_SelectStage_80196dac
 *   0x80196eb8  zz_0196eb8_       Challenge_RandomBorgFromGroup_80196eb8
 *   0x800541ac  FUN_800541ac      Battle_SpawnActiveBorgFromSlotTables_800541ac
 *   0x80057b78  FUN_80057b78      Battle_InitActiveObjectFromSlotTables_80057b78
 *
 * Raw struct/global anchors:
 *   PTR_DAT_80433934 is the battle/slot table.
 *   DAT_80436378[0x13] is the selected Challenge mode (0/1/2).
 *   DAT_80436378[8] is the current battle index.
 */

#include <stdbool.h>
#include <stdint.h>

enum ChallengeMode {
    CHALLENGE_NORMAL = 0,
    CHALLENGE_TUFF = 1,
    CHALLENGE_INSANE = 2,
};

enum ChallengeSide {
    CHALLENGE_SIDE_PLAYER = 0,
    CHALLENGE_SIDE_ENEMY = 1,
};

enum ChallengeSlotOffset {
    SLOT_ACTIVE_BORG_ID_BASE = 0x10,  /* uint16_t[6], copied into active object. */
    SLOT_STAGE_ID = 0x1c,             /* byte chosen from kChallengeStageIds. */
    SLOT_STAGE_SUBTABLE = 0x1d,       /* byte rand % 3. */
    SLOT_STAGE_VARIANT = 0x1e,        /* byte rand % variantCount. */
    SLOT_STATUS_20_BASE = 0x20,       /* byte[6], FUN_801962c4 writes 0x0e. */
    SLOT_TEAM_COLOR_BASE = 0x32,      /* byte[6], DAT_804356ec[side + mode*2]. */
    SLOT_STATE_3E_BASE = 0x3e,        /* byte[6], FUN_801962c4 writes 3. */
    SLOT_ROSTER_COUNT_BASE = 0x5a,    /* byte[6]. */
    SLOT_ACTIVE_VARIANT_BASE = 0xa0,  /* byte[6], copied with active borg id. */
    SLOT_TEAM_BASE = 0xcb,            /* byte[6], 0=player/ally, 1=enemy, 0xff=unused. */
    SLOT_ROSTER_BASE = 0x1e8,         /* per-slot roster entries, stride 0x1c. */
    SLOT_ACTIVE_MASK = 0x15d9,
    SLOT_ACTIVE_COUNT = 0x15da,
};

typedef struct ChallengeRoster {
    uint16_t borg_id[30];
    uint8_t variant[30];
    uint8_t count;
} ChallengeRoster;

typedef struct ChallengeBattleState {
    uint8_t slot_team[6];       /* PTR_DAT_80433934[slot + 0xcb] */
    uint8_t slot_status[6];     /* PTR_DAT_80433934[slot + 0x20] */
    uint8_t slot_state[6];      /* PTR_DAT_80433934[slot + 0x3e] */
    uint8_t slot_color[6];      /* PTR_DAT_80433934[slot + 0x32] */
    uint16_t active_borg_id[6]; /* PTR_DAT_80433934 + slot*2 + 0x10 */
    uint8_t active_variant[6];  /* PTR_DAT_80433934[slot + 0xa0] */
    ChallengeRoster roster[6];
    uint8_t stage_id;
    uint8_t stage_subtable;
    uint8_t stage_variant;
    uint16_t time_limit;
} ChallengeBattleState;

static const uint8_t kChallengeBattleCountByMode[3] = { 5, 10, 15 };

static const uint8_t kChallengeStageIds[11] = {
    0, 1, 2, 3, 4, 5, 8, 10, 11, 12, 14
};

static const uint16_t kChallengeAllyBudget[3][15] = {
    { 1000, 1000, 1200, 1200, 1400 },
    { 1200, 1200, 1400, 1400, 1600, 1600, 1800, 1800, 2000, 2200 },
    { 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200 },
};

static const uint16_t kChallengeEnemyBudget[3][15] = {
    { 1000, 1000, 1200, 1200, 1400 },
    { 1200, 1200, 1400, 1400, 1600, 1600, 1800, 1800, 2000, 2200 },
    { 1400, 1400, 1600, 1600, 1800, 1800, 2000, 2000, 2200, 2200, 2400, 2400, 2600, 2600, 2800 },
};

static const uint8_t kChallengeAllyMaxMembers[3][15] = {
    { 4, 4, 5, 5, 5 },
    { 4, 4, 4, 5, 5, 5, 6, 6, 6, 7 },
    { 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5 },
};

static const uint8_t kChallengeEnemyMaxMembers[3][15] = {
    { 10, 10, 8, 8, 1 },
    { 10, 10, 10, 10, 2, 10, 10, 10, 10, 2 },
    { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
};

/* Each battle picks one of four group codes with rand & 3. */
static const uint8_t kChallengeEnemyGroupCode[3][15][4] = {
    {
        {48,48,48,48}, {49,49,49,49}, {50,50,50,50}, {51,51,51,51}, {64,64,64,64},
    },
    {
        {49,49,49,49}, {50,50,50,50}, {51,51,51,51}, {52,52,52,52}, {66,66,66,66},
        {53,53,53,53}, {54,54,54,54}, {55,55,55,55}, {56,56,56,56}, {65,65,65,65},
    },
    {
        {50,50,50,50}, {51,51,51,51}, {52,52,52,52}, {54,54,54,54}, {67,67,67,67},
        {64,53,53,53}, {55,68,55,55}, {56,56,69,56}, {58,58,58,64}, {66,66,66,66},
        {57,57,69,57}, {59,68,59,59}, {60,60,66,60}, {65,61,61,61}, {61,61,61,61},
    },
};

static const uint8_t kChallengeAllyGroupCode[3][15][4] = {
    {
        {50,50,50,50}, {50,50,50,50}, {50,50,50,50}, {50,50,50,50}, {50,50,50,50},
    },
    {
        {51,51,51,51}, {51,51,51,51}, {51,51,51,51}, {51,51,51,51}, {51,51,51,51},
        {52,52,52,52}, {52,52,52,52}, {52,52,52,52}, {52,52,52,52}, {52,52,52,52},
    },
    {
        {52,52,52,52}, {52,53,52,53}, {53,53,53,53}, {53,54,53,54}, {54,54,54,54},
        {54,55,54,55}, {55,55,55,55}, {55,56,55,56}, {56,56,56,56}, {56,57,56,57},
        {57,57,57,57}, {57,58,57,58}, {58,58,58,58}, {58,60,58,60}, {60,61,60,58},
    },
};

extern uint8_t Challenge_RandomByte(void);
extern uint16_t Challenge_RandomBorgFromGroup_80196eb8(uint8_t group_code);
extern uint16_t BorgCost_Lookup_80066168(uint16_t borg_id, uint8_t variant);
extern uint8_t StageVariantCount_Lookup_800825bc(uint8_t stage_id);

void Challenge_SelectStage_80196dac(ChallengeBattleState *state)
{
    uint8_t stage_id = state->stage_id;

    for (;;) {
        uint8_t index = Challenge_RandomByte() % 11;
        uint8_t next_stage = kChallengeStageIds[index];
        if (next_stage != state->stage_id) {
            stage_id = next_stage;
            break;
        }
    }

    state->stage_id = stage_id;
    state->stage_subtable = Challenge_RandomByte() % 3;

    uint8_t variant_count = StageVariantCount_Lookup_800825bc(stage_id);
    if (variant_count == 0) {
        variant_count = 1;
    }
    state->stage_variant = Challenge_RandomByte() % variant_count;
}

static void Challenge_BuildCpuRoster(
    ChallengeRoster *roster,
    enum ChallengeMode mode,
    uint8_t battle_index,
    enum ChallengeSide side)
{
    const uint8_t (*group_table)[15][4] =
        side == CHALLENGE_SIDE_ENEMY ? kChallengeEnemyGroupCode : kChallengeAllyGroupCode;
    const uint16_t (*budget_table)[15] =
        side == CHALLENGE_SIDE_ENEMY ? kChallengeEnemyBudget : kChallengeAllyBudget;
    const uint8_t (*max_table)[15] =
        side == CHALLENGE_SIDE_ENEMY ? kChallengeEnemyMaxMembers : kChallengeAllyMaxMembers;

    uint16_t spent = 0;
    roster->count = 0;

    for (uint8_t i = 0; i < max_table[mode][battle_index]; i++) {
        uint8_t group_code = group_table[mode][battle_index][Challenge_RandomByte() & 3];
        uint16_t borg_id = Challenge_RandomBorgFromGroup_80196eb8(group_code);
        uint16_t cost = BorgCost_Lookup_80066168(borg_id, 0);
        uint16_t charged_cost = (uint16_t)((cost * 2) / 3);

        if ((uint16_t)(spent + charged_cost) > budget_table[mode][battle_index]) {
            break;
        }

        roster->borg_id[roster->count] = borg_id;
        roster->variant[roster->count] = 0;
        roster->count++;
        spent = (uint16_t)(spent + charged_cost);
    }
}

void Challenge_SetupBattle_801962c4(
    ChallengeBattleState *state,
    enum ChallengeMode mode,
    uint8_t battle_index,
    uint8_t selected_slot_mask)
{
    uint8_t active_count = 0;
    uint8_t enemy_auto_count = 0;

    for (uint8_t slot = 0; slot < 6; slot++) {
        bool selected_by_player = (selected_slot_mask & (1u << slot)) != 0;
        state->slot_team[slot] = selected_by_player ? CHALLENGE_SIDE_PLAYER : 0xff;
        if (selected_by_player) {
            active_count++;
        }
    }

    for (uint8_t slot = 0; slot < 6; slot++) {
        if (state->slot_team[slot] != 0xff) {
            continue;
        }

        if (active_count < 2) {
            state->slot_team[slot] = CHALLENGE_SIDE_PLAYER;
            active_count++;
        } else if (enemy_auto_count < 2) {
            state->slot_team[slot] = CHALLENGE_SIDE_ENEMY;
            enemy_auto_count++;
            active_count++;
        } else {
            continue;
        }

        Challenge_BuildCpuRoster(&state->roster[slot], mode, battle_index, state->slot_team[slot]);
        state->active_borg_id[slot] = state->roster[slot].borg_id[0];
        state->active_variant[slot] = state->roster[slot].variant[0];
        state->slot_status[slot] = 0x0e;
        state->slot_state[slot] = 3;
    }

    state->time_limit = 18000; /* 5 minutes at 60 Hz. */
}
