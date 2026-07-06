// Shared-engine LANCE FLIGHT X-machine — 1:1 port of `zz_0149708_` @0x80149708 and its
// 6-phase table `PTR_FUN_8033ed3c` @0x8033ed3c = [0x80149758, 0x8014989c, 0x80149954,
// 0x80149a7c, 0x80149c08, 0x80149db8] (+ NULL at index 6; the next word 0x8033ed58
// begins a DIFFERENT machine's table — zz_0149ec8_ — not part of this engine).
//
// The knight-line (pl0700-pl070d) X-special: a pitch-steered FLYING LANCE CHARGE with
// button-fueled flight extension. Unlike the 3-phase shared X (`zz_00ff2bc_`,
// shared-x-special.ts), the config block here is 0x24 bytes of PURE DATA — no callback
// pointers anywhere (every param_2 access across all six phases was enumerated; the
// per-family port is literally a config object).
//
// Config mechanism (raw-disasm proven — Ghidra dropped every r4 load): each family's
// x-action-2 handler dispatches (*variantTable[+0x581])() where ALL 5 entries point at
// ONE per-family wrapper; the wrapper loads r4 = config via lis/addi and bl's the
// engine; the engine passes r4 UNTOUCHED into every phase function (raw disasm
// 0x80149708-0x80149744 writes only r0/r5/r12 before bctrl).
//   family 1 ctor 0x800c7c80 (pl0700/pl0709):  wrapper 0x800c8538 → cfg @0x80308078
//   family 2 ctor 0x801223c0 (pl0701/pl0708/pl070c/pl070d): wrapper 0x801233cc is the
//     only BORG-SWITCHED one (lha +0x3e8): 0x701/0x708 → cfg A @0x8032c814,
//     0x70c/0x70d → cfg B @0x8032c838 (= A+0x24)
//   family 3 ctor 0x80143b7c (pl0702/pl070a):  wrapper 0x80144504 → cfg @0x8033c3d4
//   family 4 ctor 0x8019c510 (pl0705/pl070b):  wrapper 0x8019cfb4 → cfg @0x80373848
//
// Source: verified dig wav-eng-80149708 (20/21 claims CONFIRMED dual-lens; the ONE
// REFUTED sub-fact — the pitch-steer PSVECSubtract direction — is applied below, see
// steerPitchTowardTarget). Corpus: research/decomp/ghidra-export/chunk_0038.c:2356-2628.
//
// Config block layout (0x24 bytes, every field's consumer cited):
//   s32 +0x00 groundSlot   (P0: +0x6ea = cfg[0], group-4 stream slot when grounded)
//   s32 +0x04 airSlot      (P0: override when airborne, +0x5e0 & 0x40)
//   s32 +0x08 landSlot     (P4 ground exit landing stream; −1 = none — all 5 shipped
//                           configs are −1)
//   f32 +0x0c reposScale   (P0/P1/P2 PSQUATScale on motion +0x38 — the blink-away)
//   s16 +0x10 flightTime   (P2: +0x548 = cfg×10; drains −10 per +0x1b01 frame in P3)
//   s16 +0x12 extendBudget (P2: +0x54a = cfg×10 — the button-extension pool)
//   u16 +0x14 extendRate   (P2: +0x54c = cfg; decays −1 per input frame in P3)
//   u16 +0x16 extendRateFloor (P2 copies to +0x54e [write-only, consumer unresolved];
//                           P3 clamps +0x54c to this floor)
//   f32 +0x18 speed0       (P2 → +0x38 — motion vec REPURPOSED as flight-speed scratch)
//   f32 +0x1c speedMax     (P2 → +0x3c; P3 clamp)
//   f32 +0x20 accel        (P2 → +0x40; P3: +0x38 += +0x40 × dt)

import type { RomActor, Vec3 } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  integratePhysics,
  projectX,
  projectZ,
  vecSubtract,
  vecScale,
  vecAdd,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

/** Machine constants — every value read from boot.dol via dol.py (dig MACHINE-9,
 *  dual-lens re-read; r2-relative anchors verified with r2 = 0x8043ea20). */
