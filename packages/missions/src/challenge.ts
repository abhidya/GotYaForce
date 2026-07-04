// @gf/missions — challenge.ts
//
// CHALLENGE mode: the run/progression layer.
//
// Player-facing flow (reference/captures/BRANCHES.md):
//   pick difficulty (= energy budget 1500 / 2000 / 2500)
//   → pick players (1P FIGHT ALONE / 2P TEAM UP)
//   → build force(s) (≤30 borgs, summed energy ≤ budget)
//   → a RUN of consecutive battles: win → next (tougher), lose → title.
//   "FIGHT ALONE" still spawns a CPU ally on the player side.
//   WIN/LOSE results carry a GRAND TOTAL; the run tracks a cumulative score.
//
// The CPU ally/enemy rosters and Challenge stage ids below are not heuristic:
// they are built from the deobfuscated 0x801962c4 / 0x80196dac DOL tables.

import type { MissionBattleConfig, MissionBattleForce } from "./battle-config.js";
import { type BorgData, readBorgs } from "./borg-data.js";
import {
  CHALLENGE_GROUP_ROSTERS,
  CHALLENGE_TIME_LIMIT_FRAMES,
  challengeBattleCount,
  challengeBudgetFor,
  challengeGroupChoicesFor,
  challengeMaxMembersFor,
  challengeModeForPlayerBudget,
  selectChallengeStage,
  type ChallengeGroupCode,
  type ChallengeMode,
  type ChallengeSide,
  type ChallengeStageSelection,
} from "./challenge-reference.js";
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
  /** Number of human players (1 = FIGHT ALONE, 2 = TEAM UP). */
  playerCount: number;
  /** Each human player's force. */
  playerForces: PlayerForce[];
  /** Roster data (borgs.json) for assembling enemy waves. */
  borgs: BorgData;
  /** Optional cap. Defaults to the original mode table count: 5 / 10 / 15. */
  battleCount?: number;
  /**
   * Borg ids used as an explicit CPU ally roster when fighting alone.
   * Omit this to use the original DOL ally group/budget tables.
   */
  fightAloneAllyBorgIds?: string[];
  /**
   * Arena/stage override for every battle. Omit this to use the original
   * Challenge stage-byte selector (`st00`, `st01`, ..., `st0e` subset).
   */
  arena?: string;
  /** Deterministic seed for DOL-style random table picks. */
  seed?: number;
  /** Optional RNG override. Must return a value in [0, 1). */
  rng?: () => number;
}

/**
 * Legacy shape retained for older callers. Challenge CPU budgets now come from
 * the original DOL tables rather than this curve.
 */
export interface EscalationCurve {
  /** @deprecated DOL-backed Challenge no longer uses this curve. */
  startFactor: number;
  /** @deprecated DOL-backed Challenge no longer uses this curve. */
  stepFactor: number;
}

export const DEFAULT_ESCALATION: EscalationCurve = {
  startFactor: 1.0,
  stepFactor: 0.24,
};

export function enemyTargetForBattle(
  budget: number,
  index: number,
  _curve: EscalationCurve = DEFAULT_ESCALATION,
): number {
  const mode = challengeModeForPlayerBudget(budget);
  return challengeBudgetFor("enemy", mode, index);
}

/** A built challenge run: the ordered battles + the run's live progression state. */
export interface ChallengeRun {
  budget: number;
  /** Original DOL Challenge table set: 0=NORMAL, 1=TUFF, 2=INSANE. */
  mode: ChallengeMode;
  /** Original Challenge player branch, clamped to 1P/2P. */
  playerCount: number;
  /** Ordered escalating battles. */
  battles: MissionBattleConfig[];
  /** Total battles in the run. */
  total: number;
  /** Index of the battle currently to be played (0-based). */
  current: number;
  /** Cumulative GRAND TOTAL across resolved battles. */
  score: number;
  /** Whether the run has ended (loss or run completed). */
  ended: boolean;
  /** Get the current battle config, or null if the run has ended. */
  getCurrentBattle(): MissionBattleConfig | null;
  /**
   * Advance the run with a battle result.
   *  - WIN  → score accumulates, advance to the next (tougher) battle. If that
   *           was the final battle, the run ends as completed.
   *  - LOSE → score accumulates (negative), run ends → caller returns to title.
   *
   * DERIVED — original post-battle branch FUN_801969a0 (chunk_0048.c:466-506):
   * the run advances ONLY when the winner mask [0x1f] equals the player side's
   * bit (mask==1); a mutual simultaneous destruction (mask==3) takes the same
   * state-6 failure exit as a loss (`2 < [0x1f]` guard, chunk_0048.c:486-488).
   * The judge's per-side "won" flags are equality tests (mask == 1<<side,
   * chunk_0003.c:4560-4604), so a draw DISPLAYS as LOSE on results — which is
   * why BattleResults only carries WIN/LOSE and a sim "draw" maps to LOSE here.
   * Timeout draws cannot occur in Challenge at all (timer frozen, see above).
   */
  next(result: BattleResults): ChallengeProgress;
}

