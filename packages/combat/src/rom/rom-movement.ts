// ROM-faithful port of zz_001d058_ @0x8001d058 (chunk_0002.c:4017) — the MOVEMENT state
// machine that wraps FUN_80024dec (stick-toward-target) + zz_0024d1c_ (stick apply) for
// CPU borg steering. Source: research/decomp/ghidra-export/chunk_0002.c:4017-4161.
//
// High-level structure (matching the ROM):
//   1. HEIGHT GATE — abandon approach if self.y <= target.y - FLOAT_80436e20 (500.0).
//      (chunk_0002.c:4028-4031 — the param_1[0x352]==8 + 0x358 ref-Y check; this port
//      collapses 0x352 to the sub-state machine and uses target.y as the ref Y.)
//   2. IDLE TIMER decrement (+0x328 short, chunk_0002.c:4057).
//   3. SUB-STATE MACHINE (+0x2e5 byte, chunk_0002.c:4058-4116):
//        0 IDLE     → grounded? ARRIVED; else APPROACH (+0x34c seeded to 60).
//        1 APPROACH → decrement +0x34c; slope-ahead check (FUN_8003d964 +
//                     zz_003f320_) → ARRIVED if cliff, else keep approaching +
//                     request jump (bit 0x100 in +0x5b4); on approach+idle timer
//                     expiry, retarget (zz_0023bf4_/zz_002104c_).
//        2 ARRIVED  → on idle timer expiry, retarget + restart.
//      Stick (computed by FUN_80024dec as (sin(rel), -cos(rel)) × FLOAT_80436e60=54.0
//      where rel = targetYaw - facingYaw) is applied each non-ARRIVED frame via
//      zz_0024d1c_ mode-1 (× FLOAT_80436ea4 = 0.8).
//
// Port mapping: FUN_80024dec produces a WORLD-space direction-toward-target stick.
// The port's stepMovement (movement.ts:resolveHorizontalIntent) decomposes the input
// through the lock frame (lockPos=target.pos for AI borgs — combat.ts:auto-lock), so
// we emit the SAME world-space direction × STICK_SCALE. The decomposition projects it
// back into the lock frame each frame, which (because lockPos=target.pos) walks the
// borg toward target along the lock vector's projection — matching the ROM's
// facing-relative stick after the heading-turn lag the lock system performs. See
// romAi.ts header for the wider port mapping notes.

/** FLOAT_80436e60 — s8 stick magnitude (FUN_80024dec: stick = sin/cos × 54). */
export const STICK_MAGNITUDE = 54.0;
/** FLOAT_80436ea4 — zz_0024d1c_ mode-1 stick scale. */
export const STICK_SCALE = 0.8;
/** FLOAT_80436e20 — height gate: stop approaching if too far below target. */
export const HEIGHT_GATE = 500.0;
/** FLOAT_80436e24 — slope/terrain factor (FUN_8003d964 / zz_003f320_ threshold). */
export const SLOPE_FACTOR = 3.0;
/** Approach-timer seed (chunk_0002.c:4098-4099 — +0x34c byte:=0, +0x34d byte:='<'=0x3c;
 *  big-endian short = 0x003c = 60). Frames the APPROACH sub-state runs before retarget. */
export const APPROACH_TIMER_SEED = 60;
/** Vertical delta (port-side) that triggers the slope/climb jump request while
 *  APPROACHing. The ROM's exact comparator (FUN_8003d964 + 0x36c offset + SLOPE_FACTOR
 *  probe) is terrain-mesh-dependent; this is the port-side stand-in sized to match the
 *  previous heuristic (romAi.ts line 306: target.y - self.y > 40). */
export const CLIMB_JUMP_DELTA = 40;

/**
 * Per-borg AI movement scratch — the actor's +0x2e5/+0x34c block. The +0x328 idle timer
 * is owned by the brain (RomAiState.idleTimer) so attack pacing and movement pacing share
 * the same countdown exactly as in the ROM.
 */
export interface RomMovementState {
  /** +0x2e5: movement sub-state — 0=IDLE, 1=APPROACH, 2=ARRIVED. */
  subState: 0 | 1 | 2;
  /** +0x34c: approach timer (frames remaining before forced retarget while approaching). */
  approachTimer: number;
  /** Cached world-space stick components (FUN_80024dec output, the s8 stick at +0x337/+0x338).
   *  Recomputed each frame from the current self→target vector. */
  stickX: number;
  stickZ: number;
}

export function createRomMovementState(): RomMovementState {
  return { subState: 0, approachTimer: 0, stickX: 0, stickZ: 0 };
}

export interface RomMovementFrame {
  /** XZ distance from self to target (already computed by the brain). */
  dist: number;
  /** Range at which the borg considers itself arrived (the brain's `desired` window). */
  desiredRange: number;
  /** Dead-band half-width around `desiredRange` (the brain's `kiteSlack`). */
  rangeSlack: number;
}

export interface RomMovementOutput {
  /** Stick X (world-space, toward-target × STICK_SCALE). */
  moveX: number;
  /** Stick Z (world-space, toward-target × STICK_SCALE). */
  moveZ: number;
  /** True when the borg should jump (chunk_0002.c:4072-4074 sets bit 0x100 in +0x5b4). */
  wantJump: boolean;
  /** True when the state machine requests retarget + sub-state restart
   *  (chunk_0002.c:4075-4078 calls zz_0023bf4_ + zz_002104c_). */
  retarget: boolean;
}

