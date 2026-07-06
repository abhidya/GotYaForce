// Shared-engine AIMED SHOT X machine — 1:1 port of `zz_0179fcc_` @0x80179fcc and its
// 3-phase table `PTR_FUN_80352b64` @0x80352b64 = [0x8017a008, 0x8017a130, 0x8017a208].
//
// This is the SECOND shared X engine (after zz_00ff2bc_ / shared-x-special.ts) — same
// architecture (per-family wrapper loads a config block into r4, engine dispatches
// +0x540 through a phase table) but a RICHER 0x18-byte config and different dynamics:
//   * NO +0x541 prologue (the entry @0x80179fcc is a bare dispatcher; r4 passes through
//     to the phase functions untouched — proven by raw disasm, no store to r4 exists).
//   * gravity (1.0) integrates in BOTH phase 1 and phase 2 (zz_00ff2bc_ only in its P2).
//   * the 0.95 blink-reposition slide persists through ALL THREE phases until the
//     family onHit zeroes the motion vector (families 1/2 do; family 3 does NOT).
//   * cooldown is 1.0 + dt (not zz_00ff2bc_'s 4.0).
//   * facing/steering is ENTIRELY callback-driven (onSetup/onSteer/onHit config slots).
//   * the stream slot is written to +0x6ea WITHOUT the post-increment zz_00ff2bc_ does.
//   * an aim-pitch channel (+0x18da = actor.steerYaw) is halved by the family wrapper
//     on entry and decayed ×0.9 per phase-2 tick.
//
// Config block layout (0x18 bytes; engine loads ONLY +0x00/+0x02/+0x04/+0x0c/+0x10/+0x14):
//   u16 +0x00 = ground stream slot (group 4)          → +0x6ea
//   u16 +0x02 = air stream slot (used when +0x5e0 & 0x40)
//   f32 +0x04 = reposition scale (0.95 in all three family blocks)
//   f32 +0x08 = 0.1 in all three blocks — NO reader anywhere in the corpus (the P2
//               landing damp is the GLOBAL FLOAT_8043ae3c, numeric coincidence).
//               Treated as reserved/dead (dig claim CFG-08-FIELD, UNRESOLVED consumer).
//   ptr +0x0c = onSetup  (phase 0 only, called AFTER the speed zero-init)
//   ptr +0x10 = onSteer  (called once in phase 0 AND every phase-1 tick)
//   ptr +0x14 = onHit    (phase-1 contact transition only)
//
// Families on this engine (all wrappers raw-disassembled; Ghidra drops the r4 arg):
//   FAM 1 — ctor 0x800ce730, MACHINE BLUE pl0601/pl0609/pl0617/pl061d. X = action
//     INDEX 2 (table PTR_FUN_8030ce34; all 5 variants @0x8030cef8 route to wrapper
//     0x800cf9cc). Config @0x8030cf0c. ALREADY SERVED by the bridge's Machine Blue
//     registration — its config + callbacks are exported here for the future swap to
//     this faithful engine, but registration is NOT requested for it.
//   FAM 2 — ctor 0x80125a28, TITAN ROBOT pl0604 / PROTO TITAN pl0618. X = action
//     INDEX 3 (table PTR_FUN_8032f41c; handler 0x801260f0 → inner wrapper 0x80126110).
//     Config @0x8032f498.
//   FAM 3 — ctor 0x8018c2b0, PANTHER ROBOT pl0613 / PROTO PANTHER pl0627. X = action
//     INDEX 3 (table PTR_FUN_8036546c; handler 0x8018cb48 → inner wrapper 0x8018cb68).
//     Config @0x8036551c. AERIAL variant: onSetup sets yVel=4.0 + the 0x40 air-control
//     bit BEFORE phase 0's slot select, so family 3 ALWAYS starts the air stream slot.
//
// Source: scratchpad wav-eng-80179fcc.json (15+/18 CONFIRMED, adversarially verified).
// THREE verifier corrections are applied in this port (cited inline where they land):
//   (1) CB-FAM2: in zz_006e1d0_ the 0x4000 clamps the TARGET pitch, NOT the per-tick
//       step; the step is desc(+0x4ac) s16 [+0xac + 2*(mask&0xf)] × actor f32 +0x768.
//   (2) CTOR-XACTION-WIRING: the two shared-bank pointers all three ctors store are
//       +0x1d84 = 0x802BCC64 and +0x1d8c = 0x802BB698 (borrow-bit corrections of the
//       dig's 0x802ccc64/0x802cb698 — cosmetic; the ctor bank binding is bridge-side).
//   (3) HELPERS: zz_006e848_ (fam1 channel +0x18e0) and zz_006e1d0_ (fam2/3 channel
//       +0x18da) have DISTINCT semantics — e848 targets via FUN_800667a0, rate × dt,
//       clamp ±0x2000, and does NOTHING on target loss (channel frozen); e1d0 targets
//       via atan2 toward the lock target, rate × (+0x768), clamp ±0x4000, and decays
//       the channel ×0.9 on target loss. A port that decays +0x18e0 would be wrong.

