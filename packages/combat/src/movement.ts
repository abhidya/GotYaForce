// Movement / physics for a single borg, advanced one fixed frame.
//
// Model (grounded in the decomp/RAM trace):
//   - Flat ground plane; GROUND_Y when grounded (ram-trace s3.1, Y=10 const).
//   - Forward = +Z; heading is yaw at struct+0x72 (behavior-notes s3). rotY here is radians.
//   - Position is a contiguous vec3 (struct+0x44). We integrate pos += vel each frame.
//
// Controls: A=jump -> ground jump, then air-jumps up to the borg's jump level, then (flyers)
// hold A for boost flight. Stick = move. dash = step/dodge with brief i-frames.
//
// Tuning constants live in constants.ts (single CONST block). Relative feel comes from the
// borg's `speed`/jump stats; absolute scale is tuned.

import {
  add,
  clamp,
  forwardFromYaw,
  normalize,
  turnToward,
  yawFromXZ,
  type Vec3,
} from "@gf/physics";
import { DASH, JUMP, MOVE } from "./constants.js";
import type { BorgProfile } from "./stats.js";
import type { BorgRuntime, PlayerInput, RectStageBounds, StageCollision, StageCollisionTriangle } from "./types.js";

const GROUND_SNAP_UP = 35;

export interface MoveContext {
  /** Resolved lock-on target position, if locked (face toward it). */
  lockTargetPos: Vec3 | null;
  bounds: RectStageBounds;
  collision: StageCollision | null;
}

/** True if the borg's current state allows free movement input. */
function canMove(b: BorgRuntime): boolean {
  return (
    b.state === "idle" ||
    b.state === "move" ||
    b.state === "jump" ||
    b.state === "fly"
  );
}

/** Ground horizontal speed (units/frame) for this profile. */
export function groundSpeed(p: BorgProfile): number {
  return MOVE.GROUND_BASE + p.speed * MOVE.GROUND_PER_STAT;
}

/**
 * Advance movement for one borg by one frame. Mutates `b`. Handles facing, horizontal
 * acceleration, jump/air-jump/boost-flight, dash, gravity, ground clamp, and bounds.
 * Combat states (attack/special/hit/down/death/spawn) freeze horizontal input here but
 * gravity + dash decay still apply so a borg knocked into the air falls correctly.
 */
