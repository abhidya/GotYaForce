// Shared-engine 4-phase CHARGE-RELEASE machine (action 3) — 1:1 port of `zz_0177a3c_`
// @0x80177a3c and its phase table `PTR_FUN_80352af8` @0x80352af8 =
// [0x80177a8c, 0x80177b88, 0x80177c48, 0x80177d08] (exactly 4 entries — bounded by the
// sibling machine's table PTR_FUN_80352b08; exhaustive dol scan).
//
// DISTINCT from the shared X-tap zz_00ff2bc_ (shared-x-special.ts): this machine is
// bound at ACTION INDEX 3 (the charge release), uses stream GROUP 2 (not 4), never
// touches the +0x6ea combo cursor, reads its 0.98 reposition scale from the config
// (not a pooled 0.95), runs an explicit 30.0-frame windup phase, and its recovery
// phase flies BACKWARD (heading + 0x8000). Exhaustive `bl 0x80177a3c` scan: exactly
// two callers — the two family wrappers below.
//
// Families served (verified dig wav-eng-80177a3c.json, 17/17 claims CONFIRMED ×2):
//   Family 1 — ctor 0x80126e00, roster pl0619. Wrapper FUN_8012750c → zz_0127544_
//     (r4 = cfg @0x803303c8) → engine. actionTable @0x80330380, slot [3].
//   Family 2 — ctor 0x8015b420, roster pl061f + pl0625. Wrapper FUN_8015bc50 →
//     zz_015bc88_ (r4 = cfg @0x80345c34) → engine. actionTable @0x80345be8, slot [3].
//
// REGISTRATION NOTE: this file wires the families' actionTable[3] ONLY. Their action 2
// is the morph engine (a separate ported module); the orchestrator composes both into
// one root action table.
//
// Config block layout (proven by the engine's only r4/r31-relative loads —
// lwz 0(r31) @0x80177b48, lfs 4(r31) @0x80177b24/bbc/c8c, lwz 8(r31) @0x80177cc8;
// exactly 12 bytes, confirmed by fam2's next data block starting at cfg+0xc):
//   u32 +0x00 = group-2 stream slot
//   f32 +0x04 = reposition scale (P0 blink AND P1/P2 per-tick motion decay)
//   ptr +0x08 = family on-hit callback (NULL-checked; fired once on the P2 +0x1cef
//               contact transition, BEFORE the 10.0 / −0.3 speed writes)

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

/** Engine constants — every value read from boot.dol (dig `machine-constants`,
 *  CONFIRMED byte-exact; all lfs operands r2-relative with r2=0x8043ea20). */
export const SHARED_CHARGE3 = {
  WINDUP_TIME: 30.0,   // FLOAT_8043ae00 (0x41f00000) → +0x560 windup timer seed
  STREAM_RATE: -1.0,   // FLOAT_8043ae04 (0xbf800000) → zz_004beb8_ playback rate
  // FLOAT_8043ae10 (0x00000000) = 0.0 — the zeroing/comparison constant; written inline.
  HIT_FORWARD_SPEED: 10.0, // FLOAT_8043ae14 (0x41200000) → +0x44 on the P2 hit transition
  HIT_DECEL: -0.30000001192092896, // FLOAT_8043ae18 (0xbe99999a) → +0x4c on the hit transition
  RECOVERY_GRAVITY: 1.0, // FLOAT_8043ae1c (0x3f800000) — P3 integrator gravity param
  /** Stream group — immediate `li r5,2` @0x80177b58 (NOT group 4 like the X-tap). */
  STREAM_GROUP: 2,
} as const;