import type { RomActor, Vec3 } from "../rom/actor.js";
import {
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "../rom/dispatch.js";
import {
  integratePhysics,
  groundClamp,
  vecSubtract,
  vecScale,
  vecAdd,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Machine constants — every value read from boot.dol (dig claims MACHINE-P0/P1/P2). */
export const AIMED_SHOT_X = {
  /** FLOAT_8043ae10 @0x8043ae10 = 0.0 — phase-0 zero for +0x44/+0x48/+0x4c/+0x50. */
  ZERO: 0.0,
  /** FLOAT_8043ae04 @0x8043ae04 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043ae1c @0x8043ae1c = 1.0 — FUN_80067310 gravity param, applied in
   *  BOTH phase 1 and phase 2 (unlike zz_00ff2bc_, which integrates only in P2). */
  GRAVITY: 1.0,
  /** FLOAT_8043ae1c @0x8043ae1c = 1.0 — exit cooldown seed (+0x694 = 1.0 + dt).
   *  Same literal as GRAVITY; note this is 1.0, NOT zz_00ff2bc_'s 4.0. */
  COOLDOWN: 1.0,
  /** FLOAT_8043ae30 @0x8043ae30 = 0.8999999761581421 — phase-2 per-tick decay of the
   *  aim-pitch channel +0x18da (s16, via the 0x43300000/DOUBLE_8043ae08 int idiom). */
  PITCH_DECAY: 0.8999999761581421,
  /** FLOAT_8043ae38 @0x8043ae38 = 3.0 — |motion| (P1) / +0x44 (P2) afterimage gate
   *  for zz_00b22f4_ (FX helper, unported — renderer-side). */
  TRAIL_THRESHOLD: 3.0,
  /** FLOAT_8043ae3c @0x8043ae3c = 0.1 — landing damp factor passed to zz_006ed8c_
   *  (dt-corrected damp of +0x44/+0x48) on the grounded phase-2 path. */
  LANDING_DAMP: 0.1,
  /** FLOAT_80437670 @0x80437670 = 1.0 — zz_006ed8c_'s dt==1.0 fast-path constant. */
  DT_UNITY: 1.0,
  /** FLOAT_804376d8 @0x804376d8 = 0.8999999761581421 — zz_006e1d0_'s no-target decay
   *  of the +0x18da channel (fam2/3 onSteer only; fam1's zz_006e848_ never decays). */
  NO_TARGET_PITCH_DECAY: 0.8999999761581421,
  /** zz_004beb8_ group param — all aimed-shot streams are group 4. */
  STREAM_GROUP: 4,
  /** zz_006e848_ target-pitch clamp (fam1 channel +0x18e0): ±0x2000 BAM. */
  PITCH_TARGET_CLAMP_18E0: 0x2000,
  /** zz_006e1d0_ param_4 (fam2/3 channel +0x18da): ±0x4000 BAM. CORRECTED reading —
   *  this clamps the TARGET pitch, not the per-tick step (verifier note on CB-FAM2). */
  PITCH_TARGET_CLAMP_18DA: 0x4000,
} as const;

/** Per-tick aim-pitch seek step — PORT APPROXIMATION. The ROM's step is
 *  descriptor(+0x4ac) s16 at [+0xac + 2*(mask & 0xf)] (mask 0xc1 → +0xae) multiplied
 *  by actor f32 +0x768 (zz_006e1d0_) or by dt +0x1dc8 (zz_006e848_). Neither the
 *  descriptor rate field nor +0x768 is surfaced on RomDescriptor/RomActor yet, so a
 *  fixed BAM/frame rate stands in (TUNED: 0x400 ≈ 5.6°/frame; scaled by dt). */
const AIM_SEEK_STEP_APPROX = 0x400;

/** Whiff fallback frames for the phase-1 contact wait (+0x1cef is a stream-event byte;
 *  banks aren't byte-loaded — same labeled approximation as shared-x-special.ts). */
const DEFAULT_WHIFF_FRAMES = 60;
/** Frame budget for phase 2's +0x1cee stream-end/landing wait (same approximation
 *  posture: handlerTimer budget stands in for the unsurfaced stream-event byte). */
const DEFAULT_RECOVER_FRAMES = 45;

/** Per-family config for the aimed-shot X machine (the ROM's r4 config block). */
export interface SharedAimedShotConfig {
  /** cfg u16 +0x00: group-4 stream slot used when grounded (+0x5e0 & 0x40 clear). */
  groundSlot: number;
  /** cfg u16 +0x02: group-4 stream slot used when airborne (+0x5e0 & 0x40 set). */
  airSlot: number;
  /** cfg f32 +0x04: blink-reposition scale (0.95 in all three family blocks) — the
   *  motion vector is rescaled by this EVERY tick of all three phases. */
  repositionScale: number;
  /** cfg ptr +0x0c: onSetup — phase 0 only, called AFTER the speed zero-init and
   *  BEFORE the reposition + slot select (family 3 exploits the ordering to force
   *  the air slot). NULL for families 1/2. */
  onSetup: ((actor: RomActor) => void) | null;
  /** cfg ptr +0x10: onSteer — called once in phase 0 and EVERY phase-1 tick. */
  onSteer: ((actor: RomActor) => void) | null;
  /** cfg ptr +0x14: onHit — invoked exactly once on the phase-1 contact transition
   *  (`if ('\0' < +0x1cef) { +0x540++; (*cfg[+0x14])(actor); }`). */
  onHit: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** Wrapper delta (NOT a config field — encoded in each family's wrapper code):
   *  fam1's wrapper 0x800cf9cc halves +0x18da UNCONDITIONALLY every dispatch;
   *  fam2/fam3's wrappers (0x80126110/0x8018cb68) halve only when +0x5e0 & 0x40 is
   *  clear (grounded). */
  pitchHalveAlways: boolean;
  /** Whiff fallback frames for phase 1 (port approximation, see DEFAULT_WHIFF_FRAMES). */
  whiffFrames?: number;
  /** Phase-2 recovery budget frames (port approximation for the +0x1cee wait). */
  recoverFrames?: number;
}

/** Host-scratch fields the bridge mirrors onto the actor (same convention as
 *  shared-x-special.ts / shared-melee-lunge.ts). */
interface AimedShotScratch {
  lockTarget?: Vec3 | null;
  grounded?: boolean;
  /** +0x18e0: family-1 aim-pitch channel (zz_006e848_'s seek target). Distinct from
   *  actor.steerYaw (+0x18da), which is the fam2/3 channel + the wrapper-halved one. */
  aimPitch18e0?: number;
  /** Phase-2 entry latch for the +0x1d0f descriptor-gravity reload approximation. */
  aimedShotGravReloaded?: boolean;
}

// ============================================================================
// Small helpers (BAM math + bridge-synced reads)
// ============================================================================

const TAU = Math.PI * 2;

function toS16(v: number): number {
  const u = v & 0xffff;
  return u >= 0x8000 ? u - 0x10000 : u;
}

function lockTargetPos(actor: RomActor): Vec3 | null {
  const t = (actor as RomActor & AimedShotScratch).lockTarget;
  return t ?? null;
}

/** Air test for the phase-0 slot select + the wrapper pitch-halving gate. The ROM
 *  reads ONLY +0x5e0 & 0x40. The bit takes PRIORITY over the bridge's grounded mirror
 *  here (unlike shared-x-special's helper) because family 3's onSetup SETS the bit
 *  while the actor is still physically grounded — the slot select must honor it. */
function airControlBit(actor: RomActor): boolean {
  if ((actor.controlWord & 0x40) !== 0) return true;
  const grounded = (actor as RomActor & AimedShotScratch).grounded;
  return grounded === false;
}

/** Pitch (BAM16) from the actor toward its lock target — the zz_006e1d0_ target
 *  computation (PSVECSubtract from +0x518 anchor, PSVECMag, FUN_800452a0 atan).
 *  PORT APPROXIMATION: the ROM's target is `-(s16 +0x70) - atanResult`; the +0x70
 *  current body pitch isn't surfaced, so it's treated as 0 (upright). */
function pitchToTargetBam(actor: RomActor): number | null {
  const t = lockTargetPos(actor);
  if (!t) return null;
  const dx = t.x - actor.pos.x;
  const dy = t.y - actor.pos.y;
  const dz = t.z - actor.pos.z;
  const rad = Math.atan2(dy, Math.hypot(dx, dz));
  return Math.round((-rad / TAU) * 0x10000);
}

/** Face the lock target — zz_006d144_(actor, 0xc1) (fam1) / zz_006d0dc_(actor, 0xc1, 0)
 *  (fam2/3). The bridge pre-computes lockYaw from the live target each frame, so facing
 *  is modeled as adopting it directly (the mask-0xc1 turn-rate ramp via FUN_800669d0 is
 *  the bridge's aim-smoothing responsibility). zz_006d144_'s no-target branch writes
 *  the steer-delta u16 +0x5aa = +0x5ac − +0x72 (unsurfaced — no-op here). */
function faceLockTarget(actor: RomActor): void {
  if (lockTargetPos(actor)) {
    actor.activeYaw = actor.lockYaw;
  }
}

/** Port of zz_006e848_ @0x8006e848 (via one-liner zz_006e820_ @0x8006e820) — the
 *  FAMILY-1 aim-pitch seek on channel +0x18e0. CORRECTED semantics (verifier note on
 *  HELPERS): target via FUN_800667a0 (approximated by pitchToTargetBam), TARGET clamped
 *  to ±0x2000, per-tick step = desc s16 +0xae × dt (approximated by
 *  AIM_SEEK_STEP_APPROX × dt), snap when within step; NO-TARGET → return -1 WITHOUT
 *  touching the channel (frozen — no 0.9 decay on +0x18e0). */
function seekAimPitch18e0(actor: RomActor): void {
  const scratch = actor as RomActor & AimedShotScratch;
  const target = pitchToTargetBam(actor);
  if (target === null) return; // channel frozen on target loss
  const clamp = AIMED_SHOT_X.PITCH_TARGET_CLAMP_18E0;
  const t = Math.max(-clamp, Math.min(clamp, target));
  const cur = toS16(scratch.aimPitch18e0 ?? 0);
  const step = Math.max(1, Math.round(AIM_SEEK_STEP_APPROX * actor.dt));
  const diff = t - cur;
  scratch.aimPitch18e0 = Math.abs(diff) <= step ? t : cur + Math.sign(diff) * step;
}

/** Port of zz_006e1d0_ @0x8006e1d0 (via zz_006e1ac_ @0x8006e1ac, param_4 = 0x4000) —
 *  the FAMILY-2/3 aim-pitch seek on channel +0x18d4 + 6×1 = +0x18da (actor.steerYaw).
 *  CORRECTED semantics (the REFUTED CB-FAM2 reading, verifier note applied): 0x4000
 *  clamps the TARGET pitch, NOT the step; the per-tick step is desc s16 +0xae ×
 *  actor f32 +0x768 (both unsurfaced — AIM_SEEK_STEP_APPROX × dt stands in, labeled);
 *  snap-to-target when |diff| <= step; NO-TARGET → channel ×0.9 (FLOAT_804376d8). */
function seekAimPitch18da(actor: RomActor): void {
  const target = pitchToTargetBam(actor);
  if (target === null) {
    actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * AIMED_SHOT_X.NO_TARGET_PITCH_DECAY);
    return;
  }
  const clamp = AIMED_SHOT_X.PITCH_TARGET_CLAMP_18DA;
  const t = Math.max(-clamp, Math.min(clamp, target));
  const cur = toS16(actor.steerYaw);
  const step = Math.max(1, Math.round(AIM_SEEK_STEP_APPROX * actor.dt));
  const diff = t - cur;
  actor.steerYaw = Math.abs(diff) <= step ? t : cur + Math.sign(diff) * step;
}

/** Port of zz_006ed8c_ @0x8006ed8c — dt-corrected damp of +0x44/+0x48 to factor k:
 *  `if (dt == FLOAT_80437670) { v *= k; } else { v -= v * ((1-k) * dt); }`. */
function dampLanding(actor: RomActor, k: number): void {
  if (actor.dt === AIMED_SHOT_X.DT_UNITY) {
    actor.hSpeed *= k;
    actor.yVel *= k;
  } else {
    const scale = (1 - k) * actor.dt;
    actor.hSpeed -= actor.hSpeed * scale;
    actor.yVel -= actor.yVel * scale;
  }
}

// ============================================================================
// Phase 0 — FUN_8017a008 @0x8017a008. Zero-init + callbacks + blink-reposition
// + stream start. (Source order matters: zeroing BEFORE callbacks, callbacks
// BEFORE the +0x5e0&0x40 slot fork — family 3's onSetup depends on both.)
// ============================================================================
function aimedShotPhase0(actor: RomActor, cfg: SharedAimedShotConfig, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ (enter phase 1)

  // No lock target (+0xcc == 0) → active yaw = heading (+0x5ac = +0x72). NO built-in
  // face call here — facing is entirely delegated to the config callbacks.
  if (!lockTargetPos(actor)) {
    actor.activeYaw = actor.heading;
  }

  // Zero the four speed scalars +0x50/+0x48/+0x4c/+0x44 = FLOAT_8043ae10 (0.0).
  actor.hSpeed = AIMED_SHOT_X.ZERO;
  actor.yVel = AIMED_SHOT_X.ZERO;
  actor.hDecel = AIMED_SHOT_X.ZERO;
  actor.gravityCoeff = AIMED_SHOT_X.ZERO;
  // Turn-rate u16s +0x80/+0x7e/+0x7c = 0 — not surfaced on RomActor (the bridge owns
  // the aim-smoothing rates); honest no-op.

  // cfg +0x0c onSetup then cfg +0x10 onSteer — AFTER the zeroing (so family 3's
  // yVel = 4.0 write survives), BEFORE the reposition + slot select.
  cfg.onSetup?.(actor);
  cfg.onSteer?.(actor);

  // Blink-away windup: motion = pos − lockTargetPos(+0x5e8); motion ×= cfg+0x04
  // (0.95); pos += motion. Scale comes from CONFIG, not a global (unlike zz_00ff2bc_).
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // zz_00679d0_ ground snap (probe zz_00677b0_ + airborne position revert when
  // +0x5e0&0x40 clear). PORT APPROXIMATION: the host ground clamp models the snap;
  // the revert-from-last-grounded-copy (+0x2c/+0x30/+0x34) branch is unmodeled.
  groundClamp(actor);

  // Stream slot select: +0x6ea = cfg groundSlot, or cfg airSlot when +0x5e0 & 0x40.
  // NO post-increment of +0x6ea (unlike the zz_00ff2bc_ machine's combo cursor).
  const slot = airControlBit(actor) ? cfg.airSlot : cfg.groundSlot;
  actor.streamSlot = slot;
  // zz_004beb8_(rate FLOAT_8043ae04 = -1.0, actor, partMask 0xf, group 4, slot, -1, -1)
  startStream(actor, 0xf, AIMED_SHOT_X.STREAM_GROUP, slot, AIMED_SHOT_X.STREAM_RATE);
  // +0x80c = 0.0 — unsurfaced accumulator; honest no-op. No +0x558/+0x560 timers are
  // written anywhere in this machine (the handlerTimer below is the port's whiff budget).
  actor.handlerTimer = 0;
  (actor as RomActor & AimedShotScratch).aimedShotGravReloaded = false;
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_8017a130 @0x8017a130. Stream tick + per-tick onSteer + reposition
// tail + gravity integration + contact transition.
// ============================================================================
function aimedShotPhase1(actor: RomActor, cfg: SharedAimedShotConfig, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)
  cfg.onSteer?.(actor);        // cfg +0x10 runs EVERY phase-1 tick

  // Reposition continuation: motion ×= cfg+0x04 (0.95); pos += motion.
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // FUN_80067310(gravity FLOAT_8043ae1c = 1.0, actor, yaw s16 +0x5ae) — gravity
  // integrates during phase 1 (unlike zz_00ff2bc_). zz_00679d0_'s snap folds into
  // the integrator's ground clamp.
  integratePhysics(AIMED_SHOT_X.GRAVITY, actor, actor.lockYaw);

  // HIT TRANSITION: part-0 contact byte +0x1cef went positive → phase 2 + onHit.
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    actor.handlerTimer = 0;    // reset the port's phase-2 recovery budget
    cfg.onHit?.(actor, ctx);
    return;
  }
  // |motion| > FLOAT_8043ae38 (3.0) → zz_00b22f4_ afterimage (FX, renderer-side).

  // WHIFF fallback (port approximation, same rationale as shared-x-special.ts):
  // +0x1cef is a stream-event byte; without byte-loaded banks the VM can't fire it,
  // so advance to recovery (WITHOUT onHit) after the labeled frame budget.
  actor.handlerTimer += actor.dt;
  if (actor.handlerTimer >= (cfg.whiffFrames ?? DEFAULT_WHIFF_FRAMES)) {
    actor.fbPhaseSlots[0] = 2;
    actor.handlerTimer = 0;
  }
}

// ============================================================================
// Phase 2 — FUN_8017a208 @0x8017a208. Recovery: pitch decay + descriptor-gravity
// reload + reposition tail + gravity + the +0x1cee-gated three-way exit.
// (Reads only cfg +0x04; +0x1d10 is never read by this machine.)
// ============================================================================
function aimedShotPhase2(actor: RomActor, cfg: SharedAimedShotConfig, ctx: StreamContext): void {
  // Aim-pitch decay: s16 +0x18da = (s16)((float)+0x18da × FLOAT_8043ae30 (0.9)) —
  // the 0x43300000/DOUBLE_8043ae08 int-conversion idiom.
  actor.steerYaw = Math.trunc(toS16(actor.steerYaw) * AIMED_SHOT_X.PITCH_DECAY);

  tickStream(actor, 0xf, ctx);

  // Stream event +0x1d0f < 0 → +0x1d0f = 0 and +0x50 = *(descriptor(+0x4ac) + 0x6c)
  // — reload the gravity coefficient from the family descriptor default. PORT
  // APPROXIMATION: +0x1d0f isn't surfaced by the VM; the reload is applied once on
  // phase-2 entry (the event fires early in every recovery stream, and nothing else
  // writes +0x50 during phase 2, so the post-event steady state is identical).
  const scratch = actor as RomActor & AimedShotScratch;
  if (!scratch.aimedShotGravReloaded) {
    scratch.aimedShotGravReloaded = true;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
  }

  // Reposition tail continues: motion ×= cfg+0x04 (0.95); pos += motion.
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // FUN_80067310(gravity 1.0 = FLOAT_8043ae1c, actor, +0x5ae).
  integratePhysics(AIMED_SHOT_X.GRAVITY, actor, actor.lockYaw);

  // grounded = zz_00679d0_(actor) — the probe's return (verifier-upgraded to DERIVED:
  // zz_00677b0_'s result survives in r3). Here: the integrator's ground clamp mirrors
  // grounded onto the actor.
  const grounded = scratch.grounded === true;

  // EXIT LOGIC (verified exit ladder):
  //   grounded && +0x1cef >= 0 → zz_006ed8c_(FLOAT_8043ae3c = 0.1) landing damp,
  //                              then exit only if +0x1cee != 0;
  //   airborne               → exit only if +0x1cee != 0;
  //   grounded && +0x1cef < 0 → exit immediately.
  // PORT APPROXIMATION: +0x1cee is a stream-end/landing event; a handlerTimer frame
  // budget stands in for it (same posture as the other shared-machine ports).
  actor.handlerTimer += actor.dt;
  const streamEnded =
    actor.wallContact !== 0 ||
    actor.handlerTimer >= (cfg.recoverFrames ?? DEFAULT_RECOVER_FRAMES);
  let exitNow: boolean;
  if (grounded && actor.contactP0 >= 0) {
    dampLanding(actor, AIMED_SHOT_X.LANDING_DAMP);
    exitNow = streamEnded;
  } else if (!grounded) {
    exitNow = streamEnded;
  } else {
    exitNow = true; // grounded && contactP0 < 0
  }

  if (exitNow) {
    // EXIT BLOCK: +0x73f = 0 (unsurfaced housekeeping byte — no-op); +0x5e0 &= ~3.
    actor.controlWord &= ~0x3;
    if (!grounded) {
      // zz_006a5a4_(actor) — air-fall exit. Approximated as the neutral full-body cue;
      // the real air-fall state lands via the bridge's grounded transition.
      dispatchFullBodyCue(actor, 0);
    } else if ((actor.controlWord & 0x40) === 0) {
      // zz_006a474_(actor) — ground idle reset (cues 0/0).
      dispatchUpperBodyCue(actor, 0);
      dispatchFullBodyCue(actor, 0);
    } else {
      // zz_006a750_(actor, 7) — upper cue 7 (family 3's always-air path lands here).
      dispatchUpperBodyCue(actor, 7);
    }
    // Cooldown +0x694 = FLOAT_8043ae1c (1.0) + dt (+0x1dc8) — note 1.0, not 4.0.
    actor.stateTimer = AIMED_SHOT_X.COOLDOWN + actor.dt;
    actor.handlerTimer = 0;
  }
  // TAIL (runs even without exit): +0x44 > FLOAT_8043ae38 (3.0) → zz_00b22f4_
  // afterimage (FX, renderer-side).
}

/**
 * Build the aimed-shot X handler for one family config — the port of the family
 * wrapper (+0x18da halving + r4 = &config) + the zz_0179fcc_ dispatch. The wrapper
 * runs EVERY dispatched tick, so the halving is a per-tick pitch decay.
 */
export function createSharedAimedShotX(
  cfg: SharedAimedShotConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // Wrapper pitch-halving: `lha +0x18da; srawi 1; sth` — fam1 unconditionally;
    // fam2/3 only when +0x5e0 & 0x40 is clear (raw disasm, claim WRAPPER-PROOF).
    if (cfg.pitchHalveAlways || (actor.controlWord & 0x40) === 0) {
      actor.steerYaw = toS16(actor.steerYaw) >> 1;
    }
    // zz_0179fcc_: bare dispatch of PTR_FUN_80352b64[+0x540] — exactly 3 live entries
    // (the next word @0x80352b70 is non-pointer data), so phases stay in 0..2.
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: aimedShotPhase0(actor, cfg, ctx); break;
      case 1: aimedShotPhase1(actor, cfg, ctx); break;
      case 2: aimedShotPhase2(actor, cfg, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// FAMILY 1 — MACHINE BLUE (ctor 0x800ce730): pl0601 / pl0609 / pl0617 / pl061d.
// Config @0x8030cf0c. X = action INDEX 2 (PTR_FUN_8030ce34 @0x8030ce34; the 5-entry
// variant table @0x8030cef8 routes ALL X variants to wrapper 0x800cf9cc).
// NOT registered by this module — the bridge already serves Machine Blue; the config
// + callbacks are exported for the future swap onto this faithful engine.
// ============================================================================

/** FUN_800cfa38 @0x800cfa38 constants — all DOL-read (claim CB-FAM1). */
export const MACHINE_BLUE_X = {
  BACKDASH_HSPEED: 40.0, // FLOAT_804389e4 @0x804389e4 → +0x44
  BACKDASH_YVEL: 20.0,   // FLOAT_804389cc @0x804389cc → +0x48
  BACKDASH_HDECEL: -1.0, // FLOAT_804389bc @0x804389bc → +0x4c
  MOTION_ZERO: 0.0,      // FLOAT_804389c0 @0x804389c0 → +0x38/+0x3c/+0x40
  /** zz_0084600_ @0x80084600 — beam-child spawner (pl0601 variants 7/8, pl0617
   *  variants 0xf/0x10; scale-triple records @0x802d9794 + v×0x50, all (2,2,2)). */
  SPAWNER_84600_ADDR: 0x80084600,
  /** zz_00c3be0_ @0x800c3be0 — child spawner allocating against *(actor+0x90)
   *  (pl0609 variants 0x2c..0x2f, pl061d variants 0x41..0x44). */
  SPAWNER_C3BE0_ADDR: 0x800c3be0,
} as const;

/** onSteer FUN_800cfa00 @0x800cfa00: zz_006d144_(actor, 0xc1) face + zz_006e820_
 *  (= zz_006e848_(actor, &+0x18e0, 0)) aim-pitch seek on channel +0x18e0. */
export function machineBlueXOnSteer(actor: RomActor): void {
  faceLockTarget(actor);
  seekAimPitch18e0(actor);
}

/** onHit FUN_800cfa38 @0x800cfa38: face-away + ammo-gated borg-switched spawns +
 *  backdash. The ammo gate zz_006dbe0_(actor, 2, 1, 1) wraps ALL FOUR borgs; the host
 *  (BorgRuntime) owns the real ammo count — modeled as passing (honest approximation,
 *  same posture as robot.ts/cyber-machine.ts). NOTE (verifier extra finding): the
 *  backdash fires whenever the GATE passes, even if the projectile allocation fails —
 *  the velocity writes are NOT tied to spawn success. */
export function machineBlueXOnHit(actor: RomActor, ctx: StreamContext): void {
  // +0x5ae = +0x72 − 0x8000 — motion yaw faces away 180°.
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  // zz_006dbe0_(actor, 2, 1, 1) — host ammo gate (approximated as passing).
  const gatePassed = true;
  if (gatePassed) {
    switch (actor.borgNumber) {
      case 0x601:
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_84600_ADDR, 7);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_84600_ADDR, 8);
        break;
      case 0x609:
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x2c);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x2d);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x2e);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x2f);
        break;
      case 0x617:
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_84600_ADDR, 0xf);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_84600_ADDR, 0x10);
        break;
      case 0x61d:
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x41);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x42);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x43);
        ctx.onFamilyProjectile?.(actor, MACHINE_BLUE_X.SPAWNER_C3BE0_ADDR, 0x44);
        break;
    }
    // BACKDASH: +0x44 = 40.0, +0x48 = 20.0, +0x4c = −1.0, +0x50 = desc+0x6c.
    actor.hSpeed = MACHINE_BLUE_X.BACKDASH_HSPEED;
    actor.yVel = MACHINE_BLUE_X.BACKDASH_YVEL;
    actor.hDecel = MACHINE_BLUE_X.BACKDASH_HDECEL;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
  }
  // ALWAYS: motion vector +0x38/+0x3c/+0x40 = 0.0 — kills the reposition slide.
  actor.motion.x = MACHINE_BLUE_X.MOTION_ZERO;
  actor.motion.y = MACHINE_BLUE_X.MOTION_ZERO;
  actor.motion.z = MACHINE_BLUE_X.MOTION_ZERO;
}

