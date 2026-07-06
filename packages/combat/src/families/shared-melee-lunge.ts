// Shared-engine 4-phase MELEE LUNGE machine — 1:1 port of `zz_00fed6c_` @0x800fed6c and
// its phase table `PTR_FUN_8031eff0` @0x8031eff0 = [0x800fedbc, 0x800feec4, 0x800fef88,
// 0x800ff058]. Second shared machine after zz_00ff2bc_ (shared-x-special.ts): families
// route a contextual-B / lunge action here with a config block in r4.
//
// Source: research/decomp/nn-family-decode-2026-07-06.md §3 claim A8 (adversarially
// verified; the two verify-pass corrections are applied here: decelC applies WITHIN
// range — braking near the target — and the leap/lunge constant fixes don't touch this
// machine). Reference user: Normal Ninja action-1 v0/v1 with config @0x802d3bfc.
//
// Config block layout (ninja's dump: 00000001 43160000 00000014 3f733333 3f733333 3f4ccccd):
//   s32 +0x00 = slotBase      (group-3 stream slot cursor seed, +0x6ea)
//   f32 +0x04 = range         (150.0 — dash-until + brake radius)
//   s32 +0x08 = dashFrames    (20 — dash timer + speed divisor)
//   f32 +0x0c = decelA        (0.95 — phase-2 approach decay)
//   f32 +0x10 = decelB        (0.95 — phase-3 recovery decay)
//   f32 +0x14 = decelC        (0.8  — EXTRA brake applied when target dist < range)

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue } from "../rom/dispatch.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Machine constants — DOL-read (nn-family-decode §A8). */
export const SHARED_LUNGE = {
  AIM_TIMER: 60.0,       // FLOAT_804392b0 — phase-0/1 face-target budget (frames)
  TRAIL_THRESHOLD: 3.0,  // FLOAT_804392c8 — |hSpeed| gate for the afterimage helper
  STREAM_GROUP: 3,       // melee stream group (all lunge streams are g3)
} as const;

export interface SharedLungeConfig {
  slotBase: number;
  range: number;
  dashFrames: number;
  decelA: number;
  decelB: number;
  decelC: number;
  /** Whiff fallback frames for phase 3's stream-end exit (banks not byte-loaded — same
   *  labeled approximation as shared-x-special.ts). */
  whiffFrames?: number;
}

const DEFAULT_WHIFF_FRAMES = 45;

