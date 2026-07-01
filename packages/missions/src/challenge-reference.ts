// Original Challenge-mode tables recovered from the GG4E boot.dol.
//
// Primary decomp anchors:
//   - 0x801962c4 / FUN_801962c4: CPU force setup from per-mode battle tables.
//   - 0x80196eb8 / zz_0196eb8_: random borg id from group-code list.
//   - 0x80196dac / zz_0196dac_: Challenge stage-byte selector.

export type ChallengeMode = 0 | 1 | 2;
export type ChallengeSide = "ally" | "enemy";

export type ChallengeGroupCode =
  | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 | 60 | 61
  | 62 | 63 | 64 | 65 | 66 | 67 | 68 | 69;

export interface ChallengeStageSelection {
  /** Raw byte written to PTR_DAT_80433934[0x1c]. */
  stageByte: number;
  /** Browser-exported stage id corresponding to the raw stage byte. */
  stageId: string;
  /** Raw byte written to PTR_DAT_80433934[0x1d]. */
  stageSubtable: number;
  /** Raw byte written to PTR_DAT_80433934[0x1e]. */
  stageVariant: number;
}

export const CHALLENGE_BATTLE_COUNTS = [5, 10, 15] as const;

export const CHALLENGE_TIME_LIMIT_FRAMES = 18000;

export const CHALLENGE_STAGE_BYTES = [
  0x00,
  0x01,
  0x02,
  0x03,
  0x04,
  0x05,
  0x08,
  0x0a,
  0x0b,
  0x0c,
  0x0e,
] as const;

export const CHALLENGE_ALLY_BUDGETS = [
  [1000, 1000, 1200, 1200, 1400],
  [1200, 1200, 1400, 1400, 1600, 1600, 1800, 1800, 2000, 2200],
  [800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200],
] as const;

export const CHALLENGE_ENEMY_BUDGETS = [
  [1000, 1000, 1200, 1200, 1400],
  [1200, 1200, 1400, 1400, 1600, 1600, 1800, 1800, 2000, 2200],
  [1400, 1400, 1600, 1600, 1800, 1800, 2000, 2000, 2200, 2200, 2400, 2400, 2600, 2600, 2800],
] as const;

export const CHALLENGE_ALLY_MAX_MEMBERS = [
  [4, 4, 5, 5, 5],
  [4, 4, 4, 5, 5, 5, 6, 6, 6, 7],
  [4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5],
] as const;

export const CHALLENGE_ENEMY_MAX_MEMBERS = [
  [10, 10, 8, 8, 1],
  [10, 10, 10, 10, 2, 10, 10, 10, 10, 2],
  [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10],
] as const;

export const CHALLENGE_ALLY_GROUP_CODES = [
  [
    [50, 50, 50, 50],
    [50, 50, 50, 50],
    [50, 50, 50, 50],
    [50, 50, 50, 50],
    [50, 50, 50, 50],
  ],
  [
    [51, 51, 51, 51],
    [51, 51, 51, 51],
    [51, 51, 51, 51],
    [51, 51, 51, 51],
    [51, 51, 51, 51],
    [52, 52, 52, 52],
    [52, 52, 52, 52],
    [52, 52, 52, 52],
    [52, 52, 52, 52],
    [52, 52, 52, 52],
  ],
  [
    [52, 52, 52, 52],
    [52, 53, 52, 53],
    [53, 53, 53, 53],
    [53, 54, 53, 54],
    [54, 54, 54, 54],
    [54, 55, 54, 55],
    [55, 55, 55, 55],
    [55, 56, 55, 56],
    [56, 56, 56, 56],
    [56, 57, 56, 57],
    [57, 57, 57, 57],
    [57, 58, 57, 58],
    [58, 58, 58, 58],
    [58, 60, 58, 60],
    [60, 61, 60, 58],
  ],
] as const satisfies readonly (readonly (readonly ChallengeGroupCode[])[])[];

export const CHALLENGE_ENEMY_GROUP_CODES = [
  [
    [48, 48, 48, 48],
    [49, 49, 49, 49],
    [50, 50, 50, 50],
    [51, 51, 51, 51],
    [64, 64, 64, 64],
  ],
  [
    [49, 49, 49, 49],
    [50, 50, 50, 50],
    [51, 51, 51, 51],
    [52, 52, 52, 52],
    [66, 66, 66, 66],
    [53, 53, 53, 53],
    [54, 54, 54, 54],
    [55, 55, 55, 55],
    [56, 56, 56, 56],
    [65, 65, 65, 65],
  ],
  [
    [50, 50, 50, 50],
    [51, 51, 51, 51],
    [52, 52, 52, 52],
    [54, 54, 54, 54],
    [67, 67, 67, 67],
    [64, 53, 53, 53],
    [55, 68, 55, 55],
    [56, 56, 69, 56],
    [58, 58, 58, 64],
    [66, 66, 66, 66],
    [57, 57, 69, 57],
    [59, 68, 59, 59],
    [60, 60, 66, 60],
    [65, 61, 61, 61],
    [61, 61, 61, 61],
  ],
] as const satisfies readonly (readonly (readonly ChallengeGroupCode[])[])[];