export function stepMovement(
  b: BorgRuntime,
  p: BorgProfile,
  input: PlayerInput,
  ctx: MoveContext,
): void {
  const free = canMove(b);

  // --- Facing -------------------------------------------------------------------------
  // Face the lock target if locked; else face the movement direction.
  let desiredYaw: number | null = null;
  if (ctx.lockTargetPos) {
    desiredYaw = yawFromXZ(ctx.lockTargetPos.x - b.pos.x, ctx.lockTargetPos.z - b.pos.z);
  } else if (free && (input.moveX !== 0 || input.moveZ !== 0)) {
    desiredYaw = yawFromXZ(input.moveX, input.moveZ);
  }
  if (desiredYaw !== null) {
    b.rotY = turnToward(b.rotY, desiredYaw, MOVE.TURN_RATE);
  }

  // --- Dash / step --------------------------------------------------------------------
  // A dash overrides horizontal velocity for its duration and grants brief i-frames.
  const dashCd = b.cooldowns["dash"] ?? 0;
  if (free && input.dash && dashCd <= 0 && (b.cooldowns["dashActive"] ?? 0) <= 0) {
    // Dash in stick direction, or forward if no stick.
    let dx = input.moveX;
    let dz = input.moveZ;
    if (dx === 0 && dz === 0) {
      const fwd = forwardFromYaw(b.rotY);
      dx = fwd.x;
      dz = fwd.z;
    }
    const dir = normalize({ x: dx, y: 0, z: dz });
    b.vel.x = dir.x * DASH.SPEED;
    b.vel.z = dir.z * DASH.SPEED;
    b.cooldowns["dashActive"] = DASH.DURATION;
    b.cooldowns["dash"] = DASH.COOLDOWN;
    b.invincTimer = Math.max(b.invincTimer, DASH.IFRAMES);
  }

  const dashing = (b.cooldowns["dashActive"] ?? 0) > 0;

  // --- Horizontal movement ------------------------------------------------------------
  if (!dashing) {
    const flying = !b.grounded && p.flyer;
    const maxSpeed = groundSpeed(p) * (flying ? MOVE.FLY_MULT : 1);
    let targetVx = 0;
    let targetVz = 0;
    if (free && (input.moveX !== 0 || input.moveZ !== 0)) {
      const dir = normalize({ x: input.moveX, y: 0, z: input.moveZ });
      targetVx = dir.x * maxSpeed;
      targetVz = dir.z * maxSpeed;
    }
    const rate = targetVx === 0 && targetVz === 0 ? MOVE.DECEL : MOVE.ACCEL;
    b.vel.x = approachScalar(b.vel.x, targetVx, rate);
    b.vel.z = approachScalar(b.vel.z, targetVz, rate);
  }

  // --- Vertical: jump / air-jump / boost flight / gravity -----------------------------
  if (input.jump && free) {
    handleJump(b);
  }
  // Boost flight: flyer holding jump in the air gets sustained lift while fuel remains.
  const boostFuel = b.cooldowns["boostFuel"] ?? JUMP.BOOST_FUEL_FRAMES;
  if (p.flyer && !b.grounded && input.jump && free && boostFuel > 0) {
    b.vel.y = Math.min(b.vel.y + JUMP.BOOST_THRUST, JUMP.BOOST_MAX_RISE);
    b.cooldowns["boostFuel"] = boostFuel - 1;
    if (b.state === "jump" || b.state === "idle" || b.state === "move") {
      setState(b, "fly");
    }
  }

  // Gravity (always, even in combat states, so knockback arcs fall).
  b.vel.y = Math.max(b.vel.y - JUMP.GRAVITY, -JUMP.MAX_FALL);

  // --- Integrate ----------------------------------------------------------------------
  b.pos = add(b.pos, b.vel as Vec3);

  // Bounds clamp on XZ. Real STIH stage bounds are rectangular and slightly
  // asymmetric around origin (for st00: -11000..10000), so clamp to min/max
  // before querying the floor triangle under the borg.
  b.pos.x = clamp(b.pos.x, ctx.bounds.minX, ctx.bounds.maxX);
  b.pos.z = clamp(b.pos.z, ctx.bounds.minZ, ctx.bounds.maxZ);

  const groundY = groundYAt(ctx.collision, b.pos.x, b.pos.z, b.pos.y);
  if (b.pos.y <= groundY) {
    b.pos.y = groundY;
    if (b.vel.y < 0) b.vel.y = 0;
    if (!b.grounded) onLand(b, p);
    b.grounded = true;
  } else {
    b.grounded = false;
  }

  // --- State bookkeeping for the locomotion states ------------------------------------
  if (free) {
    if (!b.grounded) {
      if (b.state !== "fly") setState(b, "jump");
    } else {
      const moving = Math.abs(b.vel.x) > 0.05 || Math.abs(b.vel.z) > 0.05;
      setState(b, moving ? "move" : "idle");
    }
  }
}

function handleJump(b: BorgRuntime): void {
  // Edge-detect jump via a per-borg "jumpHeld" latch in cooldowns (0 = released).
  const held = (b.cooldowns["jumpHeld"] ?? 0) > 0;
  b.cooldowns["jumpHeld"] = 1; // mark held this frame; cleared in clearJumpLatch when released
  if (held) return; // only act on the rising edge

  if (b.grounded) {
    b.vel.y = JUMP.VELOCITY;
    b.grounded = false;
    setState(b, "jump");
  } else if (b.airJumps > 0) {
    b.vel.y = JUMP.VELOCITY;
    b.airJumps -= 1;
    setState(b, "jump");
  }
}

/** Call once per frame after movement when jump is NOT held, to re-arm the jump edge. */
export function clearJumpLatch(b: BorgRuntime, jumpHeld: boolean): void {
  if (!jumpHeld) b.cooldowns["jumpHeld"] = 0;
}

