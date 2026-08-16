// TELEPORT NINJA family (ctor 0x801456d4) — ROM-faithful port.
// @audit-ported pl0005 action=0 variants=0,1,2,3,4
// @audit-ported pl0009 action=0 variants=0,1,2,3,4
// @audit-ported pl0005 action=1 variants=0,1,2,3
// @audit-ported pl0009 action=1 variants=0,1,2,3
// @audit-ported pl0005 action=2 variants=0,1,2,3,4
// @audit-ported pl0009 action=2 variants=0,1,2,3,4
// @audit-ported pl0005 action=3 variants=0,1,2,3,4
// Covers pl0005 (TELEPORT NINJA, borg 0x005) and pl0009 (SWITCHING NINJA, borg 0x009).
// The ctor wires both borgs to the SAME vtable/anim banks/tables (only the +0x4b0
// descriptor differs), so one family module covers both.
//
// Root dispatcher FUN_80145924 @0x80145924 (chunk_0037.c):
//   `(*(code *)(&PTR_FUN_8033e4f4)[*(char *)(actor+0x580)])();`
// Action tables (per bespoke-port-work-queue.json — 8 tables, 28 fns / 3355 instrs):
//   action 0 table @0x8033e518 (3 sub-tables 0x8033e518/524/530, phase via +0x540)
//   action 1 table @0x8033e568/574 (teleport-strike melee, v0/v1 shared lunge +
//                                  v2 table A + v3/v4 table B) — PORTED HERE
//   action 2 table @0x8033e584/594 (X-special, borg-switched) — PORTED HERE
//   action 3 table @0x8033e5b4 (B-charge teleport-dash, 5 fns) — PORTED HERE
//
// This pass ports ACTION 0 (the teleport-approach + B-held combo loop) faithfully from
// FUN_801459f0/FUN_80145b00/FUN_80145bd8 (chunk_0037.c/0038.c), ACTION 1 (the
// teleport-strike melee) from FUN_80146560..FUN_80146c54 (chunk_0038.c), ACTION 2
// (the borg-switched X-special) from FUN_80146dcc..FUN_8014734c (chunk_0038.c), and
// ACTION 3 (the B-charge teleport-dash) from FUN_801474b4..FUN_80147924 (chunk_0038.c).
// Floats read from boot.dol (sdata2 @0x8043a2xx).
//
// Float constants (v2f-resolved from user-data/GG4E/disc/sys/boot.dol):
//   FLOAT_8043a2b8 = 0.0   zero-scalar (velocity/pose resets, accumulator80c clear)
//   FLOAT_8043a2bc = 30.0  action-0 ph0 +0x560 aim/approach timer seed
//   FLOAT_8043a2c0 = -1.0  zz_004beb8_ stream playback rate
//   FLOAT_8043a2c4 = 0.95  blink reposition + per-frame motion scale
//   FLOAT_8043a2c8 = 3.0   afterimage (zz_00b22f4_) motion-magnitude gate
//   FLOAT_8043a2cc = 20.0  action-0 ph0 slot-2 aim timer seed (FUN_80145e98 action-1 arm)
//   FLOAT_8043a2dc = 60.0  action-3 ph0 +0x558 seed (FUN_801474b4 B-charge window)

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, groundSnapRevert, resetPoseHousekeeping, stepAfterimage, stepPartTargetPitch, stepTargetYaw, toS16 } from "../rom/helpers.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";
import { createSharedMeleeLunge, type SharedLungeConfig } from "./shared-melee-lunge.js";

/** Borg numbers for the TELEPORT NINJA family. */
const TELEPORT_NINJA_BORG_NUMBERS: Record<string, number> = {
  pl0005: 0x005,
  pl0009: 0x009,
};

export type TeleportNinjaBorgId = "pl0005" | "pl0009";

/** Named spawner + helper addresses (the host resolves these via ctx hooks). */
export const TELEPORT_NINJA_SPAWNERS = {
  /** zz_007db5c_ @0x8007db5c — ninja-family shuriken spawner (table 0x802d6d68).
   *  TELEPORT NINJA shares the ninja shuriken record table; the per-borg type select
   *  (0x005/0x009 rows) is pending table 0x802d6d68 decode — see shurikenTypeFor. */
  SHURIKEN_SPAWNER_ADDR: 0x8007db5c,
  /** zz_006bf80_ @0x8006bf80 — target-visibility refresh (action-0 ph2 B-held loop). */
  VISIBILITY_REFRESH_ADDR: 0x8006bf80,
  /** zz_01464c0_ @0x801464c0 — action-0 ph1 transition tail (unsurfaced; TODO host hook). */
  PH1_TRANSITION_TAIL_ADDR: 0x801464c0,
} as const;

/** All DOL-read constants for the TELEPORT NINJA family (cited per FLOAT_8043a2xx). */
export const TELEPORT_NINJA = {
  /** FLOAT_8043a2b8 = 0.0 — zero-scalar (velocity/pose resets, accumulator80c clear). */
  ZERO: 0.0,
  /** FLOAT_8043a2bc = 30.0 — action-0 ph0 +0x560 aim/approach timer seed. */
  APPROACH_TIMER: 30.0,
  /** FLOAT_8043a2c0 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a2c4 = 0.95 — blink reposition + per-frame motion scale. */
  BLINK_SCALE: 0.95,
  /** FLOAT_8043a2c8 = 3.0 — afterimage (zz_00b22f4_) motion-magnitude gate. */
  AFTERIMAGE_GATE: 3.0,
  /** FLOAT_8043a2cc = 20.0 — action-0 ph0 slot-2 aim timer seed (FUN_80145e98). */
  SLOT2_AIM_TIMER: 20.0,
  /** FLOAT_8043a2d0 = 1.0 — action-3 ph3 gravity (FUN_80067310) + +0x55c re-seed. */
  GRAVITY: 1.0,
  /** FLOAT_8043a2d8 = 8.0 — action-3 exit +0x694 seed (air/ground). */
  EXIT_STATE_TIMER: 8.0,
  /** FLOAT_8043a2dc = 60.0 — action-3 ph0 +0x558 seed (FUN_801474b4 B-charge window). */
  BCHARGE_WINDOW: 60.0,
  /** FLOAT_8043a2e0 = 0.9 — action-3 ph4 +0x18da steerYaw decay (× 0.9). */
  STEER_DECAY: 0.9,
  /** FLOAT_8043a2e4 = 150.0 — action-1 proximity (not used by action 3). */
  A1_PROXIMITY: 150.0,
  /** FLOAT_8043a2e8 = 40.0 — action-3 ph3 +0x44 launch seed (B-charge dash speed). */
  LAUNCH_SPEED: 40.0,
  /** FLOAT_8043a2ec = 10.0 — action-3 ph2 +0x558 seed (post-contact window). */
  POST_CONTACT_WINDOW: 10.0,
  /** FLOAT_8043a2f0 = 4.0 — action-3 ph0 +0x558 init seed (FUN_80146dcc X-special). */
  A2_SETUP_TIMER: 4.0,
  /** FLOAT_8043a2f4 = 800.0 — action-3 ph0 X-special reposition scale (FUN_80146dcc). */
  A2_REPOSITION: 800.0,
  /** FLOAT_8043a2f8 = 50.0 — action-3 ph0 X-special far-target blink scale. */
  A2_BLINK_FAR: 50.0,
  /** FLOAT_8043a2fc = 16.0 — action-3 ph4 +0x694 seed (grounded exit). */
  EXIT_GROUND_STATE_TIMER: 16.0,
  /** FLOAT_8043a300 = 0.1 — action-3 ph3 +0x560 launch-progress step (FUN_80146f6c). */
  LAUNCH_PROGRESS_STEP: 0.1,
  /** FLOAT_8043a304 = 2.0 — action-3 ph3 +0x560 launch-progress re-seed (FUN_80146f6c). */
  LAUNCH_PROGRESS_RESET: 2.0,
  /** FLOAT_8043a308 = 15.0 — action-3 ph2 +0x560 launch-progress seed. */
  LAUNCH_PROGRESS_SEED: 15.0,
  /** FLOAT_8043a30c = 100.0 — action-3 ph2 launch speed coefficient. */
  LAUNCH_SPEED_COEFF: 100.0,
  /** +0x5e0 bits cleared at action-0 ph0 setup (FUN_801459f0: ~0xb0 mask). */
  PH0_CLEAR_MASK: 0xb0,
  /** +0x5e0 airborne/position-frozen bit (0x40). */
  AIRBORNE_BIT: 0x40,
  /** +0x5b4 B-held status bit (0x200). */
  B_HELD_BIT: 0x200,
  /** action-0 stream group (the teleport-approach choreography). */
  ACTION0_STREAM_GROUP: 2,
  /** action-3 stream group (B-charge teleport-dash). */
  ACTION3_STREAM_GROUP: 4,
  /** all-parts stream mask. */
  STREAM_MASK: 0xf,
  /** +0x272 action-3 flag bit 1 — hitbox-presentation arm (FUN_800061a8 host hook). */
  FLAG272_BIT1: 0x2,
  /** +0x272 action-3 flag bit 2 — launch commit (post-contact). */
  FLAG272_BIT2: 0x4,
  /** zz_00f036c_ SFX cue played at the action-3 launch commit (0xf2). */
  LAUNCH_CUE: 0xf2,
  // --- action 1 (teleport-strike melee) constants, chunk_0038.c:470-882 ---
  /** FLOAT_8043a2d8 = 8.0 — +0x144 seed when +0x1d9 & 0x10 (FUN_80146560 gate). */
  A1_144_SEED: 8.0,
  /** FLOAT_8043a2dc = 60.0 — action-1 v2 ph0 (0x80146640) +0x558 seed. */
  A1_PH0_TIMER: 60.0,
  /** FLOAT_8043a2bc = 30.0 — action-1 v2 ph1 (0x80146764) +0x558 re-seed. */
  A1_PH1_TIMER: 30.0,
  /** FLOAT_8043a2cc = 20.0 — action-1 v3 ph1 (0x80146af8) +0x558 re-seed. */
  A1_PH1_V3_TIMER: 20.0,
  /** FLOAT_8043a2e4 = 150.0 — action-1 v2 ph2 (0x80146888) range gate. */
  A1_RANGE_GATE: 150.0,
  /** FLOAT_8043a2e8 = 40.0 — action-1 v2 ph2 (0x80146bc4) launch speed coefficient. */
  A1_LAUNCH_SPEED: 40.0,
  /** FLOAT_8043a2ec = 10.0 — action-1 v2 ph3 (0x80146c54) +0x48 seed. */
  A1_PH3_YVEL: 10.0,
  /** FLOAT_8043a2f0 = 4.0 — action-1 v2 ph3 gravity (FUN_80067310). */
  A1_PH3_GRAVITY: 4.0,
  /** FLOAT_8043a2d0 = 1.0 — action-1 v2 ph3 exit +0x694 seed. */
  A1_PH3_EXIT: 1.0,
  /** action-1 v2 ph0 stream slot seed (+0x6ea = 4). */
  A1_PH0_STREAM_SLOT: 4,
  /** action-1 v3 ph0 stream slot (fixed 9, group 3). */
  A1_V3_STREAM_SLOT: 9,
  /** action-1 v2 stream group (3). */
  A1_STREAM_GROUP: 3,
  /** +0x1d9 & 0x30 — v2 ph3 hit-gate mask (FUN_80146c54:54-60). */
  A1_PH3_HIT_GATE_MASK: 0x30,
} as const;

