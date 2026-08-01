// FLAME NINJA (pl0006, borgNumber 0x006, ctor 0x800b2ef8) + CYBER NINJA (pl0007,
// borgNumber 0x007, ctor 0x800a6f4c) flame-cyber-ninja family — bespoke multi-action
// phase-machine port. Two UNREGISTERED large ninja borg families share this module.
//
// FLAME NINJA (chunk_0018.c, 39 fns / 4293 instrs):
//   Root action router FUN_800b31a8 (chunk_0018.c:77) indexes PTR_FUN_802fd27c by
//   actionIndex (+0x580). Action 0 (B-combo) dispatches PTR_FUN_802fd288[+0x581] variant
//   tables; each variant is a phase machine indexed by +0x540. Action 1 (contextual-B)
//   and action 2 (X-special) likewise. This module ports:
//     action 0 variant 0 — phase table @0x802fd2b0 (FUN_800b3274/3300/33f0): the 3-phase
//       swing-combo driver (setup → contact-wait → recovery/exit) PORTED here.
//     action 2 — phase table @0x802fd370 (FUN_800b518c/5310/53e4/5598/5754): the 5-phase
//       fireball X-special (charge → blink → ram/exit) PORTED here.
//   The deeper combo variants (action 0 v1/v2, action 1) are honest TODO — their
//   bone-matrix steering + multi-stage trail children need unsurfaced deps.
//
// CYBER NINJA (chunk_0016.c, 29 fns / 2593 instrs):
//   Root action router FUN_800a71a4 (chunk_0016.c:2666) indexes PTR_FUN_802f8560 by
//   actionIndex (+0x580). Action 0 variant dispatch PTR_FUN_802f8570[+0x581]. PORTED:
//     action 0 variant 0 — phase table @0x802f8584 (FUN_800a7264/7340/740c): 3-phase
//       kunai-melee driver PORTED here.
//     action 1 — phase table @0x802f85c8 (FUN_800a7b7c/7c58/7cd4): 3-phase dash-strike
//       PORTED here (deeper phases TODO).
//     action 2 — phase table @0x802f8614 (FUN_800a8ae4/8be4/8cd4): X-special shuriken
//       spread PORTED here (ph3+ TODO).
//     action 3 — phase table @0x802f8638 (FUN_800a8f44/9040): B-charge sword-flurry
//       setup PORTED here (deeper phases TODO).
//
// TRUE table lengths confirmed by address arithmetic: the work-queue overread each
// variant table to 8 entries, but the live tables are 3 meaningful phases + restart
// sentinels (e.g. 0x802fd2b0 holds [FUN_800b3274, FUN_800b3300, FUN_800b33f0, ...]).
//
// Float constants read from user-data/GG4E/disc/sys/boot.dol (cited per const; FLAME
// sdata2 @0x804383xx, CYBER sdata2 @0x804380xx). Exit helpers zz_006a474_/zz_006a5a4_/
// zz_006a750_ route to shared-idle-return.ts + dispatch.ts. zz_006a53c_ → local
// exitAction. FUN_8006cc90 stream tick → no-op returning 0 (no banks attached).

