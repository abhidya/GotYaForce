// Movement / physics for a single borg, advanced one fixed frame.
//
// Model (grounded in the decomp/RAM trace):
//   - Flat ground plane; GROUND_Y when grounded (ram-trace s3.1, Y=10 const).
//   - Forward = +Z; heading is yaw at struct+0x72 (behavior-notes s3). rotY here is radians.
//   - Position is a contiguous vec3 (struct+0x44). We integrate pos += vel each frame.
//
// Controls: A=jump -> ground jump, then air-jumps up to the borg's jump level, then (flyers)
// hold A for boost flight. While locked, stick input is target-relative: forward/back move
// toward/away from the target, left/right strafe in the same lock frame, and heading remains
// slaved to the lock vector.
//
// Tuning constants live in constants.ts (single CONST block). Relative feel comes from the
// borg's `speed`/jump stats; absolute scale is tuned.

import {
  add,
  clamp,
  candidateTrianglesForSegment,
  forwardFromYaw,
  floorSurfaceYAt,
  isFiniteVec,
  normalize,
  turnToward,
  yawFromXZ,
  type Vec3,
} from "@gf/physics";
import { BURST, DASH, JUMP, MOVE, MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES } from "./constants.js";
import { dashPhysicsForBorgId, fallGravityForBorgId, groundRunSpeedForBorgId, jumpVelocityForBorgId } from "./movementData.js";
import { actorVelocityScale } from "./timescale.js";
import type { BorgProfile } from "./stats.js";
import type { BorgRuntime, PlayerInput, RectStageBounds, StageCollision, StageCollisionTriangle } from "./types.js";

const GROUND_SNAP_UP = 35;
const WALL_NORMAL_MAX_Y = 0.5;
const WALL_CLEARANCE = 0.25;
const CEILING_NORMAL_MAX_Y = -0.5;
const CEILING_BODY_CLEARANCE = JUMP.GROUND_Y;
const CEILING_CLEARANCE = 0.25;
const STICK_EPS = 0.001;

export interface MoveContext {
  /** Resolved lock-on target position, if locked (face toward it). */
  lockTargetPos: Vec3 | null;
  bounds: RectStageBounds;
  collision: StageCollision | null;
}

/**
 * Port-side movement-context capture (ATK-004). WIKI_TAXONOMY_ONLY — this is explicitly NOT
 * a ROM enum; it is a derived label over signals the sim already tracks (dash cooldown,
 * grounded, fly state, vertical velocity, landing edge), captured so the future command
 * resolver (ATK-003) and melee-context mapping (ATK-005) have an input once the ROM's
 * variant channel (subtype byte actor+0x586, air gate at chunk_0009.c:500-534; see
 * command.ts AttackCommandSubtype.AirElevated4) is mapped to it. Nothing consumes this for
 * gameplay yet — see research/decomp/attack-mechanics-findings.md mechanics D-K.
 */
export type MovementContext =
  | "standing"
  | "ground_dash"
  | "air_dash"
  | "flying"
  | "jump_rise"
  | "neutral_air"
  | "landing";

/**
 * Derive this frame's {@link MovementContext} for `b`. Pure/read-only — does not mutate `b`.
 * Precedence (checked top to bottom; first match wins), per ATK-004:
 *   1. "landing"     — within MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES of the last onLand edge
 *                       (b.cooldowns["landedFrames"] > 0, set/ticked in onLand/stepCooldowns).
 *   2. "air_dash"     — airborne (!grounded) AND mid-dash (cooldowns["dashActive"] > 0).
 *   3. "ground_dash"  — grounded AND mid-dash (cooldowns["dashActive"] > 0).
 *   4. "flying"       — state === "fly" (boost-flight, movement.ts handleJump/stepMovement).
 *   5. "jump_rise"    — airborne, not flying/dashing, rising (vel.y > 0).
 *   6. "neutral_air"  — airborne, not flying/dashing, not rising (vel.y <= 0; apex or falling).
 *   7. "standing"     — grounded, none of the above (idle or walking).
 */