export const FLIGHT_X = {
  /** FLOAT_8043a360 = 0.8999999761581421 (0x3f666666) — P4/P5 pitch decay AND the
   *  zz_006ed8c_ velocity-decay coefficient. */
  DECAY: 0.9,
  /** FLOAT_8043a374 = 0.0 (0x00000000) — zero scalar (+0x80c, +0x4c/+0x50, timer floor). */
  ZERO: 0.0,
  /** FLOAT_8043a378 = 1.0 (0x3f800000) — FUN_80067310 gravity param, all integrator calls. */
  GRAVITY: 1.0,
  /** FLOAT_8043a37c = −1.0 (0xbf800000) — stream playback rate, every zz_004beb8_ call. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a384 = 60.0 (0x42700000) — P0 windup / face-target timer (+0x558). */
  WINDUP_TIMER: 60.0,
  /** FLOAT_8043a388 = 8.0 (0x41000000) — +0x694 cooldown at all 3 exits (NOTE: 8.0,
   *  not the ninja shared-X's 4.0 = FLOAT_804392d8). */
  COOLDOWN: 8.0,
  /** DOUBLE_8043a398 = 0.5 (0x3fe0000000000000) — P4 speed threshold on +0x44. */
  SPEED_EPSILON: 0.5,
  /** FLOAT_8043a3a0 = 120.0 (0x42f00000) — P4→P5 air-recovery timer (+0x558). */
  AIR_RECOVERY_TIMER: 120.0,
  /** FLOAT_8043a3a4 = 0.25 (0x3e800000) — P4 hitstop dt substitution (dt is swapped to
   *  0.25 around the stream tick when the contact byte +0x1cef reads NEGATIVE). */
  HITSTOP_DT: 0.25,
  /** FLOAT_804376d8 = 0.8999999761581421 (0x3f666666) — zz_006e1d0_ no-target pitch decay. */
  NO_TARGET_PITCH_DECAY: 0.9,
  /** All windup/flight/decel/landing streams are group 4 (li r5, 4 in the disasm). */
  STREAM_GROUP: 4,
  /** P3 flight-time drain per +0x1b01 frame (`+0x548 += −10`). */
  FLIGHT_DRAIN: 10,
  /** P2 config→runtime scale for flightTime/extendBudget (`cfg × 10`). */
  TIME_SCALE: 10,
  /** zz_006e1ac_ thunk passes 0x4000 → desired pitch clamped to ±0x4000 (±90° BAM). */
  PITCH_CLAMP: 0x4000,
  /** zz_006de44_ mask 0xf0f00 — the flight-extend input: face-button press-edges
   *  A/B/X/Y (0x0f00) + direction press-edges (bits 16-19, the remapped 'high direction
   *  byte' per pad-bit-binding-decode-2026-07-05.md:179/289-291). */
  EXTEND_INPUT_MASK: 0xf0f00,
  /** P4 airborne branch: generic fall stream — zz_004beb8_(−1.0, actor, 0xf, group 0,
   *  slot 0xd, 0x14, 1). The trailing args (0x14, 1) aren't surfaced by the port's
   *  startStream signature (same simplification every module using this stream makes). */
  FALL_STREAM_GROUP: 0,
  FALL_STREAM_SLOT: 0xd,
  // DOUBLE_8043a368 (raw 0x4330000080000000) is the compiler's s16→double conversion
  // magic constant — scaffolding, not behavior; no port needed.
} as const;

/** Per-family config for the lance-flight machine (the ROM's 0x24-byte r4 block). */
export interface SharedFlightXConfig {
  /** cfg s32 +0x00: group-4 stream slot when grounded (P0 seeds +0x6ea). */
  groundSlot: number;
  /** cfg s32 +0x04: group-4 stream slot when airborne (+0x5e0 & 0x40). */
  airSlot: number;
  /** cfg s32 +0x08: group-4 landing stream slot for the P4 ground exit; −1 = none
   *  (all five shipped configs are −1 — kept for layout fidelity). */
  landSlot: number;
  /** cfg f32 +0x0c: reposition scale — motion ×= this each P0/P1/P2 frame (0.95, or
   *  0.92 for family-2 cfg B). */
  reposScale: number;
  /** cfg s16 +0x10: base flight time seed — runtime +0x548 = this × 10, draining 10
   *  per active flight frame (so the raw value ≈ base flight FRAMES). */
  flightTime: number;
  /** cfg s16 +0x12: button-extension pool seed — runtime +0x54a = this × 10. */
  extendBudget: number;
  /** cfg u16 +0x14: extension transfer rate seed (+0x54c) — units moved from the pool
   *  into flight time per input frame, decaying −1 each transfer. */
  extendRate: number;
  /** cfg u16 +0x16: floor for the decaying transfer rate (+0x54c clamp). Also copied
   *  to +0x54e at launch — write-only within this machine (consumer unresolved). */
  extendRateFloor: number;
  /** cfg f32 +0x18: initial flight speed (P2 → the repurposed motion.x / +0x38). */
  speed0: number;
  /** cfg f32 +0x1c: flight speed cap (→ motion.y / +0x3c). */
  speedMax: number;
  /** cfg f32 +0x20: flight acceleration per dt (→ motion.z / +0x40). */
  accel: number;
  /** PORT APPROXIMATION (not a ROM field): frames P2 waits for the stream-raised
   *  launch signal (+0x1cee) before launching anyway. The ROM's windup anim raises
   *  +0x1cee via a stream event; our banks aren't byte-loaded (same gap gred.ts and
   *  shared-x-special.ts document), so actor.wallContact is polled AND this frame
   *  budget stands in as the fallback. TUNED (default 30). */
  launchFrames?: number;
}

