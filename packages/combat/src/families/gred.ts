import {getGRedAirShotState,stepGRedAirShot} from '../gredAirShot.js';
import {getGRedShotState,stepGRedShot} from '../gredShot.js';
import {getGBlackChargeState,stepGBlackCharge} from '../gblackCharge.js';
import {getGRedChargeState,stepGRedCharge} from '../gredCharge.js';
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
  vecScale,
  vecAdd,
} from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { createSharedMeleeGRed, GRED_ACTION1_VARIANT0_CONFIG, GRED_MELEE_CONFIG } from "./shared-melee-gred.js";
import { createSharedCharge, GRED_CHARGE_CONFIG } from "./shared-charge.js";
import { createGRedDash } from "./gred-dash.js";
import { getNeoGredMeleeState, stepNeoGredMelee } from "../neoGredMelee.js";
import { getGRedCrashState, stepGRedCrash } from "../gredCrash.js";
import {getGRedAirMeleeState,stepGRedAirMelee} from '../gredAirMelee.js';

// Original numeric constants rechecked in-place. These motion corrections do
// not claim full X stream/aim/ground/timeout parity with the source.
const G_RED_CRASH = {
  LAUNCH_Y: 4.0,         // FLOAT_8043b158 — phase-0 vertical impulse (the "fly up")
  BASE_XZ: 0.0,          // FLOAT_8043b110 — base horizontal velocity during launch
  RELPOS_SCALE: Math.fround(.95), // FLOAT_8043b124 — retained own-motion fraction
  GRAVITY: 1.0,          // FLOAT_8043b130 — per-frame gravity during the move
  HIT_DASH_XZ: 60.0,     // FLOAT_8043b148 — phase-1→2 hit-transition horizontal dash
  HIT_DASH_Y: 10.0,      // FLOAT_8043b15c — phase-1→2 hit-transition vertical velocity
  LAND_TIMER: 120.0,     // FLOAT_8043b160 — phase-2 landing timer seed
  ANGLE_DECAY: Math.fround(.9), // FLOAT_8043b100 — phase-3 signed-angle decay
  BAM_RADIANS: 0.0000958738019107841, // FLOAT_80437078 — source45204/45238
  STREAM_RATE: -1.0,     // FLOAT_8043b120 — action-stream playback rate
} as const;

// Phase indices for the X-special handler (actor.fbPhaseSlots[0]).
const PHASE_LAUNCH = 0;
// PHASE_AIR_DASH = 1 (the value the launch advances TO; not referenced directly since
// the phase index is implicit in fbPhaseSlots[0] after the increment).
const PHASE_DESCEND = 2;
const PHASE_LAND = 3;

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

  // Source+5e8 is the actor's OWN saved position, not the locked enemy.
  // Bridge.beginFrame binds it from the previous savedGroundPos. Carry inertia
  // unconditionally, including a missing target; stationary actors do not teleport.
  for (const axis of ['x','y','z'] as const) {
    const delta = Math.fround(actor.pos[axis] - actor.targetCache5e8[axis]);
    actor.motion[axis] = Math.fround(delta * G_RED_CRASH.RELPOS_SCALE);
    actor.pos[axis] = Math.fround(actor.pos[axis] + actor.motion[axis]);
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
  // Source+38 is motion.x, +3c is its increment and +40 its cap. The
  // original fmadds rounds once after multiply+add; do not double motion.y.
  actor.motion.x = Math.fround(actor.motion.y * actor.dt + actor.motion.x);
  if (actor.motion.z < actor.motion.x) actor.motion.x = actor.motion.z;

  // 45238=COS and45204=SIN consume signed BAM16, not radians. Match the
  // original f32 argument/result boundaries; JS libm remains a numeric adapter.
  const pitch = (actor.steerYaw << 16) >> 16;
  const angle = Math.fround(pitch * G_RED_CRASH.BAM_RADIANS);
  actor.hSpeed = Math.fround(actor.motion.x * Math.fround(Math.cos(angle)));
  actor.yVel = Math.fround(-actor.motion.x * Math.fround(Math.sin(angle)));

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
  // DOUBLE8043b108 is the s16-to-double conversion bias, NOT a176 offset.
  // Source fmuls -> fctiwz -> sth: f32 damping, truncate toward0, signed16 store.
  const signedPitch = (actor.steerYaw << 16) >> 16;
  actor.steerYaw = (Math.trunc(Math.fround(signedPitch * G_RED_CRASH.ANGLE_DECAY)) << 16) >> 16;
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
  const neutralGRedMelee = createSharedMeleeGRed(GRED_ACTION1_VARIANT0_CONFIG, ctx);
  const legacyCharge=createSharedCharge(GRED_CHARGE_CONFIG,ctx);
  const legacyMelee = createSharedMeleeGRed(GRED_MELEE_CONFIG, ctx);
  // The full ROM table has 5 entries indexed by +0x580; entry 2 is the X/air-B chain
  // (FUN_8018e7fc → variant table → phase table). Here we route actionIndex 2 directly
  // to the phase handler; the variant-dispatch and air-counter clear (FUN_8018e7fc /
  // FUN_8018e838) are folded in.
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    (actor)=>{if(getGRedAirShotState(actor)&&(actor.variantIndex===3||actor.variantIndex===4))stepGRedAirShot(actor,ctx);else if(getGRedShotState(actor)&&actor.variantIndex===0)stepGRedShot(actor,ctx);else dash(actor);}, // 0: admitted normal ground/air shots; other routes remain legacy.
    (actor) => {
      if((actor.borgNumber===0x615||actor.borgNumber===0x62a||actor.borgNumber===0x629) && actor.variantIndex===4 && getGRedAirMeleeState(actor)){
        stepGRedAirMelee(actor,ctx);return;
      }
      if (getNeoGredMeleeState(actor) &&
          (((actor.borgNumber === 0x615 || actor.borgNumber === 0x62a) && actor.variantIndex === 0) ||
           (actor.borgNumber === 0x629 && (actor.variantIndex === 0 || actor.variantIndex === 6)))) {
        stepNeoGredMelee(actor,ctx); return;
      }
      // Unadmitted direct callers retain the prior bounded pl0615 v0 config;
      // other variants retain their legacy placeholder. Actual fresh neutral B
      // admission above owns the source clocks, contact and retap chain.
      (actor.borgNumber === 0x615 && actor.variantIndex === 0 ? neutralGRedMelee : legacyMelee)(actor);
    }, // 1: B melee
    (actor) => {
      if((actor.borgNumber===0x615 || actor.borgNumber===0x629 || actor.borgNumber===0x62a) &&
          (actor.variantIndex===0 || actor.variantIndex===4) && getGRedCrashState(actor))
        stepGRedCrash(actor,ctx);
      else gredXHandler(actor,ctx);
    }, // 2: admitted family neutral ground/air X; other routes retain legacy behavior.
    (actor)=>{if(getGBlackChargeState(actor))stepGBlackCharge(actor,ctx);else if(getGRedChargeState(actor))stepGRedCharge(actor,ctx);else legacyCharge(actor);}, // 3: scoped RED/NEO charge; legacy neighbors unchanged.
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
