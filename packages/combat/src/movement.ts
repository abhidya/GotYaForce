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
import type { BorgRuntime, PlayerInput } from "./types.js";

export interface MoveContext {
  /** Resolved lock-on target position, if locked (face toward it). */
  lockTargetPos: Vec3 | null;
  bounds: { x: number; z: number };
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

  // Ground clamp.
  if (b.pos.y <= JUMP.GROUND_Y) {
    b.pos.y = JUMP.GROUND_Y;
    if (b.vel.y < 0) b.vel.y = 0;
    if (!b.grounded) onLand(b, p);
    b.grounded = true;
  } else {
    b.grounded = false;
  }

  // Bounds clamp on XZ.
  b.pos.x = clamp(b.pos.x, -ctx.bounds.x, ctx.bounds.x);
  b.pos.z = clamp(b.pos.z, -ctx.bounds.z, ctx.bounds.z);

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

// re-export for combat.ts convenience
export { setState as _setState };