const DEFAULT_LAUNCH_FRAMES = 30; // TUNED — see SharedFlightXConfig.launchFrames.

/** PORT APPROXIMATION: per-frame pitch-steer step in BAM units. The ROM's rate is
 *  s16 descriptor(+0x4ac)[0xac + (mask&0xf)*2] × f32 actor+0x768 (mask 0xc0 → row 0);
 *  neither the +0xac turn-rate row nor +0x768 is surfaced on RomActor yet, so a TUNED
 *  constant stands in (≈5.6°/frame). Labeled, replace when the descriptor rows load. */
const PITCH_STEP_BAM = 0x400;

/** Scratch fields the machine keeps on the actor (ROM offsets in comments). The
 *  lockTarget/grounded/extendInput fields are host-synced by the bridge each frame. */
interface FlightScratch {
  /** Bridge-synced lock-target position (the +0x5e8/+0x518 lock block pos). */
  lockTarget?: Vec3 | null;
  /** Bridge-synced ground flag (zz_00677b0_ returns 1 on land-snap — NOTE the
   *  decompile's sense; gred.ts:177's old comment is inverted). */
  grounded?: boolean;
  /** Host-set: any extend-input press-edge this frame — popcount(+0x5bc & 0xf0f00) != 0.
   *  LIKELY mash semantics (+0x5bc is the press-edge pad word per
   *  pad-bit-binding-decode-2026-07-05.md; a Dolphin watch would settle hold-vs-mash). */
  extendInput?: boolean;
  /** +0x541: target-invalidated flag (P0 range-gate fail; engine prologue clears the
   *  +0xcc lock pointer while set — modeled by lockTargetPos returning null). */
  flightTargetInvalid?: boolean;
  /** +0x548: flight time in drain units (s16; −10 per active flight frame). */
  flightUnits?: number;
  /** +0x54a: extension pool in drain units (s16). */
  extendUnits?: number;
  /** +0x54c: current transfer rate (s16; decays −1 per input frame to the cfg floor). */
  xferRate?: number;
}

function lockTargetPos(actor: RomActor): Vec3 | null {
  const s = actor as RomActor & FlightScratch;
  // Engine prologue `if (+0x541) { +0xcc = 0; }` — while the invalid flag is set the
  // lock pointer is cleared, so every target read comes back null.
  if (s.flightTargetInvalid) return null;
  return s.lockTarget ?? null;
}

/** Airborne test — the ROM reads +0x5e0 & 0x40; the bridge mirrors grounded. */
function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as RomActor & FlightScratch).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

/** Radians → BAM16 (inverse of physics.ts bam16ToRad). */
function radToBam(rad: number): number {
  return Math.round((rad / (Math.PI * 2)) * 0x10000);
}

/** Face the lock target — zz_006d144_(actor, 0xc0). Mask 0xc0 writes BOTH +0x5ae
 *  (lockYaw, bit 0x40) and +0x72 (heading, bit 0x80) every step, so during P0-P3 the
 *  flight direction continuously tracks the target (horizontal homing). The bridge
 *  pre-computes lockYaw from the live target each frame, so facing is instantaneous
 *  here (the ROM steps at descriptor turn-rate row 0 × dt — labeled approximation,
 *  same as shared-melee-lunge). Returns true when facing complete (the ROM's
 *  FUN_80066a30 returns 1 when |remaining yaw delta| <= step). */
function faceLockTarget(actor: RomActor): boolean {
  const target = lockTargetPos(actor);
  if (!target) return false;
  actor.activeYaw = actor.lockYaw;
  actor.heading = actor.lockYaw;
  return true;
}

/**
 * Pitch steer — port of zz_006e1ac_(actor, 0xc0, 1) @0x8006e1ac, a thunk for
 * zz_006e1d0_(actor, 0xc0, 1, 0x4000). Steers the channel-1 pitch s16 at +0x18da
 * (actor.steerYaw) toward the lock target; pitch > 0 dives, pitch = 0 is level flight
 * (P3 projects hSpeed = v×cos(pitch), yVel = −v×sin(pitch)).
 *
 * CORRECTED per the dig's one REFUTED sub-fact (HELPER-1 verdict): the decompile is
 * PSVECSubtract((actor+0x518), &chan1AimVec, &out) and PSVECSubtract is dst = a − b
 * (raw ps_sub decode of 0x8020ba78: f6 = [r3] − [r4]), so dy = lockPos.y − aimVec.y —
 * i.e. "+0x518 minus the chan-1 aim vector", NOT the dig's original "aim vector minus
 * +0x518" reading. (Sanity: target above → dy > 0 → desired pitch < 0 → yVel > 0 →
 * climbs toward it.)
 *
 * PORT APPROXIMATIONS (labeled):
 *  - the chan-1 aim anchor (+0x910/+0x920/+0x930, a body-mounted aim origin) isn't
 *    surfaced — actor.pos stands in;
 *  - the ROM's desired = clamp(−(s16 +0x70) − atan2BAM(dy, |dxz|), ±0x4000); the base
 *    pitch s16 +0x70 isn't surfaced — approximated 0 (level body);
 *  - step rate: PITCH_STEP_BAM stands in for descriptor(+0x4ac)[0xac] × f32 +0x768.
 *
 * Returns 1 when the desired pitch is reached, 0 while stepping, −1 with no target
 * (no-target path decays pitch ×0.9 = FLOAT_804376d8 toward 0).
 */
