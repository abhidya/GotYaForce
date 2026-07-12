// Shared-engine SERIES-3 (GIRL-BORG pl03xx) X machine — 1:1 port of the
// FUN_8010cdec / FUN_8010ce60 pair and the 3-phase table @0x80325acc =
// [0x8010ceb0 (P0 windup/blink), 0x8010cfbc (P1 active/hit), 0x8010d0d0 (P2 recovery),
// NULL] plus the common exit FUN_8010d28c.
//
// ARCHITECTURE (differs from shared-x-special.ts, and the comment must say so): this
// machine is GLOBAL and CONFIG-LESS. There is NO per-family r4 config block — the
// action-table entry 0x8010cdec loads its own global variant table @0x80325ab8 (all 5
// entries = 0x8010ce60, so +0x581 is behaviorally irrelevant) and 0x8010ce60 loads the
// global phase table @0x80325acc. An earlier scout's "config 0x80325acc" label was a
// misnomer — it is the PHASE table. Per-family flavor lives in INLINE BORG SWITCHES on
// actor+0x3e8 (phase-1 on-hit payloads, phase-2 follow-up stream) plus ctor side data
// (descriptor +0x4ac → gravity at desc+0x6c; per-family anim banks +0x1d80..+0x1d8c, so
// the same slot numbers 0x10..0x13 select different streams per family).
//
// Source: verified dig wav-eng-8010ce60.json (claims M1-M6/C1/W1-W3/F1-F5/P1-P2/N1,
// 17/19 CONFIRMED by two adversarial verifiers; the two REFUTED corrections are
// applied below and cited where they land).
//
// SERVES FOUR FAMILIES / SIX BORGS (claims W1/W2/W3 + P2 wrapper proof):
//   famA   ctor 0x8019c380: pl0303 — actionTable @0x80372108, act[2] AND act[3] = 0x8010cdec
//   famB   ctor 0x801ba020: pl0307/pl030d — actionTable @0x803826d4, act[2] AND act[3] = 0x8010cdec
//   bonus1 ctor 0x80106e3c: pl0301 — actionTable @0x80322e88, act[3] ONLY = 0x8010cdec
//   bonus2 ctor 0x80107e7c: pl0302/pl0306 — actionTable @0x803240f8, act[3] ONLY = 0x8010cdec
// CORRECTION (P1 REFUTED, applied): the dig's port-shape claim said "wire actionTable[2]
// AND [3] for all four families" — both verifiers refuted this for the bonus families:
// ctor 0x80106e3c has act[2] = 0x801073b0 and ctor 0x80107e7c has act[2] = 0x8010821c
// (bespoke handlers, unread). Wiring slot 2 to this machine for pl0301/pl0302/pl0306
// would shadow real bespoke actions, so they register at slot 3 ONLY here.
//
// Machine shape vs shared-x-special.ts (claim M3 NOTE + N1):
//   * stream group 2 (not 4), slots hardcoded 0x10/0x11 (ground/air), NO +0x6ea
//     auto-increment (no combo-cursor convention), trailing zz_004beb8_ args (8,1)
//     instead of (-1,-1) — semantics unresolved, not modeled;
//   * face(0xc1) retained in ALL phases + a ground snap/pos-revert (zz_00679d0_) each frame;
//   * zero internal timers (+0x558/+0x560 never written) — pacing is stream-driven;
//   * no afterimage |motion| gate; contact byte +0x1d10 never referenced;
//   * TWO-tier cooldown: 8.0 (phase-2 air-landing exit) vs 16.0 (common exit) — the
//     ninja shared-X uses a single 4.0.

import type { RomActor, RomPartState } from "../rom/actor.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import {
  groundSnapRevert,
  resetPoseHousekeeping,
  stepPartTargetPitch,
  stepTargetYaw,
} from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Machine constants — every value read from boot.dol (claim F5, dual-verified;
 *  r2 = 0x8043ea20, offsets cited per instruction in the dig). */