export interface TeleportNinjaFamilyCtx extends StreamContext {
  /** FUN_80066838 / FUN_800668cc — target-in-range gate (range rows @ +0x868). Host
   *  hook; default true (no host → treat as in range) so the machine advances. */
  onRangeCheck?: (actor: RomActor, distance: number) => boolean;
}

/** Scratch mirrors for ROM offsets not first-class on RomActor. */
export interface TeleportNinjaScratch {
  /** +0x5aa: signed yaw-error snapshot read by ph0 to pick the approach slot. */
  tnYawErr5aa?: number;
  /** +0x6ec: action-0 stream-slot direction byte (0 or 2). */
  tnStreamDir6ec?: number;
  /** +0x6ed: action-0 stream-side byte (0 ground / 1 air). */
  tnStreamSide6ed?: number;
  /** +0x6ee: per-move stream-slot base (combo follow-up ++). */
  tnSlotBase6ee?: number;
  /** +0x560: action-0 ph1 approach sub-timer (FLOAT_8043a2bc seed). */
  tnApproachTimer560?: number;
  /** +0x272: action-3 hitbox-presentation flag word (bits 1/2 armed by the machine). */
  tnFlag272?: number;
  /** +0x55c: action-3 ph3 launch-progress timer (FLOAT_8043a2d0 seed; drained by dt). */
  tnLaunchTimer55c?: number;
  /** +0x560 (action-3): launch-progress value fed to FUN_8016c810 as its child-life
   *  param. Initialised to FLOAT_8043a308 (15.0), stepped −FLOAT_8043a2d0 per shot. */
  tnLaunchProgress?: number;
  /** +0x54a: action-3 ph2 X-special airborne latch (bit 0x40 = forced air slot). */
  tnXAirLatch54a?: number;
  /** +0x82: action-3 anim/slot byte (the ph0 stream-slot + 0x41 write). */
  tnAnim82?: number;
  /** +0x1d9: action-3 part hit-react byte (& 0x10 gates the exit-pose despawn). */
  tnPart1d9?: number;
  /** +0x1cf0: part-1 contact byte (action-3 ph3 arm gate). */
  tnContactP1?: number;
  /** +0x1d9: action-1 hit-gate byte (& 0x30 = v2 ph3 gate; & 0x10 = 0x144 seed). */
  tnHitGate1d9?: number;
  /** +0x144: action-1 +0x144 seed value (8.0 when +0x1d9 & 0x10; child-mask elsewhere). */
  tnChild144?: number;
  /** +0x764: live target distance mirror (v2 ph1 speed computation). */
  tnTargetDist764?: number;
  /** +0x7ce: state byte gate for action-0 v4 redirect (valkrie-style; unused here). */
  tnState7ce?: number;
}

type TnActor = RomActor & TeleportNinjaScratch;

function scratchOf(actor: RomActor): TnActor {
  return actor as TnActor;
}

/** +0x5e0 airborne = position-frozen bit set. */
function isAirborne(actor: RomActor): boolean {
  return (actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT) !== 0;
}

/** Shuriken record-select by borgNumber (table 0x802d6d68). The NORMAL NINJA row is
 *  borg 0x000 → type 0 (decomp-verified in ninja.ts). The TELEPORT NINJA rows (0x005/
 *  0x009) are NOT yet surfaced in the decomp transcriptions; default to type 0 and
 *  cite the table for a follow-up pass. Exported for the pending action-1/3 port. */
export function shurikenTypeFor(borgNumber: number): number {
  void borgNumber;
  // TODO(rom): decode table 0x802d6d68 rows for borg 0x005/0x009 to recover the exact
  // per-borg shuriken type (ninja.ts covers 0x000→0, 0x00a→3; the teleport rows pending).
  return 0;
}

// ============================================================================
// ACTION 0 — teleport approach + B-held combo loop.
//   phase table @0x8033e518 (phase via +0x540); dispatcher FUN_801459a8 @0x801459a8.
//   ph0 FUN_801459f0 (setup), ph1 FUN_80145b00 (approach tick), ph2 FUN_80145bd8 (active).
// ============================================================================

/** Phase 0 — setup. FUN_801459f0 @ chunk_0037.c (68 instrs). */
function action0Phase0Setup(actor: TnActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.tnApproachTimer560 = TELEPORT_NINJA.APPROACH_TIMER; // +0x560 = 30.0 (FLOAT_8043a2bc)
  // zz_006d0dc_(actor, 0xc1, 0) — aim yaw toward target.
  stepTargetYaw(actor, 0xc1, 0);
  // Slot pick: +0x5aa < 1 → side 0 / slot 0; else side 1 / slot 2 (FUN_801459f0:18-26).
  const yawErr = actor.tnYawErr5aa ?? actor.turnErrorYaw;
  let slot: number;
  if (yawErr < 1) {
    slot = 0;
    actor.tnStreamSide6ed = 0; // +0x6ed = 0
  } else {
    slot = 2;
    actor.tnStreamSide6ed = 1; // +0x6ed = 1
  }
  actor.tnStreamDir6ec = slot; // +0x6ec = slot
  // zz_004beb8_(rate=-1, actor, 0xf, group=2, slot+0x6ee, -1, -1) — arm approach stream.
  const base = actor.tnSlotBase6ee ?? 0;
  startStream(
    actor,
    TELEPORT_NINJA.STREAM_MASK,
    TELEPORT_NINJA.ACTION0_STREAM_GROUP,
    slot + base,
    TELEPORT_NINJA.STREAM_RATE,
  );
  // +0x5e0 &= ~0xb0 (clear bits 0x10/0x20/0x80 — FUN_801459f0:31).
  actor.controlWord &= ~TELEPORT_NINJA.PH0_CLEAR_MASK;
  // Zero the four velocity scalars + pose accum (FLOAT_8043a2b8 = 0.0).
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
  // Blink reposition: motion = pos − targetCache5e8; motion ×= 0.95; pos += motion.
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor); // zz_00679d0_
  actor.accumulator80c = TELEPORT_NINJA.ZERO; // +0x80c = 0.0 (FLOAT_8043a2b8)
}