export interface ChallengeProgress {
  outcome: "WIN" | "LOSE";
  /** Action the caller should take. */
  action: "advance" | "complete" | "title";
  /** Next battle to play, or null when ending. */
  nextBattle: MissionBattleConfig | null;
  /** Cumulative score after this result. */
  score: number;
  /** 0-based index now current. */
  current: number;
}

/**
 * Build a challenge run: an ordered list of escalating mission battle plans plus the
 * `next()` progression and cumulative scoring.
 */
export function createChallengeRun(options: ChallengeRunOptions): ChallengeRun {
  const {
    budget,
    playerForces,
    borgs,
    battleCount,
    arena,
  } = options;

  const playerCount = normalizeChallengePlayerCount(options.playerCount);
  const mode = challengeModeForPlayerBudget(budget);
  const referenceBattleCount = challengeBattleCount(mode);
  const totalBattles = Math.min(battleCount ?? referenceBattleCount, referenceBattleCount);
  const rng = options.rng ?? createChallengeRng(options.seed ?? seedFromRunOptions(mode, budget, playerCount));
  const energyById = energyMap(borgs);

  const battles: MissionBattleConfig[] = [];
  let previousStageByte: number | null = null;

  for (let i = 0; i < totalBattles; i++) {
    const stage: ChallengeStageSelection | null = arena ? null : selectChallengeStage(rng, previousStageByte);
    if (stage) previousStageByte = stage.stageByte;

    const enemyRosters = [0, 1].map(() =>
      buildCpuRoster({
        side: "enemy",
        mode,
        battleIndex: i,
        energyById,
        rng,
      }),
    );

    const playerForceConfigs: MissionBattleForce[] = playerForces.map((pf) => ({
      team: "player" as const,
      ownerPlayer: pf.player,
      borgIds: pf.borgIds,
    }));

    let allyGenerated: GeneratedCpuRoster | null = null;
    let allyBorgIds: readonly string[] | null = null;

    // FIGHT ALONE -> add the original CPU ally side, not a mirror of the player force.
    if (playerCount === 1) {
      if (options.fightAloneAllyBorgIds) {
        allyBorgIds = options.fightAloneAllyBorgIds;
      } else {
        allyGenerated = buildCpuRoster({
          side: "ally",
          mode,
          battleIndex: i,
          energyById,
          rng,
        });
        allyBorgIds = allyGenerated.borgIds;
      }
      playerForceConfigs.push({
        team: "player",
        ownerPlayer: null,
        borgIds: allyBorgIds.slice(),
        cpuAlly: true,
      });
    }

    const enemyForces: MissionBattleForce[] = enemyRosters.map((enemy) => ({
      team: "enemy",
      ownerPlayer: null,
      borgIds: enemy.borgIds,
    }));
    const enemyForceEnergy = sum(enemyRosters.map((enemy) => enemy.energy));
    const enemyBudgetCharge = sum(enemyRosters.map((enemy) => enemy.chargedEnergy));

    battles.push({
      arena: arena ?? stage?.stageId ?? "st00",
      timeLimitFrames: CHALLENGE_TIME_LIMIT_FRAMES,
      // DERIVED — Challenge setup writes the 18000-frame timer AND the pause flag
      // PTR_DAT_80433934[0x50]=1 (chunk_0048.c:390-392). The countdown zz_0029b58_
      // and the judge zz_00297c8_'s timeout branches are gated on [0x50]==0, so an
      // original Challenge battle can never end by timeout — only by a side's
      // remaining borgs/energy reaching 0.
      timerFrozen: true,
      label: `BATTLE ${i + 1} VS`,
      forces: [...playerForceConfigs, ...enemyForces],
      meta: {
        mode: "challenge",
        index: i,
        challengeMode: mode,
        enemyTargetEnergy: enemyRosters[0]?.targetEnergy ?? 0,
        enemyForceEnergy,
        enemyBudgetCharge,
        enemySlotCount: enemyRosters.length,
        enemySlotForceEnergy: enemyRosters.map((enemy) => enemy.energy),
        enemySlotBudgetCharge: enemyRosters.map((enemy) => enemy.chargedEnergy),
        enemyMaxMembers: enemyRosters[0]?.maxMembers ?? 0,
        enemyGroupChoices: [...(enemyRosters[0]?.groupChoices ?? [])],
        enemyPickedGroupCodes: enemyRosters.flatMap((enemy) => enemy.pickedGroupCodes),
        timeLimitFrames: CHALLENGE_TIME_LIMIT_FRAMES,
        ...(allyGenerated
          ? {
              allyTargetEnergy: allyGenerated.targetEnergy,
              allyForceEnergy: allyGenerated.energy,
              allyBudgetCharge: allyGenerated.chargedEnergy,
              allyMaxMembers: allyGenerated.maxMembers,
              allyGroupChoices: [...allyGenerated.groupChoices],
              allyPickedGroupCodes: [...allyGenerated.pickedGroupCodes],
            }
          : {}),
        ...(stage ? stageMeta(stage) : {}),
      },
    });
  }

  const run: ChallengeRun = {
    budget,
    mode,
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

export function createChallengeRng(seed = 0x47463445): () => number {
  let state = seed >>> 0;
  if (state === 0) state = 0x47463445;
  return () => {
    state = (state + 0x6d2b79f5) >>> 0;
    let t = state;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

interface GeneratedCpuRoster {
  borgIds: string[];
  energy: number;
  chargedEnergy: number;
  targetEnergy: number;
  maxMembers: number;
  groupChoices: readonly ChallengeGroupCode[];
  pickedGroupCodes: ChallengeGroupCode[];
}

interface BuildCpuRosterOptions {
  side: ChallengeSide;
  mode: ChallengeMode;
  battleIndex: number;
  energyById: ReadonlyMap<string, number>;
  rng: () => number;
}

function buildCpuRoster(options: BuildCpuRosterOptions): GeneratedCpuRoster {
  const { side, mode, battleIndex, energyById, rng } = options;
  const targetEnergy = challengeBudgetFor(side, mode, battleIndex);
  const maxMembers = challengeMaxMembersFor(side, mode, battleIndex);
  const groupChoices = challengeGroupChoicesFor(side, mode, battleIndex);
  const borgIds: string[] = [];
  const pickedGroupCodes: ChallengeGroupCode[] = [];
  let chargedEnergy = 0;
  let energy = 0;

  for (let i = 0; i < maxMembers; i += 1) {
    const groupCode = groupChoices[randomInt(rng, groupChoices.length)] ?? groupChoices[0];
    if (groupCode === undefined) break;
    const pool = CHALLENGE_GROUP_ROSTERS[groupCode];
    const candidate = pool.length > 0 ? pool[randomInt(rng, pool.length)] ?? "pl0008" : "pl0008";
    const cost = energyById.get(candidate) ?? 0;
    const chargedCost = Math.floor((cost * 2) / 3);
    if (chargedEnergy + chargedCost > targetEnergy) break;

    borgIds.push(candidate);
    pickedGroupCodes.push(groupCode);
    chargedEnergy += chargedCost;
    energy += cost;
  }

  return {
    borgIds,
    energy,
    chargedEnergy,
    targetEnergy,
    maxMembers,
    groupChoices,
    pickedGroupCodes,
  };
}

function energyMap(data: BorgData): ReadonlyMap<string, number> {
  return new Map(readBorgs(data).map((borg) => [borg.id, borg.energy] as const));
}

function seedFromRunOptions(mode: ChallengeMode, budget: number, playerCount: number): number {
  return (0x47463445 ^ Math.imul(mode + 1, 0x9e3779b1) ^ budget ^ (playerCount << 16)) >>> 0;
}

function normalizeChallengePlayerCount(playerCount: number): 1 | 2 {
  return Number.isFinite(playerCount) && playerCount >= 2 ? 2 : 1;
}

function stageMeta(stage: ChallengeStageSelection): {
  stageByte: number;
  stageSubtable: number;
  stageVariant: number;
} {
  return {
    stageByte: stage.stageByte,
    stageSubtable: stage.stageSubtable,
    stageVariant: stage.stageVariant,
  };
}

function randomInt(rng: () => number, maxExclusive: number): number {
  if (maxExclusive <= 0) throw new RangeError("maxExclusive must be positive");
  return Math.min(maxExclusive - 1, Math.floor(Math.max(0, Math.min(0.999999999, rng())) * maxExclusive));
}

function sum(values: readonly number[]): number {
  return values.reduce((total, value) => total + value, 0);
}
