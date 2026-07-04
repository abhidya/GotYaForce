// Simple CPU AI: produce a PlayerInput for a borg whose ownerPlayer === null (CPU), or for
// a CPU-ally / single-player opponent. Behaviour: keep a valid target, otherwise seek the
// nearest enemy, hold preferred engage range, lock on, and attack when in range. Deterministic.

import { distXZ } from "@gf/physics";
import { actionProfileForProfile } from "./actionProfiles.js";
import { meleeEngageRangeFor, X_CHARGE } from "./combat.js";
import { AI, MOVE } from "./constants.js";
import { groundRunSpeedForBorgId } from "./movementData.js";
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
 * Deterministic 0..1 hash of a uid string (FNV-1a-ish), used to stagger AI decision timing
 * per-borg without any RNG/nondeterminism. TUNED port-ism — see AI.ATTACK_REACTION_* in
 * constants.ts for why this exists (desyncs symmetric CPU-vs-CPU swing timing).
 */
function hash01(uid: string): number {
  let h = 2166136261;
  for (let i = 0; i < uid.length; i += 1) {
    h ^= uid.charCodeAt(i);
    h = Math.imul(h, 16777619);
  }
  // Unsigned 32-bit -> [0, 1).
  return (h >>> 0) / 4294967296;
}

/** This borg's DERIVED raw ground run speed (movementData.ts), or the MOVE fallback formula
 *  result for synthetic ids without a data page — mirrors movement.ts groundSpeed(p) so the
 *  AI's distance bands scale with the SAME per-borg speed the sim actually moves it at. */