/** Config block @0x8030cf0c (raw: 00000001 3f733333 3dcccccd 00000000 800cfa00
 *  800cfa38): groundSlot 0, airSlot 1, scale 0.95, reserved 0.1, onSetup NULL. */
export const MACHINE_BLUE_X_CONFIG: SharedAimedShotConfig = {
  groundSlot: 0,
  airSlot: 1,
  repositionScale: 0.949999988079071, // 0x3f733333 @0x8030cf10
  onSetup: null,
  onSteer: machineBlueXOnSteer,
  onHit: machineBlueXOnHit,
  pitchHalveAlways: true, // wrapper 0x800cf9cc halves +0x18da unconditionally
};

// ============================================================================
// FAMILY 2 — TITAN ROBOT (ctor 0x80125a28): pl0604 TITAN ROBOT / pl0618 PROTO TITAN.
// Config @0x8032f498. X = action INDEX 3 (PTR_FUN_8032f41c @0x8032f41c; handler
// 0x801260f0 → inner wrapper zz_0126110_ @0x80126110 — no variant dispatch).
// Action INDEX 2 (0x801260a8) is the family's MORPH engine — a different shared
// machine ported in another module; this file wires ONLY action 3.
// ============================================================================

/** FUN_801261a0 @0x801261a0 constants — byte-identical backdash numbers to family 1,
 *  from DIFFERENT literal-pool addresses (all DOL-read, claim CB-FAM2). */
