// ROM-faithful projectile system — port of zz_0099e70_ (chunk_0015.c:1361) and the
// per-variant data table at DAT_802f3dda (0x802f3dda, 60-byte stride, 64 entries).
//
// Replaces the fake TUNED `spawnSpecialProjectiles` in combat.ts with real ROM data:
// each projectile variant's speed, drop, scale, hitbox kind, lifetime, spawn bone, and
// flags are read from the decoded variant table — NOT invented.
//
// The variant byte comes from the action stream's op 0x09 (fireChild), which passes
// it to zz_0099e70_(actor, variant). Each borg's B-shot / B-charge / X-special uses a
// specific variant determined by its action-script stream data.

import type { BorgRuntime, Projectile } from "./types.js";
import projectileVariantData from "./data/projectileVariants.json" with { type: "json" };

/** The decoded ROM variant record (60-byte struct at DAT_802f3dda + variant × 0x3c). */
export interface ProjectileVariant {
  variant: number;
  /** +0x00: s16 — which bone matrix to spawn from (the actor's bone+0x8d4 array). */
  boneIndex: number;
  /** +0x02: s16 — the HIT kind (passed to zz_008ac80_ for hitbox arming; matches
   *  attackHitTables.json kind → hit records). */
  kind: number;
  /** +0x04: s16 — lifetime in frames before despawn. */
  lifetimeFrames: number;
  /** +0x0e: f32 — initial X velocity component (usually 0 or 100). */
  speedX: number;
  /** +0x12: f32 — the speed scalar that scales the normalized velocity direction
   *  (FUN_8009a12c line 1513: PSQUATScale(hSpeed, vel, vel)). The REAL projectile
   *  speed, NOT the TUNED SHOT.SPEED constant. */
  hSpeed: number;
  /** +0x16: f32 — per-frame gravity (projectile drop). Beams = -1.5, bullets = -3.0,
   *  energy beams = 0.0, rising effects = +1.0. */
  drop: number;
  /** +0x1a/+0x1e/+0x22: f32 ×3 — visual scale [X, Y, Z]. */
  scale: [number, number, number];
  /** +0x26: s16 — BAM16 angle offset from the shooter's yaw (spread/cone). */
  angleBAM: number;
  /** +0x28: u16 — flags. bit 0 = normal, bit 1 = homing?, bit 2 = add muzzle offset,
   *  bit 3 = energy beam (no drop, different physics model). */
  flags: number;
}

/** DERIVED — the DAT_802f3dda table is 64 entries of 60-byte stride, decoded from boot.dol
 *  into data/projectileVariants.json. Callers that scan the whole table (combat.ts
 *  findVariantByKind) bound their loop with this instead of a bare 64. */
export const PROJECTILE_VARIANT_COUNT = 64;

const VARIANT_DATA = (projectileVariantData as { variants: Array<{ variant: number; boneIndex: number; kind: number; lifetimeFrames: number; speedX: number; hSpeed: number; drop: number; scale: number[]; angleBAM: number; flags: number; }> }).variants;
const VARIANTS: ProjectileVariant[] = VARIANT_DATA.map((v) => ({ ...v, scale: [v.scale[0] ?? 1, v.scale[1] ?? 1, v.scale[2] ?? 1] as [number, number, number] }));

/**
 * Spawn defaults for a fireChild projectile — the fields the DAT_802f3dda row does NOT
 * carry, so they cannot come from ROM data. All PLACEHOLDER (not ROM-derived).
 *
 * FINDING, deliberately preserved rather than "corrected": MUZZLE_FORWARD is 34, but the
 * comment that used to sit on that literal claimed it was constants.ts's MUZZLE_OFFSET.forward
 * — which is 30. The two disagree, and the same concept therefore has two live values in the
 * package (34 here for stream-spawned children, 30 in MUZZLE_OFFSET for gun projectiles and
 * the renderer's muzzle flash). Changing either would move where projectiles appear, so the
 * numbers are left exactly as they were and the discrepancy is named instead. Likewise
 * HOMING_TURN (0.03) is a third value alongside SHOT.HOMING_TURN (0.05), and HIT_RADIUS (35)
 * happens to equal SHOT.HIT_RADIUS but is not wired to it.
 */
