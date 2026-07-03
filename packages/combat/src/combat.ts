// Combat: lock-on, melee (B), ranged shot (B for ranged borgs), special (X), projectiles
// with homing, damage = f(attack/shot, defense), hitstun -> "hit", knockdown -> "down" ->
// wake with invincTimer=60 (the decomp countdown, ported exactly), cooldowns + ammo/reload.
//
// Invincibility port (behavior-notes.md s4a, struct+0x720): each frame, if timer>0 subtract
// 1.0 and clamp at 0. Entering the wake state sets it to 60. See stepInvincibility().

import {
  add,
  distXZ,
  floorSurfaceYAt,
  forwardFromYaw,
  knockbackDirectionFromPositions,
  normalize,
  scale,
  yawFromXZ,
  type Vec3,
} from "@gf/physics";
import {
  CHARGE,
  COMBO,
  DAMAGE,
  MELEE,
  LOCK,
  SHOT,
  SPECIAL,
  STATE,
  WAKE_UP_INVINCIBILITY_FRAMES,
} from "./constants.js";
import {
  actionProfileForProfile,
  type MeleeActionDef,
  type ShotActionDef,
  type SwordBeamDef,
} from "./actionProfiles.js";
import type { BorgProfile } from "./stats.js";
import { typeDamageMultiplier } from "./typeDamage.js";
import type {
  BorgRuntime,
  Projectile,
  ProjectileVisualKind,
  RectStageBounds,
  StageCollision,
} from "./types.js";
import projectileVisualFamilies from "./data/projectileVisualFamilies.json" with { type: "json" };

export interface ProjectileContext {
  bounds: RectStageBounds;
  collision: StageCollision | null;
}

// ---------------------------------------------------------------------------------------
// Invincibility timer — DIRECT PORT of the decompiled countdown (behavior-notes.md s4a).
// ---------------------------------------------------------------------------------------
export function stepInvincibility(b: BorgRuntime): void {
  if (b.invincTimer > 0) {
    b.invincTimer -= 1.0; // struct+0x1dcc ~= 1.0/frame
    if (b.invincTimer <= 0) b.invincTimer = 0;
  }
}

export function isInvincible(b: BorgRuntime): boolean {
  return b.invincTimer > 0;
}

// ---------------------------------------------------------------------------------------
// Cooldowns — tick every named cooldown down by 1 each frame.
// ---------------------------------------------------------------------------------------
export function stepCooldowns(b: BorgRuntime): void {
  for (const k of Object.keys(b.cooldowns)) {
    const v = b.cooldowns[k] ?? 0;
    // jumpHeld / switchLockHeld / allyLockHeld / attackHeld are 0/1 press latches,
    // boostFuel is a fuel gauge, chargeFrames is a hold-B charge accumulator, and
    // comboStep is the current melee-chain index — none are countdown timers; skip them here.
    if (
      k === "jumpHeld" ||
      k === "boostFuel" ||
      k === "switchLockHeld" ||
      k === "allyLockHeld" ||
      k === "attackHeld" ||
      k === "chargeFrames" ||
      k === "comboStep"
    )
      continue;
    if (v > 0) b.cooldowns[k] = v - 1;
  }
}

// ---------------------------------------------------------------------------------------
// Enemy lock-on (R switch-lock) and ally lock-on (Z).
//
// TUNED, and CHECKED CLOSED (2026-07-01, behavior-notes.md s4q): this is not a partially-derived
// stand-in awaiting a future decode — a thorough corpus search (borg state-machine dispatch,
// every writer of the 6-actor-table "last enemy" globals DAT_803b06a8/object+2000/+0x7d1,
// every loop over DAT_803c4e84, every PSVEC distance-check call site, PAD/SI input symbols) found
// no button-triggered scan-and-select enemy-lock mechanic anywhere in the ROM. Every "target"
// field the decomp has is hit-REACTIVE bookkeeping (remembers who last hit whom, for a one-shot
// reaction animation via react_to_slot_target_object/start_status_reaction_by_side), never a
// scan-selective player lock system. So there is no real algorithm to port here — this heuristic
// (nearest enemy in a forward view-cone, scored by distance*angle) is an honest design choice,
// not a guess standing in for a known-but-undecoded formula. Do not re-derive without new leads.
// ---------------------------------------------------------------------------------------
function isEnemyAlive(self: BorgRuntime, o: BorgRuntime): boolean {
  return o.alive && o.team !== self.team && o.uid !== self.uid;
}