export const TITAN_ROBOT_X = {
  BACKDASH_HSPEED: 40.0, // FLOAT_80439c24 @0x80439c24 → +0x44
  BACKDASH_YVEL: 20.0,   // FLOAT_80439c2c @0x80439c2c → +0x48
  BACKDASH_HDECEL: -1.0, // FLOAT_80439c28 @0x80439c28 → +0x4c
  MOTION_ZERO: 0.0,      // FLOAT_80439c18 @0x80439c18 → +0x38/+0x3c/+0x40
  /** zz_0182fcc_ @0x80182fcc — family child spawner (+0x10 type 0x5c; +0x13 = the
   *  record-select 0..3 passed as `type` here, +0x11 = 0 for 0/1, 1 for 2/3;
   *  update FUN_801830e4, secondary FUN_80183680; returns success bool). */
  SPAWNER_182FCC_ADDR: 0x80182fcc,
} as const;

/** onSteer FUN_80126150 @0x80126150: zz_006d0dc_(actor, 0xc1, 0) face + AIRBORNE-ONLY
 *  (+0x5e0 & 0x40) zz_006e1ac_(actor, 0xc1, 1) aim-pitch seek on channel +0x18da. */
export function titanRobotXOnSteer(actor: RomActor): void {
  faceLockTarget(actor);
  if ((actor.controlWord & 0x40) !== 0) {
    seekAimPitch18da(actor);
  }
}