function ownGroundSpeed(self: BorgRuntime, p: BorgProfile): number {
  return groundRunSpeedForBorgId(self.borgId) ?? MOVE.GROUND_BASE + p.speed * MOVE.GROUND_PER_STAT;
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
  //
  // RAW-SCALE RETUNE (2026-07-04): kite slack is now proportional to the borg's OWN
  // groundRunSpeedForBorgId (movementData.ts) instead of the flat AI.RANGE_SLACK (60 units,
  // sized for the retired 22 u/f world) — see AI.KITE_SLACK_SPEED_MULT in constants.ts.
  // TUNED port-ism (no isolated CPU decision function exists in the ROM — cpu-ai-evidence.md).
  const ownSpeed = ownGroundSpeed(self, p);
  const kiteSlack = Math.max(AI.RANGE_SLACK, ownSpeed * AI.KITE_SLACK_SPEED_MULT);
  const lockedToTarget = self.lockTarget === target.uid;
  const farFromDesired = d > desired + kiteSlack;
  if (farFromDesired) {
    // Approach.
    if (lockedToTarget) {
      input.moveZ = 1;
    } else {
      input.moveX = dirX;
      input.moveZ = dirZ;
    }
  } else if (d < desired - kiteSlack) {
    // Back off (ranged kiting / spacing).
    if (lockedToTarget) {
      input.moveZ = -1;
    } else {
      input.moveX = -dirX;
      input.moveZ = -dirZ;
    }
  }

  // Dash to close ground when well outside engage range. RAW-SCALE RETUNE (2026-07-04):
  // ground speeds are now per-borg DERIVED raw values (G RED 12 u/f) instead of the old
  // 22 u/f anchor (~0.55x as fast), so walking alone from stage-scale spawn separations
  // (thousands of XZ units on the larger Challenge stages) took a very long time to close —
  // scripts/selfcheck-challenge-stages.mjs showed several large stages never landing a hit
  // in 1200 frames. Dashing (movement.ts DASH.SPEED, a TUNED port-ism — no dash state exists
  // in the ROM) covers ground fast while the walk-in continues underneath it. Gated off the
  // borg's own speed (not a flat distance) so it kicks in consistently across fast/slow
  // borgs, and off the movement.ts dash cooldown/active window so the AI doesn't spam a
  // dash press that the sim would just ignore. TUNED port-ism.
  if (
    farFromDesired &&
    self.grounded &&
    d > desired + ownSpeed * AI.DASH_APPROACH_SPEED_MULT &&
    (self.cooldowns["dash"] ?? 0) <= 0 &&
    (self.cooldowns["dashActive"] ?? 0) <= 0
  ) {
    input.dash = true;
  }

  // Attack when within the effective attack window. Melee/mixed borgs swing inside the
  // engage window (the sim lunge closes the remaining gap); ranged-pref borgs with a melee
  // def also take the opportunistic close-range swing (the contextual-B resolver picks
  // melee for them at this distance anyway).
  const inAttackWindow =
    (meleeDef !== null && d <= meleeEngage) || (p.hasShot && d <= AI.RANGED_RANGE + kiteSlack);

  // Decision-pacing gate (RAW-SCALE RETUNE 2026-07-04, TUNED port-ism — see
  // AI.ATTACK_REACTION_* in constants.ts): holding `attack` on every single frame in range
  // made two symmetric melee CPUs (matched range/timing) start their swings on the exact
  // same frame every cycle. The melee-active i-frame refresh (STATE.MELEE_IFRAME_REFRESH_
  // PER_FRAME, constants.ts) then kept each one invincible for the other's entire active
  // window, forever — verified via scripts/selfcheck-challenge-stages.mjs (st02/st04/st08/
  // st0b/st0c all locked two CPUs at ~52 units, cycling attack/special with hp never
  // moving). A per-uid-staggered reaction delay between swings desyncs the cycle so each
  // side's active window eventually lands on the other's vulnerable frames. The gate only
  // applies BETWEEN swings (attackLock <= 0); it never interrupts a swing/lunge already in
  // progress, and non-melee (pure shot) borgs are unaffected since they have no active-i-
  // frame refresh to desync.
  // Per-PAIR structural stagger, not just a per-uid hash: comparing uid against the current
  // target's uid gives one side of a symmetric matchup a short holdoff and the other a long
  // one, EVERY cycle — immune to the hash coincidentally re-syncing two borgs after a few
  // swings (a plain per-uid-only re-hash can drift back into phase once in a while, which
  // re-opens the same deadlock intermittently instead of fixing it for the whole fight).
  const pairOffset = self.uid < target.uid ? 0 : 1;
  const holdoffFrames =
    AI.ATTACK_REACTION_MIN_FRAMES +
    pairOffset * AI.ATTACK_REACTION_JITTER_FRAMES +
    Math.floor(hash01(self.uid) * AI.ATTACK_REACTION_MIN_FRAMES);

  let attackGated = false;
  if (inAttackWindow && meleeDef && (self.cooldowns["attackLock"] ?? 0) <= 0) {
    let holdoff = self.cooldowns["aiAttackHoldoff"];
    if (holdoff === undefined) {
      // First time this borg has been in range (or has re-entered it after losing/switching
      // target): arm the paired staggered delay instead of swinging immediately, so two CPUs
      // entering range on the same frame don't also swing on it.
      holdoff = holdoffFrames;
      self.cooldowns["aiAttackHoldoff"] = holdoff;
    }
    attackGated = holdoff > 0;
  } else {
    // Out of the melee window (or mid-swing/lunge): clear the holdoff so the next entry into
    // range re-arms a fresh staggered delay rather than reusing a stale one.
    delete self.cooldowns["aiAttackHoldoff"];
  }

  if (inAttackWindow && !attackGated) {
    input.attack = true;
    if (meleeDef) {
      // Re-arm the SAME paired stagger for the next swing — a fixed, structural offset (not
      // a fresh hash) so the desync holds for the whole fight instead of only until the hash
      // happens to land both borgs back in phase.
      self.cooldowns["aiAttackHoldoff"] = holdoffFrames;
    }
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

  // Hold-jump boost as a traversal option (movement.ts: UNIVERSAL as of 2026-07-04 — every
  // borg boosts by holding jump in the air while fuel remains, not only flyers). TUNED
  // port-ism: once airborne (from the hop above, a knockback launch, terrain, etc.) while
  // still well outside engage range, keep holding jump so the boost sustains the climb/glide
  // instead of immediately falling back to a walk — this gives ground-bound CPUs a second
  // traversal tool alongside the dash above for crossing the larger Challenge stages at the
  // slower DERIVED raw ground speed. Only engages with fuel remaining (movement.ts gates the
  // thrust on boostFuel itself; this just decides WHEN to ask for it) and never fights the
  // dash (dash is a ground-only burst in movement.ts, so the two never overlap).
  if (!self.grounded && farFromDesired && (self.cooldowns["boostFuel"] ?? 0) > 0) {
    input.jump = true;
  }

  return input;
}