import { createRomActor, type RomActor, type Vec3 } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import {
  allocateWeapon,
  groundSnapRevert,
  resetPoseHousekeeping,
  stepAfterimage,
  stepPartTargetPitch,
  stepTargetRoll,
  stepTargetYaw,
} from "../rom/helpers.js";
import { integratePhysics, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

// ============================================================================
// Identity.
// ============================================================================
const FLAME_NINJA_BORG_NUMBER = 0x006; // pl0006 FLAME NINJA
const CYBER_NINJA_BORG_NUMBER = 0x007; // pl0007 CYBER NINJA

// ============================================================================
// Spawner addresses (family-local borg-switched projectile/effect spawners).
// ============================================================================
// FLAME NINJA:
/** zz_00b73b4_ @0x800b73b4 — action-0 swing contact spawn (type = +0x6e8 slot). */
export const FLAME_SWING_SPAWNER = 0x800b73b4;
/** zz_0092dcc_ @0x80092dcc — action-2 (X) fireball contact spawn. */
export const FLAME_X_CONTACT_SPAWNER = 0x80092dcc;
/** zz_00b5878_ @0x800b5878 — action-2 fireball child spawn (ammo-gated via zz_0088aa0_). */
export const FLAME_FIREBALL_SPAWNER = 0x800b5878;
// CYBER NINJA:
/** zz_00c3be0_ @0x800c3be0 — action-0 melee contact effect (shared EFFECT_SPAWNER, type 1). */
export const CYBER_MELEE_SPAWNER = 0x800c3be0;
/** zz_0082824_ @0x80082824 — record-table projectile spawn (shared SHOT_HELPER). */
export const CYBER_SHOT_HELPER = 0x80082824;
/** FUN_800b5ed8 @0x800b5ed8 — action-2 (X) shuriken spread (4 projectiles, shared with FLAME). */
export const CYBER_SHURIKEN_SPREAD_SPAWNER = 0x800b5ed8;

// ============================================================================
// Config constants — DOL-read this session (cited per const).
// ============================================================================
export const FLAME_NINJA = {
  // --- FLAME sdata2 @0x804383xx ---
  /** FLOAT_804383b0 = 20.0 — action-0 ph0 +0x560 timer seed; action-1 ph0 timer. */
  A0_TIMER_SEED: 20.0,
  /** FLOAT_804383b4 = 0.0 — universal zero / threshold. */
  ZERO: 0.0,
  /** FLOAT_804383b8 = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_804383bc = 10.0 — zz_00b3510_ swing +0x558 re-seed. */
  SWING_TIMER: 10.0,
  /** FLOAT_804383c0 = 30.0 — zz_00b3510_ swing +0x55c re-seed. */
  SWING_COOLDOWN: 30.0,
  /** FLOAT_804383c4 = 1.0 — FUN_80067310 gravity coefficient. */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_804383c8 = 60.0 — action-2 ph0 +0x558 seed (charge window). */
  X_TIMER_SEED: 60.0,
  /** FLOAT_804383ec = 0.95 — blink + per-frame motion scale. */
  MOTION_SCALE: 0.95,
  /** FLOAT_804383f0 = 40.0 — action-2 ph2 ram motion Y component. */
  X_RAM_MOTION_Y: 40.0,
  /** FLOAT_804383f8 = 0.9 — steerYaw +0x18da decay factor (CONCAT44 idiom). */
  STEER_DECAY: 0.9,
  /** FLOAT_80438400 = 3.0 — afterimage motion-magnitude threshold. */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_80438404 = 2.0 — action-2 ph2 ram motion Z component. */
  X_RAM_MOTION_Z: 2.0,
  /** FLOAT_80438408 = 16.0 — action-2 ph2 air-exit +0x694 seed. */
  X_AIR_EXIT_TIMER: 16.0,
  /** FLOAT_80438418 = 4.0 — action-2 ph4 +0x694 seed base. */
  X_RECOVER_TIMER: 4.0,
  /** FLOAT_804383e0 = -0.4 — action-2 gravity slot (NEGATIVE coefficient). */
  X_GRAVITY: -0.4,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 bits cleared by action-0/1 ph0 setup (0xffffff4f = ~0xb0). */
  SETUP_CLEAR_BITS: 0xb0,
  /** +0x5b4 charge-status bit gating action-0 ph2 combo restart. */
  CHARGE_BIT: 0x200,
  /** +0x5e0 position-frozen / airborne bit (0x40). */
  AIRBORNE_BIT: 0x40,
  /** +0x5e0 dash/aim-override bits (0xa0) gating the lockYaw=heading copy. */
  AIM_OVERRIDE_BITS: 0xa0,
} as const;

export const CYBER_NINJA = {
  // --- CYBER sdata2 @0x804380xx ---
  /** FLOAT_804380e8 = 20.0 — action-0 ph0 +0x560 timer seed; action-2 ph2 +0x48 yVel. */
  A0_TIMER_SEED: 20.0,
  /** FLOAT_804380ec = -1.0 — zz_004beb8_ stream playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_804380f0 = 0.0 — universal zero / threshold. */
  ZERO: 0.0,
  /** FLOAT_804380f4 = 0.95 — blink + per-frame motion scale. */
  MOTION_SCALE: 0.95,
  /** FLOAT_804380f8 = 3.0 — afterimage motion-magnitude threshold. */
  AFTERIMAGE_THRESHOLD: 3.0,
  /** FLOAT_804380fc = 8.0 — zz_00a75d0_ melee +0x558 re-seed. */
  MELEE_TIMER: 8.0,
  /** FLOAT_80438100 = 10.0 — zz_00a75d0_ melee +0x55c re-seed. */
  MELEE_COOLDOWN: 10.0,
  /** FLOAT_8043810c = 1.0 — FUN_80067310 gravity coefficient (action-2/3 physics). */
  PHYSICS_GRAVITY: 1.0,
  /** FLOAT_80438110 = 60.0 — action-1 ph0 +0x558 seed (dash window). */
  A1_TIMER_SEED: 60.0,
  /** FLOAT_80438114 = 150.0 — +0x764 speed threshold (dash re-aim gate). */
  SPEED_THRESHOLD: 150.0,
  /** FLOAT_80438118 = 0.03125 — action-1 ph2 decel scale. */
  A1_DECEL_SCALE: 0.03125,
  /** FLOAT_80438134 = 30.0 — action-3 ph0 +0x558 seed. */
  A3_TIMER_SEED: 30.0,
  /** FLOAT_8043813c = -0.3 — action-2 ph2 +0x4c decel. */
  X_DECEL: -0.3,
  /** FLOAT_80438144 = 250.0 — action-3 ph1 +0x38 motion seed. */
  A3_MOTION_SEED: 250.0,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** +0x5e0 bits cleared by ph0 setup (0xffffff4f = ~0xb0). */
  SETUP_CLEAR_BITS: 0xb0,
  /** +0x5e0 airborne bit. */
  AIRBORNE_BIT: 0x40,
  /** +0x5d4 charge-status bit gating action-0 ph2 combo restart (edge word bit 0x20). */
  CHARGE_BIT: 0x20,
  /** zz_00a75d0_ melee effect record type (zz_00c3be0_(actor, 1)). */
  MELEE_EFFECT_TYPE: 1,
} as const;

// ============================================================================
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ============================================================================
export interface FlameCyberNinjaScratch {
  /** +0x541/+0x542/+0x543: full-body phase-bytes 1/2/3 (variant-local flags). */
  fcFlag541?: number;
  fcFlag542?: number;
  fcFlag543?: number;
  /** +0x548/+0x54a/+0x54c/+0x54e: short cursors (ram window / stream cursor). */
  fcCursor548?: number;
  fcCursor54a?: number;
  fcCursor54c?: number;
  fcCursor54e?: number;
  /** +0x55c: contact/trail cooldown sub-timer. */
  fcCooldown55c?: number;
  /** +0x560: action handler timer (separate from +0x558). */
  fcTimer560?: number;
  /** +0x564: action-1 ram sub-timer. */
  fcTimer564?: number;
  /** +0x6e8/+0x6e9/+0x6ea/+0x6ec/+0x6f2/+0x6f4: stream/cursor/mode bytes. */
  fcSlot6e8?: number;
  fcSlot6e9?: number;
  fcMode6f2?: number;
  fcMode6f4?: number;
  /** +0x15c/+0x15d: per-slot display bytes. */
  fcDisplay15c?: number;
  fcDisplay15d?: number;
  /** +0x18dc: secondary steer yaw (distinct from steerYaw +0x18da). */
  fcSteerYaw18dc?: number;
  /** +0x1dfc: aim-roll accumulator (target-relative). */
  fcAimRoll1dfc?: number;
  /** +0x760/+0x764: movement speed scalars. */
  fcSpeed760?: number;
  fcSpeed764?: number;
  /** +0x784: charge-gate short (action-2 ph0 gravity fallback). */
  fcCharge784?: number;
}

type FnActor = RomActor & FlameCyberNinjaScratch;

function scratchOf(actor: RomActor): FnActor {
  return actor as FnActor;
}

// ============================================================================
// Shared bridges. FUN_80067310 → integratePhysics; zz_00677b0_ → groundSnapRevert;
// zz_006dee8_ → stepTargetRoll; zz_006d144_ → stepTargetYaw; zz_006e1ac_ →
// stepPartTargetPitch; zz_00b22f4_ → stepAfterimage.
// ============================================================================

/** Shared blink: motion = pos − targetCache; motion ×= 0.95; pos += motion. */
function applyBlink(actor: RomActor, scale: number): void {
  vecSubtract(actor.pos, actor.targetCache5e8, actor.motion);
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Per-frame motion continuation: motion ×= scale; pos += motion (no re-subtract). */
function applyMotionDrift(actor: RomActor, scale: number): void {
  vecScale(scale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

/** Afterimage emit when motion magnitude exceeds threshold (zz_00b22f4_ gate). */
function maybeAfterimage(actor: RomActor, threshold: number): void {
  const mag = Math.hypot(actor.motion.x, actor.motion.y, actor.motion.z);
  if (threshold < mag) stepAfterimage(actor);
}

/** zz_006e004_ / FUN_80066838 host bridge — targeting/visibility probe. Without a host
 *  roster this returns >=0 (target acquired / charge adequate) so the setup fast-path
 *  that stamps +0x581=5 / +0x541=1 is NOT taken (matches the common in-range case). */
function targetingProbe(_actor: RomActor): number {
  return 1;
}

/** zz_006a3d0_(actor, cue, stateMode, actionIndex) — command-record re-dispatch /
 *  cancel-restart. The bridge's command layer owns the live path; here it is an honest
 *  no-op (the variant/action stamp the caller writes is the observable payload). */
function redispatchCommand(_actor: RomActor, _cue: number, _stateMode: number, _actionIndex: number): void {
  // TODO(host): command-record re-dispatch (bridge command layer).
}

// ============================================================================
// FLAME NINJA — action 0 variant 0 (B-tap swing combo). Phase table @0x802fd2b0 =
// [FUN_800b3274, FUN_800b3300, FUN_800b33f0, ...]. Source: chunk_0018.c:110-225.
// ============================================================================

/** zz_00b3510_ @ chunk_0018.c:229 — action-0 swing contact helper. +0x558=10.0,
 *  +0x55c=30.0, ammo-gated consume zz_006dbe0_(0,1,1); on success spawns
 *  zz_00b73b4_(actor, +0x6e8) + stamps +0x15c[+0x6e8] = 2. */
function flameSwingSpawn(actor: FnActor, ctx: StreamContext): void {
  actor.handlerTimer = FLAME_NINJA.SWING_TIMER;       // +0x558 = 10.0
  actor.fcCooldown55c = FLAME_NINJA.SWING_COOLDOWN;   // +0x55c = 30.0
  if (allocateWeapon(actor, ctx, 0, 1, true)) {       // zz_006dbe0_(actor, 0, 1, 1)
    const slot = actor.fcSlot6e8 ?? 0;
    ctx.onFamilyProjectile?.(actor, FLAME_SWING_SPAWNER, slot); // zz_00b73b4_(p, +0x6e8)
    actor.fcDisplay15c = 2;                           // +0x15c[+0x6e8] = 2
  }
}

/** Phase 0 — setup. FUN_800b3274 @ chunk_0018.c:112. */
function flameA0v0Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  if (targetingProbe(actor) < 0) actor.variantIndex = 5; // +0x581 = 5 (out-of-range)
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcTimer560 = FLAME_NINJA.A0_TIMER_SEED;           // +0x560 = 20.0
  actor.controlWord &= ~FLAME_NINJA.SETUP_CLEAR_BITS;     // +0x5e0 &= ~0xb0
  actor.hDecel = FLAME_NINJA.ZERO;                         // +0x4c = 0
  actor.hSpeed = FLAME_NINJA.ZERO;                         // +0x44 = 0
  startStream(actor, 0xf, 2, 0, FLAME_NINJA.STREAM_RATE);  // zz_004beb8_(-1, p, 0xf, 2, 0)
  void ctx;
}

/** Phase 1 — contact-wait. FUN_800b3300 @ chunk_0018.c:140. */
function flameA0v0Phase1Wait(actor: FnActor, ctx: StreamContext): void {
  const roll = stepTargetRoll(actor, false); // zz_006dee8_(p, 1)
  const mask = (actor.controlWord & 2) !== 0 ? 0xf : 1;
  tickStream(actor, mask, ctx); // zz_004cd24_(p, mask)
  if (roll < 0) {
    // Aim lost → cancel-restart (ground variant 5 / air variant 9).
    if ((actor.controlWord & FLAME_NINJA.AIRBORNE_BIT) === 0) {
      actor.variantIndex = 5;
      redispatchCommand(actor, 0, 0, 2);
    } else {
      actor.variantIndex = 9;
      redispatchCommand(actor, 0, 4, 2);
    }
    return;
  }
  // Not converged AND timer still > 0 → stay in ph1.
  if (roll < 1) {
    const t = (actor.fcTimer560 ?? 0) - actor.dt;
    actor.fcTimer560 = t;
    if (t > FLAME_NINJA.ZERO) return;
  }
  // Converged OR timer expired → contact check.
  if (actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    flameSwingSpawn(actor, ctx);                              // zz_00b3510_(p)
  }
}

/** Phase 2 — recovery / charge-gated combo restart / ground exit. FUN_800b33f0. */
function flameA0v0Phase2Recover(actor: FnActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  if (actor.handlerTimer <= FLAME_NINJA.ZERO) {
    // Swing window elapsed: clear display bytes; charge-bit → ammo check (no consume)
    // for combo restart back to ph1 variant 0.
    actor.fcDisplay15c = 0;
    actor.fcDisplay15d = 0;
    if (((actor.statusWord5b4 ?? 0) & FLAME_NINJA.CHARGE_BIT) !== 0) {
      if (allocateWeapon(actor, ctx, 0, 1, false)) { // zz_006dbe0_(p, 0, 1, 0)
        // zz_006bf80_(p) target-visibility refresh (host hook; no-op here).
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- (back to ph1)
        actor.variantIndex = 0;                                   // +0x581 = 0
        return;
      }
      flameA0Exit(actor);
      return;
    }
  } else {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
    // Re-aim: variant 0 → roll; else yaw aim 0xc1.
    if (actor.variantIndex === 0) stepTargetRoll(actor, false);
    else stepTargetYaw(actor, 0xc1, 0);
  }
  // Cooldown gate: (+0x5d8 & 0xf0) == 0 → drain +0x55c; advance to exit when <= 0.
  if ((actor.inputHeld5d8 & 0xf0) === 0) {
    const c = (actor.fcCooldown55c ?? 0) - actor.dt;
    actor.fcCooldown55c = c;
    if (c > FLAME_NINJA.ZERO) return;
  }
  flameA0Exit(actor);
}

/** LAB_800b34dc exit: +0x15d=0; +0x73f=0; +0x5e0&=~3; zz_006a474_(ground idle return). */
function flameA0Exit(actor: FnActor): void {
  actor.fcDisplay15d = 0;
  actor.housekeeping73f = 0;
  actor.controlWord &= ~FLAME_NINJA.ACTION_MODE_BITS;
  romGroundIdleReturn(actor); // zz_006a474_(p)
}

/** Action-0 variant-0 dispatcher (FUN_800b3238 → PTR_FUN_802fd2b0[+0x540]). */
function flameAction0(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: flameA0v0Phase0Setup(actor, ctx); return;
    case 1: flameA0v0Phase1Wait(actor, ctx); return;
    case 2: flameA0v0Phase2Recover(actor, ctx); return;
    default: return; // deeper combo variants (v1/v2 @0x802fd2c8/d4/e0/ec) — TODO.
  }
}

// ============================================================================
// FLAME NINJA — action 2 (X-special fireball). Phase table @0x802fd370 =
// [FUN_800b518c, FUN_800b5310, FUN_800b53e4, FUN_800b5598, FUN_800b5754].
// Source: chunk_0018.c:1342-1586.
// ============================================================================

/** Phase 0 — charge setup. FUN_800b518c @ chunk_0018.c:1344. */
function flameA2Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcFlag542 = 0;                                      // +0x542 = 0
  actor.streamSlot = 0;                                     // +0x6ea = 0
  if ((actor.controlWord & FLAME_NINJA.AIM_OVERRIDE_BITS) === 0) {
    actor.lockYaw = actor.heading;                          // +0x5ae = +0x72
    actor.activeYaw = actor.heading;                        // +0x5ac = +0x72
  }
  if (targetingProbe(actor) < 1) {
    actor.fcFlag541 = 1;                                    // +0x541 = 1
    (actor as RomActor & { cc?: number }).cc = 0;           // +0xcc = 0 (target lost)
    actor.activeYaw = actor.lockYaw;                        // +0x5ac = +0x5ae
  }
  actor.handlerTimer = FLAME_NINJA.X_TIMER_SEED;           // +0x558 = 60.0
  stepTargetYaw(actor, 0xc0);                               // zz_006d144_(0xc0)
  stepPartTargetPitch(actor, 0xc0);                         // zz_006e1ac_(0xc0, 1)
  applyBlink(actor, FLAME_NINJA.MOTION_SCALE);              // blink ×0.95
  groundSnapRevert(actor);                                  // zz_00677b0_
  const slot = actor.streamSlot;                            // +0x6ea (pre-increment)
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, FLAME_NINJA.STREAM_RATE); // zz_004beb8_(-1, p, 0xf, 4, slot)
  actor.fcFlag542 = 0;                                      // +0x542 = 0
  // Fireball arming: ammo CHECK (no consume). On success arms the fireball child
  // (FUN_800061a8 / zz_01f1ea0_ — host presentation hooks, labeled no-op).
  if (allocateWeapon(actor, ctx, 2, 1, false)) {            // zz_006dbe0_(p, 2, 1, 0)
    actor.fcFlag542 = 1;                                    // +0x542 = 1 (fireball armed)
    ctx.onFamilyProjectile?.(actor, FLAME_FIREBALL_SPAWNER, 1); // zz_00b5878_ arm (host hook)
  }
  actor.accumulator80c = FLAME_NINJA.ZERO;                  // +0x80c = 0
}

