// @gf/missions — scoring.ts
//
// The results model matching the real GG4E Challenge results screen
// (reference captures challenge-10-LOSE-results / challenge-11-WIN-results):
//
//   WIN / LOSE
//   ATTACK                  (number of attacks initiated — ROM actor +0x404)
//   HIT RATIO               (hits / attacks — +0x408 / +0x404)
//   DODGE RATIO             ((incomingAimed − hitsTakenAimed) / (incomingAimed + hitsTakenOther))
//   ENEMY  BORGS DEFEATED   (+0x434) with TOTAL COST (+0x420) → tier score
//   PLAYER BORGS DEFEATED   (+0x435) with TOTAL COST (+0x424) → tier score
//   ALLY   BORGS DEFEATED   (+0x437, display only — never scored)
//   GRAND TOTAL             tier(costWon) + tier(costLost) + first-strike bonus
//
// DERIVED (2026-07-04, research/decomp/results-scoring-decode-2026-07-04.md): the whole
// formula below is the decoded ROM model — results row builder FUN_800d3260 @0x800d3260
// (chunk_0022.c), per-player stat gatherer zz_00d1d24_ @0x800d1d24, tier lookup
// zz_00d1cbc_ @0x800d1cbc, tier tables DAT_8030e4b8 / DAT_8030e6a8 and the first-strike
// bonus DAT_80433b58 = 5000 extracted from boot.dol. This replaces the old TUNED
// weight model (ScoreWeights) entirely — no part of the grand total is a guess anymore.
//
// Key ROM facts the old model got wrong:
//  - "ATTACK" is the COUNT of attacks initiated, not damage dealt.
//  - GRAND TOTAL has NO win/lose sign handling: it is negative only when the cost-lost
//    tier drags it negative. (Validated: WIN capture 6000 + 1000 + 0 = 7000.)
//  - The per-kill +100 (zz_002f8dc_ team score DAT_80436154) does NOT feed this screen —
//    it is the separate in-battle score counter.

/**
 * Raw, per-battle telemetry for the LOCAL PLAYER'S SLOT (the ROM keeps these counters on
 * the persistent per-player actor struct at +0x404..+0x437; they accumulate across borg
 * swaps within one battle). Emitted by @gf/combat SlotTelemetry via
 * battleOutcomeFromState.
 */
export interface BattleOutcome {
  /** Did the player's force win (winner mask == our side bit)? Display only — the ROM
   *  grand total does not use it. */
  win: boolean;
  /** ROM +0x404 — attacks initiated. This IS the screen's "ATTACK" number and the HIT
   *  RATIO denominator. */
  attempts: number;
  /** ROM +0x408 — cross-team hit connections (once per attack event per victim). */
  hits: number;
  /** ROM +0x40c — enemy attacks aimed at the player's borg at activation. */
  incomingAimed: number;
  /** ROM +0x410 — hits taken from attacks that were aimed at us (≤ incomingAimed). */
  hitsTakenAimed: number;
  /** ROM +0x414 — stray/unaimed/untracked/friendly hits taken (dodge denominator add). */
  hitsTakenOther: number;
  /** ROM +0x434 — enemy borgs the PLAYER finished off (ally kills don't count). */
  enemyBorgsDefeated: number;
  /** ROM +0x435 — the player's own borgs defeated (0 = flawless survival). */
  playerBorgsDefeated: number;
  /** ROM +0x437 — allied (CPU) borgs defeated. Display row only, never scored. */
  allyBorgsDefeated: number;
  /** ROM +0x420 — summed cost of enemy borgs the player defeated. */
  costWon: number;
  /** ROM +0x424 — summed cost of the player's own borgs lost (ally cost EXCLUDED). */
  costLost: number;
  /** ROM +0x436 — this player landed the battle's first cross-team hit (worth 5000). */
  firstStrike: boolean;
}

/** The computed results screen. Ratios are 0..1 fractions; render as percentages. */
export interface BattleResults {
  outcome: "WIN" | "LOSE";
  /** "ATTACK" row — the attack count (ROM +0x404), NOT damage. */
  attack: number;
  /** hits / attempts (0 when either is 0 — ROM FUN_800d3260 case 1). Unclamped like the
   *  ROM: one AoE attack connecting with several victims can push it past 1. */
  hitRatio: number;
  /** (incomingAimed − hitsTakenAimed) / (incomingAimed + hitsTakenOther), 0 when nothing
   *  was ever aimed at us (ROM FUN_800d3260 case 2). */
  dodgeRatio: number;
  enemyBorgsDefeated: number;
  playerBorgsDefeated: number;
  allyBorgsDefeated: number;
  /** Raw "TOTAL COST" under ENEMY BORGS DEFEATED (= costWon). */
  costWon: number;
  /** Raw "TOTAL COST" under PLAYER BORGS DEFEATED (= costLost). */
  costLost: number;
  /** Right-column tier score for costWon (DAT_8030e4b8). */
  costWonScore: number;
  /** Right-column tier score for costLost (DAT_8030e6a8; +1000 when costLost == 0). */
  costLostScore: number;
  /** First-strike bonus row: 5000 (DAT_80433b58) or 0. */
  firstStrikeBonus: number;
  /** GRAND TOTAL = costWonScore + costLostScore + firstStrikeBonus. Negative is possible
   *  (heavy losses, no kills) and the ROM renders the minus sign — no win/lose flip. */
  grandTotal: number;
}

