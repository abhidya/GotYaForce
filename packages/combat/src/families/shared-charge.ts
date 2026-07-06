// Shared charge engine — 1:1 port of `zz_0179814_` @0x80179814 and its 4-phase machine
// table `PTR_FUN_80352b54` @0x80352b54 = [FUN_80179850, FUN_801799bc, FUN_80179a88,
// FUN_80179c00] (chunk_0044.c:3908-4082). This is the B-charge (hold-B → release beam)
// shared by 183 borgs across the roster: the root dispatcher reads the phase byte at
// +0x540 and tail-calls the matching phase function via that table.
//
// MACHINE SHAPE (decomp ground truth, every value read from boot.dol this session):
//   Phase 0 FUN_80179850 (entry/windup): +0x540++; seed +0x560/+0x54e timers from cfg;
//     zero physics (+0x50/+0x48/+0x4c/+0x44 = FLOAT_8043ae10 = 0.0) + turn rates;
//     cfg+0x10 onSetup; reposition leap `motion = (pos-target) × cfg+0x8`; ground snap;
//     streamSlot = (controlWord & 0x40) ? cfg air slot : cfg ground slot; slot++;
//     startStream(rate FLOAT_8043ae04 = -1.0, mask 0xf, GROUP 4, slot, -1, -1).
//   Phase 1 FUN_801799bc (hold): tick stream; face target (0xc1); reposition glide
//     `motion ×= cfg+0x8; pos += motion`; ground snap. RELEASE TRANSITION on stream
//     choreography event `+0x1cef > 0` (op 0x02-authored, NOT a button edge): +0x540++;
//     +0x6f7 = 2; cfg+0x14 onRelease.
//   Phase 2 FUN_80179a88 (fire): +0x6f7 = 2; tick frame-count helper (zz_006de44_);
//     countdown +0x54e / accumulator +0x560; reposition glide; reload gravityCoeff from
//     descriptor+0x6c on +0x1d0f stream event; gravity integrate FUN_80067310(1.0).
//     EXIT: +0x560 <= 0 AND `+0x1cef < 0` (stream fire-complete event) → +0x540++,
//     +0x6f7 = 0. The stream's fireChild op (op 0x09) spawns the beam during this phase.
//   Phase 3 FUN_80179c00 (recovery): steerYaw (+0x18da) × FLOAT_8043ae30 (0.9) decay;
//     gravity integrate; ground check. EXIT A: grounded AND +0x1cef < 0 → +0x5e0 &= ~3,
//     upper cue 7, cooldown +0x694 = FLOAT_8043ae34 (8.0) + dt. EXIT B: +0x1cee
//     (wallContact) != 0 → +0x5e0 &= ~3, zero hSpeed/hDecel, ground-idle or air-fall.
//
// KEY INSIGHT (the whole reason this is its own port vs. reusing shared-engine.ts):
// the ROM's charge release is driven by a STREAM CHOREOGRAPHY EVENT on +0x1cef, NOT a
// frame counter. The beam's spawn frame, the release moment, and the fire-complete
// moment are all authored in the group-4 stream bytecode (op 0x02 writes +0x1cef;
// op 0x09 fireChild spawns the projectile). This replaces the existing TUNED
// chargeFrames accumulator (30/90 frame thresholds in combat.ts's B-charge branch).
//
// Constants (dol.py-read this session, all CONFIRMED byte-exact): FLOAT_8043ae04 =
// -1.0 (0xbf800000); FLOAT_8043ae10 = 0.0 (0x00000000); FLOAT_8043ae1c = 1.0
// (0x3f800000); FLOAT_8043ae30 = 0.9 (0x3f666666); FLOAT_8043ae34 = 8.0 (0x41000000);
// DOUBLE_8043ae08 = 0x43300000_80000000 (the PPC s16→f32 int-conversion magic — not
// directly used in the TS port, which has native number coercion).

import type { RomActor } from "../rom/actor.js";
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