interface LungeScratch {
  /** +0x746: B-retap latch (phase 3 combo-loop request). */
  bRetap?: boolean;
  /** Host-set: B button held/retapped this frame (+0x5d4 & 0x40 edge). */
  bRetapInput?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function targetDistance(actor: RomActor): number | null {
  const t = (actor as RomActor & LungeScratch).lockTarget;
  if (!t) return null;
  const dx = t.x - actor.pos.x;
  const dz = t.z - actor.pos.z;
  return Math.hypot(dx, dz);
}

// ============================================================================
// Phase 0 — FUN_800fedbc. Aim setup + stream start.
// ============================================================================
function lungePhase0(actor: RomActor, cfg: SharedLungeConfig, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++
  (actor as RomActor & LungeScratch).bRetap = false; // +0x746 = 0
  actor.streamSlot = cfg.slotBase; // +0x6ea = cfg.slotBase
  // Range gate FUN_80066838(+0x868 row): fail → +0x541=1 (target invalid), yaws=heading.
  // The +0x868 per-command-type range rows are runtime-populated (writer unlocated) —
  // the port gates on lock-target presence instead (labeled approximation).
  const target = (actor as RomActor & LungeScratch).lockTarget;
  if (!target) {
    actor.activeYaw = actor.heading;
    actor.lockYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }
  actor.handlerTimer = SHARED_LUNGE.AIM_TIMER; // +0x558 = 60.0
  actor.hSpeed = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  // Face target (zz_006d144_(actor, 0xc0)) — bridge pre-computes lockYaw.
  // Start stream: zz_004beb8_(rate, actor, 0xf, group 3, slot (+0x6ea++)).
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, SHARED_LUNGE.STREAM_GROUP, slot);
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_800feec4. Face-target windup, then compute the dash.
// ============================================================================
function lungePhase1(actor: RomActor, cfg: SharedLungeConfig, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // (ROM gates the tick on +0x1b03 — part-anim hold)
  actor.handlerTimer -= actor.dt; // +0x558 -= dt (the 60f face-target budget)
  // ROM: transition on timer expiry OR facing complete (zz_006d144_ return != 0). The
  // bridge pre-aims lockYaw from the live target each frame, so facing is instantaneous
  // here — the transition fires on the first phase-1 tick, and the 60f budget only
  // matters for the targetless case (kept for fidelity of the timer bookkeeping).
  const facingComplete = (actor as RomActor & LungeScratch).lockTarget != null;
  if (actor.handlerTimer <= 0 || facingComplete) {
    actor.fbPhaseSlots[0] = 2;
    actor.handlerTimer = cfg.dashFrames; // +0x558 = dashFrames (int→float)
    // zz_00ff1ec_: dash speed +0x44 = max(range, target distance) / dashFrames, capped
    // at the descriptor's +0x54 max speed (same shape as the spin-slash machine's
    // max(rangeRow, +0x764)/30 computation).
    const dist = targetDistance(actor);
    const dashDist = dist !== null ? Math.max(cfg.range, dist) : cfg.range;
    const maxSpeed = actor.maxHSpeed > 0 ? actor.maxHSpeed : Infinity; // descriptor+0x54 cap
    actor.hSpeed = Math.min(dashDist / cfg.dashFrames, maxSpeed);
    actor.hDecel = 0;
  }
}

// ============================================================================
// Phase 2 — FUN_800fef88. The dash-in (decayed approach until in range or timeout).
// ============================================================================
function lungePhase2(actor: RomActor, cfg: SharedLungeConfig, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // Decay zz_006ed8c_(decelA): dt-corrected exponential decay of +0x44/+0x48.
  actor.hSpeed *= cfg.decelA;
  actor.yVel *= cfg.decelA;
  // Advance along +0x5ae happens via the bridge's movement integration (hSpeed is
  // consumed by the physics step against lockYaw — zz_00670dc_'s role).
  actor.handlerTimer -= actor.dt;
  const dist = targetDistance(actor);
  const inRange = dist !== null && dist <= cfg.range;
  if (actor.handlerTimer <= 0 || inRange) {
    actor.fbPhaseSlots[0] = 3; // +0x540++
    actor.handlerTimer = cfg.whiffFrames ?? DEFAULT_WHIFF_FRAMES; // port stream-end budget
  }
  // |hSpeed| > 3.0 → zz_00b22f4_ afterimage (FX helper, renderer-side).
}

// ============================================================================
// Phase 3 — FUN_800ff058. Swing/recovery with the B-retap combo loop.
// ============================================================================
function lungePhase3(actor: RomActor, cfg: SharedLungeConfig, ctx: StreamContext): void {
  const scratch = actor as RomActor & LungeScratch;
  if (scratch.bRetapInput) scratch.bRetap = true; // +0x5d4 & 0x40 → +0x746 = 1
  tickStream(actor, 0xf, ctx);

  // COMBO LOOP: on the stream's re-arm event (+0x1cf0 < 0) with the retap latch set,
  // the ROM goes BACK to phase 2 with a fresh dash + the next stream slot (+0x6ea++).
  // Port approximation: the +0x1cf0 event isn't surfaced by the decoded events, so the
  // loop fires when the recovery budget elapses with the latch set.
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= 0) {
    if (scratch.bRetap) {
      scratch.bRetap = false;
      actor.fbPhaseSlots[0] = 2; // +0x540-- (loop to the dash phase)
      actor.handlerTimer = cfg.dashFrames;
      const slot = actor.streamSlot;
      actor.streamSlot = slot + 1;
      startStream(actor, 0xf, SHARED_LUNGE.STREAM_GROUP, slot);
      const dist = targetDistance(actor);
      const dashDist = dist !== null ? Math.max(cfg.range, dist) : cfg.range;
      actor.hSpeed = dashDist / cfg.dashFrames;
      return;
    }
    // Stream end (+0x1cee) → ground idle reset (zz_006a474_: cues 0/0) and done.
    actor.controlWord &= ~0x3;
    dispatchUpperBodyCue(actor, 0);
    dispatchFullBodyCue(actor, 0);
    return;
  }
  // Recovery decay: decelB, PLUS decelC when the target is WITHIN range (braking near
  // the target — the verify-pass-corrected reading of FUN_800ff058:34-37).
  actor.hSpeed *= cfg.decelB;
  const dist = targetDistance(actor);
  if (dist !== null && dist < cfg.range) actor.hSpeed *= cfg.decelC;
}

/** Build the shared melee-lunge phase handler for one family config. Wire as the
 *  family's action-1 (or wherever its command records route) handler. */
export function createSharedMeleeLunge(
  cfg: SharedLungeConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: lungePhase0(actor, cfg, ctx); break;
      case 1: lungePhase1(actor, cfg, ctx); break;
      case 2: lungePhase2(actor, cfg, ctx); break;
      case 3: lungePhase3(actor, cfg, ctx); break;
      default: break;
    }
  };
}

/** Normal Ninja action-1 v0/v1 config @0x802d3bfc (DOL dump, nn-family-decode §A8). */
export const NINJA_LUNGE_CONFIG: SharedLungeConfig = {
  slotBase: 1,
  range: 150.0,
  dashFrames: 20,
  decelA: 0.95,
  decelB: 0.95,
  decelC: 0.8,
};