function onLand(b: BorgRuntime, p: BorgProfile): void {
  b.airJumps = p.airJumpLevel;
  b.cooldowns["boostFuel"] = JUMP.BOOST_FUEL_FRAMES;
}

function setState(b: BorgRuntime, s: BorgRuntime["state"]): void {
  if (b.state !== s) {
    b.state = s;
    b.stateTime = 0;
    b.anim = s;
  }
}

function approachScalar(current: number, target: number, maxDelta: number): number {
  if (current < target) return Math.min(current + maxDelta, target);
  if (current > target) return Math.max(current - maxDelta, target);
  return target;
}

function groundYAt(collision: StageCollision | null, x: number, z: number, currentY: number): number {
  // Use STIH triangles as floor candidates, but do not teleport up to distant
  // platforms/ceilings; exact step-up limits still need a DOL mechanics trace.
  const surfaceY = floorSurfaceYAt(collision, x, z, currentY - JUMP.GROUND_Y + GROUND_SNAP_UP);
  return surfaceY == null ? JUMP.GROUND_Y : surfaceY + JUMP.GROUND_Y;
}

function floorSurfaceYAt(
  collision: StageCollision | null,
  x: number,
  z: number,
  maxSurfaceY: number,
): number | null {
  if (!collision || collision.triangles.length === 0) return null;
  let best: number | null = null;
  const primary = candidateTriangles(collision, x, z);
  best = bestFloorFromCandidates(primary, x, z, maxSurfaceY);
  if (best != null || primary.length === collision.triangles.length) return best;
  return bestFloorFromCandidates(collision.triangles, x, z, maxSurfaceY);
}

function candidateTriangles(collision: StageCollision, x: number, z: number): StageCollisionTriangle[] {
  const grid = collision.grid;
  if (!grid) return collision.triangles;
  const cx = Math.floor((x - grid.origin.x) / grid.cellSize.x);
  const cz = Math.floor((z - grid.origin.z) / grid.cellSize.z);
  if (cx < 0 || cz < 0 || cx >= grid.gridCells.x || cz >= grid.gridCells.z) return [];
  const cell = grid.cells[cz * grid.gridCells.x + cx];
  if (!cell || cell.triangleIndices.length === 0) return [];
  const out: StageCollisionTriangle[] = [];
  for (const index of cell.triangleIndices) {
    const tri = collision.triangles[index];
    if (tri) out.push(tri);
  }
  return out;
}

function bestFloorFromCandidates(
  triangles: readonly StageCollisionTriangle[],
  x: number,
  z: number,
  maxSurfaceY: number,
): number | null {
  let best: number | null = null;
  for (const tri of triangles) {
    if (tri.marker !== 0xcccccccc) continue;
    if (!isFiniteVec(tri.normal)) continue;
    if (tri.normal.y < 0.5) continue;
    if (!tri.vertices.every(isFiniteVec)) continue;
    if (x < tri.bounds2d.minX || x > tri.bounds2d.maxX || z < tri.bounds2d.minZ || z > tri.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y == null || y > maxSurfaceY) continue;
    if (best == null || y > best) best = y;
  }
  return best;
}

function yAtTriangleXZ(tri: StageCollisionTriangle, x: number, z: number): number | null {
  const [a, b, c] = tri.vertices;
  const denom = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
  if (Math.abs(denom) < 1e-5) return null;
  const wa = ((b.z - c.z) * (x - c.x) + (c.x - b.x) * (z - c.z)) / denom;
  const wb = ((c.z - a.z) * (x - c.x) + (a.x - c.x) * (z - c.z)) / denom;
  const wc = 1 - wa - wb;
  if (wa < -1e-4 || wb < -1e-4 || wc < -1e-4) return null;
  return wa * a.y + wb * b.y + wc * c.y;
}

function isFiniteVec(v: Vec3): boolean {
  return Number.isFinite(v.x) && Number.isFinite(v.y) && Number.isFinite(v.z);
}

// re-export for combat.ts convenience
export { setState as _setState };
