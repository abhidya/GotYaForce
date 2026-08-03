// ROM-faithful physics + motion integration — 1:1 port of GG4E engine functions.
//
// Source: `research/decomp/ghidra-export/chunk_0008.c`, functions FUN_80067310 (the
// primary integrator every family handler calls) and its variants. The scalar speed
// model (hSpeed + yVel + decel + gravityCoeff) is faithfully preserved; the existing
// @gf/combat movement.ts vec3-velocity model is NOT used by this runtime.
//
// Constant source: `user-data/GG4E/disc/sys/boot.dol` (read via research/decomp/dol.py).
//
// WIRING (this file owns per the physicsExtras integration spec): physicsExtras.ts ports
// the REMAINING movement entry-points — full-clamp integrator zz_0067458_, no-clamp
// integrator FUN_80067524, floor snap zz_0068030_, collision probe zz_00677b0_, ground
// revert zz_00679d0_ — plus the real DOL float constants. physics.ts delegates to that
// module so the integrator variants share one audited code path:
//   - ROM_FLOAT reads the DOL-decoded ROM_FLOAT_EX values (no more 0.0 stubs).
//   - integratePhysics's body delegates to integratePosition + decayHSpeed +
//     accumulateGravity (the shared sub-steps FUN_80067310 / FUN_80067524 / zz_0067458_
//     all share in the decomp).
//   - groundClamp routes to floorSnap8030 (zz_0068030_) when the host runtime supplies
//     the extras floor-plane contract (floorY/floorSnapDisabled) instead of a coarse
//     clampToGround override — faithful skip conditions + pos formula.
// The full-clamp + no-clamp integrator variants and the ground/collision probes are
// re-exported below so family handlers import them from the physics module surface.

import type { RomActor, RomPhysicsRuntime, Vec3 } from "./actor.js";
import type { RomPhysicsExtrasRuntime } from "./physicsExtras.js";
import {
  ROM_FLOAT_EX,
  integratePosition,
  decayHSpeed,
  accumulateGravity,
  floorSnap8030,
  clampHSpeedBand,
  applyVerticalClampBand,
} from "./physicsExtras.js";

// Re-export the integrator variants + ground/collision probes physicsExtras owns, so the
// family handlers that need a speed cap (kung-fu-master, death-borg-chi, cosmic-dragon,
// cyber-dragon, dragon, phoenix-dragon) import them from the physics surface.
export {
  // zz_0067458_ @ chunk_0008.c:3836 — full-clamp integrator (FUN_80067310 + upper
  // hSpeed/yVel band clamps). Speed-capped moves call THIS, not integratePhysics.
  integratePhysicsFullClamp,
  // FUN_80067524 @ chunk_0008.c:3878 — raw integrator (no ground snap, no vertical
  // clamp). Ballistic / airborne phases that must fall freely.
  integratePhysicsNoClamp,
  // zz_0068030_ @ chunk_0008.c:4337 — ROM-faithful floor snap (skip conditions +
  // pos.y = max(savedGroundPos.y, floorY - hoverOffset)).
  floorSnap8030,
  // zz_00677b0_ @ chunk_0008.c:3983 — collision/step-height probe (wall-slide + land).
  groundProbe77b0,
  // zz_00679d0_ @ chunk_0008.c:4062 — ground revert (probe + restore savedGroundPos).
  groundSnapRevert79d0,
  // Shared sub-steps + vertical/hSpeed band clamps, exposed for audit / family tests.
  applyVerticalClampLower,
  applyVerticalClampBand,
  clampHSpeedBand,
  ROM_FLOAT_EX,
} from "./physicsExtras.js";

