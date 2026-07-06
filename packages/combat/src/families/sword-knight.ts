// SWORD KNIGHT family (ctor 0x80073b70) — the fourth ROM-faithful family port.
// Covers pl0200 (SWORD KNIGHT), pl020a (NORMAL KNIGHT), pl020f (DEATH BORG GAMMA II):
// all three bind ctor 0x80073b70 (root dispatcher FUN_80073f3c via the ctor block-copy
// word @0x802d47b8[0]). Source:
//   research/decomp/ghidra-export/chunk_0010.c:1380-1777 (root FUN_80073f3c → action
//   table PTR_FUN_802d4820 → action 2 wrapper zz_00744fc_ → phase table
//   PTR_zz_007454c__802d486c = [zz_007454c_, zz_0074634_, zz_00746ec_, zz_00747a4_]).
//   research/decomp/cue-script-stream-decode-2026-07-04.md §"Second family" (validated).
//
// The X-special is a 4-phase LUNGE-AND-SLAM: phase 0 winds up (reposition ×0.95 from the
// lock target + arm a kind-3/kind-18 hitbox via g4 s0/s1), phase 1 holds the approach
// (motion ×0.95 per frame while the windup timer counts down), phase 2 is the active
// contact window (drift-corrects when the motion vector stays above 3.0), and phase 3
// recovers (steer-yaw ×0.9 decay + gravity + ground-check → idle). Only pl0200 wires
// command records to actionIndex 2 (pl020a/pl020f command tables only reach actions 0/1)
// but all three borgs share the family module + cue table since the ctor is identical.
//
// This is a BESPOKE phase machine — zz_007454c_ does its own PSVEC reposition + stream
// start; it does NOT delegate to zz_0177dd8_/zz_0178394_ or any engine in
// families/shared-engine.ts. Pattern follows gred.ts + star-hero.ts.