/** Phase 1 — approach tick. FUN_80145b00 @ chunk_0038.c (54 instrs). */
function action0Phase1Approach(actor: TnActor, ctx: StreamContext): void {
  // zz_004cd24_ only when +0x1cef == 0 (no active part-0 contact this frame).
  if (actor.contactP0 === 0) tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  // zz_006d0dc_(0xc1, 0) — continue aim; returns nonzero once converged.
  const converged = stepTargetYaw(actor, 0xc1, 0);
  const t = (actor.tnApproachTimer560 ?? 0) - actor.dt;
  if (!converged) {
    actor.tnApproachTimer560 = t; // +0x560 -= dt
    if (TELEPORT_NINJA.ZERO < t) {
      // Timer still running → continue the approach drift (LAB_80145b80 tail).
      driftAndAfterimage(actor);
      return;
    }
  }
  // Converged OR timer expired: if +0x1cef still 0, advance +0x540 and run the
  // transition tail zz_01464c0_ (unsurfaced host hook @0x801464c0).
  if (actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    // TODO(rom): zz_01464c0_ @0x801464c0 (the ph1→ph2 transition tail) is unsurfaced;
    // its effect on +0x18da/+0x1dfc aim accumulators is host-owned. No port-side effect.
    void TELEPORT_NINJA_SPAWNERS.PH1_TRANSITION_TAIL_ADDR;
  }
  driftAndAfterimage(actor);
}

/** LAB_80145b80 tail: motion ×= 0.95; pos += motion; ground snap; afterimage if |m| > 3. */
function driftAndAfterimage(actor: TnActor): void {
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  const mag = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
  if (mag > TELEPORT_NINJA.AFTERIMAGE_GATE) {
    stepAfterimage(actor); // zz_00b22f4_
  }
}

/** Phase 2 — active frames / B-held combo loop. FUN_80145bd8 @ chunk_0038.c (161 instrs).
 *  Condensed faithful port: the handlerTimer(+0x558) gate, the B-held(+0x5b4 &0x200) +
 *  ammo(zz_006dbe0_(0,1,0) check-only) combo loop, the airborne re-dispatch, and the
 *  wallContact(+0x1cee) → ground-idle-return exit. The stream-slot direction re-arm
 *  (the +0x1cf2 / +0x1dfc-sign branch) is host-stream-owned and cited as TODO. */
function action0Phase2Active(actor: TnActor, ctx: StreamContext): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    // Window expired: B-held + ammo still available → loop; else fall through to exit probe.
    const bHeld = (actor.statusWord5b4 & TELEPORT_NINJA.B_HELD_BIT) !== 0;
    if (bHeld && allocateWeapon(actor, ctx, 0, 1, false)) {
      // zz_006dbe0_(actor,0,1,0) — check-only (consume=false). Ammo ok → continue combo.
      if (isAirborne(actor)) {
        // Airborne: zz_006a3d0_(actor, 0, 3, 0) — command re-issue (bridge-owned).
        // Modeled as the cue-44 attack re-dispatch so the family re-enters state 61.
        dispatchFullBodyCue(actor, 0x2c);
        return;
      }
      // Grounded: zz_006bf80_(visibility refresh) + +0x540-- (loop back to ph1).
      ctx.onRefreshTargetVisibility?.(actor);
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1;
      // The stream-slot direction re-arm reads the sign of +0x1dfc (aimRoll1dfc) and the
      // +0x6ed side byte; the stream VM owns slot resolution, so this is a host concern.
      // TODO(rom): wire the +0x1dfc-sign → +0x6ec/+0x6ed stream re-arm once the aim-roll
      // accumulator is surfaced (FUN_80145bd8:45-62, chunk_0038.c).
      return;
    }
  } else {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
  }
  // No active hit this frame: drift + afterimage while no wallContact.
  if (actor.wallContact === 0) {
    driftAndAfterimage(actor);
    return;
  }
  // wallContact (+0x1cee != 0) → exit: +0x73f=0; +0x5e0&=~3; zz_006a474_(ground idle return).
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;
  romGroundIdleReturn(actor);
}

// ----------------------------------------------------------------------------
// ACTION 1 — teleport-strike melee (variant tables @0x8033e568/574). PORTED from
// chunk_0038.c:470-882. Dispatcher: root PTR_FUN_8033e4f4[1] = FUN_80146560 →
// PTR_FUN_8033e53c[+0x581] (variant). Variant routing:
//   v0/v1 → FUN_801465b0: +0x18da >>= 1, then shared lunge zz_00fed6c_
//           (config @0x8033e550 — see TELEPORT_LUNGE_CONFIG).
//   v2     → FUN_801465e4: +0x18da >>= 1, clear +0xcc if +0x541, then phase
//           table A @0x8033e568 (7 phases via +0x540).
//   v3/v4  → FUN_8014697c: clear +0xcc if +0x541, then phase table B @0x8033e574
//           (4 phases: FUN_801469cc/6af8/6bc4/6c54 — the second segment of the
//           two-segment strike).
// Root gate: if (+0x1d9 & 0x10) +0x144 = FLOAT_8043a2d8 (8.0).
//
// Phase table A (v2): [0x80146640, 0x80146764, 0x80146888, 0x801469cc,
//                      0x80146af8, 0x80146bc4, 0x80146c54]
// Phase table B (v3): [0x801469cc, 0x80146af8, 0x80146bc4, 0x80146c54]
//   ph0 0x80146640/0x801469cc — setup: stream slot, face, blink, zero scalars
//   ph1 0x80146764/0x80146af8 — approach: drift + stream tick + speed commit
//   ph2 0x80146888/0x80146bc4 — active/contact: range gate / launch commit
//   ph3 0x80146c54 — recovery: +0x18da decay, hit-gate scalars, gravity, exit
// ----------------------------------------------------------------------------

/** Shared-lunge config @0x8033e550 for action-1 v0/v1 (DOL dump:
 *  00000001 43160000 00000014 3f733333 3f733333 3f4ccccd). */
export const TELEPORT_LUNGE_CONFIG: SharedLungeConfig = {
  slotBase: 1,
  range: 150.0,
  dashFrames: 20,
  decelA: 0.949999988079071,
  decelB: 0.949999988079071,
  decelC: 0.800000011920929,
};

/** v2 ph0 — FUN_80146640 @ chunk_0038.c:470. Setup + first approach stream. */
function tnStrikeV2Phase0(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.streamSlot = TELEPORT_NINJA.A1_PH0_STREAM_SLOT;     // +0x6ea = 4
  if (!tnXRangeGate(actor, ctx)) {
    actor.fbPhaseSlots[1] = 1;      // +0x541
    actor.visibilityTarget = null;  // +0xcc = 0
    actor.activeYaw = actor.lockYaw; // +0x5ac = +0x5ae
  }
  actor.handlerTimer = TELEPORT_NINJA.A1_PH0_TIMER;          // +0x558 = 60.0
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  resetPoseHousekeeping(actor);
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  startStream(actor, TELEPORT_NINJA.STREAM_MASK, TELEPORT_NINJA.A1_STREAM_GROUP,
    TELEPORT_NINJA.A1_PH0_STREAM_SLOT, TELEPORT_NINJA.STREAM_RATE);
}

/** v2 ph1 — FUN_80146764 @ chunk_0038.c:509. Approach drift + speed commit. */
function tnStrikeV2Phase1(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.streamHold1b03 !== 0) tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  actor.handlerTimer -= actor.dt;
  const faced = stepTargetYaw(actor, 0xc0);
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO || faced) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = TELEPORT_NINJA.A1_PH1_TIMER;         // +0x558 = 30.0
    const row = actor.actionSpeedRows[(actor.cmdButton ?? 0) % 3] ?? TELEPORT_NINJA.A1_PH1_TIMER;
    let speed = row / TELEPORT_NINJA.A1_PH1_TIMER;
    const targetDist = (actor as TnActor).tnTargetDist764;
    if ((actor.visibilityTarget !== null || (actor as TnActor).tnTargetDist764 !== undefined)
        && targetDist !== undefined && row < targetDist) {
      speed = targetDist / TELEPORT_NINJA.A1_PH1_TIMER;
    }
    actor.hSpeed = speed;
    if (TELEPORT_NINJA.A1_RANGE_GATE < (targetDist ?? Infinity)) {
      ctx.onFamilyProjectile?.(actor, 0x800b2190, 0); // zz_00b2190_(0) afterimage
    }
  }
}

/** v2 ph2 — FUN_80146888 @ chunk_0038.c:546. Active: stream + range gate + exit. */
function tnStrikeV2Phase2(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  if (actor.faceGate1d10 > 0) stepTargetYaw(actor, 0xc0);
  actor.hSpeed *= TELEPORT_NINJA.BLINK_SCALE; // zz_006ed8c_(0.95)
  actor.yVel *= TELEPORT_NINJA.BLINK_SCALE;
  if (tnXRangeGate(actor, ctx)) {
    actor.hSpeed = TELEPORT_NINJA.ZERO; // +0x44 = 0
  }
  integratePhysics(TELEPORT_NINJA.GRAVITY, actor, actor.lockYaw); // zz_00670dc_ ground
  if (actor.dashStrength1d0f > 0) {
    actor.dashStrength1d0f = 0;
    const row = actor.actionSpeedRows[(actor.cmdButton ?? 0) % 3] ?? TELEPORT_NINJA.A1_PH1_TIMER;
    actor.hSpeed = row / TELEPORT_NINJA.A1_PH1_TIMER;
  }
  if (actor.wallContact !== 0) { // +0x1cee
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor); // zz_006a474_
  }
}