function steerPitchTowardTarget(actor: RomActor): number {
  const target = lockTargetPos(actor);
  if (!target) {
    actor.steerYaw = Math.trunc(actor.steerYaw * FLIGHT_X.NO_TARGET_PITCH_DECAY);
    return -1;
  }
  const dx = target.x - actor.pos.x;
  const dy = target.y - actor.pos.y; // CORRECTED direction: lockPos − aim anchor.
  const dz = target.z - actor.pos.z;
  const dxz = Math.hypot(dx, dz); // ROM zeroes the vec's y (FLOAT_80437658=0.0) → |dxz|.
  let desired = -radToBam(Math.atan2(dy, dxz)); // basePitch (+0x70) ≈ 0 approximation.
  if (desired > FLIGHT_X.PITCH_CLAMP) desired = FLIGHT_X.PITCH_CLAMP;
  if (desired < -FLIGHT_X.PITCH_CLAMP) desired = -FLIGHT_X.PITCH_CLAMP;
  const delta = desired - actor.steerYaw;
  if (Math.abs(delta) <= PITCH_STEP_BAM) {
    actor.steerYaw = desired;
    return 1;
  }
  actor.steerYaw += Math.sign(delta) * PITCH_STEP_BAM;
  return 0;
}

/** Velocity decay — port of zz_006ed8c_(k, actor) @0x8006ed8c: dt-corrected
 *  exponential decay of +0x44/+0x48 (exact ×k when dt == 1.0 = FLOAT_80437670,
 *  else v −= v×(1−k)×dt). Same identity shared-melee-lunge documents. */
function decayVelocity(k: number, actor: RomActor): void {
  if (actor.dt === 1) {
    actor.hSpeed *= k;
    actor.yVel *= k;
  } else {
    actor.hSpeed -= actor.hSpeed * (1 - k) * actor.dt;
    actor.yVel -= actor.yVel * (1 - k) * actor.dt;
  }
}