/** onHit FUN_801261a0 @0x801261a0: face-away + borg-switched spawns + backdash.
 *  pl0604 spawns UNGATED (types 0,1); pl0618 is ammo-gated (zz_006dbe0_(2,1,1),
 *  host-owned — modeled as passing) then spawns types 2,3. The `spawned` flag that
 *  gates the backdash is control-flow (true whenever the branch/gate is taken), NOT
 *  allocation success (verifier extra finding). */
export function titanRobotXOnHit(actor: RomActor, ctx: StreamContext): void {
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff; // +0x5ae = +0x72 − 0x8000
  let spawned = false;
  if (actor.borgNumber === 0x604) {
    ctx.onFamilyProjectile?.(actor, TITAN_ROBOT_X.SPAWNER_182FCC_ADDR, 0);
    ctx.onFamilyProjectile?.(actor, TITAN_ROBOT_X.SPAWNER_182FCC_ADDR, 1);
    spawned = true;
  } else if (actor.borgNumber === 0x618) {
    // zz_006dbe0_(actor, 2, 1, 1) — host ammo gate (approximated as passing).
    ctx.onFamilyProjectile?.(actor, TITAN_ROBOT_X.SPAWNER_182FCC_ADDR, 2);
    ctx.onFamilyProjectile?.(actor, TITAN_ROBOT_X.SPAWNER_182FCC_ADDR, 3);
    spawned = true;
  }
  if (spawned) {
    actor.hSpeed = TITAN_ROBOT_X.BACKDASH_HSPEED;
    actor.yVel = TITAN_ROBOT_X.BACKDASH_YVEL;
    actor.hDecel = TITAN_ROBOT_X.BACKDASH_HDECEL;
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c; // +0x50 = desc+0x6c
  }
  // ALWAYS: motion = 0 — kills the reposition slide.
  actor.motion.x = TITAN_ROBOT_X.MOTION_ZERO;
  actor.motion.y = TITAN_ROBOT_X.MOTION_ZERO;
  actor.motion.z = TITAN_ROBOT_X.MOTION_ZERO;
}