/** v2/v3 shared ph0 — FUN_801469cc @ chunk_0038.c:592. Second-segment setup. */
function tnStrikeSharedPhase0(actor: TnActor, ctx: TeleportNinjaFamilyCtx, isV2: boolean): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = TELEPORT_NINJA.A1_PH0_TIMER;         // +0x558 = 60.0
  if (!tnXRangeGate(actor, ctx)) {
    actor.fbPhaseSlots[1] = 1;
    actor.visibilityTarget = null;
    actor.activeYaw = actor.heading;   // +0x5ac = +0x72
  }
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  resetPoseHousekeeping(actor);
  stepTargetYaw(actor, 0xc0);       // zz_006d144_(0xc0)
  stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  const slot = isV2 ? TELEPORT_NINJA.A1_PH0_STREAM_SLOT + 5 : TELEPORT_NINJA.A1_V3_STREAM_SLOT;
  startStream(actor, TELEPORT_NINJA.STREAM_MASK, TELEPORT_NINJA.A1_STREAM_GROUP, slot,
    TELEPORT_NINJA.STREAM_RATE);
}

/** v2/v3 shared ph1 — FUN_80146af8 @ chunk_0038.c:632. Approach + pitch + commit. */
function tnStrikeSharedPhase1(actor: TnActor, ctx: TeleportNinjaFamilyCtx, isV2: boolean): void {
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.streamHold1b03 !== 0) tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
  actor.handlerTimer -= actor.dt;
  const faced = stepTargetYaw(actor, 0xc0);
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO || faced) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = isV2 ? TELEPORT_NINJA.A1_PH1_TIMER : TELEPORT_NINJA.A1_PH1_V3_TIMER;
    ctx.onFamilyProjectile?.(actor, 0x80092dcc, 0); // zz_0092dcc_(0) — FX child
  }
}

/** v2/v3 shared ph2 — FUN_80146bc4 @ chunk_0038.c:662. Contact → launch commit. */
function tnStrikeSharedPhase2(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  stepTargetYaw(actor, 0xc0);
  stepPartTargetPitch(actor, 0xc0);
  if (actor.contactP0 !== 0) { // +0x1cef
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    const yaw = actor.steerYaw; // +0x18da
    actor.hSpeed = TELEPORT_NINJA.A1_LAUNCH_SPEED * projectZ(yaw); // 40·cos
    actor.yVel = TELEPORT_NINJA.A1_LAUNCH_SPEED * -projectX(yaw); // 40·−sin
  }
}

/** v2/v3 shared ph3 — FUN_80146c54 @ chunk_0038.c:684. Recovery + exit. */
function tnStrikeSharedPhase3(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  if (actor.contactP0 < 0) actor.steerYaw = toS16(actor.steerYaw) >> 1; // +0x18da >> 1
  if (((s.tnHitGate1d9 ?? 0) & TELEPORT_NINJA.A1_PH3_HIT_GATE_MASK) !== 0) {
    actor.hSpeed = TELEPORT_NINJA.ZERO;
    actor.hDecel = TELEPORT_NINJA.ZERO;
    actor.yVel = TELEPORT_NINJA.A1_PH3_YVEL;        // +0x48 = 10.0
    actor.gravityCoeff = TELEPORT_NINJA.STREAM_RATE; // +0x50 = -1.0
  }
  integratePhysics(TELEPORT_NINJA.A1_PH3_GRAVITY, actor, actor.lockYaw); // FUN_80067310(4.0)
  const grounded = groundSnapRevert(actor);
  if (grounded && actor.contactP0 < 0) {
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = TELEPORT_NINJA.A1_144_SEED + actor.dt; // +0x694 = 8+dt
    return;
  }
  if (actor.wallContact !== 0) { // +0x1cee
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    if (!grounded) romAirKnockoutReturn(actor); // zz_006a5a4_
    else romGroundIdleReturn(actor);
    actor.stateTimer = TELEPORT_NINJA.A1_PH3_EXIT + actor.dt; // +0x694 = 1+dt
  }
}

/** Action-1 root — FUN_80146560 → PTR_FUN_8033e53c[+0x581]. */
function tnStrikeHandler(
  actor: TnActor,
  ctx: TeleportNinjaFamilyCtx,
  sharedLunge: (actor: RomActor) => void,
): void {
  const s = actor as TnActor;
  if (((s.tnHitGate1d9 ?? 0) & 0x10) !== 0) s.tnChild144 = TELEPORT_NINJA.A1_144_SEED;
  const v = actor.variantIndex;
  if (v === 0 || v === 1) {
    // FUN_801465b0: +0x18da >>= 1 then shared lunge zz_00fed6c_ (config @0x8033e550).
    actor.steerYaw = toS16(actor.steerYaw) >> 1;
    sharedLunge(actor);
    return;
  }
  if (v === 2) {
    // FUN_801465e4: +0x18da >>= 1, clear +0xcc if +0x541, then table A.
    actor.steerYaw = toS16(actor.steerYaw) >> 1;
    if (actor.fbPhaseSlots[1] !== 0) actor.visibilityTarget = null;
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: tnStrikeV2Phase0(actor, ctx); break;
      case 1: tnStrikeV2Phase1(actor, ctx); break;
      case 2: tnStrikeV2Phase2(actor, ctx); break;
      case 3: tnStrikeSharedPhase0(actor, ctx, true); break;
      case 4: tnStrikeSharedPhase1(actor, ctx, true); break;
      case 5: tnStrikeSharedPhase2(actor, ctx); break;
      case 6: tnStrikeSharedPhase3(actor, ctx); break;
      default: break;
    }
    return;
  }
  // v3/v4 — FUN_8014697c: clear +0xcc if +0x541, then table B (4-phase second segment).
  if (actor.fbPhaseSlots[1] !== 0) actor.visibilityTarget = null;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: tnStrikeSharedPhase0(actor, ctx, false); break;
    case 1: tnStrikeSharedPhase1(actor, ctx, false); break;
    case 2: tnStrikeSharedPhase2(actor, ctx); break;
    case 3: tnStrikeSharedPhase3(actor, ctx); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// ACTION 3 — B-charge teleport-dash (table @0x8033e5b4, 5 fns). PORTED from
// chunk_0038.c:1028-1233. Dispatcher: root PTR_FUN_8033e4f4[3] = FUN_80147428 →
// PTR_FUN_8033e5a0[+0x581] (all 5 variants route to FUN_80147464) →
// PTR_FUN_8033e5b4[+0x540]. Phase cursor = fbPhaseSlots[0].
//   ph0 0x801474b4 setup — range gate, face, blink, stream slot 0 (ground) / 2 (air)
//   ph1 0x801475f8 approach — drift + stream tick + pitch seek; advance on timer/face
//   ph2 0x801476b0 contact — arm hitbox (+0x272|=2) on +0x1cf0; on +0x1cee commit
//       launch: +0x558=10, +0x55c=1, +0x560=15, hSpeed=100·cos(steerYaw),
//       yVel=100·−sin(steerYaw) (zz_0045238_/zz_0045204_ = projectZ/projectX),
//       +0x272|=4, afterimage, +0x80c=0, +0x82=0, SFX 0xf2
//   ph3 0x801477e4 flurry — velocity drag 0.95, gravity 1.0, +0x55c drain → spawn
//       (FUN_8016c810 child, type 3), +0x560 step; +0x558 drain → exit anim arm
//   ph4 0x80147924 exit — +0x18da ×0.9 decay, +0x1d9&0x10 despawn, grounded/air exit
// ----------------------------------------------------------------------------

function tnXRangeGate(actor: TnActor, ctx: TeleportNinjaFamilyCtx): boolean {
  // FUN_80066838(range, actor): -1 no lock, 0 beyond, 1 in range. Rows at +0x868 are
  // the descriptor speed/range rows (cmdButton % 3). The port exposes the in-range
  // result through the same host hook cyber-hero uses; default true (no host → treat
  // as in range) so the machine advances deterministically in unit tests.
  const row = actor.actionSpeedRows[(actor.cmdButton ?? 0) % 3] ?? 0;
  if (ctx.onRangeCheck) return ctx.onRangeCheck(actor, row);
  return true;
}