/**
 * One frame of zz_001d058_. Mutates `state`; pure against `self`/`target`.
 *
 * @param self        The borg (pos + grounded flag).
 * @param state       Per-borg movement scratch (subState + approachTimer).
 * @param target      Target position (the brain's currently-selected enemy).
 * @param frame       Range-frame info (dist + desired + slack).
 * @param idleTimer   The brain's +0x328 idle timer (read-only here; brain decrements).
 */
export function stepRomMovement(
  self: { pos: { x: number; y: number; z: number }; grounded: boolean },
  state: RomMovementState,
  target: { pos: { x: number; y: number; z: number } },
  frame: RomMovementFrame,
  idleTimer: number,
): RomMovementOutput {
  const out: RomMovementOutput = { moveX: 0, moveZ: 0, wantJump: false, retarget: false };

  // HEIGHT GATE (chunk_0002.c:4028-4031): self.y <= ref.y - 500 → abandon.
  // The ROM resets param_1[0x352] to '\0' (idle); we collapse that to ARRIVED, which
  // forces retarget on idleTimer expiry and re-evaluates approach from scratch.
  if (self.pos.y <= target.pos.y - HEIGHT_GATE) {
    state.subState = 2;
  }

  const far = frame.dist > frame.desiredRange + frame.rangeSlack;
  const close = frame.dist < frame.desiredRange - frame.rangeSlack;

  // FUN_80024dec — compute the world-space stick toward target (chunk_0003.c:1163).
  // The ROM normalizes (targetPos - selfPos), scales by FLOAT_80436e60=54.0, and stores
  // as s8; zz_0024d1c_ mode-1 then multiplies by FLOAT_80436ea4=0.8. We collapse both
  // into a single world-space unit vector × STICK_SCALE.
  const dx = target.pos.x - self.pos.x;
  const dz = target.pos.z - self.pos.z;
  const dist = Math.hypot(dx, dz) || 1;
  state.stickX = (dx / dist) * STICK_SCALE;
  state.stickZ = (dz / dist) * STICK_SCALE;

  // The ROM's airborne-vs-grounded + slope-ahead probe decides sub-state transitions:
  //   IDLE     → ARRIVED if grounded; APPROACH if airborne (chunk_0002.c:4091-4103).
  //   APPROACH → ARRIVED if grounded/cliff; keep going + jump if slope blocks
  //              (chunk_0002.c:4059-4083).
  // The "airborne" branch there is the AI's air-approach-after-jump mode; for the port's
  // ground-movement policy we substitute the brain's range dead-band (far/close) —
  // far → APPROACH, inside the dead-band → ARRIVED. The climb/jump trigger is preserved
  // for vertical hops (target notably higher while grounded).
  //
  // PORT-SIDE GROUND GATE: the stick is applied only while grounded. The ROM's
  // facing-relative stick naturally tracks the actor's heading lag, which keeps the
  // borg walking along its current heading; the port's lock system snaps the borg's
  // facing directly at the target, so emitting the stick every frame (incl. airborne)
  // would beeline across gaps and off platforms. Gating on grounded matches the ROM's
  // "near-ground" requirement for the stick-apply path (FUN_8003d964 + 0x36c offset,
  // chunk_0002.c:4061-4083 TRUE branch) without needing the terrain mesh in this port.

  switch (state.subState) {
    case 0: { // IDLE — re-evaluate transition
      if (far) {
        state.subState = 1;
        state.approachTimer = APPROACH_TIMER_SEED;
      } else {
        state.subState = 2;
      }
      // Stick applied this frame (chunk_0002.c:4104-4109 calls zz_0024d1c_ mode-1),
      // but only while grounded (port-side gate above).
      if (self.grounded) {
        out.moveX = state.stickX;
        out.moveZ = state.stickZ;
      }
      break;
    }
    case 1: { // APPROACH
      state.approachTimer -= 1;
      if (!far && !close) {
        // Within the desired dead-band → ARRIVED.
        state.subState = 2;
      } else {
        // Slope/climb gate: target notably higher while grounded → request jump
        // (chunk_0002.c:4072-4074 sets bit 0x100 in +0x5b4).
        if (target.pos.y - self.pos.y > CLIMB_JUMP_DELTA) {
          out.wantJump = true;
        }
        // Both timers expired → retarget + restart (chunk_0002.c:4075-4078).
        if (state.approachTimer < 1 && idleTimer < 1) {
          out.retarget = true;
        }
        // Stick applied each APPROACH frame (chunk_0002.c:4084-4089). Airborne frames
        // keep the stick too — the ROM's air-approach mode steers mid-jump; the former
        // grounded-only gate (paired with the removed boost-hold port-ism) deadlocked
        // borgs into a stickless hover.
        out.moveX = state.stickX;
        out.moveZ = state.stickZ;
      }
      break;
    }
    case 2: { // ARRIVED — idle until the brain's idle timer expires.
      if (idleTimer < 1) {
        out.retarget = true;
      }
      break;
    }
  }

  return out;
}

/** Reset the movement sub-state machine after a retarget (matches zz_002104c_'s reset of
 *  +0x2e5=0 / +0x2e7=0 at chunk_0002.c:6520-6521). Caller invokes this when the brain
 *  picks a new target enemy. */
export function resetRomMovement(state: RomMovementState): void {
  state.subState = 0;
  state.approachTimer = 0;
}