// ============================================================================
// Phase 0 — FUN_80149758 @0x80149758. Windup setup + blink-reposition + stream.
// ============================================================================
function flightPhase0(actor: RomActor, cfg: SharedFlightXConfig, ctx: StreamContext): void {
  const s = actor as RomActor & FlightScratch;
  actor.fbPhaseSlots[0] = 1; // +0x540++
  s.flightTargetInvalid = false; // fresh activation (+0x540 was reset by the cue dispatch)

  // Stream cursor +0x6ea = cfg groundSlot, overridden by airSlot when airborne
  // (+0x5e0 & 0x40).
  const slot = isAirborne(actor) ? cfg.airSlot : cfg.groundSlot;
  actor.streamSlot = slot;

  // Range gate FUN_80066838(f32 +0x868 row, actor) < 1 → target invalid: +0x541=1,
  // +0xcc=0, +0x5ac=+0x72 (yaw stays at heading). PORT APPROXIMATION: the +0x868
  // per-command-type range rows are runtime-populated (writer unlocated — same gap
  // shared-melee-lunge.ts documents), so the gate fires on lock-target absence only;
  // the in-range distance check (dist ≤ range × f32 +0xb4) is not modeled.
  const target = lockTargetPos(actor);
  if (!target) {
    s.flightTargetInvalid = true; // +0x541 = 1 (prologue keeps the lock pointer cleared)
    actor.activeYaw = actor.heading; // +0x5ac = +0x72
  } else {
    faceLockTarget(actor); // zz_006d144_(actor, 0xc0)
  }

  actor.handlerTimer = FLIGHT_X.WINDUP_TIMER; // +0x558 = 60.0 (FLOAT_8043a384)
  steerPitchTowardTarget(actor); // zz_006e1ac_(actor, 0xc0, 1)

  // Reposition: motion(+0x38) = pos(+0x20) − lockTargetPos(+0x5e8); motion ×= cfg
  // reposScale; pos += motion — the blink-away windup (PSVECSubtract dst = a − b).
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.reposScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  // Commit zz_00679d0_ — ground-probe + position commit; the port's integrator/bridge
  // ground clamp covers it (no separate call needed here).

  // zz_004beb8_(−1.0 = FLOAT_8043a37c, actor, partMask 0xf, group 4, slot = +0x6ea
  // then +0x6ea++, −1, −1).
  startStream(actor, 0xf, FLIGHT_X.STREAM_GROUP, slot, FLIGHT_X.STREAM_RATE);
  actor.streamSlot = slot + 1;
  // +0x80c = 0.0 (FLOAT_8043a374) — unsurfaced scratch float; no-op in the port.
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_8014989c @0x8014989c. Reposition tail + face-target budget.
// ============================================================================
function flightPhase1(actor: RomActor, cfg: SharedFlightXConfig, ctx: StreamContext): void {
  // Reposition continuation: motion ×= reposScale; pos += motion; commit.
  vecScale(cfg.reposScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // ROM gates the tick on s8 +0x1b03 != 0 (part-anim-hold byte, not surfaced by the
  // VM) — PORT APPROXIMATION: tick unconditionally (the shared-x/ninja precedent).
  tickStream(actor, 0xf, ctx);

  steerPitchTowardTarget(actor); // zz_006e1ac_(actor, 0xc0, 1)

  actor.handlerTimer -= actor.dt; // +0x558 −= dt(+0x1dc8)
  // Transition on (timer <= 0.0) OR facing complete (zz_006d144_(0xc0) != 0). C
  // short-circuit: the face-step only runs while the timer > 0. The bridge pre-aims
  // lockYaw, so facing completes on the first tick when a target exists — the 60f
  // budget matters for the targetless case (same shape as shared-melee-lunge P1).
  const facingComplete = actor.handlerTimer > 0 && faceLockTarget(actor);
  if (actor.handlerTimer <= FLIGHT_X.ZERO || facingComplete) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    actor.handlerTimer = 0; // reused in P2 as the count-up launch budget (port-side)
  }
}

// ============================================================================
// Phase 2 — FUN_80149954 @0x80149954. Second windup anim; waits for the stream
// launch signal (+0x1cee), then loads the flight params from config and lifts off.
// ============================================================================
function flightPhase2(actor: RomActor, cfg: SharedFlightXConfig, ctx: StreamContext): void {
  const s = actor as RomActor & FlightScratch;
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)
  faceLockTarget(actor); // zz_006d144_(actor, 0xc0)
  steerPitchTowardTarget(actor); // zz_006e1ac_(actor, 0xc0, 1)

  // Reposition continue: motion ×= reposScale; pos += motion; commit.
  vecScale(cfg.reposScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // LAUNCH on s8 +0x1cee != 0 (actor.wallContact) — the stream-raised launch signal
  // set during the windup anim. PORT APPROXIMATION (labeled per launchFrames): the
  // raising stream event isn't byte-loaded, so a frame budget backs the poll.
  actor.handlerTimer += actor.dt;
  const launch =
    actor.wallContact !== 0 ||
    actor.handlerTimer >= (cfg.launchFrames ?? DEFAULT_LAUNCH_FRAMES);
  if (!launch) return;

  actor.fbPhaseSlots[0] = 3; // +0x540++

  // LOAD FLIGHT PARAMS FROM CONFIG (chunk_0038.c:2455-2467):
  s.flightUnits = cfg.flightTime * FLIGHT_X.TIME_SCALE;   // +0x548 = cfg[+0x10] × 10
  s.extendUnits = cfg.extendBudget * FLIGHT_X.TIME_SCALE; // +0x54a = cfg[+0x12] × 10
  s.xferRate = cfg.extendRate;                            // +0x54c = cfg[+0x14]
  // +0x54e = cfg[+0x16] — written here in the ROM, never read by this machine
  // (consumer unresolved — HUD/AI?); no port-side storage needed.

  // The motion vec +0x38/+0x3c/+0x40 is REPURPOSED as flight-speed scratch:
  actor.motion.x = cfg.speed0;   // +0x38 = cfg[+0x18] (current speed)
  actor.motion.y = cfg.speedMax; // +0x3c = cfg[+0x1c] (speed cap)
  actor.motion.z = cfg.accel;    // +0x40 = cfg[+0x20] (accel per dt)
  actor.hDecel = FLIGHT_X.ZERO;      // +0x4c = 0.0
  actor.gravityCoeff = FLIGHT_X.ZERO; // +0x50 = 0.0 (gravity OFF during flight)

  // zz_0066530_(actor, 0x2d) — hover-mode ON: +0x5e4 = 0x2d, +0x87 = 1, +0x5e0 |= 0x40.
  // (+0x87 isn't surfaced; the cue byte + control-word bit carry the behavior.)
  actor.ubCue = 0x2d;
  actor.controlWord |= 0x40;

  // zz_00b2190_(actor, 0) — trail FX init (renderer-side; honest no-op here).

  // Start the flight stream: zz_004beb8_(−1.0, actor, 0xf, group 4, +0x6ea then ++).
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, FLIGHT_X.STREAM_GROUP, slot, FLIGHT_X.STREAM_RATE);
}

