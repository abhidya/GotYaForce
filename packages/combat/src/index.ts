// @gf/combat — deterministic gameplay simulation core for the Gotcha Force browser
// recreation. Pure TypeScript: NO DOM, NO three.js, NO network. Single source of truth for
// movement, combat, and battle state; shared by single-player and the netcode server.
//
// Decomp grounding (see research/decomp/*.md):
//   - position vec3 @ struct+0x44 (flat ground plane, Y const ~10 grounded)
//   - heading/yaw s16 @ struct+0x72 (rotY here, radians)
//   - main state enum @ struct+0x544 (idle/move/attack/damage/down/death -> our BorgState)
//   - invincibility f32 @ struct+0x720 (60-frame wake-up i-frames, counts down 1/frame)
// HP and the damage formula could NOT be recovered from the ROM (behavior-notes.md s4f);
// those are DERIVED from the stat table with a tuned formula — flagged in stats.ts/constants.ts.

import { createBattle as createBattleWithStats } from "./battle.js";
import type { BorgStats } from "./stats.js";
import type { Battle, BattleConfig } from "./types.js";

// --- Re-exports (the public API surface) ------------------------------------------------
export {
  stageCollisionFromHitGrids,
  floorSurfaceYAt,
  isFiniteVec,
  yAtTriangleXZ,
  type Vec3,
} from "@gf/physics";
export * from "./types.js";
export {
  AttackCommandType,
  AttackCommandSubtype,
  COMMAND_FAMILY,
  COMMAND_INPUT_BITS,
  resolveCommandType,
  inputRequestsBurst,
  type AttackCommand,
} from "./command.js";
export { targetWithinMeleeEngage } from "./combat.js";
export {
  commandMoveRecordsForBorgButton,
  commandMoveRecordSummaryForBorgButton,
  commandMoveTableAssignmentForBorgId,
  commandMoveTableCoverage,
  hasExactCommandMoveTableForBorgId,
  type CommandMoveRecord,
  type CommandMoveTableAssignment,
  type CommandMoveTableCoverage,
  type RuntimeCommandMoveButton,
} from "./commandMoveTables.js";
export {
  commandButtonForType,
  commandInputWord,
  contextualBGatesForBorgId,
  resolveLiveCommand,
  selectCommandRecord,
  type CommandActorContext,
  type CommandButtonState,
  type ContextualBGates,
} from "./commandDispatch.js";
export { movementContextOf, type MovementContext } from "./movement.js";
export {
  cameraParamsForBorgId,
  defaultCameraSlotForBorgId,
  fallGravityForBorgId,
  jumpVelocityForBorgId,
  movementPhysicsForBorgId,
  statusImmunityMasksForBorgId,
  type BorgCameraParams,
  type BorgMovementPhysics,
} from "./movementData.js";
export {
  attackHitActiveWindowForKind,
  attackHitMaxReachForKind,
  attackHitRecordsForKind,
  attackHitTableForBorgId,
  shotHitRadiusForBorgId,
  type AttackHitRecord,
  type BorgAttackHitTable,
} from "./attackHitData.js";
export { groundRunSpeedForBorgId } from "./movementData.js";
export { familyDamageRecordCountForBorg, familyDamageRecordForBorg } from "./familyDamageData.js";
export { exactMeleeForBorgId, type ExactMeleeAttack } from "./meleeExactData.js";
export {
  comboLadderForBorgId,
  comboLadderStepCountForBorgId,
  type AuthoredSoundEvent,
  type ComboStep,
} from "./actionStreamData.js";
export {
  actorVelocityScale,
  isFrozen,
  statusTimescale,
  tierSizeScale,
  tierVelocityScale,
  PARAM_TIER_DEFAULT,
  type StatusSpeedLevels,
} from "./timescale.js";
export {
  buildProfile,
  forceEnergy,
  parseHp,
  parseJump,
  validateForceBudget,
  type BorgProfile,
  type BorgStats,
  type ForceBudgetResult,
  type RangePref,
} from "./stats.js";
export {
  BURST,
  CHARGE,
  COMBO,
  DASH,
  DAMAGE,
  DEFAULT_BOUNDS,
  DEPLOY,
  HERO_X_BUFF,
  HIT_STATUS,
  JUMP,
  MELEE,
  MOVE,
  MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES,
  SHOT,
  SIM,
  SPECIAL,
  STAGGER,
  STATE,
  WAKE_UP_INVINCIBILITY_FRAMES,
} from "./constants.js";
export {
  DAMAGE_RECORDS,
  DAMAGE_RECORD_INDEX,
  KNOCKBACK_STRENGTH_TABLE,
  REACTION_FORCE_STAGGER_MASK,
  damageRecordByIndex,
  knockbackStrengthClamp,
  gaugeInitForBorgId,
  type BorgGaugeInit,
  type DamageRecord,
} from "./gauges.js";
export {
  actorDataCombatStatsForBorgId,
  actorDataCombatStatsSummary,
  type ActorDataCombatStats,
} from "./actorDataStats.js";
export {
  LEVEL_ROW_OFFSETS_804339E8,
  borgSourceStatsSummary,
  sourceStatsForBorgId,
  type BorgSourceStats,
  type BorgSourceWeaponSlot,
} from "./sourceBorgStats.js";
export {
  challengeSideRanksForMode,
  damageFormulaSummary,
  type ChallengeDamageMode,
} from "./damageFormula.js";
export {
  actionProfileForProfile,
  startingAmmoForProfile,
  type BorgActionProfile,
  type MeleeActionDef,
  type PrimaryAttackKind,
  type ShotActionDef,
  type SpecialActionDef,
  type SwordBeamDef,
} from "./actionProfiles.js";
export {
  PARAM_TIER_RESET,
  PARAM_TIER_TIMER_FRAMES,
  applyActorParamTierDelta127,
  applyActorParamTierDelta63,
  resetActorParamTier,
} from "./paramTier.js";
export { stepAI } from "./ai.js";
export {
  moveProfileForBorgId,
  moveByButton,
  shotPenetrationForBorgId,
  moveDataCoverage,
  moveCrossValidation,
  type BorgMove,
  type BorgMoveProfile,
  type MoveAmmo,
  type MoveRefill,
  type MoveSolidity,
  type Penetration,
} from "./moveProperties.js";
export {
  runtimeMoveBindingForBorgId,
  runtimeMoveBindingsForProfile,
  runtimeMoveCoverage,
  runtimeShotPenetrationForBorgId,
  usesContextualBResolver,
  type RuntimeMoveAction,
  type RuntimeMoveAmmo,
  type RuntimeMoveBinding,
  type RuntimeMoveButton,
  type RuntimeMoveCommandStatus,
  type RuntimeMoveHitboxStatus,
} from "./moveRuntime.js";

// --- Borg-stats registry ----------------------------------------------------------------
// The brief's createBattle signature is `createBattle(cfg): Battle`, but the sim needs the
// per-borg stat table. We support both: register the table once via setBorgStats(...), or
// pass it explicitly as the second argument (which takes precedence).

let registeredStats: readonly BorgStats[] = [];

/** Register the global borg stat table (from packages/assets/data/borgs.json). */
export function setBorgStats(borgs: readonly BorgStats[]): void {
  registeredStats = borgs;
}

/**
 * Create a deterministic battle. Uses the explicitly-passed stat table if given, else the
 * table registered via setBorgStats(). Throws if no stats are available.
 */
export function createBattle(cfg: BattleConfig, borgStats?: readonly BorgStats[]): Battle {
  const stats = borgStats ?? registeredStats;
  if (stats.length === 0) {
    throw new Error(
      "createBattle: no borg stats available. Call setBorgStats(borgs) or pass borgStats as the 2nd argument.",
    );
  }
  return createBattleWithStats(cfg, stats);
}