function isAllyAlive(self: BorgRuntime, o: BorgRuntime): boolean {
  return o.alive && o.team === self.team && o.uid !== self.uid;
}

function canReceiveHit(self: BorgRuntime, o: BorgRuntime): boolean {
  return o.alive && o.uid !== self.uid;
}

function rawDamageForTarget(
  rawDamage: number,
  attackerTeam: number,
  targetTeam: number,
  attackerBorgId: string | undefined,
  defenderBorgId: string | undefined,
): number {
  const typeAdjusted = rawDamage * typeDamageMultiplier(attackerBorgId, defenderBorgId);
  return attackerTeam === targetTeam ? typeAdjusted / DAMAGE.SAME_TEAM_HIT_DIVISOR : typeAdjusted;
}

/** Acquire the nearest enemy that is in front (within the lock cone) and in range. */
export function acquireLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const fwd = forwardFromYaw(self.rotY);
  let best: string | null = null;
  let bestScore = Infinity;
  for (const o of all) {
    if (!isEnemyAlive(self, o)) continue;
    const d = distXZ(self.pos, o.pos);
    if (d > LOCK.RANGE) continue;
    const to = normalize({ x: o.pos.x - self.pos.x, y: 0, z: o.pos.z - self.pos.z });
    const dot = fwd.x * to.x + fwd.z * to.z;
    const ang = Math.acos(Math.max(-1, Math.min(1, dot)));
    if (ang > LOCK.CONE) continue;
    // Prefer closer + more-centered targets.
    const score = d * (1 + ang);
    if (score < bestScore) {
      bestScore = score;
      best = o.uid;
    }
  }
  return best;
}

/** Cycle to the next enemy by distance (R = switch lock-on target). Enemy-only by
 * construction (isEnemyAlive filters dead borgs, self, and same-team allies); the caller
 * (battle.ts) edge-triggers this so holding R does not re-cycle every frame. */
export function cycleLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const enemies = all
    .filter((o) => isEnemyAlive(self, o) && distXZ(self.pos, o.pos) <= LOCK.RANGE)
    .sort((a, b) => distXZ(self.pos, a.pos) - distXZ(self.pos, b.pos));
  if (enemies.length === 0) return null;
  const curIdx = enemies.findIndex((o) => o.uid === self.lockTarget);
  const next = enemies[(curIdx + 1) % enemies.length];
  return next ? next.uid : null;
}

/** Z ally-lock target selection. CONFIRMED-ASSET input, TUNED nearest-ally selection.
 * The original ally charge/power-up behavior is not decoded yet, so this only records a
 * same-team target for HUD/debug/future mechanics and never redirects enemy attacks. */
export function acquireAllyLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  let best: string | null = null;
  let bestDist = Infinity;
  for (const o of all) {
    if (!isAllyAlive(self, o)) continue;
    const d = distXZ(self.pos, o.pos);
    if (d > LOCK.RANGE || d >= bestDist) continue;
    bestDist = d;
    best = o.uid;
  }
  return best;
}

/** Cycle to the next same-team ally by distance (repeated Z presses). Ally-only by
 * construction (isAllyAlive filters dead borgs, self, and enemies). With no current
 * ally lock this selects the nearest ally, matching acquireAllyLock. TUNED — the
 * original per-press Z semantics are untraced; edge-triggering lives in battle.ts. */
export function cycleAllyLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const allies = all
    .filter((o) => isAllyAlive(self, o) && distXZ(self.pos, o.pos) <= LOCK.RANGE)
    .sort((a, b) => distXZ(self.pos, a.pos) - distXZ(self.pos, b.pos));
  if (allies.length === 0) return null;
  const curIdx = allies.findIndex((o) => o.uid === self.allyLockTarget);
  const next = allies[(curIdx + 1) % allies.length];
  return next ? next.uid : null;
}