// ============================================================================
// Phase 3 — FUN_80149a7c @0x80149a7c. THE FLIGHT — pitch-steered lance charge
// with button-fueled flight extension.
// ============================================================================
function flightPhase3(actor: RomActor, cfg: SharedFlightXConfig, ctx: StreamContext): void {
  const s = actor as RomActor & FlightScratch;

  // (a) BUTTON EXTEND: zz_006de44_(actor, 0xf0f00) != 0 — any press-edge among
  // A/B/X/Y + the direction bits this frame (host-synced boolean; LIKELY mash
  // semantics — see FlightScratch.extendInput). One transfer per input frame:
  // xfer = old rate; rate = max(rate − 1, cfg floor); xfer = min(xfer, pool);
  // pool −= xfer; flight += xfer (the 8→2-decaying budget→time transfer).
  if (s.extendInput) {
    let xfer = s.xferRate ?? cfg.extendRate;
    s.xferRate = Math.max(xfer - 1, cfg.extendRateFloor);
    const pool = s.extendUnits ?? 0;
    if (pool < xfer) xfer = pool;
    s.extendUnits = pool - xfer;
    s.flightUnits = (s.flightUnits ?? 0) + xfer;
  }

  // (b) face + pitch-steer (horizontal + vertical homing).
  faceLockTarget(actor); // zz_006d144_(actor, 0xc0) — steers +0x5ae AND +0x72
  steerPitchTowardTarget(actor); // zz_006e1ac_(actor, 0xc0, 1)

  // (c) SPEED: +0x38 += +0x40 × dt; clamp ≤ +0x3c (the repurposed motion scratch).
  actor.motion.x += actor.motion.z * actor.dt;
  if (actor.motion.x > actor.motion.y) actor.motion.x = actor.motion.y;

  // (d) PROJECT VELOCITY BY PITCH +0x18da: +0x44 = speed × cos(pitch)
  // [zz_0045238_ = cos], +0x48 = speed × −sin(pitch) [zz_0045204_ = sin] —
  // pitch > 0 dives, pitch = 0 level flight.
  actor.hSpeed = actor.motion.x * projectZ(actor.steerYaw);
  actor.yVel = actor.motion.x * -projectX(actor.steerYaw);

  // (e) integrate FUN_80067310(1.0 = FLOAT_8043a378, actor, yaw +0x5ae); commit; tick.
  integratePhysics(FLIGHT_X.GRAVITY, actor, actor.lockYaw);
  tickStream(actor, 0xf, ctx);

  // (f) FLIGHT TIMER: gated on s8 +0x1b01 != 0 (stream-written drain gate, not
  // surfaced by the VM) — PORT APPROXIMATION: always-on, making base flight =
  // flightTime frames + extension (the dig's sanctioned reading).
  s.flightUnits = (s.flightUnits ?? 0) - FLIGHT_X.FLIGHT_DRAIN;
  if (s.flightUnits < 0) {
    actor.fbPhaseSlots[0] = 4; // +0x540++
    // Decel stream: zz_004beb8_(−1.0, actor, 0xf, group 4, +0x6ea then ++, −1, −1).
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, FLIGHT_X.STREAM_GROUP, slot, FLIGHT_X.STREAM_RATE);
  }
  // (g) zz_00b22f4_(actor) — afterimage FX every frame (renderer-side; no-op here).
}