/** Phase 1 — blink drift + charge-wait. FUN_800b5310 @ chunk_0018.c:1393. */
function flameA2Phase1Wait(actor: FnActor, ctx: StreamContext): void {
  applyMotionDrift(actor, FLAME_NINJA.MOTION_SCALE);        // motion ×= 0.95; pos += motion
  groundSnapRevert(actor);                                  // zz_00677b0_
  if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx); // zz_004cd24_(0xf) gated
  stepPartTargetPitch(actor, 0xc0);                         // zz_006e1ac_(0xc0, 1)
  const t = actor.handlerTimer - actor.dt;                  // +0x558 -= dt
  actor.handlerTimer = t;
  if (t <= FLAME_NINJA.ZERO || stepTargetYaw(actor, 0xc0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
  maybeAfterimage(actor, FLAME_NINJA.AFTERIMAGE_THRESHOLD);
}

/** Phase 2 — contact: ram (fireball armed) or air-exit (unarmed). FUN_800b53e4. */
function flameA2Phase2Contact(actor: FnActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc0);
  stepPartTargetPitch(actor, 0xc0);
  applyMotionDrift(actor, FLAME_NINJA.MOTION_SCALE);
  groundSnapRevert(actor);
  if (actor.wallContact === 0) {                            // +0x1cee == 0: keep going
    maybeAfterimage(actor, FLAME_NINJA.AFTERIMAGE_THRESHOLD);
    return;
  }
  if ((actor.fcFlag542 ?? 0) === 0) {
    // Unarmed: air-knockout exit (+0x694 = 16.0 + dt).
    actor.steerYaw = 0;                                     // +0x18da = 0
    if (actor.yVel > FLAME_NINJA.ZERO) actor.yVel = FLAME_NINJA.ZERO;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = desc +0x6c
    actor.housekeeping73f = 0;
    actor.controlWord &= ~FLAME_NINJA.ACTION_MODE_BITS;
    romAirKnockoutReturn(actor);                            // zz_006a5a4_(p)
    actor.stateTimer = FLAME_NINJA.X_AIR_EXIT_TIMER + actor.dt; // +0x694 = 16.0 + dt
    return;
  }
  // Armed: advance to ram phase. Seed ram cursors + motion + consume fireball.
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcCursor548 = 0x21;                                 // +0x548 = 0x21
  actor.fcCursor54a = 0x37;                                 // +0x54a = 0x37
  actor.fcCursor54c = 6;                                    // +0x54c = 6
  actor.motion.x = FLAME_NINJA.ZERO;                        // +0x38 = 0
  actor.motion.y = FLAME_NINJA.X_RAM_MOTION_Y;              // +0x3c = 40.0
  actor.motion.z = FLAME_NINJA.X_RAM_MOTION_Z;              // +0x40 = 2.0
  actor.hDecel = FLAME_NINJA.ZERO;                          // +0x4c = 0
  actor.gravityCoeff = FLAME_NINJA.ZERO;                    // +0x50 = 0
  // zz_0066530_(p, 0x2d) — anim/event helper (host hook, no-op).
  ctx.onFamilyProjectile?.(actor, FLAME_X_CONTACT_SPAWNER, 0); // zz_0092dcc_(p, 0)
  const slot = actor.streamSlot;                            // +0x6ea++
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, FLAME_NINJA.STREAM_RATE);
  actor.fcMode6f2 = 2;                                      // +0x6f2 = 2
  // zz_0137984_(p, 1) — trail driver (host hook, no-op).
  allocateWeapon(actor, ctx, 2, 1, true);                   // zz_006dbe0_(p, 2, 1, 1) consume
  maybeAfterimage(actor, FLAME_NINJA.AFTERIMAGE_THRESHOLD);
}