// ---------------------------------------------------------------------------------------
// Damage application.
// mitigate(): DEF_PER_STAT/MIN_MULT are TUNED FROM STATS (no ROM formula recoverable yet).
// The subtract-then-clamp-at-0 shape below (victim.hp -= dmg; ...; victim.hp = 0) is DERIVED
// from the live trace at object+0x1C6 (behavior-notes.md s4h).
// Ghidra export re-read (behavior-notes.md s4m) shows object+0x88 is a match slot/team byte,
// not borgs.json's display type, so display type is intentionally not part of mitigation here.
// ---------------------------------------------------------------------------------------
function mitigate(raw: number, defenderDef: number): number {
  const mult = Math.max(DAMAGE.MIN_MULT, 1 - defenderDef * DAMAGE.DEF_PER_STAT);
  return Math.max(1, Math.round(raw * mult));
}

/**
 * Apply a hit to `victim`. Respects invincibility. Sets hitstun -> "hit", big hits or a
 * lethal blow route through knockdown -> "down" -> wake (60 i-frames). Returns dmg dealt.
 */
export function applyHit(
  victim: BorgRuntime,
  victimProfile: BorgProfile,
  rawDamage: number,
  knockback: number,
  knockDir: Vec3,
  fromPos: Vec3,
  forceKnockdown = false,
): number {
  if (!victim.alive || isInvincible(victim)) return 0;

  const dmg = mitigate(rawDamage, victimProfile.defense);
  victim.hp -= dmg;

  // Knockback DIRECTION — ROM-accurate port of zz_00300bc_ (0x800300bc), mode 1 ("attacker to
  // target" relative-position vector -> atan2 -> BAM16 yaw), the only one of the ROM's 5 vector-
  // source modes this port has enough data to compute (see packages/physics/src/knockback.ts
  // header and behavior-notes.md section (p) for the other 4 modes and why they're not wired).
  // `knockDir` lets a caller override with a more specific vector (e.g. a projectile's travel
  // direction) when the "attacker position" isn't the right source (fromPos is still passed as
  // the attacker-position input to the mode-1 calc either way).
  // Knockback MAGNITUDE remains a flat TUNED scalar (`knockback` param) — the ROM function only
  // ever computes/stores direction, never a speed/force value; see constants.ts MELEE/SHOT/SPECIAL.
  const dir =
    knockDir.x === 0 && knockDir.z === 0
      ? knockbackDirectionFromPositions(fromPos, victim.pos)
      : normalize(knockDir);
  victim.vel.x = dir.x * knockback;
  victim.vel.z = dir.z * knockback;
  if (knockback > 0) victim.vel.y = Math.max(victim.vel.y, knockback * 0.4);

  if (victim.hp <= 0) {
    victim.hp = 0;
    enterDeath(victim);
    return dmg;
  }

  const knockdown = forceKnockdown || dmg >= DAMAGE.KNOCKDOWN_DMG;
  if (knockdown) {
    enterDown(victim);
  } else {
    enterHit(victim, MELEE.HITSTUN);
  }
  return dmg;
}

export function enterHit(b: BorgRuntime, stun: number): void {
  b.state = "hit";
  b.stateTime = 0;
  b.anim = "hit";
  b.cooldowns["hitstun"] = stun;
}

export function enterDown(b: BorgRuntime): void {
  b.state = "down";
  b.stateTime = 0;
  b.anim = "down";
  b.grounded = false; // gets knocked off the ground; lands during down
}

export function enterDeath(b: BorgRuntime): void {
  b.state = "death";
  b.stateTime = 0;
  b.anim = "death";
  b.vel.x = 0;
  b.vel.z = 0;
}

/**
 * Advance the non-locomotion combat states (hit/down/death/spawn). Returns true when a
 * death state has fully elapsed (caller removes the borg + triggers next-deploy).
 */
export function stepActionState(b: BorgRuntime): { died: boolean } {
  switch (b.state) {
    case "hit": {
      const stun = b.cooldowns["hitstun"] ?? 0;
      if (stun <= 0) {
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "idle";
      }
      return { died: false };
    }
    case "down": {
      if (b.stateTime >= STATE.DOWN_DURATION && b.grounded) {
        // Wake up with the ported 60-frame invincibility.
        b.invincTimer = WAKE_UP_INVINCIBILITY_FRAMES;
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "wake";
      }
      return { died: false };
    }
    case "death": {
      if (b.stateTime >= STATE.DEATH_DURATION) {
        b.alive = false;
        return { died: true };
      }
      return { died: false };
    }
    case "spawn": {
      if (b.stateTime >= STATE.SPAWN_DURATION) {
        b.state = "idle";
        b.stateTime = 0;
        b.anim = "idle";
      }
      return { died: false };
    }
    default:
      return { died: false };
  }
}