/** Config block @0x8032f498 (raw: 00010002 3f733333 3dcccccd 00000000 80126150
 *  801261a0): groundSlot 1, airSlot 2, scale 0.95, reserved 0.1, onSetup NULL. */
export const TITAN_ROBOT_X_CONFIG: SharedAimedShotConfig = {
  groundSlot: 1,
  airSlot: 2,
  repositionScale: 0.949999988079071, // 0x3f733333 @0x8032f49c
  onSetup: null,
  onSteer: titanRobotXOnSteer,
  onHit: titanRobotXOnHit,
  pitchHalveAlways: false, // wrapper 0x80126110 halves only when +0x5e0&0x40 clear
};

// ============================================================================
// FAMILY 3 — PANTHER ROBOT (ctor 0x8018c2b0): pl0613 PANTHER ROBOT / pl0627 PROTO
// PANTHER. Config @0x8036551c. X = action INDEX 3 (PTR_FUN_8036546c @0x8036546c;
// handler 0x8018cb48 → inner wrapper zz_018cb68_ @0x8018cb68 — no variant dispatch).
// Action INDEX 2 (0x8018cb00) is the morph engine (another module). The ONLY family
// with an onSetup: rocket-punch shape — rise at 4 u/f, always-air stream slot, NO
// backdash and NO motion-zeroing (the blink slide keeps decaying through P1/P2).
// ============================================================================