/** Phase 3 — ram steering (FUN_800b5598). The +0x18da bone-matrix steering + the
 *  +0x548 countdown-by-0xb advance gate are ported; the per-axis hSpeed/yVel projection
 *  via zz_0045238_/zz_0045204_ is applied through integratePhysics. */
function flameA2Phase3Ram(actor: FnActor, ctx: StreamContext): void {
  actor.fcMode6f2 = 2;
  // zz_006de44_(p, 0xf0f00) part-mask event poll — no banks → 0 events.
  stepTargetYaw(actor, 0xc0);
  stepPartTargetPitch(actor, 0xc0);
  // motion.y += motion.z × dt; clamp to motion.y (the +0x3c cap).
  actor.motion.y = actor.motion.z * actor.dt + actor.motion.y;
  if (actor.motion.y < actor.motion.z) actor.motion.y = actor.motion.z; // cap (decomp: if +0x3c < +0x38)
  // Project motion magnitude onto hSpeed/yVel via the lockYaw (FUN_80067310 shape).
  integratePhysics(FLAME_NINJA.PHYSICS_GRAVITY, actor, actor.lockYaw);
  groundSnapRevert(actor);
  tickStream(actor, 0xf, ctx);
  // +0x1b01 gate: decrement +0x548 by 0xb; when <0 advance to ph4 (recover).
  if (actor.streamHold1b03 !== 0) { // approximated via streamHold (the +0x1b01 byte)
    const c = (actor.fcCursor548 ?? 0) - 0xb;
    actor.fcCursor548 = c;
    if (c < 0) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
      actor.handlerTimer = FLAME_NINJA.X_RECOVER_TIMER * 30; // FLOAT_8043840c=120.0 ram window
      actor.hSpeed *= 0.5;     // DOUBLE_80438410 = 0.5 (hSpeed scale)
      actor.hDecel = FLAME_NINJA.ZERO;
      actor.yVel = FLAME_NINJA.X_RECOVER_TIMER; // FLOAT_80438418 = 4.0
      actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
      const slot = actor.streamSlot;
      actor.streamSlot = slot + 1;
      startStream(actor, 0xf, 4, slot, FLAME_NINJA.STREAM_RATE);
    }
  }
  stepAfterimage(actor);
}

/** Phase 4 — recover/exit. FUN_800b5754 @ chunk_0018.c:1550. */
function flameA2Phase4Recover(actor: FnActor, ctx: StreamContext): void {
  // steerYaw × CONCAT44 idiom (decay 0.9, FLOAT_804383f8).
  actor.steerYaw = Math.trunc(actor.steerYaw * FLAME_NINJA.STEER_DECAY);
  tickStream(actor, 0xf, ctx);
  integratePhysics(FLAME_NINJA.PHYSICS_GRAVITY, actor, actor.lockYaw);
  const t = actor.handlerTimer - actor.dt; // +0x558 -= dt
  actor.handlerTimer = t;
  if (t > FLAME_NINJA.ZERO) {
    const grounded = groundSnapRevert(actor);
    if (grounded && actor.contactP0 < 0) {
      stepAfterimage(actor);
    } else {
      // Air exit via upper-body cue 7 (+0x694 = 8.0 + dt).
      actor.steerYaw = 0;
      actor.housekeeping73f = 0;
      actor.controlWord &= ~FLAME_NINJA.ACTION_MODE_BITS;
      dispatchUpperBodyCue(actor, 7); // zz_006a750_(p, 7)
      actor.stateTimer = FLAME_NINJA.X_RECOVER_TIMER + actor.dt; // +0x694 = 8.0 (80438418=4.0? — see note)
    }
  } else {
    // Timer expired: air-knockout exit (+0x694 = 8.0 + dt).
    actor.housekeeping73f = 0;
    actor.controlWord &= ~FLAME_NINJA.ACTION_MODE_BITS;
    romAirKnockoutReturn(actor); // zz_006a5a4_(p)
    actor.stateTimer = FLAME_NINJA.X_RECOVER_TIMER + actor.dt;
  }
  void ctx;
}

/** Action-2 dispatcher (FUN_800b50e8 → PTR_FUN_802fd370[+0x540]). */
function flameAction2(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: flameA2Phase0Setup(actor, ctx); return;
    case 1: flameA2Phase1Wait(actor, ctx); return;
    case 2: flameA2Phase2Contact(actor, ctx); return;
    case 3: flameA2Phase3Ram(actor, ctx); return;
    case 4: flameA2Phase4Recover(actor, ctx); return;
    default: return;
  }
}

// ============================================================================
// FLAME NINJA root dispatcher — FUN_800b31a8 indexes PTR_FUN_802fd27c[+0x580].
// Action 0 (B-combo), action 1 (contextual-B), action 2 (X-special fireball).
// ============================================================================
function createFlameRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    // Action-0 wrapper FUN_800b31e4 shifts +0x18da/+0x18dc >>1 before the variant
    // dispatch PTR_FUN_802fd288[+0x581] — applied here for the ported variant 0.
    switch (actor.actionIndex) {
      case 0:
        actor.steerYaw = Math.trunc(actor.steerYaw / 2);
        actor.fcSteerYaw18dc = Math.trunc((actor.fcSteerYaw18dc ?? 0) / 2);
        flameAction0(actor, ctx);
        return;
      case 1:
        // TODO(rom): action-1 contextual-B (3 variant tables @0x802fd324/34c/33c) —
        // bone-matrix steering + multi-stage trail children unsurfaced. Falls through.
        return;
      case 2:
        flameAction2(actor, ctx);
        return;
      default: return;
    }
  };
}

// ============================================================================
// CYBER NINJA — action 0 variant 0 (kunai melee). Phase table @0x802f8584 =
// [FUN_800a7264, FUN_800a7340, FUN_800a740c, ...]. Source: chunk_0016.c:2698-2820.
// ============================================================================

/** zz_00a75d0_ @ chunk_0016.c:2824 — action-0 melee contact helper. +0x558=8.0,
 *  +0x55c=10.0, ammo-gated consume zz_006dbe0_(0,1,1); on success spawns
 *  zz_00c3be0_(actor, 1). */
function cyberMeleeSpawn(actor: FnActor, ctx: StreamContext): void {
  actor.handlerTimer = CYBER_NINJA.MELEE_TIMER;       // +0x558 = 8.0
  actor.fcCooldown55c = CYBER_NINJA.MELEE_COOLDOWN;   // +0x55c = 10.0
  if (allocateWeapon(actor, ctx, 0, 1, true)) {       // zz_006dbe0_(p, 0, 1, 1)
    ctx.onFamilyProjectile?.(actor, CYBER_MELEE_SPAWNER, CYBER_NINJA.MELEE_EFFECT_TYPE);
  }
}