export const SERIES3_X = {
  /** FLOAT_8043955c @0x8043955c = 0.949999988079071 — blink-reposition scale, all 3
   *  phases (motion ×= 0.95; pos += motion). Same shape as shared-X's FLOAT_804392d0. */
  REPOSITION_SCALE: 0.949999988079071,
  /** FLOAT_80439554 @0x80439554 = -1.0 — zz_004beb8_ playback rate (both stream starts). */
  STREAM_RATE: -1.0,
  /** FLOAT_80439564 @0x80439564 = 1.0 — phase-2 FUN_80067310 gravity param. */
  GRAVITY: 1.0,
  /** FLOAT_80439558 @0x80439558 = 0.0 — phase-0 motion-scalar zero + exit comparisons. */
  ZERO: 0.0,
  /** FLOAT_8043959c @0x8043959c = 8.0 — +0x694 cooldown on the phase-2 AIR-LANDING exit. */
  COOLDOWN_LANDING: 8.0,
  /** FLOAT_804395a0 @0x804395a0 = 16.0 — +0x694 cooldown on the common exit FUN_8010d28c. */
  COOLDOWN_EXIT: 16.0,
  /** FLOAT_80439550 @0x80439550 = 0.9599999785423279 — +0x1900 meter decay, applied every
   *  frame the X action runs (handler FUN_8010cdec, via the DOUBLE_80439548
   *  int-conversion magic + fctiwz s16 truncation). Meter SEMANTICS UNRESOLVED (U1). */
  METER_1900_DECAY: 0.9599999785423279,
  /** FLOAT_80439540 @0x80439540 = 0.8999999761581421 — +0x18da meter decay, applied each
   *  phase-2 frame gated on (s8)+0x1cef < 0. Meter SEMANTICS UNRESOLVED (U1). */
  METER_18DA_DECAY: 0.8999999761581421,
  /** +0x6ea stream slots (hardcoded immediates, claims M3/M5 — NOT config-read). */
  GROUND_SLOT: 0x10,
  AIR_SLOT: 0x11,
  FOLLOWUP_GROUND_SLOT: 0x12,
  FOLLOWUP_AIR_SLOT: 0x13,
  /** zz_004beb8_ group param (li r5,2 @0x8010cf98) — family bank, group 2 (not 4). */
  STREAM_GROUP: 2,
  /** zz_004beb8_/zz_004cd24_ part mask (0xf, all four parts). */
  PART_MASK: 0xf,
  /** zz_006dbe0_(actor, slot, cost, mode) ammo gate for the 0x303 payload + the
   *  0x307/0x30d follow-up count read. Slot-2 count lives at +0x784 (= +0x774 + slot*8,
   *  DERIVED by verifier 2 from zz_006dbe0_'s decompile — stride-8 record layout). */
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  /** zz_0082824_ @0x80082824 — blast-record child spawner (kind 0, update FUN_80082ab8).
   *  Velocity = actor speed SCALAR (+0xb4) × record row DAT_802d7b30/34/38[rec*0x38]
   *  (one scalar × 3 record floats — verifier F1 nuance; both used rows read (5,5,5):
   *  rec 0x1f @0x802d81f8, rec 0x3b @0x802d8818). */
  BLAST_SPAWNER_ADDR: 0x80082824,
  BLAST_REC_PL0302: 0x1f, // r4=0x1f at bl @0x8010d080
  BLAST_REC_PL0303: 0x3b, // r4=0x3b at bl @0x8010d0ac (ammo-gated)
  /** zz_00c3be0_ @0x800c3be0 — kind-2 child spawner (sub-type at child+0x11, update
   *  FUN_800c3cdc; velocity = actor +0xb4 verbatim, no record scaling — claim F2). */
  CHILD_SPAWNER_ADDR: 0x800c3be0,
  CHILD_SUBTYPE_PL0301: 0x13, // r4=0x13 at bl @0x8010d070
  /** Action-mode bits 0..1 of +0x5e0, cleared on every exit (rlwinm ~3). */
  ACTION_MODE_BITS: 0x3,
} as const;

export interface Series3FamilyCtx extends StreamContext {}

/** Port-side pacing knobs for the stream-end waits the VM can't signal yet. */
export interface Series3XOptions {}