/** Per-family config for the shared charge-3 machine (the ROM's r4 config block). */
export interface SharedCharge3Config {
  /** cfg u32[0]: group-2 stream slot (1 for both bound families). */
  slot: number;
  /** cfg f32[+4]: reposition/decay scale — P0 blink `motion=(pos−target)×scale;
   *  pos+=motion` AND the P1/P2 per-tick `motion ×= scale` glide decay. */
  repositionScale: number;
  /** cfg ptr[+8]: family on-hit callback, invoked exactly once on the P2 contact
   *  transition (`if (+0x1cef > 0) { +0x540++; if (cfg[+8]) (*cfg[+8])(actor); ... }`),
   *  BEFORE the 10.0/−0.3 speed writes. Engine ignores its return (verified). */
  onHit: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** PORT APPROXIMATION (labeled): P2 has no ROM timer — the +0x1cef hit flag is
   *  authored by the group-2 stream data (op 0x02), which isn't byte-loaded yet (same
   *  caveat class as shared-x-special's whiffFrames). After this frame budget P2
   *  advances to recovery WITHOUT the onHit callback or the speed push. TUNED. */
  whiffFrames?: number;
  /** PORT APPROXIMATION (labeled): P3's exit gate is the +0x1cee contact byte; this
   *  frame budget is the stream-end/landing fallback when no contact fires. TUNED. */
  recoveryFrames?: number;
  /** PORT APPROXIMATION (labeled): the ROM reloads +0x50 (gravityCoeff) on the P3
   *  +0x1d0f stream event from `*(animBankBlob(+0x4ac) + 0x6c)` — per-borg RUNTIME
   *  pl-file data (0x803c4d94 is BSS; needs a Dolphin read to pin). Until pinned, this
   *  TUNED coefficient is applied unconditionally each P3 tick (negative = falling,
   *  matching the gravityCoeff sign convention in death-borg.ts's −1.0 pop). */
  recoveryGravityCoeff?: number;
}

const DEFAULT_WHIFF_FRAMES = 60;
const DEFAULT_RECOVERY_FRAMES = 60;
const DEFAULT_RECOVERY_GRAVITY_COEFF = -1.0; // TUNED fallback (see recoveryGravityCoeff)

/** Host-mirrored scratch the bridge stamps onto the actor (same pattern as
 *  shared-x-special.ts / shared-melee-lunge.ts). chargeMeterA/B are the family-local
 *  charge shorts the stage-1 wrappers halve EVERY dispatch tick:
 *  fam1 +0x18e0/+0x18e2 (FUN_8012750c), fam2 +0x1922/+0x1926 (FUN_8015bc50). */
interface Charge3Scratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  chargeMeterA?: number;
  chargeMeterB?: number;
}

function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  return (actor as RomActor & Charge3Scratch).lockTarget ?? null;
}

// ============================================================================
// Phase 0 — FUN_80177a8c @0x80177a8c. Setup + blink-away + group-2 stream start.
// ============================================================================
function charge3Phase0(actor: RomActor, cfg: SharedCharge3Config, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ FIRST (@0x80177ab4)
  // Windup timer +0x560 = 30.0 (FLOAT_8043ae00). +0x560 is a machine-local timer
  // distinct from +0x558; +0x558 is verified ABSENT from this whole machine, so
  // handlerTimer (+0x558's port field) safely stands in for it.
  actor.handlerTimer = SHARED_CHARGE3.WINDUP_TIME;

  // If lock ptr +0xcc == 0: active yaw +0x5ac = heading +0x72. With a target,
  // zz_006d144_(actor, 0xc1) turns toward it — the bridge pre-computes lockYaw.
  const target = lockTargetPos(actor);
  if (!target) {
    actor.activeYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }
  // zz_006e1ac_(actor, 0xc1, 1) — per-part FX helper (LIKELY label; renderer-side, unported).

  // Zero motion scalars +0x50/+0x48/+0x4c/+0x44 (FLOAT_8043ae10 = 0.0) and turn rates
  // u16 +0x80/+0x7e/+0x7c = 0. NOTE the zeroed turn rates: with turning disabled,
  // zz_006d144_'s facing-complete return can only fire if already facing — the P1
  // transition is effectively timer-bound (see charge3Phase1).
  actor.gravityCoeff = 0;
  actor.yVel = 0;
  actor.hDecel = 0;
  actor.hSpeed = 0;

  // REPOSITION (blink AWAY): motion = pos − lockTargetPos(+0x5e8); motion ×= cfg
  // scale 0.98 (lfs f1,4(r31) @0x80177b24); pos += motion → ~1.98× target distance.
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // zz_00679d0_ ground snap (port stands in with the registered ground clamp; the
  // ROM helper's airborne ledge-guard pos revert is unported — labeled approximation).
  groundClamp(actor);

  // STREAM START zz_004beb8_(rate −1.0, actor, mask 0xf, GROUP 2, slot = cfg u32[0],
  // −1, −1) @0x80177b64. NO +0x6ea combo-cursor write anywhere in this machine
  // (verified absence) — actor.streamSlot is deliberately left untouched.
  startStream(actor, 0xf, SHARED_CHARGE3.STREAM_GROUP, cfg.slot, SHARED_CHARGE3.STREAM_RATE);
  // +0x80c = 0.0 @0x80177b6c — unsurfaced float; no-op in the port.
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_80177b88 @0x80177b88. Windup glide; advance on timer or facing.
// ============================================================================
function charge3Phase1(actor: RomActor, cfg: SharedCharge3Config, ctx: StreamContext): void {
  // ROM gates zz_004cd24_(actor, 0xf) on byte +0x1b03 != 0 (part-anim hold — the same
  // gate shared-melee-lunge.ts documents). +0x1b03 isn't surfaced by the VM; the port
  // ticks unconditionally (labeled approximation — the timer still bounds the phase).
  tickStream(actor, 0xf, ctx);

  // Reposition continuation: motion ×= cfg scale (lfs f1,4(r31) @0x80177bbc); pos += motion.
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundClamp(actor); // zz_00679d0_
  // zz_006e1ac_(actor, 0xc1, 1) — FX helper (renderer-side, unported).

  // Timer decrement: +0x560 −= +0x1dc8 (per-frame dt) @0x80177bf0-c04.
  actor.handlerTimer -= actor.dt;

  // TRANSITION @0x80177c00-c2c: timer <= 0.0 (fcmpo + cror folds lt into eq) OR
  // zz_006d144_(actor, 0xc1) != 0 (facing complete). Because phase 0 zeroed the turn
  // rates (+0x7c/+0x7e/+0x80), facing-complete cannot newly fire mid-windup — the
  // port models the transition as timer-only, preserving the 30-frame charge windup
  // (labeled approximation of the OR's facing arm).
  if (actor.handlerTimer <= 0) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    // Port-side whiff budget for phase 2 (+0x558/handlerTimer is free — ROM never
    // touches it in this machine). Labeled approximation, see cfg.whiffFrames.
    actor.handlerTimer = cfg.whiffFrames ?? DEFAULT_WHIFF_FRAMES;
  }
}

