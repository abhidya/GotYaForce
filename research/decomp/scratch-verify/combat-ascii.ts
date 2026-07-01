// Combat: lock-on, melee (B), ranged shot (B for ranged borgs), special (Y), projectiles
// with homing, damage = f(attack/shot, defense), hitstun -> "hit", knockdown -> "down" ->
// wake with invincTimer=60 (the decomp countdown, ported exactly), cooldowns + ammo/reload.
//
// Invincibility port (behavior-notes.md s4a, struct+0x720): each frame, if timer>0 subtract
// 1.0 and clamp at 0. Entering the wake state sets it to 60. See stepInvincibility().

import {
  add,
  distXZ,
  forwardFromYaw,
  knockbackDirectionFromPositions,
  normalize,
  scale,
  yawFromXZ,
  type Vec3,
} from "@gf/physics";
import {
  DAMAGE,
  LOCK,
  MELEE,
  SHOT,
  SPECIAL,
  STATE,
  WAKE_UP_INVINCIBILITY_FRAMES,
} from "./constants.js";
import type { BorgProfile } from "./stats.js";
import type { BorgRuntime, Projectile, ProjectileVisualKind } from "./types.js";

// ---------------------------------------------------------------------------------------
// Invincibility timer -- DIRECT PORT of the decompiled countdown (behavior-notes.md s4a).
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
// Cooldowns -- tick every named cooldown down by 1 each frame.
// ---------------------------------------------------------------------------------------
export function stepCooldowns(b: BorgRuntime): void {
  for (const k of Object.keys(b.cooldowns)) {
    const v = b.cooldowns[k] ?? 0;
    // jumpHeld / boostFuel are latches/fuel, not countdown timers -- skip them here.
    if (k === "jumpHeld" || k === "boostFuel") continue;
    if (v > 0) b.cooldowns[k] = v - 1;
  }
}

// ---------------------------------------------------------------------------------------
// Lock-on (R) and switch-lock (Z).
// ---------------------------------------------------------------------------------------
function isEnemyAlive(self: BorgRuntime, o: BorgRuntime): boolean {
  return o.alive && o.team !== self.team && o.uid !== self.uid;
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

/** Cycle to the next enemy by distance (Z = switch lock-on target). */
export function cycleLock(self: BorgRuntime, all: BorgRuntime[]): string | null {
  const enemies = all
    .filter((o) => isEnemyAlive(self, o) && distXZ(self.pos, o.pos) <= LOCK.RANGE)
    .sort((a, b) => distXZ(self.pos, a.pos) - distXZ(self.pos, b.pos));
  if (enemies.length === 0) return null;
  const curIdx = enemies.findIndex((o) => o.uid === self.lockTarget);
  const next = enemies[(curIdx + 1) % enemies.length];
  return next ? next.uid : null;
}

// ---------------------------------------------------------------------------------------
// Damage application.
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

export function projectileVisualKindForProfile(p: BorgProfile): ProjectileVisualKind {
  const text = `${p.id} ${p.name}`.toLowerCase();
  if (/(flame|fire|phoenix|dragon)/.test(text)) return "flame";
  if (/(beam|laser|plasma|satellite|bit)/.test(text)) return "energy";
  if (/(gun|gatling|revolver|rifle|cannon|tank|machine|bullet|missile|launcher)/.test(text)) return "muzzle";
  return "energy";
}

/**
 * Process B (attack) and Y (special) for one borg. Mutates `b` (state, cooldowns, ammo) and
 * resolves melee hits immediately against `all`. Ranged borgs spawn projectiles.
 */
export function stepAttacks(
  b: BorgRuntime,
  p: BorgProfile,
  pressedAttack: boolean,
  pressedSpecial: boolean,
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
): AttackResult {
  const out: Projectile[] = [];
  if (isBusy(b) || !b.alive) return { projectiles: out };

  if (p.hasShot) {
    const reload = b.cooldowns["reload"] ?? 0;
    if (b.ammo <= 0 && reload <= 0) {
      b.ammo = SHOT.AMMO_MAX;
    }
  }

  if (pressedSpecial && (b.cooldowns["special"] ?? 0) <= 0) {
    b.cooldowns["special"] = SPECIAL.COOLDOWN;
    b.state = "special";
    b.stateTime = 0;
    b.anim = "special";
    const baseDmg =
      (p.hasMelee ? MELEE.DMG_BASE + p.attack * MELEE.DMG_PER_STAT : SHOT.DMG_BASE + p.shot * SHOT.DMG_PER_STAT) *
      SPECIAL.DMG_MULT;
    for (const o of all) {
      if (!isEnemyAlive(b, o)) continue;
      if (distXZ(b.pos, o.pos) <= SPECIAL.RADIUS) {
        const op = profiles.get(o.uid);
        if (op) {
          applyHit(o, op, baseDmg, SPECIAL.KNOCKBACK, { x: 0, y: 0, z: 0 }, b.pos, true);
        }
      }
    }
    return { projectiles: out };
  }

  if (pressedAttack) {
    if (p.hasMelee && (b.cooldowns["melee"] ?? 0) <= 0) {
      b.cooldowns["melee"] = MELEE.DURATION + MELEE.COOLDOWN;
      b.cooldowns["meleeActive"] = MELEE.STARTUP + MELEE.ACTIVE;
      b.state = "attack";
      b.stateTime = 0;
      b.anim = "melee";
    } else if (p.hasShot && (b.cooldowns["shot"] ?? 0) <= 0 && b.ammo > 0) {
      b.cooldowns["shot"] = SHOT.FIRE_COOLDOWN;
      b.ammo -= 1;
      if (b.ammo <= 0) b.cooldowns["reload"] = SHOT.RELOAD_FRAMES;
      b.state = "attack";
      b.stateTime = 0;
      b.anim = "shoot";
      out.push(spawnProjectile(b, p));
    }
  }

  const meleeActive = b.cooldowns["meleeActive"] ?? 0;
  if (b.state === "attack" && p.hasMelee && meleeActive > 0 && meleeActive <= MELEE.ACTIVE) {
    const fwd = forwardFromYaw(b.rotY);
    for (const o of all) {
      if (!isEnemyAlive(b, o)) continue;
      const d = distXZ(b.pos, o.pos);
      if (d > MELEE.RANGE) continue;
      if (Math.abs(o.pos.y - b.pos.y) > MELEE.Y_TOLERANCE) continue;
      const to = normalize({ x: o.pos.x - b.pos.x, y: 0, z: o.pos.z - b.pos.z });
      if (fwd.x * to.x + fwd.z * to.z < 0) continue;
      const op = profiles.get(o.uid);
      if (!op) continue;
      const raw = MELEE.DMG_BASE + p.attack * MELEE.DMG_PER_STAT;
      applyHit(o, op, raw, MELEE.KNOCKBACK, { x: 0, y: 0, z: 0 }, b.pos);
    }
  }

  if (b.state === "attack" && b.stateTime >= MELEE.DURATION) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }
  if (b.state === "special" && b.stateTime >= SPECIAL.DURATION) {
    b.state = "idle";
    b.stateTime = 0;
    b.anim = "idle";
  }

  return { projectiles: out };
}

