// Per-borg stat model. Drives all per-borg behavior from the original roster data.
//
// The JSON fields we consume (see borgs.json):
//   energy  -> deploy cost AND the win/lose energy pool contribution
//   hp      -> "L1/L10" string, e.g. "200/290"; we use the L1 (first) value as battle HP
//   defense -> fallback only; runtime prefers pl####data.bin byte 0x1a4
//   shot    -> fallback only; runtime prefers pl####data.bin byte 0x1a5
//   attack  -> fallback only; runtime prefers pl####data.bin byte 0x1a6
//   speed   -> fallback only; runtime prefers pl####data.bin byte 0x1a7
//   jump    -> "Air jump level N" | "Boost jump" | "N/A" -> air-jump count + flyer flag
//   type    -> fallback only; runtime prefers pl####data.bin byte 0x1a0 (type enum)
//   tribe   -> cosmetic / grouping, unused by the sim
//
// Confidence note: the HP field (object+0x1C6) and subtract-and-clamp application are now
// DERIVED from a live disassembly trace (behavior-notes.md s4h); the exact attack/defense ->
// raw-damage coefficients are still TUNED FROM THE STAT TABLE, not ported from the ROM
// (`zz_003cd5c_` is known to be a table-driven formula, but not yet fully ported).
// Clearly flagged in packages/combat/src/constants.ts.

import { actorDataCombatStatsForBorgId } from "./actorDataStats.js";

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
 * Parse the "jump" field into (airJumpLevel, flyer).
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

/** Build the resolved per-borg profile consumed by movement/combat/AI. */
export function buildProfile(s: BorgStats): BorgProfile {
  const { airJumpLevel, flyer } = parseJump(s.jump);
  const actorStats = actorDataCombatStatsForBorgId(s.id);
  const defense = actorStats?.defense ?? s.defense;
  const shot = actorStats?.shot ?? s.shot;
  const attack = actorStats?.attack ?? s.attack;
  const speed = actorStats?.speed ?? s.speed;
  const hasShot = shot > 0;
  const hasMelee = attack > 0;
  return {
    id: s.id,
    name: s.name,
    energy: s.energy,
    maxHp: parseHp(s.hp),
    defense,
    shot,
    attack,
    speed,
    airJumpLevel,
    flyer,
    hasShot,
    hasMelee,
    rangePref: rangePrefOf(actorStats?.typeCode, s.type, hasShot, hasMelee),
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