/** True while the borg is locked out of acting (hit/down/death/spawn). */
export function isBusy(b: BorgRuntime): boolean {
  return (
    b.state === "hit" ||
    b.state === "down" ||
    b.state === "death" ||
    b.state === "spawn"
  );
}

// ---------------------------------------------------------------------------------------
// Attacks. Returns a (possibly empty) list of projectiles spawned this frame.
// ---------------------------------------------------------------------------------------
export interface AttackResult {
  projectiles: Projectile[];
}

let projCounter = 0;
export function resetProjectileCounter(): void {
  projCounter = 0;
}

// Per-borg family table generated from research/asset-inventory/weapon-attachment-map.json
// (scripts/gen-projectile-visual-families.mjs) — see that JSON's own "note" field and
// behavior-notes.md s4t for the full citation. TUNED, but backed by real per-borg PZZ/model/
// mot asset-family evidence (fire/beam/gun/bulletProjectile/muzzle signals, weighted by
// confidence) instead of an English name-string match. No ROM-side per-move effect/particle-ID
// field has been decoded (hit-bin-format.md's 0xF4 records and the puVar17 per-move fields
// documented in behavior-notes.md s4j/s4o/s4p are all damage/knockback fields, not visual-asset
// IDs), so this remains explicitly TUNED, not DERIVED.
const VISUAL_FAMILY_BY_BORG_ID: Readonly<Record<string, ProjectileVisualKind>> =
  projectileVisualFamilies.kinds as Record<string, ProjectileVisualKind>;

/**
 * Resolve a projectile's visual kind for a borg. Prefers the asset-family table above (real,
 * per-borg asset-inventory evidence); falls back to the original name-string heuristic only for
 * the ~half of the roster with no confident family signal in that table. Both paths are TUNED —
 * see the comment above and constants.ts's DERIVED/TUNED header for why neither can be labeled
 * DERIVED yet.
 */
export function projectileVisualKindForProfile(p: BorgProfile): ProjectileVisualKind {
  const fromAssets = VISUAL_FAMILY_BY_BORG_ID[p.id];
  if (fromAssets) return fromAssets;
  // LAST-RESORT fallback: no real per-borg asset-family signal found for this id.
  const text = `${p.id} ${p.name}`.toLowerCase();
  if (/(flame|fire|phoenix|dragon)/.test(text)) return "flame";
  if (/(beam|laser|plasma|satellite|bit)/.test(text)) return "energy";
  if (/(gun|gatling|revolver|rifle|cannon|tank|machine|bullet|missile|launcher)/.test(text)) return "muzzle";
  return "energy";
}

/**
 * Process B (attack) and Y (special) for one borg. Mutates `b` (state, cooldowns, ammo) and
 * resolves melee hits immediately against `all`. Ranged borgs spawn projectiles.
 *
 * `attackHeld` is the button's HELD state each frame (adapter/AI pass held booleans);
 * press/release edges are detected internally via the `attackHeld` cooldown latch. Three
 * profile-driven mechanics hang off it (all with generic fallbacks, all TUNED — see
 * constants.ts COMBO/CHARGE and actionProfiles.json's note):
 *   - Melee combo chains: borgs with comboHits > 1 chain follow-up swings when attack is
 *     pressed (or still held) within comboWindowFrames after a swing's recovery. Chained
 *     swings bypass the melee cooldown, start up faster, ramp damage, and the final hit
 *     forces a knockdown.
 *   - Charge shots: borgs with shot.chargeable accumulate chargeFrames while attack is held
 *     (capped at chargeTier2Frames) and fire on RELEASE, scaled by the reached tier.
 *     Non-chargeable shooters keep the fire-while-held autofire behavior.
 *   - Sword beams: borgs with melee.swordBeam emit a fast short-lived projectile on the
 *     combo finisher's first active frame, damage scaled from the MELEE formula.
 */
