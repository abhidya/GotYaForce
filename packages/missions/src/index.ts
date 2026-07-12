// @gf/missions — barrel exports for the CHALLENGE + ADVENTURE run/progression
// layer.
//
// Modules:
//   battle-config.ts — mission-owned battle plan shape.
//   borg-data.ts     — Borg roster types + `enemyForceForBudget` assembler.
//   scoring.ts       — results model (computeResults) matching the real screen.
//   challenge.ts     — createChallengeRun(): escalating run of BattleConfigs.
//   adventure.ts     — createAdventureCampaign(): stages.json → BattleConfigs.

// --- Mission battle plan surface ---
export type {
  MissionTeam,
  MissionBattleForce,
  MissionBattleConfig,
  MissionBattleMeta,
  Team,
  BattleForce,
  BattleConfig,
  BattleMeta,
} from "./battle-config.js";
export {
  playerIdFor,
  stageIdForArena,
  stageIdForBattleConfig,
  toCombatBattleConfig,
} from "./combat-config.js";
export type {
  CombatBattleConfigOptions,
  CombatStageCatalog,
} from "./combat-config.js";

// --- Borg roster + enemy-force assembler ---
export {
  readBorgs,
  enemyForceForBudget,
  deathBorgPool,
} from "./borg-data.js";
export type {
  Borg,
  BorgData,
  EnemyForce,
  EnemyForceOptions,
} from "./borg-data.js";

// --- Scoring / results (DERIVED ROM formula — see scoring.ts header) ---
export {
  computeResults,
  accumulateScore,
  tierScore,
  COST_WON_SCORE_TABLE,
  COST_LOST_SCORE_TABLE,
  FIRST_STRIKE_BONUS,
} from "./scoring.js";
export type {
  BattleOutcome,
  BattleResults,
} from "./scoring.js";

// --- Challenge mode ---
export {
  createChallengeRun,
  createChallengeRng,
  enemyTargetForBattle,
  CHALLENGE_DIFFICULTIES,
  DEFAULT_ESCALATION,
} from "./challenge.js";
export type {
  ChallengeDifficulty,
  ChallengeRun,
  ChallengeRunOptions,
  ChallengeProgress,
  PlayerForce,
  EscalationCurve,
} from "./challenge.js";
export {
  CHALLENGE_BATTLE_COUNTS,
  CHALLENGE_TIME_LIMIT_FRAMES,
  CHALLENGE_STAGE_BYTES,
  CHALLENGE_ALLY_BUDGETS,
  CHALLENGE_ENEMY_BUDGETS,
  CHALLENGE_ALLY_MAX_MEMBERS,
  CHALLENGE_ENEMY_MAX_MEMBERS,
  CHALLENGE_ALLY_GROUP_CODES,
  CHALLENGE_ENEMY_GROUP_CODES,
  CHALLENGE_GROUP_ROSTERS,
  CHALLENGE_STAGE_VARIANT_COUNTS,
  STAGE_ARENA_NAMES,
  challengeModeForPlayerBudget,
  challengeBattleCount,
  challengeBudgetFor,
  challengeMaxMembersFor,
  challengeGroupChoicesFor,
  challengeStageId,
  challengeStageVariantCount,
  selectChallengeStage,
  arenaNameForStageByte,
  arenaNameForStageId,
} from "./challenge-reference.js";
export type {
  ChallengeMode,
  ChallengeSide,
  ChallengeGroupCode,
  ChallengeStageSelection,
} from "./challenge-reference.js";

// --- Borg GET / Gotcha-Box drop pipeline (DERIVED — see getSystem.ts header) ---
export {
  BORG_GET_DROP_TABLE,
  GET_COLOR_VARIANT_NAMES,
  GET_KILL_CREDITS,
  GET_POOL_CAP,
  GET_POINTS_CAP,
  GET_POINTS_PER_KILL_MIN,
  GET_POINTS_PER_KILL_MAX,
  createGetPool,
  clonePool,
  snapshotPool,
  restorePool,
  registerKill,
  rollDrops,
  rollPointsGain,
  rollPartIndex,
  getDropRowForBorgId,
} from "./getSystem.js";

// --- Transactional Gotcha-Box settlement ---
export {
  GOTCHA_BOX_STATE_VERSION,
  createGotchaBoxState,
  createMemoryGotchaBoxPersistence,
  createGotchaBoxSettlement,
} from "./gotchaBoxSettlement.js";
export type {
  CollectedGetDrop,
  GotchaBoxState,
  GotchaBoxPersistence,
  GotchaBoxSettlement,
  GotchaBoxSettlementOptions,
} from "./gotchaBoxSettlement.js";
export type {
  GetColorVariant,
  GetDropTableRow,
  GetDropTableMeta,
  GetDropTable,
  GetPoolEntry,
  GetPool,
  GetDropKind,
  GetDrop,
} from "./getSystem.js";

// --- Adventure mode ---
export {
  createAdventureCampaign,
  readStages,
  parseCounts,
  buildNameIndex,
  matchBorg,
  normalizeName,
  resolveAdventureStage,
  resolveAdventureStageEntry,
  resolveAdventureEnemy,
  buildAdventureBorgIndex,
  findAdventureBorg,
  normalizeAdventureName,
} from "./adventure.js";
export type {
  AdventureCampaign,
  AdventureStage as AdventureCampaignStage,
  AdventureStageEntry,
  AdventureOptions,
  ResolvedEnemy,
  StagesData,
  NameIndex,
  LegacyAdventureStageId as AdventureStageId,
  LegacyAdventureStage as AdventureStage,
  LegacyAdventureStagesData as AdventureStagesData,
  LegacyAdventureBorg as AdventureBorg,
  LegacyAdventureBorgData as AdventureBorgData,
  LegacyResolvedAdventureEnemy as ResolvedAdventureEnemy,
  LegacyResolvedAdventureStage as ResolvedAdventureStage,
  LegacyAdventureBorgIndex as AdventureBorgIndex,
} from "./adventure.js";