// ============================================================================
// Phase 2 — FUN_80177c48 @0x80177c48. Attack ride + hit check.
// ============================================================================
function charge3Phase2(actor: RomActor, cfg: SharedCharge3Config, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // unconditional zz_004cd24_(actor, 0xf)
  // zz_006d144_(actor, 0xc1) face + zz_006e1ac_(actor, 0xc1, 1) FX — with turn rates
  // still zeroed the face call is inert; the bridge pre-aims lockYaw (no-op here).

  // Reposition continuation: motion ×= cfg scale (lfs f1,4(r31) @0x80177c8c); pos += motion.
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
  groundClamp(actor); // zz_00679d0_

  // HIT TRANSITION on contact byte +0x1cef != 0 @0x80177cb0. +0x1cef is stream-op-
  // driven (op 0x02), so the ROM's hit timing is authored in the group-2 slot-1 stream
  // data (verify-pass extra finding). Ordering is load-bearing: phase++ first, THEN the
  // NULL-checked callback (lwz r12,8(r31) @0x80177cc8, bctrl r3=actor), THEN the push.
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = 3; // +0x540++
    cfg.onHit?.(actor, ctx);
    actor.hSpeed = SHARED_CHARGE3.HIT_FORWARD_SPEED; // +0x44 = 10.0 (FLOAT_8043ae14)
    actor.hDecel = SHARED_CHARGE3.HIT_DECEL;         // +0x4c = −0.3 (FLOAT_8043ae18)
    actor.handlerTimer = cfg.recoveryFrames ?? DEFAULT_RECOVERY_FRAMES; // port budget
    return;
  }

  // WHIFF fallback (port approximation, labeled — see cfg.whiffFrames): the ROM rides
  // this phase until the stream sets +0x1cef; without byte-loaded stream data, advance
  // to recovery after the budget WITHOUT the callback or the speed push.
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= 0) {
    actor.fbPhaseSlots[0] = 3;
    actor.handlerTimer = cfg.recoveryFrames ?? DEFAULT_RECOVERY_FRAMES;
  }
}

