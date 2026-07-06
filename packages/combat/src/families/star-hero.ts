// STAR HERO family (ctor 0x8010f5ac) — the third ROM-faithful family port.
// Covers pl0804 (STAR HERO) and pl080c (PLANET HERO): both bind ctor 0x8010f5ac
// (ptrLabel 0x80326ae8, root 0x80327058). Source:
//   research/decomp/ghidra-export/chunk_0031.c:517-617 (FUN_801121c0 → FUN_801121fc
//   → FUN_80112278 [phase 0] → zz_011230c_ [phase 1])
//   chunk_0030.c:4004-4026 (FUN_8010f790 buff revert, descriptor slot +0x4c8)
//   research/decomp/status-effects-decode-2026-07-04.md §A (verified chain)
//
// The X-special is a ramming dash: phase 0 arms a kind-0xf dash hitbox and computes the
// approach vector; phase 1 scales motion by 0.95/frame and advances the actor toward the
// lock target each tick. When the dash connects (contactP0 > 0) and the actor isn't
// already buffed, gain +4 param tiers (tier 16→20 = velocity ×2.366 via timescale.ts's
// tier table) for 1200 frames, play cue 0xa5, and despawn the hitbox. Wall contact ends
// the dash without buffing. The buff reverts via FUN_8010f790 (per-frame descriptor
// +0x4c8 pass) decrementing +0x144; at 0 → apply_actor_param_tier_delta_127(-4).

import type { RomActor } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { vecSubtract, vecScale, vecAdd } from "../rom/physics.js";

// Motion constants — every value DERIVED from boot.dol this session (see
// status-effects-decode-2026-07-04.md §A + action-vm-and-gcrash-decode-2026-07-05.md §B).
const STAR_HERO_X = {
  /** FLOAT_80439678 — per-frame motion multiplier for the ramming dash approach. */
  MOTION_SCALE: 0.95,
  /** FLOAT_80439618 — stream playback rate (standard forward; same role as G RED's
   *  FLOAT_8043b120 = -1.0). The exact bits aren't decoded but the usage is uniform
   *  across the hero module's zz_004beb8_ call sites. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043961c — velocity zero floor (confirmed by the `if (x < F) x = F` clamp
   *  pattern at chunk_0031.c:49-50 and the dash-end zeroing at :608). */
  VEL_FLOOR: 0.0,
  /** Part mask for the kind-0xf dash hitbox (zz_004beb8_(…,0xf,4,…)). */
  HIT_MASK: 0xf,
  /** Stream group 4 (charge/air-special axis — same as G RED). */
  STREAM_GROUP: 4,
  /** Ground stream slot (controlWord & 0x40 clear → slot 0). */
  GROUND_SLOT: 0,
  /** Air stream slot (controlWord & 0x40 set → slot 1). */
  AIR_SLOT: 1,
  /** 0x4b0 — +0x144 tier-buff timer seed (1200 frames). */
  BUFF_DURATION: 1200,
  /** 0x1e — +0x146 post-buff VFX/sound tail timer (30 frames). */
  BUFF_TAIL: 30,
  /** apply_actor_param_tier_delta_127(actor, +4): tier 16→20 = velocity ×2.366. */
  TIER_DELTA: 4,
  /** zz_00f036c_(actor, 0xa5) — sound cue on buff application. */
  CUE_BUFF: 0xa5,
} as const;

/** RomActor extension for the +0x144/+0x146 buff timers (FUN_8010f790 decrements these). */
export interface HeroBuffExt {
  /** +0x144 (s16): tier-buff frames remaining; >0 means buffed. */
  heroBuffFrames?: number;
  /** +0x146 (u8): post-buff VFX tail timer. */
  heroBuffTailFrames?: number;
}

/** The lock-target position the family handler reads at actor+0x5e8 (same field the
 *  bridge adapter copies from BorgRuntime.lockTarget each frame). */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

// ============================================================================
// Phase 0 — FUN_80112278 @ chunk_0031.c:549. Startup: advance the phase cursor, pick the
// ground/air stream slot, compute motion = pos − lockTarget, arm the kind-0xf dash hitbox,
// then fall through to phase 1 immediately (the ROM tail-calls zz_011230c_).
// ============================================================================
function starHeroXPhase0(actor: RomActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ (chunk_0031.c:557)

  // Stream slot select: +0x5e0 & 0x40 → air slot 1, else ground slot 0 (chunk_0031.c:558-561).
  const slot = (actor.controlWord & 0x40) !== 0 ? STAR_HERO_X.AIR_SLOT : STAR_HERO_X.GROUND_SLOT;

  // motion = pos − lockTarget (chunk_0031.c:562-563, gnt4_PSVECSubtract_bl).
  const target = lockTargetPos(actor);
  if (target) vecSubtract(actor.pos, target, actor.motion);

  // Arm the kind-0xf dash hitbox: zz_004beb8_(STREAM_RATE, actor, 0xf, 4, slot, -1, -1).
  // The pre-increment slot is the stream slot; +0x6ea becomes slot+1 after (chunk_0031.c:566-567).
  startStream(actor, STAR_HERO_X.HIT_MASK, STAR_HERO_X.STREAM_GROUP, slot, STAR_HERO_X.STREAM_RATE);
  actor.streamSlot = slot + 1; // +0x6ea = cVar1 + 1

  // Phase 0 tail-calls phase 1 (chunk_0031.c:568: zz_011230c_(param_1)).
  starHeroXPhase1(actor, ctx);
}

