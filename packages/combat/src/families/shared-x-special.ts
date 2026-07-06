// Shared-engine X-special machine — 1:1 port of `zz_00ff2bc_` @0x800ff2bc and its
// 3-phase table `PTR_zz_00ff30c__8031f000` = [0x800ff30c, 0x800ff418, 0x800ff4d4].
//
// Unlike G RED (whose X-special is a bespoke family chain, families/gred.ts), many
// families route their X-special through THIS shared handler: the family's per-variant
// entry is a tiny wrapper that loads a per-family CONFIG BLOCK into r4 (e.g. Normal
// Ninja's zz_00715d4_ loads r13-0x7d38 = 0x80433868) and branches to zz_00ff2bc_.
// Only the config differs per family: {ground stream slot, air stream slot, on-hit
// callback}. Source: research/decomp/nn-family-decode-2026-07-06.md §A3-§A6
// (adversarially verified 2026-07-06, workflow wf_a6dd44f6-f67).
//
// Config block layout (DOL @0x80433868 for the ninja family):
//   u16 +0x00 = ground stream slot (group 4)
//   u16 +0x02 = air stream slot    (used when +0x5e0 & 0x40)
//   ptr +0x04 = family on-hit callback (invoked on the phase-1 contact transition)

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

/** Motion constants — every value read from boot.dol (nn-family decode §A4-§A6). */
export const SHARED_X = {
  REPOSITION_SCALE: 0.95, // FLOAT_804392d0 — same 5%-pull shape as G RED's FLOAT_8043b124
  STREAM_RATE: -1.0,      // FLOAT_804392b8 — playback rate (record-rate substitution applies)
  GRAVITY: 1.0,           // FLOAT_804392d4 — phase-2 integrator gravity param
  COOLDOWN: 4.0,          // FLOAT_804392d8 — +0x694 attack cooldown seeded at exit
  TRAIL_THRESHOLD: 3.0,   // FLOAT_804392c8 — |motion| gate for the afterimage helper (FX, unported)
} as const;

/** Per-family config for the shared X machine (the ROM's r4 config block). */
export interface SharedXConfig {
  /** cfg u16[0]: group-4 stream slot used when grounded. */
  groundSlot: number;
  /** cfg u16[1]: group-4 stream slot used when airborne (+0x5e0 & 0x40). */
  airSlot: number;
  /** cfg ptr[+4]: family on-hit callback, invoked exactly once on the phase-1
   *  contact transition (`if ('\0' < +0x1cef) { +0x540++; (*cfg[+4])(actor); }`). */
  onHit: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** Whiff fallback: frames before phase 1 gives up and advances to the recovery
   *  phase when no contact fires. The ROM's stream VM advances +0x540 on stream end;
   *  our banks aren't byte-loaded yet (same approximation gred.ts documents), so a
   *  frame counter stands in. TUNED (default 60), labeled per family. */
  whiffFrames?: number;
}

const DEFAULT_WHIFF_FRAMES = 60;

/** The lock-target position the phase handlers read at actor+0x5e8 (bridge-synced). */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

/** Airborne test — the ROM reads +0x5e0 & 0x40 (position-frozen/air control bit). The
 *  bridge mirrors BorgRuntime.grounded onto the actor; prefer that live value. */
function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