/** ph0 — FUN_801474b4 @ chunk_0038.c:1028. */
function tnBChargePhase0(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = TELEPORT_NINJA.BCHARGE_WINDOW;       // +0x558 = 60.0
  // +0x6ea = 0; if (+0x5e0 & 0x40) +0x6ea = 2 (air stream slot).
  actor.streamSlot = (actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT) !== 0 ? 2 : 0;
  // FUN_80066838(range row) < 1 → +0x541 = 1; +0xcc = 0; +0x5ac = +0x72.
  if (!tnXRangeGate(actor, ctx)) {
    actor.fbPhaseSlots[1] = 1;
    actor.visibilityTarget = null;
    actor.activeYaw = actor.heading;
  }
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  resetPoseHousekeeping(actor);
  // Blink: motion = pos − targetCache5e8; motion ×= 0.95; pos += motion.
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor); // zz_00677b0_
  // +0x6ea++ (post-increment), then stream group 4, slot (old), args (6, 1).
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, TELEPORT_NINJA.STREAM_MASK, TELEPORT_NINJA.ACTION3_STREAM_GROUP, slot,
    TELEPORT_NINJA.STREAM_RATE);
}

/** ph1 — FUN_801475f8 @ chunk_0038.c:1075. */
function tnBChargePhase1(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  // Drift: motion ×= 0.95; pos += motion; ground snap.
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.streamHold1b03 !== 0) {
    tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx); // zz_004cd24_(0xf)
  }
  stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
  actor.handlerTimer -= actor.dt;    // +0x558 -= dt
  const faced = stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0) != 0
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO || faced) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

/** ph2 — FUN_801476b0 @ chunk_0038.c:1102. */
function tnBChargePhase2(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  stepTargetYaw(actor, 0xc0);      // zz_006d144_(0xc0)
  stepPartTargetPitch(actor, 0xc0); // zz_006e1ac_(0xc0, 1)
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  const s = actor as TnActor;
  if ((s.tnContactP1 ?? 0) !== 0) { // +0x1cf0 != 0
    s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT1;
    // FUN_800061a8(actor, 9) — host hitbox-presentation hook (flame-ninja convention: no-op).
  }
  if (actor.wallContact !== 0) { // +0x1cee != 0 → launch commit
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = TELEPORT_NINJA.POST_CONTACT_WINDOW;  // +0x558 = 10.0
    s.tnLaunchTimer55c = TELEPORT_NINJA.GRAVITY;              // +0x55c = 1.0
    s.tnLaunchProgress = TELEPORT_NINJA.LAUNCH_PROGRESS_SEED; // +0x560 = 15.0
    const yaw = actor.steerYaw; // +0x18da
    actor.hSpeed = TELEPORT_NINJA.LAUNCH_SPEED_COEFF * projectZ(yaw); // 100·cos
    actor.yVel = TELEPORT_NINJA.LAUNCH_SPEED_COEFF * -projectX(yaw); // 100·−sin
    actor.hDecel = TELEPORT_NINJA.ZERO;
    actor.gravityCoeff = TELEPORT_NINJA.ZERO;
    s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT2;
    stepAfterimage(actor); // zz_00b2190_(0)
    actor.accumulator80c = TELEPORT_NINJA.ZERO;
    s.tnAnim82 = 0;
    ctx.onPlayCue?.(actor, TELEPORT_NINJA.LAUNCH_CUE); // zz_00f036c_(0xf2)
  }
}

/** ph3 — FUN_801477e4 @ chunk_0038.c:1148. */
function tnBChargePhase3(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT1;
  s.tnAnim82 = 0;
  // zz_006ed8c_(0.95) — velocity drag.
  actor.hSpeed *= TELEPORT_NINJA.BLINK_SCALE;
  actor.yVel *= TELEPORT_NINJA.BLINK_SCALE;
  integratePhysics(TELEPORT_NINJA.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, +0x5ae)
  groundSnapRevert(actor);
  // +0x55c drain → spawn child (FUN_8016c810, type 3); +0x560 step.
  s.tnLaunchTimer55c = (s.tnLaunchTimer55c ?? 0) - actor.dt;
  if ((s.tnLaunchTimer55c ?? 0) <= TELEPORT_NINJA.ZERO) {
    // FUN_8016c810(+0x560, actor, 3, 0) — spawns the teleport-dash child.
    ctx.onFamilyProjectile?.(actor, 0x8016c810, 3);
    s.tnLaunchTimer55c = TELEPORT_NINJA.GRAVITY;
    s.tnLaunchProgress = (s.tnLaunchProgress ?? 0) - TELEPORT_NINJA.GRAVITY;
  }
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.hDecel = TELEPORT_NINJA.ZERO;
    actor.hSpeed = TELEPORT_NINJA.ZERO;
    actor.yVel = TELEPORT_NINJA.ZERO;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c; // +0x50
    s.tnFlag272 = 0;
    const slot = actor.streamSlot; // +0x6ea++
    actor.streamSlot = slot + 1;
    startStream(actor, TELEPORT_NINJA.STREAM_MASK, TELEPORT_NINJA.ACTION3_STREAM_GROUP, slot,
      TELEPORT_NINJA.STREAM_RATE);
    s.tnAnim82 = actor.carriedSlot96 + 0x41; // +0x82 = +0x96 + 'A'
    // FUN_800061a8(actor, 10) — host hitbox-presentation hook (no-op).
    ctx.onPlayCue?.(actor, TELEPORT_NINJA.LAUNCH_CUE); // zz_00f036c_(0xf2)
  }
}

/** ph4 — FUN_80147924 @ chunk_0038.c:1196. */
function tnBChargePhase4(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  // +0x18da = (short)((float)+0x18da × FLOAT_8043a2e0 (0.9)) — steerYaw decay.
  actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * TELEPORT_NINJA.STEER_DECAY);
  if (((s.tnPart1d9 ?? 0) & 0x10) !== 0) {
    // zz_00107a0_(actor, 0x10) — hitbox despawn (host hook; no-op).
  }
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  integratePhysics(TELEPORT_NINJA.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, +0x5ae)
  const grounded = groundSnapRevert(actor); // zz_00677b0_
  if (grounded && actor.contactP0 < 0) { // +0x1cef < 0 → grounded exit
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = TELEPORT_NINJA.EXIT_GROUND_STATE_TIMER + actor.dt; // +0x694 = 16+dt
    return;
  }
  if (actor.wallContact !== 0) { // +0x1cee != 0 → air/ground exit
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    actor.steerYaw = 0;
    if (grounded) {
      romGroundIdleReturn(actor); // zz_006a474_
    } else {
      romAirKnockoutReturn(actor); // zz_006a5a4_
    }
    actor.stateTimer = TELEPORT_NINJA.EXIT_STATE_TIMER + actor.dt; // +0x694 = 8+dt
  }
}

/** Action-3 root handler — FUN_80147428 → PTR_FUN_8033e5a0[variant] → FUN_80147464 →
 *  PTR_FUN_8033e5b4[+0x540]. All 5 variants route to the same phase machine. */
function tnBChargeHandler(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: tnBChargePhase0(actor, ctx); return;
    case 1: tnBChargePhase1(actor, ctx); return;
    case 2: tnBChargePhase2(actor, ctx); return;
    case 3: tnBChargePhase3(actor, ctx); return;
    case 4: tnBChargePhase4(actor, ctx); return;
    default: return;
  }
}

// ----------------------------------------------------------------------------
// ACTION 2 — X-special (borg-switched: borg 0x005 → table @0x8033e584,
// borg 0x009 → table @0x8033e594). PORTED from chunk_0038.c:754-999.
// Dispatcher: root PTR_FUN_8033e4f4[2] = FUN_80146d5c → borg switch →
//   pl0005 (0x005) → zz_0146d90_ → PTR_FUN_8033e584[+0x540]
//      [0x80146dcc, 0x80146ed8, 0x80146f6c, 0x80147094]  (4 phases)
//   pl0009 (0x009) → zz_0147130_ → PTR_FUN_8033e594[+0x540]
//      [0x80147180, 0x80147280, 0x8014734c]             (3 phases)
//
// pl0005 (TELEPORT NINJA) X — a blink-deploy: ph0 repositions (50.0 far /
// 800·scale aimed), ammo-gates slot 2, spawns the FX child; ph1/2 drift to
// the repositioned point (+0x82 anim arm, +0x272 flags); ph3 exits.
// pl0009 (SWITCHING NINJA) X — a ranged dash: ph0 faces + blinks, stream g4
// slot 4/5; ph1 contact (+0x1cef) ammo-gates slot 2 + borg-0x009-only child
// spawn (zz_01e29fc_); ph2 gravity + exit.
// ----------------------------------------------------------------------------

