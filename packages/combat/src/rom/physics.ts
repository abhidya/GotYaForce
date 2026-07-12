// ROM-faithful physics + motion integration — 1:1 port of GG4E engine functions.
//
// Source: `research/decomp/ghidra-export/chunk_0008.c`, functions FUN_80067310 (the
// primary integrator every family handler calls) and its variants. The scalar speed
// model (hSpeed + yVel + decel + gravityCoeff) is faithfully preserved; the existing
// @gf/combat movement.ts vec3-velocity model is NOT used by this runtime.
//
// Constant source: `user-data/GG4E/disc/sys/boot.dol` (read via research/decomp/dol.py).

import type { RomActor, Vec3 } from "./actor.js";

// Decoded from boot.dol this session (see action-vm-and-gcrash-decode-2026-07-05.md).
export const ROM_FLOAT = {
  /** 0x804375d0: minimum hSpeed clamp (FUN_80067310:3806, 3843). */
  H_SPEED_FLOOR: 0.0,
  /** 0x804375f0: terminal fall velocity for flying actors (FUN_80067310:3823). */
  FLY_FALL: 0.0,
  /** 0x804375f4: squared-magnitude threshold below which FUN_80067610 skips (line 3921). */
  DRIFT_EPSILON_SQ: 0.0,
} as const;

// Sin/cos of a BAM16 yaw — port of zz_0045204_ / zz_0045238_ (chunk_0006.c). The ROM
// stores yaws as s16 BAM (0..0xFFFF = 0..2π). Convention (verified against the ram-trace
// "yaw 0 faces +Z" anchor + FUN_80067310's axis assignment):
//   zz_0045204_(yaw) writes to pos.X → it is sin(yaw)  (sin(0)=0, sin(0x4000)=+1)
//   zz_0045238_(yaw) writes to pos.Z → it is cos(yaw)  (cos(0)=1, cos(0x4000)=0)
const TAU = Math.PI * 2;
function bam16ToRad(bam: number): number {
  // s16 wrap, then scale to radians.
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return (s / 0x10000) * TAU;
}
/** Port of zz_0045204_ — projects onto X; equals sin(yaw). */
export function projectX(bam: number): number {
  return Math.sin(bam16ToRad(bam));
}
/** Port of zz_0045238_ — projects onto Z; equals cos(yaw). */
export function projectZ(bam: number): number {
  return Math.cos(bam16ToRad(bam));
}

/**
 * Port of `FUN_80067310` @ chunk_0008.c:3787 — the primary physics integrator. Called
 * once per frame by virtually every family action handler (G Crash phase 1/2/3, melee
 * lunges, dashes, jumps, etc.) with the gravity coefficient for the current move.
 *
 * ROM signature: `void FUN_80067310(double gravity, int actor, short yaw)`.
 *
 * Effect (1:1 with the decomp):
 *  1. timescale = `+0x5f4 × +0x5f8` (status × tier velocity scales)
 *  2. pos.x += timescale × (hSpeed × cos(yaw))
 *  3. pos.y += timescale × yVel
 *  4. pos.z += timescale × (hSpeed × sin(yaw))
 *  5. (collision + ground clamp via zz_0068030_ — separately ported below)
 *  6. hSpeed += hDecel × +0x5f4 (clamp >= H_SPEED_FLOOR)
 *  7. yVel += +0x5f4 × (gravityCoeff × gravity); clamp to [maxFall, maxRise] (or
 *     FLY_FALL when the actor is a flyer / has the no-clamp flag at +0x741/+0x6cb)
 */
export function integratePhysics(gravity: number, actor: RomActor, yaw: number): void {
  const ts = actor.timescale * actor.tierScale;
  const sx = projectX(yaw);
  const sz = projectZ(yaw);
  actor.pos.x += ts * (actor.hSpeed * sx);
  actor.pos.y += ts * actor.yVel;
  actor.pos.z += ts * (actor.hSpeed * sz);
  groundClamp(actor);
  actor.hSpeed += actor.hDecel * actor.timescale;
  if (actor.hSpeed < ROM_FLOAT.H_SPEED_FLOOR) actor.hSpeed = ROM_FLOAT.H_SPEED_FLOOR;
  actor.yVel += actor.timescale * (actor.gravityCoeff * gravity);
  clampVertical(actor);
}