export function stepAttacks(
  b: BorgRuntime,
  p: BorgProfile,
  attackHeld: boolean,
  pressedSpecial: boolean,
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
): AttackResult {
  const out: Projectile[] = [];
  if (isBusy(b) || !b.alive) return { projectiles: out };
  const actionProfile = actionProfileForProfile(p);
  const meleeDef = actionProfile.melee;
  const shotDef = actionProfile.shot;

  // Press/release edge detection for the attack button (latch survives across frames).
  const prevAttackHeld = (b.cooldowns["attackHeld"] ?? 0) > 0;
  b.cooldowns["attackHeld"] = attackHeld ? 1 : 0;
  const releasedAttack = !attackHeld && prevAttackHeld;

  // Drop the combo chain once its window lapses.
  if ((b.cooldowns["comboWindow"] ?? 0) <= 0) b.cooldowns["comboStep"] = 0;

  // Reload bookkeeping for ranged.
  if (shotDef) {
    const reload = b.cooldowns["reload"] ?? 0;
    if (b.ammo <= 0 && reload <= 0) {
      b.ammo = shotDef.ammoMax;
    }
  }

  // --- Special (X) -------------------------------------------------------------------
  const canStartAction = b.state !== "attack" && b.state !== "special";
  if (canStartAction && pressedSpecial && (b.cooldowns["special"] ?? 0) <= 0) {
    const specialDef = actionProfile.special;
    b.cooldowns["special"] = specialDef.cooldown;
    b.cooldowns["attackLock"] = specialDef.duration;
    b.state = "special";
    b.stateTime = 0;
    b.anim = "special";
    // AoE burst around the borg.
    const baseDmg =
      (p.hasMelee ? MELEE.DMG_BASE + p.attack * MELEE.DMG_PER_STAT : SHOT.DMG_BASE + p.shot * SHOT.DMG_PER_STAT) *
      specialDef.damageMultiplier;
    for (const o of all) {
      if (!canReceiveHit(b, o)) continue;
      if (distXZ(b.pos, o.pos) <= specialDef.radius) {
        const op = profiles.get(o.uid);
        if (op) {
          // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target,
          // via the ported zz_00300bc_ atan2/BAM16 calc) instead of this raw un-ported subtract.
          applyHit(
            o,
            op,
            rawDamageForTarget(baseDmg, b.team, o.team, p.id, op.id),
            SPECIAL.KNOCKBACK * specialDef.knockbackMultiplier,
            { x: 0, y: 0, z: 0 },
            b.pos,
            true,
          );
        }
      }
    }
    return { projectiles: out };
  }

  // --- Attack (B): asset-backed per-borg primary action, generic fallback-safe -------
  if (canStartAction && (attackHeld || releasedAttack)) {
    const order =
      actionProfile.primary === "shot"
        ? (["shot", "melee"] as const)
        : (["melee", "shot"] as const);
    for (const kind of order) {
      if (kind === "melee" && meleeDef && attackHeld) {
        const window = b.cooldowns["comboWindow"] ?? 0;
        const prevStep = b.cooldowns["comboStep"] ?? 0;
        // Chain: within the combo window and more hits remain — bypass the melee cooldown.
        const canChain = window > 0 && prevStep + 1 < meleeDef.comboHits;
        const canFresh = (b.cooldowns["melee"] ?? 0) <= 0;
        if (canChain || canFresh) {
          startMeleeAttack(b, meleeDef, canChain ? prevStep + 1 : 0);
          break;
        }
        continue; // melee gated — a hybrid may still fire its gun below
      }
      if (kind === "shot" && shotDef && (b.cooldowns["shot"] ?? 0) <= 0 && b.ammo > 0) {
        if (shotDef.chargeable) {
          if (attackHeld) {
            // Hold-to-charge: accumulate (capped) and consume the button for this frame.
            b.cooldowns["chargeFrames"] = Math.min(
              shotDef.chargeTier2Frames,
              (b.cooldowns["chargeFrames"] ?? 0) + 1,
            );
            break;
          }
          if (releasedAttack && (b.cooldowns["chargeFrames"] ?? 0) > 0) {
            const frames = b.cooldowns["chargeFrames"] ?? 0;
            b.cooldowns["chargeFrames"] = 0;
            const tier = frames >= shotDef.chargeTier2Frames ? 2 : frames >= shotDef.chargeTier1Frames ? 1 : 0;
            startShotAttack(b, p, shotDef, tier, out);
            break;
          }
          continue;
        }
        if (attackHeld) {
          startShotAttack(b, p, shotDef, 0, out);
          break;
        }
      }
    }
  }

  // --- Resolve an active melee swing against enemies in reach ------------------------
  const meleeActive = b.cooldowns["meleeActive"] ?? 0;
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && STATE.MELEE_IFRAME_REFRESH_PER_FRAME) {
    b.invincTimer = WAKE_UP_INVINCIBILITY_FRAMES;
  }
  if (b.state === "attack" && b.anim === "melee" && meleeDef && meleeActive > 0 && meleeActive <= meleeDef.active) {
    const comboStep = b.cooldowns["comboStep"] ?? 0;
    const isFinisher = comboStep >= meleeDef.comboHits - 1;
    // Sword beam: the combo finisher's FIRST active frame emits a fast short-lived projectile
    // with melee-scaled damage (TUNED design; see actionProfiles.ts SwordBeamDef).
    if (meleeDef.swordBeam && isFinisher && meleeActive === meleeDef.active) {
      out.push(spawnSwordBeam(b, p, meleeDef, meleeDef.swordBeam));
    }
    // Only the active window (after startup) deals damage; one hit per swing per target.
    const fwd = forwardFromYaw(b.rotY);
    const stepMult =
      COMBO.STEP_DAMAGE_MULT[Math.min(comboStep, COMBO.STEP_DAMAGE_MULT.length - 1)] ?? 1;
    for (const o of all) {
      if (!canReceiveHit(b, o)) continue;
      // One hit per swing per target: skip anyone this swing already struck. (This enforces
      // the long-documented contract; previously the active window re-applied damage every
      // frame, silently multiplying melee damage by the active-frame count.)
      if (b.meleeHitUids?.includes(o.uid)) continue;
      const d = distXZ(b.pos, o.pos);
      if (d > meleeDef.range) continue;
      if (Math.abs(o.pos.y - b.pos.y) > meleeDef.yTolerance) continue;
      const to = normalize({ x: o.pos.x - b.pos.x, y: 0, z: o.pos.z - b.pos.z });
      if (fwd.x * to.x + fwd.z * to.z < 0) continue; // behind us
      const op = profiles.get(o.uid);
      if (!op) continue;
      const raw = (MELEE.DMG_BASE + p.attack * MELEE.DMG_PER_STAT) * meleeDef.damageMultiplier * stepMult;
      const knockbackMult =
        meleeDef.knockbackMultiplier * (isFinisher && meleeDef.comboHits > 1 ? COMBO.FINISHER_KNOCKBACK_MULT : 1);
      // Zero vector -> applyHit() computes the real ROM-mode-1 direction (attacker->target)
      // instead of the attacker's facing vector (`fwd`) used here previously.
      const dealt = applyHit(
        o,
        op,
        rawDamageForTarget(raw, b.team, o.team, p.id, op.id),
        MELEE.KNOCKBACK * knockbackMult,
        { x: 0, y: 0, z: 0 },
        b.pos,
        // A multi-hit chain's finisher launches: forced knockdown (TUNED game-feel choice).
        isFinisher && meleeDef.comboHits > 1,
      );
      if (dealt > 0) (b.meleeHitUids ??= []).push(o.uid);
    }
  }

  // Return to idle when the attack animation finishes.
  if (b.state === "attack" && (b.cooldowns["attackLock"] ?? 0) <= 0) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }
  if (b.state === "special" && (b.cooldowns["attackLock"] ?? 0) <= 0) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }

  return { projectiles: out };
}

