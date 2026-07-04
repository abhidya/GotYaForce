// Per-borg movement physics adapter (scale-reconciled) — behavior-notes (bc).
//
// Source: data/movementPhysics.json (scripts/gen-movement-physics.mjs), the per-borg
// pl####data.bin parameter page (DERIVED — big-endian floats at documented offsets, loaded to
// actor+0x4ac in the ROM). Raw ROM values CANNOT be swapped into the port 1:1: the port's
// world/velocity model is anchored to the DERIVED 22.0 u/f G RED ground trace with its own
// TUNED accel/decel/gravity, and (bc) shows the raw values live in a different scale
// (e.g. global max-fall -35.0 vs the port's 8.0).
//
// Reconciliation model: RATIO-ANCHORED at pl0615 (G RED) — the one borg with a live movement
// trace. Each per-borg value is applied as (borgValue / gRedValue) × the port's tuned G RED
// constant, so G RED's playable feel is bit-identical to before while every other borg's
// RELATIVE physics (jump height, fall weight) becomes DERIVED data instead of one global
// profile. Wired fields:
//   - jumpImpulse (+0x48, G RED 15.0)  → scales JUMP.VELOCITY
//   - gravityFall (+0x6c, G RED -1.0)  → scales JUMP.GRAVITY (the airborne fall slot; the
//     pl0d/pl0e satellite/air families carry -0.1 → genuinely floaty, source behavior)
// NOT yet wired (exported as data only):
//   - maxHSpeed (+0x2c): the ROM's h-speed CLAMP, whose relation to the guide speed stat
//     (+0x50 minTurnSpeed — already the port's per-borg `profile.speed` input) is unresolved:
//     pl0000 carries the same 12.0 clamp as G RED but speed stat 3, so mapping ground speed
//     from the clamp would flatten stat differences the port already models. Needs the
//     runtime speed chain read before it can replace groundSpeed().
//   - knockdownLaunch* (+0x58/+0x5c): for the future knockback launch path.
//   - groundAccel (+0x44): 0.0 means "snap-to-min" in the ROM (semantics undecoded); the
//     port keeps its global MOVE.ACCEL approach model.

import movementPhysicsData from "./data/movementPhysics.json" with { type: "json" };
import { JUMP } from "./constants.js";

export interface BorgMovementPhysics {
  /** +0x2c — max horizontal speed clamp (ROM scale). */
  maxHSpeed: number;
  /** +0x44 — ground-accel magnitude; 0.0 = snap-to-min (ROM semantics undecoded). */
  groundAccel: number;
  /** +0x48 — jump / vertical impulse (ROM scale; G RED 15.0). */
  jumpImpulse: number;
  /** +0x50 — min/turn speed; equals the guide "speed stat" feeding profile.speed. */
  minTurnSpeed: number;
  /** +0x58 — knockdown launch h-speed (future launch-path input). */
  knockdownLaunchHSpeed: number;
  /** +0x5c — knockdown launch accel. */
  knockdownLaunchAccel: number;
  /** +0x68 — gravity slot A (ground/turn states). */
  gravityGround: number;
  /** +0x6c — gravity slot B: the true airborne fall gravity (G RED -1.0). */
  gravityFall: number;
  /** +0x70 — gravity slot C. */
  gravityC: number;
}

type MovementPhysicsFile = {
  _meta: Record<string, unknown>;
  borgs: Record<string, BorgMovementPhysics>;
};

const DATA = movementPhysicsData as MovementPhysicsFile;

/** The ratio anchor: G RED, the only borg with a live-trace-calibrated port profile. */
const ANCHOR_ID = "pl0615";
const ANCHOR = DATA.borgs[ANCHOR_ID] ?? { jumpImpulse: 15, gravityFall: -1 };

/** Raw DERIVED movement page for a borg, or null for ids without a pl####data.bin. */
export function movementPhysicsForBorgId(id: string): BorgMovementPhysics | null {
  return DATA.borgs[id.toLowerCase()] ?? null;
}

/**
 * Port-scale jump takeoff velocity for a borg: JUMP.VELOCITY × (jumpImpulse / G RED's 15.0).
 * DERIVED ratio × TUNED anchor; ids without data keep the global tuned value.
 */
export function jumpVelocityForBorgId(id: string): number {
  const data = movementPhysicsForBorgId(id);
  if (!data || !(ANCHOR.jumpImpulse > 0) || !(data.jumpImpulse > 0)) return JUMP.VELOCITY;
  return JUMP.VELOCITY * (data.jumpImpulse / ANCHOR.jumpImpulse);
}

/**
 * Port-scale fall gravity for a borg: JUMP.GRAVITY × (|gravityFall| / G RED's 1.0).
 * The pl0d/pl0e satellite/air families carry -0.1 (≈float) — source behavior, applied as-is.
 */
export function fallGravityForBorgId(id: string): number {
  const data = movementPhysicsForBorgId(id);
  const anchorMag = Math.abs(ANCHOR.gravityFall);
  const mag = data ? Math.abs(data.gravityFall) : 0;
  if (!data || !(anchorMag > 0) || !(mag > 0)) return JUMP.GRAVITY;
  return JUMP.GRAVITY * (mag / anchorMag);
}
