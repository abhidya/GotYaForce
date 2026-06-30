// Source: research/PHASE0_RESEARCH.md section 6 documents GG4E wake-up
// invincibility at 0x8005d4b0 / 0x8005c7d8, static 60.0 at 0x80437448,
// and countdown at 0x80055c00.
export const WAKE_UP_INVINCIBILITY_FRAMES = 60;

export type BorgStats = {
  id: string;
  name: string;
  energy: number;
  hp?: string | number;
  defense: number;
  shot: number;
  attack: number;
  speed: number;
  jump?: string | number;
};

export type ForceBudgetResult =
  | {
      ok: true;
      energy: number;
      budget: number;
      count: number;
    }
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
    if (borg === undefined) {
      throw new RangeError(`Unknown borg id: ${id}`);
    }
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
    return {
      ok: false,
      error: "unknown-borg",
      energy,
      budget,
      count: forceIds.length,
      missingIds,
    };
  }

  if (forceIds.length > max) {
    return {
      ok: false,
      error: "too-many-borgs",
      energy,
      budget,
      count: forceIds.length,
      max,
    };
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

  return {
    ok: true,
    energy,
    budget,
    count: forceIds.length,
  };
}

function borgsById(borgs: readonly BorgStats[]): ReadonlyMap<string, BorgStats> {
  return new Map(borgs.map((borg) => [borg.id, borg]));
}