// ============================================================================
// Phase 0 — zz_00ff30c_ @0x800ff30c. Setup + blink-reposition + stream start.
// ============================================================================
function sharedXPhase0(actor: RomActor, cfg: SharedXConfig, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ (enter phase 1)

  // No lock target → active yaw stays at current heading (+0x5ac = +0x72).
  // With a target, zz_006d144_(actor, 0xc1) turns toward it; the bridge pre-computes
  // lockYaw from the live target, so face it directly here.
  const target = lockTargetPos(actor);
  if (!target) {
    actor.activeYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }

  // Zero motion scalars +0x44/+0x48/+0x4c/+0x50 (FLOAT_804392b4 = 0.0) + turn rates.
  actor.hSpeed = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  actor.gravityCoeff = 0;

  // Reposition: motion = pos − lockTargetPos; motion ×= 0.95; pos += motion — the
  // signature "blink away to double distance" windup (identical shape to G Crash).
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(SHARED_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // Stream slot select: cfg ground/air slot into +0x6ea, which then auto-increments
  // (the combo-cursor convention shared with the B ladder).
  const slot = isAirborne(actor) ? cfg.airSlot : cfg.groundSlot;
  actor.streamSlot = slot + 1;
  // zz_004beb8_(rate −1.0, actor, partMask 0xf, group 4, slot, −1, −1)
  startStream(actor, 0xf, 4, slot, SHARED_X.STREAM_RATE);
  actor.handlerTimer = 0;
  void ctx;
}

// ============================================================================
// Phase 1 — zz_00ff418_ @0x800ff418. Stream tick + reposition tail + hit check.
// ============================================================================
function sharedXPhase1(actor: RomActor, cfg: SharedXConfig, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // Reposition continuation: motion ×= 0.95; pos += motion (decaying slide-away).
  vecScale(SHARED_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // HIT TRANSITION: part-0 contact byte +0x1cef went positive → phase 2 + family callback.
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    cfg.onHit?.(actor, ctx);
    return;
  }
  // |motion| > 3.0 → zz_00b22f4_ afterimage trail (FX helper, unported — renderer-side).

  // WHIFF fallback (port approximation, same rationale as gred.ts phase 1): without
  // byte-loaded stream banks the VM can't signal stream-end, so advance to recovery
  // after the labeled frame budget.
  actor.handlerTimer += actor.dt;
  if (actor.handlerTimer >= (cfg.whiffFrames ?? DEFAULT_WHIFF_FRAMES)) {
    actor.fbPhaseSlots[0] = 2;
    actor.handlerTimer = 0;
  }
}

// ============================================================================
// Phase 2 — zz_00ff4d4_ @0x800ff4d4. Recovery/landing (no cfg use in the ROM).
// ============================================================================
function sharedXPhase2(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // FUN_80067310(gravity 1.0 = FLOAT_804392d4, actor, yaw +0x5ae).
  integratePhysics(SHARED_X.GRAVITY, actor, actor.lockYaw);

  const grounded = (actor as RomActor & { grounded?: boolean }).grounded === true;
  if (grounded) {
    // Landing exit (zz_00ff4d4_ @chunk_0028.c:1810-1839): the ROM's grounded arms are
    // zz_006a750_(7) when the hover bit (+0x5e0 & 0x40) is set, else the real
    // zz_006a474_ call — the old upper-7 + full-0 combination existed in neither arm.
    // The exit CONDITION here (any grounded frame) remains the port's labeled
    // stream-end approximation; only the cue outcome is corrected.
    actor.controlWord &= ~0x3;
    if ((actor.controlWord & 0x40) !== 0) {
      dispatchUpperBodyCue(actor, 7); // zz_006a750_(actor, 7) — hover arm
    } else {
      romGroundIdleReturn(actor);     // zz_006a474_ (chunk_0028.c:1831)
    }
    actor.stateTimer = SHARED_X.COOLDOWN + actor.dt;
  }
  // Airborne: keep integrating. The ROM's air arm exits via the real zz_006a5a4_
  // (chunk_0028.c:1828) on wall contact / cancel-press; the port's bridge-owned
  // completion path stands in for that gate (labeled approximation).
}

/**
 * Build the shared X-special phase handler for one family config — the port of the
 * `zz_00715d4_`-shaped wrapper + `zz_00ff2bc_` dispatch. Wire the result as
 * actionTable[2] in the family's root action dispatcher.
 */
export function createSharedXSpecial(
  cfg: SharedXConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // zz_00ff2bc_ prologue: `if (+0x541) { +0xcc = 0; }` — target-invalidated flag
    // clears the lock pointer. The bridge owns target validity; not modeled here.
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: sharedXPhase0(actor, cfg, ctx); break;
      case 1: sharedXPhase1(actor, cfg, ctx); break;
      case 2: sharedXPhase2(actor, ctx); break;
      // Table entry [3] is NULL in the ROM (PTR_zz_00ff30c__8031f000+0xc = 0).
      default: break;
    }
  };
}
