// Simple CPU AI: produce a PlayerInput for a borg whose ownerPlayer === null (CPU), or for
// a CPU-ally / single-player opponent. Behaviour: seek the nearest enemy, keep the borg's
// preferred engage range, lock on, and attack when in range. Deterministic (no RNG).

import { distXZ } from "@gf/physics";
import { AI } from "./constants.js";
import type { BorgProfile } from "./stats.js";
import { emptyInput, type BorgRuntime, type PlayerInput } from "./types.js";

function nearestEnemy(self: BorgRuntime, all: BorgRuntime[]): BorgRuntime | null {
  let best: BorgRuntime | null = null;
  let bestD = Infinity;
  for (const o of all) {
    if (!o.alive || o.team === self.team || o.uid === self.uid) continue;
    const d = distXZ(self.pos, o.pos);
    if (d < bestD) {
      bestD = d;
      best = o;
    }
  }
  return best;
}

/**
 * Compute one frame of AI intent for `self`. Pure: reads world, returns an input.
 * Movement aims to hold `desiredRange`; attacks fire when within an attack window.
 */
export function stepAI(self: BorgRuntime, p: BorgProfile, all: BorgRuntime[]): PlayerInput {
  const input = emptyInput();
  const target = nearestEnemy(self, all);
  if (!target) return input;

  // Always try to keep a lock so projectiles home and facing tracks.
  input.lockOn = true;

  const d = distXZ(self.pos, target.pos);
  const dx = target.pos.x - self.pos.x;
  const dz = target.pos.z - self.pos.z;
  const inv = d > 1e-3 ? 1 / d : 0;
  const dirX = dx * inv;
  const dirZ = dz * inv;

  const desired = p.rangePref === "ranged" ? AI.RANGED_RANGE : AI.MELEE_RANGE;

  if (d > desired + AI.RANGE_SLACK) {
    // Approach.
    input.moveX = dirX;
    input.moveZ = dirZ;
  } else if (d < desired - AI.RANGE_SLACK) {
    // Back off (ranged kiting / spacing).
    input.moveX = -dirX;
    input.moveZ = -dirZ;
  }

  // Attack when within the effective attack window.
  if (p.hasMelee && d <= AI.MELEE_RANGE + AI.RANGE_SLACK) {
    input.attack = true;
  } else if (p.hasShot && d <= AI.RANGED_RANGE + AI.RANGE_SLACK) {
    input.attack = true;
  }

  // Occasionally pop a special when off cooldown and an enemy is close-ish.
  if ((self.cooldowns["special"] ?? 0) <= 0 && d <= AI.RANGED_RANGE) {
    // Use special only when several enemies might be near (melee AoE) or when ranged in range.
    if (p.rangePref !== "ranged" && d <= 120) input.special = true;
  }

  // If the target is above and we can fly/jump, hop toward it.
  if (target.pos.y - self.pos.y > 40 && self.grounded) {
    input.jump = true;
  }

  return input;
}
