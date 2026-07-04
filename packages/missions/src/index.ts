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

// --- Scoring / results ---
export {
  computeResults,
  accumulateScore,
  DEFAULT_SCORE_WEIGHTS,
} from "./scoring.js";
export type {
  BattleOutcome,
  BattleResults,
  ScoreWeights,
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
  challengeModeForPlayerBudget,
  challengeBattleCount,
  challengeBudgetFor,
  challengeMaxMembersFor,
  challengeGroupChoicesFor,
  challengeStageId,
  challengeStageVariantCount,
  selectChallengeStage,
} from "./challenge-reference.js";
export type {
  ChallengeMode,
  ChallengeSide,
  ChallengeGroupCode,
  ChallengeStageSelection,
} from "./challenge-reference.js";

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