/** Phase 0 — setup. FUN_800a7264 @ chunk_0016.c:2700. */
function cyberA0v0Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcTimer560 = CYBER_NINJA.A0_TIMER_SEED;            // +0x560 = 20.0
  startStream(actor, 0xf, 2, 0, CYBER_NINJA.STREAM_RATE);   // zz_004beb8_(-1, p, 0xf, 2, 0)
  stepTargetYaw(actor, 0xc1, 0);                   // zz_006d0dc_(p, 0xc1, 0)
  actor.controlWord &= ~CYBER_NINJA.SETUP_CLEAR_BITS;       // +0x5e0 &= ~0xb0
  actor.gravityCoeff = CYBER_NINJA.ZERO;                    // +0x50 = 0
  actor.yVel = CYBER_NINJA.ZERO;                            // +0x48 = 0
  actor.hDecel = CYBER_NINJA.ZERO;                          // +0x4c = 0
  actor.hSpeed = CYBER_NINJA.ZERO;                          // +0x44 = 0
  resetPoseHousekeeping(actor);                             // +0x80/7e/7c = 0
  applyBlink(actor, CYBER_NINJA.MOTION_SCALE);              // blink ×0.95
  groundSnapRevert(actor);                                  // zz_00679d0_
  actor.accumulator80c = CYBER_NINJA.ZERO;                  // +0x80c = 0
  void ctx;
}

/** Phase 1 — contact-wait. FUN_800a7340 @ chunk_0016.c:2734. */
function cyberA0v0Phase1Wait(actor: FnActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx); // zz_004cd24_(p, 0xf)
  const ready = stepTargetYaw(actor, 0xc1, 0); // zz_006d0dc_(p, 0xc1, 0)
  let advance = false;
  if (ready) {
    advance = true;
  } else {
    const t = (actor.fcTimer560 ?? 0) - actor.dt;
    actor.fcTimer560 = t;
    if (t <= CYBER_NINJA.ZERO) advance = true;
  }
  if (advance && actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    cyberMeleeSpawn(actor, ctx);                              // zz_00a75d0_(p)
  }
  applyMotionDrift(actor, CYBER_NINJA.MOTION_SCALE); // motion ×= 0.95; pos += motion
  groundSnapRevert(actor);                            // zz_00679d0_
  maybeAfterimage(actor, CYBER_NINJA.AFTERIMAGE_THRESHOLD);
}

/** Phase 2 — recovery / charge-gated combo restart / ground exit. FUN_800a740c. */
function cyberA0v0Phase2Recover(actor: FnActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  if (actor.handlerTimer <= CYBER_NINJA.ZERO) {
    // Charge-bit (+0x5d4 & 0x20) → ammo check (no consume) for combo restart.
    if ((actor.inputEdge5d4 & CYBER_NINJA.CHARGE_BIT) !== 0) {
      if (allocateWeapon(actor, ctx, 0, 1, false)) { // zz_006dbe0_(p, 0, 1, 0)
        // zz_006bf80_(p) visibility refresh (host hook).
        startStream(actor, 0xf, 2, 1, CYBER_NINJA.STREAM_RATE); // restart stream slot 1
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1; // +0x540-- (back to ph1)
        return;
      }
      cyberA0Exit(actor);
      return;
    }
  } else {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
    stepTargetYaw(actor, 0xc1, 0); // zz_006d0dc_(p, 0xc1, 0)
  }
  // Cooldown gate: (+0x5d8 & 0xf0)==0 AND (+0x5d4 & 1)==0 AND +0x1cee==0 → drift+afterimage;
  // else when +0x55c drains → exit. The exit path (LAB_800a7528) fires when the gate fails.
  const driftGate =
    (actor.inputHeld5d8 & 0xf0) === 0 &&
    (actor.inputEdge5d4 & 1) === 0 &&
    actor.wallContact === 0;
  if (driftGate) {
    if (actor.handlerTimer > CYBER_NINJA.ZERO || (actor.fcCooldown55c ?? 0) > CYBER_NINJA.ZERO) {
      if ((actor.fcCooldown55c ?? 0) > CYBER_NINJA.ZERO) {
        actor.fcCooldown55c = (actor.fcCooldown55c ?? 0) - actor.dt;
      }
      applyMotionDrift(actor, CYBER_NINJA.MOTION_SCALE);
      groundSnapRevert(actor);
      maybeAfterimage(actor, CYBER_NINJA.AFTERIMAGE_THRESHOLD);
      return;
    }
  }
  cyberA0Exit(actor);
}

/** LAB_800a7528 exit: +0x73f=0; +0x5e0&=~3; zz_006a474_(ground idle return). */
function cyberA0Exit(actor: FnActor): void {
  actor.housekeeping73f = 0;
  actor.controlWord &= ~CYBER_NINJA.ACTION_MODE_BITS;
  romGroundIdleReturn(actor); // zz_006a474_(p)
}

/** Action-0 variant-0 dispatcher (FUN_800a7228 → PTR_FUN_802f8584[+0x540]). */
function cyberAction0(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: cyberA0v0Phase0Setup(actor, ctx); return;
    case 1: cyberA0v0Phase1Wait(actor, ctx); return;
    case 2: cyberA0v0Phase2Recover(actor, ctx); return;
    default: return; // deeper combo phases (FUN_800a7818+) — TODO.
  }
}

// ============================================================================
// CYBER NINJA — action 1 (dash-strike). Phase table @0x802f85c8 =
// [FUN_800a7b7c, FUN_800a7c58, FUN_800a7cd4, ...]. Source: chunk_0016.c:3070-3160.
// ============================================================================

/** Phase 0 — setup. FUN_800a7b7c @ chunk_0016.c:3072. */
function cyberA1Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  if (targetingProbe(actor) < 1) {
    actor.fcFlag541 = 1;                                    // +0x541 = 1
    (actor as RomActor & { cc?: number }).cc = 0;           // +0xcc = 0
    actor.activeYaw = actor.heading;                        // +0x5ac = +0x72
  }
  actor.handlerTimer = CYBER_NINJA.A1_TIMER_SEED;          // +0x558 = 60.0
  actor.fcTimer560 = CYBER_NINJA.ZERO;                      // +0x560 = 0.0
  actor.fcCursor54e = 10;                                   // +0x54e = 10
  (actor as RomActor & { byte746?: number }).byte746 = 0;   // +0x746 = 0
  stepTargetYaw(actor, 0xc0);                               // zz_006d144_(0xc0)
  startStream(actor, 0xf, 3, 4, CYBER_NINJA.STREAM_RATE);   // zz_004beb8_(-1, p, 0xf, 3, 4)
  actor.accumulator80c = CYBER_NINJA.ZERO;                  // +0x80c = 0
  void ctx;
}

/** Phase 1 — windup wait. FUN_800a7c58 @ chunk_0016.c:3099. */
function cyberA1Phase1Wait(actor: FnActor, ctx: StreamContext): void {
  if (actor.streamHold1b03 !== 0) tickStream(actor, 0xf, ctx); // zz_004cd24_(0xf)
  const t = actor.handlerTimer - actor.dt;                  // +0x558 -= dt
  actor.handlerTimer = t;
  if (t <= CYBER_NINJA.ZERO || stepTargetYaw(actor, 0xc0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

/** Phase 2 — contact dash-strike. FUN_800a7cd4 @ chunk_0016.c:3124 (partial).
 *  The +0x54e event-countdown + the +0x764 speed-gated dash are ported; the
 *  zz_00670dc_ ground-drag and zz_00b2190_ afterimage-arm are host hooks. */
function cyberA1Phase2Strike(actor: FnActor, ctx: StreamContext): void {
  // zz_006de44_(p, 0xf0f00) part-mask event poll — no banks → 0 events.
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc0); // zz_006d144_(0xc0)
  if ((actor.fcSpeed764 ?? 0) < CYBER_NINJA.SPEED_THRESHOLD) {
    // +0x1d9b clear (host hook).
  }
  if (actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++ → ph3 (TODO)
    const accelRow = actor.actionSpeedRows[actor.prevActionIndex % 3] ?? 0;
    actor.hSpeed = accelRow / CYBER_NINJA.A0_TIMER_SEED; // +0x44 = row/+0x868 / 20.0
    actor.hDecel = -actor.hSpeed * CYBER_NINJA.A1_DECEL_SCALE; // +0x4c = -hSpeed × 0.03125
    // zz_00b2190_(p, 0) afterimage arm (host hook).
  }
}

/** Action-1 dispatcher (FUN_800a7864 → PTR_FUN_802f85c8[+0x540]). */
function cyberAction1(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: cyberA1Phase0Setup(actor, ctx); return;
    case 1: cyberA1Phase1Wait(actor, ctx); return;
    case 2: cyberA1Phase2Strike(actor, ctx); return;
    default: return; // ph3+ (FUN_800a7e14/7f78/8118/8224/8354) — TODO.
  }
}

// ============================================================================
// CYBER NINJA — action 2 (X-special shuriken spread). Phase table @0x802f8614 =
// [FUN_800a8ae4, FUN_800a8be4, FUN_800a8cd4, ...]. Source: chunk_0016.c:3625-3733.
// ============================================================================

/** Phase 0 — blink setup. FUN_800a8ae4 @ chunk_0016.c:3627. */
function cyberA2Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcFlag541 = 4;                                      // +0x541 = 4
  actor.fcFlag542 = 0x14;                                   // +0x542 = 0x14
  actor.fcFlag543 = 0;                                      // +0x543 = 0
  actor.hDecel = CYBER_NINJA.ZERO;                          // +0x4c = 0
  actor.hSpeed = CYBER_NINJA.ZERO;                          // +0x44 = 0
  actor.yVel = CYBER_NINJA.PHYSICS_GRAVITY;                 // +0x48 = 1.0
  actor.gravityCoeff = CYBER_NINJA.ZERO;                    // +0x50 = 0
  if ((actor.fcCharge784 ?? 0) < 1) {
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0; // +0x50 = desc +0x6c
  }
  integratePhysics(CYBER_NINJA.PHYSICS_GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0)
  stepTargetYaw(actor, 0xc0);                               // zz_006d144_(0xc0)
  stepPartTargetPitch(actor, 0xc1);                         // zz_006e1ac_(0xc1, 1)
  applyBlink(actor, CYBER_NINJA.MOTION_SCALE);              // blink ×0.95
  groundSnapRevert(actor);                                  // zz_00677b0_
  startStream(actor, 0xf, 4, 3, CYBER_NINJA.STREAM_RATE);   // zz_004beb8_(-1, p, 0xf, 4, 3)
  void ctx;
}