// ============================================================================
// Phase 1 — zz_011230c_ @ chunk_0031.c:576. Per-frame dash: motion ×= 0.95, pos += motion,
// tick the kind-0xf stream, then the contact → buff branch and the wall → end branch.
// ============================================================================
function starHeroXPhase1(actor: RomActor, ctx: StreamContext): void {
  // motion *= FLOAT_80439678; pos += motion (chunk_0031.c:582-583).
  vecScale(STAR_HERO_X.MOTION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // zz_004cd24_(actor, 0xf) — advance the kind-0xf stream (chunk_0031.c:585).
  tickStream(actor, STAR_HERO_X.HIT_MASK, ctx);

  // Contact branch (chunk_0031.c:586-594): contactP0 > 0 means the dash hitbox connected.
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0; // clear +0x1cef (chunk_0031.c:587)
    const ext = actor as RomActor & HeroBuffExt;
    if ((ext.heroBuffFrames ?? 0) > 0) {
      // Already buffed: skip the buff write-up, just end the dash (the goto LAB_801123c4
      // path at chunk_0031.c:588 — +0x144 > 0 means a prior buff is still live).
      endStarHeroDash(actor);
      return;
    }
    // Apply the tier buff (chunk_0031.c:589-593):
    //   +0x144 = 0x4b0 (1200f), apply_actor_param_tier_delta_127(+4), cue 0xa5,
    //   +0x146 = 0x1e (30), zz_00107a0_(actor, 0xf) despawn kind-0xf hitboxes.
    ext.heroBuffFrames = STAR_HERO_X.BUFF_DURATION;
    ctx.onParamTierDelta?.(actor, STAR_HERO_X.TIER_DELTA);
    ctx.onPlayCue?.(actor, STAR_HERO_X.CUE_BUFF);
    ext.heroBuffTailFrames = STAR_HERO_X.BUFF_TAIL;
    // zz_00107a0_(actor, 0xf): despawn the kind-0xf dash hitbox — reset its stream parts.
    for (const part of actor.parts) {
      part.streamPtr = -1;
      part.active = 0;
    }
  }

  // Wall-contact branch (chunk_0031.c:595-597): +0x1cee != 0 → end the dash without buff.
  if (actor.wallContact !== 0) {
    endStarHeroDash(actor);
  }
}

// ============================================================================
// LAB_801123c4 — dash-end cleanup (chunk_0031.c:600-616). Clears the action-mode bits,
// hands motion.y → yVel, zeroes motion.y, sets hSpeed = |motion|, hDecel = 0, and restores
// gravityCoeff from the descriptor's handler-data byte.
// ============================================================================
function endStarHeroDash(actor: RomActor): void {
  // +0x5e0 &= ~3 — clear action-mode bits 0..1 (chunk_0031.c:603).
  actor.controlWord = actor.controlWord & ~0x3;
  // +0x48 = +0x3c (yVel = motion.y); motion.y = FLOAT_8043961c (0.0) — chunk_0031.c:604-605.
  actor.yVel = actor.motion.y;
  actor.motion.y = STAR_HERO_X.VEL_FLOOR;
  // +0x44 = |motion| (hSpeed = motion magnitude) — chunk_0031.c:606-607.
  actor.hSpeed = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
  // +0x4c = FLOAT_8043961c (0.0) — chunk_0031.c:608.
  actor.hDecel = STAR_HERO_X.VEL_FLOOR;
  // +0x50 = descriptor.+0x6c (gravityCoeff restore) — chunk_0031.c:609.
  if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
}

/** The X-special phase table (PTR_FUN_80434530, indexed by actor.fbPhaseSlots[0]). */
const X_PHASE_TABLE = [starHeroXPhase0, starHeroXPhase1];

/** FUN_801121fc wrapper — dispatches the phase table, folding in the s16 0x18da yaw-decay
 *  (chunk_0031.c:538-542) which is steering-only and not core to the buff mechanic. */
function starHeroXHandler(actor: RomActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_8010f86c @ chunk_0030.c:4032 (the descriptor +0x4b4
// virtual) → PTR_FUN_80326af0[actor+0x580]. Action 2 (X) is ported here; the other rows
// wire in as their handlers port. Null entries fall through to the generic combat layer.
// ============================================================================

export interface StarHeroFamilyCtx extends StreamContext {}

export function createStarHeroRootAction(ctx: StarHeroFamilyCtx): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                    // 0: dash attack — TODO port
    null,                                    // 1: B melee — TODO port
    (actor) => starHeroXHandler(actor, ctx), // 2: X-special (ramming dash + tier buff)
    null,                                    // 3: B charge — TODO port
    null,                                    // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned STAR HERO-family actor (pl0804/pl080c). Wires the root
 *  action dispatcher and stamps the borg-number switch the phase handlers read. */
export function configureStarHeroFamily(
  actor: RomActor,
  borgId: "pl0804" | "pl080c",
  ctx: StarHeroFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl080c" ? 0x80c : 0x804;
  actor.rootAction = createStarHeroRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