/** Engine constants — every value read from boot.dol this session (dol.py). */
export const SHARED_CHARGE = {
  /** FLOAT_8043ae04 @0x8043ae04 = 0xbf800000 — stream playback rate (zz_004beb8_ arg 1). */
  STREAM_RATE: -1.0,
  /** FLOAT_8043ae10 @0x8043ae10 = 0x00000000 — the 0.0 zeroing/comparison constant. */
  ZERO: 0.0,
  /** FLOAT_8043ae1c @0x8043ae1c = 0x3f800000 — gravity param to FUN_80067310 (phases 2 & 3). */
  GRAVITY: 1.0,
  /** FLOAT_8043ae30 @0x8043ae30 = 0x3f666666 — steerYaw (+0x18da) per-tick decay in phase 3. */
  STEER_DECAY: 0.8999999761581421,
  /** FLOAT_8043ae34 @0x8043ae34 = 0x41000000 — cooldown +0x694 seed on phase-3 grounded exit. */
  COOLDOWN_SEED: 8.0,
  /** Stream group — immediate `li r5,4` in FUN_80179850 (group 4 = charge/air-special axis). */
  STREAM_GROUP: 4,
  /** Part mask passed to every stream call in this machine (zz_004beb8_/zz_004cd24_ arg 2). */
  PART_MASK: 0xf,
} as const;

/**
 * Per-family config for the shared charge machine — the ROM's r4 config block.
 * Layout (G RED @0x80365854, dol.py-read this session):
 *   cfg u32[+0x0] (low byte) = ground stream slot (= 2 for G RED)
 *   cfg u32[+0x4] (low byte) = air stream slot (= 2 for G RED)
 *   cfg f32[+0x8]            = reposition scale (0.95 for G RED)
 *   cfg s16[+0xc]            = +0x560 fire-timer seed (30 for G RED)
 *   cfg u16[+0xe]            = +0x54e countdown seed (30 for G RED)
 *   cfg ptr[+0x10]           = onSetup callback (phase 0, after physics zero)
 *   cfg ptr[+0x14]           = onRelease callback (phase 1→2 stream-event transition)
 */
export interface SharedChargeConfig {
  /** cfg u32[+0x0] low byte — group-4 stream slot when grounded (controlWord & 0x40 clear). */
  seedSlot: number;
  /** cfg u32[+0x4] low byte — group-4 stream slot when airborne (controlWord & 0x40 set). */
  airSlot: number;
  /** cfg s16[+0xc] → +0x560 — fire-phase timer seed (frames). Counts down by dt in phase 2;
   *  phase 2's stream-event exit gate only fires once this reaches 0. NOT the release trigger
   *  (that's the +0x1cef stream event in phase 1). */
  chargeFrames: number;
  /** cfg f32[+0x8] — reposition scale: phase-0 leap `motion = (pos-target) × scale; pos += motion`
   *  AND phase-1/2 per-tick glide `motion ×= scale; pos += motion`. */
  repositionScale: number;
  /** Descriptor+0x6c gravityCoeff — reloaded in phase 2 on the +0x1d0f stream event and used
   *  as the integrator's per-actor gravity multiplier. Falls back to 1.0 when no descriptor. */
  gravityCoeff: number;
  /** cfg ptr[+0x10] — fired once at the end of phase 0 setup (after physics zero + before the
   *  reposition leap). Engine ignores its return (verified). NULL = not called. */
  onSetup?: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** cfg ptr[+0x14] — fired once on the phase-1→2 stream-event transition (the release moment),
   *  BEFORE the phase byte increments. NULL = not called. */
  onRelease?: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** PORT APPROXIMATION (labeled): phase 1 has no ROM timer — the release is the +0x1cef > 0
   *  stream event, authored in the group-4 slot bytecode (op 0x02). Until the bank-byte
   *  extractor lands, the bridge does not drive +0x1cef for B-charge (only X-special action 2
   *  banks are pre-decoded). After this frame budget with no event, advance to phase 2 WITHOUT
   *  the onRelease callback (labeled fallback — same caveat class as shared-charge3.whiffFrames
   *  and gred.ts's 81-frame whiff recovery). TUNED. */
  holdFrames?: number;
}

/** Host-mirrored scratch the bridge stamps onto the actor (same pattern as shared-charge3.ts). */
interface ChargeScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  return (actor as RomActor & ChargeScratch).lockTarget ?? null;
}

const DEFAULT_HOLD_FRAMES = 30;