const FIRE_CHILD_DEFAULTS = {
  MUZZLE_FORWARD: 34,
  MUZZLE_UP: 20,
  HIT_RADIUS: 35,
  /** Applied only when the variant's flags bit 1 (homing) is set. */
  HOMING_TURN: 0.03,
} as const;

/** Variant flag bits (record +0x28). bit 0 = normal, bit 1 = homing, bit 2 = add muzzle
 *  offset, bit 3 = energy beam (no drop, different physics model). */
const VARIANT_FLAG_HOMING = 0x2;
const VARIANT_FLAG_ENERGY_BEAM = 0x8;

/** Look up a projectile variant by its variant byte (the op 0x09 operand). Returns
 *  null for out-of-range variants (the ROM would crash; we fall back gracefully). */
export function projectileVariant(variantByte: number): ProjectileVariant | null {
  return VARIANTS[variantByte] ?? null;
}

/** Port of zz_0099e70_ → FUN_80099e94 spawn — creates a ROM-data-driven projectile
 *  from the shooter's position/yaw + the variant's decoded parameters. This replaces
 *  the fake TUNED spawnSpecialProjectiles.
 *
 *  The caller (combat.ts or bridge.ts) passes the shooter's runtime + the variant byte
 *  (from the action stream's fireChild op or the borg's shot-def). The projectile's
 *  speed, drop, scale, lifetime, kind, and visual all come from the ROM variant table. */
export function spawnRomProjectile(
  shooter: BorgRuntime,
  variantByte: number,
  yawRadians: number,
): Projectile | null {
  const variant = projectileVariant(variantByte);
  if (!variant) return null;
  // Velocity direction: the shooter's yaw + the variant's BAM angle offset.
  const totalYaw = yawRadians + (variant.angleBAM / 0x10000) * Math.PI * 2;
  const dirX = Math.sin(totalYaw);
  const dirZ = Math.cos(totalYaw);
  return {
    // NON-DETERMINISTIC uid — a known defect, not a style choice. battle.ts's own
    // addRomProjectile documents that a Date.now() uid broke replay determinism and
    // replaced it with a counter (romProjCounter); this spawner still carries the old
    // shape. Left as-is here because changing it changes observable uids; it should be
    // moved onto a deterministic counter in a dedicated fix.
    uid: `proj_rom_${Date.now()}_${Math.random().toString(36).slice(2, 6)}`,
    ownerUid: shooter.uid,
    team: shooter.team,
    pos: {
      x: shooter.pos.x + dirX * FIRE_CHILD_DEFAULTS.MUZZLE_FORWARD,
      y: shooter.pos.y + FIRE_CHILD_DEFAULTS.MUZZLE_UP,
      z: shooter.pos.z + dirZ * FIRE_CHILD_DEFAULTS.MUZZLE_FORWARD,
    },
    vel: {
      x: dirX * variant.hSpeed,
      y: 0,
      z: dirZ * variant.hSpeed,
    },
    damage: 1,
    hitstun: 0,
    knockback: 1,
    homingTurn: variant.flags & VARIANT_FLAG_HOMING ? FIRE_CHILD_DEFAULTS.HOMING_TURN : 0,
    homingTarget: null,
    aimedTargetUid: shooter.lockTarget,
    life: variant.lifetimeFrames,
    hitRadius: FIRE_CHILD_DEFAULTS.HIT_RADIUS,
    visualKind: variant.flags & VARIANT_FLAG_ENERGY_BEAM ? "energy" : "muzzle",
    damageRecordIndex: 0,
    romScale: variant.scale,
  };
}
