// @gf/missions — scoring.ts
//
// The results model that mirrors the real GG4E Challenge results screen
// (reference/captures/BRANCHES.md, challenge-10-LOSE-results / challenge-11-WIN-results):
//
//   WIN / LOSE
//   ATTACK
//   HIT RATIO
//   DODGE RATIO
//   ENEMY  BORGS DEFEATED
//   PLAYER BORGS DEFEATED   (0 = your borg survived)
//   ALLY   BORGS DEFEATED
//   TOTAL COST              (cost won  −  cost lost)
//   GRAND TOTAL             (positive on WIN, negative on LOSE)
//
// `computeResults` turns a raw battle outcome (the per-battle telemetry the
// @gf/combat simulation produces) into that screen's numbers. The exact GG4E
// score weights are not documented in our captures, so the weighting below is
// an explicit, tunable model — flagged where it is an assumption.

/**
 * Raw, simulation-side telemetry for a single battle. `@gf/combat` is expected
 * to emit something shaped like this when a battle ends. Counts are whole borgs.
 */
export interface BattleOutcome {
  /** Did the player's force win (enemy force energy reduced to 0)? */
  win: boolean;
  /** Total damage the player's force dealt. */
  attack: number;
  /** Shots/attacks that connected. */
  hits: number;
  /** Shots/attacks attempted (for HIT RATIO = hits / attempts). */
  attempts: number;
  /** Enemy attacks the player successfully evaded. */
  dodges: number;
  /** Enemy attacks aimed at the player (for DODGE RATIO = dodges / incoming). */
  incoming: number;
  /** Enemy borgs the player + allies defeated. */
  enemyBorgsDefeated: number;
  /** The player's own borgs that were defeated (0 = flawless survival). */
  playerBorgsDefeated: number;
  /** Allied (CPU or co-op) borgs defeated. */
  allyBorgsDefeated: number;
  /** Total energy/cost of enemy borgs defeated (cost "won"). */
  costWon: number;
  /** Total energy/cost of player borgs lost (cost "lost"). */
  costLost: number;
}

/** The computed results screen. Ratios are 0..1; render as percentages. */
export interface BattleResults {
  outcome: "WIN" | "LOSE";
  attack: number;
  hitRatio: number;
  dodgeRatio: number;
  enemyBorgsDefeated: number;
  playerBorgsDefeated: number;
  allyBorgsDefeated: number;
  /** costWon − costLost. */
  totalCost: number;
  /** Final score: positive on WIN, negative on LOSE. */
  grandTotal: number;
}

/**
 * Score weights. These are a deliberate, documented model — GG4E's exact
 * formula is not in our captures. Tune freely; the shape (WIN adds, LOSE
 * subtracts; ratios and survival reward) matches the observed screens.
 */
export interface ScoreWeights {
  /** Multiplier on raw ATTACK damage. */
  attack: number;
  /** Flat bonus per enemy borg defeated. */
  perEnemyDefeated: number;
  /** Penalty per player borg lost (always subtracts). */
  perPlayerLost: number;
  /** TOTAL COST is added directly to the grand total. */
  costWeight: number;
  /** Bonus scaled by HIT RATIO (0..1). */
  hitRatioBonus: number;
  /** Bonus scaled by DODGE RATIO (0..1). */
  dodgeRatioBonus: number;
  /** Flat penalty applied on a LOSE before sign flip (keeps LOSE negative). */
  loseFloor: number;
}

export const DEFAULT_SCORE_WEIGHTS: ScoreWeights = {
  attack: 1,
  perEnemyDefeated: 500,
  perPlayerLost: 300,
  costWeight: 1,
  hitRatioBonus: 1000,
  dodgeRatioBonus: 1000,
  loseFloor: 300,
};

function ratio(numerator: number, denominator: number): number {
  if (denominator <= 0) return 0;
  const r = numerator / denominator;
  if (r < 0) return 0;
  if (r > 1) return 1;
  return r;
}

/**
 * Compute the results screen from a battle outcome.
 *
 * GRAND TOTAL convention (matches BRANCHES.md):
 *  - WIN  → positive total (attack + ratios + defeats + cost − losses).
 *  - LOSE → negative total (we floor it negative so the screen shows e.g. −300).
 */
export function computeResults(
  outcome: BattleOutcome,
  weights: ScoreWeights = DEFAULT_SCORE_WEIGHTS,
): BattleResults {
  const hitRatio = ratio(outcome.hits, outcome.attempts);
  const dodgeRatio = ratio(outcome.dodges, outcome.incoming);
  const totalCost = outcome.costWon - outcome.costLost;

  const positive =
    outcome.attack * weights.attack +
    outcome.enemyBorgsDefeated * weights.perEnemyDefeated +
    totalCost * weights.costWeight +
    hitRatio * weights.hitRatioBonus +
    dodgeRatio * weights.dodgeRatioBonus;

  const losses = outcome.playerBorgsDefeated * weights.perPlayerLost;

  let grandTotal: number;
  if (outcome.win) {
    grandTotal = Math.round(positive - losses);
  } else {
    // On a loss the screen shows a negative grand total. Guarantee negativity.
    const raw = positive - losses - weights.loseFloor;
    grandTotal = -Math.abs(Math.round(raw) || weights.loseFloor);
  }

  return {
    outcome: outcome.win ? "WIN" : "LOSE",
    attack: outcome.attack,
    hitRatio,
    dodgeRatio,
    enemyBorgsDefeated: outcome.enemyBorgsDefeated,
    playerBorgsDefeated: outcome.playerBorgsDefeated,
    allyBorgsDefeated: outcome.allyBorgsDefeated,
    totalCost,
    grandTotal,
  };
}

/**
 * Accumulate a per-battle grand total into a running run total. Challenge mode
 * shows a cumulative score across the run of consecutive battles.
 */
export function accumulateScore(runningTotal: number, results: BattleResults): number {
  return runningTotal + results.grandTotal;
}