export const CHALLENGE_GROUP_ROSTERS = {
  48: ["pl0008", "pl0105", "pl0206", "pl0303", "pl0705", "pl0a05", "pl0b05", "pl0f04", "pl000c", "pl030c", "pl030d", "pl070b", "pl090b"],
  49: ["pl010a", "pl0807", "pl0406", "pl040b", "pl040c", "pl040d", "pl070c", "pl070d", "pl0b07", "pl0a0a"],
  50: ["pl0000", "pl0003", "pl0100", "pl0103", "pl020a", "pl0300", "pl0301", "pl0b02", "pl0b03"],
  51: ["pl0101", "pl0307", "pl0700", "pl0a00", "pl0b00", "pl0b01", "pl0b04", "pl0703", "pl0407"],
  52: ["pl0306", "pl0005", "pl0200", "pl0201", "pl020c", "pl0702", "pl0d01", "pl0808", "pl0800", "pl0801", "pl0a03"],
  53: ["pl0209", "pl0004", "pl0001", "pl0400", "pl0402", "pl0404", "pl0405", "pl0409", "pl0408", "pl0401", "pl0403"],
  54: ["pl0a01", "pl020b", "pl0302", "pl0309", "pl050d", "pl050e"],
  55: ["pl0701", "pl0708", "pl0802", "pl0a06", "pl020d"],
  56: ["pl0c00", "pl0c01", "pl0619", "pl061f", "pl0625", "pl0c00", "pl0c01", "pl0619", "pl061f", "pl0625", "pl0628"],
  57: ["pl0006", "pl0102", "pl0203", "pl0305", "pl0501", "pl0517", "pl0a08", "pl0c02"],
  58: ["pl0007", "pl0104", "pl0202", "pl0204", "pl0704", "pl020e", "pl0208", "pl030a", "pl0706", "pl0804", "pl080c", "pl0a02"],
  59: ["pl050c", "pl0515", "pl0516", "pl0502"],
  60: ["pl0627", "pl0621", "pl0623", "pl0618", "pl061a", "pl061e", "pl0604", "pl0606", "pl0613", "pl0610"],
  61: ["pl061c", "pl061d", "pl0616", "pl0617", "pl0600", "pl0601", "pl0608", "pl0609"],
  62: [],
  63: [],
  64: ["pl0500", "pl0509", "pl050a"],
  65: ["pl0e00", "pl0e03", "pl0e01", "pl0e02"],
  66: ["pl0c04"],
  67: ["pl0d06", "pl0809", "pl0c05"],
  68: ["pl090a", "pl0908", "pl0909"],
  69: ["pl0901", "pl090c", "pl080d", "pl0b06"],
} as const satisfies Record<ChallengeGroupCode, readonly string[]>;

export function challengeModeForPlayerBudget(budget: number): ChallengeMode {
  if (budget <= 1500) return 0;
  if (budget <= 2000) return 1;
  return 2;
}

export function challengeBattleCount(mode: ChallengeMode): number {
  return CHALLENGE_BATTLE_COUNTS[mode];
}

export function challengeBudgetFor(side: ChallengeSide, mode: ChallengeMode, battleIndex: number): number {
  return tableValue(side === "ally" ? CHALLENGE_ALLY_BUDGETS : CHALLENGE_ENEMY_BUDGETS, mode, battleIndex, `${side} budget`);
}

export function challengeMaxMembersFor(side: ChallengeSide, mode: ChallengeMode, battleIndex: number): number {
  return tableValue(side === "ally" ? CHALLENGE_ALLY_MAX_MEMBERS : CHALLENGE_ENEMY_MAX_MEMBERS, mode, battleIndex, `${side} max members`);
}

export function challengeGroupChoicesFor(side: ChallengeSide, mode: ChallengeMode, battleIndex: number): readonly ChallengeGroupCode[] {
  return tableRow(side === "ally" ? CHALLENGE_ALLY_GROUP_CODES : CHALLENGE_ENEMY_GROUP_CODES, mode, battleIndex, `${side} group choices`);
}

export function challengeStageId(stageByte: number): string {
  return `st${stageByte.toString(16).padStart(2, "0")}`;
}

export function selectChallengeStage(
  rng: () => number,
  previousStageByte: number | null = null,
): ChallengeStageSelection {
  let stageByte = draw(CHALLENGE_STAGE_BYTES, rng);
  for (let attempt = 0; stageByte === previousStageByte && attempt < CHALLENGE_STAGE_BYTES.length; attempt += 1) {
    stageByte = draw(CHALLENGE_STAGE_BYTES, rng);
  }

  return {
    stageByte,
    stageId: challengeStageId(stageByte),
    stageSubtable: randomInt(rng, 3),
    stageVariant: randomInt(rng, 4),
  };
}

function tableValue(
  table: readonly (readonly number[])[],
  mode: ChallengeMode,
  battleIndex: number,
  label: string,
): number {
  const value = table[mode]?.[battleIndex];
  if (value === undefined) {
    throw new RangeError(`Missing Challenge ${label} for mode ${mode}, battle ${battleIndex}`);
  }
  return value;
}

function tableRow(
  table: readonly (readonly (readonly ChallengeGroupCode[])[])[],
  mode: ChallengeMode,
  battleIndex: number,
  label: string,
): readonly ChallengeGroupCode[] {
  const value = table[mode]?.[battleIndex];
  if (!value) {
    throw new RangeError(`Missing Challenge ${label} for mode ${mode}, battle ${battleIndex}`);
  }
  return value;
}

function draw<T>(values: readonly T[], rng: () => number): T {
  const value = values[randomInt(rng, values.length)];
  if (value === undefined) throw new RangeError("Cannot draw from an empty Challenge table");
  return value;
}

function randomInt(rng: () => number, maxExclusive: number): number {
  if (maxExclusive <= 0) throw new RangeError("maxExclusive must be positive");
  const value = Math.floor(Math.max(0, Math.min(0.999999999, rng())) * maxExclusive);
  return Math.min(maxExclusive - 1, value);
}