export function movementContextOf(b: BorgRuntime): MovementContext {
  const dashing = (b.cooldowns["dashActive"] ?? 0) > 0;
  const landing = (b.cooldowns["landedFrames"] ?? 0) > 0;

  if (landing) return "landing";
  if (!b.grounded && dashing) return "air_dash";
  if (b.grounded && dashing) return "ground_dash";
  if (b.state === "fly") return "flying";
  if (!b.grounded) return b.vel.y > 0 ? "jump_rise" : "neutral_air";
  return "standing";
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

/** Ground horizontal speed (units/frame) for this profile: the DERIVED raw run speed
 *  (pl####data.bin page+0x2c — run-start states snap actor+0x44 to it, see
 *  movementData.ts), with the MOVE fallback formula for synthetic ids without a page. */
export function groundSpeed(p: BorgProfile): number {
  return groundRunSpeedForBorgId(p.id) ?? MOVE.GROUND_BASE + p.speed * MOVE.GROUND_PER_STAT;
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
  const horizontal = resolveHorizontalIntent(b, input, ctx.lockTargetPos);

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
    // Dash in resolved stick direction, or forward if no stick.
    let dx = horizontal.dashX;
    let dz = horizontal.dashZ;
    if (dx === 0 && dz === 0) {
      const fwd = forwardFromYaw(b.rotY);
      dx = fwd.x;
      dz = fwd.z;
    }
    const dir = normalize({ x: dx, y: 0, z: dz });
    // Per-borg dash page (DERIVED, +0x58/+0x5c/+0x64): the ROM dash states snap the actor's
    // speed to page+0x58 and run for page+0x64 frames with page+0x5c decay per frame
    // (FUN_80061560 / FUN_80063230). TUNED DASH block is only the fallback for synthetic
    // borgs without a data page.
    const dashPage = dashPhysicsForBorgId(b.borgId);
    const dashSpeed = dashPage ? dashPage.hSpeed : DASH.SPEED;
    b.vel.x = dir.x * dashSpeed;
    b.vel.z = dir.z * dashSpeed;
    b.cooldowns["dashActive"] = dashPage ? dashPage.durationFrames : DASH.DURATION;
    b.cooldowns["dash"] = DASH.COOLDOWN;
    b.invincTimer = Math.max(b.invincTimer, DASH.IFRAMES);
  }

  const dashing = (b.cooldowns["dashActive"] ?? 0) > 0;
  if (dashing) {
    // ROM dash decay: actor+0x4c (= page+0x5c, negative) is added to the speed magnitude
    // every frame of the dash state. Applied along the current dash direction.
    const dashPage = dashPhysicsForBorgId(b.borgId);
    if (dashPage && dashPage.accel !== 0) {
      const hSpeed = Math.hypot(b.vel.x, b.vel.z);
      if (hSpeed > 0) {
        const next = Math.max(0, hSpeed + dashPage.accel);
        const scale = next / hSpeed;
        b.vel.x *= scale;
        b.vel.z *= scale;
      }
    }
  }

  // --- Horizontal movement ------------------------------------------------------------
  if (!dashing) {
    const flying = !b.grounded && p.flyer;
    const burstMult = b.burstActive ? BURST.SPEED_MULTIPLIER : 1;
    // actorVelocityScale = the ROM's status(+0x5f4) × tier(+0x5f8) multipliers (timescale.ts,
    // DERIVED tables) — ×1.0 until tier/status writers land. Burst ×1.5 (the same
    // FLOAT_804373d8 the ROM folds into +0x5f4) stays in burstMult, not double-applied.
    const maxSpeed = groundSpeed(p) * (flying ? MOVE.FLY_MULT : 1) * burstMult * actorVelocityScale(b);
    let targetVx = 0;
    let targetVz = 0;
    if (free && (horizontal.walkX !== 0 || horizontal.walkZ !== 0)) {
      const dir = normalize({ x: horizontal.walkX, y: 0, z: horizontal.walkZ });
      targetVx = dir.x * maxSpeed;
      targetVz = dir.z * maxSpeed;
    }
    const rate = targetVx === 0 && targetVz === 0 ? MOVE.DECEL : MOVE.ACCEL;
    b.vel.x = approachScalar(b.vel.x, targetVx, rate);
    b.vel.z = approachScalar(b.vel.z, targetVz, rate);
  }

  // --- Vertical: jump / air-jump / boost flight / gravity -----------------------------
  if (input.jump && free) {
    handleJump(b, jumpVelocityForBorgId(b.borgId));
  }
  // Boost flight — UNIVERSAL (2026-07-04): EVERY borg boosts by holding jump in the air
  // while fuel remains, not only p.flyer. Evidence: the ROM's flight is the
  // gravity-coefficient-0 state (FUN_80067310 with coeff FLOAT_804374ec = 0.0 —
  // behavior-notes (bc)), the boost gauge is on every borg's HUD, and (ap) W17's three
  // flight models include the plain "boost" model for standard borgs. Thrust/max-rise stay
  // TUNED (no ROM thrust constant exists — flight is a gravity toggle). The boost only
  // engages once the jump arc has decayed to the boost ceiling (vel.y <= BOOST_MAX_RISE),
  // so a held ground jump keeps its full DERIVED impulse arc and then transitions into the
  // sustained jet climb; entering "fly" plays the exported boost (jetpack) clip.
  const boostFuel = b.cooldowns["boostFuel"] ?? JUMP.BOOST_FUEL_FRAMES;
  // Flyer-class borgs enter flight immediately (their whole movement identity); standard
  // borgs finish the jump arc first (vel gate), then the jet climb takes over.
  const boosting =
    !b.grounded &&
    input.jump &&
    free &&
    boostFuel > 0 &&
    (p.flyer || b.vel.y <= JUMP.BOOST_MAX_RISE);
  if (boosting) {
    b.vel.y = Math.min(b.vel.y + JUMP.BOOST_THRUST, JUMP.BOOST_MAX_RISE);
    b.cooldowns["boostFuel"] = boostFuel - 1;
    if (b.state === "jump" || b.state === "idle" || b.state === "move") {
      setState(b, "fly");
    }
  }

  // Gravity (skipped while boosting — the ROM's flight IS gravity-coefficient-0, so heavy
  // borgs hover too instead of fighting a thrust term). Per-borg DERIVED raw fall gravity
  // (pl####data.bin +0x6c — movementData.ts): heavies drop faster, the pl0d/pl0e
  // satellite/air families float (-0.1 in source data). MAX_FALL is the DERIVED global
  // terminal clamp (FLOAT_804375f0 = -35.0).
  if (!boosting) {
    b.vel.y = Math.max(b.vel.y - fallGravityForBorgId(b.borgId), -JUMP.MAX_FALL);
  }

  // --- Integrate ----------------------------------------------------------------------
  const prevPos = { ...b.pos };
  b.pos = add(b.pos, b.vel as Vec3);

  // Bounds clamp on XZ. Real STIH stage bounds are rectangular and slightly
  // asymmetric around origin (for st00: -11000..10000), so clamp to min/max
  // before resolving collision and querying the floor triangle under the borg.
  b.pos.x = clamp(b.pos.x, ctx.bounds.minX, ctx.bounds.maxX);
  b.pos.z = clamp(b.pos.z, ctx.bounds.minZ, ctx.bounds.maxZ);
  resolveLateralCollision(ctx.collision, prevPos, b.pos, b.vel);
  b.pos.x = clamp(b.pos.x, ctx.bounds.minX, ctx.bounds.maxX);
  b.pos.z = clamp(b.pos.z, ctx.bounds.minZ, ctx.bounds.maxZ);
  resolveCeilingCollision(ctx.collision, prevPos, b.pos, b.vel);

  keepOnStageFloor(ctx.collision, prevPos, b.pos, b.vel);
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

function handleJump(b: BorgRuntime, jumpVelocity: number = JUMP.VELOCITY): void {
  // Edge-detect jump via a per-borg "jumpHeld" latch in cooldowns (0 = released).
  const held = (b.cooldowns["jumpHeld"] ?? 0) > 0;
  b.cooldowns["jumpHeld"] = 1; // mark held this frame; cleared in clearJumpLatch when released
  if (held) return; // only act on the rising edge

  // `jumpVelocity` is the per-borg DERIVED raw takeoff speed (pl####data.bin +0x48, applied
  // 1:1 — movementData.ts); the default keeps legacy/direct callers on the global fallback.
  if (b.grounded) {
    b.vel.y = jumpVelocity;
    b.grounded = false;
    setState(b, "jump");
  } else if (b.airJumps > 0) {
    b.vel.y = jumpVelocity;
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
  // Landing-edge window for movementContextOf below: ticks down like any other cooldown
  // (see stepCooldowns in combat.ts), consumed as a capture-only signal — nothing currently
  // reads b.cooldowns["landedFrames"] for gameplay.
  b.cooldowns["landedFrames"] = MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES;
}

function setState(b: BorgRuntime, s: BorgRuntime["state"]): void {
  if (b.state !== s) {
    b.state = s;
    b.stateTime = 0;
    b.anim = s;
  }
}

interface HorizontalIntent {
  walkX: number;
  walkZ: number;
  dashX: number;
  dashZ: number;
}

function resolveHorizontalIntent(b: BorgRuntime, input: PlayerInput, lockTargetPos: Vec3 | null): HorizontalIntent {
  const stickX = Math.abs(input.moveX) < STICK_EPS ? 0 : input.moveX;
  const stickZ = Math.abs(input.moveZ) < STICK_EPS ? 0 : input.moveZ;
  if (!lockTargetPos) {
    return { walkX: stickX, walkZ: stickZ, dashX: stickX, dashZ: stickZ };
  }

  const toTargetX = lockTargetPos.x - b.pos.x;
  const toTargetZ = lockTargetPos.z - b.pos.z;
  const toTargetLen = Math.hypot(toTargetX, toTargetZ);
  if (toTargetLen < STICK_EPS) {
    return { walkX: stickX, walkZ: stickZ, dashX: stickX, dashZ: stickZ };
  }

  const towardX = toTargetX / toTargetLen;
  const towardZ = toTargetZ / toTargetLen;
  const rightX = towardZ;
  const rightZ = -towardX;
  const resolvedX = rightX * stickX + towardX * stickZ;
  const resolvedZ = rightZ * stickX + towardZ * stickZ;

  return {
    walkX: resolvedX,
    walkZ: resolvedZ,
    dashX: resolvedX,
    dashZ: resolvedZ,
  };
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

function keepOnStageFloor(
  collision: StageCollision | null,
  previous: Vec3,
  current: Vec3,
  velocity: Vec3,
): void {
  if (!collision || collision.triangles.length === 0) return;
  const maxSurfaceY = current.y - JUMP.GROUND_Y + GROUND_SNAP_UP;
  if (floorSurfaceYAt(collision, current.x, current.z, maxSurfaceY) != null) return;
  if (floorSurfaceYAt(collision, previous.x, previous.z, maxSurfaceY) == null) return;

  current.x = previous.x;
  current.z = previous.z;
  velocity.x = 0;
  velocity.z = 0;
}

function resolveLateralCollision(
  collision: StageCollision | null,
  previous: Vec3,
  current: Vec3,
  velocity: Vec3,
): void {
  if (!collision || collision.triangles.length === 0) return;
  let best: { tri: StageCollisionTriangle; point: Vec3; t: number; side: number } | null = null;
  for (const tri of candidateTrianglesForSegment(collision, previous, current)) {
    const hit = segmentTriangleWallHit(tri, previous, current);
    if (!hit) continue;
    if (!best || hit.t < best.t) best = { tri, ...hit };
  }
  if (!best) return;

  const wallNormal = horizontalNormal(best.tri.normal);
  if (!wallNormal) return;
  const away = { x: wallNormal.x * best.side, z: wallNormal.z * best.side };
  current.x = best.point.x + away.x * WALL_CLEARANCE;
  current.z = best.point.z + away.z * WALL_CLEARANCE;

  const intoWall = velocity.x * away.x + velocity.z * away.z;
  if (intoWall < 0) {
    velocity.x -= away.x * intoWall;
    velocity.z -= away.z * intoWall;
  }
}

function resolveCeilingCollision(
  collision: StageCollision | null,
  previous: Vec3,
  current: Vec3,
  velocity: Vec3,
): void {
  if (!collision || collision.triangles.length === 0 || velocity.y <= 0) return;
  let best: { point: Vec3; t: number } | null = null;
  const previousTop = { ...previous, y: previous.y + CEILING_BODY_CLEARANCE };
  const currentTop = { ...current, y: current.y + CEILING_BODY_CLEARANCE };

  for (const tri of candidateTrianglesForSegment(collision, previousTop, currentTop)) {
    const hit = segmentTriangleCeilingHit(tri, previousTop, currentTop);
    if (!hit) continue;
    if (!best || hit.t < best.t) best = hit;
  }
  if (!best) return;

  const maxOriginY = best.point.y - CEILING_BODY_CLEARANCE - CEILING_CLEARANCE;
  if (current.y > maxOriginY) current.y = maxOriginY;
  if (velocity.y > 0) velocity.y = 0;
}

function segmentTriangleWallHit(
  tri: StageCollisionTriangle,
  previous: Vec3,
  current: Vec3,
): { point: Vec3; t: number; side: number } | null {
  if (tri.marker !== 0xcccccccc) return null;
  if (!isFiniteVec(tri.normal) || !tri.vertices.every(isFiniteVec)) return null;
  if (Math.abs(tri.normal.y) > WALL_NORMAL_MAX_Y) return null;
  if (!horizontalNormal(tri.normal)) return null;

  const a = tri.vertices[0];
  const d0 = signedDistanceToPlane(previous, a, tri.normal);
  const d1 = signedDistanceToPlane(current, a, tri.normal);
  if (!Number.isFinite(d0) || !Number.isFinite(d1)) return null;
  if (Math.abs(d0 - d1) < 1e-5) return null;
  if (d0 === 0 || d0 * d1 > 0) return null;

  const t = d0 / (d0 - d1);
  if (t < -1e-4 || t > 1 + 1e-4) return null;
  const point = {
    x: previous.x + (current.x - previous.x) * t,
    y: previous.y + (current.y - previous.y) * t,
    z: previous.z + (current.z - previous.z) * t,
  };
  if (!pointInTriangle3d(point, tri.vertices)) return null;
  return { point, t, side: d0 >= 0 ? 1 : -1 };
}

function segmentTriangleCeilingHit(
  tri: StageCollisionTriangle,
  previousTop: Vec3,
  currentTop: Vec3,
): { point: Vec3; t: number } | null {
  if (tri.marker !== 0xcccccccc) return null;
  if (!isFiniteVec(tri.normal) || !tri.vertices.every(isFiniteVec)) return null;
  if (tri.normal.y > CEILING_NORMAL_MAX_Y) return null;

  const a = tri.vertices[0];
  const d0 = signedDistanceToPlane(previousTop, a, tri.normal);
  const d1 = signedDistanceToPlane(currentTop, a, tri.normal);
  if (!Number.isFinite(d0) || !Number.isFinite(d1)) return null;
  if (Math.abs(d0 - d1) < 1e-5) return null;
  if (d0 <= 0 || d1 > 0) return null;

  const t = d0 / (d0 - d1);
  if (t < -1e-4 || t > 1 + 1e-4) return null;
  const point = {
    x: previousTop.x + (currentTop.x - previousTop.x) * t,
    y: previousTop.y + (currentTop.y - previousTop.y) * t,
    z: previousTop.z + (currentTop.z - previousTop.z) * t,
  };
  if (!pointInTriangle3d(point, tri.vertices)) return null;
  return { point, t };
}

function signedDistanceToPlane(point: Vec3, planePoint: Vec3, normal: Vec3): number {
  return (
    (point.x - planePoint.x) * normal.x +
    (point.y - planePoint.y) * normal.y +
    (point.z - planePoint.z) * normal.z
  );
}

function pointInTriangle3d(point: Vec3, [a, b, c]: [Vec3, Vec3, Vec3]): boolean {
  const v0 = { x: c.x - a.x, y: c.y - a.y, z: c.z - a.z };
  const v1 = { x: b.x - a.x, y: b.y - a.y, z: b.z - a.z };
  const v2 = { x: point.x - a.x, y: point.y - a.y, z: point.z - a.z };
  const dot00 = dot(v0, v0);
  const dot01 = dot(v0, v1);
  const dot02 = dot(v0, v2);
  const dot11 = dot(v1, v1);
  const dot12 = dot(v1, v2);
  const denom = dot00 * dot11 - dot01 * dot01;
  if (Math.abs(denom) < 1e-8) return false;
  const inv = 1 / denom;
  const u = (dot11 * dot02 - dot01 * dot12) * inv;
  const v = (dot00 * dot12 - dot01 * dot02) * inv;
  return u >= -1e-4 && v >= -1e-4 && u + v <= 1.0001;
}

function horizontalNormal(normal: Vec3): { x: number; z: number } | null {
  const length = Math.hypot(normal.x, normal.z);
  if (length < 1e-5) return null;
  return { x: normal.x / length, z: normal.z / length };
}

function dot(a: Vec3, b: Vec3): number {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// re-export for combat.ts convenience
export { setState as _setState };