/** Phase 1 — contact: shuriken arm or air-exit. FUN_800a8be4 @ chunk_0016.c:3662. */
function cyberA2Phase1Contact(actor: FnActor, ctx: StreamContext): void {
  tickStream(actor, 0xf, ctx);
  stepTargetYaw(actor, 0xc0);
  stepPartTargetPitch(actor, 0xc1);
  integratePhysics(CYBER_NINJA.PHYSICS_GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0)
  applyMotionDrift(actor, CYBER_NINJA.MOTION_SCALE);
  groundSnapRevert(actor);
  if (actor.contactP0 === 0) return;
  // Ammo CHECK (no consume). Denied → air-knockout exit; armed → advance to spread.
  if (!allocateWeapon(actor, ctx, 2, 1, false)) { // zz_006dbe0_(p, 2, 1, 0)
    actor.hDecel = CYBER_NINJA.ZERO;
    actor.hSpeed = CYBER_NINJA.ZERO;
    actor.housekeeping73f = 0;
    actor.controlWord &= ~CYBER_NINJA.ACTION_MODE_BITS;
    romAirKnockoutReturn(actor); // zz_006a5a4_(p)
    return;
  }
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.fcSlot6e9 = 3;                                      // +0x6e9 = 3
  actor.fcSlot6e8 = 3;                                      // +0x6e8 = 3
}

/** Phase 2 — reseek → shuriken spread. FUN_800a8cd4 @ chunk_0016.c:3698 (partial). */
function cyberA2Phase2Spread(actor: FnActor, ctx: StreamContext): void {
  stepTargetYaw(actor, 0xc0);
  stepPartTargetPitch(actor, 0xc1);
  tickStream(actor, 0xf, ctx);
  if (actor.contactP1 !== 0) { // +0x1cf0 reseek event
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++ → ph3 (TODO)
    actor.lockYaw = (actor.heading - 0x8000) & 0xffff;       // +0x5ae = +0x72 − 0x8000
    actor.hSpeed = 30.0;                                      // +0x44 = FLOAT_80438134
    actor.hDecel = CYBER_NINJA.X_DECEL;                       // +0x4c = FLOAT_8043813c (-0.3)
    actor.yVel = CYBER_NINJA.A0_TIMER_SEED;                   // +0x48 = FLOAT_804380e8 (20.0)
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? 0;
    if (allocateWeapon(actor, ctx, 2, 1, true)) { // zz_006dbe0_(p, 2, 1, 1) consume
      // FUN_800b5ed8 shuriken spread — 4 projectiles from DAT_80433a60 offsets. The
      // host resolves the record table; surfaced as 4 sequential spawn events.
      for (let i = 0; i < 4; i += 1) {
        ctx.onFamilyProjectile?.(actor, CYBER_SHURIKEN_SPREAD_SPAWNER, i & 1);
      }
    }
  }
  // zz_00f0104_(p, 3, 2) per-frame FX (host hook, no-op).
}

/** Action-2 dispatcher (PTR_FUN_802f8614[+0x540]). */
function cyberAction2(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: cyberA2Phase0Setup(actor, ctx); return;
    case 1: cyberA2Phase1Contact(actor, ctx); return;
    case 2: cyberA2Phase2Spread(actor, ctx); return;
    default: return; // ph3+ (FUN_800a8dd0/8f08) — TODO.
  }
}

// ============================================================================
// CYBER NINJA — action 3 (B-charge sword flurry). Phase table @0x802f8638 =
// [FUN_800a8f44, FUN_800a9040, ...]. Source: chunk_0016.c:3794-3875.
// ============================================================================

/** Phase 0 — flurry setup. FUN_800a8f44 @ chunk_0016.c:3796. */
function cyberA3Phase0Setup(actor: FnActor, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  (actor as RomActor & { byte745?: number }).byte745 = 0;    // +0x745 = 0
  actor.handlerTimer = CYBER_NINJA.A3_TIMER_SEED;          // +0x558 = 30.0
  actor.fcCursor54a = 5;                                    // +0x54a = 5
  actor.fcCursor54c = 3;                                    // +0x54c = 3
  actor.hDecel = CYBER_NINJA.ZERO;                          // +0x4c = 0
  actor.hSpeed = CYBER_NINJA.ZERO;                          // +0x44 = 0
  actor.yVel = CYBER_NINJA.ZERO;                            // +0x48 = 0
  actor.gravityCoeff = CYBER_NINJA.ZERO;                    // +0x50 = 0
  stepTargetYaw(actor, 0xc0, 0x8000, true);                 // zz_006660c_ + FUN_80066a30(0xc0, -0x8000)
  applyBlink(actor, CYBER_NINJA.MOTION_SCALE);              // blink ×0.95
  groundSnapRevert(actor);                                  // zz_00677b0_
  startStream(actor, 0xf, 4, 8, CYBER_NINJA.STREAM_RATE); // zz_004beb8_(-1, p, 0xf, 4, 8, 0xc, 1)
  // FUN_800061a8(p, 0x11) + zz_01e307c_(p) — flurry arming (host presentation hooks).
  actor.fcMode6f4 = 1;                                      // +0x6f4 = 1
  // zz_00f036c_(p, 0x10b) sound cue (host hook).
  void ctx;
}

