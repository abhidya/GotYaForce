// @gf/missions — challenge.ts
//
// CHALLENGE mode: the run/progression layer.
//
// Real flow (reference/captures/BRANCHES.md):
//   pick difficulty (= energy budget 1500 / 2000 / 2500)
//   → pick players (1P FIGHT ALONE / 2P TEAM UP)
//   → build force(s) (≤30 borgs, summed energy ≤ budget)
//   → a RUN of consecutive battles: win → next (tougher), lose → title.
//   "FIGHT ALONE" still spawns a CPU ally on the player side.
//   WIN/LOSE results carry a GRAND TOTAL; the run tracks a cumulative score.
//
// This module produces an ordered list of `BattleConfig`s (the escalating run)
// and a `next(result)` progression that advances on win and ends on lose.

import type { BattleConfig, BattleForce } from "./battle-config.js";
import { type BorgData, enemyForceForBudget, deathBorgPool, type Borg } from "./borg-data.js";
import {
  type BattleResults,
  accumulateScore,
} from "./scoring.js";

/** The three selectable difficulties map directly to an energy budget. */
export const CHALLENGE_DIFFICULTIES = {
  NORMAL: 1500,
  TUFF: 2000,
  INSANE: 2500,
} as const;

export type ChallengeDifficulty = keyof typeof CHALLENGE_DIFFICULTIES;

/** One player's chosen force (ordered borg ids), validated elsewhere. */
export interface PlayerForce {
  /** 0-based player index. */
  player: number;
  /** Ordered borg ids (pl####); spawns one at a time as each dies. */
  borgIds: string[];
}

export interface ChallengeRunOptions {
  /** Energy budget (use CHALLENGE_DIFFICULTIES or a raw number). */
  budget: number;
  /** Number of human players (1 = FIGHT ALONE, 2+ = TEAM UP). */
  playerCount: number;
  /** Each human player's force. */
  playerForces: PlayerForce[];
  /** Roster data (borgs.json) for assembling enemy waves. */
  borgs: BorgData;
  /** How many battles in the run. Default 10. */
  battleCount?: number;
  /**
   * Borg id used as the CPU ally roster when fighting alone. Defaults to the
   * single player's own force (the CPU mirrors your force, as in GG4E where
   * the assist clears the wave). Provide an explicit ally if desired.
   */
  fightAloneAllyBorgIds?: string[];
  /** Arena id for the run's battles. Default "challenge". */
  arena?: string;
}

/**
 * Enemy-energy escalation across the run. Capture evidence in
 * apps/game/reference/captures/BRANCHES.md pins NORMAL battle 1 near the
 * 1500 GF-energy budget and NORMAL battle 2 at ENEMY 1860.
 *
 *   enemyTarget(i) = round(budget * (startFactor + i * stepFactor))
 */
export interface EscalationCurve {
  /** Fraction of budget the first enemy force targets. Default 1.0. */
  startFactor: number;
  /** Added fraction of budget per battle index. Default 0.24. */
  stepFactor: number;
}

export const DEFAULT_ESCALATION: EscalationCurve = {
  startFactor: 1.0,
  stepFactor: 0.24,
};

export function enemyTargetForBattle(
  budget: number,
  index: number,
  curve: EscalationCurve = DEFAULT_ESCALATION,
): number {
  return Math.round(budget * (curve.startFactor + index * curve.stepFactor));
}

/** A built challenge run: the ordered battles + the run's live progression state. */
export interface ChallengeRun {
  budget: number;
  playerCount: number;
  /** Ordered escalating battles. */
  battles: BattleConfig[];
  /** Total battles in the run. */
  total: number;
  /** Index of the battle currently to be played (0-based). */
  current: number;
  /** Cumulative GRAND TOTAL across resolved battles. */
  score: number;
  /** Whether the run has ended (loss or run completed). */
  ended: boolean;
  /** Get the current battle config, or null if the run has ended. */
  getCurrentBattle(): BattleConfig | null;
  /**
   * Advance the run with a battle result.
   *  - WIN  → score accumulates, advance to the next (tougher) battle. If that
   *           was the final battle, the run ends as completed.
   *  - LOSE → score accumulates (negative), run ends → caller returns to title.
   */
  next(result: BattleResults): ChallengeProgress;
}