// ============================================================================
// Phase 4 — FUN_80149c08 @0x80149c08. Decel / impact / land.
// ============================================================================
function flightPhase4(actor: RomActor, cfg: SharedFlightXConfig, ctx: StreamContext): void {
  const s = actor as RomActor & FlightScratch;

  // Pitch decay: +0x18da = (s16)(pitch × 0.9 [FLOAT_8043a360]).
  actor.steerYaw = Math.trunc(actor.steerYaw * FLIGHT_X.DECAY);
  // Velocity decay zz_006ed8c_(0.9, actor) on +0x44/+0x48.
  decayVelocity(FLIGHT_X.DECAY, actor);
  // Integrate FUN_80067310(1.0 [FLOAT_8043a378], actor, +0x5ae).
  integratePhysics(FLIGHT_X.GRAVITY, actor, actor.lockYaw);
  // Ground test + snap zz_00677b0_(actor) — returns 1 on the land-snap path (fires
  // the +0x754 landing callback); bridge-synced as scratch.grounded. (The decompile's
  // return sense: 1 = grounded — gred.ts:177's old comment had it inverted.)
  const grounded = s.grounded === true;

  if (actor.hSpeed >= FLIGHT_X.SPEED_EPSILON) {
    // Branch 1 — still moving (+0x44 >= 0.5 = DOUBLE_8043a398): HITSTOP when the
    // contact byte +0x1cef reads NEGATIVE (blocked-hit marker; exact producer
    // unresolved): the ROM swaps dt(+0x1dc8) to 0.25 (FLOAT_8043a3a4) around the
    // stream tick, then restores it.
    if (actor.contactP0 < 0) {
      const savedDt = actor.dt;
      actor.dt = FLIGHT_X.HITSTOP_DT;
      tickStream(actor, 0xf, ctx);
      actor.dt = savedDt;
    } else {
      tickStream(actor, 0xf, ctx);
    }
    // zz_00b22f4_ afterimage (renderer-side no-op).
    return;
  }

  if (!grounded) {
    // Branch 2 — slow + airborne: → phase 5 (air recovery).
    actor.fbPhaseSlots[0] = 5; // +0x540++
    actor.handlerTimer = FLIGHT_X.AIR_RECOVERY_TIMER; // +0x558 = 120.0 (FLOAT_8043a3a0)
    actor.lockYaw = actor.heading; // +0x5ae = +0x72
    // Gravity restored from the descriptor: +0x50 = f32 descriptor(+0x4ac)[+0x6c].
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 1; // fallback 1 when unset
    // Generic fall stream: zz_004beb8_(−1.0, actor, 0xf, group 0, slot 0xd, 0x14, 1)
    // (trailing args not surfaced by the port's startStream — see FLIGHT_X note).
    startStream(actor, 0xf, FLIGHT_X.FALL_STREAM_GROUP, FLIGHT_X.FALL_STREAM_SLOT, FLIGHT_X.STREAM_RATE);
    return;
  }

  // Branch 3 — slow + grounded: LANDING EXIT.
  actor.steerYaw = 0; // +0x18da = 0
  // +0x73f = 0 — byte cleared at all exits (semantics unresolved; unsurfaced no-op).
  actor.controlWord &= ~0x3; // +0x5e0 &= ~3 (action-mode bits)
  if (cfg.landSlot >= 0) {
    // Landing stream (gated `if (-1 < cfg[+8])` — no shipped config uses it).
    startStream(actor, 0xf, FLIGHT_X.STREAM_GROUP, cfg.landSlot, FLIGHT_X.STREAM_RATE);
  }
  actor.controlWord &= ~0x40; // hover bit off
  actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 1; // +0x50 = descriptor gravity
  // Real zz_006a474_ call (chunk_0038.c:2582) — runs AFTER the descriptor gravity
  // restore above and zeroes +0x50 again (ROM order preserved; the restore is dead
  // on this path in the ROM too). Decomp-verified helper — the old cues-0/0 mapping
  // was refuted.
  romGroundIdleReturn(actor);
  actor.stateTimer = FLIGHT_X.COOLDOWN + actor.dt; // +0x694 = 8.0 (FLOAT_8043a388) + dt
}

// ============================================================================
// Phase 5 — FUN_80149db8 @0x80149db8. Air recovery (no cfg use — the ROM signature
// takes only the actor).
// ============================================================================
function flightPhase5(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & FlightScratch;
  // Pitch decay ×0.9 (FLOAT_8043a360).
  actor.steerYaw = Math.trunc(actor.steerYaw * FLIGHT_X.DECAY);
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)
  integratePhysics(FLIGHT_X.GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0, +0x5ae)

  const grounded = s.grounded === true; // zz_00677b0_ != 0 (land-snap)
  if (grounded) {
    actor.steerYaw = 0; // +0x18da = 0 (+0x73f = 0 — unsurfaced no-op)
    actor.controlWord &= ~0x3; // +0x5e0 &= ~3
    // LANDING EXIT zz_006a750_(actor, 7) — upper-body cue 7.
    dispatchUpperBodyCue(actor, 7);
    actor.stateTimer = FLIGHT_X.COOLDOWN + actor.dt; // +0x694 = 8.0 + dt
    return;
  }
  actor.handlerTimer -= actor.dt; // +0x558 −= dt
  if (actor.handlerTimer <= FLIGHT_X.ZERO) {
    actor.steerYaw = 0;
    actor.controlWord &= ~0x3;
    romAirKnockoutReturn(actor); // real zz_006a5a4_ call (chunk_0038.c:2614) —
    // upper cue 6; the old cue-7 approximation was wrong.
    actor.stateTimer = FLIGHT_X.COOLDOWN + actor.dt;
  }
}

/**
 * Build the lance-flight phase handler for one family config — the port of the
 * per-family wrapper (0x800c8538 / 0x801233cc / 0x80144504 / 0x8019cfb4) +
 * `zz_0149708_` dispatch. Wire as actionTable[2] in the family root dispatcher
 * (all 5 variant-table entries point at the same wrapper, so variantIndex is ignored).
 */