// ============================================================================
// Phase 3 — FUN_80177d08 @0x80177d08. Recovery flying BACKWARD (cfg unused in the ROM —
// the prologue saves only r31=actor).
// ============================================================================
function charge3Phase3(actor: RomActor, cfg: SharedCharge3Config, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)

  // +0x1d10 > 0 → zz_00b22f4_ afterimage trail (FX helper, renderer-side, unported).
  // +0x1d0f < 0 → clear it and RELOAD gravityCoeff +0x50 from *(animBank +0x4ac)+0x6c
  // (lwz r3,0x4ac; lfs f0,0x6c(r3) @0x80177d4c-d50) — runtime pl-file data. PORT
  // APPROXIMATION (labeled): neither stream-event byte is surfaced by the VM; the
  // TUNED coefficient applies unconditionally each recovery tick (see cfg doc).
  actor.gravityCoeff = cfg.recoveryGravityCoeff ?? DEFAULT_RECOVERY_GRAVITY_COEFF;

  // FUN_80067310(gravity 1.0 = FLOAT_8043ae1c, actor, yaw = (s16)(heading +0x72 +
  // 0x8000)) — heading rotated 180°: the actor flies BACKWARD during recovery
  // (disasm: lha 0x72; addis +1; addi −0x8000; extsh).
  integratePhysics(SHARED_CHARGE3.RECOVERY_GRAVITY, actor, (actor.heading + 0x8000) & 0xffff);

  // grounded = zz_00679d0_ return (r3 pass-through from zz_00677b0_, consumed by
  // cmpwi r3,0 @0x80177d94). groundClamp mirrors it onto the scratch flag.
  groundClamp(actor);
  const grounded = (actor as RomActor & Charge3Scratch).grounded === true;

  // EXIT on contact byte +0x1cee != 0 (with the labeled recoveryFrames budget as the
  // port's stream-end/landing fallback — see cfg.recoveryFrames).
  actor.handlerTimer -= actor.dt;
  if (actor.wallContact !== 0 || actor.handlerTimer <= 0) {
    // +0x73f = 0 — housekeeping flag (unsurfaced; no-op in the port).
    actor.controlWord &= ~0x3; // +0x5e0 &= 0xfffffffc (rlwinm 0,0,0x1d) — exit attack state
    actor.hDecel = 0; // +0x4c = 0.0
    actor.hSpeed = 0; // +0x44 = 0.0
    if (grounded) {
      // zz_006a474_ ground idle reset (upper cue 7 → full-body cue 0, the same
      // labeling shared-x-special.ts phase 2 uses).
      dispatchUpperBodyCue(actor, 7);
      dispatchFullBodyCue(actor, 0);
    } else {
      // zz_006a5a4_ air-fall exit — unported; the action bits are cleared so the
      // bridge's completion path runs the fall state (labeled approximation).
      dispatchUpperBodyCue(actor, 7);
    }
  }
  // NOTE: phase 3 never increments +0x540 and the ROM dispatch has NO bounds check on
  // the phase byte — exit is solely the +0x5e0 &= ~3 clear (verify-pass extra finding).
  // The port's switch keeps the byte pinned at 3 until the cue reset zeroes it.
}

/**
 * Build the shared charge-3 phase handler for one family config — the port of the
 * `zz_0127544_`/`zz_015bc88_` stage-2 wrapper + `zz_0177a3c_` dispatch. Wire the
 * result as actionTable[3] in the family's root action dispatcher (action 2 is the
 * separately-ported morph engine).
 */
export function createSharedCharge3(
  cfg: SharedCharge3Config,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // zz_0177a3c_ prologue: `if (+0x541 != 0) +0xcc = 0;` — target-invalidated flag
    // clears the lock pointer. The bridge owns target validity; not modeled here
    // (same treatment as shared-x-special.ts).
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: charge3Phase0(actor, cfg, ctx); break;
      case 1: charge3Phase1(actor, cfg, ctx); break;
      case 2: charge3Phase2(actor, cfg, ctx); break;
      case 3: charge3Phase3(actor, cfg, ctx); break;
      default: break;
    }
  };
}

/** Stage-1 wrapper behavior — FUN_8012750c @0x8012750c / FUN_8015bc50 @0x8015bc50:
 *  halve two family-local charge-meter shorts (lha/srawi 1/sth — ARITHMETIC shift),
 *  then delegate. CORRECTION APPLIED (verify-pass extra finding): the stage-1 wrapper
 *  IS the actionTable[3] entry and therefore runs EVERY dispatch frame of the move —
 *  the meters decay geometrically toward 0 across the whole 4-phase action, NOT a
 *  single halve at move start (the dig's "on entry" phrasing was ambiguous).
 *  fam1 offsets +0x18e0/+0x18e2; fam2 offsets +0x1922/+0x1926 — family-local fields,
 *  surfaced as scratch chargeMeterA/chargeMeterB until the charge system ports. */