// ============================================================================
// Phase 0 — FUN_80179850 @0x80179850 (chunk_0044.c:3919). Entry/windup.
// ============================================================================
function chargePhase0(actor: RomActor, cfg: SharedChargeConfig, ctx: StreamContext): void {
  // +0x540++ FIRST (chunk_0044.c:3929).
  actor.fbPhaseSlots[0] = 1;

  // Seed the two machine-local timers (chunk_0044.c:3930-3932):
  //   +0x560 (float accumulator) = cfg s16[+0xc] via the s16→f32 idiom.
  //   +0x54e (s16 countdown)    = cfg u16[+0xe].
  // handlerTimer stands in for +0x560 (the fire-phase countdown); the +0x54e countdown is
  // modeled as a port-local scratch (it gates the zz_006de44_ frame-count extension of phase 2,
  // which without byte-loaded stream data behaves identically to +0x560).
  actor.handlerTimer = cfg.chargeFrames;
  (actor as RomActor & { chargeCountdown54e?: number }).chargeCountdown54e = cfg.chargeFrames;

  // Stream slot select (chunk_0044.c:3933-3936): ground slot, air slot on controlWord 0x40.
  const slot = (actor.controlWord & 0x40) !== 0 ? cfg.airSlot : cfg.seedSlot;
  // +0x6f7 = 0 (state byte; chunk_0044.c:3937).
  (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 0;

  // Lock-yaw snapshot when no target (chunk_0044.c:3938-3940): +0x5ac = +0x72 (heading).
  if (!lockTargetPos(actor)) {
    actor.activeYaw = actor.heading;
  }

  // Face target (zz_006d1a8_/zz_006e39c_ with 0xc1) — bridge pre-aims lockYaw; no-op here.
  // Zero motion scalars +0x50/+0x48/+0x4c/+0x44 = FLOAT_8043ae10 = 0.0 (chunk_0044.c:3943-3947)
  // and turn rates +0x80/+0x7e/+0x7c = 0 (chunk_0044.c:3948-3950).
  actor.gravityCoeff = SHARED_CHARGE.ZERO;
  actor.yVel = SHARED_CHARGE.ZERO;
  actor.hDecel = SHARED_CHARGE.ZERO;
  actor.hSpeed = SHARED_CHARGE.ZERO;

  // cfg+0x10 onSetup (chunk_0044.c:3951-3953): fired AFTER the physics zero, BEFORE the leap.
  cfg.onSetup?.(actor, ctx);

  // REPOSITION LEAP (chunk_0044.c:3954-3958): motion = pos − lockTargetPos; motion ×= cfg+0x8;
  // pos += motion. The "leaps away then dashes in" windup spacing.
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  // zz_00677b0_ ground snap (chunk_0044.c:3959).
  groundClamp(actor);

  // Stream start (chunk_0044.c:3960-3963): the slot is captured pre-increment, then +0x6ea is
  // bumped for the combo follow-up (matching G RED's pattern). startStream(group 4, slot).
  actor.streamSlot = slot;
  startStream(
    actor,
    SHARED_CHARGE.PART_MASK,
    SHARED_CHARGE.STREAM_GROUP,
    slot,
    SHARED_CHARGE.STREAM_RATE,
  );
  actor.streamSlot = slot + 1;
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_801799bc @0x801799bc (chunk_0044.c:3969). Hold — stream-driven release.
// ============================================================================
function chargePhase1(actor: RomActor, cfg: SharedChargeConfig, ctx: StreamContext): void {
  // Tick the stream (chunk_0044.c:3974) — drives the choreography whose op 0x02 sets +0x1cef.
  tickStream(actor, SHARED_CHARGE.PART_MASK, ctx);
  // Face target (zz_006d1a8_/zz_006e39c_ 0xc1) — bridge pre-aims lockYaw; no-op here.

  // Reposition glide (chunk_0044.c:3977-3979): motion ×= cfg+0x8; pos += motion.
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundClamp(actor); // zz_00677b0_

  // RELEASE TRANSITION (chunk_0044.c:3981-3988): the stream's choreography event.
  // The ROM tests `0 < +0x1cef` (s8) — i.e. contactP0 > 0 — the same hit flag G RED's G
  // Crash phase 1 polls. The op 0x02 in the group-4 slot bytecode authors the exact release
  // frame; this is the "stream-event-driven release" that replaces a frame counter.
  // (The task brief's "+0x1cef < 0" prose describes the family of stream-event gates; the
  // decompile's sign for THIS transition is > 0. Phase 2's fire-complete gate is < 0.)
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 2; // +0x6f7 = 2
    cfg.onRelease?.(actor, ctx);
    return;
  }

  // PORT APPROXIMATION (labeled — see cfg.holdFrames): without the byte-loaded group-4 slot
  // data the bridge cannot fire the +0x1cef event for B-charge. Advance to phase 2 after the
  // holdFrames budget so the machine does not stall in the windup forever. The onRelease
  // callback is NOT fired on this fallback path (mirrors shared-charge3.whiffFrames semantics).
  const scratch = actor as RomActor & { holdFallbackCounter?: number };
  scratch.holdFallbackCounter = (scratch.holdFallbackCounter ?? 0) + 1;
  if (scratch.holdFallbackCounter >= (cfg.holdFrames ?? DEFAULT_HOLD_FRAMES)) {
    actor.fbPhaseSlots[0] = 2;
    (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 2;
  }
}

// ============================================================================
// Phase 2 — FUN_80179a88 @0x80179a88 (chunk_0044.c:3994). Fire — countdown + fireChild.
// ============================================================================
function chargePhase2(actor: RomActor, cfg: SharedChargeConfig, ctx: StreamContext): void {
  // +0x6f7 = 2 (firing state; chunk_0044.c:4002).
  (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 2;

  // Frame-count helper zz_006de44_(actor, 0xf0f00) + countdown bookkeeping
  // (chunk_0044.c:4003-4013): when the helper returns nonzero, +0x54e and +0x560 are
  // adjusted by min(+0x54e, uVar2). Without byte-loaded stream data the helper is 0, so
  // neither timer moves here — the +0x560 decrement below is the sole driver. Ported as a
  // no-op (the extension only matters while the beam is actively connecting).
  // Face target + reposition glide (chunk_0044.c:4014-4018).
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // Reload gravityCoeff from descriptor+0x6c on the +0x1d0f stream event
  // (chunk_0044.c:4019-4022). +0x1d0f isn't surfaced by the VM; the cfg.gravityCoeff
  // (the descriptor default) applies unconditionally — labeled approximation matching
  // shared-charge3.ts's recoveryGravityCoeff treatment.
  actor.gravityCoeff = cfg.gravityCoeff;

  // Gravity integrate FUN_80067310(FLOAT_8043ae1c = 1.0, actor, +0x5ae) (chunk_0044.c:4023).
  integratePhysics(SHARED_CHARGE.GRAVITY, actor, actor.activeYaw);
  groundClamp(actor); // zz_00677b0_

  // EXIT gate (chunk_0044.c:4025-4037): when +0x560 <= 0.0 AND +0x1cef < 0 (stream
  // fire-complete event), advance to phase 3. The fireChild op (0x09) in the group-4
  // bytecode spawns the beam at its choreographed frame during this phase's stream ticks.
  if (actor.handlerTimer <= SHARED_CHARGE.ZERO) {
    tickStream(actor, SHARED_CHARGE.PART_MASK, ctx);
    if (actor.contactP0 < 0) {
      // Stream fire-complete event → phase 3.
      actor.fbPhaseSlots[0] = 3; // +0x540++
      (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 0; // +0x6f7 = 0
      return;
    }
    // FALLBACK (labeled): +0x1cef never went negative because the slot bytecode isn't
    // byte-loaded. Advance to recovery so the machine completes. The timer IS the ROM's
    // own +0x560 countdown (cfg.chargeFrames), so this fallback is exact for the fire
    // DURATION — only the stream-event EXACTNESS is lost.
    actor.fbPhaseSlots[0] = 3;
    (actor as RomActor & { phaseState6f7?: number }).phaseState6f7 = 0;
    return;
  }

  // Timer still positive: decrement +0x560 by dt (chunk_0044.c:4033). Tick the stream
  // (chunk_0044.c:4034-4036) only while +0x1cef >= 0 (not yet fire-complete).
  actor.handlerTimer -= actor.dt;
  if (actor.contactP0 >= 0) {
    tickStream(actor, SHARED_CHARGE.PART_MASK, ctx);
  }
}

// ============================================================================
// Phase 3 — FUN_80179c00 @0x80179c00 (chunk_0044.c:4043). Recovery — ground check + idle.
// ============================================================================
function chargePhase3(actor: RomActor, _cfg: SharedChargeConfig, ctx: StreamContext): void {
  // steerYaw (+0x18da) × FLOAT_8043ae30 (0.9) decay (chunk_0044.c:4053-4056). The ROM
  // does the multiply in f32 (PPC single precision) then truncates to s16 via (int)(short).
  // Math.fround simulates the f32 rounding (1000 × 0.8999999761... rounds to 900.0f, not
  // 899.9999... as f64 would keep); Math.trunc matches the (int) cast.
  actor.steerYaw = Math.trunc(Math.fround(actor.steerYaw * SHARED_CHARGE.STEER_DECAY));

  // Gravity integrate FUN_80067310(1.0, actor, +0x5ae) (chunk_0044.c:4057).
  integratePhysics(SHARED_CHARGE.GRAVITY, actor, actor.activeYaw);
  const grounded = (actor as RomActor & ChargeScratch).grounded === true; // zz_00677b0_

  // EXIT A (chunk_0044.c:4059-4065): grounded AND +0x1cef < 0 → upper cue 7, cooldown seed.
  if (grounded && actor.contactP0 < 0) {
    actor.controlWord = actor.controlWord & ~0x3; // +0x5e0 &= 0xfffffffc
    dispatchUpperBodyCue(actor, 7); // zz_006a750_(actor, 7)
    actor.stateTimer = SHARED_CHARGE.COOLDOWN_SEED + actor.dt; // +0x694 = 8.0 + dt
    actor.steerYaw = 0; // +0x18da = 0
    return;
  }

  // Tick stream (chunk_0044.c:4067).
  tickStream(actor, SHARED_CHARGE.PART_MASK, ctx);

  // EXIT B (chunk_0044.c:4069-4080): +0x1cee (wallContact) != 0 → clear action bits,
  // zero hSpeed/hDecel, ground-idle or air-fall.
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3; // +0x5e0 &= 0xfffffffc
    actor.hDecel = SHARED_CHARGE.ZERO; // +0x4c = 0.0
    actor.hSpeed = SHARED_CHARGE.ZERO; // +0x44 = 0.0
    if (grounded) {
      // zz_006a474_ ground idle reset.
      dispatchUpperBodyCue(actor, 7);
      dispatchFullBodyCue(actor, 0);
    } else {
      // zz_006a5a4_ air-fall exit — clear the action bits (done above) so the bridge's
      // completion path runs the fall state (labeled approximation, same as gred.ts phase 3).
      dispatchUpperBodyCue(actor, 7);
    }
  }
  // NOTE: phase 3 never increments +0x540; exit is solely the +0x5e0 &= ~3 clear (the
  // bridge's tick loop detects completion via the stream frame count / stateTimer).
}

// ============================================================================
// G RED family config @0x80365854 (dol.py-read this session).
//  bytes: 00 00 00 02 00 00 00 02 3f 73 33 33 00 1e 00 1e 80 18 ed a8 80 18 ed c4
//   cfg u32[+0x0] = 0x00000002 → ground slot 2
//   cfg u32[+0x4] = 0x00000002 → air slot 2
//   cfg f32[+0x8] = 0x3f733333 → reposition scale 0.95
//   cfg s16[+0xc] = 0x001e → fire-timer seed 30
//   cfg u16[+0xe] = 0x001e → countdown seed 30
//   cfg ptr[+0x10] = 0x8018eda8 → onSetup (FUN_8018eda8)
//   cfg ptr[+0x14] = 0x8018edc4 → onRelease (FUN_8018edc4)
// The callbacks (family-code-block addresses) are not ported yet — they carry
// G RED-specific beam-spawn bookkeeping the stream's fireChild op already covers.
// ============================================================================
/** G RED (pl0615/pl0629/pl062a) shared-charge config — the ROM r4 block @0x80365854. */
export const GRED_CHARGE_CONFIG: SharedChargeConfig = {
  seedSlot: 2,          // cfg u32[+0x0] low byte
  airSlot: 2,           // cfg u32[+0x4] low byte
  chargeFrames: 30,     // cfg s16[+0xc] → +0x560 fire timer
  repositionScale: 0.949999988079071, // cfg f32[+0x8] (0x3f733333)
  gravityCoeff: 1.0,    // descriptor+0x6c default (G RED ground gravity)
  onSetup: null,        // cfg ptr[+0x10] = FUN_8018eda8 — not yet ported
  onRelease: null,      // cfg ptr[+0x14] = FUN_8018edc4 — not yet ported
};

/**
 * Build the shared-charge phase handler for one family config — the port of the
 * `zz_0179814_` root dispatcher + its 4-entry phase table. Wire the result as
 * actionTable[3] in the family's root action dispatcher.
 */
export function createSharedCharge(
  cfg: SharedChargeConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: chargePhase0(actor, cfg, ctx); break;
      case 1: chargePhase1(actor, cfg, ctx); break;
      case 2: chargePhase2(actor, cfg, ctx); break;
      case 3: chargePhase3(actor, cfg, ctx); break;
      default: break;
    }
  };
}
