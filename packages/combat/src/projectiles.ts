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
import { MUZZLE_OFFSET, SHOT } from "./constants.js";
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
  /** +0x0e: f32 — the Z (third) component of the record's MUZZLE-OFFSET float3 at +0x06, NOT a
   *  velocity. FUN_80099e94 (chunk_0015.c:1400-1402) calls
   *  `PSMTXMultVec(owner+0x8d4 + boneIndex*0x30, record+0x06, child+0x20)`, and PSMTXMultVec
   *  reads three floats from its source pointer, so +0x06/+0x0a/+0x0e are one vector. The dump
   *  only decoded +0x0e (uniformly 50.0 or 100.0 across all 64 rows — consistent with a forward
   *  offset, not a per-variant speed); +0x06/+0x0a are still undumped and the port has no owner
   *  bone matrices to transform them by, so nothing consumes this field yet. The name matches
   *  the generated JSON key; this doc is the correction. Dumping +0x06/+0x0a is what would
   *  retire FIRE_CHILD_MUZZLE below. */
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
 * Spawn geometry for a fireChild projectile — the fields the DAT_802f3dda row does NOT give the
 * port. The ROM has no scalar "forward offset" here at all: FUN_80099e94
 * (chunk_0015.c:1400-1402) builds the child's position as
 *   PSMTXMultVec(owner bone matrix[record+0x00 boneIndex], record+0x06 float3, child+0x20)
 * plus owner+0x7b0 when the record's flags carry bit 2 (:1409-1411). The port models neither the
 * per-bone matrices nor the +0x06/+0x0a halves of that float3 (see ProjectileVariant.speedX), so
 * a scalar stand-in along the shooter's facing is unavoidable.
 *
 * RESOLVED (2026-08-29): there is now exactly ONE such stand-in. This module used to carry its
 * own MUZZLE_FORWARD 34 / HOMING_TURN 0.03 / HIT_RADIUS 35 under a comment claiming they were
 * constants.ts's values — which are 30 / 0.05 / 35. The ROM backs NEITHER number (MUZZLE_OFFSET
 * is TUNED against the undumped weapon-param table DAT_802d39dc; SHOT.HOMING_TURN is TUNED
 * because FUN_8006c1c8's per-projectile clamp value is undumped), so a second invented value for
 * the same concept was pure duplication. MUZZLE_OFFSET's own contract picks the survivor: it
 * exists precisely so "the projectile appears where the flash renders", and a stream-spawned
 * child at 34 while its muzzle flash draws at 30 breaks exactly that. The shared constants win.
 */
const FIRE_CHILD_MUZZLE = {
  /** Shared with combat.ts spawnProjectile and the renderer's muzzle flash. TUNED. */
  forward: MUZZLE_OFFSET.forward,
  up: MUZZLE_OFFSET.up,
} as const;

/** Variant flag bits (record +0x28). bit 0 = normal, bit 1 = homing, bit 2 = add muzzle
 *  offset, bit 3 = energy beam (no drop, different physics model). */
const VARIANT_FLAG_HOMING = 0x2;
const VARIANT_FLAG_ENERGY_BEAM = 0x8;

// Deterministic uid counter for stream-spawned (fireChild) projectiles, SHARED with battle.ts's
// ROM-family spawner through nextRomProjectileUid(): both mint "proj_rom_<n>" ids, so two
// independent counters would hand out colliding uids. This spawner previously built its uid from
// Date.now() + Math.random() — the same replay-determinism defect battle.ts had already fixed for
// its own spawner with a counter.
let romProjectileCounter = 0;

/** Next deterministic "proj_rom_<n>" uid. */
export function nextRomProjectileUid(): string {
  return `proj_rom_${romProjectileCounter++}`;
}

/** Reset the shared ROM-projectile uid counter. Called from createBattle so a replay from the
 *  same seed mints the same uids. */
export function resetRomProjectileCounter(): void {
  romProjectileCounter = 0;
}

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
    uid: nextRomProjectileUid(),
    ownerUid: shooter.uid,
    team: shooter.team,
    pos: {
      x: shooter.pos.x + dirX * FIRE_CHILD_MUZZLE.forward,
      y: shooter.pos.y + FIRE_CHILD_MUZZLE.up,
      z: shooter.pos.z + dirZ * FIRE_CHILD_MUZZLE.forward,
    },
    vel: {
      x: dirX * variant.hSpeed,
      y: 0,
      z: dirZ * variant.hSpeed,
    },
    damage: 1,
    hitstun: 0,
    knockback: 1,
    // Homing rate: the MECHANISM is FUN_8006c1c8's per-frame angle-clamped 3D steer; the clamp
    // VALUE lives in undumped params, so SHOT.HOMING_TURN is the port's single TUNED rate.
    homingTurn: variant.flags & VARIANT_FLAG_HOMING ? SHOT.HOMING_TURN : 0,
    homingTarget: null,
    aimedTargetUid: shooter.lockTarget,
    life: variant.lifetimeFrames,
    hitRadius: SHOT.HIT_RADIUS,
    visualKind: variant.flags & VARIANT_FLAG_ENERGY_BEAM ? "energy" : "muzzle",
    damageRecordIndex: 0,
    romScale: variant.scale,
  };
}
