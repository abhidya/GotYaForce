// Per-borg stat model. Drives all per-borg behavior from the original roster data.
//
// The JSON fields we consume (see borgs.json):
//   energy  -> deploy cost AND the win/lose energy pool contribution
//   hp      -> fallback only; runtime prefers the decompiled 0x802f2988 stat row
//   defense -> fallback only; runtime prefers pl####data.bin byte 0x1a4
//   shot    -> fallback only; runtime prefers pl####data.bin byte 0x1a5
//   attack  -> fallback only; runtime prefers pl####data.bin byte 0x1a6
//   speed   -> fallback only; runtime prefers pl####data.bin byte 0x1a7
//   jump    -> fallback flyer flag; runtime prefers pl####data.bin byte 0x1a3
//              for the discrete air-jump count
//   type    -> fallback only; runtime prefers pl####data.bin byte 0x1a0 (type enum)
//   tribe   -> cosmetic / grouping, unused by the sim
//
// Confidence note: max HP now comes from the decompiled 0x802f2988 row read by zz_0055f90_
// (behavior-notes.md ag), while defense/shot/attack/speed come from pl####data.bin bytes.
// Runtime HP damage is computed separately from damage records in damageFormula.ts.

import { actorDataCombatStatsForBorgId } from "./actorDataStats.js";
import { sourceStatsForBorgId } from "./sourceBorgStats.js";

/**
 * Raw borg stats as they appear in borgs.json. Kept structurally compatible with the
 * pre-existing BorgStats used by forceEnergy/validateForceBudget below.
 */
export interface BorgStats {
  id: string;
  name: string;
  energy: number;
  hp?: string | number;
  defense: number;
  shot: number;
  attack: number;
  speed: number;
  jump?: string | number;
  type?: string;
  tribe?: string;
}

/** Engage-range preference derived from the borg "type" string. */
export type RangePref = "melee" | "mixed" | "ranged";

/** Resolved, sim-ready per-borg parameters (computed once at battle start). */
export interface BorgProfile {
  id: string;
  name: string;
  energy: number;
  maxHp: number;
  defense: number;
  shot: number;
  attack: number;
  speed: number;
  /** Number of mid-air jumps before flight ("Air jump level N" -> N; flyers default 3). */
  airJumpLevel: number;
  /** True for "Boost jump"/"N/A" tribes that sustain flight (Machine, Dragon, Air, Wing...). */
  flyer: boolean;
  /** Has a usable ranged "shot" weapon. */
  hasShot: boolean;
  /** Has a usable melee attack. */
  hasMelee: boolean;
  rangePref: RangePref;
  /**
   * ATK-020: the borg's level BYTE (behavior-notes.md ak: actor+0x3ec, 0-based), when known.
   * Selects the stat row via the CORRECTED empirical rule row = levelByte + 2 (behavior-notes
   * (av)/(aw), 200/203 validated: display-1 -> row 2, display-10 -> row 11; monotonic). Undefined
   * means "use the default row" (byte 0 -> row 2) -- the SAME row every pre-ATK-020 profile was
   * already built from, so omitting this field reproduces today's extracted values exactly
   * (G RED (pl0615) default row -> HP 200 / ammo 5, the live-verified anchor).
   * Stored value packing (colorVariant<<8 | level) is OBSERVED_GUIDE context from (an) section
   * 6 -- not itself parsed here; callers pass the already-unpacked level byte.
   */
  level?: number;
}

/** Parse the "L1/L10" hp string (or number) to the level-1 battle HP. */
export function parseHp(hp: string | number | undefined): number {
  if (typeof hp === "number") return hp;
  if (typeof hp === "string") {
    const first = hp.split("/")[0];
    const n = first === undefined ? NaN : Number.parseInt(first.trim(), 10);
    if (Number.isFinite(n) && n > 0) return n;
  }
  return 100; // safe fallback so the sim never produces NaN HP
}

/**
 * Parse the "jump" field into fallback (airJumpLevel, flyer).
 *  - "Air jump level N"  -> N air jumps, not a sustained flyer
 *  - "Boost jump"        -> sustained-flight flyer (3 air jumps as the airborne budget)
 *  - "N/A"               -> always-airborne flyer (jets/fortresses) -> treated as flyer
 */
export function parseJump(jump: string | number | undefined): {
  airJumpLevel: number;
  flyer: boolean;
} {
  if (typeof jump === "string") {
    const j = jump.toLowerCase();
    const m = j.match(/air jump level\s*(\d+)/);
    if (m && m[1] !== undefined) {
      return { airJumpLevel: Number.parseInt(m[1], 10), flyer: false };
    }
    if (j.includes("boost")) return { airJumpLevel: 3, flyer: true };
    if (j.includes("n/a")) return { airJumpLevel: 3, flyer: true };
  }
  if (typeof jump === "number") return { airJumpLevel: jump, flyer: false };
  return { airJumpLevel: 3, flyer: false };
}