/** pl0005 X ph0 — FUN_80146dcc @ chunk_0038.c:754. Blink-deploy setup. */
function tnXTeleportPhase0(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.handlerTimer = TELEPORT_NINJA.A2_SETUP_TIMER;       // +0x558 = 4.0
  s.tnXAirLatch54a = actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT; // +0x54a = +0x5e0 & 0x40
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  const deployBlocked = (s.tnChild144 ?? 0) <= TELEPORT_NINJA.ZERO || actor.visibilityTarget === null;
  if (deployBlocked) {
    // Far blink: motion ×= FLOAT_8043a2f8 (50.0); pos += motion.
    vecScale(TELEPORT_NINJA.A2_BLINK_FAR, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  } else {
    // Aimed blink: motion = +0x518 − pos; normalize; ×= (FLOAT_8043a2f4 × +0xb4);
    // pos += motion; +0x54a = 0x40 (forced air).
    vecSubtract(actor.aimOrigin518, actor.pos, actor.motion);
    const mag = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
    if (mag > 1e-6) {
      actor.motion.x /= mag; actor.motion.y /= mag; actor.motion.z /= mag;
    }
    vecScale(TELEPORT_NINJA.A2_REPOSITION * actor.modelScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
    s.tnXAirLatch54a = TELEPORT_NINJA.AIRBORNE_BIT;
  }
  // zz_0066530_(0x2d) — host anim/event hook (no-op).
  if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
    ctx.onFamilyProjectile?.(actor, 0x80146ed8, 0); // zz_0146ed8_ — deploy child
  }
}

/** pl0005 X ph1 — zz_0146ed8_ @ chunk_0038.c:788. Drift + stream. */
function tnXTeleportPhase1(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT1;
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = TELEPORT_NINJA.EXIT_GROUND_STATE_TIMER; // +0x558 = 16.0
    ctx.onPlayCue?.(actor, TELEPORT_NINJA.LAUNCH_CUE); // zz_00f036c_(0xf2)
  }
}

/** pl0005 X ph2 — FUN_80146f6c @ chunk_0038.c:815. Aimed move + stream arm. */
function tnXTeleportPhase2(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT1;
  s.tnAnim82 = 0;
  // zz_0046588_(FLOAT_8043a300 × dt, +0x9c, pos, pos) — move toward +0x9c.
  const rate = TELEPORT_NINJA.LAUNCH_PROGRESS_STEP * actor.dt;
  actor.pos.x += (actor.motion.x - actor.pos.x) * rate;
  actor.pos.y += (actor.motion.y - actor.pos.y) * rate;
  actor.pos.z += (actor.motion.z - actor.pos.z) * rate;
  groundSnapRevert(actor);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = TELEPORT_NINJA.LAUNCH_PROGRESS_RESET; // +0x558 = 2.0
    actor.hDecel = TELEPORT_NINJA.ZERO;
    actor.hSpeed = TELEPORT_NINJA.ZERO;
    actor.yVel = TELEPORT_NINJA.ZERO;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
    s.tnAnim82 = actor.carriedSlot96 + 0x41; // +0x82 = +0x96 + 'A'
    const slot = (s.tnXAirLatch54a ?? 0) === 0 ? 0 : 0xd; // +0x54a == 0 → g0 s0, else g0 s0xd
    startStream(actor, TELEPORT_NINJA.STREAM_MASK, 0, slot, TELEPORT_NINJA.STREAM_RATE);
    ctx.onPlayCue?.(actor, TELEPORT_NINJA.LAUNCH_CUE);
  }
}

/** pl0005 X ph3 — FUN_80147094 @ chunk_0038.c:857. Exit. */
function tnXTeleportPhase3(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const s = actor as TnActor;
  s.tnFlag272 = (s.tnFlag272 ?? 0) | TELEPORT_NINJA.FLAG272_BIT1;
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= TELEPORT_NINJA.ZERO) {
    s.tnFlag272 = (s.tnFlag272 ?? 0) & ~TELEPORT_NINJA.FLAG272_BIT1;
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    if ((actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT) === 0) {
      romGroundIdleReturn(actor); // zz_006a474_
    } else {
      romAirKnockoutReturn(actor); // zz_006a5a4_
    }
  }
}

/** pl0009 X ph0 — FUN_80147180 @ chunk_0038.c:900. Ranged-dash setup. */
function tnXSwitchPhase0(actor: TnActor): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  if (actor.visibilityTarget === null) actor.activeYaw = actor.heading; // +0xcc == 0
  stepTargetYaw(actor, 0xc1); // zz_006d144_(0xc1)
  actor.gravityCoeff = TELEPORT_NINJA.ZERO;
  actor.yVel = TELEPORT_NINJA.ZERO;
  actor.hDecel = TELEPORT_NINJA.ZERO;
  actor.hSpeed = TELEPORT_NINJA.ZERO;
  resetPoseHousekeeping(actor);
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  actor.streamSlot = (actor.controlWord & TELEPORT_NINJA.AIRBORNE_BIT) !== 0 ? 5 : 4;
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, TELEPORT_NINJA.STREAM_MASK, TELEPORT_NINJA.ACTION3_STREAM_GROUP, slot,
    TELEPORT_NINJA.STREAM_RATE);
  actor.accumulator80c = TELEPORT_NINJA.ZERO;
}

/** pl0009 X ph1 — FUN_80147280 @ chunk_0038.c:941. Approach + contact spawn. */
function tnXSwitchPhase1(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  stepTargetYaw(actor, 0xc1);
  vecScale(TELEPORT_NINJA.BLINK_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);
  if (actor.contactP0 > 0) { // +0x1cef > 0
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(2,1,1)
      if (actor.borgNumber === 0x009) {
        ctx.onFamilyProjectile?.(actor, 0x801e29fc, 0); // zz_01e29fc_(0) — borg 0x009 child
      }
    }
  }
  if (Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z) > TELEPORT_NINJA.AFTERIMAGE_GATE) {
    stepAfterimage(actor); // zz_00b22f4_
  }
}

/** pl0009 X ph2 — FUN_8014734c @ chunk_0038.c:970. Gravity + exit. */
function tnXSwitchPhase2(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  tickStream(actor, TELEPORT_NINJA.STREAM_MASK, ctx);
  integratePhysics(TELEPORT_NINJA.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0)
  const grounded = groundSnapRevert(actor);
  if (grounded && actor.contactP0 < 0) { // +0x1cef < 0
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(7)
    actor.stateTimer = TELEPORT_NINJA.EXIT_STATE_TIMER + actor.dt; // +0x694 = 8+dt
    return;
  }
  if (actor.wallContact !== 0) { // +0x1cee
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    if (!grounded) romAirKnockoutReturn(actor);
    else romGroundIdleReturn(actor);
    actor.stateTimer = TELEPORT_NINJA.EXIT_STATE_TIMER + actor.dt;
  }
}

/** Action-2 root — FUN_80146d5c → borg-switched phase table. */
function tnXSpecialHandler(actor: TnActor, ctx: TeleportNinjaFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (actor.borgNumber === 0x009) {
    // zz_0147130_ → PTR_FUN_8033e594[+0x540] (3 phases).
    if (actor.fbPhaseSlots[1] !== 0) actor.visibilityTarget = null;
    switch (phase) {
      case 0: tnXSwitchPhase0(actor); break;
      case 1: tnXSwitchPhase1(actor, ctx); break;
      case 2: tnXSwitchPhase2(actor, ctx); break;
      default: break;
    }
    return;
  }
  // zz_0146d90_ → PTR_FUN_8033e584[+0x540] (4 phases).
  switch (phase) {
    case 0: tnXTeleportPhase0(actor, ctx); break;
    case 1: tnXTeleportPhase1(actor, ctx); break;
    case 2: tnXTeleportPhase2(actor, ctx); break;
    case 3: tnXTeleportPhase3(actor, ctx); break;
    default: break;
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher — FUN_80145924 indexes PTR_FUN_8033e4f4[+0x580]. All four
// player-command actions (0..3) are ported bespoke (or via the shared lunge for
// action-1 v0/v1); no action falls through to the generic layer.
// ----------------------------------------------------------------------------
export function createTeleportNinjaRootAction(
  ctx: TeleportNinjaFamilyCtx,
): (actor: RomActor) => void {
  // action 2 (X-special) — borg-switched bespoke tables @0x8033e584/594 (ported).
  const sharedX = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
  void sharedX;
  // action 1 v0/v1 — shared lunge zz_00fed6c_ (config @0x8033e550).
  const sharedLunge = createSharedMeleeLunge(TELEPORT_LUNGE_CONFIG, ctx);

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) action0Phase0Setup(actor);
        else if (phase === 1) action0Phase1Approach(actor, ctx);
        else if (phase >= 2) action0Phase2Active(actor, ctx);
        return;
      }
      case 1:
        tnStrikeHandler(actor, ctx, sharedLunge);
        return;
      case 2:
        tnXSpecialHandler(actor, ctx);
        return;
      case 3:
        tnBChargeHandler(actor, ctx);
        return;
      default:
        return;
    }
  };
}

/** Configure a freshly-spawned TELEPORT NINJA family actor (pl0005/pl0009). Stamps the
 *  per-borg number and wires the bespoke action-0 machine + shared-engine X. */