function halveChargeMeters(actor: RomActor): void {
  const s = actor as RomActor & Charge3Scratch;
  if (typeof s.chargeMeterA === "number") s.chargeMeterA >>= 1;
  if (typeof s.chargeMeterB === "number") s.chargeMeterB >>= 1;
}

// ============================================================================
// Family 1 — ctor 0x80126e00 (pl0619). Config @0x803303c8 (DOL dump 00000001
// 3f7ae148 8012756c). On-hit callback FUN_8012756c.
// ============================================================================

/** Pool spawner zz_0182fcc_ @0x80182fcc — builds a kind-0x5c child (+0x10=0x5c,
 *  +0x13=subIdx, +0x11=variant; tick FUN_801830e4, render FUN_80183680). Shot-kind
 *  attribution: table 0x8035c1e0, kind 9; pl0619 = variant 1 (chunk_0033.c:4101/4102). */
export const FAMILY1_CHARGE3 = {
  SPAWNER_ADDR: 0x80182fcc, // zz_0182fcc_
  /** zz_0182fcc_ subIdx args for the live pl0619 arm: (2,1) then (3,1). */
  SUB_IDX_A: 2,
  SUB_IDX_B: 3,
  SHOT_VARIANT: 1, // child +0x11 for borg 0x619 (table 0x8035c1e0 kind 9)
  CONFIG_ADDR: 0x803303c8,
  CALLBACK_ADDR: 0x8012756c,
} as const;

/** Family 1 on-hit callback FUN_8012756c @0x8012756c (cfg+8): borg switch on +0x3e8.
 *  Live arm 0x619 (pl0619): zz_006dbe0_(actor,2,1,1) weapon-cell cost gate, then the
 *  paired spawn zz_0182fcc_(actor,2,1) + zz_0182fcc_(actor,3,1). The 0x605 arm
 *  (unconditional pair (0,0)+(1,0)) is STATICALLY DEAD for this binding (roster =
 *  pl0619 only; the config ptr is the callback's sole DOL reference) — excluded.
 *  PORT APPROXIMATION (labeled): the zz_006dbe0_ cost gate isn't surfaced as a hook;
 *  modeled as always-pass (ammo decrement owned by the host weapon-cell system).
 *  `type` passed to onFamilyProjectile is the spawner's subIdx arg; the shot variant
 *  (1) is implied by the borg per the kind-9 attribution. */
export function family1Charge3OnHit(actor: RomActor, ctx: StreamContext): void {
  ctx.onFamilyProjectile?.(actor, FAMILY1_CHARGE3.SPAWNER_ADDR, FAMILY1_CHARGE3.SUB_IDX_A);
  ctx.onFamilyProjectile?.(actor, FAMILY1_CHARGE3.SPAWNER_ADDR, FAMILY1_CHARGE3.SUB_IDX_B);
}

/** Family 1 config @0x803303c8 (DOL-read: [0x803303c8]=1, [0x803303cc]=0x3f7ae148,
 *  [0x803303d0]=0x8012756c; exactly 12 bytes — 0x803303d4 is padding). */
export const FAMILY1_CHARGE3_CONFIG: SharedCharge3Config = {
  slot: 1,                              // cfg u32[0]
  repositionScale: 0.9800000190734863,  // cfg f32[+4] (0x3f7ae148)
  onHit: family1Charge3OnHit,           // cfg ptr[+8] = FUN_8012756c
};

/** Action-3 handler for pl0619 — the port of stage-1 wrapper FUN_8012750c (per-tick
 *  charge-meter halving of +0x18e0/+0x18e2) + stage-2 zz_0127544_ (cfg bind) + engine.
 *  Wire as actionTable[3] of the family root dispatcher FUN_80127174 (table
 *  @0x80330380; slot [2] is the morph engine, ported separately). */
export function createFamily1Charge3Action(ctx: StreamContext): (actor: RomActor) => void {
  const engine = createSharedCharge3(FAMILY1_CHARGE3_CONFIG, ctx);
  return (actor: RomActor) => {
    halveChargeMeters(actor); // FUN_8012750c: +0x18e0 >>= 1; +0x18e2 >>= 1 (every frame)
    engine(actor);
  };
}