// ---------------------------------------------------------------------------
// Scratch fields (offsets not yet surfaced on RomActor; bridge may mirror them)
// ---------------------------------------------------------------------------
interface Series3Scratch {
  /** +0x1900 meter (s16) — decays ×0.96 per handler frame. Tracked-but-unused:
   *  consumer unread (U1), kept so the eventual consumer dig can light it up. */
  meter1900?: number;
  /** +0x1cf0 part-1 contact byte (bridge-mirrored like contactP0). When absent we
   *  fall back to the stream-VM's part-0 scratch `c` (op 0x02 writes b3 there —
   *  that byte IS +0x1cf0 in the ROM layout). */
  contactP1?: number;
  /** Set by phase 0: the move started airborne (+0x5e0 & 0x40 at entry). Used by the
   *  phase-2 air-landing exit in place of re-reading the live bit (the bridge owns
   *  the 0x40 bit's lifetime; the entry snapshot is the stable signal). */
  series3StartedAir?: boolean;
  /** True once phase 2 restored gravityCoeff from the descriptor (the +0x1d0f event
   *  approximation — see phase 2). */
  series3GravityRestored?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  return (actor as RomActor & Series3Scratch).lockTarget ?? null;
}

/** Airborne test — the ROM reads +0x5e0 & 0x40; the bridge mirrors grounded. */
function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as RomActor & Series3Scratch).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

/** Read the +0x1cf0 part-1 contact byte (signed). Prefers the bridge-mirrored scratch,
 *  falls back to the stream-VM's op-0x02 b3 write on parts[0]. */
function readContactP1(actor: RomActor): number {
  const scratch = (actor as RomActor & Series3Scratch).contactP1;
  if (typeof scratch === "number") return scratch;
  const c = (actor.parts[0] as RomPartState & { c?: number }).c ?? 0;
  return c >= 0x80 ? c - 0x100 : c; // sign-extend the raw byte
}

function clearContactP1(actor: RomActor): void {
  (actor as RomActor & Series3Scratch).contactP1 = 0;
  (actor.parts[0] as RomPartState & { c?: number }).c = 0;
}

const TAU = Math.PI * 2;
/** Port of FUN_800452a0(motion.x, motion.z) — heading BAM16 from a motion vector.
 *  Axis convention matches physics.ts (projectX = sin, projectZ = cos → atan2(x, z)). */
function bamFromVector(x: number, z: number): number {
  if (x === 0 && z === 0) return 0;
  return Math.round((Math.atan2(x, z) / TAU) * 0x10000) & 0xffff;
}

// ============================================================================
// Handler FUN_8010cdec @0x8010cdec — the family actionTable entry. Decays meter
// +0x1900 ×0.96 (s16 trunc via the DOUBLE_80439548 int-conversion magic + fctiwz),
// then dispatches the GLOBAL variant table 0x80325ab8[+0x581] — all 5 entries are
// 0x8010ce60, so the variant index is behaviorally irrelevant (claim M2).
// ============================================================================
function series3Handler(actor: RomActor, ctx: Series3FamilyCtx): void {
  const scratch = actor as RomActor & Series3Scratch;
  const meter = scratch.meter1900 ?? 0;
  scratch.meter1900 = Math.trunc(meter * SERIES3_X.METER_1900_DECAY) | 0; // s16 trunc

  // Wrapper FUN_8010ce60 @0x8010ce60 prologue: `if (+0x541) +0xcc = 0` — the
  // target-invalidated flag clears the lock-target pointer (byte-identical convention
  // to zz_00ff2bc_'s prologue). The bridge owns target validity; not modeled here.
  // Then: dispatch phase table 0x80325acc[(s8)+0x540].
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: series3Phase0(actor, ctx); break;
    case 1: series3Phase1(actor, ctx); break;
    case 2: series3Phase2(actor, ctx); break;
    // Table entry [3] @0x80325ad8 is NULL in the ROM.
    default: break;
  }
}

