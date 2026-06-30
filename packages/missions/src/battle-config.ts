// @gf/missions — battle-config.ts
//
// Local mirror of the @gf/combat simulation API surface this package produces.
//
// NOTE: as of writing, `@gf/combat` (packages/combat/src/index.ts) exports
// BorgStats / forceEnergy / validateForceBudget but does NOT yet export
// `BattleConfig` or `createBattle`. The task specifies the eventual core API as
// `createBattle(BattleConfig)` with `BattleConfig.forces[] = {team, ownerPlayer,
// borgIds[]}`. We define a matching interface here so the missions layer is
// self-contained and typechecks in isolation. When @gf/combat starts exporting
// `BattleConfig`, replace this file with a re-export:
//
//     export type { BattleConfig, BattleForce, Team } from "@gf/combat";

/** Which side a force fights on. */
export type Team = "player" | "enemy";

/**
 * One force in a battle. A battle has at least one player force and one enemy
 * force; "fight alone" adds a CPU ally force on the player side.
 */
export interface BattleForce {
  /** Side this force fights for. */
  team: Team;
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
export interface BattleConfig {
  /** Arena / stage id this battle is fought in. */
  arena: string;
  /** All forces in the battle (player force(s), optional CPU ally, enemy force). */
  forces: BattleForce[];
  /** Optional human-readable label (e.g. "BATTLE 2 VS" or the stage name). */
  label?: string;
  /** Optional metadata for UI/debugging; never read by the simulation. */
  meta?: BattleMeta;
}

/** Non-simulation metadata attached to a generated battle. */
export interface BattleMeta {
  /** Which mode produced this battle. */
  mode: "challenge" | "adventure";
  /** 0-based index within the run/campaign. */
  index: number;
  /** Target enemy energy this battle was built toward (challenge escalation). */
  enemyTargetEnergy?: number;
  /** Actual summed enemy force energy. */
  enemyForceEnergy?: number;
  /** Boss label, if this is a boss stage (adventure). */
  boss?: string | null;
  /** Source-data confidence (adventure stages). */
  confidence?: string | null;
  /** Enemy names that failed to resolve to a borg id (adventure). */
  unresolvedEnemies?: string[];
}