function startMeleeAttack(b: BorgRuntime, meleeDef: MeleeActionDef, comboStep: number): void {
  // Chained swings come out faster (COMBO.STEP_STARTUP_SCALE); the opener uses full startup.
  const startup =
    comboStep > 0 ? Math.max(2, Math.round(meleeDef.startup * COMBO.STEP_STARTUP_SCALE)) : meleeDef.startup;
  b.cooldowns["melee"] = meleeDef.duration + meleeDef.cooldown;
  b.cooldowns["meleeActive"] = startup + meleeDef.active;
  b.cooldowns["attackLock"] = meleeDef.duration;
  // The chain window covers this swing plus a grace period after its recovery. The renderer
  // alternates melee/melee_alt banks on each melee re-entry (battleScene meleeParity), and the
  // >=1 idle frame between chained swings is what lets it see the re-entry.
  b.cooldowns["comboWindow"] = meleeDef.duration + meleeDef.comboWindowFrames;
  b.cooldowns["comboStep"] = comboStep;
  b.meleeHitUids = []; // fresh swing: everyone is hittable once again
  b.state = "attack";
  b.stateTime = 0;
  b.anim = "melee";
}

/** Fire a (possibly charge-scaled) shot: consumes ammo, sets cooldowns/anim, spawns projectiles.
 *  chargeTier 0 = normal shot; tiers 1/2 scale damage per-profile and speed/radius/hitstun/
 *  knockback via the TUNED CHARGE constants. */