export function createSharedFlightX(
  cfg: SharedFlightXConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // Engine prologue: `if (+0x541) { +0xcc = 0; }` — modeled inside lockTargetPos
    // (the flag keeps every lock-target read null until the next activation).
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: flightPhase0(actor, cfg, ctx); break;
      case 1: flightPhase1(actor, cfg, ctx); break;
      case 2: flightPhase2(actor, cfg, ctx); break;
      case 3: flightPhase3(actor, cfg, ctx); break;
      case 4: flightPhase4(actor, cfg, ctx); break;
      case 5: flightPhase5(actor, ctx); break;
      // Table entry [6] is NULL in the ROM (PTR_FUN_8033ed3c + 0x18 = 0).
      default: break;
    }
  };
}

// ============================================================================
// Shipped config blocks — every value from the byte-exact DOL dumps (dig CONFIG-3..6,
// dual-lens re-read). f32 raws noted where the JS double differs in the last bits.
// ============================================================================

/** Family 1 (ctor 0x800c7c80; pl0700/pl0709) config @0x80308078. */
export const FLIGHT_X_FAMILY1_CONFIG: SharedFlightXConfig = {
  groundSlot: 0,
  airSlot: 3,
  landSlot: -1,
  reposScale: 0.95, // 0x3f733333 = 0.949999988079071
  flightTime: 3,    // → 30 units = 3 base flight frames
  extendBudget: 4,  // → 40 units
  extendRate: 8,
  extendRateFloor: 2,
  speed0: 0.0,
  speedMax: 30.0,   // 0x41f00000
  accel: 2.0,       // 0x40000000
};

/** Family 2 cfg A (ctor 0x801223c0; pl0701/pl0708) @0x8032c814. EXPORTED FOR
 *  REFERENCE ONLY — family 2 is already served by an existing registration
 *  (bridge.ts makeSamuraiFamilyRegistration); do not double-register. Note
 *  flightTime = 0: base flight ends immediately unless button-extended. */
export const FLIGHT_X_FAMILY2A_CONFIG: SharedFlightXConfig = {
  groundSlot: 0,
  airSlot: 0,
  landSlot: -1,
  reposScale: 0.95, // 0x3f733333
  flightTime: 0,
  extendBudget: 3,  // → 30 units
  extendRate: 8,
  extendRateFloor: 2,
  speed0: 0.0,
  speedMax: 30.0,
  accel: 2.0,
};

/** Family 2 cfg B (pl070c/pl070d) @0x8032c838 (= A + 0x24) — the only borg-switched
 *  wrapper (lha +0x3e8 in 0x801233cc). Reference only, as above. */
export const FLIGHT_X_FAMILY2B_CONFIG: SharedFlightXConfig = {
  groundSlot: 0,
  airSlot: 0,
  landSlot: -1,
  reposScale: 0.92, // 0x3f6b851f = 0.9200000166893005
  flightTime: 0,
  extendBudget: 2,  // → 20 units
  extendRate: 8,
  extendRateFloor: 2,
  speed0: 0.0,
  speedMax: 30.0,
  accel: 2.0,
};

/** Family 3 (ctor 0x80143b7c; pl0702/pl070a) config @0x8033c3d4. Longest base
 *  flight of the line (flightTime 4). */
export const FLIGHT_X_FAMILY3_CONFIG: SharedFlightXConfig = {
  groundSlot: 0,
  airSlot: 3,
  landSlot: -1,
  reposScale: 0.95, // 0x3f733333
  flightTime: 4,    // → 40 units
  extendBudget: 3,  // → 30 units
  extendRate: 8,
  extendRateFloor: 2,
  speed0: 0.0,
  speedMax: 30.0,
  accel: 2.0,
};

/** Family 4 (ctor 0x8019c510; pl0705/pl070b) config @0x80373848. flightTime 0 +
 *  the biggest extension pool (5 → 50 units): a pure mash/hold-fueled flight. */
export const FLIGHT_X_FAMILY4_CONFIG: SharedFlightXConfig = {
  groundSlot: 0,
  airSlot: 3,
  landSlot: -1,
  reposScale: 0.95, // 0x3f733333
  flightTime: 0,
  extendBudget: 5,  // → 50 units
  extendRate: 8,
  extendRateFloor: 2,
  speed0: 0.0,
  speedMax: 30.0,
  accel: 2.0,
};

// The former lance-flight family registration block (LanceFlightBorgId /
// LANCE_FLIGHT_BORGS / createLanceFlightRootAction / configureLanceFlightFamily)
// was superseded by the samurai-cluster registration (families/samurai.ts wires
// createSharedFlightX directly with the per-family configs above) and deleted.