export function configureTeleportNinjaFamily(
  actor: RomActor,
  borgId: TeleportNinjaBorgId,
  ctx: TeleportNinjaFamilyCtx,
): void {
  actor.borgNumber = TELEPORT_NINJA_BORG_NUMBERS[borgId] ?? 0x005;
  actor.rootAction = createTeleportNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const TELEPORT_NINJA_CONSTANTS = TELEPORT_NINJA;

// ============================================================================
// Self-tests (mirror victory-king.ts / rom.selfcheck.ts style).
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function makeCtx(opts: {
  onAllocateResource?: () => boolean;
  onRefreshTargetVisibility?: () => void;
  onPlayCue?: () => void;
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
} = {}): TeleportNinjaFamilyCtx {
  const ctx: TeleportNinjaFamilyCtx = {};
  if (opts.onAllocateResource) ctx.onAllocateResource = () => opts.onAllocateResource!();
  if (opts.onRefreshTargetVisibility) {
    const sink = opts.onRefreshTargetVisibility;
    ctx.onRefreshTargetVisibility = () => sink();
  }
  if (opts.onPlayCue) ctx.onPlayCue = () => opts.onPlayCue!();
  if (opts.onFamilyProjectile) ctx.onFamilyProjectile = opts.onFamilyProjectile;
  return ctx;
}

export function runTeleportNinjaSelfTests(assert: AssertFn): void {
  // --- configure stamps borgNumber + wires bespoke rootAction for both borgs. ---
  for (const { id, num } of [
    { id: "pl0005" as const, num: 0x005 },
    { id: "pl0009" as const, num: 0x009 },
  ]) {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, id, makeCtx());
    assert(a.borgNumber === num, `${id} borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} bespoke rootAction wired`);
  }

  // --- action 0 ph0: advance +0x540, seed approach timer 30.0, zero scalars, blink. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action0 ph0 advances to ph1");
    assert(a.tnApproachTimer560 === TELEPORT_NINJA.APPROACH_TIMER,
      "action0 ph0 +0x560 = 30.0 (FLOAT_8043a2bc)");
    assert(
      a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0 && a.gravityCoeff === 0,
      "action0 ph0 zeroes all four velocity scalars (FLOAT_8043a2b8)",
    );
    assert(a.poseAccum7c === 0 && a.poseAccum7e === 0 && a.poseAccum80 === 0,
      "action0 ph0 clears pose accumulators");
    // Blink: motion = (100,0,0) × 0.95 = (95,0,0); pos += motion → x = 195.
    assert(a.pos.x === 195, "action0 ph0 blink: pos.x = 195 ((pos−target)×0.95 added)");
    assert(a.motion.x === 95, "action0 ph0 motion.x = 95 (×FLOAT_8043a2c4)");
    assert((a.controlWord & TELEPORT_NINJA.PH0_CLEAR_MASK) === 0,
      "action0 ph0 clears +0x5e0 bits 0xb0");
  }

  // --- action 0 ph0 slot pick: +0x5aa >= 1 → slot 2 / side 1. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0009", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.tnYawErr5aa = 5; // >= 1 → air-side slot
    root(a); // ph0
    assert(a.tnStreamDir6ec === 2 && a.tnStreamSide6ed === 1,
      "action0 ph0 +0x5aa>=1 → slot 2 / side 1");
  }

  // --- action 0 ph1: contactP0==0 gates the stream tick; drift applies. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.tnApproachTimer560 = 1.0; // one frame from expiry
    a.motion = { x: 10, y: 0, z: 0 };
    a.contactP0 = 0; // no contact → stream ticks
    root(a); // ph1: not converged, timer 1→0 NOT <0... 0 < 0 false → drift tail
    // motion ×= 0.95 = 9.5; pos.x += 9.5
    assert(a.motion.x === 9.5, "action0 ph1 drift: motion.x *= 0.95 (FLOAT_8043a2c4)");
  }

  // --- action 0 ph2: window expired + B-held + ammo ok (grounded) → loop (ph0--). ---
  {
    const a = createRomActor() as TnActor;
    let refreshed = 0;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({
      onAllocateResource: () => true,
      onRefreshTargetVisibility: () => { refreshed += 1; },
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0; // window expired
    a.statusWord5b4 = TELEPORT_NINJA.B_HELD_BIT; // B held
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "action0 ph2 grounded B-held loop: +0x540-- back to ph1");
    assert(refreshed === 1, "action0 ph2 grounded loop calls zz_006bf80_ (visibility refresh)");
  }

  // --- action 0 ph2: window expired + B-held + ammo ok (airborne) → cue 0x2c re-dispatch. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0x2c * 2] = 61;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0;
    a.statusWord5b4 = TELEPORT_NINJA.B_HELD_BIT;
    a.controlWord = TELEPORT_NINJA.AIRBORNE_BIT; // airborne
    root(a);
    assert(a.fbState === 61, "action0 ph2 airborne re-dispatches cue 0x2c → state 61");
  }

  // --- action 0 ph2: window expired + B released → fall through, wallContact exits. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 0; // expired
    a.statusWord5b4 = 0; // B released
    a.wallContact = 1; // exit trigger
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph2 → wallContact exit (zz_006a474_)
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action0 ph2 wallContact exit clears +0x73f / strips +0x5e0 bits");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0 && a.gravityCoeff === 0,
      "action0 ph2 ground idle return (zz_006a474_) zeroes velocity scalars");
  }

  // ============================================================================
  // ACTION 1 — teleport-strike melee.
  // ============================================================================

  // --- v0: shared lunge (config @0x8033e550) — ph0 seeds +0x6ea = slotBase then ++. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 0; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // v0 → shared lunge ph0
    assert(a.fbPhaseSlots[0] === 1, "action1 v0 lunge ph0 advances +0x540");
    assert(a.streamSlot === 2, "action1 v0 lunge ph0 seeds +0x6ea = slotBase 1 then ++");
    assert(a.handlerTimer === 60.0, "action1 v0 lunge ph0 seeds +0x558 = 60.0");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0,
      "action1 v0 lunge ph0 zeroes velocity scalars");
  }

  // --- v2 ph0: setup — +0x540++, +0x6ea=4, +0x558=60, blink. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // v2 ph0
    assert(a.fbPhaseSlots[0] === 1, "action1 v2 ph0 advances +0x540");
    assert(a.streamSlot === 4, "action1 v2 ph0 seeds +0x6ea = 4");
    assert(a.handlerTimer === TELEPORT_NINJA.A1_PH0_TIMER,
      "action1 v2 ph0 seeds +0x558 = 60.0 (FLOAT_8043a2dc)");
    assert(a.pos.x === 195, "action1 v2 ph0 blink pos.x → 195");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "action1 v2 ph0 zeroes velocity scalars");
  }

  // --- v2 ph1: timer ≤ 0 → advance + commit speed = row/30. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; // drains to 0 → advance
    a.actionSpeedRows = [30, 30, 30]; // row 0 = 30 → hSpeed = 1.0
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action1 v2 ph1 timer ≤ 0 advances to ph2");
    assert(a.handlerTimer === TELEPORT_NINJA.A1_PH1_TIMER,
      "action1 v2 ph1 re-seeds +0x558 = 30.0 (FLOAT_8043a2bc)");
    assert(a.hSpeed === 30 / 30, "action1 v2 ph1 commits hSpeed = row/30 = 1.0");
  }

  // --- v2 ph3→ph4: contact (+0x1cef) → launch commit (hSpeed=40·cos, yVel=40·−sin). ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 3; // enter shared ph0
    a.steerYaw = 0; // cos(0)=1, sin(0)=0
    root(a); // shared ph0
    assert(a.fbPhaseSlots[0] === 4, "action1 v2 shared ph0 advances to ph1");
    root(a); // shared ph1 (approach) — needs timer drain
    assert(a.fbPhaseSlots[0] === 5, "action1 v2 shared ph1 advances to ph2 (contact)");
    a.contactP0 = 1; // +0x1cef → launch commit
    root(a);
    assert(a.fbPhaseSlots[0] === 6, "action1 v2 shared ph2 contact → ph3");
    assert(a.hSpeed === TELEPORT_NINJA.A1_LAUNCH_SPEED,
      "action1 v2 shared ph2 commits hSpeed = 40·cos(0)");
    assert(a.yVel === 0, "action1 v2 shared ph2 commits yVel = 40·−sin(0) = 0");
  }

  // --- v2 ph3 hit-gate: +0x1d9 & 0x30 → yVel=10, gravity=-1, then exit. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.variantIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 6;
    a.tnHitGate1d9 = 0x30; // +0x1d9 & 0x30
    a.contactP0 = -1;      // +0x1cef < 0
    a.wallContact = 0;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[7 * 2 + 1] = 61;
    (a as RomActor & { grounded?: boolean }).grounded = true;
    root(a);
    assert(a.gravityCoeff === TELEPORT_NINJA.STREAM_RATE,
      "action1 v2 ph3 hit-gate seeds +0x50 = -1.0 (FLOAT_8043a2c0)");
    assert(a.yVel === TELEPORT_NINJA.A1_PH3_YVEL + TELEPORT_NINJA.STREAM_RATE * TELEPORT_NINJA.A1_PH3_GRAVITY,
      "action1 v2 ph3 seeds +0x48 = 10.0 then gravity integrates (10 + (-1×4) = 6)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action1 v2 ph3 grounded exit clears +0x73f / strips +0x5e0");
    assert(a.ubState === 61, "action1 v2 ph3 grounded exit dispatches upper cue 7");
    assert(a.stateTimer === TELEPORT_NINJA.A1_144_SEED + 1,
      "action1 v2 ph3 exit seeds +0x694 = 8.0 + dt (FLOAT_8043a2d8)");
  }

  // ============================================================================
  // ACTION 3 — B-charge teleport-dash (table @0x8033e5b4).
  // ============================================================================

  // --- ph0 setup: range gate + face + blink + stream slot 0/2 + +0x6ea++. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.streamSlot = 0;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action3 ph0 advances +0x540");
    assert(a.handlerTimer === TELEPORT_NINJA.BCHARGE_WINDOW,
      "action3 ph0 seeds +0x558 = 60.0 (FLOAT_8043a2dc)");
    assert(a.streamSlot === 1, "action3 ph0 +0x6ea++ (ground slot 0 → 1)");
    assert(a.pos.x === 100 + 95, "action3 ph0 blink: pos.x += (100−0)×0.95 = 95 → 195");
    assert(a.motion.x === 95, "action3 ph0 motion.x = (pos−target)×0.95 = 95");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0 && a.gravityCoeff === 0,
      "action3 ph0 zeroes all four velocity scalars");
  }

  // --- ph0 airborne: stream slot starts at 2 (+0x5e0 & 0x40). ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.controlWord = TELEPORT_NINJA.AIRBORNE_BIT;
    a.streamSlot = 0;
    root(a);
    assert(a.streamSlot === 3, "action3 ph0 airborne starts slot 2 → +0x6ea++ = 3");
  }

  // --- ph1 approach: drift + face convergence advances. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; // drains to 0 this tick
    a.motion = { x: 10, y: 0, z: 0 };
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action3 ph1 timer ≤ 0 advances to ph2");
    assert(a.motion.x === 9.5, "action3 ph1 drift: motion.x *= 0.95 (FLOAT_8043a2c4)");
  }

  // --- ph2 contact: +0x1cf0 arms +0x272 bit 1; +0x1cee commits the launch. ---
  {
    let cued = 0;
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({ onPlayCue: () => { cued += 1; } }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.steerYaw = 0; // cos(0)=1, sin(0)=0
    a.tnContactP1 = 1; // +0x1cf0
    root(a);
    assert((a.tnFlag272 ?? 0) === TELEPORT_NINJA.FLAG272_BIT1,
      "action3 ph2 +0x1cf0 arms +0x272 bit 1");
    a.wallContact = 1; // +0x1cee → launch commit
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "action3 ph2 +0x1cee advances to ph3");
    assert(a.handlerTimer === TELEPORT_NINJA.POST_CONTACT_WINDOW,
      "action3 ph2 re-seeds +0x558 = 10.0 (FLOAT_8043a2ec)");
    assert(a.tnLaunchTimer55c === TELEPORT_NINJA.GRAVITY,
      "action3 ph2 seeds +0x55c = 1.0 (FLOAT_8043a2d0)");
    assert(a.tnLaunchProgress === TELEPORT_NINJA.LAUNCH_PROGRESS_SEED,
      "action3 ph2 seeds +0x560 = 15.0 (FLOAT_8043a308)");
    assert(a.hSpeed === TELEPORT_NINJA.LAUNCH_SPEED_COEFF, "action3 ph2 hSpeed = 100·cos(0)");
    assert(a.yVel === 0, "action3 ph2 yVel = 100·−sin(0) = 0");
    assert((a.tnFlag272 ?? 0) === (TELEPORT_NINJA.FLAG272_BIT1 | TELEPORT_NINJA.FLAG272_BIT2),
      "action3 ph2 commit sets +0x272 bits 1|2");
    assert(cued === 1, "action3 ph2 commit plays SFX 0xf2 (zz_00f036c_)");
  }

  // --- ph3 flurry: +0x55c drain spawns child type 3, +0x558 drain arms exit anim. ---
  {
    const spawned: Array<[number, number]> = [];
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({
      onFamilyProjectile: (_ac, addr, type) => spawned.push([addr, type]),
    }));
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 3;
    a.handlerTimer = 1.0;   // drains to 0 → exit-anim arm
    a.tnLaunchTimer55c = 1.0; // drains to 0 → spawn child
    a.tnLaunchProgress = 15.0;
    a.streamSlot = 0;
    root(a);
    assert(spawned.length === 1 && spawned[0]![0] === 0x8016c810 && spawned[0]![1] === 3,
      `action3 ph3 spawns FUN_8016c810 child type 3 (got ${JSON.stringify(spawned)})`);
    assert(a.tnLaunchTimer55c === TELEPORT_NINJA.GRAVITY,
      "action3 ph3 re-seeds +0x55c = 1.0 after spawn");
    assert(a.tnLaunchProgress === 14.0, "action3 ph3 steps +0x560 −= 1.0");
    assert(a.fbPhaseSlots[0] === 4, "action3 ph3 +0x558 ≤ 0 advances to ph4");
    assert(a.hSpeed === 0 && a.hDecel === 0 && a.yVel === 0,
      "action3 ph3 exit-anim arm zeroes velocity scalars");
    assert((a.tnAnim82 ?? 0) === a.carriedSlot96 + 0x41,
      "action3 ph3 sets +0x82 = +0x96 + 'A'");
  }

  // --- ph4 exit: grounded + +0x1cef < 0 → upper cue 7 + +0x694 = 16 + dt. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 4;
    a.contactP0 = -1; // +0x1cef < 0
    a.wallContact = 0;
    a.steerYaw = 100;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    (a as RomActor & { grounded?: boolean }).grounded = true; // zz_00677b0_ grounded
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[7 * 2 + 1] = 61; // upper-body row 7 → state 61
    root(a);
    assert(a.steerYaw === 90, "action3 ph4 decays +0x18da × 0.9 (100 → 90)");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action3 ph4 grounded exit clears +0x73f / strips +0x5e0");
    assert(a.ubState === 61, "action3 ph4 grounded exit dispatches upper cue 7");
    assert(a.stateTimer === TELEPORT_NINJA.EXIT_GROUND_STATE_TIMER + 1,
      "action3 ph4 grounded exit seeds +0x694 = 16.0 + dt (FLOAT_8043a2fc)");
  }

  // --- ph4 exit: airborne + wallContact → air knockout + +0x694 = 8 + dt. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.fbPhaseSlots[0] = 4;
    a.contactP0 = 0;
    a.wallContact = 1; // +0x1cee
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.steerYaw = 10;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "action3 ph4 wall exit clears +0x73f / strips +0x5e0");
    assert(a.steerYaw === 0, "action3 ph4 wall exit zeroes +0x18da");
    assert(a.stateTimer === TELEPORT_NINJA.EXIT_STATE_TIMER + 1,
      "action3 ph4 wall exit seeds +0x694 = 8.0 + dt (FLOAT_8043a2d8)");
  }

  // ============================================================================
  // ACTION 2 — X-special (borg-switched).
  // ============================================================================

  // --- pl0005 X ph0: setup — +0x540++, +0x558=4.0, +0x54a latch, ammo gate. ---
  {
    const spawned: Array<[number, number]> = [];
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0005", makeCtx({
      onFamilyProjectile: (_ac, addr, type) => spawned.push([addr, type]),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.tnChild144 = 0; // +0x144 <= 0 → far blink
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 pl0005 ph0 advances +0x540");
    assert(a.handlerTimer === TELEPORT_NINJA.A2_SETUP_TIMER,
      "action2 pl0005 ph0 seeds +0x558 = 4.0 (FLOAT_8043a2f0)");
    assert(a.pos.x === 100 + 50 * 100, "action2 pl0005 ph0 far blink: pos.x += (100−0)×50 = 5100");
    assert(spawned.length >= 1, "action2 pl0005 ph0 ammo gate deploys the FX child");
  }

  // --- pl0009 X ph0: setup — +0x540++, +0x6ea=4/5, stream g4. ---
  {
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0009", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.pos = { x: 100, y: 0, z: 0 };
    a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    a.streamSlot = 0;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "action2 pl0009 ph0 advances +0x540");
    assert(a.streamSlot === 5, "action2 pl0009 ph0 +0x6ea = 4 then ++ → 5");
    assert(a.pos.x === 195, "action2 pl0009 ph0 blink pos.x → 195");
  }

  // --- pl0009 X ph1: contact (+0x1cef > 0) → advance + ammo-gated child spawn. ---
  {
    const spawned: Array<[number, number]> = [];
    const a = createRomActor() as TnActor;
    configureTeleportNinjaFamily(a, "pl0009", makeCtx({
      onFamilyProjectile: (_ac, addr, type) => spawned.push([addr, type]),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1; // +0x1cef > 0
    a.motion = { x: 10, y: 0, z: 0 };
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "action2 pl0009 ph1 contact advances to ph2");
    assert(spawned.length === 1 && spawned[0]![0] === 0x801e29fc,
      `action2 pl0009 ph1 spawns zz_01e29fc_(0) (got ${JSON.stringify(spawned)})`);
  }
}