// ============================================================================
// Family 2 — ctor 0x8015b420 (pl061f + pl0625). Config @0x80345c34 (DOL dump
// 00000001 3f7ae148 8015bcb0). On-hit callback FUN_8015bcb0.
// ============================================================================

/** Pool spawner zz_0084600_ @0x80084600 — builds a kind-1 child (+0x10=1,
 *  +0x11=kindIdx; tick FUN_80084740, render FUN_80085154) whose initial velocity is
 *  the owner speed scaled by the 3-float row at DAT_802d9794 + kindIdx*0x50 (stride-
 *  0x50 rows of the 0x802d9758 table). Shot-kind attribution: table 0x802d9758,
 *  kind 8 for all variants (chunk_0040.c:4725-4741). */
export const FAMILY2_CHARGE3 = {
  SPAWNER_ADDR: 0x80084600, // zz_0084600_
  CONFIG_ADDR: 0x80345c34,
  CALLBACK_ADDR: 0x8015bcb0,
  /** zz_0084600_ kindIdx pairs by borg (+0x3e8). 0x611 and 0x622 arms are STATICALLY
   *  DEAD for this binding (roster = pl061f + pl0625 only) — kept for the borg switch's
   *  fidelity but unreachable through the registered borgs. */
  VARIANTS: {
    0x611: [0x09, 0x0a], // dead arm (unconditional pair)
    0x61f: [0x11, 0x12], // pl061f — zz_006dbe0_(2,1,1) cost-gated pair
    0x622: [0x13, 0x14], // dead arm (unconditional pair)
    0x625: [0x15, 0x16], // pl0625 — UNGATED pair
  } as Record<number, readonly [number, number]>,
} as const;

/** Family 2 on-hit callback FUN_8015bcb0 @0x8015bcb0 (cfg+8): 4-way borg switch on
 *  +0x3e8 → paired zz_0084600_ spawns (kindIdx table above). Only the 0x61f arm is
 *  cost-gated (zz_006dbe0_(actor,2,1,1)); PORT APPROXIMATION (labeled): the cost gate
 *  is modeled as always-pass, same as family 1. Returns void (the ROM engine ignores
 *  the callback return — verified). */
export function family2Charge3OnHit(actor: RomActor, ctx: StreamContext): void {
  const pair = FAMILY2_CHARGE3.VARIANTS[actor.borgNumber];
  if (!pair) return;
  ctx.onFamilyProjectile?.(actor, FAMILY2_CHARGE3.SPAWNER_ADDR, pair[0]);
  ctx.onFamilyProjectile?.(actor, FAMILY2_CHARGE3.SPAWNER_ADDR, pair[1]);
}

/** Family 2 config @0x80345c34 (DOL-read: [0x80345c34]=1, [0x80345c38]=0x3f7ae148,
 *  [0x80345c3c]=0x8015bcb0 — byte-identical to family 1 except the callback: the
 *  machine's ENTIRE per-family variation is the on-hit projectile callback). */
export const FAMILY2_CHARGE3_CONFIG: SharedCharge3Config = {
  slot: 1,                              // cfg u32[0]
  repositionScale: 0.9800000190734863,  // cfg f32[+4] (0x3f7ae148)
  onHit: family2Charge3OnHit,           // cfg ptr[+8] = FUN_8015bcb0
};

/** Action-3 handler for pl061f/pl0625 — the port of stage-1 wrapper FUN_8015bc50
 *  (per-tick halving of +0x1922/+0x1926) + stage-2 zz_015bc88_ (cfg bind) + engine.
 *  Wire as actionTable[3] of the family root dispatcher FUN_8015b7a0 (table
 *  @0x80345be8). NOTE (verify-pass extra finding): family 2's ROM table has NULLs at
 *  [4]/[5] and bespoke drivers at [6..8] — do NOT pad it with family 1's default stub. */
export function createFamily2Charge3Action(ctx: StreamContext): (actor: RomActor) => void {
  const engine = createSharedCharge3(FAMILY2_CHARGE3_CONFIG, ctx);
  return (actor: RomActor) => {
    halveChargeMeters(actor); // FUN_8015bc50: +0x1922 >>= 1; +0x1926 >>= 1 (every frame)
    engine(actor);
  };
}