// Decoded from boot.dol (see action-vm-and-gcrash-decode-2026-07-05.md). Values sourced
// from physicsExtras.ROM_FLOAT_EX — the DOL-decoded constant table shared with the
// integrator variants. H_SPEED_FLOOR stays 0.0 (matches the DOL); FLY_FALL and
// DRIFT_EPSILON_SQ replace the prior 0.0 stubs with the real decoded values.
export const ROM_FLOAT = {
  /** 0x804375d0: minimum hSpeed clamp (FUN_80067310:3806, 3843). */
  H_SPEED_FLOOR: ROM_FLOAT_EX.H_SPEED_FLOOR,
  /** 0x804375f0: terminal fall velocity for flying actors (FUN_80067310:3823). DOL = -35.0. */
  FLY_FALL: ROM_FLOAT_EX.FLY_FALL,
  /** 0x804375f4: squared-magnitude threshold below which FUN_80067610 skips (line 3921). DOL ≈ 1e-8. */
  DRIFT_EPSILON_SQ: ROM_FLOAT_EX.DRIFT_EPSILON_SQ,
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
 *
 * FULL-CLAMP DEFAULT (zz_0067458_ @ chunk_0008.c:3836): when the actor carries POPULATED
 * ROM speed-clamp fields (maxHSpeed +0x678 > 0 AND maxRise +0x67c > 0), this integrator
 * ALSO applies the upper band clamps the FULL-clamp variant layers on top of FUN_80067310
 * (clampHSpeedBand + applyVerticalClampBand). The six documented full-clamp family
 * consumers (kung-fu-master, death-borg-chi, cosmic-dragon, cyber-dragon, dragon,
 * phoenix-dragon) call integratePhysics directly — this gate gives them the speed cap by
 * DEFAULT without needing to wire each handler to integratePhysicsFullClamp explicitly.
 * Actors without populated band fields (createRomActor defaults them to 0) keep the
 * lower-only FUN_80067310 tail (clampVertical) — the upper clamp would incorrectly zero
 * positive yVel when maxRise is unset. integratePhysicsFullClamp (physicsExtras) wraps
 * this function + re-applies the same idempotent band clamps; the redundancy is harmless.
 */
export function integratePhysics(gravity: number, actor: RomActor, yaw: number): void {
  // Delegated to physicsExtras' shared sub-steps so FUN_80067310, FUN_80067524 (no-clamp),
  // and zz_0067458_ (full-clamp) all share one audited code path (see the WIRING note at
  // the top of this file). The ground snap runs BETWEEN position integration and velocity
  // decay, matching chunk_0008.c:3805.
  integratePosition(gravity, actor, yaw);
  groundClamp(actor);
  decayHSpeed(actor);
  accumulateGravity(gravity, actor);
  // Full-clamp tail when the actor has populated speed-clamp fields (zz_0067458_'s upper
  // band clamps); otherwise the lower-only FUN_80067310 tail. See the header above.
  if (actor.maxHSpeed > 0 && actor.maxRise > 0) {
    clampHSpeedBand(actor);
    applyVerticalClampBand(actor);
  } else {
    clampVertical(actor);
  }
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
 *  integration and velocity decay. The behavior belongs to this actor's battle.
 *
 *  WIRING (physicsExtras spec item 3): when the host runtime supplies the extras
 *  floor-plane contract (`floorY` / `floorSnapDisabled` on RomPhysicsExtrasRuntime),
 *  delegate to the ROM-faithful `floorSnap8030` port — exact skip conditions + the
 *  `pos.y = max(savedGroundPos.y, floorY - hoverOffset)` formula. Battles that only
 *  supply the coarse `clampToGround` override keep that abstraction (unchanged). Unit
 *  tests with no physicsRuntime keep the pre-existing `grounded`-flag passthrough. */
export function groundClamp(actor: RomActor): boolean {
  if (!actor.physicsRuntime) return (actor as RomActor & { grounded?: boolean }).grounded === true;
  const rt = actor.physicsRuntime as RomPhysicsRuntime & Partial<RomPhysicsExtrasRuntime>;
  // Faithful-repro path: extras floor-plane contract present → ROM-faithful zz_0068030_.
  if (rt.floorY !== undefined || rt.floorSnapDisabled !== undefined) {
    return floorSnap8030(actor) !== 0;
  }
  // Host abstraction: the battle's coarse clampToGround (pre-existing behavior).
  const result = rt.clampToGround(actor.pos, actor.yVel);
  actor.pos.y = result.y;
  actor.yVel = result.velY;
  (actor as RomActor & { grounded?: boolean }).grounded = result.grounded;
  return result.grounded;
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