function startShotAttack(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  chargeTier: number,
  out: Projectile[],
): void {
  b.cooldowns["shot"] = shotDef.cooldown;
  b.ammo -= 1;
  if (b.ammo <= 0) b.cooldowns["reload"] = shotDef.reloadFrames;
  b.cooldowns["attackLock"] = shotDef.recovery;
  b.state = "attack";
  b.stateTime = 0;
  b.anim = "shoot";
  out.push(...spawnProjectiles(b, p, shotDef, chargeTier));
}

/** Per-tier charge scaling (tier 0 = all 1x). Damage mults come from the profile; the rest
 *  from the TUNED CHARGE constants. */
function chargeScaling(shotDef: ShotActionDef, tier: number): {
  damage: number;
  speed: number;
  radius: number;
  hitstun: number;
  knockback: number;
} {
  if (tier >= 2) {
    return {
      damage: shotDef.chargeTier2DamageMult,
      speed: CHARGE.TIER2_SPEED_MULT,
      radius: CHARGE.TIER2_RADIUS_MULT,
      hitstun: CHARGE.TIER2_HITSTUN_MULT,
      knockback: CHARGE.TIER2_KNOCKBACK_MULT,
    };
  }
  if (tier === 1) {
    return {
      damage: shotDef.chargeTier1DamageMult,
      speed: CHARGE.TIER1_SPEED_MULT,
      radius: CHARGE.TIER1_RADIUS_MULT,
      hitstun: CHARGE.TIER1_HITSTUN_MULT,
      knockback: CHARGE.TIER1_KNOCKBACK_MULT,
    };
  }
  return { damage: 1, speed: 1, radius: 1, hitstun: 1, knockback: 1 };
}

function spawnProjectiles(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  chargeTier = 0,
): Projectile[] {
  const count = Math.max(1, Math.floor(shotDef.projectileCount));
  const projectiles: Projectile[] = [];
  for (let i = 0; i < count; i += 1) {
    const centered = count === 1 ? 0 : i - (count - 1) / 2;
    projectiles.push(spawnProjectile(b, p, shotDef, centered * shotDef.spreadRadians, chargeTier));
  }
  return projectiles;
}

function spawnProjectile(
  b: BorgRuntime,
  p: BorgProfile,
  shotDef: ShotActionDef,
  yawOffset: number,
  chargeTier = 0,
): Projectile {
  const yaw = b.rotY + yawOffset;
  const fwd = { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) };
  const tier = chargeScaling(shotDef, chargeTier);
  const raw = (SHOT.DMG_BASE + p.shot * SHOT.DMG_PER_STAT) * shotDef.damageMultiplier * tier.damage;
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: {
      x: b.pos.x + fwd.x * shotDef.muzzleForwardOffset,
      y: b.pos.y + shotDef.muzzleYOffset,
      z: b.pos.z + fwd.z * shotDef.muzzleForwardOffset,
    },
    vel: scale(fwd, shotDef.speed * tier.speed),
    damage: raw,
    hitstun: Math.max(1, Math.round(SHOT.HITSTUN * shotDef.hitstunMultiplier * tier.hitstun)),
    knockback: SHOT.KNOCKBACK * shotDef.knockbackMultiplier * tier.knockback,
    homingTurn: shotDef.homingTurn,
    homingTarget: b.lockTarget,
    life: shotDef.lifetime,
    hitRadius: shotDef.hitRadius * tier.radius,
    visualKind: shotDef.visualKind ?? projectileVisualKindForProfile(p),
    ...(shotDef.bulletDrop > 0 ? { drop: shotDef.bulletDrop } : {}),
  };
}

/** Combo-finisher sword beam: fast, short-lived, damage scaled off the MELEE damage formula
 *  (attack stat), not the shot stat — this is the sword swing "extending", not a gun. */