/** Port of the vertical-clamp tail of FUN_80067310 (lines 3815-3828): the +0x741/+0x6cb
 *  flyer/no-clamp flag selects between the per-borg [maxFall, maxRise] band and the
 *  flyer FLY_FALL floor. The flag bytes are surfaced as `flyer` on BorgRuntime in the
 *  existing port; here they are read directly. */
export function clampVertical(actor: RomActor): void {
  // The +0x741/+0x6cb test in the ROM is "is this a flying/no-clamp actor". The existing
  // @gf/combat BorgProfile.flyer carries this; the ROM runtime reads the same bit via a
  // field the family-port adapter sets. See PORTING.md.
  const flyer = (actor as RomActor & { flyer?: boolean }).flyer === true;
  if (!flyer) {
    const fall = Math.max(actor.maxFall, actor.yVel);
    actor.yVel = fall;
  } else {
    actor.yVel = Math.max(ROM_FLOAT.FLY_FALL, actor.yVel);
  }
}

/** Port of `zz_0068030_` — the ground/collision clamp called between position
 *  integration and velocity decay. The behavior belongs to this actor's battle. */
export function groundClamp(actor: RomActor): void {
  if (!actor.physicsRuntime) return;
  const result = actor.physicsRuntime.clampToGround(actor.pos, actor.yVel);
  actor.pos.y = result.y;
  actor.yVel = result.velY;
  (actor as RomActor & { grounded?: boolean }).grounded = result.grounded;
}

/**
 * Port of `FUN_800676d8` @ chunk_0008.c:3947 — a yaw-only XZ projection used by some
 *  handlers (the "dash without decel" variant). ROM signature:
 *  `void FUN_800676d8(double magnitude, int actor, short yaw)`. Splits `magnitude ×
 *  tierScale × timescale` across X and Z via cos/sin of `yaw`; does NOT touch hSpeed
 *  or yVel. Used by spawn-arc and dash-ram families.
 */
export function projectXzMagnitude(magnitude: number, actor: RomActor, yaw: number): void {
  const ts = actor.tierScale * (magnitude * actor.timescale);
  actor.pos.x += ts * projectX(yaw);
  actor.pos.z += ts * projectZ(yaw);
}

/**
 * Port of `FUN_80067610` @ chunk_0008.c:3915 — the "drift" integrator that only applies
 *  when the motion vector `(motion.x, motion.y, motion.z)` exceeds DRIFT_EPSILON_SQ.
 *  Normalizes motion, scales by `hSpeed × timescale × tierScale`, adds to position; then
 *  decays hSpeed by `hDecel × timescale`. Used by knockback reactions.
 */
export function integrateDrift(actor: RomActor): void {
  const m = actor.motion;
  const mag2 = m.x * m.x + m.y * m.y + m.z * m.z;
  if (mag2 <= ROM_FLOAT.DRIFT_EPSILON_SQ) return;
  const ts = actor.timescale * actor.tierScale;
  const inv = 1 / Math.sqrt(mag2);
  const sx = m.x * inv;
  const sz = m.z * inv;
  const scale = actor.hSpeed * ts;
  actor.pos.x += sx * scale;
  actor.pos.z += sz * scale;
  actor.hSpeed += actor.hDecel * actor.timescale;
  if (actor.hSpeed < ROM_FLOAT.H_SPEED_FLOOR) actor.hSpeed = ROM_FLOAT.H_SPEED_FLOOR;
}

/** Port of `gnt4_PSVECSubtract_bl` / `gnt4_PSQUATScale_bl` / `gnt4_PSVECAdd_bl` — the
 *  vector helpers family handlers chain together (e.g. G Crash phase 0's "push 5% from
 *  target" repositioning at chunk_0047.c:836-839). */
export function vecSubtract(a: Vec3, b: Vec3, out: Vec3): Vec3 {
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;
  return out;
}
export function vecScale(s: number, v: Vec3, out: Vec3): Vec3 {
  out.x = v.x * s;
  out.y = v.y * s;
  out.z = v.z * s;
  return out;
}
export function vecAdd(a: Vec3, b: Vec3, out: Vec3): Vec3 {
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;
  return out;
}