/** zz_018cba8_ / zz_018cc10_ constants — DOL-read (claims CFG-FAM3, CB-FAM3). */
export const PANTHER_ROBOT_X = {
  /** FLOAT_8043b0fc @0x8043b0fc = 4.0 — onSetup rise velocity (+0x48). */
  RISE_YVEL: 4.0,
  /** zz_01b2b64_ @0x801b2b64 — fist-child spawner (+0x10 type 0x5a; +0x11 = n,
   *  +0x13 = n&1; pool arg 2 not 1; internally borg-gated to 0x613/0x627; alloc-fail
   *  → zz_01b3530_(0, actor); update zz_01b2c8c_, secondary zz_01b3490_). */
  SPAWNER_1B2B64_ADDR: 0x801b2b64,
  /** zz_00f036c_(actor, 0x105) — 2D SFX played when the fists spawn. */
  SPAWN_SFX_CUE: 0x105,
} as const;

/** onSetup zz_018cba8_ @0x8018cba8 (phase 0, AFTER the engine zeroes +0x44..+0x50):
 *  +0x48 = 4.0 (rise) and +0x5e0 |= 0x40 (air-control bit → always the air stream
 *  slot, no ground snap-back in zz_00679d0_, wrapper skips the +0x18da halving, and
 *  the exit path becomes zz_006a750_(7)). */
export function pantherRobotXOnSetup(actor: RomActor): void {
  actor.yVel = PANTHER_ROBOT_X.RISE_YVEL;
  actor.controlWord |= 0x40;
}

/** onSteer zz_018cbc0_ @0x8018cbc0 — byte-for-byte identical logic to family 2's
 *  FUN_80126150 (verified line-for-line): face 0xc1 + airborne-only +0x18da seek. */
export function pantherRobotXOnSteer(actor: RomActor): void {
  titanRobotXOnSteer(actor);
}

/** onHit zz_018cc10_ @0x8018cc10: face-away + rocket-punch fist spawns. pl0613 is
 *  UNGATED; pl0627 runs the ammo gate zz_006dbe0_(2,1,1) (host-owned — modeled as
 *  passing). Before each spawn the ROM sets the per-part flag bytes +0x144/+0x145
 *  |= 0xc0 (LIKELY hiding/detaching the fist model parts — consumer unidentified;
 *  not surfaced on RomActor, honest no-op). NO velocity writes and NO motion-zeroing
 *  — family 3 keeps rising/steering while the blink slide decays. */
