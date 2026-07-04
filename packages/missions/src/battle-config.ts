// @gf/missions — battle-config.ts
//
// Mission-owned battle plan shape. It keeps mode-facing facts such as arena
// names, labels, and scoring/debug metadata. `combat-config.ts` is the adapter
// that projects this into @gf/combat's numeric-team BattleConfig.

/** Which side a force fights on. */
export type MissionTeam = "player" | "enemy";

/**
 * One force in a battle. A battle has at least one player force and one enemy
 * force; "fight alone" adds a CPU ally force on the player side.
 */
export interface MissionBattleForce {
  /** Side this force fights for. */
  team: MissionTeam;
  /**
   * Owning player index (0-based) for human-controlled forces, or null for
   * CPU-controlled forces (enemy waves and the "fight alone" CPU ally).
   */
  ownerPlayer: number | null;
  /** Ordered borg roster ids (pl####), each spawns when the previous dies. */
  borgIds: string[];
  /**
   * True when this is the CPU ally granted in "FIGHT ALONE" mode (or any
   * non-human helper on the player side). Informational; the simulation can
   * ignore it.
   */
  cpuAlly?: boolean;
}

/** Configuration handed to `@gf/combat`'s `createBattle()`. */
export interface MissionBattleConfig {
  /** Arena / stage id this battle is fought in. */
  arena: string;
  /** All forces in the battle (player force(s), optional CPU ally, enemy force). */
  forces: MissionBattleForce[];
  /** Original battle timer in frames; omitted means no timer. */
  timeLimitFrames?: number;
  /**
   * Model of the original timer-pause flag PTR_DAT_80433934[0x50]: the countdown
   * and the judge's timeout branches only run while the flag is clear. Challenge
   * writes 18000 frames AND the pause flag (chunk_0048.c:390-392), so its timer
   * displays but never expires.
   */
  timerFrozen?: boolean;
  /** Optional human-readable label (e.g. "BATTLE 2 VS" or the stage name). */
  label?: string;
  /** Optional metadata for UI/debugging; never read by the simulation. */
  meta?: MissionBattleMeta;
}

/** Non-simulation metadata attached to a generated battle. */
export interface MissionBattleMeta {
  /** Which mode produced this battle. */
  mode: "challenge" | "adventure";
  /** 0-based index within the run/campaign. */
  index: number;
  /** Target enemy energy this battle was built toward (challenge escalation). */
  enemyTargetEnergy?: number;
  /** Actual summed enemy force energy. */
  enemyForceEnergy?: number;
  /** Original DOL Challenge mode: 0=NORMAL, 1=TUFF, 2=INSANE. */
  challengeMode?: 0 | 1 | 2;
  /** Original DOL budget charge uses floor(cost * 2 / 3), not raw force energy. */
  enemyBudgetCharge?: number;
  /** Original slot setup creates two enemy CPU slots. */
  enemySlotCount?: number;
  enemySlotForceEnergy?: number[];
  enemySlotBudgetCharge?: number[];
  enemyMaxMembers?: number;
  enemyGroupChoices?: number[];
  enemyPickedGroupCodes?: number[];
  /** CPU ally values are present for FIGHT ALONE when generated from DOL tables. */
  allyTargetEnergy?: number;
  allyForceEnergy?: number;
  allyBudgetCharge?: number;
  allyMaxMembers?: number;
  allyGroupChoices?: number[];
  allyPickedGroupCodes?: number[];
  /** Raw Challenge stage selector bytes from PTR_DAT_80433934[0x1c..0x1e]. */
  stageByte?: number;
  stageSubtable?: number;
  stageVariant?: number;
  /** Raw Challenge setup writes 18000 frames (5 minutes at 60 Hz). */
  timeLimitFrames?: number;
  /** Boss label, if this is a boss stage (adventure). */
  boss?: string | null;
  /** Source-data confidence (adventure stages). */
  confidence?: string | null;
  /** Enemy names that failed to resolve to a borg id (adventure). */
  unresolvedEnemies?: string[];
}

// Back-compat aliases for existing callers. Prefer the Mission* names in new
// mission code; use toCombatBattleConfig() at the @gf/combat interface.
export type Team = MissionTeam;
export type BattleForce = MissionBattleForce;
export type BattleConfig = MissionBattleConfig;
export type BattleMeta = MissionBattleMeta;