/**
 * DERIVED — tier lookup zz_00d1cbc_ @0x800d1cbc: walk (threshold, value) pairs while
 * threshold <= x (terminator threshold −1), return the last passed value. x below the
 * first threshold returns 0 (the accumulator's initial value).
 */
export function tierScore(table: ReadonlyArray<readonly [number, number]>, x: number): number {
  let out = 0;
  for (const [threshold, value] of table) {
    if (threshold > x) break;
    out = value;
  }
  return out;
}

/**
 * DERIVED — DAT_8030e4b8 (boot.dol): enemy-cost-defeated → score. 0 → 0; 1..100 → 100;
 * then +1000 per full 100 cost, capped at 60000 for cost ≥ 5901.
 * NOTE the 4901..5000 → 40000 entry is IN THE ROM DATA (it breaks the +1000 ladder that
 * would predict 50000) — reproduced verbatim, do not "fix" it.
 */
export const COST_WON_SCORE_TABLE: ReadonlyArray<readonly [number, number]> = [
  [0, 0], [1, 100], [101, 2000], [201, 3000], [301, 4000], [401, 5000], [501, 6000],
  [601, 7000], [701, 8000], [801, 9000], [901, 10000], [1001, 11000], [1101, 12000],
  [1201, 13000], [1301, 14000], [1401, 15000], [1501, 16000], [1601, 17000], [1701, 18000],
  [1801, 19000], [1901, 20000], [2001, 21000], [2101, 22000], [2201, 23000], [2301, 24000],
  [2401, 25000], [2501, 26000], [2601, 27000], [2701, 28000], [2801, 29000], [2901, 30000],
  [3001, 31000], [3101, 32000], [3201, 33000], [3301, 34000], [3401, 35000], [3501, 36000],
  [3601, 37000], [3701, 38000], [3801, 39000], [3901, 40000], [4001, 41000], [4101, 42000],
  [4201, 43000], [4301, 44000], [4401, 45000], [4501, 46000], [4601, 47000], [4701, 48000],
  [4801, 49000], [4901, 40000], [5001, 51000], [5101, 52000], [5201, 53000], [5301, 54000],
  [5401, 55000], [5501, 56000], [5601, 57000], [5701, 58000], [5801, 59000], [5901, 60000],
];

/**
 * DERIVED — DAT_8030e6a8 (boot.dol): own-cost-lost → score. A flawless 0 loss is a +1000
 * BONUS; any loss goes negative, down to −5000 for ≥ 3001 cost lost.
 */
export const COST_LOST_SCORE_TABLE: ReadonlyArray<readonly [number, number]> = [
  [0, 1000], [1, -100], [201, -300], [401, -500], [601, -700], [801, -1000],
  [1001, -1200], [1201, -1500], [1401, -2000], [1601, -2500], [2001, -3000], [3001, -5000],
];

/** DERIVED — DAT_80433b58 (boot.dol): landing the battle's first hit is worth 5000. */
export const FIRST_STRIKE_BONUS = 5000;

/**
 * Compute the results screen from a battle outcome — the decoded ROM formula
 * (FUN_800d3260 rows + zz_00d1d24_ grand total). See the header for provenance.
 */
export function computeResults(outcome: BattleOutcome): BattleResults {
  // Row 1 (FUN_800d3260 case 1): 0 unless BOTH counters are non-zero.
  const hitRatio =
    outcome.hits !== 0 && outcome.attempts !== 0 ? outcome.hits / outcome.attempts : 0;

  // Row 2 (case 2): numerator = aimed attacks that never connected; denominator adds the
  // stray hits taken. hitsTakenAimed is clamped ≤ incomingAimed at increment (resolver
  // chunk_0003.c:7888-7891), so the numerator is never negative with ROM-shaped inputs.
  const dodgeRatio =
    outcome.incomingAimed !== 0
      ? Math.max(0, outcome.incomingAimed - outcome.hitsTakenAimed) /
        (outcome.incomingAimed + outcome.hitsTakenOther)
      : 0;

  const costWonScore = tierScore(COST_WON_SCORE_TABLE, Math.round(outcome.costWon));
  const costLostScore = tierScore(COST_LOST_SCORE_TABLE, Math.round(outcome.costLost));
  const firstStrikeBonus = outcome.firstStrike ? FIRST_STRIKE_BONUS : 0;

  return {
    outcome: outcome.win ? "WIN" : "LOSE",
    attack: outcome.attempts,
    hitRatio,
    dodgeRatio,
    enemyBorgsDefeated: outcome.enemyBorgsDefeated,
    playerBorgsDefeated: outcome.playerBorgsDefeated,
    allyBorgsDefeated: outcome.allyBorgsDefeated,
    costWon: Math.round(outcome.costWon),
    costLost: Math.round(outcome.costLost),
    costWonScore,
    costLostScore,
    firstStrikeBonus,
    // zz_00d1d24_: struct[0x23] = [0x18] + [0x1a] + [0x1d] — nothing else contributes.
    grandTotal: costWonScore + costLostScore + firstStrikeBonus,
  };
}

/**
 * Accumulate a per-battle grand total into the running Challenge run total — the ROM adds
 * struct[0x23] into the per-player accumulator at match-state +0x17e0 (zz_00d1d24_
 * chunk_0022.c:1088-1089); the Challenge clear/fail screen renders it signed
 * (chunk_0061.c:2845-2858), so a run total CAN be negative.
 */
export function accumulateScore(runningTotal: number, results: BattleResults): number {
  return runningTotal + results.grandTotal;
}