function spawnProjectile(b: BorgRuntime, p: BorgProfile): Projectile {
  const fwd = forwardFromYaw(b.rotY);
  const raw = SHOT.DMG_BASE + p.shot * SHOT.DMG_PER_STAT;
  return {
    uid: `proj_${projCounter++}`,
    ownerUid: b.uid,
    team: b.team,
    pos: { x: b.pos.x + fwd.x * 30, y: b.pos.y + 20, z: b.pos.z + fwd.z * 30 },
    vel: scale(fwd, SHOT.SPEED),
    damage: raw,
    hitstun: SHOT.HITSTUN,
    knockback: SHOT.KNOCKBACK,
    homingTarget: b.lockTarget,
    life: SHOT.LIFETIME,
    hitRadius: SHOT.HIT_RADIUS,
    visualKind: projectileVisualKindForProfile(p),
  };
}

// ---------------------------------------------------------------------------------------
// Projectiles -- advance, home toward target, resolve hits. Returns survivors.
// ---------------------------------------------------------------------------------------
export function stepProjectiles(
  projectiles: Projectile[],
  all: BorgRuntime[],
  profiles: Map<string, BorgProfile>,
  byUid: Map<string, BorgRuntime>,
): Projectile[] {
  const survivors: Projectile[] = [];
  for (const pr of projectiles) {
    pr.life -= 1;
    if (pr.life <= 0) continue;

    if (pr.homingTarget) {
      const tgt = byUid.get(pr.homingTarget);
      if (tgt && tgt.alive) {
        const desired = yawFromXZ(tgt.pos.x - pr.pos.x, tgt.pos.z - pr.pos.z);
        const cur = yawFromXZ(pr.vel.x, pr.vel.z);
        let d = desired - cur;
        while (d > Math.PI) d -= Math.PI * 2;
        while (d < -Math.PI) d += Math.PI * 2;
        const step = Math.max(-SHOT.HOMING_TURN, Math.min(SHOT.HOMING_TURN, d));
        const newYaw = cur + step;
        pr.vel = { x: Math.sin(newYaw) * SHOT.SPEED, y: pr.vel.y, z: Math.cos(newYaw) * SHOT.SPEED };
      }
    }

    pr.pos = add(pr.pos, pr.vel as Vec3);

    let consumed = false;
    for (const o of all) {
      if (!o.alive || o.team === pr.team || o.uid === pr.ownerUid) continue;
      if (isInvincible(o)) continue;
      if (distXZ(pr.pos, o.pos) <= pr.hitRadius && Math.abs(pr.pos.y - o.pos.y) <= 60) {
        const op = profiles.get(o.uid);
        if (op) {
          applyHit(o, op, pr.damage, pr.knockback, pr.vel as Vec3, pr.pos);
        }
        consumed = true;
        break;
      }
    }
    if (!consumed) survivors.push(pr);
  }
  return survivors;
}