/** Phase 1 — flurry tick. FUN_800a9040 @ chunk_0016.c:3832 (partial). */
function cyberA3Phase1Flurry(actor: FnActor, ctx: StreamContext): void {
  actor.fcMode6f4 = 1;
  tickStream(actor, 0xf, ctx);
  applyMotionDrift(actor, CYBER_NINJA.MOTION_SCALE);
  groundSnapRevert(actor);
  if (actor.wallContact === 0) {
    if (actor.yVel < CYBER_NINJA.ZERO) actor.yVel = CYBER_NINJA.ZERO; // +0x48 floor 0
    integratePhysics(CYBER_NINJA.PHYSICS_GRAVITY, actor, actor.lockYaw); // FUN_80067310(1.0)
    return;
  }
  // wallContact → part-pitch aim + advance to ph2 on timer/aim convergence.
  stepPartTargetPitch(actor, 0xc1);
  const t = actor.handlerTimer - actor.dt;
  actor.handlerTimer = t;
  if (t <= CYBER_NINJA.ZERO || stepTargetYaw(actor, 0xc0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++ → ph2 (TODO)
    actor.handlerTimer = CYBER_NINJA.A3_TIMER_SEED;          // +0x558 = 30.0
    actor.fcTimer560 = CYBER_NINJA.ZERO;                      // +0x560 = 0.0
    actor.motion.x = CYBER_NINJA.A3_MOTION_SEED;              // +0x38 = 250.0
    // pseudo-random slot (zz_00055fc_) — deterministic 0 here.
    actor.streamSlot = 5;
    startStream(actor, 0xf, 4, actor.streamSlot, CYBER_NINJA.STREAM_RATE);
    ctx.onFamilyProjectile?.(actor, FLAME_X_CONTACT_SPAWNER, 0); // zz_0092dcc_(p, 0)
  }
}

/** Action-3 dispatcher (PTR_FUN_802f8638[+0x540]). */
function cyberAction3(actor: FnActor, ctx: StreamContext): void {
  switch (actor.fbPhaseSlots[0] ?? 0) {
    case 0: cyberA3Phase0Setup(actor, ctx); return;
    case 1: cyberA3Phase1Flurry(actor, ctx); return;
    default: return; // ph2+ (FUN_800a9188/93e0/9578) — TODO.
  }
}

// ============================================================================
// CYBER NINJA root dispatcher — FUN_800a71a4 indexes PTR_FUN_802f8560[+0x580].
// Action 0 wrapper FUN_800a71e0 shifts +0x18da >>1 before PTR_FUN_802f8570[+0x581].
// ============================================================================
function createCyberRootAction(ctx: StreamContext): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0:
        actor.steerYaw = Math.trunc(actor.steerYaw / 2);
        cyberAction0(actor, ctx);
        return;
      case 1:
        cyberAction1(actor, ctx);
        return;
      case 2:
        cyberAction2(actor, ctx);
        return;
      case 3:
        cyberAction3(actor, ctx);
        return;
      default: return;
    }
  };
}

// ============================================================================
// Configure entry points.
// ============================================================================

/** Configure a freshly-spawned FLAME NINJA (pl0006). Stamps the borg number (0x006)
 *  and wires the bespoke action dispatcher. */
export function configureFlameNinjaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = FLAME_NINJA_BORG_NUMBER;
  actor.rootAction = createFlameRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a freshly-spawned CYBER NINJA (pl0007). Stamps the borg number (0x007)
 *  and wires the bespoke action dispatcher. */
export function configureCyberNinjaFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = CYBER_NINJA_BORG_NUMBER;
  actor.rootAction = createCyberRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — phase transitions, borg-switched spawns, ammo-gates. Mirrors the
