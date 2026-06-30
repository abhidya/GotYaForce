// @gf/missions — borg-data.ts
//
// Shared borg-roster types + the `enemyForceForBudget` assembler used by
// challenge mode to build enemy waves near a cost target. Data is injected
// (the library never reads the filesystem); selfcheck.ts loads the JSON.

/** A roster borg as it appears in packages/assets/data/borgs.json. */
export interface Borg {
  id: string;
  name: string;
  energy: number;
  tribe: string;
  hasModel?: boolean;
  model?: string | null;
}

/** Either the raw borgs.json object or a bare array of borgs. */
export type BorgData = readonly Borg[] | { borgs: readonly Borg[] };

export function readBorgs(data: BorgData): readonly Borg[] {
  return "borgs" in data ? data.borgs : data;
}

/**
 * Build an enemy force whose summed energy lands as close as possible to
 * `targetEnergy`, drawing from `pool` (defaults to all Death Borg-tribe units
 * in the roster). Greedy descending fill, then a final top-up pass.
 *
 * Returns the chosen borg ids (in spawn order, cheapest-first so the wave
 * escalates) and the realised total energy.
 */
export function enemyForceForBudget(
  targetEnergy: number,
  data: BorgData,
  options: EnemyForceOptions = {},
): EnemyForce {
  const all = readBorgs(data);
  const pool = (options.pool ?? deathBorgPool(all))
    .slice()
    .filter((b) => b.energy > 0)
    .sort((a, b) => b.energy - a.energy);

  if (pool.length === 0) {
    return { borgIds: [], energy: 0, target: targetEnergy };
  }

  const maxCount = options.maxCount ?? 30;
  const chosen: Borg[] = [];
  let energy = 0;

  // Greedy: repeatedly add the largest borg that still fits under target.
  // Cap at maxCount; allow a small overshoot tolerance so we don't stall.
  const tolerance = options.tolerance ?? Math.max(50, Math.round(targetEnergy * 0.04));

  while (chosen.length < maxCount && energy < targetEnergy - tolerance) {
    const remaining = targetEnergy - energy;
    // Pick the largest borg that fits the remaining room (pool is desc-sorted).
    const fit = pool.find((b) => b.energy <= remaining + tolerance);
    if (!fit) break;
    chosen.push(fit);
    energy += fit.energy;
  }

  // If we added nothing (target smaller than the cheapest borg), add the
  // single cheapest borg so the wave is never empty.
  if (chosen.length === 0) {
    const cheapest = pool[pool.length - 1]!;
    chosen.push(cheapest);
    energy += cheapest.energy;
  }

  // Spawn order: cheapest first so the enemy wave ramps up.
  chosen.sort((a, b) => a.energy - b.energy);

  return {
    borgIds: chosen.map((b) => b.id),
    energy,
    target: targetEnergy,
  };
}

export interface EnemyForceOptions {
  /** Candidate borgs to draw from. Defaults to Death Borg-tribe units. */
  pool?: readonly Borg[];
  /** Max borgs in the force (force-size cap). Default 30. */
  maxCount?: number;
  /** Acceptable overshoot/undershoot around the target. Default ~4% of target. */
  tolerance?: number;
}

export interface EnemyForce {
  borgIds: string[];
  energy: number;
  target: number;
}

/** All Death Borg-tribe units — the canonical disposable enemy fodder. */
export function deathBorgPool(data: BorgData): Borg[] {
  return readBorgs(data).filter((b) => b.tribe === "Death Borg");
}