// ============================================================================
// Phase 0 — FUN_8010ceb0 @0x8010ceb0. Setup + blink-reposition + stream start.
// ============================================================================
function series3Phase0(actor: RomActor, ctx: Series3FamilyCtx): void {
  const scratch = actor as RomActor & Series3Scratch;
  actor.fbPhaseSlots[0] = 1; // +0x540++ (enter phase 1)

  // No lock target (+0xcc == 0) → active yaw = heading (+0x5ac = (s16)+0x72).
  // With a target, zz_006d144_(actor, 0xc1) turns toward it; the bridge pre-computes
  // lockYaw from the live target, so face it directly (shared-x-special precedent).
  const target = lockTargetPos(actor);
  if (!target) {
    actor.activeYaw = actor.heading;
  }
  stepTargetYaw(actor, 0xc1, 0, true);

  // Stream slot select: +0x6ea = 0x10 (ground) / 0x11 (airborne, +0x5e0 & 0x40).
  // NOTE: NO auto-increment (unlike the shared-X/B-ladder combo-cursor, claim N1c).
  const airborne = isAirborne(actor);
  scratch.series3StartedAir = airborne;
  const slot = airborne ? SERIES3_X.AIR_SLOT : SERIES3_X.GROUND_SLOT;
  actor.streamSlot = slot;

  if (airborne) stepPartTargetPitch(actor, 0xc1);

  // Zero motion scalars +0x50/+0x48/+0x4c/+0x44 = FLOAT_80439558 (0.0) and turn rates
  // +0x80/+0x7e/+0x7c = 0 (u16 — not surfaced on RomActor; the scalar zeroes cover the
  // motion model the port integrates).
  actor.hSpeed = SERIES3_X.ZERO;
  actor.yVel = SERIES3_X.ZERO;
  actor.hDecel = SERIES3_X.ZERO;
  actor.gravityCoeff = SERIES3_X.ZERO;
  resetPoseHousekeeping(actor);

  // BLINK-REPOSITION: motion(+0x38) = pos(+0x20) − lockTargetPos(+0x5e8);
  // motion ×= 0.95 (FLOAT_8043955c); pos += motion — the 5%-per-frame pull-away
  // (same shape as shared-X / G Crash). Guarded on target presence like shared-x
  // (the ROM reads +0x5e8 unconditionally; targetless entries have a stale vector).
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(SERIES3_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  groundSnapRevert(actor);

  // START STREAM: zz_004beb8_(rate -1.0 FLOAT_80439554, actor, partMask 0xf, group 2,
  // slot, r7=8, r8=1). The trailing (8,1) args (vs (-1,-1) in the phase-2 follow-up)
  // pass through to zz_004c050_ — semantics UNRESOLVED (N1f); the port's startStream
  // has no equivalent parameters, so they are documented but not modeled.
  startStream(actor, SERIES3_X.PART_MASK, SERIES3_X.STREAM_GROUP, slot, SERIES3_X.STREAM_RATE);

  scratch.series3GravityRestored = false;
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_8010cfbc @0x8010cfbc. Tick + face + reposition + hit transition.
// ============================================================================
function series3Phase1(actor: RomActor, ctx: Series3FamilyCtx): void {
  // zz_004cd24_(actor, 0xf) stream tick.
  tickStream(actor, SERIES3_X.PART_MASK, ctx);

  stepTargetYaw(actor, 0xc1, 0, true);
  if (isAirborne(actor)) stepPartTargetPitch(actor, 0xc1);

  // Reposition continuation: motion ×= 0.95 (FLOAT_8043955c); pos += motion.
  vecScale(SERIES3_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundSnapRevert(actor);

  // HIT TRANSITION on part-0 contact byte (s8)+0x1cef > 0: +0x540++ then the INLINE
  // BORG SWITCH on (s16)actor+0x3e8 — this switch IS the per-family "callback"; there
  // is no config pointer (claims M4/C1).
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    series3XOnHit(actor, ctx);
    return;
  }
}

/** The phase-1 on-hit payload dispatch — port of the inline borg switch at
 *  0x8010d040..0x8010d0b8 (claim M4; spawner details F1/F2). Exported so hosts/tests
 *  can invoke the payload directly. */
export function series3XOnHit(actor: RomActor, ctx: Series3FamilyCtx): void {
  const borg = actor.borgNumber;
  if (borg === 0x302) {
    // zz_0082824_(actor, 0x1f) — blast child, record 0x1f (vel = speed scalar × (5,5,5)).
    ctx.onFamilyProjectile?.(actor, SERIES3_X.BLAST_SPAWNER_ADDR, SERIES3_X.BLAST_REC_PL0302);
  } else if (borg === 0x301) {
    // zz_00c3be0_(actor, 0x13) — kind-2 child, sub-type 0x13 (stored at child+0x11).
    ctx.onFamilyProjectile?.(actor, SERIES3_X.CHILD_SPAWNER_ADDR, SERIES3_X.CHILD_SUBTYPE_PL0301);
  } else if (borg === 0x303) {
    // Ammo gate zz_006dbe0_(actor, 2, 1, 1): nonzero → zz_0082824_(actor, 0x3b);
    // zero (no ammo) → FUN_8010d28c IMMEDIATE EXIT — the ammo failure CANCELS the
    // move (a behavior shared-x has no analog for). Unwired-hook fallback: success.
    const ok = ctx.onAllocateResource?.(
      actor, SERIES3_X.AMMO_SLOT, SERIES3_X.AMMO_COST, 1,
    ) ?? false;
    if (ok) {
      ctx.onFamilyProjectile?.(actor, SERIES3_X.BLAST_SPAWNER_ADDR, SERIES3_X.BLAST_REC_PL0303);
    } else {
      series3CommonExit(actor);
    }
  }
  // borg >= 0x304 (pl0306/pl0307/pl030d): no on-hit payload — famB's flavor is the
  // phase-2 follow-up stream (claim F3).
}

// ============================================================================
// Phase 2 — FUN_8010d0d0 @0x8010d0d0. Recovery: meter decay, famB follow-up stream,
// gravity restore, physics, landing/stream-end exits.
// ============================================================================
function series3Phase2(actor: RomActor, ctx: Series3FamilyCtx): void {
  const scratch = actor as RomActor & Series3Scratch;

  // (1) Meter decay: if (s8)+0x1cef < 0 → +0x18da = (s16)trunc(+0x18da × 0.9)
  // (FLOAT_80439540). +0x18da is the field actor.ts surfaces as steerYaw (G RED uses
  // the same offset as an aim pitch); in THIS machine it is a consumer-less meter (U1).
  if (actor.contactP0 < 0) {
    actor.steerYaw = Math.trunc(actor.steerYaw * SERIES3_X.METER_18DA_DECAY) | 0;
  }

  // (2) Stream tick — all borgs tick zz_004cd24_(actor, 0xf); borgs 0x307/0x30d
  // additionally re-fire a FOLLOW-UP STREAM mid-recovery each time part-1 contact
  // byte (s8)+0x1cf0 goes positive while (s16)+0x784 (slot-2 ammo count, raw read,
  // NO deduct) > 0 — a repeating multi-hit mechanic (claims M5/F3).
  tickStream(actor, SERIES3_X.PART_MASK, ctx);
  if (actor.borgNumber === 0x307 || actor.borgNumber === 0x30d) {
    const hasAmmo = ctx.onAllocateResource?.(
      actor, SERIES3_X.AMMO_SLOT, SERIES3_X.AMMO_COST, 0,
    ) ?? false;
    if (readContactP1(actor) > 0 && hasAmmo) {
      clearContactP1(actor); // +0x1cf0 = 0
      const slot = isAirborne(actor)
        ? SERIES3_X.FOLLOWUP_AIR_SLOT
        : SERIES3_X.FOLLOWUP_GROUND_SLOT;
      actor.streamSlot = slot; // +0x6ea = 0x12 / 0x13
      // zz_004beb8_(-1.0, actor, 0xf, group 2, slot, -1, -1) — trailing args differ
      // from phase 0's (8,1); both unresolved (N1f), not modeled.
      startStream(actor, SERIES3_X.PART_MASK, SERIES3_X.STREAM_GROUP, slot, SERIES3_X.STREAM_RATE);
    }
  }

  // (3) Gravity restore: on stream-event byte (s8)+0x1d0f < 0 the ROM clears it and
  // restores +0x50 = *(descriptor(+0x4ac) + 0x6c) — the per-borg gravity coeff.
  if (actor.dashStrength1d0f < 0) {
    actor.dashStrength1d0f = 0;
    scratch.series3GravityRestored = true;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? SERIES3_X.GRAVITY;
  }

  // (4) FUN_80067310(gravity 1.0 = FLOAT_80439564, actor, yaw (s16)+0x5ae).
  integratePhysics(SERIES3_X.GRAVITY, actor, actor.lockYaw);

  // (5) Reposition continuation: motion ×= 0.95; pos += motion.
  vecScale(SERIES3_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // (6) landed = zz_00679d0_(actor); AIR-LANDING EXIT:
  // `if (landed && (+0x5e0 & 0x40) && (s8)+0x1cef < 0)`: +0x73f = 0 (unsurfaced,
  // no-op); +0x5e0 &= ~3; zz_006a750_(actor, 7) upper-body cue 7; cooldown
  // +0x694 = 8.0 (FLOAT_8043959c) + dt(+0x1dc8); early return (skips the +0x1cee check).
  // APPROXIMATIONS: `landed` = the bridge groundClamp's grounded flag; the 0x40 bit is
  // the phase-0 airborne snapshot; the +0x1cef<0 stream-event gate is modeled as
  // satisfied (same treatment as the meter gate above).
  const grounded = groundSnapRevert(actor);
  if (grounded && scratch.series3StartedAir === true && actor.contactP0 < 0) {
    actor.controlWord &= ~SERIES3_X.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7);
    actor.stateTimer = SERIES3_X.COOLDOWN_LANDING + actor.dt; // +0x694 = 8.0 + dt
    return;
  }

  // (7) Stream-end byte +0x1cee != 0 → FUN_8010d28c common exit.
  if (actor.wallContact !== 0) {
    series3CommonExit(actor);
  }
}

// ============================================================================
// Common exit — FUN_8010d28c @0x8010d28c (claim M6). Called from the phase-1
// no-ammo branch and the phase-2 +0x1cee path.
// ============================================================================
export function series3CommonExit(actor: RomActor): void {
  // +0x73f = 0 (unsurfaced housekeeping flag — no-op); +0x5e0 &= ~3.
  actor.controlWord &= ~SERIES3_X.ACTION_MODE_BITS;

  // +0x5ae = (s16)FUN_800452a0(motion.x +0x38, motion.z +0x40) — heading from the
  // motion vector (atan2-family).
  actor.lockYaw = bamFromVector(actor.motion.x, actor.motion.z);

  // Velocity restructure: if (0.0 <= +0x48) +0x48 = +0x3c (motion.y); then if
  // (0.0 < +0x48) +0x48 = 0.0 — vertical velocity inherited from motion but clamped
  // non-positive (an already-negative yVel is preserved).
  if (SERIES3_X.ZERO <= actor.yVel) actor.yVel = actor.motion.y;
  if (SERIES3_X.ZERO < actor.yVel) actor.yVel = SERIES3_X.ZERO;

  // +0x3c = 0.0 BEFORE the magnitude → +0x44 = |motion| is the HORIZONTAL magnitude.
  actor.motion.y = 0;
  actor.hSpeed = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z); // PSVECMag
  actor.hDecel = 0; // +0x4c = 0.0

  // +0x50 = *(descriptor(+0x4ac) + 0x6c) — gravity restore.
  actor.gravityCoeff = actor.descriptor?.handlerData6c ?? SERIES3_X.GRAVITY;

  // Grounded (!(+0x5e0 & 0x40)) → zz_006a474_ ground idle reset (full-body cue 0);
  // airborne → zz_006a5a4_ air-fall (no cue change — the bridge's completion path
  // transitions the actor out of attack state 61, robot.ts precedent).
  if (!isAirborne(actor)) {
    dispatchFullBodyCue(actor, 0);
  }

  // Attack cooldown +0x694 = 16.0 (FLOAT_804395a0) + dt(+0x1dc8). NOTE the two-tier
  // scheme: 8.0 on the phase-2 air-landing exit vs 16.0 here (ninja shared-X: 4.0).
  actor.stateTimer = SERIES3_X.COOLDOWN_EXIT + actor.dt;
}

/**
 * Build the series-3 shared X handler — the port of the actionTable entry
 * FUN_8010cdec (meter decay + variant dispatch) + FUN_8010ce60 (phase dispatch).
 * CONFIG-LESS by design: per-borg behavior keys off actor.borgNumber at runtime,
 * exactly like the ROM's inline +0x3e8 switches.
 */
export function createSeries3XSpecial(
  ctx: Series3FamilyCtx,
  opts: Series3XOptions = {},
): (actor: RomActor) => void {
  void opts;
  return (actor: RomActor) => series3Handler(actor, ctx);
}

/** The six borgs the ROM routes through this machine (registry @0x802d2ec0, claim W3:
 *  slot 0x1f→pl0301, 0x20→pl0302, 0x21→pl0303, 0x24→pl0306, 0x25→pl0307, 0x2b→pl030d;
 *  the slot→borg formula is LIKELY — three anchors fit, registry consumer unread). */
export type Series3BorgId =
  | "pl0301" | "pl0302" | "pl0303" | "pl0306" | "pl0307" | "pl030d";

const SERIES3_BORG_NUMBERS: Record<Series3BorgId, number> = {
  pl0301: 0x301,
  pl0302: 0x302,
  pl0303: 0x303,
  pl0306: 0x306,
  pl0307: 0x307,
  pl030d: 0x30d,
};

/** Which action-table slots route to 0x8010cdec per family (P1 REFUTED correction +
 *  P2 wrapper proof, both verifiers):
 *   pl0303 (famA @0x80372108):          act[2] @0x80372110 AND act[3] @0x80372114
 *   pl0307/pl030d (famB @0x803826d4):   act[2] @0x803826dc AND act[3] @0x803826e0
 *   pl0301 (bonus1 @0x80322e88):        act[3] @0x80322e94 ONLY (act[2] = 0x801073b0, bespoke/unread)
 *   pl0302/pl0306 (bonus2 @0x803240f8): act[3] @0x80324104 ONLY (act[2] = 0x8010821c, bespoke/unread) */
export function series3XActionSlots(borgNumber: number): ReadonlyArray<number> {
  switch (borgNumber) {
    case 0x303:
    case 0x307:
    case 0x30d:
      return [2, 3];
    default: // 0x301 / 0x302 / 0x306 — slot 3 only (see P1 correction above)
      return [3];
  }
}

/** Root-action dispatcher factory. Only the shared X slots are ported; every other
 *  action row keeps the generic fallback (null). famA's table has 4 rows; famB and the
 *  bonus families have 9 — sized to the widest so stale indices fall through safely. */
export function createSeries3RootAction(
  borgNumber: number,
  ctx: Series3FamilyCtx,
  opts: Series3XOptions = {},
): (actor: RomActor) => void {
  const xSpecial = createSeries3XSpecial(ctx, opts);
  const actionTable: Array<((actor: RomActor) => void) | null> =
    [null, null, null, null, null, null, null, null, null];
  for (const slot of series3XActionSlots(borgNumber)) actionTable[slot] = xSpecial;
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned series-3 (pl03xx) actor: stamps the borg number the
 *  inline switches read and wires the root action with the per-family slot layout.
 *
 *  Residuals NOT wired here (documented, out of the phase machine's scope):
 *   - famB's ammo-gated companion launch aux[1] @0x801ba27c → zz_01d2ffc_ @0x801d2ffc
 *     (kind-0x28 drone, variant 0 = pl0307 / 1 = pl030d; the variant param IS stored
 *     at child+0x11 — F4 REFUTED correction applied to this doc). Its trigger (famB
 *     vtable vt[9] invoker @0x801ba23c, index 1) is untraced (U1) — do not wire it
 *     into the X phases (dig portImplications item 7).
 *   - ctor-time FX child pre-attach zz_013358c_ / zz_00c74ec_ (presentation-side). */
export function configureSeries3Family(
  actor: RomActor,
  borgId: Series3BorgId,
  ctx: Series3FamilyCtx,
  opts: Series3XOptions = {},
): void {
  actor.borgNumber = SERIES3_BORG_NUMBERS[borgId];
  actor.rootAction = createSeries3RootAction(actor.borgNumber, ctx, opts);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