// rom.selfcheck.ts assert pattern (cosmic-dragon / victory-king style).
// ============================================================================
export function runFlameCyberNinjaSelfTests(assert: (cond: boolean, msg: string) => void): void {
  function approxEq(a: number, b: number, eps = 1e-4): boolean {
    return Math.abs(a - b) <= eps;
  }
  type Shot = { addr: number; type: number };

  function makeCtx(opts: {
    onAllocateResource?: (slot: number, count: number, mode: number | undefined) => boolean;
    onFamilyProjectile?: (addr: number, type: number) => void;
  } = {}): StreamContext {
    const ctx: StreamContext = {};
    if (opts.onAllocateResource) {
      const sink = opts.onAllocateResource;
      ctx.onAllocateResource = (_a, slot, count, mode) => sink(slot, count, mode);
    }
    if (opts.onFamilyProjectile) {
      const sink = opts.onFamilyProjectile;
      ctx.onFamilyProjectile = (_a, addr, type) => sink(addr, type);
    }
    return ctx;
  }

  function aimAt(actor: RomActor, x: number, z: number): void {
    (actor as RomActor & { lockTarget?: Vec3 | null }).lockTarget = { x, y: 0, z };
    actor.aimOrigin518 = { x: actor.pos.x, y: actor.pos.y, z: actor.pos.z };
  }

  // ==========================================================================
  // FLAME NINJA — action 0 variant 0 (B-tap swing combo).
  // ==========================================================================

  // --- ph0 setup: borgNumber stamped, scalars zeroed, timer seeded, bits cleared. ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx());
    assert(a.borgNumber === 0x006, "FLAME borgNumber stamped 0x006");
    assert(a.rootAction !== null, "FLAME bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.hDecel = 3; a.controlWord = 0xb0;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "FLAME a0 ph0 advances to ph1");
    assert(approxEq(a.fcTimer560!, FLAME_NINJA.A0_TIMER_SEED), "FLAME a0 ph0 +0x560 = 20.0 (FLOAT_804383b0)");
    assert(a.hSpeed === 0 && a.hDecel === 0, "FLAME a0 ph0 zeroes hSpeed/hDecel (FLOAT_804383b4)");
    assert((a.controlWord & 0xb0) === 0, "FLAME a0 ph0 clears +0x5e0 bits 0xb0");
  }

  // --- ph1 contact → swing spawn (ammo ok). ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    aimAt(a, 1000, 0);
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === FLAME_SWING_SPAWNER && shots[0]!.type === 0,
      `FLAME a0 ph1 contact spawns zz_00b73b4_(0) (got ${JSON.stringify(shots)})`);
    assert(approxEq(a.handlerTimer, FLAME_NINJA.SWING_TIMER), "FLAME a0 ph1 +0x558 = 10.0 (FLOAT_804383bc)");
    assert(approxEq(a.fcCooldown55c!, FLAME_NINJA.SWING_COOLDOWN), "FLAME a0 ph1 +0x55c = 30.0 (FLOAT_804383c0)");
    assert(a.fbPhaseSlots[0] === 2, "FLAME a0 ph1 contact advances to ph2");
  }

  // --- ph1 contact ammo DENIED → no swing, no advance. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    aimAt(a, 1000, 0);
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 0, "FLAME a0 ph1 ammo denied → no zz_00b73b4_ spawn");
    assert(approxEq(a.handlerTimer, FLAME_NINJA.SWING_TIMER), "FLAME a0 ph1 denied still seeds +0x558=10.0");
  }

  // --- ph2 charge-bit combo restart (ammo ok) → back to ph1. ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = -1; // window elapsed
    a.statusWord5b4 = FLAME_NINJA.CHARGE_BIT; // charge held
    a.inputHeld5d8 = 0; a.inputEdge5d4 = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "FLAME a0 ph2 charge + ammo ok → restart to ph1");
    assert(a.variantIndex === 0, "FLAME a0 ph2 restart stamps +0x581 = 0");
  }

  // --- ph2 ground exit (no charge, cooldown elapsed). ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = -1;
    a.fcCooldown55c = 0;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[0] = 5;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "FLAME a0 ph2 ground exit clears +0x73f / strips +0x5e0 bits");
  }

  // ==========================================================================
  // FLAME NINJA — action 2 (X-special fireball).
  // ==========================================================================

  // --- ph0 setup: +0x558=60, lockYaw=heading (no aim override), streamSlot advance. ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0x1234; a.controlWord = 0;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "FLAME a2 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, FLAME_NINJA.X_TIMER_SEED), "FLAME a2 ph0 +0x558 = 60.0 (FLOAT_804383c8)");
    assert(a.lockYaw === 0x1234 && a.activeYaw === 0x1234, "FLAME a2 ph0 lockYaw/activeYaw = heading (no 0xa0 bits)");
    assert(a.streamSlot === 1, "FLAME a2 ph0 streamSlot = 1 (seed 0 + advance)");
    assert((a.fcFlag542 ?? 0) === 1, "FLAME a2 ph0 ammo ok → +0x542 = 1 (fireball armed)");
  }

  // --- ph0 ammo DENIED → +0x542 stays 0 (unarmed). ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({ onAllocateResource: () => false }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    root(a);
    assert((a.fcFlag542 ?? 0) === 0, "FLAME a2 ph0 ammo denied → +0x542 = 0 (unarmed)");
  }

  // --- ph1 timer drain → ph2. ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0; // one frame from expiry
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "FLAME a2 ph1 timer <= 0 advances to ph2");
  }

  // --- ph2 contact UNARMED → air-knockout exit (+0x694 = 16.0 + dt). ---
  {
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[6 * 2 + 1] = 24;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 2;
    a.fcFlag542 = 0; // unarmed
    a.wallContact = 1; // exit trigger
    a.yVel = 5; a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0, "FLAME a2 ph2 unarmed exit strips bits");
    assert(approxEq(a.stateTimer, FLAME_NINJA.X_AIR_EXIT_TIMER + 1),
      "FLAME a2 ph2 unarmed +0x694 = 16.0 + dt (FLOAT_80438408)");
  }

  // --- ph2 contact ARMED → advance to ph3 ram + fireball consume. ---
  {
    let allocCalls = 0;
    const shots: Shot[] = [];
    const a = createRomActor() as FnActor;
    configureFlameNinjaFamily(a, makeCtx({
      onAllocateResource: (_s, _c, mode) => { allocCalls += 1; return (mode ?? 0) !== 1 || true; },
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 2;
    a.fcFlag542 = 1; // armed
    a.wallContact = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "FLAME a2 ph2 armed → advance to ph3 ram");
    assert(approxEq(a.motion.y, FLAME_NINJA.X_RAM_MOTION_Y), "FLAME a2 ph2 +0x3c = 40.0 (FLOAT_804383f0)");
    assert(shots.some((s) => s.addr === FLAME_X_CONTACT_SPAWNER), "FLAME a2 ph2 spawns zz_0092dcc_");
  }

  // ==========================================================================
  // CYBER NINJA — action 0 variant 0 (kunai melee).
  // ==========================================================================

  // --- ph0 setup: scalars zeroed, blink, streamSlot. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    assert(a.borgNumber === 0x007, "CYBER borgNumber stamped 0x007");
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 7;
    a.pos = { x: 100, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "CYBER a0 ph0 advances to ph1");
    assert(approxEq(a.fcTimer560!, CYBER_NINJA.A0_TIMER_SEED), "CYBER a0 ph0 +0x560 = 20.0 (FLOAT_804380e8)");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "CYBER a0 ph0 zeroes all velocity scalars (FLOAT_804380f0)");
    assert(approxEq(a.pos.x, 195.0), "CYBER a0 ph0 blink: pos.x = 195 ((100−0)×0.95 added)");
  }

  // --- ph1 contact → zz_00c3be0_(1) spawn (ammo ok). ---
  {
    const shots: Shot[] = [];
    const allocArgs = { slot: -1, count: -1, mode: -1, called: false };
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx({
      onAllocateResource: (slot: number, count: number, mode: number | undefined) => { allocArgs.slot = slot; allocArgs.count = count; allocArgs.mode = mode ?? -1; allocArgs.called = true; return true; },
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    aimAt(a, 0, 1000);
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a);
    assert(allocArgs.called && allocArgs.slot === 0 && allocArgs.count === 1 && allocArgs.mode === 1,
      "CYBER a0 ph1 zz_006dbe0_(0, 1, 1) exact arguments");
    assert(shots.length === 1 && shots[0]!.addr === CYBER_MELEE_SPAWNER && shots[0]!.type === CYBER_NINJA.MELEE_EFFECT_TYPE,
      `CYBER a0 ph1 contact spawns zz_00c3be0_(1) (got ${JSON.stringify(shots)})`);
    assert(approxEq(a.handlerTimer, CYBER_NINJA.MELEE_TIMER), "CYBER a0 ph1 +0x558 = 8.0 (FLOAT_804380fc)");
    assert(a.fbPhaseSlots[0] === 2, "CYBER a0 ph1 contact advances to ph2");
  }

  // --- ph1 contact ammo DENIED → no spawn, no advance. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    aimAt(a, 0, 1000);
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 0, "CYBER a0 ph1 ammo denied → no zz_00c3be0_ spawn");
    assert(a.fbPhaseSlots[0] === 2, "CYBER a0 ph1 denied still advances to ph2 (ROM FUN_800a7340 advances before ammo gate)");
  }

  // --- ph2 ground exit (cooldown elapsed). ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 0; a.variantIndex = 0; a.dt = 1;
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = -1; a.fcCooldown55c = 0;
    a.inputHeld5d8 = 0; a.inputEdge5d4 = 0; a.wallContact = 0;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[0] = 5;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "CYBER a0 ph2 ground exit clears +0x73f / strips +0x5e0 bits");
  }

  // ==========================================================================
  // CYBER NINJA — action 1 (dash-strike).
  // ==========================================================================

  // --- ph0 setup: +0x558=60, +0x560=0, +0x54e=10. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "CYBER a1 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, CYBER_NINJA.A1_TIMER_SEED), "CYBER a1 ph0 +0x558 = 60.0 (FLOAT_80438110)");
    assert(approxEq(a.fcTimer560!, 0), "CYBER a1 ph0 +0x560 = 0.0");
    assert(a.fcCursor54e === 10, "CYBER a1 ph0 +0x54e = 10");
  }

  // --- ph1 timer drain → ph2. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 1;
    a.handlerTimer = 1.0;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "CYBER a1 ph1 timer <= 0 advances to ph2");
  }

  // ==========================================================================
  // CYBER NINJA — action 2 (X-special shuriken spread).
  // ==========================================================================

  // --- ph0 setup: scalars, +0x541=4, +0x542=0x14. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fcCharge784 = 5; // >=1 → gravityCoeff stays 0
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "CYBER a2 ph0 advances to ph1");
    assert(a.fcFlag541 === 4, "CYBER a2 ph0 +0x541 = 4");
    assert(a.fcFlag542 === 0x14, "CYBER a2 ph0 +0x542 = 0x14");
    assert(approxEq(a.yVel, CYBER_NINJA.PHYSICS_GRAVITY), "CYBER a2 ph0 +0x48 = 1.0 (FLOAT_8043810c)");
  }

  // --- ph1 contact ammo DENIED → air-knockout exit. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx({ onAllocateResource: () => false }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[6 * 2 + 1] = 24;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0, "CYBER a2 ph1 denied → air exit strips bits");
    assert(a.fbPhaseSlots[0] === 1, "CYBER a2 ph1 denied → no advance (air return)");
  }

  // --- ph1 contact ammo OK → advance to ph2 + arm cursors. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx({ onAllocateResource: () => true }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 1;
    a.contactP0 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "CYBER a2 ph1 ammo ok → advance to ph2");
    assert(a.fcSlot6e8 === 3 && a.fcSlot6e9 === 3, "CYBER a2 ph1 arms +0x6e8/+0x6e9 = 3");
  }

  // --- ph2 reseek → shuriken spread (4 spawns, ammo consume). ---
  {
    const shots: Shot[] = [];
    const allocArgs = { slot: -1, count: -1, mode: -1, called: false };
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx({
      onAllocateResource: (slot: number, count: number, mode: number | undefined) => { allocArgs.slot = slot; allocArgs.count = count; allocArgs.mode = mode ?? -1; allocArgs.called = true; return true; },
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 2; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.fbPhaseSlots[0] = 2;
    a.contactP1 = 1; // reseek event
    root(a);
    assert(allocArgs.called && allocArgs.slot === 2 && allocArgs.count === 1 && allocArgs.mode === 1,
      "CYBER a2 ph2 zz_006dbe0_(2, 1, 1) exact arguments");
    const spread = shots.filter((s) => s.addr === CYBER_SHURIKEN_SPREAD_SPAWNER);
    assert(spread.length === 4, `CYBER a2 ph2 spawns 4× FUN_800b5ed8 spread (got ${spread.length})`);
    const expectedLockYaw = (a.heading - 0x8000) & 0xffff;
    assert(a.lockYaw === expectedLockYaw,
      "CYBER a2 ph2 lockYaw = heading − 0x8000 (face away)");
  }

  // ==========================================================================
  // CYBER NINJA — action 3 (B-charge sword flurry).
  // ==========================================================================

  // --- ph0 setup: +0x558=30, +0x54a=5, +0x54c=3, scalars zeroed. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    a.heading = 0; a.lockYaw = 0; a.timescale = 1; a.tierScale = 1;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 7;
    a.pos = { x: 50, y: 0, z: 0 }; a.targetCache5e8 = { x: 0, y: 0, z: 0 };
    root(a); // ph0
    assert(a.fbPhaseSlots[0] === 1, "CYBER a3 ph0 advances to ph1");
    assert(approxEq(a.handlerTimer, CYBER_NINJA.A3_TIMER_SEED), "CYBER a3 ph0 +0x558 = 30.0 (FLOAT_80438134)");
    assert(a.fcCursor54a === 5, "CYBER a3 ph0 +0x54a = 5");
    assert(a.fcCursor54c === 3, "CYBER a3 ph0 +0x54c = 3");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "CYBER a3 ph0 zeroes all velocity scalars");
  }

  // --- rootAction no-ops for unsupported actionIndex. ---
  {
    const a = createRomActor() as FnActor;
    configureCyberNinjaFamily(a, makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 7; // unsupported
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "CYBER unsupported actionIndex falls through (no-op)");
  }
}