function actorDataAirJumpLevel(raw: number | undefined, fallback: number): number {
  if (raw === undefined) return fallback;
  // DERIVED: pl####data.bin byte +0x1a3 is the discrete air-jump count on the
  // verifiable domains: Air jump level N -> N, Boost jump -> 0. Most N/A flyer
  // records carry 0xff, which is a sentinel/no-count value rather than 255 jumps.
  if (raw === 0xff) return 0;
  return raw;
}

function rangePrefOf(
  typeCode: number | undefined,
  type: string | undefined,
  hasShot: boolean,
  hasMelee: boolean,
): RangePref {
  // DERIVED: actor-data byte 0x1a0 is the borg-type enum (0=long range, 1=short range,
  // 2=speed, 3=almighty, 4=support), verified against borgs.json for all 190 borgs with
  // metadata. Prefer it; fall back to the borgs.json type string when no record exists.
  if (typeCode === 0) return "ranged";
  if (typeCode === 1) return "melee";
  if (typeCode === undefined) {
    const t = (type ?? "").toLowerCase();
    if (t.includes("long range")) return "ranged";
    if (t.includes("short range")) return "melee";
  }
  if (!hasMelee && hasShot) return "ranged";
  if (hasMelee && !hasShot) return "melee";
  return "mixed";
}

/**
 * Build the resolved per-borg profile consumed by movement/combat/AI.
 *
 * `level` (ATK-020, optional): the borg's level BYTE (behavior-notes.md ak, actor+0x3ec, 0-based).
 * Omitting it (the default) reproduces every pre-ATK-020 caller's behavior EXACTLY -- it
 * resolves to the same default row (byte 0 -> row 2) that sourceStatsForBorgId(id) already
 * returned with no level argument. Passing a level re-selects the stat row per the CORRECTED
 * empirical rule row = levelByte + 2 (behavior-notes (av)/(aw), 200/203 validated), clamped to
 * the borg's available rows by sourceStatsForBorgId itself.
 */
export function buildProfile(s: BorgStats, level?: number): BorgProfile {
  const parsedJump = parseJump(s.jump);
  const actorStats = actorDataCombatStatsForBorgId(s.id);
  const defense = actorStats?.defense ?? s.defense;
  const shot = actorStats?.shot ?? s.shot;
  const attack = actorStats?.attack ?? s.attack;
  const speed = actorStats?.speed ?? s.speed;
  const airJumpLevel = actorDataAirJumpLevel(actorStats?.airJump, parsedJump.airJumpLevel);
  const sourceStats = sourceStatsForBorgId(s.id, level);
  const hasShot = shot > 0;
  const hasMelee = attack > 0;
  return {
    id: s.id,
    name: s.name,
    energy: s.energy,
    maxHp: sourceStats?.maxHp ?? parseHp(s.hp),
    defense,
    shot,
    attack,
    speed,
    airJumpLevel,
    flyer: parsedJump.flyer,
    hasShot,
    hasMelee,
    rangePref: rangePrefOf(actorStats?.typeCode, s.type, hasShot, hasMelee),
    ...(level !== undefined ? { level } : {}),
  };
}

// ----------------------------------------------------------------------------------------
// Pre-existing force-budget helpers (kept; other packages already import these).
// ----------------------------------------------------------------------------------------

export type ForceBudgetResult =
  | { ok: true; energy: number; budget: number; count: number }
  | {
      ok: false;
      error: "unknown-borg" | "too-many-borgs" | "over-budget";
      energy: number;
      budget: number;
      count: number;
      missingIds?: string[];
      max?: number;
      overBy?: number;
    };

export function forceEnergy(
  forceIds: readonly string[],
  borgs: readonly BorgStats[],
): number {
  const byId = borgsById(borgs);
  let energy = 0;
  for (const id of forceIds) {
    const borg = byId.get(id);
    if (borg === undefined) throw new RangeError(`Unknown borg id: ${id}`);
    energy += borg.energy;
  }
  return energy;
}

export function validateForceBudget(
  forceIds: readonly string[],
  borgs: readonly BorgStats[],
  budget: number,
  max = 30,
): ForceBudgetResult {
  const byId = borgsById(borgs);
  const missingIds: string[] = [];
  let energy = 0;
  for (const id of forceIds) {
    const borg = byId.get(id);
    if (borg === undefined) {
      missingIds.push(id);
      continue;
    }
    energy += borg.energy;
  }
  if (missingIds.length > 0) {
    return { ok: false, error: "unknown-borg", energy, budget, count: forceIds.length, missingIds };
  }
  if (forceIds.length > max) {
    return { ok: false, error: "too-many-borgs", energy, budget, count: forceIds.length, max };
  }
  if (energy > budget) {
    return {
      ok: false,
      error: "over-budget",
      energy,
      budget,
      count: forceIds.length,
      overBy: energy - budget,
    };
  }
  return { ok: true, energy, budget, count: forceIds.length };
}

function borgsById(borgs: readonly BorgStats[]): ReadonlyMap<string, BorgStats> {
  return new Map(borgs.map((borg) => [borg.id, borg]));
}