function spawnSwordBeam(
  b: BorgRuntime,
  p: BorgProfile,
  meleeDef: MeleeActionDef,
  beam: SwordBeamDef,
): Projectile {
  const fwd = forwardFromYaw(b.rotY);
  const raw = (MELEE.DMG_BASE + p.attack * MELEE.DMG_PER_STAT) * meleeDef.damageMultiplier * beam.damageMultiplier;
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: {
      x: b.pos.x + fwd.x * 40,
      y: b.pos.y + 20,
      z: b.pos.z + fwd.z * 40,
    },
    vel: scale(fwd, beam.speed),
    damage: raw,
    hitstun: SHOT.HITSTUN,
    knockback: SHOT.KNOCKBACK * meleeDef.knockbackMultiplier,
    homingTurn: beam.homingTurn,
    homingTarget: b.lockTarget,
    life: beam.lifetime,
    hitRadius: beam.hitRadius,
    visualKind: beam.visualKind,
  };
}

// ---------------------------------------------------------------------------------------
// Projectiles — advance, home toward target, resolve hits. Returns survivors.
// ---------------------------------------------------------------------------------------
export function stepProjectiles(
  projectiles: Projectile[],
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
  byUid: Map<string, BorgRuntime>,
  ctx?: ProjectileContext,
): Projectile[] {
  const survivors: Projectile[] = [];
  for (const pr of projectiles) {
    pr.life -= 1;
    if (pr.life <= 0) continue;

    // Homing toward the locked target.
    if (pr.homingTarget) {
      const tgt = byUid.get(pr.homingTarget);
      if (tgt && tgt.alive) {
        const desired = yawFromXZ(tgt.pos.x - pr.pos.x, tgt.pos.z - pr.pos.z);
        const cur = yawFromXZ(pr.vel.x, pr.vel.z);
        let d = desired - cur;
        while (d > Math.PI) d -= Math.PI * 2;
        while (d < -Math.PI) d += Math.PI * 2;
        const step = Math.max(-pr.homingTurn, Math.min(pr.homingTurn, d));
        const newYaw = cur + step;
        const speed = Math.hypot(pr.vel.x, pr.vel.z) || SHOT.SPEED;
        pr.vel = { x: Math.sin(newYaw) * speed, y: pr.vel.y, z: Math.cos(newYaw) * speed };
      }
    }

    // Ballistic drop for bullet-kind projectiles (profile-driven; 0/absent for beams/flames).
    if (pr.drop) pr.vel.y -= pr.drop;

    pr.pos = add(pr.pos, pr.vel as Vec3);
    if (ctx && !projectileInPlayArea(pr, ctx)) continue;

    // Hit test against any non-owner borg. Same-team hits use the derived 0.25x reducer.
    let consumed = false;
    for (const o of all) {
      if (!o.alive || o.uid === pr.ownerUid) continue;
      if (isInvincible(o)) continue;
      if (distXZ(pr.pos, o.pos) <= pr.hitRadius && Math.abs(pr.pos.y - o.pos.y) <= 60) {
        const op = profiles.get(o.uid);
        if (op) {
          // Intentionally NOT the zero-vector convention: a projectile's own travel vector
          // (which may have curved via homing) is a more accurate knockback direction than
          // recomputing the ROM's mode-1 attacker->target vector from a possibly-stale shooter
          // origin. Neither is a ROM-confirmed mode for the projectile case specifically (the
          // ROM caller always passes the same hit-context wrapper regardless of melee/shot), so
          // this remains a TUNED choice between two reasonable direction sources.
          const attackerProfile = profiles.get(pr.ownerUid);
          applyHit(
            o,
            op,
            rawDamageForTarget(pr.damage, pr.team, o.team, attackerProfile?.id, op.id),
            pr.knockback,
            pr.vel as Vec3,
            pr.pos,
          );
        }
        consumed = true;
        break;
      }
    }
    if (!consumed) survivors.push(pr);
  }
  return survivors;
}

function projectileInPlayArea(projectile: Projectile, ctx: ProjectileContext): boolean {
  const { pos } = projectile;
  if (pos.x < ctx.bounds.minX || pos.x > ctx.bounds.maxX || pos.z < ctx.bounds.minZ || pos.z > ctx.bounds.maxZ) {
    return false;
  }
  if (!ctx.collision || ctx.collision.triangles.length === 0) return true;
  return floorSurfaceYAt(ctx.collision, pos.x, pos.z, pos.y) != null;
}

