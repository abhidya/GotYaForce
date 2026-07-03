// @gf/physics — deterministic 3D vector math + a fixed-step integrator helper used by
// the combat simulation. NO DOM, NO three.js, NO floating randomness from outside.
//
// The combat core treats the world as a flat ground plane (RAM trace: Y is constant when
// grounded, render scale 1.5 baked into the renderer, not here). These helpers are pure and
// allocation-light so the sim stays deterministic and replayable for netcode rollback.
//
// Source for the ground-plane / heading-as-yaw model:
//   research/decomp/ram-trace-analysis.md  (position vec3 @ struct+0x44, Y flat)
//   research/decomp/behavior-notes.md       (heading s16 @ struct+0x72 = yaw, 0x10000=360deg)

export interface Vec3 {
  x: number;
  y: number;
  z: number;
}

export function vec3(x = 0, y = 0, z = 0): Vec3 {
  return { x, y, z };
}

export function copy(v: Vec3): Vec3 {
  return { x: v.x, y: v.y, z: v.z };
}

export function add(a: Vec3, b: Vec3): Vec3 {
  return { x: a.x + b.x, y: a.y + b.y, z: a.z + b.z };
}

export function sub(a: Vec3, b: Vec3): Vec3 {
  return { x: a.x - b.x, y: a.y - b.y, z: a.z - b.z };
}

export function scale(a: Vec3, s: number): Vec3 {
  return { x: a.x * s, y: a.y * s, z: a.z * s };
}

/** Squared length on the full 3D vector. */
export function lenSq(a: Vec3): number {
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

export function len(a: Vec3): number {
  return Math.sqrt(lenSq(a));
}

/** Horizontal (XZ-plane) distance — the gameplay-relevant range metric on the flat field. */
export function distXZ(a: Vec3, b: Vec3): number {
  const dx = a.x - b.x;
  const dz = a.z - b.z;
  return Math.sqrt(dx * dx + dz * dz);
}

export function distSqXZ(a: Vec3, b: Vec3): number {
  const dx = a.x - b.x;
  const dz = a.z - b.z;
  return dx * dx + dz * dz;
}

/** Full 3D distance. */
export function dist(a: Vec3, b: Vec3): number {
  return len(sub(a, b));
}

/** Returns a normalized copy; the zero vector returns itself (no NaN). */
export function normalize(a: Vec3): Vec3 {
  const l = len(a);
  if (l < 1e-9) return { x: 0, y: 0, z: 0 };
  const inv = 1 / l;
  return { x: a.x * inv, y: a.y * inv, z: a.z * inv };
}

/**
 * Yaw angle (radians) of a horizontal direction, measured from +Z (the game's "forward"
 * per the RAM trace where holding FORWARD moved +Z). atan2(x, z) so that rotY=0 faces +Z
 * and increases toward +X.
 */
export function yawFromXZ(dx: number, dz: number): number {
  return Math.atan2(dx, dz);
}

/** Unit forward vector for a given yaw (inverse of yawFromXZ). */
export function forwardFromYaw(yaw: number): Vec3 {
  return { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) };
}

/** Shortest signed angular difference target-current, wrapped to (-PI, PI]. */
export function angleDelta(current: number, target: number): number {
  let d = (target - current) % (Math.PI * 2);
  if (d > Math.PI) d -= Math.PI * 2;
  if (d < -Math.PI) d += Math.PI * 2;
  return d;
}

/** Rotate `current` yaw toward `target` by at most `maxStep` radians. */
export function turnToward(current: number, target: number, maxStep: number): number {
  const d = angleDelta(current, target);
  if (Math.abs(d) <= maxStep) return wrapAngle(target);
  return wrapAngle(current + Math.sign(d) * maxStep);
}

/** Wrap an angle to (-PI, PI]. */
export function wrapAngle(a: number): number {
  let r = a % (Math.PI * 2);
  if (r > Math.PI) r -= Math.PI * 2;
  if (r <= -Math.PI) r += Math.PI * 2;
  return r;
}

export function clamp(v: number, lo: number, hi: number): number {
  return v < lo ? lo : v > hi ? hi : v;
}

export function lerp(a: number, b: number, t: number): number {
  return a + (b - a) * t;
}

/**
 * Move a scalar toward a target by at most `maxDelta` (used for acceleration/damping so
 * movement is frame-rate independent given a fixed step count).
 */
export function approach(current: number, target: number, maxDelta: number): number {
  if (current < target) return Math.min(current + maxDelta, target);
  if (current > target) return Math.max(current - maxDelta, target);
  return target;
}

// Knockback DIRECTION calc — ported from the decompiled ROM function `zz_00300bc_` @
// 0x800300bc. See knockback.ts for the full derivation notes and behavior-notes.md section (p).
export {
  BAM16_PER_RADIAN,
  angleTrimByteToBam16,
  bam16YawToXZ,
  computeAttackerToTargetDirection,
  computeLinkedObjectDirection,
  knockbackDirectionFromPositions,
  vectorToKnockbackAngle,
  type KnockbackAngle,
} from "./knockback.js";

export {
  bestFloorFromCandidates,
  candidateTriangles,
  candidateTrianglesForSegment,
  floorSurfaceYAt,
  isFiniteVec,
  normalizeStageBounds,
  stageCollisionFromHitGrids,
  yAtTriangleXZ,
  type RectStageBounds,
  type StageBounds,
  type StageCollision,
  type StageCollisionCell,
  type StageCollisionLayer,
  type StageCollisionResources,
  type StageCollisionTriangle,
  type StageHitGridLike,
  type SymmetricStageBounds,
} from "./collision.js";