export function pantherRobotXOnHit(actor: RomActor, ctx: StreamContext): void {
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff; // +0x5ae = +0x72 − 0x8000
  let spawned = false;
  if (actor.borgNumber === 0x613) {
    // +0x144 |= 0xc0 (part flag, unsurfaced) …
    ctx.onFamilyProjectile?.(actor, PANTHER_ROBOT_X.SPAWNER_1B2B64_ADDR, 8);
    // +0x145 |= 0xc0 …
    ctx.onFamilyProjectile?.(actor, PANTHER_ROBOT_X.SPAWNER_1B2B64_ADDR, 9);
    spawned = true;
  } else if (actor.borgNumber === 0x627) {
    // zz_006dbe0_(actor, 2, 1, 1) — host ammo gate (approximated as passing).
    ctx.onFamilyProjectile?.(actor, PANTHER_ROBOT_X.SPAWNER_1B2B64_ADDR, 10);
    ctx.onFamilyProjectile?.(actor, PANTHER_ROBOT_X.SPAWNER_1B2B64_ADDR, 0xb);
    spawned = true;
  }
  if (spawned) {
    // zz_00f036c_(actor, 0x105) — 2D SFX via the existing sound-cue hook.
    ctx.onPlayCue?.(actor, PANTHER_ROBOT_X.SPAWN_SFX_CUE);
  }
}

/** Config block @0x8036551c (raw: 00010002 3f733333 3dcccccd 8018cba8 8018cbc0
 *  8018cc10): groundSlot 1, airSlot 2, scale 0.95, reserved 0.1 — the only family
 *  with a non-NULL onSetup. */
export const PANTHER_ROBOT_X_CONFIG: SharedAimedShotConfig = {
  groundSlot: 1,
  airSlot: 2,
  repositionScale: 0.949999988079071, // 0x3f733333 @0x80365520
  onSetup: pantherRobotXOnSetup,
  onSteer: pantherRobotXOnSteer,
  onHit: pantherRobotXOnHit,
  pitchHalveAlways: false, // wrapper 0x8018cb68 halves only when +0x5e0&0x40 clear
};

// ============================================================================
// Root actions + configure entry points.
// Ctor notes (claim CTOR-XACTION-WIRING + verifier corrections): both ctors copy a
// 16-word vtable block into +0x4b4..+0x4f0 (fam2 from 0x8032f3c8, block[0] =
// 0x80125dac; fam3 from 0x80365410, block[0] = 0x8018c79c), set the descriptor
// +0x4ac = 0x803c4d94[s8 +0x3e7], and store the shared bank pointers +0x1d84 =
// 0x802BCC64 / +0x1d8c = 0x802BB698 (CORRECTED values — the dig's 0x802ccc64/
// 0x802cb698 dropped the lis/addi borrow; bank binding itself is bridge-side).
// Borg overrides: fam2 pl0618 → +0x4ec = 0x8032f910, +0x4b0 = 0x8032f690; fam3
// pl0627 → +0x4ec = 0x80365218, +0x4b0 = 0x80364f98 (descriptor/command-table data
// the bridge resolves from its extracted JSON, keyed by borg id).
// ============================================================================

/** Root dispatcher FUN_80125dac → PTR_FUN_8032f41c[+0x580]. Table (DOL dump):
 *  [0]=0x80125de8 [1]=0x80125fdc [2]=0x801260a8(morph — other module) [3]=0x801260f0
 *  (X, ported here) [4]=[5]=0x80126018. Null slots fall through to the generic layer
 *  (or compose with the morph module's handler at the bridge). */
export function createTitanRobotRootAction(ctx: StreamContext): (actor: RomActor) => void {
  const xSpecial = createSharedAimedShotX(TITAN_ROBOT_X_CONFIG, ctx);
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,     // 0: 0x80125de8 — TODO port
    null,     // 1: 0x80125fdc — TODO port
    null,     // 2: 0x801260a8 — MORPH engine (another module; compose at the bridge)
    xSpecial, // 3: 0x801260f0 — aimed-shot X (this module)
    null,     // 4: 0x80126018 (dup at [5]) — TODO port
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Root dispatcher FUN_8018c79c → PTR_FUN_8036546c[+0x580]. Table (DOL dump):
 *  [0]=0x8018c7d8 [1]=0x8018c9cc [2]=0x8018cb00(morph — other module) [3]=0x8018cb48
 *  (X, ported here) [4]=0x8018ca08. */
export function createPantherRobotRootAction(ctx: StreamContext): (actor: RomActor) => void {
  const xSpecial = createSharedAimedShotX(PANTHER_ROBOT_X_CONFIG, ctx);
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,     // 0: 0x8018c7d8 — TODO port
    null,     // 1: 0x8018c9cc — TODO port
    null,     // 2: 0x8018cb00 — MORPH engine (another module; compose at the bridge)
    xSpecial, // 3: 0x8018cb48 — aimed-shot X (this module)
    null,     // 4: 0x8018ca08 — TODO port
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a TITAN ROBOT-family actor (pl0604 / pl0618). */
export function configureTitanRobotFamily(
  actor: RomActor,
  borgId: "pl0604" | "pl0618",
  ctx: StreamContext,
): void {
  actor.borgNumber = borgId === "pl0604" ? 0x604 : 0x618;
  actor.rootAction = createTitanRobotRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a PANTHER ROBOT-family actor (pl0613 / pl0627). */
export function configurePantherRobotFamily(
  actor: RomActor,
  borgId: "pl0613" | "pl0627",
  ctx: StreamContext,
): void {
  actor.borgNumber = borgId === "pl0613" ? 0x613 : 0x627;
  actor.rootAction = createPantherRobotRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