export interface ChallengeProgress {
  outcome: "WIN" | "LOSE";
  /** Action the caller should take. */
  action: "advance" | "complete" | "title";
  /** Next battle to play, or null when ending. */
  nextBattle: BattleConfig | null;
  /** Cumulative score after this result. */
  score: number;
  /** 0-based index now current. */
  current: number;
}

/**
 * Build a challenge run: an ordered list of escalating `BattleConfig`s plus the
 * `next()` progression and cumulative scoring.
 */
export function createChallengeRun(options: ChallengeRunOptions): ChallengeRun {
  const {
    budget,
    playerCount,
    playerForces,
    borgs,
    battleCount = 10,
    arena = "challenge",
  } = options;

  const pool = deathBorgPool(borgs);
  // Augment the Death Borg fodder with a few escalating-cost roster borgs so
  // later battles can field meaningful threats, not just 30 cheap fodder.
  const escalatingPool = buildEscalatingEnemyPool(borgs, pool);

  const battles: BattleConfig[] = [];
  for (let i = 0; i < battleCount; i++) {
    const enemyTarget = enemyTargetForBattle(budget, i);
    const enemy = enemyForceForBudget(enemyTarget, borgs, {
      pool: i < 2 ? pool : escalatingPool,
    });

    const playerForceConfigs: BattleForce[] = playerForces.map((pf) => ({
      team: "player" as const,
      ownerPlayer: pf.player,
      borgIds: pf.borgIds,
    }));

    // FIGHT ALONE → add a CPU ally on the player side.
    if (playerCount <= 1) {
      const allyBorgIds =
        options.fightAloneAllyBorgIds ?? playerForces[0]?.borgIds ?? [];
      playerForceConfigs.push({
        team: "player",
        ownerPlayer: null,
        borgIds: allyBorgIds.slice(),
        cpuAlly: true,
      });
    }

    const enemyForce: BattleForce = {
      team: "enemy",
      ownerPlayer: null,
      borgIds: enemy.borgIds,
    };

    battles.push({
      arena,
      label: `BATTLE ${i + 1} VS`,
      forces: [...playerForceConfigs, enemyForce],
      meta: {
        mode: "challenge",
        index: i,
        enemyTargetEnergy: enemyTarget,
        enemyForceEnergy: enemy.energy,
      },
    });
  }

  const run: ChallengeRun = {
    budget,
    playerCount,
    battles,
    total: battles.length,
    current: 0,
    score: 0,
    ended: false,
    getCurrentBattle() {
      if (this.ended) return null;
      return this.battles[this.current] ?? null;
    },
    next(result: BattleResults): ChallengeProgress {
      if (this.ended) {
        return {
          outcome: result.outcome,
          action: "title",
          nextBattle: null,
          score: this.score,
          current: this.current,
        };
      }

      this.score = accumulateScore(this.score, result);

      if (result.outcome === "LOSE") {
        this.ended = true;
        return {
          outcome: "LOSE",
          action: "title",
          nextBattle: null,
          score: this.score,
          current: this.current,
        };
      }

      // WIN → advance.
      const nextIndex = this.current + 1;
      if (nextIndex >= this.total) {
        this.current = this.total;
        this.ended = true;
        return {
          outcome: "WIN",
          action: "complete",
          nextBattle: null,
          score: this.score,
          current: this.current,
        };
      }

      this.current = nextIndex;
      return {
        outcome: "WIN",
        action: "advance",
        nextBattle: this.battles[nextIndex] ?? null,
        score: this.score,
        current: this.current,
      };
    },
  };

  return run;
}

/**
 * A pool for later-battle enemy waves: Death Borg fodder plus a spread of
 * mid/high-cost non-Dragon, non-final roster borgs so escalating battles have
 * teeth. We exclude the ultra-cost (≥1500) units to keep waves composable.
 */
function buildEscalatingEnemyPool(data: BorgData, deathBorgs: readonly Borg[]): Borg[] {
  const all = "borgs" in data ? data.borgs : data;
  const threats = all.filter(
    (b) => b.energy >= 250 && b.energy <= 1000 && b.tribe !== "Death Borg",
  );
  return [...deathBorgs, ...threats];
}
