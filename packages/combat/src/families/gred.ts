// G RED family (ctor 0x8018ccfc) — the REFERENCE port of a ROM-faithful borg family.
// Covers pl0615 (G RED), pl0629 (NEO G RED), pl062a (G BLACK). Source:
// `research/decomp/ghidra-export/chunk_0046.c:5058` (root dispatcher zz_018d24c_) and
// `chunk_0047.c:752-970` (X-special / air-B handler chain FUN_8018e7fc → FUN_8018e838
// → FUN_8018e888/ea54/eb2c/ec34).
//
// This is the worked example for PORTING.md's per-family template. Every motion
// constant is DERIVED from boot.dol (see action-vm-and-gcrash-decode-2026-07-05.md §B).

import type { RomActor } from "../rom/actor.js";
import {
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "../rom/dispatch.js";
import {
  integratePhysics,
  vecSubtract,
  vecScale,
  vecAdd,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { createSharedMeleeGRed, GRED_MELEE_CONFIG } from "./shared-melee-gred.js";
import { createSharedCharge, GRED_CHARGE_CONFIG } from "./shared-charge.js";
import { createGRedDash } from "./gred-dash.js";

// Motion constants — every value read from boot.dol this session.
const G_RED_CRASH = {
  LAUNCH_Y: 4.0,         // FLOAT_8043b158 — phase-0 vertical impulse (the "fly up")
  BASE_XZ: 0.0,          // FLOAT_8043b110 — base horizontal velocity during launch
  RELPOS_SCALE: 0.95,    // FLOAT_8043b124 — reposition scale (push 5% from target)
  GRAVITY: 1.0,          // FLOAT_8043b130 — per-frame gravity during the move
  HIT_DASH_XZ: 60.0,     // FLOAT_8043b148 — phase-1→2 hit-transition horizontal dash
  HIT_DASH_Y: 10.0,      // FLOAT_8043b15c — phase-1→2 hit-transition vertical velocity
  LAND_TIMER: 120.0,     // FLOAT_8043b160 — phase-2 landing timer seed
  ANGLE_DECAY: 0.9,      // FLOAT_8043b100 — phase-3 steering-angle decay
  ANGLE_BASE: 176.0,     // DOUBLE_8043b108 — phase-3 steering-angle base offset
  STREAM_RATE: -1.0,     // FLOAT_8043b120 — action-stream playback rate
} as const;

// Phase indices for the X-special handler (actor.fbPhaseSlots[0]).
const PHASE_LAUNCH = 0;
// PHASE_AIR_DASH = 1 (the value the launch advances TO; not referenced directly since
// the phase index is implicit in fbPhaseSlots[0] after the increment).
const PHASE_DESCEND = 2;
const PHASE_LAND = 3;

/** The lock-target position the family handler reads at actor+0x5e8. The bridge adapter
 *  copies BorgRuntime's currently-locked enemy position into this field each frame. */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

// ============================================================================
// Phase 0 — FUN_8018e888 @ chunk_0047.c:779. The launch.
// ============================================================================
function gredXPhase0(actor: RomActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = PHASE_LAUNCH + 1; // enter (the ROM increments +0x540 first)

  // borg-number switch (chunk_0047.c:808-835). pl0615 = 0x615 (G RED, the "else" branch).
  const isNeoGRed = actor.borgNumber === 0x629;
  const isGBlack = actor.borgNumber === 0x62a;
  if (isNeoGRed || isGBlack) {
    actor.streamSlot = isNeoGRed ? 1 : 4;
    actor.hSpeed = G_RED_CRASH.BASE_XZ;
    actor.yVel = G_RED_CRASH.BASE_XZ;
    actor.hDecel = G_RED_CRASH.BASE_XZ;
    actor.gravityCoeff = G_RED_CRASH.BASE_XZ;
  } else {
    // G RED branch (chunk_0047.c:818-825).
    actor.streamSlot = 0;
    actor.hSpeed = G_RED_CRASH.BASE_XZ;          // 0
    actor.hDecel = G_RED_CRASH.BASE_XZ;          // 0
    actor.yVel = G_RED_CRASH.LAUNCH_Y;           // 4.0 — the "fly up"
    actor.gravityCoeff = G_RED_CRASH.BASE_XZ;    // 0 (no gravity during launch)
  }

  // Yaw selection (chunk_0047.c:797-803): lock-yaw = current heading, unless the
  // control-word's lock-override bits are set.
  if ((actor.controlWord & 0xa0) === 0) {
    actor.activeYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }

  // Reposition: motion = (pos - lockTarget); motion *= 0.95; pos += motion.
  // (chunk_0047.c:836-839). Pushes G RED to 95% of the vector from target → the
  // "leaps away then dashes in" windup spacing.
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(G_RED_CRASH.RELPOS_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // Start the action stream — group 4 (charge/air-special axis), slot = streamSlot.
  // The ROM call is zz_004beb8_(STREAM_RATE, actor, 0xf /*part mask*/, 4 /*group*/,
  // streamSlot, -1, -1). This arms the kind-15 hitbox + plays g4 s0.
  startStream(actor, 0xf, 4, actor.streamSlot, G_RED_CRASH.STREAM_RATE);
  void ctx;
}

// ============================================================================
// Phase 1 — FUN_8018ea54 @ chunk_0047.c:852. Airborne physics + hit check.
// ============================================================================
function gredXPhase1(actor: RomActor, ctx: StreamContext): void {
  // Advance the stream one tick (chunk_0047.c:862: zz_004cd24_(actor, 0xf)).
  tickStream(actor, 0xf, ctx);
  // Enable gravity after the initial launch impulse so G Red arcs back down.
  // The ROM sets gravityCoeff=0 in phase 0 (pure launch), then phase 1's
  // FUN_80067310(1.0) re-engages it via the gravity param. Since our integrator
  // multiplies gravityCoeff × gravity, set gravityCoeff=1 here to match.
  if (actor.gravityCoeff === 0) actor.gravityCoeff = G_RED_CRASH.GRAVITY;
  // Physics integration (FUN_80067310(GRAVITY, actor, lockYaw)).
  integratePhysics(G_RED_CRASH.GRAVITY, actor, actor.activeYaw);
  // Reposition continuation: motion = motion × 0.95; pos += motion (chunk_0047.c:868-869).
  vecScale(G_RED_CRASH.RELPOS_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // Hit-transition (chunk_0047.c:873-879): if part-0 contact flag went positive, the
  // kind-15 hitbox connected with a target. Dash forward.
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = PHASE_DESCEND; // → phase 2 (the +0x540++ in the source)
    actor.motion.x = G_RED_CRASH.BASE_XZ;     // 0
    actor.motion.y = G_RED_CRASH.HIT_DASH_Y;  // 10.0
    actor.motion.z = G_RED_CRASH.HIT_DASH_XZ; // 60.0
  } else {
    // WHIFF RECOVERY: the ROM's stream VM advances +0x540 when the stream completes
    // (zz_004cd24_ end-of-script path). Since our stream banks aren't loaded yet,
    // approximate with a frame counter: g04_s00 is 81 frames; after that, transition
    // to the descend/recovery phase so G Red comes back down instead of rising forever.
    actor.handlerTimer += actor.dt;
    if (actor.handlerTimer >= 81) {
      actor.fbPhaseSlots[0] = PHASE_LAND;
      actor.handlerTimer = G_RED_CRASH.LAND_TIMER;
      // Apply downward velocity to start the descent.
      actor.yVel = Math.min(actor.yVel, -2.0);
    }
  }
}

// ============================================================================
// Phase 2 — FUN_8018eb2c @ chunk_0047.c:887. Angle-steered descent.
// ============================================================================
function gredXPhase2(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // Vertical accumulator: motion.y += motion.y × dt; clamp to motion.z.
  // (chunk_0047.c:902-906 — the +0x38 = +0x3c × +0x1dc8 + +0x38, clamp +0x40.)
  actor.motion.y = actor.motion.y * actor.dt + actor.motion.y;
  if (actor.motion.z < actor.motion.y) actor.motion.y = actor.motion.z;

  // XZ velocity from sin/cos of steerYaw (chunk_0047.c:907-911).
  // +0x44 (hSpeed) = motion.y × sin(steerYaw); +0x48 (yVel) = motion.y × -cos(steerYaw).
  // NOTE: the source writes +0x44/+0x48 here, which the next integratePhysics consumes.
  const yaw = actor.steerYaw;
  actor.hSpeed = actor.motion.y * Math.sin(yaw);
  actor.yVel = actor.motion.y * -Math.cos(yaw);

  integratePhysics(G_RED_CRASH.GRAVITY, actor, actor.activeYaw);

  // Hit-end transition (chunk_0047.c:915-919): if contactP0 went negative, advance.
  if (actor.contactP0 < 0) {
    actor.fbPhaseSlots[0] = PHASE_LAND; // → phase 3
    actor.handlerTimer = G_RED_CRASH.LAND_TIMER; // 120.0
    // +0x50 = descriptor.+0x6c (chunk_0047.c:918) — copy the family-handler data byte.
    if (actor.descriptor) actor.gravityCoeff = actor.descriptor.handlerData6c;
  }
}

// ============================================================================
// Phase 3 — FUN_8018ec34 @ chunk_0047.c:927. Land + return to idle.
// ============================================================================
function gredXPhase3(actor: RomActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  // Steer yaw tick: steerYaw = (steerYaw - 176.0) × 0.9
  // (chunk_0047.c:937-940 — the (s16 - DOUBLE_8043b108) × FLOAT_8043b100 write.)
  actor.steerYaw = (actor.steerYaw - G_RED_CRASH.ANGLE_BASE) * G_RED_CRASH.ANGLE_DECAY;
  integratePhysics(G_RED_CRASH.GRAVITY, actor, actor.activeYaw);

  // Ground check (chunk_0047.c:942-966). zz_00677b0_ returns 0 when grounded.
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded === true;
  if (grounded) {
    if (actor.borgNumber === 0x615) {
      // G RED waits for the wall-contact flag (chunk_0047.c:944-948).
      if (actor.wallContact === 0) return;
    } else {
      // Non-G-RED: count handlerTimer down by dt; bail if still > 0.
      actor.handlerTimer -= actor.dt;
      if (actor.handlerTimer > 0) return;
    }
    // Clear X-special flags and return to idle (chunk_0047.c:957-960).
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchUpperBodyCue(actor, 7); // → idle upper body (cue 7)
    dispatchFullBodyCue(actor, 0);  // → idle full body (cue 0)
  } else {
    // Still airborne — same flag clear but transition to fall state.
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchUpperBodyCue(actor, 7);
  }
}

/** The X-special / air-B phase table. Indexed by actor.fbPhaseSlots[0]. */
const X_PHASE_TABLE = [gredXPhase0, gredXPhase1, gredXPhase2, gredXPhase3];

/** FUN_8018e838 @ chunk_0047.c:765 — the variant-0 wrapper that clears the air-counter
 *  on phase 1 entry then dispatches the phase table. */
function gredXHandler(actor: RomActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of zz_018d24c_ @ chunk_0046.c:5060.
// ============================================================================
/** Action-index table (PTR_zz_018d288__80365588, 5 entries). Only actionIndex 2
 *  (X / air-B) is ported here; the other actions (0=dash, 1=B-melee, 3=B-charge,
 *  4=...) wire in as their handlers port. Null entries fall back to the existing
 *  generic @gf/combat logic. */
export interface GRedFamilyCtx extends StreamContext {}

export function createGRedRootAction(ctx: GRedFamilyCtx): (actor: RomActor) => void {
  const dash = createGRedDash(ctx);
  // The full ROM table has 5 entries indexed by +0x580; entry 2 is the X/air-B chain
  // (FUN_8018e7fc → variant table → phase table). Here we route actionIndex 2 directly
  // to the phase handler; the variant-dispatch and air-counter clear (FUN_8018e7fc /
  // FUN_8018e838) are folded in.
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    dash,          // 0: dash attack (zz_018d288_, all five variants)
    createSharedMeleeGRed(GRED_MELEE_CONFIG, ctx), // 1: B melee (zz_0177dd8_ shared engine)
    (actor) => gredXHandler(actor, ctx), // 2: X / air-B (G Crash)
    createSharedCharge(GRED_CHARGE_CONFIG, ctx), // 3: B charge (zz_0179814_ shared engine)
    null,          // 4: (FUN_8018ee84) — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
    // Null actionIndex → no ROM handler yet; the bridge falls through to the existing
    // generic @gf/combat stepAttacks path for that button.
  };
}

/** Configure a freshly-spawned G RED-family actor (pl0615/pl0629/pl062a). Wires the
 *  family virtuals and stamps the borg-number switch the phase handlers read. */
export function configureGRedFamily(
  actor: RomActor,
  borgId: "pl0615" | "pl0629" | "pl062a",
  ctx: GRedFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl0615" ? 0x615 : borgId === "pl0629" ? 0x629 : 0x62a;
  actor.rootAction = createGRedRootAction(ctx);
  actor.hasBCharge = true; // actionTable[3] = createSharedCharge (zz_0179814_)
  // cueTable, commandTable, descriptor, familyStreamBank are set by the spawn layer
  // from the per-family extracted data (cue-script-stream-decode §1 + commandMoveTables).
  // Defaults that match G RED's power-on state:
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
