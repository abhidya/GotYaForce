// Simple CPU AI: produce a PlayerInput for a borg whose ownerPlayer === null (CPU), or for
// a CPU-ally / single-player opponent. Behaviour: keep a valid target, otherwise seek the
// nearest enemy, hold preferred engage range, lock on, and attack when in range. Deterministic.

import { distXZ } from "@gf/physics";
import { actionProfileForProfile } from "./actionProfiles.js";
import { meleeEngageRangeFor, X_CHARGE } from "./combat.js";
import { AI } from "./constants.js";
import { xChargeMoveForBorgId } from "./moveRuntime.js";
import type { BorgProfile } from "./stats.js";
import { emptyInput, type BorgRuntime, type PlayerInput } from "./types.js";

function isEnemy(self: BorgRuntime, other: BorgRuntime): boolean {
  return other.alive && other.hp > 0 && other.state !== "death" && other.team !== self.team && other.uid !== self.uid;
}

function currentLockedEnemy(self: BorgRuntime, all: BorgRuntime[]): BorgRuntime | null {
  if (!self.lockTarget) return null;
  const target = all.find((o) => o.uid === self.lockTarget);
  return target && isEnemy(self, target) ? target : null;
}

function nearestEnemy(self: BorgRuntime, all: BorgRuntime[]): BorgRuntime | null {
  let best: BorgRuntime | null = null;
  let bestD = Infinity;
  for (const o of all) {
    if (!isEnemy(self, o)) continue;
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
  const target = currentLockedEnemy(self, all) ?? nearestEnemy(self, all);
  if (!target) return input;

  // Always try to keep a lock so projectiles home and facing tracks.
  input.lockOn = true;

  const d = distXZ(self.pos, target.pos);
  const dx = target.pos.x - self.pos.x;
  const dz = target.pos.z - self.pos.z;
  const inv = d > 1e-3 ? 1 / d : 0;
  const dirX = dx * inv;
  const dirZ = dz * inv;

  // Per-borg melee window (melee workstream): the borg's ACTUAL meleeDef.range replaces the
  // flat AI.MELEE_RANGE as the desired distance, and the attack gate uses the same shared
  // engage window the sim's contextual-B resolver selects with (combat.ts meleeEngageRangeFor
  // — the melee lunge covers engage-window -> reach). The old flat 50+RANGE_SLACK gate
  // whiffed the whole 64-110 band. Still TUNED (constants.ts AI note: no isolated CPU
  // decision function exists in the ROM — cpu-ai-evidence.md).
  const actionProfile = actionProfileForProfile(p);
  const meleeDef = actionProfile.melee;
  const meleeEngage = meleeDef ? meleeEngageRangeFor(meleeDef) : 0;
  const desired = p.rangePref === "ranged" || !meleeDef ? AI.RANGED_RANGE : meleeDef.range;

  // Movement intent. While locked to `target`, stepMovement resolves the stick TARGET-
  // RELATIVE (resolveHorizontalIntent: +moveZ = toward the lock target, -moveZ = away), so
  // emit lock-relative input — the old world-space direction got rotated by that resolver
  // and melee AI orbited instead of closing. Unlocked (e.g. lock not yet acquired this
  // frame), keep the world-space fallback.
  const lockedToTarget = self.lockTarget === target.uid;
  if (d > desired + AI.RANGE_SLACK) {
    // Approach.
    if (lockedToTarget) {
      input.moveZ = 1;
    } else {
      input.moveX = dirX;
      input.moveZ = dirZ;
    }
  } else if (d < desired - AI.RANGE_SLACK) {
    // Back off (ranged kiting / spacing).
    if (lockedToTarget) {
      input.moveZ = -1;
    } else {
      input.moveX = -dirX;
      input.moveZ = -dirZ;
    }
  }

  // Attack when within the effective attack window. Melee/mixed borgs swing inside the
  // engage window (the sim lunge closes the remaining gap); ranged-pref borgs with a melee
  // def also take the opportunistic close-range swing (the contextual-B resolver picks
  // melee for them at this distance anyway).
  if (meleeDef && d <= meleeEngage) {
    input.attack = true;
  } else if (p.hasShot && d <= AI.RANGED_RANGE + AI.RANGE_SLACK) {
    input.attack = true;
  }

  // Charge-shot borgs fire on RELEASE (combat.ts stepAttacks), so a CPU that held attack
  // forever would never shoot. Release once a tier-1+ charge has built up: the sim reads the
  // hold->release edge and fires the scaled projectile that frame. TUNED pacing choice.
  if (input.attack) {
    const shot = actionProfileForProfile(p).shot;
    if (shot?.chargeable && (self.cooldowns["chargeFrames"] ?? 0) >= shot.chargeTier1Frames + 10) {
      input.attack = false;
    }
  }

  // Occasionally pop a special when off cooldown and an enemy is close-ish.
  if ((self.cooldowns["special"] ?? 0) <= 0 && d <= AI.RANGED_RANGE) {
    // Use special only when several enemies might be near (melee AoE) or when ranged in range.
    if (p.rangePref !== "ranged" && d <= 120) {
      if (xChargeMoveForBorgId(self.borgId) !== null) {
        // X-Charge borg (OBSERVED_WIKI "X Charge" row): HOLD X so the sim accumulates
        // xChargeFrames, then release once a tier-1+ charge has built up — mirrors the
        // B-charge release block below (stepAttacks fires the scaled special on the
        // hold->release edge). TUNED pacing choice, same +10-frame margin as the B rule.
        if ((self.cooldowns["xChargeFrames"] ?? 0) < X_CHARGE.TIER1_FRAMES + 10) {
          input.special = true; // hold to charge
        } else {
          // Charge banked: release to fire. If the release edge lands while the sim gates
          // the special (e.g. mid-attack), the charge stays banked — re-press whenever the
          // specialHeld latch is clear so a fresh release edge retries until it fires.
          input.special = (self.cooldowns["specialHeld"] ?? 0) <= 0;
        }
      } else {
        // Press-EDGE semantics (combat.ts specialHeld latch): only press while the latch is
        // clear, so a press that was blocked (e.g. mid-attack) reads as release-then-re-press
        // instead of one long hold that never edges — holding forever would never fire now.
        input.special = (self.cooldowns["specialHeld"] ?? 0) <= 0;
      }
    }
  }

  // If the target is above and we can fly/jump, hop toward it.
  if (target.pos.y - self.pos.y > 40 && self.grounded) {
    input.jump = true;
  }

  return input;
}