import type { RomActor } from "../rom/actor.js";
import {
  integratePhysics,
  vecSubtract,
  vecScale,
  vecAdd,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// Motion constants — every value read from boot.dol this session.
const SWORD_KNIGHT_X = {
  /** FLOAT_804377c8 — the velocity-zero sentinel written across +0x44/+0x48/+0x4c/+0x50
   *  during phase-0 windup (same constant the dash handler FUN_80073ff8 uses). */
  ZERO: 0.0,
  /** FLOAT_804377cc — action-stream playback rate (passed as r3 to zz_004beb8_). */
  STREAM_RATE: -1.0,
  /** FLOAT_804377e8 — phase-0 windup timer seed (copied into +0x558; phase 1 ticks it
   *  down by +0x1dc8 per frame). */
  WINDUP_TIMER: 20.0,
  /** FLOAT_804377ec — motion-scale for the PSVEC reposition (motion = (pos − target) ×
   *  0.95; pos += motion). Same value as G RED's G_CRASH RELPOS_SCALE. */
  REPOSITION_SCALE: 0.95,
  /** FLOAT_804377f0 — motion-magnitude threshold above which phase 2 calls the drift-
   *  correction helper zz_00b22f4_ (chunk_0010.c:1740-1743). */
  DRIFT_THRESHOLD: 3.0,
  /** FLOAT_804377f4 — phase-3 steer-yaw decay multiplier (+0x18da ×= 0.9 per frame). */
  ANGLE_DECAY: 0.9,
  /** FLOAT_804377d4 — phase-3 gravity parameter (FUN_80067310's r3). */
  GRAVITY: 1.0,
  /** Part mask passed to zz_004beb8_ / zz_004cd24_ (full 4-part body mask). */
  HIT_MASK: 0xf,
  /** Stream group 4 (charge/air-special axis — same as G RED + Star Hero). */
  STREAM_GROUP: 4,
  /** Ground stream slot (controlWord & 0x40 clear → slot 0, kind 3). */
  GROUND_SLOT: 0,
  /** Air stream slot (controlWord & 0x40 set → slot 1, kind 18). */
  AIR_SLOT: 1,
} as const;

/** The lock-target position the family handler reads at actor+0x5e8 (same field G RED's
 *  *  + Star Hero's handlers consume). */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

// ============================================================================
// Phase 0 — zz_007454c_ @ chunk_0010.c:1664. Windup: zero velocity, reposition ×0.95
// from the lock target, arm the kind-3/kind-18 hitbox via g4 s0/s1, seed the windup
// timer. The +0x540++ at line 1670 advances the phase cursor before the body runs.
// ============================================================================
function swordKnightXPhase0(actor: RomActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ (chunk_0010.c:1670)

  // Windup timer seed (chunk_0010.c:1671: +0x558 = FLOAT_804377e8 = 20.0).
  actor.handlerTimer = SWORD_KNIGHT_X.WINDUP_TIMER;

  // zz_006d144_(actor, 0xc0) + zz_006e1ac_(actor, 0xc0, 1) — turn-to-target helpers
  // (chunk_0010.c:1672-1673). The bridge pre-aims the actor via syncIn's lockYaw copy;
  // the in-handler facing is a no-op approximation here (matches the gred/star-hero port
  // stance: the host owns pre-move facing).

  // Zero the velocity scalars (chunk_0010.c:1674-1678: +0x50/+0x48/+0x4c/+0x44 = 0.0).
  actor.gravityCoeff = SWORD_KNIGHT_X.ZERO;
  actor.yVel = SWORD_KNIGHT_X.ZERO;
  actor.hDecel = SWORD_KNIGHT_X.ZERO;
  actor.hSpeed = SWORD_KNIGHT_X.ZERO;
  // Zero the yaw accumulators +0x80/+0x7e/+0x7c (chunk_0010.c:1679-1681). These aren't
  // surfaced as RomActor fields; they live in the family-local scratch the host streams.

  // Reposition: motion = (pos − lockTarget); motion ×= 0.95; pos += motion
  // (chunk_0010.c:1682-1685: PSVECSubtract → PSQUATScale → PSVECAdd). The 5% pull-back
  // from the target is the windup spacing shared with G RED's G Crash + Star Hero's dash.
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(SWORD_KNIGHT_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // zz_00679d0_(actor) — pre-step the velocity integrator once with the zeroed scalars
  // (chunk_0010.c:1686). No-op when all four scalars are 0; skipped.

  // Arm the kind-3/kind-18 hitbox: zz_004beb8_(STREAM_RATE, actor, 0xf, 4, slot, -1, -1)
  // where slot = (controlWord & 0x40) ? 1 : 0 (chunk_0010.c:1687-1688). g4 s0 → kind 3
  // [3,9] ground; g4 s1 → kind 18 [34,35] air (cue-script-stream-decode §"Second family").
  const slot = (actor.controlWord & 0x40) !== 0 ? SWORD_KNIGHT_X.AIR_SLOT : SWORD_KNIGHT_X.GROUND_SLOT;
  startStream(actor, SWORD_KNIGHT_X.HIT_MASK, SWORD_KNIGHT_X.STREAM_GROUP, slot, SWORD_KNIGHT_X.STREAM_RATE);
  actor.streamSlot = slot + 1; // +0x6ea++ (the post-stream cursor the ROM leaves behind)

  // +0x80c = FLOAT_804377c8 (chunk_0010.c:1689) — clear the in-special gravity override.
  // Not surfaced as a RomActor field; documented for fidelity.
  void ctx;
}

// ============================================================================
// Phase 1 — zz_0074634_ @ chunk_0010.c:1697. Approach: continue the ×0.95 motion decay,
// tick the stream (gated by +0x1b03), face the target, and advance to phase 2 when the
// windup timer hits 0 OR zz_006d144_ reports facing is complete.
// ============================================================================
function swordKnightXPhase1(actor: RomActor, ctx: StreamContext): void {
  // motion ×= 0.95; pos += motion (chunk_0010.c:1704-1705).
  vecScale(SWORD_KNIGHT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // zz_00679d0_(actor) — velocity integrator step (chunk_0010.c:1706). No-op with the
  // zeroed scalars from phase 0; the motion accumulator owns the movement this phase.

  // Tick the stream only while the family-local +0x1b03 flag is set
  // (chunk_0010.c:1707-1709). The bridge doesn't surface +0x1b03; we tick unconditionally
  // — the windup stream's hitbox isn't armed until later frames anyway, so an extra tick
  // is harmless and matches the kind-3/kind-18 arming cadence decoded from the stream.
  tickStream(actor, SWORD_KNIGHT_X.HIT_MASK, ctx);

  // zz_006e1ac_(actor, 0xc0, 1) — continue facing (chunk_0010.c:1710). Host-owned.

  // Timer tick: +0x558 -= +0x1dc8 (chunk_0010.c:1712-1713).
  actor.handlerTimer -= actor.dt;

  // Transition gate (chunk_1510.c:1714-1716): timer ≤ 0.0 OR zz_006d144_(0xc0) != 0.
  // The facing helper's non-zero return means "facing complete" — we treat the timer as
  // the authoritative gate since +0x6d144's completion flag isn't bridge-surfaced.
  if (actor.handlerTimer <= SWORD_KNIGHT_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
  }
}

// ============================================================================
// Phase 2 — zz_00746ec_ @ chunk_0010.c:1724. Active window: hold facing, continue the
// motion decay, tick the stream, and watch the contact flag. +0x1cef < 0 (a kind-3/18
// hit landed and its end-of-window op fired) → phase 3; else if the motion magnitude
// stays above 3.0, call the drift-correction helper zz_00b22f4_.
// ============================================================================
function swordKnightXPhase2(actor: RomActor, ctx: StreamContext): void {
  // zz_006d144_(0xc0) + zz_006e1ac_(0xc0, 1) — facing (chunk_0010.c:1729-1730). Host-owned.

  // motion ×= 0.95; pos += motion (chunk_0010.c:1731-1732).
  vecScale(SWORD_KNIGHT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // zz_00679d0_(actor) — integrator step (chunk_0010.c:1733).
  // zz_004cd24_(actor, 0xf) — advance the stream (chunk_0010.c:1734).
  tickStream(actor, SWORD_KNIGHT_X.HIT_MASK, ctx);

  // Contact-end branch (chunk_0010.c:1735-1738): +0x1cef < 0 → phase 3, and +0x50
  // reloads from the descriptor's +0x6c handler-data byte (the per-family gravityCoeff
  // restore — same pattern as Star Hero's endStarHeroDash + G RED's phase-2 exit).
  if (actor.contactP0 < 0) {
    actor.fbPhaseSlots[0] = 3;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
    return;
  }

  // Drift-correction branch (chunk_1510.c:1739-1744): motion magnitude > 3.0 → call
  // zz_00b22f4_(actor). That helper re-derives motion from the position error; without
  // it ported we approximate by leaving the existing ×0.95 decay to converge the motion
  // (labeled approximation — the threshold gate is documented but the helper isn't).
  const mag = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
  if (mag > SWORD_KNIGHT_X.DRIFT_THRESHOLD) {
    // zz_00b22f4_(actor) — TODO port if drift convergence proves visually off.
  }
}

// ============================================================================
// Phase 3 — zz_00747a4_ @ chunk_0010.c:1752. Recovery: steer-yaw ×= 0.9, integrate with
// gravity = 1.0, tick the stream, and on the wall-contact flag return to idle.
// ============================================================================
function swordKnightXPhase3(actor: RomActor, ctx: StreamContext): void {
  // +0x18da = (s16)(+0x18da × FLOAT_804377f4) — pure ×0.9 decay. The
  // CONCAT44(0x43300000, …) − DOUBLE_804377e0 pattern (chunk_1510.c:1759-1762) is GCC's
  // int→double coercion sentinel (DOUBLE_804377e0 == 0x4330000000000000 == 2^52), so the
  // expression is just `steerYaw * 0.9` — no base subtraction (unlike G RED's 176.0 term).
  actor.steerYaw = actor.steerYaw * SWORD_KNIGHT_X.ANGLE_DECAY;

  // FUN_80067310(GRAVITY, actor, +0x5ae) — full physics step with gravity (chunk_1510.c:1763).
  integratePhysics(SWORD_KNIGHT_X.GRAVITY, actor, actor.lockYaw);

  // zz_00677b0_(actor) — ground clamp check (chunk_1510.c:1764). The host's groundClamp
  // does this via the bridge; here we read the grounded flag the bridge syncs in.
  // zz_004cd24_(actor, 0xf) — advance the stream (chunk_1510.c:1765).
  tickStream(actor, SWORD_KNIGHT_X.HIT_MASK, ctx);

  // Wall/contact-end branch (chunk_1510.c:1766-1775): +0x1cee != 0 → clear +0x73f,
  // strip the action-mode bits (+0x5e0 &= ~3), and return to neutral via zz_006a474_
  // (grounded) or zz_006a5a4_ (airborne) — decomp-verified helpers in
  // shared-idle-return.ts (the old cue-7/cue-0 mapping here was refuted).
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    const grounded = (actor as RomActor & { grounded?: boolean }).grounded === true;
    if (grounded) {
      romGroundIdleReturn(actor);   // zz_006a474_ — upper cue 0 + velocity zeroing
    } else {
      romAirKnockoutReturn(actor);  // zz_006a5a4_ — upper cue 6
    }
  }
}

/** The X-special phase table (PTR_zz_007454c__802d486c, indexed by actor.fbPhaseSlots[0]). */
const X_PHASE_TABLE = [swordKnightXPhase0, swordKnightXPhase1, swordKnightXPhase2, swordKnightXPhase3];

/** zz_00744fc_ @ chunk_0010.c:1648 — the action-2 wrapper. Clears +0xcc when +0x541 is
 *  set (a one-shot entry flag; not bridge-surfaced) then dispatches the phase table. */
function swordKnightXHandler(actor: RomActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_80073f3c @ chunk_0010.c:1382 (the descriptor
// +0x4b4 virtual) → PTR_FUN_802d4820[actor+0x580]. Action 2 (X) is ported here; the
// other rows (0 = dash, 1 = B melee) wire in as their handlers port. Null entries fall
// through to the generic combat layer.
// ============================================================================

export interface SwordKnightFamilyCtx extends StreamContext {}

export function createSwordKnightRootAction(ctx: SwordKnightFamilyCtx): (actor: RomActor) => void {
  // PTR_FUN_802d4820 — action 2 (X-special lunge-and-slam) ported; 0/1/3/4 fall through.
  // (pl020a/pl020f command tables never reach action 2 — only pl0200's command records
  // map cue 44 → actionIndex 2 — but the family module is shared across all three borgs.)
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                       // 0: dash attack (FUN_80073f78) — TODO port
    null,                                       // 1: B melee (zz_00743d0_) — TODO port
    (actor) => swordKnightXHandler(actor, ctx), // 2: X-special (zz_00744fc_ → phase table)
    null,                                       // 3: — (no handler in this family's table)
    null,                                       // 4: — (no handler in this family's table)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned SWORD KNIGHT-family actor (pl0200/pl020a/pl020f). Wires
 *  the root action dispatcher and stamps the borg-number switch the phase handlers read. */
export function configureSwordKnightFamily(
  actor: RomActor,
  borgId: "pl0200" | "pl020a" | "pl020f",
  ctx: SwordKnightFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl0200" ? 0x200 : borgId === "pl020a" ? 0x20a : 0x20f;
  actor.rootAction = createSwordKnightRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
